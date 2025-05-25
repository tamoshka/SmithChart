#include "Tests.h"
#include <QFileDialog>
#include "newgeneral.h"
string get_extension(string path) {

    size_t last_slash = path.find_last_of("/\\");
    string filename;
    if (last_slash != string::npos) {
        filename = path.substr(last_slash + 1);
    }
    else {
        filename = path;
    }

    size_t last_dot = filename.find_last_of('.');

    if (last_dot != string::npos && last_dot != 0) {
        return filename.substr(last_dot + 1);
    }

    return "";
}

Tests::Tests(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TestsClass())
{
    ui->setupUi(this);

    TouchstoneFile t;
    spar_t s;
    s = t.Load2P(fileName.toStdString().c_str());


    ui->tableWidget->setRowCount(s.f.size());
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    if (get_extension(fileName.toStdString()) == "S1P" || get_extension(fileName.toStdString()) == "s1p")
    {
        ui->tableWidget->setMinimumSize(110, 500);
        ui->tableWidget->setColumnCount(3);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList()
            << "Frequency Hz" << "S11 Mag" << "S11 Angle");
        for (int i = 0; i < ui->tableWidget->rowCount();i++)
        {
            QVector<QString> S;
            S.push_back(QString::number(s.f[i]));
            S.push_back(QString::number(s.S[0][0][i].real()));
            S.push_back(QString::number(s.S[0][0][i].imag()));
            for (int j = 0;j < S.size();j++)
            {
                QVariant o(S[j]);
                QTableWidgetItem* tbl = new QTableWidgetItem();
                tbl->setData(Qt::DisplayRole, o);
                ui->tableWidget->setItem(i, j, tbl);
            }
        }
    }

    else if (get_extension(fileName.toStdString()) == "S2P" || get_extension(fileName.toStdString()) == "s2p")
    {
        ui->tableWidget->setMinimumSize(950, 500);
        ui->tableWidget->setColumnCount(9);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList()
            << "Frequency Hz" << "S11 Mag" << "S11 Angle" << "S21 Mag" << "S21 Angle" << "S12 Mag" << "S12 Angle" << "S22 Mag" << "S22 Angle");
        for (int i = 0; i < ui->tableWidget->rowCount();i++)
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
            for (int j = 0;j < S.size();j++)
            {
                QVariant o(S[j]);
                QTableWidgetItem* tbl = new QTableWidgetItem();
                tbl->setData(Qt::DisplayRole, o);
                ui->tableWidget->setItem(i, j, tbl);
            }
        }
    }
}


Tests::~Tests()
{
    delete ui;
}
