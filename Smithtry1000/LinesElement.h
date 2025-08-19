#pragma once
#include "Element.h"

class LinesElement :public Element
{
private:
	double _length;
	double _theta;
public:
	void SetLength(double);
	void SetTheta(double);
	double GetLength();
	double GetTheta();
	LinesElement(mode mode, double value, double frequency, Point point, map<chartMode, tuple<double, double>> chartParameters, map<parameterMode, Complex> parameters, double length, double theta);
};