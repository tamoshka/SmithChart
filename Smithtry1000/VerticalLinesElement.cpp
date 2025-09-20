#include "VerticalLinesElement.h"

void VerticalLinesElement::SetElectricalLength(long double electricalLength)
{
	this->_electricalLength = electricalLength;
}

void VerticalLinesElement::SetMechanicalLength(long double mechanicalLength)
{
	this->_mechanicalLength = mechanicalLength;
}

void VerticalLinesElement::SetTheta(long double theta)
{
	this->_theta = theta;
}

void VerticalLinesElement::SetLambda(long double lambda)
{
	this->_lambda = lambda;
}

long double VerticalLinesElement::GetElectricalLength()
{
	return this->_electricalLength;
}

long double VerticalLinesElement::GetMechanicalLength()
{
	return this->_mechanicalLength;
}

long double VerticalLinesElement::GetTheta()
{
	return this->_theta;
}

long double VerticalLinesElement::GetLambda()
{
	return this->_lambda;
}

VerticalLinesElement::VerticalLinesElement(mode mode, long double value, long double frequency, Point point, map<chartMode, tuple<long double, long double>> chartParameters,
	map<parameterMode, Complex> parameters, long double electricalLength, long double mechanicalLength, long double theta, long double lambda) :
	Element(mode, value, frequency, point, chartParameters, parameters)
{
	this->SetElectricalLength(electricalLength);
	this->SetMechanicalLength(mechanicalLength);
	this->SetTheta(theta);
	this->SetLambda(lambda);
}