#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <ui_ds/controls/organisms/windows/modal_window/modal_window.h>
#include <ui_ds/controls/organisms/radio_button/radio_button.h>
#include <ui_ds/controls/molecules/buttons/secondary_button.h>

using namespace ui::ds::controls::organisms::radio_button;
using namespace ui::ds::controls::organisms::modal_window;
using namespace ui::ds::controls::molecules::buttons;

class SaveDialog : public QWidget
{
    Q_OBJECT

signals:
    void finished(int result);

public:
    SaveDialog(QWidget *parent = nullptr);
    ~SaveDialog();
    void showDialog() 
	{ 
        SDialog->show(); 
        SDialog->raise();
        SDialog->activateWindow();
    }

    int result() const { return m_result; }

private slots:
    void Save();
    void Cancel();

private:
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_buttonsLayout;
    RadioButton *Circuit = nullptr;
    RadioButton *Diagram = nullptr;
    ModalWindow *SDialog = nullptr;
    SecondaryButton *SaveButton = nullptr;
    SecondaryButton *CancelButton = nullptr;
    int m_result = 0;
};