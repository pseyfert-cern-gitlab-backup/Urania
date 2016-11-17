/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef ANGABSFUNC
#define ANGABSFUNC

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "RooListProxy.h"
#include "RooArgList.h"

 
class AngAbsFunc : public RooAbsReal {
public:
  AngAbsFunc():RooAbsReal(){} ; 
    AngAbsFunc(const char *name, const char *title,
			       RooAbsReal& _c1,
			       RooAbsReal& _c2,
			       RooAbsReal& _ph,
			       RooArgList& _accTH_coefList,
	                       RooArgList& _accPH_coefList);

    AngAbsFunc(const AngAbsFunc& other, const char* name=0);

    ~AngAbsFunc() { }

    virtual Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
/*     virtual Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ; */

    Double_t getAccTHCoefs(Double_t* coefsTH)const;
    Double_t getAccPHCoefs(Double_t* coefsPH)const;

protected:

  RooRealProxy c1 ;
  RooRealProxy c2 ;
  RooRealProxy ph ;
  RooListProxy accTH_coefList;
  RooListProxy accPH_coefList;
  TIterator* coefIterTH;
  TIterator* coefIterPH;

  
private:

  ClassDef(AngAbsFunc,1) // Your description goes here...
};
 
#endif