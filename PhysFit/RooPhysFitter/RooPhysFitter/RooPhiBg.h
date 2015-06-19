// $Id: $
#ifndef ROOPHYSFITTER_ROOPHIBG_H 
#define ROOPHYSFITTER_ROOPHIBG_H 1

// Include files
#include "RooAbsPdf.h"
#include "RooRealProxy.h"

// forward declarations
class RooRealVar;

/** @class RooPhiBg RooPhiBg.h RooPhysFitter/RooPhiBg.h
 *  
 *
 *  @author Philip Hunt (LHCB)
 *  @date   2011-09-09
 *
 */
class RooPhiBg : public RooAbsPdf {
public: 
  /// Standard constructor
  RooPhiBg( ) {}
  RooPhiBg(const char* name, const char* title,
           RooAbsReal& _x, RooAbsReal& _c1,
           RooAbsReal& _c2);
  RooPhiBg(const RooPhiBg& other, const char* name=0);
  virtual TObject* clone(const char* newname) const 
  {
    return new RooPhiBg(*this,newname);
  }
  
  inline virtual ~RooPhiBg( ) {}
  
  Int_t getAnalyticalIntegral(RooArgSet& allVars, 
                              RooArgSet& analVars,
                              const char* rangeName=0) const ;
  Double_t analyticalIntegral(Int_t code, 
                              const char* rangeName=0) const ;

protected:
  RooRealProxy x ;
  RooRealProxy c1 ;
  RooRealProxy c2 ;

  Double_t evaluate() const;
  
private:
  ClassDef(RooPhiBg,1);
};
#endif // ROOPHYSFITTER_ROOPHIBG_H
