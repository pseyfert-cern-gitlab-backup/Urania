#ifndef ROOTHRESHOLDDELTAM
#define ROOTHRESHOLDDELTAM

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

class RooThresholdDeltaM : public RooAbsPdf {
public:
  RooThresholdDeltaM() {} ;
  RooThresholdDeltaM(const char *name, const char *title,
          RooAbsReal& _x,
          RooAbsReal& _dm0,
          RooAbsReal& _c);
  RooThresholdDeltaM(const RooThresholdDeltaM& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooThresholdDeltaM(*this,newname); }
  inline virtual ~RooThresholdDeltaM() { }

protected:

  RooRealProxy x ;
  RooRealProxy dm0 ;
  RooRealProxy c ;

  Double_t evaluate() const ;

private:

  //ClassDef(RooThresholdDeltaM,1) // Your description goes here...
};

#endif