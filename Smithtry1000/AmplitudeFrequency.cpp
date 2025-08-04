#include "AmplitudeFrequency.h"
#include "ui_AmplitudeFrequency.h"
const double Z0 = 50;
const double c = 299792458.0;
const double F0 = 1e9;


void AmplitudeFrequency::calc_S2P(const Circuit& circuit)
{

    /*for (int i = 0; i < 100; i++) {
        freqs.push_back(0.1 + i * 0.019);
    }
    size_t nf = freqs.size();
    size_t ne = circuit.elements.size();
    bool use_ZS = !circuit.ZS.empty();
    bool use_ZL = !circuit.ZL.empty();

    for (size_t kf = 0; kf < nf-1; ++kf) {
        double w = 2 * M_PI * freqs[kf];
        Complex R1 = use_ZS ? circuit.ZS[kf] : Complex(50.0, 0.0);
        Complex R2 = use_ZL ? circuit.ZL[kf] : Complex(100.0, 0.0);

        array<array<Complex, 2>, 2> A = { {
            {{1.0, 0.0}},
            {{0.0, 1.0}}
        } };

        for (size_t ke = 0; ke < ne-1; ++ke) {
            const auto& elem = circuit.elements[ke];
            array<array<Complex, 2>, 2> A1 = { {
                {{1.0, 0.0}},
                {{0.0, 1.0}}
            } };

            Complex z, y;
            if (elem.name == "L") {
                z = I * w * elem.values[0];
                y = 1.0 / z;
            }
            // ... (остальные элементы как в предыдущем коде)

            // Исправленное перемножение матриц
            array<array<Complex, 2>, 2> A_new = { {
                {{0.0, 0.0}},
                {{0.0, 0.0}}
            } };

            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    A_new[i][j] = A[i][0] * A1[0][j] + A[i][1] * A1[1][j];
                }
            }
            A = A_new;
        }

        // ABCD -> S-параметры
        Complex denom = A[0][0] + A[0][1] / Z0 + A[1][0] * Z0 + A[1][1];
        Complex s11 = (A[0][0] + A[0][1] / Z0 - A[1][0] * Z0 - A[1][1]) / denom;
        Complex s12 = 2.0 * (A[0][0] * A[1][1] - A[0][1] * A[1][0]) / denom;
        Complex s21 = 2.0 / denom;
        Complex s22 = (-A[0][0] + A[0][1] / Z0 - A[1][0] * Z0 + A[1][1]) / denom;

        // Коррекция для нагрузок
        if (abs(R1 - Z0) > 1e-9 || abs(R2 - Z0) > 1e-9) {
            Complex Gamma1 = (R1 - Z0) / (R1 + Z0);
            Complex Gamma2 = (R2 - Z0) / (R2 + Z0);

            // Исправленное вычисление корней
            Complex sqrt1 = sqrt(Complex(1.0 - norm(Gamma1), 0.0));
            Complex sqrt2 = sqrt(Complex(1.0 - norm(Gamma2), 0.0));

            Complex a1 = (1.0 - conj(Gamma1)) * sqrt1 / abs(1.0 - Gamma1);
            Complex a2 = (1.0 - conj(Gamma2)) * sqrt2 / abs(1.0 - Gamma2);

            Complex D = (1.0 - Gamma1 * s11) * (1.0 - Gamma2 * s22) - Gamma1 * Gamma2 * s12 * s21;

            s11 = (conj(a1) * ((1.0 - Gamma2 * s22) * (s11 - conj(Gamma1)) + Gamma2 * s12 * s21) / (a1 * D));
            s22 = (conj(a2) * ((1.0 - Gamma1 * s11) * (s22 - conj(Gamma2)) + Gamma1 * s12 * s21) / (a2 * D));
            s12 = (conj(a2) * s12 * (1.0 - norm(Gamma1))) / (a1 * D);
            s21 = (conj(a1) * s21 * (1.0 - norm(Gamma2))) / (a2 * D);
        }

        // Исправленная инициализация массива для push_back
        array<array<Complex, 2>, 2> s_matrix;
        s_matrix[0] = { {s11, s12} };
        s_matrix[1] = { {s21, s22} };
        SP.push_back(s_matrix);
    }
    SetPoint2();*/
}

