#pragma once

#include <QWidget>
#include <QMessageBox>
#include "circuitElements.h"
#include <map>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>

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
    QWidget* gridLayoutWidget;
    QGridLayout* gridLayout;
    QTabWidget* tabWidget;
    QWidget* DVSTab;
    QGroupBox* groupBox;
    QLabel* labelImpedance;
    QPushButton* ColourImpedance;
    QSpinBox* ColorImpedanceBox;
    QLabel* labelAdmitance;
    QPushButton* ColourAdmitance;
    QSpinBox* ColorAdmitanceBox;
    QPushButton* DatapointCirclesColor;
    QSpinBox* DataPointsBox;
    QLabel* labelDP;
    QLabel* labelQ;
    QPushButton* QCirclesColor;
    QSpinBox* QCirclesSpinBox;
    QLabel* labelGain;
    QLabel* labelStability;
    QPushButton* StabilityColor;
    QSpinBox* GainBox;
    QPushButton* GainColor;
    QSpinBox* StabilityBox;
    QSpinBox* VSWRSpinBox;
    QPushButton* SweepLinesColor;
    QSpinBox* SweepLinesBox;
    QLabel* labelVSWR;
    QPushButton* VSWRCirclesColor;
    QSpinBox* NoiseBox;
    QLabel* labelGamma;
    QPushButton* NoiseColor;
    QSpinBox* MainCircleBox;
    QLabel* labelNoise;
    QPushButton* MainCircleColor;
    QLabel* labelUnfoldingLines;
    QLabel* labelMainImpedance;
    QPushButton* RefZColor;
    QSpinBox* RefZBox;
    QLabel* labelMainAdmitance;
    QPushButton* RefYColor;
    QSpinBox* RefYBox;
    QSpinBox* DataPointsLinesBox;
    QPushButton* DataPointsLinesColor;
    QPushButton* TempLinesColor;
    QLabel* labelDPLines;
    QLabel* labelTemp;
    QSpinBox* TempBox;
    QSpinBox* ElementBox;
    QPushButton* SweepCirclesColor;
    QSpinBox* SweepCirclesBox;
    QLabel* labelUnfolding;
    QPushButton* ElementLinesColor;
    QLabel* labelRoot;
    QGroupBox* groupBox_2;
    QCheckBox* checkBoxLabels;
    QCheckBox* checkBoxImpedance;
    QCheckBox* checkBoxConnectDP;
    QCheckBox* checkBoxAdmitance;
    QCheckBox* checkBoxCircles;
    QCheckBox* checkBoxDiagramLabels;
    QCheckBox* checkBoxTPLabels;
    QCheckBox* checkBoxDPLabels;
    QCheckBox* checkBoxSPLabels;
    QCheckBox* checkBoxExpanding;
    QGroupBox* groupBox_3;
    QLabel* labelZ0;
    QComboBox* z0ComboBox;
    QLineEdit* z0lineEdit;
    QGroupBox* groupBox_4;
    QLabel* labelFrequency;
    QComboBox* frequencyComboBox;
    QLineEdit* frequencyLineEdit;
    QGroupBox* groupBox_5;
    QRadioButton* generatorRadioButton;
    QGroupBox* groupBox_10;
    QGroupBox* groupBox_11;
    QRadioButton* verticalRadioButton;
    QRadioButton* horizontalRadioButton;
    QCheckBox* checkBoxAutoLabels;
    QCheckBox* checkBoxMainLabels;
    QWidget* SPlotTab;
    QGroupBox* groupBox_6;
    QLabel* labelS12;
    QLabel* labelS21;
    QPushButton* CircleS12;
    QPushButton* CircleS21;
    QLabel* labelMAG;
    QPushButton* MAGGraf;
    QLabel* labelMSG;
    QPushButton* MSGGraf;
    QLabel* labelK;
    QPushButton* KGraf;
    QLabel* labelMu;
    QPushButton* MuGraf;
    QLabel* labelS11;
    QPushButton* S11Graf;
    QLabel* labelS22;
    QPushButton* S22Graf;
    QSpinBox* S12Box;
    QSpinBox* S21Box;
    QSpinBox* MAGBox;
    QSpinBox* MSGBox;
    QSpinBox* KBox;
    QSpinBox* MuBox;
    QSpinBox* S11Box;
    QSpinBox* S22Box;
    QLabel* labelGainGrid;
    QPushButton* GridGrafTwoColor;
    QSpinBox* GainSPlotBox;
    QLabel* labelLossGrid;
    QPushButton* GridGrafOneColor;
    QSpinBox* LossBox;
    QGroupBox* groupBox_7;
    QCheckBox* checkBoxImpedanceOnOff;
    QCheckBox* checkBoxAdmitanceOnOff;
    QCheckBox* checkBoxLabelsOnOff;
    QCheckBox* checkBoxDPOnOff;
    QWidget* MainTab;
    QGroupBox* groupBox_9;
    QCheckBox* checkBoxDVS;
    QCheckBox* checkBoxSPlot;
    QWidget* AFRTab;
    QGroupBox* groupBox_8;
    QLabel* labelAFRS21;
    QLabel* labelAFRS11;
    QPushButton* AmpFrS11;
    QPushButton* AmpFrS21;
    QSpinBox* spinBoxS21;
    QSpinBox* spinBoxS11;
    QPushButton* DefaultButton;
    QPushButton* OKButton;
    QPushButton* CancelButton;
    QPushButton* HelpButton;

	void setButtonColor(QPushButton* button, const QColor& color);
	void SetupUI();
    void SetupDVS();
    void SetupSPlot();
    void SetupMain();
    void SetupAFR();
	QMap<QSpinBox*, int> sBoxIndex;
	QMap<QSpinBox*, int> sBoxDVSIndex;
	QMap<QSpinBox*, int> sBoxAmpFrIndex;
	QMap<QPushButton*, QColor*> DVScolors;
	QMap<QPushButton*, QColor*> AmpFrcolors;
	QMap<QPushButton*, QColor*> colors;
};

