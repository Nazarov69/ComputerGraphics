/********************************************************************************
** Form generated from reading UI file 'Shaders.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHADERS_H
#define UI_SHADERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShadersClass
{
public:

    void setupUi(QWidget *ShadersClass)
    {
        if (ShadersClass->objectName().isEmpty())
            ShadersClass->setObjectName(QString::fromUtf8("ShadersClass"));
        ShadersClass->resize(600, 400);

        retranslateUi(ShadersClass);

        QMetaObject::connectSlotsByName(ShadersClass);
    } // setupUi

    void retranslateUi(QWidget *ShadersClass)
    {
        ShadersClass->setWindowTitle(QCoreApplication::translate("ShadersClass", "Shaders", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShadersClass: public Ui_ShadersClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHADERS_H
