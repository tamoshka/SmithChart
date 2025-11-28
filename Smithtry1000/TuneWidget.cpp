#include "TuneWidget.h"
#include "ui_TuneWidget.h"
#include "systemParameters.h"
/// <summary>
/// Конструктор класса TuneWidget.
/// </summary>
/// <param name="parent"></param>
/// <param name="circuit">Цепь.</param>
TuneWidget::TuneWidget(QWidget *parent, CircuitElements* circuit)
	: QWidget(parent)
	, ui(new Ui::TuneWidget())
{
	ui->setupUi(this);
	this->setMinimumSize(400, 300);
	circuitElements = circuit;
	count = 0;
	tuned = new CircuitElements();
	ui->scrollArea->setWidget(mainWidget);
	ui->scrollArea->setWidgetResizable(true);
	ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	connect(ui->OKButton, &QPushButton::clicked, this, &TuneWidget::OKButton_clicked);
	connect(ui->MinMaxButton, &QPushButton::clicked, this, &TuneWidget::MinMaxButton_clicked);
	connect(ui->RemoveAllButton, &QPushButton::clicked, this, &TuneWidget::RemoveAll);
}

/// <summary>
/// Деструктор класса TuneWidget.
/// </summary>
TuneWidget::~TuneWidget()
{
	delete ui;
}

/// <summary>
/// Принятие изменений.
/// </summary>
void TuneWidget::OKButton_clicked()
{
	SystemParameters::tune = false;
}

/// <summary>
/// Закрытие виджета.
/// </summary>
/// <param name="event"></param>
void TuneWidget::closeEvent(QCloseEvent *event)
{
	SystemParameters::tune = false;
}

/// <summary>
/// Получение сигнала о новом настраиваемом элементе.
/// </summary>
/// <param name="elem"></param>
/// <param name="path"></param>
void TuneWidget::GetSignal(Element* elem, QString path)
{
	SystemParameters::tuneBlock = true;
	tuned->AppendCircuitElements(elem);
	QString name;
	long long n = 1;
	QGroupBox* box = new QGroupBox(mainWidget);
	int moved = 0;
	box->move(90 * (tuned->GetCircuitElements().size() - 1 + count) + 10 * (tuned->GetCircuitElements().size() - 1), 0);
	box->resize(90, 150);
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
	else if (elem->GetMode() == Line || elem->GetMode() == OSLine || elem->GetMode() == SSLine)
	{
		name = QStringLiteral(u"Z0 волн.");
		box->resize(180, 150);
		QGroupBox* elementBox2 = new QGroupBox(box);
		elementBox2->resize(86, 114);
		elementBox2->move(2, 35);
		elementBox2->setStyleSheet("background-color: rgb(64, 244, 208); color: rgb(0,0,0);");
		elementBox2->setTitle(name);
		elementBox2->show();
		slidersBoxes.append(elementBox2);
		QSlider* sld2 = new QSlider(elementBox2);
		sld2->resize(20, 80);
		sld2->move(2, 25);
		sld2->setStyleSheet("background-color: rgb(72, 72, 72); color: rgb(0, 0, 0); ");
		sld2->setValue(50);
		sld2->setMaximum(100);
		sld2->show();
		sliders.append(sld2);
		connect(sld2, &QSlider::sliderMoved, this, &TuneWidget::ValueChanged);
		QLabel* lbl2 = new QLabel(elementBox2);
		lbl2->resize(50, 15);
		lbl2->move(25, 57);
		lbl2->setText(QString::number((double)elem->GetValue() * n));
		maxValue.append(elem->GetValue() + elem->GetValue() * 0.5);
		minValue.append(elem->GetValue() - elem->GetValue() * 0.5);
		lbl2->show();
		valueLabels.append(lbl2);
		QLabel* maxlbl2 = new QLabel(elementBox2);
		maxlbl2->resize(50, 15);
		maxlbl2->move(25, 15);
		maxlbl2->setText(QString::number(maxValue[maxValue.size() - 1] * n));
		maxlbl2->show();
		maxLabels.append(maxlbl2);
		QLabel* minlbl2 = new QLabel(elementBox2);
		minlbl2->resize(50, 15);
		minlbl2->move(25, 94);
		minlbl2->setText(QString::number(minValue[minValue.size() - 1] * n));
		minlbl2->show();
		minLabels.append(minlbl2);
		name = QStringLiteral(u"Эл.дл. в рад.");
		moved = 90;
		count++;
	}
	box->setStyleSheet("background-color: rgb(64, 244, 208); ");
	box->show();
	boxes.append(box);
	QGroupBox* elementBox = new QGroupBox(box);
	elementBox->resize(86, 114);
	elementBox->move(2+moved, 35);
	elementBox->setStyleSheet("background-color: rgb(64, 244, 208); color: rgb(0,0,0);");
	elementBox->setTitle(name);
	elementBox->show();
	slidersBoxes.append(elementBox);
	QSlider* sld = new QSlider(elementBox);
	sld->resize(20, 80);
	sld->move(2, 25);
	sld->setStyleSheet("background-color: rgb(72, 72, 72); color: rgb(0, 0, 0); ");
	sld->setValue(50);
	sld->setMaximum(100);
	sld->show();
	sliders.append(sld);
	QLabel* lbl = new QLabel(elementBox);
	lbl->resize(50, 15);
	lbl->move(25, 57);
	if (elem->GetMode() == Line || elem->GetMode() == OSLine || elem->GetMode() == SSLine)
	{
		VerticalLinesElement* tmp = dynamic_cast<VerticalLinesElement*>(elem);
		lbl->setText(QString::number((double)tmp->GetLambda() * n));
		long double maxVal;
		long double minVal;
		maxVal = tmp->GetLambda() + tmp->GetLambda() * 0.5;
		minVal = tmp->GetLambda() - tmp->GetLambda() * 0.5;
		if (maxVal >= 0.5)
		{
			maxVal = 0.499;
			long double step = (maxVal - minVal) / 100;
			long double val = tmp->GetLambda() - minVal;
			val /= step;
			sld->setValue(val);
		}
		maxValue.append(maxVal);
		minValue.append(minVal);
	}
	else
	{
		lbl->setText(QString::number((double)elem->GetValue() * n));
		maxValue.append(elem->GetValue() + elem->GetValue() * 0.5);
		minValue.append(elem->GetValue() - elem->GetValue() * 0.5);
	}
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
	btn->setText(QStringLiteral(u"Убрать"));
	btn->move(35, 10);
	btn->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(0, 0, 0); ");
	btn->show();
	buttons.append(btn);
	mainWidget->setFixedSize(100 * (tuned->GetCircuitElements().size() + count), 150);
	connect(sld, &QSlider::sliderMoved, this, &TuneWidget::ValueChanged);
	connect(btn, &QPushButton::clicked, this, &TuneWidget::Remove);
	update();
}

