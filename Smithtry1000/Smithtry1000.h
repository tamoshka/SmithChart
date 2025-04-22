#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Smithtry1000.h"
#include <qgraphicsscene.h>
#include <qpainterpath.h>
#include <QtSvg>
#include <QTimer>
#include <QMouseEvent>

class Smithtry1000 : public QMainWindow
{
    Q_OBJECT

public:
    Smithtry1000(QWidget* parent = nullptr);
    ~Smithtry1000();

private slots:
    void onButtonClicked();
    void onCapacitor_buttonClicked();
    void onInduction_buttonClicked();
    void onResistor_buttonClicked();
    void onTimeout();

private:
    void mousePressEvent(QMouseEvent* event) override;
    Ui::Smithtry1000Class* ui;
    bool trackingEnabled;
    bool leftClicked;
    bool rightClicked;
    bool firstPoint = true;
    double lastPointX;
    double lastPointY;
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
};
