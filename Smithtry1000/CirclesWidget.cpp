#include "CirclesWidget.h"
#include "ui_CirclesWidget.h"

/// <summary>
/// Конструктор класса CirclesWidget.
/// </summary>
/// <param name="parent"></param>
CirclesWidget::CirclesWidget(QWidget *parent, CircuitElements* circuit)
	: QWidget(parent)
	, ui(new Ui::CirclesWidget())
{
	circuitElements = circuit;
	ui->setupUi(this);
	this->setFixedSize(600, 600);
	checkBoxVSWRIndex[ui->checkBox10VSWR] = 10;
	checkBoxVSWRIndex[ui->checkBox5VSWR] = 5;
	checkBoxVSWRIndex[ui->checkBox3VSWR] = 3;
	checkBoxVSWRIndex[ui->checkBox2VSWR] = 2;
	checkBoxVSWRIndex[ui->checkBox1point5VSWR] = 1.5;
	checkBoxVSWRIndex[ui->checkBox1point2VSWR] = 1.2;
	checkBoxQIndex[ui->checkBox10Q] = 10;
	checkBoxQIndex[ui->checkBox5Q] = 5;
	checkBoxQIndex[ui->checkBox2Q] = 2;
	checkBoxQIndex[ui->checkBox1Q] = 1;
	checkBoxQIndex[ui->checkBox0point5Q] = 0.5;
	checkBoxQIndex[ui->checkBox0point2Q] = 0.2;
	reverseCheckBoxVSWRIndex[10] = ui->checkBox10VSWR;
	reverseCheckBoxVSWRIndex[5] = ui->checkBox5VSWR;
	reverseCheckBoxVSWRIndex[3] = ui->checkBox3VSWR;
	reverseCheckBoxVSWRIndex[2] = ui->checkBox2VSWR;
	reverseCheckBoxVSWRIndex[1.5] = ui->checkBox1point5VSWR;
	reverseCheckBoxVSWRIndex[1.2] = ui->checkBox1point2VSWR;
	reverseCheckBoxQIndex[10] = ui->checkBox10Q;
	reverseCheckBoxQIndex[5] = ui->checkBox5Q;
	reverseCheckBoxQIndex[2] = ui->checkBox2Q;
	reverseCheckBoxQIndex[1] = ui->checkBox1Q;
	reverseCheckBoxQIndex[0.5] = ui->checkBox0point5Q;
	reverseCheckBoxQIndex[0.2] = ui->checkBox0point2Q;
	connect(ui->SelectAllButtonVSWR, &QPushButton::clicked, this, &CirclesWidget::selectAllClickedVSWR);
	connect(ui->ClearAllDefinedButtonVSWR, &QPushButton::clicked, this, &CirclesWidget::clearAllDefinedClickedVSWR);
	connect(ui->checkBox10VSWR, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedVSWR);
	connect(ui->checkBox5VSWR, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedVSWR);
	connect(ui->checkBox3VSWR, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedVSWR);
	connect(ui->checkBox2VSWR, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedVSWR);
	connect(ui->checkBox1point5VSWR, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedVSWR);
	connect(ui->checkBox1point2VSWR, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedVSWR);
	connect(ui->SelectAllButtonQ, &QPushButton::clicked, this, &CirclesWidget::selectAllClickedQ);
	connect(ui->ClearAllDefinedButtonQ, &QPushButton::clicked, this, &CirclesWidget::clearAllDefinedClickedQ);
	connect(ui->checkBox10Q, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedQ);
	connect(ui->checkBox5Q, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedQ);
	connect(ui->checkBox2Q, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedQ);
	connect(ui->checkBox1Q, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedQ);
	connect(ui->checkBox0point5Q, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedQ);
	connect(ui->checkBox0point2Q, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedQ);
	connect(ui->OkButton, &QPushButton::clicked, this, &CirclesWidget::okClicked);
	connect(ui->CancelButton, &QPushButton::clicked, this, &CirclesWidget::cancelClicked);
	connect(ui->InsertButtonVSWR, &QPushButton::clicked, this, &CirclesWidget::insertVSWRClicked);
	connect(ui->DeleteButtonVSWR, &QPushButton::clicked, this, &CirclesWidget::deleteVSWRClicked);
	connect(ui->ClearAllOtherButtonVSWR, &QPushButton::clicked, this, &CirclesWidget::clearAllOthersClickedVSWR);
	connect(ui->InsertButtonQ, &QPushButton::clicked, this, &CirclesWidget::insertQClicked);
	connect(ui->DeleteButtonQ, &QPushButton::clicked, this, &CirclesWidget::deleteQClicked);
	connect(ui->ClearAllOtherButtonQ, &QPushButton::clicked, this, &CirclesWidget::clearAllOthersClickedQ);
}

