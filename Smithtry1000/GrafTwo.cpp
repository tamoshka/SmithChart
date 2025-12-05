#include "GrafTwo.h"
#include <QMessageBox>
#include <QtMath>
#include <QThread>
#include <cmath>
#include <exception>
#include <QString>
#include "S2p.h"
#include "ColourSetting.h"

/// <summary>
/// Конструктор класса GrafTwo.
/// </summary>
/// <param name="parent"></param>
GrafTwo::GrafTwo(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
}

/// <summary>
/// Инициализация пользовательского интерфейса.
/// </summary>
void GrafTwo::setupUI()
{
    mainLayout = new QVBoxLayout(this);
    saveButton = new QPushButton("Save", this);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addStretch();
    
    plotWidget = new QCustomPlot(this);

    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(plotWidget);

    connect(saveButton, &QPushButton::clicked, this, &GrafTwo::SaveGrafTwo);
    setLayout(mainLayout);
}

/// <summary>
/// Загрузка параметров из SnP файла.
/// </summary>
void GrafTwo::Load()
{
    extern QString fileName;
    if (fileName.isEmpty()) return;
    
    auto extension = fileName.toStdString();
    size_t last_dot = extension.find_last_of('.');
    extension = last_dot != std::string::npos ? extension.substr(last_dot + 1) : "";
    
    TouchstoneFile t;
    spar_t s;
    s = t.Load2P(fileName.toStdString().c_str());
    plotWidget->clearGraphs();
    
    x = QVector<double>(s.f.begin(), s.f.end());
    y1 = QVector<double>(s.Mg.begin(), s.Mg.end());
    y2 = QVector<double>(s.Ms.begin(), s.Ms.end());
    y3 = QVector<double>(s.Mk.begin(), s.Mk.end());
    y4 = QVector<double>(s.Mu.begin(), s.Mu.end());

    double m1, m2, m3, m4;
    xBegin = 0;
    xEnd = s.f[s.f.size() - 1];
    m1 = y1[0];
    m2 = y2[0];
    m3 = y3[0];
    m4 = y4[0];
    
    for (int j = 0; j < s.Mg.size() - 1; j++)
    {
        if (y1[j + 1] > m1)
        {
            m1 = y1[j + 1];
        }
    }
    for (int j = 0; j < s.Ms.size() - 1; j++)
    {
        if (y2[j + 1] > m2)
        {
            m2 = y2[j + 1];
        }
    }

    if (m2 < m1)
    {
        yBegin = m1;
        yEnd = 0;
    }
    else
    {
        yBegin = m2;
        yEnd = 0;
    }

    plotWidget->xAxis->setRange(xBegin, xEnd);
    plotWidget->xAxis->setLabel("f[Hz]");
    plotWidget->yAxis->setRange(yBegin, yEnd);
    plotWidget->yAxis->setLabel("[dB]");
    plotWidget->yAxis2->setRange(yBegin / 10, yEnd / 10);
    plotWidget->yAxis2->setLabel("[K,μ]");

    for (int i = 0; i < x.size() - 1; i++)
    {
        if (y1[i] == 0)
        {
            y1[i] = qQNaN();
        }
        if (y2[i] == 0)
        {
            y2[i] = qQNaN();
        }
    }

    plotWidget->legend->setVisible(true);
    QPen pen1(SystemParameters::magGrafColor, SystemParameters::sPlotline[2]);
    QPen penGid(SystemParameters::gridGrafTwoColor, SystemParameters::sPlotline[8], Qt::DotLine);
    plotWidget->xAxis->grid()->setPen(penGid);
    plotWidget->yAxis->grid()->setPen(penGid);
    plotWidget->yAxis2->grid()->setPen(penGid);
    
    plotWidget->addGraph(plotWidget->xAxis, plotWidget->yAxis);
    plotWidget->graph(0)->setPen(pen1);
    plotWidget->graph(0)->setName("MAG");
    plotWidget->graph(0)->addData(x, y1);
    
    QPen pen2(SystemParameters::msgGrafColor, SystemParameters::sPlotline[3]);
    plotWidget->addGraph(plotWidget->xAxis, plotWidget->yAxis);
    plotWidget->graph(1)->setPen(pen2);
    plotWidget->graph(1)->setName("MSG");
    plotWidget->graph(1)->addData(x, y2);
    
    QPen pen3(SystemParameters::kGrafColor, SystemParameters::sPlotline[4]);
    plotWidget->addGraph(plotWidget->xAxis, plotWidget->yAxis2);
    plotWidget->graph(2)->setPen(pen3);
    plotWidget->graph(2)->setName("K");
    plotWidget->graph(2)->addData(x, y3);
    
    QPen pen4(SystemParameters::muGrafColor, SystemParameters::sPlotline[5]);
    plotWidget->addGraph(plotWidget->xAxis, plotWidget->yAxis2);
    plotWidget->graph(3)->setPen(pen4);
    plotWidget->graph(3)->setName("μ");
    plotWidget->graph(3)->addData(x, y4);
    
    plotWidget->yAxis2->setVisible(true);
    plotWidget->replot();

    plotWidget->setInteraction(QCP::iRangeZoom, true);
    plotWidget->setInteraction(QCP::iRangeDrag, true);
    
    QList<QCPAxis*> axises;
    axises.append(plotWidget->xAxis);
    axises.append(plotWidget->yAxis);
    axises.append(plotWidget->yAxis2);
    plotWidget->axisRect()->setRangeDragAxes(axises);
    plotWidget->axisRect()->setRangeZoomAxes(axises);

    GraphK = plotWidget->addGraph();
    GraphK->setLineStyle(QCPGraph::lsNone);
    GraphK->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, Qt::black, 5));
    GraphK->removeFromLegend();

    Graphu = plotWidget->addGraph();
    Graphu->setLineStyle(QCPGraph::lsNone);
    Graphu->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, Qt::black, 5));
    Graphu->removeFromLegend();

    GraphMAG = plotWidget->addGraph();
    GraphMAG->setLineStyle(QCPGraph::lsNone);
    GraphMAG->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, Qt::black, 5));
    GraphMAG->removeFromLegend();

    GraphMSG = plotWidget->addGraph();
    GraphMSG->setLineStyle(QCPGraph::lsNone);
    GraphMSG->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, Qt::black, 5));
    GraphMSG->removeFromLegend();

    GraphMAG->setValueAxis(plotWidget->yAxis);
    GraphMSG->setValueAxis(plotWidget->yAxis);
    GraphK->setValueAxis(plotWidget->yAxis2);
    Graphu->setValueAxis(plotWidget->yAxis2);
}

