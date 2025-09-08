#include "Smithtry1000.h"
#include <QCursor>
#include <QPoint>
#include <QRect>
#include "Smithtry1000.h"
#include <QCursor>
#include <QPoint>
#include <QRect>
#include <QtMath>
#include <QThread>
#include <cmath>
#include <exception>


mode Model;


Smithtry1000::Smithtry1000(QWidget* parent, SParameters* sParameters1)
    : QMainWindow(parent)
    , ui(new Ui::Smithtry1000Class())
    , trackingEnabled(false)
{
    ui->setupUi(this);
    this->sParameters = sParameters1;
    Model = Default;
    this->resize(1600, 920);
    this->setMinimumSize(1630, 920);
    ui->pointTable->setColumnCount(5);
    ui->pointTable->setRowCount(1);
    ui->pointTable->setColumnWidth(0, 40);
    ui->pointTable->setColumnWidth(1, 35);
    ui->pointTable->setColumnWidth(2, 150);
    ui->pointTable->setColumnWidth(3, 70);
    ui->pointTable->setColumnWidth(4, 85);
    ui->pointTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->pointTable->setItem(0, 0, new QTableWidgetItem("Start"));
    ui->pointTable->setItem(0, 1, new QTableWidgetItem("ID"));
    ui->pointTable->setItem(0, 2, new QTableWidgetItem("Z"));
    ui->pointTable->setItem(0, 3, new QTableWidgetItem("Q"));
    ui->pointTable->setItem(0, 4, new QTableWidgetItem("Frequency"));
    ui->rTable->setRowCount(4);
    ui->rTable->setColumnCount(2);
    ui->rTable->setColumnWidth(1, 200);
    ui->rTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->rTable->setItem(1, 0, new QTableWidgetItem("Z"));
    ui->rTable->setItem(2, 0, new QTableWidgetItem("Y"));
    ui->rTable->setItem(3, 0, new QTableWidgetItem("G"));
    tmin = 0;
    tmax = 2 * M_PI;
    auxiliaryWidget->setMinimumWidth(2000);
    auxiliaryWidget->setMinimumHeight(400);
    ui->scrollArea->setWidget(auxiliaryWidget);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    auxiliaryWidget->addSvg(QString(":/Images/load.svg"), 40, 39);
    auxiliaryWidget->addSvg(QString(":/Images/source.svg"), 80, 39);
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
   // connect(ui->S11Button, &QPushButton::clicked, this, &Smithtry1000::onS11_buttonClicked);
 //   connect(ui->S22Button, &QPushButton::clicked, this, &Smithtry1000::onS22_buttonClicked);
    connect(ui->ExportNetlist, &QPushButton::clicked, this, &Smithtry1000::onExportNetlist_buttonClicked);
    connect(ui->Tune, &QPushButton::clicked, this, &Smithtry1000::onTune_buttonClicked);
    connect(ui->Line_button, &QPushButton::clicked, this, &Smithtry1000::onLine_buttonClicked);
    connect(ui->OSLine_button, &QPushButton::clicked, this, &Smithtry1000::onOSLine_buttonClicked);
    connect(ui->SSLine_button, &QPushButton::clicked, this, &Smithtry1000::onSSLine_buttonClicked);
    connect(ui->actionColors, &QAction::triggered, this, &Smithtry1000::onMenuToolsCliked);
    QObject::connect(sParameters->set, &ColourSetting::signalS12S21, this, &Smithtry1000::getS12S21signal);

    QObject::connect(sParameters->set, &ColourSetting::signalDVS, this, &Smithtry1000::getsignalDVS);

    QObject::connect(sParameters->set, &ColourSetting::signal, this, &Smithtry1000::getsignal);
    QObject::connect(tuneWidget, &TuneWidget::remove, auxiliaryWidget, &CircuitWidget::RemoveElement);
    QObject::connect(tuneWidget, &TuneWidget::removeAll, auxiliaryWidget, &CircuitWidget::RemoveAll);
    QObject::connect(auxiliaryWidget, &CircuitWidget::clicked, tuneWidget, &TuneWidget::GetSignal);
    renderArea->setMinimumHeight(800);
    renderArea->setMinimumWidth(1200);
    ui->scrollAreaDiagram->setWidget(renderArea);
    ui->scrollAreaDiagram->setWidgetResizable(true);
    ui->scrollAreaDiagram->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollAreaDiagram->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Smithtry1000::onTimeout);
    timer->start(10);  // Частое обновление для плавности
}

void Smithtry1000::closeEvent(QCloseEvent* event)
{
    this->amplitudeFrequence->close();
    this->tuneWidget->close();
    this->sParameters->Close();
}


void Smithtry1000::onLine_buttonClicked()
{
    if (pointsX.size() > 0)
    {
        LinesDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted)
        {
            Model = mode::Line;
            auxiliaryWidget->update();
            leftClicked = false;
            rightClicked = false;
            QPoint centerLocal = renderArea->rect().center();
            QPoint centerGlobal = renderArea->mapToGlobal(centerLocal);
            Complex zl, yl;
            auxiliaryWidget->addSvg(QString(":/Images/horizontal_line_circuit.svg"), (index + 2) * 40, 20);
            QCursor::setPos(centerGlobal);
            this->setCursor(Qt::BlankCursor); // скрываем системный курсор
            double x;
            double y;
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
            if (y >= 0 && y < 0.000001)
            {
                y = 0.01;
            }
            else if (y <= 0 && y > -0.000001)
            {
                y = -0.01;
            }
            Complex g1 = (zl - double(50)) / (zl + double(50));
            Complex z3 = SystemParameters::z0line * (zl + Complex(0, SystemParameters::z0line)) / (SystemParameters::z0line + Complex(0, 1) * zl);
            Complex g3 = (z3 - double(50)) / (z3 + double(50));
            double center = 0.5 * (pow(g1.real(), 2) + pow(g1.imag(), 2) - pow(g3.real(), 2) - pow(g3.imag(), 2)) / (g1.real() - g3.real());
            double R = abs(center - g1);
            double dx = x - center;
            double dy = y;
            dy *= -1;
            double sin_t = dy;
            double cos_t = dx;
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
                rAdmitanceImagCalculation(pointsX[pointsX.size() - 1], pointsY[pointsY.size() - 1]);
                double r1 = admitanceImagR;
                rAdmitanceImagCalculation(lastPointX, lastPointY);
                double r2 = admitanceImagR;
                Point point;
                point.x = lastPointX;
                point.y = lastPointY;
                allPoints[index + dpIndex - 1] = make_tuple(point, true);
                Complex z = zCalculation(lastPointX, lastPointY);
                Complex y2 = yCalculation(lastPointX, lastPointY);
                map<parameterMode, Complex> parameter;
                parameter[Z] = z;
                parameter[Y] = y2;
                Complex g;
                if (x >= 0)
                {
                    g = Complex(pow(x, 2) + pow(y, 2), atan(y / x) * 180 / M_PI * -1);
                }
                else if (y <= 0)
                {
                    g = Complex(pow(x, 2) + pow(y, 2), 180 - atan(y / x) * 180 / M_PI);
                }
                else
                {
                    g = Complex(pow(x, 2) + pow(y, 2), -180 - atan(y / x) * 180 / M_PI);
                }
                parameter[G] = g;
                map<chartMode, tuple<double, double>> chart;
                Complex rRealImpedance = impedanceRealChartParameters(lastPointX, lastPointY);
                Complex rImagImpedance = impedanceImagChartParameters(lastPointX, lastPointY);
                Complex rRealAdmitance = admitanceRealChartParameters(lastPointX, lastPointY);
                Complex rImagAdmitance = admitanceImagChartParameters(lastPointX, lastPointY);
                chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
                chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
                chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
                chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
                double RL = zl.real();
                double XL = zl.imag();
                double R = z.real();
                double X = z.imag();
                double RR = R - RL;
                double sq = -sqrt(RR * (RL * (pow(X, 2) + pow(R, 2)) - R * (pow(XL, 2) + pow(RL, 2)))) / RR;
                double tanO1 = RR * sq / (R * XL + RL * X);
                double tanO2 = -RR * sq / (R * XL + RL * X);
                double z0;
                double O;
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
                double Theta = O * 180 / M_PI;
                double L = O * 299792458 / (2*M_PI * 1e9);
                double Length = L * 1e3;
                double Lambda = L * 1e9 / 299792458;
                LinesElement* temp3 = new LinesElement(Line, SystemParameters::z0line, this->circuitElements->frequencyFirstPoint, point, chart, parameter,
                    L * 1000, L * 1000 / sqrt(SystemParameters::er), Theta, Lambda, SystemParameters::alpha);
                this->circuitElements->AddCircuitElements(temp3);
                pointsX.append(lastPointX);
                pointsY.append(lastPointY);
                QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
                points[index] = make_tuple(point, r, t, Model);
                int row = ui->pointTable->rowCount();
                ui->pointTable->insertRow(row);
                ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(index + dpIndex)));
                rImpedanceRealCalculation(lastPointX, lastPointY);
                rImpedanceImagCalculation(lastPointX, lastPointY);
                QString temp2 = " + j";
                if (impedanceImagR < 0)
                {
                    temp2 = " - j";
                }
                ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(impedanceRealR) + temp2 + QString::number(impedanceImagR)));
                if (impedanceRealR == 0)
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
                }
                else
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(abs(impedanceImagR / impedanceRealR))));
                }
                ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number(frequency)));
                index++;
                renderArea->setCursorPosOnCircle(temp);
            }
            if (rightClicked)
            {
                QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
                renderArea->setCursorPosOnCircle(temp);
                auxiliaryWidget->removeLastSvg();
                auxiliaryWidget->update();
            }
            this->unsetCursor(); // возвращаем курсор
            Model = Default;
        }
    }
}

