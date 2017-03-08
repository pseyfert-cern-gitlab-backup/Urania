/********************************************************************

 DESCRIPTION: model to describe the Bs -> (K+pi-)(K-pi+) decay
 spectrum.
 AUTHOR: Julian Garcia Pardinhas, julian.garcia.pardinas@rai.usc.es
 UNIVERSITY: Universidade de Santiago de Compostela
 DATE: 10/2014

*********************************************************************

 INFORMATION:

  - The PDF is constructed by summing up the 190 components arising
  from the product of A*complex_conjugate(A).

  - Each of the components is identifyied by 6 indexes:
      _ j1 and j1p: angular momentum of the K+pi- pair.
      _ j2 and j2p: angular momentum of the K-pi+ pair.
      _ h and hp: helicity of the Kpi (K+pi- or K-pi+) pair.
  The primed indexes, j1p, j2p and hp, appear beacuse the PDF
  components are composed by products of pairs of amplitudes, each one
  corresponding to a given configuration of angular momenta and
  helicity.
  Notation for the helicity states:
      _ h,hp = 0 -> Longitudinal.
      _ h,hp = 1 -> Parallel 1.
      _ h,hp = 2 -> Perpendicular 1.
      _ h,hp = 3 -> Parallel 2.
      _ h,hp = 4 -> Perpendicular 2.

  -Every component is factorized on functions that depend on the 11
  different observables (m1, m2, cos1, cos2, phi, t, t_error,
  decision_SSK, decision_OS, mistag_SSK and mistag_OS):
      _ compj1j2hj1pj2php = Tj1j2hj1pj2php(t,t_error,decision_SSK,
      decision_OS,mistag_SSK,mistag_OS)*Nj1j2hj1pj2php*ghhp(phi)*
      fjjphhp(cos1)*fjjphhp(cos2)*hj1j2j1pj2p(m1,m2)

********************************************************************/

#ifndef KPIKPISPECTRUMNW
#define KPIKPISPECTRUMNW

#include "RooAbsReal.h"
#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsCategory.h"
#include "TComplex.h"
#include "TF1.h"
#include "RooMath.h"
#include "NWclass.h"
#include "Splineclass.h"
#include "TAccclass.h"
#include "accparclass.h"
#include "genaccparclass.h"
#include "TResclass.h"
#include "TReseffclass.h"
#include "RooAbsNumGenerator.h"
#include "RooPrintable.h"
#include "RooArgSet.h"
#include "TRandom.h"

NWclass NW; // Normalization weights
Splineclass spl; // Time acceptance splines
TAccclass TAcc; // Time acceptance histograms
accparclass accpar; // Visualization acceptance parameters
genaccparclass genaccpar; // Toy MC generation acceptance parameters
TResclass TRes; // Time resolution parameters
TReseffclass TReseff; // Effective time resolution parameters

Double_t DCP_prod; // Production asymmetry

// Parameters of the LASS parametrisation of the Kpi scalar propagator
Double_t a_lass = 3.89834e-03;//0.00195;
Double_t r_lass = 3.20087e-03;//0.00176;
Double_t MR_lass = 1330.; // MeV/c2
Double_t F_lass = 102.722; // MeV
Double_t cd_lass = 35.2; // MeV
Double_t cm_lass = 1.027; //MeV
Double_t C_lass = -0.001; // (dimensionless)

