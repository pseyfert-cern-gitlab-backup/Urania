// #############################################################################
// Phys/Bs2JpsiKs Package
// Decay Specific Functions - Header File
// Authors: Patrick Koppenburg & Kristof De Bruyn
// #############################################################################


// #############################################################################

#ifndef B2JpsiKs_h
#define B2JpsiKs_h

// *** Load Useful Classes ***
#include <iostream>
#include <cstdio>

#include <TChain.h>
#include <TFile.h>
#include <TMath.h>

#include "IB2JpsiX.h"

// #############################################################################
class B2JpsiKs : virtual public IB2JpsiX {
private:

  // *** Used Constants ***
  // Selection Cuts
  double DTF_chi2;
  double MMERR_cut;

  // *** Multivariate Selection ***
  int nvar;

public :

  // *** Constructors ***
  B2JpsiKs(TTree *tree, const TString module, const TString data,
                const TString step, const TString dir);
  virtual ~B2JpsiKs();

  // *** Tree Manipulation ***
  TTree *fChain;  // pointer to the analyzed TTree or TChain
  Int_t fCurrent; // current Tree number in a TChain

  // *** Observables ***
  Int_t    B0_FitDaughtersPVConst_nPV;
  Float_t  B0_FitDaughtersPVConst_M[maxLeafs];
  Float_t  B0_FitDaughtersPVConst_tau[maxLeafs];
  Float_t  B0_FitDaughtersPVConst_tauErr[maxLeafs];
  Int_t    B0_TAGDECISION;
  Double_t B0_TAGOMEGA;
  Int_t    B0_TAGDECISION_OS;
  Double_t B0_TAGOMEGA_OS;
  Int_t    B0_SS_Kaon_DEC;
  Double_t B0_SS_Kaon_PROB;
  Int_t    B0_SS_Pion_DEC;
  Double_t B0_SS_Pion_PROB;

  // *** Data Manipulation ***
  UInt_t    runNumber;
  ULong64_t eventNumber;
  //Double_t GpsSecond;
  UInt_t    BCID; // Replace with GpsSecond

  // *** Observables for Common Selection Cuts ***
  Float_t B0_FitDaughtersPVConst_status[maxLeafs];
  Float_t B0_FitDaughtersPVConst_chi2[maxLeafs];
  Float_t B0_FitDaughtersPVConst_MERR[maxLeafs];
  Float_t B0_FitDaughtersPVConst_PV_Z[maxLeafs];

  // *** Observables for Decay Specific Cuts ***
  Int_t    piplus_TRACK_Type;
  Double_t KS0_M_with_pplus_piplus;
  Double_t KS0_M_with_piplus_pplus;
  Double_t piminus_ProbNNk;
  Double_t piplus_ProbNNk;
  Float_t  B0_FitDaughtersPVConst_KS0_ctau[maxLeafs];

  // Replace by KS0_M_with_pplus_piplus
  Float_t  B0_FitDaughtersPVConst_KS0_P0_PE[maxLeafs];
  Float_t  B0_FitDaughtersPVConst_KS0_P0_PX[maxLeafs];
  Float_t  B0_FitDaughtersPVConst_KS0_P0_PY[maxLeafs];
  Float_t  B0_FitDaughtersPVConst_KS0_P0_PZ[maxLeafs];
  Float_t  B0_FitDaughtersPVConst_KS0_P1_PE[maxLeafs];
  Float_t  B0_FitDaughtersPVConst_KS0_P1_PX[maxLeafs];
  Float_t  B0_FitDaughtersPVConst_KS0_P1_PY[maxLeafs];
  Float_t  B0_FitDaughtersPVConst_KS0_P1_PZ[maxLeafs];

  // *** Trigger ***
  Bool_t J_psi_1S_Hlt1TrackMuonDecision_TOS;
  Bool_t J_psi_1S_Hlt1DiMuonHighMassDecision_TOS;
  Bool_t J_psi_1S_Hlt1TrackAllL0Decision_TOS;
  Bool_t J_psi_1S_Hlt2DiMuonDetachedJPsiDecision_TOS;
  Bool_t J_psi_1S_Hlt2DiMuonJPsiHighPTDecision_TOS;
  Bool_t J_psi_1S_Hlt2DiMuonJPsiDecision_TOS;
  Bool_t J_psi_1S_Hlt2TopoMu2BodyBBDTDecision_TOS;

