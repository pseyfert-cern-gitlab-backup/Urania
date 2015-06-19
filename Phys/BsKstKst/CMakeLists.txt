################################################################################
# Package: BsKstKst
################################################################################
gaudi_subdir(BsKstKst v4r1)

gaudi_depends_on_subdirs(Math/MCLimit
                         Math/SomeUtils
                         PhysFit/SomeMassModels
                         RootTools/LHCbStyle)

find_package(GSL)
find_package(ROOT)
find_package(pyanalysis)
find_package(pytools)

gaudi_install_python_modules()