/// <summary>
/// Удаление настраиваемого элемента.
/// </summary>
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
	if (tuned->GetCircuitElements()[i]->GetMode() == Line ||
		tuned->GetCircuitElements()[i]->GetMode() == OSLine ||
		tuned->GetCircuitElements()[i]->GetMode() == SSLine)
	{
		count--;
		delete sliders[i + 1];
		delete maxLabels[i+1];
		delete minLabels[i+1];
		delete valueLabels[i+1];
		maxValue.takeAt(i+1);
		minValue.takeAt(i+1);
		delete slidersBoxes[i+1];
		sliders.takeAt(i+1);
		maxLabels.takeAt(i+1);
		minLabels.takeAt(i+1);
		valueLabels.takeAt(i+1);
		slidersBoxes.takeAt(i+1);
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
	mainWidget->setFixedSize(100 * (tuned->GetCircuitElements().size() + count), 150);
	update();
}

/// <summary>
/// Удаление всех настраиваемых элементов.
/// </summary>
void TuneWidget::RemoveAll()
{
	int i = boxes.size() - 1;
	while (boxes.size() > 0)
	{
		if (tuned->GetCircuitElements()[i]->GetMode() == Line ||
			tuned->GetCircuitElements()[i]->GetMode() == OSLine ||
			tuned->GetCircuitElements()[i]->GetMode() == SSLine)
		{
			count--;
			delete sliders.last();
			delete maxLabels.last();
			delete minLabels.last();
			delete valueLabels.last();
			maxValue.pop_back();
			minValue.pop_back();
			delete slidersBoxes.last();
			sliders.pop_back();
			maxLabels.pop_back();
			minLabels.pop_back();
			valueLabels.pop_back();
			slidersBoxes.pop_back();
		}
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
	mainWidget->setFixedSize(100 * (tuned->GetCircuitElements().size() + count), 150);
	emit removeAll();
	SystemParameters::tuneBlock = false;
	update();
}

/// <summary>
/// Отрисовка виджета.
/// </summary>
/// <param name="event"></param>
void TuneWidget::paintEvent(QPaintEvent* event)
{
	int i = 0;
	int count = 0;
	for (auto& var : boxes)
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
		valueLabels[i+count]->setText(QString::number(n* (double)tuned->GetCircuitElements()[i]->GetValue()));
		if (tuned->GetCircuitElements()[i]->GetMode() == Line)
		{
			LinesElement* tmp = dynamic_cast<LinesElement*>(tuned->GetCircuitElements()[i]);
			valueLabels[i + 1]->setText(QString::number((double)tmp->GetLambda()));
			count++;
		}
		else if (tuned->GetCircuitElements()[i]->GetMode() == OSLine)
		{
			VerticalLinesElement* tmp = dynamic_cast<VerticalLinesElement*>(tuned->GetCircuitElements()[i]);
			valueLabels[i + 1]->setText(QString::number((double)tmp->GetLambda()));
			count++;
		}
		else if (tuned->GetCircuitElements()[i]->GetMode() == SSLine)
		{
			VerticalLinesElement* tmp = dynamic_cast<VerticalLinesElement*>(tuned->GetCircuitElements()[i]);
			valueLabels[i + 1]->setText(QString::number((double)tmp->GetLambda()));
			count++;
		}
		i++;
	}
}

