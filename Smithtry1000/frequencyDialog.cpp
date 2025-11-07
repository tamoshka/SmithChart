#include "frequencyDialog.h"
#include "general.h"
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QMessageBox>

/// <summary>
/// Конструктор класса FrequencyDialog.
/// </summary>
/// <param name="parent"></param>
FrequencyDialog::FrequencyDialog(QWidget* parent, CircuitElements* circuit)
    : QDialog(parent)
{
    circuitElements = circuit;
    this->setWindowTitle("Frequency");
    this->setFixedSize(300, 150);
    inputField = new QLineEdit(this);

    powerBox = new QComboBox(this);
    powerBox->addItem("Hz");
    powerBox->addItem("KHz");
    powerBox->addItem("MHz");
    powerBox->addItem("GHz");
    powerBox->setCurrentIndex(0);
    long double val = 1;
    if (SystemParameters::defaultFrequency > 1e9)
    {
        val = 1e9;
        powerBox->setCurrentIndex(3);
    }
    else if (SystemParameters::defaultFrequency > 1e6)
    {
        val = 1e6;
        powerBox->setCurrentIndex(2);
    }
    else if (SystemParameters::defaultFrequency > 1e3)
    {
        val = 1e3;
        powerBox->setCurrentIndex(1);
    }
    inputField->setText(QString::number((double)(SystemParameters::defaultFrequency / val)));
    okButton = new QPushButton("OK", this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    QGroupBox* tempBox = new QGroupBox(this);
    QHBoxLayout* temp = new QHBoxLayout(tempBox);
    temp->addWidget(inputField);
    temp->addWidget(powerBox);
    layout->addWidget(tempBox);
    layout->addWidget(okButton);

    connect(okButton, &QPushButton::clicked, this, &FrequencyDialog::onAccept);
}

/// <summary>
/// Принятие изменений.
/// </summary>
void FrequencyDialog::onAccept()
{
    QString temp = inputField->text();
    bool validate = true;
    double value = inputField->text().toFloat(&validate);
    if (!validate || value<=0)
    {
        SystemParameters::exc = true;
        accept();
    }
    else
    {
        double power = 1;
        if (powerBox->currentIndex() == 1)
        {
            power = 1000;
        }
        else if (powerBox->currentIndex() == 2)
        {
            power = 1000000;
        }
        else if (powerBox->currentIndex() == 3)
        {
            power = 1000000000;
        }
        if (dpIndex == 0)
        {
            SystemParameters::frequency = value*power;
        }
        circuitElements->frequencyList.append(value * power);
        accept();
    }
}