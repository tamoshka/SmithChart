#pragma once

#include <QWidget>
#include "S2p.h"
#include "qpainter.h"
#include "qpoint.h"
#include "qcolor.h"
#include <QEvent>
#include "ColourSetting.h"
QT_BEGIN_NAMESPACE
#ifndef __EAXML__
namespace Ui { class S12ParamClass; };
#endif
QT_END_NAMESPACE

/// <summary>
/// Класс отображения кругов S12 и S21.
/// </summary>
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

	//Тип параметра (S12,S21)
	ParameterType currentType;
};