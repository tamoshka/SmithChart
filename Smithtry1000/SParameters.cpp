#include "SParameters.h"
#include <QString>

/// <summary>
/// Конструктор класса SParameters.
/// </summary>
/// <param name="grafOne1">GrafOne.</param>
/// <param name="grafTwo1">GrafTwo.</param>
/// <param name="d12">S12.</param>
/// <param name="d21">S21.</param>
/// <param name="d11">S11.</param>
/// <param name="d22">S22.</param>
/// <param name="t1">Таблица S-параметров.</param>
/// <param name="t2">Таблица Mag, Msg, K, mu параметров.</param>
/// <param name="set1">Настройка цветов и толщины линий.</param>
SParameters::SParameters(GrafOne& grafOne1, GrafTwo& grafTwo1, SDiagram1& d12, SDiagram1& d21, SDiagram2& d11, SDiagram2& d22, SParamTable& t1, SParamTable& t2, ColourSetting& set1)
{
	grafOne = &grafOne1;
	grafTwo = &grafTwo1;
	d1 = &d12;
	d2 = &d21;
	d3 = &d11;
	d4 = &d22;
	stable1 = &t1;
	stable2 = &t2;
	set = &set1;
}

/// <summary>
/// Деструктор класса SParameters.
/// </summary>
SParameters::~SParameters()
{

}

/// <summary>
/// Выбор отображаемых окон.
/// </summary>
void SParameters::Show()
{
	extern QString fileName;
	auto extension = fileName.toStdString();
	size_t last_dot = extension.find_last_of('.');
	extension = last_dot != string::npos ? extension.substr(last_dot + 1) : "";
	if (extension == "S1P" || extension == "s1p")
	{
		grafOne->Load();
		grafOne->show();
		d3->Load();
		d3->show();
		stable1->Load();
		stable1->show();;
	}

	else if (extension == "S2P" || extension == "s2p")
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

/// <summary>
/// Закрытие окон.
/// </summary>
void SParameters::Close()
{
	grafOne->close();
	grafTwo->close();
	d1->close();
	d2->close();
	d3->close();
	d4->close();
	stable1->close();
	stable2->close();
}