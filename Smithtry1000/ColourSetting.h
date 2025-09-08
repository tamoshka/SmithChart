﻿#pragma once

#include <QWidget>
#include "ui_ColourSetting.h"
#include "renderarea.h"
#include <map>
QT_BEGIN_NAMESPACE
namespace Ui { class ColourSettingClass; };
QT_END_NAMESPACE

class ColourSetting : public QWidget
{
	Q_OBJECT

public:
	ColourSetting(QWidget *parent = nullptr);
	~ColourSetting();
signals:
	void signal();
	void signalS12S21();
	void signalDVS();
	void grafOneColor();
	void grafTwoColor();
private slots:
	void S11Graf();
	void S22Graf();
	void MAGGraf();
	void MSGGraf();
	void KGraf();
	void MuGraf();
	void AmpFrS11();
	void AmpFrS21();
	void CircleS12();
	void CircleS21();
	void ColourImpedance();
	void ColourAdmitance();
	void ButtonCancel();
	void ButtonOK();
	void GridGrafOneColor();
	void GridGrafTwoColor();
	void DatapointCirclesColor();
	void TempLinesColor();
	void ElementLinesColor();
	void LineCircleS12S21(int line);
	void LineGrafOne(int line);
	void LineGrafTwo(int line);
private:
	Ui::ColourSettingClass *ui;
	void setButtonColor(QPushButton* button, const QColor& color);
	QMap<QSpinBox*, int> sBoxIndex;
};

