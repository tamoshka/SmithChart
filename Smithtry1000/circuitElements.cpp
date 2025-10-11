#include "circuitElements.h"

/// <summary>
/// Конструктор класса CircuitElements.
/// </summary>
CircuitElements::CircuitElements()
{
	this->circuitElements = QList<Element*>();
}

/// <summary>
/// Деструктор класса CircuitElements.
/// </summary>
CircuitElements::~CircuitElements()
{
}

/// <summary>
/// Добавление нового элемента в цепь.
/// </summary>
/// <param name="element">Элемент.</param>
void CircuitElements::AddCircuitElements(Element* element)
{
	this->circuitElements.append(element);
}

/// <summary>
/// Удаление последнего элемента из цепи.
/// </summary>
void CircuitElements::DeleteCircuitElements()
{
	delete this->circuitElements.last();
	this->circuitElements.pop_back();
}

/// <summary>
/// Получение цепи.
/// </summary>
/// <returns>Цепь.</returns>
QList<Element*> CircuitElements::GetCircuitElements()
{
	return this->circuitElements;
}

/// <summary>
/// Убирание конкретного элемента из цепи (Для TuneWidget).
/// </summary>
/// <param name="i">Индекс элемента.</param>
void CircuitElements::Remove(int i)
{
	this->circuitElements.takeAt(i);
}

/// <summary>
/// Сериализация цепи, создание объекта JSON.
/// </summary>
/// <returns>JsonObject.</returns>
QJsonObject CircuitElements::toJson() const
{
    QJsonObject json;

    json["z"] = complexToJson(z);
    json["y"] = complexToJson(y);
    json["g"] = complexToJson(g);

    json["z0"] = (double)z0;

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
    
    QJsonArray morePointsObj;
    for (const Point point : morePoints)
    {
        QJsonObject pointObj;
        pointObj["x"] = (double)point.x;
        pointObj["y"] = (double)point.y;

        morePointsObj.append(pointObj);
    }
    json["morePoints"] = morePointsObj;

    QJsonArray pointIndexesObj;
    for (const int ind : pointIndexes)
    {
        pointIndexesObj.append(ind);
    }
    json["pointIndexes"] = pointIndexesObj;

    QJsonArray elementIndexesObj;
    for (const int ind : elementIndexes)
    {
        elementIndexesObj.append(ind);
    }
    json["elementIndexes"] = elementIndexesObj;

    QJsonArray frequenciesObj;
    for (const long double val : frequencyList)
    {
        frequenciesObj.append((double)val);
    }
    json["frequencyList"] = frequenciesObj;

    return json;
}

/// <summary>
/// Загрузка из JSON.
/// </summary>
/// <param name="json">JsonObject.</param>
/// <returns>Получилось/не получилось.</returns>
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
        if (json.contains("z0"))
            z0 = json["z0"].toDouble();

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

        if (json.contains("morePoints") && json["morePoints"].isArray())
        {
            QJsonArray morePointsArray = json["morePoints"].toArray();
            for (const auto& value : morePointsArray)
            {
                Point point;
                point.x = value.toObject()["x"].toDouble();
                point.y = value.toObject()["y"].toDouble();
                morePoints.append(point);
            }
        }

        if (json.contains("elementIndexes") && json["elementIndexes"].isArray())
        {
            QJsonArray elementIndexesObj = json["elementIndexes"].toArray();
            for (const auto& value : elementIndexesObj)
            {
                elementIndexes.append(value.toInt());
            }
        }

        if (json.contains("pointIndexes") && json["pointIndexes"].isArray())
        {
            QJsonArray pointIndexesObj = json["pointIndexes"].toArray();
            for (const auto& value : pointIndexesObj)
            {
                pointIndexes.append(value.toInt());
            }
        }

        if (json.contains("frequencyList") && json["frequencyList"].isArray())
        {
            QJsonArray frequencyListObj = json["frequencyList"].toArray();
            for (const auto& value : frequencyListObj)
            {
                frequencyList.append(value.toDouble());
            }
        }

        return true;
    }
    catch (...) {
        qDebug() << "Ошибка при десериализации CircuitElements";
        return false;
    }
}

/// <summary>
/// Помощь в сериализации комплексных чисел.
/// </summary>
/// <param name="c">Число.</param>
/// <returns>JsonObject.</returns>
QJsonObject CircuitElements::complexToJson(const Complex& c)
{
    QJsonObject obj;
    obj["real"] = (double)c.real();
    obj["imag"] = (double)c.imag();
    return obj;
}

/// <summary>
/// Помощь в десериализации комплексных чисел.
/// </summary>
/// <param name="obj">JsonObject.</param>
/// <returns>Число.</returns>
Complex CircuitElements::jsonToComplex(const QJsonObject& obj)
{
    long double real = obj["real"].toDouble();
    long double imag = obj["imag"].toDouble();
    return Complex(real, imag);
}

/// <summary>
/// Помощь в сериализации элементов цепи.
/// </summary>
/// <param name="element">Элемент.</param>
/// <returns>JsonObject.</returns>
QJsonObject CircuitElements::elementToJson(const Element* element)
{
    if (!element) {
        return QJsonObject();
    }

    return element->toJson();
}

/// <summary>
/// Помощь в десериализации элементов цепи.
/// </summary>
/// <param name="obj">JsonObject.</param>
/// <returns>Элемент.</returns>
Element* CircuitElements::jsonToElement(const QJsonObject& obj)
{
    return ElementFactory::createFromJson(obj);
}

/// <summary>
/// Загрузка из JSON.
/// </summary>
/// <param name="filePath">Путь к файлу.</param>
/// <returns>Получилось/не получилось.</returns>
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

/// <summary>
/// Сохранение в файл JSON.
/// </summary>
/// <param name="filePath">Путь к файлу.</param>
/// <returns>Получилось/не получилось.</returns>
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