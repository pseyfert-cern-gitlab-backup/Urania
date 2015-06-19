// $Id: $
#ifndef ROOPHYSFITTER_ROODSTARD0MASSFITTER_H 
#define ROOPHYSFITTER_ROODSTARD0MASSFITTER_H 1

// Include files
#include "RooPhysFitter/RooDMassFitter.h"
#include "RooPhysFitter/Exceptions.h"

#include <map>
#include <string>

// forward declarations
class TTree;

/** @class RooDstarD0MassFitter RooDstarD0MassFitter.h RooPhysFitter/RooDstarD0MassFitter.h

    Class to extend the functionality of RooPhysFitter to provide helper 
    functions to create a model and unbinned data set using the D0 mass 
    and delta mass (D* mass - D0 mass) as descriminating variables. 
 
    @author Philip Hunt (LHCB)
    @date   2011-05-19
*/

namespace RooPhysFit {
  
  class RooDstarD0MassFitter : public RooPhysFit::RooDMassFitter {
  public: 
    ClassDef(RooDstarD0MassFitter,1);
    
    /// Standard constructor
    RooDstarD0MassFitter( ); 
    RooDstarD0MassFitter( const char* name, const char* title ); 
    
    /// Create the delta mass variable
    void MakeDelmVar(Float_t xmin, Float_t xmax, const char* unit="MeV/c^{2}",
                     const char* title="");
    
    /// Single Gaussian signal PDF
    void MakeDelmSigGauss(RooRealVar& mu, RooRealVar& sig);
    /// Single Gaussian signal PDF
    void MakeDelmSigGauss(Float_t mu_start, Float_t mu_min, Float_t mu_max,
                          Float_t sig_start, Float_t sig_min, Float_t sig_max,
                          const char* unit="MeV/c^{2}");
    /// Double Gaussian signal PDF with single mean
    void MakeDelmSigBiGauss(RooRealVar& mu, RooRealVar& sig0,
                            RooRealVar& sig1oSig0, RooRealVar& coreFrac,
                            const char* sig1Name, const char* sig1Title);
    /// Double Gaussian signal PDF with single mean
    void MakeDelmSigBiGauss( Float_t mu_start, Float_t mu_min, Float_t mu_max,
                             Float_t sig0_start, Float_t sig0_min,
                             Float_t sig0_max, Float_t sig1oSig0_start,
                             Float_t sig1oSig0_min, Float_t sig1oSig0_max,
                             Float_t coreFrac_start,
                             const char* unit="MeV/c^{2}");
    
    /// Double Gaussian signal PDF with separate means
    void MakeDelmSigBiGauss(RooRealVar& mu0, RooRealVar& mu1,
                            RooRealVar& sig0, RooRealVar& sig1oSig0,
                            RooRealVar& coreFrac,
                            const char* sig1Name, const char* sig1Title);
    /// Double Gaussian signal PDF with separate means
    void MakeDelmSigBiGauss( Float_t mu0_start, Float_t mu0_min,
                             Float_t mu0_max,
                             Float_t mu1_start, Float_t mu1_min,
                             Float_t mu1_max,
                             Float_t sig0_start, Float_t sig0_min,
                             Float_t sig0_max,
                             Float_t sig1oSig0_start, Float_t sig1oSig0_min,
                             Float_t sig1oSig0_max, Float_t coreFrac_start,
                             const char* unit="MeV/c^{2}");

