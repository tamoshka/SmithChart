#pragma once
#include "general.h"

/// <summary>
/// Класс элемента.
/// </summary>
class Element
{
private:
	Point point;
	long double frequency;
	map<chartMode, tuple<long double, long double>> chartParameters;
	map<parameterMode, Complex> parameters;
	mode elementMode;
	long double value;
	void SetMode(mode);
	void SetFrequency(long double);
public:
	mode GetMode();
	long double GetValue();
	void SetValue(long double);
	void SetPoint(Point);
	void SetChartParameters(map<chartMode, tuple<long double, long double>>);
	void SetParameter(map<parameterMode, Complex> parameters);
	long double GetFrequency();
	map<chartMode, tuple<long double, long double>> GetChartParameters();
	Point GetPoint();
	map<parameterMode, Complex> GetParameter();
	Element(mode, long double, long double, Point, map<chartMode, tuple<long double, long double>>, map<parameterMode, Complex>);
	virtual ~Element();
	virtual QJsonObject toJson() const;
	virtual ElementType getElementType() const { return ElementType::BaseElement; }
};