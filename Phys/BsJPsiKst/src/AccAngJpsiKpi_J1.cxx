 /***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by Urania using RooClassFactory               *
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "AccAngJpsiKpi_J1.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(AccAngJpsiKpi_J1) 

AccAngJpsiKpi_J1::AccAngJpsiKpi_J1(const char *name, const char *title, 
				   RooAbsReal& _helcosthetaK,
				   RooAbsReal& _helcosthetaL,
				   RooAbsReal& _helphi,
				   RooAbsReal& _As2,
				   RooAbsReal& _fL,
				   RooAbsReal& _fpa,
				   RooAbsReal& _delta_pa,
				   RooAbsReal& _delta_pe,
				   RooAbsReal& _delta_S,
				   RooAbsReal& _Cfact_10,
				   RooAbsReal& _c1_psi,
				   RooAbsReal& _c2_psi,
				   RooAbsReal& _c3_psi,
				   RooAbsReal& _c4_psi,
				   RooAbsReal& _y_acc,
				   RooAbsReal& _c2_theta) :
RooAbsPdf(name,title), 
  helcosthetaK("helcosthetaK","helcosthetaK",this,_helcosthetaK),
  helcosthetaL("helcosthetaL","helcosthetaL",this,_helcosthetaL),
  helphi("helphi","helphi",this,_helphi),
  As2("As2","As2",this,_As2),
  fL("fL","fL",this,_fL),
  fpa("fpa","fpa",this,_fpa),
  delta_pa("delta_pa","delta_pa",this,_delta_pa),
  delta_pe("delta_pe","delta_pe",this,_delta_pe),
  delta_S("delta_S","delta_S",this,_delta_S),
  Cfact_10("Cfact_10","Cfact_10",this,_Cfact_10),
  c1_psi("c1_psi","c1_psi",this,_c1_psi),
  c2_psi("c2_psi","c2_psi",this,_c2_psi),
  c3_psi("c3_psi","c3_psi",this,_c3_psi),
  c4_psi("c4_psi","c4_psi",this,_c4_psi),
  y_acc("y_acc","y_acc",this,_y_acc),
  c2_theta("c2_theta","c2_theta",this,_c2_theta)
{ 
} 


AccAngJpsiKpi_J1::AccAngJpsiKpi_J1(const AccAngJpsiKpi_J1& other, const char* name) :  
  RooAbsPdf(other,name), 
  helcosthetaK("helcosthetaK",this,other.helcosthetaK),
  helcosthetaL("helcosthetaL",this,other.helcosthetaL),
  helphi("helphi",this,other.helphi),
  As2("As2",this,other.As2),
  fL("fL",this,other.fL),
  fpa("fpa",this,other.fpa),
  delta_pa("delta_pa",this,other.delta_pa),
  delta_pe("delta_pe",this,other.delta_pe),
  delta_S("delta_S",this,other.delta_S),
  Cfact_10("Cfact_10",this,other.Cfact_10),
  c1_psi("c1_psi",this,other.c1_psi),
  c2_psi("c2_psi",this,other.c2_psi),
  c3_psi("c3_psi",this,other.c3_psi),
  c4_psi("c4_psi",this,other.c4_psi),
  y_acc("y_acc",this,other.y_acc),
  c2_theta("c2_theta",this,other.c2_theta)
{ 
} 



Double_t AccAngJpsiKpi_J1::evaluate() const 
{ 
  Double_t sthk = sqrt(-pow(helcosthetaK, 2) + 1);
  Double_t sthl = sqrt(-pow(helcosthetaL, 2) + 1);
  Double_t sthk2 = -pow(helcosthetaK, 2) + 1;
  Double_t sthl2 = -pow(helcosthetaL, 2) + 1;
  Double_t cthk2 = pow(helcosthetaK, 2);
  Double_t cthl2 = pow(helcosthetaL, 2);
  Double_t cosphi2 = pow(cos(helphi), 2);
  Double_t sinphi2 = pow(sin(helphi), 2);
  Double_t cosphi = cos(helphi);
  Double_t sinphi = sin(helphi);
  Double_t As = sqrt(As2);
  Double_t sqfL = sqrt(fL);
  Double_t sqfpa = sqrt(fpa);
  Double_t cdelta_pa = cos(delta_pa);
  Double_t cdelta_pe = cos(delta_pe);
  Double_t sdelta_pa = sin(delta_pa);
  Double_t sdelta_pe = sin(delta_pe);
  Double_t sdelta_s = sin(delta_S);
  Double_t cdelta_s = cos(delta_S);
  Double_t sq2 = sqrt(2);
  Double_t sq3 = sqrt(3);
  Double_t sq5 = sqrt(5);
  // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
  return ((c2_theta*cthl2 + 1.0)*(c1_psi*helcosthetaK + c2_psi*cthk2 + c3_psi*pow(cthk2, 3.0/2.0) + c4_psi*pow(cthk2, 2) + pow(cthk2, 5.0/2.0)*(-c1_psi - c2_psi - c3_psi - c4_psi + y_acc - 1) + 1.0)*(As*cdelta_s*helcosthetaK*sq3*sqfL*sthl2*Cfact_10*sqrt(-As2 + 1)/(2*M_PI) + sqrt(6)*As*cosphi*helcosthetaL*sqfpa*sthk*sthl*Cfact_10*sqrt(-As2 + 1)*(cdelta_pa*cdelta_s + sdelta_pa*sdelta_s)/(4*M_PI) - sqrt(6)*As*helcosthetaL*sinphi*sthk*sthl*Cfact_10*sqrt((-As2 + 1)*(-fL - fpa + 1))*(-cdelta_pe*sdelta_s + cdelta_s*sdelta_pe)/(4*M_PI) + As2*sthl2/(4*M_PI) + 3*cdelta_pa*cosphi*helcosthetaK*helcosthetaL*sq2*sqfL*sqfpa*sthk*sthl*(-As2 + 1)/(4*M_PI) - 3*cosphi*sinphi*sqfpa*sthk2*sthl2*sqrt((-As2 + 1)*(-fL - fpa + 1))*sqrt(-As2 + 1)*(-cdelta_pa*sdelta_pe + cdelta_pe*sdelta_pa)/(4*M_PI) + 3*cthk2*fL*sthl2*(-As2 + 1)/(4*M_PI) + 3*fpa*sthk2*(-As2 + 1)*(2*cosphi2*cthl2 + 2*sinphi2)/(16*M_PI) - 3*helcosthetaK*helcosthetaL*sdelta_pe*sinphi*sq2*sqfL*sthk*sthl*sqrt((-As2 + 1)*(-fL - fpa + 1))*sqrt(-As2 + 1)/(4*M_PI) + 3*sthk2*(-As2 + 1)*(-fL - fpa + 1)*(-2*cosphi2*cthl2 + 2*cosphi2 + 2*cthl2)/(16*M_PI))) ; 
} 



Int_t AccAngJpsiKpi_J1::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const  
{ 
  if ( matchArgs(allVars, analVars, helphi,helcosthetaK,helcosthetaL ) )  return 1;
  if ( matchArgs(allVars, analVars, helcosthetaK,helcosthetaL ) )  return 2;
  if ( matchArgs(allVars, analVars, helphi,helcosthetaK ) )  return 3;
  if ( matchArgs(allVars, analVars, helphi,helcosthetaL ) )  return 4;
  // LIST HERE OVER WHICH VARIABLES ANALYTICAL INTEGRATION IS SUPPORTED, 
  // ASSIGN A NUMERIC CODE FOR EACH SUPPORTED (SET OF) PARAMETERS 
  // THE EXAMPLE BELOW ASSIGNS CODE 1 TO INTEGRATION OVER VARIABLE X
  // YOU CAN ALSO IMPLEMENT MORE THAN ONE ANALYTICAL INTEGRAL BY REPEATING THE matchArgs 
  // EXPRESSION MULTIPLE TIMES
  
  // if (matchArgs(allVars,analVars,x)) return 1 ; 
  return 0 ; 
} 



Double_t AccAngJpsiKpi_J1::analyticalIntegral(Int_t code, const char* rangeName) const  
{ 
  Double_t sthk = sqrt(-pow(helcosthetaK, 2) + 1);
  Double_t sthl = sqrt(-pow(helcosthetaL, 2) + 1);
  Double_t sthk2 = -pow(helcosthetaK, 2) + 1;
  Double_t sthl2 = -pow(helcosthetaL, 2) + 1;
  Double_t cthk2 = pow(helcosthetaK, 2);
  Double_t cthl2 = pow(helcosthetaL, 2);
  Double_t cosphi2 = pow(cos(helphi), 2);
  Double_t sinphi2 = pow(sin(helphi), 2);
  Double_t cosphi = cos(helphi);
  Double_t sinphi = sin(helphi);
  Double_t As = sqrt(As2);
  Double_t sqfL = sqrt(fL);
  Double_t sqfpa = sqrt(fpa);
  Double_t cdelta_pa = cos(delta_pa);
  Double_t cdelta_pe = cos(delta_pe);
  Double_t sdelta_pa = sin(delta_pa);
  Double_t sdelta_pe = sin(delta_pe);
  Double_t sdelta_s = sin(delta_S);
  Double_t cdelta_s = cos(delta_S);
  Double_t sq2 = sqrt(2);
  Double_t sq3 = sqrt(3);
  Double_t sq5 = sqrt(5);
  if ( code == 1) {
    Double_t Integral = (1/(16*TMath::Pi()))*(62.831853071795884 + 9.215338450530059*c2_psi + 25.132741228718345*c2_theta + 3.6861353802120242*c2_psi*c2_theta + 4.188790204786393*c3_psi + 1.6755160819145565*c2_theta*c3_psi + 1.5558363617778053*c4_psi + 0.6223345447111209*c2_theta*c4_psi - 20.943951023931973*fL + 5.864306286700953*c2_psi*fL - 16.75516081914557*c2_theta*fL - 0.6702064327658226*c2_psi*c2_theta*fL + 4.188790204786386*c3_psi*fL + 2.034555242324817*c4_psi*fL + 0.09574377610940323*c2_theta*c4_psi*fL + c1_psi*( -4.18879020478639 + c2_theta*( -1.6755160819145565 - 3.351032163829113*fL) - 20.94395102393196*fL - 8.881784197001252e-16*fpa) - 8.881784197001252e-16*c3_psi*fpa + (4.18879020478639 + 20.94395102393196*fL + c2_theta*(1.6755160819145565 + 3.351032163829113*fL) + 8.881784197001252e-16*fpa)*y_acc + As2*( -6.981317007977325 - 13.96263401595464*c2_theta + 1.396263401595462*c3_psi - 0.5585053606381855*c2_theta*c3_psi + 0.6781850807749397*c4_psi - 0.17553025620057258*c2_theta*c4_psi + c2_psi*(1.954768762233652 + c2_theta*( -1.4521139376592822 + 0.6702064327658226*fL) - 5.864306286700953*fL) + 20.943951023931973*fL + 16.75516081914557*c2_theta*fL -4.188790204786386*c3_psi*fL - 2.034555242324817*c4_psi*fL - 0.09574377610940323*c2_theta*c4_psi*fL + c1_psi*( -6.981317007977321 + 20.94395102393196*fL + c2_theta*( -0.5585053606381855 + 3.351032163829113*fL) + 8.881784197001252e-16*fpa) + 8.881784197001252e-16*c3_psi*fpa + (6.981317007977321 + c2_theta*(0.5585053606381855 - 3.351032163829113*fL) - 20.94395102393196*fL - 8.881784197001252e-16*fpa)*y_acc) + sqrt(( -1.*( -1. + As2))*As2)*c1_psi*(77.38877287399329 + 15.477754574798658*c2_theta)*Cfact_10*sqrt(fL)*cos(delta_S));//SIMON from mathematica by 'hand'
    
    return Integral;
  } else if ( code == 2){
    Double_t Integral = -0.0127323954473516*As2*c2_psi*c2_theta*fL - 0.0212206590789194*As2*c2_psi*c2_theta*fpa*pow(sin(helphi), 2) + 0.0127323954473516*As2*c2_psi*c2_theta*fpa + 0.00141471060526129*As2*c2_psi*c2_theta - 0.106103295394597*As2*c2_psi*fL - 0.0636619772367581*As2*c2_psi*fpa*pow(sin(helphi), 2) + 0.0212206590789194*As2*c2_psi*fpa + 0.0495148711841452*As2*c2_psi - 0.0127323954473516*As2*c2_theta*c4_psi*fL - 0.00909456817667974*As2*c2_theta*c4_psi*fpa*pow(sin(helphi), 2) + 0.00545674090600784*As2*c2_theta*c4_psi*fpa + 0.00303152272555991*As2*c2_theta*c4_psi + 0.0212206590789194*As2*c2_theta*fL - 0.106103295394597*As2*c2_theta*fpa*pow(sin(helphi), 2) + 0.0636619772367581*As2*c2_theta*fpa - 0.0212206590789194*As2*c2_theta - 0.0818511135901176*As2*c4_psi*fL - 0.0272837045300392*As2*c4_psi*fpa*pow(sin(helphi), 2) + 0.00909456817667974*As2*c4_psi*fpa + 0.033346749981159*As2*c4_psi - 0.106103295394597*As2*fL - 0.318309886183791*As2*fpa*pow(sin(helphi), 2) + 0.106103295394597*As2*fpa + 0.106103295394597*As2 + 0.0318309886183791*Cfact_10*sqrt(fL)*sqrt(-As2*(As2 - 1))*(c1_psi*(0.879771838765144*c2_theta + 4.39885919382572) + c2_psi*(-0.659828879073858*c2_theta - 3.29914439536929) + 0.263931551629543*c2_theta*c3_psi - 0.659828879073858*c2_theta*c4_psi + 0.659828879073858*c2_theta*y_acc - 0.659828879073858*c2_theta + 1.31965775814772*c3_psi - 3.29914439536929*c4_psi + 3.29914439536929*y_acc - 3.29914439536929)*cos(delta_S) + 0.0127323954473516*c2_psi*c2_theta*fL + 0.00848826363156775*c2_psi*c2_theta*sqrt(fpa)*sqrt((As2 - 1)*(fL + fpa - 1))*sqrt(-As2 + 1)*sin(2*helphi)*sin(-delta_pa + delta_pe) + 0.0212206590789194*c2_psi*c2_theta*fpa*pow(sin(helphi), 2) - 0.0127323954473516*c2_psi*c2_theta*fpa + 0.0127323954473516*c2_psi*c2_theta + 0.106103295394597*c2_psi*fL + 0.0424413181578387*c2_psi*sqrt(fpa)*sqrt((As2 - 1)*(fL + fpa - 1))*sqrt(-As2 + 1)*sin(2*helphi)*sin(-delta_pa + delta_pe) + 0.0636619772367581*c2_psi*fpa*pow(sin(helphi), 2) - 0.0212206590789194*c2_psi*fpa + 0.0212206590789194*c2_psi + 0.0127323954473516*c2_theta*c4_psi*fL + 0.00363782727067189*c2_theta*c4_psi*sqrt(fpa)*sqrt((As2 - 1)*(fL + fpa - 1))*sqrt(-As2 + 1)*sin(2*helphi)*sin(-delta_pa + delta_pe) + 0.00909456817667974*c2_theta*c4_psi*fpa*pow(sin(helphi), 2) - 0.00545674090600784*c2_theta*c4_psi*fpa + 0.00545674090600784*c2_theta*c4_psi - 0.0212206590789194*c2_theta*fL + 0.0424413181578388*c2_theta*sqrt(fpa)*sqrt((As2 - 1)*(fL + fpa - 1))*sqrt(-As2 + 1)*sin(2*helphi)*sin(-delta_pa + delta_pe) + 0.106103295394597*c2_theta*fpa*pow(sin(helphi), 2) - 0.0636619772367581*c2_theta*fpa + 0.0636619772367581*c2_theta + 0.0818511135901176*c4_psi*fL + 0.0181891363533595*c4_psi*sqrt(fpa)*sqrt((As2 - 1)*(fL + fpa - 1))*sqrt(-As2 + 1)*sin(2*helphi)*sin(-delta_pa + delta_pe) + 0.0272837045300392*c4_psi*fpa*pow(sin(helphi), 2) - 0.00909456817667974*c4_psi*fpa + 0.00909456817667974*c4_psi + 0.106103295394597*fL + 0.212206590789194*sqrt(fpa)*sqrt((As2 - 1)*(fL + fpa - 1))*sqrt(-As2 + 1)*sin(2*helphi)*sin(-delta_pa + delta_pe) + 0.318309886183791*fpa*pow(sin(helphi), 2) - 0.106103295394597*fpa + 0.0318309886183791*(As2*(c2_psi*(c2_theta*(0.266666666666667*fL - 0.133333333333333*fpa - 0.266666666666667) + 1.33333333333333*fL + 0.666666666666667*fpa - 1.33333333333333) + c2_theta*(c4_psi*(0.114285714285714*fL - 0.0571428571428572*fpa - 0.114285714285714) + 1.33333333333333*fL - 0.666666666666667*fpa - 1.33333333333333) + 0.571428571428572*c4_psi*fL + 0.285714285714286*c4_psi*fpa - 0.571428571428572*c4_psi + 6.66666666666667*fL + 3.33333333333333*fpa - 6.66666666666667) + c2_psi*(c2_theta*(-0.266666666666667*fL + 0.133333333333333*fpa + 0.266666666666667) - 1.33333333333333*fL - 0.666666666666667*fpa + 1.33333333333333) - 0.114285714285714*c2_theta*c4_psi*fL + 0.0571428571428572*c2_theta*c4_psi*fpa + 0.114285714285714*c2_theta*c4_psi - 1.33333333333333*c2_theta*fL + 0.666666666666667*c2_theta*fpa + 1.33333333333333*c2_theta - 0.571428571428572*c4_psi*fL - 0.285714285714286*c4_psi*fpa + 0.571428571428572*c4_psi - 6.66666666666667*fL - 3.33333333333333*fpa + 6.66666666666667)*pow(cos(helphi), 2) + 0.106103295394597;
    return Integral;
  } else if ( code == 3){
    Double_t Integral = (0.7*c2_theta*pow(helcosthetaL, 2) + 0.7)*(As2*(c2_psi*(fL*(pow(helcosthetaL, 2) - 0.714285714285714) - 0.619047619047619*pow(helcosthetaL, 2) + 0.333333333333333) + c4_psi*(0.673469387755102*fL*pow(helcosthetaL, 2) - 0.551020408163265*fL - 0.346938775510204*pow(helcosthetaL, 2) + 0.224489795918367) + 2.14285714285714*fL*pow(helcosthetaL, 2) - 0.714285714285714*fL - 2.14285714285714*pow(helcosthetaL, 2) + 0.714285714285714) + Cfact_10*sqrt(fL)*sqrt(-As2*(As2 - 1))*(c1_psi*(-0.942612684391226*pow(helcosthetaL, 2) + 0.942612684391226) + c2_psi*(0.706959513293419*pow(helcosthetaL, 2) - 0.706959513293419) - 0.282783805317368*c3_psi*pow(helcosthetaL, 2) + 0.282783805317368*c3_psi + 0.706959513293419*c4_psi*pow(helcosthetaL, 2) - 0.706959513293419*c4_psi - 0.706959513293419*pow(helcosthetaL, 2)*y_acc + 0.706959513293419*pow(helcosthetaL, 2) + 0.706959513293419*y_acc - 0.706959513293419)*cos(delta_S) - 1.0*c2_psi*fL*pow(helcosthetaL, 2) + 0.714285714285714*c2_psi*fL + 0.142857142857143*c2_psi*pow(helcosthetaL, 2) + 0.142857142857143*c2_psi - 0.673469387755102*c4_psi*fL*pow(helcosthetaL, 2) + 0.551020408163265*c4_psi*fL + 0.0612244897959184*c4_psi*pow(helcosthetaL, 2) + 0.0612244897959184*c4_psi - 2.14285714285714*fL*pow(helcosthetaL, 2) + 0.714285714285714*fL + 0.714285714285714*pow(helcosthetaL, 2) + 0.714285714285714);
    return Integral;
  } else if ( code == 4){
    Double_t Integral = (0.8*helcosthetaK*(c1_psi*(pow(helcosthetaK, 4) - 1.0) + pow(helcosthetaK, 4)*(c2_psi + c3_psi + c4_psi - 1.0*y_acc) + helcosthetaK*(-1.0*c2_psi + helcosthetaK*(-1.0*c3_psi + helcosthetaK*(-1.0*c4_psi + helcosthetaK)))) - 0.8)*(As2*(c2_theta*(-0.5*fL + 0.333333333333333) - 1.25*fL - 7.06789929214115e-17*fpa + 0.416666666666667) - 0.577350269189626*Cfact_10*sqrt(fL)*helcosthetaK*sqrt(-As2*(As2 - 1))*(1.0*c2_theta + 5.0)*cos(delta_S) + 0.5*c2_theta*fL - 0.5*c2_theta + 1.25*fL + 7.06789929214115e-17*fpa + pow(helcosthetaK, 2)*(As2*(c2_theta*(1.0*fL - 0.5) + 3.75*fL + 7.06789929214115e-17*fpa - 1.25) + c2_theta*(-1.0*fL + 0.5) - 3.75*fL - 7.06789929214115e-17*fpa + 1.25) - 1.25);
    return Integral;
  }
}