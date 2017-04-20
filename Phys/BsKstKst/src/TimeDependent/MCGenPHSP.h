#ifndef MCGENPHSP
#define MCGENPHSP

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "TComplex.h"
#include "TF1.h"
#include "RooMath.h"

class MCGenPHSP : public RooAbsReal {
public:
  MCGenPHSP() {} ; 
  MCGenPHSP(const char *name, const char *title,
	   RooAbsReal& _wide_window,
	   RooAbsReal& _m1,
	   RooAbsReal& _m2,
	   RooAbsReal& _t,
           RooAbsReal& _option);
  MCGenPHSP(const MCGenPHSP& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new MCGenPHSP(*this,newname); }
  inline virtual ~MCGenPHSP() { }

  RooRealProxy wide_window ;
  RooRealProxy m1 ;
  RooRealProxy m2 ;
  RooRealProxy t ;
  RooRealProxy option ;

  Double_t GetQ(Double_t ma, Double_t mb, Double_t mc) const;
  Double_t phasespace(Double_t ma, Double_t mb) const;
  Double_t timemodel(Double_t tau) const;

  Double_t evaluate() const ;

private:

  ClassDef(MCGenPHSP,1)
};
 
#endif