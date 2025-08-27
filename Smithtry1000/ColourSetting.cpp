#include "ColourSetting.h"
#include <QColorDialog>
using namespace std;
ColourSetting::ColourSetting(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::ColourSettingClass())
	, s11GrafColor(Qt::blue)
	, s22GrafColor(Qt::red)
	, magGrafColor(Qt::blue)
	, msgGrafColor(Qt::red)
	, kGrafColor(Qt::green)
	, muGrafColor(Qt::black)
	, ampS11Color(Qt::blue)
	, ampS21Color(Qt::red)
	, circleS12(Qt::blue)
	, circleS21(Qt::blue)
	, ImpedanceColor(Qt::blue)
	, AdmitanceColor(Qt::red)
{
	ui->setupUi(this);

	setButtonColor(ui->S11Graf, s11GrafColor);
	setButtonColor(ui->S22Graf, s22GrafColor);
	setButtonColor(ui->MAGGraf, magGrafColor);
	setButtonColor(ui->MSGGraf, msgGrafColor);
	setButtonColor(ui->KGraf, kGrafColor);
	setButtonColor(ui->MuGraf, muGrafColor);
	setButtonColor(ui->AmpFrS11, ampS11Color);
	setButtonColor(ui->AmpFrS21, ampS21Color);
	setButtonColor(ui->CircleS12, circleS12);
	setButtonColor(ui->CircleS21, circleS21);
	setButtonColor(ui->ColourAdmitance, AdmitanceColor);
	setButtonColor(ui->ColourImpedance, ImpedanceColor);

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
	QColor newColor = QColorDialog::getColor(s11GrafColor, this);
	if (newColor.isValid()) 
	{
		s11GrafColor = newColor;
		setButtonColor(ui->S11Graf, s11GrafColor);
		SystemParameters::s11GrafColor = newColor;
		emit s11ColorChanged(s11GrafColor);
	}
}

void ColourSetting::S22Graf()
{
	QColor newColor = QColorDialog::getColor(s22GrafColor, this);
	if (newColor.isValid()) 
	{
		s22GrafColor = newColor;
		setButtonColor(ui->S22Graf, s22GrafColor);
		SystemParameters::s22GrafColor = newColor;
		emit s22ColorChanged(s22GrafColor);
	}
}

void ColourSetting::MAGGraf()
{
	QColor newColor = QColorDialog::getColor(magGrafColor, this);
	if (newColor.isValid()) 
	{
		magGrafColor = newColor;
		setButtonColor(ui->MAGGraf, magGrafColor);
		SystemParameters::magGrafColor = newColor;
		emit magColorChanged(magGrafColor);
	}
}

void ColourSetting::MSGGraf()
{
	QColor newColor = QColorDialog::getColor(msgGrafColor, this);
	if (newColor.isValid()) 
	{
		msgGrafColor = newColor;
		setButtonColor(ui->MSGGraf, msgGrafColor);
		SystemParameters::msgGrafColor = newColor;
		emit msgColorChanged(msgGrafColor);
	}
}

void ColourSetting::KGraf()
{
	QColor newColor = QColorDialog::getColor(kGrafColor, this);
	if (newColor.isValid()) 
	{
		kGrafColor = newColor;
		setButtonColor(ui->KGraf, kGrafColor);
		SystemParameters::kGrafColor = newColor;
		emit kColorChanged(kGrafColor);
	}
}

void ColourSetting::MuGraf()
{
	QColor newColor = QColorDialog::getColor(muGrafColor, this);
	if (newColor.isValid()) 
	{
		muGrafColor = newColor;
		setButtonColor(ui->MuGraf, muGrafColor);
		SystemParameters::muGrafColor = newColor;
		emit muColorChanged(muGrafColor);
	}
}

void ColourSetting::AmpFrS11()
{
	QColor newColor = QColorDialog::getColor(ampS11Color, this);
	if (newColor.isValid()) 
	{
		ampS11Color = newColor;
		setButtonColor(ui->AmpFrS11, ampS11Color);
		SystemParameters::ampS11Color = newColor;
		emit signal();
	}
}

void ColourSetting::AmpFrS21()
{
	QColor newColor = QColorDialog::getColor(ampS21Color, this);
	if (newColor.isValid())
	{
		ampS21Color = newColor;
		setButtonColor(ui->AmpFrS21, ampS21Color);
		SystemParameters::ampS21Color = newColor;
		emit signal();
	}
}

void ColourSetting::CircleS12()
{
	QColor newColor = QColorDialog::getColor(circleS12, this);
	if (newColor.isValid())
	{
		circleS12 = newColor;
		setButtonColor(ui->CircleS12, circleS12);
		SystemParameters::circleS12 = newColor;
		emit signalS12S21();
	}
}

void ColourSetting::CircleS21()
{
	QColor newColor = QColorDialog::getColor(circleS21, this);
	if (newColor.isValid())
	{
		circleS21 = newColor;
		setButtonColor(ui->CircleS21, circleS21);
		SystemParameters::circleS21 = newColor;
		emit signalS12S21();
	}
}

void ColourSetting::ColourImpedance()
{
	QColor newColor = QColorDialog::getColor(ImpedanceColor, this);
	if (newColor.isValid())
	{
		ImpedanceColor = newColor;
		setButtonColor(ui->ColourImpedance, ImpedanceColor);
		SystemParameters::ImpedanceColor = newColor;
		emit signalDVS();
	}
}

void ColourSetting::ColourAdmitance()
{
	QColor newColor = QColorDialog::getColor(AdmitanceColor, this);
	if (newColor.isValid())
	{
		AdmitanceColor = newColor;
		setButtonColor(ui->ColourAdmitance, AdmitanceColor);
		SystemParameters::AdmitanceColor = newColor;
		emit signalDVS();
	}
}