#include "TuneWidget.h"
#include "ui_TuneWidget.h"

TuneWidget::TuneWidget(QWidget *parent, CircuitElements* circuit)
	: QWidget(parent)
	, ui(new Ui::TuneWidget())
{
	ui->setupUi(this);
	circuitElements = circuit;
	tuned = new CircuitElements();
	connect(ui->OKButton, &QPushButton::clicked, this, &TuneWidget::OKButton_clicked);
	connect(ui->MinMaxButton, &QPushButton::clicked, this, &TuneWidget::MinMaxButton_clicked);
}

TuneWidget::~TuneWidget()
{
	delete ui;
}

void TuneWidget::OKButton_clicked()
{
	SystemParameters::tune = false;
}

/// <summary>
/// Получение сигнала о выбранном элементе
/// </summary>
/// <param name="elem"></param>
/// <param name="path"></param>
void TuneWidget::GetSignal(Element* elem, QString path)
{
	tuned->AddCircuitElements(elem);
	QGroupBox* box = new QGroupBox(this);
	box->resize(90,150);
	box->move(90 * (tuned->GetCircuitElements().size() - 1) + 10 * (tuned->GetCircuitElements().size() - 1), 0);
	box->setStyleSheet("background-color: rgb(64, 244, 208); ");
	box->show();
	boxes.append(box);
	QGroupBox* elementBox = new QGroupBox(box);
	elementBox->resize(86, 114);
	elementBox->move(2, 35);
	elementBox->setStyleSheet("background-color: rgb(64, 244, 208); color: rgb(0,0,0);");
	QString name;
	long long n=1;
	if (elem->GetMode() == CapacitorShunt || elem->GetMode() == CapacitorParallel)
	{
		name = "C";
		n = 1e12;
	}
	else if (elem->GetMode() == ResistorShunt || elem->GetMode() == ResistorParallel)
	{
		name = "R";
	}
	else if (elem->GetMode() == InductionShunt || elem->GetMode() == InductionParallel)
	{
		name = "L";
		n = 1e9;
	}
	elementBox->setTitle(name);
	elementBox->show();
	slidersBoxes.append(elementBox);
	QLabel* lbl = new QLabel(elementBox);
	lbl->resize(50, 15);
	lbl->move(25, 57);
	lbl->setText(QString::number(elem->GetValue()*n));
	maxValue.append(elem->GetValue() + elem->GetValue() * 0.3);
	minValue.append(elem->GetValue() - elem->GetValue() * 0.3);
	lbl->show();
	valueLabels.append(lbl);
	QLabel* maxlbl = new QLabel(elementBox);
	maxlbl->resize(50, 15);
	maxlbl->move(25, 15);
	maxlbl->setText(QString::number(maxValue[maxValue.size()-1] * n));
	maxlbl->show();
	maxLabels.append(maxlbl);
	QLabel* minlbl = new QLabel(elementBox);
	minlbl->resize(50, 15);
	minlbl->move(25, 94);
	minlbl->setText(QString::number(minValue[minValue.size() - 1] * n));
	minlbl->show();
	minLabels.append(minlbl);
	QSvgWidget* svgWidget = new QSvgWidget(box);
	svgWidget->load(QString(path));
	svgWidget->setGeometry(2, 2, 30, 30);
	svgWidget->show();
	widgets.append(svgWidget);
	QPushButton* btn = new QPushButton(box);
	btn->resize(50, 30);
	btn->setText("Remove");
	btn->move(35, 10);
	btn->setStyleSheet("background-color: rgb(72, 72, 72); color: rgb(0, 0, 0); ");
	btn->show();
	buttons.append(btn);
	QSlider* sld = new QSlider(elementBox);
	sld->resize(20, 80);
	sld->move(2, 25);
	sld->setStyleSheet("background-color: rgb(72, 72, 72); color: rgb(0, 0, 0); ");
	sld->setValue(50);
	sld->setMaximum(100);
	sld->show();
	sliders.append(sld);
	connect(sld, &QSlider::sliderMoved, this, &TuneWidget::ValueChanged);
	update();
}

