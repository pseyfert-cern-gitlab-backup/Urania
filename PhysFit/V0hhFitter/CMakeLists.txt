################################################################################
# Package: V0hhFitter
################################################################################
gaudi_subdir(V0hhFitter v1r0)

find_package(Boost COMPONENTS program_options REQUIRED)
find_package(ROOT COMPONENTS Core Tree RIO Hist TreePlayer Graf Graf3d
                             Gpad Matrix MathCore MathMore RooFitCore RooFit
                             RooStats TMVA)

find_package(GSL)
include_directories(${ROOT_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${GSL_INCLUDE_DIRS})

# override the genreflex call to wrap it in the right environment
set(ROOT_genreflex_CMD ${env_cmd} --xml ${env_xml} ${ROOT_genreflex_CMD})

reflex_generate_dictionary(V0hhFitterDict
                           dict/V0hhFitterDict.h dict/V0hhFitterDict.xml
                           SPLIT_CLASSDEF)

gaudi_add_library(V0hhFitterLib
                  src/*.cpp
                  V0hhFitterDictDict_classdef.cpp
                  PUBLIC_HEADERS RooPhysFitter
                  INCLUDE_DIRS Boost ROOT
                  LINK_LIBRARIES Boost ROOT)

add_dependencies(V0hhFitterLib V0hhFitterDictGen)
