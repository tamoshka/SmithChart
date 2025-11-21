#pragma once

#include <QWidget>
#include "circuitElements.h"
#include "general.h"
#include "qcustomplot.h"
#include "ColourSetting.h"
#include "ui_AmplitudeFrequency.h"
QT_BEGIN_NAMESPACE
#ifndef __EAXML__
namespace Ui { class AmplitudeFrequency; };
#endif
QT_END_NAMESPACE

/// <summary>
/// Класс расчёта и отображения АЧХ.
/// </summary>
class AmplitudeFrequency : public QWidget
{
	Q_OBJECT

private:
	QVector<long double> freqs;
public slots:
	void SaveAmpFr();
public:
	CircuitElements* circuitElements;
	void Clear();
	AmplitudeFrequency(QWidget* parent = nullptr, CircuitElements* = new CircuitElements());
	void MatrixCalculation();
	void SetPoint(long double[], long double[], long double[]);
	~AmplitudeFrequency();
	Ui::AmplitudeFrequency *ui;
};
