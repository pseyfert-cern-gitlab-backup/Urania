################################################################################
# Package: Meerkat
################################################################################
gaudi_subdir(Meerkat v1r4)

find_package(ROOT COMPONENTS Core EG Tree RIO Hist Matrix MathCore RooFitCore RooFit RooStats)

include_directories(SYSTEM ${ROOT_INCLUDE_DIRS})

gaudi_add_library(MeerkatLib
                  src/*.cpp
                  MeerkatCint.cc
                  PUBLIC_HEADERS Meerkat
                  INCLUDE_DIRS ROOT
                  LINK_LIBRARIES ROOT)

# use the right environment when calling rootcling
set(ROOT_rootcling_CMD ${env_cmd} --xml ${env_xml} ${ROOT_rootcling_CMD})

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/MeerkatCint.cc
                   COMMAND ${ROOT_rootcling_CMD} -f ${CMAKE_CURRENT_SOURCE_DIR}/MeerkatCint.cc -s Meerkat -rml libEG.so -rml libHist.so -rml libMatrix.so -rml libNet.so -rml libRIO.so -rml libTree.so -rml libMathCore.so -rml libCore.so -rmf libMeerkat.rootmap -c -I${ROOT_INCLUDE_DIRS} -I../../../PhysTools/Meerkat/Meerkat/ Meerkat/AbsDensity.hh Meerkat/AbsPhaseSpace.hh Meerkat/AdaptiveKernelDensity.hh Meerkat/BinnedDensity.hh Meerkat/BinnedKernelDensity.hh Meerkat/CombinedPhaseSpace.hh Meerkat/DalitzPhaseSpace.hh Meerkat/DivideDensity.hh Meerkat/ExtendedDalitzPhaseSpace.hh Meerkat/FactorisedDensity.hh Meerkat/FormulaDensity.hh Meerkat/HistogramDensity.hh Meerkat/IntersectionPhaseSpace.hh Meerkat/KernelDensity.hh Meerkat/Logger.hh Meerkat/OneDimPhaseSpace.hh Meerkat/ParametricPhaseSpace.hh Meerkat/PolynomialDensity.hh Meerkat/ProductDensity.hh Meerkat/RooMeerkatPdf.hh Meerkat/SumDensity.hh Meerkat/TransposedFactorisedDensity.hh Meerkat/UniformDensity.hh ../../../PhysTools/Meerkat/Meerkat/Meerkat_LinkDef.h
                   COMMAND ${CMAKE_COMMAND} -E copy Meerkat_rdict.pcm ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Meerkat_rdict.pcm
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Meerkat/Meerkat_LinkDef.h)

install(FILES ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Meerkat_rdict.pcm DESTINATION lib OPTIONAL)
