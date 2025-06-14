#include "general.h"
#include <QColor>

static class SystemParameters
{
public:
	static QColor AdmitanceColor=QColor::red;
	static QColor ImpedanceColor = QColor::blue;
	static QColor QCirclesColor;
	static QColor VSWRColor;
	static QColor ElementsColor;
	static QColor DataPointsColor;
	static QColor BackgroundColor;
	static QColor MainCircleColor;
	static mode Model;
	static float frequency;
	static QList<Point> morePoints;
	static int index;
	static dpIndex;
	static float lastPointX;
	static float lastPointY;
	static float scale;
	static QList<QSvgWidget*> svgWidgets;
	static float impedanceRealR;
	static float impedanceImagR;
	static float admitanceRealR;
	static float admitanceImagR;
};