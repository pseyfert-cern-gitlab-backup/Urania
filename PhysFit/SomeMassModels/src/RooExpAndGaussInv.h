 /*****************************************************************************
 * Project: Erasmus                                                           *
 * Package: SomeMassModels                                                    *
 *    File: $Id: RooExpAndGauss.h,v 1.13 2007/07/12 20:30:49 diegoms Exp $
 * Authors:                                                                  *
 *           Diego Martinez Santos          diego.martinez.santos@cern.ch
 * Purpose:
 * Description of the B->JPsiK + pion background
 *                                                                           *
 *****************************************************************************/


 // -- CLASS DESCRIPTION [PDF] -- 
 // This function describes approximately the bkg from B->JpsiK + pion in 
/// Bd -->JpsiK*



#ifndef ROOEXPANDGAUSSINV
#define ROOEXPANDGAUSSINV

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooAbsReal.h"
 
class RooExpAndGaussInv : public RooAbsPdf {
public:
  RooExpAndGaussInv(const char *name, const char *title,
	      RooAbsReal& _x,
	      RooAbsReal& _sh_mean,
	      RooAbsReal& _sh_sigma,
	      RooAbsReal& _sh_trans);
  RooExpAndGaussInv(const RooExpAndGaussInv& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooExpAndGaussInv(*this,newname); }
  inline virtual ~RooExpAndGaussInv() { }

protected:

  RooRealProxy x ;
  RooRealProxy sh_mean ;
  RooRealProxy sh_sigma ;
  RooRealProxy sh_trans ;
  
  Double_t evaluate() const ;

private:

  ClassDef(RooExpAndGaussInv,0) // Your description goes here...
};
 
#endif
