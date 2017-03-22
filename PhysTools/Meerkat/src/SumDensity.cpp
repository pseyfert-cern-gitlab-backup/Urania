#include <stdio.h>
#include <vector>
#include <stdlib.h>

#include "TMath.h"

#include "AbsPhaseSpace.hh"
#include "AbsDensity.hh"
#include "SumDensity.hh"

#include "Logger.hh"

SumDensity::SumDensity(const char* pdfName, 
                       AbsPhaseSpace* thePhaseSpace, 
                       std::vector<AbsDensity*> &densityComponents, 
                       std::vector<Double_t> &weights) : AbsDensity(pdfName) {

  init(thePhaseSpace, densityComponents, weights); 
}

SumDensity::SumDensity(const char* pdfName, 
                         AbsPhaseSpace* thePhaseSpace,
                         AbsDensity* d1, AbsDensity* d2, 
                         Double_t w1, Double_t w2) : AbsDensity(pdfName) {

  std::vector<AbsDensity*> densityVector(2); 
  densityVector[0] = d1; 
  densityVector[1] = d2; 

  std::vector<Double_t> weightVector(2); 
  weightVector[0] = w1; 
  weightVector[1] = w2; 

  init(thePhaseSpace, densityVector, weightVector); 
}

SumDensity::SumDensity(const char* pdfName, 
                         AbsPhaseSpace* thePhaseSpace,
                         AbsDensity* d1, AbsDensity* d2, AbsDensity* d3, 
                         Double_t w1, Double_t w2, Double_t w3) : AbsDensity(pdfName) {

  std::vector<AbsDensity*> densityVector(3); 
  densityVector[0] = d1; 
  densityVector[1] = d2; 
  densityVector[2] = d3; 

  std::vector<Double_t> weightVector(3); 
  weightVector[0] = w1; 
  weightVector[1] = w2; 
  weightVector[2] = w3; 

  init(thePhaseSpace, densityVector, weightVector); 
}

SumDensity::SumDensity(const char* pdfName, 
                         AbsPhaseSpace* thePhaseSpace,
                         AbsDensity* d1, AbsDensity* d2, AbsDensity* d3, AbsDensity* d4, 
                         Double_t w1, Double_t w2, Double_t w3, Double_t w4) : AbsDensity(pdfName) {

  std::vector<AbsDensity*> densityVector(4); 
  densityVector[0] = d1; 
  densityVector[1] = d2; 
  densityVector[2] = d3; 
  densityVector[3] = d4; 

  std::vector<Double_t> weightVector(4); 
  weightVector[0] = w1; 
  weightVector[1] = w2; 
  weightVector[2] = w3; 
  weightVector[3] = w4; 

  init(thePhaseSpace, densityVector, weightVector); 
}

SumDensity::~SumDensity() {

}

void SumDensity::init(AbsPhaseSpace* thePhaseSpace, 
                std::vector<AbsDensity*> &densityComponents, 
                std::vector<Double_t> &weights) {

  m_phaseSpace = thePhaseSpace;
  m_densityComponents = densityComponents; 
  m_weights = weights; 
  
  if (densityComponents.size() != weights.size() ) {
    Logger::print(2,"%20.20s ERROR: Dimensionalities of the phase space and weight vectors differ\n", m_name);
    abort();
  }

  Logger::print(0,"%20.20s INFO: Creating sum density of %d components\n", m_name, (UInt_t)densityComponents.size() ); 

  m_dim = m_phaseSpace->dimensionality(); 

  std::vector<AbsDensity*>::iterator i; 
  for (i=densityComponents.begin(); i != densityComponents.end(); i++) {
    UInt_t dim = (*i)->phaseSpace()->dimensionality();
    if (dim != m_dim) {
      Logger::print(2,"%20.20s ERROR: Dimensionalities of the sum phase space and its component %s differ\n", m_name, (*i)->name() );
      abort(); 
    }
  }

}

Double_t SumDensity::density(std::vector<Double_t> &x) {  

  if (x.size() != m_dim) {
    Logger::print(2,"%20.20s ERROR: Dimensionality of vector (%d) does not correspond to phase space definition (%d)\n", 
       m_name, (UInt_t)x.size(), m_dim);
    abort(); 
  }

  Double_t sum = 0.;
  UInt_t i; 
  for (i=0; i < m_densityComponents.size(); i++) {
    AbsDensity* dens = m_densityComponents[i];
    Double_t w = m_weights[i];
    Double_t d = dens->density(x); 
    sum += w*d;
//    Logger::print(0,"Component %d, density=%f, prod=%f\n", n, d, prod);
  }
  return sum; 
}
