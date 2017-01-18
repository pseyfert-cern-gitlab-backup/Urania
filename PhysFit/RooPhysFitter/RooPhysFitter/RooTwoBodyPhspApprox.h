#ifndef ROO_TWOBODYPHSPAPPROX_H
#define ROO_TWOBODYPHSPAPPROX_H 1

#include "RooAbsPdf.h"
#include "RooRealProxy.h"

class RooRealVar;

class RooTwoBodyPhspApprox : public RooAbsPdf {
public:
  RooTwoBodyPhspApprox() {}
  RooTwoBodyPhspApprox(const char *name, const char *title,
                       RooAbsReal& _DeltaM, RooAbsReal& _coef1,
                       RooAbsReal& _coef2);
  RooTwoBodyPhspApprox(const RooTwoBodyPhspApprox& other, const char* name = 0);
  TObject* clone(const char* newname) const override { return new RooTwoBodyPhspApprox(*this,newname); }
  inline ~RooTwoBodyPhspApprox() { }

  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars,
                      const char* rangeName=0) const override;
  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const override;

protected:

  RooRealProxy DeltaM;
  RooRealProxy coef1;
  RooRealProxy coef2;

  Double_t evaluate() const override;

private:

  ClassDef(RooTwoBodyPhspApprox,1)
};

#endif
