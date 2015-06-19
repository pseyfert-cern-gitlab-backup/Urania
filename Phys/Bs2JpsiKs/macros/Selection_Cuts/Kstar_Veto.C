///////////////////////////////////////
// ***** Veto the K* Component ***** //
///////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb
// - Reconstruct the B mass with one pion assigned the kaon mass



/////////////////////////////////////
// ***** Load useful classes ***** //
/////////////////////////////////////

#include "RooArgSet.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooRealVar.h"

#include "TAxis.h"
#include "TBox.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMath.h"
#include "TNtuple.h"
#include "TPaveText.h"

using namespace RooFit;

///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void Veto(){

// ***** Initialize ***** //
////////////////////////////

  bool debug = false;
  Double_t vetoMax = 5279.58 + 20;
  Double_t vetoMin = 5279.58 - 20;

  // *** PDG Masses ***
  Double_t clight = 299.792458;
  //Double_t mPiplus = 139.57018;
  Double_t mKplus = 493.677;
  //Double_t mJpsi = 3096.916;

  // *** Plot Ranges ***
  //Double_t Bmass_min = 5180;
  //Double_t Bmass_max = 5520;


// ***** Part I: From NTuple to DataSet ***** //
////////////////////////////////////////////////

// This is done to easily handle the selection cuts and allows semi-automatic looping over these cuts

  std::cout << " " << std::endl;
  std::cout << "== Part I: From NTuple to DataSet ==" << std::endl;
  std::cout << "====================================" << std::endl;

  // ***** Load NTuples ***** //
  //////////////////////////////

  TChain* chain_Bd = new TChain("chain_Bd");
  chain_Bd->Add("B2JpsiKs-Slim-SigBd.root/Slim_B2JpsiKs_Tuple");

  TChain* chain_Kstar = new TChain("chain_Kstar");
  chain_Kstar->Add("B2JpsiKs-Slim-SigKstarWM.root/Slim_B2JpsiKs_Tuple");
  
  Long64_t nEntries_Bd = chain_Bd->GetEntries();
  Long64_t nEntries_Kstar = chain_Kstar->GetEntries();
  std::cout << "Number of entries from DaVinci: " << nEntries_Bd << " (Bd->JpsiKs), " << nEntries_Kstar << " (Bd->JpsiKstar)" << std::endl;    


  // ***** Define DataSet Observables ***** //
  ////////////////////////////////////////////

  // *** Define Observables & Selection Variables ***
        
  // Selection Cuts
  Float_t B_FullFit_M[10];
  Int_t piminus_TRACK_Type = -999;
  // Observables for Common Selection Cuts
  Int_t B_FullFit_nPV = -999;
  Float_t B_FullFit_ctau[10];
	Float_t B_FullFit_status[10];
	Float_t B_FullFit_chi2[10];
  Float_t B_FullFit_MERR[10];
	Float_t B_FullFit_PV_Z[10];
  // Observables for Decay Specific Cuts
  Double_t Psi_PE = -999;
  Double_t piplus_PE = -999;
  Double_t piminus_PE = -999;
  Double_t Psi_PX = -999;
  Double_t piplus_PX = -999;
  Double_t piminus_PX = -999;
  Double_t Psi_PY = -999;
  Double_t piplus_PY = -999;
  Double_t piminus_PY = -999;
  Double_t Psi_PZ = -999;
  Double_t piplus_PZ = -999;
  Double_t piminus_PZ = -999;
	Double_t KS0_M_with_pplus_piplus = -999;
	Double_t KS0_M_with_piplus_pplus = -999;
	Float_t B_FullFit_KS0_ctau[10];
  Float_t B_FullFit_KS0_ctauErr[10];
  // True ID of Decay
  Int_t B_TRUEID = -999;
  Int_t Psi_TRUEID = -999;
  Int_t KS0_TRUEID = -999;
  Int_t B_BKGCAT = -999;

  // *** Initialize Arrays ***
  for(Int_t i=0; i<10; i++){
		B_FullFit_ctau[i] = -999;
    B_FullFit_M[i] = -999;
    B_FullFit_status[i] = -999;
    B_FullFit_chi2[i] = -999;
    B_FullFit_MERR[i] = -999;
    B_FullFit_PV_Z[i] = -999;
    B_FullFit_KS0_ctau[i] = -999;
    B_FullFit_KS0_ctauErr[i] = -999;
  }


  // *** Set Branch Addresses ***
  // Selection Cuts
  chain_Bd->SetBranchAddress("B_FullFit_M", &B_FullFit_M);
  chain_Bd->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type);
  // Observables for Common Selection Cuts
  chain_Bd->SetBranchAddress("B_FullFit_nPV", &B_FullFit_nPV);
  chain_Bd->SetBranchAddress("B_FullFit_ctau", &B_FullFit_ctau);
  chain_Bd->SetBranchAddress("B_FullFit_status", &B_FullFit_status);
  chain_Bd->SetBranchAddress("B_FullFit_chi2", &B_FullFit_chi2);
  chain_Bd->SetBranchAddress("B_FullFit_MERR", &B_FullFit_MERR);
  chain_Bd->SetBranchAddress("B_FullFit_PV_Z", &B_FullFit_PV_Z);
  // Observables for Decay Specific Cuts
  chain_Bd->SetBranchAddress("Psi_PE", &Psi_PE);
  chain_Bd->SetBranchAddress("piplus_PE", &piplus_PE);
  chain_Bd->SetBranchAddress("piminus_PE", &piminus_PE);
  chain_Bd->SetBranchAddress("Psi_PX", &Psi_PX);
  chain_Bd->SetBranchAddress("piplus_PX", &piplus_PX);
  chain_Bd->SetBranchAddress("piminus_PX", &piminus_PX);
  chain_Bd->SetBranchAddress("Psi_PY", &Psi_PY);
  chain_Bd->SetBranchAddress("piplus_PY", &piplus_PY);
  chain_Bd->SetBranchAddress("piminus_PY", &piminus_PY);
  chain_Bd->SetBranchAddress("Psi_PZ", &Psi_PZ);
  chain_Bd->SetBranchAddress("piplus_PZ", &piplus_PZ);
  chain_Bd->SetBranchAddress("piminus_PZ", &piminus_PZ);
  chain_Bd->SetBranchAddress("KS0_M_with_pplus_piplus", &KS0_M_with_pplus_piplus);
  chain_Bd->SetBranchAddress("KS0_M_with_piplus_pplus", &KS0_M_with_piplus_pplus);
  chain_Bd->SetBranchAddress("B_FullFit_KS0_ctau", &B_FullFit_KS0_ctau);
  chain_Bd->SetBranchAddress("B_FullFit_KS0_ctauErr", &B_FullFit_KS0_ctauErr);
  // True ID of Decay
  chain_Bd->SetBranchAddress("B_TRUEID", &B_TRUEID);
  chain_Bd->SetBranchAddress("Psi_TRUEID", &Psi_TRUEID);
  chain_Bd->SetBranchAddress("KS0_TRUEID", &KS0_TRUEID);
  chain_Bd->SetBranchAddress("B_BKGCAT", &B_BKGCAT);
  
  // Selection Cuts
  chain_Kstar->SetBranchAddress("B_FullFit_M", &B_FullFit_M);
  chain_Kstar->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type);
  // Observables for Common Selection Cuts
  chain_Kstar->SetBranchAddress("B_FullFit_nPV", &B_FullFit_nPV);
  chain_Kstar->SetBranchAddress("B_FullFit_ctau", &B_FullFit_ctau);
  chain_Kstar->SetBranchAddress("B_FullFit_status", &B_FullFit_status);
  chain_Kstar->SetBranchAddress("B_FullFit_chi2", &B_FullFit_chi2);
  chain_Kstar->SetBranchAddress("B_FullFit_MERR", &B_FullFit_MERR);
  chain_Kstar->SetBranchAddress("B_FullFit_PV_Z", &B_FullFit_PV_Z);
  // Observables for Decay Specific Cuts
  chain_Kstar->SetBranchAddress("Psi_PE", &Psi_PE);
  chain_Kstar->SetBranchAddress("piplus_PE", &piplus_PE);
  chain_Kstar->SetBranchAddress("piminus_PE", &piminus_PE);
  chain_Kstar->SetBranchAddress("Psi_PX", &Psi_PX);
  chain_Kstar->SetBranchAddress("piplus_PX", &piplus_PX);
  chain_Kstar->SetBranchAddress("piminus_PX", &piminus_PX);
  chain_Kstar->SetBranchAddress("Psi_PY", &Psi_PY);
  chain_Kstar->SetBranchAddress("piplus_PY", &piplus_PY);
  chain_Kstar->SetBranchAddress("piminus_PY", &piminus_PY);
  chain_Kstar->SetBranchAddress("Psi_PZ", &Psi_PZ);
  chain_Kstar->SetBranchAddress("piplus_PZ", &piplus_PZ);
  chain_Kstar->SetBranchAddress("piminus_PZ", &piminus_PZ);
  chain_Kstar->SetBranchAddress("KS0_M_with_pplus_piplus", &KS0_M_with_pplus_piplus);
  chain_Kstar->SetBranchAddress("KS0_M_with_piplus_pplus", &KS0_M_with_piplus_pplus);
  chain_Kstar->SetBranchAddress("B_FullFit_KS0_ctau", &B_FullFit_KS0_ctau);
  chain_Kstar->SetBranchAddress("B_FullFit_KS0_ctauErr", &B_FullFit_KS0_ctauErr);
  // True ID of Decay
  chain_Kstar->SetBranchAddress("B_TRUEID", &B_TRUEID);
  chain_Kstar->SetBranchAddress("Psi_TRUEID", &Psi_TRUEID);
  chain_Kstar->SetBranchAddress("KS0_TRUEID", &KS0_TRUEID);
  chain_Kstar->SetBranchAddress("B_BKGCAT", &B_BKGCAT);
  

  // ***** Initialize DataSet ***** //
  ////////////////////////////////////

  // *** Observable ***
  //RooRealVar *Bmass = new RooRealVar("Bmass","mass",Bmass_min,Bmass_max,"MeV/c^{2}");
  RooRealVar *Bmass = new RooRealVar("Bmass","mass",0,"MeV/c^{2}");
  RooRealVar *weight = new RooRealVar("weight","Weight for Normalisation", 0.,1.);

  // *** DataSet ***
  RooArgSet *Obs = new RooArgSet(*Bmass,*weight);
  RooDataSet *data_Bd_default = new RooDataSet("data_Bd_default","Unbinned dataset",*Obs);
  RooDataSet *data_Bd_recal = new RooDataSet("data_Bd_recal","Unbinned dataset",*Obs);
  RooDataSet *data_Bd_Khypo = new RooDataSet("data_Bd_Khypo","Unbinned dataset",*Obs);
  RooDataSet *data_Bd_Khypo_Weight = new RooDataSet("data_Bd_Khypo_Weight","Unbinned dataset",*Obs, WeightVar(*weight));

  RooDataSet *data_Kstar_default = new RooDataSet("data_Kstar_default","Unbinned dataset",*Obs);
  RooDataSet *data_Kstar_recal = new RooDataSet("data_Kstar_recal","Unbinned dataset",*Obs);
  RooDataSet *data_Kstar_Khypo = new RooDataSet("data_Kstar_Khypo","Unbinned dataset",*Obs);
  RooDataSet *data_Kstar_Khypo_PWeight = new RooDataSet("data_Kstar_Khypo_PWeight","Unbinned dataset",*Obs, WeightVar(*weight));
  RooDataSet *data_Kstar_Khypo_MWeight = new RooDataSet("data_Kstar_Khypo_MWeight","Unbinned dataset",*Obs, WeightVar(*weight));

  // ***** Loop over Entries ***** //
  ///////////////////////////////////

  Double_t recalMass = 0;
  Double_t KminusMass = 0;
  Double_t KplusMass = 0;
  bool SelCuts = false;

  std::cout << " " << std::endl;
  std::cout << "== Loop: Bd->JpsiKs ==" << std::endl;
  std::cout << "======================" << std::endl;

  Int_t Bd_All = 0;
  Int_t Bd_Veto = 0;
  
  std::cout << "Count" << std::endl;
  for(Long64_t i=0; i<nEntries_Bd; i++){
    chain_Bd->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_Bd << " (" << 100*i/nEntries_Bd << "%)" << std::endl;


    for(Int_t pv = 0; pv < B_FullFit_nPV ; pv++){
      // Selection Cuts
      SelCuts = (B_FullFit_M[pv]>5180 && B_FullFit_M[pv]<5520 && B_FullFit_status[pv]==0 && B_FullFit_chi2[pv]<72 &&
        B_FullFit_MERR[pv]<30 && B_FullFit_ctau[pv]/clight>0.0002 && TMath::Abs(B_FullFit_PV_Z[pv])<250 &&
        TMath::Abs(KS0_M_with_pplus_piplus-1116)>2*piminus_TRACK_Type &&
        TMath::Abs(KS0_M_with_piplus_pplus-1116)>2*piminus_TRACK_Type &&
        B_FullFit_KS0_ctau[pv]/B_FullFit_KS0_ctauErr[pv]>5
        );

      if(SelCuts && piminus_TRACK_Type==3){
        if(TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && KS0_TRUEID==310 && (B_BKGCAT==0 || B_BKGCAT==10)) Bd_All++;
      }
    }
  }

  std::cout << "Fill" << std::endl;
  for(Long64_t i=0; i<nEntries_Bd; i++){
    chain_Bd->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_Bd << " (" << 100*i/nEntries_Bd << "%)" << std::endl;

    for(Int_t pv = 0; pv < B_FullFit_nPV ; pv++){
      // Selection Cuts
      SelCuts = (B_FullFit_M[pv]>5180 && B_FullFit_M[pv]<5520 && B_FullFit_status[pv]==0 && B_FullFit_chi2[pv]<72 &&
        B_FullFit_MERR[pv]<30 && B_FullFit_ctau[pv]/clight>0.0002 && TMath::Abs(B_FullFit_PV_Z[pv])<250 &&
        TMath::Abs(KS0_M_with_pplus_piplus-1116)>2*piminus_TRACK_Type &&
        TMath::Abs(KS0_M_with_piplus_pplus-1116)>2*piminus_TRACK_Type &&
        B_FullFit_KS0_ctau[pv]/B_FullFit_KS0_ctauErr[pv]>5
        );

      if(SelCuts && piminus_TRACK_Type==3){
        if(TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && KS0_TRUEID==310 && (B_BKGCAT==0 || B_BKGCAT==10)){

          // Fill DataSet
          weight->setVal((double) 1./Bd_All);
          if(debug){
            Bmass->setVal(B_FullFit_M[0]);
            data_Bd_default->add(*Obs);
          
            recalMass = TMath::Sqrt(pow(Psi_PE + piplus_PE + piminus_PE,2) - pow(Psi_PX+piplus_PX+piminus_PX,2) - pow(Psi_PY+piplus_PY+piminus_PY,2) - pow(Psi_PZ+piplus_PZ+piminus_PZ,2));
            Bmass->setVal(recalMass);
            data_Bd_recal->add(*Obs);
          }
          KminusMass = TMath::Sqrt(pow(Psi_PE + piplus_PE + TMath::Sqrt(pow(mKplus,2) + pow(piminus_PX,2) + pow(piminus_PY,2) + pow(piminus_PZ,2)),2) - pow(Psi_PX+piplus_PX+piminus_PX,2) - pow(Psi_PY+piplus_PY+piminus_PY,2) - pow(Psi_PZ+piplus_PZ+piminus_PZ,2));
          KplusMass = TMath::Sqrt(pow(Psi_PE + piminus_PE + TMath::Sqrt(pow(mKplus,2) + pow(piplus_PX,2) + pow(piplus_PY,2) + pow(piplus_PZ,2)),2) - pow(Psi_PX+piplus_PX+piminus_PX,2) - pow(Psi_PY+piplus_PY+piminus_PY,2) - pow(Psi_PZ+piplus_PZ+piminus_PZ,2));
          Bmass->setVal(KminusMass);
          if(debug) data_Bd_Khypo->add(*Obs);
          data_Bd_Khypo_Weight->add(*Obs, weight->getVal());
          if(!(KminusMass>vetoMin && KminusMass<vetoMax) && !(KplusMass>vetoMin && KplusMass<vetoMax)) Bd_Veto++;
        }
      }
    }
  }

  std::cout << " " << std::endl;
  std::cout << "== Loop: Bd->JpsiKstar ==" << std::endl;
  std::cout << "=========================" << std::endl;

  Int_t Kstar_Plus = 0;
  Int_t Kstar_Min = 0;
  Int_t Kstar_Veto = 0;
  Int_t Kstar_Veto_Mass = 0;

  std::cout << "Count" << std::endl;
  for(Long64_t i=0; i<nEntries_Kstar; i++){
    chain_Kstar->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_Kstar << " (" << 100*i/nEntries_Kstar << "%)" << std::endl;

    for(Int_t pv = 0; pv < B_FullFit_nPV ; pv++){
      // Selection Cuts
      SelCuts = (B_FullFit_status[pv]==0 && B_FullFit_chi2[pv]<72 && B_FullFit_MERR[pv]<30 &&
        B_FullFit_ctau[pv]/clight>0.0002 && TMath::Abs(B_FullFit_PV_Z[pv])<250 &&
        TMath::Abs(KS0_M_with_pplus_piplus-1116)>2*piminus_TRACK_Type &&
        TMath::Abs(KS0_M_with_piplus_pplus-1116)>2*piminus_TRACK_Type &&
        B_FullFit_KS0_ctau[pv]/B_FullFit_KS0_ctauErr[pv]>5
        );

      if(SelCuts && piminus_TRACK_Type==3){
        if(TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && KS0_TRUEID== 313 && B_BKGCAT==30) Kstar_Plus++;
        if(TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && KS0_TRUEID==-313 && B_BKGCAT==30) Kstar_Min++;
      }
    }
  }
  
  std::cout << "Fill" << std::endl;
  for(Long64_t i=0; i<nEntries_Kstar; i++){
    chain_Kstar->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_Kstar << " (" << 100*i/nEntries_Kstar << "%)" << std::endl;

    for(Int_t pv = 0; pv < B_FullFit_nPV ; pv++){
      // Selection Cuts
      SelCuts = (B_FullFit_status[pv]==0 && B_FullFit_chi2[pv]<72 && B_FullFit_MERR[pv]<30 &&
        B_FullFit_ctau[pv]/clight>0.0002 && TMath::Abs(B_FullFit_PV_Z[pv])<250 &&
        TMath::Abs(KS0_M_with_pplus_piplus-1116)>2*piminus_TRACK_Type &&
        TMath::Abs(KS0_M_with_piplus_pplus-1116)>2*piminus_TRACK_Type &&
        B_FullFit_KS0_ctau[pv]/B_FullFit_KS0_ctauErr[pv]>5
        );

      if(SelCuts && piminus_TRACK_Type==3){
        if(TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==313 && B_BKGCAT==30){

          // Fill DataSet
          weight->setVal((double) 1./Kstar_Plus);
          if(debug){
            Bmass->setVal(B_FullFit_M[0]);
            data_Kstar_default->add(*Obs);
          
            recalMass = TMath::Sqrt(pow(Psi_PE + piplus_PE + piminus_PE,2) - pow(Psi_PX+piplus_PX+piminus_PX,2) - pow(Psi_PY+piplus_PY+piminus_PY,2) - pow(Psi_PZ+piplus_PZ+piminus_PZ,2));
            Bmass->setVal(recalMass);
            data_Kstar_recal->add(*Obs);
          }
          KminusMass = TMath::Sqrt(pow(Psi_PE + piplus_PE + TMath::Sqrt(pow(mKplus,2) + pow(piminus_PX,2) + pow(piminus_PY,2) + pow(piminus_PZ,2)),2) - pow(Psi_PX+piplus_PX+piminus_PX,2) - pow(Psi_PY+piplus_PY+piminus_PY,2) - pow(Psi_PZ+piplus_PZ+piminus_PZ,2));
          KplusMass = TMath::Sqrt(pow(Psi_PE + piminus_PE + TMath::Sqrt(pow(mKplus,2) + pow(piplus_PX,2) + pow(piplus_PY,2) + pow(piplus_PZ,2)),2) - pow(Psi_PX+piplus_PX+piminus_PX,2) - pow(Psi_PY+piplus_PY+piminus_PY,2) - pow(Psi_PZ+piplus_PZ+piminus_PZ,2));
          Bmass->setVal(KplusMass);
          if(debug) data_Kstar_Khypo->add(*Obs);
          if(KS0_TRUEID==-313){
            weight->setVal((double) 1./Kstar_Min);
            data_Kstar_Khypo_MWeight->add(*Obs, weight->getVal()); 
          }
          else if(KS0_TRUEID==313){
            weight->setVal((double) 1./Kstar_Plus);
            data_Kstar_Khypo_PWeight->add(*Obs, weight->getVal()); 
          }
          if(!(KminusMass>vetoMin && KminusMass<vetoMax) && !(KplusMass>vetoMin && KplusMass<vetoMax)){
            Kstar_Veto++;
            if(B_FullFit_M[pv]>5180 && B_FullFit_M[pv]<5520) Kstar_Veto_Mass++;
          }
        }
      }
    }
  }
  

  // ***** Plot ***** //
  //////////////////////

  if(debug){

    // *** Frame ***
    RooPlot* Bdframe = Bmass->frame(Range(5180,6180),Bins(100));

    // Titles
    Bdframe->SetYTitle("Events/(15 MeV/c^{2})");
    Bdframe->SetXTitle("B mass (MeV/c^{2})");

    // Cosmetics
    Bdframe->SetTitleOffset(1.2,"y");
    Bdframe->SetTitleSize(0.07,"x");
    Bdframe->SetTitleSize(0.07,"y");
    Bdframe->SetTitleFont(132,"y");
    Bdframe->SetTitleFont(132,"x");
    Bdframe->SetLabelSize(0.05,"y");
    Bdframe->SetLabelSize(0.05,"x");
    Bdframe->SetLabelFont(132,"x");
    Bdframe->SetLabelFont(132,"y");

    data_Bd_default->plotOn(Bdframe,MarkerStyle(21),MarkerSize(0.8),MarkerColor(2),LineColor(2));
    data_Bd_recal->plotOn(Bdframe,MarkerStyle(22),MarkerSize(1),MarkerColor(4),LineColor(4));
    data_Bd_Khypo->plotOn(Bdframe,MarkerStyle(23),MarkerSize(1),MarkerColor(3),LineColor(3));
  
    Bdframe->SetMinimum(10.);
    Bdframe->SetMaximum(100000);
  
    // *** Canvas ***
    TCanvas* doek_Bd = new TCanvas("doek_Bd","Observable",900,800);
    doek_Bd->SetLeftMargin(0.2);
    doek_Bd->SetBottomMargin(0.15);
    doek_Bd->cd(1);
    gPad->SetLogy(1);
    Bdframe->Draw();
    
    // *** Frame ***
    RooPlot* Kstarframe = Bmass->frame(Range(4000,5500),Bins(100));

    // Titles
    Kstarframe->SetYTitle("Events/(15 MeV/c^{2})");
    Kstarframe->SetXTitle("B mass (MeV/c^{2})");

    // Cosmetics
    Kstarframe->SetTitleOffset(1.2,"y");
    Kstarframe->SetTitleSize(0.07,"x");
    Kstarframe->SetTitleSize(0.07,"y");
    Kstarframe->SetTitleFont(132,"y");
    Kstarframe->SetTitleFont(132,"x");
    Kstarframe->SetLabelSize(0.05,"y");
    Kstarframe->SetLabelSize(0.05,"x");
    Kstarframe->SetLabelFont(132,"x");
    Kstarframe->SetLabelFont(132,"y");

    data_Kstar_default->plotOn(Kstarframe,MarkerStyle(21),MarkerSize(0.8),MarkerColor(2));
    data_Kstar_recal->plotOn(Kstarframe,MarkerStyle(22),MarkerSize(1),MarkerColor(4));
    data_Kstar_Khypo->plotOn(Kstarframe,MarkerStyle(23),MarkerSize(1),MarkerColor(3));
  
    Kstarframe->SetMinimum(10.);
    Kstarframe->SetMaximum(100000);
  
    // *** Canvas ***
    TCanvas* doek_Kstar = new TCanvas("doek_Kstar","Observable",900,800);
    doek_Kstar->SetLeftMargin(0.2);
    doek_Kstar->SetBottomMargin(0.15);
    doek_Kstar->cd(1);
    gPad->SetLogy(1);
    Kstarframe->Draw();
  }// Debug
    
  // *** Frame ***
  RooPlot* CompareFrame = Bmass->frame(Range(5180,5520),Bins(68));

    // Titles
  CompareFrame->SetYTitle("Events/(5 MeV/c^{2})");
  CompareFrame->SetXTitle("m_{J/#psi K^{+}#pi^{-}} #scale[0.8]{(MeV/c^{2})}");

    // Cosmetics
  CompareFrame->SetTitleOffset(1.2,"y");
  CompareFrame->SetTitleOffset(0.9,"x");
  CompareFrame->SetTitleSize(0.07,"x");
  CompareFrame->SetTitleSize(0.07,"y");
  CompareFrame->SetTitleFont(132,"y");
  CompareFrame->SetTitleFont(132,"x");
  CompareFrame->SetLabelSize(0.05,"y");
  CompareFrame->SetLabelSize(0.05,"x");
  CompareFrame->SetLabelFont(132,"x");
  CompareFrame->SetLabelFont(132,"y");

  data_Bd_Khypo_Weight->plotOn(CompareFrame,MarkerStyle(21),MarkerSize(0.8),MarkerColor(2),LineColor(2));
  data_Kstar_Khypo_PWeight->plotOn(CompareFrame,MarkerStyle(22),MarkerSize(1),MarkerColor(3),LineColor(3));
  data_Kstar_Khypo_MWeight->plotOn(CompareFrame,MarkerStyle(23),MarkerSize(1),MarkerColor(4),LineColor(4));
  
  CompareFrame->SetMinimum(0.0001);
  CompareFrame->SetMaximum(1);
  
  // *** Canvas ***
  TCanvas* doek_Compare = new TCanvas("doek_Compare","Observable",900,800);
  doek_Compare->SetLeftMargin(0.2);
  doek_Compare->SetBottomMargin(0.15);
  doek_Compare->cd(1);
  
  // *** Frame ***
  gPad->SetLogy(1);
  CompareFrame->Draw();
  
  // *** Exclusion Box ***
  TBox* box = new TBox(vetoMin,0,vetoMax,1);
  box->SetFillColor(18);
  box->Draw();
  CompareFrame->Draw("same");
  
  
  // *** LHCb Tag *** 
  TPaveText *lhcbTag = new TPaveText(0.60,0.80,0.89,0.89,"NDC");

  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  lhcbTag->AddText("LHCb MC11a");
  lhcbTag -> Draw("");
  
  // *** Legend ***
  // Very nasty trick to get the dot in he legend in the correct color
  Float_t red_point[2];
  red_point[0] = 0;
  red_point[1] = 1;
  TGraph *red_contour = new TGraph(2,red_point,red_point);
  red_contour->SetMarkerStyle(21);
  red_contour->SetMarkerSize(0.8);
  red_contour->SetMarkerColor(2);
  red_contour->SetLineColor(2);
  
  Float_t green_point[2];
  green_point[0] = 0;
  green_point[1] = 1;
  TGraph *green_contour = new TGraph(2,green_point,green_point);
  green_contour->SetMarkerStyle(22);
  green_contour->SetMarkerSize(0.8);
  green_contour->SetMarkerColor(3);
  green_contour->SetLineColor(3);
  
  Float_t blue_point[2];
  blue_point[0] = 0;
  blue_point[1] = 1;
  TGraph *blue_contour = new TGraph(2,blue_point,blue_point);
  blue_contour->SetMarkerStyle(23);
  blue_contour->SetMarkerSize(0.8);
  blue_contour->SetMarkerColor(4);
  blue_contour->SetLineColor(4);
  
  TLegend *leg = new TLegend(0.67,0.65,0.85,0.80);
  leg->AddEntry(red_contour,"B_{d}#rightarrow J/#psi K_{S}^{0}","lep");
  leg->AddEntry(green_contour,"B_{d}#rightarrow J/#psi K^{*0}","lep");
  leg->AddEntry(blue_contour,"B_{d}#rightarrow J/#psi #bar{K}^{*0}","lep");
  leg->SetTextAlign(12);
  leg->SetTextSize(0.03);
  leg->SetTextFont(132);
  leg->Draw("");
  
  Float_t black_pointx[4];
  black_pointx[0] = vetoMin;
  black_pointx[1] = black_pointx[0];
  black_pointx[2] = vetoMax;
  black_pointx[3] = black_pointx[2];
  Float_t black_pointy[4];
  black_pointy[0] = 0;
  black_pointy[1] = 1.1;
  black_pointy[2] = black_pointy[1];
  black_pointy[3] = black_pointy[0];
  TGraph *black_contour = new TGraph(4,black_pointx,black_pointy);
  black_contour->SetLineColor(1);
  black_contour->SetLineWidth(2);
  black_contour->Draw("");
  
  
  // *** Save ***
  doek_Compare->SaveAs("Kstar_Veto_MC.pdf");
  
  // ***** Results ***** //
  /////////////////////////
  
  std::cout << "Veto Bd->JpsiK* by excluding [" << vetoMin << "," << vetoMax << "] MeV" << std::endl;
  std::cout << "Surviving Bd->JpsiKs: " << Bd_Veto << "/" << Bd_All << " = " << (double) Bd_Veto/Bd_All << std::endl;
  std::cout << "Surviving Bd->JpsiK*: " << Kstar_Veto << "/" << (Kstar_Plus+Kstar_Min) << " = " << (double) Kstar_Veto/(Kstar_Plus+Kstar_Min) << std::endl;
  std::cout << "Surviving Bd->JpsiK* in mass range: " << Kstar_Veto_Mass << "/" << (Kstar_Plus+Kstar_Min) << " = " << (double) Kstar_Veto_Mass/(Kstar_Plus+Kstar_Min) << std::endl;
}


