#include "S21Param.h"
#include "newgeneral.h"
#include "S2p.h"
S21Param::S21Param(QWidget* parent)
	: QWidget(parent),
	mBackGroundColor(255, 255, 255)
{
	setFixedSize(600, 600);
	setMinimumSize(450, 450);
	setMaximumSize(900, 900); 
	this->setStyleSheet("background-color: white;");
}

void S21Param::Load()
{
	TouchstoneFile t;
	spar_t s;
	s = t.Load2P(fileName.toStdString().c_str());
	max = 0;
	for (int i = 0; i < s.S[1][0].size(); i++)
	{
		z.append(s.S[1][0][i].real());
		if (z[i] > max)
		{
			max = z[i];
		}
	}

	for (int i = 0; i < s.S[1][0].size(); i++)
	{
		k = z[i] / max;
		z[i] = k;
		angle.append(s.S[1][0][i].imag());
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

void S21Param::highlightPoint(int index)
{
	highlightedPoint = index;
	update();
}

void S21Param::paintEvent(QPaintEvent* event)
{
	TouchstoneFile t;
	spar_t s;
	s = t.Load2P(fileName.toStdString().c_str());

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
		painter.setPen(QPen(Qt::blue, 1));
		painter.drawEllipse(center, scaledRadius, scaledRadius);

		QString label = QString::number(max / 4 * (i + 1), 'f', 3);
		QPointF labelPos = center + QPointF(scaledRadius - 20 * scaleFactor, 0);
		painter.drawText(labelPos, label);
	}

	painter.setPen(QPen(Qt::black, 1));
	painter.drawLine(QPointF(center.x(), center.y() - maxCircleRadius),
		QPointF(center.x(), center.y() + maxCircleRadius));
	painter.drawLine(QPointF(center.x() - maxCircleRadius, center.y()),
		QPointF(center.x() + maxCircleRadius, center.y()));

	float pointScale = 2.0f * scaleFactor;
	float lineWidth = 1.0f * scaleFactor;

	painter.setPen(QPen(Qt::red, lineWidth));
	for (int i = 0; i < x.size(); i++) {
		QPointF point = center + QPointF(x[i] * 200 * scaleFactor, y[i] * 200 * scaleFactor);
		painter.drawEllipse(point, pointScale, pointScale);

		if (i > 0) {
			QPointF prevPoint = center + QPointF(x[i - 1] * 200 * scaleFactor, y[i - 1] * 200 * scaleFactor);
			painter.setPen(QPen(Qt::black, lineWidth));
			painter.drawLine(prevPoint, point);
			painter.setPen(QPen(Qt::red, lineWidth));
		}
	}

	if (highlightedPoint >= 0 && highlightedPoint < x.size()) {
		QPointF highlightPoint = center + QPointF(x[highlightedPoint] * 200 * scaleFactor,
			y[highlightedPoint] * 200 * scaleFactor);
		painter.setPen(QPen(Qt::black, lineWidth));
		painter.setBrush(Qt::black);
		painter.drawEllipse(highlightPoint, 3 * scaleFactor, 3 * scaleFactor);

		complex_t s01 = s.S[1][0][highlightedPoint];
		double magnitude = abs(s01);
		double phase = arg(s01) * 180 / M_PI;

		QString highlightLabel = QString("[%1] S21: %2∠%3°")
			.arg(highlightedPoint + 1)
			.arg(s01.real(), 0, 'f', 3)
			.arg(s01.imag(), 0, 'f', 2);

		QPointF textPos = highlightPoint + QPointF(10 * scaleFactor, -10 * scaleFactor);
		painter.drawText(textPos, highlightLabel);
	}
}

S21Param::~S21Param()
{
}

