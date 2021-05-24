#pragma once

#include <QtWidgets/QWidget>
#include "ui_Shaders.h"

class Shaders : public QWidget
{
    Q_OBJECT

public:
    Shaders(QWidget *parent = Q_NULLPTR);

private:
    Ui::ShadersClass ui;
};
