################################################################################
# Package: Urania
################################################################################
gaudi_subdir(Urania v4r0)

find_package(ROOT)
find_package(PythonLibs)
find_package(PythonInterp)
find_package(GSL)

find_package(pyanalysis)
find_package(pytools)
find_package(pygraphics)
gaudi_install_python_modules()

