cmake_minimum_required(VERSION 3.16)
project(Smithtry1000 LANGUAGES CXX)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/qt.cmake")
    include(qt.cmake)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-D_WIN32_DCOM)

# Поиск Qt компонентов (совместимо с Conan)
find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Svg PrintSupport)
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
    #awr_interface.h
    #AWR.cpp
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

# Линковка Qt библиотек
# Линковка Qt библиотек (в конце файла, где у вас target_link_libraries)
if(USING_CONAN)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Svg
        Qt5::PrintSupport
    )
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Svg
        Qt5::PrintSupport
        ole32
        oleaut32
        uuid
    )
endif()

# Настройки для разных типов сборки
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_BUILD)
endif()

# Дополнительные флаги компиляции для лучшей диагностики
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W3)
endif()

# Установка
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Установка Qt DLL на Windows (если нужно)
if(WIN32)
    # Копирование Qt DLL рядом с исполняемым файлом для удобства отладки
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(QT_DLL_DIR "${Qt${QT_VERSION_MAJOR}_DIR}/../../../bin")
    else()
        set(QT_DLL_DIR "${Qt${QT_VERSION_MAJOR}_DIR}/../../../bin")
    endif()
    
    # Эта команда выполнится после сборки
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Qt DLLs should be in PATH or copied manually from ${QT_DLL_DIR}"
        VERBATIM
    )
endif()

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /EHsc)
endif()