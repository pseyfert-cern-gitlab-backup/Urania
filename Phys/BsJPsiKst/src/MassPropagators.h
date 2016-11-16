#ifndef MASSPROPAGATORS
#define MASSPROPAGATORS

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "TComplex.h"
#include "TF1.h"
#include "RooMath.h"

class MassPropagators : public RooAbsReal {
public:
  MassPropagators() {} ; 
  MassPropagators(const char *name, const char *title,
           RooAbsReal& _m,
           RooAbsReal& _p1,
           RooAbsReal& _p2,
           RooAbsReal& _m_B,
           RooAbsReal& _m_Kst0_800,
           RooAbsReal& _gamma_Kst0_800,
           RooAbsReal& _m_Kst0_1430,
           RooAbsReal& _gamma_Kst0_1430,
           RooAbsReal& _m_Kst1_892,
           RooAbsReal& _gamma_Kst1_892,
           RooAbsReal& _m_Kst1_1410,
           RooAbsReal& _gamma_Kst1_1410,
           RooAbsReal& _m_Kst1_1680,
           RooAbsReal& _gamma_Kst1_1680,
           RooAbsReal& _m_Kst2_1430,
           RooAbsReal& _gamma_Kst2_1430,
           RooAbsReal& _a_lass,
           RooAbsReal& _r_lass,
           RooAbsReal& _g2_kpi,
           RooAbsReal& _alpha_mod,
           RooAbsReal& _alpha_phase,
           RooAbsReal& _beta_mod,
           RooAbsReal& _beta_phase,
           RooAbsReal& _delta_mod,
           RooAbsReal& _delta_phase,
           RooAbsReal& _gamma_mod,
           RooAbsReal& _gamma_phase,
           RooAbsReal& _wave,
           RooAbsReal& _PS,
           RooAbsReal& _model_sw,
           RooAbsReal& _model_pw,
           RooAbsReal& _model_dw);
  MassPropagators(const MassPropagators& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new MassPropagators(*this,newname); }
  inline virtual ~MassPropagators() { }

  RooRealProxy m ;
  RooRealProxy p1 ;
  RooRealProxy p2 ;
  RooRealProxy m_B ;
  RooRealProxy m_Kst0_800 ;
  RooRealProxy gamma_Kst0_800 ;
  RooRealProxy m_Kst0_1430 ;
  RooRealProxy gamma_Kst0_1430 ;
  RooRealProxy m_Kst1_892 ;
  RooRealProxy gamma_Kst1_892 ;
  RooRealProxy m_Kst1_1410 ;
  RooRealProxy gamma_Kst1_1410 ;
  RooRealProxy m_Kst1_1680 ;
  RooRealProxy gamma_Kst1_1680 ;
  RooRealProxy m_Kst2_1430 ;
  RooRealProxy gamma_Kst2_1430 ;
  RooRealProxy a_lass ;
  RooRealProxy r_lass ;
  RooRealProxy g2_kpi ;
  RooRealProxy alpha_mod ;
  RooRealProxy alpha_phase ;
  RooRealProxy beta_mod ;
  RooRealProxy beta_phase ;
  RooRealProxy delta_mod ;
  RooRealProxy delta_phase ;
  RooRealProxy gamma_mod ;
  RooRealProxy gamma_phase ;
  RooRealProxy wave ;
  RooRealProxy PS ;
  RooRealProxy model_sw ;
  RooRealProxy model_pw ;
  RooRealProxy model_dw ;

  Double_t Acc(Double_t mu) const;
  std::complex<Double_t> Resonance(Double_t mu, Double_t m0, Double_t g0, Int_t J) const;
  Double_t NonRes(Double_t mu) const;
  std::complex<Double_t> Lass(Double_t mu, Double_t m0, Double_t g0) const;
  std::complex<Double_t> Flatte(Double_t mu, Double_t m0, Double_t g0, Double_t gkpi2) const;
  std::complex<Double_t> Prop(Double_t mu, Int_t wave_j, Int_t model_num_sw, Int_t model_num_pw, Int_t model_num_dw) const;
  Double_t PhaseSpace(Double_t mu) const;
  Double_t likelihood(Double_t mu) const;
  Double_t ll(Double_t mu) const;

  Double_t evaluate() const ;

private:

  ClassDef(MassPropagators,1)
};
 
#endif
