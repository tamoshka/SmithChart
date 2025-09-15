#include "CirclesWidget.h"
#include "ui_CirclesWidget.h"

CirclesWidget::CirclesWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::CirclesWidget())
{
	ui->setupUi(this);
	this->setFixedSize(600, 600);
	checkBoxVSWRIndex[ui->checkBox10VSWR] = 10;
	checkBoxVSWRIndex[ui->checkBox5VSWR] = 5;
	checkBoxVSWRIndex[ui->checkBox3VSWR] = 3;
	checkBoxVSWRIndex[ui->checkBox2VSWR] = 2;
	checkBoxVSWRIndex[ui->checkBox1point5VSWR] = 1.5;
	checkBoxVSWRIndex[ui->checkBox1point2VSWR] = 1.2;
	reverseCheckBoxVSWRIndex[10] = ui->checkBox10VSWR;
	reverseCheckBoxVSWRIndex[5] = ui->checkBox5VSWR;
	reverseCheckBoxVSWRIndex[3] = ui->checkBox3VSWR;
	reverseCheckBoxVSWRIndex[2] = ui->checkBox2VSWR;
	reverseCheckBoxVSWRIndex[1.5] = ui->checkBox1point5VSWR;
	reverseCheckBoxVSWRIndex[1.2] = ui->checkBox1point2VSWR;
	connect(ui->SelectAllButtonVSWR, &QPushButton::clicked, this, &CirclesWidget::selectAllClickedVSWR);
	connect(ui->ClearAllDefinedButtonVSWR, &QPushButton::clicked, this, &CirclesWidget::clearAllDefinedClickedVSWR);
	connect(ui->checkBox10VSWR, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedVSWR);
	connect(ui->checkBox5VSWR, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedVSWR);
	connect(ui->checkBox3VSWR, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedVSWR);
	connect(ui->checkBox2VSWR, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedVSWR);
	connect(ui->checkBox1point5VSWR, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedVSWR);
	connect(ui->checkBox1point2VSWR, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedVSWR);
	connect(ui->OkButton, &QPushButton::clicked, this, &CirclesWidget::okClicked);
	connect(ui->CancelButton, &QPushButton::clicked, this, &CirclesWidget::cancelClicked);
	connect(ui->InsertButtonVSWR, &QPushButton::clicked, this, &CirclesWidget::insertVSWRClicked);
}

void CirclesWidget::insertVSWRClicked()
{
	QString tempVswr = ui->FieldVSWR->text();
	bool validateVswr = true;
	double valueVswr = ui->FieldVSWR->text().toFloat(&validateVswr);
    if (validateVswr&&valueVswr>=1)
	{
		SystemParameters::VSWRCircles.insert(valueVswr);
		if (valueVswr == 10 || valueVswr == 5 || valueVswr == 3 || valueVswr == 2 || valueVswr == 1.5 || valueVswr == 1.2)
		{
			reverseCheckBoxVSWRIndex[valueVswr]->setChecked(true);
		}
		else
		{
			ui->listWidgetVSWR->addItem(QString::number(valueVswr));
			emit circle();
		}
	}
	ui->FieldVSWR->setText("");
}

void CirclesWidget::okClicked()
{
	this->hide();
}

void CirclesWidget::cancelClicked()
{
	this->hide();
}

CirclesWidget::~CirclesWidget()
{
	delete ui;
}

void CirclesWidget::checkboxCheckedVSWR(int state)
{
	QCheckBox* checkBox = qobject_cast<QCheckBox*>(sender());
	if (state == Qt::Checked)
	{
		SystemParameters::VSWRCircles.insert(checkBoxVSWRIndex[checkBox]);
	}
	if (state == Qt::Unchecked)
	{
		int valueindex = SystemParameters::VSWRCircles.remove(checkBoxVSWRIndex[checkBox]);
	}
	emit circle();
}

void CirclesWidget::selectAllClickedVSWR()
{
	ui->checkBox10VSWR->setChecked(true);
	qreal value10 = 10;
	if (!SystemParameters::VSWRCircles.contains(value10))
	{
		SystemParameters::VSWRCircles.insert(value10);
	}
	ui->checkBox5VSWR->setChecked(true);
	qreal value5 = 5;
	if (!SystemParameters::VSWRCircles.contains(value5))
	{
		SystemParameters::VSWRCircles.insert(value5);
	}
	ui->checkBox3VSWR->setChecked(true);
	qreal value3 = 3;
	if (!SystemParameters::VSWRCircles.contains(value3))
	{
		SystemParameters::VSWRCircles.insert(value3);
	}
	ui->checkBox2VSWR->setChecked(true);
	qreal value2 = 2;
	if (!SystemParameters::VSWRCircles.contains(value2))
	{
		SystemParameters::VSWRCircles.insert(value2);
	}
	ui->checkBox1point5VSWR->setChecked(true);
	qreal value1point5 = 1.5;
	if (!SystemParameters::VSWRCircles.contains(value1point5))
	{
		SystemParameters::VSWRCircles.insert(value1point5);
	}
	ui->checkBox1point2VSWR->setChecked(true);
	qreal value1point2 = 1.2;
	if (!SystemParameters::VSWRCircles.contains(value1point2))
	{
		SystemParameters::VSWRCircles.insert(value1point2);
	}
	emit circle();
}

void CirclesWidget::clearAllDefinedClickedVSWR()
{
	ui->checkBox10VSWR->setChecked(false);
	qreal value10 = 10;
	if (SystemParameters::VSWRCircles.contains(value10))
	{
		SystemParameters::VSWRCircles.remove(value10);
	}
	ui->checkBox5VSWR->setChecked(false);
	qreal value5 = 5;
	if (SystemParameters::VSWRCircles.contains(value5))
	{
		SystemParameters::VSWRCircles.remove(value5);
	}
	ui->checkBox3VSWR->setChecked(false);
	qreal value3 = 3;
	if (SystemParameters::VSWRCircles.contains(value3))
	{
		SystemParameters::VSWRCircles.remove(value3);
	}
	ui->checkBox2VSWR->setChecked(false);
	qreal value2 = 2;
	if (SystemParameters::VSWRCircles.contains(value2))
	{
		SystemParameters::VSWRCircles.remove(value2);
	}
	ui->checkBox1point5VSWR->setChecked(false);
	qreal value1point5 = 1.5;
	if (SystemParameters::VSWRCircles.contains(value1point5))
	{
		SystemParameters::VSWRCircles.remove(value1point5);
	}
	ui->checkBox1point2VSWR->setChecked(false);
	qreal value1point2 = 1.2;
	if (SystemParameters::VSWRCircles.contains(value1point2))
	{
		SystemParameters::VSWRCircles.remove(value1point2);
	}
	emit circle();
}