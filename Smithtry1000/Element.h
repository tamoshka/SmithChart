#pragma once
#include "general.h"

class Element
{
private:
	Point point;
	float frequency;
	map<chartMode, tuple<float, float>> chartParameters;
	mode elementMode;
	float value;
	void SetMode(mode);
	void SetValue(float);
	void SetFrequency(float);
	void SetPoint(Point);
	void SetChartParameters(map<chartMode, tuple<float, float>>);
public:
	mode GetMode();
	float GetValue();
	float GetFrequency();
	map<chartMode, tuple<float, float>> GetChartParameters();
	Point GetPoint();
	Element(mode, float, float, Point, map<chartMode, tuple<float, float>>);
	~Element();
};