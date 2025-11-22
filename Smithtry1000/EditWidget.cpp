#include "EditWidget.h"
#include "ui_EditWidget.h"

/// <summary>
/// Коснтруктор класса.
/// </summary>
/// <param name="parent">Родительский виджет.</param>
/// <param name="circuit">Цепь.</param>
/// <param name="elem">Элемент.</param>
EditWidget::EditWidget(QWidget *parent, CircuitElements* circuit, Element* elem)
	: QWidget(parent)
	, ui(new Ui::EditWidget())
{
	ui->setupUi(this);
	this->setMinimumSize(400, 800);
	circuitElements = circuit;
	edited = elem;
	ui->RLineEdit->setDisabled(true);
	ui->RComboBox->addItem(QStringLiteral(u"mOhm"));
	ui->RComboBox->addItem(QStringLiteral(u"Ohm"));
	ui->RComboBox->addItem(QStringLiteral(u"KOhm"));
	ui->RComboBox->addItem(QStringLiteral(u"MOhm"));
	ui->RComboBox->addItem(QStringLiteral(u"GOhm"));
	ui->RComboBox->setCurrentIndex(1);
	ui->RComboBox->setDisabled(true);
	ui->LLineEdit->setDisabled(true);
	ui->LComboBox->addItem(QStringLiteral(u"uH"));
	ui->LComboBox->addItem(QStringLiteral(u"nH"));
	ui->LComboBox->addItem(QStringLiteral(u"pH"));
	ui->LComboBox->setCurrentIndex(1);
	ui->LComboBox->setDisabled(true);
	ui->CLineEdit->setDisabled(true);
	ui->CComboBox->addItem(QStringLiteral(u"uF"));
	ui->CComboBox->addItem(QStringLiteral(u"nF"));
	ui->CComboBox->addItem(QStringLiteral(u"pF"));
	ui->CComboBox->setCurrentIndex(2);
	ui->CComboBox->setDisabled(true);
	ui->NLineEdit->setDisabled(true);
	ui->Z0LineEdit->setDisabled(true);
	ui->ErLineEdit->setDisabled(true);
	ui->LLambdaLineEdit->setDisabled(true);
	ui->LElMMLineEdit->setDisabled(true);
	ui->LPhMMLineEdit->setDisabled(true);
	ui->AlphaLineEdit->setDisabled(true);
	mode curMode = elem->GetMode();
	if (curMode == ResistorParallel || curMode == ResistorShunt)
	{
		ui->RLineEdit->setEnabled(true);
		ui->RComboBox->setEnabled(true);
		long double val = 1e-3;
		ui->RComboBox->setCurrentIndex(0);
		if (elem->GetValue() > 1e9)
		{
			val = 1e9;
			ui->RComboBox->setCurrentIndex(4);
		}
		else if (elem->GetValue() > 1e6)
		{
			val = 1e6;
			ui->RComboBox->setCurrentIndex(3);
		}
		else if (elem->GetValue() > 1e3)
		{
			val = 1e3;
			ui->RComboBox->setCurrentIndex(2);
		}
		else if (elem->GetValue() > 1)
		{
			val = 1;
			ui->RComboBox->setCurrentIndex(1);
		}
		ui->RLineEdit->setText(QString::number((double)(elem->GetValue() / val)));
	}
	else if (curMode == CapacitorParallel || curMode == CapacitorShunt)
	{
		ui->CLineEdit->setEnabled(true);
		ui->CComboBox->setEnabled(true);
		long double val = elem->GetValue();
		ui->CComboBox->setCurrentIndex(0);
		QString power;
		val *= 1e12;
		if (val < 1000)
		{
			ui->CComboBox->setCurrentIndex(2);
		}
		else if (val < 1000000)
		{
			val /= 1e3;
			ui->CComboBox->setCurrentIndex(1);
		}
		else
		{
			val /= 1e6;
			ui->CComboBox->setCurrentIndex(0);
		}
		ui->CLineEdit->setText(QString::number((double)val));
	}
	else if (curMode == InductionParallel || curMode == InductionShunt)
	{
		ui->LLineEdit->setEnabled(true);
		ui->LComboBox->setEnabled(true);
		long double val = elem->GetValue();
		ui->LComboBox->setCurrentIndex(0);
		QString power;
		val *= 1e9;
		if (val < 1)
		{
			val *= 1e3;
			ui->LComboBox->setCurrentIndex(2);
		}
		else if (val < 1000)
		{
			ui->LComboBox->setCurrentIndex(1);
		}
		else
		{
			val /= 1e3;
			ui->LComboBox->setCurrentIndex(0);
		}
		ui->LLineEdit->setText(QString::number((double)val));
	}
	else if (curMode == Transform)
	{
		ui->NLineEdit->setEnabled(true);
	}
	else if (curMode==OSLine || curMode==SSLine||curMode==Line)
	{
		ui->Z0LineEdit->setEnabled(true);
		ui->ErLineEdit->setEnabled(true);
		ui->LLambdaLineEdit->setEnabled(true);
		ui->LElMMLineEdit->setEnabled(true);
		ui->LPhMMLineEdit->setEnabled(true);
		ui->Z0LineEdit->setText(QString::number((double)elem->GetValue()));
		if (curMode == OSLine || curMode == SSLine)
		{
			VerticalLinesElement* vl = dynamic_cast<VerticalLinesElement*>(edited);
			ui->ErLineEdit->setText(QString::number((double)pow(vl->GetElectricalLength() / vl->GetMechanicalLength(), 2)));
			ui->LLambdaLineEdit->setText(QString::number((double)vl->GetLambda()));
			ui->LElMMLineEdit->setText(QString::number((double)vl->GetElectricalLength()));
			ui->LPhMMLineEdit->setText(QString::number((double)vl->GetMechanicalLength()));
		}
		else
		{
			LinesElement* vl = dynamic_cast<LinesElement*>(edited);
			ui->ErLineEdit->setText(QString::number((double)pow(vl->GetElectricalLength() / vl->GetMechanicalLength(), 2)));
			ui->LLambdaLineEdit->setText(QString::number((double)vl->GetLambda()));
			ui->LElMMLineEdit->setText(QString::number((double)vl->GetElectricalLength()));
			ui->LPhMMLineEdit->setText(QString::number((double)vl->GetMechanicalLength()));
		}
		QLocale locale(QLocale::C);
		QDoubleValidator* z0Validator = new QDoubleValidator(0.0, 999999.0, 2, this);
		z0Validator->setLocale(locale);
		QDoubleValidator* erValidator = new QDoubleValidator(0.0, 999999.0, 2, this);
		erValidator->setLocale(locale);
		QDoubleValidator* lambdaValidator = new QDoubleValidator(0.0, 0.499, 2, this);
		lambdaValidator->setLocale(locale);
		QDoubleValidator* elValidator = new QDoubleValidator(0.0, 149.5, 2, this);
		elValidator->setLocale(locale);
		QDoubleValidator* phValidator = new QDoubleValidator(0.0, 149.5 / sqrt(ui->ErLineEdit->text().toDouble()), 2, this);
		phValidator->setLocale(locale);
		ui->LPhMMLabel->setText(QString::number(149.5 / sqrt(ui->ErLineEdit->text().toDouble())));
		ui->Z0LineEdit->setValidator(z0Validator);
		ui->ErLineEdit->setValidator(erValidator);
		ui->LLambdaLineEdit->setValidator(lambdaValidator);
		ui->LElMMLineEdit->setValidator(elValidator);
		ui->LPhMMLineEdit->setValidator(phValidator);
	}
	isUpdating = false;
	connect(ui->OKButton, &QPushButton::clicked, this, &EditWidget::OKButton_clicked);
	connect(ui->DrawButton, &QPushButton::clicked, this, &EditWidget::DrawButton_clicked);
	connect(ui->ErLineEdit, &QLineEdit::textChanged, this, &EditWidget::onErLineEditChanged);
	connect(ui->LLambdaLineEdit, &QLineEdit::textChanged, this, &EditWidget::onLLambdaLineEditChanged);
	connect(ui->LElMMLineEdit, &QLineEdit::textChanged, this, &EditWidget::onLElMMLineEditChanged);
	connect(ui->LPhMMLineEdit, &QLineEdit::textChanged, this, &EditWidget::onLPhMMLineEditChanged);
}

