/*****************************************************************************
 * Project: Erasmus                                                           *
 * Package: SomeMassModels                                                    *
 *    File: $Id: RooPhysBkg.h,v 1.13 2007/07/12 20:30:49 asarti Exp $
 * Authors:                                                                  *
 *           Alessio Sarti          alessio.sarti@lnf.infn.it
 * Purpose:
 * Description of the B->hh background at low masses
 *                                                                           *
 *****************************************************************************/

#include "RooFit.h"

#include "Riostream.h"
#include "Riostream.h"
#include <math.h>

#include "RooPhysBkg.h"
#include "RooRealVar.h"
#include "RooRealConstant.h"
#include "RooMath.h"
#include "TMath.h"

//ClassImp(RooPhysBkg)


//_____________________________________________________________________________
RooPhysBkg::RooPhysBkg(const char *name, const char *title,
		       RooAbsReal& _m, RooAbsReal& _m0, RooAbsReal& _c, RooAbsReal& _s) :
  RooAbsPdf(name, title), 
  m("m","Mass",this,_m),
  m0("m0","Resonance mass",this,_m0),
  c("c","Slope parameter",this,_c),
  s("s","Sigma",this,_s)
{
}



//_____________________________________________________________________________
RooPhysBkg::RooPhysBkg(const RooPhysBkg& other, const char* name) :
  RooAbsPdf(other,name), 
  m("m",this,other.m),
  m0("m0",this,other.m0),
  c("c",this,other.c),
  s("s",this,other.s)

{
}



//_____________________________________________________________________________
Double_t RooPhysBkg::evaluate() const {
  Double_t ssq=s*s;
  Double_t sfth=ssq*ssq;
  Double_t csq=c*c;
  Double_t m0sq=m0*m0;
  Double_t xsq=m0sq;
  Double_t msq=m*m;

  Double_t up = 0.5*s * ( 2*exp(m0* (c + m/ssq) - (xsq + msq)/(2.*ssq) ) *s* (-m0sq + csq*sfth + xsq + m0*m +
                 msq + ssq*(2 + c*m0 + 2*c*m) ) + exp((csq*sfth + xsq + 2*c*ssq*m + msq)/(2.*ssq) - 
                 (xsq + msq)/(2.*ssq))*sqrt(2*M_PI)*
                 (c*ssq + m)*(-m0sq + csq*sfth + msq + ssq*(3 + 2*c*m))*
                 TMath::Erf((c*ssq - m0 + m)/(sqrt(2)*s)));

  Double_t down = 0.5*s*(exp(-(msq)/(2.*ssq)) *s * 2 *s* (-m0sq + csq*sfth +
                 msq + ssq*(2 + 2*c*m)) + exp((csq*sfth + 2*c*ssq*m + msq)/(2.*ssq) -(msq)/(2.*ssq)  )*sqrt(2*M_PI)*
                 (c*ssq + m)*(-m0sq + csq*sfth + msq + ssq*(3 + 2*c*m))*
                 TMath::Erf((c*ssq + m)/(sqrt(2)*s)));

  return (up-down)<=0?0:(up-down);

}



//_____________________________________________________________________________
//Int_t RooPhysBkg::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const
//{
//
//  if (matchArgs(allVars,analVars,m)) return 1;

//  return 0;

//}



//_____________________________________________________________________________
//Double_t RooPhysBkg::analyticalIntegral(Int_t code, const char* rangeName) const
//{
//  assert(code==1);
//
//  return 1;
//}