    /// Single Cruijff signal PDF
    void MakeDelmSigCruijff( RooRealVar& mu, RooRealVar& sigL, 
                             RooRealVar& sigR, RooRealVar& alphaL,
                             RooRealVar& alphaR );
    /// Single Cruijff signal PDF
    void MakeDelmSigCruijff( Float_t mu_start, Float_t mu_min, Float_t mu_max,
                             Float_t sigL_start, Float_t sigL_min, 
                             Float_t sigL_max, Float_t sigR_start,
                             Float_t sigR_min, Float_t sigR_max,
                             Float_t alphaL_start, Float_t alphaL_min,
                             Float_t alphaL_max, Float_t alphaR_start,
                             Float_t alphaR_min, Float_t alphaR_max,
                             const char* unit="MeV/c^{2}");
    /// Single Cruijff signal PDF with common sigma for the tails
    void MakeDelmSigCruijff(RooRealVar& mu, RooRealVar& sig,
                            RooRealVar& alphaL, RooRealVar& alphaR );
    /// Single Cruijff signal PDF with common sigma for the tails
    void MakeDelmSigCruijff( Float_t mu_start, Float_t mu_min, Float_t mu_max,
                             Float_t sig_start, Float_t sig_min, 
                             Float_t sig_max,
                             Float_t alphaL_start, Float_t alphaL_min,
                             Float_t alphaL_max, Float_t alphaR_start,
                             Float_t alphaR_min, Float_t alphaR_max,
                             const char* unit="MeV/c^{2}");
    /// Single Crystal Ball signal PDF
    void MakeDelmSigCB(RooRealVar& mu, RooRealVar& sig, RooRealVar& alpha,
                       RooRealVar& n);
    /// Single Crystal Ball signal PDF
    void MakeDelmSigCB(Float_t mu_start, Float_t mu_min, Float_t mu_max,
                       Float_t sig_start, Float_t sig_min, Float_t sig_max,
                       Float_t alpha_start, Float_t alpha_min,
                       Float_t alpha_max, Float_t n_start, Float_t n_min,
                       Float_t n_max, const char* unit="MeV/c^{2}");

    /// RooDstD0BG background PDF
    void MakeDelmBkgDstD0BG(RooRealVar& dm0, // threshold
                            RooRealVar& c, // exponent
                            RooRealVar& a, // power
                            RooRealVar& b // linear
                            );
    /// RooDstD0BG background PDF
    void MakeDelmBkgDstD0BG(Float_t dm0_start, Float_t dm0_min, 
                            Float_t dm0_max, Float_t c_start, Float_t c_min,
                            Float_t c_max, Float_t a_start, Float_t a_min,
                            Float_t a_max, Float_t b_start, Float_t b_min,
                            Float_t b_max, const char* unit="MeV/c^{2}");
    
    /// RooDstD0BG background PDF with a fixed b and c
    void MakeDelmBkgDstD0BG(Float_t dm0_start, Float_t dm0_min, 
                            Float_t dm0_max, Float_t c, Float_t a_start, 
                            Float_t a_min, Float_t a_max,
                            Float_t b, const char* unit="MeV/c^{2}");

    /// RooDstD0BG PDF with a fixed threshold
    void MakeDelmBkgDstD0BG(Float_t dm0,  Float_t c_start, Float_t c_min,
                            Float_t c_max, Float_t a_start, Float_t a_min,
                            Float_t a_max, Float_t b_start, Float_t b_min,
                            Float_t b_max, const char* unit="MeV/c^{2}");

    /// RooGranet background PDF
    void MakeDelmBkgGranet(RooRealVar& dm0, // threshold
                           RooRealVar& a, // exponent
                           RooRealVar& b // power
                           );
    /// RooGranet background PDF
    void MakeDelmBkgGranet(Float_t dm0_start, Float_t dm0_min, 
                           Float_t dm0_max, Float_t a_start, Float_t a_min,
                           Float_t a_max, Float_t b_start, Float_t b_min,
                           Float_t b_max, const char* unit="MeV/c^{2}");
    /// RooGranet background PDF with fixed threshold
    void MakeDelmBkgGranet(Float_t dm0, Float_t a_start, Float_t a_min,
                           Float_t a_max, Float_t b_start, Float_t b_min,
                           Float_t b_max, const char* unit="MeV/c^{2}");

    /// RooTwoBodyPhspApprox background PDF
    void MakeDelmBkgTwoBodyPhsp(RooRealVar& c1, // 1st-order coefficient
                                RooRealVar& c2 // 2nd-order coefficient
                                );
    /// RooTwoBodyPhspApprox background PDF
    void MakeDelmBkgTwoBodyPhsp(Float_t c1_start, Float_t c1_min, 
                                Float_t c1_max, Float_t c2_start, 
                                Float_t c2_min, Float_t c2_max,
                                const char* unit="MeV/c^{2}");
                                
