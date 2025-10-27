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
	Element()
	{

	};
	Element(mode, long double, long double, Point, map<chartMode, tuple<long double, long double>>, map<parameterMode, Complex>);
	Element& operator=(const Element& other) {
		if (this != &other) {
			point = other.point;
			frequency = other.frequency;
			chartParameters = other.chartParameters;
			parameters = other.parameters;
			elementMode = other.elementMode;
			value = other.value;
		}
		return *this;
	} 
	Element(const Element& other)
		: point(other.point),
		frequency(other.frequency),
		chartParameters(other.chartParameters),
		parameters(other.parameters),
		elementMode(other.elementMode),
		value(other.value)
	{
		// Все поля копируются автоматически, так как они имеют правильные конструкторы копирования
	}
	virtual ~Element();
	virtual QJsonObject toJson() const;
	virtual ElementType getElementType() const { return ElementType::BaseElement; }
};