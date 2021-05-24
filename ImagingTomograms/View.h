#pragma once
#pragma comment (lib, "opengl32.lib")

#include "Data.h"
#include <iostream>
#include <QDebug>
#include <QKeyEvent>
#include <QtWidgets/QOpenGLWidget>
#include <QtOpenGL/QGLFunctions>


static const int HEIGHT = 1000;
static const int WIDTH = 250;

enum Visualization {
	VISUALIZATION_QUADS,
	VISUALIZATION_QUADSTRIP,
	VISUALIZATION_TEXTURE
};

enum Axis {
	X,
	Y,
	Z
};

class View : public QOpenGLWidget {
	Q_OBJECT
private:
	void VisualizationQuads();
	void VisualizationTexture();
	void VisualizationQuadStrip();

	float TransferFunction(short value);
	
	Visualization visualization_state;
	Axis axis;
	
public slots:
	void keyPressEvent(QKeyEvent* _event) override;

private:
	void Up();
	void Down();

	void ChangeLayer();
	
	template <class type>
	type Clamp(type _value, type _min, type _max);


	QString DialogFile();

	GLuint VBOtexture;
	void Load2DTexture();

	QImage textureImage;
	void genTextureImage();

	Data data;
	int number_layer;

	int width, height, depth;
	short min, max;

protected:
	void initializeGL() override;
	void resizeGL(int _width, int _height) override;
	void paintGL() override;

public:
	View(QWidget* parent = Q_NULLPTR);
	~View() {};

	void LoadData(QString _path);
};
