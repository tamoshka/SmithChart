#pragma once
#include <QList>
#include <QtSvg>
#include <QPointF>
#include <tuple>
#include <QMap>
#include <list>
#include <vector>
#include <complex>
#include <cmath>
#include <map>
using namespace std;

// Макрос для замены index на point_index
#define index point_index

using Complex = complex<double>;

enum mode
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
enum chartMode
{
    RealImpedance,
    RealAdmitance,
    ImagImpedance,
    ImagAdmitance
};
enum parameterMode
{
    Z,
    Y,
    G
};
struct Point
{
    double x;
    double y;
};

extern QString fileName;
extern mode Model;
extern double frequency;
extern QList<double> frequencyList;
extern QList<Point> morePoints;
extern map<int, tuple<Point, bool>> allPoints;
extern QList<double> qCircles;
extern int point_index;
extern int dpIndex;
extern double scale;
extern QList<QSvgWidget*> svgWidgets;
extern map<int, tuple<Point, double, double, mode>> points;
extern chartMode cMode;
extern parameterMode pMode;
extern double lastPointX;
extern double lastPointY;
extern double rRadius;
extern double rCenterX;
extern double rCenterY;
extern double iRadius;
extern double iCenterX;
extern double iCenterY;
extern double gRadius;
extern double gCenterX;
extern double gCenterY;
extern double bRadius;
extern double bCenterX;
extern double bCenterY;

// Добавим недостающие переменные
extern double impedanceRealR;
extern double impedanceImagR;
extern double admitanceRealR;
extern double admitanceImagR;