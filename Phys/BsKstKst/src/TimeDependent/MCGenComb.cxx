#include "Riostream.h" 
#include "RooAbsPdf.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h"
#include "TF1.h"
#include <stdexcept>
#include "RooMath.h"
#include "MCGenComb.h"

Double_t Im00;
Double_t Im01;
Double_t Im10;
Double_t Im02;
Double_t Im20;
Double_t Im11;
Double_t Im12;
Double_t Im21;
Double_t Im22;

Double_t If1 = 2.0;
Double_t If2 = 0.0;
Double_t If3 = 1.57077954759;
Double_t If4 = 0.0;
Double_t If5 = -3.01938276343e-17;
Double_t If6 = 0.666666666667;
Double_t If7 = 0.0;
Double_t If8 = 0.392693148053;
Double_t If9 = 1.33333333333;
Double_t If10 = -0.392710950478;
Double_t If11 = 0.0;
Double_t If12 = 1.6;
Double_t If13 = 0.0;
Double_t If14 = 0.266666666667;
Double_t If15 = 1.17809877895;
Double_t If16 = -0.533333333333;
Double_t If17 = -4.20669213135e-18;
Double_t If18 = 1.06666666667;

Double_t Ih1Re_wide = 0.210674308615;
Double_t Ih2Re_wide = 0.168481474532;
Double_t Ih3Re_wide = 0.0449826771666;
Double_t Ih4Re_wide = 0.0316517588792;
Double_t Ih5Re_wide = -0.0222328866172;
Double_t Ih6Re_wide = -0.0655458310955;
Double_t Ih7Re_wide = 0.0428427938202;
Double_t Ih8Re_wide = 0.208326623502;
Double_t Ih9Re_wide = -0.0147519947924;
Double_t Ih10Re_wide = 0.0417930140843;
Double_t Ih11Re_wide = 0.17915203721;
Double_t Ih12Re_wide = -0.0369018250776;
Double_t Ih13Re_wide = -0.0122316265937;
Double_t Ih14Re_wide = 0.210790878285;
Double_t Ih15Re_wide = 0.0786634518371;
Double_t Ih16Re_wide = 0.0133877465969;
Double_t Ih17Re_wide = 0.168074970305;
Double_t Ih18Re_wide = -0.0637962331225;
Double_t Ih19Re_wide = -0.00944753832398;
Double_t Ih20Re_wide = 0.0163620627534;
Double_t Ih21Re_wide = -0.0656244770586;
Double_t Ih22Re_wide = 1.0;
Double_t Ih23Re_wide = 1.0;
Double_t Ih24Re_wide = 1.0;
Double_t Ih25Re_wide = 1.0;
Double_t Ih26Re_wide = 1.0;
Double_t Ih27Re_wide = 1.0;
Double_t Ih28Re_wide = 1.0;
Double_t Ih29Re_wide = 1.0;
Double_t Ih30Re_wide = 1.0;
Double_t Ih1Im_wide = -0.021192251321;
Double_t Ih2Im_wide = -0.224649192073;
Double_t Ih3Im_wide = -0.00676773837428;
Double_t Ih4Im_wide = -0.0490356230473;
Double_t Ih5Im_wide = -0.0759237016975;
Double_t Ih6Im_wide = -0.114451380807;
Double_t Ih7Im_wide = 3.38372025817e-19;
Double_t Ih8Im_wide = -0.0103471866888;
Double_t Ih9Im_wide = -0.022038365405;
Double_t Ih10Im_wide = -0.0427071753804;
Double_t Ih11Im_wide = -0.211318762391;
Double_t Ih12Im_wide = -0.0056606060619;
Double_t Ih13Im_wide = 0.0261017700773;
Double_t Ih14Im_wide = -0.0215766188472;
Double_t Ih15Im_wide = 0.0;
Double_t Ih16Im_wide = 0.0336980089248;
Double_t Ih17Im_wide = -0.225163555358;
Double_t Ih18Im_wide = -0.114696757267;
Double_t Ih19Im_wide = 0.0156878144642;
Double_t Ih20Im_wide = -1.03957775769e-18;
Double_t Ih21Im_wide = -0.114469570229;

Double_t Ih1Re_narrow = 0.316159333795;
Double_t Ih2Re_narrow = -0.691737860375;
Double_t Ih3Re_narrow = 0.0237356299233;
Double_t Ih4Re_narrow = -0.405939361116;
Double_t Ih5Re_narrow = 0.031223676883;
Double_t Ih6Re_narrow = -0.158128584509;
Double_t Ih7Re_narrow = 0.178581391285;
Double_t Ih8Re_narrow = 0.320521263616;
Double_t Ih9Re_narrow = -0.172910216501;
Double_t Ih10Re_narrow = -0.0306108140576;
Double_t Ih11Re_narrow = -0.690987276077;
Double_t Ih12Re_narrow = -0.185573394549;
Double_t Ih13Re_narrow = 0.0716027381539;
Double_t Ih14Re_narrow = 0.316134663147;
Double_t Ih15Re_narrow = 0.925772384633;
Double_t Ih16Re_narrow = 0.403261165453;
Double_t Ih17Re_narrow = -0.69174257483;
Double_t Ih18Re_narrow = -0.163132330449;
Double_t Ih19Re_narrow = -0.168198313627;
Double_t Ih20Re_narrow = 0.217668932415;
Double_t Ih21Re_narrow = -0.158098928823;
Double_t Ih22Re_narrow = 1.0;
Double_t Ih23Re_narrow = 1.0;
Double_t Ih24Re_narrow = 1.0;
Double_t Ih25Re_narrow = 1.0;
Double_t Ih26Re_narrow = 1.0;
Double_t Ih27Re_narrow = 1.0;
Double_t Ih28Re_narrow = 1.0;
Double_t Ih29Re_narrow = 1.0;
Double_t Ih30Re_narrow = 1.0;
Double_t Ih1Im_narrow = -0.280828249261;
Double_t Ih2Im_narrow = -0.668795452803;
Double_t Ih3Im_narrow = -0.177848950366;
Double_t Ih4Im_narrow = -0.0174500832472;
Double_t Ih5Im_narrow = 0.925273741175;
Double_t Ih6Im_narrow = -0.440050250754;
Double_t Ih7Im_narrow = 0.0;
Double_t Ih8Im_narrow = -0.276517822462;
Double_t Ih9Im_narrow = -0.094733633369;
Double_t Ih10Im_narrow = -0.406447376463;
Double_t Ih11Im_narrow = -0.670092437256;
Double_t Ih12Im_narrow = 0.410740623196;
Double_t Ih13Im_narrow = 0.185364300083;
Double_t Ih14Im_narrow = -0.280856465749;
Double_t Ih15Im_narrow = 0.0;
Double_t Ih16Im_narrow = -0.198076159805;
Double_t Ih17Im_narrow = -0.668787365907;
Double_t Ih18Im_narrow = -0.438734749398;
Double_t Ih19Im_narrow = 0.141928516262;
Double_t Ih20Im_narrow = -4.54550999917e-17;
Double_t Ih21Im_narrow = -0.440061356072;
Double_t gamma_Bs_Gen = 0.6614; // value from PDG 2014
Double_t delta_gamma_Bs_Gen = 0.091; // value from PDG 2014
Double_t gammaL = gamma_Bs_Gen+0.5*delta_gamma_Bs_Gen;
Double_t gammaH = gamma_Bs_Gen-0.5*delta_gamma_Bs_Gen;

ClassImp(MCGenComb) 

// ---------------------------------------------------

 MCGenComb::MCGenComb(const char *name, const char *title,
                        RooAbsReal& _gen_model,
                        RooAbsReal& _year,
                        RooAbsReal& _wide_window,
                        RooAbsReal& _m1,
                        RooAbsReal& _m2,
                        RooAbsReal& _cos1,
                        RooAbsReal& _cos2,
                        RooAbsReal& _phi,
                        RooAbsReal& _t,
                        RooAbsReal& _option) :
   RooAbsPdf(name,title),
   gen_model("gen_model","gen_model",this,_gen_model),
   year("year","year",this,_year),
   wide_window("wide_window","wide_window",this,_wide_window),
   m1("m1","m1",this,_m1),
   m2("m2","m2",this,_m2),
   cos1("cos1","cos1",this,_cos1),
   cos2("cos2","cos2",this,_cos2),
   phi("phi","phi",this,_phi),
   t("t","t",this,_t),
   option("option","option",this,_option)
 { 
 } 

// ---------------------------------------------------

 MCGenComb::MCGenComb(const MCGenComb& other, const char* name) :  
   RooAbsPdf(other,name),
   gen_model("gen_model",this,other.gen_model),
   year("year",this,other.year),
   wide_window("wide_window",this,other.wide_window),
   m1("m1",this,other.m1),
   m2("m2",this,other.m2),
   cos1("cos1",this,other.cos1),
   cos2("cos2",this,other.cos2),
   phi("phi",this,other.phi),
   t("t",this,other.t),
   option("option",this,other.option)
 { 
 } 

