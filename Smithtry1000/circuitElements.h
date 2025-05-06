#pragma once
#include "element.h"
class CircuitElements
{
private:
	QList<Element*> circuitElements;
public:
	void AddCircuitElements(Element*);
	QList<Element*> GetCircuitElements();
	void DeleteCircuitElements();
	CircuitElements();
	float realFirstPoint = -9999;
	float imagFirstPoint = -9999;
	float frequencyFirstPoint = -9999;
	~CircuitElements();
};