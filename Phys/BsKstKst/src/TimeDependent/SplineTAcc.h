#ifndef SPLINETACC
#define SPLINETACC

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "TComplex.h"
#include "TF1.h"
#include "RooMath.h"

Double_t knot[12];

class SplineTAcc : public RooAbsPdf {
public:
  SplineTAcc() {} ; 
  SplineTAcc(const char *name, const char *title,
	   RooAbsReal& _t,
	   RooAbsReal& _x0,
	   RooAbsReal& _x1,
	   RooAbsReal& _x2,
	   RooAbsReal& _x3,
	   RooAbsReal& _x4,
	   RooAbsReal& _x5,
	   RooAbsReal& _c0,
	   RooAbsReal& _c1,
	   RooAbsReal& _c2,
	   RooAbsReal& _c3,
	   RooAbsReal& _c4,
	   RooAbsReal& _c5,
	   RooAbsReal& _c6,
	   RooAbsReal& _c7);
  SplineTAcc(const SplineTAcc& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new SplineTAcc(*this,newname); }
  inline virtual ~SplineTAcc() { }

  RooRealProxy t ;
  RooRealProxy x0 ;
  RooRealProxy x1 ;
  RooRealProxy x2 ;
  RooRealProxy x3 ;
  RooRealProxy x4 ;
  RooRealProxy x5 ;
  RooRealProxy c0 ;
  RooRealProxy c1 ;
  RooRealProxy c2 ;
  RooRealProxy c3 ;
  RooRealProxy c4 ;
  RooRealProxy c5 ;
  RooRealProxy c6 ;
  RooRealProxy c7 ;

  Double_t ci(Int_t i) const;
  Double_t Bid(Int_t i, Int_t d, Double_t x) const;
  Double_t polynomial(Double_t x) const;
  Double_t a_bin_deg(Int_t ibin, Int_t deg) const;

  Double_t evaluate() const;

private:

  ClassDef(SplineTAcc,1)
};
 
#endif
