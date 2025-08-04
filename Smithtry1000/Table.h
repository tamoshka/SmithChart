#pragma once

#include "S2p.h"
#include <QWidget>
#include "ui_Table.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Table; };
QT_END_NAMESPACE

class Table : public QWidget
{
	Q_OBJECT

public:
	Table(QWidget* parent = nullptr);
	void Load();
	~Table();
signals:
	void rowSelected(int row);
private:
	Ui::Table* ui;
};
