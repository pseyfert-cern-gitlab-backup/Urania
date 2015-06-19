////////////////////////////////////////////////////////
// ***** Compare Long and Downstream KS Samples ***** //
////////////////////////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb
// - Compare the observables for the Long and Downstream KS Samples


/////////////////////////////////////
// ***** Load useful classes ***** //
/////////////////////////////////////

#include "RooArgSet.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooRealVar.h"

#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TMath.h"
#include "TNtuple.h"
#include "TPaveText.h"

using namespace RooFit;

//////////////////////////////
// ***** Declarations ***** //
//////////////////////////////
void PullPlot(RooDataSet *data_Bd, RooDataSet *data_Bs, RooRealVar *Obs,Double_t bin_low, Double_t bin_high, Int_t bins, TString scale, TString Obs_title, TString savestring, Double_t max = 0.1);


/////////////////////////////////
// ***** Helper Function ***** //
/////////////////////////////////
void MCComparison(Int_t set = 1){

// ***** Initialize ***** //
////////////////////////////



// ***** Part I: From NTuple to DataSet ***** //
////////////////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Part I: From NTuple to DataSet ==" << std::endl;
  std::cout << "====================================" << std::endl;

  // ***** Load NTuples ***** //
  //////////////////////////////
  
  TFile* netFile_Bd = TFile::Open("B2JpsiKs-Eval-1-random-SigBd.root");
  TTree* neural_net_Bd = (TTree*)netFile_Bd->Get("NetTree");

  TChain* chain_Bd = new TChain("chain");
  chain_Bd->Add("B2JpsiKs-Slim-SigBd.root/Slim_B2JpsiKs_Tuple");
  chain_Bd->AddFriend(neural_net_Bd);
  
  
  TFile* netFile_Bs = TFile::Open("B2JpsiKs-Eval-1-random-SigBs.root");
  TTree* neural_net_Bs = (TTree*)netFile_Bs->Get("NetTree");

  TChain* chain_Bs = new TChain("chain");
  chain_Bs->Add("B2JpsiKs-Slim-SigBs.root/Slim_B2JpsiKs_Tuple");
  chain_Bs->AddFriend(neural_net_Bs);
  
  
  Long64_t nEntries_Bd = chain_Bd->GetEntries();
  Long64_t nEntries_Bs = chain_Bs->GetEntries();
  //nEntries_Bd = 10000;  
  std::cout << "Number of entries from DaVinci: " << nEntries_Bd << " (Bd) and " << nEntries_Bs << " (Bs)" << std::endl;    


  // ***** Define DataSet Observables ***** //
  ////////////////////////////////////////////

  // *** Define Observables & Selection Variables ***

  // Observable
  Int_t piminus_TRACK_Type = -999;
  // Neural Net Variables
  Float_t B_FullFit_chi2[10];
  Double_t B_DIRA_OWNPV = -999;
  Double_t KS0_PT = -999;
  Float_t B_FullFit_MERR[10];
  Double_t Psi_MINIPCHI2 = -999;
  Float_t B_FullFit_ctau[10];
  Double_t B_ENDVERTEX_CHI2 = -999;
  Int_t B_ENDVERTEX_NDOF = -999;
  Double_t B_P = -999;
  Double_t B_PT = -999;
  Float_t B_FullFit_ctauErr[10];
  Double_t Psi_FDCHI2_ORIVX = -999;
  Double_t Psi_MM = -999;
  Double_t Psi_MMERR = -999;
  Double_t Psi_P = -999;
  Double_t Psi_PT = -999;
  Double_t KS0_ENDVERTEX_Z = -999;
  Float_t B_FullFit_KS0_ctau[10];
  Float_t B_FullFit_KS0_ctauErr[10];
  Double_t KS0_ENDVERTEX_CHI2 = -999;
  Double_t KS0_MINIPCHI2 = -999;
  Double_t KS0_MM = -999;
  Double_t KS0_MMERR = -999;
  Double_t KS0_P = -999;
  Double_t muminus_MINIPCHI2 = -999;
  Double_t muplus_MINIPCHI2 = -999;
  Double_t muminus_MINIP = -999;
  Double_t muplus_MINIP = -999;
  Double_t muminus_P = -999;
  Double_t muplus_P = -999;
  Double_t muminus_PT = -999;
  Double_t muplus_PT = -999;
  Double_t muminus_PIDmu = -999;
  Double_t muplus_PIDmu = -999;
  Double_t muplus_TRACK_CHI2NDOF = -999;
  Double_t muminus_TRACK_CHI2NDOF = -999;
  Double_t piminus_MINIP = -999;
  Double_t piplus_MINIP = -999;
  Double_t piminus_PT = -999;
  Double_t piplus_PT = -999;
  Double_t piminus_TRACK_GhostProb = -999;
  Double_t piplus_TRACK_GhostProb = -999;
  Double_t piplus_TRACK_CHI2NDOF = -999;
  Double_t piminus_TRACK_CHI2NDOF = -999;
  Int_t nPVs = -999;
  Int_t nSPDHits = -999;
  Int_t nOTClusters = -999;
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
    B_FullFit_chi2[i] = -999;
    B_FullFit_MERR[i] = -999;
    B_FullFit_ctau[i] = -999;
    B_FullFit_ctauErr[i] = -999;
    B_FullFit_KS0_ctau[i] = -999;
    B_FullFit_KS0_ctauErr[i] = -999;
    B_FullFit_PV_X[i] = -999;
    B_FullFit_PV_Y[i] = -999;
    B_FullFit_PV_Z[i] = -999;
    netOutput[i] = -999;
  }
  

  // *** Set Branch Addresses ***
  // Observable
  chain_Bd->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type);
  // Neural Net Variables
  chain_Bd->SetBranchAddress("B_FullFit_chi2", &B_FullFit_chi2);
  chain_Bd->SetBranchAddress("B_DIRA_OWNPV", &B_DIRA_OWNPV);
  chain_Bd->SetBranchAddress("KS0_PT", &KS0_PT);
  chain_Bd->SetBranchAddress("B_FullFit_MERR", &B_FullFit_MERR);
  chain_Bd->SetBranchAddress("Psi_MINIPCHI2", &Psi_MINIPCHI2);
  chain_Bd->SetBranchAddress("B_FullFit_ctau", &B_FullFit_ctau);
  chain_Bd->SetBranchAddress("B_ENDVERTEX_CHI2", &B_ENDVERTEX_CHI2);
  chain_Bd->SetBranchAddress("B_ENDVERTEX_NDOF", &B_ENDVERTEX_NDOF);
  chain_Bd->SetBranchAddress("B_P", &B_P);
  chain_Bd->SetBranchAddress("B_PT", &B_PT);
  chain_Bd->SetBranchAddress("B_FullFit_ctauErr", &B_FullFit_ctauErr);
  chain_Bd->SetBranchAddress("Psi_FDCHI2_ORIVX", &Psi_FDCHI2_ORIVX);
  chain_Bd->SetBranchAddress("Psi_MM", &Psi_MM);
  chain_Bd->SetBranchAddress("Psi_MMERR", &Psi_MMERR);
  chain_Bd->SetBranchAddress("Psi_P", &Psi_P);
  chain_Bd->SetBranchAddress("Psi_PT", &Psi_PT);
  chain_Bd->SetBranchAddress("KS0_ENDVERTEX_Z", &KS0_ENDVERTEX_Z);
  chain_Bd->SetBranchAddress("B_FullFit_KS0_ctau", &B_FullFit_KS0_ctau);
  chain_Bd->SetBranchAddress("B_FullFit_KS0_ctauErr", &B_FullFit_KS0_ctauErr);
  chain_Bd->SetBranchAddress("KS0_ENDVERTEX_CHI2", &KS0_ENDVERTEX_CHI2);
  chain_Bd->SetBranchAddress("KS0_MINIPCHI2", &KS0_MINIPCHI2);
  chain_Bd->SetBranchAddress("KS0_MM", &KS0_MM);
  chain_Bd->SetBranchAddress("KS0_MMERR", &KS0_MMERR);
  chain_Bd->SetBranchAddress("KS0_P", &KS0_P);
  chain_Bd->SetBranchAddress("muminus_MINIPCHI2", &muminus_MINIPCHI2);
  chain_Bd->SetBranchAddress("muplus_MINIPCHI2", &muplus_MINIPCHI2);
  chain_Bd->SetBranchAddress("muminus_MINIP", &muminus_MINIP);
  chain_Bd->SetBranchAddress("muplus_MINIP", &muplus_MINIP);
  chain_Bd->SetBranchAddress("muminus_P", &muminus_P);
  chain_Bd->SetBranchAddress("muplus_P", &muplus_P);
  chain_Bd->SetBranchAddress("muminus_PT", &muminus_PT);
  chain_Bd->SetBranchAddress("muplus_PT", &muplus_PT);
  chain_Bd->SetBranchAddress("muminus_PIDmu", &muminus_PIDmu);
  chain_Bd->SetBranchAddress("muplus_PIDmu", &muplus_PIDmu);
  chain_Bd->SetBranchAddress("muplus_TRACK_CHI2NDOF", &muplus_TRACK_CHI2NDOF);
  chain_Bd->SetBranchAddress("muminus_TRACK_CHI2NDOF", &muminus_TRACK_CHI2NDOF);
  chain_Bd->SetBranchAddress("piminus_MINIP", &piminus_MINIP);
  chain_Bd->SetBranchAddress("piplus_MINIP", &piplus_MINIP);
  chain_Bd->SetBranchAddress("piminus_PT", &piminus_PT);
  chain_Bd->SetBranchAddress("piplus_PT", &piplus_PT);
  chain_Bd->SetBranchAddress("piminus_TRACK_GhostProb", &piminus_TRACK_GhostProb);
  chain_Bd->SetBranchAddress("piplus_TRACK_GhostProb", &piplus_TRACK_GhostProb);
  chain_Bd->SetBranchAddress("piplus_TRACK_CHI2NDOF", &piplus_TRACK_CHI2NDOF);
  chain_Bd->SetBranchAddress("piminus_TRACK_CHI2NDOF", &piminus_TRACK_CHI2NDOF);
  chain_Bd->SetBranchAddress("nPVs", &nPVs);
  chain_Bd->SetBranchAddress("nSPDHits", &nSPDHits);
  chain_Bd->SetBranchAddress("nOTClusters", &nOTClusters);
  // PV Matching
  chain_Bd->SetBranchAddress("B_FullFit_PV_X", &B_FullFit_PV_X);
  chain_Bd->SetBranchAddress("B_FullFit_PV_Y", &B_FullFit_PV_Y);
  chain_Bd->SetBranchAddress("B_FullFit_PV_Z", &B_FullFit_PV_Z);
  // Trigger
  chain_Bd->SetBranchAddress("PsiHlt1TrackMuonDecision_TOS", &PsiHlt1TrackMuonDecision_TOS);
  chain_Bd->SetBranchAddress("PsiHlt1DiMuonHighMassDecision_TOS", &PsiHlt1DiMuonHighMassDecision_TOS);
  chain_Bd->SetBranchAddress("PsiHlt1TrackAllL0Decision_TOS", &PsiHlt1TrackAllL0Decision_TOS);  
  chain_Bd->SetBranchAddress("PsiHlt2DiMuonDetachedJPsiDecision_TOS", &PsiHlt2DiMuonDetachedJPsiDecision_TOS);
  chain_Bd->SetBranchAddress("PsiHlt2DiMuonJPsiHighPTDecision_TOS", &PsiHlt2DiMuonJPsiHighPTDecision_TOS);
  chain_Bd->SetBranchAddress("PsiHlt2DiMuonJPsiDecision_TOS", &PsiHlt2DiMuonJPsiDecision_TOS);
  chain_Bd->SetBranchAddress("PsiHlt2TopoMu2BodyBBDTDecision_TOS",&PsiHlt2TopoMu2BodyBBDTDecision_TOS);  
  chain_Bd->SetBranchAddress("PsiL0Global_Dec",&PsiL0Global_Dec);
  chain_Bd->SetBranchAddress("PsiHlt1Global_Dec",&PsiHlt1Global_Dec);
  chain_Bd->SetBranchAddress("PsiHlt2Global_Dec",&PsiHlt2Global_Dec);
  // Neural Net
  chain_Bd->SetBranchAddress("netOutput", &netOutput);
  chain_Bd->SetBranchAddress("nPV2", &nPV2);
  // True ID of Decay
  chain_Bd->SetBranchAddress("B_TRUEID", &B_TRUEID);
  chain_Bd->SetBranchAddress("Psi_TRUEID", &Psi_TRUEID);
  chain_Bd->SetBranchAddress("KS0_TRUEID", &KS0_TRUEID);
  chain_Bd->SetBranchAddress("B_BKGCAT", &B_BKGCAT);
  chain_Bd->SetBranchAddress("B_TRUEORIGINVERTEX_X", &B_TRUEORIGINVERTEX_X);
  chain_Bd->SetBranchAddress("B_TRUEORIGINVERTEX_Y", &B_TRUEORIGINVERTEX_Y);
  chain_Bd->SetBranchAddress("B_TRUEORIGINVERTEX_Z", &B_TRUEORIGINVERTEX_Z);
  
  // *** Set Branch Addresses ***
  // Observable
  chain_Bs->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type);
  // Neural Net Variables
  chain_Bs->SetBranchAddress("B_FullFit_chi2", &B_FullFit_chi2);
  chain_Bs->SetBranchAddress("B_DIRA_OWNPV", &B_DIRA_OWNPV);
  chain_Bs->SetBranchAddress("KS0_PT", &KS0_PT);
  chain_Bs->SetBranchAddress("B_FullFit_MERR", &B_FullFit_MERR);
  chain_Bs->SetBranchAddress("Psi_MINIPCHI2", &Psi_MINIPCHI2);
  chain_Bs->SetBranchAddress("B_FullFit_ctau", &B_FullFit_ctau);
  chain_Bs->SetBranchAddress("B_ENDVERTEX_CHI2", &B_ENDVERTEX_CHI2);
  chain_Bs->SetBranchAddress("B_ENDVERTEX_NDOF", &B_ENDVERTEX_NDOF);
  chain_Bs->SetBranchAddress("B_P", &B_P);
  chain_Bs->SetBranchAddress("B_PT", &B_PT);
  chain_Bs->SetBranchAddress("B_FullFit_ctauErr", &B_FullFit_ctauErr);
  chain_Bs->SetBranchAddress("Psi_FDCHI2_ORIVX", &Psi_FDCHI2_ORIVX);
  chain_Bs->SetBranchAddress("Psi_MM", &Psi_MM);
  chain_Bs->SetBranchAddress("Psi_MMERR", &Psi_MMERR);
  chain_Bs->SetBranchAddress("Psi_P", &Psi_P);
  chain_Bs->SetBranchAddress("Psi_PT", &Psi_PT);
  chain_Bs->SetBranchAddress("KS0_ENDVERTEX_Z", &KS0_ENDVERTEX_Z);
  chain_Bs->SetBranchAddress("B_FullFit_KS0_ctau", &B_FullFit_KS0_ctau);
  chain_Bs->SetBranchAddress("B_FullFit_KS0_ctauErr", &B_FullFit_KS0_ctauErr);
  chain_Bs->SetBranchAddress("KS0_ENDVERTEX_CHI2", &KS0_ENDVERTEX_CHI2);
  chain_Bs->SetBranchAddress("KS0_MINIPCHI2", &KS0_MINIPCHI2);
  chain_Bs->SetBranchAddress("KS0_MM", &KS0_MM);
  chain_Bs->SetBranchAddress("KS0_MMERR", &KS0_MMERR);
  chain_Bs->SetBranchAddress("KS0_P", &KS0_P);
  chain_Bs->SetBranchAddress("muminus_MINIPCHI2", &muminus_MINIPCHI2);
  chain_Bs->SetBranchAddress("muplus_MINIPCHI2", &muplus_MINIPCHI2);
  chain_Bs->SetBranchAddress("muminus_MINIP", &muminus_MINIP);
  chain_Bs->SetBranchAddress("muplus_MINIP", &muplus_MINIP);
  chain_Bs->SetBranchAddress("muminus_P", &muminus_P);
  chain_Bs->SetBranchAddress("muplus_P", &muplus_P);
  chain_Bs->SetBranchAddress("muminus_PT", &muminus_PT);
  chain_Bs->SetBranchAddress("muplus_PT", &muplus_PT);
  chain_Bs->SetBranchAddress("muminus_PIDmu", &muminus_PIDmu);
  chain_Bs->SetBranchAddress("muplus_PIDmu", &muplus_PIDmu);
  chain_Bs->SetBranchAddress("muplus_TRACK_CHI2NDOF", &muplus_TRACK_CHI2NDOF);
  chain_Bs->SetBranchAddress("muminus_TRACK_CHI2NDOF", &muminus_TRACK_CHI2NDOF);
  chain_Bs->SetBranchAddress("piminus_MINIP", &piminus_MINIP);
  chain_Bs->SetBranchAddress("piplus_MINIP", &piplus_MINIP);
  chain_Bs->SetBranchAddress("piminus_PT", &piminus_PT);
  chain_Bs->SetBranchAddress("piplus_PT", &piplus_PT);
  chain_Bs->SetBranchAddress("piminus_TRACK_GhostProb", &piminus_TRACK_GhostProb);
  chain_Bs->SetBranchAddress("piplus_TRACK_GhostProb", &piplus_TRACK_GhostProb);
  chain_Bs->SetBranchAddress("piplus_TRACK_CHI2NDOF", &piplus_TRACK_CHI2NDOF);
  chain_Bs->SetBranchAddress("piminus_TRACK_CHI2NDOF", &piminus_TRACK_CHI2NDOF);
  chain_Bs->SetBranchAddress("nPVs", &nPVs);
  chain_Bs->SetBranchAddress("nSPDHits", &nSPDHits);
  chain_Bs->SetBranchAddress("nOTClusters", &nOTClusters);
  // PV Matching
  chain_Bs->SetBranchAddress("B_FullFit_PV_X", &B_FullFit_PV_X);
  chain_Bs->SetBranchAddress("B_FullFit_PV_Y", &B_FullFit_PV_Y);
  chain_Bs->SetBranchAddress("B_FullFit_PV_Z", &B_FullFit_PV_Z);
  // Trigger
  chain_Bs->SetBranchAddress("PsiHlt1TrackMuonDecision_TOS", &PsiHlt1TrackMuonDecision_TOS);
  chain_Bs->SetBranchAddress("PsiHlt1DiMuonHighMassDecision_TOS", &PsiHlt1DiMuonHighMassDecision_TOS);
  chain_Bs->SetBranchAddress("PsiHlt1TrackAllL0Decision_TOS", &PsiHlt1TrackAllL0Decision_TOS);  
  chain_Bs->SetBranchAddress("PsiHlt2DiMuonDetachedJPsiDecision_TOS", &PsiHlt2DiMuonDetachedJPsiDecision_TOS);
  chain_Bs->SetBranchAddress("PsiHlt2DiMuonJPsiHighPTDecision_TOS", &PsiHlt2DiMuonJPsiHighPTDecision_TOS);
  chain_Bs->SetBranchAddress("PsiHlt2DiMuonJPsiDecision_TOS", &PsiHlt2DiMuonJPsiDecision_TOS);
  chain_Bs->SetBranchAddress("PsiHlt2TopoMu2BodyBBDTDecision_TOS",&PsiHlt2TopoMu2BodyBBDTDecision_TOS);  
  chain_Bs->SetBranchAddress("PsiL0Global_Dec",&PsiL0Global_Dec);
  chain_Bs->SetBranchAddress("PsiHlt1Global_Dec",&PsiHlt1Global_Dec);
  chain_Bs->SetBranchAddress("PsiHlt2Global_Dec",&PsiHlt2Global_Dec);
  // Neural Net
  chain_Bs->SetBranchAddress("netOutput", &netOutput);
  chain_Bs->SetBranchAddress("nPV2", &nPV2);
  // True ID of Decay
  chain_Bs->SetBranchAddress("B_TRUEID", &B_TRUEID);
  chain_Bs->SetBranchAddress("Psi_TRUEID", &Psi_TRUEID);
  chain_Bs->SetBranchAddress("KS0_TRUEID", &KS0_TRUEID);
  chain_Bs->SetBranchAddress("B_BKGCAT", &B_BKGCAT);
  chain_Bs->SetBranchAddress("B_TRUEORIGINVERTEX_X", &B_TRUEORIGINVERTEX_X);
  chain_Bs->SetBranchAddress("B_TRUEORIGINVERTEX_Y", &B_TRUEORIGINVERTEX_Y);
  chain_Bs->SetBranchAddress("B_TRUEORIGINVERTEX_Z", &B_TRUEORIGINVERTEX_Z);
  

  // ***** Initialize DataSet ***** //
  ////////////////////////////////////

  // *** Observable ***
  RooRealVar *myB_FullFit_chi2 = new RooRealVar("myB_FullFit_chi2","Observable",0);
  RooRealVar *myB_DIRA_OWNPV = new RooRealVar("myB_DIRA_OWNPV","Observable",0);
  RooRealVar *myKS0_PT = new RooRealVar("myKS0_PT","Observable",0);
  RooRealVar *myB_FullFit_MERR = new RooRealVar("myB_FullFit_MERR","Observable",0);
  RooRealVar *myPsi_MINIPCHI2 = new RooRealVar("myPsi_MINIPCHI2","Observable",0);
  
  RooRealVar *myB_FullFit_ctau = new RooRealVar("myB_FullFit_ctau","Observable",0);
  RooRealVar *myB_ENDVERTEX_CHI2 = new RooRealVar("myB_ENDVERTEX_CHI2","Observable",0);
  RooRealVar *myB_P = new RooRealVar("myB_P","Observable",0);
  RooRealVar *myB_PT = new RooRealVar("myB_PT","Observable",0);
  RooRealVar *myB_FullFit_ctauErr = new RooRealVar("myB_FullFit_ctauErr","Observable",0);
  
  RooRealVar *myPsi_FDCHI2_ORIVX = new RooRealVar("myPsi_FDCHI2_ORIVX ","Observable",0);
  RooRealVar *myPsi_MM = new RooRealVar("myPsi_MM","Observable",0);
  RooRealVar *myPsi_MMERR = new RooRealVar("myPsi_MMERR","Observable",0);
  RooRealVar *myPsi_P = new RooRealVar("myPsi_P","Observable",0);
  RooRealVar *myPsi_PT = new RooRealVar("myPsi_PT","Observable",0);
  
  RooRealVar *myKS0_ENDVERTEX_Z = new RooRealVar("myKS0_ENDVERTEX_Z","Observable",0);
  RooRealVar *myB_FullFit_KS0_ctau = new RooRealVar("myB_FullFit_KS0_ctau","Observable",0);
  RooRealVar *myB_FullFit_KS0_ctauErr = new RooRealVar("myB_FullFit_KS0_ctauErr","Observable",0);
  RooRealVar *myKS0_ENDVERTEX_CHI2 = new RooRealVar("myKS0_ENDVERTEX_CHI2","Observable",0);
  RooRealVar *myKS0_MINIPCHI2 = new RooRealVar("myKS0_MINIPCHI2","Observable",0);
  RooRealVar *myKS0_MM = new RooRealVar("myKS0_MM","Observable",0);
  RooRealVar *myKS0_MMERR = new RooRealVar("myKS0_MMERR","Observable",0);
  RooRealVar *myKS0_P = new RooRealVar("myKS0_P","Observable",0);
  
  RooRealVar *mymu_MINIPCHI2 = new RooRealVar("mymu_MINIPCHI2","Observable",0);
  RooRealVar *mymu_MINIP = new RooRealVar("mymu_MINIP","Observable",0);
  RooRealVar *mymu_P = new RooRealVar("mymu_P","Observable",0);
  RooRealVar *mymu_PT = new RooRealVar("mymu_PT","Observable",0);
  RooRealVar *mymu_PIDmu = new RooRealVar("mymu_PIDmu","Observable",0);
  RooRealVar *mymu_TRACK_CHI2NDOF = new RooRealVar("mymu_TRACK_CHI2NDOF","Observable",0);
  
  RooRealVar *mypi_MINIP = new RooRealVar("mypi_MINIP","Observable",0);
  RooRealVar *mypi_PT = new RooRealVar("mypi_PT","Observable",0);
  RooRealVar *mypi_TRACK_GhostProb = new RooRealVar("mypi_TRACK_GhostProb","Observable",0);
  RooRealVar *mypi_TRACK_CHI2NDOF = new RooRealVar("mypi_TRACK_CHI2NDOF","Observable",0);
  
  RooRealVar *mynPVs = new RooRealVar("mynPVs","Observable",0);
  RooRealVar *mynSPDHits = new RooRealVar("mynSPDHits","Observable",0);
  RooRealVar *mynOTClusters = new RooRealVar("mynOTClusters","Observable",0);
  
  RooRealVar *weight = new RooRealVar("weight","Weight for Normalisation", 0.,1.);

  // *** DataSet ***
  RooArgSet *Obs = 0;
  if(set==1) Obs = new RooArgSet(*myB_FullFit_chi2,*myB_DIRA_OWNPV,*myKS0_PT,*myB_FullFit_MERR,*myPsi_MINIPCHI2,*weight);
  else if(set==2) Obs = new RooArgSet(*myB_FullFit_ctau,*myB_ENDVERTEX_CHI2,*myB_P,*myB_PT,*myB_FullFit_ctauErr,*weight);
  else if(set==3) Obs = new RooArgSet(*myPsi_FDCHI2_ORIVX,*myPsi_MM,*myPsi_MMERR,*myPsi_P,*myPsi_PT,*weight);
  else if(set==4) Obs = new RooArgSet(*myKS0_ENDVERTEX_Z,*myB_FullFit_KS0_ctau,*myB_FullFit_KS0_ctauErr,*myKS0_ENDVERTEX_CHI2,*myKS0_MINIPCHI2,*myKS0_MM,*myKS0_MMERR,*myKS0_P,*weight);
  else if(set==5) Obs = new RooArgSet(*mymu_MINIPCHI2,*mymu_MINIP,*mymu_P,*mymu_PT,*mymu_PIDmu,*mymu_TRACK_CHI2NDOF,*weight);
  else if(set==6) Obs = new RooArgSet(*mypi_MINIP,*mypi_PT,*mypi_TRACK_GhostProb,*mypi_TRACK_CHI2NDOF,*weight);
  else if(set==7) Obs = new RooArgSet(*mynPVs,*mynSPDHits,*mynOTClusters,*weight);
  RooDataSet *data_Bd_LL = new RooDataSet("data_Bd_LL","Unbinned dataset",*Obs, WeightVar(*weight));
  RooDataSet *data_Bd_DD = new RooDataSet("data_Bd_DD","Unbinned dataset",*Obs, WeightVar(*weight));
  RooDataSet *data_Bs_LL = new RooDataSet("data_Bs_LL","Unbinned dataset",*Obs, WeightVar(*weight));
  RooDataSet *data_Bs_DD = new RooDataSet("data_Bs_DD","Unbinned dataset",*Obs, WeightVar(*weight));


  // ***** Loop over Entries: Apply Selection Cuts ***** //
  /////////////////////////////////////////////////////////

  // Initialise
  Double_t DOCA = 0;
  Double_t DOCA_min = 999;
  Int_t truePV = 0;
  Long64_t selected_LL = 0;
  Long64_t selected_DD = 0;
  
  bool TruthMatch = false;

  std::cout << " " << std::endl;
  std::cout << "== Bd->JpsiKs ==" << std::endl;
  std::cout << "================" << std::endl;

  // *** Count ***
  std::cout << "Count" << std::endl;
  for(Long64_t i=0; i<nEntries_Bd; i++){
    chain_Bd->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_Bd << " (" << 100*i/nEntries_Bd << "%)" << std::endl;

    TruthMatch = (TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && (B_BKGCAT==0 || B_BKGCAT==10));
    //else if(what=="SigBs") TruthMatch = (TMath::Abs(B_TRUEID)==531 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && (B_BKGCAT==20));

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
      if(netOutput[truePV]>-1){
        if(piminus_TRACK_Type==3) selected_LL++;
        else if(piminus_TRACK_Type==5) selected_DD++;
      }
    }
    // Reset
    DOCA_min = 999;
  }
  
  // *** Fill ***
  std::cout << "Fill" << std::endl;
  for(Long64_t i=0; i<nEntries_Bd; i++){
    chain_Bd->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_Bd << " (" << 100*i/nEntries_Bd << "%)" << std::endl;

    TruthMatch = (TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && (B_BKGCAT==0 || B_BKGCAT==10));
    //else if(what=="SigBs") TruthMatch = (TMath::Abs(B_TRUEID)==531 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && (B_BKGCAT==20));

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
      if(netOutput[truePV]>-1){
      
        if(set==1){
          myB_FullFit_chi2->setVal(B_FullFit_chi2[truePV]);
          myB_DIRA_OWNPV->setVal(std::acos(B_DIRA_OWNPV));
          myKS0_PT->setVal(KS0_PT);
          myB_FullFit_MERR->setVal(B_FullFit_MERR[truePV]);
          myPsi_MINIPCHI2->setVal(Psi_MINIPCHI2);
        }
        else if(set==2){
          myB_FullFit_ctau->setVal(B_FullFit_ctau[truePV]);
          myB_ENDVERTEX_CHI2->setVal(B_ENDVERTEX_CHI2/B_ENDVERTEX_NDOF);
          myB_P->setVal(B_P);
          myB_PT->setVal(B_PT);
          myB_FullFit_ctauErr->setVal(B_FullFit_ctauErr[truePV]);
        }
        else if(set==3){
          myPsi_FDCHI2_ORIVX->setVal(Psi_FDCHI2_ORIVX);
          myPsi_MM->setVal(fabs(Psi_MM-3099.0));
          myPsi_MMERR->setVal(Psi_MMERR);
          myPsi_P->setVal(Psi_P);
          myPsi_PT->setVal(Psi_PT);
        }
        else if(set==4){
          myKS0_ENDVERTEX_Z->setVal(KS0_ENDVERTEX_Z);
          myB_FullFit_KS0_ctau->setVal(B_FullFit_KS0_ctau[truePV]);
          myB_FullFit_KS0_ctauErr->setVal(B_FullFit_KS0_ctau[truePV]/B_FullFit_KS0_ctauErr[truePV]);
          myKS0_ENDVERTEX_CHI2->setVal(KS0_ENDVERTEX_CHI2);
          myKS0_MINIPCHI2->setVal(KS0_MINIPCHI2);
          myKS0_MM->setVal(fabs(KS0_MM-497.614));
          myKS0_MMERR->setVal(KS0_MMERR);
          myKS0_P->setVal(KS0_P);
        }
        else if(set==5){
          mymu_MINIPCHI2->setVal(min(muminus_MINIPCHI2,muplus_MINIPCHI2));
          mymu_MINIP->setVal(min(muminus_MINIP,muplus_MINIP));
          mymu_P->setVal(min(muminus_P,muplus_P));
          mymu_PT->setVal(min(muminus_PT,muplus_PT));
          mymu_PIDmu->setVal(min(muminus_PIDmu,muplus_PIDmu));
          mymu_TRACK_CHI2NDOF->setVal(max(muplus_TRACK_CHI2NDOF,muminus_TRACK_CHI2NDOF));
        }
        else if(set==6){
          mypi_MINIP->setVal(min(piminus_MINIP,piplus_MINIP));
          mypi_PT->setVal(min(piminus_PT,piplus_PT));
          mypi_TRACK_GhostProb->setVal((piminus_TRACK_GhostProb>0 ? max(piminus_TRACK_GhostProb,piplus_TRACK_GhostProb) : -999));
          mypi_TRACK_CHI2NDOF->setVal(max(piplus_TRACK_CHI2NDOF,piminus_TRACK_CHI2NDOF));
        }
        else if(set==7){
          mynPVs->setVal(nPVs);
          mynSPDHits->setVal(nSPDHits);
          mynOTClusters->setVal(nOTClusters);
        }
        if(piminus_TRACK_Type==3){
          weight->setVal(1./(selected_LL));
          data_Bd_LL->add(*Obs, weight->getVal());
        }
        else if(piminus_TRACK_Type==5){
          weight->setVal(1./(selected_DD));
          data_Bd_DD->add(*Obs, weight->getVal());
        }
      }
    }
    // Reset
    DOCA_min = 999;
  }
  
  std::cout << " " << std::endl;
  std::cout << "== Bs->JpsiKs ==" << std::endl;
  std::cout << "================" << std::endl;

  selected_LL = 0;
  selected_DD = 0;

  // *** Count ***
  std::cout << "Count" << std::endl;
  for(Long64_t i=0; i<nEntries_Bs; i++){
    chain_Bs->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_Bs << " (" << 100*i/nEntries_Bs << "%)" << std::endl;

    TruthMatch = (TMath::Abs(B_TRUEID)==531 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && (B_BKGCAT==20));

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
      if(netOutput[truePV]>-1){
        if(piminus_TRACK_Type==3) selected_LL++;
        else if(piminus_TRACK_Type==5) selected_DD++;
      }
    }
    // Reset
    DOCA_min = 999;
  }
  
  // *** Fill ***
  std::cout << "Fill" << std::endl;
  for(Long64_t i=0; i<nEntries_Bs; i++){
    chain_Bs->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_Bs << " (" << 100*i/nEntries_Bs << "%)" << std::endl;

    TruthMatch = (TMath::Abs(B_TRUEID)==531 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && (B_BKGCAT==20));

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
      if(netOutput[truePV]>-1){
      
        if(set==1){
          myB_FullFit_chi2->setVal(B_FullFit_chi2[truePV]);
          myB_DIRA_OWNPV->setVal(std::acos(B_DIRA_OWNPV));
          myKS0_PT->setVal(KS0_PT);
          myB_FullFit_MERR->setVal(B_FullFit_MERR[truePV]);
          myPsi_MINIPCHI2->setVal(Psi_MINIPCHI2);
        }
        else if(set==2){
          myB_FullFit_ctau->setVal(B_FullFit_ctau[truePV]);
          myB_ENDVERTEX_CHI2->setVal(B_ENDVERTEX_CHI2/B_ENDVERTEX_NDOF);
          myB_P->setVal(B_P);
          myB_PT->setVal(B_PT);
          myB_FullFit_ctauErr->setVal(B_FullFit_ctauErr[truePV]);
        }
        else if(set==3){
          myPsi_FDCHI2_ORIVX->setVal(Psi_FDCHI2_ORIVX);
          myPsi_MM->setVal(fabs(Psi_MM-3099.0));
          myPsi_MMERR->setVal(Psi_MMERR);
          myPsi_P->setVal(Psi_P);
          myPsi_PT->setVal(Psi_PT);
        }
        else if(set==4){
          myKS0_ENDVERTEX_Z->setVal(KS0_ENDVERTEX_Z);
          myB_FullFit_KS0_ctau->setVal(B_FullFit_KS0_ctau[truePV]);
          myB_FullFit_KS0_ctauErr->setVal(B_FullFit_KS0_ctau[truePV]/B_FullFit_KS0_ctauErr[truePV]);
          myKS0_ENDVERTEX_CHI2->setVal(KS0_ENDVERTEX_CHI2);
          myKS0_MINIPCHI2->setVal(KS0_MINIPCHI2);
          myKS0_MM->setVal(fabs(KS0_MM-497.614));
          myKS0_MMERR->setVal(KS0_MMERR);
          myKS0_P->setVal(KS0_P);
        }
        else if(set==5){
          mymu_MINIPCHI2->setVal(min(muminus_MINIPCHI2,muplus_MINIPCHI2));
          mymu_MINIP->setVal(min(muminus_MINIP,muplus_MINIP));
          mymu_P->setVal(min(muminus_P,muplus_P));
          mymu_PT->setVal(min(muminus_PT,muplus_PT));
          mymu_PIDmu->setVal(min(muminus_PIDmu,muplus_PIDmu));
          mymu_TRACK_CHI2NDOF->setVal(max(muplus_TRACK_CHI2NDOF,muminus_TRACK_CHI2NDOF));
        }
        else if(set==6){
          mypi_MINIP->setVal(min(piminus_MINIP,piplus_MINIP));
          mypi_PT->setVal(min(piminus_PT,piplus_PT));
          mypi_TRACK_GhostProb->setVal((piminus_TRACK_GhostProb>0 ? max(piminus_TRACK_GhostProb,piplus_TRACK_GhostProb) : -999));
          mypi_TRACK_CHI2NDOF->setVal(max(piplus_TRACK_CHI2NDOF,piminus_TRACK_CHI2NDOF));
        }
        else if(set==7){
          mynPVs->setVal(nPVs);
          mynSPDHits->setVal(nSPDHits);
          mynOTClusters->setVal(nOTClusters);
        }
        if(piminus_TRACK_Type==3){
          weight->setVal(1./(selected_LL));
          data_Bs_LL->add(*Obs, weight->getVal());
        }
        else if(piminus_TRACK_Type==5){
          weight->setVal(1./(selected_DD));
          data_Bs_DD->add(*Obs, weight->getVal());
        }
      }
    }
    // Reset
    DOCA_min = 999;
  }


  // Free Memory
  delete chain_Bd;
  delete chain_Bs;

