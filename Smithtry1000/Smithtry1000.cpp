#include "AWRExportThread.h"
#include <QCursor>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPoint>
#include <QRect>
#include <QCursor>
#include <QPoint>
#include <QRect>
#include <QtMath>
#include <QThread>
#include <cmath>
#include <exception>
#include "systemParameters.h"

/// <summary>
/// Конструктор класса Smithtry1000.
/// </summary>
/// <param name="parent"></param>
/// <param name="sParameters1">S-параметры приходящие из файлы snp.</param>
Smithtry1000::Smithtry1000(QWidget* parent, SParameters* sParameters1)
    : QMainWindow(parent)
    , trackingEnabled(false)
{
    SetupUI();
    this->sParameters = sParameters1;
    SystemParameters::Model = Default;
    
    pointTable->setColumnCount(5);
    pointTable->setRowCount(1);
    pointTable->setColumnWidth(0, 50);
    pointTable->setColumnWidth(1, 35);
    pointTable->setColumnWidth(2, 130);
    pointTable->setColumnWidth(3, 70);
    pointTable->setColumnWidth(4, 85);
    pointTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    pointTable->setItem(0, 0, new QTableWidgetItem(QStringLiteral(u"Нач.")));
    pointTable->setItem(0, 1, new QTableWidgetItem("ID"));
    pointTable->setItem(0, 2, new QTableWidgetItem("Z"));
    pointTable->setItem(0, 3, new QTableWidgetItem("Q"));
    pointTable->setItem(0, 4, new QTableWidgetItem(QStringLiteral(u"Частота")));
    rTable->setRowCount(4);
    rTable->setColumnCount(4);
    rTable->setColumnWidth(1, 100);
    rTable->setColumnWidth(0, 30);
    rTable->setColumnWidth(2, 150);
    rTable->setColumnWidth(3, 100);
    rTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    rTable->setItem(0, 0, new QTableWidgetItem("Z"));
    rTable->setItem(1, 0, new QTableWidgetItem("Y"));
    rTable->setItem(2, 0, new QTableWidgetItem("G"));
    rTable->setItem(3, 0, new QTableWidgetItem("Z0"));
    rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)SystemParameters::z0)));
    rTable->setItem(0, 2, new QTableWidgetItem(QStringLiteral(u"КСВН")));
    rTable->setItem(1, 2, new QTableWidgetItem("Q"));
    rTable->setItem(2, 2, new QTableWidgetItem(QStringLiteral(u"Обратные потери")));
    rTable->setItem(3, 2, new QTableWidgetItem(QStringLiteral(u"Частота")));
    tmin = 0;
    tmax = 2 * M_PI;
    auxiliaryWidget->setMinimumWidth(200);
    auxiliaryWidget->setMinimumHeight(400);
    scrollArea->setWidget(auxiliaryWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    if (!SystemParameters::rotate)
    {
        auxiliaryWidget->addSvg(QString(":/Images/load.svg"), 40, 39);
        auxiliaryWidget->addSvg(QString(":/Images/source.svg"), 80, 39);
    }
    else
    {
        auxiliaryWidget->addSvg(QString(":/Images/rev_load.svg"), 39, 40);
        auxiliaryWidget->addSvg(QString(":/Images/rev_source.svg"), 39, 80);
    }
    connect(MouseButton, &QAction::triggered, this, &Smithtry1000::onButtonClicked);
    connect(Capacitor_button, &QAction::triggered, this, &Smithtry1000::onCapacitor_buttonClicked);
    connect(GraphButton, &QAction::triggered, this, &Smithtry1000::onGraph_buttonClicked);
    connect(Induction_button, &QAction::triggered, this, &Smithtry1000::onInduction_buttonClicked);
    connect(Resistor_button, &QAction::triggered, this, &Smithtry1000::onResistor_buttonClicked);
    connect(CapacitorParallel_button, &QAction::triggered, this, &Smithtry1000::onCapacitorParallel_buttonClicked);
    connect(InductionParallel_button, &QAction::triggered, this, &Smithtry1000::onInductionParallel_buttonClicked);
    connect(ResistorParallel_button, &QAction::triggered, this, &Smithtry1000::onResistorParallel_buttonClicked);
    connect(StepBackButton, &QAction::triggered, this, &Smithtry1000::onDelete_buttonClicked);
    connect(PlusSizeButton, &QAction::triggered, this, &Smithtry1000::onPlusSize_buttonClicked);
    connect(MinusSizeButton, &QAction::triggered, this, &Smithtry1000::onMinusSize_buttonClicked);
    connect(OneToOneButton, &QAction::triggered, this, &Smithtry1000::onDefaultSize_buttonClicked);
    ///connect(S11Button, &QAction::triggered, this, &Smithtry1000::onS11_buttonClicked);
    ///connect(S22Button, &QAction::triggered, this, &Smithtry1000::onS22_buttonClicked);
    connect(ExportNetlistButton, &QAction::triggered, this, &Smithtry1000::onExportNetlist_buttonClicked);
    connect(Tune, &QAction::triggered, this, &Smithtry1000::onTune_buttonClicked);
    connect(Line_button, &QAction::triggered, this, &Smithtry1000::onLine_buttonClicked);
    connect(OSLine_button, &QAction::triggered, this, &Smithtry1000::onOSLine_buttonClicked);
    connect(SSLine_button, &QAction::triggered, this, &Smithtry1000::onSSLine_buttonClicked);
    connect(actionColors, &QAction::triggered, this, &Smithtry1000::onMenuToolsCliked);
    connect(ParametersButton, &QAction::triggered, this, &Smithtry1000::onMenuToolsCliked);
    connect(KeyboardButton, &QAction::triggered, this, &Smithtry1000::onKeyboard_buttonClicked);
    connect(CirclesButton, &QAction::triggered, this, &Smithtry1000::onCirclesClicked);
    connect(Transform_button, &QAction::triggered, this, &Smithtry1000::onTransform_buttonClicked);
    connect(CopyButton, &QAction::triggered, this, &Smithtry1000::Copy);
    connect(SaveButton, &QAction::triggered, this, &Smithtry1000::Save);
    connect(OpenButton, &QAction::triggered, this, &Smithtry1000::Load);
    connect(StepForwardButton, &QAction::triggered, this, &Smithtry1000::Redo);
    connect(AWRButton, &QAction::triggered, this, &Smithtry1000::AWR_buttonClicked);
    connect(CADButton, &QAction::triggered, this, &Smithtry1000::CAD_export);
    QObject::connect(circlesWidget, &CirclesWidget::circle, this, &Smithtry1000::getCirclesSignal);
    QObject::connect(sParameters->set, &ColourSetting::signalS12S21, this, &Smithtry1000::getS12S21signal);
    QObject::connect(sParameters->set, &ColourSetting::signalDVS, this, &Smithtry1000::getsignalDVS);
    QObject::connect(sParameters->set, &ColourSetting::signal, this, &Smithtry1000::getsignal);
    QObject::connect(sParameters->set, &ColourSetting::allchangedsignal, this, &Smithtry1000::getallchangedsignal);
    QObject::connect(tuneWidget, &TuneWidget::remove, auxiliaryWidget, &CircuitWidget::RemoveElement);
    QObject::connect(tuneWidget, &TuneWidget::removeAll, auxiliaryWidget, &CircuitWidget::RemoveAll);
    QObject::connect(this, &Smithtry1000::load, circlesWidget, &CirclesWidget::Load);
    QObject::connect(auxiliaryWidget, &CircuitWidget::clicked, tuneWidget, &TuneWidget::GetSignal);
    QObject::connect(sParameters->set, &ColourSetting::rev, this, &Smithtry1000::Reverse);
    QObject::connect(this, &Smithtry1000::reverse, auxiliaryWidget, &CircuitWidget::Reverse);
    QObject::connect(auxiliaryWidget, &CircuitWidget::Edit, this, &Smithtry1000::GetEditSignal);
    QObject::connect(renderArea, &RenderArea::leftsignal, this, &Smithtry1000::getLeftClicked);
    QObject::connect(renderArea, &RenderArea::moved, this, &Smithtry1000::getMoved);
    QObject::connect(renderArea, &RenderArea::released, this, &Smithtry1000::getReleased);
    QObject::connect(renderArea, &RenderArea::resized, this, &Smithtry1000::getResized);
    renderArea->setMinimumHeight(800);
    renderArea->setMinimumWidth(1200);
    scrollAreaDiagram->setWidget(renderArea);
    scrollAreaDiagram->setWidgetResizable(true);
    scrollAreaDiagram->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollAreaDiagram->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Smithtry1000::onTimeout);
    timer->start(10);  // Частое обновление для плавности
}

/// <summary>
/// Настройка интерфейса
/// </summary>
void Smithtry1000::SetupUI()
{
    this->resize(1700, 937);

    menuBar = new QMenuBar(this);
    menuEdit = new QMenu(QStringLiteral(u"Правка"), menuBar);
    menuMode = new QMenu(QStringLiteral(u"Режим"), menuBar);
    menuMode->setTearOffEnabled(true);
    menuTools = new QMenu(QStringLiteral(u"Инструменты"), menuBar);
    menuZoom = new QMenu(QStringLiteral(u"Масштаб"), menuBar);
    menuZoom->setGeometry(QRect(938, 391, 128, 48));
    menuWindow = new QMenu(QStringLiteral(u"Окно"), menuBar);
    menuHelp = new QMenu(QStringLiteral(u"Помощь"), menuBar);
    this->setMenuBar(menuBar);
    statusBar = new QStatusBar(this);
    this->setStatusBar(statusBar);
    menuBar->addAction(menuEdit->menuAction());
    menuBar->addAction(menuMode->menuAction());
    menuBar->addAction(menuTools->menuAction());
    menuBar->addAction(menuZoom->menuAction());
    menuBar->addAction(menuWindow->menuAction());
    menuBar->addAction(menuHelp->menuAction());
    actionColors = new QAction(this);
    menuTools->addAction(actionColors);
    toolbar = new QToolBar("Главное меню", this);
    toolbar->setStyleSheet(
        "QToolBar {"
        "   background: #f0f0f0;"
        "   border: 1px solid #ccc;"
        "   spacing: 2px;"
        "   padding: 2px;"
        "}"
        "QToolButton {"
        "   background: white;"
        "   border: 1px solid #999;"
        "   border-radius: 2px;"
        "   padding: 2px 2px;"
        "   margin: 2px;"
        "}"
        "QToolButton:hover {"
        "   background: #e3f2fd;"
        "   border: 1px solid #2196F3;"
        "}"
        "QToolButton:pressed {"
        "   background: #bbdefb;"
        "   border: 1px solid #1976D2;"
        "}"
    );
    OpenButton = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/Open.png")), "");
    SaveButton = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/Save.png")), "");
    CopyButton = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/Copy.png")), "");
    StepBackButton = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/Undo.png")), "");
    StepForwardButton = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/Redo.png")), "");
    PrintButton = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/print.png")), "");
    toolbar->addSeparator();
    MouseButton = toolbar->addAction(QStringLiteral(u"Мышь"));
    KeyboardButton = toolbar->addAction(QStringLiteral(u"Клавиатура"));
    S11Button = toolbar->addAction("S11");
    S22Button = toolbar->addAction("S22");
    toolbar->addSeparator();
    PlusSizeButton = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/PlusSize.png")), "");
    MinusSizeButton = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/MinusSize.png")), "");
    OneToOneButton = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/OneToOne.png")), "");
    toolbar->addSeparator();
    ParametersButton = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/settings.png")), "");
    CirclesButton = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/Circles.png")), "");
    Resistor_button = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/horizontal_r.svg")), "");
    Induction_button = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/horizontal_i.svg")), "");
    Capacitor_button = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/horizontal_c.svg")), "");
    Line_button = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/horizontal_line.svg")), "");
    Transform_button = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/vertical_transform.svg")), "");
    ResistorParallel_button = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/vertical_r.svg")), "");
    InductionParallel_button = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/vertical_i.svg")), "");
    CapacitorParallel_button = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/vertical_c.svg")), "");
    OSLine_button = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/os.svg")), "");
    SSLine_button = toolbar->addAction(QIcon(QString::fromUtf8(":/Images/ss.svg")), ""); 
    toolbar->addSeparator();
    GraphButton = toolbar->addAction(QStringLiteral(u"АЧХ"));
    ExportNetlistButton = toolbar->addAction(QStringLiteral(u"Netlist"));
    Tune = toolbar->addAction(QStringLiteral(u"Тюнер"));
    AWRButton = toolbar->addAction(QStringLiteral(u"AWR"));
    Diagram_button = toolbar->addAction(QStringLiteral(u"Diagram"));
    SPlotButton = toolbar->addAction(QStringLiteral(u"SPlot"));
    CADButton = toolbar->addAction(QStringLiteral(u"САПР"));
    scrollAreaDiagram = new QScrollArea(this);
    scrollAreaDiagram->setWidgetResizable(true);
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    rTable = new QTableWidget(this);
    rTable->setMinimumSize(QSize(0, 200));
    pointTable = new QTableWidget(this);
    if (pointTable->columnCount() < 5)
        pointTable->setColumnCount(5);
    pointTable->setMinimumSize(QSize(250, 250));
    pointTable->setLayoutDirection(Qt::LeftToRight);
    pointTable->setColumnCount(5);
    pointTable->horizontalHeader()->setDefaultSectionSize(70);

    QWidget* centralWidget2 = new QWidget(this);
    QVBoxLayout* vBox = new QVBoxLayout(centralWidget2);
    mdiArea = new QMdiArea(this);
    vBox->addWidget(toolbar);
    vBox->addWidget(mdiArea);
    setCentralWidget(centralWidget2);
    int mdiWidth = 1600;
    int mdiHeight = 800;
    QMdiSubWindow* dvs = mdiArea->addSubWindow(scrollAreaDiagram);
    dvs->setWindowTitle(QString("ДВС"));
    dvs->resize(1200, 800);
    QMdiSubWindow* crc = mdiArea->addSubWindow(scrollArea);
    crc->setWindowTitle(QString("Цепь"));
    crc->resize(430, 330);
    QMdiSubWindow* rTab = mdiArea->addSubWindow(rTable);
    rTab->setWindowTitle(QString("Координаты курсора"));
    rTab->resize(430, 200);
    QMdiSubWindow* pTab = mdiArea->addSubWindow(pointTable);
    pTab->setWindowTitle(QString("Точки"));
    pTab->resize(430, 250);
    int leftWidth = mdiWidth * 0.75;
    int rightWidth = mdiWidth * 0.25;
    int rightHeight = mdiHeight / 3;
    dvs->setGeometry(0, 0, leftWidth, mdiHeight);

    crc->setGeometry(leftWidth, 0, rightWidth, rightHeight);

    rTab->setGeometry(leftWidth, rightHeight, rightWidth, rightHeight);

    pTab->setGeometry(leftWidth, rightHeight * 2, rightWidth, rightHeight);

    dvs->setWindowFlags(Qt::Window |
        Qt::WindowMinimizeButtonHint |
        Qt::WindowMaximizeButtonHint |
        Qt::WindowTitleHint);

    crc->setWindowFlags(Qt::Window |
        Qt::WindowMinimizeButtonHint |
        Qt::WindowMaximizeButtonHint |
        Qt::WindowTitleHint);

    rTab->setWindowFlags(Qt::Window |
        Qt::WindowMinimizeButtonHint |
        Qt::WindowMaximizeButtonHint |
        Qt::WindowTitleHint);

    pTab->setWindowFlags(Qt::Window |
        Qt::WindowMinimizeButtonHint |
        Qt::WindowMaximizeButtonHint |
        Qt::WindowTitleHint);

    dvs->show();
    crc->show();
    rTab->show();
    pTab->show();
}

/// <summary>
/// Редактирование одного элемента.
/// </summary>
/// <param name="elem">Элемент.</param>
void Smithtry1000::GetEditSignal(Element* elem)
{
    edit = new EditWidget(nullptr, circuitElements, elem);
    edit->show();
}

/// <summary>
/// Изменение ориентации цепи.
/// </summary>
void Smithtry1000::Reverse()
{
    emit reverse();
}

/// <summary>
/// Метод для кнопки AWR, запускающий отдельный поток для COM.
/// </summary>
void Smithtry1000::AWR_buttonClicked()
{
    if (SystemParameters::index <= 1)
    {
        QMessageBox::information(this, "Внимание",
            "Добавьте хотя бы 1 элемент в цепь.");
        return;
    }

    // Создаём поток для экспорта
    AWRExportThread* thread = new AWRExportThread(this);

    connect(thread, &AWRExportThread::finished, [this, thread]() {
        bool success = thread->getSuccess();
        thread->deleteLater();
        });

    thread->start();
}

