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
void MCTriggerData(TString what, Double_t *Results_LL, Double_t *Results_DD);
void PrintEntries(RooDataSet *data, Double_t *Results);

void PrintsWeights(RooDataSet *data);


///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void MCTriggerEff(){

  // *** Bd->JpsiKs ***
  std::cout << "=== SigBd ===" << std::endl;
  std::cout << "=============" << std::endl;
  Double_t results_Bd_LL[] = {-999,-999,-999,-999};
  Double_t results_Bd_DD[] = {-999,-999,-999,-999};
  MCTriggerData("SigBd",results_Bd_LL, results_Bd_DD);
  
  // *** Bs->JpsiKs ***
  std::cout << "=== SigBs ===" << std::endl;
  std::cout << "=============" << std::endl;
  Double_t results_Bs_LL[] = {-999,-999,-999,-999};
  Double_t results_Bs_DD[] = {-999,-999,-999,-999};
  MCTriggerData("SigBs",results_Bs_LL, results_Bs_DD);
  
  // *** Difference ***
  Double_t Diff_Hlt1_LL_Val = results_Bd_LL[0]-results_Bs_LL[0];
  Double_t Diff_Hlt1_LL_Err = TMath::Sqrt(pow(results_Bd_LL[1],2)+pow(results_Bs_LL[1],2));
  Double_t Diff_Hlt2_LL_Val = results_Bd_LL[2]-results_Bs_LL[2];
  Double_t Diff_Hlt2_LL_Err = TMath::Sqrt(pow(results_Bd_LL[3],2)+pow(results_Bs_LL[3],2));
  
  Double_t Diff_Hlt1_DD_Val = results_Bd_DD[0]-results_Bs_DD[0];
  Double_t Diff_Hlt1_DD_Err = TMath::Sqrt(pow(results_Bd_DD[1],2)+pow(results_Bs_DD[1],2));
  Double_t Diff_Hlt2_DD_Val = results_Bd_DD[2]-results_Bs_DD[2];
  Double_t Diff_Hlt2_DD_Err = TMath::Sqrt(pow(results_Bd_DD[3],2)+pow(results_Bs_DD[3],2));
  
  
  std::cout << "=== Difference ===" << std::endl;
  std::cout << "==================" << std::endl;
  std::cout << std::endl;
  std::cout << "=== Long KS ===" << std::endl;
  std::cout << "Hlt1: " << Diff_Hlt1_LL_Val << " +/- " << Diff_Hlt1_LL_Err << " => Sig: " << Diff_Hlt1_LL_Val/Diff_Hlt1_LL_Err << std::endl;
  std::cout << "Hlt1 & Hlt2: " << Diff_Hlt2_LL_Val << " +/- " << Diff_Hlt2_LL_Err << " => Sig: " << Diff_Hlt2_LL_Val/Diff_Hlt2_LL_Err << std::endl;
  std::cout << std::endl;
  std::cout << "=== Down KS ===" << std::endl;
  std::cout << "Hlt1: " << Diff_Hlt1_DD_Val << " +/- " << Diff_Hlt1_DD_Err << " => Sig: " << Diff_Hlt1_DD_Val/Diff_Hlt1_DD_Err << std::endl;
  std::cout << "Hlt1 & Hlt2: " << Diff_Hlt2_DD_Val << " +/- " << Diff_Hlt2_DD_Err << " => Sig: " << Diff_Hlt2_DD_Val/Diff_Hlt2_DD_Err << std::endl;
  std::cout << std::endl;
  
}