/// <summary>
/// Изменение цвета на виджете.
/// </summary>
void GrafTwo::updateGrafTwoColor()
{
    extern QString fileName;
    if (!fileName.isEmpty())
    {
        this->Load();
        this->update();
    }
}

/// <summary>
/// Сохранение виджета в изображение.
/// </summary>
void GrafTwo::SaveGrafTwo()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save the graph", QDir::homePath() + "/graph.png", "PNG Files (*.png);;JPEG Files (*.jpg);;PDF Files (*.pdf)");

    if (!fileName.isEmpty())
    {
        bool success = false;

        if (fileName.endsWith(".png", Qt::CaseInsensitive))
        {
            success = plotWidget->savePng(fileName, plotWidget->width() * 2, plotWidget->height() * 2, 2.0);
        }
        else if (fileName.endsWith(".jpg", Qt::CaseInsensitive))
        {
            success = plotWidget->saveJpg(fileName, plotWidget->width(), plotWidget->height());
        }
        else if (fileName.endsWith(".pdf", Qt::CaseInsensitive))
        {
            success = plotWidget->savePdf(fileName);
        }

        if (success)
        {
            QMessageBox::information(this, "Success", QString("The graph is saved to a file:\n%1").arg(fileName));
        }
        else
        {
            QMessageBox::warning(this, "Error", "Couldn't save graph!");
        }
    }
}

/// <summary>
/// Выбор подсвечиваемой точки.
/// </summary>
/// <param name="index">Номер точки.</param>
void GrafTwo::highlightPoint(int index)
{
    if (index >= 0 && index < x.size())
    {
        QVector<double> highlightX = { x[index] };

        if (GraphMAG) GraphMAG->setData(highlightX, QVector<double>{y1[index]});
        if (GraphMSG) GraphMSG->setData(highlightX, QVector<double>{y2[index]});
        if (GraphK) GraphK->setData(highlightX, QVector<double>{y3[index]});
        if (Graphu) Graphu->setData(highlightX, QVector<double>{y4[index]});

        plotWidget->replot();
    }
}

/// <summary>
/// Деструктор класса GrafTwo.
/// </summary>
GrafTwo::~GrafTwo()
{
}