void TuneWidget::paintEvent(QPaintEvent* event)
{
	int i = 0;
	for (auto& var : widgets)
	{
		long long n = 1;
		if (tuned->GetCircuitElements()[i]->GetMode() == InductionParallel || tuned->GetCircuitElements()[i]->GetMode() == InductionShunt)
		{
			n = 1e9;
		}
		else if (tuned->GetCircuitElements()[i]->GetMode() == CapacitorParallel || tuned->GetCircuitElements()[i]->GetMode() == CapacitorShunt)
		{
			n = 1e12;
		}
		valueLabels[i]->setText(QString::number(n*tuned->GetCircuitElements()[i]->GetValue()));
		QPainter painter(boxes[i]);
		painter.setPen(QPen(Qt::red, 2));
		QPoint first = QPoint(0, 50);
		QPoint second = QPoint(80, 50);
		QPoint third = QPoint(80, 140);
		QPoint fourth = QPoint(0, 140);
		painter.drawLine(first, second);
		painter.drawLine(second, third);
		painter.drawLine(third, fourth);
		painter.drawLine(fourth, first);
		i++;
	}
}

void TuneWidget::ValueChanged(int value)
{
	QSlider* sld = qobject_cast<QSlider*>(sender());
	int i = 0;
	for (auto var : sliders)
	{
		if (sliders[i] == sld)
		{
			break;
		}
		i++;
	}
	double step = (maxValue[i] - minValue[i]) / 100;
	double middle = (maxValue[i] + minValue[i]) / 2;
	tuned->GetCircuitElements()[i]->SetValue(minValue[i] + value * step);
	int j = 0;
	for (auto var : circuitElements->GetCircuitElements())
	{
		if (var == tuned->GetCircuitElements()[i])
		{
			break;
		}
		j++;
	}
	Complex z;
	Complex y;
	Complex tempZ;
	Complex tempY;
	for (j; j < circuitElements->GetCircuitElements().size(); j++)
	{
		if (j != 0)
		{
			z = circuitElements->GetCircuitElements()[j - 1]->GetParameter().at(Z);
			y = circuitElements->GetCircuitElements()[j - 1]->GetParameter().at(Y);
		}
		else
		{
			z = circuitElements->z;
			y = circuitElements->y;
		}

		float x;
		float y2;
		switch (circuitElements->GetCircuitElements()[j]->GetMode())
		{
			case ResistorShunt:
			{
				float r1 = z.real();
				float r2 = r1 + circuitElements->GetCircuitElements()[j]->GetValue();
				float step = 0.1;
				r2 = r2 / 50;
				tuple<float, float> tuple1 = circuitElements->GetCircuitElements()[j]->GetChartParameters().at(RealImpedance);
				tuple<float, float> tuple2 = circuitElements->GetCircuitElements()[j]->GetChartParameters().at(ImagImpedance);
				float r = get<0>(tuple2);
				float r3 = get<0>(tuple1);
				bool flag;
				bool flag2;
				if (r3 > r2)
				{
					flag = true;
				}
				else
				{
					flag = false;
				}
				if (circuitElements->GetCircuitElements()[j]->GetPoint().y < 0)
				{
					flag2 = true;
				}
				else
				{
					flag2 = false;
				}
				float t = get<1>(tuple2);
				while (r3 > r2 + 0.0001 || r3 < r2 - 0.0001)
				{
					if (r3 > r2 && flag == true)
					{
						step /= 2;
						flag = false;
					}
					else if (r3 < r2 && flag == false)
					{
						step /= 2;
						flag = true;
					}
					if ((flag == false && flag2 == false) || (flag == true && flag2 == true))
					{
						t += step;
					}
					else
					{
						t -= step;
					}
					float cos_t = cos(t);
					float sin_t = sin(t);
					x = 1 + (1 / r) * cos_t;
					y2 = (1 / r) + (1 / r) * sin_t;
					y2 = y2 * (-1);
					double circleRadius = 1 - ((pow(x, 2) + pow(y2, 2) - 1) / (2 * (x - 1)));
					double xCenter = 1 - circleRadius;
					double dx = x - xCenter;
					double dy = y2;
					double sin_t2 = dy;
					double cos_t2 = dx;
					float t1;
					if (y2 < 1e-6 && y2 >= 0)
					{
						if (y2 == 0 && x > 0.99)
						{
							t1 = 0;
						}
						else if (x > 0.99)
						{
							t1 = 2 * M_PI;
						}
						else
						{
							t1 = M_PI;
						}
					}
					else
					{
						t1 = atan(sin_t2 / cos_t2);
						if (cos_t2 < 0 && sin_t2 < 0)
						{
							t1 += M_PI;
						}
						else if (cos_t2 > 0 && sin_t2 < 0)
						{
							t1 = 2 * M_PI - abs(t1);
						}
						else if (sin_t2 > 0 && cos_t2 < 0)
						{
							t1 = M_PI - abs(t1);
						}
					}
					if (x - 1 != 0)
					{
						r3 = (cos(t1) - x) / (x - 1);
					}
				}
				Point point;
				point.x = x;
				point.y = y2;
				circuitElements->GetCircuitElements()[j]->SetPoint(point);
				Complex z2 = zCalculation(x, y2);
				Complex y3 = yCalculation(x, y2);
				map<parameterMode, Complex> parameter;
				parameter[Z] = z2;
				parameter[Y] = y3;
				map<chartMode, tuple<float, float>> chart;
				Complex rRealImpedance = impedanceRealChartParameters(x, y2);
				Complex rImagImpedance = impedanceImagChartParameters(x, y2);
				Complex rRealAdmitance = admitanceRealChartParameters(x, y2);
				Complex rImagAdmitance = admitanceImagChartParameters(x, y2);
				chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
				chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
				chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
				chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
				circuitElements->GetCircuitElements()[j]->SetChartParameters(chart);
				circuitElements->GetCircuitElements()[j]->SetParameter(parameter);
				SystemParameters::tuned = true;
				break;
			}
			/*case InductionShunt:
			{
				rImpedanceImagCalculation(get<0>(points[index - 1]).x, get<0>(points[index - 1]).y);
				float r1 = impedanceImagR;
				rImpedanceImagCalculation(lastPointX, lastPointY);
				float r2 = impedanceImagR;
				s1 = QString::number(round((r2 - r1) / (2 * M_PI * 1000000 * frequency) * 1000000000 * 10) / 10) + " nH";
				break;
			}
			case CapacitorShunt:
			{
				rImpedanceImagCalculation(get<0>(points[index - 1]).x, get<0>(points[index - 1]).y);
				float r1 = impedanceImagR;
				rImpedanceImagCalculation(lastPointX, lastPointY);
				float r2 = impedanceImagR;
				s1 = QString::number(round(10 * 1 / ((r1 - r2) * (2 * M_PI * 1000000 * frequency)) * 1000000000000) / 10) + " pF";
				break;
			}
			case ResistorParallel:
			{
				rAdmitanceRealCalculation(get<0>(points[index - 1]).x, get<0>(points[index - 1]).y);
				float r1 = admitanceRealR;
				rAdmitanceRealCalculation(lastPointX, lastPointY);
				float r2 = admitanceRealR;
				s1 = QString::number(round(1000 / (r2 - r1) * 10) / 10);
				break;
			}
			case InductionParallel:
			{
				rAdmitanceImagCalculation(get<0>(points[index - 1]).x, get<0>(points[index - 1]).y);
				float r1 = admitanceImagR;
				rAdmitanceImagCalculation(lastPointX, lastPointY);
				float r2 = admitanceImagR;
				s1 = QString::number(round(10 * M_PI / (r1 - r2) * 100 / frequency * 500) / 10) + " nH";
				break;
			}
			case CapacitorParallel:
			{
				rAdmitanceImagCalculation(get<0>(points[index - 1]).x, get<0>(points[index - 1]).y);
				float r1 = admitanceImagR;
				rAdmitanceImagCalculation(lastPointX, lastPointY);
				float r2 = admitanceImagR;
				s1 = QString::number(round((r2 - r1) / M_PI * 500 / frequency * 10) / 10) + " pF";
				break;
			}*/
		}
	}
	update();
}