/////////////////////////////////
// ***** Helper Function ***** //
/////////////////////////////////
void MCTriggerData(TString what, Double_t *Results_LL, Double_t *Results_DD){

// ***** Initialize ***** //
////////////////////////////

  // *** Neural Net ***
  Double_t NNcut_LL = 0.60;
  Double_t NNcut_DD = 0.75;
  
  // *** Plot Settings ***
  Double_t Bmass_min = 5180;
  Double_t Bmass_max = 5520;


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
    B_FullFit_M[i] = -999;
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
	RooCategory *Hlt1_Trigger = new RooCategory("Hlt1_Trigger","Is the event triggered?");
  Hlt1_Trigger->defineType("Accept",1);
  Hlt1_Trigger->defineType("Reject",0);
	RooCategory *Hlt2_Trigger = new RooCategory("Hlt2_Trigger","Is the event triggered?");
  Hlt2_Trigger->defineType("Accept",1);
  Hlt2_Trigger->defineType("Reject",0);

  // *** DataSet ***
  RooArgSet *Obs = new RooArgSet(*Bmass,*Hlt1_Trigger,*Hlt2_Trigger);
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
  bool NN = false;
  bool Hlt1 = false;
  bool Hlt2 = false;

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

      // Loop 2: Fill
      NN = ((piminus_TRACK_Type==3 && netOutput[truePV]>NNcut_LL) || (piminus_TRACK_Type==5 && netOutput[truePV]>NNcut_DD));
      if(PsiL0Global_Dec && PsiHlt1Global_Dec && PsiHlt2Global_Dec && NN){
      
        Hlt1 = (PsiHlt1TrackMuonDecision_TOS || PsiHlt1DiMuonHighMassDecision_TOS || PsiHlt1TrackAllL0Decision_TOS);
        Hlt2 = (PsiHlt2DiMuonDetachedJPsiDecision_TOS || PsiHlt2DiMuonJPsiHighPTDecision_TOS || PsiHlt2DiMuonJPsiDecision_TOS ||PsiHlt2TopoMu2BodyBBDTDecision_TOS);
      
        Bmass->setVal(B_FullFit_M[truePV]);
        if(Hlt1) Hlt1_Trigger->setLabel("Accept");
        else Hlt1_Trigger->setLabel("Reject");
        if(Hlt2) Hlt2_Trigger->setLabel("Accept");
        else Hlt2_Trigger->setLabel("Reject");
        
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
  
  RooDataSet *data_Hlt1 = (RooDataSet *) data->reduce("Hlt1_Trigger==1");
  Double_t nEvents_Hlt1 = data_Hlt1->numEntries();
  delete data_Hlt1;
  
  RooDataSet *data_Hlt2 = (RooDataSet *) data->reduce("Hlt1_Trigger==1 && Hlt2_Trigger==1");
  Double_t nEvents_Hlt2 = data_Hlt2->numEntries();
  delete data_Hlt2;
  
  // *** Efficiencies ***
  Results[0] = nEvents_Hlt1/nEvents_All;
  Results[1] = TMath::Sqrt((nEvents_Hlt1*nEvents_All + pow(nEvents_Hlt1,2))/pow(nEvents_All,3));
  Results[2] = nEvents_Hlt2/nEvents_All;
  Results[3] = TMath::Sqrt((nEvents_Hlt2*nEvents_All + pow(nEvents_Hlt2,2))/pow(nEvents_All,3));

  // *** Output ***
  std::cout << "Hlt1: " << nEvents_Hlt1 << "/" << nEvents_All << " = " << Results[0] << " +/- " << Results[1] << std::endl;
  std::cout << "Hlt1 & Hlt2: " << nEvents_Hlt2 << "/" << nEvents_All << " = " << Results[2] << " +/- " << Results[3] << std::endl;
  std::cout << std::endl;
  
}



///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void RDTriggerEff(){

// ***** Initialize ***** //
////////////////////////////

  // *** Neural Net ***
  Double_t NNcut_LL = 0.60;
  Double_t NNcut_DD = 0.75;
  
  // *** Plot Settings ***
  Double_t Bmass_min = 5180;
  Double_t Bmass_max = 5520;


// ***** Part I: From NTuple to DataSet ***** //
////////////////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Part I: From NTuple to DataSet ==" << std::endl;
  std::cout << "====================================" << std::endl;

  // ***** Load NTuples ***** //
  //////////////////////////////
  
  TFile* netFile = TFile::Open("B2JpsiKs-Eval-2-random-LHCb2011-NoTrigger.root");
  TTree* neural_net = (TTree*)netFile->Get("NetTree");

  TChain* chain = new TChain("chain");
  chain->Add("B2JpsiKs-Slim-LHCb2011.root/Slim_B2JpsiKs_Tuple");
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
  // Trigger
  Bool_t PsiHlt1TrackMuonDecision_TOS = -999;
  Bool_t PsiHlt1DiMuonHighMassDecision_TOS = -999; 
  Bool_t PsiHlt1TrackAllL0Decision_TOS = -999;
  Bool_t PsiHlt2DiMuonDetachedJPsiDecision_TOS = -999; 
  Bool_t PsiHlt2DiMuonJPsiHighPTDecision_TOS = -999;
  Bool_t PsiHlt2DiMuonJPsiDecision_TOS = -999;
  Bool_t PsiHlt2TopoMu2BodyBBDTDecision_TOS = -999;
  Bool_t PsiL0Global_Dec = -999;
  Bool_t PsiHlt1Global_TIS = -999;
  Bool_t PsiHlt2Global_TIS = -999; 
  // Neural Net
  Float_t netOutput[10];
  Int_t nPV2 = -999;
  
  // *** Initialize Arrays ***
  for(Int_t i=0; i<10; i++){
    B_FullFit_M[i] = -999;
    netOutput[i] = -999;
  }
  

  // *** Set Branch Addresses ***
  // Observable
  chain->SetBranchAddress("B_FullFit_M", &B_FullFit_M);
  chain->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type);
  // Trigger
  chain->SetBranchAddress("PsiHlt1TrackMuonDecision_TOS", &PsiHlt1TrackMuonDecision_TOS);
  chain->SetBranchAddress("PsiHlt1DiMuonHighMassDecision_TOS", &PsiHlt1DiMuonHighMassDecision_TOS);
  chain->SetBranchAddress("PsiHlt1TrackAllL0Decision_TOS", &PsiHlt1TrackAllL0Decision_TOS);  
  chain->SetBranchAddress("PsiHlt2DiMuonDetachedJPsiDecision_TOS", &PsiHlt2DiMuonDetachedJPsiDecision_TOS);
  chain->SetBranchAddress("PsiHlt2DiMuonJPsiHighPTDecision_TOS", &PsiHlt2DiMuonJPsiHighPTDecision_TOS);
  chain->SetBranchAddress("PsiHlt2DiMuonJPsiDecision_TOS", &PsiHlt2DiMuonJPsiDecision_TOS);
  chain->SetBranchAddress("PsiHlt2TopoMu2BodyBBDTDecision_TOS",&PsiHlt2TopoMu2BodyBBDTDecision_TOS);
  chain->SetBranchAddress("PsiL0Global_Dec",&PsiL0Global_Dec); 
  chain->SetBranchAddress("PsiHlt1Global_TIS",&PsiHlt1Global_TIS);
  chain->SetBranchAddress("PsiHlt2Global_TIS",&PsiHlt2Global_TIS);
  // Neural Net
  chain->SetBranchAddress("netOutput", &netOutput);
  chain->SetBranchAddress("nPV2", &nPV2);
  

  // ***** Initialize DataSet ***** //
  ////////////////////////////////////

  // *** Observable ***
  RooRealVar *Bmass = new RooRealVar("Bmass","mass",Bmass_min,Bmass_max,"MeV/c^{2}");
  RooRealVar *Hlt1Global = new RooRealVar("Hlt1Global","Hlt1Global_TIS decision",0.,1.);
  RooRealVar *Hlt1lines = new RooRealVar("Hlt1lines","Our Hlt1lines decision",0.,1.);
  RooRealVar *Hlt2Global = new RooRealVar("Hlt2Global","Hlt2Global_TIS decision",0.,1.);
  RooRealVar *Hlt2lines = new RooRealVar("Hlt2lines","Our Hlt2lines decision",0.,1.);

  // *** DataSet ***
  RooArgSet *Obs = new RooArgSet(*Bmass,*Hlt1Global,*Hlt1lines,*Hlt2Global,*Hlt2lines);
  RooDataSet *data_LL = new RooDataSet("data_LL","Unbinned dataset",*Obs);
  RooDataSet *data_DD = new RooDataSet("data_DD","Unbinned dataset",*Obs);

  // ***** Loop over Entries: Apply Selection Cuts ***** //
  /////////////////////////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Loop 1: Selection Cuts ==" << std::endl;
  std::cout << "============================" << std::endl;
  
  bool Hlt1 = false;
  bool Hlt2 = false;

  for(Long64_t i=0; i<nEntries_NTuple; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_NTuple << " (" << 100*i/nEntries_NTuple << "%)" << std::endl;


    for(Int_t pv=0; pv<nPV2; pv++){
      if((piminus_TRACK_Type==3 && netOutput[pv]>NNcut_LL) || (piminus_TRACK_Type==5 && netOutput[pv]>NNcut_DD)){;
        Hlt1 = (PsiHlt1TrackMuonDecision_TOS || PsiHlt1DiMuonHighMassDecision_TOS || PsiHlt1TrackAllL0Decision_TOS);
        Hlt2 = (PsiHlt2DiMuonDetachedJPsiDecision_TOS || PsiHlt2DiMuonJPsiHighPTDecision_TOS || PsiHlt2DiMuonJPsiDecision_TOS ||PsiHlt2TopoMu2BodyBBDTDecision_TOS);
      
        Bmass->setVal(B_FullFit_M[pv]);
        if(PsiHlt1Global_TIS) Hlt1Global->setVal(1.);
        else Hlt1Global->setVal(0.);
        if(Hlt1) Hlt1lines->setVal(1.);
        else Hlt1lines->setVal(0.);
        if(PsiHlt2Global_TIS) Hlt2Global->setVal(1.);
        else Hlt2Global->setVal(0.);
        if(Hlt2) Hlt2lines->setVal(1.);
        else Hlt2lines->setVal(0.);
        
        if(piminus_TRACK_Type==3) data_LL->add(*Obs);
        else if(piminus_TRACK_Type==5) data_DD->add(*Obs);
      }
    }
  }

  Int_t nEvents_LL = data_LL->numEntries();
  Int_t nEvents_DD = data_DD->numEntries();
  
  // Free Memory
  delete chain;


