#include "Riostream.h" 
#include "MassPropagators.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h"
#include "TF1.h"
#include <stdexcept>
#include "RooMath.h"
#include "BWtools.C"

#define MPion 139.57018
#define MKaon 493.667
#define MMuon 105.65836668
#define MJPsi 3096.916
#define MKst892 895.81

ClassImp(MassPropagators) 

// ---------------------------------------------------

 MassPropagators::MassPropagators(const char *name, const char *title,
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
                        RooAbsReal& _model_dw) :
   RooAbsReal(name,title),
   m("m","m",this,_m),
   p1("p1","p1",this,_p1),
   p2("p2","p2",this,_p2),
   m_B("m_B","m_B",this,_m_B),
   m_Kst0_800("m_Kst0_800","m_Kst0_800",this,_m_Kst0_800),
   gamma_Kst0_800("gamma_Kst0_800","gamma_Kst0_800",this,_gamma_Kst0_800),
   m_Kst0_1430("m_Kst0_1430","m_Kst0_1430",this,_m_Kst0_1430),
   gamma_Kst0_1430("gamma_Kst0_1430","gamma_Kst0_1430",this,_gamma_Kst0_1430),
   m_Kst1_892("m_Kst1_892","m_Kst1_892",this,_m_Kst1_892),
   gamma_Kst1_892("gamma_Kst1_892","gamma_Kst1_892",this,_gamma_Kst1_892),
   m_Kst1_1410("m_Kst1_1410","m_Kst1_1410",this,_m_Kst1_1410),
   gamma_Kst1_1410("gamma_Kst1_1410","gamma_Kst1_1410",this,_gamma_Kst1_1410),
   m_Kst1_1680("m_Kst1_1680","m_Kst1_1680",this,_m_Kst1_1680),
   gamma_Kst1_1680("gamma_Kst1_1680","gamma_Kst1_1680",this,_gamma_Kst1_1680),
   m_Kst2_1430("m_Kst2_1430","m_Kst2_1430",this,_m_Kst2_1430),
   gamma_Kst2_1430("gamma_Kst2_1430","gamma_Kst2_1430",this,_gamma_Kst2_1430),
   a_lass("a_lass","a_lass",this,_a_lass),
   r_lass("r_lass","r_lass",this,_r_lass),
   g2_kpi("g2_kpi","g2_kpi",this,_g2_kpi),
   alpha_mod("alpha_mod","alpha_mod",this,_alpha_mod),
   alpha_phase("alpha_phase","alpha_phase",this,_alpha_phase),
   beta_mod("beta_mod","beta_mod",this,_beta_mod),
   beta_phase("beta_phase","beta_phase",this,_beta_phase),
   delta_mod("delta_mod","delta_mod",this,_delta_mod),
   delta_phase("delta_phase","delta_phase",this,_delta_phase),
   gamma_mod("gamma_mod","gamma_mod",this,_gamma_mod),
   gamma_phase("gamma_phase","gamma_phase",this,_gamma_phase),
   wave("wave","wave",this,_wave),
   PS("PS","PS",this,_PS),
   model_sw("model_sw","model_sw",this,_model_sw),
   model_pw("model_pw","model_pw",this,_model_pw),
   model_dw("model_dw","model_dw",this,_model_dw)
 { 
 }

 MassPropagators::MassPropagators(const MassPropagators& other, const char* name) :  
   RooAbsReal(other,name),
   m("m",this,other.m),
   p1("p1",this,other.p1),
   p2("p2",this,other.p2),
   m_B("m_B",this,other.m_B),
   m_Kst0_800("m_Kst0_800",this,other.m_Kst0_800),
   gamma_Kst0_800("gamma_Kst0_800",this,other.gamma_Kst0_800),
   m_Kst0_1430("m_Kst0_1430",this,other.m_Kst0_1430),
   gamma_Kst0_1430("gamma_Kst0_1430",this,other.gamma_Kst0_1430),
   m_Kst1_892("m_Kst1_892",this,other.m_Kst1_892),
   gamma_Kst1_892("gamma_Kst1_892",this,other.gamma_Kst1_892),
   m_Kst1_1410("m_Kst1_1410",this,other.m_Kst1_1410),
   gamma_Kst1_1410("gamma_Kst1_1410",this,other.gamma_Kst1_1410),
   m_Kst1_1680("m_Kst1_1680",this,other.m_Kst1_1680),
   gamma_Kst1_1680("gamma_Kst1_1680",this,other.gamma_Kst1_1680),
   m_Kst2_1430("m_Kst2_1430",this,other.m_Kst2_1430),
   gamma_Kst2_1430("gamma_Kst2_1430",this,other.gamma_Kst2_1430),
   a_lass("a_lass",this,other.a_lass),
   r_lass("r_lass",this,other.r_lass),
   g2_kpi("g2_kpi",this,other.g2_kpi),
   alpha_mod("alpha_mod",this,other.alpha_mod),
   alpha_phase("alpha_phase",this,other.alpha_phase),
   beta_mod("beta_mod",this,other.beta_mod),
   beta_phase("beta_phase",this,other.beta_phase),
   delta_mod("delta_mod",this,other.delta_mod),
   delta_phase("delta_phase",this,other.delta_phase),
   gamma_mod("gamma_mod",this,other.gamma_mod),
   gamma_phase("gamma_phase",this,other.gamma_phase),
   wave("wave",this,other.wave),
   PS("PS",this,other.PS),
   model_sw("model_sw",this,other.model_sw),
   model_pw("model_pw",this,other.model_pw),
   model_dw("model_dw",this,other.model_dw)
 { 
 } 

