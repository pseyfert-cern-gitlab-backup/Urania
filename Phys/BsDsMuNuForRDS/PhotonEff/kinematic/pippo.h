//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Nov  7 18:09:22 2012 by ROOT version 5.28/00
// from TTree Bu2D0X/Output of CUTS
// found on file: B2D0Pi_D02KPi_recoas_b2dk_d2kpi_misID.root
//////////////////////////////////////////////////////////

#ifndef pippo_h
#define pippo_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

class pippo : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           runNumber;
   Int_t           eventNumber;
   Int_t           nPV;
   Float_t         Bu_M;
   Float_t         D0_M;
   Float_t         Bu_DPVCFIT_M;
   Float_t         Bu_DPVCFIT_CHI2NDOF;
   Float_t         Bu_DPVCFIT_D0M;
   Float_t         D0_FD_ZSIG;
   Float_t         D0_M_DOUBLESW;
   Float_t         Bu_M_DOUBLESW;
   Float_t         Bu_M_DOUBLESW_Khyp;
   Float_t         Bu_M_DOUBLESW_Pihyp;
   Int_t           OdinTCK;
   Int_t           HLTTCK;
   Int_t           L0DUTCK;
   Float_t         jpsi_veto;
   Float_t         jpsi_veto_raw;
   Int_t           first_isMuon;
   Int_t           second_isMuon;
   Float_t         Bu_P;
   Float_t         Bu_PT;
   Float_t         D0_P;
   Float_t         D0_PT;
   Float_t         Bach_P;
   Float_t         Bach_PT;
   Int_t           Bu_ID;
   Int_t           Bu_Q;
   Float_t         Bu_FD_BPV_SIGNED;
   Float_t         Bu_LV01;
   Float_t         Bu_LV02;
   Float_t         Bach_PIDK;
   Float_t         K_PIDK;
   Float_t         P_PIDK;
   Float_t         Bu_VTXCHI2DOF;
   Float_t         Bu_ENDVTX_X;
   Float_t         Bu_ENDVTX_Y;
   Float_t         Bu_ENDVTX_Z;
   Float_t         Bu_ENDVERTEX_X;
   Float_t         Bu_ENDVERTEX_Y;
   Float_t         Bu_ENDVERTEX_Z;
   Float_t         Bu_ENDVERTEX_XERR;
   Float_t         Bu_ENDVERTEX_YERR;
   Float_t         Bu_ENDVERTEX_ZERR;
   Float_t         D0_VTXCHI2DOF;
   Float_t         D0_ENDVTX_Z;
   Int_t           BuL0Global_Dec;
   Int_t           BuL0Global_TIS;
   Int_t           BuL0Global_TOS;
   Int_t           BuHlt1Global_Dec;
   Int_t           BuHlt1Global_TIS;
   Int_t           BuHlt1Global_TOS;
   Int_t           BuHlt2Global_Dec;
   Int_t           BuHlt2Global_TIS;
   Int_t           BuHlt2Global_TOS;
   Int_t           BuL0HadronDecision_Dec;
   Int_t           BuL0HadronDecision_TIS;
   Int_t           BuL0HadronDecision_TOS;
   Int_t           BuL0MuonDecision_Dec;
   Int_t           BuL0MuonDecision_TIS;
   Int_t           BuL0MuonDecision_TOS;
   Int_t           BuL0DiMuonDecision_Dec;
   Int_t           BuL0DiMuonDecision_TIS;
   Int_t           BuL0DiMuonDecision_TOS;
   Int_t           BuL0MuonHighDecision_Dec;
   Int_t           BuL0MuonHighDecision_TIS;
   Int_t           BuL0MuonHighDecision_TOS;
   Int_t           Bach_isMuon;
   Int_t           Bach_hasRich;
   Int_t           K_isMuon;
   Int_t           K_hasRich;
   Int_t           P_isMuon;
   Int_t           P_hasRich;
   Float_t         Bach_TRACK_Eta;
   Float_t         P_TRACK_Eta;
   Float_t         K_TRACK_Eta;
   Float_t         nTracks;
   Int_t           BuHlt1TrackAllL0Decision_Dec;
   Int_t           BuHlt1TrackAllL0Decision_TIS;
   Int_t           BuHlt1TrackAllL0Decision_TOS;
   Int_t           BuHlt1TrackMuonDecision_Dec;
   Int_t           BuHlt1TrackMuonDecision_TIS;
   Int_t           BuHlt1TrackMuonDecision_TOS;
   Int_t           BuHlt1TrackPhotonDecision_Dec;
   Int_t           BuHlt1TrackPhotonDecision_TIS;
   Int_t           BuHlt1TrackPhotonDecision_TOS;
   Int_t           BuHlt1SingleMuonNoIPL0Decision_Dec;
   Int_t           BuHlt1SingleMuonNoIPL0Decision_TIS;
   Int_t           BuHlt1SingleMuonNoIPL0Decision_TOS;
   Int_t           BuHlt2Topo2BodyBBDTDecision_Dec;
   Int_t           BuHlt2Topo2BodyBBDTDecision_TIS;
   Int_t           BuHlt2Topo2BodyBBDTDecision_TOS;
   Int_t           BuHlt2Topo3BodyBBDTDecision_Dec;
   Int_t           BuHlt2Topo3BodyBBDTDecision_TIS;
   Int_t           BuHlt2Topo3BodyBBDTDecision_TOS;
   Int_t           BuHlt2Topo4BodyBBDTDecision_Dec;
   Int_t           BuHlt2Topo4BodyBBDTDecision_TIS;
   Int_t           BuHlt2Topo4BodyBBDTDecision_TOS;
   Int_t           BuHlt2Topo2BodySimpleDecision_Dec;
   Int_t           BuHlt2Topo2BodySimpleDecision_TIS;
   Int_t           BuHlt2Topo2BodySimpleDecision_TOS;
   Int_t           BuHlt2Topo3BodySimpleDecision_Dec;
   Int_t           BuHlt2Topo3BodySimpleDecision_TIS;
   Int_t           BuHlt2Topo3BodySimpleDecision_TOS;
   Int_t           BuHlt2Topo4BodySimpleDecision_Dec;
   Int_t           BuHlt2Topo4BodySimpleDecision_TIS;
   Int_t           BuHlt2Topo4BodySimpleDecision_TOS;
   Int_t           BuHlt2CharmOSTF3BodyDecision_Dec;
   Int_t           BuHlt2CharmOSTF3BodyDecision_TIS;
   Int_t           BuHlt2CharmOSTF3BodyDecision_TOS;
   Int_t           BuHlt2CharmOSTF2BodyDecision_Dec;
   Int_t           BuHlt2CharmOSTF2BodyDecision_TIS;
   Int_t           BuHlt2CharmOSTF2BodyDecision_TOS;
   Int_t           BuHlt2CharmTF3BodySADecision_Dec;
   Int_t           BuHlt2CharmTF3BodySADecision_TIS;
   Int_t           BuHlt2CharmTF3BodySADecision_TOS;
   Int_t           BuHlt2CharmTF2BodySADecision_Dec;
   Int_t           BuHlt2CharmTF2BodySADecision_TIS;
   Int_t           BuHlt2CharmTF2BodySADecision_TOS;
   Int_t           BuHlt2DiMuonUnbiasedJPsiDecision_Dec;
   Int_t           BuHlt2DiMuonUnbiasedJPsiDecision_TIS;
   Int_t           BuHlt2DiMuonUnbiasedJPsiDecision_TOS;
   Float_t         Bach_PIDe;
   Float_t         Bach_PIDmu;
   Float_t         Bach_PIDp;
   Float_t         K_PIDe;
   Float_t         K_PIDmu;
   Float_t         K_PIDp;
   Float_t         P_PIDe;
   Float_t         P_PIDmu;
   Float_t         P_PIDp;
   Float_t         Bach_ProbNNe;
   Float_t         Bach_ProbNNk;
   Float_t         Bach_ProbNNp;
   Float_t         Bach_ProbNNpi;
   Float_t         Bach_ProbNNmu;
   Float_t         Bach_ProbNNghost;
   Float_t         Bach_CaloEcalE;
   Float_t         Bach_CaloHcalE;
   Float_t         Bach_PE;
   Float_t         Bach_PX;
   Float_t         Bach_PY;
   Float_t         Bach_PZ;
   Float_t         K_PE;
   Float_t         K_PX;
   Float_t         K_PY;
   Float_t         K_PZ;
   Float_t         P_PE;
   Float_t         P_PX;
   Float_t         P_PY;
   Float_t         P_PZ;
   Int_t           Bach_ID;
   Int_t           K_ID;
   Int_t           P_ID;
   Float_t         Bu_DPVCFIT_D0P;
   Float_t         Bu_DPVCFIT_BachP;
   Float_t         Bu_DPVCFIT_P;
   Float_t         K_P;
   Float_t         P_P;
   Int_t           Bu_BKGCAT;
   Int_t           D0_BKGCAT;
   Int_t           Bu_TRUEID;
   Int_t           Bu_MC_MOTHER_ID;
   Int_t           Bu_MC_GD_MOTHER_ID;
   Int_t           Bu_MC_GD_GD_MOTHER_ID;
   Float_t         Bu_TRUEP_E;
   Float_t         Bu_TRUEP_X;
   Float_t         Bu_TRUEP_Y;
   Float_t         Bu_TRUEP_Z;
   Float_t         Bu_TRUEPT;
   Int_t           D0_TRUEID;
   Int_t           D0_MC_MOTHER_ID;
   Int_t           D0_MC_GD_MOTHER_ID;
   Int_t           D0_MC_GD_GD_MOTHER_ID;
   Float_t         D0_TRUEP_E;
   Float_t         D0_TRUEP_X;
   Float_t         D0_TRUEP_Y;
   Float_t         D0_TRUEP_Z;
   Float_t         D0_TRUEPT;
   Int_t           Bach_TRUEID;
   Int_t           Bach_MC_MOTHER_ID;
   Int_t           Bach_MC_GD_MOTHER_ID;
   Int_t           Bach_MC_GD_GD_MOTHER_ID;
   Float_t         Bach_TRUEP_E;
   Float_t         Bach_TRUEP_X;
   Float_t         Bach_TRUEP_Y;
   Float_t         Bach_TRUEP_Z;
   Float_t         Bach_TRUEPT;
   Int_t           K_TRUEID;
   Int_t           K_MC_MOTHER_ID;
   Int_t           K_MC_GD_MOTHER_ID;
   Int_t           K_MC_GD_GD_MOTHER_ID;
   Float_t         K_TRUEP_E;
   Float_t         K_TRUEP_X;
   Float_t         K_TRUEP_Y;
   Float_t         K_TRUEP_Z;
   Float_t         K_TRUEPT;
   Int_t           P_TRUEID;
   Int_t           P_MC_MOTHER_ID;
   Int_t           P_MC_GD_MOTHER_ID;
   Int_t           P_MC_GD_GD_MOTHER_ID;
   Float_t         P_TRUEP_E;
   Float_t         P_TRUEP_X;
   Float_t         P_TRUEP_Y;
   Float_t         P_TRUEP_Z;
   Float_t         P_TRUEPT;
   Float_t         trueM;
   Float_t         trueM_misID;
   Float_t         trueD0M;
   Float_t         BDT;

   // List of branches
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_nPV;   //!
   TBranch        *b_Bu_M;   //!
   TBranch        *b_D0_M;   //!
   TBranch        *b_Bu_DPVCFIT_M;   //!
   TBranch        *b_Bu_DPVCFIT_CHI2NDOF;   //!
   TBranch        *b_Bu_DPVCFIT_D0M;   //!
   TBranch        *b_D0_FD_ZSIG;   //!
   TBranch        *b_D0_M_DOUBLESW;   //!
   TBranch        *b_Bu_M_DOUBLESW;   //!
   TBranch        *b_Bu_M_DOUBLESW_Khyp;   //!
   TBranch        *b_Bu_M_DOUBLESW_Pihyp;   //!
   TBranch        *b_OdinTCK;   //!
   TBranch        *b_HLTTCK;   //!
   TBranch        *b_L0DUTCK;   //!
   TBranch        *b_jpsi_veto;   //!
   TBranch        *b_jpsi_veto_raw;   //!
   TBranch        *b_first_isMuon;   //!
   TBranch        *b_second_isMuon;   //!
   TBranch        *b_Bu_P;   //!
   TBranch        *b_Bu_PT;   //!
   TBranch        *b_D0_P;   //!
   TBranch        *b_D0_PT;   //!
   TBranch        *b_Bach_P;   //!
   TBranch        *b_Bach_PT;   //!
   TBranch        *b_Bu_ID;   //!
   TBranch        *b_Bu_Q;   //!
   TBranch        *b_Bu_FD_BPV_SIGNED;   //!
   TBranch        *b_Bu_LV01;   //!
   TBranch        *b_Bu_LV02;   //!
   TBranch        *b_Bach_PIDK;   //!
   TBranch        *b_K_PIDK;   //!
   TBranch        *b_P_PIDK;   //!
   TBranch        *b_Bu_VTXCHI2DOF;   //!
   TBranch        *b_Bu_ENDVTX_X;   //!
   TBranch        *b_Bu_ENDVTX_Y;   //!
   TBranch        *b_Bu_ENDVTX_Z;   //!
   TBranch        *b_Bu_ENDVERTEX_X;   //!
   TBranch        *b_Bu_ENDVERTEX_Y;   //!
   TBranch        *b_Bu_ENDVERTEX_Z;   //!
   TBranch        *b_Bu_ENDVERTEX_XERR;   //!
   TBranch        *b_Bu_ENDVERTEX_YERR;   //!
   TBranch        *b_Bu_ENDVERTEX_ZERR;   //!
   TBranch        *b_D0_VTXCHI2DOF;   //!
   TBranch        *b_D0_ENDVTX_Z;   //!
   TBranch        *b_BuL0Global_Dec;   //!
   TBranch        *b_BuL0Global_TIS;   //!
   TBranch        *b_BuL0Global_TOS;   //!
   TBranch        *b_BuHlt1Global_Dec;   //!
   TBranch        *b_BuHlt1Global_TIS;   //!
   TBranch        *b_BuHlt1Global_TOS;   //!
   TBranch        *b_BuHlt2Global_Dec;   //!
   TBranch        *b_BuHlt2Global_TIS;   //!
   TBranch        *b_BuHlt2Global_TOS;   //!
   TBranch        *b_BuL0HadronDecision_Dec;   //!
   TBranch        *b_BuL0HadronDecision_TIS;   //!
   TBranch        *b_BuL0HadronDecision_TOS;   //!
   TBranch        *b_BuL0MuonDecision_Dec;   //!
   TBranch        *b_BuL0MuonDecision_TIS;   //!
   TBranch        *b_BuL0MuonDecision_TOS;   //!
   TBranch        *b_BuL0DiMuonDecision_Dec;   //!
   TBranch        *b_BuL0DiMuonDecision_TIS;   //!
   TBranch        *b_BuL0DiMuonDecision_TOS;   //!
   TBranch        *b_BuL0MuonHighDecision_Dec;   //!
   TBranch        *b_BuL0MuonHighDecision_TIS;   //!
   TBranch        *b_BuL0MuonHighDecision_TOS;   //!
   TBranch        *b_Bach_isMuon;   //!
   TBranch        *b_Bach_hasRich;   //!
   TBranch        *b_K_isMuon;   //!
   TBranch        *b_K_hasRich;   //!
   TBranch        *b_P_isMuon;   //!
   TBranch        *b_P_hasRich;   //!
   TBranch        *b_Bach_TRACK_Eta;   //!
   TBranch        *b_P_TRACK_Eta;   //!
   TBranch        *b_K_TRACK_Eta;   //!
   TBranch        *b_nTracks;   //!
   TBranch        *b_BuHlt1TrackAllL0Decision_Dec;   //!
   TBranch        *b_BuHlt1TrackAllL0Decision_TIS;   //!
   TBranch        *b_BuHlt1TrackAllL0Decision_TOS;   //!
   TBranch        *b_BuHlt1TrackMuonDecision_Dec;   //!
   TBranch        *b_BuHlt1TrackMuonDecision_TIS;   //!
   TBranch        *b_BuHlt1TrackMuonDecision_TOS;   //!
   TBranch        *b_BuHlt1TrackPhotonDecision_Dec;   //!
   TBranch        *b_BuHlt1TrackPhotonDecision_TIS;   //!
   TBranch        *b_BuHlt1TrackPhotonDecision_TOS;   //!
   TBranch        *b_BuHlt1SingleMuonNoIPL0Decision_Dec;   //!
   TBranch        *b_BuHlt1SingleMuonNoIPL0Decision_TIS;   //!
   TBranch        *b_BuHlt1SingleMuonNoIPL0Decision_TOS;   //!
   TBranch        *b_BuHlt2Topo2BodyBBDTDecision_Dec;   //!
   TBranch        *b_BuHlt2Topo2BodyBBDTDecision_TIS;   //!
   TBranch        *b_BuHlt2Topo2BodyBBDTDecision_TOS;   //!
   TBranch        *b_BuHlt2Topo3BodyBBDTDecision_Dec;   //!
   TBranch        *b_BuHlt2Topo3BodyBBDTDecision_TIS;   //!
   TBranch        *b_BuHlt2Topo3BodyBBDTDecision_TOS;   //!
   TBranch        *b_BuHlt2Topo4BodyBBDTDecision_Dec;   //!
   TBranch        *b_BuHlt2Topo4BodyBBDTDecision_TIS;   //!
   TBranch        *b_BuHlt2Topo4BodyBBDTDecision_TOS;   //!
   TBranch        *b_BuHlt2Topo2BodySimpleDecision_Dec;   //!
   TBranch        *b_BuHlt2Topo2BodySimpleDecision_TIS;   //!
   TBranch        *b_BuHlt2Topo2BodySimpleDecision_TOS;   //!
   TBranch        *b_BuHlt2Topo3BodySimpleDecision_Dec;   //!
   TBranch        *b_BuHlt2Topo3BodySimpleDecision_TIS;   //!
   TBranch        *b_BuHlt2Topo3BodySimpleDecision_TOS;   //!
   TBranch        *b_BuHlt2Topo4BodySimpleDecision_Dec;   //!
   TBranch        *b_BuHlt2Topo4BodySimpleDecision_TIS;   //!
   TBranch        *b_BuHlt2Topo4BodySimpleDecision_TOS;   //!
   TBranch        *b_BuHlt2CharmOSTF3BodyDecision_Dec;   //!
   TBranch        *b_BuHlt2CharmOSTF3BodyDecision_TIS;   //!
   TBranch        *b_BuHlt2CharmOSTF3BodyDecision_TOS;   //!
   TBranch        *b_BuHlt2CharmOSTF2BodyDecision_Dec;   //!
   TBranch        *b_BuHlt2CharmOSTF2BodyDecision_TIS;   //!
   TBranch        *b_BuHlt2CharmOSTF2BodyDecision_TOS;   //!
   TBranch        *b_BuHlt2CharmTF3BodySADecision_Dec;   //!
   TBranch        *b_BuHlt2CharmTF3BodySADecision_TIS;   //!
   TBranch        *b_BuHlt2CharmTF3BodySADecision_TOS;   //!
   TBranch        *b_BuHlt2CharmTF2BodySADecision_Dec;   //!
   TBranch        *b_BuHlt2CharmTF2BodySADecision_TIS;   //!
   TBranch        *b_BuHlt2CharmTF2BodySADecision_TOS;   //!
   TBranch        *b_BuHlt2DiMuonUnbiasedJPsiDecision_Dec;   //!
   TBranch        *b_BuHlt2DiMuonUnbiasedJPsiDecision_TIS;   //!
   TBranch        *b_BuHlt2DiMuonUnbiasedJPsiDecision_TOS;   //!
   TBranch        *b_Bach_PIDe;   //!
   TBranch        *b_Bach_PIDmu;   //!
   TBranch        *b_Bach_PIDp;   //!
   TBranch        *b_K_PIDe;   //!
   TBranch        *b_K_PIDmu;   //!
   TBranch        *b_K_PIDp;   //!
   TBranch        *b_P_PIDe;   //!
   TBranch        *b_P_PIDmu;   //!
   TBranch        *b_P_PIDp;   //!
   TBranch        *b_Bach_ProbNNe;   //!
   TBranch        *b_Bach_ProbNNk;   //!
   TBranch        *b_Bach_ProbNNp;   //!
   TBranch        *b_Bach_ProbNNpi;   //!
   TBranch        *b_Bach_ProbNNmu;   //!
   TBranch        *b_Bach_ProbNNghost;   //!
   TBranch        *b_Bach_CaloEcalE;   //!
   TBranch        *b_Bach_CaloHcalE;   //!
   TBranch        *b_Bach_PE;   //!
   TBranch        *b_Bach_PX;   //!
   TBranch        *b_Bach_PY;   //!
   TBranch        *b_Bach_PZ;   //!
   TBranch        *b_K_PE;   //!
   TBranch        *b_K_PX;   //!
   TBranch        *b_K_PY;   //!
   TBranch        *b_K_PZ;   //!
   TBranch        *b_P_PE;   //!
   TBranch        *b_P_PX;   //!
   TBranch        *b_P_PY;   //!
   TBranch        *b_P_PZ;   //!
   TBranch        *b_Bach_ID;   //!
   TBranch        *b_K_ID;   //!
   TBranch        *b_P_ID;   //!
   TBranch        *b_Bu_DPVCFIT_D0P;   //!
   TBranch        *b_Bu_DPVCFIT_BachP;   //!
   TBranch        *b_Bu_DPVCFIT_P;   //!
   TBranch        *b_K_P;   //!
   TBranch        *b_P_P;   //!
   TBranch        *b_Bu_BKGCAT;   //!
   TBranch        *b_D0_BKGCAT;   //!
   TBranch        *b_Bu_TRUEID;   //!
   TBranch        *b_Bu_MC_MOTHER_ID;   //!
   TBranch        *b_Bu_MC_GD_MOTHER_ID;   //!
   TBranch        *b_Bu_MC_GD_GD_MOTHER_ID;   //!
   TBranch        *b_Bu_TRUEP_E;   //!
   TBranch        *b_Bu_TRUEP_X;   //!
   TBranch        *b_Bu_TRUEP_Y;   //!
   TBranch        *b_Bu_TRUEP_Z;   //!
   TBranch        *b_Bu_TRUEPT;   //!
   TBranch        *b_D0_TRUEID;   //!
   TBranch        *b_D0_MC_MOTHER_ID;   //!
   TBranch        *b_D0_MC_GD_MOTHER_ID;   //!
   TBranch        *b_D0_MC_GD_GD_MOTHER_ID;   //!
   TBranch        *b_D0_TRUEP_E;   //!
   TBranch        *b_D0_TRUEP_X;   //!
   TBranch        *b_D0_TRUEP_Y;   //!
   TBranch        *b_D0_TRUEP_Z;   //!
   TBranch        *b_D0_TRUEPT;   //!
   TBranch        *b_Bach_TRUEID;   //!
   TBranch        *b_Bach_MC_MOTHER_ID;   //!
   TBranch        *b_Bach_MC_GD_MOTHER_ID;   //!
   TBranch        *b_Bach_MC_GD_GD_MOTHER_ID;   //!
   TBranch        *b_Bach_TRUEP_E;   //!
   TBranch        *b_Bach_TRUEP_X;   //!
   TBranch        *b_Bach_TRUEP_Y;   //!
   TBranch        *b_Bach_TRUEP_Z;   //!
   TBranch        *b_Bach_TRUEPT;   //!
   TBranch        *b_K_TRUEID;   //!
   TBranch        *b_K_MC_MOTHER_ID;   //!
   TBranch        *b_K_MC_GD_MOTHER_ID;   //!
   TBranch        *b_K_MC_GD_GD_MOTHER_ID;   //!
   TBranch        *b_K_TRUEP_E;   //!
   TBranch        *b_K_TRUEP_X;   //!
   TBranch        *b_K_TRUEP_Y;   //!
   TBranch        *b_K_TRUEP_Z;   //!
   TBranch        *b_K_TRUEPT;   //!
   TBranch        *b_P_TRUEID;   //!
   TBranch        *b_P_MC_MOTHER_ID;   //!
   TBranch        *b_P_MC_GD_MOTHER_ID;   //!
   TBranch        *b_P_MC_GD_GD_MOTHER_ID;   //!
   TBranch        *b_P_TRUEP_E;   //!
   TBranch        *b_P_TRUEP_X;   //!
   TBranch        *b_P_TRUEP_Y;   //!
   TBranch        *b_P_TRUEP_Z;   //!
   TBranch        *b_P_TRUEPT;   //!
   TBranch        *b_trueM;   //!
   TBranch        *b_trueM_misID;   //!
   TBranch        *b_trueD0M;   //!
   TBranch        *b_BDT;   //!

   pippo(TTree * /*tree*/ =0) { }
   virtual ~pippo() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(pippo,0);
};

