################################################################################
# Package: PIDPerfTools
################################################################################
gaudi_subdir(PIDPerfTools v8r0)

find_package(Boost COMPONENTS regex)
find_package(ROOT COMPONENTS Core RIO
                             RooFitCore RooFit RooStats Hist Gpad Graf Tree)

# override the genreflex call to wrap it in the right environment
set(ROOT_genreflex_CMD ${env_cmd} --xml ${env_xml} ${ROOT_genreflex_CMD})

include_directories(${ROOT_INCLUDE_DIRS})
reflex_generate_dictionary(PIDPerfTools
                           dict/PIDPerfToolsDict.h dict/PIDPerfToolsDict.xml
                           SPLIT_CLASSDEF)

gaudi_add_library(PIDPerfToolsLib
                  src/*.cpp
                  PIDPerfToolsDict_classdef.cpp
                  PUBLIC_HEADERS PIDPerfTools
                  INCLUDE_DIRS Boost ROOT
                  LINK_LIBRARIES Boost ROOT)

# ensure that genreflex is not called twice (in parallel builds)
add_dependencies(PIDPerfToolsLib PIDPerfToolsGen)
