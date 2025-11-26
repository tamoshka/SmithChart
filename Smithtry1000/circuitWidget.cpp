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
    if (!SystemParameters::rotate)
    {
        this->setFixedWidth(circuitElements->GetCircuitElements().size() * 40 + 200);
        this->setFixedHeight(300);
    }
    else
    {
        this->setFixedWidth(200);
        this->setFixedHeight(circuitElements->GetCircuitElements().size() * 40 + 300);
    }
    svgWidget->load(QString(path));
    if (SystemParameters::svgWidgets.size() >= 2)
    {
        paths.pop_back();
        SystemParameters::svgWidgets[SystemParameters::svgWidgets.size() - 1]->hide();
        QSvgWidget* widget = SystemParameters::svgWidgets.takeLast();
        widget->deleteLater();
        svgWidget->setGeometry(x - 40, y, 40, 40);
        svgWidget->show();

        SystemParameters::svgWidgets.append(svgWidget);
        QSvgWidget* load = new QSvgWidget(this);
        if (!SystemParameters::rotate)
        {

            load->load(QString(":/Images/source.svg"));
            load->setGeometry(x, 39, 40, 40);
        }
        else
        {

            load->load(QString(":/Images/rev_source.svg"));
            load->setGeometry(39, y+40, 40, 40);
        }
        load->show();
        SystemParameters::svgWidgets.append(load);
        QString tempPath=path;
        if (path == ":/Images/rev_horizontal_c.svg")
        {
            tempPath = ":/Images/horizontal_c.svg";
        }
        else if (path == ":/Images/rev_horizontal_i.svg")
        {
            tempPath = ":/Images/horizontal_i.svg";
        }
        else if (path == ":/Images/rev_horizontal_r.svg")
        {
            tempPath = ":/Images/horizontal_r.svg";
        }
        else if (path == ":/Images/rev_horizontal_line_circuit.svg")
        {
            tempPath = ":/Images/horizontal_line_circuit.svg";
        }
        else if (path == ":/Images/rev_load.svg")
        {
            tempPath = ":/Images/load.svg";
        }
        else if (path == ":/Images/rev_os_circuit.svg")
        {
            tempPath = ":/Images/os_circuit.svg";
        }
        else if (path == ":/Images/rev_source.svg")
        {
            tempPath = ":/Images/source.svg";
        }
        else if (path == ":/Images/rev_ss_circuit.svg")
        {
            tempPath = ":/Images/ss_circuit.svg";
        }
        else if (path == ":/Images/rev_vertical_c_circuit.svg")
        {
            tempPath = ":/Images/vertical_c_circuit.svg";
        }
        else if (path == ":/Images/rev_vertical_i_circuit.svg")
        {
            tempPath = ":/Images/vertical_i_circuit.svg";
        }
        else if (path == ":/Images/rev_vertical_r_circuit.svg")
        {
            tempPath = ":/Images/vertical_r_circuit.svg";
        }
        else if (path == ":/Images/rev_vertical_transform_circuit.svg")
        {
            tempPath = ":/Images/vertical_transform_circuit.svg";
        }
        paths.append(tempPath);
        paths.append(":/Images/source.svg");
    }
    else
    {
        QString tempPath = path;
        if (path == ":/Images/rev_source.svg")
        {
            tempPath = ":/Images/source.svg";
        }
        if (path == ":/Images/rev_load.svg")
        {
            tempPath = ":/Images/load.svg";
        }
        paths.append(tempPath);
        svgWidget->setGeometry(x, y, 40, 40);
        svgWidget->show();
        SystemParameters::svgWidgets.append(svgWidget);
    }
}