    /** Make the 2D mass model.
        If a starting value for a model fraction is less than zero, then this
        model type will be ignored. This is useful to produce partial models
        e.g. a background-only model.
        The method will raise an exception if all fractions are less than zero.
        N.B. The "fake D0" background is unphysical for a D0 mass v.s. delta
        mass fit, but may be useful for other types of mass fits.
    */
    void MakeDelmModel(Float_t frac_sig, Float_t frac_combBkg,
                       Float_t frac_piBkg, Float_t frac_d0Bkg);
    
    /** Make the 2D mass model, with all background types combined.
        If a starting value for a model fraction is less than zero, then this
        model type will be ignored. This is useful to produce partial models
        e.g. a background-only model.
        The method will raise an exception if all fractions are less than zero,
        or the sum of background fractions is >1.
        Note that unlike the MakeDelmModel method, at least one background
        model must be specified.
        N.B. The "fake D0" background is unphysical for a D0 mass v.s. delta
        mass fit, but may be useful for other types of mass fits.
    */
    void MakeDelmCombinedBkgModel(Float_t frac_sig, Float_t frac_combBkg,
                                  Float_t frac_piBkg, Float_t frac_d0Bkg);

    /** Make the 2D mass data set.
        If useDelmVarFromTree is true, then dstarMassVarname is assumed to
        be the delta mass (m_D*-m_D0) rather than the D* mass.
    */
    void MakeDelmDataSet(TTree* tt, const char* d0MassVarname, 
                         const char* dstarMassVarname,
                         const char* name="", const char* title="",
                         const char* cuts="",
                         Bool_t useDelmVarFromTree=kTRUE);
    

    /** Perform a binned fit to the model PDF.
        See RooPhysFitter::PerformBinnedFit for a description of the arguments.
    */
    void PerformDelmBinnedFit(Int_t nD0MassBins, Int_t nDelmBins,
                              const char* fitName="fitResults", 
                              Int_t nCores=4,
                              Bool_t saveSnapshot=kTRUE, 
                              Bool_t printResults=kFALSE,
                              Bool_t useSumW2Errors=kFALSE, 
                              Bool_t extendedMode=kTRUE,
                              Bool_t useChi2Method=kFALSE);

    /** Perform an iterative binned fit to the model PDF.
        See RooPhysFitter::PerformBinnedFit for a description of the arguments.
    */
    void PerformDelmIterativeBinnedFit(Int_t nD0MassBins, Int_t nDelmBins,
                                       std::vector<Int_t>& minuitStrategies,
                                       const char* fitName="fitResults", 
                                       Int_t nCores=4,
                                       Bool_t saveSnapshot=kTRUE, 
                                       Bool_t printResults=kFALSE,
                                       Bool_t useSumW2Errors=kFALSE, 
                                       Bool_t extendedMode=kTRUE,
                                       Bool_t useChi2Method=kFALSE);

    /// Set the name of the delta mass particle (used to label fit components)
    void SetDelmPartName(const char* name);
    /// Set the name of the delta mass variable (in the RooDataSet)
    void SetDelmName(const char* name);

    /// Set the delta mass signal model name
    void SetDelmSigModelName(const char* name);

    /// Set the delta mass background model name
    void SetDelmBkgModelName(const char* name);

    /// Set the 2D signal model name
    void Set2DMassSigModelName(const char* name);
    /// Set the 2D combinatoric background model name
    void Set2DMassCombBkgModelName(const char* name);
    /// Set the 2D random slow pion background model name
    void Set2DMassRandPiBkgModelName(const char* name);
    /** Set the 2D 'fake D0' background model name.
        N.B. This background is unphysical for D0 vs.
        delta mass fit, but may be useful for other fits.
    */
    void Set2DMassFakeD0BkgModelName(const char* name);

