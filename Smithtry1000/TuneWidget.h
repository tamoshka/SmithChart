#pragma once

#include <QWidget>
#include <QLabel>
#include <QSvgWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QSlider>
#include "circuitElements.h"
QT_BEGIN_NAMESPACE
#ifndef __EAXML__
namespace Ui { class TuneWidget; };
#endif
QT_END_NAMESPACE

/// <summary>
/// Класс, позволяющий проводить настройку элементов в цепи.
/// </summary>
class TuneWidget : public QWidget
{
	Q_OBJECT

public:
	TuneWidget(QWidget *parent = nullptr, CircuitElements* circuitElements = new CircuitElements());
	~TuneWidget();
	void RemoveOnLoad();
	CircuitElements* circuitElements;

private:
	Ui::TuneWidget *ui;
	CircuitElements* tuned;
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
	void SwitchMode(Complex, Complex, int);

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
