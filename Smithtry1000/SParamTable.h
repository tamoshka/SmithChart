#pragma once

#include "S2p.h"
#include <QWidget>
#include <ui_ds/controls/organisms/table_view/table_view.h>
using namespace ui::ds::controls::organisms::table_view;
/// <summary>
/// Класс отображения таблиц S-параметров.
/// </summary>
class SParamTable : public QWidget
{
	Q_OBJECT

public:
	enum TableType
	{
		STable1,
		STable2
	};
public:
	SParamTable(TableType type, QWidget* parent = nullptr);
	void Load();
	~SParamTable();
signals:
	void rowSelected(int row);
	void rowClicked(int row);
private:
	TableType currentType;
	TableView* tableWidget;
};