// Parameters of the elastic+inelastic phenomenological parameterisation of the Kpi mass amplitudes
Double_t c1_pol_Stheo = -5.05015e-01;
Double_t c2_pol_Stheo = -2.59249e-01;
Double_t c3_pol_Stheo = -2.77261e-02;
Double_t c4_pol_Stheo = 0.;
Double_t MEta = 547.; // MeV/c2
Double_t MEtaprime = 957.78; // MeV/c2
Double_t sAdler_Stheo = 0.236;
Double_t B0_Stheo = 0.411;
Double_t B1_Stheo = 0.162;
Double_t alpha_Stheo = 1.15;
Double_t s0_Stheo = 1.21;
Double_t phi0_Stheo = -0.19;
Double_t phi1_Stheo = 5.03;
Double_t a_Stheo = -5.2;
Double_t b_Stheo = 7.6;
Double_t c_Stheo = -1.73;
Double_t sqrtsr1_Stheo = 1.401;
Double_t sqrtsr2_Stheo = 1.817;
Double_t e1_Stheo = 1.;
Double_t e2_Stheo = 0.184;
Double_t G1_Stheo = 0.497;
Double_t G2_Stheo = 0.28;
Double_t B0_Ptheo = 0.97;
Double_t B1_Ptheo = 0.55;
Double_t B2_Ptheo = 0.75;
Double_t mr_Ptheo = 0.8957;
Double_t alpha_Ptheo = 1.15;
Double_t s0_Ptheo = 1.21;
Double_t a1_Ptheo = -1.76;
Double_t a2_Ptheo = -2.33;
Double_t a3_Ptheo = -1.41;
Double_t sqrtsr1_Ptheo = 0.896;
Double_t sqrtsr2_Ptheo = 1.347;
Double_t sqrtsr3_Ptheo = 1.645;
Double_t e1_Ptheo = 1.;
Double_t e2_Ptheo = 0.055;
Double_t e3_Ptheo = 0.306;
Double_t G1_Ptheo = 0.044;
Double_t G2_Ptheo = 0.231;
Double_t G3_Ptheo = 0.306;
Double_t phi0_Dtheo = 3.00;
Double_t phi1_Dtheo = -9.3;
Double_t sqrtsr1_Dtheo = 1.445;
Double_t e1_Dtheo = 0.465;
Double_t G1_Dtheo = 0.222;
Double_t a_Dtheo = -0.72;

// Auxiliar variables
Double_t spl_coef_array_1[2][2][5][4][4][4];
Double_t spl_coef_array_2[2][2][5][4][4][4];
Double_t spl_knot_vector[2][2][6];
Double_t f1_eff[2];
Double_t f2_eff[2];
Double_t s1_eff[2];
Double_t s2_eff[2];
Double_t spl_knot_x1_vector[2][2][6];
Double_t spl_knot_x2_vector[2][2][6];
Double_t timefun_integral = 0; // Used in the computation of the histogram-like time integrals
Double_t fjjphhpindexdict[3][3][5][5];
Double_t ghhpindexdict[5][5];
TComplex Nj1j2hdict[3][3][5];
TComplex Ihj1j2j1pj2pdict[2][2][3][3][3][3];
Double_t den_plot_var[2][2];

// Variables used in event generation
Double_t P_trueBs_const = 0.5; // Probability of generating a true Bs vs generating a true Bsbar
Double_t prob_right_tagged; // Probability of correctly tagging an event
Int_t true_ID; // True Bs vs true Bsbar identifier
Int_t event_accepted; // Accepted vs rejected event.
Int_t N_accepted; // Number of accepted events
Int_t Wide_Window_Gen; // mKpi window size option
Double_t max_fun_etaSSK; // Maximum of the etamistag_SSK PDF
Double_t max_fun_etaOS; // Maximum of the etamistag_OS PDF
Double_t max_fun_7DBs; // Maximum of the 7-D PDF for a true Bs
Double_t max_fun_7DBsbar; // Maximum of the 7-D PDF for a true Bsbar
Double_t max_fun; // Maximum of the PDF
TRandom ran; // Generic random number
Double_t etamistag_SSK_ran; // Randomized etamistag_SSK
Double_t etamistag_OS_ran; // Randomized etamistag_OS
Double_t m1_ran; // Randomized m1
Double_t m2_ran; // Randomized m2
Double_t cos1_ran; // Randomized cos1
Double_t cos2_ran; // Randomized cos2
Double_t phi_ran; // Randomized phi
Double_t t_ran; // Randomized t
Double_t t_err_ran; // Randomized t_err
Double_t fun_ran; // PDF for the randomized observables
Double_t dec_Bs; // True Bs vs true Bsbar random decision
Double_t dec_SSK_tagged; // SSK tagged vs SSK untagged random decision
Double_t dec_OS_tagged; // OS tagged vs OS untagged random decision
Double_t dec_right_tagged; // Right tagged vs wrong tagged random decision
Double_t dec_accepted; // Accepted event vs rejected event random decision

