#pragma once
#include "general.h"

class Element
{
private:
	//Point point;
	//float frequency;
	//map<chartMode, tuple<float, float>> chartParameters;
	mode elementMode;
	float value;
	void SetMode(mode);
	void SetValue(float);
public:
	mode GetMode();
	float GetValue();
	Element(mode, float);
	~Element();
};