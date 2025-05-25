#include "SParameters.h"
SParameters::SParameters()
{
	table = new Table();
	tests = new Tests();
	grafOne = new GrafOne();
	grafTwo = new GrafTwo();
	table->show();
	tests->show();
	grafOne->show();
	grafTwo->show();
}

SParameters::~SParameters()
{

}