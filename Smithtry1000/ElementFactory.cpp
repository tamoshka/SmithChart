#include "ElementFactory.h"
#include "Element.h"
#include "VerticalLinesElement.h"
#include "Line.h"

Element* ElementFactory::createFromJson(const QJsonObject& json)
{
    // Определяем тип элемента
    ElementType type = ElementType::BaseElement;
    if (json.contains("elementType")) {
        type = static_cast<ElementType>(json["elementType"].toInt());
    }

    // Создаем элемент соответствующего типа
    switch (type) {
    case ElementType::Lines:
        return createLinesElement(json);
    case ElementType::VerticalLines:
        return createVerticalLinesElement(json);
    case ElementType::BaseElement:
    default:
        return createBaseElement(json);
    }
}

Element* ElementFactory::createBaseElement(const QJsonObject& json)
{
    try {
        Point pt{ 0, 0 };
        long double freq = 0;
        long double val = 0;
        mode elemMode = mode::Default;
        map<chartMode, tuple<long double, long double>> chartParams;
        map<parameterMode, Complex> params;

        parseCommonFields(json, pt, freq, val, elemMode, chartParams, params);

        return new Element(elemMode, val, freq, pt, chartParams, params);
    }
    catch (...) {
        qDebug() << "Ошибка при создании Element из JSON";
        return nullptr;
    }
}

VerticalLinesElement* ElementFactory::createVerticalLinesElement(const QJsonObject& json)
{
    try {
        Point pt{ 0, 0 };
        long double freq = 0;
        long double val = 0;
        mode elemMode = mode::Default;
        map<chartMode, tuple<long double, long double>> chartParams;
        map<parameterMode, Complex> params;

        parseCommonFields(json, pt, freq, val, elemMode, chartParams, params);

        // Читаем специфичные для VerticalLinesElement параметры
        long double electricalLength = json.value("electricalLength").toDouble(0.0);
        long double mechanicalLength = json.value("mechanicalLength").toDouble(0.0);
        long double lambda = json.value("lambda").toDouble(0.0);
        long double theta = json.value("theta").toDouble(0.0);

        return new VerticalLinesElement(elemMode, val, freq, pt, chartParams, params,
            electricalLength, mechanicalLength, theta, lambda);
    }
    catch (...) {
        qDebug() << "Ошибка при создании VerticalLinesElement из JSON";
        return nullptr;
    }
}

LinesElement* ElementFactory::createLinesElement(const QJsonObject& json)
{
    try {
        Point pt{ 0, 0 };
        long double freq = 0;
        long double val = 0;
        mode elemMode = mode::Default;
        map<chartMode, tuple<long double, long double>> chartParams;
        map<parameterMode, Complex> params;

        parseCommonFields(json, pt, freq, val, elemMode, chartParams, params);

        // Читаем параметры VerticalLinesElement
        long double electricalLength = json.value("electricalLength").toDouble(0.0);
        long double mechanicalLength = json.value("mechanicalLength").toDouble(0.0);
        long double lambda = json.value("lambda").toDouble(0.0);
        long double theta = json.value("theta").toDouble(0.0);

        // Читаем специфичный для LinesElement параметр
        long double alpha = json.value("alpha").toDouble(0.0);

        return new LinesElement(elemMode, val, freq, pt, chartParams, params,
            electricalLength, mechanicalLength, theta, lambda, alpha);
    }
    catch (...) {
        qDebug() << "Ошибка при создании LinesElement из JSON";
        return nullptr;
    }
}

void ElementFactory::parseCommonFields(const QJsonObject& json,
    Point& pt,
    long double& freq,
    long double& val,
    mode& elemMode,
    map<chartMode, tuple<long double, long double>>& chartParams,
    map<parameterMode, Complex>& params)
{
    // Парсинг Point
    if (json.contains("point") && json["point"].isObject()) {
        QJsonObject pointObj = json["point"].toObject();
        pt.x = pointObj.value("x").toDouble(0.0);
        pt.y = pointObj.value("y").toDouble(0.0);
    }

    // Парсинг простых полей
    freq = json.value("frequency").toDouble(0.0);
    val = json.value("value").toDouble(0.0);
    elemMode = static_cast<mode>(json.value("elementMode").toInt(static_cast<int>(mode::Default)));

    // Парсинг chartParameters
    if (json.contains("chartParameters") && json["chartParameters"].isObject()) {
        QJsonObject chartParamsObj = json["chartParameters"].toObject();
        for (const QString& key : chartParamsObj.keys()) {
            chartMode cm = static_cast<chartMode>(key.toInt());
            QJsonObject tupleObj = chartParamsObj[key].toObject();

            long double first = tupleObj.value("first").toDouble(0.0);
            long double second = tupleObj.value("second").toDouble(0.0);

            chartParams[cm] = std::make_tuple(first, second);
        }
    }

    // Парсинг parameters
    if (json.contains("parameters") && json["parameters"].isObject()) {
        QJsonObject paramsObj = json["parameters"].toObject();
        for (const QString& key : paramsObj.keys()) {
            parameterMode pm = static_cast<parameterMode>(key.toInt());
            QJsonObject complexObj = paramsObj[key].toObject();

            long double real = complexObj.value("real").toDouble(0.0);
            long double imag = complexObj.value("imag").toDouble(0.0);

            params[pm] = Complex(real, imag);
        }
    }
}