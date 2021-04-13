#pragma once
#include <qcolor.h>
#include <qimage.h>
#include <cstdlib>
const double PI = 3.14;
using namespace std;

class Filter {
protected:
	virtual QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const = 0;
public:
	virtual ~Filter() = default;
	virtual QImage Process(const QImage& _image) const;
};

class InvertFilter : public Filter {
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const override;
};

class Kernel {
protected:
	unique_ptr<float[]>data;
	size_t radius;
	size_t GetLength() const { return GetSize() * GetSize(); }
public:
	Kernel(size_t radius) : radius(radius) { data = make_unique<float[]>(GetLength()); }
	Kernel(const Kernel& other) :Kernel(other.radius) {
		copy(other.data.get(), other.data.get() + GetLength(), data.get());
	}
	size_t GetRadius() const { return radius; }
	size_t GetSize()const { return 2 * radius + 1; }
	float operator [](size_t id)const { return data[id]; }
	float& operator [](size_t id) { return data[id]; }

};

class MatrixFilter : public Filter {
protected:
	Kernel mKernel;
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const override;
public:
	MatrixFilter(const Kernel& kernel) : mKernel(kernel) {};
	virtual ~MatrixFilter() = default;
};

class BlurKernel : public Kernel {
public:
	Kernel::Kernel;
	BlurKernel(size_t radius = 1) :Kernel(radius) {
		for  (size_t i = 0; i < GetLength(); i++){
			data[i] = 1.0f / GetLength();
		}
	}
};

class BlurFilter : public MatrixFilter {
public:
	BlurFilter(size_t radius = 1) : MatrixFilter(BlurKernel(radius)) {}
};

class GaussianKernel : public Kernel {
public:
	Kernel::Kernel;
	GaussianKernel(size_t radius = 1, float sigma = 2.f) :Kernel(radius) {
		float norm = 0;
		int signed_radius = static_cast<int>(radius);
		int size = GetSize();
		for (int x = -signed_radius; x <= signed_radius; x++){
			for (int y = -signed_radius; y <= signed_radius; y++){
				size_t index = (x + radius) * size + y + radius;
				data[index] = exp(-(x * x + y * y) / (2 * sigma * sigma));
				norm += data[index];
			}
		}
		for (size_t i = 0; i < GetLength(); i++){
			data[i] /= norm;
		}
	}
};

class GaussianFilter : public MatrixFilter {
public:
	GaussianFilter(size_t radius = 1, float sigma = 2.f) : MatrixFilter(GaussianKernel(radius,sigma)) {}
};

class GrayScaleFilter : public Filter {
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const override;
};

class SepiaFilter :public Filter {
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const override;
};

class BrightnessFilter :public Filter {
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const override;
};

class SobelKernel : public Kernel {
public:
	Kernel::Kernel;
	SobelKernel(size_t radius = 1) :Kernel(radius) {
		data[0] = -1.f; data[1] = -2.f; data[2] = -1.f;
		data[3] = 0.f; data[4] = 0.f; data[5] = 0.f;
		data[6] = 1.f; data[7] = 2.f; data[8] = 1.f;
	}
};

class SobelFilter : public MatrixFilter {
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const override;
public:
	SobelFilter(size_t radius = 1) : MatrixFilter(SobelKernel(radius)) {}
};

class SharpnessKernel : public Kernel {
public:
	Kernel::Kernel;
	SharpnessKernel(size_t radius = 1) :Kernel(radius) {
		data[0] = 0.f; data[1] = -1.f; data[2] = 0.f;
		data[3] = -1.f; data[4] = 5.f; data[5] = -1.f;
		data[6] = 0.f; data[7] = -1.f; data[8] = 0.f;
	}
};

class SharpnessFilter : public MatrixFilter{
public:
	SharpnessFilter(size_t radius = 1) : MatrixFilter(SharpnessKernel(radius)) {}
};

class HorizontalWaveFilter : public Filter {
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const override;
};

class VerticalWavesFilter : public Filter{
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const override;
};

class MedianKernel : public Kernel {
public:
	Kernel::Kernel;
	MedianKernel(size_t radius = 1) :Kernel(radius) {}
};

class MedianFilter : public MatrixFilter {
protected:
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const override;
public:
	MedianFilter(size_t radius = 1) : MatrixFilter(MedianKernel(radius)) {}
};

class DilationKernel : public Kernel {
public:
	Kernel::Kernel;
	DilationKernel(size_t radius = 1) :Kernel(radius) {
		int length = GetLength();
		for (int i = 0; i < length; i++) {
			srand(time(NULL));
			data[i] = rand() % 10;
		}
	}
};

class DilationFilter : public MatrixFilter {
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const override;
public:
	DilationFilter(size_t radius = 1) : MatrixFilter(DilationKernel(radius)) {}
};

class ErosionKernel : public Kernel {
public:
	Kernel::Kernel;
	ErosionKernel(size_t radius = 1) :Kernel(radius) {
		int length = GetLength();
		for (int i = 0; i < length; i++) {
			srand(time(NULL));
			data[i] = rand() % 10;
		}
	}
};

class ErosionFilter : public MatrixFilter {
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const override;
public:
	ErosionFilter(size_t radius = 1) : MatrixFilter(ErosionKernel(radius)) {}
};

class OpeningKernel : public Kernel {
public:
	Kernel::Kernel;
	OpeningKernel(size_t radius = 1) :Kernel(radius) {}
};

class OpeningFilter : public MatrixFilter {
public:
	OpeningFilter(size_t radius = 1) : MatrixFilter(OpeningKernel(radius)) {}
	QImage Process(const QImage& _image) const override;
};

