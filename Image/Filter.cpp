#include "Filter.h"
 template <class Type>
 Type Clamp(Type value, Type max, Type min) {
	 if (value > max) return max;
	 if (value < min)return min;
	 return value;
 }

 QImage Filter::Process(const QImage& _image) const {
	 QImage result(_image);
	 int width = _image.width();
	 int height = _image.height();
	 for (int x = 0; x < width; x++){
		 for (int y = 0; y < height; y++){
			 QColor color = CalcNewPixelColor(_image, x, y);
			 result.setPixelColor(x, y, color);
		 }
	 }
	 return result;
 }

 QColor InvertFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y)const {
	 QColor color = _image.pixelColor(_x, _y);
	 color.setRgb(255 - color.red(), 255 - color.green(), 255 - color.blue());
	 return color;
 }

 QColor MatrixFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y)const {
	 float returnR = 0;
	 float returnG = 0;
	 float returnB = 0;
	 int radius = mKernel.GetRadius();
	 int size = mKernel.GetSize();
	 int width = _image.width();
	 int height = _image.height();
	 for (int i = -radius; i <= radius; i++) {
		 for( int j = -radius; j <= radius; j++){
			 int index = (i + radius) * size + j + radius;
			 QColor color = _image.pixelColor(Clamp(_x + j, width - 1, 0), Clamp(_y + i, height - 1, 0));
			 returnR += color.red() * mKernel[index];
			 returnG += color.green() * mKernel[index];
			 returnB += color.blue() * mKernel[index];
		 }
	 }
	 return QColor(Clamp(returnR, 255.f, 0.f), Clamp(returnG, 255.f, 0.f), Clamp(returnB, 255.f, 0.f));
 }

 QColor GrayScaleFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y) const{
	 QColor color = _image.pixelColor(_x, _y);
	 float intensity = 0.299f * color.red() + 0.587f * color.green() + 0.114f * color.blue();
	 color.setRgb(intensity, intensity, intensity);
	 return color;
 }

 QColor SepiaFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y) const{
	 QColor  color = _image.pixelColor(_x, _y);
	 float intensity = 0.299f * color.red() + 0.587f * color.green() + 0.114f * color.blue();
	 float k = 50;
	 color.setRgb(Clamp(intensity + 2 * k, 255.f, 0.f), Clamp(intensity + 0.5f * k, 255.f, 0.f), Clamp(intensity - 1 * k, 255.f, 0.f));
	 return color;
 }

 QColor BrightnessFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y) const{
	 QColor color = _image.pixelColor(_x, _y);
	 float k = 50;
	 color.setRgb(Clamp(color.red() + k, 255.f, 0.f), Clamp(color.green() + k, 255.f, 0.f), Clamp(color.blue() + k, 255.f, 0.f));
	 return color;
 }

 QColor SobelFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y) const{
	 float returnRx = 0;
	 float returnGx = 0;
	 float returnBx = 0;
	 float returnRy = 0;
	 float returnGy = 0;
	 float returnBy = 0;
	 int radius = mKernel.GetRadius();
	 int size = mKernel.GetSize();
	 int width = _image.width();
	 int height = _image.height();
	 for (int i = -radius; i <= radius; i++) {
		 for (int j = -radius; j <= radius; j++) {
			 int index_x = (i + radius) * size + j + radius;
			 int index_y = (j + radius) * size + i + radius;
			 QColor color = _image.pixelColor(Clamp(_x + j, width - 1, 0), Clamp(_y + i, height - 1, 0));
			 returnRx += color.red() * mKernel[index_x];
			 returnGx += color.green() * mKernel[index_x];
			 returnBx += color.blue() * mKernel[index_x];
			 returnRy += color.red() * mKernel[index_y];
			 returnGy += color.green() * mKernel[index_y];
			 returnBy += color.blue() * mKernel[index_y];
		 }
	 }
	 float returnR = sqrt(returnRx * returnRx + returnRy * returnRy);
	 float returnG = sqrt(returnGx * returnGx + returnGy * returnGy);
	 float returnB = sqrt(returnBx * returnBx + returnBy * returnBy);

	 return QColor(Clamp(returnR, 255.f, 0.f), Clamp(returnG, 255.f, 0.f), Clamp(returnB, 255.f, 0.f));
 }

 QColor HorizontalWaveFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y) const {
	 int width = _image.width();
	 int x_new = _x + 20 * sin(2 * PI * _x / 30);
	 QColor color = _image.pixelColor(Clamp(x_new, width - 1, 0), _y);
	 return color;
 }

 QColor VerticalWavesFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y) const{
	 int width = _image.width();
	 int x_new = _x + 20 * sin(2 * PI * _y / 60);
	 QColor color = _image.pixelColor(Clamp(x_new, width - 1, 0), _y);
	 return color;
 }

 QColor MedianFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y) const{
	 int size = mKernel.GetSize();
	 int radius = mKernel.GetRadius();
	 int width = _image.width();
	 int height = _image.height();
	 float* returnR = new float[size * size];
	 float* returnG = new float[size * size];
	 float* returnB = new float[size * size];

	 for (int i = -radius; i <= radius; i++) {
		 for (int j = -radius; j <= radius; j++) {
			 int idx = (i + radius) * size + j + radius;
			 QColor color = _image.pixelColor(Clamp(_x + i, width - 1, 0), Clamp(_y + j, height - 1, 0));
			 returnR[idx] = color.red();
			 returnG[idx] = color.green();
			 returnB[idx] = color.blue();
		 }
	 }


	 sort(returnR, returnR + size * size);
	 sort(returnG, returnG + size * size);
	 sort(returnB, returnB + size * size);

	 return QColor(returnR[(int)(size * size / 2)], returnG[(int)(size * size / 2)], returnB[(int)(size * size / 2)]);
 }

 QColor DilationFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y) const{
	 QColor result(0, 0, 0);
	 int size = mKernel.GetSize();
	 int radius = mKernel.GetRadius();
	 int width = _image.width();
	 int height = _image.height();
	 for (int i = -radius; i <= radius; i++) {
		 for (int j = -radius; j <= radius; j++) {
			 int index = (i + radius) * size + j + radius;
			 QColor color = _image.pixelColor(Clamp(_x + j, width - 1, 0), Clamp(_y + i, height - 1, 0));
			 int intensity_color = color.red() + color.green() + color.blue();
			 int intensity_result = result.red() + result.green() + result.blue();
			 if ((mKernel[index] != 0) && (intensity_result < intensity_color)) { result = color; }
		 }
	 }
	 return result;
 }

 QColor ErosionFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y) const {
	 QColor result(255, 255, 255);
	 int size = mKernel.GetSize();
	 int radius = mKernel.GetRadius();
	 int width = _image.width();
	 int height = _image.height();
	 for (int i = -radius; i <= radius; i++) {
		 for (int j = -radius; j <= radius; j++) {
			 int idx = (i + radius) * size + j + radius;
			 QColor color = _image.pixelColor(Clamp(_x + j, width - 1, 0), Clamp(_y + i, height - 1, 0));
			 float intensity_color = color.red() + color.green() + color.blue();
			 float intensity_result = result.red() + result.green() + result.blue();
			 if ((mKernel[idx] != 0) && (intensity_result > intensity_color)) { result = color; }
		 }
	 }
	 return result;
 }
 
 QImage OpeningFilter::Process(const QImage& _image) const{
	 QImage result(_image);
	 int radius = mKernel.GetRadius();
	 DilationFilter dilation(radius);
	 ErosionFilter erosion(radius);
	 result = erosion.Process(_image);
	 result = dilation.Process(result);

	 return result;
 }

 QImage ClosingFilter::Process(const QImage& _image) const{
	 QImage result(_image);
	 int radius = mKernel.GetRadius();
	 DilationFilter dilation(radius);
	 ErosionFilter erosion(radius);
	 result = dilation.Process(_image);
	 result = erosion.Process(result);

	 return result;
 }

 QImage GradFilter::Process(const QImage& _image) const {
	 QImage result(_image);
	 QImage dilation_image(_image);
	 QImage erosion_image(_image);
	 int width = _image.width();
	 int height = _image.height();
	 int radius = mKernel.GetRadius();

	 DilationFilter dilation (radius);
	 dilation_image = dilation.Process(_image);
	 ErosionFilter erosion(radius);
	 erosion_image = erosion.Process(_image);

	 for (int x = 0; x < width; x++) {
		 for (int y = 0; y < height; y++) {
			 QColor erosion_color = erosion_image.pixelColor(x, y);
			 QColor dilation_color = dilation_image.pixelColor(x, y);
			 QColor color(Clamp(dilation_color.red() - erosion_color.red(), 255, 0), Clamp(dilation_color.green() - erosion_color.green(), 255, 0), Clamp(dilation_color.blue() - erosion_color.blue(), 255, 0));
			 result.setPixelColor(x, y, color);
		 }
	 }
	 return result;
 }

 QColor PerfectReflectorFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y) const{
	 QColor color = _image.pixelColor(_x, _y);
	 float colorR = 255.f / maxR;
	 float colorG = 255.f / maxG;
	 float colorB = 255.f / maxB;
	 color.setRgb(Clamp(color.red() * colorR, 255.f, 0.f), Clamp(color.green() * colorG, 255.f, 0.f), Clamp(color.blue() * colorB, 255.f, 0.f));
	 return color;
 }

 QImage PerfectReflectorFilter::Process(const QImage& _image) const{
	 QImage result(_image);
	 int height = _image.height();
	 int width = _image.width();
	 for (int x = 0; x < width; x++) {
		 for (int y = 0; y < height; y++) {
			 QColor color = _image.pixelColor(x, y);
			 if (color.red() > maxR) { maxR = color.red(); }
			 if (color.green() > maxG) { maxG = color.green(); }
			 if (color.blue() > maxB) { maxB = color.blue(); }
		 }
	 }
	 for (int x = 0; x < width; x++) {
		 for (int y = 0; y < height; y++) {
			 QColor color = CalcNewPixelColor(_image, x, y);
			 result.setPixelColor(x, y, color);
		 }
	 }
	 return result;
 }

 QColor GrayWorldFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y) const{
	 QColor color = _image.pixelColor(_x, _y);
	 color.setRgb(Clamp(color.red() * scaleR, 255.f, 0.f), Clamp(color.green() * scaleG, 255.f, 0.f), Clamp(color.blue() * scaleB, 255.f, 0.f));
	 return color;
 }

 QImage GrayWorldFilter::Process(const QImage& _image) const{
	 QImage result(_image);
	 int height = _image.height();
	 int width = _image.width();

	 for (int y = 0; y < height; y++) {
		 for (int x = 0; x < width; x++){
			 QColor color = _image.pixelColor(x, y);
			 sumR += color.red();
			 sumG += color.green();
			 sumB += color.blue();
		 }
	 }

	 float averageR = sumR / (height * width);
	 float averageG = sumG / (height * width);
	 float averageB = sumB / (height * width);
	 float average = (averageR + averageG + averageB) / 3.f;

	 scaleR = average / averageR;
	 scaleG = average / averageG;
	 scaleB = average / averageB;

	 for (int x = 0; x < width; x++) {
		 for (int y = 0; y < height; y++){
			 QColor color = CalcNewPixelColor(_image, x, y);
			 result.setPixelColor(x, y, color);
		 }
	 }
	 return result;
 }

 QColor EmbossingFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y) const{
	 float returnR = 0;
	 float returnG = 0;
	 float returnB = 0;
	 int height = _image.height();
	 int width = _image.width();
	 int size = mKernel.GetSize();
	 int radius = mKernel.GetRadius();
	 int k = 50;

	 for (int i = -radius; i <= radius; i++) {
		 for (int j = -radius; j <= radius; j++) {
			 int index = (i + radius) * size + j + radius;
			 QColor color = _image.pixelColor(Clamp(_x + i, width - 1, 0), Clamp(_y + j, height - 1, 0));
			 returnR += color.red() * mKernel[index];
			 returnG += color.green() * mKernel[index];
			 returnB += color.blue() * mKernel[index];
		 }
	 }

	 float itensity = 0.299f * (returnR + k) + 0.587f * (returnG + k) + 0.114f * (returnB + k);
	 return QColor(Clamp(itensity, 255.f, 0.f), Clamp(itensity, 255.f, 0.f), Clamp(itensity, 255.f, 0.f));
	        
 }

 QColor TurnFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y) const{
	 int widthhalf = _image.width() / 2;
	 int heighthalf = _image.height() / 2;
	 int width = _image.width();
	 int height = _image.height();
	 QColor color(0, 0, 0);
	 int x = (_x - widthhalf) * cos(angle) - (_y - heighthalf) * sin(angle) + widthhalf;
	 int y = (_x - widthhalf) * sin(angle) + (_y - heighthalf) * cos(angle) + heighthalf;
	 if (x < width && x >= 0 && y < height && y >= 0)
		 color = _image.pixelColor(x, y);

	 return color;
 }

 QColor TransferFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y) const {
	 int width = _image.width();
	 QColor color(0, 0, 0);
	 int k = 100;
	 if (_x + k < width)
		color = _image.pixelColor(_x + k, _y);
	 return color;
 }

 QColor GlassFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y) const {
	 int height = _image.height();
	 int width = _image.width();

	 float x = Clamp((_x + (float)((rand() % 2) - 0.5) * 10), width - 1.f, 0.f);
	 float y = Clamp((_y + (float)((rand() % 2) - 0.5) * 10), height - 1.f, 0.f);
	 QColor color = _image.pixelColor(x, y);
	 return color;
 }

 QColor ShharraFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y) const{
	 float returnRx = 0;
	 float returnGx = 0;
	 float returnBx = 0;
	 float returnRy = 0;
	 float returnGy = 0;
	 float returnBy = 0;
	 int radius = mKernel.GetRadius();
	 int size = mKernel.GetSize();
	 int width = _image.width();
	 int height = _image.height();
	 for (int i = -radius; i <= radius; i++) {
		 for (int j = -radius; j <= radius; j++) {
			 int index_x = (i + radius) * size + j + radius;
			 int index_y = (j + radius) * size + i + radius;
			 QColor color = _image.pixelColor(Clamp(_x + j, width - 1, 0), Clamp(_y + i, height - 1, 0));
			 returnRx += color.red() * mKernel[index_x];
			 returnGx += color.green() * mKernel[index_x];
			 returnBx += color.blue() * mKernel[index_x];
			 returnRy += color.red() * mKernel[index_y];
			 returnGy += color.green() * mKernel[index_y];
			 returnBy += color.blue() * mKernel[index_y];
		 }
	 }
	 float returnR = sqrt(returnRx * returnRx + returnRy * returnRy);
	 float returnG = sqrt(returnGx * returnGx + returnGy * returnGy);
	 float returnB = sqrt(returnBx * returnBx + returnBy * returnBy);

	 return QColor(Clamp(returnR, 255.f, 0.f), Clamp(returnG, 255.f, 0.f), Clamp(returnB, 255.f, 0.f));
 }

 QColor PrewittaFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y) const{
	 float returnRx = 0;
	 float returnGx = 0;
	 float returnBx = 0;
	 float returnRy = 0;
	 float returnGy = 0;
	 float returnBy = 0;
	 int radius = mKernel.GetRadius();
	 int size = mKernel.GetSize();
	 int width = _image.width();
	 int height = _image.height();
	 for (int i = -radius; i <= radius; i++) {
		 for (int j = -radius; j <= radius; j++) {
			 int index_x = (i + radius) * size + j + radius;
			 int index_y = (j + radius) * size + i + radius;
			 QColor color = _image.pixelColor(Clamp(_x + j, width - 1, 0), Clamp(_y + i, height - 1, 0));
			 returnRx += color.red() * mKernel[index_x];
			 returnGx += color.green() * mKernel[index_x];
			 returnBx += color.blue() * mKernel[index_x];
			 returnRy += color.red() * mKernel[index_y];
			 returnGy += color.green() * mKernel[index_y];
			 returnBy += color.blue() * mKernel[index_y];
		 }
	 }
	 float returnR = sqrt(returnRx * returnRx + returnRy * returnRy);
	 float returnG = sqrt(returnGx * returnGx + returnGy * returnGy);
	 float returnB = sqrt(returnBx * returnBx + returnBy * returnBy);

	 return QColor(Clamp(returnR, 255.f, 0.f), Clamp(returnG, 255.f, 0.f), Clamp(returnB, 255.f, 0.f));
 }

 QImage BlackHatFilter::Process(const QImage& _image) const{
	 QImage result(_image);
	 int radius = mKernel.GetRadius();
	 int width = _image.width();
	 int height = _image.height();

	 ClosingFilter closing(radius);
	 result = closing.Process(_image);

	 for (int x = 0; x < width; x++) {
		 for (int y = 0; y < height; y++) {
			 QColor image_color = _image.pixelColor(x, y);
			 QColor result_color = result.pixelColor(x, y);
			 QColor color(Clamp(result_color.red() - image_color.red(), 255, 0), Clamp(result_color.green() - image_color.green(), 255, 0), Clamp(result_color.blue() - image_color.blue(), 255, 0));
			 result.setPixelColor(x, y, color);
		 }
	 }
	 return result;
 }

 QImage TopHatFilter::Process(const QImage& _image) const{
	 QImage result(_image);
	 int height = _image.height();
	 int width = _image.width();
	 int radius = mKernel.GetRadius();

	 OpeningFilter opening(radius);
	 result = opening.Process(_image);

	 for (int y = 0; y < height; y++) {
		 for (int x = 0; x < width; x++){
			 QColor image_color = _image.pixelColor(x, y);
			 QColor result_color = result.pixelColor(x, y);
			 QColor color(Clamp(image_color.red() - result_color.red(), 255, 0), Clamp(image_color.green() - result_color.green(), 255, 0), Clamp(image_color.blue() - result_color.blue(), 255, 0));
			 result.setPixelColor(x, y, color);
		 }
	 }
	 return result;
 }

 QColor LinearCorrectionFilter::CalcNewPixelColor(const QImage& _image, int _x, int _y) const{
	 QColor color = _image.pixelColor(_x, _y);
	 float red = (color.red() - minR) * (255.f / (maxR - minR));
	 float green = (color.green() - minG) * (255.f / (maxG - minG));
	 float blue = (color.blue() - minB) * (255.f / (maxB - minB));
	 color.setRgb(Clamp(red, 255.f, 0.f), Clamp(green, 255.f, 0.f), Clamp(blue, 255.f, 0.f));
	 return color;
 }

 QImage LinearCorrectionFilter::Process(const QImage& _image) const{
	 QImage result(_image);
	 int height = result.height();
	 int width = result.width();

	 for (int y = 0; y < height; y++) {
		 for (int x = 0; x < width; x++) {
			 QColor color = _image.pixelColor(x, y);
			 if (color.red() > maxR) { maxR = color.red(); }
			 if (color.green() > maxG) { maxG = color.green(); }
			 if (color.blue() > maxB) { maxB = color.blue(); }

			 if (color.red() < minR) { minR = color.red(); }
			 if (color.green() < minG) { minG = color.green(); }
			 if (color.blue() < minB) { minB = color.blue(); }
		 }
	 }

	 for (int y = 0; y < height; y++) {
		 for (int x = 0; x < width; x++){
			 QColor color = CalcNewPixelColor(_image, x, y);
			 result.setPixelColor(x, y, color);
		 }
	 }
	 return result;
 }
