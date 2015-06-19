/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by Urania using RooClassFactory               *
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "Testing_sympy.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(Testing_sympy) 

 Testing_sympy::Testing_sympy(const char *name, const char *title, 
                        RooAbsReal& _helcosthetaK,
                        RooAbsReal& _helcosthetaL,
                        RooAbsReal& _helphi,
                        RooAbsReal& _A_pa_mod,
                        RooAbsReal& _A_pe_mod,
                        RooAbsReal& _A_S_mod,
                        RooAbsReal& _A_0_mod,
                        RooAbsReal& _delta_pa,
                        RooAbsReal& _delta_pe,
                        RooAbsReal& _delta_S,
                        RooAbsReal& _c1th,
                        RooAbsReal& _c2th,
                        RooAbsReal& _c3th,
                        RooAbsReal& _c4th,
                        RooAbsReal& _yth) :
   RooAbsPdf(name,title), 
   helcosthetaK("helcosthetaK","helcosthetaK",this,_helcosthetaK),
   helcosthetaL("helcosthetaL","helcosthetaL",this,_helcosthetaL),
   helphi("helphi","helphi",this,_helphi),
   A_pa_mod("A_pa_mod","A_pa_mod",this,_A_pa_mod),
   A_pe_mod("A_pe_mod","A_pe_mod",this,_A_pe_mod),
   A_S_mod("A_S_mod","A_S_mod",this,_A_S_mod),
   A_0_mod("A_0_mod","A_0_mod",this,_A_0_mod),
   delta_pa("delta_pa","delta_pa",this,_delta_pa),
   delta_pe("delta_pe","delta_pe",this,_delta_pe),
   delta_S("delta_S","delta_S",this,_delta_S),
   c1th("c1th","c1th",this,_c1th),
   c2th("c2th","c2th",this,_c2th),
   c3th("c3th","c3th",this,_c3th),
   c4th("c4th","c4th",this,_c4th),
   yth("yth","yth",this,_yth)
 { 
 } 


 Testing_sympy::Testing_sympy(const Testing_sympy& other, const char* name) :  
   RooAbsPdf(other,name), 
   helcosthetaK("helcosthetaK",this,other.helcosthetaK),
   helcosthetaL("helcosthetaL",this,other.helcosthetaL),
   helphi("helphi",this,other.helphi),
   A_pa_mod("A_pa_mod",this,other.A_pa_mod),
   A_pe_mod("A_pe_mod",this,other.A_pe_mod),
   A_S_mod("A_S_mod",this,other.A_S_mod),
   A_0_mod("A_0_mod",this,other.A_0_mod),
   delta_pa("delta_pa",this,other.delta_pa),
   delta_pe("delta_pe",this,other.delta_pe),
   delta_S("delta_S",this,other.delta_S),
   c1th("c1th",this,other.c1th),
   c2th("c2th",this,other.c2th),
   c3th("c3th",this,other.c3th),
   c4th("c4th",this,other.c4th),
   yth("yth",this,other.yth)
 { 
 } 



 Double_t Testing_sympy::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
   return 3*pow(A_0_mod, 2)*pow(helcosthetaK, 2)*pow(helcosthetaL, 2)/(4*M_PI) + sqrt(3)*A_0_mod*A_S_mod*helcosthetaK*pow(helcosthetaL, 2)*cos(delta_S)/(2*M_PI) - 3*sqrt(2)*A_0_mod*A_pa_mod*helcosthetaK*helcosthetaL*sqrt(-pow(helcosthetaK, 2) + 1)*sqrt(-pow(helcosthetaL, 2) + 1)*cos(delta_pa)*cos(helphi)/(4*M_PI) + pow(A_S_mod, 2)*pow(helcosthetaL, 2)/(4*M_PI) - sqrt(6)*A_S_mod*A_pa_mod*helcosthetaL*sqrt(-pow(helcosthetaK, 2) + 1)*sqrt(-pow(helcosthetaL, 2) + 1)*(sin(delta_S)*sin(delta_pa) + cos(delta_S)*cos(delta_pa))*cos(helphi)/(4*M_PI) + 3*pow(A_pa_mod, 2)*(-pow(helcosthetaK, 2) + 1)*(-pow(helcosthetaL, 2) + 1)*pow(cos(helphi), 2)/(8*M_PI) + 3*pow(A_pe_mod, 2)*(-pow(helcosthetaK, 2) + 1)*(-pow(helcosthetaL, 2) + 1)*pow(sin(helphi), 2)/(8*M_PI) ; 
 } 



 Int_t Testing_sympy::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const  
 { 
 if ( matchArgs(allVars, analVars, helcosthetaK ) )  return 1;
 if ( matchArgs(allVars, analVars, helcosthetaL ) )  return 2;
 if ( matchArgs(allVars, analVars, helphi ) )  return 3;
 if ( matchArgs(allVars, analVars, helcosthetaK,helcosthetaL ) )  return 4;
 if ( matchArgs(allVars, analVars, helcosthetaK,helphi ) )  return 5;
 if ( matchArgs(allVars, analVars, helcosthetaL,helphi ) )  return 6;
 if ( matchArgs(allVars, analVars, helcosthetaK,helcosthetaL,helphi ) )  return 7;
   // LIST HERE OVER WHICH VARIABLES ANALYTICAL INTEGRATION IS SUPPORTED, 
   // ASSIGN A NUMERIC CODE FOR EACH SUPPORTED (SET OF) PARAMETERS 
   // THE EXAMPLE BELOW ASSIGNS CODE 1 TO INTEGRATION OVER VARIABLE X
   // YOU CAN ALSO IMPLEMENT MORE THAN ONE ANALYTICAL INTEGRAL BY REPEATING THE matchArgs 
   // EXPRESSION MULTIPLE TIMES

   // if (matchArgs(allVars,analVars,x)) return 1 ; 
   return 0 ; 
 } 



 Double_t Testing_sympy::analyticalIntegral(Int_t code, const char* rangeName) const  
 { 
if ( code == 1)
{
Double_t Integral = pow(A_0_mod, 2)*pow(helcosthetaL, 2)/(2*M_PI) + pow(A_S_mod, 2)*pow(helcosthetaL, 2)/(2*M_PI) - sqrt(6)*A_S_mod*A_pa_mod*helcosthetaL*sqrt(-pow(helcosthetaL, 2) + 1)*(sin(delta_S)*sin(delta_pa) + cos(delta_S)*cos(delta_pa))*cos(helphi)/8 + pow(A_pa_mod, 2)*(-pow(helcosthetaL, 2) + 1)*pow(cos(helphi), 2)/(2*M_PI) + pow(A_pe_mod, 2)*(-pow(helcosthetaL, 2) + 1)*pow(sin(helphi), 2)/(2*M_PI);
return Integral;
}
else if ( code == 2)
{
Double_t Integral = pow(A_0_mod, 2)*pow(helcosthetaK, 2)/(2*M_PI) + sqrt(3)*A_0_mod*A_S_mod*helcosthetaK*cos(delta_S)/(3*M_PI) + pow(A_S_mod, 2)/(6*M_PI) + pow(A_pa_mod, 2)*(-pow(helcosthetaK, 2) + 1)*pow(cos(helphi), 2)/(2*M_PI) + pow(A_pe_mod, 2)*(-pow(helcosthetaK, 2) + 1)*pow(sin(helphi), 2)/(2*M_PI);
return Integral;
}
else if ( code == 3)
{
Double_t Integral = 3*pow(A_0_mod, 2)*pow(helcosthetaK, 2)*pow(helcosthetaL, 2)/2 + sqrt(3)*A_0_mod*A_S_mod*helcosthetaK*pow(helcosthetaL, 2)*cos(delta_S) + pow(A_S_mod, 2)*pow(helcosthetaL, 2)/2 + 3*pow(A_pa_mod, 2)*(-pow(helcosthetaK, 2) + 1)*(-pow(helcosthetaL, 2) + 1)/8 + 3*pow(A_pe_mod, 2)*(-pow(helcosthetaK, 2) + 1)*(-pow(helcosthetaL, 2) + 1)/8;
return Integral;
}
else if ( code == 4)
{
Double_t Integral = pow(A_0_mod, 2)/(3*M_PI) + pow(A_S_mod, 2)/(3*M_PI) + 2*pow(A_pa_mod, 2)*pow(cos(helphi), 2)/(3*M_PI) + 2*pow(A_pe_mod, 2)*pow(sin(helphi), 2)/(3*M_PI);
return Integral;
}
else if ( code == 5)
{
Double_t Integral = pow(A_0_mod, 2)*pow(helcosthetaL, 2) + pow(A_S_mod, 2)*pow(helcosthetaL, 2) + pow(A_pa_mod, 2)*(-pow(helcosthetaL, 2) + 1)/2 + pow(A_pe_mod, 2)*(-pow(helcosthetaL, 2) + 1)/2;
return Integral;
}
else if ( code == 6)
{
Double_t Integral = pow(A_0_mod, 2)*pow(helcosthetaK, 2) + 2*sqrt(3)*A_0_mod*A_S_mod*helcosthetaK*cos(delta_S)/3 + pow(A_S_mod, 2)/3 + pow(A_pa_mod, 2)*(-pow(helcosthetaK, 2) + 1)/2 + pow(A_pe_mod, 2)*(-pow(helcosthetaK, 2) + 1)/2;
return Integral;
}
else if ( code == 7)
{
Double_t Integral = 2*pow(A_0_mod, 2)/3 + 2*pow(A_S_mod, 2)/3 + 2*pow(A_pa_mod, 2)/3 + 2*pow(A_pe_mod, 2)/3;
return Integral;
}
}