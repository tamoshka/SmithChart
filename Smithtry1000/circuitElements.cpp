#include "circuitElements.h"
#include "systemParameters.h"

/// <summary>
/// Конструктор класса CircuitElements.
/// </summary>
CircuitElements::CircuitElements()
{
    this->z0 = SystemParameters::z0;
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
    if (element->GetMode() == OSLine || element->GetMode() == SSLine)
    {
        VerticalLinesElement* temp = dynamic_cast<VerticalLinesElement*>(element);
        this->circuitElements.append(new VerticalLinesElement(*temp));
    }
    else if (element->GetMode() == Line)
    {
        LinesElement* temp = dynamic_cast<LinesElement*>(element);
        this->circuitElements.append(new LinesElement(*temp));
    }
    else
    {
        this->circuitElements.append(new Element(*element));
    }
}

void CircuitElements::AppendCircuitElements(Element* element)
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

    QJsonArray qCirclesObj;
    for (const double val : QCircles)
    {
        qCirclesObj.append(val);
    }
    json["QCircles"] = qCirclesObj;

    QJsonArray VSWRCirclesObj;
    for (const double val : VSWRCircles)
    {
        VSWRCirclesObj.append(val);
    }
    json["VSWRCircles"] = VSWRCirclesObj;

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

        if (json.contains("QCircles") && json["QCircles"].isArray())
        {
            QJsonArray qCirclesObj = json["QCircles"].toArray();
            for (const auto& value : qCirclesObj)
            {
                QCircles.insert(value.toDouble());
            }
        }

        if (json.contains("VSWRCircles") && json["VSWRCircles"].isArray())
        {
            QJsonArray VSWRCirclesObj = json["VSWRCircles"].toArray();
            for (const auto& value : VSWRCirclesObj)
            {
                VSWRCircles.insert(value.toDouble());
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
/// Загрузка из файла SC.
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
/// Сохранение в файл SC.
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

/// <summary>
/// Сохранение в JSON для САПР.
/// </summary>
/// <returns></returns>
QJsonObject CircuitElements::toCircuitJson() const
{
    QJsonObject json;
    json["name"] = "SmithChart";
    QJsonObject schematic;
    QJsonArray components;
    QJsonObject nodes;
    QJsonArray wires;

    int node = 0;
    int nodeMax = 0;
    bool prevTransform = false;
    bool prevParallel = true;
    bool prevOSSS = false;
    QJsonArray firstNode;
    firstNode.append(0);
    firstNode.append(0);
    nodes["0"] = firstNode;
    int horCount = 0;
    QJsonObject firstPort;
    firstPort["library"] = "Basic";
    firstPort["model"] = "TERMG";
    QJsonObject firstPortPlacement;
    firstPortPlacement["rotation"] = 0;
    firstPort["placement"] = firstPortPlacement;
    QJsonArray firstPortPins;
    QJsonObject firstPortPin;
    firstPortPin["P1"] = 0;
    firstPortPins.append(firstPortPin);
    firstPort["pins"] = firstPortPins;
    QJsonArray firstPortParameters;
    QJsonObject firstPortParameter;
    firstPortParameter["name"] = "Num";
    firstPortParameter["value"] = 1;
    firstPortParameter["factor"] = "";
    QJsonObject first2PortParameter;
    first2PortParameter["name"] = "R";
    first2PortParameter["value"] = (double)this->realFirstPoint;
    first2PortParameter["factor"] = "";
    QJsonObject first3PortParameter;
    first3PortParameter["name"] = "X";
    first3PortParameter["value"] = (double)this->imagFirstPoint;
    first3PortParameter["factor"] = "";
    QJsonObject first4PortParameter;
    first4PortParameter["name"] = "Vdc";
    first4PortParameter["value"] = 0;
    first4PortParameter["factor"] = "";
    firstPortParameters.append(firstPortParameter);
    firstPortParameters.append(first2PortParameter);
    firstPortParameters.append(first3PortParameter);
    firstPortParameters.append(first4PortParameter);
    firstPort["parameters"] = firstPortParameters;
    components.append(firstPort);
    int prevNode = node;
    bool prevprevParallel = prevParallel;
    bool prevprevOSSS = prevOSSS;
    int prevNodeMax = nodeMax;
    ElementsNodesWiresInJSON(prevParallel, horCount, nodeMax, node, prevNode, prevOSSS, nodes, wires, components);
    QJsonObject secondPort;
    
    secondPort["library"] = "Basic";
    secondPort["model"] = "TERMG";
    QJsonObject secondPortPlacement;
    secondPortPlacement["rotation"] = 180;
    secondPort["placement"] = secondPortPlacement;
    if (prevParallel)
    {
        QJsonArray newNode;
        newNode.append((horCount+1) * 4);
        newNode.append(0);
        nodes[QString::number(nodeMax + 1)] = newNode;
        nodeMax++;
        QJsonArray wireNodes;
        wireNodes.append(node);
        wireNodes.append(nodeMax);
        QJsonObject wire;

        wire["title"] = "out";
        wire["nodes"] = wireNodes;
        wires.append(wire);
    }
    QJsonArray secondPortPins;
    QJsonObject secondPortPin;
    secondPortPin["P1"] = nodeMax;
    secondPortPins.append(secondPortPin);
    secondPort["pins"] = secondPortPins;
    QJsonArray secondPortParameters;
    QJsonObject secondPortParameter;
    secondPortParameter["name"] = "Num";
    secondPortParameter["value"] = 2;
    secondPortParameter["factor"] = "";
    QJsonObject second2PortParameter;
    second2PortParameter["name"] = "R";
    second2PortParameter["value"] = (double)this->circuitElements[circuitElements.size()-1]->GetParameter()[Z].real();
    second2PortParameter["factor"] = "";
    QJsonObject second3PortParameter;
    second3PortParameter["name"] = "X";
    second3PortParameter["value"] = (double)-this->circuitElements[circuitElements.size() - 1]->GetParameter()[Z].imag();
    second3PortParameter["factor"] = "";
    QJsonObject second4PortParameter;
    second4PortParameter["name"] = "Vdc";
    second4PortParameter["value"] = 0;
    second4PortParameter["factor"] = "";
    secondPortParameters.append(secondPortParameter);
    secondPortParameters.append(second2PortParameter);
    secondPortParameters.append(second3PortParameter);
    secondPortParameters.append(second4PortParameter);
    secondPort["parameters"] = secondPortParameters;
    components.append(secondPort);
    schematic["components"] = components;
    schematic["nodes"] = nodes;
    schematic["wires"] = wires;
    json["schematic"] = schematic;
    return json;
}

/// <summary>
/// Запись элементов, узлов и проводов в JSON.
/// </summary>
/// <param name="prevParallel">Элемент параллельный/трансформатор.</param>
/// <param name="horCount">Количество горизонтальных элементов/подряд идущих параллельных/трансформаторов.</param>
/// <param name="nodeMax">Максимальный номер узла.</param>
/// <param name="node">Текущий номер узла.</param>
/// <param name="prevNode">Предыдущий номер узла.</param>
/// <param name="prevOSSS">Элемент шлейф.</param>
/// <param name="nodes">Узлы в JSON.</param>
/// <param name="wires">Провода в JSON.</param>
/// <param name="components">Компоненты в JSON.</param>
void CircuitElements::ElementsNodesWiresInJSON(bool &prevParallel, int &horCount, int &nodeMax, int &node, int &prevNode, bool& prevOSSS, QJsonObject& nodes, QJsonArray& wires, QJsonArray& components) const
{
    bool prevprevParallel = prevParallel;
    bool prevprevOSSS = prevOSSS;
    int prevNodeMax = nodeMax;
    bool prevTransform = false;
    for (int i = 0; i < circuitElements.size(); i++)
    {
        if (circuitElements[i]) {
            prevprevParallel = prevParallel;
            prevprevOSSS = prevOSSS;
            prevNode = node;
            prevNodeMax = nodeMax;
            components.append(elementToCircuitJson(circuitElements[i], node, nodeMax, prevTransform, prevParallel, prevOSSS));
            if (prevTransform)
            {
                TransformInJSON(prevprevParallel, horCount, nodeMax, prevNode, nodes, wires, components);
            }
            else if (prevOSSS)
            {
                if (prevprevParallel)
                {
                    QJsonArray wireNodes;
                    wireNodes.append(prevNode);
                    wireNodes.append(node);
                    QJsonObject wire;
                    if (horCount == 0)
                    {
                        wire["title"] = "in";
                    }
                    else
                    {
                        wire["title"] = "";
                    }
                    wire["nodes"] = wireNodes;
                    wires.append(wire);
                    QJsonArray secondNode;
                    secondNode.append((horCount + 1) * 4);
                    secondNode.append(0);
                    nodes[QString::number(node)] = secondNode;
                    horCount++;
                }
            }
            else if (prevParallel)
            {
                ParallelInJSON(prevprevParallel, horCount, nodeMax, prevNode, node, nodes, wires, components);
            }
            else if (circuitElements[i]->GetMode() == Line)
            {
                if (prevprevOSSS)
                {
                    QJsonArray wireNodes;
                    wireNodes.append(prevNode);
                    wireNodes.append(node - 1);
                    QJsonObject wire;
                    if (horCount == 0)
                    {
                        wire["title"] = "in";
                    }
                    else
                    {
                        wire["title"] = "";
                    }
                    wire["nodes"] = wireNodes;
                    wires.append(wire);
                    QJsonArray secondNode;
                    secondNode.append((horCount + 1) * 4);
                    secondNode.append(0);
                    QJsonArray thirdNode;
                    thirdNode.append((horCount + 2) * 4);
                    thirdNode.append(0);
                    nodes[QString::number(node - 1)] = secondNode;
                    nodes[QString::number(node)] = thirdNode;
                    horCount++;
                }
                else
                {
                    QJsonArray secondNode;
                    secondNode.append((horCount + 1) * 4);
                    secondNode.append(0);
                    nodes[QString::number(node)] = secondNode;
                }
                horCount++;
            }
            else
            {
                QJsonArray secondNode;
                secondNode.append((horCount + 1) * 4);
                secondNode.append(0);
                nodes[QString::number(node)] = secondNode;
                horCount++;
            }
        }
    }
}

/// <summary>
/// Логика добавления трансформатора (его узлов и проводов) в JSON.
/// </summary>
/// <param name="prevprevParallel">Предыдущий элемент параллельный/трансформатор.</param>
/// <param name="horCount">Количество горизонтальных элементов/подряд идущих параллельных/трансформаторов.</param>
/// <param name="nodeMax">Максимальный номер узла.</param>
/// <param name="prevNode">Предыдущий номер узла.</param>
/// <param name="nodes">Узлы в JSON.</param>
/// <param name="wires">Провода в JSON.</param>
/// <param name="components">Компоненты в JSON.</param>
void CircuitElements::TransformInJSON(bool& prevprevParallel, int& horCount, int& nodeMax, int& prevNode, QJsonObject& nodes, QJsonArray& wires, QJsonArray& components) const
{
    if (prevprevParallel)
    {
        QJsonArray firstTrNode;
        QJsonArray secondNode;
        QJsonArray thirdNode;
        QJsonArray fourthNode;
        firstTrNode.append((horCount + 1) * 4);
        firstTrNode.append(0);
        secondNode.append((horCount + 2) * 4);
        secondNode.append(0);
        thirdNode.append((horCount + 1) * 4);
        thirdNode.append(4);
        fourthNode.append((horCount + 2) * 4);
        fourthNode.append(4);
        nodes[QString::number(nodeMax - 3)] = firstTrNode;
        nodes[QString::number(nodeMax - 2)] = secondNode;
        nodes[QString::number(nodeMax - 1)] = thirdNode;
        nodes[QString::number(nodeMax)] = fourthNode;

        QJsonArray wireNodes;
        wireNodes.append(prevNode);
        wireNodes.append(nodeMax - 3);
        QJsonObject wire;
        if (horCount == 0)
        {
            wire["title"] = "in";
        }
        else
        {
            wire["title"] = "";
        }
        wire["nodes"] = wireNodes;
        wires.append(wire);

        QJsonObject gnd;
        gnd["library"] = "Basic";
        gnd["model"] = "GND";
        QJsonObject gndPlacement;
        gndPlacement["rotation"] = 0;
        gnd["placement"] = gndPlacement;
        QJsonArray gndPins;
        QJsonObject gndPin;
        gndPin["P1"] = nodeMax;
        gndPins.append(gndPin);
        gnd["pins"] = gndPins;
        QJsonArray gndParameters;
        gnd["parameters"] = gndParameters = {};
        components.append(gnd);

        QJsonObject gnd2;
        gnd2["library"] = "Basic";
        gnd2["model"] = "GND";
        QJsonObject gnd2Placement;
        gnd2Placement["rotation"] = 0;
        gnd2["placement"] = gnd2Placement;
        QJsonArray gnd2Pins;
        QJsonObject gnd2Pin;
        gnd2Pin["P1"] = nodeMax - 1;
        gnd2Pins.append(gnd2Pin);
        gnd2["pins"] = gnd2Pins;
        QJsonArray gnd2Parameters = {};
        gnd2["parameters"] = gnd2Parameters;
        components.append(gnd2);
        horCount++;
    }
    else
    {
        QJsonArray secondNode;
        QJsonArray thirdNode;
        QJsonArray fourthNode;
        secondNode.append((horCount + 1) * 4);
        secondNode.append(0);
        thirdNode.append(horCount * 4);
        thirdNode.append(4);
        fourthNode.append((horCount + 1) * 4);
        fourthNode.append(4);
        nodes[QString::number(nodeMax - 2)] = secondNode;
        nodes[QString::number(nodeMax - 1)] = thirdNode;
        nodes[QString::number(nodeMax)] = fourthNode;

        QJsonObject gnd;
        gnd["library"] = "Basic";
        gnd["model"] = "GND";
        QJsonObject gndPlacement;
        gndPlacement["rotation"] = 0;
        gnd["placement"] = gndPlacement;
        QJsonArray gndPins;
        QJsonObject gndPin;
        gndPin["P1"] = nodeMax;
        gndPins.append(gndPin);
        gnd["pins"] = gndPins;
        QJsonArray gndParameters;
        gnd["parameters"] = gndParameters = {};
        components.append(gnd);

        QJsonObject gnd2;
        gnd2["library"] = "Basic";
        gnd2["model"] = "GND";
        QJsonObject gnd2Placement;
        gnd2Placement["rotation"] = 0;
        gnd2["placement"] = gnd2Placement;
        QJsonArray gnd2Pins;
        QJsonObject gnd2Pin;
        gnd2Pin["P1"] = nodeMax - 1;
        gnd2Pins.append(gnd2Pin);
        gnd2["pins"] = gnd2Pins;
        QJsonArray gnd2Parameters = {};
        gnd2["parameters"] = gnd2Parameters;
        components.append(gnd2);
    }
    horCount++;
}

/// <summary>
/// Логика добавления параллельных элементов (их узлов и проводов) в JSON.
/// </summary>
/// <param name="prevprevParallel">Предыдущий элемент параллельный/трансформатор.</param>
/// <param name="horCount">Количество горизонтальных элементов/подряд идущих параллельных/трансформаторов.</param>
/// <param name="nodeMax">Максимальный номер узла.</param>
/// <param name="prevNode">Предыдущий номер узла.</param>
/// <param name="node">Текущий номер узла.</param>
/// <param name="nodes">Узлы в JSON.</param>
/// <param name="wires">Провода в JSON.</param>
/// <param name="components">Компоненты в JSON.</param>
void CircuitElements::ParallelInJSON(bool& prevprevParallel, int& horCount, int& nodeMax, int& prevNode, int& node, QJsonObject& nodes, QJsonArray& wires, QJsonArray& components) const
{
    if (prevprevParallel)
    {
        QJsonArray wireNodes;
        wireNodes.append(prevNode);
        wireNodes.append(node);
        QJsonObject wire;
        if (horCount == 0)
        {
            wire["title"] = "in";
        }
        else
        {
            wire["title"] = "";
        }
        wire["nodes"] = wireNodes;
        wires.append(wire);
        QJsonArray secondNode;
        QJsonArray thirdNode;
        secondNode.append((horCount + 1) * 4);
        secondNode.append(0);
        thirdNode.append((horCount + 1) * 4);
        thirdNode.append(4);
        nodes[QString::number(node)] = secondNode;
        nodes[QString::number(nodeMax)] = thirdNode;
        QJsonObject gnd;
        gnd["library"] = "Basic";
        gnd["model"] = "GND";
        QJsonObject gndPlacement;
        gndPlacement["rotation"] = 0;
        gnd["placement"] = gndPlacement;
        QJsonArray gndPins;
        QJsonObject gndPin;
        gndPin["P1"] = nodeMax;
        gndPins.append(gndPin);
        gnd["pins"] = gndPins;
        QJsonArray gndParameters = {};
        gnd["parameters"] = gndParameters;
        components.append(gnd);
        horCount++;
    }
    else
    {
        QJsonArray secondNode;
        secondNode.append(horCount * 4);
        secondNode.append(4);
        nodes[QString::number(nodeMax)] = secondNode;
        QJsonObject gnd;
        gnd["library"] = "Basic";
        gnd["model"] = "GND";
        QJsonObject gndPlacement;
        gndPlacement["rotation"] = 0;
        gnd["placement"] = gndPlacement;
        QJsonArray gndPins;
        QJsonObject gndPin;
        gndPin["P1"] = nodeMax;
        gndPins.append(gndPin);
        gnd["pins"] = gndPins;
        QJsonArray gndParameters = {};
        gnd["parameters"] = gndParameters;
        components.append(gnd);
    }
}

/// <summary>
/// Сохранение в JSON.
/// </summary>
/// <param name="filePath">Путь к файлу.</param>
/// <returns>Получилось/не получилось.</returns>
bool CircuitElements::saveToJSON(const QString& filePath) const
{
    QJsonObject json = toCircuitJson();
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

/// <summary>
/// Элемент в JSON для САПР.
/// </summary>
/// <param name="element">Элемент.</param>
/// <param name="node">Текущий номер узла.</param>
/// <param name="nodeMax">Максимальный номер узла.</param>
/// <param name="prevTransform">Элемент трансформатор.</param>
/// <param name="prevParallel">Элемент параллельный/трансформатор.</param>
/// <param name="prevOSSS">Элемент шлейф.</param>
/// <returns></returns>
QJsonObject CircuitElements::elementToCircuitJson(Element* element, int& node, int& nodeMax, bool& prevTransform, bool& prevParallel, bool& prevOSSS)
{
    if (!element) {
        return QJsonObject();
    }
    return element->toCircuitJson(node, nodeMax, prevTransform, prevParallel, prevOSSS);
}