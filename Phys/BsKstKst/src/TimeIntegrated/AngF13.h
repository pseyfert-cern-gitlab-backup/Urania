/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef ANGF13
#define ANGF13

//local include
#include "AngAbsFunc.h"

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 #include "TH2D.h" 

class AngF13 : public AngAbsFunc {
public:
  AngF13():AngAbsFunc() {} ; 
  AngF13(const char *name, const char *title,
	      RooAbsReal& _c1,
	      RooAbsReal& _c2,
	      RooAbsReal& _ph,
	RooArgList& _accTH_coefList,
	RooArgList& _accPH_coefList):
    AngAbsFunc(name, title, _c1, _c2, _ph, _accTH_coefList, _accPH_coefList) { } 

    AngF13(const AngF13& other, const char* name=0):
      AngAbsFunc(other, name) { } 

  virtual TObject* clone(const char* newname) const { return new AngF13(*this,newname); }
  inline virtual ~AngF13() { }

  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;


  Double_t evaluate() const ;


protected:

  ClassDef(AngF13,1) // Your description goes here...
};
 
#endif
