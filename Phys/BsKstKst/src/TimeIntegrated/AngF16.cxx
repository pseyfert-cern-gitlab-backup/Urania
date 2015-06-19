/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "AngF16.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(AngF16) 



 Double_t AngF16::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
   Double_t c1_2 = c1*c1;
   Double_t c2_2 = c2*c2;
   Double_t s1_2 = 1.-c1_2;
   Double_t s2_2 = 1.-c2_2;
   Double_t s12s22 = s1_2*s2_2;
   Double_t s1s2 = sqrt(s12s22);

   Double_t coefsTH[5];
   Double_t coefsPH[5];

   getAccTHCoefs(coefsTH);
   getAccPHCoefs(coefsPH);

   Double_t c1_th = coefsTH[0];
   Double_t c2_th = coefsTH[1];
   Double_t c3_th = coefsTH[2];
   Double_t c4_th = coefsTH[3];
   Double_t c5_th = coefsTH[4];

   Double_t c1_ph = coefsPH[0];
   Double_t c2_ph = coefsPH[1];
   Double_t c3_ph = coefsPH[2];

   Double_t acc_th1 = 1. + c1_th*c1 + c2_th*c1_2 + c3_th*c1_2*c1 + c4_th*c1_2*c1_2 + c5_th*c1_2*c1_2*c1;
   Double_t acc_th2 = 1. + c1_th*c2 + c2_th*c2_2 + c3_th*c2_2*c2 + c4_th*c2_2*c2_2 + c5_th*c2_2*c2_2*c2;
   Double_t acc_phi = 1. + c1_ph*cos( c2_ph*ph + c3_ph);

   Double_t acc_val = acc_th1*acc_th2*acc_phi;
   if (acc_val<0){
     return 0.00001;
   }

   return  4*sqrt(2)*s1s2*sin(ph)/3*acc_val;
 } 





Double_t AngF16::analyticalIntegral(Int_t code, const char* rangeName) const

 { 
   // RETURN ANALYTICAL INTEGRAL DEFINED BY RETURN CODE ASSIGNED BY getAnalyticalIntegral
   // THE MEMBER FUNCTION x.min(rangeName) AND x.max(rangeName) WILL RETURN THE INTEGRATION
   // BOUNDARIES FOR EACH OBSERVABLE x

   // assert(code==1) ; 
   // return (x.max(rangeName)-x.min(rangeName)) ; 
   Double_t c1_2 = c1*c1;
   Double_t c2_2 = c2*c2;

   Double_t coefsTH[5];
   Double_t coefsPH[5];

   getAccTHCoefs(coefsTH);
   getAccPHCoefs(coefsPH);

   Double_t c1_th = coefsTH[0];
   Double_t c2_th = coefsTH[1];
   Double_t c3_th = coefsTH[2];
   Double_t c4_th = coefsTH[3];
   Double_t c5_th = coefsTH[4];

   Double_t c1_ph = coefsPH[0];
   Double_t c2_ph = coefsPH[1];
   Double_t c3_ph = coefsPH[2];

   Double_t acc_th1 = 1. + c1_th*c1 + c2_th*c1_2 + c3_th*c1_2*c1 + c4_th*c1_2*c1_2 + c5_th*c1_2*c1_2*c1;
   Double_t acc_th2 = 1. + c1_th*c2 + c2_th*c2_2 + c3_th*c2_2*c2 + c4_th*c2_2*c2_2 + c5_th*c2_2*c2_2*c2;
   Double_t acc_ph = 1. + c1_ph*cos( c2_ph*ph + c3_ph);

   double ic1;
   if (code==1 || code==2 || code==3 || code==5){

     Double_t hic1 = c1.max(rangeName);
     Double_t loc1 = c1.min(rangeName);

     double x1 = (sqrt(1 - pow(hic1,2))*(-16*(35*c1_th + 14*c3_th + 8*c5_th) - 105*(-8 + 2*c2_th + c4_th)*hic1 + 16*(35*c1_th - 7*c3_th - 4*c5_th)*pow(hic1,2) + 70*(6*c2_th - c4_th)*pow(hic1,3) + 48*(7*c3_th - c5_th)*pow(hic1,4) + 280*c4_th*pow(hic1,5) + 240*c5_th*pow(hic1,6)))/1680. + (1/16.)*(8 + 2*c2_th + c4_th)*asin(hic1);
     double y1 = (sqrt(1 - pow(loc1,2))*(-16*(35*c1_th + 14*c3_th + 8*c5_th) - 105*(-8 + 2*c2_th + c4_th)*loc1 + 16*(35*c1_th - 7*c3_th - 4*c5_th)*pow(loc1,2) + 70*(6*c2_th - c4_th)*pow(loc1,3) + 48*(7*c3_th - c5_th)*pow(loc1,4) + 280*c4_th*pow(loc1,5) + 240*c5_th*pow(loc1,6)))/1680. + (1/16.)*(8 + 2*c2_th + c4_th)*asin(loc1);
     

     ic1 = x1-y1;

   }else {
     double s1_2 = 1.-c1_2;
     double s1 = sqrt(s1_2);

     ic1 = s1*acc_th1;
   }


   double ic2;
   if (code==1 || code==2 || code==4 || code==6){

     Double_t hic2 = c2.max(rangeName);
     Double_t loc2 = c2.min(rangeName);

     double x2 = (sqrt(1 - pow(hic2,2))*(-16*(35*c1_th + 14*c3_th + 8*c5_th) - 105*(-8 + 2*c2_th + c4_th)*hic2 + 16*(35*c1_th - 7*c3_th - 4*c5_th)*pow(hic2,2) + 70*(6*c2_th - c4_th)*pow(hic2,3) + 48*(7*c3_th - c5_th)*pow(hic2,4) + 280*c4_th*pow(hic2,5) + 240*c5_th*pow(hic2,6)))/1680. + (1/16.)*(8 + 2*c2_th + c4_th)*asin(hic2);
     double y2 = (sqrt(1 - pow(loc2,2))*(-16*(35*c1_th + 14*c3_th + 8*c5_th) - 105*(-8 + 2*c2_th + c4_th)*loc2 + 16*(35*c1_th - 7*c3_th - 4*c5_th)*pow(loc2,2) + 70*(6*c2_th - c4_th)*pow(loc2,3) + 48*(7*c3_th - c5_th)*pow(loc2,4) + 280*c4_th*pow(loc2,5) + 240*c5_th*pow(loc2,6)))/1680. + (1/16.)*(8 + 2*c2_th + c4_th)*asin(loc2);
     
     ic2 = x2-y2;

   }else{

     double s2_2 = 1.-c2_2;
     double s2 = sqrt(s2_2);
     
     ic2 = s2*acc_th2;
   }



   double iph;
   if (code==1 || code==3 || code==4 || code==7 ){

     Double_t hiph = ph.max(rangeName);
     Double_t loph = ph.min(rangeName);

     Double_t x3 = -cos(hiph) + c1_ph*cos(c3_ph + (c2_ph-1.)*hiph)/(2*(c2_ph-1.)) - c1_ph*cos(c3_ph + (c2_ph+1.)*hiph)/(2*(c2_ph+1.));
     Double_t y3 = -cos(loph) + c1_ph*cos(c3_ph + (c2_ph-1.)*loph)/(2*(c2_ph-1.)) - c1_ph*cos(c3_ph + (c2_ph+1.)*loph)/(2*(c2_ph+1.));

     iph = x3-y3;
     

   }else{

     iph = sin(ph)*acc_ph;
   }


   return 4*sqrt(2)*ic1*ic2*iph/3;

 }
