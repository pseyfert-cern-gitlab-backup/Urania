#include <iostream>
#include <math.h>
#include <complex>
#include "TComplex.h"

// using namespace std;

Double_t a_dif = 0.00195;
Double_t b_dif = 0.00176;
Double_t r_kst = 0.003;//1./197.3;//0.0034;
Double_t r_kst0 = 0.;
Double_t m_kaon = 493.677;
Double_t m_pion = 139.57;


Double_t J = 1;
Double_t L = 0;

Double_t get_q(Double_t Mass, Double_t m1_, Double_t m2_)
{
  Double_t M2 = Mass*Mass;
  Double_t m12 = m1_*m1_;
  Double_t m22 = m2_*m2_;
  Double_t q2 = .25*( M2*M2 - 2*M2*(m12+m22) +(m12*m12+m22*m22)-2*m12*m22) /M2;
  if (q2<0) {return 0.;}

  return sqrt(q2);
}


Double_t Blatt_Weisskopf(Double_t Q_, Double_t Q0_, Int_t L_ = 1)
  {
  if (L_<1.) return 1.;
  
  Double_t d_ = 3.e-03/L_;/// this is true for L_ = 1,2. No clue for the rest!!!!!.
  Double_t z_ = Q_*d_*Q_*d_;
  Double_t z0_ = Q0_*d_*Q0_*d_;
  if (L_==1) return (1+z0_)/(1+z_);
  if (L_==2) return ((z0_-3)*(z0_-3) + 9*z0_) / ((z_-3)*(z_-3) + 9*z_);
  if (L_==3) return (z0_*(z0_-15)*(z0_-15) + 9*(z0_-5)) / (z_*(z_-15)*(z_-15) + 9*(z_-5));
  return ( pow(z0_*z0_ -45*z0_+105,2) +25*z0_*(2*z0_-21)*(2*z0_-21)) /(pow(z_*z_ -45*z_+105,2) +25*z_*(2*z_-21)*(2*z_-21));
  }


Double_t Blatt_Weisskopf_fM(Double_t M, Int_t L_ = 1, Double_t m1_=139.57018,Double_t m2_=493.677,Double_t M0=895.94)
  {
    Double_t q = get_q(M,m1_,m2_);
    Double_t q0 = get_q(M0,m1_,m2_);
    return Blatt_Weisskopf(q,q0,L_);
  }


std::complex<Double_t> BW_T(Double_t M, Double_t M0, Double_t Gamma0, Double_t m1_, Double_t m2_,  Double_t J_)
    {
  // BW amplitude (i.e, not quared), to use for interferences. 
  // Gamma is phase space dependent
  // Uses Blatt-Weiskopff barrier factors from PDG
  // M : mass of the pair, M0: nominal mass of the resonance, Gamma0: nominal width of the resonance, ,
  // m1_: mass of one of the PSEUDOSCALAR daughters, m2_: mass of the other PSEUDOSCALAR daughter, 
  // J_ angular momentum quantum number of the resonance

  
  Double_t q = get_q(M,m1_,m2_);
  Double_t q0 = get_q(M0,m1_,m2_);

  Double_t Gamma = Gamma0*pow(q/q0,2*J_+1)*M0/M*Blatt_Weisskopf(q,q0,J_);

  std::complex<Double_t> denom(M*M-M0*M0,-Gamma*M0);
  std::complex<Double_t> num(1.,0.);

  //Double_t nu = TMath::Sqrt(mass0*mass0*(mass0*mass0+Gamma*Gamma));
  //std::complex<Double_t> k(TMath::Sqrt(2.*TMath::Sqrt(2.)*mass0*Gamma*nu/TMath::Pi()/TMath::Sqrt(mass0*mass0+nu)),0.);

  return num/denom;
    }


  Double_t get_K(Double_t M, Double_t M0, Double_t Gamma0, Double_t m1_, Double_t m2_,  Int_t J_ = 1)
  {
  Double_t q = get_q(M,m1_,m2_);
  Double_t q0 = get_q(M0,m1_,m2_);
  Double_t Gamma = Gamma0*pow(q/q0,2*J_+1)*M0/M*Blatt_Weisskopf(q,q0,J_);

  return M0*Gamma/(M0*M0-M*M); 

  }

  Double_t get_K_hat(Double_t M, Double_t M0, Double_t Gamma0, Double_t m1_, Double_t m2_,  Int_t J_ = 1)
  {

  //Double_t q = get_q(M,m1_,m2_);
  //Double_t q0 = get_q(M0,m1_,m2_);
  //Double_t Gamma = Gamma0*pow(q/q0,2*J_+1)*M0/M*Blatt_Weisskopf(q,q0,J_);

  return sqrt(M0*Gamma0)/(M0*M0-M*M); 

  }


Double_t get_phasespace(Double_t mD1,Double_t mD2,Double_t mM)
{
   Double_t Q_kst = sqrt((mD1*mD1 - pow(m_kaon+m_pion,2))*(mD1*mD1 - pow(m_kaon-m_pion,2)))/(2*mD1);
   Double_t Q_kstb = sqrt((mD2*mD2 - pow(m_kaon+m_pion,2))*(mD2*mD2 - pow(m_kaon-m_pion,2)))/(2*mD2);
   Double_t Q_B = sqrt((mM*mM - pow(mD1+mD2,2))*(mM*mM - pow(mD1-mD2,2)))/(2*mM);
   Double_t phasespace = Q_kst * Q_kstb * Q_B;
   
   return phasespace;
}



