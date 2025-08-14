#include "general.h"
#include <QColor>

class SystemParameters
{
public:
	static QColor MainCircleColor;
	static QColor ImpedanceColor;
	static QColor AdmitanceColor;
	static QColor DataPointsColor;
	static QColor RootColor;
	static QColor ElementsColor;
	static QColor BackgroundColor;
	static QColor QCirclesColor;
	static QColor VSWRColor;
	//0 - MainCircleColor, 1 - ImpedanceColor, 2 - AdmitanceColor, 3 - DataPointsColor, 4 - RootColor, 5 - ElementsColor, 6 - BackgroundColor
	static QList<double> linesWidth;
	static mode Model;
	static float frequency;
	static QList<Point> morePoints;
	static int index;
	static int dpIndex;
	static float lastPointX;
	static float lastPointY;
	static float scale;
	static QList<QSvgWidget*> svgWidgets;
	static float impedanceRealR;
	static float impedanceImagR;
	static float admitanceRealR;
	static float admitanceImagR;
	static bool circuitHover;
	static bool tune;
	static bool tuned;
};