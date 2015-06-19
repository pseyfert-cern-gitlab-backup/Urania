// ####################################################################################################
// Phys/Bs2JpsiKs Package
// Reduce DaVinci Tuple size
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################


// ####################################################################################################
// *** Load Useful Classes ***
#include <iostream>
#include <map>
#include <vector>
#include "IB2JpsiX.h"
#include "TupleLoader.h"

// Include from ROOT 
#include "TObject.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH1F.h"

// ####################################################################################################
// *** B2JpsiKs ***
int slimmingB2JpsiKs(const TString module, const TString decay, const TString plotfilename, unsigned int ttype,
                     TString weightMethod, TString what, TString dir, unsigned int NNtype){

// ***** PART 0: Initialise ***** //
////////////////////////////////////

  // *** Load Original NTuple ***
  B2JpsiKs_2011* ntuple = loadB2JpsiKsTuple(module, decay, dir, what, NNtype, weightMethod, ttype); 

// ***** PART I: Fill Data Set ***** //
///////////////////////////////////////

  std::cout << "\n PROGRESS: Initialising TTree \n" << std::endl;
  
  // *** Create Target NTuple ***
  TFile* outfile =  new TFile(plotfilename, "RECREATE" );
  outfile->cd();
  TTree outtree("Slim_"+decay+"_Tuple","Slimmed down Decay Tree Tuple");

  // *** Declare Observables and Create Branches ***
  // Observables for Analysis
  Float_t myB_FullFit_M[10]; outtree.Branch("B_FullFit_M", &myB_FullFit_M,"b_B_FullFit_M[10]/F");
  // Observables for Data Manipulation
  UInt_t myrunNumber = -999; outtree.Branch("runNumber", &myrunNumber,"b_runNumber/i");
  ULong64_t myeventNumber = -999; outtree.Branch("eventNumber", &myeventNumber,"b_eventNumber/l");
  Double_t myGpsSecond = -999; outtree.Branch("GpsSecond", &myGpsSecond,"b_GpsSecond/D");
  // Observables for Common Selection Cuts
  Int_t myB_FullFit_nPV = -999; outtree.Branch("B_FullFit_nPV", &myB_FullFit_nPV,"b_B_FullFit_nPV/I");
  Float_t myB_FullFit_status[10]; outtree.Branch("B_FullFit_status", &myB_FullFit_status,"b_B_FullFit_status[10]/F");
  Float_t myB_FullFit_chi2[10]; outtree.Branch("B_FullFit_chi2", &myB_FullFit_chi2,"b_B_FullFit_chi2[10]/F");
  Float_t myB_FullFit_ctau[10]; outtree.Branch("B_FullFit_ctau", &myB_FullFit_ctau,"b_B_FullFit_ctau[10]/F");
  Float_t myB_FullFit_PV_X[10]; outtree.Branch("B_FullFit_PV_X", &myB_FullFit_PV_X,"b_B_FullFit_PV_X[10]/F");// For completeness
  Float_t myB_FullFit_PV_Y[10]; outtree.Branch("B_FullFit_PV_Y", &myB_FullFit_PV_Y,"b_B_FullFit_PV_Y[10]/F");// For completeness
  Float_t myB_FullFit_PV_Z[10]; outtree.Branch("B_FullFit_PV_Z", &myB_FullFit_PV_Z,"b_B_FullFit_PV_Z[10]/F");
  // Observables for Decay Specific Cuts
  Int_t mypiplus_TRACK_Type = -999; outtree.Branch("piplus_TRACK_Type", &mypiplus_TRACK_Type,"b_piplus_TRACK_Type/I");
  Double_t mypiminus_PE = -999; outtree.Branch("piminus_PE", &mypiminus_PE,"b_piminus_PE/D");
  Double_t mypiplus_PE = -999; outtree.Branch("piplus_PE", &mypiplus_PE,"b_piplus_PE/D");
  Double_t myPsi_PE = -999; outtree.Branch("Psi_PE", &myPsi_PE,"b_Psi_PE/D");
  Double_t mypiminus_PX = -999; outtree.Branch("piminus_PX", &mypiminus_PX,"b_piminus_PX/D");
  Double_t mypiplus_PX = -999; outtree.Branch("piplus_PX", &mypiplus_PX,"b_piplus_PX/D");
  Double_t myPsi_PX = -999; outtree.Branch("Psi_PX", &myPsi_PX,"b_Psi_PX/D");
  Double_t mypiminus_PY = -999; outtree.Branch("piminus_PY", &mypiminus_PY,"b_piminus_PY/D");
  Double_t mypiplus_PY = -999; outtree.Branch("piplus_PY", &mypiplus_PY,"b_piplus_PY/D");
  Double_t myPsi_PY = -999; outtree.Branch("Psi_PY", &myPsi_PY,"b_Psi_PY/D");
  Double_t mypiminus_PZ = -999; outtree.Branch("piminus_PZ", &mypiminus_PZ,"b_piminus_PZ/D");
  Double_t mypiplus_PZ = -999; outtree.Branch("piplus_PZ", &mypiplus_PZ,"b_piplus_PZ/D");
  Double_t myPsi_PZ = -999; outtree.Branch("Psi_PZ", &myPsi_PZ,"b_Psi_PZ/D");
  Double_t myKS0_M_with_pplus_piplus = -999;
  outtree.Branch("KS0_M_with_pplus_piplus",&myKS0_M_with_pplus_piplus,"b_KS0_M_with_pplus_piplus/D");
  Double_t myKS0_M_with_piplus_pplus = -999;
  outtree.Branch("KS0_M_with_piplus_pplus", &myKS0_M_with_piplus_pplus,"b_KS0_M_with_piplus_pplus/D");
  Float_t myB_FullFit_KS0_ctau[10]; outtree.Branch("B_FullFit_KS0_ctau", &myB_FullFit_KS0_ctau,"b_B_FullFit_KS0_ctau[10]/F");
  Float_t myB_FullFit_KS0_ctauErr[10];
  outtree.Branch("B_FullFit_KS0_ctauErr", &myB_FullFit_KS0_ctauErr,"b_B_FullFit_KS0_ctauErr[10]/F");
  Double_t myB_MINIPCHI2NEXTBEST = -999; outtree.Branch("B_MINIPCHI2NEXTBEST", &myB_MINIPCHI2NEXTBEST,"b_B_MINIPCHI2NEXTBEST/D");
  // Observables for Trigger
  Bool_t myPsiHlt1TrackMuonDecision_TOS = -999;
  outtree.Branch("PsiHlt1TrackMuonDecision_TOS", &myPsiHlt1TrackMuonDecision_TOS,"b_PsiHlt1TrackMuonDecision_TOS/O");
  Bool_t myPsiHlt1DiMuonHighMassDecision_TOS = -999;
  outtree.Branch("PsiHlt1DiMuonHighMassDecision_TOS",&myPsiHlt1DiMuonHighMassDecision_TOS,"b_PsiHlt1DiMuonHighMassDecision_TOS/O");
  Bool_t myPsiHlt1TrackAllL0Decision_TOS = -999;
  outtree.Branch("PsiHlt1TrackAllL0Decision_TOS", &myPsiHlt1TrackAllL0Decision_TOS,"b_PsiHlt1TrackAllL0Decision_TOS/O");
  Bool_t myPsiHlt2DiMuonDetachedJPsiDecision_TOS = -999;
  outtree.Branch("PsiHlt2DiMuonDetachedJPsiDecision_TOS", &myPsiHlt2DiMuonDetachedJPsiDecision_TOS,
                 "b_PsiHlt2DiMuonDetachedJPsiDecision_TOS/O");
  Bool_t myPsiHlt2DiMuonJPsiHighPTDecision_TOS = -999;
  outtree.Branch("PsiHlt2DiMuonJPsiHighPTDecision_TOS",&myPsiHlt2DiMuonJPsiHighPTDecision_TOS,
                 "b_PsiHlt2DiMuonJPsiHighPTDecision_TOS/O");
  Bool_t myPsiHlt2DiMuonJPsiDecision_TOS = -999;
  outtree.Branch("PsiHlt2DiMuonJPsiDecision_TOS", &myPsiHlt2DiMuonJPsiDecision_TOS,"b_PsiHlt2DiMuonJPsiDecision_TOS/O");
  Bool_t myPsiHlt2TopoMu2BodyBBDTDecision_TOS = -999;
  outtree.Branch("PsiHlt2TopoMu2BodyBBDTDecision_TOS", &myPsiHlt2TopoMu2BodyBBDTDecision_TOS,
                 "b_PsiHlt2TopoMu2BodyBBDTDecision_TOS/O");
  Bool_t myPsiL0Global_Dec = -999; outtree.Branch("PsiL0Global_Dec", &myPsiL0Global_Dec,"b_PsiL0Global_Dec/O");
  Bool_t myPsiHlt1Global_Dec = -999; outtree.Branch("PsiHlt1Global_Dec", &myPsiHlt1Global_Dec,"b_PsiHlt1Global_Dec/O");
  Bool_t myPsiHlt2Global_Dec = -999; outtree.Branch("PsiHlt2Global_Dec", &myPsiHlt2Global_Dec,"b_PsiHlt2Global_Dec/O");
  Bool_t myPsiL0Global_TIS = -999; outtree.Branch("PsiL0Global_TIS", &myPsiL0Global_TIS,"b_PsiL0Global_TIS/O");
  Bool_t myPsiHlt1Global_TIS = -999; outtree.Branch("PsiHlt1Global_TIS", &myPsiHlt1Global_TIS,"b_PsiHlt1Global_TIS/O");
  Bool_t myPsiHlt2Global_TIS = -999; outtree.Branch("PsiHlt2Global_TIS", &myPsiHlt2Global_TIS,"b_PsiHlt2Global_TIS/O");
  // Observables for Neural Net
  //Float_t myB_FullFit_chi2[10]; outtree.Branch("B_FullFit_chi2", &myB_FullFit_chi2,"b_B_FullFit_chi2[10]/F");
  Double_t myB_DIRA_OWNPV = -999; outtree.Branch("B_DIRA_OWNPV", &myB_DIRA_OWNPV,"b_B_DIRA_OWNPV/D");
  Double_t myKS0_PT = -999; outtree.Branch("KS0_PT", &myKS0_PT,"b_KS0_PT/D");
  Float_t myB_FullFit_MERR[10]; outtree.Branch("B_FullFit_MERR", &myB_FullFit_MERR,"b_B_FullFit_MERR[10]/F");
  Double_t myPsi_MINIPCHI2 = -999; outtree.Branch("Psi_MINIPCHI2", &myPsi_MINIPCHI2,"b_Psi_MINIPCHI2/D");
  //Float_t myB_FullFit_ctau[10]; outtree.Branch("B_FullFit_ctau", &myB_FullFit_ctau,"b_B_FullFit_ctau[10]/F");
  Double_t myB_ENDVERTEX_CHI2 = -999; outtree.Branch("B_ENDVERTEX_CHI2", &myB_ENDVERTEX_CHI2,"b_B_ENDVERTEX_CHI2/D");
  Int_t myB_ENDVERTEX_NDOF = -999; outtree.Branch("B_ENDVERTEX_NDOF", &myB_ENDVERTEX_NDOF,"b_B_ENDVERTEX_NDOF/I");
  Double_t myB_IPCHI2_OWNPV = -999; outtree.Branch("B_IPCHI2_OWNPV", &myB_IPCHI2_OWNPV,"b_B_IPCHI2_OWNPV/D");
  //Double_t myB_MINIPCHI2NEXTBEST = -999; outtree.Branch("B_MINIPCHI2NEXTBEST", &myB_MINIPCHI2NEXTBEST,"b_B_MINIPCHI2NEXTBEST/D");
  Double_t myB_P = -999; outtree.Branch("B_P", &myB_P,"b_B_P/D");
  Double_t myB_PT = -999; outtree.Branch("B_PT", &myB_PT,"b_B_PT/D");
  Float_t myB_FullFit_ctauErr[10]; outtree.Branch("B_FullFit_ctauErr", &myB_FullFit_ctauErr,"b_B_FullFit_ctauErr[10]/F");
  Double_t myPsi_ENDVERTEX_CHI2 = -999; outtree.Branch("Psi_ENDVERTEX_CHI2", &myPsi_ENDVERTEX_CHI2,"b_Psi_ENDVERTEX_CHI2/D");
  Double_t myPsi_FDCHI2_ORIVX = -999; outtree.Branch("Psi_FDCHI2_ORIVX", &myPsi_FDCHI2_ORIVX,"b_Psi_FDCHI2_ORIVX/D");
  Double_t myPsi_MM = -999; outtree.Branch("Psi_MM", &myPsi_MM,"b_Psi_MM/D");
  Double_t myPsi_MMERR = -999; outtree.Branch("Psi_MMERR", &myPsi_MMERR,"b_Psi_MMERR/D");
  Double_t myPsi_P = -999; outtree.Branch("Psi_P", &myPsi_P,"b_Psi_P/D");
  Double_t myPsi_PT = -999; outtree.Branch("Psi_PT", &myPsi_PT,"b_Psi_PT/D");
  Double_t myPsi_SMALLESTDELTACHI2 = -999;
  outtree.Branch("Psi_SMALLESTDELTACHI2", &myPsi_SMALLESTDELTACHI2,"b_Psi_SMALLESTDELTACHI2/D");
  Double_t myKS0_ENDVERTEX_Z = -999; outtree.Branch("KS0_ENDVERTEX_Z", &myKS0_ENDVERTEX_Z,"b_KS0_ENDVERTEX_Z/D");
  //Float_t myB_FullFit_KS0_ctau[10]; outtree.Branch("B_FullFit_KS0_ctau", &myB_FullFit_KS0_ctau,"b_B_FullFit_KS0_ctau[10]/F");
  //Float_t myB_FullFit_KS0_ctauErr[10];
  //outtree.Branch("B_FullFit_KS0_ctauErr", &myB_FullFit_KS0_ctauErr,"b_B_FullFit_KS0_ctauErr[10]/F");
  Double_t myKS0_ENDVERTEX_CHI2 = -999; outtree.Branch("KS0_ENDVERTEX_CHI2", &myKS0_ENDVERTEX_CHI2,"b_KS0_ENDVERTEX_CHI2/D");
  Double_t myKS0_MINIPCHI2 = -999; outtree.Branch("KS0_MINIPCHI2", &myKS0_MINIPCHI2,"b_KS0_MINIPCHI2/D");
  Double_t myKS0_MM = -999; outtree.Branch("KS0_MM", &myKS0_MM,"b_KS0_MM/D");
  Double_t myKS0_MMERR = -999; outtree.Branch("KS0_MMERR", &myKS0_MMERR,"b_KS0_MMERR/D");
  Double_t myKS0_P = -999; outtree.Branch("KS0_P", &myKS0_P,"b_KS0_P/D");
  Double_t mymuminus_MINIPCHI2 = -999; outtree.Branch("muminus_MINIPCHI2", &mymuminus_MINIPCHI2,"b_muminus_MINIPCHI2/D");
  Double_t mymuplus_MINIPCHI2 = -999; outtree.Branch("muplus_MINIPCHI2", &mymuplus_MINIPCHI2,"b_muplus_MINIPCHI2/D");
  Double_t mymuminus_MINIP = -999; outtree.Branch("muminus_MINIP", &mymuminus_MINIP,"b_muminus_MINIP/D");
  Double_t mymuplus_MINIP = -999; outtree.Branch("muplus_MINIP", &mymuplus_MINIP,"b_muplus_MINIP/D");
  Double_t mymuminus_P = -999; outtree.Branch("muminus_P", &mymuminus_P,"b_muminus_P/D");
  Double_t mymuplus_P = -999; outtree.Branch("muplus_P", &mymuplus_P,"b_muplus_P/D");
  Double_t mymuminus_PT = -999; outtree.Branch("muminus_PT", &mymuminus_PT,"b_muminus_PT/D");
  Double_t mymuplus_PT = -999; outtree.Branch("muplus_PT", &mymuplus_PT,"b_muplus_PT/D");
  Double_t mymuminus_PIDmu = -999; outtree.Branch("muminus_PIDmu", &mymuminus_PIDmu,"b_muminus_PIDmu/D");
  Double_t mymuplus_PIDmu = -999; outtree.Branch("muplus_PIDmu", &mymuplus_PIDmu,"b_muplus_PIDmu/D");
  Double_t mymuplus_TRACK_CHI2NDOF = -999;
  outtree.Branch("muplus_TRACK_CHI2NDOF", &mymuplus_TRACK_CHI2NDOF,"b_muplus_TRACK_CHI2NDOF/D");
  Double_t mymuminus_TRACK_CHI2NDOF = -999;
  outtree.Branch("muminus_TRACK_CHI2NDOF", &mymuminus_TRACK_CHI2NDOF,"b_muminus_TRACK_CHI2NDOF/D");
  Double_t mypiminus_MINIPCHI2 = -999; outtree.Branch("piminus_MINIPCHI2", &mypiminus_MINIPCHI2,"b_piminus_MINIPCHI2/D");
  Double_t mypiplus_MINIPCHI2 = -999; outtree.Branch("piplus_MINIPCHI2", &mypiplus_MINIPCHI2,"b_piplus_MINIPCHI2/D");
  Double_t mypiminus_MINIP = -999; outtree.Branch("piminus_MINIP", &mypiminus_MINIP,"b_piminus_MINIP/D");
  Double_t mypiplus_MINIP = -999; outtree.Branch("piplus_MINIP", &mypiplus_MINIP,"b_piplus_MINIP/D");
  Double_t mypiminus_PT = -999; outtree.Branch("piminus_PT", &mypiminus_PT,"b_piminus_PT/D");
  Double_t mypiplus_PT = -999; outtree.Branch("piplus_PT", &mypiplus_PT,"b_piplus_PT/D");
  Double_t mypiminus_TRACK_GhostProb = -999;
  outtree.Branch("piminus_TRACK_GhostProb", &mypiminus_TRACK_GhostProb,"b_piminus_TRACK_GhostProb/D");
  Double_t mypiplus_TRACK_GhostProb = -999;
  outtree.Branch("piplus_TRACK_GhostProb", &mypiplus_TRACK_GhostProb,"b_piplus_TRACK_GhostProb/D");
  Double_t mypiplus_TRACK_CHI2NDOF = -999;
  outtree.Branch("piplus_TRACK_CHI2NDOF", &mypiplus_TRACK_CHI2NDOF,"b_piplus_TRACK_CHI2NDOF/D");
  Double_t mypiminus_TRACK_CHI2NDOF = -999;
  outtree.Branch("piminus_TRACK_CHI2NDOF",&mypiminus_TRACK_CHI2NDOF,"b_piminus_TRACK_CHI2NDOF/D");
  Int_t mynPVs = -999; outtree.Branch("nPVs", &mynPVs,"b_nPVs/I");
  Int_t mynSPDHits = -999; outtree.Branch("nSPDHits", &mynSPDHits,"b_nSPDHits/I");
  Int_t mynOTClusters = -999; outtree.Branch("nOTClusters", &mynOTClusters,"b_nOTClusters/I");
  Int_t mypiminus_TRACK_Type = -999; outtree.Branch("piminus_TRACK_Type", &mypiminus_TRACK_Type,"b_piminus_TRACK_Type/I");
  
  // Truth information
  Int_t myB_TRUEID = -999;
  if(isSigMC(what) || what==m_IncJpsi){
    outtree.Branch("B_TRUEID", &myB_TRUEID, "b_B_TRUEID/I");}
  Int_t myPsi_TRUEID = -999;
  if(isSigMC(what) || what==m_IncJpsi){
    outtree.Branch("Psi_TRUEID", &myPsi_TRUEID, "b_Psi_TRUEID/I");}
  Int_t myKS0_TRUEID = -999;
  if(isSigMC(what) || what==m_IncJpsi){
    outtree.Branch("KS0_TRUEID", &myKS0_TRUEID, "b_KS0_TRUEID/I");}
  Int_t myB_BKGCAT = -999;
  if(isSigMC(what) || what==m_IncJpsi){
    outtree.Branch("B_BKGCAT", &myB_BKGCAT, "b_B_BKGCAT/I");}
  
  Int_t myB_MC_MOTHER_ID = -999; if(what==m_IncJpsi){
    outtree.Branch("B_MC_MOTHER_ID", &myB_MC_MOTHER_ID, "b_B_MC_MOTHER_ID/I");}
  Int_t myPsi_MC_MOTHER_ID = -999; if(what==m_IncJpsi){
    outtree.Branch("Psi_MC_MOTHER_ID", &myPsi_MC_MOTHER_ID, "b_Psi_MC_MOTHER_ID/I");}
  Int_t myKS0_MC_MOTHER_ID = -999; if(what==m_IncJpsi){
    outtree.Branch("KS0_MC_MOTHER_ID", &myKS0_MC_MOTHER_ID, "b_KS0_MC_MOTHER_ID/I");}
  Int_t myKS0_MC_GD_MOTHER_ID = -999; if(what==m_IncJpsi){
    outtree.Branch("KS0_MC_GD_MOTHER_ID", &myKS0_MC_GD_MOTHER_ID, "b_KS0_MC_GD_MOTHER_ID/I");}
  Int_t myKS0_MC_GD_GD_MOTHER_ID = -999; if(what==m_IncJpsi){
    outtree.Branch("KS0_MC_GD_GD_MOTHER_ID", &myKS0_MC_GD_GD_MOTHER_ID, "b_KS0_MC_GD_GD_MOTHER_ID/I");}

  Double_t myB_TRUETAU = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("B_TRUETAU", &myB_TRUETAU, "b_B_TRUETAU/D");
  Double_t myB_TRUEP_E = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("B_TRUEP_E", &myB_TRUEP_E, "b_B_TRUEP_E/D");
  Double_t myB_TRUEP_X = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("B_TRUEP_X", &myB_TRUEP_X, "b_B_TRUEP_X/D");
  Double_t myB_TRUEP_Y = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("B_TRUEP_Y", &myB_TRUEP_Y, "b_B_TRUEP_Y/D");
  Double_t myB_TRUEP_Z = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("B_TRUEP_Z", &myB_TRUEP_Z, "b_B_TRUEP_Z/D");
  Double_t myB_TRUEPT = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("B_TRUEPT", &myB_TRUEPT, "b_B_TRUEPT/D");
  
  Double_t myB_TRUEORIGINVERTEX_X = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("B_TRUEORIGINVERTEX_X", &myB_TRUEORIGINVERTEX_X, "b_B_TRUEORIGINVERTEX_X/D");
  Double_t myB_TRUEORIGINVERTEX_Y = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("B_TRUEORIGINVERTEX_Y", &myB_TRUEORIGINVERTEX_Y, "b_B_TRUEORIGINVERTEX_Y/D");
  Double_t myB_TRUEORIGINVERTEX_Z = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("B_TRUEORIGINVERTEX_Z", &myB_TRUEORIGINVERTEX_Z, "b_B_TRUEORIGINVERTEX_Z/D");
  Double_t myB_TRUEENDVERTEX_X = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("B_TRUEENDVERTEX_X", &myB_TRUEENDVERTEX_X, "b_B_TRUEENDVERTEX_X/D");
  Double_t myB_TRUEENDVERTEX_Y = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("B_TRUEENDVERTEX_Y", &myB_TRUEENDVERTEX_Y, "b_B_TRUEENDVERTEX_Y/D");
  Double_t myB_TRUEENDVERTEX_Z = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("B_TRUEENDVERTEX_Z", &myB_TRUEENDVERTEX_Z, "b_B_TRUEENDVERTEX_Z/D");
  
  Double_t mypiplus_TRUEP_X = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("piplus_TRUEP_X", &mypiplus_TRUEP_X, "b_piplus_TRUEP_X/D");
  Double_t mypiplus_TRUEP_Y = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("piplus_TRUEP_Y", &mypiplus_TRUEP_Y, "b_piplus_TRUEP_Y/D");
  Double_t mypiplus_TRUEP_Z = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("piplus_TRUEP_Z", &mypiplus_TRUEP_Z, "b_piplus_TRUEP_Z/D");
  Double_t mypiminus_TRUEP_X = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("piminus_TRUEP_X", &mypiminus_TRUEP_X, "b_piminus_TRUEP_X/D");
  Double_t mypiminus_TRUEP_Y = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("piminus_TRUEP_Y", &mypiminus_TRUEP_Y, "b_piminus_TRUEP_Y/D");
  Double_t mypiminus_TRUEP_Z = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("piminus_TRUEP_Z", &mypiminus_TRUEP_Z, "b_piminus_TRUEP_Z/D");
  Double_t mymuplus_TRUEP_X = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("muplus_TRUEP_X", &mymuplus_TRUEP_X, "b_muplus_TRUEP_X/D");
  Double_t mymuplus_TRUEP_Y = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("muplus_TRUEP_Y", &mymuplus_TRUEP_Y, "b_muplus_TRUEP_Y/D");
  Double_t mymuplus_TRUEP_Z = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("muplus_TRUEP_Z", &mymuplus_TRUEP_Z, "b_muplus_TRUEP_Z/D");
  Double_t mymuminus_TRUEP_X = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("muminus_TRUEP_X", &mymuminus_TRUEP_X, "b_muminus_TRUEP_X/D");
  Double_t mymuminus_TRUEP_Y = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("muminus_TRUEP_Y", &mymuminus_TRUEP_Y, "b_muminus_TRUEP_Y/D");
  Double_t mymuminus_TRUEP_Z = -999;
  if(isSigMC(what) || what==m_IncJpsi) outtree.Branch("muminus_TRUEP_Z", &mymuminus_TRUEP_Z, "b_muminus_TRUEP_Z/D");
  
  // *** Loop ***
  std::cout << "\n PROGRESS: Filling DataSet \n" << std::endl;
  const Long64_t nentries = ntuple->nEntries();
  
  std::cout << " * Will loop over " << nentries << " Entries." << std::endl;

  double frac = printFrac(nentries);
  for(Int_t i=0; i<nentries; i++){
    // Progress
    if(0==i%((int)(frac*nentries))) std::cout << " |-> " << i << " / " 
                                              << nentries << " (" << 100*i/nentries << "%)" << std::endl;

    // Load Entry
    ntuple->GetChain()->GetEntry(i);

    // *** Read Original Branch Values ***
    // Observables for Analysis
    for(Int_t j=0; j<10; j++){myB_FullFit_M[j] = ntuple->B_FullFit_M[j];}
    // Observables for Data Manipulation
    myrunNumber = ntuple->runNumber;
    myeventNumber = ntuple->eventNumber;
    myGpsSecond = ntuple->GpsSecond;
    // Observables for Common Selection Cuts
    myB_FullFit_nPV = ntuple->B_FullFit_nPV;
    for(Int_t j=0; j<10; j++){myB_FullFit_status[j] = ntuple->B_FullFit_status[j];}
    for(Int_t j=0; j<10; j++){myB_FullFit_chi2[j] = ntuple->DTFchi2(j);}
    for(Int_t j=0; j<10; j++){myB_FullFit_ctau[j] = ntuple->B_FullFit_ctau[j];}
    for(Int_t j=0; j<10; j++){myB_FullFit_PV_X[j] = ntuple->B_FullFit_PV_X[j];}
    for(Int_t j=0; j<10; j++){myB_FullFit_PV_Y[j] = ntuple->B_FullFit_PV_Y[j];}
    for(Int_t j=0; j<10; j++){myB_FullFit_PV_Z[j] = ntuple->B_FullFit_PV_Z[j];}
    // Observables for Decay Specific Cuts
    mypiplus_TRACK_Type = ntuple->piplus_TRACK_Type;
    mypiminus_PE = ntuple->piminus_PE;
    mypiplus_PE = ntuple->piplus_PE;
    myPsi_PE = ntuple->Psi_PE;
    mypiminus_PX = ntuple->piminus_PX;
    mypiplus_PX = ntuple->piplus_PX;
    myPsi_PX = ntuple->Psi_PX;
    mypiminus_PY = ntuple->piminus_PY;
    mypiplus_PY = ntuple->piplus_PY;
    myPsi_PY = ntuple->Psi_PY;
    mypiminus_PZ = ntuple->piminus_PZ;
    mypiplus_PZ = ntuple->piplus_PZ;
    myPsi_PZ = ntuple->Psi_PZ;
    myKS0_M_with_pplus_piplus = ntuple->KS0_M_with_pplus_piplus;
    myKS0_M_with_piplus_pplus = ntuple->KS0_M_with_piplus_pplus;
    for(Int_t j=0; j<10; j++){myB_FullFit_KS0_ctau[j] = ntuple->B_FullFit_KS0_ctau[j];}
    for(Int_t j=0; j<10; j++){myB_FullFit_ctauErr[j] = ntuple->B_FullFit_ctauErr[j];}
    myB_MINIPCHI2NEXTBEST = ntuple->B_MINIPCHI2NEXTBEST;
    // Observables for Trigger
    myPsiHlt1TrackMuonDecision_TOS = ntuple->getPsiHlt1TrackMuonDecision_TOS();
    myPsiHlt1DiMuonHighMassDecision_TOS = ntuple->getPsiHlt1DiMuonHighMassDecision_TOS();
    myPsiHlt1TrackAllL0Decision_TOS = ntuple->getPsiHlt1TrackAllL0Decision_TOS();
    myPsiHlt2DiMuonDetachedJPsiDecision_TOS = ntuple->getPsiHlt2DiMuonDetachedJPsiDecision_TOS();
    myPsiHlt2DiMuonJPsiHighPTDecision_TOS = ntuple->getPsiHlt2DiMuonJPsiHighPTDecision_TOS();
    myPsiHlt2DiMuonJPsiDecision_TOS = ntuple->getPsiHlt2DiMuonJPsiDecision_TOS();
    myPsiHlt2TopoMu2BodyBBDTDecision_TOS = ntuple->getPsiHlt2TopoMu2BodyBBDTDecision_TOS();
    myPsiL0Global_Dec = ntuple->getPsiL0Global_Dec();
    myPsiHlt1Global_Dec = ntuple->getPsiHlt1Global_Dec();
    myPsiHlt2Global_Dec = ntuple->getPsiHlt2Global_Dec();
    myPsiL0Global_TIS = ntuple->getPsiL0Global_TIS();
    myPsiHlt1Global_TIS = ntuple->getPsiHlt1Global_TIS();
    myPsiHlt2Global_TIS = ntuple->getPsiHlt2Global_TIS();
    // Observables for Neural Net
    //for(Int_t j=0; j<10; j++){myB_FullFit_chi2[j] = ntuple->B_FullFit_chi2[j];}
    myB_DIRA_OWNPV = ntuple->B_DIRA_OWNPV;
    myKS0_PT = ntuple->KS0_PT;
    for(Int_t j=0; j<10; j++){myB_FullFit_MERR[j] = ntuple->B_FullFit_MERR[j];}
    myPsi_MINIPCHI2 = ntuple->Psi_MINIPCHI2;
    //for(Int_t j=0; j<10; j++){myB_FullFit_ctau[j] = ntuple->B_FullFit_ctau[j];}
    myB_ENDVERTEX_CHI2 = ntuple->B_ENDVERTEX_CHI2;
    myB_ENDVERTEX_NDOF = ntuple->B_ENDVERTEX_NDOF;
    myB_IPCHI2_OWNPV = ntuple->B_IPCHI2_OWNPV;
    //myB_MINIPCHI2NEXTBEST = ntuple->B_MINIPCHI2NEXTBEST;
    myB_P = ntuple->B_P;
    myB_PT = ntuple->B_PT;
    //for(Int_t j=0; j<10; j++){myB_FullFit_ctauErr[j] = ntuple->B_FullFit_ctauErr[j];}
    myPsi_ENDVERTEX_CHI2 = ntuple->Psi_ENDVERTEX_CHI2;
    myPsi_FDCHI2_ORIVX = ntuple->Psi_FDCHI2_ORIVX;
    myPsi_MM = ntuple->Psi_MM;
    myPsi_MMERR = ntuple->Psi_MMERR;
    myPsi_P = ntuple->Psi_P;
    myPsi_PT = ntuple->Psi_PT;
    myPsi_SMALLESTDELTACHI2 = ntuple->Psi_SMALLESTDELTACHI2;
    myKS0_ENDVERTEX_Z = ntuple->KS0_ENDVERTEX_Z;
    //for(Int_t j=0; j<10; j++){myB_FullFit_KS0_ctau[j] = ntuple->B_FullFit_KS0_ctau[j];}
    for(Int_t j=0; j<10; j++){myB_FullFit_KS0_ctauErr[j] = ntuple->B_FullFit_KS0_ctauErr[j];}
    myKS0_ENDVERTEX_CHI2 = ntuple->KS0_ENDVERTEX_CHI2;
    myKS0_MINIPCHI2 = ntuple->KS0_MINIPCHI2;
    myKS0_MM = ntuple->KS0_MM;
    myKS0_MMERR = ntuple->KS0_MMERR;
    myKS0_P = ntuple->KS0_P;
    mymuminus_MINIPCHI2 = ntuple->muminus_MINIPCHI2;
    mymuplus_MINIPCHI2 = ntuple->muplus_MINIPCHI2;
    mymuminus_MINIP = ntuple->muminus_MINIP;
    mymuplus_MINIP = ntuple->muplus_MINIP;
    mymuminus_P = ntuple->muminus_P;
    mymuplus_P = ntuple->muplus_P;
    mymuminus_PT = ntuple->muminus_PT;
    mymuplus_PT = ntuple->muplus_PT;
    mymuminus_PIDmu = ntuple->muminus_PIDmu;
    mymuplus_PIDmu = ntuple->muplus_PIDmu;
    mymuplus_TRACK_CHI2NDOF = ntuple->muplus_TRACK_CHI2NDOF;
    mymuminus_TRACK_CHI2NDOF = ntuple->muminus_TRACK_CHI2NDOF;
    mypiminus_MINIPCHI2 = ntuple->piminus_MINIPCHI2;
    mypiplus_MINIPCHI2 = ntuple->piplus_MINIPCHI2;
    mypiminus_MINIP = ntuple->piminus_MINIP;
    mypiplus_MINIP = ntuple->piplus_MINIP;
    mypiminus_PT = ntuple->piminus_PT;
    mypiplus_PT = ntuple->piplus_PT;
    mypiminus_TRACK_GhostProb = ntuple->piminus_TRACK_GhostProb;
    mypiplus_TRACK_CHI2NDOF = ntuple->piplus_TRACK_CHI2NDOF;
    mypiminus_TRACK_CHI2NDOF = ntuple->piminus_TRACK_CHI2NDOF;
    mynPVs = ntuple->nPVs;
    mynSPDHits = ntuple->nSPDHits;
    mynOTClusters = ntuple->nOTClusters;
    mypiminus_TRACK_Type = ntuple->piminus_TRACK_Type;

    // Truth
    if(isSigMC(what) || what==m_IncJpsi){
      myB_TRUEID = ntuple->B_TRUEID;
      myPsi_TRUEID = ntuple->Psi_TRUEID;
      myKS0_TRUEID = ntuple->KS0_TRUEID;
      myB_BKGCAT = ntuple->B_BKGCAT;
      
      if(what==m_IncJpsi){
        myB_MC_MOTHER_ID = ntuple->B_MC_MOTHER_ID;
        myPsi_MC_MOTHER_ID = ntuple->Psi_MC_MOTHER_ID;
        myKS0_MC_MOTHER_ID = ntuple->KS0_MC_MOTHER_ID;
        myKS0_MC_GD_MOTHER_ID = ntuple->KS0_MC_GD_MOTHER_ID;
        myKS0_MC_GD_GD_MOTHER_ID = ntuple->KS0_MC_GD_GD_MOTHER_ID;
      }
      
      myB_TRUETAU = ntuple->B_TRUETAU;
      myB_TRUEP_E = ntuple->B_TRUEP_E;
      myB_TRUEP_X = ntuple->B_TRUEP_X;
      myB_TRUEP_Y = ntuple->B_TRUEP_Y;
      myB_TRUEP_Z = ntuple->B_TRUEP_Z;
      myB_TRUEPT = ntuple->B_TRUEPT;
      
      myB_TRUEORIGINVERTEX_X = ntuple->B_TRUEORIGINVERTEX_X;
      myB_TRUEORIGINVERTEX_Y = ntuple->B_TRUEORIGINVERTEX_Y;
      myB_TRUEORIGINVERTEX_Z = ntuple->B_TRUEORIGINVERTEX_Z;
      myB_TRUEENDVERTEX_X = ntuple->B_TRUEENDVERTEX_X;
      myB_TRUEENDVERTEX_Y = ntuple->B_TRUEENDVERTEX_Y;
      myB_TRUEENDVERTEX_Z = ntuple->B_TRUEENDVERTEX_Z;
      
      mypiplus_TRUEP_X = ntuple->piplus_TRUEP_X;
      mypiplus_TRUEP_Y = ntuple->piplus_TRUEP_Y;
      mypiplus_TRUEP_Z = ntuple->piplus_TRUEP_Z;
      mypiminus_TRUEP_X = ntuple->piminus_TRUEP_X;
      mypiminus_TRUEP_Y = ntuple->piminus_TRUEP_Y;
      mypiminus_TRUEP_Z = ntuple->piminus_TRUEP_Z;
      mymuplus_TRUEP_X = ntuple->muplus_TRUEP_X;
      mymuplus_TRUEP_Y = ntuple->muplus_TRUEP_Y;
      mymuplus_TRUEP_Z = ntuple->muplus_TRUEP_Z;
      mymuminus_TRUEP_X = ntuple->muminus_TRUEP_X;
      mymuminus_TRUEP_Y = ntuple->muminus_TRUEP_Y;
      mymuminus_TRUEP_Z = ntuple->muminus_TRUEP_Z;
    }

    // Write Branch Values 
    outtree.Fill();
  }

  // *** Write to file ***
  std::cout << "\n PROGRESS: Writing File \n" << std::endl; 
 
  outtree.Write();
  outfile->Close();
  
// ***** PART II: Return ***** //
/////////////////////////////////
  std::cout << "\n PROGRESS: Finished! \n" << std::endl;
  return 0;
}

