/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef MASSABSFUNC
#define MASSABSFUNC

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "TComplex.h"
#include <math.h> 
#include "TMath.h" 
#include "RooListProxy.h"
#include "RooArgList.h"

Double_t a_dif = 0.00195;
Double_t b_dif = 0.00176;
Double_t r_kst = 0.003;//1./197.3;//0.0034;
Double_t r_kst0 = 0.;
Double_t m_kaon = 493.677;
Double_t m_pion = 139.57;
/* Double_t m_Bs = 5279.5; */


class MassAbsFunc : public RooAbsReal {
public:
  MassAbsFunc():RooAbsReal() {} ; 
  MassAbsFunc(const char *name, const char *title,
	      RooAbsReal& _m1,
	      RooAbsReal& _m2,
	      RooAbsReal& _m_kst,
	      RooAbsReal& _m_kst0,
	      RooAbsReal& _g_kst,
	      RooAbsReal& _g_kst0,
	      RooAbsReal& _m_Bs,
	      RooArgList& _acc_coefList,
	      RooAbsReal& _norm);

  MassAbsFunc(const MassAbsFunc& other, const char* name=0) ;
  inline virtual ~MassAbsFunc() { }

  TComplex PWaveMass(Int_t indx) const;
  TComplex SWaveMass(Int_t indx) const;
  TComplex PWaveMass_2(Int_t indx) const;
  Double_t getAcc() const;
/*   inline Double_t GetNorm() const { return norm; } */
/*   inline void SetNorm(Double_t _normval) const {norm = _normval; } */


protected:

  RooRealProxy m1 ;
  RooRealProxy m2 ;
  RooRealProxy m_kst ;
  RooRealProxy m_kst0 ;
  RooRealProxy g_kst ;
  RooRealProxy g_kst0 ;
  RooRealProxy m_Bs;
  RooListProxy acc_coefList;
  RooRealProxy norm;
  TIterator* coefIter;



private:

  ClassDef(MassAbsFunc,1) // Your description goes here...
};
 
#endif
