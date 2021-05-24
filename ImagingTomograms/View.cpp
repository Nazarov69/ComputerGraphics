#include "View.h"
#include "MinMax.h"
#include "qfiledialog.h"

template <class type>
type View::Clamp(type _value, type _min, type _max) {
	if (_value > _max) return _max;
	else if (_value < _min) return _min;
	return _value;
}

void View::initializeGL() {
	glClearColor(255, 255, 255, 1);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGenTextures(1, &VBOtexture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void View::resizeGL(int _width, int _height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	switch (axis) {
	case Z:
		glOrtho(0.0f, width - 1, 0.0f, height - 1, -1.0f, 1.0f);
		break;
	case Y:
		glOrtho(0.0f, width - 1, 0.0f, depth - 1, -1.0f, 1.0f);
		break;
	case X:
		glOrtho(0.0f, height - 1, 0.0f, depth - 1, -1.0f, 1.0f);
		break;
	}

	glViewport(0, 0, (GLsizei)_width, (GLsizei)_height);
	update();
}

void View::paintGL() {
	qDebug() << "repaint" << visualization_state;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (visualization_state){
	case VISUALIZATION_QUADS:
		this->setWindowTitle("Visualization Quads");
		VisualizationQuads();
		break;

	case VISUALIZATION_QUADSTRIP:
		this->setWindowTitle("Visualization QuadStrip");
		VisualizationQuadStrip();
		break;

	case VISUALIZATION_TEXTURE:
		this->setWindowTitle("Visualization Texture");
		VisualizationTexture();
		break;
	}
}

float View::TransferFunction(short value){
	float c = (value - data.GetMin()) * 1.f / (data.GetMax() - data.GetMin());
	return c;
}

void View::VisualizationQuads() {
	float c;

	switch (axis) {
	case Z:
		for (int y = 0; y < (height - 1); y++) {
			for (int x = 0; x < (width - 1); x++) {
				glBegin(GL_QUADS);

				c = TransferFunction(data[number_layer * width * height + y * width + x]);
				glColor3f(c, c, c);
				glVertex2i(x, y);

				c = TransferFunction(data[number_layer * width * height + (y + 1) * width + x]);
				glColor3f(c, c, c);
				glVertex2i(x, (y + 1));

				c = TransferFunction(data[number_layer * width * height + (y + 1) * width + x + 1]);
				glColor3f(c, c, c);
				glVertex2i((x + 1), (y + 1));

				c = TransferFunction(data[number_layer * width * height + y * width + x + 1]);
				glColor3f(c, c, c);
				glVertex2i((x + 1), y);
				glEnd();
			}
		}
		break;

	case Y:
		for (int z = 0; z < (depth - 1); z++)
			for (int x = 0; x < (width - 1); x++) {
				glBegin(GL_QUADS);

				c = TransferFunction(data[z * width * height + number_layer * width + x]);
				glColor3f(c, c, c);
				glVertex2i(x, z);

				c = TransferFunction(data[(z + 1) * width * height + number_layer * width + x]);
				glColor3f(c, c, c);
				glVertex2i(x, (z + 1));

				c = TransferFunction(data[(z + 1) * width * height + number_layer * width + x + 1]);
				glColor3f(c, c, c);
				glVertex2i((x + 1), (z + 1));

				c = TransferFunction(data[z * width * height + number_layer * width + x + 1]);
				glColor3f(c, c, c);
				glVertex2i((x + 1), z);
				glEnd();
			}
		break;
	case X:
		for (int z = 0; z < (depth - 1); z++)
			for (int y = 0; y < (height - 1); y++) {
				glBegin(GL_QUADS);

				c = TransferFunction(data[z * width * height + y * width + number_layer]);
				glColor3f(c, c, c);
				glVertex2i(y, z);

				c = TransferFunction(data[(z + 1) * width * height + y * width + number_layer]);
				glColor3f(c, c, c);
				glVertex2i(y, (z + 1));

				c = TransferFunction(data[(z + 1) * width * height + (y + 1) * width + number_layer]);
				glColor3f(c, c, c);
				glVertex2i((y + 1), (z + 1));

				c = TransferFunction(data[z * width * height + (y + 1) * width + number_layer]);
				glColor3f(c, c, c);
				glVertex2i((y + 1), z);
				glEnd();
			}
		break;
	}
}

void View::keyPressEvent(QKeyEvent* _event) {
	if (_event->nativeVirtualKey() == Qt::Key_W) {
		Up();
		ChangeLayer();
	}
	else if (_event->nativeVirtualKey() == Qt::Key_S) {
		Down();
		ChangeLayer();
	}
	else if (_event->nativeVirtualKey() == Qt::Key_D) {
		visualization_state = static_cast<Visualization>((visualization_state + 1) % 3);

		if (visualization_state == VISUALIZATION_TEXTURE) {
			glEnable(GL_TEXTURE_2D);
			genTextureImage();
			Load2DTexture();
		}
		else
			glDisable(GL_TEXTURE_2D);
	}
	else if (_event->nativeVirtualKey() == Qt::Key_A) {
		visualization_state = static_cast<Visualization>((visualization_state + 2) % 3);

		if (visualization_state == VISUALIZATION_TEXTURE) {
			glEnable(GL_TEXTURE_2D);
			genTextureImage();
			Load2DTexture();
		}
		else
			glDisable(GL_TEXTURE_2D);
	}
	else if (_event->nativeVirtualKey() == Qt::Key_R) {
		axis = static_cast<Axis>((axis + 2) % 3);
		number_layer = 0;

		switch (axis) {
		case Z:
			resize(Clamp(width, WIDTH, HEIGHT), Clamp(height, WIDTH, HEIGHT));
			break;

		case Y:
			resize(Clamp(width, WIDTH, HEIGHT), Clamp(depth, WIDTH, HEIGHT));
			break;

		case X:
			resize(Clamp(height, WIDTH, HEIGHT), Clamp(depth, WIDTH, HEIGHT));
			break;
		}

		if (visualization_state == VISUALIZATION_TEXTURE) {
			genTextureImage();
			Load2DTexture();
		}
	}
	else if (_event->nativeVirtualKey() == Qt::Key_F) {
		number_layer = 0;
		ChangeLayer();
		QString path = DialogFile();
		LoadData(path);
	}
	else if (_event->nativeVirtualKey() == Qt::Key_T) {
		MinMax* change = new MinMax;
		change->exec();

		data.SetMax(change->Max());
		max = data.GetMax();
		data.SetMin(change->Min());
		min = data.GetMin();

		if (visualization_state == VISUALIZATION_TEXTURE) {
			genTextureImage();
			Load2DTexture();
		}

		delete change;
	}

	update();
};

void View::Load2DTexture() {
	glBindTexture(GL_TEXTURE_2D, VBOtexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage.width(), textureImage.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, textureImage.bits());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
};

void View::genTextureImage() {
	float c;

	switch (axis) {
	case Z:
		textureImage = QImage(width, height, QImage::Format_RGB32);
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				c = Clamp((int)(255 * TransferFunction(data[number_layer * width * height + y * width + x])), 0, 255);
				textureImage.setPixelColor(x, y, QColor(c, c, c));
			}
		}
		break;

	case Y:
		textureImage = QImage(width, depth, QImage::Format_RGB32);
		for (int z = 0; z < depth; z++) {
			for (int x = 0; x < width; x++) {
				c = Clamp((int)(255 * TransferFunction(data[z * width * height + number_layer * width + x])), 0, 255);
				textureImage.setPixelColor(x, z, QColor(c, c, c));
			}
		}
		break;

	case X:
		textureImage = QImage(height, depth, QImage::Format_RGB32);
		for (int z = 0; z < depth; z++) {
			for (int y = 0; y < height; y++) {
				c = Clamp((int)(255 * TransferFunction(data[z * width * height + y * width + number_layer])), 0, 255);
				textureImage.setPixelColor(y, z, QColor(c, c, c));
			}
		}
		break;
	}
};

