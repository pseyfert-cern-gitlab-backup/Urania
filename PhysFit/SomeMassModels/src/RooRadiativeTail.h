/*****************************************************************************
 * Project: Erasmus                                                           *
 * Package: SomeMassModels                                                    *
 *    File: $Id: RooRadiativeTail.h,v 1.13 2007/07/12 20:30:49 asarti Exp $
 * Authors:                                                                  *
 *           Alessio Sarti          alessio.sarti@lnf.infn.it
 * Purpose:
 * Description of the B->hh exclusive peak
 *                                                                           *
 *****************************************************************************/


#ifndef ROO_RADIATIVETAIL
#define ROO_RADIATIVETAIL

#include "RooAbsPdf.h"
#include "RooRealProxy.h"

class RooRealVar;

class RooRadiativeTail : public RooAbsPdf {
public:
  RooRadiativeTail() {} ;
  RooRadiativeTail(const char *name, const char *title,
	      RooAbsReal& _mass, RooAbsReal& _slope, RooAbsReal& _mean, RooAbsReal& _sigma);
  RooRadiativeTail(const RooRadiativeTail& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooRadiativeTail(*this,newname); }
  inline virtual ~RooRadiativeTail() { }

  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;

protected:

  RooRealProxy mass ;
  RooRealProxy slope ;
  RooRealProxy mean ;
  RooRealProxy sigma ;
  
  Double_t evaluate() const ;

private:

  ClassDef(RooRadiativeTail,1)
};

#endif
