#ifndef FREQUENCYDIALOG_H
#define FREQUENCYDIALOG_H

#include <QDialog>
#include <QComboBox>
#include "circuitElements.h"

class QLineEdit;
class QPushButton;

/// <summary>
/// Диалог для задания частоты точки.
/// </summary>
class FrequencyDialog : public QDialog {
    Q_OBJECT

public:
    explicit FrequencyDialog(QWidget* parent = nullptr, CircuitElements* circuitElements = nullptr);

private slots:
    void onAccept();

private:
    CircuitElements* circuitElements;
    QLineEdit* inputField;
    QPushButton* okButton;
    QComboBox* powerBox;
};

#endif // FREQUENCYDIALOG