// ---------------------------------------------------
// Physical amplitudes.

TComplex MCGenComb::Aj1j2h(Int_t j1, Int_t j2, Int_t h) const 
 {

   if (j1 == 0) {
      if (j2 == 0) {return TComplex(0,0,1);}
      else if (j2 == 1) {return TComplex(0,0,1);}
      else if (j2 == 2) {return TComplex(0,0,1);}
   }
   else if (j1 == 1) {
      if (j2 == 0) {return TComplex(0,0,1);}
      else if (j2 == 1) {
         if (h == 0) {return TComplex(1,0,1);}
         else if (h == 1) {return TComplex(0.6/sqrt(2),0.5,1);}
         else if (h == 2) {return TComplex(0.6/sqrt(2),0.5+3.14159265358979323846264,1);}
      }
      else if (j2 == 2) {
         if (h == 0) {return TComplex(0,0,1);}
         else if (h == 1) {return TComplex(0,0,1);}
         else if (h == 2) {return TComplex(0,0,1);}
      }
   }
   else if (j1 == 2) {
      if (j2 == 0) {return TComplex(0,0,1);}
      else if (j2 == 1) {
         if (h == 0) {return TComplex(0,0,1);}
         else if (h == 1) {return TComplex(0,0,1);}
         else if (h == 2) {return TComplex(0,0,1);}
      }
      else if (j2 == 2) {
         if (h == 0) {return TComplex(0,0,1);}
         else if (h == 1) {return TComplex(0,0,1);}
         else if (h == 2) {return TComplex(0,0,1);}
         else if (h == 3) {return TComplex(0,0,1);}
         else if (h == 4) {return TComplex(0,0,1);}
      }
   }
   return TComplex(0,0,1);

 }

// ---------------------------------------------------
// Sign factor due to helicity.

Double_t MCGenComb::etah(Int_t h) const
 {

   if ((h == 2) or (h == 4)) {return -1.;}
   else {return 1.;}

 }

// ---------------------------------------------------
// Sign factor due to helicity and angular momenta.

Double_t MCGenComb::etaj1j2h(Int_t j1, Int_t j2, Int_t h) const
 {

   return pow(-1.,j1+j2)*etah(h);

 }

// ---------------------------------------------------
// CP conjugated complex amplitudes.

TComplex MCGenComb::Abarj1j2h(Int_t j1, Int_t j2, Int_t h) const
 {

   return etaj1j2h(j2,j1,h)*Aj1j2h(j2,j1,h);

 }

// ---------------------------------------------------
// Products of the physical amplitudes.

TComplex MCGenComb::AAj1j2hj1pj2php(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const 
 {

   return (Aj1j2h(j1,j2,h)*TComplex::Conjugate(Aj1j2h(j1p,j2p,hp))+Abarj1j2h(j1,j2,h)*TComplex::Conjugate(Abarj1j2h(j1p,j2p,hp)))-0.5*delta_gamma_Bs_Gen/gamma_Bs_Gen*(Aj1j2h(j1,j2,h)*TComplex::Conjugate(Abarj1j2h(j1p,j2p,hp))+Abarj1j2h(j1,j2,h)*TComplex::Conjugate(Aj1j2h(j1p,j2p,hp)));
  
 }

// ---------------------------------------------------
// Elementary angular functions in cos(theta).

Double_t MCGenComb::fi(Double_t x, Int_t i) const 
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

   else {throw std::invalid_argument( "Invalid argument 1" );}

   return f;

 }

// ---------------------------------------------------
// Elementary angular functions in phi.

Double_t MCGenComb::gi(Double_t x, Int_t i) const 
 { 

   if (i == 1) {return 1.;}
   else if (i == 2) {return cos(x);}
   else if (i == 3) {return sin(x);}
   else if (i == 4) {return cos(x)*cos(x);}
   else if (i == 5) {return sin(x)*cos(x);}
   else if (i == 6) {return sin(x)*sin(x);}
   else if (i == 7) {return cos(2.*x);}
   else if (i == 8) {return sin(2.*x);}
   else if (i == 9) {return cos(x)*cos(2.*x);}
   else if (i == 10) {return cos(x)*sin(2.*x);}
   else if (i == 11) {return sin(x)*cos(2.*x);}
   else if (i == 12) {return sin(x)*sin(2.*x);}
   else if (i == 13) {return cos(2.*x)*cos(2.*x);}
   else if (i == 14) {return sin(2.*x)*cos(2.*x);}
   else if (i == 15) {return sin(2.*x)*sin(2.*x);}

   throw std::invalid_argument( "Invalid argument 2" );

 }

// ---------------------------------------------------
//Angular functions in cos(theta).

Double_t MCGenComb::fjjphhp(Double_t x, Int_t j, Int_t jp, Int_t h, Int_t hp) const 
 { 

   if ((j == 0) and (jp == 0) and (h == 0) and (hp == 0)) {return fi(x,1);}
   else if ((j == 0) and (jp == 1) and (h == 0) and (hp == 0)) {return fi(x,2);}
   else if ((j == 0) and (jp == 1) and (h == 0) and ((hp == 1) or (hp == 2))) {return fi(x,3);}
   else if ((j == 0) and (jp == 2) and (h == 0) and (hp == 0)) {return fi(x,4);}
   else if ((j == 0) and (jp == 2) and (h == 0) and ((hp == 1) or (hp == 2))) {return fi(x,5);}
   else if ((j == 1) and (jp == 0) and (h == 0) and (hp == 0)) {return fi(x,2);}
   else if ((j == 1) and (jp == 1) and (h == 0) and (hp == 0)) {return fi(x,6);}
   else if ((j == 1) and (jp == 1) and (h == 0) and ((hp == 1) or (hp == 2))) {return fi(x,5);}
   else if ((j == 1) and (jp == 2) and (h == 0) and (hp == 0)) {return fi(x,7);}
   else if ((j == 1) and (jp == 2) and (h == 0) and ((hp == 1) or (hp == 2))) {return fi(x,8);}
   else if ((j == 1) and (jp == 0) and ((h == 1) or (h == 2)) and (hp == 0)) {return fi(x,3);}
   else if ((j == 1) and (jp == 1) and ((h == 1) or (h == 2)) and (hp == 0)) {return fi(x,5);}
   else if ((j == 1) and (jp == 1) and ((h == 1) or (h == 2)) and ((hp == 1) or (hp == 2))) {return fi(x,9);}
   else if ((j == 1) and (jp == 2) and ((h == 1) or (h == 2)) and (hp == 0)) {return fi(x,10);}
   else if ((j == 1) and (jp == 2) and ((h == 1) or (h == 2)) and ((hp == 1) or (hp == 2))) {return fi(x,11);}
   else if ((j == 2) and (jp == 0) and (h == 0) and (hp == 0)) {return fi(x,4);}
   else if ((j == 2) and (jp == 1) and (h == 0) and (hp == 0)) {return fi(x,7);}
   else if ((j == 2) and (jp == 1) and (h == 0) and ((hp == 1) or (hp == 2))) {return fi(x,10);}
   else if ((j == 2) and (jp == 2) and (h == 0) and (hp == 0)) {return fi(x,12);}
   else if ((j == 2) and (jp == 2) and (h == 0) and ((hp == 1) or (hp == 2))) {return fi(x,13);}
   else if ((j == 2) and (jp == 0) and ((h == 1) or (h == 2)) and (hp == 0)) {return fi(x,5);}
   else if ((j == 2) and (jp == 1) and ((h == 1) or (h == 2)) and (hp == 0)) {return fi(x,8);}
   else if ((j == 2) and (jp == 1) and ((h == 1) or (h == 2)) and ((hp == 1) or (hp == 2))) {return fi(x,11);}
   else if ((j == 2) and (jp == 2) and ((h == 1) or (h == 2)) and (hp == 0)) {return fi(x,13);}
   else if ((j == 2) and (jp == 2) and ((h == 1) or (h == 2)) and ((hp == 1) or (hp == 2))) {return fi(x,14);}
   else if ((j == 0) and (jp == 2) and (h == 0) and ((hp == 3) or (hp == 4))) {return fi(x,9);}
   else if ((j == 1) and (jp == 2) and (h == 0) and ((hp == 3) or (hp == 4))) {return fi(x,11);}
   else if ((j == 1) and (jp == 2) and ((h == 1) or (h == 2)) and ((hp == 3) or (hp == 4))) {return fi(x,15);}
   else if ((j == 2) and (jp == 2) and (h == 0) and ((hp == 3) or (hp == 4))) {return fi(x,16);}
   else if ((j == 2) and (jp == 2) and ((h == 1) or (h == 2)) and ((hp == 3) or (hp == 4))) {return fi(x,17);}
   else if ((j == 2) and (jp == 0) and ((h == 3) or (h == 4)) and (hp == 0)) {return fi(x,9);}
   else if ((j == 2) and (jp == 1) and ((h == 3) or (h == 4)) and (hp == 0)) {return fi(x,11);}
   else if ((j == 2) and (jp == 1) and ((h == 3) or (h == 4)) and ((hp == 1) or (hp == 2))) {return fi(x,15);}
   else if ((j == 2) and (jp == 2) and ((h == 3) or (h == 4)) and (hp == 0)) {return fi(x,16);}
   else if ((j == 2) and (jp == 2) and ((h == 3) or (h == 4)) and ((hp == 1) or (hp == 2))) {return fi(x,17);}
   else if ((j == 2) and (jp == 2) and ((h == 3) or (h == 4)) and ((hp == 3) or (hp == 4))) {return fi(x,18);}

   else {return 0.;}

 }

