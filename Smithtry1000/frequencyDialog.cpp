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
FrequencyDialog::FrequencyDialog(QWidget* parent)
    : QDialog(parent)
{
    this->setWindowTitle("Frequency, MHz");
    this->setFixedSize(300, 150);
    inputField = new QLineEdit(this);
    inputField->setText("500");
    okButton = new QPushButton("OK", this);
    powerBox = new QComboBox(this);
    powerBox->addItem("Hz");
    powerBox->addItem("KHz");
    powerBox->addItem("MHz");
    powerBox->addItem("GHz");
    powerBox->setCurrentIndex(2);
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
        reject();
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
            frequency = value*power;
        }
        frequencyList.append(value*power);
        accept();
    }
}