#pragma once

#include <QWidget>
#include "ui_S21Param.h"
#include "S2p.h"
#include "qpainter.h"
#include "qpoint.h"
#include "qcolor.h"
#include "QEvent.h"
QT_BEGIN_NAMESPACE
namespace Ui { class S21ParamClass; };
QT_END_NAMESPACE

class S21Param : public QWidget
{
	Q_OBJECT
protected:
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

public:
	S21Param(QWidget* parent = nullptr);
	void Load();
	void highlightPoint(int index);
	~S21Param();

private:
	QColor mBackGroundColor;
	QList<double> x, y, z, angle;
	double k, max;;
	int highlightedPoint = -1;
};

