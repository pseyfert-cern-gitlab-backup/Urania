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
#ifndef ROO_PHYS_BKG
#define ROO_PHYS_BKG

#include "RooAbsPdf.h"
#include "RooRealProxy.h"

class RooRealVar;
class RooAbsReal;

class RooPhysBkg : public RooAbsPdf {
public:
  RooPhysBkg() {} ;
  RooPhysBkg(const char *name, const char *title, 
	     RooAbsReal& _m, RooAbsReal& _m0, RooAbsReal& _c, RooAbsReal& _s);
  RooPhysBkg(const RooPhysBkg& other,const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooPhysBkg(*this,newname); }
  inline virtual ~RooPhysBkg() { }

//  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
//  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;

protected:
  RooRealProxy m ;
  RooRealProxy m0 ;
  RooRealProxy c ;
  RooRealProxy s ;

  Double_t evaluate() const ;
//   void initGenerator();

private:
  ClassDef(RooPhysBkg,1) // Argus background shape PDF
};

#endif
