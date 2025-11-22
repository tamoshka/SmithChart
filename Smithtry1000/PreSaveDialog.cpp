#include "PreSaveDialog.h"
#include "general.h"
#include <QPushButton>
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
    QVBoxLayout* vert = new QVBoxLayout(this);
    QLabel* label = new QLabel(this);
    label->setText(QStringLiteral(u"Сохранить проект перед загрузкой?"));
    vert->addWidget(label);
    QGroupBox* lay = new QGroupBox(this);
    vert->addWidget(lay);
    QHBoxLayout* layout = new QHBoxLayout(lay);
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