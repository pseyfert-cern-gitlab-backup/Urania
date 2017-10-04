#include <stdio.h>
#include <vector>

#include "TMath.h"

#include "Meerkat/IntersectionPhaseSpace.hh"

#include "Meerkat/Logger.hh"

IntersectionPhaseSpace::IntersectionPhaseSpace(const char* phspName, 
                                       std::vector<AbsPhaseSpace*> &phspList) : AbsPhaseSpace(phspName) {
  init(phspList); 
}

IntersectionPhaseSpace::IntersectionPhaseSpace(const char* phspName, 
                                       AbsPhaseSpace *phaseSpace1, 
                                       AbsPhaseSpace *phaseSpace2, 
                                       AbsPhaseSpace *phaseSpace3, 
                                       AbsPhaseSpace *phaseSpace4) : AbsPhaseSpace(phspName) {

  std::vector<AbsPhaseSpace*> phspVector(2); 
  phspVector[0] = phaseSpace1; 
  phspVector[1] = phaseSpace2; 
  if (phaseSpace3) {
    phspVector.push_back(phaseSpace3); 
  }
  if (phaseSpace4) {
    phspVector.push_back(phaseSpace4); 
  }

  init(phspVector); 

}

IntersectionPhaseSpace::~IntersectionPhaseSpace() {

}

void IntersectionPhaseSpace::init(std::vector<AbsPhaseSpace*> &phspList) {

  m_phspList = phspList; 
  m_dim = 0;
  
  std::vector<AbsPhaseSpace*>::iterator i;
  
  Logger::print(0,"%20.20s INFO: Creating Intersection phase space of %d components\n", m_name, (UInt_t)m_phspList.size() ); 

  // Calculate dimensionality as a sum of component phase spaces  
  for (i=m_phspList.begin(); i != m_phspList.end(); i++) {
    UInt_t dim = (*i)->dimensionality(); 
    Logger::print(0,"%20.20s INFO: Adding component phase space \"%s\", dim=%d\n", m_name, (*i)->name(), dim); 
    if (m_dim == 0) m_dim = dim; 
    if (m_dim != dim) {
      Logger::print(1,"%20.20s WARNING: Dimensionality of  \"%s\" (%d) does not match previous (%d)\n", m_name, (*i)->name(), dim, m_dim); 
      abort(); 
    }
  }

  m_lowerLimit.resize(m_dim);
  m_upperLimit.resize(m_dim);

  // Cache lower and upper limits for variables from component phase spaces    
  UInt_t j;
  for (j=0; j<m_dim; j++) {
    i = m_phspList.begin(); 
    Double_t maxLowerLimit = (*i)->lowerLimit(j);
    Double_t minUpperLimit = (*i)->upperLimit(j); 
    for (i=m_phspList.begin(); i != m_phspList.end(); i++) {
      if (maxLowerLimit < (*i)->lowerLimit(j) ) maxLowerLimit = (*i)->lowerLimit(j);
      if (minUpperLimit > (*i)->upperLimit(j) ) minUpperLimit = (*i)->upperLimit(j);
    }
    m_lowerLimit[j] = maxLowerLimit; 
    m_upperLimit[j] = minUpperLimit; 
  }
}


UInt_t IntersectionPhaseSpace::dimensionality() {
  return m_dim;
}

Bool_t IntersectionPhaseSpace::withinLimits(std::vector<Double_t> &x) {
  if (x.size() != m_dim) {
    Logger::print(1,"%20.20s WARNING: Dimensionality of vector (%d) does not correspond to phase space definition (%d)\n", 
       m_name, (UInt_t)x.size(), m_dim);
    return 0;
  }
  
  std::vector<AbsPhaseSpace*>::iterator i; 
  for (i=m_phspList.begin(); i != m_phspList.end(); i++) {
    if ( !(*i)->withinLimits(x) ) return 0; 
  }
  return 1;
}

Double_t IntersectionPhaseSpace::lowerLimit(UInt_t var) {
  if (var < m_lowerLimit.size()) {
    return m_lowerLimit[var];
  }

  Logger::print(2,"%20.20s ERROR: var=%d for lower limit of Intersection phase space of dim=%d\n", m_name, var, m_dim);
  abort(); 
  
  return 0;
}

Double_t IntersectionPhaseSpace::upperLimit(UInt_t var) {
  if (var < m_upperLimit.size()) {
    return m_upperLimit[var];
  }

  Logger::print(2,"%20.20s ERROR: var=%d for upper limit of Intersection phase space of dim=%d\n", m_name, var, m_dim);
  abort(); 

  return 0;
}

Bool_t IntersectionPhaseSpace::limits(UInt_t var, __attribute__((unused)) std::vector<Double_t> &x, 
                                  Double_t* lower, Double_t* upper) {

  *lower = lowerLimit(var); 
  *upper = upperLimit(var); 

  return 0;

}
