#include "VerticalLinesDialog.h"
#include "systemParameters.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

/// <summary>
/// Конструктор класса VerticalLinesDialog.
/// </summary>
/// <param name="parent"></param>
VerticalLinesDialog::VerticalLinesDialog(QWidget* parent)
    : QDialog(parent)
{
    this->setWindowTitle(QStringLiteral(u"Шлейф"));
    this->setFixedSize(250, 180);
    okButton = new QPushButton("OK", this);
    Z0Box = new QGroupBox(this);
    ErBox = new QGroupBox(this);
    Z0Field = new QLineEdit(Z0Box);
    ErField = new QLineEdit(ErBox);
    Z0Box->setTitle(QStringLiteral(u"Волн. сопр."));
    ErBox->setTitle(QStringLiteral(u"Эл. проницаемость"));
    Z0Field->move(0, 20);
    ErField->move(0, 20);
    Z0Field->setText("50");
    ErField->setText("1");
    QVBoxLayout* layout = new QVBoxLayout(this);

    layout->addWidget(Z0Box);
    layout->addWidget(ErBox);
    layout->addWidget(okButton);

    connect(okButton, &QPushButton::clicked, this, &VerticalLinesDialog::onAccept);
}

/// <summary>
/// Принятие изменений.
/// </summary>
void VerticalLinesDialog::onAccept()
{
    QString tempZ0 = Z0Field->text();
    QString tempEr = ErField->text();
    bool validateZ0 = true;
    bool validateEr = true;
    double valueZ0 = Z0Field->text().toFloat(&validateZ0);
    double valueEr = ErField->text().toFloat(&validateEr);
    if (!validateZ0 || !validateEr || valueZ0<=0 || valueEr<=0)
    {
        SystemParameters::exc = true;
        accept();
    }
    else
    {
        SystemParameters::z0line = valueZ0;
        SystemParameters::er = valueEr;
        accept();
    }
}