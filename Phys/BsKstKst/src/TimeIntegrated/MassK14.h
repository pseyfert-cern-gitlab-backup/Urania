/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef MASSK14
#define MASSK14

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "TComplex.h"
#include "MassAbsFunc.h"

class MassK14 : public MassAbsFunc {
public:
  MassK14(): MassAbsFunc() {} ; 
  MassK14(const char *name, const char *title,
	      RooAbsReal& _m1,
	      RooAbsReal& _m2,
	      RooAbsReal& _Ass,
	      RooAbsReal& _dss,
	      RooAbsReal& _A0,
	      RooAbsReal& _d0,
	      RooAbsReal& _m_kst,
	      RooAbsReal& _m_kst0,
	      RooAbsReal& _g_kst,
	      RooAbsReal& _g_kst0,
	 RooAbsReal& _m_Bs,
	      RooArgList& _acc_coefList,
	  RooAbsReal& _norm):
    MassAbsFunc(name, title, _m1, _m2, _m_kst, _m_kst0, _g_kst, _g_kst0, _m_Bs, _acc_coefList,_norm),
    Ass("Ass","Ass",this,_Ass),
    dss("dss","dss",this,_dss),
    A0("A0","A0",this,_A0),
    d0("d0","d0",this,_d0){}
  
    MassK14(const MassK14& other, const char* name=0):
      MassAbsFunc(other,name),
      Ass("Ass",this,other.Ass),
      dss("dss",this,other.dss),
      A0("A0",this,other.A0),
      d0("d0",this,other.d0){}

  virtual TObject* clone(const char* newname) const { return new MassK14(*this,newname); }
  inline virtual ~MassK14() { }

protected:
  RooRealProxy Ass ;
  RooRealProxy dss ;
  RooRealProxy A0 ;
  RooRealProxy d0 ;

  
  Double_t evaluate() const ;

private:

  ClassDef(MassK14,1) // Your description goes here...
};
 
#endif
