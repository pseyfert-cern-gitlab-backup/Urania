################################################################################
# Package: B2DXFitters
################################################################################
gaudi_subdir(B2DXFitters v4r0)

find_package(RELAX)
find_package(ROOT COMPONENTS Core RooFitCore RooStats RooFit Hist Tree RIO Matrix MathCore MathMore Physics Gpad Graf)

find_package(Boost COMPONENTS container)
find_package(TBB)

# override the genreflex call to wrap it in the right environment
#set(ROOT_genreflex_CMD ${env_cmd} --xml ${env_xml} ${ROOT_genreflex_CMD})

#include_directories(${ROOT_INCLUDE_DIRS})
#reflex_generate_dictionary(B2DXFitters
#                           dict/B2DXFittersDict.h dict/B2DXFittersDict.xml
#                           SPLIT_CLASSDEF)
#add_definitions(-UNDEBUG)
include_directories(SYSTEM ${ROOT_INCLUDE_DIRS})

gaudi_add_dictionary(B2DXFitters
                     dict/B2DXFittersDict.h
                     dict/B2DXFittersDict.xml
                     INCLUDE_DIRS ROOT Boost
                     LINK_LIBRARIES ROOT Boost TBB
                     OPTIONS "-U__MINGW32__"
                     SPLIT_CLASSDEF)

gaudi_add_library(B2DXFittersLib
                  src/*.cxx
                  B2DXFittersDict_classdef.cpp
                  PUBLIC_HEADERS B2DXFitters
                  INCLUDE_DIRS ROOT Boost
                  LINK_LIBRARIES ROOT Boost TBB)
set_property(TARGET B2DXFittersLib PROPERTY COMPILE_FLAGS -g)

# ensure that genreflex is not called twice (in parallel builds)
add_dependencies(B2DXFittersLib B2DXFittersGen)

target_link_libraries(B2DXFittersDict -Wl,--no-as-needed B2DXFittersLib -Wl,--as-needed)

gaudi_install_python_modules()

