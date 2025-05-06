#include "circuitElements.h"

CircuitElements::CircuitElements()
{
	this->circuitElements = QList<Element>();
}

CircuitElements::~CircuitElements()
{
}

void CircuitElements::AddCircuitElements(Element element)
{
	this->circuitElements.append(element);
}

void CircuitElements::DeleteCircuitElements()
{
	this->circuitElements.pop_back();
}

QList<Element> CircuitElements::GetCircuitElements()
{
	return this->circuitElements;
}