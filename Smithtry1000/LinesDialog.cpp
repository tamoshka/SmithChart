#include "LinesDialog.h"
#include "systemParameters.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

/// <summary>
/// Конструктор класса LinesDialog.
/// </summary>
/// <param name="parent"></param>
LinesDialog::LinesDialog(QWidget* parent)
    : QDialog(parent)
{
    this->setWindowTitle("Line impedance");
    this->setFixedSize(150, 240);
    okButton = new QPushButton("OK", this);
    Z0Box = new QGroupBox(this);
    ErBox = new QGroupBox(this);
    AlphaBox = new QGroupBox(this);
    LambdaBox = new QGroupBox(this);
    Z0Field = new QLineEdit(Z0Box);
    ErField = new QLineEdit(ErBox);
    AlphaField = new QLineEdit(AlphaBox);
    LambdaField = new QLineEdit(LambdaBox);
    Z0Box->setTitle("Z0 Line impedance");
    ErBox->setTitle("Er");
    AlphaBox->setTitle("alpha");
    LambdaBox->setTitle("L electr. in lambda");
    Z0Field->move(0, 20);
    ErField->move(0, 20);
    AlphaField->move(0, 20);
    LambdaField->move(0, 20);
    Z0Field->setText("50");
    ErField->setText("1");
    AlphaField->setText("0");
    LambdaField->setText("0.25");
    LambdaField->setDisabled(true);
    QVBoxLayout* layout = new QVBoxLayout(this);

    layout->addWidget(Z0Box);
    layout->addWidget(ErBox);
    layout->addWidget(AlphaBox);
    layout->addWidget(LambdaBox);
    layout->addWidget(okButton);

    connect(AlphaField, &QLineEdit::textChanged, this, &LinesDialog::onChanged);
    connect(okButton, &QPushButton::clicked, this, &LinesDialog::onAccept);
}

/// <summary>
/// Принятие изменений.
/// </summary>
void LinesDialog::onAccept()
{
    QString tempZ0 = Z0Field->text();
    QString tempEr = ErField->text();
    QString tempAlpha = AlphaField->text();
    bool validateZ0 = true;
    bool validateEr = true;
    bool validateAlpha = true;
    bool validateLambda = true;
    double valueZ0 = Z0Field->text().toFloat(&validateZ0);
    double valueEr = ErField->text().toFloat(&validateEr);
    double valueAlpha = AlphaField->text().toFloat(&validateAlpha);
    if (valueAlpha == 0)
    {
        validateAlpha = false;
    }
    double valueLambda = LambdaField->text().toFloat(&validateLambda);
    if (validateZ0 && valueZ0>0 && validateEr && valueEr>0 && ((validateAlpha && validateLambda)||(!validateAlpha)))
    {
        if (validateAlpha && valueAlpha>0)
        {
            SystemParameters::alpha = valueAlpha;
            SystemParameters::lambda = valueLambda;
        }
        SystemParameters::z0line = valueZ0;
        SystemParameters::er = valueEr;
        accept();
    }
    else
    {
        SystemParameters::exc = true;
        accept();
    }
}

/// <summary>
/// Изменение активности поля lambda в зависимости от alpha.
/// </summary>
void LinesDialog::onChanged()
{
    QString tempAlpha = AlphaField->text();
    bool validateAlpha = true;
    double valueAlpha = AlphaField->text().toFloat(&validateAlpha);
    if (!validateAlpha || valueAlpha==0)
    {
        LambdaField->setDisabled(true);
    }
    else
    {
        LambdaField->setEnabled(true);
    }
}