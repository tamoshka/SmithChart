#include "circuitWidget.h"
CircuitWidget::CircuitWidget(QWidget* parent, CircuitElements* circuitElements) :
    QWidget(parent)
{
    setMinimumSize(100, 100);
    this->circuitElements = circuitElements;
}

CircuitWidget::~CircuitWidget()
{
}

void CircuitWidget::addSvg(QString path, int x, int y) {
    // Создаем SVG виджет
    QSvgWidget* svgWidget = new QSvgWidget(this);

    // Загружаем SVG из ресурсов
    svgWidget->load(QString(path));
    if (svgWidgets.size() >= 2)
    {
        svgWidgets[svgWidgets.size() - 1]->hide();
        QSvgWidget* widget = svgWidgets.takeLast();
        widget->deleteLater(); // Безопасное удаление
        // Устанавливаем позицию и размер (x, y, width, height)
        svgWidget->setGeometry(x - 40, y, 40, 40);
        svgWidget->show();

        svgWidgets.append(svgWidget);
        QSvgWidget* load = new QSvgWidget(this);

        // Загружаем SVG из ресурсов
        load->load(QString(":/Images/source.svg"));
        load->setGeometry(x, 39, 40, 40);
        load->show();
        svgWidgets.append(load);
    }
    else
    {
        svgWidget->setGeometry(x, y, 40, 40);
        svgWidget->show();
        svgWidgets.append(svgWidget);
    }
}

void CircuitWidget::removeLastSvg() {
    if (!svgWidgets.isEmpty() && svgWidgets.size()>2) {
        int deletedIndex = svgWidgets.size() - 2;
        QSvgWidget* deleted = svgWidgets[deletedIndex];
        deleted->hide();
        svgWidgets.removeAt(svgWidgets.size() - 2);
        int index = svgWidgets.size() - 1;
        QSvgWidget* temp = svgWidgets[index];
        temp->setGeometry((index + 1) * 40, 39, 40, 40);
        temp->show();
    }
}

void CircuitWidget::rImpedanceRealCalculation(float x, float y)
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

void CircuitWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::red, 2));
    QList<Element*> temp = this->circuitElements->GetCircuitElements();
    if (this->circuitElements->imagFirstPoint != -9999)
    {
        QString s2 = QString::number(this->circuitElements->realFirstPoint) + "  + j" + QString::number(this->circuitElements->imagFirstPoint);
        painter.save();
        painter.translate(40 + 20, 120);
        painter.rotate(90);
        painter.setFont(QFont("Arial", 8));
        painter.drawText(0, 0, s2);
        painter.restore();
        QString s1;
        if (Model != AddPoint && Model != Default)
        {
            switch (Model)
            {
            case ResistorShunt:
            {
                rImpedanceRealCalculation(get<0>(points[index - 1]).x, get<0>(points[index - 1]).y);
                float r1 = impedanceRealR;
                rImpedanceRealCalculation(lastPointX, lastPointY);
                float r2 = impedanceRealR;
                s1 = QString::number(r2 - r1);
                break;
            }
            case InductionShunt:
            {
                rImpedanceImagCalculation(get<0>(points[index - 1]).x, get<0>(points[index - 1]).y);
                float r1 = impedanceImagR;
                rImpedanceImagCalculation(lastPointX, lastPointY);
                float r2 = impedanceImagR;
                s1 = QString::number((r2 - r1) / (2 * M_PI * 1000000 * frequency) * 1000000000) + " nH";
                break;
            }
            case CapacitorShunt:
            {
                rImpedanceImagCalculation(get<0>(points[index - 1]).x, get<0>(points[index - 1]).y);
                float r1 = impedanceImagR;
                rImpedanceImagCalculation(lastPointX, lastPointY);
                float r2 = impedanceImagR;
                s1 = QString::number(1 / ((r1 - r2) * (2 * M_PI * 1000000 * frequency)) * 1000000000000) + " pF";
                break;
            }
            case ResistorParallel:
            {
                rAdmitanceRealCalculation(get<0>(points[index - 1]).x, get<0>(points[index - 1]).y);
                float r1 = admitanceRealR;
                rAdmitanceRealCalculation(lastPointX, lastPointY);
                float r2 = admitanceRealR;
                s1 = QString::number(1000 / (r2 - r1));
                break;
            }
            case InductionParallel:
            {
                rAdmitanceImagCalculation(get<0>(points[index-1]).x, get<0>(points[index-1]).y);
                float r1 = admitanceImagR;
                rAdmitanceImagCalculation(lastPointX, lastPointY);
                float r2 = admitanceImagR;
                s1 = QString::number(320 * (frequency / 500) / (r1 - r2)) + " nH";
                break;
            }
            case CapacitorParallel:
            {
                rAdmitanceImagCalculation(get<0>(points[index - 1]).x, get<0>(points[index - 1]).y);
                float r1 = admitanceImagR;
                rAdmitanceImagCalculation(lastPointX, lastPointY);
                float r2 = admitanceImagR;
                s1 = QString::number((r2 - r1) / (6 * (frequency / 500))) + " pF";
                break;
            }
            }
        }
        painter.save();
        painter.translate((index + 1) * 40 + 20, 120);
        painter.rotate(90);
        painter.setFont(QFont("Arial", 8));
        painter.drawText(0, 0, s1);
        painter.restore();
        for (int i = 0; i < temp.size(); i++)
        {
            float temps1 = temp[i]->GetValue();
            switch (temp[i]->GetMode())
            {
            case ResistorShunt:
            {
                s1 = QString::number(temps1);
                break;
            }
            case InductionShunt:
            {
                s1 = QString::number(temps1*1e9);
                s1 = s1 + " nH";
                break;
            }
            case CapacitorShunt:
            {
                s1 = QString::number(temps1 * 1e12);
                s1 = s1 + " pF";
                break;
            }
            case ResistorParallel:
            {
                s1 = QString::number(temps1);
                break;
            }
            case InductionParallel:
            {
                s1 = QString::number(temps1 * 1e9);
                s1 = s1 + " nH";
                break;
            }
            case CapacitorParallel:
            {
                s1 = QString::number(temps1 * 1e12);
                s1 = s1 + " pF";
                break;
            }
            }
            painter.save();
            painter.translate((i + 2) * 40 + 20, 120);
            painter.rotate(90);
            painter.setFont(QFont("Arial", 8));
            painter.drawText(0, 0, s1);
            painter.restore();
        }
    }
}

void CircuitWidget::rAdmitanceRealCalculation(float x, float y)
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
    admitanceRealR *= 20;
}

void CircuitWidget::rImpedanceImagCalculation(float x, float y)
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

void CircuitWidget::rAdmitanceImagCalculation(float x, float y)
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
    admitanceImagR *= -20;
}