Double_t calculatePDF_1D(Int_t indx,Double_t m1, Double_t m2, Double_t m_kst, Double_t g_kst, Double_t MB)
{


  Double_t m_kst_, m_kstb_;
  
  if (indx==1)
    {
      m_kst_ = m1;
      m_kstb_ = m2;
    }
  else
    {
      m_kst_ = m2;
      m_kstb_ = m1;
    }

   Double_t K0 = get_K(m_kst_,m_kst,g_kst,m_kaon,m_pion,J);
   Double_t K0h = get_K_hat(m_kst_,m_kst,g_kst,m_kaon,m_pion,J);

   Double_t q = get_q(m_kst_,m_kaon,m_pion);
   Double_t q0 = get_q(m_kst,m_kaon,m_pion);
   if (q==0) return 0;
   Double_t rho_decay = pow(q,2*J+1)*Blatt_Weisskopf(q,q0,J);


   Double_t p = get_q(MB,m_kstb_,m_kst_);
   Double_t p0 = get_q(MB,m_kstb_,m_kst);
   if (p==0) return 0;
   Double_t rho_birth = pow(p,2*L+1)*Blatt_Weisskopf(p,p0,L);

   std::complex<Double_t> num(K0h,0.); 
   std::complex<Double_t> den(1, -(K0)); 
   std::complex<Double_t> T = num/den;
   Double_t  kst1 = real(T*conj(T));

   return kst1 * rho_decay * rho_birth;



}



Double_t getPDF_1D(Double_t m_kst_, Double_t m_kstb_, Double_t M0, Double_t G0, Double_t MB)
{


  Double_t m_kst = M0;
  Double_t g_kst = G0;
  
   Double_t K0 = get_K(m_kst_,m_kst,g_kst,m_kaon,m_pion,J);
   Double_t K0h = get_K_hat(m_kst_,m_kst,g_kst,m_kaon,m_pion,J);

   Double_t q = get_q(m_kst_,m_kaon,m_pion);
   Double_t q0 = get_q(m_kst,m_kaon,m_pion);
   if (q==0) return 0;
   Double_t rho_decay = pow(q,2*J+1)*Blatt_Weisskopf(q,q0,J);


   Double_t p = get_q(MB,m_kstb_,m_kst_);
   Double_t p0 = get_q(MB,m_kstb_,m_kst);
   if (p==0) return 0;
   Double_t rho_birth = pow(p,2*L+1)*Blatt_Weisskopf(p,p0,L);

   std::complex<Double_t> num(K0h,0.); 
   std::complex<Double_t> den(1, -(K0)); 
   std::complex<Double_t> T = num/den;
   Double_t  kst1 = real(T*conj(T));

   return kst1 * rho_decay * rho_birth;


}


Double_t getPDF_2D(Double_t mkst, Double_t mkstb, Double_t M0, Double_t G0, Double_t MB)
{
  Double_t PDF_1 = getPDF_1D(mkst,mkstb,M0,G0,MB);
  Double_t PDF_2 = getPDF_1D(mkstb,mkst,M0,G0,MB);

   return PDF_1*PDF_2;

}

TComplex PWaveMass_2(Double_t m)
 { 
   Double_t m0 = 1414;
   Double_t G0 = 232.;
   

   Double_t Q_kst = sqrt((m0*m0 - pow(m_kaon+m_pion,2))*(m0*m0 - pow(m_kaon-m_pion,2)))/(2*m0);

   Double_t Q_m = sqrt((m*m - pow(m_kaon+m_pion,2))*(m*m - pow(m_kaon-m_pion,2)))/(2*m);

   Double_t g1_m = G0*(m0/m)*((1+pow(r_kst*Q_kst,2))/(1+pow(r_kst*Q_m,2)))*pow(Q_m/Q_kst,3);
   
   Double_t g1_m_num = G0*m0*((1+pow(r_kst*Q_kst,2))/(1+pow(r_kst*Q_m,2)))*pow(Q_m/Q_kst,2)/Q_kst;
   
   // WITH m/q

   TComplex num(pow(m0,2)*G0*((1+pow(r_kst*Q_kst,2))/(1+pow(r_kst*Q_m,2)))*pow(Q_m,2)/pow(Q_kst,3),0);
   TComplex denom(m0*m0 - m*m, -m0*g1_m);
   

//    //WITHOUT m/q
//    TComplex num(m0*g1_m,0);
//    TComplex denom(m0*m0 - m*m, -m0*g1_m);

   TComplex BW = num/denom;//(m/Q_m)*m0*g1_m/((m0*m0 - m*m) - i*m0*g1_m);//m0*g1_m/((m0*m0 - m*m) - i*m0*g1_m);

//    cout << "G0: "<<G0<<endl;
//    cout << "r_kst: "<<r_kst<<endl;

//   Double_t phasespace = sqrt(2*pow(Q_m/m,3));


   return BW/sqrt(72.2562757614);

 }