// ---------------------------------------------------
// Angular functions in phi.

Double_t MCGenComb::ghhp(Double_t x, Int_t h, Int_t hp) const 
 { 

   if ((h == 0) and (hp == 0)) {return gi(x,1);}
   else if ((h == 0) and (hp == 1)) {return gi(x,2);}
   else if ((h == 0) and (hp == 2)) {return gi(x,3);}
   else if ((h == 1) and (hp == 0)) {return gi(x,2);}
   else if ((h == 1) and (hp == 1)) {return gi(x,4);}
   else if ((h == 1) and (hp == 2)) {return gi(x,5);}
   else if ((h == 2) and (hp == 0)) {return gi(x,3);}
   else if ((h == 2) and (hp == 1)) {return gi(x,5);}
   else if ((h == 2) and (hp == 2)) {return gi(x,6);}
   else if ((h == 0) and (hp == 3)) {return gi(x,7);}
   else if ((h == 0) and (hp == 4)) {return gi(x,8);}
   else if ((h == 1) and (hp == 3)) {return gi(x,9);}
   else if ((h == 1) and (hp == 4)) {return gi(x,10);}
   else if ((h == 2) and (hp == 3)) {return gi(x,11);}
   else if ((h == 2) and (hp == 4)) {return gi(x,12);}
   else if ((h == 3) and (hp == 0)) {return gi(x,7);}
   else if ((h == 3) and (hp == 1)) {return gi(x,9);}
   else if ((h == 3) and (hp == 2)) {return gi(x,11);}
   else if ((h == 3) and (hp == 3)) {return gi(x,13);}
   else if ((h == 3) and (hp == 4)) {return gi(x,14);}
   else if ((h == 4) and (hp == 0)) {return gi(x,8);}
   else if ((h == 4) and (hp == 1)) {return gi(x,10);}
   else if ((h == 4) and (hp == 2)) {return gi(x,12);}
   else if ((h == 4) and (hp == 3)) {return gi(x,14);}
   else if ((h == 4) and (hp == 4)) {return gi(x,15);}

   throw std::invalid_argument( "Invalid argument 3" );

 }

// ---------------------------------------------------
// Components of the numerical normalization factors.

TComplex MCGenComb::Nj1j2h(Int_t j1, Int_t j2, Int_t h) const 
 {
  
   if ((j1 == 0) and (j2 == 0) and (h == 0)) {return TComplex(1./(2.*sqrt(2.*3.14159265358979323846264)),0.);}
   else if ((j1 == 0) and (j2 == 1) and (h == 0)) {return TComplex(-sqrt(3.)/(2.*sqrt(2.*3.14159265358979323846264)),0.);}
   else if ((j1 == 0) and (j2 == 2) and (h == 0)) {return TComplex(sqrt(5.)/(4.*sqrt(2.*3.14159265358979323846264)),0.);}
   else if ((j1 == 1) and (j2 == 0) and (h == 0)) {return TComplex(sqrt(3.)/(2.*sqrt(2.*3.14159265358979323846264)),0.);}
   else if ((j1 == 1) and (j2 == 1) and (h == 0)) {return TComplex(-3./(2.*sqrt(2.*3.14159265358979323846264)),0.);}
   else if ((j1 == 1) and (j2 == 1) and (h == 1)) {return TComplex(-3./(4.*sqrt(3.14159265358979323846264)),0.);}
   else if ((j1 == 1) and (j2 == 1) and (h == 2)) {return TComplex(0.,-3./(4.*sqrt(3.14159265358979323846264)));}
   else if ((j1 == 1) and (j2 == 2) and (h == 0)) {return TComplex(sqrt(15.)/(4.*sqrt(2.*3.14159265358979323846264)),0.);}
   else if ((j1 == 1) and (j2 == 2) and (h == 1)) {return TComplex(3.*sqrt(5.)/(4.*sqrt(3.14159265358979323846264)),0.);}
   else if ((j1 == 1) and (j2 == 2) and (h == 2)) {return TComplex(0.,3.*sqrt(5.)/(4.*sqrt(3.14159265358979323846264)));}
   else if ((j1 == 2) and (j2 == 0) and (h == 0)) {return TComplex(sqrt(5.)/(4.*sqrt(2.*3.14159265358979323846264)),0.);}
   else if ((j1 == 2) and (j2 == 1) and (h == 0)) {return TComplex(-sqrt(15.)/(4.*sqrt(2.*3.14159265358979323846264)),0.);}
   else if ((j1 == 2) and (j2 == 1) and (h == 1)) {return TComplex(-3.*sqrt(5.)/(4.*sqrt(3.14159265358979323846264)),0.);}
   else if ((j1 == 2) and (j2 == 1) and (h == 2)) {return TComplex(0.,-3.*sqrt(5.)/(4.*sqrt(3.14159265358979323846264)));}
   else if ((j1 == 2) and (j2 == 2) and (h == 0)) {return TComplex(5./(8.*sqrt(2.*3.14159265358979323846264)),0.);}
   else if ((j1 == 2) and (j2 == 2) and (h == 1)) {return TComplex(15./(4.*sqrt(3.14159265358979323846264)),0.);}
   else if ((j1 == 2) and (j2 == 2) and (h == 2)) {return TComplex(0.,15./(4.*sqrt(3.14159265358979323846264)));}
   else if ((j1 == 2) and (j2 == 2) and (h == 3)) {return TComplex(15./(16.*sqrt(3.14159265358979323846264)),0.);}
   else if ((j1 == 2) and (j2 == 2) and (h == 4)) {return TComplex(0.,15./(16.*sqrt(3.14159265358979323846264)));}

   else {return TComplex(0.,0.);}

 }

// ---------------------------------------------------
// Numerical normalization factors.

TComplex MCGenComb::Nj1j2hj1pj2php(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const 
 {
   
   TComplex N = Nj1j2h(j1,j2,h);
   TComplex Np = Nj1j2h(j1p,j2p,hp);
   return N*TComplex::Conjugate(Np);
  
 }

// ---------------------------------------------------
// Integrals of the elementary angular functions in cos(theta), parametric acceptance.

Double_t MCGenComb::Ifi(Int_t i) const
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

   throw std::invalid_argument( "Invalid argument 4" );

 }


// ---------------------------------------------------
// Integrals of the elementary angular functions in phi, parametric acceptance.

Double_t MCGenComb::Igi(Int_t i) const 
 { 

   if (i == 1) {return 2.*3.14159265358979323846264;}
   else if (i == 2) {return 0.;}
   else if (i == 3) {return 0.;}
   else if (i == 4) {return 3.14159265358979323846264;}
   else if (i == 5) {return 0;}
   else if (i == 6) {return 3.14159265358979323846264;}
   else if (i == 7) {return 0.;}
   else if (i == 8) {return 0.;}
   else if (i == 9) {return 0.;}
   else if (i == 10) {return 0.;}
   else if (i == 11) {return 0.;}
   else if (i == 12) {return 0.;}
   else if (i == 13) {return 3.14159265358979323846264;}
   else if (i == 14) {return 0.;}
   else if (i == 15) {return 3.14159265358979323846264;}

   throw std::invalid_argument( "Invalid argument 5" );

 }

// ---------------------------------------------------
// Integrals of the angular functions in cos(theta), parametric acceptance.

