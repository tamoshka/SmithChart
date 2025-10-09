#include "Element.h"
#include <QColor>

/// <summary>
/// Статический класс, хранящий все цвета, ряд методов и параметров необходимых другим классам (сервисный класс).
/// </summary>
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
	//Главный круг
	static QColor MainCircleColorDefault;
	//Круги справа
	static QColor ImpedanceColorDefault;
	//Круги слева
	static QColor AdmitanceColorDefault;
	//Единичный круг справа
	static QColor MainImpedanceColorDefault;
	//Единичный круг слева
	static QColor MainAdmitanceColorDefault;
	//Цвета точек на диаграмме
	static QColor DataPointsColorDefault;
	//Предлогаемый маршрут передвижения мышки
	static QColor RootColorDefault;
	//Годограф
	static QColor ElementsColorDefault;
	static QColor BackgroundColorDefault;
	//S ���������, ���
	static QColor s11GrafColorDefault;
	static QColor s22GrafColorDefault;
	static QColor magGrafColorDefault;
	static QColor msgGrafColorDefault;
	static QColor kGrafColorDefault;
	static QColor muGrafColorDefault;
	static QColor ampS11ColorDefault;
	static QColor ampS21ColorDefault;
	static QColor circleS12Default;
	static QColor circleS21Default;
	static QColor gridGrafOneColorDefault;
	static QColor gridGrafTwoColorDefault;
	static QColor gridAmpFrColorDefault;

	static QColor QCirclesColorDefault;
	static QColor VSWRColorDefault;
	//0 - MainCircleColor, 1 - ImpedanceColor, 2 - AdmitanceColor, 3 - DataPointsColor, 4 - RootColor, 5 - ElementsColor, 6 - BackgroundColor, 7 - MainImpedanceColor, 8 - MainAdmitanceColor
	//9 - VSWRColor, 10 - QCirclesColor
	static QList<double> linesWidth;
	//0-
	static QList<int>sPlotline;
	static QList<int>ampFrline;
	//0 - MainCircleColor, 1 - ImpedanceColor, 2 - AdmitanceColor, 3 - DataPointsColor, 4 - RootColor, 5 - ElementsColor, 6 - BackgroundColor, 7 - MainImpedanceColor, 8 - MainAdmitanceColor
	//9 - VSWRColor, 10 - QCirclesColor
	static QList<double> linesWidthDefault;
	//0-
	static QList<int>sPlotlineDefault;
	static QList<int>ampFrlineDefault;
	static mode Model;
	static long double frequency;
	static long double Im;
	static long double Re;
	static QList<Point> morePoints;
	static int index;
	static int dpIndex;
	static long double lastPointX;
	static long double lastPointY;
	static long double scale;
	static QList<QSvgWidget*> svgWidgets;
	static long double impedanceRealR;
	static long double impedanceImagR;
	static long double admitanceRealR;
	static long double admitanceImagR;
	static bool circuitHover;
	static bool tune;
	static bool tuned;
	static bool tuneBlock;
	static bool resistorLinear;
	static QList<Element*> tunedElements;
	static double er;
	static long double z0line;
	static bool colorChanged;
	static double alpha;
	static double lambda;
	static bool sizeChanged;
	static systemMode sys;
	static valueMode val;
	static QSet<double> VSWRCircles;
	static QSet<double> QCircles;
	//0 - Диаграмма, 1 - Цепь
	static int saved;

	static void SaveToJSON();
	static void deserializeFromJson();

	static void rImpedanceRealCalculation(long double, long double);
	static void rImpedanceImagCalculation(long double, long double);
	static void rAdmitanceRealCalculation(long double, long double);
	static void rAdmitanceImagCalculation(long double, long double);

	static Complex zCalculation(long double, long double);
	static Complex yCalculation(long double, long double);

	static Complex impedanceRealChartParameters(long double, long double);
	static Complex impedanceImagChartParameters(long double, long double);
	static Complex admitanceRealChartParameters(long double, long double);
	static Complex admitanceImagChartParameters(long double, long double);
private:
	static QString colorToString(const QColor&);
	static QColor stringToColor(const QString&);
};