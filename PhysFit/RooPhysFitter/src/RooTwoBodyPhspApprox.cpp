#include "Riostream.h"

#include <cmath>

#include "RooAbsReal.h"
#include "RooRealVar.h"

#include "RooPhysFitter/RooTwoBodyPhspApprox.h"

RooTwoBodyPhspApprox::RooTwoBodyPhspApprox(const char *name, const char *title,
                                           RooAbsReal& _DeltaM, RooAbsReal& _coef1,RooAbsReal& _coef2) :
  RooAbsPdf(name, title),
  DeltaM("DeltaM", "DeltaM", this, _DeltaM),
  coef1("coef1", "coef1", this, _coef1),
  coef2("coef2", "coef2", this, _coef2)
{
}

RooTwoBodyPhspApprox::RooTwoBodyPhspApprox(const RooTwoBodyPhspApprox& other, 
                                           const char* name) :
  RooAbsPdf(other, name),
  DeltaM("DeltaM", this, other.DeltaM),
  coef1("coef1", this, other.coef1),
  coef2("coef2", this, other.coef2)
{
}

Double_t RooTwoBodyPhspApprox::evaluate() const 
{
  Double_t mPi = 139.57;

  Double_t Q = DeltaM - mPi;

  if (Q <= 0.0) return 0.0;

  Double_t val = sqrt(Q) + coef1 * pow(Q, 1.5) + coef2 * pow(Q, 2.5);
  if (val >= 0.0) return val;
  return 0.0;
}

Int_t RooTwoBodyPhspApprox::getAnalyticalIntegral(RooArgSet& allVars, 
                                                  RooArgSet& analVars,
                                                  const char* /*rangeName*/) const 
{
  if (matchArgs(allVars,analVars,DeltaM)) return 1 ;
  return 0 ;
}

Double_t RooTwoBodyPhspApprox::analyticalIntegral(Int_t code, 
                                                  const char* rangeName) const 
{
  assert(code == 1);
  (void)code;
  
  Double_t mPi = 139.57;

  Double_t Qmin = DeltaM.min(rangeName) - mPi;
  Double_t Qmax = DeltaM.max(rangeName) - mPi;

  if (Qmin < 0.0) Qmin = 0.0;

  Double_t intmin = (2.0/3.0) * pow(Qmin, 1.5) + (2.0/5.0) * coef1 * pow(Qmin, 2.5) + (2.0/7.0) * coef2 * pow(Qmin, 3.5);
  Double_t intmax = (2.0/3.0) * pow(Qmax, 1.5) + (2.0/5.0) * coef1 * pow(Qmax, 2.5) + (2.0/7.0) * coef2 * pow(Qmax, 3.5);

  return intmax - intmin;
}

