/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "MassK7_int.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 
#include "TComplex.h"

ClassImp(MassK7_int) 

 Double_t MassK7_int::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 

   TComplex CAf(Af,df,1);
   TComplex CAg(Ag,dg,1);

//    TComplex CAs=(CAf+CAg)/sqrt(2);
//    TComplex CAsp=(CAf-CAg)/sqrt(2);

   Double_t GL = Gs + DGs/2.;
   Double_t GH = Gs - DGs/2.;


   //********* P-wave mass
   
   TComplex PW_m1 = PWaveMass(1);
   TComplex PW_m2 = PWaveMass(2);

   //********* S-wave mass

   TComplex SW_m1 = SWaveMass(1);
   TComplex SW_m2 = SWaveMass(2);

//    TComplex K7int = TComplex::Conjugate(CAs*PW_m1*SW_m2)*CAsp*SW_m1*PW_m2;
//    TComplex K7int = (TComplex::Conjugate(CAs*PW_m1*SW_m2)*CAsp*SW_m1*PW_m2 + TComplex::Conjugate(CAsp*PW_m1*SW_m2)*CAs*SW_m1*PW_m2)/2.;

   TComplex K7int = (CAf.Rho2()/GH - CAg.Rho2()/GL)/2.*TComplex::Conjugate(PW_m1*SW_m2)*SW_m1*PW_m2;

   Double_t acc = getAcc();

   Double_t Q_kst = sqrt((m1*m1 - pow(m_kaon+m_pion,2))*(m1*m1 - pow(m_kaon-m_pion,2)))/(2*m1);
   Double_t Q_kstb = sqrt((m2*m2 - pow(m_kaon+m_pion,2))*(m2*m2 - pow(m_kaon-m_pion,2)))/(2*m2);
   Double_t Q_B = sqrt((m_Bs*m_Bs - pow(m1+m2,2))*(m_Bs*m_Bs - pow(m1-m2,2)))/(2*m_Bs);
   Double_t phasespace = Q_kst * Q_kstb * Q_B;



   return K7int.Re() * acc *norm*phasespace; 
//    return K7int.Re() * acc *norm; 
 } 


