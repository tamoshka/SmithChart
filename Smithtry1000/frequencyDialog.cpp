#include "frequencyDialog.h"
#include "general.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

FrequencyDialog::FrequencyDialog(QWidget* parent)
    : QDialog(parent)
{
    inputField = new QLineEdit(this);
    okButton = new QPushButton("OK", this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(inputField);
    layout->addWidget(okButton);

    connect(okButton, &QPushButton::clicked, this, &FrequencyDialog::onAccept);
}

void FrequencyDialog::onAccept()
{
    QString temp = inputField->text();
    bool validate = true;
    float value = inputField->text().toFloat(&validate);
    if (!validate)
    {
        reject();
    }
    else
    {
        if (dpIndex == 0)
        {
            frequency = value;
        }
        frequencyList.append(value);
        accept();
    } // закрыть окно
}