TComplex PWaveMass(Double_t m, Double_t m_kst, Double_t g_kst)
 { 
   
  
   Double_t Q_kst = sqrt((m_kst*m_kst - pow(m_kaon+m_pion,2))*(m_kst*m_kst - pow(m_kaon-m_pion,2)))/(2*m_kst);

   Double_t Q_m = sqrt((m*m - pow(m_kaon+m_pion,2))*(m*m - pow(m_kaon-m_pion,2)))/(2*m);

   Double_t g1_m = g_kst*(m_kst/m)*((1+pow(r_kst*Q_kst,2))/(1+pow(r_kst*Q_m,2)))*pow(Q_m/Q_kst,3);
   
   Double_t g1_m_num = g_kst*m_kst*((1+pow(r_kst*Q_kst,2))/(1+pow(r_kst*Q_m,2)))*pow(Q_m/Q_kst,2)/Q_kst;
   
   // WITH m/q
   TComplex num(pow(m_kst,2)*g_kst*((1+pow(r_kst*Q_kst,2))/(1+pow(r_kst*Q_m,2)))*pow(Q_m,2)/pow(Q_kst,3),0);
   TComplex denom(m_kst*m_kst - m*m, -m_kst*g1_m);
   
//    //WITHOUT m/q
//    TComplex num(m_kst*g1_m,0);
//    TComplex denom(m_kst*m_kst - m*m, -m_kst*g1_m);

   TComplex BW = num/denom;//(m/Q_m)*m_kst*g1_m/((m_kst*m_kst - m*m) - i*m_kst*g1_m);//m_kst*g1_m/((m_kst*m_kst - m*m) - i*m_kst*g1_m);

//    cout << "g_kst0: "<<g_kst0<<endl;
//    cout << "r_kst: "<<r_kst<<endl;

//   Double_t phasespace = sqrt(2*pow(Q_m/m,3));

//   Only one P-wave:
//   return BW/sqrt(72.2562757614);


   
//  Two P-waves:


   TComplex BW_2 = PWaveMass_2(m);
   TComplex beta(0.20 , 5.31 , 1);
   
   TComplex TwoBW = BW + beta*BW_2;


//    return TwoBW/sqrt(70.0309039034);//68.533431075774885)/sqrt(sqrt(1.04224546179));
   return BW;

 } 


TComplex SWaveMass(Double_t m,Double_t m_kst0, Double_t g_kst0)
{

   Double_t Q_kst = sqrt((m_kst0*m_kst0 - pow(m_kaon+m_pion,2))*(m_kst0*m_kst0 - pow(m_kaon-m_pion,2)))/(2*m_kst0);
   Double_t Q_m = sqrt((m*m - pow(m_kaon+m_pion,2))*(m*m - pow(m_kaon-m_pion,2)))/(2*m);

   Double_t g0_m = g_kst0*(m_kst0/m)*(Q_m/Q_kst);

   Double_t g0_m_num = g_kst0*m_kst0*(1/Q_kst);
   
   TComplex i(0,1);


   Double_t cotAB_m = 1./(a_dif*Q_m)+0.5*b_dif*Q_m;



   TComplex eAB_m(1,2*atan(1./cotAB_m),1);



   // WITH (m/q)
   TComplex BW_m = (pow(m_kst0,2)*g_kst0/Q_kst)/((m_kst0*m_kst0 - m*m) - i*m_kst0*g0_m);
   TComplex NR_m = m/(Q_m*cotAB_m - i*Q_m);


//    //WITHOUT (m/q)
//    TComplex BW_m = m_kst0*g0_m/((m_kst0*m_kst0 - m*m) - i*m_kst0*g0_m);//(m/Q_m)*m_kst0*g0_m/((m_kst0*m_kst0 - m*m) - i*m_kst0*g0_m);//
//    TComplex NR_m = 1./(cotAB_m - i);


//    Double_t phasespace = sqrt(2*(Q_m/m));


   TComplex SW_m = (NR_m + eAB_m*BW_m);//BW_m;

//    cout << "g_kst0: "<<g_kst0<<endl;
//    cout << "r_kst: "<<r_kst<<endl;

   return SW_m;


}



