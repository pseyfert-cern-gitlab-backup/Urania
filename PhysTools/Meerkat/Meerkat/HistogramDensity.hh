#ifndef HISTOGRAM_DENSITY
#define HISTOGRAM_DENSITY

#include "TH1.h"

#include <vector>

#include "Meerkat/AbsDensity.hh"
#include "Meerkat/AbsPhaseSpace.hh"

/// Class that describes the density defined by ROOT Histogram
/// The phase space dimensionality must not exceed four

class HistogramDensity : public AbsDensity {

  public:

    //! Constructor
    /*!
        \param [in] pdfName PDF name
        \param [in] thePhaseSpace phase space definition
        \param [in] Histogram ROOT THistogram object
    */
    HistogramDensity(const char* pdfName, 
                   AbsPhaseSpace* thePhaseSpace, 
                   TH1* Histogram);

    virtual ~HistogramDensity(); 

    //! Calculate PDF value at the given point
    /*! 
        \param [in] x the point at which to calculate the PDF
        \return PDF value (equals 1 inside phase space, 0 outside it)
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

    //! ROOT Histogram
    TH1* m_hist;

    //! Cached dimensionality of the phase space
    UInt_t m_dim; 
}; 

#endif

