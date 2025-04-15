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

    connect(ui->button, &QPushButton::clicked, this, &Smithtry1000::onButtonClicked);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Smithtry1000::onTimeout);
    timer->start(10);  // Частое обновление для плавности
}

Smithtry1000::~Smithtry1000()
{
    delete ui;
}

void Smithtry1000::onButtonClicked()
{
    QPoint centerLocal = ui->renderArea->rect().center();
    QPoint centerGlobal = ui->renderArea->mapToGlobal(centerLocal);
    r = 4;
    t = M_PI/2;
    double cos_t = cos(t);
    double sin_t = sin(t);
    float x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
    float y = (1 / (r + 1)) * sin_t;
    trackingEnabled = !trackingEnabled;
    if (trackingEnabled)
    {
        this->setCursor(Qt::BlankCursor); // скрываем системный курсор
        double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x-1)));
        double xCenter = 1 - circleRadius;
        double dx = x - xCenter;
        double dy = y;
        sin_t = dy;
        cos_t = dx;
        if (y<1e-6 && y>0)
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
        double cos_t2 = cos(t);
        double sin_t2 = sin(t);
        double x2 = (r / (1 + r)) + (1 / (r + 1)) * cos_t2;
        double y2 = (1 / (r + 1)) * sin_t2;

        ui->button->setText("Stop");

        QCursor::setPos(centerGlobal);
        QPoint temp = QPoint(x2 * 300 + ui->renderArea->rect().center().x(), y2 * 300 + ui->renderArea->rect().center().y());
        ui->renderArea->setCursorPosOnCircle(temp);
    }
    else
    {
        this->unsetCursor(); // возвращаем курсор
        ui->button->setText("Start");
    }
}

void Smithtry1000::onTimeout()
{
    if (!trackingEnabled) return;
    // Центр окна в глобальных координатах
    QPoint centerLocal = ui->renderArea->rect().center();
    QPoint centerGlobal = ui->renderArea->mapToGlobal(centerLocal);

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
    float dif = max(dxABS, dyABS);
    step = 0.01 + dif/400;
    dy = dy * -1;
    bool flag = false;
    if (dyABS == dif)
    {
        flag = true;
    }
    x = 0;
    y = 0;
    if (dx == 0 && dy == 0)
    {
    }
    else if ((t == intervalLength / 2) && dy > 0 && flag == true)
    {
        if (t + step > intervalLength)
        {
            t = intervalLength;
        }
        else
        {
            t += step;
        }
    }
    else if (t == intervalLength / 2 && dy < 0 && flag == true)
    {
        if (t - step < 0)
        {
            t = 0;
        }
        else
        {
            t -= step;
        }
    }
    else if (t < intervalLength / 2 && t > 0)
    {
        if ((dx > 0 && flag == false) || (dy > 0 && flag == true && t < intervalLength / 4) || (dy<0 && flag == true && t>intervalLength / 4))
        {
            if (t - step < 0)
            {
                t = 0;
            }
            else
            {
                t -= step;
            }
        }
        else if ((dx < 0 && flag == false) || (dy > 0 && flag == true && t > intervalLength / 4) || (dy < 0 && flag == true && t < intervalLength / 4))
        {
            if (t + step > intervalLength)
            {
                t = intervalLength;
            }
            else
            {
                t += step;
            }
        }
    }
    else if (t > intervalLength / 2 && t < intervalLength)
    {
        if ((dx > 0 && flag == false) || (dy > 0 && flag == true && t < intervalLength*3/4) || (dy < 0 && flag==true && t > intervalLength*3/4))
        {
            if (t + step > intervalLength)
            {
                t = intervalLength;
            }
            else
            {
                t += step;
            }
        }
        else if ((dx < 0 && flag == false) || (dy < 0 && flag == true && t < intervalLength * 3 / 4) || (dy > 0 && flag == true && t > intervalLength * 3 / 4))
        {
            if (t - step < 0)
            {
                t = 0;
            }
            else
            {
                t -= step;
            }
        }
    }
    else if (t >= intervalLength)
    {
        step = 0.01;
        t = intervalLength;
        t -= step;
    }
    else if (t<=0)
    {
        t = 0;
        step = 0.01;
        t += step;
    }

    float cos_t = cos(t);
    float sin_t = sin(t);
    x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
    x = x * 300 + ui->renderArea->rect().center().x();
    y = (1 / (r + 1)) * sin_t;
    y = y * 300 + ui->renderArea->rect().center().y();
    return QPoint(x, y);
}

