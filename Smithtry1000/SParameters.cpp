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

SParameters::SParameters(Table& table1, Tests& tests1, GrafOne& grafOne1, GrafTwo& grafTwo1, SDiagram1& d12, SDiagram1& d21,SDiagram2& d11, SDiagram2& d22)
{
	table = &table1;
	tests = &tests1;
	grafOne = &grafOne1;
	grafTwo = &grafTwo1;
	d1 = &d12;
	d2 = &d21;
	d3 = &d11;
	d4 = &d22;
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
		d3->Load();
		d3->show();
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
		d1->Load();
		d1->show();
		d2->Load();
		d2->show();
		d3->Load();
		d3->show();
		d4->Load();
		d4->show();
	}
}