    /// Set the 2D combined background model name
    void Set2DMassCombinedBkgModelName(const char *name);
    
    /// Set the 2D signal yield name
    void Set2DMassSigYieldName(const char* name);
    /// Set the 2D combinatoric background yield name
    void Set2DMassCombBkgYieldName(const char* name);
    /// Set the 2D random slow pion background yield name
    void Set2DMassRandPiBkgYieldName(const char* name);
    /** Set the 2D 'fake D0' background yield name.
        N.B. This background is unphysical for D0 vs.
        delta mass fit, but may be useful for other fits.
    */
    void Set2DMassFakeD0BkgYieldName(const char* name);

    /// Set the 2D combined background yield name
    void Set2DMassCombinedBkgYieldName(const char *name);
    
    /** Name of the delta mass "particle" e.g. #Delta_{m}
        used to label the plot parameters.
    */
    const char* GetDelmPartName() const;

    /// Get the name of the delta mass RooRealVar.
    const char* GetDelmName() const;

    /// Get the name of the delta mass signal model
    const char* GetDelmSigModelName() const;
    
    /// Get the name of the delta mass background model
    const char* GetDelmBkgModelName() const;

    /// Get the name of the 2D mass signal model
    const char* Get2DMassSigModelName() const;

    /// Get the name of the 2D mass combinatoric background model
    const char* Get2DMassCombBkgModelName() const;

    /// Get the name of the 2D mass random pion background model
    const char* Get2DMassRandPiBkgModelName() const;

    /** Get the name of the 2D 'fake D0' background model.
        N.B. This background is unphysical for D0 vs.
        delta mass fit, but may be useful for other fits.
    */
    const char* Get2DMassFakeD0BkgModelName() const;

    /** Get the name of the 2D mass combined background model.
        N.B. This is used by the MakeDelmCombinedBkgModel method.
    */
    const char* Get2DMassCombinedBkgModelName() const;

    /// Get the name of the 2D mass signal yield.
    const char* Get2DMassSigYieldName() const;

    /// Get the name of the 2D mass combinatoric background yield
    const char* Get2DMassCombBkgYieldName() const;

    /// Get the name of the 2D mass random pion background yield
    const char* Get2DMassRandPiBkgYieldName() const;

    /** Get the name of the 2D 'fake D0' background yield.
        N.B. This background is unphysical for D0 vs.
        delta mass fit, but may be useful for other fits.
    */
    const char* Get2DMassFakeD0BkgYieldName() const;

    /** Get the name of the 2D mass combined background yield.
        N.B. this is used by the MakeDelmCombinedBkgModel method.
    */
    const char* Get2DMassCombinedBkgYieldName() const;

    virtual ~RooDstarD0MassFitter( ); ///< Destructor

  protected:
  
  // methods
  
  /** get the name of the data histogram in a RooPlot.
      This function is used to get the pull plot.
      NB. You may need to be override this method in a derived class.
  */
  virtual std::string GetDataHistName() const;
  
  /** get the name of the model PDF curve in a RooPlot of the specified
      fit variable.
      This function is used to get the pull plot.
      NB. You may need to be override this method in a derived class.
  */
  virtual std::string GetModelCurveName(const char* var) const;
  
  // data members
  const char* m_delmPartName;
  const char* m_delmName;
    
  const char* m_delmSigModelName;
  const char* m_delmBkgModelName;
    
  const char* m_2dMassSigModelName;
  const char* m_2dMassCombBkgModelName;
  const char* m_2dMassPiBkgModelName;
  const char* m_2dMassD0BkgModelName;

  const char* m_2dMassSigYieldName;
  const char* m_2dMassCombBkgYieldName;
  const char* m_2dMassPiBkgYieldName;
  const char* m_2dMassD0BkgYieldName;

  const char* m_2dMassCombinedBkgModelName;

  const char* m_2dMassCombinedBkgYieldName;

  private:    
  };
}

#endif // ROOPHYSFITTER_ROODSTARD0MASSFITTER_H
