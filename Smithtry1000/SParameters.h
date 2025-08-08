#include "Tests.h"
#include "Table.h"
#include "GrafOne.h"
#include "GrafTwo.h"
#include "newgeneral.h"
#include <QtWidgets/QApplication>
#include "SDiagram1.h"
#include "SDiagram2.h"

class SParameters
{
public:
	SParameters(Table&, Tests&, GrafOne&, GrafTwo&,SDiagram1&, SDiagram1&, SDiagram2&, SDiagram2&);
	void Show();
	~SParameters();
private:
	Table* table;
	Tests* tests;
	GrafOne* grafOne;
	GrafTwo* grafTwo;

	SDiagram1* d1;
	SDiagram1* d2;
	SDiagram2* d3;
	SDiagram2* d4;
};