#include "VerticalLinesElement.h"

/// <summary>
/// Сеттер электрической длины.
/// </summary>
/// <param name="electricalLength">Электрическая длина.</param>
void VerticalLinesElement::SetElectricalLength(long double electricalLength)
{
	this->_electricalLength = electricalLength;
}

/// <summary>
/// Сеттер физической длины.
/// </summary>
/// <param name="mechanicalLength">Физическая длина.</param>
void VerticalLinesElement::SetMechanicalLength(long double mechanicalLength)
{
	this->_mechanicalLength = mechanicalLength;
}

/// <summary>
/// Сеттер тета.
/// </summary>
/// <param name="theta">Тета.</param>
void VerticalLinesElement::SetTheta(long double theta)
{
	this->_theta = theta;
}

/// <summary>
/// Сеттер лямбды.
/// </summary>
/// <param name="lambda">Лямбда.</param>
void VerticalLinesElement::SetLambda(long double lambda)
{
	this->_lambda = lambda;
}

/// <summary>
/// Геттер электрической длины.
/// </summary>
/// <returns>Электрическая длина.</returns>
long double VerticalLinesElement::GetElectricalLength()
{
	return this->_electricalLength;
}

/// <summary>
/// Геттер физической длины
/// </summary>
/// <returns>Физическая длина.</returns>
long double VerticalLinesElement::GetMechanicalLength()
{
	return this->_mechanicalLength;
}

/// <summary>
/// Геттер тета.
/// </summary>
/// <returns>Тета.</returns>
long double VerticalLinesElement::GetTheta()
{
	return this->_theta;
}

/// <summary>
/// Геттер лямбда.
/// </summary>
/// <returns>Лямбда.</returns>
long double VerticalLinesElement::GetLambda()
{
	return this->_lambda;
}

/// <summary>
/// Конструктор класса VerticalLinesElement.
/// </summary>
/// <param name="mode">Тип элемента.</param>
/// <param name="value">Значение.</param>
/// <param name="frequency">Частота.</param>
/// <param name="point">Точка.</param>
/// <param name="chartParameters">Параметры на диаграмме.</param>
/// <param name="parameters">Параметры(Z, Y, G).</param>
/// <param name="electricalLength">Электрическая длина.</param>
/// <param name="mechanicalLength">Физическая длина.</param>
/// <param name="theta">Тета.</param>
/// <param name="lambda">Лямбда.</param>
VerticalLinesElement::VerticalLinesElement(mode mode, long double value, long double frequency, Point point, map<chartMode, tuple<long double, long double>> chartParameters,
	map<parameterMode, Complex> parameters, long double electricalLength, long double mechanicalLength, long double theta, long double lambda) :
	Element(mode, value, frequency, point, chartParameters, parameters)
{
	this->SetElectricalLength(electricalLength);
	this->SetMechanicalLength(mechanicalLength);
	this->SetTheta(theta);
	this->SetLambda(lambda);
}

/// <summary>
/// Сериализация шлейфов ХХ и КЗ в JSON.
/// </summary>
/// <returns>JsonObject.</returns>
QJsonObject VerticalLinesElement::toJson() const
{
	// Получаем базовый JSON
	QJsonObject json = Element::toJson();

	// Добавляем специфичные для VerticalLinesElement поля
	json["electricalLength"] = (double)_electricalLength;
	json["mechanicalLength"] = (double)_mechanicalLength;
	json["lambda"] = (double)_lambda;
	json["theta"] = (double)_theta;

	return json;
}

QJsonObject VerticalLinesElement::toCircuitJson(int& node, int& nodeMax, bool& prevTransform, bool& prevParallel, bool& prevOSSS)
{
    QJsonObject json;
    json["library"] = "Basic";
    QString modelName;
    int rotation = 90;
    QList<int> pinArray;
    QString paramName;
    double paramValue;
    QString paramFactor;
    QString secondParamName;
    double secondParamValue;
    QString secondParamFactor;
    switch (GetMode())
    {
        case OSLine:
        {
            modelName = "MLOC";
            if (prevParallel && !prevTransform)
            {
                pinArray.append(nodeMax + 1);
                node = nodeMax + 1;
                nodeMax++;
            }
            else
            {
                pinArray.append(node);
            }
            paramName = "R";
            paramFactor = "";
            ///paramValue = this->value;
            break;
        }
        case SSLine:
        {
            modelName = "MLSC";
            if (prevParallel && !prevTransform)
            {
                pinArray.append(nodeMax+1);
                node = nodeMax + 1;
                nodeMax++;
            }
            else
            {
                pinArray.append(node);
            }
            paramName = "R";
            paramFactor = "";
           ///paramValue = this->value;
            
            break;
        }  
    }
    prevTransform = false;
    prevParallel = true;
    prevOSSS = true;
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