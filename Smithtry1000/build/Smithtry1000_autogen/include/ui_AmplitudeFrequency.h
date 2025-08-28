/********************************************************************************
** Form generated from reading UI file 'AmplitudeFrequency.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AMPLITUDEFREQUENCY_H
#define UI_AMPLITUDEFREQUENCY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_AmplitudeFrequency
{
public:
    QCustomPlot *widget;

    void setupUi(QWidget *AmplitudeFrequency)
    {
        if (AmplitudeFrequency->objectName().isEmpty())
            AmplitudeFrequency->setObjectName(QString::fromUtf8("AmplitudeFrequency"));
        AmplitudeFrequency->resize(400, 300);
        widget = new QCustomPlot(AmplitudeFrequency);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 401, 301));

        retranslateUi(AmplitudeFrequency);

        QMetaObject::connectSlotsByName(AmplitudeFrequency);
    } // setupUi

    void retranslateUi(QWidget *AmplitudeFrequency)
    {
        AmplitudeFrequency->setWindowTitle(QCoreApplication::translate("AmplitudeFrequency", "AmplitudeFrequency", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AmplitudeFrequency: public Ui_AmplitudeFrequency {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AMPLITUDEFREQUENCY_H
