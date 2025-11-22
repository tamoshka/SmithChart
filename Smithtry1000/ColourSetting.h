#pragma once

#include <QWidget>
#include "ui_ColourSetting.h"
#include "circuitElements.h"
#include <map>
QT_BEGIN_NAMESPACE
#ifndef __EAXML__
namespace Ui { class ColourSettingClass; };
#endif
QT_END_NAMESPACE

/// <summary>
/// Класс настройки цветов и толщины линий.
/// </summary>
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
	void allchangedsignal();
	void rev();

private slots:
	void ButtonCancel();
	void ButtonOK();

	void DVSColor();

	void AmpFrColor();

	void CircleS12S21Color();
	void GrafOneColor();
	void GrafTwoColor();

	void VerticalHorizontalChanged();

	//По sBoxIndex
	void LineCircleS12S21(int line);
	void LineGrafOne(int line);
	void LineGrafTwo(int line);
	void DVSLine(float line);
	void AmpFrLine(int line);

	void DefaultClicked();

private:
	Ui::ColourSettingClass *ui;
	void setButtonColor(QPushButton* button, const QColor& color);
	QMap<QSpinBox*, int> sBoxIndex;
	QMap<QSpinBox*, int> sBoxDVSIndex;
	QMap<QSpinBox*, int> sBoxAmpFrIndex;
	QMap<QPushButton*, QColor*> DVScolors;
	QMap<QPushButton*, QColor*> AmpFrcolors;
	QMap<QPushButton*, QColor*> colors;
};

