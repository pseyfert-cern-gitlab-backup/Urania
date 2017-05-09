#include "RooFit.h"
#include "Riostream.h"
#include "TwoBodyMassModel.h"
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

ClassImp(TwoBodyMassModel) 

// ---------------------------------------------------

 TwoBodyMassModel::TwoBodyMassModel(const char *name, const char *title,
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
                        RooAbsReal& _c5,
                        RooAbsReal& _c6,
                        RooAbsReal& _c7,
                        RooAbsReal& _c8,
                        RooAbsReal& _c9,
                        RooAbsReal& _ms,
                        RooAbsReal& _mv,
                        RooAbsReal& _gv,
                        RooAbsReal& _mt,
                        RooAbsReal& _gt):
   RooAbsPdf(name,title),
   f00("f00","f00",this,_f00),
   f01("f01","f01",this,_f01),
   f10("f10","f10",this,_f10),
   f02("f02","f02",this,_f02),
   f20("f20","f20",this,_f20),
   f11("f11","f11",this,_f11),
   f12("f12","f12",this,_f12),
   f21("f21","f21",this,_f21),
   f22("f22","f22",this,_f22),
   m1("m1","m1",this,_m1),
   m2("m2","m2",this,_m2),
   c1("c1","c1",this,_c1),
   c2("c2","c2",this,_c2),
   c3("c3","c3",this,_c3),
   c4("c4","c4",this,_c4),
   c5("c5","c5",this,_c5),
   c6("c6","c6",this,_c6),
   c7("c7","c7",this,_c7),
   c8("c8","c8",this,_c8),
   c9("c9","c9",this,_c9),
   ms("ms","ms",this,_ms),
   mv("mv","mv",this,_mv),
   gv("gv","gv",this,_gv),
   mt("mt","mt",this,_mt),
   gt("gt","gt",this,_gt)
 {
 }

// ---------------------------------------------------

 TwoBodyMassModel::TwoBodyMassModel(const TwoBodyMassModel& other, const char* name) :  
   RooAbsPdf(other,name),
   f00("f00",this,other.f00),
   f01("f01",this,other.f01),
   f10("f10",this,other.f10),
   f02("f02",this,other.f02),
   f20("f20",this,other.f20),
   f11("f11",this,other.f11),
   f12("f12",this,other.f12),
   f21("f21",this,other.f21),
   f22("f22",this,other.f22),
   m1("m1",this,other.m1),
   m2("m2",this,other.m2),
   c1("c1",this,other.c1),
   c2("c2",this,other.c2),
   c3("c3",this,other.c3),
   c4("c4",this,other.c4),
   c5("c5",this,other.c5),
   c6("c6",this,other.c6),
   c7("c7",this,other.c7),
   c8("c8",this,other.c8),
   c9("c9",this,other.c9),
   ms("ms",this,other.ms),
   mv("mv",this,other.mv),
   gv("gv",this,other.gv),
   mt("mt",this,other.mt),
   gt("gt",this,other.gt)
 {
 }

// ######################################################################################################
// I N V A R I A N T   M A S S   D E P E N D E N T   T E R M S
// ######################################################################################################

// ---------------------------------------------------
// Momentum of one of the two daughters in the rest frame of the mother.

Double_t TwoBodyMassModel::get_q(Double_t M, Double_t ma, Double_t mb) const 
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

Double_t TwoBodyMassModel::Blatt_Weisskopf2(Double_t q, Double_t q0, Int_t L) const 
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

Double_t TwoBodyMassModel::FL_j1j2(Int_t j1, Int_t j2, Double_t ma, Double_t mb) const 
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

TComplex TwoBodyMassModel::Resonance(Double_t m, Double_t m0, Double_t g0, Int_t J) const
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
   else if (J == 2) {return BW*TComplex(1.,-0.01011220614593752,1);}
   return BW;

 }

// ---------------------------------------------------
// Lass parametrization for the S wave.

