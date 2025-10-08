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
#include <QSet>
using namespace std;

// Макрос для замены index на point_index
#define index point_index

using Complex = complex<long double>;

enum ElementType
{
    BaseElement = 0,
    VerticalLines = 1,
    Lines = 2
};

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
    Transform,
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
enum systemMode
{
    Impedance,
    Admittance,
    ReflectionCoefficient
};
enum valueMode
{
    Polar,
    Cartesian
};
struct Point
{
    long double x;
    long double y;
};

extern QString fileName;
extern mode Model;
extern long double frequency;
extern QList<long double> frequencyList;
extern QList<Point> morePoints;
extern map<int, tuple<Point, bool>> allPoints;
extern QList<double> qCircles;
extern int point_index;
extern int dpIndex;
extern int allpointindex;
extern double scale;
extern QList<QSvgWidget*> svgWidgets;
extern map<int, tuple<Point, long double, long double, mode>> points;
extern chartMode cMode;
extern parameterMode pMode;
extern long double lastPointX;
extern long double lastPointY;
extern long double rRadius;
extern long double rCenterX;
extern long double rCenterY;
extern long double iRadius;
extern long double iCenterX;
extern long double iCenterY;
extern long double gRadius;
extern long double gCenterX;
extern long double gCenterY;
extern long double bRadius;
extern long double bCenterX;
extern long double bCenterY;
