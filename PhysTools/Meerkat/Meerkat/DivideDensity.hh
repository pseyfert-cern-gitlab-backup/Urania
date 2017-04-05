#ifndef DIVIDE_DENSITY
#define DIVIDE_DENSITY

#include "TMath.h"

#include <vector>

#include "Meerkat/AbsDensity.hh"
#include "Meerkat/AbsPhaseSpace.hh"

/// Class that describes the "divide" density: the ratio of two densities in the same phase spaces

class DivideDensity : public AbsDensity {

  public: 
  
    //! Constructor of Divide density
    /*! 
      \param [in] pdfName PDF name
      \param [in] thePhaseSpace phase space. Dimensionality of the phase space should be equal to the ones of the components. 
      \param [in] d1 numerator density component. 
      \param [in] d2 denominator density component. 
    */ 
    DivideDensity(const char* pdfName, 
                      AbsPhaseSpace* thePhaseSpace, 
                      AbsDensity* d1, 
                      AbsDensity* d2);

    //! Destructor
    virtual ~DivideDensity(); 

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

    //! Cached dimensionality of the phase space
    UInt_t m_dim; 

}; 

#endif
