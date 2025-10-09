#include "Smithtry1000.h"
#include <QCursor>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
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
    //connect(ui->S11Button, &QPushButton::clicked, this, &Smithtry1000::onS11_buttonClicked);
    //connect(ui->S22Button, &QPushButton::clicked, this, &Smithtry1000::onS22_buttonClicked);
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
    QObject::connect(circlesWidget, &CirclesWidget::circle, this, &Smithtry1000::getCirclesSignal);
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
    if (index > 1)
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
}

/// <summary>
/// Загрузка проекта.
/// </summary>
void Smithtry1000::Load()
{
    if (index == 0)
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open project"), "", tr("JSON Files (*.json)"));
        try
        {
            circuitElements->loadFromFile(fileName);
            dpIndex = 1;
            index = circuitElements->GetCircuitElements().size()+1;
            allPoints[0] = make_tuple(circuitElements->firstPoint, false);
            pointsX.append(circuitElements->firstPoint.x);
            pointsY.append(circuitElements->firstPoint.y);
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 0, new QTableWidgetItem("Yes"));
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("DP 1"));
            SystemParameters::rImpedanceRealCalculation(circuitElements->firstPoint.x, circuitElements->firstPoint.y);
            SystemParameters::rImpedanceImagCalculation(circuitElements->firstPoint.x, circuitElements->firstPoint.y);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number((double)round(SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number((double)round(SystemParameters::impedanceImagR * 100) / 100)));
            if (SystemParameters::impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR))));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)frequency)));
            QString name;
            int j = 0;
            int k = 0;
            for (int i = 0; i < circuitElements->GetCircuitElements().size()+circuitElements->morePoints.size(); i++)
            {
                if (circuitElements->elementIndexes[j] == i+1)
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
                    ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number((double)round(SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number((double)round(SystemParameters::impedanceImagR * 100) / 100)));
                    if (SystemParameters::impedanceRealR == 0)
                    {
                        ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
                    }
                    else
                    {
                        ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR))));
                    }
                    ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)frequency)));
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
                    auxiliaryWidget->addSvg(QString(":/Images/" + name + ".svg"), (j + 3) * 40, val);
                    pointsX.append(circuitElements->GetCircuitElements()[j]->GetPoint().x);
                    pointsY.append(circuitElements->GetCircuitElements()[j]->GetPoint().y);
                    j++;
                }
                else
                {
                    int row = ui->pointTable->rowCount();
                    ui->pointTable->insertRow(row);
                    ui->pointTable->setItem(row, 0, new QTableWidgetItem("No"));
                    ui->pointTable->setItem(row, 1, new QTableWidgetItem("DP " + QString::number(i + 2)));
                    SystemParameters::rImpedanceRealCalculation(circuitElements->morePoints[k].x, circuitElements->morePoints[k].y);
                    SystemParameters::rImpedanceImagCalculation(circuitElements->morePoints[k].x, circuitElements->morePoints[k].y);
                    QString temp2 = " + j";
                    if (SystemParameters::impedanceImagR < 0)
                    {
                        temp2 = " - j";
                    }
                    ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number((double)round(SystemParameters::impedanceRealR * 100) / 100) + temp2 + QString::number((double)round(SystemParameters::impedanceImagR * 100) / 100)));
                    if (SystemParameters::impedanceRealR == 0)
                    {
                        ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
                    }
                    else
                    {
                        ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR))));
                    }
                    ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)frequency)));
                    allPoints[i + 1] = make_tuple(circuitElements->morePoints[k], false);
                    k++;
                }
            }
            allpointindex = index + circuitElements->morePoints.size();
            renderArea->update();
            auxiliaryWidget->update();
        }
        catch (exception e)
        {

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
    else if (pointsX.size() > 0)
    {
        y0 = circuitElements->firstPoint.y;
    }
    if (pointsX.size() > 0 && abs(y0)>=0.01)
    {
        Model = mode::Transform;
        auxiliaryWidget->update();
        leftClicked = false;
        rightClicked = false;
        QPoint centerLocal = renderArea->rect().center();
        QPoint centerGlobal = renderArea->mapToGlobal(centerLocal);
        Complex zl, yl;
        auxiliaryWidget->addSvg(QString(":/Images/vertical_transform_circuit.svg"), (index + 2) * 40, 39);
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
        if (y >= 0 && y < 0.0001)
        {
            y = 0.0001;
        }
        else if (y <= 0 && y > -0.0001)
        {
            y = -0.0001;
        }
        long double q = zl.imag() / zl.real();
        long double ycenter = -1 / q;
        long double R = sqrt(1 + 1 / pow(q, 2));
        long double dx = x;
        long double dy = y+ycenter;
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
        tmin = -M_PI;
        tmax = M_PI;
        trackingEnabled = !trackingEnabled;
        while (!leftClicked && !rightClicked)
        {
            QCoreApplication::processEvents();
        }
        if (leftClicked)
        {
            SystemParameters::rAdmitanceImagCalculation(pointsX[pointsX.size() - 1], pointsY[pointsY.size() - 1]);
            long double r1 = SystemParameters::admitanceImagR;
            SystemParameters::rAdmitanceImagCalculation(lastPointX, lastPointY);
            long double r2 = SystemParameters::admitanceImagR;
            Point point;
            point.x = lastPointX;
            point.y = lastPointY;
            allPoints[index + dpIndex - 1] = make_tuple(point, true);
            Complex z = SystemParameters::zCalculation(lastPointX, lastPointY);
            Complex y2 = SystemParameters::yCalculation(lastPointX, lastPointY);
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
            map<chartMode, tuple<long double, long double>> chart;
            Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(lastPointX, lastPointY);
            Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(lastPointX, lastPointY);
            Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(lastPointX, lastPointY);
            Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(lastPointX, lastPointY);
            chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
            chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
            chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
            chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
            long double n = sqrt(z.real() / zl.real());
            this->circuitElements->AddCircuitElements(new Element(Transform, n, this->circuitElements->frequencyFirstPoint, point, chart, parameter));
            pointsX.append(lastPointX);
            pointsY.append(lastPointY);
            QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
            points[index] = make_tuple(point, r, t, Model);
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(index + dpIndex)));
            SystemParameters::rImpedanceRealCalculation(lastPointX, lastPointY);
            SystemParameters::rImpedanceImagCalculation(lastPointX, lastPointY);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceRealR) + temp2 + QString::number((double)SystemParameters::impedanceImagR)));
            if (SystemParameters::impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR))));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)frequency)));
            circuitElements->elementIndexes.append(allpointindex);
            index++;
            allpointindex++;
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

