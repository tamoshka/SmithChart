#include "ColourSetting.h"
#include <QColorDialog>
using namespace std;
ColourSetting::ColourSetting(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::ColourSettingClass())

{
	ui->setupUi(this);

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
}

ColourSetting::~ColourSetting()
{
	delete ui;
}

void ColourSetting::setButtonColor(QPushButton* button, const QColor& color)
{
	QString style = QString("QPushButton {background-color: %1; color: white;}").arg(color.name());
	button->setStyleSheet(style);
}

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

void ColourSetting::ButtonCancel()
{
	this->close();
}

void ColourSetting::ButtonOK()
{
	this->close();
}


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