void TuneWidget::MinMaxButton_clicked()
{
	int i = 0;
	for (auto var : sliders)
	{
		long long n = 1;
		if (tuned->GetCircuitElements()[i]->GetMode() == InductionParallel || tuned->GetCircuitElements()[i]->GetMode() == InductionShunt)
		{
			n = 1e9;
		}
		else if (tuned->GetCircuitElements()[i]->GetMode() == CapacitorParallel || tuned->GetCircuitElements()[i]->GetMode() == CapacitorShunt)
		{
			n = 1e12;
		}
		maxValue[i]=(tuned->GetCircuitElements()[i]->GetValue() + tuned->GetCircuitElements()[i]->GetValue() * 0.3);
		minValue[i]=(tuned->GetCircuitElements()[i]->GetValue() - tuned->GetCircuitElements()[i]->GetValue() * 0.3);
		minLabels[i]->setText(QString::number(minValue[i] * n));
		maxLabels[i]->setText(QString::number(maxValue[i] * n));
		var->setValue(50);
		i++;
	}
	update();
}

Complex TuneWidget::zCalculation(float x, float y)
{
	rImpedanceRealCalculation(x, y);
	rImpedanceImagCalculation(x, y);
	return Complex(impedanceRealR, impedanceImagR);
}

Complex TuneWidget::yCalculation(float x, float y)
{
	rAdmitanceRealCalculation(x, y);
	rAdmitanceImagCalculation(x, y);
	return Complex(admitanceRealR, admitanceImagR);
}

