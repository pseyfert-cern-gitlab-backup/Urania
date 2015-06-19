/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef ACCEPTANCE
#define ACCEPTANCE

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

 
class Acceptance : public RooAbsReal {
public:
  Acceptance() {} ; 
  Acceptance(const char *name, const char *title,
	      RooAbsReal& _c1,
	      RooAbsReal& _c2,
	      RooAbsReal& _ph,
	      RooAbsReal& _m1,
	      RooAbsReal& _m2,
	     Int_t *_orders,
	     double **_coeffs);

/*   Acceptance(const char *name, const char *title, */
/* 	      RooAbsReal& _c1, */
/* 	      RooAbsReal& _c2, */
/* 	      RooAbsReal& _ph, */
/* 	      RooAbsReal& _m1, */
/* 	      RooAbsReal& _m2, */
/* 	      Int_t *_orders, */
/* 	     Double_t *****_coeffs); */
  Acceptance(const Acceptance& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new Acceptance(*this,newname); }
  inline virtual ~Acceptance() { }


  Int_t *orders;
  double **coeffs;
  //Double_t coeffs[][3][3][3][3];
  RooRealProxy c1 ;
  RooRealProxy c2 ;
  RooRealProxy ph ;
  RooRealProxy m1 ;
  RooRealProxy m2 ;

  
  Double_t evaluate() const ;
protected:

private:

  ClassDef(Acceptance,1) // Your description goes here...
};
 
#endif
