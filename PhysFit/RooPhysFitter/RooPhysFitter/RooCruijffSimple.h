#ifndef ROO_CRUIJFFSIMPLE_H
#define ROO_CRUIJFFSIMPLE_H 1

#include "RooAbsPdf.h"
#include "RooRealProxy.h"

class RooRealVar;
//class RooAbsReal;

class RooCruijffSimple : public RooAbsPdf {
public:
  RooCruijffSimple() { }
  RooCruijffSimple(const char *name, const char *title,
                   RooAbsReal& _x,
                   RooAbsReal& _m0,
                   RooAbsReal& _sigma,
                   RooAbsReal& _alphaL, RooAbsReal& _alphaR);

  RooCruijffSimple(const RooCruijffSimple& other, const char* name = 0);

  TObject* clone(const char* newname) const override {
    return new RooCruijffSimple(*this,newname);
  }

  inline virtual ~RooCruijffSimple() { }

 protected:
  RooRealProxy x;
  RooRealProxy m0;
  RooRealProxy sigma;
  RooRealProxy alphaL;
  RooRealProxy alphaR;

  Double_t evaluate() const override;

private:
  ClassDef(RooCruijffSimple,1); //Simple Cruijff lineshape PDF
};

#endif
