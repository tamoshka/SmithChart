#include "Smithtry1000.h"
#include <QtWidgets/QApplication>
#include "general.h"
#include "newgeneral.h"
#include <QThread>
#include "circuitElements.h"
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
QString fileName = "";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	Table t1;
	Tests t2;
	GrafOne g1;
	GrafTwo g2;
	SDiagram1 d1(SDiagram1::S12);
	SDiagram1 d2(SDiagram1::S21);
	SDiagram2 d3(SDiagram2::S11);
	SDiagram2 d4(SDiagram2::S22);

	QObject::connect(&t2, &Tests::rowSelected, &g1, &GrafOne::highlightPoint);
	QObject::connect(&t2, &Tests::rowSelected, &g2, &GrafTwo::highlightPoint);
	QObject::connect(&t1, &Table::rowSelected, &g2, &GrafTwo::highlightPoint);
	QObject::connect(&t2, &Tests::rowClicked, &d1, &SDiagram1::highlightPoint);
	QObject::connect(&t2, &Tests::rowClicked, &d2, &SDiagram1::highlightPoint);
	QObject::connect(&t2, &Tests::rowClicked, &d3, &SDiagram2::highlightPoint);
	QObject::connect(&t2, &Tests::rowClicked, &d4, &SDiagram2::highlightPoint);

	SParameters* sParameters = new SParameters(t1, t2, g1, g2,d1, d2, d3, d4);
    Smithtry1000 w = Smithtry1000(nullptr, sParameters);
    w.show();
    return a.exec();
}
