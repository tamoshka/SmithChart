cmake_minimum_required(VERSION 3.16)
project(Smithtry1000 LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
        SvgWidgets
        PrintSupport
        Graphs
)
qt_standard_project_setup()

set(PROJECT_SOURCES
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
        Qt::SvgWidgets
        Qt::PrintSupport
        Qt::Graphs
)

