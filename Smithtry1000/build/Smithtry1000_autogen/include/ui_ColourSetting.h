/********************************************************************************
** Form generated from reading UI file 'ColourSetting.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLOURSETTING_H
#define UI_COLOURSETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ColourSettingClass
{
public:
    QWidget *formLayoutWidget_3;
    QFormLayout *formLayout_2;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QPushButton *S11Graf;
    QLabel *label_2;
    QPushButton *S22Graf;
    QLabel *label_3;
    QPushButton *MAGGraf;
    QLabel *label_4;
    QPushButton *MSGGraf;
    QLabel *label_5;
    QPushButton *KGraf;
    QLabel *label_6;
    QPushButton *MuGraf;
    QFormLayout *formLayout;
    QLabel *label_8;
    QPushButton *AmpFrS21;
    QLabel *label_7;
    QPushButton *AmpFrS11;
    QPushButton *CircleS12;
    QPushButton *CircleS21;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QPushButton *ColourImpedance;
    QLabel *label_12;
    QPushButton *ColourAdmitance;

    void setupUi(QWidget *ColourSettingClass)
    {
        if (ColourSettingClass->objectName().isEmpty())
            ColourSettingClass->setObjectName(QString::fromUtf8("ColourSettingClass"));
        ColourSettingClass->resize(600, 400);
        formLayoutWidget_3 = new QWidget(ColourSettingClass);
        formLayoutWidget_3->setObjectName(QString::fromUtf8("formLayoutWidget_3"));
        formLayoutWidget_3->setGeometry(QRect(0, 0, 221, 251));
        formLayout_2 = new QFormLayout(formLayoutWidget_3);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(formLayoutWidget_3);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        S11Graf = new QPushButton(formLayoutWidget_3);
        S11Graf->setObjectName(QString::fromUtf8("S11Graf"));

        gridLayout_2->addWidget(S11Graf, 0, 1, 1, 1);

        label_2 = new QLabel(formLayoutWidget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        S22Graf = new QPushButton(formLayoutWidget_3);
        S22Graf->setObjectName(QString::fromUtf8("S22Graf"));

        gridLayout_2->addWidget(S22Graf, 1, 1, 1, 1);

        label_3 = new QLabel(formLayoutWidget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        MAGGraf = new QPushButton(formLayoutWidget_3);
        MAGGraf->setObjectName(QString::fromUtf8("MAGGraf"));

        gridLayout_2->addWidget(MAGGraf, 2, 1, 1, 1);

        label_4 = new QLabel(formLayoutWidget_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setWordWrap(false);
        label_4->setMargin(0);

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        MSGGraf = new QPushButton(formLayoutWidget_3);
        MSGGraf->setObjectName(QString::fromUtf8("MSGGraf"));

        gridLayout_2->addWidget(MSGGraf, 3, 1, 1, 1);

        label_5 = new QLabel(formLayoutWidget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 4, 0, 1, 1);

        KGraf = new QPushButton(formLayoutWidget_3);
        KGraf->setObjectName(QString::fromUtf8("KGraf"));

        gridLayout_2->addWidget(KGraf, 4, 1, 1, 1);

        label_6 = new QLabel(formLayoutWidget_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 5, 0, 1, 1);

        MuGraf = new QPushButton(formLayoutWidget_3);
        MuGraf->setObjectName(QString::fromUtf8("MuGraf"));

        gridLayout_2->addWidget(MuGraf, 5, 1, 1, 1);


        formLayout_2->setLayout(0, QFormLayout::LabelRole, gridLayout_2);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_8 = new QLabel(formLayoutWidget_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_8);

        AmpFrS21 = new QPushButton(formLayoutWidget_3);
        AmpFrS21->setObjectName(QString::fromUtf8("AmpFrS21"));

        formLayout->setWidget(0, QFormLayout::FieldRole, AmpFrS21);

        label_7 = new QLabel(formLayoutWidget_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_7);

        AmpFrS11 = new QPushButton(formLayoutWidget_3);
        AmpFrS11->setObjectName(QString::fromUtf8("AmpFrS11"));

        formLayout->setWidget(1, QFormLayout::FieldRole, AmpFrS11);

        CircleS12 = new QPushButton(formLayoutWidget_3);
        CircleS12->setObjectName(QString::fromUtf8("CircleS12"));

        formLayout->setWidget(2, QFormLayout::FieldRole, CircleS12);

        CircleS21 = new QPushButton(formLayoutWidget_3);
        CircleS21->setObjectName(QString::fromUtf8("CircleS21"));

        formLayout->setWidget(3, QFormLayout::FieldRole, CircleS21);

        label_9 = new QLabel(formLayoutWidget_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_9);

        label_10 = new QLabel(formLayoutWidget_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_10);

        label_11 = new QLabel(formLayoutWidget_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_11);

        ColourImpedance = new QPushButton(formLayoutWidget_3);
        ColourImpedance->setObjectName(QString::fromUtf8("ColourImpedance"));

        formLayout->setWidget(4, QFormLayout::FieldRole, ColourImpedance);

        label_12 = new QLabel(formLayoutWidget_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_12);

        ColourAdmitance = new QPushButton(formLayoutWidget_3);
        ColourAdmitance->setObjectName(QString::fromUtf8("ColourAdmitance"));

        formLayout->setWidget(5, QFormLayout::FieldRole, ColourAdmitance);


        formLayout_2->setLayout(0, QFormLayout::FieldRole, formLayout);


        retranslateUi(ColourSettingClass);

        QMetaObject::connectSlotsByName(ColourSettingClass);
    } // setupUi

    void retranslateUi(QWidget *ColourSettingClass)
    {
        ColourSettingClass->setWindowTitle(QCoreApplication::translate("ColourSettingClass", "ColourSetting", nullptr));
        label->setText(QCoreApplication::translate("ColourSettingClass", " S11Graf", nullptr));
        S11Graf->setText(QString());
        label_2->setText(QCoreApplication::translate("ColourSettingClass", " S22Graf", nullptr));
        S22Graf->setText(QString());
        label_3->setText(QCoreApplication::translate("ColourSettingClass", "   MAG", nullptr));
        MAGGraf->setText(QString());
        label_4->setText(QCoreApplication::translate("ColourSettingClass", "   MSG", nullptr));
        MSGGraf->setText(QString());
        label_5->setText(QCoreApplication::translate("ColourSettingClass", "     K", nullptr));
        KGraf->setText(QString());
        label_6->setText(QCoreApplication::translate("ColourSettingClass", "     \316\274", nullptr));
        MuGraf->setText(QString());
        label_8->setText(QCoreApplication::translate("ColourSettingClass", " AmpFrS21", nullptr));
        AmpFrS21->setText(QString());
        label_7->setText(QCoreApplication::translate("ColourSettingClass", " AmpFrS11", nullptr));
        AmpFrS11->setText(QString());
        CircleS12->setText(QString());
        CircleS21->setText(QString());
        label_9->setText(QCoreApplication::translate("ColourSettingClass", "       S12", nullptr));
        label_10->setText(QCoreApplication::translate("ColourSettingClass", "       S21", nullptr));
        label_11->setText(QCoreApplication::translate("ColourSettingClass", "GridImpedance", nullptr));
        ColourImpedance->setText(QString());
        label_12->setText(QCoreApplication::translate("ColourSettingClass", "GridAdmitance", nullptr));
        ColourAdmitance->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ColourSettingClass: public Ui_ColourSettingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLOURSETTING_H