class ClosingKernel : public Kernel {
public:
	Kernel::Kernel;
	ClosingKernel(size_t radius = 1) :Kernel(radius) {}
};

class ClosingFilter : public MatrixFilter {
public:
	ClosingFilter(size_t radius = 1) : MatrixFilter(ClosingKernel(radius)) {}
	QImage Process(const QImage& _image) const override;
};

class GradKernel : public Kernel {
public:
	Kernel::Kernel;
	GradKernel(size_t radius = 1) :Kernel(radius) {}
};

class GradFilter : public MatrixFilter {
public:
	GradFilter(size_t radius = 1) : MatrixFilter(GradKernel(radius)) {}
	QImage Process(const QImage& _image) const override;
};

class PerfectReflectorFilter : public Filter {
	mutable float maxR = 0;
	mutable float maxG = 0;
	mutable float maxB = 0;
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const override;
public:
	QImage Process(const QImage& _image) const override;
};

class GrayWorldFilter : public Filter {
	mutable float sumR = 0;
	mutable float sumG = 0;
	mutable float sumB = 0;
	mutable float scaleR = 0;
	mutable float scaleG = 0;
	mutable float scaleB = 0;
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const override;
public:
	QImage Process(const QImage& _image) const override;
};

class EmbrossingKernel : public Kernel {
public:
	Kernel::Kernel;
	EmbrossingKernel(size_t radius = 1) :Kernel(radius) {
		data[0] = 0.f; data[1] = 1.f; data[2] = 0.f;
		data[3] = 1.f; data[4] = 0.f; data[5] = -1.f;
		data[6] = 0.f; data[7] = -1.f; data[8] = 0.f;
	}
};

class EmbossingFilter : public MatrixFilter {
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const override;
public:
	EmbossingFilter(size_t radius = 1) : MatrixFilter(EmbrossingKernel(radius)) {}
};

class TurnFilter : public Filter {
	mutable double angle = 1;
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const override;
};

class TransferFilter : public Filter {
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const override;
};

class GlassFilter : public Filter {
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const override;
};

class AdditionalSharpnessKernel : public Kernel {
public:
	Kernel::Kernel;
	AdditionalSharpnessKernel(size_t radius = 1) :Kernel(radius) {
		data[0] = -1.f; data[1] = -1.f; data[2] = -1.f;
		data[3] = -1.f; data[4] = 9.f; data[5] = -1.f;
		data[6] = -1.f; data[7] = -1.f; data[8] = -1.f;
	}
};

class AdditionalSharpnessFilter : public MatrixFilter {
public:
	AdditionalSharpnessFilter(size_t radius = 1) : MatrixFilter(AdditionalSharpnessKernel(radius)) {}
};

class ShharraKernel : public Kernel {
public:
	Kernel::Kernel;
	ShharraKernel(size_t radius = 1) :Kernel(radius) {
		data[0] = 3.f; data[1] = 10.f; data[2] = 3.f;
		data[3] = 0.f; data[4] = 0.f; data[5] = 0.f;
		data[6] = -3.f; data[7] = -10.f; data[8] = -3.f;
	}
};

class ShharraFilter : public MatrixFilter {
protected:
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const override;
public:
	ShharraFilter(size_t radius = 1) : MatrixFilter(ShharraKernel(radius)) {}
};

class PrewittaKernel : public Kernel {
public:
	Kernel::Kernel;
	PrewittaKernel(size_t radius = 1) :Kernel(radius) {
		data[0] = -1.f; data[1] = -1.f; data[2] = -1.f;
		data[3] = 0.f; data[4] = 0.f; data[5] = 0.f;
		data[6] = 1.f; data[7] = 1.f; data[8] = 1.f;
	}
};

class PrewittaFilter : public MatrixFilter {
protected:
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y) const override;
public:
	PrewittaFilter(size_t radius = 1) : MatrixFilter(PrewittaKernel(radius)) {}
};

class MotionBlurKernel : public Kernel {
public:
	Kernel::Kernel;
	MotionBlurKernel(size_t radius = 1) :Kernel(radius) {
		int length = GetLength();
		int size = GetSize();
		for (int i = 0; i < length; i++){
			if (i % (size + 1) == 0) { 
				data[i] = 1.f / size; }
			else { data[i] = 0.f; }
		}
	}
};

class MotionBlurFilter : public MatrixFilter {
public:
	MotionBlurFilter(size_t radius = 1) : MatrixFilter(MotionBlurKernel(radius)) {}
};

class BlackHatKernel : public Kernel {
public:
	Kernel::Kernel;
	BlackHatKernel(size_t radius = 1) :Kernel(radius) {}
};

class BlackHatFilter : public MatrixFilter {
public:
	BlackHatFilter(size_t radius = 1) : MatrixFilter(BlackHatKernel(radius)) {}
	QImage Process(const QImage& _image) const override;

};

class TopHatKernel : public Kernel {
public:
	Kernel::Kernel;
	TopHatKernel(size_t radius = 1) :Kernel(radius) {}
};

class TopHatFilter : public MatrixFilter {
public:
	TopHatFilter(size_t radius = 1) : MatrixFilter(TopHatKernel(radius)) {}
	QImage Process(const QImage& _image) const override;
};

class LinearCorrectionFilter : public Filter {
	mutable float maxR = 0;
	mutable float maxG = 0;
	mutable float maxB = 0;
	mutable float minR = 255;
	mutable float minG = 255;
	mutable float minB = 255;
	QColor CalcNewPixelColor(const QImage& _image, int _x, int _y)const override;
public:
	QImage Process(const QImage& _image) const override;
};

