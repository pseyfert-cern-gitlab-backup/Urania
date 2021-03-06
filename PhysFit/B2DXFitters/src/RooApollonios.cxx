/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "B2DXFitters/RooApollonios.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(RooApollonios) 

 RooApollonios::RooApollonios(const char *name, const char *title, 
                        RooAbsReal& _m,
                        RooAbsReal& _m0,
                        RooAbsReal& _sigma,
                        RooAbsReal& _b,
                        RooAbsReal& _a,
                        RooAbsReal& _n) :
   RooAbsPdf(name,title), 
   m("m","m",this,_m),
   m0("m0","m0",this,_m0),
   sigma("sigma","sigma",this,_sigma),
   b("b","b",this,_b),
   a("a","a",this,_a),
   n("n","n",this,_n)
 { 
 } 


 RooApollonios::RooApollonios(const RooApollonios& other, const char* name) :  
   RooAbsPdf(other,name), 
   m("m",this,other.m),
   m0("m0",this,other.m0),
   sigma("sigma",this,other.sigma),
   b("b",this,other.b),
   a("a",this,other.a),
   n("n",this,other.n)
 { 
 } 



 Double_t RooApollonios::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
   //return 1.0 ; 
   Double_t xi = (m-m0)/sigma;
   Double_t xi2 = xi*xi;
   if (xi > -a) {return exp(-b*sqrt(1+ xi2));}
   Double_t a2 = a*a;
  
   Double_t B =  -1.*(a - n*sqrt(1+a2)/(b*a));
   //Double_t A = 
   Double_t A = exp(-b*sqrt(1+a2)) *pow(B+a,n);
   return A*pow(B-xi,-n);
 } 



