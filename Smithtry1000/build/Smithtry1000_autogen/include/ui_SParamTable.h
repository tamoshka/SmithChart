/********************************************************************************
** Form generated from reading UI file 'SParamTable.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPARAMTABLE_H
#define UI_SPARAMTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SParamTableClass
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;

    void setupUi(QWidget *SParamTableClass)
    {
        if (SParamTableClass->objectName().isEmpty())
            SParamTableClass->setObjectName(QString::fromUtf8("SParamTableClass"));
        SParamTableClass->resize(600, 400);
        gridLayout = new QGridLayout(SParamTableClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidget = new QTableWidget(SParamTableClass);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);


        retranslateUi(SParamTableClass);

        QMetaObject::connectSlotsByName(SParamTableClass);
    } // setupUi

    void retranslateUi(QWidget *SParamTableClass)
    {
        SParamTableClass->setWindowTitle(QCoreApplication::translate("SParamTableClass", "SParamTable", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SParamTableClass: public Ui_SParamTableClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPARAMTABLE_H
