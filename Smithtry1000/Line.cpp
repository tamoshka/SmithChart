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

 /// <summary>
 /// Сериализация элемента для САПР.
 /// </summary>
 /// <param name="node">Текущий узел.</param>
 /// <param name="nodeMax">Максимальный узел.</param>
 /// <param name="prevTransform">До этого трансформатор/нет.</param>
 /// <param name="prevParallel">До этого параллельный элемент/нет.</param>
 /// <param name="prevOSSS">До этого шлейф/нет.</param>
 /// <returns>JsonObject.</returns>
 QJsonObject LinesElement::toCircuitJson(int& node, int& nodeMax, bool& prevTransform, bool& prevParallel, bool& prevOSSS)
 {
     QJsonObject json;
     json["library"] = "Basic";
     QString modelName;
     int rotation = 0;
     QList<int> pinArray;
     modelName = "TLINP";
     if (prevOSSS)
     {
         pinArray.append(nodeMax + 1);
         pinArray.append(nodeMax + 2);
         node = nodeMax + 2;
         nodeMax+=2;
     }
     else
     {
         pinArray.append(node);
         pinArray.append(nodeMax+1);
         node = nodeMax + 1;
         nodeMax++;
     }
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
     firstParameters["name"] = "Z0";
     firstParameters["value"] = (double)this->GetValue();
     firstParameters["factor"] = "";
     QJsonObject secondParameters;
     secondParameters["name"] = "L";
     secondParameters["value"] = (double)this->GetElectricalLength();
     secondParameters["factor"] = "u";
     QJsonObject thirdParameters;
     thirdParameters["name"] = "F0";
     thirdParameters["value"] = (double)this->GetFrequency() / 1e9;
     thirdParameters["factor"] = "G";
     QJsonObject fourthParameters;
     fourthParameters["name"] = "Ere";
     fourthParameters["value"] = (double)pow(this->GetElectricalLength() / this->GetMechanicalLength(), 2);
     fourthParameters["factor"] = "";
     QJsonObject fifthParameters;
     fifthParameters["name"] = "A";
     fifthParameters["value"] = 0;
     fifthParameters["factor"] = "";
     QJsonObject sixParameters;
     sixParameters["name"] = "TanD";
     sixParameters["value"] = 0;
     sixParameters["factor"] = "";
     jsonParameters.append(firstParameters);
     jsonParameters.append(secondParameters);
     jsonParameters.append(thirdParameters);
     jsonParameters.append(fourthParameters);
     jsonParameters.append(fifthParameters);
     jsonParameters.append(sixParameters);
     json["parameters"] = jsonParameters;
     return json;
 }