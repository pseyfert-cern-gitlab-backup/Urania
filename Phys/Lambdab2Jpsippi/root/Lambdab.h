//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jul 13 15:48:46 2012 by ROOT version 5.34/00
// from TTree DecayTree/DecayTree
// found on file: castor:///castor/cern.ch/user/p/pkoppenb/Lambdab/Lambdab2Jpsippi-MC11a-IncPsi-501.root
//////////////////////////////////////////////////////////

#ifndef Lambdab_h
#define Lambdab_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.
const Int_t kMaxB_ENDVERTEX_COV = 1;
const Int_t kMaxB_OWNPV_COV = 1;
const Int_t kMaxB_TOPPV_COV = 1;
const Int_t kMaxpiminus_OWNPV_COV = 1;
const Int_t kMaxpiminus_TOPPV_COV = 1;
const Int_t kMaxpiminus_ORIVX_COV = 1;
const Int_t kMaxpplus_OWNPV_COV = 1;
const Int_t kMaxpplus_TOPPV_COV = 1;
const Int_t kMaxpplus_ORIVX_COV = 1;
const Int_t kMaxPsi_ENDVERTEX_COV = 1;
const Int_t kMaxPsi_OWNPV_COV = 1;
const Int_t kMaxPsi_TOPPV_COV = 1;
const Int_t kMaxPsi_ORIVX_COV = 1;
const Int_t kMaxmuminus_OWNPV_COV = 1;
const Int_t kMaxmuminus_TOPPV_COV = 1;
const Int_t kMaxmuminus_ORIVX_COV = 1;
const Int_t kMaxmuplus_OWNPV_COV = 1;
const Int_t kMaxmuplus_TOPPV_COV = 1;
const Int_t kMaxmuplus_ORIVX_COV = 1;

