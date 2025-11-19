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
extern map<int, tuple<Point, bool>> allPoints;