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

#include "RooFit.h"
#include "Riostream.h"
#include "KpiKpiSpectrumNW.h"
#include "RooAbsReal.h"
#include "RooRealVar.h"
#include "RooAbsPdf.h"
#include "RooCategory.h"
#include "RooAbsCategory.h"
#include <math.h>
#include "TMath.h"
#include "TF1.h"
#include <stdexcept>
#include "RooMath.h"
#include "TRandom.h"
#include "RooDataSet.h"
#include "RooRandom.h"
#include "RooErrorHandler.h"
#include "TString.h"
#include "TIterator.h"
#include "RooMsgService.h"
#include "TClass.h"
#include "TFoam.h"
#include "RooRealBinding.h"
#include "RooNumGenFactory.h"
#include "RooNumGenConfig.h"
#include <assert.h>

#define pi TMath::Pi()
#define MPion 139.57018
#define MKaon 493.667
#define MKst_1_1410 1414.
#define GKst_1_1410 232.
#define MKst_1_1680 1717.
#define GKst_1_1680 322.
#define MBs 5366.77

ClassImp(KpiKpiSpectrumNW) 

// ---------------------------------------------------

 KpiKpiSpectrumNW::KpiKpiSpectrumNW(const char *name, const char *title,
			const RooArgList& _options,
			const RooArgList& _observables,
			const RooArgList& _wave_fractions,
			const RooArgList& _dirCP_asyms,
			const RooArgList& _strong_phases,
			const RooArgList& _weak_phases,
			const RooArgList& _mixing_params,
			const RooArgList& _calib_params,
			const RooArgList& _cond_distr_params,
			const RooArgList& _sys_studies,
			const RooArgList& _mass_integrals,
			const RooArgList& _ang_integrals,
			const RooArgList& _time_integrals):
   RooAbsPdf(name,title)
 {
   RooAbsReal* coef_options ;
   TIterator* options_iter = _options.createIterator() ;
   RooAbsReal* coef_real_observables ;
   RooAbsCategory* coef_int_observables ;
   TIterator* observables_iter = _observables.createIterator() ;
   RooAbsReal* coef_wave_fractions ;
   TIterator* wave_fractions_iter = _wave_fractions.createIterator() ;
   RooAbsReal* coef_dirCP_asyms ;
   TIterator* dirCP_asyms_iter = _dirCP_asyms.createIterator() ;
   RooAbsReal* coef_strong_phases ;
   TIterator* strong_phases_iter = _strong_phases.createIterator() ;
   RooAbsReal* coef_weak_phases ;
   TIterator* weak_phases_iter = _weak_phases.createIterator() ;
   RooAbsReal* coef_mixing_params ;
   TIterator* mixing_params_iter = _mixing_params.createIterator() ;
   RooAbsReal* coef_calib_params ;
   TIterator* calib_params_iter = _calib_params.createIterator() ;
   RooAbsReal* coef_cond_distr_params ;
   TIterator* cond_distr_params_iter = _cond_distr_params.createIterator() ;
   RooAbsReal* coef_sys_studies ;
   TIterator* sys_studies_iter = _sys_studies.createIterator() ;
   RooAbsReal* coef_mass_integrals ;
   TIterator* mass_integrals_iter = _mass_integrals.createIterator() ;
   RooAbsReal* coef_ang_integrals ;
   TIterator* ang_integrals_iter = _ang_integrals.createIterator() ;
   RooAbsReal* coef_time_integrals ;
   TIterator* time_integrals_iter = _time_integrals.createIterator() ;

   // Options to configure the PDF.
   coef_options=(RooAbsReal*)options_iter->Next();
   wide_window = RooRealProxy("wide_window","wide_window",this,*coef_options);
   coef_options=(RooAbsReal*)options_iter->Next();
   year_opt = RooRealProxy("year_opt","year_opt",this,*coef_options);
   coef_options=(RooAbsReal*)options_iter->Next();
   trig_opt = RooRealProxy("trig_opt","trig_opt",this,*coef_options);
   coef_options=(RooAbsReal*)options_iter->Next();
   alt_fit = RooRealProxy("alt_fit","alt_fit",this,*coef_options);
   coef_options=(RooAbsReal*)options_iter->Next();
   option = RooRealProxy("option","option",this,*coef_options);
   coef_options=(RooAbsReal*)options_iter->Next();
   inftres = RooRealProxy("inftres","inftres",this,*coef_options);
   coef_options=(RooAbsReal*)options_iter->Next();
   acctype = RooRealProxy("acctype","acctype",this,*coef_options);
   coef_options=(RooAbsReal*)options_iter->Next();
   A_j1 = RooRealProxy("A_j1","A_j1",this,*coef_options);
   coef_options=(RooAbsReal*)options_iter->Next();
   A_j2 = RooRealProxy("A_j2","A_j2",this,*coef_options);
   coef_options=(RooAbsReal*)options_iter->Next();
   A_h = RooRealProxy("A_h","A_h",this,*coef_options);
   coef_options=(RooAbsReal*)options_iter->Next();
   A_j1p = RooRealProxy("A_j1p","A_j1p",this,*coef_options);
   coef_options=(RooAbsReal*)options_iter->Next();
   A_j2p = RooRealProxy("A_j2p","A_j2p",this,*coef_options);
   coef_options=(RooAbsReal*)options_iter->Next();
   A_hp = RooRealProxy("A_hp","A_hp",this,*coef_options);
   coef_options=(RooAbsReal*)options_iter->Next();
   qcomp = RooRealProxy("qcomp","qcomp",this,*coef_options);

   // Observables.
   coef_int_observables=(RooAbsCategory*)observables_iter->Next();
   decision_SSK = RooCategoryProxy("decision_SSK","decision_SSK",this,*coef_int_observables);
   coef_int_observables=(RooAbsCategory*)observables_iter->Next();
   decision_OS = RooCategoryProxy("decision_OS","decision_OS",this,*coef_int_observables);
   coef_real_observables=(RooAbsReal*)observables_iter->Next();
   etamistag_SSK = RooRealProxy("etamistag_SSK","etamistag_SSK",this,*coef_real_observables);
   coef_real_observables=(RooAbsReal*)observables_iter->Next();
   etamistag_OS = RooRealProxy("etamistag_OS","etamistag_OS",this,*coef_real_observables);
   coef_real_observables=(RooAbsReal*)observables_iter->Next();
   m1 = RooRealProxy("m1","m1",this,*coef_real_observables);
   coef_real_observables=(RooAbsReal*)observables_iter->Next();
   m2 = RooRealProxy("m2","m2",this,*coef_real_observables);
   coef_real_observables=(RooAbsReal*)observables_iter->Next();
   cos1 = RooRealProxy("cos1","cos1",this,*coef_real_observables);
   coef_real_observables=(RooAbsReal*)observables_iter->Next();
   cos2 = RooRealProxy("cos2","cos2",this,*coef_real_observables);
   coef_real_observables=(RooAbsReal*)observables_iter->Next();
   phi = RooRealProxy("phi","phi",this,*coef_real_observables);
   coef_real_observables=(RooAbsReal*)observables_iter->Next();
   t = RooRealProxy("t","t",this,*coef_real_observables);
   coef_real_observables=(RooAbsReal*)observables_iter->Next();
   t_err = RooRealProxy("t_err","t_err",this,*coef_real_observables);

   // CP averaged wave fractions.
   coef_wave_fractions=(RooAbsReal*)wave_fractions_iter->Next();
   f_VV = RooRealProxy("f_VV","f_VV",this,*coef_wave_fractions);
   coef_wave_fractions=(RooAbsReal*)wave_fractions_iter->Next();
   f_Swave = RooRealProxy("f_Swave","f_Swave",this,*coef_wave_fractions);
   coef_wave_fractions=(RooAbsReal*)wave_fractions_iter->Next();
   f_SS = RooRealProxy("f_SS","f_SS",this,*coef_wave_fractions);
   coef_wave_fractions=(RooAbsReal*)wave_fractions_iter->Next();
   f_VTTV = RooRealProxy("f_VTTV","f_VTTV",this,*coef_wave_fractions);
   coef_wave_fractions=(RooAbsReal*)wave_fractions_iter->Next();
   f_TT = RooRealProxy("f_TT","f_TT",this,*coef_wave_fractions);
   coef_wave_fractions=(RooAbsReal*)wave_fractions_iter->Next();
   D_SVVS = RooRealProxy("D_SVVS","D_SVVS",this,*coef_wave_fractions);
   coef_wave_fractions=(RooAbsReal*)wave_fractions_iter->Next();
   D_VTTV = RooRealProxy("D_VTTV","D_VTTV",this,*coef_wave_fractions);
   coef_wave_fractions=(RooAbsReal*)wave_fractions_iter->Next();
   D_STTS = RooRealProxy("D_STTS","D_STTS",this,*coef_wave_fractions);
   coef_wave_fractions=(RooAbsReal*)wave_fractions_iter->Next();
   fL_VV = RooRealProxy("fL_VV","fL_VV",this,*coef_wave_fractions);
   coef_wave_fractions=(RooAbsReal*)wave_fractions_iter->Next();
   xpar_VV = RooRealProxy("xpar_VV","xpar_VV",this,*coef_wave_fractions);
   coef_wave_fractions=(RooAbsReal*)wave_fractions_iter->Next();
   fL_VT = RooRealProxy("fL_VT","fL_VT",this,*coef_wave_fractions);
   coef_wave_fractions=(RooAbsReal*)wave_fractions_iter->Next();
   xpar_VT = RooRealProxy("xpar_VT","xpar_VT",this,*coef_wave_fractions);
   coef_wave_fractions=(RooAbsReal*)wave_fractions_iter->Next();
   fL_TV = RooRealProxy("fL_TV","fL_TV",this,*coef_wave_fractions);
   coef_wave_fractions=(RooAbsReal*)wave_fractions_iter->Next();
   xpar_TV = RooRealProxy("xpar_TV","xpar_TV",this,*coef_wave_fractions);
   coef_wave_fractions=(RooAbsReal*)wave_fractions_iter->Next();
   fL_TT = RooRealProxy("fL_TT","fL_TT",this,*coef_wave_fractions);
   coef_wave_fractions=(RooAbsReal*)wave_fractions_iter->Next();
   xpar1_TT = RooRealProxy("xpar1_TT","xpar1_TT",this,*coef_wave_fractions);
   coef_wave_fractions=(RooAbsReal*)wave_fractions_iter->Next();
   xperp1_TT = RooRealProxy("xperp1_TT","xperp1_TT",this,*coef_wave_fractions);
   coef_wave_fractions=(RooAbsReal*)wave_fractions_iter->Next();
   xpar2_TT = RooRealProxy("xpar2_TT","xpar2_TT",this,*coef_wave_fractions);

   // Direct CP violation asymmetries.
   coef_dirCP_asyms=(RooAbsReal*)dirCP_asyms_iter->Next();
   DCP_SS = RooRealProxy("DCP_SS","DCP_SS",this,*coef_dirCP_asyms);
   coef_dirCP_asyms=(RooAbsReal*)dirCP_asyms_iter->Next();
   DCP_SV = RooRealProxy("DCP_SV","DCP_SV",this,*coef_dirCP_asyms);
   coef_dirCP_asyms=(RooAbsReal*)dirCP_asyms_iter->Next();
   DCP_VS = RooRealProxy("DCP_VS","DCP_VS",this,*coef_dirCP_asyms);
   coef_dirCP_asyms=(RooAbsReal*)dirCP_asyms_iter->Next();
   DCP_ST = RooRealProxy("DCP_ST","DCP_ST",this,*coef_dirCP_asyms);
   coef_dirCP_asyms=(RooAbsReal*)dirCP_asyms_iter->Next();
   DCP_TS = RooRealProxy("DCP_TS","DCP_TS",this,*coef_dirCP_asyms);
   coef_dirCP_asyms=(RooAbsReal*)dirCP_asyms_iter->Next();
   DCP_VV = RooRealProxy("DCP_VV","DCP_VV",this,*coef_dirCP_asyms);
   coef_dirCP_asyms=(RooAbsReal*)dirCP_asyms_iter->Next();
   DCP_VT = RooRealProxy("DCP_VT","DCP_VT",this,*coef_dirCP_asyms);
   coef_dirCP_asyms=(RooAbsReal*)dirCP_asyms_iter->Next();
   DCP_TV = RooRealProxy("DCP_TV","DCP_TV",this,*coef_dirCP_asyms);
   coef_dirCP_asyms=(RooAbsReal*)dirCP_asyms_iter->Next();
   DCP_TT = RooRealProxy("DCP_TT","DCP_TT",this,*coef_dirCP_asyms);

   // Strong phases.
   coef_strong_phases=(RooAbsReal*)strong_phases_iter->Next();
   delta00 = RooRealProxy("delta00","delta00",this,*coef_strong_phases);
   coef_strong_phases=(RooAbsReal*)strong_phases_iter->Next();
   delta01 = RooRealProxy("delta01","delta01",this,*coef_strong_phases);
   coef_strong_phases=(RooAbsReal*)strong_phases_iter->Next();
   delta10 = RooRealProxy("delta10","delta10",this,*coef_strong_phases);
   coef_strong_phases=(RooAbsReal*)strong_phases_iter->Next();
   delta02 = RooRealProxy("delta02","delta02",this,*coef_strong_phases);
   coef_strong_phases=(RooAbsReal*)strong_phases_iter->Next();
   delta20 = RooRealProxy("delta20","delta20",this,*coef_strong_phases);
   coef_strong_phases=(RooAbsReal*)strong_phases_iter->Next();
   delta11par = RooRealProxy("delta11par","delta11par",this,*coef_strong_phases);
   coef_strong_phases=(RooAbsReal*)strong_phases_iter->Next();
   delta11perp = RooRealProxy("delta11perp","delta11perp",this,*coef_strong_phases);
   coef_strong_phases=(RooAbsReal*)strong_phases_iter->Next();
   delta120 = RooRealProxy("delta120","delta120",this,*coef_strong_phases);
   coef_strong_phases=(RooAbsReal*)strong_phases_iter->Next();
   delta12par = RooRealProxy("delta12par","delta12par",this,*coef_strong_phases);
   coef_strong_phases=(RooAbsReal*)strong_phases_iter->Next();
   delta12perp = RooRealProxy("delta12perp","delta12perp",this,*coef_strong_phases);
   coef_strong_phases=(RooAbsReal*)strong_phases_iter->Next();
   delta210 = RooRealProxy("delta210","delta210",this,*coef_strong_phases);
   coef_strong_phases=(RooAbsReal*)strong_phases_iter->Next();
   delta21par = RooRealProxy("delta21par","delta21par",this,*coef_strong_phases);
   coef_strong_phases=(RooAbsReal*)strong_phases_iter->Next();
   delta21perp = RooRealProxy("delta21perp","delta21perp",this,*coef_strong_phases);
   coef_strong_phases=(RooAbsReal*)strong_phases_iter->Next();
   delta220 = RooRealProxy("delta220","delta220",this,*coef_strong_phases);
   coef_strong_phases=(RooAbsReal*)strong_phases_iter->Next();
   delta22par = RooRealProxy("delta22par","delta22par",this,*coef_strong_phases);
   coef_strong_phases=(RooAbsReal*)strong_phases_iter->Next();
   delta22perp = RooRealProxy("delta22perp","delta22perp",this,*coef_strong_phases);
   coef_strong_phases=(RooAbsReal*)strong_phases_iter->Next();
   delta22par2 = RooRealProxy("delta22par2","delta22par2",this,*coef_strong_phases);
   coef_strong_phases=(RooAbsReal*)strong_phases_iter->Next();
   delta22perp2 = RooRealProxy("delta22perp2","delta22perp2",this,*coef_strong_phases);

   // Weak phases.
   coef_weak_phases=(RooAbsReal*)weak_phases_iter->Next();
   phis = RooRealProxy("phis","phis",this,*coef_weak_phases);
   coef_weak_phases=(RooAbsReal*)weak_phases_iter->Next();
   dphi_SS = RooRealProxy("dphi_SS","dphi_SS",this,*coef_weak_phases);
   coef_weak_phases=(RooAbsReal*)weak_phases_iter->Next();
   dphi_SV = RooRealProxy("dphi_SV","dphi_SV",this,*coef_weak_phases);
   coef_weak_phases=(RooAbsReal*)weak_phases_iter->Next();
   dphi_VS = RooRealProxy("dphi_VS","dphi_VS",this,*coef_weak_phases);
   coef_weak_phases=(RooAbsReal*)weak_phases_iter->Next();
   dphi_ST = RooRealProxy("dphi_ST","dphi_ST",this,*coef_weak_phases);
   coef_weak_phases=(RooAbsReal*)weak_phases_iter->Next();
   dphi_TS = RooRealProxy("dphi_TS","dphi_TS",this,*coef_weak_phases);
   coef_weak_phases=(RooAbsReal*)weak_phases_iter->Next();
   dphi_VT = RooRealProxy("dphi_VT","dphi_VT",this,*coef_weak_phases);
   coef_weak_phases=(RooAbsReal*)weak_phases_iter->Next();
   dphi_TV = RooRealProxy("dphi_TV","dphi_TV",this,*coef_weak_phases);
   coef_weak_phases=(RooAbsReal*)weak_phases_iter->Next();
   dphi_TT = RooRealProxy("dphi_TT","dphi_TT",this,*coef_weak_phases);

   // Mixing parameters.
   coef_mixing_params=(RooAbsReal*)mixing_params_iter->Next();
   delta_m_freq = RooRealProxy("delta_m_freq","delta_m_freq",this,*coef_mixing_params);
   coef_mixing_params=(RooAbsReal*)mixing_params_iter->Next();
   gamma_Bs_freq = RooRealProxy("gamma_Bs_freq","gamma_Bs_freq",this,*coef_mixing_params);
   coef_mixing_params=(RooAbsReal*)mixing_params_iter->Next();
   delta_gamma_freq = RooRealProxy("delta_gamma_freq","delta_gamma_freq",this,*coef_mixing_params);

   // Calibration parameters.
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   p0metac_tag_SSK = RooRealProxy("p0metac_tag_SSK","p0metac_tag_SSK",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   p0metac_tag_OS = RooRealProxy("p0metac_tag_OS","p0metac_tag_OS",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   Dp0half_tag_SSK = RooRealProxy("Dp0half_tag_SSK","Dp0half_tag_SSK",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   Dp0half_tag_OS = RooRealProxy("Dp0half_tag_OS","Dp0half_tag_OS",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   p1_tag_SSK = RooRealProxy("p1_tag_SSK","p1_tag_SSK",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   p1_tag_OS = RooRealProxy("p1_tag_OS","p1_tag_OS",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   Dp1half_tag_SSK = RooRealProxy("Dp1half_tag_SSK","Dp1half_tag_SSK",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   Dp1half_tag_OS = RooRealProxy("Dp1half_tag_OS","Dp1half_tag_OS",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   etac_tag_SSK = RooRealProxy("etac_tag_SSK","etac_tag_SSK",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   etac_tag_OS = RooRealProxy("etac_tag_OS","etac_tag_OS",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   mv = RooRealProxy("mv","mv",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   ms = RooRealProxy("ms","ms",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   mt = RooRealProxy("mt","mt",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   gv = RooRealProxy("gv","gv",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   gs = RooRealProxy("gs","gs",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   gt = RooRealProxy("gt","gt",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   res_mass = RooRealProxy("res_mass","res_mass",this,*coef_calib_params);

   // Conditional variable distribution parameters.
   coef_cond_distr_params=(RooAbsReal*)cond_distr_params_iter->Next();
   tag_eff_SSK = RooRealProxy("tag_eff_SSK","tag_eff_SSK",this,*coef_cond_distr_params);
   coef_cond_distr_params=(RooAbsReal*)cond_distr_params_iter->Next();
   mu1_SSK = RooRealProxy("mu1_SSK","mu1_SSK",this,*coef_cond_distr_params);
   coef_cond_distr_params=(RooAbsReal*)cond_distr_params_iter->Next();
   sigma1_SSK = RooRealProxy("sigma1_SSK","sigma1_SSK",this,*coef_cond_distr_params);
   coef_cond_distr_params=(RooAbsReal*)cond_distr_params_iter->Next();
   c_SSK = RooRealProxy("c_SSK","c_SSK",this,*coef_cond_distr_params);
   coef_cond_distr_params=(RooAbsReal*)cond_distr_params_iter->Next();
   mu2_SSK = RooRealProxy("mu2_SSK","mu2_SSK",this,*coef_cond_distr_params);
   coef_cond_distr_params=(RooAbsReal*)cond_distr_params_iter->Next();
   sigma2_SSK = RooRealProxy("sigma2_SSK","sigma2_SSK",this,*coef_cond_distr_params);
   coef_cond_distr_params=(RooAbsReal*)cond_distr_params_iter->Next();
   tag_eff_OS = RooRealProxy("tag_eff_OS","tag_eff_OS",this,*coef_cond_distr_params);
   coef_cond_distr_params=(RooAbsReal*)cond_distr_params_iter->Next();
   mu1_OS = RooRealProxy("mu1_OS","mu1_OS",this,*coef_cond_distr_params);
   coef_cond_distr_params=(RooAbsReal*)cond_distr_params_iter->Next();
   sigma1_OS = RooRealProxy("sigma1_OS","sigma1_OS",this,*coef_cond_distr_params);
   coef_cond_distr_params=(RooAbsReal*)cond_distr_params_iter->Next();
   c_OS = RooRealProxy("c_OS","c_OS",this,*coef_cond_distr_params);
   coef_cond_distr_params=(RooAbsReal*)cond_distr_params_iter->Next();
   mu2_OS = RooRealProxy("mu2_OS","mu2_OS",this,*coef_cond_distr_params);
   coef_cond_distr_params=(RooAbsReal*)cond_distr_params_iter->Next();
   sigma2_OS = RooRealProxy("sigma2_OS","sigma2_OS",this,*coef_cond_distr_params);
   coef_cond_distr_params=(RooAbsReal*)cond_distr_params_iter->Next();
   gamma1_dt = RooRealProxy("gamma1_dt","gamma1_dt",this,*coef_cond_distr_params);
   coef_cond_distr_params=(RooAbsReal*)cond_distr_params_iter->Next();
   beta1_dt = RooRealProxy("beta1_dt","beta1_dt",this,*coef_cond_distr_params);
   coef_cond_distr_params=(RooAbsReal*)cond_distr_params_iter->Next();
   c_dt = RooRealProxy("c_dt","c_dt",this,*coef_cond_distr_params);
   coef_cond_distr_params=(RooAbsReal*)cond_distr_params_iter->Next();
   gamma2_dt = RooRealProxy("gamma2_dt","gamma2_dt",this,*coef_cond_distr_params);
   coef_cond_distr_params=(RooAbsReal*)cond_distr_params_iter->Next();
   beta2_dt = RooRealProxy("beta2_dt","beta2_dt",this,*coef_cond_distr_params);

   // Studies on systematic uncertainties.
   coef_sys_studies=(RooAbsReal*)sys_studies_iter->Next();
   pw_mass_altmodel = RooRealProxy("pw_mass_altmodel","pw_mass_altmodel",this,*coef_sys_studies);
   coef_sys_studies=(RooAbsReal*)sys_studies_iter->Next();
   f_1410_rel2_892 = RooRealProxy("f_1410_rel2_892","f_1410_rel2_892",this,*coef_sys_studies);
   coef_sys_studies=(RooAbsReal*)sys_studies_iter->Next();
   delta_1410_rel2_892 = RooRealProxy("delta_1410_rel2_892","delta_1410_rel2_892",this,*coef_sys_studies);
   coef_sys_studies=(RooAbsReal*)sys_studies_iter->Next();
   f_1680_rel2_892 = RooRealProxy("f_1680_rel2_892","f_1680_rel2_892",this,*coef_sys_studies);
   coef_sys_studies=(RooAbsReal*)sys_studies_iter->Next();
   delta_1680_rel2_892 = RooRealProxy("delta_1680_rel2_892","delta_1680_rel2_892",this,*coef_sys_studies);

   // Integrals of the mass dependent terms, for normalization.
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Im00 = RooRealProxy("Im00","Im00",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Im01 = RooRealProxy("Im01","Im01",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Im10 = RooRealProxy("Im10","Im10",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Im02 = RooRealProxy("Im02","Im02",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Im20 = RooRealProxy("Im20","Im20",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Im11 = RooRealProxy("Im11","Im11",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Im12 = RooRealProxy("Im12","Im12",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Im21 = RooRealProxy("Im21","Im21",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Im22 = RooRealProxy("Im22","Im22",this,*coef_mass_integrals);

   // Integrals of the mass dependent terms, for visualization.
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih1Re = RooRealProxy("Ih1Re","Ih1Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih2Re = RooRealProxy("Ih2Re","Ih2Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih3Re = RooRealProxy("Ih3Re","Ih3Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih4Re = RooRealProxy("Ih4Re","Ih4Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih5Re = RooRealProxy("Ih5Re","Ih5Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih6Re = RooRealProxy("Ih6Re","Ih6Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih7Re = RooRealProxy("Ih7Re","Ih7Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih8Re = RooRealProxy("Ih8Re","Ih8Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih9Re = RooRealProxy("Ih9Re","Ih9Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih10Re = RooRealProxy("Ih10Re","Ih10Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih11Re = RooRealProxy("Ih11Re","Ih11Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih12Re = RooRealProxy("Ih12Re","Ih12Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih13Re = RooRealProxy("Ih13Re","Ih13Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih14Re = RooRealProxy("Ih14Re","Ih14Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih15Re = RooRealProxy("Ih15Re","Ih15Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih16Re = RooRealProxy("Ih16Re","Ih16Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih17Re = RooRealProxy("Ih17Re","Ih17Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih18Re = RooRealProxy("Ih18Re","Ih18Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih19Re = RooRealProxy("Ih19Re","Ih19Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih20Re = RooRealProxy("Ih20Re","Ih20Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih21Re = RooRealProxy("Ih21Re","Ih21Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih22Re = RooRealProxy("Ih22Re","Ih22Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih23Re = RooRealProxy("Ih23Re","Ih23Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih24Re = RooRealProxy("Ih24Re","Ih24Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih25Re = RooRealProxy("Ih25Re","Ih25Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih26Re = RooRealProxy("Ih26Re","Ih26Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih27Re = RooRealProxy("Ih27Re","Ih27Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih28Re = RooRealProxy("Ih28Re","Ih28Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih29Re = RooRealProxy("Ih29Re","Ih29Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih30Re = RooRealProxy("Ih30Re","Ih30Re",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih1Im = RooRealProxy("Ih1Im","Ih1Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih2Im = RooRealProxy("Ih2Im","Ih2Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih3Im = RooRealProxy("Ih3Im","Ih3Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih4Im = RooRealProxy("Ih4Im","Ih4Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih5Im = RooRealProxy("Ih5Im","Ih5Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih6Im = RooRealProxy("Ih6Im","Ih6Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih7Im = RooRealProxy("Ih7Im","Ih7Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih8Im = RooRealProxy("Ih8Im","Ih8Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih9Im = RooRealProxy("Ih9Im","Ih9Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih10Im = RooRealProxy("Ih10Im","Ih10Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih11Im = RooRealProxy("Ih11Im","Ih11Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih12Im = RooRealProxy("Ih12Im","Ih12Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih13Im = RooRealProxy("Ih13Im","Ih13Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih14Im = RooRealProxy("Ih14Im","Ih14Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih15Im = RooRealProxy("Ih15Im","Ih15Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih16Im = RooRealProxy("Ih16Im","Ih16Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih17Im = RooRealProxy("Ih17Im","Ih17Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih18Im = RooRealProxy("Ih18Im","Ih18Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih19Im = RooRealProxy("Ih19Im","Ih19Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih20Im = RooRealProxy("Ih20Im","Ih20Im",this,*coef_mass_integrals);
   coef_mass_integrals=(RooAbsReal*)mass_integrals_iter->Next();
   Ih21Im = RooRealProxy("Ih21Im","Ih21Im",this,*coef_mass_integrals);

   // Integrals of the angular terms, for visualization.
   coef_ang_integrals=(RooAbsReal*)ang_integrals_iter->Next();
   If1 = RooRealProxy("If1","If1",this,*coef_ang_integrals);
   coef_ang_integrals=(RooAbsReal*)ang_integrals_iter->Next();
   If2 = RooRealProxy("If2","If2",this,*coef_ang_integrals);
   coef_ang_integrals=(RooAbsReal*)ang_integrals_iter->Next();
   If3 = RooRealProxy("If3","If3",this,*coef_ang_integrals);
   coef_ang_integrals=(RooAbsReal*)ang_integrals_iter->Next();
   If4 = RooRealProxy("If4","If4",this,*coef_ang_integrals);
   coef_ang_integrals=(RooAbsReal*)ang_integrals_iter->Next();
   If5 = RooRealProxy("If5","If5",this,*coef_ang_integrals);
   coef_ang_integrals=(RooAbsReal*)ang_integrals_iter->Next();
   If6 = RooRealProxy("If6","If6",this,*coef_ang_integrals);
   coef_ang_integrals=(RooAbsReal*)ang_integrals_iter->Next();
   If7 = RooRealProxy("If7","If7",this,*coef_ang_integrals);
   coef_ang_integrals=(RooAbsReal*)ang_integrals_iter->Next();
   If8 = RooRealProxy("If8","If8",this,*coef_ang_integrals);
   coef_ang_integrals=(RooAbsReal*)ang_integrals_iter->Next();
   If9 = RooRealProxy("If9","If9",this,*coef_ang_integrals);
   coef_ang_integrals=(RooAbsReal*)ang_integrals_iter->Next();
   If10 = RooRealProxy("If10","If10",this,*coef_ang_integrals);
   coef_ang_integrals=(RooAbsReal*)ang_integrals_iter->Next();
   If11 = RooRealProxy("If11","If11",this,*coef_ang_integrals);
   coef_ang_integrals=(RooAbsReal*)ang_integrals_iter->Next();
   If12 = RooRealProxy("If12","If12",this,*coef_ang_integrals);
   coef_ang_integrals=(RooAbsReal*)ang_integrals_iter->Next();
   If13 = RooRealProxy("If13","If13",this,*coef_ang_integrals);
   coef_ang_integrals=(RooAbsReal*)ang_integrals_iter->Next();
   If14 = RooRealProxy("If14","If14",this,*coef_ang_integrals);
   coef_ang_integrals=(RooAbsReal*)ang_integrals_iter->Next();
   If15 = RooRealProxy("If15","If15",this,*coef_ang_integrals);
   coef_ang_integrals=(RooAbsReal*)ang_integrals_iter->Next();
   If16 = RooRealProxy("If16","If16",this,*coef_ang_integrals);
   coef_ang_integrals=(RooAbsReal*)ang_integrals_iter->Next();
   If17 = RooRealProxy("If17","If17",this,*coef_ang_integrals);
   coef_ang_integrals=(RooAbsReal*)ang_integrals_iter->Next();
   If18 = RooRealProxy("If18","If18",this,*coef_ang_integrals);

   // Integrals of the time dependent terms, for visualization.
   coef_time_integrals=(RooAbsReal*)time_integrals_iter->Next();
   IT_cosh = RooRealProxy("IT_cosh","IT_cosh",this,*coef_time_integrals);
   coef_time_integrals=(RooAbsReal*)time_integrals_iter->Next();
   IT_sinh = RooRealProxy("IT_sinh","IT_sinh",this,*coef_time_integrals);
   coef_time_integrals=(RooAbsReal*)time_integrals_iter->Next();
   IT_cos = RooRealProxy("IT_cos","IT_cos",this,*coef_time_integrals);
   coef_time_integrals=(RooAbsReal*)time_integrals_iter->Next();
   IT_sin = RooRealProxy("IT_sin","IT_sin",this,*coef_time_integrals);

   if (acctype == 0) {
      f1_eff[(int) year_opt] = TReseff.f1(year_opt);
      f2_eff[(int) year_opt] = 1.-TReseff.f1(year_opt);
      s1_eff[(int) year_opt] = TReseff.sigma1(year_opt);
      s2_eff[(int) year_opt] = TReseff.sigma2(year_opt);
   }
   else if (acctype == 1 or acctype == 2) {
      f1_eff[(int) year_opt] = TReseff.f1(year_opt);
      f2_eff[(int) year_opt] = 1.-TReseff.f1(year_opt);
      s1_eff[(int) year_opt] = TReseff.sigma1(year_opt);
      s2_eff[(int) year_opt] = TReseff.sigma2(year_opt);
      for (int i=0; i<6; ++i) {spl_knot_vector[(int) year_opt][(int) trig_opt][i] = spl.knot(wide_window,i);}
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][0] = (spl_knot_vector[(int) year_opt][(int) trig_opt][0]-TReseff.off(year_opt))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][1] = (spl_knot_vector[(int) year_opt][(int) trig_opt][1]-TReseff.off(year_opt))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][2] = (spl_knot_vector[(int) year_opt][(int) trig_opt][2]-TReseff.off(year_opt))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][3] = (spl_knot_vector[(int) year_opt][(int) trig_opt][3]-TReseff.off(year_opt))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][4] = (spl_knot_vector[(int) year_opt][(int) trig_opt][4]-TReseff.off(year_opt))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][5] = (spl_knot_vector[(int) year_opt][(int) trig_opt][5]-TReseff.off(year_opt))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][0] = (spl_knot_vector[(int) year_opt][(int) trig_opt][0]-TReseff.off(year_opt))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][1] = (spl_knot_vector[(int) year_opt][(int) trig_opt][1]-TReseff.off(year_opt))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][2] = (spl_knot_vector[(int) year_opt][(int) trig_opt][2]-TReseff.off(year_opt))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][3] = (spl_knot_vector[(int) year_opt][(int) trig_opt][3]-TReseff.off(year_opt))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][4] = (spl_knot_vector[(int) year_opt][(int) trig_opt][4]-TReseff.off(year_opt))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][5] = (spl_knot_vector[(int) year_opt][(int) trig_opt][5]-TReseff.off(year_opt))/(sqrt(2.)*s2_eff[(int) year_opt]);
      for (int ibin=0; ibin<5; ++ibin) {
         for (int k=0; k<4; ++k) {
            for (int i=0; i<(k+1); ++i) {
               for (int j=0; j<(i+1); ++j) {
                  spl_coef_array_1[(int) year_opt][(int) trig_opt][ibin][k][i][j] = spl.coef(year_opt,trig_opt,wide_window,ibin,k)*TMath::Factorial(k)/TMath::Factorial(k-i)/TMath::Factorial(i-j)/TMath::Factorial(j)*pow(s1_eff[(int) year_opt]/sqrt(2.),i+1)*pow(TReseff.off(year_opt),k-i);
                  spl_coef_array_2[(int) year_opt][(int) trig_opt][ibin][k][i][j] = spl.coef(year_opt,trig_opt,wide_window,ibin,k)*TMath::Factorial(k)/TMath::Factorial(k-i)/TMath::Factorial(i-j)/TMath::Factorial(j)*pow(s2_eff[(int) year_opt]/sqrt(2.),i+1)*pow(TReseff.off(year_opt),k-i);
               }
            }
         }
      }
   }
   else if (acctype == 3) {
      f1_eff[(int) year_opt] = TReseff.f1(1);
      f2_eff[(int) year_opt] = 1.-TReseff.f1(1);
      s1_eff[(int) year_opt] = TReseff.sigma1(1);
      s2_eff[(int) year_opt] = TReseff.sigma2(1);
      for (int i=0; i<6; ++i) {spl_knot_vector[(int) year_opt][(int) trig_opt][i] = genaccpar.knot_gen(wide_window,i);}
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][0] = (spl_knot_vector[(int) year_opt][(int) trig_opt][0]-TReseff.off(1))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][1] = (spl_knot_vector[(int) year_opt][(int) trig_opt][1]-TReseff.off(1))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][2] = (spl_knot_vector[(int) year_opt][(int) trig_opt][2]-TReseff.off(1))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][3] = (spl_knot_vector[(int) year_opt][(int) trig_opt][3]-TReseff.off(1))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][4] = (spl_knot_vector[(int) year_opt][(int) trig_opt][4]-TReseff.off(1))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][5] = (spl_knot_vector[(int) year_opt][(int) trig_opt][5]-TReseff.off(1))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][0] = (spl_knot_vector[(int) year_opt][(int) trig_opt][0]-TReseff.off(1))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][1] = (spl_knot_vector[(int) year_opt][(int) trig_opt][1]-TReseff.off(1))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][2] = (spl_knot_vector[(int) year_opt][(int) trig_opt][2]-TReseff.off(1))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][3] = (spl_knot_vector[(int) year_opt][(int) trig_opt][3]-TReseff.off(1))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][4] = (spl_knot_vector[(int) year_opt][(int) trig_opt][4]-TReseff.off(1))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][5] = (spl_knot_vector[(int) year_opt][(int) trig_opt][5]-TReseff.off(1))/(sqrt(2.)*s2_eff[(int) year_opt]);
      for (int ibin=0; ibin<5; ++ibin) {
         for (int k=0; k<4; ++k) {
            for (int i=0; i<(k+1); ++i) {
               for (int j=0; j<(i+1); ++j) {
                  spl_coef_array_1[(int) year_opt][(int) trig_opt][ibin][k][i][j] = genaccpar.coef_gen(wide_window,ibin,k)*TMath::Factorial(k)/TMath::Factorial(k-i)/TMath::Factorial(i-j)/TMath::Factorial(j)*pow(s1_eff[(int) year_opt]/sqrt(2.),i+1)*pow(TReseff.off(1),k-i);
                  spl_coef_array_2[(int) year_opt][(int) trig_opt][ibin][k][i][j] = genaccpar.coef_gen(wide_window,ibin,k)*TMath::Factorial(k)/TMath::Factorial(k-i)/TMath::Factorial(i-j)/TMath::Factorial(j)*pow(s2_eff[(int) year_opt]/sqrt(2.),i+1)*pow(TReseff.off(1),k-i);
               }
            }
         }
      }
   }
   DCP_prod[0] = -0.0101;
   DCP_prod[1] = -0.0072;
   fjjphhpindexdict[0][0][0][0] = 1;
   fjjphhpindexdict[0][1][0][0] = 2;
   fjjphhpindexdict[0][1][0][1] = 3;
   fjjphhpindexdict[0][1][0][2] = 3;
   fjjphhpindexdict[0][2][0][0] = 4;
   fjjphhpindexdict[0][2][0][1] = 5;
   fjjphhpindexdict[0][2][0][2] = 5;
   fjjphhpindexdict[1][0][0][0] = 2;
   fjjphhpindexdict[1][1][0][0] = 6;
   fjjphhpindexdict[1][1][0][1] = 5;
   fjjphhpindexdict[1][1][0][2] = 5;
   fjjphhpindexdict[1][2][0][0] = 7;
   fjjphhpindexdict[1][2][0][1] = 8;
   fjjphhpindexdict[1][2][0][2] = 8;
   fjjphhpindexdict[1][0][1][0] = 3;
   fjjphhpindexdict[1][0][2][0] = 3;
   fjjphhpindexdict[1][1][1][0] = 5;
   fjjphhpindexdict[1][1][2][0] = 5;
   fjjphhpindexdict[1][1][1][1] = 9;
   fjjphhpindexdict[1][1][1][2] = 9;
   fjjphhpindexdict[1][1][2][1] = 9;
   fjjphhpindexdict[1][1][2][2] = 9;
   fjjphhpindexdict[1][2][1][0] = 10;
   fjjphhpindexdict[1][2][2][0] = 10;
   fjjphhpindexdict[1][2][1][1] = 11;
   fjjphhpindexdict[1][2][1][2] = 11;
   fjjphhpindexdict[1][2][2][1] = 11;
   fjjphhpindexdict[1][2][2][2] = 11;
   fjjphhpindexdict[2][0][0][0] = 4;
   fjjphhpindexdict[2][1][0][0] = 7;
   fjjphhpindexdict[2][1][0][1] = 10;
   fjjphhpindexdict[2][1][0][2] = 10;
   fjjphhpindexdict[2][2][0][0] = 12;
   fjjphhpindexdict[2][2][0][1] = 13;
   fjjphhpindexdict[2][2][0][2] = 13;
   fjjphhpindexdict[2][0][1][0] = 5;
   fjjphhpindexdict[2][0][2][0] = 5;
   fjjphhpindexdict[2][1][1][0] = 8;
   fjjphhpindexdict[2][1][2][0] = 8;
   fjjphhpindexdict[2][1][1][1] = 11;
   fjjphhpindexdict[2][1][1][2] = 11;
   fjjphhpindexdict[2][1][2][1] = 11;
   fjjphhpindexdict[2][1][2][2] = 11;
   fjjphhpindexdict[2][2][1][0] = 13;
   fjjphhpindexdict[2][2][2][0] = 13;
   fjjphhpindexdict[2][2][1][1] = 14;
   fjjphhpindexdict[2][2][1][2] = 14;
   fjjphhpindexdict[2][2][2][1] = 14;
   fjjphhpindexdict[2][2][2][2] = 14;
   fjjphhpindexdict[0][2][0][3] = 9;
   fjjphhpindexdict[0][2][0][4] = 9;
   fjjphhpindexdict[1][2][0][3] = 11;
   fjjphhpindexdict[1][2][0][4] = 11;
   fjjphhpindexdict[1][2][1][3] = 15;
   fjjphhpindexdict[1][2][1][4] = 15;
   fjjphhpindexdict[1][2][2][3] = 15;
   fjjphhpindexdict[1][2][2][4] = 15;
   fjjphhpindexdict[2][2][0][3] = 16;
   fjjphhpindexdict[2][2][0][4] = 16;
   fjjphhpindexdict[2][2][1][3] = 17;
   fjjphhpindexdict[2][2][1][4] = 17;
   fjjphhpindexdict[2][2][2][3] = 17;
   fjjphhpindexdict[2][2][2][4] = 17;
   fjjphhpindexdict[2][0][3][0] = 9;
   fjjphhpindexdict[2][0][4][0] = 9;
   fjjphhpindexdict[2][1][3][0] = 11;
   fjjphhpindexdict[2][1][4][0] = 11;
   fjjphhpindexdict[2][1][3][1] = 15;
   fjjphhpindexdict[2][1][3][2] = 15;
   fjjphhpindexdict[2][1][4][1] = 15;
   fjjphhpindexdict[2][1][4][2] = 15;
   fjjphhpindexdict[2][2][3][0] = 16;
   fjjphhpindexdict[2][2][4][0] = 16;
   fjjphhpindexdict[2][2][3][1] = 17;
   fjjphhpindexdict[2][2][3][2] = 17;
   fjjphhpindexdict[2][2][4][1] = 17;
   fjjphhpindexdict[2][2][4][2] = 17;
   fjjphhpindexdict[2][2][3][3] = 18;
   fjjphhpindexdict[2][2][3][4] = 18;
   fjjphhpindexdict[2][2][4][3] = 18;
   fjjphhpindexdict[2][2][4][4] = 18;
   ghhpindexdict[0][0] = 1;
   ghhpindexdict[0][1] = 2;
   ghhpindexdict[0][2] = 3;
   ghhpindexdict[1][0] = 2;
   ghhpindexdict[1][1] = 4;
   ghhpindexdict[1][2] = 5;
   ghhpindexdict[2][0] = 3;
   ghhpindexdict[2][1] = 5;
   ghhpindexdict[2][2] = 6;
   ghhpindexdict[0][3] = 7;
   ghhpindexdict[0][4] = 8;
   ghhpindexdict[1][3] = 9;
   ghhpindexdict[1][4] = 10;
   ghhpindexdict[2][3] = 11;
   ghhpindexdict[2][4] = 12;
   ghhpindexdict[3][0] = 7;
   ghhpindexdict[3][1] = 9;
   ghhpindexdict[3][2] = 11;
   ghhpindexdict[3][3] = 13;
   ghhpindexdict[3][4] = 14;
   ghhpindexdict[4][0] = 8;
   ghhpindexdict[4][1] = 10;
   ghhpindexdict[4][2] = 12;
   ghhpindexdict[4][3] = 14;
   ghhpindexdict[4][4] = 15;
   Nj1j2hdict[0][0][0] = TComplex(1./(2.*sqrt(2.*pi)),0.);
   Nj1j2hdict[0][1][0] = TComplex(-sqrt(3.)/(2.*sqrt(2.*pi)),0.);
   Nj1j2hdict[0][2][0] = TComplex(sqrt(5.)/(4.*sqrt(2.*pi)),0.);
   Nj1j2hdict[1][0][0] = TComplex(sqrt(3.)/(2.*sqrt(2.*pi)),0.);
   Nj1j2hdict[1][1][0] = TComplex(-3./(2.*sqrt(2.*pi)),0.);
   Nj1j2hdict[1][1][1] = TComplex(-3./(4.*sqrt(pi)),0.);
   Nj1j2hdict[1][1][2] = TComplex(0.,-3./(4.*sqrt(pi)));
   Nj1j2hdict[1][2][0] = TComplex(sqrt(15.)/(4.*sqrt(2.*pi)),0.);
   Nj1j2hdict[1][2][1] = TComplex(3.*sqrt(5.)/(4.*sqrt(pi)),0.);
   Nj1j2hdict[1][2][2] = TComplex(0.,3.*sqrt(5.)/(4.*sqrt(pi)));
   Nj1j2hdict[2][0][0] = TComplex(sqrt(5.)/(4.*sqrt(2.*pi)),0.);
   Nj1j2hdict[2][1][0] = TComplex(-sqrt(15.)/(4.*sqrt(2.*pi)),0.);
   Nj1j2hdict[2][1][1] = TComplex(-3.*sqrt(5.)/(4.*sqrt(pi)),0.);
   Nj1j2hdict[2][1][2] = TComplex(0.,-3.*sqrt(5.)/(4.*sqrt(pi)));
   Nj1j2hdict[2][2][0] = TComplex(5./(8.*sqrt(2.*pi)),0.);
   Nj1j2hdict[2][2][1] = TComplex(15./(4.*sqrt(pi)),0.);
   Nj1j2hdict[2][2][2] = TComplex(0.,15./(4.*sqrt(pi)));
   Nj1j2hdict[2][2][3] = TComplex(15./(16.*sqrt(pi)),0.);
   Nj1j2hdict[2][2][4] = TComplex(0.,15./(16.*sqrt(pi)));
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][0][0][0] = TComplex(Ih22Re,0.);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][0][0][1] = TComplex(Ih1Re,Ih1Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][0][0][2] = TComplex(Ih2Re,Ih2Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][0][1][0] = TComplex(Ih1Re,Ih1Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][0][1][1] = TComplex(Ih3Re,Ih3Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][0][1][2] = TComplex(Ih4Re,Ih4Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][0][2][0] = TComplex(Ih2Re,Ih2Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][0][2][1] = TComplex(Ih4Re,Ih4Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][0][2][2] = TComplex(Ih5Re,Ih5Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][1][0][0] = TComplex(Ih1Re,-Ih1Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][1][0][1] = TComplex(Ih23Re,0.);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][1][0][2] = TComplex(Ih6Re,Ih6Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][1][1][0] = TComplex(Ih7Re,Ih7Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][1][1][1] = TComplex(Ih8Re,Ih8Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][1][1][2] = TComplex(Ih9Re,Ih9Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][1][2][0] = TComplex(Ih10Re,Ih10Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][1][2][1] = TComplex(Ih11Re,Ih11Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][1][2][2] = TComplex(Ih12Re,Ih12Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][2][0][0] = TComplex(Ih2Re,-Ih2Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][2][0][1] = TComplex(Ih6Re,-Ih6Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][2][0][2] = TComplex(Ih25Re,0.);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][2][1][0] = TComplex(Ih10Re,-Ih10Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][2][1][1] = TComplex(Ih13Re,Ih13Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][2][1][2] = TComplex(Ih14Re,Ih14Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][2][2][0] = TComplex(Ih15Re,Ih15Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][2][2][1] = TComplex(Ih16Re,Ih16Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][2][2][2] = TComplex(Ih17Re,Ih17Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][0][0][0] = TComplex(Ih1Re,-Ih1Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][0][0][1] = TComplex(Ih7Re,Ih7Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][0][0][2] = TComplex(Ih10Re,Ih10Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][0][1][0] = TComplex(Ih24Re,0.);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][0][1][1] = TComplex(Ih8Re,Ih8Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][0][1][2] = TComplex(Ih11Re,Ih11Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][0][2][0] = TComplex(Ih6Re,Ih6Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][0][2][1] = TComplex(Ih9Re,Ih9Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][0][2][2] = TComplex(Ih12Re,Ih12Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][1][0][0] = TComplex(Ih3Re,-Ih3Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][1][0][1] = TComplex(Ih8Re,-Ih8Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][1][0][2] = TComplex(Ih13Re,-Ih13Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][1][1][0] = TComplex(Ih8Re,-Ih8Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][1][1][1] = TComplex(Ih27Re,0.);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][1][1][2] = TComplex(Ih18Re,Ih18Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][1][2][0] = TComplex(Ih13Re,-Ih13Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][1][2][1] = TComplex(Ih18Re,Ih18Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][1][2][2] = TComplex(Ih19Re,Ih19Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][2][0][0] = TComplex(Ih4Re,-Ih4Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][2][0][1] = TComplex(Ih9Re,-Ih9Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][2][0][2] = TComplex(Ih14Re,-Ih14Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][2][1][0] = TComplex(Ih11Re,-Ih11Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][2][1][1] = TComplex(Ih18Re,-Ih18Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][2][1][2] = TComplex(Ih28Re,0.);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][2][2][0] = TComplex(Ih16Re,-Ih16Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][2][2][1] = TComplex(Ih20Re,Ih20Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][2][2][2] = TComplex(Ih21Re,Ih21Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][0][0][0] = TComplex(Ih2Re,-Ih2Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][0][0][1] = TComplex(Ih10Re,-Ih10Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][0][0][2] = TComplex(Ih15Re,Ih15Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][0][1][0] = TComplex(Ih6Re,-Ih6Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][0][1][1] = TComplex(Ih13Re,Ih13Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][0][1][2] = TComplex(Ih16Re,Ih16Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][0][2][0] = TComplex(Ih26Re,0.);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][0][2][1] = TComplex(Ih14Re,Ih14Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][0][2][2] = TComplex(Ih17Re,Ih17Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][1][0][0] = TComplex(Ih4Re,-Ih4Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][1][0][1] = TComplex(Ih11Re,-Ih11Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][1][0][2] = TComplex(Ih16Re,-Ih16Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][1][1][0] = TComplex(Ih9Re,-Ih9Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][1][1][1] = TComplex(Ih18Re,-Ih18Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][1][1][2] = TComplex(Ih20Re,Ih20Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][1][2][0] = TComplex(Ih14Re,-Ih14Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][1][2][1] = TComplex(Ih29Re,0.);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][1][2][2] = TComplex(Ih21Re,Ih21Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][2][0][0] = TComplex(Ih5Re,-Ih5Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][2][0][1] = TComplex(Ih12Re,-Ih12Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][2][0][2] = TComplex(Ih17Re,-Ih17Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][2][1][0] = TComplex(Ih12Re,-Ih12Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][2][1][1] = TComplex(Ih19Re,-Ih19Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][2][1][2] = TComplex(Ih21Re,-Ih21Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][2][2][0] = TComplex(Ih17Re,-Ih17Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][2][2][1] = TComplex(Ih21Re,-Ih21Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][2][2][2] = TComplex(Ih30Re,0.);

 }

// ---------------------------------------------------

 KpiKpiSpectrumNW::KpiKpiSpectrumNW(const KpiKpiSpectrumNW& other, const char* name) :  
   RooAbsPdf(other,name),
   wide_window("wide_window",this,other.wide_window),
   year_opt("year_opt",this,other.year_opt),
   trig_opt("trig_opt",this,other.trig_opt),
   alt_fit("alt_fit",this,other.alt_fit),
   option("option",this,other.option),
   inftres("inftres",this,other.inftres),
   acctype("acctype",this,other.acctype),
   A_j1("A_j1",this,other.A_j1),
   A_j2("A_j2",this,other.A_j2),
   A_h("A_h",this,other.A_h),
   A_j1p("A_j1p",this,other.A_j1p),
   A_j2p("A_j2p",this,other.A_j2p),
   A_hp("A_hp",this,other.A_hp),
   qcomp("qcomp",this,other.qcomp),
   decision_SSK("decision_SSK",this,other.decision_SSK),
   decision_OS("decision_OS",this,other.decision_OS),
   etamistag_SSK("etamistag_SSK",this,other.etamistag_SSK),
   etamistag_OS("etamistag_OS",this,other.etamistag_OS),
   m1("m1",this,other.m1),
   m2("m2",this,other.m2),
   cos1("cos1",this,other.cos1),
   cos2("cos2",this,other.cos2),
   phi("phi",this,other.phi),
   t("t",this,other.t),
   t_err("t_err",this,other.t_err),
   f_VV("f_VV",this,other.f_VV),
   f_Swave("f_Swave",this,other.f_Swave),
   f_SS("f_SS",this,other.f_SS),
   f_VTTV("f_VTTV",this,other.f_VTTV),
   f_TT("f_TT",this,other.f_TT),
   D_SVVS("D_SVVS",this,other.D_SVVS),
   D_VTTV("D_VTTV",this,other.D_VTTV),
   D_STTS("D_STTS",this,other.D_STTS),
   fL_VV("fL_VV",this,other.fL_VV),
   xpar_VV("xpar_VV",this,other.xpar_VV),
   fL_VT("fL_VT",this,other.fL_VT),
   xpar_VT("xpar_VT",this,other.xpar_VT),
   fL_TV("fL_TV",this,other.fL_TV),
   xpar_TV("xpar_TV",this,other.xpar_TV),
   fL_TT("fL_TT",this,other.fL_TT),
   xpar1_TT("xpar1_TT",this,other.xpar1_TT),
   xperp1_TT("xperp1_TT",this,other.xperp1_TT),
   xpar2_TT("xpar2_TT",this,other.xpar2_TT),
   DCP_SS("DCP_SS",this,other.DCP_SS),
   DCP_SV("DCP_SV",this,other.DCP_SV),
   DCP_VS("DCP_VS",this,other.DCP_VS),
   DCP_ST("DCP_ST",this,other.DCP_ST),
   DCP_TS("DCP_TS",this,other.DCP_TS),
   DCP_VV("DCP_VV",this,other.DCP_VV),
   DCP_VT("DCP_VT",this,other.DCP_VT),
   DCP_TV("DCP_TV",this,other.DCP_TV),
   DCP_TT("DCP_TT",this,other.DCP_TT),
   delta00("delta00",this,other.delta00),
   delta01("delta01",this,other.delta01),
   delta10("delta10",this,other.delta10),
   delta02("delta02",this,other.delta02),
   delta20("delta20",this,other.delta20),
   delta11par("delta11par",this,other.delta11par),
   delta11perp("delta11perp",this,other.delta11perp),
   delta120("delta120",this,other.delta120),
   delta12par("delta12par",this,other.delta12par),
   delta12perp("delta12perp",this,other.delta12perp),
   delta210("delta210",this,other.delta210),
   delta21par("delta21par",this,other.delta21par),
   delta21perp("delta21perp",this,other.delta21perp),
   delta220("delta220",this,other.delta220),
   delta22par("delta22par",this,other.delta22par),
   delta22perp("delta22perp",this,other.delta22perp),
   delta22par2("delta22par2",this,other.delta22par2),
   delta22perp2("delta22perp2",this,other.delta22perp2),
   phis("phis",this,other.phis),
   dphi_SS("dphi_SS",this,other.dphi_SS),
   dphi_SV("dphi_SV",this,other.dphi_SV),
   dphi_VS("dphi_VS",this,other.dphi_VS),
   dphi_ST("dphi_ST",this,other.dphi_ST),
   dphi_TS("dphi_TS",this,other.dphi_TS),
   dphi_VT("dphi_VT",this,other.dphi_VT),
   dphi_TV("dphi_TV",this,other.dphi_TV),
   dphi_TT("dphi_TT",this,other.dphi_TT),
   delta_m_freq("delta_m_freq",this,other.delta_m_freq),
   gamma_Bs_freq("gamma_Bs_freq",this,other.gamma_Bs_freq),
   delta_gamma_freq("delta_gamma_freq",this,other.delta_gamma_freq),
   p0metac_tag_SSK("p0metac_tag_SSK",this,other.p0metac_tag_SSK),
   p0metac_tag_OS("p0metac_tag_OS",this,other.p0metac_tag_OS),
   Dp0half_tag_SSK("Dp0half_tag_SSK",this,other.Dp0half_tag_SSK),
   Dp0half_tag_OS("Dp0half_tag_OS",this,other.Dp0half_tag_OS),
   p1_tag_SSK("p1_tag_SSK",this,other.p1_tag_SSK),
   p1_tag_OS("p1_tag_OS",this,other.p1_tag_OS),
   Dp1half_tag_SSK("Dp1half_tag_SSK",this,other.Dp1half_tag_SSK),
   Dp1half_tag_OS("Dp1half_tag_OS",this,other.Dp1half_tag_OS),
   etac_tag_SSK("etac_tag_SSK",this,other.etac_tag_SSK),
   etac_tag_OS("etac_tag_OS",this,other.etac_tag_OS),
   mv("mv",this,other.mv),
   ms("ms",this,other.ms),
   mt("mt",this,other.mt),
   gv("gv",this,other.gv),
   gs("gs",this,other.gs),
   gt("gt",this,other.gt),
   res_mass("res_mass",this,other.res_mass),
   tag_eff_SSK("tag_eff_SSK",this,other.tag_eff_SSK),
   mu1_SSK("mu1_SSK",this,other.mu1_SSK),
   sigma1_SSK("sigma1_SSK",this,other.sigma1_SSK),
   c_SSK("c_SSK",this,other.c_SSK),
   mu2_SSK("mu2_SSK",this,other.mu2_SSK),
   sigma2_SSK("sigma2_SSK",this,other.sigma2_SSK),
   tag_eff_OS("tag_eff_OS",this,other.tag_eff_OS),
   mu1_OS("mu1_OS",this,other.mu1_OS),
   sigma1_OS("sigma1_OS",this,other.sigma1_OS),
   c_OS("c_OS",this,other.c_OS),
   mu2_OS("mu2_OS",this,other.mu2_OS),
   sigma2_OS("sigma2_OS",this,other.sigma2_OS),
   gamma1_dt("gamma1_dt",this,other.gamma1_dt),
   beta1_dt("beta1_dt",this,other.beta1_dt),
   c_dt("c_dt",this,other.c_dt),
   gamma2_dt("gamma2_dt",this,other.gamma2_dt),
   beta2_dt("beta2_dt",this,other.beta2_dt),
   pw_mass_altmodel("pw_mass_altmodel",this,other.pw_mass_altmodel),
   f_1410_rel2_892("f_1410_rel2_892",this,other.f_1410_rel2_892),
   delta_1410_rel2_892("delta_1410_rel2_892",this,other.delta_1410_rel2_892),
   f_1680_rel2_892("f_1680_rel2_892",this,other.f_1680_rel2_892),
   delta_1680_rel2_892("delta_1680_rel2_892",this,other.delta_1680_rel2_892),
   Im00("Im00",this,other.Im00),
   Im01("Im01",this,other.Im01),
   Im10("Im10",this,other.Im10),
   Im02("Im02",this,other.Im02),
   Im20("Im20",this,other.Im20),
   Im11("Im11",this,other.Im11),
   Im12("Im12",this,other.Im12),
   Im21("Im21",this,other.Im21),
   Im22("Im22",this,other.Im22),
   Ih1Re("Ih1Re",this,other.Ih1Re),
   Ih2Re("Ih2Re",this,other.Ih2Re),
   Ih3Re("Ih3Re",this,other.Ih3Re),
   Ih4Re("Ih4Re",this,other.Ih4Re),
   Ih5Re("Ih5Re",this,other.Ih5Re),
   Ih6Re("Ih6Re",this,other.Ih6Re),
   Ih7Re("Ih7Re",this,other.Ih7Re),
   Ih8Re("Ih8Re",this,other.Ih8Re),
   Ih9Re("Ih9Re",this,other.Ih9Re),
   Ih10Re("Ih10Re",this,other.Ih10Re),
   Ih11Re("Ih11Re",this,other.Ih11Re),
   Ih12Re("Ih12Re",this,other.Ih12Re),
   Ih13Re("Ih13Re",this,other.Ih13Re),
   Ih14Re("Ih14Re",this,other.Ih14Re),
   Ih15Re("Ih15Re",this,other.Ih15Re),
   Ih16Re("Ih16Re",this,other.Ih16Re),
   Ih17Re("Ih17Re",this,other.Ih17Re),
   Ih18Re("Ih18Re",this,other.Ih18Re),
   Ih19Re("Ih19Re",this,other.Ih19Re),
   Ih20Re("Ih20Re",this,other.Ih20Re),
   Ih21Re("Ih21Re",this,other.Ih21Re),
   Ih22Re("Ih22Re",this,other.Ih22Re),
   Ih23Re("Ih23Re",this,other.Ih23Re),
   Ih24Re("Ih24Re",this,other.Ih24Re),
   Ih25Re("Ih25Re",this,other.Ih25Re),
   Ih26Re("Ih26Re",this,other.Ih26Re),
   Ih27Re("Ih27Re",this,other.Ih27Re),
   Ih28Re("Ih28Re",this,other.Ih28Re),
   Ih29Re("Ih29Re",this,other.Ih29Re),
   Ih30Re("Ih30Re",this,other.Ih30Re),
   Ih1Im("Ih1Im",this,other.Ih1Im),
   Ih2Im("Ih2Im",this,other.Ih2Im),
   Ih3Im("Ih3Im",this,other.Ih3Im),
   Ih4Im("Ih4Im",this,other.Ih4Im),
   Ih5Im("Ih5Im",this,other.Ih5Im),
   Ih6Im("Ih6Im",this,other.Ih6Im),
   Ih7Im("Ih7Im",this,other.Ih7Im),
   Ih8Im("Ih8Im",this,other.Ih8Im),
   Ih9Im("Ih9Im",this,other.Ih9Im),
   Ih10Im("Ih10Im",this,other.Ih10Im),
   Ih11Im("Ih11Im",this,other.Ih11Im),
   Ih12Im("Ih12Im",this,other.Ih12Im),
   Ih13Im("Ih13Im",this,other.Ih13Im),
   Ih14Im("Ih14Im",this,other.Ih14Im),
   Ih15Im("Ih15Im",this,other.Ih15Im),
   Ih16Im("Ih16Im",this,other.Ih16Im),
   Ih17Im("Ih17Im",this,other.Ih17Im),
   Ih18Im("Ih18Im",this,other.Ih18Im),
   Ih19Im("Ih19Im",this,other.Ih19Im),
   Ih20Im("Ih20Im",this,other.Ih20Im),
   Ih21Im("Ih21Im",this,other.Ih21Im),
   If1("If1",this,other.If1),
   If2("If2",this,other.If2),
   If3("If3",this,other.If3),
   If4("If4",this,other.If4),
   If5("If5",this,other.If5),
   If6("If6",this,other.If6),
   If7("If7",this,other.If7),
   If8("If8",this,other.If8),
   If9("If9",this,other.If9),
   If10("If10",this,other.If10),
   If11("If11",this,other.If11),
   If12("If12",this,other.If12),
   If13("If13",this,other.If13),
   If14("If14",this,other.If14),
   If15("If15",this,other.If15),
   If16("If16",this,other.If16),
   If17("If17",this,other.If17),
   If18("If18",this,other.If18),
   IT_cosh("IT_cosh",this,other.IT_cosh),
   IT_sinh("IT_sinh",this,other.IT_sinh),
   IT_cos("IT_cos",this,other.IT_cos),
   IT_sin("IT_sin",this,other.IT_sin)
 {
   if (acctype == 0) {
      f1_eff[(int) year_opt] = TReseff.f1(year_opt);
      f2_eff[(int) year_opt] = 1.-TReseff.f1(year_opt);
      s1_eff[(int) year_opt] = TReseff.sigma1(year_opt);
      s2_eff[(int) year_opt] = TReseff.sigma2(year_opt);
   }
   else if (acctype == 1 or acctype == 2) {
      f1_eff[(int) year_opt] = TReseff.f1(year_opt);
      f2_eff[(int) year_opt] = 1.-TReseff.f1(year_opt);
      s1_eff[(int) year_opt] = TReseff.sigma1(year_opt);
      s2_eff[(int) year_opt] = TReseff.sigma2(year_opt);
      for (int i=0; i<6; ++i) {spl_knot_vector[(int) year_opt][(int) trig_opt][i] = spl.knot(wide_window,i);}
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][0] = (spl_knot_vector[(int) year_opt][(int) trig_opt][0]-TReseff.off(year_opt))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][1] = (spl_knot_vector[(int) year_opt][(int) trig_opt][1]-TReseff.off(year_opt))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][2] = (spl_knot_vector[(int) year_opt][(int) trig_opt][2]-TReseff.off(year_opt))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][3] = (spl_knot_vector[(int) year_opt][(int) trig_opt][3]-TReseff.off(year_opt))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][4] = (spl_knot_vector[(int) year_opt][(int) trig_opt][4]-TReseff.off(year_opt))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][5] = (spl_knot_vector[(int) year_opt][(int) trig_opt][5]-TReseff.off(year_opt))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][0] = (spl_knot_vector[(int) year_opt][(int) trig_opt][0]-TReseff.off(year_opt))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][1] = (spl_knot_vector[(int) year_opt][(int) trig_opt][1]-TReseff.off(year_opt))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][2] = (spl_knot_vector[(int) year_opt][(int) trig_opt][2]-TReseff.off(year_opt))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][3] = (spl_knot_vector[(int) year_opt][(int) trig_opt][3]-TReseff.off(year_opt))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][4] = (spl_knot_vector[(int) year_opt][(int) trig_opt][4]-TReseff.off(year_opt))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][5] = (spl_knot_vector[(int) year_opt][(int) trig_opt][5]-TReseff.off(year_opt))/(sqrt(2.)*s2_eff[(int) year_opt]);
      for (int ibin=0; ibin<5; ++ibin) {
         for (int k=0; k<4; ++k) {
            for (int i=0; i<(k+1); ++i) {
               for (int j=0; j<(i+1); ++j) {
                  spl_coef_array_1[(int) year_opt][(int) trig_opt][ibin][k][i][j] = spl.coef(year_opt,trig_opt,wide_window,ibin,k)*TMath::Factorial(k)/TMath::Factorial(k-i)/TMath::Factorial(i-j)/TMath::Factorial(j)*pow(s1_eff[(int) year_opt]/sqrt(2.),i+1)*pow(TReseff.off(year_opt),k-i);
                  spl_coef_array_2[(int) year_opt][(int) trig_opt][ibin][k][i][j] = spl.coef(year_opt,trig_opt,wide_window,ibin,k)*TMath::Factorial(k)/TMath::Factorial(k-i)/TMath::Factorial(i-j)/TMath::Factorial(j)*pow(s2_eff[(int) year_opt]/sqrt(2.),i+1)*pow(TReseff.off(year_opt),k-i);
               }
            }
         }
      }
   }
   else if (acctype == 3) {
      f1_eff[(int) year_opt] = TReseff.f1(1);
      f2_eff[(int) year_opt] = 1.-TReseff.f1(1);
      s1_eff[(int) year_opt] = TReseff.sigma1(1);
      s2_eff[(int) year_opt] = TReseff.sigma2(1);
      for (int i=0; i<6; ++i) {spl_knot_vector[(int) year_opt][(int) trig_opt][i] = genaccpar.knot_gen(wide_window,i);}
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][0] = (spl_knot_vector[(int) year_opt][(int) trig_opt][0]-TReseff.off(1))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][1] = (spl_knot_vector[(int) year_opt][(int) trig_opt][1]-TReseff.off(1))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][2] = (spl_knot_vector[(int) year_opt][(int) trig_opt][2]-TReseff.off(1))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][3] = (spl_knot_vector[(int) year_opt][(int) trig_opt][3]-TReseff.off(1))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][4] = (spl_knot_vector[(int) year_opt][(int) trig_opt][4]-TReseff.off(1))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x1_vector[(int) year_opt][(int) trig_opt][5] = (spl_knot_vector[(int) year_opt][(int) trig_opt][5]-TReseff.off(1))/(sqrt(2.)*s1_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][0] = (spl_knot_vector[(int) year_opt][(int) trig_opt][0]-TReseff.off(1))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][1] = (spl_knot_vector[(int) year_opt][(int) trig_opt][1]-TReseff.off(1))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][2] = (spl_knot_vector[(int) year_opt][(int) trig_opt][2]-TReseff.off(1))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][3] = (spl_knot_vector[(int) year_opt][(int) trig_opt][3]-TReseff.off(1))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][4] = (spl_knot_vector[(int) year_opt][(int) trig_opt][4]-TReseff.off(1))/(sqrt(2.)*s2_eff[(int) year_opt]);
      spl_knot_x2_vector[(int) year_opt][(int) trig_opt][5] = (spl_knot_vector[(int) year_opt][(int) trig_opt][5]-TReseff.off(1))/(sqrt(2.)*s2_eff[(int) year_opt]);
      for (int ibin=0; ibin<5; ++ibin) {
         for (int k=0; k<4; ++k) {
            for (int i=0; i<(k+1); ++i) {
               for (int j=0; j<(i+1); ++j) {
                  spl_coef_array_1[(int) year_opt][(int) trig_opt][ibin][k][i][j] = genaccpar.coef_gen(wide_window,ibin,k)*TMath::Factorial(k)/TMath::Factorial(k-i)/TMath::Factorial(i-j)/TMath::Factorial(j)*pow(s1_eff[(int) year_opt]/sqrt(2.),i+1)*pow(TReseff.off(1),k-i);
                  spl_coef_array_2[(int) year_opt][(int) trig_opt][ibin][k][i][j] = genaccpar.coef_gen(wide_window,ibin,k)*TMath::Factorial(k)/TMath::Factorial(k-i)/TMath::Factorial(i-j)/TMath::Factorial(j)*pow(s2_eff[(int) year_opt]/sqrt(2.),i+1)*pow(TReseff.off(1),k-i);
               }
            }
         }
      }
   }
   DCP_prod[0] = -0.0101;
   DCP_prod[1] = -0.0072;
   fjjphhpindexdict[0][0][0][0] = 1;
   fjjphhpindexdict[0][1][0][0] = 2;
   fjjphhpindexdict[0][1][0][1] = 3;
   fjjphhpindexdict[0][1][0][2] = 3;
   fjjphhpindexdict[0][2][0][0] = 4;
   fjjphhpindexdict[0][2][0][1] = 5;
   fjjphhpindexdict[0][2][0][2] = 5;
   fjjphhpindexdict[1][0][0][0] = 2;
   fjjphhpindexdict[1][1][0][0] = 6;
   fjjphhpindexdict[1][1][0][1] = 5;
   fjjphhpindexdict[1][1][0][2] = 5;
   fjjphhpindexdict[1][2][0][0] = 7;
   fjjphhpindexdict[1][2][0][1] = 8;
   fjjphhpindexdict[1][2][0][2] = 8;
   fjjphhpindexdict[1][0][1][0] = 3;
   fjjphhpindexdict[1][0][2][0] = 3;
   fjjphhpindexdict[1][1][1][0] = 5;
   fjjphhpindexdict[1][1][2][0] = 5;
   fjjphhpindexdict[1][1][1][1] = 9;
   fjjphhpindexdict[1][1][1][2] = 9;
   fjjphhpindexdict[1][1][2][1] = 9;
   fjjphhpindexdict[1][1][2][2] = 9;
   fjjphhpindexdict[1][2][1][0] = 10;
   fjjphhpindexdict[1][2][2][0] = 10;
   fjjphhpindexdict[1][2][1][1] = 11;
   fjjphhpindexdict[1][2][1][2] = 11;
   fjjphhpindexdict[1][2][2][1] = 11;
   fjjphhpindexdict[1][2][2][2] = 11;
   fjjphhpindexdict[2][0][0][0] = 4;
   fjjphhpindexdict[2][1][0][0] = 7;
   fjjphhpindexdict[2][1][0][1] = 10;
   fjjphhpindexdict[2][1][0][2] = 10;
   fjjphhpindexdict[2][2][0][0] = 12;
   fjjphhpindexdict[2][2][0][1] = 13;
   fjjphhpindexdict[2][2][0][2] = 13;
   fjjphhpindexdict[2][0][1][0] = 5;
   fjjphhpindexdict[2][0][2][0] = 5;
   fjjphhpindexdict[2][1][1][0] = 8;
   fjjphhpindexdict[2][1][2][0] = 8;
   fjjphhpindexdict[2][1][1][1] = 11;
   fjjphhpindexdict[2][1][1][2] = 11;
   fjjphhpindexdict[2][1][2][1] = 11;
   fjjphhpindexdict[2][1][2][2] = 11;
   fjjphhpindexdict[2][2][1][0] = 13;
   fjjphhpindexdict[2][2][2][0] = 13;
   fjjphhpindexdict[2][2][1][1] = 14;
   fjjphhpindexdict[2][2][1][2] = 14;
   fjjphhpindexdict[2][2][2][1] = 14;
   fjjphhpindexdict[2][2][2][2] = 14;
   fjjphhpindexdict[0][2][0][3] = 9;
   fjjphhpindexdict[0][2][0][4] = 9;
   fjjphhpindexdict[1][2][0][3] = 11;
   fjjphhpindexdict[1][2][0][4] = 11;
   fjjphhpindexdict[1][2][1][3] = 15;
   fjjphhpindexdict[1][2][1][4] = 15;
   fjjphhpindexdict[1][2][2][3] = 15;
   fjjphhpindexdict[1][2][2][4] = 15;
   fjjphhpindexdict[2][2][0][3] = 16;
   fjjphhpindexdict[2][2][0][4] = 16;
   fjjphhpindexdict[2][2][1][3] = 17;
   fjjphhpindexdict[2][2][1][4] = 17;
   fjjphhpindexdict[2][2][2][3] = 17;
   fjjphhpindexdict[2][2][2][4] = 17;
   fjjphhpindexdict[2][0][3][0] = 9;
   fjjphhpindexdict[2][0][4][0] = 9;
   fjjphhpindexdict[2][1][3][0] = 11;
   fjjphhpindexdict[2][1][4][0] = 11;
   fjjphhpindexdict[2][1][3][1] = 15;
   fjjphhpindexdict[2][1][3][2] = 15;
   fjjphhpindexdict[2][1][4][1] = 15;
   fjjphhpindexdict[2][1][4][2] = 15;
   fjjphhpindexdict[2][2][3][0] = 16;
   fjjphhpindexdict[2][2][4][0] = 16;
   fjjphhpindexdict[2][2][3][1] = 17;
   fjjphhpindexdict[2][2][3][2] = 17;
   fjjphhpindexdict[2][2][4][1] = 17;
   fjjphhpindexdict[2][2][4][2] = 17;
   fjjphhpindexdict[2][2][3][3] = 18;
   fjjphhpindexdict[2][2][3][4] = 18;
   fjjphhpindexdict[2][2][4][3] = 18;
   fjjphhpindexdict[2][2][4][4] = 18;
   ghhpindexdict[0][0] = 1;
   ghhpindexdict[0][1] = 2;
   ghhpindexdict[0][2] = 3;
   ghhpindexdict[1][0] = 2;
   ghhpindexdict[1][1] = 4;
   ghhpindexdict[1][2] = 5;
   ghhpindexdict[2][0] = 3;
   ghhpindexdict[2][1] = 5;
   ghhpindexdict[2][2] = 6;
   ghhpindexdict[0][3] = 7;
   ghhpindexdict[0][4] = 8;
   ghhpindexdict[1][3] = 9;
   ghhpindexdict[1][4] = 10;
   ghhpindexdict[2][3] = 11;
   ghhpindexdict[2][4] = 12;
   ghhpindexdict[3][0] = 7;
   ghhpindexdict[3][1] = 9;
   ghhpindexdict[3][2] = 11;
   ghhpindexdict[3][3] = 13;
   ghhpindexdict[3][4] = 14;
   ghhpindexdict[4][0] = 8;
   ghhpindexdict[4][1] = 10;
   ghhpindexdict[4][2] = 12;
   ghhpindexdict[4][3] = 14;
   ghhpindexdict[4][4] = 15;
   Nj1j2hdict[0][0][0] = TComplex(1./(2.*sqrt(2.*pi)),0.);
   Nj1j2hdict[0][1][0] = TComplex(-sqrt(3.)/(2.*sqrt(2.*pi)),0.);
   Nj1j2hdict[0][2][0] = TComplex(sqrt(5.)/(4.*sqrt(2.*pi)),0.);
   Nj1j2hdict[1][0][0] = TComplex(sqrt(3.)/(2.*sqrt(2.*pi)),0.);
   Nj1j2hdict[1][1][0] = TComplex(-3./(2.*sqrt(2.*pi)),0.);
   Nj1j2hdict[1][1][1] = TComplex(-3./(4.*sqrt(pi)),0.);
   Nj1j2hdict[1][1][2] = TComplex(0.,-3./(4.*sqrt(pi)));
   Nj1j2hdict[1][2][0] = TComplex(sqrt(15.)/(4.*sqrt(2.*pi)),0.);
   Nj1j2hdict[1][2][1] = TComplex(3.*sqrt(5.)/(4.*sqrt(pi)),0.);
   Nj1j2hdict[1][2][2] = TComplex(0.,3.*sqrt(5.)/(4.*sqrt(pi)));
   Nj1j2hdict[2][0][0] = TComplex(sqrt(5.)/(4.*sqrt(2.*pi)),0.);
   Nj1j2hdict[2][1][0] = TComplex(-sqrt(15.)/(4.*sqrt(2.*pi)),0.);
   Nj1j2hdict[2][1][1] = TComplex(-3.*sqrt(5.)/(4.*sqrt(pi)),0.);
   Nj1j2hdict[2][1][2] = TComplex(0.,-3.*sqrt(5.)/(4.*sqrt(pi)));
   Nj1j2hdict[2][2][0] = TComplex(5./(8.*sqrt(2.*pi)),0.);
   Nj1j2hdict[2][2][1] = TComplex(15./(4.*sqrt(pi)),0.);
   Nj1j2hdict[2][2][2] = TComplex(0.,15./(4.*sqrt(pi)));
   Nj1j2hdict[2][2][3] = TComplex(15./(16.*sqrt(pi)),0.);
   Nj1j2hdict[2][2][4] = TComplex(0.,15./(16.*sqrt(pi)));
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][0][0][0] = TComplex(Ih22Re,0.);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][0][0][1] = TComplex(Ih1Re,Ih1Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][0][0][2] = TComplex(Ih2Re,Ih2Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][0][1][0] = TComplex(Ih1Re,Ih1Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][0][1][1] = TComplex(Ih3Re,Ih3Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][0][1][2] = TComplex(Ih4Re,Ih4Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][0][2][0] = TComplex(Ih2Re,Ih2Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][0][2][1] = TComplex(Ih4Re,Ih4Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][0][2][2] = TComplex(Ih5Re,Ih5Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][1][0][0] = TComplex(Ih1Re,-Ih1Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][1][0][1] = TComplex(Ih23Re,0.);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][1][0][2] = TComplex(Ih6Re,Ih6Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][1][1][0] = TComplex(Ih7Re,Ih7Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][1][1][1] = TComplex(Ih8Re,Ih8Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][1][1][2] = TComplex(Ih9Re,Ih9Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][1][2][0] = TComplex(Ih10Re,Ih10Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][1][2][1] = TComplex(Ih11Re,Ih11Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][1][2][2] = TComplex(Ih12Re,Ih12Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][2][0][0] = TComplex(Ih2Re,-Ih2Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][2][0][1] = TComplex(Ih6Re,-Ih6Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][2][0][2] = TComplex(Ih25Re,0.);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][2][1][0] = TComplex(Ih10Re,-Ih10Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][2][1][1] = TComplex(Ih13Re,Ih13Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][2][1][2] = TComplex(Ih14Re,Ih14Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][2][2][0] = TComplex(Ih15Re,Ih15Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][2][2][1] = TComplex(Ih16Re,Ih16Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][0][2][2][2] = TComplex(Ih17Re,Ih17Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][0][0][0] = TComplex(Ih1Re,-Ih1Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][0][0][1] = TComplex(Ih7Re,Ih7Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][0][0][2] = TComplex(Ih10Re,Ih10Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][0][1][0] = TComplex(Ih24Re,0.);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][0][1][1] = TComplex(Ih8Re,Ih8Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][0][1][2] = TComplex(Ih11Re,Ih11Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][0][2][0] = TComplex(Ih6Re,Ih6Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][0][2][1] = TComplex(Ih9Re,Ih9Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][0][2][2] = TComplex(Ih12Re,Ih12Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][1][0][0] = TComplex(Ih3Re,-Ih3Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][1][0][1] = TComplex(Ih8Re,-Ih8Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][1][0][2] = TComplex(Ih13Re,-Ih13Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][1][1][0] = TComplex(Ih8Re,-Ih8Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][1][1][1] = TComplex(Ih27Re,0.);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][1][1][2] = TComplex(Ih18Re,Ih18Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][1][2][0] = TComplex(Ih13Re,-Ih13Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][1][2][1] = TComplex(Ih18Re,Ih18Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][1][2][2] = TComplex(Ih19Re,Ih19Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][2][0][0] = TComplex(Ih4Re,-Ih4Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][2][0][1] = TComplex(Ih9Re,-Ih9Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][2][0][2] = TComplex(Ih14Re,-Ih14Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][2][1][0] = TComplex(Ih11Re,-Ih11Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][2][1][1] = TComplex(Ih18Re,-Ih18Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][2][1][2] = TComplex(Ih28Re,0.);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][2][2][0] = TComplex(Ih16Re,-Ih16Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][2][2][1] = TComplex(Ih20Re,Ih20Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][1][2][2][2] = TComplex(Ih21Re,Ih21Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][0][0][0] = TComplex(Ih2Re,-Ih2Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][0][0][1] = TComplex(Ih10Re,-Ih10Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][0][0][2] = TComplex(Ih15Re,Ih15Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][0][1][0] = TComplex(Ih6Re,-Ih6Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][0][1][1] = TComplex(Ih13Re,Ih13Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][0][1][2] = TComplex(Ih16Re,Ih16Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][0][2][0] = TComplex(Ih26Re,0.);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][0][2][1] = TComplex(Ih14Re,Ih14Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][0][2][2] = TComplex(Ih17Re,Ih17Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][1][0][0] = TComplex(Ih4Re,-Ih4Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][1][0][1] = TComplex(Ih11Re,-Ih11Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][1][0][2] = TComplex(Ih16Re,-Ih16Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][1][1][0] = TComplex(Ih9Re,-Ih9Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][1][1][1] = TComplex(Ih18Re,-Ih18Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][1][1][2] = TComplex(Ih20Re,Ih20Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][1][2][0] = TComplex(Ih14Re,-Ih14Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][1][2][1] = TComplex(Ih29Re,0.);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][1][2][2] = TComplex(Ih21Re,Ih21Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][2][0][0] = TComplex(Ih5Re,-Ih5Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][2][0][1] = TComplex(Ih12Re,-Ih12Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][2][0][2] = TComplex(Ih17Re,-Ih17Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][2][1][0] = TComplex(Ih12Re,-Ih12Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][2][1][1] = TComplex(Ih19Re,-Ih19Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][2][1][2] = TComplex(Ih21Re,-Ih21Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][2][2][0] = TComplex(Ih17Re,-Ih17Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][2][2][1] = TComplex(Ih21Re,-Ih21Im);
   Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][2][2][2][2] = TComplex(Ih30Re,0.);

 } 


