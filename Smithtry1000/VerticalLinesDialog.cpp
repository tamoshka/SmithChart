#include "VerticalLinesDialog.h"
#include "systemParameters.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

VerticalLinesDialog::VerticalLinesDialog(QWidget* parent)
    : QDialog(parent)
{
    this->setWindowTitle("Line impedance");
    okButton = new QPushButton("OK", this);
    Z0Box = new QGroupBox(this);
    ErBox = new QGroupBox(this);
    Z0Field = new QLineEdit(Z0Box);
    ErField = new QLineEdit(ErBox);
    Z0Box->setTitle("Z0 Line impedance");
    ErBox->setTitle("Er");
    Z0Field->setText("50");
    ErField->setText("1");
    QVBoxLayout* layout = new QVBoxLayout(this);

    layout->addWidget(Z0Box);
    layout->addWidget(ErBox);
    layout->addWidget(okButton);

    connect(okButton, &QPushButton::clicked, this, &VerticalLinesDialog::onAccept);
}

void VerticalLinesDialog::onAccept()
{
    QString tempZ0 = Z0Field->text();
    QString tempEr = ErField->text();
    bool validateZ0 = true;
    bool validateEr = true;
    double valueZ0 = Z0Field->text().toFloat(&validateZ0);
    double valueEr = ErField->text().toFloat(&validateEr);
    if (!validateZ0 || !validateEr)
    {
        reject();
    }
    else
    {
        SystemParameters::z0line = valueZ0;
        SystemParameters::er = valueEr;
        accept();
    } // закрыть окно
}