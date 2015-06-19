// #############################################################################
// Phys/Bs2JpsiKs Package
// PDF description
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ############################################################################# 

// Gaussian with single sided exponential tail
// used to describe background reconstructed under the wrong mass hypothesis

// #############################################################################
// *** Load Useful Classes ***
#include "RooGaussAndExp.h"  

// #############################################################################
// *** Constructor ***
RooGaussAndExp::RooGaussAndExp(const char *name, const char *title, 
                               RooAbsReal& _mass, RooAbsReal& _mean,
                               RooAbsReal& _sigma, RooAbsReal& _shift) :
  RooAbsPdf(name, title), 
  mass( "mass",  "mass",  this, _mass),
  mean( "mean",  "mean",  this, _mean),
  sigma("sigma", "sigma", this, _sigma),
  shift("shift", "shift", this, _shift) {}

RooGaussAndExp::RooGaussAndExp(const RooGaussAndExp& other, const char* name) :  
  RooAbsPdf(other,name), 
  mass( "mass",  this, other.mass),
  mean( "mean",  this, other.mean),
  sigma("sigma", this, other.sigma),
  shift("shift", this, other.shift) {}

// #############################################################################
// *** Evaluate ***
Double_t RooGaussAndExp::evaluate() const { 
  double x     = (mass-mean)/sigma; // exponent of gaussian
  double gauss = exp(-0.5*x*x);     // actual value of gaussian
  double trans = mean + shift;

  if ((shift>0 && mass < trans) || (shift<0 && mass > trans)) return gauss;

  Double_t xval     = (trans-mean)/sigma;     // exponent of gaussian at trans
  Double_t gaussval = exp(-0.5*xval*xval);    // value of gaussian at trans  
  Double_t slope    = -gaussval * xval/sigma; // derivative of gaussian at trans

  Double_t B = slope/gaussval;
  Double_t A = gaussval/exp(B*trans);

  return A*exp(B*mass); // exponential
} 

// #############################################################################