################################################################################
# Package: MoreSimpleTools
################################################################################
gaudi_subdir(MoreSimpleTools v1r6)

gaudi_depends_on_subdirs(RootTools/SimpleTools)

find_package(ROOT COMPONENTS Core RIO Tree TreePlayer Gui Hist Gpad Graf
                             MathCore)

gaudi_add_library(MoreSimpleTools
                  src/*.cpp
                  NO_PUBLIC_HEADERS
                  INCLUDE_DIRS ROOT
                  LINK_LIBRARIES ROOT)

gaudi_add_executable(MoreSimpleToolsOptimiser
                     src/optimiser.cc
                     src/*.cpp
                     INCLUDE_DIRS ROOT
                     LINK_LIBRARIES ROOT MoreSimpleTools)

gaudi_add_executable(MoreSimpleToolsShaper
                     src/tupleshaper.cc
                     INCLUDE_DIRS ROOT
                     LINK_LIBRARIES ROOT MoreSimpleTools)

