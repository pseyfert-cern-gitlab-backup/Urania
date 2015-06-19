////////////////////////////////////////////////////////////////////
// ***** Study the Trigger Efficiency as a Function of Mass ***** //
////////////////////////////////////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb
// - Study the Trigger Efficiency as a Function of Mass


/////////////////////////////////////
// ***** Load useful classes ***** //
/////////////////////////////////////

#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooCategory.h"
#include "RooCBShape.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooFit.h"
#include "RooRealVar.h"

#include "RooStats/SPlot.h"

#include "TChain.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TMath.h"
#include "TNtuple.h"

using namespace RooFit;

//////////////////////////////
// ***** Declarations ***** //
//////////////////////////////
void MCNNData(TString what, Double_t *Results_LL, Double_t *Results_DD);
void PrintEntries(RooDataSet *data, Double_t *Results);


///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void MCNNEff(){

  // *** Bd->JpsiKs ***
  std::cout << "=== SigBd ===" << std::endl;
  std::cout << "=============" << std::endl;
  Double_t results_Bd_LL[] = {-999,-999};
  Double_t results_Bd_DD[] = {-999,-999};
  MCNNData("SigBd",results_Bd_LL, results_Bd_DD);
  
  // *** Bs->JpsiKs ***
  std::cout << "=== SigBs ===" << std::endl;
  std::cout << "=============" << std::endl;
  Double_t results_Bs_LL[] = {-999,-999};
  Double_t results_Bs_DD[] = {-999,-999};
  MCNNData("SigBs",results_Bs_LL, results_Bs_DD);
  
  // *** Difference ***
  Double_t Diff_NN_LL_Val = results_Bd_LL[0]-results_Bs_LL[0];
  Double_t Diff_NN_LL_Err = TMath::Sqrt(pow(results_Bd_LL[1],2)+pow(results_Bs_LL[1],2));
  Double_t Eff_NN_LL_Val = results_Bd_LL[0]/results_Bs_LL[0];
  Double_t Eff_NN_LL_Err = TMath::Sqrt(pow(results_Bd_LL[1]/results_Bs_LL[0],2) + pow(results_Bd_LL[0]*results_Bs_LL[1]/pow(results_Bs_LL[0],2),2));
  Double_t Diff_NN_DD_Val = results_Bd_DD[0]-results_Bs_DD[0];
  Double_t Diff_NN_DD_Err = TMath::Sqrt(pow(results_Bd_DD[1],2)+pow(results_Bs_DD[1],2));
  Double_t Eff_NN_DD_Val = results_Bd_DD[0]/results_Bs_DD[0];
  Double_t Eff_NN_DD_Err = TMath::Sqrt(pow(results_Bd_DD[1]/results_Bs_DD[0],2) + pow(results_Bd_DD[0]*results_Bs_DD[1]/pow(results_Bs_DD[0],2),2));
  
  
  std::cout << "=== Difference ===" << std::endl;
  std::cout << "==================" << std::endl;
  std::cout << std::endl;
  std::cout << "=== Long KS ===" << std::endl;
  std::cout << "Difference: " << Diff_NN_LL_Val << " +/- " << Diff_NN_LL_Err << " => Sig: " << Diff_NN_LL_Val/Diff_NN_LL_Err << std::endl;
  std::cout << "Eff Ration: " << Eff_NN_LL_Val << " +/- " << Eff_NN_LL_Err << std::endl;
  std::cout << std::endl;
  std::cout << "=== Down KS ===" << std::endl;
  std::cout << "Difference: " << Diff_NN_DD_Val << " +/- " << Diff_NN_DD_Err << " => Sig: " << Diff_NN_DD_Val/Diff_NN_DD_Err << std::endl;
  std::cout << "Eff Ration: " << Eff_NN_DD_Val << " +/- " << Eff_NN_DD_Err << std::endl;
  std::cout << std::endl;
  
}

