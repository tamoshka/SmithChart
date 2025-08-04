#pragma once

#include <QWidget>
#include "circuitElements.h"
#include "general.h"
#include "qcustomplot.h"
QT_BEGIN_NAMESPACE
namespace Ui { class AmplitudeFrequency; };
QT_END_NAMESPACE




const Complex I(0.0, 1.0);
struct Element2 
{
	string name;       // ��� �������� ("L", "C", "R", � �.�.)
	string conn;       // ��� ���������� ("s" - series, "p" - parallel)
	vector<double> values; // ��������� ��������
};

struct Circuit 
{
	vector<Element2> elements;
	vector<Complex> ZS;     // ��������� ���������
	vector<Complex> ZL;     // ��������� ��������
};

class AmplitudeFrequency : public QWidget
{
	Q_OBJECT

private:
	CircuitElements* circuitElements;
	double z0 = 50;
	Complex gamma1; // reflection coefficient
	Complex gamma2; // reflection coefficient
	void SetGamma1(Complex);
	void SetGamma2(Complex);
	vector<array<array<Complex, 2>, 2>> SP;
	QVector<double> freqs;
public:
	void ReflectionCalculation();
	Complex GetGamma1();
	Complex GetGamma2();
	AmplitudeFrequency(QWidget* parent = nullptr, CircuitElements* = new CircuitElements());
	void MatrixCalculation();
	void SetPoint(double[], double[], double[]);
	void SetPoint2();
	~AmplitudeFrequency();
	void calc_S2P(const Circuit&);
	Ui::AmplitudeFrequency *ui;
};