///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void RD_Veto(){

// ***** Initialize ***** //
////////////////////////////

  Double_t vetoMax = 5279.58 + 20;
  Double_t vetoMin = 5279.58 - 20;

  // *** PDG Masses ***
  Double_t clight = 299.792458;
  //Double_t mPiplus = 139.57018;
  Double_t mKplus = 493.677;
  //Double_t mJpsi = 3096.916;
  Double_t mBd = 5279.58;
  Double_t msigma = 50;

  // *** Plot Ranges ***
  //Double_t Bmass_min = 5180;
  //Double_t Bmass_max = 5520;


// ***** Part I: From NTuple to DataSet ***** //
////////////////////////////////////////////////

// This is done to easily handle the selection cuts and allows semi-automatic looping over these cuts

  std::cout << " " << std::endl;
  std::cout << "== Part I: From NTuple to DataSet ==" << std::endl;
  std::cout << "====================================" << std::endl;

  // ***** Load NTuples ***** //
  //////////////////////////////

  TChain* chain = new TChain("chain");
  chain->Add("B2JpsiKs-Slim-LHCb2011.root/Slim_B2JpsiKs_Tuple");
  
  Long64_t nEntries = chain->GetEntries();
  std::cout << "Number of entries from DaVinci: " << nEntries << std::endl;    


  // ***** Define DataSet Observables ***** //
  ////////////////////////////////////////////

  // *** Define Observables & Selection Variables ***
        
  // Selection Cuts
  Float_t B_FullFit_M[10];
  Int_t piminus_TRACK_Type = -999;
  // Observables for Common Selection Cuts
  Int_t B_FullFit_nPV = -999;
  Float_t B_FullFit_ctau[10];
	Float_t B_FullFit_status[10];
	Float_t B_FullFit_chi2[10];
  Float_t B_FullFit_MERR[10];
	Float_t B_FullFit_PV_Z[10];
  // Observables for Decay Specific Cuts
  Double_t Psi_PE = -999;
  Double_t piplus_PE = -999;
  Double_t piminus_PE = -999;
  Double_t Psi_PX = -999;
  Double_t piplus_PX = -999;
  Double_t piminus_PX = -999;
  Double_t Psi_PY = -999;
  Double_t piplus_PY = -999;
  Double_t piminus_PY = -999;
  Double_t Psi_PZ = -999;
  Double_t piplus_PZ = -999;
  Double_t piminus_PZ = -999;
	Double_t KS0_M_with_pplus_piplus = -999;
	Double_t KS0_M_with_piplus_pplus = -999;
	Float_t B_FullFit_KS0_ctau[10];
  Float_t B_FullFit_KS0_ctauErr[10];
  // Trigger
  Bool_t PsiHlt1TrackMuonDecision_TOS = -999;
  Bool_t PsiHlt1DiMuonHighMassDecision_TOS = -999; 
  Bool_t PsiHlt1TrackAllL0Decision_TOS = -999;
  Bool_t PsiHlt2DiMuonDetachedJPsiDecision_TOS = -999; 
  Bool_t PsiHlt2DiMuonJPsiHighPTDecision_TOS = -999;
  Bool_t PsiHlt2DiMuonJPsiDecision_TOS = -999;
  Bool_t PsiHlt2TopoMu2BodyBBDTDecision_TOS = -999; 

  // *** Initialize Arrays ***
  for(Int_t i=0; i<10; i++){
		B_FullFit_ctau[i] = -999;
    B_FullFit_M[i] = -999;
    B_FullFit_status[i] = -999;
    B_FullFit_chi2[i] = -999;
    B_FullFit_MERR[i] = -999;
    B_FullFit_PV_Z[i] = -999;
    B_FullFit_KS0_ctau[i] = -999;
    B_FullFit_KS0_ctauErr[i] = -999;
  }


  // *** Set Branch Addresses ***
  // Selection Cuts
  chain->SetBranchAddress("B_FullFit_M", &B_FullFit_M);
  chain->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type);
  // Observables for Common Selection Cuts
  chain->SetBranchAddress("B_FullFit_nPV", &B_FullFit_nPV);
  chain->SetBranchAddress("B_FullFit_ctau", &B_FullFit_ctau);
  chain->SetBranchAddress("B_FullFit_status", &B_FullFit_status);
  chain->SetBranchAddress("B_FullFit_chi2", &B_FullFit_chi2);
  chain->SetBranchAddress("B_FullFit_MERR", &B_FullFit_MERR);
  chain->SetBranchAddress("B_FullFit_PV_Z", &B_FullFit_PV_Z);
  // Observables for Decay Specific Cuts
  chain->SetBranchAddress("Psi_PE", &Psi_PE);
  chain->SetBranchAddress("piplus_PE", &piplus_PE);
  chain->SetBranchAddress("piminus_PE", &piminus_PE);
  chain->SetBranchAddress("Psi_PX", &Psi_PX);
  chain->SetBranchAddress("piplus_PX", &piplus_PX);
  chain->SetBranchAddress("piminus_PX", &piminus_PX);
  chain->SetBranchAddress("Psi_PY", &Psi_PY);
  chain->SetBranchAddress("piplus_PY", &piplus_PY);
  chain->SetBranchAddress("piminus_PY", &piminus_PY);
  chain->SetBranchAddress("Psi_PZ", &Psi_PZ);
  chain->SetBranchAddress("piplus_PZ", &piplus_PZ);
  chain->SetBranchAddress("piminus_PZ", &piminus_PZ);
  chain->SetBranchAddress("KS0_M_with_pplus_piplus", &KS0_M_with_pplus_piplus);
  chain->SetBranchAddress("KS0_M_with_piplus_pplus", &KS0_M_with_piplus_pplus);
  chain->SetBranchAddress("B_FullFit_KS0_ctau", &B_FullFit_KS0_ctau);
  chain->SetBranchAddress("B_FullFit_KS0_ctauErr", &B_FullFit_KS0_ctauErr);
  // Trigger
  chain->SetBranchAddress("PsiHlt1TrackMuonDecision_TOS", &PsiHlt1TrackMuonDecision_TOS);
  chain->SetBranchAddress("PsiHlt1DiMuonHighMassDecision_TOS", &PsiHlt1DiMuonHighMassDecision_TOS);
  chain->SetBranchAddress("PsiHlt1TrackAllL0Decision_TOS", &PsiHlt1TrackAllL0Decision_TOS);  
  chain->SetBranchAddress("PsiHlt2DiMuonDetachedJPsiDecision_TOS", &PsiHlt2DiMuonDetachedJPsiDecision_TOS);
  chain->SetBranchAddress("PsiHlt2DiMuonJPsiHighPTDecision_TOS", &PsiHlt2DiMuonJPsiHighPTDecision_TOS);
  chain->SetBranchAddress("PsiHlt2DiMuonJPsiDecision_TOS", &PsiHlt2DiMuonJPsiDecision_TOS);
  chain->SetBranchAddress("PsiHlt2TopoMu2BodyBBDTDecision_TOS",&PsiHlt2TopoMu2BodyBBDTDecision_TOS);

  // ***** Initialize DataSet ***** //
  ////////////////////////////////////

  // *** Observable ***
  //RooRealVar *Bmass = new RooRealVar("Bmass","mass",Bmass_min,Bmass_max,"MeV/c^{2}");
  RooRealVar *Bmass = new RooRealVar("Bmass","mass",0,"MeV/c^{2}");
  RooRealVar *weight = new RooRealVar("weight","Weight for Normalisation", 0.,1.);

  // *** DataSet ***
  RooArgSet *Obs = new RooArgSet(*Bmass,*weight);
  
  RooDataSet *data_Kstar_Khypo_Weight = new RooDataSet("data_Kstar_Khypo_Weight","Unbinned dataset",*Obs, WeightVar(*weight));
  RooDataSet *data_Bd_Khypo_Weight = new RooDataSet("data_Bd_Khypo_Weight","Unbinned dataset",*Obs, WeightVar(*weight));
  RooDataSet *data_Bkg_Khypo_Weight = new RooDataSet("data_Bkg_Khypo_Weight","Unbinned dataset",*Obs, WeightVar(*weight));

  // ***** Loop over Entries ***** //
  ///////////////////////////////////

  Double_t KminusMass = 0;
  Double_t KplusMass = 0;
  bool SelCuts = false;
  bool Trigger = false;

  std::cout << " " << std::endl;
  std::cout << "== Loop: Bd->JpsiKs ==" << std::endl;
  std::cout << "======================" << std::endl;

  Int_t Kstar_All = 0;
  Int_t Bd_All = 0;
  Int_t Bkg_All = 0;
  
  std::cout << "Count" << std::endl;
  for(Long64_t i=0; i<nEntries; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries << " (" << 100*i/nEntries << "%)" << std::endl;


    for(Int_t pv = 0; pv < B_FullFit_nPV ; pv++){
      //Trigger
      Trigger = (PsiHlt1TrackMuonDecision_TOS || PsiHlt1DiMuonHighMassDecision_TOS || PsiHlt1TrackAllL0Decision_TOS) &&
                (PsiHlt2DiMuonDetachedJPsiDecision_TOS || PsiHlt2DiMuonJPsiHighPTDecision_TOS || PsiHlt2DiMuonJPsiDecision_TOS ||
                 PsiHlt2TopoMu2BodyBBDTDecision_TOS);
    
      // Selection Cuts
      SelCuts = (B_FullFit_M[pv]>5180 && B_FullFit_M[pv]<5520 && B_FullFit_status[pv]==0 && B_FullFit_chi2[pv]<72 &&
        B_FullFit_MERR[pv]<30 && B_FullFit_ctau[pv]/clight>0.0002 && TMath::Abs(B_FullFit_PV_Z[pv])<250 &&
        TMath::Abs(KS0_M_with_pplus_piplus-1116)>2*piminus_TRACK_Type &&
        TMath::Abs(KS0_M_with_piplus_pplus-1116)>2*piminus_TRACK_Type &&
        B_FullFit_KS0_ctau[pv]/B_FullFit_KS0_ctauErr[pv]>5
        );

      if(SelCuts && Trigger && piminus_TRACK_Type==3){
        if(B_FullFit_M[pv]<(mBd-msigma)) Kstar_All++;
        else if(B_FullFit_M[pv]>(mBd-msigma) && B_FullFit_M[pv]<(mBd+msigma)) Bd_All++;
        else Bkg_All++;
      }
    }
  }

  std::cout << "Fill" << std::endl;
  for(Long64_t i=0; i<nEntries; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries << " (" << 100*i/nEntries << "%)" << std::endl;

    for(Int_t pv = 0; pv < B_FullFit_nPV ; pv++){
      //Trigger
      Trigger = (PsiHlt1TrackMuonDecision_TOS || PsiHlt1DiMuonHighMassDecision_TOS || PsiHlt1TrackAllL0Decision_TOS) &&
                (PsiHlt2DiMuonDetachedJPsiDecision_TOS || PsiHlt2DiMuonJPsiHighPTDecision_TOS || PsiHlt2DiMuonJPsiDecision_TOS ||
                 PsiHlt2TopoMu2BodyBBDTDecision_TOS);
    
      // Selection Cuts
      SelCuts = (B_FullFit_M[pv]>5180 && B_FullFit_M[pv]<5520 && B_FullFit_status[pv]==0 && B_FullFit_chi2[pv]<72 &&
        B_FullFit_MERR[pv]<30 && B_FullFit_ctau[pv]/clight>0.0002 && TMath::Abs(B_FullFit_PV_Z[pv])<250 &&
        TMath::Abs(KS0_M_with_pplus_piplus-1116)>2*piminus_TRACK_Type &&
        TMath::Abs(KS0_M_with_piplus_pplus-1116)>2*piminus_TRACK_Type &&
        B_FullFit_KS0_ctau[pv]/B_FullFit_KS0_ctauErr[pv]>5
        );

      if(SelCuts && Trigger && piminus_TRACK_Type==3){
        
        KminusMass = TMath::Sqrt(pow(Psi_PE + piplus_PE + TMath::Sqrt(pow(mKplus,2) + pow(piminus_PX,2) + pow(piminus_PY,2) + pow(piminus_PZ,2)),2) - pow(Psi_PX+piplus_PX+piminus_PX,2) - pow(Psi_PY+piplus_PY+piminus_PY,2) - pow(Psi_PZ+piplus_PZ+piminus_PZ,2));
        KplusMass = TMath::Sqrt(pow(Psi_PE + piminus_PE + TMath::Sqrt(pow(mKplus,2) + pow(piplus_PX,2) + pow(piplus_PY,2) + pow(piplus_PZ,2)),2) - pow(Psi_PX+piplus_PX+piminus_PX,2) - pow(Psi_PY+piplus_PY+piminus_PY,2) - pow(Psi_PZ+piplus_PZ+piminus_PZ,2));
        Bmass->setVal(KminusMass);
        
        if(B_FullFit_M[pv]<(mBd-msigma)){
          weight->setVal((double) 1./Kstar_All);
          data_Kstar_Khypo_Weight->add(*Obs, weight->getVal());
        }
        else if(B_FullFit_M[pv]>(mBd-msigma) && B_FullFit_M[pv]<(mBd+msigma)){
          weight->setVal((double) 1./Bd_All);
          data_Bd_Khypo_Weight->add(*Obs, weight->getVal());
        }
        else{
          weight->setVal((double) 1./Bkg_All);
          data_Bkg_Khypo_Weight->add(*Obs, weight->getVal());
        }
      }
    }
  }

  // ***** Plot ***** //
  //////////////////////

    
  // *** Frame ***
  RooPlot* CompareFrame = Bmass->frame(Range(5180,5520),Bins(68));

    // Titles
  CompareFrame->SetYTitle("Events/(5 MeV/c^{2})");
  CompareFrame->SetXTitle("m_{J/#psi K^{+}#pi^{-}} #scale[0.8]{(MeV/c^{2})}");

    // Cosmetics
  CompareFrame->SetTitleOffset(1.2,"y");
  CompareFrame->SetTitleOffset(0.9,"x");
  CompareFrame->SetTitleSize(0.07,"x");
  CompareFrame->SetTitleSize(0.07,"y");
  CompareFrame->SetTitleFont(132,"y");
  CompareFrame->SetTitleFont(132,"x");
  CompareFrame->SetLabelSize(0.05,"y");
  CompareFrame->SetLabelSize(0.05,"x");
  CompareFrame->SetLabelFont(132,"x");
  CompareFrame->SetLabelFont(132,"y");

  data_Kstar_Khypo_Weight->plotOn(CompareFrame,MarkerStyle(22),MarkerSize(1),MarkerColor(3),LineColor(3));
  data_Bd_Khypo_Weight->plotOn(CompareFrame,MarkerStyle(21),MarkerSize(0.8),MarkerColor(2),LineColor(2));
  data_Bkg_Khypo_Weight->plotOn(CompareFrame,MarkerStyle(23),MarkerSize(1),MarkerColor(4),LineColor(4));
  
  CompareFrame->SetMinimum(0.0001);
  CompareFrame->SetMaximum(1);
  
  // *** Canvas ***
  TCanvas* doek_Compare = new TCanvas("doek_Compare","Observable",900,800);
  doek_Compare->SetLeftMargin(0.2);
  doek_Compare->SetBottomMargin(0.15);
  doek_Compare->cd(1);
  
  // *** Frame ***
  gPad->SetLogy(1);
  CompareFrame->Draw();
  
  // *** Exclusion Box ***
  TBox* box = new TBox(vetoMin,0,vetoMax,1);
  box->SetFillColor(18);
  box->Draw();
  CompareFrame->Draw("same");
  
  
  // *** LHCb Tag *** 
  TPaveText *lhcbTag = new TPaveText(0.60,0.80,0.89,0.89,"NDC");

  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  lhcbTag->AddText("#splitline{LHCb 2011}{#scale[0.7]{Reco 12 - Stripping 17b}}");
  lhcbTag -> Draw("");
  
  // *** Legend ***
  // Very nasty trick to get the dot in he legend in the correct color
  Float_t red_point[2];
  red_point[0] = 0;
  red_point[1] = 1;
  TGraph *red_contour = new TGraph(2,red_point,red_point);
  red_contour->SetMarkerStyle(21);
  red_contour->SetMarkerSize(0.8);
  red_contour->SetMarkerColor(2);
  red_contour->SetLineColor(2);
  
  Float_t green_point[2];
  green_point[0] = 0;
  green_point[1] = 1;
  TGraph *green_contour = new TGraph(2,green_point,green_point);
  green_contour->SetMarkerStyle(22);
  green_contour->SetMarkerSize(0.8);
  green_contour->SetMarkerColor(3);
  green_contour->SetLineColor(3);
  
  Float_t blue_point[2];
  blue_point[0] = 0;
  blue_point[1] = 1;
  TGraph *blue_contour = new TGraph(2,blue_point,blue_point);
  blue_contour->SetMarkerStyle(23);
  blue_contour->SetMarkerSize(0.8);
  blue_contour->SetMarkerColor(4);
  blue_contour->SetLineColor(4);
  
  TLegend *leg = new TLegend(0.49,0.65,0.89,0.80);
  leg->AddEntry(green_contour,"5180 < m_{J/#psi K_{S}^{0}} < 5229 MeV/c^{2}","lep");
  leg->AddEntry(red_contour,"5229 < m_{J/#psi K_{S}^{0}} < 5339 MeV/c^{2}","lep");
  leg->AddEntry(blue_contour,"5339 < m_{J/#psi K_{S}^{0}} < 5520 MeV/c^{2}","lep");
  leg->SetTextAlign(12);
  leg->SetTextSize(0.03);
  leg->SetTextFont(132);
  leg->Draw("");

  Float_t black_pointx[4];
  black_pointx[0] = vetoMin;
  black_pointx[1] = black_pointx[0];
  black_pointx[2] = vetoMax;
  black_pointx[3] = black_pointx[2];
  Float_t black_pointy[4];
  black_pointy[0] = 0;
  black_pointy[1] = 1.1;
  black_pointy[2] = black_pointy[1];
  black_pointy[3] = black_pointy[0];
  TGraph *black_contour = new TGraph(4,black_pointx,black_pointy);
  black_contour->SetLineColor(1);
  black_contour->SetLineWidth(2);
  black_contour->Draw("");
  
  
  // *** Save ***
  doek_Compare->SaveAs("Kstar_Veto_RD.pdf");

}