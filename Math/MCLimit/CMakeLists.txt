################################################################################
# Package: MCLimit
################################################################################
gaudi_subdir(MCLimit v2r2)

find_package(ROOT COMPONENTS Core RIO MathCore Minuit Hist Graf MathCore Minuit Hist Graf)

include_directories(SYSTEM ${ROOT_INCLUDE_DIRS})

gaudi_add_library(MCLimit
                  src/junkInterface.cpp
                  NO_PUBLIC_HEADERS
                  INCLUDE_DIRS ROOT
                  LINK_LIBRARIES ROOT)

gaudi_add_dictionary(MCLimit
                     dict/MCLimitDict.h
                     dict/MCLimit.xml
                     INCLUDE_DIRS ROOT
                     LINK_LIBRARIES ROOT MCLimit
                     OPTIONS " -U__MINGW32__ ")

gaudi_install_python_modules()

