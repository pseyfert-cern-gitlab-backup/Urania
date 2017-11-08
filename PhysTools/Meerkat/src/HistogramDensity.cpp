#include <stdio.h>
#include <vector>

#include "TH1.h"

#include "Meerkat/AbsPhaseSpace.hh"
#include "Meerkat/AbsDensity.hh"
#include "Meerkat/HistogramDensity.hh"

#include "Meerkat/Logger.hh"

HistogramDensity::HistogramDensity(const char* pdfName, AbsPhaseSpace* thePhaseSpace, TH1* hist) : AbsDensity(pdfName) {

  m_phaseSpace = thePhaseSpace;
  m_dim = m_phaseSpace->dimensionality(); 

  if (m_dim > 3) {
    Logger::print(2, "%20.20s ERROR: Dimensionality of the HistogramDensity phase space is %d (must not exceed 3)\n", 
           m_name, m_dim);
    abort(); 
  }

  m_hist = hist; 
}

HistogramDensity::~HistogramDensity() {

}

Double_t HistogramDensity::density(std::vector<Double_t> &x) {  

  UInt_t i;
  Double_t arg[3]; 
  for (i=0; i<3; i++) arg[i] = 0; 

  for (i=0; i<m_dim; i++) {
    arg[i] = x[i]; 
  }

  if (m_dim == 1)
    return m_hist->Interpolate(arg[0]); 
  if (m_dim == 2)
    return m_hist->Interpolate(arg[0], arg[1]); 
  if (m_dim == 3)
    return m_hist->Interpolate(arg[0], arg[1], arg[2]); 
  return 0.; 
}