/// <summary>
/// Изменение текстБокса электрической проницаемости.
/// </summary>
/// <param name="text">Строковое значение.</param>
void EditWidget::onErLineEditChanged(const QString& text)
{
	if (isUpdating)
	{
		return;
	}
	if (text.isEmpty())
	{
		isUpdating = true;
		ui->LLambdaLineEdit->setDisabled(true);
		ui->LElMMLineEdit->setDisabled(true);
		ui->LPhMMLineEdit->setDisabled(true);
		isUpdating = false;
	}
	else
	{
		isUpdating = true;
		ui->LLambdaLineEdit->setEnabled(true);
		ui->LElMMLineEdit->setEnabled(true);
		ui->LPhMMLineEdit->setEnabled(true);
		isUpdating = false;
		recalculateFromEr();
	}
}

/// <summary>
/// Изменение текстБокса электрической длины в радианах.
/// </summary>
/// <param name="text">Строковое значение.</param>
void EditWidget::onLLambdaLineEditChanged(const QString& text)
{
	if (isUpdating)
	{
		return;
	}
	if (text.isEmpty())
	{
		isUpdating = true;
		ui->LElMMLineEdit->setText("");
		ui->LPhMMLineEdit->setText("");
		ui->ErLineEdit->setDisabled(true);
		isUpdating = false;
	}
	else
	{
		ui->ErLineEdit->setEnabled(true);
		recalculateFromLambda();
	}
}

