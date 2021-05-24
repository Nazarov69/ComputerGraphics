#include "ShaderWidget.h"

ShaderWidget::ShaderWidget(QWidget* parent) : QOpenGLWidget(parent) {
    vert_data = new GLfloat[12]{ -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f };

    position_x = 0.0f;
    position_y = 0.0f;
    position_z = -10.0f;
    vert_data_location = 0;
    view = 0;
}

ShaderWidget::~ShaderWidget() { if(vert_data!= NULL) delete[] vert_data; }

QVector3D ShaderWidget::getView() const{
    switch (view){
    case 0:
        return QVector3D(0.0, 0.0, 1.0);
    case 1:
        return QVector3D(1.0, 0.0, 0.0);
    case 2:
        return QVector3D(0.0, 0.0, -1.0);
    case 3:
        return QVector3D(-1.0, 0.0, 0.0);
    }
}

QVector3D ShaderWidget::getSide() const{
    switch (view){
    case 0:
        return QVector3D(1.0, 0.0, 0.0);
    case 1:
        return QVector3D(0.0, 0.0, -1.0);
    case 2:
        return QVector3D(-1.0, 0.0, 0.0);
    case 3:
        return QVector3D(0.0, 0.0, 1.0);
    }
}

void ShaderWidget::initializeGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    QOpenGLShader vShader(QOpenGLShader::Vertex);
    vShader.compileSourceFile("raytracing.vert");

    QOpenGLShader fShader(QOpenGLShader::Fragment);
    fShader.compileSourceFile("raytracing.frag");

    m_program.addShader(&vShader);
    m_program.addShader(&fShader);

    if (!m_program.link()) {
        QMessageBox::warning(this, "Warning", "Error bind programm shader!");
        return;
    }

    vert_data_location = m_program.attributeLocation("vertex");

    qDebug() << QString("Log programm");
    qDebug() << m_program.log();


    if (!m_program.bind()) {
        QMessageBox::warning(this, "Warning", "Error bind programm shader!");
        return;
    }

    m_program.setUniformValue("camera.position", QVector3D(position_x, position_y, position_z));
    m_program.setUniformValue("camera.view", getView());
    m_program.setUniformValue("camera.up", QVector3D(0.0, 1.0, 0.0));
    m_program.setUniformValue("camera.side", getSide());

    m_program.setUniformValue("spherein[0].center", QVector3D(0.0, 1.0, 0.0));
    m_program.setUniformValue("spherein[0].color", QVector3D(1.0, 0.0, 1.0));
    m_program.setUniformValue("spherein[0].radius", 1.0f);
    m_program.setUniformValue("spherein[1].center", QVector3D(3.0, -3.0, 0.0));
    m_program.setUniformValue("spherein[1].color", QVector3D(0.0, 0.0, 1.0));
    m_program.setUniformValue("spherein[1].radius", 2.0f);

    // left
    m_program.setUniformValue("trianglein[0].v1", QVector3D(-5.0, -5.0, -5.0));
    m_program.setUniformValue("trianglein[0].v2", QVector3D(-5.0, 5.0, -5.0));
    m_program.setUniformValue("trianglein[0].v3", QVector3D(-5.0, 5.0, 5.0));
    m_program.setUniformValue("trianglein[0].color", QVector3D(1.0, 1.0, 0.0));
    m_program.setUniformValue("trianglein[1].v1", QVector3D(-5.0, -5.0, -5.0));
    m_program.setUniformValue("trianglein[1].v2", QVector3D(-5.0, 5.0, 5.0));
    m_program.setUniformValue("trianglein[1].v3", QVector3D(-5.0, -5.0, 5.0));
    m_program.setUniformValue("trianglein[1].color", QVector3D(1.0, 1.0, 0.0));

    // right
    m_program.setUniformValue("trianglein[2].v1", QVector3D(5.0, -5.0, -5.0));
    m_program.setUniformValue("trianglein[2].v2", QVector3D(5.0, 5.0, 5.0));
    m_program.setUniformValue("trianglein[2].v3", QVector3D(5.0, 5.0, -5.0));
    m_program.setUniformValue("trianglein[2].color", QVector3D(1.0, 1.0, 0.0));
    m_program.setUniformValue("trianglein[3].v1", QVector3D(5.0, -5.0, -5.0));
    m_program.setUniformValue("trianglein[3].v2", QVector3D(5.0, -5.0, 5.0));
    m_program.setUniformValue("trianglein[3].v3", QVector3D(5.0, 5.0, 5.0));
    m_program.setUniformValue("trianglein[3].color", QVector3D(1.0, 1.0, 0.0));

    // front
    m_program.setUniformValue("trianglein[4].v1", QVector3D(-5.0, -5.0, 5.0));
    m_program.setUniformValue("trianglein[4].v2", QVector3D(-5.0, 5.0, 5.0));
    m_program.setUniformValue("trianglein[4].v3", QVector3D(5.0, -5.0, 5.0));
    m_program.setUniformValue("trianglein[4].color", QVector3D(1.0, 1.0, 0.0));
    m_program.setUniformValue("trianglein[5].v1", QVector3D(5.0, 5.0, 5.0));
    m_program.setUniformValue("trianglein[5].v2", QVector3D(5.0, -5.0, 5.0));
    m_program.setUniformValue("trianglein[5].v3", QVector3D(-5.0, 5.0, 5.0));
    m_program.setUniformValue("trianglein[5].color", QVector3D(1.0, 1.0, 0.0));

    // up
    m_program.setUniformValue("trianglein[6].v1", QVector3D(-5.0, 5.0, -5.0));
    m_program.setUniformValue("trianglein[6].v2", QVector3D(5.0, 5.0, -5.0));
    m_program.setUniformValue("trianglein[6].v3", QVector3D(-5.0, 5.0, 5.0));
    m_program.setUniformValue("trianglein[6].color", QVector3D(0.0, 1.0, 0.0));
    m_program.setUniformValue("trianglein[7].v1", QVector3D(5.0, 5.0, 5.0));
    m_program.setUniformValue("trianglein[7].v2", QVector3D(-5.0, 5.0, 5.0));
    m_program.setUniformValue("trianglein[7].v3", QVector3D(5.0, 5.0, -5.0));
    m_program.setUniformValue("trianglein[7].color", QVector3D(0.0, 1.0, 0.0));

    // down
    m_program.setUniformValue("trianglein[8].v1", QVector3D(-5.0, -5.0, -5.0));
    m_program.setUniformValue("trianglein[8].v2", QVector3D(-5.0, -5.0, 5.0));
    m_program.setUniformValue("trianglein[8].v3", QVector3D(5.0, -5.0, -5.0));
    m_program.setUniformValue("trianglein[8].color", QVector3D(0.0, 1.0, 0.0));
    m_program.setUniformValue("trianglein[9].v1", QVector3D(5.0, -5.0, 5.0));
    m_program.setUniformValue("trianglein[9].v2", QVector3D(5.0, -5.0, -5.0));
    m_program.setUniformValue("trianglein[9].v3", QVector3D(-5.0, -5.0, 5.0));
    m_program.setUniformValue("trianglein[9].color", QVector3D(0.0, 1.0, 0.0));

    // tetr
    m_program.setUniformValue("trianglein[10].v1", QVector3D(-5.0, -5.0, 5.0));
    m_program.setUniformValue("trianglein[10].v2", QVector3D(-1.0, -5.0, 5.0));
    m_program.setUniformValue("trianglein[10].v3", QVector3D(-3.0, -5.0, 1.54));
    m_program.setUniformValue("trianglein[10].color", QVector3D(0.0, 1.0, 1.0));
    m_program.setUniformValue("trianglein[11].v1", QVector3D(-5.0, -5.0, 5.0));
    m_program.setUniformValue("trianglein[11].v2", QVector3D(-1.0, -5.0, 5.0));
    m_program.setUniformValue("trianglein[11].v3", QVector3D(-3.0, -1.73, 3.85));
    m_program.setUniformValue("trianglein[11].color", QVector3D(0.0, 1.0, 1.0));
    m_program.setUniformValue("trianglein[12].v1", QVector3D(-5.0, -5.0, 5.0));
    m_program.setUniformValue("trianglein[12].v2", QVector3D(-3.0, -5.0, 1.54));
    m_program.setUniformValue("trianglein[12].v3", QVector3D(-3.0, -1.73, 3.85));
    m_program.setUniformValue("trianglein[12].color", QVector3D(0.0, 1.0, 1.0));
    m_program.setUniformValue("trianglein[13].v1", QVector3D(-1.0, -5.0, 5.0));
    m_program.setUniformValue("trianglein[13].v2", QVector3D(-3.0, -5.0, 1.54));
    m_program.setUniformValue("trianglein[13].v3", QVector3D(-3.0, -1.73, 3.85));
    m_program.setUniformValue("trianglein[13].color", QVector3D(0.0, 1.0, 1.0));

    m_program.setUniformValue("scale", QVector2D(width(), height()));

    m_program.release();

    all_spheres.push_back(Sphere{ QVector3D(-2, 1, -1), 2, QVector3D(1, 0.0, 0), 0 });
    all_spheres.push_back(Sphere{ QVector3D(0.2, 1, -3), 1.5, QVector3D(1, 1, 0.0), 0 });
    all_spheres.push_back(Sphere{ QVector3D(0, 0, -5), 1, QVector3D(0.0, 1.0, 0.0), 0 });
    all_spheres.push_back(Sphere{ QVector3D(1, 0, -6), 0.7, QVector3D(0.0, 1.0, 1.0), 0});
    all_spheres.push_back(Sphere{ QVector3D(1.2, 0.4, -7), 0.3, QVector3D(0.0, 0.0, 1.0), 0 });

    functions = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    functions->glGenBuffers(1, &ssbo);
    functions->glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    functions->glBufferData(GL_SHADER_STORAGE_BUFFER, all_spheres.size() * sizeof(Sphere), all_spheres.data(), GL_DYNAMIC_COPY);
    functions->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
}

