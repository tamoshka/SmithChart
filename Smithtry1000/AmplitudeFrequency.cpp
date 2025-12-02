#include "AmplitudeFrequency.h"
#include "systemParameters.h"
/// <summary>
/// Конструктор класса AmplitudeFrequency.
/// </summary>
/// <param name="parent"></param>
/// <param name="circuitElements">Цепь.</param>
AmplitudeFrequency::AmplitudeFrequency(QWidget *parent, CircuitElements* circuitElements)
	: QWidget(parent)
{
    setMinimumSize(400, 300);
    this->setWindowTitle(QStringLiteral(u"АЧХ"));
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    saveButton = new QPushButton(this);
    saveButton->setText(QStringLiteral(u"Сохранить"));
    gridLayout->addWidget(saveButton, 0, 0, 1, 1);
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);
    widget = new QCustomPlot(this);
    gridLayout->addWidget(widget, 1, 0, 1, 2);
    this->circuitElements = circuitElements;
    connect(saveButton, &QPushButton::clicked, this, &AmplitudeFrequency::SaveAmpFr);
}

void AmplitudeFrequency::CalculateMatrix(Complex(&first)[2][2], Complex(&second)[2][2], QList<Element*> circuit, long double w)
{
    for (int i = circuitElements->GetCircuitElements().size() - 1; i >= 0; i--)
    {
        switch (circuitElements->GetCircuitElements()[i]->GetMode())
        {
        case ResistorShunt:
        {
            Complex z(circuitElements->GetCircuitElements()[i]->GetValue(), 0);
            second[0][0] = 1;
            second[0][1] = z;
            second[1][0] = 0;
            second[1][1] = 1;
            break;
        }
        case InductionShunt:
        {
            Complex z(0, w * circuitElements->GetCircuitElements()[i]->GetValue());
            Complex y = Complex(1, 0) / z;
            second[0][0] = 1;
            second[0][1] = z;
            second[1][0] = 0;
            second[1][1] = 1;
            break;
        }
        case CapacitorShunt:
        {
            Complex y(0, w * circuitElements->GetCircuitElements()[i]->GetValue());
            Complex z = Complex(1, 0) / y;
            second[0][0] = 1;
            second[0][1] = z;
            second[1][0] = 0;
            second[1][1] = 1;
            break;
        }
        case ResistorParallel:
        {
            Complex z(circuitElements->GetCircuitElements()[i]->GetValue(), 0);
            Complex y = Complex(1, 0) / z;
            second[0][0] = 1;
            second[0][1] = 0;
            second[1][0] = y;
            second[1][1] = 1;
            break;
        }
        case InductionParallel:
        {
            Complex z(0, w * circuitElements->GetCircuitElements()[i]->GetValue());
            Complex y = Complex(1, 0) / z;
            second[0][0] = 1;
            second[0][1] = 0;
            second[1][0] = y;
            second[1][1] = 1;
            break;
        }
        case CapacitorParallel:
        {
            Complex y(0, w * circuitElements->GetCircuitElements()[i]->GetValue());
            Complex z = Complex(1, 0) / y;
            second[0][0] = 1;
            second[0][1] = 0;
            second[1][0] = y;
            second[1][1] = 1;
            break;
        }
        case Line:
        {
            LinesElement* tmp = dynamic_cast<LinesElement*>(circuitElements->GetCircuitElements()[i]);
            long double r0 = tmp->GetValue();
            long double t = tmp->GetTheta();
            long double l = t * 299792458 / (360 * 1e9) * tmp->GetElectricalLength() / tmp->GetMechanicalLength();
            long double theta = l * w / 299792458;
            second[0][0] = cos(theta);
            second[1][1] = cos(theta);
            second[0][1] = Complex(0, 1) * r0 * sin(theta);
            second[1][0] = Complex(0, sin(theta)) / r0;
            break;
        }
        case OSLine:
        {
            VerticalLinesElement* tmp = dynamic_cast<VerticalLinesElement*>(circuitElements->GetCircuitElements()[i]);
            long double r0 = tmp->GetValue();
            long double t = tmp->GetTheta();
            long double l = t * 299792458 / (360 * 1e9) * tmp->GetElectricalLength() / tmp->GetMechanicalLength();
            long double theta = l * w / 299792458;
            Complex z = Complex(0, -1) * r0 / tan(theta);
            Complex y = (long double)1 / z;
            second[0][0] = 1;
            second[0][1] = 0;
            second[1][0] = y;
            second[1][1] = 1;
            break;
        }
        case SSLine:
        {
            VerticalLinesElement* tmp = dynamic_cast<VerticalLinesElement*>(circuitElements->GetCircuitElements()[i]);
            long double r0 = tmp->GetValue();
            long double t = tmp->GetTheta();
            long double l = t * 299792458 / (360 * 1e9) * tmp->GetElectricalLength() / tmp->GetMechanicalLength();
            long double theta = l * w / 299792458;
            Complex z = Complex(0, 1) * r0 * tan(theta);
            Complex y = (long double)1 / z;
            second[0][0] = 1;
            second[0][1] = 0;
            second[1][0] = y;
            second[1][1] = 1;
            break;
        }
        case Transform:
        {
            Complex n = circuitElements->GetCircuitElements()[i]->GetValue();
            second[0][0] = n;
            second[0][1] = 0;
            second[1][0] = 0;
            second[1][1] = (long double)1 / n;
            break;
        }
        }
        if (i == circuitElements->GetCircuitElements().size() - 1)
        {
            first[0][0] = second[0][0];
            first[0][1] = second[0][1];
            first[1][0] = second[1][0];
            first[1][1] = second[1][1];
        }
        else
        {
            Complex mem1 = first[0][0] * second[0][0] + first[0][1] * second[1][0];
            Complex mem2 = first[0][0] * second[0][1] + first[0][1] * second[1][1];
            Complex mem3 = first[1][0] * second[0][0] + first[1][1] * second[1][0];
            Complex mem4 = first[1][0] * second[0][1] + first[1][1] * second[1][1];

            first[0][0] = mem1;
            first[0][1] = mem2;
            first[1][0] = mem3;
            first[1][1] = mem4;
        }
    }
}

