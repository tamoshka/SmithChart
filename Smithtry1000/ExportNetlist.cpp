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
    int rCount = 1, lCount = 1, cCount = 1, tlCount = 1;  // Element counters
    QList <QString> lines;
    for (int i = circuit->GetCircuitElements().size() - 1; i >= 0; i--)
    {
        QString line = generateElementLineCir(circuit->GetCircuitElements()[i], nodeCounter, rCount, lCount, cCount, tlCount);
        if (!line.isEmpty()) {
            lines.append(line);
        }
    }
    netlistLines << ".SUBCKT MN " + QString::number(nodeCounter)+ " 1";
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
    netlistLines << "! -- CIRCUIT";
    netlistLines << "DIM";
    netlistLines << "   FREQ GHz";
    netlistLines << "    IND  nH";
    netlistLines << "    CAP  pF";
    netlistLines << "    RES  OH";
    netlistLines << "    LNG  MM";
    netlistLines << "   COND  /OH";
    netlistLines << "   TIME  PS";
    netlistLines << "    ANG  DEG";
    netlistLines << "    VOL  V";
    netlistLines << "    CUR  MA";
    netlistLines << "    PWR  DBM";
    netlistLines << "   TEMP  K";
    netlistLines << "";
    netlistLines << "CKT";
    int nodeCounter = 1;  // Current node (start from input)
    QList <QString> lines;
    for (int i = circuit->GetCircuitElements().size() - 1; i >= 0; i--)
    {
        QString line = generateElementLineCkt(circuit->GetCircuitElements()[i], nodeCounter);
        if (!line.isEmpty()) {
            netlistLines << line;
        }
    }
    netlistLines << "DEF2P " + QString::number(nodeCounter) + " 1 MN";
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
    int rCount = 1, lCount = 1, cCount = 1, tlCount = 1;  // Element counters
    QList <QString> lines;
    for (int i = circuit->GetCircuitElements().size() - 1; i >= 0; i--)
    {
        QString line = generateElementLineScs(circuit->GetCircuitElements()[i], nodeCounter, rCount, lCount, cCount, tlCount);
        if (!line.isEmpty()) {
            lines.append(line);
        }
    }
    netlistLines << "subckt MN " + QString::number(nodeCounter) + " 1";
    for (auto var : lines)
    {
        netlistLines << var;
    }
    netlistLines << "ends";
    //netlistLines << ".AC LIN " + QString::number(frequency / 10000) + "G " + QString::number(frequency * 5/1000) + "G 100";
    QString temp = netlistLines.join("\n");
    return temp;
}

