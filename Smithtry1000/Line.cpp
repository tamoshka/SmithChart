#include "Line.h"

void LinesElement::SetAlpha(long double alpha)
{
	this->_alpha = alpha;
}

long double LinesElement::GetAlpha()
{
	return this->_alpha;
}

LinesElement::LinesElement(mode mode, long double value, long double frequency, Point point, map<chartMode, tuple<long double, long double>> chartParameters,
	map<parameterMode, Complex> parameters, long double electricalLength, long double mechanicalLength, long double theta, long double lambda, long double alpha) :
	VerticalLinesElement(mode, value, frequency, point, chartParameters, parameters, electricalLength, mechanicalLength, theta, lambda)
{
	this->SetAlpha(alpha);
}