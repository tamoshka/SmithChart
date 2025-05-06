#pragma once
#include <QList>
#include <QtSvgWidgets>
#include <QPointF>
#include <tuple>
#include <QMap>>
#include <map>
using namespace std;
extern enum mode
{
    CapacitorParallel,
    CapacitorShunt,
    ResistorParallel,
    ResistorShunt,
    InductionParallel,
    InductionShunt,
    AddPoint,
    Default
}; 
extern enum chartMode
{
    RealImpedance,
    RealAdmitance,
    ImagImpedance,
    ImagAdmitance
};
extern struct Point
{
    float x;
    float y;
};
extern mode Model;
extern float frequency;
extern QList<float> frequencyList;
extern QList<Point> morePoints;
extern QList<float> qCircles;
extern int index;
extern int dpIndex;
extern float impedanceRealR;
extern float impedanceImagR;
extern float admitanceRealR;
extern float admitanceImagR;
extern float lastPointX;
extern float lastPointY;
extern float scale;
extern QList<QSvgWidget*> svgWidgets;
extern map<int, tuple<Point, float, float, mode>> points;