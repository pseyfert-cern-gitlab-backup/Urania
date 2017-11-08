{
  ////////////////////////////////////
  cout<<"---------------------"<<endl;
  cout<<"- Test of Kinematic -"<<endl;
  cout<<"---------------------"<<endl<<endl;
  ////////////////////////////////////
  gROOT->ProcessLine(".x ThesisStyle.C");
  gSystem->Load("P_DstarKinematic_C.so");
  gSystem->Load("P_VectorPlot_C.so");
  #include "Convert.h"
  using namespace std;
  cout<<"---------------------"<<endl;
  using namespace RooFit;
  cout<<"---------------------"<<endl;
  ////////////////////////////////////
  double BuPDG=5279.15;
  double BdPDG=5279.58;
  double D0PDG=1864.84;
  double RHO0=775.49;
  double KSTAR0=895.94;
  double RHOplus=775.11; 
  double KSTARplus=891.66;
  double DSTAR0=2006.98;
  double DSTARplus=2010.28;
  double PiPDG=139.57018;
  double P0PDG=134.9766;
  double KPDG= 493.677;
  ////////////////////////////////////
  //Switch the IDs and treat the D* like the K*, and the bach like the D0
  double B=BuPDG;
  double Dstar=RHOplus;
  double bach=D0PDG;
  double neutral=P0PDG;
  double ANGLE = 60./180*TMath::Pi();
  ////////////////////////////////////
  cout<<endl<<"---------------------"<<endl;
  cout<<"B     = "<<B<<endl;
  cout<<"Dstar = "<<Dstar<<endl;
  cout<<"bach  = "<<bach<<endl;
  cout<<"p_1RF = "<<P_2bodykinematic(B,Dstar,bach)<<endl;
  //TCanvas* pippo = P_Plot2BodyDecay(B,Dstar,bach);
  cout<<"---------------------"<<endl;
  ////////////////////////////////////
  cout<<endl<<"---------------------"<<endl;
  cout<<"ANGLE   = "<<ANGLE<<endl;
  cout<<"-----"<<endl;
  cout<<"Dstar   = "<<KSTAR0<<endl;
  cout<<"D0PDG   = "<<KPDG<<endl;
  cout<<"neutral = "<<neutral<<endl;
  cout<<"p_2RF      = "<<P_2bodykinematic(Dstar,KPDG,neutral)<<endl;
  cout<<"p_2RF_long = "<<P_2bodykinematicL(Dstar,KPDG,neutral,ANGLE)<<endl;
  cout<<"p_2RF_tran = "<<P_2bodykinematicT(Dstar,KPDG,neutral,ANGLE)<<endl;
  cout<<"---------------------"<<endl;
  ////////////////////////////////////
  //TCanvas* pippo2 = P_Plot2BodyDecayAngle(Dstar,PiPDG,neutral,ANGLE);


  cout<<endl;
  cout<<"---------------------"<<endl;
  cout<<" BOOSTING...         "<<endl;
  cout<<"---------------------"<<endl;



  int t=0,nstep=0;
  double max  = 360./180*TMath::Pi();
  double step = 0.01;
  for(ANGLE = 0.; ANGLE < max; ANGLE = ANGLE + step) nstep++;
  TGraph* GraphPNeutral = new TGraph(nstep);
  TGraph* GraphPNeutral_Cos = new TGraph(nstep);
  GraphMissingMass  = new TGraph(nstep);
  GraphMissingMass_Cos = new TGraph(nstep);


  for(ANGLE = 0.; ANGLE < max; ANGLE = ANGLE + step){

  double Neutral_L = Plongitudinalprime( P_2bodykinematicL(Dstar,KPDG,neutral,ANGLE), P_2bodykinematicT(Dstar,KPDG,neutral,ANGLE), neutral,       P_2bodykinematic(B,Dstar,bach), Dstar);
  double Neutral_T = P_2bodykinematicT(Dstar,KPDG,neutral,ANGLE);
  double D0_L      = Plongitudinalprime(-P_2bodykinematicL(Dstar,KPDG,neutral,ANGLE),-P_2bodykinematicT(Dstar,KPDG,neutral,ANGLE), KPDG,       P_2bodykinematic(B,Dstar,bach), Dstar);
  double D0_T      =-P_2bodykinematicT(Dstar,KPDG,neutral,ANGLE);


  //////////
  //cout<<"Sum of Longitudinal components = "<<Neutral_L+D0_L+P_2bodykinematic(B,Dstar,bach)<<endl;
  double value_PNeutral = pow( pow(Neutral_L,2) + pow(Neutral_T,2) , 0.5);
  double MissingMass    = MissingMass(B, neutral, value_PNeutral);
  GraphPNeutral->SetPoint(t, ANGLE, value_PNeutral);
  GraphPNeutral_Cos->SetPoint(t, TMath::Cos(ANGLE), value_PNeutral);
  GraphMissingMass->SetPoint(t, ANGLE, MissingMass);
  GraphMissingMass_Cos->SetPoint(t, TMath::Cos(ANGLE), MissingMass);
  //////////
 

  t++;
  }



  GraphPNeutral->GetYaxis()->SetTitle("Momentum of Neutral (MeV)");
  GraphPNeutral->GetXaxis()->SetTitle("#theta Angle");
  GraphPNeutral->SetTitle("");
  GraphPNeutral_Cos->GetYaxis()->SetTitle("Momentum of Neutral (MeV)");
  GraphPNeutral_Cos->GetXaxis()->SetTitle("Cos(#theta) Angle");
  GraphPNeutral_Cos->SetTitle("");
  GraphMissingMass->GetYaxis()->SetTitle("Reconstructed Invariant Mass (MeV)");
  GraphMissingMass->GetXaxis()->SetTitle("#theta Angle");
  GraphMissingMass->SetTitle("");
  GraphMissingMass_Cos->GetYaxis()->SetTitle("Reconstructed Invariant Mass  (MeV)");
  GraphMissingMass_Cos->GetXaxis()->SetTitle("Cos(#theta) Angle");
  GraphMissingMass_Cos->SetTitle("");


  TCanvas g("g","g",0,0,1000,500);
  g.Divide(2);

  g.cd(1);  GraphPNeutral->Draw("ALp");
  g.cd(2);  GraphPNeutral_Cos->Draw("ALp");

  TCanvas g2("g2","g2",0,0,1000,500);
  g2.Divide(2);

  g2.cd(1);  GraphMissingMass->Draw("ALp");
  g2.cd(2);  GraphMissingMass_Cos->Draw("ALp");





  /////////////////////////////////
  cout<<endl<<endl;
  ANGLE=0.;
  Neutral_L = Plongitudinalprime( P_2bodykinematicL(Dstar,KPDG,neutral,ANGLE), P_2bodykinematicT(Dstar,KPDG,neutral,ANGLE), neutral,       P_2bodykinematic(B,Dstar,bach), Dstar);
  Neutral_T = P_2bodykinematicT(Dstar,KPDG,neutral,ANGLE);
  D0_L      = Plongitudinalprime(-P_2bodykinematicL(Dstar,KPDG,neutral,ANGLE),-P_2bodykinematicT(Dstar,KPDG,neutral,ANGLE), KPDG,       P_2bodykinematic(B,Dstar,bach), Dstar);
  D0_T      =-P_2bodykinematicT(Dstar,KPDG,neutral,ANGLE);
  value_PNeutral = pow( pow(Neutral_L,2) + pow(Neutral_T,2) , 0.5);
  MissingMass    = MissingMass(B, neutral, value_PNeutral);
  cout<<"Min = "<<stringify(MissingMass,3)<<endl;

  ANGLE=TMath::Pi();
  Neutral_L = Plongitudinalprime( P_2bodykinematicL(Dstar,KPDG,neutral,ANGLE), P_2bodykinematicT(Dstar,KPDG,neutral,ANGLE), neutral,       P_2bodykinematic(B,Dstar,bach), Dstar);
  Neutral_T = P_2bodykinematicT(Dstar,KPDG,neutral,ANGLE);
  D0_L      = Plongitudinalprime(-P_2bodykinematicL(Dstar,KPDG,neutral,ANGLE),-P_2bodykinematicT(Dstar,KPDG,neutral,ANGLE), KPDG,       P_2bodykinematic(B,Dstar,bach), Dstar);
  D0_T      =-P_2bodykinematicT(Dstar,KPDG,neutral,ANGLE);
  value_PNeutral = pow( pow(Neutral_L,2) + pow(Neutral_T,2) , 0.5);
  MissingMass    = MissingMass(B, neutral, value_PNeutral);
  cout<<"Max = "<<stringify(MissingMass,3)<<endl;
  cout<<endl<<endl;




}
