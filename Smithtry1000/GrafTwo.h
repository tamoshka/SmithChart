#pragma once

#include <QWidget>
#include "ui_GrafTwo.h"
#include "S2p.h"
#include <QVector>
QT_BEGIN_NAMESPACE
namespace Ui { class GrafTwoClass; };
QT_END_NAMESPACE

class GrafTwo : public QWidget
{
	Q_OBJECT

public:
	GrafTwo(QWidget *parent = nullptr);
	~GrafTwo();

private:
	Ui::GrafTwoClass *ui;
	double xBegin, xEnd, yBegin, yEnd, yBeginTwo, yEndTwo;
	QVector<double> x, y1, y2,y3,y4;
};
