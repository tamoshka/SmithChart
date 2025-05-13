#include "AmplitudeFrequency.h"
#include "ui_AmplitudeFrequency.h"

AmplitudeFrequency::AmplitudeFrequency(QWidget *parent, CircuitElements* circuitElements)
	: QWidget(parent)
	, ui(new Ui::AmplitudeFrequency())
{
	ui->setupUi(this);
    setMinimumSize(100, 100);
    this->circuitElements = circuitElements;
}
void AmplitudeFrequency::SetGamma1(complex gamma1)
{
    this->gamma1 = gamma1;
}

void AmplitudeFrequency::SetGamma2(complex gamma2)
{
    this->gamma2 = gamma2;
}

void AmplitudeFrequency::ReflectionCalculation()
{
    complex R1, R2;

    R1 = circuitElements->GetCircuitElements()[0]->GetParameter()[Z];
    R2 = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter()[Z];
    SetGamma1((R1 - z0) / (R1 + z0));
    SetGamma2((R2 - z0) / (R2 + z0));
}

complex AmplitudeFrequency::GetGamma1()
{
    return this->gamma1;
}

complex AmplitudeFrequency::GetGamma2()
{
    return this->gamma2;
}

void AmplitudeFrequency::MatrixCalculation()
{
    int k = 0;
    double startFrequency = 0.001;
    double w;
    complex A[2][2], A1[2][2];
    double Chas[50], Znach[50];
    double f = frequency * 1e6;

    for (double freq = 0.001; freq <= 2 * f+1; freq += (2 * f - 0.001) / 49)
    {
        w = 2 * M_PI * freq;

        for (int i = 0; i < circuitElements->GetCircuitElements().size(); i++)
        {
            switch (circuitElements->GetCircuitElements()[i]->GetMode())
            {
            case ResistorShunt:
            {
                complex z(circuitElements->GetCircuitElements()[i]->GetValue(), 0);
                A1[0][0] = 1;
                A1[0][1] = z;
                A1[1][0] = 0;
                A1[1][1] = 1;
                break;
            }
            case InductionShunt:
            {
                complex z(0, w  * circuitElements->GetCircuitElements()[i]->GetValue());
                A1[0][0] = 1;
                A1[0][1] = z;
                A1[1][0] = 0;
                A1[1][1] = 1;
                break;
            }
            case CapacitorShunt:
            {
                complex z(0, 1 / (w * circuitElements->GetCircuitElements()[i]->GetValue()));
                A1[0][0] = 1;
                A1[0][1] = z;
                A1[1][0] = 0;
                A1[1][1] = 1;
                break;
            }
            case ResistorParallel:
            {
                complex z(circuitElements->GetCircuitElements()[i]->GetValue(), 0);
                complex y = complex(1, 0) / z;
                A1[0][0] = 1;
                A1[0][1] = 0;
                A1[1][0] = y;
                A1[1][1] = 1;
                break;
            }
            case InductionParallel:
            {
                complex z(0, w * circuitElements->GetCircuitElements()[i]->GetValue());
                complex y = complex(1, 0) / z;
                A1[0][0] = 1;
                A1[0][1] = 0;
                A1[1][0] = y;
                A1[1][1] = 1;
                break;
            }
            case CapacitorParallel:
            {
                complex z(0, 1 / (w * circuitElements->GetCircuitElements()[i]->GetValue()));
                complex y = complex(1, 0) / z;
                A1[0][0] = 1;
                A1[0][1] = 0;
                A1[1][0] = y;
                A1[1][1] = 1;
                break;
            }
            }
            if (i == 0)
            {
                A[0][0] = A1[0][0];
                A[0][1] = A1[0][1];
                A[1][0] = A1[1][0];
                A[1][1] = A1[1][1];
            }
            else
            {
                complex mem1 = A[0][0] * A1[0][0] + A[0][1] * A1[1][0];
                complex mem2 = A[0][0] * A1[0][1] + A[0][1] * A1[1][1];
                complex mem3 = A[1][0] * A1[0][0] + A[1][1] * A1[1][0];
                complex mem4 = A[1][0] * A1[0][1] + A[1][1] * A1[1][1];

                A[0][0] = mem1;
                A[0][1] = mem2;
                A[1][0] = mem3;
                A[1][1] = mem4;
            }
        }
        complex dT = A[0][0] + A[0][1] / complex(z0, 0) + A[1][0] * complex(z0, 0) + A[1][1];
        complex s11 = (A[0][0] + A[0][1] / complex(z0, 0) - A[1][0] * complex(z0, 0) - A[1][1]) / dT;
        complex s12 = complex(2, 0) * (A[0][0] * A[1][1] - A[0][1] * A[1][0]) / dT;
        complex s21 = complex(2, 0) / dT;
        complex s22 = (complex(-1, 0) * A[0][0] + A[0][1] / complex(z0, 0) - A[1][0] * complex(z0, 0) + A[1][1]) / dT;

        complex R2;
        complex R1(circuitElements->realFirstPoint, circuitElements->imagFirstPoint);
        R2 = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter()[Z];

        if ((R1.Re() == z0) && (R2.Re() == z0) && (R1.Im() == 0) && (R2.Im() == 0))
        {
            s11 = s11;
            s12 = s12;
            s21 = s21;
            s22 = s22;
        }
        else
        {
            SetGamma1((R1 - z0) / (R1 + z0));
            SetGamma2((R2 - z0) / (R2 + z0));
            complex sopr1(gamma1.Re(), -gamma1.Im());
            complex sopr2(gamma2.Re(), -gamma2.Im());
            double g1 = gamma1.abs(gamma1);
            double g2 = gamma2.abs(gamma2);
            complex a1 = (complex(1, 0) - sopr1) * complex(sqrt(1 - g1 * g1), 0) / complex(1 - g1, 0);
            complex a2 = (complex(1, 0) - sopr2) * complex(sqrt(1 - g2 * g2), 0) / complex(1 - g2, 0);
            complex D = (complex(1, 0) - gamma1 * s11) * (complex(1, 0) - gamma2 * s22) - gamma1 * gamma2 * s12 * s21;
            complex sopra1(a1.Re(), -a1.Im());
            complex sopra2(a2.Re(), -a2.Im());
            s11 = (sopra1 * ((complex(1, 0) - gamma2 * s22) * (s11 - sopr1)) + gamma2 * s12 * s21) / (a1 * D);
            s22 = (sopra2 * ((complex(1, 0) - gamma1 * s11) * (s22 - sopr2) + gamma1 * s12 * s21)) / (a2 * D);
            s12 = (sopra2 * s12 * complex(1 - g1 * g1, 0)) / (a1 * D);
            s21 = (sopra1 * s21 * complex(1 - g2 * g2, 0)) / (a2 * D);
        }
        Chas[k] = startFrequency;
        Znach[k] = s21.abs(s21);
        startFrequency += (2 * f - 0.001) / 49;
        k++;
    }
    SetPoint(Chas, Znach);
}

void AmplitudeFrequency::SetPoint(double x[], double y[])
{
    QVector<double> x1, y1;
    for (int i = 0; i < 50; i++)
    {
        x1.append(x[i]);
        y1.append(y[i]);
    }
    double xBegin = x[0];
    double xEnd = x[49];
    double yBegin, yEnd;
    yBegin = y[0];
    yEnd = y[0];
    for (int i = 0; i < 49; i++)
    {
        if (y[i + 1] < yBegin)
        {
            yBegin = y[i + 1];
        }
        if (y[i + 1] > yEnd)
        {
            yEnd = y[i + 1];
        }
    }
    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(yBegin, yEnd);
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x1, y1);
}

AmplitudeFrequency::~AmplitudeFrequency()
{

}
