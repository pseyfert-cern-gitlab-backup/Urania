/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            *
 *****************************************************************************/

#ifndef INVERSE
#define INVERSE

#include "RooAbsReal.h"
#include "RooRealProxy.h"

class Inverse : public RooAbsReal {
public:
  Inverse() {} ;
  Inverse(const char *name, const char *title,
	      RooAbsReal& _val);
  Inverse(const Inverse& other, const char* name=0) ;
  TObject* clone(const char* newname) const override { return new Inverse(*this,newname); }
  virtual ~Inverse();

protected:

  RooRealProxy val;

  Double_t evaluate() const override;

private:
  ClassDefOverride(Inverse, 1);
};

#endif