void View::VisualizationTexture() {
	genTextureImage();
	Load2DTexture();

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glColor3i(255, 255, 255);

	glTexCoord2f(0, 0);
	glVertex2i(0, 0);

	switch (axis) {
	case Z:
		glTexCoord2f(0, 1);
		glVertex2i(0, height);

		glTexCoord2f(1, 1);
		glVertex2i(width, height);

		glTexCoord2f(1, 0);
		glVertex2i(width, 0);
		break;

	case Y:
		glTexCoord2f(0, 1);
		glVertex2i(0, depth);

		glTexCoord2f(1, 1);
		glVertex2i(width, depth);

		glTexCoord2f(1, 0);
		glVertex2i(width, 0);
		break;

	case X:
		glTexCoord2f(0, 1);
		glVertex2i(0, depth);

		glTexCoord2f(1, 1);
		glVertex2i(height, depth);

		glTexCoord2f(1, 0);
		glVertex2i(height, 0);
		break;
	}

	glEnd();
	glDisable(GL_TEXTURE_2D);
};

void View::VisualizationQuadStrip(){
	float c;

	switch (axis){
	case Z:
		for (int y = 0; y < (height - 1); y++){
			glBegin(GL_QUAD_STRIP);
			for (int x = 0; x < width; x++){
				c = TransferFunction(data[number_layer * width * height + y * width + x]);
				glColor3f(c, c, c);
				glVertex2i(x, y);

				c = TransferFunction(data[number_layer * width * height + (y + 1) * width + x]);
				glColor3f(c, c, c);
				glVertex2i(x, (y + 1));
			}

			glEnd();
		}
		break;

	case Y:
		for (int z = 0; z < (depth - 1); z++){
			glBegin(GL_QUAD_STRIP);
			for (int x = 0; x < width; x++){
				c = TransferFunction(data[z * width * height + number_layer * width + x]);
				glColor3f(c, c, c);
				glVertex2i(x, z);

				c = TransferFunction(data[(z + 1) * width * height + number_layer * width + x]);
				glColor3f(c, c, c);
				glVertex2i(x, (z + 1));
			}

			glEnd();
		}
		break;

	case X:
		for (int z = 0; z < (depth - 1); z++){
			glBegin(GL_QUAD_STRIP);
			for (int y = 0; y < height; y++){
				c = TransferFunction(data[z * width * height + y * width + number_layer]);
				glColor3f(c, c, c);
				glVertex2i(y, z);

				c = TransferFunction(data[(z + 1) * width * height + y * width + number_layer]);
				glColor3f(c, c, c);
				glVertex2i(y, (z + 1));
			}

			glEnd();
		}
		break;
	}
};

