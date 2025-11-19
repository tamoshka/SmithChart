import os
from conan import ConanFile
from conan.tools.files import copy
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout

class Smithtry1000Conan(ConanFile):
    name = "smith_chart_tool"
    version = "1.0.0"
    requires = ["cadmw-ui-ds/0.4.0", "qt/6.5.3"]
    default_options = {
        "qt/6.5.3:qtsvg": True,
        "qt/6.5.3:shared": True,
        "qt/6.5.3:with_sqlite3": False,
        "qt/6.5.3:qtdeclarative": False,
        "qt/6.5.3:with_pq": False,
        "qt/6.5.3:with_md4c": False,
        "qt/6.5.3:with_odbc": False
    }
    package_type = "application"
    generators = "CMakeDeps"
    settings = "os", "compiler", "build_type", "arch"

    def layout(self):
        cmake_layout(self)
        
    def generate(self):
        version_parts = self.version.split('.')
        major = version_parts[0] if len(version_parts) > 0 else "0"
        minor = version_parts[1] if len(version_parts) > 1 else "0"
        patch = version_parts[2] if len(version_parts) > 2 else "0"
        tc = CMakeToolchain(self)
        tc.variables["PROJECT_VERSION"] = self.version
        tc.variables["PROJECT_VERSION_MAJOR"] = major
        tc.variables["PROJECT_VERSION_MINOR"] = minor
        tc.variables["PROJECT_VERSION_PATCH"] = patch
        tc.generate()