/// <summary>
/// Обработка изменения значений у ползунков.
/// </summary>
/// <param name="value"></param>
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
	long double step = (maxValue[i] - minValue[i]) / 100;
	long double middle = (maxValue[i] + minValue[i]) / 2;
	int k = 0;
	if (boxes.size() != sliders.size())
	{
		QGroupBox* tmp = (QGroupBox*)sliders[i]->parent();
		QGroupBox* tmp2 = (QGroupBox*)tmp->parent();
		for (auto var : boxes)
		{
			if (boxes[k] == tmp2)
			{
				break;
			}
			k++;
		}
	}
	else
	{
		k = i;
	}
	if (tuned->GetCircuitElements()[k]->GetMode() == Line ||
		tuned->GetCircuitElements()[k]->GetMode() == OSLine ||
		tuned->GetCircuitElements()[k]->GetMode() == SSLine)
	{
		if (i == sliders.size() - 1)
		{
			if (sliders[i]->parent()->parent() == sliders[i - 1]->parent()->parent())
			{
				VerticalLinesElement* tmp3 = dynamic_cast<VerticalLinesElement*>(tuned->GetCircuitElements()[k]);
				tmp3->SetLambda(minValue[i] + value * step);
			}
			else
			{
				tuned->GetCircuitElements()[k]->SetValue(minValue[i] + value * step);
			}
		}
		else
		{
			if (sliders[i]->parent()->parent() == sliders[i + 1]->parent()->parent())
			{
				tuned->GetCircuitElements()[k]->SetValue(minValue[i] + value * step);
			}
			else
			{
				VerticalLinesElement* tmp3 = dynamic_cast<VerticalLinesElement*>(tuned->GetCircuitElements()[k]);
				tmp3->SetLambda(minValue[i] + value * step);
			}
		}
	}
	else
	{
		tuned->GetCircuitElements()[k]->SetValue(minValue[i] + value * step);
	}
	int j = 0;
	for (auto var : circuitElements->GetCircuitElements())
	{
		if (var == tuned->GetCircuitElements()[k])
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
	Complex g;
	Complex tempZ;
	Complex tempY;
	for (j; j < circuitElements->GetCircuitElements().size(); j++)
	{
		int max_step = 0;
		if (j != 0)
		{
			z = circuitElements->GetCircuitElements()[j - 1]->GetParameter().at(Z);
			y = circuitElements->GetCircuitElements()[j - 1]->GetParameter().at(Y);
			g = circuitElements->GetCircuitElements()[j - 1]->GetParameter().at(G);
		}
		else
		{
			z = circuitElements->z;
			y = circuitElements->y;
			g = circuitElements->g;
		}
		long double step = 0.1;
		switch (circuitElements->GetCircuitElements()[j]->GetMode())
		{
		case ResistorShunt:
		{
			long double x;
			long double y2;
			long double r1 = z.real();
			long double r2 = r1 + circuitElements->GetCircuitElements()[j]->GetValue();
			long double tempy;
			r2 = r2 / SystemParameters::z0;
			tuple<long double, long double> tuple1 = circuitElements->GetCircuitElements()[j]->GetChartParameters().at(RealImpedance);
			tuple<long double, long double> tuple2;
			if (j != 0)
			{
				tuple2 = circuitElements->GetCircuitElements()[j - 1]->GetChartParameters().at(ImagImpedance);
				tempy = circuitElements->GetCircuitElements()[j - 1]->GetPoint().y;
			}
			else
			{
				tuple2 = circuitElements->chart.at(ImagImpedance);
				tempy = circuitElements->firstPoint.y;
			}
			long double r = get<0>(tuple2);
			long double r3 = get<0>(tuple1);
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
			if (tempy < 0)
			{
				flag2 = true;
			}
			else
			{
				flag2 = false;
			}
			long double t = get<1>(tuple2);
			long double cos_t = cos(t);
			long double sin_t = sin(t);
			x = 1 + (1 / r) * cos_t;
			y2 = (1 / r) + (1 / r) * sin_t;
			y2 = y2 * (-1);
			while (max_step < 5000)
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
				if (abs(y2) >= 0 && abs(y2) < 0.0001)
				{
					if (flag2)
					{
						y2 = -0.0001;
					}
					else
					{
						y2 = 0.0001;
					}
				}
				long double circleRadius = 1 - ((pow(x, 2) + pow(y2, 2) - 1) / (2 * (x - 1)));
				long double xCenter = 1 - circleRadius;
				long double dx = x - xCenter;
				long double dy = y2;
				long double sin_t2 = dy;
				long double cos_t2 = dx;
				long double t1;
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
				if (x - 1 != 0)
				{
					r3 = (cos(t1) - x) / (x - 1);
				}
				else
				{
					r3 = 1e9;
				}
				max_step++;
				if (max_step == 500)
				{
					max_step = 0;
					break;
				}
			}
			if (abs(x) > 1)
			{
				if (flag2)
				{
					y2 = -0.0001;
				}
				else
				{
					y2 = 0.0001;
				}
				long double denominator = (r2 + 1) * (r2 + 1);

				if (denominator != 0) {
					x = (r2 * r2 - 1) / denominator;
				}
				else
				{
					x = -1;
				}
			}
			Point point;
			point.x = x;
			point.y = y2;
			circuitElements->GetCircuitElements()[j]->SetPoint(point);
			Complex z2 = SystemParameters::zCalculation(x, y2);
			Complex y3 = SystemParameters::yCalculation(x, y2);
			map<parameterMode, Complex> parameter;
			parameter[Z] = z2;
			parameter[Y] = y3;
			Complex g;
			if (x >= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), atan(y2 / x) * 180 / M_PI * -1);
			}
			else if (y2 <= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), 180 - atan(y2 / x) * 180 / M_PI);
			}
			else
			{
				g = Complex(pow(x, 2) + pow(y2, 2), -180 - atan(y2 / x) * 180 / M_PI);
			}
			parameter[G] = g;
			map<chartMode, tuple<long double, long double>> chart;
			Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(x, y2);
			Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(x, y2);
			Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(x, y2);
			Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(x, y2);
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
			long double x;
			long double y2;
			long double r1 = z.imag();
			long double r2 = circuitElements->GetCircuitElements()[j]->GetValue() * 2 * M_PI * circuitElements->frequencyFirstPoint + r1;
			long double step = 0.1;
			r2 = r2 / SystemParameters::z0;
			tuple<long double, long double> tuple1 = circuitElements->GetCircuitElements()[j]->GetChartParameters().at(ImagImpedance);
			tuple<long double, long double> tuple2;
			if (j != 0)
			{
				tuple2 = circuitElements->GetCircuitElements()[j - 1]->GetChartParameters().at(RealImpedance);
			}
			else
			{
				tuple2 = circuitElements->chart.at(RealImpedance);
			}
			long double r = get<0>(tuple2);
			long double r3 = get<0>(tuple1);
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
			long double t = get<1>(tuple2);
			long double cos_t = cos(t);
			long double sin_t = sin(t);
			x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
			y2 = (1 / (r + 1)) * sin_t;
			if (y2 >= 0 && y2 < 0.0001)
			{
				y2 = 0.0001;
			}
			else if (y2 <= 0 && y2 > -0.0001)
			{
				y2 = -0.0001;
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
				if (y2 >= 0 && y2 < 0.0001)
				{
					y2 = 0.0001;
				}
				else if (y2 <= 0 && y2 > -0.0001)
				{
					y2 = -0.0001;
				}
				long double circleRadius = 1 - ((pow(x, 2) + pow(y2, 2) - 1) / (2 * (x - 1)));
				long double xCenter = 1 - circleRadius;
				long double dx = x - xCenter;
				long double dy = y2;
				long double sin_t2 = dy;
				long double cos_t2 = dx;
				long double t1;
				t1 = atan(cos_t2 / sin_t2);
				if (y2 < 0)
				{
					t1 += M_PI;
				}
				else
				{
					t1 += 2 * M_PI;
				}
				if (x - 1 != 0)
				{
					r3 = cos(t1) / (x - 1);
				}
				else
				{
					r3 = 1e9;
				}
				if (y2 < 0)
				{
					r3 = abs(r3);
				}
				else
				{
					r3 = abs(r3) * (-1);
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
			Complex z2 = SystemParameters::zCalculation(x, y2);
			Complex y3 = SystemParameters::yCalculation(x, y2);
			map<parameterMode, Complex> parameter;
			parameter[Z] = z2;
			parameter[Y] = y3;
			Complex g;
			if (x >= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), atan(y2 / x) * 180 / M_PI * -1);
			}
			else if (y2 <= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), 180 - atan(y2 / x) * 180 / M_PI);
			}
			else
			{
				g = Complex(pow(x, 2) + pow(y2, 2), -180 - atan(y2 / x) * 180 / M_PI);
			}
			parameter[G] = g;
			map<chartMode, tuple<long double, long double>> chart;
			Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(x, y2);
			Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(x, y2);
			Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(x, y2);
			Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(x, y2);
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
			long double x;
			long double y2;
			long double r1 = z.imag();
			long double r2 = r1 - 1 / (circuitElements->GetCircuitElements()[j]->GetValue() * 2 * M_PI * circuitElements->frequencyFirstPoint);
			long double step = 0.1;
			r2 = r2 / SystemParameters::z0;
			tuple<long double, long double> tuple1 = circuitElements->GetCircuitElements()[j]->GetChartParameters().at(ImagImpedance);
			tuple<long double, long double> tuple2;
			if (j != 0)
			{
				tuple2 = circuitElements->GetCircuitElements()[j - 1]->GetChartParameters().at(RealImpedance);
			}
			else
			{
				tuple2 = circuitElements->chart.at(RealImpedance);
			}
			long double r = get<0>(tuple2);
			long double r3 = get<0>(tuple1);
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
			long double t = get<1>(tuple2);
			long double cos_t = cos(t);
			long double sin_t = sin(t);
			x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
			y2 = (1 / (r + 1)) * sin_t;
			if (y2 >= 0 && y2 < 0.0001)
			{
				y2 = 0.0001;
			}
			else if (y2 <= 0 && y2 > -0.0001)
			{
				y2 = -0.0001;
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
				if (y2 >= 0 && y2 < 0.0001)
				{
					y2 = 0.0001;
				}
				else if (y2 <= 0 && y2 > -0.0001)
				{
					y2 = -0.0001;
				}
				long double circleRadius = 1 - ((pow(x, 2) + pow(y2, 2) - 1) / (2 * (x - 1)));
				long double xCenter = 1 - circleRadius;
				long double dx = x - xCenter;
				long double dy = y2;
				long double sin_t2 = dy;
				long double cos_t2 = dx;
				long double t1;
				t1 = atan(cos_t2 / sin_t2);
				if (y2 < 0)
				{
					t1 += M_PI;
				}
				else
				{
					t1 += 2 * M_PI;
				}
				if (x - 1 != 0)
				{
					r3 = cos(t1) / (x - 1);
				}
				else
				{
					r3 = 1e9;
				}
				if (y2 < 0)
				{
					r3 = abs(r3);
				}
				else
				{
					r3 = abs(r3) * (-1);
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
			Complex z2 = SystemParameters::zCalculation(x, y2);
			Complex y3 = SystemParameters::yCalculation(x, y2);
			map<parameterMode, Complex> parameter;
			parameter[Z] = z2;
			parameter[Y] = y3;
			Complex g;
			if (x >= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), atan(y2 / x) * 180 / M_PI * -1);
			}
			else if (y2 <= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), 180 - atan(y2 / x) * 180 / M_PI);
			}
			else
			{
				g = Complex(pow(x, 2) + pow(y2, 2), -180 - atan(y2 / x) * 180 / M_PI);
			}
			parameter[G] = g;
			map<chartMode, tuple<long double, long double>> chart;
			Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(x, y2);
			Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(x, y2);
			Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(x, y2);
			Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(x, y2);
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
			long double x;
			long double y2;
			long double tempy;
			long double r1 = y.real();
			long double r2 = 1000 / circuitElements->GetCircuitElements()[j]->GetValue() + r1;
			long double step = 0.1;
			r2 = r2 / (1000 / SystemParameters::z0);
			tuple<long double, long double> tuple1 = circuitElements->GetCircuitElements()[j]->GetChartParameters().at(RealAdmitance);
			tuple<long double, long double> tuple2;
			if (j != 0)
			{
				tuple2 = circuitElements->GetCircuitElements()[j - 1]->GetChartParameters().at(ImagAdmitance);
				tempy = circuitElements->GetCircuitElements()[j - 1]->GetPoint().y;
			}
			else
			{
				tuple2 = circuitElements->chart.at(ImagAdmitance);
				tempy = circuitElements->firstPoint.y;
			}
			long double r = get<0>(tuple2);
			long double r3 = get<0>(tuple1);
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
			if (tempy < 0)
			{
				flag2 = true;
			}
			else
			{
				flag2 = false;
			}
			long double t = get<1>(tuple2);
			long double cos_t = cos(t);
			long double sin_t = sin(t);
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
			while (max_step < 5000)
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
					t -= step;
				}
				else
				{
					t += step;
				}
				cos_t = cos(t);
				sin_t = sin(t);
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
				if (abs(y2) >= 0 && abs(y2) < 0.0001)
				{
					if (flag2)
					{
						y2 = -0.0001;
					}
					else
					{
						y2 = 0.0001;
					}
				}
				long double circleRadius = -1 - ((pow(x, 2) + pow(y2, 2) - 1) / (2 + 2 * x));
				long double xCenter = -1 - circleRadius;
				long double dx = x - xCenter;
				long double dy = y2;
				dy *= -1;
				long double sin_t2 = dy;
				long double cos_t2 = dx;
				long double t1;
				t1 = atan(sin_t2 / cos_t2);
				if (cos_t2 < 0 && sin_t2 < 0)
				{
					t1 = abs(t1) - M_PI;
				}
				else if (sin_t2 > 0 && cos_t2 < 0)
				{
					t1 = M_PI - abs(t1);
				}
				if (x - 1 != 0)
				{
					r3 = abs((cos(t1) - x) / (x + 1));
				}
				else
				{
					r3 = 1e9;
				}
				max_step++;
				if (max_step == 500)
				{
					max_step = 0;
					break;
				}
			}
			if (abs(x) > 1)
			{
				if (flag2)
				{
					y2 = -0.0001;
				}
				else
				{
					y2 = 0.0001;
				}
				long double denominator = (1 + r2) * (1 + r2);

				if (denominator != 0) {
					x = (1 - r2 * r2) / denominator;
				}
				else {
					x = -1;
				}
			}
			Point point;
			point.x = x;
			point.y = y2;
			circuitElements->GetCircuitElements()[j]->SetPoint(point);
			Complex z2 = SystemParameters::zCalculation(x, y2);
			Complex y3 = SystemParameters::yCalculation(x, y2);
			map<parameterMode, Complex> parameter;
			parameter[Z] = z2;
			parameter[Y] = y3;
			Complex g;
			if (x >= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), atan(y2 / x) * 180 / M_PI * -1);
			}
			else if (y2 <= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), 180 - atan(y2 / x) * 180 / M_PI);
			}
			else
			{
				g = Complex(pow(x, 2) + pow(y2, 2), -180 - atan(y2 / x) * 180 / M_PI);
			}
			parameter[G] = g;
			map<chartMode, tuple<long double, long double>> chart;
			Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(x, y2);
			Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(x, y2);
			Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(x, y2);
			Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(x, y2);
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
			long double x;
			long double y2;
			long double r1 = y.imag();
			long double r2 = r1 - (M_PI * 500 * 100) / (circuitElements->GetCircuitElements()[j]->GetValue() * circuitElements->frequencyFirstPoint * 1e9 / 1e6);
			r2 *= -1;
			long double step = 0.1;
			r2 = r2 / (1000 / SystemParameters::z0);
			tuple<long double, long double> tuple1 = circuitElements->GetCircuitElements()[j]->GetChartParameters().at(ImagAdmitance);
			tuple<long double, long double> tuple2;
			if (j != 0)
			{
				tuple2 = circuitElements->GetCircuitElements()[j - 1]->GetChartParameters().at(RealAdmitance);
			}
			else
			{
				tuple2 = circuitElements->chart.at(RealAdmitance);
			}
			long double r = get<0>(tuple2);
			long double r3 = get<0>(tuple1);
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
			long double t = get<1>(tuple2);
			long double cos_t = cos(t);
			long double sin_t = sin(t);
			x = (cos(t) - r) / (r + 1);
			y2 = (1 / (r + 1)) * sin_t * -1;
			if (y2 >= 0 && y2 < 0.0001)
			{
				y2 = 0.0001;
			}
			else if (y2 <= 0 && y2 > -0.0001)
			{
				y2 = -0.0001;
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
				if (y2 >= 0 && y2 < 0.0001)
				{
					y2 = 0.0001;
				}
				else if (y2 <= 0 && y2 > -0.0001)
				{
					y2 = -0.0001;
				}
				long double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y2, 2)) / (-2 * y2);
				long double yCenter = -circleRadius;
				long double dx = x + 1;
				long double dy = y2 - yCenter;
				long double sin_t2 = -dy;
				long double cos_t2 = dx;
				long double t1;
				t1 = atan(sin_t2 / cos_t2);
				if (x + 1 != 0)
				{
					r3 = cos(t1) / (x + 1);
				}
				else
				{
					r3 = 1e9;
				}
				if (y2 > 0)
				{
					r3 *= -1;
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
			Complex z2 = SystemParameters::zCalculation(x, y2);
			Complex y3 = SystemParameters::yCalculation(x, y2);
			map<parameterMode, Complex> parameter;
			parameter[Z] = z2;
			parameter[Y] = y3;
			Complex g;
			if (x >= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), atan(y2 / x) * 180 / M_PI * -1);
			}
			else if (y2 <= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), 180 - atan(y2 / x) * 180 / M_PI);
			}
			else
			{
				g = Complex(pow(x, 2) + pow(y2, 2), -180 - atan(y2 / x) * 180 / M_PI);
			}
			parameter[G] = g;
			map<chartMode, tuple<long double, long double>> chart;
			Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(x, y2);
			Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(x, y2);
			Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(x, y2);
			Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(x, y2);
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
			long double x;
			long double y2;
			long double r1 = y.imag();
			long double r2 = r1 + (circuitElements->GetCircuitElements()[j]->GetValue() * M_PI * circuitElements->frequencyFirstPoint * 1e12 / 1e6) / 500;
			r2 *= -1;
			long double step = 0.1;
			r2 = r2 / (1000 / SystemParameters::z0);
			tuple<long double, long double> tuple1 = circuitElements->GetCircuitElements()[j]->GetChartParameters().at(ImagAdmitance);
			tuple<long double, long double> tuple2;
			if (j != 0)
			{
				tuple2 = circuitElements->GetCircuitElements()[j - 1]->GetChartParameters().at(RealAdmitance);
			}
			else
			{
				tuple2 = circuitElements->chart.at(RealAdmitance);
			}
			long double r = get<0>(tuple2);
			long double r3 = get<0>(tuple1);
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
			long double t = get<1>(tuple2);
			long double cos_t = cos(t);
			long double sin_t = sin(t);
			x = (cos(t) - r) / (r + 1);
			y2 = (1 / (r + 1)) * sin_t * -1;
			if (y2 >= 0 && y2 < 0.0001)
			{
				y2 = 0.0001;
			}
			else if (y2 <= 0 && y2 > -0.0001)
			{
				y2 = -0.0001;
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
				if (y2 >= 0 && y2 < 0.0001)
				{
					y2 = 0.0001;
				}
				else if (y2 <= 0 && y2 > -0.0001)
				{
					y2 = -0.0001;
				}
				long double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y2, 2)) / (-2 * y2);
				long double yCenter = -circleRadius;
				long double dx = x + 1;
				long double dy = y2 - yCenter;
				long double sin_t2 = -dy;
				long double cos_t2 = dx;
				long double t1;
				t1 = atan(sin_t2 / cos_t2);
				if (x + 1 != 0)
				{
					r3 = cos(t1) / (x + 1);
				}
				else
				{
					r3 = 1e9;
				}
				if (y2 > 0)
				{
					r3 *= -1;
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
			Complex z2 = SystemParameters::zCalculation(x, y2);
			Complex y3 = SystemParameters::yCalculation(x, y2);
			map<parameterMode, Complex> parameter;
			parameter[Z] = z2;
			parameter[Y] = y3;
			Complex g;
			if (x >= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), atan(y2 / x) * 180 / M_PI * -1);
			}
			else if (y2 <= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), 180 - atan(y2 / x) * 180 / M_PI);
			}
			else
			{
				g = Complex(pow(x, 2) + pow(y2, 2), -180 - atan(y2 / x) * 180 / M_PI);
			}
			parameter[G] = g;
			map<chartMode, tuple<long double, long double>> chart;
			Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(x, y2);
			Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(x, y2);
			Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(x, y2);
			Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(x, y2);
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
			long double x;
			long double y2;
			if (j != 0)
			{
				x = circuitElements->GetCircuitElements()[j - 1]->GetPoint().x;
				y2 = circuitElements->GetCircuitElements()[j - 1]->GetPoint().y;
			}
			else
			{
				x = circuitElements->firstPoint.x;
				y2 = circuitElements->firstPoint.y;
			}
			LinesElement* elem = dynamic_cast<LinesElement*>(circuitElements->GetCircuitElements()[j]);
			long double z0 = elem->GetValue();
			long double lambda = elem->GetLambda();
			Complex g1 = (z - SystemParameters::z0) / (z + SystemParameters::z0);
			Complex z3 = z0 * (z + Complex(0, z0)) / (z0 + Complex(0, 1) * z);
			Complex g3 = (z3 - SystemParameters::z0) / (z3 + SystemParameters::z0);
			long double center = 0.5 * (pow(g1.real(), 2) + pow(g1.imag(), 2) - pow(g3.real(), 2) - pow(g3.imag(), 2)) / (g1.real() - g3.real());
			long double R = abs(center - g1);
			long double dx = x - center;
			long double dy = y2;
			dy *= -1;
			long double sin_t = dy;
			long double cos_t = dx;
			long double t = atan(sin_t / cos_t);
			if (cos_t >= 0)
			{
				t *= -1;
			}
			else if (sin_t <= 0)
			{
				t = M_PI - t;
			}
			else
			{
				t = -M_PI - t;
			}
			long double r = center;

			long double RL = z.real();
			long double XL = z.imag();
			long double newLambda = 0;
			long double Length;
			long double L;
			long double Theta;
			long double step = M_PI / 2;
			bool flag = true;
			while (max_step < 500)
			{
				if (flag == true)
				{
					t += step;
				}
				else
				{
					t -= step;
				}
				if (t > M_PI)
				{
					t = -M_PI;
					step /= 2;
				}
				else if (t < -M_PI)
				{
					t = M_PI;
					step /= 2;
				}
				long double cos_t1 = cos(t);
				long double sin_t1 = sin(t);
				x = cos_t1 * R + center;
				y2 = sin_t1 * R;
				if (y2 >= 0 && y2 < 0.0001)
				{
					y2 = 0.0001;
				}
				else if (y2 <= 0 && y2 > -0.0001)
				{
					y2 = -0.0001;
				}
				SystemParameters::rImpedanceRealCalculation(x, y2);
				SystemParameters::rImpedanceImagCalculation(x, y2);
				long double R3 = SystemParameters::impedanceRealR;
				long double X3 = SystemParameters::impedanceImagR;
				long double RR3 = R3 - RL;
				long double sq3 = -sqrt(RR3 * (RL * (pow(X3, 2) + pow(R3, 2)) - R3 * (pow(XL, 2) + pow(RL, 2)))) / RR3;
				long double tanO13 = RR3 * sq3 / (R3 * XL + RL * X3);
				long double tanO23 = -RR3 * sq3 / (R3 * XL + RL * X3);
				long double z03;
				long double O3;
				if (sq3 > 0)
				{
					z03 = sq3;
					O3 = atan(tanO13);
				}
				else
				{
					z03 = -sq3;
					O3 = atan(tanO23);
				}
				if (O3 < 0)
				{
					O3 += M_PI;
				}
				Theta = O3 * 180 / M_PI;
				L = O3 * 299792458 / (2 * M_PI * 1e9);
				Length = L * 1e3;
				newLambda = L * 1e9 / 299792458;
				if (newLambda > lambda && flag == true)
				{
					flag = false;
					step /= 2;
				}
				else if (newLambda < lambda && flag == false)
				{
					flag = true;
					step /= 2;
				}
				else if (newLambda == lambda)
				{
					break;
				}
				max_step++;
			}

			Point point;
			point.x = x;
			point.y = y2;
			circuitElements->GetCircuitElements()[j]->SetPoint(point);
			Complex z2 = SystemParameters::zCalculation(x, y2);
			Complex y3 = SystemParameters::yCalculation(x, y2);
			map<parameterMode, Complex> parameter;
			parameter[Z] = z2;
			parameter[Y] = y3;
			Complex g;
			if (x >= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), atan(y2 / x) * 180 / M_PI * -1);
			}
			else if (y2 <= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), 180 - atan(y2 / x) * 180 / M_PI);
			}
			else
			{
				g = Complex(pow(x, 2) + pow(y2, 2), -180 - atan(y2 / x) * 180 / M_PI);
			}
			parameter[G] = g;
			map<chartMode, tuple<long double, long double>> chart;
			Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(x, y2);
			Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(x, y2);
			Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(x, y2);
			Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(x, y2);
			chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
			chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
			chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
			chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
			circuitElements->GetCircuitElements()[j]->SetChartParameters(chart);
			circuitElements->GetCircuitElements()[j]->SetParameter(parameter);
			long double er = pow(elem->GetElectricalLength() / elem->GetMechanicalLength(), 2);
			elem->SetElectricalLength(L * 1000);
			elem->SetMechanicalLength(L * 1000 / sqrt(er));
			elem->SetTheta(Theta);
			break;
		}
		case OSLine:
		{
			long double x;
			long double y2;
			long double r1 = y.imag();
			VerticalLinesElement* elem = dynamic_cast<VerticalLinesElement*>(circuitElements->GetCircuitElements()[j]);
			long double tn;
			long double angle = 2 * M_PI * elem->GetLambda();
			if (elem->GetLambda() > 0.25)
			{
				angle -= M_PI;
			}
			tn = tan(angle) * 1000 / elem->GetValue();
			long double r2 = r1 + tn;
			r2 *= -1;
			long double step = 0.1;
			r2 = r2 / (1000 / SystemParameters::z0);
			tuple<long double, long double> tuple1 = circuitElements->GetCircuitElements()[j]->GetChartParameters().at(ImagAdmitance);
			tuple<long double, long double> tuple2;
			if (j != 0)
			{
				tuple2 = circuitElements->GetCircuitElements()[j - 1]->GetChartParameters().at(RealAdmitance);
			}
			else
			{
				tuple2 = circuitElements->chart.at(RealAdmitance);
			}
			long double r = get<0>(tuple2);
			long double r3 = get<0>(tuple1);
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
			long double t = get<1>(tuple2);
			long double cos_t = cos(t);
			long double sin_t = sin(t);
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
				long double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y2, 2)) / (-2 * y2);
				long double yCenter = -circleRadius;
				long double dx = x + 1;
				long double dy = y2 - yCenter;
				long double sin_t2 = -dy;
				long double cos_t2 = dx;
				long double t1;
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
					r3 = 1e9;
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
			Complex z2 = SystemParameters::zCalculation(x, y2);
			Complex y3 = SystemParameters::yCalculation(x, y2);
			map<parameterMode, Complex> parameter;
			parameter[Z] = z2;
			parameter[Y] = y3;
			Complex g;
			if (x >= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), atan(y2 / x) * 180 / M_PI * -1);
			}
			else if (y2 <= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), 180 - atan(y2 / x) * 180 / M_PI);
			}
			else
			{
				g = Complex(pow(x, 2) + pow(y2, 2), -180 - atan(y2 / x) * 180 / M_PI);
			}
			parameter[G] = g;
			map<chartMode, tuple<long double, long double>> chart;
			Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(x, y2);
			Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(x, y2);
			Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(x, y2);
			Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(x, y2);
			chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
			chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
			chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
			chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
			circuitElements->GetCircuitElements()[j]->SetChartParameters(chart);
			circuitElements->GetCircuitElements()[j]->SetParameter(parameter);
			long double theta;
			long double lambda;
			long double o;
			long double l;
			o = atan((y3.imag() - y.imag()) / 1000 * elem->GetValue());
			if (o < 0)
			{
				o += M_PI;
			}
			theta = o * 180 / M_PI;
			l = o * 299792458 / (2 * M_PI * 1e9);
			lambda = l * 1e9 / 299792458;
			long double er = pow(elem->GetElectricalLength() / elem->GetMechanicalLength(), 2);
			elem->SetElectricalLength(l * 1000);
			elem->SetMechanicalLength(l * 1000 / sqrt(er));
			elem->SetLambda(lambda);
			elem->SetTheta(theta);
			break;
		}
		case SSLine:
		{
			long double x;
			long double y2;
			long double r1 = y.imag();
			VerticalLinesElement* elem = dynamic_cast<VerticalLinesElement*>(circuitElements->GetCircuitElements()[j]);
			long double tn;
			long double angle = 2 * M_PI * elem->GetLambda();
			if (elem->GetLambda() > 0.25)
			{
				angle -= M_PI;
			}
			tn = -1000 / tan(angle) / elem->GetValue();
			long double r2 = r1 + tn;
			r2 *= -1;
			long double step = 0.1;
			r2 = r2 / (1000 / SystemParameters::z0);
			tuple<long double, long double> tuple1 = circuitElements->GetCircuitElements()[j]->GetChartParameters().at(ImagAdmitance);
			tuple<long double, long double> tuple2;
			if (j != 0)
			{
				tuple2 = circuitElements->GetCircuitElements()[j - 1]->GetChartParameters().at(RealAdmitance);
			}
			else
			{
				tuple2 = circuitElements->chart.at(RealAdmitance);
			}
			long double r = get<0>(tuple2);
			long double r3 = get<0>(tuple1);
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
			long double t = get<1>(tuple2);
			long double cos_t = cos(t);
			long double sin_t = sin(t);
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
				long double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y2, 2)) / (-2 * y2);
				long double yCenter = -circleRadius;
				long double dx = x + 1;
				long double dy = y2 - yCenter;
				long double sin_t2 = -dy;
				long double cos_t2 = dx;
				long double t1;
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
					r3 = 1e9;
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
			Complex z2 = SystemParameters::zCalculation(x, y2);
			Complex y3 = SystemParameters::yCalculation(x, y2);
			map<parameterMode, Complex> parameter;
			parameter[Z] = z2;
			parameter[Y] = y3;
			Complex g;
			if (x >= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), atan(y2 / x) * 180 / M_PI * -1);
			}
			else if (y2 <= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), 180 - atan(y2 / x) * 180 / M_PI);
			}
			else
			{
				g = Complex(pow(x, 2) + pow(y2, 2), -180 - atan(y2 / x) * 180 / M_PI);
			}
			parameter[G] = g;
			map<chartMode, tuple<long double, long double>> chart;
			Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(x, y2);
			Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(x, y2);
			Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(x, y2);
			Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(x, y2);
			chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
			chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
			chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
			chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
			circuitElements->GetCircuitElements()[j]->SetChartParameters(chart);
			circuitElements->GetCircuitElements()[j]->SetParameter(parameter);
			long double theta;
			long double lambda;
			long double o;
			long double l;
			o = -atan(1 / ((y3.imag() - y.imag()) / 1000 * elem->GetValue()));
			if (o < 0)
			{
				o += M_PI;
			}
			theta = o * 180 / M_PI;
			l = o * 299792458 / (2 * M_PI * 1e9);
			lambda = l * 1e9 / 299792458;
			long double er = pow(elem->GetElectricalLength() / elem->GetMechanicalLength(), 2);
			elem->SetElectricalLength(l * 1000);
			elem->SetMechanicalLength(l * 1000 / sqrt(er));
			elem->SetLambda(lambda);
			elem->SetTheta(theta);
			break;
		}
		case Transform:
		{
			long double x;
			long double y2;
			long double t;
			long double r1 = z.real();
			long double r2 = pow(circuitElements->GetCircuitElements()[j]->GetValue(), 2) * r1;
			r2 = r2 / SystemParameters::z0;
			long double q = z.imag() / z.real();
			long double rIm = q * r2;
			long double denominator = (r2 + 1) * (r2 + 1) + rIm * rIm;

			if (denominator != 0) {
				x = (r2 * r2 + rIm * rIm - 1) / denominator;
				y2 = (2 * rIm) / denominator;
			}
			else {
				x = -1;
				y2 = 0;
			}
			y2 *= -1;
			Point point;
			point.x = x;
			point.y = y2;
			circuitElements->GetCircuitElements()[j]->SetPoint(point);
			Complex z2 = SystemParameters::zCalculation(x, y2);
			Complex y3 = SystemParameters::yCalculation(x, y2);
			map<parameterMode, Complex> parameter;
			parameter[Z] = z2;
			parameter[Y] = y3;
			Complex g;
			if (x >= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), atan(y2 / x) * 180 / M_PI * -1);
			}
			else if (y2 <= 0)
			{
				g = Complex(pow(x, 2) + pow(y2, 2), 180 - atan(y2 / x) * 180 / M_PI);
			}
			else
			{
				g = Complex(pow(x, 2) + pow(y2, 2), -180 - atan(y2 / x) * 180 / M_PI);
			}
			parameter[G] = g;
			map<chartMode, tuple<long double, long double>> chart;
			Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(x, y2);
			Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(x, y2);
			Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(x, y2);
			Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(x, y2);
			chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
			chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
			chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
			chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
			circuitElements->GetCircuitElements()[j]->SetChartParameters(chart);
			circuitElements->GetCircuitElements()[j]->SetParameter(parameter);
			break;
		}
		}
		SystemParameters::tunedElements = temp;
		SystemParameters::tuned = true;
	}
	update();
}

