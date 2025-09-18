#pragma once

#include <QWidget>
#include "renderarea.h"
QT_BEGIN_NAMESPACE
namespace Ui { class CirclesWidget; };
QT_END_NAMESPACE

class CirclesWidget : public QWidget
{
	Q_OBJECT

public:
	CirclesWidget(QWidget *parent = nullptr);
	~CirclesWidget();

signals:
	void circle();

private slots:
	void selectAllClickedVSWR();
	void clearAllDefinedClickedVSWR();
	void checkboxCheckedVSWR(int state);
	void okClicked();
	void cancelClicked();
	void insertVSWRClicked();
	void deleteVSWRClicked();
	void clearAllOthersClickedVSWR();
	void insertQClicked();
	void deleteQClicked();
	void clearAllOthersClickedQ();
	void selectAllClickedQ();
	void clearAllDefinedClickedQ();
	void checkboxCheckedQ(int state);

private:
	Ui::CirclesWidget *ui;
	QMap<QCheckBox*, qreal> checkBoxVSWRIndex;
	QMap<qreal, QCheckBox*> reverseCheckBoxVSWRIndex;
	QMap<QCheckBox*, qreal> checkBoxQIndex;
	QMap<qreal, QCheckBox*> reverseCheckBoxQIndex;
};