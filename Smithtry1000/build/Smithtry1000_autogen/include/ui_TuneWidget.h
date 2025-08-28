/********************************************************************************
** Form generated from reading UI file 'TuneWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TUNEWIDGET_H
#define UI_TUNEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TuneWidget
{
public:
    QPushButton *MinMaxButton;
    QPushButton *RemoveAllButton;
    QPushButton *OKButton;

    void setupUi(QWidget *TuneWidget)
    {
        if (TuneWidget->objectName().isEmpty())
            TuneWidget->setObjectName(QString::fromUtf8("TuneWidget"));
        TuneWidget->resize(400, 300);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(99, 99, 99, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush2(QColor(72, 72, 72, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush2);
        QBrush brush3(QColor(75, 75, 75, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        TuneWidget->setPalette(palette);
        TuneWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        MinMaxButton = new QPushButton(TuneWidget);
        MinMaxButton->setObjectName(QString::fromUtf8("MinMaxButton"));
        MinMaxButton->setGeometry(QRect(60, 250, 91, 24));
        MinMaxButton->setStyleSheet(QString::fromUtf8("background-color: rgb(72, 72, 72);\n"
"color: rgb(0, 0, 0);"));
        RemoveAllButton = new QPushButton(TuneWidget);
        RemoveAllButton->setObjectName(QString::fromUtf8("RemoveAllButton"));
        RemoveAllButton->setGeometry(QRect(170, 250, 71, 24));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush2);
        QBrush brush4(QColor(0, 0, 0, 128));
        brush4.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush4);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush2);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush4);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush2);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush4);
#endif
        RemoveAllButton->setPalette(palette1);
        RemoveAllButton->setStyleSheet(QString::fromUtf8("background-color: rgb(72, 72, 72);\n"
"color: rgb(0, 0, 0);"));
        OKButton = new QPushButton(TuneWidget);
        OKButton->setObjectName(QString::fromUtf8("OKButton"));
        OKButton->setGeometry(QRect(10, 250, 31, 24));
        OKButton->setStyleSheet(QString::fromUtf8("background-color: rgb(72, 72, 72);\n"
"color: rgb(0, 0, 0);"));

        retranslateUi(TuneWidget);

        QMetaObject::connectSlotsByName(TuneWidget);
    } // setupUi

    void retranslateUi(QWidget *TuneWidget)
    {
        TuneWidget->setWindowTitle(QCoreApplication::translate("TuneWidget", "TuneWidget", nullptr));
        MinMaxButton->setText(QCoreApplication::translate("TuneWidget", "Reset Min/Max", nullptr));
        RemoveAllButton->setText(QCoreApplication::translate("TuneWidget", "Remove All", nullptr));
        OKButton->setText(QCoreApplication::translate("TuneWidget", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TuneWidget: public Ui_TuneWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TUNEWIDGET_H
