#pragma once

#include <QWidget>
#include "ui_GrafOne.h"
#include "S2p.h"
#include <QVector>
#include "ColourSetting.h"
QT_BEGIN_NAMESPACE
namespace Ui { class GrafOneClass; };
QT_END_NAMESPACE

class GrafOne : public QWidget
{
	Q_OBJECT

public:
	GrafOne(QWidget* parent = nullptr);
	~GrafOne();
	void Load();

public slots:
	void highlightPoint(int index);
	void updateGrafOneColor();

private:
	Ui::GrafOneClass* ui;
	double xBegin, xEnd, yBegin, yEnd, hY, hX;
	QVector<double> x, y1, y2;
private:
	QCPGraph* GraphS11 = nullptr;
	QCPGraph* GraphS22 = nullptr;
};
