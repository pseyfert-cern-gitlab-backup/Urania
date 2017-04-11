/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "TransF3.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(TransF3) 



 TransF3::TransF3(const TransF3& other, const char* name) :  
   RooAbsReal(other,name), 
   m_useX(other.m_useX),
   CPsi("CPsi",this,other.CPsi),
   CTheta("CTheta",this,other.CTheta),
   Phi("Phi",this,other.Phi),
   X("X",this,other.X)
 { 
 } 



 Double_t TransF3::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
   Double_t CPsi2 = CPsi*CPsi;
   Double_t SPsi2 = 1 - CPsi2;
   Double_t SPsi = sqrt(SPsi2);
   Double_t CTheta2 = CTheta*CTheta;
   Double_t STheta2 = 1-CTheta2;
   Double_t CPhi = cos(Phi);
   Double_t SPhi = sin(Phi);
   Double_t CPhi2 = CPhi*CPhi;
   Double_t SPhi2 = SPhi*SPhi;

   return SPsi2*STheta2; 
 } 



 Int_t TransF3::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const  
 { 
   // LIST HERE OVER WHICH VARIABLES ANALYTICAL INTEGRATION IS SUPPORTED, 
   // ASSIGN A NUMERIC CODE FOR EACH SUPPORTED (SET OF) PARAMETERS 
   // THE EXAMPLE BELOW ASSIGNS CODE 1 TO INTEGRATION OVER VARIABLE X
   // YOU CAN ALSO IMPLEMENT MORE THAN ONE ANALYTICAL INTEGRAL BY REPEATING THE matchArgs 
   // EXPRESSION MULTIPLE TIMES

   // if (matchArgs(allVars,analVars,x)) return 1 ; 
   if (matchArgs(allVars,analVars,CPsi,CTheta,Phi)) return 4 ;
   if (matchArgs(allVars,analVars,CPsi,CTheta    )) return 2 ;
   if (matchArgs(allVars,analVars,CPsi,       Phi)) return 3 ;
   if (matchArgs(allVars,analVars,     CTheta,Phi)) return 6 ;
   if (matchArgs(allVars,analVars,CPsi           )) return 1 ;
   if (matchArgs(allVars,analVars,     CTheta    )) return 5 ;
   if (matchArgs(allVars,analVars,            Phi)) return 7 ;
   
   return 0 ; 
 } 



 Double_t TransF3::analyticalIntegral(Int_t code, const char* range) const  
 { 
   // RETURN ANALYTICAL INTEGRAL DEFINED BY RETURN CODE ASSIGNED BY getAnalyticalIntegral
   // THE MEMBER FUNCTION x.min(rangeName) AND x.max(rangeName) WILL RETURN THE INTEGRATION
   // BOUNDARIES FOR EACH OBSERVABLE x

   // assert(code==1) ; 
   // return (x.max(rangeName)-x.min(rangeName)) ; 

//    cout << "TransF3" << endl;
//    cout << "Integral Codigo: "<< code << endl;
//    cout << "UseX is:  " << m_useX<< endl;
//    cout << "X is: "<< X << endl;

   if(useX()) return X;

   double p1;
   if (code>0 && code<5) {
     double hi = CPsi.max(range);
     double lo = CPsi.min(range);
     double p0 = pow(hi,3)-pow(lo,3); p0/=3;    // integral of cos^2 psi
     p1 = hi-lo-p0;                             // integral of sin^2 psi
   } else {
     double p0 = CPsi;
     p1 = 1-p0*p0;
        }
   double ist2;
   if ((code>3 && code<7) || code==2) {
     double hi = CTheta.max(range);
     double lo = CTheta.min(range);
     double it = hi-lo;                               // integral of 1
     double ict2 = pow(hi,3)-pow(lo,3); ict2/=3;      // integral of cos^2 theta
     ist2 = it-ict2;                                  // integral of sin^2 theta 
   } else {
     double ct = CTheta;
     ist2 = 1-ct*ct;
   }
   double ip;
   if (code==3 || code==4 || code==6 || code==7) {
     ip = Phi.max(range)-Phi.min(range);
   } else {
     ip = 1;
   }
   return p1 * ist2*ip;
   
 } 


