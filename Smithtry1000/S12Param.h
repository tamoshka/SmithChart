#pragma once

#include <QWidget>
#include "ui_S12Param.h"
#include "S2p.h"
#include "qpainter.h"
#include "qpoint.h"
#include "qcolor.h"
#include "QEvent.h"
QT_BEGIN_NAMESPACE
namespace Ui { class S12ParamClass; };
QT_END_NAMESPACE

class S12Param : public QWidget
{
	Q_OBJECT
protected:
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;


public:
	S12Param(QWidget* parent = nullptr);
	void Load();
	void highlightPoint(int index);
	~S12Param();

private:
	QColor mBackGroundColor;
	QList<double> x, y, z, angle;
	double k, max;
	int highlightedPoint = -1;

};

