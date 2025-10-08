#include "circuitElements.h"

CircuitElements::CircuitElements()
{
	this->circuitElements = QList<Element*>();
}

CircuitElements::~CircuitElements()
{
}

void CircuitElements::AddCircuitElements(Element* element)
{
	this->circuitElements.append(element);
}

void CircuitElements::DeleteCircuitElements()
{
	delete this->circuitElements.last();
	this->circuitElements.pop_back();
}

QList<Element*> CircuitElements::GetCircuitElements()
{
	return this->circuitElements;
}

void CircuitElements::Remove(int i)
{
	this->circuitElements.takeAt(i);
}

QJsonObject CircuitElements::toJson() const
{
    QJsonObject json;

    json["z"] = complexToJson(z);
    json["y"] = complexToJson(y);
    json["g"] = complexToJson(g);

    json["realFirstPoint"] = (double)realFirstPoint;
    json["imagFirstPoint"] = (double)imagFirstPoint;
    json["frequencyFirstPoint"] = (double)frequencyFirstPoint;

    QJsonObject pointObj;
    pointObj["x"] = (double)firstPoint.x;
    pointObj["y"] = (double)firstPoint.y;
    json["firstPoint"] = pointObj;

    QJsonArray elementsArray;
    for (const Element* element : circuitElements) {
        if (element) {
            elementsArray.append(elementToJson(element));
        }
    }
    json["circuitElements"] = elementsArray;

    QJsonObject chartObj;
    for (const auto& [mode, values] : chart) {
        QJsonObject valueObj;
        valueObj["first"] = (double)std::get<0>(values);
        valueObj["second"] = (double)std::get<1>(values);
        chartObj[QString::number(static_cast<int>(mode))] = valueObj;
    }
    json["chart"] = chartObj;

    return json;
}

bool CircuitElements::fromJson(const QJsonObject& json)
{
    try {
        // Десериализация Complex типов
        if (json.contains("z"))
            z = jsonToComplex(json["z"].toObject());
        if (json.contains("y"))
            y = jsonToComplex(json["y"].toObject());
        if (json.contains("g"))
            g = jsonToComplex(json["g"].toObject());

        // Десериализация простых типов
        if (json.contains("realFirstPoint"))
            realFirstPoint = json["realFirstPoint"].toDouble();
        if (json.contains("imagFirstPoint"))
            imagFirstPoint = json["imagFirstPoint"].toDouble();
        if (json.contains("frequencyFirstPoint"))
            frequencyFirstPoint = json["frequencyFirstPoint"].toDouble();

        // Десериализация Point
        if (json.contains("firstPoint") && json["firstPoint"].isObject()) {
            QJsonObject pointObj = json["firstPoint"].toObject();
            firstPoint.x = pointObj["x"].toDouble();
            firstPoint.y = pointObj["y"].toDouble();
        }

        // Десериализация элементов цепи
        if (json.contains("circuitElements") && json["circuitElements"].isArray()) {
            // Очищаем существующие элементы

            QJsonArray elementsArray = json["circuitElements"].toArray();
            for (const auto& value : elementsArray) {
                Element* element = jsonToElement(value.toObject());
                if (element) {
                    AddCircuitElements(element);
                }
            }
        }

        // Десериализация chart map
        if (json.contains("chart") && json["chart"].isObject()) {
            chart.clear();
            QJsonObject chartObj = json["chart"].toObject();

            for (const QString& key : chartObj.keys()) {
                chartMode mode = static_cast<chartMode>(key.toInt());
                QJsonObject valueObj = chartObj[key].toObject();

                long double first = valueObj["first"].toDouble();
                long double second = valueObj["second"].toDouble();

                chart[mode] = std::make_tuple(first, second);
            }
        }

        return true;
    }
    catch (...) {
        qDebug() << "Ошибка при десериализации CircuitElements";
        return false;
    }
}

QJsonObject CircuitElements::complexToJson(const Complex& c)
{
    QJsonObject obj;
    obj["real"] = (double)c.real();
    obj["imag"] = (double)c.imag();
    return obj;
}

Complex CircuitElements::jsonToComplex(const QJsonObject& obj)
{
    long double real = obj["real"].toDouble();
    long double imag = obj["imag"].toDouble();
    return Complex(real, imag);
}

QJsonObject CircuitElements::elementToJson(const Element* element)
{
    if (!element) {
        return QJsonObject();
    }

    return element->toJson();
}

Element* CircuitElements::jsonToElement(const QJsonObject& obj)
{
    return ElementFactory::createFromJson(obj);
}

bool CircuitElements::loadFromFile(const QString& filePath)
{
    if (!QFile::exists(filePath)) {
        qDebug() << "Файл не найден:" << filePath;
        return false;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Не удалось открыть файл для чтения:" << filePath;
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    if (data.isEmpty()) {
        qDebug() << "Файл пустой:" << filePath;
        return false;
    }

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << "Ошибка парсинга JSON:" << error.errorString();
        return false;
    }

    return fromJson(doc.object());
}

bool CircuitElements::saveToFile(const QString& filePath) const
{
    QJsonObject json = toJson();
    QJsonDocument doc(json);

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Не удалось открыть файл для записи:" << filePath;
        return false;
    }

    qint64 bytesWritten = file.write(doc.toJson());
    file.close();

    if (bytesWritten > 0) {
        qDebug() << "CircuitElements сохранен:" << filePath;
        return true;
    }
    return false;
}