#pragma once
#include "circuitElements.h"
#include <QWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QComboBox>

class EditWidget : public QWidget
{
	Q_OBJECT

public:
	EditWidget(QWidget *parent = nullptr, CircuitElements* circuitElements = new CircuitElements(), Element* elem = new Element());
	~EditWidget();
	CircuitElements* circuitElements;

private:
    QGroupBox* groupBox;
    QGroupBox* groupBox_2;
    QLineEdit* RLineEdit;
    QComboBox* RComboBox;
    QGroupBox* groupBox_3;
    QComboBox* LComboBox;
    QLineEdit* LLineEdit;
    QGroupBox* groupBox_4;
    QLineEdit* CLineEdit;
    QComboBox* CComboBox;
    QGroupBox* groupBox_5;
    QLineEdit* NLineEdit;
    QGroupBox* groupBox_6;
    QLineEdit* Z0LineEdit;
    QLabel* label;
    QGroupBox* groupBox_7;
    QLineEdit* ErLineEdit;
    QGroupBox* groupBox_8;
    QLineEdit* LPhMMLineEdit;
    QLabel* label_4;
    QLabel* LPhMMLabel;
    QGroupBox* groupBox_9;
    QLineEdit* AlphaLineEdit;
    QGroupBox* groupBox_10;
    QLineEdit* LLambdaLineEdit;
    QLabel* label_2;
    QLabel* LLambdaLabel;
    QGroupBox* groupBox_11;
    QLineEdit* LElMMLineEdit;
    QLabel* label_3;
    QLabel* LElMMLabel;
    QPushButton* DrawButton;
    QPushButton* OKButton;
	bool isUpdating;
	Element* edited;
	void recalculateFromEr();
	void recalculateFromLambda();
	void recalculateFromElMM();
	void recalculateFromPhMM();
	void AddResistor(bool&);
	void AddInduction(bool&);
	void AddCapacitor(bool&);
	void AddLines(bool&);
	void AddTransform(bool&);
	void SetupUI();

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
