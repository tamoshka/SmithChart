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
    this->setMaximumSize(1920, 1080);
    ui->pointTable->setColumnCount(5);
    ui->pointTable->setRowCount(1);
    ui->pointTable->setColumnWidth(0, 40);
    ui->pointTable->setColumnWidth(1, 35);
    ui->pointTable->setColumnWidth(2, 120);
    ui->pointTable->setColumnWidth(3, 70);
    ui->pointTable->setColumnWidth(4, 65);
    ui->pointTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->pointTable->setItem(0, 0, new QTableWidgetItem("Start"));
    ui->pointTable->setItem(0, 1, new QTableWidgetItem("ID"));
    ui->pointTable->setItem(0, 2, new QTableWidgetItem("Z"));
    ui->pointTable->setItem(0, 3, new QTableWidgetItem("Q"));
    ui->pointTable->setItem(0, 4, new QTableWidgetItem("Frequency"));
    ui->rTable->setRowCount(3);
    ui->rTable->setColumnCount(3);
    ui->rTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->rTable->setItem(0, 1, new QTableWidgetItem("Real"));
    ui->rTable->setItem(0, 2, new QTableWidgetItem("Imag"));
    ui->rTable->setItem(1, 0, new QTableWidgetItem("Z"));
    ui->rTable->setItem(2, 0, new QTableWidgetItem("Y"));
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
    connect(ui->S11Button, &QPushButton::clicked, this, &Smithtry1000::onS11_buttonClicked);
    connect(ui->S22Button, &QPushButton::clicked, this, &Smithtry1000::onS22_buttonClicked);
    connect(ui->ExportNetlist, &QPushButton::clicked, this, &Smithtry1000::onExportNetlist_buttonClicked);
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

Smithtry1000::~Smithtry1000()
{
    delete ui;
    delete this->circuitElements;
}

