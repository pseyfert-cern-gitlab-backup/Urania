################################################################################
# Package: P2VV
################################################################################
gaudi_subdir(P2VV v4r2)

find_package(ROOT COMPONENTS Core
                             Tree RooFitCore RooFit
                             Matrix MathCore MathMore)

# override the genreflex call to wrap it in the right environment
set(ROOT_genreflex_CMD ${env_cmd} --xml ${env_xml} ${ROOT_genreflex_CMD})

include_directories(${ROOT_INCLUDE_DIRS})
reflex_generate_dictionary(P2VV
                           dict/P2VVDict.h dict/P2VVDict.xml
                           SPLIT_CLASSDEF)

gaudi_add_library(P2VVLib
                  src/*.cxx
                  P2VVDict_classdef.cpp
                  PUBLIC_HEADERS P2VV
                  INCLUDE_DIRS ROOT
                  LINK_LIBRARIES ROOT)
set_property(TARGET P2VVLib PROPERTY COMPILE_FLAGS -g)

# ensure that genreflex is not called twice (in parallel builds)
add_dependencies(P2VVLib P2VVGen)

gaudi_install_python_modules()

