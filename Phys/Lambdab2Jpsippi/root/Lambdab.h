//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Mar 15 10:41:03 2013 by ROOT version 5.34/03
// from TTree DecayTree/DecayTree
// found on file: castor:///castor/cern.ch/user/p/pkoppenb/Lambdab/Lambdab-S20r1-950.root
//////////////////////////////////////////////////////////

#ifndef Lambdab_h
#define Lambdab_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include "Tuples.h"

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.
const Int_t kMaxB_ENDVERTEX_COV = 1;
const Int_t kMaxB_OWNPV_COV = 1;
const Int_t kMaxpiminus_OWNPV_COV = 1;
const Int_t kMaxpiminus_ORIVX_COV = 1;
const Int_t kMaxpplus_OWNPV_COV = 1;
const Int_t kMaxpplus_ORIVX_COV = 1;
const Int_t kMaxPsi_ENDVERTEX_COV = 1;
const Int_t kMaxPsi_OWNPV_COV = 1;
const Int_t kMaxPsi_ORIVX_COV = 1;
const Int_t kMaxmuminus_OWNPV_COV = 1;
const Int_t kMaxmuminus_ORIVX_COV = 1;
const Int_t kMaxmuplus_OWNPV_COV = 1;
const Int_t kMaxmuplus_ORIVX_COV = 1;

class Lambdab {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   TTree          *fFriend;  //!pointer to the friend file (brilliant idea by Rob)