Double_t MCGenComb::Ifjjphhp(Int_t j, Int_t jp, Int_t h, Int_t hp) const 
 { 

   if ((j == 0) and (jp == 0) and (h == 0) and (hp == 0)) {return Ifi(1);}
   else if ((j == 0) and (jp == 1) and (h == 0) and (hp == 0)) {return Ifi(2);}
   else if ((j == 0) and (jp == 1) and (h == 0) and ((hp == 1) or (hp == 2))) {return Ifi(3);}
   else if ((j == 0) and (jp == 2) and (h == 0) and (hp == 0)) {return Ifi(4);}
   else if ((j == 0) and (jp == 2) and (h == 0) and ((hp == 1) or (hp == 2))) {return Ifi(5);}
   else if ((j == 1) and (jp == 0) and (h == 0) and (hp == 0)) {return Ifi(2);}
   else if ((j == 1) and (jp == 1) and (h == 0) and (hp == 0)) {return Ifi(6);}
   else if ((j == 1) and (jp == 1) and (h == 0) and ((hp == 1) or (hp == 2))) {return Ifi(5);}
   else if ((j == 1) and (jp == 2) and (h == 0) and (hp == 0)) {return Ifi(7);}
   else if ((j == 1) and (jp == 2) and (h == 0) and ((hp == 1) or (hp == 2))) {return Ifi(8);}
   else if ((j == 1) and (jp == 0) and ((h == 1) or (h == 2)) and (hp == 0)) {return Ifi(3);}
   else if ((j == 1) and (jp == 1) and ((h == 1) or (h == 2)) and (hp == 0)) {return Ifi(5);}
   else if ((j == 1) and (jp == 1) and ((h == 1) or (h == 2)) and ((hp == 1) or (hp == 2))) {return Ifi(9);}
   else if ((j == 1) and (jp == 2) and ((h == 1) or (h == 2)) and (hp == 0)) {return Ifi(10);}
   else if ((j == 1) and (jp == 2) and ((h == 1) or (h == 2)) and ((hp == 1) or (hp == 2))) {return Ifi(11);}
   else if ((j == 2) and (jp == 0) and (h == 0) and (hp == 0)) {return Ifi(4);}
   else if ((j == 2) and (jp == 1) and (h == 0) and (hp == 0)) {return Ifi(7);}
   else if ((j == 2) and (jp == 1) and (h == 0) and ((hp == 1) or (hp == 2))) {return Ifi(10);}
   else if ((j == 2) and (jp == 2) and (h == 0) and (hp == 0)) {return Ifi(12);}
   else if ((j == 2) and (jp == 2) and (h == 0) and ((hp == 1) or (hp == 2))) {return Ifi(13);}
   else if ((j == 2) and (jp == 0) and ((h == 1) or (h == 2)) and (hp == 0)) {return Ifi(5);}
   else if ((j == 2) and (jp == 1) and ((h == 1) or (h == 2)) and (hp == 0)) {return Ifi(8);}
   else if ((j == 2) and (jp == 1) and ((h == 1) or (h == 2)) and ((hp == 1) or (hp == 2))) {return Ifi(11);}
   else if ((j == 2) and (jp == 2) and ((h == 1) or (h == 2)) and (hp == 0)) {return Ifi(13);}
   else if ((j == 2) and (jp == 2) and ((h == 1) or (h == 2)) and ((hp == 1) or (hp == 2))) {return Ifi(14);}
   else if ((j == 0) and (jp == 2) and (h == 0) and ((hp == 3) or (hp == 4))) {return Ifi(9);}
   else if ((j == 1) and (jp == 2) and (h == 0) and ((hp == 3) or (hp == 4))) {return Ifi(11);}
   else if ((j == 1) and (jp == 2) and ((h == 1) or (h == 2)) and ((hp == 3) or (hp == 4))) {return Ifi(15);}
   else if ((j == 2) and (jp == 2) and (h == 0) and ((hp == 3) or (hp == 4))) {return Ifi(16);}
   else if ((j == 2) and (jp == 2) and ((h == 1) or (h == 2)) and ((hp == 3) or (hp == 4))) {return Ifi(17);}
   else if ((j == 2) and (jp == 0) and ((h == 3) or (h == 4)) and (hp == 0)) {return Ifi(9);}
   else if ((j == 2) and (jp == 1) and ((h == 3) or (h == 4)) and (hp == 0)) {return Ifi(11);}
   else if ((j == 2) and (jp == 1) and ((h == 3) or (h == 4)) and ((hp == 1) or (hp == 2))) {return Ifi(15);}
   else if ((j == 2) and (jp == 2) and ((h == 3) or (h == 4)) and (hp == 0)) {return Ifi(16);}
   else if ((j == 2) and (jp == 2) and ((h == 3) or (h == 4)) and ((hp == 1) or (hp == 2))) {return Ifi(17);}
   else if ((j == 2) and (jp == 2) and ((h == 3) or (h == 4)) and ((hp == 3) or (hp == 4))) {return Ifi(18);}

   else {return 0.;}

 }

// ---------------------------------------------------
// Integrals of the angular functions in phi, parametric acceptance.

Double_t MCGenComb::Ighhp(Int_t h, Int_t hp) const 
 { 

   if ((h == 0) and (hp == 0)) {return Igi(1);}
   else if ((h == 0) and (hp == 1)) {return Igi(2);}
   else if ((h == 0) and (hp == 2)) {return Igi(3);}
   else if ((h == 1) and (hp == 1)) {return Igi(4);}
   else if ((h == 1) and (hp == 2)) {return Igi(5);}
   else if ((h == 2) and (hp == 0)) {return Igi(3);}
   else if ((h == 2) and (hp == 1)) {return Igi(5);}
   else if ((h == 2) and (hp == 2)) {return Igi(6);}
   else if ((h == 0) and (hp == 3)) {return Igi(7);}
   else if ((h == 0) and (hp == 4)) {return Igi(8);}
   else if ((h == 1) and (hp == 3)) {return Igi(9);}
   else if ((h == 1) and (hp == 4)) {return Igi(10);}
   else if ((h == 2) and (hp == 3)) {return Igi(11);}
   else if ((h == 2) and (hp == 4)) {return Igi(12);}
   else if ((h == 3) and (hp == 0)) {return Igi(7);}
   else if ((h == 3) and (hp == 1)) {return Igi(9);}
   else if ((h == 3) and (hp == 2)) {return Igi(11);}
   else if ((h == 3) and (hp == 3)) {return Igi(13);}
   else if ((h == 3) and (hp == 4)) {return Igi(14);}
   else if ((h == 4) and (hp == 0)) {return Igi(8);}
   else if ((h == 4) and (hp == 1)) {return Igi(10);}
   else if ((h == 4) and (hp == 2)) {return Igi(12);}
   else if ((h == 4) and (hp == 3)) {return Igi(14);}
   else if ((h == 4) and (hp == 4)) {return Igi(15);}

   throw std::invalid_argument( "Invalid argument 6" );

 }

// ---------------------------------------------------
// Momentum of one of the two daughters in the rest frame of the mother.

Double_t MCGenComb::get_q(Double_t M, Double_t ma, Double_t mb) const 
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

Double_t MCGenComb::Blatt_Weisskopf2(Double_t q, Double_t q0, Int_t L) const 
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

TComplex MCGenComb::Resonance(Double_t m, Double_t m_sister, Double_t m0, Double_t g0, Int_t J) const
 {

   Double_t q = get_q(m,139.57018,493.67);
   Double_t q0 = get_q(m0,139.57018,493.67);
   if (q==0) return 0;

   Double_t gamma = g0*pow(q/q0,2*J+1)*(m0/m)*Blatt_Weisskopf2(q,q0,J);

   TComplex num(sqrt(m*gamma*m0*g0),0.);
   TComplex denom(m0*m0-m*m,-m0*gamma);
   TComplex BW = num/denom;

   if (m>=(139.57018+493.67) and m_sister>=(139.57018+493.67) and m<=(m0+15.*g0) and m_sister<=(m0+15.*g0)) {return BW;}
   else {return 0.;}

 }

// ---------------------------------------------------
// Lass parametrization for the S wave.

TComplex MCGenComb::Lass(Double_t m, Double_t m_sister, Double_t m0, Double_t g0) const 
 { 

   TComplex i(0,1);

   Double_t q = get_q(m,139.57018,493.67);
   Double_t q0 = get_q(m0,139.57018,493.67);
   if (q==0) return 0;
   Double_t p = get_q(5366.77,m_sister,m);
   Double_t p0 = get_q(5366.77,m_sister,m0);
   if (p==0) return 0;

   Double_t cotg_deltaB = 1./(0.00195*q)+0.5*0.00176*q;
   Double_t deltaB = atan(1./cotg_deltaB);
   TComplex expo(1.,2.*deltaB,1);

   Double_t gamma = g0*q/q0*m0/m;
   Double_t cotg_deltaR = (m0*m0-m*m)/(m0*gamma);

   TComplex T = sqrt(Blatt_Weisskopf2(p,p0,1))*p*m/q*(1./(cotg_deltaB-i)+expo/(cotg_deltaR-i));

   return T;

 } 

// ---------------------------------------------------
// Invariant mass amplitude for each wave.

