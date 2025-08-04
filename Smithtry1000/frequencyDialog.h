#ifndef FREQUENCYDIALOG_H
#define FREQUENCYDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;

class FrequencyDialog : public QDialog {
    Q_OBJECT

public:
    explicit FrequencyDialog(QWidget* parent = nullptr);

private slots:
    void onAccept();

private:
    QLineEdit* inputField;
    QPushButton* okButton;
};

#endif // FREQUENCYDIALOG