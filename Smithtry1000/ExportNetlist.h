#pragma once

#include <QWidget>
#include "circuitElements.h"
QT_BEGIN_NAMESPACE
namespace Ui { class ExportNetlist; };
QT_END_NAMESPACE

class ExportNetlist : public QWidget
{
	Q_OBJECT

public:
	ExportNetlist(QWidget* parent = nullptr, CircuitElements* circuitElements = new CircuitElements());
	~ExportNetlist();
	QString generateNetlistCir();
	QString generateNetlistCkt();
	QString generateNetlistScs();
private:
	Ui::ExportNetlist* ui;
	QString generateElementLineCir(Element* element, int& nodeCounter, int& rCount, int& lCount, int& cCount, int& tlCount);
	QString generateElementLineCkt(Element* element, int& nodeCounter);
	QString generateElementLineScs(Element* element, int& nodeCounter, int& rCount, int& lCount, int& cCount, int& tlCount);
	CircuitElements* circuit;
};
