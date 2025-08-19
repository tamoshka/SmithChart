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
	connect(ui->RemoveAllButton, &QPushButton::clicked, this, &TuneWidget::RemoveAll);
}

TuneWidget::~TuneWidget()
{
	delete ui;
}

void TuneWidget::OKButton_clicked()
{
	SystemParameters::tune = false;
}

void TuneWidget::closeEvent(QCloseEvent *event)
{
	SystemParameters::tune = false;
}

void TuneWidget::GetSignal(Element* elem, QString path)
{
	SystemParameters::tuneBlock = true;
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
	else if (elem->GetMode() == Line)
	{

	}
	else if (elem->GetMode() == OSLine)
	{

	}
	else if (elem->GetMode() == SSLine)
	{

	}
	elementBox->setTitle(name);
	elementBox->show();
	slidersBoxes.append(elementBox);
	QLabel* lbl = new QLabel(elementBox);
	lbl->resize(50, 15);
	lbl->move(25, 57);
	lbl->setText(QString::number(elem->GetValue()*n));
	maxValue.append(elem->GetValue() + elem->GetValue() * 0.5);
	minValue.append(elem->GetValue() - elem->GetValue() * 0.5);
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
	connect(btn, &QPushButton::clicked, this, &TuneWidget::Remove);
	update();
}

void TuneWidget::Remove()
{
	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	int i = 0;
	for (auto var : buttons)
	{
		if (btn == var)
		{
			break;
		}
		i++;
	}
	delete buttons[i];
	delete sliders[i];
	delete maxLabels[i];
	delete minLabels[i];
	delete valueLabels[i];
	maxValue.takeAt(i);
	minValue.takeAt(i);
	delete slidersBoxes[i];
	delete widgets[i];
	delete boxes[i];
	buttons.takeAt(i);
	sliders.takeAt(i);
	maxLabels.takeAt(i);
	minLabels.takeAt(i);
	valueLabels.takeAt(i);
	slidersBoxes.takeAt(i);
	widgets.takeAt(i);
	boxes.takeAt(i);
	emit remove(tuned->GetCircuitElements()[i]);
	tuned->Remove(i);
	for (i; i < boxes.size(); i++)
	{
		boxes[i]->move(90 * i + 10 * i, 0);
	}
	if (boxes.size() == 0)
	{
		SystemParameters::tuneBlock = false;
	}
	update();
}

