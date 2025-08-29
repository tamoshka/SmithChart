#include <iostream>
#include "renderarea.h"
#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>
#include <QMessageBox>
#include "general.h"
#include <cmath>
#include <QCursor>


RenderArea::RenderArea(QWidget* parent, CircuitElements* newElements) :
    QWidget(parent),
    mBackGroundColor(255, 255, 255),
    mShapeColor(0, 0, 0),
    mMode(Impedence)
{
    m_cacheValid = false;
    m_scaleFactor = 2.0;
    circuitElements = newElements;
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 100);
}

Point RenderArea::compute_real(double t)
{
    double cos_t = cos(t);
    double sin_t = sin(t);
    double x = (r / (1 + r)) + (1 / (r + 1)) * cos_t;
    double y = (1 / (r + 1)) * sin_t;

    Point tmp;
    tmp.x = x;
    tmp.y = y;
    return tmp;

}
Point RenderArea::compute_realParallel(double t)
{
    double cos_t = cos(t);
    double sin_t = sin(t);
    double x = (cos(t) - r) / (r + 1);
    double y = (1 / (r + 1)) * sin_t;


    Point tmp;
    tmp.x = x;
    tmp.y = y;
    return tmp;

}

Point RenderArea::compute_imaginary(double t)
{
    double cos_t = cos(t);
    double sin_t = sin(t);
    double x = 1 + (1 / r) * cos_t;
    double y = (1 / r) + (1 / r) * sin_t;
    
    Point tmp;
    tmp.x = x;
    tmp.y = y;
    return tmp;

}

Point RenderArea::compute_imaginaryParallel(double t)
{
    double cos_t = cos(t);
    double sin_t = sin(t);
    double x;
    double y;
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

    Point tmp;
    tmp.x = x;
    tmp.y = y;
    return tmp;
}

