#include "CirclesWidget.h"
#include "systemParameters.h"
/// <summary>
/// Конструктор класса CirclesWidget.
/// </summary>
/// <param name="parent"></param>
CirclesWidget::CirclesWidget(QWidget *parent, CircuitElements* circuit)
	: QWidget(parent)
{
	SetupUI();
	circuitElements = circuit;
	this->setFixedSize(600, 600);
	checkBoxVSWRIndex[checkBox10VSWR] = 10;
	checkBoxVSWRIndex[checkBox5VSWR] = 5;
	checkBoxVSWRIndex[checkBox3VSWR] = 3;
	checkBoxVSWRIndex[checkBox2VSWR] = 2;
	checkBoxVSWRIndex[checkBox1point5VSWR] = 1.5;
	checkBoxVSWRIndex[checkBox1point2VSWR] = 1.2;
	checkBoxQIndex[checkBox10Q] = 10;
	checkBoxQIndex[checkBox5Q] = 5;
	checkBoxQIndex[checkBox2Q] = 2;
	checkBoxQIndex[checkBox1Q] = 1;
	checkBoxQIndex[checkBox0point5Q] = 0.5;
	checkBoxQIndex[checkBox0point2Q] = 0.2;
	reverseCheckBoxVSWRIndex[10] = checkBox10VSWR;
	reverseCheckBoxVSWRIndex[5] = checkBox5VSWR;
	reverseCheckBoxVSWRIndex[3] = checkBox3VSWR;
	reverseCheckBoxVSWRIndex[2] = checkBox2VSWR;
	reverseCheckBoxVSWRIndex[1.5] = checkBox1point5VSWR;
	reverseCheckBoxVSWRIndex[1.2] = checkBox1point2VSWR;
	reverseCheckBoxQIndex[10] = checkBox10Q;
	reverseCheckBoxQIndex[5] = checkBox5Q;
	reverseCheckBoxQIndex[2] = checkBox2Q;
	reverseCheckBoxQIndex[1] = checkBox1Q;
	reverseCheckBoxQIndex[0.5] = checkBox0point5Q;
	reverseCheckBoxQIndex[0.2] = checkBox0point2Q;
	connect(SelectAllButtonVSWR, &QPushButton::clicked, this, &CirclesWidget::selectAllClickedVSWR);
	connect(ClearAllDefinedButtonVSWR, &QPushButton::clicked, this, &CirclesWidget::clearAllDefinedClickedVSWR);
	connect(checkBox10VSWR, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedVSWR);
	connect(checkBox5VSWR, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedVSWR);
	connect(checkBox3VSWR, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedVSWR);
	connect(checkBox2VSWR, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedVSWR);
	connect(checkBox1point5VSWR, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedVSWR);
	connect(checkBox1point2VSWR, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedVSWR);
	connect(SelectAllButtonQ, &QPushButton::clicked, this, &CirclesWidget::selectAllClickedQ);
	connect(ClearAllDefinedButtonQ, &QPushButton::clicked, this, &CirclesWidget::clearAllDefinedClickedQ);
	connect(checkBox10Q, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedQ);
	connect(checkBox5Q, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedQ);
	connect(checkBox2Q, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedQ);
	connect(checkBox1Q, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedQ);
	connect(checkBox0point5Q, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedQ);
	connect(checkBox0point2Q, &QCheckBox::stateChanged, this, &CirclesWidget::checkboxCheckedQ);
	connect(OkButton, &QPushButton::clicked, this, &CirclesWidget::okClicked);
	connect(CancelButton, &QPushButton::clicked, this, &CirclesWidget::cancelClicked);
	connect(InsertButtonVSWR, &QPushButton::clicked, this, &CirclesWidget::insertVSWRClicked);
	connect(DeleteButtonVSWR, &QPushButton::clicked, this, &CirclesWidget::deleteVSWRClicked);
	connect(ClearAllOtherButtonVSWR, &QPushButton::clicked, this, &CirclesWidget::clearAllOthersClickedVSWR);
	connect(InsertButtonQ, &QPushButton::clicked, this, &CirclesWidget::insertQClicked);
	connect(DeleteButtonQ, &QPushButton::clicked, this, &CirclesWidget::deleteQClicked);
	connect(ClearAllOtherButtonQ, &QPushButton::clicked, this, &CirclesWidget::clearAllOthersClickedQ);
}

