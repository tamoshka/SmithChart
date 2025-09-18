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
	//Единичный круг справа
	static QColor MainImpedanceColor;
	//Единичный круг слева
	static QColor MainAdmitanceColor;
	//Цвета точек на диаграмме
	static QColor DataPointsColor;
	//Предлогаемый маршрут передвижения мышки
	static QColor RootColor;
	//Годограф
	static QColor ElementsColor;
	static QColor BackgroundColor;
	//S ���������, ���
	static QColor s11GrafColor;
	static QColor s22GrafColor;
	static QColor magGrafColor;
	static QColor msgGrafColor;
	static QColor kGrafColor;
	static QColor muGrafColor;
	static QColor ampS11Color;
	static QColor ampS21Color;
	static QColor circleS12;
	static QColor circleS21;
	static QColor gridGrafOneColor;
	static QColor gridGrafTwoColor;
	static QColor gridAmpFrColor;

	static QColor QCirclesColor;
	static QColor VSWRColor;
	//0 - MainCircleColor, 1 - ImpedanceColor, 2 - AdmitanceColor, 3 - DataPointsColor, 4 - RootColor, 5 - ElementsColor, 6 - BackgroundColor, 7 - MainImpedanceColor, 8 - MainAdmitanceColor
	//9 - VSWRColor, 10 - QCirclesColor
	static QList<double> linesWidth;
	//0-
	static QList<int>sPlotline;
	static QList<int>ampFrline;
	static mode Model;
	static double frequency;
	static double Im;
	static double Re;
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
	static bool colorChanged;
	static double alpha;
	static double lambda;
	static bool sizeChanged;
	static systemMode sys;
	static QSet<double> VSWRCircles;
	static QSet<double> QCircles;

	static void rImpedanceRealCalculation(double, double);
	static void rImpedanceImagCalculation(double, double);
	static void rAdmitanceRealCalculation(double, double);
	static void rAdmitanceImagCalculation(double, double);

	static Complex zCalculation(double, double);
	static Complex yCalculation(double, double);

	static Complex impedanceRealChartParameters(double, double);
	static Complex impedanceImagChartParameters(double, double);
	static Complex admitanceRealChartParameters(double, double);
	static Complex admitanceImagChartParameters(double, double);
};