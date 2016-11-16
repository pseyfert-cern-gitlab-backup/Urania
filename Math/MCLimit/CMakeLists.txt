################################################################################
# Package: MCLimit
################################################################################
gaudi_subdir(MCLimit v1r6)

find_package(ROOT COMPONENTS Core RIO MathCore Minuit Hist Graf MathCore Minuit Hist Graf)

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

