#include <math.h>
#include <complex>

Double_t get_q( Double_t M, Double_t m1, Double_t m2) // given the mass of the mother and the daughters, calculates the momentum of the daughters in mother's rest frame
{
  Double_t M2 = M*M;
  Double_t m12 = m1*m1;
  Double_t m22 = m2*m2;
  Double_t q2 = .25*( M2*M2 - 2*M2*(m12+m22) +(m12*m12+m22*m22)-2*m12*m22) /M2;
  if (q2<0) {return 0.;}

  return sqrt(q2);
}

Double_t Blatt_Weisskopf(Double_t q, Double_t q0, Int_t L = 1) //Blatt-Weisskpof factor **squared**
{
  if (L<1.) return 1.;
  
  Double_t d = 3.e-03/L;/// this is true for L = 1,2. No clue for the rest!!!!!.
  Double_t z = q*d*q*d;
  Double_t z0 = q0*d*q0*d;
  if (L==1) return (1+z0)/(1+z);
  if (L==2) return ((z0-3)*(z0-3) + 9*z0) / ((z-3)*(z-3) + 9*z);
  if (L==3) return (z0*(z0-15)*(z0-15) + 9*(z0-5)) / (z*(z-15)*(z-15) + 9*(z-5));
  return ( pow(z0*z0 -45*z0+105,2) +25*z0*(2*z0-21)*(2*z0-21)) /(pow(z*z -45*z+105,2) +25*z*(2*z-21)*(2*z-21));
}
Double_t Blatt_Weisskopf_fM(Double_t M, Int_t L = 1, Double_t m1=139.57018,Double_t m2=493.677,Double_t M0=895.94) 
{
  Double_t q = get_q(M,m1,m2);
  Double_t q0 = get_q(M0,m1,m2);
  return Blatt_Weisskopf(q,q0,L);
}



std::complex<Double_t> BW_T(Double_t M, Double_t M0, Double_t Gamma0, Double_t m1, Double_t m2,  Double_t J) {  
  // BW amplitude (i.e, not quared), to use for interferences. 
  // Gamma is phase space dependent
  // Uses Blatt-Weiskopff barrier factors from PDG
  // M : mass of the pair, M0: nominal mass of the resonance, Gamma0: nominal width of the resonance, ,
  // m1: mass of one of the PSEUDOSCALAR daughters, m2: mass of the other PSEUDOSCALAR daughter, 
  // J angular momentum quantum number of the resonance

  
  Double_t q = get_q(M,m1,m2);
  Double_t q0 = get_q(M0,m1,m2);

  Double_t Gamma = Gamma0*pow(q/q0,2*J+1)*M0/M*Blatt_Weisskopf(q,q0,J);

  std::complex<Double_t> denom(M*M-M0*M0,-Gamma*M0);
  std::complex<Double_t> num(1.,0.);

  //Double_t nu = TMath::Sqrt(mass0*mass0*(mass0*mass0+Gamma*Gamma));
  //std::complex<Double_t> k(TMath::Sqrt(2.*TMath::Sqrt(2.)*mass0*Gamma*nu/TMath::Pi()/TMath::Sqrt(mass0*mass0+nu)),0.);

  return num/denom;

}

Double_t get_K(Double_t M, Double_t M0, Double_t Gamma0, Double_t m1, Double_t m2,  Int_t J = 1){

  Double_t q = get_q(M,m1,m2);
  Double_t q0 = get_q(M0,m1,m2);
  Double_t Gamma = Gamma0*pow(q/q0,2*J+1)*M0/M*Blatt_Weisskopf(q,q0,J);

  return M0*Gamma/(M0*M0-M*M); 

}

Double_t get_K_hat(Double_t M, Double_t M0, Double_t Gamma0, Double_t m1, Double_t m2,  Int_t J = 1){

  //Double_t q = get_q(M,m1,m2);
  //Double_t q0 = get_q(M0,m1,m2);
  //Double_t Gamma = Gamma0*pow(q/q0,2*J+1)*M0/M*Blatt_Weisskopf(q,q0,J);

  return sqrt(M0*Gamma0)/(M0*M0-M*M); 

}
std::complex<Double_t> Single_K(Double_t M, Double_t M0, Double_t Gamma0, Double_t m1, Double_t m2,  Int_t J = 1) {  
  // BW-like amplitude (i.e, not quared), to use for interferences. 
  // Gamma is phase space dependent
  // Uses Blatt-Weiskopff barrier factors from PDG
  // M : mass of the pair, M0: nominal mass of the resonance, Gamma0: nominal width of the resonance, ,
  // m1: mass of one of the PSEUDOSCALAR daughters, m2: mass of the other PSEUDOSCALAR daughter, 
  // J angular momentum quantum number of the resonance

  std::complex<Double_t> K(get_K(M,M0,Gamma0,m1,m2,J),0.);
  std::complex<Double_t> i(0,1);
  std::complex<Double_t> one(1,0);
  //std::complex<Double_t> denom(1.,-K);
  return K/(one-i*K);
}

std::complex<Double_t> Double_K(Double_t M, Double_t M0, Double_t Gamma0,Double_t M1, Double_t Gamma1, Double_t m1, Double_t m2,  std::complex<Double_t> c1,  Int_t J = 1) {  
  // 2 BW-like amplitudes (i.e, not quared), to use for interferences. 
  // Gamma is phase space dependent
  // Uses Blatt-Weiskopff barrier factors from PDG
  // M : mass of the pair, M0: nominal mass of the resonance, Gamma0: nominal width of the resonance, ,
  // m1: mass of one of the PSEUDOSCALAR daughters, m2: mass of the other PSEUDOSCALAR daughter, 
  // J angular momentum quantum number of the resonance

  std::complex<Double_t> K1(get_K(M,M1,Gamma1,m1,m2,J),0);
  std::complex<Double_t> K0(get_K(M,M0,Gamma0,m1,m2,J),0);
  std::complex<Double_t> K = K0 + c1*K1;
  std::complex<Double_t> i(0,1);
  std::complex<Double_t> one(1,0);
  //std::complex<Double_t> denom(1.,-K);
  return K/(one-i*K);
  

}

