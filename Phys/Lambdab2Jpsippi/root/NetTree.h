
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
  Double_t        PsipiKMass[100];   //[PVs]
  Double_t        PsiKKMass[100];   //[PVs]
  Double_t        PsiKpMass[100];   //[PVs]
  Double_t        pMMass2[100];   //[PVs]
  Double_t        psiMMass2[100];   //[PVs]
  Double_t        psipMass2[100];   //[PVs]
  Double_t        KKMass[100];   //[PVs]
  Double_t        mprime[100];   //[PVs]
  Double_t        thetaprime[100];   //[PVs]
  Int_t           Category[100];   //[PVs]
  Int_t           ErrorCode[100];   //[PVs]
  Int_t           Baryon;
  Bool_t          Teaching;
  Int_t           BKGCAT;
  Int_t           pTrueID;
  Double_t        DalitzWeight[100];
  Double_t        SPDWeight[100];
  Double_t        PTWeight[100];
  Double_t        NNEffWeight[100];   //[PVs]
  Double_t        CosTheta[100];   //[PVs]
 
  // List of branches
  TBranch        *b_PVs;   //!
  TBranch        *b_EventNumber;   //!
  TBranch        *b_RunNumber;   //!
  TBranch        *b_netOutput;   //!
  TBranch        *b_PsippiMass;   //!
  TBranch        *b_PsipKMass;   //!
  TBranch        *b_PsiKpiMass;   //!
  TBranch        *b_PsipiKMass;   //!
  TBranch        *b_PsiKKMass;   //!
  TBranch        *b_PsiKpMass;   //!
  TBranch        *b_pMMass2;   //!
  TBranch        *b_psiMMass2;   //!
  TBranch        *b_psipMass2;   //!
  TBranch        *b_KKMass;   //!
  TBranch        *b_Category;   //!
  TBranch        *b_ErrorCode;   //!
  TBranch        *b_Baryon;   //!
  TBranch        *b_Teaching;   //!
  TBranch        *b_BKGCAT;   //!
  TBranch        *b_pTrueID ; //!
  TBranch        *b_DalitzWeight ; //!
  TBranch        *b_SPDWeight ; //!
  TBranch        *b_PTWeight ; //!
  TBranch        *b_mprime;   //!
  TBranch        *b_thetaprime;   //!
  TBranch        *b_NNEffWeight;   //!
  TBranch        *b_CosTheta;   //!
   
  NetTree(TString name,TString name2);
  virtual ~NetTree();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  virtual bool blinded(unsigned int pv){
    if (CatCodes::SignalCand!=Category[pv]) return false ;
    if (PsippiMass[pv]<c_ppi_minBlind) return false ;
    if (PsippiMass[pv]>c_ppi_maxBlind) return false ;
    return true ; // this is blinded
  }
  // ####################################################################################################
  // copied from Tuples.icpp
  bool optimisationSample(){
    return (0==EventNumber%c_trainFrac);
  }
  bool trainingSample(){
    return (!optimisationSample());
  }
  
};

#endif

#ifdef NetTree_cxx
NetTree::NetTree(TString name, TString name2) : fChain(0) 
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  TChain* tree = new TChain("NetTree") ;
  tree->Add(name);
  if (""!=name2) tree->Add(name2);
  Init(tree);
  if (name.Contains("MC") || name.Contains("Sim")){
    fChain->SetBranchAddress("BKGCAT", &BKGCAT, &b_BKGCAT);
    fChain->SetBranchAddress("pTrueID", &pTrueID, &b_pTrueID);
    fChain->SetBranchAddress("SPDWeight", &SPDWeight, &b_SPDWeight);
    fChain->SetBranchAddress(c_DalitzWeight, &DalitzWeight, &b_DalitzWeight);
    fChain->SetBranchAddress(c_PTWeight, &PTWeight, &b_PTWeight);
  }
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
  fChain->SetBranchAddress("netOutput", netOutput, &b_netOutput);
  fChain->SetBranchAddress("PsippiMass", PsippiMass, &b_PsippiMass);
  fChain->SetBranchAddress("PsipKMass", PsipKMass, &b_PsipKMass);
  fChain->SetBranchAddress("PsiKpiMass", PsiKpiMass, &b_PsiKpiMass);
  fChain->SetBranchAddress("PsipiKMass", PsipiKMass, &b_PsipiKMass);
  fChain->SetBranchAddress("PsiKKMass", PsiKKMass, &b_PsiKKMass);
  fChain->SetBranchAddress("PsiKpMass", PsiKpMass, &b_PsiKpMass);
  fChain->SetBranchAddress("pMMass2", pMMass2, &b_pMMass2);
  fChain->SetBranchAddress("psiMMass2", psiMMass2, &b_psiMMass2);
  fChain->SetBranchAddress("psipMass2", psipMass2, &b_psipMass2);
  fChain->SetBranchAddress("KKMass", KKMass, &b_KKMass);
  fChain->SetBranchAddress("Category", Category, &b_Category);
  fChain->SetBranchAddress("ErrorCode", ErrorCode, &b_ErrorCode);
  fChain->SetBranchAddress("Baryon", &Baryon, &b_Baryon);
  fChain->SetBranchAddress("Teaching", &Teaching, &b_Teaching);
  fChain->SetBranchAddress("mprime", mprime, &b_mprime);
  fChain->SetBranchAddress("thetaprime", thetaprime, &b_thetaprime);
  fChain->SetBranchAddress("NNEffWeight", NNEffWeight, &b_NNEffWeight);
  fChain->SetBranchAddress("CosTheta", CosTheta, &b_CosTheta);
    
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
