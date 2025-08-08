#pragma once

#include <qpainterpath.h>
#include <QtSvg>
#include "general.h"
#include <QWidget>
#include <QScrollArea>
#include "circuitElements.h"
class CircuitWidget : public QWidget
{
    Q_OBJECT

public:
    CircuitWidget(QWidget* parent = nullptr, CircuitElements* = new CircuitElements());
    ~CircuitWidget();
    void addSvg(QString, int, int);
    void removeLastSvg();
private:
    void rImpedanceRealCalculation(float x, float y);
    void rAdmitanceRealCalculation(float x, float y);
    void rImpedanceImagCalculation(float x, float y);
    void rAdmitanceImagCalculation(float x, float y);
    QList<int> tuned;
    QList<QString> paths;
    CircuitElements* circuitElements;
    CircuitElements* tuneElements;
    bool left;
signals:
    void clicked(Element* tuned, QString path);

public slots:
    void getLeft();

protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
};
