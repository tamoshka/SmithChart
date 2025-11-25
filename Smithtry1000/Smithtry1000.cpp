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

/// <summary>
/// Конструктор класса Smithtry1000.
/// </summary>
/// <param name="parent"></param>
/// <param name="sParameters1">S-параметры приходящие из файлы snp.</param>
Smithtry1000::Smithtry1000(QWidget* parent, SParameters* sParameters1)
    : QMainWindow(parent)
    , ui(new Ui::Smithtry1000Class())
    , trackingEnabled(false)
{
    ui->setupUi(this);
    this->sParameters = sParameters1;
    SystemParameters::Model = Default;
    this->resize(1600, 920);
    this->setMinimumSize(1630, 920);
    ui->pointTable->setColumnCount(5);
    ui->pointTable->setRowCount(1);
    ui->pointTable->setColumnWidth(0, 50);
    ui->pointTable->setColumnWidth(1, 35);
    ui->pointTable->setColumnWidth(2, 130);
    ui->pointTable->setColumnWidth(3, 70);
    ui->pointTable->setColumnWidth(4, 85);
    ui->pointTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->pointTable->setItem(0, 0, new QTableWidgetItem(QStringLiteral(u"Нач.")));
    ui->pointTable->setItem(0, 1, new QTableWidgetItem("ID"));
    ui->pointTable->setItem(0, 2, new QTableWidgetItem("Z"));
    ui->pointTable->setItem(0, 3, new QTableWidgetItem("Q"));
    ui->pointTable->setItem(0, 4, new QTableWidgetItem(QStringLiteral(u"Частота")));
    ui->rTable->setRowCount(4);
    ui->rTable->setColumnCount(4);
    ui->rTable->setColumnWidth(1, 100);
    ui->rTable->setColumnWidth(0, 30);
    ui->rTable->setColumnWidth(2, 150);
    ui->rTable->setColumnWidth(3, 100);
    ui->rTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->rTable->setItem(0, 0, new QTableWidgetItem("Z"));
    ui->rTable->setItem(1, 0, new QTableWidgetItem("Y"));
    ui->rTable->setItem(2, 0, new QTableWidgetItem("G"));
    ui->rTable->setItem(3, 0, new QTableWidgetItem("Z0"));
    ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)SystemParameters::z0)));
    ui->rTable->setItem(0, 2, new QTableWidgetItem(QStringLiteral(u"КСВН")));
    ui->rTable->setItem(1, 2, new QTableWidgetItem("Q"));
    ui->rTable->setItem(2, 2, new QTableWidgetItem(QStringLiteral(u"Обратные потери")));
    ui->rTable->setItem(3, 2, new QTableWidgetItem(QStringLiteral(u"Частота")));
    tmin = 0;
    tmax = 2 * M_PI;
    auxiliaryWidget->setMinimumWidth(200);
    auxiliaryWidget->setMinimumHeight(400);
    ui->scrollArea->setWidget(auxiliaryWidget);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
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
    connect(ui->MouseButton, &QPushButton::clicked, this, &Smithtry1000::onButtonClicked);
    connect(ui->Capacitor_button, &QPushButton::clicked, this, &Smithtry1000::onCapacitor_buttonClicked);
    connect(ui->GraphButton, &QPushButton::clicked, this, &Smithtry1000::onGraph_buttonClicked);
    connect(ui->Induction_button, &QPushButton::clicked, this, &Smithtry1000::onInduction_buttonClicked);
    connect(ui->Resistor_button, &QPushButton::clicked, this, &Smithtry1000::onResistor_buttonClicked);
    connect(ui->CapacitorParallel_button, &QPushButton::clicked, this, &Smithtry1000::onCapacitorParallel_buttonClicked);
    connect(ui->InductionParallel_button, &QPushButton::clicked, this, &Smithtry1000::onInductionParallel_buttonClicked);
    connect(ui->ResistorParallel_button, &QPushButton::clicked, this, &Smithtry1000::onResistorParallel_buttonClicked);
    connect(ui->StepBackButton, &QPushButton::clicked, this, &Smithtry1000::onDelete_buttonClicked);
    connect(ui->PlusSizeButton, &QPushButton::clicked, this, &Smithtry1000::onPlusSize_buttonClicked);
    connect(ui->MinusSizeButton, &QPushButton::clicked, this, &Smithtry1000::onMinusSize_buttonClicked);
    connect(ui->OneToOneButton, &QPushButton::clicked, this, &Smithtry1000::onDefaultSize_buttonClicked);
    ///connect(ui->S11Button, &QPushButton::clicked, this, &Smithtry1000::onS11_buttonClicked);
    ///connect(ui->S22Button, &QPushButton::clicked, this, &Smithtry1000::onS22_buttonClicked);
    connect(ui->ExportNetlist, &QPushButton::clicked, this, &Smithtry1000::onExportNetlist_buttonClicked);
    connect(ui->Tune, &QPushButton::clicked, this, &Smithtry1000::onTune_buttonClicked);
    connect(ui->Line_button, &QPushButton::clicked, this, &Smithtry1000::onLine_buttonClicked);
    connect(ui->OSLine_button, &QPushButton::clicked, this, &Smithtry1000::onOSLine_buttonClicked);
    connect(ui->SSLine_button, &QPushButton::clicked, this, &Smithtry1000::onSSLine_buttonClicked);
    connect(ui->actionColors, &QAction::triggered, this, &Smithtry1000::onMenuToolsCliked);
    connect(ui->ParametersButton, &QPushButton::clicked, this, &Smithtry1000::onMenuToolsCliked);
    connect(ui->KeyboardButton, &QPushButton::clicked, this, &Smithtry1000::onKeyboard_buttonClicked);
    connect(ui->CirclesButton, &QPushButton::clicked, this, &Smithtry1000::onCirclesClicked);
    connect(ui->Transform_button, &QPushButton::clicked, this, &Smithtry1000::onTransform_buttonClicked);
    connect(ui->CopyButton, &QPushButton::clicked, this, &Smithtry1000::Copy);
    connect(ui->SaveButton, &QPushButton::clicked, this, &Smithtry1000::Save);
    connect(ui->OpenButton, &QPushButton::clicked, this, &Smithtry1000::Load);
    connect(ui->StepForwardButton, &QPushButton::clicked, this, &Smithtry1000::Redo);
    connect(ui->AWRButton, &QPushButton::clicked, this, &Smithtry1000::AWR_buttonClicked);
    connect(ui->CADButton, &QPushButton::clicked, this, &Smithtry1000::CAD_export);
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
    renderArea->setMinimumHeight(800);
    renderArea->setMinimumWidth(1200);
    ui->scrollAreaDiagram->setWidget(renderArea);
    ui->scrollAreaDiagram->setWidgetResizable(true);
    ui->scrollAreaDiagram->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollAreaDiagram->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Smithtry1000::onTimeout);
    timer->start(10);  // Частое обновление для плавности
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
    /*if (SystemParameters::index <= 1)
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

    thread->start();*/
}