/// <summary>
/// Изменение текстБокса электрической длины в мм.
/// </summary>
/// <param name="text">Строковое значение.</param>
void EditWidget::onLElMMLineEditChanged(const QString& text)
{
	if (isUpdating)
	{
		return;
	}
	if (text.isEmpty())
	{
		isUpdating = true;
		ui->LLambdaLineEdit->setText("");
		ui->LPhMMLineEdit->setText("");
		ui->ErLineEdit->setDisabled(true);
		isUpdating = false;
	}
	else
	{
		ui->ErLineEdit->setEnabled(true);
		recalculateFromElMM();
	}
}

/// <summary>
/// Изменение текстБокса физической длины в мм.
/// </summary>
/// <param name="text">Строковое значение.</param>
void EditWidget::onLPhMMLineEditChanged(const QString& text)
{
	if (isUpdating)
	{
		return;
	}
	if (text.isEmpty())
	{
		isUpdating = true;
		ui->LLambdaLineEdit->setText("");
		ui->LElMMLineEdit->setText("");
		ui->ErLineEdit->setDisabled(true);
		isUpdating = false;
	}
	else
	{
		ui->ErLineEdit->setEnabled(true);
		recalculateFromPhMM();
	}
}

/// <summary>
/// Пересчёт других текстБоксов исходя из электрической проницаемости.
/// </summary>
void EditWidget::recalculateFromEr()
{
	isUpdating = true;
	ui->LPhMMLineEdit->setText(QString::number(ui->LElMMLineEdit->text().toDouble()/sqrt(ui->ErLineEdit->text().toDouble())));
	QLocale locale(QLocale::C);
	QDoubleValidator* phValidator = new QDoubleValidator(0.0, 149.5 / sqrt(ui->ErLineEdit->text().toDouble()), 2, this);
	phValidator->setLocale(locale);
	ui->LPhMMLineEdit->setValidator(phValidator);
	ui->LPhMMLabel->setText(QString::number(149.5 / sqrt(ui->ErLineEdit->text().toDouble())));
	isUpdating = false;
}

/// <summary>
/// Пересчёт других текстБоксов исходя из электрической длины в мм.
/// </summary>
void EditWidget::recalculateFromElMM()
{
	isUpdating = true;
	ui->LPhMMLineEdit->setText(QString::number(ui->LElMMLineEdit->text().toDouble() / sqrt(ui->ErLineEdit->text().toDouble())));
	ui->LLambdaLineEdit->setText(QString::number(ui->LElMMLineEdit->text().toDouble() *1e6/ 299792458));
	isUpdating = false;
}

