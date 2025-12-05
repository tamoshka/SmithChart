#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include "qcustomplot.h"
#include "S2p.h"
#include <QVector>
#include "ColourSetting.h"

/// <summary>
/// Класс для отображения графика S11/S22.
/// </summary>
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
	void SaveGrafOne();
private:
    QCustomPlot* plotWidget = nullptr;
    QPushButton* saveButton = nullptr;
    QVBoxLayout* mainLayout = nullptr;

    double xBegin, xEnd, yBegin, yEnd, hY, hX;
    QVector<double> x, y1, y2;
private:
	QCPGraph* GraphS11 = nullptr;
	QCPGraph* GraphS22 = nullptr;
	void setupUI();
};
