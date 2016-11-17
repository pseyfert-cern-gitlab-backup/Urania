/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "MassK9.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 
#include "TComplex.h"

ClassImp(MassK9) 



 Double_t MassK9::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 

   TComplex CApa(Apa,dpa,1);
   TComplex CAf(Af,df,1);
   TComplex CAg(Ag,dg,1);

   //********* P-wave mass
   
   TComplex PW_m1 = PWaveMass(1);
   TComplex PW_m2 = PWaveMass(2);

   //********* S-wave mass

   //TComplex SW_m1 = SWaveMass(1);
   TComplex SW_m2 = SWaveMass(2);


   TComplex K9 = CAg/sqrt(2.)*TComplex::Conjugate(CApa*PW_m2)*SW_m2;

   Double_t acc = getAcc();


   Double_t Q_kst = sqrt((m1*m1 - pow(m_kaon+m_pion,2))*(m1*m1 - pow(m_kaon-m_pion,2)))/(2*m1);
   Double_t Q_kstb = sqrt((m2*m2 - pow(m_kaon+m_pion,2))*(m2*m2 - pow(m_kaon-m_pion,2)))/(2*m2);
   Double_t Q_B = sqrt((m_Bs*m_Bs - pow(m1+m2,2))*(m_Bs*m_Bs - pow(m1-m2,2)))/(2*m_Bs);
   Double_t phasespace = Q_kst * Q_kstb * Q_B;



   return norm*PW_m1.Rho2()*K9.Re()*acc*phasespace  ; 
 } 


