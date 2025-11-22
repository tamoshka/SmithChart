#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Smithtry1000.h"
#include <qgraphicsscene.h>
#include <qpainterpath.h>
#include <QtSvg>
#include <QTimer>
#include <QThread>
#include <QMouseEvent>
#include "general.h"
#include <qtablewidget.h>
#include <QScrollArea>
#include "frequencyDialog.h"
#include "PreSaveDialog.h"
#include "VerticalLinesDialog.h"
#include "AmplitudeFrequency.h"
#include "SParameters.h"
#include "ExportNetlist.h"
#include "renderarea.h"
#include "TuneWidget.h"
#include "ColourSetting.h"
#include "LinesDialog.h"
#include "KeyboardDialog.h"
#include "CirclesWidget.h"
#include "SaveDialog.h"
#include "awr_interface.h"
#include "EditWidget.h"

/// <summary>
/// Класс работы с курсором, являющийся также главным хабом и окном приложения.
/// </summary>
class Smithtry1000 : public QMainWindow
{
    Q_OBJECT

public: 
    Smithtry1000(QWidget* parent = nullptr, SParameters* = nullptr);
    ~Smithtry1000();
    CircuitElements* circuitElements = new CircuitElements();
    CircuitWidget* auxiliaryWidget = new CircuitWidget(this, circuitElements);

public slots:
    void getsignal();
    void getS12S21signal();
    void getsignalDVS();
    void getCirclesSignal();
    void getallchangedsignal();
    void Reverse();
    void GetEditSignal(Element* element);

signals:
    void left();
    void load();
    void reverse();

private slots:
    void onButtonClicked();
    void onCapacitor_buttonClicked();
    void onInduction_buttonClicked();
    void onResistor_buttonClicked();
    void onCapacitorParallel_buttonClicked();
    void onInductionParallel_buttonClicked();
    void onResistorParallel_buttonClicked();
    void onLine_buttonClicked();
    void onOSLine_buttonClicked();
    void onSSLine_buttonClicked();
    void onDelete_buttonClicked();
    void onPlusSize_buttonClicked();
    void onMinusSize_buttonClicked();
    void onDefaultSize_buttonClicked();
    void onGraph_buttonClicked();
    void onExportNetlist_buttonClicked();
    void onTune_buttonClicked();
    void onS11_buttonClicked();
    void onS22_buttonClicked();
    void onTimeout();
    void TableUpdate();
    void onMenuToolsCliked();
    void onKeyboard_buttonClicked();
    void onCirclesClicked();
    void onTransform_buttonClicked();
    void Copy();
    void Save();
    void Load();
    void Redo();
    void AWR_buttonClicked();
    void CAD_export();

private:
    ///AWRInterface awr = AWRInterface();
    friend class AWRExportThread;
    EditWidget* edit;
    SParameters* sParameters;
    AmplitudeFrequency* amplitudeFrequence = new AmplitudeFrequency(nullptr, circuitElements);
    RenderArea* renderArea = new RenderArea(this, circuitElements);
    CircuitElements tempCircuit;
    TuneWidget* tuneWidget = new TuneWidget(nullptr, circuitElements);
    CirclesWidget* circlesWidget = new CirclesWidget(nullptr, circuitElements);
    void ImaginaryImpedance();
    void ImaginaryAdmitance();
    void VerticalLines();
    bool ExportToAWR();
    void mousePressEvent(QMouseEvent* event) override;
    Ui::Smithtry1000Class* ui;
    bool trackingEnabled;
    bool leftClicked;
    bool rightClicked;
    bool tableChanged=false;
    QList<long double> pointsX;
    QList<long double> pointsY;
    QPoint lastPos;
    bool moving=false;
    long double t;
    long double tmin;
    long double tmax;
    long double step;
    long double r;   
    long double intervalLength = 2 * M_PI;
    bool firstDeleted = true;
    QPoint getPointOnCircle(int, int);
    QTimer* timer;

protected:
    void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
};