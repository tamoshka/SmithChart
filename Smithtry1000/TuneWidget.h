#pragma once

#include <QWidget>
#include <QLabel>
#include <qsvgwidget.h>
#include "circuitElements.h"
QT_BEGIN_NAMESPACE
namespace Ui { class TuneWidget; };
QT_END_NAMESPACE

class TuneWidget : public QWidget
{
	Q_OBJECT

public:
	TuneWidget(QWidget *parent = nullptr, CircuitElements* circuitElements = new CircuitElements());
	~TuneWidget();

private:
	Ui::TuneWidget *ui;
	CircuitElements* tuned;
	CircuitElements* circuitElements;
	QWidget* mainWidget = new QWidget(this);
	QList<QGroupBox*> boxes;
	QList<QGroupBox*> slidersBoxes;
	QList<QSvgWidget*> widgets;
	QList<QPushButton*> buttons;
	QList<QSlider*> sliders;
	QList<QLabel*> valueLabels;
	QList<QLabel*> maxLabels;
	QList<QLabel*> minLabels;
	QList<double> maxValue;
	QList<double> minValue;
	int count;
	void rImpedanceRealCalculation(double, double);
	void rImpedanceImagCalculation(double, double);
	void rAdmitanceRealCalculation(double, double);
	void rAdmitanceImagCalculation(double, double);

	Complex zCalculation(double, double);
	Complex yCalculation(double, double);

	Complex impedanceRealChartParameters(double, double);
	Complex impedanceImagChartParameters(double, double);
	Complex admitanceRealChartParameters(double, double);
	Complex admitanceImagChartParameters(double, double);

private slots:
	void OKButton_clicked();
	void MinMaxButton_clicked();
	void ValueChanged(int value);
	void Remove();
	void RemoveAll();

public slots:
	void GetSignal(Element* elem, QString path);
signals:
	void remove(Element*);
	void removeAll();
protected:
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
	void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;
};