/// <summary>
/// Экспорт схемы в AWR.
/// </summary>
/// <returns>Успешно/нет.</returns>
bool Smithtry1000::ExportToAWR()
{
    if (!awr.Initialize()) {
        return false;
    }

    qDebug() << "Creating project...";
    if (!awr.CreateProject(L"SmithChartMatch")) {
        return false;
    }

    int x = 1000;
    if (awr.m_portSchematic == nullptr)
    {
        if (!awr.AddPortSchematic(L"ZL", false)) {
            return false;
        }
    }
    else
    {
        awr.ClearAllPortElements(false);
    }
    qDebug() << "\nAdding source port...";
    if (awr.AddPortElement(L"PORT", 1000, 800, 180, false))
    {
        awr.SetElementParameter(L"P", L"1");
        awr.SetElementParameter(L"Z", L"50");
    }
    if (awr.AddPortElement(L"IMPED", 1000, 800, 270, false))
    {
        double real = circuitElements->z.real();
        double imag = circuitElements->z.imag();
        wchar_t realstr[64];
        swprintf(realstr, 64, L"%.2f", real);
        wchar_t imagstr[64];
        swprintf(imagstr, 64, L"%.2f", imag);
        awr.SetElementParameter(L"R", realstr);
        awr.SetElementParameter(L"X", imagstr);
    }
    if (awr.AddPortElement(L"GND", 1000, 1800, 0, false))
    {

    }
    qDebug() << "Adding schematic...";
    if (awr.m_pSchematic == nullptr)
    {
        if (!awr.AddSchematic(L"MatchingNetwork")) {
            return false;
        }
    }
    else
    {
        awr.ClearAllElements();
        awr.ClearAllWires();
    }
    if (awr.AddElement(L"PORT_TN", x, 800, 0))
    {
        awr.SetElementParameter(L"P", L"2");
        awr.SetStringElementParameter(L"NET", L"\"ZL\"");
        awr.SetElementParameter(L"NP", L"1");
    }
    bool prevPar = false;
    for (auto const& val : circuitElements->GetCircuitElements())
    {
        if (val->GetMode() == CapacitorParallel || val->GetMode() == InductionParallel || val->GetMode() == ResistorParallel)
        {
            const wchar_t* type;
            const wchar_t* cotype;
            wchar_t valuestr[64];
            double value;
            bool ground = true;
            if (val->GetMode() == CapacitorParallel)
            {
                type = L"CAP";
                cotype = L"C";
                value = val->GetValue() * 1e12;
                swprintf(valuestr, 64, L"%.2fpF", value);
            }
            else if (val->GetMode() == InductionParallel)
            {
                type = L"IND";
                cotype = L"L";
                value = val->GetValue() * 1e9;
                swprintf(valuestr, 64, L"%.2fnH", value);
            }
            else if (val->GetMode() == ResistorParallel)
            {
                type = L"RES";
                cotype = L"R";
                value = val->GetValue();
                swprintf(valuestr, 64, L"%.2f", value);
            }
            if (prevPar == true)
            {
                x += 500;
            }
            if (awr.AddElement(type, x, 800, 270))
            {
                awr.SetElementParameter(cotype, valuestr);
            }
            if (awr.AddElement(L"GND", x, 1800, 0))
            {
            }
            if (prevPar == true)
            {
                awr.AddWire(x, 800, x - 500, 800);
            }
            prevPar = true;
        }
        else if (val->GetMode() == CapacitorShunt || val->GetMode() == InductionShunt || val->GetMode() == ResistorShunt)
        {
            const wchar_t* type;
            const wchar_t* cotype;
            double value;
            wchar_t valuestr[64];
            if (val->GetMode() == CapacitorShunt)
            {
                type = L"CAP";
                cotype = L"C";
                value = val->GetValue() * 1e12;
                swprintf(valuestr, 64, L"%.2fpF", value);
            }
            else if (val->GetMode() == InductionShunt)
            {
                type = L"IND";
                cotype = L"L";
                value = val->GetValue() * 1e9;
                swprintf(valuestr, 64, L"%.2fnH", value);
            }
            else if (val->GetMode() == ResistorShunt)
            {
                type = L"RES";
                cotype = L"R";
                value = val->GetValue();
                swprintf(valuestr, 64, L"%.2f", value);
            }
            if (awr.AddElement(type, x, 800, 0))
            {
                awr.SetElementParameter(cotype, valuestr);
            }
            x += 1000;
            prevPar = false;
        }
        else if (val->GetMode() == OSLine || val->GetMode() == SSLine || val->GetMode() == Line)
        {
            const wchar_t* type;
            double value;
            double valuez0;
            double valueEeff;
            double valueFreq;
            double angle = 270;
            if (val->GetMode() == OSLine)
            {
                type = L"TLOCP";
            }
            else if (val->GetMode() == SSLine)
            {
                type = L"TLSCP";
            }
            else
            {
                angle = 0;
                type = L"TLINP";
            }
            VerticalLinesElement* temp = dynamic_cast<VerticalLinesElement*>(val);
            value = temp->GetElectricalLength();
            valuez0 = temp->GetValue();
            valueEeff = pow(temp->GetElectricalLength() / temp->GetMechanicalLength(), 2);
            valueFreq = circuitElements->frequencyFirstPoint / 1e6;
            wchar_t valuestr[64];
            swprintf(valuestr, 64, L"%.2fmm", value);
            wchar_t valuez0str[64];
            swprintf(valuez0str, 64, L"%.2f", valuez0);
            wchar_t valueeeffstr[64];
            swprintf(valueeeffstr, 64, L"%.2f", valueEeff);
            wchar_t valuefreqstr[64];
            swprintf(valuefreqstr, 64, L"%.2fMHz", valueFreq);
            if (prevPar == true && val->GetMode() != Line)
            {
                x += 1000;
            }
            if (awr.AddElement(type, x, 800, angle))
            {
                awr.SetElementParameter(L"L", valuestr);
                awr.SetElementParameter(L"Z0", valuez0str);
                awr.SetElementParameter(L"Eeff", valueeeffstr);
                awr.SetElementParameter(L"F0", valuefreqstr);
            }
            if (val->GetMode() == Line)
            {
                x += 1000;
                prevPar = false;
            }
            else
            {
                if (prevPar == true)
                {
                    awr.AddWire(x, 800, x - 1000, 800);
                }
                prevPar = true;
            }
        }
        else if (val->GetMode() == Transform)
        {
            double value = val->GetValue();
            if (prevPar == true)
            {
                x += 1000;
                awr.AddWire(x, 800, x - 1000, 800);
            }
            wchar_t valuestr[64];
            swprintf(valuestr, 64, L"%.2f", value);
            if (awr.AddElement(L"XFMR", x, 800, 0))
            {
                awr.SetElementParameter(L"N", valuestr);
            }
            if (awr.AddElement(L"GND", x, 1000, 0))
            {
            }

            if (awr.AddElement(L"GND", x + 1000, 1000, 0))
            {
            }
            x += 1500;
            awr.AddWire(x, 800, x - 500, 800);
            prevPar = false;
        }

    }
    if (awr.AddElement(L"PORT_TN", x, 800, 180))
    {
        awr.SetElementParameter(L"P", L"1");
        awr.SetStringElementParameter(L"NET", L"\"ZS\"");
        awr.SetElementParameter(L"NP", L"1");
    }
    if (awr.m_port2Schematic == nullptr)
    {
        if (!awr.AddPortSchematic(L"ZS", true)) {
            return false;
        }
    }
    else
    {
        awr.ClearAllPortElements(true);
    }
    if (awr.AddPortElement(L"PORT", 1000, 800, 0, true))
    {
        awr.SetElementParameter(L"P", L"1");
        awr.SetElementParameter(L"Z", L"50");
    }
    if (awr.AddPortElement(L"IMPED", 1000, 800, 270, true))
    {
        double real = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter()[Z].real();
        double imag = -circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter()[Z].imag();
        wchar_t realstr[64];
        swprintf(realstr, 64, L"%.2f", real);
        wchar_t imagstr[64];
        swprintf(imagstr, 64, L"%.2f", imag);
        awr.SetElementParameter(L"R", realstr);
        awr.SetElementParameter(L"X", imagstr);
    }
    if (awr.AddPortElement(L"GND", 1000, 1800, 0, true))
    {

    }


    awr.SetFrequencySweep(1e8, 3e9, 1e8);

    qDebug() << "Saving project...";
    if (awr.SaveProject(L"C:\\Projects\\SmithMatch.emp")) {
        qDebug() << "Project saved successfully!";
        return true;
    }
    
    return false;
}


/// <summary>
/// Получение сигнала об изменении всего (при изменении опорного сопротивления).
/// </summary>
void Smithtry1000::getallchangedsignal()
{
    SystemParameters::sizeChanged = true;
    rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)SystemParameters::z0)));
    if (SystemParameters::index > 0)
    {
        long double Re = circuitElements->z.real();
        long double Im = -circuitElements->z.imag();
        long double x;
        long double y;
        Re /= SystemParameters::z0;
        Im /= SystemParameters::z0;
        long double denominator = (Re + 1) * (Re + 1) + Im * Im;

        if (denominator != 0) {
            x = (Re * Re + Im * Im - 1) / denominator;
            y = (2 * Im) / denominator;
        }
        else {
            x = -1;
            y = 0;
        }
        Point point;
        point.x = x;
        point.y = y;
        circuitElements->firstPoint = point;
        Complex z2 = SystemParameters::zCalculation(x, y);
        Complex y3 = SystemParameters::yCalculation(x, y);
        Complex g;
        if (x >= 0)
        {
            g = Complex(sqrt(pow(x, 2) + pow(y, 2)), atan(y / x) * 180 / M_PI * -1);
        }
        else if (y <= 0)
        {
            g = Complex(sqrt(pow(x, 2) + pow(y, 2)), 180 - atan(y / x) * 180 / M_PI);
        }
        else
        {
            g = Complex(sqrt(pow(x, 2) + pow(y, 2)), -180 - atan(y / x) * 180 / M_PI);
        }
        map<chartMode, tuple<long double, long double>> chart;
        Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(x, y);
        Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(x, y);
        Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(x, y);
        Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(x, y);
        chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
        chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
        chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
        chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
        circuitElements->chart = chart;
        circuitElements->z = z2;
        circuitElements->y = y3;
        circuitElements->g = g;
        ChangeAllElements();
        for (int j = 0; j < circuitElements->morePoints.size(); j++)
        {
            long double temp = SystemParameters::z0;
            SystemParameters::z0 = circuitElements->z0;
            Complex z = SystemParameters::zCalculation(circuitElements->morePoints[j].x, circuitElements->morePoints[j].y);
            SystemParameters::z0 = temp;
            Re = z.real();
            Im = -z.imag();
            Re /= SystemParameters::z0;
            Im /= SystemParameters::z0;
            denominator = (Re + 1) * (Re + 1) + Im * Im;

            if (denominator != 0) {
                x = (Re * Re + Im * Im - 1) / denominator;
                y = (2 * Im) / denominator;
            }
            else {
                x = -1;
                y = 0;
            }
            circuitElements->morePoints[j].x = x;
            circuitElements->morePoints[j].y = y;
        }
        if (SystemParameters::index > 1)
        {
            amplitudeFrequence->MatrixCalculation();
            amplitudeFrequence->update();
        }
        if (SystemParameters::index == 1)
        {
            SystemParameters::lastPointX = circuitElements->firstPoint.x;
            SystemParameters::lastPointY = circuitElements->firstPoint.y;
        }
        else
        {
            SystemParameters::lastPointX = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().x;
            SystemParameters::lastPointY = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().y;
        }
    }
    if (fileName != "")
    {
        sParameters->d3->Load();
        sParameters->d3->update();
        sParameters->d4->Load();
        sParameters->d4->update();
    }

    circuitElements->z0 = SystemParameters::z0;
    renderArea->update();
}

/// <summary>
/// Вспомогательный метод для изменения всех элементов в цепи.
/// </summary>
void Smithtry1000::ChangeAllElements()
{
    long double Re, Im, denominator, x, y;
    Complex z2, y3, g, rRealImpedance, rImagAdmitance, rRealAdmitance, rImagImpedance;
    Point point;
    map<chartMode, tuple<long double, long double>> chart;
    for (int i = 0; i < circuitElements->GetCircuitElements().size(); i++)
    {
        Re = circuitElements->GetCircuitElements()[i]->GetParameter()[Z].real();
        Im = -circuitElements->GetCircuitElements()[i]->GetParameter()[Z].imag();
        Re /= SystemParameters::z0;
        Im /= SystemParameters::z0;
        denominator = (Re + 1) * (Re + 1) + Im * Im;

        if (denominator != 0) {
            x = (Re * Re + Im * Im - 1) / denominator;
            y = (2 * Im) / denominator;
        }
        else {
            x = -1;
            y = 0;
        }
        point.x = x;
        point.y = y;
        circuitElements->GetCircuitElements()[i]->SetPoint(point);
        z2 = SystemParameters::zCalculation(x, y);
        y3 = SystemParameters::yCalculation(x, y);
        map<parameterMode, Complex> parameter;
        parameter[Z] = z2;
        parameter[Y] = y3;
        if (x >= 0)
        {
            g = Complex(sqrt(pow(x, 2) + pow(y, 2)), atan(y / x) * 180 / M_PI * -1);
        }
        else if (y <= 0)
        {
            g = Complex(sqrt(pow(x, 2) + pow(y, 2)), 180 - atan(y / x) * 180 / M_PI);
        }
        else
        {
            g = Complex(sqrt(pow(x, 2) + pow(y, 2)), -180 - atan(y / x) * 180 / M_PI);
        }
        parameter[G] = g;
        rRealImpedance = SystemParameters::impedanceRealChartParameters(x, y);
        rImagImpedance = SystemParameters::impedanceImagChartParameters(x, y);
        rRealAdmitance = SystemParameters::admitanceRealChartParameters(x, y);
        rImagAdmitance = SystemParameters::admitanceImagChartParameters(x, y);
        chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
        chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
        chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
        chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
        circuitElements->GetCircuitElements()[i]->SetChartParameters(chart);
        circuitElements->GetCircuitElements()[i]->SetParameter(parameter);
        pointsX[i] = x;
        pointsY[i] = y;
    }
}

/// <summary>
/// Обработка перед закрытием окна.
/// </summary>
/// <param name="event"></param>
void Smithtry1000::closeEvent(QCloseEvent* event)
{
    this->amplitudeFrequence->close();
    this->tuneWidget->close();
    this->sParameters->Close();
    SystemParameters::SaveToJSON();
    this->circlesWidget->close();
    if (SystemParameters::edit)
    {
        edit->close();
    }
}

/// <summary>
/// Нажатие на кнопку кругов.
/// </summary>
void Smithtry1000::onCirclesClicked()
{
    circlesWidget->show();
    circlesWidget->activateWindow();
}

/// <summary>
/// Получение сигнала о выбранном/убранном круге.
/// </summary>
void Smithtry1000::getCirclesSignal()
{
    renderArea->update();
}

/// <summary>
/// Сохранение проекта.
/// </summary>
void Smithtry1000::Save()
{
    if (SystemParameters::index > 1)
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Save the project", QDir::homePath() + "/project.SC", "SC Files (*.SC)");
        try
        {
            circuitElements->saveToFile(fileName);
        }
        catch (exception e)
        {

        }
    }
    else
    {
        QMessageBox* bx = new QMessageBox();
        bx->show();
        bx->Information;
        bx->setText(QStringLiteral(u"Добавьте хотя бы 1 элемент в цепь."));
    }
}

/// <summary>
/// Экспорт в САПР.
/// </summary>
void Smithtry1000::CAD_export()
{
    if (SystemParameters::index > 1)
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Save the project", QDir::homePath() + "/project.json", "JSON Files (*.json)");
        try
        {
            circuitElements->saveToJSON(fileName);
        }
        catch (exception e)
        {

        }
    }
    else
    {
        QMessageBox* bx = new QMessageBox();
        bx->show();
        bx->Information;
        bx->setText(QStringLiteral(u"Добавьте хотя бы 1 элемент в цепь."));
    }
}

/// <summary>
/// Восстановление отмененных действий.
/// </summary>
void Smithtry1000::Redo()
{
    bool areEqual = true;
    QList<Element*> list1 = tempCircuit.GetCircuitElements();
    QList<Element*> list2 = circuitElements->GetCircuitElements();

    if (list1.size() != list2.size())
    {
        areEqual = false;
    }

    QList<Point> list3 = tempCircuit.morePoints;
    QList<Point> list4 = circuitElements->morePoints;
    if (list3.size() != list4.size()) {
        areEqual = false;
    }

    if (!areEqual || circuitElements->firstPoint.x != tempCircuit.firstPoint.x || circuitElements->firstPoint.y != tempCircuit.firstPoint.y)
    {
        timer->stop();
        firstDeleted = true;
        if (tempCircuit.elementIndexes.contains(SystemParameters::allpointindex))
        {
            RedoElement();
        }
        else if (tempCircuit.pointIndexes.contains(SystemParameters::allpointindex))
        {
            RedoPoints();
        }
        else
        {
            circuitElements->chart = tempCircuit.chart;
            circuitElements->firstPoint = tempCircuit.firstPoint;
            circuitElements->frequencyFirstPoint = tempCircuit.frequencyFirstPoint;
            rTable->setItem(3, 3, new QTableWidgetItem(QString::number((double)circuitElements->frequencyFirstPoint)));
            circuitElements->z = tempCircuit.z;
            circuitElements->y = tempCircuit.y;
            circuitElements->g = tempCircuit.g;
            circuitElements->imagFirstPoint = tempCircuit.imagFirstPoint;
            circuitElements->realFirstPoint = tempCircuit.realFirstPoint;
            circuitElements->frequencyList.append(tempCircuit.frequencyList[circuitElements->frequencyList.size()]);
            int row = pointTable->rowCount();
            pointTable->insertRow(row);
            pointTable->setItem(row, 0, new QTableWidgetItem(QStringLiteral(u"Да")));
            pointTable->setItem(row, 1, new QTableWidgetItem("DP 1"));
            SystemParameters::rImpedanceRealCalculation(circuitElements->firstPoint.x, circuitElements->firstPoint.y);
            SystemParameters::rImpedanceImagCalculation(circuitElements->firstPoint.x, circuitElements->firstPoint.y);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
            if (SystemParameters::impedanceRealR == 0)
            {
                pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
            }
            pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)circuitElements->frequencyFirstPoint)));
            pointsX.append(circuitElements->firstPoint.x);
            pointsY.append(circuitElements->firstPoint.y);
            allPoints[SystemParameters::allpointindex] = make_tuple(circuitElements->firstPoint, false);
            SystemParameters::index++;
            SystemParameters::dpIndex++;
        }
        SystemParameters::allpointindex++;
        if (SystemParameters::index > 1)
        {
            amplitudeFrequence->MatrixCalculation();
            if (!amplitudeFrequence->isHidden())
            {
                amplitudeFrequence->show();
            }
        }
        renderArea->update();
        auxiliaryWidget->update();
        timer->start();
    }
}

/// <summary>
/// Преобразование режима работы элемента в имя элемента (путь).
/// </summary>
/// <param name="name">Имя/путь.</param>
/// <param name="mood">Режим.</param>
/// <param name="j">Номер элемента в списке.</param>
void Smithtry1000::SwitchElementName(QString& name, bool& mood, int j)
{
    switch (circuitElements->GetCircuitElements()[j]->GetMode())
    {
    case ResistorShunt:
    {
        name = "horizontal_r";
        mood = true;
        break;
    }
    case ResistorParallel:
    {
        name = "vertical_r_circuit";
        mood = false;
        break;
    }
    case CapacitorShunt:
    {
        name = "horizontal_c";
        mood = true;
        break;
    }
    case CapacitorParallel:
    {
        name = "vertical_c_circuit";
        mood = false;
        break;
    }
    case InductionShunt:
    {
        name = "horizontal_i";
        mood = true;
        break;
    }
    case InductionParallel:
    {
        name = "vertical_i_circuit";
        mood = false;
        break;
    }
    case Line:
    {
        name = "horizontal_line_circuit";
        mood = true;
        break;
    }
    case OSLine:
    {
        name = "os_circuit";
        mood = false;
        break;
    }
    case SSLine:
    {
        name = "ss_circuit";
        mood = false;
        break;
    }
    case Transform:
    {
        name = "vertical_transform_circuit";
        mood = false;
        break;
    }
    }
}

/// <summary>
/// Восстановление элемента.
/// </summary>
void Smithtry1000::RedoElement()
{
    circuitElements->AddCircuitElements(tempCircuit.GetCircuitElements()[circuitElements->GetCircuitElements().size()]);
    circuitElements->elementIndexes.append(tempCircuit.elementIndexes[circuitElements->elementIndexes.size()]);
    int row = pointTable->rowCount();
    pointTable->insertRow(row);
    pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(SystemParameters::index + SystemParameters::dpIndex)));
    SystemParameters::rImpedanceRealCalculation(circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().x, circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().y);
    SystemParameters::rImpedanceImagCalculation(circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().x, circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().y);
    QString temp2 = " + j";
    if (SystemParameters::impedanceImagR < 0)
    {
        temp2 = " - j";
    }
    pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
    if (SystemParameters::impedanceRealR == 0)
    {
        pointTable->setItem(row, 3, new QTableWidgetItem("0"));
    }
    else
    {
        pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
    }
    pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)circuitElements->frequencyFirstPoint)));
    QString name;
    bool mood = true;
    SwitchElementName(name, mood, circuitElements->GetCircuitElements().size() - 1);
    int val;
    if (mood)
    {
        val = 20;
    }
    else
    {
        val = 39;
    }
    if (SystemParameters::rotate)
    {
        QString rev = "rev_";
        auxiliaryWidget->addSvg(QString(":/Images/" + rev + name + ".svg"), val + 40, (circuitElements->GetCircuitElements().size() - 1 + 2) * 40);
    }
    else
    {
        auxiliaryWidget->addSvg(QString(":/Images/" + name + ".svg"), (circuitElements->GetCircuitElements().size() - 1 + 3) * 40, val);
    }
    Point point;
    point.x = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().x;
    point.y = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().y;
    allPoints[SystemParameters::allpointindex] = make_tuple(point, true);
    pointsX.append(point.x);
    pointsY.append(point.y);
    SystemParameters::index++;
}

/// <summary>
/// Восстановление точек.
/// </summary>
void Smithtry1000::RedoPoints()
{
    circuitElements->morePoints.append(tempCircuit.morePoints[circuitElements->morePoints.size()]);
    circuitElements->pointIndexes.append(tempCircuit.pointIndexes[circuitElements->pointIndexes.size()]);
    circuitElements->frequencyList.append(tempCircuit.frequencyList[circuitElements->frequencyList.size()]);
    int row = pointTable->rowCount();
    pointTable->insertRow(row);
    pointTable->setItem(row, 0, new QTableWidgetItem(QStringLiteral(u"Нет")));
    pointTable->setItem(row, 1, new QTableWidgetItem("DP " + QString::number(circuitElements->morePoints.size() + 1)));
    SystemParameters::rImpedanceRealCalculation(circuitElements->morePoints[circuitElements->morePoints.size() - 1].x, circuitElements->morePoints[circuitElements->morePoints.size() - 1].y);
    SystemParameters::rImpedanceImagCalculation(circuitElements->morePoints[circuitElements->morePoints.size() - 1].x, circuitElements->morePoints[circuitElements->morePoints.size() - 1].y);
    QString temp2 = " + j";
    if (SystemParameters::impedanceImagR < 0)
    {
        temp2 = " - j";
    }
    pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
    if (SystemParameters::impedanceRealR == 0)
    {
        pointTable->setItem(row, 3, new QTableWidgetItem("0"));
    }
    else
    {
        pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
    }
    pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)circuitElements->frequencyList[circuitElements->frequencyList.size() - 1])));
    Point point;
    point.x = circuitElements->morePoints[circuitElements->morePoints.size() - 1].x;
    point.y = circuitElements->morePoints[circuitElements->morePoints.size() - 1].y;
    allPoints[SystemParameters::allpointindex] = make_tuple(point, false);
    SystemParameters::dpIndex++;
}

