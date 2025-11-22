#include "ColourSetting.h"
#include <QColorDialog>
using namespace std;

/// <summary>
/// Конструктор класса ColourSetting.
/// </summary>
/// <param name="parent">Родительский класс.</param>
ColourSetting::ColourSetting(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::ColourSettingClass())

{
	ui->setupUi(this);
	this->setFixedSize(780,550);

	DVScolors[ui->ColourAdmitance] = &SystemParameters::AdmitanceColor;
	DVScolors[ui->ColourImpedance] = &SystemParameters::ImpedanceColor;
	DVScolors[ui->DatapointCirclesColor] = &SystemParameters::DataPointsColor;
	DVScolors[ui->TempLinesColor] = &SystemParameters::RootColor;
	DVScolors[ui->ElementLinesColor] = &SystemParameters::ElementsColor;
	DVScolors[ui->RefZColor] = &SystemParameters::MainImpedanceColor;
	DVScolors[ui->RefYColor] = &SystemParameters::MainAdmitanceColor;
	DVScolors[ui->QCirclesColor] = &SystemParameters::QCirclesColor;
	DVScolors[ui->VSWRCirclesColor] = &SystemParameters::VSWRColor;
	DVScolors[ui->MainCircleColor] = &SystemParameters::MainCircleColor;

	colors[ui->S11Graf] = &SystemParameters::s11GrafColor;
	colors[ui->S22Graf] = &SystemParameters::s22GrafColor;
	colors[ui->MAGGraf] = &SystemParameters::magGrafColor;
	colors[ui->MSGGraf] = &SystemParameters::msgGrafColor;
	colors[ui->KGraf] = &SystemParameters::kGrafColor;
	colors[ui->MuGraf] = &SystemParameters::muGrafColor;
	colors[ui->CircleS12] = &SystemParameters::circleS12;
	colors[ui->CircleS21] = &SystemParameters::circleS21;
	colors[ui->GridGrafOneColor] = &SystemParameters::gridGrafOneColor;
	colors[ui->GridGrafTwoColor] = &SystemParameters::gridGrafTwoColor;

	AmpFrcolors[ui->AmpFrS11] = &SystemParameters::ampS11Color;
	AmpFrcolors[ui->AmpFrS21] = &SystemParameters::ampS21Color;

	setButtonColor(ui->S11Graf, SystemParameters::s11GrafColor);
	setButtonColor(ui->S22Graf, SystemParameters::s22GrafColor);
	setButtonColor(ui->MAGGraf, SystemParameters::magGrafColor);
	setButtonColor(ui->MSGGraf, SystemParameters::msgGrafColor);
	setButtonColor(ui->KGraf, SystemParameters::kGrafColor);
	setButtonColor(ui->MuGraf, SystemParameters::muGrafColor);
	setButtonColor(ui->CircleS12, SystemParameters::circleS12);
	setButtonColor(ui->CircleS21, SystemParameters::circleS21);
	setButtonColor(ui->GridGrafOneColor, SystemParameters::gridGrafOneColor);
	setButtonColor(ui->GridGrafTwoColor, SystemParameters::gridGrafTwoColor);

	setButtonColor(ui->ColourAdmitance, SystemParameters::AdmitanceColor);
	setButtonColor(ui->ColourImpedance, SystemParameters::ImpedanceColor);
	setButtonColor(ui->DatapointCirclesColor, SystemParameters::DataPointsColor);
	setButtonColor(ui->TempLinesColor, SystemParameters::RootColor);
	setButtonColor(ui->ElementLinesColor, SystemParameters::ElementsColor);
	setButtonColor(ui->RefZColor, SystemParameters::MainImpedanceColor);
	setButtonColor(ui->RefYColor, SystemParameters::MainAdmitanceColor);
	setButtonColor(ui->QCirclesColor, SystemParameters::QCirclesColor);
	setButtonColor(ui->VSWRCirclesColor, SystemParameters::VSWRColor);
	setButtonColor(ui->MainCircleColor, SystemParameters::MainCircleColor);

	setButtonColor(ui->AmpFrS11, SystemParameters::ampS11Color);
	setButtonColor(ui->AmpFrS21, SystemParameters::ampS21Color);

	ui->StabilityColor->setDisabled(true);
	ui->GainColor->setDisabled(true);
	ui->NoiseColor->setDisabled(true);
	ui->SweepLinesColor->setDisabled(true);
	ui->SweepCirclesColor->setDisabled(true);
	ui->SweepCirclesBox->setDisabled(true);
	ui->SweepLinesBox->setDisabled(true);
	ui->NoiseBox->setDisabled(true);
	ui->GainBox->setDisabled(true);
	ui->StabilityBox->setDisabled(true);
	ui->DataPointsLinesBox->setDisabled(true);
	ui->DataPointsLinesColor->setDisabled(true);
	ui->checkBox->setDisabled(true);
	ui->checkBox_2->setDisabled(true);
	ui->checkBox_3->setDisabled(true);
	ui->checkBox_4->setDisabled(true);
	ui->checkBox_5->setDisabled(true);
	ui->checkBox_6->setDisabled(true);
	ui->checkBox_7->setDisabled(true);
	ui->checkBox_8->setDisabled(true);
	ui->checkBox_9->setDisabled(true);
	ui->checkBox_10->setDisabled(true);
	ui->checkBox_11->setDisabled(true);
	ui->checkBox_12->setDisabled(true);
	ui->checkBox_13->setDisabled(true);
	ui->checkBox_14->setDisabled(true);
	ui->checkBox_15->setDisabled(true);
	ui->checkBox_16->setDisabled(true);
	ui->checkBox_17->setDisabled(true);
	ui->checkBox_18->setDisabled(true);

	ui->frequencyComboBox->addItem(QStringLiteral(u"Гц"));
	ui->frequencyComboBox->addItem(QStringLiteral(u"КГц"));
	ui->frequencyComboBox->addItem(QStringLiteral(u"МГц"));
	ui->frequencyComboBox->addItem(QStringLiteral(u"ГГц"));
	long double val = 1;
	ui->frequencyComboBox->setCurrentIndex(0);
	if (SystemParameters::defaultFrequency > 1e9)
	{
		val = 1e9;
		ui->frequencyComboBox->setCurrentIndex(3);
	}
	else if (SystemParameters::defaultFrequency > 1e6)
	{
		val = 1e6;
		ui->frequencyComboBox->setCurrentIndex(2);
	}
	else if (SystemParameters::defaultFrequency > 1e3)
	{
		val = 1e3;
		ui->frequencyComboBox->setCurrentIndex(1);
	}
	ui->frequencyLineEdit->setText(QString::number((double)(SystemParameters::defaultFrequency /val)));

	ui->z0ComboBox->addItem(QStringLiteral(u"Ом"));
	ui->z0ComboBox->addItem(QStringLiteral(u"КОм"));
	ui->z0ComboBox->addItem(QStringLiteral(u"МОм"));
	ui->z0ComboBox->addItem(QStringLiteral(u"ГОм"));
	ui->z0ComboBox->setCurrentIndex(0);
	val = 1;
	if (SystemParameters::z0 > 1e9)
	{
		val = 1e9;
		ui->z0ComboBox->setCurrentIndex(3);
	}
	else if (SystemParameters::z0 > 1e6)
	{
		val = 1e6;
		ui->z0ComboBox->setCurrentIndex(2);
	}
	if (SystemParameters::z0 > 1e3)
	{
		val = 1e3;
		ui->z0ComboBox->setCurrentIndex(1);
	}
	ui->z0lineEdit->setText(QString::number((double)(SystemParameters::z0/val)));

	sBoxIndex[ui->spinBox_5] = 0;
	sBoxIndex[ui->spinBox_6] = 1;
	sBoxIndex[ui->spinBox_7] = 2;
	sBoxIndex[ui->spinBox_8] = 3;
	sBoxIndex[ui->spinBox_9] = 4;
	sBoxIndex[ui->spinBox_10] = 5;
	sBoxIndex[ui->spinBox_11] = 6;
	sBoxIndex[ui->spinBox_12] = 7;
	sBoxIndex[ui->spinBox_21] = 8;
	sBoxIndex[ui->spinBox_22] = 9;

	sBoxDVSIndex[ui->ColorImpedanceBox] = 1;
	sBoxDVSIndex[ui->ColorAdmitanceBox] = 2;
	sBoxDVSIndex[ui->DataPointsBox] = 3;
	sBoxDVSIndex[ui->TempBox] = 4;
	sBoxDVSIndex[ui->ElementBox] = 5;
	sBoxDVSIndex[ui->RefZBox] = 7;
	sBoxDVSIndex[ui->RefYBox] = 8;
	sBoxDVSIndex[ui->VSWRSpinBox] = 9;
	sBoxDVSIndex[ui->QCirclesSpinBox] = 10;


	sBoxAmpFrIndex[ui->spinBox_24] = 0;
	sBoxAmpFrIndex[ui->spinBox_23] = 1;

	if (SystemParameters::rotate)
	{
		ui->verticalRadioButton->setChecked(true);
	}
	else
	{
		ui->horizontalRadioButton->setChecked(true);
	}
	for (auto it = sBoxDVSIndex.begin(); it != sBoxDVSIndex.end(); ++it) {
		it.key()->setValue(SystemParameters::linesWidth[it.value()]);
	}
	for (auto it = sBoxIndex.begin(); it != sBoxIndex.end(); ++it) {
		it.key()->setValue(SystemParameters::sPlotline[it.value()]);
	}
	for (auto it = sBoxAmpFrIndex.begin(); it != sBoxAmpFrIndex.end(); ++it) {
		it.key()->setValue(SystemParameters::ampFrline[it.value()]);
	}

	connect(ui->horizontalRadioButton, &QRadioButton::clicked, this, &ColourSetting::VerticalHorizontalChanged);
	connect(ui->verticalRadioButton, &QRadioButton::clicked, this, &ColourSetting::VerticalHorizontalChanged);

	connect(ui->S11Graf, &QPushButton::clicked, this, &ColourSetting::GrafOneColor);
	connect(ui->S22Graf, &QPushButton::clicked, this, &ColourSetting::GrafOneColor);
	connect(ui->GridGrafOneColor, &QPushButton::clicked, this, &ColourSetting::GrafOneColor);

	connect(ui->MAGGraf, &QPushButton::clicked, this, &ColourSetting::GrafTwoColor);
	connect(ui->MSGGraf, &QPushButton::clicked, this, &ColourSetting::GrafTwoColor);
	connect(ui->KGraf, &QPushButton::clicked, this, &ColourSetting::GrafTwoColor);
	connect(ui->MuGraf, &QPushButton::clicked, this, &ColourSetting::GrafTwoColor);
	connect(ui->GridGrafTwoColor, &QPushButton::clicked, this, &ColourSetting::GrafTwoColor);

	connect(ui->CircleS12, &QPushButton::clicked, this, &ColourSetting::CircleS12S21Color);
	connect(ui->CircleS21, &QPushButton::clicked, this, &ColourSetting::CircleS12S21Color);

	connect(ui->AmpFrS11, &QPushButton::clicked, this, &ColourSetting::AmpFrColor);
	connect(ui->AmpFrS21, &QPushButton::clicked, this, &ColourSetting::AmpFrColor);

	connect(ui->ColourAdmitance, &QPushButton::clicked, this, &ColourSetting::DVSColor);
	connect(ui->ColourImpedance, &QPushButton::clicked, this, &ColourSetting::DVSColor);
	connect(ui->DatapointCirclesColor, &QPushButton::clicked, this, &ColourSetting::DVSColor);
	connect(ui->TempLinesColor, &QPushButton::clicked, this, &ColourSetting::DVSColor);
	connect(ui->ElementLinesColor, &QPushButton::clicked, this, &ColourSetting::DVSColor);
	connect(ui->RefYColor, &QPushButton::clicked, this, &ColourSetting::DVSColor);
	connect(ui->RefZColor, &QPushButton::clicked, this, &ColourSetting::DVSColor);
	connect(ui->QCirclesColor, &QPushButton::clicked, this, &ColourSetting::DVSColor);
	connect(ui->VSWRCirclesColor, &QPushButton::clicked, this, &ColourSetting::DVSColor);
	connect(ui->MainCircleColor, &QPushButton::clicked, this, &ColourSetting::DVSColor);

	connect(ui->spinBox_5, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineCircleS12S21);
	connect(ui->spinBox_6, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineCircleS12S21);

	connect(ui->spinBox_7, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineGrafTwo);
	connect(ui->spinBox_8, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineGrafTwo);
	connect(ui->spinBox_9, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineGrafTwo);
	connect(ui->spinBox_21, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineGrafTwo);
	connect(ui->spinBox_10, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineGrafTwo);

	connect(ui->spinBox_11, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineGrafOne);
	connect(ui->spinBox_12, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineGrafOne);
	connect(ui->spinBox_22, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineGrafOne);

	connect(ui->ColorImpedanceBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(ui->ColorAdmitanceBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(ui->DataPointsBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(ui->MainCircleBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(ui->RefZBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(ui->RefYBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(ui->TempBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(ui->ElementBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(ui->VSWRSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(ui->QCirclesSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);

	connect(ui->spinBox_23, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::AmpFrLine);
	connect(ui->spinBox_24, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::AmpFrLine);

	connect(ui->DefaultButton, &QPushButton::clicked, this, &ColourSetting::DefaultClicked);

	connect(ui->ButtonCancel, &QPushButton::clicked, this, &ColourSetting::ButtonCancel);
	connect(ui->ButtonOK, &QPushButton::clicked, this, &ColourSetting::ButtonOK);
}

/// <summary>
/// Изменение выбранной radiobutton.
/// </summary>
void ColourSetting::VerticalHorizontalChanged()
{
	QRadioButton* rButton = qobject_cast<QRadioButton*>(sender());
	if (rButton == ui->horizontalRadioButton)
	{
		SystemParameters::rotate = false;
		emit rev();
	}
	else if (rButton == ui->verticalRadioButton)
	{
		SystemParameters::rotate = true;
		emit rev();
	}
}

/// <summary>
/// Деструктор класса ColourSetting.
/// </summary>
ColourSetting::~ColourSetting()
{
	delete ui;
}

/// <summary>
/// Установка цвета кнопке.
/// </summary>
/// <param name="button">Кнопка.</param>
/// <param name="color">Цвет.</param>
void ColourSetting::setButtonColor(QPushButton* button, const QColor& color)
{
	QString style = QString("QPushButton {background-color: %1; color: white;}").arg(color.name());
	button->setStyleSheet(style);
}

/// <summary>
/// Обработка отмены изменений.
/// </summary>
void ColourSetting::ButtonCancel()
{
	this->close();
}

/// <summary>
/// Обработка принятия изменений.
/// </summary>
void ColourSetting::ButtonOK()
{
	QString temp = ui->z0lineEdit->text();
	bool validate = true;
	bool allCorrect = true;
	bool allChanged = false;
	double value = ui->z0lineEdit->text().toFloat(&validate);
	if (!validate || value <= 0)
	{
		allCorrect = false;
	}
	int temp3 = 1;
	if (ui->z0ComboBox->currentIndex() == 1)
	{
		temp3 = 1000;
	}
	else if (ui->z0ComboBox->currentIndex() == 2)
	{
		temp3 = 1000000;
	}
	else if (ui->z0ComboBox->currentIndex() == 3)
	{
		temp3 = 1000000000;
	}
	value *= temp3;
	if (allCorrect)
	{
		if (value != SystemParameters::z0)
		{
			allChanged = true;
		}
	}
	QString temp2 = ui->frequencyLineEdit->text();
	bool validate2 = true;
	double value2 = ui->frequencyLineEdit->text().toFloat(&validate2);
	if (!validate2 || value2 <= 0)
	{
		allCorrect = false;
	}
	temp3 = 1;
	if (ui->frequencyComboBox->currentIndex() == 1)
	{
		temp3 = 1000;
	}
	else if (ui->frequencyComboBox->currentIndex() == 2)
	{
		temp3 = 1000000;
	}
	else if (ui->frequencyComboBox->currentIndex() == 3)
	{
		temp3 = 1000000000;
	}
	value2 *= temp3;
	if (allCorrect)
	{
		SystemParameters::defaultFrequency = value2;
		if (allChanged)
		{
			SystemParameters::prevz0 = SystemParameters::z0;
			SystemParameters::z0 = value;
			emit allchangedsignal();
		}
		this->close();
	}
	else
	{
		QMessageBox* bx = new QMessageBox();
		bx->show();
		bx->Information;
		bx->setText(QStringLiteral(u"Значения для z0 и frequency должны быть положительными."));
	}
}

/// <summary>
/// Настройка толщин линий S12 м S21.
/// </summary>
/// <param name="line">Толщина линии.</param>
void ColourSetting::LineCircleS12S21(int line)
{
	QSpinBox* sBox = qobject_cast<QSpinBox*>(sender());
	if (sBox && sBoxIndex.contains(sBox)) 
	{
		int number = sBoxIndex.value(sBox);
		SystemParameters::sPlotline[number] = line;
		emit signalS12S21();
	}
}

/// <summary>
/// Настройка толщин линий для S11/S22 графиков.
/// </summary>
/// <param name="line">Толщина линии.</param>
void ColourSetting::LineGrafOne(int line)
{
	QSpinBox* sBox = qobject_cast<QSpinBox*>(sender());
	if (sBox && sBoxIndex.contains(sBox))
	{
		int number = sBoxIndex.value(sBox);
		SystemParameters::sPlotline[number] = line;
		emit grafOneColor();
	}
}

/// <summary>
/// Настройка толщин линий для mu, k, MSG, MAG графиков.
/// </summary>
/// <param name="line">Толщина линии.</param>
void ColourSetting::LineGrafTwo(int line)
{
	QSpinBox* sBox = qobject_cast<QSpinBox*>(sender());
	if (sBox && sBoxIndex.contains(sBox))
	{
		int number = sBoxIndex.value(sBox);
		SystemParameters::sPlotline[number] = line;
		emit grafTwoColor();
	}
}

/// <summary>
/// Настройка толщин линий для ДВС.
/// </summary>
/// <param name="line">Толщина линии.</param>
void ColourSetting::DVSLine(float line)
{
	QSpinBox* sBox = qobject_cast<QSpinBox*>(sender());
	if (sBox && sBoxDVSIndex.contains(sBox))
	{
		float number = sBoxDVSIndex.value(sBox);
		SystemParameters::linesWidth[number] = line;
		emit signalDVS();
	}
}

/// <summary>
/// Настройка толщин линий для АЧХ.
/// </summary>
/// <param name="line">Толщина линии.</param>
void ColourSetting::AmpFrLine(int line)
{
	QSpinBox* sBox = qobject_cast<QSpinBox*>(sender());
	if (sBox && sBoxAmpFrIndex.contains(sBox))
	{
		float number = sBoxAmpFrIndex.value(sBox);
		SystemParameters::ampFrline[number] = line;
		emit signal();
	}
}

/// <summary>
/// Сброс всех настроек в стандарт.
/// </summary>
void ColourSetting::DefaultClicked()
{
	setButtonColor(ui->S11Graf, SystemParameters::s11GrafColorDefault);
	setButtonColor(ui->S22Graf, SystemParameters::s22GrafColorDefault);
	setButtonColor(ui->MAGGraf, SystemParameters::magGrafColorDefault);
	setButtonColor(ui->MSGGraf, SystemParameters::msgGrafColorDefault);
	setButtonColor(ui->KGraf, SystemParameters::kGrafColorDefault);
	setButtonColor(ui->MuGraf, SystemParameters::muGrafColorDefault);
	setButtonColor(ui->AmpFrS11, SystemParameters::ampS11ColorDefault);
	setButtonColor(ui->AmpFrS21, SystemParameters::ampS21ColorDefault);
	setButtonColor(ui->CircleS12, SystemParameters::circleS12Default);
	setButtonColor(ui->CircleS21, SystemParameters::circleS21Default);
	setButtonColor(ui->ColourAdmitance, SystemParameters::AdmitanceColorDefault);
	setButtonColor(ui->ColourImpedance, SystemParameters::ImpedanceColorDefault);
	setButtonColor(ui->GridGrafOneColor, SystemParameters::gridGrafOneColorDefault);
	setButtonColor(ui->GridGrafTwoColor, SystemParameters::gridGrafTwoColorDefault);
	setButtonColor(ui->DatapointCirclesColor, SystemParameters::DataPointsColorDefault);
	setButtonColor(ui->TempLinesColor, SystemParameters::RootColorDefault);
	setButtonColor(ui->ElementLinesColor, SystemParameters::ElementsColorDefault);
	setButtonColor(ui->RefZColor, SystemParameters::MainImpedanceColorDefault);
	setButtonColor(ui->RefYColor, SystemParameters::MainAdmitanceColorDefault);
	setButtonColor(ui->QCirclesColor, SystemParameters::QCirclesColorDefault);
	setButtonColor(ui->VSWRCirclesColor, SystemParameters::VSWRColorDefault);
	setButtonColor(ui->MainCircleColor, SystemParameters::MainCircleColorDefault);
	SystemParameters::s11GrafColor = SystemParameters::s11GrafColorDefault;
	SystemParameters::s22GrafColor = SystemParameters::s22GrafColorDefault;
	SystemParameters::magGrafColor = SystemParameters::magGrafColorDefault;
	SystemParameters::msgGrafColor = SystemParameters::msgGrafColorDefault;
	SystemParameters::kGrafColor = SystemParameters::kGrafColorDefault;
	SystemParameters::muGrafColor = SystemParameters::muGrafColorDefault;
	SystemParameters::ampS11Color = SystemParameters::ampS11ColorDefault;
	SystemParameters::ampS21Color = SystemParameters::ampS21ColorDefault;
	SystemParameters::circleS12 = SystemParameters::circleS12Default;
	SystemParameters::circleS21 = SystemParameters::circleS21Default;
	SystemParameters::AdmitanceColor = SystemParameters::AdmitanceColorDefault;
	SystemParameters::ImpedanceColor = SystemParameters::ImpedanceColorDefault;
	SystemParameters::gridGrafOneColor = SystemParameters::gridGrafOneColorDefault;
	SystemParameters::gridGrafTwoColor = SystemParameters::gridGrafTwoColorDefault;
	SystemParameters::DataPointsColor = SystemParameters::DataPointsColorDefault;
	SystemParameters::RootColor = SystemParameters::RootColorDefault;
	SystemParameters::ElementsColor = SystemParameters::ElementsColorDefault;
	SystemParameters::MainImpedanceColor = SystemParameters::MainImpedanceColorDefault;
	SystemParameters::MainAdmitanceColor = SystemParameters::MainAdmitanceColorDefault;
	SystemParameters::QCirclesColor = SystemParameters::QCirclesColorDefault;
	SystemParameters::VSWRColor = SystemParameters::VSWRColorDefault;
	SystemParameters::MainCircleColor = SystemParameters::MainCircleColorDefault;
	SystemParameters::linesWidth = SystemParameters::linesWidthDefault;
	SystemParameters::ampFrline = SystemParameters::ampFrlineDefault;
	SystemParameters::sPlotline = SystemParameters::sPlotlineDefault;
	SystemParameters::rotate = false;
	ui->horizontalRadioButton->setChecked(true);
	ui->z0ComboBox->setCurrentIndex(0);
	ui->frequencyComboBox->setCurrentIndex(2);
	ui->z0lineEdit->setText("50");
	ui->frequencyLineEdit->setText("500");
	for (auto it = sBoxDVSIndex.begin(); it != sBoxDVSIndex.end(); ++it) {
		it.key()->setValue(SystemParameters::linesWidth[it.value()]);
	}
	for (auto it = sBoxIndex.begin(); it != sBoxIndex.end(); ++it) {
		it.key()->setValue(SystemParameters::sPlotline[it.value()]);
	}
	for (auto it = sBoxAmpFrIndex.begin(); it != sBoxAmpFrIndex.end(); ++it) {
		it.key()->setValue(SystemParameters::ampFrline[it.value()]);
	}
	emit signal();
	emit signalDVS();
	emit grafTwoColor();
	emit signalS12S21();
	emit grafOneColor();
	emit allchangedsignal();
	emit rev();
}

/// <summary>
/// Настройка цветов для ДВС.
/// </summary>
/// <param name="line">Толщина линии.</param>
void ColourSetting::DVSColor()
{
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	if (button && DVScolors.contains(button))
	{
		QColor newColor = QColorDialog::getColor(*DVScolors[button], this);
		if (newColor.isValid())
		{
			*DVScolors[button] = newColor;
			setButtonColor(button, *DVScolors[button]);
			emit signalDVS();
		}
	}
}

/// <summary>
/// Настройка цветов для АЧХ графиков.
/// </summary>
/// <param name="line">Толщина линии.</param>
void ColourSetting::AmpFrColor()
{
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	if (button && AmpFrcolors.contains(button))
	{
		QColor newColor = QColorDialog::getColor(*AmpFrcolors[button], this);
		if (newColor.isValid())
		{
			*AmpFrcolors[button] = newColor;
			setButtonColor(button, *AmpFrcolors[button]);
			emit signal();
		}
	}
}

/// <summary>
/// Настройка цветов для S12/S21 диаграмм.
/// </summary>
/// <param name="line">Толщина линии.</param>
void ColourSetting::CircleS12S21Color()
{
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	if (button && colors.contains(button))
	{
		QColor newColor = QColorDialog::getColor(*colors[button], this);
		if (newColor.isValid())
		{
			*colors[button] = newColor;
			setButtonColor(button, *colors[button]);
			emit signalS12S21();
		}
	}
}

/// <summary>
/// Настройка цветов для S11, S22 графиков.
/// </summary>
/// <param name="line">Толщина линии.</param>
void ColourSetting::GrafOneColor()
{
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	if (button && colors.contains(button))
	{
		QColor newColor = QColorDialog::getColor(*colors[button], this);
		if (newColor.isValid())
		{
			*colors[button] = newColor;
			setButtonColor(button, *colors[button]);
			emit grafOneColor();
		}
	}
}

/// <summary>
/// Настройка цветов для mu, k, MSG, MAG графиков.
/// </summary>
/// <param name="line">Толщина линии.</param>
void ColourSetting::GrafTwoColor()
{
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	if (button && colors.contains(button))
	{
		QColor newColor = QColorDialog::getColor(*colors[button], this);
		if (newColor.isValid())
		{
			*colors[button] = newColor;
			setButtonColor(button, *colors[button]);
			emit grafTwoColor();
		}
	}
}