AmplitudeFrequency::AmplitudeFrequency(QWidget *parent, CircuitElements* circuitElements)
	: QWidget(parent)
	, ui(new Ui::AmplitudeFrequency())
{
	ui->setupUi(this);
    setMinimumSize(100, 100);
    this->circuitElements = circuitElements;
}


void AmplitudeFrequency::SetGamma1(Complex gamma1)
{
    this->gamma1 = gamma1;
}

void AmplitudeFrequency::SetGamma2(Complex gamma2)
{
    this->gamma2 = gamma2;
}

void AmplitudeFrequency::ReflectionCalculation()
{
    Complex R1, R2;

    R1 = circuitElements->GetCircuitElements()[0]->GetParameter()[Z];
    R2 = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter()[Z];
    SetGamma1((R1 - z0) / (R1 + z0));
    SetGamma2((R2 - z0) / (R2 + z0));
}

Complex AmplitudeFrequency::GetGamma1()
{
    return this->gamma1;
}

Complex AmplitudeFrequency::GetGamma2()
{
    return this->gamma2;
}

void AmplitudeFrequency::MatrixCalculation()
{
    int k = 0;
    double startFrequency = 1;
    double w;
    Complex A[2][2], A1[2][2];
    double Chas[50], Znach[50], Znach2[50];
    double f = frequency * 1e6;

    for (double freq = 1; freq <= 2 * f+1; freq += (2 * f - 1) / 49)
    {
        w = 2 * M_PI * freq;

        for (int i = 0; i < circuitElements->GetCircuitElements().size(); i++)
        {
            switch (circuitElements->GetCircuitElements()[i]->GetMode())
            {
            case ResistorShunt:
            {
                Complex z(circuitElements->GetCircuitElements()[i]->GetValue(), 0);
                A1[0][0] = 1;
                A1[0][1] = z;
                A1[1][0] = 0;
                A1[1][1] = 1;
                break;
            }
            case InductionShunt:
            {
                Complex z(0, w  * circuitElements->GetCircuitElements()[i]->GetValue());
                Complex y = Complex(1, 0) / z;
                A1[0][0] = 1;
                A1[0][1] = z;
                A1[1][0] = 0;
                A1[1][1] = 1;
                break;
            }
            case CapacitorShunt:
            {
                Complex y(0, w * circuitElements->GetCircuitElements()[i]->GetValue());
                Complex z = Complex(1, 0) / y;
                A1[0][0] = 1;
                A1[0][1] = z;
                A1[1][0] = 0;
                A1[1][1] = 1;
                break;
            }
            case ResistorParallel:
            {
                Complex z(circuitElements->GetCircuitElements()[i]->GetValue(), 0);
                Complex y = Complex(1, 0) /z;
                A1[0][0] = 1;
                A1[0][1] = 0;
                A1[1][0] = y;
                A1[1][1] = 1;
                break;
            }
            case InductionParallel:
            {
                Complex z(0, w * circuitElements->GetCircuitElements()[i]->GetValue());
                Complex y = Complex(1,0) / z;
                A1[0][0] = 1;
                A1[0][1] = 0;
                A1[1][0] = y;
                A1[1][1] = 1;
                break;
            }
            case CapacitorParallel:
            {
                Complex y(0, w * circuitElements->GetCircuitElements()[i]->GetValue());
                Complex z = Complex(1, 0) / y;
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
                Complex mem1 = A[0][0] * A1[0][0] + A[0][1] * A1[1][0];
                Complex mem2 = A[0][0] * A1[0][1] + A[0][1] * A1[1][1];
                Complex mem3 = A[1][0] * A1[0][0] + A[1][1] * A1[1][0];
                Complex mem4 = A[1][0] * A1[0][1] + A[1][1] * A1[1][1];

                A[0][0] = mem1;
                A[0][1] = mem2;
                A[1][0] = mem3;
                A[1][1] = mem4;
            }
        }
        Complex dT = A[0][0] + A[0][1] / z0 + A[1][0] * z0 + A[1][1];
        Complex s11 = (A[0][0] + A[0][1] / z0 - A[1][0] * z0 - A[1][1]) / dT;
        Complex s12 = (double)(2) * (A[0][0] * A[1][1] - A[0][1] * A[1][0]) / dT;
        Complex s21 = (double)(2) / dT;
        Complex s22 = ((double)(-1) * A[0][0] + A[0][1] / z0 - A[1][0] * z0 + A[1][1]) / dT;

        Complex R2;
        Complex R1;   
        R1 = circuitElements->realFirstPoint;
        R2 = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetParameter()[Z].real();

        if ((R1.real() == z0) && (R2.real() == z0))
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
            Complex sopr1(gamma1.real(), -gamma1.imag());
            Complex sopr2(gamma2.real(), -gamma2.imag());
            double g1 = abs(gamma1);
            double g2 = abs(gamma2);
            Complex a1 = ((double)(1) - sopr1) * sqrt(1-pow(g1,2)) / abs((double)(1)-gamma1);
            Complex a2 = ((double)(1) - sopr2) * sqrt(1 - pow(g2, 2)) / abs((double)(1) - gamma2);
            Complex D = ((double)(1) - gamma1 * s11) * ((double)(1) - gamma2 * s22) - gamma1 * gamma2 * s12 * s21;
            Complex sopra1(a1.real(), -a1.imag());
            Complex sopra2(a2.real(), -a2.imag());
            s11 = (sopra1 * (((double)(1) - gamma2 * s22) * (s11 - sopr1) + gamma2 * s12 * s21)) / (a1 * D);
            s22 = (sopra2 * (((double)(1) - gamma1 * s11) * (s22 - sopr2) + gamma1 * s12 * s21)) / (a2 * D);
            s12 = (sopra2 * s12 * (1-pow(g1,2))) / (a1 * D);
            s21 = (sopra1 * s21 * (1 - pow(g2, 2))) / (a2 * D);
        }
        Chas[k] = freq;
        Znach[k] = abs(s21);
        Znach2[k] = abs(s11);
        k++;
    }
    SetPoint(Chas, Znach, Znach2);
}

