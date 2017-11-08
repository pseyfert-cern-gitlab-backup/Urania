{
  ////////////////////////////////////
  cout<<"---------------------"<<endl;
  cout<<"- Test of Kinematic -"<<endl;
  cout<<"---------------------"<<endl<<endl;
  ////////////////////////////////////
  gROOT->ProcessLine(".x /home/gandini/PDFs/ThesisStyle.C");
  gSystem->Load("P_DstarKinematic_C.so");
  gSystem->Load("P_VectorPlot_C.so");
  #include "/home/gandini/PDFs/Convert.h"
  using namespace std;
  cout<<"---------------------"<<endl;
  using namespace RooFit;
  cout<<"---------------------"<<endl;
  ////////////////////////////////////
  double BuPDG=5279.15;
  double D0PDG=1864.84;
  double DSTAR=2006.98;
  double PiPDG=139.57018;
  double P0PDG=134.9766;
  double KPDG= 493.677;
  ////////////////////////////////////
  double B=BuPDG;
  double Dstar=DSTAR;
  double bach=PiPDG;
  double neutral=P0PDG;
  double ANGLE = 30./180*TMath::Pi();
  ////////////////////////////////////
  cout<<endl<<"---------------------"<<endl;
  cout<<"B     = "<<B<<endl;
  cout<<"Dstar = "<<Dstar<<endl;
  cout<<"bach  = "<<bach<<endl;
  cout<<"p_1RF = "<<P_2bodykinematic(B,Dstar,bach)<<endl;
  TCanvas* pippo = P_Plot2BodyDecay(B,Dstar,bach);
  cout<<"---------------------"<<endl;
  ////////////////////////////////////
  cout<<endl<<"---------------------"<<endl;
  cout<<"ANGLE   = "<<ANGLE<<endl;
  cout<<"-----"<<endl;
  cout<<"Dstar   = "<<Dstar<<endl;
  cout<<"D0PDG   = "<<D0PDG<<endl;
  cout<<"neutral = "<<neutral<<endl;
  cout<<"p_2RF      = "<<P_2bodykinematic(Dstar,D0PDG,neutral)<<endl;
  cout<<"p_2RF_long = "<<P_2bodykinematicL(Dstar,D0PDG,neutral,ANGLE)<<endl;
  cout<<"p_2RF_tran = "<<P_2bodykinematicT(Dstar,D0PDG,neutral,ANGLE)<<endl;
  cout<<"---------------------"<<endl;
  ////////////////////////////////////
  TCanvas* pippo2 = P_Plot2BodyDecayAngle(Dstar,D0PDG,neutral,ANGLE);


  cout<<endl;
  cout<<"---------------------"<<endl;
  cout<<" BOOSTING...         "<<endl;
  cout<<"---------------------"<<endl;

  double Neutral_L = Plongitudinalprime( P_2bodykinematicL(Dstar,D0PDG,neutral,ANGLE), P_2bodykinematicT(Dstar,D0PDG,neutral,ANGLE), neutral,       P_2bodykinematic(B,Dstar,bach), Dstar);
  double Neutral_T = P_2bodykinematicT(Dstar,D0PDG,neutral,ANGLE);
  double D0_L      = Plongitudinalprime(-P_2bodykinematicL(Dstar,D0PDG,neutral,ANGLE),-P_2bodykinematicT(Dstar,D0PDG,neutral,ANGLE), D0PDG,       P_2bodykinematic(B,Dstar,bach), Dstar);
  double D0_T      =-P_2bodykinematicT(Dstar,D0PDG,neutral,ANGLE);
  cout<<"Neutral_L = "<<Neutral_L<<endl;
  cout<<"Neutral_T = "<<Neutral_T<<endl;
  cout<<"D0_L      = "<<D0_L<<endl;
  cout<<"D0_T      = "<<D0_T<<endl;

  cout<<"---------------------"<<endl;

  cout<<"Sum of Longitudinal components = "<<Neutral_L+D0_L+P_2bodykinematic(B,Dstar,bach)<<endl;
  TCanvas* pippo3 = P_Plot3BodyDecayBoosted(B,Dstar,bach,ANGLE,D0PDG,neutral);








}
