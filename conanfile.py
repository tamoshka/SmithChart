import os

class Smithtry1000Conan(ConanFile):
    name = "smith-chart-tool"
    version = "1.0.0"
    requires = ["cadmw-ui-ds/0.4.0", "qt/6.5.3"]
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
            # Для Linux - используем прямой путь к исполняемому файлу
            source_file = "smith-chart-tool"
            source_path = os.path.join(self.build_folder, "Smithtry1000", source_file)
            
            if os.path.exists(source_path):
                print(f"Found executable at: {source_path}")
                copy(self, source_file, src=os.path.dirname(source_path), dst=bin_folder, keep_path=False)
                print(f"File copied successfully to: {bin_folder}")
            else:
                print("Executable file not found!")
                print(f"Expected path: {source_path}")
                
                # Выводим список файлов в build_folder для диагностики
                print("Build folder contents:")
                for root, dirs, files in os.walk(self.build_folder):
                    level = root.replace(self.build_folder, '').count(os.sep)
                    indent = ' ' * 2 * level
                    print(f"{indent}{os.path.basename(root)}/")
                    subindent = ' ' * 2 * (level + 1)
                    for file in files:
                        print(f"{subindent}{file}")
