from setuptools import setup, Extension
setup(name='fast_math', ext_modules=[Extension('fast_math', ['fast_math.c'])])
