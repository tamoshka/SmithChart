/********************************************************************************
** Form generated from reading UI file 'GrafTwo.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAFTWO_H
#define UI_GRAFTWO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_GrafTwoClass
{
public:
    QGridLayout *gridLayout;
    QCustomPlot *widget;

    void setupUi(QWidget *GrafTwoClass)
    {
        if (GrafTwoClass->objectName().isEmpty())
            GrafTwoClass->setObjectName(QString::fromUtf8("GrafTwoClass"));
        GrafTwoClass->resize(596, 486);
        gridLayout = new QGridLayout(GrafTwoClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget = new QCustomPlot(GrafTwoClass);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(GrafTwoClass);

        QMetaObject::connectSlotsByName(GrafTwoClass);
    } // setupUi

    void retranslateUi(QWidget *GrafTwoClass)
    {
        GrafTwoClass->setWindowTitle(QCoreApplication::translate("GrafTwoClass", "GrafTwo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GrafTwoClass: public Ui_GrafTwoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAFTWO_H
