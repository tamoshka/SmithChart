#include "Element.h"

Element::Element(mode mode, long double value, long double frequency, Point point, map<chartMode, tuple<long double, long double>> chartParameters, map<parameterMode, Complex> parameter)
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

void Element::SetValue(long double value)
{
	this->value = value;
}

void Element::SetFrequency(long double value)
{
	this->frequency = value;
}

void Element::SetPoint(Point point)
{
	this->point = point;
}

void Element::SetChartParameters(map<chartMode, tuple<long double, long double>> chartParameters)
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

long double Element::GetValue()
{
	return this->value;
}

long double Element::GetFrequency()
{
	return this->frequency;
}

map<chartMode, tuple<long double, long double>> Element::GetChartParameters()
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