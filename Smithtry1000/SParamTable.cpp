#include "SParamTable.h"
#include <QFileDialog>
#include <QString>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QLabel>
#include <ui_ds/atoms/typography/typography.h>
using namespace ui::ds::atoms::typography;
using namespace ui::ds::controls::organisms::table_view;
/// <summary>
/// Конструктор класса SParamTable.
/// </summary>
/// <param name="type">Тип, STable1/STable2.</param>
/// <param name="parent"></param>
SParamTable::SParamTable(TableType type, QWidget* parent)
    : QWidget(parent),
    currentType(type)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    tableWidget = new TableView(this);
    layout->addWidget(tableWidget);
    
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

/// <summary>
/// Загрузка параметров из SnP файла.
/// </summary>
void SParamTable::Load()
{
    extern QString fileName;
    auto extension = fileName.toStdString();
    size_t last_dot = extension.find_last_of('.');
    extension = last_dot != std::string::npos ? extension.substr(last_dot + 1) : "";

    TouchstoneFile t;
    spar_t s;
    s = t.Load2P(fileName.toStdString().c_str());

    QFont paragraphSemibold = Typography::instance().getFont(TFontName::PARAGRAPH_SEMIBOLD);
    
    QFont paragraphMedium =Typography::instance().getFont(TFontName::PARAGRAPH_MEDIUM);

    if (currentType == TableType::STable2) 
    {
        if (extension == "S2P" || extension == "s2p") 
        {
            tableWidget->setMinimumSize(650, 500);
            
            QStandardItemModel* model = new QStandardItemModel(s.f.size(), 6, tableWidget);
            model->setHorizontalHeaderLabels(QStringList() << "Frequency Hz" << "MAG" << "MSG" << "K[-]" << "Mue[-]" << "S12[dB]");

            for (int i = 0; i < s.f.size(); i++) 
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
                    QStandardItem* item = new QStandardItem();
                    item->setData(o, Qt::DisplayRole);
                    item->setFont(paragraphMedium);
                    item->setTextAlignment(Qt::AlignCenter);
                    model->setItem(i, j, item);
                }
            }
            
            tableWidget->setModel(model);
            tableWidget->verticalHeader()->hide();
            tableWidget->horizontalHeader()->setFont(paragraphSemibold);
            tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
    }
    else
    {
        if (extension == "S1P" || extension == "s1p")
        {
            tableWidget->setMinimumSize(110, 500);
            
            QStandardItemModel* model = new QStandardItemModel(s.f.size(), 3, tableWidget);
            model->setHorizontalHeaderLabels(QStringList() << "Frequency Hz" << "S11 Mag" << "S11 Angle");
            
            for (int i = 0; i < s.f.size(); i++)
            {
                QVector<QString> S;
                S.push_back(QString::number(s.f[i]));
                S.push_back(QString::number(s.S[0][0][i].real()));
                S.push_back(QString::number(s.S[0][0][i].imag()));
                for (int j = 0; j < S.size(); j++)
                {
                    QVariant o(S[j]);
                    QStandardItem* item = new QStandardItem();
                    item->setData(o, Qt::DisplayRole);
                    item->setFont(paragraphMedium);
                    item->setTextAlignment(Qt::AlignCenter);
                    model->setItem(i, j, item);
                }
            }
            
            tableWidget->setModel(model);
            tableWidget->verticalHeader()->hide();
            tableWidget->horizontalHeader()->setFont(paragraphSemibold);
            tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
        else if (extension == "S2P" || extension == "s2p")
        {
            tableWidget->setMinimumSize(950, 500);
            
            QStandardItemModel* model = new QStandardItemModel(s.f.size(), 9, tableWidget);
            model->setHorizontalHeaderLabels(QStringList()
                << "Frequency Hz" << "S11 Mag" << "S11 Angle" << "S21 Mag" << "S21 Angle" << "S12 Mag" << "S12 Angle" << "S22 Mag" << "S22 Angle");
            
            for (int i = 0; i < s.f.size(); i++)
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
                    QStandardItem* item = new QStandardItem();
                    item->setData(o, Qt::DisplayRole);
                    item->setFont(paragraphMedium);
                    item->setTextAlignment(Qt::AlignCenter);
                    model->setItem(i, j, item);
                }
            }
            
            tableWidget->setModel(model);
            tableWidget->verticalHeader()->hide();
            tableWidget->horizontalHeader()->setFont(paragraphSemibold);
            tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
    }
    
    connect(tableWidget, &QTableView::clicked, [this](const QModelIndex& index) 
    {
        emit rowSelected(index.row());
        if (currentType == TableType::STable1) 
        {
            emit rowClicked(index.row());
        }
    });
}

/// <summary>
/// Деструктор класса SParamTable.
/// </summary>
SParamTable::~SParamTable()
{
}