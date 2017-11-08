#ifndef SUM_DENSITY
#define SUM_DENSITY

#include "TMath.h"

#include <vector>

#include "Meerkat/AbsDensity.hh"
#include "Meerkat/AbsPhaseSpace.hh"

/// Class that describes the sum density: the sum of two or more densities in the same phase spaces with optional weights

class SumDensity : public AbsDensity {

  public: 
  
    //! Constructor of Sum density of an arbitrary number of density components
    /*! 
      \param [in] pdfName PDF name
      \param [in] thePhaseSpace phase space. Dimensionality of the phase space should be equal to the ones of all density components. 
      \param [in] densityComponents vector of density components. 
      \param [in] weights vector of weights
    */ 
    SumDensity(const char* pdfName, 
                      AbsPhaseSpace* thePhaseSpace, 
                      std::vector<AbsDensity*> &densityComponents, 
                      std::vector<Double_t> &weights);

    //! Constructor of Sum density of up to four density components
    /*! 
      \param [in] pdfName PDF name
      \param [in] thePhaseSpace phase space. Dimensionality of the phase space should be equal to the ones of all density components. 
      \param [in] d1 1st density component. 
      \param [in] d2 2nd density component. 
      \param [in] w1 1rd density component weight. 
      \param [in] w2 2th density component weight. 
    */ 
    SumDensity(const char* pdfName, 
                      AbsPhaseSpace* thePhaseSpace, 
                      AbsDensity* d1, 
                      AbsDensity* d2, 
                      Double_t w1 = 1., 
                      Double_t w2 = 1.);

    //! Constructor of Sum density of up to four density components
    /*! 
      \param [in] pdfName PDF name
      \param [in] thePhaseSpace phase space. Dimensionality of the phase space should be equal to the ones of all density components. 
      \param [in] d1 1st density component. 
      \param [in] d2 2nd density component. 
      \param [in] d3 2nd density component. 
      \param [in] w1 1rd density component weight. 
      \param [in] w2 2th density component weight. 
      \param [in] w3 2th density component weight. 
    */ 
    SumDensity(const char* pdfName, 
                      AbsPhaseSpace* thePhaseSpace, 
                      AbsDensity* d1, 
                      AbsDensity* d2, 
                      AbsDensity* d3, 
                      Double_t w1 = 1., 
                      Double_t w2 = 1., 
                      Double_t w3 = 1.);

    //! Constructor of Sum density of up to four density components
    /*! 
      \param [in] pdfName PDF name
      \param [in] thePhaseSpace phase space. Dimensionality of the phase space should be equal to the ones of all density components. 
      \param [in] d1 1st density component. 
      \param [in] d2 2nd density component. 
      \param [in] d3 2nd density component. 
      \param [in] d4 2nd density component. 
      \param [in] w1 1rd density component weight. 
      \param [in] w2 2th density component weight. 
      \param [in] w3 2th density component weight. 
      \param [in] w4 2th density component weight. 
    */ 
    SumDensity(const char* pdfName, 
                      AbsPhaseSpace* thePhaseSpace, 
                      AbsDensity* d1, 
                      AbsDensity* d2, 
                      AbsDensity* d3, 
                      AbsDensity* d4, 
                      Double_t w1 = 1., 
                      Double_t w2 = 1., 
                      Double_t w3 = 1., 
                      Double_t w4 = 1.);

    //! Destructor
    virtual ~SumDensity(); 

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
    
    //! Common initialise function used by all constructors. 
    /*! 
      \param [in] thePhaseSpace phase space
      \param [in] densityComponents vector of density components. 
      \param [in] weights vector of weights
    */ 
    void init(AbsPhaseSpace* thePhaseSpace, 
              std::vector<AbsDensity*> &densityComponents, 
              std::vector<Double_t> &weights); 

    //! Reference to phase space
    AbsPhaseSpace* m_phaseSpace; 
    
    //! Vector of density components
    std::vector<AbsDensity*> m_densityComponents; 
    
    //! Vector of density component weights
    std::vector<Double_t> m_weights; 
    
    //! Cached dimensionality of the phase space
    UInt_t m_dim; 

}; 

#endif