/// <summary>
/// Экспорт схемы в AWR.
/// </summary>
/// <returns>Успешно/нет.</returns>
bool Smithtry1000::ExportToAWR()
{
    /*if (!awr.Initialize()) {
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
    */
    return false;
}


/// <summary>
/// Получение сигнала об изменении всего (при изменении опорного сопротивления).
/// </summary>
void Smithtry1000::getallchangedsignal()
{
    SystemParameters::sizeChanged = true;
    ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)SystemParameters::z0)));
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
        circuitElements->firstPoint=point;
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
        circuitElements->chart=chart;
        circuitElements->z = z2;
        circuitElements->y = y3;
        circuitElements->g = g;
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
        QString fileName = QFileDialog::getSaveFileName(this, "Save the project", QDir::homePath() + "/project.json", "JSON Files (*.json)");
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

    if (!areEqual||circuitElements->firstPoint.x!=tempCircuit.firstPoint.x||circuitElements->firstPoint.y!=tempCircuit.firstPoint.y) 
    {
        timer->stop();
        firstDeleted = true;
        if (tempCircuit.elementIndexes.contains(SystemParameters::allpointindex))
        {
            circuitElements->AddCircuitElements(tempCircuit.GetCircuitElements()[circuitElements->GetCircuitElements().size()]);
            circuitElements->elementIndexes.append(tempCircuit.elementIndexes[circuitElements->elementIndexes.size()]);
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(SystemParameters::index + SystemParameters::dpIndex)));
            SystemParameters::rImpedanceRealCalculation(circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().x, circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().y);
            SystemParameters::rImpedanceImagCalculation(circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().x, circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetPoint().y);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
            if (SystemParameters::impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)circuitElements->frequencyFirstPoint)));
            QString name;
            bool mood = true;
            switch (circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size()-1]->GetMode())
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
                auxiliaryWidget->addSvg(QString(":/Images/" + rev + name + ".svg"), val+40, (circuitElements->GetCircuitElements().size() - 1 + 2) * 40);
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
        else if (tempCircuit.pointIndexes.contains(SystemParameters::allpointindex))
        {
            circuitElements->morePoints.append(tempCircuit.morePoints[circuitElements->morePoints.size()]);
            circuitElements->pointIndexes.append(tempCircuit.pointIndexes[circuitElements->pointIndexes.size()]);
            circuitElements->frequencyList.append(tempCircuit.frequencyList[circuitElements->frequencyList.size()]);
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 0, new QTableWidgetItem(QStringLiteral(u"Нет")));
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("DP " + QString::number(circuitElements->morePoints.size() + 1)));
            SystemParameters::rImpedanceRealCalculation(circuitElements->morePoints[circuitElements->morePoints.size() - 1].x, circuitElements->morePoints[circuitElements->morePoints.size() - 1].y);
            SystemParameters::rImpedanceImagCalculation(circuitElements->morePoints[circuitElements->morePoints.size() - 1].x, circuitElements->morePoints[circuitElements->morePoints.size() - 1].y);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
            if (SystemParameters::impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)circuitElements->frequencyList[circuitElements->frequencyList.size()-1])));
            Point point;
            point.x = circuitElements->morePoints[circuitElements->morePoints.size() - 1].x;
            point.y = circuitElements->morePoints[circuitElements->morePoints.size() - 1].y;
            allPoints[SystemParameters::allpointindex] = make_tuple(point, false);
            SystemParameters::dpIndex++;
        }
        else
        {
            circuitElements->chart = tempCircuit.chart;
            circuitElements->firstPoint = tempCircuit.firstPoint;
            circuitElements->frequencyFirstPoint = tempCircuit.frequencyFirstPoint;
            ui->rTable->setItem(3, 3, new QTableWidgetItem(QString::number((double)circuitElements->frequencyFirstPoint)));
            circuitElements->z = tempCircuit.z;
            circuitElements->y = tempCircuit.y;
            circuitElements->g = tempCircuit.g;
            circuitElements->imagFirstPoint = tempCircuit.imagFirstPoint;
            circuitElements->realFirstPoint = tempCircuit.realFirstPoint;
            circuitElements->frequencyList.append(tempCircuit.frequencyList[circuitElements->frequencyList.size()]);
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 0, new QTableWidgetItem(QStringLiteral(u"Да")));
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("DP 1"));
            SystemParameters::rImpedanceRealCalculation(circuitElements->firstPoint.x, circuitElements->firstPoint.y);
            SystemParameters::rImpedanceImagCalculation(circuitElements->firstPoint.x, circuitElements->firstPoint.y);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
            if (SystemParameters::impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)circuitElements->frequencyFirstPoint)));
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
/// Загрузка проекта.
/// </summary>
void Smithtry1000::Load()
{
    if (SystemParameters::index > 1)
    {
        PreSaveDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted)
        {
            QString fileName = QFileDialog::getSaveFileName(this, "Save the project", QDir::homePath() + "/project.json", "JSON Files (*.json)");
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
    }
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open project"), "", tr("JSON Files (*.json)"));
    try
    {
        circuitElements->loadFromFile(fileName);
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
        if (x != circuitElements->firstPoint.x || y != circuitElements->firstPoint.y)
        {
            ui->rTable->setItem(3, 3, new QTableWidgetItem(QString::number((double)circuitElements->frequencyFirstPoint)));
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
        allPoints[0] = make_tuple(circuitElements->firstPoint, false);
        pointsX.append(circuitElements->firstPoint.x);
        pointsY.append(circuitElements->firstPoint.y);
        int row = ui->pointTable->rowCount();
        ui->pointTable->insertRow(row);
        ui->pointTable->setItem(row, 0, new QTableWidgetItem(QStringLiteral(u"Да")));
        ui->pointTable->setItem(row, 1, new QTableWidgetItem("DP 1"));
        SystemParameters::rImpedanceRealCalculation(circuitElements->firstPoint.x, circuitElements->firstPoint.y);
        SystemParameters::rImpedanceImagCalculation(circuitElements->firstPoint.x, circuitElements->firstPoint.y);
        QString temp2 = " + j";
        if (SystemParameters::impedanceImagR < 0)
        {
            temp2 = " - j";
        }
        ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
        if (SystemParameters::impedanceRealR == 0)
        {
            ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
        }
        else
        {
            ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
        }
        ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)circuitElements->frequencyFirstPoint)));
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
                    int row = ui->pointTable->rowCount();
                    ui->pointTable->insertRow(row);
                    ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(i + 2)));
                    SystemParameters::rImpedanceRealCalculation(circuitElements->GetCircuitElements()[j]->GetPoint().x, circuitElements->GetCircuitElements()[j]->GetPoint().y);
                    SystemParameters::rImpedanceImagCalculation(circuitElements->GetCircuitElements()[j]->GetPoint().x, circuitElements->GetCircuitElements()[j]->GetPoint().y);
                    QString temp2 = " + j";
                    if (SystemParameters::impedanceImagR < 0)
                    {
                        temp2 = " - j";
                    }
                    ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
                    if (SystemParameters::impedanceRealR == 0)
                    {
                        ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
                    }
                    else
                    {
                        ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
                    }
                    ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)circuitElements->frequencyFirstPoint)));
                    allPoints[i + 1] = make_tuple(circuitElements->GetCircuitElements()[j]->GetPoint(), true);
                    bool mood;
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
                    int row = ui->pointTable->rowCount();
                    ui->pointTable->insertRow(row);
                    ui->pointTable->setItem(row, 0, new QTableWidgetItem(QStringLiteral(u"Нет")));
                    ui->pointTable->setItem(row, 1, new QTableWidgetItem("DP " + QString::number(i + 2)));
                    SystemParameters::rImpedanceRealCalculation(circuitElements->morePoints[k].x, circuitElements->morePoints[k].y);
                    SystemParameters::rImpedanceImagCalculation(circuitElements->morePoints[k].x, circuitElements->morePoints[k].y);
                    QString temp2 = " + j";
                    if (SystemParameters::impedanceImagR < 0)
                    {
                        temp2 = " - j";
                    }
                    ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
                    if (SystemParameters::impedanceRealR == 0)
                    {
                        ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
                    }
                    else
                    {
                        ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
                    }
                    ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)circuitElements->frequencyList[k + 1])));
                    allPoints[i + 1] = make_tuple(circuitElements->morePoints[k], false);
                    k++;
                }
            }
            else
            {
                int row = ui->pointTable->rowCount();
                ui->pointTable->insertRow(row);
                ui->pointTable->setItem(row, 0, new QTableWidgetItem(QStringLiteral(u"Нет")));
                ui->pointTable->setItem(row, 1, new QTableWidgetItem("DP " + QString::number(i + 2)));
                SystemParameters::rImpedanceRealCalculation(circuitElements->morePoints[k].x, circuitElements->morePoints[k].y);
                SystemParameters::rImpedanceImagCalculation(circuitElements->morePoints[k].x, circuitElements->morePoints[k].y);
                QString temp2 = " + j";
                if (SystemParameters::impedanceImagR < 0)
                {
                    temp2 = " - j";
                }
                ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
                if (SystemParameters::impedanceRealR == 0)
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
                }
                else
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
                }
                ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)circuitElements->frequencyList[k + 1])));
                allPoints[i + 1] = make_tuple(circuitElements->morePoints[k], false);
                k++;
            }
        }
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
    catch (exception e)
    {

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
                printer.setPageSize(QPageSize(widget->size()/10, QPageSize::Point));

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
    long double y0=0;
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
            t = M_PI * 3 / 2-0.02;
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
            tmin = -M_PI+0.02;
            tmax = M_PI-0.02;
        }
        trackingEnabled = !trackingEnabled;
        while (!leftClicked && !rightClicked)
        {
            QCoreApplication::processEvents();
        }
        if (leftClicked)
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
            long double n = sqrt(z.real() / zl.real());
            this->circuitElements->AddCircuitElements(new Element(Transform, n, this->circuitElements->frequencyFirstPoint, point, chart, parameter));
            pointsX.append(SystemParameters::lastPointX);
            pointsY.append(SystemParameters::lastPointY);
            QPoint temp = QPoint(SystemParameters::lastPointX * SystemParameters::scale + renderArea->rect().center().x(), SystemParameters::lastPointY * SystemParameters::scale + renderArea->rect().center().y());
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(SystemParameters::index + SystemParameters::dpIndex)));
            SystemParameters::rImpedanceRealCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
            SystemParameters::rImpedanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
            if (SystemParameters::impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)this->circuitElements->frequencyFirstPoint)));
            circuitElements->elementIndexes.append(SystemParameters::allpointindex);
            SystemParameters::index++;
            SystemParameters::allpointindex++;
            renderArea->setCursorPosOnCircle(temp);
            tempCircuit=*circuitElements;
            firstDeleted = true;
            amplitudeFrequence->MatrixCalculation();
            if (!amplitudeFrequence->isHidden())
            {
                amplitudeFrequence->show();
            }
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
/// Линия передач.
/// </summary>
void Smithtry1000::onLine_buttonClicked()
{
    if (SystemParameters::index > 0)
    {
        LinesDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted&&!SystemParameters::exc)
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
                t=M_PI - t;
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
                long double L = O * 299792458 / (2*M_PI * 1e9);
                long double Length = L * 1e3;
                long double Lambda = L * 1e9 / 299792458;
                LinesElement* temp3 = new LinesElement(Line, SystemParameters::z0line, this->circuitElements->frequencyFirstPoint, point, chart, parameter,
                    L * 1000, L * 1000 / sqrt(SystemParameters::er), Theta, Lambda, SystemParameters::alpha);
                this->circuitElements->AddCircuitElements(temp3);
                pointsX.append(SystemParameters::lastPointX);
                pointsY.append(SystemParameters::lastPointY);
                QPoint temp = QPoint(SystemParameters::lastPointX * SystemParameters::scale + renderArea->rect().center().x(), SystemParameters::lastPointY * SystemParameters::scale + renderArea->rect().center().y());
                int row = ui->pointTable->rowCount();
                ui->pointTable->insertRow(row);
                ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(SystemParameters::index + SystemParameters::dpIndex)));
                SystemParameters::rImpedanceRealCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
                SystemParameters::rImpedanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
                QString temp2 = " + j";
                if (SystemParameters::impedanceImagR < 0)
                {
                    temp2 = " - j";
                }
                ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
                if (SystemParameters::impedanceRealR == 0)
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
                }
                else
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
                }
                ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)this->circuitElements->frequencyFirstPoint)));
                circuitElements->elementIndexes.append(SystemParameters::allpointindex);
                SystemParameters::index++;
                SystemParameters::allpointindex++;
                renderArea->setCursorPosOnCircle(temp);
                tempCircuit=*circuitElements;
                firstDeleted = true;
                amplitudeFrequence->MatrixCalculation();
                if (!amplitudeFrequence->isHidden())
                {
                    amplitudeFrequence->show();
                }
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
/// Шлейф холостого хода.
/// </summary>
void Smithtry1000::onOSLine_buttonClicked()
{
    if (SystemParameters::index > 0)
    {
        VerticalLinesDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted&&!SystemParameters::exc)
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
        if (dialog.exec() == QDialog::Accepted&& !SystemParameters::exc)
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
    if (dialog.exec() == QDialog::Accepted&& !SystemParameters::exc)
    {
        long double frequency = SystemParameters::frequency;
        long double x, y;
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
                Re /= 1000/SystemParameters::z0;
                Im /= 1000/ SystemParameters::z0;
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
                Im = Im * M_PI/180;
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
                Re /= 1000/SystemParameters::z0;
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
        if (SystemParameters::index == 0)
        {
            ui->rTable->setItem(3, 3, new QTableWidgetItem(QString::number((double)SystemParameters::frequency)));
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
            circuitElements->frequencyFirstPoint = frequency;
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
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 0, new QTableWidgetItem(QStringLiteral(u"Да")));
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("DP 1"));
            SystemParameters::rImpedanceRealCalculation(x, y);
            SystemParameters::rImpedanceImagCalculation(x, y);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
            if (SystemParameters::impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)frequency)));
            SystemParameters::index++;
            SystemParameters::dpIndex++; 
            SystemParameters::allpointindex++;
            renderArea->setCursorPosOnCircle(temp);
            auxiliaryWidget->update();
        }
        else
        {
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 0, new QTableWidgetItem(QStringLiteral(u"Нет")));
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("DP " + QString::number(SystemParameters::dpIndex + SystemParameters::index)));
            SystemParameters::rImpedanceRealCalculation(x, y);
            SystemParameters::rImpedanceImagCalculation(x, y);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
            if (SystemParameters::impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)circuitElements->frequencyList[circuitElements->frequencyList.size() - 1])));
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
        tempCircuit=*circuitElements;
        firstDeleted = true;
    }
    else if (SystemParameters::exc)
    {
        QMessageBox* bx = new QMessageBox();
        bx->show();
        bx->Warning;
        bx->setText(QStringLiteral(u"Все параметры должны быть заданы числами.\nДействительное сопротивление/проводимость всегда больше нуля.\nМагнитуда от 0 до единицы.\n")+
            QStringLiteral(u"Декартовы координаты при задании через коэффициент отражения в сумме умещаются в единичную окружность"));
        SystemParameters::exc = false;
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
            l = o * 299792458 / (2*M_PI * 1e9);
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
            l = o * 299792458 / (2*M_PI * 1e9);
            lambda = l * 1e9 / 299792458;
            VerticalLinesElement* temp = new VerticalLinesElement(SSLine, SystemParameters::z0line, this->circuitElements->frequencyFirstPoint, point, chart, parameter, l * 1000, l * 1000 / sqrt(SystemParameters::er), theta, lambda);
            this->circuitElements->AddCircuitElements(temp);
            break;
        }
        }
        pointsX.append(SystemParameters::lastPointX);
        pointsY.append(SystemParameters::lastPointY);
        QPoint temp = QPoint(SystemParameters::lastPointX * SystemParameters::scale + renderArea->rect().center().x(), SystemParameters::lastPointY * SystemParameters::scale + renderArea->rect().center().y());
        int row = ui->pointTable->rowCount();
        ui->pointTable->insertRow(row);
        ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(SystemParameters::index + SystemParameters::dpIndex)));
        SystemParameters::rImpedanceRealCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
        SystemParameters::rImpedanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
        QString temp2 = " + j";
        if (SystemParameters::impedanceImagR < 0)
        {
            temp2 = " - j";
        }
        ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
        if (SystemParameters::impedanceRealR == 0)
        {
            ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
        }
        else
        {
            ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
        }
        ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)this->circuitElements->frequencyFirstPoint)));
        circuitElements->elementIndexes.append(SystemParameters::allpointindex);
        SystemParameters::index++;
        SystemParameters::allpointindex++;
        renderArea->setCursorPosOnCircle(temp);
        tempCircuit=*circuitElements;
        firstDeleted = true;
        amplitudeFrequence->MatrixCalculation();
        if (!amplitudeFrequence->isHidden())
        {
            amplitudeFrequence->show();
        }
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
/// Обновление таблицы точек, для Tune.
/// </summary>
void Smithtry1000::TableUpdate()
{
    tableChanged = true;
    for (int j = 0; j < SystemParameters::tunedElements.size(); j++)
    {
        int id = 0;
        for (int i = 1; i < ui->pointTable->rowCount(); i++)
        {
            if (ui->pointTable->item(i, 0) == nullptr)
            {
                string str = ui->pointTable->item(i, 1)->text().toUtf8().constData();
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
                    ui->pointTable->setItem(i, 2, new QTableWidgetItem(QString::number(round(number*100)/100)
                        + temp2 + QString::number(round(abs(number2)*100)/100)));
                    if (SystemParameters::impedanceRealR == 0)
                    {
                        ui->pointTable->setItem(i, 3, new QTableWidgetItem("0"));
                    }
                    else
                    {
                        double number3 = abs(SystemParameters::tunedElements[j]->GetParameter()[Z].imag() 
                            /SystemParameters::tunedElements[j]->GetParameter()[Z].real());
                        ui->pointTable->setItem(i, 3, new QTableWidgetItem(QString::number(round(number3*100)/100)));
                    }
                }
                id++;
            }
        }
    }
    tempCircuit=*circuitElements;
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
    delete ui;
}

