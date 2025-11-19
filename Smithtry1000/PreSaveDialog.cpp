#include "PreSaveDialog.h"
#include <QPushButton>
#include "general.h"
#include <QBoxLayout>

/// <summary>
/// Конструктор класса FrequencyDialog.
/// </summary>
/// <param name="parent"></param>
PreSaveDialog::PreSaveDialog(QWidget* parent)
    : QDialog(parent)
{
    this->setWindowTitle(QStringLiteral(u"Save project?"));
    this->setFixedSize(350, 150);
    QHBoxLayout* layout = new QHBoxLayout(this);
    okButton = new QPushButton("OK", this);
    cancelButton=new QPushButton("Cancel", this);
    layout->addWidget(okButton);
    layout->addWidget(cancelButton);
    connect(okButton, &QPushButton::clicked, this, &PreSaveDialog::onAccept);
    connect(cancelButton, &QPushButton::clicked, this, &PreSaveDialog::onReject);
}

/// <summary>
/// Принятие изменений.
/// </summary>
void PreSaveDialog::onAccept()
{
    accept();
}

void PreSaveDialog::onReject()
{
    reject();
}