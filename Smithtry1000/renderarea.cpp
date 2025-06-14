#include <iostream>
#include "renderarea.h"
#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>
#include <QMessageBox>
#include "general.h"
#include <cmath>
#include <QCursor>
#include "Smithtry1000.h"


RenderArea::RenderArea(QWidget* parent) :
    QWidget(parent),
    mBackGroundColor(255, 255, 255),
    mShapeColor(0, 0, 0),
    mMode(Impedence)
{
     m_cacheValid = false;
     m_scaleFactor = 2.0;
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 100);
}

QPointF RenderArea::compute_real(float t)
{
    float cos_t = cos(t);
    float sin_t = sin(t);
    float x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
    float y = (1 / (r + 1)) * sin_t;


    return QPointF(x, y);

}
QPointF RenderArea::compute_realParallel(float t)
{
    float cos_t = cos(t);
    float sin_t = sin(t);
    float x = (cos(t)-r)/(r+1);
    float y = (1 / (r + 1)) * sin_t;


    return QPointF(x, y);

}

QPointF RenderArea::compute_imaginary(float t)
{
    float cos_t = cos(t);
    float sin_t = sin(t);
    float x = 1 + (1 / r) * cos_t;
    float y = (1 / r) + (1 / r) * sin_t;

    return QPointF(x, y);

}

QPointF RenderArea::compute_imaginaryParallel(float t)
{
    float cos_t = cos(t);
    float sin_t = sin(t);
    float x;
    float y;
    if (r > 0)
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

    return QPointF(x, y);
}