void RenderArea::drawStaticObjects(QPainter& painter)
{
    center = this->rect().center();
    painter.setBrush(SystemParameters::BackgroundColor);
    painter.setPen(QPen((mShapeColor, 20)));
    painter.drawRect(this->rect());
    painter.drawLine(QPointF(center.x(), -1000 + center.y()), QPointF(center.x(), 1000 + center.y()));
    painter.drawLine(QPointF(-1000 + center.x(), center.y()), QPointF(1000 + center.x(), center.y()));
    painter.setPen(mShapeColor);
    painter.setPen(SystemParameters::ImpedanceColor);
    double intervalLength = 2 * M_PI;
    int stepCount = 2000;
    double step;
    Point iPoint;
    QPointF iPixel;
    step = intervalLength / stepCount;
    painter.setPen(QPen(SystemParameters::ImpedanceColor, SystemParameters::linesWidth[1]));
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
        (iPoint.x * scale + center.x());
        iPixel.setY(-iPoint.y * scale + center.y());
        bool flagi = false;
        for (double t = step; t < intervalLength; t += step) {

            Point point = compute_imaginary(t);
            QPointF pixel;
            pixel.setX(point.x * scale + center.x());
            pixel.setY(-point.y * scale + center.y());

            if ((abs(pow(point.x, 2) + pow(point.y, 2) - 1) < 0.012) &&
                ((abs(pow(point.x, 2) + pow(point.y, 2) - 1) > 0.005)) &&
                flagi == false &&
                (
                    (point.y * scale + center.y() > iPixel.y() + 1) ||
                    (point.y * scale + center.y() < iPixel.y() - 1)
                    )
                && r > 0
                )

            {
                painter.setPen(QPen(SystemParameters::DataPointsColor, SystemParameters::linesWidth[3]));
                QString s1 = QString::number(r * 50);
                painter.setFont(QFont("Arial", 8));
                painter.drawText(point.x * scale + center.x(), -point.y * scale + center.y(), s1);
                painter.setPen(SystemParameters::ImpedanceColor);
                flagi = true;
            }



            painter.setPen(QPen(SystemParameters::ImpedanceColor, SystemParameters::linesWidth[1]));

            if (pow(point.x, 2) + pow(point.y, 2) < 1)
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
        iPixel.setX(iPoint.x * scale + center.x());
        iPixel.setY(-iPoint.y * scale + center.y());
        bool flagi = false;
        for (double t = 0; t < intervalLength; t += step) {

            Point point = compute_real(t);
            QPointF pixel;
            pixel.setX(point.x * scale + center.x());
            pixel.setY(point.y * scale + center.y());

            if ((floor(point.y * scale) == 0.0) && (pixel.y() < iPixel.y()) && flagi == false)
            {
                painter.setPen(QPen(SystemParameters::DataPointsColor, SystemParameters::linesWidth[3]));
                QString s1 = QString::number(r * 50);
                painter.setFont(QFont("Arial", 8));
                painter.drawText(point.x * scale + center.x(), center.y(), s1);
                painter.setPen(SystemParameters::ImpedanceColor);
                flagi == true;
            }
            if (r == 1)
            {
                painter.setPen(QPen(SystemParameters::ImpedanceColor, SystemParameters::linesWidth[1] * 6));
            }
            if (r == 0)
            {
                painter.setPen(QPen(SystemParameters::MainCircleColor, SystemParameters::linesWidth[0]));
            }
            painter.drawLine(iPixel, pixel);
            iPixel = pixel;
            painter.setPen(QPen(SystemParameters::ImpedanceColor, SystemParameters::linesWidth[1]));
        }
        k *= 2;
        r = k;
    }
    painter.setPen(QPen(SystemParameters::AdmitanceColor, SystemParameters::linesWidth[2]));
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
        (-iPoint.x * scale + center.x());
        iPixel.setY(-iPoint.y * scale + center.y());
        bool flagi = false;
        for (double t = step; t < intervalLength; t += step) {

            Point point = compute_imaginary(t);
            QPointF pixel;
            pixel.setX(-point.x * scale + center.x());
            pixel.setY(-point.y * scale + center.y());

            if ((abs(pow(point.x, 2) + pow(point.y, 2) - 1) < 0.012) &&
                ((abs(pow(point.x, 2) + pow(point.y, 2) - 1) > 0.005)) &&
                flagi == false &&
                r < 0 &&
                (
                    (point.y * scale + center.y() > iPixel.y() + 1) ||
                    (point.y * scale + center.y() < iPixel.y() - 1)
                    )
                )
            {
                painter.setPen(QPen(SystemParameters::RootColor, SystemParameters::linesWidth[4]));
                QString s1 = QString::number(r * 1000 / -50);
                painter.setFont(QFont("Arial", 8));
                painter.drawText(-point.x * scale + center.x() + 10, -point.y * scale + center.y() - 10, s1);
                flagi = true;
            }



            painter.setPen(QPen(SystemParameters::AdmitanceColor, SystemParameters::linesWidth[2]));

            if (pow(point.x, 2) + pow(point.y, 2) < 1)
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
        iPixel.setX(-iPoint.x * scale + center.x());
        iPixel.setY(-iPoint.y * scale + center.y());
        bool flagi = false;
        for (double t = 0; t < intervalLength; t += step) {

            Point point = compute_real(t);
            QPointF pixel;
            pixel.setX(-point.x * scale + center.x());
            pixel.setY(point.y * scale + center.y());

            if ((floor(point.y * scale) == 0.0) && (pixel.y() < iPixel.y()) && flagi == false)
            {
                painter.setPen(QPen(SystemParameters::RootColor, SystemParameters::linesWidth[4]));
                QString s1 = QString::number(r * 1000 / 50);
                painter.setFont(QFont("Arial", 8));
                painter.drawText(-point.x * scale + center.x(), center.y() + 10, s1);
                painter.setPen(SystemParameters::AdmitanceColor);
                flagi == true;
            }
            if (r == 1)
            {
                painter.setPen(QPen(SystemParameters::AdmitanceColor, SystemParameters::linesWidth[2] * 6));
            }
            painter.drawLine(iPixel, pixel);
            iPixel = pixel;
            painter.setPen(QPen(SystemParameters::AdmitanceColor, SystemParameters::linesWidth[2]));
        }
        k *= 2;
        r = k;
    }
}

