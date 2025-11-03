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

 QJsonObject LinesElement::toCircuitJson(int& node, int& nodeMax, bool& prevTransform, bool& prevParallel, bool& prevOSSS)
 {
     QJsonObject json;
     json["library"] = "Basic";
     QString modelName;
     int rotation = 0;
     QList<int> pinArray;
     QString paramName;
     double paramValue;
     QString paramFactor;
     QString secondParamName;
     double secondParamValue;
     QString secondParamFactor;
     modelName = "MLIN";
     pinArray.append(node);
     pinArray.append(nodeMax + 1);
     node = nodeMax + 1;
     nodeMax++;
     paramName = "R";
     paramFactor = "";
     ///paramValue = this->value;
     prevTransform = false;
     prevParallel = false;
     prevOSSS = false;
     json["model"] = modelName;
     QJsonObject rotate;
     rotate["rotation"] = rotation;
     json["placement"] = rotate;
     int i = 1;

     QJsonArray pins;
     for (auto var : pinArray)
     {
         QJsonObject pin;
         QString pinNumber = "P" + QString::number(i);
         pin[pinNumber] = var;
         pins.append(pin);
         i++;
     }
     json["pins"] = pins;
     QJsonArray jsonParameters;
     QJsonObject firstParameters;
     firstParameters["name"] = paramName;
     firstParameters["value"] = paramValue;
     firstParameters["factor"] = paramFactor;
     jsonParameters.append(firstParameters);
     json["parameters"] = jsonParameters;

     return json;
 }