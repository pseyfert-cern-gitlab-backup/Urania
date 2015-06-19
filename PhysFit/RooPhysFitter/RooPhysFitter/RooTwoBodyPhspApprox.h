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
  virtual TObject* clone(const char* newname) const { return new RooTwoBodyPhspApprox(*this,newname); }
  inline virtual ~RooTwoBodyPhspApprox() { }

  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, 
                              const char* rangeName=0) const ;
  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;
  
protected:
  
  RooRealProxy DeltaM;
  RooRealProxy coef1;
  RooRealProxy coef2;

  Double_t evaluate() const;

private:
 
  ClassDef(RooTwoBodyPhspApprox,1)
};

#endif