/// <summary>
/// Настройка пользовательского интерфейса.
/// </summary>
void CirclesWidget::SetupUI()
{
	this->resize(600, 600);
	this->setWindowTitle(QStringLiteral(u"Круги"));
	QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
	this->setSizePolicy(sizePolicy);
	verticalLayout = new QVBoxLayout(this);
	verticalLayout->setSpacing(6);
	verticalLayout->setContentsMargins(11, 11, 11, 11);
	tabWidget = new QTabWidget(this);
	QTab = new QWidget();
	groupBox_4 = new QGroupBox(QTab);
	groupBox_4->setGeometry(QRect(250, 30, 231, 211));
	groupBox_4->setTitle(QStringLiteral(u"Собственные круги"));
	InsertButtonQ = new QPushButton(groupBox_4);
	InsertButtonQ->setGeometry(QRect(140, 60, 81, 25));
	InsertButtonQ->setText(QStringLiteral(u"Добавить"));
	DeleteButtonQ = new QPushButton(groupBox_4);
	DeleteButtonQ->setGeometry(QRect(140, 90, 81, 25));
	DeleteButtonQ->setText(QStringLiteral(u"Удалить"));
	ClearAllOtherButtonQ = new QPushButton(groupBox_4);
	ClearAllOtherButtonQ->setGeometry(QRect(140, 120, 81, 25));
	ClearAllOtherButtonQ->setText(QStringLiteral(u"Удалить все"));
	listWidgetQ = new QListWidget(groupBox_4);
	listWidgetQ->setGeometry(QRect(10, 60, 121, 141));
	FieldQ = new QLineEdit(groupBox_4);
	FieldQ->setGeometry(QRect(10, 30, 121, 24));
	groupBox_5 = new QGroupBox(QTab);
	groupBox_5->setGeometry(QRect(10, 30, 191, 211));
	groupBox_5->setTitle(QStringLiteral(u"Определенные круги"));
	checkBox10Q = new QCheckBox(groupBox_5);
	checkBox10Q->setGeometry(QRect(10, 30, 83, 22));
	checkBox10Q->setText("10");
	checkBox5Q = new QCheckBox(groupBox_5);
	checkBox5Q->setGeometry(QRect(10, 60, 83, 22));
	checkBox5Q->setText("5");
	checkBox2Q = new QCheckBox(groupBox_5);
	checkBox2Q->setGeometry(QRect(10, 90, 83, 22));
	checkBox2Q->setText("2");
	checkBox1Q = new QCheckBox(groupBox_5);
	checkBox1Q->setGeometry(QRect(10, 120, 83, 22));
	checkBox1Q->setText("1");
	checkBox0point5Q = new QCheckBox(groupBox_5);
	checkBox0point5Q->setGeometry(QRect(10, 150, 83, 22));
	checkBox0point5Q->setText("0.5");
	checkBox0point2Q = new QCheckBox(groupBox_5);
	checkBox0point2Q->setGeometry(QRect(10, 180, 83, 22));
	checkBox0point2Q->setText("0.2");
	SelectAllButtonQ = new QPushButton(groupBox_5);
	SelectAllButtonQ->setGeometry(QRect(100, 80, 80, 25));
	SelectAllButtonQ->setText(QStringLiteral(u"Выбрать все"));
	ClearAllDefinedButtonQ = new QPushButton(groupBox_5);
	ClearAllDefinedButtonQ->setGeometry(QRect(100, 110, 80, 25));
	ClearAllDefinedButtonQ->setText(QStringLiteral(u"Очистить все"));
	tabWidget->addTab(QTab, QString("Q"));
	GainTab = new QWidget();
	tabWidget->addTab(GainTab, QStringLiteral(u"Усиление"));
	VSWRTab = new QWidget();
	groupBox_2 = new QGroupBox(VSWRTab);
	groupBox_2->setGeometry(QRect(10, 30, 191, 211));
	groupBox_2->setTitle(QStringLiteral(u"Определенные круги"));
	checkBox10VSWR = new QCheckBox(groupBox_2);
	checkBox10VSWR->setGeometry(QRect(10, 30, 83, 22));
	checkBox10VSWR->setText("10");
	checkBox5VSWR = new QCheckBox(groupBox_2);
	checkBox5VSWR->setGeometry(QRect(10, 60, 83, 22));
	checkBox5VSWR->setText("5");
	checkBox3VSWR = new QCheckBox(groupBox_2);
	checkBox3VSWR->setGeometry(QRect(10, 90, 83, 22));
	checkBox3VSWR->setText("3");
	checkBox2VSWR = new QCheckBox(groupBox_2);
	checkBox2VSWR->setGeometry(QRect(10, 120, 83, 22));
	checkBox2VSWR->setText("2");
	checkBox1point5VSWR = new QCheckBox(groupBox_2);
	checkBox1point5VSWR->setGeometry(QRect(10, 150, 83, 22));
	checkBox1point5VSWR->setText("1.5");
	checkBox1point2VSWR = new QCheckBox(groupBox_2);
	checkBox1point2VSWR->setGeometry(QRect(10, 180, 83, 22));
	checkBox1point2VSWR->setText("1.2");
	SelectAllButtonVSWR = new QPushButton(groupBox_2);
	SelectAllButtonVSWR->setGeometry(QRect(100, 80, 80, 25));
	SelectAllButtonVSWR->setText(QStringLiteral(u"Выбрать все"));
	ClearAllDefinedButtonVSWR = new QPushButton(groupBox_2);
	ClearAllDefinedButtonVSWR->setGeometry(QRect(100, 110, 80, 25));
	ClearAllDefinedButtonVSWR->setText(QStringLiteral(u"Очистить все"));
	groupBox_3 = new QGroupBox(VSWRTab);
	groupBox_3->setGeometry(QRect(250, 30, 231, 211));
	groupBox_3->setTitle(QStringLiteral(u"Собственные круги"));
	InsertButtonVSWR = new QPushButton(groupBox_3);
	InsertButtonVSWR->setGeometry(QRect(140, 60, 81, 25));
	InsertButtonVSWR->setText(QStringLiteral(u"Добавить"));
	DeleteButtonVSWR = new QPushButton(groupBox_3);
	DeleteButtonVSWR->setGeometry(QRect(140, 90, 81, 25));
	DeleteButtonVSWR->setText(QStringLiteral(u"Удалить"));
	ClearAllOtherButtonVSWR = new QPushButton(groupBox_3);
	ClearAllOtherButtonVSWR->setGeometry(QRect(140, 120, 81, 25));
	ClearAllOtherButtonVSWR->setText(QStringLiteral(u"Удалить все"));
	listWidgetVSWR = new QListWidget(groupBox_3);
	listWidgetVSWR->setGeometry(QRect(10, 60, 121, 141));
	FieldVSWR = new QLineEdit(groupBox_3);
	FieldVSWR->setGeometry(QRect(10, 30, 121, 24));
	tabWidget->addTab(VSWRTab, QStringLiteral(u"КСВН"));
	StabilityTab = new QWidget();
	tabWidget->addTab(StabilityTab, QStringLiteral(u"Устойчивость"));
	NoiseTab = new QWidget();
	tabWidget->addTab(NoiseTab, QStringLiteral(u"Шумы"));
	verticalLayout->addWidget(tabWidget);
	groupBox = new QGroupBox(this);
	horizontalLayout = new QHBoxLayout(groupBox);
	horizontalLayout->setSpacing(6);
	horizontalLayout->setContentsMargins(11, 11, 11, 11);
	OkButton = new QPushButton(groupBox);
	OkButton->setText("OK");
	horizontalLayout->addWidget(OkButton);
	CancelButton = new QPushButton(groupBox);
	CancelButton->setText(QStringLiteral(u"Отмена"));
	horizontalLayout->addWidget(CancelButton);
	verticalLayout->addWidget(groupBox);
	tabWidget->setCurrentIndex(0);
}

