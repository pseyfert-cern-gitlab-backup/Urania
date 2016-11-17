/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef FOURB_MASS
#define FOURB_MASS

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "TComplex.h"
#include "MassAbsFunc.h"

 
class FourB_Mass : public MassAbsFunc {
public:
  FourB_Mass(): MassAbsFunc() {} ; 
  FourB_Mass(const char *name, const char *title,
	      RooAbsReal& _m1,
	      RooAbsReal& _m2,
	      RooAbsReal& _m_kst,
	      RooAbsReal& _m_kst0,
	      RooAbsReal& _g_kst,
	      RooAbsReal& _g_kst0,
	     RooAbsReal& _m_Bs,
	  RooArgList& _acc_coefList,
	  RooAbsReal& _norm,
	  RooAbsReal& _MBs):
    MassAbsFunc(name, title, _m1, _m2, _m_kst, _m_kst0, _g_kst, _g_kst0, _m_Bs, _acc_coefList,_norm),
    MBs("MBs","MBs",this,_MBs){}

    FourB_Mass(const FourB_Mass& other, const char* name=0) :
      MassAbsFunc(other,name),
      MBs("MBs",this,other.MBs){}

    virtual TObject* clone(const char* newname) const { return new FourB_Mass(*this,newname); }

  inline virtual ~FourB_Mass() { }

protected:

  RooRealProxy MBs;
  Double_t evaluate() const ;

private:

  ClassDef(FourB_Mass,1) // Your description goes here...
};
 
#endif