/// <summary>
/// Линия передач.
/// </summary>
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
            Complex g1 = (zl - long double(50)) / (zl + long double(50));
            Complex z3 = SystemParameters::z0line * (zl + Complex(0, SystemParameters::z0line)) / (SystemParameters::z0line + Complex(0, 1) * zl);
            Complex g3 = (z3 - long double(50)) / (z3 + long double(50));
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
                SystemParameters::rAdmitanceImagCalculation(pointsX[pointsX.size() - 1], pointsY[pointsY.size() - 1]);
                long double r1 = SystemParameters::admitanceImagR;
                SystemParameters::rAdmitanceImagCalculation(lastPointX, lastPointY);
                long double r2 = SystemParameters::admitanceImagR;
                Point point;
                point.x = lastPointX;
                point.y = lastPointY;
                allPoints[index + dpIndex - 1] = make_tuple(point, true);
                Complex z = SystemParameters::zCalculation(lastPointX, lastPointY);
                Complex y2 = SystemParameters::yCalculation(lastPointX, lastPointY);
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
                map<chartMode, tuple<long double, long double>> chart;
                Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(lastPointX, lastPointY);
                Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(lastPointX, lastPointY);
                Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(lastPointX, lastPointY);
                Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(lastPointX, lastPointY);
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
                pointsX.append(lastPointX);
                pointsY.append(lastPointY);
                QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
                points[index] = make_tuple(point, r, t, Model);
                int row = ui->pointTable->rowCount();
                ui->pointTable->insertRow(row);
                ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(index + dpIndex)));
                SystemParameters::rImpedanceRealCalculation(lastPointX, lastPointY);
                SystemParameters::rImpedanceImagCalculation(lastPointX, lastPointY);
                QString temp2 = " + j";
                if (SystemParameters::impedanceImagR < 0)
                {
                    temp2 = " - j";
                }
                ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceRealR) + temp2 + QString::number((double)SystemParameters::impedanceImagR)));
                if (SystemParameters::impedanceRealR == 0)
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
                }
                else
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR))));
                }
                ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)frequency)));
                circuitElements->elementIndexes.append(allpointindex);
                index++;
                allpointindex++;
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

/// <summary>
/// Шлейф холостого хода.
/// </summary>
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

/// <summary>
/// Шлейф короткого замыкания.
/// </summary>
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