void Smithtry1000::onOSLine_buttonClicked()
{
    if (pointsX.size() > 0)
    {
        VerticalLinesDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted)
        {
            Model = mode::OSLine;
            VerticalLines();
        }
    }
}

void Smithtry1000::onSSLine_buttonClicked()
{
    if (pointsX.size() > 0)
    {
        VerticalLinesDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted)
        {
            Model = mode::SSLine;
            VerticalLines();
        }
    }
}

void Smithtry1000::VerticalLines()
{
    auxiliaryWidget->update();
    leftClicked = false;
    rightClicked = false;
    QPoint centerLocal = renderArea->rect().center();
    QPoint centerGlobal = renderArea->mapToGlobal(centerLocal);
    Complex zl, yl;
    switch (Model)
    {
    case OSLine:
    {
        auxiliaryWidget->addSvg(QString(":/Images/os_circuit.svg"), (index + 2) * 40, 39);
        break;
    }
    case SSLine:
    {
        auxiliaryWidget->addSvg(QString(":/Images/ss_circuit.svg"), (index + 2) * 40, 39);
        break;
    }
    }
    QCursor::setPos(centerGlobal);
    this->setCursor(Qt::BlankCursor); // скрываем системный курсор
    double x;
    double y;
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
    if (y >= 0 && y < 0.000001)
    {
        y = 0.01;
    }
    else if (y <= 0 && y > -0.000001)
    {
        y = -0.01;
    }
    double circleRadius = -1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 + 2 * x));
    double xCenter = -1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    dy *= -1;
    double sin_t = dy;
    double cos_t = dx;
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
    tmin = -M_PI;
    tmax = M_PI;
    trackingEnabled = !trackingEnabled;
    while (!leftClicked && !rightClicked)
    {
        QCoreApplication::processEvents();
    }
    if (leftClicked)
    {
        rAdmitanceImagCalculation(pointsX[pointsX.size() - 1], pointsY[pointsY.size() - 1]);
        double r1 = admitanceImagR;
        rAdmitanceImagCalculation(lastPointX, lastPointY);
        double r2 = admitanceImagR;
        Point point;
        point.x = lastPointX;
        point.y = lastPointY;
        allPoints[index + dpIndex - 1] = make_tuple(point, true);
        Complex z = zCalculation(lastPointX, lastPointY);
        Complex y2 = yCalculation(lastPointX, lastPointY);
        map<parameterMode, Complex> parameter;
        parameter[Z] = z;
        parameter[Y] = y2;
        Complex g;
        if (x >= 0)
        {
            g = Complex(pow(x, 2) + pow(y, 2), atan(y / x) * 180 / M_PI * -1);
        }
        else if (y <= 0)
        {
            g = Complex(pow(x, 2) + pow(y, 2), 180 - atan(y / x) * 180 / M_PI);
        }
        else
        {
            g = Complex(pow(x, 2) + pow(y, 2), -180 - atan(y / x) * 180 / M_PI);
        }
        parameter[G] = g;
        map<chartMode, tuple<double, double>> chart;
        Complex rRealImpedance = impedanceRealChartParameters(lastPointX, lastPointY);
        Complex rImagImpedance = impedanceImagChartParameters(lastPointX, lastPointY);
        Complex rRealAdmitance = admitanceRealChartParameters(lastPointX, lastPointY);
        Complex rImagAdmitance = admitanceImagChartParameters(lastPointX, lastPointY);
        chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
        chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
        chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
        chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
        switch (Model)
        {
        case OSLine:
        {
            double theta;
            double lambda;
            double o;
            double l;
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
            double theta;
            double lambda;
            double o;
            double l;
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
        pointsX.append(lastPointX);
        pointsY.append(lastPointY);
        QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
        points[index] = make_tuple(point, r, t, Model);
        int row = ui->pointTable->rowCount();
        ui->pointTable->insertRow(row);
        ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(index + dpIndex)));
        rImpedanceRealCalculation(lastPointX, lastPointY);
        rImpedanceImagCalculation(lastPointX, lastPointY);
        QString temp2 = " + j";
        if (impedanceImagR < 0)
        {
            temp2 = " - j";
        }
        ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(impedanceRealR) + temp2 + QString::number(impedanceImagR)));
        if (impedanceRealR == 0)
        {
            ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
        }
        else
        {
            ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(abs(impedanceImagR / impedanceRealR))));
        }
        ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number(frequency)));
        index++;
        renderArea->setCursorPosOnCircle(temp);
    }
    if (rightClicked)
    {
        QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
        renderArea->setCursorPosOnCircle(temp);
        auxiliaryWidget->removeLastSvg();
        auxiliaryWidget->update();
    }
    this->unsetCursor(); // возвращаем курсор
    Model = Default;
}

void Smithtry1000::TableUpdate()
{
    tableChanged = true;
    for (int j = 0; j < SystemParameters::tunedElements.size(); j++)
    {
        for (int i = 1; i < ui->pointTable->rowCount(); i++)
        {
            int id = 0;
            if (ui->pointTable->item(i, 0) == nullptr)
            {
                string str = ui->pointTable->item(i, 1)->text().toUtf8().constData();
                size_t pos = str.find(' ');
                string temp = str.substr(pos + 1);
                if (circuitElements->GetCircuitElements()[id] == SystemParameters::tunedElements[j])
                {
                    QString temp2 = " + j";
                    if (impedanceImagR < 0)
                    {
                        temp2 = " - j";
                    }
                    ui->pointTable->setItem(i, 2, new QTableWidgetItem(QString::number(SystemParameters::tunedElements[j]->GetParameter()[Z].real())
                        + temp2 + QString::number(SystemParameters::tunedElements[j]->GetParameter()[Z].imag())));
                    if (impedanceRealR == 0)
                    {
                        ui->pointTable->setItem(i, 3, new QTableWidgetItem("0"));
                    }
                    else
                    {
                        ui->pointTable->setItem(i, 3, new QTableWidgetItem(QString::number(abs(SystemParameters::tunedElements[j]->GetParameter()[Z].imag() /
                            SystemParameters::tunedElements[j]->GetParameter()[Z].real()))));
                    }
                }
                id++;
            }
        }
    }
    SystemParameters::tunedElements = {};
    tableChanged = false;
}

Smithtry1000::~Smithtry1000()
{
    delete ui;
}

void Smithtry1000::onExportNetlist_buttonClicked()
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
}

/// <summary>
/// Обработка нажатий кнопок мыши.
/// </summary>
/// <param name="event"></param>
void Smithtry1000::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        leftClicked = true;
    }
    else if (event->button() == Qt::RightButton)
    {
        rightClicked = true;
        if (Model == Default)
        {
            onDelete_buttonClicked();
        }
    }
}