void Smithtry1000::onExportNetlist_buttonClicked()
{
    ExportNetlist exporter = ExportNetlist(nullptr, circuitElements);
    QString netlist = exporter.generateNetlist();

    QString fileName = QFileDialog::getSaveFileName(this,
        "Save SPICE Netlist",
        "",
        "SPICE Files (*.CKT);;All Files (*)"
    );

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            stream << netlist;
            file.close();
            QMessageBox::information(this, "Success", "SPICE netlist exported!");
        }
        else {
            QMessageBox::warning(this, "Error", "Cannot write file");
        }
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
            float x = point.x();
            float y = point.y();
            x = (x - centerGlobal.x()) / scale;
            y = (y - centerGlobal.y()) / scale;
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
                Point point = Point();
                point.x = x;
                point.y = y;
                circuitElements->firstPoint = point;
                points[index] = make_tuple(point, r, t, mode::AddPoint);
                rImpedanceRealCalculation(x, y);
                float r1 = impedanceRealR;
                circuitElements->realFirstPoint = r1;
                rImpedanceImagCalculation(x, y);
                float r2 = impedanceImagR;
                circuitElements->imagFirstPoint = r2;
                circuitElements->frequencyFirstPoint = frequency;
                map<chartMode, tuple<float, float>> chart;
                complexNumber rRealImpedance = impedanceRealChartParameters(point.x, point.y);
                complexNumber rImagImpedance = impedanceImagChartParameters(point.x, point.y);
                complexNumber rRealAdmitance = admitanceRealChartParameters(point.x, point.y);
                complexNumber rImagAdmitance = admitanceImagChartParameters(point.x, point.y);
                chart[RealImpedance] = make_tuple(rRealImpedance.Re(), rRealImpedance.Im());
                chart[RealAdmitance] = make_tuple(rRealAdmitance.Re(), rRealAdmitance.Im());
                chart[ImagAdmitance] = make_tuple(rImagAdmitance.Re(), rImagAdmitance.Im());
                chart[ImagImpedance] = make_tuple(rImagImpedance.Re(), rImagImpedance.Im());
                circuitElements->chart = chart;
                int row = ui->pointTable->rowCount();
                ui->pointTable->insertRow(row);
                ui->pointTable->setItem(row, 0, new QTableWidgetItem("Yes"));
                ui->pointTable->setItem(row, 1, new QTableWidgetItem("DP 1"));
                ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(impedanceRealR) + " + j" + QString::number(impedanceImagR)));
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
                ui->pointTable->setItem(row, 1, new QTableWidgetItem("DP " + QString::number(dpIndex + 1)));
                rImpedanceRealCalculation(x, y);
                rImpedanceImagCalculation(x, y);
                ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(impedanceRealR) + " + j" + QString::number(impedanceImagR)));
                if (impedanceRealR == 0)
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem("0"));
                }
                else
                {
                    ui->pointTable->setItem(row, 3, new QTableWidgetItem(QString::number(abs(impedanceImagR / impedanceRealR))));
                }
                ui->pointTable->setItem(row, 4, new QTableWidgetItem(QString::number(frequencyList[frequencyList.size() - 1])));
                dpIndex++;
                Point point;
                point.x = x;
                point.y = y;
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
        float x = pointsX.back();
        float y = pointsY.back();
        double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
        double xCenter = 1 - circleRadius;
        double dx = x - xCenter;
        double dy = y;
        sin_t = dy;
        cos_t = dx;
        if (y < 1e-6 && y>0)
        {
            if (y == 0 && x > 0.99)
            {
                t = 0.0001;
            }
            else if (x > 0.99)
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
            t = atan(cos_t / sin_t);
            if (y < 0)
            {
                t += M_PI;
            }
            else
            {
                t += 2 * M_PI;
            }
        }
        if (x - 1 != 0)
        {
            r = cos(t)/ (x - 1);
        }
        else
        {
            r = (1 + sin(t)) / y;
        }
        if (y < 0)
        {
            r = abs(r);
            tmin = t;
            tmax = M_PI*3/2;
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
            rImpedanceRealCalculation(pointsX[pointsX.size()-1], pointsY[pointsY.size() - 1]);
            float r1 = impedanceRealR;
            rImpedanceRealCalculation(lastPointX, lastPointY);
            float r2 = impedanceRealR;
            Point point;
            point.x = lastPointX;
            point.y = lastPointY;
            complexNumber z = zCalculation(lastPointX, lastPointY);
            complexNumber y2 = yCalculation(lastPointX, lastPointY);
            map<parameterMode, complexNumber> parameter;
            parameter[Z] = z;
            parameter[Y] = y2;
            map<chartMode, tuple<float, float>> chart;
            complexNumber rRealImpedance = impedanceRealChartParameters(lastPointX, lastPointY);
            complexNumber rImagImpedance = impedanceImagChartParameters(lastPointX, lastPointY);
            complexNumber rRealAdmitance = admitanceRealChartParameters(lastPointX, lastPointY);
            complexNumber rImagAdmitance = admitanceImagChartParameters(lastPointX, lastPointY);
            chart[RealImpedance] = make_tuple(rRealImpedance.Re(), rRealImpedance.Im());
            chart[RealAdmitance] = make_tuple(rRealAdmitance.Re(), rRealAdmitance.Im());
            chart[ImagAdmitance] = make_tuple(rImagAdmitance.Re(), rImagAdmitance.Im());
            chart[ImagImpedance] = make_tuple(rImagImpedance.Re(), rImagImpedance.Im());
            this->circuitElements->AddCircuitElements(new Element(ResistorShunt, r2 - r1, this->circuitElements->frequencyFirstPoint, point, chart, parameter));
            pointsX.append(lastPointX);
            pointsY.append(lastPointY);
            QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
            points[index] = make_tuple(point, r, t, mode::ResistorShunt);
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(index)));
            rImpedanceRealCalculation(point.x, point.y);
            rImpedanceImagCalculation(point.x, point.y);
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(impedanceRealR) + " + j" + QString::number(impedanceImagR)));
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
        float x = pointsX.back();
        float y = pointsY.back();
        double circleRadius = (pow(x,2)+2*x+1+pow(y,2))/(-2*y);
        double yCenter = -circleRadius;
        double dx = x+1;
        double dy = y - yCenter;
        sin_t = -dy;
        cos_t = dx;
        if (y < 1e-6 && y>=0)
        {
            if (y == 0 && x < -0.99)
            {
                t = 0;
            }
            else if (x < -0.99)
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
            t = atan(sin_t/ cos_t);
        }
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
            tmax = M_PI/2;
        }
        else
        {
            tmax = t;
            tmin = -M_PI/2;
        }
        trackingEnabled = !trackingEnabled;
        while (!leftClicked && !rightClicked)
        {
            QCoreApplication::processEvents();
        }
        if (leftClicked)
        {
            rAdmitanceRealCalculation(pointsX[pointsX.size() - 1], pointsY[pointsY.size() - 1]);
            float r1 = admitanceRealR;
            rAdmitanceRealCalculation(lastPointX, lastPointY);
            float r2 = admitanceRealR;
            Point point;
            point.x = lastPointX;
            point.y = lastPointY;
            complexNumber z = zCalculation(lastPointX, lastPointY);
            complexNumber y2 = yCalculation(lastPointX, lastPointY);
            map<parameterMode, complexNumber> parameter;
            parameter[Z] = z;
            parameter[Y] = y2;
            map<chartMode, tuple<float, float>> chart;
            complexNumber rRealImpedance = impedanceRealChartParameters(lastPointX, lastPointY);
            complexNumber rImagImpedance = impedanceImagChartParameters(lastPointX, lastPointY);
            complexNumber rRealAdmitance = admitanceRealChartParameters(lastPointX, lastPointY);
            complexNumber rImagAdmitance = admitanceImagChartParameters(lastPointX, lastPointY);
            chart[RealImpedance] = make_tuple(rRealImpedance.Re(), rRealImpedance.Im());
            chart[RealAdmitance] = make_tuple(rRealAdmitance.Re(), rRealAdmitance.Im());
            chart[ImagAdmitance] = make_tuple(rImagAdmitance.Re(), rImagAdmitance.Im());
            chart[ImagImpedance] = make_tuple(rImagImpedance.Re(), rImagImpedance.Im());
            this->circuitElements->AddCircuitElements(new Element(ResistorParallel, 1000 / (r2 - r1), this->circuitElements->frequencyFirstPoint, point, chart, parameter));
            pointsX.append(lastPointX);
            pointsY.append(lastPointY);
            QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
            points[index] = make_tuple(point, r, t, mode::ResistorParallel);
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(index)));
            rImpedanceRealCalculation(point.x, point.y);
            rImpedanceImagCalculation(point.x, point.y);
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(impedanceRealR) + " + j" + QString::number(impedanceImagR)));
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
    if ((index > 0 && dpIndex==1)||index>1)
    {
        points.erase(index-1);
        index--;
        pointsX.pop_back();
        pointsY.pop_back();
        auxiliaryWidget->removeLastSvg();
        ui->pointTable->removeRow(ui->pointTable->rowCount()-1);
        for (int row = 0; row < ui->pointTable->rowCount(); ++row) {
            bool found = false; 

            int col = 1;
            QTableWidgetItem* item = ui->pointTable->item(row, col);
            if (item && item->text() == "TP " + QString::number(index)) {
                found = true;
                ui->pointTable->removeRow(row);
                break;
            }
            if (found) {
                break;  // Можно удалить только первую найденную строку, если нужно
            }
        }
        renderArea->update();
        auxiliaryWidget->update();
        if (index > 0)
        {
            this->circuitElements->DeleteCircuitElements();
        }
        else if (index == 0)
        {
            dpIndex--;
            this->circuitElements->imagFirstPoint = -9999;
            this->circuitElements->realFirstPoint = -9999;
            this->circuitElements->frequencyFirstPoint = -9999;
            this->circuitElements->firstPoint = Point();
        }
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
            auxiliaryWidget->addSvg(QString(":/Images/horizontal_i_circuit.svg"), (index + 2) * 40, 20);
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
        float x = pointsX.back();
        float y = pointsY.back();
        double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
        double xCenter = 1 - circleRadius;
        double dx = x - xCenter;
        double dy = y;
        double sin_t = dy;
        double cos_t = dx;
        if (y < 1e-6 && y >= 0)
        {
            if (y == 0 && x >0.999)
            {
                t = 0;
            }
            else if (x > 0.999)
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
            tmin = 0.000001;
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
            float r1 = impedanceImagR;
            rImpedanceImagCalculation(lastPointX, lastPointY);
            float r2 = impedanceImagR;
            Point point;
            point.x = lastPointX;
            point.y = lastPointY;
            complexNumber z = zCalculation(lastPointX, lastPointY);
            complexNumber y2 = yCalculation(lastPointX, lastPointY);
            map<parameterMode, complexNumber> parameter;
            parameter[Z] = z;
            parameter[Y] = y2;
            map<chartMode, tuple<float, float>> chart;
            complexNumber rRealImpedance = impedanceRealChartParameters(lastPointX, lastPointY);
            complexNumber rImagImpedance = impedanceImagChartParameters(lastPointX, lastPointY);
            complexNumber rRealAdmitance = admitanceRealChartParameters(lastPointX, lastPointY);
            complexNumber rImagAdmitance = admitanceImagChartParameters(lastPointX, lastPointY);
            chart[RealImpedance] = make_tuple(rRealImpedance.Re(), rRealImpedance.Im());
            chart[RealAdmitance] = make_tuple(rRealAdmitance.Re(), rRealAdmitance.Im());
            chart[ImagAdmitance] = make_tuple(rImagAdmitance.Re(), rImagAdmitance.Im());
            chart[ImagImpedance] = make_tuple(rImagImpedance.Re(), rImagImpedance.Im());
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
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(index)));
            rImpedanceRealCalculation(x, y);
            rImpedanceImagCalculation(x, y);
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(impedanceRealR) + " + j" + QString::number(impedanceImagR)));
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
        float x = pointsX.back();
        float y = pointsY.back();
        double circleRadius = -1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 + 2 * x));
        double xCenter = -1 - circleRadius;
        double dx = x - xCenter;
        double dy = y;
        dy *= -1;
        double sin_t = dy;
        double cos_t = dx;
        if (y < 1e-6 && y >= 0)
        {
            if (y == 0 && x < -0.999)
            {
                t = -M_PI;
            }
            else if (x < -0.999)
            {
                t = M_PI;
            }
            else
            {
                t = 0;
            }
        }
        else
        {
            t = atan(sin_t / cos_t);
            if (cos_t < 0 && sin_t < 0)
            {
                t = abs(t) - M_PI;
            }
            else if (sin_t > 0 && cos_t < 0)
            {
                t = M_PI - abs(t);
            }
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
            float r1 = admitanceImagR;
            rAdmitanceImagCalculation(lastPointX, lastPointY);
            float r2 = admitanceImagR;
            Point point;
            point.x = lastPointX;
            point.y = lastPointY;
            complexNumber z = zCalculation(lastPointX, lastPointY);
            complexNumber y2 = yCalculation(lastPointX, lastPointY);
            map<parameterMode, complexNumber> parameter;
            parameter[Z] = z;
            parameter[Y] = y2;
            map<chartMode, tuple<float, float>> chart;
            complexNumber rRealImpedance = impedanceRealChartParameters(lastPointX, lastPointY);
            complexNumber rImagImpedance = impedanceImagChartParameters(lastPointX, lastPointY);
            complexNumber rRealAdmitance = admitanceRealChartParameters(lastPointX, lastPointY);
            complexNumber rImagAdmitance = admitanceImagChartParameters(lastPointX, lastPointY);
            chart[RealImpedance] = make_tuple(rRealImpedance.Re(), rRealImpedance.Im());
            chart[RealAdmitance] = make_tuple(rRealAdmitance.Re(), rRealAdmitance.Im());
            chart[ImagAdmitance] = make_tuple(rImagAdmitance.Re(), rImagAdmitance.Im());
            chart[ImagImpedance] = make_tuple(rImagImpedance.Re(), rImagImpedance.Im());
            switch (Model)
            {
            case InductionParallel:
            {
                this->circuitElements->AddCircuitElements(new Element(InductionParallel, M_PI / (r1 - r2) * 100 / frequency * 500/1e9, this->circuitElements->frequencyFirstPoint, point, chart, parameter));
                break;
            }
            case CapacitorParallel:
            {
                this->circuitElements->AddCircuitElements(new Element(CapacitorParallel, (r2 - r1) / M_PI * 500 / frequency/1e12, this->circuitElements->frequencyFirstPoint, point, chart, parameter));
                break;
            }
            }
            pointsX.append(lastPointX);
            pointsY.append(lastPointY);
            QPoint temp = QPoint(pointsX.back() * scale + renderArea->rect().center().x(), pointsY.back() * scale + renderArea->rect().center().y());
            points[index] = make_tuple(point, r, t, Model);
            int row = ui->pointTable->rowCount();
            ui->pointTable->insertRow(row);
            ui->pointTable->setItem(row, 1, new QTableWidgetItem("TP " + QString::number(index)));
            rImpedanceRealCalculation(x, y);
            rImpedanceImagCalculation(x, y);
            ui->pointTable->setItem(row, 2, new QTableWidgetItem(QString::number(impedanceRealR) + " + j" + QString::number(impedanceImagR)));
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

void Smithtry1000::rImpedanceRealCalculation(float x, float y)
{
    double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
    double xCenter = 1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    double sin_t = dy;
    double cos_t = dx;
    float t1;
    if (y < 1e-6 && y >= 0)
    {
        if (y == 0 && x > 0.99)
        {
            t1 = 0;
        }
        else if (x > 0.99)
        {
            t1 = 2 * M_PI;
        }
        else
        {
            t1 = M_PI;
        }
    }
    else
    {
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
    }
    if (x - 1 != 0)
    {
        impedanceRealR = (cos(t1) - x) / (x - 1);
    }
    impedanceRealR *= 50;
}

void Smithtry1000::rAdmitanceRealCalculation(float x, float y)
{
    double circleRadius = -1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 + 2 * x));
    double xCenter = -1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    dy *= -1;
    double sin_t = dy;
    double cos_t = dx;
    float t1;
    if (y < 1e-6 && y >= 0)
    {
        if (y == 0 && x < -0.99)
        {
            t1 = 0;
        }
        else if (x < -0.99)
        {
            t1 = 2 * M_PI;
        }
        else
        {
            t1 = M_PI;
        }
    }
    else
    {
        t1 = atan(sin_t / cos_t);
        if (cos_t < 0 && sin_t < 0)
        {
            t1 = abs(t1) - M_PI;
        }
        else if (sin_t > 0 && cos_t < 0)
        {
            t1 = M_PI - abs(t1);
        }
    }
    if (x - 1 != 0)
    {
        admitanceRealR = (cos(t1) - x) / (x + 1);
    }
    admitanceRealR *= 20;
}

