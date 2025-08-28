/********************************************************************************
** Form generated from reading UI file 'ExportNetlist.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORTNETLIST_H
#define UI_EXPORTNETLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExportNetlist
{
public:

    void setupUi(QWidget *ExportNetlist)
    {
        if (ExportNetlist->objectName().isEmpty())
            ExportNetlist->setObjectName(QString::fromUtf8("ExportNetlist"));
        ExportNetlist->resize(400, 300);
        ExportNetlist->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        retranslateUi(ExportNetlist);

        QMetaObject::connectSlotsByName(ExportNetlist);
    } // setupUi

    void retranslateUi(QWidget *ExportNetlist)
    {
        ExportNetlist->setWindowTitle(QCoreApplication::translate("ExportNetlist", "ExportNetlist", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExportNetlist: public Ui_ExportNetlist {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTNETLIST_H
