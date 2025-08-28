/********************************************************************************
** Form generated from reading UI file 'GrafOne.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAFONE_H
#define UI_GRAFONE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_GrafOneClass
{
public:
    QGridLayout *gridLayout;
    QCustomPlot *widget;

    void setupUi(QWidget *GrafOneClass)
    {
        if (GrafOneClass->objectName().isEmpty())
            GrafOneClass->setObjectName(QString::fromUtf8("GrafOneClass"));
        GrafOneClass->resize(589, 400);
        gridLayout = new QGridLayout(GrafOneClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget = new QCustomPlot(GrafOneClass);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(GrafOneClass);

        QMetaObject::connectSlotsByName(GrafOneClass);
    } // setupUi

    void retranslateUi(QWidget *GrafOneClass)
    {
        GrafOneClass->setWindowTitle(QCoreApplication::translate("GrafOneClass", "GrafOne", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GrafOneClass: public Ui_GrafOneClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAFONE_H
