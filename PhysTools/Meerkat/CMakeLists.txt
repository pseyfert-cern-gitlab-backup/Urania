################################################################################
# Package: Meerkat
################################################################################
gaudi_subdir(Meerkat v1r3)

find_package(ROOT COMPONENTS Core EG Tree RIO Hist Matrix MathCore RooFitCore RooFit RooStats)

include_directories(SYSTEM ${ROOT_INCLUDE_DIRS} inc)

gaudi_add_library(MeerkatLib
                  src/*.cpp
                  MeerkatCint.cc
                  PUBLIC_HEADERS inc
                  INCLUDE_DIRS ROOT
                  LINK_LIBRARIES ROOT)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/MeerkatCint.cc
                   COMMAND rootcling -f ${CMAKE_CURRENT_SOURCE_DIR}/MeerkatCint.cc -s Meerkat -rml libEG.so -rml libHist.so -rml libMatrix.so -rml libNet.so -rml libRIO.so -rml libTree.so -rml libMathCore.so -rml libCore.so -rmf libMeerkat.rootmap -c -I${ROOT_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.hh ${CMAKE_CURRENT_SOURCE_DIR}/inc/Meerkat_LinkDef.h
                   COMMAND ${CMAKE_COMMAND} -E copy Meerkat_rdict.pcm ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Meerkat_rdict.pcm
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/inc/Meerkat_LinkDef.h)

install(FILES ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Meerkat_rdict.pcm DESTINATION lib OPTIONAL)

gaudi_install_python_modules()

