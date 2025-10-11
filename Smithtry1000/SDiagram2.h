#pragma once

#include <QWidget>
#include "S2p.h"
#include "qpainter.h"
#include "qpoint.h"
#include <QColor>
#include <QVector>
#include <QPoint>
#include <QEvent>
#include "ColourSetting.h"
QT_BEGIN_NAMESPACE
namespace Ui { class SDiagram2; };
QT_END_NAMESPACE

/// <summary>
/// Класс для отображения S11 и S22 кругов.
/// </summary>
class SDiagram2 : public QWidget
{
	Q_OBJECT
protected:
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

public:
	enum ParameterType
	{
		S11,
		S22
	};

public:
	SDiagram2(ParameterType Type = S11, QWidget* parent = nullptr);
	void highlightPoint(int index);
	void Load();
	~SDiagram2();

private:
	QList<double> x, y, z, angle;
	double k, max;
	int highlightedPoint = -1;

	float r;
	QPointF center;
	QPointF compute_real(float t);
	QPointF compute_imaginary(float t);
	QPixmap m_cache;
	QColor mBackGroundColor;
	QColor mShapeColor;
	bool m_cacheValid;
	void drawStaticObjects(QPainter&);
	void generateCache();
	float defaultScale = 200;
	qreal m_scaleFactor;
	float scale = 200;
	float scaleFactor;

	//Тип параметра (S11,S22)
	ParameterType currentType;
};