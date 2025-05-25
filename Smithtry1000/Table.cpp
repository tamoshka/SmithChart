#include "Table.h"
#include <QFileDialog>
#include "newgeneral.h"
string get_extension2(string path) {

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

Table::Table(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::Table())
{
	ui->setupUi(this);

    fileName = QFileDialog::getOpenFileName(this, tr("Open S-Parameter File"), "", tr("S2P Files (*.s2p;*.s1p);;All Files (*)"));
    TouchstoneFile t;
    spar_t s;
    s = t.Load2P(fileName.toStdString().c_str());

    ui->tableWidget->setRowCount(s.f.size());
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    if (get_extension2(fileName.toStdString()) == "S1P" || get_extension2(fileName.toStdString()) == "s1p")
    {
        ui->tableWidget->setMinimumSize(110, 500);
        ui->tableWidget->setColumnCount(1);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList()
            << "Frequency Hz");
        for (int i = 0; i < ui->tableWidget->rowCount();i++)
        {
            QVector<QString> K;
            K.push_back(QString::number(s.f[i]));
            for (int j = 0;j < K.size();j++)
            {
                QVariant o(K[j]);
                QTableWidgetItem* tbl = new QTableWidgetItem();
                tbl->setData(Qt::DisplayRole, o);
                ui->tableWidget->setItem(i, j, tbl);
            }
        }

    }

    else if(get_extension2(fileName.toStdString()) == "S2P" || get_extension2(fileName.toStdString()) == "s2p")
    {
        ui->tableWidget->setMinimumSize(650, 500);
        ui->tableWidget->setColumnCount(6);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList()
            << "Frequency Hz" << "MAG" << "MSG" << "K[-]" << "Mue[-]" << "S12[dB]");
        
        for (int i = 0; i < ui->tableWidget->rowCount();i++)
        {
            QVector<QString> K;
            K.push_back(QString::number(s.f[i]));
            K.push_back(QString::number(s.Mg[i]));
            K.push_back(QString::number(s.Ms[i]));
            K.push_back(QString::number(s.Mk[i]));
            K.push_back(QString::number(s.Mu[i]));
            K.push_back(QString::number(s.S12[i]));

            for (int j = 0;j < K.size();j++)
            {
                QVariant o(K[j]);
                QTableWidgetItem* tbl = new QTableWidgetItem();
                tbl->setData(Qt::DisplayRole, o);
                ui->tableWidget->setItem(i, j, tbl);
            }
        }
    }

}

Table::~Table()
{
	delete ui;
}