/// <summary>
/// Экспорт схемы в нетлист.
/// </summary>
void Smithtry1000::onExportNetlist_buttonClicked()
{
    if (circuitElements->GetCircuitElements().size() > 0)
    {
        ExportNetlist exporter = ExportNetlist(nullptr, circuitElements);

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
        QPoint centerLocal = ui->scrollArea->rect().center();
        QPoint centerGlobal = ui->scrollArea->mapToGlobal(centerLocal);
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
                if (leftClicked)
                {
                    emit left();
                    leftClicked = false;
                }
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
    if (event->button() == Qt::LeftButton) {
        leftClicked = true;
        QPoint globalPos = mapToGlobal(event->pos());
        QPoint scrollAreaPos = ui->scrollAreaDiagram->viewport()->mapFromGlobal(globalPos);
        if (ui->scrollAreaDiagram->viewport()->rect().contains(scrollAreaPos))
        {
            setCursor(Qt::ClosedHandCursor);
            moving = true;
            lastPos = event->pos();
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        rightClicked = true;
        if (SystemParameters::Model == Default)
        {
            onDelete_buttonClicked();
        }
    }
}

/// <summary>
/// Перемещение мыши.
/// </summary>
/// <param name="event"></param>
void Smithtry1000::mouseMoveEvent(QMouseEvent* event)
{
    if (leftClicked && moving) 
    {
        // Вычисляем дельту перемещения
        QPoint delta = event->pos() - lastPos;

        // Получаем scrollbars
        QScrollBar* hBar = ui->scrollAreaDiagram->horizontalScrollBar();
        QScrollBar* vBar = ui->scrollAreaDiagram->verticalScrollBar();

        // Перемещаем scrollbars в противоположном направлении
        // (чтобы создать эффект "перетаскивания" содержимого)
        if (hBar) {
            hBar->setValue(hBar->value() - delta.x());
        }
        if (vBar) {
            vBar->setValue(vBar->value() - delta.y());
        }

        lastPos = event->pos();
        event->accept();
    }
}

/// <summary>
/// Отжатие кнопки мыши.
/// </summary>
/// <param name="event"></param>
void Smithtry1000::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && leftClicked) {
        leftClicked = false;
        setCursor(Qt::ArrowCursor); // Возвращаем обычный курсор
        moving = false;
        event->accept();
    }
}

