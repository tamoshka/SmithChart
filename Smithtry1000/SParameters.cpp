#include "SParameters.h"

string get_extension4(string path) {

	size_t last_slash = path.find_last_of("/\\");
	string filename;
	if (last_slash != string::npos) {
		filename = path.substr(last_slash + 1);
	}
	else {
		filename = path;
	}

	size_t last_dot = filename.find_last_of('.');

	if (last_dot != string::npos && last_dot != 0) {
		return filename.substr(last_dot + 1);
	}

	return "";
}

SParameters::SParameters(Table& table1, Tests& tests1, GrafOne& grafOne1, GrafTwo& grafTwo1, S11Param& g31, S22Param& g41, S12Param& g51, S21Param& g61)
{
	table = &table1;
	tests = &tests1;
	grafOne = &grafOne1;
	grafTwo = &grafTwo1;
	g3 = &g31;
	g4 = &g41;
	g5 = &g51;
	g6 = &g61;
}

SParameters::~SParameters()
{

}

void SParameters::Show()
{
	if (get_extension4(fileName.toStdString()) == "S1P" || get_extension4(fileName.toStdString()) == "s1p")
	{
		grafOne->Load();
		grafOne->show();
		tests->Load();
		tests->show();
		g3->Load();
		g3->show();
	}

	else if (get_extension4(fileName.toStdString()) == "S2P" || get_extension4(fileName.toStdString()) == "s2p")
	{
		table->Load();
		table->show();
		tests->Load();
		tests->show();
		grafOne->Load();
		grafOne->show();
		grafTwo->Load();
		grafTwo->show();
		g3->Load();
		g3->show();
		g4->Load();
		g4->show();
		g5->Load();
		g5->show();
		g6->Load();
		g6->show();
	}
}