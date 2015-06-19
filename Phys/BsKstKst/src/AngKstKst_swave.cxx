/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "AngKstKst_swave.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(AngKstKst_swave) 

 AngKstKst_swave::AngKstKst_swave(const char *name, const char *title, 
                        RooAbsReal& _c1,
                        RooAbsReal& _c2,
                        RooAbsReal& _ph,
                        RooAbsReal& _A0,
                        RooAbsReal& _Apa,
                        RooAbsReal& _Ape,
                        RooAbsReal& _As,
                        RooAbsReal& _dpa,
                        RooAbsReal& _ds,
                        RooAbsReal& _DGs,
                        RooAbsReal& _Gs,
                        RooAbsReal& _th_1,
                        RooAbsReal& _th_2,
                        RooAbsReal& _th_3,
                        RooAbsReal& _th_4,
                        RooAbsReal& _th_5,
                        RooAbsReal& _ph_1,
                        RooAbsReal& _ph_2,
                        RooAbsReal& _ph_3,
                        RooAbsReal& _ph_4,
                        RooAbsReal& _ph_5,
                        RooAbsReal& _ph_6) :
   RooAbsPdf(name,title), 
   c1("c1","c1",this,_c1),
   c2("c2","c2",this,_c2),
   ph("ph","ph",this,_ph),
   A0("A0","A0",this,_A0),
   Apa("Apa","Apa",this,_Apa),
   Ape("Ape","Ape",this,_Ape),
   As("As","As",this,_As),
   dpa("dpa","dpa",this,_dpa),
   ds("ds","ds",this,_ds),
   DGs("DGs","DGs",this,_DGs),
   Gs("Gs","Gs",this,_Gs),
   th_1("th_1","th_1",this,_th_1),
   th_2("th_2","th_2",this,_th_2),
   th_3("th_3","th_3",this,_th_3),
   th_4("th_4","th_4",this,_th_4),
   th_5("th_5","th_5",this,_th_5),
   ph_1("ph_1","ph_1",this,_ph_1),
   ph_2("ph_2","ph_2",this,_ph_2),
   ph_3("ph_3","ph_3",this,_ph_3),
   ph_4("ph_4","ph_4",this,_ph_4),
   ph_5("ph_5","ph_5",this,_ph_5),
   ph_6("ph_6","ph_6",this,_ph_6)
 { 
 } 


 AngKstKst_swave::AngKstKst_swave(const AngKstKst_swave& other, const char* name) :  
   RooAbsPdf(other,name), 
   c1("c1",this,other.c1),
   c2("c2",this,other.c2),
   ph("ph",this,other.ph),
   A0("A0",this,other.A0),
   Apa("Apa",this,other.Apa),
   Ape("Ape",this,other.Ape),
   As("As",this,other.As),
   dpa("dpa",this,other.dpa),
   ds("ds",this,other.ds),
   DGs("DGs",this,other.DGs),
   Gs("Gs",this,other.Gs),
   th_1("th_1",this,other.th_1),
   th_2("th_2",this,other.th_2),
   th_3("th_3",this,other.th_3),
   th_4("th_4",this,other.th_4),
   th_5("th_5",this,other.th_5),
   ph_1("ph_1",this,other.ph_1),
   ph_2("ph_2",this,other.ph_2),
   ph_3("ph_3",this,other.ph_3),
   ph_4("ph_4",this,other.ph_4),
   ph_5("ph_5",this,other.ph_5),
   ph_6("ph_6",this,other.ph_6)
 { 
 } 



 Double_t AngKstKst_swave::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
   return 1. ; 
 } 



