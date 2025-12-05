#include "EditWidget.h"
#include "systemParameters.h"

/// <summary>
/// Коснтруктор класса.
/// </summary>
/// <param name="parent">Родительский виджет.</param>
/// <param name="circuit">Цепь.</param>
/// <param name="elem">Элемент.</param>
EditWidget::EditWidget(QWidget *parent, CircuitElements* circuit, Element* elem)
	: QWidget(parent)
{
	SetupUI();
	this->setMinimumSize(400, 800);
	circuitElements = circuit;
	edited = elem;
	RLineEdit->setDisabled(true);
	RComboBox->addItem(QStringLiteral(u"mOhm"));
	RComboBox->addItem(QStringLiteral(u"Ohm"));
	RComboBox->addItem(QStringLiteral(u"KOhm"));
	RComboBox->addItem(QStringLiteral(u"MOhm"));
	RComboBox->addItem(QStringLiteral(u"GOhm"));
	RComboBox->setCurrentIndex(1);
	RComboBox->setDisabled(true);
	LLineEdit->setDisabled(true);
	LComboBox->addItem(QStringLiteral(u"uH"));
	LComboBox->addItem(QStringLiteral(u"nH"));
	LComboBox->addItem(QStringLiteral(u"pH"));
	LComboBox->setCurrentIndex(1);
	LComboBox->setDisabled(true);
	CLineEdit->setDisabled(true);
	CComboBox->addItem(QStringLiteral(u"uF"));
	CComboBox->addItem(QStringLiteral(u"nF"));
	CComboBox->addItem(QStringLiteral(u"pF"));
	CComboBox->setCurrentIndex(2);
	CComboBox->setDisabled(true);
	NLineEdit->setDisabled(true);
	Z0LineEdit->setDisabled(true);
	ErLineEdit->setDisabled(true);
	LLambdaLineEdit->setDisabled(true);
	LElMMLineEdit->setDisabled(true);
	LPhMMLineEdit->setDisabled(true);
	AlphaLineEdit->setDisabled(true);
	mode curMode = elem->GetMode();
	if (curMode == ResistorParallel || curMode == ResistorShunt)
	{
		RLineEdit->setEnabled(true);
		RComboBox->setEnabled(true);
		long double val = 1e-3;
		RComboBox->setCurrentIndex(0);
		if (elem->GetValue() > 1e9)
		{
			val = 1e9;
			RComboBox->setCurrentIndex(4);
		}
		else if (elem->GetValue() > 1e6)
		{
			val = 1e6;
			RComboBox->setCurrentIndex(3);
		}
		else if (elem->GetValue() > 1e3)
		{
			val = 1e3;
			RComboBox->setCurrentIndex(2);
		}
		else if (elem->GetValue() > 1)
		{
			val = 1;
			RComboBox->setCurrentIndex(1);
		}
		RLineEdit->setText(QString::number((double)(elem->GetValue() / val)));
	}
	else if (curMode == CapacitorParallel || curMode == CapacitorShunt)
	{
		CLineEdit->setEnabled(true);
		CComboBox->setEnabled(true);
		long double val = elem->GetValue();
		CComboBox->setCurrentIndex(0);
		QString power;
		val *= 1e12;
		if (val < 1000)
		{
			CComboBox->setCurrentIndex(2);
		}
		else if (val < 1000000)
		{
			val /= 1e3;
			CComboBox->setCurrentIndex(1);
		}
		else
		{
			val /= 1e6;
			CComboBox->setCurrentIndex(0);
		}
		CLineEdit->setText(QString::number((double)val));
	}
	else if (curMode == InductionParallel || curMode == InductionShunt)
	{
		LLineEdit->setEnabled(true);
		LComboBox->setEnabled(true);
		long double val = elem->GetValue();
		LComboBox->setCurrentIndex(0);
		QString power;
		val *= 1e9;
		if (val < 1)
		{
			val *= 1e3;
			LComboBox->setCurrentIndex(2);
		}
		else if (val < 1000)
		{
			LComboBox->setCurrentIndex(1);
		}
		else
		{
			val /= 1e3;
			LComboBox->setCurrentIndex(0);
		}
		LLineEdit->setText(QString::number((double)val));
	}
	else if (curMode == Transform)
	{
		NLineEdit->setEnabled(true);
		NLineEdit->setText(QString::number((double)elem->GetValue()));
	}
	else if (curMode==OSLine || curMode==SSLine||curMode==Line)
	{
		Z0LineEdit->setEnabled(true);
		ErLineEdit->setEnabled(true);
		LLambdaLineEdit->setEnabled(true);
		LElMMLineEdit->setEnabled(true);
		LPhMMLineEdit->setEnabled(true);
		Z0LineEdit->setText(QString::number((double)elem->GetValue()));
		if (curMode == OSLine || curMode == SSLine)
		{
			VerticalLinesElement* vl = dynamic_cast<VerticalLinesElement*>(edited);
			ErLineEdit->setText(QString::number((double)pow(vl->GetElectricalLength() / vl->GetMechanicalLength(), 2)));
			LLambdaLineEdit->setText(QString::number((double)vl->GetLambda()));
			LElMMLineEdit->setText(QString::number((double)vl->GetElectricalLength()));
			LPhMMLineEdit->setText(QString::number((double)vl->GetMechanicalLength()));
		}
		else
		{
			LinesElement* vl = dynamic_cast<LinesElement*>(edited);
			ErLineEdit->setText(QString::number((double)pow(vl->GetElectricalLength() / vl->GetMechanicalLength(), 2)));
			LLambdaLineEdit->setText(QString::number((double)vl->GetLambda()));
			LElMMLineEdit->setText(QString::number((double)vl->GetElectricalLength()));
			LPhMMLineEdit->setText(QString::number((double)vl->GetMechanicalLength()));
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
		QDoubleValidator* phValidator = new QDoubleValidator(0.0, 149.5 / sqrt(ErLineEdit->text().toDouble()), 2, this);
		phValidator->setLocale(locale);
		LPhMMLabel->setText(QString::number(149.5 / sqrt(ErLineEdit->text().toDouble())));
		Z0LineEdit->setValidator(z0Validator);
		ErLineEdit->setValidator(erValidator);
		LLambdaLineEdit->setValidator(lambdaValidator);
		LElMMLineEdit->setValidator(elValidator);
		LPhMMLineEdit->setValidator(phValidator);
	}
	isUpdating = false;
	connect(OKButton, &QPushButton::clicked, this, &EditWidget::OKButton_clicked);
	connect(DrawButton, &QPushButton::clicked, this, &EditWidget::DrawButton_clicked);
	connect(ErLineEdit, &QLineEdit::textChanged, this, &EditWidget::onErLineEditChanged);
	connect(LLambdaLineEdit, &QLineEdit::textChanged, this, &EditWidget::onLLambdaLineEditChanged);
	connect(LElMMLineEdit, &QLineEdit::textChanged, this, &EditWidget::onLElMMLineEditChanged);
	connect(LPhMMLineEdit, &QLineEdit::textChanged, this, &EditWidget::onLPhMMLineEditChanged);
}

/// <summary>
/// Настройка пользовательского интерфейса.
/// </summary>
void EditWidget::SetupUI()
{
	this->setWindowTitle(QStringLiteral(u"Изменение элемента"));
	this->setFixedSize(400, 800);
	this->resize(400, 800);
	groupBox = new QGroupBox(this);
	groupBox->setGeometry(QRect(0, 10, 391, 711));
	groupBox->setTitle(QStringLiteral(u"Введите новые значения"));
	groupBox_2 = new QGroupBox(groupBox);
	groupBox_2->setGeometry(QRect(10, 30, 311, 80));
	groupBox_2->setTitle("R");
	RLineEdit = new QLineEdit(groupBox_2);
	RLineEdit->setGeometry(QRect(10, 40, 171, 24));
	RComboBox = new QComboBox(groupBox_2);
	RComboBox->setGeometry(QRect(190, 40, 111, 24));
	groupBox_3 = new QGroupBox(groupBox);
	groupBox_3->setGeometry(QRect(10, 130, 311, 80));
	groupBox_3->setTitle("L");
	LComboBox = new QComboBox(groupBox_3);
	LComboBox->setGeometry(QRect(190, 40, 111, 24));
	LLineEdit = new QLineEdit(groupBox_3);
	LLineEdit->setGeometry(QRect(10, 40, 171, 24));
	groupBox_4 = new QGroupBox(groupBox);
	groupBox_4->setGeometry(QRect(10, 230, 311, 80));
	groupBox_4->setTitle("C");
	CLineEdit = new QLineEdit(groupBox_4);
	CLineEdit->setGeometry(QRect(10, 40, 171, 24));
	CComboBox = new QComboBox(groupBox_4);
	CComboBox->setGeometry(QRect(190, 40, 111, 24));
	groupBox_5 = new QGroupBox(groupBox);
	groupBox_5->setGeometry(QRect(10, 330, 211, 80));
	groupBox_5->setTitle(QStringLiteral(u"Коэффициент передачи"));
	NLineEdit = new QLineEdit(groupBox_5);
	NLineEdit->setGeometry(QRect(10, 40, 171, 24));
	groupBox_6 = new QGroupBox(groupBox);
	groupBox_6->setGeometry(QRect(10, 430, 211, 80));
	groupBox_6->setTitle(QStringLiteral(u"Волновое сопротивление"));
	Z0LineEdit = new QLineEdit(groupBox_6);
	Z0LineEdit->setGeometry(QRect(10, 40, 131, 24));
	label = new QLabel(groupBox_6);
	label->setGeometry(QRect(160, 45, 55, 16));
	label->setLineWidth(0);
	label->setText(QStringLiteral(u"Ом"));
	groupBox_7 = new QGroupBox(groupBox);
	groupBox_7->setGeometry(QRect(230, 430, 151, 80));
	groupBox_7->setTitle(QStringLiteral(u"Коэффициент электрической проводимости"));
	ErLineEdit = new QLineEdit(groupBox_7);
	ErLineEdit->setGeometry(QRect(10, 40, 131, 24));
	groupBox_8 = new QGroupBox(groupBox);
	groupBox_8->setGeometry(QRect(230, 520, 151, 91));
	groupBox_8->setTitle(QStringLiteral(u"Физ. длина в мм."));
	LPhMMLineEdit = new QLineEdit(groupBox_8);
	LPhMMLineEdit->setGeometry(QRect(10, 40, 131, 24));
	label_4 = new QLabel(groupBox_8);
	label_4->setGeometry(QRect(10, 70, 41, 16));
	label_4->setText(QStringLiteral(u"макс = "));
	LPhMMLabel = new QLabel(groupBox_8);
	LPhMMLabel->setGeometry(QRect(60, 70, 61, 16));
	groupBox_9 = new QGroupBox(groupBox);
	groupBox_9->setGeometry(QRect(230, 620, 151, 80));
	groupBox_9->setTitle(QStringLiteral(u"Коэф. затухания"));
	AlphaLineEdit = new QLineEdit(groupBox_9);
	AlphaLineEdit->setGeometry(QRect(10, 40, 131, 24));
	groupBox_10 = new QGroupBox(groupBox);
	groupBox_10->setGeometry(QRect(10, 520, 101, 91));
	groupBox_10->setTitle(QStringLiteral(u"Эл. длина в рад."));
	LLambdaLineEdit = new QLineEdit(groupBox_10);
	LLambdaLineEdit->setGeometry(QRect(10, 40, 81, 24));
	label_2 = new QLabel(groupBox_10);
	label_2->setGeometry(QRect(10, 70, 51, 16));
	label_2->setText(QStringLiteral(u"макс = "));
	LLambdaLabel = new QLabel(groupBox_10);
	LLambdaLabel->setGeometry(QRect(54, 69, 51, 21));
	LLambdaLabel->setText("0.499");
	groupBox_11 = new QGroupBox(groupBox);
	groupBox_11->setGeometry(QRect(120, 520, 101, 91));
	groupBox_11->setTitle(QStringLiteral(u"Эл. длина в мм."));
	LElMMLineEdit = new QLineEdit(groupBox_11);
	LElMMLineEdit->setGeometry(QRect(10, 40, 71, 24));
	label_3 = new QLabel(groupBox_11);
	label_3->setGeometry(QRect(10, 70, 41, 16));
	label_3->setText(QStringLiteral(u"макс = "));
	LElMMLabel = new QLabel(groupBox_11);
	LElMMLabel->setGeometry(QRect(60, 70, 21, 20));
	LElMMLabel->setText("149");
	DrawButton = new QPushButton(this);
	DrawButton->setGeometry(QRect(0, 730, 391, 25));
	DrawButton->setText(QStringLiteral(u"Нарисовать"));
	OKButton = new QPushButton(this);
	OKButton->setGeometry(QRect(0, 760, 391, 25));
	OKButton->setText("OK");
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
		LLambdaLineEdit->setDisabled(true);
		LElMMLineEdit->setDisabled(true);
		LPhMMLineEdit->setDisabled(true);
		isUpdating = false;
	}
	else
	{
		isUpdating = true;
		LLambdaLineEdit->setEnabled(true);
		LElMMLineEdit->setEnabled(true);
		LPhMMLineEdit->setEnabled(true);
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
		LElMMLineEdit->setText("");
		LPhMMLineEdit->setText("");
		ErLineEdit->setDisabled(true);
		isUpdating = false;
	}
	else
	{
		ErLineEdit->setEnabled(true);
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
		LLambdaLineEdit->setText("");
		LPhMMLineEdit->setText("");
		ErLineEdit->setDisabled(true);
		isUpdating = false;
	}
	else
	{
		ErLineEdit->setEnabled(true);
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
		LLambdaLineEdit->setText("");
		LElMMLineEdit->setText("");
		ErLineEdit->setDisabled(true);
		isUpdating = false;
	}
	else
	{
		ErLineEdit->setEnabled(true);
		recalculateFromPhMM();
	}
}

