// $Id: $
// Include files

// BEGIN_HTML
// Phi -> K+K- background model P.D.F used in the LHCb phi cross-section
// analysis (http://arxiv.org/abs/1107.3935)
// END_HTML

#include "Riostream.h"
 
#include <cmath> 
#include "TMath.h" 

#include "RooAbsReal.h" 
#include "RooRealVar.h"
#include "RooIntegrator1D.h"
#include "RooAbsFunc.h"

// local
#include "RooPhysFitter/RooPhiBg.h"

//-----------------------------------------------------------------------------
// Implementation file for class : RooPhiBg
//
// 2011-09-09 : Philip Hunt (LHCB)
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
RooPhiBg::RooPhiBg( const char* name, const char* title,
                    RooAbsReal& _x, RooAbsReal& _c1, RooAbsReal& _c2 ) :
  RooAbsPdf(name, title),
  x("x","x",this,_x),
  c1("c1","c1",this,_c1),
  c2("c2","c2",this,_c2)
{ 
}

RooPhiBg::RooPhiBg( const RooPhiBg& other, const char* name ) :
  RooAbsPdf(other, name),
  x("x",this,other.x),
  c1("c1",this,other.c1),
  c2("c2",this,other.c2)
{
}

Double_t RooPhiBg::evaluate() const 
{
  if (c1==0||c2==x) return 1;
  Double_t val = 1 - TMath::Exp(c1*(x-c2));
  return val;
}

Int_t RooPhiBg::getAnalyticalIntegral(RooArgSet& /*allVars*/,
                                      RooArgSet& /*analVars*/,
                                      const char* /*rangeName*/) const 
{
  // if (matchArgs(allVars,analVars,x)) return 1 ; 
  return 0 ; 
} 

Double_t RooPhiBg::analyticalIntegral(Int_t code, 
                                      const char* rangeName) const  
{ 
  assert(code==1) ;  
  (void)code;
  Double_t min = x.min(rangeName);
  Double_t max = x.max(rangeName);
  if (c1==0) return 0;
  return (TMath::Exp(c1*(min-c2))-TMath::Exp(c1*(max-c2)))/(c1*c1);
}

