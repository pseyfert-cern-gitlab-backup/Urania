//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jul 22 15:04:45 2013 by ROOT version 5.34/05
// from TTree MCDecayTree/MCDecayTree
// found on file: castor:///castor/cern.ch/user/p/pkoppenb/Lambdab/LambdabMC-Lbpi-Sim08a-1122-1123-1124-1125.root
//////////////////////////////////////////////////////////

#ifndef MCTuple_h
#define MCTuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "Tuples.h"

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class MCTuple {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        Lambda_b0_TRUECosTheta;
   Double_t        Lambda_b0_TRUEP_E;
   Double_t        Lambda_b0_TRUEP_X;
   Double_t        Lambda_b0_TRUEP_Y;
   Double_t        Lambda_b0_TRUEP_Z;
   Double_t        Lambda_b0_TRUEPT;
   Double_t        Lambda_b0_TRUEORIGINVERTEX_X;
   Double_t        Lambda_b0_TRUEORIGINVERTEX_Y;
   Double_t        Lambda_b0_TRUEORIGINVERTEX_Z;
   Double_t        Lambda_b0_TRUEENDVERTEX_X;
   Double_t        Lambda_b0_TRUEENDVERTEX_Y;
   Double_t        Lambda_b0_TRUEENDVERTEX_Z;
   Bool_t          Lambda_b0_TRUEISSTABLE;
   Double_t        Lambda_b0_TRUETAU;
   Int_t           Lambda_b0_Reconstructible;
   Int_t           Lambda_b0_Reconstructed;
   Int_t           Lambda_b0_ProtoParticles;
   Float_t         Lambda_b0_PP_PX[20];   //[Lambda_b0_ProtoParticles]
   Float_t         Lambda_b0_PP_PY[20];   //[Lambda_b0_ProtoParticles]
   Float_t         Lambda_b0_PP_PZ[20];   //[Lambda_b0_ProtoParticles]
   Float_t         Lambda_b0_PP_Weight[20];   //[Lambda_b0_ProtoParticles]
   Float_t         Lambda_b0_PP_tr_pchi2[20];   //[Lambda_b0_ProtoParticles]
   Float_t         Lambda_b0_PP_DLLe[20];   //[Lambda_b0_ProtoParticles]
   Float_t         Lambda_b0_PP_DLLk[20];   //[Lambda_b0_ProtoParticles]
   Float_t         Lambda_b0_PP_DLLp[20];   //[Lambda_b0_ProtoParticles]
   Float_t         Lambda_b0_PP_DLLmu[20];   //[Lambda_b0_ProtoParticles]
   Double_t        J_psi_1S_TRUECosTheta;
   Double_t        J_psi_1S_TRUEP_E;
   Double_t        J_psi_1S_TRUEP_X;
   Double_t        J_psi_1S_TRUEP_Y;
   Double_t        J_psi_1S_TRUEP_Z;
   Double_t        J_psi_1S_TRUEPT;
   Double_t        J_psi_1S_TRUEORIGINVERTEX_X;
   Double_t        J_psi_1S_TRUEORIGINVERTEX_Y;
   Double_t        J_psi_1S_TRUEORIGINVERTEX_Z;
   Double_t        J_psi_1S_TRUEENDVERTEX_X;
   Double_t        J_psi_1S_TRUEENDVERTEX_Y;
   Double_t        J_psi_1S_TRUEENDVERTEX_Z;
   Bool_t          J_psi_1S_TRUEISSTABLE;
   Double_t        J_psi_1S_TRUETAU;
   Int_t           J_psi_1S_Reconstructible;
   Int_t           J_psi_1S_Reconstructed;
   Int_t           J_psi_1S_ProtoParticles;
   Float_t         J_psi_1S_PP_PX[20];   //[J_psi_1S_ProtoParticles]
   Float_t         J_psi_1S_PP_PY[20];   //[J_psi_1S_ProtoParticles]
   Float_t         J_psi_1S_PP_PZ[20];   //[J_psi_1S_ProtoParticles]
   Float_t         J_psi_1S_PP_Weight[20];   //[J_psi_1S_ProtoParticles]
   Float_t         J_psi_1S_PP_tr_pchi2[20];   //[J_psi_1S_ProtoParticles]
   Float_t         J_psi_1S_PP_DLLe[20];   //[J_psi_1S_ProtoParticles]
   Float_t         J_psi_1S_PP_DLLk[20];   //[J_psi_1S_ProtoParticles]
   Float_t         J_psi_1S_PP_DLLp[20];   //[J_psi_1S_ProtoParticles]
   Float_t         J_psi_1S_PP_DLLmu[20];   //[J_psi_1S_ProtoParticles]
   Double_t        muminus_TRUECosTheta;
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
   Int_t           muminus_Reconstructible;
   Int_t           muminus_Reconstructed;
   Int_t           muminus_ProtoParticles;
   Float_t         muminus_PP_PX[20];   //[muminus_ProtoParticles]
   Float_t         muminus_PP_PY[20];   //[muminus_ProtoParticles]
   Float_t         muminus_PP_PZ[20];   //[muminus_ProtoParticles]
   Float_t         muminus_PP_Weight[20];   //[muminus_ProtoParticles]
   Float_t         muminus_PP_tr_pchi2[20];   //[muminus_ProtoParticles]
   Float_t         muminus_PP_DLLe[20];   //[muminus_ProtoParticles]
   Float_t         muminus_PP_DLLk[20];   //[muminus_ProtoParticles]
   Float_t         muminus_PP_DLLp[20];   //[muminus_ProtoParticles]
   Float_t         muminus_PP_DLLmu[20];   //[muminus_ProtoParticles]
   Double_t        muplus_TRUECosTheta;
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
   Int_t           muplus_Reconstructible;
   Int_t           muplus_Reconstructed;
   Int_t           muplus_ProtoParticles;
   Float_t         muplus_PP_PX[20];   //[muplus_ProtoParticles]
   Float_t         muplus_PP_PY[20];   //[muplus_ProtoParticles]
   Float_t         muplus_PP_PZ[20];   //[muplus_ProtoParticles]
   Float_t         muplus_PP_Weight[20];   //[muplus_ProtoParticles]
   Float_t         muplus_PP_tr_pchi2[20];   //[muplus_ProtoParticles]
   Float_t         muplus_PP_DLLe[20];   //[muplus_ProtoParticles]
   Float_t         muplus_PP_DLLk[20];   //[muplus_ProtoParticles]
   Float_t         muplus_PP_DLLp[20];   //[muplus_ProtoParticles]
   Float_t         muplus_PP_DLLmu[20];   //[muplus_ProtoParticles]
   Double_t        piminus_TRUECosTheta;
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
   Int_t           piminus_Reconstructible;
   Int_t           piminus_Reconstructed;
   Int_t           piminus_ProtoParticles;
   Float_t         piminus_PP_PX[20];   //[piminus_ProtoParticles]
   Float_t         piminus_PP_PY[20];   //[piminus_ProtoParticles]
   Float_t         piminus_PP_PZ[20];   //[piminus_ProtoParticles]
   Float_t         piminus_PP_Weight[20];   //[piminus_ProtoParticles]
   Float_t         piminus_PP_tr_pchi2[20];   //[piminus_ProtoParticles]
   Float_t         piminus_PP_DLLe[20];   //[piminus_ProtoParticles]
   Float_t         piminus_PP_DLLk[20];   //[piminus_ProtoParticles]
   Float_t         piminus_PP_DLLp[20];   //[piminus_ProtoParticles]
   Float_t         piminus_PP_DLLmu[20];   //[piminus_ProtoParticles]
   Double_t        pplus_TRUECosTheta;
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
   Int_t           pplus_Reconstructible;
   Int_t           pplus_Reconstructed;
   Int_t           pplus_ProtoParticles;
   Float_t         pplus_PP_PX[20];   //[pplus_ProtoParticles]
   Float_t         pplus_PP_PY[20];   //[pplus_ProtoParticles]
   Float_t         pplus_PP_PZ[20];   //[pplus_ProtoParticles]
   Float_t         pplus_PP_Weight[20];   //[pplus_ProtoParticles]
   Float_t         pplus_PP_tr_pchi2[20];   //[pplus_ProtoParticles]
   Float_t         pplus_PP_DLLe[20];   //[pplus_ProtoParticles]
   Float_t         pplus_PP_DLLk[20];   //[pplus_ProtoParticles]
   Float_t         pplus_PP_DLLp[20];   //[pplus_ProtoParticles]
   Float_t         pplus_PP_DLLmu[20];   //[pplus_ProtoParticles]
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
   UInt_t          StrippingB2JpsiXforBeta_sLambdab2JpsippiDetachedLineDecision;
   UInt_t          StrippingB2JpsiXforBeta_sLambdab2JpsiLambdaUnbiasedLineDecision;

   // List of branches
   TBranch        *b_Lambda_b0_TRUECosTheta;   //!
   TBranch        *b_Lambda_b0_TRUEP_E;   //!
   TBranch        *b_Lambda_b0_TRUEP_X;   //!
   TBranch        *b_Lambda_b0_TRUEP_Y;   //!
   TBranch        *b_Lambda_b0_TRUEP_Z;   //!
   TBranch        *b_Lambda_b0_TRUEPT;   //!
   TBranch        *b_Lambda_b0_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_Lambda_b0_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_Lambda_b0_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_Lambda_b0_TRUEENDVERTEX_X;   //!
   TBranch        *b_Lambda_b0_TRUEENDVERTEX_Y;   //!
   TBranch        *b_Lambda_b0_TRUEENDVERTEX_Z;   //!
   TBranch        *b_Lambda_b0_TRUEISSTABLE;   //!
   TBranch        *b_Lambda_b0_TRUETAU;   //!
   TBranch        *b_Lambda_b0_Reconstructible;   //!
   TBranch        *b_Lambda_b0_Reconstructed;   //!
   TBranch        *b_Lambda_b0_ProtoParticles;   //!
   TBranch        *b_Lambda_b0_PP_PX;   //!
   TBranch        *b_Lambda_b0_PP_PY;   //!
   TBranch        *b_Lambda_b0_PP_PZ;   //!
   TBranch        *b_Lambda_b0_PP_Weight;   //!
   TBranch        *b_Lambda_b0_PP_tr_pchi2;   //!
   TBranch        *b_Lambda_b0_PP_DLLe;   //!
   TBranch        *b_Lambda_b0_PP_DLLk;   //!
   TBranch        *b_Lambda_b0_PP_DLLp;   //!
   TBranch        *b_Lambda_b0_PP_DLLmu;   //!
   TBranch        *b_J_psi_1S_TRUECosTheta;   //!
   TBranch        *b_J_psi_1S_TRUEP_E;   //!
   TBranch        *b_J_psi_1S_TRUEP_X;   //!
   TBranch        *b_J_psi_1S_TRUEP_Y;   //!
   TBranch        *b_J_psi_1S_TRUEP_Z;   //!
   TBranch        *b_J_psi_1S_TRUEPT;   //!
   TBranch        *b_J_psi_1S_TRUEORIGINVERTEX_X;   //!
   TBranch        *b_J_psi_1S_TRUEORIGINVERTEX_Y;   //!
   TBranch        *b_J_psi_1S_TRUEORIGINVERTEX_Z;   //!
   TBranch        *b_J_psi_1S_TRUEENDVERTEX_X;   //!
   TBranch        *b_J_psi_1S_TRUEENDVERTEX_Y;   //!
   TBranch        *b_J_psi_1S_TRUEENDVERTEX_Z;   //!
   TBranch        *b_J_psi_1S_TRUEISSTABLE;   //!
   TBranch        *b_J_psi_1S_TRUETAU;   //!
   TBranch        *b_J_psi_1S_Reconstructible;   //!
   TBranch        *b_J_psi_1S_Reconstructed;   //!
   TBranch        *b_J_psi_1S_ProtoParticles;   //!
   TBranch        *b_J_psi_1S_PP_PX;   //!
   TBranch        *b_J_psi_1S_PP_PY;   //!
   TBranch        *b_J_psi_1S_PP_PZ;   //!
   TBranch        *b_J_psi_1S_PP_Weight;   //!
   TBranch        *b_J_psi_1S_PP_tr_pchi2;   //!
   TBranch        *b_J_psi_1S_PP_DLLe;   //!
   TBranch        *b_J_psi_1S_PP_DLLk;   //!
   TBranch        *b_J_psi_1S_PP_DLLp;   //!
   TBranch        *b_J_psi_1S_PP_DLLmu;   //!
   TBranch        *b_muminus_TRUECosTheta;   //!
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
   TBranch        *b_muminus_Reconstructible;   //!
   TBranch        *b_muminus_Reconstructed;   //!
   TBranch        *b_muminus_ProtoParticles;   //!
   TBranch        *b_muminus_PP_PX;   //!
   TBranch        *b_muminus_PP_PY;   //!
   TBranch        *b_muminus_PP_PZ;   //!
   TBranch        *b_muminus_PP_Weight;   //!
   TBranch        *b_muminus_PP_tr_pchi2;   //!
   TBranch        *b_muminus_PP_DLLe;   //!
   TBranch        *b_muminus_PP_DLLk;   //!
   TBranch        *b_muminus_PP_DLLp;   //!
   TBranch        *b_muminus_PP_DLLmu;   //!
   TBranch        *b_muplus_TRUECosTheta;   //!
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
   TBranch        *b_muplus_Reconstructible;   //!
   TBranch        *b_muplus_Reconstructed;   //!
   TBranch        *b_muplus_ProtoParticles;   //!
   TBranch        *b_muplus_PP_PX;   //!
   TBranch        *b_muplus_PP_PY;   //!
   TBranch        *b_muplus_PP_PZ;   //!
   TBranch        *b_muplus_PP_Weight;   //!
   TBranch        *b_muplus_PP_tr_pchi2;   //!
   TBranch        *b_muplus_PP_DLLe;   //!
   TBranch        *b_muplus_PP_DLLk;   //!
   TBranch        *b_muplus_PP_DLLp;   //!
   TBranch        *b_muplus_PP_DLLmu;   //!
   TBranch        *b_piminus_TRUECosTheta;   //!
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
   TBranch        *b_piminus_Reconstructible;   //!
   TBranch        *b_piminus_Reconstructed;   //!
   TBranch        *b_piminus_ProtoParticles;   //!
   TBranch        *b_piminus_PP_PX;   //!
   TBranch        *b_piminus_PP_PY;   //!
   TBranch        *b_piminus_PP_PZ;   //!
   TBranch        *b_piminus_PP_Weight;   //!
   TBranch        *b_piminus_PP_tr_pchi2;   //!
   TBranch        *b_piminus_PP_DLLe;   //!
   TBranch        *b_piminus_PP_DLLk;   //!
   TBranch        *b_piminus_PP_DLLp;   //!
   TBranch        *b_piminus_PP_DLLmu;   //!
   TBranch        *b_pplus_TRUECosTheta;   //!
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
   TBranch        *b_pplus_Reconstructible;   //!
   TBranch        *b_pplus_Reconstructed;   //!
   TBranch        *b_pplus_ProtoParticles;   //!
   TBranch        *b_pplus_PP_PX;   //!
   TBranch        *b_pplus_PP_PY;   //!
   TBranch        *b_pplus_PP_PZ;   //!
   TBranch        *b_pplus_PP_Weight;   //!
   TBranch        *b_pplus_PP_tr_pchi2;   //!
   TBranch        *b_pplus_PP_DLLe;   //!
   TBranch        *b_pplus_PP_DLLk;   //!
   TBranch        *b_pplus_PP_DLLp;   //!
   TBranch        *b_pplus_PP_DLLmu;   //!
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
   TBranch        *b_StrippingB2JpsiXforBeta_sLambdab2JpsippiDetachedLineDecision;   //!
   TBranch        *b_StrippingB2JpsiXforBeta_sLambdab2JpsiLambdaUnbiasedLineDecision;   //!

   MCTuple(TString filename);
   virtual ~MCTuple();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   bool m_isPi ;
   
   Double_t psiMMass2();
   Double_t pMMass2();
   Double_t psipMass2();
   Double_t thetaprime();
   Double_t mprime();
};