void CircuitWidget::Reverse()
{
    bool vertical=SystemParameters::rotate;
    if (vertical)
    {
        this->setFixedWidth(200);
        this->setFixedHeight(circuitElements->GetCircuitElements().size() * 40 + 300);
        int i = 0;
        for (auto var : SystemParameters::svgWidgets)
        {
            int dif=39;
            QString newpath;
            if (paths[i] == ":/Images/horizontal_c.svg")
            {
                newpath = ":/Images/rev_horizontal_c.svg";
                dif = 20;
            }
            else if (paths[i] == ":/Images/horizontal_i.svg")
            {
                newpath = ":/Images/rev_horizontal_i.svg";
                dif = 20;
            }
            else if (paths[i] == ":/Images/horizontal_r.svg")
            {
                newpath = ":/Images/rev_horizontal_r.svg";
                dif = 20;
            }
            else if (paths[i] == ":/Images/horizontal_line_circuit.svg")
            {
                newpath = ":/Images/rev_horizontal_line_circuit.svg";
                dif = 20;
            }
            else if (paths[i] == ":/Images/load.svg")
            {
                newpath = ":/Images/rev_load.svg";
            }
            else if (paths[i] == ":/Images/os_circuit.svg")
            {
                newpath = ":/Images/rev_os_circuit.svg";
            }
            else if (paths[i] == ":/Images/source.svg")
            {
                newpath = ":/Images/rev_source.svg";
            }
            else if (paths[i] == ":/Images/ss_circuit.svg")
            {
                newpath = ":/Images/rev_ss_circuit.svg";
            }
            else if (paths[i] == ":/Images/vertical_c_circuit.svg")
            {
                newpath = ":/Images/rev_vertical_c_circuit.svg";
            }
            else if (paths[i] == ":/Images/vertical_i_circuit.svg")
            {
                newpath = ":/Images/rev_vertical_i_circuit.svg";
            }
            else if (paths[i] == ":/Images/vertical_r_circuit.svg")
            {
                newpath = ":/Images/rev_vertical_r_circuit.svg";
            }
            else if (paths[i] == ":/Images/vertical_transform_circuit.svg")
            {
                newpath = ":/Images/rev_vertical_transform_circuit.svg";
            }
            var->load(newpath);
            var->setGeometry(dif, 40 + 40 * i, 40, 40);
            i++;
        }
    }
    else
    {
        this->setFixedWidth(circuitElements->GetCircuitElements().size() * 40+200);
        this->setFixedHeight(300);
        int i = 0;
        for (auto var : SystemParameters::svgWidgets)
        {
            int dif = 39;
            if (paths[i] == ":/Images/horizontal_c.svg" || paths[i] == ":/Images/horizontal_i.svg" || paths[i] == ":/Images/horizontal_r.svg" || paths[i] == ":/Images/horizontal_line_circuit.svg")
            {
                dif = 20;
            }
            var->load(paths[i]);
            var->setGeometry(40+40*i, dif, 40, 40);
            i++;
        }
    }
    update();
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
    if (!SystemParameters::svgWidgets.isEmpty() && SystemParameters::svgWidgets.size()>2) {
        paths.takeAt(paths.size()-2);
        if (SystemParameters::rotate)
        {
            this->setFixedHeight(circuitElements->GetCircuitElements().size() * 40 + 300);
        }
        else
        {
            this->setFixedWidth(circuitElements->GetCircuitElements().size() * 40 + 200);
        }
        int deletedIndex = SystemParameters::svgWidgets.size() - 2;
        QSvgWidget* deleted = SystemParameters::svgWidgets[deletedIndex];
        deleted->hide();
        SystemParameters::svgWidgets.removeAt(SystemParameters::svgWidgets.size() - 2);
        int index = SystemParameters::svgWidgets.size() - 1;
        QSvgWidget* temp = SystemParameters::svgWidgets[index];
        if (!SystemParameters::rotate)
        {
            temp->setGeometry((index + 1) * 40, 39, 40, 40);
        }
        else
        {
            temp->setGeometry(39, (index + 1) * 40, 40, 40);
        }
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
        if (!SystemParameters::rotate)
        {
            painter.translate(60, 90);
            painter.rotate(90);
        }
        else
        {
            painter.translate(90, 60);
        }
        painter.setFont(QFont("Arial", 8));
        painter.drawText(0, 0, s2);
        painter.restore();
        QString s1;
        QString s3="";
        CurrentValuePaint(painter);
        ElementValuesPaint(painter);
        TunedPaint(painter);
    }
    left = false;
}