/// <summary>
/// Ввод с клавиатуры.
/// </summary>
void Smithtry1000::onKeyboard_buttonClicked()
{
    KeyboardDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        long double frequency = SystemParameters::frequency;
        long double x, y;
        long double Re = SystemParameters::Re;
        long double Im = SystemParameters::Im;
        if (SystemParameters::val == Cartesian)
        {
            if (SystemParameters::sys == Impedance)
            {
                Re /= 50;
                Im /= 50;
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
                Re /= 20;
                Im /= 20;
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
                Re /= 50;
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
                Re /= 20;
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
        QPoint temp = QPoint(x * scale + renderArea->rect().center().x(), y * scale + renderArea->rect().center().y());
        renderArea->setCursorPosOnCircle(temp);
        if (index == 0)
        {
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
            lastPointX = x;
            lastPointY = y;
            Point point = Point();
            point.x = x;
            point.y = y;
            circuitElements->firstPoint = point;
            allPoints[0] = make_tuple(point, false);
            points[index] = make_tuple(point, r, t, mode::AddPoint);
            SystemParameters::rImpedanceRealCalculation(x, y);
            long double r1 = SystemParameters::impedanceRealR;
            circuitElements->realFirstPoint = r1;
            SystemParameters::rImpedanceImagCalculation(x, y);
            long double r2 = SystemParameters::impedanceImagR;
            circuitElements->imagFirstPoint = r2;
            Complex z = SystemParameters::zCalculation(lastPointX, lastPointY);
            Complex y2 = SystemParameters::yCalculation(lastPointX, lastPointY);
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
            ui->pointTable->setItem(row, 0, new QTableWidgetItem("Yes"));
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("DP 1"));
            SystemParameters::rImpedanceRealCalculation(x, y);
            SystemParameters::rImpedanceImagCalculation(x, y);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceRealR) + temp2 + QString::number((double)SystemParameters::impedanceImagR)));
            if (SystemParameters::impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceImagR / (double)SystemParameters::impedanceRealR)));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)frequency)));
            index++;
            dpIndex++; 
            allpointindex++;
            renderArea->setCursorPosOnCircle(temp);
            auxiliaryWidget->update();
        }
        else
        {
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 0, new QTableWidgetItem("No"));
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("DP " + QString::number(dpIndex + index)));
            SystemParameters::rImpedanceRealCalculation(x, y);
            SystemParameters::rImpedanceImagCalculation(x, y);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceRealR) + temp2 + QString::number((double)SystemParameters::impedanceImagR)));
            if (SystemParameters::impedanceRealR == 0||abs(SystemParameters::impedanceRealR)<1e-5)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR))));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)frequencyList[frequencyList.size() - 1])));
            Point point;
            point.x = x;
            point.y = y;
            allPoints[index + dpIndex - 1] = make_tuple(point, false);
            circuitElements->pointIndexes.append(allpointindex);
            dpIndex++;
            allpointindex++;
            circuitElements->morePoints.append(point);
            renderArea->setCursorPosOnCircle(temp);
            auxiliaryWidget->update();
        }
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
    tmin = -M_PI;
    tmax = M_PI;
    trackingEnabled = !trackingEnabled;
    while (!leftClicked && !rightClicked)
    {
        QCoreApplication::processEvents();
    }
    if (leftClicked)
    {
        SystemParameters::rAdmitanceImagCalculation(pointsX[pointsX.size() - 1], pointsY[pointsY.size() - 1]);
        long double r1 = SystemParameters::admitanceImagR;
        SystemParameters::rAdmitanceImagCalculation(lastPointX, lastPointY);
        long double r2 = SystemParameters::admitanceImagR;
        Point point;
        point.x = lastPointX;
        point.y = lastPointY;
        allPoints[index + dpIndex - 1] = make_tuple(point, true);
        Complex z = SystemParameters::zCalculation(lastPointX, lastPointY);
        Complex y2 = SystemParameters::yCalculation(lastPointX, lastPointY);
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
        map<chartMode, tuple<long double, long double>> chart;
        Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(lastPointX, lastPointY);
        Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(lastPointX, lastPointY);
        Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(lastPointX, lastPointY);
        Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(lastPointX, lastPointY);
        chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
        chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
        chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
        chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
        switch (Model)
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
        pointsX.append(lastPointX);
        pointsY.append(lastPointY);
        QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
        points[index] = make_tuple(point, r, t, Model);
        int row = ui->pointTable->rowCount();
        ui->pointTable->insertRow(row);
        ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(index + dpIndex)));
        SystemParameters::rImpedanceRealCalculation(lastPointX, lastPointY);
        SystemParameters::rImpedanceImagCalculation(lastPointX, lastPointY);
        QString temp2 = " + j";
        if (SystemParameters::impedanceImagR < 0)
        {
            temp2 = " - j";
        }
        ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceRealR) + temp2 + QString::number((double)SystemParameters::impedanceImagR)));
        if (SystemParameters::impedanceRealR == 0)
        {
            ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
        }
        else
        {
            ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR))));
        }
        ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)frequency)));
        circuitElements->elementIndexes.append(allpointindex);
        index++;
        allpointindex++;
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
                    ui->pointTable->setItem(i, 2, new QTableWidgetItem(QString::number(number)
                        + temp2 + QString::number(number2)));
                    if (SystemParameters::impedanceRealR == 0)
                    {
                        ui->pointTable->setItem(i, 3, new QTableWidgetItem("0"));
                    }
                    else
                    {
                        double number3 = abs(SystemParameters::tunedElements[j]->GetParameter()[Z].imag() 
                            /SystemParameters::tunedElements[j]->GetParameter()[Z].real());
                        ui->pointTable->setItem(i, 3, new QTableWidgetItem(QString::number(number3)));
                    }
                }
                id++;
            }
        }
    }
    SystemParameters::tunedElements = {};
    tableChanged = false;
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