/// <summary>
/// Пересчёт других текстБоксов исходя из физической длины в мм.
/// </summary>
void EditWidget::recalculateFromPhMM()
{
	isUpdating = true;
	ui->LElMMLineEdit->setText(QString::number(ui->LPhMMLineEdit->text().toDouble() * sqrt(ui->ErLineEdit->text().toDouble())));
	ui->LLambdaLineEdit->setText(QString::number(ui->LElMMLineEdit->text().toDouble() * 1e6 / 299792458));
	isUpdating = false;
}

/// <summary>
/// Пересчёт других текстБоксов исходя из электрической длины в радианах.
/// </summary>
void EditWidget::recalculateFromLambda()
{
	isUpdating = true;
	ui->LElMMLineEdit->setText(QString::number(ui->LLambdaLineEdit->text().toDouble()* 299792458/1e6));
	ui->LPhMMLineEdit->setText(QString::number(ui->LElMMLineEdit->text().toDouble() / sqrt(ui->ErLineEdit->text().toDouble())));
	isUpdating = false;
}

/// <summary>
/// Применение изменений с закрытием окна.
/// </summary>
void EditWidget::OKButton_clicked()
{
	DrawButton_clicked();
	this->close();
}

/// <summary>
/// Закрытие окна
/// </summary>
/// <param name="event">Событие закрытия.</param>
void EditWidget::closeEvent(QCloseEvent* event)
{
	SystemParameters::edit = false;
}