void Smithtry1000::onButtonClicked()
{
    FrequencyDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        Model = mode::AddPoint;
        QPoint centerLocal = renderArea->rect().center();
        QPoint centerGlobal = renderArea->mapToGlobal(centerLocal);
        QCursor::setPos(lastPointX * scale + centerGlobal.x(), lastPointY * scale + centerGlobal.y());
        leftClicked = false;
        rightClicked = false;
        QPoint point = QCursor::pos();
        while (!leftClicked && !rightClicked)
        {
            QCoreApplication::processEvents();
            point = QCursor::pos();
            if (pow(point.x() - centerGlobal.x(), 2) + pow(point.y() - centerGlobal.y(), 2) >= pow(scale, 2))
            {
                QCursor::setPos(tempPointX, tempPointY);
                point.setX(tempPointX);
                point.setY(tempPointY);
            }
            tempPointX = point.x();
            tempPointY = point.y();
        }
        if (leftClicked)
        {
            double x = point.x();
            double y = point.y();
            x = (x - centerGlobal.x()) / scale;
            y = (y - centerGlobal.y()) / scale;
            if (y >= 0 && y < 0.000001)
            {
                y = 0.01;
            }
            else if (y <= 0 && y > -0.000001)
            {
                y = -0.01;
            }
            double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
            double xCenter = 1 - circleRadius;
            double dx = x - xCenter;
            double dy = y;
            double sin_t = dy;
            double cos_t = dx;
            if (y < 1e-6 && y >= 0)
            {
                if (y == 0 && x == 1)
                {
                    t = 0;
                }
                else if (x == 1)
                {
                    t = 2 * M_PI;
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
            QPoint temp = QPoint(x * scale + renderArea->rect().center().x(), y * scale + renderArea->rect().center().y());
            renderArea->setCursorPosOnCircle(temp);
            if (index == 0)
            {
                pointsX.append(x);
                pointsY.append(y);
                lastPointX = x;
                lastPointY = y;
                Point point = Point();
                point.x = x;
                point.y = y;
                circuitElements->firstPoint = point;
                allPoints[0] = make_tuple(point, false);
                points[index] = make_tuple(point, r, t, mode::AddPoint);
                rImpedanceRealCalculation(x, y);
                double r1 = impedanceRealR;
                circuitElements->realFirstPoint = r1;
                rImpedanceImagCalculation(x, y);
                double r2 = impedanceImagR;
                circuitElements->imagFirstPoint = r2;
                Complex z = zCalculation(lastPointX, lastPointY);
                Complex y2 = yCalculation(lastPointX, lastPointY);
                circuitElements->z = z;
                circuitElements->y = y2;
                Complex g;
                if (x >= 0)
                {
                    g = Complex(pow(x, 2) + pow(y, 2), atan(y / x) * 180 / M_PI * -1);
                }
                else if (y <= 0)
                {
                    g = Complex(pow(x, 2) + pow(y, 2), 180 - atan(y / x) * 180 / M_PI);
                }
                else
                {
                    g = Complex(pow(x, 2) + pow(y, 2), -180 - atan(y / x) * 180 / M_PI);
                }
                circuitElements->g = g;
                circuitElements->frequencyFirstPoint = frequency;
                map<chartMode, tuple<double, double>> chart;
                Complex rRealImpedance = impedanceRealChartParameters(point.x, point.y);
                Complex rImagImpedance = impedanceImagChartParameters(point.x, point.y);
                Complex rRealAdmitance = admitanceRealChartParameters(point.x, point.y);
                Complex rImagAdmitance = admitanceImagChartParameters(point.x, point.y);
                chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
                chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
                chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
                chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
                circuitElements->chart = chart;
                int row = ui->pointTable->rowCount();
                ui->pointTable->insertRow(row);
                ui->pointTable->setItem(row, 0, new QTableWidgetItem("Yes"));
                ui->pointTable->setItem(row, 1, new QTableWidgetItem("DP 1"));
                rImpedanceRealCalculation(x, y);
                rImpedanceImagCalculation(x, y);
                QString temp2 = " + j";
                if (impedanceImagR < 0)
                {
                    temp2 = " - j";
                }
                ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(impedanceRealR) + temp2 + QString::number(impedanceImagR)));
                if (impedanceRealR == 0)
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
                }
                else
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(impedanceImagR / impedanceRealR)));
                }
                ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number(frequency)));
                index++;
                dpIndex++;
                renderArea->setCursorPosOnCircle(temp);
                auxiliaryWidget->update();
            }
            else
            {
                int row = ui->pointTable->rowCount();
                ui->pointTable->insertRow(row);
                ui->pointTable->setItem(row, 0, new QTableWidgetItem("No"));
                ui->pointTable->setItem(row, 1, new QTableWidgetItem("DP " + QString::number(dpIndex + index)));
                rImpedanceRealCalculation(x, y);
                rImpedanceImagCalculation(x, y);
                QString temp2 = " + j";
                if (impedanceImagR < 0)
                {
                    temp2 = " - j";
                }
                ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(impedanceRealR) + temp2 + QString::number(impedanceImagR)));
                if (impedanceRealR == 0)
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
                }
                else
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(abs(impedanceImagR / impedanceRealR))));
                }
                ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number(frequencyList[frequencyList.size() - 1])));
                Point point;
                point.x = x;
                point.y = y;
                allPoints[index + dpIndex - 1] = make_tuple(point, false);
                dpIndex++;
                morePoints.append(point);
                renderArea->setCursorPosOnCircle(temp);
            }
        }
        Model = Default;
    }
}

void Smithtry1000::onInduction_buttonClicked()
{
    Model = mode::InductionShunt;
    ImaginaryImpedance();
}

void Smithtry1000::onCapacitor_buttonClicked()
{
    Model = mode::CapacitorShunt;
    ImaginaryImpedance();
}

void Smithtry1000::onResistor_buttonClicked()
{
    Model = mode::ResistorShunt;


    auxiliaryWidget->update();
    leftClicked = false;
    rightClicked = false;
    QPoint centerLocal = renderArea->rect().center();
    QPoint centerGlobal = renderArea->mapToGlobal(centerLocal);
    if (pointsX.size() > 0)
    {
        auxiliaryWidget->addSvg(QString(":/Images/horizontal_r.svg"), (index + 2) * 40, 20);
        QCursor::setPos(centerGlobal);
        this->setCursor(Qt::BlankCursor); // скрываем системный курсор
        double cos_t;
        double sin_t;
        double x;
        double y;
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
        if (y >= 0 && y < 0.000001)
        {
            y = 0.01;
        }
        else if (y <= 0 && y > -0.000001)
        {
            y = -0.01;
        }
        double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
        double xCenter = 1 - circleRadius;
        double dx = x - xCenter;
        double dy = y;
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
            r = abs(r);
            tmin = t;
            tmax = M_PI * 3 / 2;
        }
        else
        {
            r = abs(r) * (-1);
            tmax = t;
            tmin = M_PI * 3 / 2;
        }
        trackingEnabled = !trackingEnabled;
        while (!leftClicked && !rightClicked)
        {
            QCoreApplication::processEvents();
        }
        if (leftClicked)
        {
            rImpedanceRealCalculation(pointsX[pointsX.size() - 1], pointsY[pointsY.size() - 1]);
            double r1 = impedanceRealR;
            rImpedanceRealCalculation(lastPointX, lastPointY);
            double r2 = impedanceRealR;
            Point point;
            point.x = lastPointX;
            point.y = lastPointY;
            allPoints[index + dpIndex - 1] = make_tuple(point, true);
            Complex z = zCalculation(lastPointX, lastPointY);
            Complex y2 = yCalculation(lastPointX, lastPointY);
            map<parameterMode, Complex> parameter;
            parameter[Z] = z;
            parameter[Y] = y2;
            Complex g;
            if (x >= 0)
            {
                g = Complex(pow(x, 2) + pow(y, 2), atan(y / x) * 180 / M_PI * -1);
            }
            else if (y <= 0)
            {
                g = Complex(pow(x, 2) + pow(y, 2), 180 - atan(y / x) * 180 / M_PI);
            }
            else
            {
                g = Complex(pow(x, 2) + pow(y, 2), -180 - atan(y / x) * 180 / M_PI);
            }
            parameter[G] = g;
            map<chartMode, tuple<double, double>> chart;
            Complex rRealImpedance = impedanceRealChartParameters(lastPointX, lastPointY);
            Complex rImagImpedance = impedanceImagChartParameters(lastPointX, lastPointY);
            Complex rRealAdmitance = admitanceRealChartParameters(lastPointX, lastPointY);
            Complex rImagAdmitance = admitanceImagChartParameters(lastPointX, lastPointY);
            chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
            chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
            chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
            chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
            this->circuitElements->AddCircuitElements(new Element(ResistorShunt, r2 - r1, this->circuitElements->frequencyFirstPoint, point, chart, parameter));
            pointsX.append(lastPointX);
            pointsY.append(lastPointY);
            QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
            points[index] = make_tuple(point, r, t, mode::ResistorShunt);
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(index + dpIndex)));
            rImpedanceRealCalculation(point.x, point.y);
            rImpedanceImagCalculation(point.x, point.y);
            QString temp2 = " + j";
            if (impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(impedanceRealR) + temp2 + QString::number(impedanceImagR)));
            if (impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(abs(impedanceImagR / impedanceRealR))));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number(frequency)));
            index++;
            renderArea->setCursorPosOnCircle(temp);
        }
        if (rightClicked)
        {
            QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
            renderArea->setCursorPosOnCircle(temp);
            auxiliaryWidget->removeLastSvg();
            auxiliaryWidget->update();
        }
        Model = Default;
        this->unsetCursor(); // возвращаем курсор
    }
}

