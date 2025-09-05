cmake_minimum_required(VERSION 3.16)
project("Smithtry1000" LANGUAGES CXX)

# Настройки C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Проверяем наличие Conan toolchain и подключаем его при наличии
set(CONAN_TOOLCHAIN_PATH "${CMAKE_SOURCE_DIR}/build/generators/conan_toolchain.cmake")
if(EXISTS ${CONAN_TOOLCHAIN_PATH})
    message(STATUS "Найден Conan toolchain, используем Conan зависимости")
    include(${CONAN_TOOLCHAIN_PATH})
    set(USING_CONAN TRUE)
else()
    message(STATUS "Conan toolchain не найден, используем системные Qt библиотеки")
    set(USING_CONAN FALSE)
endif()

# Поиск Qt зависимостей
if(USING_CONAN)
    # Через Conan
    find_package(Qt NAMES Qt5 REQUIRED COMPONENTS Core)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Svg PrintSupport)
else()
    # Системные Qt библиотеки
    find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Svg PrintSupport)
endif()

# Автоматическая генерация MOC, UIC, RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Добавляем поддиректорию с основным проектом
add_subdirectory("Smithtry1000")