TComplex MCGenComb::Mji(Double_t m, Double_t m_sister, Int_t ji) const 
 {

   TComplex T;

   if (ji == 0)
	{
	T = Lass(m,m_sister,1425.,270.);
	}

   else if (ji == 1)
	{
	T = Resonance(m,m_sister,896,50.3,1);
	}

   else if (ji == 2)
	{
	T = Resonance(m,m_sister,1432.4,109.,2);
	}
   
   return T;

 }

// ---------------------------------------------------
// Invariant mass dependent factor for each amplitude.
 
TComplex MCGenComb::Mj1j2(Double_t ma, Double_t mb, Int_t j1, Int_t j2) const 
 { 

 Im00 = 1.;
 Im01 = 1.;
 Im10 = 1.;
 Im02 = 1.;
 Im20 = 1.;
 Im11 = 1.;
 Im12 = 1.;
 Im21 = 1.;
 Im22 = 1.;

 if ((j1 == 0) and (j2 == 0)) {return Mji(ma,mb,0)*Mji(mb,ma,0)/sqrt(Im00);}
 else if ((j1 == 0) and (j2 == 1)) {return Mji(ma,mb,0)*Mji(mb,ma,1)/sqrt(Im01);}
 else if ((j1 == 1) and (j2 == 0)) {return Mji(ma,mb,1)*Mji(mb,ma,0)/sqrt(Im10);}
 else if ((j1 == 0) and (j2 == 2)) {return Mji(ma,mb,0)*Mji(mb,ma,2)/sqrt(Im02);}
 else if ((j1 == 2) and (j2 == 0)) {return Mji(ma,mb,2)*Mji(mb,ma,0)/sqrt(Im20);}
 else if ((j1 == 1) and (j2 == 1)) {return Mji(ma,mb,1)*Mji(mb,ma,1)/sqrt(Im11);}
 else if ((j1 == 1) and (j2 == 2)) {return Mji(ma,mb,1)*Mji(mb,ma,2)/sqrt(Im12);}
 else if ((j1 == 2) and (j2 == 1)) {return Mji(ma,mb,2)*Mji(mb,ma,1)/sqrt(Im21);}
 else if ((j1 == 2) and (j2 == 2)) {return Mji(ma,mb,2)*Mji(mb,ma,2)/sqrt(Im22);}

 throw std::invalid_argument( "Invalid argument 7" );

 }

// ---------------------------------------------------
// Phase space factor.

Double_t MCGenComb::phasespace(Double_t ma, Double_t mb) const 
 { 
 
   Double_t Q1 = get_q(ma,493.67,139.57018)/get_q(896,493.67,139.57018);
   Double_t Q2 = get_q(mb,493.67,139.57018)/get_q(896,493.67,139.57018);
   Double_t QB = get_q(5366.77,ma,mb)/get_q(5366.77,896,896);
   Double_t phsp = Q1*Q2*QB;

   if (ma<=2000. and mb<=2000.) {return phsp;}

   else {return 0.;}

 } 

// ---------------------------------------------------
// Invariant mass dependent functions.

TComplex MCGenComb::hj1j2j1pj2p(Double_t ma, Double_t mb, Int_t j1, Int_t j2, Int_t j1p, Int_t j2p) const 
 { 

   return Mj1j2(ma,mb,j1,j2)*TComplex::Conjugate(Mj1j2(ma,mb,j1p,j2p))*(get_q(5366.77,ma,896)/get_q(5366.77,896,896))*(get_q(5366.77,896,mb)/get_q(5366.77,896,896));

 }

// ---------------------------------------------------
// Integrals of the invariant mass dependent functions, parametric acceptance.