#endif

#ifdef pippo_cxx
void pippo::Init(TTree *tree)
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
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("nPV", &nPV, &b_nPV);
   fChain->SetBranchAddress("Bu_M", &Bu_M, &b_Bu_M);
   fChain->SetBranchAddress("D0_M", &D0_M, &b_D0_M);
   fChain->SetBranchAddress("Bu_DPVCFIT_M", &Bu_DPVCFIT_M, &b_Bu_DPVCFIT_M);
   fChain->SetBranchAddress("Bu_DPVCFIT_CHI2NDOF", &Bu_DPVCFIT_CHI2NDOF, &b_Bu_DPVCFIT_CHI2NDOF);
   fChain->SetBranchAddress("Bu_DPVCFIT_D0M", &Bu_DPVCFIT_D0M, &b_Bu_DPVCFIT_D0M);
   fChain->SetBranchAddress("D0_FD_ZSIG", &D0_FD_ZSIG, &b_D0_FD_ZSIG);
   fChain->SetBranchAddress("D0_M_DOUBLESW", &D0_M_DOUBLESW, &b_D0_M_DOUBLESW);
   fChain->SetBranchAddress("Bu_M_DOUBLESW", &Bu_M_DOUBLESW, &b_Bu_M_DOUBLESW);
   fChain->SetBranchAddress("Bu_M_DOUBLESW_Khyp", &Bu_M_DOUBLESW_Khyp, &b_Bu_M_DOUBLESW_Khyp);
   fChain->SetBranchAddress("Bu_M_DOUBLESW_Pihyp", &Bu_M_DOUBLESW_Pihyp, &b_Bu_M_DOUBLESW_Pihyp);
   fChain->SetBranchAddress("OdinTCK", &OdinTCK, &b_OdinTCK);
   fChain->SetBranchAddress("HLTTCK", &HLTTCK, &b_HLTTCK);
   fChain->SetBranchAddress("L0DUTCK", &L0DUTCK, &b_L0DUTCK);
   fChain->SetBranchAddress("jpsi_veto", &jpsi_veto, &b_jpsi_veto);
   fChain->SetBranchAddress("jpsi_veto_raw", &jpsi_veto_raw, &b_jpsi_veto_raw);
   fChain->SetBranchAddress("first_isMuon", &first_isMuon, &b_first_isMuon);
   fChain->SetBranchAddress("second_isMuon", &second_isMuon, &b_second_isMuon);
   fChain->SetBranchAddress("Bu_P", &Bu_P, &b_Bu_P);
   fChain->SetBranchAddress("Bu_PT", &Bu_PT, &b_Bu_PT);
   fChain->SetBranchAddress("D0_P", &D0_P, &b_D0_P);
   fChain->SetBranchAddress("D0_PT", &D0_PT, &b_D0_PT);
   fChain->SetBranchAddress("Bach_P", &Bach_P, &b_Bach_P);
   fChain->SetBranchAddress("Bach_PT", &Bach_PT, &b_Bach_PT);
   fChain->SetBranchAddress("Bu_ID", &Bu_ID, &b_Bu_ID);
   fChain->SetBranchAddress("Bu_Q", &Bu_Q, &b_Bu_Q);
   fChain->SetBranchAddress("Bu_FD_BPV_SIGNED", &Bu_FD_BPV_SIGNED, &b_Bu_FD_BPV_SIGNED);
   fChain->SetBranchAddress("Bu_LV01", &Bu_LV01, &b_Bu_LV01);
   fChain->SetBranchAddress("Bu_LV02", &Bu_LV02, &b_Bu_LV02);
   fChain->SetBranchAddress("Bach_PIDK", &Bach_PIDK, &b_Bach_PIDK);
   fChain->SetBranchAddress("K_PIDK", &K_PIDK, &b_K_PIDK);
   fChain->SetBranchAddress("P_PIDK", &P_PIDK, &b_P_PIDK);
   fChain->SetBranchAddress("Bu_VTXCHI2DOF", &Bu_VTXCHI2DOF, &b_Bu_VTXCHI2DOF);
   fChain->SetBranchAddress("Bu_ENDVTX_X", &Bu_ENDVTX_X, &b_Bu_ENDVTX_X);
   fChain->SetBranchAddress("Bu_ENDVTX_Y", &Bu_ENDVTX_Y, &b_Bu_ENDVTX_Y);
   fChain->SetBranchAddress("Bu_ENDVTX_Z", &Bu_ENDVTX_Z, &b_Bu_ENDVTX_Z);
   fChain->SetBranchAddress("Bu_ENDVERTEX_X", &Bu_ENDVERTEX_X, &b_Bu_ENDVERTEX_X);
   fChain->SetBranchAddress("Bu_ENDVERTEX_Y", &Bu_ENDVERTEX_Y, &b_Bu_ENDVERTEX_Y);
   fChain->SetBranchAddress("Bu_ENDVERTEX_Z", &Bu_ENDVERTEX_Z, &b_Bu_ENDVERTEX_Z);
   fChain->SetBranchAddress("Bu_ENDVERTEX_XERR", &Bu_ENDVERTEX_XERR, &b_Bu_ENDVERTEX_XERR);
   fChain->SetBranchAddress("Bu_ENDVERTEX_YERR", &Bu_ENDVERTEX_YERR, &b_Bu_ENDVERTEX_YERR);
   fChain->SetBranchAddress("Bu_ENDVERTEX_ZERR", &Bu_ENDVERTEX_ZERR, &b_Bu_ENDVERTEX_ZERR);
   fChain->SetBranchAddress("D0_VTXCHI2DOF", &D0_VTXCHI2DOF, &b_D0_VTXCHI2DOF);
   fChain->SetBranchAddress("D0_ENDVTX_Z", &D0_ENDVTX_Z, &b_D0_ENDVTX_Z);
   fChain->SetBranchAddress("BuL0Global_Dec", &BuL0Global_Dec, &b_BuL0Global_Dec);
   fChain->SetBranchAddress("BuL0Global_TIS", &BuL0Global_TIS, &b_BuL0Global_TIS);
   fChain->SetBranchAddress("BuL0Global_TOS", &BuL0Global_TOS, &b_BuL0Global_TOS);
   fChain->SetBranchAddress("BuHlt1Global_Dec", &BuHlt1Global_Dec, &b_BuHlt1Global_Dec);
   fChain->SetBranchAddress("BuHlt1Global_TIS", &BuHlt1Global_TIS, &b_BuHlt1Global_TIS);
   fChain->SetBranchAddress("BuHlt1Global_TOS", &BuHlt1Global_TOS, &b_BuHlt1Global_TOS);
   fChain->SetBranchAddress("BuHlt2Global_Dec", &BuHlt2Global_Dec, &b_BuHlt2Global_Dec);
   fChain->SetBranchAddress("BuHlt2Global_TIS", &BuHlt2Global_TIS, &b_BuHlt2Global_TIS);
   fChain->SetBranchAddress("BuHlt2Global_TOS", &BuHlt2Global_TOS, &b_BuHlt2Global_TOS);
   fChain->SetBranchAddress("BuL0HadronDecision_Dec", &BuL0HadronDecision_Dec, &b_BuL0HadronDecision_Dec);
   fChain->SetBranchAddress("BuL0HadronDecision_TIS", &BuL0HadronDecision_TIS, &b_BuL0HadronDecision_TIS);
   fChain->SetBranchAddress("BuL0HadronDecision_TOS", &BuL0HadronDecision_TOS, &b_BuL0HadronDecision_TOS);
   fChain->SetBranchAddress("BuL0MuonDecision_Dec", &BuL0MuonDecision_Dec, &b_BuL0MuonDecision_Dec);
   fChain->SetBranchAddress("BuL0MuonDecision_TIS", &BuL0MuonDecision_TIS, &b_BuL0MuonDecision_TIS);
   fChain->SetBranchAddress("BuL0MuonDecision_TOS", &BuL0MuonDecision_TOS, &b_BuL0MuonDecision_TOS);
   fChain->SetBranchAddress("BuL0DiMuonDecision_Dec", &BuL0DiMuonDecision_Dec, &b_BuL0DiMuonDecision_Dec);
   fChain->SetBranchAddress("BuL0DiMuonDecision_TIS", &BuL0DiMuonDecision_TIS, &b_BuL0DiMuonDecision_TIS);
   fChain->SetBranchAddress("BuL0DiMuonDecision_TOS", &BuL0DiMuonDecision_TOS, &b_BuL0DiMuonDecision_TOS);
   fChain->SetBranchAddress("BuL0MuonHighDecision_Dec", &BuL0MuonHighDecision_Dec, &b_BuL0MuonHighDecision_Dec);
   fChain->SetBranchAddress("BuL0MuonHighDecision_TIS", &BuL0MuonHighDecision_TIS, &b_BuL0MuonHighDecision_TIS);
   fChain->SetBranchAddress("BuL0MuonHighDecision_TOS", &BuL0MuonHighDecision_TOS, &b_BuL0MuonHighDecision_TOS);
   fChain->SetBranchAddress("Bach_isMuon", &Bach_isMuon, &b_Bach_isMuon);
   fChain->SetBranchAddress("Bach_hasRich", &Bach_hasRich, &b_Bach_hasRich);
   fChain->SetBranchAddress("K_isMuon", &K_isMuon, &b_K_isMuon);
   fChain->SetBranchAddress("K_hasRich", &K_hasRich, &b_K_hasRich);
   fChain->SetBranchAddress("P_isMuon", &P_isMuon, &b_P_isMuon);
   fChain->SetBranchAddress("P_hasRich", &P_hasRich, &b_P_hasRich);
   fChain->SetBranchAddress("Bach_TRACK_Eta", &Bach_TRACK_Eta, &b_Bach_TRACK_Eta);
   fChain->SetBranchAddress("P_TRACK_Eta", &P_TRACK_Eta, &b_P_TRACK_Eta);
   fChain->SetBranchAddress("K_TRACK_Eta", &K_TRACK_Eta, &b_K_TRACK_Eta);
   fChain->SetBranchAddress("nTracks", &nTracks, &b_nTracks);
   fChain->SetBranchAddress("BuHlt1TrackAllL0Decision_Dec", &BuHlt1TrackAllL0Decision_Dec, &b_BuHlt1TrackAllL0Decision_Dec);
   fChain->SetBranchAddress("BuHlt1TrackAllL0Decision_TIS", &BuHlt1TrackAllL0Decision_TIS, &b_BuHlt1TrackAllL0Decision_TIS);
   fChain->SetBranchAddress("BuHlt1TrackAllL0Decision_TOS", &BuHlt1TrackAllL0Decision_TOS, &b_BuHlt1TrackAllL0Decision_TOS);
   fChain->SetBranchAddress("BuHlt1TrackMuonDecision_Dec", &BuHlt1TrackMuonDecision_Dec, &b_BuHlt1TrackMuonDecision_Dec);
   fChain->SetBranchAddress("BuHlt1TrackMuonDecision_TIS", &BuHlt1TrackMuonDecision_TIS, &b_BuHlt1TrackMuonDecision_TIS);
   fChain->SetBranchAddress("BuHlt1TrackMuonDecision_TOS", &BuHlt1TrackMuonDecision_TOS, &b_BuHlt1TrackMuonDecision_TOS);
   fChain->SetBranchAddress("BuHlt1TrackPhotonDecision_Dec", &BuHlt1TrackPhotonDecision_Dec, &b_BuHlt1TrackPhotonDecision_Dec);
   fChain->SetBranchAddress("BuHlt1TrackPhotonDecision_TIS", &BuHlt1TrackPhotonDecision_TIS, &b_BuHlt1TrackPhotonDecision_TIS);
   fChain->SetBranchAddress("BuHlt1TrackPhotonDecision_TOS", &BuHlt1TrackPhotonDecision_TOS, &b_BuHlt1TrackPhotonDecision_TOS);
   fChain->SetBranchAddress("BuHlt1SingleMuonNoIPL0Decision_Dec", &BuHlt1SingleMuonNoIPL0Decision_Dec, &b_BuHlt1SingleMuonNoIPL0Decision_Dec);
   fChain->SetBranchAddress("BuHlt1SingleMuonNoIPL0Decision_TIS", &BuHlt1SingleMuonNoIPL0Decision_TIS, &b_BuHlt1SingleMuonNoIPL0Decision_TIS);
   fChain->SetBranchAddress("BuHlt1SingleMuonNoIPL0Decision_TOS", &BuHlt1SingleMuonNoIPL0Decision_TOS, &b_BuHlt1SingleMuonNoIPL0Decision_TOS);
   fChain->SetBranchAddress("BuHlt2Topo2BodyBBDTDecision_Dec", &BuHlt2Topo2BodyBBDTDecision_Dec, &b_BuHlt2Topo2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("BuHlt2Topo2BodyBBDTDecision_TIS", &BuHlt2Topo2BodyBBDTDecision_TIS, &b_BuHlt2Topo2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("BuHlt2Topo2BodyBBDTDecision_TOS", &BuHlt2Topo2BodyBBDTDecision_TOS, &b_BuHlt2Topo2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("BuHlt2Topo3BodyBBDTDecision_Dec", &BuHlt2Topo3BodyBBDTDecision_Dec, &b_BuHlt2Topo3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("BuHlt2Topo3BodyBBDTDecision_TIS", &BuHlt2Topo3BodyBBDTDecision_TIS, &b_BuHlt2Topo3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("BuHlt2Topo3BodyBBDTDecision_TOS", &BuHlt2Topo3BodyBBDTDecision_TOS, &b_BuHlt2Topo3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("BuHlt2Topo4BodyBBDTDecision_Dec", &BuHlt2Topo4BodyBBDTDecision_Dec, &b_BuHlt2Topo4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("BuHlt2Topo4BodyBBDTDecision_TIS", &BuHlt2Topo4BodyBBDTDecision_TIS, &b_BuHlt2Topo4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("BuHlt2Topo4BodyBBDTDecision_TOS", &BuHlt2Topo4BodyBBDTDecision_TOS, &b_BuHlt2Topo4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("BuHlt2Topo2BodySimpleDecision_Dec", &BuHlt2Topo2BodySimpleDecision_Dec, &b_BuHlt2Topo2BodySimpleDecision_Dec);
   fChain->SetBranchAddress("BuHlt2Topo2BodySimpleDecision_TIS", &BuHlt2Topo2BodySimpleDecision_TIS, &b_BuHlt2Topo2BodySimpleDecision_TIS);
   fChain->SetBranchAddress("BuHlt2Topo2BodySimpleDecision_TOS", &BuHlt2Topo2BodySimpleDecision_TOS, &b_BuHlt2Topo2BodySimpleDecision_TOS);
   fChain->SetBranchAddress("BuHlt2Topo3BodySimpleDecision_Dec", &BuHlt2Topo3BodySimpleDecision_Dec, &b_BuHlt2Topo3BodySimpleDecision_Dec);
   fChain->SetBranchAddress("BuHlt2Topo3BodySimpleDecision_TIS", &BuHlt2Topo3BodySimpleDecision_TIS, &b_BuHlt2Topo3BodySimpleDecision_TIS);
   fChain->SetBranchAddress("BuHlt2Topo3BodySimpleDecision_TOS", &BuHlt2Topo3BodySimpleDecision_TOS, &b_BuHlt2Topo3BodySimpleDecision_TOS);
   fChain->SetBranchAddress("BuHlt2Topo4BodySimpleDecision_Dec", &BuHlt2Topo4BodySimpleDecision_Dec, &b_BuHlt2Topo4BodySimpleDecision_Dec);
   fChain->SetBranchAddress("BuHlt2Topo4BodySimpleDecision_TIS", &BuHlt2Topo4BodySimpleDecision_TIS, &b_BuHlt2Topo4BodySimpleDecision_TIS);
   fChain->SetBranchAddress("BuHlt2Topo4BodySimpleDecision_TOS", &BuHlt2Topo4BodySimpleDecision_TOS, &b_BuHlt2Topo4BodySimpleDecision_TOS);
   fChain->SetBranchAddress("BuHlt2CharmOSTF3BodyDecision_Dec", &BuHlt2CharmOSTF3BodyDecision_Dec, &b_BuHlt2CharmOSTF3BodyDecision_Dec);
   fChain->SetBranchAddress("BuHlt2CharmOSTF3BodyDecision_TIS", &BuHlt2CharmOSTF3BodyDecision_TIS, &b_BuHlt2CharmOSTF3BodyDecision_TIS);
   fChain->SetBranchAddress("BuHlt2CharmOSTF3BodyDecision_TOS", &BuHlt2CharmOSTF3BodyDecision_TOS, &b_BuHlt2CharmOSTF3BodyDecision_TOS);
   fChain->SetBranchAddress("BuHlt2CharmOSTF2BodyDecision_Dec", &BuHlt2CharmOSTF2BodyDecision_Dec, &b_BuHlt2CharmOSTF2BodyDecision_Dec);
   fChain->SetBranchAddress("BuHlt2CharmOSTF2BodyDecision_TIS", &BuHlt2CharmOSTF2BodyDecision_TIS, &b_BuHlt2CharmOSTF2BodyDecision_TIS);
   fChain->SetBranchAddress("BuHlt2CharmOSTF2BodyDecision_TOS", &BuHlt2CharmOSTF2BodyDecision_TOS, &b_BuHlt2CharmOSTF2BodyDecision_TOS);
   fChain->SetBranchAddress("BuHlt2CharmTF3BodySADecision_Dec", &BuHlt2CharmTF3BodySADecision_Dec, &b_BuHlt2CharmTF3BodySADecision_Dec);
   fChain->SetBranchAddress("BuHlt2CharmTF3BodySADecision_TIS", &BuHlt2CharmTF3BodySADecision_TIS, &b_BuHlt2CharmTF3BodySADecision_TIS);
   fChain->SetBranchAddress("BuHlt2CharmTF3BodySADecision_TOS", &BuHlt2CharmTF3BodySADecision_TOS, &b_BuHlt2CharmTF3BodySADecision_TOS);
   fChain->SetBranchAddress("BuHlt2CharmTF2BodySADecision_Dec", &BuHlt2CharmTF2BodySADecision_Dec, &b_BuHlt2CharmTF2BodySADecision_Dec);
   fChain->SetBranchAddress("BuHlt2CharmTF2BodySADecision_TIS", &BuHlt2CharmTF2BodySADecision_TIS, &b_BuHlt2CharmTF2BodySADecision_TIS);
   fChain->SetBranchAddress("BuHlt2CharmTF2BodySADecision_TOS", &BuHlt2CharmTF2BodySADecision_TOS, &b_BuHlt2CharmTF2BodySADecision_TOS);
   fChain->SetBranchAddress("BuHlt2DiMuonUnbiasedJPsiDecision_Dec", &BuHlt2DiMuonUnbiasedJPsiDecision_Dec, &b_BuHlt2DiMuonUnbiasedJPsiDecision_Dec);
   fChain->SetBranchAddress("BuHlt2DiMuonUnbiasedJPsiDecision_TIS", &BuHlt2DiMuonUnbiasedJPsiDecision_TIS, &b_BuHlt2DiMuonUnbiasedJPsiDecision_TIS);
   fChain->SetBranchAddress("BuHlt2DiMuonUnbiasedJPsiDecision_TOS", &BuHlt2DiMuonUnbiasedJPsiDecision_TOS, &b_BuHlt2DiMuonUnbiasedJPsiDecision_TOS);
   fChain->SetBranchAddress("Bach_PIDe", &Bach_PIDe, &b_Bach_PIDe);
   fChain->SetBranchAddress("Bach_PIDmu", &Bach_PIDmu, &b_Bach_PIDmu);
   fChain->SetBranchAddress("Bach_PIDp", &Bach_PIDp, &b_Bach_PIDp);
   fChain->SetBranchAddress("K_PIDe", &K_PIDe, &b_K_PIDe);
   fChain->SetBranchAddress("K_PIDmu", &K_PIDmu, &b_K_PIDmu);
   fChain->SetBranchAddress("K_PIDp", &K_PIDp, &b_K_PIDp);
   fChain->SetBranchAddress("P_PIDe", &P_PIDe, &b_P_PIDe);
   fChain->SetBranchAddress("P_PIDmu", &P_PIDmu, &b_P_PIDmu);
   fChain->SetBranchAddress("P_PIDp", &P_PIDp, &b_P_PIDp);
   fChain->SetBranchAddress("Bach_ProbNNe", &Bach_ProbNNe, &b_Bach_ProbNNe);
   fChain->SetBranchAddress("Bach_ProbNNk", &Bach_ProbNNk, &b_Bach_ProbNNk);
   fChain->SetBranchAddress("Bach_ProbNNp", &Bach_ProbNNp, &b_Bach_ProbNNp);
   fChain->SetBranchAddress("Bach_ProbNNpi", &Bach_ProbNNpi, &b_Bach_ProbNNpi);
   fChain->SetBranchAddress("Bach_ProbNNmu", &Bach_ProbNNmu, &b_Bach_ProbNNmu);
   fChain->SetBranchAddress("Bach_ProbNNghost", &Bach_ProbNNghost, &b_Bach_ProbNNghost);
   fChain->SetBranchAddress("Bach_CaloEcalE", &Bach_CaloEcalE, &b_Bach_CaloEcalE);
   fChain->SetBranchAddress("Bach_CaloHcalE", &Bach_CaloHcalE, &b_Bach_CaloHcalE);
   fChain->SetBranchAddress("Bach_PE", &Bach_PE, &b_Bach_PE);
   fChain->SetBranchAddress("Bach_PX", &Bach_PX, &b_Bach_PX);
   fChain->SetBranchAddress("Bach_PY", &Bach_PY, &b_Bach_PY);
   fChain->SetBranchAddress("Bach_PZ", &Bach_PZ, &b_Bach_PZ);
   fChain->SetBranchAddress("K_PE", &K_PE, &b_K_PE);
   fChain->SetBranchAddress("K_PX", &K_PX, &b_K_PX);
   fChain->SetBranchAddress("K_PY", &K_PY, &b_K_PY);
   fChain->SetBranchAddress("K_PZ", &K_PZ, &b_K_PZ);
   fChain->SetBranchAddress("P_PE", &P_PE, &b_P_PE);
   fChain->SetBranchAddress("P_PX", &P_PX, &b_P_PX);
   fChain->SetBranchAddress("P_PY", &P_PY, &b_P_PY);
   fChain->SetBranchAddress("P_PZ", &P_PZ, &b_P_PZ);
   fChain->SetBranchAddress("Bach_ID", &Bach_ID, &b_Bach_ID);
   fChain->SetBranchAddress("K_ID", &K_ID, &b_K_ID);
   fChain->SetBranchAddress("P_ID", &P_ID, &b_P_ID);
   fChain->SetBranchAddress("Bu_DPVCFIT_D0P", &Bu_DPVCFIT_D0P, &b_Bu_DPVCFIT_D0P);
   fChain->SetBranchAddress("Bu_DPVCFIT_BachP", &Bu_DPVCFIT_BachP, &b_Bu_DPVCFIT_BachP);
   fChain->SetBranchAddress("Bu_DPVCFIT_P", &Bu_DPVCFIT_P, &b_Bu_DPVCFIT_P);
   fChain->SetBranchAddress("K_P", &K_P, &b_K_P);
   fChain->SetBranchAddress("P_P", &P_P, &b_P_P);
   fChain->SetBranchAddress("Bu_BKGCAT", &Bu_BKGCAT, &b_Bu_BKGCAT);
   fChain->SetBranchAddress("D0_BKGCAT", &D0_BKGCAT, &b_D0_BKGCAT);
   fChain->SetBranchAddress("Bu_TRUEID", &Bu_TRUEID, &b_Bu_TRUEID);
   fChain->SetBranchAddress("Bu_MC_MOTHER_ID", &Bu_MC_MOTHER_ID, &b_Bu_MC_MOTHER_ID);
   fChain->SetBranchAddress("Bu_MC_GD_MOTHER_ID", &Bu_MC_GD_MOTHER_ID, &b_Bu_MC_GD_MOTHER_ID);
   fChain->SetBranchAddress("Bu_MC_GD_GD_MOTHER_ID", &Bu_MC_GD_GD_MOTHER_ID, &b_Bu_MC_GD_GD_MOTHER_ID);
   fChain->SetBranchAddress("Bu_TRUEP_E", &Bu_TRUEP_E, &b_Bu_TRUEP_E);
   fChain->SetBranchAddress("Bu_TRUEP_X", &Bu_TRUEP_X, &b_Bu_TRUEP_X);
   fChain->SetBranchAddress("Bu_TRUEP_Y", &Bu_TRUEP_Y, &b_Bu_TRUEP_Y);
   fChain->SetBranchAddress("Bu_TRUEP_Z", &Bu_TRUEP_Z, &b_Bu_TRUEP_Z);
   fChain->SetBranchAddress("Bu_TRUEPT", &Bu_TRUEPT, &b_Bu_TRUEPT);
   fChain->SetBranchAddress("D0_TRUEID", &D0_TRUEID, &b_D0_TRUEID);
   fChain->SetBranchAddress("D0_MC_MOTHER_ID", &D0_MC_MOTHER_ID, &b_D0_MC_MOTHER_ID);
   fChain->SetBranchAddress("D0_MC_GD_MOTHER_ID", &D0_MC_GD_MOTHER_ID, &b_D0_MC_GD_MOTHER_ID);
   fChain->SetBranchAddress("D0_MC_GD_GD_MOTHER_ID", &D0_MC_GD_GD_MOTHER_ID, &b_D0_MC_GD_GD_MOTHER_ID);
   fChain->SetBranchAddress("D0_TRUEP_E", &D0_TRUEP_E, &b_D0_TRUEP_E);
   fChain->SetBranchAddress("D0_TRUEP_X", &D0_TRUEP_X, &b_D0_TRUEP_X);
   fChain->SetBranchAddress("D0_TRUEP_Y", &D0_TRUEP_Y, &b_D0_TRUEP_Y);
   fChain->SetBranchAddress("D0_TRUEP_Z", &D0_TRUEP_Z, &b_D0_TRUEP_Z);
   fChain->SetBranchAddress("D0_TRUEPT", &D0_TRUEPT, &b_D0_TRUEPT);
   fChain->SetBranchAddress("Bach_TRUEID", &Bach_TRUEID, &b_Bach_TRUEID);
   fChain->SetBranchAddress("Bach_MC_MOTHER_ID", &Bach_MC_MOTHER_ID, &b_Bach_MC_MOTHER_ID);
   fChain->SetBranchAddress("Bach_MC_GD_MOTHER_ID", &Bach_MC_GD_MOTHER_ID, &b_Bach_MC_GD_MOTHER_ID);
   fChain->SetBranchAddress("Bach_MC_GD_GD_MOTHER_ID", &Bach_MC_GD_GD_MOTHER_ID, &b_Bach_MC_GD_GD_MOTHER_ID);
   fChain->SetBranchAddress("Bach_TRUEP_E", &Bach_TRUEP_E, &b_Bach_TRUEP_E);
   fChain->SetBranchAddress("Bach_TRUEP_X", &Bach_TRUEP_X, &b_Bach_TRUEP_X);
   fChain->SetBranchAddress("Bach_TRUEP_Y", &Bach_TRUEP_Y, &b_Bach_TRUEP_Y);
   fChain->SetBranchAddress("Bach_TRUEP_Z", &Bach_TRUEP_Z, &b_Bach_TRUEP_Z);
   fChain->SetBranchAddress("Bach_TRUEPT", &Bach_TRUEPT, &b_Bach_TRUEPT);
   fChain->SetBranchAddress("K_TRUEID", &K_TRUEID, &b_K_TRUEID);
   fChain->SetBranchAddress("K_MC_MOTHER_ID", &K_MC_MOTHER_ID, &b_K_MC_MOTHER_ID);
   fChain->SetBranchAddress("K_MC_GD_MOTHER_ID", &K_MC_GD_MOTHER_ID, &b_K_MC_GD_MOTHER_ID);
   fChain->SetBranchAddress("K_MC_GD_GD_MOTHER_ID", &K_MC_GD_GD_MOTHER_ID, &b_K_MC_GD_GD_MOTHER_ID);
   fChain->SetBranchAddress("K_TRUEP_E", &K_TRUEP_E, &b_K_TRUEP_E);
   fChain->SetBranchAddress("K_TRUEP_X", &K_TRUEP_X, &b_K_TRUEP_X);
   fChain->SetBranchAddress("K_TRUEP_Y", &K_TRUEP_Y, &b_K_TRUEP_Y);
   fChain->SetBranchAddress("K_TRUEP_Z", &K_TRUEP_Z, &b_K_TRUEP_Z);
   fChain->SetBranchAddress("K_TRUEPT", &K_TRUEPT, &b_K_TRUEPT);
   fChain->SetBranchAddress("P_TRUEID", &P_TRUEID, &b_P_TRUEID);
   fChain->SetBranchAddress("P_MC_MOTHER_ID", &P_MC_MOTHER_ID, &b_P_MC_MOTHER_ID);
   fChain->SetBranchAddress("P_MC_GD_MOTHER_ID", &P_MC_GD_MOTHER_ID, &b_P_MC_GD_MOTHER_ID);
   fChain->SetBranchAddress("P_MC_GD_GD_MOTHER_ID", &P_MC_GD_GD_MOTHER_ID, &b_P_MC_GD_GD_MOTHER_ID);
   fChain->SetBranchAddress("P_TRUEP_E", &P_TRUEP_E, &b_P_TRUEP_E);
   fChain->SetBranchAddress("P_TRUEP_X", &P_TRUEP_X, &b_P_TRUEP_X);
   fChain->SetBranchAddress("P_TRUEP_Y", &P_TRUEP_Y, &b_P_TRUEP_Y);
   fChain->SetBranchAddress("P_TRUEP_Z", &P_TRUEP_Z, &b_P_TRUEP_Z);
   fChain->SetBranchAddress("P_TRUEPT", &P_TRUEPT, &b_P_TRUEPT);
   fChain->SetBranchAddress("trueM", &trueM, &b_trueM);
   fChain->SetBranchAddress("trueM_misID", &trueM_misID, &b_trueM_misID);
   fChain->SetBranchAddress("trueD0M", &trueD0M, &b_trueD0M);
   fChain->SetBranchAddress("BDT", &BDT, &b_BDT);
}

Bool_t pippo::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef pippo_cxx