/// <summary>
/// Пересчёт других текстБоксов исходя из электрической проницаемости.
/// </summary>
void EditWidget::recalculateFromEr()
{
	isUpdating = true;
	LPhMMLineEdit->setText(QString::number(LElMMLineEdit->text().toDouble()/sqrt(ErLineEdit->text().toDouble())));
	QLocale locale(QLocale::C);
	QDoubleValidator* phValidator = new QDoubleValidator(0.0, 149.5 / sqrt(ErLineEdit->text().toDouble()), 2, this);
	phValidator->setLocale(locale);
	LPhMMLineEdit->setValidator(phValidator);
	LPhMMLabel->setText(QString::number(149.5 / sqrt(ErLineEdit->text().toDouble())));
	isUpdating = false;
}

/// <summary>
/// Пересчёт других текстБоксов исходя из электрической длины в мм.
/// </summary>
void EditWidget::recalculateFromElMM()
{
	isUpdating = true;
	LPhMMLineEdit->setText(QString::number(LElMMLineEdit->text().toDouble() / sqrt(ErLineEdit->text().toDouble())));
	LLambdaLineEdit->setText(QString::number(LElMMLineEdit->text().toDouble() *1e6/ 299792458));
	isUpdating = false;
}

/// <summary>
/// Пересчёт других текстБоксов исходя из физической длины в мм.
/// </summary>
void EditWidget::recalculateFromPhMM()
{
	isUpdating = true;
	LElMMLineEdit->setText(QString::number(LPhMMLineEdit->text().toDouble() * sqrt(ErLineEdit->text().toDouble())));
	LLambdaLineEdit->setText(QString::number(LElMMLineEdit->text().toDouble() * 1e6 / 299792458));
	isUpdating = false;
}

