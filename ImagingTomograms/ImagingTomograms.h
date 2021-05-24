#pragma once

#include <QtWidgets/QWidget>
#include "ui_ImagingTomograms.h"

class ImagingTomograms : public QWidget{
    Q_OBJECT
public:
    ImagingTomograms(QWidget *parent = Q_NULLPTR);

private:
    Ui::ImagingTomogramsClass ui;
};
