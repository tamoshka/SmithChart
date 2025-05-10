#pragma once
#include <QWidget>
#include "circuitElements.h"
#include "ComplexNumber.h"
#include "general.h"

class AmplitudeFrequence : public QWidget
{
	Q_OBJECT

private:
	CircuitElements* circuitElements;
	double z0 = 50;
	complex gamma1; // reflection coefficient
	complex gamma2; // reflection coefficient
	void SetGamma1(complex);
	void SetGamma2(complex);
public:
	void ReflectionCalculation();
	complex GetGamma1();
	complex GetGamma2();
	AmplitudeFrequence(QWidget* parent = nullptr, CircuitElements* = new CircuitElements());
	void MatrixCalculation();
	void SetPoint(double[], double[]);
	~AmplitudeFrequence();
};