################################################################################
# Package: MCLimit
################################################################################
project(MCLimit)
cmake_minimum_required(VERSION 3.9)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package(ROOT COMPONENTS Core RIO MathCore Minuit Hist Graf MathCore Minuit Hist Graf)

include(${ROOT_USE_FILE})
REFLEX_GENERATE_DICTIONARY(MCLimitDict dict/MCLimitDict.h SELECTION dict/MCLimit.xml)

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_library(MCLimit SHARED
            src/junkInterface.cpp
            MCLimitDict.cxx)

target_link_libraries(MCLimit ${ROOT_LIBRARIES})