// ######################################################################################################
// P H Y S I C A L   T E R M S
// ######################################################################################################

// ---------------------------------------------------
// CP averaged wave fractions corresponding to j1j2 states.

Double_t KpiKpiSpectrumNW::wfj1j2(Int_t j1, Int_t j2) const
 {

   switch(j1) {
   case 0 :
      switch(j2) {
      case 0 : return (1.-f_VV)*f_Swave*f_SS;
      case 1 : return (1.-f_VV)*f_Swave*(1.-f_SS)*0.5*(1.+D_SVVS);
      case 2 : return (1.-f_VV)*(1.-f_Swave)*(1.-f_VTTV)*(1.-f_TT)*0.5*(1.+D_STTS);
      }
   case 1 :
      switch(j2) {
      case 0 : return (1.-f_VV)*f_Swave*(1.-f_SS)*0.5*(1.-D_SVVS);
      case 1 : return f_VV;
      case 2 : return (1.-f_VV)*(1.-f_Swave)*f_VTTV*0.5*(1.+D_VTTV);
      }
   case 2 :
      switch(j2) {
      case 0 : return (1.-f_VV)*(1.-f_Swave)*(1.-f_VTTV)*(1.-f_TT)*0.5*(1.-D_STTS);
      case 1 : return (1.-f_VV)*(1.-f_Swave)*f_VTTV*0.5*(1.-D_VTTV);
      case 2 : return (1.-f_VV)*(1.-f_Swave)*(1.-f_VTTV)*f_TT;
      }
   }
   return 0;

 }

