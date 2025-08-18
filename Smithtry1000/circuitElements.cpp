#include "circuitElements.h"

CircuitElements::CircuitElements()
{
	this->circuitElements = QList<Element*>();
}

CircuitElements::~CircuitElements()
{
}

void CircuitElements::AddCircuitElements(Element* element)
{
	this->circuitElements.append(element);
}

void CircuitElements::DeleteCircuitElements()
{
	delete this->circuitElements.last();
	this->circuitElements.pop_back();
}

QList<Element*> CircuitElements::GetCircuitElements()
{
	return this->circuitElements;
}

void CircuitElements::Remove(int i)
{
	this->circuitElements.takeAt(i);
}