/////////////////////////////////
// ***** Helper Function ***** //
/////////////////////////////////
void MCNNData(TString what, Double_t *Results_LL, Double_t *Results_DD){

// ***** Initialize ***** //
////////////////////////////

  // *** Neural Net ***
  Double_t NNcut_LL = 0.60;
  Double_t NNcut_DD = 0.75;
  
  // *** Plot Settings ***
  Double_t Bmass_min = 5180;
  Double_t Bmass_max = 5520;
  
  // *** Constants ***
  Double_t clight = 299.792458;
  Double_t m_Kplus = 493.677;
  Double_t m_BdPDG = 5279.58;


// ***** Part I: From NTuple to DataSet ***** //
////////////////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Part I: From NTuple to DataSet ==" << std::endl;
  std::cout << "====================================" << std::endl;

  // ***** Load NTuples ***** //
  //////////////////////////////
  
  TFile* netFile = TFile::Open("B2JpsiKs-Eval-2-random-"+what+".root");
  TTree* neural_net = (TTree*)netFile->Get("NetTree");

  TChain* chain = new TChain("chain");
  chain->Add("B2JpsiKs-Slim-"+what+".root/Slim_B2JpsiKs_Tuple");
  chain->AddFriend(neural_net);
  
  Long64_t nEntries_NTuple = chain->GetEntries();
  //nEntries_NTuple = 10000;  
  std::cout << "Number of entries from DaVinci: " << nEntries_NTuple << std::endl;    


  // ***** Define DataSet Observables ***** //
  ////////////////////////////////////////////

  // *** Define Observables & Selection Variables ***

  // Observable
  Float_t B_FullFit_M[10];
  Int_t piminus_TRACK_Type = -999;
  // PV Matching
  Float_t B_FullFit_PV_X[10];
  Float_t B_FullFit_PV_Y[10];
  Float_t B_FullFit_PV_Z[10];
  // Observables for Common Selection Cuts
  Float_t B_FullFit_ctau[10];
	Float_t B_FullFit_status[10];
	Float_t B_FullFit_chi2[10];
  Float_t B_FullFit_MERR[10];
	//Float_t B_FullFit_PV_Z[10];
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
  Bool_t PsiL0Global_Dec = -999;
  Bool_t PsiHlt1Global_Dec = -999;
  Bool_t PsiHlt2Global_Dec = -999;
  // Neural Net
  Float_t netOutput[10];
  Int_t nPV2 = -999;
  // True ID of Decay
  Int_t B_TRUEID = -999;
  Int_t Psi_TRUEID = -999;
  Int_t KS0_TRUEID = -999;
  Int_t B_BKGCAT = -999;
  Double_t B_TRUEORIGINVERTEX_X = -999;
  Double_t B_TRUEORIGINVERTEX_Y = -999;
  Double_t B_TRUEORIGINVERTEX_Z = -999;
  
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
    netOutput[i] = -999;
  }
  

  // *** Set Branch Addresses ***
  // Observable
  chain->SetBranchAddress("B_FullFit_M", &B_FullFit_M);
  chain->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type);
  // PV Matching
  chain->SetBranchAddress("B_FullFit_PV_X", &B_FullFit_PV_X);
  chain->SetBranchAddress("B_FullFit_PV_Y", &B_FullFit_PV_Y);
  chain->SetBranchAddress("B_FullFit_PV_Z", &B_FullFit_PV_Z);
  // Observables for Common Selection Cuts
  chain->SetBranchAddress("B_FullFit_ctau", &B_FullFit_ctau);
  chain->SetBranchAddress("B_FullFit_status", &B_FullFit_status);
  chain->SetBranchAddress("B_FullFit_chi2", &B_FullFit_chi2);
  chain->SetBranchAddress("B_FullFit_MERR", &B_FullFit_MERR);
  //chain->SetBranchAddress("B_FullFit_PV_Z", &B_FullFit_PV_Z);
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
  chain->SetBranchAddress("PsiL0Global_Dec",&PsiL0Global_Dec);
  chain->SetBranchAddress("PsiHlt1Global_Dec",&PsiHlt1Global_Dec);
  chain->SetBranchAddress("PsiHlt2Global_Dec",&PsiHlt2Global_Dec);
  // Neural Net
  chain->SetBranchAddress("netOutput", &netOutput);
  chain->SetBranchAddress("nPV2", &nPV2);
  // True ID of Decay
  chain->SetBranchAddress("B_TRUEID", &B_TRUEID);
  chain->SetBranchAddress("Psi_TRUEID", &Psi_TRUEID);
  chain->SetBranchAddress("KS0_TRUEID", &KS0_TRUEID);
  chain->SetBranchAddress("B_BKGCAT", &B_BKGCAT);
  chain->SetBranchAddress("B_TRUEORIGINVERTEX_X", &B_TRUEORIGINVERTEX_X);
  chain->SetBranchAddress("B_TRUEORIGINVERTEX_Y", &B_TRUEORIGINVERTEX_Y);
  chain->SetBranchAddress("B_TRUEORIGINVERTEX_Z", &B_TRUEORIGINVERTEX_Z);
  

  // ***** Initialize DataSet ***** //
  ////////////////////////////////////

  // *** Observable ***
  RooRealVar *Bmass = new RooRealVar("Bmass","mass",Bmass_min,Bmass_max,"MeV/c^{2}");
	RooCategory *NNDec = new RooCategory("NNDec","Does event pass NN?");
  NNDec->defineType("Accept",1);
  NNDec->defineType("Reject",0);

  // *** DataSet ***
  RooArgSet *Obs = new RooArgSet(*Bmass,*NNDec);
  RooDataSet *data_LL = new RooDataSet("data_LL","Unbinned dataset",*Obs);
  RooDataSet *data_DD = new RooDataSet("data_DD","Unbinned dataset",*Obs);


  // ***** Loop over Entries: Apply Selection Cuts ***** //
  /////////////////////////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Loop 1: Selection Cuts ==" << std::endl;
  std::cout << "============================" << std::endl;

  // Initialise
  Double_t DOCA = 0;
  Double_t DOCA_min = 999;
  Int_t truePV = 0;
  
  bool TruthMatch = false;
  bool SelCuts = false;
  bool KstarVeto = false;
  Double_t Kstar_minMass = 0;
  Double_t Kstar_plusMass = 0;
  bool Hlt1 = false;
  bool Hlt2 = false;
  bool NN = false;

  for(Long64_t i=0; i<nEntries_NTuple; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_NTuple << " (" << 100*i/nEntries_NTuple << "%)" << std::endl;

    if(what=="SigBd") TruthMatch = (TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && (B_BKGCAT==0 || B_BKGCAT==10));
    else if(what=="SigBs") TruthMatch = (TMath::Abs(B_TRUEID)==531 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && (B_BKGCAT==20));

    if(TruthMatch){ // Select only True Signal
        
      // Loop 1: Determine DOCA
      for(Int_t pv = 0; pv < nPV2 ; pv++){ 
        DOCA = TMath::Sqrt(pow(B_TRUEORIGINVERTEX_X-B_FullFit_PV_X[pv],2) + pow(B_TRUEORIGINVERTEX_Y-B_FullFit_PV_Y[pv],2) + pow(B_TRUEORIGINVERTEX_Z-B_FullFit_PV_Z[pv],2));
        if(DOCA<DOCA_min){
          DOCA_min = DOCA;
          truePV = pv;
        }
      }

      SelCuts = (B_FullFit_status[truePV]==0 && B_FullFit_chi2[truePV]<72 && B_FullFit_MERR[truePV]<30 &&
            B_FullFit_ctau[truePV]/clight>0.0002 && TMath::Abs(B_FullFit_PV_Z[truePV])<250 &&
            TMath::Abs(KS0_M_with_pplus_piplus-1116)>2*piminus_TRACK_Type &&
            TMath::Abs(KS0_M_with_piplus_pplus-1116)>2*piminus_TRACK_Type &&
            B_FullFit_KS0_ctau[truePV]/B_FullFit_KS0_ctauErr[truePV]>5
            );
      Kstar_minMass = TMath::Sqrt(pow(Psi_PE + piplus_PE
            + TMath::Sqrt(pow(m_Kplus,2) + pow(piminus_PX,2) + pow(piminus_PY,2) + pow(piminus_PZ,2)),2)
            - pow(Psi_PX+piplus_PX+piminus_PX,2) - pow(Psi_PY+piplus_PY+piminus_PY,2) - pow(Psi_PZ+piplus_PZ+piminus_PZ,2));
      Kstar_plusMass = TMath::Sqrt(pow(Psi_PE + piminus_PE
            + TMath::Sqrt(pow(m_Kplus,2) + pow(piplus_PX,2) + pow(piplus_PY,2) + pow(piplus_PZ,2)),2)
            - pow(Psi_PX+piplus_PX+piminus_PX,2) - pow(Psi_PY+piplus_PY+piminus_PY,2) - pow(Psi_PZ+piplus_PZ+piminus_PZ,2));
        
      KstarVeto = (piminus_TRACK_Type==5 || (piminus_TRACK_Type==3 && 
                TMath::Abs(Kstar_minMass-m_BdPDG)>20 && TMath::Abs(Kstar_plusMass-m_BdPDG)>20));
      Hlt1 = (PsiHlt1TrackMuonDecision_TOS || PsiHlt1DiMuonHighMassDecision_TOS || PsiHlt1TrackAllL0Decision_TOS);
      Hlt2 = (PsiHlt2DiMuonDetachedJPsiDecision_TOS || PsiHlt2DiMuonJPsiHighPTDecision_TOS || PsiHlt2DiMuonJPsiDecision_TOS ||PsiHlt2TopoMu2BodyBBDTDecision_TOS);
      // Loop 2: Fill
      if(PsiL0Global_Dec && PsiHlt1Global_Dec && PsiHlt2Global_Dec && Hlt1 && Hlt2 && SelCuts && KstarVeto){
        NN = ((piminus_TRACK_Type==3 && netOutput[truePV]>NNcut_LL) || (piminus_TRACK_Type==5 && netOutput[truePV]>NNcut_DD));
      
        Bmass->setVal(B_FullFit_M[truePV]);
        if(NN) NNDec->setLabel("Accept");
        else NNDec->setLabel("Reject");
        
        if(piminus_TRACK_Type==3) data_LL->add(*Obs);
        else if(piminus_TRACK_Type==5) data_DD->add(*Obs);
      }
    }
    // Reset
    DOCA_min = 999;
  }

  // Free Memory
  delete chain;

