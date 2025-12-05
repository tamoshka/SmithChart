#pragma once

#include "GrafOne.h"
#include "GrafTwo.h"
#include <QtWidgets/QApplication>
#include "SDiagram1.h"
#include "SDiagram2.h"
#include "SParamTable.h"
#include "ColourSetting.h"
#include <ui_ds/controls/organisms/windows/window/window_container.h>
using namespace ui::ds::controls::organisms::window_container;
using namespace ui::ds::controls::organisms::window_header;
/// <summary>
/// Хаб для окон связанных с S-параметрами и окна настройки визуализации.
/// </summary>
class SParameters
{
public:
    SParameters(GrafOne&, GrafTwo&, SDiagram1&, SDiagram1&, SDiagram2&, SDiagram2&, SParamTable&, SParamTable&, ColourSetting&);
    void Show();
    void Close();
    ~SParameters();
    
    ColourSetting* set;
    SDiagram1* d1;
    SDiagram1* d2;
    SDiagram2* d3;
    SDiagram2* d4;
    GrafOne* grafOne;
    GrafTwo* grafTwo;
    SParamTable* stable1;
    SParamTable* stable2;
    WindowContainer* setContainer = nullptr;
private:
    WindowContainer* grafOneContainer = nullptr;
    WindowContainer* grafTwoContainer = nullptr;
    WindowContainer* d1Container = nullptr;
    WindowContainer* d2Container = nullptr;
    WindowContainer* d3Container = nullptr;
    WindowContainer* d4Container = nullptr;
    WindowContainer* stable1Container = nullptr;
    WindowContainer* stable2Container = nullptr; 
    
    void createContainers();
};