// ---------------------------------------------------
// CP averaged polarization fractions corresponding to h_j1j2 states.

Double_t KpiKpiSpectrumNW::pfj1j2h(Int_t j1, Int_t j2, Int_t h) const
 {

   switch(j1) {
   case 1 :
      switch(j2) {
      case 1 :
         switch(h) {
         case 0 : return fL_VV;
         case 1 : return (1.-fL_VV)*xpar_VV;
         case 2 : return (1.-fL_VV)*(1.-xpar_VV);
         }
      case 2 :
         switch(h) {
         case 0 : return fL_VT;
         case 1 : return (1.-fL_VT)*xpar_VT;
         case 2 : return (1.-fL_VT)*(1.-xpar_VT);
         }
      }
   case 2 :
      switch(j2) {
      case 1 :
         switch(h) {
         case 0 : return fL_TV;
         case 1 : return (1.-fL_TV)*xpar_TV;
         case 2 : return (1.-fL_TV)*(1.-xpar_TV);
         }
      case 2 :
         switch(h) {
         case 0 : return fL_TT;
         case 1 : return (1.-fL_TT)*xpar1_TT;
         case 2 : return (1.-fL_TT)*(1.-xpar1_TT)*xperp1_TT;
         case 3 : return (1.-fL_TT)*(1.-xpar1_TT)*(1.-xperp1_TT)*xpar2_TT;
         case 4 : return (1.-fL_TT)*(1.-xpar1_TT)*(1.-xperp1_TT)*(1.-xpar2_TT);
         }
      }
   }
   return 1.;

 }

// ---------------------------------------------------
// Amplitude strong phases.

Double_t KpiKpiSpectrumNW::deltaj1j2h(Int_t j1, Int_t j2, Int_t h) const
 {

   switch(j1) {
   case 0 :
      switch(j2) {
      case 0 : return delta00;
      case 1 : return delta01;
      case 2 : return delta02;
      }
   case 1 :
      switch(j2) {
      case 0 : return delta10;
      case 1 :
         switch(h) {
         case 0 : return 0.;
         case 1 : return delta11par;
         case 2 : return delta11perp;
         }
      case 2 :
         switch(h) {
         case 0 : return delta120;
         case 1 : return delta12par;
         case 2 : return delta12perp;      
         }
      }
   case 2 :
      switch(j2) {
      case 0 : return delta20;
      case 1 :
         switch(h) {
         case 0 : return delta210;
         case 1 : return delta21par;
         case 2 : return delta21perp;
         }
      case 2 :
         switch(h) {
         case 0 : return delta220;
         case 1 : return delta22par;
         case 2 : return delta22perp;
         case 3 : return delta22par2;
         case 4 : return delta22perp2;
         }
      }
   }
   return 0.;

 }

// ---------------------------------------------------
// Direct CP violation asymmetries.

Double_t KpiKpiSpectrumNW::DCPj1j2(Int_t j1, Int_t j2) const
 {

   switch(j1) {
   case 0 :
      switch(j2) {
      case 0 : return DCP_SS;
      case 1 : return DCP_SV;
      case 2 : return DCP_ST;
      }
   case 1 :
      switch(j2) {
      case 0 : return DCP_VS;
      case 1 : return DCP_VV;
      case 2 : return DCP_VT;
      }
   case 2 :
      switch(j2) {
      case 0 : return DCP_TS;
      case 1 : return DCP_TV;
      case 2 : return DCP_TT;
      }
   }
   return 0;

 }

// ---------------------------------------------------
// Difference between the phi_s phase for each channel and the averaged value for this quantity.

Double_t KpiKpiSpectrumNW::dphij1j2(Int_t j1, Int_t j2) const
 {

   switch(j1) {
   case 0 :
      switch(j2) {
      case 0 : return dphi_SS;
      case 1 : return dphi_SV;
      case 2 : return dphi_ST;
      }
   case 1 :
      switch(j2) {
      case 0 : return dphi_VS;
      case 1 :
         if (f_VV != 0) {return -1./f_VV*(wfj1j2(0,0)*dphi_SS+wfj1j2(0,1)*dphi_SV+wfj1j2(0,2)*dphi_ST+wfj1j2(1,0)*dphi_VS+wfj1j2(1,2)*dphi_VT+wfj1j2(2,0)*dphi_TS+wfj1j2(2,1)*dphi_TV+wfj1j2(2,2)*dphi_TT);}
         else {return 0.;}
      case 2 : return dphi_VT;
      }
   case 2 :
      switch(j2) {
      case 0 : return dphi_TS;
      case 1 : return dphi_TV;
      case 2 : return dphi_TT;
      }
   }
   return 0;

 }

// ---------------------------------------------------
// Sign factor due to helicity.

Double_t KpiKpiSpectrumNW::etah(Int_t h) const
 {

   if ((h == 2) or (h == 4)) {return -1.;}
   else {return 1.;}

 }

// ---------------------------------------------------
// Sign factor due to helicity and angular momenta.

Double_t KpiKpiSpectrumNW::etaj1j2h(Int_t j1, Int_t j2, Int_t h) const
 {

   return pow(-1.,j1+j2)*etah(h);

 }

// ---------------------------------------------------
// Complex amplitudes.

TComplex KpiKpiSpectrumNW::Aj1j2h(Int_t j1, Int_t j2, Int_t h) const
 {

   return TComplex(sqrt(wfj1j2(j1,j2)*pfj1j2h(j1,j2,h)*(1.+DCPj1j2(j1,j2))),deltaj1j2h(j1,j2,h)+0.5*(phis+dphij1j2(j1,j2)),1);

 }

// ---------------------------------------------------
// CP conjugated complex amplitudes.

TComplex KpiKpiSpectrumNW::Abarj1j2h(Int_t j1, Int_t j2, Int_t h) const
 {

   return etaj1j2h(j2,j1,h)*TComplex(sqrt(wfj1j2(j2,j1)*pfj1j2h(j2,j1,h)*(1.-DCPj1j2(j2,j1))),deltaj1j2h(j2,j1,h)-0.5*(phis+dphij1j2(j2,j1)),1);

 }

// ---------------------------------------------------
// Term AA* + AbarAbar*.

TComplex KpiKpiSpectrumNW::M_Average(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const
 {

   return Aj1j2h_temp[j1][j2][h]*TComplex::Conjugate(Aj1j2h_temp[j1p][j2p][hp])+Abarj1j2h_temp[j1][j2][h]*TComplex::Conjugate(Abarj1j2h_temp[j1p][j2p][hp]);

 }

// ---------------------------------------------------
// Term AAbar* + AbarA* = 2 Re(AAbar*).

TComplex KpiKpiSpectrumNW::M_DeltaGamma(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const
 {

   return Aj1j2h_temp[j1][j2][h]*TComplex::Conjugate(Abarj1j2h_temp[j1p][j2p][hp])+Abarj1j2h_temp[j1][j2][h]*TComplex::Conjugate(Aj1j2h_temp[j1p][j2p][hp]);

 }

// ---------------------------------------------------
// Term AA* - AbarAbar*.

TComplex KpiKpiSpectrumNW::M_DirCP(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const
 {

   return Aj1j2h_temp[j1][j2][h]*TComplex::Conjugate(Aj1j2h_temp[j1p][j2p][hp])-Abarj1j2h_temp[j1][j2][h]*TComplex::Conjugate(Abarj1j2h_temp[j1p][j2p][hp]);

 }

// ---------------------------------------------------
// Term 1/i (AAbar* - AbarA*) = 2 Im(AAbar*).

TComplex KpiKpiSpectrumNW::M_MixCP(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const
 {

   return TComplex(0.,-1.)*(Aj1j2h_temp[j1][j2][h]*TComplex::Conjugate(Abarj1j2h_temp[j1p][j2p][hp])-Abarj1j2h_temp[j1][j2][h]*TComplex::Conjugate(Aj1j2h_temp[j1p][j2p][hp]));

 }

// ######################################################################################################
// F L A V O U R   T A G G I N G   T E R M S
// ######################################################################################################

// ---------------------------------------------------
// Mistag probability for the events tagged as q_SSK = 1.

Double_t KpiKpiSpectrumNW::omega_SSK(Double_t eta) const
 {

   return (p0metac_tag_SSK+etac_tag_SSK+Dp0half_tag_SSK)+(p1_tag_SSK+Dp1half_tag_SSK)*(eta-etac_tag_SSK);

 }

// ---------------------------------------------------
// Mistag probability for the events tagged as q_SSK = -1.

Double_t KpiKpiSpectrumNW::omegabar_SSK(Double_t eta) const
 {

   return (p0metac_tag_SSK+etac_tag_SSK-Dp0half_tag_SSK)+(p1_tag_SSK-Dp1half_tag_SSK)*(eta-etac_tag_SSK);

 }

// ---------------------------------------------------
// Mistag probability for the events tagged as q_OS = 1.

Double_t KpiKpiSpectrumNW::omega_OS(Double_t eta) const
 {

   return (p0metac_tag_OS+etac_tag_OS+Dp0half_tag_OS)+(p1_tag_OS+Dp1half_tag_OS)*(eta-etac_tag_OS);

 }

// ---------------------------------------------------
// Mistag probability for the events tagged as q_OS = -1.

Double_t KpiKpiSpectrumNW::omegabar_OS(Double_t eta) const
 {

   return (p0metac_tag_OS+etac_tag_OS-Dp0half_tag_OS)+(p1_tag_OS-Dp1half_tag_OS)*(eta-etac_tag_OS);

 }

// ---------------------------------------------------
// Pseudo-probability asigned to a Bs-like event due to tagging.

Double_t KpiKpiSpectrumNW::P_Bs(Int_t q1, Int_t q2, Double_t eta1, Double_t eta2) const
 {

   return (1.+0.5*q1*(1.-q1-2.*omega_SSK(eta1)))*(1.+0.5*q2*(1.-q2-2.*omega_OS(eta2)));

 }

// ---------------------------------------------------
// Pseudo-probability asigned to a Bsbar-like event due to tagging.

Double_t KpiKpiSpectrumNW::P_Bsbar(Int_t q1, Int_t q2, Double_t eta1, Double_t eta2) const
 {

   return (1.-0.5*q1*(1.+q1-2.*omegabar_SSK(eta1)))*(1.-0.5*q2*(1.+q2-2.*omegabar_OS(eta2)));

 }

// ---------------------------------------------------
// CP averaged normalization factor due to tagging and DCP_prod.

Double_t KpiKpiSpectrumNW::zeta(Int_t q1, Int_t q2, Double_t eta1, Double_t eta2) const
 {

   return 0.5*((1.+DCP_prod[int(wide_window)])*P_Bs(q1,q2,eta1,eta2)+(1.-DCP_prod[int(wide_window)])*P_Bsbar(q1,q2,eta1,eta2));

 }

// ---------------------------------------------------
// Combined CP asymmetry at t=0, associated to tagging and DCP_prod.

Double_t KpiKpiSpectrumNW::DCP_tzero(Int_t q1, Int_t q2, Double_t eta1, Double_t eta2) const
 {

   return 0.5/zeta(q1,q2,eta1,eta2)*((1.+DCP_prod[int(wide_window)])*P_Bs(q1,q2,eta1,eta2)-(1.-DCP_prod[int(wide_window)])*P_Bsbar(q1,q2,eta1,eta2));

 }

// ######################################################################################################
// T I M E   D E P E N D E N T   T E R M S
// ######################################################################################################

// ---------------------------------------------------
// Width of a gaussian used in the per event time resolution model.

Double_t KpiKpiSpectrumNW::sigma_tres(Double_t tau_err, Int_t g_i) const 
 { 

   if (g_i == 1) {return (TRes.q0A(year_opt)+(TRes.q1A(year_opt)+TRes.q2A(year_opt)*(tau_err-TRes.mean(year_opt)))*tau_err)-sqrt(TRes.f1(year_opt)/(1.-TRes.f1(year_opt)))*(TRes.q0B(year_opt)+(TRes.q1B(year_opt)+TRes.q2B(year_opt)*(tau_err-TRes.mean(year_opt)))*tau_err);}
   else if (g_i == 2) {return (TRes.q0A(year_opt)+(TRes.q1A(year_opt)+TRes.q2A(year_opt)*(tau_err-TRes.mean(year_opt)))*tau_err)+sqrt((1.-TRes.f1(year_opt))/TRes.f1(year_opt))*(TRes.q0B(year_opt)+(TRes.q1B(year_opt)+TRes.q2B(year_opt)*(tau_err-TRes.mean(year_opt)))*tau_err);}

   return 0.;

 }

// ---------------------------------------------------
// Average gaussian width used in the per event time resolution model as a time range separator.

Double_t KpiKpiSpectrumNW::sigma_ref(Double_t tau_err) const 
 { 

   return TRes.f1(year_opt)*sigma_tres(tau_err,1)+(1.-TRes.f1(year_opt))*sigma_tres(tau_err,2);

 }

// ---------------------------------------------------
// Width of a gaussian used in the effective time resolution model.

Double_t KpiKpiSpectrumNW::sigma_tres_eff(Int_t g_i) const 
 { 

   if (g_i == 1) {return TReseff.sigma1(year_opt);}
   else if (g_i == 2) {return TReseff.sigma2(year_opt);}

   return 0.;

 }

// ---------------------------------------------------
// Average gaussian width used in the effective time resolution model as a time range separator.

Double_t KpiKpiSpectrumNW::sigma_ref_eff() const 
 { 

   return TReseff.f1(year_opt)*sigma_tres_eff(1)+(1.-TReseff.f1(year_opt))*sigma_tres_eff(2);

 }

// ---------------------------------------------------
// Real variable used in the time resolution model.

Double_t KpiKpiSpectrumNW::x_tres(Double_t tau, Double_t tau_err, Int_t g_i) const
 { 

   return 1./(sqrt(2.)*sigma_tres(tau_err,g_i))*(tau-TRes.off(year_opt)-gamma_Bs_freq*sigma_tres(tau_err,g_i)*sigma_tres(tau_err,g_i));

 }

// ---------------------------------------------------
// Real variable used in the time resolution model.

Double_t KpiKpiSpectrumNW::x0_tres(Double_t tau_err, Int_t g_i) const
 { 

   return delta_gamma_freq*sigma_tres(tau_err,g_i)/(2.*sqrt(2.));

 }

// ---------------------------------------------------
// Complex variable used in the time resolution model.

std::complex<Double_t> KpiKpiSpectrumNW::z_tres(Double_t tau, Double_t tau_err, Int_t g_i) const
 { 

   return 1./(sqrt(2.)*sigma_tres(tau_err,g_i))*std::complex<Double_t>(delta_m_freq*sigma_tres(tau_err,g_i)*sigma_tres(tau_err,g_i),-tau+TRes.off(year_opt)+gamma_Bs_freq*sigma_tres(tau_err,g_i)*sigma_tres(tau_err,g_i));

 }

// ---------------------------------------------------
// Gaussian function for time resolution.

Double_t KpiKpiSpectrumNW::gaus_tres(Double_t tau, Double_t tau_err, Int_t g_i) const
 { 

   return exp(-(tau-TRes.off(year_opt))*(tau-TRes.off(year_opt))/2./sigma_tres(tau_err,g_i)/sigma_tres(tau_err,g_i));

 }

// ---------------------------------------------------
// Real variable used in the effective time resolution model.

Double_t KpiKpiSpectrumNW::x_tres_eff(Double_t tau, Int_t g_i) const
 { 

   return 1./(sqrt(2.)*sigma_tres_eff(g_i))*(tau-TReseff.off(year_opt)-gamma_Bs_freq*sigma_tres_eff(g_i)*sigma_tres_eff(g_i));

 }

// ---------------------------------------------------
// Real variable used in the effective time resolution model.

Double_t KpiKpiSpectrumNW::x0_tres_eff(Int_t g_i) const
 { 

   return delta_gamma_freq*sigma_tres_eff(g_i)/(2.*sqrt(2.));

 }

// ---------------------------------------------------
// Complex variable used in the effective time resolution model.

std::complex<Double_t> KpiKpiSpectrumNW::z_tres_eff(Double_t tau, Int_t g_i) const
 {

   return 1./(sqrt(2.)*sigma_tres_eff(g_i))*std::complex<Double_t>(delta_m_freq*sigma_tres_eff(g_i)*sigma_tres_eff(g_i),-tau+TReseff.off(year_opt)+gamma_Bs_freq*sigma_tres_eff(g_i)*sigma_tres_eff(g_i));

 }

// ---------------------------------------------------
// Gaussian function for effective time resolution.

Double_t KpiKpiSpectrumNW::gaus_tres_eff(Double_t tau, Int_t g_i) const
 { 

   return exp(-(tau-TReseff.off(year_opt))*(tau-TReseff.off(year_opt))/2./sigma_tres_eff(g_i)/sigma_tres_eff(g_i));

 }

// ---------------------------------------------------
// Complementary error function.

Double_t KpiKpiSpectrumNW::erfc(Double_t x) const 
 { 
   
   return RooMath::erfc(x);

 }

// ---------------------------------------------------
// Real part of the Faddeeva function, used in the resolution model.

Double_t KpiKpiSpectrumNW::Re_w(std::complex<Double_t> z) const 
 { 
   
   return (RooMath::faddeeva(z)).real();

 }

// ---------------------------------------------------
// Imaginary part of the Faddeeva function, used in the resolution model.

Double_t KpiKpiSpectrumNW::Im_w(std::complex<Double_t> z) const 
 { 
   
   return (RooMath::faddeeva(z)).imag();

 }

// ---------------------------------------------------
// cosh time dependent term, ideal model.

Double_t KpiKpiSpectrumNW::T_cosh_ideal(Double_t tau) const
 {
   
   return exp(-gamma_Bs_freq*tau)*cosh(0.5*delta_gamma_freq*tau);

 }

// ---------------------------------------------------
// sinh time dependent term, ideal model.

Double_t KpiKpiSpectrumNW::T_sinh_ideal(Double_t tau) const
 {
   
   return exp(-gamma_Bs_freq*tau)*sinh(0.5*delta_gamma_freq*tau);

 }

// ---------------------------------------------------
// cos time dependent term, ideal model.

Double_t KpiKpiSpectrumNW::T_cos_ideal(Double_t tau) const
 {
   
   return exp(-gamma_Bs_freq*tau)*cos(delta_m_freq*tau);

 }

// ---------------------------------------------------
// sin time dependent term, ideal model.

Double_t KpiKpiSpectrumNW::T_sin_ideal(Double_t tau) const
 {
   
   return exp(-gamma_Bs_freq*tau)*sin(delta_m_freq*tau);

 }

// ---------------------------------------------------
// cosh time dependent term, resolution included, exact solution.

Double_t KpiKpiSpectrumNW::T_cosh_resexact(Double_t tau, Double_t tau_err) const
 {
   
   return 1./4.*(TRes.f1(year_opt)*gaus_tres(tau,tau_err,1)*(exp((x_tres(tau,tau_err,1)+x0_tres(tau_err,1))*(x_tres(tau,tau_err,1)+x0_tres(tau_err,1)))*erfc(-x_tres(tau,tau_err,1)-x0_tres(tau_err,1))+exp((x_tres(tau,tau_err,1)-x0_tres(tau_err,1))*(x_tres(tau,tau_err,1)-x0_tres(tau_err,1)))*erfc(-x_tres(tau,tau_err,1)+x0_tres(tau_err,1)))+(1.-TRes.f1(year_opt))*gaus_tres(tau,tau_err,2)*(exp((x_tres(tau,tau_err,2)+x0_tres(tau_err,2))*(x_tres(tau,tau_err,2)+x0_tres(tau_err,2)))*erfc(-x_tres(tau,tau_err,2)-x0_tres(tau_err,2))+exp((x_tres(tau,tau_err,2)-x0_tres(tau_err,2))*(x_tres(tau,tau_err,2)-x0_tres(tau_err,2)))*erfc(-x_tres(tau,tau_err,2)+x0_tres(tau_err,2))));

 }

// ---------------------------------------------------
// sinh time dependent term, resolution included, exact solution.

Double_t KpiKpiSpectrumNW::T_sinh_resexact(Double_t tau, Double_t tau_err) const
 {
   
   return 1./4.*(TRes.f1(year_opt)*gaus_tres(tau,tau_err,1)*(exp((x_tres(tau,tau_err,1)+x0_tres(tau_err,1))*(x_tres(tau,tau_err,1)+x0_tres(tau_err,1)))*erfc(-x_tres(tau,tau_err,1)-x0_tres(tau_err,1))-exp((x_tres(tau,tau_err,1)-x0_tres(tau_err,1))*(x_tres(tau,tau_err,1)-x0_tres(tau_err,1)))*erfc(-x_tres(tau,tau_err,1)+x0_tres(tau_err,1)))+(1.-TRes.f1(year_opt))*gaus_tres(tau,tau_err,2)*(exp((x_tres(tau,tau_err,2)+x0_tres(tau_err,2))*(x_tres(tau,tau_err,2)+x0_tres(tau_err,2)))*erfc(-x_tres(tau,tau_err,2)-x0_tres(tau_err,2))-exp((x_tres(tau,tau_err,2)-x0_tres(tau_err,2))*(x_tres(tau,tau_err,2)-x0_tres(tau_err,2)))*erfc(-x_tres(tau,tau_err,2)+x0_tres(tau_err,2))));

 }

// ---------------------------------------------------
// cos time dependent term, resolution included, exact solution.

Double_t KpiKpiSpectrumNW::T_cos_resexact(Double_t tau, Double_t tau_err) const
 {
   
   return 1./2.*(TRes.f1(year_opt)*gaus_tres(tau,tau_err,1)*Re_w(z_tres(tau,tau_err,1))+(1.-TRes.f1(year_opt))*gaus_tres(tau,tau_err,2)*Re_w(z_tres(tau,tau_err,2)));

 }

// ---------------------------------------------------
// sin time dependent term, resolution included, exact solution.

Double_t KpiKpiSpectrumNW::T_sin_resexact(Double_t tau, Double_t tau_err) const
 {
   
   return 1./2.*(TRes.f1(year_opt)*gaus_tres(tau,tau_err,1)*Im_w(z_tres(tau,tau_err,1))+(1.-TRes.f1(year_opt))*gaus_tres(tau,tau_err,2)*Im_w(z_tres(tau,tau_err,2)));

 }

// ---------------------------------------------------
// cosh time dependent term, resolution included, approximated solution.

Double_t KpiKpiSpectrumNW::T_cosh_resapprox(Double_t tau, Double_t tau_err) const
 {
   
   return (TRes.f1(year_opt)*exp(-gamma_Bs_freq*(tau-TRes.off(year_opt))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres(tau_err,1)*sigma_tres(tau_err,1)+1./8.*delta_gamma_freq*delta_gamma_freq*sigma_tres(tau_err,1)*sigma_tres(tau_err,1))*cosh(0.5*delta_gamma_freq*(tau-TRes.off(year_opt))-0.5*gamma_Bs_freq*delta_gamma_freq*sigma_tres(tau_err,1)*sigma_tres(tau_err,1))+(1.-TRes.f1(year_opt))*exp(-gamma_Bs_freq*(tau-TRes.off(year_opt))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres(tau_err,2)*sigma_tres(tau_err,2)+1./8.*delta_gamma_freq*delta_gamma_freq*sigma_tres(tau_err,2)*sigma_tres(tau_err,2))*cosh(0.5*delta_gamma_freq*(tau-TRes.off(year_opt))-0.5*gamma_Bs_freq*delta_gamma_freq*sigma_tres(tau_err,2)*sigma_tres(tau_err,2)));

 }

// ---------------------------------------------------
// sinh time dependent term, resolution included, approximated solution.

Double_t KpiKpiSpectrumNW::T_sinh_resapprox(Double_t tau, Double_t tau_err) const
 {
   
   return (TRes.f1(year_opt)*exp(-gamma_Bs_freq*(tau-TRes.off(year_opt))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres(tau_err,1)*sigma_tres(tau_err,1)+1./8.*delta_gamma_freq*delta_gamma_freq*sigma_tres(tau_err,1)*sigma_tres(tau_err,1))*sinh(0.5*delta_gamma_freq*(tau-TRes.off(year_opt))-0.5*gamma_Bs_freq*delta_gamma_freq*sigma_tres(tau_err,1)*sigma_tres(tau_err,1))+(1.-TRes.f1(year_opt))*exp(-gamma_Bs_freq*(tau-TRes.off(year_opt))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres(tau_err,2)*sigma_tres(tau_err,2)+1./8.*delta_gamma_freq*delta_gamma_freq*sigma_tres(tau_err,2)*sigma_tres(tau_err,2))*sinh(0.5*delta_gamma_freq*(tau-TRes.off(year_opt))-0.5*gamma_Bs_freq*delta_gamma_freq*sigma_tres(tau_err,2)*sigma_tres(tau_err,2)));

 }

// ---------------------------------------------------
// cos time dependent term, resolution included, approximated solution.

Double_t KpiKpiSpectrumNW::T_cos_resapprox(Double_t tau, Double_t tau_err) const
 {
   
   return (TRes.f1(year_opt)*exp(-gamma_Bs_freq*(tau-TRes.off(year_opt))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres(tau_err,1)*sigma_tres(tau_err,1)-0.5*delta_m_freq*delta_m_freq*sigma_tres(tau_err,1)*sigma_tres(tau_err,1))*cos(delta_m_freq*(tau-TRes.off(year_opt))-gamma_Bs_freq*delta_m_freq*sigma_tres(tau_err,1)*sigma_tres(tau_err,1))+(1.-TRes.f1(year_opt))*exp(-gamma_Bs_freq*(tau-TRes.off(year_opt))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres(tau_err,2)*sigma_tres(tau_err,2)-0.5*delta_m_freq*delta_m_freq*sigma_tres(tau_err,2)*sigma_tres(tau_err,2))*cos(delta_m_freq*(tau-TRes.off(year_opt))-gamma_Bs_freq*delta_m_freq*sigma_tres(tau_err,2)*sigma_tres(tau_err,2)));

 }

// ---------------------------------------------------
// sin time dependent term, resolution included, approximated solution.

Double_t KpiKpiSpectrumNW::T_sin_resapprox(Double_t tau, Double_t tau_err) const
 {
   
   return (TRes.f1(year_opt)*exp(-gamma_Bs_freq*(tau-TRes.off(year_opt))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres(tau_err,1)*sigma_tres(tau_err,1)-0.5*delta_m_freq*delta_m_freq*sigma_tres(tau_err,1)*sigma_tres(tau_err,1))*sin(delta_m_freq*(tau-TRes.off(year_opt))-gamma_Bs_freq*delta_m_freq*sigma_tres(tau_err,1)*sigma_tres(tau_err,1))+(1.-TRes.f1(year_opt))*exp(-gamma_Bs_freq*(tau-TRes.off(year_opt))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres(tau_err,2)*sigma_tres(tau_err,2)-0.5*delta_m_freq*delta_m_freq*sigma_tres(tau_err,2)*sigma_tres(tau_err,2))*sin(delta_m_freq*(tau-TRes.off(year_opt))-gamma_Bs_freq*delta_m_freq*sigma_tres(tau_err,2)*sigma_tres(tau_err,2)));

 }

// ---------------------------------------------------
// cosh time dependent term.

Double_t KpiKpiSpectrumNW::T_cosh(Double_t tau, Double_t tau_err) const
 {
   
   if (inftres == 1) {return T_cosh_ideal(tau);}
   else if ((inftres == 0) && ((tau-TRes.off(year_opt)) <= 10*sigma_ref(tau_err))) {return T_cosh_resexact(tau,tau_err);}
   else {return T_cosh_resapprox(tau,tau_err);}

 }

// ---------------------------------------------------
// sinh time dependent term.

Double_t KpiKpiSpectrumNW::T_sinh(Double_t tau, Double_t tau_err) const
 {
   
   if (inftres == 1) {return T_sinh_ideal(tau);}
   else if ((inftres == 0) && ((tau-TRes.off(year_opt)) <= 10*sigma_ref(tau_err))) {return T_sinh_resexact(tau,tau_err);}
   else {return T_sinh_resapprox(tau,tau_err);}

 }

// ---------------------------------------------------
// cos time dependent term.

Double_t KpiKpiSpectrumNW::T_cos(Double_t tau, Double_t tau_err) const
 {
   
   if (inftres == 1) {return T_cos_ideal(tau);}
   else if ((inftres == 0) && ((tau-TRes.off(year_opt)) <= 10*sigma_ref(tau_err))) {return T_cos_resexact(tau,tau_err);}
   else {return T_cos_resapprox(tau,tau_err);}

 }

// ---------------------------------------------------
// sin time dependent term.

Double_t KpiKpiSpectrumNW::T_sin(Double_t tau, Double_t tau_err) const
 {
   
   if (inftres == 1) {return T_sin_ideal(tau);}
   else if ((inftres == 0) && ((tau-TRes.off(year_opt)) <= 10*sigma_ref(tau_err))) {return T_sin_resexact(tau,tau_err);}
   else {return T_sin_resapprox(tau,tau_err);}

 }

// ---------------------------------------------------
// cosh time dependent term, effective resolution included, exact solution.

Double_t KpiKpiSpectrumNW::T_cosh_resexact_eff(Double_t tau) const
 {
   
   return 1./4.*(TReseff.f1(year_opt)*gaus_tres_eff(tau,1)*(exp((x_tres_eff(tau,1)+x0_tres_eff(1))*(x_tres_eff(tau,1)+x0_tres_eff(1)))*erfc(-x_tres_eff(tau,1)-x0_tres_eff(1))+exp((x_tres_eff(tau,1)-x0_tres_eff(1))*(x_tres_eff(tau,1)-x0_tres_eff(1)))*erfc(-x_tres_eff(tau,1)+x0_tres_eff(1)))+(1.-TReseff.f1(year_opt))*gaus_tres_eff(tau,2)*(exp((x_tres_eff(tau,2)+x0_tres_eff(2))*(x_tres_eff(tau,2)+x0_tres_eff(2)))*erfc(-x_tres_eff(tau,2)-x0_tres_eff(2))+exp((x_tres_eff(tau,2)-x0_tres_eff(2))*(x_tres_eff(tau,2)-x0_tres_eff(2)))*erfc(-x_tres_eff(tau,2)+x0_tres_eff(2))));

 }

// ---------------------------------------------------
// sinh time dependent term, effective resolution included, exact solution.

Double_t KpiKpiSpectrumNW::T_sinh_resexact_eff(Double_t tau) const
 {
   
   return 1./4.*(TReseff.f1(year_opt)*gaus_tres_eff(tau,1)*(exp((x_tres_eff(tau,1)+x0_tres_eff(1))*(x_tres_eff(tau,1)+x0_tres_eff(1)))*erfc(-x_tres_eff(tau,1)-x0_tres_eff(1))-exp((x_tres_eff(tau,1)-x0_tres_eff(1))*(x_tres_eff(tau,1)-x0_tres_eff(1)))*erfc(-x_tres_eff(tau,1)+x0_tres_eff(1)))+(1.-TReseff.f1(year_opt))*gaus_tres_eff(tau,2)*(exp((x_tres_eff(tau,2)+x0_tres_eff(2))*(x_tres_eff(tau,2)+x0_tres_eff(2)))*erfc(-x_tres_eff(tau,2)-x0_tres_eff(2))-exp((x_tres_eff(tau,2)-x0_tres_eff(2))*(x_tres_eff(tau,2)-x0_tres_eff(2)))*erfc(-x_tres_eff(tau,2)+x0_tres_eff(2))));

 }

// ---------------------------------------------------
// cos time dependent term, effective resolution included, exact solution.

Double_t KpiKpiSpectrumNW::T_cos_resexact_eff(Double_t tau) const
 {
   
   return 1./2.*(TReseff.f1(year_opt)*gaus_tres_eff(tau,1)*Re_w(z_tres_eff(tau,1))+(1.-TReseff.f1(year_opt))*gaus_tres_eff(tau,2)*Re_w(z_tres_eff(tau,2)));

 }

// ---------------------------------------------------
// sin time dependent term, effective resolution included, exact solution.

Double_t KpiKpiSpectrumNW::T_sin_resexact_eff(Double_t tau) const
 {
   
   return 1./2.*(TReseff.f1(year_opt)*gaus_tres_eff(tau,1)*Im_w(z_tres_eff(tau,1))+(1.-TReseff.f1(year_opt))*gaus_tres_eff(tau,2)*Im_w(z_tres_eff(tau,2)));

 }

// ---------------------------------------------------
// cosh time dependent term, effective resolution included, approximated solution.

Double_t KpiKpiSpectrumNW::T_cosh_resapprox_eff(Double_t tau) const
 {
   
   return (TReseff.f1(year_opt)*exp(-gamma_Bs_freq*(tau-TReseff.off(year_opt))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1)+1./8.*delta_gamma_freq*delta_gamma_freq*sigma_tres_eff(1)*sigma_tres_eff(1))*cosh(0.5*delta_gamma_freq*(tau-TReseff.off(year_opt))-0.5*gamma_Bs_freq*delta_gamma_freq*sigma_tres_eff(1)*sigma_tres_eff(1))+(1.-TReseff.f1(year_opt))*exp(-gamma_Bs_freq*(tau-TReseff.off(year_opt))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2)+1./8.*delta_gamma_freq*delta_gamma_freq*sigma_tres_eff(2)*sigma_tres_eff(2))*cosh(0.5*delta_gamma_freq*(tau-TReseff.off(year_opt))-0.5*gamma_Bs_freq*delta_gamma_freq*sigma_tres_eff(2)*sigma_tres_eff(2)));

 }

// ---------------------------------------------------
// sinh time dependent term, effective resolution included, approximated solution.

Double_t KpiKpiSpectrumNW::T_sinh_resapprox_eff(Double_t tau) const
 {
   
   return (TReseff.f1(year_opt)*exp(-gamma_Bs_freq*(tau-TReseff.off(year_opt))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1)+1./8.*delta_gamma_freq*delta_gamma_freq*sigma_tres_eff(1)*sigma_tres_eff(1))*sinh(0.5*delta_gamma_freq*(tau-TReseff.off(year_opt))-0.5*gamma_Bs_freq*delta_gamma_freq*sigma_tres_eff(1)*sigma_tres_eff(1))+(1.-TReseff.f1(year_opt))*exp(-gamma_Bs_freq*(tau-TReseff.off(year_opt))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2)+1./8.*delta_gamma_freq*delta_gamma_freq*sigma_tres_eff(2)*sigma_tres_eff(2))*sinh(0.5*delta_gamma_freq*(tau-TReseff.off(year_opt))-0.5*gamma_Bs_freq*delta_gamma_freq*sigma_tres_eff(2)*sigma_tres_eff(2)));

 }

