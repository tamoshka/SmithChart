#include "ColourSetting.h"
#include <QColorDialog>
#include "systemParameters.h"
using namespace std;

/// <summary>
/// Конструктор класса ColourSetting.
/// </summary>
/// <param name="parent">Родительский класс.</param>
ColourSetting::ColourSetting(QWidget *parent)
	: QWidget(parent)

{
	SetupUI();
	this->setFixedSize(780,550);

	DVScolors[ColourAdmitance] = &SystemParameters::AdmitanceColor;
	DVScolors[ColourImpedance] = &SystemParameters::ImpedanceColor;
	DVScolors[DatapointCirclesColor] = &SystemParameters::DataPointsColor;
	DVScolors[TempLinesColor] = &SystemParameters::RootColor;
	DVScolors[ElementLinesColor] = &SystemParameters::ElementsColor;
	DVScolors[RefZColor] = &SystemParameters::MainImpedanceColor;
	DVScolors[RefYColor] = &SystemParameters::MainAdmitanceColor;
	DVScolors[QCirclesColor] = &SystemParameters::QCirclesColor;
	DVScolors[VSWRCirclesColor] = &SystemParameters::VSWRColor;
	DVScolors[MainCircleColor] = &SystemParameters::MainCircleColor;

	colors[S11Graf] = &SystemParameters::s11GrafColor;
	colors[S22Graf] = &SystemParameters::s22GrafColor;
	colors[MAGGraf] = &SystemParameters::magGrafColor;
	colors[MSGGraf] = &SystemParameters::msgGrafColor;
	colors[KGraf] = &SystemParameters::kGrafColor;
	colors[MuGraf] = &SystemParameters::muGrafColor;
	colors[CircleS12] = &SystemParameters::circleS12;
	colors[CircleS21] = &SystemParameters::circleS21;
	colors[GridGrafOneColor] = &SystemParameters::gridGrafOneColor;
	colors[GridGrafTwoColor] = &SystemParameters::gridGrafTwoColor;

	AmpFrcolors[AmpFrS11] = &SystemParameters::ampS11Color;
	AmpFrcolors[AmpFrS21] = &SystemParameters::ampS21Color;

	setButtonColor(S11Graf, SystemParameters::s11GrafColor);
	setButtonColor(S22Graf, SystemParameters::s22GrafColor);
	setButtonColor(MAGGraf, SystemParameters::magGrafColor);
	setButtonColor(MSGGraf, SystemParameters::msgGrafColor);
	setButtonColor(KGraf, SystemParameters::kGrafColor);
	setButtonColor(MuGraf, SystemParameters::muGrafColor);
	setButtonColor(CircleS12, SystemParameters::circleS12);
	setButtonColor(CircleS21, SystemParameters::circleS21);
	setButtonColor(GridGrafOneColor, SystemParameters::gridGrafOneColor);
	setButtonColor(GridGrafTwoColor, SystemParameters::gridGrafTwoColor);

	setButtonColor(ColourAdmitance, SystemParameters::AdmitanceColor);
	setButtonColor(ColourImpedance, SystemParameters::ImpedanceColor);
	setButtonColor(DatapointCirclesColor, SystemParameters::DataPointsColor);
	setButtonColor(TempLinesColor, SystemParameters::RootColor);
	setButtonColor(ElementLinesColor, SystemParameters::ElementsColor);
	setButtonColor(RefZColor, SystemParameters::MainImpedanceColor);
	setButtonColor(RefYColor, SystemParameters::MainAdmitanceColor);
	setButtonColor(QCirclesColor, SystemParameters::QCirclesColor);
	setButtonColor(VSWRCirclesColor, SystemParameters::VSWRColor);
	setButtonColor(MainCircleColor, SystemParameters::MainCircleColor);

	setButtonColor(AmpFrS11, SystemParameters::ampS11Color);
	setButtonColor(AmpFrS21, SystemParameters::ampS21Color);

	StabilityColor->setDisabled(true);
	GainColor->setDisabled(true);
	NoiseColor->setDisabled(true);
	SweepLinesColor->setDisabled(true);
	SweepCirclesColor->setDisabled(true);
	SweepCirclesBox->setDisabled(true);
	SweepLinesBox->setDisabled(true);
	NoiseBox->setDisabled(true);
	GainBox->setDisabled(true);
	StabilityBox->setDisabled(true);
	DataPointsLinesBox->setDisabled(true);
	DataPointsLinesColor->setDisabled(true);
	checkBoxImpedanceOnOff->setDisabled(true);
	checkBoxAdmitanceOnOff->setDisabled(true);
	checkBoxLabelsOnOff->setDisabled(true);
	checkBoxDPOnOff->setDisabled(true);
	checkBoxDVS->setDisabled(true);
	checkBoxSPlot->setDisabled(true);
	checkBoxAutoLabels->setDisabled(true);
	checkBoxMainLabels->setDisabled(true);
	checkBoxLabels->setDisabled(true);
	checkBoxImpedance->setDisabled(true);
	checkBoxConnectDP->setDisabled(true);
	checkBoxAdmitance->setDisabled(true);
	checkBoxCircles->setDisabled(true);
	checkBoxDiagramLabels->setDisabled(true);
	checkBoxTPLabels->setDisabled(true);
	checkBoxDPLabels->setDisabled(true);
	checkBoxSPLabels->setDisabled(true);
	checkBoxExpanding->setDisabled(true);
	generatorRadioButton->setDisabled(true);

	frequencyComboBox->addItem(QStringLiteral(u"Гц"));
	frequencyComboBox->addItem(QStringLiteral(u"КГц"));
	frequencyComboBox->addItem(QStringLiteral(u"МГц"));
	frequencyComboBox->addItem(QStringLiteral(u"ГГц"));
	long double val = 1;
	frequencyComboBox->setCurrentIndex(0);
	if (SystemParameters::defaultFrequency > 1e9)
	{
		val = 1e9;
		frequencyComboBox->setCurrentIndex(3);
	}
	else if (SystemParameters::defaultFrequency > 1e6)
	{
		val = 1e6;
		frequencyComboBox->setCurrentIndex(2);
	}
	else if (SystemParameters::defaultFrequency > 1e3)
	{
		val = 1e3;
		frequencyComboBox->setCurrentIndex(1);
	}
	frequencyLineEdit->setText(QString::number((double)(SystemParameters::defaultFrequency /val)));

	z0ComboBox->addItem(QStringLiteral(u"Ом"));
	z0ComboBox->addItem(QStringLiteral(u"КОм"));
	z0ComboBox->addItem(QStringLiteral(u"МОм"));
	z0ComboBox->addItem(QStringLiteral(u"ГОм"));
	z0ComboBox->setCurrentIndex(0);
	val = 1;
	if (SystemParameters::z0 > 1e9)
	{
		val = 1e9;
		z0ComboBox->setCurrentIndex(3);
	}
	else if (SystemParameters::z0 > 1e6)
	{
		val = 1e6;
		z0ComboBox->setCurrentIndex(2);
	}
	if (SystemParameters::z0 > 1e3)
	{
		val = 1e3;
		z0ComboBox->setCurrentIndex(1);
	}
	z0lineEdit->setText(QString::number((double)(SystemParameters::z0/val)));

	sBoxIndex[S12Box] = 0;
	sBoxIndex[S21Box] = 1;
	sBoxIndex[MAGBox] = 2;
	sBoxIndex[MSGBox] = 3;
	sBoxIndex[KBox] = 4;
	sBoxIndex[MuBox] = 5;
	sBoxIndex[S11Box] = 6;
	sBoxIndex[S22Box] = 7;
	sBoxIndex[GainSPlotBox] = 8;
	sBoxIndex[LossBox] = 9;

	sBoxDVSIndex[ColorImpedanceBox] = 1;
	sBoxDVSIndex[ColorAdmitanceBox] = 2;
	sBoxDVSIndex[DataPointsBox] = 3;
	sBoxDVSIndex[TempBox] = 4;
	sBoxDVSIndex[ElementBox] = 5;
	sBoxDVSIndex[RefZBox] = 7;
	sBoxDVSIndex[RefYBox] = 8;
	sBoxDVSIndex[VSWRSpinBox] = 9;
	sBoxDVSIndex[QCirclesSpinBox] = 10;


	sBoxAmpFrIndex[spinBoxS11] = 0;
	sBoxAmpFrIndex[spinBoxS21] = 1;

	if (SystemParameters::rotate)
	{
		verticalRadioButton->setChecked(true);
	}
	else
	{
		horizontalRadioButton->setChecked(true);
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

	connect(horizontalRadioButton, &QRadioButton::clicked, this, &ColourSetting::VerticalHorizontalChanged);
	connect(verticalRadioButton, &QRadioButton::clicked, this, &ColourSetting::VerticalHorizontalChanged);

	connect(S11Graf, &QPushButton::clicked, this, &ColourSetting::GrafOneColor);
	connect(S22Graf, &QPushButton::clicked, this, &ColourSetting::GrafOneColor);
	connect(GridGrafOneColor, &QPushButton::clicked, this, &ColourSetting::GrafOneColor);

	connect(MAGGraf, &QPushButton::clicked, this, &ColourSetting::GrafTwoColor);
	connect(MSGGraf, &QPushButton::clicked, this, &ColourSetting::GrafTwoColor);
	connect(KGraf, &QPushButton::clicked, this, &ColourSetting::GrafTwoColor);
	connect(MuGraf, &QPushButton::clicked, this, &ColourSetting::GrafTwoColor);
	connect(GridGrafTwoColor, &QPushButton::clicked, this, &ColourSetting::GrafTwoColor);

	connect(CircleS12, &QPushButton::clicked, this, &ColourSetting::CircleS12S21Color);
	connect(CircleS21, &QPushButton::clicked, this, &ColourSetting::CircleS12S21Color);

	connect(AmpFrS11, &QPushButton::clicked, this, &ColourSetting::AmpFrColor);
	connect(AmpFrS21, &QPushButton::clicked, this, &ColourSetting::AmpFrColor);

	connect(ColourAdmitance, &QPushButton::clicked, this, &ColourSetting::DVSColor);
	connect(ColourImpedance, &QPushButton::clicked, this, &ColourSetting::DVSColor);
	connect(DatapointCirclesColor, &QPushButton::clicked, this, &ColourSetting::DVSColor);
	connect(TempLinesColor, &QPushButton::clicked, this, &ColourSetting::DVSColor);
	connect(ElementLinesColor, &QPushButton::clicked, this, &ColourSetting::DVSColor);
	connect(RefYColor, &QPushButton::clicked, this, &ColourSetting::DVSColor);
	connect(RefZColor, &QPushButton::clicked, this, &ColourSetting::DVSColor);
	connect(QCirclesColor, &QPushButton::clicked, this, &ColourSetting::DVSColor);
	connect(VSWRCirclesColor, &QPushButton::clicked, this, &ColourSetting::DVSColor);
	connect(MainCircleColor, &QPushButton::clicked, this, &ColourSetting::DVSColor);

	connect(S12Box, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineCircleS12S21);
	connect(S21Box, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineCircleS12S21);

	connect(MAGBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineGrafTwo);
	connect(MSGBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineGrafTwo);
	connect(KBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineGrafTwo);
	connect(GainSPlotBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineGrafTwo);
	connect(MuBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineGrafTwo);

	connect(S11Box, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineGrafOne);
	connect(S22Box, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineGrafOne);
	connect(LossBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::LineGrafOne);

	connect(ColorImpedanceBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(ColorAdmitanceBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(DataPointsBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(MainCircleBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(RefZBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(RefYBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(TempBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(ElementBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(VSWRSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);
	connect(QCirclesSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::DVSLine);

	connect(spinBoxS21, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::AmpFrLine);
	connect(spinBoxS11, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColourSetting::AmpFrLine);

	connect(DefaultButton, &QPushButton::clicked, this, &ColourSetting::DefaultClicked);

	connect(CancelButton, &QPushButton::clicked, this, &ColourSetting::ButtonCancel);
	connect(OKButton, &QPushButton::clicked, this, &ColourSetting::ButtonOK);
}

void ColourSetting::SetupUI()
{
	this->resize(772, 549);
	this->setWindowTitle("Пользовательские настройки");
	gridLayoutWidget = new QWidget(this);
	gridLayoutWidget->setGeometry(QRect(10, 10, 751, 501));
	gridLayout = new QGridLayout(gridLayoutWidget);
	gridLayout->setSpacing(6);
	gridLayout->setContentsMargins(11, 11, 11, 11);
	gridLayout->setContentsMargins(0, 0, 0, 0);
	tabWidget = new QTabWidget(gridLayoutWidget);
	DVSTab = new QWidget();
	SetupDVS();
	tabWidget->addTab(DVSTab, QStringLiteral(u"ДВС"));
	SPlotTab = new QWidget();
	SetupSPlot();
	tabWidget->addTab(SPlotTab, QStringLiteral(u"S-графики"));
	MainTab = new QWidget();
	SetupMain();
	tabWidget->addTab(MainTab, QStringLiteral(u"Основное"));
	AFRTab = new QWidget();
	SetupAFR();
	tabWidget->addTab(AFRTab, QStringLiteral(u"АЧХ"));
	gridLayout->addWidget(tabWidget, 0, 0, 1, 1);
	DefaultButton = new QPushButton(this);
	DefaultButton->setGeometry(QRect(380, 520, 111, 24));
	DefaultButton->setText(QStringLiteral(u"Сброс в стандарт"));
	OKButton = new QPushButton(this);
	OKButton->setGeometry(QRect(500, 520, 80, 24));
	OKButton->setText("OK");
	CancelButton = new QPushButton(this);
	CancelButton->setGeometry(QRect(590, 520, 80, 24));
	CancelButton->setText(QStringLiteral(u"Отмена"));
	HelpButton = new QPushButton(this);
	HelpButton->setGeometry(QRect(680, 520, 80, 24));
	HelpButton->setText(QStringLiteral(u"Помощь"));
	tabWidget->setCurrentIndex(0);

}

void ColourSetting::SetupDVS()
{
	groupBox = new QGroupBox(DVSTab);
	groupBox->setGeometry(QRect(0, 0, 471, 341));
	groupBox->setTitle(QStringLiteral(u"Цвета и толщины линий"));
	labelImpedance = new QLabel(groupBox);
	labelImpedance->setGeometry(QRect(10, 40, 101, 24));
	labelImpedance->setText(QStringLiteral(u"Сопротивление"));
	ColourImpedance = new QPushButton(groupBox);
	ColourImpedance->setGeometry(QRect(120, 40, 31, 24));
	ColorImpedanceBox = new QSpinBox(groupBox);
	ColorImpedanceBox->setGeometry(QRect(160, 40, 61, 21));
	ColorImpedanceBox->setMinimum(1);
	ColorImpedanceBox->setMaximum(10);
	ColorImpedanceBox->setSingleStep(1);
	ColorImpedanceBox->setStepType(QAbstractSpinBox::DefaultStepType);
	ColorImpedanceBox->setValue(1);
	labelAdmitance = new QLabel(groupBox);
	labelAdmitance->setGeometry(QRect(10, 70, 101, 24));
	labelAdmitance->setText(QStringLiteral(u"Проводимость"));
	ColourAdmitance = new QPushButton(groupBox);
	ColourAdmitance->setGeometry(QRect(120, 70, 31, 24));
	ColorAdmitanceBox = new QSpinBox(groupBox);
	ColorAdmitanceBox->setGeometry(QRect(160, 70, 61, 21));
	ColorAdmitanceBox->setMinimum(1);
	ColorAdmitanceBox->setMaximum(10);
	DatapointCirclesColor = new QPushButton(groupBox);
	DatapointCirclesColor->setGeometry(QRect(120, 100, 31, 24));
	DataPointsBox = new QSpinBox(groupBox);
	DataPointsBox->setGeometry(QRect(160, 100, 61, 21));
	DataPointsBox->setMinimum(1);
	DataPointsBox->setMaximum(10);
	labelDP = new QLabel(groupBox);
	labelDP->setGeometry(QRect(10, 100, 101, 21));
	labelDP->setText(QStringLiteral(u"Своб. точки"));
	labelQ = new QLabel(groupBox);
	labelQ->setGeometry(QRect(10, 130, 101, 21));
	labelQ->setText(QStringLiteral(u"Круги добр."));
	QCirclesColor = new QPushButton(groupBox);
	QCirclesColor->setGeometry(QRect(120, 130, 31, 24));
	QCirclesSpinBox = new QSpinBox(groupBox);
	QCirclesSpinBox->setGeometry(QRect(160, 130, 61, 21));
	QCirclesSpinBox->setMinimum(1);
	QCirclesSpinBox->setMaximum(10);
	labelGain = new QLabel(groupBox);
	labelGain->setGeometry(QRect(10, 190, 101, 21));
	labelGain->setText(QStringLiteral(u"Круги усил."));
	labelStability = new QLabel(groupBox);
	labelStability->setGeometry(QRect(10, 160, 101, 21));
	labelStability->setText(QStringLiteral(u"Круги устойчив."));
	StabilityColor = new QPushButton(groupBox);
	StabilityColor->setGeometry(QRect(120, 160, 31, 24));
	GainBox = new QSpinBox(groupBox);
	GainBox->setGeometry(QRect(160, 190, 61, 21));
	GainBox->setMinimum(1);
	GainBox->setMaximum(10);
	GainColor = new QPushButton(groupBox);
	GainColor->setGeometry(QRect(120, 190, 31, 24));
	StabilityBox = new QSpinBox(groupBox);
	StabilityBox->setGeometry(QRect(160, 160, 61, 21));
	StabilityBox->setMinimum(1);
	StabilityBox->setMaximum(10);
	VSWRSpinBox = new QSpinBox(groupBox);
	VSWRSpinBox->setGeometry(QRect(160, 220, 61, 21));
	VSWRSpinBox->setMinimum(1);
	VSWRSpinBox->setMaximum(10);
	SweepLinesColor = new QPushButton(groupBox);
	SweepLinesColor->setGeometry(QRect(120, 280, 31, 24));
	SweepLinesBox = new QSpinBox(groupBox);
	SweepLinesBox->setGeometry(QRect(160, 280, 61, 21));
	SweepLinesBox->setMinimum(1);
	SweepLinesBox->setMaximum(10);
	labelVSWR = new QLabel(groupBox);
	labelVSWR->setGeometry(QRect(10, 220, 101, 21));
	labelVSWR->setText(QStringLiteral(u"Круги КСВН"));
	VSWRCirclesColor = new QPushButton(groupBox);
	VSWRCirclesColor->setGeometry(QRect(120, 220, 31, 24));
	NoiseBox = new QSpinBox(groupBox);
	NoiseBox->setGeometry(QRect(160, 250, 61, 21));
	NoiseBox->setMinimum(1);
	NoiseBox->setMaximum(10);
	labelGamma = new QLabel(groupBox);
	labelGamma->setGeometry(QRect(10, 310, 101, 21));
	labelGamma->setText(QStringLiteral(u"|Г|=1"));
	NoiseColor = new QPushButton(groupBox);
	NoiseColor->setGeometry(QRect(120, 250, 31, 24));
	MainCircleBox = new QSpinBox(groupBox);
	MainCircleBox->setGeometry(QRect(160, 310, 61, 21));
	MainCircleBox->setMinimum(1);
	MainCircleBox->setMaximum(10);
	labelNoise = new QLabel(groupBox);
	labelNoise->setGeometry(QRect(10, 250, 101, 21));
	labelNoise->setText(QStringLiteral(u"Круги шумов"));
	MainCircleColor = new QPushButton(groupBox);
	MainCircleColor->setGeometry(QRect(120, 310, 31, 24));
	labelUnfoldingLines = new QLabel(groupBox);
	labelUnfoldingLines->setGeometry(QRect(10, 280, 101, 21));
	labelUnfoldingLines->setText(QStringLiteral(u"Линии разверт."));
	labelMainImpedance = new QLabel(groupBox);
	labelMainImpedance->setGeometry(QRect(230, 40, 121, 21));
	labelMainImpedance->setText(QStringLiteral(u"Опорное сопротив."));
	RefZColor = new QPushButton(groupBox);
	RefZColor->setGeometry(QRect(360, 40, 31, 24));
	RefZBox = new QSpinBox(groupBox);
	RefZBox->setGeometry(QRect(400, 40, 61, 21));
	RefZBox->setMinimum(1);
	RefZBox->setMaximum(10);
	RefZBox->setValue(3);
	labelMainAdmitance = new QLabel(groupBox);
	labelMainAdmitance->setGeometry(QRect(230, 70, 121, 21));
	labelMainAdmitance->setText(QStringLiteral(u"Опорная провод."));
	RefYColor = new QPushButton(groupBox);
	RefYColor->setGeometry(QRect(360, 70, 31, 24));
	RefYBox = new QSpinBox(groupBox);
	RefYBox->setGeometry(QRect(400, 70, 61, 21));
	RefYBox->setMinimum(1);
	RefYBox->setMaximum(10);
	RefYBox->setValue(3);
	DataPointsLinesBox = new QSpinBox(groupBox);
	DataPointsLinesBox->setGeometry(QRect(400, 100, 61, 21));
	DataPointsLinesBox->setMinimum(1);
	DataPointsLinesBox->setMaximum(10);
	DataPointsLinesBox->setValue(2);
	DataPointsLinesColor = new QPushButton(groupBox);
	DataPointsLinesColor->setGeometry(QRect(360, 100, 31, 24));
	TempLinesColor = new QPushButton(groupBox);
	TempLinesColor->setGeometry(QRect(360, 130, 31, 24));
	labelDPLines = new QLabel(groupBox);
	labelDPLines->setGeometry(QRect(230, 100, 121, 21));
	labelDPLines->setText(QStringLiteral(u"Линии своб. точек"));
	labelTemp = new QLabel(groupBox);
	labelTemp->setGeometry(QRect(230, 130, 121, 21));
	labelTemp->setText(QStringLiteral(u"Линии маршрутов"));
	TempBox = new QSpinBox(groupBox);
	TempBox->setGeometry(QRect(400, 130, 61, 21));
	TempBox->setMinimum(1);
	TempBox->setMaximum(10);
	TempBox->setValue(2);
	ElementBox = new QSpinBox(groupBox);
	ElementBox->setGeometry(QRect(400, 160, 61, 21));
	ElementBox->setMinimum(1);
	ElementBox->setMaximum(10);
	ElementBox->setValue(2);
	SweepCirclesColor = new QPushButton(groupBox);
	SweepCirclesColor->setGeometry(QRect(360, 280, 31, 24));
	SweepCirclesBox = new QSpinBox(groupBox);
	SweepCirclesBox->setGeometry(QRect(400, 280, 61, 21));
	SweepCirclesBox->setMinimum(1);
	SweepCirclesBox->setMaximum(10);
	labelUnfolding = new QLabel(groupBox);
	labelUnfolding->setGeometry(QRect(230, 280, 121, 21));
	labelUnfolding->setText(QStringLiteral(u"Круги развертки"));
	ElementLinesColor = new QPushButton(groupBox);
	ElementLinesColor->setGeometry(QRect(360, 160, 31, 24));
	labelRoot = new QLabel(groupBox);
	labelRoot->setGeometry(QRect(230, 160, 121, 21));
	labelRoot->setText(QStringLiteral(u"Годографы элементов"));
	groupBox_2 = new QGroupBox(DVSTab);
	groupBox_2->setGeometry(QRect(480, 0, 261, 321));
	groupBox_2->setTitle(QStringLiteral(u"ДВС"));
	checkBoxLabels = new QCheckBox(groupBox_2);
	checkBoxLabels->setGeometry(QRect(20, 20, 181, 22));
	checkBoxLabels->setText(QStringLiteral(u"Показывать осн. подписи"));
	checkBoxImpedance = new QCheckBox(groupBox_2);
	checkBoxImpedance->setGeometry(QRect(20, 50, 141, 22));
	checkBoxImpedance->setText(QStringLiteral(u"Сопротивление"));
	checkBoxConnectDP = new QCheckBox(groupBox_2);
	checkBoxConnectDP->setGeometry(QRect(20, 110, 171, 22));
	checkBoxConnectDP->setText(QStringLiteral(u"Соединение своб. точек"));
	checkBoxAdmitance = new QCheckBox(groupBox_2);
	checkBoxAdmitance->setGeometry(QRect(20, 80, 141, 22));
	checkBoxAdmitance->setText(QStringLiteral(u"Проводимость"));
	checkBoxCircles = new QCheckBox(groupBox_2);
	checkBoxCircles->setGeometry(QRect(20, 230, 141, 22));
	checkBoxCircles->setText(QStringLiteral(u"Подписи кругов"));
	checkBoxDiagramLabels = new QCheckBox(groupBox_2);
	checkBoxDiagramLabels->setGeometry(QRect(20, 140, 141, 22));
	checkBoxDiagramLabels->setText(QStringLiteral(u"Подпись диаграммы"));
	checkBoxTPLabels = new QCheckBox(groupBox_2);
	checkBoxTPLabels->setGeometry(QRect(20, 200, 181, 22));
	checkBoxTPLabels->setText(QStringLiteral(u"Подписи точек элементов"));
	checkBoxDPLabels = new QCheckBox(groupBox_2);
	checkBoxDPLabels->setGeometry(QRect(20, 170, 141, 22));
	checkBoxDPLabels->setText(QStringLiteral(u"Подписи своб. точек"));
	checkBoxSPLabels = new QCheckBox(groupBox_2);
	checkBoxSPLabels->setGeometry(QRect(20, 260, 141, 22));
	checkBoxSPLabels->setText(QStringLiteral(u"Подписи SP"));
	checkBoxExpanding = new QCheckBox(groupBox_2);
	checkBoxExpanding->setGeometry(QRect(20, 290, 141, 22));
	checkBoxExpanding->setText(QStringLiteral(u"Расширение"));
	groupBox_3 = new QGroupBox(DVSTab);
	groupBox_3->setGeometry(QRect(0, 340, 351, 61));
	groupBox_3->setTitle(QStringLiteral(u"Основное"));
	labelZ0 = new QLabel(groupBox_3);
	labelZ0->setGeometry(QRect(10, 30, 151, 16));
	labelZ0->setText(QStringLiteral(u"Опорное сопротивление"));
	z0ComboBox = new QComboBox(groupBox_3);
	z0ComboBox->setGeometry(QRect(280, 30, 61, 24));
	z0lineEdit = new QLineEdit(groupBox_3);
	z0lineEdit->setGeometry(QRect(180, 30, 91, 24));
	groupBox_4 = new QGroupBox(DVSTab);
	groupBox_4->setGeometry(QRect(0, 400, 291, 61));
	groupBox_4->setTitle(QStringLiteral(u"Свободные точки"));
	labelFrequency = new QLabel(groupBox_4);
	labelFrequency->setGeometry(QRect(10, 30, 111, 16));
	labelFrequency->setText(QStringLiteral(u"Стандарт. частота"));
	frequencyComboBox = new QComboBox(groupBox_4);
	frequencyComboBox->setGeometry(QRect(220, 30, 61, 24));
	frequencyLineEdit = new QLineEdit(groupBox_4);
	frequencyLineEdit->setGeometry(QRect(132, 30, 81, 24));
	groupBox_5 = new QGroupBox(DVSTab);
	groupBox_5->setGeometry(QRect(300, 400, 171, 61));
	groupBox_5->setTitle(QStringLiteral(u"Ориент. построения цепи"));
	generatorRadioButton = new QRadioButton(groupBox_5);
	generatorRadioButton->setGeometry(QRect(10, 30, 131, 22));
	generatorRadioButton->setText(QStringLiteral(u"Генератор впереди"));
	groupBox_10 = new QGroupBox(DVSTab);
	groupBox_10->setGeometry(QRect(480, 320, 261, 141));
	groupBox_10->setTitle(QStringLiteral(u"Схема"));
	groupBox_11 = new QGroupBox(groupBox_10);
	groupBox_11->setGeometry(QRect(10, 70, 241, 61));
	groupBox_11->setTitle(QStringLiteral(u"Ориентация схемы"));
	verticalRadioButton = new QRadioButton(groupBox_11);
	verticalRadioButton->setGeometry(QRect(10, 30, 91, 22));
	verticalRadioButton->setText(QStringLiteral(u"Вертик."));
	horizontalRadioButton = new QRadioButton(groupBox_11);
	horizontalRadioButton->setGeometry(QRect(130, 30, 91, 21));
	horizontalRadioButton->setText(QStringLiteral(u"Горизонт."));
	checkBoxAutoLabels = new QCheckBox(groupBox_10);
	checkBoxAutoLabels->setGeometry(QRect(20, 30, 111, 22));
	checkBoxAutoLabels->setText(QStringLiteral(u"Авт. подписи"));
	checkBoxMainLabels = new QCheckBox(groupBox_10);
	checkBoxMainLabels->setGeometry(QRect(140, 30, 111, 22));
	checkBoxMainLabels->setText(QStringLiteral(u"Осн. подписи"));
}

void ColourSetting::SetupSPlot()
{
	groupBox_6 = new QGroupBox(SPlotTab);
	groupBox_6->setGeometry(QRect(10, 10, 361, 341));
	groupBox_6->setTitle(QStringLiteral(u"Цвета и толщины линий"));
	labelS12 = new QLabel(groupBox_6);
	labelS12->setGeometry(QRect(10, 30, 161, 24));
	labelS12->setText(QStringLiteral(u"Сетка для S12 диаграммы"));
	labelS21 = new QLabel(groupBox_6);
	labelS21->setGeometry(QRect(10, 60, 161, 24));
	labelS21->setText(QStringLiteral(u"Сетка для S21 диаграммы"));
	CircleS12 = new QPushButton(groupBox_6);
	CircleS12->setGeometry(QRect(260, 30, 31, 21));
	CircleS21 = new QPushButton(groupBox_6);
	CircleS21->setGeometry(QRect(260, 60, 31, 21));
	labelMAG = new QLabel(groupBox_6);
	labelMAG->setGeometry(QRect(10, 90, 161, 24));
	labelMAG->setText(QStringLiteral(u"Линии MAG"));
	MAGGraf = new QPushButton(groupBox_6);
	MAGGraf->setGeometry(QRect(260, 90, 31, 21));
	labelMSG = new QLabel(groupBox_6);
	labelMSG->setGeometry(QRect(10, 124, 161, 20));
	labelMSG->setText(QStringLiteral(u"Линии MSG"));
	MSGGraf = new QPushButton(groupBox_6);
	MSGGraf->setGeometry(QRect(260, 120, 31, 21));
	labelK = new QLabel(groupBox_6);
	labelK->setGeometry(QRect(10, 153, 161, 21));
	labelK->setText(QStringLiteral(u"Линии K"));
	KGraf = new QPushButton(groupBox_6);
	KGraf->setGeometry(QRect(260, 150, 31, 21));
	labelMu = new QLabel(groupBox_6);
	labelMu->setGeometry(QRect(10, 183, 161, 21));
	labelMu->setText(QStringLiteral(u"Линии μ"));
	MuGraf = new QPushButton(groupBox_6);
	MuGraf->setGeometry(QRect(260, 180, 31, 21));
	labelS11 = new QLabel(groupBox_6);
	labelS11->setGeometry(QRect(10, 214, 161, 20));
	labelS11->setText(QStringLiteral(u"Линии S11"));
	S11Graf = new QPushButton(groupBox_6);
	S11Graf->setGeometry(QRect(260, 210, 31, 21));
	labelS22 = new QLabel(groupBox_6);
	labelS22->setGeometry(QRect(10, 244, 161, 20));
	labelS22->setText(QStringLiteral(u"Линии S22"));
	S22Graf = new QPushButton(groupBox_6);
	S22Graf->setGeometry(QRect(260, 240, 31, 21));
	S12Box = new QSpinBox(groupBox_6);
	S12Box->setGeometry(QRect(300, 30, 51, 21));
	S12Box->setMinimum(1);
	S12Box->setMaximum(10);
	S21Box = new QSpinBox(groupBox_6);
	S21Box->setGeometry(QRect(300, 60, 51, 21));
	S21Box->setMinimum(1);
	S21Box->setMaximum(10);
	MAGBox = new QSpinBox(groupBox_6);
	MAGBox->setGeometry(QRect(300, 90, 51, 21));
	MAGBox->setMinimum(1);
	MAGBox->setMaximum(10);
	MSGBox = new QSpinBox(groupBox_6);
	MSGBox->setGeometry(QRect(300, 120, 51, 21));
	MSGBox->setMinimum(1);
	MSGBox->setMaximum(10);
	KBox = new QSpinBox(groupBox_6);
	KBox->setGeometry(QRect(300, 150, 51, 21));
	KBox->setMinimum(1);
	KBox->setMaximum(10);
	MuBox = new QSpinBox(groupBox_6);
	MuBox->setGeometry(QRect(300, 180, 51, 21));
	MuBox->setMinimum(1);
	MuBox->setMaximum(10);
	S11Box = new QSpinBox(groupBox_6);
	S11Box->setGeometry(QRect(300, 210, 51, 21));
	S11Box->setMinimum(1);
	S11Box->setMaximum(10);
	S22Box = new QSpinBox(groupBox_6);
	S22Box->setGeometry(QRect(300, 240, 51, 21));
	S22Box->setMinimum(1);
	S22Box->setMaximum(10);
	labelGainGrid = new QLabel(groupBox_6);
	labelGainGrid->setGeometry(QRect(10, 270, 181, 21));
	labelGainGrid->setText(QStringLiteral(u"Сетка для графика усиления"));
	GridGrafTwoColor = new QPushButton(groupBox_6);
	GridGrafTwoColor->setGeometry(QRect(260, 270, 31, 21));
	GainSPlotBox = new QSpinBox(groupBox_6);
	GainSPlotBox->setGeometry(QRect(300, 270, 51, 21));
	GainSPlotBox->setMinimum(1);
	GainSPlotBox->setMaximum(10);
	labelLossGrid = new QLabel(groupBox_6);
	labelLossGrid->setGeometry(QRect(10, 296, 161, 20));
	labelLossGrid->setText(QStringLiteral(u"Сетка для графика потерь"));
	GridGrafOneColor = new QPushButton(groupBox_6);
	GridGrafOneColor->setGeometry(QRect(260, 300, 31, 21));
	LossBox = new QSpinBox(groupBox_6);
	LossBox->setGeometry(QRect(300, 300, 51, 21));
	LossBox->setMinimum(1);
	LossBox->setMaximum(10);
	groupBox_7 = new QGroupBox(SPlotTab);
	groupBox_7->setGeometry(QRect(380, 10, 281, 341));
	groupBox_7->setTitle(QStringLiteral(u"Окно S11-S22"));
	checkBoxImpedanceOnOff = new QCheckBox(groupBox_7);
	checkBoxImpedanceOnOff->setGeometry(QRect(10, 30, 191, 22));
	checkBoxImpedanceOnOff->setText(QStringLiteral(u"Сопротивление (вкл/выкл)"));
	checkBoxAdmitanceOnOff = new QCheckBox(groupBox_7);
	checkBoxAdmitanceOnOff->setGeometry(QRect(10, 60, 181, 22));
	checkBoxAdmitanceOnOff->setText(QStringLiteral(u"Проводимость (вкл/выкл)"));
	checkBoxLabelsOnOff = new QCheckBox(groupBox_7);
	checkBoxLabelsOnOff->setGeometry(QRect(10, 90, 231, 22));
	checkBoxLabelsOnOff->setText(QStringLiteral(u"Подписи на диаграмме (вкл/выкл)"));
	checkBoxDPOnOff = new QCheckBox(groupBox_7);
	checkBoxDPOnOff->setGeometry(QRect(10, 120, 231, 22));
	checkBoxDPOnOff->setText(QStringLiteral(u"Круги свободных точек (вкл/выкл)"));

}

void ColourSetting::SetupMain() 
{
	groupBox_9 = new QGroupBox(MainTab);
	groupBox_9->setGeometry(QRect(10, 10, 231, 80));
	groupBox_9->setTitle(QStringLiteral(u"Стандартный режим"));
	checkBoxDVS = new QCheckBox(groupBox_9);
	checkBoxDVS->setGeometry(QRect(10, 40, 101, 22));
	checkBoxDVS->setText(QStringLiteral(u"ДВС"));
	checkBoxSPlot = new QCheckBox(groupBox_9);
	checkBoxSPlot->setGeometry(QRect(130, 40, 91, 22));
	checkBoxSPlot->setText(QStringLiteral(u"S-графики"));
}

void ColourSetting::SetupAFR()
{
	groupBox_8 = new QGroupBox(AFRTab);
	groupBox_8->setGeometry(QRect(10, 10, 201, 321));
	groupBox_8->setTitle(QStringLiteral(u"Цвета и толщины линий"));
	labelAFRS21 = new QLabel(groupBox_8);
	labelAFRS21->setGeometry(QRect(10, 30, 151, 31));
	labelAFRS21->setText(QStringLiteral(u"АЧХ - S21"));
	labelAFRS11 = new QLabel(groupBox_8);
	labelAFRS11->setGeometry(QRect(10, 60, 151, 31));
	labelAFRS11->setText(QStringLiteral(u"АЧХ - S11"));
	AmpFrS11 = new QPushButton(groupBox_8);
	AmpFrS11->setGeometry(QRect(90, 60, 31, 24));
	AmpFrS21 = new QPushButton(groupBox_8);
	AmpFrS21->setGeometry(QRect(90, 30, 31, 24));
	spinBoxS21 = new QSpinBox(groupBox_8);
	spinBoxS21->setGeometry(QRect(130, 30, 61, 27));
	spinBoxS21->setMinimum(1);
	spinBoxS21->setMaximum(10);
	spinBoxS11 = new QSpinBox(groupBox_8);
	spinBoxS11->setGeometry(QRect(130, 60, 61, 27));
	spinBoxS11->setMinimum(1);
	spinBoxS11->setMaximum(10);

}

/// <summary>
/// Изменение выбранной radiobutton.
/// </summary>
void ColourSetting::VerticalHorizontalChanged()
{
	QRadioButton* rButton = qobject_cast<QRadioButton*>(sender());
	if (rButton == horizontalRadioButton)
	{
		SystemParameters::rotate = false;
		emit rev();
	}
	else if (rButton == verticalRadioButton)
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
	QString temp = z0lineEdit->text();
	bool validate = true;
	bool allCorrect = true;
	bool allChanged = false;
	double value = z0lineEdit->text().toFloat(&validate);
	if (!validate || value <= 0)
	{
		allCorrect = false;
	}
	int temp3 = 1;
	if (z0ComboBox->currentIndex() == 1)
	{
		temp3 = 1000;
	}
	else if (z0ComboBox->currentIndex() == 2)
	{
		temp3 = 1000000;
	}
	else if (z0ComboBox->currentIndex() == 3)
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
	QString temp2 = frequencyLineEdit->text();
	bool validate2 = true;
	double value2 = frequencyLineEdit->text().toFloat(&validate2);
	if (!validate2 || value2 <= 0)
	{
		allCorrect = false;
	}
	temp3 = 1;
	if (frequencyComboBox->currentIndex() == 1)
	{
		temp3 = 1000;
	}
	else if (frequencyComboBox->currentIndex() == 2)
	{
		temp3 = 1000000;
	}
	else if (frequencyComboBox->currentIndex() == 3)
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
	setButtonColor(S11Graf, SystemParameters::s11GrafColorDefault);
	setButtonColor(S22Graf, SystemParameters::s22GrafColorDefault);
	setButtonColor(MAGGraf, SystemParameters::magGrafColorDefault);
	setButtonColor(MSGGraf, SystemParameters::msgGrafColorDefault);
	setButtonColor(KGraf, SystemParameters::kGrafColorDefault);
	setButtonColor(MuGraf, SystemParameters::muGrafColorDefault);
	setButtonColor(AmpFrS11, SystemParameters::ampS11ColorDefault);
	setButtonColor(AmpFrS21, SystemParameters::ampS21ColorDefault);
	setButtonColor(CircleS12, SystemParameters::circleS12Default);
	setButtonColor(CircleS21, SystemParameters::circleS21Default);
	setButtonColor(ColourAdmitance, SystemParameters::AdmitanceColorDefault);
	setButtonColor(ColourImpedance, SystemParameters::ImpedanceColorDefault);
	setButtonColor(GridGrafOneColor, SystemParameters::gridGrafOneColorDefault);
	setButtonColor(GridGrafTwoColor, SystemParameters::gridGrafTwoColorDefault);
	setButtonColor(DatapointCirclesColor, SystemParameters::DataPointsColorDefault);
	setButtonColor(TempLinesColor, SystemParameters::RootColorDefault);
	setButtonColor(ElementLinesColor, SystemParameters::ElementsColorDefault);
	setButtonColor(RefZColor, SystemParameters::MainImpedanceColorDefault);
	setButtonColor(RefYColor, SystemParameters::MainAdmitanceColorDefault);
	setButtonColor(QCirclesColor, SystemParameters::QCirclesColorDefault);
	setButtonColor(VSWRCirclesColor, SystemParameters::VSWRColorDefault);
	setButtonColor(MainCircleColor, SystemParameters::MainCircleColorDefault);
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
	SystemParameters::prevz0 = SystemParameters::z0;
	SystemParameters::z0 = 50;
	horizontalRadioButton->setChecked(true);
	z0ComboBox->setCurrentIndex(0);
	frequencyComboBox->setCurrentIndex(2);
	z0lineEdit->setText("50");
	frequencyLineEdit->setText("500");
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
	emit rev();
	emit allchangedsignal();
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