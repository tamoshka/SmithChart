#pragma once
#include "Element.h"

class VerticalLinesElement :public Element
{
private:
	long double _electricalLength;
	long double _mechanicalLength;
	long double _lambda;
	long double _theta;

public:
	void SetElectricalLength(long double);
	void SetMechanicalLength(long double);
	void SetTheta(long double);
	void SetLambda(long double);
	long double GetElectricalLength();
	long double GetMechanicalLength();
	long double GetTheta();
	long double GetLambda();
	VerticalLinesElement(mode mode, long double value, long double frequency, Point point, map<chartMode, tuple<long double, long double>> chartParameters,
		map<parameterMode, Complex> parameters, long double electricalLength, long double mechanicalLength, long double theta, long double lambda);
	VerticalLinesElement(const VerticalLinesElement& other)
		: Element(other),  // Важно: вызываем конструктор копирования базового класса
		_electricalLength(other._electricalLength),
		_mechanicalLength(other._mechanicalLength),
		_lambda(other._lambda),
		_theta(other._theta)
	{
	}
	virtual ElementType getElementType() const override { return ElementType::VerticalLines; }
	virtual QJsonObject toJson() const override;
	virtual QJsonObject toCircuitJson(int&, int&, bool&, bool&, bool&) override;
};