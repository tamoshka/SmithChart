#pragma once
#include "Line.h"
#include "ElementFactory.h"
#include "systemParameters.h"
class CircuitElements
{
private:
	QList<Element*> circuitElements;
    static QJsonObject complexToJson(const Complex& c);

	static Complex jsonToComplex(const QJsonObject& obj);

	static QJsonObject elementToJson(const Element* element);

	static Element* jsonToElement(const QJsonObject& obj);
public:
	void AddCircuitElements(Element*);
	QList<Element*> GetCircuitElements();
	void DeleteCircuitElements();
	void Remove(int);
	CircuitElements();
	Complex z = Complex(-9999, -9999);
	Complex y = Complex(-9999, -9999);
	Complex g = Complex(-9999, -9999);
	long double realFirstPoint = -9999;
	long double imagFirstPoint = -9999;
	long double frequencyFirstPoint = -9999;
	Point firstPoint;
	map<chartMode, tuple<long double, long double>> chart;
	QJsonObject toJson() const;
	bool fromJson(const QJsonObject& json);
	bool loadFromFile(const QString& filePath);
	bool saveToFile(const QString& filePath) const;
	~CircuitElements();
};