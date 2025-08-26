#include "VerticalLinesElement.h"

void VerticalLinesElement::SetElectricalLength(double electricalLength)
{
	this->_electricalLength = electricalLength;
}

void VerticalLinesElement::SetMechanicalLength(double mechanicalLength)
{
	this->_mechanicalLength = mechanicalLength;
}

void VerticalLinesElement::SetTheta(double theta)
{
	this->_theta = theta;
}

void VerticalLinesElement::SetLambda(double lambda)
{
	this->_lambda = lambda;
}

double VerticalLinesElement::GetElectricalLength()
{
	return this->_electricalLength;
}

double VerticalLinesElement::GetMechanicalLength()
{
	return this->_mechanicalLength;
}

double VerticalLinesElement::GetTheta()
{
	return this->_theta;
}

double VerticalLinesElement::GetLambda()
{
	return this->_lambda;
}

VerticalLinesElement::VerticalLinesElement(mode mode, double value, double frequency, Point point, map<chartMode, tuple<double, double>> chartParameters,
	map<parameterMode, Complex> parameters, double electricalLength, double mechanicalLength, double theta, double lambda) :
	Element(mode, value, frequency, point, chartParameters, parameters)
{
	this->SetElectricalLength(electricalLength);
	this->SetMechanicalLength(mechanicalLength);
	this->SetTheta(theta);
	this->SetLambda(lambda);
}