void Smithtry1000::onInductionParallel_buttonClicked()
{
    Model = mode::InductionParallel;
    ImaginaryAdmitance();
}

void Smithtry1000::onCapacitorParallel_buttonClicked()
{
    Model = mode::CapacitorParallel;
    ImaginaryAdmitance();
}

void Smithtry1000::onResistorParallel_buttonClicked()
{
    Model = mode::ResistorParallel;
    auxiliaryWidget->update();
    leftClicked = false;
    rightClicked = false;
    QPoint centerLocal = renderArea->rect().center();
    QPoint centerGlobal = renderArea->mapToGlobal(centerLocal);
    if (pointsX.size() > 0)
    {
        auxiliaryWidget->addSvg(QString(":/Images/vertical_r_circuit.svg"), (index + 2) * 40, 39);
        QCursor::setPos(centerGlobal);
        this->setCursor(Qt::BlankCursor); // скрываем системный курсор
        double cos_t;
        double sin_t;
        double x;
        double y;
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
        if (y >= 0 && y < 0.000001)
        {
            y = 0.01;
        }
        else if (y <= 0 && y > -0.000001)
        {
            y = -0.01;
        }
        double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y, 2)) / (-2 * y);
        double yCenter = -circleRadius;
        double dx = x + 1;
        double dy = y - yCenter;
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
            tmin = t;
            tmax = M_PI / 2;
        }
        else
        {
            tmax = t;
            tmin = -M_PI / 2;
        }
        trackingEnabled = !trackingEnabled;
        while (!leftClicked && !rightClicked)
        {
            QCoreApplication::processEvents();
        }
        if (leftClicked)
        {
            rAdmitanceRealCalculation(pointsX[pointsX.size() - 1], pointsY[pointsY.size() - 1]);
            double r1 = admitanceRealR;
            rAdmitanceRealCalculation(lastPointX, lastPointY);
            double r2 = admitanceRealR;
            Point point;
            point.x = lastPointX;
            point.y = lastPointY;
            allPoints[index + dpIndex - 1] = make_tuple(point, true);
            Complex z = zCalculation(lastPointX, lastPointY);
            Complex y2 = yCalculation(lastPointX, lastPointY);
            map<parameterMode, Complex> parameter;
            parameter[Z] = z;
            parameter[Y] = y2;
            Complex g;
            if (x >= 0)
            {
                g = Complex(pow(x, 2) + pow(y, 2), atan(y / x) * 180 / M_PI * -1);
            }
            else if (y <= 0)
            {
                g = Complex(pow(x, 2) + pow(y, 2), 180 - atan(y / x) * 180 / M_PI);
            }
            else
            {
                g = Complex(pow(x, 2) + pow(y, 2), -180 - atan(y / x) * 180 / M_PI);
            }
            parameter[G] = g;
            map<chartMode, tuple<double, double>> chart;
            Complex rRealImpedance = impedanceRealChartParameters(lastPointX, lastPointY);
            Complex rImagImpedance = impedanceImagChartParameters(lastPointX, lastPointY);
            Complex rRealAdmitance = admitanceRealChartParameters(lastPointX, lastPointY);
            Complex rImagAdmitance = admitanceImagChartParameters(lastPointX, lastPointY);
            chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
            chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
            chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
            chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
            this->circuitElements->AddCircuitElements(new Element(ResistorParallel, 1000 / (r2 - r1), this->circuitElements->frequencyFirstPoint, point, chart, parameter));
            pointsX.append(lastPointX);
            pointsY.append(lastPointY);
            QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
            points[index] = make_tuple(point, r, t, mode::ResistorParallel);
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(index + dpIndex)));
            rImpedanceRealCalculation(point.x, point.y);
            rImpedanceImagCalculation(point.x, point.y);
            QString temp2 = " + j";
            if (impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(impedanceRealR) + temp2 + QString::number(impedanceImagR)));
            if (impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(abs(impedanceImagR / impedanceRealR))));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number(frequency)));
            index++;
            renderArea->setCursorPosOnCircle(temp);
        }
        if (rightClicked)
        {
            QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
            renderArea->setCursorPosOnCircle(temp);
            auxiliaryWidget->removeLastSvg();
            auxiliaryWidget->update();
        }
        Model = Default;
        this->unsetCursor(); // возвращаем курсор
    }
}

void Smithtry1000::onDelete_buttonClicked()
{
    if (allPoints.size() > 0 && !SystemParameters::tuneBlock)
    {
        if (get<1>(allPoints[allPoints.size() - 1]))
        {
            points.erase(index - 1);
            auxiliaryWidget->removeLastSvg();
            renderArea->update();
            auxiliaryWidget->update();
            this->circuitElements->DeleteCircuitElements();
            pointsX.pop_back();
            pointsY.pop_back();
            index--;
        }
        else
        {
            if (allPoints.size() == 1)
            {
                points.erase(index - 1);
                dpIndex--;
                this->circuitElements->imagFirstPoint = -9999;
                this->circuitElements->realFirstPoint = -9999;
                this->circuitElements->frequencyFirstPoint = -9999;
                this->circuitElements->z = Complex(-9999, -9999);
                this->circuitElements->y = Complex(-9999, -9999);
                this->circuitElements->g = Complex(-9999, -9999);
                this->circuitElements->firstPoint = Point();
                pointsX.pop_back();
                pointsY.pop_back();
                index--;
            }
            else
            {
                morePoints.pop_back();
                dpIndex--;
            }
        }
        ui->pointTable->removeRow(ui->pointTable->rowCount() - 1);
        allPoints.erase(allPoints.size() - 1);
        renderArea->update();
        auxiliaryWidget->update();
    }
}

