//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jan  7 16:48:56 2016 by ROOT version 6.04/02
// from TTree DecayTree/DecayTree
// found on file: RDS_MCSignal_Sim08hUp.root
//////////////////////////////////////////////////////////

#ifndef NeutralIsoData_h
#define NeutralIsoData_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class NeutralIsoData {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxBs_0_ENDVERTEX_COV = 1;
   const Int_t kMaxBs_0_OWNPV_COV = 1;
   const Int_t kMaxBs_0_TOPPV_COV = 1;
   const Int_t kMaxBs_0_SV_COV = 1;
   const Int_t kMaxBs_0_PV_COV = 1;
   const Int_t kMaxBs_0_MOM_COV = 1;
   const Int_t kMaxBs_0_POSMOM_COV = 1;
   const Int_t kMaxDs_ENDVERTEX_COV = 1;
   const Int_t kMaxDs_OWNPV_COV = 1;
   const Int_t kMaxDs_TOPPV_COV = 1;
   const Int_t kMaxDs_ORIVX_COV = 1;
   const Int_t kMaxKmi_OWNPV_COV = 1;
   const Int_t kMaxKmi_TOPPV_COV = 1;
   const Int_t kMaxKmi_ORIVX_COV = 1;
   const Int_t kMaxKmi_SV_COV = 1;
   const Int_t kMaxKmi_PV_COV = 1;
   const Int_t kMaxKmi_MOM_COV = 1;
   const Int_t kMaxKmi_POSMOM_COV = 1;
   const Int_t kMaxKpl_OWNPV_COV = 1;
   const Int_t kMaxKpl_TOPPV_COV = 1;
   const Int_t kMaxKpl_ORIVX_COV = 1;
   const Int_t kMaxKpl_SV_COV = 1;
   const Int_t kMaxKpl_PV_COV = 1;
   const Int_t kMaxKpl_MOM_COV = 1;
   const Int_t kMaxKpl_POSMOM_COV = 1;
   const Int_t kMaxpi_OWNPV_COV = 1;
   const Int_t kMaxpi_TOPPV_COV = 1;
   const Int_t kMaxpi_ORIVX_COV = 1;
   const Int_t kMaxpi_SV_COV = 1;
   const Int_t kMaxpi_PV_COV = 1;
   const Int_t kMaxpi_MOM_COV = 1;
   const Int_t kMaxpi_POSMOM_COV = 1;
   const Int_t kMaxmu_OWNPV_COV = 1;
   const Int_t kMaxmu_TOPPV_COV = 1;
   const Int_t kMaxmu_ORIVX_COV = 1;
   const Int_t kMaxmu_SV_COV = 1;
   const Int_t kMaxmu_PV_COV = 1;
   const Int_t kMaxmu_MOM_COV = 1;
   const Int_t kMaxmu_POSMOM_COV = 1;

   // Declaration of leaf types
   Double_t        Bs_0_MINIP;
   Double_t        Bs_0_MINIPCHI2;
   Double_t        Bs_0_MINIPNEXTBEST;
   Double_t        Bs_0_MINIPCHI2NEXTBEST;
   Double_t        Bs_0_ENDVERTEX_X;
   Double_t        Bs_0_ENDVERTEX_Y;
   Double_t        Bs_0_ENDVERTEX_Z;
   Double_t        Bs_0_ENDVERTEX_XERR;
   Double_t        Bs_0_ENDVERTEX_YERR;
   Double_t        Bs_0_ENDVERTEX_ZERR;
   Double_t        Bs_0_ENDVERTEX_CHI2;
   Int_t           Bs_0_ENDVERTEX_NDOF;
   Float_t         Bs_0_ENDVERTEX_COV_[3][3];
   Double_t        Bs_0_OWNPV_X;
   Double_t        Bs_0_OWNPV_Y;
   Double_t        Bs_0_OWNPV_Z;
   Double_t        Bs_0_OWNPV_XERR;
   Double_t        Bs_0_OWNPV_YERR;
   Double_t        Bs_0_OWNPV_ZERR;
   Double_t        Bs_0_OWNPV_CHI2;
   Int_t           Bs_0_OWNPV_NDOF;
   Float_t         Bs_0_OWNPV_COV_[3][3];
   Double_t        Bs_0_IP_OWNPV;
   Double_t        Bs_0_IPCHI2_OWNPV;
   Double_t        Bs_0_FD_OWNPV;
   Double_t        Bs_0_FDCHI2_OWNPV;
   Double_t        Bs_0_DIRA_OWNPV;
   Double_t        Bs_0_TOPPV_X;
   Double_t        Bs_0_TOPPV_Y;
   Double_t        Bs_0_TOPPV_Z;
   Double_t        Bs_0_TOPPV_XERR;
   Double_t        Bs_0_TOPPV_YERR;
   Double_t        Bs_0_TOPPV_ZERR;
   Double_t        Bs_0_TOPPV_CHI2;
   Int_t           Bs_0_TOPPV_NDOF;
   Float_t         Bs_0_TOPPV_COV_[3][3];
   Double_t        Bs_0_IP_TOPPV;
   Double_t        Bs_0_IPCHI2_TOPPV;
   Double_t        Bs_0_FD_TOPPV;
   Double_t        Bs_0_FDCHI2_TOPPV;
   Double_t        Bs_0_DIRA_TOPPV;
   Double_t        Bs_0_P;
   Double_t        Bs_0_PT;
   Double_t        Bs_0_PE;
   Double_t        Bs_0_PX;
   Double_t        Bs_0_PY;
   Double_t        Bs_0_PZ;
   Double_t        Bs_0_MM;
   Double_t        Bs_0_MMERR;
   Double_t        Bs_0_M;
   Int_t           Bs_0_ID;
   Double_t        Bs_0_eta;
   Double_t        Bs_0_phi;
   Float_t         Bs_0_BDTS_BIPS;
   Float_t         Bs_0_BDTS_DOCA;
   Float_t         Bs_0_BDTS_VTXCHI2;
   Float_t         Bs_0_BDTS_DIRA;
   Float_t         Bs_0_BDTS_BIP;
   Float_t         Bs_0_BDTS_MuonMINIP;
   Double_t        Bs_0_BDTS;
   Double_t        Bs_0_CTAU_ps;
   Double_t        Bs_0_TAU;
   Double_t        Bs_0_TAUERR;
   Double_t        Bs_0_TAUCHI2;
   Double_t        Bs_0_SV_X;
   Double_t        Bs_0_SV_Y;
   Double_t        Bs_0_SV_Z;
   Double_t        Bs_0_SV_CHI2;
   Int_t           Bs_0_SV_NDOF;
   Float_t         Bs_0_SV_COV_[3][3];
   Double_t        Bs_0_PV_X;
   Double_t        Bs_0_PV_Y;
   Double_t        Bs_0_PV_Z;
   Double_t        Bs_0_PV_CHI2;
   Int_t           Bs_0_PV_NDOF;
   Float_t         Bs_0_PV_COV_[3][3];
   Float_t         Bs_0_MOM_COV_[4][4];
   Float_t         Bs_0_POSMOM_COV_[4][3];
   Double_t        Bs_0_MCORR;
   Double_t        Bs_0_MCORRERR;
   Double_t        Bs_0_MCORRFULLERR;
   Double_t        Bs_0_Q2SOL1;
   Double_t        Bs_0_Q2SOL2;
   Bool_t          Bs_0_L0Global_Dec;
   Bool_t          Bs_0_L0Global_TIS;
   Bool_t          Bs_0_L0Global_TOS;
   Bool_t          Bs_0_Hlt1Global_Dec;
   Bool_t          Bs_0_Hlt1Global_TIS;
   Bool_t          Bs_0_Hlt1Global_TOS;
   Bool_t          Bs_0_Hlt1Phys_Dec;
   Bool_t          Bs_0_Hlt1Phys_TIS;
   Bool_t          Bs_0_Hlt1Phys_TOS;
   Bool_t          Bs_0_Hlt2Global_Dec;
   Bool_t          Bs_0_Hlt2Global_TIS;
   Bool_t          Bs_0_Hlt2Global_TOS;
   Bool_t          Bs_0_Hlt2Phys_Dec;
   Bool_t          Bs_0_Hlt2Phys_TIS;
   Bool_t          Bs_0_Hlt2Phys_TOS;
   Bool_t          Bs_0_L0MuonDecision_Dec;
   Bool_t          Bs_0_L0MuonDecision_TIS;
   Bool_t          Bs_0_L0MuonDecision_TOS;
   Bool_t          Bs_0_L0DiMuonDecision_Dec;
   Bool_t          Bs_0_L0DiMuonDecision_TIS;
   Bool_t          Bs_0_L0DiMuonDecision_TOS;
   Bool_t          Bs_0_L0HadronDecision_Dec;
   Bool_t          Bs_0_L0HadronDecision_TIS;
   Bool_t          Bs_0_L0HadronDecision_TOS;
   Bool_t          Bs_0_L0ElectronDecision_Dec;
   Bool_t          Bs_0_L0ElectronDecision_TIS;
   Bool_t          Bs_0_L0ElectronDecision_TOS;
   Bool_t          Bs_0_L0ElectronHiDecision_Dec;
   Bool_t          Bs_0_L0ElectronHiDecision_TIS;
   Bool_t          Bs_0_L0ElectronHiDecision_TOS;
   Bool_t          Bs_0_L0PhotonDecision_Dec;
   Bool_t          Bs_0_L0PhotonDecision_TIS;
   Bool_t          Bs_0_L0PhotonDecision_TOS;
   Bool_t          Bs_0_L0PhotonHiDecision_Dec;
   Bool_t          Bs_0_L0PhotonHiDecision_TIS;
   Bool_t          Bs_0_L0PhotonHiDecision_TOS;
   Bool_t          Bs_0_Hlt1SingleMuonNoIPDecision_Dec;
   Bool_t          Bs_0_Hlt1SingleMuonNoIPDecision_TIS;
   Bool_t          Bs_0_Hlt1SingleMuonNoIPDecision_TOS;
   Bool_t          Bs_0_Hlt1SingleMuonHighPTDecision_Dec;
   Bool_t          Bs_0_Hlt1SingleMuonHighPTDecision_TIS;
   Bool_t          Bs_0_Hlt1SingleMuonHighPTDecision_TOS;
   Bool_t          Bs_0_Hlt1SingleElectronNoIPDecision_Dec;
   Bool_t          Bs_0_Hlt1SingleElectronNoIPDecision_TIS;
   Bool_t          Bs_0_Hlt1SingleElectronNoIPDecision_TOS;
   Bool_t          Bs_0_Hlt1TrackAllL0Decision_Dec;
   Bool_t          Bs_0_Hlt1TrackAllL0Decision_TIS;
   Bool_t          Bs_0_Hlt1TrackAllL0Decision_TOS;
   Bool_t          Bs_0_Hlt1TrackMuonDecision_Dec;
   Bool_t          Bs_0_Hlt1TrackMuonDecision_TIS;
   Bool_t          Bs_0_Hlt1TrackMuonDecision_TOS;
   Bool_t          Bs_0_Hlt1TrackPhotonDecision_Dec;
   Bool_t          Bs_0_Hlt1TrackPhotonDecision_TIS;
   Bool_t          Bs_0_Hlt1TrackPhotonDecision_TOS;
   Bool_t          Bs_0_Hlt1TrackAllL0__Decision_Dec;
   Bool_t          Bs_0_Hlt1TrackAllL0__Decision_TIS;
   Bool_t          Bs_0_Hlt1TrackAllL0__Decision_TOS;
   Bool_t          Bs_0_Hlt1DiMuonLowMassDecision_Dec;
   Bool_t          Bs_0_Hlt1DiMuonLowMassDecision_TIS;
   Bool_t          Bs_0_Hlt1DiMuonLowMassDecision_TOS;
   Bool_t          Bs_0_Hlt1DiMuonHighMassDecision_Dec;
   Bool_t          Bs_0_Hlt1DiMuonHighMassDecision_TIS;
   Bool_t          Bs_0_Hlt1DiMuonHighMassDecision_TOS;
   Bool_t          Bs_0_Hlt1MB__Decision_Dec;
   Bool_t          Bs_0_Hlt1MB__Decision_TIS;
   Bool_t          Bs_0_Hlt1MB__Decision_TOS;
   Bool_t          Bs_0_Hlt1TrackAllL0TightDecision_Dec;
   Bool_t          Bs_0_Hlt1TrackAllL0TightDecision_TIS;
   Bool_t          Bs_0_Hlt1TrackAllL0TightDecision_TOS;
   Bool_t          Bs_0_Hlt2SingleMuonDecision_Dec;
   Bool_t          Bs_0_Hlt2SingleMuonDecision_TIS;
   Bool_t          Bs_0_Hlt2SingleMuonDecision_TOS;
   Bool_t          Bs_0_Hlt2SingleMuonLowPTDecision_Dec;
   Bool_t          Bs_0_Hlt2SingleMuonLowPTDecision_TIS;
   Bool_t          Bs_0_Hlt2SingleMuonLowPTDecision_TOS;
   Bool_t          Bs_0_Hlt2SingleMuonHighPTDecision_Dec;
   Bool_t          Bs_0_Hlt2SingleMuonHighPTDecision_TIS;
   Bool_t          Bs_0_Hlt2SingleMuonHighPTDecision_TOS;
   Bool_t          Bs_0_Hlt2DiMuonDecision_Dec;
   Bool_t          Bs_0_Hlt2DiMuonDecision_TIS;
   Bool_t          Bs_0_Hlt2DiMuonDecision_TOS;
   Bool_t          Bs_0_Hlt2DiMuonLowMassDecision_Dec;
   Bool_t          Bs_0_Hlt2DiMuonLowMassDecision_TIS;
   Bool_t          Bs_0_Hlt2DiMuonLowMassDecision_TOS;
   Bool_t          Bs_0_Hlt2DiMuonJPsiHighPTDecision_Dec;
   Bool_t          Bs_0_Hlt2DiMuonJPsiHighPTDecision_TIS;
   Bool_t          Bs_0_Hlt2DiMuonJPsiHighPTDecision_TOS;
   Bool_t          Bs_0_Hlt2DiMuonPsi2SDecision_Dec;
   Bool_t          Bs_0_Hlt2DiMuonPsi2SDecision_TIS;
   Bool_t          Bs_0_Hlt2DiMuonPsi2SDecision_TOS;
   Bool_t          Bs_0_Hlt2DiMuonDetachedDecision_Dec;
   Bool_t          Bs_0_Hlt2DiMuonDetachedDecision_TIS;
   Bool_t          Bs_0_Hlt2DiMuonDetachedDecision_TOS;
   Bool_t          Bs_0_Hlt2DiMuonDetachedJPsiDecision_Dec;
   Bool_t          Bs_0_Hlt2DiMuonDetachedJPsiDecision_TIS;
   Bool_t          Bs_0_Hlt2DiMuonDetachedJPsiDecision_TOS;
   Bool_t          Bs_0_Hlt2DiMuonDetachedHeavyDecision_Dec;
   Bool_t          Bs_0_Hlt2DiMuonDetachedHeavyDecision_TIS;
   Bool_t          Bs_0_Hlt2DiMuonDetachedHeavyDecision_TOS;
   Bool_t          Bs_0_Hlt2TriMuonTauDecision_Dec;
   Bool_t          Bs_0_Hlt2TriMuonTauDecision_TIS;
   Bool_t          Bs_0_Hlt2TriMuonTauDecision_TOS;
   Bool_t          Bs_0_Hlt2B2HHDecision_Dec;
   Bool_t          Bs_0_Hlt2B2HHDecision_TIS;
   Bool_t          Bs_0_Hlt2B2HHDecision_TOS;
   Bool_t          Bs_0_Hlt2DiMuonBDecision_Dec;
   Bool_t          Bs_0_Hlt2DiMuonBDecision_TIS;
   Bool_t          Bs_0_Hlt2DiMuonBDecision_TOS;
   Bool_t          Bs_0_Hlt2DiMuonZDecision_Dec;
   Bool_t          Bs_0_Hlt2DiMuonZDecision_TIS;
   Bool_t          Bs_0_Hlt2DiMuonZDecision_TOS;
   Bool_t          Bs_0_Hlt2TopoMu2BodyBBDTDecision_Dec;
   Bool_t          Bs_0_Hlt2TopoMu2BodyBBDTDecision_TIS;
   Bool_t          Bs_0_Hlt2TopoMu2BodyBBDTDecision_TOS;
   Bool_t          Bs_0_Hlt2TopoMu3BodyBBDTDecision_Dec;
   Bool_t          Bs_0_Hlt2TopoMu3BodyBBDTDecision_TIS;
   Bool_t          Bs_0_Hlt2TopoMu3BodyBBDTDecision_TOS;
   Bool_t          Bs_0_Hlt2TopoMu4BodyBBDTDecision_Dec;
   Bool_t          Bs_0_Hlt2TopoMu4BodyBBDTDecision_TIS;
   Bool_t          Bs_0_Hlt2TopoMu4BodyBBDTDecision_TOS;
   Bool_t          Bs_0_Hlt2Topo2BodyBBDTDecision_Dec;
   Bool_t          Bs_0_Hlt2Topo2BodyBBDTDecision_TIS;
   Bool_t          Bs_0_Hlt2Topo2BodyBBDTDecision_TOS;
   Bool_t          Bs_0_Hlt2Topo3BodyBBDTDecision_Dec;
   Bool_t          Bs_0_Hlt2Topo3BodyBBDTDecision_TIS;
   Bool_t          Bs_0_Hlt2Topo3BodyBBDTDecision_TOS;
   Bool_t          Bs_0_Hlt2Topo4BodyBBDTDecision_Dec;
   Bool_t          Bs_0_Hlt2Topo4BodyBBDTDecision_TIS;
   Bool_t          Bs_0_Hlt2Topo4BodyBBDTDecision_TOS;
   Bool_t          Bs_0_Hlt2Topo2BodySimpleDecision_Dec;
   Bool_t          Bs_0_Hlt2Topo2BodySimpleDecision_TIS;
   Bool_t          Bs_0_Hlt2Topo2BodySimpleDecision_TOS;
   Bool_t          Bs_0_Hlt2Topo3BodySimpleDecision_Dec;
   Bool_t          Bs_0_Hlt2Topo3BodySimpleDecision_TIS;
   Bool_t          Bs_0_Hlt2Topo3BodySimpleDecision_TOS;
   Bool_t          Bs_0_Hlt2Topo4BodySimpleDecision_Dec;
   Bool_t          Bs_0_Hlt2Topo4BodySimpleDecision_TIS;
   Bool_t          Bs_0_Hlt2Topo4BodySimpleDecision_TOS;
   Bool_t          Bs_0_Hlt2PassThroughDecision_Dec;
   Bool_t          Bs_0_Hlt2PassThroughDecision_TIS;
   Bool_t          Bs_0_Hlt2PassThroughDecision_TOS;
   Bool_t          Bs_0_Hlt2TransparentDecision_Dec;
   Bool_t          Bs_0_Hlt2TransparentDecision_TIS;
   Bool_t          Bs_0_Hlt2TransparentDecision_TOS;
   Bool_t          Bs_0_Hlt2IncPhiDecision_Dec;
   Bool_t          Bs_0_Hlt2IncPhiDecision_TIS;
   Bool_t          Bs_0_Hlt2IncPhiDecision_TOS;
   Bool_t          Bs_0_Hlt2DiMuonDY__Decision_Dec;
   Bool_t          Bs_0_Hlt2DiMuonDY__Decision_TIS;
   Bool_t          Bs_0_Hlt2DiMuonDY__Decision_TOS;
   Bool_t          Bs_0_Hlt2TopoE__Decision_Dec;
   Bool_t          Bs_0_Hlt2TopoE__Decision_TIS;
   Bool_t          Bs_0_Hlt2TopoE__Decision_TOS;
   Bool_t          Bs_0_Hlt2Topo__Decision_Dec;
   Bool_t          Bs_0_Hlt2Topo__Decision_TIS;
   Bool_t          Bs_0_Hlt2Topo__Decision_TOS;
   Bool_t          Bs_0_Hlt2Charm__Decision_Dec;
   Bool_t          Bs_0_Hlt2Charm__Decision_TIS;
   Bool_t          Bs_0_Hlt2Charm__Decision_TOS;
   Bool_t          Bs_0_Hlt2DiElectron__Decision_Dec;
   Bool_t          Bs_0_Hlt2DiElectron__Decision_TIS;
   Bool_t          Bs_0_Hlt2DiElectron__Decision_TOS;
   Bool_t          Bs_0_Hlt2__GammaDecision_Dec;
   Bool_t          Bs_0_Hlt2__GammaDecision_TIS;
   Bool_t          Bs_0_Hlt2__GammaDecision_TOS;
   Double_t        Bs_0_NumVtxWithinChi2WindowOneTrack;
   Double_t        Bs_0_SmallestDeltaChi2OneTrack;
   Double_t        Bs_0_SmallestDeltaChi2MassOneTrack;
   Double_t        Bs_0_SmallestDeltaChi2TwoTracks;
   Double_t        Bs_0_SmallestDeltaChi2MassTwoTracks;
   Int_t           Ds_0_00_cc_mult;
   Double_t        Ds_0_00_cc_PX;
   Double_t        Ds_0_00_cc_PY;
   Double_t        Ds_0_00_cc_PZ;
   Double_t        Ds_0_00_cc_vPT;
   Double_t        Ds_0_00_cc_sPT;
   Int_t           Ds_0_00_cc_maxPt_Q;
   Double_t        Ds_0_00_cc_maxPt_PT;
   Double_t        Ds_0_00_cc_maxPt_PX;
   Double_t        Ds_0_00_cc_maxPt_PY;
   Double_t        Ds_0_00_cc_maxPt_PZ;
   Double_t        Ds_0_00_cc_maxPt_PE;
   Int_t           Ds_0_00_nc_mult;
   Double_t        Ds_0_00_nc_PX;
   Double_t        Ds_0_00_nc_PY;
   Double_t        Ds_0_00_nc_PZ;
   Double_t        Ds_0_00_nc_vPT;
   Double_t        Ds_0_00_nc_sPT;
   Double_t        Ds_0_00_nc_maxPt_PT;
   Double_t        Ds_0_00_nc_maxPt_PX;
   Double_t        Ds_0_00_nc_maxPt_PY;
   Double_t        Ds_0_00_nc_maxPt_PZ;
   Int_t           Ds_1_50_cc_mult;
   Double_t        Ds_1_50_cc_PX;
   Double_t        Ds_1_50_cc_PY;
   Double_t        Ds_1_50_cc_PZ;
   Double_t        Ds_1_50_cc_vPT;
   Double_t        Ds_1_50_cc_sPT;
   Int_t           Ds_1_50_nc_mult;
   Double_t        Ds_1_50_nc_PX;
   Double_t        Ds_1_50_nc_PY;
   Double_t        Ds_1_50_nc_PZ;
   Double_t        Ds_1_50_nc_vPT;
   Double_t        Ds_1_50_nc_sPT;
   Double_t        Ds_1_50_nc_maxPt_PX;
   Double_t        Ds_1_50_nc_maxPt_PY;
   Double_t        Ds_1_50_nc_maxPt_PZ;
   Int_t           Ds_1_20_cc_mult;
   Double_t        Ds_1_20_cc_PX;
   Double_t        Ds_1_20_cc_PY;
   Double_t        Ds_1_20_cc_PZ;
   Double_t        Ds_1_20_cc_vPT;
   Double_t        Ds_1_20_cc_sPT;
   Int_t           Ds_1_20_nc_mult;
   Double_t        Ds_1_20_nc_PX;
   Double_t        Ds_1_20_nc_PY;
   Double_t        Ds_1_20_nc_PZ;
   Double_t        Ds_1_20_nc_vPT;
   Double_t        Ds_1_20_nc_sPT;
   Double_t        Ds_1_20_nc_maxPt_PX;
   Double_t        Ds_1_20_nc_maxPt_PY;
   Double_t        Ds_1_20_nc_maxPt_PZ;
   Int_t           Ds_0_90_cc_mult;
   Double_t        Ds_0_90_cc_PX;
   Double_t        Ds_0_90_cc_PY;
   Double_t        Ds_0_90_cc_PZ;
   Double_t        Ds_0_90_cc_vPT;
   Double_t        Ds_0_90_cc_sPT;
   Int_t           Ds_0_90_nc_mult;
   Double_t        Ds_0_90_nc_PX;
   Double_t        Ds_0_90_nc_PY;
   Double_t        Ds_0_90_nc_PZ;
   Double_t        Ds_0_90_nc_vPT;
   Double_t        Ds_0_90_nc_sPT;
   Double_t        Ds_0_90_nc_maxPt_PX;
   Double_t        Ds_0_90_nc_maxPt_PY;
   Double_t        Ds_0_90_nc_maxPt_PZ;
   Int_t           Ds_0_60_cc_mult;
   Double_t        Ds_0_60_cc_PX;
   Double_t        Ds_0_60_cc_PY;
   Double_t        Ds_0_60_cc_PZ;
   Double_t        Ds_0_60_cc_vPT;
   Double_t        Ds_0_60_cc_sPT;
   Int_t           Ds_0_60_nc_mult;
   Double_t        Ds_0_60_nc_PX;
   Double_t        Ds_0_60_nc_PY;
   Double_t        Ds_0_60_nc_PZ;
   Double_t        Ds_0_60_nc_vPT;
   Double_t        Ds_0_60_nc_sPT;
   Double_t        Ds_0_60_nc_maxPt_PX;
   Double_t        Ds_0_60_nc_maxPt_PY;
   Double_t        Ds_0_60_nc_maxPt_PZ;
   Int_t           Ds_0_30_cc_mult;
   Double_t        Ds_0_30_cc_PX;
   Double_t        Ds_0_30_cc_PY;
   Double_t        Ds_0_30_cc_PZ;
   Double_t        Ds_0_30_cc_vPT;
   Double_t        Ds_0_30_cc_sPT;
   Int_t           Ds_0_30_nc_mult;
   Double_t        Ds_0_30_nc_PX;
   Double_t        Ds_0_30_nc_PY;
   Double_t        Ds_0_30_nc_PZ;
   Double_t        Ds_0_30_nc_vPT;
   Double_t        Ds_0_30_nc_sPT;
   Double_t        Ds_0_30_nc_maxPt_PX;
   Double_t        Ds_0_30_nc_maxPt_PY;
   Double_t        Ds_0_30_nc_maxPt_PZ;
   Double_t        Ds_MINIP;
   Double_t        Ds_MINIPCHI2;
   Double_t        Ds_MINIPNEXTBEST;
   Double_t        Ds_MINIPCHI2NEXTBEST;
   Double_t        Ds_ENDVERTEX_X;
   Double_t        Ds_ENDVERTEX_Y;
   Double_t        Ds_ENDVERTEX_Z;
   Double_t        Ds_ENDVERTEX_XERR;
   Double_t        Ds_ENDVERTEX_YERR;
   Double_t        Ds_ENDVERTEX_ZERR;
   Double_t        Ds_ENDVERTEX_CHI2;
   Int_t           Ds_ENDVERTEX_NDOF;
   Float_t         Ds_ENDVERTEX_COV_[3][3];
   Double_t        Ds_OWNPV_X;
   Double_t        Ds_OWNPV_Y;
   Double_t        Ds_OWNPV_Z;
   Double_t        Ds_OWNPV_XERR;
   Double_t        Ds_OWNPV_YERR;
   Double_t        Ds_OWNPV_ZERR;
   Double_t        Ds_OWNPV_CHI2;
   Int_t           Ds_OWNPV_NDOF;
   Float_t         Ds_OWNPV_COV_[3][3];
   Double_t        Ds_IP_OWNPV;
   Double_t        Ds_IPCHI2_OWNPV;
   Double_t        Ds_FD_OWNPV;
   Double_t        Ds_FDCHI2_OWNPV;
   Double_t        Ds_DIRA_OWNPV;
   Double_t        Ds_TOPPV_X;
   Double_t        Ds_TOPPV_Y;
   Double_t        Ds_TOPPV_Z;
   Double_t        Ds_TOPPV_XERR;
   Double_t        Ds_TOPPV_YERR;
   Double_t        Ds_TOPPV_ZERR;
   Double_t        Ds_TOPPV_CHI2;
   Int_t           Ds_TOPPV_NDOF;
   Float_t         Ds_TOPPV_COV_[3][3];
   Double_t        Ds_IP_TOPPV;
   Double_t        Ds_IPCHI2_TOPPV;
   Double_t        Ds_FD_TOPPV;
   Double_t        Ds_FDCHI2_TOPPV;
   Double_t        Ds_DIRA_TOPPV;
   Double_t        Ds_ORIVX_X;
   Double_t        Ds_ORIVX_Y;
   Double_t        Ds_ORIVX_Z;
   Double_t        Ds_ORIVX_XERR;
   Double_t        Ds_ORIVX_YERR;
   Double_t        Ds_ORIVX_ZERR;
   Double_t        Ds_ORIVX_CHI2;
   Int_t           Ds_ORIVX_NDOF;
   Float_t         Ds_ORIVX_COV_[3][3];
   Double_t        Ds_IP_ORIVX;
   Double_t        Ds_IPCHI2_ORIVX;
   Double_t        Ds_FD_ORIVX;
   Double_t        Ds_FDCHI2_ORIVX;
   Double_t        Ds_DIRA_ORIVX;
   Double_t        Ds_P;
   Double_t        Ds_PT;
   Double_t        Ds_PE;
   Double_t        Ds_PX;
   Double_t        Ds_PY;
   Double_t        Ds_PZ;
   Double_t        Ds_MM;
   Double_t        Ds_MMERR;
   Double_t        Ds_M;
   Int_t           Ds_ID;
   Double_t        Ds_eta;
   Double_t        Ds_phi;
   Double_t        Ds_TAU;
   Double_t        Ds_TAUERR;
   Double_t        Ds_TAUCHI2;
   Double_t        Ds_NumVtxWithinChi2WindowOneTrack;
   Double_t        Ds_SmallestDeltaChi2OneTrack;
   Double_t        Ds_SmallestDeltaChi2MassOneTrack;
   Double_t        Ds_SmallestDeltaChi2TwoTracks;
   Double_t        Ds_SmallestDeltaChi2MassTwoTracks;
   Double_t        Kmi_MC12TuneV2_ProbNNe;
   Double_t        Kmi_MC12TuneV2_ProbNNmu;
   Double_t        Kmi_MC12TuneV2_ProbNNpi;
   Double_t        Kmi_MC12TuneV2_ProbNNk;
   Double_t        Kmi_MC12TuneV2_ProbNNp;
   Double_t        Kmi_MC12TuneV2_ProbNNghost;
   Double_t        Kmi_MC12TuneV3_ProbNNe;
   Double_t        Kmi_MC12TuneV3_ProbNNmu;
   Double_t        Kmi_MC12TuneV3_ProbNNpi;
   Double_t        Kmi_MC12TuneV3_ProbNNk;
   Double_t        Kmi_MC12TuneV3_ProbNNp;
   Double_t        Kmi_MC12TuneV3_ProbNNghost;
   Double_t        Kmi_MINIP;
   Double_t        Kmi_MINIPCHI2;
   Double_t        Kmi_MINIPNEXTBEST;
   Double_t        Kmi_MINIPCHI2NEXTBEST;
   Double_t        Kmi_OWNPV_X;
   Double_t        Kmi_OWNPV_Y;
   Double_t        Kmi_OWNPV_Z;
   Double_t        Kmi_OWNPV_XERR;
   Double_t        Kmi_OWNPV_YERR;
   Double_t        Kmi_OWNPV_ZERR;
   Double_t        Kmi_OWNPV_CHI2;
   Int_t           Kmi_OWNPV_NDOF;
   Float_t         Kmi_OWNPV_COV_[3][3];
   Double_t        Kmi_IP_OWNPV;
   Double_t        Kmi_IPCHI2_OWNPV;
   Double_t        Kmi_TOPPV_X;
   Double_t        Kmi_TOPPV_Y;
   Double_t        Kmi_TOPPV_Z;
   Double_t        Kmi_TOPPV_XERR;
   Double_t        Kmi_TOPPV_YERR;
   Double_t        Kmi_TOPPV_ZERR;
   Double_t        Kmi_TOPPV_CHI2;
   Int_t           Kmi_TOPPV_NDOF;
   Float_t         Kmi_TOPPV_COV_[3][3];
   Double_t        Kmi_IP_TOPPV;
   Double_t        Kmi_IPCHI2_TOPPV;
   Double_t        Kmi_ORIVX_X;
   Double_t        Kmi_ORIVX_Y;
   Double_t        Kmi_ORIVX_Z;
   Double_t        Kmi_ORIVX_XERR;
   Double_t        Kmi_ORIVX_YERR;
   Double_t        Kmi_ORIVX_ZERR;
   Double_t        Kmi_ORIVX_CHI2;
   Int_t           Kmi_ORIVX_NDOF;
   Float_t         Kmi_ORIVX_COV_[3][3];
   Double_t        Kmi_IP_ORIVX;
   Double_t        Kmi_IPCHI2_ORIVX;
   Double_t        Kmi_P;
   Double_t        Kmi_PT;
   Double_t        Kmi_PE;
   Double_t        Kmi_PX;
   Double_t        Kmi_PY;
   Double_t        Kmi_PZ;
   Double_t        Kmi_M;
   Int_t           Kmi_ID;
   Double_t        Kmi_eta;
   Double_t        Kmi_phi;
   Double_t        Kmi_PIDe;
   Double_t        Kmi_PIDmu;
   Double_t        Kmi_PIDK;
   Double_t        Kmi_PIDp;
   Double_t        Kmi_ProbNNe;
   Double_t        Kmi_ProbNNk;
   Double_t        Kmi_ProbNNp;
   Double_t        Kmi_ProbNNpi;
   Double_t        Kmi_ProbNNmu;
   Double_t        Kmi_ProbNNghost;
   Bool_t          Kmi_hasMuon;
   Bool_t          Kmi_isMuon;
   Bool_t          Kmi_hasRich;
   Bool_t          Kmi_hasCalo;
   Double_t        Kmi_SV_X;
   Double_t        Kmi_SV_Y;
   Double_t        Kmi_SV_Z;
   Double_t        Kmi_SV_XERR;
   Double_t        Kmi_SV_YERR;
   Double_t        Kmi_SV_ZERR;
   Double_t        Kmi_SV_CHI2;
   Int_t           Kmi_SV_NDOF;
   Float_t         Kmi_SV_COV_[3][3];
   Double_t        Kmi_PV_X;
   Double_t        Kmi_PV_Y;
   Double_t        Kmi_PV_Z;
   Double_t        Kmi_PV_CHI2;
   Int_t           Kmi_PV_NDOF;
   Float_t         Kmi_PV_COV_[3][3];
   Float_t         Kmi_MOM_COV_[4][4];
   Float_t         Kmi_POSMOM_COV_[4][3];
   Double_t        Kmi_MCORR;
   Double_t        Kmi_MCORRERR;
   Double_t        Kmi_MCORRFULLERR;
   Double_t        Kmi_Q2SOL1;
   Double_t        Kmi_Q2SOL2;
   Int_t           Kmi_TRACK_Type;
   Int_t           Kmi_TRACK_Key;
   Double_t        Kmi_TRACK_CHI2NDOF;
   Double_t        Kmi_TRACK_PCHI2;
   Double_t        Kmi_TRACK_MatchCHI2;
   Double_t        Kmi_TRACK_GhostProb;
   Double_t        Kmi_TRACK_CloneDist;
   Double_t        Kmi_TRACK_Likelihood;
   Double_t        Kpl_MC12TuneV2_ProbNNe;
   Double_t        Kpl_MC12TuneV2_ProbNNmu;
   Double_t        Kpl_MC12TuneV2_ProbNNpi;
   Double_t        Kpl_MC12TuneV2_ProbNNk;
   Double_t        Kpl_MC12TuneV2_ProbNNp;
   Double_t        Kpl_MC12TuneV2_ProbNNghost;
   Double_t        Kpl_MC12TuneV3_ProbNNe;
   Double_t        Kpl_MC12TuneV3_ProbNNmu;
   Double_t        Kpl_MC12TuneV3_ProbNNpi;
   Double_t        Kpl_MC12TuneV3_ProbNNk;
   Double_t        Kpl_MC12TuneV3_ProbNNp;
   Double_t        Kpl_MC12TuneV3_ProbNNghost;
   Double_t        Kpl_MINIP;
   Double_t        Kpl_MINIPCHI2;
   Double_t        Kpl_MINIPNEXTBEST;
   Double_t        Kpl_MINIPCHI2NEXTBEST;
   Double_t        Kpl_OWNPV_X;
   Double_t        Kpl_OWNPV_Y;
   Double_t        Kpl_OWNPV_Z;
   Double_t        Kpl_OWNPV_XERR;
   Double_t        Kpl_OWNPV_YERR;
   Double_t        Kpl_OWNPV_ZERR;
   Double_t        Kpl_OWNPV_CHI2;
   Int_t           Kpl_OWNPV_NDOF;
   Float_t         Kpl_OWNPV_COV_[3][3];
   Double_t        Kpl_IP_OWNPV;
   Double_t        Kpl_IPCHI2_OWNPV;
   Double_t        Kpl_TOPPV_X;
   Double_t        Kpl_TOPPV_Y;
   Double_t        Kpl_TOPPV_Z;
   Double_t        Kpl_TOPPV_XERR;
   Double_t        Kpl_TOPPV_YERR;
   Double_t        Kpl_TOPPV_ZERR;
   Double_t        Kpl_TOPPV_CHI2;
   Int_t           Kpl_TOPPV_NDOF;
   Float_t         Kpl_TOPPV_COV_[3][3];
   Double_t        Kpl_IP_TOPPV;
   Double_t        Kpl_IPCHI2_TOPPV;
   Double_t        Kpl_ORIVX_X;
   Double_t        Kpl_ORIVX_Y;
   Double_t        Kpl_ORIVX_Z;
   Double_t        Kpl_ORIVX_XERR;
   Double_t        Kpl_ORIVX_YERR;
   Double_t        Kpl_ORIVX_ZERR;
   Double_t        Kpl_ORIVX_CHI2;
   Int_t           Kpl_ORIVX_NDOF;
   Float_t         Kpl_ORIVX_COV_[3][3];
   Double_t        Kpl_IP_ORIVX;
   Double_t        Kpl_IPCHI2_ORIVX;
   Double_t        Kpl_P;
   Double_t        Kpl_PT;
   Double_t        Kpl_PE;
   Double_t        Kpl_PX;
   Double_t        Kpl_PY;
   Double_t        Kpl_PZ;
   Double_t        Kpl_M;
   Int_t           Kpl_ID;
   Double_t        Kpl_eta;
   Double_t        Kpl_phi;
   Double_t        Kpl_PIDe;
   Double_t        Kpl_PIDmu;
   Double_t        Kpl_PIDK;
   Double_t        Kpl_PIDp;
   Double_t        Kpl_ProbNNe;
   Double_t        Kpl_ProbNNk;
   Double_t        Kpl_ProbNNp;
   Double_t        Kpl_ProbNNpi;
   Double_t        Kpl_ProbNNmu;
   Double_t        Kpl_ProbNNghost;
   Bool_t          Kpl_hasMuon;
   Bool_t          Kpl_isMuon;
   Bool_t          Kpl_hasRich;
   Bool_t          Kpl_hasCalo;
   Double_t        Kpl_SV_X;
   Double_t        Kpl_SV_Y;
   Double_t        Kpl_SV_Z;
   Double_t        Kpl_SV_XERR;
   Double_t        Kpl_SV_YERR;
   Double_t        Kpl_SV_ZERR;
   Double_t        Kpl_SV_CHI2;
   Int_t           Kpl_SV_NDOF;
   Float_t         Kpl_SV_COV_[3][3];
   Double_t        Kpl_PV_X;
   Double_t        Kpl_PV_Y;
   Double_t        Kpl_PV_Z;
   Double_t        Kpl_PV_CHI2;
   Int_t           Kpl_PV_NDOF;
   Float_t         Kpl_PV_COV_[3][3];
   Float_t         Kpl_MOM_COV_[4][4];
   Float_t         Kpl_POSMOM_COV_[4][3];
   Double_t        Kpl_MCORR;
   Double_t        Kpl_MCORRERR;
   Double_t        Kpl_MCORRFULLERR;
   Double_t        Kpl_Q2SOL1;
   Double_t        Kpl_Q2SOL2;
   Int_t           Kpl_TRACK_Type;
   Int_t           Kpl_TRACK_Key;
   Double_t        Kpl_TRACK_CHI2NDOF;
   Double_t        Kpl_TRACK_PCHI2;
   Double_t        Kpl_TRACK_MatchCHI2;
   Double_t        Kpl_TRACK_GhostProb;
   Double_t        Kpl_TRACK_CloneDist;
   Double_t        Kpl_TRACK_Likelihood;
   Double_t        pi_MC12TuneV2_ProbNNe;
   Double_t        pi_MC12TuneV2_ProbNNmu;
   Double_t        pi_MC12TuneV2_ProbNNpi;
   Double_t        pi_MC12TuneV2_ProbNNk;
   Double_t        pi_MC12TuneV2_ProbNNp;
   Double_t        pi_MC12TuneV2_ProbNNghost;
   Double_t        pi_MC12TuneV3_ProbNNe;
   Double_t        pi_MC12TuneV3_ProbNNmu;
   Double_t        pi_MC12TuneV3_ProbNNpi;
   Double_t        pi_MC12TuneV3_ProbNNk;
   Double_t        pi_MC12TuneV3_ProbNNp;
   Double_t        pi_MC12TuneV3_ProbNNghost;
   Double_t        pi_MINIP;
   Double_t        pi_MINIPCHI2;
   Double_t        pi_MINIPNEXTBEST;
   Double_t        pi_MINIPCHI2NEXTBEST;
   Double_t        pi_OWNPV_X;
   Double_t        pi_OWNPV_Y;
   Double_t        pi_OWNPV_Z;
   Double_t        pi_OWNPV_XERR;
   Double_t        pi_OWNPV_YERR;
   Double_t        pi_OWNPV_ZERR;
   Double_t        pi_OWNPV_CHI2;
   Int_t           pi_OWNPV_NDOF;
   Float_t         pi_OWNPV_COV_[3][3];
   Double_t        pi_IP_OWNPV;
   Double_t        pi_IPCHI2_OWNPV;
   Double_t        pi_TOPPV_X;
   Double_t        pi_TOPPV_Y;
   Double_t        pi_TOPPV_Z;
   Double_t        pi_TOPPV_XERR;
   Double_t        pi_TOPPV_YERR;
   Double_t        pi_TOPPV_ZERR;
   Double_t        pi_TOPPV_CHI2;
   Int_t           pi_TOPPV_NDOF;
   Float_t         pi_TOPPV_COV_[3][3];
   Double_t        pi_IP_TOPPV;
   Double_t        pi_IPCHI2_TOPPV;
   Double_t        pi_ORIVX_X;
   Double_t        pi_ORIVX_Y;
   Double_t        pi_ORIVX_Z;
   Double_t        pi_ORIVX_XERR;
   Double_t        pi_ORIVX_YERR;
   Double_t        pi_ORIVX_ZERR;
   Double_t        pi_ORIVX_CHI2;
   Int_t           pi_ORIVX_NDOF;
   Float_t         pi_ORIVX_COV_[3][3];
   Double_t        pi_IP_ORIVX;
   Double_t        pi_IPCHI2_ORIVX;
   Double_t        pi_P;
   Double_t        pi_PT;
   Double_t        pi_PE;
   Double_t        pi_PX;
   Double_t        pi_PY;
   Double_t        pi_PZ;
   Double_t        pi_M;
   Int_t           pi_ID;
   Double_t        pi_eta;
   Double_t        pi_phi;
   Double_t        pi_PIDe;
   Double_t        pi_PIDmu;
   Double_t        pi_PIDK;
   Double_t        pi_PIDp;
   Double_t        pi_ProbNNe;
   Double_t        pi_ProbNNk;
   Double_t        pi_ProbNNp;
   Double_t        pi_ProbNNpi;
   Double_t        pi_ProbNNmu;
   Double_t        pi_ProbNNghost;
   Bool_t          pi_hasMuon;
   Bool_t          pi_isMuon;
   Bool_t          pi_hasRich;
   Bool_t          pi_hasCalo;
   Double_t        pi_SV_X;
   Double_t        pi_SV_Y;
   Double_t        pi_SV_Z;
   Double_t        pi_SV_XERR;
   Double_t        pi_SV_YERR;
   Double_t        pi_SV_ZERR;
   Double_t        pi_SV_CHI2;
   Int_t           pi_SV_NDOF;
   Float_t         pi_SV_COV_[3][3];
   Double_t        pi_PV_X;
   Double_t        pi_PV_Y;
   Double_t        pi_PV_Z;
   Double_t        pi_PV_CHI2;
   Int_t           pi_PV_NDOF;
   Float_t         pi_PV_COV_[3][3];
   Float_t         pi_MOM_COV_[4][4];
   Float_t         pi_POSMOM_COV_[4][3];
   Double_t        pi_MCORR;
   Double_t        pi_MCORRERR;
   Double_t        pi_MCORRFULLERR;
   Double_t        pi_Q2SOL1;
   Double_t        pi_Q2SOL2;
   Int_t           pi_TRACK_Type;
   Int_t           pi_TRACK_Key;
   Double_t        pi_TRACK_CHI2NDOF;
   Double_t        pi_TRACK_PCHI2;
   Double_t        pi_TRACK_MatchCHI2;
   Double_t        pi_TRACK_GhostProb;
   Double_t        pi_TRACK_CloneDist;
   Double_t        pi_TRACK_Likelihood;
   Double_t        mu_MC12TuneV2_ProbNNe;
   Double_t        mu_MC12TuneV2_ProbNNmu;
   Double_t        mu_MC12TuneV2_ProbNNpi;
   Double_t        mu_MC12TuneV2_ProbNNk;
   Double_t        mu_MC12TuneV2_ProbNNp;
   Double_t        mu_MC12TuneV2_ProbNNghost;
   Double_t        mu_MC12TuneV3_ProbNNe;
   Double_t        mu_MC12TuneV3_ProbNNmu;
   Double_t        mu_MC12TuneV3_ProbNNpi;
   Double_t        mu_MC12TuneV3_ProbNNk;
   Double_t        mu_MC12TuneV3_ProbNNp;
   Double_t        mu_MC12TuneV3_ProbNNghost;
   Int_t           mu_0_00_cc_mult;
   Double_t        mu_0_00_cc_PX;
   Double_t        mu_0_00_cc_PY;
   Double_t        mu_0_00_cc_PZ;
   Double_t        mu_0_00_cc_vPT;
   Double_t        mu_0_00_cc_sPT;
   Int_t           mu_0_00_cc_maxPt_Q;
   Double_t        mu_0_00_cc_maxPt_PT;
   Double_t        mu_0_00_cc_maxPt_PX;
   Double_t        mu_0_00_cc_maxPt_PY;
   Double_t        mu_0_00_cc_maxPt_PZ;
   Double_t        mu_0_00_cc_maxPt_PE;
   Int_t           mu_0_00_nc_mult;
   Double_t        mu_0_00_nc_PX;
   Double_t        mu_0_00_nc_PY;
   Double_t        mu_0_00_nc_PZ;
   Double_t        mu_0_00_nc_vPT;
   Double_t        mu_0_00_nc_sPT;
   Double_t        mu_0_00_nc_maxPt_PT;
   Double_t        mu_0_00_nc_maxPt_PX;
   Double_t        mu_0_00_nc_maxPt_PY;
   Double_t        mu_0_00_nc_maxPt_PZ;
   Int_t           mu_1_50_cc_mult;
   Double_t        mu_1_50_cc_PX;
   Double_t        mu_1_50_cc_PY;
   Double_t        mu_1_50_cc_PZ;
   Double_t        mu_1_50_cc_vPT;
   Double_t        mu_1_50_cc_sPT;
   Int_t           mu_1_50_nc_mult;
   Double_t        mu_1_50_nc_PX;
   Double_t        mu_1_50_nc_PY;
   Double_t        mu_1_50_nc_PZ;
   Double_t        mu_1_50_nc_vPT;
   Double_t        mu_1_50_nc_sPT;
   Int_t           mu_1_20_cc_mult;
   Double_t        mu_1_20_cc_PX;
   Double_t        mu_1_20_cc_PY;
   Double_t        mu_1_20_cc_PZ;
   Double_t        mu_1_20_cc_vPT;
   Double_t        mu_1_20_cc_sPT;
   Int_t           mu_1_20_nc_mult;
   Double_t        mu_1_20_nc_PX;
   Double_t        mu_1_20_nc_PY;
   Double_t        mu_1_20_nc_PZ;
   Double_t        mu_1_20_nc_vPT;
   Double_t        mu_1_20_nc_sPT;
   Int_t           mu_0_90_cc_mult;
   Double_t        mu_0_90_cc_PX;
   Double_t        mu_0_90_cc_PY;
   Double_t        mu_0_90_cc_PZ;
   Double_t        mu_0_90_cc_vPT;
   Double_t        mu_0_90_cc_sPT;
   Int_t           mu_0_90_nc_mult;
   Double_t        mu_0_90_nc_PX;
   Double_t        mu_0_90_nc_PY;
   Double_t        mu_0_90_nc_PZ;
   Double_t        mu_0_90_nc_vPT;
   Double_t        mu_0_90_nc_sPT;
   Int_t           mu_0_60_cc_mult;
   Double_t        mu_0_60_cc_PX;
   Double_t        mu_0_60_cc_PY;
   Double_t        mu_0_60_cc_PZ;
   Double_t        mu_0_60_cc_vPT;
   Double_t        mu_0_60_cc_sPT;
   Int_t           mu_0_60_nc_mult;
   Double_t        mu_0_60_nc_PX;
   Double_t        mu_0_60_nc_PY;
   Double_t        mu_0_60_nc_PZ;
   Double_t        mu_0_60_nc_vPT;
   Double_t        mu_0_60_nc_sPT;
   Int_t           mu_0_30_cc_mult;
   Double_t        mu_0_30_cc_PX;
   Double_t        mu_0_30_cc_PY;
   Double_t        mu_0_30_cc_PZ;
   Double_t        mu_0_30_cc_vPT;
   Double_t        mu_0_30_cc_sPT;
   Int_t           mu_0_30_nc_mult;
   Double_t        mu_0_30_nc_PX;
   Double_t        mu_0_30_nc_PY;
   Double_t        mu_0_30_nc_PZ;
   Double_t        mu_0_30_nc_vPT;
   Double_t        mu_0_30_nc_sPT;
   Double_t        mu_MINIP;
   Double_t        mu_MINIPCHI2;
   Double_t        mu_MINIPNEXTBEST;
   Double_t        mu_MINIPCHI2NEXTBEST;
   Double_t        mu_OWNPV_X;
   Double_t        mu_OWNPV_Y;
   Double_t        mu_OWNPV_Z;
   Double_t        mu_OWNPV_XERR;
   Double_t        mu_OWNPV_YERR;
   Double_t        mu_OWNPV_ZERR;
   Double_t        mu_OWNPV_CHI2;
   Int_t           mu_OWNPV_NDOF;
   Float_t         mu_OWNPV_COV_[3][3];
   Double_t        mu_IP_OWNPV;
   Double_t        mu_IPCHI2_OWNPV;
   Double_t        mu_TOPPV_X;
   Double_t        mu_TOPPV_Y;
   Double_t        mu_TOPPV_Z;
   Double_t        mu_TOPPV_XERR;
   Double_t        mu_TOPPV_YERR;
   Double_t        mu_TOPPV_ZERR;
   Double_t        mu_TOPPV_CHI2;
   Int_t           mu_TOPPV_NDOF;
   Float_t         mu_TOPPV_COV_[3][3];
   Double_t        mu_IP_TOPPV;
   Double_t        mu_IPCHI2_TOPPV;
   Double_t        mu_ORIVX_X;
   Double_t        mu_ORIVX_Y;
   Double_t        mu_ORIVX_Z;
   Double_t        mu_ORIVX_XERR;
   Double_t        mu_ORIVX_YERR;
   Double_t        mu_ORIVX_ZERR;
   Double_t        mu_ORIVX_CHI2;
   Int_t           mu_ORIVX_NDOF;
   Float_t         mu_ORIVX_COV_[3][3];
   Double_t        mu_IP_ORIVX;
   Double_t        mu_IPCHI2_ORIVX;
   Double_t        mu_P;
   Double_t        mu_PT;
   Double_t        mu_PE;
   Double_t        mu_PX;
   Double_t        mu_PY;
   Double_t        mu_PZ;
   Double_t        mu_M;
   Int_t           mu_ID;
   Int_t           mu_nVeloIDs;
   Int_t           mu_nITIDs;
   Int_t           mu_nTTIDs;
   Int_t           mu_nOTIDs;
   Double_t        mu_eta;
   Double_t        mu_phi;
   Double_t        mu_PIDe;
   Double_t        mu_PIDmu;
   Double_t        mu_PIDK;
   Double_t        mu_PIDp;
   Double_t        mu_ProbNNe;
   Double_t        mu_ProbNNk;
   Double_t        mu_ProbNNp;
   Double_t        mu_ProbNNpi;
   Double_t        mu_ProbNNmu;
   Double_t        mu_ProbNNghost;
   Bool_t          mu_hasMuon;
   Bool_t          mu_isMuon;
   Bool_t          mu_hasRich;
   Bool_t          mu_hasCalo;
   Double_t        mu_SV_X;
   Double_t        mu_SV_Y;
   Double_t        mu_SV_Z;
   Double_t        mu_SV_XERR;
   Double_t        mu_SV_YERR;
   Double_t        mu_SV_ZERR;
   Double_t        mu_SV_CHI2;
   Int_t           mu_SV_NDOF;
   Float_t         mu_SV_COV_[3][3];
   Double_t        mu_PV_X;
   Double_t        mu_PV_Y;
   Double_t        mu_PV_Z;
   Double_t        mu_PV_CHI2;
   Int_t           mu_PV_NDOF;
   Float_t         mu_PV_COV_[3][3];
   Float_t         mu_MOM_COV_[4][4];
   Float_t         mu_POSMOM_COV_[4][3];
   Double_t        mu_MCORR;
   Double_t        mu_MCORRERR;
   Double_t        mu_MCORRFULLERR;
   Double_t        mu_Q2SOL1;
   Double_t        mu_Q2SOL2;
   Bool_t          mu_L0Global_Dec;
   Bool_t          mu_L0Global_TIS;
   Bool_t          mu_L0Global_TOS;
   Bool_t          mu_Hlt1Global_Dec;
   Bool_t          mu_Hlt1Global_TIS;
   Bool_t          mu_Hlt1Global_TOS;
   Bool_t          mu_Hlt1Phys_Dec;
   Bool_t          mu_Hlt1Phys_TIS;
   Bool_t          mu_Hlt1Phys_TOS;
   Bool_t          mu_Hlt2Global_Dec;
   Bool_t          mu_Hlt2Global_TIS;
   Bool_t          mu_Hlt2Global_TOS;
   Bool_t          mu_Hlt2Phys_Dec;
   Bool_t          mu_Hlt2Phys_TIS;
   Bool_t          mu_Hlt2Phys_TOS;
   Bool_t          mu_L0MuonDecision_Dec;
   Bool_t          mu_L0MuonDecision_TIS;
   Bool_t          mu_L0MuonDecision_TOS;
   Bool_t          mu_L0DiMuonDecision_Dec;
   Bool_t          mu_L0DiMuonDecision_TIS;
   Bool_t          mu_L0DiMuonDecision_TOS;
   Bool_t          mu_L0HadronDecision_Dec;
   Bool_t          mu_L0HadronDecision_TIS;
   Bool_t          mu_L0HadronDecision_TOS;
   Bool_t          mu_L0ElectronDecision_Dec;
   Bool_t          mu_L0ElectronDecision_TIS;
   Bool_t          mu_L0ElectronDecision_TOS;
   Bool_t          mu_L0ElectronHiDecision_Dec;
   Bool_t          mu_L0ElectronHiDecision_TIS;
   Bool_t          mu_L0ElectronHiDecision_TOS;
   Bool_t          mu_L0PhotonDecision_Dec;
   Bool_t          mu_L0PhotonDecision_TIS;
   Bool_t          mu_L0PhotonDecision_TOS;
   Bool_t          mu_L0PhotonHiDecision_Dec;
   Bool_t          mu_L0PhotonHiDecision_TIS;
   Bool_t          mu_L0PhotonHiDecision_TOS;
   Bool_t          mu_Hlt1SingleMuonNoIPDecision_Dec;
   Bool_t          mu_Hlt1SingleMuonNoIPDecision_TIS;
   Bool_t          mu_Hlt1SingleMuonNoIPDecision_TOS;
   Bool_t          mu_Hlt1SingleMuonHighPTDecision_Dec;
   Bool_t          mu_Hlt1SingleMuonHighPTDecision_TIS;
   Bool_t          mu_Hlt1SingleMuonHighPTDecision_TOS;
   Bool_t          mu_Hlt1SingleElectronNoIPDecision_Dec;
   Bool_t          mu_Hlt1SingleElectronNoIPDecision_TIS;
   Bool_t          mu_Hlt1SingleElectronNoIPDecision_TOS;
   Bool_t          mu_Hlt1TrackAllL0Decision_Dec;
   Bool_t          mu_Hlt1TrackAllL0Decision_TIS;
   Bool_t          mu_Hlt1TrackAllL0Decision_TOS;
   Bool_t          mu_Hlt1TrackMuonDecision_Dec;
   Bool_t          mu_Hlt1TrackMuonDecision_TIS;
   Bool_t          mu_Hlt1TrackMuonDecision_TOS;
   Bool_t          mu_Hlt1TrackPhotonDecision_Dec;
   Bool_t          mu_Hlt1TrackPhotonDecision_TIS;
   Bool_t          mu_Hlt1TrackPhotonDecision_TOS;
   Bool_t          mu_Hlt1TrackAllL0__Decision_Dec;
   Bool_t          mu_Hlt1TrackAllL0__Decision_TIS;
   Bool_t          mu_Hlt1TrackAllL0__Decision_TOS;
   Bool_t          mu_Hlt1DiMuonLowMassDecision_Dec;
   Bool_t          mu_Hlt1DiMuonLowMassDecision_TIS;
   Bool_t          mu_Hlt1DiMuonLowMassDecision_TOS;
   Bool_t          mu_Hlt1DiMuonHighMassDecision_Dec;
   Bool_t          mu_Hlt1DiMuonHighMassDecision_TIS;
   Bool_t          mu_Hlt1DiMuonHighMassDecision_TOS;
   Bool_t          mu_Hlt1MB__Decision_Dec;
   Bool_t          mu_Hlt1MB__Decision_TIS;
   Bool_t          mu_Hlt1MB__Decision_TOS;
   Bool_t          mu_Hlt1TrackAllL0TightDecision_Dec;
   Bool_t          mu_Hlt1TrackAllL0TightDecision_TIS;
   Bool_t          mu_Hlt1TrackAllL0TightDecision_TOS;
   Bool_t          mu_Hlt2SingleMuonDecision_Dec;
   Bool_t          mu_Hlt2SingleMuonDecision_TIS;
   Bool_t          mu_Hlt2SingleMuonDecision_TOS;
   Bool_t          mu_Hlt2SingleMuonLowPTDecision_Dec;
   Bool_t          mu_Hlt2SingleMuonLowPTDecision_TIS;
   Bool_t          mu_Hlt2SingleMuonLowPTDecision_TOS;
   Bool_t          mu_Hlt2SingleMuonHighPTDecision_Dec;
   Bool_t          mu_Hlt2SingleMuonHighPTDecision_TIS;
   Bool_t          mu_Hlt2SingleMuonHighPTDecision_TOS;
   Bool_t          mu_Hlt2DiMuonDecision_Dec;
   Bool_t          mu_Hlt2DiMuonDecision_TIS;
   Bool_t          mu_Hlt2DiMuonDecision_TOS;
   Bool_t          mu_Hlt2DiMuonLowMassDecision_Dec;
   Bool_t          mu_Hlt2DiMuonLowMassDecision_TIS;
   Bool_t          mu_Hlt2DiMuonLowMassDecision_TOS;
   Bool_t          mu_Hlt2DiMuonJPsiHighPTDecision_Dec;
   Bool_t          mu_Hlt2DiMuonJPsiHighPTDecision_TIS;
   Bool_t          mu_Hlt2DiMuonJPsiHighPTDecision_TOS;
   Bool_t          mu_Hlt2DiMuonPsi2SDecision_Dec;
   Bool_t          mu_Hlt2DiMuonPsi2SDecision_TIS;
   Bool_t          mu_Hlt2DiMuonPsi2SDecision_TOS;
   Bool_t          mu_Hlt2DiMuonDetachedDecision_Dec;
   Bool_t          mu_Hlt2DiMuonDetachedDecision_TIS;
   Bool_t          mu_Hlt2DiMuonDetachedDecision_TOS;
   Bool_t          mu_Hlt2DiMuonDetachedJPsiDecision_Dec;
   Bool_t          mu_Hlt2DiMuonDetachedJPsiDecision_TIS;
   Bool_t          mu_Hlt2DiMuonDetachedJPsiDecision_TOS;
   Bool_t          mu_Hlt2DiMuonDetachedHeavyDecision_Dec;
   Bool_t          mu_Hlt2DiMuonDetachedHeavyDecision_TIS;
   Bool_t          mu_Hlt2DiMuonDetachedHeavyDecision_TOS;
   Bool_t          mu_Hlt2TriMuonTauDecision_Dec;
   Bool_t          mu_Hlt2TriMuonTauDecision_TIS;
   Bool_t          mu_Hlt2TriMuonTauDecision_TOS;
   Bool_t          mu_Hlt2B2HHDecision_Dec;
   Bool_t          mu_Hlt2B2HHDecision_TIS;
   Bool_t          mu_Hlt2B2HHDecision_TOS;
   Bool_t          mu_Hlt2DiMuonBDecision_Dec;
   Bool_t          mu_Hlt2DiMuonBDecision_TIS;
   Bool_t          mu_Hlt2DiMuonBDecision_TOS;
   Bool_t          mu_Hlt2DiMuonZDecision_Dec;
   Bool_t          mu_Hlt2DiMuonZDecision_TIS;
   Bool_t          mu_Hlt2DiMuonZDecision_TOS;
   Bool_t          mu_Hlt2TopoMu2BodyBBDTDecision_Dec;
   Bool_t          mu_Hlt2TopoMu2BodyBBDTDecision_TIS;
   Bool_t          mu_Hlt2TopoMu2BodyBBDTDecision_TOS;
   Bool_t          mu_Hlt2TopoMu3BodyBBDTDecision_Dec;
   Bool_t          mu_Hlt2TopoMu3BodyBBDTDecision_TIS;
   Bool_t          mu_Hlt2TopoMu3BodyBBDTDecision_TOS;
   Bool_t          mu_Hlt2TopoMu4BodyBBDTDecision_Dec;
   Bool_t          mu_Hlt2TopoMu4BodyBBDTDecision_TIS;
   Bool_t          mu_Hlt2TopoMu4BodyBBDTDecision_TOS;
   Bool_t          mu_Hlt2Topo2BodyBBDTDecision_Dec;
   Bool_t          mu_Hlt2Topo2BodyBBDTDecision_TIS;
   Bool_t          mu_Hlt2Topo2BodyBBDTDecision_TOS;
   Bool_t          mu_Hlt2Topo3BodyBBDTDecision_Dec;
   Bool_t          mu_Hlt2Topo3BodyBBDTDecision_TIS;
   Bool_t          mu_Hlt2Topo3BodyBBDTDecision_TOS;
   Bool_t          mu_Hlt2Topo4BodyBBDTDecision_Dec;
   Bool_t          mu_Hlt2Topo4BodyBBDTDecision_TIS;
   Bool_t          mu_Hlt2Topo4BodyBBDTDecision_TOS;
   Bool_t          mu_Hlt2Topo2BodySimpleDecision_Dec;
   Bool_t          mu_Hlt2Topo2BodySimpleDecision_TIS;
   Bool_t          mu_Hlt2Topo2BodySimpleDecision_TOS;
   Bool_t          mu_Hlt2Topo3BodySimpleDecision_Dec;
   Bool_t          mu_Hlt2Topo3BodySimpleDecision_TIS;
   Bool_t          mu_Hlt2Topo3BodySimpleDecision_TOS;
   Bool_t          mu_Hlt2Topo4BodySimpleDecision_Dec;
   Bool_t          mu_Hlt2Topo4BodySimpleDecision_TIS;
   Bool_t          mu_Hlt2Topo4BodySimpleDecision_TOS;
   Bool_t          mu_Hlt2PassThroughDecision_Dec;
   Bool_t          mu_Hlt2PassThroughDecision_TIS;
   Bool_t          mu_Hlt2PassThroughDecision_TOS;
   Bool_t          mu_Hlt2TransparentDecision_Dec;
   Bool_t          mu_Hlt2TransparentDecision_TIS;
   Bool_t          mu_Hlt2TransparentDecision_TOS;
   Bool_t          mu_Hlt2IncPhiDecision_Dec;
   Bool_t          mu_Hlt2IncPhiDecision_TIS;
   Bool_t          mu_Hlt2IncPhiDecision_TOS;
   Bool_t          mu_Hlt2DiMuonDY__Decision_Dec;
   Bool_t          mu_Hlt2DiMuonDY__Decision_TIS;
   Bool_t          mu_Hlt2DiMuonDY__Decision_TOS;
   Bool_t          mu_Hlt2TopoE__Decision_Dec;
   Bool_t          mu_Hlt2TopoE__Decision_TIS;
   Bool_t          mu_Hlt2TopoE__Decision_TOS;
   Bool_t          mu_Hlt2Topo__Decision_Dec;
   Bool_t          mu_Hlt2Topo__Decision_TIS;
   Bool_t          mu_Hlt2Topo__Decision_TOS;
   Bool_t          mu_Hlt2Charm__Decision_Dec;
   Bool_t          mu_Hlt2Charm__Decision_TIS;
   Bool_t          mu_Hlt2Charm__Decision_TOS;
   Bool_t          mu_Hlt2DiElectron__Decision_Dec;
   Bool_t          mu_Hlt2DiElectron__Decision_TIS;
   Bool_t          mu_Hlt2DiElectron__Decision_TOS;
   Bool_t          mu_Hlt2__GammaDecision_Dec;
   Bool_t          mu_Hlt2__GammaDecision_TIS;
   Bool_t          mu_Hlt2__GammaDecision_TOS;
   Int_t           mu_TRACK_Type;
   Int_t           mu_TRACK_Key;
   Double_t        mu_TRACK_CHI2NDOF;
   Double_t        mu_TRACK_PCHI2;
   Double_t        mu_TRACK_MatchCHI2;
   Double_t        mu_TRACK_GhostProb;
   Double_t        mu_TRACK_CloneDist;
   Double_t        mu_TRACK_Likelihood;
   UInt_t          nCandidate;
   ULong64_t       totCandidates;
   ULong64_t       EventInSequence;
   Double_t        nVeloTraks_All;
   UInt_t          runNumber;
   ULong64_t       eventNumber;
   UInt_t          BCID;
   Int_t           BCType;
   UInt_t          OdinTCK;
   UInt_t          L0DUTCK;
   UInt_t          HLT1TCK;
   UInt_t          HLT2TCK;
   ULong64_t       GpsTime;
   Short_t         Polarity;
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
   Int_t           L0Global;
   UInt_t          Hlt1Global;
   UInt_t          Hlt2Global;

   // List of branches
   TBranch        *b_Bs_0_MINIP;   //!
   TBranch        *b_Bs_0_MINIPCHI2;   //!
   TBranch        *b_Bs_0_MINIPNEXTBEST;   //!
   TBranch        *b_Bs_0_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_Bs_0_ENDVERTEX_X;   //!
   TBranch        *b_Bs_0_ENDVERTEX_Y;   //!
   TBranch        *b_Bs_0_ENDVERTEX_Z;   //!
   TBranch        *b_Bs_0_ENDVERTEX_XERR;   //!
   TBranch        *b_Bs_0_ENDVERTEX_YERR;   //!
   TBranch        *b_Bs_0_ENDVERTEX_ZERR;   //!
   TBranch        *b_Bs_0_ENDVERTEX_CHI2;   //!
   TBranch        *b_Bs_0_ENDVERTEX_NDOF;   //!
   TBranch        *b_Bs_0_ENDVERTEX_COV_;   //!
   TBranch        *b_Bs_0_OWNPV_X;   //!
   TBranch        *b_Bs_0_OWNPV_Y;   //!
   TBranch        *b_Bs_0_OWNPV_Z;   //!
   TBranch        *b_Bs_0_OWNPV_XERR;   //!
   TBranch        *b_Bs_0_OWNPV_YERR;   //!
   TBranch        *b_Bs_0_OWNPV_ZERR;   //!
   TBranch        *b_Bs_0_OWNPV_CHI2;   //!
   TBranch        *b_Bs_0_OWNPV_NDOF;   //!
   TBranch        *b_Bs_0_OWNPV_COV_;   //!
   TBranch        *b_Bs_0_IP_OWNPV;   //!
   TBranch        *b_Bs_0_IPCHI2_OWNPV;   //!
   TBranch        *b_Bs_0_FD_OWNPV;   //!
   TBranch        *b_Bs_0_FDCHI2_OWNPV;   //!
   TBranch        *b_Bs_0_DIRA_OWNPV;   //!
   TBranch        *b_Bs_0_TOPPV_X;   //!
   TBranch        *b_Bs_0_TOPPV_Y;   //!
   TBranch        *b_Bs_0_TOPPV_Z;   //!
   TBranch        *b_Bs_0_TOPPV_XERR;   //!
   TBranch        *b_Bs_0_TOPPV_YERR;   //!
   TBranch        *b_Bs_0_TOPPV_ZERR;   //!
   TBranch        *b_Bs_0_TOPPV_CHI2;   //!
   TBranch        *b_Bs_0_TOPPV_NDOF;   //!
   TBranch        *b_Bs_0_TOPPV_COV_;   //!
   TBranch        *b_Bs_0_IP_TOPPV;   //!
   TBranch        *b_Bs_0_IPCHI2_TOPPV;   //!
   TBranch        *b_Bs_0_FD_TOPPV;   //!
   TBranch        *b_Bs_0_FDCHI2_TOPPV;   //!
   TBranch        *b_Bs_0_DIRA_TOPPV;   //!
   TBranch        *b_Bs_0_P;   //!
   TBranch        *b_Bs_0_PT;   //!
   TBranch        *b_Bs_0_PE;   //!
   TBranch        *b_Bs_0_PX;   //!
   TBranch        *b_Bs_0_PY;   //!
   TBranch        *b_Bs_0_PZ;   //!
   TBranch        *b_Bs_0_MM;   //!
   TBranch        *b_Bs_0_MMERR;   //!
   TBranch        *b_Bs_0_M;   //!
   TBranch        *b_Bs_0_ID;   //!
   TBranch        *b_Bs_0_eta;   //!
   TBranch        *b_Bs_0_phi;   //!
   TBranch        *b_Bs_0_BDTS_BIPS;   //!
   TBranch        *b_Bs_0_BDTS_DOCA;   //!
   TBranch        *b_Bs_0_BDTS_VTXCHI2;   //!
   TBranch        *b_Bs_0_BDTS_DIRA;   //!
   TBranch        *b_Bs_0_BDTS_BIP;   //!
   TBranch        *b_Bs_0_BDTS_MuonMINIP;   //!
   TBranch        *b_Bs_0_BDTS;   //!
   TBranch        *b_Bs_0_CTAU_ps;   //!
   TBranch        *b_Bs_0_TAU;   //!
   TBranch        *b_Bs_0_TAUERR;   //!
   TBranch        *b_Bs_0_TAUCHI2;   //!
   TBranch        *b_Bs_0_SV_X;   //!
   TBranch        *b_Bs_0_SV_Y;   //!
   TBranch        *b_Bs_0_SV_Z;   //!
   TBranch        *b_Bs_0_SV_CHI2;   //!
   TBranch        *b_Bs_0_SV_NDOF;   //!
   TBranch        *b_Bs_0_SV_COV_;   //!
   TBranch        *b_Bs_0_PV_X;   //!
   TBranch        *b_Bs_0_PV_Y;   //!
   TBranch        *b_Bs_0_PV_Z;   //!
   TBranch        *b_Bs_0_PV_CHI2;   //!
   TBranch        *b_Bs_0_PV_NDOF;   //!
   TBranch        *b_Bs_0_PV_COV_;   //!
   TBranch        *b_Bs_0_MOM_COV_;   //!
   TBranch        *b_Bs_0_POSMOM_COV_;   //!
   TBranch        *b_Bs_0_MCORR;   //!
   TBranch        *b_Bs_0_MCORRERR;   //!
   TBranch        *b_Bs_0_MCORRFULLERR;   //!
   TBranch        *b_Bs_0_Q2SOL1;   //!
   TBranch        *b_Bs_0_Q2SOL2;   //!
   TBranch        *b_Bs_0_L0Global_Dec;   //!
   TBranch        *b_Bs_0_L0Global_TIS;   //!
   TBranch        *b_Bs_0_L0Global_TOS;   //!
   TBranch        *b_Bs_0_Hlt1Global_Dec;   //!
   TBranch        *b_Bs_0_Hlt1Global_TIS;   //!
   TBranch        *b_Bs_0_Hlt1Global_TOS;   //!
   TBranch        *b_Bs_0_Hlt1Phys_Dec;   //!
   TBranch        *b_Bs_0_Hlt1Phys_TIS;   //!
   TBranch        *b_Bs_0_Hlt1Phys_TOS;   //!
   TBranch        *b_Bs_0_Hlt2Global_Dec;   //!
   TBranch        *b_Bs_0_Hlt2Global_TIS;   //!
   TBranch        *b_Bs_0_Hlt2Global_TOS;   //!
   TBranch        *b_Bs_0_Hlt2Phys_Dec;   //!
   TBranch        *b_Bs_0_Hlt2Phys_TIS;   //!
   TBranch        *b_Bs_0_Hlt2Phys_TOS;   //!
   TBranch        *b_Bs_0_L0MuonDecision_Dec;   //!
   TBranch        *b_Bs_0_L0MuonDecision_TIS;   //!
   TBranch        *b_Bs_0_L0MuonDecision_TOS;   //!
   TBranch        *b_Bs_0_L0DiMuonDecision_Dec;   //!
   TBranch        *b_Bs_0_L0DiMuonDecision_TIS;   //!
   TBranch        *b_Bs_0_L0DiMuonDecision_TOS;   //!
   TBranch        *b_Bs_0_L0HadronDecision_Dec;   //!
   TBranch        *b_Bs_0_L0HadronDecision_TIS;   //!
   TBranch        *b_Bs_0_L0HadronDecision_TOS;   //!
   TBranch        *b_Bs_0_L0ElectronDecision_Dec;   //!
   TBranch        *b_Bs_0_L0ElectronDecision_TIS;   //!
   TBranch        *b_Bs_0_L0ElectronDecision_TOS;   //!
   TBranch        *b_Bs_0_L0ElectronHiDecision_Dec;   //!
   TBranch        *b_Bs_0_L0ElectronHiDecision_TIS;   //!
   TBranch        *b_Bs_0_L0ElectronHiDecision_TOS;   //!
   TBranch        *b_Bs_0_L0PhotonDecision_Dec;   //!
   TBranch        *b_Bs_0_L0PhotonDecision_TIS;   //!
   TBranch        *b_Bs_0_L0PhotonDecision_TOS;   //!
   TBranch        *b_Bs_0_L0PhotonHiDecision_Dec;   //!
   TBranch        *b_Bs_0_L0PhotonHiDecision_TIS;   //!
   TBranch        *b_Bs_0_L0PhotonHiDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt1SingleMuonNoIPDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt1SingleMuonNoIPDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt1SingleMuonNoIPDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt1SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt1SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt1SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt1SingleElectronNoIPDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt1SingleElectronNoIPDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt1SingleElectronNoIPDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt1TrackAllL0Decision_Dec;   //!
   TBranch        *b_Bs_0_Hlt1TrackAllL0Decision_TIS;   //!
   TBranch        *b_Bs_0_Hlt1TrackAllL0Decision_TOS;   //!
   TBranch        *b_Bs_0_Hlt1TrackMuonDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt1TrackMuonDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt1TrackMuonDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt1TrackPhotonDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt1TrackPhotonDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt1TrackPhotonDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt1TrackAllL0__Decision_Dec;   //!
   TBranch        *b_Bs_0_Hlt1TrackAllL0__Decision_TIS;   //!
   TBranch        *b_Bs_0_Hlt1TrackAllL0__Decision_TOS;   //!
   TBranch        *b_Bs_0_Hlt1DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt1DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt1DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt1DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt1DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt1MB__Decision_Dec;   //!
   TBranch        *b_Bs_0_Hlt1MB__Decision_TIS;   //!
   TBranch        *b_Bs_0_Hlt1MB__Decision_TOS;   //!
   TBranch        *b_Bs_0_Hlt1TrackAllL0TightDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt1TrackAllL0TightDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt1TrackAllL0TightDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2SingleMuonLowPTDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonJPsiHighPTDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonJPsiHighPTDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonJPsiHighPTDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonPsi2SDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonPsi2SDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonPsi2SDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonDetachedDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonDetachedDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonDetachedDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonDetachedJPsiDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonDetachedJPsiDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonDetachedJPsiDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonDetachedHeavyDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonDetachedHeavyDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonDetachedHeavyDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2TriMuonTauDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2TriMuonTauDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2TriMuonTauDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2B2HHDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2B2HHDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2B2HHDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonBDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonBDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonBDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonZDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonZDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonZDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2TopoMu2BodyBBDTDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2TopoMu2BodyBBDTDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2TopoMu2BodyBBDTDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2TopoMu3BodyBBDTDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2TopoMu3BodyBBDTDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2TopoMu3BodyBBDTDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2TopoMu4BodyBBDTDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2TopoMu4BodyBBDTDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2TopoMu4BodyBBDTDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2Topo2BodyBBDTDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2Topo2BodyBBDTDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2Topo2BodyBBDTDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2Topo3BodyBBDTDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2Topo3BodyBBDTDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2Topo3BodyBBDTDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2Topo4BodyBBDTDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2Topo4BodyBBDTDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2Topo4BodyBBDTDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2Topo2BodySimpleDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2Topo2BodySimpleDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2Topo2BodySimpleDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2Topo3BodySimpleDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2Topo3BodySimpleDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2Topo3BodySimpleDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2Topo4BodySimpleDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2Topo4BodySimpleDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2Topo4BodySimpleDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2PassThroughDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2PassThroughDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2PassThroughDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2TransparentDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2TransparentDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2TransparentDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2IncPhiDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2IncPhiDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2IncPhiDecision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonDY__Decision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonDY__Decision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2DiMuonDY__Decision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2TopoE__Decision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2TopoE__Decision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2TopoE__Decision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2Topo__Decision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2Topo__Decision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2Topo__Decision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2Charm__Decision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2Charm__Decision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2Charm__Decision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2DiElectron__Decision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2DiElectron__Decision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2DiElectron__Decision_TOS;   //!
   TBranch        *b_Bs_0_Hlt2__GammaDecision_Dec;   //!
   TBranch        *b_Bs_0_Hlt2__GammaDecision_TIS;   //!
   TBranch        *b_Bs_0_Hlt2__GammaDecision_TOS;   //!
   TBranch        *b_Bs_0_NumVtxWithinChi2WindowOneTrack;   //!
   TBranch        *b_Bs_0_SmallestDeltaChi2OneTrack;   //!
   TBranch        *b_Bs_0_SmallestDeltaChi2MassOneTrack;   //!
   TBranch        *b_Bs_0_SmallestDeltaChi2TwoTracks;   //!
   TBranch        *b_Bs_0_SmallestDeltaChi2MassTwoTracks;   //!
   TBranch        *b_Ds_0_00_cc_mult;   //!
   TBranch        *b_Ds_0_00_cc_PX;   //!
   TBranch        *b_Ds_0_00_cc_PY;   //!
   TBranch        *b_Ds_0_00_cc_PZ;   //!
   TBranch        *b_Ds_0_00_cc_vPT;   //!
   TBranch        *b_Ds_0_00_cc_sPT;   //!
   TBranch        *b_Ds_0_00_cc_maxPt_Q;   //!
   TBranch        *b_Ds_0_00_cc_maxPt_PT;   //!
   TBranch        *b_Ds_0_00_cc_maxPt_PX;   //!
   TBranch        *b_Ds_0_00_cc_maxPt_PY;   //!
   TBranch        *b_Ds_0_00_cc_maxPt_PZ;   //!
   TBranch        *b_Ds_0_00_cc_maxPt_PE;   //!
   TBranch        *b_Ds_0_00_nc_mult;   //!
   TBranch        *b_Ds_0_00_nc_PX;   //!
   TBranch        *b_Ds_0_00_nc_PY;   //!
   TBranch        *b_Ds_0_00_nc_PZ;   //!
   TBranch        *b_Ds_0_00_nc_vPT;   //!
   TBranch        *b_Ds_0_00_nc_sPT;   //!
   TBranch        *b_Ds_0_00_nc_maxPt_PT;   //!
   TBranch        *b_Ds_0_00_nc_maxPt_PX;   //!
   TBranch        *b_Ds_0_00_nc_maxPt_PY;   //!
   TBranch        *b_Ds_0_00_nc_maxPt_PZ;   //!
   TBranch        *b_Ds_1_50_cc_mult;   //!
   TBranch        *b_Ds_1_50_cc_PX;   //!
   TBranch        *b_Ds_1_50_cc_PY;   //!
   TBranch        *b_Ds_1_50_cc_PZ;   //!
   TBranch        *b_Ds_1_50_cc_vPT;   //!
   TBranch        *b_Ds_1_50_cc_sPT;   //!
   TBranch        *b_Ds_1_50_nc_mult;   //!
   TBranch        *b_Ds_1_50_nc_PX;   //!
   TBranch        *b_Ds_1_50_nc_PY;   //!
   TBranch        *b_Ds_1_50_nc_PZ;   //!
   TBranch        *b_Ds_1_50_nc_vPT;   //!
   TBranch        *b_Ds_1_50_nc_sPT;   //!
   TBranch        *b_Ds_1_50_nc_maxPt_PX;   //!
   TBranch        *b_Ds_1_50_nc_maxPt_PY;   //!
   TBranch        *b_Ds_1_50_nc_maxPt_PZ;   //!
   TBranch        *b_Ds_1_20_cc_mult;   //!
   TBranch        *b_Ds_1_20_cc_PX;   //!
   TBranch        *b_Ds_1_20_cc_PY;   //!
   TBranch        *b_Ds_1_20_cc_PZ;   //!
   TBranch        *b_Ds_1_20_cc_vPT;   //!
   TBranch        *b_Ds_1_20_cc_sPT;   //!
   TBranch        *b_Ds_1_20_nc_mult;   //!
   TBranch        *b_Ds_1_20_nc_PX;   //!
   TBranch        *b_Ds_1_20_nc_PY;   //!
   TBranch        *b_Ds_1_20_nc_PZ;   //!
   TBranch        *b_Ds_1_20_nc_vPT;   //!
   TBranch        *b_Ds_1_20_nc_sPT;   //!
   TBranch        *b_Ds_1_20_nc_maxPt_PX;   //!
   TBranch        *b_Ds_1_20_nc_maxPt_PY;   //!
   TBranch        *b_Ds_1_20_nc_maxPt_PZ;   //!
   TBranch        *b_Ds_0_90_cc_mult;   //!
   TBranch        *b_Ds_0_90_cc_PX;   //!
   TBranch        *b_Ds_0_90_cc_PY;   //!
   TBranch        *b_Ds_0_90_cc_PZ;   //!
   TBranch        *b_Ds_0_90_cc_vPT;   //!
   TBranch        *b_Ds_0_90_cc_sPT;   //!
   TBranch        *b_Ds_0_90_nc_mult;   //!
   TBranch        *b_Ds_0_90_nc_PX;   //!
   TBranch        *b_Ds_0_90_nc_PY;   //!
   TBranch        *b_Ds_0_90_nc_PZ;   //!
   TBranch        *b_Ds_0_90_nc_vPT;   //!
   TBranch        *b_Ds_0_90_nc_sPT;   //!
   TBranch        *b_Ds_0_90_nc_maxPt_PX;   //!
   TBranch        *b_Ds_0_90_nc_maxPt_PY;   //!
   TBranch        *b_Ds_0_90_nc_maxPt_PZ;   //!
   TBranch        *b_Ds_0_60_cc_mult;   //!
   TBranch        *b_Ds_0_60_cc_PX;   //!
   TBranch        *b_Ds_0_60_cc_PY;   //!
   TBranch        *b_Ds_0_60_cc_PZ;   //!
   TBranch        *b_Ds_0_60_cc_vPT;   //!
   TBranch        *b_Ds_0_60_cc_sPT;   //!
   TBranch        *b_Ds_0_60_nc_mult;   //!
   TBranch        *b_Ds_0_60_nc_PX;   //!
   TBranch        *b_Ds_0_60_nc_PY;   //!
   TBranch        *b_Ds_0_60_nc_PZ;   //!
   TBranch        *b_Ds_0_60_nc_vPT;   //!
   TBranch        *b_Ds_0_60_nc_sPT;   //!
   TBranch        *b_Ds_0_60_nc_maxPt_PX;   //!
   TBranch        *b_Ds_0_60_nc_maxPt_PY;   //!
   TBranch        *b_Ds_0_60_nc_maxPt_PZ;   //!
   TBranch        *b_Ds_0_30_cc_mult;   //!
   TBranch        *b_Ds_0_30_cc_PX;   //!
   TBranch        *b_Ds_0_30_cc_PY;   //!
   TBranch        *b_Ds_0_30_cc_PZ;   //!
   TBranch        *b_Ds_0_30_cc_vPT;   //!
   TBranch        *b_Ds_0_30_cc_sPT;   //!
   TBranch        *b_Ds_0_30_nc_mult;   //!
   TBranch        *b_Ds_0_30_nc_PX;   //!
   TBranch        *b_Ds_0_30_nc_PY;   //!
   TBranch        *b_Ds_0_30_nc_PZ;   //!
   TBranch        *b_Ds_0_30_nc_vPT;   //!
   TBranch        *b_Ds_0_30_nc_sPT;   //!
   TBranch        *b_Ds_0_30_nc_maxPt_PX;   //!
   TBranch        *b_Ds_0_30_nc_maxPt_PY;   //!
   TBranch        *b_Ds_0_30_nc_maxPt_PZ;   //!
   TBranch        *b_Ds_MINIP;   //!
   TBranch        *b_Ds_MINIPCHI2;   //!
   TBranch        *b_Ds_MINIPNEXTBEST;   //!
   TBranch        *b_Ds_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_Ds_ENDVERTEX_X;   //!
   TBranch        *b_Ds_ENDVERTEX_Y;   //!
   TBranch        *b_Ds_ENDVERTEX_Z;   //!
   TBranch        *b_Ds_ENDVERTEX_XERR;   //!
   TBranch        *b_Ds_ENDVERTEX_YERR;   //!
   TBranch        *b_Ds_ENDVERTEX_ZERR;   //!
   TBranch        *b_Ds_ENDVERTEX_CHI2;   //!
   TBranch        *b_Ds_ENDVERTEX_NDOF;   //!
   TBranch        *b_Ds_ENDVERTEX_COV_;   //!
   TBranch        *b_Ds_OWNPV_X;   //!
   TBranch        *b_Ds_OWNPV_Y;   //!
   TBranch        *b_Ds_OWNPV_Z;   //!
   TBranch        *b_Ds_OWNPV_XERR;   //!
   TBranch        *b_Ds_OWNPV_YERR;   //!
   TBranch        *b_Ds_OWNPV_ZERR;   //!
   TBranch        *b_Ds_OWNPV_CHI2;   //!
   TBranch        *b_Ds_OWNPV_NDOF;   //!
   TBranch        *b_Ds_OWNPV_COV_;   //!
   TBranch        *b_Ds_IP_OWNPV;   //!
   TBranch        *b_Ds_IPCHI2_OWNPV;   //!
   TBranch        *b_Ds_FD_OWNPV;   //!
   TBranch        *b_Ds_FDCHI2_OWNPV;   //!
   TBranch        *b_Ds_DIRA_OWNPV;   //!
   TBranch        *b_Ds_TOPPV_X;   //!
   TBranch        *b_Ds_TOPPV_Y;   //!
   TBranch        *b_Ds_TOPPV_Z;   //!
   TBranch        *b_Ds_TOPPV_XERR;   //!
   TBranch        *b_Ds_TOPPV_YERR;   //!
   TBranch        *b_Ds_TOPPV_ZERR;   //!
   TBranch        *b_Ds_TOPPV_CHI2;   //!
   TBranch        *b_Ds_TOPPV_NDOF;   //!
   TBranch        *b_Ds_TOPPV_COV_;   //!
   TBranch        *b_Ds_IP_TOPPV;   //!
   TBranch        *b_Ds_IPCHI2_TOPPV;   //!
   TBranch        *b_Ds_FD_TOPPV;   //!
   TBranch        *b_Ds_FDCHI2_TOPPV;   //!
   TBranch        *b_Ds_DIRA_TOPPV;   //!
   TBranch        *b_Ds_ORIVX_X;   //!
   TBranch        *b_Ds_ORIVX_Y;   //!
   TBranch        *b_Ds_ORIVX_Z;   //!
   TBranch        *b_Ds_ORIVX_XERR;   //!
   TBranch        *b_Ds_ORIVX_YERR;   //!
   TBranch        *b_Ds_ORIVX_ZERR;   //!
   TBranch        *b_Ds_ORIVX_CHI2;   //!
   TBranch        *b_Ds_ORIVX_NDOF;   //!
   TBranch        *b_Ds_ORIVX_COV_;   //!
   TBranch        *b_Ds_IP_ORIVX;   //!
   TBranch        *b_Ds_IPCHI2_ORIVX;   //!
   TBranch        *b_Ds_FD_ORIVX;   //!
   TBranch        *b_Ds_FDCHI2_ORIVX;   //!
   TBranch        *b_Ds_DIRA_ORIVX;   //!
   TBranch        *b_Ds_P;   //!
   TBranch        *b_Ds_PT;   //!
   TBranch        *b_Ds_PE;   //!
   TBranch        *b_Ds_PX;   //!
   TBranch        *b_Ds_PY;   //!
   TBranch        *b_Ds_PZ;   //!
   TBranch        *b_Ds_MM;   //!
   TBranch        *b_Ds_MMERR;   //!
   TBranch        *b_Ds_M;   //!
   TBranch        *b_Ds_ID;   //!
   TBranch        *b_Ds_eta;   //!
   TBranch        *b_Ds_phi;   //!
   TBranch        *b_Ds_TAU;   //!
   TBranch        *b_Ds_TAUERR;   //!
   TBranch        *b_Ds_TAUCHI2;   //!
   TBranch        *b_Ds_NumVtxWithinChi2WindowOneTrack;   //!
   TBranch        *b_Ds_SmallestDeltaChi2OneTrack;   //!
   TBranch        *b_Ds_SmallestDeltaChi2MassOneTrack;   //!
   TBranch        *b_Ds_SmallestDeltaChi2TwoTracks;   //!
   TBranch        *b_Ds_SmallestDeltaChi2MassTwoTracks;   //!
   TBranch        *b_Kmi_MC12TuneV2_ProbNNe;   //!
   TBranch        *b_Kmi_MC12TuneV2_ProbNNmu;   //!
   TBranch        *b_Kmi_MC12TuneV2_ProbNNpi;   //!
   TBranch        *b_Kmi_MC12TuneV2_ProbNNk;   //!
   TBranch        *b_Kmi_MC12TuneV2_ProbNNp;   //!
   TBranch        *b_Kmi_MC12TuneV2_ProbNNghost;   //!
   TBranch        *b_Kmi_MC12TuneV3_ProbNNe;   //!
   TBranch        *b_Kmi_MC12TuneV3_ProbNNmu;   //!
   TBranch        *b_Kmi_MC12TuneV3_ProbNNpi;   //!
   TBranch        *b_Kmi_MC12TuneV3_ProbNNk;   //!
   TBranch        *b_Kmi_MC12TuneV3_ProbNNp;   //!
   TBranch        *b_Kmi_MC12TuneV3_ProbNNghost;   //!
   TBranch        *b_Kmi_MINIP;   //!
   TBranch        *b_Kmi_MINIPCHI2;   //!
   TBranch        *b_Kmi_MINIPNEXTBEST;   //!
   TBranch        *b_Kmi_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_Kmi_OWNPV_X;   //!
   TBranch        *b_Kmi_OWNPV_Y;   //!
   TBranch        *b_Kmi_OWNPV_Z;   //!
   TBranch        *b_Kmi_OWNPV_XERR;   //!
   TBranch        *b_Kmi_OWNPV_YERR;   //!
   TBranch        *b_Kmi_OWNPV_ZERR;   //!
   TBranch        *b_Kmi_OWNPV_CHI2;   //!
   TBranch        *b_Kmi_OWNPV_NDOF;   //!
   TBranch        *b_Kmi_OWNPV_COV_;   //!
   TBranch        *b_Kmi_IP_OWNPV;   //!
   TBranch        *b_Kmi_IPCHI2_OWNPV;   //!
   TBranch        *b_Kmi_TOPPV_X;   //!
   TBranch        *b_Kmi_TOPPV_Y;   //!
   TBranch        *b_Kmi_TOPPV_Z;   //!
   TBranch        *b_Kmi_TOPPV_XERR;   //!
   TBranch        *b_Kmi_TOPPV_YERR;   //!
   TBranch        *b_Kmi_TOPPV_ZERR;   //!
   TBranch        *b_Kmi_TOPPV_CHI2;   //!
   TBranch        *b_Kmi_TOPPV_NDOF;   //!
   TBranch        *b_Kmi_TOPPV_COV_;   //!
   TBranch        *b_Kmi_IP_TOPPV;   //!
   TBranch        *b_Kmi_IPCHI2_TOPPV;   //!
   TBranch        *b_Kmi_ORIVX_X;   //!
   TBranch        *b_Kmi_ORIVX_Y;   //!
   TBranch        *b_Kmi_ORIVX_Z;   //!
   TBranch        *b_Kmi_ORIVX_XERR;   //!
   TBranch        *b_Kmi_ORIVX_YERR;   //!
   TBranch        *b_Kmi_ORIVX_ZERR;   //!
   TBranch        *b_Kmi_ORIVX_CHI2;   //!
   TBranch        *b_Kmi_ORIVX_NDOF;   //!
   TBranch        *b_Kmi_ORIVX_COV_;   //!
   TBranch        *b_Kmi_IP_ORIVX;   //!
   TBranch        *b_Kmi_IPCHI2_ORIVX;   //!
   TBranch        *b_Kmi_P;   //!
   TBranch        *b_Kmi_PT;   //!
   TBranch        *b_Kmi_PE;   //!
   TBranch        *b_Kmi_PX;   //!
   TBranch        *b_Kmi_PY;   //!
   TBranch        *b_Kmi_PZ;   //!
   TBranch        *b_Kmi_M;   //!
   TBranch        *b_Kmi_ID;   //!
   TBranch        *b_Kmi_eta;   //!
   TBranch        *b_Kmi_phi;   //!
   TBranch        *b_Kmi_PIDe;   //!
   TBranch        *b_Kmi_PIDmu;   //!
   TBranch        *b_Kmi_PIDK;   //!
   TBranch        *b_Kmi_PIDp;   //!
   TBranch        *b_Kmi_ProbNNe;   //!
   TBranch        *b_Kmi_ProbNNk;   //!
   TBranch        *b_Kmi_ProbNNp;   //!
   TBranch        *b_Kmi_ProbNNpi;   //!
   TBranch        *b_Kmi_ProbNNmu;   //!
   TBranch        *b_Kmi_ProbNNghost;   //!
   TBranch        *b_Kmi_hasMuon;   //!
   TBranch        *b_Kmi_isMuon;   //!
   TBranch        *b_Kmi_hasRich;   //!
   TBranch        *b_Kmi_hasCalo;   //!
   TBranch        *b_Kmi_SV_X;   //!
   TBranch        *b_Kmi_SV_Y;   //!
   TBranch        *b_Kmi_SV_Z;   //!
   TBranch        *b_Kmi_SV_XERR;   //!
   TBranch        *b_Kmi_SV_YERR;   //!
   TBranch        *b_Kmi_SV_ZERR;   //!
   TBranch        *b_Kmi_SV_CHI2;   //!
   TBranch        *b_Kmi_SV_NDOF;   //!
   TBranch        *b_Kmi_SV_COV_;   //!
   TBranch        *b_Kmi_PV_X;   //!
   TBranch        *b_Kmi_PV_Y;   //!
   TBranch        *b_Kmi_PV_Z;   //!
   TBranch        *b_Kmi_PV_CHI2;   //!
   TBranch        *b_Kmi_PV_NDOF;   //!
   TBranch        *b_Kmi_PV_COV_;   //!
   TBranch        *b_Kmi_MOM_COV_;   //!
   TBranch        *b_Kmi_POSMOM_COV_;   //!
   TBranch        *b_Kmi_MCORR;   //!
   TBranch        *b_Kmi_MCORRERR;   //!
   TBranch        *b_Kmi_MCORRFULLERR;   //!
   TBranch        *b_Kmi_Q2SOL1;   //!
   TBranch        *b_Kmi_Q2SOL2;   //!
   TBranch        *b_Kmi_TRACK_Type;   //!
   TBranch        *b_Kmi_TRACK_Key;   //!
   TBranch        *b_Kmi_TRACK_CHI2NDOF;   //!
   TBranch        *b_Kmi_TRACK_PCHI2;   //!
   TBranch        *b_Kmi_TRACK_MatchCHI2;   //!
   TBranch        *b_Kmi_TRACK_GhostProb;   //!
   TBranch        *b_Kmi_TRACK_CloneDist;   //!
   TBranch        *b_Kmi_TRACK_Likelihood;   //!
   TBranch        *b_Kpl_MC12TuneV2_ProbNNe;   //!
   TBranch        *b_Kpl_MC12TuneV2_ProbNNmu;   //!
   TBranch        *b_Kpl_MC12TuneV2_ProbNNpi;   //!
   TBranch        *b_Kpl_MC12TuneV2_ProbNNk;   //!
   TBranch        *b_Kpl_MC12TuneV2_ProbNNp;   //!
   TBranch        *b_Kpl_MC12TuneV2_ProbNNghost;   //!
   TBranch        *b_Kpl_MC12TuneV3_ProbNNe;   //!
   TBranch        *b_Kpl_MC12TuneV3_ProbNNmu;   //!
   TBranch        *b_Kpl_MC12TuneV3_ProbNNpi;   //!
   TBranch        *b_Kpl_MC12TuneV3_ProbNNk;   //!
   TBranch        *b_Kpl_MC12TuneV3_ProbNNp;   //!
   TBranch        *b_Kpl_MC12TuneV3_ProbNNghost;   //!
   TBranch        *b_Kpl_MINIP;   //!
   TBranch        *b_Kpl_MINIPCHI2;   //!
   TBranch        *b_Kpl_MINIPNEXTBEST;   //!
   TBranch        *b_Kpl_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_Kpl_OWNPV_X;   //!
   TBranch        *b_Kpl_OWNPV_Y;   //!
   TBranch        *b_Kpl_OWNPV_Z;   //!
   TBranch        *b_Kpl_OWNPV_XERR;   //!
   TBranch        *b_Kpl_OWNPV_YERR;   //!
   TBranch        *b_Kpl_OWNPV_ZERR;   //!
   TBranch        *b_Kpl_OWNPV_CHI2;   //!
   TBranch        *b_Kpl_OWNPV_NDOF;   //!
   TBranch        *b_Kpl_OWNPV_COV_;   //!
   TBranch        *b_Kpl_IP_OWNPV;   //!
   TBranch        *b_Kpl_IPCHI2_OWNPV;   //!
   TBranch        *b_Kpl_TOPPV_X;   //!
   TBranch        *b_Kpl_TOPPV_Y;   //!
   TBranch        *b_Kpl_TOPPV_Z;   //!
   TBranch        *b_Kpl_TOPPV_XERR;   //!
   TBranch        *b_Kpl_TOPPV_YERR;   //!
   TBranch        *b_Kpl_TOPPV_ZERR;   //!
   TBranch        *b_Kpl_TOPPV_CHI2;   //!
   TBranch        *b_Kpl_TOPPV_NDOF;   //!
   TBranch        *b_Kpl_TOPPV_COV_;   //!
   TBranch        *b_Kpl_IP_TOPPV;   //!
   TBranch        *b_Kpl_IPCHI2_TOPPV;   //!
   TBranch        *b_Kpl_ORIVX_X;   //!
   TBranch        *b_Kpl_ORIVX_Y;   //!
   TBranch        *b_Kpl_ORIVX_Z;   //!
   TBranch        *b_Kpl_ORIVX_XERR;   //!
   TBranch        *b_Kpl_ORIVX_YERR;   //!
   TBranch        *b_Kpl_ORIVX_ZERR;   //!
   TBranch        *b_Kpl_ORIVX_CHI2;   //!
   TBranch        *b_Kpl_ORIVX_NDOF;   //!
   TBranch        *b_Kpl_ORIVX_COV_;   //!
   TBranch        *b_Kpl_IP_ORIVX;   //!
   TBranch        *b_Kpl_IPCHI2_ORIVX;   //!
   TBranch        *b_Kpl_P;   //!
   TBranch        *b_Kpl_PT;   //!
   TBranch        *b_Kpl_PE;   //!
   TBranch        *b_Kpl_PX;   //!
   TBranch        *b_Kpl_PY;   //!
   TBranch        *b_Kpl_PZ;   //!
   TBranch        *b_Kpl_M;   //!
   TBranch        *b_Kpl_ID;   //!
   TBranch        *b_Kpl_eta;   //!
   TBranch        *b_Kpl_phi;   //!
   TBranch        *b_Kpl_PIDe;   //!
   TBranch        *b_Kpl_PIDmu;   //!
   TBranch        *b_Kpl_PIDK;   //!
   TBranch        *b_Kpl_PIDp;   //!
   TBranch        *b_Kpl_ProbNNe;   //!
   TBranch        *b_Kpl_ProbNNk;   //!
   TBranch        *b_Kpl_ProbNNp;   //!
   TBranch        *b_Kpl_ProbNNpi;   //!
   TBranch        *b_Kpl_ProbNNmu;   //!
   TBranch        *b_Kpl_ProbNNghost;   //!
   TBranch        *b_Kpl_hasMuon;   //!
   TBranch        *b_Kpl_isMuon;   //!
   TBranch        *b_Kpl_hasRich;   //!
   TBranch        *b_Kpl_hasCalo;   //!
   TBranch        *b_Kpl_SV_X;   //!
   TBranch        *b_Kpl_SV_Y;   //!
   TBranch        *b_Kpl_SV_Z;   //!
   TBranch        *b_Kpl_SV_XERR;   //!
   TBranch        *b_Kpl_SV_YERR;   //!
   TBranch        *b_Kpl_SV_ZERR;   //!
   TBranch        *b_Kpl_SV_CHI2;   //!
   TBranch        *b_Kpl_SV_NDOF;   //!
   TBranch        *b_Kpl_SV_COV_;   //!
   TBranch        *b_Kpl_PV_X;   //!
   TBranch        *b_Kpl_PV_Y;   //!
   TBranch        *b_Kpl_PV_Z;   //!
   TBranch        *b_Kpl_PV_CHI2;   //!
   TBranch        *b_Kpl_PV_NDOF;   //!
   TBranch        *b_Kpl_PV_COV_;   //!
   TBranch        *b_Kpl_MOM_COV_;   //!
   TBranch        *b_Kpl_POSMOM_COV_;   //!
   TBranch        *b_Kpl_MCORR;   //!
   TBranch        *b_Kpl_MCORRERR;   //!
   TBranch        *b_Kpl_MCORRFULLERR;   //!
   TBranch        *b_Kpl_Q2SOL1;   //!
   TBranch        *b_Kpl_Q2SOL2;   //!
   TBranch        *b_Kpl_TRACK_Type;   //!
   TBranch        *b_Kpl_TRACK_Key;   //!
   TBranch        *b_Kpl_TRACK_CHI2NDOF;   //!
   TBranch        *b_Kpl_TRACK_PCHI2;   //!
   TBranch        *b_Kpl_TRACK_MatchCHI2;   //!
   TBranch        *b_Kpl_TRACK_GhostProb;   //!
   TBranch        *b_Kpl_TRACK_CloneDist;   //!
   TBranch        *b_Kpl_TRACK_Likelihood;   //!
   TBranch        *b_pi_MC12TuneV2_ProbNNe;   //!
   TBranch        *b_pi_MC12TuneV2_ProbNNmu;   //!
   TBranch        *b_pi_MC12TuneV2_ProbNNpi;   //!
   TBranch        *b_pi_MC12TuneV2_ProbNNk;   //!
   TBranch        *b_pi_MC12TuneV2_ProbNNp;   //!
   TBranch        *b_pi_MC12TuneV2_ProbNNghost;   //!
   TBranch        *b_pi_MC12TuneV3_ProbNNe;   //!
   TBranch        *b_pi_MC12TuneV3_ProbNNmu;   //!
   TBranch        *b_pi_MC12TuneV3_ProbNNpi;   //!
   TBranch        *b_pi_MC12TuneV3_ProbNNk;   //!
   TBranch        *b_pi_MC12TuneV3_ProbNNp;   //!
   TBranch        *b_pi_MC12TuneV3_ProbNNghost;   //!
   TBranch        *b_pi_MINIP;   //!
   TBranch        *b_pi_MINIPCHI2;   //!
   TBranch        *b_pi_MINIPNEXTBEST;   //!
   TBranch        *b_pi_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_pi_OWNPV_X;   //!
   TBranch        *b_pi_OWNPV_Y;   //!
   TBranch        *b_pi_OWNPV_Z;   //!
   TBranch        *b_pi_OWNPV_XERR;   //!
   TBranch        *b_pi_OWNPV_YERR;   //!
   TBranch        *b_pi_OWNPV_ZERR;   //!
   TBranch        *b_pi_OWNPV_CHI2;   //!
   TBranch        *b_pi_OWNPV_NDOF;   //!
   TBranch        *b_pi_OWNPV_COV_;   //!
   TBranch        *b_pi_IP_OWNPV;   //!
   TBranch        *b_pi_IPCHI2_OWNPV;   //!
   TBranch        *b_pi_TOPPV_X;   //!
   TBranch        *b_pi_TOPPV_Y;   //!
   TBranch        *b_pi_TOPPV_Z;   //!
   TBranch        *b_pi_TOPPV_XERR;   //!
   TBranch        *b_pi_TOPPV_YERR;   //!
   TBranch        *b_pi_TOPPV_ZERR;   //!
   TBranch        *b_pi_TOPPV_CHI2;   //!
   TBranch        *b_pi_TOPPV_NDOF;   //!
   TBranch        *b_pi_TOPPV_COV_;   //!
   TBranch        *b_pi_IP_TOPPV;   //!
   TBranch        *b_pi_IPCHI2_TOPPV;   //!
   TBranch        *b_pi_ORIVX_X;   //!
   TBranch        *b_pi_ORIVX_Y;   //!
   TBranch        *b_pi_ORIVX_Z;   //!
   TBranch        *b_pi_ORIVX_XERR;   //!
   TBranch        *b_pi_ORIVX_YERR;   //!
   TBranch        *b_pi_ORIVX_ZERR;   //!
   TBranch        *b_pi_ORIVX_CHI2;   //!
   TBranch        *b_pi_ORIVX_NDOF;   //!
   TBranch        *b_pi_ORIVX_COV_;   //!
   TBranch        *b_pi_IP_ORIVX;   //!
   TBranch        *b_pi_IPCHI2_ORIVX;   //!
   TBranch        *b_pi_P;   //!
   TBranch        *b_pi_PT;   //!
   TBranch        *b_pi_PE;   //!
   TBranch        *b_pi_PX;   //!
   TBranch        *b_pi_PY;   //!
   TBranch        *b_pi_PZ;   //!
   TBranch        *b_pi_M;   //!
   TBranch        *b_pi_ID;   //!
   TBranch        *b_pi_eta;   //!
   TBranch        *b_pi_phi;   //!
   TBranch        *b_pi_PIDe;   //!
   TBranch        *b_pi_PIDmu;   //!
   TBranch        *b_pi_PIDK;   //!
   TBranch        *b_pi_PIDp;   //!
   TBranch        *b_pi_ProbNNe;   //!
   TBranch        *b_pi_ProbNNk;   //!
   TBranch        *b_pi_ProbNNp;   //!
   TBranch        *b_pi_ProbNNpi;   //!
   TBranch        *b_pi_ProbNNmu;   //!
   TBranch        *b_pi_ProbNNghost;   //!
   TBranch        *b_pi_hasMuon;   //!
   TBranch        *b_pi_isMuon;   //!
   TBranch        *b_pi_hasRich;   //!
   TBranch        *b_pi_hasCalo;   //!
   TBranch        *b_pi_SV_X;   //!
   TBranch        *b_pi_SV_Y;   //!
   TBranch        *b_pi_SV_Z;   //!
   TBranch        *b_pi_SV_XERR;   //!
   TBranch        *b_pi_SV_YERR;   //!
   TBranch        *b_pi_SV_ZERR;   //!
   TBranch        *b_pi_SV_CHI2;   //!
   TBranch        *b_pi_SV_NDOF;   //!
   TBranch        *b_pi_SV_COV_;   //!
   TBranch        *b_pi_PV_X;   //!
   TBranch        *b_pi_PV_Y;   //!
   TBranch        *b_pi_PV_Z;   //!
   TBranch        *b_pi_PV_CHI2;   //!
   TBranch        *b_pi_PV_NDOF;   //!
   TBranch        *b_pi_PV_COV_;   //!
   TBranch        *b_pi_MOM_COV_;   //!
   TBranch        *b_pi_POSMOM_COV_;   //!
   TBranch        *b_pi_MCORR;   //!
   TBranch        *b_pi_MCORRERR;   //!
   TBranch        *b_pi_MCORRFULLERR;   //!
   TBranch        *b_pi_Q2SOL1;   //!
   TBranch        *b_pi_Q2SOL2;   //!
   TBranch        *b_pi_TRACK_Type;   //!
   TBranch        *b_pi_TRACK_Key;   //!
   TBranch        *b_pi_TRACK_CHI2NDOF;   //!
   TBranch        *b_pi_TRACK_PCHI2;   //!
   TBranch        *b_pi_TRACK_MatchCHI2;   //!
   TBranch        *b_pi_TRACK_GhostProb;   //!
   TBranch        *b_pi_TRACK_CloneDist;   //!
   TBranch        *b_pi_TRACK_Likelihood;   //!
   TBranch        *b_mu_MC12TuneV2_ProbNNe;   //!
   TBranch        *b_mu_MC12TuneV2_ProbNNmu;   //!
   TBranch        *b_mu_MC12TuneV2_ProbNNpi;   //!
   TBranch        *b_mu_MC12TuneV2_ProbNNk;   //!
   TBranch        *b_mu_MC12TuneV2_ProbNNp;   //!
   TBranch        *b_mu_MC12TuneV2_ProbNNghost;   //!
   TBranch        *b_mu_MC12TuneV3_ProbNNe;   //!
   TBranch        *b_mu_MC12TuneV3_ProbNNmu;   //!
   TBranch        *b_mu_MC12TuneV3_ProbNNpi;   //!
   TBranch        *b_mu_MC12TuneV3_ProbNNk;   //!
   TBranch        *b_mu_MC12TuneV3_ProbNNp;   //!
   TBranch        *b_mu_MC12TuneV3_ProbNNghost;   //!
   TBranch        *b_mu_0_00_cc_mult;   //!
   TBranch        *b_mu_0_00_cc_PX;   //!
   TBranch        *b_mu_0_00_cc_PY;   //!
   TBranch        *b_mu_0_00_cc_PZ;   //!
   TBranch        *b_mu_0_00_cc_vPT;   //!
   TBranch        *b_mu_0_00_cc_sPT;   //!
   TBranch        *b_mu_0_00_cc_maxPt_Q;   //!
   TBranch        *b_mu_0_00_cc_maxPt_PT;   //!
   TBranch        *b_mu_0_00_cc_maxPt_PX;   //!
   TBranch        *b_mu_0_00_cc_maxPt_PY;   //!
   TBranch        *b_mu_0_00_cc_maxPt_PZ;   //!
   TBranch        *b_mu_0_00_cc_maxPt_PE;   //!
   TBranch        *b_mu_0_00_nc_mult;   //!
   TBranch        *b_mu_0_00_nc_PX;   //!
   TBranch        *b_mu_0_00_nc_PY;   //!
   TBranch        *b_mu_0_00_nc_PZ;   //!
   TBranch        *b_mu_0_00_nc_vPT;   //!
   TBranch        *b_mu_0_00_nc_sPT;   //!
   TBranch        *b_mu_0_00_nc_maxPt_PT;   //!
   TBranch        *b_mu_0_00_nc_maxPt_PX;   //!
   TBranch        *b_mu_0_00_nc_maxPt_PY;   //!
   TBranch        *b_mu_0_00_nc_maxPt_PZ;   //!
   TBranch        *b_mu_1_50_cc_mult;   //!
   TBranch        *b_mu_1_50_cc_PX;   //!
   TBranch        *b_mu_1_50_cc_PY;   //!
   TBranch        *b_mu_1_50_cc_PZ;   //!
   TBranch        *b_mu_1_50_cc_vPT;   //!
   TBranch        *b_mu_1_50_cc_sPT;   //!
   TBranch        *b_mu_1_50_nc_mult;   //!
   TBranch        *b_mu_1_50_nc_PX;   //!
   TBranch        *b_mu_1_50_nc_PY;   //!
   TBranch        *b_mu_1_50_nc_PZ;   //!
   TBranch        *b_mu_1_50_nc_vPT;   //!
   TBranch        *b_mu_1_50_nc_sPT;   //!
   TBranch        *b_mu_1_20_cc_mult;   //!
   TBranch        *b_mu_1_20_cc_PX;   //!
   TBranch        *b_mu_1_20_cc_PY;   //!
   TBranch        *b_mu_1_20_cc_PZ;   //!
   TBranch        *b_mu_1_20_cc_vPT;   //!
   TBranch        *b_mu_1_20_cc_sPT;   //!
   TBranch        *b_mu_1_20_nc_mult;   //!
   TBranch        *b_mu_1_20_nc_PX;   //!
   TBranch        *b_mu_1_20_nc_PY;   //!
   TBranch        *b_mu_1_20_nc_PZ;   //!
   TBranch        *b_mu_1_20_nc_vPT;   //!
   TBranch        *b_mu_1_20_nc_sPT;   //!
   TBranch        *b_mu_0_90_cc_mult;   //!
   TBranch        *b_mu_0_90_cc_PX;   //!
   TBranch        *b_mu_0_90_cc_PY;   //!
   TBranch        *b_mu_0_90_cc_PZ;   //!
   TBranch        *b_mu_0_90_cc_vPT;   //!
   TBranch        *b_mu_0_90_cc_sPT;   //!
   TBranch        *b_mu_0_90_nc_mult;   //!
   TBranch        *b_mu_0_90_nc_PX;   //!
   TBranch        *b_mu_0_90_nc_PY;   //!
   TBranch        *b_mu_0_90_nc_PZ;   //!
   TBranch        *b_mu_0_90_nc_vPT;   //!
   TBranch        *b_mu_0_90_nc_sPT;   //!
   TBranch        *b_mu_0_60_cc_mult;   //!
   TBranch        *b_mu_0_60_cc_PX;   //!
   TBranch        *b_mu_0_60_cc_PY;   //!
   TBranch        *b_mu_0_60_cc_PZ;   //!
   TBranch        *b_mu_0_60_cc_vPT;   //!
   TBranch        *b_mu_0_60_cc_sPT;   //!
   TBranch        *b_mu_0_60_nc_mult;   //!
   TBranch        *b_mu_0_60_nc_PX;   //!
   TBranch        *b_mu_0_60_nc_PY;   //!
   TBranch        *b_mu_0_60_nc_PZ;   //!
   TBranch        *b_mu_0_60_nc_vPT;   //!
   TBranch        *b_mu_0_60_nc_sPT;   //!
   TBranch        *b_mu_0_30_cc_mult;   //!
   TBranch        *b_mu_0_30_cc_PX;   //!
   TBranch        *b_mu_0_30_cc_PY;   //!
   TBranch        *b_mu_0_30_cc_PZ;   //!
   TBranch        *b_mu_0_30_cc_vPT;   //!
   TBranch        *b_mu_0_30_cc_sPT;   //!
   TBranch        *b_mu_0_30_nc_mult;   //!
   TBranch        *b_mu_0_30_nc_PX;   //!
   TBranch        *b_mu_0_30_nc_PY;   //!
   TBranch        *b_mu_0_30_nc_PZ;   //!
   TBranch        *b_mu_0_30_nc_vPT;   //!
   TBranch        *b_mu_0_30_nc_sPT;   //!
   TBranch        *b_mu_MINIP;   //!
   TBranch        *b_mu_MINIPCHI2;   //!
   TBranch        *b_mu_MINIPNEXTBEST;   //!
   TBranch        *b_mu_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_mu_OWNPV_X;   //!
   TBranch        *b_mu_OWNPV_Y;   //!
   TBranch        *b_mu_OWNPV_Z;   //!
   TBranch        *b_mu_OWNPV_XERR;   //!
   TBranch        *b_mu_OWNPV_YERR;   //!
   TBranch        *b_mu_OWNPV_ZERR;   //!
   TBranch        *b_mu_OWNPV_CHI2;   //!
   TBranch        *b_mu_OWNPV_NDOF;   //!
   TBranch        *b_mu_OWNPV_COV_;   //!
   TBranch        *b_mu_IP_OWNPV;   //!
   TBranch        *b_mu_IPCHI2_OWNPV;   //!
   TBranch        *b_mu_TOPPV_X;   //!
   TBranch        *b_mu_TOPPV_Y;   //!
   TBranch        *b_mu_TOPPV_Z;   //!
   TBranch        *b_mu_TOPPV_XERR;   //!
   TBranch        *b_mu_TOPPV_YERR;   //!
   TBranch        *b_mu_TOPPV_ZERR;   //!
   TBranch        *b_mu_TOPPV_CHI2;   //!
   TBranch        *b_mu_TOPPV_NDOF;   //!
   TBranch        *b_mu_TOPPV_COV_;   //!
   TBranch        *b_mu_IP_TOPPV;   //!
   TBranch        *b_mu_IPCHI2_TOPPV;   //!
   TBranch        *b_mu_ORIVX_X;   //!
   TBranch        *b_mu_ORIVX_Y;   //!
   TBranch        *b_mu_ORIVX_Z;   //!
   TBranch        *b_mu_ORIVX_XERR;   //!
   TBranch        *b_mu_ORIVX_YERR;   //!
   TBranch        *b_mu_ORIVX_ZERR;   //!
   TBranch        *b_mu_ORIVX_CHI2;   //!
   TBranch        *b_mu_ORIVX_NDOF;   //!
   TBranch        *b_mu_ORIVX_COV_;   //!
   TBranch        *b_mu_IP_ORIVX;   //!
   TBranch        *b_mu_IPCHI2_ORIVX;   //!
   TBranch        *b_mu_P;   //!
   TBranch        *b_mu_PT;   //!
   TBranch        *b_mu_PE;   //!
   TBranch        *b_mu_PX;   //!
   TBranch        *b_mu_PY;   //!
   TBranch        *b_mu_PZ;   //!
   TBranch        *b_mu_M;   //!
   TBranch        *b_mu_ID;   //!
   TBranch        *b_mu_nVeloIDs;   //!
   TBranch        *b_mu_nITIDs;   //!
   TBranch        *b_mu_nTTIDs;   //!
   TBranch        *b_mu_nOTIDs;   //!
   TBranch        *b_mu_eta;   //!
   TBranch        *b_mu_phi;   //!
   TBranch        *b_mu_PIDe;   //!
   TBranch        *b_mu_PIDmu;   //!
   TBranch        *b_mu_PIDK;   //!
   TBranch        *b_mu_PIDp;   //!
   TBranch        *b_mu_ProbNNe;   //!
   TBranch        *b_mu_ProbNNk;   //!
   TBranch        *b_mu_ProbNNp;   //!
   TBranch        *b_mu_ProbNNpi;   //!
   TBranch        *b_mu_ProbNNmu;   //!
   TBranch        *b_mu_ProbNNghost;   //!
   TBranch        *b_mu_hasMuon;   //!
   TBranch        *b_mu_isMuon;   //!
   TBranch        *b_mu_hasRich;   //!
   TBranch        *b_mu_hasCalo;   //!
   TBranch        *b_mu_SV_X;   //!
   TBranch        *b_mu_SV_Y;   //!
   TBranch        *b_mu_SV_Z;   //!
   TBranch        *b_mu_SV_XERR;   //!
   TBranch        *b_mu_SV_YERR;   //!
   TBranch        *b_mu_SV_ZERR;   //!
   TBranch        *b_mu_SV_CHI2;   //!
   TBranch        *b_mu_SV_NDOF;   //!
   TBranch        *b_mu_SV_COV_;   //!
   TBranch        *b_mu_PV_X;   //!
   TBranch        *b_mu_PV_Y;   //!
   TBranch        *b_mu_PV_Z;   //!
   TBranch        *b_mu_PV_CHI2;   //!
   TBranch        *b_mu_PV_NDOF;   //!
   TBranch        *b_mu_PV_COV_;   //!
   TBranch        *b_mu_MOM_COV_;   //!
   TBranch        *b_mu_POSMOM_COV_;   //!
   TBranch        *b_mu_MCORR;   //!
   TBranch        *b_mu_MCORRERR;   //!
   TBranch        *b_mu_MCORRFULLERR;   //!
   TBranch        *b_mu_Q2SOL1;   //!
   TBranch        *b_mu_Q2SOL2;   //!
   TBranch        *b_mu_L0Global_Dec;   //!
   TBranch        *b_mu_L0Global_TIS;   //!
   TBranch        *b_mu_L0Global_TOS;   //!
   TBranch        *b_mu_Hlt1Global_Dec;   //!
   TBranch        *b_mu_Hlt1Global_TIS;   //!
   TBranch        *b_mu_Hlt1Global_TOS;   //!
   TBranch        *b_mu_Hlt1Phys_Dec;   //!
   TBranch        *b_mu_Hlt1Phys_TIS;   //!
   TBranch        *b_mu_Hlt1Phys_TOS;   //!
   TBranch        *b_mu_Hlt2Global_Dec;   //!
   TBranch        *b_mu_Hlt2Global_TIS;   //!
   TBranch        *b_mu_Hlt2Global_TOS;   //!
   TBranch        *b_mu_Hlt2Phys_Dec;   //!
   TBranch        *b_mu_Hlt2Phys_TIS;   //!
   TBranch        *b_mu_Hlt2Phys_TOS;   //!
   TBranch        *b_mu_L0MuonDecision_Dec;   //!
   TBranch        *b_mu_L0MuonDecision_TIS;   //!
   TBranch        *b_mu_L0MuonDecision_TOS;   //!
   TBranch        *b_mu_L0DiMuonDecision_Dec;   //!
   TBranch        *b_mu_L0DiMuonDecision_TIS;   //!
   TBranch        *b_mu_L0DiMuonDecision_TOS;   //!
   TBranch        *b_mu_L0HadronDecision_Dec;   //!
   TBranch        *b_mu_L0HadronDecision_TIS;   //!
   TBranch        *b_mu_L0HadronDecision_TOS;   //!
   TBranch        *b_mu_L0ElectronDecision_Dec;   //!
   TBranch        *b_mu_L0ElectronDecision_TIS;   //!
   TBranch        *b_mu_L0ElectronDecision_TOS;   //!
   TBranch        *b_mu_L0ElectronHiDecision_Dec;   //!
   TBranch        *b_mu_L0ElectronHiDecision_TIS;   //!
   TBranch        *b_mu_L0ElectronHiDecision_TOS;   //!
   TBranch        *b_mu_L0PhotonDecision_Dec;   //!
   TBranch        *b_mu_L0PhotonDecision_TIS;   //!
   TBranch        *b_mu_L0PhotonDecision_TOS;   //!
   TBranch        *b_mu_L0PhotonHiDecision_Dec;   //!
   TBranch        *b_mu_L0PhotonHiDecision_TIS;   //!
   TBranch        *b_mu_L0PhotonHiDecision_TOS;   //!
   TBranch        *b_mu_Hlt1SingleMuonNoIPDecision_Dec;   //!
   TBranch        *b_mu_Hlt1SingleMuonNoIPDecision_TIS;   //!
   TBranch        *b_mu_Hlt1SingleMuonNoIPDecision_TOS;   //!
   TBranch        *b_mu_Hlt1SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_mu_Hlt1SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_mu_Hlt1SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_mu_Hlt1SingleElectronNoIPDecision_Dec;   //!
   TBranch        *b_mu_Hlt1SingleElectronNoIPDecision_TIS;   //!
   TBranch        *b_mu_Hlt1SingleElectronNoIPDecision_TOS;   //!
   TBranch        *b_mu_Hlt1TrackAllL0Decision_Dec;   //!
   TBranch        *b_mu_Hlt1TrackAllL0Decision_TIS;   //!
   TBranch        *b_mu_Hlt1TrackAllL0Decision_TOS;   //!
   TBranch        *b_mu_Hlt1TrackMuonDecision_Dec;   //!
   TBranch        *b_mu_Hlt1TrackMuonDecision_TIS;   //!
   TBranch        *b_mu_Hlt1TrackMuonDecision_TOS;   //!
   TBranch        *b_mu_Hlt1TrackPhotonDecision_Dec;   //!
   TBranch        *b_mu_Hlt1TrackPhotonDecision_TIS;   //!
   TBranch        *b_mu_Hlt1TrackPhotonDecision_TOS;   //!
   TBranch        *b_mu_Hlt1TrackAllL0__Decision_Dec;   //!
   TBranch        *b_mu_Hlt1TrackAllL0__Decision_TIS;   //!
   TBranch        *b_mu_Hlt1TrackAllL0__Decision_TOS;   //!
   TBranch        *b_mu_Hlt1DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_mu_Hlt1DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_mu_Hlt1DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_mu_Hlt1DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_mu_Hlt1DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_mu_Hlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_mu_Hlt1MB__Decision_Dec;   //!
   TBranch        *b_mu_Hlt1MB__Decision_TIS;   //!
   TBranch        *b_mu_Hlt1MB__Decision_TOS;   //!
   TBranch        *b_mu_Hlt1TrackAllL0TightDecision_Dec;   //!
   TBranch        *b_mu_Hlt1TrackAllL0TightDecision_TIS;   //!
   TBranch        *b_mu_Hlt1TrackAllL0TightDecision_TOS;   //!
   TBranch        *b_mu_Hlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_mu_Hlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_mu_Hlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_mu_Hlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_mu_Hlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_mu_Hlt2SingleMuonLowPTDecision_TOS;   //!
   TBranch        *b_mu_Hlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_mu_Hlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_mu_Hlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_mu_Hlt2DiMuonDecision_Dec;   //!
   TBranch        *b_mu_Hlt2DiMuonDecision_TIS;   //!
   TBranch        *b_mu_Hlt2DiMuonDecision_TOS;   //!
   TBranch        *b_mu_Hlt2DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_mu_Hlt2DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_mu_Hlt2DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_mu_Hlt2DiMuonJPsiHighPTDecision_Dec;   //!
   TBranch        *b_mu_Hlt2DiMuonJPsiHighPTDecision_TIS;   //!
   TBranch        *b_mu_Hlt2DiMuonJPsiHighPTDecision_TOS;   //!
   TBranch        *b_mu_Hlt2DiMuonPsi2SDecision_Dec;   //!
   TBranch        *b_mu_Hlt2DiMuonPsi2SDecision_TIS;   //!
   TBranch        *b_mu_Hlt2DiMuonPsi2SDecision_TOS;   //!
   TBranch        *b_mu_Hlt2DiMuonDetachedDecision_Dec;   //!
   TBranch        *b_mu_Hlt2DiMuonDetachedDecision_TIS;   //!
   TBranch        *b_mu_Hlt2DiMuonDetachedDecision_TOS;   //!
   TBranch        *b_mu_Hlt2DiMuonDetachedJPsiDecision_Dec;   //!
   TBranch        *b_mu_Hlt2DiMuonDetachedJPsiDecision_TIS;   //!
   TBranch        *b_mu_Hlt2DiMuonDetachedJPsiDecision_TOS;   //!
   TBranch        *b_mu_Hlt2DiMuonDetachedHeavyDecision_Dec;   //!
   TBranch        *b_mu_Hlt2DiMuonDetachedHeavyDecision_TIS;   //!
   TBranch        *b_mu_Hlt2DiMuonDetachedHeavyDecision_TOS;   //!
   TBranch        *b_mu_Hlt2TriMuonTauDecision_Dec;   //!
   TBranch        *b_mu_Hlt2TriMuonTauDecision_TIS;   //!
   TBranch        *b_mu_Hlt2TriMuonTauDecision_TOS;   //!
   TBranch        *b_mu_Hlt2B2HHDecision_Dec;   //!
   TBranch        *b_mu_Hlt2B2HHDecision_TIS;   //!
   TBranch        *b_mu_Hlt2B2HHDecision_TOS;   //!
   TBranch        *b_mu_Hlt2DiMuonBDecision_Dec;   //!
   TBranch        *b_mu_Hlt2DiMuonBDecision_TIS;   //!
   TBranch        *b_mu_Hlt2DiMuonBDecision_TOS;   //!
   TBranch        *b_mu_Hlt2DiMuonZDecision_Dec;   //!
   TBranch        *b_mu_Hlt2DiMuonZDecision_TIS;   //!
   TBranch        *b_mu_Hlt2DiMuonZDecision_TOS;   //!
   TBranch        *b_mu_Hlt2TopoMu2BodyBBDTDecision_Dec;   //!
   TBranch        *b_mu_Hlt2TopoMu2BodyBBDTDecision_TIS;   //!
   TBranch        *b_mu_Hlt2TopoMu2BodyBBDTDecision_TOS;   //!
   TBranch        *b_mu_Hlt2TopoMu3BodyBBDTDecision_Dec;   //!
   TBranch        *b_mu_Hlt2TopoMu3BodyBBDTDecision_TIS;   //!
   TBranch        *b_mu_Hlt2TopoMu3BodyBBDTDecision_TOS;   //!
   TBranch        *b_mu_Hlt2TopoMu4BodyBBDTDecision_Dec;   //!
   TBranch        *b_mu_Hlt2TopoMu4BodyBBDTDecision_TIS;   //!
   TBranch        *b_mu_Hlt2TopoMu4BodyBBDTDecision_TOS;   //!
   TBranch        *b_mu_Hlt2Topo2BodyBBDTDecision_Dec;   //!
   TBranch        *b_mu_Hlt2Topo2BodyBBDTDecision_TIS;   //!
   TBranch        *b_mu_Hlt2Topo2BodyBBDTDecision_TOS;   //!
   TBranch        *b_mu_Hlt2Topo3BodyBBDTDecision_Dec;   //!
   TBranch        *b_mu_Hlt2Topo3BodyBBDTDecision_TIS;   //!
   TBranch        *b_mu_Hlt2Topo3BodyBBDTDecision_TOS;   //!
   TBranch        *b_mu_Hlt2Topo4BodyBBDTDecision_Dec;   //!
   TBranch        *b_mu_Hlt2Topo4BodyBBDTDecision_TIS;   //!
   TBranch        *b_mu_Hlt2Topo4BodyBBDTDecision_TOS;   //!
   TBranch        *b_mu_Hlt2Topo2BodySimpleDecision_Dec;   //!
   TBranch        *b_mu_Hlt2Topo2BodySimpleDecision_TIS;   //!
   TBranch        *b_mu_Hlt2Topo2BodySimpleDecision_TOS;   //!
   TBranch        *b_mu_Hlt2Topo3BodySimpleDecision_Dec;   //!
   TBranch        *b_mu_Hlt2Topo3BodySimpleDecision_TIS;   //!
   TBranch        *b_mu_Hlt2Topo3BodySimpleDecision_TOS;   //!
   TBranch        *b_mu_Hlt2Topo4BodySimpleDecision_Dec;   //!
   TBranch        *b_mu_Hlt2Topo4BodySimpleDecision_TIS;   //!
   TBranch        *b_mu_Hlt2Topo4BodySimpleDecision_TOS;   //!
   TBranch        *b_mu_Hlt2PassThroughDecision_Dec;   //!
   TBranch        *b_mu_Hlt2PassThroughDecision_TIS;   //!
   TBranch        *b_mu_Hlt2PassThroughDecision_TOS;   //!
   TBranch        *b_mu_Hlt2TransparentDecision_Dec;   //!
   TBranch        *b_mu_Hlt2TransparentDecision_TIS;   //!
   TBranch        *b_mu_Hlt2TransparentDecision_TOS;   //!
   TBranch        *b_mu_Hlt2IncPhiDecision_Dec;   //!
   TBranch        *b_mu_Hlt2IncPhiDecision_TIS;   //!
   TBranch        *b_mu_Hlt2IncPhiDecision_TOS;   //!
   TBranch        *b_mu_Hlt2DiMuonDY__Decision_Dec;   //!
   TBranch        *b_mu_Hlt2DiMuonDY__Decision_TIS;   //!
   TBranch        *b_mu_Hlt2DiMuonDY__Decision_TOS;   //!
   TBranch        *b_mu_Hlt2TopoE__Decision_Dec;   //!
   TBranch        *b_mu_Hlt2TopoE__Decision_TIS;   //!
   TBranch        *b_mu_Hlt2TopoE__Decision_TOS;   //!
   TBranch        *b_mu_Hlt2Topo__Decision_Dec;   //!
   TBranch        *b_mu_Hlt2Topo__Decision_TIS;   //!
   TBranch        *b_mu_Hlt2Topo__Decision_TOS;   //!
   TBranch        *b_mu_Hlt2Charm__Decision_Dec;   //!
   TBranch        *b_mu_Hlt2Charm__Decision_TIS;   //!
   TBranch        *b_mu_Hlt2Charm__Decision_TOS;   //!
   TBranch        *b_mu_Hlt2DiElectron__Decision_Dec;   //!
   TBranch        *b_mu_Hlt2DiElectron__Decision_TIS;   //!
   TBranch        *b_mu_Hlt2DiElectron__Decision_TOS;   //!
   TBranch        *b_mu_Hlt2__GammaDecision_Dec;   //!
   TBranch        *b_mu_Hlt2__GammaDecision_TIS;   //!
   TBranch        *b_mu_Hlt2__GammaDecision_TOS;   //!
   TBranch        *b_mu_TRACK_Type;   //!
   TBranch        *b_mu_TRACK_Key;   //!
   TBranch        *b_mu_TRACK_CHI2NDOF;   //!
   TBranch        *b_mu_TRACK_PCHI2;   //!
   TBranch        *b_mu_TRACK_MatchCHI2;   //!
   TBranch        *b_mu_TRACK_GhostProb;   //!
   TBranch        *b_mu_TRACK_CloneDist;   //!
   TBranch        *b_mu_TRACK_Likelihood;   //!
   TBranch        *b_nCandidate;   //!
   TBranch        *b_totCandidates;   //!
   TBranch        *b_EventInSequence;   //!
   TBranch        *b_nVeloTraks_All;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_BCID;   //!
   TBranch        *b_BCType;   //!
   TBranch        *b_OdinTCK;   //!
   TBranch        *b_L0DUTCK;   //!
   TBranch        *b_HLT1TCK;   //!
   TBranch        *b_HLT2TCK;   //!
   TBranch        *b_GpsTime;   //!
   TBranch        *b_Polarity;   //!
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
   TBranch        *b_L0Global;   //!
   TBranch        *b_Hlt1Global;   //!
   TBranch        *b_Hlt2Global;   //!

   NeutralIsoData(TTree *tree=0);
   virtual ~NeutralIsoData();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef NeutralIsoData_cxx
