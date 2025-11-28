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
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

signals:
    void moved(QPoint);
    void released();
    void leftsignal(QPoint);
    void resized(long double, long double, long double, long double);

public slots:

private:
    void mousePressEvent(QMouseEvent* event) override;
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
    bool leftClicked = false;
    void drawStaticObjects(QPainter&);
    void drawDynamicObject(QPainter&);
    void generateCache();
    void ImpedanceImagLines(long double, long double, QPainter&);
    void ImpedanceRealLines(long double, long double, QPainter&);
    void AdmitanceImagLines(long double, long double, QPainter&);
    void AdmitanceRealLines(long double, long double, QPainter&);
    void DrawPoints(QPainter&);
    void DrawElements(QPainter&);
    void DrawCurrent(QPainter&);
    void DrawVSWR(QPainter&);
    void DrawQ(QPainter&);
    void DrawIndCapShuntElements(QPainter&, int);
    void DrawResShuntElements(QPainter&, int);
    void DrawIndCapParElements(QPainter&, int);
    void DrawResParElements(QPainter&, int);
    void DrawLineElements(QPainter&, int);
    void DrawOSSSElements(QPainter&, int);
    void DrawTransformElements(QPainter&, int);
    void DrawIndCapShuntCurrent(QPainter&);
    void DrawResShuntCurrent(QPainter&);
    void DrawIndCapParCurrent(QPainter&);
    void DrawResParCurrent(QPainter&);
    void DrawLineCurrent(QPainter&);
    void DrawOSSSCurrent(QPainter&);
    void DrawTransformCurrent(QPainter&);
    long double defaultScale = 200;



};
