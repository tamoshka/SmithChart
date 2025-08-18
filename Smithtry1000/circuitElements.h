#pragma once
#include "element.h"
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
	float realFirstPoint = -9999;
	float imagFirstPoint = -9999;
	float frequencyFirstPoint = -9999;
	Point firstPoint;
	map<chartMode, tuple<float, float>> chart;
	~CircuitElements();
};