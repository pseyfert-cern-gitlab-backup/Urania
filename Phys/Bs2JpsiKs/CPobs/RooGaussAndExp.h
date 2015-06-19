// #############################################################################
// Phys/Bs2JpsiKs Package
// PDF description
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ############################################################################# 

// Gaussian with single sided exponential tail
// used to describe background reconstructed under the wrong mass hypothesis

#ifndef ROOGAUSSANDEXP
#define ROOGAUSSANDEXP

// #############################################################################
// *** Load Useful Classes ***
#include <iostream> 

#include <RooAbsPdf.h>
#include <RooAbsReal.h>
#include <RooRealProxy.h>

// #############################################################################
// *** Class Members ***
class RooGaussAndExp : public RooAbsPdf {
public:

  // *** Constructer - Clone - Desctructor ***
  RooGaussAndExp(const char *name, const char *title, RooAbsReal& _mass,
                 RooAbsReal& _mean, RooAbsReal& _sigma, RooAbsReal& _shift);
  RooGaussAndExp(const RooGaussAndExp& other, const char* name=0);
  virtual TObject* clone(const char* newname) const {
    return new RooGaussAndExp(*this,newname);
  }
  inline virtual ~RooGaussAndExp() {}

protected:

  RooRealProxy mass;
  RooRealProxy mean;
  RooRealProxy sigma;
  RooRealProxy shift;
  
  Double_t evaluate() const;

private:

};
 
#endif
// #############################################################################