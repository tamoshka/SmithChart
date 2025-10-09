#include "Element.h"

/// <summary>
/// Конструктор класса Element.
/// </summary>
/// <param name="mode">Тип элемента.</param>
/// <param name="value">Значение.</param>
/// <param name="frequency">Частота.</param>
/// <param name="point">Точка.</param>
/// <param name="chartParameters">Параметры на диаграмме.</param>
/// <param name="parameter">Параметры(Z, Y, G).</param>
Element::Element(mode mode, long double value, long double frequency, Point point, map<chartMode, tuple<long double, long double>> chartParameters, map<parameterMode, Complex> parameter)
{
	this->SetMode(mode);
	this->SetValue(value);
	this->SetFrequency(frequency);
	this->SetPoint(point);
	this->SetChartParameters(chartParameters);
	this->SetParameter(parameter);
}

/// <summary>
/// Сеттер типа элемента.
/// </summary>
/// <param name="mode">Тип элемента.</param>
void Element::SetMode(mode mode)
{
	this->elementMode = mode;
}

/// <summary>
/// Сеттер значения элемента.
/// </summary>
/// <param name="value">Значение.</param>
void Element::SetValue(long double value)
{
	this->value = value;
}

/// <summary>
/// Сеттер частоты.
/// </summary>
/// <param name="value">Частота.</param>
void Element::SetFrequency(long double value)
{
	this->frequency = value;
}

/// <summary>
/// Сеттер точки.
/// </summary>
/// <param name="point">Точка.</param>
void Element::SetPoint(Point point)
{
	this->point = point;
}

/// <summary>
/// Сеттер параметров диаграммы.
/// </summary>
/// <param name="chartParameters">Параметры диаграммы.</param>
void Element::SetChartParameters(map<chartMode, tuple<long double, long double>> chartParameters)
{
	this->chartParameters = chartParameters;
}

/// <summary>
/// Сеттер параметров(Z, Y, G).
/// </summary>
/// <param name="parameter">Параметры(Z, Y, G).</param>
void Element::SetParameter(map<parameterMode, Complex> parameter)
{
	this->parameters = parameter;
}

/// <summary>
/// Геттер типа элемента.
/// </summary>
/// <returns>Тип элемента.</returns>
mode Element::GetMode()
{
	return this->elementMode;
}

/// <summary>
/// Геттер значения элемента.
/// </summary>
/// <returns>Значение элемента.</returns>
long double Element::GetValue()
{
	return this->value;
}

/// <summary>
/// Геттер частоты.
/// </summary>
/// <returns>Частота.</returns>
long double Element::GetFrequency()
{
	return this->frequency;
}

/// <summary>
/// Геттер параметров диаграммы.
/// </summary>
/// <returns>Параметры диаграммы.</returns>
map<chartMode, tuple<long double, long double>> Element::GetChartParameters()
{
	return this->chartParameters;
}

/// <summary>
/// Геттер точки.
/// </summary>
/// <returns>Точка.</returns>
Point Element::GetPoint()
{
	return this->point;
}

/// <summary>
/// Геттер параметров(Z, Y, G).
/// </summary>
/// <returns>Параметры(Z, Y, G).</returns>
map<parameterMode, Complex> Element::GetParameter()
{
	return this->parameters;
}

/// <summary>
/// Деструктор класса Element.
/// </summary>
Element::~Element()
{
}

/// <summary>
/// Сериализация элемента.
/// </summary>
/// <returns>JsonObject.</returns>
QJsonObject Element::toJson() const
{
    QJsonObject json;
    json["elementType"] = static_cast<int>(getElementType());
    // Сериализация Point
    QJsonObject pointObj;
    pointObj["x"] = (double)this->point.x;
    pointObj["y"] = (double)this->point.y;
    json["point"] = pointObj;

    // Сериализация простых полей
    json["frequency"] = (double)frequency;
    json["value"] = (double)value;
    json["elementMode"] = static_cast<int>(elementMode);

    // Сериализация chartParameters (map<chartMode, tuple<long double, long double>>)
    QJsonObject chartParamsObj;
    for (const auto& [chartMode, values] : chartParameters) {
        QJsonObject tupleObj;
        tupleObj["first"] = (double)std::get<0>(values);
        tupleObj["second"] = (double)std::get<1>(values);
        chartParamsObj[QString::number(static_cast<int>(chartMode))] = tupleObj;
    }
    json["chartParameters"] = chartParamsObj;

    // Сериализация parameters (map<parameterMode, Complex>)
    QJsonObject paramsObj;
    for (const auto& [paramMode, complex] : parameters) {
        QJsonObject complexObj;
        complexObj["real"] = (double)complex.real();
        complexObj["imag"] = (double)complex.imag();
        paramsObj[QString::number(static_cast<int>(paramMode))] = complexObj;
    }
    json["parameters"] = paramsObj;

    return json;
}