// ---------------------------------------------------
// Invariant mass dependent acceptance.

Double_t MassPropagators::Acc(Double_t mu) const
 { 
   
   return 1.+p1*mu+p2*mu*mu;

 }

// ---------------------------------------------------
// Amplitude for a resonance of mass m0, width g0 and spin J.

std::complex<Double_t> MassPropagators::Resonance(Double_t mu, Double_t m0, Double_t g0, Int_t J) const 
 { 
   
   Int_t L;
   if (J == 0) {L = 1;}
   else if (J == 1) {L = 0;}
   else if (J == 2) {L = 1;}

   std::complex<Double_t> T = BW_T(mu,m0,g0,MPion,MKaon,J);

   Double_t q = get_q(mu,MPion,MKaon);
   Double_t q0 = get_q(m0,MPion,MKaon);
   if (q==0) return 0;
   Double_t kst_decay = pow(q/mu,J)*sqrt(Blatt_Weisskopf(q,q0,J));


   Double_t p = get_q(m_B,MJPsi,mu);
   Double_t p0 = get_q(m_B,MJPsi,m0);
   if (p==0) return 0;
   Double_t kst_birth = pow(p/m_B,L)*sqrt(Blatt_Weisskopf(p,p0,L));

   return T * kst_birth * kst_decay;
 } 

// ---------------------------------------------------
// Amplitude for the spin-0 non resonant term.

Double_t MassPropagators::NonRes(Double_t mu) const 
 { 
   
   Double_t p = get_q(m_B,MJPsi,mu);
   if (p==0) return 0;

   Double_t T = p/m_B;

   return T;

 } 

// ---------------------------------------------------
// Lass parametrization for the S wave.

std::complex<Double_t> MassPropagators::Lass(Double_t mu, Double_t m0, Double_t g0) const 
 { 

   std::complex<Double_t> i(0,1);
   
   Double_t q = get_q(mu,MPion,MKaon);
   Double_t q0 = get_q(m0,MPion,MKaon);
   if (q==0) return 0;
   Double_t p = get_q(m_B,MJPsi,mu);
   Double_t p0 = get_q(m_B,MJPsi,m0);
   if (p==0) return 0;

   Double_t cotg_deltaB = 1./(a_lass*q)+0.5*r_lass*q;
   Double_t deltaB = atan(1./cotg_deltaB);
   std::complex<Double_t> expo(cos(2.*deltaB),sin(2.*deltaB));

   Double_t gamma_mu = g0*q/q0*m0/mu;
   Double_t cotg_deltaR = (m0*m0-mu*mu)/(m0*gamma_mu);

   std::complex<Double_t> T = sqrt(Blatt_Weisskopf(p,p0,1))*p*mu/q*(1./(cotg_deltaB-i)+expo/(cotg_deltaR-i));

   return T;

 } 

// ---------------------------------------------------
// Flatté distribution.
// (Ask Liming Zhang)

std::complex<Double_t> MassPropagators::Flatte(Double_t mu, Double_t m0, Double_t g0, Double_t gkpi2) const 
 { 

   std::complex<Double_t> i(0,1);

   Double_t rhokpi = sqrt(1.-(MKaon-MPion)*(MKaon-MPion)/mu/mu)*sqrt(1.+(MKaon-MPion)*(MKaon-MPion)/mu/mu);
   Double_t rhokstpi = sqrt(1.-(MKst892-MPion)*(MKst892-MPion)/mu/mu)*sqrt(1.+(MKst892-MPion)*(MKst892-MPion)/mu/mu);

   std::complex<Double_t> T = 1./(m0*m0-mu*mu-i*(gkpi2*(rhokpi-rhokstpi)+m0*g0*rhokstpi));

   return T;

 } 

// ---------------------------------------------------
// Mass propagator.

