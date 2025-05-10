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

QString complex::display()
{
	QString r = QString::number(real);
	QString x = QString::number(abs(imag));
	QString num;
	//r= r.left(5);
	//x=x.left(5)

	if (imag >= 0)
		num = r + " + j" + x;
	else
		num = r + " - j" + x;

	return num;
}
