#include "Smithtry1000.h"
#include <QCursor>
#include <QPoint>
#include <QRect>
#include <QtMath>
#include <QThread>
#include <cmath>
#include <exception>


mode Model;

Smithtry1000::Smithtry1000(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Smithtry1000Class())
    , trackingEnabled(false)
{
    ui->setupUi(this);
    Model = Default;
    this->resize(1600, 900);
    this->setMaximumSize(1600, 900);
    ui->rTable->setRowCount(3);
    ui->rTable->setColumnCount(3);
    ui->rTable->setItem(0, 1, new QTableWidgetItem("Real"));
    ui->rTable->setItem(0, 2, new QTableWidgetItem("Imag"));
    ui->rTable->setItem(1, 0, new QTableWidgetItem("Z"));
    ui->rTable->setItem(2, 0, new QTableWidgetItem("Y"));
    tmin = 0;
    tmax = 2 * M_PI;
    lastPointX = 0;
    lastPointY = 0;
    connect(ui->button, &QPushButton::clicked, this, &Smithtry1000::onButtonClicked);
    connect(ui->Capacitor_button, &QPushButton::clicked, this, &Smithtry1000::onCapacitor_buttonClicked);
    connect(ui->Induction_button, &QPushButton::clicked, this, &Smithtry1000::onInduction_buttonClicked);
    connect(ui->Resistor_button, &QPushButton::clicked, this, &Smithtry1000::onResistor_buttonClicked);
    connect(ui->CapacitorParallel_button, &QPushButton::clicked, this, &Smithtry1000::onCapacitorParallel_buttonClicked);
    connect(ui->InductionParallel_button, &QPushButton::clicked, this, &Smithtry1000::onInductionParallel_buttonClicked);
    connect(ui->ResistorParallel_button, &QPushButton::clicked, this, &Smithtry1000::onResistorParallel_buttonClicked);
    connect(ui->Delete_button, &QPushButton::clicked, this, &Smithtry1000::onDelete_buttonClicked);
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Smithtry1000::onTimeout);
    timer->start(10);  // Частое обновление для плавности
}

Smithtry1000::~Smithtry1000()
{
    delete ui;
}

void Smithtry1000::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        leftClicked = true; // Изменяем флаг при нажатии левой кнопки мыши
    }
    else if (event->button() == Qt::RightButton)
    {
        rightClicked = true;
    }
}

