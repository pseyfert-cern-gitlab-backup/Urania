#ifndef TRANSPOSED_FACTORISED_DENSITY
#define TRANSPOSED_FACTORISED_DENSITY

#include "AbsDensity.hh"
#include "AbsPhaseSpace.hh"

#include "TMath.h"

#include <vector>

/// Class that describes the "transposed" factorised density: the product of densities of two components
/// where the variables of 2nd component can be placed at an arbitrary position in the 1st component

class TransposedFactorisedDensity : public AbsDensity {

  public: 
  
    //! Constructor of factorised density of an arbitrary number of density components
    /*! 
      \param [in] pdfName PDF name
      \param [in] thePhaseSpace phase space. Dimensionality of the phase space should be equal to the sum of dimensionalities of all density components. 
      \param [in] density1 1st density components. 
      \param [in] density2 2nd density components. 
      \param [in] index index in 1st at which to insert 2nd density
    */ 
    TransposedFactorisedDensity(const char* pdfName, 
                      AbsPhaseSpace* thePhaseSpace, 
                      AbsDensity* density1, 
                      AbsDensity* density2, 
                      UInt_t index);

    //! Destructor
    virtual ~TransposedFactorisedDensity(); 

    //! Calculate PDF value at the given point
    /*! 
        \param [in] x the point at which to calculate the PDF
        \return PDF value
    */
    Double_t density(std::vector<Double_t> &x);

    //! Return phase space definition for this PDF
    /*!
       \return PDF phase space
    */
    AbsPhaseSpace* phaseSpace() { return m_phaseSpace; }

  private: 

    //! Reference to phase space
    AbsPhaseSpace* m_phaseSpace; 

    //! Density component 1
    AbsDensity* m_density1; 

    //! Density component 2
    AbsDensity* m_density2; 

    //! Index at which density 2 phase space is inserted
    UInt_t m_index; 

    //! Cached dimensionality of the combined phase space
    UInt_t m_dim; 

    //! Cached dimensionality of the density 1 phase space
    UInt_t m_dim1; 

    //! Cached dimensionality of the density 2 phase space
    UInt_t m_dim2; 

}; 

#endif