/// <summary>
/// Загрузка проекта.
/// </summary>
void Smithtry1000::Load()
{
    SaveBeforeLoad();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open project"), "", tr("SC Files (*.SC)"));
    if (fileName != "")
    {
        try
        {
            if (circuitElements->loadFromFile(fileName))
            {
                auxiliaryWidget->circuitElements = circuitElements;
                amplitudeFrequence->circuitElements = circuitElements;
                renderArea->circuitElements = circuitElements;
                tuneWidget->circuitElements = circuitElements;
                circlesWidget->circuitElements = circuitElements;
                SystemParameters::dpIndex = circuitElements->morePoints.size() + 1;
                SystemParameters::index = circuitElements->GetCircuitElements().size() + 1;
                long double Re = circuitElements->z.real();
                long double Im = -circuitElements->z.imag();
                long double x;
                long double y;
                Re /= SystemParameters::z0;
                Im /= SystemParameters::z0;
                long double denominator = (Re + 1) * (Re + 1) + Im * Im;

                if (denominator != 0) {
                    x = (Re * Re + Im * Im - 1) / denominator;
                    y = (2 * Im) / denominator;
                }
                else {
                    x = -1;
                    y = 0;
                }
                CorrectZ0(x, y);
                allPoints[0] = make_tuple(circuitElements->firstPoint, false);
                pointsX.append(circuitElements->firstPoint.x);
                pointsY.append(circuitElements->firstPoint.y);
                int row = pointTable->rowCount();
                pointTable->insertRow(row);
                pointTable->setItem(row, 0, new QTableWidgetItem(QStringLiteral(u"Да")));
                pointTable->setItem(row, 1, new QTableWidgetItem("DP 1"));
                SystemParameters::rImpedanceRealCalculation(circuitElements->firstPoint.x, circuitElements->firstPoint.y);
                SystemParameters::rImpedanceImagCalculation(circuitElements->firstPoint.x, circuitElements->firstPoint.y);
                QString temp2 = " + j";
                if (SystemParameters::impedanceImagR < 0)
                {
                    temp2 = " - j";
                }
                pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
                if (SystemParameters::impedanceRealR == 0)
                {
                    pointTable->setItem(row, 3, new QTableWidgetItem("0"));
                }
                else
                {
                    pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
                }
                pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)circuitElements->frequencyFirstPoint)));
                LoadElementsAndPoints();
                SystemParameters::allpointindex = SystemParameters::index + circuitElements->morePoints.size();
                auxiliaryWidget->circuitElements = circuitElements;
                amplitudeFrequence->circuitElements = circuitElements;
                renderArea->circuitElements = circuitElements;
                tuneWidget->circuitElements = circuitElements;
                circlesWidget->circuitElements = circuitElements;
                renderArea->update();
                auxiliaryWidget->update();
                firstDeleted = true;
                emit load();
            }
            else
            {
                QMessageBox* bx = new QMessageBox();
                bx->show();
                bx->Warning;
                bx->setText(QStringLiteral(u"Произошла ошибка во время загрузки проекта"));
                SystemParameters::exc = false;
            }
        }
        catch (exception e)
        {

        }
    }
}

/// <summary>
/// Сохранение перед загрузкой.
/// </summary>
void Smithtry1000::SaveBeforeLoad()
{
    if (SystemParameters::index > 1)
    {
        PreSaveDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted)
        {
            QString fileName = QFileDialog::getSaveFileName(this, "Save the project", QDir::homePath() + "/project.SC", "SC Files (*.SC)");
            try
            {
                circuitElements->saveToFile(fileName);
            }
            catch (exception e)
            {

            }
        }
        SystemParameters::allpointindex = 0;
        SystemParameters::dpIndex = 0;
        SystemParameters::index = 0;
        SystemParameters::tunedElements.clear();
        SystemParameters::edited = false;
        SystemParameters::tuned = false;
        SystemParameters::tune = false;
        SystemParameters::tuneBlock = false;
        SystemParameters::edit = false;
        tuneWidget->RemoveOnLoad();
        sParameters->set->hide();
        sParameters->Close();
        amplitudeFrequence->hide();
        circlesWidget->hide();
        if (SystemParameters::edit)
        {
            edit->close();
        }
        while (SystemParameters::svgWidgets.size() > 2)
        {
            auxiliaryWidget->removeLastSvg();
        }
        pointsX.clear();
        pointsY.clear();
        while (circuitElements->GetCircuitElements().size() > 0)
        {
            circuitElements->DeleteCircuitElements();
        }
        circuitElements->morePoints.clear();
        circuitElements->VSWRCircles.clear();
        circuitElements->QCircles.clear();
        circuitElements->elementIndexes.clear();
        circuitElements->pointIndexes.clear();
        circuitElements->frequencyList.clear();
        circuitElements->imagFirstPoint = -9999;
        circuitElements->realFirstPoint = -9999;
        circuitElements->frequencyFirstPoint = -9999;
        circuitElements->z = Complex(-9999, -9999);
        circuitElements->y = Complex(-9999, -9999);
        circuitElements->g = Complex(-9999, -9999);
        circuitElements = new CircuitElements();
        while (tempCircuit.GetCircuitElements().size() > 0)
        {
            tempCircuit.DeleteCircuitElements();
        }
        tempCircuit.morePoints.clear();
        tempCircuit.VSWRCircles.clear();
        tempCircuit.QCircles.clear();
        tempCircuit.elementIndexes.clear();
        tempCircuit.pointIndexes.clear();
        tempCircuit.frequencyList.clear();
        tempCircuit = CircuitElements();
        lastPos = QPoint(0, 0);
        firstDeleted = true;
        allPoints.clear();
        pointTable->setRowCount(1);
    }
}

/// <summary>
/// Изменение координат элементов в зависимости от z0.
/// </summary>
/// <param name="x">x.</param>
/// <param name="y">y.</param>
void Smithtry1000::CorrectZ0(long double x, long double y)
{
    if (x != circuitElements->firstPoint.x || y != circuitElements->firstPoint.y)
    {
        rTable->setItem(3, 3, new QTableWidgetItem(QString::number((double)circuitElements->frequencyFirstPoint)));
        Point point;
        point.x = x;
        point.y = y;
        circuitElements->firstPoint = point;
        Complex z2 = SystemParameters::zCalculation(x, y);
        Complex y3 = SystemParameters::yCalculation(x, y);
        Complex g;
        if (x >= 0)
        {
            g = Complex(sqrt(pow(x, 2) + pow(y, 2)), atan(y / x) * 180 / M_PI * -1);
        }
        else if (y <= 0)
        {
            g = Complex(sqrt(pow(x, 2) + pow(y, 2)), 180 - atan(y / x) * 180 / M_PI);
        }
        else
        {
            g = Complex(sqrt(pow(x, 2) + pow(y, 2)), -180 - atan(y / x) * 180 / M_PI);
        }
        map<chartMode, tuple<long double, long double>> chart;
        Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(x, y);
        Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(x, y);
        Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(x, y);
        Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(x, y);
        chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
        chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
        chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
        chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
        circuitElements->chart = chart;
        circuitElements->z = z2;
        circuitElements->y = y3;
        circuitElements->g = g;
        long double Re, Im, denominator;
        for (int i = 0; i < circuitElements->GetCircuitElements().size(); i++)
        {
            Re = circuitElements->GetCircuitElements()[i]->GetParameter()[Z].real();
            Im = -circuitElements->GetCircuitElements()[i]->GetParameter()[Z].imag();
            Re /= SystemParameters::z0;
            Im /= SystemParameters::z0;
            denominator = (Re + 1) * (Re + 1) + Im * Im;

            if (denominator != 0) {
                x = (Re * Re + Im * Im - 1) / denominator;
                y = (2 * Im) / denominator;
            }
            else {
                x = -1;
                y = 0;
            }
            point.x = x;
            point.y = y;
            circuitElements->GetCircuitElements()[i]->SetPoint(point);
            z2 = SystemParameters::zCalculation(x, y);
            y3 = SystemParameters::yCalculation(x, y);
            map<parameterMode, Complex> parameter;
            parameter[Z] = z2;
            parameter[Y] = y3;
            if (x >= 0)
            {
                g = Complex(sqrt(pow(x, 2) + pow(y, 2)), atan(y / x) * 180 / M_PI * -1);
            }
            else if (y <= 0)
            {
                g = Complex(sqrt(pow(x, 2) + pow(y, 2)), 180 - atan(y / x) * 180 / M_PI);
            }
            else
            {
                g = Complex(sqrt(pow(x, 2) + pow(y, 2)), -180 - atan(y / x) * 180 / M_PI);
            }
            parameter[G] = g;
            rRealImpedance = SystemParameters::impedanceRealChartParameters(x, y);
            rImagImpedance = SystemParameters::impedanceImagChartParameters(x, y);
            rRealAdmitance = SystemParameters::admitanceRealChartParameters(x, y);
            rImagAdmitance = SystemParameters::admitanceImagChartParameters(x, y);
            chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
            chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
            chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
            chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
            circuitElements->GetCircuitElements()[i]->SetChartParameters(chart);
            circuitElements->GetCircuitElements()[i]->SetParameter(parameter);
        }
        for (int j = 0; j < circuitElements->morePoints.size(); j++)
        {
            long double temp = SystemParameters::z0;
            SystemParameters::z0 = circuitElements->z0;
            Complex z = SystemParameters::zCalculation(circuitElements->morePoints[j].x, circuitElements->morePoints[j].y);
            SystemParameters::z0 = temp;
            Re = z.real();
            Im = -z.imag();
            Re /= SystemParameters::z0;
            Im /= SystemParameters::z0;
            denominator = (Re + 1) * (Re + 1) + Im * Im;

            if (denominator != 0) {
                x = (Re * Re + Im * Im - 1) / denominator;
                y = (2 * Im) / denominator;
            }
            else {
                x = -1;
                y = 0;
            }
            circuitElements->morePoints[j].x = x;
            circuitElements->morePoints[j].y = y;
        }
    }
}

/// <summary>
/// Загрузка элементов и точек.
/// </summary>
void Smithtry1000::LoadElementsAndPoints()
{
    QString name;
    int count = circuitElements->GetCircuitElements().size();
    int j = 0;
    int k = 0;
    for (int i = 0; i < circuitElements->GetCircuitElements().size() + circuitElements->morePoints.size(); i++)
    {
        if (j != count)
        {
            if (circuitElements->elementIndexes[j] == i + 1)
            {
                int row = pointTable->rowCount();
                pointTable->insertRow(row);
                pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(i + 2)));
                SystemParameters::rImpedanceRealCalculation(circuitElements->GetCircuitElements()[j]->GetPoint().x, circuitElements->GetCircuitElements()[j]->GetPoint().y);
                SystemParameters::rImpedanceImagCalculation(circuitElements->GetCircuitElements()[j]->GetPoint().x, circuitElements->GetCircuitElements()[j]->GetPoint().y);
                QString temp2 = " + j";
                if (SystemParameters::impedanceImagR < 0)
                {
                    temp2 = " - j";
                }
                pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
                if (SystemParameters::impedanceRealR == 0)
                {
                    pointTable->setItem(row, 3, new QTableWidgetItem("0"));
                }
                else
                {
                    pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
                }
                pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)circuitElements->frequencyFirstPoint)));
                allPoints[i + 1] = make_tuple(circuitElements->GetCircuitElements()[j]->GetPoint(), true);
                bool mood;
                SwitchElementName(name, mood, j);
                int val;
                if (mood == false)
                {
                    val = 39;
                }
                else
                {
                    val = 20;
                }
                if (SystemParameters::rotate)
                {
                    QString rev = "rev_";
                    auxiliaryWidget->addSvg(QString(":/Images/" + rev + name + ".svg"), val + 40, (j + 2) * 40);
                }
                else
                {
                    auxiliaryWidget->addSvg(QString(":/Images/" + name + ".svg"), (j + 3) * 40, val);
                }
                pointsX.append(circuitElements->GetCircuitElements()[j]->GetPoint().x);
                pointsY.append(circuitElements->GetCircuitElements()[j]->GetPoint().y);
                j++;
            }
            else
            {
                int row = pointTable->rowCount();
                pointTable->insertRow(row);
                pointTable->setItem(row, 0, new QTableWidgetItem(QStringLiteral(u"Нет")));
                pointTable->setItem(row, 1, new QTableWidgetItem("DP " + QString::number(i + 2)));
                SystemParameters::rImpedanceRealCalculation(circuitElements->morePoints[k].x, circuitElements->morePoints[k].y);
                SystemParameters::rImpedanceImagCalculation(circuitElements->morePoints[k].x, circuitElements->morePoints[k].y);
                QString temp2 = " + j";
                if (SystemParameters::impedanceImagR < 0)
                {
                    temp2 = " - j";
                }
                pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
                if (SystemParameters::impedanceRealR == 0)
                {
                    pointTable->setItem(row, 3, new QTableWidgetItem("0"));
                }
                else
                {
                    pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
                }
                pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)circuitElements->frequencyList[k + 1])));
                allPoints[i + 1] = make_tuple(circuitElements->morePoints[k], false);
                k++;
            }
        }
        else
        {
            int row = pointTable->rowCount();
            pointTable->insertRow(row);
            pointTable->setItem(row, 0, new QTableWidgetItem(QStringLiteral(u"Нет")));
            pointTable->setItem(row, 1, new QTableWidgetItem("DP " + QString::number(i + 2)));
            SystemParameters::rImpedanceRealCalculation(circuitElements->morePoints[k].x, circuitElements->morePoints[k].y);
            SystemParameters::rImpedanceImagCalculation(circuitElements->morePoints[k].x, circuitElements->morePoints[k].y);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
            if (SystemParameters::impedanceRealR == 0)
            {
                pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
            }
            pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)circuitElements->frequencyList[k + 1])));
            allPoints[i + 1] = make_tuple(circuitElements->morePoints[k], false);
            k++;
        }
    }
}

/// <summary>
/// Сохранение изображения проекта.
/// </summary>
void Smithtry1000::Copy()
{
    SaveDialog dialog(this);
    {
        if (dialog.exec() == QDialog::Accepted)
        {
            QWidget* widget;
            if (SystemParameters::saved == 0)
            {
                widget = renderArea;
            }
            else
            {
                widget = auxiliaryWidget;
            }
            QString fileName = QFileDialog::getSaveFileName(this, "Save the graph", QDir::homePath() + "/graph.png", "PNG Files (*.png);;JPEG Files (*.jpg);;PDF Files (*.pdf)");

            QPixmap pixmap(widget->size());
            widget->render(&pixmap);

            QString extension = QFileInfo(fileName).suffix().toLower();

            if (extension == "pdf") {
                QPrinter printer(QPrinter::HighResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName(fileName);
                printer.setPageSize(QPageSize(widget->size() / 10, QPageSize::Point));

                QPainter painter(&printer);
                widget->render(&painter);
                painter.end();
            }
            else if (extension == "jpg" || extension == "jpeg") {
                pixmap.save(fileName, "JPG", 90);
            }
            else if (extension == "png") {
                pixmap.save(fileName, "PNG");
            }
            else {
                // По умолчанию сохраняем как PNG
                pixmap.save(fileName + ".png", "PNG");
            }
        }
    }
}

/// <summary>
/// Трансформатор.
/// </summary>
void Smithtry1000::onTransform_buttonClicked()
{
    long double y0 = 0;
    if (circuitElements->GetCircuitElements().size() > 0)
    {
        y0 = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().y;
    }
    else if (SystemParameters::index > 0)
    {
        y0 = circuitElements->firstPoint.y;
    }
    if (SystemParameters::index > 0)
    {
        SystemParameters::Model = mode::Transform;
        auxiliaryWidget->update();
        leftClicked = false;
        rightClicked = false;
        QPoint centerLocal = renderArea->rect().center();
        QPoint centerGlobal = renderArea->mapToGlobal(centerLocal);
        Complex zl, yl;
        if (!SystemParameters::rotate)
        {
            auxiliaryWidget->addSvg(QString(":/Images/vertical_transform_circuit.svg"), (SystemParameters::index + 2) * 40, 39);
        }
        else
        {
            auxiliaryWidget->addSvg(QString(":/Images/rev_vertical_transform_circuit.svg"), 79, (SystemParameters::index + 1) * 40);
        }
        QCursor::setPos(centerGlobal);
        this->setCursor(Qt::BlankCursor);
        long double x;
        long double y;
        if (circuitElements->GetCircuitElements().size() > 0)
        {
            yl = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter()[Y];
            zl = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter()[Z];
            x = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().x;
            y = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().y;
        }
        else
        {
            yl = circuitElements->y;
            zl = circuitElements->z;
            x = circuitElements->firstPoint.x;
            y = circuitElements->firstPoint.y;
        }
        if (abs(y) <= 0.01)
        {
            SystemParameters::resistorLinear = true;
            long double denominator = (1 - x) * (1 - x) + y * y;

            if (denominator > 1e-12) {
                r = (1 - x * x - y * y) / denominator;
                if (y < 0)
                {
                    r = fabs(r);
                }
                else
                {
                    r = fabs(r) * -1;
                }
            }
            t = M_PI * 3 / 2 - 0.02;
        }
        else
        {
            long double q = zl.imag() / zl.real();
            long double ycenter = -1 / q;
            long double R = sqrt(1 + 1 / pow(q, 2));
            long double dx = x;
            long double dy = y + ycenter;
            long double sin_t = dy;
            long double cos_t = dx;
            t = atan(sin_t / cos_t);
            if (cos_t >= 0)
            {
                t *= -1;
            }
            else if (sin_t <= 0)
            {
                t = M_PI - t;
            }
            else
            {
                t = -M_PI - t;
            }
            r = ycenter;
            tmin = -M_PI + 0.02;
            tmax = M_PI - 0.02;
        }
        trackingEnabled = !trackingEnabled;
        while (!leftClicked && !rightClicked)
        {
            QCoreApplication::processEvents();
        }
        if (leftClicked)
        {
            AppendTransformer(zl);
        }
        if (rightClicked)
        {
            QPoint temp = QPoint(pointsX.back() * SystemParameters::scale + renderArea->rect().center().x(), pointsY.back() * SystemParameters::scale + renderArea->rect().center().y());
            renderArea->setCursorPosOnCircle(temp);
            auxiliaryWidget->removeLastSvg();
            auxiliaryWidget->update();
        }
        SystemParameters::resistorLinear = false;
        this->unsetCursor(); // возвращаем курсор
        SystemParameters::Model = Default;
    }
    else
    {
        QMessageBox* bx = new QMessageBox();
        bx->show();
        bx->Information;
        bx->setText(QStringLiteral(u"Добавьте стартовую точку."));
    }
}

/// <summary>
/// Добавление трансформатора в цепь.
/// </summary>
/// <param name="zl">Комплексное сопротивление прошлой точки.</param>
void Smithtry1000::AppendTransformer(Complex zl)
{
    SystemParameters::rAdmitanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Point point;
    point.x = SystemParameters::lastPointX;
    point.y = SystemParameters::lastPointY;
    allPoints[SystemParameters::index + SystemParameters::dpIndex - 1] = make_tuple(point, true);
    Complex z = SystemParameters::zCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex y2 = SystemParameters::yCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    map<parameterMode, Complex> parameter;
    parameter[Z] = z;
    parameter[Y] = y2;
    Complex g;
    if (point.x >= 0)
    {
        g = Complex(sqrt(pow(point.x, 2) + pow(point.y, 2)), atan(point.y / point.x) * 180 / M_PI * -1);
    }
    else if (point.y <= 0)
    {
        g = Complex(sqrt(pow(point.x, 2) + pow(point.y, 2)), 180 - atan(point.y / point.x) * 180 / M_PI);
    }
    else
    {
        g = Complex(sqrt(pow(point.x, 2) + pow(point.y, 2)), -180 - atan(point.y / point.x) * 180 / M_PI);
    }
    parameter[G] = g;
    map<chartMode, tuple<long double, long double>> chart;
    Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
    chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
    chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
    chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
    long double n = sqrt(z.real() / zl.real());
    this->circuitElements->AddCircuitElements(new Element(Transform, n, this->circuitElements->frequencyFirstPoint, point, chart, parameter));
    pointsX.append(SystemParameters::lastPointX);
    pointsY.append(SystemParameters::lastPointY);
    QPoint temp = QPoint(SystemParameters::lastPointX * SystemParameters::scale + renderArea->rect().center().x(), SystemParameters::lastPointY * SystemParameters::scale + renderArea->rect().center().y());
    int row = pointTable->rowCount();
    pointTable->insertRow(row);
    pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(SystemParameters::index + SystemParameters::dpIndex)));
    SystemParameters::rImpedanceRealCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    SystemParameters::rImpedanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    QString temp2 = " + j";
    if (SystemParameters::impedanceImagR < 0)
    {
        temp2 = " - j";
    }
    pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
    if (SystemParameters::impedanceRealR == 0)
    {
        pointTable->setItem(row, 3, new QTableWidgetItem("0"));
    }
    else
    {
        pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
    }
    pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)this->circuitElements->frequencyFirstPoint)));
    circuitElements->elementIndexes.append(SystemParameters::allpointindex);
    SystemParameters::index++;
    SystemParameters::allpointindex++;
    renderArea->setCursorPosOnCircle(temp);
    tempCircuit = *circuitElements;
    firstDeleted = true;
    amplitudeFrequence->MatrixCalculation();
    if (!amplitudeFrequence->isHidden())
    {
        amplitudeFrequence->show();
    }
}

