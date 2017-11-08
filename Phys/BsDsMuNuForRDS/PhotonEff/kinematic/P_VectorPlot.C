#include "TCanvas.h"
#include "TLine.h"
#include "TGraph.h"
#include "TH1.h"
#include "TMarker.h"
#include "TMath.h"
//#include "P_DstarKinematic.h"
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
  beta = -beta;
  /////////

  return gamma*(MOMlongitudinal - beta*pow(pow(mass,2)+pow(MOMlongitudinal,2)+pow(MOMtransversal,2),0.5));
}

double MissingMass(double B, double N, double Pneutral){
  return  pow( (pow((B - pow(pow(N,2)+pow(Pneutral,2),0.5)),2) - pow(Pneutral,2)),0.5);
} 


TCanvas* P_Plot2BodyDecay(double M, double m1, double m2){
  TCanvas* twoPlot = new TCanvas("twoPlot","2Body Kinematic",0,0,400,400);
  twoPlot->cd();

  double momentum  = P_2bodykinematic(M,m1,m2);
  TGraph* TOT = new TGraph(2);
  TOT->SetPoint(0,-1*momentum,-1*momentum);
  TOT->SetPoint(1, 1*momentum, 1*momentum);
  TOT->SetLineColor(0);
  TOT->Draw("AL");
  
  TGraph* TOTL = new TGraph(2);
  TOTL->SetPoint(0, 0, 0);
  TOTL->SetPoint(1, -1*momentum, 0);
  TOTL->Draw("Lsame");

  TGraph* TOTR = new TGraph(2);
  TOTR->SetPoint(0, 0, 0);
  TOTR->SetPoint(1, +1*momentum, 0);
  TOTR->Draw("Lsame");

  TMarker* M0 = new TMarker(0, 0, 20);           M0->SetMarkerColor(kBlack);   M0->Draw("");
  TMarker* ML = new TMarker(-1*momentum, 0, 20); ML->SetMarkerColor(kGreen);   ML->Draw("");
  TMarker* MR = new TMarker( 1*momentum, 0, 20); MR->SetMarkerColor(kBlue);    MR->Draw("");

  twoPlot->Update();
  return twoPlot;
}



TCanvas* P_Plot2BodyDecayAngle(double M, double m1, double m2, double ANGLE){
  TCanvas* twoPlot2 = new TCanvas("twoPlot2","2Body Kinematic",400,0,400,400);
  twoPlot2->cd();

  double momentum  = P_2bodykinematic(M,m1,m2);
  double sinANGLE  = TMath::Sin(ANGLE);
  double cosANGLE  = TMath::Cos(ANGLE);

  TGraph* TOT2 = new TGraph(2);
  TOT2->SetPoint(0,-1*momentum,-1*momentum);
  TOT2->SetPoint(1, 1*momentum, 1*momentum);
  TOT2->SetLineColor(0);
  TOT2->Draw("AL");

  TGraph* TOT2h = new TGraph(2);
  TOT2h->SetPoint(0,-1*momentum, 0);
  TOT2h->SetPoint(1, 1*momentum, 0);
  TOT2h->SetLineColor(1);
  TOT2h->Draw("Lsame");



  TGraph* TOTL2 = new TGraph(2);
  TOTL2->SetPoint(0, 0, 0);
  TOTL2->SetPoint(1, -cosANGLE*momentum, -sinANGLE*momentum);
  TOTL2->Draw("Lsame");

  TGraph* TOTR2 = new TGraph(2);
  TOTR2->SetPoint(0, 0, 0);
  TOTR2->SetPoint(1, +cosANGLE*momentum, +sinANGLE*momentum);
  TOTR2->Draw("Lsame");

  TMarker* M02 = new TMarker(0, 0, 20);                                   M02->SetMarkerColor(kGreen); M02->Draw("");
  TMarker* ML2 = new TMarker(-cosANGLE*momentum, -sinANGLE*momentum, 20); ML2->SetMarkerColor(kRed);   ML2->Draw("");
  TMarker* MR2 = new TMarker(+cosANGLE*momentum, +sinANGLE*momentum, 20); MR2->SetMarkerColor(kGray);   MR2->Draw("");

  twoPlot2->Update();
  return twoPlot2;
}



TCanvas* P_Plot3BodyDecayBoosted(double M, double m1, double m2, double ANGLE, double D0, double Neutral){

  TCanvas* twoPlot3 = new TCanvas("twoPlot3","3Body Kinematic",800,0,400,400);
  twoPlot3->cd();

  //second decay//
  double momentum1  = P_2bodykinematic(M,m1,m2);
  double momentum2  = P_2bodykinematic(m1,D0,Neutral);
  //double sinANGLE  = TMath::Sin(ANGLE);
  //double cosANGLE  = TMath::Cos(ANGLE);
  ////////////////
  double Neutral_L = Plongitudinalprime( P_2bodykinematicL(m1,D0,Neutral,ANGLE), P_2bodykinematicT(m1,D0,Neutral,ANGLE), Neutral,       momentum1, m1);
  double Neutral_T = P_2bodykinematicT(m1,D0,Neutral,ANGLE);
  double D0_L      = Plongitudinalprime(-P_2bodykinematicL(m1,D0,Neutral,ANGLE),-P_2bodykinematicT(m1,D0,Neutral,ANGLE), D0,      momentum1, m1);
  double D0_T      =-P_2bodykinematicT(m1,D0,Neutral,ANGLE);
  ////////////////


  TGraph* TOT3Body = new TGraph(2);
  TOT3Body->SetPoint(0,  momentum1,   momentum2);
  TOT3Body->SetPoint(1, -momentum1,  -momentum2);
  TOT3Body->SetLineColor(0);
  TOT3Body->Draw("AL");

  TGraph* TOTRt = new TGraph(2);
  TOTRt->SetPoint(0, 0, 0);
  TOTRt->SetPoint(1, momentum1, 0);
  TOTRt->Draw("Lsame");

  TGraph* TOTneutral = new TGraph(2);
  TOTneutral->SetPoint(0, 0, 0);
  TOTneutral->SetPoint(1, Neutral_L, Neutral_T);
  TOTneutral->Draw("Lsame");

  TGraph* TOTD0 = new TGraph(2);
  TOTD0->SetPoint(0, 0, 0);
  TOTD0->SetPoint(1, D0_L, D0_T);
  TOTD0->Draw("Lsame");

  TMarker* M02 = new TMarker(0, 0, 20);                                     M02->SetMarkerColor(kBlack); M02->Draw("");
  TMarker* Mleft = new TMarker(momentum1, 0, 20); Mleft->SetMarkerColor(kBlue); Mleft->Draw("");
  TMarker* Mneut = new TMarker(Neutral_L, Neutral_T, 20);Mneut->SetMarkerColor(kGray); Mneut->Draw("");
  TMarker* MD0   = new TMarker(D0_L, D0_T, 20);MD0->SetMarkerColor(kRed);MD0->Draw("");

  twoPlot3->Update();
  return twoPlot3;
}

