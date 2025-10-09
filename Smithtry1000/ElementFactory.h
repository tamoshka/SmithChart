#pragma once
#include <QJsonObject>
#include "general.h"

class Element;
class VerticalLinesElement;
class LinesElement;

/// <summary>
/// Фабрика для сериализации элементов в JSON.
/// </summary>
class ElementFactory
{
public:
    static Element* createFromJson(const QJsonObject& json);

    static Element* createBaseElement(const QJsonObject& json);
    static VerticalLinesElement* createVerticalLinesElement(const QJsonObject& json);
    static LinesElement* createLinesElement(const QJsonObject& json);

private:
    static void parseCommonFields(const QJsonObject& json,
        Point& pt,
        long double& freq,
        long double& val,
        mode& elemMode,
        map<chartMode, tuple<long double, long double>>& chartParams,
        map<parameterMode, Complex>& params);
};