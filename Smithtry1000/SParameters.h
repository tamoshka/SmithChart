#include "Tests.h"
#include "Table.h"
#include "GrafOne.h"
#include "GrafTwo.h"

class SParameters
{
public:
	SParameters();
	~SParameters();
private:
	Table* table;
	Tests* tests;
	GrafOne* grafOne;
	GrafTwo* grafTwo;
};