void Smithtry1000::rImpedanceImagCalculation(float x, float y)
{
    double cos_t;
    double sin_t;
    double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
    double xCenter = 1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    sin_t = dy;
    cos_t = dx;
    float t1;
    if (abs(y) < 1e-6 && abs(y) >= 0)
    {
        if (y == 0 && x > 0.99)
        {
            t1 = 0.0001;
        }
        else if (x > 0.99)
        {
            t1 = 2 * M_PI;
        }
        else
        {
            t1= M_PI;
        }
    }
    else
    {
        t1 = atan(cos_t / sin_t);
        if (y < 0)
        {
            t1 += M_PI;
        }
        else
        {
            t1 += 2 * M_PI;
        }
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

void Smithtry1000::rAdmitanceImagCalculation(float x, float y)
{
    double cos_t;
    double sin_t;
    double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y, 2)) / (-2 * y);
    double yCenter = -circleRadius;
    double dx = x + 1;
    double dy = y - yCenter;
    sin_t = -dy;
    cos_t = dx;
    float t1;
    if (abs(y) < 1e-6 && abs(y)>=0)
    {
        if (y == 0 && x < -0.99)
        {
            t1 = M_PI / 2;
        }
        else if (x < -0.99)
        {
            t1 = -M_PI/2;
        }
        else
        {
            t1 = 0;
        }
    }
    else
    {
        t1 = atan(sin_t / cos_t);
    }
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
    if (Model == AddPoint || Model==Default)
    {
        QPoint temp = QCursor::pos();
        float x = temp.x();
        float y = temp.y();
        x = (x - centerGlobal.x()) / scale;
        y = (y - centerGlobal.y()) / scale;
        if (pow(x, 2) + pow(y, 2) <= 1)
        {
            rImpedanceRealCalculation(x, y);
            rAdmitanceRealCalculation(x, y);
            rImpedanceImagCalculation(x, y);
            rAdmitanceImagCalculation(x, y);
            ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number(impedanceRealR)));
            ui->rTable->setItem(1, 2, new QTableWidgetItem(QString::number(impedanceImagR)));
            ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(admitanceRealR)));
            ui->rTable->setItem(2, 2, new QTableWidgetItem(QString::number(admitanceImagR)));
        }
        else
        {
            ui->rTable->setItem(1, 1, new QTableWidgetItem(""));
            ui->rTable->setItem(1, 2, new QTableWidgetItem(""));
            ui->rTable->setItem(2, 1, new QTableWidgetItem(""));
            ui->rTable->setItem(2, 2, new QTableWidgetItem(""));
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
        float x, y;
        int dxABS = abs(dx);
        int dyABS = abs(dy);
        float dif;
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

        float cos_t = cos(t);
        float sin_t = sin(t);
        x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
        y = (1 / (r + 1)) * sin_t;
        lastPointX = x;
        lastPointY = y;
        rImpedanceRealCalculation(x, y);
        rAdmitanceRealCalculation(x, y);
        rImpedanceImagCalculation(x, y);
        rAdmitanceImagCalculation(x, y);
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number(impedanceRealR)));
        ui->rTable->setItem(1, 2, new QTableWidgetItem(QString::number(impedanceImagR)));
        ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(admitanceRealR)));
        ui->rTable->setItem(2, 2, new QTableWidgetItem(QString::number(admitanceImagR)));
        x = x * scale + renderArea->rect().center().x();
        y = y * scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (Model == mode::InductionParallel || Model == mode::CapacitorParallel)
    {
        t = t;
        float x, y;
        int dxABS = abs(dx);
        int dyABS = abs(dy);
        float dif;
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
            if ((dx < 0 && flag == false) || (dy > 0 && flag == true && t < M_PI/2) || (dy < 0 && flag == true && t > M_PI/2))
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
            else if ((dx > 0 && flag == false) || (dy < 0 && flag == true && t < M_PI/2) || (dy > 0 && flag == true && t > M_PI/2))
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

        float cos_t = cos(t);
        float sin_t = sin(t);

        x = (cos(t) - r) / (r + 1);
        y = (1 / (r + 1)) * sin_t*-1;
        lastPointX = x;
        lastPointY = y;
        rImpedanceRealCalculation(x, y);
        rAdmitanceRealCalculation(x, y);
        rImpedanceImagCalculation(x, y);
        rAdmitanceImagCalculation(x, y);
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number(impedanceRealR)));
        ui->rTable->setItem(1, 2, new QTableWidgetItem(QString::number(impedanceImagR)));
        ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(admitanceRealR)));
        ui->rTable->setItem(2, 2, new QTableWidgetItem(QString::number(admitanceImagR)));
        x = x * scale + renderArea->rect().center().x();
        y = y * scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
    }
    else if (Model==mode::ResistorShunt)
    {
        t = t;
        float x, y;
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
        else if ((dx < 0 && abs(lastPointY) <= abs(lastPointX - 1) && flag == false) || (flag == true && dy > 0 && lastPointY >= 0) || (flag == true && dy > 0 && lastPointY <= 0)||(dx>0&&abs(lastPointY)>=abs(lastPointX-1)&&flag==false))
        {
            if (t - step <= tmin)
            {
                t = tmin+step;
            }
            else
            {
                t -= step;
            }
        }
        else if ((dx > 0 && abs(lastPointY) <= abs(lastPointX - 1) && flag == false) || (flag == true && dy < 0 && lastPointY <= 0) || (flag==true&&dy<0&&lastPointY>=0)||(dx<0&&abs(lastPointY)>=abs(lastPointX-1)&&flag==false))
        {
            if (t + step >= tmax)
            {
                t = tmax-step;
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
        float cos_t = cos(t);
        float sin_t = sin(t);
        x = 1 + (1 / r) * cos_t;
        y = (1 / r) + (1 / r) * sin_t;
        y = y * (-1);
        rImpedanceRealCalculation(x, y);
        rAdmitanceRealCalculation(x, y);
        rImpedanceImagCalculation(x, y);
        rAdmitanceImagCalculation(x, y);
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number(impedanceRealR)));
        ui->rTable->setItem(1, 2, new QTableWidgetItem(QString::number(impedanceImagR)));
        ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(admitanceRealR)));
        ui->rTable->setItem(2, 2, new QTableWidgetItem(QString::number(admitanceImagR)));
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
        float x, y;
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
                t = tmin+step;
            }
            else
            {
                t -= step;
            }
        }
        else if ((dx > 0 && abs(lastPointY) <= abs(lastPointX + 1) && flag == false) || (flag == true && dy > 0 && lastPointY <= 0) || (flag == true && dy >0 && lastPointY >= 0) || (dx<0 && abs(lastPointY)>=abs(lastPointX + 1) && flag == false))
        {
            if (t + step >= tmax)
            {
                t = tmax-step;
            }
            else
            {
                t += step;
            }
        }
        float cos_t = cos(t);
        float sin_t = sin(t);
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
        lastPointX = x;
        lastPointY = y;
        rImpedanceRealCalculation(x, y);
        rAdmitanceRealCalculation(x, y);
        rImpedanceImagCalculation(x, y);
        rAdmitanceImagCalculation(x, y);
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number(impedanceRealR)));
        ui->rTable->setItem(1, 2, new QTableWidgetItem(QString::number(impedanceImagR)));
        ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(admitanceRealR)));
        ui->rTable->setItem(2, 2, new QTableWidgetItem(QString::number(admitanceImagR)));
        x = x * scale + renderArea->rect().center().x();
        y = y * scale + renderArea->rect().center().y();

        auxiliaryWidget->update();
        return QPoint(x, y);
        }
}

