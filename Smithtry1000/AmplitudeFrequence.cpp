#include "AmplitudeFrequence.h"

void AmplitudeFrequence::SetGamma1(complex gamma1)
{
    this->gamma1 = gamma1;
}

void AmplitudeFrequence::SetGamma2(complex gamma2)
{
    this->gamma2 = gamma2;
}

void AmplitudeFrequence::ReflectionCalculation()
{
    complex R1, R2;

    R1 = circuitElements->GetCircuitElements()[0]->GetChartParameters()[RealImpedance];
    R2 = circuitElements->GetCircuitElements()[circuitElements->GetCircuitElements().size() - 1]->GetChartParameters()[RealImpedance];
    SetGamma1((R1 - z0) / (R1 + z0));
    SetGamma2((R2 - z0) / (R2 + z0));
}

complex AmplitudeFrequence::GetGamma1()
{
    return this->gamma1;
}

complex AmplitudeFrequence::GetGamma2()
{
    return this->gamma2;
}

AmplitudeFrequence::AmplitudeFrequence(QWidget* parent, CircuitElements* circuitElements) :
    QWidget(parent)
{
    setMinimumSize(100, 100);
    this->circuitElements = circuitElements;
}

AmplitudeFrequence::~AmplitudeFrequence()
{

}