/// <summary>
/// Линия передач.
/// </summary>
void Smithtry1000::onLine_buttonClicked()
{
    if (SystemParameters::index > 0)
    {
        LinesDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted && !SystemParameters::exc)
        {
            SystemParameters::Model = mode::Line;
            auxiliaryWidget->update();
            leftClicked = false;
            rightClicked = false;
            QPoint centerLocal = renderArea->rect().center();
            QPoint centerGlobal = renderArea->mapToGlobal(centerLocal);
            Complex zl, yl;
            if (!SystemParameters::rotate)
            {
                auxiliaryWidget->addSvg(QString(":/Images/horizontal_line_circuit.svg"), (SystemParameters::index + 2) * 40, 20);
            }
            else
            {
                auxiliaryWidget->addSvg(QString(":/Images/rev_horizontal_line_circuit.svg"), 60, (SystemParameters::index + 1) * 40);
            }
            QCursor::setPos(centerGlobal);
            this->setCursor(Qt::BlankCursor); // скрываем системный курсор
            long double x;
            long double y;
            if (circuitElements->GetCircuitElements().size() > 0)
            {
                yl = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter()[Y];
                zl = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter()[Z];
                x = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().x;
                y = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().y;
            }
            else
            {
                yl = circuitElements->y;
                zl = circuitElements->z;
                x = circuitElements->firstPoint.x;
                y = circuitElements->firstPoint.y;
            }
            if (y >= 0 && y < 0.0001)
            {
                y = 0.0001;
            }
            else if (y <= 0 && y > -0.0001)
            {
                y = -0.0001;
            }
            Complex g1 = (zl - SystemParameters::z0) / (zl + SystemParameters::z0);
            Complex z3 = SystemParameters::z0line * (zl + Complex(0, SystemParameters::z0line)) / (SystemParameters::z0line + Complex(0, 1) * zl);
            Complex g3 = (z3 - SystemParameters::z0) / (z3 + SystemParameters::z0);
            long double center = 0.5 * (pow(g1.real(), 2) + pow(g1.imag(), 2) - pow(g3.real(), 2) - pow(g3.imag(), 2)) / (g1.real() - g3.real());
            long double R = abs(center - g1);
            long double dx = x - center;
            long double dy = y;
            dy *= -1;
            long double sin_t = dy;
            long double cos_t = dx;
            t = atan(sin_t / cos_t);
            if (cos_t >= 0)
            {
                t *= -1;
            }
            else if (sin_t <= 0)
            {
                t = M_PI - t;
            }
            else
            {
                t = -M_PI - t;
            }
            r = center;
            tmin = -M_PI;
            tmax = M_PI;
            trackingEnabled = !trackingEnabled;
            while (!leftClicked && !rightClicked)
            {
                QCoreApplication::processEvents();
            }
            if (leftClicked)
            {
                AppendLine(zl);
            }
            if (rightClicked)
            {
                QPoint temp = QPoint(pointsX.back() * SystemParameters::scale + renderArea->rect().center().x(), pointsY.back() * SystemParameters::scale + renderArea->rect().center().y());
                renderArea->setCursorPosOnCircle(temp);
                auxiliaryWidget->removeLastSvg();
                auxiliaryWidget->update();
            }
            this->unsetCursor(); // возвращаем курсор
            SystemParameters::Model = Default;
        }
        else if (SystemParameters::exc)
        {
            QMessageBox* bx = new QMessageBox();
            bx->show();
            bx->Warning;
            bx->setText(QStringLiteral(u"Все параметры должны быть заданы положительными числами"));
            SystemParameters::exc = false;
        }
    }
    else
    {
        QMessageBox* bx = new QMessageBox();
        bx->show();
        bx->Information;
        bx->setText(QStringLiteral(u"Добавьте стартовую точку."));
    }
}

/// <summary>
/// Добавление линии передач в цепь.
/// </summary>
/// <param name="zl">Комплексное сопротивление прошлой точки.</param>
void Smithtry1000::AppendLine(Complex zl)
{
    SystemParameters::rAdmitanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Point point;
    point.x = SystemParameters::lastPointX;
    point.y = SystemParameters::lastPointY;
    long double x = point.x;
    long double y = point.y;
    allPoints[SystemParameters::index + SystemParameters::dpIndex - 1] = make_tuple(point, true);
    Complex z = SystemParameters::zCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex y2 = SystemParameters::yCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    map<parameterMode, Complex> parameter;
    parameter[Z] = z;
    parameter[Y] = y2;
    Complex g;
    if (x >= 0)
    {
        g = Complex(sqrt(pow(x, 2) + pow(y, 2)), atan(y / x) * 180 / M_PI * -1);
    }
    else if (y <= 0)
    {
        g = Complex(sqrt(pow(x, 2) + pow(y, 2)), 180 - atan(y / x) * 180 / M_PI);
    }
    else
    {
        g = Complex(sqrt(pow(x, 2) + pow(y, 2)), -180 - atan(y / x) * 180 / M_PI);
    }
    parameter[G] = g;
    map<chartMode, tuple<long double, long double>> chart;
    Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
    chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
    chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
    chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
    long double RL = zl.real();
    long double XL = zl.imag();
    long double R = z.real();
    long double X = z.imag();
    long double RR = R - RL;
    long double sq = -sqrt(RR * (RL * (pow(X, 2) + pow(R, 2)) - R * (pow(XL, 2) + pow(RL, 2)))) / RR;
    long double tanO1 = RR * sq / (R * XL + RL * X);
    long double tanO2 = -RR * sq / (R * XL + RL * X);
    long double z0;
    long double O;
    if (sq > 0)
    {
        z0 = sq;
        O = atan(tanO1);
    }
    else
    {
        z0 = -sq;
        O = atan(tanO2);
    }
    if (O < 0)
    {
        O += M_PI;
    }
    long double Theta = O * 180 / M_PI;
    long double L = O * 299792458 / (2 * M_PI * 1e9);
    long double Length = L * 1e3;
    long double Lambda = L * 1e9 / 299792458;
    LinesElement* temp3 = new LinesElement(Line, SystemParameters::z0line, this->circuitElements->frequencyFirstPoint, point, chart, parameter,
        L * 1000, L * 1000 / sqrt(SystemParameters::er), Theta, Lambda, SystemParameters::alpha);
    this->circuitElements->AddCircuitElements(temp3);
    pointsX.append(SystemParameters::lastPointX);
    pointsY.append(SystemParameters::lastPointY);
    QPoint temp = QPoint(SystemParameters::lastPointX * SystemParameters::scale + renderArea->rect().center().x(), SystemParameters::lastPointY * SystemParameters::scale + renderArea->rect().center().y());
    int row = pointTable->rowCount();
    pointTable->insertRow(row);
    pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(SystemParameters::index + SystemParameters::dpIndex)));
    SystemParameters::rImpedanceRealCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    SystemParameters::rImpedanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    QString temp2 = " + j";
    if (SystemParameters::impedanceImagR < 0)
    {
        temp2 = " - j";
    }
    pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
    if (SystemParameters::impedanceRealR == 0)
    {
        pointTable->setItem(row, 3, new QTableWidgetItem("0"));
    }
    else
    {
        pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
    }
    pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)this->circuitElements->frequencyFirstPoint)));
    circuitElements->elementIndexes.append(SystemParameters::allpointindex);
    SystemParameters::index++;
    SystemParameters::allpointindex++;
    renderArea->setCursorPosOnCircle(temp);
    tempCircuit = *circuitElements;
    firstDeleted = true;
    amplitudeFrequence->MatrixCalculation();
    if (!amplitudeFrequence->isHidden())
    {
        amplitudeFrequence->show();
    }
}

/// <summary>
/// Шлейф холостого хода.
/// </summary>
void Smithtry1000::onOSLine_buttonClicked()
{
    if (SystemParameters::index > 0)
    {
        VerticalLinesDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted && !SystemParameters::exc)
        {
            SystemParameters::Model = mode::OSLine;
            VerticalLines();
        }
        else if (SystemParameters::exc)
        {
            QMessageBox* bx = new QMessageBox();
            bx->show();
            bx->Warning;
            bx->setText(QStringLiteral(u"Все параметры должны быть заданы положительными числами"));
            SystemParameters::exc = false;
        }
    }
    else
    {
        QMessageBox* bx = new QMessageBox();
        bx->show();
        bx->Information;
        bx->setText(QStringLiteral(u"Добавьте стартовую точку."));
    }
}

/// <summary>
/// Шлейф короткого замыкания.
/// </summary>
void Smithtry1000::onSSLine_buttonClicked()
{
    if (SystemParameters::index > 0)
    {
        VerticalLinesDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted && !SystemParameters::exc)
        {
            SystemParameters::Model = mode::SSLine;
            VerticalLines();
        }
        else if (SystemParameters::exc)
        {
            QMessageBox* bx = new QMessageBox();
            bx->show();
            bx->Warning;
            bx->setText(QStringLiteral(u"Все параметры должны быть заданы положительными числами"));
            SystemParameters::exc = false;
        }
    }
    else
    {
        QMessageBox* bx = new QMessageBox();
        bx->show();
        bx->Information;
        bx->setText(QStringLiteral(u"Добавьте стартовую точку."));
    }
}

/// <summary>
/// Ввод с клавиатуры.
/// </summary>
void Smithtry1000::onKeyboard_buttonClicked()
{
    KeyboardDialog dialog(this, circuitElements);
    if (dialog.exec() == QDialog::Accepted && !SystemParameters::exc)
    {
        long double frequency = SystemParameters::frequency;
        long double x = 0;
        long double y = 0;
        long double Re = SystemParameters::Re;
        long double Im = SystemParameters::Im;
        if (SystemParameters::val == Cartesian)
        {
            if (SystemParameters::sys == Impedance)
            {
                Re /= SystemParameters::z0;
                Im /= SystemParameters::z0;
                long double denominator = (Re + 1) * (Re + 1) + Im * Im;

                if (denominator != 0) {
                    x = (Re * Re + Im * Im - 1) / denominator;
                    y = (2 * Im) / denominator;
                }
                else {
                    x = -1;
                    y = 0;
                }
            }
            else if (SystemParameters::sys == Admittance)
            {
                Re /= 1000 / SystemParameters::z0;
                Im /= 1000 / SystemParameters::z0;
                long double denominator = (1 + Re) * (1 + Re) + Im * Im;

                if (denominator != 0) {
                    x = (1 - Re * Re - Im * Im) / denominator;
                    y = (-2 * Im) / denominator;
                }
                else {
                    x = -1;
                    y = 0;
                }
            }
            else if (SystemParameters::sys == ReflectionCoefficient)
            {
                x = Re;
                y = Im;
            }
        }
        else if (SystemParameters::val == Polar)
        {
            if (SystemParameters::sys == Impedance)
            {
                Re /= SystemParameters::z0;
                Im = Im * M_PI / 180;
                double Z_real = Re * cos(Im);
                double Z_imag = Re * sin(Im);
                double denominator = (Z_real + 1) * (Z_real + 1) + Z_imag * Z_imag;

                if (denominator != 0) {
                    x = (Z_real * Z_real + Z_imag * Z_imag - 1) / denominator;
                    y = (2 * Z_imag) / denominator;
                }
                else {
                    x = -1;
                    y = 0;
                }
            }
            else if (SystemParameters::sys == Admittance)
            {
                Re /= 1000 / SystemParameters::z0;
                Im = Im * M_PI / 180;
                double Z_real = Re * cos(Im);
                double Z_imag = Re * sin(Im);
                long double denominator = (1 + Z_real) * (1 + Z_real) + Z_imag * Z_imag;

                if (denominator != 0) {
                    x = (1 - Z_real * Z_real - Z_imag * Z_imag) / denominator;
                    y = (-2 * Z_imag) / denominator;
                }
                else {
                    x = -1;
                    y = 0;
                }
            }
            else if (SystemParameters::sys == ReflectionCoefficient)
            {
                double angle = Im * M_PI / 180;
                x = Re * cos(angle);
                y = Re * sin(angle);
            }
        }
        y *= -1;
        QPoint temp = QPoint(x * SystemParameters::scale + renderArea->rect().center().x(), y * SystemParameters::scale + renderArea->rect().center().y());
        renderArea->setCursorPosOnCircle(temp);
        AppendPoint(x, y);
        tempCircuit = *circuitElements;
        firstDeleted = true;
    }
    else if (SystemParameters::exc)
    {
        QMessageBox* bx = new QMessageBox();
        bx->show();
        bx->Warning;
        bx->setText(QStringLiteral(u"Все параметры должны быть заданы числами.\nДействительное сопротивление/проводимость всегда больше нуля.\nМагнитуда от 0 до единицы.\n") +
            QStringLiteral(u"Декартовы координаты при задании через коэффициент отражения в сумме умещаются в единичную окружность"));
        SystemParameters::exc = false;
    }
}

/// <summary>
/// Добавление свободной точки в цепь.
/// </summary>
/// <param name="x">x.</param>
/// <param name="y">y.</param>
void Smithtry1000::AppendPoint(long double x, long double y)
{
    QPoint temp = QPoint(x * SystemParameters::scale + renderArea->rect().center().x(), y * SystemParameters::scale + renderArea->rect().center().y());
    if (SystemParameters::index == 0)
    {
        rTable->setItem(3, 3, new QTableWidgetItem(QString::number((double)SystemParameters::frequency)));
        if (y >= 0 && y < 0.0001)
        {
            y = 0.0001;
        }
        else if (y <= 0 && y > -0.0001)
        {
            y = -0.0001;
        }
        pointsX.append(x);
        pointsY.append(y);
        SystemParameters::lastPointX = x;
        SystemParameters::lastPointY = y;
        Point point = Point();
        point.x = x;
        point.y = y;
        circuitElements->firstPoint = point;
        allPoints[0] = make_tuple(point, false);
        SystemParameters::rImpedanceRealCalculation(x, y);
        long double r1 = SystemParameters::impedanceRealR;
        circuitElements->realFirstPoint = r1;
        SystemParameters::rImpedanceImagCalculation(x, y);
        long double r2 = SystemParameters::impedanceImagR;
        circuitElements->imagFirstPoint = r2;
        Complex z = SystemParameters::zCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
        Complex y2 = SystemParameters::yCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
        circuitElements->z = z;
        circuitElements->y = y2;
        Complex g;
        if (x >= 0)
        {
            g = Complex(sqrt(pow(x, 2) + pow(y, 2)), atan(y / x) * 180 / M_PI * -1);
        }
        else if (y <= 0)
        {
            g = Complex(sqrt(pow(x, 2) + pow(y, 2)), 180 - atan(y / x) * 180 / M_PI);
        }
        else
        {
            g = Complex(sqrt(pow(x, 2) + pow(y, 2)), -180 - atan(y / x) * 180 / M_PI);
        }
        circuitElements->g = g;
        circuitElements->frequencyFirstPoint = SystemParameters::frequency;
        map<chartMode, tuple<long double, long double>> chart;
        Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(point.x, point.y);
        Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(point.x, point.y);
        Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(point.x, point.y);
        Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(point.x, point.y);
        chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
        chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
        chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
        chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
        circuitElements->chart = chart;
        int row = pointTable->rowCount();
        pointTable->insertRow(row);
        pointTable->setItem(row, 0, new QTableWidgetItem(QStringLiteral(u"Да")));
        pointTable->setItem(row, 1, new QTableWidgetItem("DP 1"));
        SystemParameters::rImpedanceRealCalculation(x, y);
        SystemParameters::rImpedanceImagCalculation(x, y);
        QString temp2 = " + j";
        if (SystemParameters::impedanceImagR < 0)
        {
            temp2 = " - j";
        }
        pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
        if (SystemParameters::impedanceRealR == 0)
        {
            pointTable->setItem(row, 3, new QTableWidgetItem("0"));
        }
        else
        {
            pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
        }
        pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)SystemParameters::frequency)));
        SystemParameters::index++;
        SystemParameters::dpIndex++;
        SystemParameters::allpointindex++;
        renderArea->setCursorPosOnCircle(temp);
        auxiliaryWidget->update();
    }
    else
    {
        int row = pointTable->rowCount();
        pointTable->insertRow(row);
        pointTable->setItem(row, 0, new QTableWidgetItem(QStringLiteral(u"Нет")));
        pointTable->setItem(row, 1, new QTableWidgetItem("DP " + QString::number(SystemParameters::dpIndex + SystemParameters::index)));
        SystemParameters::rImpedanceRealCalculation(x, y);
        SystemParameters::rImpedanceImagCalculation(x, y);
        QString temp2 = " + j";
        if (SystemParameters::impedanceImagR < 0)
        {
            temp2 = " - j";
        }
        pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
        if (SystemParameters::impedanceRealR == 0)
        {
            pointTable->setItem(row, 3, new QTableWidgetItem("0"));
        }
        else
        {
            pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
        }
        pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)circuitElements->frequencyList[circuitElements->frequencyList.size() - 1])));
        Point point;
        point.x = x;
        point.y = y;
        allPoints[SystemParameters::index + SystemParameters::dpIndex - 1] = make_tuple(point, false);
        circuitElements->pointIndexes.append(SystemParameters::allpointindex);
        SystemParameters::dpIndex++;
        SystemParameters::allpointindex++;
        circuitElements->morePoints.append(point);
        renderArea->setCursorPosOnCircle(temp);
        auxiliaryWidget->update();
    }
}

/// <summary>
/// Шлейфы холостого хода и короткого замыкания.
/// </summary>
void Smithtry1000::VerticalLines()
{
    auxiliaryWidget->update();
    leftClicked = false;
    rightClicked = false;
    QPoint centerLocal = renderArea->rect().center();
    QPoint centerGlobal = renderArea->mapToGlobal(centerLocal);
    Complex zl, yl;
    switch (SystemParameters::Model)
    {
    case OSLine:
    {
        if (!SystemParameters::rotate)
        {
            auxiliaryWidget->addSvg(QString(":/Images/os_circuit.svg"), (SystemParameters::index + 2) * 40, 39);
        }
        else
        {
            auxiliaryWidget->addSvg(QString(":/Images/rev_os_circuit.svg"), 79, (SystemParameters::index + 1) * 40);
        }
        break;
    }
    case SSLine:
    {
        if (!SystemParameters::rotate)
        {
            auxiliaryWidget->addSvg(QString(":/Images/ss_circuit.svg"), (SystemParameters::index + 2) * 40, 39);
        }
        else
        {
            auxiliaryWidget->addSvg(QString(":/Images/rev_ss_circuit.svg"), 79, (SystemParameters::index + 1) * 40);
        }
        break;
    }
    }
    QCursor::setPos(centerGlobal);
    this->setCursor(Qt::BlankCursor); // скрываем системный курсор
    long double x;
    long double y;
    if (circuitElements->GetCircuitElements().size() > 0)
    {
        yl = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter()[Y];
        zl = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter()[Z];
        x = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().x;
        y = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().y;
    }
    else
    {
        yl = circuitElements->y;
        zl = circuitElements->z;
        x = circuitElements->firstPoint.x;
        y = circuitElements->firstPoint.y;
    }
    if (y >= 0 && y < 0.0001)
    {
        y = 0.0001;
    }
    else if (y <= 0 && y > -0.0001)
    {
        y = -0.0001;
    }
    long double circleRadius = -1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 + 2 * x));
    long double xCenter = -1 - circleRadius;
    long double dx = x - xCenter;
    long double dy = y;
    dy *= -1;
    long double sin_t = dy;
    long double cos_t = dx;
    t = atan(sin_t / cos_t);
    if (cos_t < 0 && sin_t < 0)
    {
        t = abs(t) - M_PI;
    }
    else if (sin_t > 0 && cos_t < 0)
    {
        t = M_PI - abs(t);
    }
    if (x + 1 != 0)
    {
        r = (cos(t) - x) / (x + 1);
    }
    else
    {
        r = 1e9;
    }
    tmin = -M_PI;
    tmax = M_PI;
    trackingEnabled = !trackingEnabled;
    while (!leftClicked && !rightClicked)
    {
        QCoreApplication::processEvents();
    }
    if (leftClicked)
    {
        AppendVerticalLines(yl);
    }
    if (rightClicked)
    {
        QPoint temp = QPoint(pointsX.back() * SystemParameters::scale + renderArea->rect().center().x(), pointsY.back() * SystemParameters::scale + renderArea->rect().center().y());
        renderArea->setCursorPosOnCircle(temp);
        auxiliaryWidget->removeLastSvg();
        auxiliaryWidget->update();
    }
    this->unsetCursor(); // возвращаем курсор
    SystemParameters::Model = Default;
}