void Smithtry1000::onPlusSize_buttonClicked()
{
    if (scale < 600)
    {
        scale += 100;
        renderArea->update();
    }
}

void Smithtry1000::onMinusSize_buttonClicked()
{
    if (scale > 100)
    {
        scale -= 100;
        renderArea->update();
    }
}

void Smithtry1000::onDefaultSize_buttonClicked()
{
    scale = 200;
    renderArea->update();
}

void Smithtry1000::onGraph_buttonClicked()
{
    if (pointsX.size() > 1)
    {
        AmplitudeFrequency* amplitudeFrequence = new AmplitudeFrequency(nullptr, circuitElements);
        amplitudeFrequence->show();
        /*Circuit circuit;
        // Пример конфигурации цепи
        circuit.elements = {
            {"LCS", "s", {23.94, 0.001102}},
            {"LCS", "p", {2.917, 0.003275}},
            {"LCS", "p", {8.056, 0.009045}},
            {"LCS", "s", {29.4, 0.0008974}},
            {"C",   "p", {0.01037}},
            {"L",   "p", {2.543}}
        };
        circuit.ZS =
        {
            Complex(75.08, 0.84),
            Complex(81.22, 2.98),
            Complex(81.94, -1.52),
            Complex(85.15, -1.4),
            Complex(51.44, -1.19)
        };
        circuit.ZL =
        {
            Complex(83.16, -135.9),
            Complex(53.02, -102.9),
            Complex(35.56, -77.55),
            Complex(39.93, -68.64),
            Complex(22.69, -46.11)
        };
        amplitudeFrequence->calc_S2P(circuit);*/
        amplitudeFrequence->MatrixCalculation();
    }
}

