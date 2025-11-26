#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QComboBox>
#include "circuitElements.h"
class QLineEdit;
class QPushButton;

/// <summary>
/// Диалог задания точки с использованием клавиатуры.
/// </summary>
class KeyboardDialog : public QDialog {
    Q_OBJECT

public:
    explicit KeyboardDialog(QWidget* parent = nullptr, CircuitElements* circuit = nullptr);

private slots:
    void onAccept();
    void onChanged();

private:
    CircuitElements* circuitElements;
    QLineEdit* frequencyLine;
    QLineEdit* Re;
    QLineEdit* Im;
    QRadioButton* impedance;
    QRadioButton* admittance;
    QRadioButton* reflectionCoefficient;
    QRadioButton* polar;
    QRadioButton* cartesian;
    QGroupBox* chartSystem;
    QGroupBox* frequencyBox;
    QGroupBox* valuesType;
    QHBoxLayout* valuesBox;
    QGroupBox* ReBox;
    QGroupBox* ImBox;
    QPushButton* okButton;
    QComboBox* powerBox;
};

#endif // KeyboardDIALOG