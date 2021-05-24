#ifndef _SHADERWIDGET_H_
#define _SHADERWIDGET_H_

#include <QKeyEvent>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <iostream>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_3_Core>
#include <QFileInfo>
#include <qmessagebox.h>
using namespace std;
class ShaderWidget : public QOpenGLWidget{
	Q_OBJECT
	QOpenGLShaderProgram m_program;//
	GLfloat* vert_data;
	int vert_data_location;

	float position_x, position_y, position_z;
	int view; // 0 - z, 1 - x, 2 - -z, 3 - -x

	QVector3D getView() const;
	QVector3D getSide() const;

	struct Sphere {
		QVector3D position;
		float radius;
		QVector3D color;
		int material_idx;
	};

	vector<Sphere> all_spheres;

	QOpenGLFunctions_4_3_Core* functions;
	GLuint ssbo = 0;
protected:
	void initializeGL() override;
	void resizeGL(int nWidth, int nHeight) override;
	void paintGL() override;

public:
	ShaderWidget(QWidget* parent = 0);
	~ShaderWidget();

public slots:
	void keyPressEvent(QKeyEvent* _event) override;
};

#endif