complexNumber Smithtry1000::zCalculation(float x, float y)
{
    rImpedanceRealCalculation(x, y);
    rImpedanceImagCalculation(x, y);
    return complexNumber(impedanceRealR, impedanceImagR);
}

complexNumber Smithtry1000::yCalculation(float x, float y)
{
    rAdmitanceRealCalculation(x, y);
    rAdmitanceImagCalculation(x, y);
    return complexNumber(admitanceRealR, admitanceImagR);
}

complexNumber Smithtry1000::impedanceRealChartParameters(float x, float y)
{
    double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
    double xCenter = 1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    double sin_t = dy;
    double cos_t = dx;
    float t1, r1;
    if (y < 1e-6 && y >= 0)
    {
        if (y == 0 && x > 0.99)
        {
            t1 = 0;
        }
        else if (x > 0.99)
        {
            t1 = 2 * M_PI;
        }
        else
        {
            t1 = M_PI;
        }
    }
    else
    {
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
    }
    if (x - 1 != 0)
    {
        r1 = (cos(t1) - x) / (x - 1);
    }
    return complexNumber(r1, t1);
}

complexNumber Smithtry1000::admitanceRealChartParameters(float x, float y)
{
    double circleRadius = -1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 + 2 * x));
    double xCenter = -1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    dy *= -1;
    double sin_t = dy;
    double cos_t = dx;
    float t1, r1;
    if (y < 1e-6 && y >= 0)
    {
        if (y == 0 && x < -0.99)
        {
            t1 = 0;
        }
        else if (x < -0.99)
        {
            t1 = 2 * M_PI;
        }
        else
        {
            t1 = M_PI;
        }
    }
    else
    {
        t1 = atan(sin_t / cos_t);
        if (cos_t < 0 && sin_t < 0)
        {
            t1 = abs(t1) - M_PI;
        }
        else if (sin_t > 0 && cos_t < 0)
        {
            t1 = M_PI - abs(t1);
        }
    }
    if (x - 1 != 0)
    {
        r1 = (cos(t1) - x) / (x + 1);
    }
    return complexNumber(r1, t1);
}

