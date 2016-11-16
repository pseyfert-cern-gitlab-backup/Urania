#ifndef COMPUTEINTEGRALS
#define COMPUTEINTEGRALS

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsCategory.h"
#include "TComplex.h"
#include "TF1.h"
#include "RooMath.h"

class ComputeIntegrals : public RooAbsReal {
public:
  ComputeIntegrals() {} ; 
  ComputeIntegrals(const char *name, const char *title,
	   const RooArgList& _options,
	   const RooArgList& _observables,
	   const RooArgList& _mixing_params,
	   const RooArgList& _calib_params,
	   const RooArgList& _mass_integrals);
  ComputeIntegrals(const ComputeIntegrals& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new ComputeIntegrals(*this,newname); }
  inline virtual ~ComputeIntegrals() { }

  RooRealProxy wide_window ;
  RooRealProxy year_opt ;
  RooRealProxy gen ;
  RooRealProxy option ;
  RooRealProxy inftres ;
  RooRealProxy flatacc ;
  RooRealProxy nwacc ;
  RooRealProxy A_j1 ;
  RooRealProxy A_j2 ;
  RooRealProxy A_h ;
  RooRealProxy A_j1p ;
  RooRealProxy A_j2p ;
  RooRealProxy A_hp ;
  RooRealProxy qcomp ;
  RooCategoryProxy decision_SSK ;
  RooCategoryProxy decision_OS ;
  RooRealProxy etamistag_SSK ;
  RooRealProxy etamistag_OS ;
  RooRealProxy m1 ;
  RooRealProxy m2 ;
  RooRealProxy cos1 ;
  RooRealProxy cos2 ;
  RooRealProxy phi ;
  RooRealProxy t ;
  RooRealProxy t_err ;
  RooRealProxy delta_m_freq ;
  RooRealProxy gamma_Bs_freq ;
  RooRealProxy delta_gamma_freq ;
  RooRealProxy p0metac_tag_SSK ;
  RooRealProxy p0metac_tag_OS ;
  RooRealProxy Dp0half_tag_SSK ;
  RooRealProxy Dp0half_tag_OS ;
  RooRealProxy p1_tag_SSK ;
  RooRealProxy p1_tag_OS ;
  RooRealProxy Dp1half_tag_SSK ;
  RooRealProxy Dp1half_tag_OS ;
  RooRealProxy etac_tag_SSK ;
  RooRealProxy etac_tag_OS ;
  RooRealProxy mv ;
  RooRealProxy ms ;
  RooRealProxy mt ;
  RooRealProxy gv ;
  RooRealProxy gs ;
  RooRealProxy gt ;
  RooRealProxy res_mass ;
  RooRealProxy Im00 ;
  RooRealProxy Im01 ;
  RooRealProxy Im10 ;
  RooRealProxy Im02 ;
  RooRealProxy Im20 ;
  RooRealProxy Im11 ;
  RooRealProxy Im12 ;
  RooRealProxy Im21 ;
  RooRealProxy Im22 ;
  RooRealProxy Ih1Re ;
  RooRealProxy Ih2Re ;
  RooRealProxy Ih3Re ;
  RooRealProxy Ih4Re ;
  RooRealProxy Ih5Re ;
  RooRealProxy Ih6Re ;
  RooRealProxy Ih7Re ;
  RooRealProxy Ih8Re ;
  RooRealProxy Ih9Re ;
  RooRealProxy Ih10Re ;
  RooRealProxy Ih11Re ;
  RooRealProxy Ih12Re ;
  RooRealProxy Ih13Re ;
  RooRealProxy Ih14Re ;
  RooRealProxy Ih15Re ;
  RooRealProxy Ih16Re ;
  RooRealProxy Ih17Re ;
  RooRealProxy Ih18Re ;
  RooRealProxy Ih19Re ;
  RooRealProxy Ih20Re ;
  RooRealProxy Ih21Re ;
  RooRealProxy Ih22Re ;
  RooRealProxy Ih23Re ;
  RooRealProxy Ih24Re ;
  RooRealProxy Ih25Re ;
  RooRealProxy Ih26Re ;
  RooRealProxy Ih27Re ;
  RooRealProxy Ih28Re ;
  RooRealProxy Ih29Re ;
  RooRealProxy Ih30Re ;
  RooRealProxy Ih1Im ;
  RooRealProxy Ih2Im ;
  RooRealProxy Ih3Im ;
  RooRealProxy Ih4Im ;
  RooRealProxy Ih5Im ;
  RooRealProxy Ih6Im ;
  RooRealProxy Ih7Im ;
  RooRealProxy Ih8Im ;
  RooRealProxy Ih9Im ;
  RooRealProxy Ih10Im ;
  RooRealProxy Ih11Im ;
  RooRealProxy Ih12Im ;
  RooRealProxy Ih13Im ;
  RooRealProxy Ih14Im ;
  RooRealProxy Ih15Im ;
  RooRealProxy Ih16Im ;
  RooRealProxy Ih17Im ;
  RooRealProxy Ih18Im ;
  RooRealProxy Ih19Im ;
  RooRealProxy Ih20Im ;
  RooRealProxy Ih21Im ;

