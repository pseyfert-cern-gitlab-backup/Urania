################################################################################
# Package: CalibDataScripts
################################################################################
gaudi_subdir(CalibDataScripts v4r4)

gaudi_depends_on_subdirs(PhysFit/RooPhysFitter)

find_package(Boost COMPONENTS program_options)
find_package(ROOT COMPONENTS Hist TreePlayer Graf Graf3d Gpad Matrix MathCore
                             MathMore RooFitCore RooFit RooStats Cintex)

if(GAUDI_BUILD_TESTS)
  gaudi_add_executable(TestCheckFitResults
                       src/CheckFitResults.cpp
                       src/TestCheckFitResults.cpp
                       INCLUDE_DIRS Boost ROOT
                       LINK_LIBRARIES Boost ROOT RooPhysFitterLib)
endif()

gaudi_add_executable(DStFit
                     src/GetData.cpp
                     src/SetSpectatorVars.cpp
                     src/CheckFitResults.cpp
                     src/DStFit.cpp
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT RooPhysFitterLib)

gaudi_add_executable(Lam0Fit
                     src/GetData.cpp
                     src/SetSpectatorVars.cpp
                     src/CheckFitResults.cpp
                     src/Lam0Fit.cpp
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT RooPhysFitterLib)

gaudi_add_executable(MergeCharges
                     src/MergeCharges.cpp
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT RooPhysFitterLib)

gaudi_add_executable(MergeProtonLines
                     src/MergeProtonLines.cpp
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT RooPhysFitterLib)

gaudi_add_executable(JpsiFit
                     src/GetData.cpp
                     src/SetSpectatorVars.cpp
                     src/CheckFitResults.cpp
                     src/JpsiFit.cpp
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT RooPhysFitterLib)

gaudi_add_executable(DStFit_MuonUnBiased
                     src/GetData.cpp
                     src/SetSpectatorVars.cpp
                     src/CheckFitResults.cpp
                     src/DStFit_MuonUnBiased.cpp
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT RooPhysFitterLib)

#gaudi_add_executable(Lam0Fit_MuonUnBiased
#                     src/GetData.cpp
#                     src/SetSpectatorVars.cpp
#                     src/CheckFitResults.cpp
#                     src/Lam0Fit_MuonUnBiased.cpp
#                     INCLUDE_DIRS Boost ROOT
#                     LINK_LIBRARIES Boost ROOT RooPhysFitterLib)

#gaudi_add_executable(MergeProtonLines_MuonUnBiased
#                     src/MergeProtonLines_MuonUnBiased.cpp
#                     INCLUDE_DIRS Boost ROOT
#                     LINK_LIBRARIES Boost ROOT RooPhysFitterLib)
