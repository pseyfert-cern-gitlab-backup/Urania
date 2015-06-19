// #############################################################################
// Phys/Bs2JpsiKs Package
// Reduce DaVinci Tuple size
// Authors: Patrick Koppenburg & Kristof De Bruyn
// #############################################################################


// #############################################################################
// *** Load Useful Classes ***
// General C++
#include <iostream>

// ROOT
#include <RooArgList.h>
#include <RooCategory.h>
#include <RooRealVar.h>

#include <TBranch.h>
#include <TFile.h>
#include <TTree.h>

// Bs2JpsiKs Package
#include "IB2JpsiX.h"
#include "TupleLoader.h"

// Tagging
#include "MistagCalibration.h"
#include "DLLTagCombiner.h"
#include "TagDLLToTagDec.h"
#include "TagDLLToTagEta.h"

// #############################################################################
// *** MINIP ***
Float_t MINIP (Float_t allip[100], int nPVs) {
  Float_t minip = allip[0];
  for (unsigned int i = 0; i<nPVs; i++) {
    if (allip[i] < minip) {
      minip = allip[i];
    }
  }
  return minip;
}

// #############################################################################
// *** B2JpsiKs ***
int slimmingB2JpsiKs(const TString module, const TString data,
                     const TString step, const TString dir,
                     const TString decay, const TString weightMethod) {

// ***** PART I: Initialise ***** //
////////////////////////////////////

  const int nCalib = 5; // Number of Tag Combinations

  std::cout << "\n PROGRESS: Load Input TTree \n" << std::endl;

  // *** Load Original NTuple ***
  B2JpsiKs* ntuple = loadB2JpsiKsTuple(module, data, step, dir, decay,
                                       weightMethod);

  std::cout << "\n PROGRESS: Initialising Output TTree \n" << std::endl;
  
  // *** Create Target NTuple ***
  TString outFileName = makeFileName(module, data, step, dir, decay,
                                     weightMethod);
  // Error Handling
  if (outFileName=="") {
    std::cout << "ERROR: Failed to generate output file." << std::endl;
    return -255 ;
  }
  TFile* outfile = new TFile(outFileName, "RECREATE" );
  outfile->cd();
  TTree* outtree = new TTree("Slim_"+decay+"_Tuple", "Slimmed down Decay Tree Tuple");

  // *** Declare Observables and Create Branches ***  

  // *** File/Event Tracking ***
  Int_t myB0_FitDaughtersPVConst_nPV;
    outtree->Branch("B0_FitDaughtersPVConst_nPV", &myB0_FitDaughtersPVConst_nPV,
    "B0_FitDaughtersPVConst_nPV/I");
  Int_t myInputFile;
    outtree->Branch("InputFile", &myInputFile,
    "InputFile/I");
  Int_t myPassLoose[maxLeafs];
    outtree->Branch("PassLoose", &myPassLoose,
    "PassLoose[B0_FitDaughtersPVConst_nPV]/I");

  // *** Observables ***  
  Float_t myB0_FitDaughtersPVConst_M[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_M", &myB0_FitDaughtersPVConst_M,
    "B0_FitDaughtersPVConst_M[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_tau[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_tau", &myB0_FitDaughtersPVConst_tau,
    "B0_FitDaughtersPVConst_tau[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_tauErr[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_tauErr", &myB0_FitDaughtersPVConst_tauErr,
    "B0_FitDaughtersPVConst_tauErr[B0_FitDaughtersPVConst_nPV]/F");
  Int_t myB0_TAGDECISION_OS;
    outtree->Branch("B0_TAGDECISION_OS", &myB0_TAGDECISION_OS,
    "B0_TAGDECISION_OS/I");
  Double_t myB0_TAGOMEGA_OS;
    outtree->Branch("B0_TAGOMEGA_OS", &myB0_TAGOMEGA_OS,
    "B0_TAGOMEGA_OS/D");
  Int_t myobsTagOS_StdComb;
    outtree->Branch("obsTagOS_StdComb", &myobsTagOS_StdComb,
    "obsTagOS_StdComb/I");
  Double_t myobsEtaOS_StdComb;
    outtree->Branch("obsEtaOS_StdComb", &myobsEtaOS_StdComb,
    "obsEtaOS_StdComb/D");
  Short_t myB0_SS_Kaon_DEC;
    outtree->Branch("B0_SS_Kaon_DEC", &myB0_SS_Kaon_DEC,
    "B0_SS_Kaon_DEC/S");
  Float_t myB0_SS_Kaon_PROB;
    outtree->Branch("B0_SS_Kaon_PROB", &myB0_SS_Kaon_PROB,
    "B0_SS_Kaon_PROB/F");
  Short_t myB0_SS_nnetKaon_DEC;
    outtree->Branch("B0_SS_nnetKaon_DEC", &myB0_SS_nnetKaon_DEC,
    "B0_SS_nnetKaon_DEC/S");
  Float_t myB0_SS_nnetKaon_PROB;
    outtree->Branch("B0_SS_nnetKaon_PROB", &myB0_SS_nnetKaon_PROB,
    "B0_SS_nnetKaon_PROB/F");

  // *** Tag Combinations ***
  Int_t myB0_CombinedTag_Dec[nCalib];
  Double_t myB0_CombinedTag_Omega[nCalib];

  outtree->Branch("B0_CombinedTag_Dec",
    &myB0_CombinedTag_Dec[0], "B0_CombinedTag_Dec/I");
  outtree->Branch("B0_CombinedTag_Omega",
    &myB0_CombinedTag_Omega[0], "B0_CombinedTag_Omega/D");
  outtree->Branch("B0_CombinedTag_Dec_psig",
    &myB0_CombinedTag_Dec[1], "B0_CombinedTag_Dec_psig/I");
  outtree->Branch("B0_CombinedTag_Omega_psig",
    &myB0_CombinedTag_Omega[1], "B0_CombinedTag_Omega_psig/D");
  outtree->Branch("B0_CombinedTag_Dec_msig",
    &myB0_CombinedTag_Dec[2], "B0_CombinedTag_Dec_msig/I");
  outtree->Branch("B0_CombinedTag_Omega_msig",
    &myB0_CombinedTag_Omega[2], "B0_CombinedTag_Omega_msig/D");
  outtree->Branch("B0_CombinedTag_Dec_trueB",
    &myB0_CombinedTag_Dec[3], "B0_CombinedTag_Dec_trueB/I");
  outtree->Branch("B0_CombinedTag_Omega_trueB",
    &myB0_CombinedTag_Omega[3], "B0_CombinedTag_Omega_trueB/D");
  outtree->Branch("B0_CombinedTag_Dec_trueBbar",
    &myB0_CombinedTag_Dec[4], "B0_CombinedTag_Dec_trueBbar/I");
  outtree->Branch("B0_CombinedTag_Omega_trueBbar",
    &myB0_CombinedTag_Omega[4], "B0_CombinedTag_Omega_trueBbar/D");

  // *** Data Manipulation ***
  UInt_t myrunNumber;
    outtree->Branch("runNumber", &myrunNumber,
    "runNumber/i");
  ULong64_t myeventNumber;
    outtree->Branch("eventNumber", &myeventNumber,
    "eventNumber/l");
  Short_t myPolarity;
    outtree->Branch("Polarity", &myPolarity,
    "Polarity/S");

  // *** Observables for Common Selection Cuts ***
  Float_t myB0_FitDaughtersPVConst_status[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_status", &myB0_FitDaughtersPVConst_status,
    "B0_FitDaughtersPVConst_status[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_chi2[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_chi2", &myB0_FitDaughtersPVConst_chi2,
    "B0_FitDaughtersPVConst_chi2[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_MERR[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_MERR", &myB0_FitDaughtersPVConst_MERR,
    "B0_FitDaughtersPVConst_MERR[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_PV_Z[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_PV_Z", &myB0_FitDaughtersPVConst_PV_Z,
    "B0_FitDaughtersPVConst_PV_Z[B0_FitDaughtersPVConst_nPV]/F");

  // *** Observables for Decay Specific Cuts ***
  Int_t mypiplus_TRACK_Type;
    outtree->Branch("piplus_TRACK_Type", &mypiplus_TRACK_Type,
    "piplus_TRACK_Type/I");
  Float_t myB0_FitSubstppi1_KS0_M[maxLeafs];
    outtree->Branch("B0_FitSubstppi1_KS0_M", &myB0_FitSubstppi1_KS0_M,
    "B0_FitSubstppi1_KS0_M[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitSubstppi2_KS0_M[maxLeafs];
    outtree->Branch("B0_FitSubstppi2_KS0_M", &myB0_FitSubstppi2_KS0_M,
    "B0_FitSubstppi2_KS0_M[B0_FitDaughtersPVConst_nPV]/F");
  Double_t mypiminus_ProbNNk;
    outtree->Branch("piminus_ProbNNk", &mypiminus_ProbNNk,
    "piminus_ProbNNk/D");
  Double_t mypiplus_ProbNNk;
    outtree->Branch("piplus_ProbNNk", &mypiplus_ProbNNk,
    "piplus_ProbNNk/D");
  Float_t myB0_FitDaughtersPVConst_KS0_ctau[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_KS0_ctau", &myB0_FitDaughtersPVConst_KS0_ctau,
    "B0_FitDaughtersPVConst_KS0_ctau[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myJ_psi_1S_MINIPCHI2_OtherPVs[maxLeafs];
    outtree->Branch("J_psi_1S_MINIPCHI2_OtherPVs", &myJ_psi_1S_MINIPCHI2_OtherPVs,
    "J_psi_1S_MINIPCHI2_OtherPVs[B0_FitDaughtersPVConst_nPV]/F");

  // *** Trigger ***
  Bool_t myJ_psi_1S_Hlt1TrackMuonDecision_TOS;
    outtree->Branch("J_psi_1S_Hlt1TrackMuonDecision_TOS", &myJ_psi_1S_Hlt1TrackMuonDecision_TOS,
    "J_psi_1S_Hlt1TrackMuonDecision_TOS/O");
  Bool_t myJ_psi_1S_Hlt1DiMuonHighMassDecision_TOS;
    outtree->Branch("J_psi_1S_Hlt1DiMuonHighMassDecision_TOS", &myJ_psi_1S_Hlt1DiMuonHighMassDecision_TOS,
    "J_psi_1S_Hlt1DiMuonHighMassDecision_TOS/O");
  Bool_t myJ_psi_1S_Hlt1TrackAllL0Decision_TOS;
    outtree->Branch("J_psi_1S_Hlt1TrackAllL0Decision_TOS", &myJ_psi_1S_Hlt1TrackAllL0Decision_TOS,
    "J_psi_1S_Hlt1TrackAllL0Decision_TOS/O");
  Bool_t myJ_psi_1S_Hlt2DiMuonDetachedJPsiDecision_TOS;
    outtree->Branch("J_psi_1S_Hlt2DiMuonDetachedJPsiDecision_TOS", &myJ_psi_1S_Hlt2DiMuonDetachedJPsiDecision_TOS,
    "J_psi_1S_Hlt2DiMuonDetachedJPsiDecision_TOS/O");
  Bool_t myJ_psi_1S_Hlt2DiMuonJPsiHighPTDecision_TOS;
    outtree->Branch("J_psi_1S_Hlt2DiMuonJPsiHighPTDecision_TOS", &myJ_psi_1S_Hlt2DiMuonJPsiHighPTDecision_TOS,
    "J_psi_1S_Hlt2DiMuonJPsiHighPTDecision_TOS/O");
  Bool_t myJ_psi_1S_Hlt2DiMuonJPsiDecision_TOS;
    outtree->Branch("J_psi_1S_Hlt2DiMuonJPsiDecision_TOS", &myJ_psi_1S_Hlt2DiMuonJPsiDecision_TOS,
    "J_psi_1S_Hlt2DiMuonJPsiDecision_TOS/O");
  Bool_t myJ_psi_1S_Hlt2TopoMu2BodyBBDTDecision_TOS;
    outtree->Branch("J_psi_1S_Hlt2TopoMu2BodyBBDTDecision_TOS", &myJ_psi_1S_Hlt2TopoMu2BodyBBDTDecision_TOS,
    "J_psi_1S_Hlt2TopoMu2BodyBBDTDecision_TOS/O");

  // *** Neural Net ***
  Int_t mynOTClusters;
    outtree->Branch("nOTClusters", &mynOTClusters,
    "nOTClusters/I");
  Float_t myPVCHI2[maxLeafs];
  outtree->Branch("PVCHI2", &myPVCHI2,
    "PVCHI2[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myPVNTRACKS[maxLeafs];
  outtree->Branch("PVNTRACKS", &myPVNTRACKS,
    "PVNTRACKS[B0_FitDaughtersPVConst_nPV]/F");
  Int_t mynSPDHits;
    outtree->Branch("nSPDHits", &mynSPDHits,
    "nSPDHits/I");

  Float_t myB0_FitDaughtersPVConst_PT[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_PT", &myB0_FitDaughtersPVConst_PT,
    "B0_FitDaughtersPVConst_PT[B0_FitDaughtersPVConst_nPV]/F");
  Double_t myB0_ENDVERTEX_CHI2;
    outtree->Branch("B0_ENDVERTEX_CHI2", &myB0_ENDVERTEX_CHI2,
    "B0_ENDVERTEX_CHI2/D");
  Int_t myB0_ENDVERTEX_NDOF;
    outtree->Branch("B0_ENDVERTEX_NDOF", &myB0_ENDVERTEX_NDOF,
    "B0_ENDVERTEX_NDOF/I");
  Float_t myB0_FitDaughtersPVConst_P[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_P", &myB0_FitDaughtersPVConst_P,
    "B0_FitDaughtersPVConst_P[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_AllDIRA[maxLeafs];
    outtree->Branch("B0_AllDIRA", &myB0_AllDIRA,
    "B0_AllDIRA[B0_FitDaughtersPVConst_nPV]/F");

  Double_t myJ_psi_1S_ENDVERTEX_CHI2;
    outtree->Branch("J_psi_1S_ENDVERTEX_CHI2", &myJ_psi_1S_ENDVERTEX_CHI2,
    "J_psi_1S_ENDVERTEX_CHI2/D");
  Float_t myB0_FitDaughtersPVConst_J_psi_1S_IPCHI2[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_J_psi_1S_IPCHI2", &myB0_FitDaughtersPVConst_J_psi_1S_IPCHI2,
    "B0_FitDaughtersPVConst_J_psi_1S_IPCHI2[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitPVConst_J_psi_1S_M[maxLeafs];
    outtree->Branch("B0_FitPVConst_J_psi_1S_M", &myB0_FitPVConst_J_psi_1S_M,
    "B0_FitPVConst_J_psi_1S_M[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitPVConst_J_psi_1S_MERR[maxLeafs];
    outtree->Branch("B0_FitPVConst_J_psi_1S_MERR", &myB0_FitPVConst_J_psi_1S_MERR,
    "B0_FitPVConst_J_psi_1S_MERR[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_J_psi_1S_P[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_J_psi_1S_P", &myB0_FitDaughtersPVConst_J_psi_1S_P,
    "B0_FitDaughtersPVConst_J_psi_1S_P[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_J_psi_1S_PT[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_J_psi_1S_PT", &myB0_FitDaughtersPVConst_J_psi_1S_PT,
    "B0_FitDaughtersPVConst_J_psi_1S_PT[B0_FitDaughtersPVConst_nPV]/F");

  Float_t myB0_FitDaughtersPVConst_KS0_IPCHI2[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_KS0_IPCHI2", &myB0_FitDaughtersPVConst_KS0_IPCHI2,
    "B0_FitDaughtersPVConst_KS0_IPCHI2[B0_FitDaughtersPVConst_nPV]/F");
  Double_t myKS0_ENDVERTEX_CHI2;
    outtree->Branch("KS0_ENDVERTEX_CHI2", &myKS0_ENDVERTEX_CHI2,
    "KS0_ENDVERTEX_CHI2/D");
  Double_t myKS0_ENDVERTEX_Z;
    outtree->Branch("KS0_ENDVERTEX_Z", &myKS0_ENDVERTEX_Z,
    "KS0_ENDVERTEX_Z/D");
  Float_t myB0_FitDaughtersPVConst_KS0_ctauErr[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_KS0_ctauErr", &myB0_FitDaughtersPVConst_KS0_ctauErr,
    "B0_FitDaughtersPVConst_KS0_ctauErr[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitPVConst_KS0_MERR[maxLeafs];
    outtree->Branch("B0_FitPVConst_KS0_MERR", &myB0_FitPVConst_KS0_MERR,
    "B0_FitPVConst_KS0_MERR[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitPVConst_KS0_M[maxLeafs];
    outtree->Branch("B0_FitPVConst_KS0_M", &myB0_FitPVConst_KS0_M,
    "B0_FitPVConst_KS0_M[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_KS0_P[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_KS0_P", &myB0_FitDaughtersPVConst_KS0_P,
    "B0_FitDaughtersPVConst_KS0_P[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_KS0_PT[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_KS0_PT", &myB0_FitDaughtersPVConst_KS0_PT,
    "B0_FitDaughtersPVConst_KS0_PT[B0_FitDaughtersPVConst_nPV]/F");

  Float_t myB0_FitDaughtersPVConst_J_psi_1S_P0_IPCHI2[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_J_psi_1S_P0_IPCHI2", &myB0_FitDaughtersPVConst_J_psi_1S_P0_IPCHI2,
    "B0_FitDaughtersPVConst_J_psi_1S_P0_IPCHI2[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_J_psi_1S_P1_IPCHI2[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_J_psi_1S_P1_IPCHI2", &myB0_FitDaughtersPVConst_J_psi_1S_P1_IPCHI2,
    "B0_FitDaughtersPVConst_J_psi_1S_P1_IPCHI2[B0_FitDaughtersPVConst_nPV]/F");
  Double_t mymuminus_PIDmu;
    outtree->Branch("muminus_PIDmu", &mymuminus_PIDmu,
    "muminus_PIDmu/D");
  Double_t mymuplus_PIDmu;
    outtree->Branch("muplus_PIDmu", &mymuplus_PIDmu,
    "muplus_PIDmu/D");
  Float_t myB0_FitDaughtersPVConst_J_psi_1S_P0_IP[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_J_psi_1S_P0_IP", &myB0_FitDaughtersPVConst_J_psi_1S_P0_IP,
    "B0_FitDaughtersPVConst_J_psi_1S_P0_IP[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_J_psi_1S_P1_IP[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_J_psi_1S_P1_IP", &myB0_FitDaughtersPVConst_J_psi_1S_P1_IP,
    "B0_FitDaughtersPVConst_J_psi_1S_P1_IP[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_J_psi_1S_P0_P[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_J_psi_1S_P0_P", &myB0_FitDaughtersPVConst_J_psi_1S_P0_P,
    "B0_FitDaughtersPVConst_J_psi_1S_P0_P[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_J_psi_1S_P1_P[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_J_psi_1S_P1_P", &myB0_FitDaughtersPVConst_J_psi_1S_P1_P,
    "B0_FitDaughtersPVConst_J_psi_1S_P1_P[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_J_psi_1S_P0_PT[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_J_psi_1S_P0_PT", &myB0_FitDaughtersPVConst_J_psi_1S_P0_PT,
    "B0_FitDaughtersPVConst_J_psi_1S_P0_PT[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_J_psi_1S_P1_PT[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_J_psi_1S_P1_PT", &myB0_FitDaughtersPVConst_J_psi_1S_P1_PT,
    "B0_FitDaughtersPVConst_J_psi_1S_P1_PT[B0_FitDaughtersPVConst_nPV]/F");
  Double_t mymuminus_TRACK_CHI2NDOF;
    outtree->Branch("muminus_TRACK_CHI2NDOF", &mymuminus_TRACK_CHI2NDOF,
    "muminus_TRACK_CHI2NDOF/D");
  Double_t mymuplus_TRACK_CHI2NDOF;
    outtree->Branch("muplus_TRACK_CHI2NDOF", &mymuplus_TRACK_CHI2NDOF,
    "muplus_TRACK_CHI2NDOF/D");

  Double_t mypiminus_TRACK_GhostProb;
    outtree->Branch("piminus_TRACK_GhostProb", &mypiminus_TRACK_GhostProb,
    "piminus_TRACK_GhostProb/D");
  Double_t mypiplus_TRACK_GhostProb;
    outtree->Branch("piplus_TRACK_GhostProb", &mypiplus_TRACK_GhostProb,
    "piplus_TRACK_GhostProb/D");
  Float_t myB0_FitDaughtersPVConst_KS0_P0_IPCHI2[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_KS0_P0_IPCHI2", &myB0_FitDaughtersPVConst_KS0_P0_IPCHI2,
    "B0_FitDaughtersPVConst_KS0_P0_IPCHI2[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_KS0_P1_IPCHI2[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_KS0_P1_IPCHI2", &myB0_FitDaughtersPVConst_KS0_P1_IPCHI2,
    "B0_FitDaughtersPVConst_KS0_P1_IPCHI2[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_KS0_P0_IP[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_KS0_P0_IP", &myB0_FitDaughtersPVConst_KS0_P0_IP,
    "B0_FitDaughtersPVConst_KS0_P0_IP[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_KS0_P1_IP[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_KS0_P1_IP", &myB0_FitDaughtersPVConst_KS0_P1_IP,
    "B0_FitDaughtersPVConst_KS0_P1_IP[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_KS0_P0_P[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_KS0_P0_P", &myB0_FitDaughtersPVConst_KS0_P0_P,
    "B0_FitDaughtersPVConst_KS0_P0_P[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_KS0_P1_P[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_KS0_P1_P", &myB0_FitDaughtersPVConst_KS0_P1_P,
    "B0_FitDaughtersPVConst_KS0_P1_P[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_KS0_P0_PT[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_KS0_P0_PT", &myB0_FitDaughtersPVConst_KS0_P0_PT,
    "B0_FitDaughtersPVConst_KS0_P0_PT[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitDaughtersPVConst_KS0_P1_PT[maxLeafs];
    outtree->Branch("B0_FitDaughtersPVConst_KS0_P1_PT", &myB0_FitDaughtersPVConst_KS0_P1_PT,
    "B0_FitDaughtersPVConst_KS0_P1_PT[B0_FitDaughtersPVConst_nPV]/F");
  Double_t mypiminus_TRACK_CHI2NDOF;
    outtree->Branch("piminus_TRACK_CHI2NDOF", &mypiminus_TRACK_CHI2NDOF,
    "piminus_TRACK_CHI2NDOF/D");
  Double_t mypiplus_TRACK_CHI2NDOF;
    outtree->Branch("piplus_TRACK_CHI2NDOF", &mypiplus_TRACK_CHI2NDOF,
    "piplus_TRACK_CHI2NDOF/D");
    
  // *** Truth information ***
  Int_t myB0_TRUEID;
  Int_t myJ_psi_1S_TRUEID;
  Int_t myKS0_TRUEID;
  Int_t myB0_BKGCAT;

  Double_t myB0_TRUETAU;
  Float_t  myB0_FitDaughtersPVConst_PV_X[maxLeafs];
  Float_t  myB0_FitDaughtersPVConst_PV_Y[maxLeafs];
  Double_t myB0_TRUEORIGINVERTEX_X;
  Double_t myB0_TRUEORIGINVERTEX_Y;
  Double_t myB0_TRUEORIGINVERTEX_Z;
  Double_t myJ_psi_1S_TRUEORIGINVERTEX_X;
  Double_t myJ_psi_1S_TRUEORIGINVERTEX_Y;
  Double_t myJ_psi_1S_TRUEORIGINVERTEX_Z;
  Double_t myKS0_TRUEORIGINVERTEX_X;
  Double_t myKS0_TRUEORIGINVERTEX_Y;
  Double_t myKS0_TRUEORIGINVERTEX_Z;

  Int_t myJ_psi_1S_MC_MOTHER_ID;
  Int_t myJ_psi_1S_MC_GD_MOTHER_ID;
  Int_t myJ_psi_1S_MC_GD_GD_MOTHER_ID;
  Int_t myKS0_MC_MOTHER_ID;
  Int_t myKS0_MC_GD_MOTHER_ID;
  Int_t myKS0_MC_GD_GD_MOTHER_ID;
  
  if (isSigMC(data) || data==m_IncJpsi) {
    outtree->Branch("B0_TRUEID", &myB0_TRUEID,
      "B0_TRUEID/I");
    outtree->Branch("J_psi_1S_TRUEID", &myJ_psi_1S_TRUEID,
      "J_psi_1S_TRUEID/I");
    outtree->Branch("KS0_TRUEID", &myKS0_TRUEID,
      "KS0_TRUEID/I");
    outtree->Branch("B0_BKGCAT", &myB0_BKGCAT,
      "B0_BKGCAT/I");
    outtree->Branch("B0_TRUETAU", &myB0_TRUETAU,
      "B0_TRUETAU/D");
    outtree->Branch("B0_FitDaughtersPVConst_PV_X", &myB0_FitDaughtersPVConst_PV_X,
      "B0_FitDaughtersPVConst_PV_X[B0_FitDaughtersPVConst_nPV]/F");
    outtree->Branch("B0_FitDaughtersPVConst_PV_Y", &myB0_FitDaughtersPVConst_PV_Y,
      "B0_FitDaughtersPVConst_PV_Y[B0_FitDaughtersPVConst_nPV]/F");
    outtree->Branch("B0_TRUEORIGINVERTEX_X", &myB0_TRUEORIGINVERTEX_X,
      "B0_TRUEORIGINVERTEX_X/D");
    outtree->Branch("B0_TRUEORIGINVERTEX_Y", &myB0_TRUEORIGINVERTEX_Y,
      "B0_TRUEORIGINVERTEX_Y/D");
    outtree->Branch("B0_TRUEORIGINVERTEX_Z", &myB0_TRUEORIGINVERTEX_Z,
      "B0_TRUEORIGINVERTEX_Z/D");
    outtree->Branch("J_psi_1S_TRUEORIGINVERTEX_X", &myJ_psi_1S_TRUEORIGINVERTEX_X,
      "J_psi_1S_TRUEORIGINVERTEX_X/D");
    outtree->Branch("J_psi_1S_TRUEORIGINVERTEX_Y", &myJ_psi_1S_TRUEORIGINVERTEX_Y,
      "J_psi_1S_TRUEORIGINVERTEX_Y/D");
    outtree->Branch("J_psi_1S_TRUEORIGINVERTEX_Z", &myJ_psi_1S_TRUEORIGINVERTEX_Z,
      "J_psi_1S_TRUEORIGINVERTEX_Z/D");
    outtree->Branch("KS0_TRUEORIGINVERTEX_X", &myKS0_TRUEORIGINVERTEX_X,
      "KS0_TRUEORIGINVERTEX_X/D");
    outtree->Branch("KS0_TRUEORIGINVERTEX_Y", &myKS0_TRUEORIGINVERTEX_Y,
      "KS0_TRUEORIGINVERTEX_Y/D");
    outtree->Branch("KS0_TRUEORIGINVERTEX_Z", &myKS0_TRUEORIGINVERTEX_Z,
      "KS0_TRUEORIGINVERTEX_Z/D");
  }
  if (data==m_IncJpsi) {
    outtree->Branch("J_psi_1S_MC_MOTHER_ID", &myJ_psi_1S_MC_MOTHER_ID,
      "J_psi_1S_MC_MOTHER_ID/I");
    outtree->Branch("J_psi_1S_MC_GD_MOTHER_ID", &myJ_psi_1S_MC_GD_MOTHER_ID,
      "J_psi_1S_MC_GD_MOTHER_ID/I");
    outtree->Branch("J_psi_1S_MC_GD_GD_MOTHER_ID", &myJ_psi_1S_MC_GD_GD_MOTHER_ID,
      "J_psi_1S_MC_GD_GD_MOTHER_ID/I");
    outtree->Branch("KS0_MC_MOTHER_ID", &myKS0_MC_MOTHER_ID,
      "KS0_MC_MOTHER_ID/I");
    outtree->Branch("KS0_MC_GD_MOTHER_ID", &myKS0_MC_GD_MOTHER_ID,
      "KS0_MC_GD_MOTHER_ID/I");
    outtree->Branch("KS0_MC_GD_GD_MOTHER_ID", &myKS0_MC_GD_GD_MOTHER_ID,
      "KS0_MC_GD_GD_MOTHER_ID/I");
  }

  // *** Other information ***
  Float_t myB0_FitSubstKpi1_M[maxLeafs];
    outtree->Branch("B0_FitSubstKpi1_M", &myB0_FitSubstKpi1_M,
    "B0_FitSubstKpi1_M[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitSubstKpi2_M[maxLeafs];
    outtree->Branch("B0_FitSubstKpi2_M", &myB0_FitSubstKpi2_M,
    "B0_FitSubstKpi2_M[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitSubstKpi1_KS0_M[maxLeafs];
    outtree->Branch("B0_FitSubstKpi1_KS0_M", &myB0_FitSubstKpi1_KS0_M,
    "B0_FitSubstKpi1_KS0_M[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitSubstKpi2_KS0_M[maxLeafs];
    outtree->Branch("B0_FitSubstKpi2_KS0_M", &myB0_FitSubstKpi2_KS0_M,
    "B0_FitSubstKpi2_KS0_M[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitSubstppi1_M[maxLeafs];
    outtree->Branch("B0_FitSubstppi1_M", &myB0_FitSubstppi1_M,
    "B0_FitSubstppi1_M[B0_FitDaughtersPVConst_nPV]/F");
  Float_t myB0_FitSubstppi2_M[maxLeafs];
    outtree->Branch("B0_FitSubstppi2_M", &myB0_FitSubstppi2_M,
    "B0_FitSubstppi2_M[B0_FitDaughtersPVConst_nPV]/F");

  // *** Time Information ***
  ULong64_t myGpsTime;
    outtree->Branch("GpsTime", &myGpsTime,
    "GpsTime/l");
  Int_t myGpsYear;
    outtree->Branch("GpsYear", &myGpsYear,
    "GpsYear/I");
  Int_t myGpsMonth;
    outtree->Branch("GpsMonth", &myGpsMonth,
    "GpsMonth/I");
  Int_t myGpsDay;
    outtree->Branch("GpsDay", &myGpsDay,
    "GpsDay/I");
  Int_t myGpsHour;
    outtree->Branch("GpsHour", &myGpsHour,
    "GpsHour/I");
  Int_t myGpsMinute;
    outtree->Branch("GpsMinute", &myGpsMinute,
    "GpsMinute/I");
  Double_t myGpsSecond;
    outtree->Branch("GpsSecond", &myGpsSecond,
    "GpsSecond/D");


// ***** PART II: Adding Combined Tag ***** //
//////////////////////////////////////////////

  std::cout << "\n PROGRESS: SETUP for Combined Tag Decision \n" << std::endl;

  // ***** Official Tagging Calibration ***** //
  //////////////////////////////////////////////
  
  int OSSign = 1;
  int SSKSign = 1;

  // *** Opposite Side Tagger ***
  double Av_Eta_OS_LL = 0.3749; // From Florian, average of Bd and Bs from sWeights
  double Av_Eta_OS_DD = 0.3739; // From Florian, average of Bd and Bs from sWeights
  // Official Reco14 Calibration
  double calib_OS_p0mEta_Val = 0.0062; // p0 - <eta> = 0.0062 +/- 0.0019 +/- 0.0040
  double calib_OS_p0mEta_Err = TMath::Sqrt(pow(0.0019,2) + pow(0.0040,2));
  double calib_OS_p1_Val = 0.982; // p1 = 0.982 +/- 0.007 +/- 0.034
  double calib_OS_p1_Err = TMath::Sqrt(pow(0.007,2) + pow(0.034,2));
  double calib_OS_Deltap0d2 = 0.0070; // Delta p0/2 = 0.0070 +/- 0.0006
  double calib_OS_Deltap1d2 = 0.033; // Delta p1/2 = 0.033 +/- 0.006
  
  // Analysis dependent calibration parameters
  double calib_OS_p0_LL[nCalib];
  calib_OS_p0_LL[0] = Av_Eta_OS_LL + calib_OS_p0mEta_Val;
  calib_OS_p0_LL[1] = Av_Eta_OS_LL + calib_OS_p0mEta_Val + calib_OS_p0mEta_Err;
  calib_OS_p0_LL[2] = Av_Eta_OS_LL + calib_OS_p0mEta_Val - calib_OS_p0mEta_Err;
  calib_OS_p0_LL[3] = Av_Eta_OS_LL + calib_OS_p0mEta_Val + calib_OS_Deltap0d2;
  calib_OS_p0_LL[4] = Av_Eta_OS_LL + calib_OS_p0mEta_Val - calib_OS_Deltap0d2;
  double calib_OS_p0_DD[nCalib];
  calib_OS_p0_DD[0] = Av_Eta_OS_DD + calib_OS_p0mEta_Val;
  calib_OS_p0_DD[1] = Av_Eta_OS_DD + calib_OS_p0mEta_Val + calib_OS_p0mEta_Err;
  calib_OS_p0_DD[2] = Av_Eta_OS_DD + calib_OS_p0mEta_Val - calib_OS_p0mEta_Err;
  calib_OS_p0_DD[3] = Av_Eta_OS_DD + calib_OS_p0mEta_Val + calib_OS_Deltap0d2;
  calib_OS_p0_DD[4] = Av_Eta_OS_DD + calib_OS_p0mEta_Val - calib_OS_Deltap0d2;
  double calib_OS_p1[nCalib];
  calib_OS_p1[0] = calib_OS_p1_Val;
  calib_OS_p1[1] = calib_OS_p1_Val + calib_OS_p1_Err;
  calib_OS_p1[2] = calib_OS_p1_Val - calib_OS_p1_Err;
  calib_OS_p1[3] = calib_OS_p1_Val + calib_OS_Deltap1d2;
  calib_OS_p1[4] = calib_OS_p1_Val - calib_OS_Deltap1d2;
  
  // Calibration Framework
  RooCategory* B0_OSTag_Dec = new RooCategory("B0_OSTag_Dec", "Opposite Side Tag Decision");
  B0_OSTag_Dec->defineType("B", 1);
  B0_OSTag_Dec->defineType("Bbar", -1);
  B0_OSTag_Dec->defineType("untagged", 0);
  RooRealVar* B0_OSTag_Eta = new RooRealVar("B0_OSTag_Eta",
    "Opposite Side Mistag", 0., 0.5);
  RooRealVar* calib_OSTag_Av = new RooRealVar("calib_OSTag_Av",
    "Mistag calibration - Av", Av_Eta_OS_LL);
  RooRealVar* calib_OSTag_P0 = new RooRealVar("calib_OSTag_P0",
    "Mistag calibration - p0", 0);
  RooRealVar* calib_OSTag_P1 = new RooRealVar("calib_OSTag_P1",
    "Mistag calibration - p1", 1);
  MistagCalibration* calib_OSTag = new MistagCalibration("calib_OSTag",
    "OS calibrated mistag omega", *B0_OSTag_Eta, *calib_OSTag_P0,
    *calib_OSTag_P1, *calib_OSTag_Av);
  
  // *** Same Side Kaon Tagger ***
  // Official Reco14 Calibration
  double Av_Eta_SSK = 0.3423;
  double calib_SSK_p0mEta_Val = 0.0047; // p0 - <eta> = 0.0047 +/- 0.009 +/- 0.005
  double calib_SSK_p0mEta_Err = TMath::Sqrt(pow(0.009,2) + pow(0.005,2));
  double calib_SSK_p1_Val = 1.715; // p1 = 1.715 +/- 0.020 +/- 0.057
  double calib_SSK_p1_Err = TMath::Sqrt(pow(0.020,2) + pow(0.057,2));
  double calib_SSK_Deltap0d2 = -0.0075; // Delta p0/2 = -0.0075 +/- ??
  double calib_SSK_Deltap1d2 = 0.003; // Delta p1/2 = 0.003 +/- ??
  
  // Analysis dependent calibration parameters
  double calib_SSK_p0[nCalib];
  calib_SSK_p0[0] = Av_Eta_SSK + calib_SSK_p0mEta_Val;
  calib_SSK_p0[1] = Av_Eta_SSK + calib_SSK_p0mEta_Val + calib_SSK_p0mEta_Err;
  calib_SSK_p0[2] = Av_Eta_SSK + calib_SSK_p0mEta_Val - calib_SSK_p0mEta_Err;
  calib_SSK_p0[3] = Av_Eta_SSK + calib_SSK_p0mEta_Val + calib_SSK_Deltap0d2;
  calib_SSK_p0[4] = Av_Eta_SSK + calib_SSK_p0mEta_Val - calib_SSK_Deltap0d2;
  double calib_SSK_p1[nCalib];
  calib_SSK_p1[0] = calib_SSK_p1_Val;
  calib_SSK_p1[1] = calib_SSK_p1_Val + calib_SSK_p1_Err;
  calib_SSK_p1[2] = calib_SSK_p1_Val - calib_SSK_p1_Err;
  calib_SSK_p1[3] = calib_SSK_p1_Val + calib_SSK_Deltap1d2;
  calib_SSK_p1[4] = calib_SSK_p1_Val - calib_SSK_Deltap1d2;

  // Calibration Framework
  RooCategory* B0_SSKTag_Dec = new RooCategory("B0_SSKTag_Dec","Same Side Kaon Tag Decision");
  B0_SSKTag_Dec->defineType("B", 1);
  B0_SSKTag_Dec->defineType("Bbar", -1);
  B0_SSKTag_Dec->defineType("untagged", 0);
  RooRealVar* B0_SSKTag_Eta = new RooRealVar("B0_SSKTag_Eta",
    "Same Side Kaon Mistag", 0., 0.5);
  RooRealVar* calib_SSKTag_Av = new RooRealVar("calib_SSKTag_Av",
    "Mistag calibration - Av", Av_Eta_SSK);
  RooRealVar* calib_SSKTag_P0 = new RooRealVar("calib_SSKTag_P0",
    "Mistag calibration - p0", 0);
  RooRealVar* calib_SSKTag_P1 = new RooRealVar("calib_SSKTag_P1",
    "Mistag calibration - p1", 1);
  MistagCalibration* calib_SSKTag = new MistagCalibration("calib_SSKTag",
    "SSK calibrated mistag omega", *B0_SSKTag_Eta, *calib_SSKTag_P0,
    *calib_SSKTag_P1, *calib_SSKTag_Av);

  // *** Combined Tagger ***
  RooArgList tagDecisions = RooArgList(*B0_OSTag_Dec, *B0_SSKTag_Dec);
  RooArgList tagOmegas    = RooArgList(*calib_OSTag,  *calib_SSKTag);
  
  // Average Calibration
  DLLTagCombiner* CombinedTag_DLL = new DLLTagCombiner("CombinedTag_DLL",
    "Combined Tagger Delta Log Likelihood", tagDecisions, tagOmegas);
  TagDLLToTagDec* B0_CombiTag_Dec = new TagDLLToTagDec("B0_CombiTag_Dec",
    "Combined Tag Dec", *CombinedTag_DLL, tagDecisions);
  TagDLLToTagEta* B0_CombiTag_Eta = new TagDLLToTagEta("B0_CombiTag_Eta",
    "Combined Tag Omega", *CombinedTag_DLL);



// ***** PART III: Fill Data Set ***** //
////////////////////////////////////////

  // *** Initialise ***
  std::cout << "\n PROGRESS: Filling DataSet \n" << std::endl;
  const Long64_t nentries = ntuple->nEntries();
  
  std::cout << "SLIM: Will loop over " << nentries << " entries." << std::endl;

  int maxPV = 0;
  bool DTFgood[maxLeafs];
  bool pass = false;
  const Long64_t printMod = printFrac(nentries);

  // *** Loop ***
  for (Long64_t i=0; i<nentries; i++) {
    // Reset
    pass = false;

    // Progress
    if (i%printMod==0) {
      std::cout << " |-> " << i << " / " << nentries
                << " (" << 100*i/nentries << "%)" << std::endl;
    }

    // *** Load Entry ***
    ntuple->GetChain()->GetEntry(i);
    maxPV = ntuple->B0_FitDaughtersPVConst_nPV;

    // *** File/Event Tracking ***
    myInputFile = ntuple->GetChain()->GetTreeNumber();
    for (int pv=0; pv<maxPV; pv++){
      myPassLoose[pv] = ntuple->applyAllCuts(data, pv);
      if (myPassLoose[pv]) pass = true;
    }
    if (!pass) continue;

    // *** Read Original Branch Values ***
    // Observables for Analysis
    for (int pv = 0; pv<maxPV; pv++) {
      DTFgood[pv] = TMath::Abs(ntuple->B0_FitDaughtersPVConst_status[pv])<pow(10,-5);
    }
    // *** Observables ***
    myB0_FitDaughtersPVConst_nPV = ntuple->B0_FitDaughtersPVConst_nPV;
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_M[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_M[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_tau[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_tau[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_tauErr[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_tauErr[pv] : -999);
    }

    // *** Tagging ***
    mypiplus_TRACK_Type = ntuple->piplus_TRACK_Type;
    myB0_TAGDECISION_OS = ntuple->B0_TAGDECISION_OS;
    myB0_TAGOMEGA_OS = ntuple->B0_TAGOMEGA_OS;
    myobsTagOS_StdComb = ntuple->obsTagOS_StdComb;
    myobsEtaOS_StdComb = ntuple->obsEtaOS_StdComb;
    myB0_SS_Kaon_DEC = ntuple->B0_SS_Kaon_DEC;
    myB0_SS_Kaon_PROB = ntuple->B0_SS_Kaon_PROB;
    myB0_SS_nnetKaon_DEC = ntuple->B0_SS_nnetKaon_DEC;
    myB0_SS_nnetKaon_PROB = ntuple->B0_SS_nnetKaon_PROB;

    // *** Tag Combinations ***
    if (mypiplus_TRACK_Type==3) calib_OSTag_Av->setVal(Av_Eta_OS_LL);
    else calib_OSTag_Av->setVal(Av_Eta_OS_DD);
    
    for (int j = 0; j < nCalib; j++) {
      // Get Correct Error envelop
      if (j==2 && ntuple->tagOS(data) < calib_OSTag_Av->getVal()) OSSign = 1;
      else OSSign = j;
      if (j==2 && myB0_SS_Kaon_PROB < Av_Eta_SSK) SSKSign = 1;
      else SSKSign = j;
      
      calib_OSTag_P0->setVal(mypiplus_TRACK_Type==3 ? calib_OS_p0_LL[j] : calib_OS_p0_DD[j]);
      calib_OSTag_P1->setVal(calib_OS_p1[OSSign]);
      calib_SSKTag_P0->setVal(calib_SSK_p0[j]);
      calib_SSKTag_P1->setVal(calib_SSK_p1[SSKSign]);
      B0_OSTag_Dec->setIndex(ntuple->tagOS(data));
      B0_OSTag_Eta->setVal(ntuple->etaOS(data));
      if (calib_OSTag->getVal()<=0 || calib_OSTag->getVal()>0.5) {
        B0_OSTag_Dec->setIndex(0);
        B0_OSTag_Eta->setVal(0.5);
      }
      B0_SSKTag_Dec->setIndex(myB0_SS_Kaon_DEC);
      B0_SSKTag_Eta->setVal(myB0_SS_Kaon_PROB);
      if (calib_SSKTag->getVal()<=0 || calib_SSKTag->getVal()>0.5) {
        B0_SSKTag_Dec->setIndex(0);
        B0_SSKTag_Eta->setVal(0.5);
      }
      myB0_CombinedTag_Dec[j]   = B0_CombiTag_Dec->getIndex();
      myB0_CombinedTag_Omega[j] = B0_CombiTag_Eta->getVal();
    }

    // *** Data Manipulation ***
    myrunNumber = ntuple->runNumber;
    myeventNumber = ntuple->eventNumber;
    myPolarity = ntuple->Polarity;
  
    // *** Observables for Common Selection Cuts ***
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_status[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_status[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_chi2[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_chi2[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_MERR[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_MERR[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_PV_Z[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_PV_Z[pv] : -999);
    }
  
    // *** Observables for Decay Specific Cuts ***
    //mypiplus_TRACK_Type = ntuple->piplus_TRACK_Type;
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitSubstppi1_KS0_M[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitSubstppi1_KS0_M[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitSubstppi2_KS0_M[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitSubstppi2_KS0_M[pv] : -999);
    }
    mypiminus_ProbNNk = ntuple->piminus_ProbNNk;
    mypiplus_ProbNNk = ntuple->piplus_ProbNNk;
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_KS0_ctau[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_KS0_ctau[pv] : -999);
    }
    //myJ_psi_1S_MINIPCHI2_OtherPVs[pv] // defined later

    // *** Trigger ***
    myJ_psi_1S_Hlt1TrackMuonDecision_TOS = ntuple->J_psi_1S_Hlt1TrackMuonDecision_TOS;
    myJ_psi_1S_Hlt1DiMuonHighMassDecision_TOS = ntuple->J_psi_1S_Hlt1DiMuonHighMassDecision_TOS;
    myJ_psi_1S_Hlt1TrackAllL0Decision_TOS = ntuple->J_psi_1S_Hlt1TrackAllL0Decision_TOS;
    myJ_psi_1S_Hlt2DiMuonDetachedJPsiDecision_TOS = ntuple->J_psi_1S_Hlt2DiMuonDetachedJPsiDecision_TOS;
    myJ_psi_1S_Hlt2DiMuonJPsiHighPTDecision_TOS = ntuple->J_psi_1S_Hlt2DiMuonJPsiHighPTDecision_TOS;
    myJ_psi_1S_Hlt2DiMuonJPsiDecision_TOS = ntuple->J_psi_1S_Hlt2DiMuonJPsiDecision_TOS;
    myJ_psi_1S_Hlt2TopoMu2BodyBBDTDecision_TOS = ntuple->J_psi_1S_Hlt2TopoMu2BodyBBDTDecision_TOS;

    // *** Neural Net ***
    mynOTClusters = ntuple->nOTClusters;
    for (int pv = 0; pv<maxPV; pv++) {
      myPVCHI2[pv] = (DTFgood[pv] ? ntuple->PVCHI2[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myPVNTRACKS[pv] = (DTFgood[pv] ? ntuple->PVNTRACKS[pv] : -999);
    }
    mynSPDHits = ntuple->nSPDHits;
  
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_PT[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_PT[pv] : -999);
    }
    myB0_ENDVERTEX_CHI2 = ntuple->B0_ENDVERTEX_CHI2;
    myB0_ENDVERTEX_NDOF = ntuple->B0_ENDVERTEX_NDOF;
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_P[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_P[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_AllDIRA[pv] = 
      (DTFgood[pv] ? ntuple->B0_AllDIRA[pv] : -999);
    }
  
    myJ_psi_1S_ENDVERTEX_CHI2 = ntuple->J_psi_1S_ENDVERTEX_CHI2;
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_J_psi_1S_IPCHI2[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_J_psi_1S_IPCHI2[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitPVConst_J_psi_1S_M[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitPVConst_J_psi_1S_M[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitPVConst_J_psi_1S_MERR[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitPVConst_J_psi_1S_MERR[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_J_psi_1S_P[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_J_psi_1S_P[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_J_psi_1S_PT[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_J_psi_1S_PT[pv] : -999);
    }
  
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_KS0_IPCHI2[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_KS0_IPCHI2[pv] : -999);
    }
    myKS0_ENDVERTEX_CHI2 = ntuple->KS0_ENDVERTEX_CHI2;
    myKS0_ENDVERTEX_Z = ntuple->KS0_ENDVERTEX_Z;
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_KS0_ctauErr[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_KS0_ctauErr[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitPVConst_KS0_MERR[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitPVConst_KS0_MERR[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitPVConst_KS0_M[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitPVConst_KS0_M[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_KS0_P[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_KS0_P[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_KS0_PT[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_KS0_PT[pv] : -999);
    }
  
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_J_psi_1S_P0_IPCHI2[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_J_psi_1S_P0_IPCHI2[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_J_psi_1S_P1_IPCHI2[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_J_psi_1S_P1_IPCHI2[pv] : -999);
    }
    mymuminus_PIDmu = ntuple->muminus_PIDmu;
    mymuplus_PIDmu = ntuple->muplus_PIDmu;
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_J_psi_1S_P0_IP[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_J_psi_1S_P0_IP[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_J_psi_1S_P1_IP[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_J_psi_1S_P1_IP[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_J_psi_1S_P0_P[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_J_psi_1S_P0_P[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_J_psi_1S_P1_P[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_J_psi_1S_P1_P[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_J_psi_1S_P0_PT[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_J_psi_1S_P0_PT[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_J_psi_1S_P1_PT[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_J_psi_1S_P1_PT[pv] : -999);
    }
    mymuminus_TRACK_CHI2NDOF = ntuple->muminus_TRACK_CHI2NDOF;
    mymuplus_TRACK_CHI2NDOF = ntuple->muplus_TRACK_CHI2NDOF;
  
    mypiminus_TRACK_GhostProb = ntuple->piminus_TRACK_GhostProb;
    mypiplus_TRACK_GhostProb = ntuple->piplus_TRACK_GhostProb;
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_KS0_P0_IPCHI2[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_KS0_P0_IPCHI2[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_KS0_P1_IPCHI2[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_KS0_P1_IPCHI2[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_KS0_P0_IP[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_KS0_P0_IP[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_KS0_P1_IP[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_KS0_P1_IP[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_KS0_P0_P[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_KS0_P0_P[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_KS0_P1_P[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_KS0_P1_P[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_KS0_P0_PT[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_KS0_P0_PT[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitDaughtersPVConst_KS0_P1_PT[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_KS0_P1_PT[pv] : -999);
    }
    mypiminus_TRACK_CHI2NDOF = ntuple->piminus_TRACK_CHI2NDOF;
    mypiplus_TRACK_CHI2NDOF = ntuple->piplus_TRACK_CHI2NDOF;

    // *** Truth information ***
    if(isSigMC(data) || data==m_IncJpsi) {
      myB0_TRUEID = ntuple->B0_TRUEID;
      myJ_psi_1S_TRUEID = ntuple->J_psi_1S_TRUEID;
      myKS0_TRUEID = ntuple->KS0_TRUEID;
      myB0_BKGCAT = ntuple->B0_BKGCAT;

      myB0_TRUETAU = ntuple->B0_TRUETAU;
      for (int pv = 0; pv<maxPV; pv++) {
        myB0_FitDaughtersPVConst_PV_X[pv] = 
        (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_PV_X[pv] : -999);
      }
      for (int pv = 0; pv<maxPV; pv++) {
        myB0_FitDaughtersPVConst_PV_Y[pv] = 
        (DTFgood[pv] ? ntuple->B0_FitDaughtersPVConst_PV_Y[pv] : -999);
      }
      myB0_TRUEORIGINVERTEX_X = ntuple->B0_TRUEORIGINVERTEX_X;
      myB0_TRUEORIGINVERTEX_Y = ntuple->B0_TRUEORIGINVERTEX_Y;
      myB0_TRUEORIGINVERTEX_Z = ntuple->B0_TRUEORIGINVERTEX_Z;
      myJ_psi_1S_TRUEORIGINVERTEX_X = ntuple->J_psi_1S_TRUEORIGINVERTEX_X;
      myJ_psi_1S_TRUEORIGINVERTEX_Y = ntuple->J_psi_1S_TRUEORIGINVERTEX_Y;
      myJ_psi_1S_TRUEORIGINVERTEX_Z = ntuple->J_psi_1S_TRUEORIGINVERTEX_Z;
      myKS0_TRUEORIGINVERTEX_X = ntuple->KS0_TRUEORIGINVERTEX_X;
      myKS0_TRUEORIGINVERTEX_Y = ntuple->KS0_TRUEORIGINVERTEX_Y;
      myKS0_TRUEORIGINVERTEX_Z = ntuple->KS0_TRUEORIGINVERTEX_Z;
    }
    if (data==m_IncJpsi) {
      myJ_psi_1S_MC_MOTHER_ID = ntuple->J_psi_1S_MC_MOTHER_ID;
      myJ_psi_1S_MC_GD_MOTHER_ID = ntuple->J_psi_1S_MC_GD_MOTHER_ID;
      myJ_psi_1S_MC_GD_GD_MOTHER_ID = ntuple->J_psi_1S_MC_GD_GD_MOTHER_ID;
      myKS0_MC_MOTHER_ID = ntuple->KS0_MC_MOTHER_ID;
      myKS0_MC_GD_MOTHER_ID = ntuple->KS0_MC_GD_MOTHER_ID;
      myKS0_MC_GD_GD_MOTHER_ID = ntuple->KS0_MC_GD_GD_MOTHER_ID;
    }

    // *** Other information ***

    // Calculate Minimum IPCHI2 of all other PVs
    for (int pv = 0; pv<maxPV; pv++) {
      myJ_psi_1S_MINIPCHI2_OtherPVs[pv] = -6; // Assigned if DTF only converged for 1 pv
      if (myB0_FitDaughtersPVConst_J_psi_1S_IPCHI2[pv]<0) {
        myJ_psi_1S_MINIPCHI2_OtherPVs[pv] = -999;
      } else if (maxPV==1) {
        myJ_psi_1S_MINIPCHI2_OtherPVs[pv] = -3;
      } else {
        double ipmin = -6;
        for (int pvNext = 0; pvNext < maxPV; pvNext++) {
          if (pvNext!=pv && myB0_FitDaughtersPVConst_J_psi_1S_IPCHI2[pvNext]>0
              && (ipmin<0 ||
              myB0_FitDaughtersPVConst_J_psi_1S_IPCHI2[pvNext]<ipmin)) {
            ipmin = myB0_FitDaughtersPVConst_J_psi_1S_IPCHI2[pvNext];
          }
        }
        myJ_psi_1S_MINIPCHI2_OtherPVs[pv] = ipmin;
      }
    }

    // Alternative Mass Hypotheses
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitSubstKpi1_M[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitSubstKpi1_M[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitSubstKpi2_M[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitSubstKpi2_M[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitSubstKpi1_KS0_M[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitSubstKpi1_KS0_M[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitSubstKpi2_KS0_M[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitSubstKpi2_KS0_M[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitSubstppi1_M[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitSubstppi1_M[pv] : -999);
    }
    for (int pv = 0; pv<maxPV; pv++) {
      myB0_FitSubstppi2_M[pv] = 
      (DTFgood[pv] ? ntuple->B0_FitSubstppi2_M[pv] : -999);
    }
    
    // *** Time Information ***
    myGpsTime = ntuple->GpsTime;
    myGpsYear = ntuple->GpsYear;
    myGpsMonth = ntuple->GpsMonth;
    myGpsDay = ntuple->GpsDay;
    myGpsHour = ntuple->GpsHour;
    myGpsMinute = ntuple->GpsMinute;
    myGpsSecond = ntuple->GpsSecond;


// ***** PART IV: Write Tree ***** //
/////////////////////////////////////

    outtree->Fill();
  }

  // *** Write to file ***
  std::cout << "\n PROGRESS: Writing File \n" << std::endl; 
 
  outtree->Write();
  outfile->Close();

// ***** PART V: Finish ***** //
////////////////////////////////
  
  std::cout << "\n PROGRESS: Finished! \n" << std::endl;
  return 0;
}

// #############################################################################
// *** Main ***
int main(int argc, char** argv) {

  // *** Decode Arguments ***
  TString module, data, step, dir, decay, weightMethod;
  bool hasOpt;
  int out = decodeArgs(argc, argv,
                       module, data, step, dir, decay, weightMethod, hasOpt);
  if (out!=0) return out;

  // *** Main Function ***
  if (decay==m_B2JpsiKs) {
    return slimmingB2JpsiKs(module, data, step, dir, decay, weightMethod);
  } else {
    std::cout << "ERROR: " << module << " does not (yet) support decay "
              << decay << std::endl;
    return -1;
  }
}

// #############################################################################