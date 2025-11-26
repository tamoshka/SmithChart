#include "SDiagram1.h"
#include "S2p.h"
#include "math.h"
#include <QString>
#include "systemParameters.h"
/// <summary>
/// Конструктор класса SDiagram1
/// </summary>
/// <param name="type">Тип, S12/S21.</param>
/// <param name="parent"></param>
SDiagram1::SDiagram1(ParameterType type,QWidget* parent)
	: QWidget(parent),
	mBackGroundColor(255, 255, 255),
	currentType(type)
{
	setFixedSize(600, 600);
	setMinimumSize(450, 450);
	setMaximumSize(900, 900);
	this->setStyleSheet("background-color: white;");
}

/// <summary>
/// Загрузка параметров из SnP файла.
/// </summary>
void SDiagram1::Load()
{
	extern QString fileName;
	auto extension = fileName.toStdString();
	size_t last_dot = extension.find_last_of('.');
	extension = last_dot != string::npos ? extension.substr(last_dot + 1) : "";

	TouchstoneFile t;
	spar_t s;
	s = t.Load2P(fileName.toStdString().c_str());
	z.clear();
	x.clear();
	y.clear();
	angle.clear();
	max = 0;

	//Выбор для S12,S21
	const auto& sParam = [&]() -> const std::vector<complex_t>&
	{
		switch (currentType)
		{
			case S12:
				return s.S[0][1];
				break;
			case S21:
				return s.S[1][0];
				break;
			default:
				return s.S[0][1];
				break;
		}
	}();

	for (int i = 0; i < sParam.size(); i++)
	{
		z.append(sParam[i].real());
		if (z[i] > max)
		{
			max = z[i];
		}
	}

	for (int i = 0; i < sParam.size(); i++)
	{
		k = z[i] / max;
		z[i] = k;
		angle.append(sParam[i].imag());
		double cosin;
		if (angle[i] > 90)
		{
			cosin = cos((180 - angle[i]) * M_PI / 180);
		}
		else if (angle[i] > 0 && angle[i] <= 90)
		{
			cosin = cos(angle[i] * M_PI / 180);
		}
		else if (angle[i] > -90 && angle[i] <= 0)
		{
			cosin = cos(-angle[i] * M_PI / 180);
		}
		else
		{
			cosin = cos((abs(-180 - angle[i])) * M_PI / 180);
		}
		x.append(cosin * z[i]);
		if (abs(angle[i]) > 90)
		{
			x[i] *= -1;
		}
		y.append(sqrt(pow(z[i], 2) - pow(x[i], 2)));
		if (angle[i] < 0)
		{
			y[i] *= -1;
		}
		y[i] *= -1;
	}
}

/// <summary>
/// Отображение подсвечиваемой точки.
/// </summary>
/// <param name="index">Номер точки.</param>
void SDiagram1::highlightPoint(int index)
{
	highlightedPoint = index;
	update();
}

/// <summary>
/// Отрисовка виджета.
/// </summary>
/// <param name="event"></param>
void SDiagram1::paintEvent(QPaintEvent* event)
{
	extern QString fileName;
	auto extension = fileName.toStdString();
	size_t last_dot = extension.find_last_of('.');
	extension = last_dot != string::npos ? extension.substr(last_dot + 1) : "";

	TouchstoneFile t;
	spar_t s;
	s = t.Load2P(fileName.toStdString().c_str());

	QPen circle;
	//Выбор для S12,S21
	const auto& sParam = [&]() -> const std::vector<complex_t>&
	{

		switch (currentType) 
		{
			case S12: 
				circle = QPen(SystemParameters::circleS12, SystemParameters::sPlotline[0]);
				return s.S[0][1];
				break;
			case S21: 
				circle = QPen(SystemParameters::circleS21, SystemParameters::sPlotline[1]);
				return s.S[1][0];
				break;
			default: 
				circle = QPen(SystemParameters::circleS12, SystemParameters::sPlotline[0]);
				return s.S[0][1];
				break;
		}
	}();
	
	QPainter painter(this);

	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::blue);

	QRectF widgetRect = this->rect();
	QPointF center = widgetRect.center();
	float scaleFactor = qMin(widgetRect.width(), widgetRect.height()) / 450.0f;

	float maxCircleRadius = 200 * scaleFactor;
	QVector<float> radii = { 50, 100, 150, 200 };
	QFont font = painter.font();
	font.setPointSize(8 * scaleFactor);
	painter.setFont(font);

	for (int i = 0; i < 4; i++)
	{
		float scaledRadius = radii[i] * scaleFactor;
		painter.setPen(circle);
		painter.drawEllipse(center, scaledRadius, scaledRadius);
		painter.setPen(QPen(Qt::black, 1));
		QString label = QString::number(max / 4 * (i + 1), 'f', 3);
		QPointF labelPos = center + QPointF(scaledRadius - 20 * scaleFactor, 0);
		painter.drawText(labelPos, label);
	}

	painter.setPen(QPen(Qt::black, 1));
	painter.drawLine(QPointF(center.x(), center.y() - maxCircleRadius),QPointF(center.x(), center.y() + maxCircleRadius));
	painter.drawLine(QPointF(center.x() - maxCircleRadius, center.y()),QPointF(center.x() + maxCircleRadius, center.y()));

	float pointScale = 2.0f * scaleFactor;
	float lineWidth = 1.0f * scaleFactor;

	painter.setPen(QPen(Qt::red, lineWidth));
	for (int i = 0; i < x.size(); i++) 
	{
		QPointF point = center + QPointF(x[i] * 200 * scaleFactor, y[i] * 200 * scaleFactor);
		painter.drawEllipse(point, pointScale, pointScale);

		if (i > 0) 
		{
			QPointF prevPoint = center + QPointF(x[i - 1] * 200 * scaleFactor, y[i - 1] * 200 * scaleFactor);
			painter.setPen(QPen(Qt::black, lineWidth));
			painter.drawLine(prevPoint, point);
			painter.setPen(QPen(Qt::red, lineWidth));
		}
	}

	if (highlightedPoint >= 0 && highlightedPoint < x.size()) 
	{
		QPointF highlightPoint = center + QPointF(x[highlightedPoint] * 200 * scaleFactor,y[highlightedPoint] * 200 * scaleFactor);
		painter.setPen(QPen(Qt::black, lineWidth));
		painter.setBrush(Qt::black);
		painter.drawEllipse(highlightPoint, 3 * scaleFactor, 3 * scaleFactor);

		complex_t sPoint = sParam[highlightedPoint];
		double magnitude = abs(sPoint);
		double phase = arg(sPoint) * 180 / M_PI;

		QString highlightLabel = QString("[%1] S: %2∠%3°")
			.arg(highlightedPoint + 1)
			.arg(sPoint.real(), 0, 'f', 3)
			.arg(sPoint.imag(), 0, 'f', 2);

		QPointF textPos = highlightPoint + QPointF(10 * scaleFactor, -10 * scaleFactor);
		painter.drawText(textPos, highlightLabel);
	}
}

/// <summary>
/// Деструктор класса SDiagram1.
/// </summary>
SDiagram1::~SDiagram1()
{
}