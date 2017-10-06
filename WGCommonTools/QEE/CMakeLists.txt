################################################################################
# Package: WGCommonTools/QEE
################################################################################
gaudi_subdir(QEE v1r0)

# To be updated:
gaudi_depends_on_subdirs(Math/MCLimit
                         Math/SomeUtils
                         PhysFit/SomeMassModels
                         RootTools/LHCbStyle)

# To be updated:
find_package(ROOT)
find_package(pyanalysis)
find_package(pytools)

gaudi_install_python_modules()

