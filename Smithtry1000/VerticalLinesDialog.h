#ifndef VERTICALLINESDIALOG_H
#define VERTICALLINESDIALOG_H

#include <QDialog>
#include <QGroupBox>

class QLineEdit;
class QPushButton;

/// <summary>
/// Диалог задания Шлейфоф КЗ и ХХ.
/// </summary>
class VerticalLinesDialog : public QDialog {
    Q_OBJECT

public:
    explicit VerticalLinesDialog(QWidget* parent = nullptr);

private slots:
    void onAccept();

private:
    QLineEdit* Z0Field;
    QLineEdit* ErField;
    QGroupBox* Z0Box;
    QGroupBox* ErBox;
    QPushButton* okButton;
};

#endif // VerticalLinesDIALOG