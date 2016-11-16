#ifndef ACCPDF
#define ACCPDF

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "TComplex.h"
#include "TF1.h"

class accpdf : public RooAbsReal {
public:
  accpdf() {} ; 
  accpdf(const char *name, const char *title,
           RooAbsReal& _m1,
           RooAbsReal& _m2,
           RooAbsReal& _cos1,
           RooAbsReal& _cos2,
           RooAbsReal& _phi,
           RooAbsReal& _t,
	   RooAbsReal& _k1,
	   RooAbsReal& _k2,
	   RooAbsReal& _k3,
	   RooAbsReal& _k4,
	   RooAbsReal& _p1,
	   RooAbsReal& _a_acc,
	   RooAbsReal& _b_acc,
	   RooAbsReal& _option);
  accpdf(const accpdf& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new accpdf(*this,newname); }
  inline virtual ~accpdf() { }

  RooRealProxy m1 ;
  RooRealProxy m2 ;
  RooRealProxy cos1 ;
  RooRealProxy cos2 ;
  RooRealProxy phi ;
  RooRealProxy t ;
  RooRealProxy k1 ;
  RooRealProxy k2 ;
  RooRealProxy k3 ;
  RooRealProxy k4 ;
  RooRealProxy p1 ;
  RooRealProxy a_acc ;
  RooRealProxy b_acc ;
  RooRealProxy option ;
  
  Double_t accCos(Double_t x) const;
  Double_t accPhi(Double_t x) const;
  Double_t accMass(Double_t x) const;
  Double_t accTime(Double_t x) const;
  Double_t evaluate() const;

private:

  ClassDef(accpdf,1)
};
 
#endif
