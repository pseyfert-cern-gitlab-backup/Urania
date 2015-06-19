/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "Kmatrix_2res.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 
#define MPion 139.57018
#define MKaon 493.667
#define MMuon 105.65836668
#define MJPsi 3096.916

#include <vector>
using std::vector;

#include <iostream>
using std::ios;
#include <fstream>
#include <iomanip>
#include <sstream>

#include <complex>
#include "BWtools.C"



ClassImp(Kmatrix_2res) 

 Kmatrix_2res::Kmatrix_2res(const char *name, const char *title, 
                        RooAbsReal& _m,
                        RooAbsReal& _beta,
                        RooAbsReal& _phase,
                        RooAbsReal& _mlo,
                        RooAbsReal& _mhi,
                        RooAbsReal& _gammalo,
                        RooAbsReal& _gammahi,
                        RooAbsReal& _L,
                        RooAbsReal& _MB,
                        RooAbsReal& _MV) :
   RooAbsPdf(name,title), 
   m("m","m",this,_m),
   beta("beta","beta",this,_beta),
   phase("phase","phase",this,_phase),
   mlo("mlo","mlo",this,_mlo),
   mhi("mhi","mhi",this,_mhi),
   gammalo("gammalo","gammalo",this,_gammalo),
   gammahi("gammahi","gammahi",this,_gammahi),
   L("L","L",this,_L),
   MB("MB","MB",this,_MB),
   MV("MV","MV",this,_MV)
 { 
 } 


 Kmatrix_2res::Kmatrix_2res(const Kmatrix_2res& other, const char* name) :  
   RooAbsPdf(other,name), 
   m("m",this,other.m),
   beta("beta",this,other.beta),
   phase("phase",this,other.phase),
   mlo("mlo",this,other.mlo),
   mhi("mhi",this,other.mhi),
   gammalo("gammalo",this,other.gammalo),
   gammahi("gammahi",this,other.gammahi),
   L("L",this,other.L),
   MB("MB",this,other.MB),
   MV("MV",this,other.MV)
 { 
 } 



 Double_t Kmatrix_2res::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
   //std::complex<Double_t> c1( beta*TMath::Cos(phase),beta*TMath::Sin(phase));


   //std::complex<Double_t> T = Double_K_wF(m,mlo,gammalo,mhi,gammahi,MPion,MKaon,c1, L);

   //Double_t kst1 = T2_Double_K(m,mlo,gammalo,mhi,gammahi,MPion,MKaon,real(c1), L);

   //Double_t  kst1 = real(T*conj(T));
   //kst1 = kst1*pow(get_q(m,MPion,MKaon),2*L+1); //phase space from K* --> Kpi. Check this crap
   //return kst1*get_q(MB,MV,m); /// phase space from B --> X K*

   //   return 1.0 ; 
   Double_t c1 = beta; /// phases ignored for the moment
   Double_t K0 = get_K(m,mlo,gammalo,MPion,MKaon,L);
   Double_t K0h = get_K_hat(m,mlo,gammalo,MPion,MKaon,L);//(;m,m0,g0,mDa,mDb,J);

   Double_t K02 = get_K(m,mhi,gammahi,MPion,MKaon,L);
   Double_t K0h2 = get_K_hat(m,mhi,gammahi,MPion,MKaon,L);//(;m,m0,g0,mDa,mDb,J);
   
   std::complex<Double_t> num((1-c1)*K0h+c1*K0h2,0.);
   std::complex<Double_t> den(1, -((1-c1)*K0 + c1*K02));
   std::complex<Double_t> T = num/den;
   Double_t q = get_q(m,MPion,MKaon);
   //Double_t q0 = get_q(m0,MPion,MKaon);
   if (q==0) return 0;
   //Double_t rho_decay = pow(q,2*J+1)*Blatt_Weisskopf(q,q0,L);

   // Warning: Check all these L's, J's and l's ....
   Double_t p = get_q(MB,MV,m);
   //Double_t p0 = get_q(MB,MV,m0);
   if (p==0) return 0;
   //Int_t l = 0;
   //Double_t rho_birth = pow(p,2*l+1)*Blatt_Weisskopf(p,p0,l);
   Double_t  kst1 = real(T*conj(T));

   return kst1 * p*q;


 } 



