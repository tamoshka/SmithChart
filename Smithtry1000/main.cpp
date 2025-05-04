#include "Smithtry1000.h"
#include <QtWidgets/QApplication>
#include "general.h"
#include <QThread>
QList<Point> morePoints;
int index = 0;
map<int, tuple<Point, float, float, mode>> points;
QList<float> qCircles;
int dpIndex = 0;
float scale = 200;
QList<QSvgWidget*> svgWidgets;
float frequency = 500;
QList<float> frequencyList;
float lastPointX = 0;
float lastPointY = 0;

float admitanceImagR = 0;
float admitanceRealR = 0;
float impedanceImagR = 0;
float impedanceRealR = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Smithtry1000 w;
    w.show();
    return a.exec();
}