/// <summary>
/// Расчёт s-параметров.
/// </summary>
void AmplitudeFrequency::MatrixCalculation()
{
    int k = 0;
    long double startFrequency = 1;
    long double w;
    Complex A[2][2], A1[2][2];
    long double Chas[100], Znach11[100], Znach21[100], Znach22[100], Znach12[100];
    long double f = circuitElements->frequencyFirstPoint;
    bool flag = false;
    for (long double freq = 1e8; freq <= 3e9; freq += (3e9 - 1e8) / 99)
    {
        w = 2 * M_PI * freq;

        CalculateMatrix(A, A1, circuitElements->GetCircuitElements(), w);
        Complex z0 = SystemParameters::z0;
        Complex dT = A[0][0] + A[0][1] / z0 + A[1][0] * z0 + A[1][1];
        Complex s11 = (A[0][0] + A[0][1] / z0 - A[1][0] * z0 - A[1][1]) / dT;
        Complex s12 = (long double)(2) * (A[0][0] * A[1][1] - A[0][1] * A[1][0]) / dT;
        Complex s21 = (long double)(2) / dT;
        Complex s22 = ((long double)(-1) * A[0][0] + A[0][1] / z0 - A[1][0] * z0 + A[1][1]) / dT;

        Complex R1(circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter()[Z].real(), -circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter()[Z].imag());
        Complex R2(circuitElements->z.real(), circuitElements->z.imag());
        Complex s110, s220, s120, s210;

        if ((R1 == z0) || (R2 == z0))
        {
            s11 = s11;
            s12 = s12;
            s21 = s21;
            s22 = s22;
        }
        else
        {
            Complex gamma1=(R1 - z0) / (R1 + z0);
            Complex gamma2=(R2 - z0) / (R2 + z0);
            Complex sopr1(gamma1.real(), -gamma1.imag());
            Complex sopr2(gamma2.real(), -gamma2.imag());
            long double g1 = abs(gamma1);
            long double g2 = abs(gamma2);
            Complex a1 = ((long double)(1) - sopr1) * sqrt(1-pow(g1,2)) / abs((long double)(1)-gamma1);
            Complex a2 = ((long double)(1) - sopr2) * sqrt(1 - pow(g2, 2)) / abs((long double)(1) - gamma2);
            Complex D = ((long double)(1) - gamma1 * s11) * ((long double)(1) - gamma2 * s22) - gamma1 * gamma2 * s12 * s21;
            Complex sopra1(a1.real(), -a1.imag());
            Complex sopra2(a2.real(), -a2.imag());
            s110 = (sopra1 * (((long double)(1) - gamma2 * s22) * (s11 - sopr1) + gamma2 * s12 * s21)) / (a1 * D);
            s220 = (sopra2 * (((long double)(1) - gamma1 * s11) * (s22 - sopr2) + gamma1 * s12 * s21)) / (a2 * D);
            s120 = (sopra2 * s12 * (1-pow(g1,2))) / (a1 * D);
            s210 = (sopra1 * s21 * (1 - pow(g2, 2))) / (a2 * D);
        }
        Chas[k] = freq;
        Znach21[k] = abs(s210);
        Znach11[k] = abs(s110);
        Znach22[k] = abs(s220);
        Znach12[k] = abs(s120);
        k++;
    }
    SetPoint(Chas, Znach11, Znach21);
}