void Smithtry1000::ImaginaryImpedance()
{
    auxiliaryWidget->update();
    leftClicked = false;
    rightClicked = false;
    QPoint centerLocal = renderArea->rect().center();
    QPoint centerGlobal = renderArea->mapToGlobal(centerLocal);
    if (pointsX.size() > 0)
    {
        switch (Model)
        {
        case InductionShunt:
        {
            auxiliaryWidget->addSvg(QString(":/Images/horizontal_i.svg"), (index + 2) * 40, 20);
            break;
        }
        case CapacitorShunt:
        {
            auxiliaryWidget->addSvg(QString(":/Images/horizontal_c.svg"), (index + 2) * 40, 20);
            break;
        }
        }
        QCursor::setPos(centerGlobal);
        this->setCursor(Qt::BlankCursor); // скрываем системный курсор
        double x;
        double y;
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
        if (y >= 0 && y < 0.000001)
        {
            y = 0.01;
        }
        else if (y <= 0 && y > -0.000001)
        {
            y = -0.01;
        }
        double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
        double xCenter = 1 - circleRadius;
        double dx = x - xCenter;
        double dy = y;
        double sin_t = dy;
        double cos_t = dx;
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
        switch (Model)
        {
        case InductionShunt:
        {
            tmin = t;
            tmax = 2 * M_PI;
            break;
        }
        case CapacitorShunt:
        {
            tmin = 0.001;
            tmax = t;
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
            rImpedanceImagCalculation(pointsX[pointsX.size() - 1], pointsY[pointsY.size() - 1]);
            double r1 = impedanceImagR;
            rImpedanceImagCalculation(lastPointX, lastPointY);
            double r2 = impedanceImagR;
            Point point;
            point.x = lastPointX;
            point.y = lastPointY;
            allPoints[index + dpIndex - 1] = make_tuple(point, true);
            Complex z = zCalculation(lastPointX, lastPointY);
            Complex y2 = yCalculation(lastPointX, lastPointY);
            map<parameterMode, Complex> parameter;
            parameter[Z] = z;
            parameter[Y] = y2;
            Complex g;
            if (x >= 0)
            {
                g = Complex(pow(x, 2) + pow(y, 2), atan(y / x) * 180 / M_PI * -1);
            }
            else if (y <= 0)
            {
                g = Complex(pow(x, 2) + pow(y, 2), 180 - atan(y / x) * 180 / M_PI);
            }
            else
            {
                g = Complex(pow(x, 2) + pow(y, 2), -180 - atan(y / x) * 180 / M_PI);
            }
            parameter[G] = g;
            map<chartMode, tuple<double, double>> chart;
            Complex rRealImpedance = impedanceRealChartParameters(lastPointX, lastPointY);
            Complex rImagImpedance = impedanceImagChartParameters(lastPointX, lastPointY);
            Complex rRealAdmitance = admitanceRealChartParameters(lastPointX, lastPointY);
            Complex rImagAdmitance = admitanceImagChartParameters(lastPointX, lastPointY);
            chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
            chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
            chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
            chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
            switch (Model)
            {
            case InductionShunt:
            {
                this->circuitElements->AddCircuitElements(new Element(InductionShunt, (r2 - r1) / (2 * M_PI * 1e6 * frequency), this->circuitElements->frequencyFirstPoint, point, chart, parameter));
                break;
            }
            case CapacitorShunt:
            {
                this->circuitElements->AddCircuitElements(new Element(CapacitorShunt, 1 / ((r1 - r2) * (2 * M_PI * 1e6 * frequency)), this->circuitElements->frequencyFirstPoint, point, chart, parameter));
                break;
            }
            }
            pointsX.append(lastPointX);
            pointsY.append(lastPointY);
            QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
            points[index] = make_tuple(point, r, t, Model);
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(index + dpIndex)));
            rImpedanceRealCalculation(lastPointX, lastPointY);
            rImpedanceImagCalculation(lastPointX, lastPointY);
            QString temp2 = " + j";
            if (impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(impedanceRealR) + temp2 + QString::number(impedanceImagR)));
            if (impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(abs(impedanceImagR / impedanceRealR))));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number(frequency)));
            index++;
            renderArea->setCursorPosOnCircle(temp);
        }
        if (rightClicked)
        {
            QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
            renderArea->setCursorPosOnCircle(temp);

            auxiliaryWidget->removeLastSvg();
            auxiliaryWidget->update();
        }
        this->unsetCursor(); // возвращаем курсор
    }
    Model = Default;
}

void Smithtry1000::ImaginaryAdmitance()
{
    auxiliaryWidget->update();
    leftClicked = false;
    rightClicked = false;
    QPoint centerLocal = renderArea->rect().center();
    QPoint centerGlobal = renderArea->mapToGlobal(centerLocal);
    if (pointsX.size() > 0)
    {
        switch (Model)
        {
        case InductionParallel:
        {
            auxiliaryWidget->addSvg(QString(":/Images/vertical_i_circuit.svg"), (index + 2) * 40, 39);
            break;
        }
        case CapacitorParallel:
        {
            auxiliaryWidget->addSvg(QString(":/Images/vertical_c_circuit.svg"), (index + 2) * 40, 39);
            break;
        }
        }
        QCursor::setPos(centerGlobal);
        this->setCursor(Qt::BlankCursor); // скрываем системный курсор
        double x;
        double y;
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
        if (y >= 0 && y < 0.000001)
        {
            y = 0.01;
        }
        else if (y <= 0 && y > -0.000001)
        {
            y = -0.01;
        }
        double circleRadius = -1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 + 2 * x));
        double xCenter = -1 - circleRadius;
        double dx = x - xCenter;
        double dy = y;
        dy *= -1;
        double sin_t = dy;
        double cos_t = dx;
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
        switch (Model)
        {
        case InductionParallel:
        {
            tmin = t;
            tmax = M_PI;
            break;
        }
        case CapacitorParallel:
        {
            tmin = -M_PI;
            tmax = t;
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
            rAdmitanceImagCalculation(pointsX[pointsX.size() - 1], pointsY[pointsY.size() - 1]);
            double r1 = admitanceImagR;
            rAdmitanceImagCalculation(lastPointX, lastPointY);
            double r2 = admitanceImagR;
            Point point;
            point.x = lastPointX;
            point.y = lastPointY;
            allPoints[index + dpIndex - 1] = make_tuple(point, true);
            Complex z = zCalculation(lastPointX, lastPointY);
            Complex y2 = yCalculation(lastPointX, lastPointY);
            Complex g;
            map<parameterMode, Complex> parameter;
            parameter[Z] = z;
            parameter[Y] = y2;
            if (x >= 0)
            {
                g = Complex(pow(x, 2) + pow(y, 2), atan(y / x) * 180 / M_PI * -1);
            }
            else if (y <= 0)
            {
                g = Complex(pow(x, 2) + pow(y, 2), 180 - atan(y / x) * 180 / M_PI);
            }
            else
            {
                g = Complex(pow(x, 2) + pow(y, 2), -180 - atan(y / x) * 180 / M_PI);
            }
            parameter[G] = g;
            map<chartMode, tuple<double, double>> chart;
            Complex rRealImpedance = impedanceRealChartParameters(lastPointX, lastPointY);
            Complex rImagImpedance = impedanceImagChartParameters(lastPointX, lastPointY);
            Complex rRealAdmitance = admitanceRealChartParameters(lastPointX, lastPointY);
            Complex rImagAdmitance = admitanceImagChartParameters(lastPointX, lastPointY);
            chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
            chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
            chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
            chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
            switch (Model)
            {
            case InductionParallel:
            {
                this->circuitElements->AddCircuitElements(new Element(InductionParallel, M_PI / (r1 - r2) * 100 / frequency * 500 / 1e9, this->circuitElements->frequencyFirstPoint, point, chart, parameter));
                break;
            }
            case CapacitorParallel:
            {
                this->circuitElements->AddCircuitElements(new Element(CapacitorParallel, (r2 - r1) / M_PI * 500 / frequency / 1e12, this->circuitElements->frequencyFirstPoint, point, chart, parameter));
                break;
            }
            }
            pointsX.append(lastPointX);
            pointsY.append(lastPointY);
            QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
            points[index] = make_tuple(point, r, t, Model);
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(index + dpIndex)));
            rImpedanceRealCalculation(lastPointX, lastPointY);
            rImpedanceImagCalculation(lastPointX, lastPointY);
            QString temp2 = " + j";
            if (impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(impedanceRealR) + temp2 + QString::number(impedanceImagR)));
            if (impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(abs(impedanceImagR / impedanceRealR))));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number(frequency)));
            index++;
            renderArea->setCursorPosOnCircle(temp);
        }
        if (rightClicked)
        {
            QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
            renderArea->setCursorPosOnCircle(temp);
            auxiliaryWidget->removeLastSvg();
            auxiliaryWidget->update();
        }
        this->unsetCursor(); // возвращаем курсор
    }
    Model = Default;
}

