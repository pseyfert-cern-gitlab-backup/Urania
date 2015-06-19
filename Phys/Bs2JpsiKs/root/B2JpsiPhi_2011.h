// ####################################################################################################
// Phys/Bs2JpsiKs Package
// Decay Specific Functions - Header File
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################


// ####################################################################################################

#ifndef B2JpsiPhi_2011_h
#define B2JpsiPhi_2011_h

// *** Load Useful Classes ***
#include "IB2JpsiX.h"


// ####################################################################################################
class B2JpsiPhi_2011: virtual public IB2JpsiX {
 private:
 
   // *** Used Constants ***
 
   // Selection Cuts
   double DTF_chi2 ;
   double MMERR_cut ;
  
   // Neural Net Variables
   int dtfc ;
   int dira ;
   int phpt ;
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
   int phez ;
   int phch ;
   int pipc ;
   int phmm ;
   int phme ;
   int phmo ;
   int muic ;
   int muip ;
   int mumo ;
   int mupt ;
   int muid ;
   int mutk ;
   int kaic ;
   int kaip ;
   int kapt ;
   int kagp ;
   int kagc ;
   int katk ;
   int prim ;
   int spdm ; 
   int otcl ;
   int nvar_without_ttype ;
   int NNIvar ;
 
public :

   // *** Constructors ***
   B2JpsiPhi_2011(TTree *tree=0, TString module=0, TString dir=0, TString what=0, unsigned int NNtype=0);
   virtual ~B2JpsiPhi_2011();
  
   // *** Accessors ***
   // Mass Regions
   double sideband_low_min(){return 5180;} ;
   double sideband_high_min(){return 5400;} ;
   double sideband_high_max(){return 5520;} ;
   
  // *** Updated version of DaVinci ***
  Bool_t Psi_Hlt1TrackMuonDecision_TOS;
  Bool_t Psi_Hlt1DiMuonHighMassDecision_TOS;
  Bool_t Psi_Hlt1TrackAllL0Decision_TOS;
  Bool_t Psi_Hlt2DiMuonDetachedJPsiDecision_TOS;
  Bool_t Psi_Hlt2DiMuonJPsiHighPTDecision_TOS;
  Bool_t Psi_Hlt2DiMuonJPsiDecision_TOS;
  Bool_t Psi_Hlt2TopoMu2BodyBBDTDecision_TOS;
  Bool_t Psi_L0Global_Dec;
  Bool_t Psi_Hlt1Global_Dec;
  Bool_t Psi_Hlt2Global_Dec;
  Bool_t Psi_L0Global_TIS;
  Bool_t Psi_Hlt1Global_TIS;
  Bool_t Psi_Hlt2Global_TIS;

   // *** Truth information ***
   Int_t B_TRUEID;
   Int_t Psi_TRUEID;
   Int_t phi_1020_TRUEID;
   Int_t B_BKGCAT;
   Double_t B_TRUETAU;
   
   TBranch        *b_B_TRUEID;   //!
   TBranch        *b_Psi_TRUEID;   //!
   TBranch        *b_phi_1020_TRUEID;   //!
   TBranch        *b_B_BKGCAT;   //!
   TBranch        *b_B_TRUETAU;   //!
   
   // *** sWeights && Neural Net ***
   Double_t sweight[100];
   TBranch        *b_sweight;
   Float_t netOutput[100];
   TBranch        *b_netOutput;

   // *** Tree Manipulation *** 
   TTree *fChain;   // pointer to the analyzed TTree or TChain
   Int_t fCurrent; // current Tree number in a TChain

// ####################################################################################################

//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jan 19 13:14:44 2012 by ROOT version 5.30/04
// from TTree DecayTree/DecayTree
// found on file: Bs2JpsiPhi-2011-171.root
//////////////////////////////////////////////////////////

