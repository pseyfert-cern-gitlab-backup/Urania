################################################################################
# Package: RooPhysFitter
################################################################################
gaudi_subdir(RooPhysFitter v2r2)

find_package(Boost)
find_package(ROOT COMPONENTS Core Reflex Tree RIO Hist TreePlayer Graf Graf3d
                             Gpad Matrix MathCore MathMore RooFitCore RooFit
                             RooStats Cintex)

include_directories(${ROOT_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
reflex_generate_dictionary(RooPhysFitterDict
                           dict/RooPhysFitterDict.h dict/RooPhysFitterDict.xml
                           SPLIT_CLASSDEF)

gaudi_add_library(RooPhysFitterLib
                  src/*.cpp
                  RooPhysFitterDict_dict_classdef.cpp
                  PUBLIC_HEADERS RooPhysFitter
                  INCLUDE_DIRS Boost ROOT
                  LINK_LIBRARIES Boost ROOT)

# ensure that genreflex is not called twice (in parallel builds)
add_dependencies(RooPhysFitterLib RooPhysFitterDictGen)