void Smithtry1000::onButtonClicked()
{
    Model = mode::AddPoint;
    ui->button->setText("Stop");
    QPoint centerLocal = ui->renderArea->rect().center();
    QPoint centerGlobal = ui->renderArea->mapToGlobal(centerLocal);
    QCursor::setPos(lastPointX*300+centerGlobal.x(), lastPointY*300+centerGlobal.y());
    leftClicked = false;
    rightClicked = false;
    QPoint point = QCursor::pos();
    while (!leftClicked && !rightClicked)
    {
        QCoreApplication::processEvents();
        point = QCursor::pos();
        if (pow(point.x() - centerGlobal.x(), 2) + pow(point.y() - centerGlobal.y(), 2) >= pow(300, 2))
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
        x = (x - centerGlobal.x()) / 300;
        y = (y - centerGlobal.y()) / 300;
        double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
        double xCenter = 1 - circleRadius;
        double dx = x - xCenter;
        double dy = y;
        double sin_t = dy;
        double cos_t = dx;
        if (y < 1e-6 && y>=0)
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
        QPoint temp = QPoint(x * 300 + ui->renderArea->rect().center().x(), y * 300 + ui->renderArea->rect().center().y());
        ui->renderArea->setCursorPosOnCircle(temp);
        if (index == 0)
        {
            pointsX.append(x);
            pointsY.append(y);
            points[index]=make_tuple(temp, r, t, mode::AddPoint);
            index++;
            ui->renderArea->setCursorPosOnCircle(temp);
        }
        else
        {
            morePoints.append(temp);
            ui->renderArea->setCursorPosOnCircle(temp);
        }
    }
    ui->button->setText("Start");
    Model = Default;
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
    leftClicked = false;
    rightClicked = false;
    QPoint centerLocal = ui->renderArea->rect().center();
    QPoint centerGlobal = ui->renderArea->mapToGlobal(centerLocal);
    if (pointsX.size() > 0)
    {
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
            if (y == 0)
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
            tmax = 2 * M_PI;
        }
        else
        {
            r = abs(r) * (-1);
            tmax = t;
            tmin = 0;
        }
        trackingEnabled = !trackingEnabled;
        while (!leftClicked && !rightClicked)
        {
            QCoreApplication::processEvents();
        }
        if (leftClicked)
        {
            pointsX.append(lastPointX);
            pointsY.append(lastPointY);
            QPoint temp = QPoint(pointsX.back() * 300 + ui->renderArea->rect().center().x(), pointsY.back() * 300 + ui->renderArea->rect().center().y());
            points[index] = make_tuple(temp, r, t, mode::ResistorShunt);
            index++;
            ui->renderArea->setCursorPosOnCircle(temp);
        }
        if (rightClicked)
        {
            QPoint temp = QPoint(pointsX.back() * 300 + ui->renderArea->rect().center().x(), pointsY.back() * 300 + ui->renderArea->rect().center().y());
            ui->renderArea->setCursorPosOnCircle(temp);
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
    leftClicked = false;
    rightClicked = false;
    QPoint centerLocal = ui->renderArea->rect().center();
    QPoint centerGlobal = ui->renderArea->mapToGlobal(centerLocal);
    if (pointsX.size() > 0)
    {
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
        if (y < 1e-6 && y>0)
        {
            if (y == 0)
            {
                t = 0;
            }
            else if (x == -1)
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
            pointsX.append(lastPointX);
            pointsY.append(lastPointY);
            QPoint temp = QPoint(pointsX.back() * 300 + ui->renderArea->rect().center().x(), pointsY.back() * 300 + ui->renderArea->rect().center().y());
            points[index] = make_tuple(temp, r, t, mode::ResistorParallel);
            index++;
            ui->renderArea->setCursorPosOnCircle(temp);
        }
        if (rightClicked)
        {
            QPoint temp = QPoint(pointsX.back() * 300 + ui->renderArea->rect().center().x(), pointsY.back() * 300 + ui->renderArea->rect().center().y());
            ui->renderArea->setCursorPosOnCircle(temp);
        }
        Model = Default;
        this->unsetCursor(); // возвращаем курсор
    }
}

void Smithtry1000::onDelete_buttonClicked()
{
    if (index > 0)
    {
        points.erase(index-1);
        index--;
        pointsX.pop_back();
        pointsY.pop_back();
        ui->renderArea->update();
    }
}

void Smithtry1000::ImaginaryImpedance()
{
    leftClicked = false;
    rightClicked = false;
    QPoint centerLocal = ui->renderArea->rect().center();
    QPoint centerGlobal = ui->renderArea->mapToGlobal(centerLocal);
    if (pointsX.size() > 0)
    {
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
            tmin = 0;
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
            pointsX.append(lastPointX);
            pointsY.append(lastPointY);
            QPoint temp = QPoint(pointsX.back() * 300 + ui->renderArea->rect().center().x(), pointsY.back() * 300 + ui->renderArea->rect().center().y());
            points[index] = make_tuple(temp, r, t, Model);
            index++;
            ui->renderArea->setCursorPosOnCircle(temp);
        }
        if (rightClicked)
        {
            QPoint temp = QPoint(pointsX.back() * 300 + ui->renderArea->rect().center().x(), pointsY.back() * 300 + ui->renderArea->rect().center().y());
            ui->renderArea->setCursorPosOnCircle(temp);
        }
        Model = Default;
        this->unsetCursor(); // возвращаем курсор
    }
}

