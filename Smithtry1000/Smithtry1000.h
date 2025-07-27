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
#include "ComplexNumber.h"
#include "AmplitudeFrequency.h"
#include "SParameters.h"
#include "ExportNetlist.h"
#include "renderarea.h"

class Smithtry1000 : public QMainWindow
{
    Q_OBJECT

public: 
    Smithtry1000(QWidget* parent = nullptr, SParameters* = nullptr);
    ~Smithtry1000();

private slots:
    void onButtonClicked();
    void onCapacitor_buttonClicked();
    void onInduction_buttonClicked();
    void onResistor_buttonClicked();
    void onCapacitorParallel_buttonClicked();
    void onInductionParallel_buttonClicked();
    void onResistorParallel_buttonClicked();
    void onDelete_buttonClicked();
    void onPlusSize_buttonClicked();
    void onMinusSize_buttonClicked();
    void onDefaultSize_buttonClicked();
    void onGraph_buttonClicked();
    void onExportNetlist_buttonClicked();
    void onS11_buttonClicked();
    void onS22_buttonClicked();
    void onTimeout();

private:
    SParameters* sParameters;
    CircuitElements* circuitElements = new CircuitElements();
    CircuitWidget* auxiliaryWidget = new CircuitWidget(this, circuitElements);  
    RenderArea* renderArea = new RenderArea(this, circuitElements);
    void ImaginaryImpedance();
    void ImaginaryAdmitance();
    void mousePressEvent(QMouseEvent* event) override;
    Ui::Smithtry1000Class* ui;
    bool trackingEnabled;
    bool leftClicked;
    bool rightClicked;
    double tempPointX;
    double tempPointY;
    double tempX=0;
    double tempY=0;
    QList<float> pointsX;
    QList<float> pointsY;
    float t;
    float tmin;
    float tmax;
    float step;
    float r;  // радиус в единицах
    float intervalLength = 2 * M_PI;
    QPoint getPointOnCircle(int, int);
    void rImpedanceRealCalculation(float, float);
    void rImpedanceImagCalculation(float, float);
    void rAdmitanceRealCalculation(float, float);
    void rAdmitanceImagCalculation(float, float);

    complexNumber zCalculation(float, float);
    complexNumber yCalculation(float, float);

    complexNumber impedanceRealChartParameters(float, float);
    complexNumber impedanceImagChartParameters(float, float);
    complexNumber admitanceRealChartParameters(float, float);
    complexNumber admitanceImagChartParameters(float, float);
};
