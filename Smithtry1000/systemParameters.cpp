#include "systemParameters.h"

QColor SystemParameters::MainCircleColor = QColor(Qt::black);
QColor SystemParameters::ImpedanceColor = QColor(Qt::blue);
QColor SystemParameters::AdmitanceColor = QColor(Qt::red);
QColor SystemParameters::MainImpedanceColor = QColor(Qt::blue);
QColor SystemParameters::MainAdmitanceColor = QColor(Qt::red);
QColor SystemParameters::DataPointsColor = QColor(Qt::magenta);
QColor SystemParameters::RootColor = QColor(Qt::green);
QColor SystemParameters::ElementsColor = QColor(Qt::black);
QColor SystemParameters::BackgroundColor = QColor(Qt::white);
QColor SystemParameters::VSWRColor = QColor(137, 81, 41);
QColor SystemParameters::QCirclesColor = QColor(0, 255, 255);
QColor SystemParameters::ampS11Color = QColor(Qt::blue);
QColor SystemParameters::ampS21Color = QColor(Qt::red);
QColor SystemParameters::s11GrafColor = QColor(Qt::blue);
QColor SystemParameters::s22GrafColor = QColor(Qt::red);
QColor SystemParameters::magGrafColor = QColor(Qt::blue);
QColor SystemParameters::msgGrafColor = QColor(Qt::red);
QColor SystemParameters::kGrafColor = QColor(Qt::green);
QColor SystemParameters::muGrafColor = QColor(Qt::black);
QColor SystemParameters::circleS12 = QColor(Qt::blue);
QColor SystemParameters::circleS21 = QColor(Qt::blue);
QColor SystemParameters::gridGrafOneColor = QColor(Qt::black);
QColor SystemParameters::gridGrafTwoColor = QColor(Qt::black);
QColor SystemParameters::gridAmpFrColor = QColor(Qt::black);
QList<int> SystemParameters::sPlotline = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
QList<int> SystemParameters::ampFrline = { 1,1,1 };
QList<double> SystemParameters::linesWidth = { 2, 1, 1, 2, 2, 2, 1, 3, 3, 2, 2};
bool SystemParameters::circuitHover = false;
bool SystemParameters::tune = false;
bool SystemParameters::tuned = false;
bool SystemParameters::tuneBlock = false;
bool SystemParameters::colorChanged = false;
QList<Element*> SystemParameters::tunedElements = {};
double SystemParameters::er = 1;
double SystemParameters::z0line = 50;
double SystemParameters::alpha = 0;
double SystemParameters::lambda = 0.25;
bool SystemParameters::sizeChanged = false;
double SystemParameters::frequency = 500; 
double SystemParameters::Re = 50;
double SystemParameters::Im = 0;
systemMode SystemParameters::sys = Impedance;
QSet<double> SystemParameters::VSWRCircles = {};
QSet<double> SystemParameters::QCircles = {};
double SystemParameters::impedanceRealR = 0;
double SystemParameters::impedanceImagR = 0;
double SystemParameters::admitanceImagR = 0;
double SystemParameters::admitanceRealR = 0;

void SystemParameters::rImpedanceRealCalculation(double x, double y)
{
    if (y >= 0 && y < 0.000001)
    {
        y = 0.01;
    }
    else if (y <= 0 && y > -0.000001)
    {
        y = -0.01;
    }
    double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
    double xCenter = 1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    double sin_t = dy;
    double cos_t = dx;
    double t1;
    t1 = atan(sin_t / cos_t);
    if (cos_t < 0 && sin_t < 0)
    {
        t1 += M_PI;
    }
    else if (cos_t > 0 && sin_t < 0)
    {
        t1 = 2 * M_PI - abs(t1);
    }
    else if (sin_t > 0 && cos_t < 0)
    {
        t1 = M_PI - abs(t1);
    }
    if (x - 1 != 0)
    {
        impedanceRealR = abs((cos(t1) - x) / (x - 1));
    }
    impedanceRealR *= 50;
}

void SystemParameters::rAdmitanceRealCalculation(double x, double y)
{
    if (y >= 0 && y < 0.000001)
    {
        y = 0.01;
    }
    else if (y <= 0 && y > -0.000001)
    {
        y = -0.01;
    }
    double circleRadius = -1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 + 2 * x));
    double xCenter = -1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    dy *= -1;
    double sin_t = dy;
    double cos_t = dx;
    double t1;
    t1 = atan(sin_t / cos_t);
    if (cos_t < 0 && sin_t < 0)
    {
        t1 = abs(t1) - M_PI;
    }
    else if (sin_t > 0 && cos_t < 0)
    {
        t1 = M_PI - abs(t1);
    }
    if (x - 1 != 0)
    {
        admitanceRealR = abs((cos(t1) - x) / (x + 1));
    }
    admitanceRealR *= 20;
}

