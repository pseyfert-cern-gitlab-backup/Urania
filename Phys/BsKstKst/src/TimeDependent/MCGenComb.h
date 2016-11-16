#ifndef MCGENCOMB
#define MCGENCOMB

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "TComplex.h"
#include "TF1.h"
#include "RooMath.h"

class MCGenComb : public RooAbsPdf {
public:
  MCGenComb() {} ; 
  MCGenComb(const char *name, const char *title,
	   RooAbsReal& _gen_model,
	   RooAbsReal& _year,
	   RooAbsReal& _wide_window,
	   RooAbsReal& _m1,
	   RooAbsReal& _m2,
	   RooAbsReal& _cos1,
	   RooAbsReal& _cos2,
	   RooAbsReal& _phi,
	   RooAbsReal& _t,
           RooAbsReal& _option);
  MCGenComb(const MCGenComb& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new MCGenComb(*this,newname); }
  inline virtual ~MCGenComb() { }

  RooRealProxy gen_model ;
  RooRealProxy year ;
  RooRealProxy wide_window ;
  RooRealProxy m1 ;
  RooRealProxy m2 ;
  RooRealProxy cos1 ;
  RooRealProxy cos2 ;
  RooRealProxy phi ;
  RooRealProxy t ;
  RooRealProxy option ;

  TComplex Aj1j2h(Int_t j1, Int_t j2, Int_t h) const;
  Double_t etah(Int_t h) const;
  Double_t etaj1j2h(Int_t j1, Int_t j2, Int_t h) const;
  TComplex Abarj1j2h(Int_t j1, Int_t j2, Int_t h) const;
  TComplex AAj1j2hj1pj2php(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;

  Double_t fi(Double_t x, Int_t i) const;
  Double_t gi(Double_t x, Int_t i) const;
  Double_t fjjphhp(Double_t x, Int_t j, Int_t jp, Int_t h, Int_t hp) const;
  Double_t ghhp(Double_t x, Int_t h, Int_t hp) const;
  TComplex Nj1j2h(Int_t j1, Int_t j2, Int_t h) const;
  TComplex Nj1j2hj1pj2php(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t Ifi(Int_t i) const;
  Double_t Igi(Int_t i) const;
  Double_t Ifjjphhp(Int_t j, Int_t jp, Int_t h, Int_t hp) const;
  Double_t Ighhp(Int_t h, Int_t hp) const;

  Double_t get_q(Double_t M, Double_t ma, Double_t mb) const;
  Double_t Blatt_Weisskopf2(Double_t q, Double_t q0, Int_t L) const;
  TComplex Resonance(Double_t m, Double_t m_sister, Double_t m0, Double_t g0, Int_t J) const;
  TComplex Lass(Double_t m, Double_t m_sister, Double_t m0, Double_t g0) const;
  TComplex Mji(Double_t m, Double_t m_sister, Int_t ji) const;
  TComplex Mj1j2(Double_t ma, Double_t mb, Int_t j1, Int_t j2) const;
  Double_t phasespace(Double_t ma, Double_t mb) const;
  TComplex hj1j2j1pj2p(Double_t ma, Double_t mb, Int_t j1, Int_t j2, Int_t j1p, Int_t j2p) const;
  TComplex Ihj1j2j1pj2p(Int_t j1, Int_t j2, Int_t j1p, Int_t j2p) const;

  Double_t model_comp_omega(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t Imodel_comp_omega(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t model_omega() const;
  Double_t Imodel_omega() const;

  Double_t timemodel(Double_t tau) const;

  Double_t evaluate() const;

private:

  ClassDef(MCGenComb,1)
};
 
#endif
