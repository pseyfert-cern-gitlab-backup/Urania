#include <stdio.h>
#include <vector>
#include <stdlib.h>

#include "TMath.h"

#include "AbsPhaseSpace.hh"
#include "AbsDensity.hh"
#include "TransposedFactorisedDensity.hh"

#include "Logger.hh"

TransposedFactorisedDensity::TransposedFactorisedDensity(const char* pdfName, 
                         AbsPhaseSpace* thePhaseSpace,
                         AbsDensity* d1, AbsDensity* d2, 
                         UInt_t index) : AbsDensity(pdfName) {

  m_density1 = d1; 
  m_density2 = d2; 
  m_index = index; 

  m_phaseSpace = thePhaseSpace;

  Logger::print(0,"%20.20s INFO: Creating transposed factorised density\n", m_name ); 

  m_dim = m_phaseSpace->dimensionality(); 
  m_dim1 = m_density1->phaseSpace()->dimensionality();
  m_dim2 = m_density2->phaseSpace()->dimensionality();

  if (m_dim1 + m_dim2 != m_dim) {
    Logger::print(2,"%20.20s ERROR: Dimensionalities of the factorised phase space and sum of its components differ\n", m_name);
    abort(); 
  }
}

TransposedFactorisedDensity::~TransposedFactorisedDensity() {

}

Double_t TransposedFactorisedDensity::density(std::vector<Double_t> &x) {  

  if (x.size() != m_dim) {
    Logger::print(2,"%20.20s ERROR: Dimensionality of vector (%d) does not correspond to phase space definition (%d)\n", 
       m_name, (UInt_t)x.size(), m_dim);
    abort(); 
  }

  Double_t prod = 1.;
  std::vector<Double_t> x1(m_dim1); 
  std::vector<Double_t> x2(m_dim2); 

  UInt_t j; 
  for (j=0; j<m_dim1; j++) {
    if (j<m_index)
      x1[j] = x[j];
    else 
      x1[j] = x[j+m_dim2];
  }
  for (j=0; j<m_dim2; j++) {
    x2[j] = x[j+m_index];
  }
  prod = m_density1->density(x1)*m_density2->density(x2); 

//    Logger::print(0,"Component %d, density=%f, prod=%f\n", n, d, prod);

  return prod; 

}
