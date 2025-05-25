#pragma once

#include <QWidget>
#include "circuitElements.h"
#include "ComplexNumber.h"
#include "general.h"
#include "qcustomplot.h"
QT_BEGIN_NAMESPACE
namespace Ui { class AmplitudeFrequency; };
QT_END_NAMESPACE

class AmplitudeFrequency : public QWidget
{
	Q_OBJECT

private:
	CircuitElements* circuitElements;
	double z0 = 50;
	complexNumber gamma1; // reflection coefficient
	complexNumber gamma2; // reflection coefficient
	void SetGamma1(complexNumber);
	void SetGamma2(complexNumber);
public:
	void ReflectionCalculation();
	complexNumber GetGamma1();
	complexNumber GetGamma2();
	AmplitudeFrequency(QWidget* parent = nullptr, CircuitElements* = new CircuitElements());
	void MatrixCalculation();
	void SetPoint(double[], double[]);
	~AmplitudeFrequency();
	Ui::AmplitudeFrequency *ui;
};
