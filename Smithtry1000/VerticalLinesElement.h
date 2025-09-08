#pragma once
#include "Element.h"

class VerticalLinesElement :public Element
{
private:
	double _electricalLength;
	double _mechanicalLength;
	double _lambda;
	double _theta;

public:
	void SetElectricalLength(double);
	void SetMechanicalLength(double);
	void SetTheta(double);
	void SetLambda(double);
	double GetElectricalLength();
	double GetMechanicalLength();
	double GetTheta();
	double GetLambda();
	VerticalLinesElement(mode mode, double value, double frequency, Point point, map<chartMode, tuple<double, double>> chartParameters,
		map<parameterMode, Complex> parameters, double electricalLength, double mechanicalLength, double theta, double lambda);
};