  // *** Neural Net ***
  //Float_t  B0_FitDaughtersPVConst_chi2[maxLeafs]; // dtfc
  Int_t    nOTClusters; // otcl
  //Int_t    B0_FitDaughtersPVConst_nPV; // prim
  Int_t    nSPDHits; // spdm

  //Float_t  B0_FitDaughtersPVConst_MERR[maxLeafs]; // b0me
  Float_t  B0_FitDaughtersPVConst_PT[maxLeafs]; // b0pt
  Double_t B0_ENDVERTEX_CHI2; // bch2
  Int_t    B0_ENDVERTEX_NDOF;
  Float_t  B0_FitDaughtersPVConst_P[maxLeafs]; // bmom
  Float_t  B0_AllDIRA[maxLeafs]; // dira

  Double_t J_psi_1S_ENDVERTEX_CHI2; // jchi
  Float_t  B0_FitDaughtersPVConst_J_psi_1S_IPCHI2[maxLeafs]; // jipc
  Float_t  B0_FitPVConst_J_psi_1S_M[maxLeafs]; // jmas
  Float_t  B0_FitPVConst_J_psi_1S_MERR[maxLeafs]; // jmme
  Float_t  B0_FitDaughtersPVConst_J_psi_1S_P[maxLeafs]; // jmom
  Float_t  B0_FitDaughtersPVConst_J_psi_1S_PT[maxLeafs]; // jppt

  Float_t  B0_FitDaughtersPVConst_KS0_IPCHI2[maxLeafs]; // kipc
  Double_t KS0_ENDVERTEX_CHI2; // ksch
  Double_t KS0_ENDVERTEX_Z; // ksez
  //Float_t  B0_FitDaughtersPVConst_KS0_ctau[maxLeafs]; // ksfd
  Float_t  B0_FitDaughtersPVConst_KS0_ctauErr[maxLeafs];
  Float_t  B0_FitPVConst_KS0_MERR[maxLeafs]; // ksme
  Float_t  B0_FitPVConst_KS0_M[maxLeafs]; // ksmm
  Float_t  B0_FitDaughtersPVConst_KS0_P[maxLeafs]; // ksmo
  Float_t  B0_FitDaughtersPVConst_KS0_PT[maxLeafs]; // kspt
  //Float_t  B0_FitDaughtersPVConst_KS0_ctau[maxLeafs]; // ksta

  Float_t  B0_FitDaughtersPVConst_J_psi_1S_P0_IPCHI2[maxLeafs]; // muic
  Float_t  B0_FitDaughtersPVConst_J_psi_1S_P1_IPCHI2[maxLeafs];
  Double_t muminus_PIDmu; // muid
  Double_t muplus_PIDmu;
  Float_t  B0_FitDaughtersPVConst_J_psi_1S_P0_IP[maxLeafs]; // muip
  Float_t  B0_FitDaughtersPVConst_J_psi_1S_P1_IP[maxLeafs];
  Float_t  B0_FitDaughtersPVConst_J_psi_1S_P0_P[maxLeafs]; // mumo
  Float_t  B0_FitDaughtersPVConst_J_psi_1S_P1_P[maxLeafs];
  Float_t  B0_FitDaughtersPVConst_J_psi_1S_P0_PT[maxLeafs]; // mupt
  Float_t  B0_FitDaughtersPVConst_J_psi_1S_P1_PT[maxLeafs];
  Double_t muminus_TRACK_CHI2NDOF; // mutk
  Double_t muplus_TRACK_CHI2NDOF;

  //Double_t piminus_ProbNNk; // pidk
  //Double_t piplus_ProbNNk;
  Double_t piminus_TRACK_GhostProb; // pigp
  Double_t piplus_TRACK_GhostProb;
  Float_t  B0_FitDaughtersPVConst_KS0_P0_IPCHI2[maxLeafs]; // piic
  Float_t  B0_FitDaughtersPVConst_KS0_P1_IPCHI2[maxLeafs];
  Float_t  B0_FitDaughtersPVConst_KS0_P0_IP[maxLeafs]; // piip
  Float_t  B0_FitDaughtersPVConst_KS0_P1_IP[maxLeafs];
  Float_t  B0_FitDaughtersPVConst_KS0_P0_P[maxLeafs]; // pimo
  Float_t  B0_FitDaughtersPVConst_KS0_P1_P[maxLeafs];
  Float_t  B0_FitDaughtersPVConst_KS0_P0_PT[maxLeafs]; // pipt
  Float_t  B0_FitDaughtersPVConst_KS0_P1_PT[maxLeafs];
  Double_t piminus_TRACK_CHI2NDOF; // pitk
  Double_t piplus_TRACK_CHI2NDOF;