void SystemParameters::rImpedanceImagCalculation(double x, double y)
{
    double cos_t;
    double sin_t;
    if (y >= 0 && y < 0.000001)
    {
        y = 0.01;
    }
    else if (y <= 0 && y > -0.000001)
    {
        y = -0.01;
    }
    double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
    double xCenter = 1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    sin_t = dy;
    cos_t = dx;
    double t1;
    t1 = atan(cos_t / sin_t);
    if (y < 0)
    {
        t1 += M_PI;
    }
    else
    {
        t1 += 2 * M_PI;
    }
    if (x - 1 != 0)
    {
        impedanceImagR = cos(t1) / (x - 1);
    }
    else
    {
        impedanceImagR = (1 + sin(t1)) / y;
    }
    if (y < 0)
    {
        impedanceImagR = abs(impedanceImagR);
    }
    else
    {
        impedanceImagR = abs(impedanceImagR) * (-1);
    }
    impedanceImagR *= 50;
}

void SystemParameters::rAdmitanceImagCalculation(double x, double y)
{
    if (y >= 0 && y < 0.000001)
    {
        y = 0.01;
    }
    else if (y <= 0 && y > -0.000001)
    {
        y = -0.01;
    }
    double cos_t;
    double sin_t;
    double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y, 2)) / (-2 * y);
    double yCenter = -circleRadius;
    double dx = x + 1;
    double dy = y - yCenter;
    sin_t = -dy;
    cos_t = dx;
    double t1;
    t1 = atan(sin_t / cos_t);
    if (x + 1 != 0)
    {
        admitanceImagR = cos(t1) / (x + 1);
    }
    else
    {
        admitanceImagR = (1 + sin(t1)) / y;
    }
    if (y > 0)
    {
        admitanceImagR *= -1;
    }
    admitanceImagR *= -20;
}

Complex SystemParameters::zCalculation(double x, double y)
{
    rImpedanceRealCalculation(x, y);
    rImpedanceImagCalculation(x, y);
    return Complex(impedanceRealR, impedanceImagR);
}

Complex SystemParameters::yCalculation(double x, double y)
{
    rAdmitanceRealCalculation(x, y);
    rAdmitanceImagCalculation(x, y);
    return Complex(admitanceRealR, admitanceImagR);
}

Complex SystemParameters::impedanceRealChartParameters(double x, double y)
{
    if (y >= 0 && y < 0.000001)
    {
        y = 0.01;
    }
    else if (y <= 0 && y > -0.000001)
    {
        y = -0.01;
    }
    double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
    double xCenter = 1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    double sin_t = dy;
    double cos_t = dx;
    double t1, r1;
    t1 = atan(sin_t / cos_t);
    if (cos_t < 0 && sin_t < 0)
    {
        t1 += M_PI;
    }
    else if (cos_t > 0 && sin_t < 0)
    {
        t1 = 2 * M_PI - abs(t1);
    }
    else if (sin_t > 0 && cos_t < 0)
    {
        t1 = M_PI - abs(t1);
    }
    if (x - 1 != 0)
    {
        r1 = (cos(t1) - x) / (x - 1);
    }
    return Complex(r1, t1);
}

Complex SystemParameters::admitanceRealChartParameters(double x, double y)
{
    if (y >= 0 && y < 0.000001)
    {
        y = 0.01;
    }
    else if (y <= 0 && y > -0.000001)
    {
        y = -0.01;
    }
    double circleRadius = -1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 + 2 * x));
    double xCenter = -1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    dy *= -1;
    double sin_t = dy;
    double cos_t = dx;
    double t1, r1;
    t1 = atan(sin_t / cos_t);
    if (cos_t < 0 && sin_t < 0)
    {
        t1 = abs(t1) - M_PI;
    }
    else if (sin_t > 0 && cos_t < 0)
    {
        t1 = M_PI - abs(t1);
    }
    if (x - 1 != 0)
    {
        r1 = abs((cos(t1) - x) / (x + 1));
    }
    return Complex(r1, t1);
}

Complex SystemParameters::impedanceImagChartParameters(double x, double y)
{
    double cos_t;
    double sin_t;
    if (y >= 0 && y < 0.000001)
    {
        y = 0.01;
    }
    else if (y <= 0 && y > -0.000001)
    {
        y = -0.01;
    }
    double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
    double xCenter = 1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    sin_t = dy;
    cos_t = dx;
    double t1, r1;
    t1 = atan(cos_t / sin_t);
    if (y < 0)
    {
        t1 += M_PI;
    }
    else
    {
        t1 += 2 * M_PI;
    }
    if (x - 1 != 0)
    {
        r1 = cos(t1) / (x - 1);
    }
    else
    {
        r1 = (1 + sin(t1)) / y;
    }
    if (y < 0)
    {
        r1 = abs(r1);
    }
    else
    {
        r1 = abs(r1) * (-1);
    }
    return Complex(r1, t1);
}

Complex SystemParameters::admitanceImagChartParameters(double x, double y)
{
    double cos_t;
    double sin_t;
    if (y >= 0 && y < 0.000001)
    {
        y = 0.01;
    }
    else if (y <= 0 && y > -0.0001)
    {
        y = -0.01;
    }
    double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y, 2)) / (-2 * y);
    double yCenter = -circleRadius;
    double dx = x + 1;
    double dy = y - yCenter;
    sin_t = -dy;
    cos_t = dx;
    double t1, r1;
    t1 = atan(sin_t / cos_t);
    if (x + 1 != 0)
    {
        r1 = cos(t1) / (x + 1);
    }
    else
    {
        r1 = (1 + sin(t1)) / y;
    }
    if (y > 0)
    {
        r1 *= -1;
    }
    return Complex(r1, t1);
}