std::complex<Double_t> MassPropagators::Prop(Double_t mu, Int_t wave_j, Int_t model_num_sw, Int_t model_num_pw, Int_t model_num_dw) const 
 { 

    std::complex<Double_t> one(1,0);
    std::complex<Double_t> i(0,1);

    std::complex<Double_t> T;
    std::complex<Double_t> alpha(alpha_mod*cos(alpha_phase),alpha_mod*sin(alpha_phase));
    std::complex<Double_t> beta(beta_mod*cos(beta_phase),beta_mod*sin(beta_phase));
    std::complex<Double_t> delta(delta_mod*cos(delta_phase),delta_mod*sin(delta_phase));
    std::complex<Double_t> gamma(gamma_mod*cos(gamma_phase),gamma_mod*sin(gamma_phase));

    if (wave_j == 0)
	{
	if (model_num_sw == 1) {T = Resonance(mu,m_Kst0_1430,gamma_Kst0_1430,0) + alpha*Resonance(mu,m_Kst0_800,gamma_Kst0_800,0) + beta*NonRes(mu);}
        else if (model_num_sw == 2) {T = Lass(mu,m_Kst0_1430,gamma_Kst0_1430);}
        else if (model_num_sw == 3) {
            std::complex<Double_t> K = get_K(mu,m_Kst0_1430,gamma_Kst0_1430,MPion,MKaon,0) + alpha*get_K(mu,m_Kst0_800,gamma_Kst0_800,MPion,MKaon,0) + beta;
            T = K/(one-i*K);
            }
	}

    else if (wave_j == 1)
	{
	if (model_num_pw == 1) {T = Resonance(mu,m_Kst1_892,gamma_Kst1_892,1);}
	else if (model_num_pw == 2) {T = Resonance(mu,m_Kst1_892,gamma_Kst1_892,1) + delta*Resonance(mu,m_Kst1_1410,gamma_Kst1_1410,1);}
	else if (model_num_pw == 3) {T = Resonance(mu,m_Kst1_892,gamma_Kst1_892,1) + delta*Resonance(mu,m_Kst1_1410,gamma_Kst1_1410,1) + gamma*Resonance(mu,m_Kst1_1680,gamma_Kst1_1680,1);}
        else if (model_num_sw == 4) {
            std::complex<Double_t> K = get_K(mu,m_Kst1_892,gamma_Kst1_892,MPion,MKaon,1) + delta*get_K(mu,m_Kst1_1410,gamma_Kst1_1410,MPion,MKaon,1);
            T = K/(one-i*K);
            }
        else if (model_num_sw == 5) {
            std::complex<Double_t> K = get_K(mu,m_Kst1_892,gamma_Kst1_892,MPion,MKaon,1) + delta*get_K(mu,m_Kst1_1410,gamma_Kst1_1410,MPion,MKaon,1) + gamma*get_K(mu,m_Kst1_1680,gamma_Kst1_1680,MPion,MKaon,1);
            T = K/(one-i*K);
            }
	}

    else if (wave_j == 2)
	{
	if (model_num_dw == 1) {T = Resonance(mu,m_Kst2_1430,gamma_Kst2_1430,2);}
	else if (model_num_dw == 2) {T = Flatte(mu,m_Kst2_1430,gamma_Kst2_1430,g2_kpi);}
	}

   return T;

 }

// ---------------------------------------------------
// Phase space factor.

Double_t MassPropagators::PhaseSpace(Double_t mu) const 
 { 

   Double_t PS = get_q(mu,MPion,MKaon)*get_q(m_B,MJPsi,mu)/m_B;

   return PS;

 }

// ---------------------------------------------------

 Double_t MassPropagators::likelihood(Double_t mu) const 
 { 

   return (Prop(mu,wave,model_sw,model_pw,model_dw)*conj(Prop(mu,wave,model_sw,model_pw,model_dw))).real()*PhaseSpace(mu)*Acc(mu);

 }

// ---------------------------------------------------

 Double_t MassPropagators::ll(Double_t mu) const 
 { 

   return log((Prop(mu,wave,model_sw,model_pw,model_dw)*conj(Prop(mu,wave,model_sw,model_pw,model_dw))).real()*PhaseSpace(mu)*Acc(mu));

 }

// ---------------------------------------------------

 Double_t MassPropagators::evaluate() const 
 { 

   if (PS == 1) {return PhaseSpace(m)*Acc(m);}
   else if (PS == 892) {return (Resonance(m,m_Kst1_892,gamma_Kst1_892,1)*conj(Resonance(m,m_Kst1_892,gamma_Kst1_892,1))).real()*PhaseSpace(m)*Acc(m);}
   else if (PS == 1410) {return (Resonance(m,m_Kst1_1410,gamma_Kst1_1410,1)*conj(Resonance(m,m_Kst1_1410,gamma_Kst1_1410,1))).real()*PhaseSpace(m)*Acc(m);}
   else if (PS == 1680) {return (Resonance(m,m_Kst1_1680,gamma_Kst1_1680,1)*conj(Resonance(m,m_Kst1_1680,gamma_Kst1_1680,1))).real()*PhaseSpace(m)*Acc(m);}
   return (Prop(m,wave,model_sw,model_pw,model_dw)*conj(Prop(m,wave,model_sw,model_pw,model_dw))).real()*PhaseSpace(m)*Acc(m);

 }