  // *** Truth information ***
  Int_t B0_TRUEID;
  Int_t J_psi_1S_TRUEID;
  Int_t KS0_TRUEID;
  Int_t B0_BKGCAT;

  Double_t B0_TRUETAU;
  Double_t B0_TRUEORIGINVERTEX_X;
  Double_t B0_TRUEORIGINVERTEX_Y;
  Double_t B0_TRUEORIGINVERTEX_Z;

  // *** sWeights && Neural Net ***
  Double_t sweight[maxLeafs] ;
  Int_t unbiased;
  Float_t netOutput[maxLeafs];

// #############################################################################


// #############################################################################


// #############################################################################
// *** Common Content ***
#include "B2JpsiX.icpp"
};
#endif

#ifdef B2JpsiKs_cxx
// #############################################################################
//
// Class Content
//
// #############################################################################

// *** Constructors ***

// Constructor
B2JpsiKs::B2JpsiKs(TTree *tree, const TString module, const TString data,
                   const TString step, const TString dir) : IB2JpsiX() {
  mvaVars = new std::map<TString, int>;
  defineConstants(step, 0);
  Init(tree, module, data, step, dir);
}

// Destructor
B2JpsiKs::~B2JpsiKs() {
  if (fChain) delete fChain->GetCurrentFile();
}