   // Declaration of leaf types
   Float_t         B_MINIP;
   Float_t         B_MINIPCHI2;
   Float_t         B_MINIPNEXTBEST;
   Float_t         B_MINIPCHI2NEXTBEST;
   Float_t         B_OWNPV_X;
   Float_t         B_OWNPV_Y;
   Float_t         B_OWNPV_Z;
   Float_t         B_OWNPV_XERR;
   Float_t         B_OWNPV_YERR;
   Float_t         B_OWNPV_ZERR;
   Float_t         B_OWNPV_CHI2;
   Int_t           B_OWNPV_NDOF;
   Float_t         B_OWNPV_COV_[3][3];
   Float_t         B_IP_OWNPV;
   Float_t         B_IPCHI2_OWNPV;
   Float_t         B_FD_OWNPV;
   Float_t         B_FDCHI2_OWNPV;
   Float_t         B_DIRA_OWNPV;
   Float_t         B_ENDVERTEX_X;
   Float_t         B_ENDVERTEX_Y;
   Float_t         B_ENDVERTEX_Z;
   Float_t         B_ENDVERTEX_XERR;
   Float_t         B_ENDVERTEX_YERR;
   Float_t         B_ENDVERTEX_ZERR;
   Float_t         B_ENDVERTEX_CHI2;
   Int_t           B_ENDVERTEX_NDOF;
   Float_t         B_ENDVERTEX_COV_[3][3];
   Float_t         B_P;
   Float_t         B_PT;
   Float_t         B_PE;
   Float_t         B_PX;
   Float_t         B_PY;
   Float_t         B_PZ;
   Float_t         B_MM;
   Float_t         B_MMERR;
   Float_t         B_M;
   Int_t           B_ID;
   Float_t         B_TAU;
   Float_t         B_TAUERR;
   Float_t         B_TAUCHI2;
   Int_t           B_Fit_nPV;
   Float_t         B_Fit_M[100];   //[B_Fit_nPV]
   Float_t         B_Fit_MERR[100];   //[B_Fit_nPV]
   Float_t         B_Fit_P[100];   //[B_Fit_nPV]
   Float_t         B_Fit_PERR[100];   //[B_Fit_nPV]
   Float_t         B_Fit_chi2_B[100];   //[B_Fit_nPV]
   Float_t         B_Fit_chi2[100];   //[B_Fit_nPV]
   Float_t         B_Fit_nDOF[100];   //[B_Fit_nPV]
   Float_t         B_Fit_nIter[100];   //[B_Fit_nPV]
   Float_t         B_Fit_status[100];   //[B_Fit_nPV]
   Int_t           B_FullFit_nPV;
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
   Float_t         B_FullFit_PV_sumPT[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_chi2_B[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_chi2[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_ctau[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_ctauErr[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_decayLength[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_decayLengthErr[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_nDOF[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_nIter[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_phi_1020_ctau[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_phi_1020_ctauErr[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_phi_1020_decayLength[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_phi_1020_decayLengthErr[100];   //[B_FullFit_nPV]
   Float_t         B_FullFit_status[100];   //[B_FullFit_nPV]
   Int_t           B_MassFit_nPV;
   Float_t         B_MassFit_M[100];   //[B_MassFit_nPV]
   Float_t         B_MassFit_MERR[100];   //[B_MassFit_nPV]
   Float_t         B_MassFit_P[100];   //[B_MassFit_nPV]
   Float_t         B_MassFit_PERR[100];   //[B_MassFit_nPV]
   Float_t         B_MassFit_chi2_B[100];   //[B_MassFit_nPV]
   Float_t         B_MassFit_chi2[100];   //[B_MassFit_nPV]
   Float_t         B_MassFit_nDOF[100];   //[B_MassFit_nPV]
   Float_t         B_MassFit_nIter[100];   //[B_MassFit_nPV]
   Float_t         B_MassFit_status[100];   //[B_MassFit_nPV]
   Int_t           B_NoKsFit_nPV;
   Float_t         B_NoKsFit_J_psi_1S_ctau[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_J_psi_1S_ctauErr[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_J_psi_1S_decayLength[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_J_psi_1S_decayLengthErr[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_M[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_MERR[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_P[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_PERR[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_PV_X[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_PV_Y[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_PV_Z[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_PV_key[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_PV_sumPT[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_chi2_B[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_chi2[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_ctau[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_ctauErr[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_decayLength[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_decayLengthErr[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_nDOF[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_nIter[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_phi_1020_ctau[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_phi_1020_ctauErr[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_phi_1020_decayLength[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_phi_1020_decayLengthErr[100];   //[B_NoKsFit_nPV]
   Float_t         B_NoKsFit_status[100];   //[B_NoKsFit_nPV]
   Int_t           B_PVFit_nPV;
   Float_t         B_PVFit_M[100];   //[B_PVFit_nPV]
   Float_t         B_PVFit_MERR[100];   //[B_PVFit_nPV]
   Float_t         B_PVFit_P[100];   //[B_PVFit_nPV]
   Float_t         B_PVFit_PERR[100];   //[B_PVFit_nPV]
   Float_t         B_PVFit_chi2_B[100];   //[B_PVFit_nPV]
   Float_t         B_PVFit_chi2[100];   //[B_PVFit_nPV]
   Float_t         B_PVFit_nDOF[100];   //[B_PVFit_nPV]
   Float_t         B_PVFit_nIter[100];   //[B_PVFit_nPV]
   Float_t         B_PVFit_status[100];   //[B_PVFit_nPV]
   Int_t           BL0Global_Dec;
   Int_t           BL0Global_TIS;
   Int_t           BL0Global_TOS;
   Int_t           BHlt1Global_Dec;
   Int_t           BHlt1Global_TIS;
   Int_t           BHlt1Global_TOS;
   Int_t           BHlt2Global_Dec;
   Int_t           BHlt2Global_TIS;
   Int_t           BHlt2Global_TOS;
   Int_t           BHlt1TrackAllL0Decision_Dec;
   Int_t           BHlt1TrackAllL0Decision_TIS;
   Int_t           BHlt1TrackAllL0Decision_TOS;
   Int_t           BHlt1MuTrackDecision_Dec;
   Int_t           BHlt1MuTrackDecision_TIS;
   Int_t           BHlt1MuTrackDecision_TOS;
   Int_t           BHlt1DiMuonNoIP2L0Decision_Dec;
   Int_t           BHlt1DiMuonNoIP2L0Decision_TIS;
   Int_t           BHlt1DiMuonNoIP2L0Decision_TOS;
   Int_t           BHlt1DiMuonNoIPL0SegDecision_Dec;
   Int_t           BHlt1DiMuonNoIPL0SegDecision_TIS;
   Int_t           BHlt1DiMuonNoIPL0SegDecision_TOS;
   Int_t           BHlt1DiMuonIPCL0DiDecision_Dec;
   Int_t           BHlt1DiMuonIPCL0DiDecision_TIS;
   Int_t           BHlt1DiMuonIPCL0DiDecision_TOS;
   Int_t           BHlt1DiMuonIPC2L0Decision_Dec;
   Int_t           BHlt1DiMuonIPC2L0Decision_TIS;
   Int_t           BHlt1DiMuonIPC2L0Decision_TOS;
   Int_t           BHlt1DiMuonIPCL0SegDecision_Dec;
   Int_t           BHlt1DiMuonIPCL0SegDecision_TIS;
   Int_t           BHlt1DiMuonIPCL0SegDecision_TOS;
   Int_t           BHlt1DiMuonHighMassDecision_Dec;
   Int_t           BHlt1DiMuonHighMassDecision_TIS;
   Int_t           BHlt1DiMuonHighMassDecision_TOS;
   Int_t           BHlt1DiMuonLowMassDecision_Dec;
   Int_t           BHlt1DiMuonLowMassDecision_TIS;
   Int_t           BHlt1DiMuonLowMassDecision_TOS;
   Int_t           BHlt1SingleMuonNoIPL0Decision_Dec;
   Int_t           BHlt1SingleMuonNoIPL0Decision_TIS;
   Int_t           BHlt1SingleMuonNoIPL0Decision_TOS;
   Int_t           BHlt1SingleMuonNoIPL0HighPTDecision_Dec;
   Int_t           BHlt1SingleMuonNoIPL0HighPTDecision_TIS;
   Int_t           BHlt1SingleMuonNoIPL0HighPTDecision_TOS;
   Int_t           BHlt1SingleMuonIPCL0Decision_Dec;
   Int_t           BHlt1SingleMuonIPCL0Decision_TIS;
   Int_t           BHlt1SingleMuonIPCL0Decision_TOS;
   Int_t           BHlt1SingleMuonNoIPDecision_Dec;
   Int_t           BHlt1SingleMuonNoIPDecision_TIS;
   Int_t           BHlt1SingleMuonNoIPDecision_TOS;
   Int_t           BHlt1TrackMuonDecision_Dec;
   Int_t           BHlt1TrackMuonDecision_TIS;
   Int_t           BHlt1TrackMuonDecision_TOS;
   Int_t           BHlt2TopoTF3BodyReq2YesDecision_Dec;
   Int_t           BHlt2TopoTF3BodyReq2YesDecision_TIS;
   Int_t           BHlt2TopoTF3BodyReq2YesDecision_TOS;
   Int_t           BHlt2TopoTF3BodyReq3YesDecision_Dec;
   Int_t           BHlt2TopoTF3BodyReq3YesDecision_TIS;
   Int_t           BHlt2TopoTF3BodyReq3YesDecision_TOS;
   Int_t           BHlt2TopoOSTF2BodyDecision_Dec;
   Int_t           BHlt2TopoOSTF2BodyDecision_TIS;
   Int_t           BHlt2TopoOSTF2BodyDecision_TOS;
   Int_t           BHlt2TopoOSTF3BodyDecision_Dec;
   Int_t           BHlt2TopoOSTF3BodyDecision_TIS;
   Int_t           BHlt2TopoOSTF3BodyDecision_TOS;
   Int_t           BHlt2TopoOSTF4BodyDecision_Dec;
   Int_t           BHlt2TopoOSTF4BodyDecision_TIS;
   Int_t           BHlt2TopoOSTF4BodyDecision_TOS;
   Int_t           BHlt2TransparentDecision_Dec;
   Int_t           BHlt2TransparentDecision_TIS;
   Int_t           BHlt2TransparentDecision_TOS;
   Int_t           BHlt2Topo2BodySimpleDecision_Dec;
   Int_t           BHlt2Topo2BodySimpleDecision_TIS;
   Int_t           BHlt2Topo2BodySimpleDecision_TOS;
   Int_t           BHlt2Topo3BodySimpleDecision_Dec;
   Int_t           BHlt2Topo3BodySimpleDecision_TIS;
   Int_t           BHlt2Topo3BodySimpleDecision_TOS;
   Int_t           BHlt2Topo4BodySimpleDecision_Dec;
   Int_t           BHlt2Topo4BodySimpleDecision_TIS;
   Int_t           BHlt2Topo4BodySimpleDecision_TOS;
   Int_t           BHlt2Topo2BodyBBDTDecision_Dec;
   Int_t           BHlt2Topo2BodyBBDTDecision_TIS;
   Int_t           BHlt2Topo2BodyBBDTDecision_TOS;
   Int_t           BHlt2Topo3BodyBBDTDecision_Dec;
   Int_t           BHlt2Topo3BodyBBDTDecision_TIS;
   Int_t           BHlt2Topo3BodyBBDTDecision_TOS;
   Int_t           BHlt2Topo4BodyBBDTDecision_Dec;
   Int_t           BHlt2Topo4BodyBBDTDecision_TIS;
   Int_t           BHlt2Topo4BodyBBDTDecision_TOS;
   Int_t           BHlt2MuTrackDecision_Dec;
   Int_t           BHlt2MuTrackDecision_TIS;
   Int_t           BHlt2MuTrackDecision_TOS;
   Int_t           BHlt2MuTrackNoIPDecision_Dec;
   Int_t           BHlt2MuTrackNoIPDecision_TIS;
   Int_t           BHlt2MuTrackNoIPDecision_TOS;
   Int_t           BHlt2SingleMuonDecision_Dec;
   Int_t           BHlt2SingleMuonDecision_TIS;
   Int_t           BHlt2SingleMuonDecision_TOS;
   Int_t           BHlt2UnbiasedDiMuonDecision_Dec;
   Int_t           BHlt2UnbiasedDiMuonDecision_TIS;
   Int_t           BHlt2UnbiasedDiMuonDecision_TOS;
   Int_t           BHlt2UnbiasedDiMuonLowMassDecision_Dec;
   Int_t           BHlt2UnbiasedDiMuonLowMassDecision_TIS;
   Int_t           BHlt2UnbiasedDiMuonLowMassDecision_TOS;
   Int_t           BHlt2DiMuonUnbiasedJPsiDecision_Dec;
   Int_t           BHlt2DiMuonUnbiasedJPsiDecision_TIS;
   Int_t           BHlt2DiMuonUnbiasedJPsiDecision_TOS;
   Int_t           BHlt2DiMuonUnbiasedPsi2SDecision_Dec;
   Int_t           BHlt2DiMuonUnbiasedPsi2SDecision_TIS;
   Int_t           BHlt2DiMuonUnbiasedPsi2SDecision_TOS;
   Int_t           BHlt2BiasedDiMuonSimpleDecision_Dec;
   Int_t           BHlt2BiasedDiMuonSimpleDecision_TIS;
   Int_t           BHlt2BiasedDiMuonSimpleDecision_TOS;
   Int_t           BHlt2BiasedDiMuonRefinedDecision_Dec;
   Int_t           BHlt2BiasedDiMuonRefinedDecision_TIS;
   Int_t           BHlt2BiasedDiMuonRefinedDecision_TOS;
   Int_t           BHlt2BiasedDiMuonMassDecision_Dec;
   Int_t           BHlt2BiasedDiMuonMassDecision_TIS;
   Int_t           BHlt2BiasedDiMuonMassDecision_TOS;
   Int_t           BHlt2BiasedDiMuonIPDecision_Dec;
   Int_t           BHlt2BiasedDiMuonIPDecision_TIS;
   Int_t           BHlt2BiasedDiMuonIPDecision_TOS;
   Int_t           BHlt2DiMuonBiasedJPsiDecision_Dec;
   Int_t           BHlt2DiMuonBiasedJPsiDecision_TIS;
   Int_t           BHlt2DiMuonBiasedJPsiDecision_TOS;
   Int_t           BHlt2TopoMu2BodyBBDTDecision_Dec;
   Int_t           BHlt2TopoMu2BodyBBDTDecision_TIS;
   Int_t           BHlt2TopoMu2BodyBBDTDecision_TOS;
   Int_t           BHlt2TopoMu3BodyBBDTDecision_Dec;
   Int_t           BHlt2TopoMu3BodyBBDTDecision_TIS;
   Int_t           BHlt2TopoMu3BodyBBDTDecision_TOS;
   Int_t           BHlt2TopoMu4BodyBBDTDecision_Dec;
   Int_t           BHlt2TopoMu4BodyBBDTDecision_TIS;
   Int_t           BHlt2TopoMu4BodyBBDTDecision_TOS;
   Int_t           BHlt2SingleMuonHighPTDecision_Dec;
   Int_t           BHlt2SingleMuonHighPTDecision_TIS;
   Int_t           BHlt2SingleMuonHighPTDecision_TOS;
   Int_t           BHlt2SingleMuonLowPTDecision_Dec;
   Int_t           BHlt2SingleMuonLowPTDecision_TIS;
   Int_t           BHlt2SingleMuonLowPTDecision_TOS;
   Int_t           BHlt2DiMuonDecision_Dec;
   Int_t           BHlt2DiMuonDecision_TIS;
   Int_t           BHlt2DiMuonDecision_TOS;
   Int_t           BHlt2DiMuonLowMassDecision_Dec;
   Int_t           BHlt2DiMuonLowMassDecision_TIS;
   Int_t           BHlt2DiMuonLowMassDecision_TOS;
   Int_t           BHlt2DiMuonJPsiDecision_Dec;
   Int_t           BHlt2DiMuonJPsiDecision_TIS;
   Int_t           BHlt2DiMuonJPsiDecision_TOS;
   Int_t           BHlt2DiMuonJPsiHighPTDecision_Dec;
   Int_t           BHlt2DiMuonJPsiHighPTDecision_TIS;
   Int_t           BHlt2DiMuonJPsiHighPTDecision_TOS;
   Int_t           BHlt2DiMuonPsi2SDecision_Dec;
   Int_t           BHlt2DiMuonPsi2SDecision_TIS;
   Int_t           BHlt2DiMuonPsi2SDecision_TOS;
   Int_t           BHlt2DiMuonBDecision_Dec;
   Int_t           BHlt2DiMuonBDecision_TIS;
   Int_t           BHlt2DiMuonBDecision_TOS;
   Int_t           BHlt2DiMuonDetachedDecision_Dec;
   Int_t           BHlt2DiMuonDetachedDecision_TIS;
   Int_t           BHlt2DiMuonDetachedDecision_TOS;
   Int_t           BHlt2DiMuonDetachedHeavyDecision_Dec;
   Int_t           BHlt2DiMuonDetachedHeavyDecision_TIS;
   Int_t           BHlt2DiMuonDetachedHeavyDecision_TOS;
   Int_t           BHlt2DiMuonDetachedJPsiDecision_Dec;
   Int_t           BHlt2DiMuonDetachedJPsiDecision_TIS;
   Int_t           BHlt2DiMuonDetachedJPsiDecision_TOS;
   Int_t           BHlt2ExpressJPsiDecision_Dec;
   Int_t           BHlt2ExpressJPsiDecision_TIS;
   Int_t           BHlt2ExpressJPsiDecision_TOS;
   Float_t         phi_1020_MINIP;
   Float_t         phi_1020_MINIPCHI2;
   Float_t         phi_1020_MINIPNEXTBEST;
   Float_t         phi_1020_MINIPCHI2NEXTBEST;
   Float_t         phi_1020_OWNPV_X;
   Float_t         phi_1020_OWNPV_Y;
   Float_t         phi_1020_OWNPV_Z;
   Float_t         phi_1020_OWNPV_XERR;
   Float_t         phi_1020_OWNPV_YERR;
   Float_t         phi_1020_OWNPV_ZERR;
   Float_t         phi_1020_OWNPV_CHI2;
   Int_t           phi_1020_OWNPV_NDOF;
   Float_t         phi_1020_OWNPV_COV_[3][3];
   Float_t         phi_1020_IP_OWNPV;
   Float_t         phi_1020_IPCHI2_OWNPV;
   Float_t         phi_1020_FD_OWNPV;
   Float_t         phi_1020_FDCHI2_OWNPV;
   Float_t         phi_1020_DIRA_OWNPV;
   Float_t         phi_1020_ORIVX_X;
   Float_t         phi_1020_ORIVX_Y;
   Float_t         phi_1020_ORIVX_Z;
   Float_t         phi_1020_ORIVX_XERR;
   Float_t         phi_1020_ORIVX_YERR;
   Float_t         phi_1020_ORIVX_ZERR;
   Float_t         phi_1020_ORIVX_CHI2;
   Int_t           phi_1020_ORIVX_NDOF;
   Float_t         phi_1020_ORIVX_COV_[3][3];
   Float_t         phi_1020_FD_ORIVX;
   Float_t         phi_1020_FDCHI2_ORIVX;
   Float_t         phi_1020_DIRA_ORIVX;
   Float_t         phi_1020_ENDVERTEX_X;
   Float_t         phi_1020_ENDVERTEX_Y;
   Float_t         phi_1020_ENDVERTEX_Z;
   Float_t         phi_1020_ENDVERTEX_XERR;
   Float_t         phi_1020_ENDVERTEX_YERR;
   Float_t         phi_1020_ENDVERTEX_ZERR;
   Float_t         phi_1020_ENDVERTEX_CHI2;
   Int_t           phi_1020_ENDVERTEX_NDOF;
   Float_t         phi_1020_ENDVERTEX_COV_[3][3];
   Float_t         phi_1020_P;
   Float_t         phi_1020_PT;
   Float_t         phi_1020_PE;
   Float_t         phi_1020_PX;
   Float_t         phi_1020_PY;
   Float_t         phi_1020_PZ;
   Float_t         phi_1020_MM;
   Float_t         phi_1020_MMERR;
   Float_t         phi_1020_M;
   Int_t           phi_1020_ID;
   Float_t         phi_1020_TAU;
   Float_t         phi_1020_TAUERR;
   Float_t         phi_1020_TAUCHI2;
   Float_t         Kminus_MINIP;
   Float_t         Kminus_MINIPCHI2;
   Float_t         Kminus_MINIPNEXTBEST;
   Float_t         Kminus_MINIPCHI2NEXTBEST;
   Float_t         Kminus_OWNPV_X;
   Float_t         Kminus_OWNPV_Y;
   Float_t         Kminus_OWNPV_Z;
   Float_t         Kminus_OWNPV_XERR;
   Float_t         Kminus_OWNPV_YERR;
   Float_t         Kminus_OWNPV_ZERR;
   Float_t         Kminus_OWNPV_CHI2;
   Int_t           Kminus_OWNPV_NDOF;
   Float_t         Kminus_OWNPV_COV_[3][3];
   Float_t         Kminus_IP_OWNPV;
   Float_t         Kminus_IPCHI2_OWNPV;
   Float_t         Kminus_ORIVX_X;
   Float_t         Kminus_ORIVX_Y;
   Float_t         Kminus_ORIVX_Z;
   Float_t         Kminus_ORIVX_XERR;
   Float_t         Kminus_ORIVX_YERR;
   Float_t         Kminus_ORIVX_ZERR;
   Float_t         Kminus_ORIVX_CHI2;
   Int_t           Kminus_ORIVX_NDOF;
   Float_t         Kminus_ORIVX_COV_[3][3];
   Float_t         Kminus_P;
   Float_t         Kminus_PT;
   Float_t         Kminus_PE;
   Float_t         Kminus_PX;
   Float_t         Kminus_PY;
   Float_t         Kminus_PZ;
   Float_t         Kminus_M;
   Int_t           Kminus_ID;
   Float_t         Kminus_PIDe;
   Float_t         Kminus_PIDmu;
   Float_t         Kminus_PIDK;
   Float_t         Kminus_PIDp;
   Float_t         Kminus_ProbNNe;
   Float_t         Kminus_ProbNNk;
   Float_t         Kminus_ProbNNp;
   Float_t         Kminus_ProbNNpi;
   Float_t         Kminus_ProbNNmu;
   Float_t         Kminus_ProbNNghost;
   Float_t         Kminus_CaloEcalE;
   Float_t         Kminus_CaloHcalE;
   Int_t           Kminus_hasMuon;
   Int_t           Kminus_isMuon;
   Int_t           Kminus_hasRich;
   Int_t           Kminus_hasCalo;
   Int_t           Kminus_TRACK_Type;
   Int_t           Kminus_TRACK_Key;
   Float_t         Kminus_TRACK_CHI2NDOF;
   Float_t         Kminus_TRACK_PCHI2;
   Float_t         Kminus_TRACK_GhostProb;
   Float_t         Kminus_TRACK_CloneDist;
   Float_t         Kplus_MINIP;
   Float_t         Kplus_MINIPCHI2;
   Float_t         Kplus_MINIPNEXTBEST;
   Float_t         Kplus_MINIPCHI2NEXTBEST;
   Float_t         Kplus_OWNPV_X;
   Float_t         Kplus_OWNPV_Y;
   Float_t         Kplus_OWNPV_Z;
   Float_t         Kplus_OWNPV_XERR;
   Float_t         Kplus_OWNPV_YERR;
   Float_t         Kplus_OWNPV_ZERR;
   Float_t         Kplus_OWNPV_CHI2;
   Int_t           Kplus_OWNPV_NDOF;
   Float_t         Kplus_OWNPV_COV_[3][3];
   Float_t         Kplus_IP_OWNPV;
   Float_t         Kplus_IPCHI2_OWNPV;
   Float_t         Kplus_ORIVX_X;
   Float_t         Kplus_ORIVX_Y;
   Float_t         Kplus_ORIVX_Z;
   Float_t         Kplus_ORIVX_XERR;
   Float_t         Kplus_ORIVX_YERR;
   Float_t         Kplus_ORIVX_ZERR;
   Float_t         Kplus_ORIVX_CHI2;
   Int_t           Kplus_ORIVX_NDOF;
   Float_t         Kplus_ORIVX_COV_[3][3];
   Float_t         Kplus_P;
   Float_t         Kplus_PT;
   Float_t         Kplus_PE;
   Float_t         Kplus_PX;
   Float_t         Kplus_PY;
   Float_t         Kplus_PZ;
   Float_t         Kplus_M;
   Int_t           Kplus_ID;
   Float_t         Kplus_PIDe;
   Float_t         Kplus_PIDmu;
   Float_t         Kplus_PIDK;
   Float_t         Kplus_PIDp;
   Float_t         Kplus_ProbNNe;
   Float_t         Kplus_ProbNNk;
   Float_t         Kplus_ProbNNp;
   Float_t         Kplus_ProbNNpi;
   Float_t         Kplus_ProbNNmu;
   Float_t         Kplus_ProbNNghost;
   Float_t         Kplus_CaloEcalE;
   Float_t         Kplus_CaloHcalE;
   Int_t           Kplus_hasMuon;
   Int_t           Kplus_isMuon;
   Int_t           Kplus_hasRich;
   Int_t           Kplus_hasCalo;
   Int_t           Kplus_TRACK_Type;
   Int_t           Kplus_TRACK_Key;
   Float_t         Kplus_TRACK_CHI2NDOF;
   Float_t         Kplus_TRACK_PCHI2;
   Float_t         Kplus_TRACK_GhostProb;
   Float_t         Kplus_TRACK_CloneDist;
   Float_t         Psi_MINIP;
   Float_t         Psi_MINIPCHI2;
   Float_t         Psi_MINIPNEXTBEST;
   Float_t         Psi_MINIPCHI2NEXTBEST;
   Float_t         Psi_OWNPV_X;
   Float_t         Psi_OWNPV_Y;
   Float_t         Psi_OWNPV_Z;
   Float_t         Psi_OWNPV_XERR;
   Float_t         Psi_OWNPV_YERR;
   Float_t         Psi_OWNPV_ZERR;
   Float_t         Psi_OWNPV_CHI2;
   Int_t           Psi_OWNPV_NDOF;
   Float_t         Psi_OWNPV_COV_[3][3];
   Float_t         Psi_IP_OWNPV;
   Float_t         Psi_IPCHI2_OWNPV;
   Float_t         Psi_FD_OWNPV;
   Float_t         Psi_FDCHI2_OWNPV;
   Float_t         Psi_DIRA_OWNPV;
   Float_t         Psi_ORIVX_X;
   Float_t         Psi_ORIVX_Y;
   Float_t         Psi_ORIVX_Z;
   Float_t         Psi_ORIVX_XERR;
   Float_t         Psi_ORIVX_YERR;
   Float_t         Psi_ORIVX_ZERR;
   Float_t         Psi_ORIVX_CHI2;
   Int_t           Psi_ORIVX_NDOF;
   Float_t         Psi_ORIVX_COV_[3][3];
   Float_t         Psi_FD_ORIVX;
   Float_t         Psi_FDCHI2_ORIVX;
   Float_t         Psi_DIRA_ORIVX;
   Float_t         Psi_ENDVERTEX_X;
   Float_t         Psi_ENDVERTEX_Y;
   Float_t         Psi_ENDVERTEX_Z;
   Float_t         Psi_ENDVERTEX_XERR;
   Float_t         Psi_ENDVERTEX_YERR;
   Float_t         Psi_ENDVERTEX_ZERR;
   Float_t         Psi_ENDVERTEX_CHI2;
   Int_t           Psi_ENDVERTEX_NDOF;
   Float_t         Psi_ENDVERTEX_COV_[3][3];
   Float_t         Psi_P;
   Float_t         Psi_PT;
   Float_t         Psi_PE;
   Float_t         Psi_PX;
   Float_t         Psi_PY;
   Float_t         Psi_PZ;
   Float_t         Psi_MM;
   Float_t         Psi_MMERR;
   Float_t         Psi_M;
   Int_t           Psi_ID;
   Float_t         Psi_TAU;
   Float_t         Psi_TAUERR;
   Float_t         Psi_TAUCHI2;
   Int_t           PsiL0Global_Dec;
   Int_t           PsiL0Global_TIS;
   Int_t           PsiL0Global_TOS;
   Int_t           PsiHlt1Global_Dec;
   Int_t           PsiHlt1Global_TIS;
   Int_t           PsiHlt1Global_TOS;
   Int_t           PsiHlt2Global_Dec;
   Int_t           PsiHlt2Global_TIS;
   Int_t           PsiHlt2Global_TOS;
   Int_t           PsiHlt1TrackAllL0Decision_Dec;
   Int_t           PsiHlt1TrackAllL0Decision_TIS;
   Int_t           PsiHlt1TrackAllL0Decision_TOS;
   Int_t           PsiHlt1MuTrackDecision_Dec;
   Int_t           PsiHlt1MuTrackDecision_TIS;
   Int_t           PsiHlt1MuTrackDecision_TOS;
   Int_t           PsiHlt1DiMuonNoIP2L0Decision_Dec;
   Int_t           PsiHlt1DiMuonNoIP2L0Decision_TIS;
   Int_t           PsiHlt1DiMuonNoIP2L0Decision_TOS;
   Int_t           PsiHlt1DiMuonNoIPL0SegDecision_Dec;
   Int_t           PsiHlt1DiMuonNoIPL0SegDecision_TIS;
   Int_t           PsiHlt1DiMuonNoIPL0SegDecision_TOS;
   Int_t           PsiHlt1DiMuonIPCL0DiDecision_Dec;
   Int_t           PsiHlt1DiMuonIPCL0DiDecision_TIS;
   Int_t           PsiHlt1DiMuonIPCL0DiDecision_TOS;
   Int_t           PsiHlt1DiMuonIPC2L0Decision_Dec;
   Int_t           PsiHlt1DiMuonIPC2L0Decision_TIS;
   Int_t           PsiHlt1DiMuonIPC2L0Decision_TOS;
   Int_t           PsiHlt1DiMuonIPCL0SegDecision_Dec;
   Int_t           PsiHlt1DiMuonIPCL0SegDecision_TIS;
   Int_t           PsiHlt1DiMuonIPCL0SegDecision_TOS;
   Int_t           PsiHlt1DiMuonHighMassDecision_Dec;
   Int_t           PsiHlt1DiMuonHighMassDecision_TIS;
   Int_t           PsiHlt1DiMuonHighMassDecision_TOS;
   Int_t           PsiHlt1DiMuonLowMassDecision_Dec;
   Int_t           PsiHlt1DiMuonLowMassDecision_TIS;
   Int_t           PsiHlt1DiMuonLowMassDecision_TOS;
   Int_t           PsiHlt1SingleMuonNoIPL0Decision_Dec;
   Int_t           PsiHlt1SingleMuonNoIPL0Decision_TIS;
   Int_t           PsiHlt1SingleMuonNoIPL0Decision_TOS;
   Int_t           PsiHlt1SingleMuonNoIPL0HighPTDecision_Dec;
   Int_t           PsiHlt1SingleMuonNoIPL0HighPTDecision_TIS;
   Int_t           PsiHlt1SingleMuonNoIPL0HighPTDecision_TOS;
   Int_t           PsiHlt1SingleMuonIPCL0Decision_Dec;
   Int_t           PsiHlt1SingleMuonIPCL0Decision_TIS;
   Int_t           PsiHlt1SingleMuonIPCL0Decision_TOS;
   Int_t           PsiHlt1SingleMuonNoIPDecision_Dec;
   Int_t           PsiHlt1SingleMuonNoIPDecision_TIS;
   Int_t           PsiHlt1SingleMuonNoIPDecision_TOS;
   Int_t           PsiHlt1TrackMuonDecision_Dec;
   Int_t           PsiHlt1TrackMuonDecision_TIS;
   Int_t           PsiHlt1TrackMuonDecision_TOS;
   Int_t           PsiHlt2TopoTF3BodyReq2YesDecision_Dec;
   Int_t           PsiHlt2TopoTF3BodyReq2YesDecision_TIS;
   Int_t           PsiHlt2TopoTF3BodyReq2YesDecision_TOS;
   Int_t           PsiHlt2TopoTF3BodyReq3YesDecision_Dec;
   Int_t           PsiHlt2TopoTF3BodyReq3YesDecision_TIS;
   Int_t           PsiHlt2TopoTF3BodyReq3YesDecision_TOS;
   Int_t           PsiHlt2TopoOSTF2BodyDecision_Dec;
   Int_t           PsiHlt2TopoOSTF2BodyDecision_TIS;
   Int_t           PsiHlt2TopoOSTF2BodyDecision_TOS;
   Int_t           PsiHlt2TopoOSTF3BodyDecision_Dec;
   Int_t           PsiHlt2TopoOSTF3BodyDecision_TIS;
   Int_t           PsiHlt2TopoOSTF3BodyDecision_TOS;
   Int_t           PsiHlt2TopoOSTF4BodyDecision_Dec;
   Int_t           PsiHlt2TopoOSTF4BodyDecision_TIS;
   Int_t           PsiHlt2TopoOSTF4BodyDecision_TOS;
   Int_t           PsiHlt2TransparentDecision_Dec;
   Int_t           PsiHlt2TransparentDecision_TIS;
   Int_t           PsiHlt2TransparentDecision_TOS;
   Int_t           PsiHlt2Topo2BodySimpleDecision_Dec;
   Int_t           PsiHlt2Topo2BodySimpleDecision_TIS;
   Int_t           PsiHlt2Topo2BodySimpleDecision_TOS;
   Int_t           PsiHlt2Topo3BodySimpleDecision_Dec;
   Int_t           PsiHlt2Topo3BodySimpleDecision_TIS;
   Int_t           PsiHlt2Topo3BodySimpleDecision_TOS;
   Int_t           PsiHlt2Topo4BodySimpleDecision_Dec;
   Int_t           PsiHlt2Topo4BodySimpleDecision_TIS;
   Int_t           PsiHlt2Topo4BodySimpleDecision_TOS;
   Int_t           PsiHlt2Topo2BodyBBDTDecision_Dec;
   Int_t           PsiHlt2Topo2BodyBBDTDecision_TIS;
   Int_t           PsiHlt2Topo2BodyBBDTDecision_TOS;
   Int_t           PsiHlt2Topo3BodyBBDTDecision_Dec;
   Int_t           PsiHlt2Topo3BodyBBDTDecision_TIS;
   Int_t           PsiHlt2Topo3BodyBBDTDecision_TOS;
   Int_t           PsiHlt2Topo4BodyBBDTDecision_Dec;
   Int_t           PsiHlt2Topo4BodyBBDTDecision_TIS;
   Int_t           PsiHlt2Topo4BodyBBDTDecision_TOS;
   Int_t           PsiHlt2MuTrackDecision_Dec;
   Int_t           PsiHlt2MuTrackDecision_TIS;
   Int_t           PsiHlt2MuTrackDecision_TOS;
   Int_t           PsiHlt2MuTrackNoIPDecision_Dec;
   Int_t           PsiHlt2MuTrackNoIPDecision_TIS;
   Int_t           PsiHlt2MuTrackNoIPDecision_TOS;
   Int_t           PsiHlt2SingleMuonDecision_Dec;
   Int_t           PsiHlt2SingleMuonDecision_TIS;
   Int_t           PsiHlt2SingleMuonDecision_TOS;
   Int_t           PsiHlt2UnbiasedDiMuonDecision_Dec;
   Int_t           PsiHlt2UnbiasedDiMuonDecision_TIS;
   Int_t           PsiHlt2UnbiasedDiMuonDecision_TOS;
   Int_t           PsiHlt2UnbiasedDiMuonLowMassDecision_Dec;
   Int_t           PsiHlt2UnbiasedDiMuonLowMassDecision_TIS;
   Int_t           PsiHlt2UnbiasedDiMuonLowMassDecision_TOS;
   Int_t           PsiHlt2DiMuonUnbiasedJPsiDecision_Dec;
   Int_t           PsiHlt2DiMuonUnbiasedJPsiDecision_TIS;
   Int_t           PsiHlt2DiMuonUnbiasedJPsiDecision_TOS;
   Int_t           PsiHlt2DiMuonUnbiasedPsi2SDecision_Dec;
   Int_t           PsiHlt2DiMuonUnbiasedPsi2SDecision_TIS;
   Int_t           PsiHlt2DiMuonUnbiasedPsi2SDecision_TOS;
   Int_t           PsiHlt2BiasedDiMuonSimpleDecision_Dec;
   Int_t           PsiHlt2BiasedDiMuonSimpleDecision_TIS;
   Int_t           PsiHlt2BiasedDiMuonSimpleDecision_TOS;
   Int_t           PsiHlt2BiasedDiMuonRefinedDecision_Dec;
   Int_t           PsiHlt2BiasedDiMuonRefinedDecision_TIS;
   Int_t           PsiHlt2BiasedDiMuonRefinedDecision_TOS;
   Int_t           PsiHlt2BiasedDiMuonMassDecision_Dec;
   Int_t           PsiHlt2BiasedDiMuonMassDecision_TIS;
   Int_t           PsiHlt2BiasedDiMuonMassDecision_TOS;
   Int_t           PsiHlt2BiasedDiMuonIPDecision_Dec;
   Int_t           PsiHlt2BiasedDiMuonIPDecision_TIS;
   Int_t           PsiHlt2BiasedDiMuonIPDecision_TOS;
   Int_t           PsiHlt2DiMuonBiasedJPsiDecision_Dec;
   Int_t           PsiHlt2DiMuonBiasedJPsiDecision_TIS;
   Int_t           PsiHlt2DiMuonBiasedJPsiDecision_TOS;
   Int_t           PsiHlt2TopoMu2BodyBBDTDecision_Dec;
   Int_t           PsiHlt2TopoMu2BodyBBDTDecision_TIS;
   Int_t           PsiHlt2TopoMu2BodyBBDTDecision_TOS;
   Int_t           PsiHlt2TopoMu3BodyBBDTDecision_Dec;
   Int_t           PsiHlt2TopoMu3BodyBBDTDecision_TIS;
   Int_t           PsiHlt2TopoMu3BodyBBDTDecision_TOS;
   Int_t           PsiHlt2TopoMu4BodyBBDTDecision_Dec;
   Int_t           PsiHlt2TopoMu4BodyBBDTDecision_TIS;
   Int_t           PsiHlt2TopoMu4BodyBBDTDecision_TOS;
   Int_t           PsiHlt2SingleMuonHighPTDecision_Dec;
   Int_t           PsiHlt2SingleMuonHighPTDecision_TIS;
   Int_t           PsiHlt2SingleMuonHighPTDecision_TOS;
   Int_t           PsiHlt2SingleMuonLowPTDecision_Dec;
   Int_t           PsiHlt2SingleMuonLowPTDecision_TIS;
   Int_t           PsiHlt2SingleMuonLowPTDecision_TOS;
   Int_t           PsiHlt2DiMuonDecision_Dec;
   Int_t           PsiHlt2DiMuonDecision_TIS;
   Int_t           PsiHlt2DiMuonDecision_TOS;
   Int_t           PsiHlt2DiMuonLowMassDecision_Dec;
   Int_t           PsiHlt2DiMuonLowMassDecision_TIS;
   Int_t           PsiHlt2DiMuonLowMassDecision_TOS;
   Int_t           PsiHlt2DiMuonJPsiDecision_Dec;
   Int_t           PsiHlt2DiMuonJPsiDecision_TIS;
   Int_t           PsiHlt2DiMuonJPsiDecision_TOS;
   Int_t           PsiHlt2DiMuonJPsiHighPTDecision_Dec;
   Int_t           PsiHlt2DiMuonJPsiHighPTDecision_TIS;
   Int_t           PsiHlt2DiMuonJPsiHighPTDecision_TOS;
   Int_t           PsiHlt2DiMuonPsi2SDecision_Dec;
   Int_t           PsiHlt2DiMuonPsi2SDecision_TIS;
   Int_t           PsiHlt2DiMuonPsi2SDecision_TOS;
   Int_t           PsiHlt2DiMuonBDecision_Dec;
   Int_t           PsiHlt2DiMuonBDecision_TIS;
   Int_t           PsiHlt2DiMuonBDecision_TOS;
   Int_t           PsiHlt2DiMuonDetachedDecision_Dec;
   Int_t           PsiHlt2DiMuonDetachedDecision_TIS;
   Int_t           PsiHlt2DiMuonDetachedDecision_TOS;
   Int_t           PsiHlt2DiMuonDetachedHeavyDecision_Dec;
   Int_t           PsiHlt2DiMuonDetachedHeavyDecision_TIS;
   Int_t           PsiHlt2DiMuonDetachedHeavyDecision_TOS;
   Int_t           PsiHlt2DiMuonDetachedJPsiDecision_Dec;
   Int_t           PsiHlt2DiMuonDetachedJPsiDecision_TIS;
   Int_t           PsiHlt2DiMuonDetachedJPsiDecision_TOS;
   Int_t           PsiHlt2ExpressJPsiDecision_Dec;
   Int_t           PsiHlt2ExpressJPsiDecision_TIS;
   Int_t           PsiHlt2ExpressJPsiDecision_TOS;
   Int_t           Psi_NOPARTWITHINDCHI2WDW;
   Int_t           Psi_NOPARTWITHINCHI2WDW;
   Float_t         Psi_SMALLESTCHI2;
   Float_t         Psi_SMALLESTDELTACHI2;
   Float_t         muminus_MINIP;
   Float_t         muminus_MINIPCHI2;
   Float_t         muminus_MINIPNEXTBEST;
   Float_t         muminus_MINIPCHI2NEXTBEST;
   Float_t         muminus_OWNPV_X;
   Float_t         muminus_OWNPV_Y;
   Float_t         muminus_OWNPV_Z;
   Float_t         muminus_OWNPV_XERR;
   Float_t         muminus_OWNPV_YERR;
   Float_t         muminus_OWNPV_ZERR;
   Float_t         muminus_OWNPV_CHI2;
   Int_t           muminus_OWNPV_NDOF;
   Float_t         muminus_OWNPV_COV_[3][3];
   Float_t         muminus_IP_OWNPV;
   Float_t         muminus_IPCHI2_OWNPV;
   Float_t         muminus_ORIVX_X;
   Float_t         muminus_ORIVX_Y;
   Float_t         muminus_ORIVX_Z;
   Float_t         muminus_ORIVX_XERR;
   Float_t         muminus_ORIVX_YERR;
   Float_t         muminus_ORIVX_ZERR;
   Float_t         muminus_ORIVX_CHI2;
   Int_t           muminus_ORIVX_NDOF;
   Float_t         muminus_ORIVX_COV_[3][3];
   Float_t         muminus_P;
   Float_t         muminus_PT;
   Float_t         muminus_PE;
   Float_t         muminus_PX;
   Float_t         muminus_PY;
   Float_t         muminus_PZ;
   Float_t         muminus_M;
   Int_t           muminus_ID;
   Float_t         muminus_PIDe;
   Float_t         muminus_PIDmu;
   Float_t         muminus_PIDK;
   Float_t         muminus_PIDp;
   Float_t         muminus_ProbNNe;
   Float_t         muminus_ProbNNk;
   Float_t         muminus_ProbNNp;
   Float_t         muminus_ProbNNpi;
   Float_t         muminus_ProbNNmu;
   Float_t         muminus_ProbNNghost;
   Float_t         muminus_CaloEcalE;
   Float_t         muminus_CaloHcalE;
   Int_t           muminus_hasMuon;
   Int_t           muminus_isMuon;
   Int_t           muminus_hasRich;
   Int_t           muminus_hasCalo;
   Int_t           muminus_TRACK_Type;
   Int_t           muminus_TRACK_Key;
   Float_t         muminus_TRACK_CHI2NDOF;
   Float_t         muminus_TRACK_PCHI2;
   Float_t         muminus_TRACK_GhostProb;
   Float_t         muminus_TRACK_CloneDist;
   Float_t         muplus_MINIP;
   Float_t         muplus_MINIPCHI2;
   Float_t         muplus_MINIPNEXTBEST;
   Float_t         muplus_MINIPCHI2NEXTBEST;
   Float_t         muplus_OWNPV_X;
   Float_t         muplus_OWNPV_Y;
   Float_t         muplus_OWNPV_Z;
   Float_t         muplus_OWNPV_XERR;
   Float_t         muplus_OWNPV_YERR;
   Float_t         muplus_OWNPV_ZERR;
   Float_t         muplus_OWNPV_CHI2;
   Int_t           muplus_OWNPV_NDOF;
   Float_t         muplus_OWNPV_COV_[3][3];
   Float_t         muplus_IP_OWNPV;
   Float_t         muplus_IPCHI2_OWNPV;
   Float_t         muplus_ORIVX_X;
   Float_t         muplus_ORIVX_Y;
   Float_t         muplus_ORIVX_Z;
   Float_t         muplus_ORIVX_XERR;
   Float_t         muplus_ORIVX_YERR;
   Float_t         muplus_ORIVX_ZERR;
   Float_t         muplus_ORIVX_CHI2;
   Int_t           muplus_ORIVX_NDOF;
   Float_t         muplus_ORIVX_COV_[3][3];
   Float_t         muplus_P;
   Float_t         muplus_PT;
   Float_t         muplus_PE;
   Float_t         muplus_PX;
   Float_t         muplus_PY;
   Float_t         muplus_PZ;
   Float_t         muplus_M;
   Int_t           muplus_ID;
   Float_t         muplus_PIDe;
   Float_t         muplus_PIDmu;
   Float_t         muplus_PIDK;
   Float_t         muplus_PIDp;
   Float_t         muplus_ProbNNe;
   Float_t         muplus_ProbNNk;
   Float_t         muplus_ProbNNp;
   Float_t         muplus_ProbNNpi;
   Float_t         muplus_ProbNNmu;
   Float_t         muplus_ProbNNghost;
   Float_t         muplus_CaloEcalE;
   Float_t         muplus_CaloHcalE;
   Int_t           muplus_hasMuon;
   Int_t           muplus_isMuon;
   Int_t           muplus_hasRich;
   Int_t           muplus_hasCalo;
   Int_t           muplus_TRACK_Type;
   Int_t           muplus_TRACK_Key;
   Float_t         muplus_TRACK_CHI2NDOF;
   Float_t         muplus_TRACK_PCHI2;
   Float_t         muplus_TRACK_GhostProb;
   Float_t         muplus_TRACK_CloneDist;
   Int_t           nCandidate;
   Int_t           totCandidates;
   ULong64_t           EventInSequence;
   Int_t           runNumber;
   ULong64_t       eventNumber;
   Int_t           BCID;
   Int_t           BCType;
   Int_t           OdinTCK;
   Int_t           L0DUTCK;
   Int_t           HLTTCK;
   ULong64_t         GpsTime;
   Int_t           GpsYear;
   Int_t           GpsMonth;
   Int_t           GpsDay;
   Int_t           GpsHour;
   Int_t           GpsMinute;
   Float_t         GpsSecond;
   Int_t           Primaries;
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
   Int_t           ChargedProtos;
   Int_t           NeutralProtos;
   Int_t           BestTracks;
   Int_t           MuonTracks;
   Int_t           ITClusters;
   Int_t           VeloLiteClusters;
   Int_t           OTClusters;
   Int_t           spdMult;
   Int_t           backwardTracks;
   Int_t           veloTracks;
   Int_t           longTracks;
   Int_t           goodLongTracks;

// ####################################################################################################

   // List of branches
   TBranch        *b_B_MINIP;   //!
   TBranch        *b_B_MINIPCHI2;   //!
   TBranch        *b_B_MINIPNEXTBEST;   //!
   TBranch        *b_B_MINIPCHI2NEXTBEST;   //!
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
   TBranch        *b_B_ENDVERTEX_X;   //!
   TBranch        *b_B_ENDVERTEX_Y;   //!
   TBranch        *b_B_ENDVERTEX_Z;   //!
   TBranch        *b_B_ENDVERTEX_XERR;   //!
   TBranch        *b_B_ENDVERTEX_YERR;   //!
   TBranch        *b_B_ENDVERTEX_ZERR;   //!
   TBranch        *b_B_ENDVERTEX_CHI2;   //!
   TBranch        *b_B_ENDVERTEX_NDOF;   //!
   TBranch        *b_B_ENDVERTEX_COV_;   //!
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
   TBranch        *b_B_Fit_nPV;   //!
   TBranch        *b_B_Fit_M;   //!
   TBranch        *b_B_Fit_MERR;   //!
   TBranch        *b_B_Fit_P;   //!
   TBranch        *b_B_Fit_PERR;   //!
   TBranch        *b_B_Fit_chi2_B;   //!
   TBranch        *b_B_Fit_chi2;   //!
   TBranch        *b_B_Fit_nDOF;   //!
   TBranch        *b_B_Fit_nIter;   //!
   TBranch        *b_B_Fit_status;   //!
   TBranch        *b_B_FullFit_nPV;   //!
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
   TBranch        *b_B_FullFit_PV_sumPT;   //!
   TBranch        *b_B_FullFit_chi2_B;   //!
   TBranch        *b_B_FullFit_chi2;   //!
   TBranch        *b_B_FullFit_ctau;   //!
   TBranch        *b_B_FullFit_ctauErr;   //!
   TBranch        *b_B_FullFit_decayLength;   //!
   TBranch        *b_B_FullFit_decayLengthErr;   //!
   TBranch        *b_B_FullFit_nDOF;   //!
   TBranch        *b_B_FullFit_nIter;   //!
   TBranch        *b_B_FullFit_phi_1020_ctau;   //!
   TBranch        *b_B_FullFit_phi_1020_ctauErr;   //!
   TBranch        *b_B_FullFit_phi_1020_decayLength;   //!
   TBranch        *b_B_FullFit_phi_1020_decayLengthErr;   //!
   TBranch        *b_B_FullFit_status;   //!
   TBranch        *b_B_MassFit_nPV;   //!
   TBranch        *b_B_MassFit_M;   //!
   TBranch        *b_B_MassFit_MERR;   //!
   TBranch        *b_B_MassFit_P;   //!
   TBranch        *b_B_MassFit_PERR;   //!
   TBranch        *b_B_MassFit_chi2_B;   //!
   TBranch        *b_B_MassFit_chi2;   //!
   TBranch        *b_B_MassFit_nDOF;   //!
   TBranch        *b_B_MassFit_nIter;   //!
   TBranch        *b_B_MassFit_status;   //!
   TBranch        *b_B_NoKsFit_nPV;   //!
   TBranch        *b_B_NoKsFit_J_psi_1S_ctau;   //!
   TBranch        *b_B_NoKsFit_J_psi_1S_ctauErr;   //!
   TBranch        *b_B_NoKsFit_J_psi_1S_decayLength;   //!
   TBranch        *b_B_NoKsFit_J_psi_1S_decayLengthErr;   //!
   TBranch        *b_B_NoKsFit_M;   //!
   TBranch        *b_B_NoKsFit_MERR;   //!
   TBranch        *b_B_NoKsFit_P;   //!
   TBranch        *b_B_NoKsFit_PERR;   //!
   TBranch        *b_B_NoKsFit_PV_X;   //!
   TBranch        *b_B_NoKsFit_PV_Y;   //!
   TBranch        *b_B_NoKsFit_PV_Z;   //!
   TBranch        *b_B_NoKsFit_PV_key;   //!
   TBranch        *b_B_NoKsFit_PV_sumPT;   //!
   TBranch        *b_B_NoKsFit_chi2_B;   //!
   TBranch        *b_B_NoKsFit_chi2;   //!
   TBranch        *b_B_NoKsFit_ctau;   //!
   TBranch        *b_B_NoKsFit_ctauErr;   //!
   TBranch        *b_B_NoKsFit_decayLength;   //!
   TBranch        *b_B_NoKsFit_decayLengthErr;   //!
   TBranch        *b_B_NoKsFit_nDOF;   //!
   TBranch        *b_B_NoKsFit_nIter;   //!
   TBranch        *b_B_NoKsFit_phi_1020_ctau;   //!
   TBranch        *b_B_NoKsFit_phi_1020_ctauErr;   //!
   TBranch        *b_B_NoKsFit_phi_1020_decayLength;   //!
   TBranch        *b_B_NoKsFit_phi_1020_decayLengthErr;   //!
   TBranch        *b_B_NoKsFit_status;   //!
   TBranch        *b_B_PVFit_nPV;   //!
   TBranch        *b_B_PVFit_M;   //!
   TBranch        *b_B_PVFit_MERR;   //!
   TBranch        *b_B_PVFit_P;   //!
   TBranch        *b_B_PVFit_PERR;   //!
   TBranch        *b_B_PVFit_chi2_B;   //!
   TBranch        *b_B_PVFit_chi2;   //!
   TBranch        *b_B_PVFit_nDOF;   //!
   TBranch        *b_B_PVFit_nIter;   //!
   TBranch        *b_B_PVFit_status;   //!
   TBranch        *b_BL0Global_Dec;   //!
   TBranch        *b_BL0Global_TIS;   //!
   TBranch        *b_BL0Global_TOS;   //!
   TBranch        *b_BHlt1Global_Dec;   //!
   TBranch        *b_BHlt1Global_TIS;   //!
   TBranch        *b_BHlt1Global_TOS;   //!
   TBranch        *b_BHlt2Global_Dec;   //!
   TBranch        *b_BHlt2Global_TIS;   //!
   TBranch        *b_BHlt2Global_TOS;   //!
   TBranch        *b_BHlt1TrackAllL0Decision_Dec;   //!
   TBranch        *b_BHlt1TrackAllL0Decision_TIS;   //!
   TBranch        *b_BHlt1TrackAllL0Decision_TOS;   //!
   TBranch        *b_BHlt1MuTrackDecision_Dec;   //!
   TBranch        *b_BHlt1MuTrackDecision_TIS;   //!
   TBranch        *b_BHlt1MuTrackDecision_TOS;   //!
   TBranch        *b_BHlt1DiMuonNoIP2L0Decision_Dec;   //!
   TBranch        *b_BHlt1DiMuonNoIP2L0Decision_TIS;   //!
   TBranch        *b_BHlt1DiMuonNoIP2L0Decision_TOS;   //!
   TBranch        *b_BHlt1DiMuonNoIPL0SegDecision_Dec;   //!
   TBranch        *b_BHlt1DiMuonNoIPL0SegDecision_TIS;   //!
   TBranch        *b_BHlt1DiMuonNoIPL0SegDecision_TOS;   //!
   TBranch        *b_BHlt1DiMuonIPCL0DiDecision_Dec;   //!
   TBranch        *b_BHlt1DiMuonIPCL0DiDecision_TIS;   //!
   TBranch        *b_BHlt1DiMuonIPCL0DiDecision_TOS;   //!
   TBranch        *b_BHlt1DiMuonIPC2L0Decision_Dec;   //!
   TBranch        *b_BHlt1DiMuonIPC2L0Decision_TIS;   //!
   TBranch        *b_BHlt1DiMuonIPC2L0Decision_TOS;   //!
   TBranch        *b_BHlt1DiMuonIPCL0SegDecision_Dec;   //!
   TBranch        *b_BHlt1DiMuonIPCL0SegDecision_TIS;   //!
   TBranch        *b_BHlt1DiMuonIPCL0SegDecision_TOS;   //!
   TBranch        *b_BHlt1DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_BHlt1DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_BHlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_BHlt1DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_BHlt1DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_BHlt1DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_BHlt1SingleMuonNoIPL0Decision_Dec;   //!
   TBranch        *b_BHlt1SingleMuonNoIPL0Decision_TIS;   //!
   TBranch        *b_BHlt1SingleMuonNoIPL0Decision_TOS;   //!
   TBranch        *b_BHlt1SingleMuonNoIPL0HighPTDecision_Dec;   //!
   TBranch        *b_BHlt1SingleMuonNoIPL0HighPTDecision_TIS;   //!
   TBranch        *b_BHlt1SingleMuonNoIPL0HighPTDecision_TOS;   //!
   TBranch        *b_BHlt1SingleMuonIPCL0Decision_Dec;   //!
   TBranch        *b_BHlt1SingleMuonIPCL0Decision_TIS;   //!
   TBranch        *b_BHlt1SingleMuonIPCL0Decision_TOS;   //!
   TBranch        *b_BHlt1SingleMuonNoIPDecision_Dec;   //!
   TBranch        *b_BHlt1SingleMuonNoIPDecision_TIS;   //!
   TBranch        *b_BHlt1SingleMuonNoIPDecision_TOS;   //!
   TBranch        *b_BHlt1TrackMuonDecision_Dec;   //!
   TBranch        *b_BHlt1TrackMuonDecision_TIS;   //!
   TBranch        *b_BHlt1TrackMuonDecision_TOS;   //!
   TBranch        *b_BHlt2TopoTF3BodyReq2YesDecision_Dec;   //!
   TBranch        *b_BHlt2TopoTF3BodyReq2YesDecision_TIS;   //!
   TBranch        *b_BHlt2TopoTF3BodyReq2YesDecision_TOS;   //!
   TBranch        *b_BHlt2TopoTF3BodyReq3YesDecision_Dec;   //!
   TBranch        *b_BHlt2TopoTF3BodyReq3YesDecision_TIS;   //!
   TBranch        *b_BHlt2TopoTF3BodyReq3YesDecision_TOS;   //!
   TBranch        *b_BHlt2TopoOSTF2BodyDecision_Dec;   //!
   TBranch        *b_BHlt2TopoOSTF2BodyDecision_TIS;   //!
   TBranch        *b_BHlt2TopoOSTF2BodyDecision_TOS;   //!
   TBranch        *b_BHlt2TopoOSTF3BodyDecision_Dec;   //!
   TBranch        *b_BHlt2TopoOSTF3BodyDecision_TIS;   //!
   TBranch        *b_BHlt2TopoOSTF3BodyDecision_TOS;   //!
   TBranch        *b_BHlt2TopoOSTF4BodyDecision_Dec;   //!
   TBranch        *b_BHlt2TopoOSTF4BodyDecision_TIS;   //!
   TBranch        *b_BHlt2TopoOSTF4BodyDecision_TOS;   //!
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
   TBranch        *b_BHlt2MuTrackDecision_Dec;   //!
   TBranch        *b_BHlt2MuTrackDecision_TIS;   //!
   TBranch        *b_BHlt2MuTrackDecision_TOS;   //!
   TBranch        *b_BHlt2MuTrackNoIPDecision_Dec;   //!
   TBranch        *b_BHlt2MuTrackNoIPDecision_TIS;   //!
   TBranch        *b_BHlt2MuTrackNoIPDecision_TOS;   //!
   TBranch        *b_BHlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_BHlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_BHlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_BHlt2UnbiasedDiMuonDecision_Dec;   //!
   TBranch        *b_BHlt2UnbiasedDiMuonDecision_TIS;   //!
   TBranch        *b_BHlt2UnbiasedDiMuonDecision_TOS;   //!
   TBranch        *b_BHlt2UnbiasedDiMuonLowMassDecision_Dec;   //!
   TBranch        *b_BHlt2UnbiasedDiMuonLowMassDecision_TIS;   //!
   TBranch        *b_BHlt2UnbiasedDiMuonLowMassDecision_TOS;   //!
   TBranch        *b_BHlt2DiMuonUnbiasedJPsiDecision_Dec;   //!
   TBranch        *b_BHlt2DiMuonUnbiasedJPsiDecision_TIS;   //!
   TBranch        *b_BHlt2DiMuonUnbiasedJPsiDecision_TOS;   //!
   TBranch        *b_BHlt2DiMuonUnbiasedPsi2SDecision_Dec;   //!
   TBranch        *b_BHlt2DiMuonUnbiasedPsi2SDecision_TIS;   //!
   TBranch        *b_BHlt2DiMuonUnbiasedPsi2SDecision_TOS;   //!
   TBranch        *b_BHlt2BiasedDiMuonSimpleDecision_Dec;   //!
   TBranch        *b_BHlt2BiasedDiMuonSimpleDecision_TIS;   //!
   TBranch        *b_BHlt2BiasedDiMuonSimpleDecision_TOS;   //!
   TBranch        *b_BHlt2BiasedDiMuonRefinedDecision_Dec;   //!
   TBranch        *b_BHlt2BiasedDiMuonRefinedDecision_TIS;   //!
   TBranch        *b_BHlt2BiasedDiMuonRefinedDecision_TOS;   //!
   TBranch        *b_BHlt2BiasedDiMuonMassDecision_Dec;   //!
   TBranch        *b_BHlt2BiasedDiMuonMassDecision_TIS;   //!
   TBranch        *b_BHlt2BiasedDiMuonMassDecision_TOS;   //!
   TBranch        *b_BHlt2BiasedDiMuonIPDecision_Dec;   //!
   TBranch        *b_BHlt2BiasedDiMuonIPDecision_TIS;   //!
   TBranch        *b_BHlt2BiasedDiMuonIPDecision_TOS;   //!
   TBranch        *b_BHlt2DiMuonBiasedJPsiDecision_Dec;   //!
   TBranch        *b_BHlt2DiMuonBiasedJPsiDecision_TIS;   //!
   TBranch        *b_BHlt2DiMuonBiasedJPsiDecision_TOS;   //!
   TBranch        *b_BHlt2TopoMu2BodyBBDTDecision_Dec;   //!
   TBranch        *b_BHlt2TopoMu2BodyBBDTDecision_TIS;   //!
   TBranch        *b_BHlt2TopoMu2BodyBBDTDecision_TOS;   //!
   TBranch        *b_BHlt2TopoMu3BodyBBDTDecision_Dec;   //!
   TBranch        *b_BHlt2TopoMu3BodyBBDTDecision_TIS;   //!
   TBranch        *b_BHlt2TopoMu3BodyBBDTDecision_TOS;   //!
   TBranch        *b_BHlt2TopoMu4BodyBBDTDecision_Dec;   //!
   TBranch        *b_BHlt2TopoMu4BodyBBDTDecision_TIS;   //!
   TBranch        *b_BHlt2TopoMu4BodyBBDTDecision_TOS;   //!
   TBranch        *b_BHlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_BHlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_BHlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_BHlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_BHlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_BHlt2SingleMuonLowPTDecision_TOS;   //!
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
   TBranch        *b_phi_1020_MINIP;   //!
   TBranch        *b_phi_1020_MINIPCHI2;   //!
   TBranch        *b_phi_1020_MINIPNEXTBEST;   //!
   TBranch        *b_phi_1020_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_phi_1020_OWNPV_X;   //!
   TBranch        *b_phi_1020_OWNPV_Y;   //!
   TBranch        *b_phi_1020_OWNPV_Z;   //!
   TBranch        *b_phi_1020_OWNPV_XERR;   //!
   TBranch        *b_phi_1020_OWNPV_YERR;   //!
   TBranch        *b_phi_1020_OWNPV_ZERR;   //!
   TBranch        *b_phi_1020_OWNPV_CHI2;   //!
   TBranch        *b_phi_1020_OWNPV_NDOF;   //!
   TBranch        *b_phi_1020_OWNPV_COV_;   //!
   TBranch        *b_phi_1020_IP_OWNPV;   //!
   TBranch        *b_phi_1020_IPCHI2_OWNPV;   //!
   TBranch        *b_phi_1020_FD_OWNPV;   //!
   TBranch        *b_phi_1020_FDCHI2_OWNPV;   //!
   TBranch        *b_phi_1020_DIRA_OWNPV;   //!
   TBranch        *b_phi_1020_ORIVX_X;   //!
   TBranch        *b_phi_1020_ORIVX_Y;   //!
   TBranch        *b_phi_1020_ORIVX_Z;   //!
   TBranch        *b_phi_1020_ORIVX_XERR;   //!
   TBranch        *b_phi_1020_ORIVX_YERR;   //!
   TBranch        *b_phi_1020_ORIVX_ZERR;   //!
   TBranch        *b_phi_1020_ORIVX_CHI2;   //!
   TBranch        *b_phi_1020_ORIVX_NDOF;   //!
   TBranch        *b_phi_1020_ORIVX_COV_;   //!
   TBranch        *b_phi_1020_FD_ORIVX;   //!
   TBranch        *b_phi_1020_FDCHI2_ORIVX;   //!
   TBranch        *b_phi_1020_DIRA_ORIVX;   //!
   TBranch        *b_phi_1020_ENDVERTEX_X;   //!
   TBranch        *b_phi_1020_ENDVERTEX_Y;   //!
   TBranch        *b_phi_1020_ENDVERTEX_Z;   //!
   TBranch        *b_phi_1020_ENDVERTEX_XERR;   //!
   TBranch        *b_phi_1020_ENDVERTEX_YERR;   //!
   TBranch        *b_phi_1020_ENDVERTEX_ZERR;   //!
   TBranch        *b_phi_1020_ENDVERTEX_CHI2;   //!
   TBranch        *b_phi_1020_ENDVERTEX_NDOF;   //!
   TBranch        *b_phi_1020_ENDVERTEX_COV_;   //!
   TBranch        *b_phi_1020_P;   //!
   TBranch        *b_phi_1020_PT;   //!
   TBranch        *b_phi_1020_PE;   //!
   TBranch        *b_phi_1020_PX;   //!
   TBranch        *b_phi_1020_PY;   //!
   TBranch        *b_phi_1020_PZ;   //!
   TBranch        *b_phi_1020_MM;   //!
   TBranch        *b_phi_1020_MMERR;   //!
   TBranch        *b_phi_1020_M;   //!
   TBranch        *b_phi_1020_ID;   //!
   TBranch        *b_phi_1020_TAU;   //!
   TBranch        *b_phi_1020_TAUERR;   //!
   TBranch        *b_phi_1020_TAUCHI2;   //!
   TBranch        *b_Kminus_MINIP;   //!
   TBranch        *b_Kminus_MINIPCHI2;   //!
   TBranch        *b_Kminus_MINIPNEXTBEST;   //!
   TBranch        *b_Kminus_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_Kminus_OWNPV_X;   //!
   TBranch        *b_Kminus_OWNPV_Y;   //!
   TBranch        *b_Kminus_OWNPV_Z;   //!
   TBranch        *b_Kminus_OWNPV_XERR;   //!
   TBranch        *b_Kminus_OWNPV_YERR;   //!
   TBranch        *b_Kminus_OWNPV_ZERR;   //!
   TBranch        *b_Kminus_OWNPV_CHI2;   //!
   TBranch        *b_Kminus_OWNPV_NDOF;   //!
   TBranch        *b_Kminus_OWNPV_COV_;   //!
   TBranch        *b_Kminus_IP_OWNPV;   //!
   TBranch        *b_Kminus_IPCHI2_OWNPV;   //!
   TBranch        *b_Kminus_ORIVX_X;   //!
   TBranch        *b_Kminus_ORIVX_Y;   //!
   TBranch        *b_Kminus_ORIVX_Z;   //!
   TBranch        *b_Kminus_ORIVX_XERR;   //!
   TBranch        *b_Kminus_ORIVX_YERR;   //!
   TBranch        *b_Kminus_ORIVX_ZERR;   //!
   TBranch        *b_Kminus_ORIVX_CHI2;   //!
   TBranch        *b_Kminus_ORIVX_NDOF;   //!
   TBranch        *b_Kminus_ORIVX_COV_;   //!
   TBranch        *b_Kminus_P;   //!
   TBranch        *b_Kminus_PT;   //!
   TBranch        *b_Kminus_PE;   //!
   TBranch        *b_Kminus_PX;   //!
   TBranch        *b_Kminus_PY;   //!
   TBranch        *b_Kminus_PZ;   //!
   TBranch        *b_Kminus_M;   //!
   TBranch        *b_Kminus_ID;   //!
   TBranch        *b_Kminus_PIDe;   //!
   TBranch        *b_Kminus_PIDmu;   //!
   TBranch        *b_Kminus_PIDK;   //!
   TBranch        *b_Kminus_PIDp;   //!
   TBranch        *b_Kminus_ProbNNe;   //!
   TBranch        *b_Kminus_ProbNNk;   //!
   TBranch        *b_Kminus_ProbNNp;   //!
   TBranch        *b_Kminus_ProbNNpi;   //!
   TBranch        *b_Kminus_ProbNNmu;   //!
   TBranch        *b_Kminus_ProbNNghost;   //!
   TBranch        *b_Kminus_CaloEcalE;   //!
   TBranch        *b_Kminus_CaloHcalE;   //!
   TBranch        *b_Kminus_hasMuon;   //!
   TBranch        *b_Kminus_isMuon;   //!
   TBranch        *b_Kminus_hasRich;   //!
   TBranch        *b_Kminus_hasCalo;   //!
   TBranch        *b_Kminus_TRACK_Type;   //!
   TBranch        *b_Kminus_TRACK_Key;   //!
   TBranch        *b_Kminus_TRACK_CHI2NDOF;   //!
   TBranch        *b_Kminus_TRACK_PCHI2;   //!
   TBranch        *b_Kminus_TRACK_GhostProb;   //!
   TBranch        *b_Kminus_TRACK_CloneDist;   //!
   TBranch        *b_Kplus_MINIP;   //!
   TBranch        *b_Kplus_MINIPCHI2;   //!
   TBranch        *b_Kplus_MINIPNEXTBEST;   //!
   TBranch        *b_Kplus_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_Kplus_OWNPV_X;   //!
   TBranch        *b_Kplus_OWNPV_Y;   //!
   TBranch        *b_Kplus_OWNPV_Z;   //!
   TBranch        *b_Kplus_OWNPV_XERR;   //!
   TBranch        *b_Kplus_OWNPV_YERR;   //!
   TBranch        *b_Kplus_OWNPV_ZERR;   //!
   TBranch        *b_Kplus_OWNPV_CHI2;   //!
   TBranch        *b_Kplus_OWNPV_NDOF;   //!
   TBranch        *b_Kplus_OWNPV_COV_;   //!
   TBranch        *b_Kplus_IP_OWNPV;   //!
   TBranch        *b_Kplus_IPCHI2_OWNPV;   //!
   TBranch        *b_Kplus_ORIVX_X;   //!
   TBranch        *b_Kplus_ORIVX_Y;   //!
   TBranch        *b_Kplus_ORIVX_Z;   //!
   TBranch        *b_Kplus_ORIVX_XERR;   //!
   TBranch        *b_Kplus_ORIVX_YERR;   //!
   TBranch        *b_Kplus_ORIVX_ZERR;   //!
   TBranch        *b_Kplus_ORIVX_CHI2;   //!
   TBranch        *b_Kplus_ORIVX_NDOF;   //!
   TBranch        *b_Kplus_ORIVX_COV_;   //!
   TBranch        *b_Kplus_P;   //!
   TBranch        *b_Kplus_PT;   //!
   TBranch        *b_Kplus_PE;   //!
   TBranch        *b_Kplus_PX;   //!
   TBranch        *b_Kplus_PY;   //!
   TBranch        *b_Kplus_PZ;   //!
   TBranch        *b_Kplus_M;   //!
   TBranch        *b_Kplus_ID;   //!
   TBranch        *b_Kplus_PIDe;   //!
   TBranch        *b_Kplus_PIDmu;   //!
   TBranch        *b_Kplus_PIDK;   //!
   TBranch        *b_Kplus_PIDp;   //!
   TBranch        *b_Kplus_ProbNNe;   //!
   TBranch        *b_Kplus_ProbNNk;   //!
   TBranch        *b_Kplus_ProbNNp;   //!
   TBranch        *b_Kplus_ProbNNpi;   //!
   TBranch        *b_Kplus_ProbNNmu;   //!
   TBranch        *b_Kplus_ProbNNghost;   //!
   TBranch        *b_Kplus_CaloEcalE;   //!
   TBranch        *b_Kplus_CaloHcalE;   //!
   TBranch        *b_Kplus_hasMuon;   //!
   TBranch        *b_Kplus_isMuon;   //!
   TBranch        *b_Kplus_hasRich;   //!
   TBranch        *b_Kplus_hasCalo;   //!
   TBranch        *b_Kplus_TRACK_Type;   //!
   TBranch        *b_Kplus_TRACK_Key;   //!
   TBranch        *b_Kplus_TRACK_CHI2NDOF;   //!
   TBranch        *b_Kplus_TRACK_PCHI2;   //!
   TBranch        *b_Kplus_TRACK_GhostProb;   //!
   TBranch        *b_Kplus_TRACK_CloneDist;   //!
   TBranch        *b_Psi_MINIP;   //!
   TBranch        *b_Psi_MINIPCHI2;   //!
   TBranch        *b_Psi_MINIPNEXTBEST;   //!
   TBranch        *b_Psi_MINIPCHI2NEXTBEST;   //!
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
   TBranch        *b_Psi_ENDVERTEX_X;   //!
   TBranch        *b_Psi_ENDVERTEX_Y;   //!
   TBranch        *b_Psi_ENDVERTEX_Z;   //!
   TBranch        *b_Psi_ENDVERTEX_XERR;   //!
   TBranch        *b_Psi_ENDVERTEX_YERR;   //!
   TBranch        *b_Psi_ENDVERTEX_ZERR;   //!
   TBranch        *b_Psi_ENDVERTEX_CHI2;   //!
   TBranch        *b_Psi_ENDVERTEX_NDOF;   //!
   TBranch        *b_Psi_ENDVERTEX_COV_;   //!
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
   TBranch        *b_PsiL0Global_Dec;   //!
   TBranch        *b_PsiL0Global_TIS;   //!
   TBranch        *b_PsiL0Global_TOS;   //!
   TBranch        *b_PsiHlt1Global_Dec;   //!
   TBranch        *b_PsiHlt1Global_TIS;   //!
   TBranch        *b_PsiHlt1Global_TOS;   //!
   TBranch        *b_PsiHlt2Global_Dec;   //!
   TBranch        *b_PsiHlt2Global_TIS;   //!
   TBranch        *b_PsiHlt2Global_TOS;   //!
   TBranch        *b_PsiHlt1TrackAllL0Decision_Dec;   //!
   TBranch        *b_PsiHlt1TrackAllL0Decision_TIS;   //!
   TBranch        *b_PsiHlt1TrackAllL0Decision_TOS;   //!
   TBranch        *b_PsiHlt1MuTrackDecision_Dec;   //!
   TBranch        *b_PsiHlt1MuTrackDecision_TIS;   //!
   TBranch        *b_PsiHlt1MuTrackDecision_TOS;   //!
   TBranch        *b_PsiHlt1DiMuonNoIP2L0Decision_Dec;   //!
   TBranch        *b_PsiHlt1DiMuonNoIP2L0Decision_TIS;   //!
   TBranch        *b_PsiHlt1DiMuonNoIP2L0Decision_TOS;   //!
   TBranch        *b_PsiHlt1DiMuonNoIPL0SegDecision_Dec;   //!
   TBranch        *b_PsiHlt1DiMuonNoIPL0SegDecision_TIS;   //!
   TBranch        *b_PsiHlt1DiMuonNoIPL0SegDecision_TOS;   //!
   TBranch        *b_PsiHlt1DiMuonIPCL0DiDecision_Dec;   //!
   TBranch        *b_PsiHlt1DiMuonIPCL0DiDecision_TIS;   //!
   TBranch        *b_PsiHlt1DiMuonIPCL0DiDecision_TOS;   //!
   TBranch        *b_PsiHlt1DiMuonIPC2L0Decision_Dec;   //!
   TBranch        *b_PsiHlt1DiMuonIPC2L0Decision_TIS;   //!
   TBranch        *b_PsiHlt1DiMuonIPC2L0Decision_TOS;   //!
   TBranch        *b_PsiHlt1DiMuonIPCL0SegDecision_Dec;   //!
   TBranch        *b_PsiHlt1DiMuonIPCL0SegDecision_TIS;   //!
   TBranch        *b_PsiHlt1DiMuonIPCL0SegDecision_TOS;   //!
   TBranch        *b_PsiHlt1DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_PsiHlt1DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_PsiHlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_PsiHlt1DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_PsiHlt1DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_PsiHlt1DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_PsiHlt1SingleMuonNoIPL0Decision_Dec;   //!
   TBranch        *b_PsiHlt1SingleMuonNoIPL0Decision_TIS;   //!
   TBranch        *b_PsiHlt1SingleMuonNoIPL0Decision_TOS;   //!
   TBranch        *b_PsiHlt1SingleMuonNoIPL0HighPTDecision_Dec;   //!
   TBranch        *b_PsiHlt1SingleMuonNoIPL0HighPTDecision_TIS;   //!
   TBranch        *b_PsiHlt1SingleMuonNoIPL0HighPTDecision_TOS;   //!
   TBranch        *b_PsiHlt1SingleMuonIPCL0Decision_Dec;   //!
   TBranch        *b_PsiHlt1SingleMuonIPCL0Decision_TIS;   //!
   TBranch        *b_PsiHlt1SingleMuonIPCL0Decision_TOS;   //!
   TBranch        *b_PsiHlt1SingleMuonNoIPDecision_Dec;   //!
   TBranch        *b_PsiHlt1SingleMuonNoIPDecision_TIS;   //!
   TBranch        *b_PsiHlt1SingleMuonNoIPDecision_TOS;   //!
   TBranch        *b_PsiHlt1TrackMuonDecision_Dec;   //!
   TBranch        *b_PsiHlt1TrackMuonDecision_TIS;   //!
   TBranch        *b_PsiHlt1TrackMuonDecision_TOS;   //!
   TBranch        *b_PsiHlt2TopoTF3BodyReq2YesDecision_Dec;   //!
   TBranch        *b_PsiHlt2TopoTF3BodyReq2YesDecision_TIS;   //!
   TBranch        *b_PsiHlt2TopoTF3BodyReq2YesDecision_TOS;   //!
   TBranch        *b_PsiHlt2TopoTF3BodyReq3YesDecision_Dec;   //!
   TBranch        *b_PsiHlt2TopoTF3BodyReq3YesDecision_TIS;   //!
   TBranch        *b_PsiHlt2TopoTF3BodyReq3YesDecision_TOS;   //!
   TBranch        *b_PsiHlt2TopoOSTF2BodyDecision_Dec;   //!
   TBranch        *b_PsiHlt2TopoOSTF2BodyDecision_TIS;   //!
   TBranch        *b_PsiHlt2TopoOSTF2BodyDecision_TOS;   //!
   TBranch        *b_PsiHlt2TopoOSTF3BodyDecision_Dec;   //!
   TBranch        *b_PsiHlt2TopoOSTF3BodyDecision_TIS;   //!
   TBranch        *b_PsiHlt2TopoOSTF3BodyDecision_TOS;   //!
   TBranch        *b_PsiHlt2TopoOSTF4BodyDecision_Dec;   //!
   TBranch        *b_PsiHlt2TopoOSTF4BodyDecision_TIS;   //!
   TBranch        *b_PsiHlt2TopoOSTF4BodyDecision_TOS;   //!
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
   TBranch        *b_PsiHlt2MuTrackDecision_Dec;   //!
   TBranch        *b_PsiHlt2MuTrackDecision_TIS;   //!
   TBranch        *b_PsiHlt2MuTrackDecision_TOS;   //!
   TBranch        *b_PsiHlt2MuTrackNoIPDecision_Dec;   //!
   TBranch        *b_PsiHlt2MuTrackNoIPDecision_TIS;   //!
   TBranch        *b_PsiHlt2MuTrackNoIPDecision_TOS;   //!
   TBranch        *b_PsiHlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_PsiHlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_PsiHlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_PsiHlt2UnbiasedDiMuonDecision_Dec;   //!
   TBranch        *b_PsiHlt2UnbiasedDiMuonDecision_TIS;   //!
   TBranch        *b_PsiHlt2UnbiasedDiMuonDecision_TOS;   //!
   TBranch        *b_PsiHlt2UnbiasedDiMuonLowMassDecision_Dec;   //!
   TBranch        *b_PsiHlt2UnbiasedDiMuonLowMassDecision_TIS;   //!
   TBranch        *b_PsiHlt2UnbiasedDiMuonLowMassDecision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonUnbiasedJPsiDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonUnbiasedJPsiDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonUnbiasedJPsiDecision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonUnbiasedPsi2SDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonUnbiasedPsi2SDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonUnbiasedPsi2SDecision_TOS;   //!
   TBranch        *b_PsiHlt2BiasedDiMuonSimpleDecision_Dec;   //!
   TBranch        *b_PsiHlt2BiasedDiMuonSimpleDecision_TIS;   //!
   TBranch        *b_PsiHlt2BiasedDiMuonSimpleDecision_TOS;   //!
   TBranch        *b_PsiHlt2BiasedDiMuonRefinedDecision_Dec;   //!
   TBranch        *b_PsiHlt2BiasedDiMuonRefinedDecision_TIS;   //!
   TBranch        *b_PsiHlt2BiasedDiMuonRefinedDecision_TOS;   //!
   TBranch        *b_PsiHlt2BiasedDiMuonMassDecision_Dec;   //!
   TBranch        *b_PsiHlt2BiasedDiMuonMassDecision_TIS;   //!
   TBranch        *b_PsiHlt2BiasedDiMuonMassDecision_TOS;   //!
   TBranch        *b_PsiHlt2BiasedDiMuonIPDecision_Dec;   //!
   TBranch        *b_PsiHlt2BiasedDiMuonIPDecision_TIS;   //!
   TBranch        *b_PsiHlt2BiasedDiMuonIPDecision_TOS;   //!
   TBranch        *b_PsiHlt2DiMuonBiasedJPsiDecision_Dec;   //!
   TBranch        *b_PsiHlt2DiMuonBiasedJPsiDecision_TIS;   //!
   TBranch        *b_PsiHlt2DiMuonBiasedJPsiDecision_TOS;   //!
   TBranch        *b_PsiHlt2TopoMu2BodyBBDTDecision_Dec;   //!
   TBranch        *b_PsiHlt2TopoMu2BodyBBDTDecision_TIS;   //!
   TBranch        *b_PsiHlt2TopoMu2BodyBBDTDecision_TOS;   //!
   TBranch        *b_PsiHlt2TopoMu3BodyBBDTDecision_Dec;   //!
   TBranch        *b_PsiHlt2TopoMu3BodyBBDTDecision_TIS;   //!
   TBranch        *b_PsiHlt2TopoMu3BodyBBDTDecision_TOS;   //!
   TBranch        *b_PsiHlt2TopoMu4BodyBBDTDecision_Dec;   //!
   TBranch        *b_PsiHlt2TopoMu4BodyBBDTDecision_TIS;   //!
   TBranch        *b_PsiHlt2TopoMu4BodyBBDTDecision_TOS;   //!
   TBranch        *b_PsiHlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_PsiHlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_PsiHlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_PsiHlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_PsiHlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_PsiHlt2SingleMuonLowPTDecision_TOS;   //!
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
   TBranch        *b_muminus_CaloEcalE;   //!
   TBranch        *b_muminus_CaloHcalE;   //!
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
   TBranch        *b_muplus_CaloEcalE;   //!
   TBranch        *b_muplus_CaloHcalE;   //!
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
   TBranch        *b_Primaries;   //!
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
   TBranch        *b_ChargedProtos;   //!
   TBranch        *b_NeutralProtos;   //!
   TBranch        *b_BestTracks;   //!
   TBranch        *b_MuonTracks;   //!
   TBranch        *b_ITClusters;   //!
   TBranch        *b_VeloLiteClusters;   //!
   TBranch        *b_OTClusters;   //!
   TBranch        *b_spdMult;   //!
   TBranch        *b_backwardTracks;   //!
   TBranch        *b_veloTracks;   //!
   TBranch        *b_longTracks;   //!
   TBranch        *b_goodLongTracks;   //!
   
// ####################################################################################################
// *** Common Content ***
#include "B2JpsiX.icpp"

};
#endif


#ifdef B2JpsiPhi_2011_cxx
// ####################################################################################################
//
// Class Content
//
// ####################################################################################################

// *** Constructors ***

// Constructor
B2JpsiPhi_2011::B2JpsiPhi_2011(TTree *tree, TString module, TString dir, TString what, unsigned int NNtype) : IB2JpsiX() {
   defineConstants();
   Init(tree, module, dir, what, NNtype);
}

// Destructor
B2JpsiPhi_2011::~B2JpsiPhi_2011(){
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

// Initialize
void B2JpsiPhi_2011::Init(TTree *tree, TString module, TString dir, TString what, unsigned int NNtype){
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
   if((module==m_weighting && NNtype==m_NNtype_two) || module==m_branching || module==m_lifetime){
     fChain->SetBranchAddress("netOutput", &netOutput, &b_netOutput);
   }
    // Set Truth Info
   if(what==m_IncJpsi){
     fChain->SetBranchAddress("B_TRUEID",&B_TRUEID,&b_B_TRUEID);
     fChain->SetBranchAddress("Psi_TRUEID",&Psi_TRUEID,&b_Psi_TRUEID);
     fChain->SetBranchAddress("phi_1020_TRUEID",&phi_1020_TRUEID,&b_phi_1020_TRUEID);
     fChain->SetBranchAddress("B_BKGCAT",&B_BKGCAT,&b_B_BKGCAT);
     fChain->SetBranchAddress("B_TRUETAU",&B_TRUETAU,&b_B_TRUETAU); 
   }
   //if(dir==""){
   // Slimtuple not supported
   //} // end init from slimtuple

// ####################################################################################################

   //else if(dir!=""){
   fChain->SetBranchAddress("B_MINIP", &B_MINIP, &b_B_MINIP);
   fChain->SetBranchAddress("B_MINIPCHI2", &B_MINIPCHI2, &b_B_MINIPCHI2);
   fChain->SetBranchAddress("B_MINIPNEXTBEST", &B_MINIPNEXTBEST, &b_B_MINIPNEXTBEST);
   fChain->SetBranchAddress("B_MINIPCHI2NEXTBEST", &B_MINIPCHI2NEXTBEST, &b_B_MINIPCHI2NEXTBEST);
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
   fChain->SetBranchAddress("B_ENDVERTEX_X", &B_ENDVERTEX_X, &b_B_ENDVERTEX_X);
   fChain->SetBranchAddress("B_ENDVERTEX_Y", &B_ENDVERTEX_Y, &b_B_ENDVERTEX_Y);
   fChain->SetBranchAddress("B_ENDVERTEX_Z", &B_ENDVERTEX_Z, &b_B_ENDVERTEX_Z);
   fChain->SetBranchAddress("B_ENDVERTEX_XERR", &B_ENDVERTEX_XERR, &b_B_ENDVERTEX_XERR);
   fChain->SetBranchAddress("B_ENDVERTEX_YERR", &B_ENDVERTEX_YERR, &b_B_ENDVERTEX_YERR);
   fChain->SetBranchAddress("B_ENDVERTEX_ZERR", &B_ENDVERTEX_ZERR, &b_B_ENDVERTEX_ZERR);
   fChain->SetBranchAddress("B_ENDVERTEX_CHI2", &B_ENDVERTEX_CHI2, &b_B_ENDVERTEX_CHI2);
   fChain->SetBranchAddress("B_ENDVERTEX_NDOF", &B_ENDVERTEX_NDOF, &b_B_ENDVERTEX_NDOF);
   fChain->SetBranchAddress("B_ENDVERTEX_COV_", B_ENDVERTEX_COV_, &b_B_ENDVERTEX_COV_);
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
   fChain->SetBranchAddress("B_Fit_nPV", &B_Fit_nPV, &b_B_Fit_nPV);
   fChain->SetBranchAddress("B_Fit_M", B_Fit_M, &b_B_Fit_M);
   fChain->SetBranchAddress("B_Fit_MERR", B_Fit_MERR, &b_B_Fit_MERR);
   fChain->SetBranchAddress("B_Fit_P", B_Fit_P, &b_B_Fit_P);
   fChain->SetBranchAddress("B_Fit_PERR", B_Fit_PERR, &b_B_Fit_PERR);
   fChain->SetBranchAddress("B_Fit_chi2_B", B_Fit_chi2_B, &b_B_Fit_chi2_B);
   fChain->SetBranchAddress("B_Fit_chi2", B_Fit_chi2, &b_B_Fit_chi2);
   fChain->SetBranchAddress("B_Fit_nDOF", B_Fit_nDOF, &b_B_Fit_nDOF);
   fChain->SetBranchAddress("B_Fit_nIter", B_Fit_nIter, &b_B_Fit_nIter);
   fChain->SetBranchAddress("B_Fit_status", B_Fit_status, &b_B_Fit_status);
   fChain->SetBranchAddress("B_FullFit_nPV", &B_FullFit_nPV, &b_B_FullFit_nPV);
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
   fChain->SetBranchAddress("B_FullFit_PV_sumPT", B_FullFit_PV_sumPT, &b_B_FullFit_PV_sumPT);
   fChain->SetBranchAddress("B_FullFit_chi2_B", B_FullFit_chi2_B, &b_B_FullFit_chi2_B);
   fChain->SetBranchAddress("B_FullFit_chi2", B_FullFit_chi2, &b_B_FullFit_chi2);
   fChain->SetBranchAddress("B_FullFit_ctau", B_FullFit_ctau, &b_B_FullFit_ctau);
   fChain->SetBranchAddress("B_FullFit_ctauErr", B_FullFit_ctauErr, &b_B_FullFit_ctauErr);
   fChain->SetBranchAddress("B_FullFit_decayLength", B_FullFit_decayLength, &b_B_FullFit_decayLength);
   fChain->SetBranchAddress("B_FullFit_decayLengthErr", B_FullFit_decayLengthErr, &b_B_FullFit_decayLengthErr);
   fChain->SetBranchAddress("B_FullFit_nDOF", B_FullFit_nDOF, &b_B_FullFit_nDOF);
   fChain->SetBranchAddress("B_FullFit_nIter", B_FullFit_nIter, &b_B_FullFit_nIter);
   fChain->SetBranchAddress("B_FullFit_phi_1020_ctau", B_FullFit_phi_1020_ctau, &b_B_FullFit_phi_1020_ctau);
   fChain->SetBranchAddress("B_FullFit_phi_1020_ctauErr", B_FullFit_phi_1020_ctauErr, &b_B_FullFit_phi_1020_ctauErr);
   fChain->SetBranchAddress("B_FullFit_phi_1020_decayLength", B_FullFit_phi_1020_decayLength, &b_B_FullFit_phi_1020_decayLength);
   fChain->SetBranchAddress("B_FullFit_phi_1020_decayLengthErr", B_FullFit_phi_1020_decayLengthErr, &b_B_FullFit_phi_1020_decayLengthErr);
   fChain->SetBranchAddress("B_FullFit_status", B_FullFit_status, &b_B_FullFit_status);
   fChain->SetBranchAddress("B_MassFit_nPV", &B_MassFit_nPV, &b_B_MassFit_nPV);
   fChain->SetBranchAddress("B_MassFit_M", B_MassFit_M, &b_B_MassFit_M);
   fChain->SetBranchAddress("B_MassFit_MERR", B_MassFit_MERR, &b_B_MassFit_MERR);
   fChain->SetBranchAddress("B_MassFit_P", B_MassFit_P, &b_B_MassFit_P);
   fChain->SetBranchAddress("B_MassFit_PERR", B_MassFit_PERR, &b_B_MassFit_PERR);
   fChain->SetBranchAddress("B_MassFit_chi2_B", B_MassFit_chi2_B, &b_B_MassFit_chi2_B);
   fChain->SetBranchAddress("B_MassFit_chi2", B_MassFit_chi2, &b_B_MassFit_chi2);
   fChain->SetBranchAddress("B_MassFit_nDOF", B_MassFit_nDOF, &b_B_MassFit_nDOF);
   fChain->SetBranchAddress("B_MassFit_nIter", B_MassFit_nIter, &b_B_MassFit_nIter);
   fChain->SetBranchAddress("B_MassFit_status", B_MassFit_status, &b_B_MassFit_status);
   fChain->SetBranchAddress("B_NoKsFit_nPV", &B_NoKsFit_nPV, &b_B_NoKsFit_nPV);
   fChain->SetBranchAddress("B_NoKsFit_J_psi_1S_ctau", B_NoKsFit_J_psi_1S_ctau, &b_B_NoKsFit_J_psi_1S_ctau);
   fChain->SetBranchAddress("B_NoKsFit_J_psi_1S_ctauErr", B_NoKsFit_J_psi_1S_ctauErr, &b_B_NoKsFit_J_psi_1S_ctauErr);
   fChain->SetBranchAddress("B_NoKsFit_J_psi_1S_decayLength", B_NoKsFit_J_psi_1S_decayLength, &b_B_NoKsFit_J_psi_1S_decayLength);
   fChain->SetBranchAddress("B_NoKsFit_J_psi_1S_decayLengthErr", B_NoKsFit_J_psi_1S_decayLengthErr, &b_B_NoKsFit_J_psi_1S_decayLengthErr);
   fChain->SetBranchAddress("B_NoKsFit_M", B_NoKsFit_M, &b_B_NoKsFit_M);
   fChain->SetBranchAddress("B_NoKsFit_MERR", B_NoKsFit_MERR, &b_B_NoKsFit_MERR);
   fChain->SetBranchAddress("B_NoKsFit_P", B_NoKsFit_P, &b_B_NoKsFit_P);
   fChain->SetBranchAddress("B_NoKsFit_PERR", B_NoKsFit_PERR, &b_B_NoKsFit_PERR);
   fChain->SetBranchAddress("B_NoKsFit_PV_X", B_NoKsFit_PV_X, &b_B_NoKsFit_PV_X);
   fChain->SetBranchAddress("B_NoKsFit_PV_Y", B_NoKsFit_PV_Y, &b_B_NoKsFit_PV_Y);
   fChain->SetBranchAddress("B_NoKsFit_PV_Z", B_NoKsFit_PV_Z, &b_B_NoKsFit_PV_Z);
   fChain->SetBranchAddress("B_NoKsFit_PV_key", B_NoKsFit_PV_key, &b_B_NoKsFit_PV_key);
   fChain->SetBranchAddress("B_NoKsFit_PV_sumPT", B_NoKsFit_PV_sumPT, &b_B_NoKsFit_PV_sumPT);
   fChain->SetBranchAddress("B_NoKsFit_chi2_B", B_NoKsFit_chi2_B, &b_B_NoKsFit_chi2_B);
   fChain->SetBranchAddress("B_NoKsFit_chi2", B_NoKsFit_chi2, &b_B_NoKsFit_chi2);
   fChain->SetBranchAddress("B_NoKsFit_ctau", B_NoKsFit_ctau, &b_B_NoKsFit_ctau);
   fChain->SetBranchAddress("B_NoKsFit_ctauErr", B_NoKsFit_ctauErr, &b_B_NoKsFit_ctauErr);
   fChain->SetBranchAddress("B_NoKsFit_decayLength", B_NoKsFit_decayLength, &b_B_NoKsFit_decayLength);
   fChain->SetBranchAddress("B_NoKsFit_decayLengthErr", B_NoKsFit_decayLengthErr, &b_B_NoKsFit_decayLengthErr);
   fChain->SetBranchAddress("B_NoKsFit_nDOF", B_NoKsFit_nDOF, &b_B_NoKsFit_nDOF);
   fChain->SetBranchAddress("B_NoKsFit_nIter", B_NoKsFit_nIter, &b_B_NoKsFit_nIter);
   fChain->SetBranchAddress("B_NoKsFit_phi_1020_ctau", B_NoKsFit_phi_1020_ctau, &b_B_NoKsFit_phi_1020_ctau);
   fChain->SetBranchAddress("B_NoKsFit_phi_1020_ctauErr", B_NoKsFit_phi_1020_ctauErr, &b_B_NoKsFit_phi_1020_ctauErr);
   fChain->SetBranchAddress("B_NoKsFit_phi_1020_decayLength", B_NoKsFit_phi_1020_decayLength, &b_B_NoKsFit_phi_1020_decayLength);
   fChain->SetBranchAddress("B_NoKsFit_phi_1020_decayLengthErr", B_NoKsFit_phi_1020_decayLengthErr, &b_B_NoKsFit_phi_1020_decayLengthErr);
   fChain->SetBranchAddress("B_NoKsFit_status", B_NoKsFit_status, &b_B_NoKsFit_status);
   fChain->SetBranchAddress("B_PVFit_nPV", &B_PVFit_nPV, &b_B_PVFit_nPV);
   fChain->SetBranchAddress("B_PVFit_M", B_PVFit_M, &b_B_PVFit_M);
   fChain->SetBranchAddress("B_PVFit_MERR", B_PVFit_MERR, &b_B_PVFit_MERR);
   fChain->SetBranchAddress("B_PVFit_P", B_PVFit_P, &b_B_PVFit_P);
   fChain->SetBranchAddress("B_PVFit_PERR", B_PVFit_PERR, &b_B_PVFit_PERR);
   fChain->SetBranchAddress("B_PVFit_chi2_B", B_PVFit_chi2_B, &b_B_PVFit_chi2_B);
   fChain->SetBranchAddress("B_PVFit_chi2", B_PVFit_chi2, &b_B_PVFit_chi2);
   fChain->SetBranchAddress("B_PVFit_nDOF", B_PVFit_nDOF, &b_B_PVFit_nDOF);
   fChain->SetBranchAddress("B_PVFit_nIter", B_PVFit_nIter, &b_B_PVFit_nIter);
   fChain->SetBranchAddress("B_PVFit_status", B_PVFit_status, &b_B_PVFit_status);
   fChain->SetBranchAddress("BL0Global_Dec", &BL0Global_Dec, &b_BL0Global_Dec);
   fChain->SetBranchAddress("BL0Global_TIS", &BL0Global_TIS, &b_BL0Global_TIS);
   fChain->SetBranchAddress("BL0Global_TOS", &BL0Global_TOS, &b_BL0Global_TOS);
   fChain->SetBranchAddress("BHlt1Global_Dec", &BHlt1Global_Dec, &b_BHlt1Global_Dec);
   fChain->SetBranchAddress("BHlt1Global_TIS", &BHlt1Global_TIS, &b_BHlt1Global_TIS);
   fChain->SetBranchAddress("BHlt1Global_TOS", &BHlt1Global_TOS, &b_BHlt1Global_TOS);
   fChain->SetBranchAddress("BHlt2Global_Dec", &BHlt2Global_Dec, &b_BHlt2Global_Dec);
   fChain->SetBranchAddress("BHlt2Global_TIS", &BHlt2Global_TIS, &b_BHlt2Global_TIS);
   fChain->SetBranchAddress("BHlt2Global_TOS", &BHlt2Global_TOS, &b_BHlt2Global_TOS);
   fChain->SetBranchAddress("BHlt1TrackAllL0Decision_Dec", &BHlt1TrackAllL0Decision_Dec, &b_BHlt1TrackAllL0Decision_Dec);
   fChain->SetBranchAddress("BHlt1TrackAllL0Decision_TIS", &BHlt1TrackAllL0Decision_TIS, &b_BHlt1TrackAllL0Decision_TIS);
   fChain->SetBranchAddress("BHlt1TrackAllL0Decision_TOS", &BHlt1TrackAllL0Decision_TOS, &b_BHlt1TrackAllL0Decision_TOS);
   fChain->SetBranchAddress("BHlt1MuTrackDecision_Dec", &BHlt1MuTrackDecision_Dec, &b_BHlt1MuTrackDecision_Dec);
   fChain->SetBranchAddress("BHlt1MuTrackDecision_TIS", &BHlt1MuTrackDecision_TIS, &b_BHlt1MuTrackDecision_TIS);
   fChain->SetBranchAddress("BHlt1MuTrackDecision_TOS", &BHlt1MuTrackDecision_TOS, &b_BHlt1MuTrackDecision_TOS);
   fChain->SetBranchAddress("BHlt1DiMuonNoIP2L0Decision_Dec", &BHlt1DiMuonNoIP2L0Decision_Dec, &b_BHlt1DiMuonNoIP2L0Decision_Dec);
   fChain->SetBranchAddress("BHlt1DiMuonNoIP2L0Decision_TIS", &BHlt1DiMuonNoIP2L0Decision_TIS, &b_BHlt1DiMuonNoIP2L0Decision_TIS);
   fChain->SetBranchAddress("BHlt1DiMuonNoIP2L0Decision_TOS", &BHlt1DiMuonNoIP2L0Decision_TOS, &b_BHlt1DiMuonNoIP2L0Decision_TOS);
   fChain->SetBranchAddress("BHlt1DiMuonNoIPL0SegDecision_Dec", &BHlt1DiMuonNoIPL0SegDecision_Dec, &b_BHlt1DiMuonNoIPL0SegDecision_Dec);
   fChain->SetBranchAddress("BHlt1DiMuonNoIPL0SegDecision_TIS", &BHlt1DiMuonNoIPL0SegDecision_TIS, &b_BHlt1DiMuonNoIPL0SegDecision_TIS);
   fChain->SetBranchAddress("BHlt1DiMuonNoIPL0SegDecision_TOS", &BHlt1DiMuonNoIPL0SegDecision_TOS, &b_BHlt1DiMuonNoIPL0SegDecision_TOS);
   fChain->SetBranchAddress("BHlt1DiMuonIPCL0DiDecision_Dec", &BHlt1DiMuonIPCL0DiDecision_Dec, &b_BHlt1DiMuonIPCL0DiDecision_Dec);
   fChain->SetBranchAddress("BHlt1DiMuonIPCL0DiDecision_TIS", &BHlt1DiMuonIPCL0DiDecision_TIS, &b_BHlt1DiMuonIPCL0DiDecision_TIS);
   fChain->SetBranchAddress("BHlt1DiMuonIPCL0DiDecision_TOS", &BHlt1DiMuonIPCL0DiDecision_TOS, &b_BHlt1DiMuonIPCL0DiDecision_TOS);
   fChain->SetBranchAddress("BHlt1DiMuonIPC2L0Decision_Dec", &BHlt1DiMuonIPC2L0Decision_Dec, &b_BHlt1DiMuonIPC2L0Decision_Dec);
   fChain->SetBranchAddress("BHlt1DiMuonIPC2L0Decision_TIS", &BHlt1DiMuonIPC2L0Decision_TIS, &b_BHlt1DiMuonIPC2L0Decision_TIS);
   fChain->SetBranchAddress("BHlt1DiMuonIPC2L0Decision_TOS", &BHlt1DiMuonIPC2L0Decision_TOS, &b_BHlt1DiMuonIPC2L0Decision_TOS);
   fChain->SetBranchAddress("BHlt1DiMuonIPCL0SegDecision_Dec", &BHlt1DiMuonIPCL0SegDecision_Dec, &b_BHlt1DiMuonIPCL0SegDecision_Dec);
   fChain->SetBranchAddress("BHlt1DiMuonIPCL0SegDecision_TIS", &BHlt1DiMuonIPCL0SegDecision_TIS, &b_BHlt1DiMuonIPCL0SegDecision_TIS);
   fChain->SetBranchAddress("BHlt1DiMuonIPCL0SegDecision_TOS", &BHlt1DiMuonIPCL0SegDecision_TOS, &b_BHlt1DiMuonIPCL0SegDecision_TOS);
   fChain->SetBranchAddress("BHlt1DiMuonHighMassDecision_Dec", &BHlt1DiMuonHighMassDecision_Dec, &b_BHlt1DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("BHlt1DiMuonHighMassDecision_TIS", &BHlt1DiMuonHighMassDecision_TIS, &b_BHlt1DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("BHlt1DiMuonHighMassDecision_TOS", &BHlt1DiMuonHighMassDecision_TOS, &b_BHlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("BHlt1DiMuonLowMassDecision_Dec", &BHlt1DiMuonLowMassDecision_Dec, &b_BHlt1DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("BHlt1DiMuonLowMassDecision_TIS", &BHlt1DiMuonLowMassDecision_TIS, &b_BHlt1DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("BHlt1DiMuonLowMassDecision_TOS", &BHlt1DiMuonLowMassDecision_TOS, &b_BHlt1DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("BHlt1SingleMuonNoIPL0Decision_Dec", &BHlt1SingleMuonNoIPL0Decision_Dec, &b_BHlt1SingleMuonNoIPL0Decision_Dec);
   fChain->SetBranchAddress("BHlt1SingleMuonNoIPL0Decision_TIS", &BHlt1SingleMuonNoIPL0Decision_TIS, &b_BHlt1SingleMuonNoIPL0Decision_TIS);
   fChain->SetBranchAddress("BHlt1SingleMuonNoIPL0Decision_TOS", &BHlt1SingleMuonNoIPL0Decision_TOS, &b_BHlt1SingleMuonNoIPL0Decision_TOS);
   fChain->SetBranchAddress("BHlt1SingleMuonNoIPL0HighPTDecision_Dec", &BHlt1SingleMuonNoIPL0HighPTDecision_Dec, &b_BHlt1SingleMuonNoIPL0HighPTDecision_Dec);
   fChain->SetBranchAddress("BHlt1SingleMuonNoIPL0HighPTDecision_TIS", &BHlt1SingleMuonNoIPL0HighPTDecision_TIS, &b_BHlt1SingleMuonNoIPL0HighPTDecision_TIS);
   fChain->SetBranchAddress("BHlt1SingleMuonNoIPL0HighPTDecision_TOS", &BHlt1SingleMuonNoIPL0HighPTDecision_TOS, &b_BHlt1SingleMuonNoIPL0HighPTDecision_TOS);
   fChain->SetBranchAddress("BHlt1SingleMuonIPCL0Decision_Dec", &BHlt1SingleMuonIPCL0Decision_Dec, &b_BHlt1SingleMuonIPCL0Decision_Dec);
   fChain->SetBranchAddress("BHlt1SingleMuonIPCL0Decision_TIS", &BHlt1SingleMuonIPCL0Decision_TIS, &b_BHlt1SingleMuonIPCL0Decision_TIS);
   fChain->SetBranchAddress("BHlt1SingleMuonIPCL0Decision_TOS", &BHlt1SingleMuonIPCL0Decision_TOS, &b_BHlt1SingleMuonIPCL0Decision_TOS);
   fChain->SetBranchAddress("BHlt1SingleMuonNoIPDecision_Dec", &BHlt1SingleMuonNoIPDecision_Dec, &b_BHlt1SingleMuonNoIPDecision_Dec);
   fChain->SetBranchAddress("BHlt1SingleMuonNoIPDecision_TIS", &BHlt1SingleMuonNoIPDecision_TIS, &b_BHlt1SingleMuonNoIPDecision_TIS);
   fChain->SetBranchAddress("BHlt1SingleMuonNoIPDecision_TOS", &BHlt1SingleMuonNoIPDecision_TOS, &b_BHlt1SingleMuonNoIPDecision_TOS);
   fChain->SetBranchAddress("BHlt1TrackMuonDecision_Dec", &BHlt1TrackMuonDecision_Dec, &b_BHlt1TrackMuonDecision_Dec);
   fChain->SetBranchAddress("BHlt1TrackMuonDecision_TIS", &BHlt1TrackMuonDecision_TIS, &b_BHlt1TrackMuonDecision_TIS);
   fChain->SetBranchAddress("BHlt1TrackMuonDecision_TOS", &BHlt1TrackMuonDecision_TOS, &b_BHlt1TrackMuonDecision_TOS);
   fChain->SetBranchAddress("BHlt2TopoTF3BodyReq2YesDecision_Dec", &BHlt2TopoTF3BodyReq2YesDecision_Dec, &b_BHlt2TopoTF3BodyReq2YesDecision_Dec);
   fChain->SetBranchAddress("BHlt2TopoTF3BodyReq2YesDecision_TIS", &BHlt2TopoTF3BodyReq2YesDecision_TIS, &b_BHlt2TopoTF3BodyReq2YesDecision_TIS);
   fChain->SetBranchAddress("BHlt2TopoTF3BodyReq2YesDecision_TOS", &BHlt2TopoTF3BodyReq2YesDecision_TOS, &b_BHlt2TopoTF3BodyReq2YesDecision_TOS);
   fChain->SetBranchAddress("BHlt2TopoTF3BodyReq3YesDecision_Dec", &BHlt2TopoTF3BodyReq3YesDecision_Dec, &b_BHlt2TopoTF3BodyReq3YesDecision_Dec);
   fChain->SetBranchAddress("BHlt2TopoTF3BodyReq3YesDecision_TIS", &BHlt2TopoTF3BodyReq3YesDecision_TIS, &b_BHlt2TopoTF3BodyReq3YesDecision_TIS);
   fChain->SetBranchAddress("BHlt2TopoTF3BodyReq3YesDecision_TOS", &BHlt2TopoTF3BodyReq3YesDecision_TOS, &b_BHlt2TopoTF3BodyReq3YesDecision_TOS);
   fChain->SetBranchAddress("BHlt2TopoOSTF2BodyDecision_Dec", &BHlt2TopoOSTF2BodyDecision_Dec, &b_BHlt2TopoOSTF2BodyDecision_Dec);
   fChain->SetBranchAddress("BHlt2TopoOSTF2BodyDecision_TIS", &BHlt2TopoOSTF2BodyDecision_TIS, &b_BHlt2TopoOSTF2BodyDecision_TIS);
   fChain->SetBranchAddress("BHlt2TopoOSTF2BodyDecision_TOS", &BHlt2TopoOSTF2BodyDecision_TOS, &b_BHlt2TopoOSTF2BodyDecision_TOS);
   fChain->SetBranchAddress("BHlt2TopoOSTF3BodyDecision_Dec", &BHlt2TopoOSTF3BodyDecision_Dec, &b_BHlt2TopoOSTF3BodyDecision_Dec);
   fChain->SetBranchAddress("BHlt2TopoOSTF3BodyDecision_TIS", &BHlt2TopoOSTF3BodyDecision_TIS, &b_BHlt2TopoOSTF3BodyDecision_TIS);
   fChain->SetBranchAddress("BHlt2TopoOSTF3BodyDecision_TOS", &BHlt2TopoOSTF3BodyDecision_TOS, &b_BHlt2TopoOSTF3BodyDecision_TOS);
   fChain->SetBranchAddress("BHlt2TopoOSTF4BodyDecision_Dec", &BHlt2TopoOSTF4BodyDecision_Dec, &b_BHlt2TopoOSTF4BodyDecision_Dec);
   fChain->SetBranchAddress("BHlt2TopoOSTF4BodyDecision_TIS", &BHlt2TopoOSTF4BodyDecision_TIS, &b_BHlt2TopoOSTF4BodyDecision_TIS);
   fChain->SetBranchAddress("BHlt2TopoOSTF4BodyDecision_TOS", &BHlt2TopoOSTF4BodyDecision_TOS, &b_BHlt2TopoOSTF4BodyDecision_TOS);
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
   fChain->SetBranchAddress("BHlt2MuTrackDecision_Dec", &BHlt2MuTrackDecision_Dec, &b_BHlt2MuTrackDecision_Dec);
   fChain->SetBranchAddress("BHlt2MuTrackDecision_TIS", &BHlt2MuTrackDecision_TIS, &b_BHlt2MuTrackDecision_TIS);
   fChain->SetBranchAddress("BHlt2MuTrackDecision_TOS", &BHlt2MuTrackDecision_TOS, &b_BHlt2MuTrackDecision_TOS);
   fChain->SetBranchAddress("BHlt2MuTrackNoIPDecision_Dec", &BHlt2MuTrackNoIPDecision_Dec, &b_BHlt2MuTrackNoIPDecision_Dec);
   fChain->SetBranchAddress("BHlt2MuTrackNoIPDecision_TIS", &BHlt2MuTrackNoIPDecision_TIS, &b_BHlt2MuTrackNoIPDecision_TIS);
   fChain->SetBranchAddress("BHlt2MuTrackNoIPDecision_TOS", &BHlt2MuTrackNoIPDecision_TOS, &b_BHlt2MuTrackNoIPDecision_TOS);
   fChain->SetBranchAddress("BHlt2SingleMuonDecision_Dec", &BHlt2SingleMuonDecision_Dec, &b_BHlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("BHlt2SingleMuonDecision_TIS", &BHlt2SingleMuonDecision_TIS, &b_BHlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("BHlt2SingleMuonDecision_TOS", &BHlt2SingleMuonDecision_TOS, &b_BHlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("BHlt2UnbiasedDiMuonDecision_Dec", &BHlt2UnbiasedDiMuonDecision_Dec, &b_BHlt2UnbiasedDiMuonDecision_Dec);
   fChain->SetBranchAddress("BHlt2UnbiasedDiMuonDecision_TIS", &BHlt2UnbiasedDiMuonDecision_TIS, &b_BHlt2UnbiasedDiMuonDecision_TIS);
   fChain->SetBranchAddress("BHlt2UnbiasedDiMuonDecision_TOS", &BHlt2UnbiasedDiMuonDecision_TOS, &b_BHlt2UnbiasedDiMuonDecision_TOS);
   fChain->SetBranchAddress("BHlt2UnbiasedDiMuonLowMassDecision_Dec", &BHlt2UnbiasedDiMuonLowMassDecision_Dec, &b_BHlt2UnbiasedDiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("BHlt2UnbiasedDiMuonLowMassDecision_TIS", &BHlt2UnbiasedDiMuonLowMassDecision_TIS, &b_BHlt2UnbiasedDiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("BHlt2UnbiasedDiMuonLowMassDecision_TOS", &BHlt2UnbiasedDiMuonLowMassDecision_TOS, &b_BHlt2UnbiasedDiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("BHlt2DiMuonUnbiasedJPsiDecision_Dec", &BHlt2DiMuonUnbiasedJPsiDecision_Dec, &b_BHlt2DiMuonUnbiasedJPsiDecision_Dec);
   fChain->SetBranchAddress("BHlt2DiMuonUnbiasedJPsiDecision_TIS", &BHlt2DiMuonUnbiasedJPsiDecision_TIS, &b_BHlt2DiMuonUnbiasedJPsiDecision_TIS);
   fChain->SetBranchAddress("BHlt2DiMuonUnbiasedJPsiDecision_TOS", &BHlt2DiMuonUnbiasedJPsiDecision_TOS, &b_BHlt2DiMuonUnbiasedJPsiDecision_TOS);
   fChain->SetBranchAddress("BHlt2DiMuonUnbiasedPsi2SDecision_Dec", &BHlt2DiMuonUnbiasedPsi2SDecision_Dec, &b_BHlt2DiMuonUnbiasedPsi2SDecision_Dec);
   fChain->SetBranchAddress("BHlt2DiMuonUnbiasedPsi2SDecision_TIS", &BHlt2DiMuonUnbiasedPsi2SDecision_TIS, &b_BHlt2DiMuonUnbiasedPsi2SDecision_TIS);
   fChain->SetBranchAddress("BHlt2DiMuonUnbiasedPsi2SDecision_TOS", &BHlt2DiMuonUnbiasedPsi2SDecision_TOS, &b_BHlt2DiMuonUnbiasedPsi2SDecision_TOS);
   fChain->SetBranchAddress("BHlt2BiasedDiMuonSimpleDecision_Dec", &BHlt2BiasedDiMuonSimpleDecision_Dec, &b_BHlt2BiasedDiMuonSimpleDecision_Dec);
   fChain->SetBranchAddress("BHlt2BiasedDiMuonSimpleDecision_TIS", &BHlt2BiasedDiMuonSimpleDecision_TIS, &b_BHlt2BiasedDiMuonSimpleDecision_TIS);
   fChain->SetBranchAddress("BHlt2BiasedDiMuonSimpleDecision_TOS", &BHlt2BiasedDiMuonSimpleDecision_TOS, &b_BHlt2BiasedDiMuonSimpleDecision_TOS);
   fChain->SetBranchAddress("BHlt2BiasedDiMuonRefinedDecision_Dec", &BHlt2BiasedDiMuonRefinedDecision_Dec, &b_BHlt2BiasedDiMuonRefinedDecision_Dec);
   fChain->SetBranchAddress("BHlt2BiasedDiMuonRefinedDecision_TIS", &BHlt2BiasedDiMuonRefinedDecision_TIS, &b_BHlt2BiasedDiMuonRefinedDecision_TIS);
   fChain->SetBranchAddress("BHlt2BiasedDiMuonRefinedDecision_TOS", &BHlt2BiasedDiMuonRefinedDecision_TOS, &b_BHlt2BiasedDiMuonRefinedDecision_TOS);
   fChain->SetBranchAddress("BHlt2BiasedDiMuonMassDecision_Dec", &BHlt2BiasedDiMuonMassDecision_Dec, &b_BHlt2BiasedDiMuonMassDecision_Dec);
   fChain->SetBranchAddress("BHlt2BiasedDiMuonMassDecision_TIS", &BHlt2BiasedDiMuonMassDecision_TIS, &b_BHlt2BiasedDiMuonMassDecision_TIS);
   fChain->SetBranchAddress("BHlt2BiasedDiMuonMassDecision_TOS", &BHlt2BiasedDiMuonMassDecision_TOS, &b_BHlt2BiasedDiMuonMassDecision_TOS);
   fChain->SetBranchAddress("BHlt2BiasedDiMuonIPDecision_Dec", &BHlt2BiasedDiMuonIPDecision_Dec, &b_BHlt2BiasedDiMuonIPDecision_Dec);
   fChain->SetBranchAddress("BHlt2BiasedDiMuonIPDecision_TIS", &BHlt2BiasedDiMuonIPDecision_TIS, &b_BHlt2BiasedDiMuonIPDecision_TIS);
   fChain->SetBranchAddress("BHlt2BiasedDiMuonIPDecision_TOS", &BHlt2BiasedDiMuonIPDecision_TOS, &b_BHlt2BiasedDiMuonIPDecision_TOS);
   fChain->SetBranchAddress("BHlt2DiMuonBiasedJPsiDecision_Dec", &BHlt2DiMuonBiasedJPsiDecision_Dec, &b_BHlt2DiMuonBiasedJPsiDecision_Dec);
   fChain->SetBranchAddress("BHlt2DiMuonBiasedJPsiDecision_TIS", &BHlt2DiMuonBiasedJPsiDecision_TIS, &b_BHlt2DiMuonBiasedJPsiDecision_TIS);
   fChain->SetBranchAddress("BHlt2DiMuonBiasedJPsiDecision_TOS", &BHlt2DiMuonBiasedJPsiDecision_TOS, &b_BHlt2DiMuonBiasedJPsiDecision_TOS);
   fChain->SetBranchAddress("BHlt2TopoMu2BodyBBDTDecision_Dec", &BHlt2TopoMu2BodyBBDTDecision_Dec, &b_BHlt2TopoMu2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("BHlt2TopoMu2BodyBBDTDecision_TIS", &BHlt2TopoMu2BodyBBDTDecision_TIS, &b_BHlt2TopoMu2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("BHlt2TopoMu2BodyBBDTDecision_TOS", &BHlt2TopoMu2BodyBBDTDecision_TOS, &b_BHlt2TopoMu2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("BHlt2TopoMu3BodyBBDTDecision_Dec", &BHlt2TopoMu3BodyBBDTDecision_Dec, &b_BHlt2TopoMu3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("BHlt2TopoMu3BodyBBDTDecision_TIS", &BHlt2TopoMu3BodyBBDTDecision_TIS, &b_BHlt2TopoMu3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("BHlt2TopoMu3BodyBBDTDecision_TOS", &BHlt2TopoMu3BodyBBDTDecision_TOS, &b_BHlt2TopoMu3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("BHlt2TopoMu4BodyBBDTDecision_Dec", &BHlt2TopoMu4BodyBBDTDecision_Dec, &b_BHlt2TopoMu4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("BHlt2TopoMu4BodyBBDTDecision_TIS", &BHlt2TopoMu4BodyBBDTDecision_TIS, &b_BHlt2TopoMu4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("BHlt2TopoMu4BodyBBDTDecision_TOS", &BHlt2TopoMu4BodyBBDTDecision_TOS, &b_BHlt2TopoMu4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("BHlt2SingleMuonHighPTDecision_Dec", &BHlt2SingleMuonHighPTDecision_Dec, &b_BHlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("BHlt2SingleMuonHighPTDecision_TIS", &BHlt2SingleMuonHighPTDecision_TIS, &b_BHlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("BHlt2SingleMuonHighPTDecision_TOS", &BHlt2SingleMuonHighPTDecision_TOS, &b_BHlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("BHlt2SingleMuonLowPTDecision_Dec", &BHlt2SingleMuonLowPTDecision_Dec, &b_BHlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("BHlt2SingleMuonLowPTDecision_TIS", &BHlt2SingleMuonLowPTDecision_TIS, &b_BHlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("BHlt2SingleMuonLowPTDecision_TOS", &BHlt2SingleMuonLowPTDecision_TOS, &b_BHlt2SingleMuonLowPTDecision_TOS);
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
   fChain->SetBranchAddress("phi_1020_MINIP", &phi_1020_MINIP, &b_phi_1020_MINIP);
   fChain->SetBranchAddress("phi_1020_MINIPCHI2", &phi_1020_MINIPCHI2, &b_phi_1020_MINIPCHI2);
   fChain->SetBranchAddress("phi_1020_MINIPNEXTBEST", &phi_1020_MINIPNEXTBEST, &b_phi_1020_MINIPNEXTBEST);
   fChain->SetBranchAddress("phi_1020_MINIPCHI2NEXTBEST", &phi_1020_MINIPCHI2NEXTBEST, &b_phi_1020_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("phi_1020_OWNPV_X", &phi_1020_OWNPV_X, &b_phi_1020_OWNPV_X);
   fChain->SetBranchAddress("phi_1020_OWNPV_Y", &phi_1020_OWNPV_Y, &b_phi_1020_OWNPV_Y);
   fChain->SetBranchAddress("phi_1020_OWNPV_Z", &phi_1020_OWNPV_Z, &b_phi_1020_OWNPV_Z);
   fChain->SetBranchAddress("phi_1020_OWNPV_XERR", &phi_1020_OWNPV_XERR, &b_phi_1020_OWNPV_XERR);
   fChain->SetBranchAddress("phi_1020_OWNPV_YERR", &phi_1020_OWNPV_YERR, &b_phi_1020_OWNPV_YERR);
   fChain->SetBranchAddress("phi_1020_OWNPV_ZERR", &phi_1020_OWNPV_ZERR, &b_phi_1020_OWNPV_ZERR);
   fChain->SetBranchAddress("phi_1020_OWNPV_CHI2", &phi_1020_OWNPV_CHI2, &b_phi_1020_OWNPV_CHI2);
   fChain->SetBranchAddress("phi_1020_OWNPV_NDOF", &phi_1020_OWNPV_NDOF, &b_phi_1020_OWNPV_NDOF);
   fChain->SetBranchAddress("phi_1020_OWNPV_COV_", phi_1020_OWNPV_COV_, &b_phi_1020_OWNPV_COV_);
   fChain->SetBranchAddress("phi_1020_IP_OWNPV", &phi_1020_IP_OWNPV, &b_phi_1020_IP_OWNPV);
   fChain->SetBranchAddress("phi_1020_IPCHI2_OWNPV", &phi_1020_IPCHI2_OWNPV, &b_phi_1020_IPCHI2_OWNPV);
   fChain->SetBranchAddress("phi_1020_FD_OWNPV", &phi_1020_FD_OWNPV, &b_phi_1020_FD_OWNPV);
   fChain->SetBranchAddress("phi_1020_FDCHI2_OWNPV", &phi_1020_FDCHI2_OWNPV, &b_phi_1020_FDCHI2_OWNPV);
   fChain->SetBranchAddress("phi_1020_DIRA_OWNPV", &phi_1020_DIRA_OWNPV, &b_phi_1020_DIRA_OWNPV);
   fChain->SetBranchAddress("phi_1020_ORIVX_X", &phi_1020_ORIVX_X, &b_phi_1020_ORIVX_X);
   fChain->SetBranchAddress("phi_1020_ORIVX_Y", &phi_1020_ORIVX_Y, &b_phi_1020_ORIVX_Y);
   fChain->SetBranchAddress("phi_1020_ORIVX_Z", &phi_1020_ORIVX_Z, &b_phi_1020_ORIVX_Z);
   fChain->SetBranchAddress("phi_1020_ORIVX_XERR", &phi_1020_ORIVX_XERR, &b_phi_1020_ORIVX_XERR);
   fChain->SetBranchAddress("phi_1020_ORIVX_YERR", &phi_1020_ORIVX_YERR, &b_phi_1020_ORIVX_YERR);
   fChain->SetBranchAddress("phi_1020_ORIVX_ZERR", &phi_1020_ORIVX_ZERR, &b_phi_1020_ORIVX_ZERR);
   fChain->SetBranchAddress("phi_1020_ORIVX_CHI2", &phi_1020_ORIVX_CHI2, &b_phi_1020_ORIVX_CHI2);
   fChain->SetBranchAddress("phi_1020_ORIVX_NDOF", &phi_1020_ORIVX_NDOF, &b_phi_1020_ORIVX_NDOF);
   fChain->SetBranchAddress("phi_1020_ORIVX_COV_", phi_1020_ORIVX_COV_, &b_phi_1020_ORIVX_COV_);
   fChain->SetBranchAddress("phi_1020_FD_ORIVX", &phi_1020_FD_ORIVX, &b_phi_1020_FD_ORIVX);
   fChain->SetBranchAddress("phi_1020_FDCHI2_ORIVX", &phi_1020_FDCHI2_ORIVX, &b_phi_1020_FDCHI2_ORIVX);
   fChain->SetBranchAddress("phi_1020_DIRA_ORIVX", &phi_1020_DIRA_ORIVX, &b_phi_1020_DIRA_ORIVX);
   fChain->SetBranchAddress("phi_1020_ENDVERTEX_X", &phi_1020_ENDVERTEX_X, &b_phi_1020_ENDVERTEX_X);
   fChain->SetBranchAddress("phi_1020_ENDVERTEX_Y", &phi_1020_ENDVERTEX_Y, &b_phi_1020_ENDVERTEX_Y);
   fChain->SetBranchAddress("phi_1020_ENDVERTEX_Z", &phi_1020_ENDVERTEX_Z, &b_phi_1020_ENDVERTEX_Z);
   fChain->SetBranchAddress("phi_1020_ENDVERTEX_XERR", &phi_1020_ENDVERTEX_XERR, &b_phi_1020_ENDVERTEX_XERR);
   fChain->SetBranchAddress("phi_1020_ENDVERTEX_YERR", &phi_1020_ENDVERTEX_YERR, &b_phi_1020_ENDVERTEX_YERR);
   fChain->SetBranchAddress("phi_1020_ENDVERTEX_ZERR", &phi_1020_ENDVERTEX_ZERR, &b_phi_1020_ENDVERTEX_ZERR);
   fChain->SetBranchAddress("phi_1020_ENDVERTEX_CHI2", &phi_1020_ENDVERTEX_CHI2, &b_phi_1020_ENDVERTEX_CHI2);
   fChain->SetBranchAddress("phi_1020_ENDVERTEX_NDOF", &phi_1020_ENDVERTEX_NDOF, &b_phi_1020_ENDVERTEX_NDOF);
   fChain->SetBranchAddress("phi_1020_ENDVERTEX_COV_", phi_1020_ENDVERTEX_COV_, &b_phi_1020_ENDVERTEX_COV_);
   fChain->SetBranchAddress("phi_1020_P", &phi_1020_P, &b_phi_1020_P);
   fChain->SetBranchAddress("phi_1020_PT", &phi_1020_PT, &b_phi_1020_PT);
   fChain->SetBranchAddress("phi_1020_PE", &phi_1020_PE, &b_phi_1020_PE);
   fChain->SetBranchAddress("phi_1020_PX", &phi_1020_PX, &b_phi_1020_PX);
   fChain->SetBranchAddress("phi_1020_PY", &phi_1020_PY, &b_phi_1020_PY);
   fChain->SetBranchAddress("phi_1020_PZ", &phi_1020_PZ, &b_phi_1020_PZ);
   fChain->SetBranchAddress("phi_1020_MM", &phi_1020_MM, &b_phi_1020_MM);
   fChain->SetBranchAddress("phi_1020_MMERR", &phi_1020_MMERR, &b_phi_1020_MMERR);
   fChain->SetBranchAddress("phi_1020_M", &phi_1020_M, &b_phi_1020_M);
   fChain->SetBranchAddress("phi_1020_ID", &phi_1020_ID, &b_phi_1020_ID);
   fChain->SetBranchAddress("phi_1020_TAU", &phi_1020_TAU, &b_phi_1020_TAU);
   fChain->SetBranchAddress("phi_1020_TAUERR", &phi_1020_TAUERR, &b_phi_1020_TAUERR);
   fChain->SetBranchAddress("phi_1020_TAUCHI2", &phi_1020_TAUCHI2, &b_phi_1020_TAUCHI2);
   fChain->SetBranchAddress("Kminus_MINIP", &Kminus_MINIP, &b_Kminus_MINIP);
   fChain->SetBranchAddress("Kminus_MINIPCHI2", &Kminus_MINIPCHI2, &b_Kminus_MINIPCHI2);
   fChain->SetBranchAddress("Kminus_MINIPNEXTBEST", &Kminus_MINIPNEXTBEST, &b_Kminus_MINIPNEXTBEST);
   fChain->SetBranchAddress("Kminus_MINIPCHI2NEXTBEST", &Kminus_MINIPCHI2NEXTBEST, &b_Kminus_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("Kminus_OWNPV_X", &Kminus_OWNPV_X, &b_Kminus_OWNPV_X);
   fChain->SetBranchAddress("Kminus_OWNPV_Y", &Kminus_OWNPV_Y, &b_Kminus_OWNPV_Y);
   fChain->SetBranchAddress("Kminus_OWNPV_Z", &Kminus_OWNPV_Z, &b_Kminus_OWNPV_Z);
   fChain->SetBranchAddress("Kminus_OWNPV_XERR", &Kminus_OWNPV_XERR, &b_Kminus_OWNPV_XERR);
   fChain->SetBranchAddress("Kminus_OWNPV_YERR", &Kminus_OWNPV_YERR, &b_Kminus_OWNPV_YERR);
   fChain->SetBranchAddress("Kminus_OWNPV_ZERR", &Kminus_OWNPV_ZERR, &b_Kminus_OWNPV_ZERR);
   fChain->SetBranchAddress("Kminus_OWNPV_CHI2", &Kminus_OWNPV_CHI2, &b_Kminus_OWNPV_CHI2);
   fChain->SetBranchAddress("Kminus_OWNPV_NDOF", &Kminus_OWNPV_NDOF, &b_Kminus_OWNPV_NDOF);
   fChain->SetBranchAddress("Kminus_OWNPV_COV_", Kminus_OWNPV_COV_, &b_Kminus_OWNPV_COV_);
   fChain->SetBranchAddress("Kminus_IP_OWNPV", &Kminus_IP_OWNPV, &b_Kminus_IP_OWNPV);
   fChain->SetBranchAddress("Kminus_IPCHI2_OWNPV", &Kminus_IPCHI2_OWNPV, &b_Kminus_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Kminus_ORIVX_X", &Kminus_ORIVX_X, &b_Kminus_ORIVX_X);
   fChain->SetBranchAddress("Kminus_ORIVX_Y", &Kminus_ORIVX_Y, &b_Kminus_ORIVX_Y);
   fChain->SetBranchAddress("Kminus_ORIVX_Z", &Kminus_ORIVX_Z, &b_Kminus_ORIVX_Z);
   fChain->SetBranchAddress("Kminus_ORIVX_XERR", &Kminus_ORIVX_XERR, &b_Kminus_ORIVX_XERR);
   fChain->SetBranchAddress("Kminus_ORIVX_YERR", &Kminus_ORIVX_YERR, &b_Kminus_ORIVX_YERR);
   fChain->SetBranchAddress("Kminus_ORIVX_ZERR", &Kminus_ORIVX_ZERR, &b_Kminus_ORIVX_ZERR);
   fChain->SetBranchAddress("Kminus_ORIVX_CHI2", &Kminus_ORIVX_CHI2, &b_Kminus_ORIVX_CHI2);
   fChain->SetBranchAddress("Kminus_ORIVX_NDOF", &Kminus_ORIVX_NDOF, &b_Kminus_ORIVX_NDOF);
   fChain->SetBranchAddress("Kminus_ORIVX_COV_", Kminus_ORIVX_COV_, &b_Kminus_ORIVX_COV_);
   fChain->SetBranchAddress("Kminus_P", &Kminus_P, &b_Kminus_P);
   fChain->SetBranchAddress("Kminus_PT", &Kminus_PT, &b_Kminus_PT);
   fChain->SetBranchAddress("Kminus_PE", &Kminus_PE, &b_Kminus_PE);
   fChain->SetBranchAddress("Kminus_PX", &Kminus_PX, &b_Kminus_PX);
   fChain->SetBranchAddress("Kminus_PY", &Kminus_PY, &b_Kminus_PY);
   fChain->SetBranchAddress("Kminus_PZ", &Kminus_PZ, &b_Kminus_PZ);
   fChain->SetBranchAddress("Kminus_M", &Kminus_M, &b_Kminus_M);
   fChain->SetBranchAddress("Kminus_ID", &Kminus_ID, &b_Kminus_ID);
   fChain->SetBranchAddress("Kminus_PIDe", &Kminus_PIDe, &b_Kminus_PIDe);
   fChain->SetBranchAddress("Kminus_PIDmu", &Kminus_PIDmu, &b_Kminus_PIDmu);
   fChain->SetBranchAddress("Kminus_PIDK", &Kminus_PIDK, &b_Kminus_PIDK);
   fChain->SetBranchAddress("Kminus_PIDp", &Kminus_PIDp, &b_Kminus_PIDp);
   fChain->SetBranchAddress("Kminus_ProbNNe", &Kminus_ProbNNe, &b_Kminus_ProbNNe);
   fChain->SetBranchAddress("Kminus_ProbNNk", &Kminus_ProbNNk, &b_Kminus_ProbNNk);
   fChain->SetBranchAddress("Kminus_ProbNNp", &Kminus_ProbNNp, &b_Kminus_ProbNNp);
   fChain->SetBranchAddress("Kminus_ProbNNpi", &Kminus_ProbNNpi, &b_Kminus_ProbNNpi);
   fChain->SetBranchAddress("Kminus_ProbNNmu", &Kminus_ProbNNmu, &b_Kminus_ProbNNmu);
   fChain->SetBranchAddress("Kminus_ProbNNghost", &Kminus_ProbNNghost, &b_Kminus_ProbNNghost);
   fChain->SetBranchAddress("Kminus_CaloEcalE", &Kminus_CaloEcalE, &b_Kminus_CaloEcalE);
   fChain->SetBranchAddress("Kminus_CaloHcalE", &Kminus_CaloHcalE, &b_Kminus_CaloHcalE);
   fChain->SetBranchAddress("Kminus_hasMuon", &Kminus_hasMuon, &b_Kminus_hasMuon);
   fChain->SetBranchAddress("Kminus_isMuon", &Kminus_isMuon, &b_Kminus_isMuon);
   fChain->SetBranchAddress("Kminus_hasRich", &Kminus_hasRich, &b_Kminus_hasRich);
   fChain->SetBranchAddress("Kminus_hasCalo", &Kminus_hasCalo, &b_Kminus_hasCalo);
   fChain->SetBranchAddress("Kminus_TRACK_Type", &Kminus_TRACK_Type, &b_Kminus_TRACK_Type);
   fChain->SetBranchAddress("Kminus_TRACK_Key", &Kminus_TRACK_Key, &b_Kminus_TRACK_Key);
   fChain->SetBranchAddress("Kminus_TRACK_CHI2NDOF", &Kminus_TRACK_CHI2NDOF, &b_Kminus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("Kminus_TRACK_PCHI2", &Kminus_TRACK_PCHI2, &b_Kminus_TRACK_PCHI2);
   fChain->SetBranchAddress("Kminus_TRACK_GhostProb", &Kminus_TRACK_GhostProb, &b_Kminus_TRACK_GhostProb);
   fChain->SetBranchAddress("Kminus_TRACK_CloneDist", &Kminus_TRACK_CloneDist, &b_Kminus_TRACK_CloneDist);
   fChain->SetBranchAddress("Kplus_MINIP", &Kplus_MINIP, &b_Kplus_MINIP);
   fChain->SetBranchAddress("Kplus_MINIPCHI2", &Kplus_MINIPCHI2, &b_Kplus_MINIPCHI2);
   fChain->SetBranchAddress("Kplus_MINIPNEXTBEST", &Kplus_MINIPNEXTBEST, &b_Kplus_MINIPNEXTBEST);
   fChain->SetBranchAddress("Kplus_MINIPCHI2NEXTBEST", &Kplus_MINIPCHI2NEXTBEST, &b_Kplus_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("Kplus_OWNPV_X", &Kplus_OWNPV_X, &b_Kplus_OWNPV_X);
   fChain->SetBranchAddress("Kplus_OWNPV_Y", &Kplus_OWNPV_Y, &b_Kplus_OWNPV_Y);
   fChain->SetBranchAddress("Kplus_OWNPV_Z", &Kplus_OWNPV_Z, &b_Kplus_OWNPV_Z);
   fChain->SetBranchAddress("Kplus_OWNPV_XERR", &Kplus_OWNPV_XERR, &b_Kplus_OWNPV_XERR);
   fChain->SetBranchAddress("Kplus_OWNPV_YERR", &Kplus_OWNPV_YERR, &b_Kplus_OWNPV_YERR);
   fChain->SetBranchAddress("Kplus_OWNPV_ZERR", &Kplus_OWNPV_ZERR, &b_Kplus_OWNPV_ZERR);
   fChain->SetBranchAddress("Kplus_OWNPV_CHI2", &Kplus_OWNPV_CHI2, &b_Kplus_OWNPV_CHI2);
   fChain->SetBranchAddress("Kplus_OWNPV_NDOF", &Kplus_OWNPV_NDOF, &b_Kplus_OWNPV_NDOF);
   fChain->SetBranchAddress("Kplus_OWNPV_COV_", Kplus_OWNPV_COV_, &b_Kplus_OWNPV_COV_);
   fChain->SetBranchAddress("Kplus_IP_OWNPV", &Kplus_IP_OWNPV, &b_Kplus_IP_OWNPV);
   fChain->SetBranchAddress("Kplus_IPCHI2_OWNPV", &Kplus_IPCHI2_OWNPV, &b_Kplus_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Kplus_ORIVX_X", &Kplus_ORIVX_X, &b_Kplus_ORIVX_X);
   fChain->SetBranchAddress("Kplus_ORIVX_Y", &Kplus_ORIVX_Y, &b_Kplus_ORIVX_Y);
   fChain->SetBranchAddress("Kplus_ORIVX_Z", &Kplus_ORIVX_Z, &b_Kplus_ORIVX_Z);
   fChain->SetBranchAddress("Kplus_ORIVX_XERR", &Kplus_ORIVX_XERR, &b_Kplus_ORIVX_XERR);
   fChain->SetBranchAddress("Kplus_ORIVX_YERR", &Kplus_ORIVX_YERR, &b_Kplus_ORIVX_YERR);
   fChain->SetBranchAddress("Kplus_ORIVX_ZERR", &Kplus_ORIVX_ZERR, &b_Kplus_ORIVX_ZERR);
   fChain->SetBranchAddress("Kplus_ORIVX_CHI2", &Kplus_ORIVX_CHI2, &b_Kplus_ORIVX_CHI2);
   fChain->SetBranchAddress("Kplus_ORIVX_NDOF", &Kplus_ORIVX_NDOF, &b_Kplus_ORIVX_NDOF);
   fChain->SetBranchAddress("Kplus_ORIVX_COV_", Kplus_ORIVX_COV_, &b_Kplus_ORIVX_COV_);
   fChain->SetBranchAddress("Kplus_P", &Kplus_P, &b_Kplus_P);
   fChain->SetBranchAddress("Kplus_PT", &Kplus_PT, &b_Kplus_PT);
   fChain->SetBranchAddress("Kplus_PE", &Kplus_PE, &b_Kplus_PE);
   fChain->SetBranchAddress("Kplus_PX", &Kplus_PX, &b_Kplus_PX);
   fChain->SetBranchAddress("Kplus_PY", &Kplus_PY, &b_Kplus_PY);
   fChain->SetBranchAddress("Kplus_PZ", &Kplus_PZ, &b_Kplus_PZ);
   fChain->SetBranchAddress("Kplus_M", &Kplus_M, &b_Kplus_M);
   fChain->SetBranchAddress("Kplus_ID", &Kplus_ID, &b_Kplus_ID);
   fChain->SetBranchAddress("Kplus_PIDe", &Kplus_PIDe, &b_Kplus_PIDe);
   fChain->SetBranchAddress("Kplus_PIDmu", &Kplus_PIDmu, &b_Kplus_PIDmu);
   fChain->SetBranchAddress("Kplus_PIDK", &Kplus_PIDK, &b_Kplus_PIDK);
   fChain->SetBranchAddress("Kplus_PIDp", &Kplus_PIDp, &b_Kplus_PIDp);
   fChain->SetBranchAddress("Kplus_ProbNNe", &Kplus_ProbNNe, &b_Kplus_ProbNNe);
   fChain->SetBranchAddress("Kplus_ProbNNk", &Kplus_ProbNNk, &b_Kplus_ProbNNk);
   fChain->SetBranchAddress("Kplus_ProbNNp", &Kplus_ProbNNp, &b_Kplus_ProbNNp);
   fChain->SetBranchAddress("Kplus_ProbNNpi", &Kplus_ProbNNpi, &b_Kplus_ProbNNpi);
   fChain->SetBranchAddress("Kplus_ProbNNmu", &Kplus_ProbNNmu, &b_Kplus_ProbNNmu);
   fChain->SetBranchAddress("Kplus_ProbNNghost", &Kplus_ProbNNghost, &b_Kplus_ProbNNghost);
   fChain->SetBranchAddress("Kplus_CaloEcalE", &Kplus_CaloEcalE, &b_Kplus_CaloEcalE);
   fChain->SetBranchAddress("Kplus_CaloHcalE", &Kplus_CaloHcalE, &b_Kplus_CaloHcalE);
   fChain->SetBranchAddress("Kplus_hasMuon", &Kplus_hasMuon, &b_Kplus_hasMuon);
   fChain->SetBranchAddress("Kplus_isMuon", &Kplus_isMuon, &b_Kplus_isMuon);
   fChain->SetBranchAddress("Kplus_hasRich", &Kplus_hasRich, &b_Kplus_hasRich);
   fChain->SetBranchAddress("Kplus_hasCalo", &Kplus_hasCalo, &b_Kplus_hasCalo);
   fChain->SetBranchAddress("Kplus_TRACK_Type", &Kplus_TRACK_Type, &b_Kplus_TRACK_Type);
   fChain->SetBranchAddress("Kplus_TRACK_Key", &Kplus_TRACK_Key, &b_Kplus_TRACK_Key);
   fChain->SetBranchAddress("Kplus_TRACK_CHI2NDOF", &Kplus_TRACK_CHI2NDOF, &b_Kplus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("Kplus_TRACK_PCHI2", &Kplus_TRACK_PCHI2, &b_Kplus_TRACK_PCHI2);
   fChain->SetBranchAddress("Kplus_TRACK_GhostProb", &Kplus_TRACK_GhostProb, &b_Kplus_TRACK_GhostProb);
   fChain->SetBranchAddress("Kplus_TRACK_CloneDist", &Kplus_TRACK_CloneDist, &b_Kplus_TRACK_CloneDist);
   fChain->SetBranchAddress("Psi_MINIP", &Psi_MINIP, &b_Psi_MINIP);
   fChain->SetBranchAddress("Psi_MINIPCHI2", &Psi_MINIPCHI2, &b_Psi_MINIPCHI2);
   fChain->SetBranchAddress("Psi_MINIPNEXTBEST", &Psi_MINIPNEXTBEST, &b_Psi_MINIPNEXTBEST);
   fChain->SetBranchAddress("Psi_MINIPCHI2NEXTBEST", &Psi_MINIPCHI2NEXTBEST, &b_Psi_MINIPCHI2NEXTBEST);
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
   fChain->SetBranchAddress("Psi_ENDVERTEX_X", &Psi_ENDVERTEX_X, &b_Psi_ENDVERTEX_X);
   fChain->SetBranchAddress("Psi_ENDVERTEX_Y", &Psi_ENDVERTEX_Y, &b_Psi_ENDVERTEX_Y);
   fChain->SetBranchAddress("Psi_ENDVERTEX_Z", &Psi_ENDVERTEX_Z, &b_Psi_ENDVERTEX_Z);
   fChain->SetBranchAddress("Psi_ENDVERTEX_XERR", &Psi_ENDVERTEX_XERR, &b_Psi_ENDVERTEX_XERR);
   fChain->SetBranchAddress("Psi_ENDVERTEX_YERR", &Psi_ENDVERTEX_YERR, &b_Psi_ENDVERTEX_YERR);
   fChain->SetBranchAddress("Psi_ENDVERTEX_ZERR", &Psi_ENDVERTEX_ZERR, &b_Psi_ENDVERTEX_ZERR);
   fChain->SetBranchAddress("Psi_ENDVERTEX_CHI2", &Psi_ENDVERTEX_CHI2, &b_Psi_ENDVERTEX_CHI2);
   fChain->SetBranchAddress("Psi_ENDVERTEX_NDOF", &Psi_ENDVERTEX_NDOF, &b_Psi_ENDVERTEX_NDOF);
   fChain->SetBranchAddress("Psi_ENDVERTEX_COV_", Psi_ENDVERTEX_COV_, &b_Psi_ENDVERTEX_COV_);
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
   fChain->SetBranchAddress("PsiL0Global_Dec", &PsiL0Global_Dec, &b_PsiL0Global_Dec);
   fChain->SetBranchAddress("PsiL0Global_TIS", &PsiL0Global_TIS, &b_PsiL0Global_TIS);
   fChain->SetBranchAddress("PsiL0Global_TOS", &PsiL0Global_TOS, &b_PsiL0Global_TOS);
   fChain->SetBranchAddress("PsiHlt1Global_Dec", &PsiHlt1Global_Dec, &b_PsiHlt1Global_Dec);
   fChain->SetBranchAddress("PsiHlt1Global_TIS", &PsiHlt1Global_TIS, &b_PsiHlt1Global_TIS);
   fChain->SetBranchAddress("PsiHlt1Global_TOS", &PsiHlt1Global_TOS, &b_PsiHlt1Global_TOS);
   fChain->SetBranchAddress("PsiHlt2Global_Dec", &PsiHlt2Global_Dec, &b_PsiHlt2Global_Dec);
   fChain->SetBranchAddress("PsiHlt2Global_TIS", &PsiHlt2Global_TIS, &b_PsiHlt2Global_TIS);
   fChain->SetBranchAddress("PsiHlt2Global_TOS", &PsiHlt2Global_TOS, &b_PsiHlt2Global_TOS);
   fChain->SetBranchAddress("PsiHlt1TrackAllL0Decision_Dec", &PsiHlt1TrackAllL0Decision_Dec, &b_PsiHlt1TrackAllL0Decision_Dec);
   fChain->SetBranchAddress("PsiHlt1TrackAllL0Decision_TIS", &PsiHlt1TrackAllL0Decision_TIS, &b_PsiHlt1TrackAllL0Decision_TIS);
   fChain->SetBranchAddress("PsiHlt1TrackAllL0Decision_TOS", &PsiHlt1TrackAllL0Decision_TOS, &b_PsiHlt1TrackAllL0Decision_TOS);
   fChain->SetBranchAddress("PsiHlt1MuTrackDecision_Dec", &PsiHlt1MuTrackDecision_Dec, &b_PsiHlt1MuTrackDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1MuTrackDecision_TIS", &PsiHlt1MuTrackDecision_TIS, &b_PsiHlt1MuTrackDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1MuTrackDecision_TOS", &PsiHlt1MuTrackDecision_TOS, &b_PsiHlt1MuTrackDecision_TOS);
   fChain->SetBranchAddress("PsiHlt1DiMuonNoIP2L0Decision_Dec", &PsiHlt1DiMuonNoIP2L0Decision_Dec, &b_PsiHlt1DiMuonNoIP2L0Decision_Dec);
   fChain->SetBranchAddress("PsiHlt1DiMuonNoIP2L0Decision_TIS", &PsiHlt1DiMuonNoIP2L0Decision_TIS, &b_PsiHlt1DiMuonNoIP2L0Decision_TIS);
   fChain->SetBranchAddress("PsiHlt1DiMuonNoIP2L0Decision_TOS", &PsiHlt1DiMuonNoIP2L0Decision_TOS, &b_PsiHlt1DiMuonNoIP2L0Decision_TOS);
   fChain->SetBranchAddress("PsiHlt1DiMuonNoIPL0SegDecision_Dec", &PsiHlt1DiMuonNoIPL0SegDecision_Dec, &b_PsiHlt1DiMuonNoIPL0SegDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1DiMuonNoIPL0SegDecision_TIS", &PsiHlt1DiMuonNoIPL0SegDecision_TIS, &b_PsiHlt1DiMuonNoIPL0SegDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1DiMuonNoIPL0SegDecision_TOS", &PsiHlt1DiMuonNoIPL0SegDecision_TOS, &b_PsiHlt1DiMuonNoIPL0SegDecision_TOS);
   fChain->SetBranchAddress("PsiHlt1DiMuonIPCL0DiDecision_Dec", &PsiHlt1DiMuonIPCL0DiDecision_Dec, &b_PsiHlt1DiMuonIPCL0DiDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1DiMuonIPCL0DiDecision_TIS", &PsiHlt1DiMuonIPCL0DiDecision_TIS, &b_PsiHlt1DiMuonIPCL0DiDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1DiMuonIPCL0DiDecision_TOS", &PsiHlt1DiMuonIPCL0DiDecision_TOS, &b_PsiHlt1DiMuonIPCL0DiDecision_TOS);
   fChain->SetBranchAddress("PsiHlt1DiMuonIPC2L0Decision_Dec", &PsiHlt1DiMuonIPC2L0Decision_Dec, &b_PsiHlt1DiMuonIPC2L0Decision_Dec);
   fChain->SetBranchAddress("PsiHlt1DiMuonIPC2L0Decision_TIS", &PsiHlt1DiMuonIPC2L0Decision_TIS, &b_PsiHlt1DiMuonIPC2L0Decision_TIS);
   fChain->SetBranchAddress("PsiHlt1DiMuonIPC2L0Decision_TOS", &PsiHlt1DiMuonIPC2L0Decision_TOS, &b_PsiHlt1DiMuonIPC2L0Decision_TOS);
   fChain->SetBranchAddress("PsiHlt1DiMuonIPCL0SegDecision_Dec", &PsiHlt1DiMuonIPCL0SegDecision_Dec, &b_PsiHlt1DiMuonIPCL0SegDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1DiMuonIPCL0SegDecision_TIS", &PsiHlt1DiMuonIPCL0SegDecision_TIS, &b_PsiHlt1DiMuonIPCL0SegDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1DiMuonIPCL0SegDecision_TOS", &PsiHlt1DiMuonIPCL0SegDecision_TOS, &b_PsiHlt1DiMuonIPCL0SegDecision_TOS);
   fChain->SetBranchAddress("PsiHlt1DiMuonHighMassDecision_Dec", &PsiHlt1DiMuonHighMassDecision_Dec, &b_PsiHlt1DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1DiMuonHighMassDecision_TIS", &PsiHlt1DiMuonHighMassDecision_TIS, &b_PsiHlt1DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1DiMuonHighMassDecision_TOS", &PsiHlt1DiMuonHighMassDecision_TOS, &b_PsiHlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("PsiHlt1DiMuonLowMassDecision_Dec", &PsiHlt1DiMuonLowMassDecision_Dec, &b_PsiHlt1DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1DiMuonLowMassDecision_TIS", &PsiHlt1DiMuonLowMassDecision_TIS, &b_PsiHlt1DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1DiMuonLowMassDecision_TOS", &PsiHlt1DiMuonLowMassDecision_TOS, &b_PsiHlt1DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("PsiHlt1SingleMuonNoIPL0Decision_Dec", &PsiHlt1SingleMuonNoIPL0Decision_Dec, &b_PsiHlt1SingleMuonNoIPL0Decision_Dec);
   fChain->SetBranchAddress("PsiHlt1SingleMuonNoIPL0Decision_TIS", &PsiHlt1SingleMuonNoIPL0Decision_TIS, &b_PsiHlt1SingleMuonNoIPL0Decision_TIS);
   fChain->SetBranchAddress("PsiHlt1SingleMuonNoIPL0Decision_TOS", &PsiHlt1SingleMuonNoIPL0Decision_TOS, &b_PsiHlt1SingleMuonNoIPL0Decision_TOS);
   fChain->SetBranchAddress("PsiHlt1SingleMuonNoIPL0HighPTDecision_Dec", &PsiHlt1SingleMuonNoIPL0HighPTDecision_Dec, &b_PsiHlt1SingleMuonNoIPL0HighPTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1SingleMuonNoIPL0HighPTDecision_TIS", &PsiHlt1SingleMuonNoIPL0HighPTDecision_TIS, &b_PsiHlt1SingleMuonNoIPL0HighPTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1SingleMuonNoIPL0HighPTDecision_TOS", &PsiHlt1SingleMuonNoIPL0HighPTDecision_TOS, &b_PsiHlt1SingleMuonNoIPL0HighPTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt1SingleMuonIPCL0Decision_Dec", &PsiHlt1SingleMuonIPCL0Decision_Dec, &b_PsiHlt1SingleMuonIPCL0Decision_Dec);
   fChain->SetBranchAddress("PsiHlt1SingleMuonIPCL0Decision_TIS", &PsiHlt1SingleMuonIPCL0Decision_TIS, &b_PsiHlt1SingleMuonIPCL0Decision_TIS);
   fChain->SetBranchAddress("PsiHlt1SingleMuonIPCL0Decision_TOS", &PsiHlt1SingleMuonIPCL0Decision_TOS, &b_PsiHlt1SingleMuonIPCL0Decision_TOS);
   fChain->SetBranchAddress("PsiHlt1SingleMuonNoIPDecision_Dec", &PsiHlt1SingleMuonNoIPDecision_Dec, &b_PsiHlt1SingleMuonNoIPDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1SingleMuonNoIPDecision_TIS", &PsiHlt1SingleMuonNoIPDecision_TIS, &b_PsiHlt1SingleMuonNoIPDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1SingleMuonNoIPDecision_TOS", &PsiHlt1SingleMuonNoIPDecision_TOS, &b_PsiHlt1SingleMuonNoIPDecision_TOS);
   fChain->SetBranchAddress("PsiHlt1TrackMuonDecision_Dec", &PsiHlt1TrackMuonDecision_Dec, &b_PsiHlt1TrackMuonDecision_Dec);
   fChain->SetBranchAddress("PsiHlt1TrackMuonDecision_TIS", &PsiHlt1TrackMuonDecision_TIS, &b_PsiHlt1TrackMuonDecision_TIS);
   fChain->SetBranchAddress("PsiHlt1TrackMuonDecision_TOS", &PsiHlt1TrackMuonDecision_TOS, &b_PsiHlt1TrackMuonDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2TopoTF3BodyReq2YesDecision_Dec", &PsiHlt2TopoTF3BodyReq2YesDecision_Dec, &b_PsiHlt2TopoTF3BodyReq2YesDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2TopoTF3BodyReq2YesDecision_TIS", &PsiHlt2TopoTF3BodyReq2YesDecision_TIS, &b_PsiHlt2TopoTF3BodyReq2YesDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2TopoTF3BodyReq2YesDecision_TOS", &PsiHlt2TopoTF3BodyReq2YesDecision_TOS, &b_PsiHlt2TopoTF3BodyReq2YesDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2TopoTF3BodyReq3YesDecision_Dec", &PsiHlt2TopoTF3BodyReq3YesDecision_Dec, &b_PsiHlt2TopoTF3BodyReq3YesDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2TopoTF3BodyReq3YesDecision_TIS", &PsiHlt2TopoTF3BodyReq3YesDecision_TIS, &b_PsiHlt2TopoTF3BodyReq3YesDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2TopoTF3BodyReq3YesDecision_TOS", &PsiHlt2TopoTF3BodyReq3YesDecision_TOS, &b_PsiHlt2TopoTF3BodyReq3YesDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2TopoOSTF2BodyDecision_Dec", &PsiHlt2TopoOSTF2BodyDecision_Dec, &b_PsiHlt2TopoOSTF2BodyDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2TopoOSTF2BodyDecision_TIS", &PsiHlt2TopoOSTF2BodyDecision_TIS, &b_PsiHlt2TopoOSTF2BodyDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2TopoOSTF2BodyDecision_TOS", &PsiHlt2TopoOSTF2BodyDecision_TOS, &b_PsiHlt2TopoOSTF2BodyDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2TopoOSTF3BodyDecision_Dec", &PsiHlt2TopoOSTF3BodyDecision_Dec, &b_PsiHlt2TopoOSTF3BodyDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2TopoOSTF3BodyDecision_TIS", &PsiHlt2TopoOSTF3BodyDecision_TIS, &b_PsiHlt2TopoOSTF3BodyDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2TopoOSTF3BodyDecision_TOS", &PsiHlt2TopoOSTF3BodyDecision_TOS, &b_PsiHlt2TopoOSTF3BodyDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2TopoOSTF4BodyDecision_Dec", &PsiHlt2TopoOSTF4BodyDecision_Dec, &b_PsiHlt2TopoOSTF4BodyDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2TopoOSTF4BodyDecision_TIS", &PsiHlt2TopoOSTF4BodyDecision_TIS, &b_PsiHlt2TopoOSTF4BodyDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2TopoOSTF4BodyDecision_TOS", &PsiHlt2TopoOSTF4BodyDecision_TOS, &b_PsiHlt2TopoOSTF4BodyDecision_TOS);
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
   fChain->SetBranchAddress("PsiHlt2MuTrackDecision_Dec", &PsiHlt2MuTrackDecision_Dec, &b_PsiHlt2MuTrackDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2MuTrackDecision_TIS", &PsiHlt2MuTrackDecision_TIS, &b_PsiHlt2MuTrackDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2MuTrackDecision_TOS", &PsiHlt2MuTrackDecision_TOS, &b_PsiHlt2MuTrackDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2MuTrackNoIPDecision_Dec", &PsiHlt2MuTrackNoIPDecision_Dec, &b_PsiHlt2MuTrackNoIPDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2MuTrackNoIPDecision_TIS", &PsiHlt2MuTrackNoIPDecision_TIS, &b_PsiHlt2MuTrackNoIPDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2MuTrackNoIPDecision_TOS", &PsiHlt2MuTrackNoIPDecision_TOS, &b_PsiHlt2MuTrackNoIPDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonDecision_Dec", &PsiHlt2SingleMuonDecision_Dec, &b_PsiHlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2SingleMuonDecision_TIS", &PsiHlt2SingleMuonDecision_TIS, &b_PsiHlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonDecision_TOS", &PsiHlt2SingleMuonDecision_TOS, &b_PsiHlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2UnbiasedDiMuonDecision_Dec", &PsiHlt2UnbiasedDiMuonDecision_Dec, &b_PsiHlt2UnbiasedDiMuonDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2UnbiasedDiMuonDecision_TIS", &PsiHlt2UnbiasedDiMuonDecision_TIS, &b_PsiHlt2UnbiasedDiMuonDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2UnbiasedDiMuonDecision_TOS", &PsiHlt2UnbiasedDiMuonDecision_TOS, &b_PsiHlt2UnbiasedDiMuonDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2UnbiasedDiMuonLowMassDecision_Dec", &PsiHlt2UnbiasedDiMuonLowMassDecision_Dec, &b_PsiHlt2UnbiasedDiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2UnbiasedDiMuonLowMassDecision_TIS", &PsiHlt2UnbiasedDiMuonLowMassDecision_TIS, &b_PsiHlt2UnbiasedDiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2UnbiasedDiMuonLowMassDecision_TOS", &PsiHlt2UnbiasedDiMuonLowMassDecision_TOS, &b_PsiHlt2UnbiasedDiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonUnbiasedJPsiDecision_Dec", &PsiHlt2DiMuonUnbiasedJPsiDecision_Dec, &b_PsiHlt2DiMuonUnbiasedJPsiDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonUnbiasedJPsiDecision_TIS", &PsiHlt2DiMuonUnbiasedJPsiDecision_TIS, &b_PsiHlt2DiMuonUnbiasedJPsiDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonUnbiasedJPsiDecision_TOS", &PsiHlt2DiMuonUnbiasedJPsiDecision_TOS, &b_PsiHlt2DiMuonUnbiasedJPsiDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonUnbiasedPsi2SDecision_Dec", &PsiHlt2DiMuonUnbiasedPsi2SDecision_Dec, &b_PsiHlt2DiMuonUnbiasedPsi2SDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonUnbiasedPsi2SDecision_TIS", &PsiHlt2DiMuonUnbiasedPsi2SDecision_TIS, &b_PsiHlt2DiMuonUnbiasedPsi2SDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonUnbiasedPsi2SDecision_TOS", &PsiHlt2DiMuonUnbiasedPsi2SDecision_TOS, &b_PsiHlt2DiMuonUnbiasedPsi2SDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2BiasedDiMuonSimpleDecision_Dec", &PsiHlt2BiasedDiMuonSimpleDecision_Dec, &b_PsiHlt2BiasedDiMuonSimpleDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2BiasedDiMuonSimpleDecision_TIS", &PsiHlt2BiasedDiMuonSimpleDecision_TIS, &b_PsiHlt2BiasedDiMuonSimpleDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2BiasedDiMuonSimpleDecision_TOS", &PsiHlt2BiasedDiMuonSimpleDecision_TOS, &b_PsiHlt2BiasedDiMuonSimpleDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2BiasedDiMuonRefinedDecision_Dec", &PsiHlt2BiasedDiMuonRefinedDecision_Dec, &b_PsiHlt2BiasedDiMuonRefinedDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2BiasedDiMuonRefinedDecision_TIS", &PsiHlt2BiasedDiMuonRefinedDecision_TIS, &b_PsiHlt2BiasedDiMuonRefinedDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2BiasedDiMuonRefinedDecision_TOS", &PsiHlt2BiasedDiMuonRefinedDecision_TOS, &b_PsiHlt2BiasedDiMuonRefinedDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2BiasedDiMuonMassDecision_Dec", &PsiHlt2BiasedDiMuonMassDecision_Dec, &b_PsiHlt2BiasedDiMuonMassDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2BiasedDiMuonMassDecision_TIS", &PsiHlt2BiasedDiMuonMassDecision_TIS, &b_PsiHlt2BiasedDiMuonMassDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2BiasedDiMuonMassDecision_TOS", &PsiHlt2BiasedDiMuonMassDecision_TOS, &b_PsiHlt2BiasedDiMuonMassDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2BiasedDiMuonIPDecision_Dec", &PsiHlt2BiasedDiMuonIPDecision_Dec, &b_PsiHlt2BiasedDiMuonIPDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2BiasedDiMuonIPDecision_TIS", &PsiHlt2BiasedDiMuonIPDecision_TIS, &b_PsiHlt2BiasedDiMuonIPDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2BiasedDiMuonIPDecision_TOS", &PsiHlt2BiasedDiMuonIPDecision_TOS, &b_PsiHlt2BiasedDiMuonIPDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2DiMuonBiasedJPsiDecision_Dec", &PsiHlt2DiMuonBiasedJPsiDecision_Dec, &b_PsiHlt2DiMuonBiasedJPsiDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2DiMuonBiasedJPsiDecision_TIS", &PsiHlt2DiMuonBiasedJPsiDecision_TIS, &b_PsiHlt2DiMuonBiasedJPsiDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2DiMuonBiasedJPsiDecision_TOS", &PsiHlt2DiMuonBiasedJPsiDecision_TOS, &b_PsiHlt2DiMuonBiasedJPsiDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2TopoMu2BodyBBDTDecision_Dec", &PsiHlt2TopoMu2BodyBBDTDecision_Dec, &b_PsiHlt2TopoMu2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2TopoMu2BodyBBDTDecision_TIS", &PsiHlt2TopoMu2BodyBBDTDecision_TIS, &b_PsiHlt2TopoMu2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2TopoMu2BodyBBDTDecision_TOS", &PsiHlt2TopoMu2BodyBBDTDecision_TOS, &b_PsiHlt2TopoMu2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2TopoMu3BodyBBDTDecision_Dec", &PsiHlt2TopoMu3BodyBBDTDecision_Dec, &b_PsiHlt2TopoMu3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2TopoMu3BodyBBDTDecision_TIS", &PsiHlt2TopoMu3BodyBBDTDecision_TIS, &b_PsiHlt2TopoMu3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2TopoMu3BodyBBDTDecision_TOS", &PsiHlt2TopoMu3BodyBBDTDecision_TOS, &b_PsiHlt2TopoMu3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2TopoMu4BodyBBDTDecision_Dec", &PsiHlt2TopoMu4BodyBBDTDecision_Dec, &b_PsiHlt2TopoMu4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2TopoMu4BodyBBDTDecision_TIS", &PsiHlt2TopoMu4BodyBBDTDecision_TIS, &b_PsiHlt2TopoMu4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2TopoMu4BodyBBDTDecision_TOS", &PsiHlt2TopoMu4BodyBBDTDecision_TOS, &b_PsiHlt2TopoMu4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonHighPTDecision_Dec", &PsiHlt2SingleMuonHighPTDecision_Dec, &b_PsiHlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2SingleMuonHighPTDecision_TIS", &PsiHlt2SingleMuonHighPTDecision_TIS, &b_PsiHlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonHighPTDecision_TOS", &PsiHlt2SingleMuonHighPTDecision_TOS, &b_PsiHlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonLowPTDecision_Dec", &PsiHlt2SingleMuonLowPTDecision_Dec, &b_PsiHlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("PsiHlt2SingleMuonLowPTDecision_TIS", &PsiHlt2SingleMuonLowPTDecision_TIS, &b_PsiHlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("PsiHlt2SingleMuonLowPTDecision_TOS", &PsiHlt2SingleMuonLowPTDecision_TOS, &b_PsiHlt2SingleMuonLowPTDecision_TOS);
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
   fChain->SetBranchAddress("muminus_CaloEcalE", &muminus_CaloEcalE, &b_muminus_CaloEcalE);
   fChain->SetBranchAddress("muminus_CaloHcalE", &muminus_CaloHcalE, &b_muminus_CaloHcalE);
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
   fChain->SetBranchAddress("muplus_CaloEcalE", &muplus_CaloEcalE, &b_muplus_CaloEcalE);
   fChain->SetBranchAddress("muplus_CaloHcalE", &muplus_CaloHcalE, &b_muplus_CaloHcalE);
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
   fChain->SetBranchAddress("Primaries", &Primaries, &b_Primaries);
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
   fChain->SetBranchAddress("ChargedProtos", &ChargedProtos, &b_ChargedProtos);
   fChain->SetBranchAddress("NeutralProtos", &NeutralProtos, &b_NeutralProtos);
   fChain->SetBranchAddress("BestTracks", &BestTracks, &b_BestTracks);
   fChain->SetBranchAddress("MuonTracks", &MuonTracks, &b_MuonTracks);
   fChain->SetBranchAddress("ITClusters", &ITClusters, &b_ITClusters);
   fChain->SetBranchAddress("VeloLiteClusters", &VeloLiteClusters, &b_VeloLiteClusters);
   fChain->SetBranchAddress("OTClusters", &OTClusters, &b_OTClusters);
   fChain->SetBranchAddress("spdMult", &spdMult, &b_spdMult);
   fChain->SetBranchAddress("backwardTracks", &backwardTracks, &b_backwardTracks);
   fChain->SetBranchAddress("veloTracks", &veloTracks, &b_veloTracks);
   fChain->SetBranchAddress("longTracks", &longTracks, &b_longTracks);
   fChain->SetBranchAddress("goodLongTracks", &goodLongTracks, &b_goodLongTracks);
   //} // end init from Castor
}

#endif // #ifdef B2JpsiPhi_2011_cxx
