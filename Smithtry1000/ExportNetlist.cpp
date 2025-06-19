#include "ExportNetlist.h"
#include "ui_ExportNetlist.h"

ExportNetlist::ExportNetlist(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::ExportNetlist())
{
	ui->setupUi(this);
}

ExportNetlist::~ExportNetlist()
{
	delete ui;
}
