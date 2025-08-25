#include "Element.h"

Element::Element(mode mode, double value, double frequency, Point point, map<chartMode, tuple<double, double>> chartParameters, map<parameterMode, Complex> parameter)
{
	this->SetMode(mode);
	this->SetValue(value);
	this->SetFrequency(frequency);
	this->SetPoint(point);
	this->SetChartParameters(chartParameters);
	this->SetParameter(parameter);
}

void Element::SetMode(mode mode)
{
	this->elementMode = mode;
}

void Element::SetValue(double value)
{
	this->value = value;
}

void Element::SetFrequency(double value)
{
	this->frequency = value;
}

void Element::SetPoint(Point point)
{
	this->point = point;
}

void Element::SetChartParameters(map<chartMode, tuple<double, double>> chartParameters)
{
	this->chartParameters = chartParameters;
}

void Element::SetParameter(map<parameterMode, Complex> parameter)
{
	this->parameters = parameter;
}

mode Element::GetMode()
{
	return this->elementMode;
}

double Element::GetValue()
{
	return this->value;
}

double Element::GetFrequency()
{
	return this->frequency;
}

map<chartMode, tuple<double, double>> Element::GetChartParameters()
{
	return this->chartParameters;
}

Point Element::GetPoint()
{
	return this->point;
}

map<parameterMode, Complex> Element::GetParameter()
{
	return this->parameters;
}


Element::~Element()
{
}