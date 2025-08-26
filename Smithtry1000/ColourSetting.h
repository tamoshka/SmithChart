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

	QColor getS11Color() const { return s11GrafColor;}
	QColor getS22Color() const { return s22GrafColor;}
	QColor getMAGColor() const { return magGrafColor;}
	QColor getMSGColor() const { return msgGrafColor;}
	QColor getKColor() const { return kGrafColor; }
	QColor getMuColor() const { return muGrafColor;}
	QColor getAmpS11Color() const { return ampS11Color; }
	QColor getAmpS21Color() const { return ampS21Color; }
	QColor getCirclS12Color() const { return circleS12; }
	QColor getCirclS21Color() const { return circleS21; }
signals:
	void s11ColorChanged(const QColor& color);
	void s22ColorChanged(const QColor& color);
	void magColorChanged(const QColor& color);
	void msgColorChanged(const QColor& color);
	void kColorChanged(const QColor& color);
	void muColorChanged(const QColor& color);
	void signal();
	void signalS12S21();


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

private:
	Ui::ColourSettingClass *ui;
	QColor s11GrafColor;
	QColor s22GrafColor;
	QColor magGrafColor;
	QColor msgGrafColor;
	QColor kGrafColor;
	QColor muGrafColor;
	QColor ampS11Color;
	QColor ampS21Color;
	QColor circleS12;
	QColor circleS21;

	void setButtonColor(QPushButton* button, const QColor& color);
};