/// <summary>
/// Добавление шлейфов в цепь.
/// </summary>
/// <param name="yl">Комплексная проводимость прошлой точки.</param>
void Smithtry1000::AppendVerticalLines(Complex yl)
{
    SystemParameters::rAdmitanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Point point;
    point.x = SystemParameters::lastPointX;
    point.y = SystemParameters::lastPointY;
    long double x = point.x;
    long double y = point.y;
    allPoints[SystemParameters::index + SystemParameters::dpIndex - 1] = make_tuple(point, true);
    Complex z = SystemParameters::zCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex y2 = SystemParameters::yCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    map<parameterMode, Complex> parameter;
    parameter[Z] = z;
    parameter[Y] = y2;
    Complex g;
    if (x >= 0)
    {
        g = Complex(sqrt(pow(x, 2) + pow(y, 2)), atan(y / x) * 180 / M_PI * -1);
    }
    else if (y <= 0)
    {
        g = Complex(sqrt(pow(x, 2) + pow(y, 2)), 180 - atan(y / x) * 180 / M_PI);
    }
    else
    {
        g = Complex(sqrt(pow(x, 2) + pow(y, 2)), -180 - atan(y / x) * 180 / M_PI);
    }
    parameter[G] = g;
    map<chartMode, tuple<long double, long double>> chart;
    Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
    chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
    chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
    chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
    switch (SystemParameters::Model)
    {
    case OSLine:
    {
        long double theta;
        long double lambda;
        long double o;
        long double l;
        o = atan((y2.imag() - yl.imag()) / 1000 * SystemParameters::z0line);
        if (o < 0)
        {
            o += M_PI;
        }
        theta = o * 180 / M_PI;
        l = o * 299792458 / (2 * M_PI * 1e9);
        lambda = l * 1e9 / 299792458;
        VerticalLinesElement* temp = new VerticalLinesElement(OSLine, SystemParameters::z0line, this->circuitElements->frequencyFirstPoint, point, chart, parameter,
            l * 1000, l * 1000 / sqrt(SystemParameters::er), theta, lambda);
        this->circuitElements->AddCircuitElements(temp);
        break;
    }
    case SSLine:
    {
        long double theta;
        long double lambda;
        long double o;
        long double l;
        o = -atan(1 / ((y2.imag() - yl.imag()) / 1000 * SystemParameters::z0line));
        if (o < 0)
        {
            o += M_PI;
        }
        theta = o * 180 / M_PI;
        l = o * 299792458 / (2 * M_PI * 1e9);
        lambda = l * 1e9 / 299792458;
        VerticalLinesElement* temp = new VerticalLinesElement(SSLine, SystemParameters::z0line, this->circuitElements->frequencyFirstPoint, point, chart, parameter, l * 1000, l * 1000 / sqrt(SystemParameters::er), theta, lambda);
        this->circuitElements->AddCircuitElements(temp);
        break;
    }
    }
    pointsX.append(SystemParameters::lastPointX);
    pointsY.append(SystemParameters::lastPointY);
    QPoint temp = QPoint(SystemParameters::lastPointX * SystemParameters::scale + renderArea->rect().center().x(), SystemParameters::lastPointY * SystemParameters::scale + renderArea->rect().center().y());
    int row = pointTable->rowCount();
    pointTable->insertRow(row);
    pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(SystemParameters::index + SystemParameters::dpIndex)));
    SystemParameters::rImpedanceRealCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    SystemParameters::rImpedanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    QString temp2 = " + j";
    if (SystemParameters::impedanceImagR < 0)
    {
        temp2 = " - j";
    }
    pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
    if (SystemParameters::impedanceRealR == 0)
    {
        pointTable->setItem(row, 3, new QTableWidgetItem("0"));
    }
    else
    {
        pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
    }
    pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)this->circuitElements->frequencyFirstPoint)));
    circuitElements->elementIndexes.append(SystemParameters::allpointindex);
    SystemParameters::index++;
    SystemParameters::allpointindex++;
    renderArea->setCursorPosOnCircle(temp);
    tempCircuit = *circuitElements;
    firstDeleted = true;
    amplitudeFrequence->MatrixCalculation();
    if (!amplitudeFrequence->isHidden())
    {
        amplitudeFrequence->show();
    }
}

/// <summary>
/// Обновление таблицы точек, для Tune.
/// </summary>
void Smithtry1000::TableUpdate()
{
    tableChanged = true;
    for (int j = 0; j < SystemParameters::tunedElements.size(); j++)
    {
        int id = 0;
        for (int i = 1; i < pointTable->rowCount(); i++)
        {
            if (pointTable->item(i, 0) == nullptr)
            {
                string str = pointTable->item(i, 1)->text().toUtf8().constData();
                size_t pos = str.find(' ');
                string temp = str.substr(pos + 1);
                if (circuitElements->GetCircuitElements()[id] == SystemParameters::tunedElements[j])
                {
                    QString temp2 = " + j";
                    if (SystemParameters::impedanceImagR < 0)
                    {
                        temp2 = " - j";
                    }
                    double number = SystemParameters::tunedElements[j]->GetParameter()[Z].real();
                    double number2 = SystemParameters::tunedElements[j]->GetParameter()[Z].imag();
                    pointTable->setItem(i, 2, new QTableWidgetItem(QString::number(round(number * 100) / 100)
                        + temp2 + QString::number(round(abs(number2) * 100) / 100)));
                    if (SystemParameters::impedanceRealR == 0)
                    {
                        pointTable->setItem(i, 3, new QTableWidgetItem("0"));
                    }
                    else
                    {
                        double number3 = abs(SystemParameters::tunedElements[j]->GetParameter()[Z].imag()
                            / SystemParameters::tunedElements[j]->GetParameter()[Z].real());
                        pointTable->setItem(i, 3, new QTableWidgetItem(QString::number(round(number3 * 100) / 100)));
                    }
                }
                id++;
            }
        }
    }
    tempCircuit = *circuitElements;
    firstDeleted = true;
    SystemParameters::tunedElements = {};
    tableChanged = false;
    amplitudeFrequence->MatrixCalculation();
    if (!amplitudeFrequence->isHidden())
    {
        amplitudeFrequence->show();
    }
}

/// <summary>
/// Деструктор класса Smithtry1000.
/// </summary>
Smithtry1000::~Smithtry1000()
{
}

/// <summary>
/// Экспорт схемы в нетлист.
/// </summary>
void Smithtry1000::onExportNetlist_buttonClicked()
{
    if (circuitElements->GetCircuitElements().size() > 0)
    {
        ExportNetlist exporter = ExportNetlist(circuitElements);

        QString fileName = QFileDialog::getSaveFileName(this,
            "Save CIR Netlist",
            "",
            "CIR Files (*.cir);;CKT Files (*.ckt);;SCS Files(*.scs)"
        );

        if (!fileName.isEmpty()) {
            string str = fileName.toUtf8().constData();
            size_t pos = str.find_last_of('.');
            string extension = str.substr(pos + 1);
            if (extension == "cir")
            {
                QString netlist = exporter.generateNetlistCir();
                QFile file(fileName);
                if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    QTextStream stream(&file);
                    stream << netlist;
                    file.close();
                    QMessageBox::information(this, "Success", "CIR netlist exported!");
                }
            }
            else if (extension == "ckt")
            {
                QString netlist = exporter.generateNetlistCkt();
                QFile file(fileName);
                if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    QTextStream stream(&file);
                    stream << netlist;
                    file.close();
                    QMessageBox::information(this, "Success", "CKT netlist exported!");
                }
            }
            else if (extension == "scs")
            {
                QString netlist = exporter.generateNetlistScs();
                QFile file(fileName);
                if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    QTextStream stream(&file);
                    stream << netlist;
                    file.close();
                    QMessageBox::information(this, "Success", "SCS netlist exported!");
                }
            }
            else {
                QMessageBox::warning(this, "Error", "Cannot write file");
            }
        }
    }
    else
    {
        QMessageBox* bx = new QMessageBox();
        bx->show();
        bx->Information;
        bx->setText(QStringLiteral(u"Добавьте элемент в цепь."));
    }
}

/// <summary>
/// Настройка элементов в цепи.
/// </summary>
void Smithtry1000::onTune_buttonClicked()
{
    if (circuitElements->GetCircuitElements().length() > 0)
    {
        SystemParameters::tune = true;
        tuneWidget->show();
        QPoint centerLocal = scrollArea->rect().center();
        QPoint centerGlobal = scrollArea->mapToGlobal(centerLocal);
        QCursor::setPos(centerGlobal);
        leftClicked = false;
        rightClicked = false;
        QPoint point = QCursor::pos();
        while (SystemParameters::tune)
        {
            QCoreApplication::processEvents();
            while (SystemParameters::circuitHover)
            {
                QCoreApplication::processEvents();
                auxiliaryWidget->update();
            }
        }
        tuneWidget->hide();
    }
    else
    {
        QMessageBox* bx = new QMessageBox();
        bx->show();
        bx->Information;
        bx->setText(QStringLiteral(u"Добавьте элемент в цепь."));
    }
}

/// <summary>
/// Обработка нажатий кнопок мыши.
/// </summary>
/// <param name="event"></param>
void Smithtry1000::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        rightClicked = true;
        if (SystemParameters::Model == Default)
        {
            onDelete_buttonClicked();
        }
        event->accept();
    }
}

/// <summary>
/// Получение сигнала о нажатии левой кнопки мыши на дочернем виджете.
/// </summary>
/// <param name="pos">Позиция курсора.</param>
void Smithtry1000::getLeftClicked(QPoint pos)
{
    leftClicked = true;
    QPoint globalPos = mapToGlobal(pos);
    QPoint scrollAreaPos = scrollAreaDiagram->viewport()->mapFromGlobal(globalPos);
    setCursor(Qt::ClosedHandCursor);
    moving = true;
    lastPos = pos;
}

/// <summary>
/// Получение информации о перемещении мыши на дочернем виджете ДВС.
/// </summary>
/// <param name="pos">Новая позиция курсора.</param>
void Smithtry1000::getMoved(QPoint pos)
{
    QPoint delta = pos - lastPos;

    QScrollBar* hBar = scrollAreaDiagram->horizontalScrollBar();
    QScrollBar* vBar = scrollAreaDiagram->verticalScrollBar();

    if (hBar) {
        hBar->setValue(hBar->value() - delta.x());
    }
    if (vBar) {
        vBar->setValue(vBar->value() - delta.y());
    }

    lastPos = pos;
}

/// <summary>
/// Получение информации об отжатии мыши на дочернем виджете ДВС.
/// </summary>
void Smithtry1000::getReleased()
{
    leftClicked = false;
    setCursor(Qt::ArrowCursor);
    moving = false;
}

/// <summary>
/// Ввод с помощью мышки.
/// </summary>
void Smithtry1000::onButtonClicked()
{
    FrequencyDialog dialog(this, circuitElements);
    if (dialog.exec() == QDialog::Accepted && !SystemParameters::exc)
    {
        SystemParameters::Model = AddPoint;
        QPoint centerLocal = renderArea->rect().center();
        QPoint centerGlobal = renderArea->mapToGlobal(centerLocal);
        QCursor::setPos(SystemParameters::lastPointX * SystemParameters::scale + centerGlobal.x(), SystemParameters::lastPointY * SystemParameters::scale + centerGlobal.y());
        leftClicked = false;
        rightClicked = false;
        QPoint point = QCursor::pos();
        double tempPointX = point.x();
        double tempPointY = point.y();;
        while (!leftClicked && !rightClicked)
        {
            QCoreApplication::processEvents();
            if (this->isActiveWindow())
            {
                point = QCursor::pos();
                if (pow(point.x() - centerGlobal.x(), 2) + pow(point.y() - centerGlobal.y(), 2) >= pow(SystemParameters::scale, 2))
                {
                    QCursor::setPos(tempPointX, tempPointY);
                    point.setX(tempPointX);
                    point.setY(tempPointY);
                }
                tempPointX = point.x();
                tempPointY = point.y();
            }
        }
        if (leftClicked)
        {
            long double x = point.x();
            long double y = point.y();
            x = (x - centerGlobal.x()) / SystemParameters::scale;
            y = (y - centerGlobal.y()) / SystemParameters::scale;
            if (y >= 0 && y < 0.0001)
            {
                y = 0.0001;
            }
            else if (y <= 0 && y > -0.0001)
            {
                y = -0.0001;
            }
            QPoint temp = QPoint(x * SystemParameters::scale + renderArea->rect().center().x(), y * SystemParameters::scale + renderArea->rect().center().y());
            renderArea->setCursorPosOnCircle(temp);
            AppendPoint(x, y);
            tempCircuit = *circuitElements;
            firstDeleted = true;
        }
        SystemParameters::Model = Default;
    }
    else if (SystemParameters::exc)
    {
        QMessageBox* bx = new QMessageBox();
        bx->show();
        bx->Warning;
        bx->setText(QStringLiteral(u"Частота должна быть задана положительным числом."));
        SystemParameters::exc = false;
    }
}

/// <summary>
/// Последовательная катушка индуктивности.
/// </summary>
void Smithtry1000::onInduction_buttonClicked()
{
    SystemParameters::Model = InductionShunt;
    ImaginaryImpedance();
}

/// <summary>
/// Последовательный конденсатор.
/// </summary>
void Smithtry1000::onCapacitor_buttonClicked()
{
    SystemParameters::Model = CapacitorShunt;
    ImaginaryImpedance();
}

/// <summary>
/// Последовательный резистор.
/// </summary>
void Smithtry1000::onResistor_buttonClicked()
{
    SystemParameters::Model = ResistorShunt;


    auxiliaryWidget->update();
    leftClicked = false;
    rightClicked = false;
    QPoint centerLocal = renderArea->rect().center();
    QPoint centerGlobal = renderArea->mapToGlobal(centerLocal);
    if (SystemParameters::index > 0)
    {
        if (!SystemParameters::rotate)
        {
            auxiliaryWidget->addSvg(QString(":/Images/horizontal_r.svg"), (SystemParameters::index + 2) * 40, 20);
        }
        else
        {
            auxiliaryWidget->addSvg(QString(":/Images/rev_horizontal_r.svg"), 60, (SystemParameters::index + 1) * 40);
        }
        QCursor::setPos(centerGlobal);
        this->setCursor(Qt::BlankCursor); // скрываем системный курсор
        long double cos_t;
        long double sin_t;
        long double x;
        long double y;
        if (circuitElements->GetCircuitElements().size() > 0)
        {
            x = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().x;
            y = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().y;
        }
        else
        {
            x = circuitElements->firstPoint.x;
            y = circuitElements->firstPoint.y;
        }
        if (y >= 0 && y < 0.0001)
        {
            SystemParameters::resistorLinear = true;
        }
        else if (y <= 0 && y > -0.0001)
        {
            SystemParameters::resistorLinear = true;
        }
        if (SystemParameters::resistorLinear)
        {
            long double denominator = (1 - x) * (1 - x) + y * y;

            if (denominator > 1e-12) {
                r = (1 - x * x - y * y) / denominator;
                if (y < 0)
                {
                    r = fabs(r);
                }
                else
                {
                    r = fabs(r) * -1;
                }
            }
            t = M_PI * 3 / 2 - 1 / 1e9;
        }
        else
        {
            long double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
            long double xCenter = 1 - circleRadius;
            long double dx = x - xCenter;
            long double dy = y;
            sin_t = dy;
            cos_t = dx;
            t = atan(cos_t / sin_t);
            if (y < 0)
            {
                t += M_PI;
            }
            else
            {
                t += 2 * M_PI;
            }
            if (x - 1 != 0)
            {
                r = cos(t) / (x - 1);
            }
            else
            {
                r = (1 + sin(t)) / y;
            }
            if (y < 0)
            {
                r = fabs(r);
                tmin = t + 1 / 1e9;
                t = tmin;
                tmax = M_PI * 3 / 2 - 1 / 1e9;
            }
            else
            {
                r = fabs(r) * (-1);
                tmax = t - 1 / 1e9;
                t = tmax;
                tmin = M_PI * 3 / 2 - 1 / 1e9;
            }
        }
        trackingEnabled = !trackingEnabled;
        while (!leftClicked && !rightClicked)
        {
            QCoreApplication::processEvents();
        }
        if (leftClicked)
        {
            AppendResShunt(x, y);
        }
        if (rightClicked)
        {
            QPoint temp = QPoint(pointsX.back() * SystemParameters::scale + renderArea->rect().center().x(), pointsY.back() * SystemParameters::scale + renderArea->rect().center().y());
            renderArea->setCursorPosOnCircle(temp);
            auxiliaryWidget->removeLastSvg();
            auxiliaryWidget->update();
        }
        SystemParameters::resistorLinear = false;
        SystemParameters::Model = Default;
        this->unsetCursor(); // возвращаем курсор
    }
    else
    {
        QMessageBox* bx = new QMessageBox();
        bx->show();
        bx->Information;
        bx->setText(QStringLiteral(u"Добавьте стартовую точку."));
    }
}

/// <summary>
/// Добавление последовательного резистора в цепь.
/// </summary>
/// <param name="x">x.</param>
/// <param name="y">y.</param>
void Smithtry1000::AppendResShunt(long double x, long double y)
{
    SystemParameters::rImpedanceRealCalculation(x, y);
    long double r1 = SystemParameters::impedanceRealR;
    SystemParameters::rImpedanceRealCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    long double r2 = SystemParameters::impedanceRealR;
    Point point;
    point.x = SystemParameters::lastPointX;
    point.y = SystemParameters::lastPointY;
    allPoints[SystemParameters::index + SystemParameters::dpIndex - 1] = make_tuple(point, true);
    Complex z = SystemParameters::zCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex y2 = SystemParameters::yCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    map<parameterMode, Complex> parameter;
    parameter[Z] = z;
    parameter[Y] = y2;
    Complex g;
    if (x >= 0)
    {
        g = Complex(sqrt(pow(point.x, 2) + pow(point.y, 2)), atan(point.y / point.x) * 180 / M_PI * -1);
    }
    else if (y <= 0)
    {
        g = Complex(sqrt(pow(point.x, 2) + pow(point.y, 2)), 180 - atan(point.y / point.x) * 180 / M_PI);
    }
    else
    {
        g = Complex(sqrt(pow(point.x, 2) + pow(point.y, 2)), -180 - atan(point.y / point.x) * 180 / M_PI);
    }
    parameter[G] = g;
    map<chartMode, tuple<long double, long double>> chart;
    Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
    chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
    chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
    chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
    this->circuitElements->AddCircuitElements(new Element(ResistorShunt, r2 - r1, this->circuitElements->frequencyFirstPoint, point, chart, parameter));
    pointsX.append(SystemParameters::lastPointX);
    pointsY.append(SystemParameters::lastPointY);
    QPoint temp = QPoint(SystemParameters::lastPointX * SystemParameters::scale + renderArea->rect().center().x(), SystemParameters::lastPointY * SystemParameters::scale + renderArea->rect().center().y());
    int row = pointTable->rowCount();
    pointTable->insertRow(row);
    pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(SystemParameters::index + SystemParameters::dpIndex)));
    SystemParameters::rImpedanceRealCalculation(point.x, point.y);
    SystemParameters::rImpedanceImagCalculation(point.x, point.y);
    QString temp2 = " + j";
    if (SystemParameters::impedanceImagR < 0)
    {
        temp2 = " - j";
    }
    pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
    if (SystemParameters::impedanceRealR == 0)
    {
        pointTable->setItem(row, 3, new QTableWidgetItem("0"));
    }
    else
    {
        pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
    }
    pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)this->circuitElements->frequencyFirstPoint)));
    circuitElements->elementIndexes.append(SystemParameters::allpointindex);
    SystemParameters::index++;
    SystemParameters::allpointindex++;
    renderArea->setCursorPosOnCircle(temp);
    tempCircuit = *circuitElements;
    firstDeleted = true;
    amplitudeFrequence->MatrixCalculation();
    if (!amplitudeFrequence->isHidden())
    {
        amplitudeFrequence->show();
    }
}

