#pragma once
#include "general.h"
#include "ComplexNumber.h"

class Element
{
private:
	Point point;
	float frequency;
	map<chartMode, complex> chartParameters;
	mode elementMode;
	float value;
	void SetMode(mode);
	void SetValue(float);
	void SetFrequency(float);
	void SetPoint(Point);
	void SetChartParameters(map<chartMode, complex>);
public:
	mode GetMode();
	float GetValue();
	float GetFrequency();
	map<chartMode, complex> GetChartParameters();
	Point GetPoint();
	Element(mode, float, float, Point, map<chartMode, complex>);
	~Element();
};