NeutralIsoData::NeutralIsoData(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      //TFile *f = TFile::Open("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/RDS_MCSignal_Sim08aDown.root");
      TFile *f = TFile::Open("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/DataMagUp_S23r1_RDS_FromVubStripping_1.root");
      if (!f || !f->IsOpen()) {
        //f = new TFile("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/RDS_MCSignal_Sim08aDown.root");
        f = new TFile("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/DataMagUp_S23r1_RDS_FromVubStripping_1.root");
      }
      tree = (TTree*)f->Get("B2DsMuNuTuple/DecayTree");

      TChain *chain = new TChain("B2DsMuNuTuple/DecayTree");
      //chain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/RDS_MCSignal_Sim08aDown.root");
      //chain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/RDS_MCSignal_Sim08aUp.root");
      chain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/DataMagUp_S23r1_RDS_FromVubStripping_1.root");
      chain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/DataMagUp_S23r1_RDS_FromVubStripping_2.root");
      chain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/DataMagDown_S23r1_RDS_FromVubStripping_1.root");
      chain->Add("root://eoslhcb.cern.ch//eos/lhcb/user/r/rvazquez/RDS/DataMagDown_S23r1_RDS_FromVubStripping_2.root");
      tree = chain;
   }
   Init(tree);
}

NeutralIsoData::~NeutralIsoData()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t NeutralIsoData::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t NeutralIsoData::LoadTree(Long64_t entry)
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

