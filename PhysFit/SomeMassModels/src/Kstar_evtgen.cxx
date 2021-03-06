/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "Kstar_evtgen.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

#include <vector>
using std::vector;

#include <iostream>
using std::ios;
#include <fstream>
#include <iomanip>
#include <sstream>

#include <complex>
#include "BWtools.C"


ClassImp(Kstar_evtgen) 

 Kstar_evtgen::Kstar_evtgen(const char *name, const char *title, 
                        RooAbsReal& _m,
                        RooAbsReal& _m0,
                        RooAbsReal& _g0,
                        RooAbsReal& _mDa,
                        RooAbsReal& _mDb,
                        RooAbsReal& _J,
                        RooAbsReal& _MB,
                        RooAbsReal& _MV,
                        RooAbsReal& _l) :
   RooAbsPdf(name,title), 
   m("m","m",this,_m),
   m0("m0","m0",this,_m0),
   g0("g0","g0",this,_g0),
   mDa("mDa","mDa",this,_mDa),
   mDb("mDb","mDb",this,_mDb),
   J("J","J",this,_J),
   MB("MB","MB",this,_MB),
   MV("MV","MV",this,_MV),
   l("l","l",this,_l)
 { 
 } 


 Kstar_evtgen::Kstar_evtgen(const Kstar_evtgen& other, const char* name) :  
   RooAbsPdf(other,name), 
   m("m",this,other.m),
   m0("m0",this,other.m0),
   g0("g0",this,other.g0),
   mDa("mDa",this,other.mDa),
   mDb("mDb",this,other.mDb),
   J("J",this,other.J),
   MB("MB",this,other.MB),
   MV("MV",this,other.MV),
   l("l",this,other.l)
 { 
 } 



 Double_t Kstar_evtgen::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
   
   Double_t K0 = get_K(m,m0,g0,mDa,mDb,J);
   Double_t K0h = get_K_hat(m,m0,g0,mDa,mDb,J);

   Double_t q = get_q(m,mDa,mDb);
   Double_t q0 = get_q(m0,mDa,mDb);
   if (q==0) return 0;
   Double_t rho_decay = pow(q,2*J+1)*Blatt_Weisskopf(q,q0,J);


   Double_t p = get_q(MB,MV,m);
   Double_t p0 = get_q(MB,MV,m0);
   if (p==0) return 0;
   Double_t rho_birth = pow(p,2*l+1)*Blatt_Weisskopf(p,p0,l);

   std::complex<Double_t> num(K0h,0.); 
   std::complex<Double_t> den(1, -(K0)); 
   std::complex<Double_t> T = num/den;
   Double_t  kst1 = real(T*conj(T));

   return kst1 * rho_decay * rho_birth;
 } 



