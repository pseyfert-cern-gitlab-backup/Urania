#include <stdio.h>
#include <vector>
#include <stdlib.h>

#include "TMath.h"

#include "AbsPhaseSpace.hh"
#include "AbsDensity.hh"
#include "ProductDensity.hh"

#include "Logger.hh"

ProductDensity::ProductDensity(const char* pdfName, 
                                     AbsPhaseSpace* thePhaseSpace, 
                                     std::vector<AbsDensity*> &densityComponents) : AbsDensity(pdfName) {

  init(thePhaseSpace, densityComponents); 
}

ProductDensity::ProductDensity(const char* pdfName, 
                         AbsPhaseSpace* thePhaseSpace,
                         AbsDensity* d1, AbsDensity* d2, 
                         AbsDensity* d3, AbsDensity* d4) : AbsDensity(pdfName) {

  std::vector<AbsDensity*> densityVector(2); 
  densityVector[0] = d1; 
  densityVector[1] = d2; 
  if (d3) {
    densityVector.push_back(d3); 
  }
  if (d4) {
    densityVector.push_back(d4); 
  }
  init(thePhaseSpace, densityVector); 
}

ProductDensity::~ProductDensity() {

}

void ProductDensity::init(AbsPhaseSpace* thePhaseSpace, 
                std::vector<AbsDensity*> &densityComponents) {

  m_phaseSpace = thePhaseSpace;
  m_densityComponents = densityComponents; 
  
  Logger::print(0,"%20.20s INFO: Creating product density of %d components\n", m_name, (UInt_t)densityComponents.size() ); 

  m_dim = m_phaseSpace->dimensionality(); 

  std::vector<AbsDensity*>::iterator i; 
  for (i=densityComponents.begin(); i != densityComponents.end(); i++) {
    UInt_t dim = (*i)->phaseSpace()->dimensionality();
    if (dim != m_dim) {
      Logger::print(2,"%20.20s ERROR: Dimensionalities of the product phase space and its component %s differ\n", m_name, (*i)->name() );
      abort(); 
    }
  }

}

Double_t ProductDensity::density(std::vector<Double_t> &x) {  

  if (x.size() != m_dim) {
    Logger::print(2,"%20.20s ERROR: Dimensionality of vector (%d) does not correspond to phase space definition (%d)\n", 
       m_name, (UInt_t)x.size(), m_dim);
    abort(); 
  }

  Double_t prod = 1.;
  std::vector<AbsDensity*>::iterator i; 
  for (i=m_densityComponents.begin(); i != m_densityComponents.end(); i++) {
    Double_t d = (*i)->density(x); 
    prod *= d;
//    Logger::print(0,"Component %d, density=%f, prod=%f\n", n, d, prod);
  }
  return prod; 
}
