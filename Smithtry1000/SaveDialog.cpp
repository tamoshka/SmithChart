#include "SaveDialog.h"
#include "systemParameters.h"
#include "ui_SaveDialog.h"

/// <summary>
/// Конструктор класса SaveDialog.
/// </summary>
/// <param name="parent"></param>
SaveDialog::SaveDialog(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::SaveDialog())
{
	ui->setupUi(this);
	this->setFixedSize(250, 150);
	ui->DiagramRadioButton->setChecked(true);
	connect(ui->SaveButton, &QPushButton::clicked, this, &SaveDialog::Save);
	connect(ui->CancelButton, &QPushButton::clicked, this, &SaveDialog::Cancel);
}

/// <summary>
/// Деструктор класса SaveDialog.
/// </summary>
SaveDialog::~SaveDialog()
{
	delete ui;
}

/// <summary>
/// Выбор сохраняемого объекта и принятие.
/// </summary>
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

/// <summary>
/// Отмена.
/// </summary>
void SaveDialog::Cancel()
{
	reject();
}