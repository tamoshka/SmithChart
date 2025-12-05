#pragma once

#include "circuitElements.h"

/// <summary>
/// Класс экспорта цепи в Netlist.
/// </summary>
class ExportNetlist
{

public:
	ExportNetlist(CircuitElements* circuitElements = new CircuitElements());
	~ExportNetlist();
	QString generateNetlistCir();
	QString generateNetlistCkt();
	QString generateNetlistScs();
private:
	QString generateElementLineCir(Element* element, int& nodeCounter, int& rCount, int& lCount, int& cCount, int& tlCount);
	QString generateElementLineCkt(Element* element, int& nodeCounter);
	QString generateElementLineScs(Element* element, int& nodeCounter, int& rCount, int& lCount, int& cCount, int& tlCount, int& trCount);
	CircuitElements* circuit;
};