// Buffer variables used to speed up the sumations
TComplex Aj1j2h_temp[3][3][5];
TComplex Abarj1j2h_temp[3][3][5];
Double_t T_cosh_temp = 0.;
Double_t T_sinh_temp = 0.;
Double_t T_cos_temp = 0.;
Double_t T_sin_temp = 0.;
Double_t IT_cosh_temp_deltat = 0.;
Double_t IT_sinh_temp_deltat = 0.;
Double_t IT_cos_temp_deltat = 0.;
Double_t IT_sin_temp_deltat = 0.;
Double_t IT_cosh_temp = 0.;
Double_t IT_sinh_temp = 0.;
Double_t IT_cos_temp = 0.;
Double_t IT_sin_temp = 0.;
Double_t zeta_temp = 0.;
Double_t DCP_tzero_temp = 0.;
Double_t fi_cos1_temp[18];
Double_t fi_cos2_temp[18];
Double_t gi_temp[15];
TComplex Mj1j2_temp[3][3];
Double_t phasespace_temp = 0.;

class KpiKpiSpectrumNW : public RooAbsPdf {
public:
  KpiKpiSpectrumNW() {} ; 
  KpiKpiSpectrumNW(const char *name, const char *title,
	   const RooArgList& _options,
	   const RooArgList& _observables,
	   const RooArgList& _re_amps,
	   const RooArgList& _dirCP_asyms,
	   const RooArgList& _im_amps,
	   const RooArgList& _weak_phases,
	   const RooArgList& _mixing_params,
	   const RooArgList& _calib_params,
	   const RooArgList& _cond_distr_params,
	   const RooArgList& _sys_studies,
	   const RooArgList& _mass_integrals,
	   const RooArgList& _ang_integrals,
	   const RooArgList& _time_integrals);
  KpiKpiSpectrumNW(const KpiKpiSpectrumNW& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new KpiKpiSpectrumNW(*this,newname); }
  inline virtual ~KpiKpiSpectrumNW() { }

  RooRealProxy wide_window ;
  RooRealProxy year_opt ;
  RooRealProxy trig_opt ;
  RooRealProxy alt_fit ;
  RooRealProxy option ;
  RooRealProxy inftres ;
  RooRealProxy acctype ;
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
  RooRealProxy reA00 ;
  RooRealProxy reA01 ;
  RooRealProxy reA10 ;
  RooRealProxy reA02 ;
  RooRealProxy reA20 ;
  RooRealProxy reA110 ;
  RooRealProxy reA11par ;
  RooRealProxy reA11perp ;
  RooRealProxy reA120 ;
  RooRealProxy reA12par ;
  RooRealProxy reA12perp ;
  RooRealProxy reA210 ;
  RooRealProxy reA21par ;
  RooRealProxy reA21perp ;
  RooRealProxy reA220 ;
  RooRealProxy reA22par ;
  RooRealProxy reA22perp ;
  RooRealProxy reA22par2 ;
  RooRealProxy reA22perp2 ;
  RooRealProxy DCP_SS ;
  RooRealProxy DCP_SV ;
  RooRealProxy DCP_VS ;
  RooRealProxy DCP_ST ;
  RooRealProxy DCP_TS ;
  RooRealProxy DCP_VV ;
  RooRealProxy DCP_VT ;
  RooRealProxy DCP_TV ;
  RooRealProxy DCP_TT ;
  RooRealProxy imA00 ;
  RooRealProxy imA01 ;
  RooRealProxy imA10 ;
  RooRealProxy imA02 ;
  RooRealProxy imA20 ;
  RooRealProxy imA110 ;
  RooRealProxy imA11par ;
  RooRealProxy imA11perp ;
  RooRealProxy imA120 ;
  RooRealProxy imA12par ;
  RooRealProxy imA12perp ;
  RooRealProxy imA210 ;
  RooRealProxy imA21par ;
  RooRealProxy imA21perp ;
  RooRealProxy imA220 ;
  RooRealProxy imA22par ;
  RooRealProxy imA22perp ;
  RooRealProxy imA22par2 ;
  RooRealProxy imA22perp2 ;
  RooRealProxy phis ;
  RooRealProxy dphi_SS ;
  RooRealProxy dphi_SV ;
  RooRealProxy dphi_VS ;
  RooRealProxy dphi_ST ;
  RooRealProxy dphi_TS ;
  RooRealProxy dphi_VT ;
  RooRealProxy dphi_TV ;
  RooRealProxy dphi_TT ;
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
  RooRealProxy deltatmean_tres_11 ;
  RooRealProxy p0_tres_11 ;
  RooRealProxy p1_tres_11 ;
  RooRealProxy deltatmean_tres_12 ;
  RooRealProxy p0_tres_12 ;
  RooRealProxy p1_tres_12 ;
  RooRealProxy mv ;
  RooRealProxy ms ;
  RooRealProxy mt ;
  RooRealProxy gv ;
  RooRealProxy gs ;
  RooRealProxy gt ;
  RooRealProxy res_mass ;
  RooRealProxy tag_eff_SSK ;
  RooRealProxy mu1_SSK ;
  RooRealProxy sigma1_SSK ;
  RooRealProxy c_SSK ;
  RooRealProxy mu2_SSK ;
  RooRealProxy sigma2_SSK ;
  RooRealProxy tag_eff_OS ;
  RooRealProxy mu1_OS ;
  RooRealProxy sigma1_OS ;
  RooRealProxy c_OS ;
  RooRealProxy mu2_OS ;
  RooRealProxy sigma2_OS ;
  RooRealProxy gamma1_dt ;
  RooRealProxy beta1_dt ;
  RooRealProxy c_dt ;
  RooRealProxy gamma2_dt ;
  RooRealProxy beta2_dt ;
  RooRealProxy pw_mass_altmodel ;
  RooRealProxy f_1410_rel2_892 ;
  RooRealProxy delta_1410_rel2_892 ;
  RooRealProxy f_1680_rel2_892 ;
  RooRealProxy delta_1680_rel2_892 ;
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
  RooRealProxy If1 ;
  RooRealProxy If2 ;
  RooRealProxy If3 ;
  RooRealProxy If4 ;
  RooRealProxy If5 ;
  RooRealProxy If6 ;
  RooRealProxy If7 ;
  RooRealProxy If8 ;
  RooRealProxy If9 ;
  RooRealProxy If10 ;
  RooRealProxy If11 ;
  RooRealProxy If12 ;
  RooRealProxy If13 ;
  RooRealProxy If14 ;
  RooRealProxy If15 ;
  RooRealProxy If16 ;
  RooRealProxy If17 ;
  RooRealProxy If18 ;
  RooRealProxy IT_cosh ;
  RooRealProxy IT_sinh ;
  RooRealProxy IT_cos ;
  RooRealProxy IT_sin ;

