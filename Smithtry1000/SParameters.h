#include "Tests.h"
#include "Table.h"
#include "GrafOne.h"
#include "GrafTwo.h"
#include "S11Param.h"
#include "S22Param.h"
#include "S12Param.h"
#include "S21Param.h"
#include "newgeneral.h"
#include <QtWidgets/QApplication>

class SParameters
{
public:
	SParameters(Table&, Tests&, GrafOne&, GrafTwo&, S11Param&, S22Param&, S12Param&, S21Param&);
	void Show();
	~SParameters();
private:
	Table* table;
	Tests* tests;
	GrafOne* grafOne;
	GrafTwo* grafTwo;
	S11Param* g3;
	S22Param* g4;
	S12Param* g5;
	S21Param* g6;
};