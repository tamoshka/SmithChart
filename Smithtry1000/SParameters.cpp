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

SParameters::SParameters(GrafOne& grafOne1, GrafTwo& grafTwo1, SDiagram1& d12, SDiagram1& d21,SDiagram2& d11, SDiagram2& d22, SParamTable& t1, SParamTable& t2)
{
	grafOne = &grafOne1;
	grafTwo = &grafTwo1;
	d1 = &d12;
	d2 = &d21;
	d3 = &d11;
	d4 = &d22;
	stable1 = &t1;
	stable2 = &t2;
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
		d3->Load();
		d3->show();
		stable1->Load();
		stable1->show();;
	}

	else if (get_extension4(fileName.toStdString()) == "S2P" || get_extension4(fileName.toStdString()) == "s2p")
	{
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
		stable1->Load();
		stable1->show();
		stable2->Load();
		stable2->show();
	}
}