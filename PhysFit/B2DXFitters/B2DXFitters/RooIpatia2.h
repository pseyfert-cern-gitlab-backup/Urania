/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            *
 *****************************************************************************/

#ifndef ROOIPATIA2
#define ROOIPATIA2

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

class RooIpatia2 : public RooAbsPdf {
public:
  RooIpatia2() {} ;
  RooIpatia2(const char *name, const char *title,
	      RooAbsReal& _x,
	      RooAbsReal& _l,
	      RooAbsReal& _zeta,
	      RooAbsReal& _fb,
	      RooAbsReal& _sigma,
	      RooAbsReal& _mu,
	      RooAbsReal& _a,
	      RooAbsReal& _n,
	      RooAbsReal& _a2,
	      RooAbsReal& _n2);
  RooIpatia2(const RooIpatia2& other, const char* name=0) ;
  TObject* clone(const char* newname) const override { return new RooIpatia2(*this,newname); }
  inline ~RooIpatia2() { }

  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const override;
  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const override;

protected:

  RooRealProxy x ;
  RooRealProxy l ;
  RooRealProxy zeta ;
  RooRealProxy fb ;
  RooRealProxy sigma ;
  RooRealProxy mu ;
  RooRealProxy a ;
  RooRealProxy n ;
  RooRealProxy a2 ;
  RooRealProxy n2 ;

  Double_t evaluate() const override;

private:

  ClassDef(RooIpatia2,1) // Your description goes here...
};

#endif