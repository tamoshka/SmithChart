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
    void onTimeout();

private:
    Ui::Smithtry1000Class* ui;
    bool trackingEnabled;
    float t;
    float step = 0.02;
    const float r = 1.0;  // радиус в единицах
    const float intervalLength = 2 * M_PI;

    QPoint getPointOnCircle(int, int);
};
