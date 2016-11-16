################################################################################
# Package: A2MuMu
################################################################################
gaudi_subdir(A2MuMu v1r0)

gaudi_depends_on_subdirs(Math/MCLimit
                         Math/SomeUtils
                         PhysFit/SomeMassModels
                         RootTools/LHCbStyle)

find_package(ROOT)
find_package(pyanalysis)
find_package(pytools)

