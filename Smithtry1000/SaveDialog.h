#pragma once

#include <QDialog>
QT_BEGIN_NAMESPACE
#ifndef __EAXML__
namespace Ui { class SaveDialog; };
#endif
QT_END_NAMESPACE

/// <summary>
/// Диалог для сохранения изображения виджета.
/// </summary>
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
