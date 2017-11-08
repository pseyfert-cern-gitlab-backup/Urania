//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jan 17 15:47:22 2017 by ROOT version 6.06/02
// from TTree DecayTree/tree with weights
// found on file: DsMass_WithSWeighted_Dsst_CB.root
//////////////////////////////////////////////////////////

#ifndef addRegressionData_h
#define addRegressionData_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class addRegressionData{
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Char_t          Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS;
   Double_t        Kpl_P;
   Double_t        Kmi_P;
   Double_t        pi_P;
   Double_t        Kpl_PT;
   Double_t        Kmi_PT;
   Double_t        pi_PT;
   Double_t        Ds_PT;
   Double_t        Bs_0_BDTS_DOCA;
   Double_t        Bs_0_FDCHI2_TOPPV;
   Double_t        Ds_MM;
   Double_t        Bs_MM;
   Double_t        Bs_0_MCORR;
   Double_t        q2;
   Double_t        Emu;
   Double_t        mu_PT;
   Double_t        mu_PIDmu;
   Double_t        mu_iso_MinBDT_Long;
   Int_t           Ds_0_40_nc_mult;
   Double_t        Ds_0_40_nc_maxPt_PX;
   Double_t        Ds_0_40_nc_maxPt_PY;
   Double_t        Ds_0_40_nc_maxPt_PZ;
   Double_t        Ds_0_40_nc_maxPt_PE;
   Double_t        Ds_0_40_nc_CL;
   Int_t           Ds_0_40_pi0_mult;
   Double_t        Ds_0_40_pi0_maxPt_PX;
   Double_t        Ds_0_40_pi0_maxPt_PY;
   Double_t        Ds_0_40_pi0_maxPt_PZ;
   Double_t        Ds_0_40_pi0_maxPt_MM;
   Double_t        Ds_0_40_g1_CL;
   Double_t        Ds_0_40_g2_CL;
   Double_t        Ds_0_40_pi0_maxPt_PE;
   Double_t        Ds_PE;
   Double_t        Ds_PX;
   Double_t        Ds_PY;
   Double_t        Ds_PZ;
   Double_t        Bs_PE;
   Double_t        Bs_PX;
   Double_t        Bs_PY;
   Double_t        Bs_PZ;
   Double_t        Bs_ORIGX;
   Double_t        Bs_ORIGY;
   Double_t        Bs_ORIGZ;
   Double_t        Bs_ENDX;
   Double_t        Bs_ENDY;
   Double_t        Bs_ENDZ;
   Double_t        sigw;
   Double_t        bkgw;
   Double_t        MassDsG;
   Double_t        aDsG;
   Double_t        pBsY;
   Double_t        q2Y;
   Double_t        mm2Y;
   Double_t        thlY;
   Double_t        elcmY;
   Double_t        wY;
   Double_t        pBsP1;
   Double_t        q2P1;
   Double_t        mm2P1;
   Double_t        thlP1;
   Double_t        elcmP1;
   Double_t        wP1;
   Double_t        pBsP2;
   Double_t        q2P2;
   Double_t        mm2P2;
   Double_t        thlP2;
   Double_t        elcmP2;
   Double_t        wP2;
   Double_t        sq;
   Double_t        McorrDsst;
   Double_t        bSinFlightAng;
   Double_t        bFlightLen;

   // List of branches
   TBranch        *b_Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS;   //!
   TBranch        *b_Kpl_P;   //!
   TBranch        *b_Kmi_P;   //!
   TBranch        *b_pi_P;   //!
   TBranch        *b_Kpl_PT;   //!
   TBranch        *b_Kmi_PT;   //!
   TBranch        *b_pi_PT;   //!
   TBranch        *b_Ds_PT;   //!
   TBranch        *b_Bs_0_BDTS_DOCA;   //!
   TBranch        *b_Bs_0_FDCHI2_TOPPV;   //!
   TBranch        *b_Ds_MM;   //!
   TBranch        *b_Bs_MM;   //!
   TBranch        *b_Bs_0_MCORR;   //!
   TBranch        *b_q2;   //!
   TBranch        *b_Emu;   //!
   TBranch        *b_mu_PT;   //!
   TBranch        *b_mu_PIDmu;   //!
   TBranch        *b_mu_iso_MinBDT_Long;   //!
   TBranch        *b_Ds_0_40_nc_mult;   //!
   TBranch        *b_Ds_0_40_nc_maxPt_PX;   //!
   TBranch        *b_Ds_0_40_nc_maxPt_PY;   //!
   TBranch        *b_Ds_0_40_nc_maxPt_PZ;   //!
   TBranch        *b_Ds_0_40_nc_maxPt_PE;   //!
   TBranch        *b_Ds_0_40_nc_CL;   //!
   TBranch        *b_Ds_0_40_pi0_mult;   //!
   TBranch        *b_Ds_0_40_pi0_maxPt_PX;   //!
   TBranch        *b_Ds_0_40_pi0_maxPt_PY;   //!
   TBranch        *b_Ds_0_40_pi0_maxPt_PZ;   //!
   TBranch        *b_Ds_0_40_pi0_maxPt_MM;   //!
   TBranch        *b_Ds_0_40_g1_CL;   //!
   TBranch        *b_Ds_0_40_g2_CL;   //!
   TBranch        *b_Ds_0_40_pi0_maxPt_PE;   //!
   TBranch        *b_Ds_PE;   //!
   TBranch        *b_Ds_PX;   //!
   TBranch        *b_Ds_PY;   //!
   TBranch        *b_Ds_PZ;   //!
   TBranch        *b_Bs_PE;   //!
   TBranch        *b_Bs_PX;   //!
   TBranch        *b_Bs_PY;   //!
   TBranch        *b_Bs_PZ;   //!
   TBranch        *b_Bs_ORIGX;   //!
   TBranch        *b_Bs_ORIGY;   //!
   TBranch        *b_Bs_ORIGZ;   //!
   TBranch        *b_Bs_ENDX;   //!
   TBranch        *b_Bs_ENDY;   //!
   TBranch        *b_Bs_ENDZ;   //!
   TBranch        *b_sigw;   //!
   TBranch        *b_bkgw;   //!
   TBranch        *b_MassDsG;   //!
   TBranch        *b_aDsG;   //!
   TBranch        *b_pBsY;   //!
   TBranch        *b_q2Y;   //!
   TBranch        *b_mm2Y;   //!
   TBranch        *b_thlY;   //!
   TBranch        *b_elcmY;   //!
   TBranch        *b_wY;   //!
   TBranch        *b_pBsP1;   //!
   TBranch        *b_q2P1;   //!
   TBranch        *b_mm2P1;   //!
   TBranch        *b_thlP1;   //!
   TBranch        *b_elcmP1;   //!
   TBranch        *b_wP1;   //!
   TBranch        *b_pBsP2;   //!
   TBranch        *b_q2P2;   //!
   TBranch        *b_mm2P2;   //!
   TBranch        *b_thlP2;   //!
   TBranch        *b_elcmP2;   //!
   TBranch        *b_wP2;   //!
   TBranch        *b_sq;   //!
   TBranch        *b_McorrDsst;   //!
   TBranch        *b_bSinFlightAng;   //!
   TBranch        *b_bFlightLen;   //!

   addRegressionData(TTree *tree=0);
   virtual ~addRegressionData();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef addRegressionData_cxx