  // Physical terms.
  Double_t reAj1j2h(Int_t j1, Int_t j2, Int_t h) const;
  Double_t imAj1j2h(Int_t j1, Int_t j2, Int_t h) const;
  Double_t DCPj1j2(Int_t j1, Int_t j2) const;
  Double_t dphij1j2(Int_t j1, Int_t j2) const;
  Double_t etah(Int_t h) const;
  Double_t etaj1j2h(Int_t j1, Int_t j2, Int_t h) const;
  TComplex Aj1j2h(Int_t j1, Int_t j2, Int_t h) const;
  TComplex Abarj1j2h(Int_t j1, Int_t j2, Int_t h) const;
  TComplex M_Average(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  TComplex M_DeltaGamma(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  TComplex M_DirCP(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  TComplex M_MixCP(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;

  // Flavour tagging terms.
  Double_t omega_SSK(Double_t eta) const;
  Double_t omegabar_SSK(Double_t eta) const;
  Double_t omega_OS(Double_t eta) const;
  Double_t omegabar_OS(Double_t eta) const;
  Double_t P_Bs(Int_t q1, Int_t q2, Double_t eta1, Double_t eta2) const;
  Double_t P_Bsbar(Int_t q1, Int_t q2, Double_t eta1, Double_t eta2) const;
  Double_t zeta(Int_t q1, Int_t q2, Double_t eta1, Double_t eta2) const;
  Double_t DCP_tzero(Int_t q1, Int_t q2, Double_t eta1, Double_t eta2) const;

  // Time dependent terms.
  Double_t sigma_tres(Double_t tau_err, Int_t g_i) const;
  Double_t sigma_ref(Double_t tau_err) const;
  Double_t sigma_tres_eff(Int_t g_i) const;
  Double_t sigma_ref_eff() const;
  Double_t x_tres(Double_t tau, Double_t tau_err, Int_t g_i) const;
  Double_t x0_tres(Double_t tau_err, Int_t g_i) const;
  std::complex<Double_t> z_tres(Double_t tau, Double_t tau_err, Int_t g_i) const;
  Double_t gaus_tres(Double_t tau, Double_t tau_err, Int_t g_i) const;
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
  Double_t T_cosh_resexact(Double_t tau, Double_t tau_err) const;
  Double_t T_sinh_resexact(Double_t tau, Double_t tau_err) const;
  Double_t T_cos_resexact(Double_t tau, Double_t tau_err) const;
  Double_t T_sin_resexact(Double_t tau, Double_t tau_err) const;
  Double_t T_cosh_resapprox(Double_t tau, Double_t tau_err) const;
  Double_t T_sinh_resapprox(Double_t tau, Double_t tau_err) const;
  Double_t T_cos_resapprox(Double_t tau, Double_t tau_err) const;
  Double_t T_sin_resapprox(Double_t tau, Double_t tau_err) const;
  Double_t T_cosh(Double_t tau, Double_t tau_err) const;
  Double_t T_sinh(Double_t tau, Double_t tau_err) const;
  Double_t T_cos(Double_t tau, Double_t tau_err) const;
  Double_t T_sin(Double_t tau, Double_t tau_err) const;
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
  TComplex Tj1j2hj1pj2php(Double_t tau, Double_t tau_err, Int_t q1, Int_t q2, Double_t eta1, Double_t eta2, Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  TComplex Teffj1j2hj1pj2php(Double_t tau, Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t IT_cosh_resapprox_eff_bin(Double_t tau1, Double_t tau2) const;
  Double_t IT_sinh_resapprox_eff_bin(Double_t tau1, Double_t tau2) const;
  Double_t IT_cos_resapprox_eff_bin(Double_t tau1, Double_t tau2) const;
  Double_t IT_sin_resapprox_eff_bin(Double_t tau1, Double_t tau2) const;
  Double_t IT_cosh_resapprox_eff() const;
  Double_t IT_sinh_resapprox_eff() const;
  Double_t IT_cos_resapprox_eff() const;
  Double_t IT_sin_resapprox_eff() const;
  std::complex<Double_t> faddeeva_2args(Double_t x, std::complex<Double_t> z) const;
  std::complex<Double_t> conv_exp(Double_t x, std::complex<Double_t> z) const;
  std::complex<Double_t> Kn(std::complex<Double_t> z, Int_t n) const;
  std::complex<Double_t> Mn_x(Double_t x, std::complex<Double_t> z, Int_t n) const;
  std::complex<Double_t> Mn(Double_t x_1, Double_t x_2, std::complex<Double_t> z, Int_t n) const;
  void set_buffer_differential_vars(Double_t m1var, Double_t m2var, Double_t cos1var, Double_t cos2var, Double_t phivar, Double_t tvar, Double_t terrvar, Int_t decisionSSKvar, Int_t decisionOSvar, Double_t etamistagSSKvar, Double_t etamistagOSvar) const;
  void set_buffer_integral_vars() const;
  Double_t T_cosh_spl(Double_t tau, Double_t tau_err) const;
  Double_t T_sinh_spl(Double_t tau, Double_t tau_err) const;
  Double_t T_cos_spl(Double_t tau, Double_t tau_err) const;
  Double_t T_sin_spl(Double_t tau, Double_t tau_err) const;
  Double_t IT_cosh_spl() const;
  Double_t IT_sinh_spl() const;
  Double_t IT_cos_spl() const;
  Double_t IT_sin_spl() const;
  TComplex IT_basicfit_j1j2hj1pj2php(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;

  // Angular terms.
  Double_t fi(Double_t x, Int_t i) const;
  Double_t gi(Double_t x, Int_t i) const;
  Double_t fjjphhp(Double_t x, Int_t j, Int_t jp, Int_t h, Int_t hp) const;
  Double_t fjjphhp_cos1(Int_t j, Int_t jp, Int_t h, Int_t hp) const;
  Double_t fjjphhp_cos2(Int_t j, Int_t jp, Int_t h, Int_t hp) const;
  Double_t ghhp(Double_t x, Int_t h, Int_t hp) const;
  Double_t ghhp_phi(Int_t h, Int_t hp) const;
  TComplex Nj1j2hj1pj2php(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;

  // Invariant mass dependent terms.
  Double_t get_q(Double_t M, Double_t ma, Double_t mb) const;
  Double_t Blatt_Weisskopf2(Double_t q, Double_t q0, Int_t L) const;
  Double_t FL_j1j2(Int_t j1, Int_t j2, Double_t ma, Double_t mb) const;
  TComplex Resonance(Double_t m, Double_t m0, Double_t g0, Int_t J) const;
  TComplex Lass(Double_t m, Double_t m0, Double_t g0) const;
  TComplex Lass_chiral(Double_t m) const;
  Double_t omega_Stheo(Double_t m) const;
  Double_t omega_Ptheo(Double_t m) const;
  Double_t cotdelta_Stheo(Double_t m) const;
  Double_t cotdelta_Ptheo(Double_t m) const;
  Double_t get_p1_Stheo(Double_t q) const;
  Double_t get_p2_Stheo(Double_t q) const;
  Double_t get_p1_Ptheo(Double_t q) const;
  Double_t get_p2_Ptheo(Double_t q) const;
  Double_t get_p3_Ptheo(Double_t q) const;
  Double_t get_p1_Dtheo(Double_t q) const;
  Double_t Theta_Keta(Double_t m) const;
  Double_t Theta_Ketaprime(Double_t m) const;
  TComplex Prop_Stheo(Double_t m) const;
  TComplex Prop_Ptheo(Double_t m) const;
  TComplex Prop_Dtheo(Double_t m) const;
  TComplex Mji(Double_t m, Int_t ji) const;
  TComplex Mj1j2(Double_t ma, Double_t mb, Int_t j1, Int_t j2) const; 
  Double_t phasespace(Double_t ma, Double_t mb) const;
  TComplex hj1j2j1pj2p(Double_t ma, Double_t mb, Int_t j1, Int_t j2, Int_t j1p, Int_t j2p) const;

  // Parametric acceptance.
  Double_t accTime(Double_t tau) const;
  Double_t accTimeParam(Double_t tau) const;
  Double_t accTimeHisto(Double_t tau) const;
  Double_t accAng(Double_t x) const;
  Double_t accMass(Double_t m) const;
  TComplex ITj1j2hj1pj2php(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  TComplex ITj1j2hj1pj2php_deltat(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t Ifi(Int_t i) const;
  Double_t Igi(Int_t i) const;
  Double_t Ifjjphhp(Int_t j, Int_t jp, Int_t h, Int_t hp) const;
  Double_t Ighhp(Int_t h, Int_t hp) const;
  TComplex Ihj1j2j1pj2p(Int_t j1, Int_t j2, Int_t j1p, Int_t j2p) const;

  // PDF separated components.
  Double_t comp_num_fit(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t comp_den_fit(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t comp_num_basicfit(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t comp_den_basicfit(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t comp_num_plot_t(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t comp_num_plot_phi(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t comp_num_plot_cos1(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t comp_num_plot_cos2(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t comp_num_plot_m(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t comp_den_plot(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t getReCompVal(Double_t ma, Double_t mb, Double_t cos1ang, Double_t cos2ang, Double_t phiang, Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t getImCompVal(Double_t ma, Double_t mb, Double_t cos1ang, Double_t cos2ang, Double_t phiang, Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t NWpull(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp, Int_t part) const;

  // Complete PDF.
  void sumgenerator() const;
  Double_t num_fit() const;
  Double_t den_fit() const;
  Double_t num_basicfit() const;
  Double_t den_basicfit() const;
  Double_t num_plot_t() const;
  Double_t num_plot_phi() const;
  Double_t num_plot_cos1() const;
  Double_t num_plot_cos2() const;
  Double_t num_plot_m() const;
  Double_t den_plot() const;

  // Integrals.
  void setDenPlotVarVal() const;
  Int_t getAnalyticalIntegral (RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0 ) const;
  Double_t analyticalIntegral(Int_t code, const char* rangeName=0 ) const;

  // Event generation.
  Double_t accGen(Double_t tau, Double_t ma, Double_t mb, Double_t cos1var, Double_t cos2var, Double_t phivar) const;
  Double_t P_eta_SSK(Double_t eta) const;
  Double_t P_eta_OS(Double_t eta) const;
  Double_t P_deltat(Double_t tau_err) const;
  TComplex TBsj1j2hj1pj2php(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  TComplex TBsbarj1j2hj1pj2php(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t comp_fun_Bs(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t comp_fun_Bsbar(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t fun_Bs() const;
  Double_t fun_Bsbar() const;
  TComplex ITBsj1j2hj1pj2php(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t comp_int_Bs(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const;
  Double_t int_Bs() const;
  Double_t P_trueBs() const;
  void Randomize7D(Int_t wide_window_gen) const;
  void Randomize7D_fun_max() const;
  void SetGenerator(Int_t wide_window_gen, Int_t compute_max_fun=0, Int_t sample_size_7D=1000000) const;
  Int_t getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t staticInitOK=kTRUE) const;
  void generateEvent(Int_t code);

  // Output.
  Double_t evaluate() const ;

private:

  ClassDef(KpiKpiSpectrumNW,1)
};

#endif