void B2JpsiKs::Init(TTree *tree, const TString module, const TString data,
                    const TString step, const TString dir) {
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  // *** Observables ***
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_nPV", &B0_FitDaughtersPVConst_nPV);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_M", &B0_FitDaughtersPVConst_M);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_tau", &B0_FitDaughtersPVConst_tau);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_tauErr", &B0_FitDaughtersPVConst_tauErr);
  fChain->SetBranchAddress("B0_TAGDECISION", &B0_TAGDECISION);
  fChain->SetBranchAddress("B0_TAGOMEGA", &B0_TAGOMEGA);
  fChain->SetBranchAddress("B0_TAGDECISION_OS", &B0_TAGDECISION_OS);
  fChain->SetBranchAddress("B0_TAGOMEGA_OS", &B0_TAGOMEGA_OS);
  fChain->SetBranchAddress("B0_SS_Kaon_DEC", &B0_SS_Kaon_DEC);
  fChain->SetBranchAddress("B0_SS_Kaon_PROB", &B0_SS_Kaon_PROB);
  fChain->SetBranchAddress("B0_SS_Pion_DEC", &B0_SS_Pion_DEC);
  fChain->SetBranchAddress("B0_SS_Pion_PROB", &B0_SS_Pion_PROB);

  // *** Data Manipulation ***
  fChain->SetBranchAddress("runNumber", &runNumber);
  fChain->SetBranchAddress("eventNumber", &eventNumber);
  //fChain->SetBranchAddress("GpsSecond", &GpsSecond);
  fChain->SetBranchAddress("BCID", &BCID); // Replace with GpsSecond

  // *** Observables for Common Selection Cuts ***
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_status", &B0_FitDaughtersPVConst_status);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_chi2", &B0_FitDaughtersPVConst_chi2);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_MERR", &B0_FitDaughtersPVConst_MERR);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_PV_Z", &B0_FitDaughtersPVConst_PV_Z);

  // *** Observables for Decay Specific Cuts ***
  fChain->SetBranchAddress("piplus_TRACK_Type", &piplus_TRACK_Type);
  fChain->SetBranchAddress("KS0_M_with_pplus_piplus", &KS0_M_with_pplus_piplus);
  fChain->SetBranchAddress("KS0_M_with_piplus_pplus", &KS0_M_with_piplus_pplus);
  fChain->SetBranchAddress("piminus_ProbNNk", &piminus_ProbNNk);
  fChain->SetBranchAddress("piplus_ProbNNk", &piplus_ProbNNk);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_ctau", &B0_FitDaughtersPVConst_KS0_ctau);

  // Replace by KS0_M_with_pplus_piplus
  KS0_M_with_pplus_piplus = m_Kzero;
  KS0_M_with_piplus_pplus = m_Kzero;
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_P0_PE", &B0_FitDaughtersPVConst_KS0_P0_PE);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_P0_PX", &B0_FitDaughtersPVConst_KS0_P0_PX);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_P0_PY", &B0_FitDaughtersPVConst_KS0_P0_PY);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_P0_PZ", &B0_FitDaughtersPVConst_KS0_P0_PZ);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_P1_PE", &B0_FitDaughtersPVConst_KS0_P1_PE);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_P1_PX", &B0_FitDaughtersPVConst_KS0_P1_PX);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_P1_PY", &B0_FitDaughtersPVConst_KS0_P1_PY);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_P1_PZ", &B0_FitDaughtersPVConst_KS0_P1_PZ);

  // *** Trigger ***
  fChain->SetBranchAddress("J_psi_1S_Hlt1TrackMuonDecision_TOS", &J_psi_1S_Hlt1TrackMuonDecision_TOS);
  fChain->SetBranchAddress("J_psi_1S_Hlt1DiMuonHighMassDecision_TOS", &J_psi_1S_Hlt1DiMuonHighMassDecision_TOS);
  fChain->SetBranchAddress("J_psi_1S_Hlt1TrackAllL0Decision_TOS", &J_psi_1S_Hlt1TrackAllL0Decision_TOS);
  fChain->SetBranchAddress("J_psi_1S_Hlt2DiMuonDetachedJPsiDecision_TOS", &J_psi_1S_Hlt2DiMuonDetachedJPsiDecision_TOS);
  fChain->SetBranchAddress("J_psi_1S_Hlt2DiMuonJPsiHighPTDecision_TOS", &J_psi_1S_Hlt2DiMuonJPsiHighPTDecision_TOS);
  fChain->SetBranchAddress("J_psi_1S_Hlt2DiMuonJPsiDecision_TOS", &J_psi_1S_Hlt2DiMuonJPsiDecision_TOS);
  fChain->SetBranchAddress("J_psi_1S_Hlt2TopoMu2BodyBBDTDecision_TOS", &J_psi_1S_Hlt2TopoMu2BodyBBDTDecision_TOS);

  // *** Neural Net ***
  fChain->SetBranchAddress("nOTClusters", &nOTClusters);
  fChain->SetBranchAddress("nSPDHits", &nSPDHits);

  fChain->SetBranchAddress("B0_FitDaughtersPVConst_PT", &B0_FitDaughtersPVConst_P);
  fChain->SetBranchAddress("B0_ENDVERTEX_CHI2", &B0_ENDVERTEX_CHI2);
  fChain->SetBranchAddress("B0_ENDVERTEX_NDOF", &B0_ENDVERTEX_NDOF);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_P", &B0_FitDaughtersPVConst_PT);
  fChain->SetBranchAddress("B0_AllDIRA", &B0_AllDIRA);

  fChain->SetBranchAddress("J_psi_1S_ENDVERTEX_CHI2", &J_psi_1S_ENDVERTEX_CHI2);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_J_psi_1S_IPCHI2", &B0_FitDaughtersPVConst_J_psi_1S_IPCHI2);
  fChain->SetBranchAddress("B0_FitPVConst_J_psi_1S_M", &B0_FitPVConst_J_psi_1S_M);
  fChain->SetBranchAddress("B0_FitPVConst_J_psi_1S_MERR", &B0_FitPVConst_J_psi_1S_MERR);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_J_psi_1S_P", &B0_FitDaughtersPVConst_J_psi_1S_P);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_J_psi_1S_PT", &B0_FitDaughtersPVConst_J_psi_1S_PT);

  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_IPCHI2", &B0_FitDaughtersPVConst_KS0_IPCHI2);
  fChain->SetBranchAddress("KS0_ENDVERTEX_CHI2", &KS0_ENDVERTEX_CHI2);
  fChain->SetBranchAddress("KS0_ENDVERTEX_Z", &KS0_ENDVERTEX_Z);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_ctauErr", &B0_FitDaughtersPVConst_KS0_ctauErr);
  fChain->SetBranchAddress("B0_FitPVConst_KS0_MERR", &B0_FitPVConst_KS0_MERR);
  fChain->SetBranchAddress("B0_FitPVConst_KS0_M", &B0_FitPVConst_KS0_M);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_P", &B0_FitDaughtersPVConst_KS0_P);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_PT", &B0_FitDaughtersPVConst_KS0_PT);

  fChain->SetBranchAddress("B0_FitDaughtersPVConst_J_psi_1S_P0_IPCHI2", &B0_FitDaughtersPVConst_J_psi_1S_P0_IPCHI2);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_J_psi_1S_P1_IPCHI2", &B0_FitDaughtersPVConst_J_psi_1S_P1_IPCHI2);
  fChain->SetBranchAddress("muminus_PIDmu", &muminus_PIDmu);
  fChain->SetBranchAddress("muplus_PIDmu", &muplus_PIDmu);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_J_psi_1S_P0_IP", &B0_FitDaughtersPVConst_J_psi_1S_P0_IP);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_J_psi_1S_P1_IP", &B0_FitDaughtersPVConst_J_psi_1S_P1_IP);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_J_psi_1S_P0_P", &B0_FitDaughtersPVConst_J_psi_1S_P0_P);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_J_psi_1S_P1_P", &B0_FitDaughtersPVConst_J_psi_1S_P1_P);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_J_psi_1S_P0_PT", &B0_FitDaughtersPVConst_J_psi_1S_P0_PT);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_J_psi_1S_P1_PT", &B0_FitDaughtersPVConst_J_psi_1S_P1_PT);
  fChain->SetBranchAddress("muminus_TRACK_CHI2NDOF", &muminus_TRACK_CHI2NDOF);
  fChain->SetBranchAddress("muplus_TRACK_CHI2NDOF", &muplus_TRACK_CHI2NDOF);

  fChain->SetBranchAddress("piminus_TRACK_GhostProb", &piminus_TRACK_GhostProb);
  fChain->SetBranchAddress("piplus_TRACK_GhostProb", &piplus_TRACK_GhostProb);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_P0_IPCHI2", &B0_FitDaughtersPVConst_KS0_P0_IPCHI2);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_P1_IPCHI2", &B0_FitDaughtersPVConst_KS0_P1_IPCHI2);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_P0_IP", &B0_FitDaughtersPVConst_KS0_P0_IP);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_P1_IP", &B0_FitDaughtersPVConst_KS0_P1_IP);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_P0_P", &B0_FitDaughtersPVConst_KS0_P0_P);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_P1_P", &B0_FitDaughtersPVConst_KS0_P1_P);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_P0_PT", &B0_FitDaughtersPVConst_KS0_P0_PT);
  fChain->SetBranchAddress("B0_FitDaughtersPVConst_KS0_P1_PT", &B0_FitDaughtersPVConst_KS0_P1_PT);
  fChain->SetBranchAddress("piminus_TRACK_CHI2NDOF", &piminus_TRACK_CHI2NDOF);
  fChain->SetBranchAddress("piplus_TRACK_CHI2NDOF", &piplus_TRACK_CHI2NDOF);

  // *** Truth information ***
  if(isSigMC(data) || data==m_IncJpsi){
    fChain->SetBranchAddress("B0_TRUEID", &B0_TRUEID);
    fChain->SetBranchAddress("J_psi_1S_TRUEID", &J_psi_1S_TRUEID);
    fChain->SetBranchAddress("KS0_TRUEID", &KS0_TRUEID);
    fChain->SetBranchAddress("B0_BKGCAT", &B0_BKGCAT);
     
    fChain->SetBranchAddress("B0_TRUETAU", &B0_TRUETAU);
    fChain->SetBranchAddress("B0_TRUEORIGINVERTEX_X", &B0_TRUEORIGINVERTEX_X);
    fChain->SetBranchAddress("B0_TRUEORIGINVERTEX_Y", &B0_TRUEORIGINVERTEX_Y);
    fChain->SetBranchAddress("B0_TRUEORIGINVERTEX_Z", &B0_TRUEORIGINVERTEX_Z);
  }

  // *** sWeights && Neural Net ***
  if(module==m_teacher || module==m_expert || module==m_TMVA_teacher || module==m_TMVA_expert){
    fChain->SetBranchAddress("sweight", &sweight);
    fChain->SetBranchAddress("unbiased", &unbiased);
  }
  if((module==m_weighting && step!=m_NNKstar) || module==m_optimisation){
    fChain->SetBranchAddress("netOutput", &netOutput);
  }

// #############################################################################

}

#endif // #ifdef B2JpsiKs_cxx
