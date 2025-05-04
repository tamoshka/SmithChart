#pragma once

#include <qpainterpath.h>
#include <QtSvg>
#include "general.h"
#include <QWidget>
#include <QScrollArea>

class CircuitWidget : public QWidget
{
    Q_OBJECT

public:
    CircuitWidget(QWidget* parent = nullptr);
    ~CircuitWidget();
    void addSvg(QString, int, int);
    void removeLastSvg();
private:
    void rImpedanceRealCalculation(float x, float y);
    void rAdmitanceRealCalculation(float x, float y);
    void rImpedanceImagCalculation(float x, float y);
    void rAdmitanceImagCalculation(float x, float y);
protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

};
