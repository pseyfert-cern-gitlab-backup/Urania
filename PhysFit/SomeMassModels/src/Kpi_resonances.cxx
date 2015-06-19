/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory
 * Author: Diego Martinez Santos, Paula Alvarez Cartelle, Antonio Yanez Santamaria                  * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "Kpi_resonances.h" 
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


ClassImp(TwoBW)
  
  TwoBW::TwoBW(const char *name, const char *title, 
	       RooAbsReal& _m,
	       //RooAbsReal& _alpha,
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
   //alpha("alpha","alpha",this,_alpha),
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


 TwoBW::TwoBW(const TwoBW& other, const char* name) :  
   RooAbsPdf(other,name), 
   m("m",this,other.m),
   //alpha("alpha",this,other.alpha),
   beta("beta",this,other.beta),
   phase("phase",this,other.phase),
   mlo("mlo",this,other.mlo),
   mhi("mhi",this,other.mhi),
   gammalo("gammalo",this,other.gammalo),
   gammahi("gammahi",this,other.gammahi),
   L("L","L",this,other.L),
   MB("MB","MB",this,other.MB),
   MV("MV","MV",this,other.MV)
 { 
 } 



 Double_t TwoBW::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 

   std::complex<Double_t> c1( beta*TMath::Cos(phase),beta*TMath::Sin(phase));
   std::complex<Double_t> T = BW_T(m,mlo,gammalo,MPion,MKaon,1) + c1*BW_T(m,mhi,gammahi,MPion,MKaon, 1);

   Double_t  kst1 = real(T*conj(T));
   kst1 = kst1*pow(get_q(m,MPion,MKaon),2*1+1); //phase space from K* --> Kpi. Check this crap
   return kst1*get_q(5279.,MJPsi,m); /// phase space from B --> X K*

 } 



ClassImp(SingleBW)
  
  SingleBW::SingleBW(const char *name, const char *title, 
	       RooAbsReal& _m,
	       RooAbsReal& _mlo,
	       RooAbsReal& _gammalo, 
	       RooAbsReal& _L,
	       RooAbsReal& _MB,
	       RooAbsReal& _MV) :
   RooAbsPdf(name,title), 
   m("m","m",this,_m),
   mlo("mlo","mlo",this,_mlo),
   gammalo("gammalo","gammalo",this,_gammalo),
   L("L","L",this,_L),
   MB("MB","MB",this,_MB),
   MV("MV","MV",this,_MV)
 { 
 } 


 SingleBW::SingleBW(const SingleBW& other, const char* name) :  
   RooAbsPdf(other,name), 
   m("m",this,other.m),
   mlo("mlo",this,other.mlo),
   gammalo("gammalo",this,other.gammalo),
   L("L","L",this,other.L),
   MB("MB","MB",this,other.MB),
   MV("MV","MV",this,other.MV)
 { 
 } 



 Double_t SingleBW::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 

   std::complex<Double_t> T = BW_T(m,mlo,gammalo,MPion,MKaon,1);// + c1*BW_T(m,mhi,gammahi,MPion,MKaon, L);

   Double_t  kst1 = real(T*conj(T));
   kst1 = kst1*pow(get_q(m,MPion,MKaon),2*1+1); //phase space from K* --> Kpi. Check this crap
   return kst1*get_q(MB,MJPsi,m); /// phase space from B --> X K*
 } 

int Kpi_resonances() {return 1;}