TComplex MCGenComb::Ihj1j2j1pj2p(Int_t j1, Int_t j2, Int_t j1p, Int_t j2p) const 
 { 

   if (wide_window) {

      if ((j1 == 0) and (j2 == 0) and (j1p == 0) and (j2p == 0)) {return TComplex(Ih22Re_wide,0.);}
      if ((j1 == 0) and (j2 == 0) and (j1p == 0) and (j2p == 1)) {return TComplex(Ih1Re_wide,Ih1Im_wide);}
      if ((j1 == 0) and (j2 == 0) and (j1p == 0) and (j2p == 2)) {return TComplex(Ih2Re_wide,Ih2Im_wide);}
      if ((j1 == 0) and (j2 == 0) and (j1p == 1) and (j2p == 0)) {return TComplex(Ih1Re_wide,Ih1Im_wide);}
      if ((j1 == 0) and (j2 == 0) and (j1p == 1) and (j2p == 1)) {return TComplex(Ih3Re_wide,Ih3Im_wide);}
      if ((j1 == 0) and (j2 == 0) and (j1p == 1) and (j2p == 2)) {return TComplex(Ih4Re_wide,Ih4Im_wide);}
      if ((j1 == 0) and (j2 == 0) and (j1p == 2) and (j2p == 0)) {return TComplex(Ih2Re_wide,Ih2Im_wide);}
      if ((j1 == 0) and (j2 == 0) and (j1p == 2) and (j2p == 1)) {return TComplex(Ih4Re_wide,Ih4Im_wide);}
      if ((j1 == 0) and (j2 == 0) and (j1p == 2) and (j2p == 2)) {return TComplex(Ih5Re_wide,Ih5Im_wide);}
      if ((j1 == 0) and (j2 == 1) and (j1p == 0) and (j2p == 0)) {return TComplex(Ih1Re_wide,-Ih1Im_wide);}

      if ((j1 == 0) and (j2 == 1) and (j1p == 0) and (j2p == 1)) {return TComplex(Ih23Re_wide,0.);}
      if ((j1 == 0) and (j2 == 1) and (j1p == 0) and (j2p == 2)) {return TComplex(Ih6Re_wide,Ih6Im_wide);}
      if ((j1 == 0) and (j2 == 1) and (j1p == 1) and (j2p == 0)) {return TComplex(Ih7Re_wide,Ih7Im_wide);}
      if ((j1 == 0) and (j2 == 1) and (j1p == 1) and (j2p == 1)) {return TComplex(Ih8Re_wide,Ih8Im_wide);}
      if ((j1 == 0) and (j2 == 1) and (j1p == 1) and (j2p == 2)) {return TComplex(Ih9Re_wide,Ih9Im_wide);}
      if ((j1 == 0) and (j2 == 1) and (j1p == 2) and (j2p == 0)) {return TComplex(Ih10Re_wide,Ih10Im_wide);}
      if ((j1 == 0) and (j2 == 1) and (j1p == 2) and (j2p == 1)) {return TComplex(Ih11Re_wide,Ih11Im_wide);}
      if ((j1 == 0) and (j2 == 1) and (j1p == 2) and (j2p == 2)) {return TComplex(Ih12Re_wide,Ih12Im_wide);}
      if ((j1 == 0) and (j2 == 2) and (j1p == 0) and (j2p == 0)) {return TComplex(Ih2Re_wide,-Ih2Im_wide);}
      if ((j1 == 0) and (j2 == 2) and (j1p == 0) and (j2p == 1)) {return TComplex(Ih6Re_wide,-Ih6Im_wide);}

      if ((j1 == 0) and (j2 == 2) and (j1p == 0) and (j2p == 2)) {return TComplex(Ih25Re_wide,0.);}
      if ((j1 == 0) and (j2 == 2) and (j1p == 1) and (j2p == 0)) {return TComplex(Ih10Re_wide,-Ih10Im_wide);}
      if ((j1 == 0) and (j2 == 2) and (j1p == 1) and (j2p == 1)) {return TComplex(Ih13Re_wide,Ih13Im_wide);}
      if ((j1 == 0) and (j2 == 2) and (j1p == 1) and (j2p == 2)) {return TComplex(Ih14Re_wide,Ih14Im_wide);}
      if ((j1 == 0) and (j2 == 2) and (j1p == 2) and (j2p == 0)) {return TComplex(Ih15Re_wide,Ih15Im_wide);}
      if ((j1 == 0) and (j2 == 2) and (j1p == 2) and (j2p == 1)) {return TComplex(Ih16Re_wide,Ih16Im_wide);}
      if ((j1 == 0) and (j2 == 2) and (j1p == 2) and (j2p == 2)) {return TComplex(Ih17Re_wide,Ih17Im_wide);}
      if ((j1 == 1) and (j2 == 0) and (j1p == 0) and (j2p == 0)) {return TComplex(Ih1Re_wide,-Ih1Im_wide);}
      if ((j1 == 1) and (j2 == 0) and (j1p == 0) and (j2p == 1)) {return TComplex(Ih7Re_wide,Ih7Im_wide);}
      if ((j1 == 1) and (j2 == 0) and (j1p == 0) and (j2p == 2)) {return TComplex(Ih10Re_wide,Ih10Im_wide);}

      if ((j1 == 1) and (j2 == 0) and (j1p == 1) and (j2p == 0)) {return TComplex(Ih24Re_wide,0.);}
      if ((j1 == 1) and (j2 == 0) and (j1p == 1) and (j2p == 1)) {return TComplex(Ih8Re_wide,Ih8Im_wide);}
      if ((j1 == 1) and (j2 == 0) and (j1p == 1) and (j2p == 2)) {return TComplex(Ih11Re_wide,Ih11Im_wide);}
      if ((j1 == 1) and (j2 == 0) and (j1p == 2) and (j2p == 0)) {return TComplex(Ih6Re_wide,Ih6Im_wide);}
      if ((j1 == 1) and (j2 == 0) and (j1p == 2) and (j2p == 1)) {return TComplex(Ih9Re_wide,Ih9Im_wide);}
      if ((j1 == 1) and (j2 == 0) and (j1p == 2) and (j2p == 2)) {return TComplex(Ih12Re_wide,Ih12Im_wide);}
      if ((j1 == 1) and (j2 == 1) and (j1p == 0) and (j2p == 0)) {return TComplex(Ih3Re_wide,-Ih3Im_wide);}
      if ((j1 == 1) and (j2 == 1) and (j1p == 0) and (j2p == 1)) {return TComplex(Ih8Re_wide,-Ih8Im_wide);}
      if ((j1 == 1) and (j2 == 1) and (j1p == 0) and (j2p == 2)) {return TComplex(Ih13Re_wide,-Ih13Im_wide);}
      if ((j1 == 1) and (j2 == 1) and (j1p == 1) and (j2p == 0)) {return TComplex(Ih8Re_wide,-Ih8Im_wide);}

      if ((j1 == 1) and (j2 == 1) and (j1p == 1) and (j2p == 1)) {return TComplex(5805.992273500882,0.);}
      if ((j1 == 1) and (j2 == 1) and (j1p == 1) and (j2p == 2)) {return TComplex(Ih18Re_wide,Ih18Im_wide);}
      if ((j1 == 1) and (j2 == 1) and (j1p == 2) and (j2p == 0)) {return TComplex(Ih13Re_wide,-Ih13Im_wide);}
      if ((j1 == 1) and (j2 == 1) and (j1p == 2) and (j2p == 1)) {return TComplex(Ih18Re_wide,Ih18Im_wide);}
      if ((j1 == 1) and (j2 == 1) and (j1p == 2) and (j2p == 2)) {return TComplex(Ih19Re_wide,Ih19Im_wide);}
      if ((j1 == 1) and (j2 == 2) and (j1p == 0) and (j2p == 0)) {return TComplex(Ih4Re_wide,-Ih4Im_wide);}
      if ((j1 == 1) and (j2 == 2) and (j1p == 0) and (j2p == 1)) {return TComplex(Ih9Re_wide,-Ih9Im_wide);}
      if ((j1 == 1) and (j2 == 2) and (j1p == 0) and (j2p == 2)) {return TComplex(Ih14Re_wide,-Ih14Im_wide);}
      if ((j1 == 1) and (j2 == 2) and (j1p == 1) and (j2p == 0)) {return TComplex(Ih11Re_wide,-Ih11Im_wide);}
      if ((j1 == 1) and (j2 == 2) and (j1p == 1) and (j2p == 1)) {return TComplex(Ih18Re_wide,-Ih18Im_wide);}

      if ((j1 == 1) and (j2 == 2) and (j1p == 1) and (j2p == 2)) {return TComplex(Ih28Re_wide,0.);}
      if ((j1 == 1) and (j2 == 2) and (j1p == 2) and (j2p == 0)) {return TComplex(Ih16Re_wide,-Ih16Im_wide);}
      if ((j1 == 1) and (j2 == 2) and (j1p == 2) and (j2p == 1)) {return TComplex(Ih20Re_wide,Ih20Im_wide);}
      if ((j1 == 1) and (j2 == 2) and (j1p == 2) and (j2p == 2)) {return TComplex(Ih21Re_wide,Ih21Im_wide);}
      if ((j1 == 2) and (j2 == 0) and (j1p == 0) and (j2p == 0)) {return TComplex(Ih2Re_wide,-Ih2Im_wide);}
      if ((j1 == 2) and (j2 == 0) and (j1p == 0) and (j2p == 1)) {return TComplex(Ih10Re_wide,-Ih10Im_wide);}
      if ((j1 == 2) and (j2 == 0) and (j1p == 0) and (j2p == 2)) {return TComplex(Ih15Re_wide,Ih15Im_wide);}
      if ((j1 == 2) and (j2 == 0) and (j1p == 1) and (j2p == 0)) {return TComplex(Ih6Re_wide,-Ih6Im_wide);}
      if ((j1 == 2) and (j2 == 0) and (j1p == 1) and (j2p == 1)) {return TComplex(Ih13Re_wide,Ih13Im_wide);}
      if ((j1 == 2) and (j2 == 0) and (j1p == 1) and (j2p == 2)) {return TComplex(Ih16Re_wide,Ih16Im_wide);}

      if ((j1 == 2) and (j2 == 0) and (j1p == 2) and (j2p == 0)) {return TComplex(Ih26Re_wide,0.);}
      if ((j1 == 2) and (j2 == 0) and (j1p == 2) and (j2p == 1)) {return TComplex(Ih14Re_wide,Ih14Im_wide);}
      if ((j1 == 2) and (j2 == 0) and (j1p == 2) and (j2p == 2)) {return TComplex(Ih17Re_wide,Ih17Im_wide);}
      if ((j1 == 2) and (j2 == 1) and (j1p == 0) and (j2p == 0)) {return TComplex(Ih4Re_wide,-Ih4Im_wide);}
      if ((j1 == 2) and (j2 == 1) and (j1p == 0) and (j2p == 1)) {return TComplex(Ih11Re_wide,-Ih11Im_wide);}
      if ((j1 == 2) and (j2 == 1) and (j1p == 0) and (j2p == 2)) {return TComplex(Ih16Re_wide,-Ih16Im_wide);}
      if ((j1 == 2) and (j2 == 1) and (j1p == 1) and (j2p == 0)) {return TComplex(Ih9Re_wide,-Ih9Im_wide);}
      if ((j1 == 2) and (j2 == 1) and (j1p == 1) and (j2p == 1)) {return TComplex(Ih18Re_wide,-Ih18Im_wide);}
      if ((j1 == 2) and (j2 == 1) and (j1p == 1) and (j2p == 2)) {return TComplex(Ih20Re_wide,Ih20Im_wide);}
      if ((j1 == 2) and (j2 == 1) and (j1p == 2) and (j2p == 0)) {return TComplex(Ih14Re_wide,-Ih14Im_wide);}

      if ((j1 == 2) and (j2 == 1) and (j1p == 2) and (j2p == 1)) {return TComplex(Ih29Re_wide,0.);}
      if ((j1 == 2) and (j2 == 1) and (j1p == 2) and (j2p == 2)) {return TComplex(Ih21Re_wide,Ih21Im_wide);}
      if ((j1 == 2) and (j2 == 2) and (j1p == 0) and (j2p == 0)) {return TComplex(Ih5Re_wide,-Ih5Im_wide);}
      if ((j1 == 2) and (j2 == 2) and (j1p == 0) and (j2p == 1)) {return TComplex(Ih12Re_wide,-Ih12Im_wide);}
      if ((j1 == 2) and (j2 == 2) and (j1p == 0) and (j2p == 2)) {return TComplex(Ih17Re_wide,-Ih17Im_wide);}
      if ((j1 == 2) and (j2 == 2) and (j1p == 1) and (j2p == 0)) {return TComplex(Ih12Re_wide,-Ih12Im_wide);}
      if ((j1 == 2) and (j2 == 2) and (j1p == 1) and (j2p == 1)) {return TComplex(Ih19Re_wide,-Ih19Im_wide);}
      if ((j1 == 2) and (j2 == 2) and (j1p == 1) and (j2p == 2)) {return TComplex(Ih21Re_wide,-Ih21Im_wide);}
      if ((j1 == 2) and (j2 == 2) and (j1p == 2) and (j2p == 0)) {return TComplex(Ih17Re_wide,-Ih17Im_wide);}
      if ((j1 == 2) and (j2 == 2) and (j1p == 2) and (j2p == 1)) {return TComplex(Ih21Re_wide,-Ih21Im_wide);}

      if ((j1 == 2) and (j2 == 2) and (j1p == 2) and (j2p == 2)) {return TComplex(Ih30Re_wide,0.);}

   }

   else {

      if ((j1 == 0) and (j2 == 0) and (j1p == 0) and (j2p == 0)) {return TComplex(Ih22Re_narrow,0.);}
      if ((j1 == 0) and (j2 == 0) and (j1p == 0) and (j2p == 1)) {return TComplex(Ih1Re_narrow,Ih1Im_narrow);}
      if ((j1 == 0) and (j2 == 0) and (j1p == 0) and (j2p == 2)) {return TComplex(Ih2Re_narrow,Ih2Im_narrow);}
      if ((j1 == 0) and (j2 == 0) and (j1p == 1) and (j2p == 0)) {return TComplex(Ih1Re_narrow,Ih1Im_narrow);}
      if ((j1 == 0) and (j2 == 0) and (j1p == 1) and (j2p == 1)) {return TComplex(Ih3Re_narrow,Ih3Im_narrow);}
      if ((j1 == 0) and (j2 == 0) and (j1p == 1) and (j2p == 2)) {return TComplex(Ih4Re_narrow,Ih4Im_narrow);}
      if ((j1 == 0) and (j2 == 0) and (j1p == 2) and (j2p == 0)) {return TComplex(Ih2Re_narrow,Ih2Im_narrow);}
      if ((j1 == 0) and (j2 == 0) and (j1p == 2) and (j2p == 1)) {return TComplex(Ih4Re_narrow,Ih4Im_narrow);}
      if ((j1 == 0) and (j2 == 0) and (j1p == 2) and (j2p == 2)) {return TComplex(Ih5Re_narrow,Ih5Im_narrow);}
      if ((j1 == 0) and (j2 == 1) and (j1p == 0) and (j2p == 0)) {return TComplex(Ih1Re_narrow,-Ih1Im_narrow);}

      if ((j1 == 0) and (j2 == 1) and (j1p == 0) and (j2p == 1)) {return TComplex(Ih23Re_narrow,0.);}
      if ((j1 == 0) and (j2 == 1) and (j1p == 0) and (j2p == 2)) {return TComplex(Ih6Re_narrow,Ih6Im_narrow);}
      if ((j1 == 0) and (j2 == 1) and (j1p == 1) and (j2p == 0)) {return TComplex(Ih7Re_narrow,Ih7Im_narrow);}
      if ((j1 == 0) and (j2 == 1) and (j1p == 1) and (j2p == 1)) {return TComplex(Ih8Re_narrow,Ih8Im_narrow);}
      if ((j1 == 0) and (j2 == 1) and (j1p == 1) and (j2p == 2)) {return TComplex(Ih9Re_narrow,Ih9Im_narrow);}
      if ((j1 == 0) and (j2 == 1) and (j1p == 2) and (j2p == 0)) {return TComplex(Ih10Re_narrow,Ih10Im_narrow);}
      if ((j1 == 0) and (j2 == 1) and (j1p == 2) and (j2p == 1)) {return TComplex(Ih11Re_narrow,Ih11Im_narrow);}
      if ((j1 == 0) and (j2 == 1) and (j1p == 2) and (j2p == 2)) {return TComplex(Ih12Re_narrow,Ih12Im_narrow);}
      if ((j1 == 0) and (j2 == 2) and (j1p == 0) and (j2p == 0)) {return TComplex(Ih2Re_narrow,-Ih2Im_narrow);}
      if ((j1 == 0) and (j2 == 2) and (j1p == 0) and (j2p == 1)) {return TComplex(Ih6Re_narrow,-Ih6Im_narrow);}

      if ((j1 == 0) and (j2 == 2) and (j1p == 0) and (j2p == 2)) {return TComplex(Ih25Re_narrow,0.);}
      if ((j1 == 0) and (j2 == 2) and (j1p == 1) and (j2p == 0)) {return TComplex(Ih10Re_narrow,-Ih10Im_narrow);}
      if ((j1 == 0) and (j2 == 2) and (j1p == 1) and (j2p == 1)) {return TComplex(Ih13Re_narrow,Ih13Im_narrow);}
      if ((j1 == 0) and (j2 == 2) and (j1p == 1) and (j2p == 2)) {return TComplex(Ih14Re_narrow,Ih14Im_narrow);}
      if ((j1 == 0) and (j2 == 2) and (j1p == 2) and (j2p == 0)) {return TComplex(Ih15Re_narrow,Ih15Im_narrow);}
      if ((j1 == 0) and (j2 == 2) and (j1p == 2) and (j2p == 1)) {return TComplex(Ih16Re_narrow,Ih16Im_narrow);}
      if ((j1 == 0) and (j2 == 2) and (j1p == 2) and (j2p == 2)) {return TComplex(Ih17Re_narrow,Ih17Im_narrow);}
      if ((j1 == 1) and (j2 == 0) and (j1p == 0) and (j2p == 0)) {return TComplex(Ih1Re_narrow,-Ih1Im_narrow);}
      if ((j1 == 1) and (j2 == 0) and (j1p == 0) and (j2p == 1)) {return TComplex(Ih7Re_narrow,Ih7Im_narrow);}
      if ((j1 == 1) and (j2 == 0) and (j1p == 0) and (j2p == 2)) {return TComplex(Ih10Re_narrow,Ih10Im_narrow);}

      if ((j1 == 1) and (j2 == 0) and (j1p == 1) and (j2p == 0)) {return TComplex(Ih24Re_narrow,0.);}
      if ((j1 == 1) and (j2 == 0) and (j1p == 1) and (j2p == 1)) {return TComplex(Ih8Re_narrow,Ih8Im_narrow);}
      if ((j1 == 1) and (j2 == 0) and (j1p == 1) and (j2p == 2)) {return TComplex(Ih11Re_narrow,Ih11Im_narrow);}
      if ((j1 == 1) and (j2 == 0) and (j1p == 2) and (j2p == 0)) {return TComplex(Ih6Re_narrow,Ih6Im_narrow);}
      if ((j1 == 1) and (j2 == 0) and (j1p == 2) and (j2p == 1)) {return TComplex(Ih9Re_narrow,Ih9Im_narrow);}
      if ((j1 == 1) and (j2 == 0) and (j1p == 2) and (j2p == 2)) {return TComplex(Ih12Re_narrow,Ih12Im_narrow);}
      if ((j1 == 1) and (j2 == 1) and (j1p == 0) and (j2p == 0)) {return TComplex(Ih3Re_narrow,-Ih3Im_narrow);}
      if ((j1 == 1) and (j2 == 1) and (j1p == 0) and (j2p == 1)) {return TComplex(Ih8Re_narrow,-Ih8Im_narrow);}
      if ((j1 == 1) and (j2 == 1) and (j1p == 0) and (j2p == 2)) {return TComplex(Ih13Re_narrow,-Ih13Im_narrow);}
      if ((j1 == 1) and (j2 == 1) and (j1p == 1) and (j2p == 0)) {return TComplex(Ih8Re_narrow,-Ih8Im_narrow);}

      if ((j1 == 1) and (j2 == 1) and (j1p == 1) and (j2p == 1)) {return TComplex(5805.992273500882,0.);}
      if ((j1 == 1) and (j2 == 1) and (j1p == 1) and (j2p == 2)) {return TComplex(Ih18Re_narrow,Ih18Im_narrow);}
      if ((j1 == 1) and (j2 == 1) and (j1p == 2) and (j2p == 0)) {return TComplex(Ih13Re_narrow,-Ih13Im_narrow);}
      if ((j1 == 1) and (j2 == 1) and (j1p == 2) and (j2p == 1)) {return TComplex(Ih18Re_narrow,Ih18Im_narrow);}
      if ((j1 == 1) and (j2 == 1) and (j1p == 2) and (j2p == 2)) {return TComplex(Ih19Re_narrow,Ih19Im_narrow);}
      if ((j1 == 1) and (j2 == 2) and (j1p == 0) and (j2p == 0)) {return TComplex(Ih4Re_narrow,-Ih4Im_narrow);}
      if ((j1 == 1) and (j2 == 2) and (j1p == 0) and (j2p == 1)) {return TComplex(Ih9Re_narrow,-Ih9Im_narrow);}
      if ((j1 == 1) and (j2 == 2) and (j1p == 0) and (j2p == 2)) {return TComplex(Ih14Re_narrow,-Ih14Im_narrow);}
      if ((j1 == 1) and (j2 == 2) and (j1p == 1) and (j2p == 0)) {return TComplex(Ih11Re_narrow,-Ih11Im_narrow);}
      if ((j1 == 1) and (j2 == 2) and (j1p == 1) and (j2p == 1)) {return TComplex(Ih18Re_narrow,-Ih18Im_narrow);}

      if ((j1 == 1) and (j2 == 2) and (j1p == 1) and (j2p == 2)) {return TComplex(Ih28Re_narrow,0.);}
      if ((j1 == 1) and (j2 == 2) and (j1p == 2) and (j2p == 0)) {return TComplex(Ih16Re_narrow,-Ih16Im_narrow);}
      if ((j1 == 1) and (j2 == 2) and (j1p == 2) and (j2p == 1)) {return TComplex(Ih20Re_narrow,Ih20Im_narrow);}
      if ((j1 == 1) and (j2 == 2) and (j1p == 2) and (j2p == 2)) {return TComplex(Ih21Re_narrow,Ih21Im_narrow);}
      if ((j1 == 2) and (j2 == 0) and (j1p == 0) and (j2p == 0)) {return TComplex(Ih2Re_narrow,-Ih2Im_narrow);}
      if ((j1 == 2) and (j2 == 0) and (j1p == 0) and (j2p == 1)) {return TComplex(Ih10Re_narrow,-Ih10Im_narrow);}
      if ((j1 == 2) and (j2 == 0) and (j1p == 0) and (j2p == 2)) {return TComplex(Ih15Re_narrow,Ih15Im_narrow);}
      if ((j1 == 2) and (j2 == 0) and (j1p == 1) and (j2p == 0)) {return TComplex(Ih6Re_narrow,-Ih6Im_narrow);}
      if ((j1 == 2) and (j2 == 0) and (j1p == 1) and (j2p == 1)) {return TComplex(Ih13Re_narrow,Ih13Im_narrow);}
      if ((j1 == 2) and (j2 == 0) and (j1p == 1) and (j2p == 2)) {return TComplex(Ih16Re_narrow,Ih16Im_narrow);}

      if ((j1 == 2) and (j2 == 0) and (j1p == 2) and (j2p == 0)) {return TComplex(Ih26Re_narrow,0.);}
      if ((j1 == 2) and (j2 == 0) and (j1p == 2) and (j2p == 1)) {return TComplex(Ih14Re_narrow,Ih14Im_narrow);}
      if ((j1 == 2) and (j2 == 0) and (j1p == 2) and (j2p == 2)) {return TComplex(Ih17Re_narrow,Ih17Im_narrow);}
      if ((j1 == 2) and (j2 == 1) and (j1p == 0) and (j2p == 0)) {return TComplex(Ih4Re_narrow,-Ih4Im_narrow);}
      if ((j1 == 2) and (j2 == 1) and (j1p == 0) and (j2p == 1)) {return TComplex(Ih11Re_narrow,-Ih11Im_narrow);}
      if ((j1 == 2) and (j2 == 1) and (j1p == 0) and (j2p == 2)) {return TComplex(Ih16Re_narrow,-Ih16Im_narrow);}
      if ((j1 == 2) and (j2 == 1) and (j1p == 1) and (j2p == 0)) {return TComplex(Ih9Re_narrow,-Ih9Im_narrow);}
      if ((j1 == 2) and (j2 == 1) and (j1p == 1) and (j2p == 1)) {return TComplex(Ih18Re_narrow,-Ih18Im_narrow);}
      if ((j1 == 2) and (j2 == 1) and (j1p == 1) and (j2p == 2)) {return TComplex(Ih20Re_narrow,Ih20Im_narrow);}
      if ((j1 == 2) and (j2 == 1) and (j1p == 2) and (j2p == 0)) {return TComplex(Ih14Re_narrow,-Ih14Im_narrow);}

      if ((j1 == 2) and (j2 == 1) and (j1p == 2) and (j2p == 1)) {return TComplex(Ih29Re_narrow,0.);}
      if ((j1 == 2) and (j2 == 1) and (j1p == 2) and (j2p == 2)) {return TComplex(Ih21Re_narrow,Ih21Im_narrow);}
      if ((j1 == 2) and (j2 == 2) and (j1p == 0) and (j2p == 0)) {return TComplex(Ih5Re_narrow,-Ih5Im_narrow);}
      if ((j1 == 2) and (j2 == 2) and (j1p == 0) and (j2p == 1)) {return TComplex(Ih12Re_narrow,-Ih12Im_narrow);}
      if ((j1 == 2) and (j2 == 2) and (j1p == 0) and (j2p == 2)) {return TComplex(Ih17Re_narrow,-Ih17Im_narrow);}
      if ((j1 == 2) and (j2 == 2) and (j1p == 1) and (j2p == 0)) {return TComplex(Ih12Re_narrow,-Ih12Im_narrow);}
      if ((j1 == 2) and (j2 == 2) and (j1p == 1) and (j2p == 1)) {return TComplex(Ih19Re_narrow,-Ih19Im_narrow);}
      if ((j1 == 2) and (j2 == 2) and (j1p == 1) and (j2p == 2)) {return TComplex(Ih21Re_narrow,-Ih21Im_narrow);}
      if ((j1 == 2) and (j2 == 2) and (j1p == 2) and (j2p == 0)) {return TComplex(Ih17Re_narrow,-Ih17Im_narrow);}
      if ((j1 == 2) and (j2 == 2) and (j1p == 2) and (j2p == 1)) {return TComplex(Ih21Re_narrow,-Ih21Im_narrow);}

      if ((j1 == 2) and (j2 == 2) and (j1p == 2) and (j2p == 2)) {return TComplex(Ih30Re_narrow,0.);}

   }

   throw std::invalid_argument( "Invalid argument 8" );

 }

