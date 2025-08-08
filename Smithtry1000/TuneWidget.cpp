#include "TuneWidget.h"
#include "ui_TuneWidget.h"

TuneWidget::TuneWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::TuneWidget())
{
	ui->setupUi(this);
	tuned = new CircuitElements();
	connect(ui->OKButton, &QPushButton::clicked, this, &TuneWidget::OKButton_clicked);
}

TuneWidget::~TuneWidget()
{
	delete ui;
}

void TuneWidget::OKButton_clicked()
{
	SystemParameters::tune = false;
}

void TuneWidget::GetSignal(Element* elem, QString path)
{
	tuned->AddCircuitElements(elem);
	QSvgWidget* svgWidget = new QSvgWidget(this);
	svgWidget->load(QString(path));
	widgets.append(svgWidget);
	update();
}

void TuneWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setPen(QPen(Qt::red, 2));
	int i = 0;
	for (auto& var : widgets)
	{
		var->setGeometry((i+1) * 40+i*5, 40, 40, 40);
		var->show();
		i++;
	}
}
