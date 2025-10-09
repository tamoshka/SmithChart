#ifndef FREQUENCYDIALOG_H
#define FREQUENCYDIALOG_H

#include <QDialog>
#include <QComboBox>

class QLineEdit;
class QPushButton;

/// <summary>
/// Диалог для задания частоты точки.
/// </summary>
class FrequencyDialog : public QDialog {
    Q_OBJECT

public:
    explicit FrequencyDialog(QWidget* parent = nullptr);

private slots:
    void onAccept();

private:
    QLineEdit* inputField;
    QPushButton* okButton;
    QComboBox* powerBox;
};

#endif // FREQUENCYDIALOG