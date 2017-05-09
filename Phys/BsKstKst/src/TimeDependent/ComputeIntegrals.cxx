#include "Riostream.h"
#include "ComputeIntegrals.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include <math.h>
#include "TMath.h"
#include "TF1.h"
#include <stdexcept>
#include "KpiKpiSpectrumNW.h"
#include "RooMath.h"

ClassImp(ComputeIntegrals) 

// ---------------------------------------------------

 ComputeIntegrals::ComputeIntegrals(const char *name, const char *title,
			const RooArgList& _options,
			const RooArgList& _observables,
			const RooArgList& _mixing_params,
			const RooArgList& _calib_params,
			const RooArgList& _mass_integrals):
   RooAbsReal(name,title)
 {
   RooAbsReal* coef_options ;
   TIterator* options_iter = _options.createIterator() ;
   RooAbsReal* coef_real_observables ;
   RooAbsCategory* coef_int_observables ;
   TIterator* observables_iter = _observables.createIterator() ;
   RooAbsReal* coef_mixing_params ;
   TIterator* mixing_params_iter = _mixing_params.createIterator() ;
   RooAbsReal* coef_calib_params ;
   TIterator* calib_params_iter = _calib_params.createIterator() ;
   RooAbsReal* coef_mass_integrals ;
   TIterator* mass_integrals_iter = _mass_integrals.createIterator() ;

   // Options to configure the PDF.
   coef_options=(RooAbsReal*)options_iter->Next();
   wide_window = RooRealProxy("wide_window","wide_window",this,*coef_options);
   coef_options=(RooAbsReal*)options_iter->Next();
   year_opt = RooRealProxy("year_opt","year_opt",this,*coef_options);
   coef_options=(RooAbsReal*)options_iter->Next();
   trig_opt = RooRealProxy("trig_opt","trig_opt",this,*coef_options);
   coef_options=(RooAbsReal*)options_iter->Next();
   gen = RooRealProxy("gen","gen",this,*coef_options);
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
   deltatmean_tres_11 = RooRealProxy("deltatmean_tres_11","deltatmean_tres_11",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   p0_tres_11 = RooRealProxy("p0_tres_11","p0_tres_11",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   p1_tres_11 = RooRealProxy("p1_tres_11","p1_tres_11",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   deltatmean_tres_12 = RooRealProxy("deltatmean_tres_12","deltatmean_tres_12",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   p0_tres_12 = RooRealProxy("p0_tres_12","p0_tres_12",this,*coef_calib_params);
   coef_calib_params=(RooAbsReal*)calib_params_iter->Next();
   p1_tres_12 = RooRealProxy("p1_tres_12","p1_tres_12",this,*coef_calib_params);
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

 }

// ---------------------------------------------------

 ComputeIntegrals::ComputeIntegrals(const ComputeIntegrals& other, const char* name) :  
   RooAbsReal(other,name),
   wide_window("wide_window",this,other.wide_window),
   year_opt("year_opt",this,other.year_opt),
   trig_opt("trig_opt",this,other.trig_opt),
   gen("gen",this,other.gen),
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
   deltatmean_tres_11("deltatmean_tres_11",this,other.deltatmean_tres_11),
   p0_tres_11("p0_tres_11",this,other.p0_tres_11),
   p1_tres_11("p1_tres_11",this,other.p1_tres_11),
   deltatmean_tres_12("deltatmean_tres_12",this,other.deltatmean_tres_12),
   p0_tres_12("p0_tres_12",this,other.p0_tres_12),
   p1_tres_12("p1_tres_12",this,other.p1_tres_12),
   mv("mv",this,other.mv),
   ms("ms",this,other.ms),
   mt("mt",this,other.mt),
   gv("gv",this,other.gv),
   gs("gs",this,other.gs),
   gt("gt",this,other.gt),
   res_mass("res_mass",this,other.res_mass),
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
   Ih21Im("Ih21Im",this,other.Ih21Im)
 { 
 } 

// ---------------------------------------------------

Double_t ComputeIntegrals::sigma_tres_eff(Int_t g_i) const 
 { 

   if (g_i == 1) {return TReseff.sigma1(year_opt,wide_window);}
   else if (g_i == 2) {return TReseff.sigma2(year_opt,wide_window);}

   return 0.;

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::sigma_ref_eff() const 
 { 

   Double_t sigma_val = TReseff.f1(year_opt,wide_window)*sigma_tres_eff(1)+(1.-TReseff.f1(year_opt,wide_window))*sigma_tres_eff(2);

   return sigma_val;

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::x_tres_eff(Double_t tau, Int_t g_i) const
 { 

   return 1./(sqrt(2.)*sigma_tres_eff(g_i))*(tau-TReseff.off(year_opt,wide_window)-gamma_Bs_freq*sigma_tres_eff(g_i)*sigma_tres_eff(g_i));

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::x0_tres_eff(Int_t g_i) const
 { 

   return delta_gamma_freq*sigma_tres_eff(g_i)/(2.*sqrt(2.));

 }

// ---------------------------------------------------

std::complex<Double_t> ComputeIntegrals::z_tres_eff(Double_t tau, Int_t g_i) const
 { 

   std::complex<Double_t> z_hat(delta_m_freq*sigma_tres_eff(g_i)*sigma_tres_eff(g_i),-tau+TReseff.off(year_opt,wide_window)+gamma_Bs_freq*sigma_tres_eff(g_i)*sigma_tres_eff(g_i));

   return 1./(sqrt(2.)*sigma_tres_eff(g_i))*z_hat;

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::gaus_tres_eff(Double_t tau, Int_t g_i) const
 { 

   return exp(-(tau-TReseff.off(year_opt,wide_window))*(tau-TReseff.off(year_opt,wide_window))/2./sigma_tres_eff(g_i)/sigma_tres_eff(g_i));

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::erfc(Double_t x) const 
 { 
   
   return RooMath::erfc(x);

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::Re_w(std::complex<Double_t> z) const 
 { 
   
   return (RooMath::faddeeva(z)).real();

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::Im_w(std::complex<Double_t> z) const 
 { 
   
   return (RooMath::faddeeva(z)).imag();

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::T_cosh_ideal(Double_t tau) const
 {
   
   return exp(-gamma_Bs_freq*tau)*cosh(0.5*delta_gamma_freq*tau);

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::T_sinh_ideal(Double_t tau) const
 {
   
   return exp(-gamma_Bs_freq*tau)*sinh(0.5*delta_gamma_freq*tau);

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::T_cos_ideal(Double_t tau) const
 {
   
   return exp(-gamma_Bs_freq*tau)*cos(delta_m_freq*tau);

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::T_sin_ideal(Double_t tau) const
 {
   
   return exp(-gamma_Bs_freq*tau)*sin(delta_m_freq*tau);

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::T_cosh_resexact_eff(Double_t tau) const
 {
   
   return 1./4.*(TReseff.f1(year_opt,wide_window)*gaus_tres_eff(tau,1)*(exp((x_tres_eff(tau,1)+x0_tres_eff(1))*(x_tres_eff(tau,1)+x0_tres_eff(1)))*erfc(-x_tres_eff(tau,1)-x0_tres_eff(1))+exp((x_tres_eff(tau,1)-x0_tres_eff(1))*(x_tres_eff(tau,1)-x0_tres_eff(1)))*erfc(-x_tres_eff(tau,1)+x0_tres_eff(1)))+(1.-TReseff.f1(year_opt,wide_window))*gaus_tres_eff(tau,2)*(exp((x_tres_eff(tau,2)+x0_tres_eff(2))*(x_tres_eff(tau,2)+x0_tres_eff(2)))*erfc(-x_tres_eff(tau,2)-x0_tres_eff(2))+exp((x_tres_eff(tau,2)-x0_tres_eff(2))*(x_tres_eff(tau,2)-x0_tres_eff(2)))*erfc(-x_tres_eff(tau,2)+x0_tres_eff(2))));

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::T_sinh_resexact_eff(Double_t tau) const
 {
   
   return 1./4.*(TReseff.f1(year_opt,wide_window)*gaus_tres_eff(tau,1)*(exp((x_tres_eff(tau,1)+x0_tres_eff(1))*(x_tres_eff(tau,1)+x0_tres_eff(1)))*erfc(-x_tres_eff(tau,1)-x0_tres_eff(1))-exp((x_tres_eff(tau,1)-x0_tres_eff(1))*(x_tres_eff(tau,1)-x0_tres_eff(1)))*erfc(-x_tres_eff(tau,1)+x0_tres_eff(1)))+(1.-TReseff.f1(year_opt,wide_window))*gaus_tres_eff(tau,2)*(exp((x_tres_eff(tau,2)+x0_tres_eff(2))*(x_tres_eff(tau,2)+x0_tres_eff(2)))*erfc(-x_tres_eff(tau,2)-x0_tres_eff(2))-exp((x_tres_eff(tau,2)-x0_tres_eff(2))*(x_tres_eff(tau,2)-x0_tres_eff(2)))*erfc(-x_tres_eff(tau,2)+x0_tres_eff(2))));

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::T_cos_resexact_eff(Double_t tau) const
 {
   
   return 1./2.*(TReseff.f1(year_opt,wide_window)*gaus_tres_eff(tau,1)*Re_w(z_tres_eff(tau,1))+(1.-TReseff.f1(year_opt,wide_window))*gaus_tres_eff(tau,2)*Re_w(z_tres_eff(tau,2)));

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::T_sin_resexact_eff(Double_t tau) const
 {
   
   return 1./2.*(TReseff.f1(year_opt,wide_window)*gaus_tres_eff(tau,1)*Im_w(z_tres_eff(tau,1))+(1.-TReseff.f1(year_opt,wide_window))*gaus_tres_eff(tau,2)*Im_w(z_tres_eff(tau,2)));

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::T_cosh_resapprox_eff(Double_t tau) const
 {
   
   return (TReseff.f1(year_opt,wide_window)*exp(-gamma_Bs_freq*(tau-TReseff.off(year_opt,wide_window))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1)+1./8.*delta_gamma_freq*delta_gamma_freq*sigma_tres_eff(1)*sigma_tres_eff(1))*cosh(0.5*delta_gamma_freq*(tau-TReseff.off(year_opt,wide_window))-0.5*gamma_Bs_freq*delta_gamma_freq*sigma_tres_eff(1)*sigma_tres_eff(1))+(1.-TReseff.f1(year_opt,wide_window))*exp(-gamma_Bs_freq*(tau-TReseff.off(year_opt,wide_window))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2)+1./8.*delta_gamma_freq*delta_gamma_freq*sigma_tres_eff(2)*sigma_tres_eff(2))*cosh(0.5*delta_gamma_freq*(tau-TReseff.off(year_opt,wide_window))-0.5*gamma_Bs_freq*delta_gamma_freq*sigma_tres_eff(2)*sigma_tres_eff(2)));

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::T_sinh_resapprox_eff(Double_t tau) const
 {
   
   return (TReseff.f1(year_opt,wide_window)*exp(-gamma_Bs_freq*(tau-TReseff.off(year_opt,wide_window))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1)+1./8.*delta_gamma_freq*delta_gamma_freq*sigma_tres_eff(1)*sigma_tres_eff(1))*sinh(0.5*delta_gamma_freq*(tau-TReseff.off(year_opt,wide_window))-0.5*gamma_Bs_freq*delta_gamma_freq*sigma_tres_eff(1)*sigma_tres_eff(1))+(1.-TReseff.f1(year_opt,wide_window))*exp(-gamma_Bs_freq*(tau-TReseff.off(year_opt,wide_window))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2)+1./8.*delta_gamma_freq*delta_gamma_freq*sigma_tres_eff(2)*sigma_tres_eff(2))*sinh(0.5*delta_gamma_freq*(tau-TReseff.off(year_opt,wide_window))-0.5*gamma_Bs_freq*delta_gamma_freq*sigma_tres_eff(2)*sigma_tres_eff(2)));

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::T_cos_resapprox_eff(Double_t tau) const
 {
   
   return (TReseff.f1(year_opt,wide_window)*exp(-gamma_Bs_freq*(tau-TReseff.off(year_opt,wide_window))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1)-0.5*delta_m_freq*delta_m_freq*sigma_tres_eff(1)*sigma_tres_eff(1))*cos(delta_m_freq*(tau-TReseff.off(year_opt,wide_window))-gamma_Bs_freq*delta_m_freq*sigma_tres_eff(1)*sigma_tres_eff(1))+(1.-TReseff.f1(year_opt,wide_window))*exp(-gamma_Bs_freq*(tau-TReseff.off(year_opt,wide_window))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2)-0.5*delta_m_freq*delta_m_freq*sigma_tres_eff(2)*sigma_tres_eff(2))*cos(delta_m_freq*(tau-TReseff.off(year_opt,wide_window))-gamma_Bs_freq*delta_m_freq*sigma_tres_eff(2)*sigma_tres_eff(2)));

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::T_sin_resapprox_eff(Double_t tau) const
 {
   
   return (TReseff.f1(year_opt,wide_window)*exp(-gamma_Bs_freq*(tau-TReseff.off(year_opt,wide_window))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres_eff(1)*sigma_tres_eff(1)-0.5*delta_m_freq*delta_m_freq*sigma_tres_eff(1)*sigma_tres_eff(1))*sin(delta_m_freq*(tau-TReseff.off(year_opt,wide_window))-gamma_Bs_freq*delta_m_freq*sigma_tres_eff(1)*sigma_tres_eff(1))+(1.-TReseff.f1(year_opt,wide_window))*exp(-gamma_Bs_freq*(tau-TReseff.off(year_opt,wide_window))+0.5*gamma_Bs_freq*gamma_Bs_freq*sigma_tres_eff(2)*sigma_tres_eff(2)-0.5*delta_m_freq*delta_m_freq*sigma_tres_eff(2)*sigma_tres_eff(2))*sin(delta_m_freq*(tau-TReseff.off(year_opt,wide_window))-gamma_Bs_freq*delta_m_freq*sigma_tres_eff(2)*sigma_tres_eff(2)));

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::T_cosh_eff(Double_t tau) const
 {
   
   if (inftres == 1) {return T_cosh_ideal(tau);}
   else if ((inftres == 0) && ((tau-TReseff.off(year_opt,wide_window)) <= 20*sigma_ref_eff())) {return T_cosh_resexact_eff(tau);}
   else {return T_cosh_resapprox_eff(tau);}

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::T_sinh_eff(Double_t tau) const
 {
   
   if (inftres == 1) {return T_sinh_ideal(tau);}
   else if ((inftres == 0) && ((tau-TReseff.off(year_opt,wide_window)) <= 20*sigma_ref_eff())) {return T_sinh_resexact_eff(tau);}
   else {return T_sinh_resapprox_eff(tau);}

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::T_cos_eff(Double_t tau) const
 {
   
   if (inftres == 1) {return T_cos_ideal(tau);}
   else if ((inftres == 0) && ((tau-TReseff.off(year_opt,wide_window)) <= 20*sigma_ref_eff())) {return T_cos_resexact_eff(tau);}
   else {return T_cos_resapprox_eff(tau);}

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::T_sin_eff(Double_t tau) const
 {
   
   if (inftres == 1) {return T_sin_ideal(tau);}
   else if ((inftres == 0) && ((tau-TReseff.off(year_opt,wide_window)) <= 20*sigma_ref_eff())) {return T_sin_resexact_eff(tau);}
   else {return T_sin_resapprox_eff(tau);}

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::fi(Double_t x, Int_t i) const 
 { 
   
   Double_t f;

   if (i == 1) {f = 1.;}
   else if (i == 2) {f = x;}
   else if (i == 3) {f = sqrt(1.-x*x);}
   else if (i == 4) {f = 3.*x*x-1.;}
   else if (i == 5) {f = x*sqrt(1.-x*x);}
   else if (i == 6) {f = x*x;}
   else if (i == 7) {f = x*(3.*x*x-1.);}
   else if (i == 8) {f = x*x*sqrt(1.-x*x);}
   else if (i == 9) {f = 1.-x*x;}
   else if (i == 10) {f = (3.*x*x-1.)*sqrt(1.-x*x);}
   else if (i == 11) {f = x*(1.-x*x);}
   else if (i == 12) {f = (3.*x*x-1.)*(3.*x*x-1.);}
   else if (i == 13) {f = x*(3.*x*x-1.)*sqrt(1.-x*x);}
   else if (i == 14) {f = x*x*(1.-x*x);}
   else if (i == 15) {f = (1.-x*x)*sqrt(1.-x*x);}
   else if (i == 16) {f = (3.*x*x-1.)*(1.-x*x);}
   else if (i == 17) {f = x*(1.-x*x)*sqrt(1.-x*x);}
   else if (i == 18) {f = (1.-x*x)*(1.-x*x);}

   else {throw std::invalid_argument( "Invalid argument" );}

   return f;

 }

// ---------------------------------------------------
// Momentum of one of the two daughters in the rest frame of the mother.

Double_t ComputeIntegrals::get_q(Double_t M, Double_t ma, Double_t mb) const 
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

Double_t ComputeIntegrals::Blatt_Weisskopf2(Double_t q, Double_t q0, Int_t L) const 
 {

   if (L<1.) {return 1.;}  
   Double_t d = 1.6e-03;
   Double_t z = q*d*q*d;
   Double_t z0 = q0*d*q0*d;
   if (L==1) {return (1+z0)/(1+z);}
   else if (L==2) {return ((z0-3)*(z0-3) + 9*z0) / ((z-3)*(z-3) + 9*z);}
   else if (L==3) {return (z0*(z0-15)*(z0-15) + 9*(z0-5)) / (z*(z-15)*(z-15) + 9*(z-5));}
   return ( pow(z0*z0 -45*z0+105,2) +25*z0*(2*z0-21)*(2*z0-21)) /(pow(z*z -45*z+105,2) +25*z*(2*z-21)*(2*z-21));

 }

// ---------------------------------------------------
// Angular momentum barrier factor.

Double_t ComputeIntegrals::FL_j1j2(Int_t j1, Int_t j2, Double_t ma, Double_t mb) const 
 {

   // Momenta definition.
   Double_t p = get_q(MBs,ma,mb);
   Double_t q_1 = get_q(ma,MPion,MKaon);
   Double_t q_2 = get_q(mb,MPion,MKaon);

   // Normalization constants.
   Double_t m0 = mv;
   Double_t p0 = get_q(MBs,m0,m0);
   Double_t q0 = get_q(m0,MPion,MKaon);

   // Decay of the Bs.
   Int_t L = abs(j1-j2);
   Double_t FL_Bs = pow(p/p0,L)*sqrt(Blatt_Weisskopf2(p,p0,L));

   // Decay of the K+pi- pair.
   Double_t FL_Kpi1 = pow((q_1/q0),j1)*sqrt(Blatt_Weisskopf2(q_1,q0,j1));

   // Decay of the K-pi+ pair.
   Double_t FL_Kpi2 = pow((q_2/q0),j2)*sqrt(Blatt_Weisskopf2(q_2,q0,j2));

   return FL_Bs*FL_Kpi1*FL_Kpi2;

 }

// ---------------------------------------------------
// Relativistic Breit-Wigner amplitude.

TComplex ComputeIntegrals::Resonance(Double_t m, Double_t m0, Double_t g0, Int_t J) const
 {

   // Angular momenta definition.
   Double_t q = get_q(m,MPion,MKaon);
   Double_t q0 = get_q(m0,MPion,MKaon);

   // Running width.
   Double_t gamma = g0*pow(q/q0,2*J+1)*(m0/m)*Blatt_Weisskopf2(q,q0,J);

   // Amplitude.
   TComplex num(m0*g0,0.);
   TComplex denom(m0*m0-m*m,-m0*gamma);
   TComplex BW = num/denom;

   if (J == 1) {return BW*TComplex(1.,-1.5707963267948966,1);}
   else if (J == 2) {return BW*TComplex(1.,-0.006008360479292941,1);}
   return BW;

 }

// ---------------------------------------------------
// Lass parametrization for the S wave.

TComplex ComputeIntegrals::Lass(Double_t m, Double_t m0, Double_t g0) const 
 { 

   TComplex i(0,1);
   
   Double_t q = get_q(m,MPion,MKaon);
   Double_t q0 = get_q(m0,MPion,MKaon);

   Double_t cotg_deltaB = 1./(a_lass*q)+0.5*r_lass*q;
   Double_t deltaB = atan(1./cotg_deltaB);
   TComplex expo(1.,2.*deltaB,1);

   Double_t gamma = g0*(q/q0)*(m0/m);
   Double_t cotg_deltaR = (m0*m0-m*m)/(m0*gamma);

   TComplex T = 1./(cotg_deltaB-i)+expo/(cotg_deltaR-i);

   return T*TComplex(1.,-0.9141811350146497,1);

 } 

// ---------------------------------------------------
// Alternative Lass parametrization for the S wave based on chiral perturbation theory.

TComplex ComputeIntegrals::Lass_chiral(Double_t m) const 
 { 

   // Auxiliar variables.
   TComplex i(0,1);
   Double_t svar = m*m;
   Double_t svar2 = svar*svar;
   Double_t MPion2 = MPion*MPion;
   Double_t MKaon2 = MKaon*MKaon;
   Double_t Lambda = svar2-2*svar*(MPion2+MKaon2)+(MPion2-MKaon2)*(MPion2-MKaon2);
   Double_t sqrtLambda = sqrt(Lambda);
   Double_t F_lass2 = F_lass*F_lass;
   Double_t F_lass4 = F_lass2*F_lass2;

   // Amplitude for chiral contact term + single resonance.
   Double_t L0fun = 1.+(MPion2+MKaon2)/(MPion2-MKaon2)*log(MPion/MKaon)-(MPion2-MKaon2)/svar*log(MPion/MKaon);
   TComplex Lbarfun = L0fun-sqrtLambda/svar*log((svar-MPion2-MKaon2+sqrtLambda)/(2.*MPion*MKaon))+i*pi*sqrtLambda/svar;
   TComplex Omegabar = -Lbarfun/(16.*pi*pi);
   Double_t alphafun = 3./(2.*F_lass4)*pow(cd_lass*svar-(cd_lass-cm_lass)*(MPion2+MKaon2),2);
   Double_t KernelC = (5.*svar/8.-(MPion2+MKaon2)/4.-3.*(MPion2-MKaon2)*(MPion2-MKaon2)/(8.*svar))/F_lass2;
   Double_t Kernel = KernelC-alphafun/(svar-MR_lass*MR_lass);
   TComplex T = Kernel/(1.+(C_lass+Omegabar)*Kernel);

   return T;

 }

// ---------------------------------------------------
// Auxiliar function used in the S-wave propagator obtained from theory.

Double_t ComputeIntegrals::omega_Stheo(Double_t m) const 
 {

   Double_t m_GeV = m/1000.;
   Double_t svar_GeV = m_GeV*m_GeV;
   Double_t Delta_Kpi = MKaon/1000.*MKaon/1000.-MPion/1000.*MPion/1000.;
   Double_t y_s = pow((svar_GeV-Delta_Kpi)/(svar_GeV+Delta_Kpi),2);
   Double_t y_s0 = pow((s0_Stheo-Delta_Kpi)/(s0_Stheo+Delta_Kpi),2);
   return (sqrt(y_s)-alpha_Stheo*sqrt(y_s0-y_s))/(sqrt(y_s)+alpha_Stheo*sqrt(y_s0-y_s));

 }

// ---------------------------------------------------
// Auxiliar function used in the P-wave propagator obtained from theory.

Double_t ComputeIntegrals::omega_Ptheo(Double_t m) const 
 {

   Double_t m_GeV = m/1000.;
   Double_t svar_GeV = m_GeV*m_GeV;
   Double_t Delta_Kpi = MKaon/1000.*MKaon/1000.-MPion/1000.*MPion/1000.;
   Double_t y_s = pow((svar_GeV-Delta_Kpi)/(svar_GeV+Delta_Kpi),2);
   Double_t y_s0 = pow((s0_Ptheo-Delta_Kpi)/(s0_Ptheo+Delta_Kpi),2);
   return (sqrt(y_s)-alpha_Ptheo*sqrt(y_s0-y_s))/(sqrt(y_s)+alpha_Ptheo*sqrt(y_s0-y_s));

 }

// ---------------------------------------------------
// Auxiliar function used in the S-wave propagator obtained from theory.

Double_t ComputeIntegrals::cotdelta_Stheo(Double_t m) const 
 {

   Double_t m_GeV = m/1000.;
   Double_t svar_GeV = m_GeV*m_GeV;
   Double_t q_Kpi_GeV = get_q(m,MKaon,MPion)/1000.;
   Double_t omega_func = omega_Stheo(m);
   return m_GeV/(2.*q_Kpi_GeV*(svar_GeV-sAdler_Stheo))*(B0_Stheo+B1_Stheo*omega_func);

 }

// ---------------------------------------------------
// Auxiliar function used in the P-wave propagator obtained from theory.

Double_t ComputeIntegrals::cotdelta_Ptheo(Double_t m) const 
 {

   Double_t m_GeV = m/1000.;
   Double_t svar_GeV = m_GeV*m_GeV;
   Double_t q_Kpi_GeV = get_q(m,MKaon,MPion)/1000.;
   Double_t omega_func = omega_Ptheo(m);
   return m_GeV/(2.*q_Kpi_GeV*q_Kpi_GeV*q_Kpi_GeV)*(mr_Ptheo*mr_Ptheo-svar_GeV)*(B0_Ptheo+B1_Ptheo*omega_func+B2_Ptheo*omega_func*omega_func);

 }

// ---------------------------------------------------
// Auxiliar function used in the S-wave propagator obtained from theory.

Double_t ComputeIntegrals::get_p1_Stheo(Double_t q) const 
 {

   return 1.+a_Stheo*q/1000.*q/1000.+b_Stheo*q/1000.*q/1000.*q/1000.*q/1000.;

 }

// ---------------------------------------------------
// Auxiliar function used in the S-wave propagator obtained from theory.

Double_t ComputeIntegrals::get_p2_Stheo(Double_t q) const 
 {

   return 1.+c_Stheo*q/1000.*q/1000.;

 }

// ---------------------------------------------------
// Auxiliar function used in the P-wave propagator obtained from theory.

Double_t ComputeIntegrals::get_p1_Ptheo(Double_t q) const 
 {

   return 1.+a1_Ptheo*q/1000.*q/1000.;

 }

// ---------------------------------------------------
// Auxiliar function used in the P-wave propagator obtained from theory.

Double_t ComputeIntegrals::get_p2_Ptheo(Double_t q) const 
 {

   return 1.+a2_Ptheo*q/1000.*q/1000.;

 }

// ---------------------------------------------------
// Auxiliar function used in the P-wave propagator obtained from theory.

Double_t ComputeIntegrals::get_p3_Ptheo(Double_t q) const 
 {

   return 1.+a3_Ptheo*q/1000.*q/1000.;

 }

// ---------------------------------------------------
// Auxiliar function used in the D-wave propagator obtained from theory.

Double_t ComputeIntegrals::get_p1_Dtheo(Double_t q) const 
 {

   return 1.+a_Dtheo*q/1000.*q/1000.;

 }

// ---------------------------------------------------
// Auxiliar function used in the propagators obtained from theory.

Double_t ComputeIntegrals::Theta_Keta(Double_t m) const 
 {

   if (m>=(MKaon+MEta)) {return 1.;}
   return 0.;

 }

// ---------------------------------------------------
// Auxiliar function used in the propagators obtained from theory.

Double_t ComputeIntegrals::Theta_Ketaprime(Double_t m) const 
 {

   if (m>=(MKaon+MEtaprime)) {return 1.;}
   return 0.;

 }

// ---------------------------------------------------
// S-wave propagator obtained from theory.

TComplex ComputeIntegrals::Prop_Stheo(Double_t m) const 
 { 

   // Auxiliar quantities.
   TComplex i(0,1);
   Double_t m_GeV = m/1000.;
   Double_t svar_GeV = m_GeV*m_GeV;
   Double_t q_Kpi_GeV = get_q(m,MKaon,MPion)/1000.;
   Double_t q_Keta_GeV = get_q(m,MKaon,MEta)/1000.;

   // Kpi decay amplitude.
   TComplex T;

   // Parametrisation in the elastic region.
   if (m<(MKaon+MEta)) {
      T = 1./(cotdelta_Stheo(m)-i);
   }

   // Parametrisation in the inelastic region.
   else {
      TComplex S0b(1.,2.*q_Keta_GeV*(phi0_Stheo+phi1_Stheo*q_Keta_GeV*q_Keta_GeV),1);
      Double_t q_Kpi_r1_GeV = get_q(sqrtsr1_Stheo*1000.,MKaon,MPion)/1000.;
      Double_t q_Keta_r1_GeV = get_q(sqrtsr1_Stheo*1000.,MKaon,MEta)/1000.;
      Double_t q_Kpi_r2_GeV = get_q(sqrtsr2_Stheo*1000.,MKaon,MPion)/1000.;
      Double_t q_Keta_r2_GeV = get_q(sqrtsr2_Stheo*1000.,MKaon,MEta)/1000.;
      Double_t q_Kpi_hat_GeV = get_q(MKaon+MEta,MKaon,MPion)/1000.;
      Double_t beta_Stheo = 1./cotdelta_Stheo(MKaon+MEta);
      Double_t P1_s = (sqrtsr1_Stheo*sqrtsr1_Stheo-svar_GeV)*beta_Stheo+e1_Stheo*G1_Stheo*(get_p1_Stheo(q_Kpi_GeV*1000.)*(q_Kpi_GeV-q_Kpi_hat_GeV))/(get_p1_Stheo(q_Kpi_r1_GeV*1000.)*(q_Kpi_r1_GeV-q_Kpi_hat_GeV));
      Double_t Q1_s = (1.-e1_Stheo)*G1_Stheo*get_p1_Stheo(q_Kpi_GeV*1000.)/get_p1_Stheo(q_Kpi_r1_GeV*1000.)*q_Keta_GeV/q_Keta_r1_GeV*Theta_Keta(m);
      Double_t P2_s = e2_Stheo*G2_Stheo*(get_p2_Stheo(q_Kpi_GeV*1000.)*(q_Kpi_GeV-q_Kpi_hat_GeV))/(get_p2_Stheo(q_Kpi_r2_GeV*1000.)*(q_Kpi_r2_GeV-q_Kpi_hat_GeV));
      Double_t Q2_s = (1.-e2_Stheo)*G2_Stheo*get_p2_Stheo(q_Kpi_GeV*1000.)/get_p2_Stheo(q_Kpi_r2_GeV*1000.)*q_Keta_GeV/q_Keta_r2_GeV*Theta_Keta(m);
      TComplex S1r = (sqrtsr1_Stheo*sqrtsr1_Stheo-svar_GeV+i*(P1_s-Q1_s))/(sqrtsr1_Stheo*sqrtsr1_Stheo-svar_GeV-i*(P1_s+Q1_s));
      TComplex S2r = (sqrtsr2_Stheo*sqrtsr2_Stheo-svar_GeV+i*(P2_s-Q2_s))/(sqrtsr2_Stheo*sqrtsr2_Stheo-svar_GeV-i*(P2_s+Q2_s));
      T = (S0b*S1r*S2r-1.)/(2.*i);
   }

   // Polynomical correction to convert from scattering to decay mass amplitudes.
   Double_t xm = (m-1175.)/425.;
   Double_t modulus = sqrt(1.+c1_pol_Stheo*xm+c2_pol_Stheo*(2.*xm*xm-1.)+c3_pol_Stheo*(4.*xm*xm*xm-3.*xm)+c4_pol_Stheo*(8.*xm*xm*xm*xm-8.*xm*xm+1.));

   return TComplex(modulus,T.Theta()-0.7095863518296103,1);

 }

// ---------------------------------------------------
// P-wave propagator obtained from theory.

TComplex ComputeIntegrals::Prop_Ptheo(Double_t m) const 
 { 

   // Auxiliar quantities.
   TComplex i(0,1);
   Double_t m_GeV = m/1000.;
   Double_t svar_GeV = m_GeV*m_GeV;
   Double_t q_Kpi_GeV = get_q(m,MKaon,MPion)/1000.;
   Double_t q_Keta_GeV = get_q(m,MKaon,MEta)/1000.;

   // Kpi decay amplitude.
   TComplex T;

   // Parametrisation in the elastic region.
   if (m<(MKaon+MEta)) {
      T = 1./(cotdelta_Ptheo(m)-i);
   }

   // Parametrisation in the inelastic region.
   else {
      Double_t q_Kpi_r1_GeV = get_q(sqrtsr1_Ptheo*1000.,MKaon,MPion)/1000.;
      Double_t q_Keta_r1_GeV = get_q(sqrtsr1_Ptheo*1000.,MKaon,MEta)/1000.;
      Double_t q_Kpi_r2_GeV = get_q(sqrtsr2_Ptheo*1000.,MKaon,MPion)/1000.;
      Double_t q_Keta_r2_GeV = get_q(sqrtsr2_Ptheo*1000.,MKaon,MEta)/1000.;
      Double_t q_Kpi_r3_GeV = get_q(sqrtsr3_Ptheo*1000.,MKaon,MPion)/1000.;
      Double_t q_Keta_r3_GeV = get_q(sqrtsr3_Ptheo*1000.,MKaon,MEta)/1000.;
      Double_t q_Kpi_hat_GeV = get_q(MKaon+MEta,MKaon,MPion)/1000.;
      Double_t beta_Ptheo = 1./cotdelta_Ptheo(MKaon+MEta);
      Double_t P1_s = (sqrtsr1_Ptheo*sqrtsr1_Ptheo-svar_GeV)*beta_Ptheo+e1_Ptheo*G1_Ptheo*(get_p1_Ptheo(q_Kpi_GeV*1000.)*q_Kpi_GeV*(q_Kpi_GeV*q_Kpi_GeV-q_Kpi_hat_GeV*q_Kpi_hat_GeV))/(get_p1_Ptheo(q_Kpi_r1_GeV*1000.)*q_Kpi_r1_GeV*(q_Kpi_r1_GeV*q_Kpi_r1_GeV-q_Kpi_hat_GeV*q_Kpi_hat_GeV));
      Double_t P2_s = e2_Ptheo*G2_Ptheo*(get_p2_Ptheo(q_Kpi_GeV*1000.)*q_Kpi_GeV*(q_Kpi_GeV*q_Kpi_GeV-q_Kpi_hat_GeV*q_Kpi_hat_GeV))/(get_p2_Ptheo(q_Kpi_r2_GeV*1000.)*q_Kpi_r2_GeV*(q_Kpi_r2_GeV*q_Kpi_r2_GeV-q_Kpi_hat_GeV*q_Kpi_hat_GeV));
      Double_t P3_s = e3_Ptheo*G3_Ptheo*(get_p3_Ptheo(q_Kpi_GeV*1000.)*q_Kpi_GeV*(q_Kpi_GeV*q_Kpi_GeV-q_Kpi_hat_GeV*q_Kpi_hat_GeV))/(get_p3_Ptheo(q_Kpi_r3_GeV*1000.)*q_Kpi_r3_GeV*(q_Kpi_r3_GeV*q_Kpi_r3_GeV-q_Kpi_hat_GeV*q_Kpi_hat_GeV));
      Double_t Q1_s = 0.;
      Double_t Q2_s = (1.-e2_Ptheo)*G2_Ptheo*get_p2_Ptheo(q_Kpi_GeV*1000.)/get_p2_Ptheo(q_Kpi_r2_GeV*1000.)*pow(q_Keta_GeV/q_Keta_r2_GeV,3)*Theta_Keta(m);
      Double_t Q3_s = (1.-e3_Ptheo)*G3_Ptheo*get_p3_Ptheo(q_Kpi_GeV*1000.)/get_p3_Ptheo(q_Kpi_r3_GeV*1000.)*pow(q_Keta_GeV/q_Keta_r3_GeV,3)*Theta_Keta(m);
      TComplex S1r = (sqrtsr1_Ptheo*sqrtsr1_Ptheo-svar_GeV+i*(P1_s-Q1_s))/(sqrtsr1_Ptheo*sqrtsr1_Ptheo-svar_GeV-i*(P1_s+Q1_s));
      TComplex S2r = (sqrtsr2_Ptheo*sqrtsr2_Ptheo-svar_GeV+i*(P2_s-Q2_s))/(sqrtsr2_Ptheo*sqrtsr2_Ptheo-svar_GeV-i*(P2_s+Q2_s));
      TComplex S3r = (sqrtsr3_Ptheo*sqrtsr3_Ptheo-svar_GeV+i*(P3_s-Q3_s))/(sqrtsr3_Ptheo*sqrtsr3_Ptheo-svar_GeV-i*(P3_s+Q3_s));
      T = (S1r*S2r*S3r-1.)/(2.*i);

   }

   return T*TComplex(1.,-1.5745153880460114,1);

 }

// ---------------------------------------------------
// D-wave propagator obtained from theory.

TComplex ComputeIntegrals::Prop_Dtheo(Double_t m) const 
 { 

   TComplex i(0,1);
   Double_t m_GeV = m/1000.;
   Double_t svar_GeV = m_GeV*m_GeV;
   Double_t q_Kpi_GeV = get_q(m,MKaon,MPion)/1000.;
   Double_t q_Keta_GeV = get_q(m,MKaon,MEta)/1000.;
   Double_t q_Ketaprime_GeV = get_q(m,MKaon,MEtaprime)/1000.;

   // Kpi decay amplitude.
   TComplex T;

   // Parametrisation in the whole region.
   TComplex S0b(1.,2.*(phi0_Dtheo*pow(q_Keta_GeV,5)*Theta_Keta(m)+phi1_Dtheo*pow(q_Ketaprime_GeV,5)*Theta_Ketaprime(m)),1);
   Double_t q_Kpi_r1_GeV = get_q(sqrtsr1_Dtheo*1000.,MKaon,MPion)/1000.;
   Double_t q_Keta_r1_GeV = get_q(sqrtsr1_Dtheo*1000.,MKaon,MEta)/1000.;
   Double_t P1_s = e1_Dtheo*G1_Dtheo*get_p1_Dtheo(q_Kpi_GeV*1000.)/get_p1_Dtheo(q_Kpi_r1_GeV*1000.)*pow(q_Kpi_GeV/q_Kpi_r1_GeV,5);
   Double_t Q1_s = (1.-e1_Dtheo)*G1_Dtheo*get_p1_Dtheo(q_Kpi_GeV*1000.)/get_p1_Dtheo(q_Kpi_r1_GeV*1000.)*pow(q_Keta_GeV/q_Keta_r1_GeV,5)*Theta_Keta(m);
   TComplex S1r = (sqrtsr1_Dtheo*sqrtsr1_Dtheo-svar_GeV+i*(P1_s-Q1_s))/(sqrtsr1_Dtheo*sqrtsr1_Dtheo-svar_GeV-i*(P1_s+Q1_s));
   T = (S0b*S1r-1.)/(2.*i);

   return T*TComplex(1.,-0.0022258232266847374,1);

 }

// ---------------------------------------------------
// Palano scalar Kpi mass amplitude.

TComplex ComputeIntegrals::Prop_S_Palano(Double_t m) const 
 { 

   TComplex i(0,1);
   Double_t m_GeV = m/1000.;
   Double_t svar_GeV = m_GeV*m_GeV;
   Double_t q_Kpi_GeV = get_q(m,MKaon,MPion)/1000.;
   Double_t q_Keta_GeV = get_q(m,MKaon,MEta)/1000.;

   Double_t rho_1 = 2.*q_Kpi_GeV/m_GeV;
   Double_t rho_2 = 2.*q_Keta_GeV/m_GeV;

   Double_t sbot_GeV = 0.36;
   Double_t stop_GeV = 5.832;
   Double_t X = (2.*svar_GeV-(stop_GeV+sbot_GeV))/(stop_GeV-sbot_GeV);

   Double_t K11 = (svar_GeV-s_A_palano)/s_Kpi_palano*(g_1_a_palano*g_1_a_palano/(svar_GeV-s_a_palano)+g_1_b_palano*g_1_b_palano/(svar_GeV-s_b_palano)+C_11_0_palano+C_11_1_palano*X+C_11_2_palano*X*X+C_11_3_palano*X*X*X);
   Double_t K12 = (svar_GeV-s_A_palano)/s_Kpi_palano*(g_1_a_palano*g_2_a_palano/(svar_GeV-s_a_palano)+g_1_b_palano*g_2_b_palano/(svar_GeV-s_b_palano)+C_12_0_palano+C_12_1_palano*X+C_12_2_palano*X*X+C_12_3_palano*X*X*X);
   Double_t K22 = (svar_GeV-s_A_palano)/s_Kpi_palano*(g_2_a_palano*g_2_a_palano/(svar_GeV-s_a_palano)+g_2_b_palano*g_2_b_palano/(svar_GeV-s_b_palano)+C_22_0_palano+C_22_1_palano*X+C_22_2_palano*X*X+C_22_3_palano*X*X*X);

   Double_t detK = K11*K22-K12*K12;
   TComplex Delta(1.-rho_1*rho_2*detK,-rho_1*K11-rho_2*K22);

   TComplex T11_hat = s_Kpi_palano/(svar_GeV-s_A_palano)*(K11-rho_2*detK)/Delta;
   TComplex T12_hat = s_Kpi_palano/(svar_GeV-s_A_palano)*K12/Delta;

   Double_t xm = (m-1175.)/425.;
   Double_t alpha_1_s = A_1_0_palano+A_1_1_palano*xm+A_1_2_palano*(2.*xm*xm-1.)+A_1_3_palano*(4.*xm*xm*xm-3.*xm)+A_1_4_palano*(8.*xm*xm*xm*xm-8.*xm*xm+1.);
   Double_t alpha_2_s = A_2_0_palano+A_2_1_palano*xm+A_2_2_palano*(2.*xm*xm-1.)+A_2_3_palano*(4.*xm*xm*xm-3.*xm)+A_2_4_palano*(8.*xm*xm*xm*xm-8.*xm*xm+1.);

   TComplex T = alpha_1_s*T11_hat+alpha_2_s*T12_hat;

   return T*TComplex(1.,-0.0758670,1);

 }

// ---------------------------------------------------
// Kpi mass amplitude.

TComplex ComputeIntegrals::Mji(Double_t m, Int_t ji) const 
 {

   TComplex T;

   if (ji == 0)
	{
	T = Prop_Stheo(m);
	}

   else if (ji == 1)
	{
	T = Resonance(m,mv,gv,1);
	}

   else if (ji == 2)
	{
	T = Resonance(m,mt,gt,2);
	}
   
   return T;

 }

// ---------------------------------------------------
// Invariant mass dependent factor for each wave.
 
TComplex ComputeIntegrals::Mj1j2(Double_t ma, Double_t mb, Int_t j1, Int_t j2) const 
 { 

 if ((j1 == 0) and (j2 == 0)) {return Mji(ma,0)*Mji(mb,0)*FL_j1j2(0,0,ma,mb)*(1./sqrt(Im00));}
 else if ((j1 == 0) and (j2 == 1)) {return Mji(ma,0)*Mji(mb,1)*FL_j1j2(0,1,ma,mb)*(1./sqrt(Im01));}
 else if ((j1 == 1) and (j2 == 0)) {return Mji(ma,1)*Mji(mb,0)*FL_j1j2(1,0,ma,mb)*(1./sqrt(Im10));}
 else if ((j1 == 0) and (j2 == 2)) {return Mji(ma,0)*Mji(mb,2)*FL_j1j2(0,2,ma,mb)*(1./sqrt(Im02));}
 else if ((j1 == 2) and (j2 == 0)) {return Mji(ma,2)*Mji(mb,0)*FL_j1j2(2,0,ma,mb)*(1./sqrt(Im20));}
 else if ((j1 == 1) and (j2 == 1)) {return Mji(ma,1)*Mji(mb,1)*FL_j1j2(1,1,ma,mb)*(1./sqrt(Im11));}
 else if ((j1 == 1) and (j2 == 2)) {return Mji(ma,1)*Mji(mb,2)*FL_j1j2(1,2,ma,mb)*(1./sqrt(Im12));}
 else if ((j1 == 2) and (j2 == 1)) {return Mji(ma,2)*Mji(mb,1)*FL_j1j2(2,1,ma,mb)*(1./sqrt(Im21));}
 else if ((j1 == 2) and (j2 == 2)) {return Mji(ma,2)*Mji(mb,2)*FL_j1j2(2,2,ma,mb)*(1./sqrt(Im22));}

 throw std::invalid_argument( "Invalid argument #5" );

 }

// ---------------------------------------------------
// Phase space factor.

Double_t ComputeIntegrals::phasespace(Double_t ma, Double_t mb) const 
 { 
 
   Double_t Q1 = get_q(ma,MKaon,MPion)/get_q(mv,MKaon,MPion);
   Double_t Q2 = get_q(mb,MKaon,MPion)/get_q(mv,MKaon,MPion);
   Double_t QB = get_q(MBs,ma,mb)/get_q(MBs,mv,mv);
   Double_t phsp = Q1*Q2*QB;

   return phsp;

 } 

// ---------------------------------------------------

TComplex ComputeIntegrals::hj1j2j1pj2p(Double_t ma, Double_t mb, Int_t j1, Int_t j2, Int_t j1p, Int_t j2p) const 
 { 

   return Mj1j2(ma,mb,j1,j2)*TComplex::Conjugate(Mj1j2(ma,mb,j1p,j2p))*phasespace(ma,mb);

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::accTime(Double_t tau) const 
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

Double_t ComputeIntegrals::accTimeParam(Double_t tau) const 
 { 
   
   return tau*tau*tau/(accpar.a_acc(year_opt,trig_opt,wide_window)+tau*tau*tau)*(1.+accpar.b_acc(year_opt,trig_opt,wide_window)*tau+accpar.c_acc(year_opt,trig_opt,wide_window)*tau*tau);

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::accTimeHisto(Double_t tau) const 
 { 

   for (int i=0; i<TAcc.nbins; ++i) {
      if (tau >= TAcc.bounds(i) and tau < TAcc.bounds(i+1)) {return TAcc.val(year_opt,trig_opt,wide_window,i);}
   }

   return TAcc.val(year_opt,trig_opt,wide_window,TAcc.nbins-1);

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::accAng(Double_t x) const
 { 

   if (acctype == 0) {return 1.;}
   else if (acctype == 1 or acctype == 2) {return 1.+accpar.k1(year_opt,trig_opt,wide_window)*x+accpar.k2(year_opt,trig_opt,wide_window)*(2.*x*x-1.)+accpar.k3(year_opt,trig_opt,wide_window)*(4.*x*x*x-3.*x)+accpar.k4(year_opt,trig_opt,wide_window)*(8.*x*x*x*x-8.*x*x+1.)+accpar.k5(year_opt,trig_opt,wide_window)*(16.*x*x*x*x*x-20.*x*x*x+5.*x);}
   else if (acctype == 3) {return 1.+genaccpar.k1_gen(wide_window)*x+genaccpar.k2_gen(wide_window)*(2.*x*x-1.)+genaccpar.k3_gen(wide_window)*(4.*x*x*x-3.*x)+genaccpar.k4_gen(wide_window)*(8.*x*x*x*x-8.*x*x+1.)+genaccpar.k5_gen(wide_window)*(16.*x*x*x*x*x-20.*x*x*x+5.*x);}

   return 0.;

 }

// ---------------------------------------------------

Double_t ComputeIntegrals::accMass(Double_t m) const 
 { 
   
   if (acctype == 0) {return 1.;}
   else if (acctype == 1 or acctype == 2) {return 1. + accpar.p1(year_opt,trig_opt,wide_window)*m;}
   else if (acctype == 3) {return 1. + genaccpar.p1_gen(wide_window)*m;}

   return 0.;

 }

// ---------------------------------------------------

 Double_t ComputeIntegrals::evaluate() const 
 {

	// Integrals for the normalization of the mass terms.
 	if (option == 100) {return hj1j2j1pj2p(m1,m2,0,0,0,0).Re();}
	else if (option == 101) {return hj1j2j1pj2p(m1,m2,0,1,0,1).Re();}
	else if (option == 110) {return hj1j2j1pj2p(m1,m2,1,0,1,0).Re();}
	else if (option == 102) {return hj1j2j1pj2p(m1,m2,0,2,0,2).Re();}
	else if (option == 120) {return hj1j2j1pj2p(m1,m2,2,0,2,0).Re();}
	else if (option == 111) {return hj1j2j1pj2p(m1,m2,1,1,1,1).Re();}
	else if (option == 112) {return hj1j2j1pj2p(m1,m2,1,2,1,2).Re();}
	else if (option == 121) {return hj1j2j1pj2p(m1,m2,2,1,2,1).Re();}
	else if (option == 122) {return hj1j2j1pj2p(m1,m2,2,2,2,2).Re();}

        // Integrals of the angular terms for plotting.
        else if (option == 21) {return fi(cos1,1)*accAng(cos1);}
        else if (option == 22) {return fi(cos1,2)*accAng(cos1);}
        else if (option == 23) {return fi(cos1,3)*accAng(cos1);}
        else if (option == 24) {return fi(cos1,4)*accAng(cos1);}
        else if (option == 25) {return fi(cos1,5)*accAng(cos1);}
        else if (option == 26) {return fi(cos1,6)*accAng(cos1);}
        else if (option == 27) {return fi(cos1,7)*accAng(cos1);}
        else if (option == 28) {return fi(cos1,8)*accAng(cos1);}
        else if (option == 29) {return fi(cos1,9)*accAng(cos1);}
        else if (option == 210) {return fi(cos1,10)*accAng(cos1);}
        else if (option == 211) {return fi(cos1,11)*accAng(cos1);}
        else if (option == 212) {return fi(cos1,12)*accAng(cos1);}
        else if (option == 213) {return fi(cos1,13)*accAng(cos1);}
        else if (option == 214) {return fi(cos1,14)*accAng(cos1);}
        else if (option == 215) {return fi(cos1,15)*accAng(cos1);}
        else if (option == 216) {return fi(cos1,16)*accAng(cos1);}
        else if (option == 217) {return fi(cos1,17)*accAng(cos1);}
        else if (option == 218) {return fi(cos1,18)*accAng(cos1);}

        // Integrals of the invariant mass dependent terms for plotting.
        else if (option == 31) {return hj1j2j1pj2p(m1,m2,0,0,0,1).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 32) {return hj1j2j1pj2p(m1,m2,0,0,0,2).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 33) {return hj1j2j1pj2p(m1,m2,0,0,1,1).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 34) {return hj1j2j1pj2p(m1,m2,0,0,1,2).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 35) {return hj1j2j1pj2p(m1,m2,0,0,2,2).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 36) {return hj1j2j1pj2p(m1,m2,0,1,0,2).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 37) {return hj1j2j1pj2p(m1,m2,0,1,1,0).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 38) {return hj1j2j1pj2p(m1,m2,0,1,1,1).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 39) {return hj1j2j1pj2p(m1,m2,0,1,1,2).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 310) {return hj1j2j1pj2p(m1,m2,1,0,0,2).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 311) {return hj1j2j1pj2p(m1,m2,1,0,1,2).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 312) {return hj1j2j1pj2p(m1,m2,0,1,2,2).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 313) {return hj1j2j1pj2p(m1,m2,0,2,1,1).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 314) {return hj1j2j1pj2p(m1,m2,0,2,1,2).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 315) {return hj1j2j1pj2p(m1,m2,0,2,2,0).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 316) {return hj1j2j1pj2p(m1,m2,2,0,1,2).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 317) {return hj1j2j1pj2p(m1,m2,0,2,2,2).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 318) {return hj1j2j1pj2p(m1,m2,1,1,1,2).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 319) {return hj1j2j1pj2p(m1,m2,1,1,2,2).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 320) {return hj1j2j1pj2p(m1,m2,1,2,2,1).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 321) {return hj1j2j1pj2p(m1,m2,1,2,2,2).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 322) {return hj1j2j1pj2p(m1,m2,0,0,0,0).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 323) {return hj1j2j1pj2p(m1,m2,0,1,0,1).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 324) {return hj1j2j1pj2p(m1,m2,1,0,1,0).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 325) {return hj1j2j1pj2p(m1,m2,0,2,0,2).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 326) {return hj1j2j1pj2p(m1,m2,2,0,2,0).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 327) {return hj1j2j1pj2p(m1,m2,1,1,1,1).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 328) {return hj1j2j1pj2p(m1,m2,1,2,1,2).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 329) {return hj1j2j1pj2p(m1,m2,2,1,2,1).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 330) {return hj1j2j1pj2p(m1,m2,2,2,2,2).Re()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 41) {return hj1j2j1pj2p(m1,m2,0,0,0,1).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 42) {return hj1j2j1pj2p(m1,m2,0,0,0,2).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 43) {return hj1j2j1pj2p(m1,m2,0,0,1,1).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 44) {return hj1j2j1pj2p(m1,m2,0,0,1,2).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 45) {return hj1j2j1pj2p(m1,m2,0,0,2,2).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 46) {return hj1j2j1pj2p(m1,m2,0,1,0,2).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 47) {return hj1j2j1pj2p(m1,m2,0,1,1,0).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 48) {return hj1j2j1pj2p(m1,m2,0,1,1,1).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 49) {return hj1j2j1pj2p(m1,m2,0,1,1,2).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 410) {return hj1j2j1pj2p(m1,m2,1,0,0,2).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 411) {return hj1j2j1pj2p(m1,m2,1,0,1,2).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 412) {return hj1j2j1pj2p(m1,m2,0,1,2,2).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 413) {return hj1j2j1pj2p(m1,m2,0,2,1,1).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 414) {return hj1j2j1pj2p(m1,m2,0,2,1,2).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 415) {return hj1j2j1pj2p(m1,m2,0,2,2,0).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 416) {return hj1j2j1pj2p(m1,m2,2,0,1,2).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 417) {return hj1j2j1pj2p(m1,m2,0,2,2,2).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 418) {return hj1j2j1pj2p(m1,m2,1,1,1,2).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 419) {return hj1j2j1pj2p(m1,m2,1,1,2,2).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 420) {return hj1j2j1pj2p(m1,m2,1,2,2,1).Im()*Im00*accMass(m1)*accMass(m2);}
        else if (option == 421) {return hj1j2j1pj2p(m1,m2,1,2,2,2).Im()*Im00*accMass(m1)*accMass(m2);}

	// Integrals of the time dependent terms for plotting.
	else if (option == 91) {return T_cosh_eff(t)*accTime(t);}
	else if (option == 92) {return T_sinh_eff(t)*accTime(t);}
	else if (option == 93) {return T_cos_eff(t)*accTime(t);}
	else if (option == 94) {return T_sin_eff(t)*accTime(t);}

	throw std::invalid_argument( "Invalid argument" );

}
