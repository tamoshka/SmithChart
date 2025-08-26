#pragma once

#include <QWidget>
#include "ui_GrafTwo.h"
#include "S2p.h"
#include <QVector>
#include "ColourSetting.h"
QT_BEGIN_NAMESPACE
namespace Ui { class GrafTwoClass; };
QT_END_NAMESPACE

class GrafTwo : public QWidget
{
	Q_OBJECT

public:
	GrafTwo(QWidget* parent = nullptr);
	~GrafTwo();
	void Load();

public slots:
	void highlightPoint(int index);
	void updateMAGColor(const QColor& color);
	void updateMSGColor(const QColor& color);
	void updateKColor(const QColor& color);
	void updateMuColor(const QColor& color);
private:
	Ui::GrafTwoClass* ui;
	double xBegin, xEnd, yBegin, yEnd, yBeginTwo, yEndTwo;
	QVector<double> x, y1, y2, y3, y4;
private:
	QCPGraph* GraphK = nullptr;
	QCPGraph* Graphμ = nullptr;
	QCPGraph* GraphMAG = nullptr;
	QCPGraph* GraphMSG = nullptr;
};
