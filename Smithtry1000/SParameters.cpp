#include "SParameters.h"
#include <QString>
#include <QVBoxLayout>

/// <summary>
/// Конструктор класса SParameters.
/// </summary>
SParameters::SParameters(GrafOne& grafOne1, GrafTwo& grafTwo1, SDiagram1& d12, SDiagram1& d21, SDiagram2& d11, SDiagram2& d22, SParamTable& t1, SParamTable& t2, ColourSetting& set1)
    : grafOne(&grafOne1), grafTwo(&grafTwo1),d1(&d12), d2(&d21), d3(&d11), d4(&d22),stable1(&t1), stable2(&t2), set(&set1)
{

    createContainers();
}

void SParameters::createContainers()
{
    grafOneContainer = new WindowContainer(QString("S-Parameters Graph One"),grafOne,WindowHeader::ShowButtons(WindowHeader::ShowButton::All),nullptr);
    grafTwoContainer = new WindowContainer(QString("S-Parameters Graph Two"),grafTwo,WindowHeader::ShowButtons(WindowHeader::ShowButton::All),nullptr);
    d1Container = new WindowContainer(QString("S12 Diagram"),d1,WindowHeader::ShowButtons(WindowHeader::ShowButton::All),nullptr);
    d2Container = new WindowContainer(QString("S21 Diagram"),d2,WindowHeader::ShowButtons(WindowHeader::ShowButton::All),nullptr);
    d3Container = new WindowContainer(QString("S11 Diagram"),d3,WindowHeader::ShowButtons(WindowHeader::ShowButton::All),nullptr);
    d4Container = new WindowContainer(QString("S22 Diagram"),d4,WindowHeader::ShowButtons(WindowHeader::ShowButton::All),nullptr);
    stable1Container = new WindowContainer(QString("S-Parameters Table"),stable1,WindowHeader::ShowButtons(WindowHeader::ShowButton::All),nullptr);
    stable2Container = new WindowContainer(QString("Mag/Msg/K/mu Parameters Table"),stable2,WindowHeader::ShowButtons(WindowHeader::ShowButton::All),nullptr);
    setContainer = new WindowContainer(QString("Color Settings"),set,WindowHeader::ShowButtons(WindowHeader::ShowButton::All),nullptr);
}

/// <summary>
/// Выбор отображаемых окон.
/// </summary>
void SParameters::Show()
{
    extern QString fileName;
    auto extension = fileName.toStdString();
    size_t last_dot = extension.find_last_of('.');
    extension = last_dot != std::string::npos ? extension.substr(last_dot + 1) : "";
    
    if (extension == "S1P" || extension == "s1p")
    {
        grafOne->Load();
        d3->Load();
        stable1->Load();
        
        if (grafOneContainer) grafOneContainer->show();
        if (d3Container) d3Container->show();
        if (stable1Container) stable1Container->show();
    }
    else if (extension == "S2P" || extension == "s2p")
    {
        grafOne->Load();
        grafTwo->Load();
        d1->Load();
        d2->Load();
        d3->Load();
        d4->Load();
        stable1->Load();
        stable2->Load();
        
        if (grafOneContainer) grafOneContainer->show();
        if (grafTwoContainer) grafTwoContainer->show();
        if (d1Container) d1Container->show();
        if (d2Container) d2Container->show();
        if (d3Container) d3Container->show();
        if (d4Container) d4Container->show();
        if (stable1Container) stable1Container->show();
        if (stable2Container) stable2Container->show();
    }
}

/// <summary>
/// Закрытие окон.
/// </summary>
void SParameters::Close()
{
    if (grafOneContainer) grafOneContainer->close();
    if (grafTwoContainer) grafTwoContainer->close();
    if (d1Container) d1Container->close();
    if (d2Container) d2Container->close();
    if (d3Container) d3Container->close();
    if (d4Container) d4Container->close();
    if (stable1Container) stable1Container->close();
    if (stable2Container) stable2Container->close();
    if (setContainer) setContainer->close();
}

SParameters::~SParameters()
{
    delete grafOneContainer;
    delete grafTwoContainer;
    delete d1Container;
    delete d2Container;
    delete d3Container;
    delete d4Container;
    delete stable1Container;
    delete stable2Container;
    delete setContainer;
}