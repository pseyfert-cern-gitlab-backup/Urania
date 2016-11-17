/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "AngF4.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(AngF4) 

 Double_t AngF4::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 

   Double_t c1_2 = c1*c1;
   Double_t c2_2 = c2*c2;
   Double_t s1_2 = 1.-c1_2;
   Double_t s2_2 = 1.-c2_2;
   Double_t s12s22 = s1_2*s2_2;
   Double_t s1s2 = sqrt(s12s22);

   Double_t acc_val = getAcceptance();

   return -2.*s1_2*s2_2*sin(2*ph)*acc_val ; 



 } 



Double_t AngF4::integrateBin(Int_t code, double loc1, double hic1, double loc2, double hic2, double loph, double hiph)const
 { 
   // RETURN ANALYTICAL INTEGRAL DEFINED BY RETURN CODE ASSIGNED BY getAnalyticalIntegral
   // THE MEMBER FUNCTION x.min(rangeName) AND x.max(rangeName) WILL RETURN THE INTEGRATION
   // BOUNDARIES FOR EACH OBSERVABLE x

   // assert(code==1) ; 
   // return (x.max(rangeName)-x.min(rangeName)) ; 


   double ic1;
   if (code==1 || code==2 || code==3 || code==5){

     double x1 = hic1 - pow(hic1,3)/3.;
     double y1 = loc1 - pow(loc1,3)/3.;

     ic1 = x1-y1;

   }else {
     ic1 = 1-c1*c1;
   }


   double ic2;
   if (code==1 || code==2 || code==4 || code==6){


     double x2 = hic2 - pow(hic2,3)/3.;
     double y2 = loc2 - pow(loc2,3)/3.;

     ic2 = x2-y2;
     
   }else{

     ic2 = 1-c2*c2;
   }


   double iph;
   if (code==1 || code==3 || code==4 || code==7 ){


     double x3 =  - cos(2*hiph)/2;
     double y3 =  - cos(2*loph)/2;

     iph = x3-y3;
   }else{

     iph = sin(2*ph);
   }


   return -2.*ic1*ic2*iph;

 } 


