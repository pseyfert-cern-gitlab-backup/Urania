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
  double B          =BuPDG;
  double D          =D0PDG;
  double bach       =PiPDG;
  double bach_misID =KPDG;
  double ANGLE = 30./180*TMath::Pi();
  double ALPHA = 50e3; //momentum of the B
  ////////////////////////////////////
  cout<<endl<<"---------------------"<<endl;
  cout<<"B     = "<<B<<endl;
  cout<<"D     = "<<D<<endl;
  cout<<"bach  = "<<bach<<endl;
  cout<<"ANGLE = "<<ANGLE<<endl;
  cout<<"ALPHA = "<<ALPHA<<endl;
  double p_1RF = P_2bodykinematic(B,D,bach);
  TCanvas* pippo = P_Plot2BodyDecayAngle(B,D,bach,ANGLE);
  cout<<"---------------------"<<endl;
  cout<<"p_1RF      = "<<p_1RF<<endl;
  cout<<"p_1RF_long BACHELOR = "<< P_2bodykinematicL(B,D,bach,ANGLE)<<endl;
  cout<<"p_1RF_tran BACHELOR = "<< P_2bodykinematicT(B,D,bach,ANGLE)<<endl;
  cout<<"p_1RF_long D0       = "<<-P_2bodykinematicL(B,D,bach,ANGLE)<<endl;
  cout<<"p_1RF_tran D0       = "<<-P_2bodykinematicT(B,D,bach,ANGLE)<<endl;
  cout<<"---------------------"<<endl;


  ////////////////////////////////////
  cout<<" BOOSTING...         "<<endl;
  cout<<"---------------------"<<endl;
  double Boost_Bach_L = Plongitudinalprimeprime( P_2bodykinematicL(B,D,bach,ANGLE), P_2bodykinematicT(B,D,bach,ANGLE), bach, ALPHA , B  );
  double Boost_D_L    = Plongitudinalprimeprime(-P_2bodykinematicL(B,D,bach,ANGLE),-P_2bodykinematicT(B,D,bach,ANGLE), D   , ALPHA , B  );
  double Boost_Bach_T = P_2bodykinematicT(B,D,bach,ANGLE);
  double Boost_D_T    =-P_2bodykinematicT(B,D,bach,ANGLE);
  cout<<"Boost_Bach_L = "<<Boost_Bach_L<<endl;
  cout<<"Boost_Bach_T = "<<Boost_Bach_T<<endl;
  cout<<"Boost_D_L = "<<Boost_D_L<<endl;
  cout<<"Boost_D_T = "<<Boost_D_T<<endl;
  double e1 = sqrt(pow(D,2)+pow(Boost_D_L,2)+pow(Boost_D_T,2));
  double e2_bach       = sqrt(pow(bach,2)      +pow(Boost_Bach_L,2)+pow(Boost_Bach_T,2));
  double e2_bach_misID = sqrt(pow(bach_misID,2)+pow(Boost_Bach_L,2)+pow(Boost_Bach_T,2));
  cout<<"---------------------"<<endl; 
  double Sum       = sqrt(pow((e1+e2_bach),2)       -  pow((Boost_Bach_L+Boost_D_L),2));
  double Sum_misID = sqrt(pow((e1+e2_bach_misID),2)-  pow((Boost_Bach_L+Boost_D_L),2));
  cout<<"Sum       = "<<Sum<<endl;
  cout<<"Sum_misID = "<<Sum_misID<<endl;
  cout<<"---------------------"<<endl;






  //////////////////////////////////////////////////////////////////////////////////////
  TGraph2D*    Graph = new TGraph2D();
  TGraph*   Graph_1D = new TGraph();
  TGraph*   Graph_2D = new TGraph();
  TGraph*   Graph_int = new TGraph();


  int t_angle=0; int nstep_angle=0;
  int t_alpha=0; int nstep_alpha=0;
  int t=0;

  double min_angle =   0.  /180*TMath::Pi();
  double max_angle =   360./180*TMath::Pi();
  double stp_angle =   1.  /180*TMath::Pi();
  for(ANGLE = min_angle; ANGLE < max_angle; ANGLE = ANGLE + stp_angle) nstep_angle++;

  double min_alpha =       0;
  double max_alpha =   400e3;
  double stp_alpha =     5e3;
  for(ALPHA = min_alpha; ALPHA < max_alpha; ALPHA = ALPHA + stp_alpha) nstep_alpha++;
  cout<<endl;
  cout<<"---------------------"<<endl;
  cout<<"nstep_angle = "<< nstep_angle<<endl;
  cout<<"nstep_alpha = "<< nstep_alpha<<endl;
  cout<<"---------------------"<<endl;
  //////////////////////////////////////////////////////////////////////////////////////




  double a_Boost_Bach_L,a_Boost_D_L,a_Boost_Bach_T,a_Boost_D_T,a_e1,a_e2_bach,a_e2_bach_misID,a_Sum_misID;
  double b_Boost_Bach_L,b_Boost_D_L,b_Boost_Bach_T,b_Boost_D_T,b_e1,b_e2_bach,b_e2_bach_misID,b_Sum_misID;

  double stepINT = 0.001;
  double integral;
  int zzz=0;  

  for(ALPHA = min_alpha; ALPHA < max_alpha+200; ALPHA = ALPHA + stp_alpha) {

    integral=0;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    for(double COS = -1; COS < 1; COS = COS + stepINT) {
      ANGLE = TMath::ACos(COS);
      //cout<<ANGLE/TMath::Pi()*360<<endl;

      a_Boost_Bach_L = Plongitudinalprimeprime( P_2bodykinematicL(B,D,bach,ANGLE), P_2bodykinematicT(B,D,bach,ANGLE), bach, ALPHA , B  );
      a_Boost_D_L    = Plongitudinalprimeprime(-P_2bodykinematicL(B,D,bach,ANGLE),-P_2bodykinematicT(B,D,bach,ANGLE), D   , ALPHA , B  );
      a_Boost_Bach_T = P_2bodykinematicT(B,D,bach,ANGLE);
      a_Boost_D_T    =-P_2bodykinematicT(B,D,bach,ANGLE);
      a_e1            = sqrt(pow(D,2)         +pow(a_Boost_D_L,2)   +pow(a_Boost_D_T,2));
      a_e2_bach       = sqrt(pow(bach,2)      +pow(a_Boost_Bach_L,2)+pow(a_Boost_Bach_T,2));
      a_e2_bach_misID = sqrt(pow(bach_misID,2)+pow(a_Boost_Bach_L,2)+pow(a_Boost_Bach_T,2));
      a_Sum_misID     = sqrt(pow((a_e1+a_e2_bach_misID),2)-  pow((a_Boost_Bach_L+a_Boost_D_L),2));

      b_Boost_Bach_L = Plongitudinalprimeprime( P_2bodykinematicL(B,D,bach,(ANGLE+stepINT)), P_2bodykinematicT(B,D,bach,(ANGLE+stepINT)), bach, ALPHA , B  );
      b_Boost_D_L    = Plongitudinalprimeprime(-P_2bodykinematicL(B,D,bach,(ANGLE+stepINT)),-P_2bodykinematicT(B,D,bach,(ANGLE+stepINT)), D   , ALPHA , B  );
      b_Boost_Bach_T = P_2bodykinematicT(B,D,bach,(ANGLE+stepINT));
      b_Boost_D_T    =-P_2bodykinematicT(B,D,bach,(ANGLE+stepINT));
      b_e1            = sqrt(pow(D,2)         +pow(b_Boost_D_L,2)   +pow(b_Boost_D_T,2));
      b_e2_bach       = sqrt(pow(bach,2)      +pow(b_Boost_Bach_L,2)+pow(b_Boost_Bach_T,2));
      b_e2_bach_misID = sqrt(pow(bach_misID,2)+pow(b_Boost_Bach_L,2)+pow(b_Boost_Bach_T,2));
      b_Sum_misID     = sqrt(pow((b_e1+b_e2_bach_misID),2)-  pow((b_Boost_Bach_L+b_Boost_D_L),2));

      integral = integral + 0.5*(a_Sum_misID+b_Sum_misID)/2*stepINT;

    }
    //cout<<integral<<endl;
    Graph_int->SetPoint(zzz, ALPHA, integral);
    zzz++;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  }

  TCanvas f("f","f",0,0,1000,500);
  //f.Divide(2);
  Graph_int->GetYaxis()->SetTitle("Misreconstructed mass (angle integrated)");
  Graph_int->GetXaxis()->SetTitle("B momentum (GeV)");
  Graph_int->SetTitle("");
  f.cd(1);  Graph_int->Draw("AL");







  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  for(ANGLE = min_angle; ANGLE < max_angle; ANGLE = ANGLE + stp_angle) {
    for(ALPHA = min_alpha; ALPHA < max_alpha; ALPHA = ALPHA + stp_alpha) {

      Boost_Bach_L = Plongitudinalprimeprime( P_2bodykinematicL(B,D,bach,ANGLE), P_2bodykinematicT(B,D,bach,ANGLE), bach, ALPHA , B  );
      Boost_D_L    = Plongitudinalprimeprime(-P_2bodykinematicL(B,D,bach,ANGLE),-P_2bodykinematicT(B,D,bach,ANGLE), D   , ALPHA , B  );
      Boost_Bach_T = P_2bodykinematicT(B,D,bach,ANGLE);
      Boost_D_T    =-P_2bodykinematicT(B,D,bach,ANGLE);
      e1 = sqrt(pow(D,2)+pow(Boost_D_L,2)+pow(Boost_D_T,2));
      e2_bach       = sqrt(pow(bach,2)      +pow(Boost_Bach_L,2)+pow(Boost_Bach_T,2));
      e2_bach_misID = sqrt(pow(bach_misID,2)+pow(Boost_Bach_L,2)+pow(Boost_Bach_T,2));
      Sum       = sqrt(pow((e1+e2_bach),2)       -  pow((Boost_Bach_L+Boost_D_L),2));
      Sum_misID = sqrt(pow((e1+e2_bach_misID),2)-  pow((Boost_Bach_L+Boost_D_L),2));
      //cout<<Sum_misID<<endl;
 
      Graph_1D->SetPoint(t, TMath::Cos(ANGLE), Sum_misID);
      Graph_2D->SetPoint(t, ALPHA            , Sum_misID);
      t++;

    }}
  TCanvas g("g","g",0,0,1000,500);
  g.Divide(2);
  Graph_1D->GetYaxis()->SetTitle("Misreconstructed mass (MeV)");
  Graph_1D->GetXaxis()->SetTitle("Cos(#theta) Angle");
  Graph_1D->SetTitle("");
  Graph_2D->GetYaxis()->SetTitle("Misreconstructed mass (MeV)");
  Graph_2D->GetXaxis()->SetTitle("B momentum (GeV)");
  Graph_2D->SetTitle("");
  g.cd(1);  Graph_1D->Draw("Ap");
  g.cd(2);  Graph_2D->Draw("Ap");
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////











}
