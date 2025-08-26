#include "Element.h"
#include <QColor>

class SystemParameters
{
public:
	//Главный круг
	static QColor MainCircleColor;
	//Круги справа
	static QColor ImpedanceColor;
	//Круги слева
	static QColor AdmitanceColor;
	//Цвета точек на диаграмме
	static QColor DataPointsColor;
	//Предлогаемый маршрут передвижения мышки
	static QColor RootColor;
	//Годограф
	static QColor ElementsColor;
	static QColor BackgroundColor;

	static QColor QCirclesColor;
	static QColor VSWRColor;
	//0 - MainCircleColor, 1 - ImpedanceColor, 2 - AdmitanceColor, 3 - DataPointsColor, 4 - RootColor, 5 - ElementsColor, 6 - BackgroundColor
	static QList<double> linesWidth;
	static mode Model;
	static double frequency;
	static QList<Point> morePoints;
	static int index;
	static int dpIndex;
	static double lastPointX;
	static double lastPointY;
	static double scale;
	static QList<QSvgWidget*> svgWidgets;
	static double impedanceRealR;
	static double impedanceImagR;
	static double admitanceRealR;
	static double admitanceImagR;
	static bool circuitHover;
	static bool tune;
	static bool tuned;
	static bool tuneBlock;
	static QList<Element*> tunedElements;
	static double er;
	static double z0line;
};