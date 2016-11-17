/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef ANGF16
#define ANGF16

//local include
#include "AngAbsFunc.h"

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
class AngF16 : public AngAbsFunc {
public:
  AngF16():AngAbsFunc() {} ; 
  AngF16(const char *name, const char *title,
	      RooAbsReal& _c1,
	      RooAbsReal& _c2,
	      RooAbsReal& _ph,
	RooArgList& _accTH_coefList,
	RooArgList& _accPH_coefList):
    AngAbsFunc(name, title, _c1, _c2, _ph, _accTH_coefList, _accPH_coefList) { } 

  AngF16(const AngF16& other, const char* name=0) :
      AngAbsFunc(other, name) { } 

  virtual TObject* clone(const char* newname) const { return new AngF16(*this,newname); }
  inline virtual ~AngF16() { }

  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;

  Double_t evaluate() const ;


protected:

  ClassDef(AngF16,1) // Your description goes here...
};
 
#endif