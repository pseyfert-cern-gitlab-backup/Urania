/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef ANGULARPDFNOACC
#define ANGULARPDFNOACC

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
class AngularPDFNoAcc : public RooAbsPdf {
public:
  AngularPDFNoAcc() {} ; 
  AngularPDFNoAcc(const char *name, const char *title,
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
	      RooAbsReal& _delta_S);
  AngularPDFNoAcc(const AngularPDFNoAcc& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new AngularPDFNoAcc(*this,newname); }
  inline virtual ~AngularPDFNoAcc() { }

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
  
  Double_t evaluate() const ;

private:

  ClassDef(AngularPDFNoAcc,1) // Your description goes here...
};
 
#endif
