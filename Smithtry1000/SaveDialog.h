#pragma once

#include <QDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class SaveDialog; };
QT_END_NAMESPACE

class SaveDialog : public QDialog
{
	Q_OBJECT

public:
	SaveDialog(QWidget *parent = nullptr);
	~SaveDialog();

private slots:
	void Save();
	void Cancel();

private:
	Ui::SaveDialog *ui;
};
