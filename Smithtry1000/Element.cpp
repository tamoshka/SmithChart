#include "Element.h"

Element::Element(mode mode, float value, float frequency, Point point, map<chartMode, tuple<float, float>> chartParameters)
{
	this->SetMode(mode);
	this->SetValue(value);
	this->SetFrequency(frequency);
	this->SetPoint(point);
	this->SetChartParameters(chartParameters);
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

void Element::SetChartParameters(map<chartMode, tuple<float, float>> chartParameters)
{
	this->chartParameters = chartParameters;
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

map<chartMode, tuple<float, float>> Element::GetChartParameters()
{
	return this->chartParameters;
}

Point Element::GetPoint()
{
	return this->point;
}

Element::~Element()
{
}