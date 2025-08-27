#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Smithtry1000.h"
#include <qgraphicsscene.h>
#include <qpainterpath.h>
#include <QtSvg>
#include <QTimer>
#include <QMouseEvent>
#include "general.h"
#include <qtablewidget.h>
#include <QScrollArea>
#include "frequencyDialog.h"
#include "VerticalLinesDialog.h"
#include "ComplexNumber.h"
#include "AmplitudeFrequency.h"
#include "SParameters.h"
#include "ExportNetlist.h"
#include "renderarea.h"
#include "TuneWidget.h"
#include "ColourSetting.h"
class Smithtry1000 : public QMainWindow
{
    Q_OBJECT

public: 
    Smithtry1000(QWidget* parent = nullptr, SParameters* = nullptr);
    ~Smithtry1000();
    CircuitElements* circuitElements = new CircuitElements();
    CircuitWidget* auxiliaryWidget = new CircuitWidget(this, circuitElements);

public slots:
    void getsignal();
    void getS12S21signal();
    void getsignalDVS();

signals:
    void left();

private slots:
    void onButtonClicked();
    void onCapacitor_buttonClicked();
    void onInduction_buttonClicked();
    void onResistor_buttonClicked();
    void onCapacitorParallel_buttonClicked();
    void onInductionParallel_buttonClicked();
    void onResistorParallel_buttonClicked();
    void onLine_buttonClicked();
    void onOSLine_buttonClicked();
    void onSSLine_buttonClicked();
    void onDelete_buttonClicked();
    void onPlusSize_buttonClicked();
    void onMinusSize_buttonClicked();
    void onDefaultSize_buttonClicked();
    void onGraph_buttonClicked();
    void onExportNetlist_buttonClicked();
    void onTune_buttonClicked();
    void onS11_buttonClicked();
    void onS22_buttonClicked();
    void onTimeout();
    void TableUpdate();
    void onMenuToolsCliked();
private:
    SParameters* sParameters;
    AmplitudeFrequency* amplitudeFrequence = new AmplitudeFrequency(nullptr, circuitElements);
    RenderArea* renderArea = new RenderArea(this, circuitElements);
    TuneWidget* tuneWidget = new TuneWidget(nullptr, circuitElements);
    void ImaginaryImpedance();
    void ImaginaryAdmitance();
    void VerticalLines();
    void mousePressEvent(QMouseEvent* event) override;
    Ui::Smithtry1000Class* ui;
    bool trackingEnabled;
    bool leftClicked;
    bool rightClicked;
    bool tableChanged=false;
    double tempPointX;
    double tempPointY;
    double tempX=0;
    double tempY=0;
    QList<double> pointsX;
    QList<double> pointsY;
    double t;
    double tmin;
    double tmax;
    double step;
    double r;  // радиус в единицах
    double intervalLength = 2 * M_PI;
    QPoint getPointOnCircle(int, int);
    void rImpedanceRealCalculation(double, double);
    void rImpedanceImagCalculation(double, double);
    void rAdmitanceRealCalculation(double, double);
    void rAdmitanceImagCalculation(double, double);

    Complex zCalculation(double, double);
    Complex yCalculation(double, double);

    Complex impedanceRealChartParameters(double, double);
    Complex impedanceImagChartParameters(double, double);
    Complex admitanceRealChartParameters(double, double);
    Complex admitanceImagChartParameters(double, double);

protected:
    void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;
};
