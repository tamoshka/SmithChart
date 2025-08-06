#include "ExportNetlist.h"
#include "ui_ExportNetlist.h"

ExportNetlist::ExportNetlist(QWidget* parent, CircuitElements* circuitElements)
    : QWidget(parent)
    , ui(new Ui::ExportNetlist())
{
    ui->setupUi(this);
    circuit = circuitElements;
}

QString ExportNetlist::generateNetlistCir()
{
    if (!circuit || circuit->GetCircuitElements().isEmpty()) {
        return "* Empty circuit\n.END";
    }

    QStringList netlistLines;
    netlistLines << "* spice netlist generated from Smith Chart Tool";
    netlistLines << "*";
    netlistLines << "* circuit";
    int nodeCounter = 1;  // Current node (start from input)
    int rCount = 1, lCount = 1, cCount = 1;  // Element counters
    QList <QString> lines;
    for (Element* element : circuit->GetCircuitElements()) {
        QString line = generateElementLineCir(element, nodeCounter, rCount, lCount, cCount);
        if (!line.isEmpty()) {
            lines.append(line);
        }
    }
    netlistLines << ".SUBCKT MN 1 " + QString::number(nodeCounter);
    for (auto var : lines)
    {
        netlistLines << var;
    }
    netlistLines << ".ENDS";
    //netlistLines << ".AC LIN " + QString::number(frequency / 10000) + "G " + QString::number(frequency * 5/1000) + "G 100";
    QString temp = netlistLines.join("\n");
    return temp;
}

QString ExportNetlist::generateNetlistCkt()
{
    if (!circuit || circuit->GetCircuitElements().isEmpty()) {
        return "* Empty circuit\n.END";
    }

    QStringList netlistLines;
    netlistLines << "! Touchstone netlist generated from Smith Chart Tool";
    netlistLines << "! -- GLOBAL";
    netlistLines << "DIM";
    netlistLines << "   FREQ GHz";
    netlistLines << "   IND  nH";
    netlistLines << "   CAP  pF";
    netlistLines << "   RES  OH";
    netlistLines << "";
    netlistLines << "! -- CIRCUIT";
    netlistLines << "CKT";
    int nodeCounter = 1;  // Current node (start from input)
    QList <QString> lines;
    for (Element* element : circuit->GetCircuitElements()) {
        QString line = generateElementLineCkt(element, nodeCounter);
        if (!line.isEmpty()) {
            netlistLines << line;
        }
    }
    netlistLines << "DEF2P 1 " + QString::number(nodeCounter) + " MN";
    QString temp = netlistLines.join("\n");
    return temp;
}

QString ExportNetlist::generateNetlistScs()
{
    if (!circuit || circuit->GetCircuitElements().isEmpty()) {
        return "* Empty circuit\n.END";
    }

    QStringList netlistLines;
    netlistLines << "* SPECTRE  netlist generated from Smith Chart Tool";
    netlistLines << "simulator lang=spectre";
    netlistLines << "* -- CIRCUIT";
    int nodeCounter = 1;  // Current node (start from input)
    int rCount = 1, lCount = 1, cCount = 1;  // Element counters
    QList <QString> lines;
    for (Element* element : circuit->GetCircuitElements()) {
        QString line = generateElementLineScs(element, nodeCounter, rCount, lCount, cCount);
        if (!line.isEmpty()) {
            lines.append(line);
        }
    }
    netlistLines << "subckt MN 1 " + QString::number(nodeCounter);
    for (auto var : lines)
    {
        netlistLines << var;
    }
    netlistLines << "ends";
    //netlistLines << ".AC LIN " + QString::number(frequency / 10000) + "G " + QString::number(frequency * 5/1000) + "G 100";
    QString temp = netlistLines.join("\n");
    return temp;
}

