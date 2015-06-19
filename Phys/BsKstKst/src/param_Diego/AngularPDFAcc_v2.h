/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef ANGULARPDFACC_V2
#define ANGULARPDFACC_V2

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
class AngularPDFAcc_v2 : public RooAbsPdf {
public:
  AngularPDFAcc_v2() {} ; 
  AngularPDFAcc_v2(const char *name, const char *title,
	      RooAbsReal& _helcosthetaK,
	      RooAbsReal& _helcosthetaL,
	      RooAbsReal& _helphi,
	      RooAbsReal& _A_2pe_mod,
	      RooAbsReal& _A_2pa_mod,
	      RooAbsReal& _A_20_mod,
	      RooAbsReal& _A_0_mod,
	      RooAbsReal& _A_pa_mod,
	      RooAbsReal& _A_pe_mod,
	      RooAbsReal& _A_S_mod,
	      RooAbsReal& _delta_2pe,
	      RooAbsReal& _delta_2pa,
	      RooAbsReal& _delta_20,
	      RooAbsReal& _delta_pa,
	      RooAbsReal& _delta_pe,
	      RooAbsReal& _delta_S,
	      RooAbsReal& _c1th,
	      RooAbsReal& _c2th,
	      RooAbsReal& _c3th,
	      RooAbsReal& _c4th,
	      RooAbsReal& _yth);
  AngularPDFAcc_v2(const AngularPDFAcc_v2& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new AngularPDFAcc_v2(*this,newname); }
  inline virtual ~AngularPDFAcc_v2() { }

  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;

protected:

  RooRealProxy helcosthetaK ;
  RooRealProxy helcosthetaL ;
  RooRealProxy helphi ;
  RooRealProxy A_2pe_mod ;
  RooRealProxy A_2pa_mod ;
  RooRealProxy A_20_mod ;
  RooRealProxy A_0_mod ;
  RooRealProxy A_pa_mod ;
  RooRealProxy A_pe_mod ;
  RooRealProxy A_S_mod ;
  RooRealProxy delta_2pe ;
  RooRealProxy delta_2pa ;
  RooRealProxy delta_20 ;
  RooRealProxy delta_pa ;
  RooRealProxy delta_pe ;
  RooRealProxy delta_S ;
  RooRealProxy c1th ;
  RooRealProxy c2th ;
  RooRealProxy c3th ;
  RooRealProxy c4th ;
  RooRealProxy yth ;
  
  Double_t evaluate() const ;

private:

  ClassDef(AngularPDFAcc_v2,1) // Your description goes here...
};
 
#endif
