#ifndef TWOBODYMASSMODEL
#define TWOBODYMASSMODEL

#include "RooAbsReal.h"
#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsCategory.h"
#include "TComplex.h"
#include "TF1.h"
#include "RooMath.h"
#include "RooAbsNumGenerator.h"
#include "RooPrintable.h"
#include "RooArgSet.h"
#include "TRandom.h"

// Parameters of the LASS parametrisation of the Kpi scalar propagator
Double_t MR_lass = 1330.; // MeV/c2
Double_t F_lass = 102.722; // MeV
Double_t cd_lass = 35.2; // MeV
Double_t cm_lass = 1.027; //MeV
Double_t C_lass = -0.001; // (dimensionless)

// Parameters of the elastic+inelastic phenomenological parametrisation of the Kpi propagators
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

class TwoBodyMassModel : public RooAbsPdf {
public:
  TwoBodyMassModel() {} ; 
  TwoBodyMassModel(const char *name, const char *title,
	   RooAbsReal& _f00,
	   RooAbsReal& _f01,
	   RooAbsReal& _f10,
	   RooAbsReal& _f02,
	   RooAbsReal& _f20,
	   RooAbsReal& _f11,
	   RooAbsReal& _f12,
	   RooAbsReal& _f21,
	   RooAbsReal& _f22,
	   RooAbsReal& _m1,
	   RooAbsReal& _m2,
	   RooAbsReal& _c1,
	   RooAbsReal& _c2,
	   RooAbsReal& _c3,
	   RooAbsReal& _c4,
	   RooAbsReal& _ms,
	   RooAbsReal& _mv,
	   RooAbsReal& _gv,
	   RooAbsReal& _mt,
	   RooAbsReal& _gt);
  TwoBodyMassModel(const TwoBodyMassModel& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new TwoBodyMassModel(*this,newname); }
  inline virtual ~TwoBodyMassModel() { }

  RooRealProxy f00 ;
  RooRealProxy f01 ;
  RooRealProxy f10 ;
  RooRealProxy f02 ;
  RooRealProxy f20 ;
  RooRealProxy f11 ;
  RooRealProxy f12 ;
  RooRealProxy f21 ;
  RooRealProxy f22 ;
  RooRealProxy m1 ;
  RooRealProxy m2 ;
  RooRealProxy c1 ;
  RooRealProxy c2 ;
  RooRealProxy c3 ;
  RooRealProxy c4 ;
  RooRealProxy ms ;
  RooRealProxy mv ;
  RooRealProxy gv ;
  RooRealProxy mt ;
  RooRealProxy gt ;

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

  // Output.
  Double_t evaluate() const ;

private:

  ClassDef(TwoBodyMassModel,1)
};

#endif

