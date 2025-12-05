#pragma once

#include <QtWidgets/QMainWindow>
#include <QMdiArea>
#include <QIcon>
#include <QAction>
#include <QFormLayout>
#include <QFrame>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QTableWidget>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>
#include <QMdiSubWindow>
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
#include "circuitWidget.h"
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
    void getLeftClicked(QPoint, bool);
    void getReleased();
    void getMoved(QPoint);
    void getResized(long double, long double, long double, long double);

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
    void ExportToAWR();
    void CAD_export();

private:
    ///AWRInterface awr = AWRInterface();

    QToolBar* toolbar;
    QAction* actionColors;
    QWidget* centralWidget;
    QVBoxLayout* verticalLayout_3;
    QVBoxLayout* verticalLayout;
    QAction* OpenButton;
    QAction* SaveButton;
    QAction* CopyButton;
    QAction* StepBackButton;
    QAction* StepForwardButton;
    QAction* PrintButton;
    QAction* MouseButton;
    QAction* KeyboardButton;
    QAction* S11Button;
    QAction* S22Button;
    QAction* PlusSizeButton;
    QAction* MinusSizeButton;
    QAction* OneToOneButton;
    QAction* Resistor_button;
    QAction* Induction_button;
    QAction* Capacitor_button;
    QAction* ResistorParallel_button;
    QAction* InductionParallel_button;
    QAction* CapacitorParallel_button;
    QAction* GraphButton;
    QAction* ExportNetlistButton;
    QAction* Tune;
    QAction* Line_button;
    QAction* SSLine_button;
    QAction* OSLine_button;
    QAction* CirclesButton;
    QAction* ParametersButton;
    QAction* Transform_button;
    QAction* AWRButton;
    QAction* Diagram_button;
    QAction* SPlotButton;
    QAction* CADButton;
    QScrollArea* scrollAreaDiagram;
    QScrollArea* scrollArea;
    CircuitWidget* circuitWidget;
    QTableWidget* rTable;
    QTableWidget* pointTable;
    QMenuBar* menuBar;
    QMenu* menuEdit;
    QMenu* menuMode;
    QMenu* menuTools;
    QMenu* menuZoom;
    QMenu* menuWindow;
    QMenu* menuHelp;
    QStatusBar* statusBar;

    QMdiArea* mdiArea;
    friend class AWRExportThread;
    EditWidget* edit;
    SParameters* sParameters;
    AmplitudeFrequency* amplitudeFrequence = new AmplitudeFrequency(nullptr, circuitElements);
    RenderArea* renderArea = new RenderArea(this, circuitElements);
    CircuitElements tempCircuit;
    TuneWidget* tuneWidget = new TuneWidget(nullptr, circuitElements);
    CirclesWidget* circlesWidget = new CirclesWidget(nullptr, circuitElements);
    void SetupUI();
    void ImaginaryImpedance();
    void ImaginaryAdmitance();
    void VerticalLines();
    void mousePressEvent(QMouseEvent* event) override;
    bool trackingEnabled;
    bool leftClicked;
    bool rightClicked;
    bool tableChanged = false;
    QList<long double> pointsX;
    QList<long double> pointsY;
    QPoint lastPos;
    bool moving = false;
    long double t;
    long double tmin;
    long double tmax;
    long double step;
    long double r;
    long double intervalLength = 2 * M_PI;
    bool firstDeleted = true;
    QPoint getPointOnCircle(int, int);
    QTimer* timer;
    void ChangeAllElements();
    void SwitchElementName(QString&, bool&, int);
    void RedoElement();
    void RedoPoints();
    void SaveBeforeLoad();
    void CorrectZ0(long double, long double);
    void LoadElementsAndPoints();
    void AppendTransformer(Complex);
    void AppendLine(Complex);
    void AppendPoint(long double, long double);
    void AppendVerticalLines(Complex);
    void AppendResShunt(long double, long double);
    void AppendResPar(long double, long double);
    void AppendIndCapShunt(long double, long double);
    void AppendIndCapPar(long double, long double);
    void ChangeCursorTable(long double, long double);
    void UpdateCursorTableInMode(long double&, long double&);
    void IndCapShuntPoint(int, int, long double&, long double&);
    void IndCapParPoint(int, int, long double&, long double&);
    void ResShuntPoint(int, int, long double&, long double&);
    void ResParPoint(int, int, long double&, long double&);
    void OSSSPoint(int, int, long double&, long double&);
    void LinePoint(int, int, long double&, long double&);
    void TransformPoint(int, int, long double&, long double&);
    void NormalTransformPoint(int, int, long double&, long double&);

protected:
    void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;
};