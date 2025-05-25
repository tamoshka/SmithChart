#include "ComplexNumber.h"

complexNumber::complexNumber()
{
}

complexNumber::complexNumber(float a, float b)
{
	real = a;
	imag = b;
}

complexNumber complexNumber::operator+(complexNumber a)
{
	complexNumber b;
	b.real = real + a.real;
	b.imag = imag + a.imag;
	return b;
}

complexNumber complexNumber::operator+(double a)
{
	complexNumber b;
	b.real = real + a;
	b.imag = imag;
	return b;
}


complexNumber complexNumber::operator-(complexNumber a)
{
	complexNumber b;
	b.real = real - a.real;
	b.imag = imag - a.imag;
	return b;
}

complexNumber complexNumber::operator-(double a)
{
	complexNumber b;
	b.real = real - a;
	b.imag = imag;
	return b;
}

complexNumber complexNumber::operator*(complexNumber a)
{
	complexNumber b;
	b.real = real * a.real - imag * a.imag;
	b.imag = imag * a.real + real * a.imag;
	return b;
}

complexNumber complexNumber::operator/(complexNumber a)
{
	complexNumber b;
	b.real = (real * a.real + imag * a.imag) / (pow(a.real, 2) + pow(a.imag, 2));
	b.imag = (imag * a.real - real * a.imag) / (pow(a.real, 2) + pow(a.imag, 2));
	return b;
}

complexNumber complexNumber::inverse()
{
	complexNumber b;
	b.real = (real) / (pow(real, 2) + pow(imag, 2));
	b.imag = (-imag) / (pow(real, 2) + pow(imag, 2));
	return b;
}

double complexNumber::abs(complexNumber a)  //модуль числа
{
	return (sqrt(a.Re() * a.Re() + a.Im() * a.Im()));
}

void complexNumber::operator=(int a)
{
	real = a;
	imag = 0;
}

void complexNumber::operator=(float a)
{
	real = a;
	imag = 0;
}

void complexNumber::operator=(complexNumber a)
{
	real = a.real;
	imag = a.imag;
}

bool complexNumber::operator==(complexNumber a)
{
	if (a.real == real && a.imag == imag)
		return true;
	else
		return false;
}

bool complexNumber::operator==(int a)
{
	if (real == a && imag == 0)
		return true;
	else
		return false;
}

bool complexNumber::operator==(float a)
{
	if (real == a && imag == 0)
		return true;
	else
		return false;
}

void complexNumber::setValue(float a, float b)
{
	real = a;
	imag = b;
}

double complexNumber::Re()
{
	return this->real;
}

double complexNumber::Im()
{
	return this->imag;
}