void Smithtry1000::rImpedanceRealCalculation(double x, double y)
{
    if (y >= 0 && y < 0.000001)
    {
        y = 0.01;
    }
    else if (y <= 0 && y > -0.000001)
    {
        y = -0.01;
    }
    double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
    double xCenter = 1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    double sin_t = dy;
    double cos_t = dx;
    double t1;
    t1 = atan(sin_t / cos_t);
    if (cos_t < 0 && sin_t < 0)
    {
        t1 += M_PI;
    }
    else if (cos_t > 0 && sin_t < 0)
    {
        t1 = 2 * M_PI - abs(t1);
    }
    else if (sin_t > 0 && cos_t < 0)
    {
        t1 = M_PI - abs(t1);
    }
    if (x - 1 != 0)
    {
        impedanceRealR = abs((cos(t1) - x) / (x - 1));
    }
    impedanceRealR *= 50;
}

void Smithtry1000::rAdmitanceRealCalculation(double x, double y)
{
    if (y >= 0 && y < 0.000001)
    {
        y = 0.01;
    }
    else if (y <= 0 && y > -0.000001)
    {
        y = -0.01;
    }
    double circleRadius = -1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 + 2 * x));
    double xCenter = -1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    dy *= -1;
    double sin_t = dy;
    double cos_t = dx;
    double t1;
    t1 = atan(sin_t / cos_t);
    if (cos_t < 0 && sin_t < 0)
    {
        t1 = abs(t1) - M_PI;
    }
    else if (sin_t > 0 && cos_t < 0)
    {
        t1 = M_PI - abs(t1);
    }
    if (x - 1 != 0)
    {
        admitanceRealR = abs((cos(t1) - x) / (x + 1));
    }
    admitanceRealR *= 20;
}

void Smithtry1000::rImpedanceImagCalculation(double x, double y)
{
    double cos_t;
    double sin_t;
    if (y >= 0 && y < 0.000001)
    {
        y = 0.01;
    }
    else if (y <= 0 && y > -0.000001)
    {
        y = -0.01;
    }
    double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
    double xCenter = 1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    sin_t = dy;
    cos_t = dx;
    double t1;
    t1 = atan(cos_t / sin_t);
    if (y < 0)
    {
        t1 += M_PI;
    }
    else
    {
        t1 += 2 * M_PI;
    }
    if (x - 1 != 0)
    {
        impedanceImagR = cos(t1) / (x - 1);
    }
    else
    {
        impedanceImagR = (1 + sin(t1)) / y;
    }
    if (y < 0)
    {
        impedanceImagR = abs(impedanceImagR);
    }
    else
    {
        impedanceImagR = abs(impedanceImagR) * (-1);
    }
    impedanceImagR *= 50;
}

void Smithtry1000::rAdmitanceImagCalculation(double x, double y)
{
    if (y >= 0 && y < 0.000001)
    {
        y = 0.01;
    }
    else if (y <= 0 && y > -0.000001)
    {
        y = -0.01;
    }
    double cos_t;
    double sin_t;
    double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y, 2)) / (-2 * y);
    double yCenter = -circleRadius;
    double dx = x + 1;
    double dy = y - yCenter;
    sin_t = -dy;
    cos_t = dx;
    double t1;
    t1 = atan(sin_t / cos_t);
    if (x + 1 != 0)
    {
        admitanceImagR = cos(t1) / (x + 1);
    }
    else
    {
        admitanceImagR = (1 + sin(t1)) / y;
    }
    if (y > 0)
    {
        admitanceImagR *= -1;
    }
    admitanceImagR *= -20;
}

void Smithtry1000::onTimeout()
{
    QPoint centerLocal = renderArea->rect().center();
    QPoint centerGlobal = renderArea->mapToGlobal(centerLocal);
    if (SystemParameters::tuned)
    {
        renderArea->update();
        auxiliaryWidget->update();
        if (tableChanged == false && SystemParameters::tunedElements.size() > 0)
        {
            TableUpdate();
        }
        SystemParameters::tuned = false;
    }
    if (Model == AddPoint || Model == Default)
    {
        QPoint temp = QCursor::pos();
        double x = temp.x();
        double y = temp.y();
        x = (x - centerGlobal.x()) / scale;
        y = (y - centerGlobal.y()) / scale;
        if (pow(x, 2) + pow(y, 2) <= 1)
        {
            rImpedanceRealCalculation(x, y);
            rAdmitanceRealCalculation(x, y);
            rImpedanceImagCalculation(x, y);
            rAdmitanceImagCalculation(x, y);
            QString temp = "+j";
            if (impedanceImagR < 0)
            {
                temp = "-j";
            }
            ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number(impedanceRealR) + temp + QString::number(impedanceImagR)));
            if (admitanceImagR < 0)
            {
                temp = "-j";
            }
            else
            {
                temp = "+j";
            }
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(admitanceRealR) + temp + QString::number(admitanceImagR)));
            if (x >= 0)
            {
                ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(atan(y / x) * 180 / M_PI * -1)));
            }
            else if (y <= 0)
            {
                ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(180 - atan(y / x) * 180 / M_PI)));
            }
            else
            {
                ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(-180 - atan(y / x) * 180 / M_PI)));
            }
        }
        else
        {
            ui->rTable->setItem(1, 1, new QTableWidgetItem(""));
            ui->rTable->setItem(2, 1, new QTableWidgetItem(""));
            ui->rTable->setItem(3, 1, new QTableWidgetItem(""));
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
        // Вычисляем точку на окружности и ставим туда курсор
        QPoint posOnCircle = getPointOnCircle(dx, dy);
        /*if (pow(posOnCircle.x() - centerLocal.x(), 2) + pow(posOnCircle.y() - centerLocal.y(), 2) > pow(scale, 2))
        {
            QCursor::setPos(tempX, tempY);
            posOnCircle.setX(tempX);
            posOnCircle.setY(tempY);
        }
        tempX = posOnCircle.x();
        tempY = posOnCircle.y();*/
        QCursor::setPos(renderArea->mapToGlobal(posOnCircle));
        renderArea->setCursorPosOnCircle(posOnCircle);
        // Возвращаем системный курсор обратно в центр
        QCursor::setPos(centerGlobal);
    }
}

