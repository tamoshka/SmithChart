#pragma once
#include <QWidget>
#include "circuitElements.h"

class AmplitudeFrequence : public QWidget
{
	Q_OBJECT

private:
	CircuitElements* circuitElements;
	float z0 = 50;
	float gamma1; // reflection coefficient
	float gamma2; // reflection coefficient
	void SetGamma1(float);
	void SetGamma2(float);
public:
	void ReflectionCalculation();
	float GetGamma1();
	float GetGamma2();
	AmplitudeFrequence(QWidget* parent = nullptr, CircuitElements* = new CircuitElements());
	~AmplitudeFrequence();
};