void CircuitWidget::TunedPaint(QPainter& painter)
{
    if (SystemParameters::tune && SystemParameters::circuitHover)
    {
        painter.setPen(QPen(Qt::red, 2));
        int count = circuitElements->GetCircuitElements().length();
        QPoint centerLocal = this->rect().center();
        QPoint centerGlobal = this->mapToGlobal(centerLocal);
        QPoint first, second, third, fourth;
        int n = -9999;;
        if (!SystemParameters::rotate)
        {
            int start = (int)centerGlobal.x() - this->width() / 2 + 80;
            int end = (int)(centerGlobal.x() - this->width() / 2 + 80 + 40 * (count));
            QPoint pos = QCursor::pos();
            if (pos.x() >= start && pos.x() < end)
            {
                n = (int)((pos.x() - (centerGlobal.x() - this->width() / 2)) / 40);
                first = QPoint(n * 40, 20);
                second = QPoint((n + 1) * 40, 20);
                third = QPoint((n + 1) * 40, 80);
                fourth = QPoint(n * 40, 80);
            }
        }
        else
        {
            int start = (int)centerGlobal.y() - this->height() / 2 + 80;
            int end = (int)(centerGlobal.y() - this->height() / 2 + 80 + 40 * (count));
            QPoint pos = QCursor::pos();
            if (pos.y() >= start && pos.y() < end)
            {
                n = (int)((pos.y() - (centerGlobal.y() - this->height() / 2)) / 40);
                first = QPoint(20, n * 40);
                second = QPoint(20, (n + 1) * 40);
                third = QPoint(80, (n + 1) * 40);
                fourth = QPoint(80, n * 40);
            }
        }
        painter.drawLine(first, second);
        painter.drawLine(second, third);
        painter.drawLine(third, fourth);
        painter.drawLine(fourth, first);
        if (left && n != -9999)
        {
            if (tuneElements->GetCircuitElements().length() == 0)
            {
                tuneElements->AppendCircuitElements(circuitElements->GetCircuitElements()[n - 2]);
                emit clicked(circuitElements->GetCircuitElements()[n - 2], paths[n - 1]);
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
                    emit clicked(circuitElements->GetCircuitElements()[n - 2], paths[n - 1]);
                    tuned.append(n);
                }
            }
        }
    }
    for (auto& var : tuned)
    {
        painter.setPen(QPen(Qt::blue, 2));
        QPoint first, second, third, fourth;
        if (!SystemParameters::rotate)
        {
            first = QPoint(var * 40, 20);
            second = QPoint((var + 1) * 40, 20);
            third = QPoint((var + 1) * 40, 80);
            fourth = QPoint(var * 40, 80);
        }
        else
        {
            first = QPoint(20, var * 40);
            second = QPoint(20, (var + 1) * 40);
            third = QPoint(80, (var + 1) * 40);
            fourth = QPoint(80, var * 40);
        }
        painter.drawLine(first, second);
        painter.drawLine(second, third);
        painter.drawLine(third, fourth);
        painter.drawLine(fourth, first);
    }
}