// ---------------------------------------------------
// cos time dependent term, effective resolution included, approximated solution.

Double_t KpiKpiSpectrumNW::T_cos_resapprox_eff(Double_t tau) const
 {
   
   return (TReseff.f1(year_opt)*exp(-gamma_Bs_freq*(tau-TReseff.off(year_opt))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1)-0.5*delta_m_freq*delta_m_freq*sigma_tres_eff(1)*sigma_tres_eff(1))*cos(delta_m_freq*(tau-TReseff.off(year_opt))-gamma_Bs_freq*delta_m_freq*sigma_tres_eff(1)*sigma_tres_eff(1))+(1.-TReseff.f1(year_opt))*exp(-gamma_Bs_freq*(tau-TReseff.off(year_opt))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2)-0.5*delta_m_freq*delta_m_freq*sigma_tres_eff(2)*sigma_tres_eff(2))*cos(delta_m_freq*(tau-TReseff.off(year_opt))-gamma_Bs_freq*delta_m_freq*sigma_tres_eff(2)*sigma_tres_eff(2)));

 }

// ---------------------------------------------------
// sin time dependent term, effective resolution included, approximated solution.

Double_t KpiKpiSpectrumNW::T_sin_resapprox_eff(Double_t tau) const
 {
   
   return (TReseff.f1(year_opt)*exp(-gamma_Bs_freq*(tau-TReseff.off(year_opt))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1)-0.5*delta_m_freq*delta_m_freq*sigma_tres_eff(1)*sigma_tres_eff(1))*sin(delta_m_freq*(tau-TReseff.off(year_opt))-gamma_Bs_freq*delta_m_freq*sigma_tres_eff(1)*sigma_tres_eff(1))+(1.-TReseff.f1(year_opt))*exp(-gamma_Bs_freq*(tau-TReseff.off(year_opt))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2)-0.5*delta_m_freq*delta_m_freq*sigma_tres_eff(2)*sigma_tres_eff(2))*sin(delta_m_freq*(tau-TReseff.off(year_opt))-gamma_Bs_freq*delta_m_freq*sigma_tres_eff(2)*sigma_tres_eff(2)));

 }

// ---------------------------------------------------
// cosh time dependent term, effective resolution.

Double_t KpiKpiSpectrumNW::T_cosh_eff(Double_t tau) const
 {
   
   if (inftres == 1) {return T_cosh_ideal(tau);}
   else if ((inftres == 0) && ((tau-TReseff.off(year_opt)) <= 10*sigma_ref_eff())) {return T_cosh_resexact_eff(tau);}
   else {return T_cosh_resapprox_eff(tau);}

 }

// ---------------------------------------------------
// sinh time dependent term, effective resolution.

Double_t KpiKpiSpectrumNW::T_sinh_eff(Double_t tau) const
 {
   
   if (inftres == 1) {return T_sinh_ideal(tau);}
   else if ((inftres == 0) && ((tau-TReseff.off(year_opt)) <= 10*sigma_ref_eff())) {return T_sinh_resexact_eff(tau);}
   else {return T_sinh_resapprox_eff(tau);}

 }

// ---------------------------------------------------
// cos time dependent term, effective resolution.

Double_t KpiKpiSpectrumNW::T_cos_eff(Double_t tau) const
 {
   
   if (inftres == 1) {return T_cos_ideal(tau);}
   else if ((inftres == 0) && ((tau-TReseff.off(year_opt)) <= 10*sigma_ref_eff())) {return T_cos_resexact_eff(tau);}
   else {return T_cos_resapprox_eff(tau);}

 }

// ---------------------------------------------------
// sin time dependent term, effective resolution.

Double_t KpiKpiSpectrumNW::T_sin_eff(Double_t tau) const
 {
   
   if (inftres == 1) {return T_sin_ideal(tau);}
   else if ((inftres == 0) && ((tau-TReseff.off(year_opt)) <= 10*sigma_ref_eff())) {return T_sin_resexact_eff(tau);}
   else {return T_sin_resapprox_eff(tau);}

 }

// ---------------------------------------------------
// Time dependent functions.

TComplex KpiKpiSpectrumNW::Tj1j2hj1pj2php(Double_t tau, Double_t tau_err, Int_t q1, Int_t q2, Double_t eta1, Double_t eta2, Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const
 {

   return zeta_temp*((T_cosh_temp*M_Average(j1,j2,h,j1p,j2p,hp)-T_sinh_temp*M_DeltaGamma(j1,j2,h,j1p,j2p,hp))+DCP_tzero_temp*(T_cos_temp*M_DirCP(j1,j2,h,j1p,j2p,hp)+T_sin_temp*M_MixCP(j1,j2,h,j1p,j2p,hp)));

 }

// ---------------------------------------------------
// Time dependent functions, effective resolution, without tagging.

TComplex KpiKpiSpectrumNW::Teffj1j2hj1pj2php(Double_t tau, Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const
 {

   return (T_cosh_eff(tau)*M_Average(j1,j2,h,j1p,j2p,hp)-T_sinh_eff(tau)*M_DeltaGamma(j1,j2,h,j1p,j2p,hp))+DCP_prod[int(wide_window)]*(T_cos_eff(tau)*M_DirCP(j1,j2,h,j1p,j2p,hp)+T_sin_eff(tau)*M_MixCP(j1,j2,h,j1p,j2p,hp));

 }

// ---------------------------------------------------
// Integral of the cosh time dependent term in a bin, effective resolution included, approximated solution.

Double_t KpiKpiSpectrumNW::IT_cosh_resapprox_eff_bin(Double_t tau1, Double_t tau2) const
 {
   
   return ((0.5*delta_gamma_freq*TReseff.f1(year_opt)*exp(sigma_tres_eff(1)*sigma_tres_eff(1)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*sinh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1) + 0.5*TReseff.off(year_opt) - 0.5*tau1)) - 0.5*delta_gamma_freq*TReseff.f1(year_opt)*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*sinh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + 0.5*TReseff.off(year_opt) - 0.5*tau1)) + 0.5*delta_gamma_freq*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*sinh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + 0.5*TReseff.off(year_opt) - 0.5*tau1)) - 1.0*TReseff.f1(year_opt)*gamma_Bs_freq*exp(sigma_tres_eff(1)*sigma_tres_eff(1)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*cosh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1) + 0.5*TReseff.off(year_opt) - 0.5*tau1)) + 1.0*TReseff.f1(year_opt)*gamma_Bs_freq*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*cosh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + 0.5*TReseff.off(year_opt) - 0.5*tau1)) - 1.0*gamma_Bs_freq*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*cosh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + 0.5*TReseff.off(year_opt) - 0.5*tau1)))*exp(gamma_Bs_freq*(TReseff.off(year_opt) - tau1)) - (0.5*delta_gamma_freq*TReseff.f1(year_opt)*exp(sigma_tres_eff(1)*sigma_tres_eff(1)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*sinh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1) + 0.5*TReseff.off(year_opt) - 0.5*tau2)) - 0.5*delta_gamma_freq*TReseff.f1(year_opt)*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*sinh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + 0.5*TReseff.off(year_opt) - 0.5*tau2)) + 0.5*delta_gamma_freq*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*sinh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + 0.5*TReseff.off(year_opt) - 0.5*tau2)) - 1.0*TReseff.f1(year_opt)*gamma_Bs_freq*exp(sigma_tres_eff(1)*sigma_tres_eff(1)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*cosh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1) + 0.5*TReseff.off(year_opt) - 0.5*tau2)) + 1.0*TReseff.f1(year_opt)*gamma_Bs_freq*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*cosh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + 0.5*TReseff.off(year_opt) - 0.5*tau2)) - 1.0*gamma_Bs_freq*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*cosh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + 0.5*TReseff.off(year_opt) - 0.5*tau2)))*exp(gamma_Bs_freq*(TReseff.off(year_opt) - tau2)))/((0.5*delta_gamma_freq - gamma_Bs_freq)*(0.5*delta_gamma_freq + gamma_Bs_freq));

 }

// ---------------------------------------------------
// Integral of the sinh time dependent term in a bin, effective resolution included, approximated solution.

Double_t KpiKpiSpectrumNW::IT_sinh_resapprox_eff_bin(Double_t tau1, Double_t tau2) const
 {
   
   return -((0.5*delta_gamma_freq*TReseff.f1(year_opt)*exp(sigma_tres_eff(1)*sigma_tres_eff(1)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*cosh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1) + 0.5*TReseff.off(year_opt) - 0.5*tau1)) - 0.5*delta_gamma_freq*TReseff.f1(year_opt)*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*cosh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + 0.5*TReseff.off(year_opt) - 0.5*tau1)) + 0.5*delta_gamma_freq*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*cosh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + 0.5*TReseff.off(year_opt) - 0.5*tau1)) - 1.0*TReseff.f1(year_opt)*gamma_Bs_freq*exp(sigma_tres_eff(1)*sigma_tres_eff(1)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*sinh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1) + 0.5*TReseff.off(year_opt) - 0.5*tau1)) + 1.0*TReseff.f1(year_opt)*gamma_Bs_freq*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*sinh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + 0.5*TReseff.off(year_opt) - 0.5*tau1)) - 1.0*gamma_Bs_freq*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*sinh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + 0.5*TReseff.off(year_opt) - 0.5*tau1)))*exp(gamma_Bs_freq*(TReseff.off(year_opt) - tau1)) - (0.5*delta_gamma_freq*TReseff.f1(year_opt)*exp(sigma_tres_eff(1)*sigma_tres_eff(1)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*cosh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1) + 0.5*TReseff.off(year_opt) - 0.5*tau2)) - 0.5*delta_gamma_freq*TReseff.f1(year_opt)*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*cosh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + 0.5*TReseff.off(year_opt) - 0.5*tau2)) + 0.5*delta_gamma_freq*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*cosh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + 0.5*TReseff.off(year_opt) - 0.5*tau2)) - 1.0*TReseff.f1(year_opt)*gamma_Bs_freq*exp(sigma_tres_eff(1)*sigma_tres_eff(1)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*sinh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1) + 0.5*TReseff.off(year_opt) - 0.5*tau2)) + 1.0*TReseff.f1(year_opt)*gamma_Bs_freq*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*sinh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + 0.5*TReseff.off(year_opt) - 0.5*tau2)) - 1.0*gamma_Bs_freq*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.125*delta_gamma_freq*delta_gamma_freq + 0.5*gamma_Bs_freq*gamma_Bs_freq))*sinh(delta_gamma_freq*(0.5*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + 0.5*TReseff.off(year_opt) - 0.5*tau2)))*exp(gamma_Bs_freq*(TReseff.off(year_opt) - tau2)))/((0.5*delta_gamma_freq - gamma_Bs_freq)*(0.5*delta_gamma_freq + gamma_Bs_freq));

 }

// ---------------------------------------------------
// Integral of the cos time dependent term in a bin, effective resolution included, approximated solution.

Double_t KpiKpiSpectrumNW::IT_cos_resapprox_eff_bin(Double_t tau1, Double_t tau2) const
 {
   
   return ((-TReseff.f1(year_opt)*(delta_m_freq*sin(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1) + TReseff.off(year_opt) - tau1)) + gamma_Bs_freq*cos(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1) + TReseff.off(year_opt) - tau1)))*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.5*delta_m_freq*delta_m_freq - 0.5*gamma_Bs_freq*gamma_Bs_freq)) + 1.0*(delta_m_freq*TReseff.f1(year_opt)*sin(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + TReseff.off(year_opt) - tau1)) - delta_m_freq*sin(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + TReseff.off(year_opt) - tau1)) + TReseff.f1(year_opt)*gamma_Bs_freq*cos(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + TReseff.off(year_opt) - tau1)) - gamma_Bs_freq*cos(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + TReseff.off(year_opt) - tau1)))*exp(sigma_tres_eff(1)*sigma_tres_eff(1)*(0.5*delta_m_freq*delta_m_freq - 0.5*gamma_Bs_freq*gamma_Bs_freq)))*exp(gamma_Bs_freq*(TReseff.off(year_opt) - tau1) - sigma_tres_eff(1)*sigma_tres_eff(1)*(0.5*delta_m_freq*delta_m_freq - 0.5*gamma_Bs_freq*gamma_Bs_freq) - sigma_tres_eff(2)*sigma_tres_eff(2)*(0.5*delta_m_freq*delta_m_freq - 0.5*gamma_Bs_freq*gamma_Bs_freq)) + (TReseff.f1(year_opt)*(delta_m_freq*sin(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1) + TReseff.off(year_opt) - tau2)) + gamma_Bs_freq*cos(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1) + TReseff.off(year_opt) - tau2)))*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.5*delta_m_freq*delta_m_freq - 0.5*gamma_Bs_freq*gamma_Bs_freq)) + 1.0*(-delta_m_freq*TReseff.f1(year_opt)*sin(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + TReseff.off(year_opt) - tau2)) + delta_m_freq*sin(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + TReseff.off(year_opt) - tau2)) - TReseff.f1(year_opt)*gamma_Bs_freq*cos(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + TReseff.off(year_opt) - tau2)) + gamma_Bs_freq*cos(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + TReseff.off(year_opt) - tau2)))*exp(sigma_tres_eff(1)*sigma_tres_eff(1)*(0.5*delta_m_freq*delta_m_freq - 0.5*gamma_Bs_freq*gamma_Bs_freq)))*exp(gamma_Bs_freq*(TReseff.off(year_opt) - tau2) - sigma_tres_eff(1)*sigma_tres_eff(1)*(0.5*delta_m_freq*delta_m_freq - 0.5*gamma_Bs_freq*gamma_Bs_freq) - sigma_tres_eff(2)*sigma_tres_eff(2)*(0.5*delta_m_freq*delta_m_freq - 0.5*gamma_Bs_freq*gamma_Bs_freq)))/(-delta_m_freq*delta_m_freq - gamma_Bs_freq*gamma_Bs_freq);

 }

// ---------------------------------------------------
// Integral of the sin time dependent term in a bin, effective resolution included, approximated solution.

Double_t KpiKpiSpectrumNW::IT_sin_resapprox_eff_bin(Double_t tau1, Double_t tau2) const
 {
   
   return ((-TReseff.f1(year_opt)*(delta_m_freq*cos(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1) + TReseff.off(year_opt) - tau1)) - gamma_Bs_freq*sin(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1) + TReseff.off(year_opt) - tau1)))*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.5*delta_m_freq*delta_m_freq - 0.5*gamma_Bs_freq*gamma_Bs_freq)) + 1.0*(delta_m_freq*TReseff.f1(year_opt)*cos(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + TReseff.off(year_opt) - tau1)) - delta_m_freq*cos(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + TReseff.off(year_opt) - tau1)) - TReseff.f1(year_opt)*gamma_Bs_freq*sin(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + TReseff.off(year_opt) - tau1)) + gamma_Bs_freq*sin(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + TReseff.off(year_opt) - tau1)))*exp(sigma_tres_eff(1)*sigma_tres_eff(1)*(0.5*delta_m_freq*delta_m_freq - 0.5*gamma_Bs_freq*gamma_Bs_freq)))*exp(gamma_Bs_freq*(TReseff.off(year_opt) - tau1) - sigma_tres_eff(1)*sigma_tres_eff(1)*(0.5*delta_m_freq*delta_m_freq - 0.5*gamma_Bs_freq*gamma_Bs_freq) - sigma_tres_eff(2)*sigma_tres_eff(2)*(0.5*delta_m_freq*delta_m_freq - 0.5*gamma_Bs_freq*gamma_Bs_freq)) + (TReseff.f1(year_opt)*(delta_m_freq*cos(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1) + TReseff.off(year_opt) - tau2)) - gamma_Bs_freq*sin(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1) + TReseff.off(year_opt) - tau2)))*exp(sigma_tres_eff(2)*sigma_tres_eff(2)*(0.5*delta_m_freq*delta_m_freq - 0.5*gamma_Bs_freq*gamma_Bs_freq)) + 1.0*(-delta_m_freq*TReseff.f1(year_opt)*cos(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + TReseff.off(year_opt) - tau2)) + delta_m_freq*cos(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + TReseff.off(year_opt) - tau2)) + TReseff.f1(year_opt)*gamma_Bs_freq*sin(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + TReseff.off(year_opt) - tau2)) - gamma_Bs_freq*sin(delta_m_freq*(gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2) + TReseff.off(year_opt) - tau2)))*exp(sigma_tres_eff(1)*sigma_tres_eff(1)*(0.5*delta_m_freq*delta_m_freq - 0.5*gamma_Bs_freq*gamma_Bs_freq)))*exp(gamma_Bs_freq*(TReseff.off(year_opt) - tau2) - sigma_tres_eff(1)*sigma_tres_eff(1)*(0.5*delta_m_freq*delta_m_freq - 0.5*gamma_Bs_freq*gamma_Bs_freq) - sigma_tres_eff(2)*sigma_tres_eff(2)*(0.5*delta_m_freq*delta_m_freq - 0.5*gamma_Bs_freq*gamma_Bs_freq)))/(-delta_m_freq*delta_m_freq - gamma_Bs_freq*gamma_Bs_freq);

 }

// ---------------------------------------------------
// Integral of the cosh time dependent term, effective resolution included, approximated solution.

Double_t KpiKpiSpectrumNW::IT_cosh_resapprox_eff() const
 {
   
   timefun_integral = 0.;
   for (int i=0; i<TAcc.nbins; ++i) {timefun_integral += TAcc.val(year_opt,trig_opt,wide_window,i)*IT_cosh_resapprox_eff_bin(TAcc.bounds(i),TAcc.bounds(i+1));}

   return timefun_integral;

 }

// ---------------------------------------------------
// Integral of the sinh time dependent term, effective resolution included, approximated solution.

Double_t KpiKpiSpectrumNW::IT_sinh_resapprox_eff() const
 {
   
   timefun_integral = 0.;
   for (int i=0; i<TAcc.nbins; ++i) {timefun_integral += TAcc.val(year_opt,trig_opt,wide_window,i)*IT_sinh_resapprox_eff_bin(TAcc.bounds(i),TAcc.bounds(i+1));}

   return timefun_integral;

 }

// ---------------------------------------------------
// Integral of the cos time dependent term, effective resolution included, approximated solution.

Double_t KpiKpiSpectrumNW::IT_cos_resapprox_eff() const
 {
   
   timefun_integral = 0.;
   for (int i=0; i<TAcc.nbins; ++i) {timefun_integral += TAcc.val(year_opt,trig_opt,wide_window,i)*IT_cos_resapprox_eff_bin(TAcc.bounds(i),TAcc.bounds(i+1));}

   return timefun_integral;

 }

// ---------------------------------------------------
// Integral of the sin time dependent term, effective resolution included, approximated solution.

Double_t KpiKpiSpectrumNW::IT_sin_resapprox_eff() const
 {
   
   timefun_integral = 0.;
   for (int i=0; i<TAcc.nbins; ++i) {timefun_integral += TAcc.val(year_opt,trig_opt,wide_window,i)*IT_sin_resapprox_eff_bin(TAcc.bounds(i),TAcc.bounds(i+1));}

   return timefun_integral;

 }

// ---------------------------------------------------
// 

std::complex<Double_t> KpiKpiSpectrumNW::conv_exp(Double_t x, std::complex<Double_t> z) const 
 {

   Double_t re = z.real()-x;

   if (re>-5.0) {return 0.5*RooMath::faddeeva_fast(std::complex<Double_t>(-z.imag(),re))*exp(-x*x);}

   else {
      // compute exp(-x^2)cwerf(-i(z-x)), cwerf(z) = exp(-z^2)erfc(-iz)
      // use the approximation: erfc(z) = exp(-z*z)/(sqrt(pi)*z)
      // to explicitly cancel the divergent exp(y*y) behaviour of
      // CWERF for z = x + i y with large negative y
      static const std::complex<Double_t> mi(0,-1);
      std::complex<Double_t> zp  = mi*(z-x);
      std::complex<Double_t> zsq = zp*zp;
      std::complex<Double_t> v = -zsq -x*x;
      std::complex<Double_t> iz(z.imag()+x,z.real()-x);
      return 0.5*exp(v)*(exp(zsq)/(iz*sqrt(pi)) + 1.)*2. ;
   }

 }

// ---------------------------------------------------
// 

std::complex<Double_t> KpiKpiSpectrumNW::Kn(std::complex<Double_t> z, Int_t n) const 
 {

   if (n == 0) {return 1./(2.*z);}
   else if (n == 1) {return 1./(2.*z*z);}
   else if (n == 2) {return 1./z*(1.+1./(z*z));}
   else if (n == 3) {return 3./(z*z)*(1.+1./(z*z));}

   throw std::invalid_argument( "Not implemented for n>3." );

 }

// ---------------------------------------------------
// 

std::complex<Double_t> KpiKpiSpectrumNW::Mn_x(Double_t x, std::complex<Double_t> z, Int_t n) const 
 {

   if (n == 0) {return std::complex<Double_t>(RooMath::erf(x),0.)-2.*conv_exp(x,z);}
   else if (n == 1) {return 2.*(-std::complex<Double_t>(sqrt(1./pi)*exp(-x*x),0.)-2.*x*conv_exp(x,z));}
   else if (n == 2) {return 2.*(-2.*x*exp(-x*x)*std::complex<Double_t>(sqrt(1./pi),0.)-(2.*x*x-1.)*2.*conv_exp(x,z));}
   else if (n == 3) {return 4.*(-(2.*x*x-1.)*exp(-x*x)*std::complex<Double_t>(sqrt(1./pi),0.)-x*(2.*x*x-3.)*2.*conv_exp(x,z));}

   throw std::invalid_argument( "Not implemented for n>3." );

 }

// ---------------------------------------------------
// 

std::complex<Double_t> KpiKpiSpectrumNW::Mn(Double_t x_1, Double_t x_2, std::complex<Double_t> z, Int_t n) const 
 {

   return Mn_x(x_2,z,n)-Mn_x(x_1,z,n);

 }

// ---------------------------------------------------
// 

void KpiKpiSpectrumNW::set_buffer_differential_vars(Double_t m1var, Double_t m2var, Double_t cos1var, Double_t cos2var, Double_t phivar, Double_t tvar, Double_t terrvar, Int_t decisionSSKvar, Int_t decisionOSvar, Double_t etamistagSSKvar, Double_t etamistagOSvar) const 
 {

   // Physical terms.

   Aj1j2h_temp[0][0][0] = Aj1j2h(0,0,0);
   Aj1j2h_temp[0][1][0] = Aj1j2h(0,1,0);
   Aj1j2h_temp[1][0][0] = Aj1j2h(1,0,0);
   Aj1j2h_temp[0][2][0] = Aj1j2h(0,2,0);
   Aj1j2h_temp[2][0][0] = Aj1j2h(2,0,0);
   Aj1j2h_temp[1][1][0] = Aj1j2h(1,1,0);
   Aj1j2h_temp[1][1][1] = Aj1j2h(1,1,1);
   Aj1j2h_temp[1][1][2] = Aj1j2h(1,1,2);
   Aj1j2h_temp[1][2][0] = Aj1j2h(1,2,0);
   Aj1j2h_temp[1][2][1] = Aj1j2h(1,2,1);
   Aj1j2h_temp[1][2][2] = Aj1j2h(1,2,2);
   Aj1j2h_temp[2][1][0] = Aj1j2h(2,1,0);
   Aj1j2h_temp[2][1][1] = Aj1j2h(2,1,1);
   Aj1j2h_temp[2][1][2] = Aj1j2h(2,1,2);
   Aj1j2h_temp[2][2][0] = Aj1j2h(2,2,0);
   Aj1j2h_temp[2][2][1] = Aj1j2h(2,2,1);
   Aj1j2h_temp[2][2][2] = Aj1j2h(2,2,2);
   Aj1j2h_temp[2][2][3] = Aj1j2h(2,2,3);
   Aj1j2h_temp[2][2][4] = Aj1j2h(2,2,4);
   Abarj1j2h_temp[0][0][0] = Abarj1j2h(0,0,0);
   Abarj1j2h_temp[0][1][0] = Abarj1j2h(0,1,0);
   Abarj1j2h_temp[1][0][0] = Abarj1j2h(1,0,0);
   Abarj1j2h_temp[0][2][0] = Abarj1j2h(0,2,0);
   Abarj1j2h_temp[2][0][0] = Abarj1j2h(2,0,0);
   Abarj1j2h_temp[1][1][0] = Abarj1j2h(1,1,0);
   Abarj1j2h_temp[1][1][1] = Abarj1j2h(1,1,1);
   Abarj1j2h_temp[1][1][2] = Abarj1j2h(1,1,2);
   Abarj1j2h_temp[1][2][0] = Abarj1j2h(1,2,0);
   Abarj1j2h_temp[1][2][1] = Abarj1j2h(1,2,1);
   Abarj1j2h_temp[1][2][2] = Abarj1j2h(1,2,2);
   Abarj1j2h_temp[2][1][0] = Abarj1j2h(2,1,0);
   Abarj1j2h_temp[2][1][1] = Abarj1j2h(2,1,1);
   Abarj1j2h_temp[2][1][2] = Abarj1j2h(2,1,2);
   Abarj1j2h_temp[2][2][0] = Abarj1j2h(2,2,0);
   Abarj1j2h_temp[2][2][1] = Abarj1j2h(2,2,1);
   Abarj1j2h_temp[2][2][2] = Abarj1j2h(2,2,2);
   Abarj1j2h_temp[2][2][3] = Abarj1j2h(2,2,3);
   Abarj1j2h_temp[2][2][4] = Abarj1j2h(2,2,4);

   // Time dependent terms.

   Double_t f1,f2,s1,s2,x1,x2;

   if (acctype == 3) {
      f1 = TRes.f1(1);
      f2 = 1.-f1;
      s1 = (TRes.q0A(1)+(TRes.q1A(1)+TRes.q2A(1)*(terrvar-TRes.mean(1)))*terrvar)-sqrt(TRes.f1(1)/(1.-TRes.f1(1)))*(TRes.q0B(1)+(TRes.q1B(1)+TRes.q2B(1)*(terrvar-TRes.mean(1)))*terrvar);
      s2 = (TRes.q0A(1)+(TRes.q1A(1)+TRes.q2A(1)*(terrvar-TRes.mean(1)))*terrvar)+sqrt((1.-TRes.f1(1))/TRes.f1(1))*(TRes.q0B(1)+(TRes.q1B(1)+TRes.q2B(1)*(terrvar-TRes.mean(1)))*terrvar);
      x1 = (tvar-TRes.off(1))/(sqrt(2.)*s1);
      x2 = (tvar-TRes.off(1))/(sqrt(2.)*s2);
   }
   else {
      f1 = TRes.f1(year_opt);
      f2 = 1.-f1;
      s1 = sigma_tres(terrvar,1);
      s2 = sigma_tres(terrvar,2);
      x1 = (tvar-TRes.off(year_opt))/(sqrt(2.)*s1);
      x2 = (tvar-TRes.off(year_opt))/(sqrt(2.)*s2);
   }

   std::complex<Double_t> z1_hyper_plus = s1/sqrt(2.)*std::complex<Double_t>(gamma_Bs_freq-0.5*delta_gamma_freq,0.);
   std::complex<Double_t> z2_hyper_plus = s2/sqrt(2.)*std::complex<Double_t>(gamma_Bs_freq-0.5*delta_gamma_freq,0.);
   std::complex<Double_t> z1_hyper_minus = s1/sqrt(2.)*std::complex<Double_t>(gamma_Bs_freq+0.5*delta_gamma_freq,0.);
   std::complex<Double_t> z2_hyper_minus = s2/sqrt(2.)*std::complex<Double_t>(gamma_Bs_freq+0.5*delta_gamma_freq,0.);
   std::complex<Double_t> z1_trigo = s1/sqrt(2.)*std::complex<Double_t>(gamma_Bs_freq,-delta_m_freq);
   std::complex<Double_t> z2_trigo = s2/sqrt(2.)*std::complex<Double_t>(gamma_Bs_freq,-delta_m_freq);

   Double_t conv_exp_hyper_plus = (f1*conv_exp(x1,z1_hyper_plus)+f2*conv_exp(x2,z2_hyper_plus)).real();
   Double_t conv_exp_hyper_minus = (f1*conv_exp(x1,z1_hyper_minus)+f2*conv_exp(x2,z2_hyper_minus)).real();
   std::complex<Double_t> conv_exp_trigo = f1*conv_exp(x1,z1_trigo)+f2*conv_exp(x2,z2_trigo);

   T_cosh_temp = 0.5*(conv_exp_hyper_plus + conv_exp_hyper_minus);
   T_sinh_temp = 0.5*(conv_exp_hyper_plus - conv_exp_hyper_minus);
   T_cos_temp = conv_exp_trigo.real();
   T_sin_temp = conv_exp_trigo.imag();

   // Tagging terms.

   zeta_temp = zeta(decisionSSKvar,decisionOSvar,etamistagSSKvar,etamistagOSvar);
   DCP_tzero_temp = DCP_tzero(decisionSSKvar,decisionOSvar,etamistagSSKvar,etamistagOSvar);

   // Angular terms.

   for (int i=0; i<18; ++i) {fi_cos1_temp[i] = fi(cos1var,i+1);}
   for (int i=0; i<18; ++i) {fi_cos2_temp[i] = fi(cos2var,i+1);}
   for (int i=0; i<15; ++i) {gi_temp[i] = gi(phivar,i+1);}

   // Mass terms.

   for (int j1=0; j1<3; ++j1) {
      for (int j2=0; j2<3; ++j2) {
         Mj1j2_temp[j1][j2] = Mj1j2(m1var,m2var,j1,j2);
      }
   }
   phasespace_temp = phasespace(m1var,m2var);

 }

// ---------------------------------------------------
// 

