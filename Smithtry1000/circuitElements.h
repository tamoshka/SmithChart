#pragma once
#include "Line.h"
#include "systemParameters.h"
class CircuitElements
{
private:
	QList<Element*> circuitElements;
public:
	void AddCircuitElements(Element*);
	QList<Element*> GetCircuitElements();
	void DeleteCircuitElements();
	void Remove(int);
	CircuitElements();
	Complex z = Complex(-9999, -9999);
	Complex y = Complex(-9999, -9999);
	double realFirstPoint = -9999;
	double imagFirstPoint = -9999;
	double frequencyFirstPoint = -9999;
	Point firstPoint;
	map<chartMode, tuple<double, double>> chart;
	~CircuitElements();
};