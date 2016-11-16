#include "RooFit.h"

#include "Riostream.h"
#include "Riostream.h"
#include <math.h>

#include "RooErrXLin.h"
#include "RooRealVar.h"
#include "RooRealConstant.h"
#include "RooMath.h"
#include "TMath.h"

ClassImp(RooErrXLin)


//_____________________________________________________________________________
RooErrXLin::RooErrXLin(const char *name, const char *title,
		       RooAbsReal& _m, RooAbsReal& _m0, RooAbsReal& _c, RooAbsReal& _s) :
  RooAbsPdf(name, title), 
  m("m","Mass",this,_m),
  m0("m0","Resonance mass",this,_m0),
  c("c","Slope parameter",this,_c),
  s("s","Sigma",this,_s)
{
}



//_____________________________________________________________________________
RooErrXLin::RooErrXLin(const RooErrXLin& other, const char* name) :
  RooAbsPdf(other,name), 
  m("m",this,other.m),
  m0("m0",this,other.m0),
  c("c",this,other.c),
  s("s",this,other.s)

{
}



//_____________________________________________________________________________
Double_t RooErrXLin::evaluate() const {

  return (c*(m-m0)+1)*0.5*(1-TMath::Erf(((m-m0)/s-1)/0.5));

}



//_____________________________________________________________________________
//Int_t RooErrXLin::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const
//{
//
//  if (matchArgs(allVars,analVars,m)) return 1;

//  return 0;

//}



//_____________________________________________________________________________
//Double_t RooErrXLin::analyticalIntegral(Int_t code, const char* rangeName) const
//{
//  assert(code==1);
//
//  return 1;
//}


