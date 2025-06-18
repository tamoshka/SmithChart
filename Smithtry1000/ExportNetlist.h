#pragma once

#include <QWidget>
//#include "ExportNetlist.ui"
#include "general.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ExportNetlist; };
QT_END_NAMESPACE

class ExportNetlist : public QWidget
{
	Q_OBJECT

public:
	/*ExportNetlist(QWidget* parent = nullptr);
	~ExportNetlist();*/

private:
	Ui::ExportNetlist *ui;
};