QString ExportNetlist::generateElementLineCir(Element* element, int& nodeCounter, int& rCount, int& lCount, int& cCount)
{
    const mode elMode = element->GetMode();
    const float value = element->GetValue();
    QString elementName = getSpiceElementType(elMode);
    QString line;

    switch (elMode) {
        // Series elements (shunt)
    case ResistorShunt:
        line = QString("R%1 %2 %3 %4").arg(rCount++).arg(nodeCounter).arg(nodeCounter + 1).arg(value);
        nodeCounter++;
        break;

    case InductionShunt:
        line = QString("L%1 %2 %3 %4n").arg(lCount++).arg(nodeCounter).arg(nodeCounter + 1).arg(value * 1e9);
        nodeCounter++;
        break;

    case CapacitorShunt:
        line = QString("C%1 %2 %3 %4p").arg(cCount++).arg(nodeCounter).arg(nodeCounter + 1).arg(value * 1e12);
        nodeCounter++;
        break;

        // Parallel elements
    case ResistorParallel:
        line = QString("R%1 %2 0 %3").arg(rCount++).arg(nodeCounter).arg(value);
        break;

    case InductionParallel:
        line = QString("L%1 %2 0 %3n").arg(lCount++).arg(nodeCounter).arg(value * 1e9);
        break;

    case CapacitorParallel:
        line = QString("C%1 %2 0 %3p").arg(cCount++).arg(nodeCounter).arg(value * 1e12);
        break;

    default:
        line = QString("* Unsupported element: %1").arg(static_cast<int>(elMode));
        break;
    }

    return line;
}

QString ExportNetlist::generateElementLineCkt(Element* element, int& nodeCounter)
{
    const mode elMode = element->GetMode();
    const float value = element->GetValue();
    QString elementName = getSpiceElementType(elMode);
    QString line;

    switch (elMode) {
        // Series elements (shunt)
    case ResistorShunt:
        line = QString("RES %1 %2 R=%3").arg(nodeCounter).arg(nodeCounter + 1).arg(value);
        nodeCounter++;
        break;

    case InductionShunt:
        line = QString("IND %1 %2 L=%3").arg(nodeCounter).arg(nodeCounter + 1).arg(value * 1e9);
        nodeCounter++;
        break;

    case CapacitorShunt:
        line = QString("CAP %1 %2 C=%3").arg(nodeCounter).arg(nodeCounter + 1).arg(value * 1e12);
        nodeCounter++;
        break;

        // Parallel elements
    case ResistorParallel:
        line = QString("RES %1 0 R=%2").arg(nodeCounter).arg(value);
        break;

    case InductionParallel:
        line = QString("IND %1 0 L=%2").arg(nodeCounter).arg(value * 1e9);
        break;

    case CapacitorParallel:
        line = QString("CAP %1 0 C=%2").arg(nodeCounter).arg(value * 1e12);
        break;

    default:
        line = QString("* Unsupported element: %1").arg(static_cast<int>(elMode));
        break;
    }

    return line;
}

QString ExportNetlist::generateElementLineScs(Element* element, int& nodeCounter, int& rCount, int& lCount, int& cCount)
{
    const mode elMode = element->GetMode();
    const float value = element->GetValue();
    QString elementName = getSpiceElementType(elMode);
    QString line;

    switch (elMode) {
        // Series elements (shunt)
    case ResistorShunt:
        line = QString("R%1  %2 %3 resistor  R=%4").arg(rCount++).arg(nodeCounter).arg(nodeCounter + 1).arg(value);
        nodeCounter++;
        break;

    case InductionShunt:
        line = QString("L%1  %2 %3 inductor  L=%4n").arg(lCount++).arg(nodeCounter).arg(nodeCounter + 1).arg(value * 1e9);
        nodeCounter++;
        break;

    case CapacitorShunt:
        line = QString("C%1  %2 %3 capacitor C=%4p").arg(cCount++).arg(nodeCounter).arg(nodeCounter + 1).arg(value * 1e12);
        nodeCounter++;
        break;

        // Parallel elements
    case ResistorParallel:
        line = QString("R%1  %2 0 resistor  R=%3").arg(rCount++).arg(nodeCounter).arg(value);
        break;

    case InductionParallel:
        line = QString("L%1  %2 0 inductor  L=%3n").arg(lCount++).arg(nodeCounter).arg(value * 1e9);
        break;

    case CapacitorParallel:
        line = QString("C%1  %2 0 capacitor C=%3p").arg(cCount++).arg(nodeCounter).arg(value * 1e12);
        break;

    default:
        line = QString("* Unsupported element: %1").arg(static_cast<int>(elMode));
        break;
    }

    return line;
}

QString ExportNetlist::getSpiceElementType(mode elementMode)
{
    switch (elementMode) {
    case ResistorShunt:
        return "R";
        break;
    case ResistorParallel:
        return "R";
        break;
    case CapacitorShunt:
        return "C";
        break;
    case CapacitorParallel:
        return "C";
        break;
    case InductionShunt:
        return "L";
        break;
    case InductionParallel:
        return "L";
        break;
    default: return "X";
    }
}

ExportNetlist::~ExportNetlist()
{
    delete ui;
}
