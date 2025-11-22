from conan import ConanFile
from conan.tools.cmake import CMakeDeps, CMakeToolchain, cmake_layout, CMake
from conan.tools.files import copy, collect_libs
import os

class Smithtry1000Conan(ConanFile):
    name = "smith-chart-tool"
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
        self.requires("qt/6.5.3")       
        
    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        
        deps = CMakeDeps(self)
        deps.generate()
        
    def layout(self):
        cmake_layout(self)
        
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
            # Для Linux - правильный путь к исполняемому файлу
            # Исполняемый файл находится в подкаталоге build
            source_dir = os.path.join(self.build_folder, "Smithtry1000", "build")
            source_file = "smith-chart-tool"
            source_path = os.path.join(source_dir, source_file)
            
            print(f"Corrected source dir: {source_dir}")
            print(f"Corrected source path: {source_path}")
            print(f"Source file exists: {os.path.exists(source_path)}")
            
            if os.path.exists(source_path):
                copy(self, source_file, src=source_dir, dst=bin_folder, keep_path=False)
                print(f"File copied successfully to: {bin_folder}")
            else:
                # Если не нашли в build, попробуем в корне build_folder
                source_dir = self.build_folder
                source_path = os.path.join(source_dir, source_file)
                if os.path.exists(source_path):
                    copy(self, source_file, src=source_dir, dst=bin_folder, keep_path=False)
                    print(f"File copied successfully to: {bin_folder}")
                else:
                    print("Source file does not exist!")