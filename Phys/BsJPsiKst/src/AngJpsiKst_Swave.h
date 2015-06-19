/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef ANGJPSIKST_SWAVE
#define ANGJPSIKST_SWAVE

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
class AngJpsiKst_Swave : public RooAbsPdf {
public:
  AngJpsiKst_Swave() {} ; 
  AngJpsiKst_Swave(const char *name, const char *title,
	      RooAbsReal& _CPsi,
	      RooAbsReal& _CTheta,
	      RooAbsReal& _Phi,
	      RooAbsReal& _A0,
	      RooAbsReal& _Apa,
	      RooAbsReal& _Ape,
	      RooAbsReal& _As,
	      RooAbsReal& _dpa,
	      RooAbsReal& _ds,
	      RooAbsReal& _c1_psi,
	      RooAbsReal& _c2_psi,
	      RooAbsReal& _c3_psi,
	      RooAbsReal& _c4_psi,
	      RooAbsReal& _c5_psi,
	      RooAbsReal& _c1_theta,
	      RooAbsReal& _c2_theta,
	      RooAbsReal& _c1_phi,
	      RooAbsReal& _c2_phi,
	      RooAbsReal& _c3_phi,
	      RooAbsReal& _c4_phi,
	      RooAbsReal& _c5_phi,
	      RooAbsReal& _c6_phi);
  AngJpsiKst_Swave(const AngJpsiKst_Swave& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new AngJpsiKst_Swave(*this,newname); }
  inline virtual ~AngJpsiKst_Swave() { }

protected:

  RooRealProxy CPsi ;
  RooRealProxy CTheta ;
  RooRealProxy Phi ;
  RooRealProxy A0 ;
  RooRealProxy Apa ;
  RooRealProxy Ape ;
  RooRealProxy As ;
  RooRealProxy dpa ;
  RooRealProxy ds ;
  RooRealProxy c1_psi ;
  RooRealProxy c2_psi ;
  RooRealProxy c3_psi ;
  RooRealProxy c4_psi ;
  RooRealProxy c5_psi ;
  RooRealProxy c1_theta ;
  RooRealProxy c2_theta ;
  RooRealProxy c1_phi ;
  RooRealProxy c2_phi ;
  RooRealProxy c3_phi ;
  RooRealProxy c4_phi ;
  RooRealProxy c5_phi ;
  RooRealProxy c6_phi ;
  
  Double_t evaluate() const ;

private:

  ClassDef(AngJpsiKst_Swave,1) // Your description goes here...
};
 
#endif