// ***** Part II: sWeights ***** //
///////////////////////////////////	

  std::cout << std::endl;
  std::cout << "== Part II: sWeights ==" << std::endl;
  std::cout << "=======================" << std::endl;
  
  // ***** Mass Model ***** //
  ////////////////////////////

  // *** Define Parameters ***  
  RooRealVar *meanBd = new RooRealVar("meanBd","Position of Bd mass peak",5279.5,Bmass_min,Bmass_max);
  RooFormulaVar *meanBs = new RooFormulaVar("meanBs","Position of Bs mass peak","@0+87.52",RooArgList(*meanBd));
  RooRealVar *frac_LL = new RooRealVar("frac_LL","Fraction of model I",0.47134,0.,1.);
  RooRealVar *frac_DD = new RooRealVar("frac_DD","Fraction of model I",0.64519,0.,1.);
  RooRealVar *sigma_I_LL = new RooRealVar("sigma_I_LL","Width of Bd mass peak",5.0722,1.0,25.0);
  RooRealVar *sigma_I_DD = new RooRealVar("sigma_I_DD","Width of Bd mass peak",6.2499,1.0,25.0);
  RooRealVar *sigma_II_LL = new RooRealVar("sigma_II_LL","Width of Bd mass peak",6.9036,1.0,25.0);
  RooRealVar *sigma_II_DD = new RooRealVar("sigma_II_DD","Width of Bd mass peak",10.677,1.0,25.0);
  RooRealVar *apar_I_LL = new RooRealVar("apar_I_LL","A parameter of Crystal Ball I",1.21);
  RooRealVar *apar_I_DD = new RooRealVar("apar_I_DD","A parameter of Crystal Ball I",2.478);
  RooRealVar *apar_II_LL = new RooRealVar("apar_II_LL","A parameter of Crystal Ball II",-1.517);
  RooRealVar *apar_II_DD = new RooRealVar("apar_II_DD","A parameter of Crystal Ball II",-2.54);
  RooRealVar *npar_I_LL = new RooRealVar("npar_I_LL","N parameter of Crystal Ball I",5.28);
  RooRealVar *npar_I_DD = new RooRealVar("npar_I_DD","N parameter of Crystal Ball I",1.81);
  RooRealVar *npar_II_LL = new RooRealVar("npar_II_LL","N parameter of Crystal Ball II",145.501);
  RooRealVar *npar_II_DD = new RooRealVar("npar_II_DD","N parameter of Crystal Ball II",7.5);
  
  RooRealVar *lambda_LL = new RooRealVar("lambda_LL","decay constant",-0.0027,-0.1,0.);
  RooRealVar *lambda_DD = new RooRealVar("lambda_DD","decay constant",-0.0027,-0.1,0.);
    
  // *** Crystal Ball ***
  RooCBShape *CBall_LL_Bd_I = new RooCBShape("CBall_LL_Bd_I","Crystal Ball",*Bmass,*meanBd,*sigma_I_LL,*apar_I_LL,*npar_I_LL);
  RooCBShape *CBall_LL_Bd_II = new RooCBShape("CBall_LL_Bd_II","Reflected Crystal Ball",*Bmass,*meanBd,*sigma_II_LL,*apar_II_LL,*npar_II_LL);
  RooAddPdf *double_CBall_LL_Bd = new RooAddPdf("double_CBall_LL_Bd","Double Crystal Ball",RooArgList(*CBall_LL_Bd_I,*CBall_LL_Bd_II),*frac_LL);
  RooCBShape *CBall_DD_Bd_I = new RooCBShape("CBall_DD_Bd_I","Crystal Ball",*Bmass,*meanBd,*sigma_I_DD,*apar_I_DD,*npar_I_DD);
  RooCBShape *CBall_DD_Bd_II = new RooCBShape("CBall_DD_Bd_II","Reflected Crystal Ball",*Bmass,*meanBd,*sigma_II_DD,*apar_II_DD,*npar_II_DD);
  RooAddPdf *double_CBall_DD_Bd = new RooAddPdf("double_CBall_DD_Bd","Double Crystal Ball",RooArgList(*CBall_DD_Bd_I,*CBall_DD_Bd_II),*frac_DD);

  RooCBShape *CBall_LL_Bs_I = new RooCBShape("CBall_LL_Bs_I","Crystal Ball",*Bmass,*meanBs,*sigma_I_LL,*apar_I_LL,*npar_I_LL);
  RooCBShape *CBall_LL_Bs_II = new RooCBShape("CBall_LL_Bs_II","Reflected Crystal Ball",*Bmass,*meanBs,*sigma_II_LL,*apar_II_LL,*npar_II_LL);
  RooAddPdf *double_CBall_LL_Bs = new RooAddPdf("double_CBall_LL_Bs","Double Crystal Ball",RooArgList(*CBall_LL_Bs_I,*CBall_LL_Bs_II),*frac_LL);
  RooCBShape *CBall_DD_Bs_I = new RooCBShape("CBall_DD_Bs_I","Crystal Ball",*Bmass,*meanBs,*sigma_I_DD,*apar_I_DD,*npar_I_DD);
  RooCBShape *CBall_DD_Bs_II = new RooCBShape("CBall_DD_Bs_II","Reflected Crystal Ball",*Bmass,*meanBs,*sigma_II_DD,*apar_II_DD,*npar_II_DD);
  RooAddPdf *double_CBall_DD_Bs = new RooAddPdf("double_CBall_DD_Bs","Double Crystal Ball",RooArgList(*CBall_DD_Bs_I,*CBall_DD_Bs_II),*frac_DD);
  
  // *** exponential (Background) ***
  RooExponential *exponential_LL = new RooExponential("exponential_LL","Exponential for background",*Bmass,*lambda_LL);
  RooExponential *exponential_DD = new RooExponential("exponential_DD","Exponential for background",*Bmass,*lambda_DD);

  // *** Combined signal and background ***
  RooRealVar *nBkg_LL = new RooRealVar("nBkg_LL","fraction",0.042311*nEvents_LL,0,nEvents_LL);
  RooRealVar *nBd_LL = new RooRealVar("nBd_LL","fraction",0.947600*nEvents_LL,0,nEvents_LL);
  RooRealVar *nBs_LL = new RooRealVar("nBs_LL","fraction",0.010089*nEvents_LL,0,nEvents_LL);

  RooAddPdf *massPDF_LL= new RooAddPdf("massPDF_LL","PDF for Sig + Bkg",RooArgList(*exponential_LL,*double_CBall_LL_Bd,*double_CBall_LL_Bs),RooArgList(*nBkg_LL,*nBd_LL,*nBs_LL));
  
  RooRealVar *nBkg_DD = new RooRealVar("nBkg_DD","fraction",0.042311*nEvents_DD,0,nEvents_DD);
  RooRealVar *nBd_DD = new RooRealVar("nBd_DD","fraction",0.947600*nEvents_DD,0,nEvents_DD);
  RooRealVar *nBs_DD = new RooRealVar("nBs_DD","fraction",0.010089*nEvents_DD,0,nEvents_DD);

  RooAddPdf *massPDF_DD= new RooAddPdf("massPDF_DD","PDF for Sig + Bkg",RooArgList(*exponential_DD,*double_CBall_DD_Bd,*double_CBall_DD_Bs),RooArgList(*nBkg_DD,*nBd_DD,*nBs_DD));


  // *** Fit ***
  massPDF_LL->fitTo(*data_LL,Save(),NumCPU(2));
  massPDF_DD->fitTo(*data_DD,Save(),NumCPU(2)); 
  
  bool debug = false;
  if(debug){
    // ***** Plot: Mass ***** //
    ////////////////////////////
	
    // *** Signal ***
    RooPlot* mBframe = Bmass->frame(Bins(60));

    // Titles
    mBframe->SetYTitle("# Events/(5 MeV/c^{2})");
    mBframe->SetXTitle("B mass (MeV/c^{2})");

    // Cosmetics
    mBframe->SetTitleOffset(1.2,"y");
    mBframe->SetTitleSize(0.07,"x");
    mBframe->SetTitleSize(0.07,"y");
    mBframe->SetTitleFont(132,"y");
    mBframe->SetTitleFont(132,"x");
    mBframe->SetLabelSize(0.05,"y");
    mBframe->SetLabelSize(0.05,"x");
    mBframe->SetLabelFont(132,"x");
    mBframe->SetLabelFont(132,"y");

    data_LL->plotOn(mBframe,MarkerStyle(20),MarkerSize(1),MarkerColor(2));
    massPDF_LL->plotOn(mBframe,Components("exponential_LL"),LineColor(1),LineWidth(2));
    massPDF_LL->plotOn(mBframe,LineColor(2),LineWidth(2));
  
    data_DD->plotOn(mBframe,MarkerStyle(20),MarkerSize(1),MarkerColor(4));
    massPDF_DD->plotOn(mBframe,Components("exponential_DD"),LineColor(3),LineWidth(2));
    massPDF_DD->plotOn(mBframe,LineColor(4),LineWidth(2));

    mBframe->SetMinimum(0.9);
    mBframe->SetMaximum(10000);

	  // *** Canvas ***
    TCanvas *doek_mass = new TCanvas("doek_mass","B Mass Spectrum",900,800);
    doek_mass->SetLeftMargin(0.2);
    doek_mass->SetBottomMargin(0.15);
    doek_mass->cd(1);
    gPad->SetLogy(1);
    mBframe->Draw("");
  }
  
  // ***** sPlot ***** //
  ///////////////////////
  
  std::cout << " " << std::endl;
  std::cout << "==============" << std::endl;
  std::cout << "== sWeights ==" << std::endl;
  std::cout << "==============" << std::endl;
  
  RooRealVar *sWeight = new RooRealVar("sWeight","sWeight for component",0);
  RooArgSet *sWeight_Obs = new RooArgSet(*Bmass,*Hlt1Global,*Hlt1lines,*Hlt2Global,*Hlt2lines,*sWeight);

	// ***** sWeighted Datasets - LL ***** //
  /////////////////////////////////////////
  
  // *** sWeighted Dataset ***
  // Initialise
  RooArgSet *sWeightVar = (RooArgSet *)data_LL->get();
  RooRealVar *sWeight_Bmass = (RooRealVar *)sWeightVar->find(Bmass->GetName());
  RooRealVar *sWeight_Hlt1Global = (RooRealVar *)sWeightVar->find(Hlt1Global->GetName());
  RooRealVar *sWeight_Hlt1lines = (RooRealVar *)sWeightVar->find(Hlt1lines->GetName());
  RooRealVar *sWeight_Hlt2Global = (RooRealVar *)sWeightVar->find(Hlt2Global->GetName());
  RooRealVar *sWeight_Hlt2lines = (RooRealVar *)sWeightVar->find(Hlt2lines->GetName());
  //Double_t tot_LL = sData_LL->GetYieldFromSWeight("nBd_LL");
  RooDataSet *Data_sWeight_LL = new RooDataSet("Data_sWeight_LL","sWeighted Dataset",*sWeight_Obs,WeightVar(*sWeight));
		
  // Get Weights
  RooStats::SPlot *sData_LL = new RooStats::SPlot("sData_LL","sData", *data_LL, massPDF_LL, RooArgSet(*nBkg_LL,*nBd_LL,*nBs_LL));
  for(Int_t i=0; i<nEvents_LL; i++){	
    data_LL->get(i);
    Bmass->setVal(sWeight_Bmass->getVal());
    Hlt1Global->setVal(sWeight_Hlt1Global->getVal());
    Hlt1lines->setVal(sWeight_Hlt1lines->getVal());
    Hlt2Global->setVal(sWeight_Hlt2Global->getVal());
    Hlt2lines->setVal(sWeight_Hlt2lines->getVal());
    sWeight->setVal(sData_LL->GetSWeight(i,"nBd_LL"));
    Data_sWeight_LL->add(*sWeight_Obs,sWeight->getVal());	
  }

  
  // ***** sWeighted Datasets - DD ***** //
  /////////////////////////////////////////

  // *** sWeighted Dataset ***
  // Initialise
  sWeightVar = (RooArgSet *)data_DD->get();
  sWeight_Bmass = (RooRealVar *)sWeightVar->find(Bmass->GetName());
  sWeight_Hlt1Global = (RooRealVar *)sWeightVar->find(Hlt1Global->GetName());
  sWeight_Hlt1lines = (RooRealVar *)sWeightVar->find(Hlt1lines->GetName());
  sWeight_Hlt2Global = (RooRealVar *)sWeightVar->find(Hlt2Global->GetName());
  sWeight_Hlt2lines = (RooRealVar *)sWeightVar->find(Hlt2lines->GetName());
  RooDataSet *Data_sWeight_DD = new RooDataSet("Data_sWeight_DD","sWeighted Dataset",*sWeight_Obs,WeightVar(*sWeight));
		
  // Get Weights
  RooStats::SPlot *sData_DD = new RooStats::SPlot("sData_DD","sData", *data_DD, massPDF_DD, RooArgSet(*nBkg_DD,*nBd_DD,*nBs_DD));
  for(Int_t i=0; i<nEvents_DD; i++){	
    data_DD->get(i);
    Bmass->setVal(sWeight_Bmass->getVal());
    Hlt1Global->setVal(sWeight_Hlt1Global->getVal());
    Hlt1lines->setVal(sWeight_Hlt1lines->getVal());
    Hlt2Global->setVal(sWeight_Hlt2Global->getVal());
    Hlt2lines->setVal(sWeight_Hlt2lines->getVal());
    sWeight->setVal(sData_DD->GetSWeight(i,"nBd_DD"));
    Data_sWeight_DD->add(*sWeight_Obs,sWeight->getVal());	
  }


