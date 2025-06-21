#include "ExportNetlist.h"
#include "ui_ExportNetlist.h"

ExportNetlist::ExportNetlist(QWidget *parent, CircuitElements* circuitElements)
	: QWidget(parent)
	, ui(new Ui::ExportNetlist())
{
	ui->setupUi(this);
	circuit = circuitElements;
}

QString ExportNetlist::generateNetlist()
{
    if (!circuit || circuit->GetCircuitElements().isEmpty()) {
        return "* Empty circuit\n.END";
    }

    QStringList netlistLines;
    netlistLines << "* SPICE netlist generated from Smith Chart Tool";
    netlistLines << "!GLOBAL";
    netlistLines << "DIM FREQ=1e6 R=1e0 L=1e-9 C=1e-12";
    netlistLines << "!";
    netlistLines << "CKT";
    int nodeCounter = 0;  // Current node (start from input)
    int rCount = 1, lCount = 1, cCount = 1;  // Element counters

    for (Element* element : circuit->GetCircuitElements()) {
        QString line = generateElementLine(element, nodeCounter, rCount, lCount, cCount);
        if (!line.isEmpty()) {
            netlistLines << line;
        }
    }
    netlistLines << "DEF2P 1 " + QString::number(nodeCounter) + " A";
    netlistLines << "!";
    // Analysis directives
    netlistLines << "FREQ";
    netlistLines << " FIXED "+QString::number(frequency);
    netlistLines << ".END";
    QString temp = netlistLines.join("\n");
    return temp;
}

QString ExportNetlist::generateElementLine(Element* element, int& nodeCounter, int& rCount, int& lCount, int& cCount)
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
        line = QString("L%1 %2 %3 %4").arg(lCount++).arg(nodeCounter).arg(nodeCounter + 1).arg(value*1e9);
        nodeCounter++;
        break;

    case CapacitorShunt:
        line = QString("C%1 %2 %3 %4").arg(cCount++).arg(nodeCounter).arg(nodeCounter + 1).arg(value*1e12);
        nodeCounter++;
        break;

        // Parallel elements
    case ResistorParallel:
        line = QString("R%1 %2 0 %3").arg(rCount++).arg(nodeCounter+1).arg(value);
        nodeCounter++;
        break;

    case InductionParallel:
        line = QString("L%1 %2 0 %3").arg(lCount++).arg(nodeCounter+1).arg(value*1e9);
        nodeCounter++;
        break;

    case CapacitorParallel:
        line = QString("C%1 %2 0 %3").arg(cCount++).arg(nodeCounter+1).arg(value*1e12);
        nodeCounter++;
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
