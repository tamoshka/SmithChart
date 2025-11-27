#include "EditWidget.h"
#include "ui_EditWidget.h"
#include "systemParameters.h"

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
		ui->NLineEdit->setText(QString::number((double)elem->GetValue()));
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

void EditWidget::AddResistor(bool& correct)
{
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
}

void EditWidget::AddCapacitor(bool& correct)
{
	if (edited->GetMode() == CapacitorParallel || edited->GetMode() == CapacitorShunt)
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
}

void EditWidget::AddInduction(bool& correct)
{
	if (edited->GetMode() == InductionParallel || edited->GetMode() == InductionShunt)
	{
		QString tempL = ui->LLineEdit->text();
		bool validateL = true;
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
}

void EditWidget::AddTransform(bool& correct)
{
	if (edited->GetMode() == Transform)
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
}

void EditWidget::AddLines(bool& correct)
{
	if (edited->GetMode() == OSLine || edited->GetMode() == SSLine || edited->GetMode() == Line)
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
	delete ui;
}