/// <summary>
/// Ввод с помощью мышки.
/// </summary>
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
            long double x = point.x();
            long double y = point.y();
            x = (x - centerGlobal.x()) / scale;
            y = (y - centerGlobal.y()) / scale;
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
                SystemParameters::rImpedanceRealCalculation(x, y);
                long double r1 = SystemParameters::impedanceRealR;
                circuitElements->realFirstPoint = r1;
                SystemParameters::rImpedanceImagCalculation(x, y);
                long double r2 = SystemParameters::impedanceImagR;
                circuitElements->imagFirstPoint = r2;
                Complex z = SystemParameters::zCalculation(lastPointX, lastPointY);
                Complex y2 = SystemParameters::yCalculation(lastPointX, lastPointY);
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
                ui->pointTable->setItem(row, 0, new QTableWidgetItem("Yes"));
                ui->pointTable->setItem(row, 1, new QTableWidgetItem("DP 1"));
                SystemParameters::rImpedanceRealCalculation(x, y);
                SystemParameters::rImpedanceImagCalculation(x, y);
                QString temp2 = " + j";
                if (SystemParameters::impedanceImagR < 0)
                {
                    temp2 = " - j";
                }
                ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceRealR) + temp2 + QString::number((double)SystemParameters::impedanceImagR)));
                if (SystemParameters::impedanceRealR == 0)
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
                }
                else
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceImagR / (double)SystemParameters::impedanceRealR)));
                }
                ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)frequency)));
                index++;
                dpIndex++;
                allpointindex++;
                renderArea->setCursorPosOnCircle(temp);
                auxiliaryWidget->update();
            }
            else
            {
                int row = ui->pointTable->rowCount();
                ui->pointTable->insertRow(row);
                ui->pointTable->setItem(row, 0, new QTableWidgetItem("No"));
                ui->pointTable->setItem(row, 1, new QTableWidgetItem("DP " + QString::number(dpIndex + index)));
                SystemParameters::rImpedanceRealCalculation(x, y);
                SystemParameters::rImpedanceImagCalculation(x, y);
                QString temp2 = " + j";
                if (SystemParameters::impedanceImagR < 0)
                {
                    temp2 = " - j";
                }
                ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceRealR) + temp2 + QString::number((double)SystemParameters::impedanceImagR)));
                if (SystemParameters::impedanceRealR == 0)
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
                }
                else
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR))));
                }
                ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)frequencyList[frequencyList.size() - 1])));
                Point point;
                point.x = x;
                point.y = y;
                allPoints[index + dpIndex - 1] = make_tuple(point, false);
                circuitElements->pointIndexes.append(allpointindex);
                dpIndex++;
                allpointindex++;
                circuitElements->morePoints.append(point);
                renderArea->setCursorPosOnCircle(temp);
            }
        }
        Model = Default;
    }
}

/// <summary>
/// Последовательная катушка индуктивности.
/// </summary>
void Smithtry1000::onInduction_buttonClicked()
{
    Model = mode::InductionShunt;
    ImaginaryImpedance();
}

/// <summary>
/// Последовательный конденсатор.
/// </summary>
void Smithtry1000::onCapacitor_buttonClicked()
{
    Model = mode::CapacitorShunt;
    ImaginaryImpedance();
}

/// <summary>
/// Последовательный резистор.
/// </summary>
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
            t = M_PI * 3 / 2;
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
                tmin = t;
                tmax = M_PI * 3 / 2;
            }
            else
            {
                r = fabs(r) * (-1);
                tmax = t;
                tmin = M_PI * 3 / 2;
            }
        }
        trackingEnabled = !trackingEnabled;
        while (!leftClicked && !rightClicked)
        {
            QCoreApplication::processEvents();
        }
        if (leftClicked)
        {
            SystemParameters::rImpedanceRealCalculation(pointsX[pointsX.size() - 1], pointsY[pointsY.size() - 1]);
            long double r1 = SystemParameters::impedanceRealR;
            SystemParameters::rImpedanceRealCalculation(lastPointX, lastPointY);
            long double r2 = SystemParameters::impedanceRealR;
            Point point;
            point.x = lastPointX;
            point.y = lastPointY;
            allPoints[index + dpIndex - 1] = make_tuple(point, true);
            Complex z = SystemParameters::zCalculation(lastPointX, lastPointY);
            Complex y2 = SystemParameters::yCalculation(lastPointX, lastPointY);
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
            map<chartMode, tuple<long double, long double>> chart;
            Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(lastPointX, lastPointY);
            Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(lastPointX, lastPointY);
            Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(lastPointX, lastPointY);
            Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(lastPointX, lastPointY);
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
            SystemParameters::rImpedanceRealCalculation(point.x, point.y);
            SystemParameters::rImpedanceImagCalculation(point.x, point.y);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number((double)round(SystemParameters::impedanceRealR*100)/100) + temp2 + QString::number((double)round(SystemParameters::impedanceImagR*100)/100)));
            if (SystemParameters::impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR))));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)frequency)));
            circuitElements->elementIndexes.append(allpointindex);
            index++;
            allpointindex++;
            renderArea->setCursorPosOnCircle(temp);
        }
        if (rightClicked)
        {
            QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
            renderArea->setCursorPosOnCircle(temp);
            auxiliaryWidget->removeLastSvg();
            auxiliaryWidget->update();
        }
        SystemParameters::resistorLinear = false;
        Model = Default;
        this->unsetCursor(); // возвращаем курсор
    }
}

/// <summary>
/// Параллельная катушка индуктивности.
/// </summary>
void Smithtry1000::onInductionParallel_buttonClicked()
{
    Model = mode::InductionParallel;
    ImaginaryAdmitance();
}

/// <summary>
/// Параллельный конденсатор.
/// </summary>
void Smithtry1000::onCapacitorParallel_buttonClicked()
{
    Model = mode::CapacitorParallel;
    ImaginaryAdmitance();
}

