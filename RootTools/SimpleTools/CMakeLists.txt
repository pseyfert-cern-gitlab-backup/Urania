################################################################################
# Package: SimpleTools
################################################################################
gaudi_subdir(SimpleTools v2r0)

find_package(Boost)
find_package(ROOT COMPONENTS Core RIO Tree TreePlayer Gui Hist Gpad Graf
                             MathCore)
find_package(TBB)

include_directories(SYSTEM ${Boost_INCLUDE_DIRS} ${ROOT_INCLUDE_DIRS})

gaudi_add_executable(SimpleToolsColumnMaker
                     src/columnmaker.cc
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT TBB)

gaudi_add_executable(SimpleToolsCorrs
                     src/corrs.cc
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT TBB)

gaudi_add_executable(SimpleToolsCrop
                     src/crop.cc
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT TBB)

gaudi_add_executable(SimpleToolsCutApplier
                     src/cutapplier.cc
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT TBB)

if(GAUDI_BUILD_TESTS)
  gaudi_add_executable(SimpleToolsCutTester
                       src/cuttester.cc
                       INCLUDE_DIRS Boost ROOT
                       LINK_LIBRARIES Boost ROOT TBB)
endif()

gaudi_add_executable(SimpleToolsEff
                     src/eff.cc
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT TBB)

if(GAUDI_BUILD_TESTS)
  gaudi_add_executable(SimpleToolsKstest
                       src/kstest.cc
                       INCLUDE_DIRS Boost ROOT
                       LINK_LIBRARIES Boost ROOT TBB)
endif()

gaudi_add_executable(SimpleToolsStacker
                     src/stacker.cc
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT TBB)

gaudi_add_executable(SimpleToolsStackerGen
                     src/stackergen.cc
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT TBB)

gaudi_add_executable(SimpleToolsStackerGenLog
                     src/stackergenlog.cc
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT TBB)

gaudi_add_executable(SimpleToolsTupleSampler
                     src/tuplesampler.cc
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT TBB)

