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
    /*qCircles.append(2);
    float qT;
    float qStep = 2 * M_PI / 2000;
    for (qT = 0; qT < 2 * M_PI; qT += qStep)
    {
        iPoint = compute_real(0);
        iPixel.setX(iPoint.x() * scale + center.y());
        iPixel.setY(iPoint.y() * scale + center.y());

    }*/
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
        iPixel.setX// mBackGroundColor = Qt::green;
        (iPoint.x() * scale + center.x());
        iPixel.setY(-iPoint.y() * scale + center.y());
        bool flagi = false;
        for (float t = step; t < intervalLength; t += step) {

            QPointF point = compute_imaginary(t);
            //if(pow((pow(point.x(),2) + pow(point.y(),2)),0.5) > 1) continue;
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
                )
            {
                painter.setPen(QPen(Qt::red, 2));
                QString s1 = QString::number(r * 50);
                painter.setFont(QFont("Arial", 8));
                painter.drawText(point.x() * scale + center.x(), -point.y() * scale + center.y(), s1);
                painter.setPen(Qt::blue);
                flagi = true;
            }



            painter.setPen(Qt::blue);

            if (pow(point.x(), 2) + pow(point.y(), 2) < 1)      //Restricting the domain of Smith Chart
            {
                painter.drawLine(iPixel, pixel);
            }
            iPixel = pixel;
            //painter.drawPoint(pixel);
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
                painter.setPen(QPen(Qt::red, 2));
                QString s1 = QString::number(r * 50);
                painter.setFont(QFont("Arial", 8));
                painter.drawText(point.x() * scale + center.x(), center.y(), s1);
                painter.setPen(Qt::blue);
                flagi == true;
            }



            painter.drawLine(iPixel, pixel);
            iPixel = pixel;

            //painter.drawPoint(pixel);

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
        iPixel.setX// mBackGroundColor = Qt::green;
        (-iPoint.x() * scale + center.x());
        iPixel.setY(-iPoint.y() * scale + center.y());
        bool flagi = false;
        for (float t = step; t < intervalLength; t += step) {

            QPointF point = compute_imaginary(t);
            //if(pow((pow(point.x(),2) + pow(point.y(),2)),0.5) > 1) continue;
            QPointF pixel;
            pixel.setX(-point.x() * scale + center.x());
            pixel.setY(-point.y() * scale + center.y());

            if ((abs(pow(point.x(), 2) + pow(point.y(), 2) - 1) < 0.012) &&
                ((abs(pow(point.x(), 2) + pow(point.y(), 2) - 1) > 0.005)) &&
                flagi == false &&
                (
                    (point.y() * scale + center.y() > iPixel.y() + 1) ||
                    (point.y() * scale + center.y() < iPixel.y() - 1)
                    )
                )
            {
                painter.setPen(QPen(Qt::green, 2));
                QString s1 = QString::number(r * 50);
                painter.setFont(QFont("Arial", 8));
                painter.drawText(-point.x() * scale + center.x() + 10, -point.y() * scale + center.y() - 10, s1);
                painter.setPen(Qt::red);
                flagi = true;
            }



            painter.setPen(Qt::red);

            if (pow(point.x(), 2) + pow(point.y(), 2) < 1)      //Restricting the domain of Smith Chart
            {
                painter.drawLine(iPixel, pixel);
            }
            iPixel = pixel;
            //painter.drawPoint(pixel);
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
                QString s1 = QString::number(r * 50);
                painter.setFont(QFont("Arial", 8));
                painter.drawText(-point.x() * scale + center.x(), center.y() + 10, s1);
                painter.setPen(Qt::red);
                flagi == true;
            }



            painter.drawLine(iPixel, pixel);
            iPixel = pixel;

            //painter.drawPoint(pixel);

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
        painter.drawEllipse(get<0>(points[ii]), 5, 5);
    }
    painter.setPen(QPen(Qt::magenta, 2));
    for (int ll = 0; ll < index - 1; ll++)
    {
        if (get<3>(points[ll + 1]) == mode::InductionShunt)
        {
            r = get<1>(points[ll + 1]);
            float x = get<0>(points[ll]).x();
            float y = get<0>(points[ll]).y();
            x = (x - this->rect().center().x()) / 300;
            y = (y - this->rect().center().y()) / 300;
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

                //painter.drawPoint(pixel);

            }
        }
        else if (get<3>(points[ll + 1]) == mode::CapacitorShunt)
        {
            r = get<1>(points[ll + 1]);
            float x = get<0>(points[ll]).x();
            float y = get<0>(points[ll]).y();
            x = (x - this->rect().center().x()) / 300;
            y = (y - this->rect().center().y()) / 300;
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
            iPoint = compute_real(t);
            iPixel.setX(iPoint.x() * scale + this->rect().center().x());
            iPixel.setY(iPoint.y() * scale + this->rect().center().y());
            bool flagi = false;
            step = abs(t2 - t) / 100;
            for (t; t > t2; t -= step) {

                QPointF point = compute_real(t);
                QPointF pixel;
                pixel.setX(point.x() * scale + center.x());
                pixel.setY(point.y() * scale + center.y());




                painter.drawLine(iPixel, pixel);
                iPixel = pixel;

                //painter.drawPoint(pixel);

            }
        }
        else if (get<3>(points[ll + 1]) == mode::ResistorShunt)
        {
            r = get<1>(points[ll + 1]);
            float t2 = get<2>(points[ll + 1]);
            float t;
            float x = get<0>(points[ll]).x();
            float y = get<0>(points[ll]).y();
            x = (x - this->rect().center().x()) / 300;
            y = (y - this->rect().center().y()) / 300;
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
                //if(pow((pow(point.x(),2) + pow(point.y(),2)),0.5) > 1) continue;
                QPointF pixel;
                pixel.setX(point.x() * scale + center.x());
                pixel.setY(-point.y() * scale + center.y());
                painter.drawLine(iPixel, pixel);
                iPixel = pixel;

            }
        }
        else if (get<3>(points[ll + 1]) == mode::InductionParallel)
        {
            r = get<1>(points[ll + 1]);
            float x = get<0>(points[ll]).x();
            float y = get<0>(points[ll]).y();
            x = (x - this->rect().center().x()) / 300;
            y = (y - this->rect().center().y()) / 300;
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
            float t2 = get<2>(points[ll + 1]);
            iPoint = compute_realParallel(t);
            iPixel.setX(iPoint.x() * scale + this->rect().center().x());
            iPixel.setY(-iPoint.y() * scale + this->rect().center().y());
            bool flagi = false;
            step = abs(t2 - t) / 100;
            for (t; t < t2; t += step) {

                QPointF point = compute_realParallel(t);
                QPointF pixel;

                pixel.setX(point.x() * scale + center.x());
                pixel.setY(-point.y() * scale + center.y());




                painter.drawLine(iPixel, pixel);
                iPixel = pixel;

                //painter.drawPoint(pixel);

            }
        }
        else if (get<3>(points[ll + 1]) == mode::CapacitorParallel)
        {
            r = get<1>(points[ll + 1]);
            float x = get<0>(points[ll]).x();
            float y = get<0>(points[ll]).y();
            x = (x - this->rect().center().x()) / 300;
            y = (y - this->rect().center().y()) / 300;
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
            float t2 = get<2>(points[ll + 1]);
            iPoint = compute_realParallel(t);
            iPixel.setX(iPoint.x() * scale + this->rect().center().x());
            iPixel.setY(-iPoint.y() * scale + this->rect().center().y());
            bool flagi = false;
            step = abs(t2 - t) / 100;
            for (t; t > t2; t -= step) {

                QPointF point = compute_realParallel(t);
                QPointF pixel;
                pixel.setX(point.x() * scale + center.x());
                pixel.setY(-point.y() * scale + center.y());




                painter.drawLine(iPixel, pixel);
                iPixel = pixel;

                //painter.drawPoint(pixel);

            }
        }
        else if (get<3>(points[ll + 1]) == mode::ResistorParallel)
        {
            r = get<1>(points[ll + 1]);
            float t2 = get<2>(points[ll + 1]);
            float t;
            float x = get<0>(points[ll]).x();
            float y = get<0>(points[ll]).y();
            x = (x - this->rect().center().x()) / 300;
            y = (y - this->rect().center().y()) / 300;
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
                //if(pow((pow(point.x(),2) + pow(point.y(),2)),0.5) > 1) continue;
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
        painter.drawEllipse(morePoints[jj], 5, 5);
    }
    if (index > 0 && Model != mode::AddPoint)
    {
        painter.setPen(QPen(Qt::green, 2));
        float tmax, tmin;
        if (Model == mode::InductionShunt)
        {
            float t;
            float x = get<0>(points[index - 1]).x();
            float y = get<0>(points[index - 1]).y();
            x = (x - this->rect().center().x()) / 300;
            y = (y - this->rect().center().y()) / 300;
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
            tmax = 2 * M_PI;
            tmin = t;
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

                //painter.drawPoint(pixel);

            }
        }
        else if (Model == mode::CapacitorShunt)
        {
            float t;
            float x = get<0>(points[index - 1]).x();
            float y = get<0>(points[index - 1]).y();
            x = (x - this->rect().center().x()) / 300;
            y = (y - this->rect().center().y()) / 300;
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
            tmax = t;
            tmin = 0;
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

                //painter.drawPoint(pixel);

            }
        }
        else if (Model == mode::ResistorShunt)
        {
            float t;
            float x = get<0>(points[index - 1]).x();
            float y = get<0>(points[index - 1]).y();
            x = (x - this->rect().center().x()) / 300;
            y = (y - this->rect().center().y()) / 300;
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
            iPixel.setX// mBackGroundColor = Qt::green;
            (iPoint.x() * scale + center.x());
            iPixel.setY(-iPoint.y() * scale + center.y());
            bool flagi = false;
            for (tmin; tmin < tmax; tmin += step) {

                QPointF point = compute_imaginary(tmin);
                //if(pow((pow(point.x(),2) + pow(point.y(),2)),0.5) > 1) continue;
                QPointF pixel;
                pixel.setX(point.x() * scale + center.x());
                pixel.setY(-point.y() * scale + center.y());


                if (pow(point.x(), 2) + pow(point.y(), 2) < 1)      //Restricting the domain of Smith Chart
                {
                    painter.drawLine(iPixel, pixel);
                }
                iPixel = pixel;
                //painter.drawPoint(pixel);
            }
        }
        else if (Model == mode::InductionParallel)
        {
            float t;
            float x = get<0>(points[index - 1]).x();
            float y = get<0>(points[index - 1]).y();
            x = (x - this->rect().center().x()) / 300;
            y = (y - this->rect().center().y()) / 300;
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
            tmax = M_PI;
            tmin = t;
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

                //painter.drawPoint(pixel);

            }
        }
        else if (Model == mode::CapacitorParallel)
        {
            float t;
            float x = get<0>(points[index - 1]).x();
            float y = get<0>(points[index - 1]).y();
            x = (x - this->rect().center().x()) / 300;
            y = (y - this->rect().center().y()) / 300;
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
            tmax = t;
            tmin = -M_PI;
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

                //painter.drawPoint(pixel);

            }
        }
        else if (Model == mode::ResistorParallel)
        {
            float t;
            float x = get<0>(points[index - 1]).x();
            float y = get<0>(points[index - 1]).y();
            x = (x - this->rect().center().x()) / 300;
            y = (y - this->rect().center().y()) / 300;
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
            iPixel.setX// mBackGroundColor = Qt::green;
            (iPoint.x() * scale + center.x());
            iPixel.setY(iPoint.y() * scale + center.y());
            bool flagi = false;
            for (tmin; tmin < tmax; tmin += step) {

                QPointF point = compute_imaginaryParallel(tmin);
                //if(pow((pow(point.x(),2) + pow(point.y(),2)),0.5) > 1) continue;
                QPointF pixel;
                pixel.setX(point.x() * scale + center.x());
                pixel.setY(point.y() * scale + center.y());


                if (pow(point.x(), 2) + pow(point.y(), 2) < 1)      //Restricting the domain of Smith Chart
                {
                    painter.drawLine(iPixel, pixel);
                }
                iPixel = pixel;
                //painter.drawPoint(pixel);
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

    cachePainter.scale(m_scaleFactor, m_scaleFactor); // масштабируем систему координат
    drawStaticObjects(cachePainter);

    m_cache = QPixmap::fromImage(
        image.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
    );

    m_cacheValid = true;
}

void RenderArea::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    if (!m_cacheValid) {
        generateCache();
    }
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.drawPixmap(rect(), m_cache);
    painter.drawPixmap(0, 0, m_cache);
    drawDynamicObject(painter);
   /* painter.setRenderHint(QPainter::Antialiasing, true);
    
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
    switch (mMode) {

    case Superimpose:
    {
        for (RenderArea::r = -2; RenderArea::r <= 2; RenderArea::r += 0.2) {

            iPoint = compute_imaginary(0);
            iPixel.setX// mBackGroundColor = Qt::green;
            (-iPoint.x() * scale + center.x());
            iPixel.setY(iPoint.y() * scale + center.y());

            for (float t = step; t < intervalLength; t += step) {

                QPointF point = compute_imaginary(t);
                //if(pow((pow(point.x(),2) + pow(point.y(),2)),0.5) > 1) continue;
                QPointF pixel;
                pixel.setX(-point.x() * scale + center.x());
                pixel.setY(point.y() * scale + center.y());

                painter.setPen(Qt::red);
                if (pow(point.x(), 2) + pow(point.y(), 2) < 1)      //Restricting the domain of Smith Chart
                {
                    painter.drawLine(iPixel, pixel);
                }
                iPixel = pixel;
                //painter.drawPoint(pixel);
            }
        }
        for (RenderArea::r = 0; RenderArea::r < 10; RenderArea::r += 0.25) {

            iPoint = compute_real(0);
            iPixel.setX(-iPoint.x() * scale + center.x());
            iPixel.setY(iPoint.y() * scale + center.y());

            for (float t = 0; t < intervalLength; t += step) {

                QPointF point = compute_real(t);
                QPointF pixel;
                pixel.setX(-point.x() * scale + center.x());
                pixel.setY(point.y() * scale + center.y());
                painter.drawLine(iPixel, pixel);
                iPixel = pixel;

                //painter.drawPoint(pixel);

            }
        }

        double k = 0.333333333333;
        for (RenderArea::r = -2; RenderArea::r <= 2.1; RenderArea::r += 0.2) {

            iPoint = compute_imaginary(0);
            iPixel.setX// mBackGroundColor = Qt::green;
            (iPoint.x() * scale + center.x());
            iPixel.setY(-iPoint.y() * scale + center.y());
            bool flagi = false;
            for (float t = step; t < intervalLength; t += step) {

                QPointF point = compute_imaginary(t);
                //if(pow((pow(point.x(),2) + pow(point.y(),2)),0.5) > 1) continue;
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
                    )
                {
                    painter.setPen(QPen(Qt::blue, 2));
                    QString s1 = QString::number(r);
                    painter.setFont(QFont("Arial", 8));
                    painter.drawText(point.x() * scale + center.x(), -point.y() * scale + center.y(), s1);
                    painter.setPen(Qt::blue);
                    flagi = true;
                }



                painter.setPen(Qt::blue);
                if (pow(point.x(), 2) + pow(point.y(), 2) < 1)      //Restricting the domain of Smith Chart
                {
                    painter.drawLine(iPixel, pixel);
                }
                iPixel = pixel;
                //painter.drawPoint(pixel);
            }
        }
        for (RenderArea::r = 0; RenderArea::r < 7; RenderArea::r += k) {

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
                    painter.setPen(QPen(Qt::blue, 2));
                    QString s1 = QString::number(r);
                    painter.setFont(QFont("Arial", 8));
                    painter.drawText(point.x() * scale + center.x(), center.y(), s1);
                    painter.setPen(Qt::blue);
                    flagi == true;
                }



                painter.drawLine(iPixel, pixel);
                iPixel = pixel;

                //painter.drawPoint(pixel);

            }
            if (r > 0.99 && r < 1.1)
            {
                k = 0.75;
            }
            else if (r > 0.99)
            {
                k *= 2;
            }
        }

        break;
    }
    case Admittance:
        for (RenderArea::r = -2; RenderArea::r <= 2; RenderArea::r += 0.2) {

            iPoint = compute_imaginary(0);
            iPixel.setX// mBackGroundColor = Qt::green;
            (-iPoint.x() * scale + center.x());
            iPixel.setY(iPoint.y() * scale + center.y());

            for (float t = step; t < intervalLength; t += step) {

                QPointF point = compute_imaginary(t);
                //if(pow((pow(point.x(),2) + pow(point.y(),2)),0.5) > 1) continue;
                QPointF pixel;
                pixel.setX(-point.x() * scale + center.x());
                pixel.setY(point.y() * scale + center.y());

                painter.setPen(Qt::blue);
                if (pow(point.x(), 2) + pow(point.y(), 2) < 1)      //Restricting the domain of Smith Chart
                {
                    painter.drawLine(iPixel, pixel);
                }
                iPixel = pixel;
                //painter.drawPoint(pixel);
            }
        }
        for (RenderArea::r = 0; RenderArea::r < 10; RenderArea::r += 0.5) {
            bool flagi = false;
            iPoint = compute_real(0);
            iPixel.setX(-iPoint.x() * scale + center.x());
            iPixel.setY(iPoint.y() * scale + center.y());

            for (float t = 0; t < intervalLength; t += step) {

                QPointF point = compute_real(t);
                QPointF pixel;
                pixel.setX(-point.x() * scale + center.x());
                pixel.setY(point.y() * scale + center.y());
                if ((floor(point.y() * scale) == 0.0) && (pixel.y() < iPixel.y()) && flagi == false)
                {
                    painter.setPen(QPen(Qt::red, 2));
                    QString s1 = QString::number(r);
                    painter.setFont(QFont("Arial", 8));
                    painter.drawText(-point.x() * scale + center.x(), center.y(), s1);
                    painter.setPen(Qt::blue);
                    flagi == true;
                }
                painter.drawLine(iPixel, pixel);
                iPixel = pixel;

                //painter.drawPoint(pixel);

            }
        }

        break;

    case Impedence:
    {
        /*double m = 0;
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
            iPixel.setX// mBackGroundColor = Qt::green;
            (iPoint.x() * scale + center.x());
            iPixel.setY(-iPoint.y() * scale + center.y());
            bool flagi = false;
            for (float t = step; t<intervalLength; t += step) {
                
                QPointF point = compute_imaginary(t);
                //if(pow((pow(point.x(),2) + pow(point.y(),2)),0.5) > 1) continue;
                QPointF pixel;
                pixel.setX(point.x() * scale + center.x());
                pixel.setY(-point.y() * scale + center.y());

                if ((abs(pow(point.x(), 2) + pow(point.y(), 2) - 1) < 0.012) &&
                    ((abs(pow(point.x(), 2) + pow(point.y(), 2) - 1) > 0.005)) &&
                    flagi == false &&
                    (
                        (point.y() * scale + center.y() > iPixel.y()+1) ||
                        (point.y() * scale + center.y() < iPixel.y() -1)
                    )
                   )
                {
                    painter.setPen(QPen(Qt::red, 2));
                    QString s1 = QString::number(r * 50);
                    painter.setFont(QFont("Arial", 8));
                    painter.drawText(point.x() * scale + center.x(), -point.y() * scale + center.y(), s1);
                    painter.setPen(Qt::blue);
                    flagi = true;
                }



                painter.setPen(Qt::blue);

                if (pow(point.x(), 2) + pow(point.y(), 2) < 1)      //Restricting the domain of Smith Chart
                {
                    painter.drawLine(iPixel, pixel);
                }
                iPixel = pixel;
                //painter.drawPoint(pixel);
            }
            if (m < 0 && m<-0.25)
            {
                m/= 2;
            }
            else if (m > 0)
            {
                m *= 2;
            }
            else if (m<0)
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
                    painter.setPen(QPen(Qt::red, 2));
                    QString s1 = QString::number(r * 50);
                    painter.setFont(QFont("Arial", 8));
                    painter.drawText(point.x() * scale + center.x(), center.y(), s1);
                    painter.setPen(Qt::blue);
                    flagi == true;
                }



                painter.drawLine(iPixel, pixel);
                iPixel = pixel;

                //painter.drawPoint(pixel);

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
            iPixel.setX// mBackGroundColor = Qt::green;
            (-iPoint.x() * scale + center.x());
            iPixel.setY(-iPoint.y() * scale + center.y());
            bool flagi = false;
            for (float t = step; t < intervalLength; t += step) {

                QPointF point = compute_imaginary(t);
                //if(pow((pow(point.x(),2) + pow(point.y(),2)),0.5) > 1) continue;
                QPointF pixel;
                pixel.setX(-point.x() * scale + center.x());
                pixel.setY(-point.y() * scale + center.y());

                if ((abs(pow(point.x(), 2) + pow(point.y(), 2) - 1) < 0.012) &&
                    ((abs(pow(point.x(), 2) + pow(point.y(), 2) - 1) > 0.005)) &&
                    flagi == false &&
                    (
                        (point.y() * scale + center.y() > iPixel.y() + 1) ||
                        (point.y() * scale + center.y() < iPixel.y() - 1)
                        )
                    )
                {
                    painter.setPen(QPen(Qt::green, 2));
                    QString s1 = QString::number(r * 50);
                    painter.setFont(QFont("Arial", 8));
                    painter.drawText(-point.x() * scale + center.x()+10, -point.y() * scale + center.y()-10, s1);
                    painter.setPen(Qt::red);
                    flagi = true;
                }



                painter.setPen(Qt::red);

                if (pow(point.x(), 2) + pow(point.y(), 2) < 1)      //Restricting the domain of Smith Chart
                {
                    painter.drawLine(iPixel, pixel);
                }
                iPixel = pixel;
                //painter.drawPoint(pixel);
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
                    QString s1 = QString::number(r*50);
                    painter.setFont(QFont("Arial", 8));
                    painter.drawText(-point.x() * scale + center.x(), center.y()+10, s1);
                    painter.setPen(Qt::red);
                    flagi == true;
                }



                painter.drawLine(iPixel, pixel);
                iPixel = pixel;

                //painter.drawPoint(pixel);

            }
            k *= 2;
            r = k;
        }
        break;
    }
    case Hide:
        break;

    }*/
    // курсор (точка)
    

    /*for (int i = 0; i < 5; i++) {

        if (flag[i]) {

            painter.setPen(QPen(Qt::red, 5));
            QVector<QPointF> pixel_array(4);


            double x = points[i].x();
            double y = points[i].y();
            if (x == -1 && y == 0) continue;
            pixel_array[i].setX((((x - 1) * (x + 1) + pow(y, 2)) / ((pow(x + 1, 2) + pow(y, 2)))) * scale + center.x());
            pixel_array[i].setY(-((2 * y) / ((pow(x + 1, 2) + pow(y, 2)))) * scale + center.y());
            painter.drawPoint(pixel_array[i]);


        }
    }

    if (flag[4]) {
        painter.setPen(QPen(Qt::green, 5));
        if (!flag[5]) {
            X1L = pow((Rs * Rp - Rp * Rp), 2);      //tuning
            X2L = Rs * Rp / X1L;
        }//tuning
        if (Rs + X2L != 0) {
            Zin = (Rs * X2L / (Rs + X2L)) + X1L;   //plot Zin and Rp
            L_l = X1L / (2 * M_PI * f) * pow(10, 6);      //display and tuning
            C_l = 1 / (X2L * 2 * M_PI * f) * pow(10, 9); //display and tuning
            painter.drawPoint(QPointF(((Zin - 1) / (Zin + 1)) * scale + center.x(), center.y()));
            painter.drawPoint(QPointF(((Rp - 1) / (Rp + 1)) * scale + center.x(), center.y()));
        }

    }

    if (flag[6] && flag[7]) {

        painter.setPen(QPen(Qt::red, 5));
        double x = impedence_admittance(Zin2.x(), Zin2.y()).x();
        double y = impedence_admittance(Zin2.x(), Zin2.y()).y();
        // TODO: create a function to convert Impedence to Admittance
        Yin.setX(x);
        Yin.setY(y);
        painter.drawPoint(Y_to_Gamma(x, y));
        // TODO: create a function to convert Admittance to Gamma values and replace the above expression inside QPointF

        double a = Yin.x() / 50;
        double b = Yin.y() / 50;

        L = pow(((50 - (2500 * a)) / (a * w * w)), 0.5);
        C = (1 / w) * (((w * L) / (2500 + w * w * L * L)) + b);

    }

    if (flag[8] && (flag[7] && flag[6])) {

        painter.setPen(QPen(Qt::green, 5));
        double x = impedence_admittance(Ztemp.x(), Ztemp.y()).x();
        double y;
        if (flag[10]) y = Ytemp.y();
        else y = impedence_admittance(Ztemp.x(), Ztemp.y()).y();
        Ytemp.setX(x);
        painter.drawPoint(Y_to_Gamma(x, y));
    }

    if (flag[12]) {

        if (!flag[11]) Lin = 0;
        for (; Lin <= L; Lin += (L / 100)) {

            double x = 1;
            double y = (w * Lin) / 50;
            painter.setPen(QPen(Qt::black, 2));
            painter.drawPoint(Z_to_Gamma(x, y));

        }
        if (!flag[10]) Cin = 0;

        for (; Cin <= C; Cin += (C / 100)) {

            painter.setPen(QPen(Qt::black, 2));
            double  x = 2500 / (2500 + w * w * L * L);
            double y = 50 * (((-w * L) / (2500 + w * w * L * L)) + w * Cin);
            painter.drawPoint(Y_to_Gamma(x, y));
        }
    }


    if (flag[13]) {



        if (flag[18]) {
            S1.setX(S1Mag * cos(S1angle));
            S1.setY(S1Mag * sin(S1angle));
            S2.setX(S2Mag * cos(S2angle));
            S2.setY(S2Mag * sin(S2angle));
            S3.setX(S3Mag * cos(S3angle));
            S3.setY(S3Mag * sin(S3angle));
            painter.setPen(QPen(Qt::magenta, 12));
            painter.drawPoint(S1.x() * scale + center.x(), -S1.y() * scale + center.y());
            painter.setPen(QPen(Qt::red, 12));
            painter.drawPoint(S2.x() * scale + center.x(), -S2.y() * scale + center.y());
            painter.setPen(QPen(Qt::green, 12));
            painter.drawPoint(S3.x() * scale + center.x(), -S3.y() * scale + center.y());
        }


        else {
            S1.setX(S1Mag * cos(S1angle));
            S1.setY(S1Mag * sin(S1angle));
            S2.setX(S2Mag * cos(S2angle));
            S2.setY(S2Mag * sin(S2angle));
            S3.setX(S3Mag * cos(S3angle));
            S3.setY(S3Mag * sin(S3angle));
            painter.setPen(QPen(Qt::magenta, 8));
            painter.drawPoint(S1.x() * scale + center.x(), -S1.y() * scale + center.y());
            painter.setPen(QPen(Qt::red, 8));
            painter.drawPoint(S2.x() * scale + center.x(), -S2.y() * scale + center.y());
            painter.setPen(QPen(Qt::green, 8));
            painter.drawPoint(S3.x() * scale + center.x(), -S3.y() * scale + center.y());
        }


        painter.setPen(QPen(Qt::red, 2));

        double initial_y;
        double initial_x;
        double initial_yMin;
        double initial_xMin;
        double initial_yMax;
        double initial_xMax;

        initial_point = QPointF(1, 0);
        initial_pointMin = QPointF(1, 0);
        initial_pointMax = QPointF(1, 0);

        initial_x = initial_point.x();
        initial_y = initial_point.y();
        initial_xMin = initial_pointMin.x();
        initial_yMin = initial_pointMin.y();
        initial_xMax = initial_pointMax.x();
        initial_yMax = initial_pointMax.y();


        for (int i = 0; i <= step_count - 1; i++) {

            initial_x = initial_point.x();
            initial_y = initial_point.y();
            initial_xMin = initial_pointMin.x();
            initial_yMin = initial_pointMin.y();
            initial_xMax = initial_pointMax.x();
            initial_yMax = initial_pointMax.y();


            switch (step_array[i].topology) {

            case Series_Inductance:
            {
                double L = 0;

                for (; L <= step_array[i].Val; L += step_array[i].Val / 10000)
                {

                    initial_point.setY(initial_y + ((w * L) / 50));
                    //  if((i == (step_count-1)) && (L == step_array[i].Val)) painter.setPen(QPen(Qt::green, 10));
                    painter.setPen(QPen(Qt::red, 2));
                    painter.drawPoint(Z_to_Gamma(initial_point.x(), initial_point.y()));

                    initial_pointMin.setY(initial_yMin + ((wMin * L) / 50));
                    //  if((i == (step_count-1)) && (L == step_array[i].Val)) painter.setPen(QPen(Qt::green, 10));
                    painter.setPen(QPen(Qt::green, 2));
                    painter.drawPoint(Z_to_Gamma(initial_pointMin.x(), initial_pointMin.y()));

                    initial_pointMax.setY(initial_yMax + ((wMax * L) / 50));
                    //  if((i == (step_count-1)) && (L == step_array[i].Val)) painter.setPen(QPen(Qt::green, 10));
                    painter.setPen(QPen(Qt::magenta, 2));
                    painter.drawPoint(Z_to_Gamma(initial_pointMax.x(), initial_pointMax.y()));


                }
                painter.setPen(QPen(Qt::red, 2));


                break;
            }

            case Shunt_Capacitance:

            {
                double C = 0;

                initial_point = impedence_admittance(initial_point.x(), initial_point.y());
                initial_y = initial_point.y();
                double firstx = initial_point.x();
                double firsty = initial_point.y();

                initial_pointMin = impedence_admittance(initial_pointMin.x(), initial_pointMin.y());
                initial_yMin = initial_pointMin.y();
                double firstxMin = initial_pointMin.x();
                double firstyMin = initial_pointMin.y();

                initial_pointMax = impedence_admittance(initial_pointMax.x(), initial_pointMax.y());
                initial_yMax = initial_pointMax.y();
                double firstxMax = initial_pointMax.x();
                double firstyMax = initial_pointMax.y();


                for (; C <= step_array[i].Val; C += (step_array[i].Val / 10000)) {

                    initial_point.setY(initial_y + ((w * C) * 50));
                    //      if((i == (step_count-1)) && (C == step_array[i].Val)) painter.setPen(QPen(Qt::green, 10));
                    painter.setPen(QPen(Qt::red, 2));
                    painter.drawPoint(Y_to_Gamma(initial_point.x(), initial_point.y()));
                    painter.drawLine(Y_to_Gamma(firstx, firsty), Y_to_Gamma(initial_point.x(), initial_point.y()));
                    firstx = initial_point.x();
                    firsty = initial_point.y();

                    initial_pointMin.setY(initial_yMin + ((wMin * C) * 50));
                    //      if((i == (step_count-1)) && (C == step_array[i].Val)) painter.setPen(QPen(Qt::green, 10));
                    painter.setPen(QPen(Qt::green, 2));
                    painter.drawPoint(Y_to_Gamma(initial_pointMin.x(), initial_pointMin.y()));
                    painter.drawLine(Y_to_Gamma(firstxMin, firstyMin), Y_to_Gamma(initial_pointMin.x(), initial_pointMin.y()));
                    firstxMin = initial_pointMin.x();
                    firstyMin = initial_pointMin.y();

                    initial_pointMax.setY(initial_yMax + ((wMax * C) * 50));
                    //      if((i == (step_count-1)) && (C == step_array[i].Val)) painter.setPen(QPen(Qt::green, 10));
                    painter.setPen(QPen(Qt::magenta, 2));
                    painter.drawPoint(Y_to_Gamma(initial_pointMax.x(), initial_pointMax.y()));
                    painter.drawLine(Y_to_Gamma(firstxMax, firstyMax), Y_to_Gamma(initial_pointMax.x(), initial_pointMax.y()));
                    firstxMax = initial_pointMax.x();
                    firstyMax = initial_pointMax.y();

                }
                painter.setPen(QPen(Qt::red, 2));

                initial_point = impedence_admittance(initial_point.x(), initial_point.y());
                initial_pointMin = impedence_admittance(initial_pointMin.x(), initial_pointMin.y());
                initial_pointMax = impedence_admittance(initial_pointMax.x(), initial_pointMax.y());


                break;
            }

            //Same AS ABOVE

            case Series_Capacitance:
            {
                double delta = 0;

                for (; delta <= 1 / (50 * wMin * step_array[i].Val); delta += 1 / (50 * wMin * step_array[i].Val) / 100000)
                {

                    initial_pointMin.setY(initial_yMin - (delta));
                    //if((i == (step_count-1)) && (C == step_array[i].Val)) painter.setPen(QPen(Qt::green, 4));
                    painter.setPen(QPen(Qt::green, 2));
                    painter.drawPoint(Z_to_Gamma(initial_pointMin.x(), initial_pointMin.y()));

                }
                delta = 0;

                for (; delta <= 1 / (50 * w * step_array[i].Val); delta += 1 / (50 * w * step_array[i].Val) / 100000)
                {

                    //if(C == 0)
                    //  {
                      //  initial_point.setY(0);
                     //   initial_pointMin.setY(0);
                     //   initial_pointMax.setY(0);
                    //   }
                    //else

                    initial_point.setY(initial_y - (delta));
                    //if((i == (step_count-1)) && (C == step_array[i].Val)) painter.setPen(QPen(Qt::green, 4));
                    painter.setPen(QPen(Qt::red, 2));
                    painter.drawPoint(Z_to_Gamma(initial_point.x(), initial_point.y()));

                    //initial_pointMin.setY( initial_yMin - (50/(wMin*C)));
                   //if((i == (step_count-1)) && (C == step_array[i].Val)) painter.setPen(QPen(Qt::green, 4));
                    //painter.setPen(QPen(Qt::green, 2));
                    //painter.drawPoint(Z_to_Gamma(initial_pointMin.x(), initial_pointMin.y()));

                    //initial_pointMax.setY( initial_yMax - (50/(wMax*C)));
                   //if((i == (step_count-1)) && (C == step_array[i].Val)) painter.setPen(QPen(Qt::green, 4));
                    //painter.setPen(QPen(Qt::magenta, 2));
                    //painter.drawPoint(Z_to_Gamma(initial_pointMax.x(), initial_pointMax.y()));

                }


                delta = 0;
                for (; delta <= 1 / (50 * wMax * step_array[i].Val); delta += 1 / (50 * wMax * step_array[i].Val) / 100000)
                {

                    initial_pointMax.setY(initial_yMax - delta);
                    //if((i == (step_count-1)) && (C == step_array[i].Val)) painter.setPen(QPen(Qt::green, 4));
                    painter.setPen(QPen(Qt::magenta, 2));
                    painter.drawPoint(Z_to_Gamma(initial_pointMax.x(), initial_pointMax.y()));


                }



                painter.setPen(QPen(Qt::red, 2));

                break;
            }

            case Shunt_Inductance:

            {
                double delta = 0;

                initial_point = impedence_admittance(initial_point.x(), initial_point.y());
                initial_y = initial_point.y();

                initial_pointMin = impedence_admittance(initial_pointMin.x(), initial_pointMin.y());
                initial_yMin = initial_pointMin.y();

                initial_pointMax = impedence_admittance(initial_pointMax.x(), initial_pointMax.y());
                initial_yMax = initial_pointMax.y();

                for (; delta <= 50 / (wMin * step_array[i].Val); delta += 50 / (wMin * step_array[i].Val) / 10000) {

                    initial_pointMin.setY(initial_yMin - delta);

                    // if((i == (step_count-1)) && (L == step_array[i].Val)) painter.setPen(QPen(Qt::green, 4));
                    painter.setPen(QPen(Qt::green, 2));
                    painter.drawPoint(Y_to_Gamma(initial_pointMin.x(), initial_pointMin.y()));


                }

                delta = 0;

                for (; delta <= 50 / (w * step_array[i].Val); delta += 50 / (w * step_array[i].Val) / 10000) {

                    //if(L == 0)
                    //{
                      //  initial_point.setY(0);
                        //initial_pointMin.setY(0);
                        //initial_pointMax.setY(0);
                    //}
                    //else

                    initial_point.setY(initial_y - delta);

                    // if((i == (step_count-1)) && (L == step_array[i].Val)) painter.setPen(QPen(Qt::green, 4));
                    painter.setPen(QPen(Qt::red, 2));
                    painter.drawPoint(Y_to_Gamma(initial_point.x(), initial_point.y()));



                }




                delta = 0;
                for (; delta <= 50 / (wMax * step_array[i].Val); delta += 50 / (wMax * step_array[i].Val) / 10000) {

                    initial_pointMax.setY(initial_yMax - delta);

                    // if((i == (step_count-1)) && (L == step_array[i].Val)) painter.setPen(QPen(Qt::green, 4));
                    painter.setPen(QPen(Qt::magenta, 2));
                    painter.drawPoint(Y_to_Gamma(initial_pointMax.x(), initial_pointMax.y()));
                }
                painter.setPen(QPen(Qt::red, 2));
                initial_point = impedence_admittance(initial_point.x(), initial_point.y());
                initial_pointMin = impedence_admittance(initial_pointMin.x(), initial_pointMin.y());
                initial_pointMax = impedence_admittance(initial_pointMax.x(), initial_pointMax.y());

                break;
            }
            }


        }
        flag[18] = false;
    }

    if (flag[19]) {

        if (flag[18]) {
            S1.setX(S1Mag * cos(S1angle));
            S1.setY(S1Mag * sin(S1angle));
            S2.setX(S2Mag * cos(S2angle));
            S2.setY(S2Mag * sin(S2angle));
            S3.setX(S3Mag * cos(S3angle));
            S3.setY(S3Mag * sin(S3angle));
            painter.setPen(QPen(Qt::magenta, 12));
            painter.drawPoint(S1.x() * scale + center.x(), -S1.y() * scale + center.y());
            painter.setPen(QPen(Qt::red, 12));
            painter.drawPoint(S2.x() * scale + center.x(), -S2.y() * scale + center.y());
            painter.setPen(QPen(Qt::green, 12));
            painter.drawPoint(S3.x() * scale + center.x(), -S3.y() * scale + center.y());
        }


        else {
            S1.setX(S1Mag * cos(S1angle));
            S1.setY(S1Mag * sin(S1angle));
            S2.setX(S2Mag * cos(S2angle));
            S2.setY(S2Mag * sin(S2angle));
            S3.setX(S3Mag * cos(S3angle));
            S3.setY(S3Mag * sin(S3angle));
            painter.setPen(QPen(Qt::magenta, 8));
            painter.drawPoint(S1.x() * scale + center.x(), -S1.y() * scale + center.y());
            painter.setPen(QPen(Qt::red, 8));
            painter.drawPoint(S2.x() * scale + center.x(), -S2.y() * scale + center.y());
            painter.setPen(QPen(Qt::green, 8));
            painter.drawPoint(S3.x() * scale + center.x(), -S3.y() * scale + center.y());
        }


        painter.setPen(QPen(Qt::red, 2));


        double initial_y;
        double initial_x;
        double initial_yMin;
        double initial_xMin;
        double initial_yMax;
        double initial_xMax;

        initial_point = QPointF(1, 0);
        initial_pointMin = QPointF(1, 0);
        initial_pointMax = QPointF(1, 0);

        initial_x = initial_point.x();
        initial_y = initial_point.y();
        initial_xMin = initial_pointMin.x();
        initial_yMin = initial_pointMin.y();
        initial_xMax = initial_pointMax.x();
        initial_yMax = initial_pointMax.y();


        for (int i = 0; i <= step_count - 1; i++) {

            initial_x = initial_point.x();
            initial_y = initial_point.y();
            initial_xMin = initial_pointMin.x();
            initial_yMin = initial_pointMin.y();
            initial_xMax = initial_pointMax.x();
            initial_yMax = initial_pointMax.y();


            switch (step_array[i].topology) {

            case Series_Inductance:
            {
                double L = 0;

                for (; L <= step_array[i].Val; L += step_array[i].Val / 10000)
                {

                    initial_point.setY(initial_y + ((w * L) / 50));
                    //  if((i == (step_count-1)) && (L == step_array[i].Val)) painter.setPen(QPen(Qt::green, 10));
                    painter.setPen(QPen(Qt::red, 2));
                    painter.drawPoint(Z_to_Gamma(initial_point.x(), initial_point.y()));

                    initial_pointMin.setY(initial_yMin + ((wMin * L) / 50));
                    //  if((i == (step_count-1)) && (L == step_array[i].Val)) painter.setPen(QPen(Qt::green, 10));
                    painter.setPen(QPen(Qt::green, 2));
                    painter.drawPoint(Z_to_Gamma(initial_pointMin.x(), initial_pointMin.y()));

                    initial_pointMax.setY(initial_yMax + ((wMax * L) / 50));
                    //  if((i == (step_count-1)) && (L == step_array[i].Val)) painter.setPen(QPen(Qt::green, 10));
                    painter.setPen(QPen(Qt::magenta, 2));
                    painter.drawPoint(Z_to_Gamma(initial_pointMax.x(), initial_pointMax.y()));


                }
                painter.setPen(QPen(Qt::red, 2));


                break;
            }

            case Shunt_Capacitance:

            {
                double C = 0;

                initial_point = impedence_admittance(initial_point.x(), initial_point.y());
                initial_y = initial_point.y();
                double firstx = initial_point.x();
                double firsty = initial_point.y();

                initial_pointMin = impedence_admittance(initial_pointMin.x(), initial_pointMin.y());
                initial_yMin = initial_pointMin.y();
                double firstxMin = initial_pointMin.x();
                double firstyMin = initial_pointMin.y();


                initial_pointMax = impedence_admittance(initial_pointMax.x(), initial_pointMax.y());
                initial_yMax = initial_pointMax.y();
                double firstxMax = initial_pointMax.x();
                double firstyMax = initial_pointMax.y();



                for (; C <= step_array[i].Val; C += (step_array[i].Val / 100000)) {

                    initial_point.setY(initial_y + ((w * C) * 50));
                    //      if((i == (step_count-1)) && (C == step_array[i].Val)) painter.setPen(QPen(Qt::green, 10));
                    painter.setPen(QPen(Qt::red, 2));
                    painter.drawPoint(Y_to_Gamma(initial_point.x(), initial_point.y()));
                    painter.drawLine(Y_to_Gamma(firstx, firsty), Y_to_Gamma(initial_point.x(), initial_point.y()));
                    firstx = initial_point.x();
                    firsty = initial_point.y();

                    initial_pointMin.setY(initial_yMin + ((wMin * C) * 50));
                    //      if((i == (step_count-1)) && (C == step_array[i].Val)) painter.setPen(QPen(Qt::green, 10));
                    painter.setPen(QPen(Qt::green, 2));
                    painter.drawPoint(Y_to_Gamma(initial_pointMin.x(), initial_pointMin.y()));
                    painter.drawLine(Y_to_Gamma(firstxMin, firstyMin), Y_to_Gamma(initial_pointMin.x(), initial_pointMin.y()));
                    firstxMin = initial_pointMin.x();
                    firstyMin = initial_pointMin.y();

                    initial_pointMax.setY(initial_yMax + ((wMax * C) * 50));
                    //      if((i == (step_count-1)) && (C == step_array[i].Val)) painter.setPen(QPen(Qt::green, 10));
                    painter.setPen(QPen(Qt::magenta, 2));
                    painter.drawPoint(Y_to_Gamma(initial_pointMax.x(), initial_pointMax.y()));
                    firstxMax = initial_pointMax.x();
                    firstyMax = initial_pointMax.y();


                }
                painter.setPen(QPen(Qt::red, 2));

                initial_point = impedence_admittance(initial_point.x(), initial_point.y());
                initial_pointMin = impedence_admittance(initial_pointMin.x(), initial_pointMin.y());
                initial_pointMax = impedence_admittance(initial_pointMax.x(), initial_pointMax.y());


                break;
            }

            //Same AS ABOVE

            case Series_Capacitance:
            {
                double delta = 0;


                for (; delta <= 1 / (50 * w * step_array[i].Val); delta += 1 / (50 * w * step_array[i].Val) / 100000)
                {

                    //if(C == 0)
                    //{
                      //  initial_point.setY(0);
                        //initial_pointMin.setY(0);
                        //initial_pointMax.setY(0);
                    //}
                    //else

                    initial_point.setY(initial_y - delta);
                    //if((i == (step_count-1)) && (C == step_array[i].Val)) painter.setPen(QPen(Qt::green, 4));
                    painter.setPen(QPen(Qt::red, 2));
                    painter.drawPoint(Z_to_Gamma(initial_point.x(), initial_point.y()));



                }

                delta = 0;


                for (; delta <= 1 / (50 * wMin * step_array[i].Val); delta += 1 / (50 * wMin * step_array[i].Val) / 100000)
                {

                    initial_pointMin.setY(initial_yMin - delta);
                    //if((i == (step_count-1)) && (C == step_array[i].Val)) painter.setPen(QPen(Qt::green, 4));
                    painter.setPen(QPen(Qt::green, 2));
                    painter.drawPoint(Z_to_Gamma(initial_pointMin.x(), initial_pointMin.y()));

                }

                delta = 0;


                for (; delta <= 1 / (50 * wMax * step_array[i].Val); delta += 1 / (50 * wMax * step_array[i].Val) / 100000)
                {

                    initial_pointMax.setY(initial_yMax - delta);
                    //if((i == (step_count-1)) && (C == step_array[i].Val)) painter.setPen(QPen(Qt::green, 4));
                    painter.setPen(QPen(Qt::magenta, 2));
                    painter.drawPoint(Z_to_Gamma(initial_pointMax.x(), initial_pointMax.y()));

                }

                painter.setPen(QPen(Qt::red, 2));

                break;
            }

            case Shunt_Inductance:

            {
                double delta = 0;

                initial_point = impedence_admittance(initial_point.x(), initial_point.y());
                initial_y = initial_point.y();

                initial_pointMin = impedence_admittance(initial_pointMin.x(), initial_pointMin.y());
                initial_yMin = initial_pointMin.y();

                initial_pointMax = impedence_admittance(initial_pointMax.x(), initial_pointMax.y());
                initial_yMax = initial_pointMax.y();

                for (; delta <= 50 / (wMin * step_array[i].Val); delta += 50 / (wMin * step_array[i].Val) / 10000) {

                    initial_pointMin.setY(initial_yMin - delta);

                    // if((i == (step_count-1)) && (L == step_array[i].Val)) painter.setPen(QPen(Qt::green, 4));
                    painter.setPen(QPen(Qt::green, 2));
                    painter.drawPoint(Y_to_Gamma(initial_pointMin.x(), initial_pointMin.y()));

                }
                delta = 0;

                for (; delta <= 50 / (w * step_array[i].Val); delta += 50 / (w * step_array[i].Val) / 10000) {

                    //if(L == 0)
                    //{
                      //  initial_point.setY(0);
                       // initial_pointMin.setY(0);
                       // initial_pointMax.setY(0);
                    //}
                    //else

                    initial_point.setY(initial_y - delta);

                    // if((i == (step_count-1)) && (L == step_array[i].Val)) painter.setPen(QPen(Qt::green, 4));
                    painter.setPen(QPen(Qt::red, 2));
                    painter.drawPoint(Y_to_Gamma(initial_point.x(), initial_point.y()));

                }



                delta = 0;
                for (; delta <= 50 / (wMax * step_array[i].Val); delta += 50 / (wMax * step_array[i].Val) / 10000) {

                    initial_pointMax.setY(initial_yMax - delta);

                    // if((i == (step_count-1)) && (L == step_array[i].Val)) painter.setPen(QPen(Qt::green, 4));
                    painter.setPen(QPen(Qt::magenta, 2));
                    painter.drawPoint(Y_to_Gamma(initial_pointMax.x(), initial_pointMax.y()));


                }



                painter.setPen(QPen(Qt::red, 2));
                initial_point = impedence_admittance(initial_point.x(), initial_point.y());
                initial_pointMin = impedence_admittance(initial_pointMin.x(), initial_pointMin.y());
                initial_pointMax = impedence_admittance(initial_pointMax.x(), initial_pointMax.y());

                break;
            }
            }


        }
        flag[18] = false;



    }*/



}

void RenderArea::setCursorPosOnCircle(const QPoint& pos)
{
    cursorPos = pos;
    update();  
}