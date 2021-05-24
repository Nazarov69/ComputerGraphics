#pragma once

#include <cstdio>
#include <fstream>
#include <qstring.h>
#include <iostream>

using namespace std;

class Data {
	int data_w, data_h, data_d;
	float voxel_x, voxel_y, voxel_z;
	short* value;
	short min, max;
public:
	Data();
	~Data();

	short GetMin() { return min; }
	short GetMax() { return max; }
	void SetMinMax();

	void SetMin(short value) { min = value; }
	void SetMax(short value) { max = value; }

	int GetWidth() { return data_w; }
	int GetHeight() { return data_h; }
	int GetDepth() { return data_d; }

	int ReadFile(QString file_name);
	short& operator[] (const int index) { return value[index]; }
};