void NeutralIsoData::Init(TTree *tree)
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

   fChain->SetBranchAddress("Bs_0_MINIP", &Bs_0_MINIP, &b_Bs_0_MINIP);
   fChain->SetBranchAddress("Bs_0_MINIPCHI2", &Bs_0_MINIPCHI2, &b_Bs_0_MINIPCHI2);
   fChain->SetBranchAddress("Bs_0_MINIPNEXTBEST", &Bs_0_MINIPNEXTBEST, &b_Bs_0_MINIPNEXTBEST);
   fChain->SetBranchAddress("Bs_0_MINIPCHI2NEXTBEST", &Bs_0_MINIPCHI2NEXTBEST, &b_Bs_0_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("Bs_0_ENDVERTEX_X", &Bs_0_ENDVERTEX_X, &b_Bs_0_ENDVERTEX_X);
   fChain->SetBranchAddress("Bs_0_ENDVERTEX_Y", &Bs_0_ENDVERTEX_Y, &b_Bs_0_ENDVERTEX_Y);
   fChain->SetBranchAddress("Bs_0_ENDVERTEX_Z", &Bs_0_ENDVERTEX_Z, &b_Bs_0_ENDVERTEX_Z);
   fChain->SetBranchAddress("Bs_0_ENDVERTEX_XERR", &Bs_0_ENDVERTEX_XERR, &b_Bs_0_ENDVERTEX_XERR);
   fChain->SetBranchAddress("Bs_0_ENDVERTEX_YERR", &Bs_0_ENDVERTEX_YERR, &b_Bs_0_ENDVERTEX_YERR);
   fChain->SetBranchAddress("Bs_0_ENDVERTEX_ZERR", &Bs_0_ENDVERTEX_ZERR, &b_Bs_0_ENDVERTEX_ZERR);
   fChain->SetBranchAddress("Bs_0_ENDVERTEX_CHI2", &Bs_0_ENDVERTEX_CHI2, &b_Bs_0_ENDVERTEX_CHI2);
   fChain->SetBranchAddress("Bs_0_ENDVERTEX_NDOF", &Bs_0_ENDVERTEX_NDOF, &b_Bs_0_ENDVERTEX_NDOF);
   fChain->SetBranchAddress("Bs_0_ENDVERTEX_COV_", Bs_0_ENDVERTEX_COV_, &b_Bs_0_ENDVERTEX_COV_);
   fChain->SetBranchAddress("Bs_0_OWNPV_X", &Bs_0_OWNPV_X, &b_Bs_0_OWNPV_X);
   fChain->SetBranchAddress("Bs_0_OWNPV_Y", &Bs_0_OWNPV_Y, &b_Bs_0_OWNPV_Y);
   fChain->SetBranchAddress("Bs_0_OWNPV_Z", &Bs_0_OWNPV_Z, &b_Bs_0_OWNPV_Z);
   fChain->SetBranchAddress("Bs_0_OWNPV_XERR", &Bs_0_OWNPV_XERR, &b_Bs_0_OWNPV_XERR);
   fChain->SetBranchAddress("Bs_0_OWNPV_YERR", &Bs_0_OWNPV_YERR, &b_Bs_0_OWNPV_YERR);
   fChain->SetBranchAddress("Bs_0_OWNPV_ZERR", &Bs_0_OWNPV_ZERR, &b_Bs_0_OWNPV_ZERR);
   fChain->SetBranchAddress("Bs_0_OWNPV_CHI2", &Bs_0_OWNPV_CHI2, &b_Bs_0_OWNPV_CHI2);
   fChain->SetBranchAddress("Bs_0_OWNPV_NDOF", &Bs_0_OWNPV_NDOF, &b_Bs_0_OWNPV_NDOF);
   fChain->SetBranchAddress("Bs_0_OWNPV_COV_", Bs_0_OWNPV_COV_, &b_Bs_0_OWNPV_COV_);
   fChain->SetBranchAddress("Bs_0_IP_OWNPV", &Bs_0_IP_OWNPV, &b_Bs_0_IP_OWNPV);
   fChain->SetBranchAddress("Bs_0_IPCHI2_OWNPV", &Bs_0_IPCHI2_OWNPV, &b_Bs_0_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Bs_0_FD_OWNPV", &Bs_0_FD_OWNPV, &b_Bs_0_FD_OWNPV);
   fChain->SetBranchAddress("Bs_0_FDCHI2_OWNPV", &Bs_0_FDCHI2_OWNPV, &b_Bs_0_FDCHI2_OWNPV);
   fChain->SetBranchAddress("Bs_0_DIRA_OWNPV", &Bs_0_DIRA_OWNPV, &b_Bs_0_DIRA_OWNPV);
   fChain->SetBranchAddress("Bs_0_TOPPV_X", &Bs_0_TOPPV_X, &b_Bs_0_TOPPV_X);
   fChain->SetBranchAddress("Bs_0_TOPPV_Y", &Bs_0_TOPPV_Y, &b_Bs_0_TOPPV_Y);
   fChain->SetBranchAddress("Bs_0_TOPPV_Z", &Bs_0_TOPPV_Z, &b_Bs_0_TOPPV_Z);
   fChain->SetBranchAddress("Bs_0_TOPPV_XERR", &Bs_0_TOPPV_XERR, &b_Bs_0_TOPPV_XERR);
   fChain->SetBranchAddress("Bs_0_TOPPV_YERR", &Bs_0_TOPPV_YERR, &b_Bs_0_TOPPV_YERR);
   fChain->SetBranchAddress("Bs_0_TOPPV_ZERR", &Bs_0_TOPPV_ZERR, &b_Bs_0_TOPPV_ZERR);
   fChain->SetBranchAddress("Bs_0_TOPPV_CHI2", &Bs_0_TOPPV_CHI2, &b_Bs_0_TOPPV_CHI2);
   fChain->SetBranchAddress("Bs_0_TOPPV_NDOF", &Bs_0_TOPPV_NDOF, &b_Bs_0_TOPPV_NDOF);
   fChain->SetBranchAddress("Bs_0_TOPPV_COV_", Bs_0_TOPPV_COV_, &b_Bs_0_TOPPV_COV_);
   fChain->SetBranchAddress("Bs_0_IP_TOPPV", &Bs_0_IP_TOPPV, &b_Bs_0_IP_TOPPV);
   fChain->SetBranchAddress("Bs_0_IPCHI2_TOPPV", &Bs_0_IPCHI2_TOPPV, &b_Bs_0_IPCHI2_TOPPV);
   fChain->SetBranchAddress("Bs_0_FD_TOPPV", &Bs_0_FD_TOPPV, &b_Bs_0_FD_TOPPV);
   fChain->SetBranchAddress("Bs_0_FDCHI2_TOPPV", &Bs_0_FDCHI2_TOPPV, &b_Bs_0_FDCHI2_TOPPV);
   fChain->SetBranchAddress("Bs_0_DIRA_TOPPV", &Bs_0_DIRA_TOPPV, &b_Bs_0_DIRA_TOPPV);
   fChain->SetBranchAddress("Bs_0_P", &Bs_0_P, &b_Bs_0_P);
   fChain->SetBranchAddress("Bs_0_PT", &Bs_0_PT, &b_Bs_0_PT);
   fChain->SetBranchAddress("Bs_0_PE", &Bs_0_PE, &b_Bs_0_PE);
   fChain->SetBranchAddress("Bs_0_PX", &Bs_0_PX, &b_Bs_0_PX);
   fChain->SetBranchAddress("Bs_0_PY", &Bs_0_PY, &b_Bs_0_PY);
   fChain->SetBranchAddress("Bs_0_PZ", &Bs_0_PZ, &b_Bs_0_PZ);
   fChain->SetBranchAddress("Bs_0_MM", &Bs_0_MM, &b_Bs_0_MM);
   fChain->SetBranchAddress("Bs_0_MMERR", &Bs_0_MMERR, &b_Bs_0_MMERR);
   fChain->SetBranchAddress("Bs_0_M", &Bs_0_M, &b_Bs_0_M);
   fChain->SetBranchAddress("Bs_0_ID", &Bs_0_ID, &b_Bs_0_ID);
   fChain->SetBranchAddress("Bs_0_eta", &Bs_0_eta, &b_Bs_0_eta);
   fChain->SetBranchAddress("Bs_0_phi", &Bs_0_phi, &b_Bs_0_phi);
   fChain->SetBranchAddress("Bs_0_BDTS_BIPS", &Bs_0_BDTS_BIPS, &b_Bs_0_BDTS_BIPS);
   fChain->SetBranchAddress("Bs_0_BDTS_DOCA", &Bs_0_BDTS_DOCA, &b_Bs_0_BDTS_DOCA);
   fChain->SetBranchAddress("Bs_0_BDTS_VTXCHI2", &Bs_0_BDTS_VTXCHI2, &b_Bs_0_BDTS_VTXCHI2);
   fChain->SetBranchAddress("Bs_0_BDTS_DIRA", &Bs_0_BDTS_DIRA, &b_Bs_0_BDTS_DIRA);
   fChain->SetBranchAddress("Bs_0_BDTS_BIP", &Bs_0_BDTS_BIP, &b_Bs_0_BDTS_BIP);
   fChain->SetBranchAddress("Bs_0_BDTS_MuonMINIP", &Bs_0_BDTS_MuonMINIP, &b_Bs_0_BDTS_MuonMINIP);
   fChain->SetBranchAddress("Bs_0_BDTS", &Bs_0_BDTS, &b_Bs_0_BDTS);
   fChain->SetBranchAddress("Bs_0_CTAU_ps", &Bs_0_CTAU_ps, &b_Bs_0_CTAU_ps);
   fChain->SetBranchAddress("Bs_0_TAU", &Bs_0_TAU, &b_Bs_0_TAU);
   fChain->SetBranchAddress("Bs_0_TAUERR", &Bs_0_TAUERR, &b_Bs_0_TAUERR);
   fChain->SetBranchAddress("Bs_0_TAUCHI2", &Bs_0_TAUCHI2, &b_Bs_0_TAUCHI2);
   fChain->SetBranchAddress("Bs_0_SV_X", &Bs_0_SV_X, &b_Bs_0_SV_X);
   fChain->SetBranchAddress("Bs_0_SV_Y", &Bs_0_SV_Y, &b_Bs_0_SV_Y);
   fChain->SetBranchAddress("Bs_0_SV_Z", &Bs_0_SV_Z, &b_Bs_0_SV_Z);
   fChain->SetBranchAddress("Bs_0_SV_CHI2", &Bs_0_SV_CHI2, &b_Bs_0_SV_CHI2);
   fChain->SetBranchAddress("Bs_0_SV_NDOF", &Bs_0_SV_NDOF, &b_Bs_0_SV_NDOF);
   fChain->SetBranchAddress("Bs_0_SV_COV_", Bs_0_SV_COV_, &b_Bs_0_SV_COV_);
   fChain->SetBranchAddress("Bs_0_PV_X", &Bs_0_PV_X, &b_Bs_0_PV_X);
   fChain->SetBranchAddress("Bs_0_PV_Y", &Bs_0_PV_Y, &b_Bs_0_PV_Y);
   fChain->SetBranchAddress("Bs_0_PV_Z", &Bs_0_PV_Z, &b_Bs_0_PV_Z);
   fChain->SetBranchAddress("Bs_0_PV_CHI2", &Bs_0_PV_CHI2, &b_Bs_0_PV_CHI2);
   fChain->SetBranchAddress("Bs_0_PV_NDOF", &Bs_0_PV_NDOF, &b_Bs_0_PV_NDOF);
   fChain->SetBranchAddress("Bs_0_PV_COV_", Bs_0_PV_COV_, &b_Bs_0_PV_COV_);
   fChain->SetBranchAddress("Bs_0_MOM_COV_", Bs_0_MOM_COV_, &b_Bs_0_MOM_COV_);
   fChain->SetBranchAddress("Bs_0_POSMOM_COV_", Bs_0_POSMOM_COV_, &b_Bs_0_POSMOM_COV_);
   fChain->SetBranchAddress("Bs_0_MCORR", &Bs_0_MCORR, &b_Bs_0_MCORR);
   fChain->SetBranchAddress("Bs_0_MCORRERR", &Bs_0_MCORRERR, &b_Bs_0_MCORRERR);
   fChain->SetBranchAddress("Bs_0_MCORRFULLERR", &Bs_0_MCORRFULLERR, &b_Bs_0_MCORRFULLERR);
   fChain->SetBranchAddress("Bs_0_Q2SOL1", &Bs_0_Q2SOL1, &b_Bs_0_Q2SOL1);
   fChain->SetBranchAddress("Bs_0_Q2SOL2", &Bs_0_Q2SOL2, &b_Bs_0_Q2SOL2);
   fChain->SetBranchAddress("Bs_0_L0Global_Dec", &Bs_0_L0Global_Dec, &b_Bs_0_L0Global_Dec);
   fChain->SetBranchAddress("Bs_0_L0Global_TIS", &Bs_0_L0Global_TIS, &b_Bs_0_L0Global_TIS);
   fChain->SetBranchAddress("Bs_0_L0Global_TOS", &Bs_0_L0Global_TOS, &b_Bs_0_L0Global_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt1Global_Dec", &Bs_0_Hlt1Global_Dec, &b_Bs_0_Hlt1Global_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt1Global_TIS", &Bs_0_Hlt1Global_TIS, &b_Bs_0_Hlt1Global_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt1Global_TOS", &Bs_0_Hlt1Global_TOS, &b_Bs_0_Hlt1Global_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt1Phys_Dec", &Bs_0_Hlt1Phys_Dec, &b_Bs_0_Hlt1Phys_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt1Phys_TIS", &Bs_0_Hlt1Phys_TIS, &b_Bs_0_Hlt1Phys_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt1Phys_TOS", &Bs_0_Hlt1Phys_TOS, &b_Bs_0_Hlt1Phys_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2Global_Dec", &Bs_0_Hlt2Global_Dec, &b_Bs_0_Hlt2Global_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2Global_TIS", &Bs_0_Hlt2Global_TIS, &b_Bs_0_Hlt2Global_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2Global_TOS", &Bs_0_Hlt2Global_TOS, &b_Bs_0_Hlt2Global_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2Phys_Dec", &Bs_0_Hlt2Phys_Dec, &b_Bs_0_Hlt2Phys_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2Phys_TIS", &Bs_0_Hlt2Phys_TIS, &b_Bs_0_Hlt2Phys_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2Phys_TOS", &Bs_0_Hlt2Phys_TOS, &b_Bs_0_Hlt2Phys_TOS);
   fChain->SetBranchAddress("Bs_0_L0MuonDecision_Dec", &Bs_0_L0MuonDecision_Dec, &b_Bs_0_L0MuonDecision_Dec);
   fChain->SetBranchAddress("Bs_0_L0MuonDecision_TIS", &Bs_0_L0MuonDecision_TIS, &b_Bs_0_L0MuonDecision_TIS);
   fChain->SetBranchAddress("Bs_0_L0MuonDecision_TOS", &Bs_0_L0MuonDecision_TOS, &b_Bs_0_L0MuonDecision_TOS);
   fChain->SetBranchAddress("Bs_0_L0DiMuonDecision_Dec", &Bs_0_L0DiMuonDecision_Dec, &b_Bs_0_L0DiMuonDecision_Dec);
   fChain->SetBranchAddress("Bs_0_L0DiMuonDecision_TIS", &Bs_0_L0DiMuonDecision_TIS, &b_Bs_0_L0DiMuonDecision_TIS);
   fChain->SetBranchAddress("Bs_0_L0DiMuonDecision_TOS", &Bs_0_L0DiMuonDecision_TOS, &b_Bs_0_L0DiMuonDecision_TOS);
   fChain->SetBranchAddress("Bs_0_L0HadronDecision_Dec", &Bs_0_L0HadronDecision_Dec, &b_Bs_0_L0HadronDecision_Dec);
   fChain->SetBranchAddress("Bs_0_L0HadronDecision_TIS", &Bs_0_L0HadronDecision_TIS, &b_Bs_0_L0HadronDecision_TIS);
   fChain->SetBranchAddress("Bs_0_L0HadronDecision_TOS", &Bs_0_L0HadronDecision_TOS, &b_Bs_0_L0HadronDecision_TOS);
   fChain->SetBranchAddress("Bs_0_L0ElectronDecision_Dec", &Bs_0_L0ElectronDecision_Dec, &b_Bs_0_L0ElectronDecision_Dec);
   fChain->SetBranchAddress("Bs_0_L0ElectronDecision_TIS", &Bs_0_L0ElectronDecision_TIS, &b_Bs_0_L0ElectronDecision_TIS);
   fChain->SetBranchAddress("Bs_0_L0ElectronDecision_TOS", &Bs_0_L0ElectronDecision_TOS, &b_Bs_0_L0ElectronDecision_TOS);
   fChain->SetBranchAddress("Bs_0_L0ElectronHiDecision_Dec", &Bs_0_L0ElectronHiDecision_Dec, &b_Bs_0_L0ElectronHiDecision_Dec);
   fChain->SetBranchAddress("Bs_0_L0ElectronHiDecision_TIS", &Bs_0_L0ElectronHiDecision_TIS, &b_Bs_0_L0ElectronHiDecision_TIS);
   fChain->SetBranchAddress("Bs_0_L0ElectronHiDecision_TOS", &Bs_0_L0ElectronHiDecision_TOS, &b_Bs_0_L0ElectronHiDecision_TOS);
   fChain->SetBranchAddress("Bs_0_L0PhotonDecision_Dec", &Bs_0_L0PhotonDecision_Dec, &b_Bs_0_L0PhotonDecision_Dec);
   fChain->SetBranchAddress("Bs_0_L0PhotonDecision_TIS", &Bs_0_L0PhotonDecision_TIS, &b_Bs_0_L0PhotonDecision_TIS);
   fChain->SetBranchAddress("Bs_0_L0PhotonDecision_TOS", &Bs_0_L0PhotonDecision_TOS, &b_Bs_0_L0PhotonDecision_TOS);
   fChain->SetBranchAddress("Bs_0_L0PhotonHiDecision_Dec", &Bs_0_L0PhotonHiDecision_Dec, &b_Bs_0_L0PhotonHiDecision_Dec);
   fChain->SetBranchAddress("Bs_0_L0PhotonHiDecision_TIS", &Bs_0_L0PhotonHiDecision_TIS, &b_Bs_0_L0PhotonHiDecision_TIS);
   fChain->SetBranchAddress("Bs_0_L0PhotonHiDecision_TOS", &Bs_0_L0PhotonHiDecision_TOS, &b_Bs_0_L0PhotonHiDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt1SingleMuonNoIPDecision_Dec", &Bs_0_Hlt1SingleMuonNoIPDecision_Dec, &b_Bs_0_Hlt1SingleMuonNoIPDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt1SingleMuonNoIPDecision_TIS", &Bs_0_Hlt1SingleMuonNoIPDecision_TIS, &b_Bs_0_Hlt1SingleMuonNoIPDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt1SingleMuonNoIPDecision_TOS", &Bs_0_Hlt1SingleMuonNoIPDecision_TOS, &b_Bs_0_Hlt1SingleMuonNoIPDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt1SingleMuonHighPTDecision_Dec", &Bs_0_Hlt1SingleMuonHighPTDecision_Dec, &b_Bs_0_Hlt1SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt1SingleMuonHighPTDecision_TIS", &Bs_0_Hlt1SingleMuonHighPTDecision_TIS, &b_Bs_0_Hlt1SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt1SingleMuonHighPTDecision_TOS", &Bs_0_Hlt1SingleMuonHighPTDecision_TOS, &b_Bs_0_Hlt1SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt1SingleElectronNoIPDecision_Dec", &Bs_0_Hlt1SingleElectronNoIPDecision_Dec, &b_Bs_0_Hlt1SingleElectronNoIPDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt1SingleElectronNoIPDecision_TIS", &Bs_0_Hlt1SingleElectronNoIPDecision_TIS, &b_Bs_0_Hlt1SingleElectronNoIPDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt1SingleElectronNoIPDecision_TOS", &Bs_0_Hlt1SingleElectronNoIPDecision_TOS, &b_Bs_0_Hlt1SingleElectronNoIPDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt1TrackAllL0Decision_Dec", &Bs_0_Hlt1TrackAllL0Decision_Dec, &b_Bs_0_Hlt1TrackAllL0Decision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt1TrackAllL0Decision_TIS", &Bs_0_Hlt1TrackAllL0Decision_TIS, &b_Bs_0_Hlt1TrackAllL0Decision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt1TrackAllL0Decision_TOS", &Bs_0_Hlt1TrackAllL0Decision_TOS, &b_Bs_0_Hlt1TrackAllL0Decision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt1TrackMuonDecision_Dec", &Bs_0_Hlt1TrackMuonDecision_Dec, &b_Bs_0_Hlt1TrackMuonDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt1TrackMuonDecision_TIS", &Bs_0_Hlt1TrackMuonDecision_TIS, &b_Bs_0_Hlt1TrackMuonDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt1TrackMuonDecision_TOS", &Bs_0_Hlt1TrackMuonDecision_TOS, &b_Bs_0_Hlt1TrackMuonDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt1TrackPhotonDecision_Dec", &Bs_0_Hlt1TrackPhotonDecision_Dec, &b_Bs_0_Hlt1TrackPhotonDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt1TrackPhotonDecision_TIS", &Bs_0_Hlt1TrackPhotonDecision_TIS, &b_Bs_0_Hlt1TrackPhotonDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt1TrackPhotonDecision_TOS", &Bs_0_Hlt1TrackPhotonDecision_TOS, &b_Bs_0_Hlt1TrackPhotonDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt1TrackAllL0__Decision_Dec", &Bs_0_Hlt1TrackAllL0__Decision_Dec, &b_Bs_0_Hlt1TrackAllL0__Decision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt1TrackAllL0__Decision_TIS", &Bs_0_Hlt1TrackAllL0__Decision_TIS, &b_Bs_0_Hlt1TrackAllL0__Decision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt1TrackAllL0__Decision_TOS", &Bs_0_Hlt1TrackAllL0__Decision_TOS, &b_Bs_0_Hlt1TrackAllL0__Decision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt1DiMuonLowMassDecision_Dec", &Bs_0_Hlt1DiMuonLowMassDecision_Dec, &b_Bs_0_Hlt1DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt1DiMuonLowMassDecision_TIS", &Bs_0_Hlt1DiMuonLowMassDecision_TIS, &b_Bs_0_Hlt1DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt1DiMuonLowMassDecision_TOS", &Bs_0_Hlt1DiMuonLowMassDecision_TOS, &b_Bs_0_Hlt1DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt1DiMuonHighMassDecision_Dec", &Bs_0_Hlt1DiMuonHighMassDecision_Dec, &b_Bs_0_Hlt1DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt1DiMuonHighMassDecision_TIS", &Bs_0_Hlt1DiMuonHighMassDecision_TIS, &b_Bs_0_Hlt1DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt1DiMuonHighMassDecision_TOS", &Bs_0_Hlt1DiMuonHighMassDecision_TOS, &b_Bs_0_Hlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt1MB__Decision_Dec", &Bs_0_Hlt1MB__Decision_Dec, &b_Bs_0_Hlt1MB__Decision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt1MB__Decision_TIS", &Bs_0_Hlt1MB__Decision_TIS, &b_Bs_0_Hlt1MB__Decision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt1MB__Decision_TOS", &Bs_0_Hlt1MB__Decision_TOS, &b_Bs_0_Hlt1MB__Decision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt1TrackAllL0TightDecision_Dec", &Bs_0_Hlt1TrackAllL0TightDecision_Dec, &b_Bs_0_Hlt1TrackAllL0TightDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt1TrackAllL0TightDecision_TIS", &Bs_0_Hlt1TrackAllL0TightDecision_TIS, &b_Bs_0_Hlt1TrackAllL0TightDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt1TrackAllL0TightDecision_TOS", &Bs_0_Hlt1TrackAllL0TightDecision_TOS, &b_Bs_0_Hlt1TrackAllL0TightDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2SingleMuonDecision_Dec", &Bs_0_Hlt2SingleMuonDecision_Dec, &b_Bs_0_Hlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2SingleMuonDecision_TIS", &Bs_0_Hlt2SingleMuonDecision_TIS, &b_Bs_0_Hlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2SingleMuonDecision_TOS", &Bs_0_Hlt2SingleMuonDecision_TOS, &b_Bs_0_Hlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2SingleMuonLowPTDecision_Dec", &Bs_0_Hlt2SingleMuonLowPTDecision_Dec, &b_Bs_0_Hlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2SingleMuonLowPTDecision_TIS", &Bs_0_Hlt2SingleMuonLowPTDecision_TIS, &b_Bs_0_Hlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2SingleMuonLowPTDecision_TOS", &Bs_0_Hlt2SingleMuonLowPTDecision_TOS, &b_Bs_0_Hlt2SingleMuonLowPTDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2SingleMuonHighPTDecision_Dec", &Bs_0_Hlt2SingleMuonHighPTDecision_Dec, &b_Bs_0_Hlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2SingleMuonHighPTDecision_TIS", &Bs_0_Hlt2SingleMuonHighPTDecision_TIS, &b_Bs_0_Hlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2SingleMuonHighPTDecision_TOS", &Bs_0_Hlt2SingleMuonHighPTDecision_TOS, &b_Bs_0_Hlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonDecision_Dec", &Bs_0_Hlt2DiMuonDecision_Dec, &b_Bs_0_Hlt2DiMuonDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonDecision_TIS", &Bs_0_Hlt2DiMuonDecision_TIS, &b_Bs_0_Hlt2DiMuonDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonDecision_TOS", &Bs_0_Hlt2DiMuonDecision_TOS, &b_Bs_0_Hlt2DiMuonDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonLowMassDecision_Dec", &Bs_0_Hlt2DiMuonLowMassDecision_Dec, &b_Bs_0_Hlt2DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonLowMassDecision_TIS", &Bs_0_Hlt2DiMuonLowMassDecision_TIS, &b_Bs_0_Hlt2DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonLowMassDecision_TOS", &Bs_0_Hlt2DiMuonLowMassDecision_TOS, &b_Bs_0_Hlt2DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonJPsiHighPTDecision_Dec", &Bs_0_Hlt2DiMuonJPsiHighPTDecision_Dec, &b_Bs_0_Hlt2DiMuonJPsiHighPTDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonJPsiHighPTDecision_TIS", &Bs_0_Hlt2DiMuonJPsiHighPTDecision_TIS, &b_Bs_0_Hlt2DiMuonJPsiHighPTDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonJPsiHighPTDecision_TOS", &Bs_0_Hlt2DiMuonJPsiHighPTDecision_TOS, &b_Bs_0_Hlt2DiMuonJPsiHighPTDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonPsi2SDecision_Dec", &Bs_0_Hlt2DiMuonPsi2SDecision_Dec, &b_Bs_0_Hlt2DiMuonPsi2SDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonPsi2SDecision_TIS", &Bs_0_Hlt2DiMuonPsi2SDecision_TIS, &b_Bs_0_Hlt2DiMuonPsi2SDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonPsi2SDecision_TOS", &Bs_0_Hlt2DiMuonPsi2SDecision_TOS, &b_Bs_0_Hlt2DiMuonPsi2SDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonDetachedDecision_Dec", &Bs_0_Hlt2DiMuonDetachedDecision_Dec, &b_Bs_0_Hlt2DiMuonDetachedDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonDetachedDecision_TIS", &Bs_0_Hlt2DiMuonDetachedDecision_TIS, &b_Bs_0_Hlt2DiMuonDetachedDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonDetachedDecision_TOS", &Bs_0_Hlt2DiMuonDetachedDecision_TOS, &b_Bs_0_Hlt2DiMuonDetachedDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonDetachedJPsiDecision_Dec", &Bs_0_Hlt2DiMuonDetachedJPsiDecision_Dec, &b_Bs_0_Hlt2DiMuonDetachedJPsiDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonDetachedJPsiDecision_TIS", &Bs_0_Hlt2DiMuonDetachedJPsiDecision_TIS, &b_Bs_0_Hlt2DiMuonDetachedJPsiDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonDetachedJPsiDecision_TOS", &Bs_0_Hlt2DiMuonDetachedJPsiDecision_TOS, &b_Bs_0_Hlt2DiMuonDetachedJPsiDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonDetachedHeavyDecision_Dec", &Bs_0_Hlt2DiMuonDetachedHeavyDecision_Dec, &b_Bs_0_Hlt2DiMuonDetachedHeavyDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonDetachedHeavyDecision_TIS", &Bs_0_Hlt2DiMuonDetachedHeavyDecision_TIS, &b_Bs_0_Hlt2DiMuonDetachedHeavyDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonDetachedHeavyDecision_TOS", &Bs_0_Hlt2DiMuonDetachedHeavyDecision_TOS, &b_Bs_0_Hlt2DiMuonDetachedHeavyDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2TriMuonTauDecision_Dec", &Bs_0_Hlt2TriMuonTauDecision_Dec, &b_Bs_0_Hlt2TriMuonTauDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2TriMuonTauDecision_TIS", &Bs_0_Hlt2TriMuonTauDecision_TIS, &b_Bs_0_Hlt2TriMuonTauDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2TriMuonTauDecision_TOS", &Bs_0_Hlt2TriMuonTauDecision_TOS, &b_Bs_0_Hlt2TriMuonTauDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2B2HHDecision_Dec", &Bs_0_Hlt2B2HHDecision_Dec, &b_Bs_0_Hlt2B2HHDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2B2HHDecision_TIS", &Bs_0_Hlt2B2HHDecision_TIS, &b_Bs_0_Hlt2B2HHDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2B2HHDecision_TOS", &Bs_0_Hlt2B2HHDecision_TOS, &b_Bs_0_Hlt2B2HHDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonBDecision_Dec", &Bs_0_Hlt2DiMuonBDecision_Dec, &b_Bs_0_Hlt2DiMuonBDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonBDecision_TIS", &Bs_0_Hlt2DiMuonBDecision_TIS, &b_Bs_0_Hlt2DiMuonBDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonBDecision_TOS", &Bs_0_Hlt2DiMuonBDecision_TOS, &b_Bs_0_Hlt2DiMuonBDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonZDecision_Dec", &Bs_0_Hlt2DiMuonZDecision_Dec, &b_Bs_0_Hlt2DiMuonZDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonZDecision_TIS", &Bs_0_Hlt2DiMuonZDecision_TIS, &b_Bs_0_Hlt2DiMuonZDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonZDecision_TOS", &Bs_0_Hlt2DiMuonZDecision_TOS, &b_Bs_0_Hlt2DiMuonZDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2TopoMu2BodyBBDTDecision_Dec", &Bs_0_Hlt2TopoMu2BodyBBDTDecision_Dec, &b_Bs_0_Hlt2TopoMu2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2TopoMu2BodyBBDTDecision_TIS", &Bs_0_Hlt2TopoMu2BodyBBDTDecision_TIS, &b_Bs_0_Hlt2TopoMu2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2TopoMu2BodyBBDTDecision_TOS", &Bs_0_Hlt2TopoMu2BodyBBDTDecision_TOS, &b_Bs_0_Hlt2TopoMu2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2TopoMu3BodyBBDTDecision_Dec", &Bs_0_Hlt2TopoMu3BodyBBDTDecision_Dec, &b_Bs_0_Hlt2TopoMu3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2TopoMu3BodyBBDTDecision_TIS", &Bs_0_Hlt2TopoMu3BodyBBDTDecision_TIS, &b_Bs_0_Hlt2TopoMu3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2TopoMu3BodyBBDTDecision_TOS", &Bs_0_Hlt2TopoMu3BodyBBDTDecision_TOS, &b_Bs_0_Hlt2TopoMu3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2TopoMu4BodyBBDTDecision_Dec", &Bs_0_Hlt2TopoMu4BodyBBDTDecision_Dec, &b_Bs_0_Hlt2TopoMu4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2TopoMu4BodyBBDTDecision_TIS", &Bs_0_Hlt2TopoMu4BodyBBDTDecision_TIS, &b_Bs_0_Hlt2TopoMu4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2TopoMu4BodyBBDTDecision_TOS", &Bs_0_Hlt2TopoMu4BodyBBDTDecision_TOS, &b_Bs_0_Hlt2TopoMu4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo2BodyBBDTDecision_Dec", &Bs_0_Hlt2Topo2BodyBBDTDecision_Dec, &b_Bs_0_Hlt2Topo2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo2BodyBBDTDecision_TIS", &Bs_0_Hlt2Topo2BodyBBDTDecision_TIS, &b_Bs_0_Hlt2Topo2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo2BodyBBDTDecision_TOS", &Bs_0_Hlt2Topo2BodyBBDTDecision_TOS, &b_Bs_0_Hlt2Topo2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo3BodyBBDTDecision_Dec", &Bs_0_Hlt2Topo3BodyBBDTDecision_Dec, &b_Bs_0_Hlt2Topo3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo3BodyBBDTDecision_TIS", &Bs_0_Hlt2Topo3BodyBBDTDecision_TIS, &b_Bs_0_Hlt2Topo3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo3BodyBBDTDecision_TOS", &Bs_0_Hlt2Topo3BodyBBDTDecision_TOS, &b_Bs_0_Hlt2Topo3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo4BodyBBDTDecision_Dec", &Bs_0_Hlt2Topo4BodyBBDTDecision_Dec, &b_Bs_0_Hlt2Topo4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo4BodyBBDTDecision_TIS", &Bs_0_Hlt2Topo4BodyBBDTDecision_TIS, &b_Bs_0_Hlt2Topo4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo4BodyBBDTDecision_TOS", &Bs_0_Hlt2Topo4BodyBBDTDecision_TOS, &b_Bs_0_Hlt2Topo4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo2BodySimpleDecision_Dec", &Bs_0_Hlt2Topo2BodySimpleDecision_Dec, &b_Bs_0_Hlt2Topo2BodySimpleDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo2BodySimpleDecision_TIS", &Bs_0_Hlt2Topo2BodySimpleDecision_TIS, &b_Bs_0_Hlt2Topo2BodySimpleDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo2BodySimpleDecision_TOS", &Bs_0_Hlt2Topo2BodySimpleDecision_TOS, &b_Bs_0_Hlt2Topo2BodySimpleDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo3BodySimpleDecision_Dec", &Bs_0_Hlt2Topo3BodySimpleDecision_Dec, &b_Bs_0_Hlt2Topo3BodySimpleDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo3BodySimpleDecision_TIS", &Bs_0_Hlt2Topo3BodySimpleDecision_TIS, &b_Bs_0_Hlt2Topo3BodySimpleDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo3BodySimpleDecision_TOS", &Bs_0_Hlt2Topo3BodySimpleDecision_TOS, &b_Bs_0_Hlt2Topo3BodySimpleDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo4BodySimpleDecision_Dec", &Bs_0_Hlt2Topo4BodySimpleDecision_Dec, &b_Bs_0_Hlt2Topo4BodySimpleDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo4BodySimpleDecision_TIS", &Bs_0_Hlt2Topo4BodySimpleDecision_TIS, &b_Bs_0_Hlt2Topo4BodySimpleDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo4BodySimpleDecision_TOS", &Bs_0_Hlt2Topo4BodySimpleDecision_TOS, &b_Bs_0_Hlt2Topo4BodySimpleDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2PassThroughDecision_Dec", &Bs_0_Hlt2PassThroughDecision_Dec, &b_Bs_0_Hlt2PassThroughDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2PassThroughDecision_TIS", &Bs_0_Hlt2PassThroughDecision_TIS, &b_Bs_0_Hlt2PassThroughDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2PassThroughDecision_TOS", &Bs_0_Hlt2PassThroughDecision_TOS, &b_Bs_0_Hlt2PassThroughDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2TransparentDecision_Dec", &Bs_0_Hlt2TransparentDecision_Dec, &b_Bs_0_Hlt2TransparentDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2TransparentDecision_TIS", &Bs_0_Hlt2TransparentDecision_TIS, &b_Bs_0_Hlt2TransparentDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2TransparentDecision_TOS", &Bs_0_Hlt2TransparentDecision_TOS, &b_Bs_0_Hlt2TransparentDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2IncPhiDecision_Dec", &Bs_0_Hlt2IncPhiDecision_Dec, &b_Bs_0_Hlt2IncPhiDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2IncPhiDecision_TIS", &Bs_0_Hlt2IncPhiDecision_TIS, &b_Bs_0_Hlt2IncPhiDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2IncPhiDecision_TOS", &Bs_0_Hlt2IncPhiDecision_TOS, &b_Bs_0_Hlt2IncPhiDecision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonDY__Decision_Dec", &Bs_0_Hlt2DiMuonDY__Decision_Dec, &b_Bs_0_Hlt2DiMuonDY__Decision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonDY__Decision_TIS", &Bs_0_Hlt2DiMuonDY__Decision_TIS, &b_Bs_0_Hlt2DiMuonDY__Decision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiMuonDY__Decision_TOS", &Bs_0_Hlt2DiMuonDY__Decision_TOS, &b_Bs_0_Hlt2DiMuonDY__Decision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2TopoE__Decision_Dec", &Bs_0_Hlt2TopoE__Decision_Dec, &b_Bs_0_Hlt2TopoE__Decision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2TopoE__Decision_TIS", &Bs_0_Hlt2TopoE__Decision_TIS, &b_Bs_0_Hlt2TopoE__Decision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2TopoE__Decision_TOS", &Bs_0_Hlt2TopoE__Decision_TOS, &b_Bs_0_Hlt2TopoE__Decision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo__Decision_Dec", &Bs_0_Hlt2Topo__Decision_Dec, &b_Bs_0_Hlt2Topo__Decision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo__Decision_TIS", &Bs_0_Hlt2Topo__Decision_TIS, &b_Bs_0_Hlt2Topo__Decision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2Topo__Decision_TOS", &Bs_0_Hlt2Topo__Decision_TOS, &b_Bs_0_Hlt2Topo__Decision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2Charm__Decision_Dec", &Bs_0_Hlt2Charm__Decision_Dec, &b_Bs_0_Hlt2Charm__Decision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2Charm__Decision_TIS", &Bs_0_Hlt2Charm__Decision_TIS, &b_Bs_0_Hlt2Charm__Decision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2Charm__Decision_TOS", &Bs_0_Hlt2Charm__Decision_TOS, &b_Bs_0_Hlt2Charm__Decision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiElectron__Decision_Dec", &Bs_0_Hlt2DiElectron__Decision_Dec, &b_Bs_0_Hlt2DiElectron__Decision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2DiElectron__Decision_TIS", &Bs_0_Hlt2DiElectron__Decision_TIS, &b_Bs_0_Hlt2DiElectron__Decision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2DiElectron__Decision_TOS", &Bs_0_Hlt2DiElectron__Decision_TOS, &b_Bs_0_Hlt2DiElectron__Decision_TOS);
   fChain->SetBranchAddress("Bs_0_Hlt2__GammaDecision_Dec", &Bs_0_Hlt2__GammaDecision_Dec, &b_Bs_0_Hlt2__GammaDecision_Dec);
   fChain->SetBranchAddress("Bs_0_Hlt2__GammaDecision_TIS", &Bs_0_Hlt2__GammaDecision_TIS, &b_Bs_0_Hlt2__GammaDecision_TIS);
   fChain->SetBranchAddress("Bs_0_Hlt2__GammaDecision_TOS", &Bs_0_Hlt2__GammaDecision_TOS, &b_Bs_0_Hlt2__GammaDecision_TOS);
   fChain->SetBranchAddress("Bs_0_NumVtxWithinChi2WindowOneTrack", &Bs_0_NumVtxWithinChi2WindowOneTrack, &b_Bs_0_NumVtxWithinChi2WindowOneTrack);
   fChain->SetBranchAddress("Bs_0_SmallestDeltaChi2OneTrack", &Bs_0_SmallestDeltaChi2OneTrack, &b_Bs_0_SmallestDeltaChi2OneTrack);
   fChain->SetBranchAddress("Bs_0_SmallestDeltaChi2MassOneTrack", &Bs_0_SmallestDeltaChi2MassOneTrack, &b_Bs_0_SmallestDeltaChi2MassOneTrack);
   fChain->SetBranchAddress("Bs_0_SmallestDeltaChi2TwoTracks", &Bs_0_SmallestDeltaChi2TwoTracks, &b_Bs_0_SmallestDeltaChi2TwoTracks);
   fChain->SetBranchAddress("Bs_0_SmallestDeltaChi2MassTwoTracks", &Bs_0_SmallestDeltaChi2MassTwoTracks, &b_Bs_0_SmallestDeltaChi2MassTwoTracks);
   fChain->SetBranchAddress("Ds_0.00_cc_mult", &Ds_0_00_cc_mult, &b_Ds_0_00_cc_mult);
   fChain->SetBranchAddress("Ds_0.00_cc_PX", &Ds_0_00_cc_PX, &b_Ds_0_00_cc_PX);
   fChain->SetBranchAddress("Ds_0.00_cc_PY", &Ds_0_00_cc_PY, &b_Ds_0_00_cc_PY);
   fChain->SetBranchAddress("Ds_0.00_cc_PZ", &Ds_0_00_cc_PZ, &b_Ds_0_00_cc_PZ);
   fChain->SetBranchAddress("Ds_0.00_cc_vPT", &Ds_0_00_cc_vPT, &b_Ds_0_00_cc_vPT);
   fChain->SetBranchAddress("Ds_0.00_cc_sPT", &Ds_0_00_cc_sPT, &b_Ds_0_00_cc_sPT);
   fChain->SetBranchAddress("Ds_0.00_cc_maxPt_Q", &Ds_0_00_cc_maxPt_Q, &b_Ds_0_00_cc_maxPt_Q);
   fChain->SetBranchAddress("Ds_0.00_cc_maxPt_PT", &Ds_0_00_cc_maxPt_PT, &b_Ds_0_00_cc_maxPt_PT);
   fChain->SetBranchAddress("Ds_0.00_cc_maxPt_PX", &Ds_0_00_cc_maxPt_PX, &b_Ds_0_00_cc_maxPt_PX);
   fChain->SetBranchAddress("Ds_0.00_cc_maxPt_PY", &Ds_0_00_cc_maxPt_PY, &b_Ds_0_00_cc_maxPt_PY);
   fChain->SetBranchAddress("Ds_0.00_cc_maxPt_PZ", &Ds_0_00_cc_maxPt_PZ, &b_Ds_0_00_cc_maxPt_PZ);
   fChain->SetBranchAddress("Ds_0.00_cc_maxPt_PE", &Ds_0_00_cc_maxPt_PE, &b_Ds_0_00_cc_maxPt_PE);
   fChain->SetBranchAddress("Ds_0.00_nc_mult", &Ds_0_00_nc_mult, &b_Ds_0_00_nc_mult);
   fChain->SetBranchAddress("Ds_0.00_nc_PX", &Ds_0_00_nc_PX, &b_Ds_0_00_nc_PX);
   fChain->SetBranchAddress("Ds_0.00_nc_PY", &Ds_0_00_nc_PY, &b_Ds_0_00_nc_PY);
   fChain->SetBranchAddress("Ds_0.00_nc_PZ", &Ds_0_00_nc_PZ, &b_Ds_0_00_nc_PZ);
   fChain->SetBranchAddress("Ds_0.00_nc_vPT", &Ds_0_00_nc_vPT, &b_Ds_0_00_nc_vPT);
   fChain->SetBranchAddress("Ds_0.00_nc_sPT", &Ds_0_00_nc_sPT, &b_Ds_0_00_nc_sPT);
   fChain->SetBranchAddress("Ds_0.00_nc_maxPt_PT", &Ds_0_00_nc_maxPt_PT, &b_Ds_0_00_nc_maxPt_PT);
   fChain->SetBranchAddress("Ds_0.00_nc_maxPt_PX", &Ds_0_00_nc_maxPt_PX, &b_Ds_0_00_nc_maxPt_PX);
   fChain->SetBranchAddress("Ds_0.00_nc_maxPt_PY", &Ds_0_00_nc_maxPt_PY, &b_Ds_0_00_nc_maxPt_PY);
   fChain->SetBranchAddress("Ds_0.00_nc_maxPt_PZ", &Ds_0_00_nc_maxPt_PZ, &b_Ds_0_00_nc_maxPt_PZ);
   fChain->SetBranchAddress("Ds_1.50_cc_mult", &Ds_1_50_cc_mult, &b_Ds_1_50_cc_mult);
   fChain->SetBranchAddress("Ds_1.50_cc_PX", &Ds_1_50_cc_PX, &b_Ds_1_50_cc_PX);
   fChain->SetBranchAddress("Ds_1.50_cc_PY", &Ds_1_50_cc_PY, &b_Ds_1_50_cc_PY);
   fChain->SetBranchAddress("Ds_1.50_cc_PZ", &Ds_1_50_cc_PZ, &b_Ds_1_50_cc_PZ);
   fChain->SetBranchAddress("Ds_1.50_cc_vPT", &Ds_1_50_cc_vPT, &b_Ds_1_50_cc_vPT);
   fChain->SetBranchAddress("Ds_1.50_cc_sPT", &Ds_1_50_cc_sPT, &b_Ds_1_50_cc_sPT);
   fChain->SetBranchAddress("Ds_1.50_nc_mult", &Ds_1_50_nc_mult, &b_Ds_1_50_nc_mult);
   fChain->SetBranchAddress("Ds_1.50_nc_PX", &Ds_1_50_nc_PX, &b_Ds_1_50_nc_PX);
   fChain->SetBranchAddress("Ds_1.50_nc_PY", &Ds_1_50_nc_PY, &b_Ds_1_50_nc_PY);
   fChain->SetBranchAddress("Ds_1.50_nc_PZ", &Ds_1_50_nc_PZ, &b_Ds_1_50_nc_PZ);
   fChain->SetBranchAddress("Ds_1.50_nc_vPT", &Ds_1_50_nc_vPT, &b_Ds_1_50_nc_vPT);
   fChain->SetBranchAddress("Ds_1.50_nc_sPT", &Ds_1_50_nc_sPT, &b_Ds_1_50_nc_sPT);
   fChain->SetBranchAddress("Ds_1.50_nc_maxPt_PX", &Ds_1_50_nc_maxPt_PX, &b_Ds_1_50_nc_maxPt_PX);
   fChain->SetBranchAddress("Ds_1.50_nc_maxPt_PY", &Ds_1_50_nc_maxPt_PY, &b_Ds_1_50_nc_maxPt_PY);
   fChain->SetBranchAddress("Ds_1.50_nc_maxPt_PZ", &Ds_1_50_nc_maxPt_PZ, &b_Ds_1_50_nc_maxPt_PZ);
   fChain->SetBranchAddress("Ds_1.20_cc_mult", &Ds_1_20_cc_mult, &b_Ds_1_20_cc_mult);
   fChain->SetBranchAddress("Ds_1.20_cc_PX", &Ds_1_20_cc_PX, &b_Ds_1_20_cc_PX);
   fChain->SetBranchAddress("Ds_1.20_cc_PY", &Ds_1_20_cc_PY, &b_Ds_1_20_cc_PY);
   fChain->SetBranchAddress("Ds_1.20_cc_PZ", &Ds_1_20_cc_PZ, &b_Ds_1_20_cc_PZ);
   fChain->SetBranchAddress("Ds_1.20_cc_vPT", &Ds_1_20_cc_vPT, &b_Ds_1_20_cc_vPT);
   fChain->SetBranchAddress("Ds_1.20_cc_sPT", &Ds_1_20_cc_sPT, &b_Ds_1_20_cc_sPT);
   fChain->SetBranchAddress("Ds_1.20_nc_mult", &Ds_1_20_nc_mult, &b_Ds_1_20_nc_mult);
   fChain->SetBranchAddress("Ds_1.20_nc_PX", &Ds_1_20_nc_PX, &b_Ds_1_20_nc_PX);
   fChain->SetBranchAddress("Ds_1.20_nc_PY", &Ds_1_20_nc_PY, &b_Ds_1_20_nc_PY);
   fChain->SetBranchAddress("Ds_1.20_nc_PZ", &Ds_1_20_nc_PZ, &b_Ds_1_20_nc_PZ);
   fChain->SetBranchAddress("Ds_1.20_nc_vPT", &Ds_1_20_nc_vPT, &b_Ds_1_20_nc_vPT);
   fChain->SetBranchAddress("Ds_1.20_nc_sPT", &Ds_1_20_nc_sPT, &b_Ds_1_20_nc_sPT);
   fChain->SetBranchAddress("Ds_1.20_nc_maxPt_PX", &Ds_1_20_nc_maxPt_PX, &b_Ds_1_20_nc_maxPt_PX);
   fChain->SetBranchAddress("Ds_1.20_nc_maxPt_PY", &Ds_1_20_nc_maxPt_PY, &b_Ds_1_20_nc_maxPt_PY);
   fChain->SetBranchAddress("Ds_1.20_nc_maxPt_PZ", &Ds_1_20_nc_maxPt_PZ, &b_Ds_1_20_nc_maxPt_PZ);
   fChain->SetBranchAddress("Ds_0.90_cc_mult", &Ds_0_90_cc_mult, &b_Ds_0_90_cc_mult);
   fChain->SetBranchAddress("Ds_0.90_cc_PX", &Ds_0_90_cc_PX, &b_Ds_0_90_cc_PX);
   fChain->SetBranchAddress("Ds_0.90_cc_PY", &Ds_0_90_cc_PY, &b_Ds_0_90_cc_PY);
   fChain->SetBranchAddress("Ds_0.90_cc_PZ", &Ds_0_90_cc_PZ, &b_Ds_0_90_cc_PZ);
   fChain->SetBranchAddress("Ds_0.90_cc_vPT", &Ds_0_90_cc_vPT, &b_Ds_0_90_cc_vPT);
   fChain->SetBranchAddress("Ds_0.90_cc_sPT", &Ds_0_90_cc_sPT, &b_Ds_0_90_cc_sPT);
   fChain->SetBranchAddress("Ds_0.90_nc_mult", &Ds_0_90_nc_mult, &b_Ds_0_90_nc_mult);
   fChain->SetBranchAddress("Ds_0.90_nc_PX", &Ds_0_90_nc_PX, &b_Ds_0_90_nc_PX);
   fChain->SetBranchAddress("Ds_0.90_nc_PY", &Ds_0_90_nc_PY, &b_Ds_0_90_nc_PY);
   fChain->SetBranchAddress("Ds_0.90_nc_PZ", &Ds_0_90_nc_PZ, &b_Ds_0_90_nc_PZ);
   fChain->SetBranchAddress("Ds_0.90_nc_vPT", &Ds_0_90_nc_vPT, &b_Ds_0_90_nc_vPT);
   fChain->SetBranchAddress("Ds_0.90_nc_sPT", &Ds_0_90_nc_sPT, &b_Ds_0_90_nc_sPT);
   fChain->SetBranchAddress("Ds_0.90_nc_maxPt_PX", &Ds_0_90_nc_maxPt_PX, &b_Ds_0_90_nc_maxPt_PX);
   fChain->SetBranchAddress("Ds_0.90_nc_maxPt_PY", &Ds_0_90_nc_maxPt_PY, &b_Ds_0_90_nc_maxPt_PY);
   fChain->SetBranchAddress("Ds_0.90_nc_maxPt_PZ", &Ds_0_90_nc_maxPt_PZ, &b_Ds_0_90_nc_maxPt_PZ);
   fChain->SetBranchAddress("Ds_0.60_cc_mult", &Ds_0_60_cc_mult, &b_Ds_0_60_cc_mult);
   fChain->SetBranchAddress("Ds_0.60_cc_PX", &Ds_0_60_cc_PX, &b_Ds_0_60_cc_PX);
   fChain->SetBranchAddress("Ds_0.60_cc_PY", &Ds_0_60_cc_PY, &b_Ds_0_60_cc_PY);
   fChain->SetBranchAddress("Ds_0.60_cc_PZ", &Ds_0_60_cc_PZ, &b_Ds_0_60_cc_PZ);
   fChain->SetBranchAddress("Ds_0.60_cc_vPT", &Ds_0_60_cc_vPT, &b_Ds_0_60_cc_vPT);
   fChain->SetBranchAddress("Ds_0.60_cc_sPT", &Ds_0_60_cc_sPT, &b_Ds_0_60_cc_sPT);
   fChain->SetBranchAddress("Ds_0.60_nc_mult", &Ds_0_60_nc_mult, &b_Ds_0_60_nc_mult);
   fChain->SetBranchAddress("Ds_0.60_nc_PX", &Ds_0_60_nc_PX, &b_Ds_0_60_nc_PX);
   fChain->SetBranchAddress("Ds_0.60_nc_PY", &Ds_0_60_nc_PY, &b_Ds_0_60_nc_PY);
   fChain->SetBranchAddress("Ds_0.60_nc_PZ", &Ds_0_60_nc_PZ, &b_Ds_0_60_nc_PZ);
   fChain->SetBranchAddress("Ds_0.60_nc_vPT", &Ds_0_60_nc_vPT, &b_Ds_0_60_nc_vPT);
   fChain->SetBranchAddress("Ds_0.60_nc_sPT", &Ds_0_60_nc_sPT, &b_Ds_0_60_nc_sPT);
   fChain->SetBranchAddress("Ds_0.60_nc_maxPt_PX", &Ds_0_60_nc_maxPt_PX, &b_Ds_0_60_nc_maxPt_PX);
   fChain->SetBranchAddress("Ds_0.60_nc_maxPt_PY", &Ds_0_60_nc_maxPt_PY, &b_Ds_0_60_nc_maxPt_PY);
   fChain->SetBranchAddress("Ds_0.60_nc_maxPt_PZ", &Ds_0_60_nc_maxPt_PZ, &b_Ds_0_60_nc_maxPt_PZ);
   fChain->SetBranchAddress("Ds_0.30_cc_mult", &Ds_0_30_cc_mult, &b_Ds_0_30_cc_mult);
   fChain->SetBranchAddress("Ds_0.30_cc_PX", &Ds_0_30_cc_PX, &b_Ds_0_30_cc_PX);
   fChain->SetBranchAddress("Ds_0.30_cc_PY", &Ds_0_30_cc_PY, &b_Ds_0_30_cc_PY);
   fChain->SetBranchAddress("Ds_0.30_cc_PZ", &Ds_0_30_cc_PZ, &b_Ds_0_30_cc_PZ);
   fChain->SetBranchAddress("Ds_0.30_cc_vPT", &Ds_0_30_cc_vPT, &b_Ds_0_30_cc_vPT);
   fChain->SetBranchAddress("Ds_0.30_cc_sPT", &Ds_0_30_cc_sPT, &b_Ds_0_30_cc_sPT);
   fChain->SetBranchAddress("Ds_0.30_nc_mult", &Ds_0_30_nc_mult, &b_Ds_0_30_nc_mult);
   fChain->SetBranchAddress("Ds_0.30_nc_PX", &Ds_0_30_nc_PX, &b_Ds_0_30_nc_PX);
   fChain->SetBranchAddress("Ds_0.30_nc_PY", &Ds_0_30_nc_PY, &b_Ds_0_30_nc_PY);
   fChain->SetBranchAddress("Ds_0.30_nc_PZ", &Ds_0_30_nc_PZ, &b_Ds_0_30_nc_PZ);
   fChain->SetBranchAddress("Ds_0.30_nc_vPT", &Ds_0_30_nc_vPT, &b_Ds_0_30_nc_vPT);
   fChain->SetBranchAddress("Ds_0.30_nc_sPT", &Ds_0_30_nc_sPT, &b_Ds_0_30_nc_sPT);
   fChain->SetBranchAddress("Ds_0.30_nc_maxPt_PX", &Ds_0_30_nc_maxPt_PX, &b_Ds_0_30_nc_maxPt_PX);
   fChain->SetBranchAddress("Ds_0.30_nc_maxPt_PY", &Ds_0_30_nc_maxPt_PY, &b_Ds_0_30_nc_maxPt_PY);
   fChain->SetBranchAddress("Ds_0.30_nc_maxPt_PZ", &Ds_0_30_nc_maxPt_PZ, &b_Ds_0_30_nc_maxPt_PZ);
   fChain->SetBranchAddress("Ds_MINIP", &Ds_MINIP, &b_Ds_MINIP);
   fChain->SetBranchAddress("Ds_MINIPCHI2", &Ds_MINIPCHI2, &b_Ds_MINIPCHI2);
   fChain->SetBranchAddress("Ds_MINIPNEXTBEST", &Ds_MINIPNEXTBEST, &b_Ds_MINIPNEXTBEST);
   fChain->SetBranchAddress("Ds_MINIPCHI2NEXTBEST", &Ds_MINIPCHI2NEXTBEST, &b_Ds_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("Ds_ENDVERTEX_X", &Ds_ENDVERTEX_X, &b_Ds_ENDVERTEX_X);
   fChain->SetBranchAddress("Ds_ENDVERTEX_Y", &Ds_ENDVERTEX_Y, &b_Ds_ENDVERTEX_Y);
   fChain->SetBranchAddress("Ds_ENDVERTEX_Z", &Ds_ENDVERTEX_Z, &b_Ds_ENDVERTEX_Z);
   fChain->SetBranchAddress("Ds_ENDVERTEX_XERR", &Ds_ENDVERTEX_XERR, &b_Ds_ENDVERTEX_XERR);
   fChain->SetBranchAddress("Ds_ENDVERTEX_YERR", &Ds_ENDVERTEX_YERR, &b_Ds_ENDVERTEX_YERR);
   fChain->SetBranchAddress("Ds_ENDVERTEX_ZERR", &Ds_ENDVERTEX_ZERR, &b_Ds_ENDVERTEX_ZERR);
   fChain->SetBranchAddress("Ds_ENDVERTEX_CHI2", &Ds_ENDVERTEX_CHI2, &b_Ds_ENDVERTEX_CHI2);
   fChain->SetBranchAddress("Ds_ENDVERTEX_NDOF", &Ds_ENDVERTEX_NDOF, &b_Ds_ENDVERTEX_NDOF);
   fChain->SetBranchAddress("Ds_ENDVERTEX_COV_", Ds_ENDVERTEX_COV_, &b_Ds_ENDVERTEX_COV_);
   fChain->SetBranchAddress("Ds_OWNPV_X", &Ds_OWNPV_X, &b_Ds_OWNPV_X);
   fChain->SetBranchAddress("Ds_OWNPV_Y", &Ds_OWNPV_Y, &b_Ds_OWNPV_Y);
   fChain->SetBranchAddress("Ds_OWNPV_Z", &Ds_OWNPV_Z, &b_Ds_OWNPV_Z);
   fChain->SetBranchAddress("Ds_OWNPV_XERR", &Ds_OWNPV_XERR, &b_Ds_OWNPV_XERR);
   fChain->SetBranchAddress("Ds_OWNPV_YERR", &Ds_OWNPV_YERR, &b_Ds_OWNPV_YERR);
   fChain->SetBranchAddress("Ds_OWNPV_ZERR", &Ds_OWNPV_ZERR, &b_Ds_OWNPV_ZERR);
   fChain->SetBranchAddress("Ds_OWNPV_CHI2", &Ds_OWNPV_CHI2, &b_Ds_OWNPV_CHI2);
   fChain->SetBranchAddress("Ds_OWNPV_NDOF", &Ds_OWNPV_NDOF, &b_Ds_OWNPV_NDOF);
   fChain->SetBranchAddress("Ds_OWNPV_COV_", Ds_OWNPV_COV_, &b_Ds_OWNPV_COV_);
   fChain->SetBranchAddress("Ds_IP_OWNPV", &Ds_IP_OWNPV, &b_Ds_IP_OWNPV);
   fChain->SetBranchAddress("Ds_IPCHI2_OWNPV", &Ds_IPCHI2_OWNPV, &b_Ds_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Ds_FD_OWNPV", &Ds_FD_OWNPV, &b_Ds_FD_OWNPV);
   fChain->SetBranchAddress("Ds_FDCHI2_OWNPV", &Ds_FDCHI2_OWNPV, &b_Ds_FDCHI2_OWNPV);
   fChain->SetBranchAddress("Ds_DIRA_OWNPV", &Ds_DIRA_OWNPV, &b_Ds_DIRA_OWNPV);
   fChain->SetBranchAddress("Ds_TOPPV_X", &Ds_TOPPV_X, &b_Ds_TOPPV_X);
   fChain->SetBranchAddress("Ds_TOPPV_Y", &Ds_TOPPV_Y, &b_Ds_TOPPV_Y);
   fChain->SetBranchAddress("Ds_TOPPV_Z", &Ds_TOPPV_Z, &b_Ds_TOPPV_Z);
   fChain->SetBranchAddress("Ds_TOPPV_XERR", &Ds_TOPPV_XERR, &b_Ds_TOPPV_XERR);
   fChain->SetBranchAddress("Ds_TOPPV_YERR", &Ds_TOPPV_YERR, &b_Ds_TOPPV_YERR);
   fChain->SetBranchAddress("Ds_TOPPV_ZERR", &Ds_TOPPV_ZERR, &b_Ds_TOPPV_ZERR);
   fChain->SetBranchAddress("Ds_TOPPV_CHI2", &Ds_TOPPV_CHI2, &b_Ds_TOPPV_CHI2);
   fChain->SetBranchAddress("Ds_TOPPV_NDOF", &Ds_TOPPV_NDOF, &b_Ds_TOPPV_NDOF);
   fChain->SetBranchAddress("Ds_TOPPV_COV_", Ds_TOPPV_COV_, &b_Ds_TOPPV_COV_);
   fChain->SetBranchAddress("Ds_IP_TOPPV", &Ds_IP_TOPPV, &b_Ds_IP_TOPPV);
   fChain->SetBranchAddress("Ds_IPCHI2_TOPPV", &Ds_IPCHI2_TOPPV, &b_Ds_IPCHI2_TOPPV);
   fChain->SetBranchAddress("Ds_FD_TOPPV", &Ds_FD_TOPPV, &b_Ds_FD_TOPPV);
   fChain->SetBranchAddress("Ds_FDCHI2_TOPPV", &Ds_FDCHI2_TOPPV, &b_Ds_FDCHI2_TOPPV);
   fChain->SetBranchAddress("Ds_DIRA_TOPPV", &Ds_DIRA_TOPPV, &b_Ds_DIRA_TOPPV);
   fChain->SetBranchAddress("Ds_ORIVX_X", &Ds_ORIVX_X, &b_Ds_ORIVX_X);
   fChain->SetBranchAddress("Ds_ORIVX_Y", &Ds_ORIVX_Y, &b_Ds_ORIVX_Y);
   fChain->SetBranchAddress("Ds_ORIVX_Z", &Ds_ORIVX_Z, &b_Ds_ORIVX_Z);
   fChain->SetBranchAddress("Ds_ORIVX_XERR", &Ds_ORIVX_XERR, &b_Ds_ORIVX_XERR);
   fChain->SetBranchAddress("Ds_ORIVX_YERR", &Ds_ORIVX_YERR, &b_Ds_ORIVX_YERR);
   fChain->SetBranchAddress("Ds_ORIVX_ZERR", &Ds_ORIVX_ZERR, &b_Ds_ORIVX_ZERR);
   fChain->SetBranchAddress("Ds_ORIVX_CHI2", &Ds_ORIVX_CHI2, &b_Ds_ORIVX_CHI2);
   fChain->SetBranchAddress("Ds_ORIVX_NDOF", &Ds_ORIVX_NDOF, &b_Ds_ORIVX_NDOF);
   fChain->SetBranchAddress("Ds_ORIVX_COV_", Ds_ORIVX_COV_, &b_Ds_ORIVX_COV_);
   fChain->SetBranchAddress("Ds_IP_ORIVX", &Ds_IP_ORIVX, &b_Ds_IP_ORIVX);
   fChain->SetBranchAddress("Ds_IPCHI2_ORIVX", &Ds_IPCHI2_ORIVX, &b_Ds_IPCHI2_ORIVX);
   fChain->SetBranchAddress("Ds_FD_ORIVX", &Ds_FD_ORIVX, &b_Ds_FD_ORIVX);
   fChain->SetBranchAddress("Ds_FDCHI2_ORIVX", &Ds_FDCHI2_ORIVX, &b_Ds_FDCHI2_ORIVX);
   fChain->SetBranchAddress("Ds_DIRA_ORIVX", &Ds_DIRA_ORIVX, &b_Ds_DIRA_ORIVX);
   fChain->SetBranchAddress("Ds_P", &Ds_P, &b_Ds_P);
   fChain->SetBranchAddress("Ds_PT", &Ds_PT, &b_Ds_PT);
   fChain->SetBranchAddress("Ds_PE", &Ds_PE, &b_Ds_PE);
   fChain->SetBranchAddress("Ds_PX", &Ds_PX, &b_Ds_PX);
   fChain->SetBranchAddress("Ds_PY", &Ds_PY, &b_Ds_PY);
   fChain->SetBranchAddress("Ds_PZ", &Ds_PZ, &b_Ds_PZ);
   fChain->SetBranchAddress("Ds_MM", &Ds_MM, &b_Ds_MM);
   fChain->SetBranchAddress("Ds_MMERR", &Ds_MMERR, &b_Ds_MMERR);
   fChain->SetBranchAddress("Ds_M", &Ds_M, &b_Ds_M);
   fChain->SetBranchAddress("Ds_ID", &Ds_ID, &b_Ds_ID);
   fChain->SetBranchAddress("Ds_eta", &Ds_eta, &b_Ds_eta);
   fChain->SetBranchAddress("Ds_phi", &Ds_phi, &b_Ds_phi);
   fChain->SetBranchAddress("Ds_TAU", &Ds_TAU, &b_Ds_TAU);
   fChain->SetBranchAddress("Ds_TAUERR", &Ds_TAUERR, &b_Ds_TAUERR);
   fChain->SetBranchAddress("Ds_TAUCHI2", &Ds_TAUCHI2, &b_Ds_TAUCHI2);
   fChain->SetBranchAddress("Ds_NumVtxWithinChi2WindowOneTrack", &Ds_NumVtxWithinChi2WindowOneTrack, &b_Ds_NumVtxWithinChi2WindowOneTrack);
   fChain->SetBranchAddress("Ds_SmallestDeltaChi2OneTrack", &Ds_SmallestDeltaChi2OneTrack, &b_Ds_SmallestDeltaChi2OneTrack);
   fChain->SetBranchAddress("Ds_SmallestDeltaChi2MassOneTrack", &Ds_SmallestDeltaChi2MassOneTrack, &b_Ds_SmallestDeltaChi2MassOneTrack);
   fChain->SetBranchAddress("Ds_SmallestDeltaChi2TwoTracks", &Ds_SmallestDeltaChi2TwoTracks, &b_Ds_SmallestDeltaChi2TwoTracks);
   fChain->SetBranchAddress("Ds_SmallestDeltaChi2MassTwoTracks", &Ds_SmallestDeltaChi2MassTwoTracks, &b_Ds_SmallestDeltaChi2MassTwoTracks);
   fChain->SetBranchAddress("Kmi_MC12TuneV2_ProbNNe", &Kmi_MC12TuneV2_ProbNNe, &b_Kmi_MC12TuneV2_ProbNNe);
   fChain->SetBranchAddress("Kmi_MC12TuneV2_ProbNNmu", &Kmi_MC12TuneV2_ProbNNmu, &b_Kmi_MC12TuneV2_ProbNNmu);
   fChain->SetBranchAddress("Kmi_MC12TuneV2_ProbNNpi", &Kmi_MC12TuneV2_ProbNNpi, &b_Kmi_MC12TuneV2_ProbNNpi);
   fChain->SetBranchAddress("Kmi_MC12TuneV2_ProbNNk", &Kmi_MC12TuneV2_ProbNNk, &b_Kmi_MC12TuneV2_ProbNNk);
   fChain->SetBranchAddress("Kmi_MC12TuneV2_ProbNNp", &Kmi_MC12TuneV2_ProbNNp, &b_Kmi_MC12TuneV2_ProbNNp);
   fChain->SetBranchAddress("Kmi_MC12TuneV2_ProbNNghost", &Kmi_MC12TuneV2_ProbNNghost, &b_Kmi_MC12TuneV2_ProbNNghost);
   fChain->SetBranchAddress("Kmi_MC12TuneV3_ProbNNe", &Kmi_MC12TuneV3_ProbNNe, &b_Kmi_MC12TuneV3_ProbNNe);
   fChain->SetBranchAddress("Kmi_MC12TuneV3_ProbNNmu", &Kmi_MC12TuneV3_ProbNNmu, &b_Kmi_MC12TuneV3_ProbNNmu);
   fChain->SetBranchAddress("Kmi_MC12TuneV3_ProbNNpi", &Kmi_MC12TuneV3_ProbNNpi, &b_Kmi_MC12TuneV3_ProbNNpi);
   fChain->SetBranchAddress("Kmi_MC12TuneV3_ProbNNk", &Kmi_MC12TuneV3_ProbNNk, &b_Kmi_MC12TuneV3_ProbNNk);
   fChain->SetBranchAddress("Kmi_MC12TuneV3_ProbNNp", &Kmi_MC12TuneV3_ProbNNp, &b_Kmi_MC12TuneV3_ProbNNp);
   fChain->SetBranchAddress("Kmi_MC12TuneV3_ProbNNghost", &Kmi_MC12TuneV3_ProbNNghost, &b_Kmi_MC12TuneV3_ProbNNghost);
   fChain->SetBranchAddress("Kmi_MINIP", &Kmi_MINIP, &b_Kmi_MINIP);
   fChain->SetBranchAddress("Kmi_MINIPCHI2", &Kmi_MINIPCHI2, &b_Kmi_MINIPCHI2);
   fChain->SetBranchAddress("Kmi_MINIPNEXTBEST", &Kmi_MINIPNEXTBEST, &b_Kmi_MINIPNEXTBEST);
   fChain->SetBranchAddress("Kmi_MINIPCHI2NEXTBEST", &Kmi_MINIPCHI2NEXTBEST, &b_Kmi_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("Kmi_OWNPV_X", &Kmi_OWNPV_X, &b_Kmi_OWNPV_X);
   fChain->SetBranchAddress("Kmi_OWNPV_Y", &Kmi_OWNPV_Y, &b_Kmi_OWNPV_Y);
   fChain->SetBranchAddress("Kmi_OWNPV_Z", &Kmi_OWNPV_Z, &b_Kmi_OWNPV_Z);
   fChain->SetBranchAddress("Kmi_OWNPV_XERR", &Kmi_OWNPV_XERR, &b_Kmi_OWNPV_XERR);
   fChain->SetBranchAddress("Kmi_OWNPV_YERR", &Kmi_OWNPV_YERR, &b_Kmi_OWNPV_YERR);
   fChain->SetBranchAddress("Kmi_OWNPV_ZERR", &Kmi_OWNPV_ZERR, &b_Kmi_OWNPV_ZERR);
   fChain->SetBranchAddress("Kmi_OWNPV_CHI2", &Kmi_OWNPV_CHI2, &b_Kmi_OWNPV_CHI2);
   fChain->SetBranchAddress("Kmi_OWNPV_NDOF", &Kmi_OWNPV_NDOF, &b_Kmi_OWNPV_NDOF);
   fChain->SetBranchAddress("Kmi_OWNPV_COV_", Kmi_OWNPV_COV_, &b_Kmi_OWNPV_COV_);
   fChain->SetBranchAddress("Kmi_IP_OWNPV", &Kmi_IP_OWNPV, &b_Kmi_IP_OWNPV);
   fChain->SetBranchAddress("Kmi_IPCHI2_OWNPV", &Kmi_IPCHI2_OWNPV, &b_Kmi_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Kmi_TOPPV_X", &Kmi_TOPPV_X, &b_Kmi_TOPPV_X);
   fChain->SetBranchAddress("Kmi_TOPPV_Y", &Kmi_TOPPV_Y, &b_Kmi_TOPPV_Y);
   fChain->SetBranchAddress("Kmi_TOPPV_Z", &Kmi_TOPPV_Z, &b_Kmi_TOPPV_Z);
   fChain->SetBranchAddress("Kmi_TOPPV_XERR", &Kmi_TOPPV_XERR, &b_Kmi_TOPPV_XERR);
   fChain->SetBranchAddress("Kmi_TOPPV_YERR", &Kmi_TOPPV_YERR, &b_Kmi_TOPPV_YERR);
   fChain->SetBranchAddress("Kmi_TOPPV_ZERR", &Kmi_TOPPV_ZERR, &b_Kmi_TOPPV_ZERR);
   fChain->SetBranchAddress("Kmi_TOPPV_CHI2", &Kmi_TOPPV_CHI2, &b_Kmi_TOPPV_CHI2);
   fChain->SetBranchAddress("Kmi_TOPPV_NDOF", &Kmi_TOPPV_NDOF, &b_Kmi_TOPPV_NDOF);
   fChain->SetBranchAddress("Kmi_TOPPV_COV_", Kmi_TOPPV_COV_, &b_Kmi_TOPPV_COV_);
   fChain->SetBranchAddress("Kmi_IP_TOPPV", &Kmi_IP_TOPPV, &b_Kmi_IP_TOPPV);
   fChain->SetBranchAddress("Kmi_IPCHI2_TOPPV", &Kmi_IPCHI2_TOPPV, &b_Kmi_IPCHI2_TOPPV);
   fChain->SetBranchAddress("Kmi_ORIVX_X", &Kmi_ORIVX_X, &b_Kmi_ORIVX_X);
   fChain->SetBranchAddress("Kmi_ORIVX_Y", &Kmi_ORIVX_Y, &b_Kmi_ORIVX_Y);
   fChain->SetBranchAddress("Kmi_ORIVX_Z", &Kmi_ORIVX_Z, &b_Kmi_ORIVX_Z);
   fChain->SetBranchAddress("Kmi_ORIVX_XERR", &Kmi_ORIVX_XERR, &b_Kmi_ORIVX_XERR);
   fChain->SetBranchAddress("Kmi_ORIVX_YERR", &Kmi_ORIVX_YERR, &b_Kmi_ORIVX_YERR);
   fChain->SetBranchAddress("Kmi_ORIVX_ZERR", &Kmi_ORIVX_ZERR, &b_Kmi_ORIVX_ZERR);
   fChain->SetBranchAddress("Kmi_ORIVX_CHI2", &Kmi_ORIVX_CHI2, &b_Kmi_ORIVX_CHI2);
   fChain->SetBranchAddress("Kmi_ORIVX_NDOF", &Kmi_ORIVX_NDOF, &b_Kmi_ORIVX_NDOF);
   fChain->SetBranchAddress("Kmi_ORIVX_COV_", Kmi_ORIVX_COV_, &b_Kmi_ORIVX_COV_);
   fChain->SetBranchAddress("Kmi_IP_ORIVX", &Kmi_IP_ORIVX, &b_Kmi_IP_ORIVX);
   fChain->SetBranchAddress("Kmi_IPCHI2_ORIVX", &Kmi_IPCHI2_ORIVX, &b_Kmi_IPCHI2_ORIVX);
   fChain->SetBranchAddress("Kmi_P", &Kmi_P, &b_Kmi_P);
   fChain->SetBranchAddress("Kmi_PT", &Kmi_PT, &b_Kmi_PT);
   fChain->SetBranchAddress("Kmi_PE", &Kmi_PE, &b_Kmi_PE);
   fChain->SetBranchAddress("Kmi_PX", &Kmi_PX, &b_Kmi_PX);
   fChain->SetBranchAddress("Kmi_PY", &Kmi_PY, &b_Kmi_PY);
   fChain->SetBranchAddress("Kmi_PZ", &Kmi_PZ, &b_Kmi_PZ);
   fChain->SetBranchAddress("Kmi_M", &Kmi_M, &b_Kmi_M);
   fChain->SetBranchAddress("Kmi_ID", &Kmi_ID, &b_Kmi_ID);
   fChain->SetBranchAddress("Kmi_eta", &Kmi_eta, &b_Kmi_eta);
   fChain->SetBranchAddress("Kmi_phi", &Kmi_phi, &b_Kmi_phi);
   fChain->SetBranchAddress("Kmi_PIDe", &Kmi_PIDe, &b_Kmi_PIDe);
   fChain->SetBranchAddress("Kmi_PIDmu", &Kmi_PIDmu, &b_Kmi_PIDmu);
   fChain->SetBranchAddress("Kmi_PIDK", &Kmi_PIDK, &b_Kmi_PIDK);
   fChain->SetBranchAddress("Kmi_PIDp", &Kmi_PIDp, &b_Kmi_PIDp);
   fChain->SetBranchAddress("Kmi_ProbNNe", &Kmi_ProbNNe, &b_Kmi_ProbNNe);
   fChain->SetBranchAddress("Kmi_ProbNNk", &Kmi_ProbNNk, &b_Kmi_ProbNNk);
   fChain->SetBranchAddress("Kmi_ProbNNp", &Kmi_ProbNNp, &b_Kmi_ProbNNp);
   fChain->SetBranchAddress("Kmi_ProbNNpi", &Kmi_ProbNNpi, &b_Kmi_ProbNNpi);
   fChain->SetBranchAddress("Kmi_ProbNNmu", &Kmi_ProbNNmu, &b_Kmi_ProbNNmu);
   fChain->SetBranchAddress("Kmi_ProbNNghost", &Kmi_ProbNNghost, &b_Kmi_ProbNNghost);
   fChain->SetBranchAddress("Kmi_hasMuon", &Kmi_hasMuon, &b_Kmi_hasMuon);
   fChain->SetBranchAddress("Kmi_isMuon", &Kmi_isMuon, &b_Kmi_isMuon);
   fChain->SetBranchAddress("Kmi_hasRich", &Kmi_hasRich, &b_Kmi_hasRich);
   fChain->SetBranchAddress("Kmi_hasCalo", &Kmi_hasCalo, &b_Kmi_hasCalo);
   fChain->SetBranchAddress("Kmi_SV_X", &Kmi_SV_X, &b_Kmi_SV_X);
   fChain->SetBranchAddress("Kmi_SV_Y", &Kmi_SV_Y, &b_Kmi_SV_Y);
   fChain->SetBranchAddress("Kmi_SV_Z", &Kmi_SV_Z, &b_Kmi_SV_Z);
   fChain->SetBranchAddress("Kmi_SV_XERR", &Kmi_SV_XERR, &b_Kmi_SV_XERR);
   fChain->SetBranchAddress("Kmi_SV_YERR", &Kmi_SV_YERR, &b_Kmi_SV_YERR);
   fChain->SetBranchAddress("Kmi_SV_ZERR", &Kmi_SV_ZERR, &b_Kmi_SV_ZERR);
   fChain->SetBranchAddress("Kmi_SV_CHI2", &Kmi_SV_CHI2, &b_Kmi_SV_CHI2);
   fChain->SetBranchAddress("Kmi_SV_NDOF", &Kmi_SV_NDOF, &b_Kmi_SV_NDOF);
   fChain->SetBranchAddress("Kmi_SV_COV_", Kmi_SV_COV_, &b_Kmi_SV_COV_);
   fChain->SetBranchAddress("Kmi_PV_X", &Kmi_PV_X, &b_Kmi_PV_X);
   fChain->SetBranchAddress("Kmi_PV_Y", &Kmi_PV_Y, &b_Kmi_PV_Y);
   fChain->SetBranchAddress("Kmi_PV_Z", &Kmi_PV_Z, &b_Kmi_PV_Z);
   fChain->SetBranchAddress("Kmi_PV_CHI2", &Kmi_PV_CHI2, &b_Kmi_PV_CHI2);
   fChain->SetBranchAddress("Kmi_PV_NDOF", &Kmi_PV_NDOF, &b_Kmi_PV_NDOF);
   fChain->SetBranchAddress("Kmi_PV_COV_", Kmi_PV_COV_, &b_Kmi_PV_COV_);
   fChain->SetBranchAddress("Kmi_MOM_COV_", Kmi_MOM_COV_, &b_Kmi_MOM_COV_);
   fChain->SetBranchAddress("Kmi_POSMOM_COV_", Kmi_POSMOM_COV_, &b_Kmi_POSMOM_COV_);
   fChain->SetBranchAddress("Kmi_MCORR", &Kmi_MCORR, &b_Kmi_MCORR);
   fChain->SetBranchAddress("Kmi_MCORRERR", &Kmi_MCORRERR, &b_Kmi_MCORRERR);
   fChain->SetBranchAddress("Kmi_MCORRFULLERR", &Kmi_MCORRFULLERR, &b_Kmi_MCORRFULLERR);
   fChain->SetBranchAddress("Kmi_Q2SOL1", &Kmi_Q2SOL1, &b_Kmi_Q2SOL1);
   fChain->SetBranchAddress("Kmi_Q2SOL2", &Kmi_Q2SOL2, &b_Kmi_Q2SOL2);
   fChain->SetBranchAddress("Kmi_TRACK_Type", &Kmi_TRACK_Type, &b_Kmi_TRACK_Type);
   fChain->SetBranchAddress("Kmi_TRACK_Key", &Kmi_TRACK_Key, &b_Kmi_TRACK_Key);
   fChain->SetBranchAddress("Kmi_TRACK_CHI2NDOF", &Kmi_TRACK_CHI2NDOF, &b_Kmi_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("Kmi_TRACK_PCHI2", &Kmi_TRACK_PCHI2, &b_Kmi_TRACK_PCHI2);
   fChain->SetBranchAddress("Kmi_TRACK_MatchCHI2", &Kmi_TRACK_MatchCHI2, &b_Kmi_TRACK_MatchCHI2);
   fChain->SetBranchAddress("Kmi_TRACK_GhostProb", &Kmi_TRACK_GhostProb, &b_Kmi_TRACK_GhostProb);
   fChain->SetBranchAddress("Kmi_TRACK_CloneDist", &Kmi_TRACK_CloneDist, &b_Kmi_TRACK_CloneDist);
   fChain->SetBranchAddress("Kmi_TRACK_Likelihood", &Kmi_TRACK_Likelihood, &b_Kmi_TRACK_Likelihood);
   fChain->SetBranchAddress("Kpl_MC12TuneV2_ProbNNe", &Kpl_MC12TuneV2_ProbNNe, &b_Kpl_MC12TuneV2_ProbNNe);
   fChain->SetBranchAddress("Kpl_MC12TuneV2_ProbNNmu", &Kpl_MC12TuneV2_ProbNNmu, &b_Kpl_MC12TuneV2_ProbNNmu);
   fChain->SetBranchAddress("Kpl_MC12TuneV2_ProbNNpi", &Kpl_MC12TuneV2_ProbNNpi, &b_Kpl_MC12TuneV2_ProbNNpi);
   fChain->SetBranchAddress("Kpl_MC12TuneV2_ProbNNk", &Kpl_MC12TuneV2_ProbNNk, &b_Kpl_MC12TuneV2_ProbNNk);
   fChain->SetBranchAddress("Kpl_MC12TuneV2_ProbNNp", &Kpl_MC12TuneV2_ProbNNp, &b_Kpl_MC12TuneV2_ProbNNp);
   fChain->SetBranchAddress("Kpl_MC12TuneV2_ProbNNghost", &Kpl_MC12TuneV2_ProbNNghost, &b_Kpl_MC12TuneV2_ProbNNghost);
   fChain->SetBranchAddress("Kpl_MC12TuneV3_ProbNNe", &Kpl_MC12TuneV3_ProbNNe, &b_Kpl_MC12TuneV3_ProbNNe);
   fChain->SetBranchAddress("Kpl_MC12TuneV3_ProbNNmu", &Kpl_MC12TuneV3_ProbNNmu, &b_Kpl_MC12TuneV3_ProbNNmu);
   fChain->SetBranchAddress("Kpl_MC12TuneV3_ProbNNpi", &Kpl_MC12TuneV3_ProbNNpi, &b_Kpl_MC12TuneV3_ProbNNpi);
   fChain->SetBranchAddress("Kpl_MC12TuneV3_ProbNNk", &Kpl_MC12TuneV3_ProbNNk, &b_Kpl_MC12TuneV3_ProbNNk);
   fChain->SetBranchAddress("Kpl_MC12TuneV3_ProbNNp", &Kpl_MC12TuneV3_ProbNNp, &b_Kpl_MC12TuneV3_ProbNNp);
   fChain->SetBranchAddress("Kpl_MC12TuneV3_ProbNNghost", &Kpl_MC12TuneV3_ProbNNghost, &b_Kpl_MC12TuneV3_ProbNNghost);
   fChain->SetBranchAddress("Kpl_MINIP", &Kpl_MINIP, &b_Kpl_MINIP);
   fChain->SetBranchAddress("Kpl_MINIPCHI2", &Kpl_MINIPCHI2, &b_Kpl_MINIPCHI2);
   fChain->SetBranchAddress("Kpl_MINIPNEXTBEST", &Kpl_MINIPNEXTBEST, &b_Kpl_MINIPNEXTBEST);
   fChain->SetBranchAddress("Kpl_MINIPCHI2NEXTBEST", &Kpl_MINIPCHI2NEXTBEST, &b_Kpl_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("Kpl_OWNPV_X", &Kpl_OWNPV_X, &b_Kpl_OWNPV_X);
   fChain->SetBranchAddress("Kpl_OWNPV_Y", &Kpl_OWNPV_Y, &b_Kpl_OWNPV_Y);
   fChain->SetBranchAddress("Kpl_OWNPV_Z", &Kpl_OWNPV_Z, &b_Kpl_OWNPV_Z);
   fChain->SetBranchAddress("Kpl_OWNPV_XERR", &Kpl_OWNPV_XERR, &b_Kpl_OWNPV_XERR);
   fChain->SetBranchAddress("Kpl_OWNPV_YERR", &Kpl_OWNPV_YERR, &b_Kpl_OWNPV_YERR);
   fChain->SetBranchAddress("Kpl_OWNPV_ZERR", &Kpl_OWNPV_ZERR, &b_Kpl_OWNPV_ZERR);
   fChain->SetBranchAddress("Kpl_OWNPV_CHI2", &Kpl_OWNPV_CHI2, &b_Kpl_OWNPV_CHI2);
   fChain->SetBranchAddress("Kpl_OWNPV_NDOF", &Kpl_OWNPV_NDOF, &b_Kpl_OWNPV_NDOF);
   fChain->SetBranchAddress("Kpl_OWNPV_COV_", Kpl_OWNPV_COV_, &b_Kpl_OWNPV_COV_);
   fChain->SetBranchAddress("Kpl_IP_OWNPV", &Kpl_IP_OWNPV, &b_Kpl_IP_OWNPV);
   fChain->SetBranchAddress("Kpl_IPCHI2_OWNPV", &Kpl_IPCHI2_OWNPV, &b_Kpl_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Kpl_TOPPV_X", &Kpl_TOPPV_X, &b_Kpl_TOPPV_X);
   fChain->SetBranchAddress("Kpl_TOPPV_Y", &Kpl_TOPPV_Y, &b_Kpl_TOPPV_Y);
   fChain->SetBranchAddress("Kpl_TOPPV_Z", &Kpl_TOPPV_Z, &b_Kpl_TOPPV_Z);
   fChain->SetBranchAddress("Kpl_TOPPV_XERR", &Kpl_TOPPV_XERR, &b_Kpl_TOPPV_XERR);
   fChain->SetBranchAddress("Kpl_TOPPV_YERR", &Kpl_TOPPV_YERR, &b_Kpl_TOPPV_YERR);
   fChain->SetBranchAddress("Kpl_TOPPV_ZERR", &Kpl_TOPPV_ZERR, &b_Kpl_TOPPV_ZERR);
   fChain->SetBranchAddress("Kpl_TOPPV_CHI2", &Kpl_TOPPV_CHI2, &b_Kpl_TOPPV_CHI2);
   fChain->SetBranchAddress("Kpl_TOPPV_NDOF", &Kpl_TOPPV_NDOF, &b_Kpl_TOPPV_NDOF);
   fChain->SetBranchAddress("Kpl_TOPPV_COV_", Kpl_TOPPV_COV_, &b_Kpl_TOPPV_COV_);
   fChain->SetBranchAddress("Kpl_IP_TOPPV", &Kpl_IP_TOPPV, &b_Kpl_IP_TOPPV);
   fChain->SetBranchAddress("Kpl_IPCHI2_TOPPV", &Kpl_IPCHI2_TOPPV, &b_Kpl_IPCHI2_TOPPV);
   fChain->SetBranchAddress("Kpl_ORIVX_X", &Kpl_ORIVX_X, &b_Kpl_ORIVX_X);
   fChain->SetBranchAddress("Kpl_ORIVX_Y", &Kpl_ORIVX_Y, &b_Kpl_ORIVX_Y);
   fChain->SetBranchAddress("Kpl_ORIVX_Z", &Kpl_ORIVX_Z, &b_Kpl_ORIVX_Z);
   fChain->SetBranchAddress("Kpl_ORIVX_XERR", &Kpl_ORIVX_XERR, &b_Kpl_ORIVX_XERR);
   fChain->SetBranchAddress("Kpl_ORIVX_YERR", &Kpl_ORIVX_YERR, &b_Kpl_ORIVX_YERR);
   fChain->SetBranchAddress("Kpl_ORIVX_ZERR", &Kpl_ORIVX_ZERR, &b_Kpl_ORIVX_ZERR);
   fChain->SetBranchAddress("Kpl_ORIVX_CHI2", &Kpl_ORIVX_CHI2, &b_Kpl_ORIVX_CHI2);
   fChain->SetBranchAddress("Kpl_ORIVX_NDOF", &Kpl_ORIVX_NDOF, &b_Kpl_ORIVX_NDOF);
   fChain->SetBranchAddress("Kpl_ORIVX_COV_", Kpl_ORIVX_COV_, &b_Kpl_ORIVX_COV_);
   fChain->SetBranchAddress("Kpl_IP_ORIVX", &Kpl_IP_ORIVX, &b_Kpl_IP_ORIVX);
   fChain->SetBranchAddress("Kpl_IPCHI2_ORIVX", &Kpl_IPCHI2_ORIVX, &b_Kpl_IPCHI2_ORIVX);
   fChain->SetBranchAddress("Kpl_P", &Kpl_P, &b_Kpl_P);
   fChain->SetBranchAddress("Kpl_PT", &Kpl_PT, &b_Kpl_PT);
   fChain->SetBranchAddress("Kpl_PE", &Kpl_PE, &b_Kpl_PE);
   fChain->SetBranchAddress("Kpl_PX", &Kpl_PX, &b_Kpl_PX);
   fChain->SetBranchAddress("Kpl_PY", &Kpl_PY, &b_Kpl_PY);
   fChain->SetBranchAddress("Kpl_PZ", &Kpl_PZ, &b_Kpl_PZ);
   fChain->SetBranchAddress("Kpl_M", &Kpl_M, &b_Kpl_M);
   fChain->SetBranchAddress("Kpl_ID", &Kpl_ID, &b_Kpl_ID);
   fChain->SetBranchAddress("Kpl_eta", &Kpl_eta, &b_Kpl_eta);
   fChain->SetBranchAddress("Kpl_phi", &Kpl_phi, &b_Kpl_phi);
   fChain->SetBranchAddress("Kpl_PIDe", &Kpl_PIDe, &b_Kpl_PIDe);
   fChain->SetBranchAddress("Kpl_PIDmu", &Kpl_PIDmu, &b_Kpl_PIDmu);
   fChain->SetBranchAddress("Kpl_PIDK", &Kpl_PIDK, &b_Kpl_PIDK);
   fChain->SetBranchAddress("Kpl_PIDp", &Kpl_PIDp, &b_Kpl_PIDp);
   fChain->SetBranchAddress("Kpl_ProbNNe", &Kpl_ProbNNe, &b_Kpl_ProbNNe);
   fChain->SetBranchAddress("Kpl_ProbNNk", &Kpl_ProbNNk, &b_Kpl_ProbNNk);
   fChain->SetBranchAddress("Kpl_ProbNNp", &Kpl_ProbNNp, &b_Kpl_ProbNNp);
   fChain->SetBranchAddress("Kpl_ProbNNpi", &Kpl_ProbNNpi, &b_Kpl_ProbNNpi);
   fChain->SetBranchAddress("Kpl_ProbNNmu", &Kpl_ProbNNmu, &b_Kpl_ProbNNmu);
   fChain->SetBranchAddress("Kpl_ProbNNghost", &Kpl_ProbNNghost, &b_Kpl_ProbNNghost);
   fChain->SetBranchAddress("Kpl_hasMuon", &Kpl_hasMuon, &b_Kpl_hasMuon);
   fChain->SetBranchAddress("Kpl_isMuon", &Kpl_isMuon, &b_Kpl_isMuon);
   fChain->SetBranchAddress("Kpl_hasRich", &Kpl_hasRich, &b_Kpl_hasRich);
   fChain->SetBranchAddress("Kpl_hasCalo", &Kpl_hasCalo, &b_Kpl_hasCalo);
   fChain->SetBranchAddress("Kpl_SV_X", &Kpl_SV_X, &b_Kpl_SV_X);
   fChain->SetBranchAddress("Kpl_SV_Y", &Kpl_SV_Y, &b_Kpl_SV_Y);
   fChain->SetBranchAddress("Kpl_SV_Z", &Kpl_SV_Z, &b_Kpl_SV_Z);
   fChain->SetBranchAddress("Kpl_SV_XERR", &Kpl_SV_XERR, &b_Kpl_SV_XERR);
   fChain->SetBranchAddress("Kpl_SV_YERR", &Kpl_SV_YERR, &b_Kpl_SV_YERR);
   fChain->SetBranchAddress("Kpl_SV_ZERR", &Kpl_SV_ZERR, &b_Kpl_SV_ZERR);
   fChain->SetBranchAddress("Kpl_SV_CHI2", &Kpl_SV_CHI2, &b_Kpl_SV_CHI2);
   fChain->SetBranchAddress("Kpl_SV_NDOF", &Kpl_SV_NDOF, &b_Kpl_SV_NDOF);
   fChain->SetBranchAddress("Kpl_SV_COV_", Kpl_SV_COV_, &b_Kpl_SV_COV_);
   fChain->SetBranchAddress("Kpl_PV_X", &Kpl_PV_X, &b_Kpl_PV_X);
   fChain->SetBranchAddress("Kpl_PV_Y", &Kpl_PV_Y, &b_Kpl_PV_Y);
   fChain->SetBranchAddress("Kpl_PV_Z", &Kpl_PV_Z, &b_Kpl_PV_Z);
   fChain->SetBranchAddress("Kpl_PV_CHI2", &Kpl_PV_CHI2, &b_Kpl_PV_CHI2);
   fChain->SetBranchAddress("Kpl_PV_NDOF", &Kpl_PV_NDOF, &b_Kpl_PV_NDOF);
   fChain->SetBranchAddress("Kpl_PV_COV_", Kpl_PV_COV_, &b_Kpl_PV_COV_);
   fChain->SetBranchAddress("Kpl_MOM_COV_", Kpl_MOM_COV_, &b_Kpl_MOM_COV_);
   fChain->SetBranchAddress("Kpl_POSMOM_COV_", Kpl_POSMOM_COV_, &b_Kpl_POSMOM_COV_);
   fChain->SetBranchAddress("Kpl_MCORR", &Kpl_MCORR, &b_Kpl_MCORR);
   fChain->SetBranchAddress("Kpl_MCORRERR", &Kpl_MCORRERR, &b_Kpl_MCORRERR);
   fChain->SetBranchAddress("Kpl_MCORRFULLERR", &Kpl_MCORRFULLERR, &b_Kpl_MCORRFULLERR);
   fChain->SetBranchAddress("Kpl_Q2SOL1", &Kpl_Q2SOL1, &b_Kpl_Q2SOL1);
   fChain->SetBranchAddress("Kpl_Q2SOL2", &Kpl_Q2SOL2, &b_Kpl_Q2SOL2);
   fChain->SetBranchAddress("Kpl_TRACK_Type", &Kpl_TRACK_Type, &b_Kpl_TRACK_Type);
   fChain->SetBranchAddress("Kpl_TRACK_Key", &Kpl_TRACK_Key, &b_Kpl_TRACK_Key);
   fChain->SetBranchAddress("Kpl_TRACK_CHI2NDOF", &Kpl_TRACK_CHI2NDOF, &b_Kpl_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("Kpl_TRACK_PCHI2", &Kpl_TRACK_PCHI2, &b_Kpl_TRACK_PCHI2);
   fChain->SetBranchAddress("Kpl_TRACK_MatchCHI2", &Kpl_TRACK_MatchCHI2, &b_Kpl_TRACK_MatchCHI2);
   fChain->SetBranchAddress("Kpl_TRACK_GhostProb", &Kpl_TRACK_GhostProb, &b_Kpl_TRACK_GhostProb);
   fChain->SetBranchAddress("Kpl_TRACK_CloneDist", &Kpl_TRACK_CloneDist, &b_Kpl_TRACK_CloneDist);
   fChain->SetBranchAddress("Kpl_TRACK_Likelihood", &Kpl_TRACK_Likelihood, &b_Kpl_TRACK_Likelihood);
   fChain->SetBranchAddress("pi_MC12TuneV2_ProbNNe", &pi_MC12TuneV2_ProbNNe, &b_pi_MC12TuneV2_ProbNNe);
   fChain->SetBranchAddress("pi_MC12TuneV2_ProbNNmu", &pi_MC12TuneV2_ProbNNmu, &b_pi_MC12TuneV2_ProbNNmu);
   fChain->SetBranchAddress("pi_MC12TuneV2_ProbNNpi", &pi_MC12TuneV2_ProbNNpi, &b_pi_MC12TuneV2_ProbNNpi);
   fChain->SetBranchAddress("pi_MC12TuneV2_ProbNNk", &pi_MC12TuneV2_ProbNNk, &b_pi_MC12TuneV2_ProbNNk);
   fChain->SetBranchAddress("pi_MC12TuneV2_ProbNNp", &pi_MC12TuneV2_ProbNNp, &b_pi_MC12TuneV2_ProbNNp);
   fChain->SetBranchAddress("pi_MC12TuneV2_ProbNNghost", &pi_MC12TuneV2_ProbNNghost, &b_pi_MC12TuneV2_ProbNNghost);
   fChain->SetBranchAddress("pi_MC12TuneV3_ProbNNe", &pi_MC12TuneV3_ProbNNe, &b_pi_MC12TuneV3_ProbNNe);
   fChain->SetBranchAddress("pi_MC12TuneV3_ProbNNmu", &pi_MC12TuneV3_ProbNNmu, &b_pi_MC12TuneV3_ProbNNmu);
   fChain->SetBranchAddress("pi_MC12TuneV3_ProbNNpi", &pi_MC12TuneV3_ProbNNpi, &b_pi_MC12TuneV3_ProbNNpi);
   fChain->SetBranchAddress("pi_MC12TuneV3_ProbNNk", &pi_MC12TuneV3_ProbNNk, &b_pi_MC12TuneV3_ProbNNk);
   fChain->SetBranchAddress("pi_MC12TuneV3_ProbNNp", &pi_MC12TuneV3_ProbNNp, &b_pi_MC12TuneV3_ProbNNp);
   fChain->SetBranchAddress("pi_MC12TuneV3_ProbNNghost", &pi_MC12TuneV3_ProbNNghost, &b_pi_MC12TuneV3_ProbNNghost);
   fChain->SetBranchAddress("pi_MINIP", &pi_MINIP, &b_pi_MINIP);
   fChain->SetBranchAddress("pi_MINIPCHI2", &pi_MINIPCHI2, &b_pi_MINIPCHI2);
   fChain->SetBranchAddress("pi_MINIPNEXTBEST", &pi_MINIPNEXTBEST, &b_pi_MINIPNEXTBEST);
   fChain->SetBranchAddress("pi_MINIPCHI2NEXTBEST", &pi_MINIPCHI2NEXTBEST, &b_pi_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("pi_OWNPV_X", &pi_OWNPV_X, &b_pi_OWNPV_X);
   fChain->SetBranchAddress("pi_OWNPV_Y", &pi_OWNPV_Y, &b_pi_OWNPV_Y);
   fChain->SetBranchAddress("pi_OWNPV_Z", &pi_OWNPV_Z, &b_pi_OWNPV_Z);
   fChain->SetBranchAddress("pi_OWNPV_XERR", &pi_OWNPV_XERR, &b_pi_OWNPV_XERR);
   fChain->SetBranchAddress("pi_OWNPV_YERR", &pi_OWNPV_YERR, &b_pi_OWNPV_YERR);
   fChain->SetBranchAddress("pi_OWNPV_ZERR", &pi_OWNPV_ZERR, &b_pi_OWNPV_ZERR);
   fChain->SetBranchAddress("pi_OWNPV_CHI2", &pi_OWNPV_CHI2, &b_pi_OWNPV_CHI2);
   fChain->SetBranchAddress("pi_OWNPV_NDOF", &pi_OWNPV_NDOF, &b_pi_OWNPV_NDOF);
   fChain->SetBranchAddress("pi_OWNPV_COV_", pi_OWNPV_COV_, &b_pi_OWNPV_COV_);
   fChain->SetBranchAddress("pi_IP_OWNPV", &pi_IP_OWNPV, &b_pi_IP_OWNPV);
   fChain->SetBranchAddress("pi_IPCHI2_OWNPV", &pi_IPCHI2_OWNPV, &b_pi_IPCHI2_OWNPV);
   fChain->SetBranchAddress("pi_TOPPV_X", &pi_TOPPV_X, &b_pi_TOPPV_X);
   fChain->SetBranchAddress("pi_TOPPV_Y", &pi_TOPPV_Y, &b_pi_TOPPV_Y);
   fChain->SetBranchAddress("pi_TOPPV_Z", &pi_TOPPV_Z, &b_pi_TOPPV_Z);
   fChain->SetBranchAddress("pi_TOPPV_XERR", &pi_TOPPV_XERR, &b_pi_TOPPV_XERR);
   fChain->SetBranchAddress("pi_TOPPV_YERR", &pi_TOPPV_YERR, &b_pi_TOPPV_YERR);
   fChain->SetBranchAddress("pi_TOPPV_ZERR", &pi_TOPPV_ZERR, &b_pi_TOPPV_ZERR);
   fChain->SetBranchAddress("pi_TOPPV_CHI2", &pi_TOPPV_CHI2, &b_pi_TOPPV_CHI2);
   fChain->SetBranchAddress("pi_TOPPV_NDOF", &pi_TOPPV_NDOF, &b_pi_TOPPV_NDOF);
   fChain->SetBranchAddress("pi_TOPPV_COV_", pi_TOPPV_COV_, &b_pi_TOPPV_COV_);
   fChain->SetBranchAddress("pi_IP_TOPPV", &pi_IP_TOPPV, &b_pi_IP_TOPPV);
   fChain->SetBranchAddress("pi_IPCHI2_TOPPV", &pi_IPCHI2_TOPPV, &b_pi_IPCHI2_TOPPV);
   fChain->SetBranchAddress("pi_ORIVX_X", &pi_ORIVX_X, &b_pi_ORIVX_X);
   fChain->SetBranchAddress("pi_ORIVX_Y", &pi_ORIVX_Y, &b_pi_ORIVX_Y);
   fChain->SetBranchAddress("pi_ORIVX_Z", &pi_ORIVX_Z, &b_pi_ORIVX_Z);
   fChain->SetBranchAddress("pi_ORIVX_XERR", &pi_ORIVX_XERR, &b_pi_ORIVX_XERR);
   fChain->SetBranchAddress("pi_ORIVX_YERR", &pi_ORIVX_YERR, &b_pi_ORIVX_YERR);
   fChain->SetBranchAddress("pi_ORIVX_ZERR", &pi_ORIVX_ZERR, &b_pi_ORIVX_ZERR);
   fChain->SetBranchAddress("pi_ORIVX_CHI2", &pi_ORIVX_CHI2, &b_pi_ORIVX_CHI2);
   fChain->SetBranchAddress("pi_ORIVX_NDOF", &pi_ORIVX_NDOF, &b_pi_ORIVX_NDOF);
   fChain->SetBranchAddress("pi_ORIVX_COV_", pi_ORIVX_COV_, &b_pi_ORIVX_COV_);
   fChain->SetBranchAddress("pi_IP_ORIVX", &pi_IP_ORIVX, &b_pi_IP_ORIVX);
   fChain->SetBranchAddress("pi_IPCHI2_ORIVX", &pi_IPCHI2_ORIVX, &b_pi_IPCHI2_ORIVX);
   fChain->SetBranchAddress("pi_P", &pi_P, &b_pi_P);
   fChain->SetBranchAddress("pi_PT", &pi_PT, &b_pi_PT);
   fChain->SetBranchAddress("pi_PE", &pi_PE, &b_pi_PE);
   fChain->SetBranchAddress("pi_PX", &pi_PX, &b_pi_PX);
   fChain->SetBranchAddress("pi_PY", &pi_PY, &b_pi_PY);
   fChain->SetBranchAddress("pi_PZ", &pi_PZ, &b_pi_PZ);
   fChain->SetBranchAddress("pi_M", &pi_M, &b_pi_M);
   fChain->SetBranchAddress("pi_ID", &pi_ID, &b_pi_ID);
   fChain->SetBranchAddress("pi_eta", &pi_eta, &b_pi_eta);
   fChain->SetBranchAddress("pi_phi", &pi_phi, &b_pi_phi);
   fChain->SetBranchAddress("pi_PIDe", &pi_PIDe, &b_pi_PIDe);
   fChain->SetBranchAddress("pi_PIDmu", &pi_PIDmu, &b_pi_PIDmu);
   fChain->SetBranchAddress("pi_PIDK", &pi_PIDK, &b_pi_PIDK);
   fChain->SetBranchAddress("pi_PIDp", &pi_PIDp, &b_pi_PIDp);
   fChain->SetBranchAddress("pi_ProbNNe", &pi_ProbNNe, &b_pi_ProbNNe);
   fChain->SetBranchAddress("pi_ProbNNk", &pi_ProbNNk, &b_pi_ProbNNk);
   fChain->SetBranchAddress("pi_ProbNNp", &pi_ProbNNp, &b_pi_ProbNNp);
   fChain->SetBranchAddress("pi_ProbNNpi", &pi_ProbNNpi, &b_pi_ProbNNpi);
   fChain->SetBranchAddress("pi_ProbNNmu", &pi_ProbNNmu, &b_pi_ProbNNmu);
   fChain->SetBranchAddress("pi_ProbNNghost", &pi_ProbNNghost, &b_pi_ProbNNghost);
   fChain->SetBranchAddress("pi_hasMuon", &pi_hasMuon, &b_pi_hasMuon);
   fChain->SetBranchAddress("pi_isMuon", &pi_isMuon, &b_pi_isMuon);
   fChain->SetBranchAddress("pi_hasRich", &pi_hasRich, &b_pi_hasRich);
   fChain->SetBranchAddress("pi_hasCalo", &pi_hasCalo, &b_pi_hasCalo);
   fChain->SetBranchAddress("pi_SV_X", &pi_SV_X, &b_pi_SV_X);
   fChain->SetBranchAddress("pi_SV_Y", &pi_SV_Y, &b_pi_SV_Y);
   fChain->SetBranchAddress("pi_SV_Z", &pi_SV_Z, &b_pi_SV_Z);
   fChain->SetBranchAddress("pi_SV_XERR", &pi_SV_XERR, &b_pi_SV_XERR);
   fChain->SetBranchAddress("pi_SV_YERR", &pi_SV_YERR, &b_pi_SV_YERR);
   fChain->SetBranchAddress("pi_SV_ZERR", &pi_SV_ZERR, &b_pi_SV_ZERR);
   fChain->SetBranchAddress("pi_SV_CHI2", &pi_SV_CHI2, &b_pi_SV_CHI2);
   fChain->SetBranchAddress("pi_SV_NDOF", &pi_SV_NDOF, &b_pi_SV_NDOF);
   fChain->SetBranchAddress("pi_SV_COV_", pi_SV_COV_, &b_pi_SV_COV_);
   fChain->SetBranchAddress("pi_PV_X", &pi_PV_X, &b_pi_PV_X);
   fChain->SetBranchAddress("pi_PV_Y", &pi_PV_Y, &b_pi_PV_Y);
   fChain->SetBranchAddress("pi_PV_Z", &pi_PV_Z, &b_pi_PV_Z);
   fChain->SetBranchAddress("pi_PV_CHI2", &pi_PV_CHI2, &b_pi_PV_CHI2);
   fChain->SetBranchAddress("pi_PV_NDOF", &pi_PV_NDOF, &b_pi_PV_NDOF);
   fChain->SetBranchAddress("pi_PV_COV_", pi_PV_COV_, &b_pi_PV_COV_);
   fChain->SetBranchAddress("pi_MOM_COV_", pi_MOM_COV_, &b_pi_MOM_COV_);
   fChain->SetBranchAddress("pi_POSMOM_COV_", pi_POSMOM_COV_, &b_pi_POSMOM_COV_);
   fChain->SetBranchAddress("pi_MCORR", &pi_MCORR, &b_pi_MCORR);
   fChain->SetBranchAddress("pi_MCORRERR", &pi_MCORRERR, &b_pi_MCORRERR);
   fChain->SetBranchAddress("pi_MCORRFULLERR", &pi_MCORRFULLERR, &b_pi_MCORRFULLERR);
   fChain->SetBranchAddress("pi_Q2SOL1", &pi_Q2SOL1, &b_pi_Q2SOL1);
   fChain->SetBranchAddress("pi_Q2SOL2", &pi_Q2SOL2, &b_pi_Q2SOL2);
   fChain->SetBranchAddress("pi_TRACK_Type", &pi_TRACK_Type, &b_pi_TRACK_Type);
   fChain->SetBranchAddress("pi_TRACK_Key", &pi_TRACK_Key, &b_pi_TRACK_Key);
   fChain->SetBranchAddress("pi_TRACK_CHI2NDOF", &pi_TRACK_CHI2NDOF, &b_pi_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("pi_TRACK_PCHI2", &pi_TRACK_PCHI2, &b_pi_TRACK_PCHI2);
   fChain->SetBranchAddress("pi_TRACK_MatchCHI2", &pi_TRACK_MatchCHI2, &b_pi_TRACK_MatchCHI2);
   fChain->SetBranchAddress("pi_TRACK_GhostProb", &pi_TRACK_GhostProb, &b_pi_TRACK_GhostProb);
   fChain->SetBranchAddress("pi_TRACK_CloneDist", &pi_TRACK_CloneDist, &b_pi_TRACK_CloneDist);
   fChain->SetBranchAddress("pi_TRACK_Likelihood", &pi_TRACK_Likelihood, &b_pi_TRACK_Likelihood);
   fChain->SetBranchAddress("mu_MC12TuneV2_ProbNNe", &mu_MC12TuneV2_ProbNNe, &b_mu_MC12TuneV2_ProbNNe);
   fChain->SetBranchAddress("mu_MC12TuneV2_ProbNNmu", &mu_MC12TuneV2_ProbNNmu, &b_mu_MC12TuneV2_ProbNNmu);
   fChain->SetBranchAddress("mu_MC12TuneV2_ProbNNpi", &mu_MC12TuneV2_ProbNNpi, &b_mu_MC12TuneV2_ProbNNpi);
   fChain->SetBranchAddress("mu_MC12TuneV2_ProbNNk", &mu_MC12TuneV2_ProbNNk, &b_mu_MC12TuneV2_ProbNNk);
   fChain->SetBranchAddress("mu_MC12TuneV2_ProbNNp", &mu_MC12TuneV2_ProbNNp, &b_mu_MC12TuneV2_ProbNNp);
   fChain->SetBranchAddress("mu_MC12TuneV2_ProbNNghost", &mu_MC12TuneV2_ProbNNghost, &b_mu_MC12TuneV2_ProbNNghost);
   fChain->SetBranchAddress("mu_MC12TuneV3_ProbNNe", &mu_MC12TuneV3_ProbNNe, &b_mu_MC12TuneV3_ProbNNe);
   fChain->SetBranchAddress("mu_MC12TuneV3_ProbNNmu", &mu_MC12TuneV3_ProbNNmu, &b_mu_MC12TuneV3_ProbNNmu);
   fChain->SetBranchAddress("mu_MC12TuneV3_ProbNNpi", &mu_MC12TuneV3_ProbNNpi, &b_mu_MC12TuneV3_ProbNNpi);
   fChain->SetBranchAddress("mu_MC12TuneV3_ProbNNk", &mu_MC12TuneV3_ProbNNk, &b_mu_MC12TuneV3_ProbNNk);
   fChain->SetBranchAddress("mu_MC12TuneV3_ProbNNp", &mu_MC12TuneV3_ProbNNp, &b_mu_MC12TuneV3_ProbNNp);
   fChain->SetBranchAddress("mu_MC12TuneV3_ProbNNghost", &mu_MC12TuneV3_ProbNNghost, &b_mu_MC12TuneV3_ProbNNghost);
   fChain->SetBranchAddress("mu_0.00_cc_mult", &mu_0_00_cc_mult, &b_mu_0_00_cc_mult);
   fChain->SetBranchAddress("mu_0.00_cc_PX", &mu_0_00_cc_PX, &b_mu_0_00_cc_PX);
   fChain->SetBranchAddress("mu_0.00_cc_PY", &mu_0_00_cc_PY, &b_mu_0_00_cc_PY);
   fChain->SetBranchAddress("mu_0.00_cc_PZ", &mu_0_00_cc_PZ, &b_mu_0_00_cc_PZ);
   fChain->SetBranchAddress("mu_0.00_cc_vPT", &mu_0_00_cc_vPT, &b_mu_0_00_cc_vPT);
   fChain->SetBranchAddress("mu_0.00_cc_sPT", &mu_0_00_cc_sPT, &b_mu_0_00_cc_sPT);
   fChain->SetBranchAddress("mu_0.00_cc_maxPt_Q", &mu_0_00_cc_maxPt_Q, &b_mu_0_00_cc_maxPt_Q);
   fChain->SetBranchAddress("mu_0.00_cc_maxPt_PT", &mu_0_00_cc_maxPt_PT, &b_mu_0_00_cc_maxPt_PT);
   fChain->SetBranchAddress("mu_0.00_cc_maxPt_PX", &mu_0_00_cc_maxPt_PX, &b_mu_0_00_cc_maxPt_PX);
   fChain->SetBranchAddress("mu_0.00_cc_maxPt_PY", &mu_0_00_cc_maxPt_PY, &b_mu_0_00_cc_maxPt_PY);
   fChain->SetBranchAddress("mu_0.00_cc_maxPt_PZ", &mu_0_00_cc_maxPt_PZ, &b_mu_0_00_cc_maxPt_PZ);
   fChain->SetBranchAddress("mu_0.00_cc_maxPt_PE", &mu_0_00_cc_maxPt_PE, &b_mu_0_00_cc_maxPt_PE);
   fChain->SetBranchAddress("mu_0.00_nc_mult", &mu_0_00_nc_mult, &b_mu_0_00_nc_mult);
   fChain->SetBranchAddress("mu_0.00_nc_PX", &mu_0_00_nc_PX, &b_mu_0_00_nc_PX);
   fChain->SetBranchAddress("mu_0.00_nc_PY", &mu_0_00_nc_PY, &b_mu_0_00_nc_PY);
   fChain->SetBranchAddress("mu_0.00_nc_PZ", &mu_0_00_nc_PZ, &b_mu_0_00_nc_PZ);
   fChain->SetBranchAddress("mu_0.00_nc_vPT", &mu_0_00_nc_vPT, &b_mu_0_00_nc_vPT);
   fChain->SetBranchAddress("mu_0.00_nc_sPT", &mu_0_00_nc_sPT, &b_mu_0_00_nc_sPT);
   fChain->SetBranchAddress("mu_0.00_nc_maxPt_PT", &mu_0_00_nc_maxPt_PT, &b_mu_0_00_nc_maxPt_PT);
   fChain->SetBranchAddress("mu_0.00_nc_maxPt_PX", &mu_0_00_nc_maxPt_PX, &b_mu_0_00_nc_maxPt_PX);
   fChain->SetBranchAddress("mu_0.00_nc_maxPt_PY", &mu_0_00_nc_maxPt_PY, &b_mu_0_00_nc_maxPt_PY);
   fChain->SetBranchAddress("mu_0.00_nc_maxPt_PZ", &mu_0_00_nc_maxPt_PZ, &b_mu_0_00_nc_maxPt_PZ);
   fChain->SetBranchAddress("mu_1.50_cc_mult", &mu_1_50_cc_mult, &b_mu_1_50_cc_mult);
   fChain->SetBranchAddress("mu_1.50_cc_PX", &mu_1_50_cc_PX, &b_mu_1_50_cc_PX);
   fChain->SetBranchAddress("mu_1.50_cc_PY", &mu_1_50_cc_PY, &b_mu_1_50_cc_PY);
   fChain->SetBranchAddress("mu_1.50_cc_PZ", &mu_1_50_cc_PZ, &b_mu_1_50_cc_PZ);
   fChain->SetBranchAddress("mu_1.50_cc_vPT", &mu_1_50_cc_vPT, &b_mu_1_50_cc_vPT);
   fChain->SetBranchAddress("mu_1.50_cc_sPT", &mu_1_50_cc_sPT, &b_mu_1_50_cc_sPT);
   fChain->SetBranchAddress("mu_1.50_nc_mult", &mu_1_50_nc_mult, &b_mu_1_50_nc_mult);
   fChain->SetBranchAddress("mu_1.50_nc_PX", &mu_1_50_nc_PX, &b_mu_1_50_nc_PX);
   fChain->SetBranchAddress("mu_1.50_nc_PY", &mu_1_50_nc_PY, &b_mu_1_50_nc_PY);
   fChain->SetBranchAddress("mu_1.50_nc_PZ", &mu_1_50_nc_PZ, &b_mu_1_50_nc_PZ);
   fChain->SetBranchAddress("mu_1.50_nc_vPT", &mu_1_50_nc_vPT, &b_mu_1_50_nc_vPT);
   fChain->SetBranchAddress("mu_1.50_nc_sPT", &mu_1_50_nc_sPT, &b_mu_1_50_nc_sPT);
   fChain->SetBranchAddress("mu_1.20_cc_mult", &mu_1_20_cc_mult, &b_mu_1_20_cc_mult);
   fChain->SetBranchAddress("mu_1.20_cc_PX", &mu_1_20_cc_PX, &b_mu_1_20_cc_PX);
   fChain->SetBranchAddress("mu_1.20_cc_PY", &mu_1_20_cc_PY, &b_mu_1_20_cc_PY);
   fChain->SetBranchAddress("mu_1.20_cc_PZ", &mu_1_20_cc_PZ, &b_mu_1_20_cc_PZ);
   fChain->SetBranchAddress("mu_1.20_cc_vPT", &mu_1_20_cc_vPT, &b_mu_1_20_cc_vPT);
   fChain->SetBranchAddress("mu_1.20_cc_sPT", &mu_1_20_cc_sPT, &b_mu_1_20_cc_sPT);
   fChain->SetBranchAddress("mu_1.20_nc_mult", &mu_1_20_nc_mult, &b_mu_1_20_nc_mult);
   fChain->SetBranchAddress("mu_1.20_nc_PX", &mu_1_20_nc_PX, &b_mu_1_20_nc_PX);
   fChain->SetBranchAddress("mu_1.20_nc_PY", &mu_1_20_nc_PY, &b_mu_1_20_nc_PY);
   fChain->SetBranchAddress("mu_1.20_nc_PZ", &mu_1_20_nc_PZ, &b_mu_1_20_nc_PZ);
   fChain->SetBranchAddress("mu_1.20_nc_vPT", &mu_1_20_nc_vPT, &b_mu_1_20_nc_vPT);
   fChain->SetBranchAddress("mu_1.20_nc_sPT", &mu_1_20_nc_sPT, &b_mu_1_20_nc_sPT);
   fChain->SetBranchAddress("mu_0.90_cc_mult", &mu_0_90_cc_mult, &b_mu_0_90_cc_mult);
   fChain->SetBranchAddress("mu_0.90_cc_PX", &mu_0_90_cc_PX, &b_mu_0_90_cc_PX);
   fChain->SetBranchAddress("mu_0.90_cc_PY", &mu_0_90_cc_PY, &b_mu_0_90_cc_PY);
   fChain->SetBranchAddress("mu_0.90_cc_PZ", &mu_0_90_cc_PZ, &b_mu_0_90_cc_PZ);
   fChain->SetBranchAddress("mu_0.90_cc_vPT", &mu_0_90_cc_vPT, &b_mu_0_90_cc_vPT);
   fChain->SetBranchAddress("mu_0.90_cc_sPT", &mu_0_90_cc_sPT, &b_mu_0_90_cc_sPT);
   fChain->SetBranchAddress("mu_0.90_nc_mult", &mu_0_90_nc_mult, &b_mu_0_90_nc_mult);
   fChain->SetBranchAddress("mu_0.90_nc_PX", &mu_0_90_nc_PX, &b_mu_0_90_nc_PX);
   fChain->SetBranchAddress("mu_0.90_nc_PY", &mu_0_90_nc_PY, &b_mu_0_90_nc_PY);
   fChain->SetBranchAddress("mu_0.90_nc_PZ", &mu_0_90_nc_PZ, &b_mu_0_90_nc_PZ);
   fChain->SetBranchAddress("mu_0.90_nc_vPT", &mu_0_90_nc_vPT, &b_mu_0_90_nc_vPT);
   fChain->SetBranchAddress("mu_0.90_nc_sPT", &mu_0_90_nc_sPT, &b_mu_0_90_nc_sPT);
   fChain->SetBranchAddress("mu_0.60_cc_mult", &mu_0_60_cc_mult, &b_mu_0_60_cc_mult);
   fChain->SetBranchAddress("mu_0.60_cc_PX", &mu_0_60_cc_PX, &b_mu_0_60_cc_PX);
   fChain->SetBranchAddress("mu_0.60_cc_PY", &mu_0_60_cc_PY, &b_mu_0_60_cc_PY);
   fChain->SetBranchAddress("mu_0.60_cc_PZ", &mu_0_60_cc_PZ, &b_mu_0_60_cc_PZ);
   fChain->SetBranchAddress("mu_0.60_cc_vPT", &mu_0_60_cc_vPT, &b_mu_0_60_cc_vPT);
   fChain->SetBranchAddress("mu_0.60_cc_sPT", &mu_0_60_cc_sPT, &b_mu_0_60_cc_sPT);
   fChain->SetBranchAddress("mu_0.60_nc_mult", &mu_0_60_nc_mult, &b_mu_0_60_nc_mult);
   fChain->SetBranchAddress("mu_0.60_nc_PX", &mu_0_60_nc_PX, &b_mu_0_60_nc_PX);
   fChain->SetBranchAddress("mu_0.60_nc_PY", &mu_0_60_nc_PY, &b_mu_0_60_nc_PY);
   fChain->SetBranchAddress("mu_0.60_nc_PZ", &mu_0_60_nc_PZ, &b_mu_0_60_nc_PZ);
   fChain->SetBranchAddress("mu_0.60_nc_vPT", &mu_0_60_nc_vPT, &b_mu_0_60_nc_vPT);
   fChain->SetBranchAddress("mu_0.60_nc_sPT", &mu_0_60_nc_sPT, &b_mu_0_60_nc_sPT);
   fChain->SetBranchAddress("mu_0.30_cc_mult", &mu_0_30_cc_mult, &b_mu_0_30_cc_mult);
   fChain->SetBranchAddress("mu_0.30_cc_PX", &mu_0_30_cc_PX, &b_mu_0_30_cc_PX);
   fChain->SetBranchAddress("mu_0.30_cc_PY", &mu_0_30_cc_PY, &b_mu_0_30_cc_PY);
   fChain->SetBranchAddress("mu_0.30_cc_PZ", &mu_0_30_cc_PZ, &b_mu_0_30_cc_PZ);
   fChain->SetBranchAddress("mu_0.30_cc_vPT", &mu_0_30_cc_vPT, &b_mu_0_30_cc_vPT);
   fChain->SetBranchAddress("mu_0.30_cc_sPT", &mu_0_30_cc_sPT, &b_mu_0_30_cc_sPT);
   fChain->SetBranchAddress("mu_0.30_nc_mult", &mu_0_30_nc_mult, &b_mu_0_30_nc_mult);
   fChain->SetBranchAddress("mu_0.30_nc_PX", &mu_0_30_nc_PX, &b_mu_0_30_nc_PX);
   fChain->SetBranchAddress("mu_0.30_nc_PY", &mu_0_30_nc_PY, &b_mu_0_30_nc_PY);
   fChain->SetBranchAddress("mu_0.30_nc_PZ", &mu_0_30_nc_PZ, &b_mu_0_30_nc_PZ);
   fChain->SetBranchAddress("mu_0.30_nc_vPT", &mu_0_30_nc_vPT, &b_mu_0_30_nc_vPT);
   fChain->SetBranchAddress("mu_0.30_nc_sPT", &mu_0_30_nc_sPT, &b_mu_0_30_nc_sPT);
   fChain->SetBranchAddress("mu_MINIP", &mu_MINIP, &b_mu_MINIP);
   fChain->SetBranchAddress("mu_MINIPCHI2", &mu_MINIPCHI2, &b_mu_MINIPCHI2);
   fChain->SetBranchAddress("mu_MINIPNEXTBEST", &mu_MINIPNEXTBEST, &b_mu_MINIPNEXTBEST);
   fChain->SetBranchAddress("mu_MINIPCHI2NEXTBEST", &mu_MINIPCHI2NEXTBEST, &b_mu_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("mu_OWNPV_X", &mu_OWNPV_X, &b_mu_OWNPV_X);
   fChain->SetBranchAddress("mu_OWNPV_Y", &mu_OWNPV_Y, &b_mu_OWNPV_Y);
   fChain->SetBranchAddress("mu_OWNPV_Z", &mu_OWNPV_Z, &b_mu_OWNPV_Z);
   fChain->SetBranchAddress("mu_OWNPV_XERR", &mu_OWNPV_XERR, &b_mu_OWNPV_XERR);
   fChain->SetBranchAddress("mu_OWNPV_YERR", &mu_OWNPV_YERR, &b_mu_OWNPV_YERR);
   fChain->SetBranchAddress("mu_OWNPV_ZERR", &mu_OWNPV_ZERR, &b_mu_OWNPV_ZERR);
   fChain->SetBranchAddress("mu_OWNPV_CHI2", &mu_OWNPV_CHI2, &b_mu_OWNPV_CHI2);
   fChain->SetBranchAddress("mu_OWNPV_NDOF", &mu_OWNPV_NDOF, &b_mu_OWNPV_NDOF);
   fChain->SetBranchAddress("mu_OWNPV_COV_", mu_OWNPV_COV_, &b_mu_OWNPV_COV_);
   fChain->SetBranchAddress("mu_IP_OWNPV", &mu_IP_OWNPV, &b_mu_IP_OWNPV);
   fChain->SetBranchAddress("mu_IPCHI2_OWNPV", &mu_IPCHI2_OWNPV, &b_mu_IPCHI2_OWNPV);
   fChain->SetBranchAddress("mu_TOPPV_X", &mu_TOPPV_X, &b_mu_TOPPV_X);
   fChain->SetBranchAddress("mu_TOPPV_Y", &mu_TOPPV_Y, &b_mu_TOPPV_Y);
   fChain->SetBranchAddress("mu_TOPPV_Z", &mu_TOPPV_Z, &b_mu_TOPPV_Z);
   fChain->SetBranchAddress("mu_TOPPV_XERR", &mu_TOPPV_XERR, &b_mu_TOPPV_XERR);
   fChain->SetBranchAddress("mu_TOPPV_YERR", &mu_TOPPV_YERR, &b_mu_TOPPV_YERR);
   fChain->SetBranchAddress("mu_TOPPV_ZERR", &mu_TOPPV_ZERR, &b_mu_TOPPV_ZERR);
   fChain->SetBranchAddress("mu_TOPPV_CHI2", &mu_TOPPV_CHI2, &b_mu_TOPPV_CHI2);
   fChain->SetBranchAddress("mu_TOPPV_NDOF", &mu_TOPPV_NDOF, &b_mu_TOPPV_NDOF);
   fChain->SetBranchAddress("mu_TOPPV_COV_", mu_TOPPV_COV_, &b_mu_TOPPV_COV_);
   fChain->SetBranchAddress("mu_IP_TOPPV", &mu_IP_TOPPV, &b_mu_IP_TOPPV);
   fChain->SetBranchAddress("mu_IPCHI2_TOPPV", &mu_IPCHI2_TOPPV, &b_mu_IPCHI2_TOPPV);
   fChain->SetBranchAddress("mu_ORIVX_X", &mu_ORIVX_X, &b_mu_ORIVX_X);
   fChain->SetBranchAddress("mu_ORIVX_Y", &mu_ORIVX_Y, &b_mu_ORIVX_Y);
   fChain->SetBranchAddress("mu_ORIVX_Z", &mu_ORIVX_Z, &b_mu_ORIVX_Z);
   fChain->SetBranchAddress("mu_ORIVX_XERR", &mu_ORIVX_XERR, &b_mu_ORIVX_XERR);
   fChain->SetBranchAddress("mu_ORIVX_YERR", &mu_ORIVX_YERR, &b_mu_ORIVX_YERR);
   fChain->SetBranchAddress("mu_ORIVX_ZERR", &mu_ORIVX_ZERR, &b_mu_ORIVX_ZERR);
   fChain->SetBranchAddress("mu_ORIVX_CHI2", &mu_ORIVX_CHI2, &b_mu_ORIVX_CHI2);
   fChain->SetBranchAddress("mu_ORIVX_NDOF", &mu_ORIVX_NDOF, &b_mu_ORIVX_NDOF);
   fChain->SetBranchAddress("mu_ORIVX_COV_", mu_ORIVX_COV_, &b_mu_ORIVX_COV_);
   fChain->SetBranchAddress("mu_IP_ORIVX", &mu_IP_ORIVX, &b_mu_IP_ORIVX);
   fChain->SetBranchAddress("mu_IPCHI2_ORIVX", &mu_IPCHI2_ORIVX, &b_mu_IPCHI2_ORIVX);
   fChain->SetBranchAddress("mu_P", &mu_P, &b_mu_P);
   fChain->SetBranchAddress("mu_PT", &mu_PT, &b_mu_PT);
   fChain->SetBranchAddress("mu_PE", &mu_PE, &b_mu_PE);
   fChain->SetBranchAddress("mu_PX", &mu_PX, &b_mu_PX);
   fChain->SetBranchAddress("mu_PY", &mu_PY, &b_mu_PY);
   fChain->SetBranchAddress("mu_PZ", &mu_PZ, &b_mu_PZ);
   fChain->SetBranchAddress("mu_M", &mu_M, &b_mu_M);
   fChain->SetBranchAddress("mu_ID", &mu_ID, &b_mu_ID);
   fChain->SetBranchAddress("mu_nVeloIDs", &mu_nVeloIDs, &b_mu_nVeloIDs);
   fChain->SetBranchAddress("mu_nITIDs", &mu_nITIDs, &b_mu_nITIDs);
   fChain->SetBranchAddress("mu_nTTIDs", &mu_nTTIDs, &b_mu_nTTIDs);
   fChain->SetBranchAddress("mu_nOTIDs", &mu_nOTIDs, &b_mu_nOTIDs);
   fChain->SetBranchAddress("mu_eta", &mu_eta, &b_mu_eta);
   fChain->SetBranchAddress("mu_phi", &mu_phi, &b_mu_phi);
   fChain->SetBranchAddress("mu_PIDe", &mu_PIDe, &b_mu_PIDe);
   fChain->SetBranchAddress("mu_PIDmu", &mu_PIDmu, &b_mu_PIDmu);
   fChain->SetBranchAddress("mu_PIDK", &mu_PIDK, &b_mu_PIDK);
   fChain->SetBranchAddress("mu_PIDp", &mu_PIDp, &b_mu_PIDp);
   fChain->SetBranchAddress("mu_ProbNNe", &mu_ProbNNe, &b_mu_ProbNNe);
   fChain->SetBranchAddress("mu_ProbNNk", &mu_ProbNNk, &b_mu_ProbNNk);
   fChain->SetBranchAddress("mu_ProbNNp", &mu_ProbNNp, &b_mu_ProbNNp);
   fChain->SetBranchAddress("mu_ProbNNpi", &mu_ProbNNpi, &b_mu_ProbNNpi);
   fChain->SetBranchAddress("mu_ProbNNmu", &mu_ProbNNmu, &b_mu_ProbNNmu);
   fChain->SetBranchAddress("mu_ProbNNghost", &mu_ProbNNghost, &b_mu_ProbNNghost);
   fChain->SetBranchAddress("mu_hasMuon", &mu_hasMuon, &b_mu_hasMuon);
   fChain->SetBranchAddress("mu_isMuon", &mu_isMuon, &b_mu_isMuon);
   fChain->SetBranchAddress("mu_hasRich", &mu_hasRich, &b_mu_hasRich);
   fChain->SetBranchAddress("mu_hasCalo", &mu_hasCalo, &b_mu_hasCalo);
   fChain->SetBranchAddress("mu_SV_X", &mu_SV_X, &b_mu_SV_X);
   fChain->SetBranchAddress("mu_SV_Y", &mu_SV_Y, &b_mu_SV_Y);
   fChain->SetBranchAddress("mu_SV_Z", &mu_SV_Z, &b_mu_SV_Z);
   fChain->SetBranchAddress("mu_SV_XERR", &mu_SV_XERR, &b_mu_SV_XERR);
   fChain->SetBranchAddress("mu_SV_YERR", &mu_SV_YERR, &b_mu_SV_YERR);
   fChain->SetBranchAddress("mu_SV_ZERR", &mu_SV_ZERR, &b_mu_SV_ZERR);
   fChain->SetBranchAddress("mu_SV_CHI2", &mu_SV_CHI2, &b_mu_SV_CHI2);
   fChain->SetBranchAddress("mu_SV_NDOF", &mu_SV_NDOF, &b_mu_SV_NDOF);
   fChain->SetBranchAddress("mu_SV_COV_", mu_SV_COV_, &b_mu_SV_COV_);
   fChain->SetBranchAddress("mu_PV_X", &mu_PV_X, &b_mu_PV_X);
   fChain->SetBranchAddress("mu_PV_Y", &mu_PV_Y, &b_mu_PV_Y);
   fChain->SetBranchAddress("mu_PV_Z", &mu_PV_Z, &b_mu_PV_Z);
   fChain->SetBranchAddress("mu_PV_CHI2", &mu_PV_CHI2, &b_mu_PV_CHI2);
   fChain->SetBranchAddress("mu_PV_NDOF", &mu_PV_NDOF, &b_mu_PV_NDOF);
   fChain->SetBranchAddress("mu_PV_COV_", mu_PV_COV_, &b_mu_PV_COV_);
   fChain->SetBranchAddress("mu_MOM_COV_", mu_MOM_COV_, &b_mu_MOM_COV_);
   fChain->SetBranchAddress("mu_POSMOM_COV_", mu_POSMOM_COV_, &b_mu_POSMOM_COV_);
   fChain->SetBranchAddress("mu_MCORR", &mu_MCORR, &b_mu_MCORR);
   fChain->SetBranchAddress("mu_MCORRERR", &mu_MCORRERR, &b_mu_MCORRERR);
   fChain->SetBranchAddress("mu_MCORRFULLERR", &mu_MCORRFULLERR, &b_mu_MCORRFULLERR);
   fChain->SetBranchAddress("mu_Q2SOL1", &mu_Q2SOL1, &b_mu_Q2SOL1);
   fChain->SetBranchAddress("mu_Q2SOL2", &mu_Q2SOL2, &b_mu_Q2SOL2);
   fChain->SetBranchAddress("mu_L0Global_Dec", &mu_L0Global_Dec, &b_mu_L0Global_Dec);
   fChain->SetBranchAddress("mu_L0Global_TIS", &mu_L0Global_TIS, &b_mu_L0Global_TIS);
   fChain->SetBranchAddress("mu_L0Global_TOS", &mu_L0Global_TOS, &b_mu_L0Global_TOS);
   fChain->SetBranchAddress("mu_Hlt1Global_Dec", &mu_Hlt1Global_Dec, &b_mu_Hlt1Global_Dec);
   fChain->SetBranchAddress("mu_Hlt1Global_TIS", &mu_Hlt1Global_TIS, &b_mu_Hlt1Global_TIS);
   fChain->SetBranchAddress("mu_Hlt1Global_TOS", &mu_Hlt1Global_TOS, &b_mu_Hlt1Global_TOS);
   fChain->SetBranchAddress("mu_Hlt1Phys_Dec", &mu_Hlt1Phys_Dec, &b_mu_Hlt1Phys_Dec);
   fChain->SetBranchAddress("mu_Hlt1Phys_TIS", &mu_Hlt1Phys_TIS, &b_mu_Hlt1Phys_TIS);
   fChain->SetBranchAddress("mu_Hlt1Phys_TOS", &mu_Hlt1Phys_TOS, &b_mu_Hlt1Phys_TOS);
   fChain->SetBranchAddress("mu_Hlt2Global_Dec", &mu_Hlt2Global_Dec, &b_mu_Hlt2Global_Dec);
   fChain->SetBranchAddress("mu_Hlt2Global_TIS", &mu_Hlt2Global_TIS, &b_mu_Hlt2Global_TIS);
   fChain->SetBranchAddress("mu_Hlt2Global_TOS", &mu_Hlt2Global_TOS, &b_mu_Hlt2Global_TOS);
   fChain->SetBranchAddress("mu_Hlt2Phys_Dec", &mu_Hlt2Phys_Dec, &b_mu_Hlt2Phys_Dec);
   fChain->SetBranchAddress("mu_Hlt2Phys_TIS", &mu_Hlt2Phys_TIS, &b_mu_Hlt2Phys_TIS);
   fChain->SetBranchAddress("mu_Hlt2Phys_TOS", &mu_Hlt2Phys_TOS, &b_mu_Hlt2Phys_TOS);
   fChain->SetBranchAddress("mu_L0MuonDecision_Dec", &mu_L0MuonDecision_Dec, &b_mu_L0MuonDecision_Dec);
   fChain->SetBranchAddress("mu_L0MuonDecision_TIS", &mu_L0MuonDecision_TIS, &b_mu_L0MuonDecision_TIS);
   fChain->SetBranchAddress("mu_L0MuonDecision_TOS", &mu_L0MuonDecision_TOS, &b_mu_L0MuonDecision_TOS);
   fChain->SetBranchAddress("mu_L0DiMuonDecision_Dec", &mu_L0DiMuonDecision_Dec, &b_mu_L0DiMuonDecision_Dec);
   fChain->SetBranchAddress("mu_L0DiMuonDecision_TIS", &mu_L0DiMuonDecision_TIS, &b_mu_L0DiMuonDecision_TIS);
   fChain->SetBranchAddress("mu_L0DiMuonDecision_TOS", &mu_L0DiMuonDecision_TOS, &b_mu_L0DiMuonDecision_TOS);
   fChain->SetBranchAddress("mu_L0HadronDecision_Dec", &mu_L0HadronDecision_Dec, &b_mu_L0HadronDecision_Dec);
   fChain->SetBranchAddress("mu_L0HadronDecision_TIS", &mu_L0HadronDecision_TIS, &b_mu_L0HadronDecision_TIS);
   fChain->SetBranchAddress("mu_L0HadronDecision_TOS", &mu_L0HadronDecision_TOS, &b_mu_L0HadronDecision_TOS);
   fChain->SetBranchAddress("mu_L0ElectronDecision_Dec", &mu_L0ElectronDecision_Dec, &b_mu_L0ElectronDecision_Dec);
   fChain->SetBranchAddress("mu_L0ElectronDecision_TIS", &mu_L0ElectronDecision_TIS, &b_mu_L0ElectronDecision_TIS);
   fChain->SetBranchAddress("mu_L0ElectronDecision_TOS", &mu_L0ElectronDecision_TOS, &b_mu_L0ElectronDecision_TOS);
   fChain->SetBranchAddress("mu_L0ElectronHiDecision_Dec", &mu_L0ElectronHiDecision_Dec, &b_mu_L0ElectronHiDecision_Dec);
   fChain->SetBranchAddress("mu_L0ElectronHiDecision_TIS", &mu_L0ElectronHiDecision_TIS, &b_mu_L0ElectronHiDecision_TIS);
   fChain->SetBranchAddress("mu_L0ElectronHiDecision_TOS", &mu_L0ElectronHiDecision_TOS, &b_mu_L0ElectronHiDecision_TOS);
   fChain->SetBranchAddress("mu_L0PhotonDecision_Dec", &mu_L0PhotonDecision_Dec, &b_mu_L0PhotonDecision_Dec);
   fChain->SetBranchAddress("mu_L0PhotonDecision_TIS", &mu_L0PhotonDecision_TIS, &b_mu_L0PhotonDecision_TIS);
   fChain->SetBranchAddress("mu_L0PhotonDecision_TOS", &mu_L0PhotonDecision_TOS, &b_mu_L0PhotonDecision_TOS);
   fChain->SetBranchAddress("mu_L0PhotonHiDecision_Dec", &mu_L0PhotonHiDecision_Dec, &b_mu_L0PhotonHiDecision_Dec);
   fChain->SetBranchAddress("mu_L0PhotonHiDecision_TIS", &mu_L0PhotonHiDecision_TIS, &b_mu_L0PhotonHiDecision_TIS);
   fChain->SetBranchAddress("mu_L0PhotonHiDecision_TOS", &mu_L0PhotonHiDecision_TOS, &b_mu_L0PhotonHiDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt1SingleMuonNoIPDecision_Dec", &mu_Hlt1SingleMuonNoIPDecision_Dec, &b_mu_Hlt1SingleMuonNoIPDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt1SingleMuonNoIPDecision_TIS", &mu_Hlt1SingleMuonNoIPDecision_TIS, &b_mu_Hlt1SingleMuonNoIPDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt1SingleMuonNoIPDecision_TOS", &mu_Hlt1SingleMuonNoIPDecision_TOS, &b_mu_Hlt1SingleMuonNoIPDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt1SingleMuonHighPTDecision_Dec", &mu_Hlt1SingleMuonHighPTDecision_Dec, &b_mu_Hlt1SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt1SingleMuonHighPTDecision_TIS", &mu_Hlt1SingleMuonHighPTDecision_TIS, &b_mu_Hlt1SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt1SingleMuonHighPTDecision_TOS", &mu_Hlt1SingleMuonHighPTDecision_TOS, &b_mu_Hlt1SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt1SingleElectronNoIPDecision_Dec", &mu_Hlt1SingleElectronNoIPDecision_Dec, &b_mu_Hlt1SingleElectronNoIPDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt1SingleElectronNoIPDecision_TIS", &mu_Hlt1SingleElectronNoIPDecision_TIS, &b_mu_Hlt1SingleElectronNoIPDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt1SingleElectronNoIPDecision_TOS", &mu_Hlt1SingleElectronNoIPDecision_TOS, &b_mu_Hlt1SingleElectronNoIPDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt1TrackAllL0Decision_Dec", &mu_Hlt1TrackAllL0Decision_Dec, &b_mu_Hlt1TrackAllL0Decision_Dec);
   fChain->SetBranchAddress("mu_Hlt1TrackAllL0Decision_TIS", &mu_Hlt1TrackAllL0Decision_TIS, &b_mu_Hlt1TrackAllL0Decision_TIS);
   fChain->SetBranchAddress("mu_Hlt1TrackAllL0Decision_TOS", &mu_Hlt1TrackAllL0Decision_TOS, &b_mu_Hlt1TrackAllL0Decision_TOS);
   fChain->SetBranchAddress("mu_Hlt1TrackMuonDecision_Dec", &mu_Hlt1TrackMuonDecision_Dec, &b_mu_Hlt1TrackMuonDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt1TrackMuonDecision_TIS", &mu_Hlt1TrackMuonDecision_TIS, &b_mu_Hlt1TrackMuonDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt1TrackMuonDecision_TOS", &mu_Hlt1TrackMuonDecision_TOS, &b_mu_Hlt1TrackMuonDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt1TrackPhotonDecision_Dec", &mu_Hlt1TrackPhotonDecision_Dec, &b_mu_Hlt1TrackPhotonDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt1TrackPhotonDecision_TIS", &mu_Hlt1TrackPhotonDecision_TIS, &b_mu_Hlt1TrackPhotonDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt1TrackPhotonDecision_TOS", &mu_Hlt1TrackPhotonDecision_TOS, &b_mu_Hlt1TrackPhotonDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt1TrackAllL0__Decision_Dec", &mu_Hlt1TrackAllL0__Decision_Dec, &b_mu_Hlt1TrackAllL0__Decision_Dec);
   fChain->SetBranchAddress("mu_Hlt1TrackAllL0__Decision_TIS", &mu_Hlt1TrackAllL0__Decision_TIS, &b_mu_Hlt1TrackAllL0__Decision_TIS);
   fChain->SetBranchAddress("mu_Hlt1TrackAllL0__Decision_TOS", &mu_Hlt1TrackAllL0__Decision_TOS, &b_mu_Hlt1TrackAllL0__Decision_TOS);
   fChain->SetBranchAddress("mu_Hlt1DiMuonLowMassDecision_Dec", &mu_Hlt1DiMuonLowMassDecision_Dec, &b_mu_Hlt1DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt1DiMuonLowMassDecision_TIS", &mu_Hlt1DiMuonLowMassDecision_TIS, &b_mu_Hlt1DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt1DiMuonLowMassDecision_TOS", &mu_Hlt1DiMuonLowMassDecision_TOS, &b_mu_Hlt1DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt1DiMuonHighMassDecision_Dec", &mu_Hlt1DiMuonHighMassDecision_Dec, &b_mu_Hlt1DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt1DiMuonHighMassDecision_TIS", &mu_Hlt1DiMuonHighMassDecision_TIS, &b_mu_Hlt1DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt1DiMuonHighMassDecision_TOS", &mu_Hlt1DiMuonHighMassDecision_TOS, &b_mu_Hlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt1MB__Decision_Dec", &mu_Hlt1MB__Decision_Dec, &b_mu_Hlt1MB__Decision_Dec);
   fChain->SetBranchAddress("mu_Hlt1MB__Decision_TIS", &mu_Hlt1MB__Decision_TIS, &b_mu_Hlt1MB__Decision_TIS);
   fChain->SetBranchAddress("mu_Hlt1MB__Decision_TOS", &mu_Hlt1MB__Decision_TOS, &b_mu_Hlt1MB__Decision_TOS);
   fChain->SetBranchAddress("mu_Hlt1TrackAllL0TightDecision_Dec", &mu_Hlt1TrackAllL0TightDecision_Dec, &b_mu_Hlt1TrackAllL0TightDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt1TrackAllL0TightDecision_TIS", &mu_Hlt1TrackAllL0TightDecision_TIS, &b_mu_Hlt1TrackAllL0TightDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt1TrackAllL0TightDecision_TOS", &mu_Hlt1TrackAllL0TightDecision_TOS, &b_mu_Hlt1TrackAllL0TightDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2SingleMuonDecision_Dec", &mu_Hlt2SingleMuonDecision_Dec, &b_mu_Hlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2SingleMuonDecision_TIS", &mu_Hlt2SingleMuonDecision_TIS, &b_mu_Hlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2SingleMuonDecision_TOS", &mu_Hlt2SingleMuonDecision_TOS, &b_mu_Hlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2SingleMuonLowPTDecision_Dec", &mu_Hlt2SingleMuonLowPTDecision_Dec, &b_mu_Hlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2SingleMuonLowPTDecision_TIS", &mu_Hlt2SingleMuonLowPTDecision_TIS, &b_mu_Hlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2SingleMuonLowPTDecision_TOS", &mu_Hlt2SingleMuonLowPTDecision_TOS, &b_mu_Hlt2SingleMuonLowPTDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2SingleMuonHighPTDecision_Dec", &mu_Hlt2SingleMuonHighPTDecision_Dec, &b_mu_Hlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2SingleMuonHighPTDecision_TIS", &mu_Hlt2SingleMuonHighPTDecision_TIS, &b_mu_Hlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2SingleMuonHighPTDecision_TOS", &mu_Hlt2SingleMuonHighPTDecision_TOS, &b_mu_Hlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonDecision_Dec", &mu_Hlt2DiMuonDecision_Dec, &b_mu_Hlt2DiMuonDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2DiMuonDecision_TIS", &mu_Hlt2DiMuonDecision_TIS, &b_mu_Hlt2DiMuonDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonDecision_TOS", &mu_Hlt2DiMuonDecision_TOS, &b_mu_Hlt2DiMuonDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonLowMassDecision_Dec", &mu_Hlt2DiMuonLowMassDecision_Dec, &b_mu_Hlt2DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2DiMuonLowMassDecision_TIS", &mu_Hlt2DiMuonLowMassDecision_TIS, &b_mu_Hlt2DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonLowMassDecision_TOS", &mu_Hlt2DiMuonLowMassDecision_TOS, &b_mu_Hlt2DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonJPsiHighPTDecision_Dec", &mu_Hlt2DiMuonJPsiHighPTDecision_Dec, &b_mu_Hlt2DiMuonJPsiHighPTDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2DiMuonJPsiHighPTDecision_TIS", &mu_Hlt2DiMuonJPsiHighPTDecision_TIS, &b_mu_Hlt2DiMuonJPsiHighPTDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonJPsiHighPTDecision_TOS", &mu_Hlt2DiMuonJPsiHighPTDecision_TOS, &b_mu_Hlt2DiMuonJPsiHighPTDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonPsi2SDecision_Dec", &mu_Hlt2DiMuonPsi2SDecision_Dec, &b_mu_Hlt2DiMuonPsi2SDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2DiMuonPsi2SDecision_TIS", &mu_Hlt2DiMuonPsi2SDecision_TIS, &b_mu_Hlt2DiMuonPsi2SDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonPsi2SDecision_TOS", &mu_Hlt2DiMuonPsi2SDecision_TOS, &b_mu_Hlt2DiMuonPsi2SDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonDetachedDecision_Dec", &mu_Hlt2DiMuonDetachedDecision_Dec, &b_mu_Hlt2DiMuonDetachedDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2DiMuonDetachedDecision_TIS", &mu_Hlt2DiMuonDetachedDecision_TIS, &b_mu_Hlt2DiMuonDetachedDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonDetachedDecision_TOS", &mu_Hlt2DiMuonDetachedDecision_TOS, &b_mu_Hlt2DiMuonDetachedDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonDetachedJPsiDecision_Dec", &mu_Hlt2DiMuonDetachedJPsiDecision_Dec, &b_mu_Hlt2DiMuonDetachedJPsiDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2DiMuonDetachedJPsiDecision_TIS", &mu_Hlt2DiMuonDetachedJPsiDecision_TIS, &b_mu_Hlt2DiMuonDetachedJPsiDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonDetachedJPsiDecision_TOS", &mu_Hlt2DiMuonDetachedJPsiDecision_TOS, &b_mu_Hlt2DiMuonDetachedJPsiDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonDetachedHeavyDecision_Dec", &mu_Hlt2DiMuonDetachedHeavyDecision_Dec, &b_mu_Hlt2DiMuonDetachedHeavyDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2DiMuonDetachedHeavyDecision_TIS", &mu_Hlt2DiMuonDetachedHeavyDecision_TIS, &b_mu_Hlt2DiMuonDetachedHeavyDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonDetachedHeavyDecision_TOS", &mu_Hlt2DiMuonDetachedHeavyDecision_TOS, &b_mu_Hlt2DiMuonDetachedHeavyDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2TriMuonTauDecision_Dec", &mu_Hlt2TriMuonTauDecision_Dec, &b_mu_Hlt2TriMuonTauDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2TriMuonTauDecision_TIS", &mu_Hlt2TriMuonTauDecision_TIS, &b_mu_Hlt2TriMuonTauDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2TriMuonTauDecision_TOS", &mu_Hlt2TriMuonTauDecision_TOS, &b_mu_Hlt2TriMuonTauDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2B2HHDecision_Dec", &mu_Hlt2B2HHDecision_Dec, &b_mu_Hlt2B2HHDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2B2HHDecision_TIS", &mu_Hlt2B2HHDecision_TIS, &b_mu_Hlt2B2HHDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2B2HHDecision_TOS", &mu_Hlt2B2HHDecision_TOS, &b_mu_Hlt2B2HHDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonBDecision_Dec", &mu_Hlt2DiMuonBDecision_Dec, &b_mu_Hlt2DiMuonBDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2DiMuonBDecision_TIS", &mu_Hlt2DiMuonBDecision_TIS, &b_mu_Hlt2DiMuonBDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonBDecision_TOS", &mu_Hlt2DiMuonBDecision_TOS, &b_mu_Hlt2DiMuonBDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonZDecision_Dec", &mu_Hlt2DiMuonZDecision_Dec, &b_mu_Hlt2DiMuonZDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2DiMuonZDecision_TIS", &mu_Hlt2DiMuonZDecision_TIS, &b_mu_Hlt2DiMuonZDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonZDecision_TOS", &mu_Hlt2DiMuonZDecision_TOS, &b_mu_Hlt2DiMuonZDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2TopoMu2BodyBBDTDecision_Dec", &mu_Hlt2TopoMu2BodyBBDTDecision_Dec, &b_mu_Hlt2TopoMu2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2TopoMu2BodyBBDTDecision_TIS", &mu_Hlt2TopoMu2BodyBBDTDecision_TIS, &b_mu_Hlt2TopoMu2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2TopoMu2BodyBBDTDecision_TOS", &mu_Hlt2TopoMu2BodyBBDTDecision_TOS, &b_mu_Hlt2TopoMu2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2TopoMu3BodyBBDTDecision_Dec", &mu_Hlt2TopoMu3BodyBBDTDecision_Dec, &b_mu_Hlt2TopoMu3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2TopoMu3BodyBBDTDecision_TIS", &mu_Hlt2TopoMu3BodyBBDTDecision_TIS, &b_mu_Hlt2TopoMu3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2TopoMu3BodyBBDTDecision_TOS", &mu_Hlt2TopoMu3BodyBBDTDecision_TOS, &b_mu_Hlt2TopoMu3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2TopoMu4BodyBBDTDecision_Dec", &mu_Hlt2TopoMu4BodyBBDTDecision_Dec, &b_mu_Hlt2TopoMu4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2TopoMu4BodyBBDTDecision_TIS", &mu_Hlt2TopoMu4BodyBBDTDecision_TIS, &b_mu_Hlt2TopoMu4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2TopoMu4BodyBBDTDecision_TOS", &mu_Hlt2TopoMu4BodyBBDTDecision_TOS, &b_mu_Hlt2TopoMu4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2Topo2BodyBBDTDecision_Dec", &mu_Hlt2Topo2BodyBBDTDecision_Dec, &b_mu_Hlt2Topo2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2Topo2BodyBBDTDecision_TIS", &mu_Hlt2Topo2BodyBBDTDecision_TIS, &b_mu_Hlt2Topo2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2Topo2BodyBBDTDecision_TOS", &mu_Hlt2Topo2BodyBBDTDecision_TOS, &b_mu_Hlt2Topo2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2Topo3BodyBBDTDecision_Dec", &mu_Hlt2Topo3BodyBBDTDecision_Dec, &b_mu_Hlt2Topo3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2Topo3BodyBBDTDecision_TIS", &mu_Hlt2Topo3BodyBBDTDecision_TIS, &b_mu_Hlt2Topo3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2Topo3BodyBBDTDecision_TOS", &mu_Hlt2Topo3BodyBBDTDecision_TOS, &b_mu_Hlt2Topo3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2Topo4BodyBBDTDecision_Dec", &mu_Hlt2Topo4BodyBBDTDecision_Dec, &b_mu_Hlt2Topo4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2Topo4BodyBBDTDecision_TIS", &mu_Hlt2Topo4BodyBBDTDecision_TIS, &b_mu_Hlt2Topo4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2Topo4BodyBBDTDecision_TOS", &mu_Hlt2Topo4BodyBBDTDecision_TOS, &b_mu_Hlt2Topo4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2Topo2BodySimpleDecision_Dec", &mu_Hlt2Topo2BodySimpleDecision_Dec, &b_mu_Hlt2Topo2BodySimpleDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2Topo2BodySimpleDecision_TIS", &mu_Hlt2Topo2BodySimpleDecision_TIS, &b_mu_Hlt2Topo2BodySimpleDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2Topo2BodySimpleDecision_TOS", &mu_Hlt2Topo2BodySimpleDecision_TOS, &b_mu_Hlt2Topo2BodySimpleDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2Topo3BodySimpleDecision_Dec", &mu_Hlt2Topo3BodySimpleDecision_Dec, &b_mu_Hlt2Topo3BodySimpleDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2Topo3BodySimpleDecision_TIS", &mu_Hlt2Topo3BodySimpleDecision_TIS, &b_mu_Hlt2Topo3BodySimpleDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2Topo3BodySimpleDecision_TOS", &mu_Hlt2Topo3BodySimpleDecision_TOS, &b_mu_Hlt2Topo3BodySimpleDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2Topo4BodySimpleDecision_Dec", &mu_Hlt2Topo4BodySimpleDecision_Dec, &b_mu_Hlt2Topo4BodySimpleDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2Topo4BodySimpleDecision_TIS", &mu_Hlt2Topo4BodySimpleDecision_TIS, &b_mu_Hlt2Topo4BodySimpleDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2Topo4BodySimpleDecision_TOS", &mu_Hlt2Topo4BodySimpleDecision_TOS, &b_mu_Hlt2Topo4BodySimpleDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2PassThroughDecision_Dec", &mu_Hlt2PassThroughDecision_Dec, &b_mu_Hlt2PassThroughDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2PassThroughDecision_TIS", &mu_Hlt2PassThroughDecision_TIS, &b_mu_Hlt2PassThroughDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2PassThroughDecision_TOS", &mu_Hlt2PassThroughDecision_TOS, &b_mu_Hlt2PassThroughDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2TransparentDecision_Dec", &mu_Hlt2TransparentDecision_Dec, &b_mu_Hlt2TransparentDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2TransparentDecision_TIS", &mu_Hlt2TransparentDecision_TIS, &b_mu_Hlt2TransparentDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2TransparentDecision_TOS", &mu_Hlt2TransparentDecision_TOS, &b_mu_Hlt2TransparentDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2IncPhiDecision_Dec", &mu_Hlt2IncPhiDecision_Dec, &b_mu_Hlt2IncPhiDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2IncPhiDecision_TIS", &mu_Hlt2IncPhiDecision_TIS, &b_mu_Hlt2IncPhiDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2IncPhiDecision_TOS", &mu_Hlt2IncPhiDecision_TOS, &b_mu_Hlt2IncPhiDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonDY__Decision_Dec", &mu_Hlt2DiMuonDY__Decision_Dec, &b_mu_Hlt2DiMuonDY__Decision_Dec);
   fChain->SetBranchAddress("mu_Hlt2DiMuonDY__Decision_TIS", &mu_Hlt2DiMuonDY__Decision_TIS, &b_mu_Hlt2DiMuonDY__Decision_TIS);
   fChain->SetBranchAddress("mu_Hlt2DiMuonDY__Decision_TOS", &mu_Hlt2DiMuonDY__Decision_TOS, &b_mu_Hlt2DiMuonDY__Decision_TOS);
   fChain->SetBranchAddress("mu_Hlt2TopoE__Decision_Dec", &mu_Hlt2TopoE__Decision_Dec, &b_mu_Hlt2TopoE__Decision_Dec);
   fChain->SetBranchAddress("mu_Hlt2TopoE__Decision_TIS", &mu_Hlt2TopoE__Decision_TIS, &b_mu_Hlt2TopoE__Decision_TIS);
   fChain->SetBranchAddress("mu_Hlt2TopoE__Decision_TOS", &mu_Hlt2TopoE__Decision_TOS, &b_mu_Hlt2TopoE__Decision_TOS);
   fChain->SetBranchAddress("mu_Hlt2Topo__Decision_Dec", &mu_Hlt2Topo__Decision_Dec, &b_mu_Hlt2Topo__Decision_Dec);
   fChain->SetBranchAddress("mu_Hlt2Topo__Decision_TIS", &mu_Hlt2Topo__Decision_TIS, &b_mu_Hlt2Topo__Decision_TIS);
   fChain->SetBranchAddress("mu_Hlt2Topo__Decision_TOS", &mu_Hlt2Topo__Decision_TOS, &b_mu_Hlt2Topo__Decision_TOS);
   fChain->SetBranchAddress("mu_Hlt2Charm__Decision_Dec", &mu_Hlt2Charm__Decision_Dec, &b_mu_Hlt2Charm__Decision_Dec);
   fChain->SetBranchAddress("mu_Hlt2Charm__Decision_TIS", &mu_Hlt2Charm__Decision_TIS, &b_mu_Hlt2Charm__Decision_TIS);
   fChain->SetBranchAddress("mu_Hlt2Charm__Decision_TOS", &mu_Hlt2Charm__Decision_TOS, &b_mu_Hlt2Charm__Decision_TOS);
   fChain->SetBranchAddress("mu_Hlt2DiElectron__Decision_Dec", &mu_Hlt2DiElectron__Decision_Dec, &b_mu_Hlt2DiElectron__Decision_Dec);
   fChain->SetBranchAddress("mu_Hlt2DiElectron__Decision_TIS", &mu_Hlt2DiElectron__Decision_TIS, &b_mu_Hlt2DiElectron__Decision_TIS);
   fChain->SetBranchAddress("mu_Hlt2DiElectron__Decision_TOS", &mu_Hlt2DiElectron__Decision_TOS, &b_mu_Hlt2DiElectron__Decision_TOS);
   fChain->SetBranchAddress("mu_Hlt2__GammaDecision_Dec", &mu_Hlt2__GammaDecision_Dec, &b_mu_Hlt2__GammaDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2__GammaDecision_TIS", &mu_Hlt2__GammaDecision_TIS, &b_mu_Hlt2__GammaDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2__GammaDecision_TOS", &mu_Hlt2__GammaDecision_TOS, &b_mu_Hlt2__GammaDecision_TOS);
   fChain->SetBranchAddress("mu_TRACK_Type", &mu_TRACK_Type, &b_mu_TRACK_Type);
   fChain->SetBranchAddress("mu_TRACK_Key", &mu_TRACK_Key, &b_mu_TRACK_Key);
   fChain->SetBranchAddress("mu_TRACK_CHI2NDOF", &mu_TRACK_CHI2NDOF, &b_mu_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("mu_TRACK_PCHI2", &mu_TRACK_PCHI2, &b_mu_TRACK_PCHI2);
   fChain->SetBranchAddress("mu_TRACK_MatchCHI2", &mu_TRACK_MatchCHI2, &b_mu_TRACK_MatchCHI2);
   fChain->SetBranchAddress("mu_TRACK_GhostProb", &mu_TRACK_GhostProb, &b_mu_TRACK_GhostProb);
   fChain->SetBranchAddress("mu_TRACK_CloneDist", &mu_TRACK_CloneDist, &b_mu_TRACK_CloneDist);
   fChain->SetBranchAddress("mu_TRACK_Likelihood", &mu_TRACK_Likelihood, &b_mu_TRACK_Likelihood);
   fChain->SetBranchAddress("nCandidate", &nCandidate, &b_nCandidate);
   fChain->SetBranchAddress("totCandidates", &totCandidates, &b_totCandidates);
   fChain->SetBranchAddress("EventInSequence", &EventInSequence, &b_EventInSequence);
   fChain->SetBranchAddress("nVeloTraks_All", &nVeloTraks_All, &b_nVeloTraks_All);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("BCID", &BCID, &b_BCID);
   fChain->SetBranchAddress("BCType", &BCType, &b_BCType);
   fChain->SetBranchAddress("OdinTCK", &OdinTCK, &b_OdinTCK);
   fChain->SetBranchAddress("L0DUTCK", &L0DUTCK, &b_L0DUTCK);
   fChain->SetBranchAddress("HLT1TCK", &HLT1TCK, &b_HLT1TCK);
   fChain->SetBranchAddress("HLT2TCK", &HLT2TCK, &b_HLT2TCK);
   fChain->SetBranchAddress("GpsTime", &GpsTime, &b_GpsTime);
   fChain->SetBranchAddress("Polarity", &Polarity, &b_Polarity);
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
   fChain->SetBranchAddress("L0Global", &L0Global, &b_L0Global);
   fChain->SetBranchAddress("Hlt1Global", &Hlt1Global, &b_Hlt1Global);
   fChain->SetBranchAddress("Hlt2Global", &Hlt2Global, &b_Hlt2Global);
   Notify();
}

Bool_t NeutralIsoData::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void NeutralIsoData::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t NeutralIsoData::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef NeutralIsoData_cxx
