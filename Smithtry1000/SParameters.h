#include "GrafOne.h"
#include "GrafTwo.h"
#include "newgeneral.h"
#include <QtWidgets/QApplication>
#include "SDiagram1.h"
#include "SDiagram2.h"
#include "SParamTable.h"

class SParameters
{
public:
	SParameters(GrafOne&, GrafTwo&,SDiagram1&, SDiagram1&, SDiagram2&, SDiagram2&, SParamTable&, SParamTable&);
	void Show();
	~SParameters();
private:
	GrafOne* grafOne;
	GrafTwo* grafTwo;

	SDiagram1* d1;
	SDiagram1* d2;
	SDiagram2* d3;
	SDiagram2* d4;

	SParamTable* stable1;
	SParamTable* stable2;
};