/// <summary>
/// Ввод с помощью мышки.
/// </summary>
void Smithtry1000::onButtonClicked()
{
    FrequencyDialog dialog(this, circuitElements);
    if (dialog.exec() == QDialog::Accepted&& !SystemParameters::exc)
    {
        SystemParameters::Model = AddPoint;
        QPoint centerLocal = renderArea->rect().center();
        QPoint centerGlobal = renderArea->mapToGlobal(centerLocal);
        QCursor::setPos(SystemParameters::lastPointX * SystemParameters::scale + centerGlobal.x(), SystemParameters::lastPointY * SystemParameters::scale + centerGlobal.y());
        leftClicked = false;
        rightClicked = false;
        QPoint point = QCursor::pos();
        double tempPointX, tempPointY;
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
            long double circleRadius = 1 - ((sqrt(pow(x, 2) + pow(y, 2)) - 1) / (2 * (x - 1)));
            long double xCenter = 1 - circleRadius;
            long double dx = x - xCenter;
            long double dy = y;
            long double sin_t = dy;
            long double cos_t = dx;
            if (abs(y) < 1e-6 && abs(y) >= 0)
            {
                if (y == 0 && x == 1)
                {
                    t = 0+ 0.02;
                }
                else if (x == 1&&y<0)
                {
                    t = 2 * M_PI- 0.02;
                }
                else
                {
                    t = M_PI;
                }
            }
            else
            {
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
            }
            if (x - 1 != 0)
            {
                r = (cos(t) - x) / (x - 1);
            }
            else
            {
                r = 1e9;
            }
            QPoint temp = QPoint(x * SystemParameters::scale + renderArea->rect().center().x(), y * SystemParameters::scale + renderArea->rect().center().y());
            renderArea->setCursorPosOnCircle(temp);
            if (SystemParameters::index == 0)
            {
                ui->rTable->setItem(3, 3, new QTableWidgetItem(QString::number((double)SystemParameters::frequency)));
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
                int row = ui->pointTable->rowCount();
                ui->pointTable->insertRow(row);
                ui->pointTable->setItem(row, 0, new QTableWidgetItem(QStringLiteral(u"Да")));
                ui->pointTable->setItem(row, 1, new QTableWidgetItem("DP 1"));
                SystemParameters::rImpedanceRealCalculation(x, y);
                SystemParameters::rImpedanceImagCalculation(x, y);
                QString temp2 = " + j";
                if (SystemParameters::impedanceImagR < 0)
                {
                    temp2 = " - j";
                }
                ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
                if (SystemParameters::impedanceRealR == 0)
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
                }
                else
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
                }
                ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)this->circuitElements->frequencyFirstPoint)));
                SystemParameters::index++;
                SystemParameters::dpIndex++;
                SystemParameters::allpointindex++;
                renderArea->setCursorPosOnCircle(temp);
                auxiliaryWidget->update();
            }
            else
            {
                int row = ui->pointTable->rowCount();
                ui->pointTable->insertRow(row);
                ui->pointTable->setItem(row, 0, new QTableWidgetItem(QStringLiteral(u"Нет")));
                ui->pointTable->setItem(row, 1, new QTableWidgetItem("DP " + QString::number(SystemParameters::dpIndex + SystemParameters::index)));
                SystemParameters::rImpedanceRealCalculation(x, y);
                SystemParameters::rImpedanceImagCalculation(x, y);
                QString temp2 = " + j";
                if (SystemParameters::impedanceImagR < 0)
                {
                    temp2 = " - j";
                }
                ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
                if (SystemParameters::impedanceRealR == 0)
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
                }
                else
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
                }
                ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)circuitElements->frequencyList[circuitElements->frequencyList.size() - 1])));
                Point point;
                point.x = x;
                point.y = y;
                allPoints[SystemParameters::index + SystemParameters::dpIndex - 1] = make_tuple(point, false);
                circuitElements->pointIndexes.append(SystemParameters::allpointindex);
                SystemParameters::dpIndex++;
                SystemParameters::allpointindex++;
                circuitElements->morePoints.append(point);
                renderArea->setCursorPosOnCircle(temp);
            }

            tempCircuit=*circuitElements;
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
            t = M_PI * 3 / 2- 1 / 1e9;
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
                tmin = t+ 1 / 1e9;
                t = tmin;
                tmax = M_PI * 3 / 2- 1 / 1e9;
            }
            else
            {
                r = fabs(r) * (-1);
                tmax = t- 1 / 1e9;
                t = tmax;
                tmin = M_PI * 3 / 2- 1 / 1e9;
            }
        }
        trackingEnabled = !trackingEnabled;
        while (!leftClicked && !rightClicked)
        {
            QCoreApplication::processEvents();
        }
        if (leftClicked)
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
            this->circuitElements->AddCircuitElements(new Element(ResistorShunt, r2 - r1, this->circuitElements->frequencyFirstPoint, point, chart, parameter));
            pointsX.append(SystemParameters::lastPointX);
            pointsY.append(SystemParameters::lastPointY);
            QPoint temp = QPoint(SystemParameters::lastPointX * SystemParameters::scale + renderArea->rect().center().x(), SystemParameters::lastPointY * SystemParameters::scale + renderArea->rect().center().y());
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(SystemParameters::index + SystemParameters::dpIndex)));
            SystemParameters::rImpedanceRealCalculation(point.x, point.y);
            SystemParameters::rImpedanceImagCalculation(point.x, point.y);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
            if (SystemParameters::impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)this->circuitElements->frequencyFirstPoint)));
            circuitElements->elementIndexes.append(SystemParameters::allpointindex);
            SystemParameters::index++;
            SystemParameters::allpointindex++;
            renderArea->setCursorPosOnCircle(temp);
            tempCircuit=*circuitElements;
            firstDeleted = true;
            amplitudeFrequence->MatrixCalculation();
            if (!amplitudeFrequence->isHidden())
            {
                amplitudeFrequence->show();
            }
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
            t = M_PI * 3 / 2- 1 / 1e9;
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
                tmin = t+ 1 / 1e9;
                t = tmin;
                tmax = M_PI / 2-1/1e9;
            }
            else
            {
                tmax = t- 1 / 1e9;
                t = tmax;
                tmin = -M_PI / 2+ 1 / 1e9;
            }
        }
        trackingEnabled = !trackingEnabled;
        while (!leftClicked && !rightClicked)
        {
            QCoreApplication::processEvents();
        }
        if (leftClicked)
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
            this->circuitElements->AddCircuitElements(new Element(ResistorParallel, 1000 / (r2 - r1), this->circuitElements->frequencyFirstPoint, point, chart, parameter));
            pointsX.append(SystemParameters::lastPointX);
            pointsY.append(SystemParameters::lastPointY);
            QPoint temp = QPoint(SystemParameters::lastPointX * SystemParameters::scale + renderArea->rect().center().x(), SystemParameters::lastPointY * SystemParameters::scale + renderArea->rect().center().y());
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(SystemParameters::index + SystemParameters::dpIndex)));
            SystemParameters::rImpedanceRealCalculation(point.x, point.y);
            SystemParameters::rImpedanceImagCalculation(point.x, point.y);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
            if (SystemParameters::impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)this->circuitElements->frequencyFirstPoint)));
            circuitElements->elementIndexes.append(SystemParameters::allpointindex);
            SystemParameters::index++;
            SystemParameters::allpointindex++;
            renderArea->setCursorPosOnCircle(temp);
            tempCircuit=*circuitElements;
            firstDeleted = true;
            amplitudeFrequence->MatrixCalculation();
            if (!amplitudeFrequence->isHidden())
            {
                amplitudeFrequence->show();
            }
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
        if (get<1>(allPoints[SystemParameters::allpointindex-1]))
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
                ui->rTable->setItem(3, 3, new QTableWidgetItem(""));
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
        ui->pointTable->removeRow(ui->pointTable->rowCount() - 1);
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
            tmin = t+ 0.04;
            t = tmin;
            tmax = 2 * M_PI- 0.04;
            break;
        }
        case CapacitorShunt:
        {
            tmin = 0.04;
            tmax = t- 0.04;
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
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(SystemParameters::index + SystemParameters::dpIndex)));
            SystemParameters::rImpedanceRealCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
            SystemParameters::rImpedanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR) * 100) / 100)));
            if (SystemParameters::impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)this->circuitElements->frequencyFirstPoint)));
            circuitElements->elementIndexes.append(SystemParameters::allpointindex);
            SystemParameters::index++;
            SystemParameters::allpointindex++;
            renderArea->setCursorPosOnCircle(temp);
            tempCircuit=*circuitElements;
            firstDeleted = true;
            amplitudeFrequence->MatrixCalculation();
            if (!amplitudeFrequence->isHidden())
            {
                amplitudeFrequence->show();
            }
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
            tmin = t+0.04;
            t = tmin;
            tmax = M_PI-0.04;
            break;
        }
        case CapacitorParallel:
        {
            tmin = -M_PI+0.04;
            tmax = t-0.04;
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
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(SystemParameters::index + SystemParameters::dpIndex)));
            SystemParameters::rImpedanceRealCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
            SystemParameters::rImpedanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(round((double)SystemParameters::impedanceRealR*100)/100) + temp2 + QString::number(round((double)abs(SystemParameters::impedanceImagR)*100)/100)));
            if (SystemParameters::impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR)*100)/100)));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)this->circuitElements->frequencyFirstPoint)));
            circuitElements->elementIndexes.append(SystemParameters::allpointindex);
            SystemParameters::index++;
            SystemParameters::allpointindex++;
            renderArea->setCursorPosOnCircle(temp);
            tempCircuit=*circuitElements;
            firstDeleted = true;
            amplitudeFrequence->MatrixCalculation();
            if (!amplitudeFrequence->isHidden())
            {
                amplitudeFrequence->show();
            }
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
            ui->rTable->setItem(0, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::impedanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::impedanceImagR) * 100) / 100)));
            if (SystemParameters::admitanceImagR < 0)
            {
                temp = "-j";
            }
            else
            {
                temp = "+j";
            }
            ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::admitanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::admitanceImagR) * 100) / 100)));
            if (x > 0)
            {
                ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round(((double)atan(y / x) * 180 / M_PI * -1) * 100) / 100)));
            }
            else if (y < 0)
            {
                ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
            }
            else
            {
                ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((-180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
            }
            if (SystemParameters::impedanceRealR == 0)
            {
                ui->rTable->setItem(1, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->rTable->setItem(1, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
            }
            double r = sqrt(pow(x, 2) + pow(y, 2));
            ui->rTable->setItem(0, 3, new QTableWidgetItem(QString::number(round(((- 1 - r) / (r-1))*100)/100)+":1"));
            ui->rTable->setItem(2, 3, new QTableWidgetItem(QString::number(round(-20*log10(r)*100)/100)));
        }
        else
        {
            ui->rTable->setItem(0, 1, new QTableWidgetItem(""));
            ui->rTable->setItem(1, 1, new QTableWidgetItem(""));
            ui->rTable->setItem(2, 1, new QTableWidgetItem(""));
            ui->rTable->setItem(1, 3, new QTableWidgetItem(""));
            ui->rTable->setItem(0, 3, new QTableWidgetItem(""));
            ui->rTable->setItem(2, 3, new QTableWidgetItem(""));
        }
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
/// Определение положения эмуляции курсора на диаграмме.
/// </summary>
/// <param name="dx">Перемещение по x.</param>
/// <param name="dy">Перемещение по y.</param>
/// <returns>Точка на диаграмме.</returns>
QPoint Smithtry1000::getPointOnCircle(int dx, int dy)
{
    if (SystemParameters::Model == mode::InductionShunt || SystemParameters::Model == mode::CapacitorShunt)
    {
        t = t;
        long double x, y;
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
        ui->rTable->setItem(0, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::impedanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::impedanceImagR) * 100) / 100)));
        if (SystemParameters::admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::admitanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::admitanceImagR) * 100) / 100)));
        if (x > 0)
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round(((double)atan(y / x) * 180 / M_PI * -1) * 100) / 100)));
        }
        else if (y < 0)
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
        }
        else
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((-180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
        }
        if (SystemParameters::impedanceRealR == 0)
        {
            ui->rTable->setItem(1, 3, new QTableWidgetItem("0"));
        }
        else
        {
            ui->rTable->setItem(1, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
        }
        double rtemp = sqrt(pow(x, 2) + pow(y, 2));
        ui->rTable->setItem(0, 3, new QTableWidgetItem(QString::number(round(((-1 - rtemp) / (rtemp - 1))*100)/100) + ":1"));
        ui->rTable->setItem(2, 3, new QTableWidgetItem(QString::number(round(-20 * log10(rtemp) * 100) / 100)));
        x = x * SystemParameters::scale + renderArea->rect().center().x();
        y = y * SystemParameters::scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (SystemParameters::Model == mode::InductionParallel || SystemParameters::Model == mode::CapacitorParallel)
    {
        t = t;
        long double x, y;
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
        ui->rTable->setItem(0, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::impedanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::impedanceImagR) * 100) / 100)));
        if (SystemParameters::admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::admitanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::admitanceImagR) * 100) / 100)));
        if (x > 0)
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round(((double)atan(y / x) * 180 / M_PI * -1) * 100) / 100)));
        }
        else if (y < 0)
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
        }
        else
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((-180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
        }
        if (SystemParameters::impedanceRealR == 0)
        {
            ui->rTable->setItem(1, 3, new QTableWidgetItem("0"));
        }
        else
        {
            ui->rTable->setItem(1, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
        }
        double rtemp = sqrt(pow(x, 2) + pow(y, 2));
        ui->rTable->setItem(0, 3, new QTableWidgetItem(QString::number(round(((-1 - rtemp) / (rtemp - 1))*100)/100) + ":1"));
        ui->rTable->setItem(2, 3, new QTableWidgetItem(QString::number(round(-20 * log10(rtemp) * 100) / 100)));
        x = x * SystemParameters::scale + renderArea->rect().center().x();
        y = y * SystemParameters::scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (SystemParameters::Model == mode::ResistorShunt)
    {
        long double x, y;
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
                    x = 1-step;
                }
                else
                {
                    x = SystemParameters::lastPointX + step;
                }
            }
            else if (dx<0 && SystemParameters::lastPointX>=xmin)
            {
                if (SystemParameters::lastPointX - step <= xmin)
                {
                    x = xmin +step;
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
        SystemParameters::rImpedanceRealCalculation(x, y);
        SystemParameters::rAdmitanceRealCalculation(x, y);
        SystemParameters::rImpedanceImagCalculation(x, y);
        SystemParameters::rAdmitanceImagCalculation(x, y);
        QString temp = "+j";
        if (SystemParameters::impedanceImagR < 0)
        {
            temp = "-j";
        }
        ui->rTable->setItem(0, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::impedanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::impedanceImagR) * 100) / 100)));
        if (SystemParameters::admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::admitanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::admitanceImagR) * 100) / 100)));
        if (x > 0)
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round(((double)atan(y / x) * 180 / M_PI * -1) * 100) / 100)));
        }
        else if (y < 0)
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
        }
        else
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((-180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
        }
        if (SystemParameters::impedanceRealR == 0)
        {
            ui->rTable->setItem(1, 3, new QTableWidgetItem("0"));
        }
        else
        {
            ui->rTable->setItem(1, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
        }
        double rtemp = sqrt(pow(x, 2) + pow(y, 2));
        ui->rTable->setItem(0, 3, new QTableWidgetItem(QString::number(round(((-1 - rtemp) / (rtemp - 1))*100)/100) + ":1"));
        ui->rTable->setItem(2, 3, new QTableWidgetItem(QString::number(round(-20 * log10(rtemp) * 100) / 100)));
        SystemParameters::lastPointX = x;
        SystemParameters::lastPointY = y;
        x = x * SystemParameters::scale + renderArea->rect().center().x();
        y = y * SystemParameters::scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (SystemParameters::Model == mode::ResistorParallel)
    {
        long double x, y;
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
            else if (dx<0 && SystemParameters::lastPointX>=-1)
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
        ui->rTable->setItem(0, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::impedanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::impedanceImagR) * 100) / 100)));
        if (SystemParameters::admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::admitanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::admitanceImagR) * 100) / 100)));
        if (x > 0)
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round(((double)atan(y / x) * 180 / M_PI * -1) * 100) / 100)));
        }
        else if (y < 0)
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
        }
        else
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((-180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
        }
        if (SystemParameters::impedanceRealR == 0)
        {
            ui->rTable->setItem(1, 3, new QTableWidgetItem("0"));
        }
        else
        {
            ui->rTable->setItem(1, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
        }
        double rtemp = sqrt(pow(x, 2) + pow(y, 2));
        ui->rTable->setItem(0, 3, new QTableWidgetItem(QString::number(round(((-1 - rtemp) / (rtemp - 1))*100)/100) + ":1"));
        ui->rTable->setItem(2, 3, new QTableWidgetItem(QString::number(round(-20 * log10(rtemp) * 100) / 100)));
        x = x * SystemParameters::scale + renderArea->rect().center().x();
        y = y * SystemParameters::scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (SystemParameters::Model == mode::OSLine)
    {
        t = t;
        long double x, y;
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
        ui->rTable->setItem(0, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::impedanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::impedanceImagR) * 100) / 100)));
        if (SystemParameters::admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::admitanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::admitanceImagR) * 100) / 100)));
        if (x > 0)
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round(((double)atan(y / x) * 180 / M_PI * -1) * 100) / 100)));
        }
        else if (y < 0)
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
        }
        else
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((-180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
        }
        if (SystemParameters::impedanceRealR == 0)
        {
            ui->rTable->setItem(1, 3, new QTableWidgetItem("0"));
        }
        else
        {
            ui->rTable->setItem(1, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
        }
        double rtemp = sqrt(pow(x, 2) + pow(y, 2));
        ui->rTable->setItem(0, 3, new QTableWidgetItem(QString::number(round(((-1 - rtemp) / (rtemp - 1))*100)/100) + ":1"));
        ui->rTable->setItem(2, 3, new QTableWidgetItem(QString::number(round(-20 * log10(rtemp) * 100) / 100)));
        x = x * SystemParameters::scale + renderArea->rect().center().x();
        y = y * SystemParameters::scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (SystemParameters::Model == mode::SSLine)
    {
        t = t;
        long double x, y;
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
        ui->rTable->setItem(0, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::impedanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::impedanceImagR) * 100) / 100)));
        if (SystemParameters::admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::admitanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::admitanceImagR) * 100) / 100)));
        if (x > 0)
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round(((double)atan(y / x) * 180 / M_PI * -1) * 100) / 100)));
        }
        else if (y < 0)
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
        }
        else
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((-180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
        }
        if (SystemParameters::impedanceRealR == 0)
        {
            ui->rTable->setItem(1, 3, new QTableWidgetItem("0"));
        }
        else
        {
            ui->rTable->setItem(1, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
        }
        double rtemp = sqrt(pow(x, 2) + pow(y, 2));
        ui->rTable->setItem(0, 3, new QTableWidgetItem(QString::number(round(((-1 - rtemp) / (rtemp - 1))*100)/100) + ":1"));
        ui->rTable->setItem(2, 3, new QTableWidgetItem(QString::number(round(-20 * log10(rtemp) * 100) / 100)));
        x = x * SystemParameters::scale + renderArea->rect().center().x();
        y = y * SystemParameters::scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (SystemParameters::Model == Line)
    {
        t = t;
        long double x, y;
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
        x = cos_t*R+r;
        y = sin_t*R;
        if (y >= 0 && y < 0.0001)
        {
            y = 0.0001;
        }
        else if (y <= 0 && y > -0.0001)
        {
            y = -0.0001;
        }
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
        ui->rTable->setItem(0, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::impedanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::impedanceImagR) * 100) / 100)));
        if (SystemParameters::admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::admitanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::admitanceImagR) * 100) / 100)));
        if (x > 0)
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round(((double)atan(y / x) * 180 / M_PI * -1) * 100) / 100)));
        }
        else if (y < 0)
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
        }
        else
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2))) * 100) / 100) + " / " + QString::number(round((-180 - (double)atan(y / x) * 180 / M_PI) * 100) / 100)));
        }
        if (SystemParameters::impedanceRealR == 0)
        {
            ui->rTable->setItem(1, 3, new QTableWidgetItem("0"));
        }
        else
        {
            ui->rTable->setItem(1, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
        }
        double rtemp = sqrt(pow(x, 2) + pow(y, 2));
        ui->rTable->setItem(0, 3, new QTableWidgetItem(QString::number(round(((-1 - rtemp) / (rtemp - 1))*100)/100) + ":1"));
        ui->rTable->setItem(2, 3, new QTableWidgetItem(QString::number(round(-20 * log10(rtemp) * 100) / 100)));
        x = x * SystemParameters::scale + renderArea->rect().center().x();
        y = y * SystemParameters::scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (SystemParameters::Model == Transform)
    {
        long double tprev = t;
        t = t;
        long double x, y;
        x = 0;
        y = 0;
        int dxABS = abs(dx);
        int dyABS = abs(dy);
        long double dif;
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
            else if (dx<0 && SystemParameters::lastPointX>=-1)
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
        else
        {
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
        ui->rTable->setItem(0, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::impedanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::impedanceImagR) * 100) / 100)));
        if (SystemParameters::admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)round(abs(SystemParameters::admitanceRealR) * 100) / 100) + temp + QString::number((double)round(abs(SystemParameters::admitanceImagR) * 100) / 100)));
        if (x > 0)
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2)))*100)/100) + " / " + QString::number(round(((double)atan(y / x) * 180 / M_PI * -1)*100)/100)));
        }
        else if (y < 0)
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2)))*100)/100) + " / " + QString::number(round((180 - (double)atan(y / x) * 180 / M_PI)*100)/100)));
        }
        else
        {
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(round((sqrt((double)pow(x, 2) + (double)pow(y, 2)))*100)/100) + " / " + QString::number(round(( - 180 - (double)atan(y / x) * 180 / M_PI)*100)/100)));
        }
        if (SystemParameters::impedanceRealR == 0)
        {
            ui->rTable->setItem(1, 3, new QTableWidgetItem("0"));
        }
        else
        {
            ui->rTable->setItem(1, 3, new QTableWidgetItem(QString::number(round((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR) * 100) / 100)));
        }
        double rtemp = sqrt(pow(x, 2) + pow(y, 2));
        ui->rTable->setItem(0, 3, new QTableWidgetItem(QString::number(round(((-1 - rtemp) / (rtemp - 1))*100)/100) + ":1"));
        ui->rTable->setItem(2, 3, new QTableWidgetItem(QString::number(round(-20 * log10(rtemp) * 100) / 100)));
        x = x * SystemParameters::scale + renderArea->rect().center().x();
        y = y * SystemParameters::scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else
    {
        return QPoint(0, 0);
    }
}