void ShaderWidget::resizeGL(int _width, int _height){
    glViewport(0, 0, _width, _height);

    if (!m_program.bind()){
        QMessageBox::warning(this, "Warning", "Error bind programm shader!");
        return;
    }

    m_program.setUniformValue("scale", QVector2D(width(), height()));
    m_program.release();
}

void ShaderWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    if (!m_program.bind()) return;

    m_program.enableAttributeArray(vert_data_location);
    m_program.setAttributeArray(vert_data_location, vert_data, 3);

    glDrawArrays(GL_QUADS, 0, 4);

    m_program.disableAttributeArray(vert_data_location);

    m_program.release();
}

void ShaderWidget::keyPressEvent(QKeyEvent* _event){
    if (_event->nativeVirtualKey() == Qt::Key_W){
        switch (view){
        case 0:
            position_z++;
            break;
        case 1:
            position_x++;
            break;
        case 2:
            position_z--;
            break;
        case 3:
            position_x--;
            break;
        }
    }
    else if (_event->nativeVirtualKey() == Qt::Key_S){
        switch (view){
        case 0:
            position_z--;
            break;
        case 1:
            position_x--;
            break;
        case 2:
            position_z++;
            break;
        case 3:
            position_x++;
            break;
        }
    }
    else if (_event->nativeVirtualKey() == Qt::Key_D){
        switch (view){
        case 0:
            position_x++;
            break;
        case 1:
            position_z--;
            break;
        case 2:
            position_x--;
            break;
        case 3:
            position_z++;
            break;
        }
    }
    else if (_event->nativeVirtualKey() == Qt::Key_A){
        switch (view){
        case 0:
            position_x--;
            break;
        case 1:
            position_z++;
            break;
        case 2:
            position_x++;
            break;
        case 3:
            position_z--;
            break;
        }
    }
    else if (_event->nativeVirtualKey() == Qt::Key_I) { position_y++; }
    else if (_event->nativeVirtualKey() == Qt::Key_K) { position_y--; }
    if (_event->nativeVirtualKey() == Qt::Key_J) { view = (view + 3) % 4; }
    else if (_event->nativeVirtualKey() == Qt::Key_L) { view = (view + 1) % 4; }

    if (!m_program.bind()){
        QMessageBox::warning(this, "Warning", "Error bind programm shader!");
        return;
    }

    m_program.setUniformValue("camera.position", QVector3D(position_x, position_y, position_z));
    m_program.setUniformValue("camera.view", getView());
    m_program.setUniformValue("camera.side", getSide());
    m_program.release();

    update();
}