/// <summary>
/// Построение графика АЧХ.
/// </summary>
/// <param name="x">Частота.</param>
/// <param name="y">S11.</param>
/// <param name="z">S21.</param>
void AmplitudeFrequency::SetPoint(long double x[], long double y[], long double z[])
{
    widget->clearGraphs();
    QVector<double> x1, y1, z1;
    for (int i = 0; i < 100; i++)
    {
        x1.append(x[i]);
        y1.append(y[i]);
        z1.append(z[i]);
    }
    long double xBegin = x1[0];
    long double xEnd = x1[99];
    long double yBegin, yEnd;
    long double zBegin, zEnd;
    zBegin = z1[0];
    zEnd = z1[0];
    yBegin = y1[0];
    yEnd = y1[0];
    for (int i = 0; i < 99; i++)
    {
        if (y1[i + 1] < yBegin)
        {
            yBegin = y1[i + 1];
        }
        if (y1[i + 1] > yEnd)
        {
            yEnd = y1[i + 1];
        }
    }
    for (int i = 0; i < 99; i++)
    {
        if (z1[i + 1] < zBegin)
        {
            zBegin = z1[i + 1];
        }
        if (z1[i + 1] > zEnd)
        {
            zEnd = z1[i + 1];
        }
    }
    widget->xAxis->setRange(xBegin, xEnd);
    widget->xAxis->setLabel(QStringLiteral(u"Частота в Гц"));
    widget->yAxis->setRange(0, 1);
    widget->yAxis->setLabel(QStringLiteral(u"S11 в разах"));
    widget->yAxis2->setRange(0, 1);
    widget->yAxis2->setLabel(QStringLiteral(u"S21 в разах"));
    widget->yAxis2->setVisible(true);
    QPen pen1(SystemParameters::ampS11Color, SystemParameters::ampFrline[0]);
    widget->setInteraction(QCP::iRangeZoom, true);
    widget->setInteraction(QCP::iRangeDrag, true);
    widget->addGraph(widget->xAxis, widget->yAxis2);
    widget->graph(0)->addData(x1, y1);
    widget->graph(0)->setPen(pen1);
    widget->addGraph(widget->xAxis, widget->yAxis);
    widget->graph(1)->addData(x1, z1);
    QPen pen(SystemParameters::ampS21Color, SystemParameters::ampFrline[1]);
    widget->graph(1)->setPen(pen);
    widget->replot();

    widget->setInteraction(QCP::iRangeZoom, true);
    widget->setInteraction(QCP::iRangeDrag, true);
    QList<QCPAxis*> axises;
    axises.append(widget->xAxis);
    axises.append(widget->yAxis);
    axises.append(widget->yAxis2);
    widget->axisRect()->setRangeDragAxes(axises);
    widget->axisRect()->setRangeZoomAxes(axises);
}

void AmplitudeFrequency::Clear()
{
    widget->clearGraphs();
    widget->replot();
}

/// <summary>
/// Сохранение изображения графика.
/// </summary>
void AmplitudeFrequency::SaveAmpFr()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save the graph", QDir::homePath() + "/graph.png", "PNG Files (*.png);;JPEG Files (*.jpg);;PDF Files (*.pdf)");

    if (!fileName.isEmpty())
    {
        bool success = false;

        if (fileName.endsWith(".png", Qt::CaseInsensitive))
        {
            success = widget->savePng(fileName, widget->width() * 2, widget->height() * 2, 2.0);
        }
        else if (fileName.endsWith(".jpg", Qt::CaseInsensitive))
        {
            success = widget->saveJpg(fileName, widget->width(), widget->height());
        }
        else if (fileName.endsWith(".pdf", Qt::CaseInsensitive))
        {
            success = widget->savePdf(fileName);
        }

        if (success)
        {
            QMessageBox::information(this, "Success", QString("The graph is saved to a file:\n%1").arg(fileName));
        }
        else
        {
            QMessageBox::warning(this, "Error", "Couldn't save graph!");
        }
    }
}

/// <summary>
/// Деструктор класса AmplitudeFrequency.
/// </summary>
AmplitudeFrequency::~AmplitudeFrequency()
{

}