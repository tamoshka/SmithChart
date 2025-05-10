#pragma once
#include "general.h"
#include "ComplexNumber.h"
class Element
{
private:
	Point point;
	float frequency;
	map<chartMode, tuple<float, float>> chartParameters;
	map<parameterMode, complex> parameters;
	mode elementMode;
	float value;
	void SetMode(mode);
	void SetValue(float);
	void SetFrequency(float);
	void SetPoint(Point);
	void SetChartParameters(map<chartMode, tuple<float, float>>);
	void SetParameter(map<parameterMode, complex> parameters);
public:
	mode GetMode();
	float GetValue();
	float GetFrequency();
	map<chartMode, complex> GetChartParameters();
	Point GetPoint();
	map<parameterMode, complex> GetParameter();
	Element(mode, float, float, Point, map<chartMode, tuple<float, float>>, map<parameterMode, complex>);
	~Element();
};