/// <summary>
/// Параллельный резистор.
/// </summary>
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
            t = M_PI * 3 / 2;
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
                tmin = t;
                tmax = M_PI / 2;
            }
            else
            {
                tmax = t;
                tmin = -M_PI / 2;
            }
        }
        trackingEnabled = !trackingEnabled;
        while (!leftClicked && !rightClicked)
        {
            QCoreApplication::processEvents();
        }
        if (leftClicked)
        {
            SystemParameters::rAdmitanceRealCalculation(pointsX[pointsX.size() - 1], pointsY[pointsY.size() - 1]);
            long double r1 = SystemParameters::admitanceRealR;
            SystemParameters::rAdmitanceRealCalculation(lastPointX, lastPointY);
            long double r2 = SystemParameters::admitanceRealR;
            Point point;
            point.x = lastPointX;
            point.y = lastPointY;
            allPoints[index + dpIndex - 1] = make_tuple(point, true);
            Complex z = SystemParameters::zCalculation(lastPointX, lastPointY);
            Complex y2 = SystemParameters::yCalculation(lastPointX, lastPointY);
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
            map<chartMode, tuple<long double, long double>> chart;
            Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(lastPointX, lastPointY);
            Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(lastPointX, lastPointY);
            Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(lastPointX, lastPointY);
            Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(lastPointX, lastPointY);
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
            SystemParameters::rImpedanceRealCalculation(point.x, point.y);
            SystemParameters::rImpedanceImagCalculation(point.x, point.y);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number((double)round(SystemParameters::impedanceRealR*100)/100) + temp2 + QString::number((double)round(SystemParameters::impedanceImagR*100)/100)));
            if (SystemParameters::impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR))));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)frequency)));
            circuitElements->elementIndexes.append(allpointindex);
            index++;
            allpointindex++;
            renderArea->setCursorPosOnCircle(temp);
        }
        if (rightClicked)
        {
            QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
            renderArea->setCursorPosOnCircle(temp);
            auxiliaryWidget->removeLastSvg();
            auxiliaryWidget->update();
        }
        SystemParameters::resistorLinear = false;
        Model = Default;
        this->unsetCursor(); // возвращаем курсор
    }
}

/// <summary>
/// Удаление элементов и точек с конца.
/// </summary>
void Smithtry1000::onDelete_buttonClicked()
{
    if (allpointindex > 0 && !SystemParameters::tuneBlock)
    {
        if (get<1>(allPoints[allpointindex-1]))
        {
            points.erase(index - 1);
            auxiliaryWidget->removeLastSvg();
            renderArea->update();
            auxiliaryWidget->update();
            this->circuitElements->DeleteCircuitElements();
            pointsX.pop_back();
            pointsY.pop_back();
            this->circuitElements->elementIndexes.pop_back();
            index--;
            allpointindex--;
        }
        else
        {
            if (allpointindex == 1)
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
                allpointindex--;
            }
            else
            {
                circuitElements->morePoints.pop_back();
                this->circuitElements->pointIndexes.pop_back();
                dpIndex--;
                allpointindex--;
            }
        }
        ui->pointTable->removeRow(ui->pointTable->rowCount() - 1);
        allPoints.erase(allPoints.size() - 1);
        renderArea->update();
        auxiliaryWidget->update();
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
            SystemParameters::rImpedanceImagCalculation(pointsX[pointsX.size() - 1], pointsY[pointsY.size() - 1]);
            long double r1 = SystemParameters::impedanceImagR;
            SystemParameters::rImpedanceImagCalculation(lastPointX, lastPointY);
            long double r2 = SystemParameters::impedanceImagR;
            Point point;
            point.x = lastPointX;
            point.y = lastPointY;
            allPoints[index + dpIndex - 1] = make_tuple(point, true);
            Complex z = SystemParameters::zCalculation(lastPointX, lastPointY);
            Complex y2 = SystemParameters::yCalculation(lastPointX, lastPointY);
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
            map<chartMode, tuple<long double, long double>> chart;
            Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(lastPointX, lastPointY);
            Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(lastPointX, lastPointY);
            Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(lastPointX, lastPointY);
            Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(lastPointX, lastPointY);
            chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
            chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
            chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
            chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
            switch (Model)
            {
            case InductionShunt:
            {
                this->circuitElements->AddCircuitElements(new Element(InductionShunt, (r2 - r1) / (2 * M_PI * frequency), this->circuitElements->frequencyFirstPoint, point, chart, parameter));
                break;
            }
            case CapacitorShunt:
            {
                this->circuitElements->AddCircuitElements(new Element(CapacitorShunt, 1 / ((r1 - r2) * (2 * M_PI * frequency)), this->circuitElements->frequencyFirstPoint, point, chart, parameter));
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
            SystemParameters::rImpedanceRealCalculation(lastPointX, lastPointY);
            SystemParameters::rImpedanceImagCalculation(lastPointX, lastPointY);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceRealR) + temp2 + QString::number((double)SystemParameters::impedanceImagR)));
            if (SystemParameters::impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR))));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)frequency)));
            circuitElements->elementIndexes.append(allpointindex);
            index++;
            allpointindex++;
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
            SystemParameters::rAdmitanceImagCalculation(pointsX[pointsX.size() - 1], pointsY[pointsY.size() - 1]);
            long double r1 = SystemParameters::admitanceImagR;
            SystemParameters::rAdmitanceImagCalculation(lastPointX, lastPointY);
            long double r2 = SystemParameters::admitanceImagR;
            Point point;
            point.x = lastPointX;
            point.y = lastPointY;
            allPoints[index + dpIndex - 1] = make_tuple(point, true);
            Complex z = SystemParameters::zCalculation(lastPointX, lastPointY);
            Complex y2 = SystemParameters::yCalculation(lastPointX, lastPointY);
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
            map<chartMode, tuple<long double, long double>> chart;
            Complex rRealImpedance = SystemParameters::impedanceRealChartParameters(lastPointX, lastPointY);
            Complex rImagImpedance = SystemParameters::impedanceImagChartParameters(lastPointX, lastPointY);
            Complex rRealAdmitance = SystemParameters::admitanceRealChartParameters(lastPointX, lastPointY);
            Complex rImagAdmitance = SystemParameters::admitanceImagChartParameters(lastPointX, lastPointY);
            chart[RealImpedance] = make_tuple(rRealImpedance.real(), rRealImpedance.imag());
            chart[RealAdmitance] = make_tuple(rRealAdmitance.real(), rRealAdmitance.imag());
            chart[ImagAdmitance] = make_tuple(rImagAdmitance.real(), rImagAdmitance.imag());
            chart[ImagImpedance] = make_tuple(rImagImpedance.real(), rImagImpedance.imag());
            switch (Model)
            {
            case InductionParallel:
            {
                this->circuitElements->AddCircuitElements(new Element(InductionParallel, M_PI / (r1 - r2) * 100 / frequency * 1e6 * 500 / 1e9, this->circuitElements->frequencyFirstPoint, point, chart, parameter));
                break;
            }
            case CapacitorParallel:
            {
                this->circuitElements->AddCircuitElements(new Element(CapacitorParallel, (r2 - r1) / M_PI * 500 / frequency * 1e6 / 1e12, this->circuitElements->frequencyFirstPoint, point, chart, parameter));
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
            SystemParameters::rImpedanceRealCalculation(lastPointX, lastPointY);
            SystemParameters::rImpedanceImagCalculation(lastPointX, lastPointY);
            QString temp2 = " + j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp2 = " - j";
            }
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceRealR) + temp2 + QString::number((double)SystemParameters::impedanceImagR)));
            if (SystemParameters::impedanceRealR == 0)
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
            }
            else
            {
                ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number((double)abs(SystemParameters::impedanceImagR / SystemParameters::impedanceRealR))));
            }
            ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number((double)frequency)));
            circuitElements->elementIndexes.append(allpointindex);
            index++;
            allpointindex++;
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