addRegressionData::addRegressionData(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("DsMass_WithSWeighted_Dsst_LbDD_NoCL_CB_Sim09b.root");
      if (!f || !f->IsOpen()) {
         r = new TFile("DsMass_WithSWeighted_Dsst_LbDD_NoCL_CB_Sim09b.root","update");
      }
      f->GetObject("DecayTree",tree);

   }
   Init(tree);
}

addRegressionData::~addRegressionData()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t addRegressionData::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t addRegressionData::LoadTree(Long64_t entry)
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

void addRegressionData::Init(TTree *tree)
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

   fChain->SetBranchAddress("Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS", &Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS, &b_Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS);
   fChain->SetBranchAddress("Kpl_P", &Kpl_P, &b_Kpl_P);
   fChain->SetBranchAddress("Kmi_P", &Kmi_P, &b_Kmi_P);
   fChain->SetBranchAddress("pi_P", &pi_P, &b_pi_P);
   fChain->SetBranchAddress("Kpl_PT", &Kpl_PT, &b_Kpl_PT);
   fChain->SetBranchAddress("Kmi_PT", &Kmi_PT, &b_Kmi_PT);
   fChain->SetBranchAddress("pi_PT", &pi_PT, &b_pi_PT);
   fChain->SetBranchAddress("Ds_PT", &Ds_PT, &b_Ds_PT);
   fChain->SetBranchAddress("Bs_0_BDTS_DOCA", &Bs_0_BDTS_DOCA, &b_Bs_0_BDTS_DOCA);
   fChain->SetBranchAddress("Bs_0_FDCHI2_TOPPV", &Bs_0_FDCHI2_TOPPV, &b_Bs_0_FDCHI2_TOPPV);
   fChain->SetBranchAddress("Ds_MM", &Ds_MM, &b_Ds_MM);
   fChain->SetBranchAddress("Bs_MM", &Bs_MM, &b_Bs_MM);
   fChain->SetBranchAddress("Bs_0_MCORR", &Bs_0_MCORR, &b_Bs_0_MCORR);
   fChain->SetBranchAddress("q2", &q2, &b_q2);
   fChain->SetBranchAddress("Emu", &Emu, &b_Emu);
   fChain->SetBranchAddress("mu_PT", &mu_PT, &b_mu_PT);
   fChain->SetBranchAddress("mu_PIDmu", &mu_PIDmu, &b_mu_PIDmu);
   fChain->SetBranchAddress("mu_iso_MinBDT_Long", &mu_iso_MinBDT_Long, &b_mu_iso_MinBDT_Long);
   fChain->SetBranchAddress("Ds_0.40_nc_mult", &Ds_0_40_nc_mult, &b_Ds_0_40_nc_mult);
   fChain->SetBranchAddress("Ds_0.40_nc_maxPt_PX", &Ds_0_40_nc_maxPt_PX, &b_Ds_0_40_nc_maxPt_PX);
   fChain->SetBranchAddress("Ds_0.40_nc_maxPt_PY", &Ds_0_40_nc_maxPt_PY, &b_Ds_0_40_nc_maxPt_PY);
   fChain->SetBranchAddress("Ds_0.40_nc_maxPt_PZ", &Ds_0_40_nc_maxPt_PZ, &b_Ds_0_40_nc_maxPt_PZ);
   fChain->SetBranchAddress("Ds_0.40_nc_maxPt_PE", &Ds_0_40_nc_maxPt_PE, &b_Ds_0_40_nc_maxPt_PE);
   fChain->SetBranchAddress("Ds_0.40_nc_CL", &Ds_0_40_nc_CL, &b_Ds_0_40_nc_CL);
   fChain->SetBranchAddress("Ds_0.40_pi0_mult", &Ds_0_40_pi0_mult, &b_Ds_0_40_pi0_mult);
   fChain->SetBranchAddress("Ds_0.40_pi0_maxPt_PX", &Ds_0_40_pi0_maxPt_PX, &b_Ds_0_40_pi0_maxPt_PX);
   fChain->SetBranchAddress("Ds_0.40_pi0_maxPt_PY", &Ds_0_40_pi0_maxPt_PY, &b_Ds_0_40_pi0_maxPt_PY);
   fChain->SetBranchAddress("Ds_0.40_pi0_maxPt_PZ", &Ds_0_40_pi0_maxPt_PZ, &b_Ds_0_40_pi0_maxPt_PZ);
   fChain->SetBranchAddress("Ds_0.40_pi0_maxPt_MM", &Ds_0_40_pi0_maxPt_MM, &b_Ds_0_40_pi0_maxPt_MM);
   fChain->SetBranchAddress("Ds_0.40_g1_CL", &Ds_0_40_g1_CL, &b_Ds_0_40_g1_CL);
   fChain->SetBranchAddress("Ds_0.40_g2_CL", &Ds_0_40_g2_CL, &b_Ds_0_40_g2_CL);
   fChain->SetBranchAddress("Ds_0.40_pi0_maxPt_PE", &Ds_0_40_pi0_maxPt_PE, &b_Ds_0_40_pi0_maxPt_PE);
   fChain->SetBranchAddress("Ds_PE", &Ds_PE, &b_Ds_PE);
   fChain->SetBranchAddress("Ds_PX", &Ds_PX, &b_Ds_PX);
   fChain->SetBranchAddress("Ds_PY", &Ds_PY, &b_Ds_PY);
   fChain->SetBranchAddress("Ds_PZ", &Ds_PZ, &b_Ds_PZ);
   fChain->SetBranchAddress("Bs_PE", &Bs_PE, &b_Bs_PE);
   fChain->SetBranchAddress("Bs_PX", &Bs_PX, &b_Bs_PX);
   fChain->SetBranchAddress("Bs_PY", &Bs_PY, &b_Bs_PY);
   fChain->SetBranchAddress("Bs_PZ", &Bs_PZ, &b_Bs_PZ);
   fChain->SetBranchAddress("Bs_ORIGX", &Bs_ORIGX, &b_Bs_ORIGX);
   fChain->SetBranchAddress("Bs_ORIGY", &Bs_ORIGY, &b_Bs_ORIGY);
   fChain->SetBranchAddress("Bs_ORIGZ", &Bs_ORIGZ, &b_Bs_ORIGZ);
   fChain->SetBranchAddress("Bs_ENDX", &Bs_ENDX, &b_Bs_ENDX);
   fChain->SetBranchAddress("Bs_ENDY", &Bs_ENDY, &b_Bs_ENDY);
   fChain->SetBranchAddress("Bs_ENDZ", &Bs_ENDZ, &b_Bs_ENDZ);
   fChain->SetBranchAddress("sigw", &sigw, &b_sigw);
   fChain->SetBranchAddress("bkgw", &bkgw, &b_bkgw);
   fChain->SetBranchAddress("MassDsG", &MassDsG, &b_MassDsG);
   fChain->SetBranchAddress("aDsG", &aDsG, &b_aDsG);
   fChain->SetBranchAddress("pBsY", &pBsY, &b_pBsY);
   fChain->SetBranchAddress("q2Y", &q2Y, &b_q2Y);
   fChain->SetBranchAddress("mm2Y", &mm2Y, &b_mm2Y);
   fChain->SetBranchAddress("thlY", &thlY, &b_thlY);
   fChain->SetBranchAddress("elcmY", &elcmY, &b_elcmY);
   fChain->SetBranchAddress("wY", &wY, &b_wY);
   fChain->SetBranchAddress("pBsP1", &pBsP1, &b_pBsP1);
   fChain->SetBranchAddress("q2P1", &q2P1, &b_q2P1);
   fChain->SetBranchAddress("mm2P1", &mm2P1, &b_mm2P1);
   fChain->SetBranchAddress("thlP1", &thlP1, &b_thlP1);
   fChain->SetBranchAddress("elcmP1", &elcmP1, &b_elcmP1);
   fChain->SetBranchAddress("wP1", &wP1, &b_wP1);
   fChain->SetBranchAddress("pBsP2", &pBsP2, &b_pBsP2);
   fChain->SetBranchAddress("q2P2", &q2P2, &b_q2P2);
   fChain->SetBranchAddress("mm2P2", &mm2P2, &b_mm2P2);
   fChain->SetBranchAddress("thlP2", &thlP2, &b_thlP2);
   fChain->SetBranchAddress("elcmP2", &elcmP2, &b_elcmP2);
   fChain->SetBranchAddress("wP2", &wP2, &b_wP2);
   fChain->SetBranchAddress("sq", &sq, &b_sq);
   fChain->SetBranchAddress("McorrDsst", &McorrDsst, &b_McorrDsst);
   fChain->SetBranchAddress("bSinFlightAng", &bSinFlightAng, &b_bSinFlightAng);
   fChain->SetBranchAddress("bFlightLen", &bFlightLen, &b_bFlightLen);
   Notify();
}

Bool_t addRegressionData::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void addRegressionData::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t addRegressionData::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef addRegressionData_cxx