complexNumber Smithtry1000::impedanceImagChartParameters(float x, float y)
{
    double cos_t;
    double sin_t;
    double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
    double xCenter = 1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    sin_t = dy;
    cos_t = dx;
    float t1, r1;
    if (abs(y) < 1e-6 && abs(y) >= 0)
    {
        if (y == 0 && x > 0.99)
        {
            t1 = 0.0001;
        }
        else if (x > 0.99)
        {
            t1 = 2 * M_PI;
        }
        else
        {
            t1 = M_PI;
        }
    }
    else
    {
        t1 = atan(cos_t / sin_t);
        if (y < 0)
        {
            t1 += M_PI;
        }
        else
        {
            t1 += 2 * M_PI;
        }
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
    return complexNumber(r1, t1);
}

complexNumber Smithtry1000::admitanceImagChartParameters(float x, float y)
{
    double cos_t;
    double sin_t;
    double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y, 2)) / (-2 * y);
    double yCenter = -circleRadius;
    double dx = x + 1;
    double dy = y - yCenter;
    sin_t = -dy;
    cos_t = dx;
    float t1, r1;
    if (abs(y) < 1e-6 && abs(y) >= 0)
    {
        if (y == 0 && x < -0.99)
        {
            t1 = M_PI / 2;
        }
        else if (x < -0.99)
        {
            t1 = -M_PI / 2;
        }
        else
        {
            t1 = 0;
        }
    }
    else
    {
        t1 = atan(sin_t / cos_t);
    }
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
    return complexNumber(r1, t1);
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