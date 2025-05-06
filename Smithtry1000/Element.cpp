#include "Element.h"

Element::Element(mode mode, float value)
{
	this->SetMode(mode);
	this->SetValue(value);
}

void Element::SetMode(mode mode)
{
	this->elementMode = mode;
}

void Element::SetValue(float value)
{
	this->value = value;
}

mode Element::GetMode()
{
	return this->elementMode;
}

float Element::GetValue()
{
	return this->value;
}

Element::~Element()
{
}