QPoint Smithtry1000::getPointOnCircle(int dx, int dy)
{
    if (Model == mode::InductionShunt || Model == mode::CapacitorShunt)
    {
        t = t;
        double x, y;
        int dxABS = abs(dx);
        int dyABS = abs(dy);
        double dif;
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
            step = 0.01;
            t = tmax;
            t -= step;
        }
        else if (t <= tmin)
        {
            t = tmin;
            step = 0.01;
            t += step;
        }

        double cos_t = cos(t);
        double sin_t = sin(t);
        x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
        y = (1 / (r + 1)) * sin_t;
        if (y >= 0 && y < 0.000001)
        {
            y = 0.01;
        }
        else if (y <= 0 && y > -0.000001)
        {
            y = -0.01;
        }
        lastPointX = x;
        lastPointY = y;
        rImpedanceRealCalculation(x, y);
        rAdmitanceRealCalculation(x, y);
        rImpedanceImagCalculation(x, y);
        rAdmitanceImagCalculation(x, y);
        QString temp = "+j";
        if (impedanceImagR < 0)
        {
            temp = "-j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number(impedanceRealR) + temp + QString::number(impedanceImagR)));
        if (admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(admitanceRealR) + temp + QString::number(admitanceImagR)));
        if (x >= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(atan(y / x) * 180 / M_PI * -1)));
        }
        else if (y <= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(180 - atan(y / x) * 180 / M_PI)));
        }
        else
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(-180 - atan(y / x) * 180 / M_PI)));
        }
        x = x * scale + renderArea->rect().center().x();
        y = y * scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (Model == mode::InductionParallel || Model == mode::CapacitorParallel)
    {
        t = t;
        double x, y;
        int dxABS = abs(dx);
        int dyABS = abs(dy);
        double dif;
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
        }
        else if (t <= tmin)
        {
            t = tmin;
            step = 0.01;
            t += step;
        }

        double cos_t = cos(t);
        double sin_t = sin(t);

        x = (cos(t) - r) / (r + 1);
        y = (1 / (r + 1)) * sin_t * -1;
        if (y >= 0 && y < 0.000001)
        {
            y = 0.01;
        }
        else if (y <= 0 && y > -0.000001)
        {
            y = -0.01;
        }
        lastPointX = x;
        lastPointY = y;
        rImpedanceRealCalculation(x, y);
        rAdmitanceRealCalculation(x, y);
        rImpedanceImagCalculation(x, y);
        rAdmitanceImagCalculation(x, y);
        QString temp = "+j";
        if (impedanceImagR < 0)
        {
            temp = "-j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number(impedanceRealR) + temp + QString::number(impedanceImagR)));
        if (admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(admitanceRealR) + temp + QString::number(admitanceImagR)));
        if (x >= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(atan(y / x) * 180 / M_PI * -1)));
        }
        else if (y <= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(180 - atan(y / x) * 180 / M_PI)));
        }
        else
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(-180 - atan(y / x) * 180 / M_PI)));
        }
        x = x * scale + renderArea->rect().center().x();
        y = y * scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (Model == mode::ResistorShunt)
    {
        t = t;
        double x, y;
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
        if (lastPointY > 0)
        {
            dx *= -1;
        }
        if (dx == 0 && dy == 0)
        {
        }
        else if ((dx < 0 && abs(lastPointY) <= abs(lastPointX - 1) && flag == false) || (flag == true && dy > 0 && lastPointY >= 0) || (flag == true && dy > 0 && lastPointY <= 0) || (dx > 0 && abs(lastPointY) >= abs(lastPointX - 1) && flag == false))
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
        else if ((dx > 0 && abs(lastPointY) <= abs(lastPointX - 1) && flag == false) || (flag == true && dy < 0 && lastPointY <= 0) || (flag == true && dy < 0 && lastPointY >= 0) || (dx < 0 && abs(lastPointY) >= abs(lastPointX - 1) && flag == false))
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
            step = 0.01;
            t = tmax;
            t -= step;
        }
        else if (t <= tmin)
        {
            t = tmin;
            step = 0.01;
            t += step;
        }
        double cos_t = cos(t);
        double sin_t = sin(t);
        x = 1 + (1 / r) * cos_t;
        y = (1 / r) + (1 / r) * sin_t;
        y = y * (-1);
        if (y >= 0 && y < 0.000001)
        {
            y = 0.01;
        }
        else if (y <= 0 && y > -0.000001)
        {
            y = -0.01;
        }
        rImpedanceRealCalculation(x, y);
        rAdmitanceRealCalculation(x, y);
        rImpedanceImagCalculation(x, y);
        rAdmitanceImagCalculation(x, y);
        QString temp = "+j";
        if (impedanceImagR < 0)
        {
            temp = "-j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number(impedanceRealR) + temp + QString::number(impedanceImagR)));
        if (admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(admitanceRealR) + temp + QString::number(admitanceImagR)));
        if (x >= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(atan(y / x) * 180 / M_PI * -1)));
        }
        else if (y <= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(180 - atan(y / x) * 180 / M_PI)));
        }
        else
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(-180 - atan(y / x) * 180 / M_PI)));
        }
        lastPointX = x;
        lastPointY = y;
        x = x * scale + renderArea->rect().center().x();
        y = y * scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (Model == mode::ResistorParallel)
    {
        t = t;
        double x, y;
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
        if (lastPointY > 0)
        {
            dx *= -1;
        }
        if (dx == 0 && dy == 0)
        {
        }
        else if ((dx < 0 && abs(lastPointY) <= abs(lastPointX + 1) && flag == false) || (flag == true && dy < 0 && lastPointY >= 0) || (flag == true && dy < 0 && lastPointY <= 0) || (dx > 0 && abs(lastPointY) >= abs(lastPointX + 1) && flag == false))
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
        else if ((dx > 0 && abs(lastPointY) <= abs(lastPointX + 1) && flag == false) || (flag == true && dy > 0 && lastPointY <= 0) || (flag == true && dy > 0 && lastPointY >= 0) || (dx < 0 && abs(lastPointY) >= abs(lastPointX + 1) && flag == false))
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
        double cos_t = cos(t);
        double sin_t = sin(t);
        if (lastPointY < 0)
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
        if (y >= 0 && y < 0.000001)
        {
            y = 0.01;
        }
        else if (y <= 0 && y > -0.000001)
        {
            y = -0.01;
        }
        lastPointX = x;
        lastPointY = y;
        rImpedanceRealCalculation(x, y);
        rAdmitanceRealCalculation(x, y);
        rImpedanceImagCalculation(x, y);
        rAdmitanceImagCalculation(x, y);
        QString temp = "+j";
        if (impedanceImagR < 0)
        {
            temp = "-j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number(impedanceRealR) + temp + QString::number(impedanceImagR)));
        if (admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(admitanceRealR) + temp + QString::number(admitanceImagR)));
        if (x >= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(atan(y / x) * 180 / M_PI * -1)));
        }
        else if (y <= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(180 - atan(y / x) * 180 / M_PI)));
        }
        else
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(-180 - atan(y / x) * 180 / M_PI)));
        }
        x = x * scale + renderArea->rect().center().x();
        y = y * scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (Model == mode::OSLine)
    {
        t = t;
        double x, y;
        int dxABS = abs(dx);
        int dyABS = abs(dy);
        double dif;
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

        double cos_t = cos(t);
        double sin_t = sin(t);

        x = (cos(t) - r) / (r + 1);
        y = (1 / (r + 1)) * sin_t * -1;
        if (y >= 0 && y < 0.000001)
        {
            y = 0.01;
        }
        else if (y <= 0 && y > -0.000001)
        {
            y = -0.01;
        }
        lastPointX = x;
        lastPointY = y;
        rImpedanceRealCalculation(x, y);
        rAdmitanceRealCalculation(x, y);
        rImpedanceImagCalculation(x, y);
        rAdmitanceImagCalculation(x, y);
        QString temp = "+j";
        if (impedanceImagR < 0)
        {
            temp = "-j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number(impedanceRealR) + temp + QString::number(impedanceImagR)));
        if (admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(admitanceRealR) + temp + QString::number(admitanceImagR)));
        if (x >= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(atan(y / x) * 180 / M_PI * -1)));
        }
        else if (y <= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(180 - atan(y / x) * 180 / M_PI)));
        }
        else
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(-180 - atan(y / x) * 180 / M_PI)));
        }
        x = x * scale + renderArea->rect().center().x();
        y = y * scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (Model == mode::SSLine)
    {
        t = t;
        double x, y;
        int dxABS = abs(dx);
        int dyABS = abs(dy);
        double dif;
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

        double cos_t = cos(t);
        double sin_t = sin(t);

        x = (cos(t) - r) / (r + 1);
        y = (1 / (r + 1)) * sin_t * -1;
        if (y >= 0 && y < 0.000001)
        {
            y = 0.01;
        }
        else if (y <= 0 && y > -0.000001)
        {
            y = -0.01;
        }
        lastPointX = x;
        lastPointY = y;
        rImpedanceRealCalculation(x, y);
        rAdmitanceRealCalculation(x, y);
        rImpedanceImagCalculation(x, y);
        rAdmitanceImagCalculation(x, y);
        QString temp = "+j";
        if (impedanceImagR < 0)
        {
            temp = "-j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number(impedanceRealR) + temp + QString::number(impedanceImagR)));
        if (admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(admitanceRealR) + temp + QString::number(admitanceImagR)));
        if (x >= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(atan(y / x) * 180 / M_PI * -1)));
        }
        else if (y <= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(180 - atan(y / x) * 180 / M_PI)));
        }
        else
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(-180 - atan(y / x) * 180 / M_PI)));
        }
        x = x * scale + renderArea->rect().center().x();
        y = y * scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (Model == Line)
    {
        t = t;
        double x, y;
        int dxABS = abs(dx);
        int dyABS = abs(dy);
        double dif;
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

        double cos_t = cos(t);
        double sin_t = sin(t);
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
        Complex g1 = (zl - double(50)) / (zl + double(50));
        Complex z3 = SystemParameters::z0line * (zl + Complex(0, SystemParameters::z0line)) / (SystemParameters::z0line + Complex(0, 1) * zl);
        Complex g3 = (z3 - double(50)) / (z3 + double(50));
        double center = 0.5 * (pow(g1.real(), 2) + pow(g1.imag(), 2) - pow(g3.real(), 2) - pow(g3.imag(), 2)) / (g1.real() - g3.real());
        double R = abs(center - g1);
        x = cos_t*R+r;
        y = sin_t*R;
        if (y >= 0 && y < 0.000001)
        {
            y = 0.01;
        }
        else if (y <= 0 && y > -0.000001)
        {
            y = -0.01;
        }
        lastPointX = x;
        lastPointY = y;
        rImpedanceRealCalculation(x, y);
        rAdmitanceRealCalculation(x, y);
        rImpedanceImagCalculation(x, y);
        rAdmitanceImagCalculation(x, y);
        QString temp = "+j";
        if (impedanceImagR < 0)
        {
            temp = "-j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number(impedanceRealR) + temp + QString::number(impedanceImagR)));
        if (admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(admitanceRealR) + temp + QString::number(admitanceImagR)));
        if (x >= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(atan(y / x) * 180 / M_PI * -1)));
        }
        else if (y <= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(180 - atan(y / x) * 180 / M_PI)));
        }
        else
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number(pow(x, 2) + pow(y, 2)) + " / " + QString::number(-180 - atan(y / x) * 180 / M_PI)));
        }
        x = x * scale + renderArea->rect().center().x();
        y = y * scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
}

