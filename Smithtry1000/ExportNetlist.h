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
	ExportNetlist(QWidget *parent = nullptr, CircuitElements* circuitElements=new CircuitElements());
	~ExportNetlist();
	QString generateNetlist();
private:
	Ui::ExportNetlist *ui;
	QString generateElementLine(Element* element, int& nodeCounter, int& rCount, int& lCount, int& cCount);
	QString getSpiceElementType(mode elementMode);
	CircuitElements* circuit;
};