void CirclesWidget::Load()
{
	clearOnLoad();
	for (const double& value : circuitElements->VSWRCircles)
	{
		addVSWR(value);
	}
	for (const double& value : circuitElements->QCircles)
	{
		addQ(value);
	}
}

void CirclesWidget::clearOnLoad()
{
	for (auto item : ui->listWidgetQ->findItems("*", Qt::MatchWildcard))
	{
		double valueQ = item->text().toDouble();
		ui->listWidgetQ->takeItem(ui->listWidgetQ->row(item));
	}

	for (auto item : ui->listWidgetVSWR->findItems("*", Qt::MatchWildcard))
	{
		double valueVswr = item->text().toDouble();
		ui->listWidgetVSWR->takeItem(ui->listWidgetVSWR->row(item));
	}

	ui->checkBox10Q->setChecked(false);
	ui->checkBox5Q->setChecked(false);
	ui->checkBox2Q->setChecked(false);
	ui->checkBox1Q->setChecked(false);
	ui->checkBox0point5Q->setChecked(false);
	ui->checkBox0point2Q->setChecked(false);

	ui->checkBox10VSWR->setChecked(false);
	ui->checkBox5VSWR->setChecked(false);
	ui->checkBox3VSWR->setChecked(false);
	ui->checkBox2VSWR->setChecked(false);
	ui->checkBox1point5VSWR->setChecked(false);
	ui->checkBox1point2VSWR->setChecked(false);
}

/// <summary>
/// Очистка всех кругов VSWR, введённых вручную.
/// </summary>
void CirclesWidget::clearAllOthersClickedVSWR()
{
	for (auto item : ui->listWidgetVSWR->findItems("*", Qt::MatchWildcard))
	{
		double valueVswr = item->text().toDouble();
		circuitElements->VSWRCircles.remove(valueVswr);
		ui->listWidgetVSWR->takeItem(ui->listWidgetVSWR->row(item));
	}
	emit circle();
}

/// <summary>
/// Очистка всех кругов Q, введённых вручную.
/// </summary>
void CirclesWidget::clearAllOthersClickedQ()
{
	for (auto item : ui->listWidgetQ->findItems("*", Qt::MatchWildcard))
	{
		double valueQ = item->text().toDouble();
		circuitElements->QCircles.remove(valueQ);
		ui->listWidgetQ->takeItem(ui->listWidgetQ->row(item));
	}
	emit circle();
}

/// <summary>
/// Удаление выбранного VSWR круга.
/// </summary>
void CirclesWidget::deleteVSWRClicked()
{
	for (auto item : ui->listWidgetVSWR->selectedItems())
	{
		double valueVswr = item->text().toDouble();
		circuitElements->VSWRCircles.remove(valueVswr);
		ui->listWidgetVSWR->takeItem(ui->listWidgetVSWR->row(item));
	}
	emit circle();
}

/// <summary>
/// Удаление выбранного Q круга.
/// </summary>
void CirclesWidget::deleteQClicked()
{
	for (auto item : ui->listWidgetQ->selectedItems())
	{
		double valueQ = item->text().toDouble();
		circuitElements->QCircles.remove(valueQ);
		ui->listWidgetQ->takeItem(ui->listWidgetQ->row(item));
	}
	emit circle();
}

