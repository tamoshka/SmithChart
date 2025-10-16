#pragma once
#include "Line.h"
#include "ElementFactory.h"
#include "systemParameters.h"

/// <summary>
/// Класс хранения цепи.
/// </summary>
class CircuitElements
{
private:
	QList<Element*> circuitElements;
    static QJsonObject complexToJson(const Complex& c);

	static Complex jsonToComplex(const QJsonObject& obj);

	static QJsonObject elementToJson(const Element* element);

	static Element* jsonToElement(const QJsonObject& obj);
public:
	QList<Point> morePoints;
	QSet<double> VSWRCircles;
	QSet<double> QCircles;
	long double z0 = SystemParameters::z0;
	QList<int> elementIndexes;
	QList<int> pointIndexes;
	QList<long double> frequencyList;
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
    CircuitElements(const CircuitElements& other) {
        // ГЛУБОКОЕ копирование - создаем новые объекты Element
        for (Element* elem : other.circuitElements) {
            if (elem != nullptr) {
                circuitElements.append(new Element(*elem)); // Копируем объект, а не указатель
            }
            else {
                circuitElements.append(nullptr);
            }
        }
        // Копируем остальные поля
        morePoints = other.morePoints;
        VSWRCircles = other.VSWRCircles;
        QCircles = other.QCircles;
        z0 = other.z0;
        elementIndexes = other.elementIndexes;
        pointIndexes = other.pointIndexes;
        frequencyList = other.frequencyList;
        z = other.z;
        y = other.y;
        g = other.g;
        realFirstPoint = other.realFirstPoint;
        imagFirstPoint = other.imagFirstPoint;
        frequencyFirstPoint = other.frequencyFirstPoint;
        firstPoint = other.firstPoint;
        chart = other.chart;
    }
    CircuitElements& operator=(const CircuitElements& other) {
        if (this != &other) {
            // Очистка текущих данных
            for (Element* elem : circuitElements) {
                delete elem;
            }
            circuitElements.clear();

            // Глубокое копирование
            for (Element* elem : other.circuitElements) {
                if (elem != nullptr) {
                    circuitElements.append(new Element(*elem));
                }
            }

            // Копирование остальных полей
            morePoints = other.morePoints;
            VSWRCircles = other.VSWRCircles;
            QCircles = other.QCircles;
            z0 = other.z0;
            elementIndexes = other.elementIndexes;
            pointIndexes = other.pointIndexes;
            frequencyList = other.frequencyList;
            z = other.z;
            y = other.y;
            g = other.g;
            realFirstPoint = other.realFirstPoint;
            imagFirstPoint = other.imagFirstPoint;
            frequencyFirstPoint = other.frequencyFirstPoint;
            firstPoint = other.firstPoint;
            chart = other.chart;
        }
        return *this;
    }
};