TComplex TwoBodyMassModel::Lass(Double_t m, Double_t m0, Double_t g0) const 
 { 

   TComplex i(0,1);
   
   Double_t q = get_q(m,MPion,MKaon);
   Double_t q0 = get_q(m0,MPion,MKaon);

   Double_t cotg_deltaB = 1./(c1*q)+0.5*c2*q;
   Double_t deltaB = atan(1./cotg_deltaB);
   TComplex expo(1.,2.*deltaB,1);

   Double_t gamma = g0*(q/q0)*(m0/m);
   Double_t cotg_deltaR = (m0*m0-m*m)/(m0*gamma);

   TComplex T = 1./(cotg_deltaB-i)+expo/(cotg_deltaR-i);

   return T*TComplex(1.,-0.9100120858249479,1);

 } 

// ---------------------------------------------------
// Alternative Lass parametrization for the S wave based on chiral perturbation theory.

TComplex TwoBodyMassModel::Lass_chiral(Double_t m) const 
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
   Double_t alphafun = 3./(2.*F_lass4)*pow(c1*svar-(c1-c2)*(MPion2+MKaon2),2);
   Double_t KernelC = (5.*svar/8.-(MPion2+MKaon2)/4.-3.*(MPion2-MKaon2)*(MPion2-MKaon2)/(8.*svar))/F_lass2;
   Double_t Kernel = KernelC-alphafun/(svar-ms*ms);
   TComplex T = Kernel/(1.+(c3+Omegabar)*Kernel);

   return T;

 }

// ---------------------------------------------------
// Auxiliar function used in the S-wave propagator obtained from theory.

Double_t TwoBodyMassModel::omega_Stheo(Double_t m) const 
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

Double_t TwoBodyMassModel::omega_Ptheo(Double_t m) const 
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

Double_t TwoBodyMassModel::cotdelta_Stheo(Double_t m) const 
 {

   Double_t m_GeV = m/1000.;
   Double_t svar_GeV = m_GeV*m_GeV;
   Double_t q_Kpi_GeV = get_q(m,MKaon,MPion)/1000.;
   Double_t omega_func = omega_Stheo(m);
   return m_GeV/(2.*q_Kpi_GeV*(svar_GeV-sAdler_Stheo))*(B0_Stheo+B1_Stheo*omega_func);

 }

// ---------------------------------------------------
// Auxiliar function used in the P-wave propagator obtained from theory.

Double_t TwoBodyMassModel::cotdelta_Ptheo(Double_t m) const 
 {

   Double_t m_GeV = m/1000.;
   Double_t svar_GeV = m_GeV*m_GeV;
   Double_t q_Kpi_GeV = get_q(m,MKaon,MPion)/1000.;
   Double_t omega_func = omega_Ptheo(m);
   return m_GeV/(2.*q_Kpi_GeV*q_Kpi_GeV*q_Kpi_GeV)*(mr_Ptheo*mr_Ptheo-svar_GeV)*(B0_Ptheo+B1_Ptheo*omega_func+B2_Ptheo*omega_func*omega_func);

 }

// ---------------------------------------------------
// Auxiliar function used in the S-wave propagator obtained from theory.

Double_t TwoBodyMassModel::get_p1_Stheo(Double_t q) const 
 {

   return 1.+a_Stheo*q/1000.*q/1000.+b_Stheo*q/1000.*q/1000.*q/1000.*q/1000.;

 }

// ---------------------------------------------------
// Auxiliar function used in the S-wave propagator obtained from theory.

Double_t TwoBodyMassModel::get_p2_Stheo(Double_t q) const 
 {

   return 1.+c_Stheo*q/1000.*q/1000.;

 }

// ---------------------------------------------------
// Auxiliar function used in the P-wave propagator obtained from theory.

Double_t TwoBodyMassModel::get_p1_Ptheo(Double_t q) const 
 {

   return 1.+a1_Ptheo*q/1000.*q/1000.;

 }

