#ifndef PRESAVEDIALOG_H
#define PRESAVEDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;

/// <summary>
/// Диалог для сохранения проекта перед загрузкой.
/// </summary>
class PreSaveDialog : public QDialog {
    Q_OBJECT

public:
    explicit PreSaveDialog(QWidget* parent = nullptr);

private slots:
    void onAccept();
    void onReject();

private:
    QPushButton* okButton;
    QPushButton* cancelButton;
};

#endif // PRESAVEDIALOG