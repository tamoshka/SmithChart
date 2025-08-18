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
	void rImpedanceRealCalculation(float, float);
	void rImpedanceImagCalculation(float, float);
	void rAdmitanceRealCalculation(float, float);
	void rAdmitanceImagCalculation(float, float);

	Complex zCalculation(float, float);
	Complex yCalculation(float, float);

	Complex impedanceRealChartParameters(float, float);
	Complex impedanceImagChartParameters(float, float);
	Complex admitanceRealChartParameters(float, float);
	Complex admitanceImagChartParameters(float, float);

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
