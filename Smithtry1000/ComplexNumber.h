#pragma once
#include <QString>

class complex {
private:
    float real, imag;

public:
    complex();
    complex(float a, float b);
    complex operator + (complex a);
    complex operator + (double a);
    complex operator - (complex a);
    complex operator - (double a);
    complex operator * (complex a);
    complex operator /(complex a);
    complex inverse();
    void operator =(int a);
    void operator =(float a);
    void operator =(complex a);
    bool operator ==(complex a);
    bool operator ==(int a);
    bool operator ==(float a);
    void setValue(float a, float b);

    QString display();
};