// ---------------------------------------------------
// Auxiliar function used in the P-wave propagator obtained from theory.

Double_t TwoBodyMassModel::get_p2_Ptheo(Double_t q) const 
 {

   return 1.+a2_Ptheo*q/1000.*q/1000.;

 }

// ---------------------------------------------------
// Auxiliar function used in the P-wave propagator obtained from theory.

Double_t TwoBodyMassModel::get_p3_Ptheo(Double_t q) const 
 {

   return 1.+a3_Ptheo*q/1000.*q/1000.;

 }

// ---------------------------------------------------
// Auxiliar function used in the D-wave propagator obtained from theory.

Double_t TwoBodyMassModel::get_p1_Dtheo(Double_t q) const 
 {

   return 1.+a_Dtheo*q/1000.*q/1000.;

 }

// ---------------------------------------------------
// Auxiliar function used in the propagators obtained from theory.

Double_t TwoBodyMassModel::Theta_Keta(Double_t m) const 
 {

   if (m>=(MKaon+MEta)) {return 1.;}
   return 0.;

 }

// ---------------------------------------------------
// Auxiliar function used in the propagators obtained from theory.

Double_t TwoBodyMassModel::Theta_Ketaprime(Double_t m) const 
 {

   if (m>=(MKaon+MEtaprime)) {return 1.;}
   return 0.;

 }

// ---------------------------------------------------
// S-wave propagator obtained from theory.

TComplex TwoBodyMassModel::Prop_Stheo(Double_t m) const 
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
   Double_t pol_corr = sqrt(1.+c1*xm+c2*(2.*xm*xm-1.)+c3*(4.*xm*xm*xm-3.*xm)+c4*(8.*xm*xm*xm*xm-8.*xm*xm+1.));
   //Double_t pol_corr = sqrt(1.+c1*(xm+TMath::Sign(1,c1))+c2*(xm*xm-(c2<0))+c3*(xm*xm*xm+TMath::Sign(1,c3))+c4*(xm*xm*xm*xm-(c4<0)));
   //Double_t pol_corr = (1.+c1*(pow(xm,c2)-(c1<0))+c3*(pow((1.-xm),c4)-(c3<0)));
   //Double_t pol_corr = 1.-c1*pow(xm,c2);
   //Double_t pol_corr = pow(xm+c1,c2);
   //return T*TComplex(pol_corr,-0.7095863518296103,1);
   //Double_t pol_corr = sqrt(1.-c1*xm-c2*xm*xm-c3*xm*xm*xm-c4*xm*xm*xm*xm);
   return TComplex(pol_corr,T.Theta()-0.7095863518296103,1);

 }

// ---------------------------------------------------
// P-wave propagator obtained from theory.

TComplex TwoBodyMassModel::Prop_Ptheo(Double_t m) const 
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

TComplex TwoBodyMassModel::Prop_Dtheo(Double_t m) const 
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

TComplex TwoBodyMassModel::Prop_S_Palano(Double_t m) const 
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
   Double_t alpha_1_s = 1.+c1*xm+c2*(2.*xm*xm-1.)+c3*(4.*xm*xm*xm-3.*xm)+c4*(8.*xm*xm*xm*xm-8.*xm*xm+1.);
   Double_t alpha_2_s = c5+c6*xm+c7*(2.*xm*xm-1.)+c8*(4.*xm*xm*xm-3.*xm)+c9*(8.*xm*xm*xm*xm-8.*xm*xm+1.);

   TComplex T = alpha_1_s*T11_hat+alpha_2_s*T12_hat;

   return T*TComplex(1.,0.0533209,1);

 }

// ---------------------------------------------------
// Kpi mass amplitude.

