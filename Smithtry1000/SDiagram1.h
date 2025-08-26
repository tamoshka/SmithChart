#pragma once

#include <QWidget>
#include "S2p.h"
#include "qpainter.h"
#include "qpoint.h"
#include "qcolor.h"
#include "QEvent.h"
QT_BEGIN_NAMESPACE
namespace Ui { class S12ParamClass; };
QT_END_NAMESPACE

class SDiagram1 : public QWidget
{
	Q_OBJECT
protected:
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

public:
	enum ParameterType
	{
		S12,
		S21
	};

public:
	SDiagram1(ParameterType Type = S12, QWidget* parent = nullptr);
	void Load();
	void highlightPoint(int index);
	~SDiagram1();

private:
	QColor mBackGroundColor;
	QList<double> x, y, z, angle;
	double k, max;
	int highlightedPoint = -1;

	//Хранит выбор (S12,S21)
	ParameterType currentType;
};

