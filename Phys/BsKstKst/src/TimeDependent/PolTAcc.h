#ifndef POLTACC
#define POLTACC

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "TComplex.h"
#include "TF1.h"
#include "RooMath.h"

class PolTAcc : public RooAbsPdf {
public:
  PolTAcc() {} ; 
  PolTAcc(const char *name, const char *title,
	   RooAbsReal& _t,
	   RooAbsReal& _year_opt,
	   RooAbsReal& _trig_opt,
	   RooAbsReal& _wide_window);
  PolTAcc(const PolTAcc& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new PolTAcc(*this,newname); }
  inline virtual ~PolTAcc() { }

  RooRealProxy t ;
  RooRealProxy year_opt ;
  RooRealProxy trig_opt ;
  RooRealProxy wide_window ;

  Int_t iBin(Double_t x) const;

  Double_t evaluate() const;

private:

  ClassDef(PolTAcc,1)
};
 
#endif
