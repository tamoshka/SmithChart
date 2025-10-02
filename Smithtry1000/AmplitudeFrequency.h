#pragma once

#include <QWidget>
#include "circuitElements.h"
#include "general.h"
#include "qcustomplot.h"
#include "ColourSetting.h"
#include "ui_AmplitudeFrequency.h"
QT_BEGIN_NAMESPACE
namespace Ui { class AmplitudeFrequency; };
QT_END_NAMESPACE

class AmplitudeFrequency : public QWidget
{
	Q_OBJECT

private:
	CircuitElements* circuitElements;
	Complex z0 = 50;
	Complex gamma1; // reflection coefficient
	Complex gamma2; // reflection coefficient
	void SetGamma1(Complex);
	void SetGamma2(Complex);
	QVector<long double> freqs;
public slots:
	void SaveAmpFr();
public:
	void ReflectionCalculation();
	Complex GetGamma1();
	Complex GetGamma2();
	AmplitudeFrequency(QWidget* parent = nullptr, CircuitElements* = new CircuitElements());
	void MatrixCalculation();
	void SetPoint(long double[], long double[], long double[]);
	~AmplitudeFrequency();
	Ui::AmplitudeFrequency *ui;
};
