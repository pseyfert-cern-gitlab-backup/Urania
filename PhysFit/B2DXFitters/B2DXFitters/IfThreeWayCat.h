/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef IFTHREEWAYCAT
#define IFTHREEWAYCAT

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
class IfThreeWayCat : public RooAbsReal {
public:
  IfThreeWayCat() {} ; 
  IfThreeWayCat(const char *name, const char *title,
	      RooAbsCategory& _cond,
	      RooAbsReal& _pos,
	      RooAbsReal& _zero,
	      RooAbsReal& _neg);
  IfThreeWayCat(const IfThreeWayCat& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new IfThreeWayCat(*this,newname); }
  virtual ~IfThreeWayCat();

protected:

  RooCategoryProxy cond;
  RooRealProxy pos;
  RooRealProxy zero;
  RooRealProxy neg;
  
  Double_t evaluate() const;

private:
  ClassDef(IfThreeWayCat, 1);
};
 
#endif