/// <summary>
/// Загрузка кругов при загрузке файла проекта.
/// </summary>
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

/// <summary>
/// Очистка от старых кругов при загрузке проекта.
/// </summary>
void CirclesWidget::clearOnLoad()
{
	for (auto item : listWidgetQ->findItems("*", Qt::MatchWildcard))
	{
		double valueQ = item->text().toDouble();
		listWidgetQ->takeItem(listWidgetQ->row(item));
	}

	for (auto item : listWidgetVSWR->findItems("*", Qt::MatchWildcard))
	{
		double valueVswr = item->text().toDouble();
		listWidgetVSWR->takeItem(listWidgetVSWR->row(item));
	}

	checkBox10Q->setChecked(false);
	checkBox5Q->setChecked(false);
	checkBox2Q->setChecked(false);
	checkBox1Q->setChecked(false);
	checkBox0point5Q->setChecked(false);
	checkBox0point2Q->setChecked(false);

	checkBox10VSWR->setChecked(false);
	checkBox5VSWR->setChecked(false);
	checkBox3VSWR->setChecked(false);
	checkBox2VSWR->setChecked(false);
	checkBox1point5VSWR->setChecked(false);
	checkBox1point2VSWR->setChecked(false);
}

/// <summary>
/// Очистка всех кругов VSWR, введённых вручную.
/// </summary>
void CirclesWidget::clearAllOthersClickedVSWR()
{
	for (auto item : listWidgetVSWR->findItems("*", Qt::MatchWildcard))
	{
		double valueVswr = item->text().toDouble();
		circuitElements->VSWRCircles.remove(valueVswr);
		listWidgetVSWR->takeItem(listWidgetVSWR->row(item));
	}
	emit circle();
}

