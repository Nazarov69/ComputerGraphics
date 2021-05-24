#include "Data.h"

Data::Data() {
	data_w = 0; data_h = 0; data_d = 0;
	voxel_x = 0.f; voxel_y = 0.f; voxel_z = 0.f;
	min = 0; max = 0;

	value = NULL;
}

Data::~Data() {
	data_w = 0; data_h = 0; data_d = 0;
	voxel_x = 0.f; voxel_y = 0.f; voxel_z = 0.f;
	min = 0; max = 0;

	if (value != NULL) {
		delete[] value;
		value = NULL;
	}
}

void Data::SetMinMax() {
	min = value[0];
	max = value[0];

	int i = 0;
	while (i < data_w * data_h * data_d) {
		if (min > value[i]) min = value[i];
		if (max < value[i]) max = value[i];
		i++;
	}
}

int Data::ReadFile(QString file_name) {
	ifstream file;
	file.open(file_name.toStdString(), ios::binary | ios::in);

	if (!file.is_open()) { file.close(); return -1; }

	file.read((char*)&data_w, sizeof(int));
	file.read((char*)&data_h, sizeof(int));
	file.read((char*)&data_d, sizeof(int));

	if (data_w == 0 || data_h == 0 || data_d == 0) { file.close(); return -1; }

	file.read((char*)&voxel_x, sizeof(float));
	file.read((char*)&voxel_y, sizeof(float));
	file.read((char*)&voxel_z, sizeof(float));

	if (value != NULL) { delete[] value; }
	value = new short[data_w * data_h * data_d];

	int i = 0;
	while (i < data_w * data_h * data_d) {
		file.read((char*)(value + i), sizeof(short));
		i++;
	}
	file.close();

	SetMinMax();
	return 0;
}

