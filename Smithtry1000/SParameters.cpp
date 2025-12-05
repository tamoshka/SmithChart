#include "SParameters.h"
#include <QString>
#include <QVBoxLayout>

/// <summary>
/// Конструктор класса SParameters.
/// </summary>
SParameters::SParameters(GrafOne& grafOne1, GrafTwo& grafTwo1, SDiagram1& d12, SDiagram1& d21, SDiagram2& d11, SDiagram2& d22, SParamTable& t1, SParamTable& t2, ColourSetting& set1)
    : set(&set1), d1(&d12), d2(&d21), d3(&d11), d4(&d22), grafOne(&grafOne1), grafTwo(&grafTwo1),stable1(&t1), stable2(&t2)
{

    createContainers();
}

void SParameters::createContainers()
{
    grafOneContainer = new WindowContainer(QString("S-Parameters Graph One"),grafOne);
    grafTwoContainer = new WindowContainer(QString("S-Parameters Graph Two"),grafTwo);
    d1Container = new WindowContainer(QString("S12 Diagram"),d1);
    d2Container = new WindowContainer(QString("S21 Diagram"),d2);
    d3Container = new WindowContainer(QString("S11 Diagram"),d3);
    d4Container = new WindowContainer(QString("S22 Diagram"),d4);
    stable1Container = new WindowContainer(QString("S-Parameters Table"),stable1);
    stable2Container = new WindowContainer(QString("Mag/Msg/K/mu Parameters Table"),stable2);
    setContainer = new WindowContainer(QString("Color Settings"),set);
    d1Container->setFixedSize(500,500);
    d1Container->setMinimumSize(500,500);
    d1Container->setMaximumSize(900,900);
    d2Container->setFixedSize(500,500);
    d2Container->setMinimumSize(500,500);
    d2Container->setMaximumSize(900,900);
    d3Container->setFixedSize(500,500);
    d3Container->setMinimumSize(500,500);
    d3Container->setMaximumSize(900,900);
    d4Container->setFixedSize(500,500);
    d4Container->setMinimumSize(500,500);
    d4Container->setMaximumSize(900,900);
    setContainer->setMinimumSize(500,500);
    setContainer->setMaximumSize(770,600);
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