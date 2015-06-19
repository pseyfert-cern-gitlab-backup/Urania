/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef ANGF6
#define ANGF6

//local include
#include "AngAbsFunc.h"

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
class AngF6 : public AngAbsFunc {
public:
  AngF6():AngAbsFunc() {} ; 
  AngF6(const char *name, const char *title,
	      RooAbsReal& _c1,
	      RooAbsReal& _c2,
	      RooAbsReal& _ph,
	      TH2D& _acc):
    AngAbsFunc(name, title, _c1, _c2, _ph, _acc) { } 
  AngF6(const AngF6& other, const char* name=0):
      AngAbsFunc(other, name) { } 
  virtual TObject* clone(const char* newname) const { return new AngF6(*this,newname); }
  inline virtual ~AngF6() { }

  Double_t integrateBin(Int_t code, double loc1, double hic1, double loc2, double hic2, double loph, double hiph)const;

  Double_t evaluate() const ;


protected:


  ClassDef(AngF6,1) // Your description goes here...
};
 
#endif
