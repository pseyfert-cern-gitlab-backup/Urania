/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

// ROOT and RooFit includes
#include <RooAbsReal.h>
#include <cmath> 
#include <algorithm>

// B2DXFitters includes
#include "B2DXFitters/BdPTAcceptance.h"

//ClassImp(BdPTAcceptance) 


BdPTAcceptance::BdPTAcceptance(const char *name, const char *title, 
                               RooAbsReal& _t,
                               RooAbsReal& _beta, 
                               RooAbsReal& _slope,
                               RooAbsReal& _offset) :
  RooAbsReal(name,title), 
  t("t","t",this,_t),
  beta("beta","beta",this,_beta),
  slope("slope","slope",this,_slope),
  offset("offset","offset",this,_offset)
{ }

BdPTAcceptance::BdPTAcceptance(const BdPTAcceptance& other, const char* name) :  
  RooAbsReal(other,name), 
  t("t",this,other.t),
  beta("beta",this,other.beta),
  slope("slope",this,other.slope),
  offset("offset",this,other.offset)
{ }

Double_t BdPTAcceptance::evaluate() const 
{ 
  // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE
  const double o = offset, b = beta, s = slope, t = this->t;
  if ( t < o ) return 0.;
  const double var = s * ( t - o );
  if ( var < 10. ) {
    return ( 1. - std::exp( -var ) )*(1.-b*t);
  }
  else
    return 1.*(1.-b*t);
}

Int_t BdPTAcceptance::getAnalyticalIntegral(
	RooArgSet& integ, RooArgSet& anaIntSet, const char*) const
{
    if (matchArgs(integ, anaIntSet, t)) return 1;
    return 0;
}

double BdPTAcceptance::ourIntegral(const double t) const
{
    const double o = offset, b = beta, s = slope;
    return -(b * s * t - s + b) / (s * s) * std::exp(-s * (t - o)) -
	    0.5 * b * t * t + t;
}

Double_t BdPTAcceptance::analyticalIntegral(
	Int_t code, const char* rangeName) const
{
    if (1 != code) return 0.;
    const double o = offset;
    const double tmin = std::max(t.min(rangeName), o);
    const double tmax = t.max(rangeName);
    if (tmax <= tmin) return 0.;
    return ourIntegral(tmax) - ourIntegral(tmin);
}