/// <summary>
/// Вставка нового VSWR круга.
/// </summary>
void CirclesWidget::insertVSWRClicked()
{
	QString tempVswr = ui->FieldVSWR->text();
	bool validateVswr = true;
	double valueVswr = ui->FieldVSWR->text().toFloat(&validateVswr);
    if (validateVswr&&valueVswr>=1&&!circuitElements->VSWRCircles.contains(valueVswr))
	{
		circuitElements->VSWRCircles.insert(valueVswr);
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

void CirclesWidget::addVSWR(double val)
{
	circuitElements->VSWRCircles.insert(val);
	if (val == 10.0f || val == 5.0f || val == 3.0f || val == 2.0f || val == 1.5f || val == 1.2f)
	{
		reverseCheckBoxVSWRIndex[val]->setChecked(true);
	}
	else
	{
		ui->listWidgetVSWR->addItem(QString::number(val));
	}
}

void CirclesWidget::addQ(double val)
{
	circuitElements->QCircles.insert(val);
	if (val == 10.0f || val == 5.0f || val == 2.0f || val == 1.0f || val == 0.5f || val == 0.2f)
	{
		reverseCheckBoxQIndex[val]->setChecked(true);
	}
	else
	{
		ui->listWidgetQ->addItem(QString::number(val));
	}
}

/// <summary>
/// Вставка нового Q круга.
/// </summary>
void CirclesWidget::insertQClicked()
{
	QString tempQ = ui->FieldQ->text();
	bool validateQ = true;
	double valueQ = ui->FieldQ->text().toFloat(&validateQ);
	if (validateQ && valueQ > 0 && !circuitElements->QCircles.contains(valueQ))
	{
		circuitElements->QCircles.insert(valueQ);
		if (valueQ == 10 || valueQ == 5 || valueQ == 2 || valueQ == 1 || valueQ == 0.5 || valueQ == 0.2)
		{
			reverseCheckBoxQIndex[valueQ]->setChecked(true);
		}
		else
		{
			ui->listWidgetQ->addItem(QString::number(valueQ));
			emit circle();
		}
	}
	ui->FieldQ->setText("");
}

/// <summary>
/// Обработка принятия изменений.
/// </summary>
void CirclesWidget::okClicked()
{
	this->hide();
}

/// <summary>
/// Обработка отмены изменений.
/// </summary>
void CirclesWidget::cancelClicked()
{
	this->hide();
}

/// <summary>
/// Деструктор класса CirclesWidget.
/// </summary>
CirclesWidget::~CirclesWidget()
{
	delete ui;
}

/// <summary>
/// Выбирание/убирание VSWR круга.
/// </summary>
/// <param name="state">Состояние чекбокса.</param>
void CirclesWidget::checkboxCheckedVSWR(int state)
{
	QCheckBox* checkBox = qobject_cast<QCheckBox*>(sender());
	if (state == Qt::Checked)
	{
		circuitElements->VSWRCircles.insert(checkBoxVSWRIndex[checkBox]);
	}
	if (state == Qt::Unchecked)
	{
		int valueindex = circuitElements->VSWRCircles.remove(checkBoxVSWRIndex[checkBox]);
	}
	emit circle();
}

/// <summary>
/// Выбирание/убирание VSWR круга.
/// </summary>
/// <param name="state">Состояние чекбокса.</param>
void CirclesWidget::checkboxCheckedQ(int state)
{
	QCheckBox* checkBox = qobject_cast<QCheckBox*>(sender());
	if (state == Qt::Checked)
	{
		circuitElements->QCircles.insert(checkBoxQIndex[checkBox]);
	}
	if (state == Qt::Unchecked)
	{
		int valueindex = circuitElements->QCircles.remove(checkBoxQIndex[checkBox]);
	}
	emit circle();
}

/// <summary>
/// Выбор всех стандартных кругов VSWR.
/// </summary>
void CirclesWidget::selectAllClickedVSWR()
{
	ui->checkBox10VSWR->setChecked(true);
	qreal value10 = 10;
	if (!circuitElements->VSWRCircles.contains(value10))
	{
		circuitElements->VSWRCircles.insert(value10);
	}
	ui->checkBox5VSWR->setChecked(true);
	qreal value5 = 5;
	if (!circuitElements->VSWRCircles.contains(value5))
	{
		circuitElements->VSWRCircles.insert(value5);
	}
	ui->checkBox3VSWR->setChecked(true);
	qreal value3 = 3;
	if (!circuitElements->VSWRCircles.contains(value3))
	{
		circuitElements->VSWRCircles.insert(value3);
	}
	ui->checkBox2VSWR->setChecked(true);
	qreal value2 = 2;
	if (!circuitElements->VSWRCircles.contains(value2))
	{
		circuitElements->VSWRCircles.insert(value2);
	}
	ui->checkBox1point5VSWR->setChecked(true);
	qreal value1point5 = 1.5;
	if (!circuitElements->VSWRCircles.contains(value1point5))
	{
		circuitElements->VSWRCircles.insert(value1point5);
	}
	ui->checkBox1point2VSWR->setChecked(true);
	qreal value1point2 = 1.2;
	if (!circuitElements->VSWRCircles.contains(value1point2))
	{
		circuitElements->VSWRCircles.insert(value1point2);
	}
	emit circle();
}

/// <summary>
/// Выбор всех стандартных кругов Q.
/// </summary>
void CirclesWidget::selectAllClickedQ()
{
	ui->checkBox10Q->setChecked(true);
	qreal value10 = 10;
	if (!circuitElements->QCircles.contains(value10))
	{
		circuitElements->QCircles.insert(value10);
	}
	ui->checkBox5Q->setChecked(true);
	qreal value5 = 5;
	if (!circuitElements->QCircles.contains(value5))
	{
		circuitElements->QCircles.insert(value5);
	}
	ui->checkBox2Q->setChecked(true);
	qreal value2 = 2;
	if (!circuitElements->QCircles.contains(value2))
	{
		circuitElements->QCircles.insert(value2);
	}
	ui->checkBox1Q->setChecked(true);
	qreal value1 = 1;
	if (!circuitElements->QCircles.contains(value1))
	{
		circuitElements->QCircles.insert(value1);
	}
	ui->checkBox0point5Q->setChecked(true);
	qreal value0point5 = 0.5;
	if (!circuitElements->QCircles.contains(value0point5))
	{
		circuitElements->QCircles.insert(value0point5);
	}
	ui->checkBox0point2Q->setChecked(true);
	qreal value0point2 = 0.2;
	if (!circuitElements->QCircles.contains(value0point2))
	{
		circuitElements->QCircles.insert(value0point2);
	}
	emit circle();
}

/// <summary>
/// Очистка всех стандартных кругов VSWR.
/// </summary>
void CirclesWidget::clearAllDefinedClickedVSWR()
{
	ui->checkBox10VSWR->setChecked(false);
	qreal value10 = 10;
	if (circuitElements->VSWRCircles.contains(value10))
	{
		circuitElements->VSWRCircles.remove(value10);
	}
	ui->checkBox5VSWR->setChecked(false);
	qreal value5 = 5;
	if (circuitElements->VSWRCircles.contains(value5))
	{
		circuitElements->VSWRCircles.remove(value5);
	}
	ui->checkBox3VSWR->setChecked(false);
	qreal value3 = 3;
	if (circuitElements->VSWRCircles.contains(value3))
	{
		circuitElements->VSWRCircles.remove(value3);
	}
	ui->checkBox2VSWR->setChecked(false);
	qreal value2 = 2;
	if (circuitElements->VSWRCircles.contains(value2))
	{
		circuitElements->VSWRCircles.remove(value2);
	}
	ui->checkBox1point5VSWR->setChecked(false);
	qreal value1point5 = 1.5;
	if (circuitElements->VSWRCircles.contains(value1point5))
	{
		circuitElements->VSWRCircles.remove(value1point5);
	}
	ui->checkBox1point2VSWR->setChecked(false);
	qreal value1point2 = 1.2;
	if (circuitElements->VSWRCircles.contains(value1point2))
	{
		circuitElements->VSWRCircles.remove(value1point2);
	}
	emit circle();
}

/// <summary>
/// Очистка всех стандартных кругов Q.
/// </summary>
void CirclesWidget::clearAllDefinedClickedQ()
{
	ui->checkBox10Q->setChecked(false);
	qreal value10 = 10;
	if (circuitElements->QCircles.contains(value10))
	{
		circuitElements->QCircles.remove(value10);
	}
	ui->checkBox5Q->setChecked(false);
	qreal value5 = 5;
	if (circuitElements->QCircles.contains(value5))
	{
		circuitElements->QCircles.remove(value5);
	}
	ui->checkBox2Q->setChecked(false);
	qreal value2 = 2;
	if (circuitElements->QCircles.contains(value2))
	{
		circuitElements->QCircles.remove(value2);
	}
	ui->checkBox1Q->setChecked(false);
	qreal value1 = 1;
	if (circuitElements->QCircles.contains(value1))
	{
		circuitElements->QCircles.remove(value1);
	}
	ui->checkBox0point5Q->setChecked(false);
	qreal value0point5 = 0.5;
	if (circuitElements->QCircles.contains(value0point5))
	{
		circuitElements->QCircles.remove(value0point5);
	}
	ui->checkBox0point2Q->setChecked(false);
	qreal value0point2 = 0.2;
	if (circuitElements->QCircles.contains(value0point2))
	{
		circuitElements->QCircles.remove(value0point2);
	}
	emit circle();
}