#pragma once
#include <QJsonObject>
#include "general.h"

// Forward declarations - избегаем include
class Element;
class VerticalLinesElement;
class LinesElement;

// Фабричный класс для создания элементов из JSON
class ElementFactory
{
public:
    // Главный метод - создает элемент правильного типа из JSON
    static Element* createFromJson(const QJsonObject& json);

    // Вспомогательные методы для каждого типа
    static Element* createBaseElement(const QJsonObject& json);
    static VerticalLinesElement* createVerticalLinesElement(const QJsonObject& json);
    static LinesElement* createLinesElement(const QJsonObject& json);

private:
    // Вспомогательные методы для парсинга общих полей
    static void parseCommonFields(const QJsonObject& json,
        Point& pt,
        long double& freq,
        long double& val,
        mode& elemMode,
        map<chartMode, tuple<long double, long double>>& chartParams,
        map<parameterMode, Complex>& params);
};