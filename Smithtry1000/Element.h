#pragma once
#include "general.h"
class Element
{
private:
	Point point;
	double frequency;
	map<chartMode, tuple<double, double>> chartParameters;
	map<parameterMode, Complex> parameters;
	mode elementMode;
	double value;
	void SetMode(mode);
	void SetFrequency(double);
public:
	mode GetMode();
	double GetValue();
	void SetValue(double);
	void SetPoint(Point);
	void SetChartParameters(map<chartMode, tuple<double, double>>);
	void SetParameter(map<parameterMode, Complex> parameters);
	double GetFrequency();
	map<chartMode, tuple<double, double>> GetChartParameters();
	Point GetPoint();
	map<parameterMode, Complex> GetParameter();
	Element(mode, double, double, Point, map<chartMode, tuple<double, double>>, map<parameterMode, Complex>);
	virtual ~Element();
};