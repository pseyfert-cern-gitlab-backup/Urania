/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef FOURBODYPDF
#define FOURBODYPDF

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
class FourBodyPdf : public RooAbsPdf {
public:
  FourBodyPdf() {} ; 
  FourBodyPdf(const char *name, const char *title,
	      RooAbsReal& _m1,
	      RooAbsReal& _m2,
	      RooAbsReal& _m_kst,
	      RooAbsReal& _k_kst0,
	      RooAbsReal& _g_kst,
	      RooAbsReal& _g_kst0,
	      RooAbsReal& _MBs);
  FourBodyPdf(const FourBodyPdf& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new FourBodyPdf(*this,newname); }
  inline virtual ~FourBodyPdf() { }

protected:

  RooRealProxy m1 ;
  RooRealProxy m2 ;
  RooRealProxy m_kst ;
  RooRealProxy k_kst0 ;
  RooRealProxy g_kst ;
  RooRealProxy g_kst0 ;
  RooRealProxy MBs ;
  
  Double_t evaluate() const ;

private:

  ClassDef(FourBodyPdf,1) // Your description goes here...
};
 
#endif