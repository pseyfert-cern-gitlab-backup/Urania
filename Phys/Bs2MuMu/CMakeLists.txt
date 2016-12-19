################################################################################
# Package: Bs2MuMu
################################################################################
gaudi_subdir(Bs2MuMu v3r2)

gaudi_depends_on_subdirs(Math/MCLimit
                         Math/SomeUtils
                         PhysFit/SomeMassModels
                         RootTools/LHCbStyle)

find_package(ROOT)
find_package(pyanalysis)
find_package(pytools)