// ***** Part III: Efficiencies ***** //
////////////////////////////////////////  

  std::cout << std::endl;
  std::cout << "== Part III: Efficiencies ==" << std::endl;
  std::cout << "============================" << std::endl;
  
  std::cout << "=== Long KS ===" << std::endl;
  std::cout << "===============" << std::endl;
  PrintsWeights(Data_sWeight_LL);

  std::cout << "=== Down KS ===" << std::endl;
  std::cout << "===============" << std::endl;
  PrintsWeights(Data_sWeight_DD);
  
}

/////////////////////////////////
// ***** Helper Function ***** //
/////////////////////////////////
void PrintsWeights(RooDataSet *data){

  // *** Number of Events ***
  RooDataSet *data_Hlt1Global = (RooDataSet *) data->reduce("Hlt1Global==1");
  Double_t nEvents_Hlt1Global = data_Hlt1Global->sumEntries();
  delete data_Hlt1Global;
  
  RooDataSet *data_Hlt1 = (RooDataSet *) data->reduce("Hlt1Global==1 && Hlt1lines==1");
  Double_t nEvents_Hlt1 = data_Hlt1->sumEntries();
  delete data_Hlt1;
  
  RooDataSet *data_Hlt2Global = (RooDataSet *) data->reduce("Hlt1Global==1 && Hlt2Global==1");
  Double_t nEvents_Hlt2Global = data_Hlt2Global->sumEntries();
  delete data_Hlt2Global;
  
  RooDataSet *data_Hlt2 = (RooDataSet *) data->reduce("Hlt1Global==1 && Hlt1lines==1 && Hlt2Global==1 && Hlt2lines==1");
  Double_t nEvents_Hlt2 = data_Hlt2->numEntries();
  delete data_Hlt2;

  // *** Efficiencies ***
  Double_t eff_Hlt1_Val = nEvents_Hlt1/nEvents_Hlt1Global;
  Double_t eff_Hlt1_Err = TMath::Sqrt((nEvents_Hlt1*nEvents_Hlt1Global + pow(nEvents_Hlt1,2))/pow(nEvents_Hlt1Global,3));
  Double_t eff_Hlt2_Val = nEvents_Hlt2/nEvents_Hlt2Global;
  Double_t eff_Hlt2_Err = TMath::Sqrt((nEvents_Hlt2*nEvents_Hlt2Global + pow(nEvents_Hlt2,2))/pow(nEvents_Hlt2Global,3));

  // *** Output ***
  std::cout << "Hlt1: " << nEvents_Hlt1 << "/" << nEvents_Hlt1Global << " = " << eff_Hlt1_Val << " +/- " << eff_Hlt1_Err << std::endl;
  std::cout << "Hlt1 & Hlt2: " << nEvents_Hlt2 << "/" << nEvents_Hlt2Global << " = " << eff_Hlt2_Val << " +/- " << eff_Hlt2_Err << std::endl;
  std::cout << std::endl;
  
}
