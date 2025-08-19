#include "LinesElement.h"

void LinesElement::SetLength(double length)
{
	this->_length = length;
}

void LinesElement::SetTheta(double theta)
{
	this->_theta = theta;
}

double LinesElement::GetLength()
{
	return this->_length;
}

double LinesElement::GetTheta()
{
	return this->_theta;
}

LinesElement::LinesElement(mode mode, double value, double frequency, Point point, map<chartMode, tuple<double, double>> chartParameters, map<parameterMode, Complex> parameters, double length, double theta) :
	Element(mode, value, frequency, point, chartParameters, parameters)
{
	this->SetLength(length);
	this->SetTheta(theta);
}