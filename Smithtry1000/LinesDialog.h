#ifndef LINESDIALOG_H
#define LINESDIALOG_H

#include <QDialog>
#include <QGroupBox>

class QLineEdit;
class QPushButton;

/// <summary>
/// Диалог задания линии передач.
/// </summary>
class LinesDialog : public QDialog {
    Q_OBJECT

public:
    explicit LinesDialog(QWidget* parent = nullptr);

private slots:
    void onAccept();
    void onChanged();

private:
    QLineEdit* Z0Field;
    QLineEdit* ErField;
    QLineEdit* AlphaField;
    QLineEdit* LambdaField;
    QGroupBox* Z0Box;
    QGroupBox* ErBox;
    QGroupBox* AlphaBox;
    QGroupBox* LambdaBox;
    QPushButton* okButton;
};

#endif // LinesDIALOG