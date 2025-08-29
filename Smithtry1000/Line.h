#pragma once
#include "VerticalLinesElement.h"

class LinesElement :public VerticalLinesElement
{
private:
	double _alpha;

public:
	void SetAlpha(double);
	double GetAlpha();
	LinesElement(mode mode, double value, double frequency, Point point, map<chartMode, tuple<double, double>> chartParameters,
		map<parameterMode, Complex> parameters, double electricalLength, double mechanicalLength, double theta, double lambda, double alpha);
};