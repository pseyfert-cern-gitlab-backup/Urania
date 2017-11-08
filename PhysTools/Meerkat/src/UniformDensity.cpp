#include <stdio.h>
#include <vector>

#include "Meerkat/AbsPhaseSpace.hh"
#include "Meerkat/AbsDensity.hh"
#include "Meerkat/UniformDensity.hh"

UniformDensity::UniformDensity(const char* pdfName, AbsPhaseSpace* thePhaseSpace) : AbsDensity(pdfName) {

  m_phaseSpace = thePhaseSpace;
}


UniformDensity::~UniformDensity() {

}

Double_t UniformDensity::density(__attribute__((unused)) std::vector<Double_t> &x) {  

  return 1.; 

}
