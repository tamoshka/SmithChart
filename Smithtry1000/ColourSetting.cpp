#include "ColourSetting.h"
#include <QColorDialog>
using namespace std;

/// <summary>
/// Конструктор класса ColourSetting.
/// </summary>
/// <param name="parent"></param>
ColourSetting::ColourSetting(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::ColourSettingClass())

{
	ui->setupUi(this);
	this->setFixedSize(780,550);
	setButtonColor(ui->S11Graf, SystemParameters::s11GrafColor);
	setButtonColor(ui->S22Graf, SystemParameters::s22GrafColor);
	setButtonColor(ui->MAGGraf, SystemParameters::magGrafColor);
	setButtonColor(ui->MSGGraf, SystemParameters::msgGrafColor);
	setButtonColor(ui->KGraf, SystemParameters::kGrafColor);
	setButtonColor(ui->MuGraf, SystemParameters::muGrafColor);
	setButtonColor(ui->AmpFrS11, SystemParameters::ampS11Color);
	setButtonColor(ui->AmpFrS21, SystemParameters::ampS21Color);
	setButtonColor(ui->CircleS12, SystemParameters::circleS12);
	setButtonColor(ui->CircleS21, SystemParameters::circleS21);
	setButtonColor(ui->ColourAdmitance, SystemParameters::AdmitanceColor);
	setButtonColor(ui->ColourImpedance, SystemParameters::ImpedanceColor);
	setButtonColor(ui->GridGrafOneColor, SystemParameters::gridGrafOneColor);
	setButtonColor(ui->GridGrafTwoColor, SystemParameters::gridGrafTwoColor);
	setButtonColor(ui->DatapointCirclesColor, SystemParameters::DataPointsColor);
	setButtonColor(ui->TempLinesColor, SystemParameters::RootColor);
	setButtonColor(ui->ElementLinesColor, SystemParameters::ElementsColor);
	setButtonColor(ui->RefZColor, SystemParameters::MainImpedanceColor);
	setButtonColor(ui->RefYColor, SystemParameters::MainAdmitanceColor);
	ui->frequencyComboBox->addItem("Hz");
	ui->frequencyComboBox->addItem("KHz");
	ui->frequencyComboBox->addItem("MHz");
	ui->frequencyComboBox->addItem("GHz");
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
	ui->z0ComboBox->addItem("Ohm");
	ui->z0ComboBox->addItem("KOhm");
	ui->z0ComboBox->addItem("MOhm");
	ui->z0ComboBox->addItem("GOhm");
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

	sBoxDVSIndex[ui->spinBox] = 1;
	sBoxDVSIndex[ui->spinBox_2] = 2;
	sBoxDVSIndex[ui->spinBox_25] = 3;
	sBoxDVSIndex[ui->spinBox_46] = 4;
	sBoxDVSIndex[ui->spinBox_47] = 5;
	sBoxDVSIndex[ui->spinBox_43] = 7;
	sBoxDVSIndex[ui->spinBox_44] = 8;


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
	connect(ui->S11Graf, &QPushButton::clicked, this, &ColourSetting::S11Graf);
	connect(ui->S22Graf, &QPushButton::clicked, this, &ColourSetting::S22Graf);
	connect(ui->MAGGraf, &QPushButton::clicked, this, &ColourSetting::MAGGraf);
	connect(ui->MSGGraf, &QPushButton::clicked, this, &ColourSetting::MSGGraf);
	connect(ui->KGraf, &QPushButton::clicked, this, &ColourSetting::KGraf);
	connect(ui->MuGraf, &QPushButton::clicked, this, &ColourSetting::MuGraf);
	connect(ui->AmpFrS11, &QPushButton::clicked, this, &ColourSetting::AmpFrS11);
	connect(ui->AmpFrS21, &QPushButton::clicked, this, &ColourSetting::AmpFrS21);
	connect(ui->CircleS12, &QPushButton::clicked, this, &ColourSetting::CircleS12);
	connect(ui->CircleS21, &QPushButton::clicked, this, &ColourSetting::CircleS21);
	connect(ui->ColourAdmitance, &QPushButton::clicked, this, &ColourSetting::ColourAdmitance);
	connect(ui->ColourImpedance, &QPushButton::clicked, this, &ColourSetting::ColourImpedance);
	connect(ui->ButtonCancel, &QPushButton::clicked, this, &ColourSetting::ButtonCancel);
	connect(ui->ButtonOK, &QPushButton::clicked, this, &ColourSetting::ButtonOK);
	connect(ui->GridGrafOneColor, &QPushButton::clicked, this, &ColourSetting::GridGrafOneColor);
	connect(ui->GridGrafTwoColor, &QPushButton::clicked, this, &ColourSetting::GridGrafTwoColor);
	connect(ui->DatapointCirclesColor, &QPushButton::clicked, this, &ColourSetting::DatapointCirclesColor);
	connect(ui->TempLinesColor, &QPushButton::clicked, this, &ColourSetting::TempLinesColor);
	connect(ui->ElementLinesColor, &QPushButton::clicked, this, &ColourSetting::ElementLinesColor);
	connect(ui->RefYColor, &QPushButton::clicked, this, &ColourSetting::RefYColor);
	connect(ui->RefZColor, &QPushButton::clicked, this, &ColourSetting::RefZColor);
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
	connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(ui->spinBox_2, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(ui->spinBox_25, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(ui->spinBox_43, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(ui->spinBox_44, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(ui->spinBox_46, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(ui->spinBox_47, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);

	connect(ui->spinBox_23, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::AmpFrLine);
	connect(ui->spinBox_24, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::AmpFrLine);
	connect(ui->DefaultButton, &QPushButton::clicked, this, &ColourSetting::DefaultClicked);
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
/// Настройка цветов для S11.
/// </summary>
void ColourSetting::S11Graf()
{
	QColor newColor = QColorDialog::getColor(SystemParameters::s11GrafColor, this);
	if (newColor.isValid()) 
	{
		SystemParameters::s11GrafColor = newColor;
		setButtonColor(ui->S11Graf, SystemParameters::s11GrafColor);
		emit grafOneColor();
	}
}

/// <summary>
/// Настройка цветов для S22.
/// </summary>
void ColourSetting::S22Graf()
{
	QColor newColor = QColorDialog::getColor(SystemParameters::s22GrafColor, this);
	if (newColor.isValid()) 
	{
		SystemParameters::s22GrafColor = newColor;
		setButtonColor(ui->S22Graf, SystemParameters::s22GrafColor);
		emit grafOneColor();
	}
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
/// Настройка цвета MAG.
/// </summary>
void ColourSetting::MAGGraf()
{
	QColor newColor = QColorDialog::getColor(SystemParameters::magGrafColor, this);
	if (newColor.isValid()) 
	{
		SystemParameters::magGrafColor = newColor;
		setButtonColor(ui->MAGGraf, SystemParameters::magGrafColor);
		emit grafTwoColor();
	}
}

/// <summary>
/// Настройка цвета MSG.
/// </summary>
void ColourSetting::MSGGraf()
{
	QColor newColor = QColorDialog::getColor(SystemParameters::msgGrafColor, this);
	if (newColor.isValid()) 
	{
		SystemParameters::msgGrafColor = newColor;
		setButtonColor(ui->MSGGraf, SystemParameters::msgGrafColor);
		emit grafTwoColor();
	}
}

/// <summary>
/// Настройка цвета K.
/// </summary>
void ColourSetting::KGraf()
{
	QColor newColor = QColorDialog::getColor(SystemParameters::kGrafColor, this);
	if (newColor.isValid()) 
	{
		SystemParameters::kGrafColor = newColor;
		setButtonColor(ui->KGraf, SystemParameters::kGrafColor);
		emit grafTwoColor();
	}
}

/// <summary>
/// Настройка цвета mu.
/// </summary>
void ColourSetting::MuGraf()
{
	QColor newColor = QColorDialog::getColor(SystemParameters::muGrafColor, this);
	if (newColor.isValid()) 
	{
		SystemParameters::muGrafColor = newColor;
		setButtonColor(ui->MuGraf, SystemParameters::muGrafColor);
		emit grafTwoColor();
	}
}

/// <summary>
/// Настройка цвета S11 для АЧХ.
/// </summary>
void ColourSetting::AmpFrS11()
{
	QColor newColor = QColorDialog::getColor(SystemParameters::ampS11Color, this);
	if (newColor.isValid()) 
	{
		SystemParameters::ampS11Color = newColor;
		setButtonColor(ui->AmpFrS11, SystemParameters::ampS11Color);
		emit signal();
	}
}

/// <summary>
/// Настройка цвета S21 для АЧХ.
/// </summary>
void ColourSetting::AmpFrS21()
{
	QColor newColor = QColorDialog::getColor(SystemParameters::ampS21Color, this);
	if (newColor.isValid())
	{
		SystemParameters::ampS21Color = newColor;
		setButtonColor(ui->AmpFrS21, SystemParameters::ampS21Color);
		emit signal();
	}
}

/// <summary>
/// Настройка цвета S12.
/// </summary>
void ColourSetting::CircleS12()
{
	QColor newColor = QColorDialog::getColor(SystemParameters::circleS12, this);
	if (newColor.isValid())
	{
		SystemParameters::circleS12 = newColor;
		setButtonColor(ui->CircleS12, SystemParameters::circleS12);
		emit signalS12S21();
	}
}

/// <summary>
/// Настройка цвета S21.
/// </summary>
void ColourSetting::CircleS21()
{
	QColor newColor = QColorDialog::getColor(SystemParameters::circleS21, this);
	if (newColor.isValid())
	{
		SystemParameters::circleS21 = newColor;
		setButtonColor(ui->CircleS21, SystemParameters::circleS21);
		emit signalS12S21();
	}
}

/// <summary>
/// Настройка цвета линий сопротивления.
/// </summary>
void ColourSetting::ColourImpedance()
{
	QColor newColor = QColorDialog::getColor(SystemParameters::ImpedanceColor, this);
	if (newColor.isValid())
	{
		SystemParameters::ImpedanceColor = newColor;
		setButtonColor(ui->ColourImpedance, SystemParameters::ImpedanceColor);
		emit signalDVS();
	}
}

/// <summary>
/// Настройка цвета линии проводимости.
/// </summary>
void ColourSetting::ColourAdmitance()
{
	QColor newColor = QColorDialog::getColor(SystemParameters::AdmitanceColor, this);
	if (newColor.isValid())
	{
		SystemParameters::AdmitanceColor = newColor;
		setButtonColor(ui->ColourAdmitance, SystemParameters::AdmitanceColor);
		emit signalDVS();
	}
}

/// <summary>
/// Настройка цвета сетки у графика S11/S22.
/// </summary>
void ColourSetting::GridGrafOneColor()
{
	QColor newColor = QColorDialog::getColor(SystemParameters::gridGrafOneColor, this);
	if (newColor.isValid())
	{
		SystemParameters::gridGrafOneColor = newColor;
		setButtonColor(ui->GridGrafOneColor, SystemParameters::gridGrafOneColor);
		emit grafOneColor();
	}
}

/// <summary>
/// Настройка цвета сетки у графиков K, mu, Mag, MSG.
/// </summary>
void ColourSetting::GridGrafTwoColor()
{
	QColor newColor = QColorDialog::getColor(SystemParameters::gridGrafTwoColor, this);
	if (newColor.isValid())
	{
		SystemParameters::gridGrafTwoColor = newColor;
		setButtonColor(ui->GridGrafTwoColor, SystemParameters::gridGrafTwoColor);
		emit grafTwoColor();
	}
}

/// <summary>
/// Настройка цвета точек.
/// </summary>
void ColourSetting::DatapointCirclesColor()
{
	QColor newColor = QColorDialog::getColor(SystemParameters::DataPointsColor, this);
	if (newColor.isValid())
	{
		SystemParameters::DataPointsColor = newColor;
		setButtonColor(ui->DatapointCirclesColor, SystemParameters::DataPointsColor);
		emit signalDVS();
	}
}

/// <summary>
/// Настройка цвета маршрутов для передвижения курсора.
/// </summary>
void ColourSetting::TempLinesColor()
{
	QColor newColor = QColorDialog::getColor(SystemParameters::RootColor, this);
	if (newColor.isValid())
	{
		SystemParameters::RootColor = newColor;
		setButtonColor(ui->TempLinesColor, SystemParameters::RootColor);
		emit signalDVS();
	}
}

/// <summary>
/// Настройка цвета годографов.
/// </summary>
void ColourSetting::ElementLinesColor()
{
	QColor newColor = QColorDialog::getColor(SystemParameters::ElementsColor, this);
	if (newColor.isValid())
	{
		SystemParameters::ElementsColor = newColor;
		setButtonColor(ui->ElementLinesColor, SystemParameters::ElementsColor);
		emit signalDVS();
	}
}

/// <summary>
/// Настройка цвета опорной проводимости.
/// </summary>
void ColourSetting::RefYColor()
{
	QColor newColor = QColorDialog::getColor(SystemParameters::MainAdmitanceColor, this);
	if (newColor.isValid())
	{
		SystemParameters::MainAdmitanceColor = newColor;
		setButtonColor(ui->RefYColor, SystemParameters::MainAdmitanceColor);
		emit signalDVS();
	}
}

/// <summary>
/// Настройка цвета опорного сопротивления.
/// </summary>
void ColourSetting::RefZColor()
{
	QColor newColor = QColorDialog::getColor(SystemParameters::MainImpedanceColor, this);
	if (newColor.isValid())
	{
		SystemParameters::MainImpedanceColor = newColor;
		setButtonColor(ui->RefZColor, SystemParameters::MainImpedanceColor);
		emit signalDVS();
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
}