/// <summary>
/// Очистка всех кругов Q, введённых вручную.
/// </summary>
void CirclesWidget::clearAllOthersClickedQ()
{
	for (auto item : listWidgetQ->findItems("*", Qt::MatchWildcard))
	{
		double valueQ = item->text().toDouble();
		circuitElements->QCircles.remove(valueQ);
		listWidgetQ->takeItem(listWidgetQ->row(item));
	}
	emit circle();
}

/// <summary>
/// Удаление выбранного VSWR круга.
/// </summary>
void CirclesWidget::deleteVSWRClicked()
{
	for (auto item : listWidgetVSWR->selectedItems())
	{
		double valueVswr = item->text().toDouble();
		circuitElements->VSWRCircles.remove(valueVswr);
		listWidgetVSWR->takeItem(listWidgetVSWR->row(item));
	}
	emit circle();
}

/// <summary>
/// Удаление выбранного Q круга.
/// </summary>
void CirclesWidget::deleteQClicked()
{
	for (auto item : listWidgetQ->selectedItems())
	{
		double valueQ = item->text().toDouble();
		circuitElements->QCircles.remove(valueQ);
		listWidgetQ->takeItem(listWidgetQ->row(item));
	}
	emit circle();
}

/// <summary>
/// Вставка нового VSWR круга.
/// </summary>
void CirclesWidget::insertVSWRClicked()
{
	QString tempVswr = FieldVSWR->text();
	bool validateVswr = true;
	double valueVswr = FieldVSWR->text().toFloat(&validateVswr);
    if (validateVswr&&valueVswr>=1&&!circuitElements->VSWRCircles.contains(valueVswr))
	{
		circuitElements->VSWRCircles.insert(valueVswr);
		if (valueVswr == 10 || valueVswr == 5 || valueVswr == 3 || valueVswr == 2 || valueVswr == 1.5 || valueVswr == 1.2)
		{
			reverseCheckBoxVSWRIndex[valueVswr]->setChecked(true);
		}
		else
		{
			listWidgetVSWR->addItem(QString::number(valueVswr));
			emit circle();
		}
	}
	FieldVSWR->setText("");
}

/// <summary>
/// Добавление круга VSWR.
/// </summary>
/// <param name="val">Значение.</param>
void CirclesWidget::addVSWR(double val)
{
	circuitElements->VSWRCircles.insert(val);
	if (val == 10.0f || val == 5.0f || val == 3.0f || val == 2.0f || val == 1.5f || val == 1.2f)
	{
		reverseCheckBoxVSWRIndex[val]->setChecked(true);
	}
	else
	{
		listWidgetVSWR->addItem(QString::number(val));
	}
}

/// <summary>
/// Добавление круга Q.
/// </summary>
/// <param name="val">Значение.</param>
void CirclesWidget::addQ(double val)
{
	circuitElements->QCircles.insert(val);
	if (val == 10.0f || val == 5.0f || val == 2.0f || val == 1.0f || val == 0.5f || val == 0.2f)
	{
		reverseCheckBoxQIndex[val]->setChecked(true);
	}
	else
	{
		listWidgetQ->addItem(QString::number(val));
	}
}

