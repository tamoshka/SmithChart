#include "Line.h"

void LinesElement::SetAlpha(double alpha)
{
	this->_alpha = alpha;
}

double LinesElement::GetAlpha()
{
	return this->_alpha;
}

LinesElement::LinesElement(mode mode, double value, double frequency, Point point, map<chartMode, tuple<double, double>> chartParameters,
	map<parameterMode, Complex> parameters, double electricalLength, double mechanicalLength, double theta, double lambda, double alpha) :
	VerticalLinesElement(mode, value, frequency, point, chartParameters, parameters, electricalLength, mechanicalLength, theta, lambda)
{
	this->SetAlpha(alpha);
}