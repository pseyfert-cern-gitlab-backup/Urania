#ifndef ROO_ERRX_LIN
#define ROO_ERRX_LIN

#include "RooAbsPdf.h"
#include "RooRealProxy.h"

class RooRealVar;
class RooAbsReal;

class RooErrXLin : public RooAbsPdf {
public:
  RooErrXLin() {} ;
  RooErrXLin(const char *name, const char *title, 
	     RooAbsReal& _m, RooAbsReal& _m0, RooAbsReal& _c, RooAbsReal& _s);
  RooErrXLin(const RooErrXLin& other,const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooErrXLin(*this,newname); }
  inline virtual ~RooErrXLin() { }

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
  ClassDef(RooErrXLin,1) // Argus background shape PDF
};

#endif