// ***** Part II: Efficiencies ***** //
///////////////////////////////////////  

  std::cout << std::endl;
  std::cout << "== Part II: Efficiencies ==" << std::endl;
  std::cout << "===========================" << std::endl;

  std::cout << "=== Long KS ===" << std::endl;
  std::cout << "===============" << std::endl;
  PrintEntries(data_LL, Results_LL);

  std::cout << "=== Down KS ===" << std::endl;
  std::cout << "===============" << std::endl;
  PrintEntries(data_DD, Results_DD);

}

/////////////////////////////////
// ***** Helper Function ***** //
/////////////////////////////////
void PrintEntries(RooDataSet *data, Double_t *Results){

  // *** Number of Events ***
  Double_t nEvents_All = data->numEntries();
  
  RooDataSet *data_NN = (RooDataSet *) data->reduce("NNDec==1");
  Double_t nEvents_NN = data_NN->numEntries();
  delete data_NN;
  
  // *** Efficiencies ***
  Results[0] = nEvents_NN/nEvents_All;
  Results[1] = TMath::Sqrt((nEvents_NN*nEvents_All + pow(nEvents_NN,2))/pow(nEvents_All,3));

  // *** Output ***
  std::cout << "NN: " << nEvents_NN << "/" << nEvents_All << " = " << Results[0] << " +/- " << Results[1] << std::endl;
  std::cout << std::endl;
  
}
