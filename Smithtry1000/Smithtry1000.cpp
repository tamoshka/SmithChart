#include "Smithtry1000.h"
#include <QCursor>
#include <QPoint>
#include <QRect>
#include <QtMath>
#include <cmath>
#include <exception>

Smithtry1000::Smithtry1000(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Smithtry1000Class())
    , trackingEnabled(false)
{
    ui->setupUi(this);
    this->resize(1600, 900);
    this->setMaximumSize(1600, 900);
    tmin = 0;
    tmax = 2 * M_PI;
    lastPointX = 0;
    lastPointY = 0;
    connect(ui->button, &QPushButton::clicked, this, &Smithtry1000::onButtonClicked);
    connect(ui->Capacitor_button, &QPushButton::clicked, this, &Smithtry1000::onCapacitor_buttonClicked);
    connect(ui->Induction_button, &QPushButton::clicked, this, &Smithtry1000::onInduction_buttonClicked);
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
    ui->button->setText("Stop");
    QPoint centerLocal = ui->renderArea->rect().center();
    QPoint centerGlobal = ui->renderArea->mapToGlobal(centerLocal);
    QCursor::setPos(lastPointX*300+centerGlobal.x(), lastPointY*300+centerGlobal.y());
    leftClicked = false;
    rightClicked = false;
    while (!leftClicked && !rightClicked)
    {
        QCoreApplication::processEvents();
    }
    if (leftClicked)
    {
        QPoint point = QCursor::pos();
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
        if (firstPoint == true)
        {
            pointsX.append(x);
            pointsY.append(y);
            firstPoint = false;
        }
        lastPointX = x;
        lastPointY = y;
    }
    ui->button->setText("Start");
}

void Smithtry1000::onInduction_buttonClicked()
{
    leftClicked = false;
    rightClicked = false;
    QPoint centerLocal = ui->renderArea->rect().center();
    QPoint centerGlobal = ui->renderArea->mapToGlobal(centerLocal);
    if (pointsX.size() > 0)
    {
        QCursor::setPos(centerGlobal);
        double cos_t;
        double sin_t;
        float x = pointsX.back();
        float y = pointsY.back();
        this->setCursor(Qt::BlankCursor); // скрываем системный курсор
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
        tmin = t;
        tmax = 2 * M_PI;
        trackingEnabled = !trackingEnabled;
        while (!leftClicked && !rightClicked)
        {
            QCoreApplication::processEvents();
        }
        if (leftClicked)
        {
            pointsX.append(lastPointX);
            pointsY.append(lastPointY);
        }
        if (rightClicked)
        {
            QPoint temp = QPoint(pointsX.back() * 300 + ui->renderArea->rect().center().x(), pointsY.back() * 300 + ui->renderArea->rect().center().y());
            ui->renderArea->setCursorPosOnCircle(temp);
        }
        this->unsetCursor(); // возвращаем курсор
    }
}

void Smithtry1000::onCapacitor_buttonClicked()
{
    leftClicked = false;
    rightClicked = false;
    QPoint centerLocal = ui->renderArea->rect().center();
    QPoint centerGlobal = ui->renderArea->mapToGlobal(centerLocal);
    if (pointsX.size() > 0)
    {
        QCursor::setPos(centerGlobal);
        double cos_t;
        double sin_t;
        float x = pointsX.back();
        float y = pointsY.back();
        this->setCursor(Qt::BlankCursor); // скрываем системный курсор
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
        tmax = t;
        tmin = 0;
        trackingEnabled = !trackingEnabled;
        while (!leftClicked && !rightClicked)
        {
            QCoreApplication::processEvents();
        }
        if (leftClicked)
        {
            pointsX.append(lastPointX);
            pointsY.append(lastPointY);
        }
        if (rightClicked)
        {
            QPoint temp = QPoint(pointsX.back() * 300 + ui->renderArea->rect().center().x(), pointsY.back() * 300 + ui->renderArea->rect().center().y());
            ui->renderArea->setCursorPosOnCircle(temp);
        }
        this->unsetCursor(); // возвращаем курсор
    }
}

void Smithtry1000::onTimeout()
{
    if (!trackingEnabled) return;
    // Центр окна в глобальных координатах
    QPoint centerLocal = ui->renderArea->rect().center();
    QPoint centerGlobal = ui->renderArea->mapToGlobal(centerLocal);
    if (leftClicked || rightClicked)
    {
        trackingEnabled = false;
        this->unsetCursor(); // возвращаем курсор
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
        QCursor::setPos(ui->renderArea->mapToGlobal(posOnCircle));
        ui->renderArea->setCursorPosOnCircle(posOnCircle);
        // Возвращаем системный курсор обратно в центр
        QCursor::setPos(centerGlobal);
    }
}

QPoint Smithtry1000::getPointOnCircle(int dx, int dy)
{
    t = t;
    float x, y;
    int dxABS = abs(dx);
    int dyABS = abs(dy);
    float dif;
    dy = dy * -1;
    bool flag;
    if (dyABS>dxABS)
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
        if ((dx > 0 && flag == false) || (dy > 0 && flag == true && t < intervalLength*3/4) || (dy < 0 && flag==true && t > intervalLength*3/4))
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
    else if (t<=tmin)
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
    x = x * 300 + ui->renderArea->rect().center().x();
    y = y * 300 + ui->renderArea->rect().center().y();
    return QPoint(x, y);
}

