#pragma once

#include <QWidget>
#include <QPushButton>
#include "circuitElements.h"
#include "general.h"
#include "qcustomplot.h"
#include "ColourSetting.h"
#include <QSpacerItem>
#include <QGridLayout>

/// <summary>
/// Класс расчёта и отображения АЧХ.
/// </summary>
class AmplitudeFrequency : public QWidget
{
	Q_OBJECT

private:
	QVector<long double> freqs;
	QPushButton* saveButton;
	QSpacerItem* horizontalSpacer;
	QCustomPlot* widget;
	QGridLayout* gridLayout;
public slots:
	void SaveAmpFr();
public:
	CircuitElements* circuitElements;
	void Clear();
	AmplitudeFrequency(QWidget* parent = nullptr, CircuitElements* = new CircuitElements());
	void MatrixCalculation();
	void SetPoint(long double[], long double[], long double[]);
	void CalculateMatrix(Complex(&first)[2][2], Complex(&second)[2][2], QList<Element*> circuit, long double w);
	~AmplitudeFrequency();
};
