#include "GrafOne.h"
#include "GrafTwo.h"
#include <QtWidgets/QApplication>
#include "SDiagram1.h"
#include "SDiagram2.h"
#include "SParamTable.h"
#include "ColourSetting.h"

/// <summary>
/// Хаб для окон связанных с S-параметрами и окна настройки визуализации.
/// </summary>
class SParameters
{
public:
	SParameters(GrafOne&, GrafTwo&,SDiagram1&, SDiagram1&, SDiagram2&, SDiagram2&, SParamTable&, SParamTable&, ColourSetting&);
	void Show();
	void Close();
	~SParameters();
	ColourSetting* set;
	SDiagram1* d1;
	SDiagram1* d2;
	SDiagram2* d3;
	SDiagram2* d4;

private:
	GrafOne* grafOne;
	GrafTwo* grafTwo;

	SParamTable* stable1;
	SParamTable* stable2;
};