/// <summary>
/// Параллельная катушка индуктивности.
/// </summary>
void Smithtry1000::onInductionParallel_buttonClicked()
{
    SystemParameters::Model = InductionParallel;
    ImaginaryAdmitance();
}

/// <summary>
/// Параллельный конденсатор.
/// </summary>
void Smithtry1000::onCapacitorParallel_buttonClicked()
{
    SystemParameters::Model = CapacitorParallel;
    ImaginaryAdmitance();
}

/// <summary>
/// Параллельный резистор.
/// </summary>
void Smithtry1000::onResistorParallel_buttonClicked()
{
    SystemParameters::Model = ResistorParallel;
    auxiliaryWidget->update();
    leftClicked = false;
    rightClicked = false;
    QPoint centerLocal = renderArea->rect().center();
    QPoint centerGlobal = renderArea->mapToGlobal(centerLocal);
    if (SystemParameters::index > 0)
    {
        if (!SystemParameters::rotate)
        {
            auxiliaryWidget->addSvg(QString(":/Images/vertical_r_circuit.svg"), (SystemParameters::index + 2) * 40, 39);
        }
        else
        {
            auxiliaryWidget->addSvg(QString(":/Images/rev_vertical_r_circuit.svg"), 79, (SystemParameters::index + 1) * 40);
        }
        QCursor::setPos(centerGlobal);
        this->setCursor(Qt::BlankCursor); // скрываем системный курсор
        long double cos_t;
        long double sin_t;
        long double x;
        long double y;
        if (circuitElements->GetCircuitElements().size() > 0)
        {
            x = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().x;
            y = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().y;
        }
        else
        {
            x = circuitElements->firstPoint.x;
            y = circuitElements->firstPoint.y;
        }
        if (y >= 0 && y < 0.0001)
        {
            SystemParameters::resistorLinear = true;
        }
        else if (y <= 0 && y > -0.0001)
        {
            SystemParameters::resistorLinear = true;
        }
        if (SystemParameters::resistorLinear)
        {
            long double denominator = (1 + x) * (1 + x) + y * y;

            if (denominator > 1e-12) {
                r = (1 - x * x - y * y) / denominator;
                if (y < 0)
                {
                    r = fabs(r);
                }
                else
                {
                    r = fabs(r) * -1;
                }
            }
            t = M_PI * 3 / 2 - 1 / 1e9;
        }
        else
        {
            long double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y, 2)) / (-2 * y);
            long double yCenter = -circleRadius;
            long double dx = x + 1;
            long double dy = y - yCenter;
            sin_t = -dy;
            cos_t = dx;
            t = atan(sin_t / cos_t);
            if (x + 1 != 0)
            {
                r = cos(t) / (x + 1);
            }
            else
            {
                r = (1 + sin(t)) / y;
            }
            if (y > 0)
            {
                r *= -1;
                tmin = t + 1 / 1e9;
                t = tmin;
                tmax = M_PI / 2 - 1 / 1e9;
            }
            else
            {
                tmax = t - 1 / 1e9;
                t = tmax;
                tmin = -M_PI / 2 + 1 / 1e9;
            }
        }
        trackingEnabled = !trackingEnabled;
        while (!leftClicked && !rightClicked)
        {
            QCoreApplication::processEvents();
        }
        if (leftClicked)
        {
            AppendResPar(x, y);
        }
        if (rightClicked)
        {
            QPoint temp = QPoint(pointsX.back() * SystemParameters::scale + renderArea->rect().center().x(), pointsY.back() * SystemParameters::scale + renderArea->rect().center().y());
            renderArea->setCursorPosOnCircle(temp);
            auxiliaryWidget->removeLastSvg();
            auxiliaryWidget->update();
        }
        SystemParameters::resistorLinear = false;
        SystemParameters::Model = Default;
        this->unsetCursor(); // возвращаем курсор
    }
    else
    {
        QMessageBox* bx = new QMessageBox();
        bx->show();
        bx->Information;
        bx->setText(QStringLiteral(u"Добавьте стартовую точку."));
    }
}

/// <summary>
/// Добавление параллельного резистора в цепь.
/// </summary>
/// <param name="x">x.</param>
/// <param name="y">y.</param>
void Smithtry1000::AppendResPar(long double x, long double y)
{
    SystemParameters::rAdmitanceRealCalculation(x, y);
    long double r1 = SystemParameters::admitanceRealR;
    SystemParameters::rAdmitanceRealCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    long double r2 = SystemParameters::admitanceRealR;
    Point point;
    point.x = SystemParameters::lastPointX;
    point.y = SystemParameters::lastPointY;
    allPoints[SystemParameters::index + SystemParameters::dpIndex - 1] = make_tuple(point, true);
    Complex z = SystemParameters::zCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex y2 = SystemParameters::yCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    map<parameterMode, Complex> parameter;
    parameter[Z] = z;
    parameter[Y] = y2;
    Complex g;
    if (x >= 0)
    {
        g = Complex(sqrt(pow(point.x, 2) + pow(point.y, 2)), atan(point.y / point.x) * 180 / M_PI * -1);
    }
    else if (y <= 0)
    {
        g = Complex(sqrt(pow(point.x, 2) + pow(point.y, 2)), 180 - atan(point.y / point.x) * 180 / M_PI);
    }
    else
    {
        g = Complex(sqrt(pow(point.x, 2) + pow(point.y, 2)), -180 - atan(point.y / point.x) * 180 / M_PI);
    }
    parameter[G] = g;
    map<chartMode, tuple<long double, long double>> chart;
    Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
    chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
    chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
    chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
    this->circuitElements->AddCircuitElements(new Element(ResistorParallel, 1000 / (r2 - r1), this->circuitElements->frequencyFirstPoint, point, chart, parameter));
    pointsX.append(SystemParameters::lastPointX);
    pointsY.append(SystemParameters::lastPointY);
    QPoint temp = QPoint(SystemParameters::lastPointX * SystemParameters::scale + renderArea->rect().center().x(), SystemParameters::lastPointY * SystemParameters::scale + renderArea->rect().center().y());
    int row = pointTable->rowCount();
    pointTable->insertRow(row);
    pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(SystemParameters::index + SystemParameters::dpIndex)));
    SystemParameters::rImpedanceRealCalculation(point.x, point.y);
    SystemParameters::rImpedanceImagCalculation(point.x, point.y);
    QString temp2 = " + j";
    if (SystemParameters::impedanceImagR < 0)
    {
        temp2 = " - j";
    }
    pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
    if (SystemParameters::impedanceRealR == 0)
    {
        pointTable->setItem(row, 3, new QTableWidgetItem("0"));
    }
    else
    {
        pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
    }
    pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)this->circuitElements->frequencyFirstPoint)));
    circuitElements->elementIndexes.append(SystemParameters::allpointindex);
    SystemParameters::index++;
    SystemParameters::allpointindex++;
    renderArea->setCursorPosOnCircle(temp);
    tempCircuit = *circuitElements;
    firstDeleted = true;
    amplitudeFrequence->MatrixCalculation();
    if (!amplitudeFrequence->isHidden())
    {
        amplitudeFrequence->show();
    }
}

/// <summary>
/// Удаление элементов и точек с конца.
/// </summary>
void Smithtry1000::onDelete_buttonClicked()
{
    if (SystemParameters::allpointindex > 0 && !SystemParameters::tuneBlock && !SystemParameters::edit)
    {
        if (firstDeleted)
        {
            tempCircuit = CircuitElements(*circuitElements);
            firstDeleted = false;
        }
        if (get<1>(allPoints[SystemParameters::allpointindex - 1]))
        {
            auxiliaryWidget->removeLastSvg();
            renderArea->update();
            auxiliaryWidget->update();
            this->circuitElements->DeleteCircuitElements();
            pointsX.pop_back();
            pointsY.pop_back();
            this->circuitElements->elementIndexes.pop_back();
            SystemParameters::index--;
            SystemParameters::allpointindex--;
        }
        else
        {
            if (SystemParameters::allpointindex == 1)
            {
                rTable->setItem(3, 3, new QTableWidgetItem(""));
                SystemParameters::dpIndex--;
                this->circuitElements->imagFirstPoint = -9999;
                this->circuitElements->realFirstPoint = -9999;
                this->circuitElements->frequencyFirstPoint = -9999;
                this->circuitElements->z = Complex(-9999, -9999);
                this->circuitElements->y = Complex(-9999, -9999);
                this->circuitElements->g = Complex(-9999, -9999);
                this->circuitElements->firstPoint = Point();
                this->circuitElements->frequencyList.pop_back();
                pointsX.pop_back();
                pointsY.pop_back();
                SystemParameters::index--;
                SystemParameters::allpointindex--;
            }
            else
            {
                circuitElements->morePoints.pop_back();
                this->circuitElements->pointIndexes.pop_back();
                SystemParameters::dpIndex--;
                SystemParameters::allpointindex--;
                this->circuitElements->frequencyList.pop_back();
            }
        }
        pointTable->removeRow(pointTable->rowCount() - 1);
        allPoints.erase(allPoints.size() - 1);
        renderArea->update();
        auxiliaryWidget->update();
        if (SystemParameters::index > 1)
        {
            amplitudeFrequence->MatrixCalculation();
        }
        else
        {
            amplitudeFrequence->Clear();
        }
        if (!amplitudeFrequence->isHidden())
        {
            amplitudeFrequence->show();
        }
    }
    else
    {
        if (SystemParameters::allpointindex == 0)
        {
            QMessageBox* bx = new QMessageBox();
            bx->show();
            bx->Information;
            bx->setText(QStringLiteral(u"Нет элементов для удаления."));
        }
        else
        {
            QMessageBox* bx = new QMessageBox();
            bx->show();
            bx->Information;
            bx->setText(QStringLiteral(u"Уберите все элементы из Tune, чтобы удалять элементы."));
        }
    }
}

/// <summary>
/// Последовательные катушка индуктивности и конденсатор.
/// </summary>
void Smithtry1000::ImaginaryImpedance()
{
    auxiliaryWidget->update();
    leftClicked = false;
    rightClicked = false;
    QPoint centerLocal = renderArea->rect().center();
    QPoint centerGlobal = renderArea->mapToGlobal(centerLocal);
    if (SystemParameters::index > 0)
    {
        switch (SystemParameters::Model)
        {
        case InductionShunt:
        {
            if (!SystemParameters::rotate)
            {
                auxiliaryWidget->addSvg(QString(":/Images/horizontal_i.svg"), (SystemParameters::index + 2) * 40, 20);
            }
            else
            {
                auxiliaryWidget->addSvg(QString(":/Images/rev_horizontal_i.svg"), 60, (SystemParameters::index + 1) * 40);
            }
            break;
        }
        case CapacitorShunt:
        {
            if (!SystemParameters::rotate)
            {
                auxiliaryWidget->addSvg(QString(":/Images/horizontal_c.svg"), (SystemParameters::index + 2) * 40, 20);
            }
            else
            {
                auxiliaryWidget->addSvg(QString(":/Images/rev_horizontal_c.svg"), 60, (SystemParameters::index + 1) * 40);
            }
            break;
        }
        }
        QCursor::setPos(centerGlobal);
        this->setCursor(Qt::BlankCursor); // скрываем системный курсор
        long double x;
        long double y;
        if (circuitElements->GetCircuitElements().size() > 0)
        {
            x = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().x;
            y = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().y;
        }
        else
        {
            x = circuitElements->firstPoint.x;
            y = circuitElements->firstPoint.y;
        }
        if (y >= 0 && y < 0.0001)
        {
            y = 0.0001;
        }
        else if (y <= 0 && y > -0.0001)
        {
            y = -0.0001;
        }
        long double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
        long double xCenter = 1 - circleRadius;
        long double dx = x - xCenter;
        long double dy = y;
        long double sin_t = dy;
        long double cos_t = dx;
        t = atan(sin_t / cos_t);
        if (cos_t < 0 && sin_t < 0)
        {
            t += M_PI;
        }
        else if (cos_t > 0 && sin_t < 0)
        {
            t = 2 * M_PI - abs(t);
        }
        else if (sin_t > 0 && cos_t < 0)
        {
            t = M_PI - abs(t);
        }
        if (x - 1 != 0)
        {
            r = (cos(t) - x) / (x - 1);
        }
        else
        {
            r = 1e9;
        }
        switch (SystemParameters::Model)
        {
        case InductionShunt:
        {
            tmin = t + 0.04;
            t = tmin;
            tmax = 2 * M_PI - 0.04;
            break;
        }
        case CapacitorShunt:
        {
            tmin = 0.04;
            tmax = t - 0.04;
            t = tmax;
            break;
        }
        }
        trackingEnabled = !trackingEnabled;
        while (!leftClicked && !rightClicked)
        {
            QCoreApplication::processEvents();
        }
        if (leftClicked)
        {
            AppendIndCapShunt(x, y);
        }
        if (rightClicked)
        {
            QPoint temp = QPoint(pointsX.back() * SystemParameters::scale + renderArea->rect().center().x(), pointsY.back() * SystemParameters::scale + renderArea->rect().center().y());
            renderArea->setCursorPosOnCircle(temp);

            auxiliaryWidget->removeLastSvg();
            auxiliaryWidget->update();
        }
        this->unsetCursor(); // возвращаем курсор
    }
    else
    {
        QMessageBox* bx = new QMessageBox();
        bx->show();
        bx->Information;
        bx->setText(QStringLiteral(u"Добавьте стартовую точку."));
    }
    SystemParameters::Model = Default;
}

/// <summary>
/// Добавление последовательной катушки/конденсатора в цепь.
/// </summary>
/// <param name="x">x.</param>
/// <param name="y">y.</param>
void Smithtry1000::AppendIndCapShunt(long double x, long double y)
{
    SystemParameters::rImpedanceImagCalculation(x, y);
    long double r1 = SystemParameters::impedanceImagR;
    SystemParameters::rImpedanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    long double r2 = SystemParameters::impedanceImagR;
    Point point;
    point.x = SystemParameters::lastPointX;
    point.y = SystemParameters::lastPointY;
    allPoints[SystemParameters::index + SystemParameters::dpIndex - 1] = make_tuple(point, true);
    Complex z = SystemParameters::zCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex y2 = SystemParameters::yCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    map<parameterMode, Complex> parameter;
    parameter[Z] = z;
    parameter[Y] = y2;
    Complex g;
    if (x >= 0)
    {
        g = Complex(sqrt(pow(point.x, 2) + pow(point.y, 2)), atan(point.y / point.x) * 180 / M_PI * -1);
    }
    else if (y <= 0)
    {
        g = Complex(sqrt(pow(point.x, 2) + pow(point.y, 2)), 180 - atan(point.y / point.x) * 180 / M_PI);
    }
    else
    {
        g = Complex(sqrt(pow(point.x, 2) + pow(point.y, 2)), -180 - atan(point.y / point.x) * 180 / M_PI);
    }
    parameter[G] = g;
    map<chartMode, tuple<long double, long double>> chart;
    Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
    chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
    chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
    chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
    switch (SystemParameters::Model)
    {
    case InductionShunt:
    {
        this->circuitElements->AddCircuitElements(new Element(InductionShunt, (r2 - r1) / (2 * M_PI * circuitElements->frequencyFirstPoint), this->circuitElements->frequencyFirstPoint, point, chart, parameter));
        break;
    }
    case CapacitorShunt:
    {
        this->circuitElements->AddCircuitElements(new Element(CapacitorShunt, 1 / ((r1 - r2) * (2 * M_PI * circuitElements->frequencyFirstPoint)), this->circuitElements->frequencyFirstPoint, point, chart, parameter));
        break;
    }
    }
    pointsX.append(SystemParameters::lastPointX);
    pointsY.append(SystemParameters::lastPointY);
    QPoint temp = QPoint(SystemParameters::lastPointX * SystemParameters::scale + renderArea->rect().center().x(), SystemParameters::lastPointY * SystemParameters::scale + renderArea->rect().center().y());
    int row = pointTable->rowCount();
    pointTable->insertRow(row);
    pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(SystemParameters::index + SystemParameters::dpIndex)));
    SystemParameters::rImpedanceRealCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    SystemParameters::rImpedanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    QString temp2 = " + j";
    if (SystemParameters::impedanceImagR < 0)
    {
        temp2 = " - j";
    }
    pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
    if (SystemParameters::impedanceRealR == 0)
    {
        pointTable->setItem(row, 3, new QTableWidgetItem("0"));
    }
    else
    {
        pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
    }
    pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)this->circuitElements->frequencyFirstPoint)));
    circuitElements->elementIndexes.append(SystemParameters::allpointindex);
    SystemParameters::index++;
    SystemParameters::allpointindex++;
    renderArea->setCursorPosOnCircle(temp);
    tempCircuit = *circuitElements;
    firstDeleted = true;
    amplitudeFrequence->MatrixCalculation();
    if (!amplitudeFrequence->isHidden())
    {
        amplitudeFrequence->show();
    }
}

/// <summary>
/// Параллельные катушка индуктивности и конденсатор.
/// </summary>
void Smithtry1000::ImaginaryAdmitance()
{
    auxiliaryWidget->update();
    leftClicked = false;
    rightClicked = false;
    QPoint centerLocal = renderArea->rect().center();
    QPoint centerGlobal = renderArea->mapToGlobal(centerLocal);
    if (SystemParameters::index > 0)
    {
        switch (SystemParameters::Model)
        {
        case InductionParallel:
        {
            if (!SystemParameters::rotate)
            {
                auxiliaryWidget->addSvg(QString(":/Images/vertical_i_circuit.svg"), (SystemParameters::index + 2) * 40, 39);
            }
            else
            {
                auxiliaryWidget->addSvg(QString(":/Images/rev_vertical_i_circuit.svg"), 79, (SystemParameters::index + 1) * 40);
            }
            break;
        }
        case CapacitorParallel:
        {
            if (!SystemParameters::rotate)
            {
                auxiliaryWidget->addSvg(QString(":/Images/vertical_c_circuit.svg"), (SystemParameters::index + 2) * 40, 39);
            }
            else
            {
                auxiliaryWidget->addSvg(QString(":/Images/rev_vertical_c_circuit.svg"), 79, (SystemParameters::index + 1) * 40);
            }
            break;
        }
        }
        QCursor::setPos(centerGlobal);
        this->setCursor(Qt::BlankCursor); // скрываем системный курсор
        long double x;
        long double y;
        if (circuitElements->GetCircuitElements().size() > 0)
        {
            x = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().x;
            y = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().y;
        }
        else
        {
            x = circuitElements->firstPoint.x;
            y = circuitElements->firstPoint.y;
        }
        if (y >= 0 && y < 0.0001)
        {
            y = 0.0001;
        }
        else if (y <= 0 && y > -0.0001)
        {
            y = -0.0001;
        }
        long double circleRadius = -1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 + 2 * x));
        long double xCenter = -1 - circleRadius;
        long double dx = x - xCenter;
        long double dy = y;
        dy *= -1;
        long double sin_t = dy;
        long double cos_t = dx;
        t = atan(sin_t / cos_t);
        if (cos_t < 0 && sin_t < 0)
        {
            t = abs(t) - M_PI;
        }
        else if (sin_t > 0 && cos_t < 0)
        {
            t = M_PI - abs(t);
        }
        if (x + 1 != 0)
        {
            r = (cos(t) - x) / (x + 1);
        }
        else
        {
            r = 1e9;
        }
        switch (SystemParameters::Model)
        {
        case InductionParallel:
        {
            tmin = t + 0.04;
            t = tmin;
            tmax = M_PI - 0.04;
            break;
        }
        case CapacitorParallel:
        {
            tmin = -M_PI + 0.04;
            tmax = t - 0.04;
            t = tmax;
            break;
        }
        }
        trackingEnabled = !trackingEnabled;
        while (!leftClicked && !rightClicked)
        {
            QCoreApplication::processEvents();
        }
        if (leftClicked)
        {
            AppendIndCapPar(x, y);
        }
        if (rightClicked)
        {
            QPoint temp = QPoint(pointsX.back() * SystemParameters::scale + renderArea->rect().center().x(), pointsY.back() * SystemParameters::scale + renderArea->rect().center().y());
            renderArea->setCursorPosOnCircle(temp);
            auxiliaryWidget->removeLastSvg();
            auxiliaryWidget->update();
        }
        this->unsetCursor(); // возвращаем курсор
    }
    else
    {
        QMessageBox* bx = new QMessageBox();
        bx->show();
        bx->Information;
        bx->setText(QStringLiteral(u"Добавьте стартовую точку."));
    }
    SystemParameters::Model = Default;
}

