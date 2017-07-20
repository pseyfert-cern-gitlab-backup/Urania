/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef ROOPRIOR
#define ROOPRIOR

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
class RooPrior : public RooAbsPdf {
public:
  RooPrior() {} ; 
  RooPrior(const char *name, const char *title,
	      RooAbsReal& _BR);
  RooPrior(const RooPrior& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooPrior(*this,newname); }
  inline virtual ~RooPrior() { }

  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;

protected:

  RooRealProxy BR ;
  
  Double_t evaluate() const ;

private:

  ClassDef(RooPrior,1) // Your description goes here...
};
 
#endif
