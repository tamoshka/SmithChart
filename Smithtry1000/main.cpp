#include "Smithtry1000.h"
#include <QtWidgets/QApplication>
#include "general.h"
#include <QThread>
#include "circuitElements.h"
QList<Point> morePoints;
map<int, tuple<Point, bool>> allPoints;
int point_index = 0;
int allpointindex = 0;
map<int, tuple<Point, long double, long double, mode>> points;
int dpIndex = 0;
double scale = 200;
QList<QSvgWidget*> svgWidgets;
long double frequency = 500;
QList<long double> frequencyList;
long double lastPointX = 0;
long double lastPointY = 0;

QString fileName = "";

int main(int argc, char *argv[])
{
	QCoreApplication::setApplicationName("Smithtry1000");
	QCoreApplication::setApplicationVersion("1.0");
	QCoreApplication::setOrganizationName("Tamoshka");
	QCoreApplication::setOrganizationDomain("Tamoshka.com");
	try 
	{
		SystemParameters::deserializeFromJson();
	}
	catch(exception e)
	{

	}
    QApplication a(argc, argv);

	GrafOne g1;
	GrafTwo g2;
	SDiagram1 d1(SDiagram1::S12);
	SDiagram1 d2(SDiagram1::S21);
	SDiagram2 d3(SDiagram2::S11);
	SDiagram2 d4(SDiagram2::S22);
	ColourSetting set;
	SParamTable stable1(SParamTable::STable1);
	SParamTable stable2(SParamTable::STable2);

	//Сигналы
	QObject::connect(&stable1, &SParamTable::rowClicked, &d1, &SDiagram1::highlightPoint);
	QObject::connect(&stable1, &SParamTable::rowSelected, &d2, &SDiagram1::highlightPoint);
	QObject::connect(&stable1, &SParamTable::rowClicked, &d3, &SDiagram2::highlightPoint);
	QObject::connect(&stable1, &SParamTable::rowSelected, &d4, &SDiagram2::highlightPoint);
	//Графики
	QObject::connect(&stable1, &SParamTable::rowSelected, &g1, &GrafOne::highlightPoint);
	QObject::connect(&stable1, &SParamTable::rowSelected, &g2, &GrafTwo::highlightPoint);
	QObject::connect(&stable2, &SParamTable::rowSelected, &g2, &GrafTwo::highlightPoint);
	QObject::connect(&set, &ColourSetting::grafOneColor, &g1, &GrafOne::updateGrafOneColor);
	QObject::connect(&set, &ColourSetting::grafTwoColor, &g2, &GrafTwo::updateGrafTwoColor);

	SParameters* sParameters = new SParameters(g1, g2, d1, d2, d3, d4, stable1, stable2, set);
    Smithtry1000 w = Smithtry1000(nullptr, sParameters);
	QObject::connect(&w, &Smithtry1000::left, w.auxiliaryWidget, &CircuitWidget::getLeft);
    w.show();
    return a.exec();
}