void CircuitWidget::ElementValuesPaint(QPainter& painter)
{
    QList<Element*> temp = circuitElements->GetCircuitElements();
    QString s1, s3;
    for (int i = 0; i < temp.size(); i++)
    {
        double temps1 = temp[i]->GetValue();
        switch (temp[i]->GetMode())
        {
        case ResistorShunt:
        {
            s1 = QString::number(round(temps1 * 10) / 10);
            break;
        }
        case InductionShunt:
        {
            QString power;
            temps1 *= 1e9;
            if (temps1 < 1)
            {
                temps1 *= 1000;
                power = " pH";
            }
            else if (temps1 < 1000)
            {
                power = " nH";
            }
            else if (temps1 < 1000000)
            {
                temps1 /= 1e3;
                power = " uH";
            }
            else
            {
                temps1 /= 1e6;
                power = " mH";
            }
            s1 = QString::number(round(temps1 * 10) / 10);
            s1 = s1 + power;
            break;
        }
        case CapacitorShunt:
        {
            QString power;
            temps1 *= 1e12;
            if (temps1 < 1)
            {
                temps1 *= 1000;
                power = " fF";
            }
            else if (temps1 < 1000)
            {
                power = " pF";
            }
            else if (temps1 < 1000000)
            {
                temps1 /= 1e3;
                power = " nF";
            }
            else
            {
                temps1 /= 1e6;
                power = " uF";
            }
            s1 = QString::number(round(temps1 * 10) / 10);
            s1 = s1 + power;
            break;
        }
        case ResistorParallel:
        {
            s1 = QString::number(round(temps1 * 10) / 10);
            break;
        }
        case InductionParallel:
        {
            QString power;
            temps1 *= 1e9;
            if (temps1 < 1)
            {
                temps1 *= 1000;
                power = " pH";
            }
            else if (temps1 < 1000)
            {
                power = " nH";
            }
            else if (temps1 < 1000000)
            {
                temps1 /= 1e3;
                power = " uH";
            }
            else
            {
                temps1 /= 1e6;
                power = " mH";
            }
            s1 = QString::number(round(temps1 * 10) / 10);
            s1 = s1 + power;
            break;
        }
        case CapacitorParallel:
        {
            QString power;
            temps1 *= 1e12;
            if (temps1 < 1)
            {
                temps1 *= 1000;
                power = " fF";
            }
            else if (temps1 < 1000)
            {
                power = " pF";
            }
            else if (temps1 < 1000000)
            {
                temps1 /= 1e3;
                power = " nF";
            }
            else
            {
                temps1 /= 1e6;
                power = " uF";
            }
            s1 = QString::number(round(temps1 * 10) / 10);
            s1 = s1 + power;
            break;
        }
        case Line:
        {
            LinesElement* tmp = dynamic_cast<LinesElement*>(temp[i]);
            s1 = QString::number((double)round(tmp->GetValue() * 10) / 10) + "Ohm |" + QString::number((double)round(tmp->GetAlpha() * 10) / 10) + "dB/m|lambda=" + QString::number((double)round(tmp->GetLambda() * 10000) / 10000);
            s3 = QString::number((double)round(tmp->GetMechanicalLength() * 10) / 10) + "mm(phys)|" + QString::number((double)round(tmp->GetElectricalLength() * 10) / 10) + "mm(electr)";
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
        if (!SystemParameters::rotate)
        {
            painter.translate((i + 2) * 40 + 20, 90);
            painter.rotate(90);
            painter.setFont(QFont("Arial", 8));
            painter.drawText(0, 0, s1);
            painter.translate(0, +15);
            painter.drawText(0, 0, s3);
        }
        else
        {
            painter.translate(90, (i + 2) * 40 + 20);
            painter.setFont(QFont("Arial", 8));
            painter.drawText(0, 0, s1);
            painter.translate(0, 15);
            painter.drawText(0, 0, s3);
        }
        s3 = "";
        painter.restore();
    }
}

void CircuitWidget::CurrentValuePaint(QPainter& painter)
{
    QString s1, s3;
    if (SystemParameters::Model != AddPoint && SystemParameters::Model != Default)
    {
        Complex z;
        Complex y;
        if (SystemParameters::index != 1)
        {
            z = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter().at(Z);
            y = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter().at(Y);
        }
        else
        {
            z = circuitElements->z;
            y = circuitElements->y;
        }
        switch (SystemParameters::Model)
        {
        case ResistorShunt:
        {
            double r1 = z.real();
            SystemParameters::rImpedanceRealCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
            double r2 = SystemParameters::impedanceRealR;
            s1 = QString::number(round((r2 - r1) * 10) / 10);
            break;
        }
        case InductionShunt:
        {
            double r1 = z.imag();
            SystemParameters::rImpedanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
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
                val /= 1e3;
                power = " uH";
            }
            else
            {
                val /= 1e6;
                power = " mH";
            }
            s1 = QString::number((double)round(val * 10) / 10) + power;
            break;
        }
        case CapacitorShunt:
        {
            double r1 = z.imag();
            SystemParameters::rImpedanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
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
                val /= 1e3;
                power = " nF";
            }
            else
            {
                val /= 1e6;
                power = " uF";
            }
            s1 = QString::number((double)round(val * 10) / 10) + power;
            break;
        }
        case ResistorParallel:
        {
            double r1 = y.real();
            SystemParameters::rAdmitanceRealCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
            double r2 = SystemParameters::admitanceRealR;
            s1 = QString::number(round(1000 / (r2 - r1) * 10) / 10);
            break;
        }
        case InductionParallel:
        {
            double r1 = y.imag();
            SystemParameters::rAdmitanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
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
                val /= 1e3;
                power = " uH";
            }
            else
            {
                val /= 1e6;
                power = " mH";
            }
            s1 = QString::number((double)round(val * 10) / 10) + power;
            break;
        }
        case CapacitorParallel:
        {
            double r1 = y.imag();
            SystemParameters::rAdmitanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
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
                val /= 1e3;
                power = " nF";
            }
            else
            {
                val /= 1e6;
                power = " uF";
            }
            s1 = QString::number((double)round(val * 10) / 10) + power;
            break;
        }
        case Line:
        {
            double RL = z.real();
            double XL = z.imag();
            SystemParameters::rImpedanceRealCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
            SystemParameters::rImpedanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
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
            double l = O * 299792458 / (M_PI * 1e9 * 2);
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
            SystemParameters::rAdmitanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
            o = atan((SystemParameters::admitanceImagR - y.imag()) / 1000 * SystemParameters::z0line);
            if (o < 0)
            {
                o += M_PI;
            }
            theta = o * 180 / M_PI;
            l = o * 299792458 / (2 * M_PI * 1e9);
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
            SystemParameters::rAdmitanceImagCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
            o = -atan(1 / ((SystemParameters::admitanceImagR - y.imag()) / 1000 * SystemParameters::z0line));
            if (o < 0)
            {
                o += M_PI;
            }
            theta = o * 180 / M_PI;
            l = o * 299792458 / (2 * M_PI * 1e9);
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
            SystemParameters::rImpedanceRealCalculation(SystemParameters::lastPointX, SystemParameters::lastPointY);
            double n = sqrt(SystemParameters::impedanceRealR / z.real());
            s1 = "1:" + QString::number(n);
            break;
        }
        }
    }
    painter.save();
    if (!SystemParameters::rotate)
    {
        painter.translate((SystemParameters::index + 1) * 40 + 20, 90);
        painter.rotate(90);
        painter.setFont(QFont("Arial", 8));
        painter.drawText(0, 0, s1);
        painter.translate(0, +15);
        painter.drawText(0, 0, s3);
    }
    else
    {
        painter.translate(90, (SystemParameters::index + 1) * 40 + 20);
        painter.setFont(QFont("Arial", 8));
        painter.drawText(0, 0, s1);
        painter.translate(0, 15);
        painter.drawText(0, 0, s3);
    }
    s3 = "";
    painter.restore();
}

/// <summary>
/// Обработка при наведении на виджет.
/// </summary>
/// <param name="event"></param>
void CircuitWidget::enterEvent(QEnterEvent* event)
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

void CircuitWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (!SystemParameters::tune && !SystemParameters::edit)
    {
        if (event->button() == Qt::LeftButton)
        {
            QPoint clickPos = event->pos();

            // Проверяем все SVG виджеты
            for (int i = 0; i < SystemParameters::svgWidgets.size(); ++i)
            {
                QSvgWidget* svgWidget = SystemParameters::svgWidgets.at(i);

                // Проверяем, попал ли клик в область SVG виджета
                if (svgWidget->geometry().contains(clickPos)&&i!=0&&i!= SystemParameters::svgWidgets.size()-1)
                {
                    SystemParameters::edit = true;
                    emit Edit(circuitElements->GetCircuitElements()[i-1]);
                    event->accept();
                    return;
                }
            }
        }

        QWidget::mouseDoubleClickEvent(event);
    }
}