#include "SParamTable.h"
#include <QFileDialog>
#include <QString>
#include <qtablewidget.h>

/// <summary>
/// Конструктор класса SParamTable.
/// </summary>
/// <param name="type">Тип, STable1/STable2.</param>
/// <param name="parent"></param>
SParamTable::SParamTable(TableType type, QWidget* parent)
    : QWidget(parent),
    currentType(type)
    , ui(new Ui::SParamTableClass())
{
    ui->setupUi(this);
}

/// <summary>
/// Загрузка параметров из SnP файла.
/// </summary>
void SParamTable::Load()
{
    extern QString fileName;
    auto extension = fileName.toStdString();
    size_t last_dot = extension.find_last_of('.');
    extension = last_dot != string::npos ? extension.substr(last_dot + 1) : "";

    TouchstoneFile t;
    spar_t s;
    s = t.Load2P(fileName.toStdString().c_str());

    ui->tableWidget->setRowCount(s.f.size());
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    if (currentType == TableType::STable2) 
    {
        if (extension == "S2P" || extension == "s2p") 
        {
            ui->tableWidget->setMinimumSize(650, 500);
            ui->tableWidget->setColumnCount(6);
            ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Frequency Hz" << "MAG" << "MSG" << "K[-]" << "Mue[-]" << "S12[dB]");

            for (int i = 0; i < ui->tableWidget->rowCount(); i++) 
            {
                QVector<QString> S;
                S.push_back(QString::number(s.f[i]));
                S.push_back(QString::number(s.Mg[i]));
                S.push_back(QString::number(s.Ms[i]));
                S.push_back(QString::number(s.Mk[i]));
                S.push_back(QString::number(s.Mu[i]));
                S.push_back(QString::number(s.S12[i]));
                for (int j = 0; j < S.size(); j++)
                {
                    QVariant o(S[j]);
                    QTableWidgetItem* tbl = new QTableWidgetItem();
                    tbl->setData(Qt::DisplayRole, o);
                    ui->tableWidget->setItem(i, j, tbl);
                }
            }
        }
    }

    else
    {
        if (extension == "S1P" || extension == "s1p")
        {
            ui->tableWidget->setMinimumSize(110, 500);
            ui->tableWidget->setColumnCount(3);
            ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Frequency Hz" << "S11 Mag" << "S11 Angle");
            for (int i = 0; i < ui->tableWidget->rowCount(); i++)
            {
                QVector<QString> S;
                S.push_back(QString::number(s.f[i]));
                S.push_back(QString::number(s.S[0][0][i].real()));
                S.push_back(QString::number(s.S[0][0][i].imag()));
                for (int j = 0; j < S.size(); j++)
                {
                    QVariant o(S[j]);
                    QTableWidgetItem* tbl = new QTableWidgetItem();
                    tbl->setData(Qt::DisplayRole, o);
                    ui->tableWidget->setItem(i, j, tbl);
                }
            }
        }

        else if (extension == "S2P" || extension == "s2p")
        {
            ui->tableWidget->setMinimumSize(950, 500);
            ui->tableWidget->setColumnCount(9);
            ui->tableWidget->setHorizontalHeaderLabels(QStringList()
                << "Frequency Hz" << "S11 Mag" << "S11 Angle" << "S21 Mag" << "S21 Angle" << "S12 Mag" << "S12 Angle" << "S22 Mag" << "S22 Angle");
            for (int i = 0; i < ui->tableWidget->rowCount(); i++)
            {
                QVector<QString> S;
                S.push_back(QString::number(s.f[i]));
                S.push_back(QString::number(s.S[0][0][i].real()));
                S.push_back(QString::number(s.S[0][0][i].imag()));
                S.push_back(QString::number(s.S[1][0][i].real()));
                S.push_back(QString::number(s.S[1][0][i].imag()));
                S.push_back(QString::number(s.S[0][1][i].real()));
                S.push_back(QString::number(s.S[0][1][i].imag()));
                S.push_back(QString::number(s.S[1][1][i].real()));
                S.push_back(QString::number(s.S[1][1][i].imag()));
                for (int j = 0; j < S.size(); j++)
                {
                    QVariant o(S[j]);
                    QTableWidgetItem* tbl = new QTableWidgetItem();
                    tbl->setData(Qt::DisplayRole, o);
                    ui->tableWidget->setItem(i, j, tbl);
                }
            }
        }
    }
    connect(ui->tableWidget, &QTableWidget::itemClicked, [this](QTableWidgetItem* item) 
    {
            emit rowSelected(item->row());
        if (currentType == TableType::STable1) 
        {
            emit rowClicked(item->row());
        }
    });
}

/// <summary>
/// Деструктор класса SParamTable.
/// </summary>
SParamTable::~SParamTable()
{
    delete ui;
}