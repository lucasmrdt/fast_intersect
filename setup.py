from distutils.core import setup, Extension
import os

dir_path = os.path.dirname(os.path.realpath(__file__))

sources = [os.path.join(dir_path, source) for source in [
    "fast_intersect.cc"
]]

fast_intersect = Extension("fast_intersect", sources=sources)

setup(
    name="fast_intersect",
    packages=["fast_intersect"],
    version="0.1",
    license="MIT",
    description="Fast intersection of sets",
    author="Lucas Marandat",
    author_email="lucas.mrdt@gmail.com",
    url="https://github.com/lucasmrdt/algo-midterm-part2",
    download_url="https://github.com/lucasmrdt/algo-midterm-part2",
    description="Set package",
    ext_modules=[fast_intersect],
)
