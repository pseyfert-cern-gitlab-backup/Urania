#include <stdio.h>
#include <vector>
#include <stdlib.h>

#include "TMath.h"

#include "AbsPhaseSpace.hh"
#include "AbsDensity.hh"
#include "DivideDensity.hh"

#include "Logger.hh"

DivideDensity::DivideDensity(const char* pdfName,
                         AbsPhaseSpace* thePhaseSpace,
                         AbsDensity* d1, AbsDensity* d2) : AbsDensity(pdfName) {

  m_phaseSpace = thePhaseSpace;
  m_density1 = d1;
  m_density2 = d2;

  Logger::print(0,"%20.20s INFO: Creating divide density\n", m_name); 

  m_dim = m_phaseSpace->dimensionality(); 

  UInt_t dim = m_density1->phaseSpace()->dimensionality();
  if (dim != m_dim) {
    Logger::print(2,"%20.20s ERROR: Dimensionalities of the Divide phase space and its component %s differ\n", m_name, m_density1->name() );
    abort();
  }
  dim = m_density2->phaseSpace()->dimensionality();
  if (dim != m_dim) {
    Logger::print(2,"%20.20s ERROR: Dimensionalities of the Divide phase space and its component %s differ\n", m_name, m_density2->name() );
    abort();
  }
}

DivideDensity::~DivideDensity() {

}

Double_t DivideDensity::density(std::vector<Double_t> &x) {

  if (x.size() != m_dim) {
    Logger::print(2,"%20.20s ERROR: Dimensionality of vector (%d) does not correspond to phase space definition (%d)\n", 
       m_name, (UInt_t)x.size(), m_dim);
    abort(); 
  }

  Double_t d1 = m_density1->density(x);
  Double_t d2 = m_density2->density(x);
  Double_t d = d1;
  if (d2 > 0.) {
    d /= d2; 
  } else {
    d = 0.; 
  }
  return d; 
}
