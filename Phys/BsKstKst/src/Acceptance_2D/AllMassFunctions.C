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
		      Double_t Af, Double_t df, 
		      Double_t Ag, Double_t dg, 
		      Double_t Ah, Double_t dh, 
		      Double_t Gs, Double_t DGs, 
		      Double_t m_kst, Double_t m_kst0, 
		      Double_t g_kst, Double_t g_kst0 , 
		      Double_t m_Bs, Double_t norm)
{

  TComplex CAf(Af,df,1);
  TComplex CAg(Ag,dg,1);
  TComplex CAh(Ah,dh,1);

  Double_t GL = Gs + DGs/2.;
  Double_t GH = Gs - DGs/2.;

  Double_t massterm = 0;

  TComplex PW_m1 = PWaveMass(m1,m_kst,g_kst);
  TComplex PW_m2 = PWaveMass(m2,m_kst,g_kst);
  TComplex SW_m1 = SWaveMass(m1,m_kst0,g_kst0);
  TComplex SW_m2 = SWaveMass(m2,m_kst0,g_kst0);

  if (indx==1 || indx==2 || indx==3 || indx==5)
    {
//       Double_t PDF_1 = calculatePDF_1D(1,m1,m2,m_kst,g_kst,m_Bs);
//       Double_t PDF_2 = calculatePDF_1D(2,m1,m2,m_kst,g_kst,m_Bs);

//       return PDF_1*PDF_2*norm;
      massterm = PW_m1.Rho2() * PW_m2.Rho2();
    }
  else if (indx==7)
    {
      Double_t K7 = (CAf.Rho2()/GH + CAg.Rho2()/GL)/2.;

      massterm = K7*PW_m1.Rho2()*SW_m2.Rho2();
    }
  else if (indx==8 || indx==9)
    {
      TComplex Keven = CAg/sqrt(2.)*TComplex::Conjugate(CAh*PW_m2)*SW_m2;
      massterm = PW_m1.Rho2()*Keven.Re();
    }
  else if (indx==10)
    {
      TComplex K10 = CAf/sqrt(2.)*TComplex::Conjugate(CAh*PW_m2)*SW_m2;
      massterm = PW_m1.Rho2()*K10.Im()  ;
    }
  else if (indx==11)
    {
      TComplex K11 = CAg*TComplex::Conjugate(CAh*SW_m1)*PW_m1;
      massterm = SW_m2.Rho2()*K11.Re();
    }
  else if (indx==12) //equivalent to MassK7_int
    {
      TComplex K12 = (CAf.Rho2()/GH - CAg.Rho2()/GL)/2.*TComplex::Conjugate(PW_m1*SW_m2)*SW_m1*PW_m2;
      massterm = K12.Re();
    }
  else if (indx==13)
    {
      massterm = SW_m1.Rho2()*SW_m2.Rho2();
    }
  else if (indx==14 || indx==15)
    {
      TComplex Keven = CAf*SW_m1*SW_m2*TComplex::Conjugate(CAg*PW_m1*PW_m2);
      massterm = Keven.Re();
    }
  else
    {
      cout << "No massterm selected. Return 0"<<endl;
      return 0;
    }

  Double_t phasespace = get_phasespace(m1,m2,m_Bs);

  return massterm*phasespace*norm;
}