Double_t get_MassTerm(Int_t indx, Double_t m1, Double_t m2, 
		      Double_t fL, Double_t fpa, Double_t Asp2, Double_t Asm2, Double_t Ass2,
		      Double_t dpa, Double_t dpe, Double_t dsp, Double_t dsm, Double_t dss,
		      // Double_t Af, Double_t df, 
// 		      Double_t Ag, Double_t dg, 
// 		      Double_t Ah, Double_t dh, 
		      Double_t Gs, Double_t DGs, 
		      Double_t m_kst, Double_t m_kst0, 
		      Double_t g_kst, Double_t g_kst0 , 
		      Double_t m_Bs, Double_t normP, Double_t normS, Double_t normSS)
{


   Double_t Ap2 = 1-Asp2-Asm2-Ass2;
   Double_t A02 = fL*Ap2;
   Double_t Apa2 = fpa*Ap2;
   Double_t fpe = 1-fL-fpa;
   Double_t Ape2 = fpe*Ap2;

   Double_t A0 = sqrt(A02);
   Double_t Apa = sqrt(Apa2);
   Double_t Ape = sqrt(Ape2);
   Double_t Asp = sqrt(Asp2);
   Double_t Asm = sqrt(Asm2);
   Double_t Ass = sqrt(Ass2);

   Double_t norm_int = sqrt(normP*normS);
   Double_t norm_int_ss = sqrt(normP*normSS);
   Double_t norm_int_sv_ss = sqrt(normS*normSS);

   Double_t d0 = 0;

   TComplex CA0(A0,d0,1);
   TComplex CApa(Apa,dpa,1);
   TComplex CApe(Ape,dpe,1);
   TComplex CAsp(Asp,dsp,1);
   TComplex CAsm(Asm,dsm,1);
   TComplex CAss(Ass,dss,1);

   Double_t GL = Gs + DGs/2.;
   Double_t GH = Gs - DGs/2.;
  
   Double_t massterm = 0;
   Double_t norm = 1;
   
   TComplex PW_m1 = PWaveMass(m1,m_kst,g_kst);
   TComplex PW_m2 = PWaveMass(m2,m_kst,g_kst);
   TComplex SW_m1 = SWaveMass(m1,m_kst0,g_kst0);
   TComplex SW_m2 = SWaveMass(m2,m_kst0,g_kst0);

   
   if (indx==1 || indx==2 || indx==3 || indx==5)
     {
//        Double_t PDF_1 = calculatePDF_1D(1,m1,m2,m_kst,g_kst,m_Bs);
//        Double_t PDF_2 = calculatePDF_1D(2,m1,m2,m_kst,g_kst,m_Bs);
       
//        massterm =  PDF_1*PDF_2;
       massterm = PW_m1.Rho2() * PW_m2.Rho2();
       norm = normP;
     }
   else if (indx==7)
     {
       Double_t K7 = (CAsp.Rho2()/GH + CAsm.Rho2()/GL)/2.;
       
       massterm = K7*PW_m1.Rho2()*SW_m2.Rho2();
       norm = normS;
     }
   else if (indx==71)
     {
       Double_t K7 = (CAsp.Rho2()/GH + CAsm.Rho2()/GL)/2.;
       
       massterm = K7*PW_m2.Rho2()*SW_m1.Rho2();
       norm = normS;
    }
  else if (indx==8)
    {
      TComplex Keven = CAsm/sqrt(2.)*TComplex::Conjugate(CA0*PW_m2)*SW_m2;
      massterm = PW_m1.Rho2()*Keven.Re();
      norm = norm_int;
    }
  else if (indx==81)
    {
      TComplex Keven = CAsm/sqrt(2.)*TComplex::Conjugate(CA0*PW_m1)*SW_m1;
      massterm = PW_m2.Rho2()*Keven.Re();
      norm = norm_int;
    }
  else if (indx==9)
    {
      TComplex Keven = CAsm/sqrt(2.)*TComplex::Conjugate(CApa*PW_m2)*SW_m2;
      massterm = PW_m1.Rho2()*Keven.Re();
      norm=norm_int;
    }
  else if (indx==91)
    {
      TComplex Keven = CAsm/sqrt(2.)*TComplex::Conjugate(CApa*PW_m1)*SW_m1;
      massterm = PW_m2.Rho2()*Keven.Re();
      norm=norm_int;
    }
  else if (indx==10)
    {
      TComplex K10 = CAsp/sqrt(2.)*TComplex::Conjugate(CApe*PW_m2)*SW_m2;
      massterm = PW_m1.Rho2()*K10.Im()  ;
      norm=norm_int;
    }
  else if (indx==101)
    {
      TComplex K10 = CAsp/sqrt(2.)*TComplex::Conjugate(CApe*PW_m1)*SW_m1;
      massterm = PW_m2.Rho2()*K10.Im()  ;
      norm=norm_int;
    }
  else if (indx==11)
    {
      TComplex K11 = CAsm*TComplex::Conjugate(CAss*SW_m1)*PW_m1;
      massterm = SW_m2.Rho2()*K11.Re();
      norm=norm_int_sv_ss;
    }
  else if (indx==111)
    {
      TComplex K11 = CAsm*TComplex::Conjugate(CAss*SW_m2)*PW_m2;
      massterm = SW_m1.Rho2()*K11.Re();
      norm=norm_int_sv_ss;
    }
//   else if (indx==1111)
//     {
//       TComplex K11 = CAg*TComplex::Conjugate(CAh*SW_m2)*PW_m2;
//       massterm = SW_m1.Rho2()*K11.Re();
//     }
//   else if (indx==1112)
//     {
//       TComplex K11 = CAg*TComplex::Conjugate(CAh*SW_m2)*PW_m2;
//       massterm = SW_m1.Rho2()*K11.Re();
//     }
  else if (indx==12) //equivalent to MassK7_int
    {
      TComplex K12 = (CAsp.Rho2()/GH - CAsm.Rho2()/GL)/2.*TComplex::Conjugate(PW_m1*SW_m2)*SW_m1*PW_m2;
      massterm = K12.Re();
      norm = normS;
    }
  else if (indx==13)
    {
      massterm = SW_m1.Rho2()*SW_m2.Rho2();
      norm = normSS;
    }
  else if (indx==14)
    {
      TComplex Keven = CAss*SW_m1*SW_m2*TComplex::Conjugate(CA0*PW_m1*PW_m2);
      massterm = Keven.Re();
      norm = norm_int_ss;
    }
  else if (indx==15)
    {
      TComplex Keven = CAss*SW_m1*SW_m2*TComplex::Conjugate(CApa*PW_m1*PW_m2);
      massterm = Keven.Re();
      norm = norm_int_ss;
    }
  else
    {
      cout << "No massterm selected. Return 0"<<endl;
      return 0;
    }

  Double_t phasespace = get_phasespace(m1,m2,m_Bs);

  return massterm*phasespace*norm;
}

