#include "ComplexNumber.h"

complex::complex()
{
}

complex::complex(float a, float b)
{
	real = a;
	imag = b;
}

complex complex::operator+(complex a)
{
	complex b;
	b.real = real + a.real;
	b.imag = imag + a.imag;
	return b;
}

complex complex::operator+(double a)
{
	complex b;
	b.real = real + a;
	b.imag = imag;
	return b;
}


complex complex::operator-(complex a)
{
	complex b;
	b.real = real - a.real;
	b.imag = imag - a.imag;
	return b;
}

complex complex::operator-(double a)
{
	complex b;
	b.real = real - a;
	b.imag = imag;
	return b;
}

complex complex::operator*(complex a)
{
	complex b;
	b.real = real * a.real - imag * a.imag;
	b.imag = imag * a.real + real * a.imag;
	return b;
}

complex complex::operator/(complex a)
{
	complex b;
	b.real = (real * a.real + imag * a.imag) / (pow(a.real, 2) + pow(a.imag, 2));
	b.imag = (imag * a.real - real * a.imag) / (pow(a.real, 2) + pow(a.imag, 2));
	return b;
}

complex complex::inverse()
{
	complex b;
	b.real = (real) / (pow(real, 2) + pow(imag, 2));
	b.imag = (-imag) / (pow(real, 2) + pow(imag, 2));
	return b;
}

double complex::abs(complex a)  //модуль числа
{
	return (sqrt(a.Re() * a.Re() + a.Im() * a.Im()));
}

void complex::operator=(int a)
{
	real = a;
	imag = 0;
}

void complex::operator=(float a)
{
	real = a;
	imag = 0;
}

void complex::operator=(complex a)
{
	real = a.real;
	imag = a.imag;
}

bool complex::operator==(complex a)
{
	if (a.real == real && a.imag == imag)
		return true;
	else
		return false;
}

bool complex::operator==(int a)
{
	if (real == a && imag == 0)
		return true;
	else
		return false;
}

bool complex::operator==(float a)
{
	if (real == a && imag == 0)
		return true;
	else
		return false;
}

void complex::setValue(float a, float b)
{
	real = a;
	imag = b;
}

double complex::Re()
{
	return this->real;
}

double complex::Im()
{
	return this->imag;
}