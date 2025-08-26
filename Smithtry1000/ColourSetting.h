#pragma once

#include <QWidget>
#include "ui_ColourSetting.h"

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

signals:
	void s11ColorChanged(const QColor& color);
	void s22ColorChanged(const QColor& color);
	void magColorChanged(const QColor& color);
	void msgColorChanged(const QColor& color);
	void kColorChanged(const QColor& color);
	void muColorChanged(const QColor& color);

private slots:
	void S11Graf();
	void S22Graf();
	void MAGGraf();
	void MSGGraf();
	void KGraf();
	void MuGraf();
private:
	Ui::ColourSettingClass *ui;
	QColor s11GrafColor;
	QColor s22GrafColor;
	QColor magGrafColor;
	QColor msgGrafColor;
	QColor kGrafColor;
	QColor muGrafColor;

	void setButtonColor(QPushButton* button, const QColor& color);
};

