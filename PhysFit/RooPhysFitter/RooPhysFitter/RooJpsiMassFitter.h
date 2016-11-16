// $Id: $
#ifndef ROOPHYSFITTER_ROOJPSIMASSFITTER_H
#define ROOPHYSFITTER_ROOJPSIMASSFITTER_H 1

// Include files
#include "RooPhysFitter/RooDMassFitter.h"

#include <map>
#include <string>
#include "TFormula.h"

// forward declarations
class TTree;

/** @class RooJpsiMassFitter RooJpsiMassFitter.h RooPhysFitter/RooJpsiMassFitter.h

    Class to extend the functionality of RooPhysFitter to provide helper
    functions to create a model and unbinned data set for a single
    descriminating variable.
    In principle, the variable can be any physical parameter, but the
    model production functions are designed for a mass variable with a
    Gaussian-like signal, and a simple polynomial background, e.g. D^0 mass.

    @author Thoams Bird
    @date   2014-02-27
*/

namespace RooPhysFit
{
  class RooJpsiMassFitter : public RooPhysFit::RooDMassFitter {
  public:
    ClassDef(RooJpsiMassFitter,1);

    /// Standard constructor
    RooJpsiMassFitter( ) : RooDMassFitter() {}
    /// Overloaded constructor
    RooJpsiMassFitter( const char* name, const char* title) : RooDMassFitter(name,title) {}

    //Crystal Ball PDF with gaus. Not same means

    void MakeDMassSigCBplusGauss( RooRealVar& mu, RooRealVar& sig_left,
                            RooRealVar& alpha_left,
                            RooRealVar& n_left,
				  RooRealVar& m_gaus, RooRealVar& sig_gaus,RooRealVar& frac_CB );


    /// Double D0 model Crystal Ball PDF with single mean and oppisite tails
    void MakeDMassSigBiCB(  RooRealVar& mu, RooRealVar& sig_left,
                            RooRealVar& sig_right, RooRealVar& alpha_left,
                            RooRealVar& alpha_right, RooRealVar& n_left,
                            RooRealVar& n_right, RooRealVar& frac_left );
    /// Double D0 model Crystal Ball PDF with single mean and oppisite tails
    void MakeDMassSigBiCB(  Float_t mu_start, Float_t mu_min,
                            Float_t mu_max, Float_t sig_left_start,
                            Float_t sig_left_min, Float_t sig_left_max,
                            Float_t sig_right_start, Float_t sig_right_min,
                            Float_t sig_right_max, Float_t alpha_left_start,
                            Float_t alpha_left_min, Float_t alpha_left_max,
                            Float_t alpha_right_start, Float_t alpha_right_min,
                            Float_t alpha_right_max,
                            Float_t n_left_start, Float_t n_left_min,
                            Float_t n_left_max, Float_t n_right_start,
                            Float_t n_right_min, Float_t n_right_max,
                            Float_t frac_left_start, Float_t frac_left_min,
                            Float_t frac_left_max, const char* unit="MeV/c^{2}");


void MakeDMassSigCBplusGauss(  Float_t mu_start, Float_t mu_min,
                            Float_t mu_max, Float_t sig_left_start,
                            Float_t sig_left_min, Float_t sig_left_max,
                            Float_t alpha_left_start,
                            Float_t alpha_left_min, Float_t alpha_left_max,
			      Float_t n_left_fix, Float_t m_gaus_start, Float_t m_gaus_min, Float_t m_gaus_max,
Float_t sig_gaus_start, Float_t sig_gaus_min, Float_t sig_gaus_max,
Float_t frac_CB, Float_t frac_CB_min,
                            Float_t frac_CB_max, const char* unit="MeV/c^{2}");


    /// Double D0 model Crystal Ball PDF with single mean and oppisite tails, fixed n
    void MakeDMassSigBiCBFixn(  RooRealVar& mu, RooRealVar& sig_left,
                            RooRealVar& sig_right, RooRealVar& alpha_left,
                            RooRealVar& alpha_right, RooRealVar& frac_left );
    /// Double D0 model Crystal Ball PDF with single mean and oppisite tails, fixed n
    void MakeDMassSigBiCBFixn(  Float_t mu_start, Float_t mu_min,
                            Float_t mu_max, Float_t sig_left_start,
                            Float_t sig_left_min, Float_t sig_left_max,
                            Float_t sig_right_start, Float_t sig_right_min,
                            Float_t sig_right_max, Float_t alpha_left_start,
                            Float_t alpha_left_min, Float_t alpha_left_max,
                            Float_t alpha_right_start, Float_t alpha_right_min,
                            Float_t alpha_right_max,
                            Float_t frac_left_start, Float_t frac_left_min,
                            Float_t frac_left_max, const char* unit="MeV/c^{2}");
    
    /// background with excited Jpsi state (unit is the "mass" unit)
    void MakeBkgJpsi2s(RooRealVar& grad, RooRealVar& mu, 
                            RooRealVar& frac);
    /// background with excited Jpsi state (unit is the "mass" unit)
    void MakeBkgJpsi2s(Float_t grad_start, Float_t grad_min,
                            Float_t grad_max, Float_t mu_start, 
                            Float_t mu_min, Float_t mu_max,
                            Float_t frac_start, Float_t frac_min,
                            Float_t frac_max, const char* unit="MeV/c^{2}");
    
    
    void ReplaceWithAbsVar( const char* varName, float varMin, 
                            float varMax );
    void RemoveAbsVar( const char* varName, float varMin, 
                            float varMax );

    ~RooJpsiMassFitter( ){} ///< Destructor

  protected:
    // methods
    
    
    // data members

  private:
  };
}
#endif // ROOPHYSFITTER_ROOJPSIMASSFITTER_H
