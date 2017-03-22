################################################################################
# Package: Espresso
################################################################################
gaudi_subdir(Espresso v0r6p2)

find_package(Boost COMPONENTS filesystem serialization)
find_package(Xrootd)
find_package(ROOT REQUIRED Core RooFitCore RooFit Matrix Physics MathCore MathMore RIO Gpad Hist Tree TreePlayer TMVA Postscript ASImage HistPainter XrdUtils NetxNG)
find_package(GSL)

include_directories(SYSTEM ${Boost_INCLUDE_DIRS} ${Xrootd_INCLUDE_DIRS} ${ROOT_INCLUDE_DIRS} ${GSL_INCLUDE_DIRS} Espresso)

gaudi_add_dictionary(Espresso
	             dict/EspressoDict.hh
	             dict/EspressoDict.xml
                     INCLUDE_DIRS Boost ROOT GSL
                     LINK_LIBRARIES Boost ROOT GSL
                     OPTIONS "-U__MINGW32__"
                     SPLIT_CLASSDEF)	

gaudi_add_library(EspressoLib
                  src/*.cpp
                  EspressoDict_classdef.cpp
                  PUBLIC_HEADERS Espresso
                  INCLUDE_DIRS Boost ROOT GSL
                  LINK_LIBRARIES Boost ROOT GSL)

add_dependencies(EspressoLib EspressoGen)