// ####################################################################################################
// *** Bu2JpsiK ***
int slimmingBu2JpsiK(const TString module, const TString decay, const TString plotfilename, unsigned int ttype,
                     TString weightMethod, TString what, TString dir, unsigned int NNtype){

// ***** PART 0: Initialise ***** //
////////////////////////////////////

  // *** Load Original NTuple ***
  Bu2JpsiK_2011* ntuple = loadBu2JpsiKTuple(module, decay, dir, what, NNtype, weightMethod, ttype); 

// ***** PART I: Fill Data Set ***** //
///////////////////////////////////////

  std::cout << "\n PROGRESS: Initialising TTree \n" << std::endl;
  
  // *** Create Target NTuple ***
  TTree outtree("Slim_"+decay+"_Tuple","Slimmed down Decay Tree Tuple");

  // *** Declare Observables and Create Branches ***
  // Observables for Analysis
  Float_t myB_FullFit_M[10]; outtree.Branch("B_FullFit_M", &myB_FullFit_M,"b_B_FullFit_M[10]/F");
  // Observables for Data Manipulation
  UInt_t myrunNumber = -999; outtree.Branch("runNumber", &myrunNumber,"b_runNumber/i");
  ULong64_t myeventNumber = -999; outtree.Branch("eventNumber", &myeventNumber,"b_eventNumber/l");
  Double_t myGpsSecond = -999; outtree.Branch("GpsSecond", &myGpsSecond,"b_GpsSecond/D");
  // Observables for Common Selection Cuts
  Int_t myB_FullFit_nPV = -999; outtree.Branch("B_FullFit_nPV", &myB_FullFit_nPV,"b_B_FullFit_nPV/I");
  Float_t myB_FullFit_status[10]; outtree.Branch("B_FullFit_status", &myB_FullFit_status,"b_B_FullFit_status[10]/F");
  Float_t myB_FullFit_chi2[10]; outtree.Branch("B_FullFit_chi2", &myB_FullFit_chi2,"b_B_FullFit_chi2[10]/F");
  Float_t myB_FullFit_ctau[10]; outtree.Branch("B_FullFit_ctau", &myB_FullFit_ctau,"b_B_FullFit_ctau[10]/F");
  Float_t myB_FullFit_PV_X[10]; outtree.Branch("B_FullFit_PV_X", &myB_FullFit_PV_X,"b_B_FullFit_PV_X[10]/F");// For completeness
  Float_t myB_FullFit_PV_Y[10]; outtree.Branch("B_FullFit_PV_Y", &myB_FullFit_PV_Y,"b_B_FullFit_PV_Y[10]/F");// For completeness
  Float_t myB_FullFit_PV_Z[10]; outtree.Branch("B_FullFit_PV_Z", &myB_FullFit_PV_Z,"b_B_FullFit_PV_Z[10]/F");
  // Observables for Decay Specific Cuts
  //      No additional cuts so far
  // Observables for Trigger
  Bool_t myPsiHlt1TrackMuonDecision_TOS = -999;
  outtree.Branch("PsiHlt1TrackMuonDecision_TOS", &myPsiHlt1TrackMuonDecision_TOS,"b_PsiHlt1TrackMuonDecision_TOS/O");
  Bool_t myPsiHlt1DiMuonHighMassDecision_TOS = -999;
  outtree.Branch("PsiHlt1DiMuonHighMassDecision_TOS",&myPsiHlt1DiMuonHighMassDecision_TOS,"b_PsiHlt1DiMuonHighMassDecision_TOS/O");
  Bool_t myPsiHlt1TrackAllL0Decision_TOS = -999;
  outtree.Branch("PsiHlt1TrackAllL0Decision_TOS", &myPsiHlt1TrackAllL0Decision_TOS,"b_PsiHlt1TrackAllL0Decision_TOS/O");
  Bool_t myPsiHlt2DiMuonDetachedJPsiDecision_TOS = -999;
  outtree.Branch("PsiHlt2DiMuonDetachedJPsiDecision_TOS", &myPsiHlt2DiMuonDetachedJPsiDecision_TOS,
                 "b_PsiHlt2DiMuonDetachedJPsiDecision_TOS/O");
  Bool_t myPsiHlt2DiMuonJPsiHighPTDecision_TOS = -999;
  outtree.Branch("PsiHlt2DiMuonJPsiHighPTDecision_TOS",&myPsiHlt2DiMuonJPsiHighPTDecision_TOS,
                 "b_PsiHlt2DiMuonJPsiHighPTDecision_TOS/O");
  Bool_t myPsiHlt2DiMuonJPsiDecision_TOS = -999;
  outtree.Branch("PsiHlt2DiMuonJPsiDecision_TOS", &myPsiHlt2DiMuonJPsiDecision_TOS,"b_PsiHlt2DiMuonJPsiDecision_TOS/O");
  Bool_t myPsiHlt2TopoMu2BodyBBDTDecision_TOS = -999;
  outtree.Branch("PsiHlt2TopoMu2BodyBBDTDecision_TOS", &myPsiHlt2TopoMu2BodyBBDTDecision_TOS,
                 "b_PsiHlt2TopoMu2BodyBBDTDecision_TOS/O");
  // Observables for Neural Net
  //Float_t myB_FullFit_chi2[10]; outtree.Branch("B_FullFit_chi2", &myB_FullFit_chi2,"b_B_FullFit_chi2[10]/F");
  Double_t myB_DIRA_OWNPV = -999; outtree.Branch("B_DIRA_OWNPV", &myB_DIRA_OWNPV,"b_B_DIRA_OWNPV/D");
  Double_t myKplus_PT = -999; outtree.Branch("Kplus_PT", &myKplus_PT,"b_Kplus_PT/D");
  Float_t myB_FullFit_MERR[10]; outtree.Branch("B_FullFit_MERR", &myB_FullFit_MERR,"b_B_FullFit_MERR[10]/F");
  Double_t myPsi_MINIPCHI2 = -999; outtree.Branch("Psi_MINIPCHI2", &myPsi_MINIPCHI2,"b_Psi_MINIPCHI2/D");
  //Float_t myB_FullFit_ctau[10]; outtree.Branch("B_FullFit_ctau", &myB_FullFit_ctau,"b_B_FullFit_ctau[10]/F");
  Double_t myB_ENDVERTEX_CHI2 = -999; outtree.Branch("B_ENDVERTEX_CHI2", &myB_ENDVERTEX_CHI2,"b_B_ENDVERTEX_CHI2/D");
  Int_t myB_ENDVERTEX_NDOF = -999; outtree.Branch("B_ENDVERTEX_NDOF", &myB_ENDVERTEX_NDOF,"b_B_ENDVERTEX_NDOF/I");
  Double_t myB_IPCHI2_OWNPV = -999; outtree.Branch("B_IPCHI2_OWNPV", &myB_IPCHI2_OWNPV,"b_B_IPCHI2_OWNPV/D");
  Double_t myB_MINIPCHI2NEXTBEST = -999; outtree.Branch("B_MINIPCHI2NEXTBEST", &myB_MINIPCHI2NEXTBEST,"b_B_MINIPCHI2NEXTBEST/D");
  Double_t myB_P = -999; outtree.Branch("B_P", &myB_P,"b_B_P/D");
  Double_t myB_PT = -999; outtree.Branch("B_PT", &myB_PT,"b_B_PT/D");
  Float_t myB_FullFit_ctauErr[10]; outtree.Branch("B_FullFit_ctauErr", &myB_FullFit_ctauErr,"b_B_FullFit_ctauErr[10]/F");
  Double_t myPsi_ENDVERTEX_CHI2 = -999; outtree.Branch("Psi_ENDVERTEX_CHI2", &myPsi_ENDVERTEX_CHI2,"b_Psi_ENDVERTEX_CHI2/D");
  Double_t myPsi_FDCHI2_ORIVX = -999; outtree.Branch("Psi_FDCHI2_ORIVX", &myPsi_FDCHI2_ORIVX,"b_Psi_FDCHI2_ORIVX/D");
  Double_t myPsi_MM = -999; outtree.Branch("Psi_MM", &myPsi_MM,"b_Psi_MM/D");
  Double_t myPsi_MMERR = -999; outtree.Branch("Psi_MMERR", &myPsi_MMERR,"b_Psi_MMERR/D");
  Double_t myPsi_P = -999; outtree.Branch("Psi_P", &myPsi_P,"b_Psi_P/D");
  Double_t myPsi_PT = -999; outtree.Branch("Psi_PT", &myPsi_PT,"b_Psi_PT/D");
  Double_t myPsi_SMALLESTDELTACHI2 = -999;
  outtree.Branch("Psi_SMALLESTDELTACHI2", &myPsi_SMALLESTDELTACHI2,"b_Psi_SMALLESTDELTACHI2/D");
  Double_t myKplus_PIDK = -999; outtree.Branch("Kplus_PIDK", &myKplus_PIDK,"b_Kplus_PIDK/D");
  Double_t myKplus_MINIPCHI2 = -999; outtree.Branch("Kplus_MINIPCHI2", &myKplus_MINIPCHI2,"b_Kplus_MINIPCHI2/D");
  Double_t myKplus_P = -999; outtree.Branch("Kplus_P", &myKplus_P,"b_Kplus_P/D");
  Double_t mymuminus_MINIPCHI2 = -999; outtree.Branch("muminus_MINIPCHI2", &mymuminus_MINIPCHI2,"b_muminus_MINIPCHI2/D");
  Double_t mymuplus_MINIPCHI2 = -999; outtree.Branch("muplus_MINIPCHI2", &mymuplus_MINIPCHI2,"b_muplus_MINIPCHI2/D");
  Double_t mymuminus_MINIP = -999; outtree.Branch("muminus_MINIP", &mymuminus_MINIP,"b_muminus_MINIP/D");
  Double_t mymuplus_MINIP = -999; outtree.Branch("muplus_MINIP", &mymuplus_MINIP,"b_muplus_MINIP/D");
  Double_t mymuminus_P = -999; outtree.Branch("muminus_P", &mymuminus_P,"b_muminus_P/D");
  Double_t mymuplus_P = -999; outtree.Branch("muplus_P", &mymuplus_P,"b_muplus_P/D");
  Double_t mymuminus_PT = -999; outtree.Branch("muminus_PT", &mymuminus_PT,"b_muminus_PT/D");
  Double_t mymuplus_PT = -999; outtree.Branch("muplus_PT", &mymuplus_PT,"b_muplus_PT/D");
  Double_t mymuminus_PIDmu = -999; outtree.Branch("muminus_PIDmu", &mymuminus_PIDmu,"b_muminus_PIDmu/D");
  Double_t mymuplus_PIDmu = -999; outtree.Branch("muplus_PIDmu", &mymuplus_PIDmu,"b_muplus_PIDmu/D");
  Double_t mymuplus_TRACK_CHI2NDOF = -999;
  outtree.Branch("muplus_TRACK_CHI2NDOF", &mymuplus_TRACK_CHI2NDOF,"b_muplus_TRACK_CHI2NDOF/D");
  Double_t mymuminus_TRACK_CHI2NDOF = -999;
  outtree.Branch("muminus_TRACK_CHI2NDOF", &mymuminus_TRACK_CHI2NDOF,"b_muminus_TRACK_CHI2NDOF/D");
  Double_t myKplus_TRACK_GhostProb = -999;
  outtree.Branch("Kplus_TRACK_GhostProb", &myKplus_TRACK_GhostProb,"b_Kplus_TRACK_GhostProb/D");
  Double_t myKplus_TRACK_CHI2NDOF = -999;
  outtree.Branch("Kplus_TRACK_CHI2NDOF", &myKplus_TRACK_CHI2NDOF,"b_Kplus_TRACK_CHI2NDOF/D");
  Int_t myPrimaries = -999; outtree.Branch("Primaries", &myPrimaries,"b_Primaries/I");
  Int_t mynSPDHits = -999; outtree.Branch("nSPDHits", &mynSPDHits,"b_nSPDHits/I");
  Int_t mynOTClusters = -999; outtree.Branch("nOTClusters", &mynOTClusters,"b_nOTClusters/I");
  
  // Truth information
  Int_t myB_TRUEID = -999;
  if(isSigMC(what) || what==m_IncJpsi){
    outtree.Branch("B_TRUEID", &myB_TRUEID, "b_B_TRUEID/I");}
  Int_t myPsi_TRUEID = -999;
  if(isSigMC(what) || what==m_IncJpsi){
    outtree.Branch("Psi_TRUEID", &myPsi_TRUEID, "b_Psi_TRUEID/I");}
  Int_t myB_BKGCAT = -999;
  if(isSigMC(what) || what==m_IncJpsi){
    outtree.Branch("B_BKGCAT", &myB_BKGCAT, "b_B_BKGCAT/I");}
  Double_t myB_TRUETAU = -999;
  if(isSigMC(what) || what==m_IncJpsi){
    outtree.Branch("B_TRUETAU", &myB_TRUETAU, "b_B_TRUETAU/D");}  
  
  
  // *** Loop *** 
  std::cout << "\n PROGRESS: Filling DataSet \n" << std::endl;
  const Long64_t nentries = ntuple->nEntries();
  double frac = printFrac(nentries);
  for(Int_t i=0; i<nentries; i++){
    // Progress
    if(0==i%((int)(frac*nentries))) std::cout << " |-> " << i << " / " 
                                              << nentries << " (" << 100*i/nentries << "%)" << std::endl;
  
    // Load Entry
    ntuple->GetChain()->GetEntry(i);

    // *** Read Original Branch Values ***
    // Observables for Analysis
    for(Int_t j=0; j<10; j++){myB_FullFit_M[j] = ntuple->B_FullFit_M[j];}
    // Observables for Data Manipulation
    myrunNumber = ntuple->runNumber;
    myeventNumber = ntuple->eventNumber;
    myGpsSecond = ntuple->GpsSecond;
    // Observables for Common Selection Cuts
    myB_FullFit_nPV = ntuple->B_FullFit_nPV;
    for(Int_t j=0; j<10; j++){myB_FullFit_status[j] = ntuple->B_FullFit_status[j];}
    for(Int_t j=0; j<10; j++){myB_FullFit_chi2[j] = ntuple->B_FullFit_chi2[j];}
    for(Int_t j=0; j<10; j++){myB_FullFit_ctau[j] = ntuple->B_FullFit_ctau[j];}
    for(Int_t j=0; j<10; j++){myB_FullFit_PV_X[j] = ntuple->B_FullFit_PV_X[j];}
    for(Int_t j=0; j<10; j++){myB_FullFit_PV_Y[j] = ntuple->B_FullFit_PV_Y[j];}
    for(Int_t j=0; j<10; j++){myB_FullFit_PV_Z[j] = ntuple->B_FullFit_PV_Z[j];}
    // Observables for Decay Specific Cuts
    //      No additional cuts so far
    // Observables for Trigger
    myPsiHlt1TrackMuonDecision_TOS = ntuple->PsiHlt1TrackMuonDecision_TOS;
    myPsiHlt1DiMuonHighMassDecision_TOS = ntuple->PsiHlt1DiMuonHighMassDecision_TOS;
    myPsiHlt1TrackAllL0Decision_TOS = ntuple->PsiHlt1TrackAllL0Decision_TOS;
    myPsiHlt2DiMuonDetachedJPsiDecision_TOS = ntuple->PsiHlt2DiMuonDetachedJPsiDecision_TOS;
    myPsiHlt2DiMuonJPsiHighPTDecision_TOS = ntuple->PsiHlt2DiMuonJPsiHighPTDecision_TOS;
    myPsiHlt2DiMuonJPsiDecision_TOS = ntuple->PsiHlt2DiMuonJPsiDecision_TOS;
    myPsiHlt2TopoMu2BodyBBDTDecision_TOS = ntuple->PsiHlt2TopoMu2BodyBBDTDecision_TOS;
    // Observables for Neural Net
    //for(Int_t j=0; j<10; j++){myB_FullFit_chi2[j] = ntuple->B_FullFit_chi2[j];}
    myB_DIRA_OWNPV = ntuple->B_DIRA_OWNPV;
    myKplus_PT = ntuple->Kplus_PT;
    for(Int_t j=0; j<10; j++){myB_FullFit_MERR[j] = ntuple->B_FullFit_MERR[j];}
    myPsi_MINIPCHI2 = ntuple->Psi_MINIPCHI2;
    //for(Int_t j=0; j<10; j++){myB_FullFit_ctau[j] = ntuple->B_FullFit_ctau[j];}
    myB_ENDVERTEX_CHI2 = ntuple->B_ENDVERTEX_CHI2;
    myB_ENDVERTEX_NDOF = ntuple->B_ENDVERTEX_NDOF;
    myB_IPCHI2_OWNPV = ntuple->B_IPCHI2_OWNPV;
    myB_MINIPCHI2NEXTBEST = ntuple->B_MINIPCHI2NEXTBEST;
    myB_P = ntuple->B_P;
    myB_PT = ntuple->B_PT;
    for(Int_t j=0; j<10; j++){myB_FullFit_ctauErr[j] = ntuple->B_FullFit_ctauErr[j];}
    myPsi_ENDVERTEX_CHI2 = ntuple->Psi_ENDVERTEX_CHI2;
    myPsi_FDCHI2_ORIVX = ntuple->Psi_FDCHI2_ORIVX;
    myPsi_MM = ntuple->Psi_MM;
    myPsi_MMERR = ntuple->Psi_MMERR;
    myPsi_P = ntuple->Psi_P;
    myPsi_PT = ntuple->Psi_PT;
    myPsi_SMALLESTDELTACHI2 = ntuple->Psi_SMALLESTDELTACHI2;
    myKplus_PIDK = ntuple->Kplus_PIDK;
    myKplus_MINIPCHI2 = ntuple->Kplus_MINIPCHI2;
    myKplus_P = ntuple->Kplus_P;
    mymuminus_MINIPCHI2 = ntuple->muminus_MINIPCHI2;
    mymuplus_MINIPCHI2 = ntuple->muplus_MINIPCHI2;
    mymuminus_MINIP = ntuple->muminus_MINIP;
    mymuplus_MINIP = ntuple->muplus_MINIP;
    mymuminus_P = ntuple->muminus_P;
    mymuplus_P = ntuple->muplus_P;
    mymuminus_PT = ntuple->muminus_PT;
    mymuplus_PT = ntuple->muplus_PT;
    mymuminus_PIDmu = ntuple->muminus_PIDmu;
    mymuplus_PIDmu = ntuple->muplus_PIDmu;
    mymuplus_TRACK_CHI2NDOF = ntuple->muplus_TRACK_CHI2NDOF;
    mymuminus_TRACK_CHI2NDOF = ntuple->muminus_TRACK_CHI2NDOF;
    myKplus_TRACK_GhostProb = ntuple->Kplus_TRACK_GhostProb;
    myKplus_TRACK_CHI2NDOF = ntuple->Kplus_TRACK_CHI2NDOF;
    myPrimaries = ntuple->Primaries;
    mynSPDHits = ntuple->nSPDHits;
    mynOTClusters = ntuple->nOTClusters;

    // Truth
    if(isSigMC(what) || what==m_IncJpsi){
      myB_TRUEID = ntuple->B_TRUEID;
      myPsi_TRUEID = ntuple->Psi_TRUEID;
      myB_BKGCAT = ntuple->B_BKGCAT;
      myB_TRUETAU = ntuple->B_TRUETAU;
    }

    // Write Branch Values 
    outtree.Fill();
  }


  // *** Write to file ***
  std::cout << "\n PROGRESS: Writing File \n" << std::endl; 

  TFile* outfile =  new TFile(plotfilename, "RECREATE" );
  outfile->cd(); 
  outtree.Write();
  outfile->Close();
  
// ***** PART II: Return ***** //
/////////////////////////////////
  std::cout << "\n PROGRESS: Finished! \n" << std::endl;
  return 0;
}

// ####################################################################################################
// *** Main ***
int main(int argc, char** argv){

  // *** Decode Arguments ***
  TString module, decay, dir, weightMethod, what;
  unsigned int NNtype, ttype;
  int out = decodeArgs(module, decay, NNtype, dir, weightMethod, ttype, what, argc, argv);
  // Error Analysis
  if (out != 0) return out ;
  
  TString sFile = makeFileName(module,decay,NNtype,weightMethod,what,ttype,dir);
  // Error Analysis
  if (""==sFile) {
    std::cout << "ERROR: Failed to generate file." << std::endl;
    return -255 ;
  }
  
  if (decay==m_B2JpsiKs){
    return slimmingB2JpsiKs(module, decay, sFile, ttype, weightMethod, what, dir, NNtype);
  } else if (decay==m_Bu2JpsiK){
    return slimmingBu2JpsiK(module, decay, sFile, ttype, weightMethod, what, dir, NNtype);
  } else{
    std::cout << "ERROR: " << module << " does not (yet) support decay " << decay << std::endl;
    return -1;
  }
}
