#pragma once
#include <QString>

class complexNumber {
private:
    float real, imag;

public:
    complexNumber();
    complexNumber(float a, float b);
    complexNumber operator + (complexNumber a);
    complexNumber operator + (double a);
    complexNumber operator - (complexNumber a);
    complexNumber operator - (double a);
    complexNumber operator * (complexNumber a);
    complexNumber operator /(complexNumber a);
    complexNumber inverse();
    double abs(complexNumber a);
    void operator =(int a);
    void operator =(float a);
    void operator =(complexNumber a);
    bool operator ==(complexNumber a);
    bool operator ==(int a);
    bool operator ==(float a);
    void setValue(float a, float b);
    double Re();
    double Im();
};