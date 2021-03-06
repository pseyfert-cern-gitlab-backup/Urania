/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef ANGJPSIKST
#define ANGJPSIKST

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
class AngJPsiKst : public RooAbsPdf {
public:
  AngJPsiKst() {} ; 
  AngJPsiKst(const char *name, const char *title,
	      RooAbsReal& _CPsi,
	      RooAbsReal& _CTheta,
	      RooAbsReal& _Phi,
	      RooAbsReal& _A0,
	      RooAbsReal& _Apa,
	      RooAbsReal& _Ape,
	      RooAbsReal& _cdpa,
	      RooAbsReal& _c1_psi,
	      RooAbsReal& _c2_psi,
	      RooAbsReal& _c3_psi,
	      RooAbsReal& _c4_psi,
	      RooAbsReal& _c5_psi,
	      RooAbsReal& _c1_theta,
	      RooAbsReal& _c2_theta,
	      RooAbsReal& _c1_phi,
	      RooAbsReal& _c2_phi,
	      RooAbsReal& _c3_phi,
	      RooAbsReal& _c4_phi,
	      RooAbsReal& _c5_phi,
	      RooAbsReal& _c6_phi);
  AngJPsiKst(const AngJPsiKst& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new AngJPsiKst(*this,newname); }
  inline virtual ~AngJPsiKst() { }

protected:

  RooRealProxy CPsi ;
  RooRealProxy CTheta ;
  RooRealProxy Phi ;
  RooRealProxy A0 ;
  RooRealProxy Apa ;
  RooRealProxy Ape ;
  RooRealProxy cdpa ;
  RooRealProxy c1_psi ;
  RooRealProxy c2_psi ;
  RooRealProxy c3_psi ;
  RooRealProxy c4_psi ;
  RooRealProxy c5_psi ;
  RooRealProxy c1_theta ;
  RooRealProxy c2_theta ;
  RooRealProxy c1_phi ;
  RooRealProxy c2_phi ;
  RooRealProxy c3_phi ;
  RooRealProxy c4_phi ;
  RooRealProxy c5_phi ;
  RooRealProxy c6_phi ;
  
  Double_t evaluate() const ;

private:

  ClassDef(AngJPsiKst,1) // Your description goes here...
};
 
#endif
