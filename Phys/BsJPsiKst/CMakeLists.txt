################################################################################
# Package: BsJPsiKst
################################################################################
gaudi_subdir(BsJPsiKst v3r7)

gaudi_depends_on_subdirs(Math/SomeUtils
                         PhysFit/SomeMassModels)

find_package(ROOT)
find_package(pyanalysis)
find_package(pytools)