#endif

#ifdef MCTuple_cxx
MCTuple::MCTuple(TString filename) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  
  m_isPi = (filename.Contains("LambdabMC-Lbpi"));
  std::cout << "Making Tuple with " << filename << " -> Looking for J/psip" << (m_isPi?"pi":"K") << std::endl ;
  TFile *f = TFile::Open(filename);
  TString tName = TString((m_isPi?"MCTuplepp":"MCTuplepk"))+TString("/MCDecayTree");
  TTree* tree = (TTree*)f->Get(tName);
  if (!tree) std::cout << "Cannot find " << tName << " in " << filename << std::endl ;
  Init(tree);
}

MCTuple::~MCTuple()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MCTuple::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MCTuple::LoadTree(Long64_t entry)
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

void MCTuple::Init(TTree *tree)
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

   fChain->SetBranchAddress("Lambda_b0_TRUECosTheta", &Lambda_b0_TRUECosTheta, &b_Lambda_b0_TRUECosTheta);
   fChain->SetBranchAddress("Lambda_b0_TRUEP_E", &Lambda_b0_TRUEP_E, &b_Lambda_b0_TRUEP_E);
   fChain->SetBranchAddress("Lambda_b0_TRUEP_X", &Lambda_b0_TRUEP_X, &b_Lambda_b0_TRUEP_X);
   fChain->SetBranchAddress("Lambda_b0_TRUEP_Y", &Lambda_b0_TRUEP_Y, &b_Lambda_b0_TRUEP_Y);
   fChain->SetBranchAddress("Lambda_b0_TRUEP_Z", &Lambda_b0_TRUEP_Z, &b_Lambda_b0_TRUEP_Z);
   fChain->SetBranchAddress("Lambda_b0_TRUEPT", &Lambda_b0_TRUEPT, &b_Lambda_b0_TRUEPT);
   fChain->SetBranchAddress("Lambda_b0_TRUEORIGINVERTEX_X", &Lambda_b0_TRUEORIGINVERTEX_X, &b_Lambda_b0_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("Lambda_b0_TRUEORIGINVERTEX_Y", &Lambda_b0_TRUEORIGINVERTEX_Y, &b_Lambda_b0_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("Lambda_b0_TRUEORIGINVERTEX_Z", &Lambda_b0_TRUEORIGINVERTEX_Z, &b_Lambda_b0_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("Lambda_b0_TRUEENDVERTEX_X", &Lambda_b0_TRUEENDVERTEX_X, &b_Lambda_b0_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("Lambda_b0_TRUEENDVERTEX_Y", &Lambda_b0_TRUEENDVERTEX_Y, &b_Lambda_b0_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("Lambda_b0_TRUEENDVERTEX_Z", &Lambda_b0_TRUEENDVERTEX_Z, &b_Lambda_b0_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("Lambda_b0_TRUEISSTABLE", &Lambda_b0_TRUEISSTABLE, &b_Lambda_b0_TRUEISSTABLE);
   fChain->SetBranchAddress("Lambda_b0_TRUETAU", &Lambda_b0_TRUETAU, &b_Lambda_b0_TRUETAU);
   fChain->SetBranchAddress("Lambda_b0_Reconstructible", &Lambda_b0_Reconstructible, &b_Lambda_b0_Reconstructible);
   fChain->SetBranchAddress("Lambda_b0_Reconstructed", &Lambda_b0_Reconstructed, &b_Lambda_b0_Reconstructed);
   fChain->SetBranchAddress("Lambda_b0_ProtoParticles", &Lambda_b0_ProtoParticles, &b_Lambda_b0_ProtoParticles);
   fChain->SetBranchAddress("Lambda_b0_PP_PX", Lambda_b0_PP_PX, &b_Lambda_b0_PP_PX);
   fChain->SetBranchAddress("Lambda_b0_PP_PY", Lambda_b0_PP_PY, &b_Lambda_b0_PP_PY);
   fChain->SetBranchAddress("Lambda_b0_PP_PZ", Lambda_b0_PP_PZ, &b_Lambda_b0_PP_PZ);
   fChain->SetBranchAddress("Lambda_b0_PP_Weight", Lambda_b0_PP_Weight, &b_Lambda_b0_PP_Weight);
   fChain->SetBranchAddress("Lambda_b0_PP_tr_pchi2", Lambda_b0_PP_tr_pchi2, &b_Lambda_b0_PP_tr_pchi2);
   fChain->SetBranchAddress("Lambda_b0_PP_DLLe", Lambda_b0_PP_DLLe, &b_Lambda_b0_PP_DLLe);
   fChain->SetBranchAddress("Lambda_b0_PP_DLLk", Lambda_b0_PP_DLLk, &b_Lambda_b0_PP_DLLk);
   fChain->SetBranchAddress("Lambda_b0_PP_DLLp", Lambda_b0_PP_DLLp, &b_Lambda_b0_PP_DLLp);
   fChain->SetBranchAddress("Lambda_b0_PP_DLLmu", Lambda_b0_PP_DLLmu, &b_Lambda_b0_PP_DLLmu);
   fChain->SetBranchAddress("J_psi_1S_TRUECosTheta", &J_psi_1S_TRUECosTheta, &b_J_psi_1S_TRUECosTheta);
   fChain->SetBranchAddress("J_psi_1S_TRUEP_E", &J_psi_1S_TRUEP_E, &b_J_psi_1S_TRUEP_E);
   fChain->SetBranchAddress("J_psi_1S_TRUEP_X", &J_psi_1S_TRUEP_X, &b_J_psi_1S_TRUEP_X);
   fChain->SetBranchAddress("J_psi_1S_TRUEP_Y", &J_psi_1S_TRUEP_Y, &b_J_psi_1S_TRUEP_Y);
   fChain->SetBranchAddress("J_psi_1S_TRUEP_Z", &J_psi_1S_TRUEP_Z, &b_J_psi_1S_TRUEP_Z);
   fChain->SetBranchAddress("J_psi_1S_TRUEPT", &J_psi_1S_TRUEPT, &b_J_psi_1S_TRUEPT);
   fChain->SetBranchAddress("J_psi_1S_TRUEORIGINVERTEX_X", &J_psi_1S_TRUEORIGINVERTEX_X, &b_J_psi_1S_TRUEORIGINVERTEX_X);
   fChain->SetBranchAddress("J_psi_1S_TRUEORIGINVERTEX_Y", &J_psi_1S_TRUEORIGINVERTEX_Y, &b_J_psi_1S_TRUEORIGINVERTEX_Y);
   fChain->SetBranchAddress("J_psi_1S_TRUEORIGINVERTEX_Z", &J_psi_1S_TRUEORIGINVERTEX_Z, &b_J_psi_1S_TRUEORIGINVERTEX_Z);
   fChain->SetBranchAddress("J_psi_1S_TRUEENDVERTEX_X", &J_psi_1S_TRUEENDVERTEX_X, &b_J_psi_1S_TRUEENDVERTEX_X);
   fChain->SetBranchAddress("J_psi_1S_TRUEENDVERTEX_Y", &J_psi_1S_TRUEENDVERTEX_Y, &b_J_psi_1S_TRUEENDVERTEX_Y);
   fChain->SetBranchAddress("J_psi_1S_TRUEENDVERTEX_Z", &J_psi_1S_TRUEENDVERTEX_Z, &b_J_psi_1S_TRUEENDVERTEX_Z);
   fChain->SetBranchAddress("J_psi_1S_TRUEISSTABLE", &J_psi_1S_TRUEISSTABLE, &b_J_psi_1S_TRUEISSTABLE);
   fChain->SetBranchAddress("J_psi_1S_TRUETAU", &J_psi_1S_TRUETAU, &b_J_psi_1S_TRUETAU);
   fChain->SetBranchAddress("J_psi_1S_Reconstructible", &J_psi_1S_Reconstructible, &b_J_psi_1S_Reconstructible);
   fChain->SetBranchAddress("J_psi_1S_Reconstructed", &J_psi_1S_Reconstructed, &b_J_psi_1S_Reconstructed);
   fChain->SetBranchAddress("J_psi_1S_ProtoParticles", &J_psi_1S_ProtoParticles, &b_J_psi_1S_ProtoParticles);
   fChain->SetBranchAddress("J_psi_1S_PP_PX", J_psi_1S_PP_PX, &b_J_psi_1S_PP_PX);
   fChain->SetBranchAddress("J_psi_1S_PP_PY", J_psi_1S_PP_PY, &b_J_psi_1S_PP_PY);
   fChain->SetBranchAddress("J_psi_1S_PP_PZ", J_psi_1S_PP_PZ, &b_J_psi_1S_PP_PZ);
   fChain->SetBranchAddress("J_psi_1S_PP_Weight", J_psi_1S_PP_Weight, &b_J_psi_1S_PP_Weight);
   fChain->SetBranchAddress("J_psi_1S_PP_tr_pchi2", J_psi_1S_PP_tr_pchi2, &b_J_psi_1S_PP_tr_pchi2);
   fChain->SetBranchAddress("J_psi_1S_PP_DLLe", J_psi_1S_PP_DLLe, &b_J_psi_1S_PP_DLLe);
   fChain->SetBranchAddress("J_psi_1S_PP_DLLk", J_psi_1S_PP_DLLk, &b_J_psi_1S_PP_DLLk);
   fChain->SetBranchAddress("J_psi_1S_PP_DLLp", J_psi_1S_PP_DLLp, &b_J_psi_1S_PP_DLLp);
   fChain->SetBranchAddress("J_psi_1S_PP_DLLmu", J_psi_1S_PP_DLLmu, &b_J_psi_1S_PP_DLLmu);
   fChain->SetBranchAddress("muminus_TRUECosTheta", &muminus_TRUECosTheta, &b_muminus_TRUECosTheta);
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
   fChain->SetBranchAddress("muminus_Reconstructible", &muminus_Reconstructible, &b_muminus_Reconstructible);
   fChain->SetBranchAddress("muminus_Reconstructed", &muminus_Reconstructed, &b_muminus_Reconstructed);
   fChain->SetBranchAddress("muminus_ProtoParticles", &muminus_ProtoParticles, &b_muminus_ProtoParticles);
   fChain->SetBranchAddress("muminus_PP_PX", muminus_PP_PX, &b_muminus_PP_PX);
   fChain->SetBranchAddress("muminus_PP_PY", muminus_PP_PY, &b_muminus_PP_PY);
   fChain->SetBranchAddress("muminus_PP_PZ", muminus_PP_PZ, &b_muminus_PP_PZ);
   fChain->SetBranchAddress("muminus_PP_Weight", muminus_PP_Weight, &b_muminus_PP_Weight);
   fChain->SetBranchAddress("muminus_PP_tr_pchi2", muminus_PP_tr_pchi2, &b_muminus_PP_tr_pchi2);
   fChain->SetBranchAddress("muminus_PP_DLLe", muminus_PP_DLLe, &b_muminus_PP_DLLe);
   fChain->SetBranchAddress("muminus_PP_DLLk", muminus_PP_DLLk, &b_muminus_PP_DLLk);
   fChain->SetBranchAddress("muminus_PP_DLLp", muminus_PP_DLLp, &b_muminus_PP_DLLp);
   fChain->SetBranchAddress("muminus_PP_DLLmu", muminus_PP_DLLmu, &b_muminus_PP_DLLmu);
   fChain->SetBranchAddress("muplus_TRUECosTheta", &muplus_TRUECosTheta, &b_muplus_TRUECosTheta);
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
   fChain->SetBranchAddress("muplus_Reconstructible", &muplus_Reconstructible, &b_muplus_Reconstructible);
   fChain->SetBranchAddress("muplus_Reconstructed", &muplus_Reconstructed, &b_muplus_Reconstructed);
   fChain->SetBranchAddress("muplus_ProtoParticles", &muplus_ProtoParticles, &b_muplus_ProtoParticles);
   fChain->SetBranchAddress("muplus_PP_PX", muplus_PP_PX, &b_muplus_PP_PX);
   fChain->SetBranchAddress("muplus_PP_PY", muplus_PP_PY, &b_muplus_PP_PY);
   fChain->SetBranchAddress("muplus_PP_PZ", muplus_PP_PZ, &b_muplus_PP_PZ);
   fChain->SetBranchAddress("muplus_PP_Weight", muplus_PP_Weight, &b_muplus_PP_Weight);
   fChain->SetBranchAddress("muplus_PP_tr_pchi2", muplus_PP_tr_pchi2, &b_muplus_PP_tr_pchi2);
   fChain->SetBranchAddress("muplus_PP_DLLe", muplus_PP_DLLe, &b_muplus_PP_DLLe);
   fChain->SetBranchAddress("muplus_PP_DLLk", muplus_PP_DLLk, &b_muplus_PP_DLLk);
   fChain->SetBranchAddress("muplus_PP_DLLp", muplus_PP_DLLp, &b_muplus_PP_DLLp);
   fChain->SetBranchAddress("muplus_PP_DLLmu", muplus_PP_DLLmu, &b_muplus_PP_DLLmu);
   if (m_isPi){
     fChain->SetBranchAddress("piminus_TRUECosTheta", &piminus_TRUECosTheta, &b_piminus_TRUECosTheta);
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
     fChain->SetBranchAddress("piminus_Reconstructible", &piminus_Reconstructible, &b_piminus_Reconstructible);
     fChain->SetBranchAddress("piminus_Reconstructed", &piminus_Reconstructed, &b_piminus_Reconstructed);
     fChain->SetBranchAddress("piminus_ProtoParticles", &piminus_ProtoParticles, &b_piminus_ProtoParticles);
     fChain->SetBranchAddress("piminus_PP_PX", piminus_PP_PX, &b_piminus_PP_PX);
     fChain->SetBranchAddress("piminus_PP_PY", piminus_PP_PY, &b_piminus_PP_PY);
     fChain->SetBranchAddress("piminus_PP_PZ", piminus_PP_PZ, &b_piminus_PP_PZ);
     fChain->SetBranchAddress("piminus_PP_Weight", piminus_PP_Weight, &b_piminus_PP_Weight);
     fChain->SetBranchAddress("piminus_PP_tr_pchi2", piminus_PP_tr_pchi2, &b_piminus_PP_tr_pchi2);
     fChain->SetBranchAddress("piminus_PP_DLLe", piminus_PP_DLLe, &b_piminus_PP_DLLe);
     fChain->SetBranchAddress("piminus_PP_DLLk", piminus_PP_DLLk, &b_piminus_PP_DLLk);
     fChain->SetBranchAddress("piminus_PP_DLLp", piminus_PP_DLLp, &b_piminus_PP_DLLp);
     fChain->SetBranchAddress("piminus_PP_DLLmu", piminus_PP_DLLmu, &b_piminus_PP_DLLmu);
   } else {
     fChain->SetBranchAddress("Kminus_TRUECosTheta", &piminus_TRUECosTheta, &b_piminus_TRUECosTheta);
     fChain->SetBranchAddress("Kminus_TRUEP_E", &piminus_TRUEP_E, &b_piminus_TRUEP_E);
     fChain->SetBranchAddress("Kminus_TRUEP_X", &piminus_TRUEP_X, &b_piminus_TRUEP_X);
     fChain->SetBranchAddress("Kminus_TRUEP_Y", &piminus_TRUEP_Y, &b_piminus_TRUEP_Y);
     fChain->SetBranchAddress("Kminus_TRUEP_Z", &piminus_TRUEP_Z, &b_piminus_TRUEP_Z);
     fChain->SetBranchAddress("Kminus_TRUEPT", &piminus_TRUEPT, &b_piminus_TRUEPT);
     fChain->SetBranchAddress("Kminus_TRUEORIGINVERTEX_X", &piminus_TRUEORIGINVERTEX_X, &b_piminus_TRUEORIGINVERTEX_X);
     fChain->SetBranchAddress("Kminus_TRUEORIGINVERTEX_Y", &piminus_TRUEORIGINVERTEX_Y, &b_piminus_TRUEORIGINVERTEX_Y);
     fChain->SetBranchAddress("Kminus_TRUEORIGINVERTEX_Z", &piminus_TRUEORIGINVERTEX_Z, &b_piminus_TRUEORIGINVERTEX_Z);
     fChain->SetBranchAddress("Kminus_TRUEENDVERTEX_X", &piminus_TRUEENDVERTEX_X, &b_piminus_TRUEENDVERTEX_X);
     fChain->SetBranchAddress("Kminus_TRUEENDVERTEX_Y", &piminus_TRUEENDVERTEX_Y, &b_piminus_TRUEENDVERTEX_Y);
     fChain->SetBranchAddress("Kminus_TRUEENDVERTEX_Z", &piminus_TRUEENDVERTEX_Z, &b_piminus_TRUEENDVERTEX_Z);
     fChain->SetBranchAddress("Kminus_TRUEISSTABLE", &piminus_TRUEISSTABLE, &b_piminus_TRUEISSTABLE);
     fChain->SetBranchAddress("Kminus_TRUETAU", &piminus_TRUETAU, &b_piminus_TRUETAU);
     fChain->SetBranchAddress("Kminus_Reconstructible", &piminus_Reconstructible, &b_piminus_Reconstructible);
     fChain->SetBranchAddress("Kminus_Reconstructed", &piminus_Reconstructed, &b_piminus_Reconstructed);
     fChain->SetBranchAddress("Kminus_ProtoParticles", &piminus_ProtoParticles, &b_piminus_ProtoParticles);
     fChain->SetBranchAddress("Kminus_PP_PX", piminus_PP_PX, &b_piminus_PP_PX);
     fChain->SetBranchAddress("Kminus_PP_PY", piminus_PP_PY, &b_piminus_PP_PY);
     fChain->SetBranchAddress("Kminus_PP_PZ", piminus_PP_PZ, &b_piminus_PP_PZ);
     fChain->SetBranchAddress("Kminus_PP_Weight", piminus_PP_Weight, &b_piminus_PP_Weight);
     fChain->SetBranchAddress("Kminus_PP_tr_pchi2", piminus_PP_tr_pchi2, &b_piminus_PP_tr_pchi2);
     fChain->SetBranchAddress("Kminus_PP_DLLe", piminus_PP_DLLe, &b_piminus_PP_DLLe);
     fChain->SetBranchAddress("Kminus_PP_DLLk", piminus_PP_DLLk, &b_piminus_PP_DLLk);
     fChain->SetBranchAddress("Kminus_PP_DLLp", piminus_PP_DLLp, &b_piminus_PP_DLLp);
     fChain->SetBranchAddress("Kminus_PP_DLLmu", piminus_PP_DLLmu, &b_piminus_PP_DLLmu);
   }
   fChain->SetBranchAddress("pplus_TRUECosTheta", &pplus_TRUECosTheta, &b_pplus_TRUECosTheta);
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
   fChain->SetBranchAddress("pplus_Reconstructible", &pplus_Reconstructible, &b_pplus_Reconstructible);
   fChain->SetBranchAddress("pplus_Reconstructed", &pplus_Reconstructed, &b_pplus_Reconstructed);
   fChain->SetBranchAddress("pplus_ProtoParticles", &pplus_ProtoParticles, &b_pplus_ProtoParticles);
   fChain->SetBranchAddress("pplus_PP_PX", pplus_PP_PX, &b_pplus_PP_PX);
   fChain->SetBranchAddress("pplus_PP_PY", pplus_PP_PY, &b_pplus_PP_PY);
   fChain->SetBranchAddress("pplus_PP_PZ", pplus_PP_PZ, &b_pplus_PP_PZ);
   fChain->SetBranchAddress("pplus_PP_Weight", pplus_PP_Weight, &b_pplus_PP_Weight);
   fChain->SetBranchAddress("pplus_PP_tr_pchi2", pplus_PP_tr_pchi2, &b_pplus_PP_tr_pchi2);
   fChain->SetBranchAddress("pplus_PP_DLLe", pplus_PP_DLLe, &b_pplus_PP_DLLe);
   fChain->SetBranchAddress("pplus_PP_DLLk", pplus_PP_DLLk, &b_pplus_PP_DLLk);
   fChain->SetBranchAddress("pplus_PP_DLLp", pplus_PP_DLLp, &b_pplus_PP_DLLp);
   fChain->SetBranchAddress("pplus_PP_DLLmu", pplus_PP_DLLmu, &b_pplus_PP_DLLmu);
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
   fChain->SetBranchAddress("StrippingB2JpsiXforBeta_sLambdab2JpsippiDetachedLineDecision", &StrippingB2JpsiXforBeta_sLambdab2JpsippiDetachedLineDecision, &b_StrippingB2JpsiXforBeta_sLambdab2JpsippiDetachedLineDecision);
   fChain->SetBranchAddress("StrippingB2JpsiXforBeta_sLambdab2JpsiLambdaUnbiasedLineDecision", &StrippingB2JpsiXforBeta_sLambdab2JpsiLambdaUnbiasedLineDecision, &b_StrippingB2JpsiXforBeta_sLambdab2JpsiLambdaUnbiasedLineDecision);
   Notify();
}

Bool_t MCTuple::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MCTuple::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MCTuple::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MCTuple_cxx
