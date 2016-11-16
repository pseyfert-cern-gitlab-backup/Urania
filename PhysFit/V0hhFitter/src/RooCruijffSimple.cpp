/*****************************************************************************
 * Package: RooRarFit                                                        *
 *    File: $Id: RooCruijffSimple.cc,v 1.3 2007/06/29 08:37:34 zhanglei Exp $   *
 * Authors:                                                                  *
 *    Karsten Koeneke, Massachusetts Institute of Technology, Cambridge, USA *
 *    Vouter Hulbergen                                                       *
 *                                                                           *
 * Copyright (c) 2006, Massachsetts Institute of Technology, Cambridge, USA  *
 *****************************************************************************/

// This is an implementation for the Cruijff function for RooFit
// - CT modified to only have one sigma (hence 'simple')

#include "RooFit.h"

#include "Riostream.h"
#include "Riostream.h"
#include <iostream>
#include <math.h>

#include "RooAbsReal.h"
#include "RooRealVar.h"
#include "RooRealConstant.h"

#include "V0hhFitter/RooCruijffSimple.h"

//ClassImp(RooCruijffSimple);

RooCruijffSimple::RooCruijffSimple(const char *name, const char *title,
		RooAbsReal& _x, RooAbsReal& _m0, 
		RooAbsReal& _sigma,
		RooAbsReal& _alphaL, RooAbsReal& _alphaR)
    :
    RooAbsPdf(name, title),
    x("x", "x", this, _x),
    m0("m0", "m0", this, _m0),
    sigma("sigma", "sigma", this, _sigma),
    alphaL("alphaL", "alphaL", this, _alphaL),
    alphaR("alphaR", "alphaR", this, _alphaR)
{
}

RooCruijffSimple::RooCruijffSimple(const RooCruijffSimple& other, const char* name) :
  RooAbsPdf(other, name), 
  x("x", this, other.x), 
  m0("m0", this, other.m0),
  sigma("sigma", this, other.sigma), 
  alphaL("alphaL", this, other.alphaL), 
  alphaR("alphaR", this, other.alphaR)
{
}

Double_t RooCruijffSimple::evaluate() const 
{
  // build the functional form
  double _alpha = 0.0;
  double dx = (x - m0);
  if(dx<0){
    _alpha = alphaL;
  } else {
    _alpha = alphaR;
  }
  double f = 2*sigma*sigma + _alpha*dx*dx ;
  return exp(-dx*dx/f) ;
}
