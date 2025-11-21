from conan import ConanFile
from conan.tools.cmake import CMakeDeps, CMakeToolchain, cmake_layout, CMake
from conan.tools.files import copy, collect_libs
from conan.tools.build import check_min_cppstd
import os

class Smithtry1000Conan(ConanFile):
    name = "smith_chart_tool"
    version = "1.0.0"
    package_type = "application"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "fPIC": [True, False]
    }
    default_options = {
        "shared": False,
        "fPIC": True,
        "qt/*:shared": True,
        "qt/*:with_gui": True,
        "qt/*:with_widgets": True,
        "qt/*:with_svg": True,
        "qt/*:with_printsupport": True,
        "qt/*:qtsvg": True
    }
    
    exports_sources = "CMakeLists.txt", "Smithtry1000/*"
    
    def requirements(self):
        self.requires("qt/6.5.3")
    
    def layout(self):
        cmake_layout(self)
    
    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        
        tc = CMakeToolchain(self)
        tc.generate()
    
    def configure(self):
        if self.settings.os == "Windows":
            del self.options.fPIC
            self.options["qt"].shared = True
    
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
    
    def package(self):
    print(f"Package folder: {self.package_folder}")
    print(f"Build folder: {self.build_folder}")
    
    # Создаем папку bin в пакете
    bin_folder = os.path.join(self.package_folder, "bin")
    os.makedirs(bin_folder, exist_ok=True)
    print(f"Bin folder created: {bin_folder}")
    
    if self.settings.os == "Windows":
        copy(self, "*.exe", 
             src=self.build_folder, 
             dst=bin_folder, 
             keep_path=False)
        self._copy_qt_runtime()
    else:
        # Для Linux - правильный путь (исключаем лишнюю часть build/Release)
        # Conan уже указывает на правильную папку Release в self.build_folder
        source_dir = os.path.join(self.build_folder, "Smithtry1000")  # Только Smithtry1000
        source_file = "Smithtry1000"
        source_path = os.path.join(source_dir, source_file)
        
        print(f"Corrected source dir: {source_dir}")
        print(f"Corrected source path: {source_path}")
        print(f"Source file exists: {os.path.exists(source_path)}")
        
        if os.path.exists(source_path):
            copy(self, source_file, src=source_dir, dst=bin_folder, keep_path=False)
            print(f"File copied successfully to: {bin_folder}")
        else:
            print("Source file does not exist!")
        
    def _copy_qt_runtime(self):
        qt_dep = self.dependencies["qt"]
        
        # Определяем правильный путь к бинарным файлам Qt
        possible_bindirs = [
            os.path.join(qt_dep.package_folder, "bin"),
            os.path.join(qt_dep.package_folder, "libexec"),
            os.path.join(qt_dep.package_folder, "lib")
        ]
        
        qt_bindir = None
        for bindir in possible_bindirs:
            if os.path.exists(bindir):
                qt_bindir = bindir
                break
        
        if qt_bindir:
            # Находим Qt DLLs для Qt 6.x
            qt_dlls = ["Qt6Core.dll", "Qt6Gui.dll", "Qt6Widgets.dll", "Qt6Svg.dll", 
                      "Qt6PrintSupport.dll", "Qt6OpenGL.dll", "Qt6OpenGLWidgets.dll"]
            for dll in qt_dlls:
                dll_path = os.path.join(qt_bindir, dll)
                if os.path.exists(dll_path):
                    copy(self, dll, 
                         src=qt_bindir,
                         dst=os.path.join(self.package_folder, "bin"),
                         keep_path=False)
        
        # Копируем плагины Qt
        qt_pluginsdir = os.path.join(qt_dep.package_folder, "plugins")
        if os.path.exists(qt_pluginsdir):
            copy(self, "*", 
                 src=os.path.join(qt_pluginsdir, "platforms"),
                 dst=os.path.join(self.package_folder, "bin", "platforms"),
                 keep_path=False)
            
            copy(self, "*", 
                 src=os.path.join(qt_pluginsdir, "imageformats"),
                 dst=os.path.join(self.package_folder, "bin", "imageformats"),
                 keep_path=False)

            copy(self, "*", 
                 src=os.path.join(qt_pluginsdir, "styles"),
                 dst=os.path.join(self.package_folder, "bin", "styles"),
                 keep_path=False)
    
    def package_info(self):
        self.cpp_info.bindirs = ["bin"]