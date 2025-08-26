#pragma once
#include <QList>
#include <QtSvgWidgets>
#include <QPointF>
#include <tuple>
#include <QMap>>
#include <list>
#include <vector>
#include <complex>
#include <cmath>
#include <map>
using namespace std;

using Complex = complex<double>;

extern enum mode
{
    CapacitorParallel,
    CapacitorShunt,
    ResistorParallel,
    ResistorShunt,
    InductionParallel,
    InductionShunt,
    Line,
    OSLine,
    SSLine,
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
extern enum parameterMode
{
    Z,
    Y,
    G
};
extern struct Point
{
    double x;
    double y;
};
extern QString fileName;
extern mode Model;
extern double frequency;
extern QList<double> frequencyList;
extern QList<Point> morePoints;
extern QList<double> qCircles;
extern int index;
extern int dpIndex;
extern double impedanceRealR;
extern double impedanceImagR;
extern double admitanceRealR;
extern double admitanceImagR;
extern double lastPointX;
extern double lastPointY;
extern double scale;
extern QList<QSvgWidget*> svgWidgets;
extern map<int, tuple<Point, double, double, mode>> points;