/// <summary>
/// Пересчёт других текстБоксов исходя из электрической длины в радианах.
/// </summary>
void EditWidget::recalculateFromLambda()
{
	isUpdating = true;
	LElMMLineEdit->setText(QString::number(LLambdaLineEdit->text().toDouble()* 299792458/1e6));
	LPhMMLineEdit->setText(QString::number(LElMMLineEdit->text().toDouble() / sqrt(ErLineEdit->text().toDouble())));
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
	AddResistor(correct);
	AddCapacitor(correct);
	AddInduction(correct);
	AddTransform(correct);
	AddLines(correct);
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
					Complex params= SystemParameters::EditCapIndShunt(circuitElements, j, r1, r2);
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
					long double o;
					o = atan((y3.imag() - y.imag()) / 1000 * elem->GetValue());
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
					SystemParameters::AddElement(circuitElements, x, y2, j);
					break;
				}
			}
			SystemParameters::tunedElements = temp;
			SystemParameters::edited = true;
		}
	}
	
}

/// <summary>
/// Изменяется резистор.
/// </summary>
/// <param name="correct">Изменение корректно.</param>
void EditWidget::AddResistor(bool& correct)
{
	if (edited->GetMode() == ResistorParallel || edited->GetMode() == ResistorShunt)
	{
		QString tempR = RLineEdit->text();
		bool validateR = true;
		long double valueR = RLineEdit->text().toFloat(&validateR);
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
			if (RComboBox->currentIndex() == 0)
			{
				valueR /= 1e3;
			}
			else if (RComboBox->currentIndex() == 2)
			{
				valueR *= 1e3;
			}
			else if (RComboBox->currentIndex() == 3)
			{
				valueR *= 1e6;
			}
			else if (RComboBox->currentIndex() == 4)
			{
				valueR *= 1e9;
			}
			edited->SetValue(valueR);
		}
	}
}

