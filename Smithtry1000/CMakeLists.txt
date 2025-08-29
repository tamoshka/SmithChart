cmake_minimum_required(VERSION 3.16)
project(Smithtry1000 LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
        Svg
        PrintSupport
)
qt_standard_project_setup()

# Добавим путь к заголовочным файлам
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(PROJECT_SOURCES
    systemParameters.h
    systemParameters.cpp
    general.h
    Element.h
    Element.cpp
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
    ComplexNumber.h
    ComplexNumber.cpp
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
    SDiagram2.cpp
    SParamTable.ui
    SParamTable.h
    SParamTable.cpp
    ColourSetting.ui
    ColourSetting.h
    ColourSetting.cpp
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

SET(UI_RESOURCES
    Resources/FirstTime.qrc
)

set(CMAKE_AUTORCC ON)

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Svg
        Qt::PrintSupport
)