void Smithtry1000::onPlusSize_buttonClicked()
{
    if (scale < 2000)
    {
        scale += 100;
        renderArea->update();
        int n = ui->scrollAreaDiagram->horizontalScrollBar()->value();
        int m = ui->scrollAreaDiagram->verticalScrollBar()->value();
        renderArea->setFixedWidth(1200 + (scale - 200) * 2);
        renderArea->setFixedHeight(800 + (scale - 200) * 2);
        ui->scrollAreaDiagram->horizontalScrollBar()->setValue(n * (scale / (scale - 100)));
        ui->scrollAreaDiagram->verticalScrollBar()->setValue(m * (scale / (scale - 100)));
    }
}

void Smithtry1000::onMinusSize_buttonClicked()
{
    if (scale > 100)
    {
        scale -= 100;
        int n = ui->scrollAreaDiagram->horizontalScrollBar()->value();
        int m = ui->scrollAreaDiagram->verticalScrollBar()->value();
        renderArea->setFixedWidth(1200 + (scale - 200) * 2);
        renderArea->setFixedHeight(800 + (scale - 200) * 2);
        renderArea->update();
        ui->scrollAreaDiagram->horizontalScrollBar()->setValue(n * (scale / (scale + 100)));
        ui->scrollAreaDiagram->verticalScrollBar()->setValue(m * (scale / (scale + 100)));
    }
}

void Smithtry1000::onDefaultSize_buttonClicked()
{
    scale = 200;
    renderArea->update();
    renderArea->setFixedWidth(1200);
    renderArea->setFixedHeight(800);
}

void Smithtry1000::onGraph_buttonClicked()
{
    if (pointsX.size() > 1)
    {
        amplitudeFrequence->MatrixCalculation();

        amplitudeFrequence->show();
        amplitudeFrequence->activateWindow();
    }
}

Complex Smithtry1000::zCalculation(double x, double y)
{
    rImpedanceRealCalculation(x, y);
    rImpedanceImagCalculation(x, y);
    return Complex(impedanceRealR, impedanceImagR);
}

Complex Smithtry1000::yCalculation(double x, double y)
{
    rAdmitanceRealCalculation(x, y);
    rAdmitanceImagCalculation(x, y);
    return Complex(admitanceRealR, admitanceImagR);
}

Complex Smithtry1000::impedanceRealChartParameters(double x, double y)
{
    if (y >= 0 && y < 0.000001)
    {
        y = 0.01;
    }
    else if (y <= 0 && y > -0.000001)
    {
        y = -0.01;
    }
    double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
    double xCenter = 1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    double sin_t = dy;
    double cos_t = dx;
    double t1, r1;
    t1 = atan(sin_t / cos_t);
    if (cos_t < 0 && sin_t < 0)
    {
        t1 += M_PI;
    }
    else if (cos_t > 0 && sin_t < 0)
    {
        t1 = 2 * M_PI - abs(t1);
    }
    else if (sin_t > 0 && cos_t < 0)
    {
        t1 = M_PI - abs(t1);
    }
    if (x - 1 != 0)
    {
        r1 = (cos(t1) - x) / (x - 1);
    }
    return Complex(r1, t1);
}

Complex Smithtry1000::admitanceRealChartParameters(double x, double y)
{
    if (y >= 0 && y < 0.000001)
    {
        y = 0.01;
    }
    else if (y <= 0 && y > -0.000001)
    {
        y = -0.01;
    }
    double circleRadius = -1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 + 2 * x));
    double xCenter = -1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    dy *= -1;
    double sin_t = dy;
    double cos_t = dx;
    double t1, r1;
    t1 = atan(sin_t / cos_t);
    if (cos_t < 0 && sin_t < 0)
    {
        t1 = abs(t1) - M_PI;
    }
    else if (sin_t > 0 && cos_t < 0)
    {
        t1 = M_PI - abs(t1);
    }
    if (x - 1 != 0)
    {
        r1 = abs((cos(t1) - x) / (x + 1));
    }
    return Complex(r1, t1);
}

Complex Smithtry1000::impedanceImagChartParameters(double x, double y)
{
    double cos_t;
    double sin_t;
    if (y >= 0 && y < 0.000001)
    {
        y = 0.01;
    }
    else if (y <= 0 && y > -0.000001)
    {
        y = -0.01;
    }
    double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
    double xCenter = 1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    sin_t = dy;
    cos_t = dx;
    double t1, r1;
    t1 = atan(cos_t / sin_t);
    if (y < 0)
    {
        t1 += M_PI;
    }
    else
    {
        t1 += 2 * M_PI;
    }
    if (x - 1 != 0)
    {
        r1 = cos(t1) / (x - 1);
    }
    else
    {
        r1 = (1 + sin(t1)) / y;
    }
    if (y < 0)
    {
        r1 = abs(r1);
    }
    else
    {
        r1 = abs(r1) * (-1);
    }
    return Complex(r1, t1);
}

Complex Smithtry1000::admitanceImagChartParameters(double x, double y)
{
    double cos_t;
    double sin_t;
    if (y >= 0 && y < 0.000001)
    {
        y = 0.01;
    }
    else if (y <= 0 && y > -0.0001)
    {
        y = -0.01;
    }
    double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y, 2)) / (-2 * y);
    double yCenter = -circleRadius;
    double dx = x + 1;
    double dy = y - yCenter;
    sin_t = -dy;
    cos_t = dx;
    double t1, r1;
    t1 = atan(sin_t / cos_t);
    if (x + 1 != 0)
    {
        r1 = cos(t1) / (x + 1);
    }
    else
    {
        r1 = (1 + sin(t1)) / y;
    }
    if (y > 0)
    {
        r1 *= -1;
    }
    return Complex(r1, t1);
}

void Smithtry1000::onS11_buttonClicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open S-Parameter File"), "", tr("S2P Files (*.s2p;*.s1p);;All Files (*)"));
    sParameters->Show();
}

void Smithtry1000::onS22_buttonClicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open S-Parameter File"), "", tr("S2P Files (*.s2p;*.s1p);;All Files (*)"));
    sParameters->Show();
}

void Smithtry1000::getsignal()
{
    if (pointsX.size() > 1)
    {
        amplitudeFrequence->MatrixCalculation();
        amplitudeFrequence->update();
    }
}

void Smithtry1000::onMenuToolsCliked()
{
    sParameters->set->show();
}

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

void Smithtry1000::getsignalDVS()
{
    SystemParameters::colorChanged = true;
    renderArea->update();
}


void Smithtry1000::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    SystemParameters::sizeChanged = true;
    renderArea->update();
    if (event->oldSize().width() != -1)
    {
        double coef1 = (double)event->size().width() / (double)event->oldSize().width();
        double coef2 = (double)event->size().height() / (double)event->oldSize().height();
        double coef = coef1 * coef2;
        scale = scale * coef;
        int n = ui->scrollAreaDiagram->horizontalScrollBar()->value();
        int m = ui->scrollAreaDiagram->verticalScrollBar()->value();
        renderArea->setFixedWidth(1200 + (scale - 200) * 2);
        renderArea->setFixedHeight(800 + (scale - 200) * 2);
        ui->scrollAreaDiagram->horizontalScrollBar()->setValue(n * (scale / (scale - 100)));
        ui->scrollAreaDiagram->verticalScrollBar()->setValue(m * (scale / (scale - 100)));
    }
}