void KpiKpiSpectrumNW::set_buffer_integral_vars() const 
 {

   // Physical terms.

   Aj1j2h_temp[0][0][0] = Aj1j2h(0,0,0);
   Aj1j2h_temp[0][1][0] = Aj1j2h(0,1,0);
   Aj1j2h_temp[1][0][0] = Aj1j2h(1,0,0);
   Aj1j2h_temp[0][2][0] = Aj1j2h(0,2,0);
   Aj1j2h_temp[2][0][0] = Aj1j2h(2,0,0);
   Aj1j2h_temp[1][1][0] = Aj1j2h(1,1,0);
   Aj1j2h_temp[1][1][1] = Aj1j2h(1,1,1);
   Aj1j2h_temp[1][1][2] = Aj1j2h(1,1,2);
   Aj1j2h_temp[1][2][0] = Aj1j2h(1,2,0);
   Aj1j2h_temp[1][2][1] = Aj1j2h(1,2,1);
   Aj1j2h_temp[1][2][2] = Aj1j2h(1,2,2);
   Aj1j2h_temp[2][1][0] = Aj1j2h(2,1,0);
   Aj1j2h_temp[2][1][1] = Aj1j2h(2,1,1);
   Aj1j2h_temp[2][1][2] = Aj1j2h(2,1,2);
   Aj1j2h_temp[2][2][0] = Aj1j2h(2,2,0);
   Aj1j2h_temp[2][2][1] = Aj1j2h(2,2,1);
   Aj1j2h_temp[2][2][2] = Aj1j2h(2,2,2);
   Aj1j2h_temp[2][2][3] = Aj1j2h(2,2,3);
   Aj1j2h_temp[2][2][4] = Aj1j2h(2,2,4);
   Abarj1j2h_temp[0][0][0] = Abarj1j2h(0,0,0);
   Abarj1j2h_temp[0][1][0] = Abarj1j2h(0,1,0);
   Abarj1j2h_temp[1][0][0] = Abarj1j2h(1,0,0);
   Abarj1j2h_temp[0][2][0] = Abarj1j2h(0,2,0);
   Abarj1j2h_temp[2][0][0] = Abarj1j2h(2,0,0);
   Abarj1j2h_temp[1][1][0] = Abarj1j2h(1,1,0);
   Abarj1j2h_temp[1][1][1] = Abarj1j2h(1,1,1);
   Abarj1j2h_temp[1][1][2] = Abarj1j2h(1,1,2);
   Abarj1j2h_temp[1][2][0] = Abarj1j2h(1,2,0);
   Abarj1j2h_temp[1][2][1] = Abarj1j2h(1,2,1);
   Abarj1j2h_temp[1][2][2] = Abarj1j2h(1,2,2);
   Abarj1j2h_temp[2][1][0] = Abarj1j2h(2,1,0);
   Abarj1j2h_temp[2][1][1] = Abarj1j2h(2,1,1);
   Abarj1j2h_temp[2][1][2] = Abarj1j2h(2,1,2);
   Abarj1j2h_temp[2][2][0] = Abarj1j2h(2,2,0);
   Abarj1j2h_temp[2][2][1] = Abarj1j2h(2,2,1);
   Abarj1j2h_temp[2][2][2] = Abarj1j2h(2,2,2);
   Abarj1j2h_temp[2][2][3] = Abarj1j2h(2,2,3);
   Abarj1j2h_temp[2][2][4] = Abarj1j2h(2,2,4);

   // Time dependent terms.

   std::complex<Double_t> z1_hyper_plus = s1_eff[(int) year_opt]/sqrt(2.)*std::complex<Double_t>(gamma_Bs_freq-0.5*delta_gamma_freq,0.);
   std::complex<Double_t> z2_hyper_plus = s2_eff[(int) year_opt]/sqrt(2.)*std::complex<Double_t>(gamma_Bs_freq-0.5*delta_gamma_freq,0.);
   std::complex<Double_t> z1_hyper_minus = s1_eff[(int) year_opt]/sqrt(2.)*std::complex<Double_t>(gamma_Bs_freq+0.5*delta_gamma_freq,0.);
   std::complex<Double_t> z2_hyper_minus = s2_eff[(int) year_opt]/sqrt(2.)*std::complex<Double_t>(gamma_Bs_freq+0.5*delta_gamma_freq,0.);
   std::complex<Double_t> z1_trigo = s1_eff[(int) year_opt]/sqrt(2.)*std::complex<Double_t>(gamma_Bs_freq,-delta_m_freq);
   std::complex<Double_t> z2_trigo = s2_eff[(int) year_opt]/sqrt(2.)*std::complex<Double_t>(gamma_Bs_freq,-delta_m_freq);

   Double_t integral_conv_exp_hyper_plus_1 = 0;
   Double_t integral_conv_exp_hyper_plus_2 = 0;
   Double_t integral_conv_exp_hyper_minus_1 = 0;
   Double_t integral_conv_exp_hyper_minus_2 = 0;
   std::complex<Double_t> integral_conv_exp_trigo_1 = std::complex<Double_t>(0.,0.);
   std::complex<Double_t> integral_conv_exp_trigo_2 = std::complex<Double_t>(0.,0.);

   if (acctype == 0) {
      integral_conv_exp_hyper_plus_1 += (s1_eff[(int) year_opt]/sqrt(2.)*Mn((0.-TReseff.off(1))/(sqrt(2.)*s1_eff[(int) year_opt]),(12.-TReseff.off(1))/(sqrt(2.)*s1_eff[(int) year_opt]),z1_hyper_plus,0)*Kn(z1_hyper_plus,0)).real();
      integral_conv_exp_hyper_plus_2 += (s2_eff[(int) year_opt]/sqrt(2.)*Mn((0.-TReseff.off(1))/(sqrt(2.)*s2_eff[(int) year_opt]),(12.-TReseff.off(1))/(sqrt(2.)*s2_eff[(int) year_opt]),z2_hyper_plus,0)*Kn(z2_hyper_plus,0)).real();
      integral_conv_exp_hyper_minus_1 += (s1_eff[(int) year_opt]/sqrt(2.)*Mn((0.-TReseff.off(1))/(sqrt(2.)*s1_eff[(int) year_opt]),(12.-TReseff.off(1))/(sqrt(2.)*s1_eff[(int) year_opt]),z1_hyper_minus,0)*Kn(z1_hyper_minus,0)).real();
      integral_conv_exp_hyper_minus_2 += (s2_eff[(int) year_opt]/sqrt(2.)*Mn((0.-TReseff.off(1))/(sqrt(2.)*s2_eff[(int) year_opt]),(12.-TReseff.off(1))/(sqrt(2.)*s2_eff[(int) year_opt]),z2_hyper_minus,0)*Kn(z2_hyper_minus,0)).real();
      integral_conv_exp_trigo_1 += s1_eff[(int) year_opt]/sqrt(2.)*Mn((0.-TReseff.off(1))/(sqrt(2.)*s1_eff[(int) year_opt]),(12.-TReseff.off(1))/(sqrt(2.)*s1_eff[(int) year_opt]),z1_trigo,0)*Kn(z1_trigo,0);
      integral_conv_exp_trigo_2 += s2_eff[(int) year_opt]/sqrt(2.)*Mn((0.-TReseff.off(1))/(sqrt(2.)*s2_eff[(int) year_opt]),(12.-TReseff.off(1))/(sqrt(2.)*s2_eff[(int) year_opt]),z2_trigo,0)*Kn(z2_trigo,0);
   }
   else {
      for (int ibin=0; ibin<5; ++ibin) {
         for (int k=0; k<4; ++k) {
            for (int i=0; i<(k+1); ++i) {
               for (int j=0; j<(i+1); ++j) {
                  integral_conv_exp_hyper_plus_1 += (spl_coef_array_1[(int) year_opt][(int) trig_opt][ibin][k][i][j]*Mn(spl_knot_x1_vector[(int) year_opt][(int) trig_opt][ibin],spl_knot_x1_vector[(int) year_opt][(int) trig_opt][ibin+1],z1_hyper_plus,i-j)*Kn(z1_hyper_plus,j)).real();
                  integral_conv_exp_hyper_plus_2 += (spl_coef_array_2[(int) year_opt][(int) trig_opt][ibin][k][i][j]*Mn(spl_knot_x2_vector[(int) year_opt][(int) trig_opt][ibin],spl_knot_x2_vector[(int) year_opt][(int) trig_opt][ibin+1],z2_hyper_plus,i-j)*Kn(z2_hyper_plus,j)).real();
                  integral_conv_exp_hyper_minus_1 += (spl_coef_array_1[(int) year_opt][(int) trig_opt][ibin][k][i][j]*Mn(spl_knot_x1_vector[(int) year_opt][(int) trig_opt][ibin],spl_knot_x1_vector[(int) year_opt][(int) trig_opt][ibin+1],z1_hyper_minus,i-j)*Kn(z1_hyper_minus,j)).real();
                  integral_conv_exp_hyper_minus_2 += (spl_coef_array_2[(int) year_opt][(int) trig_opt][ibin][k][i][j]*Mn(spl_knot_x2_vector[(int) year_opt][(int) trig_opt][ibin],spl_knot_x2_vector[(int) year_opt][(int) trig_opt][ibin+1],z2_hyper_minus,i-j)*Kn(z2_hyper_minus,j)).real();
                  integral_conv_exp_trigo_1 += spl_coef_array_1[(int) year_opt][(int) trig_opt][ibin][k][i][j]*Mn(spl_knot_x1_vector[(int) year_opt][(int) trig_opt][ibin],spl_knot_x1_vector[(int) year_opt][(int) trig_opt][ibin+1],z1_trigo,i-j)*Kn(z1_trigo,j);
                  integral_conv_exp_trigo_2 += spl_coef_array_2[(int) year_opt][(int) trig_opt][ibin][k][i][j]*Mn(spl_knot_x2_vector[(int) year_opt][(int) trig_opt][ibin],spl_knot_x2_vector[(int) year_opt][(int) trig_opt][ibin+1],z2_trigo,i-j)*Kn(z2_trigo,j);
               }
            }
         }
      }
   }

   Double_t integral_conv_exp_hyper_plus = f1_eff[(int) year_opt]*integral_conv_exp_hyper_plus_1+f2_eff[(int) year_opt]*integral_conv_exp_hyper_plus_2;
   Double_t integral_conv_exp_hyper_minus = f1_eff[(int) year_opt]*integral_conv_exp_hyper_minus_1+f2_eff[(int) year_opt]*integral_conv_exp_hyper_minus_2;
   std::complex<Double_t> integral_conv_exp_trigo = f1_eff[(int) year_opt]*integral_conv_exp_trigo_1+f2_eff[(int) year_opt]*integral_conv_exp_trigo_2;

   IT_cosh_temp = 0.5*(integral_conv_exp_hyper_plus + integral_conv_exp_hyper_minus);
   IT_sinh_temp = 0.5*(integral_conv_exp_hyper_plus - integral_conv_exp_hyper_minus);
   IT_cos_temp = integral_conv_exp_trigo.real();
   IT_sin_temp = integral_conv_exp_trigo.imag();

 }

// ######################################################################################################
// A N G U L A R   T E R M S
// ######################################################################################################

// ---------------------------------------------------
// Elementary angular functions in cos(theta).

Double_t KpiKpiSpectrumNW::fi(Double_t x, Int_t i) const 
 { 

   switch(i) {
      case 1 : return 1.;
      case 2 : return x;
      case 3 : return sqrt(1.-x*x);
      case 4 : return 3.*x*x-1.;
      case 5 : return x*sqrt(1.-x*x);
      case 6 : return x*x;
      case 7 : return x*(3.*x*x-1.);
      case 8 : return x*x*sqrt(1.-x*x);
      case 9 : return 1.-x*x;
      case 10 : return (3.*x*x-1.)*sqrt(1.-x*x);
      case 11 : return x*(1.-x*x);
      case 12 : return (3.*x*x-1.)*(3.*x*x-1.);
      case 13 : return x*(3.*x*x-1.)*sqrt(1.-x*x);
      case 14 : return x*x*(1.-x*x);
      case 15 : return (1.-x*x)*sqrt(1.-x*x);
      case 16 : return (3.*x*x-1.)*(1.-x*x);
      case 17 : return x*(1.-x*x)*sqrt(1.-x*x);
      case 18 : return (1.-x*x)*(1.-x*x);
   }

   throw std::invalid_argument( "Invalid argument #1" );

 }

// ---------------------------------------------------
// Elementary angular functions in phi.

Double_t KpiKpiSpectrumNW::gi(Double_t x, Int_t i) const 
 { 

   switch(i) {
      case 1 : return 1.;
      case 2 : return cos(x);
      case 3 : return sin(x);
      case 4 : return cos(x)*cos(x);
      case 5 : return sin(x)*cos(x);
      case 6 : return sin(x)*sin(x);
      case 7 : return cos(2.*x);
      case 8 : return sin(2.*x);
      case 9 : return cos(x)*cos(2.*x);
      case 10 : return cos(x)*sin(2.*x);
      case 11 : return sin(x)*cos(2.*x);
      case 12 : return sin(x)*sin(2.*x);
      case 13 : return cos(2.*x)*cos(2.*x);
      case 14 : return sin(2.*x)*cos(2.*x);
      case 15 : return sin(2.*x)*sin(2.*x);
   }

   throw std::invalid_argument( "Invalid argument #2" );

 }

// ---------------------------------------------------
//Angular functions in cos(theta).

Double_t KpiKpiSpectrumNW::fjjphhp(Double_t x, Int_t j, Int_t jp, Int_t h, Int_t hp) const 
 { 

   return fi(x,fjjphhpindexdict[j][jp][h][hp]);

 }

// ---------------------------------------------------
//

Double_t KpiKpiSpectrumNW::fjjphhp_cos1(Int_t j, Int_t jp, Int_t h, Int_t hp) const 
 { 

   return fi_cos1_temp[(int) fjjphhpindexdict[j][jp][h][hp]-1];

 }

// ---------------------------------------------------
//

Double_t KpiKpiSpectrumNW::fjjphhp_cos2(Int_t j, Int_t jp, Int_t h, Int_t hp) const 
 { 

   return fi_cos2_temp[(int) fjjphhpindexdict[j][jp][h][hp]-1];

 }

// ---------------------------------------------------
// Angular functions in phi.

Double_t KpiKpiSpectrumNW::ghhp(Double_t x, Int_t h, Int_t hp) const 
 { 

   return gi(x,ghhpindexdict[h][hp]);

 }

// ---------------------------------------------------
// 

Double_t KpiKpiSpectrumNW::ghhp_phi(Int_t h, Int_t hp) const 
 { 

   return gi_temp[(int) ghhpindexdict[h][hp]-1];

 }

// ---------------------------------------------------
// Numerical normalization factors.