Double_t get_MassTerm_Integral(Int_t indx, 
		      Double_t fL, Double_t fpa, Double_t Asp2, Double_t Asm2, Double_t Ass2,
		      Double_t dpa, Double_t dpe, Double_t dsp, Double_t dsm, Double_t dss,
		      // Double_t Af, Double_t df, 
// 		      Double_t Ag, Double_t dg, 
// 		      Double_t Ah, Double_t dh, 
		      Double_t Gs, Double_t DGs, 
		      Double_t m_kst, Double_t m_kst0, 
		      Double_t g_kst, Double_t g_kst0 , 
		      Double_t m_Bs, Double_t normP, Double_t normS, Double_t normSS,
		      Int_t n_m1,Int_t n_m2)
{


   Double_t Ap2 = 1-Asp2-Asm2-Ass2;
   Double_t A02 = fL*Ap2;
   Double_t Apa2 = fpa*Ap2;
   Double_t fpe = 1-fL-fpa;
   Double_t Ape2 = fpe*Ap2;

   Double_t A0 = sqrt(A02);
   Double_t Apa = sqrt(Apa2);
   Double_t Ape = sqrt(Ape2);
   Double_t Asp = sqrt(Asp2);
   Double_t Asm = sqrt(Asm2);
   Double_t Ass = sqrt(Ass2);

   Double_t norm_int = sqrt(normP*normS);
   Double_t norm_int_ss = sqrt(normP*normSS);
   Double_t norm_int_sv_ss = sqrt(normS*normSS);

   Double_t d0 = 0;

   TComplex CA0(A0,d0,1);
   TComplex CApa(Apa,dpa,1);
   TComplex CApe(Ape,dpe,1);
   TComplex CAsp(Asp,dsp,1);
   TComplex CAsm(Asm,dsm,1);
   TComplex CAss(Ass,dss,1);

   Double_t GL = Gs + DGs/2.;
   Double_t GH = Gs - DGs/2.;
  
   Double_t norm = 1;


  Int_t n_max = 3;
  Int_t n_m1m2 = n_m1 + n_max*n_m2;



  if (indx==1 || indx==2 || indx==3 || indx==5)
    {

      if (n_m1m2== 0) return ( 9.53823067503e+13 )*normP;
      if (n_m1m2== 1) return ( 6.90428448442e+12 )*normP;
      if (n_m1m2== 2) return ( -3.44722590531e+13 )*normP;
      if (n_m1m2== 3) return ( 6.90428448442e+12 )*normP;
      if (n_m1m2== 4) return ( 499523359401.0 )*normP;
      if (n_m1m2== 5) return ( -2.49540728766e+12 )*normP;
      if (n_m1m2== 6) return ( -3.44722590531e+13 )*normP;
      if (n_m1m2== 7) return ( -2.49540728766e+12 )*normP;
      if (n_m1m2== 8) return ( 1.24586112871e+13 )*normP;

    }
  else if (indx==7)
    {
      Double_t K7 = (CAsp.Rho2()/GH + CAsm.Rho2()/GL)/2.;
      
      if (n_m1m2== 0) return K7*( 1.67643895893e+14 )*normS;
      if (n_m1m2== 1) return K7*( 1.21344702595e+13 )*normS;
      if (n_m1m2== 2) return K7*( -6.05886677828e+13 )*normS;
      if (n_m1m2== 3) return K7*( 2.530693743e+13 )*normS;
      if (n_m1m2== 4) return K7*( 1.83025721134e+12 )*normS;
      if (n_m1m2== 5) return K7*( -9.14699393017e+12 )*normS;
      if (n_m1m2== 6) return K7*( 252270991306.0 )*normS;
      if (n_m1m2== 7) return K7*( 17901725280.4 )*normS;
      if (n_m1m2== 8) return K7*( -91348467759.5 )*normS;

    }

  else if (indx==71)
    {
      Double_t K7 = (CAsp.Rho2()/GH + CAsm.Rho2()/GL)/2.;

      if (n_m1m2== 0) return K7*( 1.67643895893e+14 )*normS;
      if (n_m1m2== 1) return K7*( 2.530693743e+13 )*normS;
      if (n_m1m2== 2) return K7*( 252270991306.0 )*normS;
      if (n_m1m2== 3) return K7*( 1.21344702595e+13 )*normS;
      if (n_m1m2== 4) return K7*( 1.83025721134e+12 )*normS;
      if (n_m1m2== 5) return K7*( 17901725280.4 )*normS;
      if (n_m1m2== 6) return K7*( -6.05886677828e+13 )*normS;
      if (n_m1m2== 7) return K7*( -9.14699393017e+12 )*normS;
      if (n_m1m2== 8) return K7*( -91348467759.5 )*normS;

    }

  else if (indx==8)
    {

      TComplex Keven = CAsm*TComplex::Conjugate(CA0);

      if (n_m1m2== 0) return (Keven.Re()*( 2.10747556558e+13 ) + Keven.Im()*( 4.554924447e+13 ))*norm_int;
      if (n_m1m2== 1) return (Keven.Re()*( 1.52595118179e+12 ) + Keven.Im()*( 3.29665840873e+12 ))*norm_int;
      if (n_m1m2== 2) return (Keven.Re()*( -7.61644063745e+12 ) + Keven.Im()*( -1.64622337945e+13 ))*norm_int;
      if (n_m1m2== 3) return (Keven.Re()*( -1.37934457355e+13 ) + Keven.Im()*( 1.82233451294e+13 ))*norm_int;
      if (n_m1m2== 4) return (Keven.Re()*( -998444954960.0 ) + Keven.Im()*( 1.31888054159e+12 ))*norm_int;
      if (n_m1m2== 5) return (Keven.Re()*( 4.98510885012e+12 ) + Keven.Im()*( -6.5862345449e+12 ))*norm_int;
      if (n_m1m2== 6) return (Keven.Re()*( -1.13526306912e+13 ) + Keven.Im()*( -1.00538373973e+13 ))*norm_int;
      if (n_m1m2== 7) return (Keven.Re()*( -821755885133.0 ) + Keven.Im()*( -727852449451.0 ))*norm_int;
      if (n_m1m2== 8) return (Keven.Re()*( 4.10297505687e+12 ) + Keven.Im()*( 3.63352260246e+12 ))*norm_int;

    }
  else if (indx==81)
    {

      TComplex Keven = CAsm*TComplex::Conjugate(CA0);
      
      if (n_m1m2== 0) return (Keven.Re()*( 2.10747556558e+13 ) + Keven.Im()*( 4.554924447e+13 ))*norm_int;
      if (n_m1m2== 1) return (Keven.Re()*( -1.37934457355e+13 ) + Keven.Im()*( 1.82233451294e+13 ))*norm_int;
      if (n_m1m2== 2) return (Keven.Re()*( -1.13526306912e+13 ) + Keven.Im()*( -1.00538373973e+13 ))*norm_int;
      if (n_m1m2== 3) return (Keven.Re()*( 1.52595118179e+12 ) + Keven.Im()*( 3.29665840873e+12 ))*norm_int;
      if (n_m1m2== 4) return (Keven.Re()*( -998444954960.0 ) + Keven.Im()*( 1.31888054159e+12 ))*norm_int;
      if (n_m1m2== 5) return (Keven.Re()*( -821755885133.0 ) + Keven.Im()*( -727852449451.0 ))*norm_int;
      if (n_m1m2== 6) return (Keven.Re()*( -7.61644063745e+12 ) + Keven.Im()*( -1.64622337945e+13 ))*norm_int;
      if (n_m1m2== 7) return (Keven.Re()*( 4.98510885012e+12 ) + Keven.Im()*( -6.5862345449e+12 ))*norm_int;
      if (n_m1m2== 8) return (Keven.Re()*( 4.10297505687e+12 ) + Keven.Im()*( 3.63352260246e+12 ))*norm_int;

    }

  else if (indx==9)
    {

      TComplex Keven = CAsm*TComplex::Conjugate(CApa);

      if (n_m1m2== 0) return (Keven.Re()*( 2.10747556558e+13 ) + Keven.Im()*( 4.554924447e+13 ))*norm_int;
      if (n_m1m2== 1) return (Keven.Re()*( 1.52595118179e+12 ) + Keven.Im()*( 3.29665840873e+12 ))*norm_int;
      if (n_m1m2== 2) return (Keven.Re()*( -7.61644063745e+12 ) + Keven.Im()*( -1.64622337945e+13 ))*norm_int;
      if (n_m1m2== 3) return (Keven.Re()*( -1.37934457355e+13 ) + Keven.Im()*( 1.82233451294e+13 ))*norm_int;
      if (n_m1m2== 4) return (Keven.Re()*( -998444954960.0 ) + Keven.Im()*( 1.31888054159e+12 ))*norm_int;
      if (n_m1m2== 5) return (Keven.Re()*( 4.98510885012e+12 ) + Keven.Im()*( -6.5862345449e+12 ))*norm_int;
      if (n_m1m2== 6) return (Keven.Re()*( -1.13526306912e+13 ) + Keven.Im()*( -1.00538373973e+13 ))*norm_int;
      if (n_m1m2== 7) return (Keven.Re()*( -821755885133.0 ) + Keven.Im()*( -727852449451.0 ))*norm_int;
      if (n_m1m2== 8) return (Keven.Re()*( 4.10297505687e+12 ) + Keven.Im()*( 3.63352260246e+12 ))*norm_int;

    }


  else if (indx==91)
    {

      TComplex Keven = CAsm*TComplex::Conjugate(CApa);
      
      if (n_m1m2== 0) return (Keven.Re()*( 2.10747556558e+13 ) + Keven.Im()*( 4.554924447e+13 ))*norm_int;
      if (n_m1m2== 1) return (Keven.Re()*( -1.37934457355e+13 ) + Keven.Im()*( 1.82233451294e+13 ))*norm_int;
      if (n_m1m2== 2) return (Keven.Re()*( -1.13526306912e+13 ) + Keven.Im()*( -1.00538373973e+13 ))*norm_int;
      if (n_m1m2== 3) return (Keven.Re()*( 1.52595118179e+12 ) + Keven.Im()*( 3.29665840873e+12 ))*norm_int;
      if (n_m1m2== 4) return (Keven.Re()*( -998444954960.0 ) + Keven.Im()*( 1.31888054159e+12 ))*norm_int;
      if (n_m1m2== 5) return (Keven.Re()*( -821755885133.0 ) + Keven.Im()*( -727852449451.0 ))*norm_int;
      if (n_m1m2== 6) return (Keven.Re()*( -7.61644063745e+12 ) + Keven.Im()*( -1.64622337945e+13 ))*norm_int;
      if (n_m1m2== 7) return (Keven.Re()*( 4.98510885012e+12 ) + Keven.Im()*( -6.5862345449e+12 ))*norm_int;
      if (n_m1m2== 8) return (Keven.Re()*( 4.10297505687e+12 ) + Keven.Im()*( 3.63352260246e+12 ))*norm_int;

    }
  else if (indx==10)
    {
      TComplex K10 = CAsp*TComplex::Conjugate(CApe);

      if (n_m1m2== 0) return (K10.Re()*( -4.554924447e+13 ) + K10.Im()*( 2.10747556558e+13 ))*norm_int;
      if (n_m1m2== 1) return (K10.Re()*( -3.29665840873e+12 ) + K10.Im()*( 1.52595118179e+12 ))*norm_int;
      if (n_m1m2== 2) return (K10.Re()*( 1.64622337945e+13 ) + K10.Im()*( -7.61644063745e+12 ))*norm_int;
      if (n_m1m2== 3) return (K10.Re()*( -1.82233451294e+13 ) + K10.Im()*( -1.37934457355e+13 ))*norm_int;
      if (n_m1m2== 4) return (K10.Re()*( -1.31888054159e+12 ) + K10.Im()*( -998444954960.0 ))*norm_int;
      if (n_m1m2== 5) return (K10.Re()*( 6.5862345449e+12 ) + K10.Im()*( 4.98510885012e+12 ))*norm_int;
      if (n_m1m2== 6) return (K10.Re()*( 1.00538373973e+13 ) + K10.Im()*( -1.13526306912e+13 ))*norm_int;
      if (n_m1m2== 7) return (K10.Re()*( 727852449451.0 ) + K10.Im()*( -821755885133.0 ))*norm_int;
      if (n_m1m2== 8) return (K10.Re()*( -3.63352260246e+12 ) + K10.Im()*( 4.10297505687e+12 ))*norm_int;
      
    }
  
  else if (indx==101)
    {
      TComplex K10 = CAsp*TComplex::Conjugate(CApe);

      if (n_m1m2== 0) return (K10.Re()*( -4.554924447e+13 ) + K10.Im()*( 2.10747556558e+13 ))*norm_int;
      if (n_m1m2== 1) return (K10.Re()*( -1.82233451294e+13 ) + K10.Im()*( -1.37934457355e+13 ))*norm_int;
      if (n_m1m2== 2) return (K10.Re()*( 1.00538373973e+13 ) + K10.Im()*( -1.13526306912e+13 ))*norm_int;
      if (n_m1m2== 3) return (K10.Re()*( -3.29665840873e+12 ) + K10.Im()*( 1.52595118179e+12 ))*norm_int;
      if (n_m1m2== 4) return (K10.Re()*( -1.31888054159e+12 ) + K10.Im()*( -998444954960.0 ))*norm_int;
      if (n_m1m2== 5) return (K10.Re()*( 727852449451.0 ) + K10.Im()*( -821755885133.0 ))*norm_int;
      if (n_m1m2== 6) return (K10.Re()*( 1.64622337945e+13 ) + K10.Im()*( -7.61644063745e+12 ))*norm_int;
      if (n_m1m2== 7) return (K10.Re()*( 6.5862345449e+12 ) + K10.Im()*( 4.98510885012e+12 ))*norm_int;
      if (n_m1m2== 8) return (K10.Re()*( -3.63352260246e+12 ) + K10.Im()*( 4.10297505687e+12 ))*norm_int;

    }
  else if (indx==11)
    {
      TComplex K11 = CAsm*TComplex::Conjugate(CAss);

      if (n_m1m2== 0) return (K11.Re()*( 5.23851337907e+13 ) + K11.Im()*( -1.13216901928e+14 ))*norm_int_sv_ss;
      if (n_m1m2== 1) return (K11.Re()*( -3.42852825149e+13 ) + K11.Im()*( -4.52956927287e+13 ))*norm_int_sv_ss;
      if (n_m1m2== 2) return (K11.Re()*( -2.82183134718e+13 ) + K11.Im()*( 2.49903204826e+13 ))*norm_int_sv_ss;
      if (n_m1m2== 3) return (K11.Re()*( 7.91178475353e+12 ) + K11.Im()*( -1.70869734561e+13 ))*norm_int_sv_ss;
      if (n_m1m2== 4) return (K11.Re()*( -5.17559664735e+12 ) + K11.Im()*( -6.83572828409e+12 ))*norm_int_sv_ss;
      if (n_m1m2== 5) return (K11.Re()*( -4.25966295325e+12 ) + K11.Im()*( 3.77333987889e+12 ))*norm_int_sv_ss;
      if (n_m1m2== 6) return (K11.Re()*( 79750268051.7 ) + K11.Im()*( -169460557780.0 ))*norm_int_sv_ss;
      if (n_m1m2== 7) return (K11.Re()*( -51594887811.6 ) + K11.Im()*( -67701097719.6 ))*norm_int_sv_ss;
      if (n_m1m2== 8) return (K11.Re()*( -42445275776.7 ) + K11.Im()*( 37814918545.6 ))*norm_int_sv_ss;
      
    }
  else if (indx==111)
    {

      TComplex K11 = CAsm*TComplex::Conjugate(CAss);


      if (n_m1m2== 0) return (K11.Re()*( 5.23851337907e+13 ) + K11.Im()*( -1.13216901928e+14 ))*norm_int_sv_ss;
      if (n_m1m2== 1) return (K11.Re()*( 7.91178475353e+12 ) + K11.Im()*( -1.70869734561e+13 ))*norm_int_sv_ss;
      if (n_m1m2== 2) return (K11.Re()*( 79750268051.7 ) + K11.Im()*( -169460557780.0 ))*norm_int_sv_ss;
      if (n_m1m2== 3) return (K11.Re()*( -3.42852825149e+13 ) + K11.Im()*( -4.52956927287e+13 ))*norm_int_sv_ss;
      if (n_m1m2== 4) return (K11.Re()*( -5.17559664735e+12 ) + K11.Im()*( -6.83572828409e+12 ))*norm_int_sv_ss;
      if (n_m1m2== 5) return (K11.Re()*( -51594887811.6 ) + K11.Im()*( -67701097719.6 ))*norm_int_sv_ss;
      if (n_m1m2== 6) return (K11.Re()*( -2.82183134718e+13 ) + K11.Im()*( 2.49903204826e+13 ))*norm_int_sv_ss;
      if (n_m1m2== 7) return (K11.Re()*( -4.25966295325e+12 ) + K11.Im()*( 3.77333987889e+12 ))*norm_int_sv_ss;
      if (n_m1m2== 8) return (K11.Re()*( -42445275776.7 ) + K11.Im()*( 37814918545.6 ))*norm_int_sv_ss;
      
    }
  else if (indx==12) //equivalent to MassK7_int
    {

      Double_t K12 = (CAsp.Rho2()/GH - CAsm.Rho2()/GL)/2.;
      
      if (n_m1m2== 0) return (K12*( 5.28132765909e+13 ))*normS;
      if (n_m1m2== 1) return (K12*( 1.13087666425e+13 ))*normS;
      if (n_m1m2== 2) return (K12*( -1.46194301633e+13 ))*normS;
      if (n_m1m2== 3) return (K12*( 1.13087666425e+13 ))*normS;
      if (n_m1m2== 4) return (K12*( 1.09523483339e+13 ))*normS;
      if (n_m1m2== 5) return (K12*( -558414851224.0 ))*normS;
      if (n_m1m2== 6) return (K12*( -1.46194301633e+13 ))*normS;
      if (n_m1m2== 7) return (K12*( -558414851224.0 ))*normS;
      if (n_m1m2== 8) return (K12*( 4.82181326116e+12 ))*normS;

    }
  else if (indx==13)
    {

      if (n_m1m2== 0) return ( 2.94649825509e+14 )*normSS;
      if (n_m1m2== 1) return ( 4.44762383492e+13 )*normSS;
      if (n_m1m2== 2) return ( 442665652919.0 )*normSS;
      if (n_m1m2== 3) return ( 4.44762383492e+13 )*normSS;
      if (n_m1m2== 4) return ( 6.70411735934e+12 )*normSS;
      if (n_m1m2== 5) return ( 64604031138.3 )*normSS;
      if (n_m1m2== 6) return ( 442665652919.0 )*normSS;
      if (n_m1m2== 7) return ( 64604031138.3 )*normSS;
      if (n_m1m2== 8) return ( 142850125.595 )*normSS;

    }
  else if (indx==14 )
    {
      TComplex Keven = CAss*TComplex::Conjugate(CA0);

      if (n_m1m2== 0) return (Keven.Re()*( -3.41906268539e+13 ) + Keven.Im()*( 4.02596953195e+13 ))*norm_int_ss;
      if (n_m1m2== 1) return (Keven.Re()*( -2.34994258568e+13 ) + Keven.Im()*( -5.12023642031e+12 ))*norm_int_ss;
      if (n_m1m2== 2) return (Keven.Re()*( 4.58589598864e+12 ) + Keven.Im()*( -1.5285158297e+13 ))*norm_int_ss;
      if (n_m1m2== 3) return (Keven.Re()*( -2.34994258568e+13 ) + Keven.Im()*( -5.12023642031e+12 ))*norm_int_ss;
      if (n_m1m2== 4) return (Keven.Re()*( -2.97354595364e+12 ) + Keven.Im()*( -1.05412766539e+13 ))*norm_int_ss;
      if (n_m1m2== 5) return (Keven.Re()*( 7.12533085688e+12 ) + Keven.Im()*( -1.43014252947e+12 ))*norm_int_ss;
      if (n_m1m2== 6) return (Keven.Re()*( 4.58589598864e+12 ) + Keven.Im()*( -1.5285158297e+13 ))*norm_int_ss;
      if (n_m1m2== 7) return (Keven.Re()*( 7.12533085688e+12 ) + Keven.Im()*( -1.43014252947e+12 ))*norm_int_ss;
      if (n_m1m2== 8) return (Keven.Re()*( 583054763372.0 ) + Keven.Im()*( 4.78654147953e+12 ))*norm_int_ss;
      
    }
  else if ( indx==15)
    {
      TComplex Keven = CAss*TComplex::Conjugate(CApa);

      if (n_m1m2== 0) return (Keven.Re()*( -3.41906268539e+13 ) + Keven.Im()*( 4.02596953195e+13 ))*norm_int_ss;
      if (n_m1m2== 1) return (Keven.Re()*( -2.34994258568e+13 ) + Keven.Im()*( -5.12023642031e+12 ))*norm_int_ss;
      if (n_m1m2== 2) return (Keven.Re()*( 4.58589598864e+12 ) + Keven.Im()*( -1.5285158297e+13 ))*norm_int_ss;
      if (n_m1m2== 3) return (Keven.Re()*( -2.34994258568e+13 ) + Keven.Im()*( -5.12023642031e+12 ))*norm_int_ss;
      if (n_m1m2== 4) return (Keven.Re()*( -2.97354595364e+12 ) + Keven.Im()*( -1.05412766539e+13 ))*norm_int_ss;
      if (n_m1m2== 5) return (Keven.Re()*( 7.12533085688e+12 ) + Keven.Im()*( -1.43014252947e+12 ))*norm_int_ss;
      if (n_m1m2== 6) return (Keven.Re()*( 4.58589598864e+12 ) + Keven.Im()*( -1.5285158297e+13 ))*norm_int_ss;
      if (n_m1m2== 7) return (Keven.Re()*( 7.12533085688e+12 ) + Keven.Im()*( -1.43014252947e+12 ))*norm_int_ss;
      if (n_m1m2== 8) return (Keven.Re()*( 583054763372.0 ) + Keven.Im()*( 4.78654147953e+12 ))*norm_int_ss;
      
    }
  else
    {
      cout << "No massterm integral selected. Return 0"<<endl;
      return 0;
    }

  
  
  return 0.;
  
}