void TuneWidget::RemoveAll()
{
	int i = boxes.size() - 1;
	while (boxes.size() > 0)
	{
		delete buttons.last();
		delete sliders.last();
		delete maxLabels.last();
		delete minLabels.last();
		delete valueLabels.last();
		maxValue.pop_back();
		minValue.pop_back();
		delete slidersBoxes.last();
		delete widgets.last();
		delete boxes.last();
		buttons.pop_back();
		sliders.pop_back();
		maxLabels.pop_back();
		minLabels.pop_back();
		valueLabels.pop_back();
		slidersBoxes.pop_back();
		widgets.pop_back();
		boxes.pop_back();
		tuned->Remove(i);
		i--;
	}
	emit removeAll();
	SystemParameters::tuneBlock = false;
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
		else if (tuned->GetCircuitElements()[i]->GetMode() == Line)
		{

		}
		else if (tuned->GetCircuitElements()[i]->GetMode() == OSLine)
		{

		}
		else if (tuned->GetCircuitElements()[i]->GetMode() == SSLine)
		{

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
	QList <Element*> temp = {};
	for (int firstj = j; firstj < circuitElements->GetCircuitElements().size(); firstj++)
	{
		temp.append(circuitElements->GetCircuitElements()[firstj]);
	}
	Complex z;
	Complex y;
	Complex tempZ;
	Complex tempY;
	for (j; j < circuitElements->GetCircuitElements().size(); j++)
	{
		int max_step=0;
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
		double step = 0.1;
		switch (circuitElements->GetCircuitElements()[j]->GetMode())
		{
			case ResistorShunt:
			{
				double x;
				double y2;
				double r1 = z.real();
				double r2 = r1 + circuitElements->GetCircuitElements()[j]->GetValue();
				
				r2 = r2 / 50;
				tuple<double, double> tuple1 = circuitElements->GetCircuitElements()[j]->GetChartParameters().at(RealImpedance);
				tuple<double, double> tuple2;
				if (j != 0)
				{
					tuple2 = circuitElements->GetCircuitElements()[j-1]->GetChartParameters().at(ImagImpedance);
				}
				else
				{
					tuple2 = circuitElements->chart.at(ImagImpedance);
				}
				double r = get<0>(tuple2);
				double r3 = get<0>(tuple1);
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
				double t = get<1>(tuple2);
				double cos_t = cos(t);
				double sin_t = sin(t);
				x = 1 + (1 / r) * cos_t;
				y2 = (1 / r) + (1 / r) * sin_t;
				y2 = y2 * (-1);
				while (max_step < 500)
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
					cos_t = cos(t);
					sin_t = sin(t);
					x = 1 + (1 / r) * cos_t;
					y2 = (1 / r) + (1 / r) * sin_t;
					y2 = y2 * (-1);
					double circleRadius = 1 - ((pow(x, 2) + pow(y2, 2) - 1) / (2 * (x - 1)));
					double xCenter = 1 - circleRadius;
					double dx = x - xCenter;
					double dy = y2;
					double sin_t2 = dy;
					double cos_t2 = dx;
					double t1;
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
					max_step++;
					if (max_step == 500)
					{
						max_step = 0;
						break;
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
				map<chartMode, tuple<double, double>> chart;
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
				break;
			}
			case InductionShunt:
			{
				double x;
				double y2;
				double r1 = z.imag();
				double r2 = circuitElements->GetCircuitElements()[j]->GetValue()*2*M_PI*1e6*frequency+r1;
				double step = 0.1;
				r2 = r2 / 50;
				tuple<double, double> tuple1 = circuitElements->GetCircuitElements()[j]->GetChartParameters().at(ImagImpedance);
				tuple<double, double> tuple2;
				if (j != 0)
				{
					tuple2 = circuitElements->GetCircuitElements()[j - 1]->GetChartParameters().at(RealImpedance);
				}
				else
				{
					tuple2 = circuitElements->chart.at(RealImpedance);
				}
				double r = get<0>(tuple2);
				double r3 = get<0>(tuple1);
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
				double t = get<1>(tuple2);
				double cos_t = cos(t);
				double sin_t = sin(t);
				x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
				y2 = (1 / (r + 1)) * sin_t;
				while (max_step < 500)
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
					if (flag == false)
					{
						t -= step;
					}
					else
					{
						t += step;
					}
					cos_t = cos(t);
					sin_t = sin(t);
					x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
					y2 = (1 / (r + 1)) * sin_t;
					double circleRadius = 1 - ((pow(x, 2) + pow(y2, 2) - 1) / (2 * (x - 1)));
					double xCenter = 1 - circleRadius;
					double dx = x - xCenter;
					double dy = y2;
					double sin_t2 = dy;
					double cos_t2 = dx;
					double t1;
					if (abs(y2) < 1e-6 && abs(y2) >= 0)
					{
						if (y2 == 0 && x > 0.99)
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
						t1 = atan(cos_t2 / sin_t2);
						if (y2 < 0)
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
						r3 = cos(t1) / (x - 1);
					}
					else
					{
						r3 = (1 + sin(t1)) / y2;
					}
					if (y2 < 0)
					{
						r3 = abs(r3);
					}
					else
					{
						r3 = abs(r3) * (-1);
					}
					if (y2 == 0)
					{
						r3 = 0;
					}
					max_step++;
					if (max_step == 500)
					{
						max_step = 0;
						break;
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
				map<chartMode, tuple<double, double>> chart;
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
				break;
			}
			case CapacitorShunt:
			{
				double x;
				double y2;
				double r1 = z.imag();
				double r2 = r1-1/(circuitElements->GetCircuitElements()[j]->GetValue()*2*M_PI*frequency*1e6);
				double step = 0.1;
				r2 = r2 / 50;
				tuple<double, double> tuple1 = circuitElements->GetCircuitElements()[j]->GetChartParameters().at(ImagImpedance);
				tuple<double, double> tuple2;
				if (j != 0)
				{
					tuple2 = circuitElements->GetCircuitElements()[j - 1]->GetChartParameters().at(RealImpedance);
				}
				else
				{
					tuple2 = circuitElements->chart.at(RealImpedance);
				}
				double r = get<0>(tuple2);
				double r3 = get<0>(tuple1);
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
				double t = get<1>(tuple2);
				double cos_t = cos(t);
				double sin_t = sin(t);
				x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
				y2 = (1 / (r + 1)) * sin_t;
				while (max_step < 500)
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
					if (flag == false)
					{
						t -= step;
					}
					else
					{
						t += step;
					}
					cos_t = cos(t);
					sin_t = sin(t);
					x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
					y2 = (1 / (r + 1)) * sin_t;
					double circleRadius = 1 - ((pow(x, 2) + pow(y2, 2) - 1) / (2 * (x - 1)));
					double xCenter = 1 - circleRadius;
					double dx = x - xCenter;
					double dy = y2;
					double sin_t2 = dy;
					double cos_t2 = dx;
					double t1;
					if (abs(y2) < 1e-6 && abs(y2) >= 0)
					{
						if (y2 == 0 && x > 0.99)
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
						t1 = atan(cos_t2 / sin_t2);
						if (y2 < 0)
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
						r3 = cos(t1) / (x - 1);
					}
					else
					{
						r3 = (1 + sin(t1)) / y2;
					}
					if (y2 < 0)
					{
						r3 = abs(r3);
					}
					else
					{
						r3 = abs(r3) * (-1);
					}
					if (y2 == 0)
					{
						r3 = 0;
					}
					max_step++;
					if (max_step == 500)
					{
						max_step = 0;
						break;
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
				map<chartMode, tuple<double, double>> chart;
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
				break;
			}
			case ResistorParallel:
			{
				double x;
				double y2;
				double r1 = y.real();
				double r2 = 1000/circuitElements->GetCircuitElements()[j]->GetValue()+r1;
				double step = 0.1;
				r2 = r2 / 20;
				tuple<double, double> tuple1 = circuitElements->GetCircuitElements()[j]->GetChartParameters().at(RealAdmitance);
				tuple<double, double> tuple2;
				if (j != 0)
				{
					tuple2 = circuitElements->GetCircuitElements()[j - 1]->GetChartParameters().at(ImagAdmitance);
				}
				else
				{
					tuple2 = circuitElements->chart.at(ImagAdmitance);
				}
				double r = get<0>(tuple2);
				double r3 = get<0>(tuple1);
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
				double t = get<1>(tuple2);
				double cos_t = cos(t);
				double sin_t = sin(t);
				if (flag2 == true)
				{
					x = (cos_t - abs(r)) / r;
					y2 = (1 / r) + (1 / r) * sin_t;
					y2 *= -1;
				}
				else
				{
					x = -(cos_t - abs(r)) / r;
					y2 = -(1 / r) + (1 / r) * sin_t;
				}
				while (max_step < 500)
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
					if ((flag == false && flag2==false)||(flag==true && flag2==true))
					{
						t -= step;
					}
					else
					{
						t += step;
					}
					cos_t = cos(t);
					sin_t = sin(t);
					if (flag2==true)
					{
						x = (cos_t - abs(r)) / r;
						y2 = (1 / r) + (1 / r) * sin_t;
						y2 *= -1;
					}
					else
					{
						x = -(cos_t - abs(r)) / r;
						y2 = -(1 / r) + (1 / r) * sin_t;
					}
					double circleRadius = -1 - ((pow(x, 2) + pow(y2, 2) - 1) / (2 + 2 * x));
					double xCenter = -1 - circleRadius;
					double dx = x - xCenter;
					double dy = y2;
					dy *= -1;
					double sin_t2 = dy;
					double cos_t2 = dx;
					double t1;
					if (y2 < 1e-6 && y2 >= 0)
					{
						if (y2 == 0 && x < -0.99)
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
						t1 = atan(sin_t2 / cos_t2);
						if (cos_t2 < 0 && sin_t2 < 0)
						{
							t1 = abs(t1) - M_PI;
						}
						else if (sin_t2 > 0 && cos_t2 < 0)
						{
							t1 = M_PI - abs(t1);
						}
					}
					if (x - 1 != 0)
					{
						r3 = abs((cos(t1) - x) / (x + 1));
					}
					max_step++;
					if (max_step == 500)
					{
						max_step = 0;
						break;
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
				map<chartMode, tuple<double, double>> chart;
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
				break;
			}
			case InductionParallel:
			{
				double x;
				double y2;
				double r1 = y.imag();
				double r2 = r1-(M_PI*500*100)/(circuitElements->GetCircuitElements()[j]->GetValue()*frequency*1e9);
				r2 *= -1;
				double step = 0.1;
				r2 = r2 / 20;
				tuple<double, double> tuple1 = circuitElements->GetCircuitElements()[j]->GetChartParameters().at(ImagAdmitance);
				tuple<double, double> tuple2;
				if (j != 0)
				{
					tuple2 = circuitElements->GetCircuitElements()[j - 1]->GetChartParameters().at(RealAdmitance);
				}
				else
				{
					tuple2 = circuitElements->chart.at(RealAdmitance);
				}
				double r = get<0>(tuple2);
				double r3 = get<0>(tuple1);
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
				double t = get<1>(tuple2);
				double cos_t = cos(t);
				double sin_t = sin(t);
				x = (cos(t) - r) / (r + 1);
				y2 = (1 / (r + 1)) * sin_t * -1;
				while (max_step < 500)
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
					if (flag == false)
					{
						t -= step;
					}
					else
					{
						t += step;
					}
					cos_t = cos(t);
					sin_t = sin(t);
					x = (cos(t) - r) / (r + 1);
					y2 = (1 / (r + 1)) * sin_t * -1;
					double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y2, 2)) / (-2 * y2);
					double yCenter = -circleRadius;
					double dx = x + 1;
					double dy = y2 - yCenter;
					double sin_t2 = -dy;
					double cos_t2 = dx;
					double t1;
					if (abs(y2) <= 1e-6 && abs(y2) >= 0)
					{
						if (y2 == 0 && x < -0.99)
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
						t1 = atan(sin_t2 / cos_t2);
					}
					if (x + 1 != 0)
					{
						r3 = cos(t1) / (x + 1);
					}
					else
					{
						r3 = (1 + sin(t1)) / y2;
					}
					if (y2 > 0)
					{
						r3 *= -1;
					}
					if (y2 == 0)
					{
						r3 = 0;
						t1 = -M_PI / 2;
					}
					max_step++;
					if (max_step == 500)
					{
						max_step = 0;
						break;
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
				map<chartMode, tuple<double, double>> chart;
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
				break;
			}
			case CapacitorParallel:
			{
				double x;
				double y2;
				double r1 = y.imag();
				double r2 = r1 + (circuitElements->GetCircuitElements()[j]->GetValue()*M_PI*frequency*1e12)/500;
				r2 *= -1;
				double step = 0.1;
				r2 = r2 / 20;
				tuple<double, double> tuple1 = circuitElements->GetCircuitElements()[j]->GetChartParameters().at(ImagAdmitance);
				tuple<double, double> tuple2;
				if (j != 0)
				{
					tuple2 = circuitElements->GetCircuitElements()[j - 1]->GetChartParameters().at(RealAdmitance);
				}
				else
				{
					tuple2 = circuitElements->chart.at(RealAdmitance);
				}
				double r = get<0>(tuple2);
				double r3 = get<0>(tuple1);
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
				double t = get<1>(tuple2);
				double cos_t = cos(t);
				double sin_t = sin(t);
				x = (cos(t) - r) / (r + 1);
				y2 = (1 / (r + 1)) * sin_t * -1;
				while (max_step<500)
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
					if (flag == false)
					{
						t -= step;
					}
					else
					{
						t += step;
					}
					cos_t = cos(t);
					sin_t = sin(t);
					x = (cos(t) - r) / (r + 1);
					y2 = (1 / (r + 1)) * sin_t * -1;
					double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y2, 2)) / (-2 * y2);
					double yCenter = -circleRadius;
					double dx = x + 1;
					double dy = y2 - yCenter;
					double sin_t2 = -dy;
					double cos_t2 = dx;
					double t1;
					if (abs(y2) <= 1e-6 && abs(y2) >= 0)
					{
						if (y2 == 0 && x < -0.99)
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
						t1 = atan(sin_t2 / cos_t2);
					}
					if (x + 1 != 0)
					{
						r3 = cos(t1) / (x + 1);
					}
					else
					{
						r3 = (1 + sin(t1)) / y2;
					}
					if (y2 > 0)
					{
						r3 *= -1;
					}
					if (y2 == 0)
					{
						r3 = 0;
						t1 = -M_PI / 2;
					}
					max_step++;
					if (max_step == 500)
					{
						max_step = 0;
						break;
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
				map<chartMode, tuple<double, double>> chart;
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
				break;
			}
			case Line:
			{
				break;
			}
			case OSLine:
			{
				break;
			}
			case SSLine:
			{
				break;
			}
		}
		SystemParameters::tunedElements = temp;
		SystemParameters::tuned = true;
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
		else if (tuned->GetCircuitElements()[i]->GetMode() == Line)
		{

		}
		else if (tuned->GetCircuitElements()[i]->GetMode() == OSLine)
		{

		}
		else if (tuned->GetCircuitElements()[i]->GetMode() == SSLine)
		{

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

Complex TuneWidget::zCalculation(double x, double y)
{
	rImpedanceRealCalculation(x, y);
	rImpedanceImagCalculation(x, y);
	return Complex(impedanceRealR, impedanceImagR);
}

Complex TuneWidget::yCalculation(double x, double y)
{
	rAdmitanceRealCalculation(x, y);
	rAdmitanceImagCalculation(x, y);
	return Complex(admitanceRealR, admitanceImagR);
}

Complex TuneWidget::impedanceRealChartParameters(double x, double y)
{
	double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
	double xCenter = 1 - circleRadius;
	double dx = x - xCenter;
	double dy = y;
	double sin_t = dy;
	double cos_t = dx;
	double t1, r1;
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

Complex TuneWidget::admitanceRealChartParameters(double x, double y)
{
	double circleRadius = -1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 + 2 * x));
	double xCenter = -1 - circleRadius;
	double dx = x - xCenter;
	double dy = y;
	dy *= -1;
	double sin_t = dy;
	double cos_t = dx;
	double t1, r1;
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

Complex TuneWidget::impedanceImagChartParameters(double x, double y)
{
	double cos_t;
	double sin_t;
	double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
	double xCenter = 1 - circleRadius;
	double dx = x - xCenter;
	double dy = y;
	sin_t = dy;
	cos_t = dx;
	double t1, r1;
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

Complex TuneWidget::admitanceImagChartParameters(double x, double y)
{
	double cos_t;
	double sin_t;
	double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y, 2)) / (-2 * y);
	double yCenter = -circleRadius;
	double dx = x + 1;
	double dy = y - yCenter;
	sin_t = -dy;
	cos_t = dx;
	double t1, r1;
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

void TuneWidget::rImpedanceRealCalculation(double x, double y)
{
	double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
	double xCenter = 1 - circleRadius;
	double dx = x - xCenter;
	double dy = y;
	double sin_t = dy;
	double cos_t = dx;
	double t1;
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

void TuneWidget::rAdmitanceRealCalculation(double x, double y)
{
	double circleRadius = -1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 + 2 * x));
	double xCenter = -1 - circleRadius;
	double dx = x - xCenter;
	double dy = y;
	dy *= -1;
	double sin_t = dy;
	double cos_t = dx;
	double t1;
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

void TuneWidget::rImpedanceImagCalculation(double x, double y)
{
	double cos_t;
	double sin_t;
	double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
	double xCenter = 1 - circleRadius;
	double dx = x - xCenter;
	double dy = y;
	sin_t = dy;
	cos_t = dx;
	double t1;
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

void TuneWidget::rAdmitanceImagCalculation(double x, double y)
{
	double cos_t;
	double sin_t;
	double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y, 2)) / (-2 * y);
	double yCenter = -circleRadius;
	double dx = x + 1;
	double dy = y - yCenter;
	sin_t = -dy;
	cos_t = dx;
	double t1;
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