  Double_t sigma_tres_eff(Int_t g_i) const;
  Double_t sigma_ref_eff() const;
  Double_t x_tres_eff(Double_t tau, Int_t g_i) const;
  Double_t x0_tres_eff(Int_t g_i) const;
  std::complex<Double_t> z_tres_eff(Double_t tau, Int_t g_i) const;
  Double_t gaus_tres_eff(Double_t tau, Int_t g_i) const;
  Double_t erfc(Double_t x) const;
  Double_t Re_w(std::complex<Double_t> z) const;
  Double_t Im_w(std::complex<Double_t> z) const;
  Double_t T_cosh_ideal(Double_t tau) const;
  Double_t T_sinh_ideal(Double_t tau) const;
  Double_t T_cos_ideal(Double_t tau) const;
  Double_t T_sin_ideal(Double_t tau) const;
  Double_t T_cosh_resexact_eff(Double_t tau) const;
  Double_t T_sinh_resexact_eff(Double_t tau) const;
  Double_t T_cos_resexact_eff(Double_t tau) const;
  Double_t T_sin_resexact_eff(Double_t tau) const;
  Double_t T_cosh_resapprox_eff(Double_t tau) const;
  Double_t T_sinh_resapprox_eff(Double_t tau) const;
  Double_t T_cos_resapprox_eff(Double_t tau) const;
  Double_t T_sin_resapprox_eff(Double_t tau) const;
  Double_t T_cosh_eff(Double_t tau) const;
  Double_t T_sinh_eff(Double_t tau) const;
  Double_t T_cos_eff(Double_t tau) const;
  Double_t T_sin_eff(Double_t tau) const;
  Double_t fi(Double_t x, Int_t i) const;
  Double_t get_q(Double_t M, Double_t ma, Double_t mb) const;
  Double_t Blatt_Weisskopf2(Double_t q, Double_t q0, Int_t L) const;
  TComplex Resonance(Double_t m, Double_t m_sister, Double_t m0, Double_t g0, Int_t J) const;
  TComplex Lass(Double_t m, Double_t m_sister, Double_t m0, Double_t g0) const;
  TComplex Mji(Double_t m, Double_t m_sister, Int_t ji) const;
  TComplex Mj1j2(Double_t ma, Double_t mb, Int_t j1, Int_t j2) const; 
  Double_t phasespace(Double_t ma, Double_t mb) const;
  TComplex hj1j2j1pj2p(Double_t ma, Double_t mb, Int_t j1, Int_t j2, Int_t j1p, Int_t j2p) const;
  Double_t accTime(Double_t tau) const;
  Double_t accAng(Double_t x) const;
  Double_t accMass(Double_t m) const;

  Double_t evaluate() const ;

private:

  ClassDef(ComputeIntegrals,1)
};
 
#endif