/// <summary>
/// Событие происходящее по истечении каждых 10 мс.
/// </summary>
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
        long double x = temp.x();
        long double y = temp.y();
        x = (x - centerGlobal.x()) / scale;
        y = (y - centerGlobal.y()) / scale;
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
            ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceRealR) + temp + QString::number((double)SystemParameters::impedanceImagR)));
            if (SystemParameters::admitanceImagR < 0)
            {
                temp = "-j";
            }
            else
            {
                temp = "+j";
            }
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number((double)SystemParameters::admitanceRealR) + temp + QString::number((double)SystemParameters::admitanceImagR)));
            if (x >= 0)
            {
                ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number((double)atan(y / x) * 180 / M_PI * -1)));
            }
            else if (y <= 0)
            {
                ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number(180 - (double)atan(y / x) * 180 / M_PI)));
            }
            else
            {
                ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number(-180 - (double)atan(y / x) * 180 / M_PI)));
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
        if (Model == Transform)
        {
            if (pow(posOnCircle.x() - centerLocal.x(), 2) + pow(posOnCircle.y() - centerLocal.y(), 2) > pow(scale, 2))
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

/// <summary>
/// Определение положения эмуляции курсора на диаграмме.
/// </summary>
/// <param name="dx">Перемещение по x.</param>
/// <param name="dy">Перемещение по y.</param>
/// <returns>Точка на диаграмме.</returns>
QPoint Smithtry1000::getPointOnCircle(int dx, int dy)
{
    if (Model == mode::InductionShunt || Model == mode::CapacitorShunt)
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
        lastPointX = x;
        lastPointY = y;
        SystemParameters::rImpedanceRealCalculation(x, y);
        SystemParameters::rAdmitanceRealCalculation(x, y);
        SystemParameters::rImpedanceImagCalculation(x, y);
        SystemParameters::rAdmitanceImagCalculation(x, y);
        QString temp = "+j";
        if (SystemParameters::impedanceImagR < 0)
        {
            temp = "-j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceRealR) + temp + QString::number((double)SystemParameters::impedanceImagR)));
        if (SystemParameters::admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number((double)SystemParameters::admitanceRealR) + temp + QString::number((double)SystemParameters::admitanceImagR)));
        if (x >= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number((double)atan(y / x) * 180 / M_PI * -1)));
        }
        else if (y <= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number(180 - (double)atan(y / x) * 180 / M_PI)));
        }
        else
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number(-180 - (double)atan(y / x) * 180 / M_PI)));
        }
        x = x * scale + renderArea->rect().center().x();
        y = y * scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (Model == mode::InductionParallel || Model == mode::CapacitorParallel)
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
        }
        else if (t <= tmin)
        {
            t = tmin;
            step = 0.01;
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
        lastPointX = x;
        lastPointY = y;
        SystemParameters::rImpedanceRealCalculation(x, y);
        SystemParameters::rAdmitanceRealCalculation(x, y);
        SystemParameters::rImpedanceImagCalculation(x, y);
        SystemParameters::rAdmitanceImagCalculation(x, y);
        QString temp = "+j";
        if (SystemParameters::impedanceImagR < 0)
        {
            temp = "-j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceRealR) + temp + QString::number((double)SystemParameters::impedanceImagR)));
        if (SystemParameters::admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number((double)SystemParameters::admitanceRealR) + temp + QString::number((double)SystemParameters::admitanceImagR)));
        if (x >= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number((double)atan(y / x) * 180 / M_PI * -1)));
        }
        else if (y <= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number(180 - (double)atan(y / x) * 180 / M_PI)));
        }
        else
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number(-180 - (double)atan(y / x) * 180 / M_PI)));
        }
        x = x * scale + renderArea->rect().center().x();
        y = y * scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (Model == mode::ResistorShunt)
    {
        long double x, y;
        if (SystemParameters::resistorLinear)
        {
            step = abs(r) / 1000;
            step += step * abs(dx);
            if (dx > 0 && lastPointX < 1)
            {
                if (lastPointX + step > 1)
                {
                    lastPointX = 1-step;
                }
                else
                {
                    x = lastPointX + step;
                }
            }
            else if (dx<0 && lastPointX>-1)
            {
                if (lastPointX - step < -1)
                {
                    lastPointX = -1+step;
                }
                else
                {
                    x = lastPointX - step;
                }
            }
            y = 0;
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
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceRealR) + temp + QString::number((double)SystemParameters::impedanceImagR)));
        if (SystemParameters::admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number((double)SystemParameters::admitanceRealR) + temp + QString::number((double)SystemParameters::admitanceImagR)));
        if (x >= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number((double)atan(y / x) * 180 / M_PI * -1)));
        }
        else if (y <= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number(180 - (double)atan(y / x) * 180 / M_PI)));
        }
        else
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number(-180 - (double)atan(y / x) * 180 / M_PI)));
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
        long double x, y;
        if (SystemParameters::resistorLinear)
        {
            step = abs(r) / 1000;
            step += step * abs(dx);
            if (dx > 0 && lastPointX < 1)
            {
                if (lastPointX + step > 1)
                {
                    lastPointX = 1 - step;
                }
                else
                {
                    x = lastPointX + step;
                }
            }
            else if (dx<0 && lastPointX>-1)
            {
                if (lastPointX - step < -1)
                {
                    lastPointX = -1 + step;
                }
                else
                {
                    x = lastPointX - step;
                }
            }
            y = 0;
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
            long double cos_t = cos(t);
            long double sin_t = sin(t);
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
            if (y >= 0 && y < 0.0001)
            {
                y = 0.0001;
            }
            else if (y <= 0 && y > -0.0001)
            {
                y = -0.0001;
            }
        }
        lastPointX = x;
        lastPointY = y;
        SystemParameters::rImpedanceRealCalculation(x, y);
        SystemParameters::rAdmitanceRealCalculation(x, y);
        SystemParameters::rImpedanceImagCalculation(x, y);
        SystemParameters::rAdmitanceImagCalculation(x, y);
        QString temp = "+j";
        if (SystemParameters::impedanceImagR < 0)
        {
            temp = "-j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceRealR) + temp + QString::number((double)SystemParameters::impedanceImagR)));
        if (SystemParameters::admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number((double)SystemParameters::admitanceRealR) + temp + QString::number((double)SystemParameters::admitanceImagR)));
        if (x >= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number((double)atan(y / x) * 180 / M_PI * -1)));
        }
        else if (y <= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number(180 - (double)atan(y / x) * 180 / M_PI)));
        }
        else
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number(-180 - (double)atan(y / x) * 180 / M_PI)));
        }
        x = x * scale + renderArea->rect().center().x();
        y = y * scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (Model == mode::OSLine)
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
        lastPointX = x;
        lastPointY = y;
        SystemParameters::rImpedanceRealCalculation(x, y);
        SystemParameters::rAdmitanceRealCalculation(x, y);
        SystemParameters::rImpedanceImagCalculation(x, y);
        SystemParameters::rAdmitanceImagCalculation(x, y);
        QString temp = "+j";
        if (SystemParameters::impedanceImagR < 0)
        {
            temp = "-j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceRealR) + temp + QString::number((double)SystemParameters::impedanceImagR)));
        if (SystemParameters::admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number((double)SystemParameters::admitanceRealR) + temp + QString::number((double)SystemParameters::admitanceImagR)));
        if (x >= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number((double)atan(y / x) * 180 / M_PI * -1)));
        }
        else if (y <= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number(180 - (double)atan(y / x) * 180 / M_PI)));
        }
        else
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number(-180 - (double)atan(y / x) * 180 / M_PI)));
        }
        x = x * scale + renderArea->rect().center().x();
        y = y * scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (Model == mode::SSLine)
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
        lastPointX = x;
        lastPointY = y;
        SystemParameters::rImpedanceRealCalculation(x, y);
        SystemParameters::rAdmitanceRealCalculation(x, y);
        SystemParameters::rImpedanceImagCalculation(x, y);
        SystemParameters::rAdmitanceImagCalculation(x, y);
        QString temp = "+j";
        if (SystemParameters::impedanceImagR < 0)
        {
            temp = "-j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceRealR) + temp + QString::number((double)SystemParameters::impedanceImagR)));
        if (SystemParameters::admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number((double)SystemParameters::admitanceRealR) + temp + QString::number((double)SystemParameters::admitanceImagR)));
        if (x >= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number((double)atan(y / x) * 180 / M_PI * -1)));
        }
        else if (y <= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number(180 - (double)atan(y / x) * 180 / M_PI)));
        }
        else
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number(-180 - (double)atan(y / x) * 180 / M_PI)));
        }
        x = x * scale + renderArea->rect().center().x();
        y = y * scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (Model == Line)
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
        Complex g1 = (zl - long double(50)) / (zl + long double(50));
        Complex z3 = SystemParameters::z0line * (zl + Complex(0, SystemParameters::z0line)) / (SystemParameters::z0line + Complex(0, 1) * zl);
        Complex g3 = (z3 - long double(50)) / (z3 + long double(50));
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
        lastPointX = x;
        lastPointY = y;
        SystemParameters::rImpedanceRealCalculation(x, y);
        SystemParameters::rAdmitanceRealCalculation(x, y);
        SystemParameters::rImpedanceImagCalculation(x, y);
        SystemParameters::rAdmitanceImagCalculation(x, y);
        QString temp = "+j";
        if (SystemParameters::impedanceImagR < 0)
        {
            temp = "-j";
        }
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceRealR) + temp + QString::number((double)SystemParameters::impedanceImagR)));
        if (SystemParameters::admitanceImagR < 0)
        {
            temp = "-j";
        }
        else
        {
            temp = "+j";
        }
        ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number((double)SystemParameters::admitanceRealR) + temp + QString::number((double)SystemParameters::admitanceImagR)));
        if (x >= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number((double)atan(y / x) * 180 / M_PI * -1)));
        }
        else if (y <= 0)
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number(180 - (double)atan(y / x) * 180 / M_PI)));
        }
        else
        {
            ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number(-180 - (double)atan(y / x) * 180 / M_PI)));
        }
        x = x * scale + renderArea->rect().center().x();
        y = y * scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (Model == Transform)
    {
        long double tprev = t;
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
        long double q = zl.imag() / zl.real();
        long double ycenter = -1 / q;
        long double R = sqrt(1 + 1 / pow(q, 2));
        x = cos_t * R;
        if (abs(x) >= 1)
        {
            t = tprev;
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
            lastPointX = x;
            lastPointY = y;
            SystemParameters::rImpedanceRealCalculation(x, y);
            SystemParameters::rAdmitanceRealCalculation(x, y);
            SystemParameters::rImpedanceImagCalculation(x, y);
            SystemParameters::rAdmitanceImagCalculation(x, y);
            QString temp = "+j";
            if (SystemParameters::impedanceImagR < 0)
            {
                temp = "-j";
            }
            ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number((double)SystemParameters::impedanceRealR) + temp + QString::number((double)SystemParameters::impedanceImagR)));
            if (SystemParameters::admitanceImagR < 0)
            {
                temp = "-j";
            }
            else
            {
                temp = "+j";
            }
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number((double)SystemParameters::admitanceRealR) + temp + QString::number((double)SystemParameters::admitanceImagR)));
            if (x >= 0)
            {
                ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number((double)atan(y / x) * 180 / M_PI * -1)));
            }
            else if (y <= 0)
            {
                ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number(180 - (double)atan(y / x) * 180 / M_PI)));
            }
            else
            {
                ui->rTable->setItem(3, 1, new QTableWidgetItem(QString::number((double)pow(x, 2) + (double)pow(y, 2)) + " / " + QString::number(-180 - (double)atan(y / x) * 180 / M_PI)));
            }
            x = x * scale + renderArea->rect().center().x();
            y = y * scale + renderArea->rect().center().y();

            auxiliaryWidget->update();
            return QPoint(x, y);
        }
    }
}

