#include "Element.h"

Element::Element(mode mode, float value, float frequency, Point point, map<chartMode, tuple<float, float>> chartParameters, map<parameterMode, complex> parameter)
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

void Element::SetValue(float value)
{
	this->value = value;
}

void Element::SetFrequency(float value)
{
	this->frequency = value;
}

void Element::SetPoint(Point point)
{
	this->point = point;
}

void Element::SetChartParameters(map<chartMode, complex> chartParameters)
{
	this->chartParameters = chartParameters;
}

void Element::SetParameter(map<parameterMode, complex> parameter)
{
	this->parameters = parameter;
}

mode Element::GetMode()
{
	return this->elementMode;
}

float Element::GetValue()
{
	return this->value;
}

float Element::GetFrequency()
{
	return this->frequency;
}

map<chartMode, complex> Element::GetChartParameters()
{
	return this->chartParameters;
}

Point Element::GetPoint()
{
	return this->point;
}

map<parameterMode, complex> Element::GetParameter()
{
	return this->parameters;
}


Element::~Element()
{
}