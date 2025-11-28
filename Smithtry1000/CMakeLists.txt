cmake_minimum_required(VERSION 3.16)
project(smith-chart-tool LANGUAGES CXX)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/qt.cmake")
    include(qt.cmake)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-D_WIN32_DCOM)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets PrintSupport SvgWidgets)

# Если qt.cmake включает qt_standard_project_setup(), то используем его
# Иначе настраиваем вручную
if(COMMAND qt_standard_project_setup)
    qt_standard_project_setup()
else()
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)
endif()

# Добавим путь к заголовочным файлам
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Все исходные файлы проекта
    set(PROJECT_SOURCES
    awr_interface.h
    AWR.cpp
    AWRExportThread.h
    AWRExportThread.cpp
    KeyboardDialog.h
    KeyboardDialog.cpp
    systemParameters.h
    systemParameters.cpp
    general.h
    ElementFactory.h
    ElementFactory.cpp
    Element.h
    Element.cpp
    EditWidget.ui
    EditWidget.h
    EditWidget.cpp
    PreSaveDialog.h
    PreSaveDialog.cpp
    main.cpp
    Smithtry1000.ui
    Smithtry1000.h
    Smithtry1000.cpp
    circuitWidget.h
    circuitWidget.cpp
    Resources/FirstTime.qrc
    renderarea.h
    renderarea.cpp
    frequencyDialog.h
    frequencyDialog.cpp
    circuitElements.h
    circuitElements.cpp
    qcustomplot.h
    qcustomplot.cpp
    AmplitudeFrequency.ui
    AmplitudeFrequency.h
    AmplitudeFrequency.cpp
    Timedes.h
    S2p.h
    S2p.cpp
    GrafOne.ui
    GrafOne.h
    GrafOne.cpp
    GrafTwo.ui
    GrafTwo.h
    GrafTwo.cpp
    SParameters.h
    SParameters.cpp
    ExportNetlist.ui
    ExportNetlist.h
    ExportNetlist.cpp
    SDiagram1.ui
    SDiagram1.h
    SDiagram1.cpp
    SDiagram2.ui
    SDiagram2.h
    SaveDialog.ui
    SaveDialog.h
    SaveDialog.cpp
    SDiagram2.cpp
    SParamTable.ui
    SParamTable.h
    SParamTable.cpp
    ColourSetting.ui
    ColourSetting.h
    ColourSetting.cpp
    CirclesWidget.ui
    CirclesWidget.h
    CirclesWidget.cpp
    TuneWidget.ui
    TuneWidget.h
    TuneWidget.cpp
    Line.h
    Line.cpp
    LinesDialog.h
    LinesDialog.cpp
    VerticalLinesElement.h
    VerticalLinesElement.cpp
    VerticalLinesDialog.h
    VerticalLinesDialog.cpp
)

# Ресурсы
set(UI_RESOURCES
    Resources/FirstTime.qrc
)

# Включаем автоматическую обработку ресурсов
set(CMAKE_AUTORCC ON)

# Создание исполняемого файла
if(COMMAND qt_add_executable)
    qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
else()
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
endif()

# Свойства для Windows
set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Svg
    Qt6::PrintSupport
    Qt6::SvgWidgets
)
