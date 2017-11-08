//
// Authors: Matteo Rama (INFN Pisa), 29 March 2016
//
//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Mar 12 12:24:35 2016 by ROOT version 5.34/25
// from TTree DecayTree/DecayTree
// found on file: bbbar2MuMuX_highpt_MC12_MagUp_selection.root
//////////////////////////////////////////////////////////
#ifndef addIso_h
#define addIso_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

//bips stuff
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TVector3.h"
#include "TMatrixDSym.h"

#include <string>

using namespace std;

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxB_ENDVERTEX_COV = 1;
   const Int_t kMaxB_OWNPV_COV = 1;
   const Int_t kMaxmuplus_OWNPV_COV = 1;
   const Int_t kMaxmuplus_ORIVX_COV = 1;
   const Int_t kMaxmuminus_OWNPV_COV = 1;
   const Int_t kMaxmuminus_ORIVX_COV = 1;

class addIso {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        B_BPVDIRA;
   Double_t        B_BPVIPCHI2;
   Double_t        B_BPVVDCHI2;
   Double_t        B_BPVVDZ;
   Double_t        B_DOCAMAX;
   Double_t        B_MINIPCHI2;
   Double_t        B_VFASPF;
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
   Int_t           B_ID;
   Double_t        B_eta;
   Double_t        B_phi;
   Double_t        B_D1_isolation_Giampi;
   Double_t        B_D2_isolation_Giampi;
   Double_t        B_D1_isolation_Giampi_tc;
   Double_t        B_D2_isolation_Giampi_tc;
   Double_t        B_D1_isolation_Giampi_new1;
   Double_t        B_D2_isolation_Giampi_new1;
   Double_t        B_D1_isolation_Giampi_new2;
   Double_t        B_D2_isolation_Giampi_new2;
   Double_t        B_D1_isolation_Giampi_newD0;
   Double_t        B_D2_isolation_Giampi_newD0;
   Double_t        B_yetanother_CDF_iso;
   Double_t        B_yetanother_CDF_iso_tc;
   Double_t        B_doca;
   Double_t        B_cosnk;
   Float_t         B_BDTS_BIPS;
   Float_t         B_BDTS_DOCA;
   Float_t         B_BDTS_VTXCHI2;
   Float_t         B_BDTS_DIRA;
   Float_t         B_BDTS_BIP;
   Float_t         B_BDTS_MuonMINIP;
   Double_t        B_BDTS;
   Double_t        B_CTAU_ps;
   Int_t           IsoSTIdx;
   Float_t         IsoST_trk_typ[500];   //[IsoSTIdx]
   Float_t         IsoST_trk_chi[500];   //[IsoSTIdx]
   Float_t         IsoST_trk_chg[500];   //[IsoSTIdx]
   Float_t         IsoST_trk_pt[500];   //[IsoSTIdx]
   Float_t         IsoST_trk_gho[500];   //[IsoSTIdx]
   Float_t         IsoST_trk_clo[500];   //[IsoSTIdx]
   Float_t         IsoST_trk_ips[500];   //[IsoSTIdx]
   Float_t         IsoST_trk_hlt[500];   //[IsoSTIdx]
   Float_t         IsoST_fim_angle[500];   //[IsoSTIdx]
   Float_t         IsoST_fim_fc[500];   //[IsoSTIdx]
   Float_t         IsoST_fim_doca[500];   //[IsoSTIdx]
   Float_t         IsoST_fim_doca2[500];   //[IsoSTIdx]
   Float_t         IsoST_fim_docachi2[500];   //[IsoSTIdx]
   Float_t         IsoST_fim_svdis[500];   //[IsoSTIdx]
   Float_t         IsoST_fim_pvdis[500];   //[IsoSTIdx]
   Float_t         IsoST_fim_vtxx[500];   //[IsoSTIdx]
   Float_t         IsoST_fim_vtxy[500];   //[IsoSTIdx]
   Float_t         IsoST_fim_vtxz[500];   //[IsoSTIdx]
   Float_t         IsoST_sem_angle[500];   //[IsoSTIdx]
   Float_t         IsoST_sem_fc[500];   //[IsoSTIdx]
   Float_t         IsoST_sem_doca[500];   //[IsoSTIdx]
   Float_t         IsoST_sem_doca2[500];   //[IsoSTIdx]
   Float_t         IsoST_sem_docachi2[500];   //[IsoSTIdx]
   Float_t         IsoST_sem_svdis[500];   //[IsoSTIdx]
   Float_t         IsoST_sem_pvdis[500];   //[IsoSTIdx]
   Float_t         IsoST_sem_vtxx[500];   //[IsoSTIdx]
   Float_t         IsoST_sem_vtxy[500];   //[IsoSTIdx]
   Float_t         IsoST_sem_vtxz[500];   //[IsoSTIdx]
   Double_t        B_D1_isobdt1_1st;
   Double_t        B_D1_isobdt1_2nd;
   Double_t        B_D1_isobdt1_3rd;
   Double_t        B_D2_isobdt1_1st;
   Double_t        B_D2_isobdt1_2nd;
   Double_t        B_D2_isobdt1_3rd;
   Double_t        B_D1_isobdt2_1st;
   Double_t        B_D1_isobdt2_2nd;
   Double_t        B_D1_isobdt2_3rd;
   Double_t        B_D2_isobdt2_1st;
   Double_t        B_D2_isobdt2_2nd;
   Double_t        B_D2_isobdt2_3rd;
   Double_t        B_D1_isobdt3_1st;
   Double_t        B_D1_isobdt3_2nd;
   Double_t        B_D1_isobdt3_3rd;
   Double_t        B_D2_isobdt3_1st;
   Double_t        B_D2_isobdt3_2nd;
   Double_t        B_D2_isobdt3_3rd;
   Double_t        B_D1_isobdt4_1st;
   Double_t        B_D1_isobdt4_2nd;
   Double_t        B_D1_isobdt4_3rd;
   Double_t        B_D2_isobdt4_1st;
   Double_t        B_D2_isobdt4_2nd;
   Double_t        B_D2_isobdt4_3rd;
   Double_t        B_CDFiso;
   Double_t        B_CDFiso_tc;
   Double_t        B_otherB_mag;
   Double_t        B_otherB_ang;
   Int_t           B_otherB_ntrk;
   Double_t        B_otherB_boo_mag;
   Double_t        B_otherB_boo_ang;
   Int_t           EVB_Nparts;
   Int_t           pbIdx;
   Float_t         EVB_par_pos_x[500];   //[pbIdx]
   Float_t         EVB_par_pos_y[500];   //[pbIdx]
   Float_t         EVB_par_pos_z[500];   //[pbIdx]
   Float_t         EVB_par_pos_covxx[500];   //[pbIdx]
   Float_t         EVB_par_pos_covyy[500];   //[pbIdx]
   Float_t         EVB_par_pos_covxy[500];   //[pbIdx]
   Float_t         EVB_par_fmpos_x[500];   //[pbIdx]
   Float_t         EVB_par_fmpos_y[500];   //[pbIdx]
   Float_t         EVB_par_fmpos_z[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov00[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov11[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov22[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov33[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov44[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov55[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov01[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov02[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov12[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov34[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov35[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov45[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov03[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov04[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov05[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov13[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov14[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov15[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov23[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov24[500];   //[pbIdx]
   Float_t         EVB_par_xp_cov25[500];   //[pbIdx]
   Float_t         EVB_par_px[500];   //[pbIdx]
   Float_t         EVB_par_py[500];   //[pbIdx]
   Float_t         EVB_par_pz[500];   //[pbIdx]
   Float_t         EVB_par_pt[500];   //[pbIdx]
   Float_t         EVB_par_p[500];   //[pbIdx]
   Float_t         EVB_par_chg[500];   //[pbIdx]
   Float_t         EVB_par_typ[500];   //[pbIdx]
   Float_t         EVB_par_gho[500];   //[pbIdx]
   Float_t         EVB_par_chi[500];   //[pbIdx]
   Float_t         EVB_par_clo[500];   //[pbIdx]
   Float_t         EVB_par_ip[500];   //[pbIdx]
   Float_t         EVB_par_ips[500];   //[pbIdx]
   Float_t         EVB_par_hlt[500];   //[pbIdx]
   Float_t         EVB_par_slope_covxx[500];   //[pbIdx]
   Float_t         EVB_par_slope_covyy[500];   //[pbIdx]
   Float_t         EVB_par_slope_covxy[500];   //[pbIdx]
   Float_t         EVB_par_NNe[500];   //[pbIdx]
   Float_t         EVB_par_NNmu[500];   //[pbIdx]
   Float_t         EVB_par_NNpi[500];   //[pbIdx]
   Float_t         EVB_par_NNk[500];   //[pbIdx]
   Float_t         EVB_par_NNp[500];   //[pbIdx]
   Float_t         EVB_par_NNghost[500];   //[pbIdx]
   Float_t         EVB_par_DLLe[500];   //[pbIdx]
   Float_t         EVB_par_DLLmu[500];   //[pbIdx]
   Float_t         EVB_par_DLLk[500];   //[pbIdx]
   Float_t         EVB_par_DLLp[500];   //[pbIdx]
   Float_t         EVB_par_isMuon[500];   //[pbIdx]
   Float_t         EVB_par_PVind[500];   //[pbIdx]
   Float_t         EVB_isMCMatched[500];   //[pbIdx]
   Float_t         EVB_true_Origin_ID[500];   //[pbIdx]
   Float_t         EVB_true_part_Ori_Vtx_x[500];   //[pbIdx]
   Float_t         EVB_true_part_Ori_Vtx_y[500];   //[pbIdx]
   Float_t         EVB_true_part_Ori_Vtx_z[500];   //[pbIdx]
   Float_t         EVB_true_part_Ori_type[500];   //[pbIdx]
   Float_t         EVB_true_part_ID[500];   //[pbIdx]
   Float_t         EVB_true_isnoniso_mup[500];   //[pbIdx]
   Float_t         EVB_true_isnoniso_mum[500];   //[pbIdx]
   Float_t         EVB_true_part_Px[500];   //[pbIdx]
   Float_t         EVB_true_part_Py[500];   //[pbIdx]
   Float_t         EVB_true_part_Pz[500];   //[pbIdx]
   Float_t         EVB_true_part_E[500];   //[pbIdx]
   Float_t         EVB_true_part_M[500];   //[pbIdx]
   Float_t         EVB_true_part_hasMother[500];   //[pbIdx]
   Float_t         EVB_true_moth_Ori_Vtx_x[500];   //[pbIdx]
   Float_t         EVB_true_moth_Ori_Vtx_y[500];   //[pbIdx]
   Float_t         EVB_true_moth_Ori_Vtx_z[500];   //[pbIdx]
   Float_t         EVB_true_moth_ID[500];   //[pbIdx]
   Float_t         EVB_true_moth_Px[500];   //[pbIdx]
   Float_t         EVB_true_moth_Py[500];   //[pbIdx]
   Float_t         EVB_true_moth_Pz[500];   //[pbIdx]
   Float_t         EVB_true_moth_E[500];   //[pbIdx]
   Float_t         EVB_true_moth_M[500];   //[pbIdx]
   Float_t         EVB_true_moth_hasMother[500];   //[pbIdx]
   Float_t         EVB_true_gran_Ori_Vtx_x[500];   //[pbIdx]
   Float_t         EVB_true_gran_Ori_Vtx_y[500];   //[pbIdx]
   Float_t         EVB_true_gran_Ori_Vtx_z[500];   //[pbIdx]
   Float_t         EVB_true_gran_ID[500];   //[pbIdx]
   Float_t         EVB_true_gran_Px[500];   //[pbIdx]
   Float_t         EVB_true_gran_Py[500];   //[pbIdx]
   Float_t         EVB_true_gran_Pz[500];   //[pbIdx]
   Float_t         EVB_true_gran_E[500];   //[pbIdx]
   Float_t         EVB_true_gran_M[500];   //[pbIdx]
   Float_t         EVB_true_gran_hasMother[500];   //[pbIdx]
   Float_t         EVB_true_mogr_Ori_Vtx_x[500];   //[pbIdx]
   Float_t         EVB_true_mogr_Ori_Vtx_y[500];   //[pbIdx]
   Float_t         EVB_true_mogr_Ori_Vtx_z[500];   //[pbIdx]
   Float_t         EVB_true_mogr_ID[500];   //[pbIdx]
   Float_t         EVB_true_mogr_Px[500];   //[pbIdx]
   Float_t         EVB_true_mogr_Py[500];   //[pbIdx]
   Float_t         EVB_true_mogr_Pz[500];   //[pbIdx]
   Float_t         EVB_true_mogr_E[500];   //[pbIdx]
   Float_t         EVB_true_mogr_M[500];   //[pbIdx]
   Float_t         EVB_true_mogr_hasMother[500];   //[pbIdx]
   Float_t         EVB_true_grgr_Ori_Vtx_x[500];   //[pbIdx]
   Float_t         EVB_true_grgr_Ori_Vtx_y[500];   //[pbIdx]
   Float_t         EVB_true_grgr_Ori_Vtx_z[500];   //[pbIdx]
   Float_t         EVB_true_grgr_ID[500];   //[pbIdx]
   Float_t         EVB_true_grgr_Px[500];   //[pbIdx]
   Float_t         EVB_true_grgr_Py[500];   //[pbIdx]
   Float_t         EVB_true_grgr_Pz[500];   //[pbIdx]
   Float_t         EVB_true_grgr_E[500];   //[pbIdx]
   Float_t         EVB_true_grgr_M[500];   //[pbIdx]
   Int_t           PV_num;
   Float_t         PV_x[30];   //[PV_num]
   Float_t         PV_y[30];   //[PV_num]
   Float_t         PV_z[30];   //[PV_num]
   Float_t         PV_covxx[30];   //[PV_num]
   Float_t         PV_covyy[30];   //[PV_num]
   Float_t         PV_covzz[30];   //[PV_num]
   Float_t         PV_covxy[30];   //[PV_num]
   Float_t         PV_covxz[30];   //[PV_num]
   Float_t         PV_covyz[30];   //[PV_num]
   Float_t         PV_chi2PerDoF[30];   //[PV_num]
   Float_t         PV_nDoF[30];   //[PV_num]
   Float_t         PV_ntrk[30];   //[PV_num]
   Int_t           PV2_num;
   Float_t         PV2_x[30];   //[PV2_num]
   Float_t         PV2_y[30];   //[PV2_num]
   Float_t         PV2_z[30];   //[PV2_num]
   Float_t         PV2_covxx[30];   //[PV2_num]
   Float_t         PV2_covyy[30];   //[PV2_num]
   Float_t         PV2_covzz[30];   //[PV2_num]
   Float_t         PV2_covxy[30];   //[PV2_num]
   Float_t         PV2_covxz[30];   //[PV2_num]
   Float_t         PV2_covyz[30];   //[PV2_num]
   Float_t         PV2_chi2PerDoF[30];   //[PV2_num]
   Float_t         PV2_nDoF[30];   //[PV2_num]
   Float_t         PV2_ntrk[30];   //[PV2_num]
   Double_t        B_cov00;
   Double_t        B_cov01;
   Double_t        B_cov02;
   Double_t        B_cov03;
   Double_t        B_cov04;
   Double_t        B_cov05;
   Double_t        B_cov06;
   Double_t        B_cov11;
   Double_t        B_cov12;
   Double_t        B_cov13;
   Double_t        B_cov14;
   Double_t        B_cov15;
   Double_t        B_cov16;
   Double_t        B_cov22;
   Double_t        B_cov23;
   Double_t        B_cov24;
   Double_t        B_cov25;
   Double_t        B_cov26;
   Double_t        B_cov33;
   Double_t        B_cov34;
   Double_t        B_cov35;
   Double_t        B_cov36;
   Double_t        B_cov44;
   Double_t        B_cov45;
   Double_t        B_cov46;
   Double_t        B_cov55;
   Double_t        B_cov56;
   Double_t        B_cov66;
   Int_t           VEL_num;
   Float_t         VEL_par_pos_x[500];   //[VEL_num]
   Float_t         VEL_par_pos_y[500];   //[VEL_num]
   Float_t         VEL_par_pos_z[500];   //[VEL_num]
   Float_t         VEL_par_fmpos_x[500];   //[VEL_num]
   Float_t         VEL_par_fmpos_y[500];   //[VEL_num]
   Float_t         VEL_par_fmpos_z[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov00[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov11[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov22[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov33[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov44[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov55[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov01[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov02[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov12[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov34[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov35[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov45[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov03[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov04[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov05[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov13[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov14[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov15[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov23[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov24[500];   //[VEL_num]
   Float_t         VEL_par_xp_cov25[500];   //[VEL_num]
   Float_t         VEL_par_px[500];   //[VEL_num]
   Float_t         VEL_par_py[500];   //[VEL_num]
   Float_t         VEL_par_pz[500];   //[VEL_num]
   Float_t         VEL_par_pt[500];   //[VEL_num]
   Float_t         VEL_par_p[500];   //[VEL_num]
   Float_t         VEL_par_chg[500];   //[VEL_num]
   Float_t         VEL_par_slope_covxx[500];   //[VEL_num]
   Float_t         VEL_par_slope_covyy[500];   //[VEL_num]
   Float_t         VEL_par_slope_covxy[500];   //[VEL_num]
   Float_t         VEL_par_back[500];   //[VEL_num]
   Float_t         VEL_par_typ[500];   //[VEL_num]
   Float_t         VEL_par_gho[500];   //[VEL_num]
   Float_t         VEL_par_chi[500];   //[VEL_num]
   Float_t         VEL_par_clo[500];   //[VEL_num]
   Float_t         VEL_par_PVind[500];   //[VEL_num]
   Float_t         VEL_isMCMatched[500];   //[VEL_num]
   Float_t         VEL_true_Origin_ID[500];   //[VEL_num]
   Float_t         VEL_true_part_Ori_Vtx_x[500];   //[VEL_num]
   Float_t         VEL_true_part_Ori_Vtx_y[500];   //[VEL_num]
   Float_t         VEL_true_part_Ori_Vtx_z[500];   //[VEL_num]
   Float_t         VEL_true_part_Ori_type[500];   //[VEL_num]
   Float_t         VEL_true_part_ID[500];   //[VEL_num]
   Float_t         VEL_true_isnoniso_mup[500];   //[VEL_num]
   Float_t         VEL_true_isnoniso_mum[500];   //[VEL_num]
   Float_t         VEL_true_part_Px[500];   //[VEL_num]
   Float_t         VEL_true_part_Py[500];   //[VEL_num]
   Float_t         VEL_true_part_Pz[500];   //[VEL_num]
   Float_t         VEL_true_part_E[500];   //[VEL_num]
   Float_t         VEL_true_part_M[500];   //[VEL_num]
   Float_t         VEL_true_part_hasMother[500];   //[VEL_num]
   Float_t         VEL_true_moth_Ori_Vtx_x[500];   //[VEL_num]
   Float_t         VEL_true_moth_Ori_Vtx_y[500];   //[VEL_num]
   Float_t         VEL_true_moth_Ori_Vtx_z[500];   //[VEL_num]
   Float_t         VEL_true_moth_ID[500];   //[VEL_num]
   Float_t         VEL_true_moth_Px[500];   //[VEL_num]
   Float_t         VEL_true_moth_Py[500];   //[VEL_num]
   Float_t         VEL_true_moth_Pz[500];   //[VEL_num]
   Float_t         VEL_true_moth_E[500];   //[VEL_num]
   Float_t         VEL_true_moth_M[500];   //[VEL_num]
   Float_t         VEL_true_moth_hasMother[500];   //[VEL_num]
   Float_t         VEL_true_gran_Ori_Vtx_x[500];   //[VEL_num]
   Float_t         VEL_true_gran_Ori_Vtx_y[500];   //[VEL_num]
   Float_t         VEL_true_gran_Ori_Vtx_z[500];   //[VEL_num]
   Float_t         VEL_true_gran_ID[500];   //[VEL_num]
   Float_t         VEL_true_gran_Px[500];   //[VEL_num]
   Float_t         VEL_true_gran_Py[500];   //[VEL_num]
   Float_t         VEL_true_gran_Pz[500];   //[VEL_num]
   Float_t         VEL_true_gran_E[500];   //[VEL_num]
   Float_t         VEL_true_gran_M[500];   //[VEL_num]
   Float_t         VEL_true_gran_hasMother[500];   //[VEL_num]
   Float_t         VEL_true_mogr_Ori_Vtx_x[500];   //[VEL_num]
   Float_t         VEL_true_mogr_Ori_Vtx_y[500];   //[VEL_num]
   Float_t         VEL_true_mogr_Ori_Vtx_z[500];   //[VEL_num]
   Float_t         VEL_true_mogr_ID[500];   //[VEL_num]
   Float_t         VEL_true_mogr_Px[500];   //[VEL_num]
   Float_t         VEL_true_mogr_Py[500];   //[VEL_num]
   Float_t         VEL_true_mogr_Pz[500];   //[VEL_num]
   Float_t         VEL_true_mogr_E[500];   //[VEL_num]
   Float_t         VEL_true_mogr_M[500];   //[VEL_num]
   Float_t         VEL_true_mogr_hasMother[500];   //[VEL_num]
   Float_t         VEL_true_grgr_Ori_Vtx_x[500];   //[VEL_num]
   Float_t         VEL_true_grgr_Ori_Vtx_y[500];   //[VEL_num]
   Float_t         VEL_true_grgr_Ori_Vtx_z[500];   //[VEL_num]
   Float_t         VEL_true_grgr_ID[500];   //[VEL_num]
   Float_t         VEL_true_grgr_Px[500];   //[VEL_num]
   Float_t         VEL_true_grgr_Py[500];   //[VEL_num]
   Float_t         VEL_true_grgr_Pz[500];   //[VEL_num]
   Float_t         VEL_true_grgr_E[500];   //[VEL_num]
   Float_t         VEL_true_grgr_M[500];   //[VEL_num]
   Int_t           US_num;
   Float_t         US_par_pos_x[250];   //[US_num]
   Float_t         US_par_pos_y[250];   //[US_num]
   Float_t         US_par_pos_z[250];   //[US_num]
   Float_t         US_par_fmpos_x[250];   //[US_num]
   Float_t         US_par_fmpos_y[250];   //[US_num]
   Float_t         US_par_fmpos_z[250];   //[US_num]
   Float_t         US_par_xp_cov00[250];   //[US_num]
   Float_t         US_par_xp_cov11[250];   //[US_num]
   Float_t         US_par_xp_cov22[250];   //[US_num]
   Float_t         US_par_xp_cov33[250];   //[US_num]
   Float_t         US_par_xp_cov44[250];   //[US_num]
   Float_t         US_par_xp_cov55[250];   //[US_num]
   Float_t         US_par_xp_cov01[250];   //[US_num]
   Float_t         US_par_xp_cov02[250];   //[US_num]
   Float_t         US_par_xp_cov12[250];   //[US_num]
   Float_t         US_par_xp_cov34[250];   //[US_num]
   Float_t         US_par_xp_cov35[250];   //[US_num]
   Float_t         US_par_xp_cov45[250];   //[US_num]
   Float_t         US_par_xp_cov03[250];   //[US_num]
   Float_t         US_par_xp_cov04[250];   //[US_num]
   Float_t         US_par_xp_cov05[250];   //[US_num]
   Float_t         US_par_xp_cov13[250];   //[US_num]
   Float_t         US_par_xp_cov14[250];   //[US_num]
   Float_t         US_par_xp_cov15[250];   //[US_num]
   Float_t         US_par_xp_cov23[250];   //[US_num]
   Float_t         US_par_xp_cov24[250];   //[US_num]
   Float_t         US_par_xp_cov25[250];   //[US_num]
   Float_t         US_par_px[250];   //[US_num]
   Float_t         US_par_py[250];   //[US_num]
   Float_t         US_par_pz[250];   //[US_num]
   Float_t         US_par_pt[250];   //[US_num]
   Float_t         US_par_p[250];   //[US_num]
   Float_t         US_par_chg[250];   //[US_num]
   Float_t         US_par_slope_covxx[250];   //[US_num]
   Float_t         US_par_slope_covyy[250];   //[US_num]
   Float_t         US_par_slope_covxy[250];   //[US_num]
   Float_t         US_par_typ[250];   //[US_num]
   Float_t         US_par_gho[250];   //[US_num]
   Float_t         US_par_chi[250];   //[US_num]
   Float_t         US_par_clo[250];   //[US_num]
   Float_t         US_par_NNe[250];   //[US_num]
   Float_t         US_par_NNmu[250];   //[US_num]
   Float_t         US_par_NNpi[250];   //[US_num]
   Float_t         US_par_NNk[250];   //[US_num]
   Float_t         US_par_NNp[250];   //[US_num]
   Float_t         US_par_NNghost[250];   //[US_num]
   Float_t         US_par_DLLe[250];   //[US_num]
   Float_t         US_par_DLLmu[250];   //[US_num]
   Float_t         US_par_DLLk[250];   //[US_num]
   Float_t         US_par_DLLp[250];   //[US_num]
   Float_t         US_par_isMuon[250];   //[US_num]
   Float_t         US_par_PVind[250];   //[US_num]
   Float_t         US_isMCMatched[250];   //[US_num]
   Float_t         US_true_Origin_ID[250];   //[US_num]
   Float_t         US_true_part_Ori_Vtx_x[250];   //[US_num]
   Float_t         US_true_part_Ori_Vtx_y[250];   //[US_num]
   Float_t         US_true_part_Ori_Vtx_z[250];   //[US_num]
   Float_t         US_true_part_Ori_type[250];   //[US_num]
   Float_t         US_true_part_ID[250];   //[US_num]
   Float_t         US_true_isnoniso_mup[250];   //[US_num]
   Float_t         US_true_isnoniso_mum[250];   //[US_num]
   Float_t         US_true_part_Px[250];   //[US_num]
   Float_t         US_true_part_Py[250];   //[US_num]
   Float_t         US_true_part_Pz[250];   //[US_num]
   Float_t         US_true_part_E[250];   //[US_num]
   Float_t         US_true_part_M[250];   //[US_num]
   Float_t         US_true_part_hasMother[250];   //[US_num]
   Float_t         US_true_moth_Ori_Vtx_x[250];   //[US_num]
   Float_t         US_true_moth_Ori_Vtx_y[250];   //[US_num]
   Float_t         US_true_moth_Ori_Vtx_z[250];   //[US_num]
   Float_t         US_true_moth_ID[250];   //[US_num]
   Float_t         US_true_moth_Px[250];   //[US_num]
   Float_t         US_true_moth_Py[250];   //[US_num]
   Float_t         US_true_moth_Pz[250];   //[US_num]
   Float_t         US_true_moth_E[250];   //[US_num]
   Float_t         US_true_moth_M[250];   //[US_num]
   Float_t         US_true_moth_hasMother[250];   //[US_num]
   Float_t         US_true_gran_Ori_Vtx_x[250];   //[US_num]
   Float_t         US_true_gran_Ori_Vtx_y[250];   //[US_num]
   Float_t         US_true_gran_Ori_Vtx_z[250];   //[US_num]
   Float_t         US_true_gran_ID[250];   //[US_num]
   Float_t         US_true_gran_Px[250];   //[US_num]
   Float_t         US_true_gran_Py[250];   //[US_num]
   Float_t         US_true_gran_Pz[250];   //[US_num]
   Float_t         US_true_gran_E[250];   //[US_num]
   Float_t         US_true_gran_M[250];   //[US_num]
   Float_t         US_true_gran_hasMother[250];   //[US_num]
   Float_t         US_true_mogr_Ori_Vtx_x[250];   //[US_num]
   Float_t         US_true_mogr_Ori_Vtx_y[250];   //[US_num]
   Float_t         US_true_mogr_Ori_Vtx_z[250];   //[US_num]
   Float_t         US_true_mogr_ID[250];   //[US_num]
   Float_t         US_true_mogr_Px[250];   //[US_num]
   Float_t         US_true_mogr_Py[250];   //[US_num]
   Float_t         US_true_mogr_Pz[250];   //[US_num]
   Float_t         US_true_mogr_E[250];   //[US_num]
   Float_t         US_true_mogr_M[250];   //[US_num]
   Float_t         US_true_mogr_hasMother[250];   //[US_num]
   Float_t         US_true_grgr_Ori_Vtx_x[250];   //[US_num]
   Float_t         US_true_grgr_Ori_Vtx_y[250];   //[US_num]
   Float_t         US_true_grgr_Ori_Vtx_z[250];   //[US_num]
   Float_t         US_true_grgr_ID[250];   //[US_num]
   Float_t         US_true_grgr_Px[250];   //[US_num]
   Float_t         US_true_grgr_Py[250];   //[US_num]
   Float_t         US_true_grgr_Pz[250];   //[US_num]
   Float_t         US_true_grgr_E[250];   //[US_num]
   Float_t         US_true_grgr_M[250];   //[US_num]
   Int_t           MCGEN_num;
   Float_t         MCGEN_partindex[750];   //[MCGEN_num]
   Float_t         MCGEN_motindex[750];   //[MCGEN_num]
   Float_t         MCGEN_lundid[750];   //[MCGEN_num]
   Float_t         MCGEN_px[750];   //[MCGEN_num]
   Float_t         MCGEN_py[750];   //[MCGEN_num]
   Float_t         MCGEN_pz[750];   //[MCGEN_num]
   Float_t         MCGEN_vtx_x[750];   //[MCGEN_num]
   Float_t         MCGEN_vtx_y[750];   //[MCGEN_num]
   Float_t         MCGEN_vtx_z[750];   //[MCGEN_num]
   Float_t         MCGEN_origtype[750];   //[MCGEN_num]
   Double_t        B_typeOriginVtx;
   Double_t        B_nEndVertices;
   Double_t        B_ancestorpid;
   Double_t        B_MCI;
   Double_t        B_TAU;
   Double_t        B_TAUERR;
   Double_t        B_TAUCHI2;
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
   Bool_t          B_L0MuonDecision_Dec;
   Bool_t          B_L0MuonDecision_TIS;
   Bool_t          B_L0MuonDecision_TOS;
   Bool_t          B_L0DiMuonDecision_Dec;
   Bool_t          B_L0DiMuonDecision_TIS;
   Bool_t          B_L0DiMuonDecision_TOS;
   Bool_t          B_L0HadronDecision_Dec;
   Bool_t          B_L0HadronDecision_TIS;
   Bool_t          B_L0HadronDecision_TOS;
   Bool_t          B_L0ElectronDecision_Dec;
   Bool_t          B_L0ElectronDecision_TIS;
   Bool_t          B_L0ElectronDecision_TOS;
   Bool_t          B_L0ElectronHiDecision_Dec;
   Bool_t          B_L0ElectronHiDecision_TIS;
   Bool_t          B_L0ElectronHiDecision_TOS;
   Bool_t          B_L0PhotonDecision_Dec;
   Bool_t          B_L0PhotonDecision_TIS;
   Bool_t          B_L0PhotonDecision_TOS;
   Bool_t          B_L0PhotonHiDecision_Dec;
   Bool_t          B_L0PhotonHiDecision_TIS;
   Bool_t          B_L0PhotonHiDecision_TOS;
   Bool_t          B_Hlt1SingleMuonNoIPDecision_Dec;
   Bool_t          B_Hlt1SingleMuonNoIPDecision_TIS;
   Bool_t          B_Hlt1SingleMuonNoIPDecision_TOS;
   Bool_t          B_Hlt1SingleMuonHighPTDecision_Dec;
   Bool_t          B_Hlt1SingleMuonHighPTDecision_TIS;
   Bool_t          B_Hlt1SingleMuonHighPTDecision_TOS;
   Bool_t          B_Hlt1SingleElectronNoIPDecision_Dec;
   Bool_t          B_Hlt1SingleElectronNoIPDecision_TIS;
   Bool_t          B_Hlt1SingleElectronNoIPDecision_TOS;
   Bool_t          B_Hlt1TrackAllL0Decision_Dec;
   Bool_t          B_Hlt1TrackAllL0Decision_TIS;
   Bool_t          B_Hlt1TrackAllL0Decision_TOS;
   Bool_t          B_Hlt1TrackMuonDecision_Dec;
   Bool_t          B_Hlt1TrackMuonDecision_TIS;
   Bool_t          B_Hlt1TrackMuonDecision_TOS;
   Bool_t          B_Hlt1TrackPhotonDecision_Dec;
   Bool_t          B_Hlt1TrackPhotonDecision_TIS;
   Bool_t          B_Hlt1TrackPhotonDecision_TOS;
   Bool_t          B_Hlt1TrackAllL0__Decision_Dec;
   Bool_t          B_Hlt1TrackAllL0__Decision_TIS;
   Bool_t          B_Hlt1TrackAllL0__Decision_TOS;
   Bool_t          B_Hlt1DiMuonLowMassDecision_Dec;
   Bool_t          B_Hlt1DiMuonLowMassDecision_TIS;
   Bool_t          B_Hlt1DiMuonLowMassDecision_TOS;
   Bool_t          B_Hlt1DiMuonHighMassDecision_Dec;
   Bool_t          B_Hlt1DiMuonHighMassDecision_TIS;
   Bool_t          B_Hlt1DiMuonHighMassDecision_TOS;
   Bool_t          B_Hlt1MB__Decision_Dec;
   Bool_t          B_Hlt1MB__Decision_TIS;
   Bool_t          B_Hlt1MB__Decision_TOS;
   Bool_t          B_Hlt1TrackAllL0TightDecision_Dec;
   Bool_t          B_Hlt1TrackAllL0TightDecision_TIS;
   Bool_t          B_Hlt1TrackAllL0TightDecision_TOS;
   Bool_t          B_Hlt2SingleMuonDecision_Dec;
   Bool_t          B_Hlt2SingleMuonDecision_TIS;
   Bool_t          B_Hlt2SingleMuonDecision_TOS;
   Bool_t          B_Hlt2SingleMuonLowPTDecision_Dec;
   Bool_t          B_Hlt2SingleMuonLowPTDecision_TIS;
   Bool_t          B_Hlt2SingleMuonLowPTDecision_TOS;
   Bool_t          B_Hlt2SingleMuonHighPTDecision_Dec;
   Bool_t          B_Hlt2SingleMuonHighPTDecision_TIS;
   Bool_t          B_Hlt2SingleMuonHighPTDecision_TOS;
   Bool_t          B_Hlt2DiMuonDecision_Dec;
   Bool_t          B_Hlt2DiMuonDecision_TIS;
   Bool_t          B_Hlt2DiMuonDecision_TOS;
   Bool_t          B_Hlt2DiMuonLowMassDecision_Dec;
   Bool_t          B_Hlt2DiMuonLowMassDecision_TIS;
   Bool_t          B_Hlt2DiMuonLowMassDecision_TOS;
   Bool_t          B_Hlt2DiMuonJPsiDecision_Dec;
   Bool_t          B_Hlt2DiMuonJPsiDecision_TIS;
   Bool_t          B_Hlt2DiMuonJPsiDecision_TOS;
   Bool_t          B_Hlt2DiMuonJPsiHighPTDecision_Dec;
   Bool_t          B_Hlt2DiMuonJPsiHighPTDecision_TIS;
   Bool_t          B_Hlt2DiMuonJPsiHighPTDecision_TOS;
   Bool_t          B_Hlt2DiMuonPsi2SDecision_Dec;
   Bool_t          B_Hlt2DiMuonPsi2SDecision_TIS;
   Bool_t          B_Hlt2DiMuonPsi2SDecision_TOS;
   Bool_t          B_Hlt2DiMuonDetachedDecision_Dec;
   Bool_t          B_Hlt2DiMuonDetachedDecision_TIS;
   Bool_t          B_Hlt2DiMuonDetachedDecision_TOS;
   Bool_t          B_Hlt2DiMuonDetachedJPsiDecision_Dec;
   Bool_t          B_Hlt2DiMuonDetachedJPsiDecision_TIS;
   Bool_t          B_Hlt2DiMuonDetachedJPsiDecision_TOS;
   Bool_t          B_Hlt2DiMuonDetachedHeavyDecision_Dec;
   Bool_t          B_Hlt2DiMuonDetachedHeavyDecision_TIS;
   Bool_t          B_Hlt2DiMuonDetachedHeavyDecision_TOS;
   Bool_t          B_Hlt2TriMuonTauDecision_Dec;
   Bool_t          B_Hlt2TriMuonTauDecision_TIS;
   Bool_t          B_Hlt2TriMuonTauDecision_TOS;
   Bool_t          B_Hlt2B2HHDecision_Dec;
   Bool_t          B_Hlt2B2HHDecision_TIS;
   Bool_t          B_Hlt2B2HHDecision_TOS;
   Bool_t          B_Hlt2DiMuonBDecision_Dec;
   Bool_t          B_Hlt2DiMuonBDecision_TIS;
   Bool_t          B_Hlt2DiMuonBDecision_TOS;
   Bool_t          B_Hlt2DiMuonZDecision_Dec;
   Bool_t          B_Hlt2DiMuonZDecision_TIS;
   Bool_t          B_Hlt2DiMuonZDecision_TOS;
   Bool_t          B_Hlt2TopoMu2BodyBBDTDecision_Dec;
   Bool_t          B_Hlt2TopoMu2BodyBBDTDecision_TIS;
   Bool_t          B_Hlt2TopoMu2BodyBBDTDecision_TOS;
   Bool_t          B_Hlt2TopoMu3BodyBBDTDecision_Dec;
   Bool_t          B_Hlt2TopoMu3BodyBBDTDecision_TIS;
   Bool_t          B_Hlt2TopoMu3BodyBBDTDecision_TOS;
   Bool_t          B_Hlt2TopoMu4BodyBBDTDecision_Dec;
   Bool_t          B_Hlt2TopoMu4BodyBBDTDecision_TIS;
   Bool_t          B_Hlt2TopoMu4BodyBBDTDecision_TOS;
   Bool_t          B_Hlt2Topo2BodyBBDTDecision_Dec;
   Bool_t          B_Hlt2Topo2BodyBBDTDecision_TIS;
   Bool_t          B_Hlt2Topo2BodyBBDTDecision_TOS;
   Bool_t          B_Hlt2Topo3BodyBBDTDecision_Dec;
   Bool_t          B_Hlt2Topo3BodyBBDTDecision_TIS;
   Bool_t          B_Hlt2Topo3BodyBBDTDecision_TOS;
   Bool_t          B_Hlt2Topo4BodyBBDTDecision_Dec;
   Bool_t          B_Hlt2Topo4BodyBBDTDecision_TIS;
   Bool_t          B_Hlt2Topo4BodyBBDTDecision_TOS;
   Bool_t          B_Hlt2Topo2BodySimpleDecision_Dec;
   Bool_t          B_Hlt2Topo2BodySimpleDecision_TIS;
   Bool_t          B_Hlt2Topo2BodySimpleDecision_TOS;
   Bool_t          B_Hlt2Topo3BodySimpleDecision_Dec;
   Bool_t          B_Hlt2Topo3BodySimpleDecision_TIS;
   Bool_t          B_Hlt2Topo3BodySimpleDecision_TOS;
   Bool_t          B_Hlt2Topo4BodySimpleDecision_Dec;
   Bool_t          B_Hlt2Topo4BodySimpleDecision_TIS;
   Bool_t          B_Hlt2Topo4BodySimpleDecision_TOS;
   Bool_t          B_Hlt2PassThroughDecision_Dec;
   Bool_t          B_Hlt2PassThroughDecision_TIS;
   Bool_t          B_Hlt2PassThroughDecision_TOS;
   Bool_t          B_Hlt2TransparentDecision_Dec;
   Bool_t          B_Hlt2TransparentDecision_TIS;
   Bool_t          B_Hlt2TransparentDecision_TOS;
   Bool_t          B_Hlt2IncPhiDecision_Dec;
   Bool_t          B_Hlt2IncPhiDecision_TIS;
   Bool_t          B_Hlt2IncPhiDecision_TOS;
   Bool_t          B_Hlt2DiMuonDY__Decision_Dec;
   Bool_t          B_Hlt2DiMuonDY__Decision_TIS;
   Bool_t          B_Hlt2DiMuonDY__Decision_TOS;
   Bool_t          B_Hlt2TopoE__Decision_Dec;
   Bool_t          B_Hlt2TopoE__Decision_TIS;
   Bool_t          B_Hlt2TopoE__Decision_TOS;
   Bool_t          B_Hlt2Topo__Decision_Dec;
   Bool_t          B_Hlt2Topo__Decision_TIS;
   Bool_t          B_Hlt2Topo__Decision_TOS;
   Bool_t          B_Hlt2Charm__Decision_Dec;
   Bool_t          B_Hlt2Charm__Decision_TIS;
   Bool_t          B_Hlt2Charm__Decision_TOS;
   Bool_t          B_Hlt2DiElectron__Decision_Dec;
   Bool_t          B_Hlt2DiElectron__Decision_TIS;
   Bool_t          B_Hlt2DiElectron__Decision_TOS;
   Bool_t          B_Hlt2__GammaDecision_Dec;
   Bool_t          B_Hlt2__GammaDecision_TIS;
   Bool_t          B_Hlt2__GammaDecision_TOS;
   Double_t        B_DTF_M;
   Double_t        B_DTF_MM;
   Double_t        B_DTF_P;
   Double_t        B_DTF_PE;
   Double_t        B_DTF_PT;
   Double_t        B_DTF_PX;
   Double_t        B_DTF_PY;
   Double_t        B_DTF_PZ;
   Double_t        B_DTF_VFit_M;
   Double_t        B_DTF_VFit_MM;
   Double_t        B_DTF_VFit_P;
   Double_t        B_DTF_VFit_PE;
   Double_t        B_DTF_VFit_PT;
   Double_t        B_DTF_VFit_PX;
   Double_t        B_DTF_VFit_PY;
   Double_t        B_DTF_VFit_PZ;
   Double_t        B_WRONGMASS_K_K;
   Double_t        B_WRONGMASS_K_p;
   Double_t        B_WRONGMASS_K_pi;
   Double_t        B_WRONGMASS_p_K;
   Double_t        B_WRONGMASS_p_pi;
   Double_t        B_WRONGMASS_pi_K;
   Double_t        B_WRONGMASS_pi_p;
   Double_t        B_WRONGMASS_pi_pi;
   Double_t        B_WRONGMASS_K_K_2;
   Double_t        B_WRONGMASS_K_p_2;
   Double_t        B_WRONGMASS_K_pi_2;
   Double_t        B_WRONGMASS_p_K_2;
   Double_t        B_WRONGMASS_p_pi_2;
   Double_t        B_WRONGMASS_pi_K_2;
   Double_t        B_WRONGMASS_pi_p_2;
   Double_t        B_WRONGMASS_pi_pi_2;
   Float_t         B_Vf;
   Float_t         MPT_iso;
   Float_t         MPT_iso_UpS;
   Float_t         MPT_iso_DwS;
   Float_t         Vf_Max;
   Float_t         Vf_Max_UpS;
   Float_t         Vf_Max_DwS;
   Float_t         Pos_Max;
   Float_t         Pos_Max_UpS;
   Float_t         Pos_Max_DwS;
   Float_t         sum_Vf_Maxs;
   Float_t         sum_Vf_Maxs_UpS;
   Float_t         B_ZVtop_nvtx;
   Float_t         B_zv_same;
   Float_t         MuP_zv_ipsall;
   Float_t         MuP_zv_ipall;
   Float_t         MuP_zv_proba;
   Float_t         MuP_zv_proba_close;
   Float_t         MuP_zv_chi2;
   Float_t         MuP_zv_dist;
   Float_t         MuP_zv_ntrkvtz;
   Float_t         MuM_zv_ipsall;
   Float_t         MuM_zv_ipall;
   Float_t         MuM_zv_proba;
   Float_t         MuM_zv_proba_close;
   Float_t         MuM_zv_chi2;
   Float_t         MuM_zv_dist;
   Float_t         MuM_zv_ntrkvtz;
   Float_t         zv_ipsall;
   Float_t         zv_ipall;
   Float_t         zv_proba;
   Float_t         zv_proba_close;
   Float_t         zv_chi2;
   Float_t         zv_dist;
   Float_t         zv_ntrkvtz;
   Float_t         ZViso;
   Int_t           B_Fit_nPV;
   Float_t         B_Fit_M[100];   //[B_Fit_nPV]
   Float_t         B_Fit_MERR[100];   //[B_Fit_nPV]
   Float_t         B_Fit_P[100];   //[B_Fit_nPV]
   Float_t         B_Fit_PERR[100];   //[B_Fit_nPV]
   Float_t         B_Fit_chi2[100];   //[B_Fit_nPV]
   Float_t         B_Fit_muminus_0_ID[100];   //[B_Fit_nPV]
   Float_t         B_Fit_muminus_0_PE[100];   //[B_Fit_nPV]
   Float_t         B_Fit_muminus_0_PX[100];   //[B_Fit_nPV]
   Float_t         B_Fit_muminus_0_PY[100];   //[B_Fit_nPV]
   Float_t         B_Fit_muminus_0_PZ[100];   //[B_Fit_nPV]
   Float_t         B_Fit_muminus_ID[100];   //[B_Fit_nPV]
   Float_t         B_Fit_muminus_PE[100];   //[B_Fit_nPV]
   Float_t         B_Fit_muminus_PX[100];   //[B_Fit_nPV]
   Float_t         B_Fit_muminus_PY[100];   //[B_Fit_nPV]
   Float_t         B_Fit_muminus_PZ[100];   //[B_Fit_nPV]
   Float_t         B_Fit_nDOF[100];   //[B_Fit_nPV]
   Float_t         B_Fit_nIter[100];   //[B_Fit_nPV]
   Float_t         B_Fit_status[100];   //[B_Fit_nPV]
   Int_t           B_VFit_nPV;
   Float_t         B_VFit_M[100];   //[B_VFit_nPV]
   Float_t         B_VFit_MERR[100];   //[B_VFit_nPV]
   Float_t         B_VFit_P[100];   //[B_VFit_nPV]
   Float_t         B_VFit_PERR[100];   //[B_VFit_nPV]
   Float_t         B_VFit_PV_X[100];   //[B_VFit_nPV]
   Float_t         B_VFit_PV_Y[100];   //[B_VFit_nPV]
   Float_t         B_VFit_PV_Z[100];   //[B_VFit_nPV]
   Float_t         B_VFit_PV_key[100];   //[B_VFit_nPV]
   Float_t         B_VFit_chi2[100];   //[B_VFit_nPV]
   Float_t         B_VFit_ctau[100];   //[B_VFit_nPV]
   Float_t         B_VFit_ctauErr[100];   //[B_VFit_nPV]
   Float_t         B_VFit_decayLength[100];   //[B_VFit_nPV]
   Float_t         B_VFit_decayLengthErr[100];   //[B_VFit_nPV]
   Float_t         B_VFit_muminus_0_ID[100];   //[B_VFit_nPV]
   Float_t         B_VFit_muminus_0_PE[100];   //[B_VFit_nPV]
   Float_t         B_VFit_muminus_0_PX[100];   //[B_VFit_nPV]
   Float_t         B_VFit_muminus_0_PY[100];   //[B_VFit_nPV]
   Float_t         B_VFit_muminus_0_PZ[100];   //[B_VFit_nPV]
   Float_t         B_VFit_muminus_ID[100];   //[B_VFit_nPV]
   Float_t         B_VFit_muminus_PE[100];   //[B_VFit_nPV]
   Float_t         B_VFit_muminus_PX[100];   //[B_VFit_nPV]
   Float_t         B_VFit_muminus_PY[100];   //[B_VFit_nPV]
   Float_t         B_VFit_muminus_PZ[100];   //[B_VFit_nPV]
   Float_t         B_VFit_nDOF[100];   //[B_VFit_nPV]
   Float_t         B_VFit_nIter[100];   //[B_VFit_nPV]
   Float_t         B_VFit_status[100];   //[B_VFit_nPV]
   Double_t        B_JETNOMU1PX;
   Double_t        B_JETNOMU1PY;
   Double_t        B_JETNOMU1PZ;
   Double_t        B_JETNOMU1PT;
   Double_t        B_JETNOMU1JETWIDTH;
   Double_t        B_JETNOMU1NNTAG;
   Double_t        B_JETNOMU1MNF;
   Double_t        B_JETNOMU2PX;
   Double_t        B_JETNOMU2PY;
   Double_t        B_JETNOMU2PZ;
   Double_t        B_JETNOMU2PT;
   Double_t        B_JETNOMU2JETWIDTH;
   Double_t        B_JETNOMU2NNTAG;
   Double_t        B_JETNOMU2MNF;
   Double_t        B_JETNOMU3PX;
   Double_t        B_JETNOMU3PY;
   Double_t        B_JETNOMU3PZ;
   Double_t        B_JETNOMU3PT;
   Double_t        B_JETNOMU3JETWIDTH;
   Double_t        B_JETNOMU3NNTAG;
   Double_t        B_JETNOMU3MNF;
   Double_t        B_JETMU1PX;
   Double_t        B_JETMU1PY;
   Double_t        B_JETMU1PZ;
   Double_t        B_JETMU1PT;
   Double_t        B_JETMU1JETWIDTH;
   Double_t        B_JETMU1NNTAG;
   Double_t        B_JETMU1MNF;
   Double_t        B_JETBPX;
   Double_t        B_JETBPY;
   Double_t        B_JETBPZ;
   Double_t        B_JETBPT;
   Double_t        B_JETBJETWIDTH;
   Double_t        B_JETBNNTAG;
   Double_t        B_JETBMNF;
   Double_t        B_JETMU2PX;
   Double_t        B_JETMU2PY;
   Double_t        B_JETMU2PZ;
   Double_t        B_JETMU2PT;
   Double_t        B_JETMU2JETWIDTH;
   Double_t        B_JETMU2NNTAG;
   Double_t        B_JETMU2MNF;
   Double_t        muplus_BPVDIRA;
   Double_t        muplus_BPVIPCHI2;
   Double_t        muplus_BPVVDCHI2;
   Double_t        muplus_BPVVDZ;
   Double_t        muplus_DOCAMAX;
   Double_t        muplus_MINIPCHI2;
   Double_t        muplus_VFASPF;
   Double_t        muplus_MC12TuneV2_ProbNNe;
   Double_t        muplus_MC12TuneV2_ProbNNmu;
   Double_t        muplus_MC12TuneV2_ProbNNpi;
   Double_t        muplus_MC12TuneV2_ProbNNk;
   Double_t        muplus_MC12TuneV2_ProbNNp;
   Double_t        muplus_MC12TuneV2_ProbNNghost;
   Double_t        muplus_MC12TuneV3_ProbNNe;
   Double_t        muplus_MC12TuneV3_ProbNNmu;
   Double_t        muplus_MC12TuneV3_ProbNNpi;
   Double_t        muplus_MC12TuneV3_ProbNNk;
   Double_t        muplus_MC12TuneV3_ProbNNp;
   Double_t        muplus_MC12TuneV3_ProbNNghost;
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
   Double_t        muplus_Xs1;
   Double_t        muplus_Ys1;
   Double_t        muplus_Xs2;
   Double_t        muplus_Ys2;
   Double_t        muplus_Xs3;
   Double_t        muplus_Ys3;
   Double_t        muplus_Xs4;
   Double_t        muplus_Ys4;
   Double_t        muplus_Xs5;
   Double_t        muplus_Ys5;
   Float_t         muplus_DistAve;
   Int_t           muplus_ID;
   Double_t        muplus_CombDLLMu;
   Double_t        muplus_ProbNNmu;
   Double_t        muplus_ProbNNghost;
   Double_t        muplus_InMuonAcc;
   Double_t        muplus_MuonDist2;
   Int_t           muplus_regionInM2;
   Bool_t          muplus_hasMuon;
   Bool_t          muplus_isMuon;
   Bool_t          muplus_isMuonLoose;
   Int_t           muplus_NShared;
   Double_t        muplus_MuonLLmu;
   Double_t        muplus_MuonLLbg;
   Int_t           muplus_isMuonFromProto;
   Int_t           muplus_nVeloIDs;
   Int_t           muplus_nITIDs;
   Int_t           muplus_nTTIDs;
   Int_t           muplus_nOTIDs;
   Double_t        muplus_eta;
   Double_t        muplus_phi;
   Double_t        muplus_typeOriginVtx;
   Double_t        muplus_nEndVertices;
   Double_t        muplus_ancestorpid;
   Double_t        muplus_MCI;
   Double_t        muplus_PIDe;
   Double_t        muplus_PIDmu;
   Double_t        muplus_PIDK;
   Double_t        muplus_PIDp;
   Double_t        muplus_ProbNNe;
   Double_t        muplus_ProbNNk;
   Double_t        muplus_ProbNNp;
   Double_t        muplus_ProbNNpi;
   Bool_t          muplus_hasRich;
   Bool_t          muplus_hasCalo;
   Bool_t          muplus_L0Global_Dec;
   Bool_t          muplus_L0Global_TIS;
   Bool_t          muplus_L0Global_TOS;
   Bool_t          muplus_Hlt1Global_Dec;
   Bool_t          muplus_Hlt1Global_TIS;
   Bool_t          muplus_Hlt1Global_TOS;
   Bool_t          muplus_Hlt1Phys_Dec;
   Bool_t          muplus_Hlt1Phys_TIS;
   Bool_t          muplus_Hlt1Phys_TOS;
   Bool_t          muplus_Hlt2Global_Dec;
   Bool_t          muplus_Hlt2Global_TIS;
   Bool_t          muplus_Hlt2Global_TOS;
   Bool_t          muplus_Hlt2Phys_Dec;
   Bool_t          muplus_Hlt2Phys_TIS;
   Bool_t          muplus_Hlt2Phys_TOS;
   Bool_t          muplus_L0MuonDecision_Dec;
   Bool_t          muplus_L0MuonDecision_TIS;
   Bool_t          muplus_L0MuonDecision_TOS;
   Bool_t          muplus_L0DiMuonDecision_Dec;
   Bool_t          muplus_L0DiMuonDecision_TIS;
   Bool_t          muplus_L0DiMuonDecision_TOS;
   Bool_t          muplus_L0HadronDecision_Dec;
   Bool_t          muplus_L0HadronDecision_TIS;
   Bool_t          muplus_L0HadronDecision_TOS;
   Bool_t          muplus_L0ElectronDecision_Dec;
   Bool_t          muplus_L0ElectronDecision_TIS;
   Bool_t          muplus_L0ElectronDecision_TOS;
   Bool_t          muplus_L0ElectronHiDecision_Dec;
   Bool_t          muplus_L0ElectronHiDecision_TIS;
   Bool_t          muplus_L0ElectronHiDecision_TOS;
   Bool_t          muplus_L0PhotonDecision_Dec;
   Bool_t          muplus_L0PhotonDecision_TIS;
   Bool_t          muplus_L0PhotonDecision_TOS;
   Bool_t          muplus_L0PhotonHiDecision_Dec;
   Bool_t          muplus_L0PhotonHiDecision_TIS;
   Bool_t          muplus_L0PhotonHiDecision_TOS;
   Bool_t          muplus_Hlt1SingleMuonNoIPDecision_Dec;
   Bool_t          muplus_Hlt1SingleMuonNoIPDecision_TIS;
   Bool_t          muplus_Hlt1SingleMuonNoIPDecision_TOS;
   Bool_t          muplus_Hlt1SingleMuonHighPTDecision_Dec;
   Bool_t          muplus_Hlt1SingleMuonHighPTDecision_TIS;
   Bool_t          muplus_Hlt1SingleMuonHighPTDecision_TOS;
   Bool_t          muplus_Hlt1SingleElectronNoIPDecision_Dec;
   Bool_t          muplus_Hlt1SingleElectronNoIPDecision_TIS;
   Bool_t          muplus_Hlt1SingleElectronNoIPDecision_TOS;
   Bool_t          muplus_Hlt1TrackAllL0Decision_Dec;
   Bool_t          muplus_Hlt1TrackAllL0Decision_TIS;
   Bool_t          muplus_Hlt1TrackAllL0Decision_TOS;
   Bool_t          muplus_Hlt1TrackMuonDecision_Dec;
   Bool_t          muplus_Hlt1TrackMuonDecision_TIS;
   Bool_t          muplus_Hlt1TrackMuonDecision_TOS;
   Bool_t          muplus_Hlt1TrackPhotonDecision_Dec;
   Bool_t          muplus_Hlt1TrackPhotonDecision_TIS;
   Bool_t          muplus_Hlt1TrackPhotonDecision_TOS;
   Bool_t          muplus_Hlt1TrackAllL0__Decision_Dec;
   Bool_t          muplus_Hlt1TrackAllL0__Decision_TIS;
   Bool_t          muplus_Hlt1TrackAllL0__Decision_TOS;
   Bool_t          muplus_Hlt1DiMuonLowMassDecision_Dec;
   Bool_t          muplus_Hlt1DiMuonLowMassDecision_TIS;
   Bool_t          muplus_Hlt1DiMuonLowMassDecision_TOS;
   Bool_t          muplus_Hlt1DiMuonHighMassDecision_Dec;
   Bool_t          muplus_Hlt1DiMuonHighMassDecision_TIS;
   Bool_t          muplus_Hlt1DiMuonHighMassDecision_TOS;
   Bool_t          muplus_Hlt1MB__Decision_Dec;
   Bool_t          muplus_Hlt1MB__Decision_TIS;
   Bool_t          muplus_Hlt1MB__Decision_TOS;
   Bool_t          muplus_Hlt1TrackAllL0TightDecision_Dec;
   Bool_t          muplus_Hlt1TrackAllL0TightDecision_TIS;
   Bool_t          muplus_Hlt1TrackAllL0TightDecision_TOS;
   Bool_t          muplus_Hlt2SingleMuonDecision_Dec;
   Bool_t          muplus_Hlt2SingleMuonDecision_TIS;
   Bool_t          muplus_Hlt2SingleMuonDecision_TOS;
   Bool_t          muplus_Hlt2SingleMuonLowPTDecision_Dec;
   Bool_t          muplus_Hlt2SingleMuonLowPTDecision_TIS;
   Bool_t          muplus_Hlt2SingleMuonLowPTDecision_TOS;
   Bool_t          muplus_Hlt2SingleMuonHighPTDecision_Dec;
   Bool_t          muplus_Hlt2SingleMuonHighPTDecision_TIS;
   Bool_t          muplus_Hlt2SingleMuonHighPTDecision_TOS;
   Bool_t          muplus_Hlt2DiMuonDecision_Dec;
   Bool_t          muplus_Hlt2DiMuonDecision_TIS;
   Bool_t          muplus_Hlt2DiMuonDecision_TOS;
   Bool_t          muplus_Hlt2DiMuonLowMassDecision_Dec;
   Bool_t          muplus_Hlt2DiMuonLowMassDecision_TIS;
   Bool_t          muplus_Hlt2DiMuonLowMassDecision_TOS;
   Bool_t          muplus_Hlt2DiMuonJPsiDecision_Dec;
   Bool_t          muplus_Hlt2DiMuonJPsiDecision_TIS;
   Bool_t          muplus_Hlt2DiMuonJPsiDecision_TOS;
   Bool_t          muplus_Hlt2DiMuonJPsiHighPTDecision_Dec;
   Bool_t          muplus_Hlt2DiMuonJPsiHighPTDecision_TIS;
   Bool_t          muplus_Hlt2DiMuonJPsiHighPTDecision_TOS;
   Bool_t          muplus_Hlt2DiMuonPsi2SDecision_Dec;
   Bool_t          muplus_Hlt2DiMuonPsi2SDecision_TIS;
   Bool_t          muplus_Hlt2DiMuonPsi2SDecision_TOS;
   Bool_t          muplus_Hlt2DiMuonDetachedDecision_Dec;
   Bool_t          muplus_Hlt2DiMuonDetachedDecision_TIS;
   Bool_t          muplus_Hlt2DiMuonDetachedDecision_TOS;
   Bool_t          muplus_Hlt2DiMuonDetachedJPsiDecision_Dec;
   Bool_t          muplus_Hlt2DiMuonDetachedJPsiDecision_TIS;
   Bool_t          muplus_Hlt2DiMuonDetachedJPsiDecision_TOS;
   Bool_t          muplus_Hlt2DiMuonDetachedHeavyDecision_Dec;
   Bool_t          muplus_Hlt2DiMuonDetachedHeavyDecision_TIS;
   Bool_t          muplus_Hlt2DiMuonDetachedHeavyDecision_TOS;
   Bool_t          muplus_Hlt2TriMuonTauDecision_Dec;
   Bool_t          muplus_Hlt2TriMuonTauDecision_TIS;
   Bool_t          muplus_Hlt2TriMuonTauDecision_TOS;
   Bool_t          muplus_Hlt2B2HHDecision_Dec;
   Bool_t          muplus_Hlt2B2HHDecision_TIS;
   Bool_t          muplus_Hlt2B2HHDecision_TOS;
   Bool_t          muplus_Hlt2DiMuonBDecision_Dec;
   Bool_t          muplus_Hlt2DiMuonBDecision_TIS;
   Bool_t          muplus_Hlt2DiMuonBDecision_TOS;
   Bool_t          muplus_Hlt2DiMuonZDecision_Dec;
   Bool_t          muplus_Hlt2DiMuonZDecision_TIS;
   Bool_t          muplus_Hlt2DiMuonZDecision_TOS;
   Bool_t          muplus_Hlt2TopoMu2BodyBBDTDecision_Dec;
   Bool_t          muplus_Hlt2TopoMu2BodyBBDTDecision_TIS;
   Bool_t          muplus_Hlt2TopoMu2BodyBBDTDecision_TOS;
   Bool_t          muplus_Hlt2TopoMu3BodyBBDTDecision_Dec;
   Bool_t          muplus_Hlt2TopoMu3BodyBBDTDecision_TIS;
   Bool_t          muplus_Hlt2TopoMu3BodyBBDTDecision_TOS;
   Bool_t          muplus_Hlt2TopoMu4BodyBBDTDecision_Dec;
   Bool_t          muplus_Hlt2TopoMu4BodyBBDTDecision_TIS;
   Bool_t          muplus_Hlt2TopoMu4BodyBBDTDecision_TOS;
   Bool_t          muplus_Hlt2Topo2BodyBBDTDecision_Dec;
   Bool_t          muplus_Hlt2Topo2BodyBBDTDecision_TIS;
   Bool_t          muplus_Hlt2Topo2BodyBBDTDecision_TOS;
   Bool_t          muplus_Hlt2Topo3BodyBBDTDecision_Dec;
   Bool_t          muplus_Hlt2Topo3BodyBBDTDecision_TIS;
   Bool_t          muplus_Hlt2Topo3BodyBBDTDecision_TOS;
   Bool_t          muplus_Hlt2Topo4BodyBBDTDecision_Dec;
   Bool_t          muplus_Hlt2Topo4BodyBBDTDecision_TIS;
   Bool_t          muplus_Hlt2Topo4BodyBBDTDecision_TOS;
   Bool_t          muplus_Hlt2Topo2BodySimpleDecision_Dec;
   Bool_t          muplus_Hlt2Topo2BodySimpleDecision_TIS;
   Bool_t          muplus_Hlt2Topo2BodySimpleDecision_TOS;
   Bool_t          muplus_Hlt2Topo3BodySimpleDecision_Dec;
   Bool_t          muplus_Hlt2Topo3BodySimpleDecision_TIS;
   Bool_t          muplus_Hlt2Topo3BodySimpleDecision_TOS;
   Bool_t          muplus_Hlt2Topo4BodySimpleDecision_Dec;
   Bool_t          muplus_Hlt2Topo4BodySimpleDecision_TIS;
   Bool_t          muplus_Hlt2Topo4BodySimpleDecision_TOS;
   Bool_t          muplus_Hlt2PassThroughDecision_Dec;
   Bool_t          muplus_Hlt2PassThroughDecision_TIS;
   Bool_t          muplus_Hlt2PassThroughDecision_TOS;
   Bool_t          muplus_Hlt2TransparentDecision_Dec;
   Bool_t          muplus_Hlt2TransparentDecision_TIS;
   Bool_t          muplus_Hlt2TransparentDecision_TOS;
   Bool_t          muplus_Hlt2IncPhiDecision_Dec;
   Bool_t          muplus_Hlt2IncPhiDecision_TIS;
   Bool_t          muplus_Hlt2IncPhiDecision_TOS;
   Bool_t          muplus_Hlt2DiMuonDY__Decision_Dec;
   Bool_t          muplus_Hlt2DiMuonDY__Decision_TIS;
   Bool_t          muplus_Hlt2DiMuonDY__Decision_TOS;
   Bool_t          muplus_Hlt2TopoE__Decision_Dec;
   Bool_t          muplus_Hlt2TopoE__Decision_TIS;
   Bool_t          muplus_Hlt2TopoE__Decision_TOS;
   Bool_t          muplus_Hlt2Topo__Decision_Dec;
   Bool_t          muplus_Hlt2Topo__Decision_TIS;
   Bool_t          muplus_Hlt2Topo__Decision_TOS;
   Bool_t          muplus_Hlt2Charm__Decision_Dec;
   Bool_t          muplus_Hlt2Charm__Decision_TIS;
   Bool_t          muplus_Hlt2Charm__Decision_TOS;
   Bool_t          muplus_Hlt2DiElectron__Decision_Dec;
   Bool_t          muplus_Hlt2DiElectron__Decision_TIS;
   Bool_t          muplus_Hlt2DiElectron__Decision_TOS;
   Bool_t          muplus_Hlt2__GammaDecision_Dec;
   Bool_t          muplus_Hlt2__GammaDecision_TIS;
   Bool_t          muplus_Hlt2__GammaDecision_TOS;
   Int_t           muplus_TRACK_Type;
   Int_t           muplus_TRACK_Key;
   Double_t        muplus_TRACK_CHI2NDOF;
   Double_t        muplus_TRACK_PCHI2;
   Double_t        muplus_TRACK_MatchCHI2;
   Double_t        muplus_TRACK_GhostProb;
   Double_t        muplus_TRACK_CloneDist;
   Double_t        muplus_TRACK_Likelihood;
   Double_t        muminus_BPVDIRA;
   Double_t        muminus_BPVIPCHI2;
   Double_t        muminus_BPVVDCHI2;
   Double_t        muminus_BPVVDZ;
   Double_t        muminus_DOCAMAX;
   Double_t        muminus_MINIPCHI2;
   Double_t        muminus_VFASPF;
   Double_t        muminus_MC12TuneV2_ProbNNe;
   Double_t        muminus_MC12TuneV2_ProbNNmu;
   Double_t        muminus_MC12TuneV2_ProbNNpi;
   Double_t        muminus_MC12TuneV2_ProbNNk;
   Double_t        muminus_MC12TuneV2_ProbNNp;
   Double_t        muminus_MC12TuneV2_ProbNNghost;
   Double_t        muminus_MC12TuneV3_ProbNNe;
   Double_t        muminus_MC12TuneV3_ProbNNmu;
   Double_t        muminus_MC12TuneV3_ProbNNpi;
   Double_t        muminus_MC12TuneV3_ProbNNk;
   Double_t        muminus_MC12TuneV3_ProbNNp;
   Double_t        muminus_MC12TuneV3_ProbNNghost;
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
   Double_t        muminus_Xs1;
   Double_t        muminus_Ys1;
   Double_t        muminus_Xs2;
   Double_t        muminus_Ys2;
   Double_t        muminus_Xs3;
   Double_t        muminus_Ys3;
   Double_t        muminus_Xs4;
   Double_t        muminus_Ys4;
   Double_t        muminus_Xs5;
   Double_t        muminus_Ys5;
   Float_t         muminus_DistAve;
   Int_t           muminus_ID;
   Double_t        muminus_CombDLLMu;
   Double_t        muminus_ProbNNmu;
   Double_t        muminus_ProbNNghost;
   Double_t        muminus_InMuonAcc;
   Double_t        muminus_MuonDist2;
   Int_t           muminus_regionInM2;
   Bool_t          muminus_hasMuon;
   Bool_t          muminus_isMuon;
   Bool_t          muminus_isMuonLoose;
   Int_t           muminus_NShared;
   Double_t        muminus_MuonLLmu;
   Double_t        muminus_MuonLLbg;
   Int_t           muminus_isMuonFromProto;
   Int_t           muminus_nVeloIDs;
   Int_t           muminus_nITIDs;
   Int_t           muminus_nTTIDs;
   Int_t           muminus_nOTIDs;
   Double_t        muminus_eta;
   Double_t        muminus_phi;
   Double_t        muminus_typeOriginVtx;
   Double_t        muminus_nEndVertices;
   Double_t        muminus_ancestorpid;
   Double_t        muminus_MCI;
   Double_t        muminus_PIDe;
   Double_t        muminus_PIDmu;
   Double_t        muminus_PIDK;
   Double_t        muminus_PIDp;
   Double_t        muminus_ProbNNe;
   Double_t        muminus_ProbNNk;
   Double_t        muminus_ProbNNp;
   Double_t        muminus_ProbNNpi;
   Bool_t          muminus_hasRich;
   Bool_t          muminus_hasCalo;
   Bool_t          muminus_L0Global_Dec;
   Bool_t          muminus_L0Global_TIS;
   Bool_t          muminus_L0Global_TOS;
   Bool_t          muminus_Hlt1Global_Dec;
   Bool_t          muminus_Hlt1Global_TIS;
   Bool_t          muminus_Hlt1Global_TOS;
   Bool_t          muminus_Hlt1Phys_Dec;
   Bool_t          muminus_Hlt1Phys_TIS;
   Bool_t          muminus_Hlt1Phys_TOS;
   Bool_t          muminus_Hlt2Global_Dec;
   Bool_t          muminus_Hlt2Global_TIS;
   Bool_t          muminus_Hlt2Global_TOS;
   Bool_t          muminus_Hlt2Phys_Dec;
   Bool_t          muminus_Hlt2Phys_TIS;
   Bool_t          muminus_Hlt2Phys_TOS;
   Bool_t          muminus_L0MuonDecision_Dec;
   Bool_t          muminus_L0MuonDecision_TIS;
   Bool_t          muminus_L0MuonDecision_TOS;
   Bool_t          muminus_L0DiMuonDecision_Dec;
   Bool_t          muminus_L0DiMuonDecision_TIS;
   Bool_t          muminus_L0DiMuonDecision_TOS;
   Bool_t          muminus_L0HadronDecision_Dec;
   Bool_t          muminus_L0HadronDecision_TIS;
   Bool_t          muminus_L0HadronDecision_TOS;
   Bool_t          muminus_L0ElectronDecision_Dec;
   Bool_t          muminus_L0ElectronDecision_TIS;
   Bool_t          muminus_L0ElectronDecision_TOS;
   Bool_t          muminus_L0ElectronHiDecision_Dec;
   Bool_t          muminus_L0ElectronHiDecision_TIS;
   Bool_t          muminus_L0ElectronHiDecision_TOS;
   Bool_t          muminus_L0PhotonDecision_Dec;
   Bool_t          muminus_L0PhotonDecision_TIS;
   Bool_t          muminus_L0PhotonDecision_TOS;
   Bool_t          muminus_L0PhotonHiDecision_Dec;
   Bool_t          muminus_L0PhotonHiDecision_TIS;
   Bool_t          muminus_L0PhotonHiDecision_TOS;
   Bool_t          muminus_Hlt1SingleMuonNoIPDecision_Dec;
   Bool_t          muminus_Hlt1SingleMuonNoIPDecision_TIS;
   Bool_t          muminus_Hlt1SingleMuonNoIPDecision_TOS;
   Bool_t          muminus_Hlt1SingleMuonHighPTDecision_Dec;
   Bool_t          muminus_Hlt1SingleMuonHighPTDecision_TIS;
   Bool_t          muminus_Hlt1SingleMuonHighPTDecision_TOS;
   Bool_t          muminus_Hlt1SingleElectronNoIPDecision_Dec;
   Bool_t          muminus_Hlt1SingleElectronNoIPDecision_TIS;
   Bool_t          muminus_Hlt1SingleElectronNoIPDecision_TOS;
   Bool_t          muminus_Hlt1TrackAllL0Decision_Dec;
   Bool_t          muminus_Hlt1TrackAllL0Decision_TIS;
   Bool_t          muminus_Hlt1TrackAllL0Decision_TOS;
   Bool_t          muminus_Hlt1TrackMuonDecision_Dec;
   Bool_t          muminus_Hlt1TrackMuonDecision_TIS;
   Bool_t          muminus_Hlt1TrackMuonDecision_TOS;
   Bool_t          muminus_Hlt1TrackPhotonDecision_Dec;
   Bool_t          muminus_Hlt1TrackPhotonDecision_TIS;
   Bool_t          muminus_Hlt1TrackPhotonDecision_TOS;
   Bool_t          muminus_Hlt1TrackAllL0__Decision_Dec;
   Bool_t          muminus_Hlt1TrackAllL0__Decision_TIS;
   Bool_t          muminus_Hlt1TrackAllL0__Decision_TOS;
   Bool_t          muminus_Hlt1DiMuonLowMassDecision_Dec;
   Bool_t          muminus_Hlt1DiMuonLowMassDecision_TIS;
   Bool_t          muminus_Hlt1DiMuonLowMassDecision_TOS;
   Bool_t          muminus_Hlt1DiMuonHighMassDecision_Dec;
   Bool_t          muminus_Hlt1DiMuonHighMassDecision_TIS;
   Bool_t          muminus_Hlt1DiMuonHighMassDecision_TOS;
   Bool_t          muminus_Hlt1MB__Decision_Dec;
   Bool_t          muminus_Hlt1MB__Decision_TIS;
   Bool_t          muminus_Hlt1MB__Decision_TOS;
   Bool_t          muminus_Hlt1TrackAllL0TightDecision_Dec;
   Bool_t          muminus_Hlt1TrackAllL0TightDecision_TIS;
   Bool_t          muminus_Hlt1TrackAllL0TightDecision_TOS;
   Bool_t          muminus_Hlt2SingleMuonDecision_Dec;
   Bool_t          muminus_Hlt2SingleMuonDecision_TIS;
   Bool_t          muminus_Hlt2SingleMuonDecision_TOS;
   Bool_t          muminus_Hlt2SingleMuonLowPTDecision_Dec;
   Bool_t          muminus_Hlt2SingleMuonLowPTDecision_TIS;
   Bool_t          muminus_Hlt2SingleMuonLowPTDecision_TOS;
   Bool_t          muminus_Hlt2SingleMuonHighPTDecision_Dec;
   Bool_t          muminus_Hlt2SingleMuonHighPTDecision_TIS;
   Bool_t          muminus_Hlt2SingleMuonHighPTDecision_TOS;
   Bool_t          muminus_Hlt2DiMuonDecision_Dec;
   Bool_t          muminus_Hlt2DiMuonDecision_TIS;
   Bool_t          muminus_Hlt2DiMuonDecision_TOS;
   Bool_t          muminus_Hlt2DiMuonLowMassDecision_Dec;
   Bool_t          muminus_Hlt2DiMuonLowMassDecision_TIS;
   Bool_t          muminus_Hlt2DiMuonLowMassDecision_TOS;
   Bool_t          muminus_Hlt2DiMuonJPsiDecision_Dec;
   Bool_t          muminus_Hlt2DiMuonJPsiDecision_TIS;
   Bool_t          muminus_Hlt2DiMuonJPsiDecision_TOS;
   Bool_t          muminus_Hlt2DiMuonJPsiHighPTDecision_Dec;
   Bool_t          muminus_Hlt2DiMuonJPsiHighPTDecision_TIS;
   Bool_t          muminus_Hlt2DiMuonJPsiHighPTDecision_TOS;
   Bool_t          muminus_Hlt2DiMuonPsi2SDecision_Dec;
   Bool_t          muminus_Hlt2DiMuonPsi2SDecision_TIS;
   Bool_t          muminus_Hlt2DiMuonPsi2SDecision_TOS;
   Bool_t          muminus_Hlt2DiMuonDetachedDecision_Dec;
   Bool_t          muminus_Hlt2DiMuonDetachedDecision_TIS;
   Bool_t          muminus_Hlt2DiMuonDetachedDecision_TOS;
   Bool_t          muminus_Hlt2DiMuonDetachedJPsiDecision_Dec;
   Bool_t          muminus_Hlt2DiMuonDetachedJPsiDecision_TIS;
   Bool_t          muminus_Hlt2DiMuonDetachedJPsiDecision_TOS;
   Bool_t          muminus_Hlt2DiMuonDetachedHeavyDecision_Dec;
   Bool_t          muminus_Hlt2DiMuonDetachedHeavyDecision_TIS;
   Bool_t          muminus_Hlt2DiMuonDetachedHeavyDecision_TOS;
   Bool_t          muminus_Hlt2TriMuonTauDecision_Dec;
   Bool_t          muminus_Hlt2TriMuonTauDecision_TIS;
   Bool_t          muminus_Hlt2TriMuonTauDecision_TOS;
   Bool_t          muminus_Hlt2B2HHDecision_Dec;
   Bool_t          muminus_Hlt2B2HHDecision_TIS;
   Bool_t          muminus_Hlt2B2HHDecision_TOS;
   Bool_t          muminus_Hlt2DiMuonBDecision_Dec;
   Bool_t          muminus_Hlt2DiMuonBDecision_TIS;
   Bool_t          muminus_Hlt2DiMuonBDecision_TOS;
   Bool_t          muminus_Hlt2DiMuonZDecision_Dec;
   Bool_t          muminus_Hlt2DiMuonZDecision_TIS;
   Bool_t          muminus_Hlt2DiMuonZDecision_TOS;
   Bool_t          muminus_Hlt2TopoMu2BodyBBDTDecision_Dec;
   Bool_t          muminus_Hlt2TopoMu2BodyBBDTDecision_TIS;
   Bool_t          muminus_Hlt2TopoMu2BodyBBDTDecision_TOS;
   Bool_t          muminus_Hlt2TopoMu3BodyBBDTDecision_Dec;
   Bool_t          muminus_Hlt2TopoMu3BodyBBDTDecision_TIS;
   Bool_t          muminus_Hlt2TopoMu3BodyBBDTDecision_TOS;
   Bool_t          muminus_Hlt2TopoMu4BodyBBDTDecision_Dec;
   Bool_t          muminus_Hlt2TopoMu4BodyBBDTDecision_TIS;
   Bool_t          muminus_Hlt2TopoMu4BodyBBDTDecision_TOS;
   Bool_t          muminus_Hlt2Topo2BodyBBDTDecision_Dec;
   Bool_t          muminus_Hlt2Topo2BodyBBDTDecision_TIS;
   Bool_t          muminus_Hlt2Topo2BodyBBDTDecision_TOS;
   Bool_t          muminus_Hlt2Topo3BodyBBDTDecision_Dec;
   Bool_t          muminus_Hlt2Topo3BodyBBDTDecision_TIS;
   Bool_t          muminus_Hlt2Topo3BodyBBDTDecision_TOS;
   Bool_t          muminus_Hlt2Topo4BodyBBDTDecision_Dec;
   Bool_t          muminus_Hlt2Topo4BodyBBDTDecision_TIS;
   Bool_t          muminus_Hlt2Topo4BodyBBDTDecision_TOS;
   Bool_t          muminus_Hlt2Topo2BodySimpleDecision_Dec;
   Bool_t          muminus_Hlt2Topo2BodySimpleDecision_TIS;
   Bool_t          muminus_Hlt2Topo2BodySimpleDecision_TOS;
   Bool_t          muminus_Hlt2Topo3BodySimpleDecision_Dec;
   Bool_t          muminus_Hlt2Topo3BodySimpleDecision_TIS;
   Bool_t          muminus_Hlt2Topo3BodySimpleDecision_TOS;
   Bool_t          muminus_Hlt2Topo4BodySimpleDecision_Dec;
   Bool_t          muminus_Hlt2Topo4BodySimpleDecision_TIS;
   Bool_t          muminus_Hlt2Topo4BodySimpleDecision_TOS;
   Bool_t          muminus_Hlt2PassThroughDecision_Dec;
   Bool_t          muminus_Hlt2PassThroughDecision_TIS;
   Bool_t          muminus_Hlt2PassThroughDecision_TOS;
   Bool_t          muminus_Hlt2TransparentDecision_Dec;
   Bool_t          muminus_Hlt2TransparentDecision_TIS;
   Bool_t          muminus_Hlt2TransparentDecision_TOS;
   Bool_t          muminus_Hlt2IncPhiDecision_Dec;
   Bool_t          muminus_Hlt2IncPhiDecision_TIS;
   Bool_t          muminus_Hlt2IncPhiDecision_TOS;
   Bool_t          muminus_Hlt2DiMuonDY__Decision_Dec;
   Bool_t          muminus_Hlt2DiMuonDY__Decision_TIS;
   Bool_t          muminus_Hlt2DiMuonDY__Decision_TOS;
   Bool_t          muminus_Hlt2TopoE__Decision_Dec;
   Bool_t          muminus_Hlt2TopoE__Decision_TIS;
   Bool_t          muminus_Hlt2TopoE__Decision_TOS;
   Bool_t          muminus_Hlt2Topo__Decision_Dec;
   Bool_t          muminus_Hlt2Topo__Decision_TIS;
   Bool_t          muminus_Hlt2Topo__Decision_TOS;
   Bool_t          muminus_Hlt2Charm__Decision_Dec;
   Bool_t          muminus_Hlt2Charm__Decision_TIS;
   Bool_t          muminus_Hlt2Charm__Decision_TOS;
   Bool_t          muminus_Hlt2DiElectron__Decision_Dec;
   Bool_t          muminus_Hlt2DiElectron__Decision_TIS;
   Bool_t          muminus_Hlt2DiElectron__Decision_TOS;
   Bool_t          muminus_Hlt2__GammaDecision_Dec;
   Bool_t          muminus_Hlt2__GammaDecision_TIS;
   Bool_t          muminus_Hlt2__GammaDecision_TOS;
   Int_t           muminus_TRACK_Type;
   Int_t           muminus_TRACK_Key;
   Double_t        muminus_TRACK_CHI2NDOF;
   Double_t        muminus_TRACK_PCHI2;
   Double_t        muminus_TRACK_MatchCHI2;
   Double_t        muminus_TRACK_GhostProb;
   Double_t        muminus_TRACK_CloneDist;
   Double_t        muminus_TRACK_Likelihood;
   UInt_t          nCandidate;
   ULong64_t       totCandidates;
   ULong64_t       EventInSequence;
   Int_t           MCPVs;
   Float_t         MCPVX[50];   //[MCPVs]
   Float_t         MCPVY[50];   //[MCPVs]
   Float_t         MCPVZ[50];   //[MCPVs]
   Float_t         MCPVT[50];   //[MCPVs]
   UInt_t          runNumber;
   ULong64_t       eventNumber;
   UInt_t          BCID;
   Int_t           BCType;
   UInt_t          OdinTCK;
   UInt_t          L0DUTCK;
   UInt_t          HLTTCK;
   ULong64_t       GpsTime;
   Short_t         Polarity;
   Int_t           Collisions;
   Float_t         ProcessType[20];   //[Collisions]
   Float_t         HeaviestQuark[20];   //[Collisions]
   UInt_t          HeaviestQuarkInEvent;
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
   TBranch        *b_B_BPVDIRA;   //!
   TBranch        *b_B_BPVIPCHI2;   //!
   TBranch        *b_B_BPVVDCHI2;   //!
   TBranch        *b_B_BPVVDZ;   //!
   TBranch        *b_B_DOCAMAX;   //!
   TBranch        *b_B_MINIPCHI2;   //!
   TBranch        *b_B_VFASPF;   //!
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
   TBranch        *b_B_ID;   //!
   TBranch        *b_B_eta;   //!
   TBranch        *b_B_phi;   //!
   TBranch        *b_B_D1_isolation_Giampi;   //!
   TBranch        *b_B_D2_isolation_Giampi;   //!
   TBranch        *b_B_D1_isolation_Giampi_tc;   //!
   TBranch        *b_B_D2_isolation_Giampi_tc;   //!
   TBranch        *b_B_D1_isolation_Giampi_new1;   //!
   TBranch        *b_B_D2_isolation_Giampi_new1;   //!
   TBranch        *b_B_D1_isolation_Giampi_new2;   //!
   TBranch        *b_B_D2_isolation_Giampi_new2;   //!
   TBranch        *b_B_D1_isolation_Giampi_newD0;   //!
   TBranch        *b_B_D2_isolation_Giampi_newD0;   //!
   TBranch        *b_B_yetanother_CDF_iso;   //!
   TBranch        *b_B_yetanother_CDF_iso_tc;   //!
   TBranch        *b_B_doca;   //!
   TBranch        *b_B_cosnk;   //!
   TBranch        *b_B_BDTS_BIPS;   //!
   TBranch        *b_B_BDTS_DOCA;   //!
   TBranch        *b_B_BDTS_VTXCHI2;   //!
   TBranch        *b_B_BDTS_DIRA;   //!
   TBranch        *b_B_BDTS_BIP;   //!
   TBranch        *b_B_BDTS_MuonMINIP;   //!
   TBranch        *b_B_BDTS;   //!
   TBranch        *b_B_CTAU_ps;   //!
   TBranch        *b_IsoSTIdx;   //!
   TBranch        *b_IsoST_trk_typ;   //!
   TBranch        *b_IsoST_trk_chi;   //!
   TBranch        *b_IsoST_trk_chg;   //!
   TBranch        *b_IsoST_trk_pt;   //!
   TBranch        *b_IsoST_trk_gho;   //!
   TBranch        *b_IsoST_trk_clo;   //!
   TBranch        *b_IsoST_trk_ips;   //!
   TBranch        *b_IsoST_trk_hlt;   //!
   TBranch        *b_IsoST_fim_angle;   //!
   TBranch        *b_IsoST_fim_fc;   //!
   TBranch        *b_IsoST_fim_doca;   //!
   TBranch        *b_IsoST_fim_doca2;   //!
   TBranch        *b_IsoST_fim_docachi2;   //!
   TBranch        *b_IsoST_fim_svdis;   //!
   TBranch        *b_IsoST_fim_pvdis;   //!
   TBranch        *b_IsoST_fim_vtxx;   //!
   TBranch        *b_IsoST_fim_vtxy;   //!
   TBranch        *b_IsoST_fim_vtxz;   //!
   TBranch        *b_IsoST_sem_angle;   //!
   TBranch        *b_IsoST_sem_fc;   //!
   TBranch        *b_IsoST_sem_doca;   //!
   TBranch        *b_IsoST_sem_doca2;   //!
   TBranch        *b_IsoST_sem_docachi2;   //!
   TBranch        *b_IsoST_sem_svdis;   //!
   TBranch        *b_IsoST_sem_pvdis;   //!
   TBranch        *b_IsoST_sem_vtxx;   //!
   TBranch        *b_IsoST_sem_vtxy;   //!
   TBranch        *b_IsoST_sem_vtxz;   //!
   TBranch        *b_B_D1_isobdt1_1st;   //!
   TBranch        *b_B_D1_isobdt1_2nd;   //!
   TBranch        *b_B_D1_isobdt1_3rd;   //!
   TBranch        *b_B_D2_isobdt1_1st;   //!
   TBranch        *b_B_D2_isobdt1_2nd;   //!
   TBranch        *b_B_D2_isobdt1_3rd;   //!
   TBranch        *b_B_D1_isobdt2_1st;   //!
   TBranch        *b_B_D1_isobdt2_2nd;   //!
   TBranch        *b_B_D1_isobdt2_3rd;   //!
   TBranch        *b_B_D2_isobdt2_1st;   //!
   TBranch        *b_B_D2_isobdt2_2nd;   //!
   TBranch        *b_B_D2_isobdt2_3rd;   //!
   TBranch        *b_B_D1_isobdt3_1st;   //!
   TBranch        *b_B_D1_isobdt3_2nd;   //!
   TBranch        *b_B_D1_isobdt3_3rd;   //!
   TBranch        *b_B_D2_isobdt3_1st;   //!
   TBranch        *b_B_D2_isobdt3_2nd;   //!
   TBranch        *b_B_D2_isobdt3_3rd;   //!
   TBranch        *b_B_D1_isobdt4_1st;   //!
   TBranch        *b_B_D1_isobdt4_2nd;   //!
   TBranch        *b_B_D1_isobdt4_3rd;   //!
   TBranch        *b_B_D2_isobdt4_1st;   //!
   TBranch        *b_B_D2_isobdt4_2nd;   //!
   TBranch        *b_B_D2_isobdt4_3rd;   //!
   TBranch        *b_B_CDFiso;   //!
   TBranch        *b_B_CDFiso_tc;   //!
   TBranch        *b_B_otherB_mag;   //!
   TBranch        *b_B_otherB_ang;   //!
   TBranch        *b_B_otherB_ntrk;   //!
   TBranch        *b_B_otherB_boo_mag;   //!
   TBranch        *b_B_otherB_boo_ang;   //!
   TBranch        *b_EVB_Nparts;   //!
   TBranch        *b_pbIdx;   //!
   TBranch        *b_EVB_par_pos_x;   //!
   TBranch        *b_EVB_par_pos_y;   //!
   TBranch        *b_EVB_par_pos_z;   //!
   TBranch        *b_EVB_par_pos_covxx;   //!
   TBranch        *b_EVB_par_pos_covyy;   //!
   TBranch        *b_EVB_par_pos_covxy;   //!
   TBranch        *b_EVB_par_fmpos_x;   //!
   TBranch        *b_EVB_par_fmpos_y;   //!
   TBranch        *b_EVB_par_fmpos_z;   //!
   TBranch        *b_EVB_par_xp_cov00;   //!
   TBranch        *b_EVB_par_xp_cov11;   //!
   TBranch        *b_EVB_par_xp_cov22;   //!
   TBranch        *b_EVB_par_xp_cov33;   //!
   TBranch        *b_EVB_par_xp_cov44;   //!
   TBranch        *b_EVB_par_xp_cov55;   //!
   TBranch        *b_EVB_par_xp_cov01;   //!
   TBranch        *b_EVB_par_xp_cov02;   //!
   TBranch        *b_EVB_par_xp_cov12;   //!
   TBranch        *b_EVB_par_xp_cov34;   //!
   TBranch        *b_EVB_par_xp_cov35;   //!
   TBranch        *b_EVB_par_xp_cov45;   //!
   TBranch        *b_EVB_par_xp_cov03;   //!
   TBranch        *b_EVB_par_xp_cov04;   //!
   TBranch        *b_EVB_par_xp_cov05;   //!
   TBranch        *b_EVB_par_xp_cov13;   //!
   TBranch        *b_EVB_par_xp_cov14;   //!
   TBranch        *b_EVB_par_xp_cov15;   //!
   TBranch        *b_EVB_par_xp_cov23;   //!
   TBranch        *b_EVB_par_xp_cov24;   //!
   TBranch        *b_EVB_par_xp_cov25;   //!
   TBranch        *b_EVB_par_px;   //!
   TBranch        *b_EVB_par_py;   //!
   TBranch        *b_EVB_par_pz;   //!
   TBranch        *b_EVB_par_pt;   //!
   TBranch        *b_EVB_par_p;   //!
   TBranch        *b_EVB_par_chg;   //!
   TBranch        *b_EVB_par_typ;   //!
   TBranch        *b_EVB_par_gho;   //!
   TBranch        *b_EVB_par_chi;   //!
   TBranch        *b_EVB_par_clo;   //!
   TBranch        *b_EVB_par_ip;   //!
   TBranch        *b_EVB_par_ips;   //!
   TBranch        *b_EVB_par_hlt;   //!
   TBranch        *b_EVB_par_slope_covxx;   //!
   TBranch        *b_EVB_par_slope_covyy;   //!
   TBranch        *b_EVB_par_slope_covxy;   //!
   TBranch        *b_EVB_par_NNe;   //!
   TBranch        *b_EVB_par_NNmu;   //!
   TBranch        *b_EVB_par_NNpi;   //!
   TBranch        *b_EVB_par_NNk;   //!
   TBranch        *b_EVB_par_NNp;   //!
   TBranch        *b_EVB_par_NNghost;   //!
   TBranch        *b_EVB_par_DLLe;   //!
   TBranch        *b_EVB_par_DLLmu;   //!
   TBranch        *b_EVB_par_DLLk;   //!
   TBranch        *b_EVB_par_DLLp;   //!
   TBranch        *b_EVB_par_isMuon;   //!
   TBranch        *b_EVB_par_PVind;   //!
   TBranch        *b_EVB_isMCMatched;   //!
   TBranch        *b_EVB_true_Origin_ID;   //!
   TBranch        *b_EVB_true_part_Ori_Vtx_x;   //!
   TBranch        *b_EVB_true_part_Ori_Vtx_y;   //!
   TBranch        *b_EVB_true_part_Ori_Vtx_z;   //!
   TBranch        *b_EVB_true_part_Ori_type;   //!
   TBranch        *b_EVB_true_part_ID;   //!
   TBranch        *b_EVB_true_isnoniso_mup;   //!
   TBranch        *b_EVB_true_isnoniso_mum;   //!
   TBranch        *b_EVB_true_part_Px;   //!
   TBranch        *b_EVB_true_part_Py;   //!
   TBranch        *b_EVB_true_part_Pz;   //!
   TBranch        *b_EVB_true_part_E;   //!
   TBranch        *b_EVB_true_part_M;   //!
   TBranch        *b_EVB_true_part_hasMother;   //!
   TBranch        *b_EVB_true_moth_Ori_Vtx_x;   //!
   TBranch        *b_EVB_true_moth_Ori_Vtx_y;   //!
   TBranch        *b_EVB_true_moth_Ori_Vtx_z;   //!
   TBranch        *b_EVB_true_moth_ID;   //!
   TBranch        *b_EVB_true_moth_Px;   //!
   TBranch        *b_EVB_true_moth_Py;   //!
   TBranch        *b_EVB_true_moth_Pz;   //!
   TBranch        *b_EVB_true_moth_E;   //!
   TBranch        *b_EVB_true_moth_M;   //!
   TBranch        *b_EVB_true_moth_hasMother;   //!
   TBranch        *b_EVB_true_gran_Ori_Vtx_x;   //!
   TBranch        *b_EVB_true_gran_Ori_Vtx_y;   //!
   TBranch        *b_EVB_true_gran_Ori_Vtx_z;   //!
   TBranch        *b_EVB_true_gran_ID;   //!
   TBranch        *b_EVB_true_gran_Px;   //!
   TBranch        *b_EVB_true_gran_Py;   //!
   TBranch        *b_EVB_true_gran_Pz;   //!
   TBranch        *b_EVB_true_gran_E;   //!
   TBranch        *b_EVB_true_gran_M;   //!
   TBranch        *b_EVB_true_gran_hasMother;   //!
   TBranch        *b_EVB_true_mogr_Ori_Vtx_x;   //!
   TBranch        *b_EVB_true_mogr_Ori_Vtx_y;   //!
   TBranch        *b_EVB_true_mogr_Ori_Vtx_z;   //!
   TBranch        *b_EVB_true_mogr_ID;   //!
   TBranch        *b_EVB_true_mogr_Px;   //!
   TBranch        *b_EVB_true_mogr_Py;   //!
   TBranch        *b_EVB_true_mogr_Pz;   //!
   TBranch        *b_EVB_true_mogr_E;   //!
   TBranch        *b_EVB_true_mogr_M;   //!
   TBranch        *b_EVB_true_mogr_hasMother;   //!
   TBranch        *b_EVB_true_grgr_Ori_Vtx_x;   //!
   TBranch        *b_EVB_true_grgr_Ori_Vtx_y;   //!
   TBranch        *b_EVB_true_grgr_Ori_Vtx_z;   //!
   TBranch        *b_EVB_true_grgr_ID;   //!
   TBranch        *b_EVB_true_grgr_Px;   //!
   TBranch        *b_EVB_true_grgr_Py;   //!
   TBranch        *b_EVB_true_grgr_Pz;   //!
   TBranch        *b_EVB_true_grgr_E;   //!
   TBranch        *b_EVB_true_grgr_M;   //!
   TBranch        *b_PV_num;   //!
   TBranch        *b_PV_x;   //!
   TBranch        *b_PV_y;   //!
   TBranch        *b_PV_z;   //!
   TBranch        *b_PV_covxx;   //!
   TBranch        *b_PV_covyy;   //!
   TBranch        *b_PV_covzz;   //!
   TBranch        *b_PV_covxy;   //!
   TBranch        *b_PV_covxz;   //!
   TBranch        *b_PV_covyz;   //!
   TBranch        *b_PV_chi2PerDoF;   //!
   TBranch        *b_PV_nDoF;   //!
   TBranch        *b_PV_ntrk;   //!
   TBranch        *b_PV2_num;   //!
   TBranch        *b_PV2_x;   //!
   TBranch        *b_PV2_y;   //!
   TBranch        *b_PV2_z;   //!
   TBranch        *b_PV2_covxx;   //!
   TBranch        *b_PV2_covyy;   //!
   TBranch        *b_PV2_covzz;   //!
   TBranch        *b_PV2_covxy;   //!
   TBranch        *b_PV2_covxz;   //!
   TBranch        *b_PV2_covyz;   //!
   TBranch        *b_PV2_chi2PerDoF;   //!
   TBranch        *b_PV2_nDoF;   //!
   TBranch        *b_PV2_ntrk;   //!
   TBranch        *b_B_cov00;   //!
   TBranch        *b_B_cov01;   //!
   TBranch        *b_B_cov02;   //!
   TBranch        *b_B_cov03;   //!
   TBranch        *b_B_cov04;   //!
   TBranch        *b_B_cov05;   //!
   TBranch        *b_B_cov06;   //!
   TBranch        *b_B_cov11;   //!
   TBranch        *b_B_cov12;   //!
   TBranch        *b_B_cov13;   //!
   TBranch        *b_B_cov14;   //!
   TBranch        *b_B_cov15;   //!
   TBranch        *b_B_cov16;   //!
   TBranch        *b_B_cov22;   //!
   TBranch        *b_B_cov23;   //!
   TBranch        *b_B_cov24;   //!
   TBranch        *b_B_cov25;   //!
   TBranch        *b_B_cov26;   //!
   TBranch        *b_B_cov33;   //!
   TBranch        *b_B_cov34;   //!
   TBranch        *b_B_cov35;   //!
   TBranch        *b_B_cov36;   //!
   TBranch        *b_B_cov44;   //!
   TBranch        *b_B_cov45;   //!
   TBranch        *b_B_cov46;   //!
   TBranch        *b_B_cov55;   //!
   TBranch        *b_B_cov56;   //!
   TBranch        *b_B_cov66;   //!
   TBranch        *b_VEL_num;   //!
   TBranch        *b_VEL_par_pos_x;   //!
   TBranch        *b_VEL_par_pos_y;   //!
   TBranch        *b_VEL_par_pos_z;   //!
   TBranch        *b_VEL_par_fmpos_x;   //!
   TBranch        *b_VEL_par_fmpos_y;   //!
   TBranch        *b_VEL_par_fmpos_z;   //!
   TBranch        *b_VEL_par_xp_cov00;   //!
   TBranch        *b_VEL_par_xp_cov11;   //!
   TBranch        *b_VEL_par_xp_cov22;   //!
   TBranch        *b_VEL_par_xp_cov33;   //!
   TBranch        *b_VEL_par_xp_cov44;   //!
   TBranch        *b_VEL_par_xp_cov55;   //!
   TBranch        *b_VEL_par_xp_cov01;   //!
   TBranch        *b_VEL_par_xp_cov02;   //!
   TBranch        *b_VEL_par_xp_cov12;   //!
   TBranch        *b_VEL_par_xp_cov34;   //!
   TBranch        *b_VEL_par_xp_cov35;   //!
   TBranch        *b_VEL_par_xp_cov45;   //!
   TBranch        *b_VEL_par_xp_cov03;   //!
   TBranch        *b_VEL_par_xp_cov04;   //!
   TBranch        *b_VEL_par_xp_cov05;   //!
   TBranch        *b_VEL_par_xp_cov13;   //!
   TBranch        *b_VEL_par_xp_cov14;   //!
   TBranch        *b_VEL_par_xp_cov15;   //!
   TBranch        *b_VEL_par_xp_cov23;   //!
   TBranch        *b_VEL_par_xp_cov24;   //!
   TBranch        *b_VEL_par_xp_cov25;   //!
   TBranch        *b_VEL_par_px;   //!
   TBranch        *b_VEL_par_py;   //!
   TBranch        *b_VEL_par_pz;   //!
   TBranch        *b_VEL_par_pt;   //!
   TBranch        *b_VEL_par_p;   //!
   TBranch        *b_VEL_par_chg;   //!
   TBranch        *b_VEL_par_slope_covxx;   //!
   TBranch        *b_VEL_par_slope_covyy;   //!
   TBranch        *b_VEL_par_slope_covxy;   //!
   TBranch        *b_VEL_par_back;   //!
   TBranch        *b_VEL_par_typ;   //!
   TBranch        *b_VEL_par_gho;   //!
   TBranch        *b_VEL_par_chi;   //!
   TBranch        *b_VEL_par_clo;   //!
   TBranch        *b_VEL_par_PVind;   //!
   TBranch        *b_VEL_isMCMatched;   //!
   TBranch        *b_VEL_true_Origin_ID;   //!
   TBranch        *b_VEL_true_part_Ori_Vtx_x;   //!
   TBranch        *b_VEL_true_part_Ori_Vtx_y;   //!
   TBranch        *b_VEL_true_part_Ori_Vtx_z;   //!
   TBranch        *b_VEL_true_part_Ori_type;   //!
   TBranch        *b_VEL_true_part_ID;   //!
   TBranch        *b_VEL_true_isnoniso_mup;   //!
   TBranch        *b_VEL_true_isnoniso_mum;   //!
   TBranch        *b_VEL_true_part_Px;   //!
   TBranch        *b_VEL_true_part_Py;   //!
   TBranch        *b_VEL_true_part_Pz;   //!
   TBranch        *b_VEL_true_part_E;   //!
   TBranch        *b_VEL_true_part_M;   //!
   TBranch        *b_VEL_true_part_hasMother;   //!
   TBranch        *b_VEL_true_moth_Ori_Vtx_x;   //!
   TBranch        *b_VEL_true_moth_Ori_Vtx_y;   //!
   TBranch        *b_VEL_true_moth_Ori_Vtx_z;   //!
   TBranch        *b_VEL_true_moth_ID;   //!
   TBranch        *b_VEL_true_moth_Px;   //!
   TBranch        *b_VEL_true_moth_Py;   //!
   TBranch        *b_VEL_true_moth_Pz;   //!
   TBranch        *b_VEL_true_moth_E;   //!
   TBranch        *b_VEL_true_moth_M;   //!
   TBranch        *b_VEL_true_moth_hasMother;   //!
   TBranch        *b_VEL_true_gran_Ori_Vtx_x;   //!
   TBranch        *b_VEL_true_gran_Ori_Vtx_y;   //!
   TBranch        *b_VEL_true_gran_Ori_Vtx_z;   //!
   TBranch        *b_VEL_true_gran_ID;   //!
   TBranch        *b_VEL_true_gran_Px;   //!
   TBranch        *b_VEL_true_gran_Py;   //!
   TBranch        *b_VEL_true_gran_Pz;   //!
   TBranch        *b_VEL_true_gran_E;   //!
   TBranch        *b_VEL_true_gran_M;   //!
   TBranch        *b_VEL_true_gran_hasMother;   //!
   TBranch        *b_VEL_true_mogr_Ori_Vtx_x;   //!
   TBranch        *b_VEL_true_mogr_Ori_Vtx_y;   //!
   TBranch        *b_VEL_true_mogr_Ori_Vtx_z;   //!
   TBranch        *b_VEL_true_mogr_ID;   //!
   TBranch        *b_VEL_true_mogr_Px;   //!
   TBranch        *b_VEL_true_mogr_Py;   //!
   TBranch        *b_VEL_true_mogr_Pz;   //!
   TBranch        *b_VEL_true_mogr_E;   //!
   TBranch        *b_VEL_true_mogr_M;   //!
   TBranch        *b_VEL_true_mogr_hasMother;   //!
   TBranch        *b_VEL_true_grgr_Ori_Vtx_x;   //!
   TBranch        *b_VEL_true_grgr_Ori_Vtx_y;   //!
   TBranch        *b_VEL_true_grgr_Ori_Vtx_z;   //!
   TBranch        *b_VEL_true_grgr_ID;   //!
   TBranch        *b_VEL_true_grgr_Px;   //!
   TBranch        *b_VEL_true_grgr_Py;   //!
   TBranch        *b_VEL_true_grgr_Pz;   //!
   TBranch        *b_VEL_true_grgr_E;   //!
   TBranch        *b_VEL_true_grgr_M;   //!
   TBranch        *b_US_num;   //!
   TBranch        *b_US_par_pos_x;   //!
   TBranch        *b_US_par_pos_y;   //!
   TBranch        *b_US_par_pos_z;   //!
   TBranch        *b_US_par_fmpos_x;   //!
   TBranch        *b_US_par_fmpos_y;   //!
   TBranch        *b_US_par_fmpos_z;   //!
   TBranch        *b_US_par_xp_cov00;   //!
   TBranch        *b_US_par_xp_cov11;   //!
   TBranch        *b_US_par_xp_cov22;   //!
   TBranch        *b_US_par_xp_cov33;   //!
   TBranch        *b_US_par_xp_cov44;   //!
   TBranch        *b_US_par_xp_cov55;   //!
   TBranch        *b_US_par_xp_cov01;   //!
   TBranch        *b_US_par_xp_cov02;   //!
   TBranch        *b_US_par_xp_cov12;   //!
   TBranch        *b_US_par_xp_cov34;   //!
   TBranch        *b_US_par_xp_cov35;   //!
   TBranch        *b_US_par_xp_cov45;   //!
   TBranch        *b_US_par_xp_cov03;   //!
   TBranch        *b_US_par_xp_cov04;   //!
   TBranch        *b_US_par_xp_cov05;   //!
   TBranch        *b_US_par_xp_cov13;   //!
   TBranch        *b_US_par_xp_cov14;   //!
   TBranch        *b_US_par_xp_cov15;   //!
   TBranch        *b_US_par_xp_cov23;   //!
   TBranch        *b_US_par_xp_cov24;   //!
   TBranch        *b_US_par_xp_cov25;   //!
   TBranch        *b_US_par_px;   //!
   TBranch        *b_US_par_py;   //!
   TBranch        *b_US_par_pz;   //!
   TBranch        *b_US_par_pt;   //!
   TBranch        *b_US_par_p;   //!
   TBranch        *b_US_par_chg;   //!
   TBranch        *b_US_par_slope_covxx;   //!
   TBranch        *b_US_par_slope_covyy;   //!
   TBranch        *b_US_par_slope_covxy;   //!
   TBranch        *b_US_par_typ;   //!
   TBranch        *b_US_par_gho;   //!
   TBranch        *b_US_par_chi;   //!
   TBranch        *b_US_par_clo;   //!
   TBranch        *b_US_par_NNe;   //!
   TBranch        *b_US_par_NNmu;   //!
   TBranch        *b_US_par_NNpi;   //!
   TBranch        *b_US_par_NNk;   //!
   TBranch        *b_US_par_NNp;   //!
   TBranch        *b_US_par_NNghost;   //!
   TBranch        *b_US_par_DLLe;   //!
   TBranch        *b_US_par_DLLmu;   //!
   TBranch        *b_US_par_DLLk;   //!
   TBranch        *b_US_par_DLLp;   //!
   TBranch        *b_US_par_isMuon;   //!
   TBranch        *b_US_par_PVind;   //!
   TBranch        *b_US_isMCMatched;   //!
   TBranch        *b_US_true_Origin_ID;   //!
   TBranch        *b_US_true_part_Ori_Vtx_x;   //!
   TBranch        *b_US_true_part_Ori_Vtx_y;   //!
   TBranch        *b_US_true_part_Ori_Vtx_z;   //!
   TBranch        *b_US_true_part_Ori_type;   //!
   TBranch        *b_US_true_part_ID;   //!
   TBranch        *b_US_true_isnoniso_mup;   //!
   TBranch        *b_US_true_isnoniso_mum;   //!
   TBranch        *b_US_true_part_Px;   //!
   TBranch        *b_US_true_part_Py;   //!
   TBranch        *b_US_true_part_Pz;   //!
   TBranch        *b_US_true_part_E;   //!
   TBranch        *b_US_true_part_M;   //!
   TBranch        *b_US_true_part_hasMother;   //!
   TBranch        *b_US_true_moth_Ori_Vtx_x;   //!
   TBranch        *b_US_true_moth_Ori_Vtx_y;   //!
   TBranch        *b_US_true_moth_Ori_Vtx_z;   //!
   TBranch        *b_US_true_moth_ID;   //!
   TBranch        *b_US_true_moth_Px;   //!
   TBranch        *b_US_true_moth_Py;   //!
   TBranch        *b_US_true_moth_Pz;   //!
   TBranch        *b_US_true_moth_E;   //!
   TBranch        *b_US_true_moth_M;   //!
   TBranch        *b_US_true_moth_hasMother;   //!
   TBranch        *b_US_true_gran_Ori_Vtx_x;   //!
   TBranch        *b_US_true_gran_Ori_Vtx_y;   //!
   TBranch        *b_US_true_gran_Ori_Vtx_z;   //!
   TBranch        *b_US_true_gran_ID;   //!
   TBranch        *b_US_true_gran_Px;   //!
   TBranch        *b_US_true_gran_Py;   //!
   TBranch        *b_US_true_gran_Pz;   //!
   TBranch        *b_US_true_gran_E;   //!
   TBranch        *b_US_true_gran_M;   //!
   TBranch        *b_US_true_gran_hasMother;   //!
   TBranch        *b_US_true_mogr_Ori_Vtx_x;   //!
   TBranch        *b_US_true_mogr_Ori_Vtx_y;   //!
   TBranch        *b_US_true_mogr_Ori_Vtx_z;   //!
   TBranch        *b_US_true_mogr_ID;   //!
   TBranch        *b_US_true_mogr_Px;   //!
   TBranch        *b_US_true_mogr_Py;   //!
   TBranch        *b_US_true_mogr_Pz;   //!
   TBranch        *b_US_true_mogr_E;   //!
   TBranch        *b_US_true_mogr_M;   //!
   TBranch        *b_US_true_mogr_hasMother;   //!
   TBranch        *b_US_true_grgr_Ori_Vtx_x;   //!
   TBranch        *b_US_true_grgr_Ori_Vtx_y;   //!
   TBranch        *b_US_true_grgr_Ori_Vtx_z;   //!
   TBranch        *b_US_true_grgr_ID;   //!
   TBranch        *b_US_true_grgr_Px;   //!
   TBranch        *b_US_true_grgr_Py;   //!
   TBranch        *b_US_true_grgr_Pz;   //!
   TBranch        *b_US_true_grgr_E;   //!
   TBranch        *b_US_true_grgr_M;   //!
   TBranch        *b_MCGEN_num;   //!
   TBranch        *b_MCGEN_partindex;   //!
   TBranch        *b_MCGEN_motindex;   //!
   TBranch        *b_MCGEN_lundid;   //!
   TBranch        *b_MCGEN_px;   //!
   TBranch        *b_MCGEN_py;   //!
   TBranch        *b_MCGEN_pz;   //!
   TBranch        *b_MCGEN_vtx_x;   //!
   TBranch        *b_MCGEN_vtx_y;   //!
   TBranch        *b_MCGEN_vtx_z;   //!
   TBranch        *b_MCGEN_origtype;   //!
   TBranch        *b_B_typeOriginVtx;   //!
   TBranch        *b_B_nEndVertices;   //!
   TBranch        *b_B_ancestorpid;   //!
   TBranch        *b_B_MCI;   //!
   TBranch        *b_B_TAU;   //!
   TBranch        *b_B_TAUERR;   //!
   TBranch        *b_B_TAUCHI2;   //!
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
   TBranch        *b_B_L0MuonDecision_Dec;   //!
   TBranch        *b_B_L0MuonDecision_TIS;   //!
   TBranch        *b_B_L0MuonDecision_TOS;   //!
   TBranch        *b_B_L0DiMuonDecision_Dec;   //!
   TBranch        *b_B_L0DiMuonDecision_TIS;   //!
   TBranch        *b_B_L0DiMuonDecision_TOS;   //!
   TBranch        *b_B_L0HadronDecision_Dec;   //!
   TBranch        *b_B_L0HadronDecision_TIS;   //!
   TBranch        *b_B_L0HadronDecision_TOS;   //!
   TBranch        *b_B_L0ElectronDecision_Dec;   //!
   TBranch        *b_B_L0ElectronDecision_TIS;   //!
   TBranch        *b_B_L0ElectronDecision_TOS;   //!
   TBranch        *b_B_L0ElectronHiDecision_Dec;   //!
   TBranch        *b_B_L0ElectronHiDecision_TIS;   //!
   TBranch        *b_B_L0ElectronHiDecision_TOS;   //!
   TBranch        *b_B_L0PhotonDecision_Dec;   //!
   TBranch        *b_B_L0PhotonDecision_TIS;   //!
   TBranch        *b_B_L0PhotonDecision_TOS;   //!
   TBranch        *b_B_L0PhotonHiDecision_Dec;   //!
   TBranch        *b_B_L0PhotonHiDecision_TIS;   //!
   TBranch        *b_B_L0PhotonHiDecision_TOS;   //!
   TBranch        *b_B_Hlt1SingleMuonNoIPDecision_Dec;   //!
   TBranch        *b_B_Hlt1SingleMuonNoIPDecision_TIS;   //!
   TBranch        *b_B_Hlt1SingleMuonNoIPDecision_TOS;   //!
   TBranch        *b_B_Hlt1SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_B_Hlt1SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_B_Hlt1SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_B_Hlt1SingleElectronNoIPDecision_Dec;   //!
   TBranch        *b_B_Hlt1SingleElectronNoIPDecision_TIS;   //!
   TBranch        *b_B_Hlt1SingleElectronNoIPDecision_TOS;   //!
   TBranch        *b_B_Hlt1TrackAllL0Decision_Dec;   //!
   TBranch        *b_B_Hlt1TrackAllL0Decision_TIS;   //!
   TBranch        *b_B_Hlt1TrackAllL0Decision_TOS;   //!
   TBranch        *b_B_Hlt1TrackMuonDecision_Dec;   //!
   TBranch        *b_B_Hlt1TrackMuonDecision_TIS;   //!
   TBranch        *b_B_Hlt1TrackMuonDecision_TOS;   //!
   TBranch        *b_B_Hlt1TrackPhotonDecision_Dec;   //!
   TBranch        *b_B_Hlt1TrackPhotonDecision_TIS;   //!
   TBranch        *b_B_Hlt1TrackPhotonDecision_TOS;   //!
   TBranch        *b_B_Hlt1TrackAllL0__Decision_Dec;   //!
   TBranch        *b_B_Hlt1TrackAllL0__Decision_TIS;   //!
   TBranch        *b_B_Hlt1TrackAllL0__Decision_TOS;   //!
   TBranch        *b_B_Hlt1DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_B_Hlt1DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_B_Hlt1DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_B_Hlt1DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_B_Hlt1DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_B_Hlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_B_Hlt1MB__Decision_Dec;   //!
   TBranch        *b_B_Hlt1MB__Decision_TIS;   //!
   TBranch        *b_B_Hlt1MB__Decision_TOS;   //!
   TBranch        *b_B_Hlt1TrackAllL0TightDecision_Dec;   //!
   TBranch        *b_B_Hlt1TrackAllL0TightDecision_TIS;   //!
   TBranch        *b_B_Hlt1TrackAllL0TightDecision_TOS;   //!
   TBranch        *b_B_Hlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_B_Hlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_B_Hlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_B_Hlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_B_Hlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_B_Hlt2SingleMuonLowPTDecision_TOS;   //!
   TBranch        *b_B_Hlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_B_Hlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_B_Hlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonJPsiDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonJPsiDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonJPsiDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonJPsiHighPTDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonJPsiHighPTDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonJPsiHighPTDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonPsi2SDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonPsi2SDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonPsi2SDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedJPsiDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedJPsiDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedJPsiDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedHeavyDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedHeavyDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonDetachedHeavyDecision_TOS;   //!
   TBranch        *b_B_Hlt2TriMuonTauDecision_Dec;   //!
   TBranch        *b_B_Hlt2TriMuonTauDecision_TIS;   //!
   TBranch        *b_B_Hlt2TriMuonTauDecision_TOS;   //!
   TBranch        *b_B_Hlt2B2HHDecision_Dec;   //!
   TBranch        *b_B_Hlt2B2HHDecision_TIS;   //!
   TBranch        *b_B_Hlt2B2HHDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonBDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonBDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonBDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonZDecision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonZDecision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonZDecision_TOS;   //!
   TBranch        *b_B_Hlt2TopoMu2BodyBBDTDecision_Dec;   //!
   TBranch        *b_B_Hlt2TopoMu2BodyBBDTDecision_TIS;   //!
   TBranch        *b_B_Hlt2TopoMu2BodyBBDTDecision_TOS;   //!
   TBranch        *b_B_Hlt2TopoMu3BodyBBDTDecision_Dec;   //!
   TBranch        *b_B_Hlt2TopoMu3BodyBBDTDecision_TIS;   //!
   TBranch        *b_B_Hlt2TopoMu3BodyBBDTDecision_TOS;   //!
   TBranch        *b_B_Hlt2TopoMu4BodyBBDTDecision_Dec;   //!
   TBranch        *b_B_Hlt2TopoMu4BodyBBDTDecision_TIS;   //!
   TBranch        *b_B_Hlt2TopoMu4BodyBBDTDecision_TOS;   //!
   TBranch        *b_B_Hlt2Topo2BodyBBDTDecision_Dec;   //!
   TBranch        *b_B_Hlt2Topo2BodyBBDTDecision_TIS;   //!
   TBranch        *b_B_Hlt2Topo2BodyBBDTDecision_TOS;   //!
   TBranch        *b_B_Hlt2Topo3BodyBBDTDecision_Dec;   //!
   TBranch        *b_B_Hlt2Topo3BodyBBDTDecision_TIS;   //!
   TBranch        *b_B_Hlt2Topo3BodyBBDTDecision_TOS;   //!
   TBranch        *b_B_Hlt2Topo4BodyBBDTDecision_Dec;   //!
   TBranch        *b_B_Hlt2Topo4BodyBBDTDecision_TIS;   //!
   TBranch        *b_B_Hlt2Topo4BodyBBDTDecision_TOS;   //!
   TBranch        *b_B_Hlt2Topo2BodySimpleDecision_Dec;   //!
   TBranch        *b_B_Hlt2Topo2BodySimpleDecision_TIS;   //!
   TBranch        *b_B_Hlt2Topo2BodySimpleDecision_TOS;   //!
   TBranch        *b_B_Hlt2Topo3BodySimpleDecision_Dec;   //!
   TBranch        *b_B_Hlt2Topo3BodySimpleDecision_TIS;   //!
   TBranch        *b_B_Hlt2Topo3BodySimpleDecision_TOS;   //!
   TBranch        *b_B_Hlt2Topo4BodySimpleDecision_Dec;   //!
   TBranch        *b_B_Hlt2Topo4BodySimpleDecision_TIS;   //!
   TBranch        *b_B_Hlt2Topo4BodySimpleDecision_TOS;   //!
   TBranch        *b_B_Hlt2PassThroughDecision_Dec;   //!
   TBranch        *b_B_Hlt2PassThroughDecision_TIS;   //!
   TBranch        *b_B_Hlt2PassThroughDecision_TOS;   //!
   TBranch        *b_B_Hlt2TransparentDecision_Dec;   //!
   TBranch        *b_B_Hlt2TransparentDecision_TIS;   //!
   TBranch        *b_B_Hlt2TransparentDecision_TOS;   //!
   TBranch        *b_B_Hlt2IncPhiDecision_Dec;   //!
   TBranch        *b_B_Hlt2IncPhiDecision_TIS;   //!
   TBranch        *b_B_Hlt2IncPhiDecision_TOS;   //!
   TBranch        *b_B_Hlt2DiMuonDY__Decision_Dec;   //!
   TBranch        *b_B_Hlt2DiMuonDY__Decision_TIS;   //!
   TBranch        *b_B_Hlt2DiMuonDY__Decision_TOS;   //!
   TBranch        *b_B_Hlt2TopoE__Decision_Dec;   //!
   TBranch        *b_B_Hlt2TopoE__Decision_TIS;   //!
   TBranch        *b_B_Hlt2TopoE__Decision_TOS;   //!
   TBranch        *b_B_Hlt2Topo__Decision_Dec;   //!
   TBranch        *b_B_Hlt2Topo__Decision_TIS;   //!
   TBranch        *b_B_Hlt2Topo__Decision_TOS;   //!
   TBranch        *b_B_Hlt2Charm__Decision_Dec;   //!
   TBranch        *b_B_Hlt2Charm__Decision_TIS;   //!
   TBranch        *b_B_Hlt2Charm__Decision_TOS;   //!
   TBranch        *b_B_Hlt2DiElectron__Decision_Dec;   //!
   TBranch        *b_B_Hlt2DiElectron__Decision_TIS;   //!
   TBranch        *b_B_Hlt2DiElectron__Decision_TOS;   //!
   TBranch        *b_B_Hlt2__GammaDecision_Dec;   //!
   TBranch        *b_B_Hlt2__GammaDecision_TIS;   //!
   TBranch        *b_B_Hlt2__GammaDecision_TOS;   //!
   TBranch        *b_B_DTF_M;   //!
   TBranch        *b_B_DTF_MM;   //!
   TBranch        *b_B_DTF_P;   //!
   TBranch        *b_B_DTF_PE;   //!
   TBranch        *b_B_DTF_PT;   //!
   TBranch        *b_B_DTF_PX;   //!
   TBranch        *b_B_DTF_PY;   //!
   TBranch        *b_B_DTF_PZ;   //!
   TBranch        *b_B_DTF_VFit_M;   //!
   TBranch        *b_B_DTF_VFit_MM;   //!
   TBranch        *b_B_DTF_VFit_P;   //!
   TBranch        *b_B_DTF_VFit_PE;   //!
   TBranch        *b_B_DTF_VFit_PT;   //!
   TBranch        *b_B_DTF_VFit_PX;   //!
   TBranch        *b_B_DTF_VFit_PY;   //!
   TBranch        *b_B_DTF_VFit_PZ;   //!
   TBranch        *b_B_WRONGMASS_K_K;   //!
   TBranch        *b_B_WRONGMASS_K_p;   //!
   TBranch        *b_B_WRONGMASS_K_pi;   //!
   TBranch        *b_B_WRONGMASS_p_K;   //!
   TBranch        *b_B_WRONGMASS_p_pi;   //!
   TBranch        *b_B_WRONGMASS_pi_K;   //!
   TBranch        *b_B_WRONGMASS_pi_p;   //!
   TBranch        *b_B_WRONGMASS_pi_pi;   //!
   TBranch        *b_B_WRONGMASS_K_K_2;   //!
   TBranch        *b_B_WRONGMASS_K_p_2;   //!
   TBranch        *b_B_WRONGMASS_K_pi_2;   //!
   TBranch        *b_B_WRONGMASS_p_K_2;   //!
   TBranch        *b_B_WRONGMASS_p_pi_2;   //!
   TBranch        *b_B_WRONGMASS_pi_K_2;   //!
   TBranch        *b_B_WRONGMASS_pi_p_2;   //!
   TBranch        *b_B_WRONGMASS_pi_pi_2;   //!
   TBranch        *b_B_Vf;   //!
   TBranch        *b_MPT_iso;   //!
   TBranch        *b_MPT_iso_UpS;   //!
   TBranch        *b_MPT_iso_DwS;   //!
   TBranch        *b_Vf_Max;   //!
   TBranch        *b_Vf_Max_UpS;   //!
   TBranch        *b_Vf_Max_DwS;   //!
   TBranch        *b_Pos_Max;   //!
   TBranch        *b_Pos_Max_UpS;   //!
   TBranch        *b_Pos_Max_DwS;   //!
   TBranch        *b_sum_Vf_Maxs;   //!
   TBranch        *b_sum_Vf_Maxs_UpS;   //!
   TBranch        *b_B_ZVtop_nvtx;   //!
   TBranch        *b_B_zv_same;   //!
   TBranch        *b_MuP_zv_ipsall;   //!
   TBranch        *b_MuP_zv_ipall;   //!
   TBranch        *b_MuP_zv_proba;   //!
   TBranch        *b_MuP_zv_proba_close;   //!
   TBranch        *b_MuP_zv_chi2;   //!
   TBranch        *b_MuP_zv_dist;   //!
   TBranch        *b_MuP_zv_ntrkvtz;   //!
   TBranch        *b_MuM_zv_ipsall;   //!
   TBranch        *b_MuM_zv_ipall;   //!
   TBranch        *b_MuM_zv_proba;   //!
   TBranch        *b_MuM_zv_proba_close;   //!
   TBranch        *b_MuM_zv_chi2;   //!
   TBranch        *b_MuM_zv_dist;   //!
   TBranch        *b_MuM_zv_ntrkvtz;   //!
   TBranch        *b_zv_ipsall;   //!
   TBranch        *b_zv_ipall;   //!
   TBranch        *b_zv_proba;   //!
   TBranch        *b_zv_proba_close;   //!
   TBranch        *b_zv_chi2;   //!
   TBranch        *b_zv_dist;   //!
   TBranch        *b_zv_ntrkvtz;   //!
   TBranch        *b_ZViso;   //!
   TBranch        *b_B_Fit_nPV;   //!
   TBranch        *b_B_Fit_M;   //!
   TBranch        *b_B_Fit_MERR;   //!
   TBranch        *b_B_Fit_P;   //!
   TBranch        *b_B_Fit_PERR;   //!
   TBranch        *b_B_Fit_chi2;   //!
   TBranch        *b_B_Fit_muminus_0_ID;   //!
   TBranch        *b_B_Fit_muminus_0_PE;   //!
   TBranch        *b_B_Fit_muminus_0_PX;   //!
   TBranch        *b_B_Fit_muminus_0_PY;   //!
   TBranch        *b_B_Fit_muminus_0_PZ;   //!
   TBranch        *b_B_Fit_muminus_ID;   //!
   TBranch        *b_B_Fit_muminus_PE;   //!
   TBranch        *b_B_Fit_muminus_PX;   //!
   TBranch        *b_B_Fit_muminus_PY;   //!
   TBranch        *b_B_Fit_muminus_PZ;   //!
   TBranch        *b_B_Fit_nDOF;   //!
   TBranch        *b_B_Fit_nIter;   //!
   TBranch        *b_B_Fit_status;   //!
   TBranch        *b_B_VFit_nPV;   //!
   TBranch        *b_B_VFit_M;   //!
   TBranch        *b_B_VFit_MERR;   //!
   TBranch        *b_B_VFit_P;   //!
   TBranch        *b_B_VFit_PERR;   //!
   TBranch        *b_B_VFit_PV_X;   //!
   TBranch        *b_B_VFit_PV_Y;   //!
   TBranch        *b_B_VFit_PV_Z;   //!
   TBranch        *b_B_VFit_PV_key;   //!
   TBranch        *b_B_VFit_chi2;   //!
   TBranch        *b_B_VFit_ctau;   //!
   TBranch        *b_B_VFit_ctauErr;   //!
   TBranch        *b_B_VFit_decayLength;   //!
   TBranch        *b_B_VFit_decayLengthErr;   //!
   TBranch        *b_B_VFit_muminus_0_ID;   //!
   TBranch        *b_B_VFit_muminus_0_PE;   //!
   TBranch        *b_B_VFit_muminus_0_PX;   //!
   TBranch        *b_B_VFit_muminus_0_PY;   //!
   TBranch        *b_B_VFit_muminus_0_PZ;   //!
   TBranch        *b_B_VFit_muminus_ID;   //!
   TBranch        *b_B_VFit_muminus_PE;   //!
   TBranch        *b_B_VFit_muminus_PX;   //!
   TBranch        *b_B_VFit_muminus_PY;   //!
   TBranch        *b_B_VFit_muminus_PZ;   //!
   TBranch        *b_B_VFit_nDOF;   //!
   TBranch        *b_B_VFit_nIter;   //!
   TBranch        *b_B_VFit_status;   //!
   TBranch        *b_B_JETNOMU1PX;   //!
   TBranch        *b_B_JETNOMU1PY;   //!
   TBranch        *b_B_JETNOMU1PZ;   //!
   TBranch        *b_B_JETNOMU1PT;   //!
   TBranch        *b_B_JETNOMU1JETWIDTH;   //!
   TBranch        *b_B_JETNOMU1NNTAG;   //!
   TBranch        *b_B_JETNOMU1MNF;   //!
   TBranch        *b_B_JETNOMU2PX;   //!
   TBranch        *b_B_JETNOMU2PY;   //!
   TBranch        *b_B_JETNOMU2PZ;   //!
   TBranch        *b_B_JETNOMU2PT;   //!
   TBranch        *b_B_JETNOMU2JETWIDTH;   //!
   TBranch        *b_B_JETNOMU2NNTAG;   //!
   TBranch        *b_B_JETNOMU2MNF;   //!
   TBranch        *b_B_JETNOMU3PX;   //!
   TBranch        *b_B_JETNOMU3PY;   //!
   TBranch        *b_B_JETNOMU3PZ;   //!
   TBranch        *b_B_JETNOMU3PT;   //!
   TBranch        *b_B_JETNOMU3JETWIDTH;   //!
   TBranch        *b_B_JETNOMU3NNTAG;   //!
   TBranch        *b_B_JETNOMU3MNF;   //!
   TBranch        *b_B_JETMU1PX;   //!
   TBranch        *b_B_JETMU1PY;   //!
   TBranch        *b_B_JETMU1PZ;   //!
   TBranch        *b_B_JETMU1PT;   //!
   TBranch        *b_B_JETMU1JETWIDTH;   //!
   TBranch        *b_B_JETMU1NNTAG;   //!
   TBranch        *b_B_JETMU1MNF;   //!
   TBranch        *b_B_JETBPX;   //!
   TBranch        *b_B_JETBPY;   //!
   TBranch        *b_B_JETBPZ;   //!
   TBranch        *b_B_JETBPT;   //!
   TBranch        *b_B_JETBJETWIDTH;   //!
   TBranch        *b_B_JETBNNTAG;   //!
   TBranch        *b_B_JETBMNF;   //!
   TBranch        *b_B_JETMU2PX;   //!
   TBranch        *b_B_JETMU2PY;   //!
   TBranch        *b_B_JETMU2PZ;   //!
   TBranch        *b_B_JETMU2PT;   //!
   TBranch        *b_B_JETMU2JETWIDTH;   //!
   TBranch        *b_B_JETMU2NNTAG;   //!
   TBranch        *b_B_JETMU2MNF;   //!
   TBranch        *b_muplus_BPVDIRA;   //!
   TBranch        *b_muplus_BPVIPCHI2;   //!
   TBranch        *b_muplus_BPVVDCHI2;   //!
   TBranch        *b_muplus_BPVVDZ;   //!
   TBranch        *b_muplus_DOCAMAX;   //!
   TBranch        *b_muplus_MINIPCHI2;   //!
   TBranch        *b_muplus_VFASPF;   //!
   TBranch        *b_muplus_MC12TuneV2_ProbNNe;   //!
   TBranch        *b_muplus_MC12TuneV2_ProbNNmu;   //!
   TBranch        *b_muplus_MC12TuneV2_ProbNNpi;   //!
   TBranch        *b_muplus_MC12TuneV2_ProbNNk;   //!
   TBranch        *b_muplus_MC12TuneV2_ProbNNp;   //!
   TBranch        *b_muplus_MC12TuneV2_ProbNNghost;   //!
   TBranch        *b_muplus_MC12TuneV3_ProbNNe;   //!
   TBranch        *b_muplus_MC12TuneV3_ProbNNmu;   //!
   TBranch        *b_muplus_MC12TuneV3_ProbNNpi;   //!
   TBranch        *b_muplus_MC12TuneV3_ProbNNk;   //!
   TBranch        *b_muplus_MC12TuneV3_ProbNNp;   //!
   TBranch        *b_muplus_MC12TuneV3_ProbNNghost;   //!
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
   TBranch        *b_muplus_Xs1;   //!
   TBranch        *b_muplus_Ys1;   //!
   TBranch        *b_muplus_Xs2;   //!
   TBranch        *b_muplus_Ys2;   //!
   TBranch        *b_muplus_Xs3;   //!
   TBranch        *b_muplus_Ys3;   //!
   TBranch        *b_muplus_Xs4;   //!
   TBranch        *b_muplus_Ys4;   //!
   TBranch        *b_muplus_Xs5;   //!
   TBranch        *b_muplus_Ys5;   //!
   TBranch        *b_muplus_DistAve;   //!
   TBranch        *b_muplus_ID;   //!
   TBranch        *b_muplus_CombDLLMu;   //!
   TBranch        *b_muplus_ProbNNmu;   //!
   TBranch        *b_muplus_ProbNNghost;   //!
   TBranch        *b_muplus_InMuonAcc;   //!
   TBranch        *b_muplus_MuonDist2;   //!
   TBranch        *b_muplus_regionInM2;   //!
   TBranch        *b_muplus_hasMuon;   //!
   TBranch        *b_muplus_isMuon;   //!
   TBranch        *b_muplus_isMuonLoose;   //!
   TBranch        *b_muplus_NShared;   //!
   TBranch        *b_muplus_MuonLLmu;   //!
   TBranch        *b_muplus_MuonLLbg;   //!
   TBranch        *b_muplus_isMuonFromProto;   //!
   TBranch        *b_muplus_nVeloIDs;   //!
   TBranch        *b_muplus_nITIDs;   //!
   TBranch        *b_muplus_nTTIDs;   //!
   TBranch        *b_muplus_nOTIDs;   //!
   TBranch        *b_muplus_eta;   //!
   TBranch        *b_muplus_phi;   //!
   TBranch        *b_muplus_typeOriginVtx;   //!
   TBranch        *b_muplus_nEndVertices;   //!
   TBranch        *b_muplus_ancestorpid;   //!
   TBranch        *b_muplus_MCI;   //!
   TBranch        *b_muplus_PIDe;   //!
   TBranch        *b_muplus_PIDmu;   //!
   TBranch        *b_muplus_PIDK;   //!
   TBranch        *b_muplus_PIDp;   //!
   TBranch        *b_muplus_ProbNNe;   //!
   TBranch        *b_muplus_ProbNNk;   //!
   TBranch        *b_muplus_ProbNNp;   //!
   TBranch        *b_muplus_ProbNNpi;   //!
   TBranch        *b_muplus_hasRich;   //!
   TBranch        *b_muplus_hasCalo;   //!
   TBranch        *b_muplus_L0Global_Dec;   //!
   TBranch        *b_muplus_L0Global_TIS;   //!
   TBranch        *b_muplus_L0Global_TOS;   //!
   TBranch        *b_muplus_Hlt1Global_Dec;   //!
   TBranch        *b_muplus_Hlt1Global_TIS;   //!
   TBranch        *b_muplus_Hlt1Global_TOS;   //!
   TBranch        *b_muplus_Hlt1Phys_Dec;   //!
   TBranch        *b_muplus_Hlt1Phys_TIS;   //!
   TBranch        *b_muplus_Hlt1Phys_TOS;   //!
   TBranch        *b_muplus_Hlt2Global_Dec;   //!
   TBranch        *b_muplus_Hlt2Global_TIS;   //!
   TBranch        *b_muplus_Hlt2Global_TOS;   //!
   TBranch        *b_muplus_Hlt2Phys_Dec;   //!
   TBranch        *b_muplus_Hlt2Phys_TIS;   //!
   TBranch        *b_muplus_Hlt2Phys_TOS;   //!
   TBranch        *b_muplus_L0MuonDecision_Dec;   //!
   TBranch        *b_muplus_L0MuonDecision_TIS;   //!
   TBranch        *b_muplus_L0MuonDecision_TOS;   //!
   TBranch        *b_muplus_L0DiMuonDecision_Dec;   //!
   TBranch        *b_muplus_L0DiMuonDecision_TIS;   //!
   TBranch        *b_muplus_L0DiMuonDecision_TOS;   //!
   TBranch        *b_muplus_L0HadronDecision_Dec;   //!
   TBranch        *b_muplus_L0HadronDecision_TIS;   //!
   TBranch        *b_muplus_L0HadronDecision_TOS;   //!
   TBranch        *b_muplus_L0ElectronDecision_Dec;   //!
   TBranch        *b_muplus_L0ElectronDecision_TIS;   //!
   TBranch        *b_muplus_L0ElectronDecision_TOS;   //!
   TBranch        *b_muplus_L0ElectronHiDecision_Dec;   //!
   TBranch        *b_muplus_L0ElectronHiDecision_TIS;   //!
   TBranch        *b_muplus_L0ElectronHiDecision_TOS;   //!
   TBranch        *b_muplus_L0PhotonDecision_Dec;   //!
   TBranch        *b_muplus_L0PhotonDecision_TIS;   //!
   TBranch        *b_muplus_L0PhotonDecision_TOS;   //!
   TBranch        *b_muplus_L0PhotonHiDecision_Dec;   //!
   TBranch        *b_muplus_L0PhotonHiDecision_TIS;   //!
   TBranch        *b_muplus_L0PhotonHiDecision_TOS;   //!
   TBranch        *b_muplus_Hlt1SingleMuonNoIPDecision_Dec;   //!
   TBranch        *b_muplus_Hlt1SingleMuonNoIPDecision_TIS;   //!
   TBranch        *b_muplus_Hlt1SingleMuonNoIPDecision_TOS;   //!
   TBranch        *b_muplus_Hlt1SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_muplus_Hlt1SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_muplus_Hlt1SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_muplus_Hlt1SingleElectronNoIPDecision_Dec;   //!
   TBranch        *b_muplus_Hlt1SingleElectronNoIPDecision_TIS;   //!
   TBranch        *b_muplus_Hlt1SingleElectronNoIPDecision_TOS;   //!
   TBranch        *b_muplus_Hlt1TrackAllL0Decision_Dec;   //!
   TBranch        *b_muplus_Hlt1TrackAllL0Decision_TIS;   //!
   TBranch        *b_muplus_Hlt1TrackAllL0Decision_TOS;   //!
   TBranch        *b_muplus_Hlt1TrackMuonDecision_Dec;   //!
   TBranch        *b_muplus_Hlt1TrackMuonDecision_TIS;   //!
   TBranch        *b_muplus_Hlt1TrackMuonDecision_TOS;   //!
   TBranch        *b_muplus_Hlt1TrackPhotonDecision_Dec;   //!
   TBranch        *b_muplus_Hlt1TrackPhotonDecision_TIS;   //!
   TBranch        *b_muplus_Hlt1TrackPhotonDecision_TOS;   //!
   TBranch        *b_muplus_Hlt1TrackAllL0__Decision_Dec;   //!
   TBranch        *b_muplus_Hlt1TrackAllL0__Decision_TIS;   //!
   TBranch        *b_muplus_Hlt1TrackAllL0__Decision_TOS;   //!
   TBranch        *b_muplus_Hlt1DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_muplus_Hlt1DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_muplus_Hlt1DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_muplus_Hlt1DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_muplus_Hlt1DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_muplus_Hlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_muplus_Hlt1MB__Decision_Dec;   //!
   TBranch        *b_muplus_Hlt1MB__Decision_TIS;   //!
   TBranch        *b_muplus_Hlt1MB__Decision_TOS;   //!
   TBranch        *b_muplus_Hlt1TrackAllL0TightDecision_Dec;   //!
   TBranch        *b_muplus_Hlt1TrackAllL0TightDecision_TIS;   //!
   TBranch        *b_muplus_Hlt1TrackAllL0TightDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2SingleMuonLowPTDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2DiMuonDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2DiMuonDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2DiMuonDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2DiMuonJPsiDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2DiMuonJPsiDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2DiMuonJPsiDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2DiMuonJPsiHighPTDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2DiMuonJPsiHighPTDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2DiMuonJPsiHighPTDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2DiMuonPsi2SDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2DiMuonPsi2SDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2DiMuonPsi2SDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2DiMuonDetachedDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2DiMuonDetachedDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2DiMuonDetachedDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2DiMuonDetachedJPsiDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2DiMuonDetachedJPsiDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2DiMuonDetachedJPsiDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2DiMuonDetachedHeavyDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2DiMuonDetachedHeavyDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2DiMuonDetachedHeavyDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2TriMuonTauDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2TriMuonTauDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2TriMuonTauDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2B2HHDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2B2HHDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2B2HHDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2DiMuonBDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2DiMuonBDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2DiMuonBDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2DiMuonZDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2DiMuonZDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2DiMuonZDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2TopoMu2BodyBBDTDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2TopoMu2BodyBBDTDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2TopoMu2BodyBBDTDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2TopoMu3BodyBBDTDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2TopoMu3BodyBBDTDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2TopoMu3BodyBBDTDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2TopoMu4BodyBBDTDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2TopoMu4BodyBBDTDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2TopoMu4BodyBBDTDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2Topo2BodyBBDTDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2Topo2BodyBBDTDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2Topo2BodyBBDTDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2Topo3BodyBBDTDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2Topo3BodyBBDTDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2Topo3BodyBBDTDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2Topo4BodyBBDTDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2Topo4BodyBBDTDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2Topo4BodyBBDTDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2Topo2BodySimpleDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2Topo2BodySimpleDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2Topo2BodySimpleDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2Topo3BodySimpleDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2Topo3BodySimpleDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2Topo3BodySimpleDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2Topo4BodySimpleDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2Topo4BodySimpleDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2Topo4BodySimpleDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2PassThroughDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2PassThroughDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2PassThroughDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2TransparentDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2TransparentDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2TransparentDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2IncPhiDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2IncPhiDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2IncPhiDecision_TOS;   //!
   TBranch        *b_muplus_Hlt2DiMuonDY__Decision_Dec;   //!
   TBranch        *b_muplus_Hlt2DiMuonDY__Decision_TIS;   //!
   TBranch        *b_muplus_Hlt2DiMuonDY__Decision_TOS;   //!
   TBranch        *b_muplus_Hlt2TopoE__Decision_Dec;   //!
   TBranch        *b_muplus_Hlt2TopoE__Decision_TIS;   //!
   TBranch        *b_muplus_Hlt2TopoE__Decision_TOS;   //!
   TBranch        *b_muplus_Hlt2Topo__Decision_Dec;   //!
   TBranch        *b_muplus_Hlt2Topo__Decision_TIS;   //!
   TBranch        *b_muplus_Hlt2Topo__Decision_TOS;   //!
   TBranch        *b_muplus_Hlt2Charm__Decision_Dec;   //!
   TBranch        *b_muplus_Hlt2Charm__Decision_TIS;   //!
   TBranch        *b_muplus_Hlt2Charm__Decision_TOS;   //!
   TBranch        *b_muplus_Hlt2DiElectron__Decision_Dec;   //!
   TBranch        *b_muplus_Hlt2DiElectron__Decision_TIS;   //!
   TBranch        *b_muplus_Hlt2DiElectron__Decision_TOS;   //!
   TBranch        *b_muplus_Hlt2__GammaDecision_Dec;   //!
   TBranch        *b_muplus_Hlt2__GammaDecision_TIS;   //!
   TBranch        *b_muplus_Hlt2__GammaDecision_TOS;   //!
   TBranch        *b_muplus_TRACK_Type;   //!
   TBranch        *b_muplus_TRACK_Key;   //!
   TBranch        *b_muplus_TRACK_CHI2NDOF;   //!
   TBranch        *b_muplus_TRACK_PCHI2;   //!
   TBranch        *b_muplus_TRACK_MatchCHI2;   //!
   TBranch        *b_muplus_TRACK_GhostProb;   //!
   TBranch        *b_muplus_TRACK_CloneDist;   //!
   TBranch        *b_muplus_TRACK_Likelihood;   //!
   TBranch        *b_muminus_BPVDIRA;   //!
   TBranch        *b_muminus_BPVIPCHI2;   //!
   TBranch        *b_muminus_BPVVDCHI2;   //!
   TBranch        *b_muminus_BPVVDZ;   //!
   TBranch        *b_muminus_DOCAMAX;   //!
   TBranch        *b_muminus_MINIPCHI2;   //!
   TBranch        *b_muminus_VFASPF;   //!
   TBranch        *b_muminus_MC12TuneV2_ProbNNe;   //!
   TBranch        *b_muminus_MC12TuneV2_ProbNNmu;   //!
   TBranch        *b_muminus_MC12TuneV2_ProbNNpi;   //!
   TBranch        *b_muminus_MC12TuneV2_ProbNNk;   //!
   TBranch        *b_muminus_MC12TuneV2_ProbNNp;   //!
   TBranch        *b_muminus_MC12TuneV2_ProbNNghost;   //!
   TBranch        *b_muminus_MC12TuneV3_ProbNNe;   //!
   TBranch        *b_muminus_MC12TuneV3_ProbNNmu;   //!
   TBranch        *b_muminus_MC12TuneV3_ProbNNpi;   //!
   TBranch        *b_muminus_MC12TuneV3_ProbNNk;   //!
   TBranch        *b_muminus_MC12TuneV3_ProbNNp;   //!
   TBranch        *b_muminus_MC12TuneV3_ProbNNghost;   //!
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
   TBranch        *b_muminus_Xs1;   //!
   TBranch        *b_muminus_Ys1;   //!
   TBranch        *b_muminus_Xs2;   //!
   TBranch        *b_muminus_Ys2;   //!
   TBranch        *b_muminus_Xs3;   //!
   TBranch        *b_muminus_Ys3;   //!
   TBranch        *b_muminus_Xs4;   //!
   TBranch        *b_muminus_Ys4;   //!
   TBranch        *b_muminus_Xs5;   //!
   TBranch        *b_muminus_Ys5;   //!
   TBranch        *b_muminus_DistAve;   //!
   TBranch        *b_muminus_ID;   //!
   TBranch        *b_muminus_CombDLLMu;   //!
   TBranch        *b_muminus_ProbNNmu;   //!
   TBranch        *b_muminus_ProbNNghost;   //!
   TBranch        *b_muminus_InMuonAcc;   //!
   TBranch        *b_muminus_MuonDist2;   //!
   TBranch        *b_muminus_regionInM2;   //!
   TBranch        *b_muminus_hasMuon;   //!
   TBranch        *b_muminus_isMuon;   //!
   TBranch        *b_muminus_isMuonLoose;   //!
   TBranch        *b_muminus_NShared;   //!
   TBranch        *b_muminus_MuonLLmu;   //!
   TBranch        *b_muminus_MuonLLbg;   //!
   TBranch        *b_muminus_isMuonFromProto;   //!
   TBranch        *b_muminus_nVeloIDs;   //!
   TBranch        *b_muminus_nITIDs;   //!
   TBranch        *b_muminus_nTTIDs;   //!
   TBranch        *b_muminus_nOTIDs;   //!
   TBranch        *b_muminus_eta;   //!
   TBranch        *b_muminus_phi;   //!
   TBranch        *b_muminus_typeOriginVtx;   //!
   TBranch        *b_muminus_nEndVertices;   //!
   TBranch        *b_muminus_ancestorpid;   //!
   TBranch        *b_muminus_MCI;   //!
   TBranch        *b_muminus_PIDe;   //!
   TBranch        *b_muminus_PIDmu;   //!
   TBranch        *b_muminus_PIDK;   //!
   TBranch        *b_muminus_PIDp;   //!
   TBranch        *b_muminus_ProbNNe;   //!
   TBranch        *b_muminus_ProbNNk;   //!
   TBranch        *b_muminus_ProbNNp;   //!
   TBranch        *b_muminus_ProbNNpi;   //!
   TBranch        *b_muminus_hasRich;   //!
   TBranch        *b_muminus_hasCalo;   //!
   TBranch        *b_muminus_L0Global_Dec;   //!
   TBranch        *b_muminus_L0Global_TIS;   //!
   TBranch        *b_muminus_L0Global_TOS;   //!
   TBranch        *b_muminus_Hlt1Global_Dec;   //!
   TBranch        *b_muminus_Hlt1Global_TIS;   //!
   TBranch        *b_muminus_Hlt1Global_TOS;   //!
   TBranch        *b_muminus_Hlt1Phys_Dec;   //!
   TBranch        *b_muminus_Hlt1Phys_TIS;   //!
   TBranch        *b_muminus_Hlt1Phys_TOS;   //!
   TBranch        *b_muminus_Hlt2Global_Dec;   //!
   TBranch        *b_muminus_Hlt2Global_TIS;   //!
   TBranch        *b_muminus_Hlt2Global_TOS;   //!
   TBranch        *b_muminus_Hlt2Phys_Dec;   //!
   TBranch        *b_muminus_Hlt2Phys_TIS;   //!
   TBranch        *b_muminus_Hlt2Phys_TOS;   //!
   TBranch        *b_muminus_L0MuonDecision_Dec;   //!
   TBranch        *b_muminus_L0MuonDecision_TIS;   //!
   TBranch        *b_muminus_L0MuonDecision_TOS;   //!
   TBranch        *b_muminus_L0DiMuonDecision_Dec;   //!
   TBranch        *b_muminus_L0DiMuonDecision_TIS;   //!
   TBranch        *b_muminus_L0DiMuonDecision_TOS;   //!
   TBranch        *b_muminus_L0HadronDecision_Dec;   //!
   TBranch        *b_muminus_L0HadronDecision_TIS;   //!
   TBranch        *b_muminus_L0HadronDecision_TOS;   //!
   TBranch        *b_muminus_L0ElectronDecision_Dec;   //!
   TBranch        *b_muminus_L0ElectronDecision_TIS;   //!
   TBranch        *b_muminus_L0ElectronDecision_TOS;   //!
   TBranch        *b_muminus_L0ElectronHiDecision_Dec;   //!
   TBranch        *b_muminus_L0ElectronHiDecision_TIS;   //!
   TBranch        *b_muminus_L0ElectronHiDecision_TOS;   //!
   TBranch        *b_muminus_L0PhotonDecision_Dec;   //!
   TBranch        *b_muminus_L0PhotonDecision_TIS;   //!
   TBranch        *b_muminus_L0PhotonDecision_TOS;   //!
   TBranch        *b_muminus_L0PhotonHiDecision_Dec;   //!
   TBranch        *b_muminus_L0PhotonHiDecision_TIS;   //!
   TBranch        *b_muminus_L0PhotonHiDecision_TOS;   //!
   TBranch        *b_muminus_Hlt1SingleMuonNoIPDecision_Dec;   //!
   TBranch        *b_muminus_Hlt1SingleMuonNoIPDecision_TIS;   //!
   TBranch        *b_muminus_Hlt1SingleMuonNoIPDecision_TOS;   //!
   TBranch        *b_muminus_Hlt1SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_muminus_Hlt1SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_muminus_Hlt1SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_muminus_Hlt1SingleElectronNoIPDecision_Dec;   //!
   TBranch        *b_muminus_Hlt1SingleElectronNoIPDecision_TIS;   //!
   TBranch        *b_muminus_Hlt1SingleElectronNoIPDecision_TOS;   //!
   TBranch        *b_muminus_Hlt1TrackAllL0Decision_Dec;   //!
   TBranch        *b_muminus_Hlt1TrackAllL0Decision_TIS;   //!
   TBranch        *b_muminus_Hlt1TrackAllL0Decision_TOS;   //!
   TBranch        *b_muminus_Hlt1TrackMuonDecision_Dec;   //!
   TBranch        *b_muminus_Hlt1TrackMuonDecision_TIS;   //!
   TBranch        *b_muminus_Hlt1TrackMuonDecision_TOS;   //!
   TBranch        *b_muminus_Hlt1TrackPhotonDecision_Dec;   //!
   TBranch        *b_muminus_Hlt1TrackPhotonDecision_TIS;   //!
   TBranch        *b_muminus_Hlt1TrackPhotonDecision_TOS;   //!
   TBranch        *b_muminus_Hlt1TrackAllL0__Decision_Dec;   //!
   TBranch        *b_muminus_Hlt1TrackAllL0__Decision_TIS;   //!
   TBranch        *b_muminus_Hlt1TrackAllL0__Decision_TOS;   //!
   TBranch        *b_muminus_Hlt1DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_muminus_Hlt1DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_muminus_Hlt1DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_muminus_Hlt1DiMuonHighMassDecision_Dec;   //!
   TBranch        *b_muminus_Hlt1DiMuonHighMassDecision_TIS;   //!
   TBranch        *b_muminus_Hlt1DiMuonHighMassDecision_TOS;   //!
   TBranch        *b_muminus_Hlt1MB__Decision_Dec;   //!
   TBranch        *b_muminus_Hlt1MB__Decision_TIS;   //!
   TBranch        *b_muminus_Hlt1MB__Decision_TOS;   //!
   TBranch        *b_muminus_Hlt1TrackAllL0TightDecision_Dec;   //!
   TBranch        *b_muminus_Hlt1TrackAllL0TightDecision_TIS;   //!
   TBranch        *b_muminus_Hlt1TrackAllL0TightDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2SingleMuonLowPTDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2DiMuonDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2DiMuonDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2DiMuonDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2DiMuonLowMassDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2DiMuonLowMassDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2DiMuonLowMassDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2DiMuonJPsiDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2DiMuonJPsiDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2DiMuonJPsiDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2DiMuonJPsiHighPTDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2DiMuonJPsiHighPTDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2DiMuonJPsiHighPTDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2DiMuonPsi2SDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2DiMuonPsi2SDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2DiMuonPsi2SDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2DiMuonDetachedDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2DiMuonDetachedDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2DiMuonDetachedDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2DiMuonDetachedJPsiDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2DiMuonDetachedJPsiDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2DiMuonDetachedJPsiDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2DiMuonDetachedHeavyDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2DiMuonDetachedHeavyDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2DiMuonDetachedHeavyDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2TriMuonTauDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2TriMuonTauDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2TriMuonTauDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2B2HHDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2B2HHDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2B2HHDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2DiMuonBDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2DiMuonBDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2DiMuonBDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2DiMuonZDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2DiMuonZDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2DiMuonZDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2TopoMu2BodyBBDTDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2TopoMu2BodyBBDTDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2TopoMu2BodyBBDTDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2TopoMu3BodyBBDTDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2TopoMu3BodyBBDTDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2TopoMu3BodyBBDTDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2TopoMu4BodyBBDTDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2TopoMu4BodyBBDTDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2TopoMu4BodyBBDTDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2Topo2BodyBBDTDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2Topo2BodyBBDTDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2Topo2BodyBBDTDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2Topo3BodyBBDTDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2Topo3BodyBBDTDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2Topo3BodyBBDTDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2Topo4BodyBBDTDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2Topo4BodyBBDTDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2Topo4BodyBBDTDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2Topo2BodySimpleDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2Topo2BodySimpleDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2Topo2BodySimpleDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2Topo3BodySimpleDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2Topo3BodySimpleDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2Topo3BodySimpleDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2Topo4BodySimpleDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2Topo4BodySimpleDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2Topo4BodySimpleDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2PassThroughDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2PassThroughDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2PassThroughDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2TransparentDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2TransparentDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2TransparentDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2IncPhiDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2IncPhiDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2IncPhiDecision_TOS;   //!
   TBranch        *b_muminus_Hlt2DiMuonDY__Decision_Dec;   //!
   TBranch        *b_muminus_Hlt2DiMuonDY__Decision_TIS;   //!
   TBranch        *b_muminus_Hlt2DiMuonDY__Decision_TOS;   //!
   TBranch        *b_muminus_Hlt2TopoE__Decision_Dec;   //!
   TBranch        *b_muminus_Hlt2TopoE__Decision_TIS;   //!
   TBranch        *b_muminus_Hlt2TopoE__Decision_TOS;   //!
   TBranch        *b_muminus_Hlt2Topo__Decision_Dec;   //!
   TBranch        *b_muminus_Hlt2Topo__Decision_TIS;   //!
   TBranch        *b_muminus_Hlt2Topo__Decision_TOS;   //!
   TBranch        *b_muminus_Hlt2Charm__Decision_Dec;   //!
   TBranch        *b_muminus_Hlt2Charm__Decision_TIS;   //!
   TBranch        *b_muminus_Hlt2Charm__Decision_TOS;   //!
   TBranch        *b_muminus_Hlt2DiElectron__Decision_Dec;   //!
   TBranch        *b_muminus_Hlt2DiElectron__Decision_TIS;   //!
   TBranch        *b_muminus_Hlt2DiElectron__Decision_TOS;   //!
   TBranch        *b_muminus_Hlt2__GammaDecision_Dec;   //!
   TBranch        *b_muminus_Hlt2__GammaDecision_TIS;   //!
   TBranch        *b_muminus_Hlt2__GammaDecision_TOS;   //!
   TBranch        *b_muminus_TRACK_Type;   //!
   TBranch        *b_muminus_TRACK_Key;   //!
   TBranch        *b_muminus_TRACK_CHI2NDOF;   //!
   TBranch        *b_muminus_TRACK_PCHI2;   //!
   TBranch        *b_muminus_TRACK_MatchCHI2;   //!
   TBranch        *b_muminus_TRACK_GhostProb;   //!
   TBranch        *b_muminus_TRACK_CloneDist;   //!
   TBranch        *b_muminus_TRACK_Likelihood;   //!
   TBranch        *b_nCandidate;   //!
   TBranch        *b_totCandidates;   //!
   TBranch        *b_EventInSequence;   //!
   TBranch        *b_MCPVs;   //!
   TBranch        *b_MCPVX;   //!
   TBranch        *b_MCPVY;   //!
   TBranch        *b_MCPVZ;   //!
   TBranch        *b_MCPVT;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_BCID;   //!
   TBranch        *b_BCType;   //!
   TBranch        *b_OdinTCK;   //!
   TBranch        *b_L0DUTCK;   //!
   TBranch        *b_HLTTCK;   //!
   TBranch        *b_GpsTime;   //!
   TBranch        *b_Polarity;   //!
   TBranch        *b_Collisions;   //!
   TBranch        *b_ProcessType;   //!
   TBranch        *b_HeaviestQuark;   //!
   TBranch        *b_HeaviestQuarkInEvent;   //!
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

   addIso(TTree *tree=0);
   virtual ~addIso();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   //virtual void     Loop();
   virtual void     Loop(TString,TString,TString,TString,TString,int,TString,TString);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   void ComputeIsoBDTVars_new(int i_trk,int trk_type);

   vector<string> getBDTVars(TString,TString);
   std::vector<std::string>& split(const std::string&,char,std::vector<std::string>&);
   std::vector<std::string> split(const std::string &, char);
   void getMuonTrackIndex(int*);
   double getVal(TString var_name,int i_mu);
   double GetTrackPhi(int);
   double GetTrackEta(int);
   double ComputeIso(std::vector<double> iso1_vec,std::vector<double> iso2_vec,int flag);
   std::vector<double> Ordina(std::vector<double>);
   double ratio(double,double);

   //get_bips stuff
   //double get_bips(int i_trk,int trk_type);
   TMatrixD get_dFdv(TVectorD);
   TMatrixD get_dFdp(TVector3,TVector3);
   TMatrixDSym get_trkCov(int trk_id,int trk_type);
   void get_TrkIPSwrtBVtx(int trk_id,TVector3& vtx_pos,TMatrixD& vtx_Cov,double& chi2,int trk_type);
   bool _v;

   //US e VEL getVal(...) stuff
   void get_TRKminIP(int trk_id, int& pv_ip_id, int& pv_ips_id, double& trk_ip, double& trk_ips,int trk_type);
   void get_TrkIPSwrtPV(int trk_id,int pv_id,TVector3& vtx_pos,TMatrixD& vtx_Cov,double& chi2,int trk_type);
   TMatrixDSym get_PVCov(int pv_id);
   int _mup_id,_mum_id;
   double get_Doca(int trk_id,int mu_id,int trk_type);
   void get_fc_pvdis_svdis(int trk_id,int mu_id,int trk_type,double& fc,double& pvdis,double& svdis);
   void ComputeIsoBDTVars(int i_trk,int trk_type);
   void get_BminIP(int& minip_pv_id,int& minips_pv_id,double& ip,double& ips);
   void get_BIPwrtPV(int pv_id,double& ip,double& ips,double& fl,double& fl0,double& ctau);
   TVector3 get_Bpos();
   TVector3 get_Bmom();
   TMatrixDSym get_BCov();
   TMatrixD get_dFdq(TVectorD);

   double trkus_bips;
   double trkus_ip;
   double trkus_ips;
   double trkus_gho;
   double trkus_chi;
   double trkus_angle1;
   double trkus_doca1;
   double trkus_fc1;
   double trkus_svdis1;
   double trkus_pvdis1;
   double trkus_angle2;
   double trkus_doca2;
   double trkus_fc2;
   double trkus_svdis2;
   double trkus_pvdis2;
   double trkus_dphi1;
   double trkus_dphi2;
   double trkus_deta1;
   double trkus_deta2;
   double trkus_pt;
   double trkus_ch;
   double trkus_nnmu;
   double trkus_nnpi;
   double trkus_nnk;
   double trkus_ismuon;

   double trkvel_bips;
   double trkvel_ip;
   double trkvel_ips;
   double trkvel_gho;
   double trkvel_chi;
   double trkvel_angle1;
   double trkvel_doca1;
   double trkvel_fc1;
   double trkvel_svdis1;
   double trkvel_pvdis1;
   double trkvel_angle2;
   double trkvel_doca2;
   double trkvel_fc2;
   double trkvel_svdis2;
   double trkvel_pvdis2;
   double trkvel_dphi1;
   double trkvel_dphi2;
   double trkvel_deta1;
   double trkvel_deta2;


   int _jentry;
   double trk_bips;
   double trk_ip;
   double trk_ips;
   double trk_gho;
   double trk_chi;
   double trk_angle1;
   double trk_doca1;
   double trk_fc1;
   double trk_svdis1;
   double trk_pvdis1;
   double trk_angle2;
   double trk_doca2;
   double trk_fc2;
   double trk_svdis2;
   double trk_pvdis2;
   double trk_phi;
   double trk_dphi1;
   double trk_dphi2;
   double trk_eta;
   double trk_deta1;
   double trk_deta2;
   double trk_r;
   double trk_dr1;
   double trk_dr2;
   
   double trk_pt;
   double mu1_gho;
   double mu2_gho;
   double mu1_phi;
   double mu2_phi;
   int mu1_ch;
   int mu2_ch;
   double trk_ch;
   double trk_nnmu;
   double trk_nnpi;
   double trk_nnk;
   double trk_dllmu;
   double trk_dllk;
   double trk_ismuon;
   double trk_pvind;
   int trk_typ;
   double trk_clo;
   double trk_back;
};

#endif

#ifdef addIso_cxx
addIso::addIso(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
/*
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("bbbar2MuMuX_highpt_MC12_MagUp_selection.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("bbbar2MuMuX_highpt_MC12_MagUp_selection.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("bbbar2MuMuX_highpt_MC12_MagUp_selection.root:/B2HHTuple");
      dir->GetObject("DecayTree",tree);

   }
   Init(tree);
*/
}

addIso::~addIso()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t addIso::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t addIso::LoadTree(Long64_t entry)
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

void addIso::Init(TTree *tree)
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

   fChain->SetBranchAddress("B_BPVDIRA", &B_BPVDIRA, &b_B_BPVDIRA);
   fChain->SetBranchAddress("B_BPVIPCHI2", &B_BPVIPCHI2, &b_B_BPVIPCHI2);
   fChain->SetBranchAddress("B_BPVVDCHI2", &B_BPVVDCHI2, &b_B_BPVVDCHI2);
   fChain->SetBranchAddress("B_BPVVDZ", &B_BPVVDZ, &b_B_BPVVDZ);
   fChain->SetBranchAddress("B_DOCAMAX", &B_DOCAMAX, &b_B_DOCAMAX);
   fChain->SetBranchAddress("B_MINIPCHI2", &B_MINIPCHI2, &b_B_MINIPCHI2);
   fChain->SetBranchAddress("B_VFASPF", &B_VFASPF, &b_B_VFASPF);
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
   fChain->SetBranchAddress("B_ID", &B_ID, &b_B_ID);
   fChain->SetBranchAddress("B_eta", &B_eta, &b_B_eta);
   fChain->SetBranchAddress("B_phi", &B_phi, &b_B_phi);
   fChain->SetBranchAddress("B_D1_isolation_Giampi", &B_D1_isolation_Giampi, &b_B_D1_isolation_Giampi);
   fChain->SetBranchAddress("B_D2_isolation_Giampi", &B_D2_isolation_Giampi, &b_B_D2_isolation_Giampi);
   fChain->SetBranchAddress("B_D1_isolation_Giampi_tc", &B_D1_isolation_Giampi_tc, &b_B_D1_isolation_Giampi_tc);
   fChain->SetBranchAddress("B_D2_isolation_Giampi_tc", &B_D2_isolation_Giampi_tc, &b_B_D2_isolation_Giampi_tc);
   fChain->SetBranchAddress("B_D1_isolation_Giampi_new1", &B_D1_isolation_Giampi_new1, &b_B_D1_isolation_Giampi_new1);
   fChain->SetBranchAddress("B_D2_isolation_Giampi_new1", &B_D2_isolation_Giampi_new1, &b_B_D2_isolation_Giampi_new1);
   fChain->SetBranchAddress("B_D1_isolation_Giampi_new2", &B_D1_isolation_Giampi_new2, &b_B_D1_isolation_Giampi_new2);
   fChain->SetBranchAddress("B_D2_isolation_Giampi_new2", &B_D2_isolation_Giampi_new2, &b_B_D2_isolation_Giampi_new2);
   fChain->SetBranchAddress("B_D1_isolation_Giampi_newD0", &B_D1_isolation_Giampi_newD0, &b_B_D1_isolation_Giampi_newD0);
   fChain->SetBranchAddress("B_D2_isolation_Giampi_newD0", &B_D2_isolation_Giampi_newD0, &b_B_D2_isolation_Giampi_newD0);
   fChain->SetBranchAddress("B_yetanother_CDF_iso", &B_yetanother_CDF_iso, &b_B_yetanother_CDF_iso);
   fChain->SetBranchAddress("B_yetanother_CDF_iso_tc", &B_yetanother_CDF_iso_tc, &b_B_yetanother_CDF_iso_tc);
   fChain->SetBranchAddress("B_doca", &B_doca, &b_B_doca);
   fChain->SetBranchAddress("B_cosnk", &B_cosnk, &b_B_cosnk);
   fChain->SetBranchAddress("B_BDTS_BIPS", &B_BDTS_BIPS, &b_B_BDTS_BIPS);
   fChain->SetBranchAddress("B_BDTS_DOCA", &B_BDTS_DOCA, &b_B_BDTS_DOCA);
   fChain->SetBranchAddress("B_BDTS_VTXCHI2", &B_BDTS_VTXCHI2, &b_B_BDTS_VTXCHI2);
   fChain->SetBranchAddress("B_BDTS_DIRA", &B_BDTS_DIRA, &b_B_BDTS_DIRA);
   fChain->SetBranchAddress("B_BDTS_BIP", &B_BDTS_BIP, &b_B_BDTS_BIP);
   fChain->SetBranchAddress("B_BDTS_MuonMINIP", &B_BDTS_MuonMINIP, &b_B_BDTS_MuonMINIP);
   fChain->SetBranchAddress("B_BDTS", &B_BDTS, &b_B_BDTS);
   fChain->SetBranchAddress("B_CTAU_ps", &B_CTAU_ps, &b_B_CTAU_ps);
   fChain->SetBranchAddress("IsoSTIdx", &IsoSTIdx, &b_IsoSTIdx);
   fChain->SetBranchAddress("IsoST_trk_typ", IsoST_trk_typ, &b_IsoST_trk_typ);
   fChain->SetBranchAddress("IsoST_trk_chi", IsoST_trk_chi, &b_IsoST_trk_chi);
   fChain->SetBranchAddress("IsoST_trk_chg", IsoST_trk_chg, &b_IsoST_trk_chg);
   fChain->SetBranchAddress("IsoST_trk_pt", IsoST_trk_pt, &b_IsoST_trk_pt);
   fChain->SetBranchAddress("IsoST_trk_gho", IsoST_trk_gho, &b_IsoST_trk_gho);
   fChain->SetBranchAddress("IsoST_trk_clo", IsoST_trk_clo, &b_IsoST_trk_clo);
   fChain->SetBranchAddress("IsoST_trk_ips", IsoST_trk_ips, &b_IsoST_trk_ips);
   fChain->SetBranchAddress("IsoST_trk_hlt", IsoST_trk_hlt, &b_IsoST_trk_hlt);
   fChain->SetBranchAddress("IsoST_fim_angle", IsoST_fim_angle, &b_IsoST_fim_angle);
   fChain->SetBranchAddress("IsoST_fim_fc", IsoST_fim_fc, &b_IsoST_fim_fc);
   fChain->SetBranchAddress("IsoST_fim_doca", IsoST_fim_doca, &b_IsoST_fim_doca);
   fChain->SetBranchAddress("IsoST_fim_doca2", IsoST_fim_doca2, &b_IsoST_fim_doca2);
   fChain->SetBranchAddress("IsoST_fim_docachi2", IsoST_fim_docachi2, &b_IsoST_fim_docachi2);
   fChain->SetBranchAddress("IsoST_fim_svdis", IsoST_fim_svdis, &b_IsoST_fim_svdis);
   fChain->SetBranchAddress("IsoST_fim_pvdis", IsoST_fim_pvdis, &b_IsoST_fim_pvdis);
   fChain->SetBranchAddress("IsoST_fim_vtxx", IsoST_fim_vtxx, &b_IsoST_fim_vtxx);
   fChain->SetBranchAddress("IsoST_fim_vtxy", IsoST_fim_vtxy, &b_IsoST_fim_vtxy);
   fChain->SetBranchAddress("IsoST_fim_vtxz", IsoST_fim_vtxz, &b_IsoST_fim_vtxz);
   fChain->SetBranchAddress("IsoST_sem_angle", IsoST_sem_angle, &b_IsoST_sem_angle);
   fChain->SetBranchAddress("IsoST_sem_fc", IsoST_sem_fc, &b_IsoST_sem_fc);
   fChain->SetBranchAddress("IsoST_sem_doca", IsoST_sem_doca, &b_IsoST_sem_doca);
   fChain->SetBranchAddress("IsoST_sem_doca2", IsoST_sem_doca2, &b_IsoST_sem_doca2);
   fChain->SetBranchAddress("IsoST_sem_docachi2", IsoST_sem_docachi2, &b_IsoST_sem_docachi2);
   fChain->SetBranchAddress("IsoST_sem_svdis", IsoST_sem_svdis, &b_IsoST_sem_svdis);
   fChain->SetBranchAddress("IsoST_sem_pvdis", IsoST_sem_pvdis, &b_IsoST_sem_pvdis);
   fChain->SetBranchAddress("IsoST_sem_vtxx", IsoST_sem_vtxx, &b_IsoST_sem_vtxx);
   fChain->SetBranchAddress("IsoST_sem_vtxy", IsoST_sem_vtxy, &b_IsoST_sem_vtxy);
   fChain->SetBranchAddress("IsoST_sem_vtxz", IsoST_sem_vtxz, &b_IsoST_sem_vtxz);
   fChain->SetBranchAddress("B_D1_isobdt1_1st", &B_D1_isobdt1_1st, &b_B_D1_isobdt1_1st);
   fChain->SetBranchAddress("B_D1_isobdt1_2nd", &B_D1_isobdt1_2nd, &b_B_D1_isobdt1_2nd);
   fChain->SetBranchAddress("B_D1_isobdt1_3rd", &B_D1_isobdt1_3rd, &b_B_D1_isobdt1_3rd);
   fChain->SetBranchAddress("B_D2_isobdt1_1st", &B_D2_isobdt1_1st, &b_B_D2_isobdt1_1st);
   fChain->SetBranchAddress("B_D2_isobdt1_2nd", &B_D2_isobdt1_2nd, &b_B_D2_isobdt1_2nd);
   fChain->SetBranchAddress("B_D2_isobdt1_3rd", &B_D2_isobdt1_3rd, &b_B_D2_isobdt1_3rd);
   fChain->SetBranchAddress("B_D1_isobdt2_1st", &B_D1_isobdt2_1st, &b_B_D1_isobdt2_1st);
   fChain->SetBranchAddress("B_D1_isobdt2_2nd", &B_D1_isobdt2_2nd, &b_B_D1_isobdt2_2nd);
   fChain->SetBranchAddress("B_D1_isobdt2_3rd", &B_D1_isobdt2_3rd, &b_B_D1_isobdt2_3rd);
   fChain->SetBranchAddress("B_D2_isobdt2_1st", &B_D2_isobdt2_1st, &b_B_D2_isobdt2_1st);
   fChain->SetBranchAddress("B_D2_isobdt2_2nd", &B_D2_isobdt2_2nd, &b_B_D2_isobdt2_2nd);
   fChain->SetBranchAddress("B_D2_isobdt2_3rd", &B_D2_isobdt2_3rd, &b_B_D2_isobdt2_3rd);
   fChain->SetBranchAddress("B_D1_isobdt3_1st", &B_D1_isobdt3_1st, &b_B_D1_isobdt3_1st);
   fChain->SetBranchAddress("B_D1_isobdt3_2nd", &B_D1_isobdt3_2nd, &b_B_D1_isobdt3_2nd);
   fChain->SetBranchAddress("B_D1_isobdt3_3rd", &B_D1_isobdt3_3rd, &b_B_D1_isobdt3_3rd);
   fChain->SetBranchAddress("B_D2_isobdt3_1st", &B_D2_isobdt3_1st, &b_B_D2_isobdt3_1st);
   fChain->SetBranchAddress("B_D2_isobdt3_2nd", &B_D2_isobdt3_2nd, &b_B_D2_isobdt3_2nd);
   fChain->SetBranchAddress("B_D2_isobdt3_3rd", &B_D2_isobdt3_3rd, &b_B_D2_isobdt3_3rd);
   fChain->SetBranchAddress("B_D1_isobdt4_1st", &B_D1_isobdt4_1st, &b_B_D1_isobdt4_1st);
   fChain->SetBranchAddress("B_D1_isobdt4_2nd", &B_D1_isobdt4_2nd, &b_B_D1_isobdt4_2nd);
   fChain->SetBranchAddress("B_D1_isobdt4_3rd", &B_D1_isobdt4_3rd, &b_B_D1_isobdt4_3rd);
   fChain->SetBranchAddress("B_D2_isobdt4_1st", &B_D2_isobdt4_1st, &b_B_D2_isobdt4_1st);
   fChain->SetBranchAddress("B_D2_isobdt4_2nd", &B_D2_isobdt4_2nd, &b_B_D2_isobdt4_2nd);
   fChain->SetBranchAddress("B_D2_isobdt4_3rd", &B_D2_isobdt4_3rd, &b_B_D2_isobdt4_3rd);
   fChain->SetBranchAddress("B_CDFiso", &B_CDFiso, &b_B_CDFiso);
   fChain->SetBranchAddress("B_CDFiso_tc", &B_CDFiso_tc, &b_B_CDFiso_tc);
   fChain->SetBranchAddress("B_otherB_mag", &B_otherB_mag, &b_B_otherB_mag);
   fChain->SetBranchAddress("B_otherB_ang", &B_otherB_ang, &b_B_otherB_ang);
   fChain->SetBranchAddress("B_otherB_ntrk", &B_otherB_ntrk, &b_B_otherB_ntrk);
   fChain->SetBranchAddress("B_otherB_boo_mag", &B_otherB_boo_mag, &b_B_otherB_boo_mag);
   fChain->SetBranchAddress("B_otherB_boo_ang", &B_otherB_boo_ang, &b_B_otherB_boo_ang);
   fChain->SetBranchAddress("EVB_Nparts", &EVB_Nparts, &b_EVB_Nparts);
   fChain->SetBranchAddress("pbIdx", &pbIdx, &b_pbIdx);
   fChain->SetBranchAddress("EVB_par_pos_x", EVB_par_pos_x, &b_EVB_par_pos_x);
   fChain->SetBranchAddress("EVB_par_pos_y", EVB_par_pos_y, &b_EVB_par_pos_y);
   fChain->SetBranchAddress("EVB_par_pos_z", EVB_par_pos_z, &b_EVB_par_pos_z);
   fChain->SetBranchAddress("EVB_par_pos_covxx", EVB_par_pos_covxx, &b_EVB_par_pos_covxx);
   fChain->SetBranchAddress("EVB_par_pos_covyy", EVB_par_pos_covyy, &b_EVB_par_pos_covyy);
   fChain->SetBranchAddress("EVB_par_pos_covxy", EVB_par_pos_covxy, &b_EVB_par_pos_covxy);
   fChain->SetBranchAddress("EVB_par_fmpos_x", EVB_par_fmpos_x, &b_EVB_par_fmpos_x);
   fChain->SetBranchAddress("EVB_par_fmpos_y", EVB_par_fmpos_y, &b_EVB_par_fmpos_y);
   fChain->SetBranchAddress("EVB_par_fmpos_z", EVB_par_fmpos_z, &b_EVB_par_fmpos_z);
   fChain->SetBranchAddress("EVB_par_xp_cov00", EVB_par_xp_cov00, &b_EVB_par_xp_cov00);
   fChain->SetBranchAddress("EVB_par_xp_cov11", EVB_par_xp_cov11, &b_EVB_par_xp_cov11);
   fChain->SetBranchAddress("EVB_par_xp_cov22", EVB_par_xp_cov22, &b_EVB_par_xp_cov22);
   fChain->SetBranchAddress("EVB_par_xp_cov33", EVB_par_xp_cov33, &b_EVB_par_xp_cov33);
   fChain->SetBranchAddress("EVB_par_xp_cov44", EVB_par_xp_cov44, &b_EVB_par_xp_cov44);
   fChain->SetBranchAddress("EVB_par_xp_cov55", EVB_par_xp_cov55, &b_EVB_par_xp_cov55);
   fChain->SetBranchAddress("EVB_par_xp_cov01", EVB_par_xp_cov01, &b_EVB_par_xp_cov01);
   fChain->SetBranchAddress("EVB_par_xp_cov02", EVB_par_xp_cov02, &b_EVB_par_xp_cov02);
   fChain->SetBranchAddress("EVB_par_xp_cov12", EVB_par_xp_cov12, &b_EVB_par_xp_cov12);
   fChain->SetBranchAddress("EVB_par_xp_cov34", EVB_par_xp_cov34, &b_EVB_par_xp_cov34);
   fChain->SetBranchAddress("EVB_par_xp_cov35", EVB_par_xp_cov35, &b_EVB_par_xp_cov35);
   fChain->SetBranchAddress("EVB_par_xp_cov45", EVB_par_xp_cov45, &b_EVB_par_xp_cov45);
   fChain->SetBranchAddress("EVB_par_xp_cov03", EVB_par_xp_cov03, &b_EVB_par_xp_cov03);
   fChain->SetBranchAddress("EVB_par_xp_cov04", EVB_par_xp_cov04, &b_EVB_par_xp_cov04);
   fChain->SetBranchAddress("EVB_par_xp_cov05", EVB_par_xp_cov05, &b_EVB_par_xp_cov05);
   fChain->SetBranchAddress("EVB_par_xp_cov13", EVB_par_xp_cov13, &b_EVB_par_xp_cov13);
   fChain->SetBranchAddress("EVB_par_xp_cov14", EVB_par_xp_cov14, &b_EVB_par_xp_cov14);
   fChain->SetBranchAddress("EVB_par_xp_cov15", EVB_par_xp_cov15, &b_EVB_par_xp_cov15);
   fChain->SetBranchAddress("EVB_par_xp_cov23", EVB_par_xp_cov23, &b_EVB_par_xp_cov23);
   fChain->SetBranchAddress("EVB_par_xp_cov24", EVB_par_xp_cov24, &b_EVB_par_xp_cov24);
   fChain->SetBranchAddress("EVB_par_xp_cov25", EVB_par_xp_cov25, &b_EVB_par_xp_cov25);
   fChain->SetBranchAddress("EVB_par_px", EVB_par_px, &b_EVB_par_px);
   fChain->SetBranchAddress("EVB_par_py", EVB_par_py, &b_EVB_par_py);
   fChain->SetBranchAddress("EVB_par_pz", EVB_par_pz, &b_EVB_par_pz);
   fChain->SetBranchAddress("EVB_par_pt", EVB_par_pt, &b_EVB_par_pt);
   fChain->SetBranchAddress("EVB_par_p", EVB_par_p, &b_EVB_par_p);
   fChain->SetBranchAddress("EVB_par_chg", EVB_par_chg, &b_EVB_par_chg);
   fChain->SetBranchAddress("EVB_par_typ", EVB_par_typ, &b_EVB_par_typ);
   fChain->SetBranchAddress("EVB_par_gho", EVB_par_gho, &b_EVB_par_gho);
   fChain->SetBranchAddress("EVB_par_chi", EVB_par_chi, &b_EVB_par_chi);
   fChain->SetBranchAddress("EVB_par_clo", EVB_par_clo, &b_EVB_par_clo);
   fChain->SetBranchAddress("EVB_par_ip", EVB_par_ip, &b_EVB_par_ip);
   fChain->SetBranchAddress("EVB_par_ips", EVB_par_ips, &b_EVB_par_ips);
   fChain->SetBranchAddress("EVB_par_hlt", EVB_par_hlt, &b_EVB_par_hlt);
   fChain->SetBranchAddress("EVB_par_slope_covxx", EVB_par_slope_covxx, &b_EVB_par_slope_covxx);
   fChain->SetBranchAddress("EVB_par_slope_covyy", EVB_par_slope_covyy, &b_EVB_par_slope_covyy);
   fChain->SetBranchAddress("EVB_par_slope_covxy", EVB_par_slope_covxy, &b_EVB_par_slope_covxy);
   fChain->SetBranchAddress("EVB_par_NNe", EVB_par_NNe, &b_EVB_par_NNe);
   fChain->SetBranchAddress("EVB_par_NNmu", EVB_par_NNmu, &b_EVB_par_NNmu);
   fChain->SetBranchAddress("EVB_par_NNpi", EVB_par_NNpi, &b_EVB_par_NNpi);
   fChain->SetBranchAddress("EVB_par_NNk", EVB_par_NNk, &b_EVB_par_NNk);
   fChain->SetBranchAddress("EVB_par_NNp", EVB_par_NNp, &b_EVB_par_NNp);
   fChain->SetBranchAddress("EVB_par_NNghost", EVB_par_NNghost, &b_EVB_par_NNghost);
   fChain->SetBranchAddress("EVB_par_DLLe", EVB_par_DLLe, &b_EVB_par_DLLe);
   fChain->SetBranchAddress("EVB_par_DLLmu", EVB_par_DLLmu, &b_EVB_par_DLLmu);
   fChain->SetBranchAddress("EVB_par_DLLk", EVB_par_DLLk, &b_EVB_par_DLLk);
   fChain->SetBranchAddress("EVB_par_DLLp", EVB_par_DLLp, &b_EVB_par_DLLp);
   fChain->SetBranchAddress("EVB_par_isMuon", EVB_par_isMuon, &b_EVB_par_isMuon);
   fChain->SetBranchAddress("EVB_par_PVind", EVB_par_PVind, &b_EVB_par_PVind);
   fChain->SetBranchAddress("EVB_isMCMatched", EVB_isMCMatched, &b_EVB_isMCMatched);
   fChain->SetBranchAddress("EVB_true_Origin_ID", EVB_true_Origin_ID, &b_EVB_true_Origin_ID);
   fChain->SetBranchAddress("EVB_true_part_Ori_Vtx_x", EVB_true_part_Ori_Vtx_x, &b_EVB_true_part_Ori_Vtx_x);
   fChain->SetBranchAddress("EVB_true_part_Ori_Vtx_y", EVB_true_part_Ori_Vtx_y, &b_EVB_true_part_Ori_Vtx_y);
   fChain->SetBranchAddress("EVB_true_part_Ori_Vtx_z", EVB_true_part_Ori_Vtx_z, &b_EVB_true_part_Ori_Vtx_z);
   fChain->SetBranchAddress("EVB_true_part_Ori_type", EVB_true_part_Ori_type, &b_EVB_true_part_Ori_type);
   fChain->SetBranchAddress("EVB_true_part_ID", EVB_true_part_ID, &b_EVB_true_part_ID);
   fChain->SetBranchAddress("EVB_true_isnoniso_mup", EVB_true_isnoniso_mup, &b_EVB_true_isnoniso_mup);
   fChain->SetBranchAddress("EVB_true_isnoniso_mum", EVB_true_isnoniso_mum, &b_EVB_true_isnoniso_mum);
   fChain->SetBranchAddress("EVB_true_part_Px", EVB_true_part_Px, &b_EVB_true_part_Px);
   fChain->SetBranchAddress("EVB_true_part_Py", EVB_true_part_Py, &b_EVB_true_part_Py);
   fChain->SetBranchAddress("EVB_true_part_Pz", EVB_true_part_Pz, &b_EVB_true_part_Pz);
   fChain->SetBranchAddress("EVB_true_part_E", EVB_true_part_E, &b_EVB_true_part_E);
   fChain->SetBranchAddress("EVB_true_part_M", EVB_true_part_M, &b_EVB_true_part_M);
   fChain->SetBranchAddress("EVB_true_part_hasMother", EVB_true_part_hasMother, &b_EVB_true_part_hasMother);
   fChain->SetBranchAddress("EVB_true_moth_Ori_Vtx_x", EVB_true_moth_Ori_Vtx_x, &b_EVB_true_moth_Ori_Vtx_x);
   fChain->SetBranchAddress("EVB_true_moth_Ori_Vtx_y", EVB_true_moth_Ori_Vtx_y, &b_EVB_true_moth_Ori_Vtx_y);
   fChain->SetBranchAddress("EVB_true_moth_Ori_Vtx_z", EVB_true_moth_Ori_Vtx_z, &b_EVB_true_moth_Ori_Vtx_z);
   fChain->SetBranchAddress("EVB_true_moth_ID", EVB_true_moth_ID, &b_EVB_true_moth_ID);
   fChain->SetBranchAddress("EVB_true_moth_Px", EVB_true_moth_Px, &b_EVB_true_moth_Px);
   fChain->SetBranchAddress("EVB_true_moth_Py", EVB_true_moth_Py, &b_EVB_true_moth_Py);
   fChain->SetBranchAddress("EVB_true_moth_Pz", EVB_true_moth_Pz, &b_EVB_true_moth_Pz);
   fChain->SetBranchAddress("EVB_true_moth_E", EVB_true_moth_E, &b_EVB_true_moth_E);
   fChain->SetBranchAddress("EVB_true_moth_M", EVB_true_moth_M, &b_EVB_true_moth_M);
   fChain->SetBranchAddress("EVB_true_moth_hasMother", EVB_true_moth_hasMother, &b_EVB_true_moth_hasMother);
   fChain->SetBranchAddress("EVB_true_gran_Ori_Vtx_x", EVB_true_gran_Ori_Vtx_x, &b_EVB_true_gran_Ori_Vtx_x);
   fChain->SetBranchAddress("EVB_true_gran_Ori_Vtx_y", EVB_true_gran_Ori_Vtx_y, &b_EVB_true_gran_Ori_Vtx_y);
   fChain->SetBranchAddress("EVB_true_gran_Ori_Vtx_z", EVB_true_gran_Ori_Vtx_z, &b_EVB_true_gran_Ori_Vtx_z);
   fChain->SetBranchAddress("EVB_true_gran_ID", EVB_true_gran_ID, &b_EVB_true_gran_ID);
   fChain->SetBranchAddress("EVB_true_gran_Px", EVB_true_gran_Px, &b_EVB_true_gran_Px);
   fChain->SetBranchAddress("EVB_true_gran_Py", EVB_true_gran_Py, &b_EVB_true_gran_Py);
   fChain->SetBranchAddress("EVB_true_gran_Pz", EVB_true_gran_Pz, &b_EVB_true_gran_Pz);
   fChain->SetBranchAddress("EVB_true_gran_E", EVB_true_gran_E, &b_EVB_true_gran_E);
   fChain->SetBranchAddress("EVB_true_gran_M", EVB_true_gran_M, &b_EVB_true_gran_M);
   fChain->SetBranchAddress("EVB_true_gran_hasMother", EVB_true_gran_hasMother, &b_EVB_true_gran_hasMother);
   fChain->SetBranchAddress("EVB_true_mogr_Ori_Vtx_x", EVB_true_mogr_Ori_Vtx_x, &b_EVB_true_mogr_Ori_Vtx_x);
   fChain->SetBranchAddress("EVB_true_mogr_Ori_Vtx_y", EVB_true_mogr_Ori_Vtx_y, &b_EVB_true_mogr_Ori_Vtx_y);
   fChain->SetBranchAddress("EVB_true_mogr_Ori_Vtx_z", EVB_true_mogr_Ori_Vtx_z, &b_EVB_true_mogr_Ori_Vtx_z);
   fChain->SetBranchAddress("EVB_true_mogr_ID", EVB_true_mogr_ID, &b_EVB_true_mogr_ID);
   fChain->SetBranchAddress("EVB_true_mogr_Px", EVB_true_mogr_Px, &b_EVB_true_mogr_Px);
   fChain->SetBranchAddress("EVB_true_mogr_Py", EVB_true_mogr_Py, &b_EVB_true_mogr_Py);
   fChain->SetBranchAddress("EVB_true_mogr_Pz", EVB_true_mogr_Pz, &b_EVB_true_mogr_Pz);
   fChain->SetBranchAddress("EVB_true_mogr_E", EVB_true_mogr_E, &b_EVB_true_mogr_E);
   fChain->SetBranchAddress("EVB_true_mogr_M", EVB_true_mogr_M, &b_EVB_true_mogr_M);
   fChain->SetBranchAddress("EVB_true_mogr_hasMother", EVB_true_mogr_hasMother, &b_EVB_true_mogr_hasMother);
   fChain->SetBranchAddress("EVB_true_grgr_Ori_Vtx_x", EVB_true_grgr_Ori_Vtx_x, &b_EVB_true_grgr_Ori_Vtx_x);
   fChain->SetBranchAddress("EVB_true_grgr_Ori_Vtx_y", EVB_true_grgr_Ori_Vtx_y, &b_EVB_true_grgr_Ori_Vtx_y);
   fChain->SetBranchAddress("EVB_true_grgr_Ori_Vtx_z", EVB_true_grgr_Ori_Vtx_z, &b_EVB_true_grgr_Ori_Vtx_z);
   fChain->SetBranchAddress("EVB_true_grgr_ID", EVB_true_grgr_ID, &b_EVB_true_grgr_ID);
   fChain->SetBranchAddress("EVB_true_grgr_Px", EVB_true_grgr_Px, &b_EVB_true_grgr_Px);
   fChain->SetBranchAddress("EVB_true_grgr_Py", EVB_true_grgr_Py, &b_EVB_true_grgr_Py);
   fChain->SetBranchAddress("EVB_true_grgr_Pz", EVB_true_grgr_Pz, &b_EVB_true_grgr_Pz);
   fChain->SetBranchAddress("EVB_true_grgr_E", EVB_true_grgr_E, &b_EVB_true_grgr_E);
   fChain->SetBranchAddress("EVB_true_grgr_M", EVB_true_grgr_M, &b_EVB_true_grgr_M);
   fChain->SetBranchAddress("PV_num", &PV_num, &b_PV_num);
   fChain->SetBranchAddress("PV_x", PV_x, &b_PV_x);
   fChain->SetBranchAddress("PV_y", PV_y, &b_PV_y);
   fChain->SetBranchAddress("PV_z", PV_z, &b_PV_z);
   fChain->SetBranchAddress("PV_covxx", PV_covxx, &b_PV_covxx);
   fChain->SetBranchAddress("PV_covyy", PV_covyy, &b_PV_covyy);
   fChain->SetBranchAddress("PV_covzz", PV_covzz, &b_PV_covzz);
   fChain->SetBranchAddress("PV_covxy", PV_covxy, &b_PV_covxy);
   fChain->SetBranchAddress("PV_covxz", PV_covxz, &b_PV_covxz);
   fChain->SetBranchAddress("PV_covyz", PV_covyz, &b_PV_covyz);
   fChain->SetBranchAddress("PV_chi2PerDoF", PV_chi2PerDoF, &b_PV_chi2PerDoF);
   fChain->SetBranchAddress("PV_nDoF", PV_nDoF, &b_PV_nDoF);
   fChain->SetBranchAddress("PV_ntrk", PV_ntrk, &b_PV_ntrk);
   fChain->SetBranchAddress("PV2_num", &PV2_num, &b_PV2_num);
   fChain->SetBranchAddress("PV2_x", PV2_x, &b_PV2_x);
   fChain->SetBranchAddress("PV2_y", PV2_y, &b_PV2_y);
   fChain->SetBranchAddress("PV2_z", PV2_z, &b_PV2_z);
   fChain->SetBranchAddress("PV2_covxx", PV2_covxx, &b_PV2_covxx);
   fChain->SetBranchAddress("PV2_covyy", PV2_covyy, &b_PV2_covyy);
   fChain->SetBranchAddress("PV2_covzz", PV2_covzz, &b_PV2_covzz);
   fChain->SetBranchAddress("PV2_covxy", PV2_covxy, &b_PV2_covxy);
   fChain->SetBranchAddress("PV2_covxz", PV2_covxz, &b_PV2_covxz);
   fChain->SetBranchAddress("PV2_covyz", PV2_covyz, &b_PV2_covyz);
   fChain->SetBranchAddress("PV2_chi2PerDoF", PV2_chi2PerDoF, &b_PV2_chi2PerDoF);
   fChain->SetBranchAddress("PV2_nDoF", PV2_nDoF, &b_PV2_nDoF);
   fChain->SetBranchAddress("PV2_ntrk", PV2_ntrk, &b_PV2_ntrk);
   fChain->SetBranchAddress("B_cov00", &B_cov00, &b_B_cov00);
   fChain->SetBranchAddress("B_cov01", &B_cov01, &b_B_cov01);
   fChain->SetBranchAddress("B_cov02", &B_cov02, &b_B_cov02);
   fChain->SetBranchAddress("B_cov03", &B_cov03, &b_B_cov03);
   fChain->SetBranchAddress("B_cov04", &B_cov04, &b_B_cov04);
   fChain->SetBranchAddress("B_cov05", &B_cov05, &b_B_cov05);
   fChain->SetBranchAddress("B_cov06", &B_cov06, &b_B_cov06);
   fChain->SetBranchAddress("B_cov11", &B_cov11, &b_B_cov11);
   fChain->SetBranchAddress("B_cov12", &B_cov12, &b_B_cov12);
   fChain->SetBranchAddress("B_cov13", &B_cov13, &b_B_cov13);
   fChain->SetBranchAddress("B_cov14", &B_cov14, &b_B_cov14);
   fChain->SetBranchAddress("B_cov15", &B_cov15, &b_B_cov15);
   fChain->SetBranchAddress("B_cov16", &B_cov16, &b_B_cov16);
   fChain->SetBranchAddress("B_cov22", &B_cov22, &b_B_cov22);
   fChain->SetBranchAddress("B_cov23", &B_cov23, &b_B_cov23);
   fChain->SetBranchAddress("B_cov24", &B_cov24, &b_B_cov24);
   fChain->SetBranchAddress("B_cov25", &B_cov25, &b_B_cov25);
   fChain->SetBranchAddress("B_cov26", &B_cov26, &b_B_cov26);
   fChain->SetBranchAddress("B_cov33", &B_cov33, &b_B_cov33);
   fChain->SetBranchAddress("B_cov34", &B_cov34, &b_B_cov34);
   fChain->SetBranchAddress("B_cov35", &B_cov35, &b_B_cov35);
   fChain->SetBranchAddress("B_cov36", &B_cov36, &b_B_cov36);
   fChain->SetBranchAddress("B_cov44", &B_cov44, &b_B_cov44);
   fChain->SetBranchAddress("B_cov45", &B_cov45, &b_B_cov45);
   fChain->SetBranchAddress("B_cov46", &B_cov46, &b_B_cov46);
   fChain->SetBranchAddress("B_cov55", &B_cov55, &b_B_cov55);
   fChain->SetBranchAddress("B_cov56", &B_cov56, &b_B_cov56);
   fChain->SetBranchAddress("B_cov66", &B_cov66, &b_B_cov66);
   fChain->SetBranchAddress("VEL_num", &VEL_num, &b_VEL_num);
   fChain->SetBranchAddress("VEL_par_pos_x", VEL_par_pos_x, &b_VEL_par_pos_x);
   fChain->SetBranchAddress("VEL_par_pos_y", VEL_par_pos_y, &b_VEL_par_pos_y);
   fChain->SetBranchAddress("VEL_par_pos_z", VEL_par_pos_z, &b_VEL_par_pos_z);
   fChain->SetBranchAddress("VEL_par_fmpos_x", VEL_par_fmpos_x, &b_VEL_par_fmpos_x);
   fChain->SetBranchAddress("VEL_par_fmpos_y", VEL_par_fmpos_y, &b_VEL_par_fmpos_y);
   fChain->SetBranchAddress("VEL_par_fmpos_z", VEL_par_fmpos_z, &b_VEL_par_fmpos_z);
   fChain->SetBranchAddress("VEL_par_xp_cov00", VEL_par_xp_cov00, &b_VEL_par_xp_cov00);
   fChain->SetBranchAddress("VEL_par_xp_cov11", VEL_par_xp_cov11, &b_VEL_par_xp_cov11);
   fChain->SetBranchAddress("VEL_par_xp_cov22", VEL_par_xp_cov22, &b_VEL_par_xp_cov22);
   fChain->SetBranchAddress("VEL_par_xp_cov33", VEL_par_xp_cov33, &b_VEL_par_xp_cov33);
   fChain->SetBranchAddress("VEL_par_xp_cov44", VEL_par_xp_cov44, &b_VEL_par_xp_cov44);
   fChain->SetBranchAddress("VEL_par_xp_cov55", VEL_par_xp_cov55, &b_VEL_par_xp_cov55);
   fChain->SetBranchAddress("VEL_par_xp_cov01", VEL_par_xp_cov01, &b_VEL_par_xp_cov01);
   fChain->SetBranchAddress("VEL_par_xp_cov02", VEL_par_xp_cov02, &b_VEL_par_xp_cov02);
   fChain->SetBranchAddress("VEL_par_xp_cov12", VEL_par_xp_cov12, &b_VEL_par_xp_cov12);
   fChain->SetBranchAddress("VEL_par_xp_cov34", VEL_par_xp_cov34, &b_VEL_par_xp_cov34);
   fChain->SetBranchAddress("VEL_par_xp_cov35", VEL_par_xp_cov35, &b_VEL_par_xp_cov35);
   fChain->SetBranchAddress("VEL_par_xp_cov45", VEL_par_xp_cov45, &b_VEL_par_xp_cov45);
   fChain->SetBranchAddress("VEL_par_xp_cov03", VEL_par_xp_cov03, &b_VEL_par_xp_cov03);
   fChain->SetBranchAddress("VEL_par_xp_cov04", VEL_par_xp_cov04, &b_VEL_par_xp_cov04);
   fChain->SetBranchAddress("VEL_par_xp_cov05", VEL_par_xp_cov05, &b_VEL_par_xp_cov05);
   fChain->SetBranchAddress("VEL_par_xp_cov13", VEL_par_xp_cov13, &b_VEL_par_xp_cov13);
   fChain->SetBranchAddress("VEL_par_xp_cov14", VEL_par_xp_cov14, &b_VEL_par_xp_cov14);
   fChain->SetBranchAddress("VEL_par_xp_cov15", VEL_par_xp_cov15, &b_VEL_par_xp_cov15);
   fChain->SetBranchAddress("VEL_par_xp_cov23", VEL_par_xp_cov23, &b_VEL_par_xp_cov23);
   fChain->SetBranchAddress("VEL_par_xp_cov24", VEL_par_xp_cov24, &b_VEL_par_xp_cov24);
   fChain->SetBranchAddress("VEL_par_xp_cov25", VEL_par_xp_cov25, &b_VEL_par_xp_cov25);
   fChain->SetBranchAddress("VEL_par_px", VEL_par_px, &b_VEL_par_px);
   fChain->SetBranchAddress("VEL_par_py", VEL_par_py, &b_VEL_par_py);
   fChain->SetBranchAddress("VEL_par_pz", VEL_par_pz, &b_VEL_par_pz);
   fChain->SetBranchAddress("VEL_par_pt", VEL_par_pt, &b_VEL_par_pt);
   fChain->SetBranchAddress("VEL_par_p", VEL_par_p, &b_VEL_par_p);
   fChain->SetBranchAddress("VEL_par_chg", VEL_par_chg, &b_VEL_par_chg);
   fChain->SetBranchAddress("VEL_par_slope_covxx", VEL_par_slope_covxx, &b_VEL_par_slope_covxx);
   fChain->SetBranchAddress("VEL_par_slope_covyy", VEL_par_slope_covyy, &b_VEL_par_slope_covyy);
   fChain->SetBranchAddress("VEL_par_slope_covxy", VEL_par_slope_covxy, &b_VEL_par_slope_covxy);
   fChain->SetBranchAddress("VEL_par_back", VEL_par_back, &b_VEL_par_back);
   fChain->SetBranchAddress("VEL_par_typ", VEL_par_typ, &b_VEL_par_typ);
   fChain->SetBranchAddress("VEL_par_gho", VEL_par_gho, &b_VEL_par_gho);
   fChain->SetBranchAddress("VEL_par_chi", VEL_par_chi, &b_VEL_par_chi);
   fChain->SetBranchAddress("VEL_par_clo", VEL_par_clo, &b_VEL_par_clo);
   fChain->SetBranchAddress("VEL_par_PVind", VEL_par_PVind, &b_VEL_par_PVind);
   fChain->SetBranchAddress("VEL_isMCMatched", VEL_isMCMatched, &b_VEL_isMCMatched);
   fChain->SetBranchAddress("VEL_true_Origin_ID", VEL_true_Origin_ID, &b_VEL_true_Origin_ID);
   fChain->SetBranchAddress("VEL_true_part_Ori_Vtx_x", VEL_true_part_Ori_Vtx_x, &b_VEL_true_part_Ori_Vtx_x);
   fChain->SetBranchAddress("VEL_true_part_Ori_Vtx_y", VEL_true_part_Ori_Vtx_y, &b_VEL_true_part_Ori_Vtx_y);
   fChain->SetBranchAddress("VEL_true_part_Ori_Vtx_z", VEL_true_part_Ori_Vtx_z, &b_VEL_true_part_Ori_Vtx_z);
   fChain->SetBranchAddress("VEL_true_part_Ori_type", VEL_true_part_Ori_type, &b_VEL_true_part_Ori_type);
   fChain->SetBranchAddress("VEL_true_part_ID", VEL_true_part_ID, &b_VEL_true_part_ID);
   fChain->SetBranchAddress("VEL_true_isnoniso_mup", VEL_true_isnoniso_mup, &b_VEL_true_isnoniso_mup);
   fChain->SetBranchAddress("VEL_true_isnoniso_mum", VEL_true_isnoniso_mum, &b_VEL_true_isnoniso_mum);
   fChain->SetBranchAddress("VEL_true_part_Px", VEL_true_part_Px, &b_VEL_true_part_Px);
   fChain->SetBranchAddress("VEL_true_part_Py", VEL_true_part_Py, &b_VEL_true_part_Py);
   fChain->SetBranchAddress("VEL_true_part_Pz", VEL_true_part_Pz, &b_VEL_true_part_Pz);
   fChain->SetBranchAddress("VEL_true_part_E", VEL_true_part_E, &b_VEL_true_part_E);
   fChain->SetBranchAddress("VEL_true_part_M", VEL_true_part_M, &b_VEL_true_part_M);
   fChain->SetBranchAddress("VEL_true_part_hasMother", VEL_true_part_hasMother, &b_VEL_true_part_hasMother);
   fChain->SetBranchAddress("VEL_true_moth_Ori_Vtx_x", VEL_true_moth_Ori_Vtx_x, &b_VEL_true_moth_Ori_Vtx_x);
   fChain->SetBranchAddress("VEL_true_moth_Ori_Vtx_y", VEL_true_moth_Ori_Vtx_y, &b_VEL_true_moth_Ori_Vtx_y);
   fChain->SetBranchAddress("VEL_true_moth_Ori_Vtx_z", VEL_true_moth_Ori_Vtx_z, &b_VEL_true_moth_Ori_Vtx_z);
   fChain->SetBranchAddress("VEL_true_moth_ID", VEL_true_moth_ID, &b_VEL_true_moth_ID);
   fChain->SetBranchAddress("VEL_true_moth_Px", VEL_true_moth_Px, &b_VEL_true_moth_Px);
   fChain->SetBranchAddress("VEL_true_moth_Py", VEL_true_moth_Py, &b_VEL_true_moth_Py);
   fChain->SetBranchAddress("VEL_true_moth_Pz", VEL_true_moth_Pz, &b_VEL_true_moth_Pz);
   fChain->SetBranchAddress("VEL_true_moth_E", VEL_true_moth_E, &b_VEL_true_moth_E);
   fChain->SetBranchAddress("VEL_true_moth_M", VEL_true_moth_M, &b_VEL_true_moth_M);
   fChain->SetBranchAddress("VEL_true_moth_hasMother", VEL_true_moth_hasMother, &b_VEL_true_moth_hasMother);
   fChain->SetBranchAddress("VEL_true_gran_Ori_Vtx_x", VEL_true_gran_Ori_Vtx_x, &b_VEL_true_gran_Ori_Vtx_x);
   fChain->SetBranchAddress("VEL_true_gran_Ori_Vtx_y", VEL_true_gran_Ori_Vtx_y, &b_VEL_true_gran_Ori_Vtx_y);
   fChain->SetBranchAddress("VEL_true_gran_Ori_Vtx_z", VEL_true_gran_Ori_Vtx_z, &b_VEL_true_gran_Ori_Vtx_z);
   fChain->SetBranchAddress("VEL_true_gran_ID", VEL_true_gran_ID, &b_VEL_true_gran_ID);
   fChain->SetBranchAddress("VEL_true_gran_Px", VEL_true_gran_Px, &b_VEL_true_gran_Px);
   fChain->SetBranchAddress("VEL_true_gran_Py", VEL_true_gran_Py, &b_VEL_true_gran_Py);
   fChain->SetBranchAddress("VEL_true_gran_Pz", VEL_true_gran_Pz, &b_VEL_true_gran_Pz);
   fChain->SetBranchAddress("VEL_true_gran_E", VEL_true_gran_E, &b_VEL_true_gran_E);
   fChain->SetBranchAddress("VEL_true_gran_M", VEL_true_gran_M, &b_VEL_true_gran_M);
   fChain->SetBranchAddress("VEL_true_gran_hasMother", VEL_true_gran_hasMother, &b_VEL_true_gran_hasMother);
   fChain->SetBranchAddress("VEL_true_mogr_Ori_Vtx_x", VEL_true_mogr_Ori_Vtx_x, &b_VEL_true_mogr_Ori_Vtx_x);
   fChain->SetBranchAddress("VEL_true_mogr_Ori_Vtx_y", VEL_true_mogr_Ori_Vtx_y, &b_VEL_true_mogr_Ori_Vtx_y);
   fChain->SetBranchAddress("VEL_true_mogr_Ori_Vtx_z", VEL_true_mogr_Ori_Vtx_z, &b_VEL_true_mogr_Ori_Vtx_z);
   fChain->SetBranchAddress("VEL_true_mogr_ID", VEL_true_mogr_ID, &b_VEL_true_mogr_ID);
   fChain->SetBranchAddress("VEL_true_mogr_Px", VEL_true_mogr_Px, &b_VEL_true_mogr_Px);
   fChain->SetBranchAddress("VEL_true_mogr_Py", VEL_true_mogr_Py, &b_VEL_true_mogr_Py);
   fChain->SetBranchAddress("VEL_true_mogr_Pz", VEL_true_mogr_Pz, &b_VEL_true_mogr_Pz);
   fChain->SetBranchAddress("VEL_true_mogr_E", VEL_true_mogr_E, &b_VEL_true_mogr_E);
   fChain->SetBranchAddress("VEL_true_mogr_M", VEL_true_mogr_M, &b_VEL_true_mogr_M);
   fChain->SetBranchAddress("VEL_true_mogr_hasMother", VEL_true_mogr_hasMother, &b_VEL_true_mogr_hasMother);
   fChain->SetBranchAddress("VEL_true_grgr_Ori_Vtx_x", VEL_true_grgr_Ori_Vtx_x, &b_VEL_true_grgr_Ori_Vtx_x);
   fChain->SetBranchAddress("VEL_true_grgr_Ori_Vtx_y", VEL_true_grgr_Ori_Vtx_y, &b_VEL_true_grgr_Ori_Vtx_y);
   fChain->SetBranchAddress("VEL_true_grgr_Ori_Vtx_z", VEL_true_grgr_Ori_Vtx_z, &b_VEL_true_grgr_Ori_Vtx_z);
   fChain->SetBranchAddress("VEL_true_grgr_ID", VEL_true_grgr_ID, &b_VEL_true_grgr_ID);
   fChain->SetBranchAddress("VEL_true_grgr_Px", VEL_true_grgr_Px, &b_VEL_true_grgr_Px);
   fChain->SetBranchAddress("VEL_true_grgr_Py", VEL_true_grgr_Py, &b_VEL_true_grgr_Py);
   fChain->SetBranchAddress("VEL_true_grgr_Pz", VEL_true_grgr_Pz, &b_VEL_true_grgr_Pz);
   fChain->SetBranchAddress("VEL_true_grgr_E", VEL_true_grgr_E, &b_VEL_true_grgr_E);
   fChain->SetBranchAddress("VEL_true_grgr_M", VEL_true_grgr_M, &b_VEL_true_grgr_M);
   fChain->SetBranchAddress("US_num", &US_num, &b_US_num);
   fChain->SetBranchAddress("US_par_pos_x", US_par_pos_x, &b_US_par_pos_x);
   fChain->SetBranchAddress("US_par_pos_y", US_par_pos_y, &b_US_par_pos_y);
   fChain->SetBranchAddress("US_par_pos_z", US_par_pos_z, &b_US_par_pos_z);
   fChain->SetBranchAddress("US_par_fmpos_x", US_par_fmpos_x, &b_US_par_fmpos_x);
   fChain->SetBranchAddress("US_par_fmpos_y", US_par_fmpos_y, &b_US_par_fmpos_y);
   fChain->SetBranchAddress("US_par_fmpos_z", US_par_fmpos_z, &b_US_par_fmpos_z);
   fChain->SetBranchAddress("US_par_xp_cov00", US_par_xp_cov00, &b_US_par_xp_cov00);
   fChain->SetBranchAddress("US_par_xp_cov11", US_par_xp_cov11, &b_US_par_xp_cov11);
   fChain->SetBranchAddress("US_par_xp_cov22", US_par_xp_cov22, &b_US_par_xp_cov22);
   fChain->SetBranchAddress("US_par_xp_cov33", US_par_xp_cov33, &b_US_par_xp_cov33);
   fChain->SetBranchAddress("US_par_xp_cov44", US_par_xp_cov44, &b_US_par_xp_cov44);
   fChain->SetBranchAddress("US_par_xp_cov55", US_par_xp_cov55, &b_US_par_xp_cov55);
   fChain->SetBranchAddress("US_par_xp_cov01", US_par_xp_cov01, &b_US_par_xp_cov01);
   fChain->SetBranchAddress("US_par_xp_cov02", US_par_xp_cov02, &b_US_par_xp_cov02);
   fChain->SetBranchAddress("US_par_xp_cov12", US_par_xp_cov12, &b_US_par_xp_cov12);
   fChain->SetBranchAddress("US_par_xp_cov34", US_par_xp_cov34, &b_US_par_xp_cov34);
   fChain->SetBranchAddress("US_par_xp_cov35", US_par_xp_cov35, &b_US_par_xp_cov35);
   fChain->SetBranchAddress("US_par_xp_cov45", US_par_xp_cov45, &b_US_par_xp_cov45);
   fChain->SetBranchAddress("US_par_xp_cov03", US_par_xp_cov03, &b_US_par_xp_cov03);
   fChain->SetBranchAddress("US_par_xp_cov04", US_par_xp_cov04, &b_US_par_xp_cov04);
   fChain->SetBranchAddress("US_par_xp_cov05", US_par_xp_cov05, &b_US_par_xp_cov05);
   fChain->SetBranchAddress("US_par_xp_cov13", US_par_xp_cov13, &b_US_par_xp_cov13);
   fChain->SetBranchAddress("US_par_xp_cov14", US_par_xp_cov14, &b_US_par_xp_cov14);
   fChain->SetBranchAddress("US_par_xp_cov15", US_par_xp_cov15, &b_US_par_xp_cov15);
   fChain->SetBranchAddress("US_par_xp_cov23", US_par_xp_cov23, &b_US_par_xp_cov23);
   fChain->SetBranchAddress("US_par_xp_cov24", US_par_xp_cov24, &b_US_par_xp_cov24);
   fChain->SetBranchAddress("US_par_xp_cov25", US_par_xp_cov25, &b_US_par_xp_cov25);
   fChain->SetBranchAddress("US_par_px", US_par_px, &b_US_par_px);
   fChain->SetBranchAddress("US_par_py", US_par_py, &b_US_par_py);
   fChain->SetBranchAddress("US_par_pz", US_par_pz, &b_US_par_pz);
   fChain->SetBranchAddress("US_par_pt", US_par_pt, &b_US_par_pt);
   fChain->SetBranchAddress("US_par_p", US_par_p, &b_US_par_p);
   fChain->SetBranchAddress("US_par_chg", US_par_chg, &b_US_par_chg);
   fChain->SetBranchAddress("US_par_slope_covxx", US_par_slope_covxx, &b_US_par_slope_covxx);
   fChain->SetBranchAddress("US_par_slope_covyy", US_par_slope_covyy, &b_US_par_slope_covyy);
   fChain->SetBranchAddress("US_par_slope_covxy", US_par_slope_covxy, &b_US_par_slope_covxy);
   fChain->SetBranchAddress("US_par_typ", US_par_typ, &b_US_par_typ);
   fChain->SetBranchAddress("US_par_gho", US_par_gho, &b_US_par_gho);
   fChain->SetBranchAddress("US_par_chi", US_par_chi, &b_US_par_chi);
   fChain->SetBranchAddress("US_par_clo", US_par_clo, &b_US_par_clo);
   fChain->SetBranchAddress("US_par_NNe", US_par_NNe, &b_US_par_NNe);
   fChain->SetBranchAddress("US_par_NNmu", US_par_NNmu, &b_US_par_NNmu);
   fChain->SetBranchAddress("US_par_NNpi", US_par_NNpi, &b_US_par_NNpi);
   fChain->SetBranchAddress("US_par_NNk", US_par_NNk, &b_US_par_NNk);
   fChain->SetBranchAddress("US_par_NNp", US_par_NNp, &b_US_par_NNp);
   fChain->SetBranchAddress("US_par_NNghost", US_par_NNghost, &b_US_par_NNghost);
   fChain->SetBranchAddress("US_par_DLLe", US_par_DLLe, &b_US_par_DLLe);
   fChain->SetBranchAddress("US_par_DLLmu", US_par_DLLmu, &b_US_par_DLLmu);
   fChain->SetBranchAddress("US_par_DLLk", US_par_DLLk, &b_US_par_DLLk);
   fChain->SetBranchAddress("US_par_DLLp", US_par_DLLp, &b_US_par_DLLp);
   fChain->SetBranchAddress("US_par_isMuon", US_par_isMuon, &b_US_par_isMuon);
   fChain->SetBranchAddress("US_par_PVind", US_par_PVind, &b_US_par_PVind);
   fChain->SetBranchAddress("US_isMCMatched", US_isMCMatched, &b_US_isMCMatched);
   fChain->SetBranchAddress("US_true_Origin_ID", US_true_Origin_ID, &b_US_true_Origin_ID);
   fChain->SetBranchAddress("US_true_part_Ori_Vtx_x", US_true_part_Ori_Vtx_x, &b_US_true_part_Ori_Vtx_x);
   fChain->SetBranchAddress("US_true_part_Ori_Vtx_y", US_true_part_Ori_Vtx_y, &b_US_true_part_Ori_Vtx_y);
   fChain->SetBranchAddress("US_true_part_Ori_Vtx_z", US_true_part_Ori_Vtx_z, &b_US_true_part_Ori_Vtx_z);
   fChain->SetBranchAddress("US_true_part_Ori_type", US_true_part_Ori_type, &b_US_true_part_Ori_type);
   fChain->SetBranchAddress("US_true_part_ID", US_true_part_ID, &b_US_true_part_ID);
   fChain->SetBranchAddress("US_true_isnoniso_mup", US_true_isnoniso_mup, &b_US_true_isnoniso_mup);
   fChain->SetBranchAddress("US_true_isnoniso_mum", US_true_isnoniso_mum, &b_US_true_isnoniso_mum);
   fChain->SetBranchAddress("US_true_part_Px", US_true_part_Px, &b_US_true_part_Px);
   fChain->SetBranchAddress("US_true_part_Py", US_true_part_Py, &b_US_true_part_Py);
   fChain->SetBranchAddress("US_true_part_Pz", US_true_part_Pz, &b_US_true_part_Pz);
   fChain->SetBranchAddress("US_true_part_E", US_true_part_E, &b_US_true_part_E);
   fChain->SetBranchAddress("US_true_part_M", US_true_part_M, &b_US_true_part_M);
   fChain->SetBranchAddress("US_true_part_hasMother", US_true_part_hasMother, &b_US_true_part_hasMother);
   fChain->SetBranchAddress("US_true_moth_Ori_Vtx_x", US_true_moth_Ori_Vtx_x, &b_US_true_moth_Ori_Vtx_x);
   fChain->SetBranchAddress("US_true_moth_Ori_Vtx_y", US_true_moth_Ori_Vtx_y, &b_US_true_moth_Ori_Vtx_y);
   fChain->SetBranchAddress("US_true_moth_Ori_Vtx_z", US_true_moth_Ori_Vtx_z, &b_US_true_moth_Ori_Vtx_z);
   fChain->SetBranchAddress("US_true_moth_ID", US_true_moth_ID, &b_US_true_moth_ID);
   fChain->SetBranchAddress("US_true_moth_Px", US_true_moth_Px, &b_US_true_moth_Px);
   fChain->SetBranchAddress("US_true_moth_Py", US_true_moth_Py, &b_US_true_moth_Py);
   fChain->SetBranchAddress("US_true_moth_Pz", US_true_moth_Pz, &b_US_true_moth_Pz);
   fChain->SetBranchAddress("US_true_moth_E", US_true_moth_E, &b_US_true_moth_E);
   fChain->SetBranchAddress("US_true_moth_M", US_true_moth_M, &b_US_true_moth_M);
   fChain->SetBranchAddress("US_true_moth_hasMother", US_true_moth_hasMother, &b_US_true_moth_hasMother);
   fChain->SetBranchAddress("US_true_gran_Ori_Vtx_x", US_true_gran_Ori_Vtx_x, &b_US_true_gran_Ori_Vtx_x);
   fChain->SetBranchAddress("US_true_gran_Ori_Vtx_y", US_true_gran_Ori_Vtx_y, &b_US_true_gran_Ori_Vtx_y);
   fChain->SetBranchAddress("US_true_gran_Ori_Vtx_z", US_true_gran_Ori_Vtx_z, &b_US_true_gran_Ori_Vtx_z);
   fChain->SetBranchAddress("US_true_gran_ID", US_true_gran_ID, &b_US_true_gran_ID);
   fChain->SetBranchAddress("US_true_gran_Px", US_true_gran_Px, &b_US_true_gran_Px);
   fChain->SetBranchAddress("US_true_gran_Py", US_true_gran_Py, &b_US_true_gran_Py);
   fChain->SetBranchAddress("US_true_gran_Pz", US_true_gran_Pz, &b_US_true_gran_Pz);
   fChain->SetBranchAddress("US_true_gran_E", US_true_gran_E, &b_US_true_gran_E);
   fChain->SetBranchAddress("US_true_gran_M", US_true_gran_M, &b_US_true_gran_M);
   fChain->SetBranchAddress("US_true_gran_hasMother", US_true_gran_hasMother, &b_US_true_gran_hasMother);
   fChain->SetBranchAddress("US_true_mogr_Ori_Vtx_x", US_true_mogr_Ori_Vtx_x, &b_US_true_mogr_Ori_Vtx_x);
   fChain->SetBranchAddress("US_true_mogr_Ori_Vtx_y", US_true_mogr_Ori_Vtx_y, &b_US_true_mogr_Ori_Vtx_y);
   fChain->SetBranchAddress("US_true_mogr_Ori_Vtx_z", US_true_mogr_Ori_Vtx_z, &b_US_true_mogr_Ori_Vtx_z);
   fChain->SetBranchAddress("US_true_mogr_ID", US_true_mogr_ID, &b_US_true_mogr_ID);
   fChain->SetBranchAddress("US_true_mogr_Px", US_true_mogr_Px, &b_US_true_mogr_Px);
   fChain->SetBranchAddress("US_true_mogr_Py", US_true_mogr_Py, &b_US_true_mogr_Py);
   fChain->SetBranchAddress("US_true_mogr_Pz", US_true_mogr_Pz, &b_US_true_mogr_Pz);
   fChain->SetBranchAddress("US_true_mogr_E", US_true_mogr_E, &b_US_true_mogr_E);
   fChain->SetBranchAddress("US_true_mogr_M", US_true_mogr_M, &b_US_true_mogr_M);
   fChain->SetBranchAddress("US_true_mogr_hasMother", US_true_mogr_hasMother, &b_US_true_mogr_hasMother);
   fChain->SetBranchAddress("US_true_grgr_Ori_Vtx_x", US_true_grgr_Ori_Vtx_x, &b_US_true_grgr_Ori_Vtx_x);
   fChain->SetBranchAddress("US_true_grgr_Ori_Vtx_y", US_true_grgr_Ori_Vtx_y, &b_US_true_grgr_Ori_Vtx_y);
   fChain->SetBranchAddress("US_true_grgr_Ori_Vtx_z", US_true_grgr_Ori_Vtx_z, &b_US_true_grgr_Ori_Vtx_z);
   fChain->SetBranchAddress("US_true_grgr_ID", US_true_grgr_ID, &b_US_true_grgr_ID);
   fChain->SetBranchAddress("US_true_grgr_Px", US_true_grgr_Px, &b_US_true_grgr_Px);
   fChain->SetBranchAddress("US_true_grgr_Py", US_true_grgr_Py, &b_US_true_grgr_Py);
   fChain->SetBranchAddress("US_true_grgr_Pz", US_true_grgr_Pz, &b_US_true_grgr_Pz);
   fChain->SetBranchAddress("US_true_grgr_E", US_true_grgr_E, &b_US_true_grgr_E);
   fChain->SetBranchAddress("US_true_grgr_M", US_true_grgr_M, &b_US_true_grgr_M);
   fChain->SetBranchAddress("MCGEN_num", &MCGEN_num, &b_MCGEN_num);
   fChain->SetBranchAddress("MCGEN_partindex", MCGEN_partindex, &b_MCGEN_partindex);
   fChain->SetBranchAddress("MCGEN_motindex", MCGEN_motindex, &b_MCGEN_motindex);
   fChain->SetBranchAddress("MCGEN_lundid", MCGEN_lundid, &b_MCGEN_lundid);
   fChain->SetBranchAddress("MCGEN_px", MCGEN_px, &b_MCGEN_px);
   fChain->SetBranchAddress("MCGEN_py", MCGEN_py, &b_MCGEN_py);
   fChain->SetBranchAddress("MCGEN_pz", MCGEN_pz, &b_MCGEN_pz);
   fChain->SetBranchAddress("MCGEN_vtx_x", MCGEN_vtx_x, &b_MCGEN_vtx_x);
   fChain->SetBranchAddress("MCGEN_vtx_y", MCGEN_vtx_y, &b_MCGEN_vtx_y);
   fChain->SetBranchAddress("MCGEN_vtx_z", MCGEN_vtx_z, &b_MCGEN_vtx_z);
   fChain->SetBranchAddress("MCGEN_origtype", MCGEN_origtype, &b_MCGEN_origtype);
   fChain->SetBranchAddress("B_typeOriginVtx", &B_typeOriginVtx, &b_B_typeOriginVtx);
   fChain->SetBranchAddress("B_nEndVertices", &B_nEndVertices, &b_B_nEndVertices);
   fChain->SetBranchAddress("B_ancestorpid", &B_ancestorpid, &b_B_ancestorpid);
   fChain->SetBranchAddress("B_MCI", &B_MCI, &b_B_MCI);
   fChain->SetBranchAddress("B_TAU", &B_TAU, &b_B_TAU);
   fChain->SetBranchAddress("B_TAUERR", &B_TAUERR, &b_B_TAUERR);
   fChain->SetBranchAddress("B_TAUCHI2", &B_TAUCHI2, &b_B_TAUCHI2);
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
   fChain->SetBranchAddress("B_L0MuonDecision_Dec", &B_L0MuonDecision_Dec, &b_B_L0MuonDecision_Dec);
   fChain->SetBranchAddress("B_L0MuonDecision_TIS", &B_L0MuonDecision_TIS, &b_B_L0MuonDecision_TIS);
   fChain->SetBranchAddress("B_L0MuonDecision_TOS", &B_L0MuonDecision_TOS, &b_B_L0MuonDecision_TOS);
   fChain->SetBranchAddress("B_L0DiMuonDecision_Dec", &B_L0DiMuonDecision_Dec, &b_B_L0DiMuonDecision_Dec);
   fChain->SetBranchAddress("B_L0DiMuonDecision_TIS", &B_L0DiMuonDecision_TIS, &b_B_L0DiMuonDecision_TIS);
   fChain->SetBranchAddress("B_L0DiMuonDecision_TOS", &B_L0DiMuonDecision_TOS, &b_B_L0DiMuonDecision_TOS);
   fChain->SetBranchAddress("B_L0HadronDecision_Dec", &B_L0HadronDecision_Dec, &b_B_L0HadronDecision_Dec);
   fChain->SetBranchAddress("B_L0HadronDecision_TIS", &B_L0HadronDecision_TIS, &b_B_L0HadronDecision_TIS);
   fChain->SetBranchAddress("B_L0HadronDecision_TOS", &B_L0HadronDecision_TOS, &b_B_L0HadronDecision_TOS);
   fChain->SetBranchAddress("B_L0ElectronDecision_Dec", &B_L0ElectronDecision_Dec, &b_B_L0ElectronDecision_Dec);
   fChain->SetBranchAddress("B_L0ElectronDecision_TIS", &B_L0ElectronDecision_TIS, &b_B_L0ElectronDecision_TIS);
   fChain->SetBranchAddress("B_L0ElectronDecision_TOS", &B_L0ElectronDecision_TOS, &b_B_L0ElectronDecision_TOS);
   fChain->SetBranchAddress("B_L0ElectronHiDecision_Dec", &B_L0ElectronHiDecision_Dec, &b_B_L0ElectronHiDecision_Dec);
   fChain->SetBranchAddress("B_L0ElectronHiDecision_TIS", &B_L0ElectronHiDecision_TIS, &b_B_L0ElectronHiDecision_TIS);
   fChain->SetBranchAddress("B_L0ElectronHiDecision_TOS", &B_L0ElectronHiDecision_TOS, &b_B_L0ElectronHiDecision_TOS);
   fChain->SetBranchAddress("B_L0PhotonDecision_Dec", &B_L0PhotonDecision_Dec, &b_B_L0PhotonDecision_Dec);
   fChain->SetBranchAddress("B_L0PhotonDecision_TIS", &B_L0PhotonDecision_TIS, &b_B_L0PhotonDecision_TIS);
   fChain->SetBranchAddress("B_L0PhotonDecision_TOS", &B_L0PhotonDecision_TOS, &b_B_L0PhotonDecision_TOS);
   fChain->SetBranchAddress("B_L0PhotonHiDecision_Dec", &B_L0PhotonHiDecision_Dec, &b_B_L0PhotonHiDecision_Dec);
   fChain->SetBranchAddress("B_L0PhotonHiDecision_TIS", &B_L0PhotonHiDecision_TIS, &b_B_L0PhotonHiDecision_TIS);
   fChain->SetBranchAddress("B_L0PhotonHiDecision_TOS", &B_L0PhotonHiDecision_TOS, &b_B_L0PhotonHiDecision_TOS);
   fChain->SetBranchAddress("B_Hlt1SingleMuonNoIPDecision_Dec", &B_Hlt1SingleMuonNoIPDecision_Dec, &b_B_Hlt1SingleMuonNoIPDecision_Dec);
   fChain->SetBranchAddress("B_Hlt1SingleMuonNoIPDecision_TIS", &B_Hlt1SingleMuonNoIPDecision_TIS, &b_B_Hlt1SingleMuonNoIPDecision_TIS);
   fChain->SetBranchAddress("B_Hlt1SingleMuonNoIPDecision_TOS", &B_Hlt1SingleMuonNoIPDecision_TOS, &b_B_Hlt1SingleMuonNoIPDecision_TOS);
   fChain->SetBranchAddress("B_Hlt1SingleMuonHighPTDecision_Dec", &B_Hlt1SingleMuonHighPTDecision_Dec, &b_B_Hlt1SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt1SingleMuonHighPTDecision_TIS", &B_Hlt1SingleMuonHighPTDecision_TIS, &b_B_Hlt1SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt1SingleMuonHighPTDecision_TOS", &B_Hlt1SingleMuonHighPTDecision_TOS, &b_B_Hlt1SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt1SingleElectronNoIPDecision_Dec", &B_Hlt1SingleElectronNoIPDecision_Dec, &b_B_Hlt1SingleElectronNoIPDecision_Dec);
   fChain->SetBranchAddress("B_Hlt1SingleElectronNoIPDecision_TIS", &B_Hlt1SingleElectronNoIPDecision_TIS, &b_B_Hlt1SingleElectronNoIPDecision_TIS);
   fChain->SetBranchAddress("B_Hlt1SingleElectronNoIPDecision_TOS", &B_Hlt1SingleElectronNoIPDecision_TOS, &b_B_Hlt1SingleElectronNoIPDecision_TOS);
   fChain->SetBranchAddress("B_Hlt1TrackAllL0Decision_Dec", &B_Hlt1TrackAllL0Decision_Dec, &b_B_Hlt1TrackAllL0Decision_Dec);
   fChain->SetBranchAddress("B_Hlt1TrackAllL0Decision_TIS", &B_Hlt1TrackAllL0Decision_TIS, &b_B_Hlt1TrackAllL0Decision_TIS);
   fChain->SetBranchAddress("B_Hlt1TrackAllL0Decision_TOS", &B_Hlt1TrackAllL0Decision_TOS, &b_B_Hlt1TrackAllL0Decision_TOS);
   fChain->SetBranchAddress("B_Hlt1TrackMuonDecision_Dec", &B_Hlt1TrackMuonDecision_Dec, &b_B_Hlt1TrackMuonDecision_Dec);
   fChain->SetBranchAddress("B_Hlt1TrackMuonDecision_TIS", &B_Hlt1TrackMuonDecision_TIS, &b_B_Hlt1TrackMuonDecision_TIS);
   fChain->SetBranchAddress("B_Hlt1TrackMuonDecision_TOS", &B_Hlt1TrackMuonDecision_TOS, &b_B_Hlt1TrackMuonDecision_TOS);
   fChain->SetBranchAddress("B_Hlt1TrackPhotonDecision_Dec", &B_Hlt1TrackPhotonDecision_Dec, &b_B_Hlt1TrackPhotonDecision_Dec);
   fChain->SetBranchAddress("B_Hlt1TrackPhotonDecision_TIS", &B_Hlt1TrackPhotonDecision_TIS, &b_B_Hlt1TrackPhotonDecision_TIS);
   fChain->SetBranchAddress("B_Hlt1TrackPhotonDecision_TOS", &B_Hlt1TrackPhotonDecision_TOS, &b_B_Hlt1TrackPhotonDecision_TOS);
   fChain->SetBranchAddress("B_Hlt1TrackAllL0__Decision_Dec", &B_Hlt1TrackAllL0__Decision_Dec, &b_B_Hlt1TrackAllL0__Decision_Dec);
   fChain->SetBranchAddress("B_Hlt1TrackAllL0__Decision_TIS", &B_Hlt1TrackAllL0__Decision_TIS, &b_B_Hlt1TrackAllL0__Decision_TIS);
   fChain->SetBranchAddress("B_Hlt1TrackAllL0__Decision_TOS", &B_Hlt1TrackAllL0__Decision_TOS, &b_B_Hlt1TrackAllL0__Decision_TOS);
   fChain->SetBranchAddress("B_Hlt1DiMuonLowMassDecision_Dec", &B_Hlt1DiMuonLowMassDecision_Dec, &b_B_Hlt1DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("B_Hlt1DiMuonLowMassDecision_TIS", &B_Hlt1DiMuonLowMassDecision_TIS, &b_B_Hlt1DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("B_Hlt1DiMuonLowMassDecision_TOS", &B_Hlt1DiMuonLowMassDecision_TOS, &b_B_Hlt1DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("B_Hlt1DiMuonHighMassDecision_Dec", &B_Hlt1DiMuonHighMassDecision_Dec, &b_B_Hlt1DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("B_Hlt1DiMuonHighMassDecision_TIS", &B_Hlt1DiMuonHighMassDecision_TIS, &b_B_Hlt1DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("B_Hlt1DiMuonHighMassDecision_TOS", &B_Hlt1DiMuonHighMassDecision_TOS, &b_B_Hlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("B_Hlt1MB__Decision_Dec", &B_Hlt1MB__Decision_Dec, &b_B_Hlt1MB__Decision_Dec);
   fChain->SetBranchAddress("B_Hlt1MB__Decision_TIS", &B_Hlt1MB__Decision_TIS, &b_B_Hlt1MB__Decision_TIS);
   fChain->SetBranchAddress("B_Hlt1MB__Decision_TOS", &B_Hlt1MB__Decision_TOS, &b_B_Hlt1MB__Decision_TOS);
   fChain->SetBranchAddress("B_Hlt1TrackAllL0TightDecision_Dec", &B_Hlt1TrackAllL0TightDecision_Dec, &b_B_Hlt1TrackAllL0TightDecision_Dec);
   fChain->SetBranchAddress("B_Hlt1TrackAllL0TightDecision_TIS", &B_Hlt1TrackAllL0TightDecision_TIS, &b_B_Hlt1TrackAllL0TightDecision_TIS);
   fChain->SetBranchAddress("B_Hlt1TrackAllL0TightDecision_TOS", &B_Hlt1TrackAllL0TightDecision_TOS, &b_B_Hlt1TrackAllL0TightDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2SingleMuonDecision_Dec", &B_Hlt2SingleMuonDecision_Dec, &b_B_Hlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2SingleMuonDecision_TIS", &B_Hlt2SingleMuonDecision_TIS, &b_B_Hlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2SingleMuonDecision_TOS", &B_Hlt2SingleMuonDecision_TOS, &b_B_Hlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2SingleMuonLowPTDecision_Dec", &B_Hlt2SingleMuonLowPTDecision_Dec, &b_B_Hlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2SingleMuonLowPTDecision_TIS", &B_Hlt2SingleMuonLowPTDecision_TIS, &b_B_Hlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2SingleMuonLowPTDecision_TOS", &B_Hlt2SingleMuonLowPTDecision_TOS, &b_B_Hlt2SingleMuonLowPTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2SingleMuonHighPTDecision_Dec", &B_Hlt2SingleMuonHighPTDecision_Dec, &b_B_Hlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2SingleMuonHighPTDecision_TIS", &B_Hlt2SingleMuonHighPTDecision_TIS, &b_B_Hlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2SingleMuonHighPTDecision_TOS", &B_Hlt2SingleMuonHighPTDecision_TOS, &b_B_Hlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDecision_Dec", &B_Hlt2DiMuonDecision_Dec, &b_B_Hlt2DiMuonDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonDecision_TIS", &B_Hlt2DiMuonDecision_TIS, &b_B_Hlt2DiMuonDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDecision_TOS", &B_Hlt2DiMuonDecision_TOS, &b_B_Hlt2DiMuonDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonLowMassDecision_Dec", &B_Hlt2DiMuonLowMassDecision_Dec, &b_B_Hlt2DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonLowMassDecision_TIS", &B_Hlt2DiMuonLowMassDecision_TIS, &b_B_Hlt2DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonLowMassDecision_TOS", &B_Hlt2DiMuonLowMassDecision_TOS, &b_B_Hlt2DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonJPsiDecision_Dec", &B_Hlt2DiMuonJPsiDecision_Dec, &b_B_Hlt2DiMuonJPsiDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonJPsiDecision_TIS", &B_Hlt2DiMuonJPsiDecision_TIS, &b_B_Hlt2DiMuonJPsiDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonJPsiDecision_TOS", &B_Hlt2DiMuonJPsiDecision_TOS, &b_B_Hlt2DiMuonJPsiDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonJPsiHighPTDecision_Dec", &B_Hlt2DiMuonJPsiHighPTDecision_Dec, &b_B_Hlt2DiMuonJPsiHighPTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonJPsiHighPTDecision_TIS", &B_Hlt2DiMuonJPsiHighPTDecision_TIS, &b_B_Hlt2DiMuonJPsiHighPTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonJPsiHighPTDecision_TOS", &B_Hlt2DiMuonJPsiHighPTDecision_TOS, &b_B_Hlt2DiMuonJPsiHighPTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonPsi2SDecision_Dec", &B_Hlt2DiMuonPsi2SDecision_Dec, &b_B_Hlt2DiMuonPsi2SDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonPsi2SDecision_TIS", &B_Hlt2DiMuonPsi2SDecision_TIS, &b_B_Hlt2DiMuonPsi2SDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonPsi2SDecision_TOS", &B_Hlt2DiMuonPsi2SDecision_TOS, &b_B_Hlt2DiMuonPsi2SDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedDecision_Dec", &B_Hlt2DiMuonDetachedDecision_Dec, &b_B_Hlt2DiMuonDetachedDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedDecision_TIS", &B_Hlt2DiMuonDetachedDecision_TIS, &b_B_Hlt2DiMuonDetachedDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedDecision_TOS", &B_Hlt2DiMuonDetachedDecision_TOS, &b_B_Hlt2DiMuonDetachedDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedJPsiDecision_Dec", &B_Hlt2DiMuonDetachedJPsiDecision_Dec, &b_B_Hlt2DiMuonDetachedJPsiDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedJPsiDecision_TIS", &B_Hlt2DiMuonDetachedJPsiDecision_TIS, &b_B_Hlt2DiMuonDetachedJPsiDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedJPsiDecision_TOS", &B_Hlt2DiMuonDetachedJPsiDecision_TOS, &b_B_Hlt2DiMuonDetachedJPsiDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedHeavyDecision_Dec", &B_Hlt2DiMuonDetachedHeavyDecision_Dec, &b_B_Hlt2DiMuonDetachedHeavyDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedHeavyDecision_TIS", &B_Hlt2DiMuonDetachedHeavyDecision_TIS, &b_B_Hlt2DiMuonDetachedHeavyDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDetachedHeavyDecision_TOS", &B_Hlt2DiMuonDetachedHeavyDecision_TOS, &b_B_Hlt2DiMuonDetachedHeavyDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2TriMuonTauDecision_Dec", &B_Hlt2TriMuonTauDecision_Dec, &b_B_Hlt2TriMuonTauDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2TriMuonTauDecision_TIS", &B_Hlt2TriMuonTauDecision_TIS, &b_B_Hlt2TriMuonTauDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2TriMuonTauDecision_TOS", &B_Hlt2TriMuonTauDecision_TOS, &b_B_Hlt2TriMuonTauDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2B2HHDecision_Dec", &B_Hlt2B2HHDecision_Dec, &b_B_Hlt2B2HHDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2B2HHDecision_TIS", &B_Hlt2B2HHDecision_TIS, &b_B_Hlt2B2HHDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2B2HHDecision_TOS", &B_Hlt2B2HHDecision_TOS, &b_B_Hlt2B2HHDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonBDecision_Dec", &B_Hlt2DiMuonBDecision_Dec, &b_B_Hlt2DiMuonBDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonBDecision_TIS", &B_Hlt2DiMuonBDecision_TIS, &b_B_Hlt2DiMuonBDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonBDecision_TOS", &B_Hlt2DiMuonBDecision_TOS, &b_B_Hlt2DiMuonBDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonZDecision_Dec", &B_Hlt2DiMuonZDecision_Dec, &b_B_Hlt2DiMuonZDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonZDecision_TIS", &B_Hlt2DiMuonZDecision_TIS, &b_B_Hlt2DiMuonZDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonZDecision_TOS", &B_Hlt2DiMuonZDecision_TOS, &b_B_Hlt2DiMuonZDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2TopoMu2BodyBBDTDecision_Dec", &B_Hlt2TopoMu2BodyBBDTDecision_Dec, &b_B_Hlt2TopoMu2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2TopoMu2BodyBBDTDecision_TIS", &B_Hlt2TopoMu2BodyBBDTDecision_TIS, &b_B_Hlt2TopoMu2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2TopoMu2BodyBBDTDecision_TOS", &B_Hlt2TopoMu2BodyBBDTDecision_TOS, &b_B_Hlt2TopoMu2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2TopoMu3BodyBBDTDecision_Dec", &B_Hlt2TopoMu3BodyBBDTDecision_Dec, &b_B_Hlt2TopoMu3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2TopoMu3BodyBBDTDecision_TIS", &B_Hlt2TopoMu3BodyBBDTDecision_TIS, &b_B_Hlt2TopoMu3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2TopoMu3BodyBBDTDecision_TOS", &B_Hlt2TopoMu3BodyBBDTDecision_TOS, &b_B_Hlt2TopoMu3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2TopoMu4BodyBBDTDecision_Dec", &B_Hlt2TopoMu4BodyBBDTDecision_Dec, &b_B_Hlt2TopoMu4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2TopoMu4BodyBBDTDecision_TIS", &B_Hlt2TopoMu4BodyBBDTDecision_TIS, &b_B_Hlt2TopoMu4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2TopoMu4BodyBBDTDecision_TOS", &B_Hlt2TopoMu4BodyBBDTDecision_TOS, &b_B_Hlt2TopoMu4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2Topo2BodyBBDTDecision_Dec", &B_Hlt2Topo2BodyBBDTDecision_Dec, &b_B_Hlt2Topo2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2Topo2BodyBBDTDecision_TIS", &B_Hlt2Topo2BodyBBDTDecision_TIS, &b_B_Hlt2Topo2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2Topo2BodyBBDTDecision_TOS", &B_Hlt2Topo2BodyBBDTDecision_TOS, &b_B_Hlt2Topo2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2Topo3BodyBBDTDecision_Dec", &B_Hlt2Topo3BodyBBDTDecision_Dec, &b_B_Hlt2Topo3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2Topo3BodyBBDTDecision_TIS", &B_Hlt2Topo3BodyBBDTDecision_TIS, &b_B_Hlt2Topo3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2Topo3BodyBBDTDecision_TOS", &B_Hlt2Topo3BodyBBDTDecision_TOS, &b_B_Hlt2Topo3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2Topo4BodyBBDTDecision_Dec", &B_Hlt2Topo4BodyBBDTDecision_Dec, &b_B_Hlt2Topo4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2Topo4BodyBBDTDecision_TIS", &B_Hlt2Topo4BodyBBDTDecision_TIS, &b_B_Hlt2Topo4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2Topo4BodyBBDTDecision_TOS", &B_Hlt2Topo4BodyBBDTDecision_TOS, &b_B_Hlt2Topo4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2Topo2BodySimpleDecision_Dec", &B_Hlt2Topo2BodySimpleDecision_Dec, &b_B_Hlt2Topo2BodySimpleDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2Topo2BodySimpleDecision_TIS", &B_Hlt2Topo2BodySimpleDecision_TIS, &b_B_Hlt2Topo2BodySimpleDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2Topo2BodySimpleDecision_TOS", &B_Hlt2Topo2BodySimpleDecision_TOS, &b_B_Hlt2Topo2BodySimpleDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2Topo3BodySimpleDecision_Dec", &B_Hlt2Topo3BodySimpleDecision_Dec, &b_B_Hlt2Topo3BodySimpleDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2Topo3BodySimpleDecision_TIS", &B_Hlt2Topo3BodySimpleDecision_TIS, &b_B_Hlt2Topo3BodySimpleDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2Topo3BodySimpleDecision_TOS", &B_Hlt2Topo3BodySimpleDecision_TOS, &b_B_Hlt2Topo3BodySimpleDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2Topo4BodySimpleDecision_Dec", &B_Hlt2Topo4BodySimpleDecision_Dec, &b_B_Hlt2Topo4BodySimpleDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2Topo4BodySimpleDecision_TIS", &B_Hlt2Topo4BodySimpleDecision_TIS, &b_B_Hlt2Topo4BodySimpleDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2Topo4BodySimpleDecision_TOS", &B_Hlt2Topo4BodySimpleDecision_TOS, &b_B_Hlt2Topo4BodySimpleDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2PassThroughDecision_Dec", &B_Hlt2PassThroughDecision_Dec, &b_B_Hlt2PassThroughDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2PassThroughDecision_TIS", &B_Hlt2PassThroughDecision_TIS, &b_B_Hlt2PassThroughDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2PassThroughDecision_TOS", &B_Hlt2PassThroughDecision_TOS, &b_B_Hlt2PassThroughDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2TransparentDecision_Dec", &B_Hlt2TransparentDecision_Dec, &b_B_Hlt2TransparentDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2TransparentDecision_TIS", &B_Hlt2TransparentDecision_TIS, &b_B_Hlt2TransparentDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2TransparentDecision_TOS", &B_Hlt2TransparentDecision_TOS, &b_B_Hlt2TransparentDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2IncPhiDecision_Dec", &B_Hlt2IncPhiDecision_Dec, &b_B_Hlt2IncPhiDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2IncPhiDecision_TIS", &B_Hlt2IncPhiDecision_TIS, &b_B_Hlt2IncPhiDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2IncPhiDecision_TOS", &B_Hlt2IncPhiDecision_TOS, &b_B_Hlt2IncPhiDecision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDY__Decision_Dec", &B_Hlt2DiMuonDY__Decision_Dec, &b_B_Hlt2DiMuonDY__Decision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiMuonDY__Decision_TIS", &B_Hlt2DiMuonDY__Decision_TIS, &b_B_Hlt2DiMuonDY__Decision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiMuonDY__Decision_TOS", &B_Hlt2DiMuonDY__Decision_TOS, &b_B_Hlt2DiMuonDY__Decision_TOS);
   fChain->SetBranchAddress("B_Hlt2TopoE__Decision_Dec", &B_Hlt2TopoE__Decision_Dec, &b_B_Hlt2TopoE__Decision_Dec);
   fChain->SetBranchAddress("B_Hlt2TopoE__Decision_TIS", &B_Hlt2TopoE__Decision_TIS, &b_B_Hlt2TopoE__Decision_TIS);
   fChain->SetBranchAddress("B_Hlt2TopoE__Decision_TOS", &B_Hlt2TopoE__Decision_TOS, &b_B_Hlt2TopoE__Decision_TOS);
   fChain->SetBranchAddress("B_Hlt2Topo__Decision_Dec", &B_Hlt2Topo__Decision_Dec, &b_B_Hlt2Topo__Decision_Dec);
   fChain->SetBranchAddress("B_Hlt2Topo__Decision_TIS", &B_Hlt2Topo__Decision_TIS, &b_B_Hlt2Topo__Decision_TIS);
   fChain->SetBranchAddress("B_Hlt2Topo__Decision_TOS", &B_Hlt2Topo__Decision_TOS, &b_B_Hlt2Topo__Decision_TOS);
   fChain->SetBranchAddress("B_Hlt2Charm__Decision_Dec", &B_Hlt2Charm__Decision_Dec, &b_B_Hlt2Charm__Decision_Dec);
   fChain->SetBranchAddress("B_Hlt2Charm__Decision_TIS", &B_Hlt2Charm__Decision_TIS, &b_B_Hlt2Charm__Decision_TIS);
   fChain->SetBranchAddress("B_Hlt2Charm__Decision_TOS", &B_Hlt2Charm__Decision_TOS, &b_B_Hlt2Charm__Decision_TOS);
   fChain->SetBranchAddress("B_Hlt2DiElectron__Decision_Dec", &B_Hlt2DiElectron__Decision_Dec, &b_B_Hlt2DiElectron__Decision_Dec);
   fChain->SetBranchAddress("B_Hlt2DiElectron__Decision_TIS", &B_Hlt2DiElectron__Decision_TIS, &b_B_Hlt2DiElectron__Decision_TIS);
   fChain->SetBranchAddress("B_Hlt2DiElectron__Decision_TOS", &B_Hlt2DiElectron__Decision_TOS, &b_B_Hlt2DiElectron__Decision_TOS);
   fChain->SetBranchAddress("B_Hlt2__GammaDecision_Dec", &B_Hlt2__GammaDecision_Dec, &b_B_Hlt2__GammaDecision_Dec);
   fChain->SetBranchAddress("B_Hlt2__GammaDecision_TIS", &B_Hlt2__GammaDecision_TIS, &b_B_Hlt2__GammaDecision_TIS);
   fChain->SetBranchAddress("B_Hlt2__GammaDecision_TOS", &B_Hlt2__GammaDecision_TOS, &b_B_Hlt2__GammaDecision_TOS);
   fChain->SetBranchAddress("B_DTF_M", &B_DTF_M, &b_B_DTF_M);
   fChain->SetBranchAddress("B_DTF_MM", &B_DTF_MM, &b_B_DTF_MM);
   fChain->SetBranchAddress("B_DTF_P", &B_DTF_P, &b_B_DTF_P);
   fChain->SetBranchAddress("B_DTF_PE", &B_DTF_PE, &b_B_DTF_PE);
   fChain->SetBranchAddress("B_DTF_PT", &B_DTF_PT, &b_B_DTF_PT);
   fChain->SetBranchAddress("B_DTF_PX", &B_DTF_PX, &b_B_DTF_PX);
   fChain->SetBranchAddress("B_DTF_PY", &B_DTF_PY, &b_B_DTF_PY);
   fChain->SetBranchAddress("B_DTF_PZ", &B_DTF_PZ, &b_B_DTF_PZ);
   fChain->SetBranchAddress("B_DTF_VFit_M", &B_DTF_VFit_M, &b_B_DTF_VFit_M);
   fChain->SetBranchAddress("B_DTF_VFit_MM", &B_DTF_VFit_MM, &b_B_DTF_VFit_MM);
   fChain->SetBranchAddress("B_DTF_VFit_P", &B_DTF_VFit_P, &b_B_DTF_VFit_P);
   fChain->SetBranchAddress("B_DTF_VFit_PE", &B_DTF_VFit_PE, &b_B_DTF_VFit_PE);
   fChain->SetBranchAddress("B_DTF_VFit_PT", &B_DTF_VFit_PT, &b_B_DTF_VFit_PT);
   fChain->SetBranchAddress("B_DTF_VFit_PX", &B_DTF_VFit_PX, &b_B_DTF_VFit_PX);
   fChain->SetBranchAddress("B_DTF_VFit_PY", &B_DTF_VFit_PY, &b_B_DTF_VFit_PY);
   fChain->SetBranchAddress("B_DTF_VFit_PZ", &B_DTF_VFit_PZ, &b_B_DTF_VFit_PZ);
   fChain->SetBranchAddress("B_WRONGMASS_K_K", &B_WRONGMASS_K_K, &b_B_WRONGMASS_K_K);
   fChain->SetBranchAddress("B_WRONGMASS_K_p", &B_WRONGMASS_K_p, &b_B_WRONGMASS_K_p);
   fChain->SetBranchAddress("B_WRONGMASS_K_pi", &B_WRONGMASS_K_pi, &b_B_WRONGMASS_K_pi);
   fChain->SetBranchAddress("B_WRONGMASS_p_K", &B_WRONGMASS_p_K, &b_B_WRONGMASS_p_K);
   fChain->SetBranchAddress("B_WRONGMASS_p_pi", &B_WRONGMASS_p_pi, &b_B_WRONGMASS_p_pi);
   fChain->SetBranchAddress("B_WRONGMASS_pi_K", &B_WRONGMASS_pi_K, &b_B_WRONGMASS_pi_K);
   fChain->SetBranchAddress("B_WRONGMASS_pi_p", &B_WRONGMASS_pi_p, &b_B_WRONGMASS_pi_p);
   fChain->SetBranchAddress("B_WRONGMASS_pi_pi", &B_WRONGMASS_pi_pi, &b_B_WRONGMASS_pi_pi);
   fChain->SetBranchAddress("B_WRONGMASS_K_K_2", &B_WRONGMASS_K_K_2, &b_B_WRONGMASS_K_K_2);
   fChain->SetBranchAddress("B_WRONGMASS_K_p_2", &B_WRONGMASS_K_p_2, &b_B_WRONGMASS_K_p_2);
   fChain->SetBranchAddress("B_WRONGMASS_K_pi_2", &B_WRONGMASS_K_pi_2, &b_B_WRONGMASS_K_pi_2);
   fChain->SetBranchAddress("B_WRONGMASS_p_K_2", &B_WRONGMASS_p_K_2, &b_B_WRONGMASS_p_K_2);
   fChain->SetBranchAddress("B_WRONGMASS_p_pi_2", &B_WRONGMASS_p_pi_2, &b_B_WRONGMASS_p_pi_2);
   fChain->SetBranchAddress("B_WRONGMASS_pi_K_2", &B_WRONGMASS_pi_K_2, &b_B_WRONGMASS_pi_K_2);
   fChain->SetBranchAddress("B_WRONGMASS_pi_p_2", &B_WRONGMASS_pi_p_2, &b_B_WRONGMASS_pi_p_2);
   fChain->SetBranchAddress("B_WRONGMASS_pi_pi_2", &B_WRONGMASS_pi_pi_2, &b_B_WRONGMASS_pi_pi_2);
   fChain->SetBranchAddress("B_Vf", &B_Vf, &b_B_Vf);
   fChain->SetBranchAddress("MPT_iso", &MPT_iso, &b_MPT_iso);
   fChain->SetBranchAddress("MPT_iso_UpS", &MPT_iso_UpS, &b_MPT_iso_UpS);
   fChain->SetBranchAddress("MPT_iso_DwS", &MPT_iso_DwS, &b_MPT_iso_DwS);
   fChain->SetBranchAddress("Vf_Max", &Vf_Max, &b_Vf_Max);
   fChain->SetBranchAddress("Vf_Max_UpS", &Vf_Max_UpS, &b_Vf_Max_UpS);
   fChain->SetBranchAddress("Vf_Max_DwS", &Vf_Max_DwS, &b_Vf_Max_DwS);
   fChain->SetBranchAddress("Pos_Max", &Pos_Max, &b_Pos_Max);
   fChain->SetBranchAddress("Pos_Max_UpS", &Pos_Max_UpS, &b_Pos_Max_UpS);
   fChain->SetBranchAddress("Pos_Max_DwS", &Pos_Max_DwS, &b_Pos_Max_DwS);
   fChain->SetBranchAddress("sum_Vf_Maxs", &sum_Vf_Maxs, &b_sum_Vf_Maxs);
   fChain->SetBranchAddress("sum_Vf_Maxs_UpS", &sum_Vf_Maxs_UpS, &b_sum_Vf_Maxs_UpS);
   fChain->SetBranchAddress("B_ZVtop_nvtx", &B_ZVtop_nvtx, &b_B_ZVtop_nvtx);
   fChain->SetBranchAddress("B_zv_same", &B_zv_same, &b_B_zv_same);
   fChain->SetBranchAddress("MuP_zv_ipsall", &MuP_zv_ipsall, &b_MuP_zv_ipsall);
   fChain->SetBranchAddress("MuP_zv_ipall", &MuP_zv_ipall, &b_MuP_zv_ipall);
   fChain->SetBranchAddress("MuP_zv_proba", &MuP_zv_proba, &b_MuP_zv_proba);
   fChain->SetBranchAddress("MuP_zv_proba_close", &MuP_zv_proba_close, &b_MuP_zv_proba_close);
   fChain->SetBranchAddress("MuP_zv_chi2", &MuP_zv_chi2, &b_MuP_zv_chi2);
   fChain->SetBranchAddress("MuP_zv_dist", &MuP_zv_dist, &b_MuP_zv_dist);
   fChain->SetBranchAddress("MuP_zv_ntrkvtz", &MuP_zv_ntrkvtz, &b_MuP_zv_ntrkvtz);
   fChain->SetBranchAddress("MuM_zv_ipsall", &MuM_zv_ipsall, &b_MuM_zv_ipsall);
   fChain->SetBranchAddress("MuM_zv_ipall", &MuM_zv_ipall, &b_MuM_zv_ipall);
   fChain->SetBranchAddress("MuM_zv_proba", &MuM_zv_proba, &b_MuM_zv_proba);
   fChain->SetBranchAddress("MuM_zv_proba_close", &MuM_zv_proba_close, &b_MuM_zv_proba_close);
   fChain->SetBranchAddress("MuM_zv_chi2", &MuM_zv_chi2, &b_MuM_zv_chi2);
   fChain->SetBranchAddress("MuM_zv_dist", &MuM_zv_dist, &b_MuM_zv_dist);
   fChain->SetBranchAddress("MuM_zv_ntrkvtz", &MuM_zv_ntrkvtz, &b_MuM_zv_ntrkvtz);
   fChain->SetBranchAddress("zv_ipsall", &zv_ipsall, &b_zv_ipsall);
   fChain->SetBranchAddress("zv_ipall", &zv_ipall, &b_zv_ipall);
   fChain->SetBranchAddress("zv_proba", &zv_proba, &b_zv_proba);
   fChain->SetBranchAddress("zv_proba_close", &zv_proba_close, &b_zv_proba_close);
   fChain->SetBranchAddress("zv_chi2", &zv_chi2, &b_zv_chi2);
   fChain->SetBranchAddress("zv_dist", &zv_dist, &b_zv_dist);
   fChain->SetBranchAddress("zv_ntrkvtz", &zv_ntrkvtz, &b_zv_ntrkvtz);
   fChain->SetBranchAddress("ZViso", &ZViso, &b_ZViso);
   fChain->SetBranchAddress("B_Fit_nPV", &B_Fit_nPV, &b_B_Fit_nPV);
   fChain->SetBranchAddress("B_Fit_M", B_Fit_M, &b_B_Fit_M);
   fChain->SetBranchAddress("B_Fit_MERR", B_Fit_MERR, &b_B_Fit_MERR);
   fChain->SetBranchAddress("B_Fit_P", B_Fit_P, &b_B_Fit_P);
   fChain->SetBranchAddress("B_Fit_PERR", B_Fit_PERR, &b_B_Fit_PERR);
   fChain->SetBranchAddress("B_Fit_chi2", B_Fit_chi2, &b_B_Fit_chi2);
   fChain->SetBranchAddress("B_Fit_muminus_0_ID", B_Fit_muminus_0_ID, &b_B_Fit_muminus_0_ID);
   fChain->SetBranchAddress("B_Fit_muminus_0_PE", B_Fit_muminus_0_PE, &b_B_Fit_muminus_0_PE);
   fChain->SetBranchAddress("B_Fit_muminus_0_PX", B_Fit_muminus_0_PX, &b_B_Fit_muminus_0_PX);
   fChain->SetBranchAddress("B_Fit_muminus_0_PY", B_Fit_muminus_0_PY, &b_B_Fit_muminus_0_PY);
   fChain->SetBranchAddress("B_Fit_muminus_0_PZ", B_Fit_muminus_0_PZ, &b_B_Fit_muminus_0_PZ);
   fChain->SetBranchAddress("B_Fit_muminus_ID", B_Fit_muminus_ID, &b_B_Fit_muminus_ID);
   fChain->SetBranchAddress("B_Fit_muminus_PE", B_Fit_muminus_PE, &b_B_Fit_muminus_PE);
   fChain->SetBranchAddress("B_Fit_muminus_PX", B_Fit_muminus_PX, &b_B_Fit_muminus_PX);
   fChain->SetBranchAddress("B_Fit_muminus_PY", B_Fit_muminus_PY, &b_B_Fit_muminus_PY);
   fChain->SetBranchAddress("B_Fit_muminus_PZ", B_Fit_muminus_PZ, &b_B_Fit_muminus_PZ);
   fChain->SetBranchAddress("B_Fit_nDOF", B_Fit_nDOF, &b_B_Fit_nDOF);
   fChain->SetBranchAddress("B_Fit_nIter", B_Fit_nIter, &b_B_Fit_nIter);
   fChain->SetBranchAddress("B_Fit_status", B_Fit_status, &b_B_Fit_status);
   fChain->SetBranchAddress("B_VFit_nPV", &B_VFit_nPV, &b_B_VFit_nPV);
   fChain->SetBranchAddress("B_VFit_M", B_VFit_M, &b_B_VFit_M);
   fChain->SetBranchAddress("B_VFit_MERR", B_VFit_MERR, &b_B_VFit_MERR);
   fChain->SetBranchAddress("B_VFit_P", B_VFit_P, &b_B_VFit_P);
   fChain->SetBranchAddress("B_VFit_PERR", B_VFit_PERR, &b_B_VFit_PERR);
   fChain->SetBranchAddress("B_VFit_PV_X", B_VFit_PV_X, &b_B_VFit_PV_X);
   fChain->SetBranchAddress("B_VFit_PV_Y", B_VFit_PV_Y, &b_B_VFit_PV_Y);
   fChain->SetBranchAddress("B_VFit_PV_Z", B_VFit_PV_Z, &b_B_VFit_PV_Z);
   fChain->SetBranchAddress("B_VFit_PV_key", B_VFit_PV_key, &b_B_VFit_PV_key);
   fChain->SetBranchAddress("B_VFit_chi2", B_VFit_chi2, &b_B_VFit_chi2);
   fChain->SetBranchAddress("B_VFit_ctau", B_VFit_ctau, &b_B_VFit_ctau);
   fChain->SetBranchAddress("B_VFit_ctauErr", B_VFit_ctauErr, &b_B_VFit_ctauErr);
   fChain->SetBranchAddress("B_VFit_decayLength", B_VFit_decayLength, &b_B_VFit_decayLength);
   fChain->SetBranchAddress("B_VFit_decayLengthErr", B_VFit_decayLengthErr, &b_B_VFit_decayLengthErr);
   fChain->SetBranchAddress("B_VFit_muminus_0_ID", B_VFit_muminus_0_ID, &b_B_VFit_muminus_0_ID);
   fChain->SetBranchAddress("B_VFit_muminus_0_PE", B_VFit_muminus_0_PE, &b_B_VFit_muminus_0_PE);
   fChain->SetBranchAddress("B_VFit_muminus_0_PX", B_VFit_muminus_0_PX, &b_B_VFit_muminus_0_PX);
   fChain->SetBranchAddress("B_VFit_muminus_0_PY", B_VFit_muminus_0_PY, &b_B_VFit_muminus_0_PY);
   fChain->SetBranchAddress("B_VFit_muminus_0_PZ", B_VFit_muminus_0_PZ, &b_B_VFit_muminus_0_PZ);
   fChain->SetBranchAddress("B_VFit_muminus_ID", B_VFit_muminus_ID, &b_B_VFit_muminus_ID);
   fChain->SetBranchAddress("B_VFit_muminus_PE", B_VFit_muminus_PE, &b_B_VFit_muminus_PE);
   fChain->SetBranchAddress("B_VFit_muminus_PX", B_VFit_muminus_PX, &b_B_VFit_muminus_PX);
   fChain->SetBranchAddress("B_VFit_muminus_PY", B_VFit_muminus_PY, &b_B_VFit_muminus_PY);
   fChain->SetBranchAddress("B_VFit_muminus_PZ", B_VFit_muminus_PZ, &b_B_VFit_muminus_PZ);
   fChain->SetBranchAddress("B_VFit_nDOF", B_VFit_nDOF, &b_B_VFit_nDOF);
   fChain->SetBranchAddress("B_VFit_nIter", B_VFit_nIter, &b_B_VFit_nIter);
   fChain->SetBranchAddress("B_VFit_status", B_VFit_status, &b_B_VFit_status);
   fChain->SetBranchAddress("B_JETNOMU1PX", &B_JETNOMU1PX, &b_B_JETNOMU1PX);
   fChain->SetBranchAddress("B_JETNOMU1PY", &B_JETNOMU1PY, &b_B_JETNOMU1PY);
   fChain->SetBranchAddress("B_JETNOMU1PZ", &B_JETNOMU1PZ, &b_B_JETNOMU1PZ);
   fChain->SetBranchAddress("B_JETNOMU1PT", &B_JETNOMU1PT, &b_B_JETNOMU1PT);
   fChain->SetBranchAddress("B_JETNOMU1JETWIDTH", &B_JETNOMU1JETWIDTH, &b_B_JETNOMU1JETWIDTH);
   fChain->SetBranchAddress("B_JETNOMU1NNTAG", &B_JETNOMU1NNTAG, &b_B_JETNOMU1NNTAG);
   fChain->SetBranchAddress("B_JETNOMU1MNF", &B_JETNOMU1MNF, &b_B_JETNOMU1MNF);
   fChain->SetBranchAddress("B_JETNOMU2PX", &B_JETNOMU2PX, &b_B_JETNOMU2PX);
   fChain->SetBranchAddress("B_JETNOMU2PY", &B_JETNOMU2PY, &b_B_JETNOMU2PY);
   fChain->SetBranchAddress("B_JETNOMU2PZ", &B_JETNOMU2PZ, &b_B_JETNOMU2PZ);
   fChain->SetBranchAddress("B_JETNOMU2PT", &B_JETNOMU2PT, &b_B_JETNOMU2PT);
   fChain->SetBranchAddress("B_JETNOMU2JETWIDTH", &B_JETNOMU2JETWIDTH, &b_B_JETNOMU2JETWIDTH);
   fChain->SetBranchAddress("B_JETNOMU2NNTAG", &B_JETNOMU2NNTAG, &b_B_JETNOMU2NNTAG);
   fChain->SetBranchAddress("B_JETNOMU2MNF", &B_JETNOMU2MNF, &b_B_JETNOMU2MNF);
   fChain->SetBranchAddress("B_JETNOMU3PX", &B_JETNOMU3PX, &b_B_JETNOMU3PX);
   fChain->SetBranchAddress("B_JETNOMU3PY", &B_JETNOMU3PY, &b_B_JETNOMU3PY);
   fChain->SetBranchAddress("B_JETNOMU3PZ", &B_JETNOMU3PZ, &b_B_JETNOMU3PZ);
   fChain->SetBranchAddress("B_JETNOMU3PT", &B_JETNOMU3PT, &b_B_JETNOMU3PT);
   fChain->SetBranchAddress("B_JETNOMU3JETWIDTH", &B_JETNOMU3JETWIDTH, &b_B_JETNOMU3JETWIDTH);
   fChain->SetBranchAddress("B_JETNOMU3NNTAG", &B_JETNOMU3NNTAG, &b_B_JETNOMU3NNTAG);
   fChain->SetBranchAddress("B_JETNOMU3MNF", &B_JETNOMU3MNF, &b_B_JETNOMU3MNF);
   fChain->SetBranchAddress("B_JETMU1PX", &B_JETMU1PX, &b_B_JETMU1PX);
   fChain->SetBranchAddress("B_JETMU1PY", &B_JETMU1PY, &b_B_JETMU1PY);
   fChain->SetBranchAddress("B_JETMU1PZ", &B_JETMU1PZ, &b_B_JETMU1PZ);
   fChain->SetBranchAddress("B_JETMU1PT", &B_JETMU1PT, &b_B_JETMU1PT);
   fChain->SetBranchAddress("B_JETMU1JETWIDTH", &B_JETMU1JETWIDTH, &b_B_JETMU1JETWIDTH);
   fChain->SetBranchAddress("B_JETMU1NNTAG", &B_JETMU1NNTAG, &b_B_JETMU1NNTAG);
   fChain->SetBranchAddress("B_JETMU1MNF", &B_JETMU1MNF, &b_B_JETMU1MNF);
   fChain->SetBranchAddress("B_JETBPX", &B_JETBPX, &b_B_JETBPX);
   fChain->SetBranchAddress("B_JETBPY", &B_JETBPY, &b_B_JETBPY);
   fChain->SetBranchAddress("B_JETBPZ", &B_JETBPZ, &b_B_JETBPZ);
   fChain->SetBranchAddress("B_JETBPT", &B_JETBPT, &b_B_JETBPT);
   fChain->SetBranchAddress("B_JETBJETWIDTH", &B_JETBJETWIDTH, &b_B_JETBJETWIDTH);
   fChain->SetBranchAddress("B_JETBNNTAG", &B_JETBNNTAG, &b_B_JETBNNTAG);
   fChain->SetBranchAddress("B_JETBMNF", &B_JETBMNF, &b_B_JETBMNF);
   fChain->SetBranchAddress("B_JETMU2PX", &B_JETMU2PX, &b_B_JETMU2PX);
   fChain->SetBranchAddress("B_JETMU2PY", &B_JETMU2PY, &b_B_JETMU2PY);
   fChain->SetBranchAddress("B_JETMU2PZ", &B_JETMU2PZ, &b_B_JETMU2PZ);
   fChain->SetBranchAddress("B_JETMU2PT", &B_JETMU2PT, &b_B_JETMU2PT);
   fChain->SetBranchAddress("B_JETMU2JETWIDTH", &B_JETMU2JETWIDTH, &b_B_JETMU2JETWIDTH);
   fChain->SetBranchAddress("B_JETMU2NNTAG", &B_JETMU2NNTAG, &b_B_JETMU2NNTAG);
   fChain->SetBranchAddress("B_JETMU2MNF", &B_JETMU2MNF, &b_B_JETMU2MNF);
   fChain->SetBranchAddress("muplus_BPVDIRA", &muplus_BPVDIRA, &b_muplus_BPVDIRA);
   fChain->SetBranchAddress("muplus_BPVIPCHI2", &muplus_BPVIPCHI2, &b_muplus_BPVIPCHI2);
   fChain->SetBranchAddress("muplus_BPVVDCHI2", &muplus_BPVVDCHI2, &b_muplus_BPVVDCHI2);
   fChain->SetBranchAddress("muplus_BPVVDZ", &muplus_BPVVDZ, &b_muplus_BPVVDZ);
   fChain->SetBranchAddress("muplus_DOCAMAX", &muplus_DOCAMAX, &b_muplus_DOCAMAX);
   fChain->SetBranchAddress("muplus_MINIPCHI2", &muplus_MINIPCHI2, &b_muplus_MINIPCHI2);
   fChain->SetBranchAddress("muplus_VFASPF", &muplus_VFASPF, &b_muplus_VFASPF);
   fChain->SetBranchAddress("muplus_MC12TuneV2_ProbNNe", &muplus_MC12TuneV2_ProbNNe, &b_muplus_MC12TuneV2_ProbNNe);
   fChain->SetBranchAddress("muplus_MC12TuneV2_ProbNNmu", &muplus_MC12TuneV2_ProbNNmu, &b_muplus_MC12TuneV2_ProbNNmu);
   fChain->SetBranchAddress("muplus_MC12TuneV2_ProbNNpi", &muplus_MC12TuneV2_ProbNNpi, &b_muplus_MC12TuneV2_ProbNNpi);
   fChain->SetBranchAddress("muplus_MC12TuneV2_ProbNNk", &muplus_MC12TuneV2_ProbNNk, &b_muplus_MC12TuneV2_ProbNNk);
   fChain->SetBranchAddress("muplus_MC12TuneV2_ProbNNp", &muplus_MC12TuneV2_ProbNNp, &b_muplus_MC12TuneV2_ProbNNp);
   fChain->SetBranchAddress("muplus_MC12TuneV2_ProbNNghost", &muplus_MC12TuneV2_ProbNNghost, &b_muplus_MC12TuneV2_ProbNNghost);
   fChain->SetBranchAddress("muplus_MC12TuneV3_ProbNNe", &muplus_MC12TuneV3_ProbNNe, &b_muplus_MC12TuneV3_ProbNNe);
   fChain->SetBranchAddress("muplus_MC12TuneV3_ProbNNmu", &muplus_MC12TuneV3_ProbNNmu, &b_muplus_MC12TuneV3_ProbNNmu);
   fChain->SetBranchAddress("muplus_MC12TuneV3_ProbNNpi", &muplus_MC12TuneV3_ProbNNpi, &b_muplus_MC12TuneV3_ProbNNpi);
   fChain->SetBranchAddress("muplus_MC12TuneV3_ProbNNk", &muplus_MC12TuneV3_ProbNNk, &b_muplus_MC12TuneV3_ProbNNk);
   fChain->SetBranchAddress("muplus_MC12TuneV3_ProbNNp", &muplus_MC12TuneV3_ProbNNp, &b_muplus_MC12TuneV3_ProbNNp);
   fChain->SetBranchAddress("muplus_MC12TuneV3_ProbNNghost", &muplus_MC12TuneV3_ProbNNghost, &b_muplus_MC12TuneV3_ProbNNghost);
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
   fChain->SetBranchAddress("muplus_Xs1", &muplus_Xs1, &b_muplus_Xs1);
   fChain->SetBranchAddress("muplus_Ys1", &muplus_Ys1, &b_muplus_Ys1);
   fChain->SetBranchAddress("muplus_Xs2", &muplus_Xs2, &b_muplus_Xs2);
   fChain->SetBranchAddress("muplus_Ys2", &muplus_Ys2, &b_muplus_Ys2);
   fChain->SetBranchAddress("muplus_Xs3", &muplus_Xs3, &b_muplus_Xs3);
   fChain->SetBranchAddress("muplus_Ys3", &muplus_Ys3, &b_muplus_Ys3);
   fChain->SetBranchAddress("muplus_Xs4", &muplus_Xs4, &b_muplus_Xs4);
   fChain->SetBranchAddress("muplus_Ys4", &muplus_Ys4, &b_muplus_Ys4);
   fChain->SetBranchAddress("muplus_Xs5", &muplus_Xs5, &b_muplus_Xs5);
   fChain->SetBranchAddress("muplus_Ys5", &muplus_Ys5, &b_muplus_Ys5);
   fChain->SetBranchAddress("muplus_DistAve", &muplus_DistAve, &b_muplus_DistAve);
   fChain->SetBranchAddress("muplus_ID", &muplus_ID, &b_muplus_ID);
   fChain->SetBranchAddress("muplus_CombDLLMu", &muplus_CombDLLMu, &b_muplus_CombDLLMu);
   fChain->SetBranchAddress("muplus_ProbNNmu", &muplus_ProbNNmu, &b_muplus_ProbNNmu);
   fChain->SetBranchAddress("muplus_ProbNNghost", &muplus_ProbNNghost, &b_muplus_ProbNNghost);
   fChain->SetBranchAddress("muplus_InMuonAcc", &muplus_InMuonAcc, &b_muplus_InMuonAcc);
   fChain->SetBranchAddress("muplus_MuonDist2", &muplus_MuonDist2, &b_muplus_MuonDist2);
   fChain->SetBranchAddress("muplus_regionInM2", &muplus_regionInM2, &b_muplus_regionInM2);
   fChain->SetBranchAddress("muplus_hasMuon", &muplus_hasMuon, &b_muplus_hasMuon);
   fChain->SetBranchAddress("muplus_isMuon", &muplus_isMuon, &b_muplus_isMuon);
   fChain->SetBranchAddress("muplus_isMuonLoose", &muplus_isMuonLoose, &b_muplus_isMuonLoose);
   fChain->SetBranchAddress("muplus_NShared", &muplus_NShared, &b_muplus_NShared);
   fChain->SetBranchAddress("muplus_MuonLLmu", &muplus_MuonLLmu, &b_muplus_MuonLLmu);
   fChain->SetBranchAddress("muplus_MuonLLbg", &muplus_MuonLLbg, &b_muplus_MuonLLbg);
   fChain->SetBranchAddress("muplus_isMuonFromProto", &muplus_isMuonFromProto, &b_muplus_isMuonFromProto);
   fChain->SetBranchAddress("muplus_nVeloIDs", &muplus_nVeloIDs, &b_muplus_nVeloIDs);
   fChain->SetBranchAddress("muplus_nITIDs", &muplus_nITIDs, &b_muplus_nITIDs);
   fChain->SetBranchAddress("muplus_nTTIDs", &muplus_nTTIDs, &b_muplus_nTTIDs);
   fChain->SetBranchAddress("muplus_nOTIDs", &muplus_nOTIDs, &b_muplus_nOTIDs);
   fChain->SetBranchAddress("muplus_eta", &muplus_eta, &b_muplus_eta);
   fChain->SetBranchAddress("muplus_phi", &muplus_phi, &b_muplus_phi);
   fChain->SetBranchAddress("muplus_typeOriginVtx", &muplus_typeOriginVtx, &b_muplus_typeOriginVtx);
   fChain->SetBranchAddress("muplus_nEndVertices", &muplus_nEndVertices, &b_muplus_nEndVertices);
   fChain->SetBranchAddress("muplus_ancestorpid", &muplus_ancestorpid, &b_muplus_ancestorpid);
   fChain->SetBranchAddress("muplus_MCI", &muplus_MCI, &b_muplus_MCI);
   fChain->SetBranchAddress("muplus_PIDe", &muplus_PIDe, &b_muplus_PIDe);
   fChain->SetBranchAddress("muplus_PIDmu", &muplus_PIDmu, &b_muplus_PIDmu);
   fChain->SetBranchAddress("muplus_PIDK", &muplus_PIDK, &b_muplus_PIDK);
   fChain->SetBranchAddress("muplus_PIDp", &muplus_PIDp, &b_muplus_PIDp);
   fChain->SetBranchAddress("muplus_ProbNNe", &muplus_ProbNNe, &b_muplus_ProbNNe);
   fChain->SetBranchAddress("muplus_ProbNNk", &muplus_ProbNNk, &b_muplus_ProbNNk);
   fChain->SetBranchAddress("muplus_ProbNNp", &muplus_ProbNNp, &b_muplus_ProbNNp);
   fChain->SetBranchAddress("muplus_ProbNNpi", &muplus_ProbNNpi, &b_muplus_ProbNNpi);
   fChain->SetBranchAddress("muplus_hasRich", &muplus_hasRich, &b_muplus_hasRich);
   fChain->SetBranchAddress("muplus_hasCalo", &muplus_hasCalo, &b_muplus_hasCalo);
   fChain->SetBranchAddress("muplus_L0Global_Dec", &muplus_L0Global_Dec, &b_muplus_L0Global_Dec);
   fChain->SetBranchAddress("muplus_L0Global_TIS", &muplus_L0Global_TIS, &b_muplus_L0Global_TIS);
   fChain->SetBranchAddress("muplus_L0Global_TOS", &muplus_L0Global_TOS, &b_muplus_L0Global_TOS);
   fChain->SetBranchAddress("muplus_Hlt1Global_Dec", &muplus_Hlt1Global_Dec, &b_muplus_Hlt1Global_Dec);
   fChain->SetBranchAddress("muplus_Hlt1Global_TIS", &muplus_Hlt1Global_TIS, &b_muplus_Hlt1Global_TIS);
   fChain->SetBranchAddress("muplus_Hlt1Global_TOS", &muplus_Hlt1Global_TOS, &b_muplus_Hlt1Global_TOS);
   fChain->SetBranchAddress("muplus_Hlt1Phys_Dec", &muplus_Hlt1Phys_Dec, &b_muplus_Hlt1Phys_Dec);
   fChain->SetBranchAddress("muplus_Hlt1Phys_TIS", &muplus_Hlt1Phys_TIS, &b_muplus_Hlt1Phys_TIS);
   fChain->SetBranchAddress("muplus_Hlt1Phys_TOS", &muplus_Hlt1Phys_TOS, &b_muplus_Hlt1Phys_TOS);
   fChain->SetBranchAddress("muplus_Hlt2Global_Dec", &muplus_Hlt2Global_Dec, &b_muplus_Hlt2Global_Dec);
   fChain->SetBranchAddress("muplus_Hlt2Global_TIS", &muplus_Hlt2Global_TIS, &b_muplus_Hlt2Global_TIS);
   fChain->SetBranchAddress("muplus_Hlt2Global_TOS", &muplus_Hlt2Global_TOS, &b_muplus_Hlt2Global_TOS);
   fChain->SetBranchAddress("muplus_Hlt2Phys_Dec", &muplus_Hlt2Phys_Dec, &b_muplus_Hlt2Phys_Dec);
   fChain->SetBranchAddress("muplus_Hlt2Phys_TIS", &muplus_Hlt2Phys_TIS, &b_muplus_Hlt2Phys_TIS);
   fChain->SetBranchAddress("muplus_Hlt2Phys_TOS", &muplus_Hlt2Phys_TOS, &b_muplus_Hlt2Phys_TOS);
   fChain->SetBranchAddress("muplus_L0MuonDecision_Dec", &muplus_L0MuonDecision_Dec, &b_muplus_L0MuonDecision_Dec);
   fChain->SetBranchAddress("muplus_L0MuonDecision_TIS", &muplus_L0MuonDecision_TIS, &b_muplus_L0MuonDecision_TIS);
   fChain->SetBranchAddress("muplus_L0MuonDecision_TOS", &muplus_L0MuonDecision_TOS, &b_muplus_L0MuonDecision_TOS);
   fChain->SetBranchAddress("muplus_L0DiMuonDecision_Dec", &muplus_L0DiMuonDecision_Dec, &b_muplus_L0DiMuonDecision_Dec);
   fChain->SetBranchAddress("muplus_L0DiMuonDecision_TIS", &muplus_L0DiMuonDecision_TIS, &b_muplus_L0DiMuonDecision_TIS);
   fChain->SetBranchAddress("muplus_L0DiMuonDecision_TOS", &muplus_L0DiMuonDecision_TOS, &b_muplus_L0DiMuonDecision_TOS);
   fChain->SetBranchAddress("muplus_L0HadronDecision_Dec", &muplus_L0HadronDecision_Dec, &b_muplus_L0HadronDecision_Dec);
   fChain->SetBranchAddress("muplus_L0HadronDecision_TIS", &muplus_L0HadronDecision_TIS, &b_muplus_L0HadronDecision_TIS);
   fChain->SetBranchAddress("muplus_L0HadronDecision_TOS", &muplus_L0HadronDecision_TOS, &b_muplus_L0HadronDecision_TOS);
   fChain->SetBranchAddress("muplus_L0ElectronDecision_Dec", &muplus_L0ElectronDecision_Dec, &b_muplus_L0ElectronDecision_Dec);
   fChain->SetBranchAddress("muplus_L0ElectronDecision_TIS", &muplus_L0ElectronDecision_TIS, &b_muplus_L0ElectronDecision_TIS);
   fChain->SetBranchAddress("muplus_L0ElectronDecision_TOS", &muplus_L0ElectronDecision_TOS, &b_muplus_L0ElectronDecision_TOS);
   fChain->SetBranchAddress("muplus_L0ElectronHiDecision_Dec", &muplus_L0ElectronHiDecision_Dec, &b_muplus_L0ElectronHiDecision_Dec);
   fChain->SetBranchAddress("muplus_L0ElectronHiDecision_TIS", &muplus_L0ElectronHiDecision_TIS, &b_muplus_L0ElectronHiDecision_TIS);
   fChain->SetBranchAddress("muplus_L0ElectronHiDecision_TOS", &muplus_L0ElectronHiDecision_TOS, &b_muplus_L0ElectronHiDecision_TOS);
   fChain->SetBranchAddress("muplus_L0PhotonDecision_Dec", &muplus_L0PhotonDecision_Dec, &b_muplus_L0PhotonDecision_Dec);
   fChain->SetBranchAddress("muplus_L0PhotonDecision_TIS", &muplus_L0PhotonDecision_TIS, &b_muplus_L0PhotonDecision_TIS);
   fChain->SetBranchAddress("muplus_L0PhotonDecision_TOS", &muplus_L0PhotonDecision_TOS, &b_muplus_L0PhotonDecision_TOS);
   fChain->SetBranchAddress("muplus_L0PhotonHiDecision_Dec", &muplus_L0PhotonHiDecision_Dec, &b_muplus_L0PhotonHiDecision_Dec);
   fChain->SetBranchAddress("muplus_L0PhotonHiDecision_TIS", &muplus_L0PhotonHiDecision_TIS, &b_muplus_L0PhotonHiDecision_TIS);
   fChain->SetBranchAddress("muplus_L0PhotonHiDecision_TOS", &muplus_L0PhotonHiDecision_TOS, &b_muplus_L0PhotonHiDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt1SingleMuonNoIPDecision_Dec", &muplus_Hlt1SingleMuonNoIPDecision_Dec, &b_muplus_Hlt1SingleMuonNoIPDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt1SingleMuonNoIPDecision_TIS", &muplus_Hlt1SingleMuonNoIPDecision_TIS, &b_muplus_Hlt1SingleMuonNoIPDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt1SingleMuonNoIPDecision_TOS", &muplus_Hlt1SingleMuonNoIPDecision_TOS, &b_muplus_Hlt1SingleMuonNoIPDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt1SingleMuonHighPTDecision_Dec", &muplus_Hlt1SingleMuonHighPTDecision_Dec, &b_muplus_Hlt1SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt1SingleMuonHighPTDecision_TIS", &muplus_Hlt1SingleMuonHighPTDecision_TIS, &b_muplus_Hlt1SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt1SingleMuonHighPTDecision_TOS", &muplus_Hlt1SingleMuonHighPTDecision_TOS, &b_muplus_Hlt1SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt1SingleElectronNoIPDecision_Dec", &muplus_Hlt1SingleElectronNoIPDecision_Dec, &b_muplus_Hlt1SingleElectronNoIPDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt1SingleElectronNoIPDecision_TIS", &muplus_Hlt1SingleElectronNoIPDecision_TIS, &b_muplus_Hlt1SingleElectronNoIPDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt1SingleElectronNoIPDecision_TOS", &muplus_Hlt1SingleElectronNoIPDecision_TOS, &b_muplus_Hlt1SingleElectronNoIPDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt1TrackAllL0Decision_Dec", &muplus_Hlt1TrackAllL0Decision_Dec, &b_muplus_Hlt1TrackAllL0Decision_Dec);
   fChain->SetBranchAddress("muplus_Hlt1TrackAllL0Decision_TIS", &muplus_Hlt1TrackAllL0Decision_TIS, &b_muplus_Hlt1TrackAllL0Decision_TIS);
   fChain->SetBranchAddress("muplus_Hlt1TrackAllL0Decision_TOS", &muplus_Hlt1TrackAllL0Decision_TOS, &b_muplus_Hlt1TrackAllL0Decision_TOS);
   fChain->SetBranchAddress("muplus_Hlt1TrackMuonDecision_Dec", &muplus_Hlt1TrackMuonDecision_Dec, &b_muplus_Hlt1TrackMuonDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt1TrackMuonDecision_TIS", &muplus_Hlt1TrackMuonDecision_TIS, &b_muplus_Hlt1TrackMuonDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt1TrackMuonDecision_TOS", &muplus_Hlt1TrackMuonDecision_TOS, &b_muplus_Hlt1TrackMuonDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt1TrackPhotonDecision_Dec", &muplus_Hlt1TrackPhotonDecision_Dec, &b_muplus_Hlt1TrackPhotonDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt1TrackPhotonDecision_TIS", &muplus_Hlt1TrackPhotonDecision_TIS, &b_muplus_Hlt1TrackPhotonDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt1TrackPhotonDecision_TOS", &muplus_Hlt1TrackPhotonDecision_TOS, &b_muplus_Hlt1TrackPhotonDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt1TrackAllL0__Decision_Dec", &muplus_Hlt1TrackAllL0__Decision_Dec, &b_muplus_Hlt1TrackAllL0__Decision_Dec);
   fChain->SetBranchAddress("muplus_Hlt1TrackAllL0__Decision_TIS", &muplus_Hlt1TrackAllL0__Decision_TIS, &b_muplus_Hlt1TrackAllL0__Decision_TIS);
   fChain->SetBranchAddress("muplus_Hlt1TrackAllL0__Decision_TOS", &muplus_Hlt1TrackAllL0__Decision_TOS, &b_muplus_Hlt1TrackAllL0__Decision_TOS);
   fChain->SetBranchAddress("muplus_Hlt1DiMuonLowMassDecision_Dec", &muplus_Hlt1DiMuonLowMassDecision_Dec, &b_muplus_Hlt1DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt1DiMuonLowMassDecision_TIS", &muplus_Hlt1DiMuonLowMassDecision_TIS, &b_muplus_Hlt1DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt1DiMuonLowMassDecision_TOS", &muplus_Hlt1DiMuonLowMassDecision_TOS, &b_muplus_Hlt1DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt1DiMuonHighMassDecision_Dec", &muplus_Hlt1DiMuonHighMassDecision_Dec, &b_muplus_Hlt1DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt1DiMuonHighMassDecision_TIS", &muplus_Hlt1DiMuonHighMassDecision_TIS, &b_muplus_Hlt1DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt1DiMuonHighMassDecision_TOS", &muplus_Hlt1DiMuonHighMassDecision_TOS, &b_muplus_Hlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt1MB__Decision_Dec", &muplus_Hlt1MB__Decision_Dec, &b_muplus_Hlt1MB__Decision_Dec);
   fChain->SetBranchAddress("muplus_Hlt1MB__Decision_TIS", &muplus_Hlt1MB__Decision_TIS, &b_muplus_Hlt1MB__Decision_TIS);
   fChain->SetBranchAddress("muplus_Hlt1MB__Decision_TOS", &muplus_Hlt1MB__Decision_TOS, &b_muplus_Hlt1MB__Decision_TOS);
   fChain->SetBranchAddress("muplus_Hlt1TrackAllL0TightDecision_Dec", &muplus_Hlt1TrackAllL0TightDecision_Dec, &b_muplus_Hlt1TrackAllL0TightDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt1TrackAllL0TightDecision_TIS", &muplus_Hlt1TrackAllL0TightDecision_TIS, &b_muplus_Hlt1TrackAllL0TightDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt1TrackAllL0TightDecision_TOS", &muplus_Hlt1TrackAllL0TightDecision_TOS, &b_muplus_Hlt1TrackAllL0TightDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2SingleMuonDecision_Dec", &muplus_Hlt2SingleMuonDecision_Dec, &b_muplus_Hlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2SingleMuonDecision_TIS", &muplus_Hlt2SingleMuonDecision_TIS, &b_muplus_Hlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2SingleMuonDecision_TOS", &muplus_Hlt2SingleMuonDecision_TOS, &b_muplus_Hlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2SingleMuonLowPTDecision_Dec", &muplus_Hlt2SingleMuonLowPTDecision_Dec, &b_muplus_Hlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2SingleMuonLowPTDecision_TIS", &muplus_Hlt2SingleMuonLowPTDecision_TIS, &b_muplus_Hlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2SingleMuonLowPTDecision_TOS", &muplus_Hlt2SingleMuonLowPTDecision_TOS, &b_muplus_Hlt2SingleMuonLowPTDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2SingleMuonHighPTDecision_Dec", &muplus_Hlt2SingleMuonHighPTDecision_Dec, &b_muplus_Hlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2SingleMuonHighPTDecision_TIS", &muplus_Hlt2SingleMuonHighPTDecision_TIS, &b_muplus_Hlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2SingleMuonHighPTDecision_TOS", &muplus_Hlt2SingleMuonHighPTDecision_TOS, &b_muplus_Hlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonDecision_Dec", &muplus_Hlt2DiMuonDecision_Dec, &b_muplus_Hlt2DiMuonDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonDecision_TIS", &muplus_Hlt2DiMuonDecision_TIS, &b_muplus_Hlt2DiMuonDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonDecision_TOS", &muplus_Hlt2DiMuonDecision_TOS, &b_muplus_Hlt2DiMuonDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonLowMassDecision_Dec", &muplus_Hlt2DiMuonLowMassDecision_Dec, &b_muplus_Hlt2DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonLowMassDecision_TIS", &muplus_Hlt2DiMuonLowMassDecision_TIS, &b_muplus_Hlt2DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonLowMassDecision_TOS", &muplus_Hlt2DiMuonLowMassDecision_TOS, &b_muplus_Hlt2DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonJPsiDecision_Dec", &muplus_Hlt2DiMuonJPsiDecision_Dec, &b_muplus_Hlt2DiMuonJPsiDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonJPsiDecision_TIS", &muplus_Hlt2DiMuonJPsiDecision_TIS, &b_muplus_Hlt2DiMuonJPsiDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonJPsiDecision_TOS", &muplus_Hlt2DiMuonJPsiDecision_TOS, &b_muplus_Hlt2DiMuonJPsiDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonJPsiHighPTDecision_Dec", &muplus_Hlt2DiMuonJPsiHighPTDecision_Dec, &b_muplus_Hlt2DiMuonJPsiHighPTDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonJPsiHighPTDecision_TIS", &muplus_Hlt2DiMuonJPsiHighPTDecision_TIS, &b_muplus_Hlt2DiMuonJPsiHighPTDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonJPsiHighPTDecision_TOS", &muplus_Hlt2DiMuonJPsiHighPTDecision_TOS, &b_muplus_Hlt2DiMuonJPsiHighPTDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonPsi2SDecision_Dec", &muplus_Hlt2DiMuonPsi2SDecision_Dec, &b_muplus_Hlt2DiMuonPsi2SDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonPsi2SDecision_TIS", &muplus_Hlt2DiMuonPsi2SDecision_TIS, &b_muplus_Hlt2DiMuonPsi2SDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonPsi2SDecision_TOS", &muplus_Hlt2DiMuonPsi2SDecision_TOS, &b_muplus_Hlt2DiMuonPsi2SDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonDetachedDecision_Dec", &muplus_Hlt2DiMuonDetachedDecision_Dec, &b_muplus_Hlt2DiMuonDetachedDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonDetachedDecision_TIS", &muplus_Hlt2DiMuonDetachedDecision_TIS, &b_muplus_Hlt2DiMuonDetachedDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonDetachedDecision_TOS", &muplus_Hlt2DiMuonDetachedDecision_TOS, &b_muplus_Hlt2DiMuonDetachedDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonDetachedJPsiDecision_Dec", &muplus_Hlt2DiMuonDetachedJPsiDecision_Dec, &b_muplus_Hlt2DiMuonDetachedJPsiDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonDetachedJPsiDecision_TIS", &muplus_Hlt2DiMuonDetachedJPsiDecision_TIS, &b_muplus_Hlt2DiMuonDetachedJPsiDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonDetachedJPsiDecision_TOS", &muplus_Hlt2DiMuonDetachedJPsiDecision_TOS, &b_muplus_Hlt2DiMuonDetachedJPsiDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonDetachedHeavyDecision_Dec", &muplus_Hlt2DiMuonDetachedHeavyDecision_Dec, &b_muplus_Hlt2DiMuonDetachedHeavyDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonDetachedHeavyDecision_TIS", &muplus_Hlt2DiMuonDetachedHeavyDecision_TIS, &b_muplus_Hlt2DiMuonDetachedHeavyDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonDetachedHeavyDecision_TOS", &muplus_Hlt2DiMuonDetachedHeavyDecision_TOS, &b_muplus_Hlt2DiMuonDetachedHeavyDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2TriMuonTauDecision_Dec", &muplus_Hlt2TriMuonTauDecision_Dec, &b_muplus_Hlt2TriMuonTauDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2TriMuonTauDecision_TIS", &muplus_Hlt2TriMuonTauDecision_TIS, &b_muplus_Hlt2TriMuonTauDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2TriMuonTauDecision_TOS", &muplus_Hlt2TriMuonTauDecision_TOS, &b_muplus_Hlt2TriMuonTauDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2B2HHDecision_Dec", &muplus_Hlt2B2HHDecision_Dec, &b_muplus_Hlt2B2HHDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2B2HHDecision_TIS", &muplus_Hlt2B2HHDecision_TIS, &b_muplus_Hlt2B2HHDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2B2HHDecision_TOS", &muplus_Hlt2B2HHDecision_TOS, &b_muplus_Hlt2B2HHDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonBDecision_Dec", &muplus_Hlt2DiMuonBDecision_Dec, &b_muplus_Hlt2DiMuonBDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonBDecision_TIS", &muplus_Hlt2DiMuonBDecision_TIS, &b_muplus_Hlt2DiMuonBDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonBDecision_TOS", &muplus_Hlt2DiMuonBDecision_TOS, &b_muplus_Hlt2DiMuonBDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonZDecision_Dec", &muplus_Hlt2DiMuonZDecision_Dec, &b_muplus_Hlt2DiMuonZDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonZDecision_TIS", &muplus_Hlt2DiMuonZDecision_TIS, &b_muplus_Hlt2DiMuonZDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonZDecision_TOS", &muplus_Hlt2DiMuonZDecision_TOS, &b_muplus_Hlt2DiMuonZDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2TopoMu2BodyBBDTDecision_Dec", &muplus_Hlt2TopoMu2BodyBBDTDecision_Dec, &b_muplus_Hlt2TopoMu2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2TopoMu2BodyBBDTDecision_TIS", &muplus_Hlt2TopoMu2BodyBBDTDecision_TIS, &b_muplus_Hlt2TopoMu2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2TopoMu2BodyBBDTDecision_TOS", &muplus_Hlt2TopoMu2BodyBBDTDecision_TOS, &b_muplus_Hlt2TopoMu2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2TopoMu3BodyBBDTDecision_Dec", &muplus_Hlt2TopoMu3BodyBBDTDecision_Dec, &b_muplus_Hlt2TopoMu3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2TopoMu3BodyBBDTDecision_TIS", &muplus_Hlt2TopoMu3BodyBBDTDecision_TIS, &b_muplus_Hlt2TopoMu3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2TopoMu3BodyBBDTDecision_TOS", &muplus_Hlt2TopoMu3BodyBBDTDecision_TOS, &b_muplus_Hlt2TopoMu3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2TopoMu4BodyBBDTDecision_Dec", &muplus_Hlt2TopoMu4BodyBBDTDecision_Dec, &b_muplus_Hlt2TopoMu4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2TopoMu4BodyBBDTDecision_TIS", &muplus_Hlt2TopoMu4BodyBBDTDecision_TIS, &b_muplus_Hlt2TopoMu4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2TopoMu4BodyBBDTDecision_TOS", &muplus_Hlt2TopoMu4BodyBBDTDecision_TOS, &b_muplus_Hlt2TopoMu4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2Topo2BodyBBDTDecision_Dec", &muplus_Hlt2Topo2BodyBBDTDecision_Dec, &b_muplus_Hlt2Topo2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2Topo2BodyBBDTDecision_TIS", &muplus_Hlt2Topo2BodyBBDTDecision_TIS, &b_muplus_Hlt2Topo2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2Topo2BodyBBDTDecision_TOS", &muplus_Hlt2Topo2BodyBBDTDecision_TOS, &b_muplus_Hlt2Topo2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2Topo3BodyBBDTDecision_Dec", &muplus_Hlt2Topo3BodyBBDTDecision_Dec, &b_muplus_Hlt2Topo3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2Topo3BodyBBDTDecision_TIS", &muplus_Hlt2Topo3BodyBBDTDecision_TIS, &b_muplus_Hlt2Topo3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2Topo3BodyBBDTDecision_TOS", &muplus_Hlt2Topo3BodyBBDTDecision_TOS, &b_muplus_Hlt2Topo3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2Topo4BodyBBDTDecision_Dec", &muplus_Hlt2Topo4BodyBBDTDecision_Dec, &b_muplus_Hlt2Topo4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2Topo4BodyBBDTDecision_TIS", &muplus_Hlt2Topo4BodyBBDTDecision_TIS, &b_muplus_Hlt2Topo4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2Topo4BodyBBDTDecision_TOS", &muplus_Hlt2Topo4BodyBBDTDecision_TOS, &b_muplus_Hlt2Topo4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2Topo2BodySimpleDecision_Dec", &muplus_Hlt2Topo2BodySimpleDecision_Dec, &b_muplus_Hlt2Topo2BodySimpleDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2Topo2BodySimpleDecision_TIS", &muplus_Hlt2Topo2BodySimpleDecision_TIS, &b_muplus_Hlt2Topo2BodySimpleDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2Topo2BodySimpleDecision_TOS", &muplus_Hlt2Topo2BodySimpleDecision_TOS, &b_muplus_Hlt2Topo2BodySimpleDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2Topo3BodySimpleDecision_Dec", &muplus_Hlt2Topo3BodySimpleDecision_Dec, &b_muplus_Hlt2Topo3BodySimpleDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2Topo3BodySimpleDecision_TIS", &muplus_Hlt2Topo3BodySimpleDecision_TIS, &b_muplus_Hlt2Topo3BodySimpleDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2Topo3BodySimpleDecision_TOS", &muplus_Hlt2Topo3BodySimpleDecision_TOS, &b_muplus_Hlt2Topo3BodySimpleDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2Topo4BodySimpleDecision_Dec", &muplus_Hlt2Topo4BodySimpleDecision_Dec, &b_muplus_Hlt2Topo4BodySimpleDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2Topo4BodySimpleDecision_TIS", &muplus_Hlt2Topo4BodySimpleDecision_TIS, &b_muplus_Hlt2Topo4BodySimpleDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2Topo4BodySimpleDecision_TOS", &muplus_Hlt2Topo4BodySimpleDecision_TOS, &b_muplus_Hlt2Topo4BodySimpleDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2PassThroughDecision_Dec", &muplus_Hlt2PassThroughDecision_Dec, &b_muplus_Hlt2PassThroughDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2PassThroughDecision_TIS", &muplus_Hlt2PassThroughDecision_TIS, &b_muplus_Hlt2PassThroughDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2PassThroughDecision_TOS", &muplus_Hlt2PassThroughDecision_TOS, &b_muplus_Hlt2PassThroughDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2TransparentDecision_Dec", &muplus_Hlt2TransparentDecision_Dec, &b_muplus_Hlt2TransparentDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2TransparentDecision_TIS", &muplus_Hlt2TransparentDecision_TIS, &b_muplus_Hlt2TransparentDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2TransparentDecision_TOS", &muplus_Hlt2TransparentDecision_TOS, &b_muplus_Hlt2TransparentDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2IncPhiDecision_Dec", &muplus_Hlt2IncPhiDecision_Dec, &b_muplus_Hlt2IncPhiDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2IncPhiDecision_TIS", &muplus_Hlt2IncPhiDecision_TIS, &b_muplus_Hlt2IncPhiDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2IncPhiDecision_TOS", &muplus_Hlt2IncPhiDecision_TOS, &b_muplus_Hlt2IncPhiDecision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonDY__Decision_Dec", &muplus_Hlt2DiMuonDY__Decision_Dec, &b_muplus_Hlt2DiMuonDY__Decision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonDY__Decision_TIS", &muplus_Hlt2DiMuonDY__Decision_TIS, &b_muplus_Hlt2DiMuonDY__Decision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2DiMuonDY__Decision_TOS", &muplus_Hlt2DiMuonDY__Decision_TOS, &b_muplus_Hlt2DiMuonDY__Decision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2TopoE__Decision_Dec", &muplus_Hlt2TopoE__Decision_Dec, &b_muplus_Hlt2TopoE__Decision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2TopoE__Decision_TIS", &muplus_Hlt2TopoE__Decision_TIS, &b_muplus_Hlt2TopoE__Decision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2TopoE__Decision_TOS", &muplus_Hlt2TopoE__Decision_TOS, &b_muplus_Hlt2TopoE__Decision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2Topo__Decision_Dec", &muplus_Hlt2Topo__Decision_Dec, &b_muplus_Hlt2Topo__Decision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2Topo__Decision_TIS", &muplus_Hlt2Topo__Decision_TIS, &b_muplus_Hlt2Topo__Decision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2Topo__Decision_TOS", &muplus_Hlt2Topo__Decision_TOS, &b_muplus_Hlt2Topo__Decision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2Charm__Decision_Dec", &muplus_Hlt2Charm__Decision_Dec, &b_muplus_Hlt2Charm__Decision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2Charm__Decision_TIS", &muplus_Hlt2Charm__Decision_TIS, &b_muplus_Hlt2Charm__Decision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2Charm__Decision_TOS", &muplus_Hlt2Charm__Decision_TOS, &b_muplus_Hlt2Charm__Decision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2DiElectron__Decision_Dec", &muplus_Hlt2DiElectron__Decision_Dec, &b_muplus_Hlt2DiElectron__Decision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2DiElectron__Decision_TIS", &muplus_Hlt2DiElectron__Decision_TIS, &b_muplus_Hlt2DiElectron__Decision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2DiElectron__Decision_TOS", &muplus_Hlt2DiElectron__Decision_TOS, &b_muplus_Hlt2DiElectron__Decision_TOS);
   fChain->SetBranchAddress("muplus_Hlt2__GammaDecision_Dec", &muplus_Hlt2__GammaDecision_Dec, &b_muplus_Hlt2__GammaDecision_Dec);
   fChain->SetBranchAddress("muplus_Hlt2__GammaDecision_TIS", &muplus_Hlt2__GammaDecision_TIS, &b_muplus_Hlt2__GammaDecision_TIS);
   fChain->SetBranchAddress("muplus_Hlt2__GammaDecision_TOS", &muplus_Hlt2__GammaDecision_TOS, &b_muplus_Hlt2__GammaDecision_TOS);
   fChain->SetBranchAddress("muplus_TRACK_Type", &muplus_TRACK_Type, &b_muplus_TRACK_Type);
   fChain->SetBranchAddress("muplus_TRACK_Key", &muplus_TRACK_Key, &b_muplus_TRACK_Key);
   fChain->SetBranchAddress("muplus_TRACK_CHI2NDOF", &muplus_TRACK_CHI2NDOF, &b_muplus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("muplus_TRACK_PCHI2", &muplus_TRACK_PCHI2, &b_muplus_TRACK_PCHI2);
   fChain->SetBranchAddress("muplus_TRACK_MatchCHI2", &muplus_TRACK_MatchCHI2, &b_muplus_TRACK_MatchCHI2);
   fChain->SetBranchAddress("muplus_TRACK_GhostProb", &muplus_TRACK_GhostProb, &b_muplus_TRACK_GhostProb);
   fChain->SetBranchAddress("muplus_TRACK_CloneDist", &muplus_TRACK_CloneDist, &b_muplus_TRACK_CloneDist);
   fChain->SetBranchAddress("muplus_TRACK_Likelihood", &muplus_TRACK_Likelihood, &b_muplus_TRACK_Likelihood);
   fChain->SetBranchAddress("muminus_BPVDIRA", &muminus_BPVDIRA, &b_muminus_BPVDIRA);
   fChain->SetBranchAddress("muminus_BPVIPCHI2", &muminus_BPVIPCHI2, &b_muminus_BPVIPCHI2);
   fChain->SetBranchAddress("muminus_BPVVDCHI2", &muminus_BPVVDCHI2, &b_muminus_BPVVDCHI2);
   fChain->SetBranchAddress("muminus_BPVVDZ", &muminus_BPVVDZ, &b_muminus_BPVVDZ);
   fChain->SetBranchAddress("muminus_DOCAMAX", &muminus_DOCAMAX, &b_muminus_DOCAMAX);
   fChain->SetBranchAddress("muminus_MINIPCHI2", &muminus_MINIPCHI2, &b_muminus_MINIPCHI2);
   fChain->SetBranchAddress("muminus_VFASPF", &muminus_VFASPF, &b_muminus_VFASPF);
   fChain->SetBranchAddress("muminus_MC12TuneV2_ProbNNe", &muminus_MC12TuneV2_ProbNNe, &b_muminus_MC12TuneV2_ProbNNe);
   fChain->SetBranchAddress("muminus_MC12TuneV2_ProbNNmu", &muminus_MC12TuneV2_ProbNNmu, &b_muminus_MC12TuneV2_ProbNNmu);
   fChain->SetBranchAddress("muminus_MC12TuneV2_ProbNNpi", &muminus_MC12TuneV2_ProbNNpi, &b_muminus_MC12TuneV2_ProbNNpi);
   fChain->SetBranchAddress("muminus_MC12TuneV2_ProbNNk", &muminus_MC12TuneV2_ProbNNk, &b_muminus_MC12TuneV2_ProbNNk);
   fChain->SetBranchAddress("muminus_MC12TuneV2_ProbNNp", &muminus_MC12TuneV2_ProbNNp, &b_muminus_MC12TuneV2_ProbNNp);
   fChain->SetBranchAddress("muminus_MC12TuneV2_ProbNNghost", &muminus_MC12TuneV2_ProbNNghost, &b_muminus_MC12TuneV2_ProbNNghost);
   fChain->SetBranchAddress("muminus_MC12TuneV3_ProbNNe", &muminus_MC12TuneV3_ProbNNe, &b_muminus_MC12TuneV3_ProbNNe);
   fChain->SetBranchAddress("muminus_MC12TuneV3_ProbNNmu", &muminus_MC12TuneV3_ProbNNmu, &b_muminus_MC12TuneV3_ProbNNmu);
   fChain->SetBranchAddress("muminus_MC12TuneV3_ProbNNpi", &muminus_MC12TuneV3_ProbNNpi, &b_muminus_MC12TuneV3_ProbNNpi);
   fChain->SetBranchAddress("muminus_MC12TuneV3_ProbNNk", &muminus_MC12TuneV3_ProbNNk, &b_muminus_MC12TuneV3_ProbNNk);
   fChain->SetBranchAddress("muminus_MC12TuneV3_ProbNNp", &muminus_MC12TuneV3_ProbNNp, &b_muminus_MC12TuneV3_ProbNNp);
   fChain->SetBranchAddress("muminus_MC12TuneV3_ProbNNghost", &muminus_MC12TuneV3_ProbNNghost, &b_muminus_MC12TuneV3_ProbNNghost);
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
   fChain->SetBranchAddress("muminus_Xs1", &muminus_Xs1, &b_muminus_Xs1);
   fChain->SetBranchAddress("muminus_Ys1", &muminus_Ys1, &b_muminus_Ys1);
   fChain->SetBranchAddress("muminus_Xs2", &muminus_Xs2, &b_muminus_Xs2);
   fChain->SetBranchAddress("muminus_Ys2", &muminus_Ys2, &b_muminus_Ys2);
   fChain->SetBranchAddress("muminus_Xs3", &muminus_Xs3, &b_muminus_Xs3);
   fChain->SetBranchAddress("muminus_Ys3", &muminus_Ys3, &b_muminus_Ys3);
   fChain->SetBranchAddress("muminus_Xs4", &muminus_Xs4, &b_muminus_Xs4);
   fChain->SetBranchAddress("muminus_Ys4", &muminus_Ys4, &b_muminus_Ys4);
   fChain->SetBranchAddress("muminus_Xs5", &muminus_Xs5, &b_muminus_Xs5);
   fChain->SetBranchAddress("muminus_Ys5", &muminus_Ys5, &b_muminus_Ys5);
   fChain->SetBranchAddress("muminus_DistAve", &muminus_DistAve, &b_muminus_DistAve);
   fChain->SetBranchAddress("muminus_ID", &muminus_ID, &b_muminus_ID);
   fChain->SetBranchAddress("muminus_CombDLLMu", &muminus_CombDLLMu, &b_muminus_CombDLLMu);
   fChain->SetBranchAddress("muminus_ProbNNmu", &muminus_ProbNNmu, &b_muminus_ProbNNmu);
   fChain->SetBranchAddress("muminus_ProbNNghost", &muminus_ProbNNghost, &b_muminus_ProbNNghost);
   fChain->SetBranchAddress("muminus_InMuonAcc", &muminus_InMuonAcc, &b_muminus_InMuonAcc);
   fChain->SetBranchAddress("muminus_MuonDist2", &muminus_MuonDist2, &b_muminus_MuonDist2);
   fChain->SetBranchAddress("muminus_regionInM2", &muminus_regionInM2, &b_muminus_regionInM2);
   fChain->SetBranchAddress("muminus_hasMuon", &muminus_hasMuon, &b_muminus_hasMuon);
   fChain->SetBranchAddress("muminus_isMuon", &muminus_isMuon, &b_muminus_isMuon);
   fChain->SetBranchAddress("muminus_isMuonLoose", &muminus_isMuonLoose, &b_muminus_isMuonLoose);
   fChain->SetBranchAddress("muminus_NShared", &muminus_NShared, &b_muminus_NShared);
   fChain->SetBranchAddress("muminus_MuonLLmu", &muminus_MuonLLmu, &b_muminus_MuonLLmu);
   fChain->SetBranchAddress("muminus_MuonLLbg", &muminus_MuonLLbg, &b_muminus_MuonLLbg);
   fChain->SetBranchAddress("muminus_isMuonFromProto", &muminus_isMuonFromProto, &b_muminus_isMuonFromProto);
   fChain->SetBranchAddress("muminus_nVeloIDs", &muminus_nVeloIDs, &b_muminus_nVeloIDs);
   fChain->SetBranchAddress("muminus_nITIDs", &muminus_nITIDs, &b_muminus_nITIDs);
   fChain->SetBranchAddress("muminus_nTTIDs", &muminus_nTTIDs, &b_muminus_nTTIDs);
   fChain->SetBranchAddress("muminus_nOTIDs", &muminus_nOTIDs, &b_muminus_nOTIDs);
   fChain->SetBranchAddress("muminus_eta", &muminus_eta, &b_muminus_eta);
   fChain->SetBranchAddress("muminus_phi", &muminus_phi, &b_muminus_phi);
   fChain->SetBranchAddress("muminus_typeOriginVtx", &muminus_typeOriginVtx, &b_muminus_typeOriginVtx);
   fChain->SetBranchAddress("muminus_nEndVertices", &muminus_nEndVertices, &b_muminus_nEndVertices);
   fChain->SetBranchAddress("muminus_ancestorpid", &muminus_ancestorpid, &b_muminus_ancestorpid);
   fChain->SetBranchAddress("muminus_MCI", &muminus_MCI, &b_muminus_MCI);
   fChain->SetBranchAddress("muminus_PIDe", &muminus_PIDe, &b_muminus_PIDe);
   fChain->SetBranchAddress("muminus_PIDmu", &muminus_PIDmu, &b_muminus_PIDmu);
   fChain->SetBranchAddress("muminus_PIDK", &muminus_PIDK, &b_muminus_PIDK);
   fChain->SetBranchAddress("muminus_PIDp", &muminus_PIDp, &b_muminus_PIDp);
   fChain->SetBranchAddress("muminus_ProbNNe", &muminus_ProbNNe, &b_muminus_ProbNNe);
   fChain->SetBranchAddress("muminus_ProbNNk", &muminus_ProbNNk, &b_muminus_ProbNNk);
   fChain->SetBranchAddress("muminus_ProbNNp", &muminus_ProbNNp, &b_muminus_ProbNNp);
   fChain->SetBranchAddress("muminus_ProbNNpi", &muminus_ProbNNpi, &b_muminus_ProbNNpi);
   fChain->SetBranchAddress("muminus_hasRich", &muminus_hasRich, &b_muminus_hasRich);
   fChain->SetBranchAddress("muminus_hasCalo", &muminus_hasCalo, &b_muminus_hasCalo);
   fChain->SetBranchAddress("muminus_L0Global_Dec", &muminus_L0Global_Dec, &b_muminus_L0Global_Dec);
   fChain->SetBranchAddress("muminus_L0Global_TIS", &muminus_L0Global_TIS, &b_muminus_L0Global_TIS);
   fChain->SetBranchAddress("muminus_L0Global_TOS", &muminus_L0Global_TOS, &b_muminus_L0Global_TOS);
   fChain->SetBranchAddress("muminus_Hlt1Global_Dec", &muminus_Hlt1Global_Dec, &b_muminus_Hlt1Global_Dec);
   fChain->SetBranchAddress("muminus_Hlt1Global_TIS", &muminus_Hlt1Global_TIS, &b_muminus_Hlt1Global_TIS);
   fChain->SetBranchAddress("muminus_Hlt1Global_TOS", &muminus_Hlt1Global_TOS, &b_muminus_Hlt1Global_TOS);
   fChain->SetBranchAddress("muminus_Hlt1Phys_Dec", &muminus_Hlt1Phys_Dec, &b_muminus_Hlt1Phys_Dec);
   fChain->SetBranchAddress("muminus_Hlt1Phys_TIS", &muminus_Hlt1Phys_TIS, &b_muminus_Hlt1Phys_TIS);
   fChain->SetBranchAddress("muminus_Hlt1Phys_TOS", &muminus_Hlt1Phys_TOS, &b_muminus_Hlt1Phys_TOS);
   fChain->SetBranchAddress("muminus_Hlt2Global_Dec", &muminus_Hlt2Global_Dec, &b_muminus_Hlt2Global_Dec);
   fChain->SetBranchAddress("muminus_Hlt2Global_TIS", &muminus_Hlt2Global_TIS, &b_muminus_Hlt2Global_TIS);
   fChain->SetBranchAddress("muminus_Hlt2Global_TOS", &muminus_Hlt2Global_TOS, &b_muminus_Hlt2Global_TOS);
   fChain->SetBranchAddress("muminus_Hlt2Phys_Dec", &muminus_Hlt2Phys_Dec, &b_muminus_Hlt2Phys_Dec);
   fChain->SetBranchAddress("muminus_Hlt2Phys_TIS", &muminus_Hlt2Phys_TIS, &b_muminus_Hlt2Phys_TIS);
   fChain->SetBranchAddress("muminus_Hlt2Phys_TOS", &muminus_Hlt2Phys_TOS, &b_muminus_Hlt2Phys_TOS);
   fChain->SetBranchAddress("muminus_L0MuonDecision_Dec", &muminus_L0MuonDecision_Dec, &b_muminus_L0MuonDecision_Dec);
   fChain->SetBranchAddress("muminus_L0MuonDecision_TIS", &muminus_L0MuonDecision_TIS, &b_muminus_L0MuonDecision_TIS);
   fChain->SetBranchAddress("muminus_L0MuonDecision_TOS", &muminus_L0MuonDecision_TOS, &b_muminus_L0MuonDecision_TOS);
   fChain->SetBranchAddress("muminus_L0DiMuonDecision_Dec", &muminus_L0DiMuonDecision_Dec, &b_muminus_L0DiMuonDecision_Dec);
   fChain->SetBranchAddress("muminus_L0DiMuonDecision_TIS", &muminus_L0DiMuonDecision_TIS, &b_muminus_L0DiMuonDecision_TIS);
   fChain->SetBranchAddress("muminus_L0DiMuonDecision_TOS", &muminus_L0DiMuonDecision_TOS, &b_muminus_L0DiMuonDecision_TOS);
   fChain->SetBranchAddress("muminus_L0HadronDecision_Dec", &muminus_L0HadronDecision_Dec, &b_muminus_L0HadronDecision_Dec);
   fChain->SetBranchAddress("muminus_L0HadronDecision_TIS", &muminus_L0HadronDecision_TIS, &b_muminus_L0HadronDecision_TIS);
   fChain->SetBranchAddress("muminus_L0HadronDecision_TOS", &muminus_L0HadronDecision_TOS, &b_muminus_L0HadronDecision_TOS);
   fChain->SetBranchAddress("muminus_L0ElectronDecision_Dec", &muminus_L0ElectronDecision_Dec, &b_muminus_L0ElectronDecision_Dec);
   fChain->SetBranchAddress("muminus_L0ElectronDecision_TIS", &muminus_L0ElectronDecision_TIS, &b_muminus_L0ElectronDecision_TIS);
   fChain->SetBranchAddress("muminus_L0ElectronDecision_TOS", &muminus_L0ElectronDecision_TOS, &b_muminus_L0ElectronDecision_TOS);
   fChain->SetBranchAddress("muminus_L0ElectronHiDecision_Dec", &muminus_L0ElectronHiDecision_Dec, &b_muminus_L0ElectronHiDecision_Dec);
   fChain->SetBranchAddress("muminus_L0ElectronHiDecision_TIS", &muminus_L0ElectronHiDecision_TIS, &b_muminus_L0ElectronHiDecision_TIS);
   fChain->SetBranchAddress("muminus_L0ElectronHiDecision_TOS", &muminus_L0ElectronHiDecision_TOS, &b_muminus_L0ElectronHiDecision_TOS);
   fChain->SetBranchAddress("muminus_L0PhotonDecision_Dec", &muminus_L0PhotonDecision_Dec, &b_muminus_L0PhotonDecision_Dec);
   fChain->SetBranchAddress("muminus_L0PhotonDecision_TIS", &muminus_L0PhotonDecision_TIS, &b_muminus_L0PhotonDecision_TIS);
   fChain->SetBranchAddress("muminus_L0PhotonDecision_TOS", &muminus_L0PhotonDecision_TOS, &b_muminus_L0PhotonDecision_TOS);
   fChain->SetBranchAddress("muminus_L0PhotonHiDecision_Dec", &muminus_L0PhotonHiDecision_Dec, &b_muminus_L0PhotonHiDecision_Dec);
   fChain->SetBranchAddress("muminus_L0PhotonHiDecision_TIS", &muminus_L0PhotonHiDecision_TIS, &b_muminus_L0PhotonHiDecision_TIS);
   fChain->SetBranchAddress("muminus_L0PhotonHiDecision_TOS", &muminus_L0PhotonHiDecision_TOS, &b_muminus_L0PhotonHiDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt1SingleMuonNoIPDecision_Dec", &muminus_Hlt1SingleMuonNoIPDecision_Dec, &b_muminus_Hlt1SingleMuonNoIPDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt1SingleMuonNoIPDecision_TIS", &muminus_Hlt1SingleMuonNoIPDecision_TIS, &b_muminus_Hlt1SingleMuonNoIPDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt1SingleMuonNoIPDecision_TOS", &muminus_Hlt1SingleMuonNoIPDecision_TOS, &b_muminus_Hlt1SingleMuonNoIPDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt1SingleMuonHighPTDecision_Dec", &muminus_Hlt1SingleMuonHighPTDecision_Dec, &b_muminus_Hlt1SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt1SingleMuonHighPTDecision_TIS", &muminus_Hlt1SingleMuonHighPTDecision_TIS, &b_muminus_Hlt1SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt1SingleMuonHighPTDecision_TOS", &muminus_Hlt1SingleMuonHighPTDecision_TOS, &b_muminus_Hlt1SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt1SingleElectronNoIPDecision_Dec", &muminus_Hlt1SingleElectronNoIPDecision_Dec, &b_muminus_Hlt1SingleElectronNoIPDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt1SingleElectronNoIPDecision_TIS", &muminus_Hlt1SingleElectronNoIPDecision_TIS, &b_muminus_Hlt1SingleElectronNoIPDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt1SingleElectronNoIPDecision_TOS", &muminus_Hlt1SingleElectronNoIPDecision_TOS, &b_muminus_Hlt1SingleElectronNoIPDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt1TrackAllL0Decision_Dec", &muminus_Hlt1TrackAllL0Decision_Dec, &b_muminus_Hlt1TrackAllL0Decision_Dec);
   fChain->SetBranchAddress("muminus_Hlt1TrackAllL0Decision_TIS", &muminus_Hlt1TrackAllL0Decision_TIS, &b_muminus_Hlt1TrackAllL0Decision_TIS);
   fChain->SetBranchAddress("muminus_Hlt1TrackAllL0Decision_TOS", &muminus_Hlt1TrackAllL0Decision_TOS, &b_muminus_Hlt1TrackAllL0Decision_TOS);
   fChain->SetBranchAddress("muminus_Hlt1TrackMuonDecision_Dec", &muminus_Hlt1TrackMuonDecision_Dec, &b_muminus_Hlt1TrackMuonDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt1TrackMuonDecision_TIS", &muminus_Hlt1TrackMuonDecision_TIS, &b_muminus_Hlt1TrackMuonDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt1TrackMuonDecision_TOS", &muminus_Hlt1TrackMuonDecision_TOS, &b_muminus_Hlt1TrackMuonDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt1TrackPhotonDecision_Dec", &muminus_Hlt1TrackPhotonDecision_Dec, &b_muminus_Hlt1TrackPhotonDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt1TrackPhotonDecision_TIS", &muminus_Hlt1TrackPhotonDecision_TIS, &b_muminus_Hlt1TrackPhotonDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt1TrackPhotonDecision_TOS", &muminus_Hlt1TrackPhotonDecision_TOS, &b_muminus_Hlt1TrackPhotonDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt1TrackAllL0__Decision_Dec", &muminus_Hlt1TrackAllL0__Decision_Dec, &b_muminus_Hlt1TrackAllL0__Decision_Dec);
   fChain->SetBranchAddress("muminus_Hlt1TrackAllL0__Decision_TIS", &muminus_Hlt1TrackAllL0__Decision_TIS, &b_muminus_Hlt1TrackAllL0__Decision_TIS);
   fChain->SetBranchAddress("muminus_Hlt1TrackAllL0__Decision_TOS", &muminus_Hlt1TrackAllL0__Decision_TOS, &b_muminus_Hlt1TrackAllL0__Decision_TOS);
   fChain->SetBranchAddress("muminus_Hlt1DiMuonLowMassDecision_Dec", &muminus_Hlt1DiMuonLowMassDecision_Dec, &b_muminus_Hlt1DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt1DiMuonLowMassDecision_TIS", &muminus_Hlt1DiMuonLowMassDecision_TIS, &b_muminus_Hlt1DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt1DiMuonLowMassDecision_TOS", &muminus_Hlt1DiMuonLowMassDecision_TOS, &b_muminus_Hlt1DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt1DiMuonHighMassDecision_Dec", &muminus_Hlt1DiMuonHighMassDecision_Dec, &b_muminus_Hlt1DiMuonHighMassDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt1DiMuonHighMassDecision_TIS", &muminus_Hlt1DiMuonHighMassDecision_TIS, &b_muminus_Hlt1DiMuonHighMassDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt1DiMuonHighMassDecision_TOS", &muminus_Hlt1DiMuonHighMassDecision_TOS, &b_muminus_Hlt1DiMuonHighMassDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt1MB__Decision_Dec", &muminus_Hlt1MB__Decision_Dec, &b_muminus_Hlt1MB__Decision_Dec);
   fChain->SetBranchAddress("muminus_Hlt1MB__Decision_TIS", &muminus_Hlt1MB__Decision_TIS, &b_muminus_Hlt1MB__Decision_TIS);
   fChain->SetBranchAddress("muminus_Hlt1MB__Decision_TOS", &muminus_Hlt1MB__Decision_TOS, &b_muminus_Hlt1MB__Decision_TOS);
   fChain->SetBranchAddress("muminus_Hlt1TrackAllL0TightDecision_Dec", &muminus_Hlt1TrackAllL0TightDecision_Dec, &b_muminus_Hlt1TrackAllL0TightDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt1TrackAllL0TightDecision_TIS", &muminus_Hlt1TrackAllL0TightDecision_TIS, &b_muminus_Hlt1TrackAllL0TightDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt1TrackAllL0TightDecision_TOS", &muminus_Hlt1TrackAllL0TightDecision_TOS, &b_muminus_Hlt1TrackAllL0TightDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2SingleMuonDecision_Dec", &muminus_Hlt2SingleMuonDecision_Dec, &b_muminus_Hlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2SingleMuonDecision_TIS", &muminus_Hlt2SingleMuonDecision_TIS, &b_muminus_Hlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2SingleMuonDecision_TOS", &muminus_Hlt2SingleMuonDecision_TOS, &b_muminus_Hlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2SingleMuonLowPTDecision_Dec", &muminus_Hlt2SingleMuonLowPTDecision_Dec, &b_muminus_Hlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2SingleMuonLowPTDecision_TIS", &muminus_Hlt2SingleMuonLowPTDecision_TIS, &b_muminus_Hlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2SingleMuonLowPTDecision_TOS", &muminus_Hlt2SingleMuonLowPTDecision_TOS, &b_muminus_Hlt2SingleMuonLowPTDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2SingleMuonHighPTDecision_Dec", &muminus_Hlt2SingleMuonHighPTDecision_Dec, &b_muminus_Hlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2SingleMuonHighPTDecision_TIS", &muminus_Hlt2SingleMuonHighPTDecision_TIS, &b_muminus_Hlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2SingleMuonHighPTDecision_TOS", &muminus_Hlt2SingleMuonHighPTDecision_TOS, &b_muminus_Hlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonDecision_Dec", &muminus_Hlt2DiMuonDecision_Dec, &b_muminus_Hlt2DiMuonDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonDecision_TIS", &muminus_Hlt2DiMuonDecision_TIS, &b_muminus_Hlt2DiMuonDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonDecision_TOS", &muminus_Hlt2DiMuonDecision_TOS, &b_muminus_Hlt2DiMuonDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonLowMassDecision_Dec", &muminus_Hlt2DiMuonLowMassDecision_Dec, &b_muminus_Hlt2DiMuonLowMassDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonLowMassDecision_TIS", &muminus_Hlt2DiMuonLowMassDecision_TIS, &b_muminus_Hlt2DiMuonLowMassDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonLowMassDecision_TOS", &muminus_Hlt2DiMuonLowMassDecision_TOS, &b_muminus_Hlt2DiMuonLowMassDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonJPsiDecision_Dec", &muminus_Hlt2DiMuonJPsiDecision_Dec, &b_muminus_Hlt2DiMuonJPsiDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonJPsiDecision_TIS", &muminus_Hlt2DiMuonJPsiDecision_TIS, &b_muminus_Hlt2DiMuonJPsiDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonJPsiDecision_TOS", &muminus_Hlt2DiMuonJPsiDecision_TOS, &b_muminus_Hlt2DiMuonJPsiDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonJPsiHighPTDecision_Dec", &muminus_Hlt2DiMuonJPsiHighPTDecision_Dec, &b_muminus_Hlt2DiMuonJPsiHighPTDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonJPsiHighPTDecision_TIS", &muminus_Hlt2DiMuonJPsiHighPTDecision_TIS, &b_muminus_Hlt2DiMuonJPsiHighPTDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonJPsiHighPTDecision_TOS", &muminus_Hlt2DiMuonJPsiHighPTDecision_TOS, &b_muminus_Hlt2DiMuonJPsiHighPTDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonPsi2SDecision_Dec", &muminus_Hlt2DiMuonPsi2SDecision_Dec, &b_muminus_Hlt2DiMuonPsi2SDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonPsi2SDecision_TIS", &muminus_Hlt2DiMuonPsi2SDecision_TIS, &b_muminus_Hlt2DiMuonPsi2SDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonPsi2SDecision_TOS", &muminus_Hlt2DiMuonPsi2SDecision_TOS, &b_muminus_Hlt2DiMuonPsi2SDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonDetachedDecision_Dec", &muminus_Hlt2DiMuonDetachedDecision_Dec, &b_muminus_Hlt2DiMuonDetachedDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonDetachedDecision_TIS", &muminus_Hlt2DiMuonDetachedDecision_TIS, &b_muminus_Hlt2DiMuonDetachedDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonDetachedDecision_TOS", &muminus_Hlt2DiMuonDetachedDecision_TOS, &b_muminus_Hlt2DiMuonDetachedDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonDetachedJPsiDecision_Dec", &muminus_Hlt2DiMuonDetachedJPsiDecision_Dec, &b_muminus_Hlt2DiMuonDetachedJPsiDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonDetachedJPsiDecision_TIS", &muminus_Hlt2DiMuonDetachedJPsiDecision_TIS, &b_muminus_Hlt2DiMuonDetachedJPsiDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonDetachedJPsiDecision_TOS", &muminus_Hlt2DiMuonDetachedJPsiDecision_TOS, &b_muminus_Hlt2DiMuonDetachedJPsiDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonDetachedHeavyDecision_Dec", &muminus_Hlt2DiMuonDetachedHeavyDecision_Dec, &b_muminus_Hlt2DiMuonDetachedHeavyDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonDetachedHeavyDecision_TIS", &muminus_Hlt2DiMuonDetachedHeavyDecision_TIS, &b_muminus_Hlt2DiMuonDetachedHeavyDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonDetachedHeavyDecision_TOS", &muminus_Hlt2DiMuonDetachedHeavyDecision_TOS, &b_muminus_Hlt2DiMuonDetachedHeavyDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2TriMuonTauDecision_Dec", &muminus_Hlt2TriMuonTauDecision_Dec, &b_muminus_Hlt2TriMuonTauDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2TriMuonTauDecision_TIS", &muminus_Hlt2TriMuonTauDecision_TIS, &b_muminus_Hlt2TriMuonTauDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2TriMuonTauDecision_TOS", &muminus_Hlt2TriMuonTauDecision_TOS, &b_muminus_Hlt2TriMuonTauDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2B2HHDecision_Dec", &muminus_Hlt2B2HHDecision_Dec, &b_muminus_Hlt2B2HHDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2B2HHDecision_TIS", &muminus_Hlt2B2HHDecision_TIS, &b_muminus_Hlt2B2HHDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2B2HHDecision_TOS", &muminus_Hlt2B2HHDecision_TOS, &b_muminus_Hlt2B2HHDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonBDecision_Dec", &muminus_Hlt2DiMuonBDecision_Dec, &b_muminus_Hlt2DiMuonBDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonBDecision_TIS", &muminus_Hlt2DiMuonBDecision_TIS, &b_muminus_Hlt2DiMuonBDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonBDecision_TOS", &muminus_Hlt2DiMuonBDecision_TOS, &b_muminus_Hlt2DiMuonBDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonZDecision_Dec", &muminus_Hlt2DiMuonZDecision_Dec, &b_muminus_Hlt2DiMuonZDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonZDecision_TIS", &muminus_Hlt2DiMuonZDecision_TIS, &b_muminus_Hlt2DiMuonZDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonZDecision_TOS", &muminus_Hlt2DiMuonZDecision_TOS, &b_muminus_Hlt2DiMuonZDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2TopoMu2BodyBBDTDecision_Dec", &muminus_Hlt2TopoMu2BodyBBDTDecision_Dec, &b_muminus_Hlt2TopoMu2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2TopoMu2BodyBBDTDecision_TIS", &muminus_Hlt2TopoMu2BodyBBDTDecision_TIS, &b_muminus_Hlt2TopoMu2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2TopoMu2BodyBBDTDecision_TOS", &muminus_Hlt2TopoMu2BodyBBDTDecision_TOS, &b_muminus_Hlt2TopoMu2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2TopoMu3BodyBBDTDecision_Dec", &muminus_Hlt2TopoMu3BodyBBDTDecision_Dec, &b_muminus_Hlt2TopoMu3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2TopoMu3BodyBBDTDecision_TIS", &muminus_Hlt2TopoMu3BodyBBDTDecision_TIS, &b_muminus_Hlt2TopoMu3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2TopoMu3BodyBBDTDecision_TOS", &muminus_Hlt2TopoMu3BodyBBDTDecision_TOS, &b_muminus_Hlt2TopoMu3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2TopoMu4BodyBBDTDecision_Dec", &muminus_Hlt2TopoMu4BodyBBDTDecision_Dec, &b_muminus_Hlt2TopoMu4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2TopoMu4BodyBBDTDecision_TIS", &muminus_Hlt2TopoMu4BodyBBDTDecision_TIS, &b_muminus_Hlt2TopoMu4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2TopoMu4BodyBBDTDecision_TOS", &muminus_Hlt2TopoMu4BodyBBDTDecision_TOS, &b_muminus_Hlt2TopoMu4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2Topo2BodyBBDTDecision_Dec", &muminus_Hlt2Topo2BodyBBDTDecision_Dec, &b_muminus_Hlt2Topo2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2Topo2BodyBBDTDecision_TIS", &muminus_Hlt2Topo2BodyBBDTDecision_TIS, &b_muminus_Hlt2Topo2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2Topo2BodyBBDTDecision_TOS", &muminus_Hlt2Topo2BodyBBDTDecision_TOS, &b_muminus_Hlt2Topo2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2Topo3BodyBBDTDecision_Dec", &muminus_Hlt2Topo3BodyBBDTDecision_Dec, &b_muminus_Hlt2Topo3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2Topo3BodyBBDTDecision_TIS", &muminus_Hlt2Topo3BodyBBDTDecision_TIS, &b_muminus_Hlt2Topo3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2Topo3BodyBBDTDecision_TOS", &muminus_Hlt2Topo3BodyBBDTDecision_TOS, &b_muminus_Hlt2Topo3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2Topo4BodyBBDTDecision_Dec", &muminus_Hlt2Topo4BodyBBDTDecision_Dec, &b_muminus_Hlt2Topo4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2Topo4BodyBBDTDecision_TIS", &muminus_Hlt2Topo4BodyBBDTDecision_TIS, &b_muminus_Hlt2Topo4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2Topo4BodyBBDTDecision_TOS", &muminus_Hlt2Topo4BodyBBDTDecision_TOS, &b_muminus_Hlt2Topo4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2Topo2BodySimpleDecision_Dec", &muminus_Hlt2Topo2BodySimpleDecision_Dec, &b_muminus_Hlt2Topo2BodySimpleDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2Topo2BodySimpleDecision_TIS", &muminus_Hlt2Topo2BodySimpleDecision_TIS, &b_muminus_Hlt2Topo2BodySimpleDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2Topo2BodySimpleDecision_TOS", &muminus_Hlt2Topo2BodySimpleDecision_TOS, &b_muminus_Hlt2Topo2BodySimpleDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2Topo3BodySimpleDecision_Dec", &muminus_Hlt2Topo3BodySimpleDecision_Dec, &b_muminus_Hlt2Topo3BodySimpleDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2Topo3BodySimpleDecision_TIS", &muminus_Hlt2Topo3BodySimpleDecision_TIS, &b_muminus_Hlt2Topo3BodySimpleDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2Topo3BodySimpleDecision_TOS", &muminus_Hlt2Topo3BodySimpleDecision_TOS, &b_muminus_Hlt2Topo3BodySimpleDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2Topo4BodySimpleDecision_Dec", &muminus_Hlt2Topo4BodySimpleDecision_Dec, &b_muminus_Hlt2Topo4BodySimpleDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2Topo4BodySimpleDecision_TIS", &muminus_Hlt2Topo4BodySimpleDecision_TIS, &b_muminus_Hlt2Topo4BodySimpleDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2Topo4BodySimpleDecision_TOS", &muminus_Hlt2Topo4BodySimpleDecision_TOS, &b_muminus_Hlt2Topo4BodySimpleDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2PassThroughDecision_Dec", &muminus_Hlt2PassThroughDecision_Dec, &b_muminus_Hlt2PassThroughDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2PassThroughDecision_TIS", &muminus_Hlt2PassThroughDecision_TIS, &b_muminus_Hlt2PassThroughDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2PassThroughDecision_TOS", &muminus_Hlt2PassThroughDecision_TOS, &b_muminus_Hlt2PassThroughDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2TransparentDecision_Dec", &muminus_Hlt2TransparentDecision_Dec, &b_muminus_Hlt2TransparentDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2TransparentDecision_TIS", &muminus_Hlt2TransparentDecision_TIS, &b_muminus_Hlt2TransparentDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2TransparentDecision_TOS", &muminus_Hlt2TransparentDecision_TOS, &b_muminus_Hlt2TransparentDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2IncPhiDecision_Dec", &muminus_Hlt2IncPhiDecision_Dec, &b_muminus_Hlt2IncPhiDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2IncPhiDecision_TIS", &muminus_Hlt2IncPhiDecision_TIS, &b_muminus_Hlt2IncPhiDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2IncPhiDecision_TOS", &muminus_Hlt2IncPhiDecision_TOS, &b_muminus_Hlt2IncPhiDecision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonDY__Decision_Dec", &muminus_Hlt2DiMuonDY__Decision_Dec, &b_muminus_Hlt2DiMuonDY__Decision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonDY__Decision_TIS", &muminus_Hlt2DiMuonDY__Decision_TIS, &b_muminus_Hlt2DiMuonDY__Decision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2DiMuonDY__Decision_TOS", &muminus_Hlt2DiMuonDY__Decision_TOS, &b_muminus_Hlt2DiMuonDY__Decision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2TopoE__Decision_Dec", &muminus_Hlt2TopoE__Decision_Dec, &b_muminus_Hlt2TopoE__Decision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2TopoE__Decision_TIS", &muminus_Hlt2TopoE__Decision_TIS, &b_muminus_Hlt2TopoE__Decision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2TopoE__Decision_TOS", &muminus_Hlt2TopoE__Decision_TOS, &b_muminus_Hlt2TopoE__Decision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2Topo__Decision_Dec", &muminus_Hlt2Topo__Decision_Dec, &b_muminus_Hlt2Topo__Decision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2Topo__Decision_TIS", &muminus_Hlt2Topo__Decision_TIS, &b_muminus_Hlt2Topo__Decision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2Topo__Decision_TOS", &muminus_Hlt2Topo__Decision_TOS, &b_muminus_Hlt2Topo__Decision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2Charm__Decision_Dec", &muminus_Hlt2Charm__Decision_Dec, &b_muminus_Hlt2Charm__Decision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2Charm__Decision_TIS", &muminus_Hlt2Charm__Decision_TIS, &b_muminus_Hlt2Charm__Decision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2Charm__Decision_TOS", &muminus_Hlt2Charm__Decision_TOS, &b_muminus_Hlt2Charm__Decision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2DiElectron__Decision_Dec", &muminus_Hlt2DiElectron__Decision_Dec, &b_muminus_Hlt2DiElectron__Decision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2DiElectron__Decision_TIS", &muminus_Hlt2DiElectron__Decision_TIS, &b_muminus_Hlt2DiElectron__Decision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2DiElectron__Decision_TOS", &muminus_Hlt2DiElectron__Decision_TOS, &b_muminus_Hlt2DiElectron__Decision_TOS);
   fChain->SetBranchAddress("muminus_Hlt2__GammaDecision_Dec", &muminus_Hlt2__GammaDecision_Dec, &b_muminus_Hlt2__GammaDecision_Dec);
   fChain->SetBranchAddress("muminus_Hlt2__GammaDecision_TIS", &muminus_Hlt2__GammaDecision_TIS, &b_muminus_Hlt2__GammaDecision_TIS);
   fChain->SetBranchAddress("muminus_Hlt2__GammaDecision_TOS", &muminus_Hlt2__GammaDecision_TOS, &b_muminus_Hlt2__GammaDecision_TOS);
   fChain->SetBranchAddress("muminus_TRACK_Type", &muminus_TRACK_Type, &b_muminus_TRACK_Type);
   fChain->SetBranchAddress("muminus_TRACK_Key", &muminus_TRACK_Key, &b_muminus_TRACK_Key);
   fChain->SetBranchAddress("muminus_TRACK_CHI2NDOF", &muminus_TRACK_CHI2NDOF, &b_muminus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("muminus_TRACK_PCHI2", &muminus_TRACK_PCHI2, &b_muminus_TRACK_PCHI2);
   fChain->SetBranchAddress("muminus_TRACK_MatchCHI2", &muminus_TRACK_MatchCHI2, &b_muminus_TRACK_MatchCHI2);
   fChain->SetBranchAddress("muminus_TRACK_GhostProb", &muminus_TRACK_GhostProb, &b_muminus_TRACK_GhostProb);
   fChain->SetBranchAddress("muminus_TRACK_CloneDist", &muminus_TRACK_CloneDist, &b_muminus_TRACK_CloneDist);
   fChain->SetBranchAddress("muminus_TRACK_Likelihood", &muminus_TRACK_Likelihood, &b_muminus_TRACK_Likelihood);
   fChain->SetBranchAddress("nCandidate", &nCandidate, &b_nCandidate);
   fChain->SetBranchAddress("totCandidates", &totCandidates, &b_totCandidates);
   fChain->SetBranchAddress("EventInSequence", &EventInSequence, &b_EventInSequence);
   fChain->SetBranchAddress("MCPVs", &MCPVs, &b_MCPVs);
   fChain->SetBranchAddress("MCPVX", MCPVX, &b_MCPVX);
   fChain->SetBranchAddress("MCPVY", MCPVY, &b_MCPVY);
   fChain->SetBranchAddress("MCPVZ", MCPVZ, &b_MCPVZ);
   fChain->SetBranchAddress("MCPVT", MCPVT, &b_MCPVT);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("BCID", &BCID, &b_BCID);
   fChain->SetBranchAddress("BCType", &BCType, &b_BCType);
   fChain->SetBranchAddress("OdinTCK", &OdinTCK, &b_OdinTCK);
   fChain->SetBranchAddress("L0DUTCK", &L0DUTCK, &b_L0DUTCK);
   fChain->SetBranchAddress("HLTTCK", &HLTTCK, &b_HLTTCK);
   fChain->SetBranchAddress("GpsTime", &GpsTime, &b_GpsTime);
   fChain->SetBranchAddress("Polarity", &Polarity, &b_Polarity);
   fChain->SetBranchAddress("Collisions", &Collisions, &b_Collisions);
   fChain->SetBranchAddress("ProcessType", ProcessType, &b_ProcessType);
   fChain->SetBranchAddress("HeaviestQuark", HeaviestQuark, &b_HeaviestQuark);
   fChain->SetBranchAddress("HeaviestQuarkInEvent", &HeaviestQuarkInEvent, &b_HeaviestQuarkInEvent);
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

Bool_t addIso::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void addIso::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t addIso::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef addIso_cxx