/// <summary>
/// Изменяется конденсатор.
/// </summary>
/// <param name="correct">Изменение корректно.</param>
void EditWidget::AddCapacitor(bool& correct)
{
	if (edited->GetMode() == CapacitorParallel || edited->GetMode() == CapacitorShunt)
	{
		QString tempC = CLineEdit->text();
		bool validateC = true;
		long double valueC = CLineEdit->text().toFloat(&validateC);
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
			if (CComboBox->currentIndex() == 0)
			{
				valueC /= 1e6;
			}
			else if (CComboBox->currentIndex() == 1)
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
}

/// <summary>
/// Изменяется катушка.
/// </summary>
/// <param name="correct">Изменение корректно.</param>
void EditWidget::AddInduction(bool& correct)
{
	if (edited->GetMode() == InductionParallel || edited->GetMode() == InductionShunt)
	{
		QString tempL = LLineEdit->text();
		bool validateL = true;
		long double valueL = LLineEdit->text().toFloat(&validateL);
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
			if (LComboBox->currentIndex() == 0)
			{
				valueL /= 1e6;
			}
			else if (LComboBox->currentIndex() == 1)
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
}

/// <summary>
/// Изменяется трансформатор.
/// </summary>
/// <param name="correct">Изменение корректно.</param>
void EditWidget::AddTransform(bool& correct)
{
	if (edited->GetMode() == Transform)
	{
		QString tempN = NLineEdit->text();
		bool validateN = true;
		long double valueN = NLineEdit->text().toFloat(&validateN);
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
}

/// <summary>
/// Изменяется линия передач/шлейф.
/// </summary>
/// <param name="correct">Изменение корректно.</param>
void EditWidget::AddLines(bool& correct)
{
	if (edited->GetMode() == OSLine || edited->GetMode() == SSLine || edited->GetMode() == Line)
	{
		QString tempZ0 = Z0LineEdit->text();
		QString tempEr = ErLineEdit->text();
		QString tempLambda = LLambdaLineEdit->text();
		QString tempLEl = LElMMLineEdit->text();
		QString tempLPh = LPhMMLineEdit->text();
		bool validateZ0 = true;
		bool validateEr = true;
		bool validateLambda = true;
		bool validateLEl = true;
		bool validateLPh = true;
		long double valueZ0 = Z0LineEdit->text().toFloat(&validateZ0);
		long double valueEr = ErLineEdit->text().toFloat(&validateEr);
		long double valueLambda = LLambdaLineEdit->text().toFloat(&validateLambda);
		long double valueLEl = LElMMLineEdit->text().toFloat(&validateLEl);
		long double valueLPh = LPhMMLineEdit->text().toFloat(&validateLPh);
		if (!validateZ0 || !validateEr || !validateLambda || !validateLEl || !validateLPh || valueZ0 <= 0 || valueEr <= 0 || valueLambda <= 0 || valueLambda > 0.5 || valueLEl <= 0 || valueLPh <= 0)
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
}

/// <summary>
/// Деструктор класса.
/// </summary>
EditWidget::~EditWidget()
{
}