void TuneWidget::SwitchMode(Complex z, Complex y, int j)
{

	switch (circuitElements->GetCircuitElements()[j]->GetMode())
	{
	case ResistorShunt:
	{
		Complex params = SystemParameters::EditResistorShunt(circuitElements, z, j);
		SystemParameters::AddElement(circuitElements, params.real(), params.imag(), j);
		break;
	}
	case InductionShunt:
	{
		long double r1 = z.imag();
		long double r2 = circuitElements->GetCircuitElements()[j]->GetValue() * 2 * M_PI * circuitElements->frequencyFirstPoint + r1;
		Complex params = SystemParameters::EditCapIndShunt(circuitElements, j, r1, r2);
		SystemParameters::AddElement(circuitElements, params.real(), params.imag(), j);
		break;
	}
	case CapacitorShunt:
	{
		long double r1 = z.imag();
		long double r2 = r1 - 1 / (circuitElements->GetCircuitElements()[j]->GetValue() * 2 * M_PI * circuitElements->frequencyFirstPoint);
		Complex params = SystemParameters::EditCapIndShunt(circuitElements, j, r1, r2);
		SystemParameters::AddElement(circuitElements, params.real(), params.imag(), j);
		break;
	}
	case ResistorParallel:
	{
		Complex params = SystemParameters::EditResistorParallel(circuitElements, y, j);
		SystemParameters::AddElement(circuitElements, params.real(), params.imag(), j);
		break;
	}
	case InductionParallel:
	{
		long double r1 = y.imag();
		long double r2 = r1 - (M_PI * 500 * 100) / (circuitElements->GetCircuitElements()[j]->GetValue() * circuitElements->frequencyFirstPoint * 1e9 / 1e6);
		Complex params = SystemParameters::EditCapIndParallel(circuitElements, j, r1, r2);
		SystemParameters::AddElement(circuitElements, params.real(), params.imag(), j);
		break;
	}
	case CapacitorParallel:
	{
		long double r1 = y.imag();
		long double r2 = r1 + (circuitElements->GetCircuitElements()[j]->GetValue() * M_PI * circuitElements->frequencyFirstPoint * 1e12 / 1e6) / 500;
		Complex params = SystemParameters::EditCapIndParallel(circuitElements, j, r1, r2);
		SystemParameters::AddElement(circuitElements, params.real(), params.imag(), j);
		break;
	}
	case Line:
	{
		Complex params = SystemParameters::EditLine(circuitElements, z, j);
		SystemParameters::AddElement(circuitElements, params.real(), params.imag(), j);
		break;
	}
	case OSLine:
	{
		VerticalLinesElement* elem = dynamic_cast<VerticalLinesElement*>(circuitElements->GetCircuitElements()[j]);
		long double tn;
		long double angle = 2 * M_PI * elem->GetLambda();
		if (elem->GetLambda() > 0.25)
		{
			angle -= M_PI;
		}
		tn = tan(angle) * 1000 / elem->GetValue();
		Complex params = SystemParameters::EditOSSSLine(circuitElements, y, tn, elem, j);
		SystemParameters::AddElement(circuitElements, params.real(), params.imag(), j);
		Complex y3 = SystemParameters::yCalculation(params.real(), params.imag());
		long double theta;
		long double lambda;
		long double o;
		long double l;
		o = atan((y3.imag() - y.imag()) / 1000 * elem->GetValue());
		if (o < 0)
		{
			o += M_PI;
		}
		theta = o * 180 / M_PI;
		l = o * 299792458 / (2 * M_PI * 1e9);
		lambda = l * 1e9 / 299792458;
		long double er = pow(elem->GetElectricalLength() / elem->GetMechanicalLength(), 2);
		elem->SetElectricalLength(l * 1000);
		elem->SetMechanicalLength(l * 1000 / sqrt(er));
		elem->SetLambda(lambda);
		elem->SetTheta(theta);
		break;
	}
	case SSLine:
	{
		VerticalLinesElement* elem = dynamic_cast<VerticalLinesElement*>(circuitElements->GetCircuitElements()[j]);
		long double tn;
		long double angle = 2 * M_PI * elem->GetLambda();
		if (elem->GetLambda() > 0.25)
		{
			angle -= M_PI;
		}
		tn = -1000 / tan(angle) / elem->GetValue();
		Complex params = SystemParameters::EditOSSSLine(circuitElements, y, tn, elem, j);
		SystemParameters::AddElement(circuitElements, params.real(), params.imag(), j);
		Complex y3 = SystemParameters::yCalculation(params.real(), params.imag());
		long double theta;
		long double lambda;
		long double o;
		long double l;
		o = -atan(1 / ((y3.imag() - y.imag()) / 1000 * elem->GetValue()));
		if (o < 0)
		{
			o += M_PI;
		}
		theta = o * 180 / M_PI;
		l = o * 299792458 / (2 * M_PI * 1e9);
		lambda = l * 1e9 / 299792458;
		long double er = pow(elem->GetElectricalLength() / elem->GetMechanicalLength(), 2);
		elem->SetElectricalLength(l * 1000);
		elem->SetMechanicalLength(l * 1000 / sqrt(er));
		elem->SetLambda(lambda);
		elem->SetTheta(theta);
		break;
	}
	case Transform:
	{
		long double x;
		long double y2;
		long double t;
		long double r1 = z.real();
		long double r2 = pow(circuitElements->GetCircuitElements()[j]->GetValue(), 2) * r1;
		r2 = r2 / SystemParameters::z0;
		long double q = z.imag() / z.real();
		long double rIm = q * r2;
		long double denominator = (r2 + 1) * (r2 + 1) + rIm * rIm;

		if (denominator != 0) {
			x = (r2 * r2 + rIm * rIm - 1) / denominator;
			y2 = (2 * rIm) / denominator;
		}
		else {
			x = -1;
			y2 = 0;
		}
		y2 *= -1;
		SystemParameters::AddElement(circuitElements, x, y2, j);
		break;
	}
	}
}

