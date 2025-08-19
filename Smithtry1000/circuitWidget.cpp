#include "circuitWidget.h"
CircuitWidget::CircuitWidget(QWidget* parent, CircuitElements* circuitElements) :
    QWidget(parent)
{
    setMinimumSize(100, 100);
    this->circuitElements = circuitElements;
    this->tuneElements = new CircuitElements();
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
        paths.append(path);
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

void CircuitWidget::RemoveElement(Element* el)
{
    int i = 0;
    for (auto var :  tuneElements->GetCircuitElements())
    {
        if (var == el)
        {
            tuneElements->Remove(i);
            tuned.takeAt(i);
            break;
        }
        i++;
    }
    update();
}

void CircuitWidget::RemoveAll()
{
    int i = tuneElements->GetCircuitElements().size() - 1;
    while (tuneElements->GetCircuitElements().size() > 0)
    {
        tuneElements->Remove(i);
        tuned.pop_back();
        i--;
    }
    update();
}

void CircuitWidget::removeLastSvg() {
    paths.pop_back();
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

void CircuitWidget::rImpedanceRealCalculation(double x, double y)
{
    double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
    double xCenter = 1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    double sin_t = dy;
    double cos_t = dx;
    double t1;
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
    painter.setPen(QPen(Qt::black, 2));
    QList<Element*> temp;
    try
    {
         temp = this->circuitElements->GetCircuitElements();
    }
    catch(exception ex)
    {

    }
    if (this->circuitElements->imagFirstPoint != -9999)
    {
        QString s2 = QString::number(round(this->circuitElements->realFirstPoint*10)/10) + "  + j" + QString::number(round(this->circuitElements->imagFirstPoint*10)/10);
        painter.save();
        painter.translate(40 + 20, 120);
        painter.rotate(90);
        painter.setFont(QFont("Arial", 8));
        painter.drawText(0, 0, s2);
        painter.restore();
        QString s1;
        if (Model != AddPoint && Model != Default)
        {
            Complex z;
            Complex y;
            if (index != 1)
            {
                z = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size()-1]->GetParameter().at(Z);
                y = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter().at(Y);
            }
            else
            {
                z = circuitElements->z;
                y = circuitElements->y;
            }
            switch (Model)
            {
                case ResistorShunt:
                {
                    double r1 = z.real();
                    rImpedanceRealCalculation(lastPointX, lastPointY);
                    double r2 = impedanceRealR;
                    s1 = QString::number(round((r2 - r1)*10)/10);
                    break;
                }
                case InductionShunt:
                {
                    double r1 = z.imag();
                    rImpedanceImagCalculation(lastPointX, lastPointY);
                    double r2 = impedanceImagR;
                    s1 = QString::number(round((r2 - r1) / (2 * M_PI * 1000000 * frequency) * 1000000000*10)/10) + " nH";
                    break;
                }
                case CapacitorShunt:
                {
                    double r1 = z.imag();
                    rImpedanceImagCalculation(lastPointX, lastPointY);
                    double r2 = impedanceImagR;
                    s1 = QString::number(round(10*1 / ((r1 - r2) * (2 * M_PI * 1000000 * frequency)) * 1000000000000)/10) + " pF";
                    break;
                }
                case ResistorParallel:
                {
                    double r1 = y.real();
                    rAdmitanceRealCalculation(lastPointX, lastPointY);
                    double r2 = admitanceRealR;
                    s1 = QString::number(round(1000 / (r2 - r1)*10)/10);
                    break;
                }
                case InductionParallel:
                {
                    double r1 = y.imag();
                    rAdmitanceImagCalculation(lastPointX, lastPointY);
                    double r2 = admitanceImagR;
                    s1 = QString::number(round(10*M_PI/(r1-r2) * 100/frequency*500)/10) + " nH";
                    break;
                }
                case CapacitorParallel:
                {
                    double r1 = y.imag();
                    rAdmitanceImagCalculation(lastPointX, lastPointY);
                    double r2 = admitanceImagR;
                    s1 = QString::number(round((r2 - r1) / M_PI * 500/frequency*10)/10) + " pF";
                    break;
                }
                case Line:
                {
                    break;
                }
                case OSLine:
                {
                    break;
                }
                case SSLine:
                {
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
            double temps1 = temp[i]->GetValue();
            switch (temp[i]->GetMode())
            {
                case ResistorShunt:
                {
                    s1 = QString::number(round(temps1*10)/10);
                    break;
                }
                case InductionShunt:
                {
                    s1 = QString::number(round(temps1 * 10*1e9) / 10);
                    s1 = s1 + " nH";
                    break;
                }
                case CapacitorShunt:
                {
                    s1 = QString::number(round(temps1 * 10 * 1e12) / 10);
                    s1 = s1 + " pF";
                    break;
                }
                case ResistorParallel:
                {
                    s1 = QString::number(round(temps1 * 10) / 10);
                    break;
                }
                case InductionParallel:
                {
                    s1 = QString::number(round(temps1 * 10 * 1e9) / 10);
                    s1 = s1 + " nH";
                    break;
                }
                case CapacitorParallel:
                {
                    s1 = QString::number(round(temps1 * 10 * 1e12) / 10);
                    s1 = s1 + " pF";
                    break;
                }
                case Line:
                {
                    break;
                }
                case OSLine:
                {
                    break;
                }
                case SSLine:
                {
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
        if (SystemParameters::tune && SystemParameters::circuitHover)
        {
            painter.setPen(QPen(Qt::red, 2));
            int count = circuitElements->GetCircuitElements().length();
            QPoint centerLocal = this->rect().center();
            QPoint centerGlobal = this->mapToGlobal(centerLocal);
            int start = (int)centerGlobal.x()-920;
            int end = (int)(centerGlobal.x()-920 + 40 * (count));
            QPoint pos = QCursor::pos();
            if (pos.x() >= start && pos.x() < end)
            {
                int n = (int)((pos.x() - (centerGlobal.x()-1000)) / 40);
                QPoint first = QPoint(n * 40, 20);
                QPoint second = QPoint((n + 1) * 40, 20);
                QPoint third = QPoint((n + 1) * 40, 80);
                QPoint fourth = QPoint(n * 40, 80);
                painter.drawLine(first, second);
                painter.drawLine(second, third);
                painter.drawLine(third, fourth);
                painter.drawLine(fourth, first);
                if (left)
                {
                    if (tuneElements->GetCircuitElements().length() == 0)
                    {
                        tuneElements->AddCircuitElements(circuitElements->GetCircuitElements()[n-2]);
                        emit clicked(circuitElements->GetCircuitElements()[n - 2], paths[n - 2]);
                        tuned.append(n);
                    }
                    else
                    {
                        bool flag = false;
                        for (auto& var : tuneElements->GetCircuitElements())
                        {
                            if (var == circuitElements->GetCircuitElements()[n - 2])
                            {
                                flag = true;
                                break;
                            }
                        }
                        if (flag == false)
                        {
                            tuneElements->AddCircuitElements(circuitElements->GetCircuitElements()[n - 2]);
                            emit clicked(circuitElements->GetCircuitElements()[n - 2], paths[n-2]);
                            tuned.append(n);
                        }
                    }
                }
            }
        }
        for (auto& var : tuned)
        {
            painter.setPen(QPen(Qt::blue, 2));
            QPoint first = QPoint(var * 40, 20);
            QPoint second = QPoint((var + 1) * 40, 20);
            QPoint third = QPoint((var + 1) * 40, 80);
            QPoint fourth = QPoint(var * 40, 80);
            painter.drawLine(first, second);
            painter.drawLine(second, third);
            painter.drawLine(third, fourth);
            painter.drawLine(fourth, first);
        }
        left = false;
    }
}

void CircuitWidget::rAdmitanceRealCalculation(double x, double y)
{
    double circleRadius = -1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 + 2 * x));
    double xCenter = -1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    dy *= -1;
    double sin_t = dy;
    double cos_t = dx;
    double t1;
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

void CircuitWidget::rImpedanceImagCalculation(double x, double y)
{
    double cos_t;
    double sin_t;
    double circleRadius = 1 - ((pow(x, 2) + pow(y, 2) - 1) / (2 * (x - 1)));
    double xCenter = 1 - circleRadius;
    double dx = x - xCenter;
    double dy = y;
    sin_t = dy;
    cos_t = dx;
    double t1;
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
    if (y == 0 || (abs(y) < 1e-7&&x<0.999))
    {
        impedanceImagR = 0;
    }
    impedanceImagR *= 50;
}

void CircuitWidget::rAdmitanceImagCalculation(double x, double y)
{
    double cos_t;
    double sin_t;
    double circleRadius = (pow(x, 2) + 2 * x + 1 + pow(y, 2)) / (-2 * y);
    double yCenter = -circleRadius;
    double dx = x + 1;
    double dy = y - yCenter;
    sin_t = -dy;
    cos_t = dx;
    double t1;
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
    if (y == 0 || (abs(y) < 1e-7 && x > -0.999))
    {
        admitanceImagR = 0;
    }
    admitanceImagR *= -20;
}

void CircuitWidget::enterEvent(QEnterEvent* event)
{
    SystemParameters::circuitHover = true;
}

void CircuitWidget::leaveEvent(QEvent* event)
{
    SystemParameters::circuitHover = false;
}

void CircuitWidget::getLeft()
{
    left = true;
    update();
}