void View::LoadData(QString _path){
	data.ReadFile(_path);
	number_layer = 0;
	width = data.GetWidth();
	height = data.GetHeight();
	depth = data.GetDepth();
	min = data.GetMin();
	max = data.GetMax();

	resize(Clamp(width, WIDTH, HEIGHT), Clamp(height, WIDTH, HEIGHT));

	update();
};

QString View::DialogFile(){
	QString path = QFileDialog::getOpenFileName(this, "Choose binary file", "", "*.bin");
	return path;
};

void View::Up(){
	switch (axis){
	case Z:
		if (number_layer + 1 < data.GetDepth()) number_layer++;
		break;

	case Y:
		if (number_layer + 1 < data.GetHeight()) number_layer++;
		break;

	case X:
		if (number_layer + 1 < data.GetWidth()) number_layer++;
		break;
	}
	update();
};

void View::Down(){
	if (number_layer - 1 >= 0) number_layer--;
	update();
};

void View::ChangeLayer(){
	if (visualization_state == VISUALIZATION_TEXTURE){
		genTextureImage();
		Load2DTexture();
	}
};

View::View(QWidget* parent) : QOpenGLWidget(parent){
	number_layer = 0;
	visualization_state = VISUALIZATION_QUADS;
	axis = Z;
	resizeGL(WIDTH, HEIGHT);
	setFocus();
	this->setWindowIcon(QIcon("resources/heart.jpg"));
};