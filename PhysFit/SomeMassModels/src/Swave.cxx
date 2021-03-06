/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "Swave.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 
#define MPion 139.57018
#define MKaon 493.667

#include <vector>
using std::vector;

#include <iostream>
using std::ios;
#include <fstream>
#include <iomanip>
#include <sstream>

#include <complex>
#include "BWtools.C"


ClassImp(Swave) 

 Swave::Swave(const char *name, const char *title, 
                        RooAbsReal& _m,
                        RooAbsReal& _a,
                        RooAbsReal& _r,
                        RooAbsReal& _M0,
                        RooAbsReal& _gamma,
                        RooAbsReal& _kappa,
                        RooAbsReal& _MB,
                        RooAbsReal& _MV) :
   RooAbsPdf(name,title), 
   m("m","m",this,_m),
   a("a","a",this,_a),
   r("r","r",this,_r),
   M0("M0","M0",this,_M0),
   gamma("gamma","gamma",this,_gamma),
   kappa("kappa","kappa",this,_kappa),
   MB("MB","MB",this,_MB),
   MV("MV","MV",this,_MV)
 { 
 } 


 Swave::Swave(const Swave& other, const char* name) :  
   RooAbsPdf(other,name), 
   m("m",this,other.m),
   a("a",this,other.a),
   r("r",this,other.r),
   M0("M0",this,other.M0),
   gamma("gamma",this,other.gamma),
   kappa("kappa",this,other.kappa),
   MB("MB",this,other.MB),
   MV("MV",this,other.MV)
 { 
 } 



 Double_t Swave::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
   Double_t q = get_q(m,MPion,MKaon);
   //Double_t q0 = get_q(M0,MPion,MKaon);
   if (q<=0.) {return 0.;}
   Double_t cotdB = 1./(a*q) + 0.5*r*q;
   std::complex<Double_t> i(0,1);
   std::complex<Double_t> dB_times2(2*atan(1./cotdB),0.);
   std::complex<Double_t> k(kappa*M0*gamma,0.);
   
   //std::complex<Double_t> T = 1./(cotdB-i)+ k*exp(i*dB_times2)*BW_T(m,M0,gamma,MPion,MKaon,0);
   std::complex<Double_t> T = k*BW_T(m,M0,gamma,MPion,MKaon,0);
   Double_t  kst1 = (real(T*conj(T)) + 1)*q;
  
   //Double_t  kst1 = real(T*conj(T))*q*q/m/m;
   //Double_t  kst1 = real(T*conj(T))*m*m/q;
   
   return kst1*get_q(MB,MV,m); /// phase space from B --> X K*
 
 } 