/// <summary>
/// Масштабирование - приближение.
/// </summary>
void Smithtry1000::onPlusSize_buttonClicked()
{
    if (SystemParameters::scale < 2000)
    {
        if (SystemParameters::scale == 1900)
        {
            ui->PlusSizeButton->setDisabled(true);
        }
        if (SystemParameters::scale == 100)
        {
            ui->MinusSizeButton->setEnabled(true);
        }
        SystemParameters::scale += 100;
        renderArea->update();
        int n = ui->scrollAreaDiagram->horizontalScrollBar()->value();
        int m = ui->scrollAreaDiagram->verticalScrollBar()->value();
        renderArea->setFixedWidth(1200 + (SystemParameters::scale - 200) * 2);
        renderArea->setFixedHeight(800 + (SystemParameters::scale - 200) * 2);
        ui->scrollAreaDiagram->horizontalScrollBar()->setValue(n * (SystemParameters::scale / (SystemParameters::scale - 100)));
        ui->scrollAreaDiagram->verticalScrollBar()->setValue(m * (SystemParameters::scale / (SystemParameters::scale - 100)));
    }
}

/// <summary>
/// Масштабирование - отдаление.
/// </summary>
void Smithtry1000::onMinusSize_buttonClicked()
{
    if (SystemParameters::scale > 100)
    {
        if (SystemParameters::scale == 200)
        {
            ui->MinusSizeButton->setDisabled(true);
        }
        if (SystemParameters::scale == 2000)
        {
            ui->PlusSizeButton->setEnabled(true);
        }
        SystemParameters::scale -= 100;
        int n = ui->scrollAreaDiagram->horizontalScrollBar()->value();
        int m = ui->scrollAreaDiagram->verticalScrollBar()->value();
        renderArea->setFixedWidth(1200 + (SystemParameters::scale - 200) * 2);
        renderArea->setFixedHeight(800 + (SystemParameters::scale - 200) * 2);
        renderArea->update();
        ui->scrollAreaDiagram->horizontalScrollBar()->setValue(n * (SystemParameters::scale / (SystemParameters::scale + 100)));
        ui->scrollAreaDiagram->verticalScrollBar()->setValue(m * (SystemParameters::scale / (SystemParameters::scale + 100)));
    }
}

