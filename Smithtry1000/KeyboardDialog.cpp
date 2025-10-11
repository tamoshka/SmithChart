#include "KeyboardDialog.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

/// <summary>
/// Конструктор класса KeyboardDialog.
/// </summary>
/// <param name="parent"></param>
KeyboardDialog::KeyboardDialog(QWidget* parent, CircuitElements* circuit)
    : QDialog(parent)
{
    circuitElements = circuit;
    this->setWindowTitle("Data Point"); 
    this->setFixedSize(250, 400);
    okButton = new QPushButton("OK", this);
    chartSystem = new QGroupBox(this);
    frequencyBox = new QGroupBox(this);
    valuesType = new QGroupBox(this);
    QGroupBox* group = new QGroupBox(this);
    valuesBox = new QHBoxLayout(group);
    ReBox = new QGroupBox();
    ImBox = new QGroupBox();
    QHBoxLayout* tempfrequency = new QHBoxLayout(frequencyBox);
    frequencyLine = new QLineEdit(this);
    valuesBox->addWidget(ReBox);
    valuesBox->addWidget(ImBox);
    Re = new QLineEdit(ReBox);
    Im = new QLineEdit(ImBox);
    ReBox->setTitle("Re"); 
    ImBox->setTitle("Im");
    frequencyBox->setTitle("frequency, MHz");
    Re->move(5, 20);
    Im->move(5, 20); 
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
    frequencyLine->setText(QString::number((double)(SystemParameters::defaultFrequency / val)));
    tempfrequency->addWidget(frequencyLine);
    tempfrequency->addWidget(powerBox);
    QVBoxLayout* temp = new QVBoxLayout(chartSystem);
    impedance = new QRadioButton("impedance", this);
    impedance->setChecked(true);
    admittance = new QRadioButton("admittance", this);
    reflectionCoefficient = new QRadioButton("reflection coefficient", this);
    temp->addWidget(impedance);
    temp->addWidget(admittance);
    temp->addWidget(reflectionCoefficient);
    QVBoxLayout* temp2 = new QVBoxLayout(valuesType);
    cartesian = new QRadioButton("cartesian", this);
    cartesian->setChecked(true);
    polar = new QRadioButton("polar", this);
    temp2->addWidget(cartesian);
    temp2->addWidget(polar);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(chartSystem);
    layout->addWidget(group);
    layout->addWidget(valuesType);
    layout->addWidget(frequencyBox);
    layout->addWidget(okButton);
    connect(polar, &QRadioButton::clicked, this, &KeyboardDialog::onChanged);
    connect(cartesian, &QRadioButton::clicked, this, &KeyboardDialog::onChanged);
    connect(okButton, &QPushButton::clicked, this, &KeyboardDialog::onAccept);
}

/// <summary>
/// Принятие изменений.
/// </summary>
void KeyboardDialog::onAccept()
{
    QString tempFrequency = frequencyLine->text();
    QString tempRed = Re->text();
    QString tempIm = Im->text();
    bool validateRe = true;
    bool validateIm = true;
    bool validateFrequency = true;
    double valueRe = Re->text().toFloat(&validateRe);
    double valueIm = Im->text().toFloat(&validateIm);
    double valueFrequency = frequencyLine->text().toFloat(&validateFrequency);
    if (!validateIm || !validateRe || !validateFrequency|| validateRe<0)
    {
        SystemParameters::exc = true;
        accept();
    }
    else
    {
        if ((!reflectionCoefficient->isChecked()&&cartesian->isChecked()&&valueRe<0) ||
            (reflectionCoefficient->isChecked() && cartesian->isChecked()&&(valueRe > 1 || valueRe < -1 || valueIm > 1 || valueIm < -1||abs(pow(valueRe,2)+pow(valueIm,2))>1)) ||
            (reflectionCoefficient->isChecked() && polar->isChecked()&&(valueRe<0||valueRe>1)) ||
            (!reflectionCoefficient->isChecked()&&polar->isChecked()&&(abs(valueIm)>90||valueRe<0)))
        {
            SystemParameters::exc = true;
            accept();
        }
        else
        {
            if (impedance->isChecked())
            {
                SystemParameters::sys = Impedance;
            }
            if (admittance->isChecked())
            {
                SystemParameters::sys = Admittance;
            }
            if (reflectionCoefficient->isChecked())
            {
                SystemParameters::sys = ReflectionCoefficient;
            }
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
                SystemParameters::frequency = valueFrequency * power;
            }
            if (polar->isChecked())
            {
                SystemParameters::val = Polar;
            }
            if (cartesian->isChecked())
            {
                SystemParameters::val = Cartesian;
            }
            circuitElements->frequencyList.append(valueFrequency*power);
            SystemParameters::frequency = valueFrequency*power;
            SystemParameters::Re = valueRe;
            SystemParameters::Im = valueIm;
            accept();
        }
    }
}

/// <summary>
/// Изменение выбранной radiobutton.
/// </summary>
void KeyboardDialog::onChanged()
{
    QRadioButton* rButton = qobject_cast<QRadioButton*>(sender());
    if (rButton == polar)
    {
        ReBox->setTitle("Magnitude");
        ImBox->setTitle("Angle [degrees]");
    }
    else if (rButton == cartesian)
    {
        ReBox->setTitle("Re");
        ImBox->setTitle("Im");
    }
}