   // Declaration of leaf types
   Int_t           nPV;
   Float_t         B_AllIP[100];   //[nPV]
   Float_t         B_AllIPchi2[100];   //[nPV]
   Float_t         B_AllDIRA[100];   //[nPV]
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
   Double_t        B_P;
   Double_t        B_PT;
   Double_t        B_PE;
   Double_t        B_PX;
   Double_t        B_PY;
   Double_t        B_PZ;
   Double_t        B_MM;
   Double_t        B_MMERR;
   Double_t        B_M;
   Int_t           B_ID;
   Double_t        B_TAU;
   Double_t        B_TAUERR;
   Double_t        B_TAUCHI2;
   Double_t        Dalitz_pplus_J_psi_1S_M2;
   Double_t        Dalitz_piminus_J_psi_1S_M2;
   Double_t        Dalitz_piminus_pplus_M2;
   Int_t           B_ConstBFit_nPV;
   Float_t         B_ConstBFit_J_psi_1S_M[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_MERR[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_P[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_muminus_ID[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_muminus_PE[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_muminus_PX[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_muminus_PY[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_muminus_PZ[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_muminus_0_ID[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_muminus_0_PE[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_muminus_0_PX[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_muminus_0_PY[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_muminus_0_PZ[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_PERR[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_ctau[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_ctauErr[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_decayLength[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_J_psi_1S_decayLengthErr[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_M[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_MERR[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_P[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_pplus_ID[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_pplus_PE[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_pplus_PX[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_pplus_PY[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_pplus_PZ[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_piplus_ID[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_piplus_PE[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_piplus_PX[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_piplus_PY[100];   //[B_ConstBFit_nPV]
   Float_t         B_ConstBFit_piplus_PZ[100];   //[B_ConstBFit_nPV]
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
   Int_t           B_ConstBSubFit_nPV;
   Float_t         B_ConstBSubFit_J_psi_1S_M[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_J_psi_1S_MERR[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_J_psi_1S_P[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_J_psi_1S_PERR[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_J_psi_1S_ctau[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_J_psi_1S_ctauErr[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_J_psi_1S_decayLength[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_J_psi_1S_decayLengthErr[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_J_psi_1S_muminus_0_ID[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_J_psi_1S_muminus_0_PE[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_J_psi_1S_muminus_0_PX[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_J_psi_1S_muminus_0_PY[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_J_psi_1S_muminus_0_PZ[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_J_psi_1S_muminus_ID[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_J_psi_1S_muminus_PE[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_J_psi_1S_muminus_PX[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_J_psi_1S_muminus_PY[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_J_psi_1S_muminus_PZ[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_Kplus_ID[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_Kplus_PE[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_Kplus_PX[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_Kplus_PY[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_Kplus_PZ[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_M[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_MERR[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_P[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_PERR[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_PV_X[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_PV_Y[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_PV_Z[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_PV_key[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_chi2[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_ctau[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_ctauErr[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_decayLength[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_decayLengthErr[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_nDOF[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_nIter[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_pplus_ID[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_pplus_PE[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_pplus_PX[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_pplus_PY[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_pplus_PZ[100];   //[B_ConstBSubFit_nPV]
   Float_t         B_ConstBSubFit_status[100];   //[B_ConstBSubFit_nPV]
   Int_t           B_FullFit_nPV;
   Float_t         B_FullFit_J_psi_1S_M[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_MERR[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_P[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_PERR[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_ctau[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_ctauErr[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_decayLength[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_decayLengthErr[100];   //[B_FullFit_nPV]
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
   Int_t           B_SubKpi_nPV;
   Float_t         B_SubKpi_M[100];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_MERR[100];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_P[100];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_PERR[100];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_PV_key[100];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_chi2[100];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_ctau[100];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_ctauErr[100];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_decayLength[100];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_decayLengthErr[100];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_nDOF[100];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_nIter[100];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_status[100];   //[B_SubKpi_nPV]
   Int_t           B_SubpK_nPV;
   Float_t         B_SubpK_M[100];   //[B_SubpK_nPV]
   Float_t         B_SubpK_MERR[100];   //[B_SubpK_nPV]
   Float_t         B_SubpK_P[100];   //[B_SubpK_nPV]
   Float_t         B_SubpK_PERR[100];   //[B_SubpK_nPV]
   Float_t         B_SubpK_PV_key[100];   //[B_SubpK_nPV]
   Float_t         B_SubpK_chi2[100];   //[B_SubpK_nPV]
   Float_t         B_SubpK_ctau[100];   //[B_SubpK_nPV]
   Float_t         B_SubpK_ctauErr[100];   //[B_SubpK_nPV]
   Float_t         B_SubpK_decayLength[100];   //[B_SubpK_nPV]
   Float_t         B_SubpK_decayLengthErr[100];   //[B_SubpK_nPV]
   Float_t         B_SubpK_nDOF[100];   //[B_SubpK_nPV]
   Float_t         B_SubpK_nIter[100];   //[B_SubpK_nPV]
   Float_t         B_SubpK_status[100];   //[B_SubpK_nPV]
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
   Double_t        piminus_CosTheta;
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
   Double_t        piminus_ORIVX_X;
   Double_t        piminus_ORIVX_Y;
   Double_t        piminus_ORIVX_Z;
   Double_t        piminus_ORIVX_XERR;
   Double_t        piminus_ORIVX_YERR;
   Double_t        piminus_ORIVX_ZERR;
   Double_t        piminus_ORIVX_CHI2;
   Int_t           piminus_ORIVX_NDOF;
   Float_t         piminus_ORIVX_COV_[3][3];
   Double_t        piminus_P;
   Double_t        piminus_PT;
   Double_t        piminus_PE;
   Double_t        piminus_PX;
   Double_t        piminus_PY;
   Double_t        piminus_PZ;
   Double_t        piminus_M;
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
   Int_t           piminus_TRACK_Type;
   Int_t           piminus_TRACK_Key;
   Double_t        piminus_TRACK_CHI2NDOF;
   Double_t        piminus_TRACK_PCHI2;
   Double_t        piminus_TRACK_MatchCHI2;
   Double_t        piminus_TRACK_GhostProb;
   Double_t        piminus_TRACK_CloneDist;
   Double_t        piminus_TRACK_Likelihood;
   Double_t        pplus_CosTheta;
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
   Double_t        pplus_ORIVX_X;
   Double_t        pplus_ORIVX_Y;
   Double_t        pplus_ORIVX_Z;
   Double_t        pplus_ORIVX_XERR;
   Double_t        pplus_ORIVX_YERR;
   Double_t        pplus_ORIVX_ZERR;
   Double_t        pplus_ORIVX_CHI2;
   Int_t           pplus_ORIVX_NDOF;
   Float_t         pplus_ORIVX_COV_[3][3];
   Double_t        pplus_P;
   Double_t        pplus_PT;
   Double_t        pplus_PE;
   Double_t        pplus_PX;
   Double_t        pplus_PY;
   Double_t        pplus_PZ;
   Double_t        pplus_M;
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
   Int_t           pplus_TRACK_Type;
   Int_t           pplus_TRACK_Key;
   Double_t        pplus_TRACK_CHI2NDOF;
   Double_t        pplus_TRACK_PCHI2;
   Double_t        pplus_TRACK_MatchCHI2;
   Double_t        pplus_TRACK_GhostProb;
   Double_t        pplus_TRACK_CloneDist;
   Double_t        pplus_TRACK_Likelihood;
   Double_t        Psi_CosTheta;
   Float_t         Psi_AllIP[100];   //[nPV]
   Float_t         Psi_AllIPchi2[100];   //[nPV]
   Float_t         Psi_AllDIRA[100];   //[nPV]
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
   Double_t        Psi_ORIVX_X;
   Double_t        Psi_ORIVX_Y;
   Double_t        Psi_ORIVX_Z;
   Double_t        Psi_ORIVX_XERR;
   Double_t        Psi_ORIVX_YERR;
   Double_t        Psi_ORIVX_ZERR;
   Double_t        Psi_ORIVX_CHI2;
   Int_t           Psi_ORIVX_NDOF;
   Float_t         Psi_ORIVX_COV_[3][3];
   Double_t        Psi_FD_ORIVX;
   Double_t        Psi_FDCHI2_ORIVX;
   Double_t        Psi_DIRA_ORIVX;
   Double_t        Psi_P;
   Double_t        Psi_PT;
   Double_t        Psi_PE;
   Double_t        Psi_PX;
   Double_t        Psi_PY;
   Double_t        Psi_PZ;
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
   Double_t        muminus_CosTheta;
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
   Double_t        muminus_ORIVX_X;
   Double_t        muminus_ORIVX_Y;
   Double_t        muminus_ORIVX_Z;
   Double_t        muminus_ORIVX_XERR;
   Double_t        muminus_ORIVX_YERR;
   Double_t        muminus_ORIVX_ZERR;
   Double_t        muminus_ORIVX_CHI2;
   Int_t           muminus_ORIVX_NDOF;
   Float_t         muminus_ORIVX_COV_[3][3];
   Double_t        muminus_P;
   Double_t        muminus_PT;
   Double_t        muminus_PE;
   Double_t        muminus_PX;
   Double_t        muminus_PY;
   Double_t        muminus_PZ;
   Double_t        muminus_M;
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
   Int_t           muminus_TRACK_Type;
   Int_t           muminus_TRACK_Key;
   Double_t        muminus_TRACK_CHI2NDOF;
   Double_t        muminus_TRACK_PCHI2;
   Double_t        muminus_TRACK_MatchCHI2;
   Double_t        muminus_TRACK_GhostProb;
   Double_t        muminus_TRACK_CloneDist;
   Double_t        muminus_TRACK_Likelihood;
   Double_t        muplus_CosTheta;
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
   Double_t        muplus_ORIVX_X;
   Double_t        muplus_ORIVX_Y;
   Double_t        muplus_ORIVX_Z;
   Double_t        muplus_ORIVX_XERR;
   Double_t        muplus_ORIVX_YERR;
   Double_t        muplus_ORIVX_ZERR;
   Double_t        muplus_ORIVX_CHI2;
   Int_t           muplus_ORIVX_NDOF;
   Float_t         muplus_ORIVX_COV_[3][3];
   Double_t        muplus_P;
   Double_t        muplus_PT;
   Double_t        muplus_PE;
   Double_t        muplus_PX;
   Double_t        muplus_PY;
   Double_t        muplus_PZ;
   Double_t        muplus_M;
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
   Int_t           muplus_TRACK_Type;
   Int_t           muplus_TRACK_Key;
   Double_t        muplus_TRACK_CHI2NDOF;
   Double_t        muplus_TRACK_PCHI2;
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
   Short_t         Polarity;
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

   // List of branches
   TBranch        *b_nPV;   //!
   TBranch        *b_B_AllIP;   //!
   TBranch        *b_B_AllIPchi2;   //!
   TBranch        *b_B_AllDIRA;   //!
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
   TBranch        *b_B_P;   //!
   TBranch        *b_B_PT;   //!
   TBranch        *b_B_PE;   //!
   TBranch        *b_B_PX;   //!
   TBranch        *b_B_PY;   //!
   TBranch        *b_B_PZ;   //!
   TBranch        *b_B_MM;   //!
   TBranch        *b_B_MMERR;   //!
   TBranch        *b_B_M;   //!
   TBranch        *b_B_ID;   //!
   TBranch        *b_B_TAU;   //!
   TBranch        *b_B_TAUERR;   //!
   TBranch        *b_B_TAUCHI2;   //!
   TBranch        *b_Dalitz_pplus_J_psi_1S_M2;   //!
   TBranch        *b_Dalitz_piminus_J_psi_1S_M2;   //!
   TBranch        *b_Dalitz_piminus_pplus_M2;   //!
   TBranch        *b_B_ConstBFit_nPV;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_M;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_MERR;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_P;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_muminus_0_ID;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_muminus_0_PE;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_muminus_0_PX;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_muminus_0_PY;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_muminus_0_PZ;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_muminus_ID;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_muminus_PE;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_muminus_PX;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_muminus_PY;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_muminus_PZ;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_PERR;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_ctau;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_ctauErr;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_decayLength;   //!
   TBranch        *b_B_ConstBFit_J_psi_1S_decayLengthErr;   //!
   TBranch        *b_B_ConstBFit_M;   //!
   TBranch        *b_B_ConstBFit_MERR;   //!
   TBranch        *b_B_ConstBFit_P;   //!
   TBranch        *b_B_ConstBFit_pplus_ID;   //!
   TBranch        *b_B_ConstBFit_pplus_PE;   //!
   TBranch        *b_B_ConstBFit_pplus_PX;   //!
   TBranch        *b_B_ConstBFit_pplus_PY;   //!
   TBranch        *b_B_ConstBFit_pplus_PZ;   //!
   TBranch        *b_B_ConstBFit_piplus_ID;   //!
   TBranch        *b_B_ConstBFit_piplus_PE;   //!
   TBranch        *b_B_ConstBFit_piplus_PX;   //!
   TBranch        *b_B_ConstBFit_piplus_PY;   //!
   TBranch        *b_B_ConstBFit_piplus_PZ;   //!
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
   TBranch        *b_B_ConstBSubFit_nPV;   //!
   TBranch        *b_B_ConstBSubFit_J_psi_1S_M;   //!
   TBranch        *b_B_ConstBSubFit_J_psi_1S_MERR;   //!
   TBranch        *b_B_ConstBSubFit_J_psi_1S_P;   //!
   TBranch        *b_B_ConstBSubFit_J_psi_1S_PERR;   //!
   TBranch        *b_B_ConstBSubFit_J_psi_1S_ctau;   //!
   TBranch        *b_B_ConstBSubFit_J_psi_1S_ctauErr;   //!
   TBranch        *b_B_ConstBSubFit_J_psi_1S_decayLength;   //!
   TBranch        *b_B_ConstBSubFit_J_psi_1S_decayLengthErr;   //!
   TBranch        *b_B_ConstBSubFit_J_psi_1S_muminus_0_ID;   //!
   TBranch        *b_B_ConstBSubFit_J_psi_1S_muminus_0_PE;   //!
   TBranch        *b_B_ConstBSubFit_J_psi_1S_muminus_0_PX;   //!
   TBranch        *b_B_ConstBSubFit_J_psi_1S_muminus_0_PY;   //!
   TBranch        *b_B_ConstBSubFit_J_psi_1S_muminus_0_PZ;   //!
   TBranch        *b_B_ConstBSubFit_J_psi_1S_muminus_ID;   //!
   TBranch        *b_B_ConstBSubFit_J_psi_1S_muminus_PE;   //!
   TBranch        *b_B_ConstBSubFit_J_psi_1S_muminus_PX;   //!
   TBranch        *b_B_ConstBSubFit_J_psi_1S_muminus_PY;   //!
   TBranch        *b_B_ConstBSubFit_J_psi_1S_muminus_PZ;   //!
   TBranch        *b_B_ConstBSubFit_Kplus_ID;   //!
   TBranch        *b_B_ConstBSubFit_Kplus_PE;   //!
   TBranch        *b_B_ConstBSubFit_Kplus_PX;   //!
   TBranch        *b_B_ConstBSubFit_Kplus_PY;   //!
   TBranch        *b_B_ConstBSubFit_Kplus_PZ;   //!
   TBranch        *b_B_ConstBSubFit_M;   //!
   TBranch        *b_B_ConstBSubFit_MERR;   //!
   TBranch        *b_B_ConstBSubFit_P;   //!
   TBranch        *b_B_ConstBSubFit_PERR;   //!
   TBranch        *b_B_ConstBSubFit_PV_X;   //!
   TBranch        *b_B_ConstBSubFit_PV_Y;   //!
   TBranch        *b_B_ConstBSubFit_PV_Z;   //!
   TBranch        *b_B_ConstBSubFit_PV_key;   //!
   TBranch        *b_B_ConstBSubFit_chi2;   //!
   TBranch        *b_B_ConstBSubFit_ctau;   //!
   TBranch        *b_B_ConstBSubFit_ctauErr;   //!
   TBranch        *b_B_ConstBSubFit_decayLength;   //!
   TBranch        *b_B_ConstBSubFit_decayLengthErr;   //!
   TBranch        *b_B_ConstBSubFit_nDOF;   //!
   TBranch        *b_B_ConstBSubFit_nIter;   //!
   TBranch        *b_B_ConstBSubFit_pplus_ID;   //!
   TBranch        *b_B_ConstBSubFit_pplus_PE;   //!
   TBranch        *b_B_ConstBSubFit_pplus_PX;   //!
   TBranch        *b_B_ConstBSubFit_pplus_PY;   //!
   TBranch        *b_B_ConstBSubFit_pplus_PZ;   //!
   TBranch        *b_B_ConstBSubFit_status;   //!
   TBranch        *b_B_FullFit_nPV;   //!
   TBranch        *b_B_FullFit_J_psi_1S_M;   //!
   TBranch        *b_B_FullFit_J_psi_1S_MERR;   //!
   TBranch        *b_B_FullFit_J_psi_1S_P;   //!
   TBranch        *b_B_FullFit_J_psi_1S_PERR;   //!
   TBranch        *b_B_FullFit_J_psi_1S_ctau;   //!
   TBranch        *b_B_FullFit_J_psi_1S_ctauErr;   //!
   TBranch        *b_B_FullFit_J_psi_1S_decayLength;   //!
   TBranch        *b_B_FullFit_J_psi_1S_decayLengthErr;   //!
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
   TBranch        *b_B_SubKpi_nPV;   //!
   TBranch        *b_B_SubKpi_M;   //!
   TBranch        *b_B_SubKpi_MERR;   //!
   TBranch        *b_B_SubKpi_P;   //!
   TBranch        *b_B_SubKpi_PERR;   //!
   TBranch        *b_B_SubKpi_PV_key;   //!
   TBranch        *b_B_SubKpi_chi2;   //!
   TBranch        *b_B_SubKpi_ctau;   //!
   TBranch        *b_B_SubKpi_ctauErr;   //!
   TBranch        *b_B_SubKpi_decayLength;   //!
   TBranch        *b_B_SubKpi_decayLengthErr;   //!
   TBranch        *b_B_SubKpi_nDOF;   //!
   TBranch        *b_B_SubKpi_nIter;   //!
   TBranch        *b_B_SubKpi_status;   //!
   TBranch        *b_B_SubpK_nPV;   //!
   TBranch        *b_B_SubpK_M;   //!
   TBranch        *b_B_SubpK_MERR;   //!
   TBranch        *b_B_SubpK_P;   //!
   TBranch        *b_B_SubpK_PERR;   //!
   TBranch        *b_B_SubpK_PV_key;   //!
   TBranch        *b_B_SubpK_chi2;   //!
   TBranch        *b_B_SubpK_ctau;   //!
   TBranch        *b_B_SubpK_ctauErr;   //!
   TBranch        *b_B_SubpK_decayLength;   //!
   TBranch        *b_B_SubpK_decayLengthErr;   //!
   TBranch        *b_B_SubpK_nDOF;   //!
   TBranch        *b_B_SubpK_nIter;   //!
   TBranch        *b_B_SubpK_status;   //!
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
   TBranch        *b_piminus_CosTheta;   //!
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
   TBranch        *b_piminus_ORIVX_X;   //!
   TBranch        *b_piminus_ORIVX_Y;   //!
   TBranch        *b_piminus_ORIVX_Z;   //!
   TBranch        *b_piminus_ORIVX_XERR;   //!
   TBranch        *b_piminus_ORIVX_YERR;   //!
   TBranch        *b_piminus_ORIVX_ZERR;   //!
   TBranch        *b_piminus_ORIVX_CHI2;   //!
   TBranch        *b_piminus_ORIVX_NDOF;   //!
   TBranch        *b_piminus_ORIVX_COV_;   //!
   TBranch        *b_piminus_P;   //!
   TBranch        *b_piminus_PT;   //!
   TBranch        *b_piminus_PE;   //!
   TBranch        *b_piminus_PX;   //!
   TBranch        *b_piminus_PY;   //!
   TBranch        *b_piminus_PZ;   //!
   TBranch        *b_piminus_M;   //!
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
   TBranch        *b_piminus_TRACK_Type;   //!
   TBranch        *b_piminus_TRACK_Key;   //!
   TBranch        *b_piminus_TRACK_CHI2NDOF;   //!
   TBranch        *b_piminus_TRACK_PCHI2;   //!
   TBranch        *b_piminus_TRACK_MatchCHI2;   //!
   TBranch        *b_piminus_TRACK_GhostProb;   //!
   TBranch        *b_piminus_TRACK_CloneDist;   //!
   TBranch        *b_piminus_TRACK_Likelihood;   //!
   TBranch        *b_pplus_CosTheta;   //!
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
   TBranch        *b_pplus_ORIVX_X;   //!
   TBranch        *b_pplus_ORIVX_Y;   //!
   TBranch        *b_pplus_ORIVX_Z;   //!
   TBranch        *b_pplus_ORIVX_XERR;   //!
   TBranch        *b_pplus_ORIVX_YERR;   //!
   TBranch        *b_pplus_ORIVX_ZERR;   //!
   TBranch        *b_pplus_ORIVX_CHI2;   //!
   TBranch        *b_pplus_ORIVX_NDOF;   //!
   TBranch        *b_pplus_ORIVX_COV_;   //!
   TBranch        *b_pplus_P;   //!
   TBranch        *b_pplus_PT;   //!
   TBranch        *b_pplus_PE;   //!
   TBranch        *b_pplus_PX;   //!
   TBranch        *b_pplus_PY;   //!
   TBranch        *b_pplus_PZ;   //!
   TBranch        *b_pplus_M;   //!
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
   TBranch        *b_pplus_TRACK_Type;   //!
   TBranch        *b_pplus_TRACK_Key;   //!
   TBranch        *b_pplus_TRACK_CHI2NDOF;   //!
   TBranch        *b_pplus_TRACK_PCHI2;   //!
   TBranch        *b_pplus_TRACK_MatchCHI2;   //!
   TBranch        *b_pplus_TRACK_GhostProb;   //!
   TBranch        *b_pplus_TRACK_CloneDist;   //!
   TBranch        *b_pplus_TRACK_Likelihood;   //!
   TBranch        *b_Psi_CosTheta;   //!
   TBranch        *b_Psi_AllIP;   //!
   TBranch        *b_Psi_AllIPchi2;   //!
   TBranch        *b_Psi_AllDIRA;   //!
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
   TBranch        *b_Psi_ORIVX_X;   //!
   TBranch        *b_Psi_ORIVX_Y;   //!
   TBranch        *b_Psi_ORIVX_Z;   //!
   TBranch        *b_Psi_ORIVX_XERR;   //!
   TBranch        *b_Psi_ORIVX_YERR;   //!
   TBranch        *b_Psi_ORIVX_ZERR;   //!
   TBranch        *b_Psi_ORIVX_CHI2;   //!
   TBranch        *b_Psi_ORIVX_NDOF;   //!
   TBranch        *b_Psi_ORIVX_COV_;   //!
   TBranch        *b_Psi_FD_ORIVX;   //!
   TBranch        *b_Psi_FDCHI2_ORIVX;   //!
   TBranch        *b_Psi_DIRA_ORIVX;   //!
   TBranch        *b_Psi_P;   //!
   TBranch        *b_Psi_PT;   //!
   TBranch        *b_Psi_PE;   //!
   TBranch        *b_Psi_PX;   //!
   TBranch        *b_Psi_PY;   //!
   TBranch        *b_Psi_PZ;   //!
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
   TBranch        *b_muminus_CosTheta;   //!
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
   TBranch        *b_muminus_ORIVX_X;   //!
   TBranch        *b_muminus_ORIVX_Y;   //!
   TBranch        *b_muminus_ORIVX_Z;   //!
   TBranch        *b_muminus_ORIVX_XERR;   //!
   TBranch        *b_muminus_ORIVX_YERR;   //!
   TBranch        *b_muminus_ORIVX_ZERR;   //!
   TBranch        *b_muminus_ORIVX_CHI2;   //!
   TBranch        *b_muminus_ORIVX_NDOF;   //!
   TBranch        *b_muminus_ORIVX_COV_;   //!
   TBranch        *b_muminus_P;   //!
   TBranch        *b_muminus_PT;   //!
   TBranch        *b_muminus_PE;   //!
   TBranch        *b_muminus_PX;   //!
   TBranch        *b_muminus_PY;   //!
   TBranch        *b_muminus_PZ;   //!
   TBranch        *b_muminus_M;   //!
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
   TBranch        *b_muminus_TRACK_Type;   //!
   TBranch        *b_muminus_TRACK_Key;   //!
   TBranch        *b_muminus_TRACK_CHI2NDOF;   //!
   TBranch        *b_muminus_TRACK_PCHI2;   //!
   TBranch        *b_muminus_TRACK_MatchCHI2;   //!
   TBranch        *b_muminus_TRACK_GhostProb;   //!
   TBranch        *b_muminus_TRACK_CloneDist;   //!
   TBranch        *b_muminus_TRACK_Likelihood;   //!
   TBranch        *b_muplus_CosTheta;   //!
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
   TBranch        *b_muplus_ORIVX_X;   //!
   TBranch        *b_muplus_ORIVX_Y;   //!
   TBranch        *b_muplus_ORIVX_Z;   //!
   TBranch        *b_muplus_ORIVX_XERR;   //!
   TBranch        *b_muplus_ORIVX_YERR;   //!
   TBranch        *b_muplus_ORIVX_ZERR;   //!
   TBranch        *b_muplus_ORIVX_CHI2;   //!
   TBranch        *b_muplus_ORIVX_NDOF;   //!
   TBranch        *b_muplus_ORIVX_COV_;   //!
   TBranch        *b_muplus_P;   //!
   TBranch        *b_muplus_PT;   //!
   TBranch        *b_muplus_PE;   //!
   TBranch        *b_muplus_PX;   //!
   TBranch        *b_muplus_PY;   //!
   TBranch        *b_muplus_PZ;   //!
   TBranch        *b_muplus_M;   //!
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
   TBranch        *b_muplus_TRACK_Type;   //!
   TBranch        *b_muplus_TRACK_Key;   //!
   TBranch        *b_muplus_TRACK_CHI2NDOF;   //!
   TBranch        *b_muplus_TRACK_PCHI2;   //!
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
   TBranch        *b_Polarity;   //!
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


   Int_t           B_BKGCAT;
   Int_t           B_TRUEID;
   Int_t           Psi_TRUEID;
   Int_t           muplus_TRUEID;
   Int_t           muminus_TRUEID;
   Int_t           pplus_TRUEID;
   Int_t           piminus_TRUEID;

   TBranch        *b_B_BKGCAT;   //!
   TBranch        *b_B_TRUEID;   //!
   TBranch*        b_Psi_TRUEID;
   TBranch*        b_muplus_TRUEID;
   TBranch*        b_muminus_TRUEID;
   TBranch*        b_pplus_TRUEID;
   TBranch*        b_piminus_TRUEID;

   Double_t       netOutput[100] ;
   Int_t          category[100] ;
   Double_t       tweightLb[100] ;
   TBranch        *b_netOutput;   //!
   TBranch        *b_category;   //!
   TBranch        *b_tweightLb;   //!

   Lambdab(TString filename, TString filename2, TString friendname, TString type);
   virtual ~Lambdab();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
  Double_t GetEntries(bool debug=false){
    if (debug) return 100000.;
    else return fChain->GetEntries();
  }
  
   bool m_isMC;
  // local
  bool firstFill ;
  std::vector<TString> m_names ; ///< names of variables
#include "Tuples.icpp"
};

#endif

#ifdef Lambdab_cxx
Lambdab::Lambdab(TString filename, TString filename2, TString friendname, TString type) : fChain(0){
  std::cout << "Lambdab with " << filename << " " << filename2 << " " << friendname << " " << type << std::endl ;
  firstFill = true ;
  m_names.reserve(nvar);
  m_names.resize(nvar, TString(max_name_length));
  fillNames(nvar);
  TFile *f = TFile::Open(filename);
  m_isMC = filename.Contains("MC");
  TString chainName ="";
  if ("ppi"==type || ""==type){
    type="ppi";
    if (m_isMC) chainName ="BetaSLambdab2JpsippiDetachedLine_TupleMC/DecayTree";
    else chainName ="BetaSLambdab2JpsippiDetachedLine_Tuple/DecayTree";
    TObject* o = f->Get(chainName);
    if (0==o) chainName = "Lambdab2Jpsippi_TupleMC/DecayTree";
    fFriend = 0 ;
  } else if ("Lambda"==type){
    if (m_isMC) chainName ="BetaSLambdab2JpsiLaymbdaUnbiasedLine_TupleMC/DecayTree";
    else chainName ="RefinedLambdas_Tuple/DecayTree";
  }
  std::cout << "Getting ``" << type << "'' line : " << chainName<< std::endl ;
  
  TChain* tree = new TChain(chainName);
  tree->Add(filename);
  if (""!=filename2){
    tree->Add(filename2);
  }
  std::cout << tree << " entries: " << tree->GetEntries() << std::endl ;

  if ( ""!=friendname){
    unsigned int lastslash = filename.Last('/');
    TString plotfilename = filename(lastslash+1,filename.Length()-lastslash-1);
    plotfilename = plotfilename.ReplaceAll(".root",TString("-"+friendname+".root")) ;
    std::cout << plotfilename << std::endl ;
    TFile *f2 = TFile::Open(plotfilename);
    if ("NN" == friendname  ) fFriend = (TChain*)f2->Get("NetTree"); // get some sweights 
    else if ("All-SW" == friendname  ) fFriend = (TChain*)f2->Get("TrainTree"); // get some sweights 
  }
  if (fFriend) TFriendElement* t = tree->AddFriend(fFriend);
  
  if (fFriend){
    /// Add variables HERE!
    if (friendname == "All-SW" ){
      tree->SetBranchAddress("tweightLb", &tweightLb, &b_tweightLb);   
    } else if ("NN" == friendname  ){
      tree->SetBranchAddress("netOutput", &netOutput, &b_netOutput);
      tree->SetBranchAddress("category", &category, &b_category);
    }
  }
  Init(tree);
  
}

Lambdab::~Lambdab()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Lambdab::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Lambdab::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Lambdab::Init(TTree *tree)
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

   if (m_isMC){
     fChain->SetBranchAddress("B_BKGCAT", &B_BKGCAT, &b_B_BKGCAT);
     fChain->SetBranchAddress("B_TRUEID",&B_TRUEID,&b_B_TRUEID);   //!
     fChain->SetBranchAddress("Psi_TRUEID",&Psi_TRUEID,&b_Psi_TRUEID);   //!
     fChain->SetBranchAddress("muplus_TRUEID",&muplus_TRUEID,&b_muplus_TRUEID);   //!
     fChain->SetBranchAddress("muminus_TRUEID",&muminus_TRUEID,&b_muminus_TRUEID);   //!
     fChain->SetBranchAddress("pplus_TRUEID",&pplus_TRUEID,&b_pplus_TRUEID);   //!
     fChain->SetBranchAddress("piminus_TRUEID",&piminus_TRUEID,&b_piminus_TRUEID);   //!
   }

   fChain->SetBranchAddress("nPV", &nPV, &b_nPV);
   //   std::cout << "nPV " << &nPV << " " << &b_nPV << std::endl ;
   fChain->SetBranchAddress("B_AllIP", B_AllIP, &b_B_AllIP);
   fChain->SetBranchAddress("B_AllIPchi2", B_AllIPchi2, &b_B_AllIPchi2);
   fChain->SetBranchAddress("B_AllDIRA", B_AllDIRA, &b_B_AllDIRA);
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
   fChain->SetBranchAddress("B_P", &B_P, &b_B_P);
   fChain->SetBranchAddress("B_PT", &B_PT, &b_B_PT);
   fChain->SetBranchAddress("B_PE", &B_PE, &b_B_PE);
   fChain->SetBranchAddress("B_PX", &B_PX, &b_B_PX);
   fChain->SetBranchAddress("B_PY", &B_PY, &b_B_PY);
   fChain->SetBranchAddress("B_PZ", &B_PZ, &b_B_PZ);
   fChain->SetBranchAddress("B_MM", &B_MM, &b_B_MM);
   fChain->SetBranchAddress("B_MMERR", &B_MMERR, &b_B_MMERR);
   fChain->SetBranchAddress("B_M", &B_M, &b_B_M);
   fChain->SetBranchAddress("B_ID", &B_ID, &b_B_ID);
   fChain->SetBranchAddress("B_TAU", &B_TAU, &b_B_TAU);
   fChain->SetBranchAddress("B_TAUERR", &B_TAUERR, &b_B_TAUERR);
   fChain->SetBranchAddress("B_TAUCHI2", &B_TAUCHI2, &b_B_TAUCHI2);
   fChain->SetBranchAddress("Dalitz_pplus_J_psi_1S_M2", &Dalitz_pplus_J_psi_1S_M2, &b_Dalitz_pplus_J_psi_1S_M2);
   fChain->SetBranchAddress("Dalitz_piminus_J_psi_1S_M2", &Dalitz_piminus_J_psi_1S_M2, &b_Dalitz_piminus_J_psi_1S_M2);
   fChain->SetBranchAddress("Dalitz_piminus_pplus_M2", &Dalitz_piminus_pplus_M2, &b_Dalitz_piminus_pplus_M2);
   fChain->SetBranchAddress("B_ConstBFit_nPV", &B_ConstBFit_nPV, &b_B_ConstBFit_nPV);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_M", B_ConstBFit_J_psi_1S_M, &b_B_ConstBFit_J_psi_1S_M);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_MERR", B_ConstBFit_J_psi_1S_MERR, &b_B_ConstBFit_J_psi_1S_MERR);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_P", B_ConstBFit_J_psi_1S_P, &b_B_ConstBFit_J_psi_1S_P);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_muminus_0_ID", B_ConstBFit_J_psi_1S_muminus_0_ID, &b_B_ConstBFit_J_psi_1S_muminus_0_ID);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_muminus_0_PE", B_ConstBFit_J_psi_1S_muminus_0_PE, &b_B_ConstBFit_J_psi_1S_muminus_0_PE);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_muminus_0_PX", B_ConstBFit_J_psi_1S_muminus_0_PX, &b_B_ConstBFit_J_psi_1S_muminus_0_PX);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_muminus_0_PY", B_ConstBFit_J_psi_1S_muminus_0_PY, &b_B_ConstBFit_J_psi_1S_muminus_0_PY);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_muminus_0_PZ", B_ConstBFit_J_psi_1S_muminus_0_PZ, &b_B_ConstBFit_J_psi_1S_muminus_0_PZ);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_muminus_ID", B_ConstBFit_J_psi_1S_muminus_ID, &b_B_ConstBFit_J_psi_1S_muminus_ID);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_muminus_PE", B_ConstBFit_J_psi_1S_muminus_PE, &b_B_ConstBFit_J_psi_1S_muminus_PE);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_muminus_PX", B_ConstBFit_J_psi_1S_muminus_PX, &b_B_ConstBFit_J_psi_1S_muminus_PX);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_muminus_PY", B_ConstBFit_J_psi_1S_muminus_PY, &b_B_ConstBFit_J_psi_1S_muminus_PY);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_muminus_PZ", B_ConstBFit_J_psi_1S_muminus_PZ, &b_B_ConstBFit_J_psi_1S_muminus_PZ);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_PERR", B_ConstBFit_J_psi_1S_PERR, &b_B_ConstBFit_J_psi_1S_PERR);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_ctau", B_ConstBFit_J_psi_1S_ctau, &b_B_ConstBFit_J_psi_1S_ctau);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_ctauErr", B_ConstBFit_J_psi_1S_ctauErr, &b_B_ConstBFit_J_psi_1S_ctauErr);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_decayLength", B_ConstBFit_J_psi_1S_decayLength, &b_B_ConstBFit_J_psi_1S_decayLength);
   fChain->SetBranchAddress("B_ConstBFit_J_psi_1S_decayLengthErr", B_ConstBFit_J_psi_1S_decayLengthErr, &b_B_ConstBFit_J_psi_1S_decayLengthErr);
   fChain->SetBranchAddress("B_ConstBFit_M", B_ConstBFit_M, &b_B_ConstBFit_M);
   fChain->SetBranchAddress("B_ConstBFit_MERR", B_ConstBFit_MERR, &b_B_ConstBFit_MERR);
   fChain->SetBranchAddress("B_ConstBFit_P", B_ConstBFit_P, &b_B_ConstBFit_P);
   fChain->SetBranchAddress("B_ConstBFit_pplus_ID", B_ConstBFit_pplus_ID, &b_B_ConstBFit_pplus_ID);
   fChain->SetBranchAddress("B_ConstBFit_pplus_PE", B_ConstBFit_pplus_PE, &b_B_ConstBFit_pplus_PE);
   fChain->SetBranchAddress("B_ConstBFit_pplus_PX", B_ConstBFit_pplus_PX, &b_B_ConstBFit_pplus_PX);
   fChain->SetBranchAddress("B_ConstBFit_pplus_PY", B_ConstBFit_pplus_PY, &b_B_ConstBFit_pplus_PY);
   fChain->SetBranchAddress("B_ConstBFit_pplus_PZ", B_ConstBFit_pplus_PZ, &b_B_ConstBFit_pplus_PZ);
   fChain->SetBranchAddress("B_ConstBFit_piplus_ID", B_ConstBFit_piplus_ID, &b_B_ConstBFit_piplus_ID);
   fChain->SetBranchAddress("B_ConstBFit_piplus_PE", B_ConstBFit_piplus_PE, &b_B_ConstBFit_piplus_PE);
   fChain->SetBranchAddress("B_ConstBFit_piplus_PX", B_ConstBFit_piplus_PX, &b_B_ConstBFit_piplus_PX);
   fChain->SetBranchAddress("B_ConstBFit_piplus_PY", B_ConstBFit_piplus_PY, &b_B_ConstBFit_piplus_PY);
   fChain->SetBranchAddress("B_ConstBFit_piplus_PZ", B_ConstBFit_piplus_PZ, &b_B_ConstBFit_piplus_PZ);
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
   fChain->SetBranchAddress("B_ConstBSubFit_nPV", &B_ConstBSubFit_nPV, &b_B_ConstBSubFit_nPV);
   fChain->SetBranchAddress("B_ConstBSubFit_J_psi_1S_M", B_ConstBSubFit_J_psi_1S_M, &b_B_ConstBSubFit_J_psi_1S_M);
   fChain->SetBranchAddress("B_ConstBSubFit_J_psi_1S_MERR", B_ConstBSubFit_J_psi_1S_MERR, &b_B_ConstBSubFit_J_psi_1S_MERR);
   fChain->SetBranchAddress("B_ConstBSubFit_J_psi_1S_P", B_ConstBSubFit_J_psi_1S_P, &b_B_ConstBSubFit_J_psi_1S_P);
   fChain->SetBranchAddress("B_ConstBSubFit_J_psi_1S_PERR", B_ConstBSubFit_J_psi_1S_PERR, &b_B_ConstBSubFit_J_psi_1S_PERR);
   fChain->SetBranchAddress("B_ConstBSubFit_J_psi_1S_ctau", B_ConstBSubFit_J_psi_1S_ctau, &b_B_ConstBSubFit_J_psi_1S_ctau);
   fChain->SetBranchAddress("B_ConstBSubFit_J_psi_1S_ctauErr", B_ConstBSubFit_J_psi_1S_ctauErr, &b_B_ConstBSubFit_J_psi_1S_ctauErr);
   fChain->SetBranchAddress("B_ConstBSubFit_J_psi_1S_decayLength", B_ConstBSubFit_J_psi_1S_decayLength, &b_B_ConstBSubFit_J_psi_1S_decayLength);
   fChain->SetBranchAddress("B_ConstBSubFit_J_psi_1S_decayLengthErr", B_ConstBSubFit_J_psi_1S_decayLengthErr, &b_B_ConstBSubFit_J_psi_1S_decayLengthErr);
   fChain->SetBranchAddress("B_ConstBSubFit_J_psi_1S_muminus_0_ID", B_ConstBSubFit_J_psi_1S_muminus_0_ID, &b_B_ConstBSubFit_J_psi_1S_muminus_0_ID);
   fChain->SetBranchAddress("B_ConstBSubFit_J_psi_1S_muminus_0_PE", B_ConstBSubFit_J_psi_1S_muminus_0_PE, &b_B_ConstBSubFit_J_psi_1S_muminus_0_PE);
   fChain->SetBranchAddress("B_ConstBSubFit_J_psi_1S_muminus_0_PX", B_ConstBSubFit_J_psi_1S_muminus_0_PX, &b_B_ConstBSubFit_J_psi_1S_muminus_0_PX);
   fChain->SetBranchAddress("B_ConstBSubFit_J_psi_1S_muminus_0_PY", B_ConstBSubFit_J_psi_1S_muminus_0_PY, &b_B_ConstBSubFit_J_psi_1S_muminus_0_PY);
   fChain->SetBranchAddress("B_ConstBSubFit_J_psi_1S_muminus_0_PZ", B_ConstBSubFit_J_psi_1S_muminus_0_PZ, &b_B_ConstBSubFit_J_psi_1S_muminus_0_PZ);
   fChain->SetBranchAddress("B_ConstBSubFit_J_psi_1S_muminus_ID", B_ConstBSubFit_J_psi_1S_muminus_ID, &b_B_ConstBSubFit_J_psi_1S_muminus_ID);
   fChain->SetBranchAddress("B_ConstBSubFit_J_psi_1S_muminus_PE", B_ConstBSubFit_J_psi_1S_muminus_PE, &b_B_ConstBSubFit_J_psi_1S_muminus_PE);
   fChain->SetBranchAddress("B_ConstBSubFit_J_psi_1S_muminus_PX", B_ConstBSubFit_J_psi_1S_muminus_PX, &b_B_ConstBSubFit_J_psi_1S_muminus_PX);
   fChain->SetBranchAddress("B_ConstBSubFit_J_psi_1S_muminus_PY", B_ConstBSubFit_J_psi_1S_muminus_PY, &b_B_ConstBSubFit_J_psi_1S_muminus_PY);
   fChain->SetBranchAddress("B_ConstBSubFit_J_psi_1S_muminus_PZ", B_ConstBSubFit_J_psi_1S_muminus_PZ, &b_B_ConstBSubFit_J_psi_1S_muminus_PZ);
   fChain->SetBranchAddress("B_ConstBSubFit_Kplus_ID", B_ConstBSubFit_Kplus_ID, &b_B_ConstBSubFit_Kplus_ID);
   fChain->SetBranchAddress("B_ConstBSubFit_Kplus_PE", B_ConstBSubFit_Kplus_PE, &b_B_ConstBSubFit_Kplus_PE);
   fChain->SetBranchAddress("B_ConstBSubFit_Kplus_PX", B_ConstBSubFit_Kplus_PX, &b_B_ConstBSubFit_Kplus_PX);
   fChain->SetBranchAddress("B_ConstBSubFit_Kplus_PY", B_ConstBSubFit_Kplus_PY, &b_B_ConstBSubFit_Kplus_PY);
   fChain->SetBranchAddress("B_ConstBSubFit_Kplus_PZ", B_ConstBSubFit_Kplus_PZ, &b_B_ConstBSubFit_Kplus_PZ);
   fChain->SetBranchAddress("B_ConstBSubFit_M", B_ConstBSubFit_M, &b_B_ConstBSubFit_M);
   fChain->SetBranchAddress("B_ConstBSubFit_MERR", B_ConstBSubFit_MERR, &b_B_ConstBSubFit_MERR);
   fChain->SetBranchAddress("B_ConstBSubFit_P", B_ConstBSubFit_P, &b_B_ConstBSubFit_P);
   fChain->SetBranchAddress("B_ConstBSubFit_PERR", B_ConstBSubFit_PERR, &b_B_ConstBSubFit_PERR);
   fChain->SetBranchAddress("B_ConstBSubFit_PV_X", B_ConstBSubFit_PV_X, &b_B_ConstBSubFit_PV_X);
   fChain->SetBranchAddress("B_ConstBSubFit_PV_Y", B_ConstBSubFit_PV_Y, &b_B_ConstBSubFit_PV_Y);
   fChain->SetBranchAddress("B_ConstBSubFit_PV_Z", B_ConstBSubFit_PV_Z, &b_B_ConstBSubFit_PV_Z);
   fChain->SetBranchAddress("B_ConstBSubFit_PV_key", B_ConstBSubFit_PV_key, &b_B_ConstBSubFit_PV_key);
   fChain->SetBranchAddress("B_ConstBSubFit_chi2", B_ConstBSubFit_chi2, &b_B_ConstBSubFit_chi2);
   fChain->SetBranchAddress("B_ConstBSubFit_ctau", B_ConstBSubFit_ctau, &b_B_ConstBSubFit_ctau);
   fChain->SetBranchAddress("B_ConstBSubFit_ctauErr", B_ConstBSubFit_ctauErr, &b_B_ConstBSubFit_ctauErr);
   fChain->SetBranchAddress("B_ConstBSubFit_decayLength", B_ConstBSubFit_decayLength, &b_B_ConstBSubFit_decayLength);
   fChain->SetBranchAddress("B_ConstBSubFit_decayLengthErr", B_ConstBSubFit_decayLengthErr, &b_B_ConstBSubFit_decayLengthErr);
   fChain->SetBranchAddress("B_ConstBSubFit_nDOF", B_ConstBSubFit_nDOF, &b_B_ConstBSubFit_nDOF);
   fChain->SetBranchAddress("B_ConstBSubFit_nIter", B_ConstBSubFit_nIter, &b_B_ConstBSubFit_nIter);
   fChain->SetBranchAddress("B_ConstBSubFit_pplus_ID", B_ConstBSubFit_pplus_ID, &b_B_ConstBSubFit_pplus_ID);
   fChain->SetBranchAddress("B_ConstBSubFit_pplus_PE", B_ConstBSubFit_pplus_PE, &b_B_ConstBSubFit_pplus_PE);
   fChain->SetBranchAddress("B_ConstBSubFit_pplus_PX", B_ConstBSubFit_pplus_PX, &b_B_ConstBSubFit_pplus_PX);
   fChain->SetBranchAddress("B_ConstBSubFit_pplus_PY", B_ConstBSubFit_pplus_PY, &b_B_ConstBSubFit_pplus_PY);
   fChain->SetBranchAddress("B_ConstBSubFit_pplus_PZ", B_ConstBSubFit_pplus_PZ, &b_B_ConstBSubFit_pplus_PZ);
   fChain->SetBranchAddress("B_ConstBSubFit_status", B_ConstBSubFit_status, &b_B_ConstBSubFit_status);
   fChain->SetBranchAddress("B_FullFit_nPV", &B_FullFit_nPV, &b_B_FullFit_nPV);
   fChain->SetBranchAddress("B_FullFit_J_psi_1S_M", B_FullFit_J_psi_1S_M, &b_B_FullFit_J_psi_1S_M);
   fChain->SetBranchAddress("B_FullFit_J_psi_1S_MERR", B_FullFit_J_psi_1S_MERR, &b_B_FullFit_J_psi_1S_MERR);
   fChain->SetBranchAddress("B_FullFit_J_psi_1S_P", B_FullFit_J_psi_1S_P, &b_B_FullFit_J_psi_1S_P);
   fChain->SetBranchAddress("B_FullFit_J_psi_1S_PERR", B_FullFit_J_psi_1S_PERR, &b_B_FullFit_J_psi_1S_PERR);
   fChain->SetBranchAddress("B_FullFit_J_psi_1S_ctau", B_FullFit_J_psi_1S_ctau, &b_B_FullFit_J_psi_1S_ctau);
   fChain->SetBranchAddress("B_FullFit_J_psi_1S_ctauErr", B_FullFit_J_psi_1S_ctauErr, &b_B_FullFit_J_psi_1S_ctauErr);
   fChain->SetBranchAddress("B_FullFit_J_psi_1S_decayLength", B_FullFit_J_psi_1S_decayLength, &b_B_FullFit_J_psi_1S_decayLength);
   fChain->SetBranchAddress("B_FullFit_J_psi_1S_decayLengthErr", B_FullFit_J_psi_1S_decayLengthErr, &b_B_FullFit_J_psi_1S_decayLengthErr);
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
   fChain->SetBranchAddress("B_SubKpi_nPV", &B_SubKpi_nPV, &b_B_SubKpi_nPV);
   fChain->SetBranchAddress("B_SubKpi_M", B_SubKpi_M, &b_B_SubKpi_M);
   fChain->SetBranchAddress("B_SubKpi_MERR", B_SubKpi_MERR, &b_B_SubKpi_MERR);
   fChain->SetBranchAddress("B_SubKpi_P", B_SubKpi_P, &b_B_SubKpi_P);
   fChain->SetBranchAddress("B_SubKpi_PERR", B_SubKpi_PERR, &b_B_SubKpi_PERR);
   fChain->SetBranchAddress("B_SubKpi_PV_key", B_SubKpi_PV_key, &b_B_SubKpi_PV_key);
   fChain->SetBranchAddress("B_SubKpi_chi2", B_SubKpi_chi2, &b_B_SubKpi_chi2);
   fChain->SetBranchAddress("B_SubKpi_ctau", B_SubKpi_ctau, &b_B_SubKpi_ctau);
   fChain->SetBranchAddress("B_SubKpi_ctauErr", B_SubKpi_ctauErr, &b_B_SubKpi_ctauErr);
   fChain->SetBranchAddress("B_SubKpi_decayLength", B_SubKpi_decayLength, &b_B_SubKpi_decayLength);
   fChain->SetBranchAddress("B_SubKpi_decayLengthErr", B_SubKpi_decayLengthErr, &b_B_SubKpi_decayLengthErr);
   fChain->SetBranchAddress("B_SubKpi_nDOF", B_SubKpi_nDOF, &b_B_SubKpi_nDOF);
   fChain->SetBranchAddress("B_SubKpi_nIter", B_SubKpi_nIter, &b_B_SubKpi_nIter);
   fChain->SetBranchAddress("B_SubKpi_status", B_SubKpi_status, &b_B_SubKpi_status);
   fChain->SetBranchAddress("B_SubpK_nPV", &B_SubpK_nPV, &b_B_SubpK_nPV);
   fChain->SetBranchAddress("B_SubpK_M", B_SubpK_M, &b_B_SubpK_M);
   fChain->SetBranchAddress("B_SubpK_MERR", B_SubpK_MERR, &b_B_SubpK_MERR);
   fChain->SetBranchAddress("B_SubpK_P", B_SubpK_P, &b_B_SubpK_P);
   fChain->SetBranchAddress("B_SubpK_PERR", B_SubpK_PERR, &b_B_SubpK_PERR);
   fChain->SetBranchAddress("B_SubpK_PV_key", B_SubpK_PV_key, &b_B_SubpK_PV_key);
   fChain->SetBranchAddress("B_SubpK_chi2", B_SubpK_chi2, &b_B_SubpK_chi2);
   fChain->SetBranchAddress("B_SubpK_ctau", B_SubpK_ctau, &b_B_SubpK_ctau);
   fChain->SetBranchAddress("B_SubpK_ctauErr", B_SubpK_ctauErr, &b_B_SubpK_ctauErr);
   fChain->SetBranchAddress("B_SubpK_decayLength", B_SubpK_decayLength, &b_B_SubpK_decayLength);
   fChain->SetBranchAddress("B_SubpK_decayLengthErr", B_SubpK_decayLengthErr, &b_B_SubpK_decayLengthErr);
   fChain->SetBranchAddress("B_SubpK_nDOF", B_SubpK_nDOF, &b_B_SubpK_nDOF);
   fChain->SetBranchAddress("B_SubpK_nIter", B_SubpK_nIter, &b_B_SubpK_nIter);
   fChain->SetBranchAddress("B_SubpK_status", B_SubpK_status, &b_B_SubpK_status);
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
   fChain->SetBranchAddress("piminus_CosTheta", &piminus_CosTheta, &b_piminus_CosTheta);
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
   fChain->SetBranchAddress("piminus_ORIVX_X", &piminus_ORIVX_X, &b_piminus_ORIVX_X);
   fChain->SetBranchAddress("piminus_ORIVX_Y", &piminus_ORIVX_Y, &b_piminus_ORIVX_Y);
   fChain->SetBranchAddress("piminus_ORIVX_Z", &piminus_ORIVX_Z, &b_piminus_ORIVX_Z);
   fChain->SetBranchAddress("piminus_ORIVX_XERR", &piminus_ORIVX_XERR, &b_piminus_ORIVX_XERR);
   fChain->SetBranchAddress("piminus_ORIVX_YERR", &piminus_ORIVX_YERR, &b_piminus_ORIVX_YERR);
   fChain->SetBranchAddress("piminus_ORIVX_ZERR", &piminus_ORIVX_ZERR, &b_piminus_ORIVX_ZERR);
   fChain->SetBranchAddress("piminus_ORIVX_CHI2", &piminus_ORIVX_CHI2, &b_piminus_ORIVX_CHI2);
   fChain->SetBranchAddress("piminus_ORIVX_NDOF", &piminus_ORIVX_NDOF, &b_piminus_ORIVX_NDOF);
   fChain->SetBranchAddress("piminus_ORIVX_COV_", piminus_ORIVX_COV_, &b_piminus_ORIVX_COV_);
   fChain->SetBranchAddress("piminus_P", &piminus_P, &b_piminus_P);
   fChain->SetBranchAddress("piminus_PT", &piminus_PT, &b_piminus_PT);
   fChain->SetBranchAddress("piminus_PE", &piminus_PE, &b_piminus_PE);
   fChain->SetBranchAddress("piminus_PX", &piminus_PX, &b_piminus_PX);
   fChain->SetBranchAddress("piminus_PY", &piminus_PY, &b_piminus_PY);
   fChain->SetBranchAddress("piminus_PZ", &piminus_PZ, &b_piminus_PZ);
   fChain->SetBranchAddress("piminus_M", &piminus_M, &b_piminus_M);
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
   fChain->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type, &b_piminus_TRACK_Type);
   fChain->SetBranchAddress("piminus_TRACK_Key", &piminus_TRACK_Key, &b_piminus_TRACK_Key);
   fChain->SetBranchAddress("piminus_TRACK_CHI2NDOF", &piminus_TRACK_CHI2NDOF, &b_piminus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("piminus_TRACK_PCHI2", &piminus_TRACK_PCHI2, &b_piminus_TRACK_PCHI2);
   fChain->SetBranchAddress("piminus_TRACK_MatchCHI2", &piminus_TRACK_MatchCHI2, &b_piminus_TRACK_MatchCHI2);
   fChain->SetBranchAddress("piminus_TRACK_GhostProb", &piminus_TRACK_GhostProb, &b_piminus_TRACK_GhostProb);
   fChain->SetBranchAddress("piminus_TRACK_CloneDist", &piminus_TRACK_CloneDist, &b_piminus_TRACK_CloneDist);
   fChain->SetBranchAddress("piminus_TRACK_Likelihood", &piminus_TRACK_Likelihood, &b_piminus_TRACK_Likelihood);
   fChain->SetBranchAddress("pplus_CosTheta", &pplus_CosTheta, &b_pplus_CosTheta);
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
   fChain->SetBranchAddress("pplus_ORIVX_X", &pplus_ORIVX_X, &b_pplus_ORIVX_X);
   fChain->SetBranchAddress("pplus_ORIVX_Y", &pplus_ORIVX_Y, &b_pplus_ORIVX_Y);
   fChain->SetBranchAddress("pplus_ORIVX_Z", &pplus_ORIVX_Z, &b_pplus_ORIVX_Z);
   fChain->SetBranchAddress("pplus_ORIVX_XERR", &pplus_ORIVX_XERR, &b_pplus_ORIVX_XERR);
   fChain->SetBranchAddress("pplus_ORIVX_YERR", &pplus_ORIVX_YERR, &b_pplus_ORIVX_YERR);
   fChain->SetBranchAddress("pplus_ORIVX_ZERR", &pplus_ORIVX_ZERR, &b_pplus_ORIVX_ZERR);
   fChain->SetBranchAddress("pplus_ORIVX_CHI2", &pplus_ORIVX_CHI2, &b_pplus_ORIVX_CHI2);
   fChain->SetBranchAddress("pplus_ORIVX_NDOF", &pplus_ORIVX_NDOF, &b_pplus_ORIVX_NDOF);
   fChain->SetBranchAddress("pplus_ORIVX_COV_", pplus_ORIVX_COV_, &b_pplus_ORIVX_COV_);
   fChain->SetBranchAddress("pplus_P", &pplus_P, &b_pplus_P);
   fChain->SetBranchAddress("pplus_PT", &pplus_PT, &b_pplus_PT);
   fChain->SetBranchAddress("pplus_PE", &pplus_PE, &b_pplus_PE);
   fChain->SetBranchAddress("pplus_PX", &pplus_PX, &b_pplus_PX);
   fChain->SetBranchAddress("pplus_PY", &pplus_PY, &b_pplus_PY);
   fChain->SetBranchAddress("pplus_PZ", &pplus_PZ, &b_pplus_PZ);
   fChain->SetBranchAddress("pplus_M", &pplus_M, &b_pplus_M);
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
   fChain->SetBranchAddress("pplus_TRACK_Type", &pplus_TRACK_Type, &b_pplus_TRACK_Type);
   fChain->SetBranchAddress("pplus_TRACK_Key", &pplus_TRACK_Key, &b_pplus_TRACK_Key);
   fChain->SetBranchAddress("pplus_TRACK_CHI2NDOF", &pplus_TRACK_CHI2NDOF, &b_pplus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("pplus_TRACK_PCHI2", &pplus_TRACK_PCHI2, &b_pplus_TRACK_PCHI2);
   fChain->SetBranchAddress("pplus_TRACK_MatchCHI2", &pplus_TRACK_MatchCHI2, &b_pplus_TRACK_MatchCHI2);
   fChain->SetBranchAddress("pplus_TRACK_GhostProb", &pplus_TRACK_GhostProb, &b_pplus_TRACK_GhostProb);
   fChain->SetBranchAddress("pplus_TRACK_CloneDist", &pplus_TRACK_CloneDist, &b_pplus_TRACK_CloneDist);
   fChain->SetBranchAddress("pplus_TRACK_Likelihood", &pplus_TRACK_Likelihood, &b_pplus_TRACK_Likelihood);
   fChain->SetBranchAddress("Psi_CosTheta", &Psi_CosTheta, &b_Psi_CosTheta);
   fChain->SetBranchAddress("Psi_AllIP", Psi_AllIP, &b_Psi_AllIP);
   fChain->SetBranchAddress("Psi_AllIPchi2", Psi_AllIPchi2, &b_Psi_AllIPchi2);
   fChain->SetBranchAddress("Psi_AllDIRA", Psi_AllDIRA, &b_Psi_AllDIRA);
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
   fChain->SetBranchAddress("Psi_ORIVX_X", &Psi_ORIVX_X, &b_Psi_ORIVX_X);
   fChain->SetBranchAddress("Psi_ORIVX_Y", &Psi_ORIVX_Y, &b_Psi_ORIVX_Y);
   fChain->SetBranchAddress("Psi_ORIVX_Z", &Psi_ORIVX_Z, &b_Psi_ORIVX_Z);
   fChain->SetBranchAddress("Psi_ORIVX_XERR", &Psi_ORIVX_XERR, &b_Psi_ORIVX_XERR);
   fChain->SetBranchAddress("Psi_ORIVX_YERR", &Psi_ORIVX_YERR, &b_Psi_ORIVX_YERR);
   fChain->SetBranchAddress("Psi_ORIVX_ZERR", &Psi_ORIVX_ZERR, &b_Psi_ORIVX_ZERR);
   fChain->SetBranchAddress("Psi_ORIVX_CHI2", &Psi_ORIVX_CHI2, &b_Psi_ORIVX_CHI2);
   fChain->SetBranchAddress("Psi_ORIVX_NDOF", &Psi_ORIVX_NDOF, &b_Psi_ORIVX_NDOF);
   fChain->SetBranchAddress("Psi_ORIVX_COV_", Psi_ORIVX_COV_, &b_Psi_ORIVX_COV_);
   fChain->SetBranchAddress("Psi_FD_ORIVX", &Psi_FD_ORIVX, &b_Psi_FD_ORIVX);
   fChain->SetBranchAddress("Psi_FDCHI2_ORIVX", &Psi_FDCHI2_ORIVX, &b_Psi_FDCHI2_ORIVX);
   fChain->SetBranchAddress("Psi_DIRA_ORIVX", &Psi_DIRA_ORIVX, &b_Psi_DIRA_ORIVX);
   fChain->SetBranchAddress("Psi_P", &Psi_P, &b_Psi_P);
   fChain->SetBranchAddress("Psi_PT", &Psi_PT, &b_Psi_PT);
   fChain->SetBranchAddress("Psi_PE", &Psi_PE, &b_Psi_PE);
   fChain->SetBranchAddress("Psi_PX", &Psi_PX, &b_Psi_PX);
   fChain->SetBranchAddress("Psi_PY", &Psi_PY, &b_Psi_PY);
   fChain->SetBranchAddress("Psi_PZ", &Psi_PZ, &b_Psi_PZ);
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
   fChain->SetBranchAddress("Psi_Hlt1Global_Dec", &Psi_Hlt1Global_Dec, &b_Psi_Hlt1Global_Dec);
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
   fChain->SetBranchAddress("muminus_CosTheta", &muminus_CosTheta, &b_muminus_CosTheta);
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
   fChain->SetBranchAddress("muminus_ORIVX_X", &muminus_ORIVX_X, &b_muminus_ORIVX_X);
   fChain->SetBranchAddress("muminus_ORIVX_Y", &muminus_ORIVX_Y, &b_muminus_ORIVX_Y);
   fChain->SetBranchAddress("muminus_ORIVX_Z", &muminus_ORIVX_Z, &b_muminus_ORIVX_Z);
   fChain->SetBranchAddress("muminus_ORIVX_XERR", &muminus_ORIVX_XERR, &b_muminus_ORIVX_XERR);
   fChain->SetBranchAddress("muminus_ORIVX_YERR", &muminus_ORIVX_YERR, &b_muminus_ORIVX_YERR);
   fChain->SetBranchAddress("muminus_ORIVX_ZERR", &muminus_ORIVX_ZERR, &b_muminus_ORIVX_ZERR);
   fChain->SetBranchAddress("muminus_ORIVX_CHI2", &muminus_ORIVX_CHI2, &b_muminus_ORIVX_CHI2);
   fChain->SetBranchAddress("muminus_ORIVX_NDOF", &muminus_ORIVX_NDOF, &b_muminus_ORIVX_NDOF);
   fChain->SetBranchAddress("muminus_ORIVX_COV_", muminus_ORIVX_COV_, &b_muminus_ORIVX_COV_);
   fChain->SetBranchAddress("muminus_P", &muminus_P, &b_muminus_P);
   fChain->SetBranchAddress("muminus_PT", &muminus_PT, &b_muminus_PT);
   fChain->SetBranchAddress("muminus_PE", &muminus_PE, &b_muminus_PE);
   fChain->SetBranchAddress("muminus_PX", &muminus_PX, &b_muminus_PX);
   fChain->SetBranchAddress("muminus_PY", &muminus_PY, &b_muminus_PY);
   fChain->SetBranchAddress("muminus_PZ", &muminus_PZ, &b_muminus_PZ);
   fChain->SetBranchAddress("muminus_M", &muminus_M, &b_muminus_M);
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
   fChain->SetBranchAddress("muminus_TRACK_Type", &muminus_TRACK_Type, &b_muminus_TRACK_Type);
   fChain->SetBranchAddress("muminus_TRACK_Key", &muminus_TRACK_Key, &b_muminus_TRACK_Key);
   fChain->SetBranchAddress("muminus_TRACK_CHI2NDOF", &muminus_TRACK_CHI2NDOF, &b_muminus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("muminus_TRACK_PCHI2", &muminus_TRACK_PCHI2, &b_muminus_TRACK_PCHI2);
   fChain->SetBranchAddress("muminus_TRACK_MatchCHI2", &muminus_TRACK_MatchCHI2, &b_muminus_TRACK_MatchCHI2);
   fChain->SetBranchAddress("muminus_TRACK_GhostProb", &muminus_TRACK_GhostProb, &b_muminus_TRACK_GhostProb);
   fChain->SetBranchAddress("muminus_TRACK_CloneDist", &muminus_TRACK_CloneDist, &b_muminus_TRACK_CloneDist);
   fChain->SetBranchAddress("muminus_TRACK_Likelihood", &muminus_TRACK_Likelihood, &b_muminus_TRACK_Likelihood);
   fChain->SetBranchAddress("muplus_CosTheta", &muplus_CosTheta, &b_muplus_CosTheta);
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
   fChain->SetBranchAddress("muplus_ORIVX_X", &muplus_ORIVX_X, &b_muplus_ORIVX_X);
   fChain->SetBranchAddress("muplus_ORIVX_Y", &muplus_ORIVX_Y, &b_muplus_ORIVX_Y);
   fChain->SetBranchAddress("muplus_ORIVX_Z", &muplus_ORIVX_Z, &b_muplus_ORIVX_Z);
   fChain->SetBranchAddress("muplus_ORIVX_XERR", &muplus_ORIVX_XERR, &b_muplus_ORIVX_XERR);
   fChain->SetBranchAddress("muplus_ORIVX_YERR", &muplus_ORIVX_YERR, &b_muplus_ORIVX_YERR);
   fChain->SetBranchAddress("muplus_ORIVX_ZERR", &muplus_ORIVX_ZERR, &b_muplus_ORIVX_ZERR);
   fChain->SetBranchAddress("muplus_ORIVX_CHI2", &muplus_ORIVX_CHI2, &b_muplus_ORIVX_CHI2);
   fChain->SetBranchAddress("muplus_ORIVX_NDOF", &muplus_ORIVX_NDOF, &b_muplus_ORIVX_NDOF);
   fChain->SetBranchAddress("muplus_ORIVX_COV_", muplus_ORIVX_COV_, &b_muplus_ORIVX_COV_);
   fChain->SetBranchAddress("muplus_P", &muplus_P, &b_muplus_P);
   fChain->SetBranchAddress("muplus_PT", &muplus_PT, &b_muplus_PT);
   fChain->SetBranchAddress("muplus_PE", &muplus_PE, &b_muplus_PE);
   fChain->SetBranchAddress("muplus_PX", &muplus_PX, &b_muplus_PX);
   fChain->SetBranchAddress("muplus_PY", &muplus_PY, &b_muplus_PY);
   fChain->SetBranchAddress("muplus_PZ", &muplus_PZ, &b_muplus_PZ);
   fChain->SetBranchAddress("muplus_M", &muplus_M, &b_muplus_M);
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
   fChain->SetBranchAddress("muplus_TRACK_Type", &muplus_TRACK_Type, &b_muplus_TRACK_Type);
   fChain->SetBranchAddress("muplus_TRACK_Key", &muplus_TRACK_Key, &b_muplus_TRACK_Key);
   fChain->SetBranchAddress("muplus_TRACK_CHI2NDOF", &muplus_TRACK_CHI2NDOF, &b_muplus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("muplus_TRACK_PCHI2", &muplus_TRACK_PCHI2, &b_muplus_TRACK_PCHI2);
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
   fChain->SetBranchAddress("Polarity", &Polarity, &b_Polarity);
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
   Notify();
}

Bool_t Lambdab::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Lambdab::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Lambdab::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Lambdab_cxx