TComplex KpiKpiSpectrumNW::Nj1j2hj1pj2php(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const 
 {

   return Nj1j2hdict[j1][j2][h]*TComplex::Conjugate(Nj1j2hdict[j1p][j2p][hp]);
  
 }

// ######################################################################################################
// I N V A R I A N T   M A S S   D E P E N D E N T   T E R M S
// ######################################################################################################

// ---------------------------------------------------
// Momentum of one of the two daughters in the rest frame of the mother.

Double_t KpiKpiSpectrumNW::get_q(Double_t M, Double_t ma, Double_t mb) const 
 {

   Double_t M2 = M*M;
   Double_t m12 = ma*ma;
   Double_t m22 = mb*mb;
   Double_t q2 = .25*( M2*M2 - 2*M2*(m12+m22) +(m12*m12+m22*m22)-2*m12*m22) /M2;
   if (q2<0) {return 0.;}
   return sqrt(q2);

 }

// ---------------------------------------------------
// Blatt Weisskopf factor squared.

Double_t KpiKpiSpectrumNW::Blatt_Weisskopf2(Double_t q, Double_t q0, Int_t L) const 
 {

   if (L<1.) {return 1.;}  
   Double_t d;
   if (L == 1) {d = 3.e-03;}
   else if (L == 2) {d = 2.7e-03;}
   else {d = 3.e-03/L;}
   Double_t z = q*d*q*d;
   Double_t z0 = q0*d*q0*d;
   if (L==1) {return (1+z0)/(1+z);}
   else if (L==2) {return ((z0-3)*(z0-3) + 9*z0) / ((z-3)*(z-3) + 9*z);}
   else if (L==3) {return (z0*(z0-15)*(z0-15) + 9*(z0-5)) / (z*(z-15)*(z-15) + 9*(z-5));}
   return ( pow(z0*z0 -45*z0+105,2) +25*z0*(2*z0-21)*(2*z0-21)) /(pow(z*z -45*z+105,2) +25*z*(2*z-21)*(2*z-21));

 }

// ---------------------------------------------------
// Isobaric amplitude for a resonance of mass m0, width g0 and spin J.

TComplex KpiKpiSpectrumNW::Resonance(Double_t m, Double_t m_sister, Double_t m0, Double_t g0, Int_t J) const
 {

   // Approximation of the lowest orbital angular momentum available.
   Int_t L = 0;
   if (J == 0) {L = 1;}
   else if (J == 1) {L = 0;}
   else if (J == 2) {L = 1;}

   // Angular momentum barrier factor for the decay of the Kst.
   Double_t q = get_q(m,MPion,MKaon);
   Double_t q0 = get_q(m0,MPion,MKaon);
   if (q==0) return 0;
   Double_t kst_decay = pow(q/m,J)*sqrt(Blatt_Weisskopf2(q,q0,J));

   // Angular momentum barrier factor for the creation of the Kst.
   Double_t p = get_q(MBs,m_sister,m);
   Double_t p0 = get_q(MBs,m_sister,m0);
   if (p==0) return 0;
   Double_t kst_birth = pow(p/MBs,L)*sqrt(Blatt_Weisskopf2(p,p0,L));

   // Relativistic spin-J Breit Wigner amplitude.
   Double_t gamma = g0*pow(q/q0,2*J+1)*m0/m*Blatt_Weisskopf2(q,q0,J);
   TComplex denom(m0*m0-m*m,-m0*gamma);
   TComplex num(m0*g0,0.);
   TComplex BW = num/denom;

   return BW * kst_birth * kst_decay;

 }

// ---------------------------------------------------
// Lass parametrization for the S wave.

TComplex KpiKpiSpectrumNW::Lass(Double_t m, Double_t m_sister, Double_t m0, Double_t g0) const 
 { 

   TComplex i(0,1);
   
   Double_t q = get_q(m,MPion,MKaon);
   Double_t q0 = get_q(m0,MPion,MKaon);
   if (q==0) return 0;
   Double_t p = get_q(MBs,m_sister,m);
   Double_t p0 = get_q(MBs,m_sister,m0);
   if (p==0) return 0;

   Double_t cotg_deltaB = 1./(a_lass*q)+0.5*r_lass*q;
   Double_t deltaB = atan(1./cotg_deltaB);
   TComplex expo(1.,2.*deltaB,1);

   Double_t gamma = g0*q/q0*m0/m;
   Double_t cotg_deltaR = (m0*m0-m*m)/(m0*gamma);

   TComplex T = sqrt(Blatt_Weisskopf2(p,p0,1))*p*m/q*(1./(cotg_deltaB-i)+expo/(cotg_deltaR-i));

   return T;

 } 

// ---------------------------------------------------
// Invariant mass amplitude for each wave.

TComplex KpiKpiSpectrumNW::Mji(Double_t m, Double_t m_sister, Int_t ji) const 
 {

   TComplex T;

   if (ji == 0)
	{
	T = Lass(m,m_sister,ms,gs)*TComplex(0.00021167233881101775,-0.6904181463662509,1);
	}

   else if (ji == 1.)
	{
	if (pw_mass_altmodel == 0) {T = Resonance(m,m_sister,mv,gv,1)*TComplex(3.0782434270248222,1.5707963267948966-pi,1);}
	else if (pw_mass_altmodel == 1) {T = Resonance(m,m_sister,mv,gv,1) + TComplex(sqrt(f_1410_rel2_892),delta_1410_rel2_892,1)*Resonance(m,m_sister,MKst_1_1410,GKst_1_1410,1) + TComplex(sqrt(f_1680_rel2_892),delta_1680_rel2_892,1)*Resonance(m,m_sister,MKst_1_1680,GKst_1_1680,1);}
	else {throw std::invalid_argument( "Invalid argument #4" );}
	}

   else if (ji == 2)
	{
	T = Resonance(m,m_sister,mt,gt,2)*TComplex(112.27484112040055,3.1314804474438556-pi,1);
	}
   
   return T;

 }

// ---------------------------------------------------
// Invariant mass dependent factor for each amplitude.
 
TComplex KpiKpiSpectrumNW::Mj1j2(Double_t ma, Double_t mb, Int_t j1, Int_t j2) const 
 { 

 if ((j1 == 0) and (j2 == 0)) {return Mji(ma,mb,0)*Mji(mb,ma,0)/sqrt(Im00);}
 else if ((j1 == 0) and (j2 == 1)) {return Mji(ma,mb,0)*Mji(mb,ma,1)/sqrt(Im01);}
 else if ((j1 == 1) and (j2 == 0)) {return Mji(ma,mb,1)*Mji(mb,ma,0)/sqrt(Im10);}
 else if ((j1 == 0) and (j2 == 2)) {return Mji(ma,mb,0)*Mji(mb,ma,2)/sqrt(Im02);}
 else if ((j1 == 2) and (j2 == 0)) {return Mji(ma,mb,2)*Mji(mb,ma,0)/sqrt(Im20);}
 else if ((j1 == 1) and (j2 == 1)) {return Mji(ma,mb,1)*Mji(mb,ma,1)/sqrt(Im11);}
 else if ((j1 == 1) and (j2 == 2)) {return Mji(ma,mb,1)*Mji(mb,ma,2)/sqrt(Im12);}
 else if ((j1 == 2) and (j2 == 1)) {return Mji(ma,mb,2)*Mji(mb,ma,1)/sqrt(Im21);}
 else if ((j1 == 2) and (j2 == 2)) {return Mji(ma,mb,2)*Mji(mb,ma,2)/sqrt(Im22);}

 throw std::invalid_argument( "Invalid argument #5" );

 }

// ---------------------------------------------------
// Phase space factor.

Double_t KpiKpiSpectrumNW::phasespace(Double_t ma, Double_t mb) const 
 { 
 
   Double_t Q1 = get_q(ma,MKaon,MPion);
   Double_t Q2 = get_q(mb,MKaon,MPion);
   Double_t QB = get_q(MBs,ma,mb);
   Double_t phsp = Q1*Q2*QB*4.668198266871305e-09;

   return phsp;

 } 

// ---------------------------------------------------
// Invariant mass dependent functions.

TComplex KpiKpiSpectrumNW::hj1j2j1pj2p(Double_t ma, Double_t mb, Int_t j1, Int_t j2, Int_t j1p, Int_t j2p) const 
 { 

   return Mj1j2_temp[j1][j2]*TComplex::Conjugate(Mj1j2_temp[j1p][j2p])*phasespace_temp;

 }

// ######################################################################################################
// P A R A M E T R I C   A C C E P T A N C E
// ######################################################################################################

// ---------------------------------------------------
// Time dependent acceptance, spline version.

Double_t KpiKpiSpectrumNW::accTime(Double_t tau) const 
 { 

   if (acctype == 0) {return 1.;}
   else if (acctype == 1 or acctype == 2) {

      Int_t tau_bin;
      if (tau < spl.knot(wide_window,1)) {tau_bin = 0;}
      else if ((tau >= spl.knot(wide_window,1)) and (tau < spl.knot(wide_window,2))) {tau_bin = 1;}
      else if ((tau >= spl.knot(wide_window,2)) and (tau < spl.knot(wide_window,3))) {tau_bin = 2;}
      else if ((tau >= spl.knot(wide_window,3)) and (tau < spl.knot(wide_window,4))) {tau_bin = 3;}
      else {tau_bin = 4;}

      return spl.coef(year_opt,trig_opt,wide_window,tau_bin,0)+tau*spl.coef(year_opt,trig_opt,wide_window,tau_bin,1)+tau*tau*spl.coef(year_opt,trig_opt,wide_window,tau_bin,2)+tau*tau*tau*spl.coef(year_opt,trig_opt,wide_window,tau_bin,3);

   }

   else if (acctype == 3) {

      Int_t tau_bin;
      if (tau < genaccpar.knot_gen(wide_window,1)) {tau_bin = 0;}
      else if ((tau >= genaccpar.knot_gen(wide_window,1)) and (tau < genaccpar.knot_gen(wide_window,2))) {tau_bin = 1;}
      else if ((tau >= genaccpar.knot_gen(wide_window,2)) and (tau < genaccpar.knot_gen(wide_window,3))) {tau_bin = 2;}
      else if ((tau >= genaccpar.knot_gen(wide_window,3)) and (tau < genaccpar.knot_gen(wide_window,4))) {tau_bin = 3;}
      else {tau_bin = 4;}

      return genaccpar.coef_gen(wide_window,tau_bin,0)+tau*genaccpar.coef_gen(wide_window,tau_bin,1)+tau*tau*genaccpar.coef_gen(wide_window,tau_bin,2)+tau*tau*tau*genaccpar.coef_gen(wide_window,tau_bin,3);

   }

   return 0.;

 }

// ---------------------------------------------------
// Time dependent acceptance, parametric version.

Double_t KpiKpiSpectrumNW::accTimeParam(Double_t tau) const 
 { 
   
   return tau*tau*tau/(accpar.a_acc(year_opt,trig_opt,wide_window)+tau*tau*tau)*(1.+accpar.b_acc(year_opt,trig_opt,wide_window)*tau+accpar.c_acc(year_opt,trig_opt,wide_window)*tau*tau);

 }

// ---------------------------------------------------
// Time dependent acceptance, histogram version.

Double_t KpiKpiSpectrumNW::accTimeHisto(Double_t tau) const 
 { 

   for (int i=0; i<TAcc.nbins; ++i) {
      if (tau >= TAcc.bounds(i) and tau < TAcc.bounds(i+1)) {return TAcc.val(year_opt,trig_opt,wide_window,i);}
   }

   return TAcc.val(year_opt,trig_opt,wide_window,TAcc.nbins-1);

 }

// ---------------------------------------------------
// Angular acceptance in cos(theta).

Double_t KpiKpiSpectrumNW::accAng(Double_t x) const
 { 

   if (acctype == 0) {return 1.;}
   else if (acctype == 1 or acctype == 2) {return 1.+accpar.k1(year_opt,trig_opt,wide_window)*x+accpar.k2(year_opt,trig_opt,wide_window)*(2.*x*x-1.)+accpar.k3(year_opt,trig_opt,wide_window)*(4.*x*x*x-3.*x)+accpar.k4(year_opt,trig_opt,wide_window)*(8.*x*x*x*x-8.*x*x+1.)+accpar.k5(year_opt,trig_opt,wide_window)*(16.*x*x*x*x*x-20.*x*x*x+5.*x);}
   else if (acctype == 3) {return 1.+genaccpar.k1_gen(wide_window)*x+genaccpar.k2_gen(wide_window)*(2.*x*x-1.)+genaccpar.k3_gen(wide_window)*(4.*x*x*x-3.*x)+genaccpar.k4_gen(wide_window)*(8.*x*x*x*x-8.*x*x+1.)+genaccpar.k5_gen(wide_window)*(16.*x*x*x*x*x-20.*x*x*x+5.*x);}

   return 0.;

 }

// ---------------------------------------------------
// Invariant mass dependent acceptance.

Double_t KpiKpiSpectrumNW::accMass(Double_t m) const 
 { 
   
   if (acctype == 0) {return 1.;}
   else if (acctype == 1 or acctype == 2) {return 1. + accpar.p1(year_opt,trig_opt,wide_window)*m;}
   else if (acctype == 3) {return 1. + genaccpar.p1_gen(wide_window)*m;}

   return 0.;

 }

// ---------------------------------------------------
// Integrals of the time dependent functions, effective resolution, without tagging, parametric acceptance.

TComplex KpiKpiSpectrumNW::ITj1j2hj1pj2php(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const
 {

   return (IT_cosh_temp*M_Average(j1,j2,h,j1p,j2p,hp)-IT_sinh_temp*M_DeltaGamma(j1,j2,h,j1p,j2p,hp))+DCP_prod[int(wide_window)]*(IT_cos_temp*M_DirCP(j1,j2,h,j1p,j2p,hp)+IT_sin_temp*M_MixCP(j1,j2,h,j1p,j2p,hp));

 }

// ---------------------------------------------------
// Integrals of the elementary angular functions in cos(theta), parametric acceptance.

Double_t KpiKpiSpectrumNW::Ifi(Int_t i) const
 { 

   if (i == 1) {return If1;}
   else if (i == 2) {return If2;}
   else if (i == 3) {return If3;}
   else if (i == 4) {return If4;}
   else if (i == 5) {return If5;}
   else if (i == 6) {return If6;}
   else if (i == 7) {return If7;}
   else if (i == 8) {return If8;}
   else if (i == 9) {return If9;}
   else if (i == 10) {return If10;}
   else if (i == 11) {return If11;}
   else if (i == 12) {return If12;}
   else if (i == 13) {return If13;}
   else if (i == 14) {return If14;}
   else if (i == 15) {return If15;}
   else if (i == 16) {return If16;}
   else if (i == 17) {return If17;}
   else if (i == 18) {return If18;}

   throw std::invalid_argument( "Invalid argument #6" );

 }


// ---------------------------------------------------
// Integrals of the elementary angular functions in phi, parametric acceptance.

Double_t KpiKpiSpectrumNW::Igi(Int_t i) const 
 { 

   if (i == 1) {return 2.*pi;}
   else if (i == 2) {return 0.;}
   else if (i == 3) {return 0.;}
   else if (i == 4) {return pi;}
   else if (i == 5) {return 0;}
   else if (i == 6) {return pi;}
   else if (i == 7) {return 0.;}
   else if (i == 8) {return 0.;}
   else if (i == 9) {return 0.;}
   else if (i == 10) {return 0.;}
   else if (i == 11) {return 0.;}
   else if (i == 12) {return 0.;}
   else if (i == 13) {return pi;}
   else if (i == 14) {return 0.;}
   else if (i == 15) {return pi;}

   throw std::invalid_argument( "Invalid argument #7" );

 }

// ---------------------------------------------------
// Integrals of the angular functions in cos(theta), parametric acceptance.

Double_t KpiKpiSpectrumNW::Ifjjphhp(Int_t j, Int_t jp, Int_t h, Int_t hp) const 
 { 

   return Ifi(fjjphhpindexdict[j][jp][h][hp]);

 }

// ---------------------------------------------------
// Integrals of the angular functions in phi, parametric acceptance.

Double_t KpiKpiSpectrumNW::Ighhp(Int_t h, Int_t hp) const 
 { 

   return Igi(ghhpindexdict[h][hp]);

 }

// ---------------------------------------------------
// Integrals of the invariant mass dependent functions, parametric acceptance.

TComplex KpiKpiSpectrumNW::Ihj1j2j1pj2p(Int_t j1, Int_t j2, Int_t j1p, Int_t j2p) const 
 { 

   return Ihj1j2j1pj2pdict[(int) year_opt][(int) trig_opt][j1][j2][j1p][j2p];

 }

// ######################################################################################################
// P D F   S E P A R A T E D   C O M P O N E N T S
// ######################################################################################################

// ---------------------------------------------------
// Components of the PDF used for fitting.

 Double_t KpiKpiSpectrumNW::comp_num_fit(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const 
 {
   return (Tj1j2hj1pj2php(t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS,j1,j2,h,j1p,j2p,hp)*Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*hj1j2j1pj2p(m1,m2,j1,j2,j1p,j2p)).Re()*ghhp_phi(h,hp)*fjjphhp_cos1(j1,j1p,h,hp)*fjjphhp_cos2(j2,j2p,h,hp);
 }

// ---------------------------------------------------
// Components of the PDF normalization integral used for fitting.

 Double_t KpiKpiSpectrumNW::comp_den_fit(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const 
 { 
   return (ITj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*TComplex(NW.comp(year_opt,trig_opt,wide_window,j1,j2,h,j1p,j2p,hp,0),NW.comp(year_opt,trig_opt,wide_window,j1,j2,h,j1p,j2p,hp,1))).Re();
 }

// ---------------------------------------------------
// Components of the PDF used for the plot on t.

 Double_t KpiKpiSpectrumNW::comp_num_plot_t(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const 
 { 
   return (Teffj1j2hj1pj2php(t,j1,j2,h,j1p,j2p,hp)*Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Ihj1j2j1pj2p(j1,j2,j1p,j2p)).Re()*Ighhp(h,hp)*Ifjjphhp(j1,j1p,h,hp)*Ifjjphhp(j2,j2p,h,hp)*accTime(t);
 }

// ---------------------------------------------------
// Components of the PDF used for the plot on phi.

 Double_t KpiKpiSpectrumNW::comp_num_plot_phi(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const 
 { 
   return (ITj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Ihj1j2j1pj2p(j1,j2,j1p,j2p)).Re()*ghhp(phi,h,hp)*Ifjjphhp(j1,j1p,h,hp)*Ifjjphhp(j2,j2p,h,hp);
 }

// ---------------------------------------------------
// Components of the PDF used for the plot on cos1.

 Double_t KpiKpiSpectrumNW::comp_num_plot_cos1(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const 
 { 
   return (ITj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Ihj1j2j1pj2p(j1,j2,j1p,j2p)).Re()*Ighhp(h,hp)*fjjphhp(cos1,j1,j1p,h,hp)*Ifjjphhp(j2,j2p,h,hp)*accAng(cos1);
 }

// ---------------------------------------------------
// Components of the PDF used for the plot on cos2.

 Double_t KpiKpiSpectrumNW::comp_num_plot_cos2(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const 
 { 
   return (ITj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Ihj1j2j1pj2p(j1,j2,j1p,j2p)).Re()*Ighhp(h,hp)*Ifjjphhp(j1,j1p,h,hp)*fjjphhp(cos2,j2,j2p,h,hp)*accAng(cos2);
 }

// ---------------------------------------------------
// Components of the PDF used for the plot on m1 and m2.

 Double_t KpiKpiSpectrumNW::comp_num_plot_m(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const 
 { 
   return (ITj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*hj1j2j1pj2p(m1,m2,j1,j2,j1p,j2p)).Re()*Ighhp(h,hp)*Ifjjphhp(j1,j1p,h,hp)*Ifjjphhp(j2,j2p,h,hp)*accMass(m1)*accMass(m2);
 }

// ---------------------------------------------------
// Components of the PDF normalization integral used for plotting.

 Double_t KpiKpiSpectrumNW::comp_den_plot(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const 
 { 
   return (ITj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Ihj1j2j1pj2p(j1,j2,j1p,j2p)).Re()*Ighhp(h,hp)*Ifjjphhp(j1,j1p,h,hp)*Ifjjphhp(j2,j2p,h,hp);
 }

// ---------------------------------------------------
// Real part of the components of the m1, m2, cos1, cos2 and phi funtion without the time dependent term.

 Double_t KpiKpiSpectrumNW::getReCompVal(Double_t ma, Double_t mb, Double_t cos1ang, Double_t cos2ang, Double_t phiang, Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const 
 { 
   set_buffer_differential_vars(ma,mb,cos1ang,cos2ang,phiang,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
   return (Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*hj1j2j1pj2p(ma,mb,j1,j2,j1p,j2p)).Re()*ghhp_phi(h,hp)*fjjphhp_cos1(j1,j1p,h,hp)*fjjphhp_cos2(j2,j2p,h,hp);
 }

// ---------------------------------------------------
// Imaginary part of the components of the m1, m2, cos1, cos2 and phi funtion without the time dependent term.

 Double_t KpiKpiSpectrumNW::getImCompVal(Double_t ma, Double_t mb, Double_t cos1ang, Double_t cos2ang, Double_t phiang, Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const 
 { 
   set_buffer_differential_vars(ma,mb,cos1ang,cos2ang,phiang,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
   return (Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*hj1j2j1pj2p(ma,mb,j1,j2,j1p,j2p)).Im()*ghhp_phi(h,hp)*fjjphhp_cos1(j1,j1p,h,hp)*fjjphhp_cos2(j2,j2p,h,hp);
 }

// ######################################################################################################
// C O M P L E T E   P D F
// ######################################################################################################

// ---------------------------------------------------
// Method to write down explicitly the sums over the components.

 void KpiKpiSpectrumNW::sumgenerator() const 
 { 

	for (Int_t j1=0; j1<3; j1++) {for (Int_t j2=0; j2<3; j2++) {for (Int_t h=0; h<5; h++) {
		if (Nj1j2hj1pj2php(j1,j2,h,j1,j2,h).Rho() != 0.) {
			cout << "comp("<<j1<<","<<j2<<","<<h<<","<<j1<<","<<j2<<","<<h<<")+";
		}
	}}}
	for (Int_t j1=0; j1<3; j1++) {for (Int_t j2=0; j2<3; j2++) {for (Int_t h=0; h<5; h++) {for (Int_t j1p=0; j1p<3; j1p++) {for (Int_t j2p=0; j2p<3; j2p++) {for (Int_t hp=0; hp<5; hp++) {
		if ((Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp).Rho() != 0.) and ((j1p+3*j2p+9*hp) < (j1+3*j2+9*h)) and (Ighhp(h,hp) != 0.)) {
			cout << "2.*comp("<<j1<<","<<j2<<","<<h<<","<<j1p<<","<<j2p<<","<<hp<<")+";
		}
	}}}}}}

	return;

 }

// ---------------------------------------------------
// PDF used for fitting.

 Double_t KpiKpiSpectrumNW::num_fit() const 
 {

   set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);

   return comp_num_fit(0,0,0,0,0,0)+comp_num_fit(0,1,0,0,1,0)+comp_num_fit(0,2,0,0,2,0)+comp_num_fit(1,0,0,1,0,0)+comp_num_fit(1,1,0,1,1,0)+comp_num_fit(1,1,1,1,1,1)
+comp_num_fit(1,1,2,1,1,2)+comp_num_fit(1,2,0,1,2,0)+comp_num_fit(1,2,1,1,2,1)+comp_num_fit(1,2,2,1,2,2)+comp_num_fit(2,0,0,2,0,0)+comp_num_fit(2,1,0,2,1,0)+comp_num_fit(2,1,1,2,1,1)
+comp_num_fit(2,1,2,2,1,2)+comp_num_fit(2,2,0,2,2,0)+comp_num_fit(2,2,1,2,2,1)+comp_num_fit(2,2,2,2,2,2)+comp_num_fit(2,2,3,2,2,3)+comp_num_fit(2,2,4,2,2,4)+2.*comp_num_fit(0,1,0,0,0,0)
+2.*comp_num_fit(0,1,0,1,0,0)+2.*comp_num_fit(0,1,0,2,0,0)+2.*comp_num_fit(0,2,0,0,0,0)+2.*comp_num_fit(0,2,0,0,1,0)+2.*comp_num_fit(0,2,0,1,0,0)+2.*comp_num_fit(0,2,0,1,1,0)
+2.*comp_num_fit(0,2,0,2,0,0)+2.*comp_num_fit(0,2,0,2,1,0)+2.*comp_num_fit(1,0,0,0,0,0)+2.*comp_num_fit(1,1,0,0,0,0)+2.*comp_num_fit(1,1,0,0,1,0)+2.*comp_num_fit(1,1,0,1,0,0)
+2.*comp_num_fit(1,1,0,2,0,0)+2.*comp_num_fit(1,1,1,0,0,0)+2.*comp_num_fit(1,1,1,0,1,0)+2.*comp_num_fit(1,1,1,0,2,0)+2.*comp_num_fit(1,1,1,1,0,0)+2.*comp_num_fit(1,1,1,1,1,0)
+2.*comp_num_fit(1,1,1,1,2,0)+2.*comp_num_fit(1,1,1,2,0,0)+2.*comp_num_fit(1,1,1,2,1,0)+2.*comp_num_fit(1,1,1,2,2,0)+2.*comp_num_fit(1,1,2,0,0,0)+2.*comp_num_fit(1,1,2,0,1,0)
+2.*comp_num_fit(1,1,2,0,2,0)+2.*comp_num_fit(1,1,2,1,0,0)+2.*comp_num_fit(1,1,2,1,1,0)+2.*comp_num_fit(1,1,2,1,1,1)+2.*comp_num_fit(1,1,2,1,2,0)+2.*comp_num_fit(1,1,2,1,2,1)
+2.*comp_num_fit(1,1,2,2,0,0)+2.*comp_num_fit(1,1,2,2,1,0)+2.*comp_num_fit(1,1,2,2,1,1)+2.*comp_num_fit(1,1,2,2,2,0)+2.*comp_num_fit(1,1,2,2,2,1)+2.*comp_num_fit(1,2,0,0,0,0)
+2.*comp_num_fit(1,2,0,0,1,0)+2.*comp_num_fit(1,2,0,0,2,0)+2.*comp_num_fit(1,2,0,1,0,0)+2.*comp_num_fit(1,2,0,1,1,0)+2.*comp_num_fit(1,2,0,2,0,0)+2.*comp_num_fit(1,2,0,2,1,0)
+2.*comp_num_fit(1,2,1,0,0,0)+2.*comp_num_fit(1,2,1,0,1,0)+2.*comp_num_fit(1,2,1,0,2,0)+2.*comp_num_fit(1,2,1,1,0,0)+2.*comp_num_fit(1,2,1,1,1,0)+2.*comp_num_fit(1,2,1,1,1,1)
+2.*comp_num_fit(1,2,1,1,2,0)+2.*comp_num_fit(1,2,1,2,0,0)+2.*comp_num_fit(1,2,1,2,1,0)+2.*comp_num_fit(1,2,1,2,1,1)+2.*comp_num_fit(1,2,1,2,2,0)+2.*comp_num_fit(1,2,2,0,0,0)
+2.*comp_num_fit(1,2,2,0,1,0)+2.*comp_num_fit(1,2,2,0,2,0)+2.*comp_num_fit(1,2,2,1,0,0)+2.*comp_num_fit(1,2,2,1,1,0)+2.*comp_num_fit(1,2,2,1,1,1)+2.*comp_num_fit(1,2,2,1,1,2)
+2.*comp_num_fit(1,2,2,1,2,0)+2.*comp_num_fit(1,2,2,1,2,1)+2.*comp_num_fit(1,2,2,2,0,0)+2.*comp_num_fit(1,2,2,2,1,0)+2.*comp_num_fit(1,2,2,2,1,1)+2.*comp_num_fit(1,2,2,2,1,2)
+2.*comp_num_fit(1,2,2,2,2,0)+2.*comp_num_fit(1,2,2,2,2,1)+2.*comp_num_fit(2,0,0,0,0,0)+2.*comp_num_fit(2,0,0,1,0,0)+2.*comp_num_fit(2,1,0,0,0,0)+2.*comp_num_fit(2,1,0,0,1,0)
+2.*comp_num_fit(2,1,0,1,0,0)+2.*comp_num_fit(2,1,0,1,1,0)+2.*comp_num_fit(2,1,0,2,0,0)+2.*comp_num_fit(2,1,1,0,0,0)+2.*comp_num_fit(2,1,1,0,1,0)+2.*comp_num_fit(2,1,1,0,2,0)
+2.*comp_num_fit(2,1,1,1,0,0)+2.*comp_num_fit(2,1,1,1,1,0)+2.*comp_num_fit(2,1,1,1,1,1)+2.*comp_num_fit(2,1,1,1,2,0)+2.*comp_num_fit(2,1,1,2,0,0)+2.*comp_num_fit(2,1,1,2,1,0)
+2.*comp_num_fit(2,1,1,2,2,0)+2.*comp_num_fit(2,1,2,0,0,0)+2.*comp_num_fit(2,1,2,0,1,0)+2.*comp_num_fit(2,1,2,0,2,0)+2.*comp_num_fit(2,1,2,1,0,0)+2.*comp_num_fit(2,1,2,1,1,0)
+2.*comp_num_fit(2,1,2,1,1,1)+2.*comp_num_fit(2,1,2,1,1,2)+2.*comp_num_fit(2,1,2,1,2,0)+2.*comp_num_fit(2,1,2,1,2,1)+2.*comp_num_fit(2,1,2,2,0,0)+2.*comp_num_fit(2,1,2,2,1,0)
+2.*comp_num_fit(2,1,2,2,1,1)+2.*comp_num_fit(2,1,2,2,2,0)+2.*comp_num_fit(2,1,2,2,2,1)+2.*comp_num_fit(2,2,0,0,0,0)+2.*comp_num_fit(2,2,0,0,1,0)+2.*comp_num_fit(2,2,0,0,2,0)
+2.*comp_num_fit(2,2,0,1,0,0)+2.*comp_num_fit(2,2,0,1,1,0)+2.*comp_num_fit(2,2,0,1,2,0)+2.*comp_num_fit(2,2,0,2,0,0)+2.*comp_num_fit(2,2,0,2,1,0)+2.*comp_num_fit(2,2,1,0,0,0)
+2.*comp_num_fit(2,2,1,0,1,0)+2.*comp_num_fit(2,2,1,0,2,0)+2.*comp_num_fit(2,2,1,1,0,0)+2.*comp_num_fit(2,2,1,1,1,0)+2.*comp_num_fit(2,2,1,1,1,1)+2.*comp_num_fit(2,2,1,1,2,0)
+2.*comp_num_fit(2,2,1,1,2,1)+2.*comp_num_fit(2,2,1,2,0,0)+2.*comp_num_fit(2,2,1,2,1,0)+2.*comp_num_fit(2,2,1,2,1,1)+2.*comp_num_fit(2,2,1,2,2,0)+2.*comp_num_fit(2,2,2,0,0,0)
+2.*comp_num_fit(2,2,2,0,1,0)+2.*comp_num_fit(2,2,2,0,2,0)+2.*comp_num_fit(2,2,2,1,0,0)+2.*comp_num_fit(2,2,2,1,1,0)+2.*comp_num_fit(2,2,2,1,1,1)+2.*comp_num_fit(2,2,2,1,1,2)
+2.*comp_num_fit(2,2,2,1,2,0)+2.*comp_num_fit(2,2,2,1,2,1)+2.*comp_num_fit(2,2,2,1,2,2)+2.*comp_num_fit(2,2,2,2,0,0)+2.*comp_num_fit(2,2,2,2,1,0)+2.*comp_num_fit(2,2,2,2,1,1)
+2.*comp_num_fit(2,2,2,2,1,2)+2.*comp_num_fit(2,2,2,2,2,0)+2.*comp_num_fit(2,2,2,2,2,1)+2.*comp_num_fit(2,2,3,0,0,0)+2.*comp_num_fit(2,2,3,0,1,0)+2.*comp_num_fit(2,2,3,0,2,0)
+2.*comp_num_fit(2,2,3,1,0,0)+2.*comp_num_fit(2,2,3,1,1,0)+2.*comp_num_fit(2,2,3,1,1,1)+2.*comp_num_fit(2,2,3,1,1,2)+2.*comp_num_fit(2,2,3,1,2,0)+2.*comp_num_fit(2,2,3,1,2,1)
+2.*comp_num_fit(2,2,3,1,2,2)+2.*comp_num_fit(2,2,3,2,0,0)+2.*comp_num_fit(2,2,3,2,1,0)+2.*comp_num_fit(2,2,3,2,1,1)+2.*comp_num_fit(2,2,3,2,1,2)+2.*comp_num_fit(2,2,3,2,2,0)
+2.*comp_num_fit(2,2,3,2,2,1)+2.*comp_num_fit(2,2,3,2,2,2)+2.*comp_num_fit(2,2,4,0,0,0)+2.*comp_num_fit(2,2,4,0,1,0)+2.*comp_num_fit(2,2,4,0,2,0)+2.*comp_num_fit(2,2,4,1,0,0)
+2.*comp_num_fit(2,2,4,1,1,0)+2.*comp_num_fit(2,2,4,1,1,1)+2.*comp_num_fit(2,2,4,1,1,2)+2.*comp_num_fit(2,2,4,1,2,0)+2.*comp_num_fit(2,2,4,1,2,1)+2.*comp_num_fit(2,2,4,1,2,2)
+2.*comp_num_fit(2,2,4,2,0,0)+2.*comp_num_fit(2,2,4,2,1,0)+2.*comp_num_fit(2,2,4,2,1,1)+2.*comp_num_fit(2,2,4,2,1,2)+2.*comp_num_fit(2,2,4,2,2,0)+2.*comp_num_fit(2,2,4,2,2,1)
+2.*comp_num_fit(2,2,4,2,2,2)+2.*comp_num_fit(2,2,4,2,2,3);

 }

// ---------------------------------------------------
// PDF normalization integral used for fitting.

 Double_t KpiKpiSpectrumNW::den_fit() const 
 {

   set_buffer_integral_vars();

   return comp_den_fit(0,0,0,0,0,0)+comp_den_fit(0,1,0,0,1,0)+comp_den_fit(0,2,0,0,2,0)+comp_den_fit(1,0,0,1,0,0)+comp_den_fit(1,1,0,1,1,0)+comp_den_fit(1,1,1,1,1,1)
+comp_den_fit(1,1,2,1,1,2)+comp_den_fit(1,2,0,1,2,0)+comp_den_fit(1,2,1,1,2,1)+comp_den_fit(1,2,2,1,2,2)+comp_den_fit(2,0,0,2,0,0)+comp_den_fit(2,1,0,2,1,0)+comp_den_fit(2,1,1,2,1,1)
+comp_den_fit(2,1,2,2,1,2)+comp_den_fit(2,2,0,2,2,0)+comp_den_fit(2,2,1,2,2,1)+comp_den_fit(2,2,2,2,2,2)+comp_den_fit(2,2,3,2,2,3)+comp_den_fit(2,2,4,2,2,4)+2.*comp_den_fit(0,1,0,0,0,0)
+2.*comp_den_fit(0,1,0,1,0,0)+2.*comp_den_fit(0,1,0,2,0,0)+2.*comp_den_fit(0,2,0,0,0,0)+2.*comp_den_fit(0,2,0,0,1,0)+2.*comp_den_fit(0,2,0,1,0,0)+2.*comp_den_fit(0,2,0,1,1,0)
+2.*comp_den_fit(0,2,0,2,0,0)+2.*comp_den_fit(0,2,0,2,1,0)+2.*comp_den_fit(1,0,0,0,0,0)+2.*comp_den_fit(1,1,0,0,0,0)+2.*comp_den_fit(1,1,0,0,1,0)+2.*comp_den_fit(1,1,0,1,0,0)
+2.*comp_den_fit(1,1,0,2,0,0)+2.*comp_den_fit(1,1,1,0,0,0)+2.*comp_den_fit(1,1,1,0,1,0)+2.*comp_den_fit(1,1,1,0,2,0)+2.*comp_den_fit(1,1,1,1,0,0)+2.*comp_den_fit(1,1,1,1,1,0)
+2.*comp_den_fit(1,1,1,1,2,0)+2.*comp_den_fit(1,1,1,2,0,0)+2.*comp_den_fit(1,1,1,2,1,0)+2.*comp_den_fit(1,1,1,2,2,0)+2.*comp_den_fit(1,1,2,0,0,0)+2.*comp_den_fit(1,1,2,0,1,0)
+2.*comp_den_fit(1,1,2,0,2,0)+2.*comp_den_fit(1,1,2,1,0,0)+2.*comp_den_fit(1,1,2,1,1,0)+2.*comp_den_fit(1,1,2,1,1,1)+2.*comp_den_fit(1,1,2,1,2,0)+2.*comp_den_fit(1,1,2,1,2,1)
+2.*comp_den_fit(1,1,2,2,0,0)+2.*comp_den_fit(1,1,2,2,1,0)+2.*comp_den_fit(1,1,2,2,1,1)+2.*comp_den_fit(1,1,2,2,2,0)+2.*comp_den_fit(1,1,2,2,2,1)+2.*comp_den_fit(1,2,0,0,0,0)
+2.*comp_den_fit(1,2,0,0,1,0)+2.*comp_den_fit(1,2,0,0,2,0)+2.*comp_den_fit(1,2,0,1,0,0)+2.*comp_den_fit(1,2,0,1,1,0)+2.*comp_den_fit(1,2,0,2,0,0)+2.*comp_den_fit(1,2,0,2,1,0)
+2.*comp_den_fit(1,2,1,0,0,0)+2.*comp_den_fit(1,2,1,0,1,0)+2.*comp_den_fit(1,2,1,0,2,0)+2.*comp_den_fit(1,2,1,1,0,0)+2.*comp_den_fit(1,2,1,1,1,0)+2.*comp_den_fit(1,2,1,1,1,1)
+2.*comp_den_fit(1,2,1,1,2,0)+2.*comp_den_fit(1,2,1,2,0,0)+2.*comp_den_fit(1,2,1,2,1,0)+2.*comp_den_fit(1,2,1,2,1,1)+2.*comp_den_fit(1,2,1,2,2,0)+2.*comp_den_fit(1,2,2,0,0,0)
+2.*comp_den_fit(1,2,2,0,1,0)+2.*comp_den_fit(1,2,2,0,2,0)+2.*comp_den_fit(1,2,2,1,0,0)+2.*comp_den_fit(1,2,2,1,1,0)+2.*comp_den_fit(1,2,2,1,1,1)+2.*comp_den_fit(1,2,2,1,1,2)
+2.*comp_den_fit(1,2,2,1,2,0)+2.*comp_den_fit(1,2,2,1,2,1)+2.*comp_den_fit(1,2,2,2,0,0)+2.*comp_den_fit(1,2,2,2,1,0)+2.*comp_den_fit(1,2,2,2,1,1)+2.*comp_den_fit(1,2,2,2,1,2)
+2.*comp_den_fit(1,2,2,2,2,0)+2.*comp_den_fit(1,2,2,2,2,1)+2.*comp_den_fit(2,0,0,0,0,0)+2.*comp_den_fit(2,0,0,1,0,0)+2.*comp_den_fit(2,1,0,0,0,0)+2.*comp_den_fit(2,1,0,0,1,0)
+2.*comp_den_fit(2,1,0,1,0,0)+2.*comp_den_fit(2,1,0,1,1,0)+2.*comp_den_fit(2,1,0,2,0,0)+2.*comp_den_fit(2,1,1,0,0,0)+2.*comp_den_fit(2,1,1,0,1,0)+2.*comp_den_fit(2,1,1,0,2,0)
+2.*comp_den_fit(2,1,1,1,0,0)+2.*comp_den_fit(2,1,1,1,1,0)+2.*comp_den_fit(2,1,1,1,1,1)+2.*comp_den_fit(2,1,1,1,2,0)+2.*comp_den_fit(2,1,1,2,0,0)+2.*comp_den_fit(2,1,1,2,1,0)
+2.*comp_den_fit(2,1,1,2,2,0)+2.*comp_den_fit(2,1,2,0,0,0)+2.*comp_den_fit(2,1,2,0,1,0)+2.*comp_den_fit(2,1,2,0,2,0)+2.*comp_den_fit(2,1,2,1,0,0)+2.*comp_den_fit(2,1,2,1,1,0)
+2.*comp_den_fit(2,1,2,1,1,1)+2.*comp_den_fit(2,1,2,1,1,2)+2.*comp_den_fit(2,1,2,1,2,0)+2.*comp_den_fit(2,1,2,1,2,1)+2.*comp_den_fit(2,1,2,2,0,0)+2.*comp_den_fit(2,1,2,2,1,0)
+2.*comp_den_fit(2,1,2,2,1,1)+2.*comp_den_fit(2,1,2,2,2,0)+2.*comp_den_fit(2,1,2,2,2,1)+2.*comp_den_fit(2,2,0,0,0,0)+2.*comp_den_fit(2,2,0,0,1,0)+2.*comp_den_fit(2,2,0,0,2,0)
+2.*comp_den_fit(2,2,0,1,0,0)+2.*comp_den_fit(2,2,0,1,1,0)+2.*comp_den_fit(2,2,0,1,2,0)+2.*comp_den_fit(2,2,0,2,0,0)+2.*comp_den_fit(2,2,0,2,1,0)+2.*comp_den_fit(2,2,1,0,0,0)
+2.*comp_den_fit(2,2,1,0,1,0)+2.*comp_den_fit(2,2,1,0,2,0)+2.*comp_den_fit(2,2,1,1,0,0)+2.*comp_den_fit(2,2,1,1,1,0)+2.*comp_den_fit(2,2,1,1,1,1)+2.*comp_den_fit(2,2,1,1,2,0)
+2.*comp_den_fit(2,2,1,1,2,1)+2.*comp_den_fit(2,2,1,2,0,0)+2.*comp_den_fit(2,2,1,2,1,0)+2.*comp_den_fit(2,2,1,2,1,1)+2.*comp_den_fit(2,2,1,2,2,0)+2.*comp_den_fit(2,2,2,0,0,0)
+2.*comp_den_fit(2,2,2,0,1,0)+2.*comp_den_fit(2,2,2,0,2,0)+2.*comp_den_fit(2,2,2,1,0,0)+2.*comp_den_fit(2,2,2,1,1,0)+2.*comp_den_fit(2,2,2,1,1,1)+2.*comp_den_fit(2,2,2,1,1,2)
+2.*comp_den_fit(2,2,2,1,2,0)+2.*comp_den_fit(2,2,2,1,2,1)+2.*comp_den_fit(2,2,2,1,2,2)+2.*comp_den_fit(2,2,2,2,0,0)+2.*comp_den_fit(2,2,2,2,1,0)+2.*comp_den_fit(2,2,2,2,1,1)
+2.*comp_den_fit(2,2,2,2,1,2)+2.*comp_den_fit(2,2,2,2,2,0)+2.*comp_den_fit(2,2,2,2,2,1)+2.*comp_den_fit(2,2,3,0,0,0)+2.*comp_den_fit(2,2,3,0,1,0)+2.*comp_den_fit(2,2,3,0,2,0)
+2.*comp_den_fit(2,2,3,1,0,0)+2.*comp_den_fit(2,2,3,1,1,0)+2.*comp_den_fit(2,2,3,1,1,1)+2.*comp_den_fit(2,2,3,1,1,2)+2.*comp_den_fit(2,2,3,1,2,0)+2.*comp_den_fit(2,2,3,1,2,1)
+2.*comp_den_fit(2,2,3,1,2,2)+2.*comp_den_fit(2,2,3,2,0,0)+2.*comp_den_fit(2,2,3,2,1,0)+2.*comp_den_fit(2,2,3,2,1,1)+2.*comp_den_fit(2,2,3,2,1,2)+2.*comp_den_fit(2,2,3,2,2,0)
+2.*comp_den_fit(2,2,3,2,2,1)+2.*comp_den_fit(2,2,3,2,2,2)+2.*comp_den_fit(2,2,4,0,0,0)+2.*comp_den_fit(2,2,4,0,1,0)+2.*comp_den_fit(2,2,4,0,2,0)+2.*comp_den_fit(2,2,4,1,0,0)
+2.*comp_den_fit(2,2,4,1,1,0)+2.*comp_den_fit(2,2,4,1,1,1)+2.*comp_den_fit(2,2,4,1,1,2)+2.*comp_den_fit(2,2,4,1,2,0)+2.*comp_den_fit(2,2,4,1,2,1)+2.*comp_den_fit(2,2,4,1,2,2)
+2.*comp_den_fit(2,2,4,2,0,0)+2.*comp_den_fit(2,2,4,2,1,0)+2.*comp_den_fit(2,2,4,2,1,1)+2.*comp_den_fit(2,2,4,2,1,2)+2.*comp_den_fit(2,2,4,2,2,0)+2.*comp_den_fit(2,2,4,2,2,1)
+2.*comp_den_fit(2,2,4,2,2,2)+2.*comp_den_fit(2,2,4,2,2,3);

 }

// ---------------------------------------------------
// PDF normalization integral used for plotting.

 Double_t KpiKpiSpectrumNW::den_plot() const 
 {

   set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
   set_buffer_integral_vars();

   return comp_den_plot(0,0,0,0,0,0)+comp_den_plot(0,1,0,0,1,0)+comp_den_plot(0,2,0,0,2,0)+comp_den_plot(1,0,0,1,0,0)+comp_den_plot(1,1,0,1,1,0)
+comp_den_plot(1,1,1,1,1,1)+comp_den_plot(1,1,2,1,1,2)+comp_den_plot(1,2,0,1,2,0)+comp_den_plot(1,2,1,1,2,1)+comp_den_plot(1,2,2,1,2,2)
+comp_den_plot(2,0,0,2,0,0)+comp_den_plot(2,1,0,2,1,0)+comp_den_plot(2,1,1,2,1,1)+comp_den_plot(2,1,2,2,1,2)+comp_den_plot(2,2,0,2,2,0)
+comp_den_plot(2,2,1,2,2,1)+comp_den_plot(2,2,2,2,2,2)+comp_den_plot(2,2,3,2,2,3)+comp_den_plot(2,2,4,2,2,4)+2.*comp_den_plot(0,1,0,0,0,0)
+2.*comp_den_plot(0,1,0,1,0,0)+2.*comp_den_plot(0,1,0,2,0,0)+2.*comp_den_plot(0,2,0,0,0,0)+2.*comp_den_plot(0,2,0,0,1,0)+2.*comp_den_plot(0,2,0,1,0,0)
+2.*comp_den_plot(0,2,0,1,1,0)+2.*comp_den_plot(0,2,0,2,0,0)+2.*comp_den_plot(0,2,0,2,1,0)+2.*comp_den_plot(1,0,0,0,0,0)+2.*comp_den_plot(1,1,0,0,0,0)
+2.*comp_den_plot(1,1,0,0,1,0)+2.*comp_den_plot(1,1,0,1,0,0)+2.*comp_den_plot(1,1,0,2,0,0)+2.*comp_den_plot(1,2,0,0,0,0)+2.*comp_den_plot(1,2,0,0,1,0)
+2.*comp_den_plot(1,2,0,0,2,0)+2.*comp_den_plot(1,2,0,1,0,0)+2.*comp_den_plot(1,2,0,1,1,0)+2.*comp_den_plot(1,2,0,2,0,0)+2.*comp_den_plot(1,2,0,2,1,0)
+2.*comp_den_plot(1,2,1,1,1,1)+2.*comp_den_plot(1,2,1,2,1,1)+2.*comp_den_plot(1,2,2,1,1,2)+2.*comp_den_plot(1,2,2,2,1,2)+2.*comp_den_plot(2,0,0,0,0,0)
+2.*comp_den_plot(2,0,0,1,0,0)+2.*comp_den_plot(2,1,0,0,0,0)+2.*comp_den_plot(2,1,0,0,1,0)+2.*comp_den_plot(2,1,0,1,0,0)+2.*comp_den_plot(2,1,0,1,1,0)
+2.*comp_den_plot(2,1,0,2,0,0)+2.*comp_den_plot(2,1,1,1,1,1)+2.*comp_den_plot(2,1,2,1,1,2)+2.*comp_den_plot(2,2,0,0,0,0)+2.*comp_den_plot(2,2,0,0,1,0)
+2.*comp_den_plot(2,2,0,0,2,0)+2.*comp_den_plot(2,2,0,1,0,0)+2.*comp_den_plot(2,2,0,1,1,0)+2.*comp_den_plot(2,2,0,1,2,0)+2.*comp_den_plot(2,2,0,2,0,0)
+2.*comp_den_plot(2,2,0,2,1,0)+2.*comp_den_plot(2,2,1,1,1,1)+2.*comp_den_plot(2,2,1,1,2,1)+2.*comp_den_plot(2,2,1,2,1,1)+2.*comp_den_plot(2,2,2,1,1,2)
+2.*comp_den_plot(2,2,2,1,2,2)+2.*comp_den_plot(2,2,2,2,1,2);

 }

// ---------------------------------------------------
// PDF used for the plot on t.

 Double_t KpiKpiSpectrumNW::num_plot_t() const 
 {

   set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
   set_buffer_integral_vars();

   return comp_num_plot_t(0,0,0,0,0,0)+comp_num_plot_t(0,1,0,0,1,0)+comp_num_plot_t(0,2,0,0,2,0)+comp_num_plot_t(1,0,0,1,0,0)+comp_num_plot_t(1,1,0,1,1,0)
+comp_num_plot_t(1,1,1,1,1,1)+comp_num_plot_t(1,1,2,1,1,2)+comp_num_plot_t(1,2,0,1,2,0)+comp_num_plot_t(1,2,1,1,2,1)+comp_num_plot_t(1,2,2,1,2,2)
+comp_num_plot_t(2,0,0,2,0,0)+comp_num_plot_t(2,1,0,2,1,0)+comp_num_plot_t(2,1,1,2,1,1)+comp_num_plot_t(2,1,2,2,1,2)+comp_num_plot_t(2,2,0,2,2,0)
+comp_num_plot_t(2,2,1,2,2,1)+comp_num_plot_t(2,2,2,2,2,2)+comp_num_plot_t(2,2,3,2,2,3)+comp_num_plot_t(2,2,4,2,2,4)+2.*comp_num_plot_t(0,1,0,0,0,0)
+2.*comp_num_plot_t(0,1,0,1,0,0)+2.*comp_num_plot_t(0,1,0,2,0,0)+2.*comp_num_plot_t(0,2,0,0,0,0)+2.*comp_num_plot_t(0,2,0,0,1,0)+2.*comp_num_plot_t(0,2,0,1,0,0)
+2.*comp_num_plot_t(0,2,0,1,1,0)+2.*comp_num_plot_t(0,2,0,2,0,0)+2.*comp_num_plot_t(0,2,0,2,1,0)+2.*comp_num_plot_t(1,0,0,0,0,0)+2.*comp_num_plot_t(1,1,0,0,0,0)
+2.*comp_num_plot_t(1,1,0,0,1,0)+2.*comp_num_plot_t(1,1,0,1,0,0)+2.*comp_num_plot_t(1,1,0,2,0,0)+2.*comp_num_plot_t(1,2,0,0,0,0)+2.*comp_num_plot_t(1,2,0,0,1,0)
+2.*comp_num_plot_t(1,2,0,0,2,0)+2.*comp_num_plot_t(1,2,0,1,0,0)+2.*comp_num_plot_t(1,2,0,1,1,0)+2.*comp_num_plot_t(1,2,0,2,0,0)+2.*comp_num_plot_t(1,2,0,2,1,0)
+2.*comp_num_plot_t(1,2,1,1,1,1)+2.*comp_num_plot_t(1,2,1,2,1,1)+2.*comp_num_plot_t(1,2,2,1,1,2)+2.*comp_num_plot_t(1,2,2,2,1,2)+2.*comp_num_plot_t(2,0,0,0,0,0)
+2.*comp_num_plot_t(2,0,0,1,0,0)+2.*comp_num_plot_t(2,1,0,0,0,0)+2.*comp_num_plot_t(2,1,0,0,1,0)+2.*comp_num_plot_t(2,1,0,1,0,0)+2.*comp_num_plot_t(2,1,0,1,1,0)
+2.*comp_num_plot_t(2,1,0,2,0,0)+2.*comp_num_plot_t(2,1,1,1,1,1)+2.*comp_num_plot_t(2,1,2,1,1,2)+2.*comp_num_plot_t(2,2,0,0,0,0)+2.*comp_num_plot_t(2,2,0,0,1,0)
+2.*comp_num_plot_t(2,2,0,0,2,0)+2.*comp_num_plot_t(2,2,0,1,0,0)+2.*comp_num_plot_t(2,2,0,1,1,0)+2.*comp_num_plot_t(2,2,0,1,2,0)+2.*comp_num_plot_t(2,2,0,2,0,0)
+2.*comp_num_plot_t(2,2,0,2,1,0)+2.*comp_num_plot_t(2,2,1,1,1,1)+2.*comp_num_plot_t(2,2,1,1,2,1)+2.*comp_num_plot_t(2,2,1,2,1,1)+2.*comp_num_plot_t(2,2,2,1,1,2)
+2.*comp_num_plot_t(2,2,2,1,2,2)+2.*comp_num_plot_t(2,2,2,2,1,2);

 }

// ---------------------------------------------------
// PDF used for the plot on phi.

 Double_t KpiKpiSpectrumNW::num_plot_phi() const 
 {

   set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
   set_buffer_integral_vars();

   return comp_num_plot_phi(0,0,0,0,0,0)+comp_num_plot_phi(0,1,0,0,1,0)+comp_num_plot_phi(0,2,0,0,2,0)+comp_num_plot_phi(1,0,0,1,0,0)+comp_num_plot_phi(1,1,0,1,1,0)+comp_num_plot_phi(1,1,1,1,1,1)
+comp_num_plot_phi(1,1,2,1,1,2)+comp_num_plot_phi(1,2,0,1,2,0)+comp_num_plot_phi(1,2,1,1,2,1)+comp_num_plot_phi(1,2,2,1,2,2)+comp_num_plot_phi(2,0,0,2,0,0)+comp_num_plot_phi(2,1,0,2,1,0)+comp_num_plot_phi(2,1,1,2,1,1)
+comp_num_plot_phi(2,1,2,2,1,2)+comp_num_plot_phi(2,2,0,2,2,0)+comp_num_plot_phi(2,2,1,2,2,1)+comp_num_plot_phi(2,2,2,2,2,2)+comp_num_plot_phi(2,2,3,2,2,3)+comp_num_plot_phi(2,2,4,2,2,4)+2.*comp_num_plot_phi(0,1,0,0,0,0)
+2.*comp_num_plot_phi(0,1,0,1,0,0)+2.*comp_num_plot_phi(0,1,0,2,0,0)+2.*comp_num_plot_phi(0,2,0,0,0,0)+2.*comp_num_plot_phi(0,2,0,0,1,0)+2.*comp_num_plot_phi(0,2,0,1,0,0)+2.*comp_num_plot_phi(0,2,0,1,1,0)
+2.*comp_num_plot_phi(0,2,0,2,0,0)+2.*comp_num_plot_phi(0,2,0,2,1,0)+2.*comp_num_plot_phi(1,0,0,0,0,0)+2.*comp_num_plot_phi(1,1,0,0,0,0)+2.*comp_num_plot_phi(1,1,0,0,1,0)+2.*comp_num_plot_phi(1,1,0,1,0,0)
+2.*comp_num_plot_phi(1,1,0,2,0,0)+2.*comp_num_plot_phi(1,1,1,0,0,0)+2.*comp_num_plot_phi(1,1,1,0,1,0)+2.*comp_num_plot_phi(1,1,1,0,2,0)+2.*comp_num_plot_phi(1,1,1,1,0,0)+2.*comp_num_plot_phi(1,1,1,1,1,0)
+2.*comp_num_plot_phi(1,1,1,1,2,0)+2.*comp_num_plot_phi(1,1,1,2,0,0)+2.*comp_num_plot_phi(1,1,1,2,1,0)+2.*comp_num_plot_phi(1,1,1,2,2,0)+2.*comp_num_plot_phi(1,1,2,0,0,0)+2.*comp_num_plot_phi(1,1,2,0,1,0)
+2.*comp_num_plot_phi(1,1,2,0,2,0)+2.*comp_num_plot_phi(1,1,2,1,0,0)+2.*comp_num_plot_phi(1,1,2,1,1,0)+2.*comp_num_plot_phi(1,1,2,1,1,1)+2.*comp_num_plot_phi(1,1,2,1,2,0)+2.*comp_num_plot_phi(1,1,2,1,2,1)
+2.*comp_num_plot_phi(1,1,2,2,0,0)+2.*comp_num_plot_phi(1,1,2,2,1,0)+2.*comp_num_plot_phi(1,1,2,2,1,1)+2.*comp_num_plot_phi(1,1,2,2,2,0)+2.*comp_num_plot_phi(1,1,2,2,2,1)+2.*comp_num_plot_phi(1,2,0,0,0,0)
+2.*comp_num_plot_phi(1,2,0,0,1,0)+2.*comp_num_plot_phi(1,2,0,0,2,0)+2.*comp_num_plot_phi(1,2,0,1,0,0)+2.*comp_num_plot_phi(1,2,0,1,1,0)+2.*comp_num_plot_phi(1,2,0,2,0,0)+2.*comp_num_plot_phi(1,2,0,2,1,0)
+2.*comp_num_plot_phi(1,2,1,0,0,0)+2.*comp_num_plot_phi(1,2,1,0,1,0)+2.*comp_num_plot_phi(1,2,1,0,2,0)+2.*comp_num_plot_phi(1,2,1,1,0,0)+2.*comp_num_plot_phi(1,2,1,1,1,0)+2.*comp_num_plot_phi(1,2,1,1,1,1)
+2.*comp_num_plot_phi(1,2,1,1,2,0)+2.*comp_num_plot_phi(1,2,1,2,0,0)+2.*comp_num_plot_phi(1,2,1,2,1,0)+2.*comp_num_plot_phi(1,2,1,2,1,1)+2.*comp_num_plot_phi(1,2,1,2,2,0)+2.*comp_num_plot_phi(1,2,2,0,0,0)
+2.*comp_num_plot_phi(1,2,2,0,1,0)+2.*comp_num_plot_phi(1,2,2,0,2,0)+2.*comp_num_plot_phi(1,2,2,1,0,0)+2.*comp_num_plot_phi(1,2,2,1,1,0)+2.*comp_num_plot_phi(1,2,2,1,1,1)+2.*comp_num_plot_phi(1,2,2,1,1,2)
+2.*comp_num_plot_phi(1,2,2,1,2,0)+2.*comp_num_plot_phi(1,2,2,1,2,1)+2.*comp_num_plot_phi(1,2,2,2,0,0)+2.*comp_num_plot_phi(1,2,2,2,1,0)+2.*comp_num_plot_phi(1,2,2,2,1,1)+2.*comp_num_plot_phi(1,2,2,2,1,2)
+2.*comp_num_plot_phi(1,2,2,2,2,0)+2.*comp_num_plot_phi(1,2,2,2,2,1)+2.*comp_num_plot_phi(2,0,0,0,0,0)+2.*comp_num_plot_phi(2,0,0,1,0,0)+2.*comp_num_plot_phi(2,1,0,0,0,0)+2.*comp_num_plot_phi(2,1,0,0,1,0)
+2.*comp_num_plot_phi(2,1,0,1,0,0)+2.*comp_num_plot_phi(2,1,0,1,1,0)+2.*comp_num_plot_phi(2,1,0,2,0,0)+2.*comp_num_plot_phi(2,1,1,0,0,0)+2.*comp_num_plot_phi(2,1,1,0,1,0)+2.*comp_num_plot_phi(2,1,1,0,2,0)
+2.*comp_num_plot_phi(2,1,1,1,0,0)+2.*comp_num_plot_phi(2,1,1,1,1,0)+2.*comp_num_plot_phi(2,1,1,1,1,1)+2.*comp_num_plot_phi(2,1,1,1,2,0)+2.*comp_num_plot_phi(2,1,1,2,0,0)+2.*comp_num_plot_phi(2,1,1,2,1,0)
+2.*comp_num_plot_phi(2,1,1,2,2,0)+2.*comp_num_plot_phi(2,1,2,0,0,0)+2.*comp_num_plot_phi(2,1,2,0,1,0)+2.*comp_num_plot_phi(2,1,2,0,2,0)+2.*comp_num_plot_phi(2,1,2,1,0,0)+2.*comp_num_plot_phi(2,1,2,1,1,0)
+2.*comp_num_plot_phi(2,1,2,1,1,1)+2.*comp_num_plot_phi(2,1,2,1,1,2)+2.*comp_num_plot_phi(2,1,2,1,2,0)+2.*comp_num_plot_phi(2,1,2,1,2,1)+2.*comp_num_plot_phi(2,1,2,2,0,0)+2.*comp_num_plot_phi(2,1,2,2,1,0)
+2.*comp_num_plot_phi(2,1,2,2,1,1)+2.*comp_num_plot_phi(2,1,2,2,2,0)+2.*comp_num_plot_phi(2,1,2,2,2,1)+2.*comp_num_plot_phi(2,2,0,0,0,0)+2.*comp_num_plot_phi(2,2,0,0,1,0)+2.*comp_num_plot_phi(2,2,0,0,2,0)
+2.*comp_num_plot_phi(2,2,0,1,0,0)+2.*comp_num_plot_phi(2,2,0,1,1,0)+2.*comp_num_plot_phi(2,2,0,1,2,0)+2.*comp_num_plot_phi(2,2,0,2,0,0)+2.*comp_num_plot_phi(2,2,0,2,1,0)+2.*comp_num_plot_phi(2,2,1,0,0,0)
+2.*comp_num_plot_phi(2,2,1,0,1,0)+2.*comp_num_plot_phi(2,2,1,0,2,0)+2.*comp_num_plot_phi(2,2,1,1,0,0)+2.*comp_num_plot_phi(2,2,1,1,1,0)+2.*comp_num_plot_phi(2,2,1,1,1,1)+2.*comp_num_plot_phi(2,2,1,1,2,0)
+2.*comp_num_plot_phi(2,2,1,1,2,1)+2.*comp_num_plot_phi(2,2,1,2,0,0)+2.*comp_num_plot_phi(2,2,1,2,1,0)+2.*comp_num_plot_phi(2,2,1,2,1,1)+2.*comp_num_plot_phi(2,2,1,2,2,0)+2.*comp_num_plot_phi(2,2,2,0,0,0)
+2.*comp_num_plot_phi(2,2,2,0,1,0)+2.*comp_num_plot_phi(2,2,2,0,2,0)+2.*comp_num_plot_phi(2,2,2,1,0,0)+2.*comp_num_plot_phi(2,2,2,1,1,0)+2.*comp_num_plot_phi(2,2,2,1,1,1)+2.*comp_num_plot_phi(2,2,2,1,1,2)
+2.*comp_num_plot_phi(2,2,2,1,2,0)+2.*comp_num_plot_phi(2,2,2,1,2,1)+2.*comp_num_plot_phi(2,2,2,1,2,2)+2.*comp_num_plot_phi(2,2,2,2,0,0)+2.*comp_num_plot_phi(2,2,2,2,1,0)+2.*comp_num_plot_phi(2,2,2,2,1,1)
+2.*comp_num_plot_phi(2,2,2,2,1,2)+2.*comp_num_plot_phi(2,2,2,2,2,0)+2.*comp_num_plot_phi(2,2,2,2,2,1)+2.*comp_num_plot_phi(2,2,3,0,0,0)+2.*comp_num_plot_phi(2,2,3,0,1,0)+2.*comp_num_plot_phi(2,2,3,0,2,0)
+2.*comp_num_plot_phi(2,2,3,1,0,0)+2.*comp_num_plot_phi(2,2,3,1,1,0)+2.*comp_num_plot_phi(2,2,3,1,1,1)+2.*comp_num_plot_phi(2,2,3,1,1,2)+2.*comp_num_plot_phi(2,2,3,1,2,0)+2.*comp_num_plot_phi(2,2,3,1,2,1)
+2.*comp_num_plot_phi(2,2,3,1,2,2)+2.*comp_num_plot_phi(2,2,3,2,0,0)+2.*comp_num_plot_phi(2,2,3,2,1,0)+2.*comp_num_plot_phi(2,2,3,2,1,1)+2.*comp_num_plot_phi(2,2,3,2,1,2)+2.*comp_num_plot_phi(2,2,3,2,2,0)
+2.*comp_num_plot_phi(2,2,3,2,2,1)+2.*comp_num_plot_phi(2,2,3,2,2,2)+2.*comp_num_plot_phi(2,2,4,0,0,0)+2.*comp_num_plot_phi(2,2,4,0,1,0)+2.*comp_num_plot_phi(2,2,4,0,2,0)+2.*comp_num_plot_phi(2,2,4,1,0,0)
+2.*comp_num_plot_phi(2,2,4,1,1,0)+2.*comp_num_plot_phi(2,2,4,1,1,1)+2.*comp_num_plot_phi(2,2,4,1,1,2)+2.*comp_num_plot_phi(2,2,4,1,2,0)+2.*comp_num_plot_phi(2,2,4,1,2,1)+2.*comp_num_plot_phi(2,2,4,1,2,2)
+2.*comp_num_plot_phi(2,2,4,2,0,0)+2.*comp_num_plot_phi(2,2,4,2,1,0)+2.*comp_num_plot_phi(2,2,4,2,1,1)+2.*comp_num_plot_phi(2,2,4,2,1,2)+2.*comp_num_plot_phi(2,2,4,2,2,0)+2.*comp_num_plot_phi(2,2,4,2,2,1)
+2.*comp_num_plot_phi(2,2,4,2,2,2)+2.*comp_num_plot_phi(2,2,4,2,2,3);

 }

// ---------------------------------------------------
// PDF used for the plot on cos1.

 Double_t KpiKpiSpectrumNW::num_plot_cos1() const 
 {

   set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
   set_buffer_integral_vars();

   return comp_num_plot_cos1(0,0,0,0,0,0)+comp_num_plot_cos1(0,1,0,0,1,0)+comp_num_plot_cos1(0,2,0,0,2,0)+comp_num_plot_cos1(1,0,0,1,0,0)+comp_num_plot_cos1(1,1,0,1,1,0)
+comp_num_plot_cos1(1,1,1,1,1,1)+comp_num_plot_cos1(1,1,2,1,1,2)+comp_num_plot_cos1(1,2,0,1,2,0)+comp_num_plot_cos1(1,2,1,1,2,1)+comp_num_plot_cos1(1,2,2,1,2,2)
+comp_num_plot_cos1(2,0,0,2,0,0)+comp_num_plot_cos1(2,1,0,2,1,0)+comp_num_plot_cos1(2,1,1,2,1,1)+comp_num_plot_cos1(2,1,2,2,1,2)+comp_num_plot_cos1(2,2,0,2,2,0)
+comp_num_plot_cos1(2,2,1,2,2,1)+comp_num_plot_cos1(2,2,2,2,2,2)+comp_num_plot_cos1(2,2,3,2,2,3)+comp_num_plot_cos1(2,2,4,2,2,4)+2.*comp_num_plot_cos1(0,1,0,0,0,0)
+2.*comp_num_plot_cos1(0,1,0,1,0,0)+2.*comp_num_plot_cos1(0,1,0,2,0,0)+2.*comp_num_plot_cos1(0,2,0,0,0,0)+2.*comp_num_plot_cos1(0,2,0,0,1,0)+2.*comp_num_plot_cos1(0,2,0,1,0,0)
+2.*comp_num_plot_cos1(0,2,0,1,1,0)+2.*comp_num_plot_cos1(0,2,0,2,0,0)+2.*comp_num_plot_cos1(0,2,0,2,1,0)+2.*comp_num_plot_cos1(1,0,0,0,0,0)+2.*comp_num_plot_cos1(1,1,0,0,0,0)
+2.*comp_num_plot_cos1(1,1,0,0,1,0)+2.*comp_num_plot_cos1(1,1,0,1,0,0)+2.*comp_num_plot_cos1(1,1,0,2,0,0)+2.*comp_num_plot_cos1(1,2,0,0,0,0)+2.*comp_num_plot_cos1(1,2,0,0,1,0)
+2.*comp_num_plot_cos1(1,2,0,0,2,0)+2.*comp_num_plot_cos1(1,2,0,1,0,0)+2.*comp_num_plot_cos1(1,2,0,1,1,0)+2.*comp_num_plot_cos1(1,2,0,2,0,0)+2.*comp_num_plot_cos1(1,2,0,2,1,0)
+2.*comp_num_plot_cos1(1,2,1,1,1,1)+2.*comp_num_plot_cos1(1,2,1,2,1,1)+2.*comp_num_plot_cos1(1,2,2,1,1,2)+2.*comp_num_plot_cos1(1,2,2,2,1,2)+2.*comp_num_plot_cos1(2,0,0,0,0,0)
+2.*comp_num_plot_cos1(2,0,0,1,0,0)+2.*comp_num_plot_cos1(2,1,0,0,0,0)+2.*comp_num_plot_cos1(2,1,0,0,1,0)+2.*comp_num_plot_cos1(2,1,0,1,0,0)+2.*comp_num_plot_cos1(2,1,0,1,1,0)
+2.*comp_num_plot_cos1(2,1,0,2,0,0)+2.*comp_num_plot_cos1(2,1,1,1,1,1)+2.*comp_num_plot_cos1(2,1,2,1,1,2)+2.*comp_num_plot_cos1(2,2,0,0,0,0)+2.*comp_num_plot_cos1(2,2,0,0,1,0)
+2.*comp_num_plot_cos1(2,2,0,0,2,0)+2.*comp_num_plot_cos1(2,2,0,1,0,0)+2.*comp_num_plot_cos1(2,2,0,1,1,0)+2.*comp_num_plot_cos1(2,2,0,1,2,0)+2.*comp_num_plot_cos1(2,2,0,2,0,0)
+2.*comp_num_plot_cos1(2,2,0,2,1,0)+2.*comp_num_plot_cos1(2,2,1,1,1,1)+2.*comp_num_plot_cos1(2,2,1,1,2,1)+2.*comp_num_plot_cos1(2,2,1,2,1,1)+2.*comp_num_plot_cos1(2,2,2,1,1,2)
+2.*comp_num_plot_cos1(2,2,2,1,2,2)+2.*comp_num_plot_cos1(2,2,2,2,1,2);

 }

// ---------------------------------------------------
// PDF used for the plot on cos2.

 Double_t KpiKpiSpectrumNW::num_plot_cos2() const 
 {

   set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
   set_buffer_integral_vars();

   return comp_num_plot_cos2(0,0,0,0,0,0)+comp_num_plot_cos2(0,1,0,0,1,0)+comp_num_plot_cos2(0,2,0,0,2,0)+comp_num_plot_cos2(1,0,0,1,0,0)+comp_num_plot_cos2(1,1,0,1,1,0)
+comp_num_plot_cos2(1,1,1,1,1,1)+comp_num_plot_cos2(1,1,2,1,1,2)+comp_num_plot_cos2(1,2,0,1,2,0)+comp_num_plot_cos2(1,2,1,1,2,1)+comp_num_plot_cos2(1,2,2,1,2,2)
+comp_num_plot_cos2(2,0,0,2,0,0)+comp_num_plot_cos2(2,1,0,2,1,0)+comp_num_plot_cos2(2,1,1,2,1,1)+comp_num_plot_cos2(2,1,2,2,1,2)+comp_num_plot_cos2(2,2,0,2,2,0)
+comp_num_plot_cos2(2,2,1,2,2,1)+comp_num_plot_cos2(2,2,2,2,2,2)+comp_num_plot_cos2(2,2,3,2,2,3)+comp_num_plot_cos2(2,2,4,2,2,4)+2.*comp_num_plot_cos2(0,1,0,0,0,0)
+2.*comp_num_plot_cos2(0,1,0,1,0,0)+2.*comp_num_plot_cos2(0,1,0,2,0,0)+2.*comp_num_plot_cos2(0,2,0,0,0,0)+2.*comp_num_plot_cos2(0,2,0,0,1,0)+2.*comp_num_plot_cos2(0,2,0,1,0,0)
+2.*comp_num_plot_cos2(0,2,0,1,1,0)+2.*comp_num_plot_cos2(0,2,0,2,0,0)+2.*comp_num_plot_cos2(0,2,0,2,1,0)+2.*comp_num_plot_cos2(1,0,0,0,0,0)+2.*comp_num_plot_cos2(1,1,0,0,0,0)
+2.*comp_num_plot_cos2(1,1,0,0,1,0)+2.*comp_num_plot_cos2(1,1,0,1,0,0)+2.*comp_num_plot_cos2(1,1,0,2,0,0)+2.*comp_num_plot_cos2(1,2,0,0,0,0)+2.*comp_num_plot_cos2(1,2,0,0,1,0)
+2.*comp_num_plot_cos2(1,2,0,0,2,0)+2.*comp_num_plot_cos2(1,2,0,1,0,0)+2.*comp_num_plot_cos2(1,2,0,1,1,0)+2.*comp_num_plot_cos2(1,2,0,2,0,0)+2.*comp_num_plot_cos2(1,2,0,2,1,0)
+2.*comp_num_plot_cos2(1,2,1,1,1,1)+2.*comp_num_plot_cos2(1,2,1,2,1,1)+2.*comp_num_plot_cos2(1,2,2,1,1,2)+2.*comp_num_plot_cos2(1,2,2,2,1,2)+2.*comp_num_plot_cos2(2,0,0,0,0,0)
+2.*comp_num_plot_cos2(2,0,0,1,0,0)+2.*comp_num_plot_cos2(2,1,0,0,0,0)+2.*comp_num_plot_cos2(2,1,0,0,1,0)+2.*comp_num_plot_cos2(2,1,0,1,0,0)+2.*comp_num_plot_cos2(2,1,0,1,1,0)
+2.*comp_num_plot_cos2(2,1,0,2,0,0)+2.*comp_num_plot_cos2(2,1,1,1,1,1)+2.*comp_num_plot_cos2(2,1,2,1,1,2)+2.*comp_num_plot_cos2(2,2,0,0,0,0)+2.*comp_num_plot_cos2(2,2,0,0,1,0)
+2.*comp_num_plot_cos2(2,2,0,0,2,0)+2.*comp_num_plot_cos2(2,2,0,1,0,0)+2.*comp_num_plot_cos2(2,2,0,1,1,0)+2.*comp_num_plot_cos2(2,2,0,1,2,0)+2.*comp_num_plot_cos2(2,2,0,2,0,0)
+2.*comp_num_plot_cos2(2,2,0,2,1,0)+2.*comp_num_plot_cos2(2,2,1,1,1,1)+2.*comp_num_plot_cos2(2,2,1,1,2,1)+2.*comp_num_plot_cos2(2,2,1,2,1,1)+2.*comp_num_plot_cos2(2,2,2,1,1,2)
+2.*comp_num_plot_cos2(2,2,2,1,2,2)+2.*comp_num_plot_cos2(2,2,2,2,1,2);

 }

// ---------------------------------------------------
// PDF used for the plot on m1 and m2.

 Double_t KpiKpiSpectrumNW::num_plot_m() const 
 {

   set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
   set_buffer_integral_vars();

   return comp_num_plot_m(0,0,0,0,0,0)+comp_num_plot_m(0,1,0,0,1,0)+comp_num_plot_m(0,2,0,0,2,0)+comp_num_plot_m(1,0,0,1,0,0)+comp_num_plot_m(1,1,0,1,1,0)
+comp_num_plot_m(1,1,1,1,1,1)+comp_num_plot_m(1,1,2,1,1,2)+comp_num_plot_m(1,2,0,1,2,0)+comp_num_plot_m(1,2,1,1,2,1)+comp_num_plot_m(1,2,2,1,2,2)
+comp_num_plot_m(2,0,0,2,0,0)+comp_num_plot_m(2,1,0,2,1,0)+comp_num_plot_m(2,1,1,2,1,1)+comp_num_plot_m(2,1,2,2,1,2)+comp_num_plot_m(2,2,0,2,2,0)
+comp_num_plot_m(2,2,1,2,2,1)+comp_num_plot_m(2,2,2,2,2,2)+comp_num_plot_m(2,2,3,2,2,3)+comp_num_plot_m(2,2,4,2,2,4)+2.*comp_num_plot_m(0,1,0,0,0,0)
+2.*comp_num_plot_m(0,1,0,1,0,0)+2.*comp_num_plot_m(0,1,0,2,0,0)+2.*comp_num_plot_m(0,2,0,0,0,0)+2.*comp_num_plot_m(0,2,0,0,1,0)+2.*comp_num_plot_m(0,2,0,1,0,0)
+2.*comp_num_plot_m(0,2,0,1,1,0)+2.*comp_num_plot_m(0,2,0,2,0,0)+2.*comp_num_plot_m(0,2,0,2,1,0)+2.*comp_num_plot_m(1,0,0,0,0,0)+2.*comp_num_plot_m(1,1,0,0,0,0)
+2.*comp_num_plot_m(1,1,0,0,1,0)+2.*comp_num_plot_m(1,1,0,1,0,0)+2.*comp_num_plot_m(1,1,0,2,0,0)+2.*comp_num_plot_m(1,2,0,0,0,0)+2.*comp_num_plot_m(1,2,0,0,1,0)
+2.*comp_num_plot_m(1,2,0,0,2,0)+2.*comp_num_plot_m(1,2,0,1,0,0)+2.*comp_num_plot_m(1,2,0,1,1,0)+2.*comp_num_plot_m(1,2,0,2,0,0)+2.*comp_num_plot_m(1,2,0,2,1,0)
+2.*comp_num_plot_m(1,2,1,1,1,1)+2.*comp_num_plot_m(1,2,1,2,1,1)+2.*comp_num_plot_m(1,2,2,1,1,2)+2.*comp_num_plot_m(1,2,2,2,1,2)+2.*comp_num_plot_m(2,0,0,0,0,0)
+2.*comp_num_plot_m(2,0,0,1,0,0)+2.*comp_num_plot_m(2,1,0,0,0,0)+2.*comp_num_plot_m(2,1,0,0,1,0)+2.*comp_num_plot_m(2,1,0,1,0,0)+2.*comp_num_plot_m(2,1,0,1,1,0)
+2.*comp_num_plot_m(2,1,0,2,0,0)+2.*comp_num_plot_m(2,1,1,1,1,1)+2.*comp_num_plot_m(2,1,2,1,1,2)+2.*comp_num_plot_m(2,2,0,0,0,0)+2.*comp_num_plot_m(2,2,0,0,1,0)
+2.*comp_num_plot_m(2,2,0,0,2,0)+2.*comp_num_plot_m(2,2,0,1,0,0)+2.*comp_num_plot_m(2,2,0,1,1,0)+2.*comp_num_plot_m(2,2,0,1,2,0)+2.*comp_num_plot_m(2,2,0,2,0,0)
+2.*comp_num_plot_m(2,2,0,2,1,0)+2.*comp_num_plot_m(2,2,1,1,1,1)+2.*comp_num_plot_m(2,2,1,1,2,1)+2.*comp_num_plot_m(2,2,1,2,1,1)+2.*comp_num_plot_m(2,2,2,1,1,2)
+2.*comp_num_plot_m(2,2,2,1,2,2)+2.*comp_num_plot_m(2,2,2,2,1,2);

 }

// ######################################################################################################
// I N T E G R A L S
// ######################################################################################################

// ---------------------------------------------------

void KpiKpiSpectrumNW::setDenPlotVarVal() const
{

   den_plot_var[(int) year_opt][(int) trig_opt] = den_plot();

   return;

}

// ---------------------------------------------------

Int_t KpiKpiSpectrumNW::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char*  rangeName) const
{

   // Normalization integral for fitting.
   if ( matchArgs(allVars,analVars,m1,m2,cos1,cos2) && matchArgs(allVars,analVars,phi,t,decision_SSK,decision_OS) && matchArgs(allVars,analVars,etamistag_SSK,etamistag_OS,t_err) ) return 1;

   // Integrals for plotting.
   if ( matchArgs(allVars,analVars,m1,m2,cos1,cos2) && matchArgs(allVars,analVars,phi,decision_SSK,decision_OS) && matchArgs(allVars,analVars,etamistag_SSK,etamistag_OS,t_err) ) return 2; // Plot on t.
   if ( matchArgs(allVars,analVars,m1,m2,cos1,cos2) && matchArgs(allVars,analVars,t,decision_SSK,decision_OS) && matchArgs(allVars,analVars,etamistag_SSK,etamistag_OS,t_err) ) return 3; // Plot on phi.
   if ( matchArgs(allVars,analVars,m1,m2,cos2,phi) && matchArgs(allVars,analVars,t,decision_SSK,decision_OS) && matchArgs(allVars,analVars,etamistag_SSK,etamistag_OS,t_err) ) return 4; // Plot on cos1.
   if ( matchArgs(allVars,analVars,m1,m2,cos1,phi) && matchArgs(allVars,analVars,t,decision_SSK,decision_OS) && matchArgs(allVars,analVars,etamistag_SSK,etamistag_OS,t_err) ) return 5; // Plot on cos2.
   if ( matchArgs(allVars,analVars,cos1,cos2,phi,t) && matchArgs(allVars,analVars,decision_SSK,decision_OS) && matchArgs(allVars,analVars,etamistag_SSK,etamistag_OS,t_err) ) return 6; // Plot on m1 and m2.

   return 0;

}

// ---------------------------------------------------

Double_t KpiKpiSpectrumNW::analyticalIntegral(Int_t code, const char* rangeName ) const
{

   // Normalization integral for fitting.
   if (code == 1) {return 1.;}

   // Integrals for plotting, full model.
   else if (code == 2 and ((A_j1 == 9) or (A_j2 == 9) or (A_h == 9) or (A_j1p == 9) or (A_j2p == 9) or (A_hp == 9))) {return num_plot_t()/den_plot_var[(int) year_opt][(int) trig_opt];}
   else if (code == 3 and ((A_j1 == 9) or (A_j2 == 9) or (A_h == 9) or (A_j1p == 9) or (A_j2p == 9) or (A_hp == 9))) {return num_plot_phi()/den_plot_var[(int) year_opt][(int) trig_opt];}
   else if (code == 4 and ((A_j1 == 9) or (A_j2 == 9) or (A_h == 9) or (A_j1p == 9) or (A_j2p == 9) or (A_hp == 9))) {return num_plot_cos1()/den_plot_var[(int) year_opt][(int) trig_opt];}
   else if (code == 5 and ((A_j1 == 9) or (A_j2 == 9) or (A_h == 9) or (A_j1p == 9) or (A_j2p == 9) or (A_hp == 9))) {return num_plot_cos2()/den_plot_var[(int) year_opt][(int) trig_opt];}
   else if (code == 6 and ((A_j1 == 9) or (A_j2 == 9) or (A_h == 9) or (A_j1p == 9) or (A_j2p == 9) or (A_hp == 9))) {return num_plot_m()/den_plot_var[(int) year_opt][(int) trig_opt];}

   // Integrals for plotting, VV component.
   else if (code == 2 and ((A_j1 == 10) or (A_j2 == 10) or (A_h == 10) or (A_j1p == 10) or (A_j2p == 10) or (A_hp == 10))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_t(1,1,0,1,1,0)+comp_num_plot_t(1,1,1,1,1,1)+comp_num_plot_t(1,1,2,1,1,2))/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 3 and ((A_j1 == 10) or (A_j2 == 10) or (A_h == 10) or (A_j1p == 10) or (A_j2p == 10) or (A_hp == 10))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_phi(1,1,0,1,1,0)+comp_num_plot_phi(1,1,1,1,1,1)+comp_num_plot_phi(1,1,2,1,1,2)+2.*comp_num_plot_phi(1,1,1,1,1,0)+2.*comp_num_plot_phi(1,1,2,1,1,0)+2.*comp_num_plot_phi(1,1,2,1,1,1))/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 4 and ((A_j1 == 10) or (A_j2 == 10) or (A_h == 10) or (A_j1p == 10) or (A_j2p == 10) or (A_hp == 10))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_cos1(1,1,0,1,1,0)+comp_num_plot_cos1(1,1,1,1,1,1)+comp_num_plot_cos1(1,1,2,1,1,2))/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 5 and ((A_j1 == 10) or (A_j2 == 10) or (A_h == 10) or (A_j1p == 10) or (A_j2p == 10) or (A_hp == 10))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_cos2(1,1,0,1,1,0)+comp_num_plot_cos2(1,1,1,1,1,1)+comp_num_plot_cos2(1,1,2,1,1,2))/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 6 and ((A_j1 == 10) or (A_j2 == 10) or (A_h == 10) or (A_j1p == 10) or (A_j2p == 10) or (A_hp == 10))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_m(1,1,0,1,1,0)+comp_num_plot_m(1,1,1,1,1,1)+comp_num_plot_m(1,1,2,1,1,2))/den_plot_var[(int) year_opt][(int) trig_opt];
   }

   // Integrals for plotting, SS component.
   else if (code == 2 and (A_j1 == 11) and (A_j2 == 11) and (A_h == 11) and (A_j1p == 11) and (A_j2p == 11) and (A_hp == 11)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_t(0,0,0,0,0,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 3 and (A_j1 == 11) and (A_j2 == 11) and (A_h == 11) and (A_j1p == 11) and (A_j2p == 11) and (A_hp == 11)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_phi(0,0,0,0,0,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 4 and (A_j1 == 11) and (A_j2 == 11) and (A_h == 11) and (A_j1p == 11) and (A_j2p == 11) and (A_hp == 11)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_cos1(0,0,0,0,0,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 5 and (A_j1 == 11) and (A_j2 == 11) and (A_h == 11) and (A_j1p == 11) and (A_j2p == 11) and (A_hp == 11)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_cos2(0,0,0,0,0,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 6 and (A_j1 == 11) and (A_j2 == 11) and (A_h == 11) and (A_j1p == 11) and (A_j2p == 11) and (A_hp == 11)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_m(0,0,0,0,0,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }

   // Integrals for plotting, SV component.
   else if (code == 2 and (A_j1 == 12) and (A_j2 == 12) and (A_h == 12) and (A_j1p == 12) and (A_j2p == 12) and (A_hp == 12)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_t(0,1,0,0,1,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 3 and (A_j1 == 12) and (A_j2 == 12) and (A_h == 12) and (A_j1p == 12) and (A_j2p == 12) and (A_hp == 12)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_phi(0,1,0,0,1,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 4 and (A_j1 == 12) and (A_j2 == 12) and (A_h == 12) and (A_j1p == 12) and (A_j2p == 12) and (A_hp == 12)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_cos1(0,1,0,0,1,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 5 and (A_j1 == 12) and (A_j2 == 12) and (A_h == 12) and (A_j1p == 12) and (A_j2p == 12) and (A_hp == 12)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_cos2(0,1,0,0,1,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 6 and (A_j1 == 12) and (A_j2 == 12) and (A_h == 12) and (A_j1p == 12) and (A_j2p == 12) and (A_hp == 12)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_m(0,1,0,0,1,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }

   // Integrals for plotting, VS component.
   else if (code == 2 and (A_j1 == 13) and (A_j2 == 13) and (A_h == 13) and (A_j1p == 13) and (A_j2p == 13) and (A_hp == 13)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_t(1,0,0,1,0,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 3 and (A_j1 == 13) and (A_j2 == 13) and (A_h == 13) and (A_j1p == 13) and (A_j2p == 13) and (A_hp == 13)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_phi(1,0,0,1,0,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 4 and (A_j1 == 13) and (A_j2 == 13) and (A_h == 13) and (A_j1p == 13) and (A_j2p == 13) and (A_hp == 13)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_cos1(1,0,0,1,0,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 5 and (A_j1 == 13) and (A_j2 == 13) and (A_h == 13) and (A_j1p == 13) and (A_j2p == 13) and (A_hp == 13)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_cos2(1,0,0,1,0,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 6 and (A_j1 == 13) and (A_j2 == 13) and (A_h == 13) and (A_j1p == 13) and (A_j2p == 13) and (A_hp == 13)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_m(1,0,0,1,0,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }

   // Integrals for plotting, ST component.
   else if (code == 2 and (A_j1 == 14) and (A_j2 == 14) and (A_h == 14) and (A_j1p == 14) and (A_j2p == 14) and (A_hp == 14)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_t(0,2,0,0,2,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 3 and (A_j1 == 14) and (A_j2 == 14) and (A_h == 14) and (A_j1p == 14) and (A_j2p == 14) and (A_hp == 14)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_phi(0,2,0,0,2,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 4 and (A_j1 == 14) and (A_j2 == 14) and (A_h == 14) and (A_j1p == 14) and (A_j2p == 14) and (A_hp == 14)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_cos1(0,2,0,0,2,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 5 and (A_j1 == 14) and (A_j2 == 14) and (A_h == 14) and (A_j1p == 14) and (A_j2p == 14) and (A_hp == 14)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_cos2(0,2,0,0,2,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 6 and (A_j1 == 14) and (A_j2 == 14) and (A_h == 14) and (A_j1p == 14) and (A_j2p == 14) and (A_hp == 14)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_m(0,2,0,0,2,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }

   // Integrals for plotting, TS component.
   else if (code == 2 and (A_j1 == 15) and (A_j2 == 15) and (A_h == 15) and (A_j1p == 15) and (A_j2p == 15) and (A_hp == 15)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_t(2,0,0,2,0,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 3 and (A_j1 == 15) and (A_j2 == 15) and (A_h == 15) and (A_j1p == 15) and (A_j2p == 15) and (A_hp == 15)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_phi(2,0,0,2,0,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 4 and (A_j1 == 15) and (A_j2 == 15) and (A_h == 15) and (A_j1p == 15) and (A_j2p == 15) and (A_hp == 15)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_cos1(2,0,0,2,0,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 5 and (A_j1 == 15) and (A_j2 == 15) and (A_h == 15) and (A_j1p == 15) and (A_j2p == 15) and (A_hp == 15)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_cos2(2,0,0,2,0,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 6 and (A_j1 == 15) and (A_j2 == 15) and (A_h == 15) and (A_j1p == 15) and (A_j2p == 15) and (A_hp == 15)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_m(2,0,0,2,0,0)/den_plot_var[(int) year_opt][(int) trig_opt];
   }

   // Integrals for plotting, VT component.
   else if (code == 2 and ((A_j1 == 16) or (A_j2 == 16) or (A_h == 16) or (A_j1p == 16) or (A_j2p == 16) or (A_hp == 16))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_t(1,2,0,1,2,0)+comp_num_plot_t(1,2,1,1,2,1)+comp_num_plot_t(1,2,2,1,2,2))/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 3 and ((A_j1 == 16) or (A_j2 == 16) or (A_h == 16) or (A_j1p == 16) or (A_j2p == 16) or (A_hp == 16))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_phi(1,2,0,1,2,0)+comp_num_plot_phi(1,2,1,1,2,1)+comp_num_plot_phi(1,2,2,1,2,2)+2.*comp_num_plot_phi(1,2,1,1,2,0)+2.*comp_num_plot_phi(1,2,2,1,2,0)+2.*comp_num_plot_phi(1,2,2,1,2,1))/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 4 and ((A_j1 == 16) or (A_j2 == 16) or (A_h == 16) or (A_j1p == 16) or (A_j2p == 16) or (A_hp == 16))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_cos1(1,2,0,1,2,0)+comp_num_plot_cos1(1,2,1,1,2,1)+comp_num_plot_cos1(1,2,2,1,2,2))/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 5 and ((A_j1 == 16) or (A_j2 == 16) or (A_h == 16) or (A_j1p == 16) or (A_j2p == 16) or (A_hp == 16))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_cos2(1,2,0,1,2,0)+comp_num_plot_cos2(1,2,1,1,2,1)+comp_num_plot_cos2(1,2,2,1,2,2))/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 6 and ((A_j1 == 16) or (A_j2 == 16) or (A_h == 16) or (A_j1p == 16) or (A_j2p == 16) or (A_hp == 16))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_m(1,2,0,1,2,0)+comp_num_plot_m(1,2,1,1,2,1)+comp_num_plot_m(1,2,2,1,2,2))/den_plot_var[(int) year_opt][(int) trig_opt];
   }

   // Integrals for plotting, TV component.
   else if (code == 2 and ((A_j1 == 17) or (A_j2 == 17) or (A_h == 17) or (A_j1p == 17) or (A_j2p == 17) or (A_hp == 17))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_t(2,1,0,2,1,0)+comp_num_plot_t(2,1,1,2,1,1)+comp_num_plot_t(2,1,2,2,1,2))/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 3 and ((A_j1 == 17) or (A_j2 == 17) or (A_h == 17) or (A_j1p == 17) or (A_j2p == 17) or (A_hp == 17))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_phi(2,1,0,2,1,0)+comp_num_plot_phi(2,1,1,2,1,1)+comp_num_plot_phi(2,1,2,2,1,2)+2.*comp_num_plot_phi(2,1,1,2,1,0)+2.*comp_num_plot_phi(2,1,2,2,1,0)+2.*comp_num_plot_phi(2,1,2,2,1,1))/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 4 and ((A_j1 == 17) or (A_j2 == 17) or (A_h == 17) or (A_j1p == 17) or (A_j2p == 17) or (A_hp == 17))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_cos1(2,1,0,2,1,0)+comp_num_plot_cos1(2,1,1,2,1,1)+comp_num_plot_cos1(2,1,2,2,1,2))/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 5 and ((A_j1 == 17) or (A_j2 == 17) or (A_h == 17) or (A_j1p == 17) or (A_j2p == 17) or (A_hp == 17))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_cos2(2,1,0,2,1,0)+comp_num_plot_cos2(2,1,1,2,1,1)+comp_num_plot_cos2(2,1,2,2,1,2))/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 6 and ((A_j1 == 17) or (A_j2 == 17) or (A_h == 17) or (A_j1p == 17) or (A_j2p == 17) or (A_hp == 17))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_m(2,1,0,2,1,0)+comp_num_plot_m(2,1,1,2,1,1)+comp_num_plot_m(2,1,2,2,1,2))/den_plot_var[(int) year_opt][(int) trig_opt];
   }

   // Integrals for plotting, TT component.
   else if (code == 2 and ((A_j1 == 18) or (A_j2 == 18) or (A_h == 18) or (A_j1p == 18) or (A_j2p == 18) or (A_hp == 18))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_t(2,2,0,2,2,0)+comp_num_plot_t(2,2,1,2,2,1)+comp_num_plot_t(2,2,2,2,2,2)+comp_num_plot_t(2,2,3,2,2,3)+comp_num_plot_t(2,2,4,2,2,4))/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 3 and ((A_j1 == 18) or (A_j2 == 18) or (A_h == 18) or (A_j1p == 18) or (A_j2p == 18) or (A_hp == 18))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_phi(2,2,0,2,2,0)+comp_num_plot_phi(2,2,1,2,2,1)+comp_num_plot_phi(2,2,2,2,2,2)+comp_num_plot_phi(2,2,3,2,2,3)+comp_num_plot_phi(2,2,4,2,2,4)+2.*comp_num_plot_phi(2,2,0,2,2,1)+2.*comp_num_plot_phi(2,2,0,2,2,2)+2.*comp_num_plot_phi(2,2,0,2,2,3)+2.*comp_num_plot_phi(2,2,0,2,2,4)+2.*comp_num_plot_phi(2,2,1,2,2,2)+2.*comp_num_plot_phi(2,2,1,2,2,3)+2.*comp_num_plot_phi(2,2,1,2,2,4)+2.*comp_num_plot_phi(2,2,2,2,2,3)+2.*comp_num_plot_phi(2,2,2,2,2,4)+2.*comp_num_plot_phi(2,2,3,2,2,4))/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 4 and ((A_j1 == 18) or (A_j2 == 18) or (A_h == 18) or (A_j1p == 18) or (A_j2p == 18) or (A_hp == 18))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_cos1(2,2,0,2,2,0)+comp_num_plot_cos1(2,2,1,2,2,1)+comp_num_plot_cos1(2,2,2,2,2,2)+comp_num_plot_cos1(2,2,3,2,2,3)+comp_num_plot_cos1(2,2,4,2,2,4))/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 5 and ((A_j1 == 18) or (A_j2 == 18) or (A_h == 18) or (A_j1p == 18) or (A_j2p == 18) or (A_hp == 18))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_cos2(2,2,0,2,2,0)+comp_num_plot_cos2(2,2,1,2,2,1)+comp_num_plot_cos2(2,2,2,2,2,2)+comp_num_plot_cos2(2,2,3,2,2,3)+comp_num_plot_cos2(2,2,4,2,2,4))/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 6 and ((A_j1 == 18) or (A_j2 == 18) or (A_h == 18) or (A_j1p == 18) or (A_j2p == 18) or (A_hp == 18))) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return (comp_num_plot_m(2,2,0,2,2,0)+comp_num_plot_m(2,2,1,2,2,1)+comp_num_plot_m(2,2,2,2,2,2)+comp_num_plot_m(2,2,3,2,2,3)+comp_num_plot_m(2,2,4,2,2,4))/den_plot_var[(int) year_opt][(int) trig_opt];
   }

   // Integrals for plotting, j1j2hj1pj2php component.
   else if (code == 2 and (A_j1 < 9) and (A_j2 < 9) and (A_h < 9) and (A_j1p < 9) and (A_j2p < 9) and (A_hp < 9)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_t(A_j1,A_j2,A_h,A_j1p,A_j2p,A_hp)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 3 and (A_j1 < 9) and (A_j2 < 9) and (A_h < 9) and (A_j1p < 9) and (A_j2p < 9) and (A_hp < 9)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_phi(A_j1,A_j2,A_h,A_j1p,A_j2p,A_hp)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 4 and (A_j1 < 9) and (A_j2 < 9) and (A_h < 9) and (A_j1p < 9) and (A_j2p < 9) and (A_hp < 9)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_cos1(A_j1,A_j2,A_h,A_j1p,A_j2p,A_hp)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 5 and (A_j1 < 9) and (A_j2 < 9) and (A_h < 9) and (A_j1p < 9) and (A_j2p < 9) and (A_hp < 9)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_cos2(A_j1,A_j2,A_h,A_j1p,A_j2p,A_hp)/den_plot_var[(int) year_opt][(int) trig_opt];
   }
   else if (code == 6 and (A_j1 < 9) and (A_j2 < 9) and (A_h < 9) and (A_j1p < 9) and (A_j2p < 9) and (A_hp < 9)) {
      set_buffer_differential_vars(m1,m2,cos1,cos2,phi,t,t_err,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS);
      set_buffer_integral_vars();
      return comp_num_plot_m(A_j1,A_j2,A_h,A_j1p,A_j2p,A_hp)/den_plot_var[(int) year_opt][(int) trig_opt];
   }

   return 0;

}

// ######################################################################################################
// E V E N T   G E N E R A T I O N
// ######################################################################################################

// ---------------------------------------------------
// Acceptance used in generation.

 Double_t KpiKpiSpectrumNW::accGen(Double_t tau, Double_t ma, Double_t mb, Double_t cos1var, Double_t cos2var, Double_t phivar) const
 {
   return accTime(tau)*accMass(ma)*accMass(mb)*accAng(cos1var)*accAng(cos2var);
 }

// ---------------------------------------------------
// SSK mistag probability spectrum.

 Double_t KpiKpiSpectrumNW::P_eta_SSK(Double_t eta) const 
 {
   if (eta < 0.5) {return c_SSK*TMath::Gaus(eta,mu1_SSK,sigma1_SSK)+(1.-c_SSK)*TMath::Gaus(eta,mu2_SSK,sigma2_SSK);}
   else {return 0.;}
 }

// ---------------------------------------------------
// OS mistag probability spectrum.

 Double_t KpiKpiSpectrumNW::P_eta_OS(Double_t eta) const 
 {
   if (eta < 0.5) {return c_OS*TMath::Gaus(eta,mu1_OS,sigma1_OS)+(1.-c_OS)*TMath::Gaus(eta,mu2_OS,sigma2_OS);}
   else {return 0.;}
 }

// ---------------------------------------------------
// Decay time error spectrum.

 Double_t KpiKpiSpectrumNW::P_deltat(Double_t tau_err) const 
 { 
   return TMath::GammaDist(tau_err,gamma1_dt,0.,beta1_dt)+c_dt*TMath::GammaDist(tau_err,gamma2_dt,0.,beta2_dt);
 }

// ---------------------------------------------------
// Bs time dependent function.

TComplex KpiKpiSpectrumNW::TBsj1j2hj1pj2php(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const
 {

   return T_cosh_temp*M_Average(j1,j2,h,j1p,j2p,hp)-T_sinh_temp*M_DeltaGamma(j1,j2,h,j1p,j2p,hp)+T_cos_temp*M_DirCP(j1,j2,h,j1p,j2p,hp)+T_sin_temp*M_MixCP(j1,j2,h,j1p,j2p,hp);

 }

// ---------------------------------------------------
// Bsbar time dependent function.

TComplex KpiKpiSpectrumNW::TBsbarj1j2hj1pj2php(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const
 {

   return T_cosh_temp*M_Average(j1,j2,h,j1p,j2p,hp)-T_sinh_temp*M_DeltaGamma(j1,j2,h,j1p,j2p,hp)-T_cos_temp*M_DirCP(j1,j2,h,j1p,j2p,hp)-T_sin_temp*M_MixCP(j1,j2,h,j1p,j2p,hp);

 }

// ---------------------------------------------------
// Components of the Bs decay rate.

 Double_t KpiKpiSpectrumNW::comp_fun_Bs(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const 
 {

   return (TBsj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*hj1j2j1pj2p(m1,m2,j1,j2,j1p,j2p)).Re()*ghhp_phi(h,hp)*fjjphhp_cos1(j1,j1p,h,hp)*fjjphhp_cos2(j2,j2p,h,hp);

 }

// ---------------------------------------------------
// Components of the Bsbar decay rate.

 Double_t KpiKpiSpectrumNW::comp_fun_Bsbar(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const 
 {

   return (TBsbarj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*hj1j2j1pj2p(m1,m2,j1,j2,j1p,j2p)).Re()*ghhp_phi(h,hp)*fjjphhp_cos1(j1,j1p,h,hp)*fjjphhp_cos2(j2,j2p,h,hp);

 }

// ---------------------------------------------------
// Bs decay rate.

 Double_t KpiKpiSpectrumNW::fun_Bs() const 
 {

   return comp_fun_Bs(0,0,0,0,0,0)+comp_fun_Bs(0,1,0,0,1,0)+comp_fun_Bs(0,2,0,0,2,0)+comp_fun_Bs(1,0,0,1,0,0)+comp_fun_Bs(1,1,0,1,1,0)+comp_fun_Bs(1,1,1,1,1,1)
+comp_fun_Bs(1,1,2,1,1,2)+comp_fun_Bs(1,2,0,1,2,0)+comp_fun_Bs(1,2,1,1,2,1)+comp_fun_Bs(1,2,2,1,2,2)+comp_fun_Bs(2,0,0,2,0,0)+comp_fun_Bs(2,1,0,2,1,0)+comp_fun_Bs(2,1,1,2,1,1)
+comp_fun_Bs(2,1,2,2,1,2)+comp_fun_Bs(2,2,0,2,2,0)+comp_fun_Bs(2,2,1,2,2,1)+comp_fun_Bs(2,2,2,2,2,2)+comp_fun_Bs(2,2,3,2,2,3)+comp_fun_Bs(2,2,4,2,2,4)+2.*comp_fun_Bs(0,1,0,0,0,0)
+2.*comp_fun_Bs(0,1,0,1,0,0)+2.*comp_fun_Bs(0,1,0,2,0,0)+2.*comp_fun_Bs(0,2,0,0,0,0)+2.*comp_fun_Bs(0,2,0,0,1,0)+2.*comp_fun_Bs(0,2,0,1,0,0)+2.*comp_fun_Bs(0,2,0,1,1,0)
+2.*comp_fun_Bs(0,2,0,2,0,0)+2.*comp_fun_Bs(0,2,0,2,1,0)+2.*comp_fun_Bs(1,0,0,0,0,0)+2.*comp_fun_Bs(1,1,0,0,0,0)+2.*comp_fun_Bs(1,1,0,0,1,0)+2.*comp_fun_Bs(1,1,0,1,0,0)
+2.*comp_fun_Bs(1,1,0,2,0,0)+2.*comp_fun_Bs(1,1,1,0,0,0)+2.*comp_fun_Bs(1,1,1,0,1,0)+2.*comp_fun_Bs(1,1,1,0,2,0)+2.*comp_fun_Bs(1,1,1,1,0,0)+2.*comp_fun_Bs(1,1,1,1,1,0)
+2.*comp_fun_Bs(1,1,1,1,2,0)+2.*comp_fun_Bs(1,1,1,2,0,0)+2.*comp_fun_Bs(1,1,1,2,1,0)+2.*comp_fun_Bs(1,1,1,2,2,0)+2.*comp_fun_Bs(1,1,2,0,0,0)+2.*comp_fun_Bs(1,1,2,0,1,0)
+2.*comp_fun_Bs(1,1,2,0,2,0)+2.*comp_fun_Bs(1,1,2,1,0,0)+2.*comp_fun_Bs(1,1,2,1,1,0)+2.*comp_fun_Bs(1,1,2,1,1,1)+2.*comp_fun_Bs(1,1,2,1,2,0)+2.*comp_fun_Bs(1,1,2,1,2,1)
+2.*comp_fun_Bs(1,1,2,2,0,0)+2.*comp_fun_Bs(1,1,2,2,1,0)+2.*comp_fun_Bs(1,1,2,2,1,1)+2.*comp_fun_Bs(1,1,2,2,2,0)+2.*comp_fun_Bs(1,1,2,2,2,1)+2.*comp_fun_Bs(1,2,0,0,0,0)
+2.*comp_fun_Bs(1,2,0,0,1,0)+2.*comp_fun_Bs(1,2,0,0,2,0)+2.*comp_fun_Bs(1,2,0,1,0,0)+2.*comp_fun_Bs(1,2,0,1,1,0)+2.*comp_fun_Bs(1,2,0,2,0,0)+2.*comp_fun_Bs(1,2,0,2,1,0)
+2.*comp_fun_Bs(1,2,1,0,0,0)+2.*comp_fun_Bs(1,2,1,0,1,0)+2.*comp_fun_Bs(1,2,1,0,2,0)+2.*comp_fun_Bs(1,2,1,1,0,0)+2.*comp_fun_Bs(1,2,1,1,1,0)+2.*comp_fun_Bs(1,2,1,1,1,1)
+2.*comp_fun_Bs(1,2,1,1,2,0)+2.*comp_fun_Bs(1,2,1,2,0,0)+2.*comp_fun_Bs(1,2,1,2,1,0)+2.*comp_fun_Bs(1,2,1,2,1,1)+2.*comp_fun_Bs(1,2,1,2,2,0)+2.*comp_fun_Bs(1,2,2,0,0,0)
+2.*comp_fun_Bs(1,2,2,0,1,0)+2.*comp_fun_Bs(1,2,2,0,2,0)+2.*comp_fun_Bs(1,2,2,1,0,0)+2.*comp_fun_Bs(1,2,2,1,1,0)+2.*comp_fun_Bs(1,2,2,1,1,1)+2.*comp_fun_Bs(1,2,2,1,1,2)
+2.*comp_fun_Bs(1,2,2,1,2,0)+2.*comp_fun_Bs(1,2,2,1,2,1)+2.*comp_fun_Bs(1,2,2,2,0,0)+2.*comp_fun_Bs(1,2,2,2,1,0)+2.*comp_fun_Bs(1,2,2,2,1,1)+2.*comp_fun_Bs(1,2,2,2,1,2)
+2.*comp_fun_Bs(1,2,2,2,2,0)+2.*comp_fun_Bs(1,2,2,2,2,1)+2.*comp_fun_Bs(2,0,0,0,0,0)+2.*comp_fun_Bs(2,0,0,1,0,0)+2.*comp_fun_Bs(2,1,0,0,0,0)+2.*comp_fun_Bs(2,1,0,0,1,0)
+2.*comp_fun_Bs(2,1,0,1,0,0)+2.*comp_fun_Bs(2,1,0,1,1,0)+2.*comp_fun_Bs(2,1,0,2,0,0)+2.*comp_fun_Bs(2,1,1,0,0,0)+2.*comp_fun_Bs(2,1,1,0,1,0)+2.*comp_fun_Bs(2,1,1,0,2,0)
+2.*comp_fun_Bs(2,1,1,1,0,0)+2.*comp_fun_Bs(2,1,1,1,1,0)+2.*comp_fun_Bs(2,1,1,1,1,1)+2.*comp_fun_Bs(2,1,1,1,2,0)+2.*comp_fun_Bs(2,1,1,2,0,0)+2.*comp_fun_Bs(2,1,1,2,1,0)
+2.*comp_fun_Bs(2,1,1,2,2,0)+2.*comp_fun_Bs(2,1,2,0,0,0)+2.*comp_fun_Bs(2,1,2,0,1,0)+2.*comp_fun_Bs(2,1,2,0,2,0)+2.*comp_fun_Bs(2,1,2,1,0,0)+2.*comp_fun_Bs(2,1,2,1,1,0)
+2.*comp_fun_Bs(2,1,2,1,1,1)+2.*comp_fun_Bs(2,1,2,1,1,2)+2.*comp_fun_Bs(2,1,2,1,2,0)+2.*comp_fun_Bs(2,1,2,1,2,1)+2.*comp_fun_Bs(2,1,2,2,0,0)+2.*comp_fun_Bs(2,1,2,2,1,0)
+2.*comp_fun_Bs(2,1,2,2,1,1)+2.*comp_fun_Bs(2,1,2,2,2,0)+2.*comp_fun_Bs(2,1,2,2,2,1)+2.*comp_fun_Bs(2,2,0,0,0,0)+2.*comp_fun_Bs(2,2,0,0,1,0)+2.*comp_fun_Bs(2,2,0,0,2,0)
+2.*comp_fun_Bs(2,2,0,1,0,0)+2.*comp_fun_Bs(2,2,0,1,1,0)+2.*comp_fun_Bs(2,2,0,1,2,0)+2.*comp_fun_Bs(2,2,0,2,0,0)+2.*comp_fun_Bs(2,2,0,2,1,0)+2.*comp_fun_Bs(2,2,1,0,0,0)
+2.*comp_fun_Bs(2,2,1,0,1,0)+2.*comp_fun_Bs(2,2,1,0,2,0)+2.*comp_fun_Bs(2,2,1,1,0,0)+2.*comp_fun_Bs(2,2,1,1,1,0)+2.*comp_fun_Bs(2,2,1,1,1,1)+2.*comp_fun_Bs(2,2,1,1,2,0)
+2.*comp_fun_Bs(2,2,1,1,2,1)+2.*comp_fun_Bs(2,2,1,2,0,0)+2.*comp_fun_Bs(2,2,1,2,1,0)+2.*comp_fun_Bs(2,2,1,2,1,1)+2.*comp_fun_Bs(2,2,1,2,2,0)+2.*comp_fun_Bs(2,2,2,0,0,0)
+2.*comp_fun_Bs(2,2,2,0,1,0)+2.*comp_fun_Bs(2,2,2,0,2,0)+2.*comp_fun_Bs(2,2,2,1,0,0)+2.*comp_fun_Bs(2,2,2,1,1,0)+2.*comp_fun_Bs(2,2,2,1,1,1)+2.*comp_fun_Bs(2,2,2,1,1,2)
+2.*comp_fun_Bs(2,2,2,1,2,0)+2.*comp_fun_Bs(2,2,2,1,2,1)+2.*comp_fun_Bs(2,2,2,1,2,2)+2.*comp_fun_Bs(2,2,2,2,0,0)+2.*comp_fun_Bs(2,2,2,2,1,0)+2.*comp_fun_Bs(2,2,2,2,1,1)
+2.*comp_fun_Bs(2,2,2,2,1,2)+2.*comp_fun_Bs(2,2,2,2,2,0)+2.*comp_fun_Bs(2,2,2,2,2,1)+2.*comp_fun_Bs(2,2,3,0,0,0)+2.*comp_fun_Bs(2,2,3,0,1,0)+2.*comp_fun_Bs(2,2,3,0,2,0)
+2.*comp_fun_Bs(2,2,3,1,0,0)+2.*comp_fun_Bs(2,2,3,1,1,0)+2.*comp_fun_Bs(2,2,3,1,1,1)+2.*comp_fun_Bs(2,2,3,1,1,2)+2.*comp_fun_Bs(2,2,3,1,2,0)+2.*comp_fun_Bs(2,2,3,1,2,1)
+2.*comp_fun_Bs(2,2,3,1,2,2)+2.*comp_fun_Bs(2,2,3,2,0,0)+2.*comp_fun_Bs(2,2,3,2,1,0)+2.*comp_fun_Bs(2,2,3,2,1,1)+2.*comp_fun_Bs(2,2,3,2,1,2)+2.*comp_fun_Bs(2,2,3,2,2,0)
+2.*comp_fun_Bs(2,2,3,2,2,1)+2.*comp_fun_Bs(2,2,3,2,2,2)+2.*comp_fun_Bs(2,2,4,0,0,0)+2.*comp_fun_Bs(2,2,4,0,1,0)+2.*comp_fun_Bs(2,2,4,0,2,0)+2.*comp_fun_Bs(2,2,4,1,0,0)
+2.*comp_fun_Bs(2,2,4,1,1,0)+2.*comp_fun_Bs(2,2,4,1,1,1)+2.*comp_fun_Bs(2,2,4,1,1,2)+2.*comp_fun_Bs(2,2,4,1,2,0)+2.*comp_fun_Bs(2,2,4,1,2,1)+2.*comp_fun_Bs(2,2,4,1,2,2)
+2.*comp_fun_Bs(2,2,4,2,0,0)+2.*comp_fun_Bs(2,2,4,2,1,0)+2.*comp_fun_Bs(2,2,4,2,1,1)+2.*comp_fun_Bs(2,2,4,2,1,2)+2.*comp_fun_Bs(2,2,4,2,2,0)+2.*comp_fun_Bs(2,2,4,2,2,1)
+2.*comp_fun_Bs(2,2,4,2,2,2)+2.*comp_fun_Bs(2,2,4,2,2,3);

 }

// ---------------------------------------------------
// Bsbar decay rate.

 Double_t KpiKpiSpectrumNW::fun_Bsbar() const 
 {

   return comp_fun_Bsbar(0,0,0,0,0,0)+comp_fun_Bsbar(0,1,0,0,1,0)+comp_fun_Bsbar(0,2,0,0,2,0)+comp_fun_Bsbar(1,0,0,1,0,0)+comp_fun_Bsbar(1,1,0,1,1,0)+comp_fun_Bsbar(1,1,1,1,1,1)
+comp_fun_Bsbar(1,1,2,1,1,2)+comp_fun_Bsbar(1,2,0,1,2,0)+comp_fun_Bsbar(1,2,1,1,2,1)+comp_fun_Bsbar(1,2,2,1,2,2)+comp_fun_Bsbar(2,0,0,2,0,0)+comp_fun_Bsbar(2,1,0,2,1,0)+comp_fun_Bsbar(2,1,1,2,1,1)
+comp_fun_Bsbar(2,1,2,2,1,2)+comp_fun_Bsbar(2,2,0,2,2,0)+comp_fun_Bsbar(2,2,1,2,2,1)+comp_fun_Bsbar(2,2,2,2,2,2)+comp_fun_Bsbar(2,2,3,2,2,3)+comp_fun_Bsbar(2,2,4,2,2,4)+2.*comp_fun_Bsbar(0,1,0,0,0,0)
+2.*comp_fun_Bsbar(0,1,0,1,0,0)+2.*comp_fun_Bsbar(0,1,0,2,0,0)+2.*comp_fun_Bsbar(0,2,0,0,0,0)+2.*comp_fun_Bsbar(0,2,0,0,1,0)+2.*comp_fun_Bsbar(0,2,0,1,0,0)+2.*comp_fun_Bsbar(0,2,0,1,1,0)
+2.*comp_fun_Bsbar(0,2,0,2,0,0)+2.*comp_fun_Bsbar(0,2,0,2,1,0)+2.*comp_fun_Bsbar(1,0,0,0,0,0)+2.*comp_fun_Bsbar(1,1,0,0,0,0)+2.*comp_fun_Bsbar(1,1,0,0,1,0)+2.*comp_fun_Bsbar(1,1,0,1,0,0)
+2.*comp_fun_Bsbar(1,1,0,2,0,0)+2.*comp_fun_Bsbar(1,1,1,0,0,0)+2.*comp_fun_Bsbar(1,1,1,0,1,0)+2.*comp_fun_Bsbar(1,1,1,0,2,0)+2.*comp_fun_Bsbar(1,1,1,1,0,0)+2.*comp_fun_Bsbar(1,1,1,1,1,0)
+2.*comp_fun_Bsbar(1,1,1,1,2,0)+2.*comp_fun_Bsbar(1,1,1,2,0,0)+2.*comp_fun_Bsbar(1,1,1,2,1,0)+2.*comp_fun_Bsbar(1,1,1,2,2,0)+2.*comp_fun_Bsbar(1,1,2,0,0,0)+2.*comp_fun_Bsbar(1,1,2,0,1,0)
+2.*comp_fun_Bsbar(1,1,2,0,2,0)+2.*comp_fun_Bsbar(1,1,2,1,0,0)+2.*comp_fun_Bsbar(1,1,2,1,1,0)+2.*comp_fun_Bsbar(1,1,2,1,1,1)+2.*comp_fun_Bsbar(1,1,2,1,2,0)+2.*comp_fun_Bsbar(1,1,2,1,2,1)
+2.*comp_fun_Bsbar(1,1,2,2,0,0)+2.*comp_fun_Bsbar(1,1,2,2,1,0)+2.*comp_fun_Bsbar(1,1,2,2,1,1)+2.*comp_fun_Bsbar(1,1,2,2,2,0)+2.*comp_fun_Bsbar(1,1,2,2,2,1)+2.*comp_fun_Bsbar(1,2,0,0,0,0)
+2.*comp_fun_Bsbar(1,2,0,0,1,0)+2.*comp_fun_Bsbar(1,2,0,0,2,0)+2.*comp_fun_Bsbar(1,2,0,1,0,0)+2.*comp_fun_Bsbar(1,2,0,1,1,0)+2.*comp_fun_Bsbar(1,2,0,2,0,0)+2.*comp_fun_Bsbar(1,2,0,2,1,0)
+2.*comp_fun_Bsbar(1,2,1,0,0,0)+2.*comp_fun_Bsbar(1,2,1,0,1,0)+2.*comp_fun_Bsbar(1,2,1,0,2,0)+2.*comp_fun_Bsbar(1,2,1,1,0,0)+2.*comp_fun_Bsbar(1,2,1,1,1,0)+2.*comp_fun_Bsbar(1,2,1,1,1,1)
+2.*comp_fun_Bsbar(1,2,1,1,2,0)+2.*comp_fun_Bsbar(1,2,1,2,0,0)+2.*comp_fun_Bsbar(1,2,1,2,1,0)+2.*comp_fun_Bsbar(1,2,1,2,1,1)+2.*comp_fun_Bsbar(1,2,1,2,2,0)+2.*comp_fun_Bsbar(1,2,2,0,0,0)
+2.*comp_fun_Bsbar(1,2,2,0,1,0)+2.*comp_fun_Bsbar(1,2,2,0,2,0)+2.*comp_fun_Bsbar(1,2,2,1,0,0)+2.*comp_fun_Bsbar(1,2,2,1,1,0)+2.*comp_fun_Bsbar(1,2,2,1,1,1)+2.*comp_fun_Bsbar(1,2,2,1,1,2)
+2.*comp_fun_Bsbar(1,2,2,1,2,0)+2.*comp_fun_Bsbar(1,2,2,1,2,1)+2.*comp_fun_Bsbar(1,2,2,2,0,0)+2.*comp_fun_Bsbar(1,2,2,2,1,0)+2.*comp_fun_Bsbar(1,2,2,2,1,1)+2.*comp_fun_Bsbar(1,2,2,2,1,2)
+2.*comp_fun_Bsbar(1,2,2,2,2,0)+2.*comp_fun_Bsbar(1,2,2,2,2,1)+2.*comp_fun_Bsbar(2,0,0,0,0,0)+2.*comp_fun_Bsbar(2,0,0,1,0,0)+2.*comp_fun_Bsbar(2,1,0,0,0,0)+2.*comp_fun_Bsbar(2,1,0,0,1,0)
+2.*comp_fun_Bsbar(2,1,0,1,0,0)+2.*comp_fun_Bsbar(2,1,0,1,1,0)+2.*comp_fun_Bsbar(2,1,0,2,0,0)+2.*comp_fun_Bsbar(2,1,1,0,0,0)+2.*comp_fun_Bsbar(2,1,1,0,1,0)+2.*comp_fun_Bsbar(2,1,1,0,2,0)
+2.*comp_fun_Bsbar(2,1,1,1,0,0)+2.*comp_fun_Bsbar(2,1,1,1,1,0)+2.*comp_fun_Bsbar(2,1,1,1,1,1)+2.*comp_fun_Bsbar(2,1,1,1,2,0)+2.*comp_fun_Bsbar(2,1,1,2,0,0)+2.*comp_fun_Bsbar(2,1,1,2,1,0)
+2.*comp_fun_Bsbar(2,1,1,2,2,0)+2.*comp_fun_Bsbar(2,1,2,0,0,0)+2.*comp_fun_Bsbar(2,1,2,0,1,0)+2.*comp_fun_Bsbar(2,1,2,0,2,0)+2.*comp_fun_Bsbar(2,1,2,1,0,0)+2.*comp_fun_Bsbar(2,1,2,1,1,0)
+2.*comp_fun_Bsbar(2,1,2,1,1,1)+2.*comp_fun_Bsbar(2,1,2,1,1,2)+2.*comp_fun_Bsbar(2,1,2,1,2,0)+2.*comp_fun_Bsbar(2,1,2,1,2,1)+2.*comp_fun_Bsbar(2,1,2,2,0,0)+2.*comp_fun_Bsbar(2,1,2,2,1,0)
+2.*comp_fun_Bsbar(2,1,2,2,1,1)+2.*comp_fun_Bsbar(2,1,2,2,2,0)+2.*comp_fun_Bsbar(2,1,2,2,2,1)+2.*comp_fun_Bsbar(2,2,0,0,0,0)+2.*comp_fun_Bsbar(2,2,0,0,1,0)+2.*comp_fun_Bsbar(2,2,0,0,2,0)
+2.*comp_fun_Bsbar(2,2,0,1,0,0)+2.*comp_fun_Bsbar(2,2,0,1,1,0)+2.*comp_fun_Bsbar(2,2,0,1,2,0)+2.*comp_fun_Bsbar(2,2,0,2,0,0)+2.*comp_fun_Bsbar(2,2,0,2,1,0)+2.*comp_fun_Bsbar(2,2,1,0,0,0)
+2.*comp_fun_Bsbar(2,2,1,0,1,0)+2.*comp_fun_Bsbar(2,2,1,0,2,0)+2.*comp_fun_Bsbar(2,2,1,1,0,0)+2.*comp_fun_Bsbar(2,2,1,1,1,0)+2.*comp_fun_Bsbar(2,2,1,1,1,1)+2.*comp_fun_Bsbar(2,2,1,1,2,0)
+2.*comp_fun_Bsbar(2,2,1,1,2,1)+2.*comp_fun_Bsbar(2,2,1,2,0,0)+2.*comp_fun_Bsbar(2,2,1,2,1,0)+2.*comp_fun_Bsbar(2,2,1,2,1,1)+2.*comp_fun_Bsbar(2,2,1,2,2,0)+2.*comp_fun_Bsbar(2,2,2,0,0,0)
+2.*comp_fun_Bsbar(2,2,2,0,1,0)+2.*comp_fun_Bsbar(2,2,2,0,2,0)+2.*comp_fun_Bsbar(2,2,2,1,0,0)+2.*comp_fun_Bsbar(2,2,2,1,1,0)+2.*comp_fun_Bsbar(2,2,2,1,1,1)+2.*comp_fun_Bsbar(2,2,2,1,1,2)
+2.*comp_fun_Bsbar(2,2,2,1,2,0)+2.*comp_fun_Bsbar(2,2,2,1,2,1)+2.*comp_fun_Bsbar(2,2,2,1,2,2)+2.*comp_fun_Bsbar(2,2,2,2,0,0)+2.*comp_fun_Bsbar(2,2,2,2,1,0)+2.*comp_fun_Bsbar(2,2,2,2,1,1)
+2.*comp_fun_Bsbar(2,2,2,2,1,2)+2.*comp_fun_Bsbar(2,2,2,2,2,0)+2.*comp_fun_Bsbar(2,2,2,2,2,1)+2.*comp_fun_Bsbar(2,2,3,0,0,0)+2.*comp_fun_Bsbar(2,2,3,0,1,0)+2.*comp_fun_Bsbar(2,2,3,0,2,0)
+2.*comp_fun_Bsbar(2,2,3,1,0,0)+2.*comp_fun_Bsbar(2,2,3,1,1,0)+2.*comp_fun_Bsbar(2,2,3,1,1,1)+2.*comp_fun_Bsbar(2,2,3,1,1,2)+2.*comp_fun_Bsbar(2,2,3,1,2,0)+2.*comp_fun_Bsbar(2,2,3,1,2,1)
+2.*comp_fun_Bsbar(2,2,3,1,2,2)+2.*comp_fun_Bsbar(2,2,3,2,0,0)+2.*comp_fun_Bsbar(2,2,3,2,1,0)+2.*comp_fun_Bsbar(2,2,3,2,1,1)+2.*comp_fun_Bsbar(2,2,3,2,1,2)+2.*comp_fun_Bsbar(2,2,3,2,2,0)
+2.*comp_fun_Bsbar(2,2,3,2,2,1)+2.*comp_fun_Bsbar(2,2,3,2,2,2)+2.*comp_fun_Bsbar(2,2,4,0,0,0)+2.*comp_fun_Bsbar(2,2,4,0,1,0)+2.*comp_fun_Bsbar(2,2,4,0,2,0)+2.*comp_fun_Bsbar(2,2,4,1,0,0)
+2.*comp_fun_Bsbar(2,2,4,1,1,0)+2.*comp_fun_Bsbar(2,2,4,1,1,1)+2.*comp_fun_Bsbar(2,2,4,1,1,2)+2.*comp_fun_Bsbar(2,2,4,1,2,0)+2.*comp_fun_Bsbar(2,2,4,1,2,1)+2.*comp_fun_Bsbar(2,2,4,1,2,2)
+2.*comp_fun_Bsbar(2,2,4,2,0,0)+2.*comp_fun_Bsbar(2,2,4,2,1,0)+2.*comp_fun_Bsbar(2,2,4,2,1,1)+2.*comp_fun_Bsbar(2,2,4,2,1,2)+2.*comp_fun_Bsbar(2,2,4,2,2,0)+2.*comp_fun_Bsbar(2,2,4,2,2,1)
+2.*comp_fun_Bsbar(2,2,4,2,2,2)+2.*comp_fun_Bsbar(2,2,4,2,2,3);

 }

// ---------------------------------------------------
// Integral of the Bs time dependent function, effective resolution.

TComplex KpiKpiSpectrumNW::ITBsj1j2hj1pj2php(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const
 {

   return IT_cosh_temp*M_Average(j1,j2,h,j1p,j2p,hp)-IT_sinh_temp*M_DeltaGamma(j1,j2,h,j1p,j2p,hp)+IT_cos_temp*M_DirCP(j1,j2,h,j1p,j2p,hp)+IT_sin_temp*M_MixCP(j1,j2,h,j1p,j2p,hp);

 }

// ---------------------------------------------------
// Components of the Bs decay rate integral.

 Double_t KpiKpiSpectrumNW::comp_int_Bs(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const 
 { 
   return (ITBsj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Ihj1j2j1pj2p(j1,j2,j1p,j2p)).Re()*Ighhp(h,hp)*Ifjjphhp(j1,j1p,h,hp)*Ifjjphhp(j2,j2p,h,hp);
 }

// ---------------------------------------------------
// Bs decay rate integral.

 Double_t KpiKpiSpectrumNW::int_Bs() const 
 {

   return comp_int_Bs(0,0,0,0,0,0)+comp_int_Bs(0,1,0,0,1,0)+comp_int_Bs(0,2,0,0,2,0)+comp_int_Bs(1,0,0,1,0,0)+comp_int_Bs(1,1,0,1,1,0)
+comp_int_Bs(1,1,1,1,1,1)+comp_int_Bs(1,1,2,1,1,2)+comp_int_Bs(1,2,0,1,2,0)+comp_int_Bs(1,2,1,1,2,1)+comp_int_Bs(1,2,2,1,2,2)
+comp_int_Bs(2,0,0,2,0,0)+comp_int_Bs(2,1,0,2,1,0)+comp_int_Bs(2,1,1,2,1,1)+comp_int_Bs(2,1,2,2,1,2)+comp_int_Bs(2,2,0,2,2,0)
+comp_int_Bs(2,2,1,2,2,1)+comp_int_Bs(2,2,2,2,2,2)+comp_int_Bs(2,2,3,2,2,3)+comp_int_Bs(2,2,4,2,2,4)+2.*comp_int_Bs(0,1,0,0,0,0)
+2.*comp_int_Bs(0,1,0,1,0,0)+2.*comp_int_Bs(0,1,0,2,0,0)+2.*comp_int_Bs(0,2,0,0,0,0)+2.*comp_int_Bs(0,2,0,0,1,0)+2.*comp_int_Bs(0,2,0,1,0,0)
+2.*comp_int_Bs(0,2,0,1,1,0)+2.*comp_int_Bs(0,2,0,2,0,0)+2.*comp_int_Bs(0,2,0,2,1,0)+2.*comp_int_Bs(1,0,0,0,0,0)+2.*comp_int_Bs(1,1,0,0,0,0)
+2.*comp_int_Bs(1,1,0,0,1,0)+2.*comp_int_Bs(1,1,0,1,0,0)+2.*comp_int_Bs(1,1,0,2,0,0)+2.*comp_int_Bs(1,2,0,0,0,0)+2.*comp_int_Bs(1,2,0,0,1,0)
+2.*comp_int_Bs(1,2,0,0,2,0)+2.*comp_int_Bs(1,2,0,1,0,0)+2.*comp_int_Bs(1,2,0,1,1,0)+2.*comp_int_Bs(1,2,0,2,0,0)+2.*comp_int_Bs(1,2,0,2,1,0)
+2.*comp_int_Bs(1,2,1,1,1,1)+2.*comp_int_Bs(1,2,1,2,1,1)+2.*comp_int_Bs(1,2,2,1,1,2)+2.*comp_int_Bs(1,2,2,2,1,2)+2.*comp_int_Bs(2,0,0,0,0,0)
+2.*comp_int_Bs(2,0,0,1,0,0)+2.*comp_int_Bs(2,1,0,0,0,0)+2.*comp_int_Bs(2,1,0,0,1,0)+2.*comp_int_Bs(2,1,0,1,0,0)+2.*comp_int_Bs(2,1,0,1,1,0)
+2.*comp_int_Bs(2,1,0,2,0,0)+2.*comp_int_Bs(2,1,1,1,1,1)+2.*comp_int_Bs(2,1,2,1,1,2)+2.*comp_int_Bs(2,2,0,0,0,0)+2.*comp_int_Bs(2,2,0,0,1,0)
+2.*comp_int_Bs(2,2,0,0,2,0)+2.*comp_int_Bs(2,2,0,1,0,0)+2.*comp_int_Bs(2,2,0,1,1,0)+2.*comp_int_Bs(2,2,0,1,2,0)+2.*comp_int_Bs(2,2,0,2,0,0)
+2.*comp_int_Bs(2,2,0,2,1,0)+2.*comp_int_Bs(2,2,1,1,1,1)+2.*comp_int_Bs(2,2,1,1,2,1)+2.*comp_int_Bs(2,2,1,2,1,1)+2.*comp_int_Bs(2,2,2,1,1,2)
+2.*comp_int_Bs(2,2,2,1,2,2)+2.*comp_int_Bs(2,2,2,2,1,2);

 }

// ---------------------------------------------------
// True Bs (vs true Bsbar) probability.

Double_t KpiKpiSpectrumNW::P_trueBs() const
{

  set_buffer_integral_vars();

  cout << "P(Bs_true) = " << 0.5*(1.+DCP_prod[int(wide_window)])*int_Bs()/den_plot() << endl;

  return 0.5*(1.+DCP_prod[int(wide_window)])*int_Bs()/den_plot();

}

// ---------------------------------------------------
// Randomization of the auxiliar m1, m2, cos1, cos2, phi, t and t_err variables.

 void KpiKpiSpectrumNW::Randomize7D(Int_t wide_window_gen) const 
 {

   if (wide_window_gen == 1) {
      m1_ran = 750.+ran.Rndm()*(1500.-750.);
      m2_ran = 750.+ran.Rndm()*(1500.-750.);
      }
   else {
      m1_ran = 750.+ran.Rndm()*(1050.-750.);
      m2_ran = 750.+ran.Rndm()*(1050.-750.);
      }
   cos1_ran = -1.+ran.Rndm()*2.;
   cos2_ran = -1.+ran.Rndm()*2.;
   phi_ran = -pi+ran.Rndm()*2.*pi;
   t_ran = ran.Rndm()*12.;
   t_err_ran = ran.Rndm()*0.1;

   return;

 }

// ---------------------------------------------------
// Randomization of the auxiliar m1, m2, cos1, cos2, phi, t and t_err variables, used to estimate
// the maximum of the PDF. Variable ranges reduced in an appropriate way to increase the efficiency.

 void KpiKpiSpectrumNW::Randomize7D_fun_max() const 
 {

   m1_ran = 850.+ran.Rndm()*(950.-850.);
   m2_ran = 850.+ran.Rndm()*(950.-850.);
   cos1_ran = -1.+ran.Rndm()*2.;
   cos2_ran = -1.+ran.Rndm()*2.;
   phi_ran = -pi+ran.Rndm()*2.*pi;
   t_ran = ran.Rndm()*3.;
   t_err_ran = 0.01+ran.Rndm()*(0.04-0.01);

   return;

 }

// ---------------------------------------------------
// Configuration of the generator settings.

void KpiKpiSpectrumNW::SetGenerator(Int_t wide_window_gen, Int_t compute_max_fun, Int_t sample_size_7D) const
{

  // Setting of the mKpi generation range.
  Wide_Window_Gen = wide_window_gen;

  // Randomization of the random number generator seed.
  ran.SetSeed(0);

  // Variable inicialization.
  dec_Bs = 0.;
  dec_SSK_tagged = 0.;
  dec_OS_tagged = 0.;
  dec_accepted = 0.;
  N_accepted = 0;

  // Computation of the true Bs (vs true Bsbar) probability.
  P_trueBs_const = P_trueBs();

  // Computation of the maximum value for the considered distributions, if requested.
  if (compute_max_fun == 1) {

    cout << "Computing p.d.f.'s maxima.\n";

    max_fun_etaSSK = 0.;
    max_fun_etaOS = 0.;
    max_fun_7DBs = 0.;
    max_fun_7DBsbar = 0.;

    // Tagging performance distributions.
    for (int i=0; i<10000; i++) {
      etamistag_SSK_ran = 0.3+ran.Rndm()*(0.5-0.3);
      fun_ran = P_eta_SSK(etamistag_SSK_ran);
      if (fun_ran > max_fun_etaSSK) {max_fun_etaSSK = fun_ran;}
      etamistag_OS_ran = 0.3+ran.Rndm()*(0.5-0.3);
      fun_ran = P_eta_OS(etamistag_OS_ran);
      if (fun_ran > max_fun_etaOS) {max_fun_etaOS = fun_ran;}
      }

    // Decay observable distributions.
    cout << "(Using a randomized sample of " << sample_size_7D << " 7D points to find the maximum of the Bs and Bs-bar PDFs).\n";
    for (int i=0; i<sample_size_7D; i++) {
      Randomize7D_fun_max();
      set_buffer_differential_vars(m1_ran,m2_ran,cos1_ran,cos2_ran,phi_ran,t_ran,t_err_ran,0,0,0.5,0.5);
      fun_ran = P_deltat(t_err_ran)*fun_Bs()*accGen(t_ran,m1_ran,m2_ran,cos1_ran,cos2_ran,phi_ran);
      if (fun_ran > max_fun_7DBs) {max_fun_7DBs = fun_ran;}
      Randomize7D_fun_max();
      set_buffer_differential_vars(m1_ran,m2_ran,cos1_ran,cos2_ran,phi_ran,t_ran,t_err_ran,0,0,0.5,0.5);
      fun_ran = P_deltat(t_err_ran)*fun_Bsbar()*accGen(t_ran,m1_ran,m2_ran,cos1_ran,cos2_ran,phi_ran);
      if (fun_ran > max_fun_7DBsbar) {max_fun_7DBsbar = fun_ran;}
      }

    // Providing the computed maxima with an extra safety range.
    max_fun_etaSSK *= 1.1;
    max_fun_etaOS *= 1.1;
    max_fun_7DBs *= 1.1;
    max_fun_7DBsbar *= 1.1;

    cout << "max_P_eta_SSK = " << max_fun_etaSSK << "\n" << "max_P_eta_OS = " << max_fun_etaOS << "\n" << "max_P_7D_Bs = " << max_fun_7DBs << "\n" << "max_P_7D_Bsbar = " << max_fun_7DBsbar << "\n";

    }

  else {

    // Relyable previously measured values.

    if (Wide_Window_Gen == 0) {
      cout << "Using previously obtained values for the maxima of the Bs and Bs-bar PDFs in the narrow mKpi window.\n";
      max_fun_etaSSK = 0.26227;
      max_fun_etaOS = 0.958321;
      max_fun_7DBs = 0.0330968;
      max_fun_7DBsbar = 0.0342749;
      }

    else {
      cout << "Using previously obtained values for the maxima of the Bs and Bs-bar PDFs in the wide mKpi window.\n";
      max_fun_etaSSK = 0.262292;
      max_fun_etaOS = 0.958321;
      max_fun_7DBs = 0.00494785;
      max_fun_7DBsbar = 0.00519231;
      }

    }

  return;

}

// ---------------------------------------------------

Int_t KpiKpiSpectrumNW::getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t /*staticInitOK*/) const
{

  // 11-D generation, corresponding to the full set of observables.
  if ( matchArgs(directVars,generateVars,m1,m2,cos1,cos2) && matchArgs(directVars,generateVars,phi,t,decision_SSK,decision_OS) && matchArgs(directVars,generateVars,etamistag_SSK,etamistag_OS,t_err) ) return 1 ;

  return 0 ;

}

// ---------------------------------------------------

void KpiKpiSpectrumNW::generateEvent(Int_t code)
{

  assert(code==1);

  // Generation is performed in three steps:
  //    1. The event is first generated either as a Bs or a Bsbar.
  //    2. Mistag probabilities and tagging decisions are assigned to the event.
  //    3. Decay variables (angles, invariant masses, decay time and
  //       estimated decay time error) are assigned to the event.

  // Generation of a Bs or a Bsbar event.
  dec_Bs = ran.Rndm();
  if (dec_Bs <= P_trueBs_const) {true_ID = 1;} // Bs-like event.
  else {true_ID = -1;} // Bsbar-like event.

  // Determination of the SSK mistag probability.
  dec_SSK_tagged = ran.Rndm();
  if (dec_SSK_tagged <= tag_eff_SSK) {
    // If the event is tagged, the accept-reject method is used to generate eta.
    event_accepted = 0;
    max_fun = max_fun_etaSSK;
    while (event_accepted == 0) {
      etamistag_SSK_ran = 0.5*ran.Rndm();
      fun_ran = P_eta_SSK(etamistag_SSK_ran);
      dec_accepted = max_fun*ran.Rndm();
      if (fun_ran >= dec_accepted) {event_accepted = 1;}
      }
    etamistag_SSK = etamistag_SSK_ran;
    }
  else {
    // If the event is not tagged, eta is set to 0.5.
    etamistag_SSK = 0.5;
    }

  // Determination of the SSK tagging decision.
  if (etamistag_SSK < 0.5) {
    dec_right_tagged = ran.Rndm();
    if (true_ID == 1) {
      prob_right_tagged = 1.-omega_SSK(etamistag_SSK);
      if (dec_right_tagged <= prob_right_tagged) {decision_SSK = 1;} // Right tagged Bs.
      else {decision_SSK = -1;} // Wrong tagged Bs.
      }
    else {
      prob_right_tagged = 1.-omegabar_SSK(etamistag_SSK);
      if (dec_right_tagged <= prob_right_tagged) {decision_SSK = -1;} // Right tagged Bsbar.
      else {decision_SSK = 1;} // Wrong tagged Bsbar.
      }
    }
  else {
    decision_SSK = 0;
    }

  // Determination of the OS mistag probability.
  dec_OS_tagged = ran.Rndm();
  if (dec_OS_tagged <= tag_eff_OS) {
    // If the event is tagged, the accept-reject method is used to generate eta.
    event_accepted = 0;
    max_fun = max_fun_etaOS;
    while (event_accepted == 0) {
      etamistag_OS_ran = 0.5*ran.Rndm();
      fun_ran = P_eta_OS(etamistag_OS_ran);
      dec_accepted = max_fun*ran.Rndm();
      if (fun_ran >= dec_accepted) {event_accepted = 1;}
      }
    etamistag_OS = etamistag_OS_ran;
    }
  else {
    // If the event is not tagged, eta is set to 0.5.
    etamistag_OS = 0.5;
    }

  // Determination of the OS tagging decision.
  if (etamistag_OS < 0.5) {
    dec_right_tagged = ran.Rndm();
    if (true_ID == 1) {
      prob_right_tagged = 1.-omega_OS(etamistag_OS);
      if (dec_right_tagged <= prob_right_tagged) {decision_OS = 1;} // Right tagged Bs.
      else {decision_OS = -1;} // Wrong tagged Bs.
      }
    else {
      prob_right_tagged = 1.-omegabar_OS(etamistag_OS);
      if (dec_right_tagged <= prob_right_tagged) {decision_OS = -1;} // Right tagged Bsbar.
      else {decision_OS = 1;} // Wrong tagged Bsbar.
      }
    }
  else {
    decision_OS = 0;
    }

  // Determination of the event decay observables, using the accept-reject method in 7-D.
  // Acceptance effects are taken into account and the parametrized t_err distribution is used.
  event_accepted = 0;
  if (true_ID == 1) {max_fun = max_fun_7DBs;}
  else {max_fun = max_fun_7DBsbar;}
  while (event_accepted == 0) {
    Randomize7D(Wide_Window_Gen);
    set_buffer_differential_vars(m1_ran,m2_ran,cos1_ran,cos2_ran,phi_ran,t_ran,t_err_ran,0,0,0.5,0.5);
    dec_accepted = max_fun*ran.Rndm();
    if (true_ID == 1) {
      fun_ran = P_deltat(t_err_ran)*fun_Bs()*accGen(t_ran,m1_ran,m2_ran,cos1_ran,cos2_ran,phi_ran);
      }
    else {
      fun_ran = P_deltat(t_err_ran)*fun_Bsbar()*accGen(t_ran,m1_ran,m2_ran,cos1_ran,cos2_ran,phi_ran);
      }
    if (fun_ran >= dec_accepted) {event_accepted = 1;}
    }
  m1 = m1_ran;
  m2 = m2_ran;
  cos1 = cos1_ran;
  cos2 = cos2_ran;
  phi = phi_ran;
  t = t_ran;
  t_err = t_err_ran;

  N_accepted += 1;
  if (N_accepted%10 == 0) {cout << N_accepted << " events generated\n";}

  return;

}

// ######################################################################################################
// O U T P U T
// ######################################################################################################

// ---------------------------------------------------

Double_t KpiKpiSpectrumNW::evaluate() const 
{

	// Full fitter.
	if (alt_fit == 0) {
		if (acctype == 2) {return num_fit()/den_fit();}
		else {return num_fit()/den_plot();}
	}

	// 1-D fits of the conditional variable distributions.
	else if (alt_fit == 1) {return P_deltat(t_err);}
	else if (alt_fit == 2) {return P_eta_SSK(etamistag_SSK);}
	else if (alt_fit == 3) {return P_eta_OS(etamistag_OS);}

	else {return 0.;}

}