/// <summary>
/// Вставка нового Q круга.
/// </summary>
void CirclesWidget::insertQClicked()
{
	QString tempQ = FieldQ->text();
	bool validateQ = true;
	double valueQ = FieldQ->text().toFloat(&validateQ);
	if (validateQ && valueQ > 0 && !circuitElements->QCircles.contains(valueQ))
	{
		circuitElements->QCircles.insert(valueQ);
		if (valueQ == 10 || valueQ == 5 || valueQ == 2 || valueQ == 1 || valueQ == 0.5 || valueQ == 0.2)
		{
			reverseCheckBoxQIndex[valueQ]->setChecked(true);
		}
		else
		{
			listWidgetQ->addItem(QString::number(valueQ));
			emit circle();
		}
	}
	FieldQ->setText("");
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
	checkBox10VSWR->setChecked(true);
	qreal value10 = 10;
	if (!circuitElements->VSWRCircles.contains(value10))
	{
		circuitElements->VSWRCircles.insert(value10);
	}
	checkBox5VSWR->setChecked(true);
	qreal value5 = 5;
	if (!circuitElements->VSWRCircles.contains(value5))
	{
		circuitElements->VSWRCircles.insert(value5);
	}
	checkBox3VSWR->setChecked(true);
	qreal value3 = 3;
	if (!circuitElements->VSWRCircles.contains(value3))
	{
		circuitElements->VSWRCircles.insert(value3);
	}
	checkBox2VSWR->setChecked(true);
	qreal value2 = 2;
	if (!circuitElements->VSWRCircles.contains(value2))
	{
		circuitElements->VSWRCircles.insert(value2);
	}
	checkBox1point5VSWR->setChecked(true);
	qreal value1point5 = 1.5;
	if (!circuitElements->VSWRCircles.contains(value1point5))
	{
		circuitElements->VSWRCircles.insert(value1point5);
	}
	checkBox1point2VSWR->setChecked(true);
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
	checkBox10Q->setChecked(true);
	qreal value10 = 10;
	if (!circuitElements->QCircles.contains(value10))
	{
		circuitElements->QCircles.insert(value10);
	}
	checkBox5Q->setChecked(true);
	qreal value5 = 5;
	if (!circuitElements->QCircles.contains(value5))
	{
		circuitElements->QCircles.insert(value5);
	}
	checkBox2Q->setChecked(true);
	qreal value2 = 2;
	if (!circuitElements->QCircles.contains(value2))
	{
		circuitElements->QCircles.insert(value2);
	}
	checkBox1Q->setChecked(true);
	qreal value1 = 1;
	if (!circuitElements->QCircles.contains(value1))
	{
		circuitElements->QCircles.insert(value1);
	}
	checkBox0point5Q->setChecked(true);
	qreal value0point5 = 0.5;
	if (!circuitElements->QCircles.contains(value0point5))
	{
		circuitElements->QCircles.insert(value0point5);
	}
	checkBox0point2Q->setChecked(true);
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
	checkBox10VSWR->setChecked(false);
	qreal value10 = 10;
	if (circuitElements->VSWRCircles.contains(value10))
	{
		circuitElements->VSWRCircles.remove(value10);
	}
	checkBox5VSWR->setChecked(false);
	qreal value5 = 5;
	if (circuitElements->VSWRCircles.contains(value5))
	{
		circuitElements->VSWRCircles.remove(value5);
	}
	checkBox3VSWR->setChecked(false);
	qreal value3 = 3;
	if (circuitElements->VSWRCircles.contains(value3))
	{
		circuitElements->VSWRCircles.remove(value3);
	}
	checkBox2VSWR->setChecked(false);
	qreal value2 = 2;
	if (circuitElements->VSWRCircles.contains(value2))
	{
		circuitElements->VSWRCircles.remove(value2);
	}
	checkBox1point5VSWR->setChecked(false);
	qreal value1point5 = 1.5;
	if (circuitElements->VSWRCircles.contains(value1point5))
	{
		circuitElements->VSWRCircles.remove(value1point5);
	}
	checkBox1point2VSWR->setChecked(false);
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
	checkBox10Q->setChecked(false);
	qreal value10 = 10;
	if (circuitElements->QCircles.contains(value10))
	{
		circuitElements->QCircles.remove(value10);
	}
	checkBox5Q->setChecked(false);
	qreal value5 = 5;
	if (circuitElements->QCircles.contains(value5))
	{
		circuitElements->QCircles.remove(value5);
	}
	checkBox2Q->setChecked(false);
	qreal value2 = 2;
	if (circuitElements->QCircles.contains(value2))
	{
		circuitElements->QCircles.remove(value2);
	}
	checkBox1Q->setChecked(false);
	qreal value1 = 1;
	if (circuitElements->QCircles.contains(value1))
	{
		circuitElements->QCircles.remove(value1);
	}
	checkBox0point5Q->setChecked(false);
	qreal value0point5 = 0.5;
	if (circuitElements->QCircles.contains(value0point5))
	{
		circuitElements->QCircles.remove(value0point5);
	}
	checkBox0point2Q->setChecked(false);
	qreal value0point2 = 0.2;
	if (circuitElements->QCircles.contains(value0point2))
	{
		circuitElements->QCircles.remove(value0point2);
	}
	emit circle();
}