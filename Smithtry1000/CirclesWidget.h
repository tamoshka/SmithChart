#pragma once

#include <QWidget>
#include "renderarea.h"
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>

/// <summary>
/// Класс выбора и отображения вспомогательных кругов.
/// </summary>
class CirclesWidget : public QWidget
{
	Q_OBJECT

public:
	CirclesWidget(QWidget* parent = nullptr, CircuitElements* circuit = nullptr);
	~CirclesWidget();
	CircuitElements* circuitElements;

signals:
	void circle();

private slots:
	void selectAllClickedVSWR();
	void clearAllDefinedClickedVSWR();
	void checkboxCheckedVSWR(int state);
	void okClicked();
	void cancelClicked();
	void insertVSWRClicked();
	void deleteVSWRClicked();
	void clearAllOthersClickedVSWR();
	void insertQClicked();
	void deleteQClicked();
	void clearAllOthersClickedQ();
	void selectAllClickedQ();
	void clearAllDefinedClickedQ();
	void checkboxCheckedQ(int state);

public slots:
	void Load();

private:
    QVBoxLayout* verticalLayout;
    QTabWidget* tabWidget;
    QWidget* QTab;
    QGroupBox* groupBox_4;
    QPushButton* InsertButtonQ;
    QPushButton* DeleteButtonQ;
    QPushButton* ClearAllOtherButtonQ;
    QListWidget* listWidgetQ;
    QLineEdit* FieldQ;
    QGroupBox* groupBox_5;
    QCheckBox* checkBox10Q;
    QCheckBox* checkBox5Q;
    QCheckBox* checkBox2Q;
    QCheckBox* checkBox1Q;
    QCheckBox* checkBox0point5Q;
    QCheckBox* checkBox0point2Q;
    QPushButton* SelectAllButtonQ;
    QPushButton* ClearAllDefinedButtonQ;
    QWidget* GainTab;
    QWidget* VSWRTab;
    QGroupBox* groupBox_2;
    QCheckBox* checkBox10VSWR;
    QCheckBox* checkBox5VSWR;
    QCheckBox* checkBox3VSWR;
    QCheckBox* checkBox2VSWR;
    QCheckBox* checkBox1point5VSWR;
    QCheckBox* checkBox1point2VSWR;
    QPushButton* SelectAllButtonVSWR;
    QPushButton* ClearAllDefinedButtonVSWR;
    QGroupBox* groupBox_3;
    QPushButton* InsertButtonVSWR;
    QPushButton* DeleteButtonVSWR;
    QPushButton* ClearAllOtherButtonVSWR;
    QListWidget* listWidgetVSWR;
    QLineEdit* FieldVSWR;
    QWidget* StabilityTab;
    QWidget* NoiseTab;
    QGroupBox* groupBox;
    QHBoxLayout* horizontalLayout;
    QPushButton* OkButton;
    QPushButton* CancelButton;

	QMap<QCheckBox*, qreal> checkBoxVSWRIndex;
	QMap<qreal, QCheckBox*> reverseCheckBoxVSWRIndex;
	QMap<QCheckBox*, qreal> checkBoxQIndex;
	QMap<qreal, QCheckBox*> reverseCheckBoxQIndex;
	void addVSWR(double);
	void addQ(double);
	void clearOnLoad();
	void SetupUI();
};