class Lambdab {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        B_MINIP;
   Double_t        B_MINIPCHI2;
   Double_t        B_MINIPNEXTBEST;
   Double_t        B_MINIPCHI2NEXTBEST;
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
   Int_t           B_BKGCAT;
   Int_t           B_TRUEID;
   Int_t           B_MC_MOTHER_ID;
   Int_t           B_MC_MOTHER_KEY;
   Int_t           B_MC_GD_MOTHER_ID;
   Int_t           B_MC_GD_MOTHER_KEY;
   Int_t           B_MC_GD_GD_MOTHER_ID;
   Int_t           B_MC_GD_GD_MOTHER_KEY;
   Double_t        B_TRUEP_E;
   Double_t        B_TRUEP_X;
   Double_t        B_TRUEP_Y;
   Double_t        B_TRUEP_Z;
   Double_t        B_TRUEPT;
   Double_t        B_TRUEORIGINVERTEX_X;
   Double_t        B_TRUEORIGINVERTEX_Y;
   Double_t        B_TRUEORIGINVERTEX_Z;
   Double_t        B_TRUEENDVERTEX_X;
   Double_t        B_TRUEENDVERTEX_Y;
   Double_t        B_TRUEENDVERTEX_Z;
   Bool_t          B_TRUEISSTABLE;
   Double_t        B_TRUETAU;
   Bool_t          B_OSCIL;
   Int_t           B_ID;
   Double_t        B_TAU;
   Double_t        B_TAUERR;
   Double_t        B_TAUCHI2;
   Int_t           B_FullFit_nPV;
   Float_t         B_FullFit_J_psi_1S_M[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_MERR[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_P[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_PERR[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_ctau[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_ctauErr[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_decayLength[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_J_psi_1S_decayLengthErr[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_M[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_MERR[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_P[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_PERR[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_PV_X[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_PV_Y[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_PV_Z[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_PV_key[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_chi2_B[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_chi2[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_ctau[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_ctauErr[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_decayLength[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_decayLengthErr[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_nDOF[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_nIter[10];   //[B_FullFit_nPV]
   Float_t         B_FullFit_status[10];   //[B_FullFit_nPV]
   Int_t           B_MassFit_nPV;
   Float_t         B_MassFit_J_psi_1S_M[10];   //[B_MassFit_nPV]
   Float_t         B_MassFit_J_psi_1S_MERR[10];   //[B_MassFit_nPV]
   Float_t         B_MassFit_J_psi_1S_P[10];   //[B_MassFit_nPV]
   Float_t         B_MassFit_J_psi_1S_PERR[10];   //[B_MassFit_nPV]
   Float_t         B_MassFit_J_psi_1S_ctau[10];   //[B_MassFit_nPV]
   Float_t         B_MassFit_J_psi_1S_ctauErr[10];   //[B_MassFit_nPV]
   Float_t         B_MassFit_J_psi_1S_decayLength[10];   //[B_MassFit_nPV]
   Float_t         B_MassFit_J_psi_1S_decayLengthErr[10];   //[B_MassFit_nPV]
   Float_t         B_MassFit_M[10];   //[B_MassFit_nPV]
   Float_t         B_MassFit_MERR[10];   //[B_MassFit_nPV]
   Float_t         B_MassFit_P[10];   //[B_MassFit_nPV]
   Float_t         B_MassFit_PERR[10];   //[B_MassFit_nPV]
   Float_t         B_MassFit_chi2_B[10];   //[B_MassFit_nPV]
   Float_t         B_MassFit_nDOF[10];   //[B_MassFit_nPV]
   Float_t         B_MassFit_nIter[10];   //[B_MassFit_nPV]
   Float_t         B_MassFit_status[10];   //[B_MassFit_nPV]
   Int_t           B_SubKpi_nPV;
   Float_t         B_SubKpi_J_psi_1S_M[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_J_psi_1S_MERR[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_J_psi_1S_P[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_J_psi_1S_PERR[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_J_psi_1S_ctau[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_J_psi_1S_ctauErr[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_J_psi_1S_decayLength[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_J_psi_1S_decayLengthErr[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_M[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_MERR[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_P[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_PERR[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_PV_X[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_PV_Y[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_PV_Z[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_PV_key[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_chi2_B[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_ctau[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_ctauErr[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_decayLength[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_decayLengthErr[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_nDOF[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_nIter[10];   //[B_SubKpi_nPV]
   Float_t         B_SubKpi_status[10];   //[B_SubKpi_nPV]
   Int_t           B_SubpK_nPV;
   Float_t         B_SubpK_J_psi_1S_M[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_J_psi_1S_MERR[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_J_psi_1S_P[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_J_psi_1S_PERR[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_J_psi_1S_ctau[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_J_psi_1S_ctauErr[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_J_psi_1S_decayLength[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_J_psi_1S_decayLengthErr[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_M[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_MERR[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_P[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_PERR[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_PV_X[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_PV_Y[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_PV_Z[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_PV_key[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_chi2_B[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_ctau[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_ctauErr[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_decayLength[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_decayLengthErr[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_nDOF[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_nIter[10];   //[B_SubpK_nPV]
   Float_t         B_SubpK_status[10];   //[B_SubpK_nPV]
   Bool_t          BL0Global_Dec;
   Bool_t          BL0Global_TIS;
   Bool_t          BL0Global_TOS;
   Bool_t          BHlt1Global_Dec;
   Bool_t          BHlt1Global_TIS;
   Bool_t          BHlt1Global_TOS;
   Bool_t          BHlt1Phys_Dec;
   Bool_t          BHlt1Phys_TIS;
   Bool_t          BHlt1Phys_TOS;
   Bool_t          BHlt2Global_Dec;
   Bool_t          BHlt2Global_TIS;
   Bool_t          BHlt2Global_TOS;
   Bool_t          BHlt2Phys_Dec;
   Bool_t          BHlt2Phys_TIS;
   Bool_t          BHlt2Phys_TOS;
   Bool_t          BStrippingGlobal_Dec;
   Bool_t          BStrippingGlobal_TIS;
   Bool_t          BStrippingGlobal_TOS;
   Bool_t          BL0HadronDecision_Dec;
   Bool_t          BL0HadronDecision_TIS;
   Bool_t          BL0HadronDecision_TOS;
   Bool_t          BL0MuonDecision_Dec;
   Bool_t          BL0MuonDecision_TIS;
   Bool_t          BL0MuonDecision_TOS;
   Bool_t          BL0DiMuonDecision_Dec;
   Bool_t          BL0DiMuonDecision_TIS;
   Bool_t          BL0DiMuonDecision_TOS;
   Bool_t          BL0ElectronDecision_Dec;
   Bool_t          BL0ElectronDecision_TIS;
   Bool_t          BL0ElectronDecision_TOS;
   Bool_t          BL0PhotonDecision_Dec;
   Bool_t          BL0PhotonDecision_TIS;
   Bool_t          BL0PhotonDecision_TOS;
   Bool_t          BHlt1TrackAllL0Decision_Dec;
   Bool_t          BHlt1TrackAllL0Decision_TIS;
   Bool_t          BHlt1TrackAllL0Decision_TOS;
   Bool_t          BHlt1DiMuonHighMassDecision_Dec;
   Bool_t          BHlt1DiMuonHighMassDecision_TIS;
   Bool_t          BHlt1DiMuonHighMassDecision_TOS;
   Bool_t          BHlt1DiMuonLowMassDecision_Dec;
   Bool_t          BHlt1DiMuonLowMassDecision_TIS;
   Bool_t          BHlt1DiMuonLowMassDecision_TOS;
   Bool_t          BHlt1SingleMuonNoIPDecision_Dec;
   Bool_t          BHlt1SingleMuonNoIPDecision_TIS;
   Bool_t          BHlt1SingleMuonNoIPDecision_TOS;
   Bool_t          BHlt1SingleMuonHighPTDecision_Dec;
   Bool_t          BHlt1SingleMuonHighPTDecision_TIS;
   Bool_t          BHlt1SingleMuonHighPTDecision_TOS;
   Bool_t          BHlt1TrackMuonDecision_Dec;
   Bool_t          BHlt1TrackMuonDecision_TIS;
   Bool_t          BHlt1TrackMuonDecision_TOS;
   Bool_t          BHlt2TransparentDecision_Dec;
   Bool_t          BHlt2TransparentDecision_TIS;
   Bool_t          BHlt2TransparentDecision_TOS;
   Bool_t          BHlt2Topo2BodySimpleDecision_Dec;
   Bool_t          BHlt2Topo2BodySimpleDecision_TIS;
   Bool_t          BHlt2Topo2BodySimpleDecision_TOS;
   Bool_t          BHlt2Topo3BodySimpleDecision_Dec;
   Bool_t          BHlt2Topo3BodySimpleDecision_TIS;
   Bool_t          BHlt2Topo3BodySimpleDecision_TOS;
   Bool_t          BHlt2Topo4BodySimpleDecision_Dec;
   Bool_t          BHlt2Topo4BodySimpleDecision_TIS;
   Bool_t          BHlt2Topo4BodySimpleDecision_TOS;
   Bool_t          BHlt2Topo2BodyBBDTDecision_Dec;
   Bool_t          BHlt2Topo2BodyBBDTDecision_TIS;
   Bool_t          BHlt2Topo2BodyBBDTDecision_TOS;
   Bool_t          BHlt2Topo3BodyBBDTDecision_Dec;
   Bool_t          BHlt2Topo3BodyBBDTDecision_TIS;
   Bool_t          BHlt2Topo3BodyBBDTDecision_TOS;
   Bool_t          BHlt2Topo4BodyBBDTDecision_Dec;
   Bool_t          BHlt2Topo4BodyBBDTDecision_TIS;
   Bool_t          BHlt2Topo4BodyBBDTDecision_TOS;
   Bool_t          BHlt2SingleMuonDecision_Dec;
   Bool_t          BHlt2SingleMuonDecision_TIS;
   Bool_t          BHlt2SingleMuonDecision_TOS;
   Bool_t          BHlt2SingleMuonHighPTDecision_Dec;
   Bool_t          BHlt2SingleMuonHighPTDecision_TIS;
   Bool_t          BHlt2SingleMuonHighPTDecision_TOS;
   Bool_t          BHlt2SingleMuonLowPTDecision_Dec;
   Bool_t          BHlt2SingleMuonLowPTDecision_TIS;
   Bool_t          BHlt2SingleMuonLowPTDecision_TOS;
   Bool_t          BHlt2TopoMu2BodyBBDTDecision_Dec;
   Bool_t          BHlt2TopoMu2BodyBBDTDecision_TIS;
   Bool_t          BHlt2TopoMu2BodyBBDTDecision_TOS;
   Bool_t          BHlt2TopoMu3BodyBBDTDecision_Dec;
   Bool_t          BHlt2TopoMu3BodyBBDTDecision_TIS;
   Bool_t          BHlt2TopoMu3BodyBBDTDecision_TOS;
   Bool_t          BHlt2TopoMu4BodyBBDTDecision_Dec;
   Bool_t          BHlt2TopoMu4BodyBBDTDecision_TIS;
   Bool_t          BHlt2TopoMu4BodyBBDTDecision_TOS;
   Bool_t          BHlt2MuonFromHLT1Decision_Dec;
   Bool_t          BHlt2MuonFromHLT1Decision_TIS;
   Bool_t          BHlt2MuonFromHLT1Decision_TOS;
   Bool_t          BHlt2DiMuonDecision_Dec;
   Bool_t          BHlt2DiMuonDecision_TIS;
   Bool_t          BHlt2DiMuonDecision_TOS;
   Bool_t          BHlt2DiMuonLowMassDecision_Dec;
   Bool_t          BHlt2DiMuonLowMassDecision_TIS;
   Bool_t          BHlt2DiMuonLowMassDecision_TOS;
   Bool_t          BHlt2DiMuonJPsiDecision_Dec;
   Bool_t          BHlt2DiMuonJPsiDecision_TIS;
   Bool_t          BHlt2DiMuonJPsiDecision_TOS;
   Bool_t          BHlt2DiMuonJPsiHighPTDecision_Dec;
   Bool_t          BHlt2DiMuonJPsiHighPTDecision_TIS;
   Bool_t          BHlt2DiMuonJPsiHighPTDecision_TOS;
   Bool_t          BHlt2DiMuonPsi2SDecision_Dec;
   Bool_t          BHlt2DiMuonPsi2SDecision_TIS;
   Bool_t          BHlt2DiMuonPsi2SDecision_TOS;
   Bool_t          BHlt2DiMuonPsi2SHighPTDecision_Dec;
   Bool_t          BHlt2DiMuonPsi2SHighPTDecision_TIS;
   Bool_t          BHlt2DiMuonPsi2SHighPTDecision_TOS;
   Bool_t          BHlt2DiMuonBDecision_Dec;
   Bool_t          BHlt2DiMuonBDecision_TIS;
   Bool_t          BHlt2DiMuonBDecision_TOS;
   Bool_t          BHlt2DiMuonDetachedDecision_Dec;
   Bool_t          BHlt2DiMuonDetachedDecision_TIS;
   Bool_t          BHlt2DiMuonDetachedDecision_TOS;
   Bool_t          BHlt2DiMuonDetachedHeavyDecision_Dec;
   Bool_t          BHlt2DiMuonDetachedHeavyDecision_TIS;
   Bool_t          BHlt2DiMuonDetachedHeavyDecision_TOS;
   Bool_t          BHlt2DiMuonDetachedJPsiDecision_Dec;
   Bool_t          BHlt2DiMuonDetachedJPsiDecision_TIS;
   Bool_t          BHlt2DiMuonDetachedJPsiDecision_TOS;
   Bool_t          BHlt2ExpressJPsiDecision_Dec;
   Bool_t          BHlt2ExpressJPsiDecision_TIS;
   Bool_t          BHlt2ExpressJPsiDecision_TOS;
   Double_t        piminus_MINIP;
   Double_t        piminus_MINIPCHI2;
   Double_t        piminus_MINIPNEXTBEST;
   Double_t        piminus_MINIPCHI2NEXTBEST;
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
   Int_t           piminus_TRUEID;
   Int_t           piminus_MC_MOTHER_ID;
   Int_t           piminus_MC_MOTHER_KEY;
   Int_t           piminus_MC_GD_MOTHER_ID;
   Int_t           piminus_MC_GD_MOTHER_KEY;
   Int_t           piminus_MC_GD_GD_MOTHER_ID;
   Int_t           piminus_MC_GD_GD_MOTHER_KEY;
   Double_t        piminus_TRUEP_E;
   Double_t        piminus_TRUEP_X;
   Double_t        piminus_TRUEP_Y;
   Double_t        piminus_TRUEP_Z;
   Double_t        piminus_TRUEPT;
   Double_t        piminus_TRUEORIGINVERTEX_X;
   Double_t        piminus_TRUEORIGINVERTEX_Y;
   Double_t        piminus_TRUEORIGINVERTEX_Z;
   Double_t        piminus_TRUEENDVERTEX_X;
   Double_t        piminus_TRUEENDVERTEX_Y;
   Double_t        piminus_TRUEENDVERTEX_Z;
   Bool_t          piminus_TRUEISSTABLE;
   Double_t        piminus_TRUETAU;
   Bool_t          piminus_OSCIL;
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
   Double_t        piminus_TRACK_GhostProb;
   Double_t        piminus_TRACK_CloneDist;
   Double_t        pplus_MINIP;
   Double_t        pplus_MINIPCHI2;
   Double_t        pplus_MINIPNEXTBEST;
   Double_t        pplus_MINIPCHI2NEXTBEST;
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
   Int_t           pplus_TRUEID;
   Int_t           pplus_MC_MOTHER_ID;
   Int_t           pplus_MC_MOTHER_KEY;
   Int_t           pplus_MC_GD_MOTHER_ID;
   Int_t           pplus_MC_GD_MOTHER_KEY;
   Int_t           pplus_MC_GD_GD_MOTHER_ID;
   Int_t           pplus_MC_GD_GD_MOTHER_KEY;
   Double_t        pplus_TRUEP_E;
   Double_t        pplus_TRUEP_X;
   Double_t        pplus_TRUEP_Y;
   Double_t        pplus_TRUEP_Z;
   Double_t        pplus_TRUEPT;
   Double_t        pplus_TRUEORIGINVERTEX_X;
   Double_t        pplus_TRUEORIGINVERTEX_Y;
   Double_t        pplus_TRUEORIGINVERTEX_Z;
   Double_t        pplus_TRUEENDVERTEX_X;
   Double_t        pplus_TRUEENDVERTEX_Y;
   Double_t        pplus_TRUEENDVERTEX_Z;
   Bool_t          pplus_TRUEISSTABLE;
   Double_t        pplus_TRUETAU;
   Bool_t          pplus_OSCIL;
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
   Double_t        pplus_TRACK_GhostProb;
   Double_t        pplus_TRACK_CloneDist;
   Double_t        Psi_MINIP;
   Double_t        Psi_MINIPCHI2;
   Double_t        Psi_MINIPNEXTBEST;
   Double_t        Psi_MINIPCHI2NEXTBEST;
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
   Int_t           Psi_BKGCAT;
   Int_t           Psi_TRUEID;
   Int_t           Psi_MC_MOTHER_ID;
   Int_t           Psi_MC_MOTHER_KEY;
   Int_t           Psi_MC_GD_MOTHER_ID;
   Int_t           Psi_MC_GD_MOTHER_KEY;
   Int_t           Psi_MC_GD_GD_MOTHER_ID;
   Int_t           Psi_MC_GD_GD_MOTHER_KEY;
   Double_t        Psi_TRUEP_E;
   Double_t        Psi_TRUEP_X;
   Double_t        Psi_TRUEP_Y;
   Double_t        Psi_TRUEP_Z;
   Double_t        Psi_TRUEPT;
   Double_t        Psi_TRUEORIGINVERTEX_X;
   Double_t        Psi_TRUEORIGINVERTEX_Y;
   Double_t        Psi_TRUEORIGINVERTEX_Z;
   Double_t        Psi_TRUEENDVERTEX_X;
   Double_t        Psi_TRUEENDVERTEX_Y;
   Double_t        Psi_TRUEENDVERTEX_Z;
   Bool_t          Psi_TRUEISSTABLE;
   Double_t        Psi_TRUETAU;
   Bool_t          Psi_OSCIL;
   Int_t           Psi_ID;
   Double_t        Psi_TAU;
   Double_t        Psi_TAUERR;
   Double_t        Psi_TAUCHI2;
   Bool_t          PsiL0Global_Dec;
   Bool_t          PsiL0Global_TIS;
   Bool_t          PsiL0Global_TOS;
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
   Bool_t          PsiStrippingGlobal_Dec;
   Bool_t          PsiStrippingGlobal_TIS;
   Bool_t          PsiStrippingGlobal_TOS;
   Bool_t          PsiL0HadronDecision_Dec;
   Bool_t          PsiL0HadronDecision_TIS;
   Bool_t          PsiL0HadronDecision_TOS;
   Bool_t          PsiL0MuonDecision_Dec;
   Bool_t          PsiL0MuonDecision_TIS;
   Bool_t          PsiL0MuonDecision_TOS;
   Bool_t          PsiL0DiMuonDecision_Dec;
   Bool_t          PsiL0DiMuonDecision_TIS;
   Bool_t          PsiL0DiMuonDecision_TOS;
   Bool_t          PsiL0ElectronDecision_Dec;
   Bool_t          PsiL0ElectronDecision_TIS;
   Bool_t          PsiL0ElectronDecision_TOS;
   Bool_t          PsiL0PhotonDecision_Dec;
   Bool_t          PsiL0PhotonDecision_TIS;
   Bool_t          PsiL0PhotonDecision_TOS;
   Bool_t          PsiHlt1TrackAllL0Decision_Dec;
   Bool_t          PsiHlt1TrackAllL0Decision_TIS;
   Bool_t          PsiHlt1TrackAllL0Decision_TOS;
   Bool_t          PsiHlt1DiMuonHighMassDecision_Dec;
   Bool_t          PsiHlt1DiMuonHighMassDecision_TIS;
   Bool_t          PsiHlt1DiMuonHighMassDecision_TOS;
   Bool_t          PsiHlt1DiMuonLowMassDecision_Dec;
   Bool_t          PsiHlt1DiMuonLowMassDecision_TIS;
   Bool_t          PsiHlt1DiMuonLowMassDecision_TOS;
   Bool_t          PsiHlt1SingleMuonNoIPDecision_Dec;
   Bool_t          PsiHlt1SingleMuonNoIPDecision_TIS;
   Bool_t          PsiHlt1SingleMuonNoIPDecision_TOS;
   Bool_t          PsiHlt1SingleMuonHighPTDecision_Dec;
   Bool_t          PsiHlt1SingleMuonHighPTDecision_TIS;
   Bool_t          PsiHlt1SingleMuonHighPTDecision_TOS;
   Bool_t          PsiHlt1TrackMuonDecision_Dec;
   Bool_t          PsiHlt1TrackMuonDecision_TIS;
   Bool_t          PsiHlt1TrackMuonDecision_TOS;
   Bool_t          PsiHlt2TransparentDecision_Dec;
   Bool_t          PsiHlt2TransparentDecision_TIS;
   Bool_t          PsiHlt2TransparentDecision_TOS;
   Bool_t          PsiHlt2Topo2BodySimpleDecision_Dec;
   Bool_t          PsiHlt2Topo2BodySimpleDecision_TIS;
   Bool_t          PsiHlt2Topo2BodySimpleDecision_TOS;
   Bool_t          PsiHlt2Topo3BodySimpleDecision_Dec;
   Bool_t          PsiHlt2Topo3BodySimpleDecision_TIS;
   Bool_t          PsiHlt2Topo3BodySimpleDecision_TOS;
   Bool_t          PsiHlt2Topo4BodySimpleDecision_Dec;
   Bool_t          PsiHlt2Topo4BodySimpleDecision_TIS;
   Bool_t          PsiHlt2Topo4BodySimpleDecision_TOS;
   Bool_t          PsiHlt2Topo2BodyBBDTDecision_Dec;
   Bool_t          PsiHlt2Topo2BodyBBDTDecision_TIS;
   Bool_t          PsiHlt2Topo2BodyBBDTDecision_TOS;
   Bool_t          PsiHlt2Topo3BodyBBDTDecision_Dec;
   Bool_t          PsiHlt2Topo3BodyBBDTDecision_TIS;
   Bool_t          PsiHlt2Topo3BodyBBDTDecision_TOS;
   Bool_t          PsiHlt2Topo4BodyBBDTDecision_Dec;
   Bool_t          PsiHlt2Topo4BodyBBDTDecision_TIS;
   Bool_t          PsiHlt2Topo4BodyBBDTDecision_TOS;
   Bool_t          PsiHlt2SingleMuonDecision_Dec;
   Bool_t          PsiHlt2SingleMuonDecision_TIS;
   Bool_t          PsiHlt2SingleMuonDecision_TOS;
   Bool_t          PsiHlt2SingleMuonHighPTDecision_Dec;
   Bool_t          PsiHlt2SingleMuonHighPTDecision_TIS;
   Bool_t          PsiHlt2SingleMuonHighPTDecision_TOS;
   Bool_t          PsiHlt2SingleMuonLowPTDecision_Dec;
   Bool_t          PsiHlt2SingleMuonLowPTDecision_TIS;
   Bool_t          PsiHlt2SingleMuonLowPTDecision_TOS;
   Bool_t          PsiHlt2TopoMu2BodyBBDTDecision_Dec;
   Bool_t          PsiHlt2TopoMu2BodyBBDTDecision_TIS;
   Bool_t          PsiHlt2TopoMu2BodyBBDTDecision_TOS;
   Bool_t          PsiHlt2TopoMu3BodyBBDTDecision_Dec;
   Bool_t          PsiHlt2TopoMu3BodyBBDTDecision_TIS;
   Bool_t          PsiHlt2TopoMu3BodyBBDTDecision_TOS;
   Bool_t          PsiHlt2TopoMu4BodyBBDTDecision_Dec;
   Bool_t          PsiHlt2TopoMu4BodyBBDTDecision_TIS;
   Bool_t          PsiHlt2TopoMu4BodyBBDTDecision_TOS;
   Bool_t          PsiHlt2MuonFromHLT1Decision_Dec;
   Bool_t          PsiHlt2MuonFromHLT1Decision_TIS;
   Bool_t          PsiHlt2MuonFromHLT1Decision_TOS;
   Bool_t          PsiHlt2DiMuonDecision_Dec;
   Bool_t          PsiHlt2DiMuonDecision_TIS;
   Bool_t          PsiHlt2DiMuonDecision_TOS;
   Bool_t          PsiHlt2DiMuonLowMassDecision_Dec;
   Bool_t          PsiHlt2DiMuonLowMassDecision_TIS;
   Bool_t          PsiHlt2DiMuonLowMassDecision_TOS;
   Bool_t          PsiHlt2DiMuonJPsiDecision_Dec;
   Bool_t          PsiHlt2DiMuonJPsiDecision_TIS;
   Bool_t          PsiHlt2DiMuonJPsiDecision_TOS;
   Bool_t          PsiHlt2DiMuonJPsiHighPTDecision_Dec;
   Bool_t          PsiHlt2DiMuonJPsiHighPTDecision_TIS;
   Bool_t          PsiHlt2DiMuonJPsiHighPTDecision_TOS;
   Bool_t          PsiHlt2DiMuonPsi2SDecision_Dec;
   Bool_t          PsiHlt2DiMuonPsi2SDecision_TIS;
   Bool_t          PsiHlt2DiMuonPsi2SDecision_TOS;
   Bool_t          PsiHlt2DiMuonPsi2SHighPTDecision_Dec;
   Bool_t          PsiHlt2DiMuonPsi2SHighPTDecision_TIS;
   Bool_t          PsiHlt2DiMuonPsi2SHighPTDecision_TOS;
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
   Bool_t          PsiHlt2ExpressJPsiDecision_Dec;
   Bool_t          PsiHlt2ExpressJPsiDecision_TIS;
   Bool_t          PsiHlt2ExpressJPsiDecision_TOS;
   Int_t           Psi_NOPARTWITHINDCHI2WDW;
   Int_t           Psi_NOPARTWITHINCHI2WDW;
   Double_t        Psi_SMALLESTCHI2;
   Double_t        Psi_SMALLESTDELTACHI2;
   Double_t        muminus_MINIP;
   Double_t        muminus_MINIPCHI2;
   Double_t        muminus_MINIPNEXTBEST;
   Double_t        muminus_MINIPCHI2NEXTBEST;
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
   Int_t           muminus_TRUEID;
   Int_t           muminus_MC_MOTHER_ID;
   Int_t           muminus_MC_MOTHER_KEY;
   Int_t           muminus_MC_GD_MOTHER_ID;
   Int_t           muminus_MC_GD_MOTHER_KEY;
   Int_t           muminus_MC_GD_GD_MOTHER_ID;
   Int_t           muminus_MC_GD_GD_MOTHER_KEY;
   Double_t        muminus_TRUEP_E;
   Double_t        muminus_TRUEP_X;
   Double_t        muminus_TRUEP_Y;
   Double_t        muminus_TRUEP_Z;
   Double_t        muminus_TRUEPT;
   Double_t        muminus_TRUEORIGINVERTEX_X;
   Double_t        muminus_TRUEORIGINVERTEX_Y;
   Double_t        muminus_TRUEORIGINVERTEX_Z;
   Double_t        muminus_TRUEENDVERTEX_X;
   Double_t        muminus_TRUEENDVERTEX_Y;
   Double_t        muminus_TRUEENDVERTEX_Z;
   Bool_t          muminus_TRUEISSTABLE;
   Double_t        muminus_TRUETAU;
   Bool_t          muminus_OSCIL;
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
   Double_t        muminus_TRACK_GhostProb;
   Double_t        muminus_TRACK_CloneDist;
   Double_t        muplus_MINIP;
   Double_t        muplus_MINIPCHI2;
   Double_t        muplus_MINIPNEXTBEST;
   Double_t        muplus_MINIPCHI2NEXTBEST;
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
   Int_t           muplus_TRUEID;
   Int_t           muplus_MC_MOTHER_ID;
   Int_t           muplus_MC_MOTHER_KEY;
   Int_t           muplus_MC_GD_MOTHER_ID;
   Int_t           muplus_MC_GD_MOTHER_KEY;
   Int_t           muplus_MC_GD_GD_MOTHER_ID;
   Int_t           muplus_MC_GD_GD_MOTHER_KEY;
   Double_t        muplus_TRUEP_E;
   Double_t        muplus_TRUEP_X;
   Double_t        muplus_TRUEP_Y;
   Double_t        muplus_TRUEP_Z;
   Double_t        muplus_TRUEPT;
   Double_t        muplus_TRUEORIGINVERTEX_X;
   Double_t        muplus_TRUEORIGINVERTEX_Y;
   Double_t        muplus_TRUEORIGINVERTEX_Z;
   Double_t        muplus_TRUEENDVERTEX_X;
   Double_t        muplus_TRUEENDVERTEX_Y;
   Double_t        muplus_TRUEENDVERTEX_Z;
   Bool_t          muplus_TRUEISSTABLE;
   Double_t        muplus_TRUETAU;
   Bool_t          muplus_OSCIL;
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
   Double_t        muplus_TRACK_GhostProb;
   Double_t        muplus_TRACK_CloneDist;
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
   UInt_t          Primaries;
   Short_t         Polarity;
   Int_t           nPV;
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
   TBranch        *b_B_MINIP;   //!
   TBranch        *b_B_MINIPCHI2;   //!
   TBranch        *b_B_MINIPNEXTBEST;   //!
   TBranch        *b_B_MINIPCHI2NEXTBEST;   //!
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
   TBranch        *b_B_BKGCAT;   //!
   TBranch        *b_B_TRUEID;   //!
   TBranch        *b_B_MC_MOTHER_ID;   //!
   TBranch        *b_B_MC_MOTHER_KEY;   //!
   TBranch        *b_B_MC_GD_MOTHER_ID;   //!
   TBranch        *b_B_MC_GD_MOTHER_KEY;   //!
   TBranch        *b_B_MC_GD_GD_MOTHER_ID;   //!
   TBranch        *b_B_MC_GD_GD_MOTHER_KEY;   //!
   TBranch        *b_B_TRUEP_E;   //!
   TBranch        *b_B_TRUEP_X;   //!
   TBranch        *b_B_TRUEP_Y;   //!
   TBranch        *b_B_TRUEP_Z;   //!
   TBranch        *b_B_TRUEPT;   //!
   TBranch        *b_B_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_B_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_B_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_B_TRUEENDVERTEX_X;   //!
   TBranch        *b_B_TRUEENDVERTEX_Y;   //!
   TBranch        *b_B_TRUEENDVERTEX_Z;   //!
   TBranch        *b_B_TRUEISSTABLE;   //!
   TBranch        *b_B_TRUETAU;   //!
   TBranch        *b_B_OSCIL;   //!
   TBranch        *b_B_ID;   //!
   TBranch        *b_B_TAU;   //!
   TBranch        *b_B_TAUERR;   //!
   TBranch        *b_B_TAUCHI2;   //!
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
   TBranch        *b_B_FullFit_chi2_B;   //!
   TBranch        *b_B_FullFit_chi2;   //!
   TBranch        *b_B_FullFit_ctau;   //!
   TBranch        *b_B_FullFit_ctauErr;   //!
   TBranch        *b_B_FullFit_decayLength;   //!
   TBranch        *b_B_FullFit_decayLengthErr;   //!
   TBranch        *b_B_FullFit_nDOF;   //!
   TBranch        *b_B_FullFit_nIter;   //!
   TBranch        *b_B_FullFit_status;   //!
   TBranch        *b_B_MassFit_nPV;   //!
   TBranch        *b_B_MassFit_J_psi_1S_M;   //!
   TBranch        *b_B_MassFit_J_psi_1S_MERR;   //!
   TBranch        *b_B_MassFit_J_psi_1S_P;   //!
   TBranch        *b_B_MassFit_J_psi_1S_PERR;   //!
   TBranch        *b_B_MassFit_J_psi_1S_ctau;   //!
   TBranch        *b_B_MassFit_J_psi_1S_ctauErr;   //!
   TBranch        *b_B_MassFit_J_psi_1S_decayLength;   //!
   TBranch        *b_B_MassFit_J_psi_1S_decayLengthErr;   //!
   TBranch        *b_B_MassFit_M;   //!
   TBranch        *b_B_MassFit_MERR;   //!
   TBranch        *b_B_MassFit_P;   //!
   TBranch        *b_B_MassFit_PERR;   //!
   TBranch        *b_B_MassFit_chi2_B;   //!
   TBranch        *b_B_MassFit_nDOF;   //!
   TBranch        *b_B_MassFit_nIter;   //!
   TBranch        *b_B_MassFit_status;   //!
   TBranch        *b_B_SubKpi_nPV;   //!
   TBranch        *b_B_SubKpi_J_psi_1S_M;   //!
   TBranch        *b_B_SubKpi_J_psi_1S_MERR;   //!
   TBranch        *b_B_SubKpi_J_psi_1S_P;   //!
   TBranch        *b_B_SubKpi_J_psi_1S_PERR;   //!
   TBranch        *b_B_SubKpi_J_psi_1S_ctau;   //!
   TBranch        *b_B_SubKpi_J_psi_1S_ctauErr;   //!
   TBranch        *b_B_SubKpi_J_psi_1S_decayLength;   //!
   TBranch        *b_B_SubKpi_J_psi_1S_decayLengthErr;   //!
   TBranch        *b_B_SubKpi_M;   //!
   TBranch        *b_B_SubKpi_MERR;   //!
   TBranch        *b_B_SubKpi_P;   //!
   TBranch        *b_B_SubKpi_PERR;   //!
   TBranch        *b_B_SubKpi_PV_X;   //!
   TBranch        *b_B_SubKpi_PV_Y;   //!
   TBranch        *b_B_SubKpi_PV_Z;   //!
   TBranch        *b_B_SubKpi_PV_key;   //!
   TBranch        *b_B_SubKpi_chi2_B;   //!
   TBranch        *b_B_SubKpi_ctau;   //!
   TBranch        *b_B_SubKpi_ctauErr;   //!
   TBranch        *b_B_SubKpi_decayLength;   //!
   TBranch        *b_B_SubKpi_decayLengthErr;   //!
   TBranch        *b_B_SubKpi_nDOF;   //!
   TBranch        *b_B_SubKpi_nIter;   //!
   TBranch        *b_B_SubKpi_status;   //!
   TBranch        *b_B_SubpK_nPV;   //!
   TBranch        *b_B_SubpK_J_psi_1S_M;   //!
   TBranch        *b_B_SubpK_J_psi_1S_MERR;   //!
   TBranch        *b_B_SubpK_J_psi_1S_P;   //!
   TBranch        *b_B_SubpK_J_psi_1S_PERR;   //!
   TBranch        *b_B_SubpK_J_psi_1S_ctau;   //!
   TBranch        *b_B_SubpK_J_psi_1S_ctauErr;   //!
   TBranch        *b_B_SubpK_J_psi_1S_decayLength;   //!
   TBranch        *b_B_SubpK_J_psi_1S_decayLengthErr;   //!
   TBranch        *b_B_SubpK_M;   //!
   TBranch        *b_B_SubpK_MERR;   //!
   TBranch        *b_B_SubpK_P;   //!
   TBranch        *b_B_SubpK_PERR;   //!
   TBranch        *b_B_SubpK_PV_X;   //!
   TBranch        *b_B_SubpK_PV_Y;   //!
   TBranch        *b_B_SubpK_PV_Z;   //!
   TBranch        *b_B_SubpK_PV_key;   //!
   TBranch        *b_B_SubpK_chi2_B;   //!
   TBranch        *b_B_SubpK_ctau;   //!
   TBranch        *b_B_SubpK_ctauErr;   //!
   TBranch        *b_B_SubpK_decayLength;   //!
   TBranch        *b_B_SubpK_decayLengthErr;   //!
   TBranch        *b_B_SubpK_nDOF;   //!
   TBranch        *b_B_SubpK_nIter;   //!
   TBranch        *b_B_SubpK_status;   //!
   TBranch        *b_BL0Global_Dec;   //!
   TBranch        *b_BL0Global_TIS;   //!
   TBranch        *b_BL0Global_TOS;   //!
   TBranch        *b_BHlt1Global_Dec;   //!
   TBranch        *b_BHlt1Global_TIS;   //!
   TBranch        *b_BHlt1Global_TOS;   //!
   TBranch        *b_BHlt1Phys_Dec;   //!
   TBranch        *b_BHlt1Phys_TIS;   //!
   TBranch        *b_BHlt1Phys_TOS;   //!
   TBranch        *b_BHlt2Global_Dec;   //!
   TBranch        *b_BHlt2Global_TIS;   //!
   TBranch        *b_BHlt2Global_TOS;   //!
   TBranch        *b_BHlt2Phys_Dec;   //!
   TBranch        *b_BHlt2Phys_TIS;   //!
   TBranch        *b_BHlt2Phys_TOS;   //!
   TBranch        *b_BStrippingGlobal_Dec;   //!
   TBranch        *b_BStrippingGlobal_TIS;   //!
   TBranch        *b_BStrippingGlobal_TOS;   //!
   TBranch        *b_BL0HadronDecision_Dec;   //!
   TBranch        *b_BL0HadronDecision_TIS;   //!
   TBranch        *b_BL0HadronDecision_TOS;   //!
   TBranch        *b_BL0MuonDecision_Dec;   //!
   TBranch        *b_BL0MuonDecision_TIS;   //!
   TBranch        *b_BL0MuonDecision_TOS;   //!
   TBranch        *b_BL0DiMuonDecision_Dec;   //!
   TBranch        *b_BL0DiMuonDecision_TIS;   //!
   TBranch        *b_BL0DiMuonDecision_TOS;   //!
   TBranch        *b_BL0ElectronDecision_Dec;   //!
   TBranch        *b_BL0ElectronDecision_TIS;   //!
   TBranch        *b_BL0ElectronDecision_TOS;   //!
   TBranch        *b_BL0PhotonDecision_Dec;   //!
   TBranch        *b_BL0PhotonDecision_TIS;   //!
   TBranch        *b_BL0PhotonDecision_TOS;   //!
   TBranch        *b_BHlt1TrackAllL0Decision_Dec;   //!
   TBranch        *b_BHlt1TrackAllL0Decision_TIS;   //!
   TBranch        *b_BHlt1TrackAllL0Decision_TOS;   //!
   TBranch        *b_BHlt1DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_BHlt1DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_BHlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_BHlt1DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_BHlt1DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_BHlt1DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_BHlt1SingleMuonNoIPDecision_Dec;   //!
   TBranch        *b_BHlt1SingleMuonNoIPDecision_TIS;   //!
   TBranch        *b_BHlt1SingleMuonNoIPDecision_TOS;   //!
   TBranch        *b_BHlt1SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_BHlt1SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_BHlt1SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_BHlt1TrackMuonDecision_Dec;   //!
   TBranch        *b_BHlt1TrackMuonDecision_TIS;   //!
   TBranch        *b_BHlt1TrackMuonDecision_TOS;   //!
   TBranch        *b_BHlt2TransparentDecision_Dec;   //!
   TBranch        *b_BHlt2TransparentDecision_TIS;   //!
   TBranch        *b_BHlt2TransparentDecision_TOS;   //!
   TBranch        *b_BHlt2Topo2BodySimpleDecision_Dec;   //!
   TBranch        *b_BHlt2Topo2BodySimpleDecision_TIS;   //!
   TBranch        *b_BHlt2Topo2BodySimpleDecision_TOS;   //!
   TBranch        *b_BHlt2Topo3BodySimpleDecision_Dec;   //!
   TBranch        *b_BHlt2Topo3BodySimpleDecision_TIS;   //!
   TBranch        *b_BHlt2Topo3BodySimpleDecision_TOS;   //!
   TBranch        *b_BHlt2Topo4BodySimpleDecision_Dec;   //!
   TBranch        *b_BHlt2Topo4BodySimpleDecision_TIS;   //!
   TBranch        *b_BHlt2Topo4BodySimpleDecision_TOS;   //!
   TBranch        *b_BHlt2Topo2BodyBBDTDecision_Dec;   //!
   TBranch        *b_BHlt2Topo2BodyBBDTDecision_TIS;   //!
   TBranch        *b_BHlt2Topo2BodyBBDTDecision_TOS;   //!
   TBranch        *b_BHlt2Topo3BodyBBDTDecision_Dec;   //!
   TBranch        *b_BHlt2Topo3BodyBBDTDecision_TIS;   //!
   TBranch        *b_BHlt2Topo3BodyBBDTDecision_TOS;   //!
   TBranch        *b_BHlt2Topo4BodyBBDTDecision_Dec;   //!
   TBranch        *b_BHlt2Topo4BodyBBDTDecision_TIS;   //!
   TBranch        *b_BHlt2Topo4BodyBBDTDecision_TOS;   //!
   TBranch        *b_BHlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_BHlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_BHlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_BHlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_BHlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_BHlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_BHlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_BHlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_BHlt2SingleMuonLowPTDecision_TOS;   //!
   TBranch        *b_BHlt2TopoMu2BodyBBDTDecision_Dec;   //!
   TBranch        *b_BHlt2TopoMu2BodyBBDTDecision_TIS;   //!
   TBranch        *b_BHlt2TopoMu2BodyBBDTDecision_TOS;   //!
   TBranch        *b_BHlt2TopoMu3BodyBBDTDecision_Dec;   //!
   TBranch        *b_BHlt2TopoMu3BodyBBDTDecision_TIS;   //!
   TBranch        *b_BHlt2TopoMu3BodyBBDTDecision_TOS;   //!
   TBranch        *b_BHlt2TopoMu4BodyBBDTDecision_Dec;   //!
   TBranch        *b_BHlt2TopoMu4BodyBBDTDecision_TIS;   //!
   TBranch        *b_BHlt2TopoMu4BodyBBDTDecision_TOS;   //!
   TBranch        *b_BHlt2MuonFromHLT1Decision_Dec;   //!
   TBranch        *b_BHlt2MuonFromHLT1Decision_TIS;   //!
   TBranch        *b_BHlt2MuonFromHLT1Decision_TOS;   //!
   TBranch        *b_BHlt2DiMuonDecision_Dec;   //!
   TBranch        *b_BHlt2DiMuonDecision_TIS;   //!
   TBranch        *b_BHlt2DiMuonDecision_TOS;   //!
   TBranch        *b_BHlt2DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_BHlt2DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_BHlt2DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_BHlt2DiMuonJPsiDecision_Dec;   //!
   TBranch        *b_BHlt2DiMuonJPsiDecision_TIS;   //!
   TBranch        *b_BHlt2DiMuonJPsiDecision_TOS;   //!
   TBranch        *b_BHlt2DiMuonJPsiHighPTDecision_Dec;   //!
   TBranch        *b_BHlt2DiMuonJPsiHighPTDecision_TIS;   //!
   TBranch        *b_BHlt2DiMuonJPsiHighPTDecision_TOS;   //!
   TBranch        *b_BHlt2DiMuonPsi2SDecision_Dec;   //!
   TBranch        *b_BHlt2DiMuonPsi2SDecision_TIS;   //!
   TBranch        *b_BHlt2DiMuonPsi2SDecision_TOS;   //!
   TBranch        *b_BHlt2DiMuonPsi2SHighPTDecision_Dec;   //!
   TBranch        *b_BHlt2DiMuonPsi2SHighPTDecision_TIS;   //!
   TBranch        *b_BHlt2DiMuonPsi2SHighPTDecision_TOS;   //!
   TBranch        *b_BHlt2DiMuonBDecision_Dec;   //!
   TBranch        *b_BHlt2DiMuonBDecision_TIS;   //!
   TBranch        *b_BHlt2DiMuonBDecision_TOS;   //!
   TBranch        *b_BHlt2DiMuonDetachedDecision_Dec;   //!
   TBranch        *b_BHlt2DiMuonDetachedDecision_TIS;   //!
   TBranch        *b_BHlt2DiMuonDetachedDecision_TOS;   //!
   TBranch        *b_BHlt2DiMuonDetachedHeavyDecision_Dec;   //!
   TBranch        *b_BHlt2DiMuonDetachedHeavyDecision_TIS;   //!
   TBranch        *b_BHlt2DiMuonDetachedHeavyDecision_TOS;   //!
   TBranch        *b_BHlt2DiMuonDetachedJPsiDecision_Dec;   //!
   TBranch        *b_BHlt2DiMuonDetachedJPsiDecision_TIS;   //!
   TBranch        *b_BHlt2DiMuonDetachedJPsiDecision_TOS;   //!
   TBranch        *b_BHlt2ExpressJPsiDecision_Dec;   //!
   TBranch        *b_BHlt2ExpressJPsiDecision_TIS;   //!
   TBranch        *b_BHlt2ExpressJPsiDecision_TOS;   //!
   TBranch        *b_piminus_MINIP;   //!
   TBranch        *b_piminus_MINIPCHI2;   //!
   TBranch        *b_piminus_MINIPNEXTBEST;   //!
   TBranch        *b_piminus_MINIPCHI2NEXTBEST;   //!
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
   TBranch        *b_piminus_TRUEID;   //!
   TBranch        *b_piminus_MC_MOTHER_ID;   //!
   TBranch        *b_piminus_MC_MOTHER_KEY;   //!
   TBranch        *b_piminus_MC_GD_MOTHER_ID;   //!
   TBranch        *b_piminus_MC_GD_MOTHER_KEY;   //!
   TBranch        *b_piminus_MC_GD_GD_MOTHER_ID;   //!
   TBranch        *b_piminus_MC_GD_GD_MOTHER_KEY;   //!
   TBranch        *b_piminus_TRUEP_E;   //!
   TBranch        *b_piminus_TRUEP_X;   //!
   TBranch        *b_piminus_TRUEP_Y;   //!
   TBranch        *b_piminus_TRUEP_Z;   //!
   TBranch        *b_piminus_TRUEPT;   //!
   TBranch        *b_piminus_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_piminus_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_piminus_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_piminus_TRUEENDVERTEX_X;   //!
   TBranch        *b_piminus_TRUEENDVERTEX_Y;   //!
   TBranch        *b_piminus_TRUEENDVERTEX_Z;   //!
   TBranch        *b_piminus_TRUEISSTABLE;   //!
   TBranch        *b_piminus_TRUETAU;   //!
   TBranch        *b_piminus_OSCIL;   //!
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
   TBranch        *b_piminus_TRACK_GhostProb;   //!
   TBranch        *b_piminus_TRACK_CloneDist;   //!
   TBranch        *b_pplus_MINIP;   //!
   TBranch        *b_pplus_MINIPCHI2;   //!
   TBranch        *b_pplus_MINIPNEXTBEST;   //!
   TBranch        *b_pplus_MINIPCHI2NEXTBEST;   //!
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
   TBranch        *b_pplus_TRUEID;   //!
   TBranch        *b_pplus_MC_MOTHER_ID;   //!
   TBranch        *b_pplus_MC_MOTHER_KEY;   //!
   TBranch        *b_pplus_MC_GD_MOTHER_ID;   //!
   TBranch        *b_pplus_MC_GD_MOTHER_KEY;   //!
   TBranch        *b_pplus_MC_GD_GD_MOTHER_ID;   //!
   TBranch        *b_pplus_MC_GD_GD_MOTHER_KEY;   //!
   TBranch        *b_pplus_TRUEP_E;   //!
   TBranch        *b_pplus_TRUEP_X;   //!
   TBranch        *b_pplus_TRUEP_Y;   //!
   TBranch        *b_pplus_TRUEP_Z;   //!
   TBranch        *b_pplus_TRUEPT;   //!
   TBranch        *b_pplus_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_pplus_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_pplus_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_pplus_TRUEENDVERTEX_X;   //!
   TBranch        *b_pplus_TRUEENDVERTEX_Y;   //!
   TBranch        *b_pplus_TRUEENDVERTEX_Z;   //!
   TBranch        *b_pplus_TRUEISSTABLE;   //!
   TBranch        *b_pplus_TRUETAU;   //!
   TBranch        *b_pplus_OSCIL;   //!
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
   TBranch        *b_pplus_TRACK_GhostProb;   //!
   TBranch        *b_pplus_TRACK_CloneDist;   //!
   TBranch        *b_Psi_MINIP;   //!
   TBranch        *b_Psi_MINIPCHI2;   //!
   TBranch        *b_Psi_MINIPNEXTBEST;   //!
   TBranch        *b_Psi_MINIPCHI2NEXTBEST;   //!
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
   TBranch        *b_Psi_BKGCAT;   //!
   TBranch        *b_Psi_TRUEID;   //!
   TBranch        *b_Psi_MC_MOTHER_ID;   //!
   TBranch        *b_Psi_MC_MOTHER_KEY;   //!
   TBranch        *b_Psi_MC_GD_MOTHER_ID;   //!
   TBranch        *b_Psi_MC_GD_MOTHER_KEY;   //!
   TBranch        *b_Psi_MC_GD_GD_MOTHER_ID;   //!
   TBranch        *b_Psi_MC_GD_GD_MOTHER_KEY;   //!
   TBranch        *b_Psi_TRUEP_E;   //!
   TBranch        *b_Psi_TRUEP_X;   //!
   TBranch        *b_Psi_TRUEP_Y;   //!
   TBranch        *b_Psi_TRUEP_Z;   //!
   TBranch        *b_Psi_TRUEPT;   //!
   TBranch        *b_Psi_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_Psi_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_Psi_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_Psi_TRUEENDVERTEX_X;   //!
   TBranch        *b_Psi_TRUEENDVERTEX_Y;   //!
   TBranch        *b_Psi_TRUEENDVERTEX_Z;   //!
   TBranch        *b_Psi_TRUEISSTABLE;   //!
   TBranch        *b_Psi_TRUETAU;   //!
   TBranch        *b_Psi_OSCIL;   //!
   TBranch        *b_Psi_ID;   //!
   TBranch        *b_Psi_TAU;   //!
   TBranch        *b_Psi_TAUERR;   //!
   TBranch        *b_Psi_TAUCHI2;   //!
   TBranch        *b_PsiL0Global_Dec;   //!
   TBranch        *b_PsiL0Global_TIS;   //!
   TBranch        *b_PsiL0Global_TOS;   //!
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
   TBranch        *b_PsiStrippingGlobal_Dec;   //!
   TBranch        *b_PsiStrippingGlobal_TIS;   //!
   TBranch        *b_PsiStrippingGlobal_TOS;   //!
   TBranch        *b_PsiL0HadronDecision_Dec;   //!
   TBranch        *b_PsiL0HadronDecision_TIS;   //!
   TBranch        *b_PsiL0HadronDecision_TOS;   //!
   TBranch        *b_PsiL0MuonDecision_Dec;   //!
   TBranch        *b_PsiL0MuonDecision_TIS;   //!
   TBranch        *b_PsiL0MuonDecision_TOS;   //!
   TBranch        *b_PsiL0DiMuonDecision_Dec;   //!
   TBranch        *b_PsiL0DiMuonDecision_TIS;   //!
   TBranch        *b_PsiL0DiMuonDecision_TOS;   //!
   TBranch        *b_PsiL0ElectronDecision_Dec;   //!
   TBranch        *b_PsiL0ElectronDecision_TIS;   //!
   TBranch        *b_PsiL0ElectronDecision_TOS;   //!
   TBranch        *b_PsiL0PhotonDecision_Dec;   //!
   TBranch        *b_PsiL0PhotonDecision_TIS;   //!
   TBranch        *b_PsiL0PhotonDecision_TOS;   //!
   TBranch        *b_PsiHlt1TrackAllL0Decision_Dec;   //!
   TBranch        *b_PsiHlt1TrackAllL0Decision_TIS;   //!
   TBranch        *b_PsiHlt1TrackAllL0Decision_TOS;   //!
   TBranch        *b_PsiHlt1DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_PsiHlt1DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_PsiHlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_PsiHlt1DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_PsiHlt1DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_PsiHlt1DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_PsiHlt1SingleMuonNoIPDecision_Dec;   //!
   TBranch        *b_PsiHlt1SingleMuonNoIPDecision_TIS;   //!
   TBranch        *b_PsiHlt1SingleMuonNoIPDecision_TOS;   //!
   TBranch        *b_PsiHlt1SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_PsiHlt1SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_PsiHlt1SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_PsiHlt1TrackMuonDecision_Dec;   //!
   TBranch        *b_PsiHlt1TrackMuonDecision_TIS;   //!
   TBranch        *b_PsiHlt1TrackMuonDecision_TOS;   //!
   TBranch        *b_PsiHlt2TransparentDecision_Dec;   //!
   TBranch        *b_PsiHlt2TransparentDecision_TIS;   //!
   TBranch        *b_PsiHlt2TransparentDecision_TOS;   //!
   TBranch        *b_PsiHlt2Topo2BodySimpleDecision_Dec;   //!
   TBranch        *b_PsiHlt2Topo2BodySimpleDecision_TIS;   //!
   TBranch        *b_PsiHlt2Topo2BodySimpleDecision_TOS;   //!
   TBranch        *b_PsiHlt2Topo3BodySimpleDecision_Dec;   //!
   TBranch        *b_PsiHlt2Topo3BodySimpleDecision_TIS;   //!
   TBranch        *b_PsiHlt2Topo3BodySimpleDecision_TOS;   //!
   TBranch        *b_PsiHlt2Topo4BodySimpleDecision_Dec;   //!
   TBranch        *b_PsiHlt2Topo4BodySimpleDecision_TIS;   //!
   TBranch        *b_PsiHlt2Topo4BodySimpleDecision_TOS;   //!
   TBranch        *b_PsiHlt2Topo2BodyBBDTDecision_Dec;   //!
   TBranch        *b_PsiHlt2Topo2BodyBBDTDecision_TIS;   //!
   TBranch        *b_PsiHlt2Topo2BodyBBDTDecision_TOS;   //!
   TBranch        *b_PsiHlt2Topo3BodyBBDTDecision_Dec;   //!
   TBranch        *b_PsiHlt2Topo3BodyBBDTDecision_TIS;   //!
   TBranch        *b_PsiHlt2Topo3BodyBBDTDecision_TOS;   //!
   TBranch        *b_PsiHlt2Topo4BodyBBDTDecision_Dec;   //!
   TBranch        *b_PsiHlt2Topo4BodyBBDTDecision_TIS;   //!
   TBranch        *b_PsiHlt2Topo4BodyBBDTDecision_TOS;   //!
   TBranch        *b_PsiHlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_PsiHlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_PsiHlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_PsiHlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_PsiHlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_PsiHlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_PsiHlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_PsiHlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_PsiHlt2SingleMuonLowPTDecision_TOS;   //!
   TBranch        *b_PsiHlt2TopoMu2BodyBBDTDecision_Dec;   //!
   TBranch        *b_PsiHlt2TopoMu2BodyBBDTDecision_TIS;   //!
   TBranch        *b_PsiHlt2TopoMu2BodyBBDTDecision_TOS;   //!
   TBranch        *b_PsiHlt2TopoMu3BodyBBDTDecision_Dec;   //!
   TBranch        *b_PsiHlt2TopoMu3BodyBBDTDecision_TIS;   //!
   TBranch        *b_PsiHlt2TopoMu3BodyBBDTDecision_TOS;   //!
   TBranch        *b_PsiHlt2TopoMu4BodyBBDTDecision_Dec;   //!
   TBranch        *b_PsiHlt2TopoMu4BodyBBDTDecision_TIS;   //!
   TBranch        *b_PsiHlt2TopoMu4BodyBBDTDecision_TOS;   //!
   TBranch        *b_PsiHlt2MuonFromHLT1Decision_Dec;   //!
   TBranch        *b_PsiHlt2MuonFromHLT1Decision_TIS;   //!
   TBranch        *b_PsiHlt2MuonFromHLT1Decision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonDecision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonJPsiDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonJPsiDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonJPsiDecision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonJPsiHighPTDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonJPsiHighPTDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonJPsiHighPTDecision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonPsi2SDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonPsi2SDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonPsi2SDecision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonPsi2SHighPTDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonPsi2SHighPTDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonPsi2SHighPTDecision_TOS;   //!
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
   TBranch        *b_PsiHlt2ExpressJPsiDecision_Dec;   //!
   TBranch        *b_PsiHlt2ExpressJPsiDecision_TIS;   //!
   TBranch        *b_PsiHlt2ExpressJPsiDecision_TOS;   //!
   TBranch        *b_Psi_NOPARTWITHINDCHI2WDW;   //!
   TBranch        *b_Psi_NOPARTWITHINCHI2WDW;   //!
   TBranch        *b_Psi_SMALLESTCHI2;   //!
   TBranch        *b_Psi_SMALLESTDELTACHI2;   //!
   TBranch        *b_muminus_MINIP;   //!
   TBranch        *b_muminus_MINIPCHI2;   //!
   TBranch        *b_muminus_MINIPNEXTBEST;   //!
   TBranch        *b_muminus_MINIPCHI2NEXTBEST;   //!
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
   TBranch        *b_muminus_TRUEID;   //!
   TBranch        *b_muminus_MC_MOTHER_ID;   //!
   TBranch        *b_muminus_MC_MOTHER_KEY;   //!
   TBranch        *b_muminus_MC_GD_MOTHER_ID;   //!
   TBranch        *b_muminus_MC_GD_MOTHER_KEY;   //!
   TBranch        *b_muminus_MC_GD_GD_MOTHER_ID;   //!
   TBranch        *b_muminus_MC_GD_GD_MOTHER_KEY;   //!
   TBranch        *b_muminus_TRUEP_E;   //!
   TBranch        *b_muminus_TRUEP_X;   //!
   TBranch        *b_muminus_TRUEP_Y;   //!
   TBranch        *b_muminus_TRUEP_Z;   //!
   TBranch        *b_muminus_TRUEPT;   //!
   TBranch        *b_muminus_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_muminus_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_muminus_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_muminus_TRUEENDVERTEX_X;   //!
   TBranch        *b_muminus_TRUEENDVERTEX_Y;   //!
   TBranch        *b_muminus_TRUEENDVERTEX_Z;   //!
   TBranch        *b_muminus_TRUEISSTABLE;   //!
   TBranch        *b_muminus_TRUETAU;   //!
   TBranch        *b_muminus_OSCIL;   //!
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
   TBranch        *b_muminus_TRACK_GhostProb;   //!
   TBranch        *b_muminus_TRACK_CloneDist;   //!
   TBranch        *b_muplus_MINIP;   //!
   TBranch        *b_muplus_MINIPCHI2;   //!
   TBranch        *b_muplus_MINIPNEXTBEST;   //!
   TBranch        *b_muplus_MINIPCHI2NEXTBEST;   //!
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
   TBranch        *b_muplus_TRUEID;   //!
   TBranch        *b_muplus_MC_MOTHER_ID;   //!
   TBranch        *b_muplus_MC_MOTHER_KEY;   //!
   TBranch        *b_muplus_MC_GD_MOTHER_ID;   //!
   TBranch        *b_muplus_MC_GD_MOTHER_KEY;   //!
   TBranch        *b_muplus_MC_GD_GD_MOTHER_ID;   //!
   TBranch        *b_muplus_MC_GD_GD_MOTHER_KEY;   //!
   TBranch        *b_muplus_TRUEP_E;   //!
   TBranch        *b_muplus_TRUEP_X;   //!
   TBranch        *b_muplus_TRUEP_Y;   //!
   TBranch        *b_muplus_TRUEP_Z;   //!
   TBranch        *b_muplus_TRUEPT;   //!
   TBranch        *b_muplus_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_muplus_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_muplus_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_muplus_TRUEENDVERTEX_X;   //!
   TBranch        *b_muplus_TRUEENDVERTEX_Y;   //!
   TBranch        *b_muplus_TRUEENDVERTEX_Z;   //!
   TBranch        *b_muplus_TRUEISSTABLE;   //!
   TBranch        *b_muplus_TRUETAU;   //!
   TBranch        *b_muplus_OSCIL;   //!
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
   TBranch        *b_muplus_TRACK_GhostProb;   //!
   TBranch        *b_muplus_TRACK_CloneDist;   //!
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
   TBranch        *b_Primaries;   //!
   TBranch        *b_Polarity;   //!
   TBranch        *b_nPV;   //!
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

   Lambdab(TString filename);
   virtual ~Lambdab();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual Float_t Manage_B_FullFit_chi2_B(Int_t j);
};

#endif

#ifdef Lambdab_cxx
Lambdab::Lambdab(TString filename) : fChain(0) 
{
  TFile *f = TFile::Open(filename);
  bool isMC = filename.Contains("MC");
  TTree* tree = (TTree*)(isMC?f->Get("Lambdab2Jpsippi_TupleMC/DecayTree"):f->Get("BetaSLambdab2JpsippiDetachedLine_Tuple/DecayTree"));
  std::cout << tree << std::endl ;	
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

   fChain->SetBranchAddress("B_MINIP", &B_MINIP, &b_B_MINIP);
   fChain->SetBranchAddress("B_MINIPCHI2", &B_MINIPCHI2, &b_B_MINIPCHI2);
   fChain->SetBranchAddress("B_MINIPNEXTBEST", &B_MINIPNEXTBEST, &b_B_MINIPNEXTBEST);
   fChain->SetBranchAddress("B_MINIPCHI2NEXTBEST", &B_MINIPCHI2NEXTBEST, &b_B_MINIPCHI2NEXTBEST);
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
   fChain->SetBranchAddress("B_BKGCAT", &B_BKGCAT, &b_B_BKGCAT);
   fChain->SetBranchAddress("B_TRUEID", &B_TRUEID, &b_B_TRUEID);
   fChain->SetBranchAddress("B_MC_MOTHER_ID", &B_MC_MOTHER_ID, &b_B_MC_MOTHER_ID);
   fChain->SetBranchAddress("B_MC_MOTHER_KEY", &B_MC_MOTHER_KEY, &b_B_MC_MOTHER_KEY);
   fChain->SetBranchAddress("B_MC_GD_MOTHER_ID", &B_MC_GD_MOTHER_ID, &b_B_MC_GD_MOTHER_ID);
   fChain->SetBranchAddress("B_MC_GD_MOTHER_KEY", &B_MC_GD_MOTHER_KEY, &b_B_MC_GD_MOTHER_KEY);
   fChain->SetBranchAddress("B_MC_GD_GD_MOTHER_ID", &B_MC_GD_GD_MOTHER_ID, &b_B_MC_GD_GD_MOTHER_ID);
   fChain->SetBranchAddress("B_MC_GD_GD_MOTHER_KEY", &B_MC_GD_GD_MOTHER_KEY, &b_B_MC_GD_GD_MOTHER_KEY);
   fChain->SetBranchAddress("B_TRUEP_E", &B_TRUEP_E, &b_B_TRUEP_E);
   fChain->SetBranchAddress("B_TRUEP_X", &B_TRUEP_X, &b_B_TRUEP_X);
   fChain->SetBranchAddress("B_TRUEP_Y", &B_TRUEP_Y, &b_B_TRUEP_Y);
   fChain->SetBranchAddress("B_TRUEP_Z", &B_TRUEP_Z, &b_B_TRUEP_Z);
   fChain->SetBranchAddress("B_TRUEPT", &B_TRUEPT, &b_B_TRUEPT);
   fChain->SetBranchAddress("B_TRUEORIGINVERTEX_X", &B_TRUEORIGINVERTEX_X, &b_B_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("B_TRUEORIGINVERTEX_Y", &B_TRUEORIGINVERTEX_Y, &b_B_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("B_TRUEORIGINVERTEX_Z", &B_TRUEORIGINVERTEX_Z, &b_B_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("B_TRUEENDVERTEX_X", &B_TRUEENDVERTEX_X, &b_B_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("B_TRUEENDVERTEX_Y", &B_TRUEENDVERTEX_Y, &b_B_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("B_TRUEENDVERTEX_Z", &B_TRUEENDVERTEX_Z, &b_B_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("B_TRUEISSTABLE", &B_TRUEISSTABLE, &b_B_TRUEISSTABLE);
   fChain->SetBranchAddress("B_TRUETAU", &B_TRUETAU, &b_B_TRUETAU);
   fChain->SetBranchAddress("B_OSCIL", &B_OSCIL, &b_B_OSCIL);
   fChain->SetBranchAddress("B_ID", &B_ID, &b_B_ID);
   fChain->SetBranchAddress("B_TAU", &B_TAU, &b_B_TAU);
   fChain->SetBranchAddress("B_TAUERR", &B_TAUERR, &b_B_TAUERR);
   fChain->SetBranchAddress("B_TAUCHI2", &B_TAUCHI2, &b_B_TAUCHI2);
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
   fChain->SetBranchAddress("B_FullFit_chi2_B", B_FullFit_chi2_B, &b_B_FullFit_chi2_B);
   fChain->SetBranchAddress("B_FullFit_chi2", B_FullFit_chi2, &b_B_FullFit_chi2);
   fChain->SetBranchAddress("B_FullFit_ctau", B_FullFit_ctau, &b_B_FullFit_ctau);
   fChain->SetBranchAddress("B_FullFit_ctauErr", B_FullFit_ctauErr, &b_B_FullFit_ctauErr);
   fChain->SetBranchAddress("B_FullFit_decayLength", B_FullFit_decayLength, &b_B_FullFit_decayLength);
   fChain->SetBranchAddress("B_FullFit_decayLengthErr", B_FullFit_decayLengthErr, &b_B_FullFit_decayLengthErr);
   fChain->SetBranchAddress("B_FullFit_nDOF", B_FullFit_nDOF, &b_B_FullFit_nDOF);
   fChain->SetBranchAddress("B_FullFit_nIter", B_FullFit_nIter, &b_B_FullFit_nIter);
   fChain->SetBranchAddress("B_FullFit_status", B_FullFit_status, &b_B_FullFit_status);
   fChain->SetBranchAddress("B_MassFit_nPV", &B_MassFit_nPV, &b_B_MassFit_nPV);
   fChain->SetBranchAddress("B_MassFit_J_psi_1S_M", B_MassFit_J_psi_1S_M, &b_B_MassFit_J_psi_1S_M);
   fChain->SetBranchAddress("B_MassFit_J_psi_1S_MERR", B_MassFit_J_psi_1S_MERR, &b_B_MassFit_J_psi_1S_MERR);
   fChain->SetBranchAddress("B_MassFit_J_psi_1S_P", B_MassFit_J_psi_1S_P, &b_B_MassFit_J_psi_1S_P);
   fChain->SetBranchAddress("B_MassFit_J_psi_1S_PERR", B_MassFit_J_psi_1S_PERR, &b_B_MassFit_J_psi_1S_PERR);
   fChain->SetBranchAddress("B_MassFit_J_psi_1S_ctau", B_MassFit_J_psi_1S_ctau, &b_B_MassFit_J_psi_1S_ctau);
   fChain->SetBranchAddress("B_MassFit_J_psi_1S_ctauErr", B_MassFit_J_psi_1S_ctauErr, &b_B_MassFit_J_psi_1S_ctauErr);
   fChain->SetBranchAddress("B_MassFit_J_psi_1S_decayLength", B_MassFit_J_psi_1S_decayLength, &b_B_MassFit_J_psi_1S_decayLength);
   fChain->SetBranchAddress("B_MassFit_J_psi_1S_decayLengthErr", B_MassFit_J_psi_1S_decayLengthErr, &b_B_MassFit_J_psi_1S_decayLengthErr);
   fChain->SetBranchAddress("B_MassFit_M", B_MassFit_M, &b_B_MassFit_M);
   fChain->SetBranchAddress("B_MassFit_MERR", B_MassFit_MERR, &b_B_MassFit_MERR);
   fChain->SetBranchAddress("B_MassFit_P", B_MassFit_P, &b_B_MassFit_P);
   fChain->SetBranchAddress("B_MassFit_PERR", B_MassFit_PERR, &b_B_MassFit_PERR);
   fChain->SetBranchAddress("B_MassFit_chi2_B", B_MassFit_chi2_B, &b_B_MassFit_chi2_B);
   fChain->SetBranchAddress("B_MassFit_nDOF", B_MassFit_nDOF, &b_B_MassFit_nDOF);
   fChain->SetBranchAddress("B_MassFit_nIter", B_MassFit_nIter, &b_B_MassFit_nIter);
   fChain->SetBranchAddress("B_MassFit_status", B_MassFit_status, &b_B_MassFit_status);
   fChain->SetBranchAddress("B_SubKpi_nPV", &B_SubKpi_nPV, &b_B_SubKpi_nPV);
   fChain->SetBranchAddress("B_SubKpi_J_psi_1S_M", B_SubKpi_J_psi_1S_M, &b_B_SubKpi_J_psi_1S_M);
   fChain->SetBranchAddress("B_SubKpi_J_psi_1S_MERR", B_SubKpi_J_psi_1S_MERR, &b_B_SubKpi_J_psi_1S_MERR);
   fChain->SetBranchAddress("B_SubKpi_J_psi_1S_P", B_SubKpi_J_psi_1S_P, &b_B_SubKpi_J_psi_1S_P);
   fChain->SetBranchAddress("B_SubKpi_J_psi_1S_PERR", B_SubKpi_J_psi_1S_PERR, &b_B_SubKpi_J_psi_1S_PERR);
   fChain->SetBranchAddress("B_SubKpi_J_psi_1S_ctau", B_SubKpi_J_psi_1S_ctau, &b_B_SubKpi_J_psi_1S_ctau);
   fChain->SetBranchAddress("B_SubKpi_J_psi_1S_ctauErr", B_SubKpi_J_psi_1S_ctauErr, &b_B_SubKpi_J_psi_1S_ctauErr);
   fChain->SetBranchAddress("B_SubKpi_J_psi_1S_decayLength", B_SubKpi_J_psi_1S_decayLength, &b_B_SubKpi_J_psi_1S_decayLength);
   fChain->SetBranchAddress("B_SubKpi_J_psi_1S_decayLengthErr", B_SubKpi_J_psi_1S_decayLengthErr, &b_B_SubKpi_J_psi_1S_decayLengthErr);
   fChain->SetBranchAddress("B_SubKpi_M", B_SubKpi_M, &b_B_SubKpi_M);
   fChain->SetBranchAddress("B_SubKpi_MERR", B_SubKpi_MERR, &b_B_SubKpi_MERR);
   fChain->SetBranchAddress("B_SubKpi_P", B_SubKpi_P, &b_B_SubKpi_P);
   fChain->SetBranchAddress("B_SubKpi_PERR", B_SubKpi_PERR, &b_B_SubKpi_PERR);
   fChain->SetBranchAddress("B_SubKpi_PV_X", B_SubKpi_PV_X, &b_B_SubKpi_PV_X);
   fChain->SetBranchAddress("B_SubKpi_PV_Y", B_SubKpi_PV_Y, &b_B_SubKpi_PV_Y);
   fChain->SetBranchAddress("B_SubKpi_PV_Z", B_SubKpi_PV_Z, &b_B_SubKpi_PV_Z);
   fChain->SetBranchAddress("B_SubKpi_PV_key", B_SubKpi_PV_key, &b_B_SubKpi_PV_key);
   fChain->SetBranchAddress("B_SubKpi_chi2_B", B_SubKpi_chi2_B, &b_B_SubKpi_chi2_B);
   fChain->SetBranchAddress("B_SubKpi_ctau", B_SubKpi_ctau, &b_B_SubKpi_ctau);
   fChain->SetBranchAddress("B_SubKpi_ctauErr", B_SubKpi_ctauErr, &b_B_SubKpi_ctauErr);
   fChain->SetBranchAddress("B_SubKpi_decayLength", B_SubKpi_decayLength, &b_B_SubKpi_decayLength);
   fChain->SetBranchAddress("B_SubKpi_decayLengthErr", B_SubKpi_decayLengthErr, &b_B_SubKpi_decayLengthErr);
   fChain->SetBranchAddress("B_SubKpi_nDOF", B_SubKpi_nDOF, &b_B_SubKpi_nDOF);
   fChain->SetBranchAddress("B_SubKpi_nIter", B_SubKpi_nIter, &b_B_SubKpi_nIter);
   fChain->SetBranchAddress("B_SubKpi_status", B_SubKpi_status, &b_B_SubKpi_status);
   fChain->SetBranchAddress("B_SubpK_nPV", &B_SubpK_nPV, &b_B_SubpK_nPV);
   fChain->SetBranchAddress("B_SubpK_J_psi_1S_M", B_SubpK_J_psi_1S_M, &b_B_SubpK_J_psi_1S_M);
   fChain->SetBranchAddress("B_SubpK_J_psi_1S_MERR", B_SubpK_J_psi_1S_MERR, &b_B_SubpK_J_psi_1S_MERR);
   fChain->SetBranchAddress("B_SubpK_J_psi_1S_P", B_SubpK_J_psi_1S_P, &b_B_SubpK_J_psi_1S_P);
   fChain->SetBranchAddress("B_SubpK_J_psi_1S_PERR", B_SubpK_J_psi_1S_PERR, &b_B_SubpK_J_psi_1S_PERR);
   fChain->SetBranchAddress("B_SubpK_J_psi_1S_ctau", B_SubpK_J_psi_1S_ctau, &b_B_SubpK_J_psi_1S_ctau);
   fChain->SetBranchAddress("B_SubpK_J_psi_1S_ctauErr", B_SubpK_J_psi_1S_ctauErr, &b_B_SubpK_J_psi_1S_ctauErr);
   fChain->SetBranchAddress("B_SubpK_J_psi_1S_decayLength", B_SubpK_J_psi_1S_decayLength, &b_B_SubpK_J_psi_1S_decayLength);
   fChain->SetBranchAddress("B_SubpK_J_psi_1S_decayLengthErr", B_SubpK_J_psi_1S_decayLengthErr, &b_B_SubpK_J_psi_1S_decayLengthErr);
   fChain->SetBranchAddress("B_SubpK_M", B_SubpK_M, &b_B_SubpK_M);
   fChain->SetBranchAddress("B_SubpK_MERR", B_SubpK_MERR, &b_B_SubpK_MERR);
   fChain->SetBranchAddress("B_SubpK_P", B_SubpK_P, &b_B_SubpK_P);
   fChain->SetBranchAddress("B_SubpK_PERR", B_SubpK_PERR, &b_B_SubpK_PERR);
   fChain->SetBranchAddress("B_SubpK_PV_X", B_SubpK_PV_X, &b_B_SubpK_PV_X);
   fChain->SetBranchAddress("B_SubpK_PV_Y", B_SubpK_PV_Y, &b_B_SubpK_PV_Y);
   fChain->SetBranchAddress("B_SubpK_PV_Z", B_SubpK_PV_Z, &b_B_SubpK_PV_Z);
   fChain->SetBranchAddress("B_SubpK_PV_key", B_SubpK_PV_key, &b_B_SubpK_PV_key);
   fChain->SetBranchAddress("B_SubpK_chi2_B", B_SubpK_chi2_B, &b_B_SubpK_chi2_B);
   fChain->SetBranchAddress("B_SubpK_ctau", B_SubpK_ctau, &b_B_SubpK_ctau);
   fChain->SetBranchAddress("B_SubpK_ctauErr", B_SubpK_ctauErr, &b_B_SubpK_ctauErr);
   fChain->SetBranchAddress("B_SubpK_decayLength", B_SubpK_decayLength, &b_B_SubpK_decayLength);
   fChain->SetBranchAddress("B_SubpK_decayLengthErr", B_SubpK_decayLengthErr, &b_B_SubpK_decayLengthErr);
   fChain->SetBranchAddress("B_SubpK_nDOF", B_SubpK_nDOF, &b_B_SubpK_nDOF);
   fChain->SetBranchAddress("B_SubpK_nIter", B_SubpK_nIter, &b_B_SubpK_nIter);
   fChain->SetBranchAddress("B_SubpK_status", B_SubpK_status, &b_B_SubpK_status);
   fChain->SetBranchAddress("BL0Global_Dec", &BL0Global_Dec, &b_BL0Global_Dec);
   fChain->SetBranchAddress("BL0Global_TIS", &BL0Global_TIS, &b_BL0Global_TIS);
   fChain->SetBranchAddress("BL0Global_TOS", &BL0Global_TOS, &b_BL0Global_TOS);
   fChain->SetBranchAddress("BHlt1Global_Dec", &BHlt1Global_Dec, &b_BHlt1Global_Dec);
   fChain->SetBranchAddress("BHlt1Global_TIS", &BHlt1Global_TIS, &b_BHlt1Global_TIS);
   fChain->SetBranchAddress("BHlt1Global_TOS", &BHlt1Global_TOS, &b_BHlt1Global_TOS);
   fChain->SetBranchAddress("BHlt1Phys_Dec", &BHlt1Phys_Dec, &b_BHlt1Phys_Dec);
   fChain->SetBranchAddress("BHlt1Phys_TIS", &BHlt1Phys_TIS, &b_BHlt1Phys_TIS);
   fChain->SetBranchAddress("BHlt1Phys_TOS", &BHlt1Phys_TOS, &b_BHlt1Phys_TOS);
   fChain->SetBranchAddress("BHlt2Global_Dec", &BHlt2Global_Dec, &b_BHlt2Global_Dec);
   fChain->SetBranchAddress("BHlt2Global_TIS", &BHlt2Global_TIS, &b_BHlt2Global_TIS);
   fChain->SetBranchAddress("BHlt2Global_TOS", &BHlt2Global_TOS, &b_BHlt2Global_TOS);
   fChain->SetBranchAddress("BHlt2Phys_Dec", &BHlt2Phys_Dec, &b_BHlt2Phys_Dec);
   fChain->SetBranchAddress("BHlt2Phys_TIS", &BHlt2Phys_TIS, &b_BHlt2Phys_TIS);
   fChain->SetBranchAddress("BHlt2Phys_TOS", &BHlt2Phys_TOS, &b_BHlt2Phys_TOS);
   fChain->SetBranchAddress("BStrippingGlobal_Dec", &BStrippingGlobal_Dec, &b_BStrippingGlobal_Dec);
   fChain->SetBranchAddress("BStrippingGlobal_TIS", &BStrippingGlobal_TIS, &b_BStrippingGlobal_TIS);
   fChain->SetBranchAddress("BStrippingGlobal_TOS", &BStrippingGlobal_TOS, &b_BStrippingGlobal_TOS);
   fChain->SetBranchAddress("BL0HadronDecision_Dec", &BL0HadronDecision_Dec, &b_BL0HadronDecision_Dec);
   fChain->SetBranchAddress("BL0HadronDecision_TIS", &BL0HadronDecision_TIS, &b_BL0HadronDecision_TIS);
   fChain->SetBranchAddress("BL0HadronDecision_TOS", &BL0HadronDecision_TOS, &b_BL0HadronDecision_TOS);
   fChain->SetBranchAddress("BL0MuonDecision_Dec", &BL0MuonDecision_Dec, &b_BL0MuonDecision_Dec);
   fChain->SetBranchAddress("BL0MuonDecision_TIS", &BL0MuonDecision_TIS, &b_BL0MuonDecision_TIS);
   fChain->SetBranchAddress("BL0MuonDecision_TOS", &BL0MuonDecision_TOS, &b_BL0MuonDecision_TOS);
   fChain->SetBranchAddress("BL0DiMuonDecision_Dec", &BL0DiMuonDecision_Dec, &b_BL0DiMuonDecision_Dec);
   fChain->SetBranchAddress("BL0DiMuonDecision_TIS", &BL0DiMuonDecision_TIS, &b_BL0DiMuonDecision_TIS);
   fChain->SetBranchAddress("BL0DiMuonDecision_TOS", &BL0DiMuonDecision_TOS, &b_BL0DiMuonDecision_TOS);
   fChain->SetBranchAddress("BL0ElectronDecision_Dec", &BL0ElectronDecision_Dec, &b_BL0ElectronDecision_Dec);
   fChain->SetBranchAddress("BL0ElectronDecision_TIS", &BL0ElectronDecision_TIS, &b_BL0ElectronDecision_TIS);
   fChain->SetBranchAddress("BL0ElectronDecision_TOS", &BL0ElectronDecision_TOS, &b_BL0ElectronDecision_TOS);
   fChain->SetBranchAddress("BL0PhotonDecision_Dec", &BL0PhotonDecision_Dec, &b_BL0PhotonDecision_Dec);
   fChain->SetBranchAddress("BL0PhotonDecision_TIS", &BL0PhotonDecision_TIS, &b_BL0PhotonDecision_TIS);
   fChain->SetBranchAddress("BL0PhotonDecision_TOS", &BL0PhotonDecision_TOS, &b_BL0PhotonDecision_TOS);
   fChain->SetBranchAddress("BHlt1TrackAllL0Decision_Dec", &BHlt1TrackAllL0Decision_Dec, &b_BHlt1TrackAllL0Decision_Dec);
   fChain->SetBranchAddress("BHlt1TrackAllL0Decision_TIS", &BHlt1TrackAllL0Decision_TIS, &b_BHlt1TrackAllL0Decision_TIS);
   fChain->SetBranchAddress("BHlt1TrackAllL0Decision_TOS", &BHlt1TrackAllL0Decision_TOS, &b_BHlt1TrackAllL0Decision_TOS);
   fChain->SetBranchAddress("BHlt1DiMuonHighMassDecision_Dec", &BHlt1DiMuonHighMassDecision_Dec, &b_BHlt1DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("BHlt1DiMuonHighMassDecision_TIS", &BHlt1DiMuonHighMassDecision_TIS, &b_BHlt1DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("BHlt1DiMuonHighMassDecision_TOS", &BHlt1DiMuonHighMassDecision_TOS, &b_BHlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("BHlt1DiMuonLowMassDecision_Dec", &BHlt1DiMuonLowMassDecision_Dec, &b_BHlt1DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("BHlt1DiMuonLowMassDecision_TIS", &BHlt1DiMuonLowMassDecision_TIS, &b_BHlt1DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("BHlt1DiMuonLowMassDecision_TOS", &BHlt1DiMuonLowMassDecision_TOS, &b_BHlt1DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("BHlt1SingleMuonNoIPDecision_Dec", &BHlt1SingleMuonNoIPDecision_Dec, &b_BHlt1SingleMuonNoIPDecision_Dec);
   fChain->SetBranchAddress("BHlt1SingleMuonNoIPDecision_TIS", &BHlt1SingleMuonNoIPDecision_TIS, &b_BHlt1SingleMuonNoIPDecision_TIS);
   fChain->SetBranchAddress("BHlt1SingleMuonNoIPDecision_TOS", &BHlt1SingleMuonNoIPDecision_TOS, &b_BHlt1SingleMuonNoIPDecision_TOS);
   fChain->SetBranchAddress("BHlt1SingleMuonHighPTDecision_Dec", &BHlt1SingleMuonHighPTDecision_Dec, &b_BHlt1SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("BHlt1SingleMuonHighPTDecision_TIS", &BHlt1SingleMuonHighPTDecision_TIS, &b_BHlt1SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("BHlt1SingleMuonHighPTDecision_TOS", &BHlt1SingleMuonHighPTDecision_TOS, &b_BHlt1SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("BHlt1TrackMuonDecision_Dec", &BHlt1TrackMuonDecision_Dec, &b_BHlt1TrackMuonDecision_Dec);
   fChain->SetBranchAddress("BHlt1TrackMuonDecision_TIS", &BHlt1TrackMuonDecision_TIS, &b_BHlt1TrackMuonDecision_TIS);
   fChain->SetBranchAddress("BHlt1TrackMuonDecision_TOS", &BHlt1TrackMuonDecision_TOS, &b_BHlt1TrackMuonDecision_TOS);
   fChain->SetBranchAddress("BHlt2TransparentDecision_Dec", &BHlt2TransparentDecision_Dec, &b_BHlt2TransparentDecision_Dec);
   fChain->SetBranchAddress("BHlt2TransparentDecision_TIS", &BHlt2TransparentDecision_TIS, &b_BHlt2TransparentDecision_TIS);
   fChain->SetBranchAddress("BHlt2TransparentDecision_TOS", &BHlt2TransparentDecision_TOS, &b_BHlt2TransparentDecision_TOS);
   fChain->SetBranchAddress("BHlt2Topo2BodySimpleDecision_Dec", &BHlt2Topo2BodySimpleDecision_Dec, &b_BHlt2Topo2BodySimpleDecision_Dec);
   fChain->SetBranchAddress("BHlt2Topo2BodySimpleDecision_TIS", &BHlt2Topo2BodySimpleDecision_TIS, &b_BHlt2Topo2BodySimpleDecision_TIS);
   fChain->SetBranchAddress("BHlt2Topo2BodySimpleDecision_TOS", &BHlt2Topo2BodySimpleDecision_TOS, &b_BHlt2Topo2BodySimpleDecision_TOS);
   fChain->SetBranchAddress("BHlt2Topo3BodySimpleDecision_Dec", &BHlt2Topo3BodySimpleDecision_Dec, &b_BHlt2Topo3BodySimpleDecision_Dec);
   fChain->SetBranchAddress("BHlt2Topo3BodySimpleDecision_TIS", &BHlt2Topo3BodySimpleDecision_TIS, &b_BHlt2Topo3BodySimpleDecision_TIS);
   fChain->SetBranchAddress("BHlt2Topo3BodySimpleDecision_TOS", &BHlt2Topo3BodySimpleDecision_TOS, &b_BHlt2Topo3BodySimpleDecision_TOS);
   fChain->SetBranchAddress("BHlt2Topo4BodySimpleDecision_Dec", &BHlt2Topo4BodySimpleDecision_Dec, &b_BHlt2Topo4BodySimpleDecision_Dec);
   fChain->SetBranchAddress("BHlt2Topo4BodySimpleDecision_TIS", &BHlt2Topo4BodySimpleDecision_TIS, &b_BHlt2Topo4BodySimpleDecision_TIS);
   fChain->SetBranchAddress("BHlt2Topo4BodySimpleDecision_TOS", &BHlt2Topo4BodySimpleDecision_TOS, &b_BHlt2Topo4BodySimpleDecision_TOS);
   fChain->SetBranchAddress("BHlt2Topo2BodyBBDTDecision_Dec", &BHlt2Topo2BodyBBDTDecision_Dec, &b_BHlt2Topo2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("BHlt2Topo2BodyBBDTDecision_TIS", &BHlt2Topo2BodyBBDTDecision_TIS, &b_BHlt2Topo2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("BHlt2Topo2BodyBBDTDecision_TOS", &BHlt2Topo2BodyBBDTDecision_TOS, &b_BHlt2Topo2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("BHlt2Topo3BodyBBDTDecision_Dec", &BHlt2Topo3BodyBBDTDecision_Dec, &b_BHlt2Topo3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("BHlt2Topo3BodyBBDTDecision_TIS", &BHlt2Topo3BodyBBDTDecision_TIS, &b_BHlt2Topo3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("BHlt2Topo3BodyBBDTDecision_TOS", &BHlt2Topo3BodyBBDTDecision_TOS, &b_BHlt2Topo3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("BHlt2Topo4BodyBBDTDecision_Dec", &BHlt2Topo4BodyBBDTDecision_Dec, &b_BHlt2Topo4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("BHlt2Topo4BodyBBDTDecision_TIS", &BHlt2Topo4BodyBBDTDecision_TIS, &b_BHlt2Topo4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("BHlt2Topo4BodyBBDTDecision_TOS", &BHlt2Topo4BodyBBDTDecision_TOS, &b_BHlt2Topo4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("BHlt2SingleMuonDecision_Dec", &BHlt2SingleMuonDecision_Dec, &b_BHlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("BHlt2SingleMuonDecision_TIS", &BHlt2SingleMuonDecision_TIS, &b_BHlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("BHlt2SingleMuonDecision_TOS", &BHlt2SingleMuonDecision_TOS, &b_BHlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("BHlt2SingleMuonHighPTDecision_Dec", &BHlt2SingleMuonHighPTDecision_Dec, &b_BHlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("BHlt2SingleMuonHighPTDecision_TIS", &BHlt2SingleMuonHighPTDecision_TIS, &b_BHlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("BHlt2SingleMuonHighPTDecision_TOS", &BHlt2SingleMuonHighPTDecision_TOS, &b_BHlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("BHlt2SingleMuonLowPTDecision_Dec", &BHlt2SingleMuonLowPTDecision_Dec, &b_BHlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("BHlt2SingleMuonLowPTDecision_TIS", &BHlt2SingleMuonLowPTDecision_TIS, &b_BHlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("BHlt2SingleMuonLowPTDecision_TOS", &BHlt2SingleMuonLowPTDecision_TOS, &b_BHlt2SingleMuonLowPTDecision_TOS);
   fChain->SetBranchAddress("BHlt2TopoMu2BodyBBDTDecision_Dec", &BHlt2TopoMu2BodyBBDTDecision_Dec, &b_BHlt2TopoMu2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("BHlt2TopoMu2BodyBBDTDecision_TIS", &BHlt2TopoMu2BodyBBDTDecision_TIS, &b_BHlt2TopoMu2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("BHlt2TopoMu2BodyBBDTDecision_TOS", &BHlt2TopoMu2BodyBBDTDecision_TOS, &b_BHlt2TopoMu2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("BHlt2TopoMu3BodyBBDTDecision_Dec", &BHlt2TopoMu3BodyBBDTDecision_Dec, &b_BHlt2TopoMu3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("BHlt2TopoMu3BodyBBDTDecision_TIS", &BHlt2TopoMu3BodyBBDTDecision_TIS, &b_BHlt2TopoMu3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("BHlt2TopoMu3BodyBBDTDecision_TOS", &BHlt2TopoMu3BodyBBDTDecision_TOS, &b_BHlt2TopoMu3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("BHlt2TopoMu4BodyBBDTDecision_Dec", &BHlt2TopoMu4BodyBBDTDecision_Dec, &b_BHlt2TopoMu4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("BHlt2TopoMu4BodyBBDTDecision_TIS", &BHlt2TopoMu4BodyBBDTDecision_TIS, &b_BHlt2TopoMu4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("BHlt2TopoMu4BodyBBDTDecision_TOS", &BHlt2TopoMu4BodyBBDTDecision_TOS, &b_BHlt2TopoMu4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("BHlt2MuonFromHLT1Decision_Dec", &BHlt2MuonFromHLT1Decision_Dec, &b_BHlt2MuonFromHLT1Decision_Dec);
   fChain->SetBranchAddress("BHlt2MuonFromHLT1Decision_TIS", &BHlt2MuonFromHLT1Decision_TIS, &b_BHlt2MuonFromHLT1Decision_TIS);
   fChain->SetBranchAddress("BHlt2MuonFromHLT1Decision_TOS", &BHlt2MuonFromHLT1Decision_TOS, &b_BHlt2MuonFromHLT1Decision_TOS);
   fChain->SetBranchAddress("BHlt2DiMuonDecision_Dec", &BHlt2DiMuonDecision_Dec, &b_BHlt2DiMuonDecision_Dec);
   fChain->SetBranchAddress("BHlt2DiMuonDecision_TIS", &BHlt2DiMuonDecision_TIS, &b_BHlt2DiMuonDecision_TIS);
   fChain->SetBranchAddress("BHlt2DiMuonDecision_TOS", &BHlt2DiMuonDecision_TOS, &b_BHlt2DiMuonDecision_TOS);
   fChain->SetBranchAddress("BHlt2DiMuonLowMassDecision_Dec", &BHlt2DiMuonLowMassDecision_Dec, &b_BHlt2DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("BHlt2DiMuonLowMassDecision_TIS", &BHlt2DiMuonLowMassDecision_TIS, &b_BHlt2DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("BHlt2DiMuonLowMassDecision_TOS", &BHlt2DiMuonLowMassDecision_TOS, &b_BHlt2DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("BHlt2DiMuonJPsiDecision_Dec", &BHlt2DiMuonJPsiDecision_Dec, &b_BHlt2DiMuonJPsiDecision_Dec);
   fChain->SetBranchAddress("BHlt2DiMuonJPsiDecision_TIS", &BHlt2DiMuonJPsiDecision_TIS, &b_BHlt2DiMuonJPsiDecision_TIS);
   fChain->SetBranchAddress("BHlt2DiMuonJPsiDecision_TOS", &BHlt2DiMuonJPsiDecision_TOS, &b_BHlt2DiMuonJPsiDecision_TOS);
   fChain->SetBranchAddress("BHlt2DiMuonJPsiHighPTDecision_Dec", &BHlt2DiMuonJPsiHighPTDecision_Dec, &b_BHlt2DiMuonJPsiHighPTDecision_Dec);
   fChain->SetBranchAddress("BHlt2DiMuonJPsiHighPTDecision_TIS", &BHlt2DiMuonJPsiHighPTDecision_TIS, &b_BHlt2DiMuonJPsiHighPTDecision_TIS);
   fChain->SetBranchAddress("BHlt2DiMuonJPsiHighPTDecision_TOS", &BHlt2DiMuonJPsiHighPTDecision_TOS, &b_BHlt2DiMuonJPsiHighPTDecision_TOS);
   fChain->SetBranchAddress("BHlt2DiMuonPsi2SDecision_Dec", &BHlt2DiMuonPsi2SDecision_Dec, &b_BHlt2DiMuonPsi2SDecision_Dec);
   fChain->SetBranchAddress("BHlt2DiMuonPsi2SDecision_TIS", &BHlt2DiMuonPsi2SDecision_TIS, &b_BHlt2DiMuonPsi2SDecision_TIS);
   fChain->SetBranchAddress("BHlt2DiMuonPsi2SDecision_TOS", &BHlt2DiMuonPsi2SDecision_TOS, &b_BHlt2DiMuonPsi2SDecision_TOS);
   fChain->SetBranchAddress("BHlt2DiMuonPsi2SHighPTDecision_Dec", &BHlt2DiMuonPsi2SHighPTDecision_Dec, &b_BHlt2DiMuonPsi2SHighPTDecision_Dec);
   fChain->SetBranchAddress("BHlt2DiMuonPsi2SHighPTDecision_TIS", &BHlt2DiMuonPsi2SHighPTDecision_TIS, &b_BHlt2DiMuonPsi2SHighPTDecision_TIS);
   fChain->SetBranchAddress("BHlt2DiMuonPsi2SHighPTDecision_TOS", &BHlt2DiMuonPsi2SHighPTDecision_TOS, &b_BHlt2DiMuonPsi2SHighPTDecision_TOS);
   fChain->SetBranchAddress("BHlt2DiMuonBDecision_Dec", &BHlt2DiMuonBDecision_Dec, &b_BHlt2DiMuonBDecision_Dec);
   fChain->SetBranchAddress("BHlt2DiMuonBDecision_TIS", &BHlt2DiMuonBDecision_TIS, &b_BHlt2DiMuonBDecision_TIS);
   fChain->SetBranchAddress("BHlt2DiMuonBDecision_TOS", &BHlt2DiMuonBDecision_TOS, &b_BHlt2DiMuonBDecision_TOS);
   fChain->SetBranchAddress("BHlt2DiMuonDetachedDecision_Dec", &BHlt2DiMuonDetachedDecision_Dec, &b_BHlt2DiMuonDetachedDecision_Dec);
   fChain->SetBranchAddress("BHlt2DiMuonDetachedDecision_TIS", &BHlt2DiMuonDetachedDecision_TIS, &b_BHlt2DiMuonDetachedDecision_TIS);
   fChain->SetBranchAddress("BHlt2DiMuonDetachedDecision_TOS", &BHlt2DiMuonDetachedDecision_TOS, &b_BHlt2DiMuonDetachedDecision_TOS);
   fChain->SetBranchAddress("BHlt2DiMuonDetachedHeavyDecision_Dec", &BHlt2DiMuonDetachedHeavyDecision_Dec, &b_BHlt2DiMuonDetachedHeavyDecision_Dec);
   fChain->SetBranchAddress("BHlt2DiMuonDetachedHeavyDecision_TIS", &BHlt2DiMuonDetachedHeavyDecision_TIS, &b_BHlt2DiMuonDetachedHeavyDecision_TIS);
   fChain->SetBranchAddress("BHlt2DiMuonDetachedHeavyDecision_TOS", &BHlt2DiMuonDetachedHeavyDecision_TOS, &b_BHlt2DiMuonDetachedHeavyDecision_TOS);
   fChain->SetBranchAddress("BHlt2DiMuonDetachedJPsiDecision_Dec", &BHlt2DiMuonDetachedJPsiDecision_Dec, &b_BHlt2DiMuonDetachedJPsiDecision_Dec);
   fChain->SetBranchAddress("BHlt2DiMuonDetachedJPsiDecision_TIS", &BHlt2DiMuonDetachedJPsiDecision_TIS, &b_BHlt2DiMuonDetachedJPsiDecision_TIS);
   fChain->SetBranchAddress("BHlt2DiMuonDetachedJPsiDecision_TOS", &BHlt2DiMuonDetachedJPsiDecision_TOS, &b_BHlt2DiMuonDetachedJPsiDecision_TOS);
   fChain->SetBranchAddress("BHlt2ExpressJPsiDecision_Dec", &BHlt2ExpressJPsiDecision_Dec, &b_BHlt2ExpressJPsiDecision_Dec);
   fChain->SetBranchAddress("BHlt2ExpressJPsiDecision_TIS", &BHlt2ExpressJPsiDecision_TIS, &b_BHlt2ExpressJPsiDecision_TIS);
   fChain->SetBranchAddress("BHlt2ExpressJPsiDecision_TOS", &BHlt2ExpressJPsiDecision_TOS, &b_BHlt2ExpressJPsiDecision_TOS);
   fChain->SetBranchAddress("piminus_MINIP", &piminus_MINIP, &b_piminus_MINIP);
   fChain->SetBranchAddress("piminus_MINIPCHI2", &piminus_MINIPCHI2, &b_piminus_MINIPCHI2);
   fChain->SetBranchAddress("piminus_MINIPNEXTBEST", &piminus_MINIPNEXTBEST, &b_piminus_MINIPNEXTBEST);
   fChain->SetBranchAddress("piminus_MINIPCHI2NEXTBEST", &piminus_MINIPCHI2NEXTBEST, &b_piminus_MINIPCHI2NEXTBEST);
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
   fChain->SetBranchAddress("piminus_TRUEID", &piminus_TRUEID, &b_piminus_TRUEID);
   fChain->SetBranchAddress("piminus_MC_MOTHER_ID", &piminus_MC_MOTHER_ID, &b_piminus_MC_MOTHER_ID);
   fChain->SetBranchAddress("piminus_MC_MOTHER_KEY", &piminus_MC_MOTHER_KEY, &b_piminus_MC_MOTHER_KEY);
   fChain->SetBranchAddress("piminus_MC_GD_MOTHER_ID", &piminus_MC_GD_MOTHER_ID, &b_piminus_MC_GD_MOTHER_ID);
   fChain->SetBranchAddress("piminus_MC_GD_MOTHER_KEY", &piminus_MC_GD_MOTHER_KEY, &b_piminus_MC_GD_MOTHER_KEY);
   fChain->SetBranchAddress("piminus_MC_GD_GD_MOTHER_ID", &piminus_MC_GD_GD_MOTHER_ID, &b_piminus_MC_GD_GD_MOTHER_ID);
   fChain->SetBranchAddress("piminus_MC_GD_GD_MOTHER_KEY", &piminus_MC_GD_GD_MOTHER_KEY, &b_piminus_MC_GD_GD_MOTHER_KEY);
   fChain->SetBranchAddress("piminus_TRUEP_E", &piminus_TRUEP_E, &b_piminus_TRUEP_E);
   fChain->SetBranchAddress("piminus_TRUEP_X", &piminus_TRUEP_X, &b_piminus_TRUEP_X);
   fChain->SetBranchAddress("piminus_TRUEP_Y", &piminus_TRUEP_Y, &b_piminus_TRUEP_Y);
   fChain->SetBranchAddress("piminus_TRUEP_Z", &piminus_TRUEP_Z, &b_piminus_TRUEP_Z);
   fChain->SetBranchAddress("piminus_TRUEPT", &piminus_TRUEPT, &b_piminus_TRUEPT);
   fChain->SetBranchAddress("piminus_TRUEORIGINVERTEX_X", &piminus_TRUEORIGINVERTEX_X, &b_piminus_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("piminus_TRUEORIGINVERTEX_Y", &piminus_TRUEORIGINVERTEX_Y, &b_piminus_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("piminus_TRUEORIGINVERTEX_Z", &piminus_TRUEORIGINVERTEX_Z, &b_piminus_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("piminus_TRUEENDVERTEX_X", &piminus_TRUEENDVERTEX_X, &b_piminus_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("piminus_TRUEENDVERTEX_Y", &piminus_TRUEENDVERTEX_Y, &b_piminus_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("piminus_TRUEENDVERTEX_Z", &piminus_TRUEENDVERTEX_Z, &b_piminus_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("piminus_TRUEISSTABLE", &piminus_TRUEISSTABLE, &b_piminus_TRUEISSTABLE);
   fChain->SetBranchAddress("piminus_TRUETAU", &piminus_TRUETAU, &b_piminus_TRUETAU);
   fChain->SetBranchAddress("piminus_OSCIL", &piminus_OSCIL, &b_piminus_OSCIL);
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
   fChain->SetBranchAddress("piminus_TRACK_GhostProb", &piminus_TRACK_GhostProb, &b_piminus_TRACK_GhostProb);
   fChain->SetBranchAddress("piminus_TRACK_CloneDist", &piminus_TRACK_CloneDist, &b_piminus_TRACK_CloneDist);
   fChain->SetBranchAddress("pplus_MINIP", &pplus_MINIP, &b_pplus_MINIP);
   fChain->SetBranchAddress("pplus_MINIPCHI2", &pplus_MINIPCHI2, &b_pplus_MINIPCHI2);
   fChain->SetBranchAddress("pplus_MINIPNEXTBEST", &pplus_MINIPNEXTBEST, &b_pplus_MINIPNEXTBEST);
   fChain->SetBranchAddress("pplus_MINIPCHI2NEXTBEST", &pplus_MINIPCHI2NEXTBEST, &b_pplus_MINIPCHI2NEXTBEST);
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
   fChain->SetBranchAddress("pplus_TRUEID", &pplus_TRUEID, &b_pplus_TRUEID);
   fChain->SetBranchAddress("pplus_MC_MOTHER_ID", &pplus_MC_MOTHER_ID, &b_pplus_MC_MOTHER_ID);
   fChain->SetBranchAddress("pplus_MC_MOTHER_KEY", &pplus_MC_MOTHER_KEY, &b_pplus_MC_MOTHER_KEY);
   fChain->SetBranchAddress("pplus_MC_GD_MOTHER_ID", &pplus_MC_GD_MOTHER_ID, &b_pplus_MC_GD_MOTHER_ID);
   fChain->SetBranchAddress("pplus_MC_GD_MOTHER_KEY", &pplus_MC_GD_MOTHER_KEY, &b_pplus_MC_GD_MOTHER_KEY);
   fChain->SetBranchAddress("pplus_MC_GD_GD_MOTHER_ID", &pplus_MC_GD_GD_MOTHER_ID, &b_pplus_MC_GD_GD_MOTHER_ID);
   fChain->SetBranchAddress("pplus_MC_GD_GD_MOTHER_KEY", &pplus_MC_GD_GD_MOTHER_KEY, &b_pplus_MC_GD_GD_MOTHER_KEY);
   fChain->SetBranchAddress("pplus_TRUEP_E", &pplus_TRUEP_E, &b_pplus_TRUEP_E);
   fChain->SetBranchAddress("pplus_TRUEP_X", &pplus_TRUEP_X, &b_pplus_TRUEP_X);
   fChain->SetBranchAddress("pplus_TRUEP_Y", &pplus_TRUEP_Y, &b_pplus_TRUEP_Y);
   fChain->SetBranchAddress("pplus_TRUEP_Z", &pplus_TRUEP_Z, &b_pplus_TRUEP_Z);
   fChain->SetBranchAddress("pplus_TRUEPT", &pplus_TRUEPT, &b_pplus_TRUEPT);
   fChain->SetBranchAddress("pplus_TRUEORIGINVERTEX_X", &pplus_TRUEORIGINVERTEX_X, &b_pplus_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("pplus_TRUEORIGINVERTEX_Y", &pplus_TRUEORIGINVERTEX_Y, &b_pplus_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("pplus_TRUEORIGINVERTEX_Z", &pplus_TRUEORIGINVERTEX_Z, &b_pplus_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("pplus_TRUEENDVERTEX_X", &pplus_TRUEENDVERTEX_X, &b_pplus_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("pplus_TRUEENDVERTEX_Y", &pplus_TRUEENDVERTEX_Y, &b_pplus_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("pplus_TRUEENDVERTEX_Z", &pplus_TRUEENDVERTEX_Z, &b_pplus_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("pplus_TRUEISSTABLE", &pplus_TRUEISSTABLE, &b_pplus_TRUEISSTABLE);
   fChain->SetBranchAddress("pplus_TRUETAU", &pplus_TRUETAU, &b_pplus_TRUETAU);
   fChain->SetBranchAddress("pplus_OSCIL", &pplus_OSCIL, &b_pplus_OSCIL);
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
   fChain->SetBranchAddress("pplus_TRACK_GhostProb", &pplus_TRACK_GhostProb, &b_pplus_TRACK_GhostProb);
   fChain->SetBranchAddress("pplus_TRACK_CloneDist", &pplus_TRACK_CloneDist, &b_pplus_TRACK_CloneDist);
   fChain->SetBranchAddress("Psi_MINIP", &Psi_MINIP, &b_Psi_MINIP);
   fChain->SetBranchAddress("Psi_MINIPCHI2", &Psi_MINIPCHI2, &b_Psi_MINIPCHI2);
   fChain->SetBranchAddress("Psi_MINIPNEXTBEST", &Psi_MINIPNEXTBEST, &b_Psi_MINIPNEXTBEST);
   fChain->SetBranchAddress("Psi_MINIPCHI2NEXTBEST", &Psi_MINIPCHI2NEXTBEST, &b_Psi_MINIPCHI2NEXTBEST);
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
   fChain->SetBranchAddress("Psi_BKGCAT", &Psi_BKGCAT, &b_Psi_BKGCAT);
   fChain->SetBranchAddress("Psi_TRUEID", &Psi_TRUEID, &b_Psi_TRUEID);
   fChain->SetBranchAddress("Psi_MC_MOTHER_ID", &Psi_MC_MOTHER_ID, &b_Psi_MC_MOTHER_ID);
   fChain->SetBranchAddress("Psi_MC_MOTHER_KEY", &Psi_MC_MOTHER_KEY, &b_Psi_MC_MOTHER_KEY);
   fChain->SetBranchAddress("Psi_MC_GD_MOTHER_ID", &Psi_MC_GD_MOTHER_ID, &b_Psi_MC_GD_MOTHER_ID);
   fChain->SetBranchAddress("Psi_MC_GD_MOTHER_KEY", &Psi_MC_GD_MOTHER_KEY, &b_Psi_MC_GD_MOTHER_KEY);
   fChain->SetBranchAddress("Psi_MC_GD_GD_MOTHER_ID", &Psi_MC_GD_GD_MOTHER_ID, &b_Psi_MC_GD_GD_MOTHER_ID);
   fChain->SetBranchAddress("Psi_MC_GD_GD_MOTHER_KEY", &Psi_MC_GD_GD_MOTHER_KEY, &b_Psi_MC_GD_GD_MOTHER_KEY);
   fChain->SetBranchAddress("Psi_TRUEP_E", &Psi_TRUEP_E, &b_Psi_TRUEP_E);
   fChain->SetBranchAddress("Psi_TRUEP_X", &Psi_TRUEP_X, &b_Psi_TRUEP_X);
   fChain->SetBranchAddress("Psi_TRUEP_Y", &Psi_TRUEP_Y, &b_Psi_TRUEP_Y);
   fChain->SetBranchAddress("Psi_TRUEP_Z", &Psi_TRUEP_Z, &b_Psi_TRUEP_Z);
   fChain->SetBranchAddress("Psi_TRUEPT", &Psi_TRUEPT, &b_Psi_TRUEPT);
   fChain->SetBranchAddress("Psi_TRUEORIGINVERTEX_X", &Psi_TRUEORIGINVERTEX_X, &b_Psi_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("Psi_TRUEORIGINVERTEX_Y", &Psi_TRUEORIGINVERTEX_Y, &b_Psi_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("Psi_TRUEORIGINVERTEX_Z", &Psi_TRUEORIGINVERTEX_Z, &b_Psi_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("Psi_TRUEENDVERTEX_X", &Psi_TRUEENDVERTEX_X, &b_Psi_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("Psi_TRUEENDVERTEX_Y", &Psi_TRUEENDVERTEX_Y, &b_Psi_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("Psi_TRUEENDVERTEX_Z", &Psi_TRUEENDVERTEX_Z, &b_Psi_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("Psi_TRUEISSTABLE", &Psi_TRUEISSTABLE, &b_Psi_TRUEISSTABLE);
   fChain->SetBranchAddress("Psi_TRUETAU", &Psi_TRUETAU, &b_Psi_TRUETAU);
   fChain->SetBranchAddress("Psi_OSCIL", &Psi_OSCIL, &b_Psi_OSCIL);
   fChain->SetBranchAddress("Psi_ID", &Psi_ID, &b_Psi_ID);
   fChain->SetBranchAddress("Psi_TAU", &Psi_TAU, &b_Psi_TAU);
   fChain->SetBranchAddress("Psi_TAUERR", &Psi_TAUERR, &b_Psi_TAUERR);
   fChain->SetBranchAddress("Psi_TAUCHI2", &Psi_TAUCHI2, &b_Psi_TAUCHI2);
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
   fChain->SetBranchAddress("PsiStrippingGlobal_Dec", &PsiStrippingGlobal_Dec, &b_PsiStrippingGlobal_Dec);
   fChain->SetBranchAddress("PsiStrippingGlobal_TIS", &PsiStrippingGlobal_TIS, &b_PsiStrippingGlobal_TIS);
   fChain->SetBranchAddress("PsiStrippingGlobal_TOS", &PsiStrippingGlobal_TOS, &b_PsiStrippingGlobal_TOS);
   fChain->SetBranchAddress("PsiL0HadronDecision_Dec", &PsiL0HadronDecision_Dec, &b_PsiL0HadronDecision_Dec);
   fChain->SetBranchAddress("PsiL0HadronDecision_TIS", &PsiL0HadronDecision_TIS, &b_PsiL0HadronDecision_TIS);
   fChain->SetBranchAddress("PsiL0HadronDecision_TOS", &PsiL0HadronDecision_TOS, &b_PsiL0HadronDecision_TOS);
   fChain->SetBranchAddress("PsiL0MuonDecision_Dec", &PsiL0MuonDecision_Dec, &b_PsiL0MuonDecision_Dec);
   fChain->SetBranchAddress("PsiL0MuonDecision_TIS", &PsiL0MuonDecision_TIS, &b_PsiL0MuonDecision_TIS);
   fChain->SetBranchAddress("PsiL0MuonDecision_TOS", &PsiL0MuonDecision_TOS, &b_PsiL0MuonDecision_TOS);
   fChain->SetBranchAddress("PsiL0DiMuonDecision_Dec", &PsiL0DiMuonDecision_Dec, &b_PsiL0DiMuonDecision_Dec);
   fChain->SetBranchAddress("PsiL0DiMuonDecision_TIS", &PsiL0DiMuonDecision_TIS, &b_PsiL0DiMuonDecision_TIS);
   fChain->SetBranchAddress("PsiL0DiMuonDecision_TOS", &PsiL0DiMuonDecision_TOS, &b_PsiL0DiMuonDecision_TOS);
   fChain->SetBranchAddress("PsiL0ElectronDecision_Dec", &PsiL0ElectronDecision_Dec, &b_PsiL0ElectronDecision_Dec);
   fChain->SetBranchAddress("PsiL0ElectronDecision_TIS", &PsiL0ElectronDecision_TIS, &b_PsiL0ElectronDecision_TIS);
   fChain->SetBranchAddress("PsiL0ElectronDecision_TOS", &PsiL0ElectronDecision_TOS, &b_PsiL0ElectronDecision_TOS);
   fChain->SetBranchAddress("PsiL0PhotonDecision_Dec", &PsiL0PhotonDecision_Dec, &b_PsiL0PhotonDecision_Dec);
   fChain->SetBranchAddress("PsiL0PhotonDecision_TIS", &PsiL0PhotonDecision_TIS, &b_PsiL0PhotonDecision_TIS);
   fChain->SetBranchAddress("PsiL0PhotonDecision_TOS", &PsiL0PhotonDecision_TOS, &b_PsiL0PhotonDecision_TOS);
   fChain->SetBranchAddress("PsiHlt1TrackAllL0Decision_Dec", &PsiHlt1TrackAllL0Decision_Dec, &b_PsiHlt1TrackAllL0Decision_Dec);
   fChain->SetBranchAddress("PsiHlt1TrackAllL0Decision_TIS", &PsiHlt1TrackAllL0Decision_TIS, &b_PsiHlt1TrackAllL0Decision_TIS);
   fChain->SetBranchAddress("PsiHlt1TrackAllL0Decision_TOS", &PsiHlt1TrackAllL0Decision_TOS, &b_PsiHlt1TrackAllL0Decision_TOS);
   fChain->SetBranchAddress("PsiHlt1DiMuonHighMassDecision_Dec", &PsiHlt1DiMuonHighMassDecision_Dec, &b_PsiHlt1DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1DiMuonHighMassDecision_TIS", &PsiHlt1DiMuonHighMassDecision_TIS, &b_PsiHlt1DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1DiMuonHighMassDecision_TOS", &PsiHlt1DiMuonHighMassDecision_TOS, &b_PsiHlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("PsiHlt1DiMuonLowMassDecision_Dec", &PsiHlt1DiMuonLowMassDecision_Dec, &b_PsiHlt1DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1DiMuonLowMassDecision_TIS", &PsiHlt1DiMuonLowMassDecision_TIS, &b_PsiHlt1DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1DiMuonLowMassDecision_TOS", &PsiHlt1DiMuonLowMassDecision_TOS, &b_PsiHlt1DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("PsiHlt1SingleMuonNoIPDecision_Dec", &PsiHlt1SingleMuonNoIPDecision_Dec, &b_PsiHlt1SingleMuonNoIPDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1SingleMuonNoIPDecision_TIS", &PsiHlt1SingleMuonNoIPDecision_TIS, &b_PsiHlt1SingleMuonNoIPDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1SingleMuonNoIPDecision_TOS", &PsiHlt1SingleMuonNoIPDecision_TOS, &b_PsiHlt1SingleMuonNoIPDecision_TOS);
   fChain->SetBranchAddress("PsiHlt1SingleMuonHighPTDecision_Dec", &PsiHlt1SingleMuonHighPTDecision_Dec, &b_PsiHlt1SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1SingleMuonHighPTDecision_TIS", &PsiHlt1SingleMuonHighPTDecision_TIS, &b_PsiHlt1SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1SingleMuonHighPTDecision_TOS", &PsiHlt1SingleMuonHighPTDecision_TOS, &b_PsiHlt1SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt1TrackMuonDecision_Dec", &PsiHlt1TrackMuonDecision_Dec, &b_PsiHlt1TrackMuonDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1TrackMuonDecision_TIS", &PsiHlt1TrackMuonDecision_TIS, &b_PsiHlt1TrackMuonDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1TrackMuonDecision_TOS", &PsiHlt1TrackMuonDecision_TOS, &b_PsiHlt1TrackMuonDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2TransparentDecision_Dec", &PsiHlt2TransparentDecision_Dec, &b_PsiHlt2TransparentDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2TransparentDecision_TIS", &PsiHlt2TransparentDecision_TIS, &b_PsiHlt2TransparentDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2TransparentDecision_TOS", &PsiHlt2TransparentDecision_TOS, &b_PsiHlt2TransparentDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2Topo2BodySimpleDecision_Dec", &PsiHlt2Topo2BodySimpleDecision_Dec, &b_PsiHlt2Topo2BodySimpleDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2Topo2BodySimpleDecision_TIS", &PsiHlt2Topo2BodySimpleDecision_TIS, &b_PsiHlt2Topo2BodySimpleDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2Topo2BodySimpleDecision_TOS", &PsiHlt2Topo2BodySimpleDecision_TOS, &b_PsiHlt2Topo2BodySimpleDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2Topo3BodySimpleDecision_Dec", &PsiHlt2Topo3BodySimpleDecision_Dec, &b_PsiHlt2Topo3BodySimpleDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2Topo3BodySimpleDecision_TIS", &PsiHlt2Topo3BodySimpleDecision_TIS, &b_PsiHlt2Topo3BodySimpleDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2Topo3BodySimpleDecision_TOS", &PsiHlt2Topo3BodySimpleDecision_TOS, &b_PsiHlt2Topo3BodySimpleDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2Topo4BodySimpleDecision_Dec", &PsiHlt2Topo4BodySimpleDecision_Dec, &b_PsiHlt2Topo4BodySimpleDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2Topo4BodySimpleDecision_TIS", &PsiHlt2Topo4BodySimpleDecision_TIS, &b_PsiHlt2Topo4BodySimpleDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2Topo4BodySimpleDecision_TOS", &PsiHlt2Topo4BodySimpleDecision_TOS, &b_PsiHlt2Topo4BodySimpleDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2Topo2BodyBBDTDecision_Dec", &PsiHlt2Topo2BodyBBDTDecision_Dec, &b_PsiHlt2Topo2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2Topo2BodyBBDTDecision_TIS", &PsiHlt2Topo2BodyBBDTDecision_TIS, &b_PsiHlt2Topo2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2Topo2BodyBBDTDecision_TOS", &PsiHlt2Topo2BodyBBDTDecision_TOS, &b_PsiHlt2Topo2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2Topo3BodyBBDTDecision_Dec", &PsiHlt2Topo3BodyBBDTDecision_Dec, &b_PsiHlt2Topo3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2Topo3BodyBBDTDecision_TIS", &PsiHlt2Topo3BodyBBDTDecision_TIS, &b_PsiHlt2Topo3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2Topo3BodyBBDTDecision_TOS", &PsiHlt2Topo3BodyBBDTDecision_TOS, &b_PsiHlt2Topo3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2Topo4BodyBBDTDecision_Dec", &PsiHlt2Topo4BodyBBDTDecision_Dec, &b_PsiHlt2Topo4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2Topo4BodyBBDTDecision_TIS", &PsiHlt2Topo4BodyBBDTDecision_TIS, &b_PsiHlt2Topo4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2Topo4BodyBBDTDecision_TOS", &PsiHlt2Topo4BodyBBDTDecision_TOS, &b_PsiHlt2Topo4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonDecision_Dec", &PsiHlt2SingleMuonDecision_Dec, &b_PsiHlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2SingleMuonDecision_TIS", &PsiHlt2SingleMuonDecision_TIS, &b_PsiHlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonDecision_TOS", &PsiHlt2SingleMuonDecision_TOS, &b_PsiHlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonHighPTDecision_Dec", &PsiHlt2SingleMuonHighPTDecision_Dec, &b_PsiHlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2SingleMuonHighPTDecision_TIS", &PsiHlt2SingleMuonHighPTDecision_TIS, &b_PsiHlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonHighPTDecision_TOS", &PsiHlt2SingleMuonHighPTDecision_TOS, &b_PsiHlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonLowPTDecision_Dec", &PsiHlt2SingleMuonLowPTDecision_Dec, &b_PsiHlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2SingleMuonLowPTDecision_TIS", &PsiHlt2SingleMuonLowPTDecision_TIS, &b_PsiHlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonLowPTDecision_TOS", &PsiHlt2SingleMuonLowPTDecision_TOS, &b_PsiHlt2SingleMuonLowPTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2TopoMu2BodyBBDTDecision_Dec", &PsiHlt2TopoMu2BodyBBDTDecision_Dec, &b_PsiHlt2TopoMu2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2TopoMu2BodyBBDTDecision_TIS", &PsiHlt2TopoMu2BodyBBDTDecision_TIS, &b_PsiHlt2TopoMu2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2TopoMu2BodyBBDTDecision_TOS", &PsiHlt2TopoMu2BodyBBDTDecision_TOS, &b_PsiHlt2TopoMu2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2TopoMu3BodyBBDTDecision_Dec", &PsiHlt2TopoMu3BodyBBDTDecision_Dec, &b_PsiHlt2TopoMu3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2TopoMu3BodyBBDTDecision_TIS", &PsiHlt2TopoMu3BodyBBDTDecision_TIS, &b_PsiHlt2TopoMu3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2TopoMu3BodyBBDTDecision_TOS", &PsiHlt2TopoMu3BodyBBDTDecision_TOS, &b_PsiHlt2TopoMu3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2TopoMu4BodyBBDTDecision_Dec", &PsiHlt2TopoMu4BodyBBDTDecision_Dec, &b_PsiHlt2TopoMu4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2TopoMu4BodyBBDTDecision_TIS", &PsiHlt2TopoMu4BodyBBDTDecision_TIS, &b_PsiHlt2TopoMu4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2TopoMu4BodyBBDTDecision_TOS", &PsiHlt2TopoMu4BodyBBDTDecision_TOS, &b_PsiHlt2TopoMu4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2MuonFromHLT1Decision_Dec", &PsiHlt2MuonFromHLT1Decision_Dec, &b_PsiHlt2MuonFromHLT1Decision_Dec);
   fChain->SetBranchAddress("PsiHlt2MuonFromHLT1Decision_TIS", &PsiHlt2MuonFromHLT1Decision_TIS, &b_PsiHlt2MuonFromHLT1Decision_TIS);
   fChain->SetBranchAddress("PsiHlt2MuonFromHLT1Decision_TOS", &PsiHlt2MuonFromHLT1Decision_TOS, &b_PsiHlt2MuonFromHLT1Decision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonDecision_Dec", &PsiHlt2DiMuonDecision_Dec, &b_PsiHlt2DiMuonDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonDecision_TIS", &PsiHlt2DiMuonDecision_TIS, &b_PsiHlt2DiMuonDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonDecision_TOS", &PsiHlt2DiMuonDecision_TOS, &b_PsiHlt2DiMuonDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonLowMassDecision_Dec", &PsiHlt2DiMuonLowMassDecision_Dec, &b_PsiHlt2DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonLowMassDecision_TIS", &PsiHlt2DiMuonLowMassDecision_TIS, &b_PsiHlt2DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonLowMassDecision_TOS", &PsiHlt2DiMuonLowMassDecision_TOS, &b_PsiHlt2DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonJPsiDecision_Dec", &PsiHlt2DiMuonJPsiDecision_Dec, &b_PsiHlt2DiMuonJPsiDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonJPsiDecision_TIS", &PsiHlt2DiMuonJPsiDecision_TIS, &b_PsiHlt2DiMuonJPsiDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonJPsiDecision_TOS", &PsiHlt2DiMuonJPsiDecision_TOS, &b_PsiHlt2DiMuonJPsiDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonJPsiHighPTDecision_Dec", &PsiHlt2DiMuonJPsiHighPTDecision_Dec, &b_PsiHlt2DiMuonJPsiHighPTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonJPsiHighPTDecision_TIS", &PsiHlt2DiMuonJPsiHighPTDecision_TIS, &b_PsiHlt2DiMuonJPsiHighPTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonJPsiHighPTDecision_TOS", &PsiHlt2DiMuonJPsiHighPTDecision_TOS, &b_PsiHlt2DiMuonJPsiHighPTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonPsi2SDecision_Dec", &PsiHlt2DiMuonPsi2SDecision_Dec, &b_PsiHlt2DiMuonPsi2SDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonPsi2SDecision_TIS", &PsiHlt2DiMuonPsi2SDecision_TIS, &b_PsiHlt2DiMuonPsi2SDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonPsi2SDecision_TOS", &PsiHlt2DiMuonPsi2SDecision_TOS, &b_PsiHlt2DiMuonPsi2SDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonPsi2SHighPTDecision_Dec", &PsiHlt2DiMuonPsi2SHighPTDecision_Dec, &b_PsiHlt2DiMuonPsi2SHighPTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonPsi2SHighPTDecision_TIS", &PsiHlt2DiMuonPsi2SHighPTDecision_TIS, &b_PsiHlt2DiMuonPsi2SHighPTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonPsi2SHighPTDecision_TOS", &PsiHlt2DiMuonPsi2SHighPTDecision_TOS, &b_PsiHlt2DiMuonPsi2SHighPTDecision_TOS);
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
   fChain->SetBranchAddress("PsiHlt2ExpressJPsiDecision_Dec", &PsiHlt2ExpressJPsiDecision_Dec, &b_PsiHlt2ExpressJPsiDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2ExpressJPsiDecision_TIS", &PsiHlt2ExpressJPsiDecision_TIS, &b_PsiHlt2ExpressJPsiDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2ExpressJPsiDecision_TOS", &PsiHlt2ExpressJPsiDecision_TOS, &b_PsiHlt2ExpressJPsiDecision_TOS);
   fChain->SetBranchAddress("Psi_NOPARTWITHINDCHI2WDW", &Psi_NOPARTWITHINDCHI2WDW, &b_Psi_NOPARTWITHINDCHI2WDW);
   fChain->SetBranchAddress("Psi_NOPARTWITHINCHI2WDW", &Psi_NOPARTWITHINCHI2WDW, &b_Psi_NOPARTWITHINCHI2WDW);
   fChain->SetBranchAddress("Psi_SMALLESTCHI2", &Psi_SMALLESTCHI2, &b_Psi_SMALLESTCHI2);
   fChain->SetBranchAddress("Psi_SMALLESTDELTACHI2", &Psi_SMALLESTDELTACHI2, &b_Psi_SMALLESTDELTACHI2);
   fChain->SetBranchAddress("muminus_MINIP", &muminus_MINIP, &b_muminus_MINIP);
   fChain->SetBranchAddress("muminus_MINIPCHI2", &muminus_MINIPCHI2, &b_muminus_MINIPCHI2);
   fChain->SetBranchAddress("muminus_MINIPNEXTBEST", &muminus_MINIPNEXTBEST, &b_muminus_MINIPNEXTBEST);
   fChain->SetBranchAddress("muminus_MINIPCHI2NEXTBEST", &muminus_MINIPCHI2NEXTBEST, &b_muminus_MINIPCHI2NEXTBEST);
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
   fChain->SetBranchAddress("muminus_TRUEID", &muminus_TRUEID, &b_muminus_TRUEID);
   fChain->SetBranchAddress("muminus_MC_MOTHER_ID", &muminus_MC_MOTHER_ID, &b_muminus_MC_MOTHER_ID);
   fChain->SetBranchAddress("muminus_MC_MOTHER_KEY", &muminus_MC_MOTHER_KEY, &b_muminus_MC_MOTHER_KEY);
   fChain->SetBranchAddress("muminus_MC_GD_MOTHER_ID", &muminus_MC_GD_MOTHER_ID, &b_muminus_MC_GD_MOTHER_ID);
   fChain->SetBranchAddress("muminus_MC_GD_MOTHER_KEY", &muminus_MC_GD_MOTHER_KEY, &b_muminus_MC_GD_MOTHER_KEY);
   fChain->SetBranchAddress("muminus_MC_GD_GD_MOTHER_ID", &muminus_MC_GD_GD_MOTHER_ID, &b_muminus_MC_GD_GD_MOTHER_ID);
   fChain->SetBranchAddress("muminus_MC_GD_GD_MOTHER_KEY", &muminus_MC_GD_GD_MOTHER_KEY, &b_muminus_MC_GD_GD_MOTHER_KEY);
   fChain->SetBranchAddress("muminus_TRUEP_E", &muminus_TRUEP_E, &b_muminus_TRUEP_E);
   fChain->SetBranchAddress("muminus_TRUEP_X", &muminus_TRUEP_X, &b_muminus_TRUEP_X);
   fChain->SetBranchAddress("muminus_TRUEP_Y", &muminus_TRUEP_Y, &b_muminus_TRUEP_Y);
   fChain->SetBranchAddress("muminus_TRUEP_Z", &muminus_TRUEP_Z, &b_muminus_TRUEP_Z);
   fChain->SetBranchAddress("muminus_TRUEPT", &muminus_TRUEPT, &b_muminus_TRUEPT);
   fChain->SetBranchAddress("muminus_TRUEORIGINVERTEX_X", &muminus_TRUEORIGINVERTEX_X, &b_muminus_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("muminus_TRUEORIGINVERTEX_Y", &muminus_TRUEORIGINVERTEX_Y, &b_muminus_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("muminus_TRUEORIGINVERTEX_Z", &muminus_TRUEORIGINVERTEX_Z, &b_muminus_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("muminus_TRUEENDVERTEX_X", &muminus_TRUEENDVERTEX_X, &b_muminus_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("muminus_TRUEENDVERTEX_Y", &muminus_TRUEENDVERTEX_Y, &b_muminus_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("muminus_TRUEENDVERTEX_Z", &muminus_TRUEENDVERTEX_Z, &b_muminus_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("muminus_TRUEISSTABLE", &muminus_TRUEISSTABLE, &b_muminus_TRUEISSTABLE);
   fChain->SetBranchAddress("muminus_TRUETAU", &muminus_TRUETAU, &b_muminus_TRUETAU);
   fChain->SetBranchAddress("muminus_OSCIL", &muminus_OSCIL, &b_muminus_OSCIL);
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
   fChain->SetBranchAddress("muminus_TRACK_GhostProb", &muminus_TRACK_GhostProb, &b_muminus_TRACK_GhostProb);
   fChain->SetBranchAddress("muminus_TRACK_CloneDist", &muminus_TRACK_CloneDist, &b_muminus_TRACK_CloneDist);
   fChain->SetBranchAddress("muplus_MINIP", &muplus_MINIP, &b_muplus_MINIP);
   fChain->SetBranchAddress("muplus_MINIPCHI2", &muplus_MINIPCHI2, &b_muplus_MINIPCHI2);
   fChain->SetBranchAddress("muplus_MINIPNEXTBEST", &muplus_MINIPNEXTBEST, &b_muplus_MINIPNEXTBEST);
   fChain->SetBranchAddress("muplus_MINIPCHI2NEXTBEST", &muplus_MINIPCHI2NEXTBEST, &b_muplus_MINIPCHI2NEXTBEST);
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
   fChain->SetBranchAddress("muplus_TRUEID", &muplus_TRUEID, &b_muplus_TRUEID);
   fChain->SetBranchAddress("muplus_MC_MOTHER_ID", &muplus_MC_MOTHER_ID, &b_muplus_MC_MOTHER_ID);
   fChain->SetBranchAddress("muplus_MC_MOTHER_KEY", &muplus_MC_MOTHER_KEY, &b_muplus_MC_MOTHER_KEY);
   fChain->SetBranchAddress("muplus_MC_GD_MOTHER_ID", &muplus_MC_GD_MOTHER_ID, &b_muplus_MC_GD_MOTHER_ID);
   fChain->SetBranchAddress("muplus_MC_GD_MOTHER_KEY", &muplus_MC_GD_MOTHER_KEY, &b_muplus_MC_GD_MOTHER_KEY);
   fChain->SetBranchAddress("muplus_MC_GD_GD_MOTHER_ID", &muplus_MC_GD_GD_MOTHER_ID, &b_muplus_MC_GD_GD_MOTHER_ID);
   fChain->SetBranchAddress("muplus_MC_GD_GD_MOTHER_KEY", &muplus_MC_GD_GD_MOTHER_KEY, &b_muplus_MC_GD_GD_MOTHER_KEY);
   fChain->SetBranchAddress("muplus_TRUEP_E", &muplus_TRUEP_E, &b_muplus_TRUEP_E);
   fChain->SetBranchAddress("muplus_TRUEP_X", &muplus_TRUEP_X, &b_muplus_TRUEP_X);
   fChain->SetBranchAddress("muplus_TRUEP_Y", &muplus_TRUEP_Y, &b_muplus_TRUEP_Y);
   fChain->SetBranchAddress("muplus_TRUEP_Z", &muplus_TRUEP_Z, &b_muplus_TRUEP_Z);
   fChain->SetBranchAddress("muplus_TRUEPT", &muplus_TRUEPT, &b_muplus_TRUEPT);
   fChain->SetBranchAddress("muplus_TRUEORIGINVERTEX_X", &muplus_TRUEORIGINVERTEX_X, &b_muplus_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("muplus_TRUEORIGINVERTEX_Y", &muplus_TRUEORIGINVERTEX_Y, &b_muplus_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("muplus_TRUEORIGINVERTEX_Z", &muplus_TRUEORIGINVERTEX_Z, &b_muplus_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("muplus_TRUEENDVERTEX_X", &muplus_TRUEENDVERTEX_X, &b_muplus_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("muplus_TRUEENDVERTEX_Y", &muplus_TRUEENDVERTEX_Y, &b_muplus_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("muplus_TRUEENDVERTEX_Z", &muplus_TRUEENDVERTEX_Z, &b_muplus_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("muplus_TRUEISSTABLE", &muplus_TRUEISSTABLE, &b_muplus_TRUEISSTABLE);
   fChain->SetBranchAddress("muplus_TRUETAU", &muplus_TRUETAU, &b_muplus_TRUETAU);
   fChain->SetBranchAddress("muplus_OSCIL", &muplus_OSCIL, &b_muplus_OSCIL);
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
   fChain->SetBranchAddress("muplus_TRACK_GhostProb", &muplus_TRACK_GhostProb, &b_muplus_TRACK_GhostProb);
   fChain->SetBranchAddress("muplus_TRACK_CloneDist", &muplus_TRACK_CloneDist, &b_muplus_TRACK_CloneDist);
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
   fChain->SetBranchAddress("Primaries", &Primaries, &b_Primaries);
   fChain->SetBranchAddress("Polarity", &Polarity, &b_Polarity);
   fChain->SetBranchAddress("nPV", &nPV, &b_nPV);
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
// hacking between versions of MC ;)
Float_t Lambdab::Manage_B_FullFit_chi2_B(Int_t j)
{
	return (b_B_FullFit_chi2_B?B_FullFit_chi2_B[j]:B_FullFit_chi2[j]);
}
#endif // #ifdef Lambdab_cxx
