#include "SaveDialog.h"
#include "systemParameters.h"

SaveDialog::SaveDialog(QWidget *parent)
    : QWidget(parent)
{
    SDialog = new ModalWindow("SaveDialog", parent);
    SDialog->setMinimumSize(250, 200);
    
    m_mainLayout = new QVBoxLayout(SDialog);
    m_mainLayout->setContentsMargins(20, 20, 20, 20);
    m_mainLayout->setSpacing(10);

    Circuit = new RadioButton("Circuit", SDialog);
    Diagram = new RadioButton("Diagram", SDialog);
    
    m_mainLayout->addWidget(Circuit);
    m_mainLayout->addSpacing(15);
    m_mainLayout->addWidget(Diagram);
    m_mainLayout->addSpacing(15);

    m_buttonsLayout = new QHBoxLayout();
    m_buttonsLayout->setSpacing(10);

    SaveButton = new SecondaryButton("Save", SDialog);
    CancelButton = new SecondaryButton("Cancel", SDialog);

    m_buttonsLayout->addWidget(SaveButton);
    m_buttonsLayout->addStretch();
    m_buttonsLayout->addWidget(CancelButton);

    m_mainLayout->addLayout(m_buttonsLayout);
    m_mainLayout->addSpacing(15);

    SDialog->setLayout(m_mainLayout);

    SDialog->setFixedSize(250, 200);
    Circuit->setChecked(true);

    connect(SaveButton, &SecondaryButton::clicked, this, &SaveDialog::Save);
    connect(CancelButton, &SecondaryButton::clicked, this, &SaveDialog::Cancel);
    
    this->setVisible(false);
}

SaveDialog::~SaveDialog()
{
}

void SaveDialog::Save()
{
    if (Circuit->isChecked()) 
	{
        SystemParameters::saved = 0;
    } else if (Diagram->isChecked()) 
	{
        SystemParameters::saved = 1;
    }
    m_result = QDialog::Accepted;
    SDialog->accept();
    emit finished(m_result);
    SDialog->hide();
}

void SaveDialog::Cancel()
{
    m_result = QDialog::Rejected;
    SDialog->reject();
    emit finished(m_result);
    SDialog->hide();
}