/// <summary>
/// Сброс минимального/максимального значения у элемента.
/// </summary>
void TuneWidget::MinMaxButton_clicked()
{
	int i = 0;
	int k = 0;
	for (auto var : sliders)
	{
		var->setValue(50);
		long long n = 1;
		if (boxes.size() != sliders.size())
		{
			QGroupBox* tmp = (QGroupBox*)sliders[i]->parent();
			QGroupBox* tmp2 = (QGroupBox*)tmp->parent();
			for (auto var : boxes)
			{
				if (boxes[k] == tmp2)
				{
					break;
				}
				k++;
			}
		}
		else
		{
			k = i;
		}
		if (tuned->GetCircuitElements()[k]->GetMode() == Line ||
			tuned->GetCircuitElements()[k]->GetMode() == OSLine ||
			tuned->GetCircuitElements()[k]->GetMode() == SSLine)
		{
			if (i == sliders.size() - 1)
			{
				if (sliders[i]->parent()->parent() == sliders[i - 1]->parent()->parent())
				{
					VerticalLinesElement* tmp3 = dynamic_cast<VerticalLinesElement*>(tuned->GetCircuitElements()[k]);
					long double maxVal;
					long double minVal;
					maxVal = tmp3->GetLambda() + tmp3->GetLambda() * 0.5;
					minVal = tmp3->GetLambda() - tmp3->GetLambda() * 0.5;
					if (maxVal >= 0.5)
					{
						maxVal = 0.499;
						long double step = (maxVal - minVal) / 100;
						long double val = tmp3->GetLambda() - minVal;
						val /= step;
						var->setValue(val);
					}
					maxValue[i]=maxVal;
					minValue[i]=minVal;
				}
				else
				{
					maxValue[i] = (tuned->GetCircuitElements()[k]->GetValue() + tuned->GetCircuitElements()[k]->GetValue() * 0.5);
					minValue[i] = (tuned->GetCircuitElements()[k]->GetValue() - tuned->GetCircuitElements()[k]->GetValue() * 0.5);
				}
			}
			else
			{
				if (sliders[i]->parent()->parent() == sliders[i + 1]->parent()->parent())
				{
					maxValue[i] = (tuned->GetCircuitElements()[k]->GetValue() + tuned->GetCircuitElements()[k]->GetValue() * 0.5);
					minValue[i] = (tuned->GetCircuitElements()[k]->GetValue() - tuned->GetCircuitElements()[k]->GetValue() * 0.5);
				}
				else
				{
					VerticalLinesElement* tmp3 = dynamic_cast<VerticalLinesElement*>(tuned->GetCircuitElements()[k]);
					long double maxVal;
					long double minVal;
					maxVal = tmp3->GetLambda() + tmp3->GetLambda() * 0.5;
					minVal = tmp3->GetLambda() - tmp3->GetLambda() * 0.5;
					if (maxVal >= 0.5)
					{
						maxVal = 0.499;
						long double step = (maxVal - minVal) / 100;
						long double val = tmp3->GetLambda() - minVal;
						val /= step;
						var->setValue(val);
					}
					maxValue[i] = maxVal;
					minValue[i] = minVal;
				}
			}
		}
		else
		{
			if (tuned->GetCircuitElements()[k]->GetMode() == InductionParallel || tuned->GetCircuitElements()[k]->GetMode() == InductionShunt)
			{
				n = 1e9;
			}
			else if (tuned->GetCircuitElements()[k]->GetMode() == CapacitorParallel || tuned->GetCircuitElements()[k]->GetMode() == CapacitorShunt)
			{
				n = 1e12;
			}
			maxValue[i] = (tuned->GetCircuitElements()[k]->GetValue() + tuned->GetCircuitElements()[k]->GetValue() * 0.5);
			minValue[i] = (tuned->GetCircuitElements()[k]->GetValue() - tuned->GetCircuitElements()[k]->GetValue() * 0.5);
			
		}
		minLabels[i]->setText(QString::number(minValue[i] * n));
		maxLabels[i]->setText(QString::number(maxValue[i] * n));
		i++;
	}
	update();
}

void TuneWidget::RemoveOnLoad()
{
	RemoveAll();
}