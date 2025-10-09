#include "Line.h"

/// <summary>
/// Сеттер альфы.
/// </summary>
/// <param name="alpha">Альфа.</param>
void LinesElement::SetAlpha(long double alpha)
{
	this->_alpha = alpha;
}

/// <summary>
/// Геттер альфы.
/// </summary>
/// <returns>Альфа.</returns>
long double LinesElement::GetAlpha()
{
	return this->_alpha;
}

/// <summary>
/// Конструктор класса LinesElement.
/// </summary>
/// <param name="mode">Тип элемента.</param>
/// <param name="value">Значение.</param>
/// <param name="frequency">Частота.</param>
/// <param name="point">Точка.</param>
/// <param name="chartParameters">Параметры диаграммы.</param>
/// <param name="parameters">Параметры(Z, Y, G).</param>
/// <param name="electricalLength">Электрическая длина.</param>
/// <param name="mechanicalLength">Физическая длина.</param>
/// <param name="theta">Тета.</param>
/// <param name="lambda">Лямбда.</param>
/// <param name="alpha">Альфа.</param>
LinesElement::LinesElement(mode mode, long double value, long double frequency, Point point, map<chartMode, tuple<long double, long double>> chartParameters,
	map<parameterMode, Complex> parameters, long double electricalLength, long double mechanicalLength, long double theta, long double lambda, long double alpha) :
	VerticalLinesElement(mode, value, frequency, point, chartParameters, parameters, electricalLength, mechanicalLength, theta, lambda)
{
	this->SetAlpha(alpha);
}

 /// <summary>
 /// Сериализация линии передач.
 /// </summary>
 /// <returns>JsonObject.</returns>
 QJsonObject LinesElement::toJson() const 
{
    // Получаем JSON от родителя (VerticalLinesElement)
    QJsonObject json = VerticalLinesElement::toJson();

    // Добавляем специфичное для LinesElement поле
    json["alpha"] = (double)_alpha;

    return json;
}