
//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Oct 22 15:31:13 2012 by ROOT version 5.32/02
// from TTree NetTree/Neural Net Tree
// found on file: LambdabMC-MC11-Lb2Jpsippi-707-712-NN.root
//////////////////////////////////////////////////////////

#ifndef NetTree_h
#define NetTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "Tuples.h"

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class NetTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           PVs;
   ULong64_t       EventNumber;
   UInt_t          RunNumber;
   Double_t        netOutput[100];   //[PVs]
   Double_t        PsippiMass[100];   //[PVs]
   Double_t        PsipKMass[100];   //[PVs]
   Double_t        PsiKpiMass[100];   //[PVs]
   Double_t        pMMass2[100];   //[PVs]
   Double_t        psiMMass2[100];   //[PVs]
   Double_t        psipMass2[100];   //[PVs]
   Int_t           Category[100];   //[PVs]
   Int_t           ErrorCode[100];   //[PVs]
   Int_t           Baryon;
   Int_t           BKGCAT;
   Bool_t          Teaching;

   // List of branches
   TBranch        *b_PVs;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_netOutput;   //!
   TBranch        *b_PsippiMass;   //!
   TBranch        *b_PsipKMass;   //!
   TBranch        *b_PsiKpiMass;   //!
   TBranch        *b_pMMass2;   //!
   TBranch        *b_psiMMass2;   //!
   TBranch        *b_psipMass2;   //!
   TBranch        *b_Category;   //!
   TBranch        *b_Baryon;   //!
   TBranch        *b_ErrorCode;   //!
   TBranch        *b_BKGCAT;   //!
   TBranch        *b_Teaching;   //!

   NetTree(TString name);
   virtual ~NetTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef NetTree_cxx
NetTree::NetTree(TString name) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  TTree* tree ;
  TFile *f = TFile::Open(name);
  f->GetObject("NetTree",tree);
  Init(tree);
}

NetTree::~NetTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t NetTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t NetTree::LoadTree(Long64_t entry)
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

void NetTree::Init(TTree *tree)
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

   fChain->SetBranchAddress("PVs", &PVs, &b_PVs);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress(c_NetOutput, netOutput, &b_netOutput);
   fChain->SetBranchAddress(c_PsippiMass, PsippiMass, &b_PsippiMass);
   fChain->SetBranchAddress(c_PsipKMass, PsipKMass, &b_PsipKMass);
   fChain->SetBranchAddress(c_PsiKpiMass, PsiKpiMass, &b_PsiKpiMass);
   fChain->SetBranchAddress("pMMass2", pMMass2, &b_pMMass2);
   fChain->SetBranchAddress("psiMMass2", psiMMass2, &b_psiMMass2);
   fChain->SetBranchAddress("psipMass2", psipMass2, &b_psipMass2);
   fChain->SetBranchAddress(c_Category, Category, &b_Category);
   fChain->SetBranchAddress(c_Baryon, &Baryon, &b_Baryon);
   fChain->SetBranchAddress("BKGCAT", &BKGCAT, &b_BKGCAT);
   fChain->SetBranchAddress("Teaching", &Teaching, &b_Teaching);
   fChain->SetBranchAddress(c_ErrorCode, &ErrorCode, &b_ErrorCode);
   Notify();
}

Bool_t NetTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void NetTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t NetTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef NetTree_cxx
