/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 * @(#)root/roofit:$Id: RooBifurcatedCB.cxx 28259 2009-04-16 16:21:16Z wouter $
 * Authors:                                                                  *
 *   Patrick Koppenburg                                                      *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
//
// BEGIN_HTML
// P.d.f implementing the Crystall Ball line shape
// END_HTML
//

#include "RooFit.h"

#include "Riostream.h"
#include <math.h>

#include "RooBifurcatedCB.h"
#include "RooAbsReal.h"
#include "RooRealVar.h"
#include "RooMath.h"
#include "TMath.h"

// ClassImp(RooBifurcatedCB) // causes linking problems
;

//_____________________________________________________________________________
Double_t RooBifurcatedCB::ApproxErf(Double_t arg) const 
{
  static const double erflim = 5.0;
  if( arg > erflim )
    return 1.0;
  if( arg < -erflim )
    return -1.0;
  
  return RooMath::erf(arg);
}


static const char rcsid[] =
"$Id: RooBifurcatedCB.cpp 28259 2009-04-16 16:21:16Z wouter $";


//_____________________________________________________________________________
RooBifurcatedCB::RooBifurcatedCB(const char *name, const char *title,
				 RooAbsReal& _m, RooAbsReal& _m0, 
				 RooAbsReal& _sigma, RooAbsReal& _alpha, RooAbsReal& _n, 
				 RooAbsReal& _sigma2, RooAbsReal& _alpha2, RooAbsReal& _n2) :
  RooAbsPdf(name, title),
  m("m", "Dependent", this, _m),
  m0("m0", "M0", this, _m0),
  sigma("sigma", "Sigma, left", this, _sigma),
  alpha("alpha", "Alpha, left", this, _alpha),
  n("n", "Order, right", this, _n),
  sigma2("sigma2", "Sigma, right", this, _sigma2),
  alpha2("alpha2", "Alpha, right", this, _alpha2),
  n2("n2", "Order, right", this, _n2)
{
}


//_____________________________________________________________________________
RooBifurcatedCB::RooBifurcatedCB(const RooBifurcatedCB& other, const char* name) :
  RooAbsPdf(other, name), 
  m("m", this, other.m), m0("m0", this, other.m0),
  sigma("sigma", this, other.sigma), 
  alpha("alpha", this, other.alpha),
  n("n", this, other.n), 
  sigma2("sigma2", this, other.sigma2), 
  alpha2("alpha2", this, other.alpha2),
  n2("n2", this, other.n2)
{
}

//_____________________________________________________________________________
Double_t RooBifurcatedCB::evaluate() const {

  if (m<m0){ // left side
    return evaluate(sigma,alpha,n);
  } else {
    return evaluate(sigma2,-alpha2,n2);
  }
}

//_____________________________________________________________________________
Double_t RooBifurcatedCB::evaluate(double i_sigma, double i_alpha, double i_n) const {

  Double_t t = (m-m0)/i_sigma;
  if (i_alpha < 0) t = -t;
  Double_t absAlpha = fabs((Double_t)i_alpha);

  //  std::cout << m << " " << t << " " << i_alpha << endl ;
  if (t >= -absAlpha) {
    return exp(-0.5*t*t);
  } else {
    Double_t a =  TMath::Power(i_n/absAlpha,n)*exp(-0.5*absAlpha*absAlpha);
    Double_t b= i_n/absAlpha - absAlpha; 
    return a/TMath::Power(b - t, i_n);
  }
}
//_____________________________________________________________________________
Int_t RooBifurcatedCB::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const
{
  if( matchArgs(allVars,analVars,m) )
    return 1 ;
  
  return 0;
}

//_____________________________________________________________________________
Double_t RooBifurcatedCB::analyticalIntegral(Int_t code, const char* rangeName) const
{
  assert(code==1);
  double mmin = (m.min(rangeName)-m0) ;
  double mmax = (m.max(rangeName)-m0) ;

  // three possibilities 
  if ( mmax < 0 ){
    return analyticalIntegral(mmin, mmax, sigma, alpha, n); // left side only
  } else if ( mmin > 0 ){
    return analyticalIntegral(mmin, mmax, sigma2, -alpha2, n2); // right side only
  } else {
    return analyticalIntegral(mmin, 0., sigma, alpha, n)+
      analyticalIntegral(0., mmax, sigma2, -alpha2, n2) ;
   
  }
}

//_____________________________________________________________________________
Double_t RooBifurcatedCB::analyticalIntegral(double i_mmin, double i_mmax, 
					     double i_sigma, double i_alpha, 
					     double i_n) const
{
  static const double sqrtPiOver2 = 1.2533141373;
  static const double sqrt2 = 1.4142135624;

  double result = 0.0;
  bool useLog = false;
  
  if( fabs(i_n-1.0) < 1.0e-05 )
    useLog = true;
  
  double sig = fabs((Double_t)i_sigma);
  
  double tmin = i_mmin/sig;
  double tmax = i_mmax/sig;
  
  if(i_alpha < 0) {
    double tmp = tmin;
    tmin = -tmax;
    tmax = -tmp;
  }

  double absAlpha = fabs((Double_t)i_alpha);
  
  if( tmin >= -absAlpha ) {
    result += sig*sqrtPiOver2*(   ApproxErf(tmax/sqrt2)
                                - ApproxErf(tmin/sqrt2) );
  }
  else if( tmax <= -absAlpha ) {
    double a = TMath::Power(i_n/absAlpha,i_n)*exp(-0.5*absAlpha*absAlpha);
    double b = i_n/absAlpha - absAlpha;
    
    if(useLog) {
      result += a*sig*( log(b-tmin) - log(b-tmax) );
    }
    else {
      result += a*sig/(1.0-i_n)*(   1.0/(TMath::Power(b-tmin,i_n-1.0))
				  - 1.0/(TMath::Power(b-tmax,i_n-1.0)) );
    }
  }
  else {
    double a = TMath::Power(i_n/absAlpha,i_n)*exp(-0.5*absAlpha*absAlpha);
    double b = i_n/absAlpha - absAlpha;
    
    double term1 = 0.0;
    if(useLog) {
      term1 = a*sig*(  log(b-tmin) - log(n/absAlpha));
    }
    else {
      term1 = a*sig/(1.0-i_n)*(   1.0/(TMath::Power(b-tmin,i_n-1.0))
                              - 1.0/(TMath::Power(i_n/absAlpha,i_n-1.0)) );
    }
    
    double term2 = sig*sqrtPiOver2*(   ApproxErf(tmax/sqrt2)
                                     - ApproxErf(-absAlpha/sqrt2) );
    
    
    result += term1 + term2;
  }
  
  return result;
}



//_____________________________________________________________________________
Int_t RooBifurcatedCB::getMaxVal(const RooArgSet& vars) const 
{
  // Advertise that we know the maximum of self for given (m0,alpha,n,sigma)
  RooArgSet dummy ;

  if (matchArgs(vars,dummy,m)) {
    return 1 ;  
  }
  return 0 ;  
}



//_____________________________________________________________________________
Double_t RooBifurcatedCB::maxVal(Int_t code) const
{
  assert(code==1) ;

  // The maximum value for given (m0,alpha,n,sigma)
  return 1.0 ;
}


