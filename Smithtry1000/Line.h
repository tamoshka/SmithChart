#pragma once
#include "VerticalLinesElement.h"

class LinesElement :public VerticalLinesElement
{
private:
	long double _alpha;

public:
	void SetAlpha(long double);
	long double GetAlpha();
	LinesElement(mode mode, long double value, long double frequency, Point point, map<chartMode, tuple<long double, long double>> chartParameters,
		map<parameterMode, Complex> parameters, long double electricalLength, long double mechanicalLength, long double theta, long double lambda, long double alpha);
	virtual ElementType getElementType() const override { return ElementType::Lines; }
	virtual QJsonObject toJson() const override;
	static LinesElement* createFromJson(const QJsonObject& json);
};