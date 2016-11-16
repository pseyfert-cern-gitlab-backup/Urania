################################################################################
# Package: RooPhysFitter
################################################################################
gaudi_subdir(RooPhysFitter v3r1)

find_package(Boost)
find_package(ROOT COMPONENTS Core Tree RIO Hist TreePlayer Graf Graf3d
                             Gpad Matrix MathCore MathMore RooFitCore RooFit
                             RooStats)

# override the genreflex call to wrap it in the right environment
set(ROOT_genreflex_CMD ${env_cmd} --xml ${env_xml} ${ROOT_genreflex_CMD})

include_directories(${ROOT_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
reflex_generate_dictionary(RooPhysFitter
                           dict/RooPhysFitterDict.h dict/RooPhysFitterDict.xml
                           SPLIT_CLASSDEF)

gaudi_add_library(RooPhysFitterLib
                  src/*.cpp
                  RooPhysFitterDict_classdef.cpp
                  PUBLIC_HEADERS RooPhysFitter
                  INCLUDE_DIRS Boost ROOT
                  LINK_LIBRARIES Boost ROOT)

# ensure that genreflex is not called twice (in parallel builds)
add_dependencies(RooPhysFitterLib RooPhysFitterGen)
