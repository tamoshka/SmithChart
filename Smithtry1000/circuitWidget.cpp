#include "circuitWidget.h"

/// <summary>
/// Конструктор класса CircuitWidget.
/// </summary>
/// <param name="parent">Родитель (Smithtry1000).</param>
/// <param name="circuitElements">Цепь.</param>
CircuitWidget::CircuitWidget(QWidget* parent, CircuitElements* circuitElements) :
    QWidget(parent)
{
    setMinimumSize(100, 100);
    this->circuitElements = circuitElements;
    this->tuneElements = new CircuitElements();
}

/// <summary>
/// Деструктор класса CircuitWidget.
/// </summary>
CircuitWidget::~CircuitWidget()
{
}

/// <summary>
/// Добавление SVG на виджет.
/// </summary>
/// <param name="path">Путь к изображению.</param>
/// <param name="x">X.</param>
/// <param name="y">Y.</param>
void CircuitWidget::addSvg(QString path, int x, int y) {
    QSvgWidget* svgWidget = new QSvgWidget(this);

    svgWidget->load(QString(path));
    if (svgWidgets.size() >= 2)
    {
        paths.append(path);
        svgWidgets[svgWidgets.size() - 1]->hide();
        QSvgWidget* widget = svgWidgets.takeLast();
        widget->deleteLater();
        svgWidget->setGeometry(x - 40, y, 40, 40);
        svgWidget->show();

        svgWidgets.append(svgWidget);
        QSvgWidget* load = new QSvgWidget(this);

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

/// <summary>
/// Удаление настраиваемого элемента из цепи (Для TuneWidget).
/// </summary>
/// <param name="el">Элемент.</param>
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

/// <summary>
/// Удаление всех настраиваемых элементов из цепи (Для TuneWidget).
/// </summary>
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

/// <summary>
/// Удаление последнего SVG.
/// </summary>
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

/// <summary>
/// Отрисовка виджета.
/// </summary>
/// <param name="event"></param>
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
        QString s2 = QString::number((double)round(this->circuitElements->realFirstPoint*10)/10) + "  + j" + QString::number((double)round(this->circuitElements->imagFirstPoint*10)/10);
        painter.save();
        painter.translate(40 + 20, 90);
        painter.rotate(90);
        painter.setFont(QFont("Arial", 8));
        painter.drawText(0, 0, s2);
        painter.restore();
        QString s1;
        QString s3="";
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
                    SystemParameters::rImpedanceRealCalculation(lastPointX, lastPointY);
                    double r2 = SystemParameters::impedanceRealR;
                    s1 = QString::number(round((r2 - r1)*10)/10);
                    break;
                }
                case InductionShunt:
                {
                    double r1 = z.imag();
                    SystemParameters::rImpedanceImagCalculation(lastPointX, lastPointY);
                    double r2 = SystemParameters::impedanceImagR;
                    double val = (r2 - r1) / (2 * M_PI * circuitElements->frequencyFirstPoint) * 1000000000;
                    QString power;
                    if (val < 1)
                    {
                        val *= 1000;
                        power = " pH";
                    }
                    else if (val < 1000)
                    {
                        power = " nH";
                    }
                    else if (val < 1000000)
                    {
                        power = " uH";
                    }
                    else
                    {
                        power = " mH";
                    }
                    s1 = QString::number((double)round(val*10)/10) + power;
                    break;
                }
                case CapacitorShunt:
                {
                    double r1 = z.imag();
                    SystemParameters::rImpedanceImagCalculation(lastPointX, lastPointY);
                    double r2 = SystemParameters::impedanceImagR;
                    double val = 10 / ((r1 - r2) * (2 * M_PI * circuitElements->frequencyFirstPoint)) * 100000000000;
                    QString power;
                    if (val < 1)
                    {
                        val *= 1000;
                        power = " fF";
                    }
                    else if (val < 1000)
                    {
                        power = " pF";
                    }
                    else if (val < 1000000)
                    {
                        power = " nF";
                    }
                    else
                    {
                        power = " uF";
                    }
                    s1 = QString::number((double)round(val * 10) / 10) + power;
                    break;
                }
                case ResistorParallel:
                {
                    double r1 = y.real();
                    SystemParameters::rAdmitanceRealCalculation(lastPointX, lastPointY);
                    double r2 = SystemParameters::admitanceRealR;
                    s1 = QString::number(round(1000 / (r2 - r1)*10)/10);
                    break;
                }
                case InductionParallel:
                {
                    double r1 = y.imag();
                    SystemParameters::rAdmitanceImagCalculation(lastPointX, lastPointY);
                    double r2 = SystemParameters::admitanceImagR;
                    double val = M_PI / (r1 - r2) * 100 / circuitElements->frequencyFirstPoint * 1e6 * 500;
                    QString power;
                    if (val < 1)
                    {
                        val *= 1000;
                        power = " pH";
                    }
                    else if (val < 1000)
                    {
                        power = " nH";
                    }
                    else if (val < 1000000)
                    {
                        power = " uH";
                    }
                    else
                    {
                        power = " mH";
                    }
                    s1 = QString::number((double)round(val * 10) / 10) + power;
                    break;
                }
                case CapacitorParallel:
                {
                    double r1 = y.imag();
                    SystemParameters::rAdmitanceImagCalculation(lastPointX, lastPointY);
                    double r2 = SystemParameters::admitanceImagR;
                    double val = (r2 - r1) / M_PI * 500 / circuitElements->frequencyFirstPoint * 1000000;
                    QString power;
                    if (val < 1)
                    {
                        val *= 1000;
                        power = " fF";
                    }
                    else if (val < 1000)
                    {
                        power = " pF";
                    }
                    else if (val < 1000000)
                    {
                        power = " nF";
                    }
                    else
                    {
                        power = " uF";
                    }
                    s1 = QString::number((double)round(val * 10) / 10) + power;
                    break;
                }
                case Line:
                {
                    double RL = z.real();
                    double XL = z.imag();
                    SystemParameters::rImpedanceRealCalculation(lastPointX, lastPointY);
                    SystemParameters::rImpedanceImagCalculation(lastPointX, lastPointY);
                    double R = SystemParameters::impedanceRealR;
                    double X = SystemParameters::impedanceImagR;
                    double RR = R - RL;
                    double sq = -sqrt(RR * (RL * (pow(X, 2) + pow(R, 2)) - R * (pow(XL, 2) + pow(RL, 2)))) / RR;
                    double tanO1 = RR * sq / (R * XL + RL * X);
                    double tanO2 = -RR * sq / (R * XL + RL * X);
                    double z0;
                    double O;
                    if (sq > 0)
                    {
                        z0 = sq;
                        O = atan(tanO1);
                    }
                    else
                    {
                        z0 = -sq;
                        O = atan(tanO2);
                    }
                    if (O < 0)
                    {
                        O += M_PI;
                    }
                    double Theta = O * 180 / M_PI;
                    double l = O * 299792458 / (M_PI * 1e9*2);
                    double Length = l * 1e3;
                    double lambda = l * 1e9 / 299792458;
                    s1 = QString::number((double)round(SystemParameters::z0line * 10) / 10) + "Ohm |" + QString::number(round(SystemParameters::alpha * 10) / 10) + "dB/m|lambda=" + QString::number(round(lambda * 10000) / 10000);
                    s3 = QString::number(round(l * 1000 / sqrt(SystemParameters::er) * 10) / 10) + "mm(phys)|" + QString::number(round(l * 1000 * 10) / 10) + "mm(electr)";
                    break;
                }
                case OSLine:
                {
                    double theta;
                    double lambda;
                    double o;
                    double l;
                    SystemParameters::rAdmitanceImagCalculation(lastPointX, lastPointY);
                    o = atan((SystemParameters::admitanceImagR - y.imag()) / 1000 * SystemParameters::z0line);
                    if (o < 0)
                    {
                        o += M_PI;
                    }
                    theta = o * 180 / M_PI;
                    l = o * 299792458 / (2*M_PI * 1e9);
                    lambda = l * 1e9 / 299792458;
                    s1 = QString::number((double)round(SystemParameters::z0line * 10) / 10) + "Ohm | lambda=" + QString::number(round(lambda * 10000) / 10000);
                    s3 = QString::number(round(l * 1000 / sqrt(SystemParameters::er) * 10) / 10) + "mm(phys)|" + QString::number(round(l * 1000 * 10) / 10) + "mm(electr)";
                    break;
                }
                case SSLine:
                {
                    double theta;
                    double lambda;
                    double o;
                    double l;
                    SystemParameters::rAdmitanceImagCalculation(lastPointX, lastPointY);
                    o = -atan(1 / ((SystemParameters::admitanceImagR - y.imag()) / 1000 * SystemParameters::z0line));
                    if (o < 0)
                    {
                        o += M_PI;
                    }
                    theta = o * 180 / M_PI;
                    l = o * 299792458 / (2*M_PI * 1e9);
                    lambda = l * 1e9 / 299792458;
                    s1 = QString::number((double)round(SystemParameters::z0line * 10) / 10) + "Ohm | lambda=" + QString::number(round(lambda * 10000) / 10000);
                    s3 = QString::number(round(l * 1000 / sqrt(SystemParameters::er) * 10) / 10) + "mm(phys)|" + QString::number(round(l * 1000 * 10) / 10) + "mm(electr)";
                    break;
                }
                case Transform:
                {
                    double theta;
                    double lambda;
                    double o;
                    double l;
                    SystemParameters::rImpedanceRealCalculation(lastPointX, lastPointY);
                    double n = sqrt(SystemParameters::impedanceRealR / z.real());
                    s1 = "1:" + QString::number(n);
                    break;
                }
            }
        }
        painter.save();
        painter.translate((index + 1) * 40 + 20, 90);
        painter.rotate(90);
        painter.setFont(QFont("Arial", 8));
        painter.drawText(0, 0, s1);
        painter.translate(0, +15);
        painter.drawText(0, 0, s3);
        s3 = "";
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
                    LinesElement* tmp = dynamic_cast<LinesElement*>(temp[i]);
                    s1 = QString::number((double)round(tmp->GetValue()*10)/10) + "Ohm |" + QString::number((double)round(tmp->GetAlpha()*10)/10)+ "dB/m|lambda=" +QString::number((double)round(tmp->GetLambda()*10000)/10000);
                    s3 = QString::number((double)round(tmp->GetMechanicalLength()*10)/10) + "mm(phys)|" + QString::number((double)round(tmp->GetElectricalLength()*10)/10) + "mm(electr)";
                    break;
                }
                case OSLine:
                {
                    VerticalLinesElement* tmp = dynamic_cast<VerticalLinesElement*>(temp[i]);
                    s1 = QString::number((double)round(tmp->GetValue() * 10) / 10) + "Ohm | lambda=" + QString::number((double)round(tmp->GetLambda() * 10000) / 10000);
                    s3 = QString::number((double)round(tmp->GetMechanicalLength() * 10) / 10) + "mm(phys)|" + QString::number((double)round(tmp->GetElectricalLength() * 10) / 10) + "mm(electr)";
                    break;
                }
                case SSLine:
                {
                    VerticalLinesElement* tmp = dynamic_cast<VerticalLinesElement*>(temp[i]);
                    s1 = QString::number((double)tmp->GetValue()) + "Ohm | lambda=" + QString::number((double)tmp->GetLambda());
                    s3 = QString::number((double)round(tmp->GetMechanicalLength() * 10) / 10) + "mm(phys)|" + QString::number((double)round(tmp->GetElectricalLength() * 10) / 10) + "mm(electr)";
                    break;
                }
                case Transform:
                {
                    s1 = "1:" + QString::number(temps1);
                    break;
                }
            }
            painter.save();
            painter.translate((i + 2) * 40 + 20, 90);
            painter.rotate(90);
            painter.setFont(QFont("Arial", 8));
            painter.drawText(0, 0, s1);
            painter.translate(0, +15);
            painter.drawText(0, 0, s3);
            s3 = "";
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
                        tuneElements->AppendCircuitElements(circuitElements->GetCircuitElements()[n-2]);
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
                            tuneElements->AppendCircuitElements(circuitElements->GetCircuitElements()[n - 2]);
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

/// <summary>
/// Обработка при наведении на виджет.
/// </summary>
/// <param name="event"></param>
void CircuitWidget::enterEvent(QEvent* event)
{
    SystemParameters::circuitHover = true;
    update();
    QWidget::enterEvent(event);
}

/// <summary>
/// Обработка при выходе с виджета.
/// </summary>
/// <param name="event"></param>
void CircuitWidget::leaveEvent(QEvent* event)
{
    SystemParameters::circuitHover = false;
}

/// <summary>
/// Обработка нажатия левой кнопки мыши.
/// </summary>
void CircuitWidget::getLeft()
{
    left = true;
    update();
}