// ***** Part II: Plot ***** //
///////////////////////////////  

  std::cout << std::endl;
  std::cout << "== Part II: Plot ==" << std::endl;
  std::cout << "===================" << std::endl;

  if(set==1){
    PullPlot(data_Bd_LL,data_Bs_LL,myB_FullFit_chi2,0.,72.,72,"/(1)","DTF #chi^{2}","B_FullFit_chi2_LL.pdf");
    PullPlot(data_Bd_DD,data_Bs_DD,myB_FullFit_chi2,0.,72.,72,"/(1)","DTF #chi^{2}","B_FullFit_chi2_DD.pdf");
    PullPlot(data_Bd_LL,data_Bs_LL,myB_DIRA_OWNPV,0.,0.1,100,"/(0.001)","acos(DIRA)","B_DIRA_OWNPV_LL.pdf",1.);
    PullPlot(data_Bd_DD,data_Bs_DD,myB_DIRA_OWNPV,0.,0.1,100,"/(0.001)","acos(DIRA)","B_DIRA_OWNPV_DD.pdf",1.);
    PullPlot(data_Bd_LL,data_Bs_LL,myKS0_PT,0.,15000.,100,"/(1500 MeV/c)","K_{S}^{0} Transverse Momentum (MeV/c)","KS0_PT_LL.pdf");
    PullPlot(data_Bd_DD,data_Bs_DD,myKS0_PT,0.,15000.,100,"/(1500 MeV/c)","K_{S}^{0} Transverse Momentum (MeV/c)","KS0_PT_DD.pdf");
    PullPlot(data_Bd_LL,data_Bs_LL,myB_FullFit_MERR,0.,25.,50,"/(0.5 MeV/c)","B_{d}^{0} Mass Error","B_FullFit_MERR_LL.pdf",1.);
    PullPlot(data_Bd_DD,data_Bs_DD,myB_FullFit_MERR,0.,25.,50,"/(0.5 MeV/c)","B_{d}^{0} Mass Error","B_FullFit_MERR_DD.pdf",1.);
    PullPlot(data_Bd_LL,data_Bs_LL,myPsi_MINIPCHI2,0.,1000.,100,"/(10)","J/#psi Min IP #chi^{2}","Psi_MINIPCHI2_LL.pdf",1.);
    PullPlot(data_Bd_DD,data_Bs_DD,myPsi_MINIPCHI2,0.,1000.,100,"/(10)","J/#psi Min IP #chi^{2}","Psi_MINIPCHI2_DD.pdf",1.);
  }
  else if(set==2){
    PullPlot(data_Bd_LL,data_Bs_LL,myB_FullFit_ctau,0.,5.,50,"/(0.1 ps)","B_{d}^{0} Decay Time (ps)","B_FullFit_ctau_LL.pdf",1.);
    PullPlot(data_Bd_DD,data_Bs_DD,myB_FullFit_ctau,0.,5.,50,"/(0.1 ps)","B_{d}^{0} Decay Time (ps)","B_FullFit_ctau_DD.pdf",1.);
    PullPlot(data_Bd_LL,data_Bs_LL,myB_ENDVERTEX_CHI2,0.,10.,100,"/(0.1)","B_{d}^{0} Endvertex #chi^{2}_{NDOF}","B_ENDVERTEX_CHI2_LL.pdf");
    PullPlot(data_Bd_DD,data_Bs_DD,myB_ENDVERTEX_CHI2,0.,10.,100,"/(0.1)","B_{d}^{0} Endvertex #chi^{2}_{NDOF}","B_ENDVERTEX_CHI2_DD.pdf");
    PullPlot(data_Bd_LL,data_Bs_LL,myB_PT,0.,40000.,80,"/(500 MeV/c)","B_{d}^{0} Transverse Momentum (MeV/c)","B_PT_LL.pdf");
    PullPlot(data_Bd_DD,data_Bs_DD,myB_PT,0.,40000.,80,"/(500 MeV/c)","B_{d}^{0} Transverse Momentum (MeV/c)","B_PT_DD.pdf");
    PullPlot(data_Bd_LL,data_Bs_LL,myB_P,0.,500000.,100,"/(5000 MeV/c)","B_{d}^{0} Momentum (MeV/c)","B_P_LL.pdf");
    PullPlot(data_Bd_DD,data_Bs_DD,myB_P,0.,500000.,100,"/(5000 MeV/c)","B_{d}^{0} Momentum (MeV/c)","B_P_DD.pdf");
    PullPlot(data_Bd_LL,data_Bs_LL,myB_FullFit_ctauErr,0.,0.05,50,"/(0.001 ps)","B_{d}^{0} Decay Time Error (ps)","B_FullFit_ctauErr_LL.pdf",1.);
    PullPlot(data_Bd_DD,data_Bs_DD,myB_FullFit_ctauErr,0.,0.05,50,"/(0.001 ps)","B_{d}^{0} Decay Time Error (ps)","B_FullFit_ctauErr_DD.pdf",1.);
  }
  else if(set==3){
    PullPlot(data_Bd_LL,data_Bs_LL,myPsi_FDCHI2_ORIVX,0.,1.,100,"/(0.01)","J/#psi Flight Distance #chi^{2}","Psi_FDCHI2_ORIVX_LL.pdf",1.);
    PullPlot(data_Bd_DD,data_Bs_DD,myPsi_FDCHI2_ORIVX,0.,1.,100,"/(0.01)","J/#psi Flight Distance #chi^{2}","Psi_FDCHI2_ORIVX_DD.pdf",1.);
    PullPlot(data_Bd_LL,data_Bs_LL,myPsi_MM,0.,50.,100,"/(0.5 MeV/c^{2})","|m_{J/#psi} - 3099| (MeV/c^{2})","Psi_MM_LL.pdf");
    PullPlot(data_Bd_DD,data_Bs_DD,myPsi_MM,0.,50.,100,"/(0.5 MeV/c^{2})","|m_{J/#psi} - 3099| (MeV/c^{2})","Psi_MM_DD.pdf");
    PullPlot(data_Bd_LL,data_Bs_LL,myPsi_MMERR,0.,25.,50,"/(0.5 MeV/c^{2})","J/#psi Mass Error (MeV/c^{2})","Psi_MMERR_LL.pdf",1.);
    PullPlot(data_Bd_DD,data_Bs_DD,myPsi_MMERR,0.,25.,50,"/(0.5 MeV/c^{2})","J/#psi Mass Error (MeV/c^{2})","Psi_MMERR_DD.pdf",1.);    
    PullPlot(data_Bd_LL,data_Bs_LL,myPsi_P,0.,500000.,100,"/(5000 MeV/c)","J/#psi Momentum (MeV/c)","Psi_P_LL.pdf");
    PullPlot(data_Bd_DD,data_Bs_DD,myPsi_P,0.,500000.,100,"/(5000 MeV/c)","J/#psi Momentum (MeV/c)","Psi_P_DD.pdf");
    PullPlot(data_Bd_LL,data_Bs_LL,myPsi_PT,0.,30000.,60,"/(500 MeV/c)","J/#psi Transverse Momentum (MeV/c)","Psi_PT_LL.pdf",1.);
    PullPlot(data_Bd_DD,data_Bs_DD,myPsi_PT,0.,30000.,60,"/(500 MeV/c)","J/#psi Transverse Momentum (MeV/c)","Psi_PT_DD.pdf",1.);
  }
  else if(set==4){
    PullPlot(data_Bd_LL,data_Bs_LL,myKS0_ENDVERTEX_Z,0.,1000.,100,"/(10 mm)","K_{S}^{0} End Vertex Z (mm)","KS0_ENDVERTEX_Z_LL.pdf");
    PullPlot(data_Bd_DD,data_Bs_DD,myKS0_ENDVERTEX_Z,0.,1000.,100,"/(10 mm)","K_{S}^{0} End Vertex Z (mm)","KS0_ENDVERTEX_Z_DD.pdf");
    PullPlot(data_Bd_LL,data_Bs_LL,myB_FullFit_KS0_ctau,0.,25.,50,"/(0.5 ps)","K_{S}^{0} Decay Time (ps)","B_FullFit_KS0_ctau_LL.pdf",1.);
    PullPlot(data_Bd_DD,data_Bs_DD,myB_FullFit_KS0_ctau,0.,25.,50,"/(0.5 ps)","K_{S}^{0} Decay Time (ps)","B_FullFit_KS0_ctau_DD.pdf",1.);
    PullPlot(data_Bd_LL,data_Bs_LL,myB_FullFit_KS0_ctauErr,0.,500.,100,"/(5)","K_{S}^{0} Decay Time Significance","B_FullFit_KS0_ctauErr_LL.pdf");
    PullPlot(data_Bd_DD,data_Bs_DD,myB_FullFit_KS0_ctauErr,0.,500.,100,"/(5)","K_{S}^{0} Decay Time Significance","B_FullFit_KS0_ctauErr_DD.pdf");
    PullPlot(data_Bd_LL,data_Bs_LL,myKS0_ENDVERTEX_CHI2,0.,20.,100,"/(0.2)","K_{S}^{0} End Vertex #chi^{2}","KS0_ENDVERTEX_CHI2_LL.pdf");
    PullPlot(data_Bd_DD,data_Bs_DD,myKS0_ENDVERTEX_CHI2,0.,20.,100,"/(0.2)","K_{S}^{0} End Vertex #chi^{2}","KS0_ENDVERTEX_CHI2_DD.pdf");
    PullPlot(data_Bd_LL,data_Bs_LL,myKS0_MINIPCHI2,0.,1000.,100,"/(10)","K_{S}^{0} Min IP #chi^{2}","KS0_MINIPCHI2_LL.pdf",1.);
    PullPlot(data_Bd_DD,data_Bs_DD,myKS0_MINIPCHI2,0.,1000.,100,"/(10)","K_{S}^{0} Min IP #chi^{2}","KS0_MINIPCHI2_DD.pdf",1.);
    PullPlot(data_Bd_LL,data_Bs_LL,myKS0_MM,0.,40.,80,"/(0.5 MeV/c^{2})","|m_{K_{S}^{0}} - 497.6| (MeV/c^{2})","KS0_MM_LL.pdf",1.);
    PullPlot(data_Bd_DD,data_Bs_DD,myKS0_MM,0.,40.,80,"/(0.5 MeV/c^{2})","|m_{K_{S}^{0}} - 497.6| (MeV/c^{2})","KS0_MM_DD.pdf",1.);
    PullPlot(data_Bd_LL,data_Bs_LL,myKS0_MMERR,0.,20.,100,"/(0.2 MeV/c^{2})","K_{S}^{0} Mass Error (MeV/c^{2})","KS0_MMERR_LL.pdf",1.);
    PullPlot(data_Bd_DD,data_Bs_DD,myKS0_MMERR,0.,20.,100,"/(0.2 MeV/c^{2})","K_{S}^{0} Mass Error (MeV/c^{2})","KS0_MMERR_DD.pdf",1.);
    PullPlot(data_Bd_LL,data_Bs_LL,myKS0_P,0.,100000.,100,"/(1000 MeV/c)","K_{S}^{0} Momentum (MeV/c)","KS0_P_LL.pdf");
    PullPlot(data_Bd_DD,data_Bs_DD,myKS0_P,0.,100000.,100,"/(1000 MeV/c)","K_{S}^{0} Momentum (MeV/c)","KS0_P_DD.pdf");
  }
  else if(set==5){
    PullPlot(data_Bd_LL,data_Bs_LL,mymu_MINIPCHI2,0.,1000.,100,"/(10)","Min #mu Min IP #chi^{2}","mu_MINIPCHI2_LL.pdf",1.);
    PullPlot(data_Bd_DD,data_Bs_DD,mymu_MINIPCHI2,0.,1000.,100,"/(10)","Min #mu Min IP #chi^{2}","mu_MINIPCHI2_DD.pdf",1.);
    PullPlot(data_Bd_LL,data_Bs_LL,mymu_MINIP,0.,3.5,70,"/(0.05)","Min #mu Min IP","mu_MINIP_LL.pdf",1.);
    PullPlot(data_Bd_DD,data_Bs_DD,mymu_MINIP,0.,3.5,70,"/(0.05)","Min #mu Min IP","mu_MINIP_DD.pdf",1.);
    PullPlot(data_Bd_LL,data_Bs_LL,mymu_P,0.,100000.,100,"/(1000 MeV/c)","Min #mu Momentum (MeV/c)","mu_P_LL.pdf");
    PullPlot(data_Bd_DD,data_Bs_DD,mymu_P,0.,100000.,100,"/(1000 MeV/c)","Min #mu Momentum (MeV/c)","mu_P_DD.pdf");
    PullPlot(data_Bd_LL,data_Bs_LL,mymu_PT,0.,10000.,100,"/(1000 MeV/c)","Min #mu Transverse Momentum","mu_PT_LL.pdf");
    PullPlot(data_Bd_DD,data_Bs_DD,mymu_PT,0.,10000.,100,"/(1000 MeV/c)","Min #mu Transverse Momentum","mu_PT_DD.pdf");
    PullPlot(data_Bd_LL,data_Bs_LL,mymu_PIDmu,0.,13.,65,"/(0.2)","Min #mu PID","mu_PIDmu_LL.pdf");
    PullPlot(data_Bd_DD,data_Bs_DD,mymu_PIDmu,0.,13.,65,"/(0.2)","Min #mu PID","mu_PIDmu_DD.pdf");
    PullPlot(data_Bd_LL,data_Bs_LL,mymu_TRACK_CHI2NDOF,0.,5.,50,"/(0.1)","Max #mu Track #chi^{2}_{NDOF}","mu_TRACK_CHI2NDOF_LL.pdf",1.);
    PullPlot(data_Bd_DD,data_Bs_DD,mymu_TRACK_CHI2NDOF,0.,5.,50,"/(0.1)","Max #mu Track #chi^{2}_{NDOF}","mu_TRACK_CHI2NDOF_DD.pdf",1.);
  }
  else if(set==6){
    PullPlot(data_Bd_LL,data_Bs_LL,mypi_MINIP,0.,10,100,"/(0.1)","Min #pi Min IP","pi_MINIP_LL.pdf");
    PullPlot(data_Bd_DD,data_Bs_DD,mypi_MINIP,0.,10,100,"/(0.1)","Min #pi Min IP","pi_MINIP_DD.pdf");
    PullPlot(data_Bd_LL,data_Bs_LL,mypi_PT,0.,5000.,100,"/(500 MeV/c)","Min #pi Transverse Momentum","pi_PT_LL.pdf");
    PullPlot(data_Bd_DD,data_Bs_DD,mypi_PT,0.,5000.,100,"/(500 MeV/c)","Min #pi Transverse Momentum","pi_PT_DD.pdf");
    PullPlot(data_Bd_LL,data_Bs_LL,mypi_TRACK_GhostProb,0.,1.,100,"/(0.01)","Max #pi Track Ghost Prob","pi_TRACK_GhostProb_LL.pdf",1.);
    PullPlot(data_Bd_DD,data_Bs_DD,mypi_TRACK_GhostProb,0.,1.,100,"/(0.01)","Max #pi Track Ghost Prob","pi_TRACK_GhostProb_DD.pdf",1.);
    PullPlot(data_Bd_LL,data_Bs_LL,mypi_TRACK_CHI2NDOF,0.,5.,50,"/(0.1)","Max #pi Track #chi^{2}_{NDOF}","pi_TRACK_CHI2NDOF_LL.pdf",1.);
    PullPlot(data_Bd_DD,data_Bs_DD,mypi_TRACK_CHI2NDOF,0.,5.,50,"/(0.1)","Max #pi Track #chi^{2}_{NDOF}","pi_TRACK_CHI2NDOF_DD.pdf",1.);
  }
  else if(set==7){
    PullPlot(data_Bd_LL,data_Bs_LL,mynPVs,0.,10.,10,"/(1)","Number of PVs","nPVs_LL.pdf",1.);
    PullPlot(data_Bd_DD,data_Bs_DD,mynPVs,0.,10.,10,"/(1)","Number of PVs","nPVs_DD.pdf",1.);
    PullPlot(data_Bd_LL,data_Bs_LL,mynSPDHits,0.,700.,70,"/(10)","Number of SPD hits","nSPDHits_LL.pdf");
    PullPlot(data_Bd_DD,data_Bs_DD,mynSPDHits,0.,700.,70,"/(10)","Number of SPD hits","nSPDHits_DD.pdf");
    PullPlot(data_Bd_LL,data_Bs_LL,mynOTClusters,0.,10000.,100,"/(100)","Number of OT Clusters","nOTClusters_LL.pdf");
    PullPlot(data_Bd_DD,data_Bs_DD,mynOTClusters,0.,10000.,100,"/(100)","Number of OT Clusters","nOTClusters_DD.pdf");
  }
}


