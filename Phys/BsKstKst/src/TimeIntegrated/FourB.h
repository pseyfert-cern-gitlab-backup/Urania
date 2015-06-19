/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef FOURB
#define FOURB

//local include
#include "AngAbsFunc.h"

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 #include "TH2D.h" 

class FourB : public AngAbsFunc {
public:
  FourB():AngAbsFunc() {} ; 
  FourB(const char *name, const char *title,
	      RooAbsReal& _c1,
	      RooAbsReal& _c2,
	      RooAbsReal& _ph,
	RooArgList& _accTH_coefList,
	RooArgList& _accPH_coefList):
    AngAbsFunc(name, title, _c1, _c2, _ph, _accTH_coefList, _accPH_coefList) { } 

    FourB(const FourB& other, const char* name=0):
      AngAbsFunc(other, name) { } 

  virtual TObject* clone(const char* newname) const { return new FourB(*this,newname); }
  inline virtual ~FourB() { }

  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;


  Double_t evaluate() const ;


protected:

  ClassDef(FourB,1) // Your description goes here...
};
 
#endif