Complex TuneWidget::impedanceRealChartParameters(float x, float y)
{
	double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
	double xCenter = 1 - circleRadius;
	double dx = x - xCenter;
	double dy = y;
	double sin_t = dy;
	double cos_t = dx;
	float t1, r1;
	if (y < 1e-6 && y >= 0)
	{
		if (y == 0 && x > 0.99)
		{
			t1 = 0;
		}
		else if (x > 0.99)
		{
			t1 = 2 * M_PI;
		}
		else
		{
			t1 = M_PI;
		}
	}
	else
	{
		t1 = atan(sin_t / cos_t);
		if (cos_t < 0 && sin_t < 0)
		{
			t1 += M_PI;
		}
		else if (cos_t > 0 && sin_t < 0)
		{
			t1 = 2 * M_PI - abs(t1);
		}
		else if (sin_t > 0 && cos_t < 0)
		{
			t1 = M_PI - abs(t1);
		}
	}
	if (x - 1 != 0)
	{
		r1 = (cos(t1) - x) / (x - 1);
	}
	return Complex(r1, t1);
}

Complex TuneWidget::admitanceRealChartParameters(float x, float y)
{
	double circleRadius = -1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 + 2 * x));
	double xCenter = -1 - circleRadius;
	double dx = x - xCenter;
	double dy = y;
	dy *= -1;
	double sin_t = dy;
	double cos_t = dx;
	float t1, r1;
	if (y <= 1e-6 && y >= 1e-6)
	{
		if (y == 0 && x < -0.99)
		{
			t1 = 0;
		}
		else if (x < -0.99)
		{
			t1 = 2 * M_PI;
		}
		else
		{
			t1 = M_PI;
		}
	}
	else
	{
		t1 = atan(sin_t / cos_t);
		if (cos_t < 0 && sin_t < 0)
		{
			t1 = abs(t1) - M_PI;
		}
		else if (sin_t > 0 && cos_t < 0)
		{
			t1 = M_PI - abs(t1);
		}
	}
	if (x - 1 != 0)
	{
		r1 = abs((cos(t1) - x) / (x + 1));
	}
	return Complex(r1, t1);
}

Complex TuneWidget::impedanceImagChartParameters(float x, float y)
{
	double cos_t;
	double sin_t;
	double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
	double xCenter = 1 - circleRadius;
	double dx = x - xCenter;
	double dy = y;
	sin_t = dy;
	cos_t = dx;
	float t1, r1;
	if (abs(y) < 1e-6 && abs(y) >= 0)
	{
		if (y == 0 && x > 0.99)
		{
			t1 = 0.0001;
		}
		else if (x > 0.99)
		{
			t1 = 2 * M_PI;
		}
		else
		{
			t1 = M_PI;
		}
	}
	else
	{
		t1 = atan(cos_t / sin_t);
		if (y < 0)
		{
			t1 += M_PI;
		}
		else
		{
			t1 += 2 * M_PI;
		}
	}
	if (x - 1 != 0)
	{
		r1 = cos(t1) / (x - 1);
	}
	else
	{
		r1 = (1 + sin(t1)) / y;
	}
	if (y < 0)
	{
		r1 = abs(r1);
	}
	else
	{
		r1 = abs(r1) * (-1);
	}
	if (y == 0)
	{
		r1 = 0;
	}
	return Complex(r1, t1);
}

Complex TuneWidget::admitanceImagChartParameters(float x, float y)
{
	double cos_t;
	double sin_t;
	double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y, 2)) / (-2 * y);
	double yCenter = -circleRadius;
	double dx = x + 1;
	double dy = y - yCenter;
	sin_t = -dy;
	cos_t = dx;
	float t1, r1;
	if (abs(y) <= 1e-6 && abs(y) >= 0)
	{
		if (y == 0 && x < -0.99)
		{
			t1 = M_PI / 2;
		}
		else if (x < -0.99)
		{
			t1 = -M_PI / 2;
		}
		else
		{
			t1 = 0;
		}
	}
	else
	{
		t1 = atan(sin_t / cos_t);
	}
	if (x + 1 != 0)
	{
		r1 = cos(t1) / (x + 1);
	}
	else
	{
		r1 = (1 + sin(t1)) / y;
	}
	if (y > 0)
	{
		r1 *= -1;
	}
	if (y == 0)
	{
		r1 = 0;
		t1 = -M_PI / 2;
	}
	return Complex(r1, t1);
}

