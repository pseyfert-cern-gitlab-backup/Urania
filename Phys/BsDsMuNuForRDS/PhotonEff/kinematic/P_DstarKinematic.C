#include "TMath.h"
#include "TLorentzVector.h"

double P_2bodykinematic(double M, double m1, double m2){
  return  pow(  ( (pow(M,2)-pow((m1+m2),2) )*(pow(M,2)-pow((m1-m2),2))),0.5)/(2*M);
}

double P_2bodykinematicL(double M, double m1, double m2, double ANGLE){
  return  pow(  ( (pow(M,2)-pow((m1+m2),2) )*(pow(M,2)-pow((m1-m2),2))),0.5)/(2*M) * TMath::Cos(ANGLE);
}

double P_2bodykinematicT(double M, double m1, double m2, double ANGLE){
  return  pow(  ( (pow(M,2)-pow((m1+m2),2) )*(pow(M,2)-pow((m1-m2),2))),0.5)/(2*M) * TMath::Sin(ANGLE);
}

double E_kinematic(double p, double m){
  return  pow(pow(m,2)+pow(p,2),0.5);
}

double Plongitudinalprime(double MOMlongitudinal, double MOMtransversal, double mass, double p_1RF, double DSTAR){
  /*********************************************************************************************************
  The particle I am boosting is identified with (MOMlongitudinal,mass) -> like the neutral (secodary decay)
  The boost is identified with a beta from (p_1RF,DSTAR)
  **********************************************************************************************************/

  /////////
  double gamma = E_kinematic(p_1RF,DSTAR)/DSTAR;
  double beta  = pow((1-pow(gamma,-2)),0.5);
  /////////

  return   gamma*(MOMlongitudinal - beta*pow(pow(mass,2)+pow(MOMlongitudinal,2)+pow(MOMtransversal,2),0.5));
}

double Plongitudinalprimeprime(double MOMlongitudinal, double MOMtransversal, double mass, double p_1RF, double DSTAR){
  /*********************************************************************************************************
  The particle I am boosting is identified with (MOMlongitudinal,mass) -> like the neutral (secodary decay)
  The boost is identified with a beta from (p_1RF,DSTAR)
  **********************************************************************************************************/

  /////////
  double gamma = E_kinematic(p_1RF,DSTAR)/DSTAR;
  double beta  = pow((1-pow(gamma,-2)),0.5);
  beta  = -beta;
  /////////

  return   gamma*(MOMlongitudinal - beta*pow(pow(mass,2)+pow(MOMlongitudinal,2)+pow(MOMtransversal,2),0.5));
}

double MissingMass(double B, double N, double Pneutral){
  return         pow( (pow((B - pow(pow(N,2)+pow(Pneutral,2),0.5)),2) - pow(Pneutral,2)),0.5);
}
