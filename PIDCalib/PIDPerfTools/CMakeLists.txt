################################################################################
# Package: PIDPerfTools
################################################################################
gaudi_subdir(PIDPerfTools v5r5)

find_package(Boost COMPONENTS regex)
find_package(ROOT COMPONENTS Core Reflex RIO
                             RooFitCore RooFit RooStats Hist Gpad Graf Tree)

include_directories(${ROOT_INCLUDE_DIRS})
reflex_generate_dictionary(PIDPerfToolsDict
                           dict/PIDPerfToolsDict.h dict/PIDPerfToolsDict.xml
                           SPLIT_CLASSDEF)

gaudi_add_library(PIDPerfToolsLib
                  src/*.cpp
                  PIDPerfToolsDict_dict_classdef.cpp
                  PUBLIC_HEADERS PIDPerfTools
                  INCLUDE_DIRS Boost ROOT
                  LINK_LIBRARIES Boost ROOT)

# ensure that genreflex is not called twice (in parallel builds)
add_dependencies(PIDPerfToolsLib PIDPerfToolsDictGen)