///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void PullPlot(RooDataSet *data_Bd, RooDataSet *data_Bs, RooRealVar *Obs,Double_t bin_low, Double_t bin_high, Int_t bins, TString scale, TString Obs_title, TString savestring,Double_t max){

  // ***** Distribution ***** //
  //////////////////////////////

  // *** Canvas ***
  TCanvas *doek = new TCanvas("doek","Observable",900,800);
  doek->cd(1);
  Float_t ratio = 0.45; // Percentage of the plot for Pull distributions
  
  // *** RooPlot ***
  RooPlot* frame = Obs->frame(Range(bin_low,bin_high),Bins(bins));

  // Titles
  frame->SetYTitle("Events"+scale);
  frame->SetXTitle(Obs_title);

  // Cosmetics
  frame->SetTitleOffset(1.2,"y");
  frame->SetTitleSize(0.07,"y");
  frame->SetTitleFont(132,"y");
  frame->SetLabelSize(0.03,"y");
  frame->SetLabelFont(132,"y");

  data_Bd->plotOn(frame,DataError(RooAbsData::SumW2),MarkerStyle(21),MarkerSize(0.8),MarkerColor(2),LineColor(2));
  data_Bs->plotOn(frame,DataError(RooAbsData::SumW2),MarkerStyle(22),MarkerSize(1),MarkerColor(4),LineColor(4));

  frame->SetMinimum(0.00009);
  frame->SetMaximum(max);
  
  // *** Place the first frame ***
  // To keep the correct scale of the labels, use the Margins instead of Pad coordinates
  TPad* xPad = new TPad("xPad", "Pad for Observable Plot", 0., 0, 1., 1.);
  xPad->SetLeftMargin(0.2);
  xPad->SetBottomMargin(ratio);  
  // Draw Pad  
  xPad->Draw();
  xPad->cd();
  xPad->SetLogy(1);
  // Suppress X-axis decoration
  frame->SetLabelSize(0,"x");
  frame->SetTitleSize(0,"x");
  // Fill Pad  
  frame->Draw("");

  
  // *** LHCb Tag ***
  string convSave (savestring);
  TString track("");
  if(convSave.find("LL")!=string::npos) track = "Long K_{S}^{0}";
  else if(convSave.find("DD")!=string::npos) track = "Downstream K_{S}^{0}";
  TPaveText *lhcbTag = new TPaveText(0.65,0.75,0.89,0.89,"NDC");
  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  lhcbTag->AddText("#splitline{LHCb MC11a}{#scale[0.7]{"+track+"}}");
  lhcbTag->Draw("");
  
  
  // *** Legend *** 
  // Very nasty trick to get the dot in he legend in the correct color
  Float_t red_point[2];
  red_point[0] = 0;
  red_point[1] = 1;
  TGraph *red_contour = new TGraph(2,red_point,red_point);
  red_contour->SetMarkerStyle(21);
  red_contour->SetMarkerSize(1);
  red_contour->SetMarkerColor(2);
  red_contour->SetLineColor(2);
  
  Float_t blue_point[2];
  blue_point[0] = 0;
  blue_point[1] = 1;
  TGraph *blue_contour = new TGraph(2,blue_point,blue_point);
  blue_contour->SetMarkerStyle(23);
  blue_contour->SetMarkerSize(0.8);
  blue_contour->SetMarkerColor(4);
  blue_contour->SetLineColor(4);

  TLegend *leg = new TLegend(0.65,0.65,0.89,0.75);
  leg->AddEntry(blue_contour,"B_{d}^{0}#rightarrow J/#psi K_{S}^{0}","lep");
  leg->AddEntry(red_contour,"B_{s}^{0}#rightarrow J/#psi K_{S}^{0}","lep");
  leg->SetTextAlign(12);
  leg->SetTextSize(0.03);
  leg->SetTextFont(132);
  leg->Draw("");
  
  // ***** Make Histograms ***** //
  /////////////////////////////////
  
  // *** Prepare the Second frame ***
  // go back to the Bottom layer
  doek->cd();
  // To keep the correct scale of the labels, use the Margins instead of Pad coordinates
  TPad* pullPad = new TPad("pullPad", "Pad for Pull Plot", 0., 0., 1., 1);
  pullPad->SetLeftMargin(0.2);
  pullPad->SetBottomMargin(0.15);  
  pullPad->SetTopMargin(1-ratio+0.01);
  // Make the pad transparent
  pullPad->SetFillColor(0);
  pullPad->SetFillStyle(0);
  // Draw Pad  
  pullPad->Draw();
  pullPad->cd();
  gPad->SetTicks(1,1);
  
  
  // *** Construct Histogram Ratio ***
  TH1D *hist_Bd = (TH1D *)data_Bd->createHistogram("hist_Bd",*Obs,Binning(bins,bin_low,bin_high));
  TH1D *hist_Bs = (TH1D *)data_Bs->createHistogram("hist_Bs",*Obs,Binning(bins,bin_low,bin_high));
  TH1D *hist_Diff = (TH1D *)hist_Bs->Clone("hist_Diff");
  hist_Diff->Divide(hist_Bd);
  
  // *** Cosmetics ***
  hist_Diff->SetStats(0);
  hist_Diff->SetMinimum(0.5);
  hist_Diff->SetMaximum(1.5);
  hist_Diff->SetNdivisions(504,"Y");
  
  hist_Diff->SetXTitle(Obs_title);
  hist_Diff->SetYTitle("");
  hist_Diff->SetTitleOffset(0.9,"x");
  hist_Diff->SetTitleOffset(1.2,"y");
  hist_Diff->SetTitleSize(0.07,"x");
  hist_Diff->SetTitleSize(0.07,"y");
  hist_Diff->SetTitleFont(132,"y");
  hist_Diff->SetTitleFont(132,"x");
  hist_Diff->SetLabelSize(0.03,"y");
  hist_Diff->SetLabelSize(0.03,"x");
  hist_Diff->SetLabelFont(132,"x");
  hist_Diff->SetLabelFont(132,"y");
  
  hist_Diff->SetMarkerStyle(8);
  hist_Diff->SetMarkerSize(1);
  hist_Diff->SetMarkerColor(1);
  
  // *** Draw ***
  hist_Diff->Draw("");
  
  // Benchmark
  Float_t red_bench[2];
  red_bench[0] = bin_low;
  red_bench[1] = bin_high;
  Float_t one[2];
  one[0] = 1;
  one[1] = 1;
  TGraph *red_line = new TGraph(2,red_bench,one);
  red_line->SetLineColor(2);
  red_line->SetLineWidth(2);
  red_line->Draw("");
  
  // *** Save ***
  doek->SaveAs(savestring);
  
  return;
}