// ---------------------------------------------------
// PDF components.

Double_t MCGenComb::model_comp_omega(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const 
 {

   return (AAj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*hj1j2j1pj2p(m1,m2,j1,j2,j1p,j2p)).Re()*ghhp(phi,h,hp)*fjjphhp(cos1,j1,j1p,h,hp)*fjjphhp(cos2,j2,j2p,h,hp);

 }

// ---------------------------------------------------
// Integrals of the PDF components.

Double_t MCGenComb::Imodel_comp_omega(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp) const 
 {

   return (AAj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Ihj1j2j1pj2p(j1,j2,j1p,j2p)).Re()*Ighhp(h,hp)*Ifjjphhp(j1,j1p,h,hp)*Ifjjphhp(j2,j2p,h,hp);

 }

// ---------------------------------------------------
// PDF.

Double_t MCGenComb::model_omega() const 
 {

   return 100./6.*(model_comp_omega(1,1,0,1,1,0)+model_comp_omega(1,1,1,1,1,1)+model_comp_omega(1,1,2,1,1,2)+2.*model_comp_omega(1,1,1,1,1,0)+2.*model_comp_omega(1,1,2,1,1,0)+2.*model_comp_omega(1,1,2,1,1,1));

 }

// ---------------------------------------------------
// Integral of the PDF.

Double_t MCGenComb::Imodel_omega() const 
 {

   return 100./6.*(Imodel_comp_omega(1,1,0,1,1,0)+Imodel_comp_omega(1,1,1,1,1,1)+Imodel_comp_omega(1,1,2,1,1,2));

 }

// ---------------------------------------------------
// Decay time dependence.

Double_t MCGenComb::timemodel(Double_t tau) const 
 {

   // Normalization factors.
   Double_t norm_PhSp = 1./gammaL;
   Double_t norm_VV = 1.18/gammaL+0.18/gammaH;

   // Relative yields.
   Double_t R_VV_to_PhSp_Ngen_2011 = 0.2425273669948235;
   Double_t R_VV_to_PhSp_Ngen_2012 = 0.4895249199941268;
   R_VV = norm_PhSp/norm_VV;
   if (year == 0) {R_VV *= R_VV_to_PhSp_Ngen_2011;}
   else {R_VV *= R_VV_to_PhSp_Ngen_2012;}

   if (gen_model == 0) {return exp(-gammaL*tau)/norm_PhSp;}
   else if (gen_model == 1) {return (1.18*exp(-gammaL*tau)+0.18*exp(-gammaH*tau))/norm_VV;}
   else {return ((1.+1.18*R_VV)*exp(-gammaL*tau)+0.18*R_VV*exp(-gammaH*tau))/((1.+1.18*R_VV)/gammaL+0.18*R_VV/gammaH);}

 }

// ---------------------------------------------------

Double_t MCGenComb::evaluate() const 
 {

	// Normalization factors (in a generation mass window from threshold, M(K)+M(pi), to 2000 MeV/c2).
	Double_t norm_PhSp = 140648555.41415584;
	Double_t norm_VV = 249890.75981680135;

	// Relative yields.
	Double_t R_VV_to_PhSp_Ngen_2011 = 0.2425273669948235;
	Double_t R_VV_to_PhSp_Ngen_2012 = 0.4895249199941268;
	R_VV = norm_PhSp/norm_VV;
	if (year == 0) {R_VV *= R_VV_to_PhSp_Ngen_2011;}
	else {R_VV *= R_VV_to_PhSp_Ngen_2012;}

	if (option == 1) {
		if (gen_model == 0) {return phasespace(m1,m2);}
		else if (gen_model == 1) {return model_omega();}
		else {return (phasespace(m1,m2)+R_VV*model_omega())/(1.+R_VV);}
	}
	else if (option == 2) {return timemodel(t);}

	throw std::invalid_argument( "Invalid option value." );

}