void RenderArea::drawStaticObjects(QPainter& painter)
{
    center = this->rect().center();
    painter.setBrush(mBackGroundColor);
    painter.setPen(QPen((mShapeColor, 20)));
    painter.drawRect(this->rect());
    painter.drawLine(QPointF(center.x(), -1000 + center.y()), QPointF(center.x(), 1000 + center.y()));
    painter.drawLine(QPointF(-1000 + center.x(), center.y()), QPointF(1000 + center.x(), center.y()));
    painter.setPen(mShapeColor);
    painter.setPen(Qt::blue);
    float intervalLength = 2 * M_PI;
    int stepCount = 2000;
    float step;
    QPointF iPoint;
    QPointF iPixel;
    step = intervalLength / stepCount;
    painter.setPen(Qt::blue);
    double m = 0;
    for (RenderArea::r = -10; RenderArea::r <= 10; RenderArea::r += 0) {
        if (r == -10)
        {
            m = -8;
        }
        if (r == -0.25)
        {
            r = -0.2;
        }
        if (r == 0.25)
        {
            r = 0.2;
        }
        if (r == 8)
        {
            r = 10;
        }
        iPoint = compute_imaginary(0);
        iPixel.setX
        (iPoint.x() * scale + center.x());
        iPixel.setY(-iPoint.y() * scale + center.y());
        bool flagi = false;
        for (float t = step; t < intervalLength; t += step) {

            QPointF point = compute_imaginary(t);
            QPointF pixel;
            pixel.setX(point.x() * scale + center.x());
            pixel.setY(-point.y() * scale + center.y());

            if ((abs(pow(point.x(), 2) + pow(point.y(), 2) - 1) < 0.012) &&
                ((abs(pow(point.x(), 2) + pow(point.y(), 2) - 1) > 0.005)) &&
                flagi == false && 
                (
                    (point.y() * scale + center.y() > iPixel.y() + 1) ||
                    (point.y() * scale + center.y() < iPixel.y() - 1)
                )
                && r>0
                )
                
            {
                painter.setPen(QPen(Qt::magenta, 2));
                QString s1 = QString::number(r * 50);
                painter.setFont(QFont("Arial", 8));
                painter.drawText(point.x() * scale + center.x(), -point.y() * scale + center.y(), s1);
                painter.setPen(Qt::blue);
                flagi = true;
            }



            painter.setPen(Qt::blue);

            if (pow(point.x(), 2) + pow(point.y(), 2) < 1) 
            {
                painter.drawLine(iPixel, pixel);
            }
            iPixel = pixel;
        }
        if (m < 0 && m < -0.25)
        {
            m /= 2;
        }
        else if (m > 0)
        {
            m *= 2;
        }
        else if (m < 0)
        {
            m *= -1;
        }
        r = m;
    }

    double k = 0.125;
    for (RenderArea::r = 0; RenderArea::r < 10; RenderArea::r += 0) {
        if (r == 0.25)
        {
            r = 0.2;
        }
        if (r == 8)
        {
            r = 10;
        }
        iPoint = compute_real(0);
        iPixel.setX(iPoint.x() * scale + center.x());
        iPixel.setY(-iPoint.y() * scale + center.y());
        bool flagi = false;
        for (float t = 0; t < intervalLength; t += step) {

            QPointF point = compute_real(t);
            QPointF pixel;
            pixel.setX(point.x() * scale + center.x());
            pixel.setY(point.y() * scale + center.y());

            if ((floor(point.y() * scale) == 0.0) && (pixel.y() < iPixel.y()) && flagi == false)
            {
                painter.setPen(QPen(Qt::magenta, 2));
                QString s1 = QString::number(r * 50);
                painter.setFont(QFont("Arial", 8));
                painter.drawText(point.x() * scale + center.x(), center.y(), s1);
                painter.setPen(Qt::blue);
                flagi == true;
            }


            if (r == 1)
            {
                painter.setPen(QPen(Qt::blue, 3));
            }
            painter.drawLine(iPixel, pixel);
            iPixel = pixel;
            painter.setPen(Qt::blue);

        }
        k *= 2;
        r = k;
    }
    painter.setPen(Qt::red);
    m = 0;
    for (RenderArea::r = -10; RenderArea::r <= 10; RenderArea::r += 0) {
        if (r == -10)
        {
            m = -8;
        }
        if (r == -0.25)
        {
            r = -0.2;
        }
        if (r == 0.25)
        {
            r = 0.2;
        }
        if (r == 8)
        {
            r = 10;
        }
        iPoint = compute_imaginary(0);
        iPixel.setX
        (-iPoint.x() * scale + center.x());
        iPixel.setY(-iPoint.y() * scale + center.y());
        bool flagi = false;
        for (float t = step; t < intervalLength; t += step) {

            QPointF point = compute_imaginary(t);
            QPointF pixel;
            pixel.setX(-point.x() * scale + center.x());
            pixel.setY(-point.y() * scale + center.y());

            if ((abs(pow(point.x(), 2) + pow(point.y(), 2) - 1) < 0.012) &&
                ((abs(pow(point.x(), 2) + pow(point.y(), 2) - 1) > 0.005)) &&
                flagi == false &&
                r<0 &&
                (
                    (point.y() * scale + center.y() > iPixel.y() + 1) ||
                    (point.y() * scale + center.y() < iPixel.y() - 1)
                    )
                )
            {
                painter.setPen(QPen(Qt::green, 2));
                QString s1 = QString::number(r * 1000/-50);
                painter.setFont(QFont("Arial", 8));
                painter.drawText(-point.x() * scale + center.x() + 10, -point.y() * scale + center.y() - 10, s1);
                painter.setPen(Qt::red);
                flagi = true;
            }



            painter.setPen(Qt::red);

            if (pow(point.x(), 2) + pow(point.y(), 2) < 1) 
            {
                painter.drawLine(iPixel, pixel);
            }
            iPixel = pixel;
        }
        if (m < 0 && m < -0.25)
        {
            m /= 2;
        }
        else if (m > 0)
        {
            m *= 2;
        }
        else if (m < 0)
        {
            m *= -1;
        }
        r = m;
    }
    k = 0.25;
    for (RenderArea::r = 0.25; RenderArea::r < 10; RenderArea::r += 0) {
        if (r == 0.25)
        {
            r = 0.2;
        }
        if (r == 8)
        {
            r = 10;
        }
        iPoint = compute_real(0);
        iPixel.setX(-iPoint.x() * scale + center.x());
        iPixel.setY(-iPoint.y() * scale + center.y());
        bool flagi = false;
        for (float t = 0; t < intervalLength; t += step) {

            QPointF point = compute_real(t);
            QPointF pixel;
            pixel.setX(-point.x() * scale + center.x());
            pixel.setY(point.y() * scale + center.y());

            if ((floor(point.y() * scale) == 0.0) && (pixel.y() < iPixel.y()) && flagi == false)
            {
                painter.setPen(QPen(Qt::green, 2));
                QString s1 = QString::number(r * 1000 / 50);
                painter.setFont(QFont("Arial", 8));
                painter.drawText(-point.x() * scale + center.x(), center.y() + 10, s1);
                painter.setPen(Qt::red);
                flagi == true;
            }
            if (r == 1)
            {
                painter.setPen(QPen(Qt::red, 3));
            }
            painter.drawLine(iPixel, pixel);
            iPixel = pixel;
            painter.setPen(Qt::red);
        }
        k *= 2;
        r = k;
    }
}

