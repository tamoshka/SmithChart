#pragma once
#include "VerticalLinesElement.h"

/// <summary>
/// Класс хранения линий передач.
/// </summary>
class LinesElement :public VerticalLinesElement
{
private:
	long double _alpha;

public:
	void SetAlpha(long double);
	long double GetAlpha();
	LinesElement(mode mode, long double value, long double frequency, Point point, map<chartMode, tuple<long double, long double>> chartParameters,
		map<parameterMode, Complex> parameters, long double electricalLength, long double mechanicalLength, long double theta, long double lambda, long double alpha);
	LinesElement(const LinesElement& other)
		: VerticalLinesElement(other),  // Вызываем конструктор копирования родительского класса
		_alpha(other._alpha)
	{
	}
	virtual ElementType getElementType() const override { return ElementType::Lines; }
	virtual QJsonObject toJson() const override;
	virtual QJsonObject toCircuitJson(int&, int&, bool&, bool&, bool&) override;
	static LinesElement* createFromJson(const QJsonObject& json);
};