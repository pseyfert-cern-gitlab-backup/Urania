/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef MASSK7
#define MASSK7

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "TComplex.h"
#include "MassAbsFunc.h"
 
class MassK7 : public MassAbsFunc {
public:
  MassK7():MassAbsFunc() {} ; 
  MassK7(const char *name, const char *title,
	      RooAbsReal& _m1,
	      RooAbsReal& _m2,
	      RooAbsReal& _Af,
	      RooAbsReal& _df,
	      RooAbsReal& _Ag,
	      RooAbsReal& _dg,
	      RooAbsReal& _Gs,
	      RooAbsReal& _DGs,
	      RooAbsReal& _m_kst,
	      RooAbsReal& _m_kst0,
	      RooAbsReal& _g_kst,
	      RooAbsReal& _g_kst0,
	 RooAbsReal& _m_Bs,
	      RooArgList& _acc_coefList,
	 RooAbsReal& _norm):
    MassAbsFunc(name, title, _m1, _m2, _m_kst, _m_kst0, _g_kst, _g_kst0, _m_Bs, _acc_coefList, _norm),
    Af("Af","Af",this,_Af),
    df("df","df",this,_df),
    Ag("Ag","Ag",this,_Ag),
    dg("dg","dg",this,_dg),
    Gs("Gs","Gs",this,_Gs),
    DGs("DGs","DGs",this,_DGs){}

    MassK7(const MassK7& other, const char* name=0):
      MassAbsFunc(other,name),
      Af("Af",this,other.Af),
      df("df",this,other.df),
      Ag("Ag",this,other.Ag),
      dg("dg",this,other.dg),
      Gs("Gs",this,other.Gs),
      DGs("DGs",this,other.DGs){}

    virtual TObject* clone(const char* newname) const { return new MassK7(*this,newname); }
    inline virtual ~MassK7() { }


    

protected:

  RooRealProxy Af ;
  RooRealProxy df ;
  RooRealProxy Ag ;
  RooRealProxy dg ;
  RooRealProxy Gs ;
  RooRealProxy DGs;
  
  Double_t evaluate() const ;

private:

  ClassDef(MassK7,1) // Your description goes here...
};
 
#endif