/// <summary>
/// Добавление параллельной катушки/конденсатора в цепь.
/// </summary>
/// <param name="x">x.</param>
/// <param name="y">y.</param>
void Smithtry1000::AppendIndCapPar(long double x, long double y)
{
    SystemParameters::rAdmitanceImagCalculation(x, y);
    long double r1 = SystemParameters::admitanceImagR;
    SystemParameters::rAdmitanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    long double r2 = SystemParameters::admitanceImagR;
    Point point;
    point.x = SystemParameters::lastPointX;
    point.y = SystemParameters::lastPointY;
    allPoints[SystemParameters::index + SystemParameters::dpIndex - 1] = make_tuple(point, true);
    Complex z = SystemParameters::zCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex y2 = SystemParameters::yCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex g;
    map<parameterMode, Complex> parameter;
    parameter[Z] = z;
    parameter[Y] = y2;
    if (x >= 0)
    {
        g = Complex(sqrt(pow(point.x, 2) + pow(point.y, 2)), atan(point.y / point.x) * 180 / M_PI * -1);
    }
    else if (y <= 0)
    {
        g = Complex(sqrt(pow(point.x, 2) + pow(point.y, 2)), 180 - atan(point.y / point.x) * 180 / M_PI);
    }
    else
    {
        g = Complex(sqrt(pow(point.x, 2) + pow(point.y, 2)), -180 - atan(point.y / point.x) * 180 / M_PI);
    }
    parameter[G] = g;
    map<chartMode, tuple<long double, long double>> chart;
    Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(SystemParameters::lastPointX, SystemParameters::lastPointY);
    chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
    chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
    chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
    chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
    switch (SystemParameters::Model)
    {
    case InductionParallel:
    {
        this->circuitElements->AddCircuitElements(new Element(InductionParallel, M_PI / (r1 - r2) * 100 / circuitElements->frequencyFirstPoint * 1e6 * 500 / 1e9, this->circuitElements->frequencyFirstPoint, point, chart, parameter));
        break;
    }
    case CapacitorParallel:
    {
        this->circuitElements->AddCircuitElements(new Element(CapacitorParallel, (r2 - r1) / M_PI * 500 / circuitElements->frequencyFirstPoint * 1e6 / 1e12, this->circuitElements->frequencyFirstPoint, point, chart, parameter));
        break;
    }
    }
    pointsX.append(SystemParameters::lastPointX);
    pointsY.append(SystemParameters::lastPointY);
    QPoint temp = QPoint(SystemParameters::lastPointX * SystemParameters::scale + renderArea->rect().center().x(), SystemParameters::lastPointY * SystemParameters::scale + renderArea->rect().center().y());
    int row = pointTable->rowCount();
    pointTable->insertRow(row);
    pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(SystemParameters::index + SystemParameters::dpIndex)));
    SystemParameters::rImpedanceRealCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    SystemParameters::rImpedanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
    QString temp2 = " + j";
    if (SystemParameters::impedanceImagR < 0)
    {
        temp2 = " - j";
    }
    pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
    if (SystemParameters::impedanceRealR == 0)
    {
        pointTable->setItem(row, 3, new QTableWidgetItem("0"));
    }
    else
    {
        pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
    }
    pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)this->circuitElements->frequencyFirstPoint)));
    circuitElements->elementIndexes.append(SystemParameters::allpointindex);
    SystemParameters::index++;
    SystemParameters::allpointindex++;
    renderArea->setCursorPosOnCircle(temp);
    tempCircuit = *circuitElements;
    firstDeleted = true;
    amplitudeFrequence->MatrixCalculation();
    if (!amplitudeFrequence->isHidden())
    {
        amplitudeFrequence->show();
    }
}

/// <summary>
/// Событие происходящее по истечении каждых 10 мс.
/// </summary>
void Smithtry1000::onTimeout()
{
    QPoint centerLocal = renderArea->rect().center();
    QPoint centerGlobal = renderArea->mapToGlobal(centerLocal);
    if (SystemParameters::tuned || SystemParameters::edited)
    {
        renderArea->update();
        auxiliaryWidget->update();
        if (tableChanged == false && SystemParameters::tunedElements.size() > 0)
        {
            TableUpdate();
        }
        if (SystemParameters::tuned)
        {
            SystemParameters::tuned = false;
        }
        else
        {
            SystemParameters::edited = false;
        }
    }
    if (SystemParameters::Model == AddPoint || SystemParameters::Model == Default)
    {
        QPoint temp = QCursor::pos();
        long double x = temp.x();
        long double y = temp.y();
        x = (x - centerGlobal.x()) / SystemParameters::scale;
        y = (y - centerGlobal.y()) / SystemParameters::scale;
        ChangeCursorTable(x, y);
    }
    if (!trackingEnabled) return;

    if (leftClicked || rightClicked)
    {
        trackingEnabled = false;
        this->unsetCursor();
        return;
    }

    // Физическая позиция курсора
    QPoint currentGlobal = QCursor::pos();

    // Смещение мыши от центра
    int dx = currentGlobal.x() - centerGlobal.x();
    int dy = currentGlobal.y() - centerGlobal.y();

    if (dx != 0 || dy != 0)
    {
        if (this->isActiveWindow())
        {
            // Вычисляем точку на окружности и ставим туда курсор
            QPoint posOnCircle = getPointOnCircle(dx, dy);
            if (SystemParameters::Model == Transform)
            {
                double tempX = 0, tempY = 0;
                if (pow(posOnCircle.x() - centerLocal.x(), 2) + pow(posOnCircle.y() - centerLocal.y(), 2) > pow(SystemParameters::scale, 2))
                {
                    QCursor::setPos(tempX, tempY);
                    posOnCircle.setX(tempX);
                    posOnCircle.setY(tempY);
                }
                tempX = posOnCircle.x();
                tempY = posOnCircle.y();
            }
            QCursor::setPos(renderArea->mapToGlobal(posOnCircle));
            renderArea->setCursorPosOnCircle(posOnCircle);
            // Возвращаем системный курсор обратно в центр
            QCursor::setPos(centerGlobal);
        }
    }
}

