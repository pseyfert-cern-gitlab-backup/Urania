/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
 * This code was autogenerated by RooClassFactory                            *
 *****************************************************************************/

#ifndef ROOAMOROSO
#define ROOAMOROSO

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

class RooAmoroso : public RooAbsPdf {
public:
   RooAmoroso() {} ;
   RooAmoroso(const char *name, const char *title,
              RooAbsReal& _x,
              RooAbsReal& _a,
              RooAbsReal& _theta,
              RooAbsReal& _alpha,
              RooAbsReal& _beta);
   RooAmoroso(const RooAmoroso& other, const char* name=0) ;
   TObject* clone(const char* newname) const override { return new RooAmoroso(*this,newname); }
   inline virtual ~RooAmoroso() { }

protected:

   RooRealProxy x ;
   RooRealProxy a ;
   RooRealProxy theta ;
   RooRealProxy alpha ;
   RooRealProxy beta ;

   Double_t evaluate() const override;

private:

   ClassDef(RooAmoroso,1) // Your description goes here...
};

#endif
