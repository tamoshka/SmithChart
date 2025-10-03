#include "KeyboardDialog.h"
#include "systemParameters.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

KeyboardDialog::KeyboardDialog(QWidget* parent)
    : QDialog(parent)
{
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
    frequencyLine = new QLineEdit(frequencyBox);
    valuesBox->addWidget(ReBox);
    valuesBox->addWidget(ImBox);
    Re = new QLineEdit(ReBox);
    Im = new QLineEdit(ImBox);
    ReBox->setTitle("Re"); 
    ImBox->setTitle("Im");
    frequencyBox->setTitle("frequency, MHz");
    Re->move(5, 20);
    Im->move(5, 20);
    frequencyLine->move(5, 20);
    frequencyLine->setText("1000");
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
        reject();
    }
    else
    {
        if ((!reflectionCoefficient->isChecked()&&cartesian->isChecked()&&valueRe<0) ||
            (reflectionCoefficient->isChecked() && cartesian->isChecked()&&(valueRe > 1 || valueRe < -1 || valueIm > 1 || valueIm < -1||abs(pow(valueRe,2)+pow(valueIm,2))>1)) ||
            (reflectionCoefficient->isChecked() && polar->isChecked()&&(valueRe<0||valueRe>1)) ||
            (!reflectionCoefficient->isChecked()&&polar->isChecked()&&(abs(valueIm)>90||valueRe<0)))
        {
            reject();
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
            if (dpIndex == 0)
            {
                frequency = valueFrequency;
            }
            if (polar->isChecked())
            {
                SystemParameters::val = Polar;
            }
            if (cartesian->isChecked())
            {
                SystemParameters::val = Cartesian;
            }
            frequencyList.append(valueFrequency);
            SystemParameters::frequency = valueFrequency;
            SystemParameters::Re = valueRe;
            SystemParameters::Im = valueIm;
            accept();
        }
    }
}

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