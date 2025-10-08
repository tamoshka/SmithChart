#include "Element.h"

Element::Element(mode mode, long double value, long double frequency, Point point, map<chartMode, tuple<long double, long double>> chartParameters, map<parameterMode, Complex> parameter)
{
	this->SetMode(mode);
	this->SetValue(value);
	this->SetFrequency(frequency);
	this->SetPoint(point);
	this->SetChartParameters(chartParameters);
	this->SetParameter(parameter);
}

void Element::SetMode(mode mode)
{
	this->elementMode = mode;
}

void Element::SetValue(long double value)
{
	this->value = value;
}

void Element::SetFrequency(long double value)
{
	this->frequency = value;
}

void Element::SetPoint(Point point)
{
	this->point = point;
}

void Element::SetChartParameters(map<chartMode, tuple<long double, long double>> chartParameters)
{
	this->chartParameters = chartParameters;
}

void Element::SetParameter(map<parameterMode, Complex> parameter)
{
	this->parameters = parameter;
}

mode Element::GetMode()
{
	return this->elementMode;
}

long double Element::GetValue()
{
	return this->value;
}

long double Element::GetFrequency()
{
	return this->frequency;
}

map<chartMode, tuple<long double, long double>> Element::GetChartParameters()
{
	return this->chartParameters;
}

Point Element::GetPoint()
{
	return this->point;
}

map<parameterMode, Complex> Element::GetParameter()
{
	return this->parameters;
}


Element::~Element()
{
}

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