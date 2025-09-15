#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QRadioButton>
#include <QHBoxLayout>

class QLineEdit;
class QPushButton;

class KeyboardDialog : public QDialog {
    Q_OBJECT

public:
    explicit KeyboardDialog(QWidget* parent = nullptr);

private slots:
    void onAccept();

private:
    QLineEdit* frequencyLine;
    QLineEdit* Re;
    QLineEdit* Im;
    QRadioButton* impedance;
    QRadioButton* admittance;
    QRadioButton* reflectionCoefficient;
    QGroupBox* chartSystem;
    QGroupBox* frequencyBox;
    QHBoxLayout* valuesBox;
    QGroupBox* ReBox;
    QGroupBox* ImBox;
    QPushButton* okButton;
};

#endif // KeyboardDIALOG