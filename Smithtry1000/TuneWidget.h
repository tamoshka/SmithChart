#pragma once

#include <QWidget>
#include <qsvgwidget.h>
#include "circuitElements.h"
QT_BEGIN_NAMESPACE
namespace Ui { class TuneWidget; };
QT_END_NAMESPACE

class TuneWidget : public QWidget
{
	Q_OBJECT

public:
	TuneWidget(QWidget *parent = nullptr);
	~TuneWidget();

private:
	Ui::TuneWidget *ui;
	CircuitElements* tuned;
	QList<QSvgWidget*> widgets;
private slots:
	void OKButton_clicked();

public slots:
	void GetSignal(Element* elem, QString path);
protected:
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
};