void AmplitudeFrequency::SetPoint(double x[], double y[], double z[])
{
    ui->widget->clearGraphs();
    QVector<double> x1, y1, z1;
    for (int i = 0; i < 50; i++)
    {
        x1.append(x[i]);
        y1.append(y[i]);
        z1.append(z[i]);
    }
    double xBegin = x1[0];
    double xEnd = x1[49];
    double yBegin, yEnd;
    double zBegin, zEnd;
    zBegin = z1[0];
    zEnd = z1[0];
    yBegin = y1[0];
    yEnd = y1[0];
    for (int i = 0; i < 49; i++)
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
    for (int i = 0; i < 49; i++)
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
    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->xAxis->setLabel("f[Hz]");
    ui->widget->yAxis->setRange(0, 1);
    ui->widget->yAxis->setLabel("S11 in dB");
    ui->widget->yAxis2->setRange(0, 1);
    ui->widget->yAxis2->setLabel("S21 in dB");
    ui->widget->yAxis2->setVisible(true);
    QPen pen1(Qt::blue);
    ui->widget->addGraph(ui->widget->xAxis, ui->widget->yAxis2);
    ui->widget->graph(0)->addData(x1, y1);
    ui->widget->graph(0)->setPen(pen1);
    ui->widget->addGraph(ui->widget->xAxis, ui->widget->yAxis);
    ui->widget->graph(1)->addData(x1, z1);
    QPen pen(Qt::red);
    ui->widget->graph(1)->setPen(pen);
    ui->widget->replot();
}

void AmplitudeFrequency::SetPoint2()
{
    QVector<double> x1, y1;
    QVector<double> s21_dB;
    for (const auto& s_matrix : SP) {
        // Извлекаем S21 (элемент [1][0])
        Complex s21 = s_matrix[1][0];

        // Вычисляем амплитуду в децибелах: 20*log10(|s21|)
        double magnitude = std::abs(s21);
        double dB = 20.0 * std::log10(magnitude); // Защита от log10(0)

        s21_dB.append(dB);
    }

    x1 = s21_dB;
    y1 = freqs;
    double xBegin = x1[0];
    double xEnd = x1[98];
    double yBegin, yEnd;
    yBegin = y1[0];
    yEnd = y1[0];
    for (int i = 0; i < 98; i++)
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
    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(yBegin, yEnd);
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x1, y1);
}

AmplitudeFrequency::~AmplitudeFrequency()
{

}