void RenderArea::drawDynamicObject(QPainter& painter)
{
    float intervalLength = 2 * M_PI;
    int stepCount = 2000;
    float step;
    QPointF iPoint;
    QPointF iPixel;
    step = intervalLength / stepCount;
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    if (Model != Default && Model != AddPoint)
    {
        painter.drawEllipse(cursorPos, 5, 5);
    }
    for (int ii = 0; ii < index; ii++)
    {
        float x = get<0>(points[ii]).x * scale + this->rect().center().x();
        float y = get<0>(points[ii]).y * scale + this->rect().center().y();
        QPointF point = QPointF(x, y);
        painter.drawEllipse(point, 5, 5);
    }
    painter.setPen(QPen(Qt::magenta, 2));
    for (int ll = 0; ll < index - 1; ll++)
    {
        if (get<3>(points[ll + 1]) == mode::InductionShunt || get<3>(points[ll + 1]) == mode::CapacitorShunt)
        {
            r = get<1>(points[ll + 1]);
            float x = get<0>(points[ll]).x;
            float y = get<0>(points[ll]).y;
            float t;
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
            float t2 = get<2>(points[ll + 1]);
            if (t2 < t)
            {
                float temp = t;
                t = t2;
                t2 = temp;
            }
            iPoint = compute_real(t);
            iPixel.setX(iPoint.x() * scale + this->rect().center().x());
            iPixel.setY(iPoint.y() * scale + this->rect().center().y());
            bool flagi = false;
            step = abs(t2 - t) / 100;
            for (t; t < t2; t += step) {

                QPointF point = compute_real(t);
                QPointF pixel;

                pixel.setX(point.x() * scale + center.x());
                pixel.setY(point.y() * scale + center.y());




                painter.drawLine(iPixel, pixel);
                iPixel = pixel;


            }
        }
        else if (get<3>(points[ll + 1]) == mode::ResistorShunt)
        {
            r = get<1>(points[ll + 1]);
            float t2 = get<2>(points[ll + 1]);
            float t;
            float x = get<0>(points[ll]).x;
            float y = get<0>(points[ll]).y;
            double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
            double xCenter = 1 - circleRadius;
            double dx = x - xCenter;
            double dy = y;
            float sin_t = dy;
            float cos_t = dx;
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
            step = abs(t2 - t) / 100;
            float tmin, tmax;
            if (t2 > t)
            {
                tmax = t2;
                tmin = t;
            }
            else
            {
                tmax = t;
                tmin = t2;
            }
            iPoint = compute_imaginary(tmin);
            iPixel.setX(iPoint.x() * scale + this->rect().center().x());
            iPixel.setY(-iPoint.y() * scale + this->rect().center().y());
            for (tmin = tmin + step; tmin < tmax; tmin += step) {

                QPointF point = compute_imaginary(tmin);
                QPointF pixel;
                pixel.setX(point.x() * scale + center.x());
                pixel.setY(-point.y() * scale + center.y());
                painter.drawLine(iPixel, pixel);
                iPixel = pixel;

            }
        }
        else if (get<3>(points[ll + 1]) == mode::InductionParallel|| get<3>(points[ll + 1]) == mode::CapacitorParallel)
        {
            r = get<1>(points[ll + 1]);
            float x = get<0>(points[ll]).x;
            float y = get<0>(points[ll]).y;
            float t;
            double circleRadius = -1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 + 2 * x));
            double xCenter = -1 - circleRadius;
            double dx = x - xCenter;
            double dy = -y;
            double sin_t = dy;
            double cos_t = dx;
            if (y < 1e-6 && y >= 0)
            {
                if (y == 0 && x == -1)
                {
                    t = -M_PI;
                }
                else if (x == -1)
                {
                    t = M_PI;
                }
                else if (x == 0)
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
            if (x - 1 != 0)
            {
                r = (cos(t) - x) / (x + 1);
            }
            float t2 = get<2>(points[ll + 1]);
            bool flagi = false;
            step = abs(t2 - t) / 100;
            if (t2 < t)
            {
                float temp = t;
                t = t2;
                t2 = temp;
            }

            iPoint = compute_realParallel(t);
            iPixel.setX(iPoint.x()* scale + this->rect().center().x());
            iPixel.setY(-iPoint.y() * scale + this->rect().center().y());
            for (t; t < t2; t += step) {

                QPointF point = compute_realParallel(t);
                QPointF pixel;

                pixel.setX(point.x() * scale + center.x());
                pixel.setY(-point.y() * scale + center.y());




                painter.drawLine(iPixel, pixel);
                iPixel = pixel;


            }
        }
        else if (get<3>(points[ll + 1]) == mode::ResistorParallel)
        {
            r = get<1>(points[ll + 1]);
            float t2 = get<2>(points[ll + 1]);
            float t;
            float x = get<0>(points[ll]).x;
            float y = get<0>(points[ll]).y;
            double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y, 2)) / (-2 * y);
            double yCenter = -circleRadius;
            double dx = x + 1;
            double dy = y - yCenter;
            float sin_t = -dy;
            float cos_t = dx;
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
                t = atan(sin_t / cos_t);
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
            }
            step = abs(t2 - t) / 100;
            float tmin, tmax;
            if (t2 > t)
            {
                tmax = t2;
                tmin = t;
            }
            else
            {
                tmax = t;
                tmin = t2;
            }
            iPoint = compute_imaginaryParallel(tmin);
            iPixel.setX(iPoint.x() * scale + this->rect().center().x());
            iPixel.setY(iPoint.y() * scale + this->rect().center().y());
            for (tmin = tmin + step; tmin < tmax; tmin += step) {

                QPointF point = compute_imaginaryParallel(tmin);
                QPointF pixel;
                pixel.setX(point.x() * scale + center.x());
                pixel.setY(point.y() * scale + center.y());
                painter.drawLine(iPixel, pixel);
                iPixel = pixel;

            }
        }
    }

    for (int jj = 0; jj < morePoints.size(); jj++)
    {
        float x = morePoints[jj].x * scale + this->rect().center().x();
        float y = morePoints[jj].y * scale + this->rect().center().y();
        QPointF point = QPointF(x, y);
        painter.drawEllipse(point, 5, 5);
    }
    if (index > 0 && Model != mode::AddPoint && Model != mode::Default)
    {
        painter.setPen(QPen(Qt::green, 2));
        float tmax, tmin;
        if (Model == mode::InductionShunt || Model==mode::CapacitorShunt)
        {
            float t;
            float x = get<0>(points[index - 1]).x;
            float y = get<0>(points[index - 1]).y;
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
            iPoint = compute_real(tmin);
            iPixel.setX(iPoint.x() * scale + this->rect().center().x());
            iPixel.setY(iPoint.y() * scale + this->rect().center().y());
            bool flagi = false;
            step = abs(tmax - tmin) / 100;
            for (tmin; tmin < tmax; tmin += step) {

                QPointF point = compute_real(tmin);
                QPointF pixel;
                pixel.setX(point.x() * scale + this->rect().center().x());
                pixel.setY(point.y() * scale + this->rect().center().y());



                painter.drawLine(iPixel, pixel);
                iPixel = pixel;


            }
        }
        else if (Model == mode::ResistorShunt)
        {
            float t;
            float x = get<0>(points[index - 1]).x;
            float y = get<0>(points[index - 1]).y;
            double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
            double xCenter = 1 - circleRadius;
            double dx = x - xCenter;
            double dy = y;
            float sin_t = dy;
            float cos_t = dx;
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
                tmax = 2 * M_PI;
            }
            else
            {
                r = abs(r) * (-1);
                tmax = t;
                tmin = M_PI;
            }
            step = intervalLength / stepCount;
            iPoint = compute_imaginary(tmin);
            iPixel.setX
            (iPoint.x() * scale + center.x());
            iPixel.setY(-iPoint.y() * scale + center.y());
            bool flagi = false;
            for (tmin; tmin < tmax; tmin += step) {

                QPointF point = compute_imaginary(tmin);
                QPointF pixel;
                pixel.setX(point.x() * scale + center.x());
                pixel.setY(-point.y() * scale + center.y());


                if (pow(point.x(), 2) + pow(point.y(), 2) < 1)
                {
                    painter.drawLine(iPixel, pixel);
                }
                iPixel = pixel;
            }
        }
        else if (Model == mode::InductionParallel || Model == mode::CapacitorParallel)
        {
            float t;
            float x = get<0>(points[index - 1]).x;
            float y = get<0>(points[index - 1]).y;
            double circleRadius = -1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 + 2 * x));
            double xCenter = -1 - circleRadius;
            double dx = x - xCenter;
            double dy = -y;
            double sin_t = dy;
            double cos_t = dx;
            if (y < 1e-6 && y >= 0)
            {
                if (y == 0 && x == -1)
                {
                    t = -M_PI;
                }
                else if (x == -1)
                {
                    t = M_PI;
                }
                else if (x == 0)
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
            if (x - 1 != 0)
            {
                r = (cos(t) - x) / (x + 1);
            }
            switch (Model)
            {
            case InductionParallel:
            {
                tmax = M_PI;
                tmin = t;
                break;
            }
            case CapacitorParallel:
            {
                tmin = -M_PI;
                tmax = t;
                break;
            }
            }
            iPoint = compute_realParallel(tmin);
            iPixel.setX(iPoint.x() * scale + this->rect().center().x());
            iPixel.setY(-iPoint.y() * scale + this->rect().center().y());
            bool flagi = false;
            step = abs(tmax - tmin) / 100;
            for (tmin; tmin < tmax; tmin += step) {

                QPointF point = compute_realParallel(tmin);
                QPointF pixel;
                pixel.setX(point.x() * scale + this->rect().center().x());
                pixel.setY(-point.y() * scale + this->rect().center().y());



                painter.drawLine(iPixel, pixel);
                iPixel = pixel;


            }
        }
        else if (Model == mode::ResistorParallel)
        {
            float t;
            float x = get<0>(points[index - 1]).x;
            float y = get<0>(points[index - 1]).y;
            double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y, 2)) / (-2 * y);
            double yCenter = -circleRadius;
            double dx = x + 1;
            double dy = y - yCenter;
            float sin_t = -dy;
            float cos_t = dx;
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
                t = atan(sin_t / cos_t);
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
                tmax = M_PI / 2;
            }
            else
            {
                tmax = t;
                tmin = -M_PI / 2;
            }
            step = (tmax - tmin) / 100;
            iPoint = compute_imaginaryParallel(tmin);
            iPixel.setX
            (iPoint.x() * scale + center.x());
            iPixel.setY(iPoint.y() * scale + center.y());
            bool flagi = false;
            for (tmin; tmin < tmax; tmin += step) {

                QPointF point = compute_imaginaryParallel(tmin);
                QPointF pixel;
                pixel.setX(point.x() * scale + center.x());
                pixel.setY(point.y() * scale + center.y());


                if (pow(point.x(), 2) + pow(point.y(), 2) < 1) 
                {
                    painter.drawLine(iPixel, pixel);
                }
                iPixel = pixel;
            }
        }

    }
}

void RenderArea::generateCache()
{
    QSize scaledSize = size() * m_scaleFactor;
    QImage image(scaledSize, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);

    QPainter cachePainter(&image);
    cachePainter.setRenderHint(QPainter::Antialiasing, true);
    cachePainter.setRenderHint(QPainter::TextAntialiasing, true);
    cachePainter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    cachePainter.scale(m_scaleFactor, m_scaleFactor); 
    drawStaticObjects(cachePainter);

    m_cache = QPixmap::fromImage(
        image.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
    );

    m_cacheValid = true;
}

void RenderArea::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    if (!m_cacheValid || defaultScale != scale) {
        generateCache();
        defaultScale = scale;
    }
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.drawPixmap(rect(), m_cache);
    painter.drawPixmap(0, 0, m_cache);
    drawDynamicObject(painter);
}

void RenderArea::setCursorPosOnCircle(const QPoint& pos)
{
    cursorPos = pos;
    update();  
}