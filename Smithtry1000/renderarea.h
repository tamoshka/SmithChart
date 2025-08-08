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

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    void setCursorPosOnCircle(const QPoint& pos);

    RenderArea(QWidget* parent = nullptr, CircuitElements* circuitElements = nullptr);
    bool flag[20] = { false };
    int step_count = 0;


    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;


    enum Mode { Impedence, Admittance, Superimpose, Hide, Both };


protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

signals:

public slots:

private:
    CircuitElements* circuitElements = new CircuitElements();
    float r;
    QPointF center;
    QColor mBackGroundColor;
    QColor mShapeColor;
    Mode mMode;
    float mScale;
    QPointF compute_real(float t);
    QPointF compute_realParallel(float t);
    QPointF compute_imaginary(float t);
    QPointF compute_imaginaryParallel(float t);
    QPoint cursorPos;
    QPixmap m_cache;
    bool m_cacheValid;
    void drawStaticObjects(QPainter&);
    void drawDynamicObject(QPainter&);
    qreal m_scaleFactor;
    void generateCache();
    float defaultScale = 200;



};