void TuneWidget::rImpedanceRealCalculation(float x, float y)
{
	double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
	double xCenter = 1 - circleRadius;
	double dx = x - xCenter;
	double dy = y;
	double sin_t = dy;
	double cos_t = dx;
	float t1;
	if (y < 1e-6 && y >= 0)
	{
		if (y == 0 && x > 0.99)
		{
			t1 = 0;
		}
		else if (x > 0.99)
		{
			t1 = 2 * M_PI;
		}
		else
		{
			t1 = M_PI;
		}
	}
	else
	{
		t1 = atan(sin_t / cos_t);
		if (cos_t < 0 && sin_t < 0)
		{
			t1 += M_PI;
		}
		else if (cos_t > 0 && sin_t < 0)
		{
			t1 = 2 * M_PI - abs(t1);
		}
		else if (sin_t > 0 && cos_t < 0)
		{
			t1 = M_PI - abs(t1);
		}
	}
	if (x - 1 != 0)
	{
		impedanceRealR = abs((cos(t1) - x) / (x - 1));
	}
	impedanceRealR *= 50;
}

void TuneWidget::rAdmitanceRealCalculation(float x, float y)
{
	double circleRadius = -1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 + 2 * x));
	double xCenter = -1 - circleRadius;
	double dx = x - xCenter;
	double dy = y;
	dy *= -1;
	double sin_t = dy;
	double cos_t = dx;
	float t1;
	if (y < 1e-6 && y >= 0)
	{
		if (y == 0 && x < -0.99)
		{
			t1 = 0;
		}
		else if (x < -0.99)
		{
			t1 = 2 * M_PI;
		}
		else
		{
			t1 = M_PI;
		}
	}
	else
	{
		t1 = atan(sin_t / cos_t);
		if (cos_t < 0 && sin_t < 0)
		{
			t1 = abs(t1) - M_PI;
		}
		else if (sin_t > 0 && cos_t < 0)
		{
			t1 = M_PI - abs(t1);
		}
	}
	if (x - 1 != 0)
	{
		admitanceRealR = abs((cos(t1) - x) / (x + 1));
	}
	admitanceRealR *= 20;
}

void TuneWidget::rImpedanceImagCalculation(float x, float y)
{
	double cos_t;
	double sin_t;
	double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
	double xCenter = 1 - circleRadius;
	double dx = x - xCenter;
	double dy = y;
	sin_t = dy;
	cos_t = dx;
	float t1;
	if (abs(y) < 1e-6 && abs(y) >= 0)
	{
		if (y == 0 && x > 0.99)
		{
			t1 = 0.0001;
		}
		else if (x > 0.99)
		{
			t1 = 2 * M_PI;
		}
		else
		{
			t1 = M_PI;
		}
	}
	else
	{
		t1 = atan(cos_t / sin_t);
		if (y < 0)
		{
			t1 += M_PI;
		}
		else
		{
			t1 += 2 * M_PI;
		}
	}
	if (x - 1 != 0)
	{
		impedanceImagR = cos(t1) / (x - 1);
	}
	else
	{
		impedanceImagR = (1 + sin(t1)) / y;
	}
	if (y < 0)
	{
		impedanceImagR = abs(impedanceImagR);
	}
	else
	{
		impedanceImagR = abs(impedanceImagR) * (-1);
	}
	if (y == 0 || (abs(y) < 1e-7 && x < 0.999))
	{
		impedanceImagR = 0;
	}
	impedanceImagR *= 50;
}

void TuneWidget::rAdmitanceImagCalculation(float x, float y)
{
	double cos_t;
	double sin_t;
	double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y, 2)) / (-2 * y);
	double yCenter = -circleRadius;
	double dx = x + 1;
	double dy = y - yCenter;
	sin_t = -dy;
	cos_t = dx;
	float t1;
	if (abs(y) < 1e-6 && abs(y) >= 0)
	{
		if (y == 0 && x < -0.99)
		{
			t1 = M_PI / 2;
		}
		else if (x < -0.99)
		{
			t1 = -M_PI / 2;
		}
		else
		{
			t1 = 0;
		}
	}
	else
	{
		t1 = atan(sin_t / cos_t);
	}
	if (x + 1 != 0)
	{
		admitanceImagR = cos(t1) / (x + 1);
	}
	else
	{
		admitanceImagR = (1 + sin(t1)) / y;
	}
	if (y > 0)
	{
		admitanceImagR *= -1;
	}
	if (y == 0 || (abs(y) < 1e-7 && x > -0.999))
	{
		admitanceImagR = 0;
	}
	admitanceImagR *= -20;
}