/// <summary>
/// Применение изменений без закрытия окна.
/// </summary>
void EditWidget::DrawButton_clicked()
{
	bool correct = true;
	if (edited->GetMode() == ResistorParallel || edited->GetMode() == ResistorShunt)
	{
		QString tempR = ui->RLineEdit->text();
		bool validateR = true;
		long double valueR = ui->RLineEdit->text().toFloat(&validateR);
		if (!validateR || valueR <= 0)
		{
			correct = false;
			QMessageBox* bx = new QMessageBox();
			bx->show();
			bx->Warning;
			QLocale locale(QLocale::C);
			bx->setText(QString::fromUtf8("Все параметры должны быть заданы положительными числами"));
			SystemParameters::exc = false;
		}
		else
		{
			if (ui->RComboBox->currentIndex() == 0)
			{
				valueR /= 1e3;
			}
			else if (ui->RComboBox->currentIndex() == 2)
			{
				valueR *= 1e3;
			}
			else if (ui->RComboBox->currentIndex() == 3)
			{
				valueR *= 1e6;
			}
			else if (ui->RComboBox->currentIndex() == 4)
			{
				valueR *= 1e9;
			}
			edited->SetValue(valueR);
		}
	}
	else if (edited->GetMode() == CapacitorParallel || edited->GetMode() == CapacitorShunt)
	{
		QString tempC = ui->CLineEdit->text();
		bool validateC = true;
		long double valueC = ui->CLineEdit->text().toFloat(&validateC);
		if (!validateC || valueC <= 0)
		{
			correct = false;
			QMessageBox* bx = new QMessageBox();
			bx->show();
			bx->Warning;
			bx->setText(QString::fromUtf8("Все параметры должны быть заданы положительными числами"));
			SystemParameters::exc = false;
		}
		else
		{
			if (ui->CComboBox->currentIndex() == 0)
			{
				valueC /= 1e6;
			}
			else if (ui->CComboBox->currentIndex() == 1)
			{
				valueC /= 1e9;
			}
			else
			{
				valueC /= 1e12;
			}
			edited->SetValue(valueC);
		}
	}
	else if (edited->GetMode() == InductionParallel || edited->GetMode() == InductionShunt)
	{
		QString tempL = ui->LLineEdit->text();
		bool validateL= true;
		long double valueL = ui->LLineEdit->text().toFloat(&validateL);
		if (!validateL || valueL <= 0)
		{
			correct = false;
			QMessageBox* bx = new QMessageBox();
			bx->show();
			bx->Warning;
			bx->setText(QString::fromUtf8("Все параметры должны быть заданы положительными числами"));
			SystemParameters::exc = false;
		}
		else
		{
			if (ui->LComboBox->currentIndex() == 0)
			{
				valueL /= 1e6;
			}
			else if (ui->LComboBox->currentIndex() == 1)
			{
				valueL /= 1e9;
			}
			else
			{
				valueL /= 1e12;
			}
			edited->SetValue(valueL);
		}
	}
	else if (edited->GetMode() == Transform)
	{
		QString tempN = ui->NLineEdit->text();
		bool validateN = true;
		long double valueN = ui->NLineEdit->text().toFloat(&validateN);
		if (!validateN || valueN <= 0)
		{
			correct = false;
			QMessageBox* bx = new QMessageBox();
			bx->show();
			bx->Warning;
			bx->setText(QString::fromUtf8("Все параметры должны быть заданы положительными числами"));
			SystemParameters::exc = false;
		}
		else
		{
			edited->SetValue(valueN);
		}
	}
	else if (edited->GetMode() == OSLine || edited->GetMode() == SSLine || edited->GetMode() == Line)
	{
		QString tempZ0 = ui->Z0LineEdit->text();
		QString tempEr = ui->ErLineEdit->text();
		QString tempLambda = ui->LLambdaLineEdit->text();
		QString tempLEl = ui->LElMMLineEdit->text();
		QString tempLPh = ui->LPhMMLineEdit->text();
		bool validateZ0 = true;
		bool validateEr = true;
		bool validateLambda = true;
		bool validateLEl = true;
		bool validateLPh = true;
		long double valueZ0 = ui->Z0LineEdit->text().toFloat(&validateZ0);
		long double valueEr = ui->ErLineEdit->text().toFloat(&validateEr);
		long double valueLambda = ui->LLambdaLineEdit->text().toFloat(&validateLambda);
		long double valueLEl = ui->LElMMLineEdit->text().toFloat(&validateLEl);
		long double valueLPh = ui->LPhMMLineEdit->text().toFloat(&validateLPh);
		if (!validateZ0 || !validateEr || !validateLambda || !validateLEl || !validateLPh || valueZ0 <= 0 || valueEr<=0 || valueLambda<=0 || valueLambda>0.5 || valueLEl<=0 || valueLPh<=0)
		{
			correct = false;
			QMessageBox* bx = new QMessageBox();
			bx->show();
			bx->Warning;
			bx->setText(QString::fromUtf8("Все параметры должны быть заданы положительными числами"));
			SystemParameters::exc = false;
		}
		else
		{
			if (edited->GetMode() == OSLine || edited->GetMode() == SSLine)
			{
				VerticalLinesElement* vl = dynamic_cast<VerticalLinesElement*>(edited);
				vl->SetValue(valueZ0);
				vl->SetLambda(valueLambda);
				vl->SetMechanicalLength(valueLPh);
				vl->SetElectricalLength(valueLEl);
			}
			else
			{
				LinesElement* vl = dynamic_cast<LinesElement*>(edited);
				vl->SetValue(valueZ0);
				vl->SetLambda(valueLambda);
				vl->SetMechanicalLength(valueLPh);
				vl->SetElectricalLength(valueLEl);
			}
		}
	}
	if (correct)
	{
		int j = 0;
		for (auto var : circuitElements->GetCircuitElements())
		{
			if (var == edited)
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
				long double o;
				o = -atan(1 / ((y3.imag() - y.imag()) / 1000 * elem->GetValue()));
				if (o < 0)
				{
					o += M_PI;
				}
				theta = o * 180 / M_PI;
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
				long double o;
				o = -atan(1 / ((y3.imag() - y.imag()) / 1000 * elem->GetValue()));
				if (o < 0)
				{
					o += M_PI;
				}
				theta = o * 180 / M_PI;
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
			SystemParameters::edited = true;
		}
	}
	
}

/// <summary>
/// Деструктор класса.
/// </summary>
EditWidget::~EditWidget()
{
	delete ui;
}
