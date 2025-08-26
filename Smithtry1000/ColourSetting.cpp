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
{
	ui->setupUi(this);

	setButtonColor(ui->S11Graf, s11GrafColor);
	setButtonColor(ui->S22Graf, s22GrafColor);
	setButtonColor(ui->MAGGraf, magGrafColor);
	setButtonColor(ui->MSGGraf, msgGrafColor);
	setButtonColor(ui->KGraf, kGrafColor);
	setButtonColor(ui->MuGraf, muGrafColor);

	connect(ui->S11Graf, &QPushButton::clicked, this, &ColourSetting::S11Graf);
	connect(ui->S22Graf, &QPushButton::clicked, this, &ColourSetting::S22Graf);
	connect(ui->MAGGraf, &QPushButton::clicked, this, &ColourSetting::MAGGraf);
	connect(ui->MSGGraf, &QPushButton::clicked, this, &ColourSetting::MSGGraf);
	connect(ui->KGraf, &QPushButton::clicked, this, &ColourSetting::KGraf);
	connect(ui->MuGraf, &QPushButton::clicked, this, &ColourSetting::MuGraf);
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
	if (newColor.isValid()) {
		s11GrafColor = newColor;
		setButtonColor(ui->S11Graf, s11GrafColor);
		emit s11ColorChanged(s11GrafColor);
	}
}

void ColourSetting::S22Graf()
{
	QColor newColor = QColorDialog::getColor(s22GrafColor, this);
	if (newColor.isValid()) {
		s22GrafColor = newColor;
		setButtonColor(ui->S22Graf, s22GrafColor);
		emit s22ColorChanged(s22GrafColor);
	}
}

void ColourSetting::MAGGraf()
{
	QColor newColor = QColorDialog::getColor(magGrafColor, this);
	if (newColor.isValid()) {
		magGrafColor = newColor;
		setButtonColor(ui->MAGGraf, magGrafColor);
		emit magColorChanged(magGrafColor);
	}
}

void ColourSetting::MSGGraf()
{
	QColor newColor = QColorDialog::getColor(msgGrafColor, this);
	if (newColor.isValid()) {
		msgGrafColor = newColor;
		setButtonColor(ui->MSGGraf, msgGrafColor);
		emit msgColorChanged(msgGrafColor);
	}
}

void ColourSetting::KGraf()
{
	QColor newColor = QColorDialog::getColor(kGrafColor, this);
	if (newColor.isValid()) {
		kGrafColor = newColor;
		setButtonColor(ui->KGraf, kGrafColor);
		emit kColorChanged(kGrafColor);
	}
}

void ColourSetting::MuGraf()
{
	QColor newColor = QColorDialog::getColor(muGrafColor, this);
	if (newColor.isValid()) {
		muGrafColor = newColor;
		setButtonColor(ui->MuGraf, muGrafColor);
		emit muColorChanged(muGrafColor);
	}
}