/// <summary>
/// Изменение таблицы с параметрами по координатам курсора.
/// </summary>
/// <param name="x">x.</param>
/// <param name="y">y.</param>
void Smithtry1000::ChangeCursorTable(long double x, long double y)
{
    if (pow(x, 2) + pow(y, 2) <= 1)
    {
        SystemParameters::rImpedanceRealCalculation(x, y);
        SystemParameters::rAdmitanceRealCalculation(x, y);
        SystemParameters::rImpedanceImagCalculation(x, y);
        SystemParameters::rAdmitanceImagCalculation(x, y);
        QString temp = "+j";
        if (SystemParameters::impedanceImagR < 0)
        {
            temp = "-j";
        }
        rTable->setItem(0, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::impedanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::impedanceImagR) * 100) / 100)));
        if (SystemParameters::admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::admitanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::admitanceImagR) * 100) / 100)));
        if (x > 0)
        {
            rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round(((double)atan(y / x) * 180 / M_PI * -1) * 100) / 100)));
        }
        else if (y < 0)
        {
            rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
        }
        else
        {
            rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((-180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
        }
        if (SystemParameters::impedanceRealR == 0)
        {
            rTable->setItem(1, 3, new QTableWidgetItem("0"));
        }
        else
        {
            rTable->setItem(1, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
        }
        double r = sqrt(pow(x, 2) + pow(y, 2));
        rTable->setItem(0, 3, new QTableWidgetItem(QString::number(round(((-1 - r) / (r - 1)) * 100) / 100) + ":1"));
        rTable->setItem(2, 3, new QTableWidgetItem(QString::number(round(-20 * log10(r) * 100) / 100)));
    }
    else
    {
        rTable->setItem(0, 1, new QTableWidgetItem(""));
        rTable->setItem(1, 1, new QTableWidgetItem(""));
        rTable->setItem(2, 1, new QTableWidgetItem(""));
        rTable->setItem(1, 3, new QTableWidgetItem(""));
        rTable->setItem(0, 3, new QTableWidgetItem(""));
        rTable->setItem(2, 3, new QTableWidgetItem(""));
    }
}

/// <summary>
/// Определение положения эмуляции курсора на диаграмме.
/// </summary>
/// <param name="dx">Перемещение по x.</param>
/// <param name="dy">Перемещение по y.</param>
/// <returns>Точка на диаграмме.</returns>
QPoint Smithtry1000::getPointOnCircle(int dx, int dy)
{
    long double x = 0;
    long double y = 0;
    switch (SystemParameters::Model)
    {
    case ResistorShunt:
    {
        ResShuntPoint(dx, dy, x, y);
        break;
    }
    case InductionShunt:
    {
        IndCapShuntPoint(dx, dy, x, y);
        break;
    }
    case CapacitorShunt:
    {
        IndCapShuntPoint(dx, dy, x, y);
        break;
    }
    case ResistorParallel:
    {
        ResParPoint(dx, dy, x, y);
        break;
    }
    case InductionParallel:
    {
        IndCapParPoint(dx, dy, x, y);
        break;
    }
    case CapacitorParallel:
    {
        IndCapParPoint(dx, dy, x, y);
        break;
    }
    case Line:
    {
        LinePoint(dx, dy, x, y);
        break;
    }
    case OSLine:
    {
        OSSSPoint(dx, dy, x, y);
        break;
    }
    case SSLine:
    {
        OSSSPoint(dx, dy, x, y);
        break;
    }
    case Transform:
    {
        TransformPoint(dx, dy, x, y);
        break;
    }
    }
    UpdateCursorTableInMode(x, y);
    auxiliaryWidget->update();
    return QPoint(x, y);
}

/// <summary>
/// Получение новой точки для последовательной катушки/конденсатора.
/// </summary>
/// <param name="dx">Сдвиг по x.</param>
/// <param name="dy">Сдвиг по y.</param>
/// <param name="x">Новый x.</param>
/// <param name="y">Новый y.</param>
void Smithtry1000::IndCapShuntPoint(int dx, int dy, long double& x, long double& y)
{
    t = t;
    int dxABS = abs(dx);
    int dyABS = abs(dy);
    long double dif;
    dy = dy * -1;
    bool flag;
    if (dyABS > dxABS)
    {
        flag = true;
        dif = dyABS;
    }
    else
    {
        flag = false;
        dif = dxABS;
    }
    step = 0.01 + dif / 400;
    x = 0;
    y = 0;
    if (dx == 0 && dy == 0)
    {
    }
    else if (t <= intervalLength / 2 && t > tmin)
    {
        if ((dx > 0 && flag == false) || (dy > 0 && flag == true && t < intervalLength / 4) || (dy<0 && flag == true && t>intervalLength / 4))
        {
            if (t - step < tmin)
            {
                t = tmin;
            }
            else
            {
                t -= step;
            }
        }
        else if ((dx < 0 && flag == false) || (dy > 0 && flag == true && t > intervalLength / 4) || (dy < 0 && flag == true && t < intervalLength / 4))
        {
            if (t + step > tmax)
            {
                t = tmax;
            }
            else
            {
                t += step;
            }
        }
    }
    else if (t >= intervalLength / 2 && t < tmax)
    {
        if ((dx > 0 && flag == false) || (dy > 0 && flag == true && t < intervalLength * 3 / 4) || (dy < 0 && flag == true && t > intervalLength * 3 / 4))
        {
            if (t + step > tmax)
            {
                t = tmax;
            }
            else
            {
                t += step;
            }
        }
        else if ((dx < 0 && flag == false) || (dy < 0 && flag == true && t < intervalLength * 3 / 4) || (dy > 0 && flag == true && t > intervalLength * 3 / 4))
        {
            if (t - step < tmin)
            {
                t = tmin;
            }
            else
            {
                t -= step;
            }
        }
    }
    else if (t >= tmax)
    {
        step = 0.02;
        t = tmax;
        t -= step;
    }
    else if (t <= tmin)
    {
        t = tmin;
        step = 0.02;
        t += step;
    }

    long double cos_t = cos(t);
    long double sin_t = sin(t);
    x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
    y = (1 / (r + 1)) * sin_t;
    if (y >= 0 && y < 0.0001)
    {
        y = 0.0001;
    }
    else if (y <= 0 && y > -0.0001)
    {
        y = -0.0001;
    }
}

/// <summary>
/// Получение новой точки для параллельной катушки/конденсатора.
/// </summary>
/// <param name="dx">Сдвиг по x.</param>
/// <param name="dy">Сдвиг по y.</param>
/// <param name="x">Новый x.</param>
/// <param name="y">Новый y.</param>
void Smithtry1000::IndCapParPoint(int dx, int dy, long double& x, long double& y)
{
    t = t;
    int dxABS = abs(dx);
    int dyABS = abs(dy);
    long double dif;
    dy = dy * -1;
    bool flag;
    if (dyABS > dxABS)
    {
        flag = true;
        dif = dyABS;
    }
    else
    {
        flag = false;
        dif = dxABS;
    }
    step = 0.01 + dif / 800;
    x = 0;
    y = 0;
    if (dx == 0 && dy == 0)
    {
    }
    else if (t <= 0 && t > tmin)
    {
        if ((dx < 0 && flag == false) || (dy > 0 && flag == true && t < M_PI / 2 * (-1)) || (dy<0 && flag == true && t>M_PI / 2 * (-1)))
        {
            if (t - step < tmin)
            {
                t = tmin;
            }
            else
            {
                t -= step;
            }
        }
        else if ((dx > 0 && flag == false) || (dy > 0 && flag == true && t > M_PI / 2 * (-1)) || (dy < 0 && flag == true && t < M_PI / 2 * (-1)))
        {
            if (t + step > tmax)
            {
                t = tmax;
            }
            else
            {
                t += step;
            }
        }
    }
    else if (t >= 0 && t < tmax)
    {
        if ((dx < 0 && flag == false) || (dy > 0 && flag == true && t < M_PI / 2) || (dy < 0 && flag == true && t > M_PI / 2))
        {
            if (t + step > tmax)
            {
                t = tmax;
            }
            else
            {
                t += step;
            }
        }
        else if ((dx > 0 && flag == false) || (dy < 0 && flag == true && t < M_PI / 2) || (dy > 0 && flag == true && t > M_PI / 2))
        {
            if (t - step < tmin)
            {
                t = tmin;
            }
            else
            {
                t -= step;
            }
        }
    }
    else if (t >= tmax)
    {
        step = 0.02;
        t = tmax;
        t -= step;
    }
    else if (t <= tmin)
    {
        t = tmin;
        step = 0.02;
        t += step;
    }

    long double cos_t = cos(t);
    long double sin_t = sin(t);

    x = (cos(t) - r) / (r + 1);
    y = (1 / (r + 1)) * sin_t * -1;
    if (y >= 0 && y < 0.0001)
    {
        y = 0.0001;
    }
    else if (y <= 0 && y > -0.0001)
    {
        y = -0.0001;
    }
}

/// <summary>
/// Получение новой точки для последовательного резистора.
/// </summary>
/// <param name="dx">Сдвиг по x.</param>
/// <param name="dy">Сдвиг по y.</param>
/// <param name="x">Новый x.</param>
/// <param name="y">Новый y.</param>
void Smithtry1000::ResShuntPoint(int dx, int dy, long double& x, long double& y)
{
    x = 0;
    y = 0;
    long double xmin;
    if (circuitElements->GetCircuitElements().size() > 0)
    {
        xmin = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().x;
    }
    else
    {
        xmin = circuitElements->firstPoint.x;
    }
    if (SystemParameters::resistorLinear)
    {
        step = abs(r) / 1000;
        step += step * abs(dx);
        if (dx > 0 && SystemParameters::lastPointX <= 1)
        {
            if (SystemParameters::lastPointX + step >= 1)
            {
                x = 1 - step;
            }
            else
            {
                x = SystemParameters::lastPointX + step;
            }
        }
        else if (dx < 0 && SystemParameters::lastPointX >= xmin)
        {
            if (SystemParameters::lastPointX - step <= xmin)
            {
                x = xmin + step;
            }
            else
            {
                x = SystemParameters::lastPointX - step;
            }
        }
        else if (dx == 0)
        {
            x = SystemParameters::lastPointX;
        }
    }
    else
    {
        t = t;
        int dxABS = abs(dx);
        int dyABS = abs(dy);
        dy = dy * -1;
        int dif;
        bool flag;
        if (dyABS > dxABS)
        {
            flag = true;
            dif = dyABS;
        }
        else
        {
            flag = false;
            dif = dxABS;
        }
        step = abs(r) / 1000;
        step += step * dif;
        x = 0;
        y = 0;
        if (SystemParameters::lastPointY > 0)
        {
            dx *= -1;
        }
        if (dx == 0 && dy == 0)
        {
        }
        else if ((dx < 0 && abs(SystemParameters::lastPointY) <= abs(SystemParameters::lastPointX - 1) && flag == false) || (flag == true && dy > 0 && SystemParameters::lastPointY >= 0) || (flag == true && dy > 0 && SystemParameters::lastPointY <= 0) || (dx > 0 && abs(SystemParameters::lastPointY) >= abs(SystemParameters::lastPointX - 1) && flag == false))
        {
            if (t - step <= tmin)
            {
                t = tmin + step;
            }
            else
            {
                t -= step;
            }
        }
        else if ((dx > 0 && abs(SystemParameters::lastPointY) <= abs(SystemParameters::lastPointX - 1) && flag == false) || (flag == true && dy < 0 && SystemParameters::lastPointY <= 0) || (flag == true && dy < 0 && SystemParameters::lastPointY >= 0) || (dx < 0 && abs(SystemParameters::lastPointY) >= abs(SystemParameters::lastPointX - 1) && flag == false))
        {
            if (t + step >= tmax)
            {
                t = tmax - step;
            }
            else
            {
                t += step;
            }
        }
        else if (t >= tmax)
        {
            step = 1 / 1e9;
            t = tmax;
            t -= step;
        }
        else if (t <= tmin)
        {
            t = tmin;
            step = 1 / 1e9;
            t += step;
        }
        long double cos_t = cos(t);
        long double sin_t = sin(t);
        x = 1 + (1 / r) * cos_t;
        y = (1 / r) + (1 / r) * sin_t;
        y = y * (-1);
        if (y >= 0 && y < 0.0001)
        {
            y = 0.0001;
        }
        else if (y <= 0 && y > -0.0001)
        {
            y = -0.0001;
        }
    }
}

/// <summary>
/// Получение новой точки для параллельного резистора.
/// </summary>
/// <param name="dx">Сдвиг по x.</param>
/// <param name="dy">Сдвиг по y.</param>
/// <param name="x">Новый x.</param>
/// <param name="y">Новый y.</param>
void Smithtry1000::ResParPoint(int dx, int dy, long double& x, long double& y)
{
    if (SystemParameters::resistorLinear)
    {
        step = abs(r) / 1000;
        step += step * abs(dx);
        x = 0;
        y = 0;
        long double xmax;
        if (circuitElements->GetCircuitElements().size() > 0)
        {
            xmax = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().x;
        }
        else
        {
            xmax = circuitElements->firstPoint.x;
        }
        if (dx > 0 && SystemParameters::lastPointX <= xmax)
        {
            if (SystemParameters::lastPointX + step > xmax)
            {
                x = xmax - step;
            }
            else
            {
                x = SystemParameters::lastPointX + step;
            }
        }
        else if (dx < 0 && SystemParameters::lastPointX >= -1)
        {
            if (SystemParameters::lastPointX - step < -1)
            {
                x = -1 + step;
            }
            else
            {
                x = SystemParameters::lastPointX - step;
            }
        }
        else if (dx == 0)
        {
            x = SystemParameters::lastPointX;
        }
    }
    else
    {
        t = t;
        int dxABS = abs(dx);
        int dyABS = abs(dy);
        dy = dy * -1;
        int dif;
        bool flag;
        if (dyABS > dxABS)
        {
            flag = true;
            dif = dyABS;
        }
        else
        {
            flag = false;
            dif = dxABS;
        }
        step = abs(r) / 1000;
        step += step * dif;
        x = 0;
        y = 0;
        if (SystemParameters::lastPointY > 0)
        {
            dx *= -1;
        }
        if (dx == 0 && dy == 0)
        {
        }
        else if ((dx < 0 && abs(SystemParameters::lastPointY) <= abs(SystemParameters::lastPointX + 1) && flag == false) || (flag == true && dy < 0 && SystemParameters::lastPointY >= 0) || (flag == true && dy < 0 && SystemParameters::lastPointY <= 0) || (dx > 0 && abs(SystemParameters::lastPointY) >= abs(SystemParameters::lastPointX + 1) && flag == false))
        {
            if (t - step <= tmin)
            {
                t = tmin + step;
            }
            else
            {
                t -= step;
            }
        }
        else if ((dx > 0 && abs(SystemParameters::lastPointY) <= abs(SystemParameters::lastPointX + 1) && flag == false) || (flag == true && dy > 0 && SystemParameters::lastPointY <= 0) || (flag == true && dy > 0 && SystemParameters::lastPointY >= 0) || (dx < 0 && abs(SystemParameters::lastPointY) >= abs(SystemParameters::lastPointX + 1) && flag == false))
        {
            if (t + step >= tmax)
            {
                t = tmax - step;
            }
            else
            {
                t += step;
            }
        }
        long double cos_t = cos(t);
        long double sin_t = sin(t);
        if (SystemParameters::lastPointY < 0)
        {
            x = (cos_t - abs(r)) / r;
            y = (1 / r) + (1 / r) * sin_t;
            y *= -1;
        }
        else
        {
            x = -(cos_t - abs(r)) / r;
            y = -(1 / r) + (1 / r) * sin_t;
        }
        if (y >= 0 && y < 0.0001)
        {
            y = 0.0001;
        }
        else if (y <= 0 && y > -0.0001)
        {
            y = -0.0001;
        }
    }
}

/// <summary>
/// Получение новой точки для шлейфов.
/// </summary>
/// <param name="dx">Сдвиг по x.</param>
/// <param name="dy">Сдвиг по y.</param>
/// <param name="x">Новый x.</param>
/// <param name="y">Новый y.</param>
void Smithtry1000::OSSSPoint(int dx, int dy, long double& x, long double& y)
{
    t = t;
    int dxABS = abs(dx);
    int dyABS = abs(dy);
    long double dif;
    dy = dy * -1;
    bool flag;
    if (dyABS > dxABS)
    {
        flag = true;
        dif = dyABS;
    }
    else
    {
        flag = false;
        dif = dxABS;
    }
    step = 0.01 + dif / 800;
    x = 0;
    y = 0;
    if (dx == 0 && dy == 0)
    {
    }
    else if (t <= 0 && t > tmin)
    {
        if ((dx < 0 && flag == false) || (dy > 0 && flag == true && t < M_PI / 2 * (-1)) || (dy<0 && flag == true && t>M_PI / 2 * (-1)))
        {
            if (t - step < tmin)
            {
                t = tmin;
            }
            else
            {
                t -= step;
            }
        }
        else if ((dx > 0 && flag == false) || (dy > 0 && flag == true && t > M_PI / 2 * (-1)) || (dy < 0 && flag == true && t < M_PI / 2 * (-1)))
        {
            if (t + step > tmax)
            {
                t = tmax;
            }
            else
            {
                t += step;
            }
        }
    }
    else if (t >= 0 && t < tmax)
    {
        if ((dx < 0 && flag == false) || (dy > 0 && flag == true && t < M_PI / 2) || (dy < 0 && flag == true && t > M_PI / 2))
        {
            if (t + step > tmax)
            {
                t = tmax;
            }
            else
            {
                t += step;
            }
        }
        else if ((dx > 0 && flag == false) || (dy < 0 && flag == true && t < M_PI / 2) || (dy > 0 && flag == true && t > M_PI / 2))
        {
            if (t - step < tmin)
            {
                t = tmin;
            }
            else
            {
                t -= step;
            }
        }
    }
    else if (t >= tmax)
    {
        step = 0.01;
        t = tmax;
        t -= step;
        t *= -1;
    }
    else if (t <= tmin)
    {
        t = tmin;
        step = 0.01;
        t += step;
        t *= -1;
    }

    long double cos_t = cos(t);
    long double sin_t = sin(t);

    x = (cos(t) - r) / (r + 1);
    y = (1 / (r + 1)) * sin_t * -1;
    if (y >= 0 && y < 0.0001)
    {
        y = 0.0001;
    }
    else if (y <= 0 && y > -0.0001)
    {
        y = -0.0001;
    }
}

/// <summary>
/// Получение новой точки для линии передач.
/// </summary>
/// <param name="dx">Сдвиг по x.</param>
/// <param name="dy">Сдвиг по y.</param>
/// <param name="x">Новый x.</param>
/// <param name="y">Новый y.</param>
void Smithtry1000::LinePoint(int dx, int dy, long double& x, long double& y)
{
    t = t;
    int dxABS = abs(dx);
    int dyABS = abs(dy);
    long double dif;
    bool flag;
    if (dyABS > dxABS)
    {
        flag = true;
        dif = dyABS;
    }
    else
    {
        flag = false;
        dif = dxABS;
    }
    step = 0.01 + dif / 800;
    x = 0;
    y = 0;
    if (dx == 0 && dy == 0)
    {
    }
    else if (t <= 0 && t > tmin)
    {
        if ((dx < 0 && flag == false) || (dy > 0 && flag == true && t < M_PI / 2 * (-1)) || (dy<0 && flag == true && t>M_PI / 2 * (-1)))
        {
            if (t - step < tmin)
            {
                t = tmin;
            }
            else
            {
                t -= step;
            }
        }
        else if ((dx > 0 && flag == false) || (dy > 0 && flag == true && t > M_PI / 2 * (-1)) || (dy < 0 && flag == true && t < M_PI / 2 * (-1)))
        {
            if (t + step > tmax)
            {
                t = tmax;
            }
            else
            {
                t += step;
            }
        }
    }
    else if (t >= 0 && t < tmax)
    {
        if ((dx < 0 && flag == false) || (dy > 0 && flag == true && t < M_PI / 2) || (dy < 0 && flag == true && t > M_PI / 2))
        {
            if (t + step > tmax)
            {
                t = tmax;
            }
            else
            {
                t += step;
            }
        }
        else if ((dx > 0 && flag == false) || (dy < 0 && flag == true && t < M_PI / 2) || (dy > 0 && flag == true && t > M_PI / 2))
        {
            if (t - step < tmin)
            {
                t = tmin;
            }
            else
            {
                t -= step;
            }
        }
    }
    else if (t >= tmax)
    {
        step = 0.01;
        t = tmax;
        t -= step;
        t *= -1;
    }
    else if (t <= tmin)
    {
        t = tmin;
        step = 0.01;
        t += step;
        t *= -1;
    }

    long double cos_t = cos(t);
    long double sin_t = sin(t);
    Complex zl, yl;
    if (circuitElements->GetCircuitElements().size() > 0)
    {
        yl = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter()[Y];
        zl = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter()[Z];
    }
    else
    {
        yl = circuitElements->y;
        zl = circuitElements->z;
    }
    Complex g1 = (zl - SystemParameters::z0) / (zl + SystemParameters::z0);
    Complex z3 = SystemParameters::z0line * (zl + Complex(0, SystemParameters::z0line)) / (SystemParameters::z0line + Complex(0, 1) * zl);
    Complex g3 = (z3 - SystemParameters::z0) / (z3 + SystemParameters::z0);
    long double center = 0.5 * (pow(g1.real(), 2) + pow(g1.imag(), 2) - pow(g3.real(), 2) - pow(g3.imag(), 2)) / (g1.real() - g3.real());
    long double R = abs(center - g1);
    x = cos_t * R + r;
    y = sin_t * R;
    if (y >= 0 && y < 0.0001)
    {
        y = 0.0001;
    }
    else if (y <= 0 && y > -0.0001)
    {
        y = -0.0001;
    }
}

/// <summary>
/// Получение новой точки для трансформатора (линеаризированного).
/// </summary>
/// <param name="dx">Сдвиг по x.</param>
/// <param name="dy">Сдвиг по y.</param>
/// <param name="x">Новый x.</param>
/// <param name="y">Новый y.</param>
void Smithtry1000::TransformPoint(int dx, int dy, long double& x, long double& y)
{
    x = 0;
    y = 0;
    int dxABS = abs(dx);
    int dyABS = abs(dy);
    long double dif;
    if (SystemParameters::resistorLinear)
    {
        step = abs(r) / 1000;
        step += step * abs(dx);
        if (dx > 0 && SystemParameters::lastPointX <= 1)
        {
            if (SystemParameters::lastPointX + step >= 1)
            {
                x = 1 - step;
            }
            else
            {
                x = SystemParameters::lastPointX + step;
            }
        }
        else if (dx < 0 && SystemParameters::lastPointX >= -1)
        {
            if (SystemParameters::lastPointX - step <= -1)
            {
                x = -1 + step;
            }
            else
            {
                x = SystemParameters::lastPointX - step;
            }
        }
        else if (dx == 0)
        {
            x = SystemParameters::lastPointX;
        }
        y = 0;
    }
    NormalTransformPoint(dx, dy, x, y);
}

/// <summary>
/// Получение новой точки для трансформатора обычного.
/// </summary>
/// <param name="dx">Сдвиг по x.</param>
/// <param name="dy">Сдвиг по y.</param>
/// <param name="x">Новый x.</param>
/// <param name="y">Новый y.</param>
void Smithtry1000::NormalTransformPoint(int dx, int dy, long double& x, long double& y)
{
    long double dif;
    bool flag;
    long double tprev = t;
    int dxABS = abs(dx);
    int dyABS = abs(dy);
    if (dyABS > dxABS)
    {
        flag = true;
        dif = dyABS;
    }
    else
    {
        flag = false;
        dif = dxABS;
    }
    Complex zl;
    if (circuitElements->GetCircuitElements().size() > 0)
    {
        zl = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter()[Z];
    }
    else
    {
        zl = circuitElements->z;
    }
    step = 0.001 + dif / 2000;
    if (dx == 0 && dy == 0)
    {
    }
    else if (t <= 0 && t > tmin)
    {
        if ((dx < 0 && flag == false) || (dy < 0 && flag == true && t < M_PI / 2 * (-1)) || (dy > 0 && flag == true && t > M_PI / 2 * (-1)))
        {
            if (t - step < tmin)
            {
                t = tmin;
            }
            else
            {
                t -= step;
            }
        }
        else if ((dx > 0 && flag == false) || (dy < 0 && flag == true && t > M_PI / 2 * (-1)) || (dy > 0 && flag == true && t < M_PI / 2 * (-1)))
        {
            if (t + step > tmax)
            {
                t = tmax;
            }
            else
            {
                t += step;
            }
        }
    }
    else if (t >= 0 && t < tmax)
    {
        if ((dx < 0 && flag == false) || (dy < 0 && flag == true && t < M_PI / 2) || (dy > 0 && flag == true && t > M_PI / 2))
        {
            if (t + step > tmax)
            {
                t = tmax;
            }
            else
            {
                t += step;
            }
        }
        else if ((dx > 0 && flag == false) || (dy > 0 && flag == true && t < M_PI / 2) || (dy < 0 && flag == true && t > M_PI / 2))
        {
            if (t - step < tmin)
            {
                t = tmin;
            }
            else
            {
                t -= step;
            }
        }
    }

    long double cos_t = cos(t);
    long double sin_t = sin(t);

    long double q = zl.imag() / zl.real();
    long double ycenter = -1 / q;
    long double R = sqrt(1 + 1 / pow(q, 2));
    x = cos_t * R;
    if (abs(x) >= 0.99)
    {
        t = tprev;
        if (y > 0)
        {
            if (x < 0)
            {
                tmin = t;
            }
            else
            {
                tmax = t;
            }
        }
        else
        {
            if (x > 0)
            {
                tmin = t;
            }
            else
            {
                tmax = t;
            }
        }
    }
    else
    {
        y = sin_t * R + r;
        y *= -1;
        if (y >= 0 && y < 0.0001)
        {
            y = 0.0001;
        }
        else if (y <= 0 && y > -0.0001)
        {
            y = -0.0001;
        }
    }
}

/// <summary>
/// Обновление таблицы параметров по позиции курсора в режиме добавления элементов.
/// </summary>
/// <param name="x">x.</param>
/// <param name="y">y.</param>
void Smithtry1000::UpdateCursorTableInMode(long double& x, long double& y)
{
    SystemParameters::lastPointX = x;
    SystemParameters::lastPointY = y;
    SystemParameters::rImpedanceRealCalculation(x, y);
    SystemParameters::rAdmitanceRealCalculation(x, y);
    SystemParameters::rImpedanceImagCalculation(x, y);
    SystemParameters::rAdmitanceImagCalculation(x, y);
    QString temp = "+j";
    if (SystemParameters::impedanceImagR < 0)
    {
        temp = "-j";
    }
    rTable->setItem(0, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::impedanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::impedanceImagR) * 100) / 100)));
    if (SystemParameters::admitanceImagR < 0)
    {
        temp = "-j";
    }
    else
    {
        temp = "+j";
    }
    rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::admitanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::admitanceImagR) * 100) / 100)));
    if (x > 0)
    {
        rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round(((double)atan(y / x) * 180 / M_PI * -1) * 100) / 100)));
    }
    else if (y < 0)
    {
        rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
    }
    else
    {
        rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((-180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
    }
    if (SystemParameters::impedanceRealR == 0)
    {
        rTable->setItem(1, 3, new QTableWidgetItem("0"));
    }
    else
    {
        rTable->setItem(1, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
    }
    double rtemp = sqrt(pow(x, 2) + pow(y, 2));
    rTable->setItem(0, 3, new QTableWidgetItem(QString::number(round(((-1 - rtemp) / (rtemp - 1)) * 100) / 100) + ":1"));
    rTable->setItem(2, 3, new QTableWidgetItem(QString::number(round(-20 * log10(rtemp) * 100) / 100)));
    x = x * SystemParameters::scale + renderArea->rect().center().x();
    y = y * SystemParameters::scale + renderArea->rect().center().y();
}

/// <summary>
/// Масштабирование - приближение.
/// </summary>
void Smithtry1000::onPlusSize_buttonClicked()
{
    SystemParameters::unresized = true;
    if (SystemParameters::scale < 2000)
    {
        if (SystemParameters::scale == 1900)
        {
            PlusSizeButton->setDisabled(true);
        }
        if (SystemParameters::scale == 100)
        {
            MinusSizeButton->setEnabled(true);
        }
        SystemParameters::scale += 100;
        renderArea->update();
        int n = scrollAreaDiagram->horizontalScrollBar()->value();
        int m = scrollAreaDiagram->verticalScrollBar()->value();
        renderArea->setFixedWidth(1200 + (SystemParameters::scale - 200) * 2);
        renderArea->setFixedHeight(800 + (SystemParameters::scale - 200) * 2);
        scrollAreaDiagram->horizontalScrollBar()->setValue(n * (SystemParameters::scale / (SystemParameters::scale - 100)));
        scrollAreaDiagram->verticalScrollBar()->setValue(m * (SystemParameters::scale / (SystemParameters::scale - 100)));
    }
    SystemParameters::unresized = false;
}

/// <summary>
/// Масштабирование - отдаление.
/// </summary>
void Smithtry1000::onMinusSize_buttonClicked()
{
    SystemParameters::unresized = true;
    if (SystemParameters::scale > 100)
    {
        if (SystemParameters::scale == 200)
        {
            MinusSizeButton->setDisabled(true);
        }
        if (SystemParameters::scale == 2000)
        {
            PlusSizeButton->setEnabled(true);
        }
        SystemParameters::scale -= 100;
        int n = scrollAreaDiagram->horizontalScrollBar()->value();
        int m = scrollAreaDiagram->verticalScrollBar()->value();
        renderArea->setFixedWidth(1200 + (SystemParameters::scale - 200) * 2);
        renderArea->setFixedHeight(800 + (SystemParameters::scale - 200) * 2);
        renderArea->update();
        scrollAreaDiagram->horizontalScrollBar()->setValue(n * (SystemParameters::scale / (SystemParameters::scale + 100)));
        scrollAreaDiagram->verticalScrollBar()->setValue(m * (SystemParameters::scale / (SystemParameters::scale + 100)));
    }
    SystemParameters::unresized = false;
}

/// <summary>
/// Масштабирование - стандартное значение
/// </summary>
void Smithtry1000::onDefaultSize_buttonClicked()
{
    SystemParameters::unresized = true;
    SystemParameters::scale = 200;
    renderArea->update();
    renderArea->setFixedWidth(1200);
    renderArea->setFixedHeight(800);
    SystemParameters::unresized = false;
}

/// <summary>
/// Вызов амплитудно-частотной характеристики для цепи.
/// </summary>
void Smithtry1000::onGraph_buttonClicked()
{
    if (SystemParameters::index > 1)
    {
        amplitudeFrequence->MatrixCalculation();

        amplitudeFrequence->show();
        amplitudeFrequence->activateWindow();
    }
    else
    {
        QMessageBox* bx = new QMessageBox();
        bx->show();
        bx->Information;
        bx->setText(QStringLiteral(u"Добавьте хотя бы 1 элемент в цепь."));
    }
}

/// <summary>
/// Вызов выбора файла touchstone и установка точки по S11.
/// </summary>
void Smithtry1000::onS11_buttonClicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open S-Parameter File"), "", tr("S2P Files (*.s2p;*.s1p);;All Files (*)"));
    sParameters->Show();
}

/// <summary>
/// Вызов выбора файла touchstone и установка точки по S22.
/// </summary>
void Smithtry1000::onS22_buttonClicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open S-Parameter File"), "", tr("S2P Files (*.s2p;*.s1p);;All Files (*)"));
    sParameters->Show();
}

/// <summary>
/// Получение сигнала об изменении параметров отображения АЧХ.
/// </summary>
void Smithtry1000::getsignal()
{
    if (SystemParameters::index > 1)
    {
        amplitudeFrequence->MatrixCalculation();
        amplitudeFrequence->update();
    }
}

/// <summary>
/// Окно настройки цветов и толщин линий, опорного сопротивления, а также стандартно подставляемой частоты.
/// </summary>
void Smithtry1000::onMenuToolsCliked()
{
    sParameters->set->show();
    amplitudeFrequence->activateWindow();
}

/// <summary>
/// Получение сигнала об изменении параметров отображения окон S-параметров.
/// </summary>
void Smithtry1000::getS12S21signal()
{
    if (fileName != "")
    {
        sParameters->d1->Load();
        sParameters->d1->update();
        sParameters->d2->Load();
        sParameters->d2->update();
    }
}

/// <summary>
/// Получение сигнала об изменении параметров отображения на сетке ДВС.
/// </summary>
void Smithtry1000::getsignalDVS()
{
    SystemParameters::colorChanged = true;
    renderArea->update();
}

/// <summary>
/// Реакция на изменение размера виджета ДВС.
/// </summary>
/// <param name="width">Ширина окна.</param>
/// <param name="height">Высота окна.</param>
/// <param name="oldwidth">Старая ширина.</param>
/// <param name="oldheight">Старая высота.</param>
void Smithtry1000::getResized(long double width, long double height, long double oldwidth, long double oldheight)
{
    long double coef1 = width / oldwidth;
    long double coef2 = height / oldheight;
    long double coef = coef1 * coef2;
    SystemParameters::scale = SystemParameters::scale * coef;
    int n = scrollAreaDiagram->horizontalScrollBar()->value();
    int m = scrollAreaDiagram->verticalScrollBar()->value();
    renderArea->setFixedWidth(1200 + (SystemParameters::scale - 200) * 2);
    renderArea->setFixedHeight(800 + (SystemParameters::scale - 200) * 2);
    scrollAreaDiagram->horizontalScrollBar()->setValue(n * (SystemParameters::scale / (SystemParameters::scale - 100)));
    scrollAreaDiagram->verticalScrollBar()->setValue(m * (SystemParameters::scale / (SystemParameters::scale - 100)));
}