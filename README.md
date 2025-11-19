## Сборка пакета с использованием Conan

### Предварительные требования

- Пакетный менеджер Conan
- CMake 3.25 или выше
- C++ 20 совместимый компилятор

### Шаги сборки

1. Создать профиль Conan:

   `conan profile detect --force`

2. Создать директорию сборки:

   `rm -rf build && mkdir build`

3. Установить зависимости используя conan

   `conan install . --output-folder=build`

4. Собрать conan пакет:

   `conan create --build=missing -s build_type=Release -c tools.system.package_manager:mode=install .`

---