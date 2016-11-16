################################################################################
# Package: SomeUtils
################################################################################
gaudi_subdir(SomeUtils v3r6)

find_package(pyanalysis)
find_package(pytools)

gaudi_add_library(SomeUtils src/*.cpp
                  PUBLIC_HEADERS SomeUtils)

gaudi_install_python_modules()
