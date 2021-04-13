#include <QImage>
#include <iostream>
#include "Filter.h"
using namespace std;

int main(int length, char* arr[]) {
	string str;
	QImage image;
	for (int item = 0; item < length; item++) {
		if (!strcmp(arr[item], "-p") && (item + 1 < length)) {
			str = arr[item + 1];
		}
	}

	image.load(QString(str.c_str()));
	image.save("images/simba.png");
	
	cout << "--------------------Matrix filtes--------------------" << endl;

	BlurFilter blur;
	clock_t start = clock();
	blur.Process(image).save("images/simbaBLUR.png");
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaBLUR: %f seconds\n", seconds);

	GaussianFilter gaussian(2);
	start = clock();
	gaussian.Process(image).save("images/simbaGAUSSIAN.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaGAUSSIAN: %f seconds\n", seconds);

	SobelFilter sobel;
	start = clock();
	sobel.Process(image).save("images/simbaSOBEL.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaSOBEL: %f seconds\n", seconds);

	SharpnessFilter sharpness;
	start = clock();
	sharpness.Process(image).save("images/simbaSHARPNESS.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaSHARPNESS: %f seconds\n", seconds);

	MedianFilter median(2);
	start = clock();
	median.Process(image).save("images/simbaMEDIAN.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaMEDIAN: %f seconds\n", seconds);

	DilationFilter dilation;
	start = clock();
	dilation.Process(image).save("images/simbaDILATION.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaDILATION: %f seconds\n", seconds);

	ErosionFilter erosion;
	start = clock();
	erosion.Process(image).save("images/simbaEROSIN.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaEROSIN: %f seconds\n", seconds);

	OpeningFilter opening;
	start = clock();
	opening.Process(image).save("images/simbaOPENING.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaOPENING: %f seconds\n", seconds);

	ClosingFilter closing;
	start = clock();
	closing.Process(image).save("images/simbaCLOSING.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaCLOSING: %f seconds\n", seconds);

	GradFilter grad;
	start = clock();
	grad.Process(image).save("images/simbaGRAD.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaGRAD: %f seconds\n", seconds);

	EmbossingFilter embossing;
	start = clock();
	embossing.Process(image).save("images/simbaEMBOSSING.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaEMBOSSING: %f seconds\n", seconds);

	AdditionalSharpnessFilter additionalsharpness;
	start = clock();
	additionalsharpness.Process(image).save("images/simbaADDITIONALSHARPNESS.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaADDITIONALSHARPNESS: %f seconds\n", seconds);

	ShharraFilter shharra;
	start = clock();
	shharra.Process(image).save("images/simbaSHHARRA.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaSHHARRA: %f seconds\n", seconds);

	PrewittaFilter prewitta;
	start = clock();
	prewitta.Process(image).save("images/simbaPREWITTA.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaPREWITTA: %f seconds\n", seconds);

	MotionBlurFilter motionblur(2);
	start = clock();
	motionblur.Process(image).save("images/simbaMOTIONBLUR.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaMOTIONBLUR: %f seconds\n", seconds);

	BlackHatFilter blackhat;
	start = clock();
	blackhat.Process(image).save("images/simbaBLACKHAT.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaBLACKHAT: %f seconds\n", seconds);

	TopHatFilter tophat;
	start = clock();
	tophat.Process(image).save("images/simbaTOPHAT.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaTOPHAT: %f seconds\n", seconds);

	cout << "--------------------Pixel filtes--------------------" << endl;
	 
	InvertFilter invert;
	start = clock();
	invert.Process(image).save("images/simbaINVERT.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaINVERT: %f seconds\n", seconds);

	GrayScaleFilter grayscale;
	start = clock();
	grayscale.Process(image).save("images/simbaGRAYSCALE.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaGRAYSCALE: %f seconds\n", seconds);

	SepiaFilter sepia;
	start = clock();
	sepia.Process(image).save("images/simbaSEPIA.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaSEPIA: %f seconds\n", seconds);

	BrightnessFilter brightness;
	start = clock();
	brightness.Process(image).save("images/simbaBRIGHTNESS.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaBRIGHTNESS: %f seconds\n", seconds);

	HorizontalWaveFilter horizontalwave;
	start = clock();
	horizontalwave.Process(image).save("images/simbaHORIZONTALWAVE.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaHORIZONTALWAVE: %f seconds\n", seconds);

	VerticalWavesFilter verticalwaves;
	start = clock();
	verticalwaves.Process(image).save("images/simbaVERTICALWAVE.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaVERTICALWAVE: %f seconds\n", seconds);

	PerfectReflectorFilter perfectreflector;
	start = clock();
	perfectreflector.Process(image).save("images/simbaPERFECTREFLECTOR.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaPERFECTREFLECTOR: %f seconds\n", seconds);

	GrayWorldFilter grayworld;
	start = clock();
	grayworld.Process(image).save("images/simbaGRAYWORLD.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaGRAYWORLD: %f seconds\n", seconds);

	TurnFilter turn;
	start = clock();
	turn.Process(image).save("images/simbaTURN.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaTURN: %f seconds\n", seconds);

	TransferFilter transfer;
	start = clock();
	transfer.Process(image).save("images/simbaTRANSFER.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaTRANSFER: %f seconds\n", seconds);

	GlassFilter glass;
	start = clock();
	glass.Process(image).save("images/simbaGLASS.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("simbaGLASS: %f seconds\n", seconds);

	LinearCorrectionFilter linearcorrection;
	start = clock();
	linearcorrection.Process(image).save("images/simbaLINEARCORRECTION.png");
	end = clock();
	seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("sumbaLINEARCORRECTION: %f seconds\n", seconds);
}
