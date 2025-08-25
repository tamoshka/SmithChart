#pragma once

#include "S2p.h"
#include <QWidget>
#include "ui_SParamTable.h"
QT_BEGIN_NAMESPACE
namespace Ui { class SParamTableClass; };
QT_END_NAMESPACE

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
	Ui::SParamTableClass* ui;

	//Хранит выбор (STable1,STable2)
	TableType currentType;
};
