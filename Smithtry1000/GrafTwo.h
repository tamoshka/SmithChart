#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include "qcustomplot.h"
#include "S2p.h"
#include <QVector>
#include "ColourSetting.h"

/// <summary>
/// Класс для отображения k, mu, MAG, MSG.
/// </summary>
class GrafTwo : public QWidget
{
    Q_OBJECT

public:
    GrafTwo(QWidget* parent = nullptr);
    ~GrafTwo();
    void Load();

public slots:
    void highlightPoint(int index);
    void updateGrafTwoColor();
    void SaveGrafTwo();
private:
    QCustomPlot* plotWidget = nullptr;
    QPushButton* saveButton = nullptr;
    QVBoxLayout* mainLayout = nullptr;
    
    double xBegin, xEnd, yBegin, yEnd, yBeginTwo, yEndTwo;
    QVector<double> x, y1, y2, y3, y4;
private:
    QCPGraph* GraphK = nullptr;
    QCPGraph* Graphu = nullptr;
    QCPGraph* GraphMAG = nullptr;
    QCPGraph* GraphMSG = nullptr;
    void setupUI();
};