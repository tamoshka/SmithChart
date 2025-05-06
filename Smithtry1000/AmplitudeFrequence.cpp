#include "AmplitudeFrequence.h"
#include "ComplexNumber.h"

void AmplitudeFrequence::SetGamma1(float gamma1)
{
    this->gamma1 = gamma1;
}

void AmplitudeFrequence::SetGamma2(float gamma2)
{
    this->gamma2 = gamma2;
}

void AmplitudeFrequence::ReflectionCalculation()
{
    float gamma1, gamma2;
    complex R1, R2;

    //R1 = this->circuitElements[0]->;
    //R2 = this->circuitElements[this->circuitElements.size() - 1]
    //Gamma1 = (R1 - m_Z0)/(R1 + m_Z0);
    //Gamma2 = (R2 - m_Z0) / (R2 + m_Z0);
}

float AmplitudeFrequence::GetGamma1()
{
    return this->gamma1;
}

float AmplitudeFrequence::GetGamma2()
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