from conan import ConanFile
from conan.tools.cmake import CMakeDeps, CMakeToolchain, cmake_layout, CMake
from conan.tools.files import copy, collect_libs
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
        "qt/*:with_printSupport": True,
        "qt/*:qtsvg": True
    }
    
    exports_sources = "CMakeLists.txt", "Smithtry1000/*"
    
    def requirements(self):
        self.requires("qt/5.15.13")
    
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
        if (self.settings.os == "Windows"):
            self._copy_qt_runtime()
    
    def _copy_qt_runtime(self):
        qt_dep = self.dependencies["qt"]
        qt_bindir = os.path.join(qt_dep.package_folder, "bin")
        qt_pluginsdir = os.path.join(qt_dep.package_folder, "bin", "archdatadir", "plugins")
        
        qt_dlls = ["Qt5Core.dll", "Qt5Gui.dll", "Qt5Widgets.dll", "Qt5Svg.dll"]
        for dll in qt_dlls:
            copy(self, dll, 
                 src=qt_bindir,
                 dst=os.path.join(self.build_folder, "Smithtry1000\Release"),
                 keep_path=False)
        
        copy(self, "*.dll", 
             src=os.path.join(qt_pluginsdir, "platforms"),
             dst=os.path.join(self.build_folder, "Smithtry1000\Release\platforms"),
             keep_path=False)
        
        copy(self, "*.dll", 
             src=os.path.join(qt_pluginsdir, "imageformats"),
             dst=os.path.join(self.build_folder, "Smithtry1000\Release\imageformats"),
             keep_path=False)

        copy(self, "*.dll", 
             src=os.path.join(qt_pluginsdir, "styles"),
             dst=os.path.join(self.build_folder, "Smithtry1000\Release\styles"),
             keep_path=False)
    
    def package_info(self):
        self.cpp_info.bindirs = ["bin"]
