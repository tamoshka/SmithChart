#pragma once
#include <QWidget>
#include <QColor>
#include <QVector>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPoint>
#include <QTimer>
#include "circuitElements.h"
using namespace std;

/// <summary>
/// Класс визуализации ДВС.
/// </summary>
class RenderArea : public QWidget
{
    Q_OBJECT
public:
    void setCursorPosOnCircle(const QPoint& pos);
    CircuitElements* circuitElements = new CircuitElements();

    RenderArea(QWidget* parent = nullptr, CircuitElements* circuitElements = nullptr);


protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

signals:

public slots:

private:
    long double r;
    QPointF center;
    Point compute_real(long double t);
    Point compute_realParallel(long double t);
    Point compute_imaginary(long double t);
    Point compute_imaginaryParallel(long double t);
    Point compute_line(long double t, long double radius);
    Point compute_q(long double t, long double radius);
    QPoint cursorPos;
    QPixmap m_cache;
    bool m_cacheValid;
    void drawStaticObjects(QPainter&);
    void drawDynamicObject(QPainter&);
    void generateCache();
    long double defaultScale = 200;



};
