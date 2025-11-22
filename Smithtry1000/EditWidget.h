#pragma once
#include "circuitElements.h"
#include <QWidget>
QT_BEGIN_NAMESPACE
#ifndef __EAXML__
namespace Ui { class EditWidget; };
#endif
QT_END_NAMESPACE

class EditWidget : public QWidget
{
	Q_OBJECT

public:
	EditWidget(QWidget *parent = nullptr, CircuitElements* circuitElements = new CircuitElements(), Element* elem = new Element());
	~EditWidget();
	CircuitElements* circuitElements;

private:
	bool isUpdating;
	Ui::EditWidget *ui;
	Element* edited;
	void recalculateFromEr();
	void recalculateFromLambda();
	void recalculateFromElMM();
	void recalculateFromPhMM();

private slots:
	void OKButton_clicked();
	void DrawButton_clicked();
	void onErLineEditChanged(const QString& text);
	void onLLambdaLineEditChanged(const QString& text);
	void onLElMMLineEditChanged(const QString& text);
	void onLPhMMLineEditChanged(const QString& text);

protected:
	void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;
};