/// <summary>
/// Масштабирование - стандартное значение
/// </summary>
void Smithtry1000::onDefaultSize_buttonClicked()
{
    SystemParameters::scale = 200;
    renderArea->update();
    renderArea->setFixedWidth(1200);
    renderArea->setFixedHeight(800);
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
/// Масштабирование в зависимости от пропорций окна.
/// </summary>
/// <param name="event"></param>
void Smithtry1000::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    SystemParameters::sizeChanged = true;
    renderArea->update();
    if (event->oldSize().width() != -1)
    {
        long double coef1 = (long double)event->size().width() / (long double)event->oldSize().width();
        long double coef2 = (long double)event->size().height() / (long double)event->oldSize().height();
        long double coef = coef1 * coef2;
        SystemParameters::scale = SystemParameters::scale * coef;
        int n = ui->scrollAreaDiagram->horizontalScrollBar()->value();
        int m = ui->scrollAreaDiagram->verticalScrollBar()->value();
        renderArea->setFixedWidth(1200 + (SystemParameters::scale - 200) * 2);
        renderArea->setFixedHeight(800 + (SystemParameters::scale - 200) * 2);
        ui->scrollAreaDiagram->horizontalScrollBar()->setValue(n * (SystemParameters::scale / (SystemParameters::scale - 100)));
        ui->scrollAreaDiagram->verticalScrollBar()->setValue(m * (SystemParameters::scale / (SystemParameters::scale - 100)));
    }
}