void RenderArea::drawDynamicObject(QPainter& painter)
{
    double intervalLength = 2 * M_PI;
    int stepCount = 2000;
    double step;
    Point iPoint;
    QPointF iPixel;
    step = intervalLength / stepCount;
    painter.setPen(Qt::NoPen);
    painter.setBrush(SystemParameters::DataPointsColor);
    if (Model != Default && Model != AddPoint)
    {
        painter.drawEllipse(cursorPos, 5, 5);
    }
    int i = 0;
    int j = 0;
    for (int ii = 0; ii < allPoints.size(); ii++)
    {
        if (get<1>(allPoints[ii]))
        {
            double x = circuitElements->GetCircuitElements()[i]->GetPoint().x * scale + this->rect().center().x();
            double y = circuitElements->GetCircuitElements()[i]->GetPoint().y * scale + this->rect().center().y();
            QPointF point = QPointF(x, y);
            painter.drawEllipse(point, 5, 5);
            painter.setPen(QPen(SystemParameters::ElementsColor, SystemParameters::linesWidth[5]));
            QString s1 = "TP " + QString::number(ii + 1);
            painter.setFont(QFont("Calibri", 10));
            painter.drawText(x + 10, y + 10, s1);
            painter.setPen(Qt::NoPen);
            i++;
        }
        else
        {
            if (j == 0)
            {
                double x = circuitElements->firstPoint.x * scale + this->rect().center().x();
                double y = circuitElements->firstPoint.y * scale + this->rect().center().y();
                QPointF point = QPointF(x, y);
                painter.drawEllipse(point, 5, 5);
                painter.setPen(QPen(SystemParameters::ElementsColor, SystemParameters::linesWidth[5]));
                QString s1 = "DP " + QString::number(ii + 1);
                painter.setFont(QFont("Calibri", 10));
                painter.drawText(x + 10, y + 10, s1);
                painter.setPen(Qt::NoPen);
                j++;
            }
            else
            {
                double x = morePoints[j-1].x * scale + this->rect().center().x();
                double y = morePoints[j-1].y * scale + this->rect().center().y();
                QPointF point = QPointF(x, y);
                painter.drawEllipse(point, 5, 5);
                painter.setPen(QPen(SystemParameters::ElementsColor, SystemParameters::linesWidth[5]));
                QString s1 = "DP " + QString::number(ii + 1);
                painter.setFont(QFont("Calibri", 10));
                painter.drawText(x + 10, y + 10, s1);
                painter.setPen(Qt::NoPen);
            }
        }
    }
    painter.setPen(QPen(SystemParameters::ElementsColor, SystemParameters::linesWidth[5]));
    for (int ll = 0; ll < index - 1; ll++)
    {
        if (circuitElements->GetCircuitElements()[ll]->GetMode() == mode::InductionShunt || circuitElements->GetCircuitElements()[ll]->GetMode() == mode::CapacitorShunt)
        {
            tuple<double, double> tuple1 = circuitElements->GetCircuitElements()[ll]->GetChartParameters().at(RealImpedance);
            r = get<0>(tuple1);
            double t2 = get<1>(tuple1);
            tuple<double, double> tuple2;
            double t;
            if (ll == 0)
            {
                tuple2 = circuitElements->chart.at(RealImpedance);
                t = get<1>(tuple2);
            }
            else
            {
                tuple2 = circuitElements->GetCircuitElements()[ll - 1]->GetChartParameters().at(RealImpedance);
                t = get<1>(tuple2);
            }
            if (t2 < t)
            {
                double temp = t;
                t = t2;
                t2 = temp;
            }
            iPoint = compute_real(t);
            iPixel.setX(iPoint.x * scale + this->rect().center().x());
            iPixel.setY(iPoint.y * scale + this->rect().center().y());
            bool flagi = false;
            step = abs(t2 - t) / 100;
            for (t; t < t2; t += step)
            {
                Point point = compute_real(t);
                QPointF pixel;
                pixel.setX(point.x * scale + center.x());
                pixel.setY(point.y * scale + center.y());
                painter.drawLine(iPixel, pixel);
                iPixel = pixel;
            }
        }
        else if (circuitElements->GetCircuitElements()[ll]->GetMode() == mode::ResistorShunt)
        {
            tuple<double, double> tuple1 = circuitElements->GetCircuitElements()[ll]->GetChartParameters().at(ImagImpedance);
            r = get<0>(tuple1);
            double t2 = get<1>(tuple1);
            tuple<double, double> tuple2;
            double t;
            if (ll == 0)
            {
                tuple2 = circuitElements->chart.at(ImagImpedance);
                t = get<1>(tuple2);
            }
            else
            {
                tuple2 = circuitElements->GetCircuitElements()[ll - 1]->GetChartParameters().at(ImagImpedance);
                t = get<1>(tuple2);
            }
            step = abs(t2 - t) / 100;
            double tmin, tmax;
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
            iPixel.setX(iPoint.x * scale + this->rect().center().x());
            iPixel.setY(-iPoint.y * scale + this->rect().center().y());
            for (tmin = tmin + step; tmin < tmax; tmin += step) {

                Point point = compute_imaginary(tmin);
                QPointF pixel;
                pixel.setX(point.x * scale + center.x());
                pixel.setY(-point.y * scale + center.y());
                if (pow(point.x, 2) + pow(point.y, 2) < 1)
                {
                    painter.drawLine(iPixel, pixel);
                }
                iPixel = pixel;
            }
        }
        else if (circuitElements->GetCircuitElements()[ll]->GetMode() == mode::InductionParallel || circuitElements->GetCircuitElements()[ll]->GetMode() == mode::CapacitorParallel)
        {
            tuple<double, double> tuple1 = circuitElements->GetCircuitElements()[ll]->GetChartParameters().at(RealAdmitance);
            r = get<0>(tuple1);
            double t2 = get<1>(tuple1);
            tuple<double, double> tuple2;
            double t;
            if (ll == 0)
            {
                tuple2 = circuitElements->chart.at(RealAdmitance);
                t = get<1>(tuple2);
            }
            else
            {
                tuple2 = circuitElements->GetCircuitElements()[ll - 1]->GetChartParameters().at(RealAdmitance);
                t = get<1>(tuple2);
            }
            bool flagi = false;
            step = abs(t2 - t) / 100;
            if (t2 < t)
            {
                double temp = t;
                t = t2;
                t2 = temp;
            }
            iPoint = compute_realParallel(t);
            iPixel.setX(iPoint.x * scale + this->rect().center().x());
            iPixel.setY(-iPoint.y * scale + this->rect().center().y());
            for (t; t < t2; t += step)
            {
                Point point = compute_realParallel(t);
                QPointF pixel;
                pixel.setX(point.x * scale + center.x());
                pixel.setY(-point.y * scale + center.y());
                painter.drawLine(iPixel, pixel);
                iPixel = pixel;
            }
        }
        else if (circuitElements->GetCircuitElements()[ll]->GetMode() == mode::ResistorParallel)
        {
            tuple<double, double> tuple1 = circuitElements->GetCircuitElements()[ll]->GetChartParameters().at(ImagAdmitance);
            double t2 = get<1>(tuple1);
            tuple<double, double> tuple2;
            double t;
            if (ll == 0)
            {
                tuple2 = circuitElements->chart.at(ImagAdmitance);
                t = get<1>(tuple2);
            }
            else
            {
                tuple2 = circuitElements->GetCircuitElements()[ll - 1]->GetChartParameters().at(ImagAdmitance);
                t = get<1>(tuple2);
            }
            r = get<0>(tuple1);
            step = abs(t2 - t) / 100;
            double tmin, tmax;
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
            iPixel.setX(iPoint.x * scale + this->rect().center().x());
            iPixel.setY(iPoint.y * scale + this->rect().center().y());
            for (tmin = tmin + step; tmin < tmax; tmin += step) {

                Point point = compute_imaginaryParallel(tmin);
                QPointF pixel;
                pixel.setX(point.x * scale + center.x());
                pixel.setY(point.y * scale + center.y());
                if (pow(point.x, 2) + pow(point.y, 2) < 1)
                {
                    painter.drawLine(iPixel, pixel);
                }
                iPixel = pixel;
            }
        }
        else if (circuitElements->GetCircuitElements()[ll]->GetMode() == mode::Line)
        {

        }
        else if (circuitElements->GetCircuitElements()[ll]->GetMode() == mode::OSLine)
        {
            tuple<double, double> tuple1 = circuitElements->GetCircuitElements()[ll]->GetChartParameters().at(RealAdmitance);
            r = get<0>(tuple1);
            double t2 = get<1>(tuple1);
            tuple<double, double> tuple2;
            double t;
            if (ll == 0)
            {
                tuple2 = circuitElements->chart.at(RealAdmitance);
                t = get<1>(tuple2);
            }
            else
            {
                tuple2 = circuitElements->GetCircuitElements()[ll - 1]->GetChartParameters().at(RealAdmitance);
                t = get<1>(tuple2);
            }
            bool flagi = false;
            step = abs(t2 - t) / 100;
            iPoint = compute_realParallel(t);
            iPixel.setX(iPoint.x * scale + this->rect().center().x());
            iPixel.setY(-iPoint.y * scale + this->rect().center().y());
            if (t > t2)
            {
                for (t; t > t2; t -= step)
                {
                    Point point = compute_realParallel(t);
                    QPointF pixel;
                    pixel.setX(point.x * scale + center.x());
                    pixel.setY(-point.y * scale + center.y());
                    painter.drawLine(iPixel, pixel);
                    iPixel = pixel;
                }
            }
            else
            {
                for (t; t > t2-2*M_PI; t -= step)
                {
                    Point point = compute_realParallel(t);
                    QPointF pixel;
                    pixel.setX(point.x * scale + center.x());
                    pixel.setY(-point.y * scale + center.y());
                    painter.drawLine(iPixel, pixel);
                    iPixel = pixel;
                }
            }
        }
        else if (circuitElements->GetCircuitElements()[ll]->GetMode() == mode::SSLine)
        {
            tuple<double, double> tuple1 = circuitElements->GetCircuitElements()[ll]->GetChartParameters().at(RealAdmitance);
            r = get<0>(tuple1);
            double t2 = get<1>(tuple1);
            tuple<double, double> tuple2;
            double t;
            if (ll == 0)
            {
                tuple2 = circuitElements->chart.at(RealAdmitance);
                t = get<1>(tuple2);
            }
            else
            {
                tuple2 = circuitElements->GetCircuitElements()[ll - 1]->GetChartParameters().at(RealAdmitance);
                t = get<1>(tuple2);
            }
            bool flagi = false;
            step = abs(t2 - t) / 100;
            iPoint = compute_realParallel(t);
            iPixel.setX(iPoint.x * scale + this->rect().center().x());
            iPixel.setY(-iPoint.y * scale + this->rect().center().y());
            if (t < t2)
            {
                for (t; t < t2; t += step)
                {
                    Point point = compute_realParallel(t);
                    QPointF pixel;
                    pixel.setX(point.x * scale + center.x());
                    pixel.setY(-point.y * scale + center.y());
                    painter.drawLine(iPixel, pixel);
                    iPixel = pixel;
                }
            }
            else
            {
                for (t; t < t2+2*M_PI; t += step)
                {
                    Point point = compute_realParallel(t);
                    QPointF pixel;
                    pixel.setX(point.x * scale + center.x());
                    pixel.setY(-point.y * scale + center.y());
                    painter.drawLine(iPixel, pixel);
                    iPixel = pixel;
                }
            }
        }
    }

    painter.setPen(QPen(SystemParameters::RootColor, SystemParameters::linesWidth[4]));
    if (index > 0 && Model != mode::AddPoint && Model != mode::Default)
    {
        double tmax, tmin;
        if (Model == mode::InductionShunt || Model == mode::CapacitorShunt)
        {
            tuple<double, double> tuple1;
            if (index == 1)
            {
                tuple1 = circuitElements->chart.at(RealImpedance);
            }
            else
            {
                tuple1 = circuitElements->GetCircuitElements()[index - 2]->GetChartParameters().at(RealImpedance);
            }
            r = get<0>(tuple1);
            double t = get<1>(tuple1);
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
            iPixel.setX(iPoint.x * scale + this->rect().center().x());
            iPixel.setY(iPoint.y * scale + this->rect().center().y());
            bool flagi = false;
            step = abs(tmax - tmin) / 100;
            for (tmin; tmin < tmax; tmin += step) {

                Point point = compute_real(tmin);
                QPointF pixel;
                pixel.setX(point.x * scale + this->rect().center().x());
                pixel.setY(point.y * scale + this->rect().center().y());
                painter.drawLine(iPixel, pixel);
                iPixel = pixel;
            }
        }
        else if (Model == mode::ResistorShunt)
        {
            double y;
            tuple<double, double> tuple1;
            if (index == 1)
            {
                tuple1 = circuitElements->chart.at(ImagImpedance);
                y = circuitElements->firstPoint.y;
            }
            else
            {
                tuple1 = circuitElements->GetCircuitElements()[index - 2]->GetChartParameters().at(ImagImpedance);
                y = circuitElements->GetCircuitElements()[index - 2]->GetPoint().y;
            }
            if (y >= 0 && y < 0.000001)
            {
                y = 0.01;
            }
            else if (y <= 0 && y > -0.000001)
            {
                y = -0.01;
            }
            r = get<0>(tuple1);
            double t = get<1>(tuple1);
            if (y < 0)
            {
                r = abs(r);
                tmin = t;
                tmax = 2*M_PI;
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
            (iPoint.x * scale + center.x());
            iPixel.setY(-iPoint.y * scale + center.y());
            bool flagi = false;
            for (tmin; tmin < tmax; tmin += step)
            {
                Point point = compute_imaginary(tmin);
                QPointF pixel;
                pixel.setX(point.x * scale + center.x());
                pixel.setY(-point.y * scale + center.y());
                if (pow(point.x, 2) + pow(point.y, 2) < 1)
                {
                    painter.drawLine(iPixel, pixel);
                }
                iPixel = pixel;
            }
        }
        else if (Model == mode::InductionParallel || Model == mode::CapacitorParallel)
        {
            tuple<double, double> tuple1;
            if (index == 1)
            {
                tuple1 = circuitElements->chart.at(RealAdmitance);
            }
            else
            {
                tuple1 = circuitElements->GetCircuitElements()[index - 2]->GetChartParameters().at(RealAdmitance);
            }
            r = get<0>(tuple1);
            double t = get<1>(tuple1);
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
            iPixel.setX(iPoint.x * scale + this->rect().center().x());
            iPixel.setY(-iPoint.y * scale + this->rect().center().y());
            bool flagi = false;
            step = abs(tmax - tmin) / 100;
            for (tmin; tmin < tmax; tmin += step)
            {
                Point point = compute_realParallel(tmin);
                QPointF pixel;
                pixel.setX(point.x * scale + this->rect().center().x());
                pixel.setY(-point.y * scale + this->rect().center().y());
                painter.drawLine(iPixel, pixel);
                iPixel = pixel;
            }
        }
        else if (Model == mode::ResistorParallel)
        {
            double y;
            tuple<double, double> tuple1;
            if (index == 1)
            {
                tuple1 = circuitElements->chart.at(ImagAdmitance);
                y = circuitElements->firstPoint.y;
            }
            else
            {
                tuple1 = circuitElements->GetCircuitElements()[index - 2]->GetChartParameters().at(ImagAdmitance);
                y = circuitElements->GetCircuitElements()[index - 2]->GetPoint().y;
            }
            if (y >= 0 && y < 0.000001)
            {
                y = 0.01;
            }
            else if (y <= 0 && y > -0.000001)
            {
                y = -0.01;
            }
            r = get<0>(tuple1);
            double t = get<1>(tuple1);
            if (y > 0)
            {
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
            (iPoint.x * scale + center.x());
            iPixel.setY(iPoint.y * scale + center.y());
            bool flagi = false;
            for (tmin; tmin < tmax; tmin += step)
            {
                Point point = compute_imaginaryParallel(tmin);
                QPointF pixel;
                pixel.setX(point.x * scale + center.x());
                pixel.setY(point.y * scale + center.y());
                if (pow(point.x, 2) + pow(point.y, 2) < 1)
                {
                    painter.drawLine(iPixel, pixel);
                }
                iPixel = pixel;
            }
        }
        else if (Model == mode::Line) 
        {
            Point point;
            tuple<double, double> tuple1;
            Complex zl;
            if (index == 1)
            {
                point = circuitElements->firstPoint;
                zl = circuitElements->z;
            }
            else
            {
                point = circuitElements->GetCircuitElements()[index - 2]->GetPoint();
                zl = circuitElements->GetCircuitElements()[index - 2]->GetParameter()[Z];
            }
            Complex g1 = (zl - double(50)) / (zl + double(50));
            Complex z3 = SystemParameters::z0line * (zl + Complex(0, SystemParameters::z0line)) / (SystemParameters::z0line + Complex(0, 1) * zl);
            Complex g3 = (z3 - double(50)) / (z3 + double(50));
            double center2 = 0.5 * (pow(g1.real(), 2) + pow(g1.imag(), 2) - pow(g3.real(), 2) - pow(g3.imag(), 2)) / (g1.real() - g3.real());
            qreal R = abs(center2 - g1);
            painter.setBrush(QBrush(Qt::NoBrush)); // Red solid fill
            painter.drawEllipse(QPointF(center2*scale+center.x(), center.y()), R*scale, R*scale);
        }
        else if (Model == mode::OSLine)
        {
            tuple<double, double> tuple1;
            if (index == 1)
            {
                tuple1 = circuitElements->chart.at(RealAdmitance);
            }
            else
            {
                tuple1 = circuitElements->GetCircuitElements()[index - 2]->GetChartParameters().at(RealAdmitance);
            }
            r = get<0>(tuple1);
            double t = get<1>(tuple1);
            tmin = t;
            tmax = t + 2 * M_PI;
            iPoint = compute_realParallel(tmin);
            iPixel.setX(iPoint.x * scale + this->rect().center().x());
            iPixel.setY(-iPoint.y * scale + this->rect().center().y());
            bool flagi = false;
            step = abs(tmax - tmin) / 100;
            for (tmin; tmin < tmax; tmin += step)
            {
                Point point = compute_realParallel(tmin);
                QPointF pixel;
                pixel.setX(point.x * scale + this->rect().center().x());
                pixel.setY(-point.y * scale + this->rect().center().y());
                painter.drawLine(iPixel, pixel);
                iPixel = pixel;
            }
        }
        else if (Model == mode::SSLine)
        {
            tuple<double, double> tuple1;
            if (index == 1)
            {
                tuple1 = circuitElements->chart.at(RealAdmitance);
            }
            else
            {
                tuple1 = circuitElements->GetCircuitElements()[index - 2]->GetChartParameters().at(RealAdmitance);
            }
            r = get<0>(tuple1);
            double t = get<1>(tuple1);
            tmin = t;
            tmax = t + 2 * M_PI;
            iPoint = compute_realParallel(tmin);
            iPixel.setX(iPoint.x * scale + this->rect().center().x());
            iPixel.setY(-iPoint.y * scale + this->rect().center().y());
            bool flagi = false;
            step = abs(tmax - tmin) / 100;
            for (tmin; tmin < tmax; tmin += step)
            {
                Point point = compute_realParallel(tmin);
                QPointF pixel;
                pixel.setX(point.x * scale + this->rect().center().x());
                pixel.setY(-point.y * scale + this->rect().center().y());
                painter.drawLine(iPixel, pixel);
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
    if (!m_cacheValid || defaultScale != scale || SystemParameters::colorChanged || SystemParameters::sizeChanged)
    {
        generateCache();
        defaultScale = scale;
        if (SystemParameters::colorChanged)
        {
            SystemParameters::colorChanged = false;
        }
        if (SystemParameters::sizeChanged)
        {
            SystemParameters::sizeChanged = false;
        }
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