void Smithtry1000::ImaginaryAdmitance()
{
    leftClicked = false;
    rightClicked = false;
    QPoint centerLocal = ui->renderArea->rect().center();
    QPoint centerGlobal = ui->renderArea->mapToGlobal(centerLocal);
    if (pointsX.size() > 0)
    {
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
            if (y == 0 && x == -1)
            {
                t = 0;
            }
            else if (x == -1)
            {
                t = 2 * M_PI;
            }
            else if (x == 0)
            {
                t = M_PI;
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
        if (x - 1 != 0)
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
            pointsX.append(lastPointX);
            pointsY.append(lastPointY);
            QPoint temp = QPoint(pointsX.back() * 300 + ui->renderArea->rect().center().x(), pointsY.back() * 300 + ui->renderArea->rect().center().y());
            points[index] = make_tuple(temp, r, t, Model);
            index++;
            ui->renderArea->setCursorPosOnCircle(temp);
        }
        if (rightClicked)
        {
            QPoint temp = QPoint(pointsX.back() * 300 + ui->renderArea->rect().center().x(), pointsY.back() * 300 + ui->renderArea->rect().center().y());
            ui->renderArea->setCursorPosOnCircle(temp);
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
        if (y == 0 && x == 1)
        {
            t1 = 0;
        }
        else if (x == 1)
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
        if (x == -1)
        {
            t1 = 2 * M_PI;
        }
        else if (y == 0)
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
    admitanceRealR *= 50;
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
    if (y < 1e-6 && y>0)
    {
        if (y == 0)
        {
            t1 = 0;
        }
        else if (x == 1)
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
    if (y < 1e-6 && y>0)
    {
        if (y == 0)
        {
            t1 = 0;
        }
        else if (x == -1)
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
    admitanceImagR *= 50;
}

void Smithtry1000::onTimeout()
{

    QPoint centerLocal = ui->renderArea->rect().center();
    QPoint centerGlobal = ui->renderArea->mapToGlobal(centerLocal);
    if (Model == AddPoint)
    {
        QPoint temp = QCursor::pos();
        float x = temp.x();
        float y = temp.y();
        x = (x - centerGlobal.x()) / 300;
        y = (y - centerGlobal.y()) / 300;
        rImpedanceRealCalculation(x, y);
        rAdmitanceRealCalculation(x, y);
        rImpedanceImagCalculation(x, y);
        rAdmitanceImagCalculation(x, y);
        ui->rTable->setItem(1, 1, new QTableWidgetItem(QString::number(impedanceRealR)));
        ui->rTable->setItem(1, 2, new QTableWidgetItem(QString::number(impedanceImagR)));
        ui->rTable->setItem(2, 1, new QTableWidgetItem(QString::number(admitanceRealR)));
        ui->rTable->setItem(2, 2, new QTableWidgetItem(QString::number(admitanceImagR)));
    }
    if (Model == Default)
    {
        QPoint temp = QCursor::pos();
        float x = temp.x();
        float y = temp.y();
        x = (x - centerGlobal.x()) / 300;
        y = (y - centerGlobal.y()) / 300;
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
        ui->button->setText("Start");
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
        if (pow(posOnCircle.x() - centerLocal.x(), 2) + pow(posOnCircle.y() - centerLocal.y(), 2) > pow(300, 2))
        {
            QCursor::setPos(tempX, tempY);
            posOnCircle.setX(tempX);
            posOnCircle.setY(tempY);
        }
        tempX = posOnCircle.x();
        tempY = posOnCircle.y();
        QCursor::setPos(ui->renderArea->mapToGlobal(posOnCircle));
        ui->renderArea->setCursorPosOnCircle(posOnCircle);
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
        x = x * 300 + ui->renderArea->rect().center().x();
        y = y * 300 + ui->renderArea->rect().center().y();
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
        x = x * 300 + ui->renderArea->rect().center().x();
        y = y * 300 + ui->renderArea->rect().center().y();
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
        step = abs(r) / 100;
        x = 0;
        y = 0;
        if (lastPointY > 0)
        {
            dx *= -1;
        }
        if (dx == 0 && dy == 0)
        {
        }
        else if ((dx < 0 && abs(lastPointY) < abs(lastPointX + 1) && flag == false) || (flag == true && dy > 0 && lastPointY > 0) || (flag == true && dy > 0 && lastPointY < 0)||(dx>0&&abs(lastPointY)>abs(lastPointX+1)&&flag==false))
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
        else if ((dx > 0 && abs(lastPointY) < abs(lastPointX + 1) && flag == false) || (flag == true && dy < 0 && lastPointY < 0) || (flag==true&&dy<0&&lastPointY>0)||(dx<0&&abs(lastPointY)>abs(lastPointX+1)&&flag==false))
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
        x = x * 300 + ui->renderArea->rect().center().x();
        y = y * 300 + ui->renderArea->rect().center().y();
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
        step = abs(r) / 100;
        x = 0;
        y = 0;
        if (lastPointY > 0)
        {
            dx *= -1;
        }
        if (dx == 0 && dy == 0)
        {
        }
        else if ((dx < 0 && abs(lastPointY) < abs(lastPointX + 1) && flag == false) || (flag == true && dy < 0 && lastPointY > 0) || (flag == true && dy < 0 && lastPointY < 0) || (dx > 0 && abs(lastPointY) > abs(lastPointX + 1) && flag == false))
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
        else if ((dx > 0 && abs(lastPointY) < abs(lastPointX + 1) && flag == false) || (flag == true && dy > 0 && lastPointY < 0) || (flag == true && dy >0 && lastPointY > 0) || (dx<0 && abs(lastPointY)>abs(lastPointX + 1) && flag == false))
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
        x = x * 300 + ui->renderArea->rect().center().x();
        y = y * 300 + ui->renderArea->rect().center().y();
        return QPoint(x, y);
        }
}