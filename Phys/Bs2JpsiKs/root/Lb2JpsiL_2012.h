//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar  5 10:32:11 2013 by ROOT version 5.32/02
// from TTree DecayTree/DecayTree
// found on file: castor:///castor/cern.ch/user/p/pkoppenb/B2JpsiKs/Bu2JpsiK-S20-Down-760.root
//////////////////////////////////////////////////////////

#ifndef Lb2JpsiL_2012_h
#define Lb2JpsiL_2012_h

#include "IB2JpsiX.h"
#include "TMath.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Lb2JpsiL_2012 : virtual public IB2JpsiX {

private:
 
  // *** Used Constants ***
 
  // Selection Cuts
  double DTF_chi2 ;
  double MMERR_cut ;
  
  // Neural Net Variables
  int dtfc ;
  int dira ;
  int kspt ;
  int b0me ;
  int jipc ;
  
  int b0ta ;
  int bch2 ;
  int ipch ;
  int ipnx ;
  int bmom ;
  int b0pt ;
  int b0te ;
  int jchi ;
  int jfdc ;
  int jmas ;
  int jmme ;
  int jmom ;
  int jppt ; 
  int jpsc ;
  int ksez ;
  int ksta ;
  int ksfd ;
  int ksch ;
  int kipc ;
  int ksmm ;
  int ksme ;
  int ksmo ;
  int muic ;
  int muip ;
  int mumo ;
  int mupt ;
  int muid ;
  int mutk ;
  int piic ;
  int piip ;
  int pipt ;
  int pigp ;
  int pigc ;
  int pitk ; 
  int prim ;
  int spdm ; 
  int otcl ;
  int nvar_without_ttype ;
  int NNIvar ;

public :

  Lb2JpsiL_2012(TTree *tree=0, TString module=0, TString dir=0, TString what=0, unsigned int NNtype=0);
  virtual ~Lb2JpsiL_2012();

  // *** Accessors ***
  // Mass Regions
  double sideband_low_min(){return 5200;} ;
  double sideband_high_min(){return 5700;} ;
  double sideband_high_max(){return 6100;} ;

  // *** sWeights && Neural Net ***
  Double_t sweight[100] ;
  TBranch        *b_sweight;
  Float_t netOutput[100];
  TBranch        *b_netOutput;

   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        B_MINIP;
   Double_t        B_MINIPCHI2;
   Double_t        B_MINIPNEXTBEST;
   Double_t        B_MINIPCHI2NEXTBEST;
   Int_t           nPV;
   Float_t         B_AllIP[100];   //[nPV]
   Float_t         B_AllIPchi2[100];   //[nPV]
   Double_t        B_ENDVERTEX_X;
   Double_t        B_ENDVERTEX_Y;
   Double_t        B_ENDVERTEX_Z;
   Double_t        B_ENDVERTEX_XERR;
   Double_t        B_ENDVERTEX_YERR;
   Double_t        B_ENDVERTEX_ZERR;
   Double_t        B_ENDVERTEX_CHI2;
   Int_t           B_ENDVERTEX_NDOF;
   Float_t         B_ENDVERTEX_COV_[3][3];
   Double_t        B_OWNPV_X;
   Double_t        B_OWNPV_Y;
   Double_t        B_OWNPV_Z;
   Double_t        B_OWNPV_XERR;
   Double_t        B_OWNPV_YERR;
   Double_t        B_OWNPV_ZERR;
   Double_t        B_OWNPV_CHI2;
   Int_t           B_OWNPV_NDOF;
   Float_t         B_OWNPV_COV_[3][3];
   Double_t        B_IP_OWNPV;
   Double_t        B_IPCHI2_OWNPV;
   Double_t        B_FD_OWNPV;
   Double_t        B_FDCHI2_OWNPV;
   Double_t        B_DIRA_OWNPV;
   Double_t        B_TOPPV_X;
   Double_t        B_TOPPV_Y;
   Double_t        B_TOPPV_Z;
   Double_t        B_TOPPV_XERR;
   Double_t        B_TOPPV_YERR;
   Double_t        B_TOPPV_ZERR;
   Double_t        B_TOPPV_CHI2;
   Int_t           B_TOPPV_NDOF;
   Float_t         B_TOPPV_COV_[3][3];
   Double_t        B_IP_TOPPV;
   Double_t        B_IPCHI2_TOPPV;
   Double_t        B_FD_TOPPV;
   Double_t        B_FDCHI2_TOPPV;
   Double_t        B_DIRA_TOPPV;
   Double_t        B_P;
   Double_t        B_PT;
   Double_t        B_PE;
   Double_t        B_PX;
   Double_t        B_PY;
   Double_t        B_PZ;
   Double_t        B_REFPX;
   Double_t        B_REFPY;
   Double_t        B_REFPZ;
   Double_t        B_MM;
   Double_t        B_MMERR;
   Double_t        B_M;
   Int_t           B_ID;
   Double_t        B_TAU;
   Double_t        B_TAUERR;
   Double_t        B_TAUCHI2;
   Int_t           B_ConstBFit_nPV;
   Float_t         B_ConstBFit_J_psi_1S_M[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_MERR[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_P[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_P0_ID[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_P0_PE[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_P0_PX[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_P0_PY[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_P0_PZ[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_P1_ID[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_P1_PE[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_P1_PX[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_P1_PY[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_P1_PZ[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_PERR[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_ctau[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_ctauErr[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_decayLength[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_decayLengthErr[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_Lambda0_M[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_Lambda0_MERR[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_Lambda0_P[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_Lambda0_P0_ID[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_Lambda0_P0_PE[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_Lambda0_P0_PX[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_Lambda0_P0_PY[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_Lambda0_P0_PZ[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_Lambda0_P1_ID[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_Lambda0_P1_PE[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_Lambda0_P1_PX[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_Lambda0_P1_PY[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_Lambda0_P1_PZ[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_Lambda0_PERR[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_Lambda0_ctau[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_Lambda0_ctauErr[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_Lambda0_decayLength[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_Lambda0_decayLengthErr[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_M[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_MERR[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_P[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_PERR[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_PV_X[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_PV_Y[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_PV_Z[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_PV_key[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_chi2[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_ctau[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_ctauErr[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_decayLength[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_decayLengthErr[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_nDOF[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_nIter[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_status[100];   //[B_ConstBFit_nPV]
   Int_t           B_FullFit_nPV;
   Float_t         B_FullFit_J_psi_1S_M[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_MERR[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_P[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_PERR[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_ctau[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_ctauErr[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_decayLength[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_decayLengthErr[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_Lambda0_M[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_Lambda0_MERR[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_Lambda0_P[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_Lambda0_PERR[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_Lambda0_ctau[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_Lambda0_ctauErr[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_Lambda0_decayLength[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_Lambda0_decayLengthErr[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_M[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_MERR[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_P[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_PERR[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_PV_X[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_PV_Y[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_PV_Z[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_PV_key[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_chi2[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_ctau[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_ctauErr[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_decayLength[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_decayLengthErr[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_nDOF[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_nIter[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_status[100];   //[B_FullFit_nPV]
   Int_t           B_OnlyPsiFit_nPV;
   Float_t         B_OnlyPsiFit_J_psi_1S_M[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_J_psi_1S_MERR[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_J_psi_1S_P[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_J_psi_1S_PERR[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_J_psi_1S_ctau[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_J_psi_1S_ctauErr[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_J_psi_1S_decayLength[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_J_psi_1S_decayLengthErr[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_Lambda0_M[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_Lambda0_MERR[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_Lambda0_P[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_Lambda0_PERR[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_Lambda0_ctau[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_Lambda0_ctauErr[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_Lambda0_decayLength[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_Lambda0_decayLengthErr[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_M[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_MERR[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_P[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_PERR[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_PV_X[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_PV_Y[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_PV_Z[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_PV_key[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_chi2[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_ctau[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_ctauErr[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_decayLength[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_decayLengthErr[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_nDOF[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_nIter[100];   //[B_OnlyPsiFit_nPV]
   Float_t         B_OnlyPsiFit_status[100];   //[B_OnlyPsiFit_nPV]
   Bool_t          B_L0Global_Dec;
   Bool_t          B_L0Global_TIS;
   Bool_t          B_L0Global_TOS;
   Bool_t          B_Hlt1Global_Dec;
   Bool_t          B_Hlt1Global_TIS;
   Bool_t          B_Hlt1Global_TOS;
   Bool_t          B_Hlt1Phys_Dec;
   Bool_t          B_Hlt1Phys_TIS;
   Bool_t          B_Hlt1Phys_TOS;
   Bool_t          B_Hlt2Global_Dec;
   Bool_t          B_Hlt2Global_TIS;
   Bool_t          B_Hlt2Global_TOS;
   Bool_t          B_Hlt2Phys_Dec;
   Bool_t          B_Hlt2Phys_TIS;
   Bool_t          B_Hlt2Phys_TOS;
   Bool_t          B_StrippingGlobal_Dec;
   Bool_t          B_StrippingGlobal_TIS;
   Bool_t          B_StrippingGlobal_TOS;
   Bool_t          B_L0HadronDecision_Dec;
   Bool_t          B_L0HadronDecision_TIS;
   Bool_t          B_L0HadronDecision_TOS;
   Bool_t          B_L0MuonDecision_Dec;
   Bool_t          B_L0MuonDecision_TIS;
   Bool_t          B_L0MuonDecision_TOS;
   Bool_t          B_L0DiMuonDecision_Dec;
   Bool_t          B_L0DiMuonDecision_TIS;
   Bool_t          B_L0DiMuonDecision_TOS;
   Bool_t          B_L0ElectronDecision_Dec;
   Bool_t          B_L0ElectronDecision_TIS;
   Bool_t          B_L0ElectronDecision_TOS;
   Bool_t          B_L0PhotonDecision_Dec;
   Bool_t          B_L0PhotonDecision_TIS;
   Bool_t          B_L0PhotonDecision_TOS;
   Bool_t          B_Hlt1TrackAllL0Decision_Dec;
   Bool_t          B_Hlt1TrackAllL0Decision_TIS;
   Bool_t          B_Hlt1TrackAllL0Decision_TOS;
   Bool_t          B_Hlt1TrackAllL0TightDecision_Dec;
   Bool_t          B_Hlt1TrackAllL0TightDecision_TIS;
   Bool_t          B_Hlt1TrackAllL0TightDecision_TOS;
   Bool_t          B_Hlt1DiMuonHighMassDecision_Dec;
   Bool_t          B_Hlt1DiMuonHighMassDecision_TIS;
   Bool_t          B_Hlt1DiMuonHighMassDecision_TOS;
   Bool_t          B_Hlt1DiMuonLowMassDecision_Dec;
   Bool_t          B_Hlt1DiMuonLowMassDecision_TIS;
   Bool_t          B_Hlt1DiMuonLowMassDecision_TOS;
   Bool_t          B_Hlt1SingleMuonHighPTDecision_Dec;
   Bool_t          B_Hlt1SingleMuonHighPTDecision_TIS;
   Bool_t          B_Hlt1SingleMuonHighPTDecision_TOS;
   Bool_t          B_Hlt1SingleMuonNoIPDecision_Dec;
   Bool_t          B_Hlt1SingleMuonNoIPDecision_TIS;
   Bool_t          B_Hlt1SingleMuonNoIPDecision_TOS;
   Bool_t          B_Hlt1TrackMuonDecision_Dec;
   Bool_t          B_Hlt1TrackMuonDecision_TIS;
   Bool_t          B_Hlt1TrackMuonDecision_TOS;
   Bool_t          B_Hlt2Topo2BodyBBDTDecision_Dec;
   Bool_t          B_Hlt2Topo2BodyBBDTDecision_TIS;
   Bool_t          B_Hlt2Topo2BodyBBDTDecision_TOS;
   Bool_t          B_Hlt2Topo2BodySimpleDecision_Dec;
   Bool_t          B_Hlt2Topo2BodySimpleDecision_TIS;
   Bool_t          B_Hlt2Topo2BodySimpleDecision_TOS;
   Bool_t          B_Hlt2Topo3BodyBBDTDecision_Dec;
   Bool_t          B_Hlt2Topo3BodyBBDTDecision_TIS;
   Bool_t          B_Hlt2Topo3BodyBBDTDecision_TOS;
   Bool_t          B_Hlt2Topo3BodySimpleDecision_Dec;
   Bool_t          B_Hlt2Topo3BodySimpleDecision_TIS;
   Bool_t          B_Hlt2Topo3BodySimpleDecision_TOS;
   Bool_t          B_Hlt2Topo4BodyBBDTDecision_Dec;
   Bool_t          B_Hlt2Topo4BodyBBDTDecision_TIS;
   Bool_t          B_Hlt2Topo4BodyBBDTDecision_TOS;
   Bool_t          B_Hlt2Topo4BodySimpleDecision_Dec;
   Bool_t          B_Hlt2Topo4BodySimpleDecision_TIS;
   Bool_t          B_Hlt2Topo4BodySimpleDecision_TOS;
   Bool_t          B_Hlt2DiMuonDecision_Dec;
   Bool_t          B_Hlt2DiMuonDecision_TIS;
   Bool_t          B_Hlt2DiMuonDecision_TOS;
   Bool_t          B_Hlt2DiMuonBDecision_Dec;
   Bool_t          B_Hlt2DiMuonBDecision_TIS;
   Bool_t          B_Hlt2DiMuonBDecision_TOS;
   Bool_t          B_Hlt2DiMuonDetachedDecision_Dec;
   Bool_t          B_Hlt2DiMuonDetachedDecision_TIS;
   Bool_t          B_Hlt2DiMuonDetachedDecision_TOS;
   Bool_t          B_Hlt2DiMuonDetachedHeavyDecision_Dec;
   Bool_t          B_Hlt2DiMuonDetachedHeavyDecision_TIS;
   Bool_t          B_Hlt2DiMuonDetachedHeavyDecision_TOS;
   Bool_t          B_Hlt2DiMuonDetachedJPsiDecision_Dec;
   Bool_t          B_Hlt2DiMuonDetachedJPsiDecision_TIS;
   Bool_t          B_Hlt2DiMuonDetachedJPsiDecision_TOS;
   Bool_t          B_Hlt2DiMuonDetachedPsi2SDecision_Dec;
   Bool_t          B_Hlt2DiMuonDetachedPsi2SDecision_TIS;
   Bool_t          B_Hlt2DiMuonDetachedPsi2SDecision_TOS;
   Bool_t          B_Hlt2DiMuonJPsiDecision_Dec;
   Bool_t          B_Hlt2DiMuonJPsiDecision_TIS;
   Bool_t          B_Hlt2DiMuonJPsiDecision_TOS;
   Bool_t          B_Hlt2DiMuonJPsiHighPTDecision_Dec;
   Bool_t          B_Hlt2DiMuonJPsiHighPTDecision_TIS;
   Bool_t          B_Hlt2DiMuonJPsiHighPTDecision_TOS;
   Bool_t          B_Hlt2DiMuonLowMassDecision_Dec;
   Bool_t          B_Hlt2DiMuonLowMassDecision_TIS;
   Bool_t          B_Hlt2DiMuonLowMassDecision_TOS;
   Bool_t          B_Hlt2DiMuonPsi2SDecision_Dec;
   Bool_t          B_Hlt2DiMuonPsi2SDecision_TIS;
   Bool_t          B_Hlt2DiMuonPsi2SDecision_TOS;
   Bool_t          B_Hlt2DiMuonPsi2SHighPTDecision_Dec;
   Bool_t          B_Hlt2DiMuonPsi2SHighPTDecision_TIS;
   Bool_t          B_Hlt2DiMuonPsi2SHighPTDecision_TOS;
   Bool_t          B_Hlt2LowMultMuonDecision_Dec;
   Bool_t          B_Hlt2LowMultMuonDecision_TIS;
   Bool_t          B_Hlt2LowMultMuonDecision_TOS;
   Bool_t          B_Hlt2MuonFromHLT1Decision_Dec;
   Bool_t          B_Hlt2MuonFromHLT1Decision_TIS;
   Bool_t          B_Hlt2MuonFromHLT1Decision_TOS;
   Bool_t          B_Hlt2SingleMuonDecision_Dec;
   Bool_t          B_Hlt2SingleMuonDecision_TIS;
   Bool_t          B_Hlt2SingleMuonDecision_TOS;
   Bool_t          B_Hlt2SingleMuonHighPTDecision_Dec;
   Bool_t          B_Hlt2SingleMuonHighPTDecision_TIS;
   Bool_t          B_Hlt2SingleMuonHighPTDecision_TOS;
   Bool_t          B_Hlt2SingleMuonLowPTDecision_Dec;
   Bool_t          B_Hlt2SingleMuonLowPTDecision_TIS;
   Bool_t          B_Hlt2SingleMuonLowPTDecision_TOS;
   Bool_t          B_Hlt2SingleMuonVHighPTDecision_Dec;
   Bool_t          B_Hlt2SingleMuonVHighPTDecision_TIS;
   Bool_t          B_Hlt2SingleMuonVHighPTDecision_TOS;
   Bool_t          B_Hlt2TopoMu2BodyBBDTDecision_Dec;
   Bool_t          B_Hlt2TopoMu2BodyBBDTDecision_TIS;
   Bool_t          B_Hlt2TopoMu2BodyBBDTDecision_TOS;
   Bool_t          B_Hlt2TopoMu3BodyBBDTDecision_Dec;
   Bool_t          B_Hlt2TopoMu3BodyBBDTDecision_TIS;
   Bool_t          B_Hlt2TopoMu3BodyBBDTDecision_TOS;
   Bool_t          B_Hlt2TopoMu4BodyBBDTDecision_Dec;
   Bool_t          B_Hlt2TopoMu4BodyBBDTDecision_TIS;
   Bool_t          B_Hlt2TopoMu4BodyBBDTDecision_TOS;
   Bool_t          B_Hlt2diPhotonDiMuonDecision_Dec;
   Bool_t          B_Hlt2diPhotonDiMuonDecision_TIS;
   Bool_t          B_Hlt2diPhotonDiMuonDecision_TOS;
   Double_t        Lambda0_MINIP;
   Double_t        Lambda0_MINIPCHI2;
   Double_t        Lambda0_MINIPNEXTBEST;
   Double_t        Lambda0_MINIPCHI2NEXTBEST;
   Float_t         Lambda0_AllIP[100];   //[nPV]
   Float_t         Lambda0_AllIPchi2[100];   //[nPV]
   Double_t        Lambda0_ENDVERTEX_X;
   Double_t        Lambda0_ENDVERTEX_Y;
   Double_t        Lambda0_ENDVERTEX_Z;
   Double_t        Lambda0_ENDVERTEX_XERR;
   Double_t        Lambda0_ENDVERTEX_YERR;
   Double_t        Lambda0_ENDVERTEX_ZERR;
   Double_t        Lambda0_ENDVERTEX_CHI2;
   Int_t           Lambda0_ENDVERTEX_NDOF;
   Float_t         Lambda0_ENDVERTEX_COV_[3][3];
   Double_t        Lambda0_OWNPV_X;
   Double_t        Lambda0_OWNPV_Y;
   Double_t        Lambda0_OWNPV_Z;
   Double_t        Lambda0_OWNPV_XERR;
   Double_t        Lambda0_OWNPV_YERR;
   Double_t        Lambda0_OWNPV_ZERR;
   Double_t        Lambda0_OWNPV_CHI2;
   Int_t           Lambda0_OWNPV_NDOF;
   Float_t         Lambda0_OWNPV_COV_[3][3];
   Double_t        Lambda0_IP_OWNPV;
   Double_t        Lambda0_IPCHI2_OWNPV;
   Double_t        Lambda0_FD_OWNPV;
   Double_t        Lambda0_FDCHI2_OWNPV;
   Double_t        Lambda0_DIRA_OWNPV;
   Double_t        Lambda0_TOPPV_X;
   Double_t        Lambda0_TOPPV_Y;
   Double_t        Lambda0_TOPPV_Z;
   Double_t        Lambda0_TOPPV_XERR;
   Double_t        Lambda0_TOPPV_YERR;
   Double_t        Lambda0_TOPPV_ZERR;
   Double_t        Lambda0_TOPPV_CHI2;
   Int_t           Lambda0_TOPPV_NDOF;
   Float_t         Lambda0_TOPPV_COV_[3][3];
   Double_t        Lambda0_IP_TOPPV;
   Double_t        Lambda0_IPCHI2_TOPPV;
   Double_t        Lambda0_FD_TOPPV;
   Double_t        Lambda0_FDCHI2_TOPPV;
   Double_t        Lambda0_DIRA_TOPPV;
   Double_t        Lambda0_ORIVX_X;
   Double_t        Lambda0_ORIVX_Y;
   Double_t        Lambda0_ORIVX_Z;
   Double_t        Lambda0_ORIVX_XERR;
   Double_t        Lambda0_ORIVX_YERR;
   Double_t        Lambda0_ORIVX_ZERR;
   Double_t        Lambda0_ORIVX_CHI2;
   Int_t           Lambda0_ORIVX_NDOF;
   Float_t         Lambda0_ORIVX_COV_[3][3];
   Double_t        Lambda0_IP_ORIVX;
   Double_t        Lambda0_IPCHI2_ORIVX;
   Double_t        Lambda0_FD_ORIVX;
   Double_t        Lambda0_FDCHI2_ORIVX;
   Double_t        Lambda0_DIRA_ORIVX;
   Double_t        Lambda0_P;
   Double_t        Lambda0_PT;
   Double_t        Lambda0_PE;
   Double_t        Lambda0_PX;
   Double_t        Lambda0_PY;
   Double_t        Lambda0_PZ;
   Double_t        Lambda0_REFPX;
   Double_t        Lambda0_REFPY;
   Double_t        Lambda0_REFPZ;
   Double_t        Lambda0_MM;
   Double_t        Lambda0_MMERR;
   Double_t        Lambda0_M;
   Double_t        Lambda0_M_with_pplus_piplus;
   Double_t        Lambda0_M_with_piplus_piplus;
   Int_t           Lambda0_ID;
   Double_t        Lambda0_TAU;
   Double_t        Lambda0_TAUERR;
   Double_t        Lambda0_TAUCHI2;
   Double_t        piminus_MINIP;
   Double_t        piminus_MINIPCHI2;
   Double_t        piminus_MINIPNEXTBEST;
   Double_t        piminus_MINIPCHI2NEXTBEST;
   Float_t         piminus_AllIP[100];   //[nPV]
   Float_t         piminus_AllIPchi2[100];   //[nPV]
   Double_t        piminus_OWNPV_X;
   Double_t        piminus_OWNPV_Y;
   Double_t        piminus_OWNPV_Z;
   Double_t        piminus_OWNPV_XERR;
   Double_t        piminus_OWNPV_YERR;
   Double_t        piminus_OWNPV_ZERR;
   Double_t        piminus_OWNPV_CHI2;
   Int_t           piminus_OWNPV_NDOF;
   Float_t         piminus_OWNPV_COV_[3][3];
   Double_t        piminus_IP_OWNPV;
   Double_t        piminus_IPCHI2_OWNPV;
   Double_t        piminus_TOPPV_X;
   Double_t        piminus_TOPPV_Y;
   Double_t        piminus_TOPPV_Z;
   Double_t        piminus_TOPPV_XERR;
   Double_t        piminus_TOPPV_YERR;
   Double_t        piminus_TOPPV_ZERR;
   Double_t        piminus_TOPPV_CHI2;
   Int_t           piminus_TOPPV_NDOF;
   Float_t         piminus_TOPPV_COV_[3][3];
   Double_t        piminus_IP_TOPPV;
   Double_t        piminus_IPCHI2_TOPPV;
   Double_t        piminus_ORIVX_X;
   Double_t        piminus_ORIVX_Y;
   Double_t        piminus_ORIVX_Z;
   Double_t        piminus_ORIVX_XERR;
   Double_t        piminus_ORIVX_YERR;
   Double_t        piminus_ORIVX_ZERR;
   Double_t        piminus_ORIVX_CHI2;
   Int_t           piminus_ORIVX_NDOF;
   Float_t         piminus_ORIVX_COV_[3][3];
   Double_t        piminus_IP_ORIVX;
   Double_t        piminus_IPCHI2_ORIVX;
   Double_t        piminus_P;
   Double_t        piminus_PT;
   Double_t        piminus_PE;
   Double_t        piminus_PX;
   Double_t        piminus_PY;
   Double_t        piminus_PZ;
   Double_t        piminus_REFPX;
   Double_t        piminus_REFPY;
   Double_t        piminus_REFPZ;
   Double_t        piminus_M;
   Double_t        piminus_AtVtx_PE;
   Double_t        piminus_AtVtx_PX;
   Double_t        piminus_AtVtx_PY;
   Double_t        piminus_AtVtx_PZ;
   Double_t        piminus_L0Calo_HCAL_realET;
   Double_t        piminus_L0Calo_HCAL_xProjection;
   Double_t        piminus_L0Calo_HCAL_yProjection;
   Int_t           piminus_L0Calo_HCAL_region;
   Int_t           piminus_ID;
   Double_t        piminus_PIDe;
   Double_t        piminus_PIDmu;
   Double_t        piminus_PIDK;
   Double_t        piminus_PIDp;
   Double_t        piminus_ProbNNe;
   Double_t        piminus_ProbNNk;
   Double_t        piminus_ProbNNp;
   Double_t        piminus_ProbNNpi;
   Double_t        piminus_ProbNNmu;
   Double_t        piminus_ProbNNghost;
   Bool_t          piminus_hasMuon;
   Bool_t          piminus_isMuon;
   Bool_t          piminus_hasRich;
   Bool_t          piminus_hasCalo;
   Bool_t          piminus_UsedRichAerogel;
   Bool_t          piminus_UsedRich1Gas;
   Bool_t          piminus_UsedRich2Gas;
   Bool_t          piminus_RichAboveElThres;
   Bool_t          piminus_RichAboveMuThres;
   Bool_t          piminus_RichAbovePiThres;
   Bool_t          piminus_RichAboveKaThres;
   Bool_t          piminus_RichAbovePrThres;
   Double_t        piminus_RichDLLe;
   Double_t        piminus_RichDLLmu;
   Double_t        piminus_RichDLLpi;
   Double_t        piminus_RichDLLk;
   Double_t        piminus_RichDLLp;
   Double_t        piminus_RichDLLbt;
   Bool_t          piminus_InAccMuon;
   Bool_t          piminus_isMuonLoose;
   Double_t        piminus_MuonMuLL;
   Double_t        piminus_MuonBkgLL;
   Int_t           piminus_MuonNShared;
   Bool_t          piminus_InAccEcal;
   Double_t        piminus_CaloEcalE;
   Double_t        piminus_EcalPIDe;
   Double_t        piminus_EcalPIDmu;
   Bool_t          piminus_InAccHcal;
   Double_t        piminus_CaloHcalE;
   Double_t        piminus_HcalPIDe;
   Double_t        piminus_HcalPIDmu;
   Bool_t          piminus_InAccPrs;
   Double_t        piminus_PrsPIDe;
   Double_t        piminus_CaloPrsE;
   Bool_t          piminus_InAccSpd;
   Double_t        piminus_CaloSpdE;
   Bool_t          piminus_InAccBrem;
   Double_t        piminus_BremPIDe;
   Double_t        piminus_VeloCharge;
   Int_t           piminus_TRACK_Type;
   Int_t           piminus_TRACK_Key;
   Double_t        piminus_TRACK_CHI2;
   Int_t           piminus_TRACK_NDOF;
   Double_t        piminus_TRACK_CHI2NDOF;
   Double_t        piminus_TRACK_PCHI2;
   Double_t        piminus_TRACK_VeloCHI2NDOF;
   Double_t        piminus_TRACK_TCHI2NDOF;
   Double_t        piminus_VELO_UTID;
   Double_t        piminus_TRACK_FirstMeasurementX;
   Double_t        piminus_TRACK_FirstMeasurementY;
   Double_t        piminus_TRACK_FirstMeasurementZ;
   Double_t        piminus_TRACK_MatchCHI2;
   Double_t        piminus_TRACK_GhostProb;
   Double_t        piminus_TRACK_CloneDist;
   Double_t        piminus_TRACK_Likelihood;
   Double_t        pplus_MINIP;
   Double_t        pplus_MINIPCHI2;
   Double_t        pplus_MINIPNEXTBEST;
   Double_t        pplus_MINIPCHI2NEXTBEST;
   Float_t         pplus_AllIP[100];   //[nPV]
   Float_t         pplus_AllIPchi2[100];   //[nPV]
   Double_t        pplus_OWNPV_X;
   Double_t        pplus_OWNPV_Y;
   Double_t        pplus_OWNPV_Z;
   Double_t        pplus_OWNPV_XERR;
   Double_t        pplus_OWNPV_YERR;
   Double_t        pplus_OWNPV_ZERR;
   Double_t        pplus_OWNPV_CHI2;
   Int_t           pplus_OWNPV_NDOF;
   Float_t         pplus_OWNPV_COV_[3][3];
   Double_t        pplus_IP_OWNPV;
   Double_t        pplus_IPCHI2_OWNPV;
   Double_t        pplus_TOPPV_X;
   Double_t        pplus_TOPPV_Y;
   Double_t        pplus_TOPPV_Z;
   Double_t        pplus_TOPPV_XERR;
   Double_t        pplus_TOPPV_YERR;
   Double_t        pplus_TOPPV_ZERR;
   Double_t        pplus_TOPPV_CHI2;
   Int_t           pplus_TOPPV_NDOF;
   Float_t         pplus_TOPPV_COV_[3][3];
   Double_t        pplus_IP_TOPPV;
   Double_t        pplus_IPCHI2_TOPPV;
   Double_t        pplus_ORIVX_X;
   Double_t        pplus_ORIVX_Y;
   Double_t        pplus_ORIVX_Z;
   Double_t        pplus_ORIVX_XERR;
   Double_t        pplus_ORIVX_YERR;
   Double_t        pplus_ORIVX_ZERR;
   Double_t        pplus_ORIVX_CHI2;
   Int_t           pplus_ORIVX_NDOF;
   Float_t         pplus_ORIVX_COV_[3][3];
   Double_t        pplus_IP_ORIVX;
   Double_t        pplus_IPCHI2_ORIVX;
   Double_t        pplus_P;
   Double_t        pplus_PT;
   Double_t        pplus_PE;
   Double_t        pplus_PX;
   Double_t        pplus_PY;
   Double_t        pplus_PZ;
   Double_t        pplus_REFPX;
   Double_t        pplus_REFPY;
   Double_t        pplus_REFPZ;
   Double_t        pplus_M;
   Double_t        pplus_AtVtx_PE;
   Double_t        pplus_AtVtx_PX;
   Double_t        pplus_AtVtx_PY;
   Double_t        pplus_AtVtx_PZ;
   Double_t        pplus_L0Calo_HCAL_realET;
   Double_t        pplus_L0Calo_HCAL_xProjection;
   Double_t        pplus_L0Calo_HCAL_yProjection;
   Int_t           pplus_L0Calo_HCAL_region;
   Int_t           pplus_ID;
   Double_t        pplus_PIDe;
   Double_t        pplus_PIDmu;
   Double_t        pplus_PIDK;
   Double_t        pplus_PIDp;
   Double_t        pplus_ProbNNe;
   Double_t        pplus_ProbNNk;
   Double_t        pplus_ProbNNp;
   Double_t        pplus_ProbNNpi;
   Double_t        pplus_ProbNNmu;
   Double_t        pplus_ProbNNghost;
   Bool_t          pplus_hasMuon;
   Bool_t          pplus_isMuon;
   Bool_t          pplus_hasRich;
   Bool_t          pplus_hasCalo;
   Bool_t          pplus_UsedRichAerogel;
   Bool_t          pplus_UsedRich1Gas;
   Bool_t          pplus_UsedRich2Gas;
   Bool_t          pplus_RichAboveElThres;
   Bool_t          pplus_RichAboveMuThres;
   Bool_t          pplus_RichAbovePiThres;
   Bool_t          pplus_RichAboveKaThres;
   Bool_t          pplus_RichAbovePrThres;
   Double_t        pplus_RichDLLe;
   Double_t        pplus_RichDLLmu;
   Double_t        pplus_RichDLLpi;
   Double_t        pplus_RichDLLk;
   Double_t        pplus_RichDLLp;
   Double_t        pplus_RichDLLbt;
   Bool_t          pplus_InAccMuon;
   Bool_t          pplus_isMuonLoose;
   Double_t        pplus_MuonMuLL;
   Double_t        pplus_MuonBkgLL;
   Int_t           pplus_MuonNShared;
   Bool_t          pplus_InAccEcal;
   Double_t        pplus_CaloEcalE;
   Double_t        pplus_EcalPIDe;
   Double_t        pplus_EcalPIDmu;
   Bool_t          pplus_InAccHcal;
   Double_t        pplus_CaloHcalE;
   Double_t        pplus_HcalPIDe;
   Double_t        pplus_HcalPIDmu;
   Bool_t          pplus_InAccPrs;
   Double_t        pplus_PrsPIDe;
   Double_t        pplus_CaloPrsE;
   Bool_t          pplus_InAccSpd;
   Double_t        pplus_CaloSpdE;
   Bool_t          pplus_InAccBrem;
   Double_t        pplus_BremPIDe;
   Double_t        pplus_VeloCharge;
   Int_t           pplus_TRACK_Type;
   Int_t           pplus_TRACK_Key;
   Double_t        pplus_TRACK_CHI2;
   Int_t           pplus_TRACK_NDOF;
   Double_t        pplus_TRACK_CHI2NDOF;
   Double_t        pplus_TRACK_PCHI2;
   Double_t        pplus_TRACK_VeloCHI2NDOF;
   Double_t        pplus_TRACK_TCHI2NDOF;
   Double_t        pplus_VELO_UTID;
   Double_t        pplus_TRACK_FirstMeasurementX;
   Double_t        pplus_TRACK_FirstMeasurementY;
   Double_t        pplus_TRACK_FirstMeasurementZ;
   Double_t        pplus_TRACK_MatchCHI2;
   Double_t        pplus_TRACK_GhostProb;
   Double_t        pplus_TRACK_CloneDist;
   Double_t        pplus_TRACK_Likelihood;
   Double_t        Psi_MINIP;
   Double_t        Psi_MINIPCHI2;
   Double_t        Psi_MINIPNEXTBEST;
   Double_t        Psi_MINIPCHI2NEXTBEST;
   Float_t         Psi_AllIP[100];   //[nPV]
   Float_t         Psi_AllIPchi2[100];   //[nPV]
   Double_t        Psi_ENDVERTEX_X;
   Double_t        Psi_ENDVERTEX_Y;
   Double_t        Psi_ENDVERTEX_Z;
   Double_t        Psi_ENDVERTEX_XERR;
   Double_t        Psi_ENDVERTEX_YERR;
   Double_t        Psi_ENDVERTEX_ZERR;
   Double_t        Psi_ENDVERTEX_CHI2;
   Int_t           Psi_ENDVERTEX_NDOF;
   Float_t         Psi_ENDVERTEX_COV_[3][3];
   Double_t        Psi_OWNPV_X;
   Double_t        Psi_OWNPV_Y;
   Double_t        Psi_OWNPV_Z;
   Double_t        Psi_OWNPV_XERR;
   Double_t        Psi_OWNPV_YERR;
   Double_t        Psi_OWNPV_ZERR;
   Double_t        Psi_OWNPV_CHI2;
   Int_t           Psi_OWNPV_NDOF;
   Float_t         Psi_OWNPV_COV_[3][3];
   Double_t        Psi_IP_OWNPV;
   Double_t        Psi_IPCHI2_OWNPV;
   Double_t        Psi_FD_OWNPV;
   Double_t        Psi_FDCHI2_OWNPV;
   Double_t        Psi_DIRA_OWNPV;
   Double_t        Psi_TOPPV_X;
   Double_t        Psi_TOPPV_Y;
   Double_t        Psi_TOPPV_Z;
   Double_t        Psi_TOPPV_XERR;
   Double_t        Psi_TOPPV_YERR;
   Double_t        Psi_TOPPV_ZERR;
   Double_t        Psi_TOPPV_CHI2;
   Int_t           Psi_TOPPV_NDOF;
   Float_t         Psi_TOPPV_COV_[3][3];
   Double_t        Psi_IP_TOPPV;
   Double_t        Psi_IPCHI2_TOPPV;
   Double_t        Psi_FD_TOPPV;
   Double_t        Psi_FDCHI2_TOPPV;
   Double_t        Psi_DIRA_TOPPV;
   Double_t        Psi_ORIVX_X;
   Double_t        Psi_ORIVX_Y;
   Double_t        Psi_ORIVX_Z;
   Double_t        Psi_ORIVX_XERR;
   Double_t        Psi_ORIVX_YERR;
   Double_t        Psi_ORIVX_ZERR;
   Double_t        Psi_ORIVX_CHI2;
   Int_t           Psi_ORIVX_NDOF;
   Float_t         Psi_ORIVX_COV_[3][3];
   Double_t        Psi_IP_ORIVX;
   Double_t        Psi_IPCHI2_ORIVX;
   Double_t        Psi_FD_ORIVX;
   Double_t        Psi_FDCHI2_ORIVX;
   Double_t        Psi_DIRA_ORIVX;
   Double_t        Psi_P;
   Double_t        Psi_PT;
   Double_t        Psi_PE;
   Double_t        Psi_PX;
   Double_t        Psi_PY;
   Double_t        Psi_PZ;
   Double_t        Psi_REFPX;
   Double_t        Psi_REFPY;
   Double_t        Psi_REFPZ;
   Double_t        Psi_MM;
   Double_t        Psi_MMERR;
   Double_t        Psi_M;
   Int_t           Psi_ID;
   Double_t        Psi_TAU;
   Double_t        Psi_TAUERR;
   Double_t        Psi_TAUCHI2;
   Bool_t          Psi_L0Global_Dec;
   Bool_t          Psi_L0Global_TIS;
   Bool_t          Psi_L0Global_TOS;
   Bool_t          Psi_Hlt1Global_Dec;
   Bool_t          Psi_Hlt1Global_TIS;
   Bool_t          Psi_Hlt1Global_TOS;
   Bool_t          Psi_Hlt1Phys_Dec;
   Bool_t          Psi_Hlt1Phys_TIS;
   Bool_t          Psi_Hlt1Phys_TOS;
   Bool_t          Psi_Hlt2Global_Dec;
   Bool_t          Psi_Hlt2Global_TIS;
   Bool_t          Psi_Hlt2Global_TOS;
   Bool_t          Psi_Hlt2Phys_Dec;
   Bool_t          Psi_Hlt2Phys_TIS;
   Bool_t          Psi_Hlt2Phys_TOS;
   Bool_t          Psi_StrippingGlobal_Dec;
   Bool_t          Psi_StrippingGlobal_TIS;
   Bool_t          Psi_StrippingGlobal_TOS;
   Bool_t          Psi_L0HadronDecision_Dec;
   Bool_t          Psi_L0HadronDecision_TIS;
   Bool_t          Psi_L0HadronDecision_TOS;
   Bool_t          Psi_L0MuonDecision_Dec;
   Bool_t          Psi_L0MuonDecision_TIS;
   Bool_t          Psi_L0MuonDecision_TOS;
   Bool_t          Psi_L0DiMuonDecision_Dec;
   Bool_t          Psi_L0DiMuonDecision_TIS;
   Bool_t          Psi_L0DiMuonDecision_TOS;
   Bool_t          Psi_L0ElectronDecision_Dec;
   Bool_t          Psi_L0ElectronDecision_TIS;
   Bool_t          Psi_L0ElectronDecision_TOS;
   Bool_t          Psi_L0PhotonDecision_Dec;
   Bool_t          Psi_L0PhotonDecision_TIS;
   Bool_t          Psi_L0PhotonDecision_TOS;
   Bool_t          Psi_Hlt1TrackAllL0Decision_Dec;
   Bool_t          Psi_Hlt1TrackAllL0Decision_TIS;
   Bool_t          Psi_Hlt1TrackAllL0Decision_TOS;
   Bool_t          Psi_Hlt1TrackAllL0TightDecision_Dec;
   Bool_t          Psi_Hlt1TrackAllL0TightDecision_TIS;
   Bool_t          Psi_Hlt1TrackAllL0TightDecision_TOS;
   Bool_t          Psi_Hlt1DiMuonHighMassDecision_Dec;
   Bool_t          Psi_Hlt1DiMuonHighMassDecision_TIS;
   Bool_t          Psi_Hlt1DiMuonHighMassDecision_TOS;
   Bool_t          Psi_Hlt1DiMuonLowMassDecision_Dec;
   Bool_t          Psi_Hlt1DiMuonLowMassDecision_TIS;
   Bool_t          Psi_Hlt1DiMuonLowMassDecision_TOS;
   Bool_t          Psi_Hlt1SingleMuonHighPTDecision_Dec;
   Bool_t          Psi_Hlt1SingleMuonHighPTDecision_TIS;
   Bool_t          Psi_Hlt1SingleMuonHighPTDecision_TOS;
   Bool_t          Psi_Hlt1SingleMuonNoIPDecision_Dec;
   Bool_t          Psi_Hlt1SingleMuonNoIPDecision_TIS;
   Bool_t          Psi_Hlt1SingleMuonNoIPDecision_TOS;
   Bool_t          Psi_Hlt1TrackMuonDecision_Dec;
   Bool_t          Psi_Hlt1TrackMuonDecision_TIS;
   Bool_t          Psi_Hlt1TrackMuonDecision_TOS;
   Bool_t          Psi_Hlt2Topo2BodyBBDTDecision_Dec;
   Bool_t          Psi_Hlt2Topo2BodyBBDTDecision_TIS;
   Bool_t          Psi_Hlt2Topo2BodyBBDTDecision_TOS;
   Bool_t          Psi_Hlt2Topo2BodySimpleDecision_Dec;
   Bool_t          Psi_Hlt2Topo2BodySimpleDecision_TIS;
   Bool_t          Psi_Hlt2Topo2BodySimpleDecision_TOS;
   Bool_t          Psi_Hlt2Topo3BodyBBDTDecision_Dec;
   Bool_t          Psi_Hlt2Topo3BodyBBDTDecision_TIS;
   Bool_t          Psi_Hlt2Topo3BodyBBDTDecision_TOS;
   Bool_t          Psi_Hlt2Topo3BodySimpleDecision_Dec;
   Bool_t          Psi_Hlt2Topo3BodySimpleDecision_TIS;
   Bool_t          Psi_Hlt2Topo3BodySimpleDecision_TOS;
   Bool_t          Psi_Hlt2Topo4BodyBBDTDecision_Dec;
   Bool_t          Psi_Hlt2Topo4BodyBBDTDecision_TIS;
   Bool_t          Psi_Hlt2Topo4BodyBBDTDecision_TOS;
   Bool_t          Psi_Hlt2Topo4BodySimpleDecision_Dec;
   Bool_t          Psi_Hlt2Topo4BodySimpleDecision_TIS;
   Bool_t          Psi_Hlt2Topo4BodySimpleDecision_TOS;
   Bool_t          Psi_Hlt2DiMuonDecision_Dec;
   Bool_t          Psi_Hlt2DiMuonDecision_TIS;
   Bool_t          Psi_Hlt2DiMuonDecision_TOS;
   Bool_t          Psi_Hlt2DiMuonBDecision_Dec;
   Bool_t          Psi_Hlt2DiMuonBDecision_TIS;
   Bool_t          Psi_Hlt2DiMuonBDecision_TOS;
   Bool_t          Psi_Hlt2DiMuonDetachedDecision_Dec;
   Bool_t          Psi_Hlt2DiMuonDetachedDecision_TIS;
   Bool_t          Psi_Hlt2DiMuonDetachedDecision_TOS;
   Bool_t          Psi_Hlt2DiMuonDetachedHeavyDecision_Dec;
   Bool_t          Psi_Hlt2DiMuonDetachedHeavyDecision_TIS;
   Bool_t          Psi_Hlt2DiMuonDetachedHeavyDecision_TOS;
   Bool_t          Psi_Hlt2DiMuonDetachedJPsiDecision_Dec;
   Bool_t          Psi_Hlt2DiMuonDetachedJPsiDecision_TIS;
   Bool_t          Psi_Hlt2DiMuonDetachedJPsiDecision_TOS;
   Bool_t          Psi_Hlt2DiMuonDetachedPsi2SDecision_Dec;
   Bool_t          Psi_Hlt2DiMuonDetachedPsi2SDecision_TIS;
   Bool_t          Psi_Hlt2DiMuonDetachedPsi2SDecision_TOS;
   Bool_t          Psi_Hlt2DiMuonJPsiDecision_Dec;
   Bool_t          Psi_Hlt2DiMuonJPsiDecision_TIS;
   Bool_t          Psi_Hlt2DiMuonJPsiDecision_TOS;
   Bool_t          Psi_Hlt2DiMuonJPsiHighPTDecision_Dec;
   Bool_t          Psi_Hlt2DiMuonJPsiHighPTDecision_TIS;
   Bool_t          Psi_Hlt2DiMuonJPsiHighPTDecision_TOS;
   Bool_t          Psi_Hlt2DiMuonLowMassDecision_Dec;
   Bool_t          Psi_Hlt2DiMuonLowMassDecision_TIS;
   Bool_t          Psi_Hlt2DiMuonLowMassDecision_TOS;
   Bool_t          Psi_Hlt2DiMuonPsi2SDecision_Dec;
   Bool_t          Psi_Hlt2DiMuonPsi2SDecision_TIS;
   Bool_t          Psi_Hlt2DiMuonPsi2SDecision_TOS;
   Bool_t          Psi_Hlt2DiMuonPsi2SHighPTDecision_Dec;
   Bool_t          Psi_Hlt2DiMuonPsi2SHighPTDecision_TIS;
   Bool_t          Psi_Hlt2DiMuonPsi2SHighPTDecision_TOS;
   Bool_t          Psi_Hlt2LowMultMuonDecision_Dec;
   Bool_t          Psi_Hlt2LowMultMuonDecision_TIS;
   Bool_t          Psi_Hlt2LowMultMuonDecision_TOS;
   Bool_t          Psi_Hlt2MuonFromHLT1Decision_Dec;
   Bool_t          Psi_Hlt2MuonFromHLT1Decision_TIS;
   Bool_t          Psi_Hlt2MuonFromHLT1Decision_TOS;
   Bool_t          Psi_Hlt2SingleMuonDecision_Dec;
   Bool_t          Psi_Hlt2SingleMuonDecision_TIS;
   Bool_t          Psi_Hlt2SingleMuonDecision_TOS;
   Bool_t          Psi_Hlt2SingleMuonHighPTDecision_Dec;
   Bool_t          Psi_Hlt2SingleMuonHighPTDecision_TIS;
   Bool_t          Psi_Hlt2SingleMuonHighPTDecision_TOS;
   Bool_t          Psi_Hlt2SingleMuonLowPTDecision_Dec;
   Bool_t          Psi_Hlt2SingleMuonLowPTDecision_TIS;
   Bool_t          Psi_Hlt2SingleMuonLowPTDecision_TOS;
   Bool_t          Psi_Hlt2SingleMuonVHighPTDecision_Dec;
   Bool_t          Psi_Hlt2SingleMuonVHighPTDecision_TIS;
   Bool_t          Psi_Hlt2SingleMuonVHighPTDecision_TOS;
   Bool_t          Psi_Hlt2TopoMu2BodyBBDTDecision_Dec;
   Bool_t          Psi_Hlt2TopoMu2BodyBBDTDecision_TIS;
   Bool_t          Psi_Hlt2TopoMu2BodyBBDTDecision_TOS;
   Bool_t          Psi_Hlt2TopoMu3BodyBBDTDecision_Dec;
   Bool_t          Psi_Hlt2TopoMu3BodyBBDTDecision_TIS;
   Bool_t          Psi_Hlt2TopoMu3BodyBBDTDecision_TOS;
   Bool_t          Psi_Hlt2TopoMu4BodyBBDTDecision_Dec;
   Bool_t          Psi_Hlt2TopoMu4BodyBBDTDecision_TIS;
   Bool_t          Psi_Hlt2TopoMu4BodyBBDTDecision_TOS;
   Bool_t          Psi_Hlt2diPhotonDiMuonDecision_Dec;
   Bool_t          Psi_Hlt2diPhotonDiMuonDecision_TIS;
   Bool_t          Psi_Hlt2diPhotonDiMuonDecision_TOS;
   Int_t           Psi_NOPARTWITHINDCHI2WDW;
   Int_t           Psi_NOPARTWITHINCHI2WDW;
   Double_t        Psi_SMALLESTCHI2;
   Double_t        Psi_SMALLESTDELTACHI2;
   Double_t        muminus_MINIP;
   Double_t        muminus_MINIPCHI2;
   Double_t        muminus_MINIPNEXTBEST;
   Double_t        muminus_MINIPCHI2NEXTBEST;
   Float_t         muminus_AllIP[100];   //[nPV]
   Float_t         muminus_AllIPchi2[100];   //[nPV]
   Double_t        muminus_OWNPV_X;
   Double_t        muminus_OWNPV_Y;
   Double_t        muminus_OWNPV_Z;
   Double_t        muminus_OWNPV_XERR;
   Double_t        muminus_OWNPV_YERR;
   Double_t        muminus_OWNPV_ZERR;
   Double_t        muminus_OWNPV_CHI2;
   Int_t           muminus_OWNPV_NDOF;
   Float_t         muminus_OWNPV_COV_[3][3];
   Double_t        muminus_IP_OWNPV;
   Double_t        muminus_IPCHI2_OWNPV;
   Double_t        muminus_TOPPV_X;
   Double_t        muminus_TOPPV_Y;
   Double_t        muminus_TOPPV_Z;
   Double_t        muminus_TOPPV_XERR;
   Double_t        muminus_TOPPV_YERR;
   Double_t        muminus_TOPPV_ZERR;
   Double_t        muminus_TOPPV_CHI2;
   Int_t           muminus_TOPPV_NDOF;
   Float_t         muminus_TOPPV_COV_[3][3];
   Double_t        muminus_IP_TOPPV;
   Double_t        muminus_IPCHI2_TOPPV;
   Double_t        muminus_ORIVX_X;
   Double_t        muminus_ORIVX_Y;
   Double_t        muminus_ORIVX_Z;
   Double_t        muminus_ORIVX_XERR;
   Double_t        muminus_ORIVX_YERR;
   Double_t        muminus_ORIVX_ZERR;
   Double_t        muminus_ORIVX_CHI2;
   Int_t           muminus_ORIVX_NDOF;
   Float_t         muminus_ORIVX_COV_[3][3];
   Double_t        muminus_IP_ORIVX;
   Double_t        muminus_IPCHI2_ORIVX;
   Double_t        muminus_P;
   Double_t        muminus_PT;
   Double_t        muminus_PE;
   Double_t        muminus_PX;
   Double_t        muminus_PY;
   Double_t        muminus_PZ;
   Double_t        muminus_REFPX;
   Double_t        muminus_REFPY;
   Double_t        muminus_REFPZ;
   Double_t        muminus_M;
   Double_t        muminus_AtVtx_PE;
   Double_t        muminus_AtVtx_PX;
   Double_t        muminus_AtVtx_PY;
   Double_t        muminus_AtVtx_PZ;
   Double_t        muminus_L0Calo_HCAL_realET;
   Double_t        muminus_L0Calo_HCAL_xProjection;
   Double_t        muminus_L0Calo_HCAL_yProjection;
   Int_t           muminus_L0Calo_HCAL_region;
   Int_t           muminus_ID;
   Double_t        muminus_PIDe;
   Double_t        muminus_PIDmu;
   Double_t        muminus_PIDK;
   Double_t        muminus_PIDp;
   Double_t        muminus_ProbNNe;
   Double_t        muminus_ProbNNk;
   Double_t        muminus_ProbNNp;
   Double_t        muminus_ProbNNpi;
   Double_t        muminus_ProbNNmu;
   Double_t        muminus_ProbNNghost;
   Bool_t          muminus_hasMuon;
   Bool_t          muminus_isMuon;
   Bool_t          muminus_hasRich;
   Bool_t          muminus_hasCalo;
   Bool_t          muminus_UsedRichAerogel;
   Bool_t          muminus_UsedRich1Gas;
   Bool_t          muminus_UsedRich2Gas;
   Bool_t          muminus_RichAboveElThres;
   Bool_t          muminus_RichAboveMuThres;
   Bool_t          muminus_RichAbovePiThres;
   Bool_t          muminus_RichAboveKaThres;
   Bool_t          muminus_RichAbovePrThres;
   Double_t        muminus_RichDLLe;
   Double_t        muminus_RichDLLmu;
   Double_t        muminus_RichDLLpi;
   Double_t        muminus_RichDLLk;
   Double_t        muminus_RichDLLp;
   Double_t        muminus_RichDLLbt;
   Bool_t          muminus_InAccMuon;
   Bool_t          muminus_isMuonLoose;
   Double_t        muminus_MuonMuLL;
   Double_t        muminus_MuonBkgLL;
   Int_t           muminus_MuonNShared;
   Bool_t          muminus_InAccEcal;
   Double_t        muminus_CaloEcalE;
   Double_t        muminus_EcalPIDe;
   Double_t        muminus_EcalPIDmu;
   Bool_t          muminus_InAccHcal;
   Double_t        muminus_CaloHcalE;
   Double_t        muminus_HcalPIDe;
   Double_t        muminus_HcalPIDmu;
   Bool_t          muminus_InAccPrs;
   Double_t        muminus_PrsPIDe;
   Double_t        muminus_CaloPrsE;
   Bool_t          muminus_InAccSpd;
   Double_t        muminus_CaloSpdE;
   Bool_t          muminus_InAccBrem;
   Double_t        muminus_BremPIDe;
   Double_t        muminus_VeloCharge;
   Int_t           muminus_TRACK_Type;
   Int_t           muminus_TRACK_Key;
   Double_t        muminus_TRACK_CHI2;
   Int_t           muminus_TRACK_NDOF;
   Double_t        muminus_TRACK_CHI2NDOF;
   Double_t        muminus_TRACK_PCHI2;
   Double_t        muminus_TRACK_VeloCHI2NDOF;
   Double_t        muminus_TRACK_TCHI2NDOF;
   Double_t        muminus_VELO_UTID;
   Double_t        muminus_TRACK_FirstMeasurementX;
   Double_t        muminus_TRACK_FirstMeasurementY;
   Double_t        muminus_TRACK_FirstMeasurementZ;
   Double_t        muminus_TRACK_MatchCHI2;
   Double_t        muminus_TRACK_GhostProb;
   Double_t        muminus_TRACK_CloneDist;
   Double_t        muminus_TRACK_Likelihood;
   Double_t        muplus_MINIP;
   Double_t        muplus_MINIPCHI2;
   Double_t        muplus_MINIPNEXTBEST;
   Double_t        muplus_MINIPCHI2NEXTBEST;
   Float_t         muplus_AllIP[100];   //[nPV]
   Float_t         muplus_AllIPchi2[100];   //[nPV]
   Double_t        muplus_OWNPV_X;
   Double_t        muplus_OWNPV_Y;
   Double_t        muplus_OWNPV_Z;
   Double_t        muplus_OWNPV_XERR;
   Double_t        muplus_OWNPV_YERR;
   Double_t        muplus_OWNPV_ZERR;
   Double_t        muplus_OWNPV_CHI2;
   Int_t           muplus_OWNPV_NDOF;
   Float_t         muplus_OWNPV_COV_[3][3];
   Double_t        muplus_IP_OWNPV;
   Double_t        muplus_IPCHI2_OWNPV;
   Double_t        muplus_TOPPV_X;
   Double_t        muplus_TOPPV_Y;
   Double_t        muplus_TOPPV_Z;
   Double_t        muplus_TOPPV_XERR;
   Double_t        muplus_TOPPV_YERR;
   Double_t        muplus_TOPPV_ZERR;
   Double_t        muplus_TOPPV_CHI2;
   Int_t           muplus_TOPPV_NDOF;
   Float_t         muplus_TOPPV_COV_[3][3];
   Double_t        muplus_IP_TOPPV;
   Double_t        muplus_IPCHI2_TOPPV;
   Double_t        muplus_ORIVX_X;
   Double_t        muplus_ORIVX_Y;
   Double_t        muplus_ORIVX_Z;
   Double_t        muplus_ORIVX_XERR;
   Double_t        muplus_ORIVX_YERR;
   Double_t        muplus_ORIVX_ZERR;
   Double_t        muplus_ORIVX_CHI2;
   Int_t           muplus_ORIVX_NDOF;
   Float_t         muplus_ORIVX_COV_[3][3];
   Double_t        muplus_IP_ORIVX;
   Double_t        muplus_IPCHI2_ORIVX;
   Double_t        muplus_P;
   Double_t        muplus_PT;
   Double_t        muplus_PE;
   Double_t        muplus_PX;
   Double_t        muplus_PY;
   Double_t        muplus_PZ;
   Double_t        muplus_REFPX;
   Double_t        muplus_REFPY;
   Double_t        muplus_REFPZ;
   Double_t        muplus_M;
   Double_t        muplus_AtVtx_PE;
   Double_t        muplus_AtVtx_PX;
   Double_t        muplus_AtVtx_PY;
   Double_t        muplus_AtVtx_PZ;
   Double_t        muplus_L0Calo_HCAL_realET;
   Double_t        muplus_L0Calo_HCAL_xProjection;
   Double_t        muplus_L0Calo_HCAL_yProjection;
   Int_t           muplus_L0Calo_HCAL_region;
   Int_t           muplus_ID;
   Double_t        muplus_PIDe;
   Double_t        muplus_PIDmu;
   Double_t        muplus_PIDK;
   Double_t        muplus_PIDp;
   Double_t        muplus_ProbNNe;
   Double_t        muplus_ProbNNk;
   Double_t        muplus_ProbNNp;
   Double_t        muplus_ProbNNpi;
   Double_t        muplus_ProbNNmu;
   Double_t        muplus_ProbNNghost;
   Bool_t          muplus_hasMuon;
   Bool_t          muplus_isMuon;
   Bool_t          muplus_hasRich;
   Bool_t          muplus_hasCalo;
   Bool_t          muplus_UsedRichAerogel;
   Bool_t          muplus_UsedRich1Gas;
   Bool_t          muplus_UsedRich2Gas;
   Bool_t          muplus_RichAboveElThres;
   Bool_t          muplus_RichAboveMuThres;
   Bool_t          muplus_RichAbovePiThres;
   Bool_t          muplus_RichAboveKaThres;
   Bool_t          muplus_RichAbovePrThres;
   Double_t        muplus_RichDLLe;
   Double_t        muplus_RichDLLmu;
   Double_t        muplus_RichDLLpi;
   Double_t        muplus_RichDLLk;
   Double_t        muplus_RichDLLp;
   Double_t        muplus_RichDLLbt;
   Bool_t          muplus_InAccMuon;
   Bool_t          muplus_isMuonLoose;
   Double_t        muplus_MuonMuLL;
   Double_t        muplus_MuonBkgLL;
   Int_t           muplus_MuonNShared;
   Bool_t          muplus_InAccEcal;
   Double_t        muplus_CaloEcalE;
   Double_t        muplus_EcalPIDe;
   Double_t        muplus_EcalPIDmu;
   Bool_t          muplus_InAccHcal;
   Double_t        muplus_CaloHcalE;
   Double_t        muplus_HcalPIDe;
   Double_t        muplus_HcalPIDmu;
   Bool_t          muplus_InAccPrs;
   Double_t        muplus_PrsPIDe;
   Double_t        muplus_CaloPrsE;
   Bool_t          muplus_InAccSpd;
   Double_t        muplus_CaloSpdE;
   Bool_t          muplus_InAccBrem;
   Double_t        muplus_BremPIDe;
   Double_t        muplus_VeloCharge;
   Int_t           muplus_TRACK_Type;
   Int_t           muplus_TRACK_Key;
   Double_t        muplus_TRACK_CHI2;
   Int_t           muplus_TRACK_NDOF;
   Double_t        muplus_TRACK_CHI2NDOF;
   Double_t        muplus_TRACK_PCHI2;
   Double_t        muplus_TRACK_VeloCHI2NDOF;
   Double_t        muplus_TRACK_TCHI2NDOF;
   Double_t        muplus_VELO_UTID;
   Double_t        muplus_TRACK_FirstMeasurementX;
   Double_t        muplus_TRACK_FirstMeasurementY;
   Double_t        muplus_TRACK_FirstMeasurementZ;
   Double_t        muplus_TRACK_MatchCHI2;
   Double_t        muplus_TRACK_GhostProb;
   Double_t        muplus_TRACK_CloneDist;
   Double_t        muplus_TRACK_Likelihood;
   UInt_t          nCandidate;
   ULong64_t       totCandidates;
   ULong64_t       EventInSequence;
   UInt_t          runNumber;
   ULong64_t       eventNumber;
   UInt_t          BCID;
   Int_t           BCType;
   UInt_t          OdinTCK;
   UInt_t          L0DUTCK;
   UInt_t          HLTTCK;
   ULong64_t       GpsTime;
   Int_t           GpsYear;
   Int_t           GpsMonth;
   Int_t           GpsDay;
   Int_t           GpsHour;
   Int_t           GpsMinute;
   Double_t        GpsSecond;
   Int_t           TriggerType;
   Short_t         Polarity;
   Double_t        SignedRelativeCurrent;
   Float_t         PVX[100];   //[nPV]
   Float_t         PVY[100];   //[nPV]
   Float_t         PVZ[100];   //[nPV]
   Float_t         PVXERR[100];   //[nPV]
   Float_t         PVYERR[100];   //[nPV]
   Float_t         PVZERR[100];   //[nPV]
   Float_t         PVCHI2[100];   //[nPV]
   Float_t         PVNDOF[100];   //[nPV]
   Float_t         PVNTRACKS[100];   //[nPV]
   Int_t           nPVs;
   Int_t           nTracks;
   Int_t           nLongTracks;
   Int_t           nDownstreamTracks;
   Int_t           nUpstreamTracks;
   Int_t           nVeloTracks;
   Int_t           nTTracks;
   Int_t           nBackTracks;
   Int_t           nRich1Hits;
   Int_t           nRich2Hits;
   Int_t           nVeloClusters;
   Int_t           nITClusters;
   Int_t           nTTClusters;
   Int_t           nOTClusters;
   Int_t           nSPDHits;
   Int_t           nMuonCoordsS0;
   Int_t           nMuonCoordsS1;
   Int_t           nMuonCoordsS2;
   Int_t           nMuonCoordsS3;
   Int_t           nMuonCoordsS4;
   Int_t           nMuonTracks;
   UInt_t          StrippingBetaSBd2JpsiKsDetachedLineDecision;
   UInt_t          StrippingBetaSBd2JpsiKsPrescaledLineDecision;
   UInt_t          StrippingBetaSBd2JpsiKstarDetachedLineDecision;
   UInt_t          StrippingBetaSBd2JpsiKstarPrescaledLineDecision;
   UInt_t          StrippingBetaSBs2ChicPhi_Chic2KKPiPiNominalLineDecision;
   UInt_t          StrippingBetaSBs2ChicPhi_Chic2PiPiPiPiNominalLineDecision;
   UInt_t          StrippingBetaSBs2EtacPhiNominalLineDecision;
   UInt_t          StrippingBetaSBs2JpsiEtaDetachedLineDecision;
   UInt_t          StrippingBetaSBs2JpsiEtaPrescaledLineDecision;
   UInt_t          StrippingBetaSBs2JpsiKstarLineDecision;
   UInt_t          StrippingBetaSBs2JpsiPhiDetachedLineDecision;
   UInt_t          StrippingBetaSBs2JpsiPhiPrescaledLineDecision;
   UInt_t          StrippingBetaSBs2JpsieePhiDetachedLineDecision;
   UInt_t          StrippingBetaSBs2JpsieePhiLineDecision;
   UInt_t          StrippingBetaSBs2Jpsif0LineDecision;
   UInt_t          StrippingBetaSBs2K0stK0stNominalLineDecision;
   UInt_t          StrippingBetaSBs2KstKstNominalLineDecision;
   UInt_t          StrippingBetaSBs2KstKstSameChargeLineDecision;
   UInt_t          StrippingBetaSBs2PhiKstNominalLineDecision;
   UInt_t          StrippingBetaSBs2PhiPhiLineDecision;
   UInt_t          StrippingBetaSBs2PhiPhiWideLineDecision;
   UInt_t          StrippingBetaSBs2Q2Body4piLineDecision;
   UInt_t          StrippingBetaSBu2JpsiKDetachedLineDecision;
   UInt_t          StrippingBetaSBu2JpsiKNoPIDDetachedLineDecision;
   UInt_t          StrippingBetaSBu2JpsiKPrescaledLineDecision;
   UInt_t          StrippingBetaSJpsi2MuMuDetachedLineDecision;
   UInt_t          StrippingBetaSJpsi2MuMuLineDecision;
   UInt_t          StrippingBetaSLambdab2JpsiLambdaUnbiasedLineDecision;
   UInt_t          StrippingBu2LLK_eeLineDecision;
   UInt_t          StrippingBu2LLK_mmLineDecision;
   UInt_t          StrippingBd2KstarMuMu_BdToKstarMuMuLineDecision;
   UInt_t          StrippingBd2KstarMuMu_BdToKstarMuMuLowPLineDecision;
   UInt_t          StrippingBd2KstarMuMu_BdToKstarMuMuSSLineDecision;
   UInt_t          StrippingBd2KstarMuMu_BdToKstarMuMuSSLowPLineDecision;
   UInt_t          StrippingBd2KstarMuMu_BuToKMuMuLineDecision;
   UInt_t          StrippingBd2KstarMuMu_BuToKMuMuSSLineDecision;

   // List of branches
   TBranch        *b_B_MINIP;   //!
   TBranch        *b_B_MINIPCHI2;   //!
   TBranch        *b_B_MINIPNEXTBEST;   //!
   TBranch        *b_B_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_nPV;   //!
   TBranch        *b_B_AllIP;   //!
   TBranch        *b_B_AllIPchi2;   //!
   TBranch        *b_B_ENDVERTEX_X;   //!
   TBranch        *b_B_ENDVERTEX_Y;   //!
   TBranch        *b_B_ENDVERTEX_Z;   //!
   TBranch        *b_B_ENDVERTEX_XERR;   //!
   TBranch        *b_B_ENDVERTEX_YERR;   //!
   TBranch        *b_B_ENDVERTEX_ZERR;   //!
   TBranch        *b_B_ENDVERTEX_CHI2;   //!
   TBranch        *b_B_ENDVERTEX_NDOF;   //!
   TBranch        *b_B_ENDVERTEX_COV_;   //!
   TBranch        *b_B_OWNPV_X;   //!
   TBranch        *b_B_OWNPV_Y;   //!
   TBranch        *b_B_OWNPV_Z;   //!
   TBranch        *b_B_OWNPV_XERR;   //!
   TBranch        *b_B_OWNPV_YERR;   //!
   TBranch        *b_B_OWNPV_ZERR;   //!
   TBranch        *b_B_OWNPV_CHI2;   //!
   TBranch        *b_B_OWNPV_NDOF;   //!
   TBranch        *b_B_OWNPV_COV_;   //!
   TBranch        *b_B_IP_OWNPV;   //!
   TBranch        *b_B_IPCHI2_OWNPV;   //!
   TBranch        *b_B_FD_OWNPV;   //!
   TBranch        *b_B_FDCHI2_OWNPV;   //!
   TBranch        *b_B_DIRA_OWNPV;   //!
   TBranch        *b_B_TOPPV_X;   //!
   TBranch        *b_B_TOPPV_Y;   //!
   TBranch        *b_B_TOPPV_Z;   //!
   TBranch        *b_B_TOPPV_XERR;   //!
   TBranch        *b_B_TOPPV_YERR;   //!
   TBranch        *b_B_TOPPV_ZERR;   //!
   TBranch        *b_B_TOPPV_CHI2;   //!
   TBranch        *b_B_TOPPV_NDOF;   //!
   TBranch        *b_B_TOPPV_COV_;   //!
   TBranch        *b_B_IP_TOPPV;   //!
   TBranch        *b_B_IPCHI2_TOPPV;   //!
   TBranch        *b_B_FD_TOPPV;   //!
   TBranch        *b_B_FDCHI2_TOPPV;   //!
   TBranch        *b_B_DIRA_TOPPV;   //!
   TBranch        *b_B_P;   //!
   TBranch        *b_B_PT;   //!
   TBranch        *b_B_PE;   //!
   TBranch        *b_B_PX;   //!
   TBranch        *b_B_PY;   //!
   TBranch        *b_B_PZ;   //!
   TBranch        *b_B_REFPX;   //!
   TBranch        *b_B_REFPY;   //!
   TBranch        *b_B_REFPZ;   //!
   TBranch        *b_B_MM;   //!
   TBranch        *b_B_MMERR;   //!
   TBranch        *b_B_M;   //!
   TBranch        *b_B_ID;   //!
   TBranch        *b_B_TAU;   //!
   TBranch        *b_B_TAUERR;   //!
   TBranch        *b_B_TAUCHI2;   //!
   TBranch        *b_B_ConstBFit_nPV;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_M;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_MERR;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_P;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_P0_ID;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_P0_PE;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_P0_PX;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_P0_PY;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_P0_PZ;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_P1_ID;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_P1_PE;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_P1_PX;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_P1_PY;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_P1_PZ;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_PERR;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_ctau;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_ctauErr;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_decayLength;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_decayLengthErr;   //!
   TBranch        *b_B_ConstBFit_Lambda0_M;   //!
   TBranch        *b_B_ConstBFit_Lambda0_MERR;   //!
   TBranch        *b_B_ConstBFit_Lambda0_P;   //!
   TBranch        *b_B_ConstBFit_Lambda0_P0_ID;   //!
   TBranch        *b_B_ConstBFit_Lambda0_P0_PE;   //!
   TBranch        *b_B_ConstBFit_Lambda0_P0_PX;   //!
   TBranch        *b_B_ConstBFit_Lambda0_P0_PY;   //!
   TBranch        *b_B_ConstBFit_Lambda0_P0_PZ;   //!
   TBranch        *b_B_ConstBFit_Lambda0_P1_ID;   //!
   TBranch        *b_B_ConstBFit_Lambda0_P1_PE;   //!
   TBranch        *b_B_ConstBFit_Lambda0_P1_PX;   //!
   TBranch        *b_B_ConstBFit_Lambda0_P1_PY;   //!
   TBranch        *b_B_ConstBFit_Lambda0_P1_PZ;   //!
   TBranch        *b_B_ConstBFit_Lambda0_PERR;   //!
   TBranch        *b_B_ConstBFit_Lambda0_ctau;   //!
   TBranch        *b_B_ConstBFit_Lambda0_ctauErr;   //!
   TBranch        *b_B_ConstBFit_Lambda0_decayLength;   //!
   TBranch        *b_B_ConstBFit_Lambda0_decayLengthErr;   //!
   TBranch        *b_B_ConstBFit_M;   //!
   TBranch        *b_B_ConstBFit_MERR;   //!
   TBranch        *b_B_ConstBFit_P;   //!
   TBranch        *b_B_ConstBFit_PERR;   //!
   TBranch        *b_B_ConstBFit_PV_X;   //!
   TBranch        *b_B_ConstBFit_PV_Y;   //!
   TBranch        *b_B_ConstBFit_PV_Z;   //!
   TBranch        *b_B_ConstBFit_PV_key;   //!
   TBranch        *b_B_ConstBFit_chi2;   //!
   TBranch        *b_B_ConstBFit_ctau;   //!
   TBranch        *b_B_ConstBFit_ctauErr;   //!
   TBranch        *b_B_ConstBFit_decayLength;   //!
   TBranch        *b_B_ConstBFit_decayLengthErr;   //!
   TBranch        *b_B_ConstBFit_nDOF;   //!
   TBranch        *b_B_ConstBFit_nIter;   //!
   TBranch        *b_B_ConstBFit_status;   //!
   TBranch        *b_B_FullFit_nPV;   //!
   TBranch        *b_B_FullFit_J_psi_1S_M;   //!
   TBranch        *b_B_FullFit_J_psi_1S_MERR;   //!
   TBranch        *b_B_FullFit_J_psi_1S_P;   //!
   TBranch        *b_B_FullFit_J_psi_1S_PERR;   //!
   TBranch        *b_B_FullFit_J_psi_1S_ctau;   //!
   TBranch        *b_B_FullFit_J_psi_1S_ctauErr;   //!
   TBranch        *b_B_FullFit_J_psi_1S_decayLength;   //!
   TBranch        *b_B_FullFit_J_psi_1S_decayLengthErr;   //!
   TBranch        *b_B_FullFit_Lambda0_M;   //!
   TBranch        *b_B_FullFit_Lambda0_MERR;   //!
   TBranch        *b_B_FullFit_Lambda0_P;   //!
   TBranch        *b_B_FullFit_Lambda0_PERR;   //!
   TBranch        *b_B_FullFit_Lambda0_ctau;   //!
   TBranch        *b_B_FullFit_Lambda0_ctauErr;   //!
   TBranch        *b_B_FullFit_Lambda0_decayLength;   //!
   TBranch        *b_B_FullFit_Lambda0_decayLengthErr;   //!
   TBranch        *b_B_FullFit_M;   //!
   TBranch        *b_B_FullFit_MERR;   //!
   TBranch        *b_B_FullFit_P;   //!
   TBranch        *b_B_FullFit_PERR;   //!
   TBranch        *b_B_FullFit_PV_X;   //!
   TBranch        *b_B_FullFit_PV_Y;   //!
   TBranch        *b_B_FullFit_PV_Z;   //!
   TBranch        *b_B_FullFit_PV_key;   //!
   TBranch        *b_B_FullFit_chi2;   //!
   TBranch        *b_B_FullFit_ctau;   //!
   TBranch        *b_B_FullFit_ctauErr;   //!
   TBranch        *b_B_FullFit_decayLength;   //!
   TBranch        *b_B_FullFit_decayLengthErr;   //!
   TBranch        *b_B_FullFit_nDOF;   //!
   TBranch        *b_B_FullFit_nIter;   //!
   TBranch        *b_B_FullFit_status;   //!
   TBranch        *b_B_OnlyPsiFit_nPV;   //!
   TBranch        *b_B_OnlyPsiFit_J_psi_1S_M;   //!
   TBranch        *b_B_OnlyPsiFit_J_psi_1S_MERR;   //!
   TBranch        *b_B_OnlyPsiFit_J_psi_1S_P;   //!
   TBranch        *b_B_OnlyPsiFit_J_psi_1S_PERR;   //!
   TBranch        *b_B_OnlyPsiFit_J_psi_1S_ctau;   //!
   TBranch        *b_B_OnlyPsiFit_J_psi_1S_ctauErr;   //!
   TBranch        *b_B_OnlyPsiFit_J_psi_1S_decayLength;   //!
   TBranch        *b_B_OnlyPsiFit_J_psi_1S_decayLengthErr;   //!
   TBranch        *b_B_OnlyPsiFit_Lambda0_M;   //!
   TBranch        *b_B_OnlyPsiFit_Lambda0_MERR;   //!
   TBranch        *b_B_OnlyPsiFit_Lambda0_P;   //!
   TBranch        *b_B_OnlyPsiFit_Lambda0_PERR;   //!
   TBranch        *b_B_OnlyPsiFit_Lambda0_ctau;   //!
   TBranch        *b_B_OnlyPsiFit_Lambda0_ctauErr;   //!
   TBranch        *b_B_OnlyPsiFit_Lambda0_decayLength;   //!
   TBranch        *b_B_OnlyPsiFit_Lambda0_decayLengthErr;   //!
   TBranch        *b_B_OnlyPsiFit_M;   //!
   TBranch        *b_B_OnlyPsiFit_MERR;   //!
   TBranch        *b_B_OnlyPsiFit_P;   //!
   TBranch        *b_B_OnlyPsiFit_PERR;   //!
   TBranch        *b_B_OnlyPsiFit_PV_X;   //!
   TBranch        *b_B_OnlyPsiFit_PV_Y;   //!
   TBranch        *b_B_OnlyPsiFit_PV_Z;   //!
   TBranch        *b_B_OnlyPsiFit_PV_key;   //!
   TBranch        *b_B_OnlyPsiFit_chi2;   //!
   TBranch        *b_B_OnlyPsiFit_ctau;   //!
   TBranch        *b_B_OnlyPsiFit_ctauErr;   //!
   TBranch        *b_B_OnlyPsiFit_decayLength;   //!
   TBranch        *b_B_OnlyPsiFit_decayLengthErr;   //!
   TBranch        *b_B_OnlyPsiFit_nDOF;   //!
   TBranch        *b_B_OnlyPsiFit_nIter;   //!
   TBranch        *b_B_OnlyPsiFit_status;   //!
   TBranch        *b_B_L0Global_Dec;   //!
   TBranch        *b_B_L0Global_TIS;   //!
   TBranch        *b_B_L0Global_TOS;   //!
   TBranch        *b_B_Hlt1Global_Dec;   //!
   TBranch        *b_B_Hlt1Global_TIS;   //!
   TBranch        *b_B_Hlt1Global_TOS;   //!
   TBranch        *b_B_Hlt1Phys_Dec;   //!
   TBranch        *b_B_Hlt1Phys_TIS;   //!
   TBranch        *b_B_Hlt1Phys_TOS;   //!
   TBranch        *b_B_Hlt2Global_Dec;   //!
   TBranch        *b_B_Hlt2Global_TIS;   //!
   TBranch        *b_B_Hlt2Global_TOS;   //!
   TBranch        *b_B_Hlt2Phys_Dec;   //!
   TBranch        *b_B_Hlt2Phys_TIS;   //!
   TBranch        *b_B_Hlt2Phys_TOS;   //!
   TBranch        *b_B_StrippingGlobal_Dec;   //!
   TBranch        *b_B_StrippingGlobal_TIS;   //!
   TBranch        *b_B_StrippingGlobal_TOS;   //!
   TBranch        *b_B_L0HadronDecision_Dec;   //!
   TBranch        *b_B_L0HadronDecision_TIS;   //!
   TBranch        *b_B_L0HadronDecision_TOS;   //!
   TBranch        *b_B_L0MuonDecision_Dec;   //!
   TBranch        *b_B_L0MuonDecision_TIS;   //!
   TBranch        *b_B_L0MuonDecision_TOS;   //!
   TBranch        *b_B_L0DiMuonDecision_Dec;   //!
   TBranch        *b_B_L0DiMuonDecision_TIS;   //!
   TBranch        *b_B_L0DiMuonDecision_TOS;   //!
   TBranch        *b_B_L0ElectronDecision_Dec;   //!
   TBranch        *b_B_L0ElectronDecision_TIS;   //!
   TBranch        *b_B_L0ElectronDecision_TOS;   //!
   TBranch        *b_B_L0PhotonDecision_Dec;   //!
   TBranch        *b_B_L0PhotonDecision_TIS;   //!
   TBranch        *b_B_L0PhotonDecision_TOS;   //!
   TBranch        *b_B_Hlt1TrackAllL0Decision_Dec;   //!
   TBranch        *b_B_Hlt1TrackAllL0Decision_TIS;   //!
   TBranch        *b_B_Hlt1TrackAllL0Decision_TOS;   //!
   TBranch        *b_B_Hlt1TrackAllL0TightDecision_Dec;   //!
   TBranch        *b_B_Hlt1TrackAllL0TightDecision_TIS;   //!
   TBranch        *b_B_Hlt1TrackAllL0TightDecision_TOS;   //!
   TBranch        *b_B_Hlt1DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_B_Hlt1DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_B_Hlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_B_Hlt1DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_B_Hlt1DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_B_Hlt1DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_B_Hlt1SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_B_Hlt1SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_B_Hlt1SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_B_Hlt1SingleMuonNoIPDecision_Dec;   //!
   TBranch        *b_B_Hlt1SingleMuonNoIPDecision_TIS;   //!
   TBranch        *b_B_Hlt1SingleMuonNoIPDecision_TOS;   //!
   TBranch        *b_B_Hlt1TrackMuonDecision_Dec;   //!
   TBranch        *b_B_Hlt1TrackMuonDecision_TIS;   //!
   TBranch        *b_B_Hlt1TrackMuonDecision_TOS;   //!
   TBranch        *b_B_Hlt2Topo2BodyBBDTDecision_Dec;   //!
   TBranch        *b_B_Hlt2Topo2BodyBBDTDecision_TIS;   //!
   TBranch        *b_B_Hlt2Topo2BodyBBDTDecision_TOS;   //!
   TBranch        *b_B_Hlt2Topo2BodySimpleDecision_Dec;   //!
   TBranch        *b_B_Hlt2Topo2BodySimpleDecision_TIS;   //!
   TBranch        *b_B_Hlt2Topo2BodySimpleDecision_TOS;   //!
   TBranch        *b_B_Hlt2Topo3BodyBBDTDecision_Dec;   //!
   TBranch        *b_B_Hlt2Topo3BodyBBDTDecision_TIS;   //!
   TBranch        *b_B_Hlt2Topo3BodyBBDTDecision_TOS;   //!
   TBranch        *b_B_Hlt2Topo3BodySimpleDecision_Dec;   //!
   TBranch        *b_B_Hlt2Topo3BodySimpleDecision_TIS;   //!
   TBranch        *b_B_Hlt2Topo3BodySimpleDecision_TOS;   //!
   TBranch        *b_B_Hlt2Topo4BodyBBDTDecision_Dec;   //!
   TBranch        *b_B_Hlt2Topo4BodyBBDTDecision_TIS;   //!
   TBranch        *b_B_Hlt2Topo4BodyBBDTDecision_TOS;   //!
   TBranch        *b_B_Hlt2Topo4BodySimpleDecision_Dec;   //!
   TBranch        *b_B_Hlt2Topo4BodySimpleDecision_TIS;   //!
   TBranch        *b_B_Hlt2Topo4BodySimpleDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonBDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonBDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonBDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedHeavyDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedHeavyDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedHeavyDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedJPsiDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedJPsiDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedJPsiDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedPsi2SDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedPsi2SDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedPsi2SDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonJPsiDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonJPsiDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonJPsiDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonJPsiHighPTDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonJPsiHighPTDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonJPsiHighPTDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonPsi2SDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonPsi2SDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonPsi2SDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonPsi2SHighPTDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonPsi2SHighPTDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonPsi2SHighPTDecision_TOS;   //!
   TBranch        *b_B_Hlt2LowMultMuonDecision_Dec;   //!
   TBranch        *b_B_Hlt2LowMultMuonDecision_TIS;   //!
   TBranch        *b_B_Hlt2LowMultMuonDecision_TOS;   //!
   TBranch        *b_B_Hlt2MuonFromHLT1Decision_Dec;   //!
   TBranch        *b_B_Hlt2MuonFromHLT1Decision_TIS;   //!
   TBranch        *b_B_Hlt2MuonFromHLT1Decision_TOS;   //!
   TBranch        *b_B_Hlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_B_Hlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_B_Hlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_B_Hlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_B_Hlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_B_Hlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_B_Hlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_B_Hlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_B_Hlt2SingleMuonLowPTDecision_TOS;   //!
   TBranch        *b_B_Hlt2SingleMuonVHighPTDecision_Dec;   //!
   TBranch        *b_B_Hlt2SingleMuonVHighPTDecision_TIS;   //!
   TBranch        *b_B_Hlt2SingleMuonVHighPTDecision_TOS;   //!
   TBranch        *b_B_Hlt2TopoMu2BodyBBDTDecision_Dec;   //!
   TBranch        *b_B_Hlt2TopoMu2BodyBBDTDecision_TIS;   //!
   TBranch        *b_B_Hlt2TopoMu2BodyBBDTDecision_TOS;   //!
   TBranch        *b_B_Hlt2TopoMu3BodyBBDTDecision_Dec;   //!
   TBranch        *b_B_Hlt2TopoMu3BodyBBDTDecision_TIS;   //!
   TBranch        *b_B_Hlt2TopoMu3BodyBBDTDecision_TOS;   //!
   TBranch        *b_B_Hlt2TopoMu4BodyBBDTDecision_Dec;   //!
   TBranch        *b_B_Hlt2TopoMu4BodyBBDTDecision_TIS;   //!
   TBranch        *b_B_Hlt2TopoMu4BodyBBDTDecision_TOS;   //!
   TBranch        *b_B_Hlt2diPhotonDiMuonDecision_Dec;   //!
   TBranch        *b_B_Hlt2diPhotonDiMuonDecision_TIS;   //!
   TBranch        *b_B_Hlt2diPhotonDiMuonDecision_TOS;   //!
   TBranch        *b_Lambda0_MINIP;   //!
   TBranch        *b_Lambda0_MINIPCHI2;   //!
   TBranch        *b_Lambda0_MINIPNEXTBEST;   //!
   TBranch        *b_Lambda0_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_Lambda0_AllIP;   //!
   TBranch        *b_Lambda0_AllIPchi2;   //!
   TBranch        *b_Lambda0_ENDVERTEX_X;   //!
   TBranch        *b_Lambda0_ENDVERTEX_Y;   //!
   TBranch        *b_Lambda0_ENDVERTEX_Z;   //!
   TBranch        *b_Lambda0_ENDVERTEX_XERR;   //!
   TBranch        *b_Lambda0_ENDVERTEX_YERR;   //!
   TBranch        *b_Lambda0_ENDVERTEX_ZERR;   //!
   TBranch        *b_Lambda0_ENDVERTEX_CHI2;   //!
   TBranch        *b_Lambda0_ENDVERTEX_NDOF;   //!
   TBranch        *b_Lambda0_ENDVERTEX_COV_;   //!
   TBranch        *b_Lambda0_OWNPV_X;   //!
   TBranch        *b_Lambda0_OWNPV_Y;   //!
   TBranch        *b_Lambda0_OWNPV_Z;   //!
   TBranch        *b_Lambda0_OWNPV_XERR;   //!
   TBranch        *b_Lambda0_OWNPV_YERR;   //!
   TBranch        *b_Lambda0_OWNPV_ZERR;   //!
   TBranch        *b_Lambda0_OWNPV_CHI2;   //!
   TBranch        *b_Lambda0_OWNPV_NDOF;   //!
   TBranch        *b_Lambda0_OWNPV_COV_;   //!
   TBranch        *b_Lambda0_IP_OWNPV;   //!
   TBranch        *b_Lambda0_IPCHI2_OWNPV;   //!
   TBranch        *b_Lambda0_FD_OWNPV;   //!
   TBranch        *b_Lambda0_FDCHI2_OWNPV;   //!
   TBranch        *b_Lambda0_DIRA_OWNPV;   //!
   TBranch        *b_Lambda0_TOPPV_X;   //!
   TBranch        *b_Lambda0_TOPPV_Y;   //!
   TBranch        *b_Lambda0_TOPPV_Z;   //!
   TBranch        *b_Lambda0_TOPPV_XERR;   //!
   TBranch        *b_Lambda0_TOPPV_YERR;   //!
   TBranch        *b_Lambda0_TOPPV_ZERR;   //!
   TBranch        *b_Lambda0_TOPPV_CHI2;   //!
   TBranch        *b_Lambda0_TOPPV_NDOF;   //!
   TBranch        *b_Lambda0_TOPPV_COV_;   //!
   TBranch        *b_Lambda0_IP_TOPPV;   //!
   TBranch        *b_Lambda0_IPCHI2_TOPPV;   //!
   TBranch        *b_Lambda0_FD_TOPPV;   //!
   TBranch        *b_Lambda0_FDCHI2_TOPPV;   //!
   TBranch        *b_Lambda0_DIRA_TOPPV;   //!
   TBranch        *b_Lambda0_ORIVX_X;   //!
   TBranch        *b_Lambda0_ORIVX_Y;   //!
   TBranch        *b_Lambda0_ORIVX_Z;   //!
   TBranch        *b_Lambda0_ORIVX_XERR;   //!
   TBranch        *b_Lambda0_ORIVX_YERR;   //!
   TBranch        *b_Lambda0_ORIVX_ZERR;   //!
   TBranch        *b_Lambda0_ORIVX_CHI2;   //!
   TBranch        *b_Lambda0_ORIVX_NDOF;   //!
   TBranch        *b_Lambda0_ORIVX_COV_;   //!
   TBranch        *b_Lambda0_IP_ORIVX;   //!
   TBranch        *b_Lambda0_IPCHI2_ORIVX;   //!
   TBranch        *b_Lambda0_FD_ORIVX;   //!
   TBranch        *b_Lambda0_FDCHI2_ORIVX;   //!
   TBranch        *b_Lambda0_DIRA_ORIVX;   //!
   TBranch        *b_Lambda0_P;   //!
   TBranch        *b_Lambda0_PT;   //!
   TBranch        *b_Lambda0_PE;   //!
   TBranch        *b_Lambda0_PX;   //!
   TBranch        *b_Lambda0_PY;   //!
   TBranch        *b_Lambda0_PZ;   //!
   TBranch        *b_Lambda0_REFPX;   //!
   TBranch        *b_Lambda0_REFPY;   //!
   TBranch        *b_Lambda0_REFPZ;   //!
   TBranch        *b_Lambda0_MM;   //!
   TBranch        *b_Lambda0_MMERR;   //!
   TBranch        *b_Lambda0_M;   //!
   TBranch        *b_Lambda0_M_with_pplus_piplus;   //!
   TBranch        *b_Lambda0_M_with_piplus_piplus;   //!
   TBranch        *b_Lambda0_ID;   //!
   TBranch        *b_Lambda0_TAU;   //!
   TBranch        *b_Lambda0_TAUERR;   //!
   TBranch        *b_Lambda0_TAUCHI2;   //!
   TBranch        *b_piminus_MINIP;   //!
   TBranch        *b_piminus_MINIPCHI2;   //!
   TBranch        *b_piminus_MINIPNEXTBEST;   //!
   TBranch        *b_piminus_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_piminus_AllIP;   //!
   TBranch        *b_piminus_AllIPchi2;   //!
   TBranch        *b_piminus_OWNPV_X;   //!
   TBranch        *b_piminus_OWNPV_Y;   //!
   TBranch        *b_piminus_OWNPV_Z;   //!
   TBranch        *b_piminus_OWNPV_XERR;   //!
   TBranch        *b_piminus_OWNPV_YERR;   //!
   TBranch        *b_piminus_OWNPV_ZERR;   //!
   TBranch        *b_piminus_OWNPV_CHI2;   //!
   TBranch        *b_piminus_OWNPV_NDOF;   //!
   TBranch        *b_piminus_OWNPV_COV_;   //!
   TBranch        *b_piminus_IP_OWNPV;   //!
   TBranch        *b_piminus_IPCHI2_OWNPV;   //!
   TBranch        *b_piminus_TOPPV_X;   //!
   TBranch        *b_piminus_TOPPV_Y;   //!
   TBranch        *b_piminus_TOPPV_Z;   //!
   TBranch        *b_piminus_TOPPV_XERR;   //!
   TBranch        *b_piminus_TOPPV_YERR;   //!
   TBranch        *b_piminus_TOPPV_ZERR;   //!
   TBranch        *b_piminus_TOPPV_CHI2;   //!
   TBranch        *b_piminus_TOPPV_NDOF;   //!
   TBranch        *b_piminus_TOPPV_COV_;   //!
   TBranch        *b_piminus_IP_TOPPV;   //!
   TBranch        *b_piminus_IPCHI2_TOPPV;   //!
   TBranch        *b_piminus_ORIVX_X;   //!
   TBranch        *b_piminus_ORIVX_Y;   //!
   TBranch        *b_piminus_ORIVX_Z;   //!
   TBranch        *b_piminus_ORIVX_XERR;   //!
   TBranch        *b_piminus_ORIVX_YERR;   //!
   TBranch        *b_piminus_ORIVX_ZERR;   //!
   TBranch        *b_piminus_ORIVX_CHI2;   //!
   TBranch        *b_piminus_ORIVX_NDOF;   //!
   TBranch        *b_piminus_ORIVX_COV_;   //!
   TBranch        *b_piminus_IP_ORIVX;   //!
   TBranch        *b_piminus_IPCHI2_ORIVX;   //!
   TBranch        *b_piminus_P;   //!
   TBranch        *b_piminus_PT;   //!
   TBranch        *b_piminus_PE;   //!
   TBranch        *b_piminus_PX;   //!
   TBranch        *b_piminus_PY;   //!
   TBranch        *b_piminus_PZ;   //!
   TBranch        *b_piminus_REFPX;   //!
   TBranch        *b_piminus_REFPY;   //!
   TBranch        *b_piminus_REFPZ;   //!
   TBranch        *b_piminus_M;   //!
   TBranch        *b_piminus_AtVtx_PE;   //!
   TBranch        *b_piminus_AtVtx_PX;   //!
   TBranch        *b_piminus_AtVtx_PY;   //!
   TBranch        *b_piminus_AtVtx_PZ;   //!
   TBranch        *b_piminus_L0Calo_HCAL_realET;   //!
   TBranch        *b_piminus_L0Calo_HCAL_xProjection;   //!
   TBranch        *b_piminus_L0Calo_HCAL_yProjection;   //!
   TBranch        *b_piminus_L0Calo_HCAL_region;   //!
   TBranch        *b_piminus_ID;   //!
   TBranch        *b_piminus_PIDe;   //!
   TBranch        *b_piminus_PIDmu;   //!
   TBranch        *b_piminus_PIDK;   //!
   TBranch        *b_piminus_PIDp;   //!
   TBranch        *b_piminus_ProbNNe;   //!
   TBranch        *b_piminus_ProbNNk;   //!
   TBranch        *b_piminus_ProbNNp;   //!
   TBranch        *b_piminus_ProbNNpi;   //!
   TBranch        *b_piminus_ProbNNmu;   //!
   TBranch        *b_piminus_ProbNNghost;   //!
   TBranch        *b_piminus_hasMuon;   //!
   TBranch        *b_piminus_isMuon;   //!
   TBranch        *b_piminus_hasRich;   //!
   TBranch        *b_piminus_hasCalo;   //!
   TBranch        *b_piminus_UsedRichAerogel;   //!
   TBranch        *b_piminus_UsedRich1Gas;   //!
   TBranch        *b_piminus_UsedRich2Gas;   //!
   TBranch        *b_piminus_RichAboveElThres;   //!
   TBranch        *b_piminus_RichAboveMuThres;   //!
   TBranch        *b_piminus_RichAbovePiThres;   //!
   TBranch        *b_piminus_RichAboveKaThres;   //!
   TBranch        *b_piminus_RichAbovePrThres;   //!
   TBranch        *b_piminus_RichDLLe;   //!
   TBranch        *b_piminus_RichDLLmu;   //!
   TBranch        *b_piminus_RichDLLpi;   //!
   TBranch        *b_piminus_RichDLLk;   //!
   TBranch        *b_piminus_RichDLLp;   //!
   TBranch        *b_piminus_RichDLLbt;   //!
   TBranch        *b_piminus_InAccMuon;   //!
   TBranch        *b_piminus_isMuonLoose;   //!
   TBranch        *b_piminus_MuonMuLL;   //!
   TBranch        *b_piminus_MuonBkgLL;   //!
   TBranch        *b_piminus_MuonNShared;   //!
   TBranch        *b_piminus_InAccEcal;   //!
   TBranch        *b_piminus_CaloEcalE;   //!
   TBranch        *b_piminus_EcalPIDe;   //!
   TBranch        *b_piminus_EcalPIDmu;   //!
   TBranch        *b_piminus_InAccHcal;   //!
   TBranch        *b_piminus_CaloHcalE;   //!
   TBranch        *b_piminus_HcalPIDe;   //!
   TBranch        *b_piminus_HcalPIDmu;   //!
   TBranch        *b_piminus_InAccPrs;   //!
   TBranch        *b_piminus_PrsPIDe;   //!
   TBranch        *b_piminus_CaloPrsE;   //!
   TBranch        *b_piminus_InAccSpd;   //!
   TBranch        *b_piminus_CaloSpdE;   //!
   TBranch        *b_piminus_InAccBrem;   //!
   TBranch        *b_piminus_BremPIDe;   //!
   TBranch        *b_piminus_VeloCharge;   //!
   TBranch        *b_piminus_TRACK_Type;   //!
   TBranch        *b_piminus_TRACK_Key;   //!
   TBranch        *b_piminus_TRACK_CHI2;   //!
   TBranch        *b_piminus_TRACK_NDOF;   //!
   TBranch        *b_piminus_TRACK_CHI2NDOF;   //!
   TBranch        *b_piminus_TRACK_PCHI2;   //!
   TBranch        *b_piminus_TRACK_VeloCHI2NDOF;   //!
   TBranch        *b_piminus_TRACK_TCHI2NDOF;   //!
   TBranch        *b_piminus_VELO_UTID;   //!
   TBranch        *b_piminus_TRACK_FirstMeasurementX;   //!
   TBranch        *b_piminus_TRACK_FirstMeasurementY;   //!
   TBranch        *b_piminus_TRACK_FirstMeasurementZ;   //!
   TBranch        *b_piminus_TRACK_MatchCHI2;   //!
   TBranch        *b_piminus_TRACK_GhostProb;   //!
   TBranch        *b_piminus_TRACK_CloneDist;   //!
   TBranch        *b_piminus_TRACK_Likelihood;   //!
   TBranch        *b_pplus_MINIP;   //!
   TBranch        *b_pplus_MINIPCHI2;   //!
   TBranch        *b_pplus_MINIPNEXTBEST;   //!
   TBranch        *b_pplus_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_pplus_AllIP;   //!
   TBranch        *b_pplus_AllIPchi2;   //!
   TBranch        *b_pplus_OWNPV_X;   //!
   TBranch        *b_pplus_OWNPV_Y;   //!
   TBranch        *b_pplus_OWNPV_Z;   //!
   TBranch        *b_pplus_OWNPV_XERR;   //!
   TBranch        *b_pplus_OWNPV_YERR;   //!
   TBranch        *b_pplus_OWNPV_ZERR;   //!
   TBranch        *b_pplus_OWNPV_CHI2;   //!
   TBranch        *b_pplus_OWNPV_NDOF;   //!
   TBranch        *b_pplus_OWNPV_COV_;   //!
   TBranch        *b_pplus_IP_OWNPV;   //!
   TBranch        *b_pplus_IPCHI2_OWNPV;   //!
   TBranch        *b_pplus_TOPPV_X;   //!
   TBranch        *b_pplus_TOPPV_Y;   //!
   TBranch        *b_pplus_TOPPV_Z;   //!
   TBranch        *b_pplus_TOPPV_XERR;   //!
   TBranch        *b_pplus_TOPPV_YERR;   //!
   TBranch        *b_pplus_TOPPV_ZERR;   //!
   TBranch        *b_pplus_TOPPV_CHI2;   //!
   TBranch        *b_pplus_TOPPV_NDOF;   //!
   TBranch        *b_pplus_TOPPV_COV_;   //!
   TBranch        *b_pplus_IP_TOPPV;   //!
   TBranch        *b_pplus_IPCHI2_TOPPV;   //!
   TBranch        *b_pplus_ORIVX_X;   //!
   TBranch        *b_pplus_ORIVX_Y;   //!
   TBranch        *b_pplus_ORIVX_Z;   //!
   TBranch        *b_pplus_ORIVX_XERR;   //!
   TBranch        *b_pplus_ORIVX_YERR;   //!
   TBranch        *b_pplus_ORIVX_ZERR;   //!
   TBranch        *b_pplus_ORIVX_CHI2;   //!
   TBranch        *b_pplus_ORIVX_NDOF;   //!
   TBranch        *b_pplus_ORIVX_COV_;   //!
   TBranch        *b_pplus_IP_ORIVX;   //!
   TBranch        *b_pplus_IPCHI2_ORIVX;   //!
   TBranch        *b_pplus_P;   //!
   TBranch        *b_pplus_PT;   //!
   TBranch        *b_pplus_PE;   //!
   TBranch        *b_pplus_PX;   //!
   TBranch        *b_pplus_PY;   //!
   TBranch        *b_pplus_PZ;   //!
   TBranch        *b_pplus_REFPX;   //!
   TBranch        *b_pplus_REFPY;   //!
   TBranch        *b_pplus_REFPZ;   //!
   TBranch        *b_pplus_M;   //!
   TBranch        *b_pplus_AtVtx_PE;   //!
   TBranch        *b_pplus_AtVtx_PX;   //!
   TBranch        *b_pplus_AtVtx_PY;   //!
   TBranch        *b_pplus_AtVtx_PZ;   //!
   TBranch        *b_pplus_L0Calo_HCAL_realET;   //!
   TBranch        *b_pplus_L0Calo_HCAL_xProjection;   //!
   TBranch        *b_pplus_L0Calo_HCAL_yProjection;   //!
   TBranch        *b_pplus_L0Calo_HCAL_region;   //!
   TBranch        *b_pplus_ID;   //!
   TBranch        *b_pplus_PIDe;   //!
   TBranch        *b_pplus_PIDmu;   //!
   TBranch        *b_pplus_PIDK;   //!
   TBranch        *b_pplus_PIDp;   //!
   TBranch        *b_pplus_ProbNNe;   //!
   TBranch        *b_pplus_ProbNNk;   //!
   TBranch        *b_pplus_ProbNNp;   //!
   TBranch        *b_pplus_ProbNNpi;   //!
   TBranch        *b_pplus_ProbNNmu;   //!
   TBranch        *b_pplus_ProbNNghost;   //!
   TBranch        *b_pplus_hasMuon;   //!
   TBranch        *b_pplus_isMuon;   //!
   TBranch        *b_pplus_hasRich;   //!
   TBranch        *b_pplus_hasCalo;   //!
   TBranch        *b_pplus_UsedRichAerogel;   //!
   TBranch        *b_pplus_UsedRich1Gas;   //!
   TBranch        *b_pplus_UsedRich2Gas;   //!
   TBranch        *b_pplus_RichAboveElThres;   //!
   TBranch        *b_pplus_RichAboveMuThres;   //!
   TBranch        *b_pplus_RichAbovePiThres;   //!
   TBranch        *b_pplus_RichAboveKaThres;   //!
   TBranch        *b_pplus_RichAbovePrThres;   //!
   TBranch        *b_pplus_RichDLLe;   //!
   TBranch        *b_pplus_RichDLLmu;   //!
   TBranch        *b_pplus_RichDLLpi;   //!
   TBranch        *b_pplus_RichDLLk;   //!
   TBranch        *b_pplus_RichDLLp;   //!
   TBranch        *b_pplus_RichDLLbt;   //!
   TBranch        *b_pplus_InAccMuon;   //!
   TBranch        *b_pplus_isMuonLoose;   //!
   TBranch        *b_pplus_MuonMuLL;   //!
   TBranch        *b_pplus_MuonBkgLL;   //!
   TBranch        *b_pplus_MuonNShared;   //!
   TBranch        *b_pplus_InAccEcal;   //!
   TBranch        *b_pplus_CaloEcalE;   //!
   TBranch        *b_pplus_EcalPIDe;   //!
   TBranch        *b_pplus_EcalPIDmu;   //!
   TBranch        *b_pplus_InAccHcal;   //!
   TBranch        *b_pplus_CaloHcalE;   //!
   TBranch        *b_pplus_HcalPIDe;   //!
   TBranch        *b_pplus_HcalPIDmu;   //!
   TBranch        *b_pplus_InAccPrs;   //!
   TBranch        *b_pplus_PrsPIDe;   //!
   TBranch        *b_pplus_CaloPrsE;   //!
   TBranch        *b_pplus_InAccSpd;   //!
   TBranch        *b_pplus_CaloSpdE;   //!
   TBranch        *b_pplus_InAccBrem;   //!
   TBranch        *b_pplus_BremPIDe;   //!
   TBranch        *b_pplus_VeloCharge;   //!
   TBranch        *b_pplus_TRACK_Type;   //!
   TBranch        *b_pplus_TRACK_Key;   //!
   TBranch        *b_pplus_TRACK_CHI2;   //!
   TBranch        *b_pplus_TRACK_NDOF;   //!
   TBranch        *b_pplus_TRACK_CHI2NDOF;   //!
   TBranch        *b_pplus_TRACK_PCHI2;   //!
   TBranch        *b_pplus_TRACK_VeloCHI2NDOF;   //!
   TBranch        *b_pplus_TRACK_TCHI2NDOF;   //!
   TBranch        *b_pplus_VELO_UTID;   //!
   TBranch        *b_pplus_TRACK_FirstMeasurementX;   //!
   TBranch        *b_pplus_TRACK_FirstMeasurementY;   //!
   TBranch        *b_pplus_TRACK_FirstMeasurementZ;   //!
   TBranch        *b_pplus_TRACK_MatchCHI2;   //!
   TBranch        *b_pplus_TRACK_GhostProb;   //!
   TBranch        *b_pplus_TRACK_CloneDist;   //!
   TBranch        *b_pplus_TRACK_Likelihood;   //!
   TBranch        *b_Psi_MINIP;   //!
   TBranch        *b_Psi_MINIPCHI2;   //!
   TBranch        *b_Psi_MINIPNEXTBEST;   //!
   TBranch        *b_Psi_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_Psi_AllIP;   //!
   TBranch        *b_Psi_AllIPchi2;   //!
   TBranch        *b_Psi_ENDVERTEX_X;   //!
   TBranch        *b_Psi_ENDVERTEX_Y;   //!
   TBranch        *b_Psi_ENDVERTEX_Z;   //!
   TBranch        *b_Psi_ENDVERTEX_XERR;   //!
   TBranch        *b_Psi_ENDVERTEX_YERR;   //!
   TBranch        *b_Psi_ENDVERTEX_ZERR;   //!
   TBranch        *b_Psi_ENDVERTEX_CHI2;   //!
   TBranch        *b_Psi_ENDVERTEX_NDOF;   //!
   TBranch        *b_Psi_ENDVERTEX_COV_;   //!
   TBranch        *b_Psi_OWNPV_X;   //!
   TBranch        *b_Psi_OWNPV_Y;   //!
   TBranch        *b_Psi_OWNPV_Z;   //!
   TBranch        *b_Psi_OWNPV_XERR;   //!
   TBranch        *b_Psi_OWNPV_YERR;   //!
   TBranch        *b_Psi_OWNPV_ZERR;   //!
   TBranch        *b_Psi_OWNPV_CHI2;   //!
   TBranch        *b_Psi_OWNPV_NDOF;   //!
   TBranch        *b_Psi_OWNPV_COV_;   //!
   TBranch        *b_Psi_IP_OWNPV;   //!
   TBranch        *b_Psi_IPCHI2_OWNPV;   //!
   TBranch        *b_Psi_FD_OWNPV;   //!
   TBranch        *b_Psi_FDCHI2_OWNPV;   //!
   TBranch        *b_Psi_DIRA_OWNPV;   //!
   TBranch        *b_Psi_TOPPV_X;   //!
   TBranch        *b_Psi_TOPPV_Y;   //!
   TBranch        *b_Psi_TOPPV_Z;   //!
   TBranch        *b_Psi_TOPPV_XERR;   //!
   TBranch        *b_Psi_TOPPV_YERR;   //!
   TBranch        *b_Psi_TOPPV_ZERR;   //!
   TBranch        *b_Psi_TOPPV_CHI2;   //!
   TBranch        *b_Psi_TOPPV_NDOF;   //!
   TBranch        *b_Psi_TOPPV_COV_;   //!
   TBranch        *b_Psi_IP_TOPPV;   //!
   TBranch        *b_Psi_IPCHI2_TOPPV;   //!
   TBranch        *b_Psi_FD_TOPPV;   //!
   TBranch        *b_Psi_FDCHI2_TOPPV;   //!
   TBranch        *b_Psi_DIRA_TOPPV;   //!
   TBranch        *b_Psi_ORIVX_X;   //!
   TBranch        *b_Psi_ORIVX_Y;   //!
   TBranch        *b_Psi_ORIVX_Z;   //!
   TBranch        *b_Psi_ORIVX_XERR;   //!
   TBranch        *b_Psi_ORIVX_YERR;   //!
   TBranch        *b_Psi_ORIVX_ZERR;   //!
   TBranch        *b_Psi_ORIVX_CHI2;   //!
   TBranch        *b_Psi_ORIVX_NDOF;   //!
   TBranch        *b_Psi_ORIVX_COV_;   //!
   TBranch        *b_Psi_IP_ORIVX;   //!
   TBranch        *b_Psi_IPCHI2_ORIVX;   //!
   TBranch        *b_Psi_FD_ORIVX;   //!
   TBranch        *b_Psi_FDCHI2_ORIVX;   //!
   TBranch        *b_Psi_DIRA_ORIVX;   //!
   TBranch        *b_Psi_P;   //!
   TBranch        *b_Psi_PT;   //!
   TBranch        *b_Psi_PE;   //!
   TBranch        *b_Psi_PX;   //!
   TBranch        *b_Psi_PY;   //!
   TBranch        *b_Psi_PZ;   //!
   TBranch        *b_Psi_REFPX;   //!
   TBranch        *b_Psi_REFPY;   //!
   TBranch        *b_Psi_REFPZ;   //!
   TBranch        *b_Psi_MM;   //!
   TBranch        *b_Psi_MMERR;   //!
   TBranch        *b_Psi_M;   //!
   TBranch        *b_Psi_ID;   //!
   TBranch        *b_Psi_TAU;   //!
   TBranch        *b_Psi_TAUERR;   //!
   TBranch        *b_Psi_TAUCHI2;   //!
   TBranch        *b_Psi_L0Global_Dec;   //!
   TBranch        *b_Psi_L0Global_TIS;   //!
   TBranch        *b_Psi_L0Global_TOS;   //!
   TBranch        *b_Psi_Hlt1Global_Dec;   //!
   TBranch        *b_Psi_Hlt1Global_TIS;   //!
   TBranch        *b_Psi_Hlt1Global_TOS;   //!
   TBranch        *b_Psi_Hlt1Phys_Dec;   //!
   TBranch        *b_Psi_Hlt1Phys_TIS;   //!
   TBranch        *b_Psi_Hlt1Phys_TOS;   //!
   TBranch        *b_Psi_Hlt2Global_Dec;   //!
   TBranch        *b_Psi_Hlt2Global_TIS;   //!
   TBranch        *b_Psi_Hlt2Global_TOS;   //!
   TBranch        *b_Psi_Hlt2Phys_Dec;   //!
   TBranch        *b_Psi_Hlt2Phys_TIS;   //!
   TBranch        *b_Psi_Hlt2Phys_TOS;   //!
   TBranch        *b_Psi_StrippingGlobal_Dec;   //!
   TBranch        *b_Psi_StrippingGlobal_TIS;   //!
   TBranch        *b_Psi_StrippingGlobal_TOS;   //!
   TBranch        *b_Psi_L0HadronDecision_Dec;   //!
   TBranch        *b_Psi_L0HadronDecision_TIS;   //!
   TBranch        *b_Psi_L0HadronDecision_TOS;   //!
   TBranch        *b_Psi_L0MuonDecision_Dec;   //!
   TBranch        *b_Psi_L0MuonDecision_TIS;   //!
   TBranch        *b_Psi_L0MuonDecision_TOS;   //!
   TBranch        *b_Psi_L0DiMuonDecision_Dec;   //!
   TBranch        *b_Psi_L0DiMuonDecision_TIS;   //!
   TBranch        *b_Psi_L0DiMuonDecision_TOS;   //!
   TBranch        *b_Psi_L0ElectronDecision_Dec;   //!
   TBranch        *b_Psi_L0ElectronDecision_TIS;   //!
   TBranch        *b_Psi_L0ElectronDecision_TOS;   //!
   TBranch        *b_Psi_L0PhotonDecision_Dec;   //!
   TBranch        *b_Psi_L0PhotonDecision_TIS;   //!
   TBranch        *b_Psi_L0PhotonDecision_TOS;   //!
   TBranch        *b_Psi_Hlt1TrackAllL0Decision_Dec;   //!
   TBranch        *b_Psi_Hlt1TrackAllL0Decision_TIS;   //!
   TBranch        *b_Psi_Hlt1TrackAllL0Decision_TOS;   //!
   TBranch        *b_Psi_Hlt1TrackAllL0TightDecision_Dec;   //!
   TBranch        *b_Psi_Hlt1TrackAllL0TightDecision_TIS;   //!
   TBranch        *b_Psi_Hlt1TrackAllL0TightDecision_TOS;   //!
   TBranch        *b_Psi_Hlt1DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_Psi_Hlt1DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_Psi_Hlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_Psi_Hlt1DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_Psi_Hlt1DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_Psi_Hlt1DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_Psi_Hlt1SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_Psi_Hlt1SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_Psi_Hlt1SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_Psi_Hlt1SingleMuonNoIPDecision_Dec;   //!
   TBranch        *b_Psi_Hlt1SingleMuonNoIPDecision_TIS;   //!
   TBranch        *b_Psi_Hlt1SingleMuonNoIPDecision_TOS;   //!
   TBranch        *b_Psi_Hlt1TrackMuonDecision_Dec;   //!
   TBranch        *b_Psi_Hlt1TrackMuonDecision_TIS;   //!
   TBranch        *b_Psi_Hlt1TrackMuonDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2Topo2BodyBBDTDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2Topo2BodyBBDTDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2Topo2BodyBBDTDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2Topo2BodySimpleDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2Topo2BodySimpleDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2Topo2BodySimpleDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2Topo3BodyBBDTDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2Topo3BodyBBDTDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2Topo3BodyBBDTDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2Topo3BodySimpleDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2Topo3BodySimpleDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2Topo3BodySimpleDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2Topo4BodyBBDTDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2Topo4BodyBBDTDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2Topo4BodyBBDTDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2Topo4BodySimpleDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2Topo4BodySimpleDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2Topo4BodySimpleDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2DiMuonDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2DiMuonDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2DiMuonDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2DiMuonBDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2DiMuonBDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2DiMuonBDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2DiMuonDetachedDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2DiMuonDetachedDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2DiMuonDetachedDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2DiMuonDetachedHeavyDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2DiMuonDetachedHeavyDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2DiMuonDetachedHeavyDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2DiMuonDetachedJPsiDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2DiMuonDetachedJPsiDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2DiMuonDetachedJPsiDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2DiMuonDetachedPsi2SDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2DiMuonDetachedPsi2SDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2DiMuonDetachedPsi2SDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2DiMuonJPsiDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2DiMuonJPsiDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2DiMuonJPsiDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2DiMuonJPsiHighPTDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2DiMuonJPsiHighPTDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2DiMuonJPsiHighPTDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2DiMuonPsi2SDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2DiMuonPsi2SDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2DiMuonPsi2SDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2DiMuonPsi2SHighPTDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2DiMuonPsi2SHighPTDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2DiMuonPsi2SHighPTDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2LowMultMuonDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2LowMultMuonDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2LowMultMuonDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2MuonFromHLT1Decision_Dec;   //!
   TBranch        *b_Psi_Hlt2MuonFromHLT1Decision_TIS;   //!
   TBranch        *b_Psi_Hlt2MuonFromHLT1Decision_TOS;   //!
   TBranch        *b_Psi_Hlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2SingleMuonLowPTDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2SingleMuonVHighPTDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2SingleMuonVHighPTDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2SingleMuonVHighPTDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2TopoMu2BodyBBDTDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2TopoMu2BodyBBDTDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2TopoMu2BodyBBDTDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2TopoMu3BodyBBDTDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2TopoMu3BodyBBDTDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2TopoMu3BodyBBDTDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2TopoMu4BodyBBDTDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2TopoMu4BodyBBDTDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2TopoMu4BodyBBDTDecision_TOS;   //!
   TBranch        *b_Psi_Hlt2diPhotonDiMuonDecision_Dec;   //!
   TBranch        *b_Psi_Hlt2diPhotonDiMuonDecision_TIS;   //!
   TBranch        *b_Psi_Hlt2diPhotonDiMuonDecision_TOS;   //!
   TBranch        *b_Psi_NOPARTWITHINDCHI2WDW;   //!
   TBranch        *b_Psi_NOPARTWITHINCHI2WDW;   //!
   TBranch        *b_Psi_SMALLESTCHI2;   //!
   TBranch        *b_Psi_SMALLESTDELTACHI2;   //!
   TBranch        *b_muminus_MINIP;   //!
   TBranch        *b_muminus_MINIPCHI2;   //!
   TBranch        *b_muminus_MINIPNEXTBEST;   //!
   TBranch        *b_muminus_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_muminus_AllIP;   //!
   TBranch        *b_muminus_AllIPchi2;   //!
   TBranch        *b_muminus_OWNPV_X;   //!
   TBranch        *b_muminus_OWNPV_Y;   //!
   TBranch        *b_muminus_OWNPV_Z;   //!
   TBranch        *b_muminus_OWNPV_XERR;   //!
   TBranch        *b_muminus_OWNPV_YERR;   //!
   TBranch        *b_muminus_OWNPV_ZERR;   //!
   TBranch        *b_muminus_OWNPV_CHI2;   //!
   TBranch        *b_muminus_OWNPV_NDOF;   //!
   TBranch        *b_muminus_OWNPV_COV_;   //!
   TBranch        *b_muminus_IP_OWNPV;   //!
   TBranch        *b_muminus_IPCHI2_OWNPV;   //!
   TBranch        *b_muminus_TOPPV_X;   //!
   TBranch        *b_muminus_TOPPV_Y;   //!
   TBranch        *b_muminus_TOPPV_Z;   //!
   TBranch        *b_muminus_TOPPV_XERR;   //!
   TBranch        *b_muminus_TOPPV_YERR;   //!
   TBranch        *b_muminus_TOPPV_ZERR;   //!
   TBranch        *b_muminus_TOPPV_CHI2;   //!
   TBranch        *b_muminus_TOPPV_NDOF;   //!
   TBranch        *b_muminus_TOPPV_COV_;   //!
   TBranch        *b_muminus_IP_TOPPV;   //!
   TBranch        *b_muminus_IPCHI2_TOPPV;   //!
   TBranch        *b_muminus_ORIVX_X;   //!
   TBranch        *b_muminus_ORIVX_Y;   //!
   TBranch        *b_muminus_ORIVX_Z;   //!
   TBranch        *b_muminus_ORIVX_XERR;   //!
   TBranch        *b_muminus_ORIVX_YERR;   //!
   TBranch        *b_muminus_ORIVX_ZERR;   //!
   TBranch        *b_muminus_ORIVX_CHI2;   //!
   TBranch        *b_muminus_ORIVX_NDOF;   //!
   TBranch        *b_muminus_ORIVX_COV_;   //!
   TBranch        *b_muminus_IP_ORIVX;   //!
   TBranch        *b_muminus_IPCHI2_ORIVX;   //!
   TBranch        *b_muminus_P;   //!
   TBranch        *b_muminus_PT;   //!
   TBranch        *b_muminus_PE;   //!
   TBranch        *b_muminus_PX;   //!
   TBranch        *b_muminus_PY;   //!
   TBranch        *b_muminus_PZ;   //!
   TBranch        *b_muminus_REFPX;   //!
   TBranch        *b_muminus_REFPY;   //!
   TBranch        *b_muminus_REFPZ;   //!
   TBranch        *b_muminus_M;   //!
   TBranch        *b_muminus_AtVtx_PE;   //!
   TBranch        *b_muminus_AtVtx_PX;   //!
   TBranch        *b_muminus_AtVtx_PY;   //!
   TBranch        *b_muminus_AtVtx_PZ;   //!
   TBranch        *b_muminus_L0Calo_HCAL_realET;   //!
   TBranch        *b_muminus_L0Calo_HCAL_xProjection;   //!
   TBranch        *b_muminus_L0Calo_HCAL_yProjection;   //!
   TBranch        *b_muminus_L0Calo_HCAL_region;   //!
   TBranch        *b_muminus_ID;   //!
   TBranch        *b_muminus_PIDe;   //!
   TBranch        *b_muminus_PIDmu;   //!
   TBranch        *b_muminus_PIDK;   //!
   TBranch        *b_muminus_PIDp;   //!
   TBranch        *b_muminus_ProbNNe;   //!
   TBranch        *b_muminus_ProbNNk;   //!
   TBranch        *b_muminus_ProbNNp;   //!
   TBranch        *b_muminus_ProbNNpi;   //!
   TBranch        *b_muminus_ProbNNmu;   //!
   TBranch        *b_muminus_ProbNNghost;   //!
   TBranch        *b_muminus_hasMuon;   //!
   TBranch        *b_muminus_isMuon;   //!
   TBranch        *b_muminus_hasRich;   //!
   TBranch        *b_muminus_hasCalo;   //!
   TBranch        *b_muminus_UsedRichAerogel;   //!
   TBranch        *b_muminus_UsedRich1Gas;   //!
   TBranch        *b_muminus_UsedRich2Gas;   //!
   TBranch        *b_muminus_RichAboveElThres;   //!
   TBranch        *b_muminus_RichAboveMuThres;   //!
   TBranch        *b_muminus_RichAbovePiThres;   //!
   TBranch        *b_muminus_RichAboveKaThres;   //!
   TBranch        *b_muminus_RichAbovePrThres;   //!
   TBranch        *b_muminus_RichDLLe;   //!
   TBranch        *b_muminus_RichDLLmu;   //!
   TBranch        *b_muminus_RichDLLpi;   //!
   TBranch        *b_muminus_RichDLLk;   //!
   TBranch        *b_muminus_RichDLLp;   //!
   TBranch        *b_muminus_RichDLLbt;   //!
   TBranch        *b_muminus_InAccMuon;   //!
   TBranch        *b_muminus_isMuonLoose;   //!
   TBranch        *b_muminus_MuonMuLL;   //!
   TBranch        *b_muminus_MuonBkgLL;   //!
   TBranch        *b_muminus_MuonNShared;   //!
   TBranch        *b_muminus_InAccEcal;   //!
   TBranch        *b_muminus_CaloEcalE;   //!
   TBranch        *b_muminus_EcalPIDe;   //!
   TBranch        *b_muminus_EcalPIDmu;   //!
   TBranch        *b_muminus_InAccHcal;   //!
   TBranch        *b_muminus_CaloHcalE;   //!
   TBranch        *b_muminus_HcalPIDe;   //!
   TBranch        *b_muminus_HcalPIDmu;   //!
   TBranch        *b_muminus_InAccPrs;   //!
   TBranch        *b_muminus_PrsPIDe;   //!
   TBranch        *b_muminus_CaloPrsE;   //!
   TBranch        *b_muminus_InAccSpd;   //!
   TBranch        *b_muminus_CaloSpdE;   //!
   TBranch        *b_muminus_InAccBrem;   //!
   TBranch        *b_muminus_BremPIDe;   //!
   TBranch        *b_muminus_VeloCharge;   //!
   TBranch        *b_muminus_TRACK_Type;   //!
   TBranch        *b_muminus_TRACK_Key;   //!
   TBranch        *b_muminus_TRACK_CHI2;   //!
   TBranch        *b_muminus_TRACK_NDOF;   //!
   TBranch        *b_muminus_TRACK_CHI2NDOF;   //!
   TBranch        *b_muminus_TRACK_PCHI2;   //!
   TBranch        *b_muminus_TRACK_VeloCHI2NDOF;   //!
   TBranch        *b_muminus_TRACK_TCHI2NDOF;   //!
   TBranch        *b_muminus_VELO_UTID;   //!
   TBranch        *b_muminus_TRACK_FirstMeasurementX;   //!
   TBranch        *b_muminus_TRACK_FirstMeasurementY;   //!
   TBranch        *b_muminus_TRACK_FirstMeasurementZ;   //!
   TBranch        *b_muminus_TRACK_MatchCHI2;   //!
   TBranch        *b_muminus_TRACK_GhostProb;   //!
   TBranch        *b_muminus_TRACK_CloneDist;   //!
   TBranch        *b_muminus_TRACK_Likelihood;   //!
   TBranch        *b_muplus_MINIP;   //!
   TBranch        *b_muplus_MINIPCHI2;   //!
   TBranch        *b_muplus_MINIPNEXTBEST;   //!
   TBranch        *b_muplus_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_muplus_AllIP;   //!
   TBranch        *b_muplus_AllIPchi2;   //!
   TBranch        *b_muplus_OWNPV_X;   //!
   TBranch        *b_muplus_OWNPV_Y;   //!
   TBranch        *b_muplus_OWNPV_Z;   //!
   TBranch        *b_muplus_OWNPV_XERR;   //!
   TBranch        *b_muplus_OWNPV_YERR;   //!
   TBranch        *b_muplus_OWNPV_ZERR;   //!
   TBranch        *b_muplus_OWNPV_CHI2;   //!
   TBranch        *b_muplus_OWNPV_NDOF;   //!
   TBranch        *b_muplus_OWNPV_COV_;   //!
   TBranch        *b_muplus_IP_OWNPV;   //!
   TBranch        *b_muplus_IPCHI2_OWNPV;   //!
   TBranch        *b_muplus_TOPPV_X;   //!
   TBranch        *b_muplus_TOPPV_Y;   //!
   TBranch        *b_muplus_TOPPV_Z;   //!
   TBranch        *b_muplus_TOPPV_XERR;   //!
   TBranch        *b_muplus_TOPPV_YERR;   //!
   TBranch        *b_muplus_TOPPV_ZERR;   //!
   TBranch        *b_muplus_TOPPV_CHI2;   //!
   TBranch        *b_muplus_TOPPV_NDOF;   //!
   TBranch        *b_muplus_TOPPV_COV_;   //!
   TBranch        *b_muplus_IP_TOPPV;   //!
   TBranch        *b_muplus_IPCHI2_TOPPV;   //!
   TBranch        *b_muplus_ORIVX_X;   //!
   TBranch        *b_muplus_ORIVX_Y;   //!
   TBranch        *b_muplus_ORIVX_Z;   //!
   TBranch        *b_muplus_ORIVX_XERR;   //!
   TBranch        *b_muplus_ORIVX_YERR;   //!
   TBranch        *b_muplus_ORIVX_ZERR;   //!
   TBranch        *b_muplus_ORIVX_CHI2;   //!
   TBranch        *b_muplus_ORIVX_NDOF;   //!
   TBranch        *b_muplus_ORIVX_COV_;   //!
   TBranch        *b_muplus_IP_ORIVX;   //!
   TBranch        *b_muplus_IPCHI2_ORIVX;   //!
   TBranch        *b_muplus_P;   //!
   TBranch        *b_muplus_PT;   //!
   TBranch        *b_muplus_PE;   //!
   TBranch        *b_muplus_PX;   //!
   TBranch        *b_muplus_PY;   //!
   TBranch        *b_muplus_PZ;   //!
   TBranch        *b_muplus_REFPX;   //!
   TBranch        *b_muplus_REFPY;   //!
   TBranch        *b_muplus_REFPZ;   //!
   TBranch        *b_muplus_M;   //!
   TBranch        *b_muplus_AtVtx_PE;   //!
   TBranch        *b_muplus_AtVtx_PX;   //!
   TBranch        *b_muplus_AtVtx_PY;   //!
   TBranch        *b_muplus_AtVtx_PZ;   //!
   TBranch        *b_muplus_L0Calo_HCAL_realET;   //!
   TBranch        *b_muplus_L0Calo_HCAL_xProjection;   //!
   TBranch        *b_muplus_L0Calo_HCAL_yProjection;   //!
   TBranch        *b_muplus_L0Calo_HCAL_region;   //!
   TBranch        *b_muplus_ID;   //!
   TBranch        *b_muplus_PIDe;   //!
   TBranch        *b_muplus_PIDmu;   //!
   TBranch        *b_muplus_PIDK;   //!
   TBranch        *b_muplus_PIDp;   //!
   TBranch        *b_muplus_ProbNNe;   //!
   TBranch        *b_muplus_ProbNNk;   //!
   TBranch        *b_muplus_ProbNNp;   //!
   TBranch        *b_muplus_ProbNNpi;   //!
   TBranch        *b_muplus_ProbNNmu;   //!
   TBranch        *b_muplus_ProbNNghost;   //!
   TBranch        *b_muplus_hasMuon;   //!
   TBranch        *b_muplus_isMuon;   //!
   TBranch        *b_muplus_hasRich;   //!
   TBranch        *b_muplus_hasCalo;   //!
   TBranch        *b_muplus_UsedRichAerogel;   //!
   TBranch        *b_muplus_UsedRich1Gas;   //!
   TBranch        *b_muplus_UsedRich2Gas;   //!
   TBranch        *b_muplus_RichAboveElThres;   //!
   TBranch        *b_muplus_RichAboveMuThres;   //!
   TBranch        *b_muplus_RichAbovePiThres;   //!
   TBranch        *b_muplus_RichAboveKaThres;   //!
   TBranch        *b_muplus_RichAbovePrThres;   //!
   TBranch        *b_muplus_RichDLLe;   //!
   TBranch        *b_muplus_RichDLLmu;   //!
   TBranch        *b_muplus_RichDLLpi;   //!
   TBranch        *b_muplus_RichDLLk;   //!
   TBranch        *b_muplus_RichDLLp;   //!
   TBranch        *b_muplus_RichDLLbt;   //!
   TBranch        *b_muplus_InAccMuon;   //!
   TBranch        *b_muplus_isMuonLoose;   //!
   TBranch        *b_muplus_MuonMuLL;   //!
   TBranch        *b_muplus_MuonBkgLL;   //!
   TBranch        *b_muplus_MuonNShared;   //!
   TBranch        *b_muplus_InAccEcal;   //!
   TBranch        *b_muplus_CaloEcalE;   //!
   TBranch        *b_muplus_EcalPIDe;   //!
   TBranch        *b_muplus_EcalPIDmu;   //!
   TBranch        *b_muplus_InAccHcal;   //!
   TBranch        *b_muplus_CaloHcalE;   //!
   TBranch        *b_muplus_HcalPIDe;   //!
   TBranch        *b_muplus_HcalPIDmu;   //!
   TBranch        *b_muplus_InAccPrs;   //!
   TBranch        *b_muplus_PrsPIDe;   //!
   TBranch        *b_muplus_CaloPrsE;   //!
   TBranch        *b_muplus_InAccSpd;   //!
   TBranch        *b_muplus_CaloSpdE;   //!
   TBranch        *b_muplus_InAccBrem;   //!
   TBranch        *b_muplus_BremPIDe;   //!
   TBranch        *b_muplus_VeloCharge;   //!
   TBranch        *b_muplus_TRACK_Type;   //!
   TBranch        *b_muplus_TRACK_Key;   //!
   TBranch        *b_muplus_TRACK_CHI2;   //!
   TBranch        *b_muplus_TRACK_NDOF;   //!
   TBranch        *b_muplus_TRACK_CHI2NDOF;   //!
   TBranch        *b_muplus_TRACK_PCHI2;   //!
   TBranch        *b_muplus_TRACK_VeloCHI2NDOF;   //!
   TBranch        *b_muplus_TRACK_TCHI2NDOF;   //!
   TBranch        *b_muplus_VELO_UTID;   //!
   TBranch        *b_muplus_TRACK_FirstMeasurementX;   //!
   TBranch        *b_muplus_TRACK_FirstMeasurementY;   //!
   TBranch        *b_muplus_TRACK_FirstMeasurementZ;   //!
   TBranch        *b_muplus_TRACK_MatchCHI2;   //!
   TBranch        *b_muplus_TRACK_GhostProb;   //!
   TBranch        *b_muplus_TRACK_CloneDist;   //!
   TBranch        *b_muplus_TRACK_Likelihood;   //!
   TBranch        *b_nCandidate;   //!
   TBranch        *b_totCandidates;   //!
   TBranch        *b_EventInSequence;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_BCID;   //!
   TBranch        *b_BCType;   //!
   TBranch        *b_OdinTCK;   //!
   TBranch        *b_L0DUTCK;   //!
   TBranch        *b_HLTTCK;   //!
   TBranch        *b_GpsTime;   //!
   TBranch        *b_GpsYear;   //!
   TBranch        *b_GpsMonth;   //!
   TBranch        *b_GpsDay;   //!
   TBranch        *b_GpsHour;   //!
   TBranch        *b_GpsMinute;   //!
   TBranch        *b_GpsSecond;   //!
   TBranch        *b_TriggerType;   //!
   TBranch        *b_Polarity;   //!
   TBranch        *b_SignedRelativeCurrent;   //!
   TBranch        *b_PVX;   //!
   TBranch        *b_PVY;   //!
   TBranch        *b_PVZ;   //!
   TBranch        *b_PVXERR;   //!
   TBranch        *b_PVYERR;   //!
   TBranch        *b_PVZERR;   //!
   TBranch        *b_PVCHI2;   //!
   TBranch        *b_PVNDOF;   //!
   TBranch        *b_PVNTRACKS;   //!
   TBranch        *b_nPVs;   //!
   TBranch        *b_nTracks;   //!
   TBranch        *b_nLongTracks;   //!
   TBranch        *b_nDownstreamTracks;   //!
   TBranch        *b_nUpstreamTracks;   //!
   TBranch        *b_nVeloTracks;   //!
   TBranch        *b_nTTracks;   //!
   TBranch        *b_nBackTracks;   //!
   TBranch        *b_nRich1Hits;   //!
   TBranch        *b_nRich2Hits;   //!
   TBranch        *b_nVeloClusters;   //!
   TBranch        *b_nITClusters;   //!
   TBranch        *b_nTTClusters;   //!
   TBranch        *b_nOTClusters;   //!
   TBranch        *b_nSPDHits;   //!
   TBranch        *b_nMuonCoordsS0;   //!
   TBranch        *b_nMuonCoordsS1;   //!
   TBranch        *b_nMuonCoordsS2;   //!
   TBranch        *b_nMuonCoordsS3;   //!
   TBranch        *b_nMuonCoordsS4;   //!
   TBranch        *b_nMuonTracks;   //!
   TBranch        *b_StrippingBetaSBd2JpsiKsDetachedLineDecision;   //!
   TBranch        *b_StrippingBetaSBd2JpsiKsPrescaledLineDecision;   //!
   TBranch        *b_StrippingBetaSBd2JpsiKstarDetachedLineDecision;   //!
   TBranch        *b_StrippingBetaSBd2JpsiKstarPrescaledLineDecision;   //!
   TBranch        *b_StrippingBetaSBs2ChicPhi_Chic2KKPiPiNominalLineDecision;   //!
   TBranch        *b_StrippingBetaSBs2ChicPhi_Chic2PiPiPiPiNominalLineDecision;   //!
   TBranch        *b_StrippingBetaSBs2EtacPhiNominalLineDecision;   //!
   TBranch        *b_StrippingBetaSBs2JpsiEtaDetachedLineDecision;   //!
   TBranch        *b_StrippingBetaSBs2JpsiEtaPrescaledLineDecision;   //!
   TBranch        *b_StrippingBetaSBs2JpsiKstarLineDecision;   //!
   TBranch        *b_StrippingBetaSBs2JpsiPhiDetachedLineDecision;   //!
   TBranch        *b_StrippingBetaSBs2JpsiPhiPrescaledLineDecision;   //!
   TBranch        *b_StrippingBetaSBs2JpsieePhiDetachedLineDecision;   //!
   TBranch        *b_StrippingBetaSBs2JpsieePhiLineDecision;   //!
   TBranch        *b_StrippingBetaSBs2Jpsif0LineDecision;   //!
   TBranch        *b_StrippingBetaSBs2K0stK0stNominalLineDecision;   //!
   TBranch        *b_StrippingBetaSBs2KstKstNominalLineDecision;   //!
   TBranch        *b_StrippingBetaSBs2KstKstSameChargeLineDecision;   //!
   TBranch        *b_StrippingBetaSBs2PhiKstNominalLineDecision;   //!
   TBranch        *b_StrippingBetaSBs2PhiPhiLineDecision;   //!
   TBranch        *b_StrippingBetaSBs2PhiPhiWideLineDecision;   //!
   TBranch        *b_StrippingBetaSBs2Q2Body4piLineDecision;   //!
   TBranch        *b_StrippingBetaSBu2JpsiKDetachedLineDecision;   //!
   TBranch        *b_StrippingBetaSBu2JpsiKNoPIDDetachedLineDecision;   //!
   TBranch        *b_StrippingBetaSBu2JpsiKPrescaledLineDecision;   //!
   TBranch        *b_StrippingBetaSJpsi2MuMuDetachedLineDecision;   //!
   TBranch        *b_StrippingBetaSJpsi2MuMuLineDecision;   //!
   TBranch        *b_StrippingBetaSLambdab2JpsiLambdaUnbiasedLineDecision;   //!
   TBranch        *b_StrippingBu2LLK_eeLineDecision;   //!
   TBranch        *b_StrippingBu2LLK_mmLineDecision;   //!
   TBranch        *b_StrippingBd2KstarMuMu_BdToKstarMuMuLineDecision;   //!
   TBranch        *b_StrippingBd2KstarMuMu_BdToKstarMuMuLowPLineDecision;   //!
   TBranch        *b_StrippingBd2KstarMuMu_BdToKstarMuMuSSLineDecision;   //!
   TBranch        *b_StrippingBd2KstarMuMu_BdToKstarMuMuSSLowPLineDecision;   //!
   TBranch        *b_StrippingBd2KstarMuMu_BuToKMuMuLineDecision;   //!
   TBranch        *b_StrippingBd2KstarMuMu_BuToKMuMuSSLineDecision;   //

  // backward compatibility
   Bool_t          PsiHlt1Global_Dec;
   Bool_t          PsiHlt1Global_TIS;
   Bool_t          PsiHlt1Global_TOS;
   Bool_t          PsiHlt1Phys_Dec;
   Bool_t          PsiHlt1Phys_TIS;
   Bool_t          PsiHlt1Phys_TOS;
   Bool_t          PsiHlt2Global_Dec;
   Bool_t          PsiHlt2Global_TIS;
   Bool_t          PsiHlt2Global_TOS;
   Bool_t          PsiHlt2Phys_Dec;
   Bool_t          PsiHlt2Phys_TIS;
   Bool_t          PsiHlt2Phys_TOS;
   Bool_t          PsiHlt1TrackAllL0Decision_Dec;
   Bool_t          PsiHlt1TrackAllL0Decision_TIS;
   Bool_t          PsiHlt1TrackAllL0Decision_TOS;
   Bool_t          PsiHlt1TrackAllL0TightDecision_Dec;
   Bool_t          PsiHlt1TrackAllL0TightDecision_TIS;
   Bool_t          PsiHlt1TrackAllL0TightDecision_TOS;
   Bool_t          PsiHlt1DiMuonHighMassDecision_Dec;
   Bool_t          PsiHlt1DiMuonHighMassDecision_TIS;
   Bool_t          PsiHlt1DiMuonHighMassDecision_TOS;
   Bool_t          PsiHlt1DiMuonLowMassDecision_Dec;
   Bool_t          PsiHlt1DiMuonLowMassDecision_TIS;
   Bool_t          PsiHlt1DiMuonLowMassDecision_TOS;
   Bool_t          PsiHlt1SingleMuonHighPTDecision_Dec;
   Bool_t          PsiHlt1SingleMuonHighPTDecision_TIS;
   Bool_t          PsiHlt1SingleMuonHighPTDecision_TOS;
   Bool_t          PsiHlt1SingleMuonNoIPDecision_Dec;
   Bool_t          PsiHlt1SingleMuonNoIPDecision_TIS;
   Bool_t          PsiHlt1SingleMuonNoIPDecision_TOS;
   Bool_t          PsiHlt1TrackMuonDecision_Dec;
   Bool_t          PsiHlt1TrackMuonDecision_TIS;
   Bool_t          PsiHlt1TrackMuonDecision_TOS;
   Bool_t          PsiHlt2Topo2BodyBBDTDecision_Dec;
   Bool_t          PsiHlt2Topo2BodyBBDTDecision_TIS;
   Bool_t          PsiHlt2Topo2BodyBBDTDecision_TOS;
   Bool_t          PsiHlt2Topo2BodySimpleDecision_Dec;
   Bool_t          PsiHlt2Topo2BodySimpleDecision_TIS;
   Bool_t          PsiHlt2Topo2BodySimpleDecision_TOS;
   Bool_t          PsiHlt2Topo3BodyBBDTDecision_Dec;
   Bool_t          PsiHlt2Topo3BodyBBDTDecision_TIS;
   Bool_t          PsiHlt2Topo3BodyBBDTDecision_TOS;
   Bool_t          PsiHlt2Topo3BodySimpleDecision_Dec;
   Bool_t          PsiHlt2Topo3BodySimpleDecision_TIS;
   Bool_t          PsiHlt2Topo3BodySimpleDecision_TOS;
   Bool_t          PsiHlt2Topo4BodyBBDTDecision_Dec;
   Bool_t          PsiHlt2Topo4BodyBBDTDecision_TIS;
   Bool_t          PsiHlt2Topo4BodyBBDTDecision_TOS;
   Bool_t          PsiHlt2Topo4BodySimpleDecision_Dec;
   Bool_t          PsiHlt2Topo4BodySimpleDecision_TIS;
   Bool_t          PsiHlt2Topo4BodySimpleDecision_TOS;
   Bool_t          PsiHlt2DiMuonDecision_Dec;
   Bool_t          PsiHlt2DiMuonDecision_TIS;
   Bool_t          PsiHlt2DiMuonDecision_TOS;
   Bool_t          PsiHlt2DiMuonBDecision_Dec;
   Bool_t          PsiHlt2DiMuonBDecision_TIS;
   Bool_t          PsiHlt2DiMuonBDecision_TOS;
   Bool_t          PsiHlt2DiMuonDetachedDecision_Dec;
   Bool_t          PsiHlt2DiMuonDetachedDecision_TIS;
   Bool_t          PsiHlt2DiMuonDetachedDecision_TOS;
   Bool_t          PsiHlt2DiMuonDetachedHeavyDecision_Dec;
   Bool_t          PsiHlt2DiMuonDetachedHeavyDecision_TIS;
   Bool_t          PsiHlt2DiMuonDetachedHeavyDecision_TOS;
   Bool_t          PsiHlt2DiMuonDetachedJPsiDecision_Dec;
   Bool_t          PsiHlt2DiMuonDetachedJPsiDecision_TIS;
   Bool_t          PsiHlt2DiMuonDetachedJPsiDecision_TOS;
   Bool_t          PsiHlt2DiMuonDetachedPsi2SDecision_Dec;
   Bool_t          PsiHlt2DiMuonDetachedPsi2SDecision_TIS;
   Bool_t          PsiHlt2DiMuonDetachedPsi2SDecision_TOS;
   Bool_t          PsiHlt2DiMuonJPsiDecision_Dec;
   Bool_t          PsiHlt2DiMuonJPsiDecision_TIS;
   Bool_t          PsiHlt2DiMuonJPsiDecision_TOS;
   Bool_t          PsiHlt2DiMuonJPsiHighPTDecision_Dec;
   Bool_t          PsiHlt2DiMuonJPsiHighPTDecision_TIS;
   Bool_t          PsiHlt2DiMuonJPsiHighPTDecision_TOS;
   Bool_t          PsiHlt2DiMuonLowMassDecision_Dec;
   Bool_t          PsiHlt2DiMuonLowMassDecision_TIS;
   Bool_t          PsiHlt2DiMuonLowMassDecision_TOS;
   Bool_t          PsiHlt2DiMuonPsi2SDecision_Dec;
   Bool_t          PsiHlt2DiMuonPsi2SDecision_TIS;
   Bool_t          PsiHlt2DiMuonPsi2SDecision_TOS;
   Bool_t          PsiHlt2DiMuonPsi2SHighPTDecision_Dec;
   Bool_t          PsiHlt2DiMuonPsi2SHighPTDecision_TIS;
   Bool_t          PsiHlt2DiMuonPsi2SHighPTDecision_TOS;
   Bool_t          PsiHlt2LowMultMuonDecision_Dec;
   Bool_t          PsiHlt2LowMultMuonDecision_TIS;
   Bool_t          PsiHlt2LowMultMuonDecision_TOS;
   Bool_t          PsiHlt2MuonFromHLT1Decision_Dec;
   Bool_t          PsiHlt2MuonFromHLT1Decision_TIS;
   Bool_t          PsiHlt2MuonFromHLT1Decision_TOS;
   Bool_t          PsiHlt2SingleMuonDecision_Dec;
   Bool_t          PsiHlt2SingleMuonDecision_TIS;
   Bool_t          PsiHlt2SingleMuonDecision_TOS;
   Bool_t          PsiHlt2SingleMuonHighPTDecision_Dec;
   Bool_t          PsiHlt2SingleMuonHighPTDecision_TIS;
   Bool_t          PsiHlt2SingleMuonHighPTDecision_TOS;
   Bool_t          PsiHlt2SingleMuonLowPTDecision_Dec;
   Bool_t          PsiHlt2SingleMuonLowPTDecision_TIS;
   Bool_t          PsiHlt2SingleMuonLowPTDecision_TOS;
   Bool_t          PsiHlt2SingleMuonVHighPTDecision_Dec;
   Bool_t          PsiHlt2SingleMuonVHighPTDecision_TIS;
   Bool_t          PsiHlt2SingleMuonVHighPTDecision_TOS;
   Bool_t          PsiHlt2TopoMu2BodyBBDTDecision_Dec;
   Bool_t          PsiHlt2TopoMu2BodyBBDTDecision_TIS;
   Bool_t          PsiHlt2TopoMu2BodyBBDTDecision_TOS;
   Bool_t          PsiHlt2TopoMu3BodyBBDTDecision_Dec;
   Bool_t          PsiHlt2TopoMu3BodyBBDTDecision_TIS;
   Bool_t          PsiHlt2TopoMu3BodyBBDTDecision_TOS;
   Bool_t          PsiHlt2TopoMu4BodyBBDTDecision_Dec;
   Bool_t          PsiHlt2TopoMu4BodyBBDTDecision_TIS;
   Bool_t          PsiHlt2TopoMu4BodyBBDTDecision_TOS;
   Bool_t          PsiHlt2diPhotonDiMuonDecision_Dec;
   Bool_t          PsiHlt2diPhotonDiMuonDecision_TIS;
   Bool_t          PsiHlt2diPhotonDiMuonDecision_TOS;
   Bool_t          PsiL0Global_Dec;
   Bool_t          PsiL0Global_TIS;
   Bool_t          PsiL0Global_TOS;



   TBranch        *b_PsiHlt1Global_Dec;   //!
   TBranch        *b_PsiHlt1Global_TIS;   //!
   TBranch        *b_PsiHlt1Global_TOS;   //!
   TBranch        *b_PsiHlt1Phys_Dec;   //!
   TBranch        *b_PsiHlt1Phys_TIS;   //!
   TBranch        *b_PsiHlt1Phys_TOS;   //!
   TBranch        *b_PsiHlt2Global_Dec;   //!
   TBranch        *b_PsiHlt2Global_TIS;   //!
   TBranch        *b_PsiHlt2Global_TOS;   //!
   TBranch        *b_PsiHlt2Phys_Dec;   //!
   TBranch        *b_PsiHlt2Phys_TIS;   //!
   TBranch        *b_PsiHlt2Phys_TOS;   //!
   TBranch        *b_PsiHlt1TrackAllL0Decision_Dec;   //!
   TBranch        *b_PsiHlt1TrackAllL0Decision_TIS;   //!
   TBranch        *b_PsiHlt1TrackAllL0Decision_TOS;   //!
   TBranch        *b_PsiHlt1TrackAllL0TightDecision_Dec;   //!
   TBranch        *b_PsiHlt1TrackAllL0TightDecision_TIS;   //!
   TBranch        *b_PsiHlt1TrackAllL0TightDecision_TOS;   //!
   TBranch        *b_PsiHlt1DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_PsiHlt1DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_PsiHlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_PsiHlt1DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_PsiHlt1DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_PsiHlt1DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_PsiHlt1SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_PsiHlt1SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_PsiHlt1SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_PsiHlt1SingleMuonNoIPDecision_Dec;   //!
   TBranch        *b_PsiHlt1SingleMuonNoIPDecision_TIS;   //!
   TBranch        *b_PsiHlt1SingleMuonNoIPDecision_TOS;   //!
   TBranch        *b_PsiHlt1TrackMuonDecision_Dec;   //!
   TBranch        *b_PsiHlt1TrackMuonDecision_TIS;   //!
   TBranch        *b_PsiHlt1TrackMuonDecision_TOS;   //!
   TBranch        *b_PsiHlt2Topo2BodyBBDTDecision_Dec;   //!
   TBranch        *b_PsiHlt2Topo2BodyBBDTDecision_TIS;   //!
   TBranch        *b_PsiHlt2Topo2BodyBBDTDecision_TOS;   //!
   TBranch        *b_PsiHlt2Topo2BodySimpleDecision_Dec;   //!
   TBranch        *b_PsiHlt2Topo2BodySimpleDecision_TIS;   //!
   TBranch        *b_PsiHlt2Topo2BodySimpleDecision_TOS;   //!
   TBranch        *b_PsiHlt2Topo3BodyBBDTDecision_Dec;   //!
   TBranch        *b_PsiHlt2Topo3BodyBBDTDecision_TIS;   //!
   TBranch        *b_PsiHlt2Topo3BodyBBDTDecision_TOS;   //!
   TBranch        *b_PsiHlt2Topo3BodySimpleDecision_Dec;   //!
   TBranch        *b_PsiHlt2Topo3BodySimpleDecision_TIS;   //!
   TBranch        *b_PsiHlt2Topo3BodySimpleDecision_TOS;   //!
   TBranch        *b_PsiHlt2Topo4BodyBBDTDecision_Dec;   //!
   TBranch        *b_PsiHlt2Topo4BodyBBDTDecision_TIS;   //!
   TBranch        *b_PsiHlt2Topo4BodyBBDTDecision_TOS;   //!
   TBranch        *b_PsiHlt2Topo4BodySimpleDecision_Dec;   //!
   TBranch        *b_PsiHlt2Topo4BodySimpleDecision_TIS;   //!
   TBranch        *b_PsiHlt2Topo4BodySimpleDecision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonDecision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonBDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonBDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonBDecision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonDetachedDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonDetachedDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonDetachedDecision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonDetachedHeavyDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonDetachedHeavyDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonDetachedHeavyDecision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonDetachedJPsiDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonDetachedJPsiDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonDetachedJPsiDecision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonDetachedPsi2SDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonDetachedPsi2SDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonDetachedPsi2SDecision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonJPsiDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonJPsiDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonJPsiDecision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonJPsiHighPTDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonJPsiHighPTDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonJPsiHighPTDecision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonPsi2SDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonPsi2SDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonPsi2SDecision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonPsi2SHighPTDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonPsi2SHighPTDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonPsi2SHighPTDecision_TOS;   //!
   TBranch        *b_PsiHlt2LowMultMuonDecision_Dec;   //!
   TBranch        *b_PsiHlt2LowMultMuonDecision_TIS;   //!
   TBranch        *b_PsiHlt2LowMultMuonDecision_TOS;   //!
   TBranch        *b_PsiHlt2MuonFromHLT1Decision_Dec;   //!
   TBranch        *b_PsiHlt2MuonFromHLT1Decision_TIS;   //!
   TBranch        *b_PsiHlt2MuonFromHLT1Decision_TOS;   //!
   TBranch        *b_PsiHlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_PsiHlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_PsiHlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_PsiHlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_PsiHlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_PsiHlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_PsiHlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_PsiHlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_PsiHlt2SingleMuonLowPTDecision_TOS;   //!
   TBranch        *b_PsiHlt2SingleMuonVHighPTDecision_Dec;   //!
   TBranch        *b_PsiHlt2SingleMuonVHighPTDecision_TIS;   //!
   TBranch        *b_PsiHlt2SingleMuonVHighPTDecision_TOS;   //!
   TBranch        *b_PsiHlt2TopoMu2BodyBBDTDecision_Dec;   //!
   TBranch        *b_PsiHlt2TopoMu2BodyBBDTDecision_TIS;   //!
   TBranch        *b_PsiHlt2TopoMu2BodyBBDTDecision_TOS;   //!
   TBranch        *b_PsiHlt2TopoMu3BodyBBDTDecision_Dec;   //!
   TBranch        *b_PsiHlt2TopoMu3BodyBBDTDecision_TIS;   //!
   TBranch        *b_PsiHlt2TopoMu3BodyBBDTDecision_TOS;   //!
   TBranch        *b_PsiHlt2TopoMu4BodyBBDTDecision_Dec;   //!
   TBranch        *b_PsiHlt2TopoMu4BodyBBDTDecision_TIS;   //!
   TBranch        *b_PsiHlt2TopoMu4BodyBBDTDecision_TOS;   //!
   TBranch        *b_PsiHlt2diPhotonDiMuonDecision_Dec;   //!
   TBranch        *b_PsiHlt2diPhotonDiMuonDecision_TIS;   //!
   TBranch        *b_PsiHlt2diPhotonDiMuonDecision_TOS;   //!
   TBranch        *b_PsiL0Global_Dec;   //!
   TBranch        *b_PsiL0Global_TIS;   //!
   TBranch        *b_PsiL0Global_TOS;   //!


// ####################################################################################################
// *** Common Content ***
#include "B2JpsiX.icpp"


};

#endif

#ifdef Lb2JpsiL_2012_cxx
Lb2JpsiL_2012::Lb2JpsiL_2012(TTree *tree, TString module, TString dir, TString what, unsigned int NNtype): IB2JpsiX()
{
  defineConstants();
  Init(tree, module, dir, what, NNtype);
}

Lb2JpsiL_2012::~Lb2JpsiL_2012()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

void Lb2JpsiL_2012::Init(TTree *tree, TString module, TString dir, TString what, unsigned int NNtype)
{
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
  // Set sWeight address
  if(module==m_teacher || module==m_expert) fChain->SetBranchAddress("sweight", &sweight, &b_sweight);
  // Set NetOutput address
  if((module==m_weighting && NNtype==m_NNtype_two) || module==m_branching || module==m_branchingSim || module==m_lifetime){
    fChain->SetBranchAddress("netOutput", &netOutput, &b_netOutput);
  }

   fChain->SetBranchAddress("B_MINIP", &B_MINIP, &b_B_MINIP);
   fChain->SetBranchAddress("B_MINIPCHI2", &B_MINIPCHI2, &b_B_MINIPCHI2);
   fChain->SetBranchAddress("B_MINIPNEXTBEST", &B_MINIPNEXTBEST, &b_B_MINIPNEXTBEST);
   fChain->SetBranchAddress("B_MINIPCHI2NEXTBEST", &B_MINIPCHI2NEXTBEST, &b_B_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("nPV", &nPV, &b_nPV);
   fChain->SetBranchAddress("B_AllIP", B_AllIP, &b_B_AllIP);
   fChain->SetBranchAddress("B_AllIPchi2", B_AllIPchi2, &b_B_AllIPchi2);
   fChain->SetBranchAddress("B_ENDVERTEX_X", &B_ENDVERTEX_X, &b_B_ENDVERTEX_X);
   fChain->SetBranchAddress("B_ENDVERTEX_Y", &B_ENDVERTEX_Y, &b_B_ENDVERTEX_Y);
   fChain->SetBranchAddress("B_ENDVERTEX_Z", &B_ENDVERTEX_Z, &b_B_ENDVERTEX_Z);
   fChain->SetBranchAddress("B_ENDVERTEX_XERR", &B_ENDVERTEX_XERR, &b_B_ENDVERTEX_XERR);
   fChain->SetBranchAddress("B_ENDVERTEX_YERR", &B_ENDVERTEX_YERR, &b_B_ENDVERTEX_YERR);
   fChain->SetBranchAddress("B_ENDVERTEX_ZERR", &B_ENDVERTEX_ZERR, &b_B_ENDVERTEX_ZERR);
   fChain->SetBranchAddress("B_ENDVERTEX_CHI2", &B_ENDVERTEX_CHI2, &b_B_ENDVERTEX_CHI2);
   fChain->SetBranchAddress("B_ENDVERTEX_NDOF", &B_ENDVERTEX_NDOF, &b_B_ENDVERTEX_NDOF);
   fChain->SetBranchAddress("B_ENDVERTEX_COV_", B_ENDVERTEX_COV_, &b_B_ENDVERTEX_COV_);
   fChain->SetBranchAddress("B_OWNPV_X", &B_OWNPV_X, &b_B_OWNPV_X);
   fChain->SetBranchAddress("B_OWNPV_Y", &B_OWNPV_Y, &b_B_OWNPV_Y);
   fChain->SetBranchAddress("B_OWNPV_Z", &B_OWNPV_Z, &b_B_OWNPV_Z);
   fChain->SetBranchAddress("B_OWNPV_XERR", &B_OWNPV_XERR, &b_B_OWNPV_XERR);
   fChain->SetBranchAddress("B_OWNPV_YERR", &B_OWNPV_YERR, &b_B_OWNPV_YERR);
   fChain->SetBranchAddress("B_OWNPV_ZERR", &B_OWNPV_ZERR, &b_B_OWNPV_ZERR);
   fChain->SetBranchAddress("B_OWNPV_CHI2", &B_OWNPV_CHI2, &b_B_OWNPV_CHI2);
   fChain->SetBranchAddress("B_OWNPV_NDOF", &B_OWNPV_NDOF, &b_B_OWNPV_NDOF);
   fChain->SetBranchAddress("B_OWNPV_COV_", B_OWNPV_COV_, &b_B_OWNPV_COV_);
   fChain->SetBranchAddress("B_IP_OWNPV", &B_IP_OWNPV, &b_B_IP_OWNPV);
   fChain->SetBranchAddress("B_IPCHI2_OWNPV", &B_IPCHI2_OWNPV, &b_B_IPCHI2_OWNPV);
   fChain->SetBranchAddress("B_FD_OWNPV", &B_FD_OWNPV, &b_B_FD_OWNPV);
   fChain->SetBranchAddress("B_FDCHI2_OWNPV", &B_FDCHI2_OWNPV, &b_B_FDCHI2_OWNPV);
   fChain->SetBranchAddress("B_DIRA_OWNPV", &B_DIRA_OWNPV, &b_B_DIRA_OWNPV);
   fChain->SetBranchAddress("B_TOPPV_X", &B_TOPPV_X, &b_B_TOPPV_X);
   fChain->SetBranchAddress("B_TOPPV_Y", &B_TOPPV_Y, &b_B_TOPPV_Y);
   fChain->SetBranchAddress("B_TOPPV_Z", &B_TOPPV_Z, &b_B_TOPPV_Z);
   fChain->SetBranchAddress("B_TOPPV_XERR", &B_TOPPV_XERR, &b_B_TOPPV_XERR);
   fChain->SetBranchAddress("B_TOPPV_YERR", &B_TOPPV_YERR, &b_B_TOPPV_YERR);
   fChain->SetBranchAddress("B_TOPPV_ZERR", &B_TOPPV_ZERR, &b_B_TOPPV_ZERR);
   fChain->SetBranchAddress("B_TOPPV_CHI2", &B_TOPPV_CHI2, &b_B_TOPPV_CHI2);
   fChain->SetBranchAddress("B_TOPPV_NDOF", &B_TOPPV_NDOF, &b_B_TOPPV_NDOF);
   fChain->SetBranchAddress("B_TOPPV_COV_", B_TOPPV_COV_, &b_B_TOPPV_COV_);
   fChain->SetBranchAddress("B_IP_TOPPV", &B_IP_TOPPV, &b_B_IP_TOPPV);
   fChain->SetBranchAddress("B_IPCHI2_TOPPV", &B_IPCHI2_TOPPV, &b_B_IPCHI2_TOPPV);
   fChain->SetBranchAddress("B_FD_TOPPV", &B_FD_TOPPV, &b_B_FD_TOPPV);
   fChain->SetBranchAddress("B_FDCHI2_TOPPV", &B_FDCHI2_TOPPV, &b_B_FDCHI2_TOPPV);
   fChain->SetBranchAddress("B_DIRA_TOPPV", &B_DIRA_TOPPV, &b_B_DIRA_TOPPV);
   fChain->SetBranchAddress("B_P", &B_P, &b_B_P);
   fChain->SetBranchAddress("B_PT", &B_PT, &b_B_PT);
   fChain->SetBranchAddress("B_PE", &B_PE, &b_B_PE);
   fChain->SetBranchAddress("B_PX", &B_PX, &b_B_PX);
   fChain->SetBranchAddress("B_PY", &B_PY, &b_B_PY);
   fChain->SetBranchAddress("B_PZ", &B_PZ, &b_B_PZ);
   fChain->SetBranchAddress("B_REFPX", &B_REFPX, &b_B_REFPX);
   fChain->SetBranchAddress("B_REFPY", &B_REFPY, &b_B_REFPY);
   fChain->SetBranchAddress("B_REFPZ", &B_REFPZ, &b_B_REFPZ);
   fChain->SetBranchAddress("B_MM", &B_MM, &b_B_MM);
   fChain->SetBranchAddress("B_MMERR", &B_MMERR, &b_B_MMERR);
   fChain->SetBranchAddress("B_M", &B_M, &b_B_M);
   fChain->SetBranchAddress("B_ID", &B_ID, &b_B_ID);
   fChain->SetBranchAddress("B_TAU", &B_TAU, &b_B_TAU);
   fChain->SetBranchAddress("B_TAUERR", &B_TAUERR, &b_B_TAUERR);
   fChain->SetBranchAddress("B_TAUCHI2", &B_TAUCHI2, &b_B_TAUCHI2);
   fChain->SetBranchAddress("B_ConstBFit_nPV", &B_ConstBFit_nPV, &b_B_ConstBFit_nPV);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_M", B_ConstBFit_J_psi_1S_M, &b_B_ConstBFit_J_psi_1S_M);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_MERR", B_ConstBFit_J_psi_1S_MERR, &b_B_ConstBFit_J_psi_1S_MERR);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_P", B_ConstBFit_J_psi_1S_P, &b_B_ConstBFit_J_psi_1S_P);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_P0_ID", B_ConstBFit_J_psi_1S_P0_ID, &b_B_ConstBFit_J_psi_1S_P0_ID);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_P0_PE", B_ConstBFit_J_psi_1S_P0_PE, &b_B_ConstBFit_J_psi_1S_P0_PE);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_P0_PX", B_ConstBFit_J_psi_1S_P0_PX, &b_B_ConstBFit_J_psi_1S_P0_PX);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_P0_PY", B_ConstBFit_J_psi_1S_P0_PY, &b_B_ConstBFit_J_psi_1S_P0_PY);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_P0_PZ", B_ConstBFit_J_psi_1S_P0_PZ, &b_B_ConstBFit_J_psi_1S_P0_PZ);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_P1_ID", B_ConstBFit_J_psi_1S_P1_ID, &b_B_ConstBFit_J_psi_1S_P1_ID);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_P1_PE", B_ConstBFit_J_psi_1S_P1_PE, &b_B_ConstBFit_J_psi_1S_P1_PE);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_P1_PX", B_ConstBFit_J_psi_1S_P1_PX, &b_B_ConstBFit_J_psi_1S_P1_PX);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_P1_PY", B_ConstBFit_J_psi_1S_P1_PY, &b_B_ConstBFit_J_psi_1S_P1_PY);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_P1_PZ", B_ConstBFit_J_psi_1S_P1_PZ, &b_B_ConstBFit_J_psi_1S_P1_PZ);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_PERR", B_ConstBFit_J_psi_1S_PERR, &b_B_ConstBFit_J_psi_1S_PERR);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_ctau", B_ConstBFit_J_psi_1S_ctau, &b_B_ConstBFit_J_psi_1S_ctau);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_ctauErr", B_ConstBFit_J_psi_1S_ctauErr, &b_B_ConstBFit_J_psi_1S_ctauErr);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_decayLength", B_ConstBFit_J_psi_1S_decayLength, &b_B_ConstBFit_J_psi_1S_decayLength);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_decayLengthErr", B_ConstBFit_J_psi_1S_decayLengthErr, &b_B_ConstBFit_J_psi_1S_decayLengthErr);
   fChain->SetBranchAddress("B_ConstBFit_Lambda0_M", B_ConstBFit_Lambda0_M, &b_B_ConstBFit_Lambda0_M);
   fChain->SetBranchAddress("B_ConstBFit_Lambda0_MERR", B_ConstBFit_Lambda0_MERR, &b_B_ConstBFit_Lambda0_MERR);
   fChain->SetBranchAddress("B_ConstBFit_Lambda0_P", B_ConstBFit_Lambda0_P, &b_B_ConstBFit_Lambda0_P);
   fChain->SetBranchAddress("B_ConstBFit_Lambda0_P0_ID", B_ConstBFit_Lambda0_P0_ID, &b_B_ConstBFit_Lambda0_P0_ID);
   fChain->SetBranchAddress("B_ConstBFit_Lambda0_P0_PE", B_ConstBFit_Lambda0_P0_PE, &b_B_ConstBFit_Lambda0_P0_PE);
   fChain->SetBranchAddress("B_ConstBFit_Lambda0_P0_PX", B_ConstBFit_Lambda0_P0_PX, &b_B_ConstBFit_Lambda0_P0_PX);
   fChain->SetBranchAddress("B_ConstBFit_Lambda0_P0_PY", B_ConstBFit_Lambda0_P0_PY, &b_B_ConstBFit_Lambda0_P0_PY);
   fChain->SetBranchAddress("B_ConstBFit_Lambda0_P0_PZ", B_ConstBFit_Lambda0_P0_PZ, &b_B_ConstBFit_Lambda0_P0_PZ);
   fChain->SetBranchAddress("B_ConstBFit_Lambda0_P1_ID", B_ConstBFit_Lambda0_P1_ID, &b_B_ConstBFit_Lambda0_P1_ID);
   fChain->SetBranchAddress("B_ConstBFit_Lambda0_P1_PE", B_ConstBFit_Lambda0_P1_PE, &b_B_ConstBFit_Lambda0_P1_PE);
   fChain->SetBranchAddress("B_ConstBFit_Lambda0_P1_PX", B_ConstBFit_Lambda0_P1_PX, &b_B_ConstBFit_Lambda0_P1_PX);
   fChain->SetBranchAddress("B_ConstBFit_Lambda0_P1_PY", B_ConstBFit_Lambda0_P1_PY, &b_B_ConstBFit_Lambda0_P1_PY);
   fChain->SetBranchAddress("B_ConstBFit_Lambda0_P1_PZ", B_ConstBFit_Lambda0_P1_PZ, &b_B_ConstBFit_Lambda0_P1_PZ);
   fChain->SetBranchAddress("B_ConstBFit_Lambda0_PERR", B_ConstBFit_Lambda0_PERR, &b_B_ConstBFit_Lambda0_PERR);
   fChain->SetBranchAddress("B_ConstBFit_Lambda0_ctau", B_ConstBFit_Lambda0_ctau, &b_B_ConstBFit_Lambda0_ctau);
   fChain->SetBranchAddress("B_ConstBFit_Lambda0_ctauErr", B_ConstBFit_Lambda0_ctauErr, &b_B_ConstBFit_Lambda0_ctauErr);
   fChain->SetBranchAddress("B_ConstBFit_Lambda0_decayLength", B_ConstBFit_Lambda0_decayLength, &b_B_ConstBFit_Lambda0_decayLength);
   fChain->SetBranchAddress("B_ConstBFit_Lambda0_decayLengthErr", B_ConstBFit_Lambda0_decayLengthErr, &b_B_ConstBFit_Lambda0_decayLengthErr);
   fChain->SetBranchAddress("B_ConstBFit_M", B_ConstBFit_M, &b_B_ConstBFit_M);
   fChain->SetBranchAddress("B_ConstBFit_MERR", B_ConstBFit_MERR, &b_B_ConstBFit_MERR);
   fChain->SetBranchAddress("B_ConstBFit_P", B_ConstBFit_P, &b_B_ConstBFit_P);
   fChain->SetBranchAddress("B_ConstBFit_PERR", B_ConstBFit_PERR, &b_B_ConstBFit_PERR);
   fChain->SetBranchAddress("B_ConstBFit_PV_X", B_ConstBFit_PV_X, &b_B_ConstBFit_PV_X);
   fChain->SetBranchAddress("B_ConstBFit_PV_Y", B_ConstBFit_PV_Y, &b_B_ConstBFit_PV_Y);
   fChain->SetBranchAddress("B_ConstBFit_PV_Z", B_ConstBFit_PV_Z, &b_B_ConstBFit_PV_Z);
   fChain->SetBranchAddress("B_ConstBFit_PV_key", B_ConstBFit_PV_key, &b_B_ConstBFit_PV_key);
   fChain->SetBranchAddress("B_ConstBFit_chi2", B_ConstBFit_chi2, &b_B_ConstBFit_chi2);
   fChain->SetBranchAddress("B_ConstBFit_ctau", B_ConstBFit_ctau, &b_B_ConstBFit_ctau);
   fChain->SetBranchAddress("B_ConstBFit_ctauErr", B_ConstBFit_ctauErr, &b_B_ConstBFit_ctauErr);
   fChain->SetBranchAddress("B_ConstBFit_decayLength", B_ConstBFit_decayLength, &b_B_ConstBFit_decayLength);
   fChain->SetBranchAddress("B_ConstBFit_decayLengthErr", B_ConstBFit_decayLengthErr, &b_B_ConstBFit_decayLengthErr);
   fChain->SetBranchAddress("B_ConstBFit_nDOF", B_ConstBFit_nDOF, &b_B_ConstBFit_nDOF);
   fChain->SetBranchAddress("B_ConstBFit_nIter", B_ConstBFit_nIter, &b_B_ConstBFit_nIter);
   fChain->SetBranchAddress("B_ConstBFit_status", B_ConstBFit_status, &b_B_ConstBFit_status);
   fChain->SetBranchAddress("B_FullFit_nPV", &B_FullFit_nPV, &b_B_FullFit_nPV);
   fChain->SetBranchAddress("B_FullFit_J_psi_1S_M", B_FullFit_J_psi_1S_M, &b_B_FullFit_J_psi_1S_M);
   fChain->SetBranchAddress("B_FullFit_J_psi_1S_MERR", B_FullFit_J_psi_1S_MERR, &b_B_FullFit_J_psi_1S_MERR);
   fChain->SetBranchAddress("B_FullFit_J_psi_1S_P", B_FullFit_J_psi_1S_P, &b_B_FullFit_J_psi_1S_P);
   fChain->SetBranchAddress("B_FullFit_J_psi_1S_PERR", B_FullFit_J_psi_1S_PERR, &b_B_FullFit_J_psi_1S_PERR);
   fChain->SetBranchAddress("B_FullFit_J_psi_1S_ctau", B_FullFit_J_psi_1S_ctau, &b_B_FullFit_J_psi_1S_ctau);
   fChain->SetBranchAddress("B_FullFit_J_psi_1S_ctauErr", B_FullFit_J_psi_1S_ctauErr, &b_B_FullFit_J_psi_1S_ctauErr);
   fChain->SetBranchAddress("B_FullFit_J_psi_1S_decayLength", B_FullFit_J_psi_1S_decayLength, &b_B_FullFit_J_psi_1S_decayLength);
   fChain->SetBranchAddress("B_FullFit_J_psi_1S_decayLengthErr", B_FullFit_J_psi_1S_decayLengthErr, &b_B_FullFit_J_psi_1S_decayLengthErr);
   fChain->SetBranchAddress("B_FullFit_Lambda0_M", B_FullFit_Lambda0_M, &b_B_FullFit_Lambda0_M);
   fChain->SetBranchAddress("B_FullFit_Lambda0_MERR", B_FullFit_Lambda0_MERR, &b_B_FullFit_Lambda0_MERR);
   fChain->SetBranchAddress("B_FullFit_Lambda0_P", B_FullFit_Lambda0_P, &b_B_FullFit_Lambda0_P);
   fChain->SetBranchAddress("B_FullFit_Lambda0_PERR", B_FullFit_Lambda0_PERR, &b_B_FullFit_Lambda0_PERR);
   fChain->SetBranchAddress("B_FullFit_Lambda0_ctau", B_FullFit_Lambda0_ctau, &b_B_FullFit_Lambda0_ctau);
   fChain->SetBranchAddress("B_FullFit_Lambda0_ctauErr", B_FullFit_Lambda0_ctauErr, &b_B_FullFit_Lambda0_ctauErr);
   fChain->SetBranchAddress("B_FullFit_Lambda0_decayLength", B_FullFit_Lambda0_decayLength, &b_B_FullFit_Lambda0_decayLength);
   fChain->SetBranchAddress("B_FullFit_Lambda0_decayLengthErr", B_FullFit_Lambda0_decayLengthErr, &b_B_FullFit_Lambda0_decayLengthErr);
   fChain->SetBranchAddress("B_FullFit_M", B_FullFit_M, &b_B_FullFit_M);
   fChain->SetBranchAddress("B_FullFit_MERR", B_FullFit_MERR, &b_B_FullFit_MERR);
   fChain->SetBranchAddress("B_FullFit_P", B_FullFit_P, &b_B_FullFit_P);
   fChain->SetBranchAddress("B_FullFit_PERR", B_FullFit_PERR, &b_B_FullFit_PERR);
   fChain->SetBranchAddress("B_FullFit_PV_X", B_FullFit_PV_X, &b_B_FullFit_PV_X);
   fChain->SetBranchAddress("B_FullFit_PV_Y", B_FullFit_PV_Y, &b_B_FullFit_PV_Y);
   fChain->SetBranchAddress("B_FullFit_PV_Z", B_FullFit_PV_Z, &b_B_FullFit_PV_Z);
   fChain->SetBranchAddress("B_FullFit_PV_key", B_FullFit_PV_key, &b_B_FullFit_PV_key);
   fChain->SetBranchAddress("B_FullFit_chi2", B_FullFit_chi2, &b_B_FullFit_chi2);
   fChain->SetBranchAddress("B_FullFit_ctau", B_FullFit_ctau, &b_B_FullFit_ctau);
   fChain->SetBranchAddress("B_FullFit_ctauErr", B_FullFit_ctauErr, &b_B_FullFit_ctauErr);
   fChain->SetBranchAddress("B_FullFit_decayLength", B_FullFit_decayLength, &b_B_FullFit_decayLength);
   fChain->SetBranchAddress("B_FullFit_decayLengthErr", B_FullFit_decayLengthErr, &b_B_FullFit_decayLengthErr);
   fChain->SetBranchAddress("B_FullFit_nDOF", B_FullFit_nDOF, &b_B_FullFit_nDOF);
   fChain->SetBranchAddress("B_FullFit_nIter", B_FullFit_nIter, &b_B_FullFit_nIter);
   fChain->SetBranchAddress("B_FullFit_status", B_FullFit_status, &b_B_FullFit_status);
   fChain->SetBranchAddress("B_OnlyPsiFit_nPV", &B_OnlyPsiFit_nPV, &b_B_OnlyPsiFit_nPV);
   fChain->SetBranchAddress("B_OnlyPsiFit_J_psi_1S_M", B_OnlyPsiFit_J_psi_1S_M, &b_B_OnlyPsiFit_J_psi_1S_M);
   fChain->SetBranchAddress("B_OnlyPsiFit_J_psi_1S_MERR", B_OnlyPsiFit_J_psi_1S_MERR, &b_B_OnlyPsiFit_J_psi_1S_MERR);
   fChain->SetBranchAddress("B_OnlyPsiFit_J_psi_1S_P", B_OnlyPsiFit_J_psi_1S_P, &b_B_OnlyPsiFit_J_psi_1S_P);
   fChain->SetBranchAddress("B_OnlyPsiFit_J_psi_1S_PERR", B_OnlyPsiFit_J_psi_1S_PERR, &b_B_OnlyPsiFit_J_psi_1S_PERR);
   fChain->SetBranchAddress("B_OnlyPsiFit_J_psi_1S_ctau", B_OnlyPsiFit_J_psi_1S_ctau, &b_B_OnlyPsiFit_J_psi_1S_ctau);
   fChain->SetBranchAddress("B_OnlyPsiFit_J_psi_1S_ctauErr", B_OnlyPsiFit_J_psi_1S_ctauErr, &b_B_OnlyPsiFit_J_psi_1S_ctauErr);
   fChain->SetBranchAddress("B_OnlyPsiFit_J_psi_1S_decayLength", B_OnlyPsiFit_J_psi_1S_decayLength, &b_B_OnlyPsiFit_J_psi_1S_decayLength);
   fChain->SetBranchAddress("B_OnlyPsiFit_J_psi_1S_decayLengthErr", B_OnlyPsiFit_J_psi_1S_decayLengthErr, &b_B_OnlyPsiFit_J_psi_1S_decayLengthErr);
   fChain->SetBranchAddress("B_OnlyPsiFit_Lambda0_M", B_OnlyPsiFit_Lambda0_M, &b_B_OnlyPsiFit_Lambda0_M);
   fChain->SetBranchAddress("B_OnlyPsiFit_Lambda0_MERR", B_OnlyPsiFit_Lambda0_MERR, &b_B_OnlyPsiFit_Lambda0_MERR);
   fChain->SetBranchAddress("B_OnlyPsiFit_Lambda0_P", B_OnlyPsiFit_Lambda0_P, &b_B_OnlyPsiFit_Lambda0_P);
   fChain->SetBranchAddress("B_OnlyPsiFit_Lambda0_PERR", B_OnlyPsiFit_Lambda0_PERR, &b_B_OnlyPsiFit_Lambda0_PERR);
   fChain->SetBranchAddress("B_OnlyPsiFit_Lambda0_ctau", B_OnlyPsiFit_Lambda0_ctau, &b_B_OnlyPsiFit_Lambda0_ctau);
   fChain->SetBranchAddress("B_OnlyPsiFit_Lambda0_ctauErr", B_OnlyPsiFit_Lambda0_ctauErr, &b_B_OnlyPsiFit_Lambda0_ctauErr);
   fChain->SetBranchAddress("B_OnlyPsiFit_Lambda0_decayLength", B_OnlyPsiFit_Lambda0_decayLength, &b_B_OnlyPsiFit_Lambda0_decayLength);
   fChain->SetBranchAddress("B_OnlyPsiFit_Lambda0_decayLengthErr", B_OnlyPsiFit_Lambda0_decayLengthErr, &b_B_OnlyPsiFit_Lambda0_decayLengthErr);
   fChain->SetBranchAddress("B_OnlyPsiFit_M", B_OnlyPsiFit_M, &b_B_OnlyPsiFit_M);
   fChain->SetBranchAddress("B_OnlyPsiFit_MERR", B_OnlyPsiFit_MERR, &b_B_OnlyPsiFit_MERR);
   fChain->SetBranchAddress("B_OnlyPsiFit_P", B_OnlyPsiFit_P, &b_B_OnlyPsiFit_P);
   fChain->SetBranchAddress("B_OnlyPsiFit_PERR", B_OnlyPsiFit_PERR, &b_B_OnlyPsiFit_PERR);
   fChain->SetBranchAddress("B_OnlyPsiFit_PV_X", B_OnlyPsiFit_PV_X, &b_B_OnlyPsiFit_PV_X);
   fChain->SetBranchAddress("B_OnlyPsiFit_PV_Y", B_OnlyPsiFit_PV_Y, &b_B_OnlyPsiFit_PV_Y);
   fChain->SetBranchAddress("B_OnlyPsiFit_PV_Z", B_OnlyPsiFit_PV_Z, &b_B_OnlyPsiFit_PV_Z);
   fChain->SetBranchAddress("B_OnlyPsiFit_PV_key", B_OnlyPsiFit_PV_key, &b_B_OnlyPsiFit_PV_key);
   fChain->SetBranchAddress("B_OnlyPsiFit_chi2", B_OnlyPsiFit_chi2, &b_B_OnlyPsiFit_chi2);
   fChain->SetBranchAddress("B_OnlyPsiFit_ctau", B_OnlyPsiFit_ctau, &b_B_OnlyPsiFit_ctau);
   fChain->SetBranchAddress("B_OnlyPsiFit_ctauErr", B_OnlyPsiFit_ctauErr, &b_B_OnlyPsiFit_ctauErr);
   fChain->SetBranchAddress("B_OnlyPsiFit_decayLength", B_OnlyPsiFit_decayLength, &b_B_OnlyPsiFit_decayLength);
   fChain->SetBranchAddress("B_OnlyPsiFit_decayLengthErr", B_OnlyPsiFit_decayLengthErr, &b_B_OnlyPsiFit_decayLengthErr);
   fChain->SetBranchAddress("B_OnlyPsiFit_nDOF", B_OnlyPsiFit_nDOF, &b_B_OnlyPsiFit_nDOF);
   fChain->SetBranchAddress("B_OnlyPsiFit_nIter", B_OnlyPsiFit_nIter, &b_B_OnlyPsiFit_nIter);
   fChain->SetBranchAddress("B_OnlyPsiFit_status", B_OnlyPsiFit_status, &b_B_OnlyPsiFit_status);
   fChain->SetBranchAddress("B_L0Global_Dec", &B_L0Global_Dec, &b_B_L0Global_Dec);
   fChain->SetBranchAddress("B_L0Global_TIS", &B_L0Global_TIS, &b_B_L0Global_TIS);
   fChain->SetBranchAddress("B_L0Global_TOS", &B_L0Global_TOS, &b_B_L0Global_TOS);
   fChain->SetBranchAddress("B_Hlt1Global_Dec", &B_Hlt1Global_Dec, &b_B_Hlt1Global_Dec);
   fChain->SetBranchAddress("B_Hlt1Global_TIS", &B_Hlt1Global_TIS, &b_B_Hlt1Global_TIS);
   fChain->SetBranchAddress("B_Hlt1Global_TOS", &B_Hlt1Global_TOS, &b_B_Hlt1Global_TOS);
   fChain->SetBranchAddress("B_Hlt1Phys_Dec", &B_Hlt1Phys_Dec, &b_B_Hlt1Phys_Dec);
   fChain->SetBranchAddress("B_Hlt1Phys_TIS", &B_Hlt1Phys_TIS, &b_B_Hlt1Phys_TIS);
   fChain->SetBranchAddress("B_Hlt1Phys_TOS", &B_Hlt1Phys_TOS, &b_B_Hlt1Phys_TOS);
   fChain->SetBranchAddress("B_Hlt2Global_Dec", &B_Hlt2Global_Dec, &b_B_Hlt2Global_Dec);
   fChain->SetBranchAddress("B_Hlt2Global_TIS", &B_Hlt2Global_TIS, &b_B_Hlt2Global_TIS);
   fChain->SetBranchAddress("B_Hlt2Global_TOS", &B_Hlt2Global_TOS, &b_B_Hlt2Global_TOS);
   fChain->SetBranchAddress("B_Hlt2Phys_Dec", &B_Hlt2Phys_Dec, &b_B_Hlt2Phys_Dec);
   fChain->SetBranchAddress("B_Hlt2Phys_TIS", &B_Hlt2Phys_TIS, &b_B_Hlt2Phys_TIS);
   fChain->SetBranchAddress("B_Hlt2Phys_TOS", &B_Hlt2Phys_TOS, &b_B_Hlt2Phys_TOS);
   fChain->SetBranchAddress("B_StrippingGlobal_Dec", &B_StrippingGlobal_Dec, &b_B_StrippingGlobal_Dec);
   fChain->SetBranchAddress("B_StrippingGlobal_TIS", &B_StrippingGlobal_TIS, &b_B_StrippingGlobal_TIS);
   fChain->SetBranchAddress("B_StrippingGlobal_TOS", &B_StrippingGlobal_TOS, &b_B_StrippingGlobal_TOS);
   fChain->SetBranchAddress("B_L0HadronDecision_Dec", &B_L0HadronDecision_Dec, &b_B_L0HadronDecision_Dec);
   fChain->SetBranchAddress("B_L0HadronDecision_TIS", &B_L0HadronDecision_TIS, &b_B_L0HadronDecision_TIS);
   fChain->SetBranchAddress("B_L0HadronDecision_TOS", &B_L0HadronDecision_TOS, &b_B_L0HadronDecision_TOS);
   fChain->SetBranchAddress("B_L0MuonDecision_Dec", &B_L0MuonDecision_Dec, &b_B_L0MuonDecision_Dec);
   fChain->SetBranchAddress("B_L0MuonDecision_TIS", &B_L0MuonDecision_TIS, &b_B_L0MuonDecision_TIS);
   fChain->SetBranchAddress("B_L0MuonDecision_TOS", &B_L0MuonDecision_TOS, &b_B_L0MuonDecision_TOS);
   fChain->SetBranchAddress("B_L0DiMuonDecision_Dec", &B_L0DiMuonDecision_Dec, &b_B_L0DiMuonDecision_Dec);
   fChain->SetBranchAddress("B_L0DiMuonDecision_TIS", &B_L0DiMuonDecision_TIS, &b_B_L0DiMuonDecision_TIS);
   fChain->SetBranchAddress("B_L0DiMuonDecision_TOS", &B_L0DiMuonDecision_TOS, &b_B_L0DiMuonDecision_TOS);
   fChain->SetBranchAddress("B_L0ElectronDecision_Dec", &B_L0ElectronDecision_Dec, &b_B_L0ElectronDecision_Dec);
   fChain->SetBranchAddress("B_L0ElectronDecision_TIS", &B_L0ElectronDecision_TIS, &b_B_L0ElectronDecision_TIS);
   fChain->SetBranchAddress("B_L0ElectronDecision_TOS", &B_L0ElectronDecision_TOS, &b_B_L0ElectronDecision_TOS);
   fChain->SetBranchAddress("B_L0PhotonDecision_Dec", &B_L0PhotonDecision_Dec, &b_B_L0PhotonDecision_Dec);
   fChain->SetBranchAddress("B_L0PhotonDecision_TIS", &B_L0PhotonDecision_TIS, &b_B_L0PhotonDecision_TIS);
   fChain->SetBranchAddress("B_L0PhotonDecision_TOS", &B_L0PhotonDecision_TOS, &b_B_L0PhotonDecision_TOS);
   fChain->SetBranchAddress("B_Hlt1TrackAllL0Decision_Dec", &B_Hlt1TrackAllL0Decision_Dec, &b_B_Hlt1TrackAllL0Decision_Dec);
   fChain->SetBranchAddress("B_Hlt1TrackAllL0Decision_TIS", &B_Hlt1TrackAllL0Decision_TIS, &b_B_Hlt1TrackAllL0Decision_TIS);
   fChain->SetBranchAddress("B_Hlt1TrackAllL0Decision_TOS", &B_Hlt1TrackAllL0Decision_TOS, &b_B_Hlt1TrackAllL0Decision_TOS);
   fChain->SetBranchAddress("B_Hlt1TrackAllL0TightDecision_Dec", &B_Hlt1TrackAllL0TightDecision_Dec, &b_B_Hlt1TrackAllL0TightDecision_Dec);
   fChain->SetBranchAddress("B_Hlt1TrackAllL0TightDecision_TIS", &B_Hlt1TrackAllL0TightDecision_TIS, &b_B_Hlt1TrackAllL0TightDecision_TIS);
   fChain->SetBranchAddress("B_Hlt1TrackAllL0TightDecision_TOS", &B_Hlt1TrackAllL0TightDecision_TOS, &b_B_Hlt1TrackAllL0TightDecision_TOS);
   fChain->SetBranchAddress("B_Hlt1DiMuonHighMassDecision_Dec", &B_Hlt1DiMuonHighMassDecision_Dec, &b_B_Hlt1DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("B_Hlt1DiMuonHighMassDecision_TIS", &B_Hlt1DiMuonHighMassDecision_TIS, &b_B_Hlt1DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("B_Hlt1DiMuonHighMassDecision_TOS", &B_Hlt1DiMuonHighMassDecision_TOS, &b_B_Hlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("B_Hlt1DiMuonLowMassDecision_Dec", &B_Hlt1DiMuonLowMassDecision_Dec, &b_B_Hlt1DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("B_Hlt1DiMuonLowMassDecision_TIS", &B_Hlt1DiMuonLowMassDecision_TIS, &b_B_Hlt1DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("B_Hlt1DiMuonLowMassDecision_TOS", &B_Hlt1DiMuonLowMassDecision_TOS, &b_B_Hlt1DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("B_Hlt1SingleMuonHighPTDecision_Dec", &B_Hlt1SingleMuonHighPTDecision_Dec, &b_B_Hlt1SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt1SingleMuonHighPTDecision_TIS", &B_Hlt1SingleMuonHighPTDecision_TIS, &b_B_Hlt1SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt1SingleMuonHighPTDecision_TOS", &B_Hlt1SingleMuonHighPTDecision_TOS, &b_B_Hlt1SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt1SingleMuonNoIPDecision_Dec", &B_Hlt1SingleMuonNoIPDecision_Dec, &b_B_Hlt1SingleMuonNoIPDecision_Dec);
   fChain->SetBranchAddress("B_Hlt1SingleMuonNoIPDecision_TIS", &B_Hlt1SingleMuonNoIPDecision_TIS, &b_B_Hlt1SingleMuonNoIPDecision_TIS);
   fChain->SetBranchAddress("B_Hlt1SingleMuonNoIPDecision_TOS", &B_Hlt1SingleMuonNoIPDecision_TOS, &b_B_Hlt1SingleMuonNoIPDecision_TOS);
   fChain->SetBranchAddress("B_Hlt1TrackMuonDecision_Dec", &B_Hlt1TrackMuonDecision_Dec, &b_B_Hlt1TrackMuonDecision_Dec);
   fChain->SetBranchAddress("B_Hlt1TrackMuonDecision_TIS", &B_Hlt1TrackMuonDecision_TIS, &b_B_Hlt1TrackMuonDecision_TIS);
   fChain->SetBranchAddress("B_Hlt1TrackMuonDecision_TOS", &B_Hlt1TrackMuonDecision_TOS, &b_B_Hlt1TrackMuonDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2Topo2BodyBBDTDecision_Dec", &B_Hlt2Topo2BodyBBDTDecision_Dec, &b_B_Hlt2Topo2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2Topo2BodyBBDTDecision_TIS", &B_Hlt2Topo2BodyBBDTDecision_TIS, &b_B_Hlt2Topo2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2Topo2BodyBBDTDecision_TOS", &B_Hlt2Topo2BodyBBDTDecision_TOS, &b_B_Hlt2Topo2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2Topo2BodySimpleDecision_Dec", &B_Hlt2Topo2BodySimpleDecision_Dec, &b_B_Hlt2Topo2BodySimpleDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2Topo2BodySimpleDecision_TIS", &B_Hlt2Topo2BodySimpleDecision_TIS, &b_B_Hlt2Topo2BodySimpleDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2Topo2BodySimpleDecision_TOS", &B_Hlt2Topo2BodySimpleDecision_TOS, &b_B_Hlt2Topo2BodySimpleDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2Topo3BodyBBDTDecision_Dec", &B_Hlt2Topo3BodyBBDTDecision_Dec, &b_B_Hlt2Topo3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2Topo3BodyBBDTDecision_TIS", &B_Hlt2Topo3BodyBBDTDecision_TIS, &b_B_Hlt2Topo3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2Topo3BodyBBDTDecision_TOS", &B_Hlt2Topo3BodyBBDTDecision_TOS, &b_B_Hlt2Topo3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2Topo3BodySimpleDecision_Dec", &B_Hlt2Topo3BodySimpleDecision_Dec, &b_B_Hlt2Topo3BodySimpleDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2Topo3BodySimpleDecision_TIS", &B_Hlt2Topo3BodySimpleDecision_TIS, &b_B_Hlt2Topo3BodySimpleDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2Topo3BodySimpleDecision_TOS", &B_Hlt2Topo3BodySimpleDecision_TOS, &b_B_Hlt2Topo3BodySimpleDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2Topo4BodyBBDTDecision_Dec", &B_Hlt2Topo4BodyBBDTDecision_Dec, &b_B_Hlt2Topo4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2Topo4BodyBBDTDecision_TIS", &B_Hlt2Topo4BodyBBDTDecision_TIS, &b_B_Hlt2Topo4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2Topo4BodyBBDTDecision_TOS", &B_Hlt2Topo4BodyBBDTDecision_TOS, &b_B_Hlt2Topo4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2Topo4BodySimpleDecision_Dec", &B_Hlt2Topo4BodySimpleDecision_Dec, &b_B_Hlt2Topo4BodySimpleDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2Topo4BodySimpleDecision_TIS", &B_Hlt2Topo4BodySimpleDecision_TIS, &b_B_Hlt2Topo4BodySimpleDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2Topo4BodySimpleDecision_TOS", &B_Hlt2Topo4BodySimpleDecision_TOS, &b_B_Hlt2Topo4BodySimpleDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDecision_Dec", &B_Hlt2DiMuonDecision_Dec, &b_B_Hlt2DiMuonDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonDecision_TIS", &B_Hlt2DiMuonDecision_TIS, &b_B_Hlt2DiMuonDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDecision_TOS", &B_Hlt2DiMuonDecision_TOS, &b_B_Hlt2DiMuonDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonBDecision_Dec", &B_Hlt2DiMuonBDecision_Dec, &b_B_Hlt2DiMuonBDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonBDecision_TIS", &B_Hlt2DiMuonBDecision_TIS, &b_B_Hlt2DiMuonBDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonBDecision_TOS", &B_Hlt2DiMuonBDecision_TOS, &b_B_Hlt2DiMuonBDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedDecision_Dec", &B_Hlt2DiMuonDetachedDecision_Dec, &b_B_Hlt2DiMuonDetachedDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedDecision_TIS", &B_Hlt2DiMuonDetachedDecision_TIS, &b_B_Hlt2DiMuonDetachedDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedDecision_TOS", &B_Hlt2DiMuonDetachedDecision_TOS, &b_B_Hlt2DiMuonDetachedDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedHeavyDecision_Dec", &B_Hlt2DiMuonDetachedHeavyDecision_Dec, &b_B_Hlt2DiMuonDetachedHeavyDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedHeavyDecision_TIS", &B_Hlt2DiMuonDetachedHeavyDecision_TIS, &b_B_Hlt2DiMuonDetachedHeavyDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedHeavyDecision_TOS", &B_Hlt2DiMuonDetachedHeavyDecision_TOS, &b_B_Hlt2DiMuonDetachedHeavyDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedJPsiDecision_Dec", &B_Hlt2DiMuonDetachedJPsiDecision_Dec, &b_B_Hlt2DiMuonDetachedJPsiDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedJPsiDecision_TIS", &B_Hlt2DiMuonDetachedJPsiDecision_TIS, &b_B_Hlt2DiMuonDetachedJPsiDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedJPsiDecision_TOS", &B_Hlt2DiMuonDetachedJPsiDecision_TOS, &b_B_Hlt2DiMuonDetachedJPsiDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedPsi2SDecision_Dec", &B_Hlt2DiMuonDetachedPsi2SDecision_Dec, &b_B_Hlt2DiMuonDetachedPsi2SDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedPsi2SDecision_TIS", &B_Hlt2DiMuonDetachedPsi2SDecision_TIS, &b_B_Hlt2DiMuonDetachedPsi2SDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedPsi2SDecision_TOS", &B_Hlt2DiMuonDetachedPsi2SDecision_TOS, &b_B_Hlt2DiMuonDetachedPsi2SDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonJPsiDecision_Dec", &B_Hlt2DiMuonJPsiDecision_Dec, &b_B_Hlt2DiMuonJPsiDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonJPsiDecision_TIS", &B_Hlt2DiMuonJPsiDecision_TIS, &b_B_Hlt2DiMuonJPsiDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonJPsiDecision_TOS", &B_Hlt2DiMuonJPsiDecision_TOS, &b_B_Hlt2DiMuonJPsiDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonJPsiHighPTDecision_Dec", &B_Hlt2DiMuonJPsiHighPTDecision_Dec, &b_B_Hlt2DiMuonJPsiHighPTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonJPsiHighPTDecision_TIS", &B_Hlt2DiMuonJPsiHighPTDecision_TIS, &b_B_Hlt2DiMuonJPsiHighPTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonJPsiHighPTDecision_TOS", &B_Hlt2DiMuonJPsiHighPTDecision_TOS, &b_B_Hlt2DiMuonJPsiHighPTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonLowMassDecision_Dec", &B_Hlt2DiMuonLowMassDecision_Dec, &b_B_Hlt2DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonLowMassDecision_TIS", &B_Hlt2DiMuonLowMassDecision_TIS, &b_B_Hlt2DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonLowMassDecision_TOS", &B_Hlt2DiMuonLowMassDecision_TOS, &b_B_Hlt2DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonPsi2SDecision_Dec", &B_Hlt2DiMuonPsi2SDecision_Dec, &b_B_Hlt2DiMuonPsi2SDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonPsi2SDecision_TIS", &B_Hlt2DiMuonPsi2SDecision_TIS, &b_B_Hlt2DiMuonPsi2SDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonPsi2SDecision_TOS", &B_Hlt2DiMuonPsi2SDecision_TOS, &b_B_Hlt2DiMuonPsi2SDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonPsi2SHighPTDecision_Dec", &B_Hlt2DiMuonPsi2SHighPTDecision_Dec, &b_B_Hlt2DiMuonPsi2SHighPTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonPsi2SHighPTDecision_TIS", &B_Hlt2DiMuonPsi2SHighPTDecision_TIS, &b_B_Hlt2DiMuonPsi2SHighPTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonPsi2SHighPTDecision_TOS", &B_Hlt2DiMuonPsi2SHighPTDecision_TOS, &b_B_Hlt2DiMuonPsi2SHighPTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2LowMultMuonDecision_Dec", &B_Hlt2LowMultMuonDecision_Dec, &b_B_Hlt2LowMultMuonDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2LowMultMuonDecision_TIS", &B_Hlt2LowMultMuonDecision_TIS, &b_B_Hlt2LowMultMuonDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2LowMultMuonDecision_TOS", &B_Hlt2LowMultMuonDecision_TOS, &b_B_Hlt2LowMultMuonDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2MuonFromHLT1Decision_Dec", &B_Hlt2MuonFromHLT1Decision_Dec, &b_B_Hlt2MuonFromHLT1Decision_Dec);
   fChain->SetBranchAddress("B_Hlt2MuonFromHLT1Decision_TIS", &B_Hlt2MuonFromHLT1Decision_TIS, &b_B_Hlt2MuonFromHLT1Decision_TIS);
   fChain->SetBranchAddress("B_Hlt2MuonFromHLT1Decision_TOS", &B_Hlt2MuonFromHLT1Decision_TOS, &b_B_Hlt2MuonFromHLT1Decision_TOS);
   fChain->SetBranchAddress("B_Hlt2SingleMuonDecision_Dec", &B_Hlt2SingleMuonDecision_Dec, &b_B_Hlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2SingleMuonDecision_TIS", &B_Hlt2SingleMuonDecision_TIS, &b_B_Hlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2SingleMuonDecision_TOS", &B_Hlt2SingleMuonDecision_TOS, &b_B_Hlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2SingleMuonHighPTDecision_Dec", &B_Hlt2SingleMuonHighPTDecision_Dec, &b_B_Hlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2SingleMuonHighPTDecision_TIS", &B_Hlt2SingleMuonHighPTDecision_TIS, &b_B_Hlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2SingleMuonHighPTDecision_TOS", &B_Hlt2SingleMuonHighPTDecision_TOS, &b_B_Hlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2SingleMuonLowPTDecision_Dec", &B_Hlt2SingleMuonLowPTDecision_Dec, &b_B_Hlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2SingleMuonLowPTDecision_TIS", &B_Hlt2SingleMuonLowPTDecision_TIS, &b_B_Hlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2SingleMuonLowPTDecision_TOS", &B_Hlt2SingleMuonLowPTDecision_TOS, &b_B_Hlt2SingleMuonLowPTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2SingleMuonVHighPTDecision_Dec", &B_Hlt2SingleMuonVHighPTDecision_Dec, &b_B_Hlt2SingleMuonVHighPTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2SingleMuonVHighPTDecision_TIS", &B_Hlt2SingleMuonVHighPTDecision_TIS, &b_B_Hlt2SingleMuonVHighPTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2SingleMuonVHighPTDecision_TOS", &B_Hlt2SingleMuonVHighPTDecision_TOS, &b_B_Hlt2SingleMuonVHighPTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2TopoMu2BodyBBDTDecision_Dec", &B_Hlt2TopoMu2BodyBBDTDecision_Dec, &b_B_Hlt2TopoMu2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2TopoMu2BodyBBDTDecision_TIS", &B_Hlt2TopoMu2BodyBBDTDecision_TIS, &b_B_Hlt2TopoMu2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2TopoMu2BodyBBDTDecision_TOS", &B_Hlt2TopoMu2BodyBBDTDecision_TOS, &b_B_Hlt2TopoMu2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2TopoMu3BodyBBDTDecision_Dec", &B_Hlt2TopoMu3BodyBBDTDecision_Dec, &b_B_Hlt2TopoMu3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2TopoMu3BodyBBDTDecision_TIS", &B_Hlt2TopoMu3BodyBBDTDecision_TIS, &b_B_Hlt2TopoMu3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2TopoMu3BodyBBDTDecision_TOS", &B_Hlt2TopoMu3BodyBBDTDecision_TOS, &b_B_Hlt2TopoMu3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2TopoMu4BodyBBDTDecision_Dec", &B_Hlt2TopoMu4BodyBBDTDecision_Dec, &b_B_Hlt2TopoMu4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2TopoMu4BodyBBDTDecision_TIS", &B_Hlt2TopoMu4BodyBBDTDecision_TIS, &b_B_Hlt2TopoMu4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2TopoMu4BodyBBDTDecision_TOS", &B_Hlt2TopoMu4BodyBBDTDecision_TOS, &b_B_Hlt2TopoMu4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2diPhotonDiMuonDecision_Dec", &B_Hlt2diPhotonDiMuonDecision_Dec, &b_B_Hlt2diPhotonDiMuonDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2diPhotonDiMuonDecision_TIS", &B_Hlt2diPhotonDiMuonDecision_TIS, &b_B_Hlt2diPhotonDiMuonDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2diPhotonDiMuonDecision_TOS", &B_Hlt2diPhotonDiMuonDecision_TOS, &b_B_Hlt2diPhotonDiMuonDecision_TOS);
   fChain->SetBranchAddress("Lambda0_MINIP", &Lambda0_MINIP, &b_Lambda0_MINIP);
   fChain->SetBranchAddress("Lambda0_MINIPCHI2", &Lambda0_MINIPCHI2, &b_Lambda0_MINIPCHI2);
   fChain->SetBranchAddress("Lambda0_MINIPNEXTBEST", &Lambda0_MINIPNEXTBEST, &b_Lambda0_MINIPNEXTBEST);
   fChain->SetBranchAddress("Lambda0_MINIPCHI2NEXTBEST", &Lambda0_MINIPCHI2NEXTBEST, &b_Lambda0_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("Lambda0_AllIP", Lambda0_AllIP, &b_Lambda0_AllIP);
   fChain->SetBranchAddress("Lambda0_AllIPchi2", Lambda0_AllIPchi2, &b_Lambda0_AllIPchi2);
   fChain->SetBranchAddress("Lambda0_ENDVERTEX_X", &Lambda0_ENDVERTEX_X, &b_Lambda0_ENDVERTEX_X);
   fChain->SetBranchAddress("Lambda0_ENDVERTEX_Y", &Lambda0_ENDVERTEX_Y, &b_Lambda0_ENDVERTEX_Y);
   fChain->SetBranchAddress("Lambda0_ENDVERTEX_Z", &Lambda0_ENDVERTEX_Z, &b_Lambda0_ENDVERTEX_Z);
   fChain->SetBranchAddress("Lambda0_ENDVERTEX_XERR", &Lambda0_ENDVERTEX_XERR, &b_Lambda0_ENDVERTEX_XERR);
   fChain->SetBranchAddress("Lambda0_ENDVERTEX_YERR", &Lambda0_ENDVERTEX_YERR, &b_Lambda0_ENDVERTEX_YERR);
   fChain->SetBranchAddress("Lambda0_ENDVERTEX_ZERR", &Lambda0_ENDVERTEX_ZERR, &b_Lambda0_ENDVERTEX_ZERR);
   fChain->SetBranchAddress("Lambda0_ENDVERTEX_CHI2", &Lambda0_ENDVERTEX_CHI2, &b_Lambda0_ENDVERTEX_CHI2);
   fChain->SetBranchAddress("Lambda0_ENDVERTEX_NDOF", &Lambda0_ENDVERTEX_NDOF, &b_Lambda0_ENDVERTEX_NDOF);
   fChain->SetBranchAddress("Lambda0_ENDVERTEX_COV_", Lambda0_ENDVERTEX_COV_, &b_Lambda0_ENDVERTEX_COV_);
   fChain->SetBranchAddress("Lambda0_OWNPV_X", &Lambda0_OWNPV_X, &b_Lambda0_OWNPV_X);
   fChain->SetBranchAddress("Lambda0_OWNPV_Y", &Lambda0_OWNPV_Y, &b_Lambda0_OWNPV_Y);
   fChain->SetBranchAddress("Lambda0_OWNPV_Z", &Lambda0_OWNPV_Z, &b_Lambda0_OWNPV_Z);
   fChain->SetBranchAddress("Lambda0_OWNPV_XERR", &Lambda0_OWNPV_XERR, &b_Lambda0_OWNPV_XERR);
   fChain->SetBranchAddress("Lambda0_OWNPV_YERR", &Lambda0_OWNPV_YERR, &b_Lambda0_OWNPV_YERR);
   fChain->SetBranchAddress("Lambda0_OWNPV_ZERR", &Lambda0_OWNPV_ZERR, &b_Lambda0_OWNPV_ZERR);
   fChain->SetBranchAddress("Lambda0_OWNPV_CHI2", &Lambda0_OWNPV_CHI2, &b_Lambda0_OWNPV_CHI2);
   fChain->SetBranchAddress("Lambda0_OWNPV_NDOF", &Lambda0_OWNPV_NDOF, &b_Lambda0_OWNPV_NDOF);
   fChain->SetBranchAddress("Lambda0_OWNPV_COV_", Lambda0_OWNPV_COV_, &b_Lambda0_OWNPV_COV_);
   fChain->SetBranchAddress("Lambda0_IP_OWNPV", &Lambda0_IP_OWNPV, &b_Lambda0_IP_OWNPV);
   fChain->SetBranchAddress("Lambda0_IPCHI2_OWNPV", &Lambda0_IPCHI2_OWNPV, &b_Lambda0_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Lambda0_FD_OWNPV", &Lambda0_FD_OWNPV, &b_Lambda0_FD_OWNPV);
   fChain->SetBranchAddress("Lambda0_FDCHI2_OWNPV", &Lambda0_FDCHI2_OWNPV, &b_Lambda0_FDCHI2_OWNPV);
   fChain->SetBranchAddress("Lambda0_DIRA_OWNPV", &Lambda0_DIRA_OWNPV, &b_Lambda0_DIRA_OWNPV);
   fChain->SetBranchAddress("Lambda0_TOPPV_X", &Lambda0_TOPPV_X, &b_Lambda0_TOPPV_X);
   fChain->SetBranchAddress("Lambda0_TOPPV_Y", &Lambda0_TOPPV_Y, &b_Lambda0_TOPPV_Y);
   fChain->SetBranchAddress("Lambda0_TOPPV_Z", &Lambda0_TOPPV_Z, &b_Lambda0_TOPPV_Z);
   fChain->SetBranchAddress("Lambda0_TOPPV_XERR", &Lambda0_TOPPV_XERR, &b_Lambda0_TOPPV_XERR);
   fChain->SetBranchAddress("Lambda0_TOPPV_YERR", &Lambda0_TOPPV_YERR, &b_Lambda0_TOPPV_YERR);
   fChain->SetBranchAddress("Lambda0_TOPPV_ZERR", &Lambda0_TOPPV_ZERR, &b_Lambda0_TOPPV_ZERR);
   fChain->SetBranchAddress("Lambda0_TOPPV_CHI2", &Lambda0_TOPPV_CHI2, &b_Lambda0_TOPPV_CHI2);
   fChain->SetBranchAddress("Lambda0_TOPPV_NDOF", &Lambda0_TOPPV_NDOF, &b_Lambda0_TOPPV_NDOF);
   fChain->SetBranchAddress("Lambda0_TOPPV_COV_", Lambda0_TOPPV_COV_, &b_Lambda0_TOPPV_COV_);
   fChain->SetBranchAddress("Lambda0_IP_TOPPV", &Lambda0_IP_TOPPV, &b_Lambda0_IP_TOPPV);
   fChain->SetBranchAddress("Lambda0_IPCHI2_TOPPV", &Lambda0_IPCHI2_TOPPV, &b_Lambda0_IPCHI2_TOPPV);
   fChain->SetBranchAddress("Lambda0_FD_TOPPV", &Lambda0_FD_TOPPV, &b_Lambda0_FD_TOPPV);
   fChain->SetBranchAddress("Lambda0_FDCHI2_TOPPV", &Lambda0_FDCHI2_TOPPV, &b_Lambda0_FDCHI2_TOPPV);
   fChain->SetBranchAddress("Lambda0_DIRA_TOPPV", &Lambda0_DIRA_TOPPV, &b_Lambda0_DIRA_TOPPV);
   fChain->SetBranchAddress("Lambda0_ORIVX_X", &Lambda0_ORIVX_X, &b_Lambda0_ORIVX_X);
   fChain->SetBranchAddress("Lambda0_ORIVX_Y", &Lambda0_ORIVX_Y, &b_Lambda0_ORIVX_Y);
   fChain->SetBranchAddress("Lambda0_ORIVX_Z", &Lambda0_ORIVX_Z, &b_Lambda0_ORIVX_Z);
   fChain->SetBranchAddress("Lambda0_ORIVX_XERR", &Lambda0_ORIVX_XERR, &b_Lambda0_ORIVX_XERR);
   fChain->SetBranchAddress("Lambda0_ORIVX_YERR", &Lambda0_ORIVX_YERR, &b_Lambda0_ORIVX_YERR);
   fChain->SetBranchAddress("Lambda0_ORIVX_ZERR", &Lambda0_ORIVX_ZERR, &b_Lambda0_ORIVX_ZERR);
   fChain->SetBranchAddress("Lambda0_ORIVX_CHI2", &Lambda0_ORIVX_CHI2, &b_Lambda0_ORIVX_CHI2);
   fChain->SetBranchAddress("Lambda0_ORIVX_NDOF", &Lambda0_ORIVX_NDOF, &b_Lambda0_ORIVX_NDOF);
   fChain->SetBranchAddress("Lambda0_ORIVX_COV_", Lambda0_ORIVX_COV_, &b_Lambda0_ORIVX_COV_);
   fChain->SetBranchAddress("Lambda0_IP_ORIVX", &Lambda0_IP_ORIVX, &b_Lambda0_IP_ORIVX);
   fChain->SetBranchAddress("Lambda0_IPCHI2_ORIVX", &Lambda0_IPCHI2_ORIVX, &b_Lambda0_IPCHI2_ORIVX);
   fChain->SetBranchAddress("Lambda0_FD_ORIVX", &Lambda0_FD_ORIVX, &b_Lambda0_FD_ORIVX);
   fChain->SetBranchAddress("Lambda0_FDCHI2_ORIVX", &Lambda0_FDCHI2_ORIVX, &b_Lambda0_FDCHI2_ORIVX);
   fChain->SetBranchAddress("Lambda0_DIRA_ORIVX", &Lambda0_DIRA_ORIVX, &b_Lambda0_DIRA_ORIVX);
   fChain->SetBranchAddress("Lambda0_P", &Lambda0_P, &b_Lambda0_P);
   fChain->SetBranchAddress("Lambda0_PT", &Lambda0_PT, &b_Lambda0_PT);
   fChain->SetBranchAddress("Lambda0_PE", &Lambda0_PE, &b_Lambda0_PE);
   fChain->SetBranchAddress("Lambda0_PX", &Lambda0_PX, &b_Lambda0_PX);
   fChain->SetBranchAddress("Lambda0_PY", &Lambda0_PY, &b_Lambda0_PY);
   fChain->SetBranchAddress("Lambda0_PZ", &Lambda0_PZ, &b_Lambda0_PZ);
   fChain->SetBranchAddress("Lambda0_REFPX", &Lambda0_REFPX, &b_Lambda0_REFPX);
   fChain->SetBranchAddress("Lambda0_REFPY", &Lambda0_REFPY, &b_Lambda0_REFPY);
   fChain->SetBranchAddress("Lambda0_REFPZ", &Lambda0_REFPZ, &b_Lambda0_REFPZ);
   fChain->SetBranchAddress("Lambda0_MM", &Lambda0_MM, &b_Lambda0_MM);
   fChain->SetBranchAddress("Lambda0_MMERR", &Lambda0_MMERR, &b_Lambda0_MMERR);
   fChain->SetBranchAddress("Lambda0_M", &Lambda0_M, &b_Lambda0_M);
   fChain->SetBranchAddress("Lambda0_M_with_pplus_piplus", &Lambda0_M_with_pplus_piplus, &b_Lambda0_M_with_pplus_piplus);
   fChain->SetBranchAddress("Lambda0_M_with_piplus_piplus", &Lambda0_M_with_piplus_piplus, &b_Lambda0_M_with_piplus_piplus);
   fChain->SetBranchAddress("Lambda0_ID", &Lambda0_ID, &b_Lambda0_ID);
   fChain->SetBranchAddress("Lambda0_TAU", &Lambda0_TAU, &b_Lambda0_TAU);
   fChain->SetBranchAddress("Lambda0_TAUERR", &Lambda0_TAUERR, &b_Lambda0_TAUERR);
   fChain->SetBranchAddress("Lambda0_TAUCHI2", &Lambda0_TAUCHI2, &b_Lambda0_TAUCHI2);
   fChain->SetBranchAddress("piminus_MINIP", &piminus_MINIP, &b_piminus_MINIP);
   fChain->SetBranchAddress("piminus_MINIPCHI2", &piminus_MINIPCHI2, &b_piminus_MINIPCHI2);
   fChain->SetBranchAddress("piminus_MINIPNEXTBEST", &piminus_MINIPNEXTBEST, &b_piminus_MINIPNEXTBEST);
   fChain->SetBranchAddress("piminus_MINIPCHI2NEXTBEST", &piminus_MINIPCHI2NEXTBEST, &b_piminus_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("piminus_AllIP", piminus_AllIP, &b_piminus_AllIP);
   fChain->SetBranchAddress("piminus_AllIPchi2", piminus_AllIPchi2, &b_piminus_AllIPchi2);
   fChain->SetBranchAddress("piminus_OWNPV_X", &piminus_OWNPV_X, &b_piminus_OWNPV_X);
   fChain->SetBranchAddress("piminus_OWNPV_Y", &piminus_OWNPV_Y, &b_piminus_OWNPV_Y);
   fChain->SetBranchAddress("piminus_OWNPV_Z", &piminus_OWNPV_Z, &b_piminus_OWNPV_Z);
   fChain->SetBranchAddress("piminus_OWNPV_XERR", &piminus_OWNPV_XERR, &b_piminus_OWNPV_XERR);
   fChain->SetBranchAddress("piminus_OWNPV_YERR", &piminus_OWNPV_YERR, &b_piminus_OWNPV_YERR);
   fChain->SetBranchAddress("piminus_OWNPV_ZERR", &piminus_OWNPV_ZERR, &b_piminus_OWNPV_ZERR);
   fChain->SetBranchAddress("piminus_OWNPV_CHI2", &piminus_OWNPV_CHI2, &b_piminus_OWNPV_CHI2);
   fChain->SetBranchAddress("piminus_OWNPV_NDOF", &piminus_OWNPV_NDOF, &b_piminus_OWNPV_NDOF);
   fChain->SetBranchAddress("piminus_OWNPV_COV_", piminus_OWNPV_COV_, &b_piminus_OWNPV_COV_);
   fChain->SetBranchAddress("piminus_IP_OWNPV", &piminus_IP_OWNPV, &b_piminus_IP_OWNPV);
   fChain->SetBranchAddress("piminus_IPCHI2_OWNPV", &piminus_IPCHI2_OWNPV, &b_piminus_IPCHI2_OWNPV);
   fChain->SetBranchAddress("piminus_TOPPV_X", &piminus_TOPPV_X, &b_piminus_TOPPV_X);
   fChain->SetBranchAddress("piminus_TOPPV_Y", &piminus_TOPPV_Y, &b_piminus_TOPPV_Y);
   fChain->SetBranchAddress("piminus_TOPPV_Z", &piminus_TOPPV_Z, &b_piminus_TOPPV_Z);
   fChain->SetBranchAddress("piminus_TOPPV_XERR", &piminus_TOPPV_XERR, &b_piminus_TOPPV_XERR);
   fChain->SetBranchAddress("piminus_TOPPV_YERR", &piminus_TOPPV_YERR, &b_piminus_TOPPV_YERR);
   fChain->SetBranchAddress("piminus_TOPPV_ZERR", &piminus_TOPPV_ZERR, &b_piminus_TOPPV_ZERR);
   fChain->SetBranchAddress("piminus_TOPPV_CHI2", &piminus_TOPPV_CHI2, &b_piminus_TOPPV_CHI2);
   fChain->SetBranchAddress("piminus_TOPPV_NDOF", &piminus_TOPPV_NDOF, &b_piminus_TOPPV_NDOF);
   fChain->SetBranchAddress("piminus_TOPPV_COV_", piminus_TOPPV_COV_, &b_piminus_TOPPV_COV_);
   fChain->SetBranchAddress("piminus_IP_TOPPV", &piminus_IP_TOPPV, &b_piminus_IP_TOPPV);
   fChain->SetBranchAddress("piminus_IPCHI2_TOPPV", &piminus_IPCHI2_TOPPV, &b_piminus_IPCHI2_TOPPV);
   fChain->SetBranchAddress("piminus_ORIVX_X", &piminus_ORIVX_X, &b_piminus_ORIVX_X);
   fChain->SetBranchAddress("piminus_ORIVX_Y", &piminus_ORIVX_Y, &b_piminus_ORIVX_Y);
   fChain->SetBranchAddress("piminus_ORIVX_Z", &piminus_ORIVX_Z, &b_piminus_ORIVX_Z);
   fChain->SetBranchAddress("piminus_ORIVX_XERR", &piminus_ORIVX_XERR, &b_piminus_ORIVX_XERR);
   fChain->SetBranchAddress("piminus_ORIVX_YERR", &piminus_ORIVX_YERR, &b_piminus_ORIVX_YERR);
   fChain->SetBranchAddress("piminus_ORIVX_ZERR", &piminus_ORIVX_ZERR, &b_piminus_ORIVX_ZERR);
   fChain->SetBranchAddress("piminus_ORIVX_CHI2", &piminus_ORIVX_CHI2, &b_piminus_ORIVX_CHI2);
   fChain->SetBranchAddress("piminus_ORIVX_NDOF", &piminus_ORIVX_NDOF, &b_piminus_ORIVX_NDOF);
   fChain->SetBranchAddress("piminus_ORIVX_COV_", piminus_ORIVX_COV_, &b_piminus_ORIVX_COV_);
   fChain->SetBranchAddress("piminus_IP_ORIVX", &piminus_IP_ORIVX, &b_piminus_IP_ORIVX);
   fChain->SetBranchAddress("piminus_IPCHI2_ORIVX", &piminus_IPCHI2_ORIVX, &b_piminus_IPCHI2_ORIVX);
   fChain->SetBranchAddress("piminus_P", &piminus_P, &b_piminus_P);
   fChain->SetBranchAddress("piminus_PT", &piminus_PT, &b_piminus_PT);
   fChain->SetBranchAddress("piminus_PE", &piminus_PE, &b_piminus_PE);
   fChain->SetBranchAddress("piminus_PX", &piminus_PX, &b_piminus_PX);
   fChain->SetBranchAddress("piminus_PY", &piminus_PY, &b_piminus_PY);
   fChain->SetBranchAddress("piminus_PZ", &piminus_PZ, &b_piminus_PZ);
   fChain->SetBranchAddress("piminus_REFPX", &piminus_REFPX, &b_piminus_REFPX);
   fChain->SetBranchAddress("piminus_REFPY", &piminus_REFPY, &b_piminus_REFPY);
   fChain->SetBranchAddress("piminus_REFPZ", &piminus_REFPZ, &b_piminus_REFPZ);
   fChain->SetBranchAddress("piminus_M", &piminus_M, &b_piminus_M);
   fChain->SetBranchAddress("piminus_AtVtx_PE", &piminus_AtVtx_PE, &b_piminus_AtVtx_PE);
   fChain->SetBranchAddress("piminus_AtVtx_PX", &piminus_AtVtx_PX, &b_piminus_AtVtx_PX);
   fChain->SetBranchAddress("piminus_AtVtx_PY", &piminus_AtVtx_PY, &b_piminus_AtVtx_PY);
   fChain->SetBranchAddress("piminus_AtVtx_PZ", &piminus_AtVtx_PZ, &b_piminus_AtVtx_PZ);
   fChain->SetBranchAddress("piminus_L0Calo_HCAL_realET", &piminus_L0Calo_HCAL_realET, &b_piminus_L0Calo_HCAL_realET);
   fChain->SetBranchAddress("piminus_L0Calo_HCAL_xProjection", &piminus_L0Calo_HCAL_xProjection, &b_piminus_L0Calo_HCAL_xProjection);
   fChain->SetBranchAddress("piminus_L0Calo_HCAL_yProjection", &piminus_L0Calo_HCAL_yProjection, &b_piminus_L0Calo_HCAL_yProjection);
   fChain->SetBranchAddress("piminus_L0Calo_HCAL_region", &piminus_L0Calo_HCAL_region, &b_piminus_L0Calo_HCAL_region);
   fChain->SetBranchAddress("piminus_ID", &piminus_ID, &b_piminus_ID);
   fChain->SetBranchAddress("piminus_PIDe", &piminus_PIDe, &b_piminus_PIDe);
   fChain->SetBranchAddress("piminus_PIDmu", &piminus_PIDmu, &b_piminus_PIDmu);
   fChain->SetBranchAddress("piminus_PIDK", &piminus_PIDK, &b_piminus_PIDK);
   fChain->SetBranchAddress("piminus_PIDp", &piminus_PIDp, &b_piminus_PIDp);
   fChain->SetBranchAddress("piminus_ProbNNe", &piminus_ProbNNe, &b_piminus_ProbNNe);
   fChain->SetBranchAddress("piminus_ProbNNk", &piminus_ProbNNk, &b_piminus_ProbNNk);
   fChain->SetBranchAddress("piminus_ProbNNp", &piminus_ProbNNp, &b_piminus_ProbNNp);
   fChain->SetBranchAddress("piminus_ProbNNpi", &piminus_ProbNNpi, &b_piminus_ProbNNpi);
   fChain->SetBranchAddress("piminus_ProbNNmu", &piminus_ProbNNmu, &b_piminus_ProbNNmu);
   fChain->SetBranchAddress("piminus_ProbNNghost", &piminus_ProbNNghost, &b_piminus_ProbNNghost);
   fChain->SetBranchAddress("piminus_hasMuon", &piminus_hasMuon, &b_piminus_hasMuon);
   fChain->SetBranchAddress("piminus_isMuon", &piminus_isMuon, &b_piminus_isMuon);
   fChain->SetBranchAddress("piminus_hasRich", &piminus_hasRich, &b_piminus_hasRich);
   fChain->SetBranchAddress("piminus_hasCalo", &piminus_hasCalo, &b_piminus_hasCalo);
   fChain->SetBranchAddress("piminus_UsedRichAerogel", &piminus_UsedRichAerogel, &b_piminus_UsedRichAerogel);
   fChain->SetBranchAddress("piminus_UsedRich1Gas", &piminus_UsedRich1Gas, &b_piminus_UsedRich1Gas);
   fChain->SetBranchAddress("piminus_UsedRich2Gas", &piminus_UsedRich2Gas, &b_piminus_UsedRich2Gas);
   fChain->SetBranchAddress("piminus_RichAboveElThres", &piminus_RichAboveElThres, &b_piminus_RichAboveElThres);
   fChain->SetBranchAddress("piminus_RichAboveMuThres", &piminus_RichAboveMuThres, &b_piminus_RichAboveMuThres);
   fChain->SetBranchAddress("piminus_RichAbovePiThres", &piminus_RichAbovePiThres, &b_piminus_RichAbovePiThres);
   fChain->SetBranchAddress("piminus_RichAboveKaThres", &piminus_RichAboveKaThres, &b_piminus_RichAboveKaThres);
   fChain->SetBranchAddress("piminus_RichAbovePrThres", &piminus_RichAbovePrThres, &b_piminus_RichAbovePrThres);
   fChain->SetBranchAddress("piminus_RichDLLe", &piminus_RichDLLe, &b_piminus_RichDLLe);
   fChain->SetBranchAddress("piminus_RichDLLmu", &piminus_RichDLLmu, &b_piminus_RichDLLmu);
   fChain->SetBranchAddress("piminus_RichDLLpi", &piminus_RichDLLpi, &b_piminus_RichDLLpi);
   fChain->SetBranchAddress("piminus_RichDLLk", &piminus_RichDLLk, &b_piminus_RichDLLk);
   fChain->SetBranchAddress("piminus_RichDLLp", &piminus_RichDLLp, &b_piminus_RichDLLp);
   fChain->SetBranchAddress("piminus_RichDLLbt", &piminus_RichDLLbt, &b_piminus_RichDLLbt);
   fChain->SetBranchAddress("piminus_InAccMuon", &piminus_InAccMuon, &b_piminus_InAccMuon);
   fChain->SetBranchAddress("piminus_isMuonLoose", &piminus_isMuonLoose, &b_piminus_isMuonLoose);
   fChain->SetBranchAddress("piminus_MuonMuLL", &piminus_MuonMuLL, &b_piminus_MuonMuLL);
   fChain->SetBranchAddress("piminus_MuonBkgLL", &piminus_MuonBkgLL, &b_piminus_MuonBkgLL);
   fChain->SetBranchAddress("piminus_MuonNShared", &piminus_MuonNShared, &b_piminus_MuonNShared);
   fChain->SetBranchAddress("piminus_InAccEcal", &piminus_InAccEcal, &b_piminus_InAccEcal);
   fChain->SetBranchAddress("piminus_CaloEcalE", &piminus_CaloEcalE, &b_piminus_CaloEcalE);
   fChain->SetBranchAddress("piminus_EcalPIDe", &piminus_EcalPIDe, &b_piminus_EcalPIDe);
   fChain->SetBranchAddress("piminus_EcalPIDmu", &piminus_EcalPIDmu, &b_piminus_EcalPIDmu);
   fChain->SetBranchAddress("piminus_InAccHcal", &piminus_InAccHcal, &b_piminus_InAccHcal);
   fChain->SetBranchAddress("piminus_CaloHcalE", &piminus_CaloHcalE, &b_piminus_CaloHcalE);
   fChain->SetBranchAddress("piminus_HcalPIDe", &piminus_HcalPIDe, &b_piminus_HcalPIDe);
   fChain->SetBranchAddress("piminus_HcalPIDmu", &piminus_HcalPIDmu, &b_piminus_HcalPIDmu);
   fChain->SetBranchAddress("piminus_InAccPrs", &piminus_InAccPrs, &b_piminus_InAccPrs);
   fChain->SetBranchAddress("piminus_PrsPIDe", &piminus_PrsPIDe, &b_piminus_PrsPIDe);
   fChain->SetBranchAddress("piminus_CaloPrsE", &piminus_CaloPrsE, &b_piminus_CaloPrsE);
   fChain->SetBranchAddress("piminus_InAccSpd", &piminus_InAccSpd, &b_piminus_InAccSpd);
   fChain->SetBranchAddress("piminus_CaloSpdE", &piminus_CaloSpdE, &b_piminus_CaloSpdE);
   fChain->SetBranchAddress("piminus_InAccBrem", &piminus_InAccBrem, &b_piminus_InAccBrem);
   fChain->SetBranchAddress("piminus_BremPIDe", &piminus_BremPIDe, &b_piminus_BremPIDe);
   fChain->SetBranchAddress("piminus_VeloCharge", &piminus_VeloCharge, &b_piminus_VeloCharge);
   fChain->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type, &b_piminus_TRACK_Type);
   fChain->SetBranchAddress("piminus_TRACK_Key", &piminus_TRACK_Key, &b_piminus_TRACK_Key);
   fChain->SetBranchAddress("piminus_TRACK_CHI2", &piminus_TRACK_CHI2, &b_piminus_TRACK_CHI2);
   fChain->SetBranchAddress("piminus_TRACK_NDOF", &piminus_TRACK_NDOF, &b_piminus_TRACK_NDOF);
   fChain->SetBranchAddress("piminus_TRACK_CHI2NDOF", &piminus_TRACK_CHI2NDOF, &b_piminus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("piminus_TRACK_PCHI2", &piminus_TRACK_PCHI2, &b_piminus_TRACK_PCHI2);
   fChain->SetBranchAddress("piminus_TRACK_VeloCHI2NDOF", &piminus_TRACK_VeloCHI2NDOF, &b_piminus_TRACK_VeloCHI2NDOF);
   fChain->SetBranchAddress("piminus_TRACK_TCHI2NDOF", &piminus_TRACK_TCHI2NDOF, &b_piminus_TRACK_TCHI2NDOF);
   fChain->SetBranchAddress("piminus_VELO_UTID", &piminus_VELO_UTID, &b_piminus_VELO_UTID);
   fChain->SetBranchAddress("piminus_TRACK_FirstMeasurementX", &piminus_TRACK_FirstMeasurementX, &b_piminus_TRACK_FirstMeasurementX);
   fChain->SetBranchAddress("piminus_TRACK_FirstMeasurementY", &piminus_TRACK_FirstMeasurementY, &b_piminus_TRACK_FirstMeasurementY);
   fChain->SetBranchAddress("piminus_TRACK_FirstMeasurementZ", &piminus_TRACK_FirstMeasurementZ, &b_piminus_TRACK_FirstMeasurementZ);
   fChain->SetBranchAddress("piminus_TRACK_MatchCHI2", &piminus_TRACK_MatchCHI2, &b_piminus_TRACK_MatchCHI2);
   fChain->SetBranchAddress("piminus_TRACK_GhostProb", &piminus_TRACK_GhostProb, &b_piminus_TRACK_GhostProb);
   fChain->SetBranchAddress("piminus_TRACK_CloneDist", &piminus_TRACK_CloneDist, &b_piminus_TRACK_CloneDist);
   fChain->SetBranchAddress("piminus_TRACK_Likelihood", &piminus_TRACK_Likelihood, &b_piminus_TRACK_Likelihood);
   fChain->SetBranchAddress("pplus_MINIP", &pplus_MINIP, &b_pplus_MINIP);
   fChain->SetBranchAddress("pplus_MINIPCHI2", &pplus_MINIPCHI2, &b_pplus_MINIPCHI2);
   fChain->SetBranchAddress("pplus_MINIPNEXTBEST", &pplus_MINIPNEXTBEST, &b_pplus_MINIPNEXTBEST);
   fChain->SetBranchAddress("pplus_MINIPCHI2NEXTBEST", &pplus_MINIPCHI2NEXTBEST, &b_pplus_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("pplus_AllIP", pplus_AllIP, &b_pplus_AllIP);
   fChain->SetBranchAddress("pplus_AllIPchi2", pplus_AllIPchi2, &b_pplus_AllIPchi2);
   fChain->SetBranchAddress("pplus_OWNPV_X", &pplus_OWNPV_X, &b_pplus_OWNPV_X);
   fChain->SetBranchAddress("pplus_OWNPV_Y", &pplus_OWNPV_Y, &b_pplus_OWNPV_Y);
   fChain->SetBranchAddress("pplus_OWNPV_Z", &pplus_OWNPV_Z, &b_pplus_OWNPV_Z);
   fChain->SetBranchAddress("pplus_OWNPV_XERR", &pplus_OWNPV_XERR, &b_pplus_OWNPV_XERR);
   fChain->SetBranchAddress("pplus_OWNPV_YERR", &pplus_OWNPV_YERR, &b_pplus_OWNPV_YERR);
   fChain->SetBranchAddress("pplus_OWNPV_ZERR", &pplus_OWNPV_ZERR, &b_pplus_OWNPV_ZERR);
   fChain->SetBranchAddress("pplus_OWNPV_CHI2", &pplus_OWNPV_CHI2, &b_pplus_OWNPV_CHI2);
   fChain->SetBranchAddress("pplus_OWNPV_NDOF", &pplus_OWNPV_NDOF, &b_pplus_OWNPV_NDOF);
   fChain->SetBranchAddress("pplus_OWNPV_COV_", pplus_OWNPV_COV_, &b_pplus_OWNPV_COV_);
   fChain->SetBranchAddress("pplus_IP_OWNPV", &pplus_IP_OWNPV, &b_pplus_IP_OWNPV);
   fChain->SetBranchAddress("pplus_IPCHI2_OWNPV", &pplus_IPCHI2_OWNPV, &b_pplus_IPCHI2_OWNPV);
   fChain->SetBranchAddress("pplus_TOPPV_X", &pplus_TOPPV_X, &b_pplus_TOPPV_X);
   fChain->SetBranchAddress("pplus_TOPPV_Y", &pplus_TOPPV_Y, &b_pplus_TOPPV_Y);
   fChain->SetBranchAddress("pplus_TOPPV_Z", &pplus_TOPPV_Z, &b_pplus_TOPPV_Z);
   fChain->SetBranchAddress("pplus_TOPPV_XERR", &pplus_TOPPV_XERR, &b_pplus_TOPPV_XERR);
   fChain->SetBranchAddress("pplus_TOPPV_YERR", &pplus_TOPPV_YERR, &b_pplus_TOPPV_YERR);
   fChain->SetBranchAddress("pplus_TOPPV_ZERR", &pplus_TOPPV_ZERR, &b_pplus_TOPPV_ZERR);
   fChain->SetBranchAddress("pplus_TOPPV_CHI2", &pplus_TOPPV_CHI2, &b_pplus_TOPPV_CHI2);
   fChain->SetBranchAddress("pplus_TOPPV_NDOF", &pplus_TOPPV_NDOF, &b_pplus_TOPPV_NDOF);
   fChain->SetBranchAddress("pplus_TOPPV_COV_", pplus_TOPPV_COV_, &b_pplus_TOPPV_COV_);
   fChain->SetBranchAddress("pplus_IP_TOPPV", &pplus_IP_TOPPV, &b_pplus_IP_TOPPV);
   fChain->SetBranchAddress("pplus_IPCHI2_TOPPV", &pplus_IPCHI2_TOPPV, &b_pplus_IPCHI2_TOPPV);
   fChain->SetBranchAddress("pplus_ORIVX_X", &pplus_ORIVX_X, &b_pplus_ORIVX_X);
   fChain->SetBranchAddress("pplus_ORIVX_Y", &pplus_ORIVX_Y, &b_pplus_ORIVX_Y);
   fChain->SetBranchAddress("pplus_ORIVX_Z", &pplus_ORIVX_Z, &b_pplus_ORIVX_Z);
   fChain->SetBranchAddress("pplus_ORIVX_XERR", &pplus_ORIVX_XERR, &b_pplus_ORIVX_XERR);
   fChain->SetBranchAddress("pplus_ORIVX_YERR", &pplus_ORIVX_YERR, &b_pplus_ORIVX_YERR);
   fChain->SetBranchAddress("pplus_ORIVX_ZERR", &pplus_ORIVX_ZERR, &b_pplus_ORIVX_ZERR);
   fChain->SetBranchAddress("pplus_ORIVX_CHI2", &pplus_ORIVX_CHI2, &b_pplus_ORIVX_CHI2);
   fChain->SetBranchAddress("pplus_ORIVX_NDOF", &pplus_ORIVX_NDOF, &b_pplus_ORIVX_NDOF);
   fChain->SetBranchAddress("pplus_ORIVX_COV_", pplus_ORIVX_COV_, &b_pplus_ORIVX_COV_);
   fChain->SetBranchAddress("pplus_IP_ORIVX", &pplus_IP_ORIVX, &b_pplus_IP_ORIVX);
   fChain->SetBranchAddress("pplus_IPCHI2_ORIVX", &pplus_IPCHI2_ORIVX, &b_pplus_IPCHI2_ORIVX);
   fChain->SetBranchAddress("pplus_P", &pplus_P, &b_pplus_P);
   fChain->SetBranchAddress("pplus_PT", &pplus_PT, &b_pplus_PT);
   fChain->SetBranchAddress("pplus_PE", &pplus_PE, &b_pplus_PE);
   fChain->SetBranchAddress("pplus_PX", &pplus_PX, &b_pplus_PX);
   fChain->SetBranchAddress("pplus_PY", &pplus_PY, &b_pplus_PY);
   fChain->SetBranchAddress("pplus_PZ", &pplus_PZ, &b_pplus_PZ);
   fChain->SetBranchAddress("pplus_REFPX", &pplus_REFPX, &b_pplus_REFPX);
   fChain->SetBranchAddress("pplus_REFPY", &pplus_REFPY, &b_pplus_REFPY);
   fChain->SetBranchAddress("pplus_REFPZ", &pplus_REFPZ, &b_pplus_REFPZ);
   fChain->SetBranchAddress("pplus_M", &pplus_M, &b_pplus_M);
   fChain->SetBranchAddress("pplus_AtVtx_PE", &pplus_AtVtx_PE, &b_pplus_AtVtx_PE);
   fChain->SetBranchAddress("pplus_AtVtx_PX", &pplus_AtVtx_PX, &b_pplus_AtVtx_PX);
   fChain->SetBranchAddress("pplus_AtVtx_PY", &pplus_AtVtx_PY, &b_pplus_AtVtx_PY);
   fChain->SetBranchAddress("pplus_AtVtx_PZ", &pplus_AtVtx_PZ, &b_pplus_AtVtx_PZ);
   fChain->SetBranchAddress("pplus_L0Calo_HCAL_realET", &pplus_L0Calo_HCAL_realET, &b_pplus_L0Calo_HCAL_realET);
   fChain->SetBranchAddress("pplus_L0Calo_HCAL_xProjection", &pplus_L0Calo_HCAL_xProjection, &b_pplus_L0Calo_HCAL_xProjection);
   fChain->SetBranchAddress("pplus_L0Calo_HCAL_yProjection", &pplus_L0Calo_HCAL_yProjection, &b_pplus_L0Calo_HCAL_yProjection);
   fChain->SetBranchAddress("pplus_L0Calo_HCAL_region", &pplus_L0Calo_HCAL_region, &b_pplus_L0Calo_HCAL_region);
   fChain->SetBranchAddress("pplus_ID", &pplus_ID, &b_pplus_ID);
   fChain->SetBranchAddress("pplus_PIDe", &pplus_PIDe, &b_pplus_PIDe);
   fChain->SetBranchAddress("pplus_PIDmu", &pplus_PIDmu, &b_pplus_PIDmu);
   fChain->SetBranchAddress("pplus_PIDK", &pplus_PIDK, &b_pplus_PIDK);
   fChain->SetBranchAddress("pplus_PIDp", &pplus_PIDp, &b_pplus_PIDp);
   fChain->SetBranchAddress("pplus_ProbNNe", &pplus_ProbNNe, &b_pplus_ProbNNe);
   fChain->SetBranchAddress("pplus_ProbNNk", &pplus_ProbNNk, &b_pplus_ProbNNk);
   fChain->SetBranchAddress("pplus_ProbNNp", &pplus_ProbNNp, &b_pplus_ProbNNp);
   fChain->SetBranchAddress("pplus_ProbNNpi", &pplus_ProbNNpi, &b_pplus_ProbNNpi);
   fChain->SetBranchAddress("pplus_ProbNNmu", &pplus_ProbNNmu, &b_pplus_ProbNNmu);
   fChain->SetBranchAddress("pplus_ProbNNghost", &pplus_ProbNNghost, &b_pplus_ProbNNghost);
   fChain->SetBranchAddress("pplus_hasMuon", &pplus_hasMuon, &b_pplus_hasMuon);
   fChain->SetBranchAddress("pplus_isMuon", &pplus_isMuon, &b_pplus_isMuon);
   fChain->SetBranchAddress("pplus_hasRich", &pplus_hasRich, &b_pplus_hasRich);
   fChain->SetBranchAddress("pplus_hasCalo", &pplus_hasCalo, &b_pplus_hasCalo);
   fChain->SetBranchAddress("pplus_UsedRichAerogel", &pplus_UsedRichAerogel, &b_pplus_UsedRichAerogel);
   fChain->SetBranchAddress("pplus_UsedRich1Gas", &pplus_UsedRich1Gas, &b_pplus_UsedRich1Gas);
   fChain->SetBranchAddress("pplus_UsedRich2Gas", &pplus_UsedRich2Gas, &b_pplus_UsedRich2Gas);
   fChain->SetBranchAddress("pplus_RichAboveElThres", &pplus_RichAboveElThres, &b_pplus_RichAboveElThres);
   fChain->SetBranchAddress("pplus_RichAboveMuThres", &pplus_RichAboveMuThres, &b_pplus_RichAboveMuThres);
   fChain->SetBranchAddress("pplus_RichAbovePiThres", &pplus_RichAbovePiThres, &b_pplus_RichAbovePiThres);
   fChain->SetBranchAddress("pplus_RichAboveKaThres", &pplus_RichAboveKaThres, &b_pplus_RichAboveKaThres);
   fChain->SetBranchAddress("pplus_RichAbovePrThres", &pplus_RichAbovePrThres, &b_pplus_RichAbovePrThres);
   fChain->SetBranchAddress("pplus_RichDLLe", &pplus_RichDLLe, &b_pplus_RichDLLe);
   fChain->SetBranchAddress("pplus_RichDLLmu", &pplus_RichDLLmu, &b_pplus_RichDLLmu);
   fChain->SetBranchAddress("pplus_RichDLLpi", &pplus_RichDLLpi, &b_pplus_RichDLLpi);
   fChain->SetBranchAddress("pplus_RichDLLk", &pplus_RichDLLk, &b_pplus_RichDLLk);
   fChain->SetBranchAddress("pplus_RichDLLp", &pplus_RichDLLp, &b_pplus_RichDLLp);
   fChain->SetBranchAddress("pplus_RichDLLbt", &pplus_RichDLLbt, &b_pplus_RichDLLbt);
   fChain->SetBranchAddress("pplus_InAccMuon", &pplus_InAccMuon, &b_pplus_InAccMuon);
   fChain->SetBranchAddress("pplus_isMuonLoose", &pplus_isMuonLoose, &b_pplus_isMuonLoose);
   fChain->SetBranchAddress("pplus_MuonMuLL", &pplus_MuonMuLL, &b_pplus_MuonMuLL);
   fChain->SetBranchAddress("pplus_MuonBkgLL", &pplus_MuonBkgLL, &b_pplus_MuonBkgLL);
   fChain->SetBranchAddress("pplus_MuonNShared", &pplus_MuonNShared, &b_pplus_MuonNShared);
   fChain->SetBranchAddress("pplus_InAccEcal", &pplus_InAccEcal, &b_pplus_InAccEcal);
   fChain->SetBranchAddress("pplus_CaloEcalE", &pplus_CaloEcalE, &b_pplus_CaloEcalE);
   fChain->SetBranchAddress("pplus_EcalPIDe", &pplus_EcalPIDe, &b_pplus_EcalPIDe);
   fChain->SetBranchAddress("pplus_EcalPIDmu", &pplus_EcalPIDmu, &b_pplus_EcalPIDmu);
   fChain->SetBranchAddress("pplus_InAccHcal", &pplus_InAccHcal, &b_pplus_InAccHcal);
   fChain->SetBranchAddress("pplus_CaloHcalE", &pplus_CaloHcalE, &b_pplus_CaloHcalE);
   fChain->SetBranchAddress("pplus_HcalPIDe", &pplus_HcalPIDe, &b_pplus_HcalPIDe);
   fChain->SetBranchAddress("pplus_HcalPIDmu", &pplus_HcalPIDmu, &b_pplus_HcalPIDmu);
   fChain->SetBranchAddress("pplus_InAccPrs", &pplus_InAccPrs, &b_pplus_InAccPrs);
   fChain->SetBranchAddress("pplus_PrsPIDe", &pplus_PrsPIDe, &b_pplus_PrsPIDe);
   fChain->SetBranchAddress("pplus_CaloPrsE", &pplus_CaloPrsE, &b_pplus_CaloPrsE);
   fChain->SetBranchAddress("pplus_InAccSpd", &pplus_InAccSpd, &b_pplus_InAccSpd);
   fChain->SetBranchAddress("pplus_CaloSpdE", &pplus_CaloSpdE, &b_pplus_CaloSpdE);
   fChain->SetBranchAddress("pplus_InAccBrem", &pplus_InAccBrem, &b_pplus_InAccBrem);
   fChain->SetBranchAddress("pplus_BremPIDe", &pplus_BremPIDe, &b_pplus_BremPIDe);
   fChain->SetBranchAddress("pplus_VeloCharge", &pplus_VeloCharge, &b_pplus_VeloCharge);
   fChain->SetBranchAddress("pplus_TRACK_Type", &pplus_TRACK_Type, &b_pplus_TRACK_Type);
   fChain->SetBranchAddress("pplus_TRACK_Key", &pplus_TRACK_Key, &b_pplus_TRACK_Key);
   fChain->SetBranchAddress("pplus_TRACK_CHI2", &pplus_TRACK_CHI2, &b_pplus_TRACK_CHI2);
   fChain->SetBranchAddress("pplus_TRACK_NDOF", &pplus_TRACK_NDOF, &b_pplus_TRACK_NDOF);
   fChain->SetBranchAddress("pplus_TRACK_CHI2NDOF", &pplus_TRACK_CHI2NDOF, &b_pplus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("pplus_TRACK_PCHI2", &pplus_TRACK_PCHI2, &b_pplus_TRACK_PCHI2);
   fChain->SetBranchAddress("pplus_TRACK_VeloCHI2NDOF", &pplus_TRACK_VeloCHI2NDOF, &b_pplus_TRACK_VeloCHI2NDOF);
   fChain->SetBranchAddress("pplus_TRACK_TCHI2NDOF", &pplus_TRACK_TCHI2NDOF, &b_pplus_TRACK_TCHI2NDOF);
   fChain->SetBranchAddress("pplus_VELO_UTID", &pplus_VELO_UTID, &b_pplus_VELO_UTID);
   fChain->SetBranchAddress("pplus_TRACK_FirstMeasurementX", &pplus_TRACK_FirstMeasurementX, &b_pplus_TRACK_FirstMeasurementX);
   fChain->SetBranchAddress("pplus_TRACK_FirstMeasurementY", &pplus_TRACK_FirstMeasurementY, &b_pplus_TRACK_FirstMeasurementY);
   fChain->SetBranchAddress("pplus_TRACK_FirstMeasurementZ", &pplus_TRACK_FirstMeasurementZ, &b_pplus_TRACK_FirstMeasurementZ);
   fChain->SetBranchAddress("pplus_TRACK_MatchCHI2", &pplus_TRACK_MatchCHI2, &b_pplus_TRACK_MatchCHI2);
   fChain->SetBranchAddress("pplus_TRACK_GhostProb", &pplus_TRACK_GhostProb, &b_pplus_TRACK_GhostProb);
   fChain->SetBranchAddress("pplus_TRACK_CloneDist", &pplus_TRACK_CloneDist, &b_pplus_TRACK_CloneDist);
   fChain->SetBranchAddress("pplus_TRACK_Likelihood", &pplus_TRACK_Likelihood, &b_pplus_TRACK_Likelihood);
   fChain->SetBranchAddress("Psi_MINIP", &Psi_MINIP, &b_Psi_MINIP);
   fChain->SetBranchAddress("Psi_MINIPCHI2", &Psi_MINIPCHI2, &b_Psi_MINIPCHI2);
   fChain->SetBranchAddress("Psi_MINIPNEXTBEST", &Psi_MINIPNEXTBEST, &b_Psi_MINIPNEXTBEST);
   fChain->SetBranchAddress("Psi_MINIPCHI2NEXTBEST", &Psi_MINIPCHI2NEXTBEST, &b_Psi_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("Psi_AllIP", Psi_AllIP, &b_Psi_AllIP);
   fChain->SetBranchAddress("Psi_AllIPchi2", Psi_AllIPchi2, &b_Psi_AllIPchi2);
   fChain->SetBranchAddress("Psi_ENDVERTEX_X", &Psi_ENDVERTEX_X, &b_Psi_ENDVERTEX_X);
   fChain->SetBranchAddress("Psi_ENDVERTEX_Y", &Psi_ENDVERTEX_Y, &b_Psi_ENDVERTEX_Y);
   fChain->SetBranchAddress("Psi_ENDVERTEX_Z", &Psi_ENDVERTEX_Z, &b_Psi_ENDVERTEX_Z);
   fChain->SetBranchAddress("Psi_ENDVERTEX_XERR", &Psi_ENDVERTEX_XERR, &b_Psi_ENDVERTEX_XERR);
   fChain->SetBranchAddress("Psi_ENDVERTEX_YERR", &Psi_ENDVERTEX_YERR, &b_Psi_ENDVERTEX_YERR);
   fChain->SetBranchAddress("Psi_ENDVERTEX_ZERR", &Psi_ENDVERTEX_ZERR, &b_Psi_ENDVERTEX_ZERR);
   fChain->SetBranchAddress("Psi_ENDVERTEX_CHI2", &Psi_ENDVERTEX_CHI2, &b_Psi_ENDVERTEX_CHI2);
   fChain->SetBranchAddress("Psi_ENDVERTEX_NDOF", &Psi_ENDVERTEX_NDOF, &b_Psi_ENDVERTEX_NDOF);
   fChain->SetBranchAddress("Psi_ENDVERTEX_COV_", Psi_ENDVERTEX_COV_, &b_Psi_ENDVERTEX_COV_);
   fChain->SetBranchAddress("Psi_OWNPV_X", &Psi_OWNPV_X, &b_Psi_OWNPV_X);
   fChain->SetBranchAddress("Psi_OWNPV_Y", &Psi_OWNPV_Y, &b_Psi_OWNPV_Y);
   fChain->SetBranchAddress("Psi_OWNPV_Z", &Psi_OWNPV_Z, &b_Psi_OWNPV_Z);
   fChain->SetBranchAddress("Psi_OWNPV_XERR", &Psi_OWNPV_XERR, &b_Psi_OWNPV_XERR);
   fChain->SetBranchAddress("Psi_OWNPV_YERR", &Psi_OWNPV_YERR, &b_Psi_OWNPV_YERR);
   fChain->SetBranchAddress("Psi_OWNPV_ZERR", &Psi_OWNPV_ZERR, &b_Psi_OWNPV_ZERR);
   fChain->SetBranchAddress("Psi_OWNPV_CHI2", &Psi_OWNPV_CHI2, &b_Psi_OWNPV_CHI2);
   fChain->SetBranchAddress("Psi_OWNPV_NDOF", &Psi_OWNPV_NDOF, &b_Psi_OWNPV_NDOF);
   fChain->SetBranchAddress("Psi_OWNPV_COV_", Psi_OWNPV_COV_, &b_Psi_OWNPV_COV_);
   fChain->SetBranchAddress("Psi_IP_OWNPV", &Psi_IP_OWNPV, &b_Psi_IP_OWNPV);
   fChain->SetBranchAddress("Psi_IPCHI2_OWNPV", &Psi_IPCHI2_OWNPV, &b_Psi_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Psi_FD_OWNPV", &Psi_FD_OWNPV, &b_Psi_FD_OWNPV);
   fChain->SetBranchAddress("Psi_FDCHI2_OWNPV", &Psi_FDCHI2_OWNPV, &b_Psi_FDCHI2_OWNPV);
   fChain->SetBranchAddress("Psi_DIRA_OWNPV", &Psi_DIRA_OWNPV, &b_Psi_DIRA_OWNPV);
   fChain->SetBranchAddress("Psi_TOPPV_X", &Psi_TOPPV_X, &b_Psi_TOPPV_X);
   fChain->SetBranchAddress("Psi_TOPPV_Y", &Psi_TOPPV_Y, &b_Psi_TOPPV_Y);
   fChain->SetBranchAddress("Psi_TOPPV_Z", &Psi_TOPPV_Z, &b_Psi_TOPPV_Z);
   fChain->SetBranchAddress("Psi_TOPPV_XERR", &Psi_TOPPV_XERR, &b_Psi_TOPPV_XERR);
   fChain->SetBranchAddress("Psi_TOPPV_YERR", &Psi_TOPPV_YERR, &b_Psi_TOPPV_YERR);
   fChain->SetBranchAddress("Psi_TOPPV_ZERR", &Psi_TOPPV_ZERR, &b_Psi_TOPPV_ZERR);
   fChain->SetBranchAddress("Psi_TOPPV_CHI2", &Psi_TOPPV_CHI2, &b_Psi_TOPPV_CHI2);
   fChain->SetBranchAddress("Psi_TOPPV_NDOF", &Psi_TOPPV_NDOF, &b_Psi_TOPPV_NDOF);
   fChain->SetBranchAddress("Psi_TOPPV_COV_", Psi_TOPPV_COV_, &b_Psi_TOPPV_COV_);
   fChain->SetBranchAddress("Psi_IP_TOPPV", &Psi_IP_TOPPV, &b_Psi_IP_TOPPV);
   fChain->SetBranchAddress("Psi_IPCHI2_TOPPV", &Psi_IPCHI2_TOPPV, &b_Psi_IPCHI2_TOPPV);
   fChain->SetBranchAddress("Psi_FD_TOPPV", &Psi_FD_TOPPV, &b_Psi_FD_TOPPV);
   fChain->SetBranchAddress("Psi_FDCHI2_TOPPV", &Psi_FDCHI2_TOPPV, &b_Psi_FDCHI2_TOPPV);
   fChain->SetBranchAddress("Psi_DIRA_TOPPV", &Psi_DIRA_TOPPV, &b_Psi_DIRA_TOPPV);
   fChain->SetBranchAddress("Psi_ORIVX_X", &Psi_ORIVX_X, &b_Psi_ORIVX_X);
   fChain->SetBranchAddress("Psi_ORIVX_Y", &Psi_ORIVX_Y, &b_Psi_ORIVX_Y);
   fChain->SetBranchAddress("Psi_ORIVX_Z", &Psi_ORIVX_Z, &b_Psi_ORIVX_Z);
   fChain->SetBranchAddress("Psi_ORIVX_XERR", &Psi_ORIVX_XERR, &b_Psi_ORIVX_XERR);
   fChain->SetBranchAddress("Psi_ORIVX_YERR", &Psi_ORIVX_YERR, &b_Psi_ORIVX_YERR);
   fChain->SetBranchAddress("Psi_ORIVX_ZERR", &Psi_ORIVX_ZERR, &b_Psi_ORIVX_ZERR);
   fChain->SetBranchAddress("Psi_ORIVX_CHI2", &Psi_ORIVX_CHI2, &b_Psi_ORIVX_CHI2);
   fChain->SetBranchAddress("Psi_ORIVX_NDOF", &Psi_ORIVX_NDOF, &b_Psi_ORIVX_NDOF);
   fChain->SetBranchAddress("Psi_ORIVX_COV_", Psi_ORIVX_COV_, &b_Psi_ORIVX_COV_);
   fChain->SetBranchAddress("Psi_IP_ORIVX", &Psi_IP_ORIVX, &b_Psi_IP_ORIVX);
   fChain->SetBranchAddress("Psi_IPCHI2_ORIVX", &Psi_IPCHI2_ORIVX, &b_Psi_IPCHI2_ORIVX);
   fChain->SetBranchAddress("Psi_FD_ORIVX", &Psi_FD_ORIVX, &b_Psi_FD_ORIVX);
   fChain->SetBranchAddress("Psi_FDCHI2_ORIVX", &Psi_FDCHI2_ORIVX, &b_Psi_FDCHI2_ORIVX);
   fChain->SetBranchAddress("Psi_DIRA_ORIVX", &Psi_DIRA_ORIVX, &b_Psi_DIRA_ORIVX);
   fChain->SetBranchAddress("Psi_P", &Psi_P, &b_Psi_P);
   fChain->SetBranchAddress("Psi_PT", &Psi_PT, &b_Psi_PT);
   fChain->SetBranchAddress("Psi_PE", &Psi_PE, &b_Psi_PE);
   fChain->SetBranchAddress("Psi_PX", &Psi_PX, &b_Psi_PX);
   fChain->SetBranchAddress("Psi_PY", &Psi_PY, &b_Psi_PY);
   fChain->SetBranchAddress("Psi_PZ", &Psi_PZ, &b_Psi_PZ);
   fChain->SetBranchAddress("Psi_REFPX", &Psi_REFPX, &b_Psi_REFPX);
   fChain->SetBranchAddress("Psi_REFPY", &Psi_REFPY, &b_Psi_REFPY);
   fChain->SetBranchAddress("Psi_REFPZ", &Psi_REFPZ, &b_Psi_REFPZ);
   fChain->SetBranchAddress("Psi_MM", &Psi_MM, &b_Psi_MM);
   fChain->SetBranchAddress("Psi_MMERR", &Psi_MMERR, &b_Psi_MMERR);
   fChain->SetBranchAddress("Psi_M", &Psi_M, &b_Psi_M);
   fChain->SetBranchAddress("Psi_ID", &Psi_ID, &b_Psi_ID);
   fChain->SetBranchAddress("Psi_TAU", &Psi_TAU, &b_Psi_TAU);
   fChain->SetBranchAddress("Psi_TAUERR", &Psi_TAUERR, &b_Psi_TAUERR);
   fChain->SetBranchAddress("Psi_TAUCHI2", &Psi_TAUCHI2, &b_Psi_TAUCHI2);
   fChain->SetBranchAddress("Psi_L0Global_Dec", &Psi_L0Global_Dec, &b_Psi_L0Global_Dec);
   fChain->SetBranchAddress("Psi_L0Global_TIS", &Psi_L0Global_TIS, &b_Psi_L0Global_TIS);
   fChain->SetBranchAddress("Psi_L0Global_TOS", &Psi_L0Global_TOS, &b_Psi_L0Global_TOS);
   fChain->SetBranchAddress("PsiHlt1Global_Dec", &Psi_Hlt1Global_Dec, &b_Psi_Hlt1Global_Dec);
   fChain->SetBranchAddress("Psi_Hlt1Global_TIS", &Psi_Hlt1Global_TIS, &b_Psi_Hlt1Global_TIS);
   fChain->SetBranchAddress("Psi_Hlt1Global_TOS", &Psi_Hlt1Global_TOS, &b_Psi_Hlt1Global_TOS);
   fChain->SetBranchAddress("Psi_Hlt1Phys_Dec", &Psi_Hlt1Phys_Dec, &b_Psi_Hlt1Phys_Dec);
   fChain->SetBranchAddress("Psi_Hlt1Phys_TIS", &Psi_Hlt1Phys_TIS, &b_Psi_Hlt1Phys_TIS);
   fChain->SetBranchAddress("Psi_Hlt1Phys_TOS", &Psi_Hlt1Phys_TOS, &b_Psi_Hlt1Phys_TOS);
   fChain->SetBranchAddress("Psi_Hlt2Global_Dec", &Psi_Hlt2Global_Dec, &b_Psi_Hlt2Global_Dec);
   fChain->SetBranchAddress("Psi_Hlt2Global_TIS", &Psi_Hlt2Global_TIS, &b_Psi_Hlt2Global_TIS);
   fChain->SetBranchAddress("Psi_Hlt2Global_TOS", &Psi_Hlt2Global_TOS, &b_Psi_Hlt2Global_TOS);
   fChain->SetBranchAddress("Psi_Hlt2Phys_Dec", &Psi_Hlt2Phys_Dec, &b_Psi_Hlt2Phys_Dec);
   fChain->SetBranchAddress("Psi_Hlt2Phys_TIS", &Psi_Hlt2Phys_TIS, &b_Psi_Hlt2Phys_TIS);
   fChain->SetBranchAddress("Psi_Hlt2Phys_TOS", &Psi_Hlt2Phys_TOS, &b_Psi_Hlt2Phys_TOS);
   fChain->SetBranchAddress("Psi_StrippingGlobal_Dec", &Psi_StrippingGlobal_Dec, &b_Psi_StrippingGlobal_Dec);
   fChain->SetBranchAddress("Psi_StrippingGlobal_TIS", &Psi_StrippingGlobal_TIS, &b_Psi_StrippingGlobal_TIS);
   fChain->SetBranchAddress("Psi_StrippingGlobal_TOS", &Psi_StrippingGlobal_TOS, &b_Psi_StrippingGlobal_TOS);
   fChain->SetBranchAddress("Psi_L0HadronDecision_Dec", &Psi_L0HadronDecision_Dec, &b_Psi_L0HadronDecision_Dec);
   fChain->SetBranchAddress("Psi_L0HadronDecision_TIS", &Psi_L0HadronDecision_TIS, &b_Psi_L0HadronDecision_TIS);
   fChain->SetBranchAddress("Psi_L0HadronDecision_TOS", &Psi_L0HadronDecision_TOS, &b_Psi_L0HadronDecision_TOS);
   fChain->SetBranchAddress("Psi_L0MuonDecision_Dec", &Psi_L0MuonDecision_Dec, &b_Psi_L0MuonDecision_Dec);
   fChain->SetBranchAddress("Psi_L0MuonDecision_TIS", &Psi_L0MuonDecision_TIS, &b_Psi_L0MuonDecision_TIS);
   fChain->SetBranchAddress("Psi_L0MuonDecision_TOS", &Psi_L0MuonDecision_TOS, &b_Psi_L0MuonDecision_TOS);
   fChain->SetBranchAddress("Psi_L0DiMuonDecision_Dec", &Psi_L0DiMuonDecision_Dec, &b_Psi_L0DiMuonDecision_Dec);
   fChain->SetBranchAddress("Psi_L0DiMuonDecision_TIS", &Psi_L0DiMuonDecision_TIS, &b_Psi_L0DiMuonDecision_TIS);
   fChain->SetBranchAddress("Psi_L0DiMuonDecision_TOS", &Psi_L0DiMuonDecision_TOS, &b_Psi_L0DiMuonDecision_TOS);
   fChain->SetBranchAddress("Psi_L0ElectronDecision_Dec", &Psi_L0ElectronDecision_Dec, &b_Psi_L0ElectronDecision_Dec);
   fChain->SetBranchAddress("Psi_L0ElectronDecision_TIS", &Psi_L0ElectronDecision_TIS, &b_Psi_L0ElectronDecision_TIS);
   fChain->SetBranchAddress("Psi_L0ElectronDecision_TOS", &Psi_L0ElectronDecision_TOS, &b_Psi_L0ElectronDecision_TOS);
   fChain->SetBranchAddress("Psi_L0PhotonDecision_Dec", &Psi_L0PhotonDecision_Dec, &b_Psi_L0PhotonDecision_Dec);
   fChain->SetBranchAddress("Psi_L0PhotonDecision_TIS", &Psi_L0PhotonDecision_TIS, &b_Psi_L0PhotonDecision_TIS);
   fChain->SetBranchAddress("Psi_L0PhotonDecision_TOS", &Psi_L0PhotonDecision_TOS, &b_Psi_L0PhotonDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt1TrackAllL0Decision_Dec", &Psi_Hlt1TrackAllL0Decision_Dec, &b_Psi_Hlt1TrackAllL0Decision_Dec);
   fChain->SetBranchAddress("Psi_Hlt1TrackAllL0Decision_TIS", &Psi_Hlt1TrackAllL0Decision_TIS, &b_Psi_Hlt1TrackAllL0Decision_TIS);
   fChain->SetBranchAddress("Psi_Hlt1TrackAllL0Decision_TOS", &Psi_Hlt1TrackAllL0Decision_TOS, &b_Psi_Hlt1TrackAllL0Decision_TOS);
   fChain->SetBranchAddress("Psi_Hlt1TrackAllL0TightDecision_Dec", &Psi_Hlt1TrackAllL0TightDecision_Dec, &b_Psi_Hlt1TrackAllL0TightDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt1TrackAllL0TightDecision_TIS", &Psi_Hlt1TrackAllL0TightDecision_TIS, &b_Psi_Hlt1TrackAllL0TightDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt1TrackAllL0TightDecision_TOS", &Psi_Hlt1TrackAllL0TightDecision_TOS, &b_Psi_Hlt1TrackAllL0TightDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt1DiMuonHighMassDecision_Dec", &Psi_Hlt1DiMuonHighMassDecision_Dec, &b_Psi_Hlt1DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt1DiMuonHighMassDecision_TIS", &Psi_Hlt1DiMuonHighMassDecision_TIS, &b_Psi_Hlt1DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt1DiMuonHighMassDecision_TOS", &Psi_Hlt1DiMuonHighMassDecision_TOS, &b_Psi_Hlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt1DiMuonLowMassDecision_Dec", &Psi_Hlt1DiMuonLowMassDecision_Dec, &b_Psi_Hlt1DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt1DiMuonLowMassDecision_TIS", &Psi_Hlt1DiMuonLowMassDecision_TIS, &b_Psi_Hlt1DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt1DiMuonLowMassDecision_TOS", &Psi_Hlt1DiMuonLowMassDecision_TOS, &b_Psi_Hlt1DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt1SingleMuonHighPTDecision_Dec", &Psi_Hlt1SingleMuonHighPTDecision_Dec, &b_Psi_Hlt1SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt1SingleMuonHighPTDecision_TIS", &Psi_Hlt1SingleMuonHighPTDecision_TIS, &b_Psi_Hlt1SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt1SingleMuonHighPTDecision_TOS", &Psi_Hlt1SingleMuonHighPTDecision_TOS, &b_Psi_Hlt1SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt1SingleMuonNoIPDecision_Dec", &Psi_Hlt1SingleMuonNoIPDecision_Dec, &b_Psi_Hlt1SingleMuonNoIPDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt1SingleMuonNoIPDecision_TIS", &Psi_Hlt1SingleMuonNoIPDecision_TIS, &b_Psi_Hlt1SingleMuonNoIPDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt1SingleMuonNoIPDecision_TOS", &Psi_Hlt1SingleMuonNoIPDecision_TOS, &b_Psi_Hlt1SingleMuonNoIPDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt1TrackMuonDecision_Dec", &Psi_Hlt1TrackMuonDecision_Dec, &b_Psi_Hlt1TrackMuonDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt1TrackMuonDecision_TIS", &Psi_Hlt1TrackMuonDecision_TIS, &b_Psi_Hlt1TrackMuonDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt1TrackMuonDecision_TOS", &Psi_Hlt1TrackMuonDecision_TOS, &b_Psi_Hlt1TrackMuonDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2Topo2BodyBBDTDecision_Dec", &Psi_Hlt2Topo2BodyBBDTDecision_Dec, &b_Psi_Hlt2Topo2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2Topo2BodyBBDTDecision_TIS", &Psi_Hlt2Topo2BodyBBDTDecision_TIS, &b_Psi_Hlt2Topo2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2Topo2BodyBBDTDecision_TOS", &Psi_Hlt2Topo2BodyBBDTDecision_TOS, &b_Psi_Hlt2Topo2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2Topo2BodySimpleDecision_Dec", &Psi_Hlt2Topo2BodySimpleDecision_Dec, &b_Psi_Hlt2Topo2BodySimpleDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2Topo2BodySimpleDecision_TIS", &Psi_Hlt2Topo2BodySimpleDecision_TIS, &b_Psi_Hlt2Topo2BodySimpleDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2Topo2BodySimpleDecision_TOS", &Psi_Hlt2Topo2BodySimpleDecision_TOS, &b_Psi_Hlt2Topo2BodySimpleDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2Topo3BodyBBDTDecision_Dec", &Psi_Hlt2Topo3BodyBBDTDecision_Dec, &b_Psi_Hlt2Topo3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2Topo3BodyBBDTDecision_TIS", &Psi_Hlt2Topo3BodyBBDTDecision_TIS, &b_Psi_Hlt2Topo3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2Topo3BodyBBDTDecision_TOS", &Psi_Hlt2Topo3BodyBBDTDecision_TOS, &b_Psi_Hlt2Topo3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2Topo3BodySimpleDecision_Dec", &Psi_Hlt2Topo3BodySimpleDecision_Dec, &b_Psi_Hlt2Topo3BodySimpleDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2Topo3BodySimpleDecision_TIS", &Psi_Hlt2Topo3BodySimpleDecision_TIS, &b_Psi_Hlt2Topo3BodySimpleDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2Topo3BodySimpleDecision_TOS", &Psi_Hlt2Topo3BodySimpleDecision_TOS, &b_Psi_Hlt2Topo3BodySimpleDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2Topo4BodyBBDTDecision_Dec", &Psi_Hlt2Topo4BodyBBDTDecision_Dec, &b_Psi_Hlt2Topo4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2Topo4BodyBBDTDecision_TIS", &Psi_Hlt2Topo4BodyBBDTDecision_TIS, &b_Psi_Hlt2Topo4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2Topo4BodyBBDTDecision_TOS", &Psi_Hlt2Topo4BodyBBDTDecision_TOS, &b_Psi_Hlt2Topo4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2Topo4BodySimpleDecision_Dec", &Psi_Hlt2Topo4BodySimpleDecision_Dec, &b_Psi_Hlt2Topo4BodySimpleDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2Topo4BodySimpleDecision_TIS", &Psi_Hlt2Topo4BodySimpleDecision_TIS, &b_Psi_Hlt2Topo4BodySimpleDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2Topo4BodySimpleDecision_TOS", &Psi_Hlt2Topo4BodySimpleDecision_TOS, &b_Psi_Hlt2Topo4BodySimpleDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonDecision_Dec", &Psi_Hlt2DiMuonDecision_Dec, &b_Psi_Hlt2DiMuonDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonDecision_TIS", &Psi_Hlt2DiMuonDecision_TIS, &b_Psi_Hlt2DiMuonDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonDecision_TOS", &Psi_Hlt2DiMuonDecision_TOS, &b_Psi_Hlt2DiMuonDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonBDecision_Dec", &Psi_Hlt2DiMuonBDecision_Dec, &b_Psi_Hlt2DiMuonBDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonBDecision_TIS", &Psi_Hlt2DiMuonBDecision_TIS, &b_Psi_Hlt2DiMuonBDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonBDecision_TOS", &Psi_Hlt2DiMuonBDecision_TOS, &b_Psi_Hlt2DiMuonBDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonDetachedDecision_Dec", &Psi_Hlt2DiMuonDetachedDecision_Dec, &b_Psi_Hlt2DiMuonDetachedDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonDetachedDecision_TIS", &Psi_Hlt2DiMuonDetachedDecision_TIS, &b_Psi_Hlt2DiMuonDetachedDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonDetachedDecision_TOS", &Psi_Hlt2DiMuonDetachedDecision_TOS, &b_Psi_Hlt2DiMuonDetachedDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonDetachedHeavyDecision_Dec", &Psi_Hlt2DiMuonDetachedHeavyDecision_Dec, &b_Psi_Hlt2DiMuonDetachedHeavyDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonDetachedHeavyDecision_TIS", &Psi_Hlt2DiMuonDetachedHeavyDecision_TIS, &b_Psi_Hlt2DiMuonDetachedHeavyDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonDetachedHeavyDecision_TOS", &Psi_Hlt2DiMuonDetachedHeavyDecision_TOS, &b_Psi_Hlt2DiMuonDetachedHeavyDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonDetachedJPsiDecision_Dec", &Psi_Hlt2DiMuonDetachedJPsiDecision_Dec, &b_Psi_Hlt2DiMuonDetachedJPsiDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonDetachedJPsiDecision_TIS", &Psi_Hlt2DiMuonDetachedJPsiDecision_TIS, &b_Psi_Hlt2DiMuonDetachedJPsiDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonDetachedJPsiDecision_TOS", &Psi_Hlt2DiMuonDetachedJPsiDecision_TOS, &b_Psi_Hlt2DiMuonDetachedJPsiDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonDetachedPsi2SDecision_Dec", &Psi_Hlt2DiMuonDetachedPsi2SDecision_Dec, &b_Psi_Hlt2DiMuonDetachedPsi2SDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonDetachedPsi2SDecision_TIS", &Psi_Hlt2DiMuonDetachedPsi2SDecision_TIS, &b_Psi_Hlt2DiMuonDetachedPsi2SDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonDetachedPsi2SDecision_TOS", &Psi_Hlt2DiMuonDetachedPsi2SDecision_TOS, &b_Psi_Hlt2DiMuonDetachedPsi2SDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonJPsiDecision_Dec", &Psi_Hlt2DiMuonJPsiDecision_Dec, &b_Psi_Hlt2DiMuonJPsiDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonJPsiDecision_TIS", &Psi_Hlt2DiMuonJPsiDecision_TIS, &b_Psi_Hlt2DiMuonJPsiDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonJPsiDecision_TOS", &Psi_Hlt2DiMuonJPsiDecision_TOS, &b_Psi_Hlt2DiMuonJPsiDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonJPsiHighPTDecision_Dec", &Psi_Hlt2DiMuonJPsiHighPTDecision_Dec, &b_Psi_Hlt2DiMuonJPsiHighPTDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonJPsiHighPTDecision_TIS", &Psi_Hlt2DiMuonJPsiHighPTDecision_TIS, &b_Psi_Hlt2DiMuonJPsiHighPTDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonJPsiHighPTDecision_TOS", &Psi_Hlt2DiMuonJPsiHighPTDecision_TOS, &b_Psi_Hlt2DiMuonJPsiHighPTDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonLowMassDecision_Dec", &Psi_Hlt2DiMuonLowMassDecision_Dec, &b_Psi_Hlt2DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonLowMassDecision_TIS", &Psi_Hlt2DiMuonLowMassDecision_TIS, &b_Psi_Hlt2DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonLowMassDecision_TOS", &Psi_Hlt2DiMuonLowMassDecision_TOS, &b_Psi_Hlt2DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonPsi2SDecision_Dec", &Psi_Hlt2DiMuonPsi2SDecision_Dec, &b_Psi_Hlt2DiMuonPsi2SDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonPsi2SDecision_TIS", &Psi_Hlt2DiMuonPsi2SDecision_TIS, &b_Psi_Hlt2DiMuonPsi2SDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonPsi2SDecision_TOS", &Psi_Hlt2DiMuonPsi2SDecision_TOS, &b_Psi_Hlt2DiMuonPsi2SDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonPsi2SHighPTDecision_Dec", &Psi_Hlt2DiMuonPsi2SHighPTDecision_Dec, &b_Psi_Hlt2DiMuonPsi2SHighPTDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonPsi2SHighPTDecision_TIS", &Psi_Hlt2DiMuonPsi2SHighPTDecision_TIS, &b_Psi_Hlt2DiMuonPsi2SHighPTDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2DiMuonPsi2SHighPTDecision_TOS", &Psi_Hlt2DiMuonPsi2SHighPTDecision_TOS, &b_Psi_Hlt2DiMuonPsi2SHighPTDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2LowMultMuonDecision_Dec", &Psi_Hlt2LowMultMuonDecision_Dec, &b_Psi_Hlt2LowMultMuonDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2LowMultMuonDecision_TIS", &Psi_Hlt2LowMultMuonDecision_TIS, &b_Psi_Hlt2LowMultMuonDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2LowMultMuonDecision_TOS", &Psi_Hlt2LowMultMuonDecision_TOS, &b_Psi_Hlt2LowMultMuonDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2MuonFromHLT1Decision_Dec", &Psi_Hlt2MuonFromHLT1Decision_Dec, &b_Psi_Hlt2MuonFromHLT1Decision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2MuonFromHLT1Decision_TIS", &Psi_Hlt2MuonFromHLT1Decision_TIS, &b_Psi_Hlt2MuonFromHLT1Decision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2MuonFromHLT1Decision_TOS", &Psi_Hlt2MuonFromHLT1Decision_TOS, &b_Psi_Hlt2MuonFromHLT1Decision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2SingleMuonDecision_Dec", &Psi_Hlt2SingleMuonDecision_Dec, &b_Psi_Hlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2SingleMuonDecision_TIS", &Psi_Hlt2SingleMuonDecision_TIS, &b_Psi_Hlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2SingleMuonDecision_TOS", &Psi_Hlt2SingleMuonDecision_TOS, &b_Psi_Hlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2SingleMuonHighPTDecision_Dec", &Psi_Hlt2SingleMuonHighPTDecision_Dec, &b_Psi_Hlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2SingleMuonHighPTDecision_TIS", &Psi_Hlt2SingleMuonHighPTDecision_TIS, &b_Psi_Hlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2SingleMuonHighPTDecision_TOS", &Psi_Hlt2SingleMuonHighPTDecision_TOS, &b_Psi_Hlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2SingleMuonLowPTDecision_Dec", &Psi_Hlt2SingleMuonLowPTDecision_Dec, &b_Psi_Hlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2SingleMuonLowPTDecision_TIS", &Psi_Hlt2SingleMuonLowPTDecision_TIS, &b_Psi_Hlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2SingleMuonLowPTDecision_TOS", &Psi_Hlt2SingleMuonLowPTDecision_TOS, &b_Psi_Hlt2SingleMuonLowPTDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2SingleMuonVHighPTDecision_Dec", &Psi_Hlt2SingleMuonVHighPTDecision_Dec, &b_Psi_Hlt2SingleMuonVHighPTDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2SingleMuonVHighPTDecision_TIS", &Psi_Hlt2SingleMuonVHighPTDecision_TIS, &b_Psi_Hlt2SingleMuonVHighPTDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2SingleMuonVHighPTDecision_TOS", &Psi_Hlt2SingleMuonVHighPTDecision_TOS, &b_Psi_Hlt2SingleMuonVHighPTDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2TopoMu2BodyBBDTDecision_Dec", &Psi_Hlt2TopoMu2BodyBBDTDecision_Dec, &b_Psi_Hlt2TopoMu2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2TopoMu2BodyBBDTDecision_TIS", &Psi_Hlt2TopoMu2BodyBBDTDecision_TIS, &b_Psi_Hlt2TopoMu2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2TopoMu2BodyBBDTDecision_TOS", &Psi_Hlt2TopoMu2BodyBBDTDecision_TOS, &b_Psi_Hlt2TopoMu2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2TopoMu3BodyBBDTDecision_Dec", &Psi_Hlt2TopoMu3BodyBBDTDecision_Dec, &b_Psi_Hlt2TopoMu3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2TopoMu3BodyBBDTDecision_TIS", &Psi_Hlt2TopoMu3BodyBBDTDecision_TIS, &b_Psi_Hlt2TopoMu3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2TopoMu3BodyBBDTDecision_TOS", &Psi_Hlt2TopoMu3BodyBBDTDecision_TOS, &b_Psi_Hlt2TopoMu3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2TopoMu4BodyBBDTDecision_Dec", &Psi_Hlt2TopoMu4BodyBBDTDecision_Dec, &b_Psi_Hlt2TopoMu4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2TopoMu4BodyBBDTDecision_TIS", &Psi_Hlt2TopoMu4BodyBBDTDecision_TIS, &b_Psi_Hlt2TopoMu4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2TopoMu4BodyBBDTDecision_TOS", &Psi_Hlt2TopoMu4BodyBBDTDecision_TOS, &b_Psi_Hlt2TopoMu4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("Psi_Hlt2diPhotonDiMuonDecision_Dec", &Psi_Hlt2diPhotonDiMuonDecision_Dec, &b_Psi_Hlt2diPhotonDiMuonDecision_Dec);
   fChain->SetBranchAddress("Psi_Hlt2diPhotonDiMuonDecision_TIS", &Psi_Hlt2diPhotonDiMuonDecision_TIS, &b_Psi_Hlt2diPhotonDiMuonDecision_TIS);
   fChain->SetBranchAddress("Psi_Hlt2diPhotonDiMuonDecision_TOS", &Psi_Hlt2diPhotonDiMuonDecision_TOS, &b_Psi_Hlt2diPhotonDiMuonDecision_TOS);
   fChain->SetBranchAddress("Psi_NOPARTWITHINDCHI2WDW", &Psi_NOPARTWITHINDCHI2WDW, &b_Psi_NOPARTWITHINDCHI2WDW);
   fChain->SetBranchAddress("Psi_NOPARTWITHINCHI2WDW", &Psi_NOPARTWITHINCHI2WDW, &b_Psi_NOPARTWITHINCHI2WDW);
   fChain->SetBranchAddress("Psi_SMALLESTCHI2", &Psi_SMALLESTCHI2, &b_Psi_SMALLESTCHI2);
   fChain->SetBranchAddress("Psi_SMALLESTDELTACHI2", &Psi_SMALLESTDELTACHI2, &b_Psi_SMALLESTDELTACHI2);
   fChain->SetBranchAddress("muminus_MINIP", &muminus_MINIP, &b_muminus_MINIP);
   fChain->SetBranchAddress("muminus_MINIPCHI2", &muminus_MINIPCHI2, &b_muminus_MINIPCHI2);
   fChain->SetBranchAddress("muminus_MINIPNEXTBEST", &muminus_MINIPNEXTBEST, &b_muminus_MINIPNEXTBEST);
   fChain->SetBranchAddress("muminus_MINIPCHI2NEXTBEST", &muminus_MINIPCHI2NEXTBEST, &b_muminus_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("muminus_AllIP", muminus_AllIP, &b_muminus_AllIP);
   fChain->SetBranchAddress("muminus_AllIPchi2", muminus_AllIPchi2, &b_muminus_AllIPchi2);
   fChain->SetBranchAddress("muminus_OWNPV_X", &muminus_OWNPV_X, &b_muminus_OWNPV_X);
   fChain->SetBranchAddress("muminus_OWNPV_Y", &muminus_OWNPV_Y, &b_muminus_OWNPV_Y);
   fChain->SetBranchAddress("muminus_OWNPV_Z", &muminus_OWNPV_Z, &b_muminus_OWNPV_Z);
   fChain->SetBranchAddress("muminus_OWNPV_XERR", &muminus_OWNPV_XERR, &b_muminus_OWNPV_XERR);
   fChain->SetBranchAddress("muminus_OWNPV_YERR", &muminus_OWNPV_YERR, &b_muminus_OWNPV_YERR);
   fChain->SetBranchAddress("muminus_OWNPV_ZERR", &muminus_OWNPV_ZERR, &b_muminus_OWNPV_ZERR);
   fChain->SetBranchAddress("muminus_OWNPV_CHI2", &muminus_OWNPV_CHI2, &b_muminus_OWNPV_CHI2);
   fChain->SetBranchAddress("muminus_OWNPV_NDOF", &muminus_OWNPV_NDOF, &b_muminus_OWNPV_NDOF);
   fChain->SetBranchAddress("muminus_OWNPV_COV_", muminus_OWNPV_COV_, &b_muminus_OWNPV_COV_);
   fChain->SetBranchAddress("muminus_IP_OWNPV", &muminus_IP_OWNPV, &b_muminus_IP_OWNPV);
   fChain->SetBranchAddress("muminus_IPCHI2_OWNPV", &muminus_IPCHI2_OWNPV, &b_muminus_IPCHI2_OWNPV);
   fChain->SetBranchAddress("muminus_TOPPV_X", &muminus_TOPPV_X, &b_muminus_TOPPV_X);
   fChain->SetBranchAddress("muminus_TOPPV_Y", &muminus_TOPPV_Y, &b_muminus_TOPPV_Y);
   fChain->SetBranchAddress("muminus_TOPPV_Z", &muminus_TOPPV_Z, &b_muminus_TOPPV_Z);
   fChain->SetBranchAddress("muminus_TOPPV_XERR", &muminus_TOPPV_XERR, &b_muminus_TOPPV_XERR);
   fChain->SetBranchAddress("muminus_TOPPV_YERR", &muminus_TOPPV_YERR, &b_muminus_TOPPV_YERR);
   fChain->SetBranchAddress("muminus_TOPPV_ZERR", &muminus_TOPPV_ZERR, &b_muminus_TOPPV_ZERR);
   fChain->SetBranchAddress("muminus_TOPPV_CHI2", &muminus_TOPPV_CHI2, &b_muminus_TOPPV_CHI2);
   fChain->SetBranchAddress("muminus_TOPPV_NDOF", &muminus_TOPPV_NDOF, &b_muminus_TOPPV_NDOF);
   fChain->SetBranchAddress("muminus_TOPPV_COV_", muminus_TOPPV_COV_, &b_muminus_TOPPV_COV_);
   fChain->SetBranchAddress("muminus_IP_TOPPV", &muminus_IP_TOPPV, &b_muminus_IP_TOPPV);
   fChain->SetBranchAddress("muminus_IPCHI2_TOPPV", &muminus_IPCHI2_TOPPV, &b_muminus_IPCHI2_TOPPV);
   fChain->SetBranchAddress("muminus_ORIVX_X", &muminus_ORIVX_X, &b_muminus_ORIVX_X);
   fChain->SetBranchAddress("muminus_ORIVX_Y", &muminus_ORIVX_Y, &b_muminus_ORIVX_Y);
   fChain->SetBranchAddress("muminus_ORIVX_Z", &muminus_ORIVX_Z, &b_muminus_ORIVX_Z);
   fChain->SetBranchAddress("muminus_ORIVX_XERR", &muminus_ORIVX_XERR, &b_muminus_ORIVX_XERR);
   fChain->SetBranchAddress("muminus_ORIVX_YERR", &muminus_ORIVX_YERR, &b_muminus_ORIVX_YERR);
   fChain->SetBranchAddress("muminus_ORIVX_ZERR", &muminus_ORIVX_ZERR, &b_muminus_ORIVX_ZERR);
   fChain->SetBranchAddress("muminus_ORIVX_CHI2", &muminus_ORIVX_CHI2, &b_muminus_ORIVX_CHI2);
   fChain->SetBranchAddress("muminus_ORIVX_NDOF", &muminus_ORIVX_NDOF, &b_muminus_ORIVX_NDOF);
   fChain->SetBranchAddress("muminus_ORIVX_COV_", muminus_ORIVX_COV_, &b_muminus_ORIVX_COV_);
   fChain->SetBranchAddress("muminus_IP_ORIVX", &muminus_IP_ORIVX, &b_muminus_IP_ORIVX);
   fChain->SetBranchAddress("muminus_IPCHI2_ORIVX", &muminus_IPCHI2_ORIVX, &b_muminus_IPCHI2_ORIVX);
   fChain->SetBranchAddress("muminus_P", &muminus_P, &b_muminus_P);
   fChain->SetBranchAddress("muminus_PT", &muminus_PT, &b_muminus_PT);
   fChain->SetBranchAddress("muminus_PE", &muminus_PE, &b_muminus_PE);
   fChain->SetBranchAddress("muminus_PX", &muminus_PX, &b_muminus_PX);
   fChain->SetBranchAddress("muminus_PY", &muminus_PY, &b_muminus_PY);
   fChain->SetBranchAddress("muminus_PZ", &muminus_PZ, &b_muminus_PZ);
   fChain->SetBranchAddress("muminus_REFPX", &muminus_REFPX, &b_muminus_REFPX);
   fChain->SetBranchAddress("muminus_REFPY", &muminus_REFPY, &b_muminus_REFPY);
   fChain->SetBranchAddress("muminus_REFPZ", &muminus_REFPZ, &b_muminus_REFPZ);
   fChain->SetBranchAddress("muminus_M", &muminus_M, &b_muminus_M);
   fChain->SetBranchAddress("muminus_AtVtx_PE", &muminus_AtVtx_PE, &b_muminus_AtVtx_PE);
   fChain->SetBranchAddress("muminus_AtVtx_PX", &muminus_AtVtx_PX, &b_muminus_AtVtx_PX);
   fChain->SetBranchAddress("muminus_AtVtx_PY", &muminus_AtVtx_PY, &b_muminus_AtVtx_PY);
   fChain->SetBranchAddress("muminus_AtVtx_PZ", &muminus_AtVtx_PZ, &b_muminus_AtVtx_PZ);
   fChain->SetBranchAddress("muminus_L0Calo_HCAL_realET", &muminus_L0Calo_HCAL_realET, &b_muminus_L0Calo_HCAL_realET);
   fChain->SetBranchAddress("muminus_L0Calo_HCAL_xProjection", &muminus_L0Calo_HCAL_xProjection, &b_muminus_L0Calo_HCAL_xProjection);
   fChain->SetBranchAddress("muminus_L0Calo_HCAL_yProjection", &muminus_L0Calo_HCAL_yProjection, &b_muminus_L0Calo_HCAL_yProjection);
   fChain->SetBranchAddress("muminus_L0Calo_HCAL_region", &muminus_L0Calo_HCAL_region, &b_muminus_L0Calo_HCAL_region);
   fChain->SetBranchAddress("muminus_ID", &muminus_ID, &b_muminus_ID);
   fChain->SetBranchAddress("muminus_PIDe", &muminus_PIDe, &b_muminus_PIDe);
   fChain->SetBranchAddress("muminus_PIDmu", &muminus_PIDmu, &b_muminus_PIDmu);
   fChain->SetBranchAddress("muminus_PIDK", &muminus_PIDK, &b_muminus_PIDK);
   fChain->SetBranchAddress("muminus_PIDp", &muminus_PIDp, &b_muminus_PIDp);
   fChain->SetBranchAddress("muminus_ProbNNe", &muminus_ProbNNe, &b_muminus_ProbNNe);
   fChain->SetBranchAddress("muminus_ProbNNk", &muminus_ProbNNk, &b_muminus_ProbNNk);
   fChain->SetBranchAddress("muminus_ProbNNp", &muminus_ProbNNp, &b_muminus_ProbNNp);
   fChain->SetBranchAddress("muminus_ProbNNpi", &muminus_ProbNNpi, &b_muminus_ProbNNpi);
   fChain->SetBranchAddress("muminus_ProbNNmu", &muminus_ProbNNmu, &b_muminus_ProbNNmu);
   fChain->SetBranchAddress("muminus_ProbNNghost", &muminus_ProbNNghost, &b_muminus_ProbNNghost);
   fChain->SetBranchAddress("muminus_hasMuon", &muminus_hasMuon, &b_muminus_hasMuon);
   fChain->SetBranchAddress("muminus_isMuon", &muminus_isMuon, &b_muminus_isMuon);
   fChain->SetBranchAddress("muminus_hasRich", &muminus_hasRich, &b_muminus_hasRich);
   fChain->SetBranchAddress("muminus_hasCalo", &muminus_hasCalo, &b_muminus_hasCalo);
   fChain->SetBranchAddress("muminus_UsedRichAerogel", &muminus_UsedRichAerogel, &b_muminus_UsedRichAerogel);
   fChain->SetBranchAddress("muminus_UsedRich1Gas", &muminus_UsedRich1Gas, &b_muminus_UsedRich1Gas);
   fChain->SetBranchAddress("muminus_UsedRich2Gas", &muminus_UsedRich2Gas, &b_muminus_UsedRich2Gas);
   fChain->SetBranchAddress("muminus_RichAboveElThres", &muminus_RichAboveElThres, &b_muminus_RichAboveElThres);
   fChain->SetBranchAddress("muminus_RichAboveMuThres", &muminus_RichAboveMuThres, &b_muminus_RichAboveMuThres);
   fChain->SetBranchAddress("muminus_RichAbovePiThres", &muminus_RichAbovePiThres, &b_muminus_RichAbovePiThres);
   fChain->SetBranchAddress("muminus_RichAboveKaThres", &muminus_RichAboveKaThres, &b_muminus_RichAboveKaThres);
   fChain->SetBranchAddress("muminus_RichAbovePrThres", &muminus_RichAbovePrThres, &b_muminus_RichAbovePrThres);
   fChain->SetBranchAddress("muminus_RichDLLe", &muminus_RichDLLe, &b_muminus_RichDLLe);
   fChain->SetBranchAddress("muminus_RichDLLmu", &muminus_RichDLLmu, &b_muminus_RichDLLmu);
   fChain->SetBranchAddress("muminus_RichDLLpi", &muminus_RichDLLpi, &b_muminus_RichDLLpi);
   fChain->SetBranchAddress("muminus_RichDLLk", &muminus_RichDLLk, &b_muminus_RichDLLk);
   fChain->SetBranchAddress("muminus_RichDLLp", &muminus_RichDLLp, &b_muminus_RichDLLp);
   fChain->SetBranchAddress("muminus_RichDLLbt", &muminus_RichDLLbt, &b_muminus_RichDLLbt);
   fChain->SetBranchAddress("muminus_InAccMuon", &muminus_InAccMuon, &b_muminus_InAccMuon);
   fChain->SetBranchAddress("muminus_isMuonLoose", &muminus_isMuonLoose, &b_muminus_isMuonLoose);
   fChain->SetBranchAddress("muminus_MuonMuLL", &muminus_MuonMuLL, &b_muminus_MuonMuLL);
   fChain->SetBranchAddress("muminus_MuonBkgLL", &muminus_MuonBkgLL, &b_muminus_MuonBkgLL);
   fChain->SetBranchAddress("muminus_MuonNShared", &muminus_MuonNShared, &b_muminus_MuonNShared);
   fChain->SetBranchAddress("muminus_InAccEcal", &muminus_InAccEcal, &b_muminus_InAccEcal);
   fChain->SetBranchAddress("muminus_CaloEcalE", &muminus_CaloEcalE, &b_muminus_CaloEcalE);
   fChain->SetBranchAddress("muminus_EcalPIDe", &muminus_EcalPIDe, &b_muminus_EcalPIDe);
   fChain->SetBranchAddress("muminus_EcalPIDmu", &muminus_EcalPIDmu, &b_muminus_EcalPIDmu);
   fChain->SetBranchAddress("muminus_InAccHcal", &muminus_InAccHcal, &b_muminus_InAccHcal);
   fChain->SetBranchAddress("muminus_CaloHcalE", &muminus_CaloHcalE, &b_muminus_CaloHcalE);
   fChain->SetBranchAddress("muminus_HcalPIDe", &muminus_HcalPIDe, &b_muminus_HcalPIDe);
   fChain->SetBranchAddress("muminus_HcalPIDmu", &muminus_HcalPIDmu, &b_muminus_HcalPIDmu);
   fChain->SetBranchAddress("muminus_InAccPrs", &muminus_InAccPrs, &b_muminus_InAccPrs);
   fChain->SetBranchAddress("muminus_PrsPIDe", &muminus_PrsPIDe, &b_muminus_PrsPIDe);
   fChain->SetBranchAddress("muminus_CaloPrsE", &muminus_CaloPrsE, &b_muminus_CaloPrsE);
   fChain->SetBranchAddress("muminus_InAccSpd", &muminus_InAccSpd, &b_muminus_InAccSpd);
   fChain->SetBranchAddress("muminus_CaloSpdE", &muminus_CaloSpdE, &b_muminus_CaloSpdE);
   fChain->SetBranchAddress("muminus_InAccBrem", &muminus_InAccBrem, &b_muminus_InAccBrem);
   fChain->SetBranchAddress("muminus_BremPIDe", &muminus_BremPIDe, &b_muminus_BremPIDe);
   fChain->SetBranchAddress("muminus_VeloCharge", &muminus_VeloCharge, &b_muminus_VeloCharge);
   fChain->SetBranchAddress("muminus_TRACK_Type", &muminus_TRACK_Type, &b_muminus_TRACK_Type);
   fChain->SetBranchAddress("muminus_TRACK_Key", &muminus_TRACK_Key, &b_muminus_TRACK_Key);
   fChain->SetBranchAddress("muminus_TRACK_CHI2", &muminus_TRACK_CHI2, &b_muminus_TRACK_CHI2);
   fChain->SetBranchAddress("muminus_TRACK_NDOF", &muminus_TRACK_NDOF, &b_muminus_TRACK_NDOF);
   fChain->SetBranchAddress("muminus_TRACK_CHI2NDOF", &muminus_TRACK_CHI2NDOF, &b_muminus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("muminus_TRACK_PCHI2", &muminus_TRACK_PCHI2, &b_muminus_TRACK_PCHI2);
   fChain->SetBranchAddress("muminus_TRACK_VeloCHI2NDOF", &muminus_TRACK_VeloCHI2NDOF, &b_muminus_TRACK_VeloCHI2NDOF);
   fChain->SetBranchAddress("muminus_TRACK_TCHI2NDOF", &muminus_TRACK_TCHI2NDOF, &b_muminus_TRACK_TCHI2NDOF);
   fChain->SetBranchAddress("muminus_VELO_UTID", &muminus_VELO_UTID, &b_muminus_VELO_UTID);
   fChain->SetBranchAddress("muminus_TRACK_FirstMeasurementX", &muminus_TRACK_FirstMeasurementX, &b_muminus_TRACK_FirstMeasurementX);
   fChain->SetBranchAddress("muminus_TRACK_FirstMeasurementY", &muminus_TRACK_FirstMeasurementY, &b_muminus_TRACK_FirstMeasurementY);
   fChain->SetBranchAddress("muminus_TRACK_FirstMeasurementZ", &muminus_TRACK_FirstMeasurementZ, &b_muminus_TRACK_FirstMeasurementZ);
   fChain->SetBranchAddress("muminus_TRACK_MatchCHI2", &muminus_TRACK_MatchCHI2, &b_muminus_TRACK_MatchCHI2);
   fChain->SetBranchAddress("muminus_TRACK_GhostProb", &muminus_TRACK_GhostProb, &b_muminus_TRACK_GhostProb);
   fChain->SetBranchAddress("muminus_TRACK_CloneDist", &muminus_TRACK_CloneDist, &b_muminus_TRACK_CloneDist);
   fChain->SetBranchAddress("muminus_TRACK_Likelihood", &muminus_TRACK_Likelihood, &b_muminus_TRACK_Likelihood);
   fChain->SetBranchAddress("muplus_MINIP", &muplus_MINIP, &b_muplus_MINIP);
   fChain->SetBranchAddress("muplus_MINIPCHI2", &muplus_MINIPCHI2, &b_muplus_MINIPCHI2);
   fChain->SetBranchAddress("muplus_MINIPNEXTBEST", &muplus_MINIPNEXTBEST, &b_muplus_MINIPNEXTBEST);
   fChain->SetBranchAddress("muplus_MINIPCHI2NEXTBEST", &muplus_MINIPCHI2NEXTBEST, &b_muplus_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("muplus_AllIP", muplus_AllIP, &b_muplus_AllIP);
   fChain->SetBranchAddress("muplus_AllIPchi2", muplus_AllIPchi2, &b_muplus_AllIPchi2);
   fChain->SetBranchAddress("muplus_OWNPV_X", &muplus_OWNPV_X, &b_muplus_OWNPV_X);
   fChain->SetBranchAddress("muplus_OWNPV_Y", &muplus_OWNPV_Y, &b_muplus_OWNPV_Y);
   fChain->SetBranchAddress("muplus_OWNPV_Z", &muplus_OWNPV_Z, &b_muplus_OWNPV_Z);
   fChain->SetBranchAddress("muplus_OWNPV_XERR", &muplus_OWNPV_XERR, &b_muplus_OWNPV_XERR);
   fChain->SetBranchAddress("muplus_OWNPV_YERR", &muplus_OWNPV_YERR, &b_muplus_OWNPV_YERR);
   fChain->SetBranchAddress("muplus_OWNPV_ZERR", &muplus_OWNPV_ZERR, &b_muplus_OWNPV_ZERR);
   fChain->SetBranchAddress("muplus_OWNPV_CHI2", &muplus_OWNPV_CHI2, &b_muplus_OWNPV_CHI2);
   fChain->SetBranchAddress("muplus_OWNPV_NDOF", &muplus_OWNPV_NDOF, &b_muplus_OWNPV_NDOF);
   fChain->SetBranchAddress("muplus_OWNPV_COV_", muplus_OWNPV_COV_, &b_muplus_OWNPV_COV_);
   fChain->SetBranchAddress("muplus_IP_OWNPV", &muplus_IP_OWNPV, &b_muplus_IP_OWNPV);
   fChain->SetBranchAddress("muplus_IPCHI2_OWNPV", &muplus_IPCHI2_OWNPV, &b_muplus_IPCHI2_OWNPV);
   fChain->SetBranchAddress("muplus_TOPPV_X", &muplus_TOPPV_X, &b_muplus_TOPPV_X);
   fChain->SetBranchAddress("muplus_TOPPV_Y", &muplus_TOPPV_Y, &b_muplus_TOPPV_Y);
   fChain->SetBranchAddress("muplus_TOPPV_Z", &muplus_TOPPV_Z, &b_muplus_TOPPV_Z);
   fChain->SetBranchAddress("muplus_TOPPV_XERR", &muplus_TOPPV_XERR, &b_muplus_TOPPV_XERR);
   fChain->SetBranchAddress("muplus_TOPPV_YERR", &muplus_TOPPV_YERR, &b_muplus_TOPPV_YERR);
   fChain->SetBranchAddress("muplus_TOPPV_ZERR", &muplus_TOPPV_ZERR, &b_muplus_TOPPV_ZERR);
   fChain->SetBranchAddress("muplus_TOPPV_CHI2", &muplus_TOPPV_CHI2, &b_muplus_TOPPV_CHI2);
   fChain->SetBranchAddress("muplus_TOPPV_NDOF", &muplus_TOPPV_NDOF, &b_muplus_TOPPV_NDOF);
   fChain->SetBranchAddress("muplus_TOPPV_COV_", muplus_TOPPV_COV_, &b_muplus_TOPPV_COV_);
   fChain->SetBranchAddress("muplus_IP_TOPPV", &muplus_IP_TOPPV, &b_muplus_IP_TOPPV);
   fChain->SetBranchAddress("muplus_IPCHI2_TOPPV", &muplus_IPCHI2_TOPPV, &b_muplus_IPCHI2_TOPPV);
   fChain->SetBranchAddress("muplus_ORIVX_X", &muplus_ORIVX_X, &b_muplus_ORIVX_X);
   fChain->SetBranchAddress("muplus_ORIVX_Y", &muplus_ORIVX_Y, &b_muplus_ORIVX_Y);
   fChain->SetBranchAddress("muplus_ORIVX_Z", &muplus_ORIVX_Z, &b_muplus_ORIVX_Z);
   fChain->SetBranchAddress("muplus_ORIVX_XERR", &muplus_ORIVX_XERR, &b_muplus_ORIVX_XERR);
   fChain->SetBranchAddress("muplus_ORIVX_YERR", &muplus_ORIVX_YERR, &b_muplus_ORIVX_YERR);
   fChain->SetBranchAddress("muplus_ORIVX_ZERR", &muplus_ORIVX_ZERR, &b_muplus_ORIVX_ZERR);
   fChain->SetBranchAddress("muplus_ORIVX_CHI2", &muplus_ORIVX_CHI2, &b_muplus_ORIVX_CHI2);
   fChain->SetBranchAddress("muplus_ORIVX_NDOF", &muplus_ORIVX_NDOF, &b_muplus_ORIVX_NDOF);
   fChain->SetBranchAddress("muplus_ORIVX_COV_", muplus_ORIVX_COV_, &b_muplus_ORIVX_COV_);
   fChain->SetBranchAddress("muplus_IP_ORIVX", &muplus_IP_ORIVX, &b_muplus_IP_ORIVX);
   fChain->SetBranchAddress("muplus_IPCHI2_ORIVX", &muplus_IPCHI2_ORIVX, &b_muplus_IPCHI2_ORIVX);
   fChain->SetBranchAddress("muplus_P", &muplus_P, &b_muplus_P);
   fChain->SetBranchAddress("muplus_PT", &muplus_PT, &b_muplus_PT);
   fChain->SetBranchAddress("muplus_PE", &muplus_PE, &b_muplus_PE);
   fChain->SetBranchAddress("muplus_PX", &muplus_PX, &b_muplus_PX);
   fChain->SetBranchAddress("muplus_PY", &muplus_PY, &b_muplus_PY);
   fChain->SetBranchAddress("muplus_PZ", &muplus_PZ, &b_muplus_PZ);
   fChain->SetBranchAddress("muplus_REFPX", &muplus_REFPX, &b_muplus_REFPX);
   fChain->SetBranchAddress("muplus_REFPY", &muplus_REFPY, &b_muplus_REFPY);
   fChain->SetBranchAddress("muplus_REFPZ", &muplus_REFPZ, &b_muplus_REFPZ);
   fChain->SetBranchAddress("muplus_M", &muplus_M, &b_muplus_M);
   fChain->SetBranchAddress("muplus_AtVtx_PE", &muplus_AtVtx_PE, &b_muplus_AtVtx_PE);
   fChain->SetBranchAddress("muplus_AtVtx_PX", &muplus_AtVtx_PX, &b_muplus_AtVtx_PX);
   fChain->SetBranchAddress("muplus_AtVtx_PY", &muplus_AtVtx_PY, &b_muplus_AtVtx_PY);
   fChain->SetBranchAddress("muplus_AtVtx_PZ", &muplus_AtVtx_PZ, &b_muplus_AtVtx_PZ);
   fChain->SetBranchAddress("muplus_L0Calo_HCAL_realET", &muplus_L0Calo_HCAL_realET, &b_muplus_L0Calo_HCAL_realET);
   fChain->SetBranchAddress("muplus_L0Calo_HCAL_xProjection", &muplus_L0Calo_HCAL_xProjection, &b_muplus_L0Calo_HCAL_xProjection);
   fChain->SetBranchAddress("muplus_L0Calo_HCAL_yProjection", &muplus_L0Calo_HCAL_yProjection, &b_muplus_L0Calo_HCAL_yProjection);
   fChain->SetBranchAddress("muplus_L0Calo_HCAL_region", &muplus_L0Calo_HCAL_region, &b_muplus_L0Calo_HCAL_region);
   fChain->SetBranchAddress("muplus_ID", &muplus_ID, &b_muplus_ID);
   fChain->SetBranchAddress("muplus_PIDe", &muplus_PIDe, &b_muplus_PIDe);
   fChain->SetBranchAddress("muplus_PIDmu", &muplus_PIDmu, &b_muplus_PIDmu);
   fChain->SetBranchAddress("muplus_PIDK", &muplus_PIDK, &b_muplus_PIDK);
   fChain->SetBranchAddress("muplus_PIDp", &muplus_PIDp, &b_muplus_PIDp);
   fChain->SetBranchAddress("muplus_ProbNNe", &muplus_ProbNNe, &b_muplus_ProbNNe);
   fChain->SetBranchAddress("muplus_ProbNNk", &muplus_ProbNNk, &b_muplus_ProbNNk);
   fChain->SetBranchAddress("muplus_ProbNNp", &muplus_ProbNNp, &b_muplus_ProbNNp);
   fChain->SetBranchAddress("muplus_ProbNNpi", &muplus_ProbNNpi, &b_muplus_ProbNNpi);
   fChain->SetBranchAddress("muplus_ProbNNmu", &muplus_ProbNNmu, &b_muplus_ProbNNmu);
   fChain->SetBranchAddress("muplus_ProbNNghost", &muplus_ProbNNghost, &b_muplus_ProbNNghost);
   fChain->SetBranchAddress("muplus_hasMuon", &muplus_hasMuon, &b_muplus_hasMuon);
   fChain->SetBranchAddress("muplus_isMuon", &muplus_isMuon, &b_muplus_isMuon);
   fChain->SetBranchAddress("muplus_hasRich", &muplus_hasRich, &b_muplus_hasRich);
   fChain->SetBranchAddress("muplus_hasCalo", &muplus_hasCalo, &b_muplus_hasCalo);
   fChain->SetBranchAddress("muplus_UsedRichAerogel", &muplus_UsedRichAerogel, &b_muplus_UsedRichAerogel);
   fChain->SetBranchAddress("muplus_UsedRich1Gas", &muplus_UsedRich1Gas, &b_muplus_UsedRich1Gas);
   fChain->SetBranchAddress("muplus_UsedRich2Gas", &muplus_UsedRich2Gas, &b_muplus_UsedRich2Gas);
   fChain->SetBranchAddress("muplus_RichAboveElThres", &muplus_RichAboveElThres, &b_muplus_RichAboveElThres);
   fChain->SetBranchAddress("muplus_RichAboveMuThres", &muplus_RichAboveMuThres, &b_muplus_RichAboveMuThres);
   fChain->SetBranchAddress("muplus_RichAbovePiThres", &muplus_RichAbovePiThres, &b_muplus_RichAbovePiThres);
   fChain->SetBranchAddress("muplus_RichAboveKaThres", &muplus_RichAboveKaThres, &b_muplus_RichAboveKaThres);
   fChain->SetBranchAddress("muplus_RichAbovePrThres", &muplus_RichAbovePrThres, &b_muplus_RichAbovePrThres);
   fChain->SetBranchAddress("muplus_RichDLLe", &muplus_RichDLLe, &b_muplus_RichDLLe);
   fChain->SetBranchAddress("muplus_RichDLLmu", &muplus_RichDLLmu, &b_muplus_RichDLLmu);
   fChain->SetBranchAddress("muplus_RichDLLpi", &muplus_RichDLLpi, &b_muplus_RichDLLpi);
   fChain->SetBranchAddress("muplus_RichDLLk", &muplus_RichDLLk, &b_muplus_RichDLLk);
   fChain->SetBranchAddress("muplus_RichDLLp", &muplus_RichDLLp, &b_muplus_RichDLLp);
   fChain->SetBranchAddress("muplus_RichDLLbt", &muplus_RichDLLbt, &b_muplus_RichDLLbt);
   fChain->SetBranchAddress("muplus_InAccMuon", &muplus_InAccMuon, &b_muplus_InAccMuon);
   fChain->SetBranchAddress("muplus_isMuonLoose", &muplus_isMuonLoose, &b_muplus_isMuonLoose);
   fChain->SetBranchAddress("muplus_MuonMuLL", &muplus_MuonMuLL, &b_muplus_MuonMuLL);
   fChain->SetBranchAddress("muplus_MuonBkgLL", &muplus_MuonBkgLL, &b_muplus_MuonBkgLL);
   fChain->SetBranchAddress("muplus_MuonNShared", &muplus_MuonNShared, &b_muplus_MuonNShared);
   fChain->SetBranchAddress("muplus_InAccEcal", &muplus_InAccEcal, &b_muplus_InAccEcal);
   fChain->SetBranchAddress("muplus_CaloEcalE", &muplus_CaloEcalE, &b_muplus_CaloEcalE);
   fChain->SetBranchAddress("muplus_EcalPIDe", &muplus_EcalPIDe, &b_muplus_EcalPIDe);
   fChain->SetBranchAddress("muplus_EcalPIDmu", &muplus_EcalPIDmu, &b_muplus_EcalPIDmu);
   fChain->SetBranchAddress("muplus_InAccHcal", &muplus_InAccHcal, &b_muplus_InAccHcal);
   fChain->SetBranchAddress("muplus_CaloHcalE", &muplus_CaloHcalE, &b_muplus_CaloHcalE);
   fChain->SetBranchAddress("muplus_HcalPIDe", &muplus_HcalPIDe, &b_muplus_HcalPIDe);
   fChain->SetBranchAddress("muplus_HcalPIDmu", &muplus_HcalPIDmu, &b_muplus_HcalPIDmu);
   fChain->SetBranchAddress("muplus_InAccPrs", &muplus_InAccPrs, &b_muplus_InAccPrs);
   fChain->SetBranchAddress("muplus_PrsPIDe", &muplus_PrsPIDe, &b_muplus_PrsPIDe);
   fChain->SetBranchAddress("muplus_CaloPrsE", &muplus_CaloPrsE, &b_muplus_CaloPrsE);
   fChain->SetBranchAddress("muplus_InAccSpd", &muplus_InAccSpd, &b_muplus_InAccSpd);
   fChain->SetBranchAddress("muplus_CaloSpdE", &muplus_CaloSpdE, &b_muplus_CaloSpdE);
   fChain->SetBranchAddress("muplus_InAccBrem", &muplus_InAccBrem, &b_muplus_InAccBrem);
   fChain->SetBranchAddress("muplus_BremPIDe", &muplus_BremPIDe, &b_muplus_BremPIDe);
   fChain->SetBranchAddress("muplus_VeloCharge", &muplus_VeloCharge, &b_muplus_VeloCharge);
   fChain->SetBranchAddress("muplus_TRACK_Type", &muplus_TRACK_Type, &b_muplus_TRACK_Type);
   fChain->SetBranchAddress("muplus_TRACK_Key", &muplus_TRACK_Key, &b_muplus_TRACK_Key);
   fChain->SetBranchAddress("muplus_TRACK_CHI2", &muplus_TRACK_CHI2, &b_muplus_TRACK_CHI2);
   fChain->SetBranchAddress("muplus_TRACK_NDOF", &muplus_TRACK_NDOF, &b_muplus_TRACK_NDOF);
   fChain->SetBranchAddress("muplus_TRACK_CHI2NDOF", &muplus_TRACK_CHI2NDOF, &b_muplus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("muplus_TRACK_PCHI2", &muplus_TRACK_PCHI2, &b_muplus_TRACK_PCHI2);
   fChain->SetBranchAddress("muplus_TRACK_VeloCHI2NDOF", &muplus_TRACK_VeloCHI2NDOF, &b_muplus_TRACK_VeloCHI2NDOF);
   fChain->SetBranchAddress("muplus_TRACK_TCHI2NDOF", &muplus_TRACK_TCHI2NDOF, &b_muplus_TRACK_TCHI2NDOF);
   fChain->SetBranchAddress("muplus_VELO_UTID", &muplus_VELO_UTID, &b_muplus_VELO_UTID);
   fChain->SetBranchAddress("muplus_TRACK_FirstMeasurementX", &muplus_TRACK_FirstMeasurementX, &b_muplus_TRACK_FirstMeasurementX);
   fChain->SetBranchAddress("muplus_TRACK_FirstMeasurementY", &muplus_TRACK_FirstMeasurementY, &b_muplus_TRACK_FirstMeasurementY);
   fChain->SetBranchAddress("muplus_TRACK_FirstMeasurementZ", &muplus_TRACK_FirstMeasurementZ, &b_muplus_TRACK_FirstMeasurementZ);
   fChain->SetBranchAddress("muplus_TRACK_MatchCHI2", &muplus_TRACK_MatchCHI2, &b_muplus_TRACK_MatchCHI2);
   fChain->SetBranchAddress("muplus_TRACK_GhostProb", &muplus_TRACK_GhostProb, &b_muplus_TRACK_GhostProb);
   fChain->SetBranchAddress("muplus_TRACK_CloneDist", &muplus_TRACK_CloneDist, &b_muplus_TRACK_CloneDist);
   fChain->SetBranchAddress("muplus_TRACK_Likelihood", &muplus_TRACK_Likelihood, &b_muplus_TRACK_Likelihood);
   fChain->SetBranchAddress("nCandidate", &nCandidate, &b_nCandidate);
   fChain->SetBranchAddress("totCandidates", &totCandidates, &b_totCandidates);
   fChain->SetBranchAddress("EventInSequence", &EventInSequence, &b_EventInSequence);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("BCID", &BCID, &b_BCID);
   fChain->SetBranchAddress("BCType", &BCType, &b_BCType);
   fChain->SetBranchAddress("OdinTCK", &OdinTCK, &b_OdinTCK);
   fChain->SetBranchAddress("L0DUTCK", &L0DUTCK, &b_L0DUTCK);
   fChain->SetBranchAddress("HLTTCK", &HLTTCK, &b_HLTTCK);
   fChain->SetBranchAddress("GpsTime", &GpsTime, &b_GpsTime);
   fChain->SetBranchAddress("GpsYear", &GpsYear, &b_GpsYear);
   fChain->SetBranchAddress("GpsMonth", &GpsMonth, &b_GpsMonth);
   fChain->SetBranchAddress("GpsDay", &GpsDay, &b_GpsDay);
   fChain->SetBranchAddress("GpsHour", &GpsHour, &b_GpsHour);
   fChain->SetBranchAddress("GpsMinute", &GpsMinute, &b_GpsMinute);
   fChain->SetBranchAddress("GpsSecond", &GpsSecond, &b_GpsSecond);
   fChain->SetBranchAddress("TriggerType", &TriggerType, &b_TriggerType);
   fChain->SetBranchAddress("Polarity", &Polarity, &b_Polarity);
   fChain->SetBranchAddress("SignedRelativeCurrent", &SignedRelativeCurrent, &b_SignedRelativeCurrent);
   fChain->SetBranchAddress("PVX", PVX, &b_PVX);
   fChain->SetBranchAddress("PVY", PVY, &b_PVY);
   fChain->SetBranchAddress("PVZ", PVZ, &b_PVZ);
   fChain->SetBranchAddress("PVXERR", PVXERR, &b_PVXERR);
   fChain->SetBranchAddress("PVYERR", PVYERR, &b_PVYERR);
   fChain->SetBranchAddress("PVZERR", PVZERR, &b_PVZERR);
   fChain->SetBranchAddress("PVCHI2", PVCHI2, &b_PVCHI2);
   fChain->SetBranchAddress("PVNDOF", PVNDOF, &b_PVNDOF);
   fChain->SetBranchAddress("PVNTRACKS", PVNTRACKS, &b_PVNTRACKS);
   fChain->SetBranchAddress("nPVs", &nPVs, &b_nPVs);
   fChain->SetBranchAddress("nTracks", &nTracks, &b_nTracks);
   fChain->SetBranchAddress("nLongTracks", &nLongTracks, &b_nLongTracks);
   fChain->SetBranchAddress("nDownstreamTracks", &nDownstreamTracks, &b_nDownstreamTracks);
   fChain->SetBranchAddress("nUpstreamTracks", &nUpstreamTracks, &b_nUpstreamTracks);
   fChain->SetBranchAddress("nVeloTracks", &nVeloTracks, &b_nVeloTracks);
   fChain->SetBranchAddress("nTTracks", &nTTracks, &b_nTTracks);
   fChain->SetBranchAddress("nBackTracks", &nBackTracks, &b_nBackTracks);
   fChain->SetBranchAddress("nRich1Hits", &nRich1Hits, &b_nRich1Hits);
   fChain->SetBranchAddress("nRich2Hits", &nRich2Hits, &b_nRich2Hits);
   fChain->SetBranchAddress("nVeloClusters", &nVeloClusters, &b_nVeloClusters);
   fChain->SetBranchAddress("nITClusters", &nITClusters, &b_nITClusters);
   fChain->SetBranchAddress("nTTClusters", &nTTClusters, &b_nTTClusters);
   fChain->SetBranchAddress("nOTClusters", &nOTClusters, &b_nOTClusters);
   fChain->SetBranchAddress("nSPDHits", &nSPDHits, &b_nSPDHits);
   fChain->SetBranchAddress("nMuonCoordsS0", &nMuonCoordsS0, &b_nMuonCoordsS0);
   fChain->SetBranchAddress("nMuonCoordsS1", &nMuonCoordsS1, &b_nMuonCoordsS1);
   fChain->SetBranchAddress("nMuonCoordsS2", &nMuonCoordsS2, &b_nMuonCoordsS2);
   fChain->SetBranchAddress("nMuonCoordsS3", &nMuonCoordsS3, &b_nMuonCoordsS3);
   fChain->SetBranchAddress("nMuonCoordsS4", &nMuonCoordsS4, &b_nMuonCoordsS4);
   fChain->SetBranchAddress("nMuonTracks", &nMuonTracks, &b_nMuonTracks);
   fChain->SetBranchAddress("StrippingBetaSBd2JpsiKsDetachedLineDecision", &StrippingBetaSBd2JpsiKsDetachedLineDecision, &b_StrippingBetaSBd2JpsiKsDetachedLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBd2JpsiKsPrescaledLineDecision", &StrippingBetaSBd2JpsiKsPrescaledLineDecision, &b_StrippingBetaSBd2JpsiKsPrescaledLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBd2JpsiKstarDetachedLineDecision", &StrippingBetaSBd2JpsiKstarDetachedLineDecision, &b_StrippingBetaSBd2JpsiKstarDetachedLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBd2JpsiKstarPrescaledLineDecision", &StrippingBetaSBd2JpsiKstarPrescaledLineDecision, &b_StrippingBetaSBd2JpsiKstarPrescaledLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBs2ChicPhi_Chic2KKPiPiNominalLineDecision", &StrippingBetaSBs2ChicPhi_Chic2KKPiPiNominalLineDecision, &b_StrippingBetaSBs2ChicPhi_Chic2KKPiPiNominalLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBs2ChicPhi_Chic2PiPiPiPiNominalLineDecision", &StrippingBetaSBs2ChicPhi_Chic2PiPiPiPiNominalLineDecision, &b_StrippingBetaSBs2ChicPhi_Chic2PiPiPiPiNominalLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBs2EtacPhiNominalLineDecision", &StrippingBetaSBs2EtacPhiNominalLineDecision, &b_StrippingBetaSBs2EtacPhiNominalLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBs2JpsiEtaDetachedLineDecision", &StrippingBetaSBs2JpsiEtaDetachedLineDecision, &b_StrippingBetaSBs2JpsiEtaDetachedLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBs2JpsiEtaPrescaledLineDecision", &StrippingBetaSBs2JpsiEtaPrescaledLineDecision, &b_StrippingBetaSBs2JpsiEtaPrescaledLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBs2JpsiKstarLineDecision", &StrippingBetaSBs2JpsiKstarLineDecision, &b_StrippingBetaSBs2JpsiKstarLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBs2JpsiPhiDetachedLineDecision", &StrippingBetaSBs2JpsiPhiDetachedLineDecision, &b_StrippingBetaSBs2JpsiPhiDetachedLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBs2JpsiPhiPrescaledLineDecision", &StrippingBetaSBs2JpsiPhiPrescaledLineDecision, &b_StrippingBetaSBs2JpsiPhiPrescaledLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBs2JpsieePhiDetachedLineDecision", &StrippingBetaSBs2JpsieePhiDetachedLineDecision, &b_StrippingBetaSBs2JpsieePhiDetachedLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBs2JpsieePhiLineDecision", &StrippingBetaSBs2JpsieePhiLineDecision, &b_StrippingBetaSBs2JpsieePhiLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBs2Jpsif0LineDecision", &StrippingBetaSBs2Jpsif0LineDecision, &b_StrippingBetaSBs2Jpsif0LineDecision);
   fChain->SetBranchAddress("StrippingBetaSBs2K0stK0stNominalLineDecision", &StrippingBetaSBs2K0stK0stNominalLineDecision, &b_StrippingBetaSBs2K0stK0stNominalLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBs2KstKstNominalLineDecision", &StrippingBetaSBs2KstKstNominalLineDecision, &b_StrippingBetaSBs2KstKstNominalLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBs2KstKstSameChargeLineDecision", &StrippingBetaSBs2KstKstSameChargeLineDecision, &b_StrippingBetaSBs2KstKstSameChargeLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBs2PhiKstNominalLineDecision", &StrippingBetaSBs2PhiKstNominalLineDecision, &b_StrippingBetaSBs2PhiKstNominalLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBs2PhiPhiLineDecision", &StrippingBetaSBs2PhiPhiLineDecision, &b_StrippingBetaSBs2PhiPhiLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBs2PhiPhiWideLineDecision", &StrippingBetaSBs2PhiPhiWideLineDecision, &b_StrippingBetaSBs2PhiPhiWideLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBs2Q2Body4piLineDecision", &StrippingBetaSBs2Q2Body4piLineDecision, &b_StrippingBetaSBs2Q2Body4piLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBu2JpsiKDetachedLineDecision", &StrippingBetaSBu2JpsiKDetachedLineDecision, &b_StrippingBetaSBu2JpsiKDetachedLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBu2JpsiKNoPIDDetachedLineDecision", &StrippingBetaSBu2JpsiKNoPIDDetachedLineDecision, &b_StrippingBetaSBu2JpsiKNoPIDDetachedLineDecision);
   fChain->SetBranchAddress("StrippingBetaSBu2JpsiKPrescaledLineDecision", &StrippingBetaSBu2JpsiKPrescaledLineDecision, &b_StrippingBetaSBu2JpsiKPrescaledLineDecision);
   fChain->SetBranchAddress("StrippingBetaSJpsi2MuMuDetachedLineDecision", &StrippingBetaSJpsi2MuMuDetachedLineDecision, &b_StrippingBetaSJpsi2MuMuDetachedLineDecision);
   fChain->SetBranchAddress("StrippingBetaSJpsi2MuMuLineDecision", &StrippingBetaSJpsi2MuMuLineDecision, &b_StrippingBetaSJpsi2MuMuLineDecision);
   fChain->SetBranchAddress("StrippingBetaSLambdab2JpsiLambdaUnbiasedLineDecision", &StrippingBetaSLambdab2JpsiLambdaUnbiasedLineDecision, &b_StrippingBetaSLambdab2JpsiLambdaUnbiasedLineDecision);
   fChain->SetBranchAddress("StrippingBu2LLK_eeLineDecision", &StrippingBu2LLK_eeLineDecision, &b_StrippingBu2LLK_eeLineDecision);
   fChain->SetBranchAddress("StrippingBu2LLK_mmLineDecision", &StrippingBu2LLK_mmLineDecision, &b_StrippingBu2LLK_mmLineDecision);
   fChain->SetBranchAddress("StrippingBd2KstarMuMu_BdToKstarMuMuLineDecision", &StrippingBd2KstarMuMu_BdToKstarMuMuLineDecision, &b_StrippingBd2KstarMuMu_BdToKstarMuMuLineDecision);
   fChain->SetBranchAddress("StrippingBd2KstarMuMu_BdToKstarMuMuLowPLineDecision", &StrippingBd2KstarMuMu_BdToKstarMuMuLowPLineDecision, &b_StrippingBd2KstarMuMu_BdToKstarMuMuLowPLineDecision);
   fChain->SetBranchAddress("StrippingBd2KstarMuMu_BdToKstarMuMuSSLineDecision", &StrippingBd2KstarMuMu_BdToKstarMuMuSSLineDecision, &b_StrippingBd2KstarMuMu_BdToKstarMuMuSSLineDecision);
   fChain->SetBranchAddress("StrippingBd2KstarMuMu_BdToKstarMuMuSSLowPLineDecision", &StrippingBd2KstarMuMu_BdToKstarMuMuSSLowPLineDecision, &b_StrippingBd2KstarMuMu_BdToKstarMuMuSSLowPLineDecision);
   fChain->SetBranchAddress("StrippingBd2KstarMuMu_BuToKMuMuLineDecision", &StrippingBd2KstarMuMu_BuToKMuMuLineDecision, &b_StrippingBd2KstarMuMu_BuToKMuMuLineDecision);
   fChain->SetBranchAddress("StrippingBd2KstarMuMu_BuToKMuMuSSLineDecision", &StrippingBd2KstarMuMu_BuToKMuMuSSLineDecision, &b_StrippingBd2KstarMuMu_BuToKMuMuSSLineDecision);

   // backward compatibility

   fChain->SetBranchAddress("PsiL0Global_Dec", &PsiL0Global_Dec, &b_PsiL0Global_Dec);
   fChain->SetBranchAddress("PsiL0Global_TIS", &PsiL0Global_TIS, &b_PsiL0Global_TIS);
   fChain->SetBranchAddress("PsiL0Global_TOS", &PsiL0Global_TOS, &b_PsiL0Global_TOS);
   fChain->SetBranchAddress("PsiHlt1Global_Dec", &PsiHlt1Global_Dec, &b_PsiHlt1Global_Dec);
   fChain->SetBranchAddress("PsiHlt1Global_TIS", &PsiHlt1Global_TIS, &b_PsiHlt1Global_TIS);
   fChain->SetBranchAddress("PsiHlt1Global_TOS", &PsiHlt1Global_TOS, &b_PsiHlt1Global_TOS);
   fChain->SetBranchAddress("PsiHlt1Phys_Dec", &PsiHlt1Phys_Dec, &b_PsiHlt1Phys_Dec);
   fChain->SetBranchAddress("PsiHlt1Phys_TIS", &PsiHlt1Phys_TIS, &b_PsiHlt1Phys_TIS);
   fChain->SetBranchAddress("PsiHlt1Phys_TOS", &PsiHlt1Phys_TOS, &b_PsiHlt1Phys_TOS);
   fChain->SetBranchAddress("PsiHlt2Global_Dec", &PsiHlt2Global_Dec, &b_PsiHlt2Global_Dec);
   fChain->SetBranchAddress("PsiHlt2Global_TIS", &PsiHlt2Global_TIS, &b_PsiHlt2Global_TIS);
   fChain->SetBranchAddress("PsiHlt2Global_TOS", &PsiHlt2Global_TOS, &b_PsiHlt2Global_TOS);
   fChain->SetBranchAddress("PsiHlt2Phys_Dec", &PsiHlt2Phys_Dec, &b_PsiHlt2Phys_Dec);
   fChain->SetBranchAddress("PsiHlt2Phys_TIS", &PsiHlt2Phys_TIS, &b_PsiHlt2Phys_TIS);
   fChain->SetBranchAddress("PsiHlt2Phys_TOS", &PsiHlt2Phys_TOS, &b_PsiHlt2Phys_TOS);
   fChain->SetBranchAddress("PsiHlt1TrackAllL0Decision_Dec", &PsiHlt1TrackAllL0Decision_Dec, &b_PsiHlt1TrackAllL0Decision_Dec);
   fChain->SetBranchAddress("PsiHlt1TrackAllL0Decision_TIS", &PsiHlt1TrackAllL0Decision_TIS, &b_PsiHlt1TrackAllL0Decision_TIS);
   fChain->SetBranchAddress("PsiHlt1TrackAllL0Decision_TOS", &PsiHlt1TrackAllL0Decision_TOS, &b_PsiHlt1TrackAllL0Decision_TOS);
   fChain->SetBranchAddress("PsiHlt1TrackAllL0TightDecision_Dec", &PsiHlt1TrackAllL0TightDecision_Dec, &b_PsiHlt1TrackAllL0TightDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1TrackAllL0TightDecision_TIS", &PsiHlt1TrackAllL0TightDecision_TIS, &b_PsiHlt1TrackAllL0TightDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1TrackAllL0TightDecision_TOS", &PsiHlt1TrackAllL0TightDecision_TOS, &b_PsiHlt1TrackAllL0TightDecision_TOS);
   fChain->SetBranchAddress("PsiHlt1DiMuonHighMassDecision_Dec", &PsiHlt1DiMuonHighMassDecision_Dec, &b_PsiHlt1DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1DiMuonHighMassDecision_TIS", &PsiHlt1DiMuonHighMassDecision_TIS, &b_PsiHlt1DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1DiMuonHighMassDecision_TOS", &PsiHlt1DiMuonHighMassDecision_TOS, &b_PsiHlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("PsiHlt1DiMuonLowMassDecision_Dec", &PsiHlt1DiMuonLowMassDecision_Dec, &b_PsiHlt1DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1DiMuonLowMassDecision_TIS", &PsiHlt1DiMuonLowMassDecision_TIS, &b_PsiHlt1DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1DiMuonLowMassDecision_TOS", &PsiHlt1DiMuonLowMassDecision_TOS, &b_PsiHlt1DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("PsiHlt1SingleMuonHighPTDecision_Dec", &PsiHlt1SingleMuonHighPTDecision_Dec, &b_PsiHlt1SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1SingleMuonHighPTDecision_TIS", &PsiHlt1SingleMuonHighPTDecision_TIS, &b_PsiHlt1SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1SingleMuonHighPTDecision_TOS", &PsiHlt1SingleMuonHighPTDecision_TOS, &b_PsiHlt1SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt1SingleMuonNoIPDecision_Dec", &PsiHlt1SingleMuonNoIPDecision_Dec, &b_PsiHlt1SingleMuonNoIPDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1SingleMuonNoIPDecision_TIS", &PsiHlt1SingleMuonNoIPDecision_TIS, &b_PsiHlt1SingleMuonNoIPDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1SingleMuonNoIPDecision_TOS", &PsiHlt1SingleMuonNoIPDecision_TOS, &b_PsiHlt1SingleMuonNoIPDecision_TOS);
   fChain->SetBranchAddress("PsiHlt1TrackMuonDecision_Dec", &PsiHlt1TrackMuonDecision_Dec, &b_PsiHlt1TrackMuonDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1TrackMuonDecision_TIS", &PsiHlt1TrackMuonDecision_TIS, &b_PsiHlt1TrackMuonDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1TrackMuonDecision_TOS", &PsiHlt1TrackMuonDecision_TOS, &b_PsiHlt1TrackMuonDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2Topo2BodyBBDTDecision_Dec", &PsiHlt2Topo2BodyBBDTDecision_Dec, &b_PsiHlt2Topo2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2Topo2BodyBBDTDecision_TIS", &PsiHlt2Topo2BodyBBDTDecision_TIS, &b_PsiHlt2Topo2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2Topo2BodyBBDTDecision_TOS", &PsiHlt2Topo2BodyBBDTDecision_TOS, &b_PsiHlt2Topo2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2Topo2BodySimpleDecision_Dec", &PsiHlt2Topo2BodySimpleDecision_Dec, &b_PsiHlt2Topo2BodySimpleDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2Topo2BodySimpleDecision_TIS", &PsiHlt2Topo2BodySimpleDecision_TIS, &b_PsiHlt2Topo2BodySimpleDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2Topo2BodySimpleDecision_TOS", &PsiHlt2Topo2BodySimpleDecision_TOS, &b_PsiHlt2Topo2BodySimpleDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2Topo3BodyBBDTDecision_Dec", &PsiHlt2Topo3BodyBBDTDecision_Dec, &b_PsiHlt2Topo3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2Topo3BodyBBDTDecision_TIS", &PsiHlt2Topo3BodyBBDTDecision_TIS, &b_PsiHlt2Topo3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2Topo3BodyBBDTDecision_TOS", &PsiHlt2Topo3BodyBBDTDecision_TOS, &b_PsiHlt2Topo3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2Topo3BodySimpleDecision_Dec", &PsiHlt2Topo3BodySimpleDecision_Dec, &b_PsiHlt2Topo3BodySimpleDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2Topo3BodySimpleDecision_TIS", &PsiHlt2Topo3BodySimpleDecision_TIS, &b_PsiHlt2Topo3BodySimpleDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2Topo3BodySimpleDecision_TOS", &PsiHlt2Topo3BodySimpleDecision_TOS, &b_PsiHlt2Topo3BodySimpleDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2Topo4BodyBBDTDecision_Dec", &PsiHlt2Topo4BodyBBDTDecision_Dec, &b_PsiHlt2Topo4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2Topo4BodyBBDTDecision_TIS", &PsiHlt2Topo4BodyBBDTDecision_TIS, &b_PsiHlt2Topo4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2Topo4BodyBBDTDecision_TOS", &PsiHlt2Topo4BodyBBDTDecision_TOS, &b_PsiHlt2Topo4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2Topo4BodySimpleDecision_Dec", &PsiHlt2Topo4BodySimpleDecision_Dec, &b_PsiHlt2Topo4BodySimpleDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2Topo4BodySimpleDecision_TIS", &PsiHlt2Topo4BodySimpleDecision_TIS, &b_PsiHlt2Topo4BodySimpleDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2Topo4BodySimpleDecision_TOS", &PsiHlt2Topo4BodySimpleDecision_TOS, &b_PsiHlt2Topo4BodySimpleDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonDecision_Dec", &PsiHlt2DiMuonDecision_Dec, &b_PsiHlt2DiMuonDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonDecision_TIS", &PsiHlt2DiMuonDecision_TIS, &b_PsiHlt2DiMuonDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonDecision_TOS", &PsiHlt2DiMuonDecision_TOS, &b_PsiHlt2DiMuonDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonBDecision_Dec", &PsiHlt2DiMuonBDecision_Dec, &b_PsiHlt2DiMuonBDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonBDecision_TIS", &PsiHlt2DiMuonBDecision_TIS, &b_PsiHlt2DiMuonBDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonBDecision_TOS", &PsiHlt2DiMuonBDecision_TOS, &b_PsiHlt2DiMuonBDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonDetachedDecision_Dec", &PsiHlt2DiMuonDetachedDecision_Dec, &b_PsiHlt2DiMuonDetachedDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonDetachedDecision_TIS", &PsiHlt2DiMuonDetachedDecision_TIS, &b_PsiHlt2DiMuonDetachedDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonDetachedDecision_TOS", &PsiHlt2DiMuonDetachedDecision_TOS, &b_PsiHlt2DiMuonDetachedDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonDetachedHeavyDecision_Dec", &PsiHlt2DiMuonDetachedHeavyDecision_Dec, &b_PsiHlt2DiMuonDetachedHeavyDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonDetachedHeavyDecision_TIS", &PsiHlt2DiMuonDetachedHeavyDecision_TIS, &b_PsiHlt2DiMuonDetachedHeavyDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonDetachedHeavyDecision_TOS", &PsiHlt2DiMuonDetachedHeavyDecision_TOS, &b_PsiHlt2DiMuonDetachedHeavyDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonDetachedJPsiDecision_Dec", &PsiHlt2DiMuonDetachedJPsiDecision_Dec, &b_PsiHlt2DiMuonDetachedJPsiDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonDetachedJPsiDecision_TIS", &PsiHlt2DiMuonDetachedJPsiDecision_TIS, &b_PsiHlt2DiMuonDetachedJPsiDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonDetachedJPsiDecision_TOS", &PsiHlt2DiMuonDetachedJPsiDecision_TOS, &b_PsiHlt2DiMuonDetachedJPsiDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonDetachedPsi2SDecision_Dec", &PsiHlt2DiMuonDetachedPsi2SDecision_Dec, &b_PsiHlt2DiMuonDetachedPsi2SDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonDetachedPsi2SDecision_TIS", &PsiHlt2DiMuonDetachedPsi2SDecision_TIS, &b_PsiHlt2DiMuonDetachedPsi2SDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonDetachedPsi2SDecision_TOS", &PsiHlt2DiMuonDetachedPsi2SDecision_TOS, &b_PsiHlt2DiMuonDetachedPsi2SDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonJPsiDecision_Dec", &PsiHlt2DiMuonJPsiDecision_Dec, &b_PsiHlt2DiMuonJPsiDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonJPsiDecision_TIS", &PsiHlt2DiMuonJPsiDecision_TIS, &b_PsiHlt2DiMuonJPsiDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonJPsiDecision_TOS", &PsiHlt2DiMuonJPsiDecision_TOS, &b_PsiHlt2DiMuonJPsiDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonJPsiHighPTDecision_Dec", &PsiHlt2DiMuonJPsiHighPTDecision_Dec, &b_PsiHlt2DiMuonJPsiHighPTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonJPsiHighPTDecision_TIS", &PsiHlt2DiMuonJPsiHighPTDecision_TIS, &b_PsiHlt2DiMuonJPsiHighPTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonJPsiHighPTDecision_TOS", &PsiHlt2DiMuonJPsiHighPTDecision_TOS, &b_PsiHlt2DiMuonJPsiHighPTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonLowMassDecision_Dec", &PsiHlt2DiMuonLowMassDecision_Dec, &b_PsiHlt2DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonLowMassDecision_TIS", &PsiHlt2DiMuonLowMassDecision_TIS, &b_PsiHlt2DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonLowMassDecision_TOS", &PsiHlt2DiMuonLowMassDecision_TOS, &b_PsiHlt2DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonPsi2SDecision_Dec", &PsiHlt2DiMuonPsi2SDecision_Dec, &b_PsiHlt2DiMuonPsi2SDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonPsi2SDecision_TIS", &PsiHlt2DiMuonPsi2SDecision_TIS, &b_PsiHlt2DiMuonPsi2SDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonPsi2SDecision_TOS", &PsiHlt2DiMuonPsi2SDecision_TOS, &b_PsiHlt2DiMuonPsi2SDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonPsi2SHighPTDecision_Dec", &PsiHlt2DiMuonPsi2SHighPTDecision_Dec, &b_PsiHlt2DiMuonPsi2SHighPTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonPsi2SHighPTDecision_TIS", &PsiHlt2DiMuonPsi2SHighPTDecision_TIS, &b_PsiHlt2DiMuonPsi2SHighPTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonPsi2SHighPTDecision_TOS", &PsiHlt2DiMuonPsi2SHighPTDecision_TOS, &b_PsiHlt2DiMuonPsi2SHighPTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2LowMultMuonDecision_Dec", &PsiHlt2LowMultMuonDecision_Dec, &b_PsiHlt2LowMultMuonDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2LowMultMuonDecision_TIS", &PsiHlt2LowMultMuonDecision_TIS, &b_PsiHlt2LowMultMuonDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2LowMultMuonDecision_TOS", &PsiHlt2LowMultMuonDecision_TOS, &b_PsiHlt2LowMultMuonDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2MuonFromHLT1Decision_Dec", &PsiHlt2MuonFromHLT1Decision_Dec, &b_PsiHlt2MuonFromHLT1Decision_Dec);
   fChain->SetBranchAddress("PsiHlt2MuonFromHLT1Decision_TIS", &PsiHlt2MuonFromHLT1Decision_TIS, &b_PsiHlt2MuonFromHLT1Decision_TIS);
   fChain->SetBranchAddress("PsiHlt2MuonFromHLT1Decision_TOS", &PsiHlt2MuonFromHLT1Decision_TOS, &b_PsiHlt2MuonFromHLT1Decision_TOS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonDecision_Dec", &PsiHlt2SingleMuonDecision_Dec, &b_PsiHlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2SingleMuonDecision_TIS", &PsiHlt2SingleMuonDecision_TIS, &b_PsiHlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonDecision_TOS", &PsiHlt2SingleMuonDecision_TOS, &b_PsiHlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonHighPTDecision_Dec", &PsiHlt2SingleMuonHighPTDecision_Dec, &b_PsiHlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2SingleMuonHighPTDecision_TIS", &PsiHlt2SingleMuonHighPTDecision_TIS, &b_PsiHlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonHighPTDecision_TOS", &PsiHlt2SingleMuonHighPTDecision_TOS, &b_PsiHlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonLowPTDecision_Dec", &PsiHlt2SingleMuonLowPTDecision_Dec, &b_PsiHlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2SingleMuonLowPTDecision_TIS", &PsiHlt2SingleMuonLowPTDecision_TIS, &b_PsiHlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonLowPTDecision_TOS", &PsiHlt2SingleMuonLowPTDecision_TOS, &b_PsiHlt2SingleMuonLowPTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonVHighPTDecision_Dec", &PsiHlt2SingleMuonVHighPTDecision_Dec, &b_PsiHlt2SingleMuonVHighPTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2SingleMuonVHighPTDecision_TIS", &PsiHlt2SingleMuonVHighPTDecision_TIS, &b_PsiHlt2SingleMuonVHighPTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonVHighPTDecision_TOS", &PsiHlt2SingleMuonVHighPTDecision_TOS, &b_PsiHlt2SingleMuonVHighPTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2TopoMu2BodyBBDTDecision_Dec", &PsiHlt2TopoMu2BodyBBDTDecision_Dec, &b_PsiHlt2TopoMu2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2TopoMu2BodyBBDTDecision_TIS", &PsiHlt2TopoMu2BodyBBDTDecision_TIS, &b_PsiHlt2TopoMu2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2TopoMu2BodyBBDTDecision_TOS", &PsiHlt2TopoMu2BodyBBDTDecision_TOS, &b_PsiHlt2TopoMu2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2TopoMu3BodyBBDTDecision_Dec", &PsiHlt2TopoMu3BodyBBDTDecision_Dec, &b_PsiHlt2TopoMu3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2TopoMu3BodyBBDTDecision_TIS", &PsiHlt2TopoMu3BodyBBDTDecision_TIS, &b_PsiHlt2TopoMu3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2TopoMu3BodyBBDTDecision_TOS", &PsiHlt2TopoMu3BodyBBDTDecision_TOS, &b_PsiHlt2TopoMu3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2TopoMu4BodyBBDTDecision_Dec", &PsiHlt2TopoMu4BodyBBDTDecision_Dec, &b_PsiHlt2TopoMu4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2TopoMu4BodyBBDTDecision_TIS", &PsiHlt2TopoMu4BodyBBDTDecision_TIS, &b_PsiHlt2TopoMu4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2TopoMu4BodyBBDTDecision_TOS", &PsiHlt2TopoMu4BodyBBDTDecision_TOS, &b_PsiHlt2TopoMu4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2diPhotonDiMuonDecision_Dec", &PsiHlt2diPhotonDiMuonDecision_Dec, &b_PsiHlt2diPhotonDiMuonDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2diPhotonDiMuonDecision_TIS", &PsiHlt2diPhotonDiMuonDecision_TIS, &b_PsiHlt2diPhotonDiMuonDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2diPhotonDiMuonDecision_TOS", &PsiHlt2diPhotonDiMuonDecision_TOS, &b_PsiHlt2diPhotonDiMuonDecision_TOS);
   
}

#endif // #ifdef Lb2JpsiL_2012_cxx
