{

  //////////////////////////
  #include "/home/gandini/PDFs/Convert.h"
  gROOT->ProcessLine(".x /home/gandini/PDFs/ThesisStyle.C");
  gSystem->Load("RooCruijff_cc.so");
  gStyle->SetPadTopMargin(0.065); //0.08
  gStyle->SetPadBottomMargin(0.15);//12
  gStyle->SetPadLeftMargin(0.18); //0.14
  gStyle->SetPadRightMargin(0.08);
  //////////////////////////
  double BuPDG=5279.15;
  double D0PDG=1864.84;
  double DSTAR=2006.98;
  double PiPDG=139.57018;
  double KPDG= 493.677;
  double BsPDG=5366.3;
  int NBIN=100;
  //////////////////////////



  TH1F DB("DB","DB",NBIN,-100,+100);
  TH1F mis("mis","mis",NBIN,5100,6500);
  TH1F mistrue("mistrue","mistrue",NBIN,5100,6500);




  //////////////////////////  
  TFile *Ntuple = new TFile("$PWD/B2D0Pi_D02KPi_recoas_b2dk_d2kpi_misID.root");  
  TTree *tree   = (TTree*) Ntuple->Get("Bu2D0X");
  Int_t nEvents = tree->GetEntries();
  cout<<"-----------------------------------"<<endl;
  printf( "Nentries = %d\n" , nEvents ) ;
  cout<<"-----------------------------------"<<endl; 
  float trueM_misID, trueM, Bu_TRUEP_M;
  int Bu_BKGCAT;
  Float_t         Bu_TRUEP_E;
  Float_t         Bu_TRUEP_X;
  Float_t         Bu_TRUEP_Y;
  Float_t         Bu_TRUEP_Z;
  Float_t Bu_DPVCFIT_M,Bu_M,BDT,Bach_PIDK;
  Float_t         Bach_PT,P_PT,K_PT,Bach_P,P_P,K_P,K_PX,K_PY,P_PX,P_PY;
  TLorentzVector Bu_TRUEP;
  //////////////////////////
  tree->SetBranchAddress("trueM_misID",&trueM_misID);
  tree->SetBranchAddress("trueM",&trueM);
  tree->SetBranchAddress("Bu_TRUEP_E",&Bu_TRUEP_E);
  tree->SetBranchAddress("Bu_TRUEP_X",&Bu_TRUEP_X);
  tree->SetBranchAddress("Bu_TRUEP_Y",&Bu_TRUEP_Y);
  tree->SetBranchAddress("Bu_TRUEP_Z",&Bu_TRUEP_Z);
  tree->SetBranchAddress("Bu_BKGCAT",&Bu_BKGCAT);
  tree->SetBranchAddress("Bach_PT",&Bach_PT);
  tree->SetBranchAddress("Bach_P",&Bach_P);
  tree->SetBranchAddress("P_PX",&P_PX);
  tree->SetBranchAddress("K_PX",&K_PX);
  tree->SetBranchAddress("P_PY",&P_PY);
  tree->SetBranchAddress("K_PY",&K_PY);
  tree->SetBranchAddress("Bu_DPVCFIT_M",&Bu_DPVCFIT_M);
  tree->SetBranchAddress("Bu_M",&Bu_M);
  tree->SetBranchAddress("BDT",&BDT);
  tree->SetBranchAddress("Bach_PIDK",&Bach_PIDK);


  //////////////////////////
  outputfile = new TFile("Mass.root","RECREATE");
  TTree Mass_tree("Mass_tree","Mass_tree");
  Mass_tree->Branch("trueM",&trueM,"trueM/F");
  Mass_tree->Branch("trueM_misID",&trueM_misID,"trueM_misID/F");
  Mass_tree->Branch("Bu_TRUEP_M",&Bu_TRUEP_M,"Bu_TRUEP_M/F");
  Mass_tree->Branch("Bu_BKGCAT",&Bu_BKGCAT,"Bu_BKGCAT/I"); 
 //////////////////////////




  for(Int_t i = 0;i<nEvents;i++) {
    tree->GetEntry(i);



    /////////
    P_PT = sqrt(pow(P_PX,2)+pow(P_PY,2));
    K_PT = sqrt(pow(K_PX,2)+pow(K_PY,2));
    Bu_TRUEP.SetXYZT(Bu_TRUEP_X,Bu_TRUEP_Y,Bu_TRUEP_Z,Bu_TRUEP_E); 
    Bu_TRUEP_M=Bu_TRUEP.M();
    if(abs(Bu_TRUEP_M-5279.15)>1) continue;
    if(Bu_BKGCAT!=30) continue;

    if(K_PT<250) continue;        if(P_PT<250) continue;
    if(Bach_P <5.0e3) continue;   if(Bach_P >100e3) continue;
    if(Bach_PT<0.5e3) continue;   if(Bach_PT>10e3 ) continue;
    /////////


    if(Bach_PIDK>0) mis->Fill(Bu_DPVCFIT_M);
    mistrue->Fill(trueM_misID);
    Mass_tree->Fill();    
  } 
  printf( "Nentries = %d\n" , Mass_tree->GetEntries() ) ;
  cout<<"-----------------------------------"<<endl;
  cout<<endl;





  //////////////////////////////////////
  TCanvas BMass("BMass", "B Mass",10,10,1200,500);
  BMass.Divide(2);
  mis->SetLineColor(kRed);

  BMass.cd(1);  Mass_tree->Draw("Bu_TRUEP_M-5279.15");
  BMass.cd(2);  gPad->SetLogy(); mistrue->DrawNormalized(""); mis->DrawNormalized("same");
  ///////////////////////////////////////





  RooRealVar rootrueM_misID("trueM_misID","Mass",5100,6500,"MeV/#font[12]{c}^{2}");
  RooDataSet data("data","data",&Mass_tree,RooArgSet(rootrueM_misID));

  RooRealVar  mean("mean"  ,"m"      , (5100+6500)/2    , 5100,6500);
  RooRealVar  sigma("sigma","#sigma" , 11               , 4, 100);
  RooRealVar  alphaL("alphaL", "alphaL", 0.115, 0, 1, "");//alphaL.setConstant();
  RooRealVar  alphaR("alphaR", "alphaR", 0.098, 0, 1, "");//alphaR.setConstant();
  RooCruijff  pdf("pdf","pdf",rootrueM_misID, mean,sigma,sigma,alphaL,alphaR);
  pdf.fitTo(data);

  TCanvas *c2 = new TCanvas("c2", "c2",10,10,1200/3,500);
  RooPlot* xframe = rootrueM_misID.frame();
  data.plotOn(xframe);
  pdf.plotOn(xframe);
  xframe->SetTitle("");
  xframe->Draw();









}
