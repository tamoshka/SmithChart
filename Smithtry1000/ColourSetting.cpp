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