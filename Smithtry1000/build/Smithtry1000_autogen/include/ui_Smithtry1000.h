/********************************************************************************
** Form generated from reading UI file 'Smithtry1000.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMITHTRY1000_H
#define UI_SMITHTRY1000_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "circuitWidget.h"

QT_BEGIN_NAMESPACE

class Ui_Smithtry1000Class
{
public:
    QAction *actionColors;
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QTableWidget *rTable;
    QTableWidget *pointTable;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    CircuitWidget *circuitWidget;
    QScrollArea *scrollAreaDiagram;
    QWidget *scrollAreaWidgetContents_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QPushButton *OpenButton;
    QPushButton *SaveButton;
    QPushButton *CopyButton;
    QPushButton *StepBackButton;
    QPushButton *StepForwardButton;
    QPushButton *PrintButton;
    QFrame *line;
    QPushButton *MouseButton;
    QPushButton *KeyboardButton;
    QPushButton *S11Button;
    QPushButton *S22Button;
    QFrame *line_2;
    QPushButton *PlusSizeButton;
    QPushButton *MinusSizeButton;
    QPushButton *OneToOneButton;
    QFrame *line_3;
    QPushButton *Resistor_button;
    QPushButton *Induction_button;
    QPushButton *Capacitor_button;
    QPushButton *ResistorParallel_button;
    QPushButton *InductionParallel_button;
    QPushButton *CapacitorParallel_button;
    QPushButton *GraphButton;
    QFrame *line_4;
    QPushButton *ExportNetlist;
    QPushButton *Tune;
    QPushButton *Line_button;
    QPushButton *SSLine_button;
    QPushButton *OSLine_button;
    QMenuBar *menuBar;
    QMenu *menuEdit;
    QMenu *menuMode;
    QMenu *menuTools;
    QMenu *menuZoom;
    QMenu *menuWindow;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Smithtry1000Class)
    {
        if (Smithtry1000Class->objectName().isEmpty())
            Smithtry1000Class->setObjectName(QString::fromUtf8("Smithtry1000Class"));
        Smithtry1000Class->resize(1601, 900);
        actionColors = new QAction(Smithtry1000Class);
        actionColors->setObjectName(QString::fromUtf8("actionColors"));
        centralWidget = new QWidget(Smithtry1000Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 49, 1600, 850));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border-color: rgb(0, 0, 0);"));
        rTable = new QTableWidget(groupBox);
        rTable->setObjectName(QString::fromUtf8("rTable"));
        rTable->setGeometry(QRect(1200, 360, 401, 151));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        rTable->setPalette(palette);
        rTable->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pointTable = new QTableWidget(groupBox);
        if (pointTable->columnCount() < 5)
            pointTable->setColumnCount(5);
        pointTable->setObjectName(QString::fromUtf8("pointTable"));
        pointTable->setGeometry(QRect(1200, 510, 401, 301));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Button, brush);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush);
        pointTable->setPalette(palette1);
        pointTable->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        pointTable->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pointTable->setColumnCount(5);
        pointTable->horizontalHeader()->setDefaultSectionSize(70);
        scrollArea = new QScrollArea(groupBox);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(1200, 60, 391, 301));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 389, 299));
        circuitWidget = new CircuitWidget(scrollAreaWidgetContents);
        circuitWidget->setObjectName(QString::fromUtf8("circuitWidget"));
        circuitWidget->setGeometry(QRect(0, -60, 391, 361));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Button, brush);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush);
        circuitWidget->setPalette(palette2);
        scrollArea->setWidget(scrollAreaWidgetContents);
        scrollAreaDiagram = new QScrollArea(groupBox);
        scrollAreaDiagram->setObjectName(QString::fromUtf8("scrollAreaDiagram"));
        scrollAreaDiagram->setGeometry(QRect(0, 0, 1201, 811));
        scrollAreaDiagram->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 1199, 809));
        scrollAreaDiagram->setWidget(scrollAreaWidgetContents_2);
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, -1, 1931, 51));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(verticalLayoutWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(75, 75, 75);\n"
"border-color: rgb(0, 0, 0);\n"
"border-bottom-color: rgb(0, 0, 0);"));
        OpenButton = new QPushButton(groupBox_2);
        OpenButton->setObjectName(QString::fromUtf8("OpenButton"));
        OpenButton->setGeometry(QRect(20, 5, 31, 31));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Button, brush);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush);
        OpenButton->setPalette(palette3);
        OpenButton->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Images/Open.png"), QSize(), QIcon::Normal, QIcon::Off);
        OpenButton->setIcon(icon);
        OpenButton->setIconSize(QSize(21, 21));
        OpenButton->setAutoDefault(false);
        OpenButton->setFlat(false);
        SaveButton = new QPushButton(groupBox_2);
        SaveButton->setObjectName(QString::fromUtf8("SaveButton"));
        SaveButton->setGeometry(QRect(60, 5, 31, 31));
        SaveButton->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Images/Save.png"), QSize(), QIcon::Normal, QIcon::Off);
        SaveButton->setIcon(icon1);
        SaveButton->setIconSize(QSize(18, 18));
        CopyButton = new QPushButton(groupBox_2);
        CopyButton->setObjectName(QString::fromUtf8("CopyButton"));
        CopyButton->setGeometry(QRect(100, 5, 31, 31));
        CopyButton->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Images/Copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        CopyButton->setIcon(icon2);
        CopyButton->setIconSize(QSize(18, 18));
        StepBackButton = new QPushButton(groupBox_2);
        StepBackButton->setObjectName(QString::fromUtf8("StepBackButton"));
        StepBackButton->setGeometry(QRect(140, 5, 31, 31));
        StepBackButton->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Images/Undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        StepBackButton->setIcon(icon3);
        StepBackButton->setIconSize(QSize(25, 25));
        StepForwardButton = new QPushButton(groupBox_2);
        StepForwardButton->setObjectName(QString::fromUtf8("StepForwardButton"));
        StepForwardButton->setGeometry(QRect(180, 5, 31, 31));
        StepForwardButton->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Images/Redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        StepForwardButton->setIcon(icon4);
        StepForwardButton->setIconSize(QSize(25, 25));
        PrintButton = new QPushButton(groupBox_2);
        PrintButton->setObjectName(QString::fromUtf8("PrintButton"));
        PrintButton->setGeometry(QRect(220, 5, 31, 31));
        PrintButton->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Images/print.png"), QSize(), QIcon::Normal, QIcon::Off);
        PrintButton->setIcon(icon5);
        PrintButton->setIconSize(QSize(18, 18));
        line = new QFrame(groupBox_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(250, -10, 20, 51));
        line->setLineWidth(3);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        MouseButton = new QPushButton(groupBox_2);
        MouseButton->setObjectName(QString::fromUtf8("MouseButton"));
        MouseButton->setGeometry(QRect(270, 5, 51, 31));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Button, brush);
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush);
        MouseButton->setPalette(palette4);
        MouseButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        MouseButton->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        MouseButton->setIconSize(QSize(25, 25));
        KeyboardButton = new QPushButton(groupBox_2);
        KeyboardButton->setObjectName(QString::fromUtf8("KeyboardButton"));
        KeyboardButton->setGeometry(QRect(330, 5, 71, 31));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::Button, brush);
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette5.setBrush(QPalette::Active, QPalette::Base, brush);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush);
        KeyboardButton->setPalette(palette5);
        KeyboardButton->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        S11Button = new QPushButton(groupBox_2);
        S11Button->setObjectName(QString::fromUtf8("S11Button"));
        S11Button->setGeometry(QRect(410, 5, 41, 31));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::Button, brush);
        palette6.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette6.setBrush(QPalette::Active, QPalette::Base, brush);
        palette6.setBrush(QPalette::Active, QPalette::Window, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette6.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Window, brush);
        S11Button->setPalette(palette6);
        S11Button->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        S22Button = new QPushButton(groupBox_2);
        S22Button->setObjectName(QString::fromUtf8("S22Button"));
        S22Button->setGeometry(QRect(460, 5, 41, 31));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::Button, brush);
        palette7.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette7.setBrush(QPalette::Active, QPalette::Base, brush);
        palette7.setBrush(QPalette::Active, QPalette::Window, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette7.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Window, brush);
        S22Button->setPalette(palette7);
        S22Button->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        line_2 = new QFrame(groupBox_2);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(500, -10, 21, 51));
        line_2->setLineWidth(3);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        PlusSizeButton = new QPushButton(groupBox_2);
        PlusSizeButton->setObjectName(QString::fromUtf8("PlusSizeButton"));
        PlusSizeButton->setGeometry(QRect(520, 5, 31, 31));
        PlusSizeButton->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Images/PlusSize.png"), QSize(), QIcon::Normal, QIcon::Off);
        PlusSizeButton->setIcon(icon6);
        PlusSizeButton->setIconSize(QSize(18, 18));
        MinusSizeButton = new QPushButton(groupBox_2);
        MinusSizeButton->setObjectName(QString::fromUtf8("MinusSizeButton"));
        MinusSizeButton->setGeometry(QRect(560, 5, 31, 31));
        MinusSizeButton->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Images/MinusSize.png"), QSize(), QIcon::Normal, QIcon::Off);
        MinusSizeButton->setIcon(icon7);
        MinusSizeButton->setIconSize(QSize(18, 18));
        OneToOneButton = new QPushButton(groupBox_2);
        OneToOneButton->setObjectName(QString::fromUtf8("OneToOneButton"));
        OneToOneButton->setGeometry(QRect(600, 5, 31, 31));
        OneToOneButton->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Images/OneToOne.png"), QSize(), QIcon::Normal, QIcon::Off);
        OneToOneButton->setIcon(icon8);
        OneToOneButton->setIconSize(QSize(18, 18));
        line_3 = new QFrame(groupBox_2);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(630, -10, 20, 51));
        line_3->setLineWidth(3);
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        Resistor_button = new QPushButton(groupBox_2);
        Resistor_button->setObjectName(QString::fromUtf8("Resistor_button"));
        Resistor_button->setGeometry(QRect(644, 5, 31, 31));
        Resistor_button->setCursor(QCursor(Qt::ArrowCursor));
        Resistor_button->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Images/horizontal_r.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Resistor_button->setIcon(icon9);
        Resistor_button->setIconSize(QSize(25, 25));
        Induction_button = new QPushButton(groupBox_2);
        Induction_button->setObjectName(QString::fromUtf8("Induction_button"));
        Induction_button->setGeometry(QRect(680, 5, 31, 31));
        Induction_button->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Images/horizontal_i.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Induction_button->setIcon(icon10);
        Induction_button->setIconSize(QSize(25, 25));
        Capacitor_button = new QPushButton(groupBox_2);
        Capacitor_button->setObjectName(QString::fromUtf8("Capacitor_button"));
        Capacitor_button->setGeometry(QRect(720, 5, 31, 31));
        Capacitor_button->setCursor(QCursor(Qt::ArrowCursor));
        Capacitor_button->setFocusPolicy(Qt::FocusPolicy::WheelFocus);
        Capacitor_button->setContextMenuPolicy(Qt::ContextMenuPolicy::PreventContextMenu);
        Capacitor_button->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/Images/horizontal_c.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Capacitor_button->setIcon(icon11);
        Capacitor_button->setIconSize(QSize(25, 25));
        ResistorParallel_button = new QPushButton(groupBox_2);
        ResistorParallel_button->setObjectName(QString::fromUtf8("ResistorParallel_button"));
        ResistorParallel_button->setGeometry(QRect(800, 5, 31, 31));
        ResistorParallel_button->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/Images/vertical_r.svg"), QSize(), QIcon::Normal, QIcon::Off);
        ResistorParallel_button->setIcon(icon12);
        ResistorParallel_button->setIconSize(QSize(25, 25));
        InductionParallel_button = new QPushButton(groupBox_2);
        InductionParallel_button->setObjectName(QString::fromUtf8("InductionParallel_button"));
        InductionParallel_button->setGeometry(QRect(840, 5, 31, 31));
        InductionParallel_button->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/Images/vertical_i.svg"), QSize(), QIcon::Normal, QIcon::Off);
        icon13.addFile(QString::fromUtf8(":/Images/vertical_i_selected.svg"), QSize(), QIcon::Normal, QIcon::On);
        icon13.addFile(QString::fromUtf8(":/Images/vertical_i_selected.svg"), QSize(), QIcon::Disabled, QIcon::Off);
        icon13.addFile(QString::fromUtf8(":/Images/vertical_i_selected.svg"), QSize(), QIcon::Disabled, QIcon::On);
        icon13.addFile(QString::fromUtf8(":/Images/vertical_i_selected.svg"), QSize(), QIcon::Active, QIcon::Off);
        icon13.addFile(QString::fromUtf8(":/Images/vertical_i_selected.svg"), QSize(), QIcon::Active, QIcon::On);
        icon13.addFile(QString::fromUtf8(":/Images/vertical_i_selected.svg"), QSize(), QIcon::Selected, QIcon::Off);
        icon13.addFile(QString::fromUtf8(":/Images/vertical_i_selected.svg"), QSize(), QIcon::Selected, QIcon::On);
        InductionParallel_button->setIcon(icon13);
        InductionParallel_button->setIconSize(QSize(25, 25));
        CapacitorParallel_button = new QPushButton(groupBox_2);
        CapacitorParallel_button->setObjectName(QString::fromUtf8("CapacitorParallel_button"));
        CapacitorParallel_button->setGeometry(QRect(880, 5, 31, 31));
        CapacitorParallel_button->setToolTipDuration(-1);
        CapacitorParallel_button->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/Images/vertical_c.svg"), QSize(), QIcon::Normal, QIcon::Off);
        CapacitorParallel_button->setIcon(icon14);
        CapacitorParallel_button->setIconSize(QSize(25, 25));
        GraphButton = new QPushButton(groupBox_2);
        GraphButton->setObjectName(QString::fromUtf8("GraphButton"));
        GraphButton->setGeometry(QRect(1000, 5, 61, 31));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::Button, brush);
        palette8.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette8.setBrush(QPalette::Active, QPalette::Base, brush);
        palette8.setBrush(QPalette::Active, QPalette::Window, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette8.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::Window, brush);
        GraphButton->setPalette(palette8);
        GraphButton->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        line_4 = new QFrame(groupBox_2);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(0, 40, 1601, 2));
        line_4->setCursor(QCursor(Qt::ArrowCursor));
        line_4->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        ExportNetlist = new QPushButton(groupBox_2);
        ExportNetlist->setObjectName(QString::fromUtf8("ExportNetlist"));
        ExportNetlist->setGeometry(QRect(1070, 5, 61, 31));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::Button, brush);
        palette9.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette9.setBrush(QPalette::Active, QPalette::Base, brush);
        palette9.setBrush(QPalette::Active, QPalette::Window, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette9.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Window, brush);
        ExportNetlist->setPalette(palette9);
        ExportNetlist->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        Tune = new QPushButton(groupBox_2);
        Tune->setObjectName(QString::fromUtf8("Tune"));
        Tune->setGeometry(QRect(1140, 5, 61, 31));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::Button, brush);
        palette10.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette10.setBrush(QPalette::Active, QPalette::Base, brush);
        palette10.setBrush(QPalette::Active, QPalette::Window, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette10.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::Window, brush);
        Tune->setPalette(palette10);
        Tune->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        Line_button = new QPushButton(groupBox_2);
        Line_button->setObjectName(QString::fromUtf8("Line_button"));
        Line_button->setGeometry(QRect(760, 5, 31, 31));
        Line_button->setCursor(QCursor(Qt::ArrowCursor));
        Line_button->setFocusPolicy(Qt::FocusPolicy::WheelFocus);
        Line_button->setContextMenuPolicy(Qt::ContextMenuPolicy::PreventContextMenu);
        Line_button->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/Images/horizontal_line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Line_button->setIcon(icon15);
        Line_button->setIconSize(QSize(25, 25));
        SSLine_button = new QPushButton(groupBox_2);
        SSLine_button->setObjectName(QString::fromUtf8("SSLine_button"));
        SSLine_button->setGeometry(QRect(960, 5, 31, 31));
        SSLine_button->setToolTipDuration(-1);
        SSLine_button->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/Images/ss.svg"), QSize(), QIcon::Normal, QIcon::Off);
        SSLine_button->setIcon(icon16);
        SSLine_button->setIconSize(QSize(25, 25));
        OSLine_button = new QPushButton(groupBox_2);
        OSLine_button->setObjectName(QString::fromUtf8("OSLine_button"));
        OSLine_button->setGeometry(QRect(920, 5, 31, 31));
        OSLine_button->setToolTipDuration(-1);
        OSLine_button->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 255, 255);"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/Images/os.svg"), QSize(), QIcon::Normal, QIcon::Off);
        OSLine_button->setIcon(icon17);
        OSLine_button->setIconSize(QSize(25, 25));

        verticalLayout->addWidget(groupBox_2);

        Smithtry1000Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Smithtry1000Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1601, 21));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuMode = new QMenu(menuBar);
        menuMode->setObjectName(QString::fromUtf8("menuMode"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuZoom = new QMenu(menuBar);
        menuZoom->setObjectName(QString::fromUtf8("menuZoom"));
        menuWindow = new QMenu(menuBar);
        menuWindow->setObjectName(QString::fromUtf8("menuWindow"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        Smithtry1000Class->setMenuBar(menuBar);
        statusBar = new QStatusBar(Smithtry1000Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Smithtry1000Class->setStatusBar(statusBar);

        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuMode->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuZoom->menuAction());
        menuBar->addAction(menuWindow->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuTools->addAction(actionColors);

        retranslateUi(Smithtry1000Class);

        QMetaObject::connectSlotsByName(Smithtry1000Class);
    } // setupUi

    void retranslateUi(QMainWindow *Smithtry1000Class)
    {
        Smithtry1000Class->setWindowTitle(QCoreApplication::translate("Smithtry1000Class", "Smithtry1000", nullptr));
        actionColors->setText(QCoreApplication::translate("Smithtry1000Class", "Colors", nullptr));
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QString());
        OpenButton->setText(QString());
        SaveButton->setText(QString());
        CopyButton->setText(QString());
        StepBackButton->setText(QString());
        StepForwardButton->setText(QString());
        PrintButton->setText(QString());
        MouseButton->setText(QCoreApplication::translate("Smithtry1000Class", "Mouse", nullptr));
        KeyboardButton->setText(QCoreApplication::translate("Smithtry1000Class", "Keyboard", nullptr));
        S11Button->setText(QCoreApplication::translate("Smithtry1000Class", "S11", nullptr));
        S22Button->setText(QCoreApplication::translate("Smithtry1000Class", "S22", nullptr));
        PlusSizeButton->setText(QString());
        MinusSizeButton->setText(QString());
        OneToOneButton->setText(QString());
        Resistor_button->setText(QString());
        Induction_button->setText(QString());
        Capacitor_button->setText(QString());
        ResistorParallel_button->setText(QString());
        InductionParallel_button->setText(QString());
        CapacitorParallel_button->setText(QString());
        GraphButton->setText(QCoreApplication::translate("Smithtry1000Class", "AFR", nullptr));
        ExportNetlist->setText(QCoreApplication::translate("Smithtry1000Class", "Netlist", nullptr));
        Tune->setText(QCoreApplication::translate("Smithtry1000Class", "Tune", nullptr));
        Line_button->setText(QString());
        SSLine_button->setText(QString());
        OSLine_button->setText(QString());
        menuEdit->setTitle(QCoreApplication::translate("Smithtry1000Class", "Edit", nullptr));
        menuMode->setTitle(QCoreApplication::translate("Smithtry1000Class", "Mode", nullptr));
        menuTools->setTitle(QCoreApplication::translate("Smithtry1000Class", "Tools", nullptr));
        menuZoom->setTitle(QCoreApplication::translate("Smithtry1000Class", "Zoom", nullptr));
        menuWindow->setTitle(QCoreApplication::translate("Smithtry1000Class", "Window", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("Smithtry1000Class", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Smithtry1000Class: public Ui_Smithtry1000Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMITHTRY1000_H