/// <summary>
/// Масштабирование - приближение.
/// </summary>
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

/// <summary>
/// Масштабирование - отдаление.
/// </summary>
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

/// <summary>
/// Масштабирование - стандартное значение
/// </summary>
void Smithtry1000::onDefaultSize_buttonClicked()
{
    scale = 200;
    renderArea->update();
    renderArea->setFixedWidth(1200);
    renderArea->setFixedHeight(800);
}

/// <summary>
/// Вызов амплитудно-частотной характеристики для цепи.
/// </summary>
void Smithtry1000::onGraph_buttonClicked()
{
    if (pointsX.size() > 1)
    {
        amplitudeFrequence->MatrixCalculation();

        amplitudeFrequence->show();
        amplitudeFrequence->activateWindow();
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
    if (pointsX.size() > 1)
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
        scale = scale * coef;
        int n = ui->scrollAreaDiagram->horizontalScrollBar()->value();
        int m = ui->scrollAreaDiagram->verticalScrollBar()->value();
        renderArea->setFixedWidth(1200 + (scale - 200) * 2);
        renderArea->setFixedHeight(800 + (scale - 200) * 2);
        ui->scrollAreaDiagram->horizontalScrollBar()->setValue(n * (scale / (scale - 100)));
        ui->scrollAreaDiagram->verticalScrollBar()->setValue(m * (scale / (scale - 100)));
    }
}