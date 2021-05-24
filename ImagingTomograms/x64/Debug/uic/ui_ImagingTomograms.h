/********************************************************************************
** Form generated from reading UI file 'ImagingTomograms.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGINGTOMOGRAMS_H
#define UI_IMAGINGTOMOGRAMS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImagingTomogramsClass
{
public:

    void setupUi(QWidget *ImagingTomogramsClass)
    {
        if (ImagingTomogramsClass->objectName().isEmpty())
            ImagingTomogramsClass->setObjectName(QString::fromUtf8("ImagingTomogramsClass"));
        ImagingTomogramsClass->resize(600, 400);

        retranslateUi(ImagingTomogramsClass);

        QMetaObject::connectSlotsByName(ImagingTomogramsClass);
    } // setupUi

    void retranslateUi(QWidget *ImagingTomogramsClass)
    {
        ImagingTomogramsClass->setWindowTitle(QCoreApplication::translate("ImagingTomogramsClass", "ImagingTomograms", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImagingTomogramsClass: public Ui_ImagingTomogramsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGINGTOMOGRAMS_H
