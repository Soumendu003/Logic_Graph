from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
ext_modules=[ Extension("PyWire",
              sources=["PyWire.pyx", "Wire.cpp"], language='c++', extra_compile_args=['-std=c++0x'])]
setup(
  name = "PyWire",
  cmdclass = {"build_ext": build_ext},
  ext_modules = ext_modules)
  