TComplex TwoBodyMassModel::Mji(Double_t m, Int_t ji) const 
 {

   TComplex T;

   if (ji == 0)
	{
	T = Prop_S_Palano(m)/5.001755254370297;
	}

   else if (ji == 1)
	{
	T = Resonance(m,mv,gv,1)/8.632755409954383;
	}

   else if (ji == 2)
	{
	T = Resonance(m,mt,gt,2)/66.84493742623923;
	}
   
   return T;

 }

// ---------------------------------------------------
// Invariant mass dependent factor for each wave.
 
TComplex TwoBodyMassModel::Mj1j2(Double_t ma, Double_t mb, Int_t j1, Int_t j2) const 
 { 

 if ((j1 == 0) and (j2 == 0)) {return Mji(ma,0)*Mji(mb,0)*FL_j1j2(0,0,ma,mb);}
 else if ((j1 == 0) and (j2 == 1)) {return Mji(ma,0)*Mji(mb,1)*FL_j1j2(0,1,ma,mb);}
 else if ((j1 == 1) and (j2 == 0)) {return Mji(ma,1)*Mji(mb,0)*FL_j1j2(1,0,ma,mb);}
 else if ((j1 == 0) and (j2 == 2)) {return Mji(ma,0)*Mji(mb,2)*FL_j1j2(0,2,ma,mb);}
 else if ((j1 == 2) and (j2 == 0)) {return Mji(ma,2)*Mji(mb,0)*FL_j1j2(2,0,ma,mb);}
 else if ((j1 == 1) and (j2 == 1)) {return Mji(ma,1)*Mji(mb,1)*FL_j1j2(1,1,ma,mb);}
 else if ((j1 == 1) and (j2 == 2)) {return Mji(ma,1)*Mji(mb,2)*FL_j1j2(1,2,ma,mb);}
 else if ((j1 == 2) and (j2 == 1)) {return Mji(ma,2)*Mji(mb,1)*FL_j1j2(2,1,ma,mb);}
 else if ((j1 == 2) and (j2 == 2)) {return Mji(ma,2)*Mji(mb,2)*FL_j1j2(2,2,ma,mb);}

 throw std::invalid_argument( "Invalid argument #5" );

 }

// ---------------------------------------------------
// Phase space factor.

Double_t TwoBodyMassModel::phasespace(Double_t ma, Double_t mb) const 
 { 
 
   Double_t Q1 = get_q(ma,MKaon,MPion)/get_q(mv,MKaon,MPion);
   Double_t Q2 = get_q(mb,MKaon,MPion)/get_q(mv,MKaon,MPion);
   Double_t QB = get_q(MBs,ma,mb)/get_q(MBs,mv,mv);
   Double_t phsp = Q1*Q2*QB;

   return phsp;

 } 

// ---------------------------------------------------
// Invariant mass dependent functions.

TComplex TwoBodyMassModel::hj1j2j1pj2p(Double_t ma, Double_t mb, Int_t j1, Int_t j2, Int_t j1p, Int_t j2p) const 
 { 

   return Mj1j2(ma,mb,j1,j2)*TComplex::Conjugate(Mj1j2(ma,mb,j1p,j2p))*phasespace(ma,mb);

 }

// ######################################################################################################
// O U T P U T
// ######################################################################################################

// ---------------------------------------------------

Double_t TwoBodyMassModel::evaluate() const 
{

	return f00*hj1j2j1pj2p(m1,m2,0,0,0,0) + f01*hj1j2j1pj2p(m1,m2,0,1,0,1) + f02*hj1j2j1pj2p(m1,m2,0,2,0,2) + f10*hj1j2j1pj2p(m1,m2,1,0,1,0) + f11*hj1j2j1pj2p(m1,m2,1,1,1,1) + f12*hj1j2j1pj2p(m1,m2,1,2,1,2) + f20*hj1j2j1pj2p(m1,m2,2,0,2,0) + f21*hj1j2j1pj2p(m1,m2,2,1,2,1) + f22*hj1j2j1pj2p(m1,m2,2,2,2,2);

}

