#include "Smithtry1000.h"
#include <QCursor>
#include <QPoint>
#include <QRect>
#include <QtMath>

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
    trackingEnabled = !trackingEnabled;

    if (trackingEnabled)
    {
        this->setCursor(Qt::BlankCursor); // скрываем системный курсор
        t = intervalLength/2;
        QPoint initialPos = getPointOnCircle(0, 0);
        QCursor::setPos(ui->renderArea->mapToGlobal(initialPos));
        ui->button->setText("Stop");
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
    x = ui->renderArea->rect().center().x();
    y = ui->renderArea->rect().center().y();
    if (dx == 0 && dy == 0)
    {
        float cos_t = cos(t);
        float sin_t = sin(t);
        x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
        x = x * 300 + ui->renderArea->rect().center().x();
        y = (1 / (r + 1)) * sin_t;
        y = y * 300 + ui->renderArea->rect().center().y();
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
        float cos_t = cos(t);
        float sin_t = sin(t);
        x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
        x = x * 300 + ui->renderArea->rect().center().x();
        y = (1 / (r + 1)) * sin_t;
        y = y * 300 + ui->renderArea->rect().center().y();
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
        float cos_t = cos(t);
        float sin_t = sin(t);
        x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
        x = x * 300 + ui->renderArea->rect().center().x();
        y = (1 / (r + 1)) * sin_t;
        y = y * 300 + ui->renderArea->rect().center().y();
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
            float cos_t = cos(t);
            float sin_t = sin(t);
            x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
            x = x * 300 + ui->renderArea->rect().center().x();
            y = (1 / (r + 1)) * sin_t;
            y = y * 300 + ui->renderArea->rect().center().y();
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
            float cos_t = cos(t);
            float sin_t = sin(t);
            x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
            x = x * 300 + ui->renderArea->rect().center().x();
            y = (1 / (r + 1)) * sin_t;
            y = y * 300 + ui->renderArea->rect().center().y();
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
            float cos_t = cos(t);
            float sin_t = sin(t);
            x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
            x = x * 300 + ui->renderArea->rect().center().x();
            y = (1 / (r + 1)) * sin_t;
            y = y * 300 + ui->renderArea->rect().center().y();
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
            float cos_t = cos(t);
            float sin_t = sin(t);
            x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
            x = x * 300 + ui->renderArea->rect().center().x();
            y = (1 / (r + 1)) * sin_t;
            y = y * 300 + ui->renderArea->rect().center().y();
        }
    }
    else if (t >= intervalLength)
    {
        step = 0.01;
        t -= step;
        float cos_t = cos(t);
        float sin_t = sin(t);
        x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
        x = x * 300 + ui->renderArea->rect().center().x();
        y = (1 / (r + 1)) * sin_t;
        y = y * 300 + ui->renderArea->rect().center().y();
    }
    else if (t<=0)
    {
        step = 0.01;
        t += step;
        float cos_t = cos(t);
        float sin_t = sin(t);
        x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
        x = x * 300 + ui->renderArea->rect().center().x();
        y = (1 / (r + 1)) * sin_t;
        y = y * 300 + ui->renderArea->rect().center().y();
    }
    return QPoint(x, y);
}