################################################################################
# Package: B2CCtuples
################################################################################
gaudi_subdir(B2CCtuples v3r0)

gaudi_depends_on_subdirs(Math/SomeUtils)

find_package(ROOT)
find_package(pyanalysis)
find_package(pytools)