QString ExportNetlist::generateElementLineCir(Element* element, int& nodeCounter, int& rCount, int& lCount, int& cCount, int& tlCount)
{
    const mode elMode = element->GetMode();
    const double value = element->GetValue();
    QString line;

    switch (elMode)
    {
    case ResistorShunt:
    {
        line = QString("R%1 %2 %3 %4").arg(rCount++).arg(nodeCounter).arg(nodeCounter + 1).arg(value);
        nodeCounter++;
        break;
    }
    case InductionShunt:
    {
        line = QString("L%1 %2 %3 %4n").arg(lCount++).arg(nodeCounter).arg(nodeCounter + 1).arg(value * 1e9);
        nodeCounter++;
        break;
    }
    case CapacitorShunt:
    {
        line = QString("C%1 %2 %3 %4p").arg(cCount++).arg(nodeCounter).arg(nodeCounter + 1).arg(value * 1e12);
        nodeCounter++;
        break;
    }
    case ResistorParallel:
    {
        line = QString("R%1 %2 0 %3").arg(rCount++).arg(nodeCounter).arg(value);
        break;
    }
    case InductionParallel:
    {
        line = QString("L%1 %2 0 %3n").arg(lCount++).arg(nodeCounter).arg(value * 1e9);
        break;
    }
    case CapacitorParallel:
    {
        line = QString("C%1 %2 0 %3p").arg(cCount++).arg(nodeCounter).arg(value * 1e12);
        break;
    }
    case Line:
    {
        LinesElement* elem = dynamic_cast<LinesElement*>(element);
        line = QString("T%1 %2 0 %3 0 Z0=%4 F=%5GHZ NL=%6 ").arg(tlCount++).arg(nodeCounter).arg(nodeCounter + 1)
            .arg(value).arg((double)elem->GetFrequency() / 1000).arg((double)(elem->GetLambda() * elem->GetElectricalLength() / elem->GetMechanicalLength()));
        nodeCounter++;
        break;
    }
    case OSLine:
    {
        VerticalLinesElement* elem = dynamic_cast<VerticalLinesElement*>(element);
        line = QString("T%1 %2 0 100 0 Z0=%3 F=%4GHZ NL=%5").arg(tlCount++).arg(nodeCounter)
            .arg(value).arg((double)elem->GetFrequency() / 1000).arg((double)(elem->GetLambda() * elem->GetElectricalLength() / elem->GetMechanicalLength()));
        break;
    }
    case SSLine:
    {
        VerticalLinesElement* elem = dynamic_cast<VerticalLinesElement*>(element);
        line = QString("T%1 %2 0 0 0 Z0=%3 F=%4GHZ NL=%5").arg(tlCount++).arg(nodeCounter)
            .arg(value).arg((double)elem->GetFrequency() / 1000).arg((double)(elem->GetLambda() * elem->GetElectricalLength() / elem->GetMechanicalLength()));
        break;
    }
    case Transform:
    {
        break;
    }
    default:
    {
        line = QString("* Unsupported element: %1").arg(static_cast<int>(elMode));
        break;
    }
    }

    return line;
}

QString ExportNetlist::generateElementLineCkt(Element* element, int& nodeCounter)
{
    const mode elMode = element->GetMode();
    const double value = element->GetValue();
    QString line;

    switch (elMode)
    {
    case ResistorShunt:
    {
        line = QString("RES %1 %2 R=%3").arg(nodeCounter).arg(nodeCounter + 1).arg(value);
        nodeCounter++;
        break;
    }

    case InductionShunt:
    {
        line = QString("IND %1 %2 L=%3").arg(nodeCounter).arg(nodeCounter + 1).arg(value * 1e9);
        nodeCounter++;
        break;
    }

    case CapacitorShunt:
    {
        line = QString("CAP %1 %2 C=%3").arg(nodeCounter).arg(nodeCounter + 1).arg(value * 1e12);
        nodeCounter++;
        break;
    }

    case ResistorParallel:
    {
        line = QString("RES %1 0 R=%2").arg(nodeCounter).arg(value);
        break;
    }

    case InductionParallel:
    {
        line = QString("IND %1 0 L=%2").arg(nodeCounter).arg(value * 1e9);
        break;
    }

    case CapacitorParallel:
    {
        line = QString("CAP %1 0 C=%2").arg(nodeCounter).arg(value * 1e12);
        break;
    }
    case Line:
    {
        LinesElement* elem = dynamic_cast<LinesElement*>(element);
        line = QString("TLINP %1 %2 z=%3 L=%4 K=%5 F=%6").arg(nodeCounter).arg(nodeCounter + 1).arg(value).arg((double)elem->GetElectricalLength())
            .arg((double)pow(elem->GetElectricalLength() / elem->GetMechanicalLength(), 2)).arg((double)elem->GetFrequency() / 1000);
        nodeCounter++;
        break;
    }
    //ХХ
    case OSLine:
    {
        VerticalLinesElement* elem = dynamic_cast<VerticalLinesElement*>(element);
        line = QString("TLINP %1 100 z=%2 L=%3 K=%4 F=%5").arg(nodeCounter).arg(value).arg((double)elem->GetElectricalLength())
            .arg((double)pow(elem->GetElectricalLength() / elem->GetMechanicalLength(), 2)).arg((double)elem->GetFrequency() / 1000);
        break;
    }
    //КЗ
    case SSLine:
    {
        VerticalLinesElement* elem = dynamic_cast<VerticalLinesElement*>(element);
        line = QString("TLINP %1 0 z=%2 L=%3 K=%4 F=%5").arg(nodeCounter).arg(value).arg((double)elem->GetElectricalLength())
            .arg((double)pow(elem->GetElectricalLength() / elem->GetMechanicalLength(), 2)).arg((double)elem->GetFrequency() / 1000);
        break;
    }
    case Transform:
    {
        break;
    }
    default:
    {
        line = QString("* Unsupported element: %1").arg(static_cast<int>(elMode));
        break;
    }
    }
    return line;
}

