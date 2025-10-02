#include "SaveDialog.h"
#include "systemParameters.h"
#include "ui_SaveDialog.h"

SaveDialog::SaveDialog(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::SaveDialog())
{
	ui->setupUi(this);
	this->setFixedSize(250, 150);
	connect(ui->SaveButton, &QPushButton::clicked, this, &SaveDialog::Save);
	connect(ui->CancelButton, &QPushButton::clicked, this, &SaveDialog::Cancel);
}

SaveDialog::~SaveDialog()
{
	delete ui;
}

void SaveDialog::Save()
{
	if (ui->DiagramRadioButton->isChecked())
	{
		SystemParameters::saved = 0;
	}
	else
	{
		SystemParameters::saved = 1;
	}
	accept();
}

void SaveDialog::Cancel()
{
	reject();
}