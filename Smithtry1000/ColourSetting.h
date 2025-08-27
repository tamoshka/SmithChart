#pragma once

#include <QWidget>
#include "ui_ColourSetting.h"
#include "renderarea.h"
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
	void s11ColorChanged();
	void s22ColorChanged();
	void magColorChanged();
	void msgColorChanged();
	void kColorChanged();
	void muColorChanged();
	void signal();
	void signalS12S21();
	void signalDVS();

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

private:
	Ui::ColourSettingClass *ui;
	void setButtonColor(QPushButton* button, const QColor& color);
};

