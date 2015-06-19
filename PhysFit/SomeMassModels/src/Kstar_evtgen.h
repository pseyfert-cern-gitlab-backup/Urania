/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef KSTAR_EVTGEN
#define KSTAR_EVTGEN

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

class Kstar_evtgen : public RooAbsPdf {
public:
  Kstar_evtgen() {} ; 
  Kstar_evtgen(const char *name, const char *title,
	       RooAbsReal& _m,   // mass of P
	       RooAbsReal& _m0,  // m0 of P
	       RooAbsReal& _g0,  // g0 of P
	       RooAbsReal& _mDa, // mass of the first daughter of P
	       RooAbsReal& _mDb, // mass of the second daughter of P
	       RooAbsReal& _J,   // angular momentum in the decay P->Da Db
	       RooAbsReal& _MB,  // mass of the mother of P 
	       RooAbsReal& _MV,  // mass of X in the decay G-> P X 
	       RooAbsReal& _l);  // angular momentum in the decay G-> P X 

  Kstar_evtgen(const Kstar_evtgen& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new Kstar_evtgen(*this,newname); }
  inline virtual ~Kstar_evtgen() { }

protected:

  RooRealProxy m ;
  RooRealProxy m0 ;
  RooRealProxy g0 ;
  RooRealProxy mDa ;
  RooRealProxy mDb ;
  RooRealProxy J ;
  RooRealProxy MB ;
  RooRealProxy MV ;
  RooRealProxy l ;
  
  Double_t evaluate() const ;

private:

  ClassDef(Kstar_evtgen,1) // Your description goes here...
};
 
#endif