QString ExportNetlist::generateElementLineScs(Element* element, int& nodeCounter, int& rCount, int& lCount, int& cCount, int& tlCount)
{
    const mode elMode = element->GetMode();
    const double value = element->GetValue();
    QString line;

    switch (elMode)
    {
    case ResistorShunt:
    {
        line = QString("R%1  %2 %3 resistor  R=%4").arg(rCount++).arg(nodeCounter).arg(nodeCounter + 1).arg(value);
        nodeCounter++;
        break;
    }
    case InductionShunt:
    {
        line = QString("L%1  %2 %3 inductor  L=%4n").arg(lCount++).arg(nodeCounter).arg(nodeCounter + 1).arg(value * 1e9);
        nodeCounter++;
        break;
    }
    case CapacitorShunt:
    {
        line = QString("C%1  %2 %3 capacitor C=%4p").arg(cCount++).arg(nodeCounter).arg(nodeCounter + 1).arg(value * 1e12);
        nodeCounter++;
        break;
    }
    case ResistorParallel:
    {
        line = QString("R%1  %2 0 resistor  R=%3").arg(rCount++).arg(nodeCounter).arg(value);
        break;
    }
    case InductionParallel:
    {
        line = QString("L%1  %2 0 inductor  L=%3n").arg(lCount++).arg(nodeCounter).arg(value * 1e9);
        break;
    }
    case CapacitorParallel:
    {
        line = QString("C%1  %2 0 capacitor C=%3p").arg(cCount++).arg(nodeCounter).arg(value * 1e12);
        break;
    }
    case Line:
    {
        LinesElement* elem = dynamic_cast<LinesElement*>(element);
        line = QString("TL%1 %2 0 %3 0 tline z0=%4 len=%5e-3 f=0").arg(tlCount++).arg(nodeCounter).arg(nodeCounter + 1).arg(value).arg((double)(elem->GetElectricalLength() * elem->GetElectricalLength() / elem->GetMechanicalLength()));
        nodeCounter++;
        break;
    }
    case OSLine:
    {
        VerticalLinesElement* elem = dynamic_cast<VerticalLinesElement*>(element);
        line = QString("TL%1 %2 0 100 0 tline z0=%3 len=%4e-3 f=0").arg(tlCount++).arg(nodeCounter).arg(value).arg((double)(elem->GetElectricalLength() * elem->GetElectricalLength() / elem->GetMechanicalLength()));
        break;
    }
    case SSLine:
    {
        VerticalLinesElement* elem = dynamic_cast<VerticalLinesElement*>(element);
        line = QString("TL%1 %2 0 0 0 tline z0=%3 len=%4e-3 f=0").arg(tlCount++).arg(nodeCounter).arg(value).arg((double)(elem->GetElectricalLength() * elem->GetElectricalLength() / elem->GetMechanicalLength()));
        break;
    }
    case Transform:
    {
        break;
    }
    default:
    {
        line = QString("* Unsupported element: %1").arg(static_cast<int>(elMode));
        break;
    }
    }

    return line;
}

ExportNetlist::~ExportNetlist()
{
    delete ui;
}
