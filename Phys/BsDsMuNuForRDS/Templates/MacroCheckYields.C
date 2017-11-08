void MacroCheckYields(int f_matchPar = 1, bool f_doTau=kFALSE, string fileO="tmp.root"){ 

  TFile *f_in = TFile::Open("/data/Shared/TupleProd_Dec15/RDS/Signal.root");
  f_in->ls();  
  TTree *tree = (TTree*)f_in->Get("DecayTree");
  if (!tree) return;

  Double_t fl_Bmass;
  int fl_nentries = tree->GetEntries();
  tree->SetBranchStatus("*",1);
  tree->Print();
  tree->SetBranchAddress("Bs_0_MCORR",&fl_Bmass);

  /*
    # MC matching stuff
    # Will start with some common cuts. There will be redundancies there but I don't care too much.
  */

  // Cut to say it's a valid reconstructed Ds2KKpi decay.
  TString DsCut = "( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)";
  
  //Cut to say it's a valid mu from a Bs->tau->mu
  TString tauCut = "( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )";
  // Cut to say it's a valid mu from Bs->mu
  TString muCut = "( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )";
  
  // Cut to say the head of the chain is a genuine Bs
  TString Bs0Cut = "( TMath::Abs(Bs_0_TRUEID) == 531 )";
    
  // Cut to indicate the Ds was a direct product of the Bs.
  TString DsFromBsCut = "( TMath::Abs(Ds_MC_MOTHER_ID) == 531 )";
  
  // Cut to say the D came from an intermediate Ds* which came directly from a Bs0.
  TString DsStarCut = "( TMath::Abs(Ds_MC_MOTHER_ID) == 433 )";
    
  //  Same but for Ds1* modes.
  TString Ds2460Cut = "( TMath::Abs(Ds_MC_MOTHER_ID) == 20433 )";
  TString Ds2536Cut = "( TMath::Abs(Ds_MC_MOTHER_ID) == 10433 )";
    
  // For the Ds0*
  TString Ds0StarCut = "( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 )";

  /*    
    # Now for the cut independent strings.
    # For the ground state Ds modes...
  */
  // For Bs0->Dsmu:
  TString Dsmu = "( (" + DsCut + ") && (" + muCut + ") && (" + DsFromBsCut + ") && (" + Bs0Cut + ") )";
  TString Dstau = "( (" + DsCut + ") && (" + tauCut + ") && (" + DsFromBsCut + " ) && (" + Bs0Cut + ") )";

  // For the DsStar modes...
  TString DsStarmu  = "( (" + DsCut + ") && (" + muCut + ") && (" + DsStarCut + " ) && (" + Bs0Cut + ") )" ;
  TString DsStartau = "( (" + DsCut + ") && (" + tauCut + ") && (" + DsStarCut + " ) && (" + Bs0Cut + ") )" ;

  // For the Ds2460 modes...
  TString Ds2460mu  = "( (" + DsCut + ") && (" + muCut + ") && (" + Ds2460Cut + " ) && (" + Bs0Cut + ") )";
  TString Ds2460tau = "( (" + DsCut + ") && (" + tauCut + ") && (" + Ds2460Cut + " ) && (" + Bs0Cut + ") )";

  //For the Ds2536 modes...
  TString Ds2536mu  = "( (" + DsCut + ") && (" + muCut + ") && (" + Ds2536Cut + " ) && (" + Bs0Cut + ") )";
  TString Ds2536tau = "( (" + DsCut + ") && (" + tauCut + ") && (" + Ds2536Cut + " ) && (" + Bs0Cut + ") )";

  // For the Ds0Star modes...
  TString Ds0Starmu  = "( (" + DsCut + ") && (" + muCut + ") && (" + Ds0StarCut + " ) && (" + Bs0Cut + ") )";
  TString Ds0Startau = "( (" + DsCut + ") && (" + tauCut + ") && (" + Ds0StarCut + " ) && (" + Bs0Cut + ") )";

  TString cut = " Bs_0_MCORR > 3000 && Bs_0_MCORR < 8000 && (Ds_MM>1920 && Ds_MM<2010)";
  TString cutIN, cutFIT;
  TString rec_muCut = " && ( mu_ProbNNmu > 0.3)";

  TString cutSele = " && (sqrt( (Ds_PE+mu_PE)**2 - ((Ds_PX+mu_PX)**2 + (Ds_PY+mu_PY)**2 + (Ds_PZ+mu_PZ)**2) ) > 3000) && (mu_PT>1000)";


  cutIN = cut + rec_muCut;
  if(f_matchPar == 1) {
    if(f_doTau) {
      cutIN += " && " + Dstau;
    } else {
      cutIN += " && " + Dsmu;
    }
  } else  if(f_matchPar == 2) {
    if(f_doTau) {
      cutIN += " && " + DsStartau;
    } else {
      cutIN += " && " + DsStarmu;
    }
  } else  if(f_matchPar == 3) {
    if(f_doTau) {
      cutIN += " && " + Ds2460tau;
    } else {
      cutIN += " && " + Ds2460mu;
    }
  } else  if(f_matchPar == 4) {
    if(f_doTau) {
      cutIN += " && " + Ds2536tau;
    } else {
      cutIN += " && " + Ds2536mu;
    }
  } else  if(f_matchPar == 5) {
    if(f_doTau) {
      cutIN += " && " + 	Ds0Startau;
    } else {
      cutIN += " && " + 	Ds0Starmu;
    }
  } 

  cutFIT = cutIN + cutSele;

  TTreeFormula *formula = new TTreeFormula("formula",cutIN,tree);
  TTreeFormula *formulaH = new TTreeFormula("formulaH",cutFIT,tree);

  TFile *fou = new TFile(fileO.data(),"RECREATE");
  TH1D *histoMass = new TH1D("histoMass","",125,3000,8000);
  TH1D *histoMassFit = new TH1D("histoMassFit","",125,3000,8000);

  for (Long64_t i=0;i<fl_nentries; i++) {
    if (i%10000 == 0) std::cout << "--- ... Processing event: " << i << std::endl;
    
    tree->GetEntry(i);
    //    if(m_debug)    cout<<"Applying the following CUT::  "<<cutIN.Data()<<endl;
    Int_t ndata = formula->GetNdata();
    if(ndata!=1) cout<<""<<endl;
    if (formula->EvalInstance(0)>0){ 
      //Store datasets
      histoMass->Fill(fl_Bmass);
    }
  }

  for (Long64_t i=0;i<fl_nentries; i++) {
    if (i%10000 == 0) std::cout << "--- ... Processing event: " << i << std::endl;
    
    tree->GetEntry(i);
    //    if(m_debug)    cout<<"Applying the following CUT::  "<<cutIN.Data()<<endl;
    Int_t ndata = formulaH->GetNdata();
    if(ndata!=1) cout<<""<<endl;
    if (formulaH->EvalInstance(0)>0){ 
      //Store datasets
      histoMassFit->Fill(fl_Bmass);
    }
  }
  fou->cd();
  histoMass->Write();
  histoMassFit->Write();
  fou->Close();

  return;

}
