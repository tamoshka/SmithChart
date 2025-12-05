﻿#include "GrafOne.h"
#include "S2p.h"
#include <QString>

/// <summary>
/// Конструктор класса GrafOne.
/// </summary>
/// <param name="parent"></param>
GrafOne::GrafOne(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
}

/// <summary>
/// Инициализация пользовательского интерфейса.
/// </summary>
void GrafOne::setupUI()
{

    mainLayout = new QVBoxLayout(this);
    saveButton = new QPushButton("Save", this);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addStretch();

    plotWidget = new QCustomPlot(this);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(plotWidget);

    connect(saveButton, &QPushButton::clicked, this, &GrafOne::SaveGrafOne);
    setLayout(mainLayout);
}

/// <summary>
/// Загрузка параметров из SnP файла.
/// </summary>
void GrafOne::Load()
{
    extern QString fileName;
    auto extension = fileName.toStdString();
    size_t last_dot = extension.find_last_of('.');
    extension = last_dot != std::string::npos ? extension.substr(last_dot + 1) : "";

    TouchstoneFile t;
    spar_t s;
    plotWidget->clearGraphs();
    s = t.Load2P(fileName.toStdString().c_str());

    x = QVector<double>(s.f.begin(), s.f.end());
    y1 = QVector<double>(s.S11.begin(), s.S11.end());
    y2 = QVector<double>(s.S22.begin(), s.S22.end());
    double m1, m2;
    hX = s.f[s.f.size() - 1] / 4;

    xBegin = 0;
    xEnd = s.f[s.f.size() - 1];
    m1 = y1[0];
    m2 = y2[0];
    for (int j = 0; j < s.S11.size() - 1; j++)
    {
        if (y1[j + 1] < m1)
        {
            m1 = y1[j + 1];
        }
    }
    for (int j = 0; j < s.S22.size() - 1; j++)
    {
        if (y2[j + 1] < m2)
        {
            m2 = y2[j + 1];
        }
    }
    if (extension == "S1P" || extension == "s1p")
    {
        hY = m1 / 5;
        yBegin = m1 * 1.25;
        yEnd = 0;
    }
    else if (m2 < m1)
    {
        hY = m2 / 5;
        yBegin = m2 * 1.25;
        yEnd = 0;
    }
    else
    {
        hY = m1 / 5;
        yBegin = m1 * 1.25;
        yEnd = 0;
    }

    plotWidget->xAxis->setRange(xBegin, xEnd);
    plotWidget->xAxis->setLabel("f[Hz]");
    plotWidget->yAxis->setRange(yBegin, yEnd);
    plotWidget->yAxis->setLabel("[dB]");

    for (xBegin; xBegin <= xEnd; xBegin += hX)
    {
        if (xBegin <= xEnd)
        {
            x;
            y1;
        }
    }

    for (yEnd; yEnd <= yBegin; yEnd += yBegin / 5)
    {
        hY + hY;
        if (hY == yEnd)
        {
            x;
            y2;
        }
    }

    plotWidget->legend->setVisible(true);
    if (extension == "S1P" || extension == "s1p")
    {
        plotWidget->addGraph();
        QPen penGid(SystemParameters::gridGrafOneColor, SystemParameters::sPlotline[9], Qt::DotLine);
        QPen pen1(SystemParameters::s11GrafColor, SystemParameters::sPlotline[6]);
        plotWidget->graph(0)->setPen(pen1);
        plotWidget->xAxis->grid()->setPen(penGid);
        plotWidget->yAxis->grid()->setPen(penGid);
        plotWidget->graph(0)->addData(x, y1);
        plotWidget->graph(0)->setName("Return Loss S11");
    }
    else if (extension == "S2P" || extension == "s2p")
    {
        plotWidget->addGraph();
        QPen penGid(SystemParameters::gridGrafOneColor, SystemParameters::sPlotline[9], Qt::DotLine);
        QPen pen1(SystemParameters::s11GrafColor, SystemParameters::sPlotline[6]);
        plotWidget->graph(0)->setPen(pen1);
        plotWidget->xAxis->grid()->setPen(penGid);
        plotWidget->yAxis->grid()->setPen(penGid);
        plotWidget->graph(0)->addData(x, y1);
        plotWidget->graph(0)->setName("Return Loss S11");
        plotWidget->addGraph();
        plotWidget->graph(1)->setName("Return Loss S22");
        plotWidget->graph(1)->addData(x, y2);
        QPen pen2(SystemParameters::s22GrafColor, SystemParameters::sPlotline[7]);
        plotWidget->graph(1)->setPen(pen2);
    }

    plotWidget->replot();
    plotWidget->setInteraction(QCP::iRangeZoom, true);
    plotWidget->setInteraction(QCP::iRangeDrag, true);

    GraphS11 = plotWidget->addGraph();
    GraphS11->setLineStyle(QCPGraph::lsNone);
    GraphS11->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, Qt::black, 5));
    GraphS11->removeFromLegend();

    GraphS22 = plotWidget->addGraph();
    GraphS22->setLineStyle(QCPGraph::lsNone);
    GraphS22->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, Qt::black, 5));
    GraphS22->removeFromLegend();
}

/// <summary>
/// Обновление цвета на виджете.
/// </summary>
void GrafOne::updateGrafOneColor()
{
    if (!fileName.isEmpty())
    {
        this->Load();
        this->update();
    }
}

/// <summary>
/// Сохранение изображения виджета.
/// </summary>
void GrafOne::SaveGrafOne()
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
void GrafOne::highlightPoint(int index)
{
    if (index >= 0 && index < x.size())
    {
        QVector<double> highlightX = { x[index] };
        QVector<double> highlightY1 = { y1[index] };
        QVector<double> highlightY2 = { y2[index] };

        if (GraphS11)
            GraphS11->setData(highlightX, highlightY1);
        if (GraphS22)
            GraphS22->setData(highlightX, highlightY2);

        plotWidget->replot();
    }
}

/// <summary>
/// Деструктор класса GrafOne.
/// </summary>
GrafOne::~GrafOne()
{
}