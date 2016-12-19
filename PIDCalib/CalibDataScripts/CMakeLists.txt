################################################################################
# Package: CalibDataScripts
################################################################################
gaudi_subdir(CalibDataScripts v5r4)

gaudi_depends_on_subdirs(PhysFit/RooPhysFitter)

find_package(Boost COMPONENTS program_options)
find_package(ROOT COMPONENTS Hist TreePlayer Graf Graf3d Gpad Matrix MathCore
                             MathMore RooFitCore RooFit RooStats)

if(NOT heptools_version STRLESS 68)
  # FIXME: for some reason, starting from LCG 68, libMathMore.so requires libgsl.so
  find_package(GSL)
  set(ROOT_LIBRARIES ${ROOT_LIBRARIES} ${GSL_LIBRARIES})
endif()

if(GAUDI_BUILD_TESTS)
  gaudi_add_executable(TestCheckFitResults
                       src/CheckFitResults.cpp
                       src/TestCheckFitResults.cpp
                       INCLUDE_DIRS Boost ROOT
                       LINK_LIBRARIES Boost ROOT RooPhysFitterLib)
endif()

gaudi_add_executable(DStFit
                     src/GetData.cpp
                     src_S21/SetSpectatorVars.cpp
                     src/CheckFitResults.cpp
                     src_S21/DStFit.cpp
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT RooPhysFitterLib)

gaudi_add_executable(Lam0Fit
                     src/GetData.cpp
                     src_S21/SetSpectatorVars.cpp
                     src/CheckFitResults.cpp
                     src_S21/Lam0Fit.cpp
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT RooPhysFitterLib)

gaudi_add_executable(IncLcFit
                     src/GetData.cpp
                     src_S21/SetSpectatorVars.cpp
                     src/CheckFitResults.cpp
                     src_S21/IncLcFit.cpp
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT RooPhysFitterLib)

gaudi_add_executable(LcfBFit
                     src/GetData.cpp
                     src_S21/SetSpectatorVars.cpp
                     src/CheckFitResults.cpp
                     src_S21/LcfBFit.cpp
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT RooPhysFitterLib)

gaudi_add_executable(MergeCharges
                     src_S21/MergeCharges.cpp
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT RooPhysFitterLib)

gaudi_add_executable(MergeProtonLines
                     src_S21/MergeProtonLines.cpp
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT RooPhysFitterLib)

gaudi_add_executable(MergeProtIncLc
                     src_S21/MergeProtIncLc.cpp
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT RooPhysFitterLib)

gaudi_add_executable(JpsiFit
                     src/GetData.cpp
                     src_S21/SetSpectatorVars.cpp
                     src/CheckFitResults.cpp
                     src_S21/JpsiFit.cpp
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT RooPhysFitterLib)

gaudi_add_executable(JpsieeFit
                     src/GetData.cpp
                     src_S21/SetSpectatorVars.cpp
                     src/CheckFitResults.cpp
                     src_S21/JpsieeFit.cpp
                     INCLUDE_DIRS Boost ROOT
                     LINK_LIBRARIES Boost ROOT RooPhysFitterLib)

#gaudi_add_executable(DStFit_MuonUnBiased
#                     src/GetData.cpp
#                     src/SetSpectatorVars.cpp
#                     src/CheckFitResults.cpp
#                     src/DStFit_MuonUnBiased.cpp
#                     INCLUDE_DIRS Boost ROOT
#                     LINK_LIBRARIES Boost ROOT RooPhysFitterLib)

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