std::complex<Double_t> Double_K_wF(Double_t M, Double_t M0, Double_t Gamma0,Double_t M1, Double_t Gamma1, Double_t m1, Double_t m2,  std::complex<Double_t> c1,  Int_t J = 1) {  
  // 2 BW-like amplitudes (i.e, not quared), to use for interferences. 
  // Gamma is phase space dependent
  // Uses Blatt-Weiskopff barrier factors from PDG
  // M : mass of the pair, M0: nominal mass of the resonance, Gamma0: nominal width of the resonance, ,
  // m1: mass of one of the PSEUDOSCALAR daughters, m2: mass of the other PSEUDOSCALAR daughter, 
  // J angular momentum quantum number of the resonance

  std::complex<Double_t> K1(get_K(M,M1,Gamma1,m1,m2,J),0);
  std::complex<Double_t> K0(get_K(M,M0,Gamma0,m1,m2,J),0);
  std::complex<Double_t> K = K0 + c1*K1;
  std::complex<Double_t> i(0,1);
  std::complex<Double_t> one(1,0);
  //std::complex<Double_t> denom(1.,-K);
  return K/(one-i*(K0+K1));
  

}



Double_t T2_Double_K_old(Double_t M, Double_t M0, Double_t Gamma0,Double_t M1, Double_t Gamma1, Double_t m1, Double_t m2, Double_t c1,  Int_t J = 1) {  
  // 2 BW-like amplitudes (i.e, not quared), to use for interferences. Amplitude squared
  // Gamma is phase space dependent
  // Uses Blatt-Weiskopff barrier factors from PDG
  // M : mass of the pair, M0: nominal mass of the resonance, Gamma0: nominal width of the resonance, ,
  // m1: mass of one of the PSEUDOSCALAR daughters, m2: mass of the other PSEUDOSCALAR daughter, 
  // J angular momentum quantum number of the resonance
  Double_t K0 = get_K(M,M0,Gamma0,m1,m2,J);
  Double_t K1 = get_K(M,M1,Gamma1,m1,m2,J);
  
  Double_t K02 = K0*K0;
  Double_t BW1 = K02/(1+K02);
  Double_t delta = K1*K1 + 2*K0*K1;
  Double_t q = get_q(M,m1,m2);
  Double_t q0 = get_q(M0,m1,m2);

  return (BW1 + c1*delta/(1+K02)/(1+delta+K02))*M/pow(q,2*J+1)/Blatt_Weisskopf(q,q0,J); //substractiong one p. space. Check if this is crap.
}

Double_t T2_Double_K(Double_t M, Double_t M0, Double_t Gamma0,Double_t M1, Double_t Gamma1, Double_t m1, Double_t m2, std::complex<Double_t> c,  Int_t J = 1) {  
  // 2 BW-like amplitudes (i.e, not quared), to use for interferences. Returns the amplitude squared
  // Gamma is phase space dependent
  // Uses Blatt-Weiskopff barrier factors from PDG
  // M : mass of the pair, M0: nominal mass of the resonance, Gamma0: nominal width of the resonance, ,
  // m1: mass of one of the PSEUDOSCALAR daughters, m2: mass of the other PSEUDOSCALAR daughter, 
  // J angular momentum quantum number of the resonance
  Double_t K0 = get_K(M,M0,Gamma0,m1,m2,J);
  Double_t K1 = get_K(M,M1,Gamma1,m1,m2,J);
  Double_t c1 = real(c);
  Double_t c2 = imag(c);
  Double_t K02 = K0*K0;
  Double_t K12 = K1*K1;
  Double_t eps = 2*K0*K1;

  Double_t BW0 = K02/(1+K02);
  Double_t BW1 = K12/(1+K12);
  Double_t q = get_q(M,m1,m2);
  Double_t q0 = get_q(M0,m1,m2);

  return (BW0 + c1*BW1 + c2 * (eps-K02*K12*(2+pow(K0+K1,2)))/(1+K02)/(1+K02+K12+eps)/(1+K12)  )*M/pow(q,2*J+1)/Blatt_Weisskopf(q,q0,J); //substractiong one p. space. Check if this is crap.

}



std::complex<Double_t> T_ResonancePlusNonR_K(Double_t M, Double_t M0, Double_t Gamma0, Double_t m1, Double_t m2, std::complex<Double_t> c,  Int_t J = 1) {  
  // BW-like amplitude + complex copnstant  to use for interferences. Note that according to Chung, c must be real. However we keep it as complex in case one wants to play.
  // Gamma is phase space dependent
  // Uses Blatt-Weiskopff barrier factors from PDG
  // M : mass of the pair, M0: nominal mass of the resonance, Gamma0: nominal width of the resonance, ,
  // m1: mass of one of the PSEUDOSCALAR daughters, m2: mass of the other PSEUDOSCALAR daughter, 
  // J angular momentum quantum number of the resonance
  //Double_t q = get_q(M,m1,m2);
  std::complex<Double_t> K0(get_K(M,M0,Gamma0,m1,m2,J),0.);
  std::complex<Double_t> K = K0 + c;//*sqrt(pow(q,2*J+1)/M);
  
  //  Double_t q0 = get_q(M0,m1,m2);

  std::complex<Double_t> i(0,1);
  std::complex<Double_t> one(1,0);
  return K/(one-i*K);
}



int BWtools() {return 1;}

