#ifndef EXTENDED_DALITZ_PHASE_SPACE 
#define EXTENDED_DALITZ_PHASE_SPACE

#include "TMath.h"

#include <vector>

#include "Meerkat/AbsPhaseSpace.hh"

/// Class that describes the extended Dalitz phase space: 
/// the 3D phase space where the first variable gives the 
/// range of the mother particle masses, and the two other
/// variables are a usual Dalitz plot phase space. 

class ExtendedDalitzPhaseSpace : public AbsPhaseSpace {

  public: 

    //! Constructor
    /*! 
      \param [in] phaseSpaceName name of the phase space
      \param [in] mDmin minimum mass of the mother particle
      \param [in] mDmax maximum mass of the mother particle
      \param [in] mA mass of the 1st daughter
      \param [in] mB mass of the 2nd daughter
      \param [in] mC mass of the 3rd daughter
    */ 
    ExtendedDalitzPhaseSpace(const char* phaseSpaceName, 
                     Double_t mDmin, 
                     Double_t mDmax, 
                     Double_t mA, 
                     Double_t mB, 
                     Double_t mC); 

    //! Destructor
    virtual ~ExtendedDalitzPhaseSpace(); 
    
    //! Get dimensionality of the phase space. Always equals to two. 
    /*! 
      \return 2 :) 
    */ 
    UInt_t dimensionality() { return 3; }

    //! Check if the point is within the phase space limits
    /*! 
      \param [in] x point 
      \return true in the point is within the phase space, false otherwise
    */ 
    Bool_t withinLimits(std::vector<Double_t> &x); 

    //! Get lower limit
    /*! 
      \param [in] var variable number (0 or 1 for this class)
      \return lower limit of the phase space for this variable
    */ 
    Double_t lowerLimit(UInt_t var); 
    
    //! Get upper limit
    /*! 
      \param [in] var variable number (0 or 1 for this class)
      \return upper limit of the phase space for this variable
    */ 
    Double_t upperLimit(UInt_t var);

    //! Return limits (lower and upper) for the variable at the certain point of the phase space
    /*! 
      \param [in] var number of the variable
      \param [in] x point in the phase space
      \param [out] lower lower limit
      \param [out] upper upper limit
    */ 
    Bool_t limits(UInt_t var, std::vector<Double_t> &x, Double_t* lower, Double_t* upper); 

  private: 
  
    //! Mass of the particle A
    Double_t m_a;

    //! Mass of the particle B
    Double_t m_b;

    //! Mass of the particle C
    Double_t m_c;

    //! Minimum mass of the mother particle
    Double_t m_d_min;

    //! Maximum mass of the mother particle
    Double_t m_d_max;

    //! Squared mass of the particle A
    Double_t m_a2;

    //! Squared mass of the particle B
    Double_t m_b2;

    //! Squared mass of the particle C
    Double_t m_c2;

    //! Sum of squared masses of daughter particles
    Double_t m_SqSum;

    //! Lower limit of AB invariant mass values
    Double_t m_MinAB;

    //! Upper limit of AB invariant mass values
    Double_t m_MaxAB;

    //! Lower limit of BC invariant mass values
    Double_t m_MinBC;

    //! Upper limit of BC invariant mass values
    Double_t m_MaxBC;

}; 

#endif
