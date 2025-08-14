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
	S11Param g3;
	S22Param g4;
	S12Param g5;
	S21Param g6;

	QObject::connect(&t2, &Tests::rowClicked, &g5, &S12Param::highlightPoint);
	QObject::connect(&t2, &Tests::rowClicked, &g3, &S11Param::highlightPoint);
	QObject::connect(&t2, &Tests::rowClicked, &g6, &S21Param::highlightPoint);
	QObject::connect(&t2, &Tests::rowClicked, &g4, &S22Param::highlightPoint);
	QObject::connect(&t2, &Tests::rowSelected, &g1, &GrafOne::highlightPoint);
	QObject::connect(&t2, &Tests::rowSelected, &g2, &GrafTwo::highlightPoint);
	QObject::connect(&t1, &Table::rowSelected, &g2, &GrafTwo::highlightPoint);
	SParameters* sParameters = new SParameters(t1, t2, g1, g2, g3, g4, g5, g6);
    Smithtry1000 w = Smithtry1000(nullptr, sParameters);
	QObject::connect(&w, &Smithtry1000::left, w.auxiliaryWidget, &CircuitWidget::getLeft);
    w.show();
    return a.exec();
}
