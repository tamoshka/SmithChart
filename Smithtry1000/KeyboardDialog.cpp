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
    this->setWindowTitle(QStringLiteral(u"Свободные точки"));
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
    ReBox->setTitle(QStringLiteral(u"Действительное"));
    ImBox->setTitle(QStringLiteral(u"Мнимое"));
    frequencyBox->setTitle(QStringLiteral(u"Частота"));
    Re->move(5, 20);
    Im->move(5, 20); 
    powerBox = new QComboBox(this);
    powerBox->addItem(QStringLiteral(u"Гц"));
    powerBox->addItem(QStringLiteral(u"КГц"));
    powerBox->addItem(QStringLiteral(u"МГц"));
    powerBox->addItem(QStringLiteral(u"ГГц"));
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
    impedance = new QRadioButton(QStringLiteral(u"Сопротивление"), this);
    impedance->setChecked(true);
    admittance = new QRadioButton(QStringLiteral(u"Проводимость"), this);
    reflectionCoefficient = new QRadioButton(QStringLiteral(u"Коэффициент отражения"), this);
    temp->addWidget(impedance);
    temp->addWidget(admittance);
    temp->addWidget(reflectionCoefficient);
    QVBoxLayout* temp2 = new QVBoxLayout(valuesType);
    cartesian = new QRadioButton(QStringLiteral(u"Декартовы координаты"), this);
    cartesian->setChecked(true);
    polar = new QRadioButton(QStringLiteral(u"Полярные координаты"), this);
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
            if (SystemParameters::dpIndex == 0)
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
        ReBox->setTitle(QStringLiteral(u"Магнитуда"));
        ImBox->setTitle(QStringLiteral(u"Угол (в градусах)"));
    }
    else if (rButton == cartesian)
    {
        ReBox->setTitle(QStringLiteral(u"Действительное"));
        ImBox->setTitle(QStringLiteral(u"Мнимое"));
    }
}