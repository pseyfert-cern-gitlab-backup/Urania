################################################################################
# Package: Ks2Pi0MuMu
################################################################################
gaudi_subdir(Ks2Pi0MuMu v1r2)

gaudi_depends_on_subdirs(Math/MCLimit
                         Math/SomeUtils
                         PhysFit/SomeMassModels
                         RootTools/LHCbStyle)

find_package(ROOT)
find_package(pyanalysis)
find_package(pytools)

