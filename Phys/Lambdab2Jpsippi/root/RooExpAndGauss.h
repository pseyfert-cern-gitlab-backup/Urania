/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
 * Copyright (c) 2000-2005, Regents of the University of California          *
 *                          and Stanford University. All rights reserved.    *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/

#ifndef ROOEXPANDGAUSS
#define ROOEXPANDGAUSS

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooAbsReal.h"
 
class RooExpAndGauss : public RooAbsPdf {
public:
  RooExpAndGauss(const char *name, const char *title,
	      RooAbsReal& _m,
	      RooAbsReal& _m0,
	      RooAbsReal& _sigma,
	      RooAbsReal& _m1);
  RooExpAndGauss(const RooExpAndGauss& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooExpAndGauss(*this,newname); }
  inline virtual ~RooExpAndGauss() { }

protected:

  RooRealProxy m ;
  RooRealProxy m0 ;
  RooRealProxy sigma ;
  RooRealProxy m1 ;
  
  Double_t evaluate() const ;

private:

  //  ClassDef(RooExpAndGauss,0) // Your description goes here...  /// Had to remove that ???
};
 
#endif
