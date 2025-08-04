#pragma once

#include <QWidget>
#include "S2p.h"
#include "qpainter.h"
#include "qpoint.h"
#include <QColor>
#include <QVector>
#include <QPoint>
#include "QEvent.h"
QT_BEGIN_NAMESPACE
namespace Ui { class S11Param; };
QT_END_NAMESPACE

class S11Param : public QWidget
{
	Q_OBJECT
protected:
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

public:
	S11Param(QWidget* parent = nullptr);
	void highlightPoint(int index);
	void Load();
	~S11Param();

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
};
