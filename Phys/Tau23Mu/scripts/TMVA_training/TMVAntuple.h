//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Dec 13 00:04:25 2013 by ROOT version 5.34/07
// from TTree TestTree/TestTree
// found on file: 145cf018_MC12vsMC12.root
//////////////////////////////////////////////////////////

#ifndef TMVAntuple_h
#define TMVAntuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.
const Int_t kMaxTMath_Exp__M_1000_T_LifeTime = 1;
const Int_t kMaxacos_dira = 1;
const Int_t kMaxmin_p0_IPSig_min_p1_IPSig_p2_IPSig_ = 1;

class TMVAntuple {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           classID;
   Char_t          className[11];
   Float_t         TMath_Exp__M_1000_T_LifeTime_;
   Float_t         IPSig;
   Float_t         VertexChi2;
   Float_t         acos_dira_;
   Float_t         pt;
   Float_t         min_p0_IPSig_min_p1_IPSig_p2_IPSig__;
   Float_t         DOCAone;
   Float_t         DOCAtwo;
   Float_t         DOCAthree;
   Float_t         CDF3;
   Float_t         p0_track_MatchChi2;
   Float_t         p1_track_MatchChi2;
   Float_t         p2_track_MatchChi2;
   Float_t         weight;
   Float_t         BDT;
   Float_t         MLP;
   Float_t         MLPBFGS;
   Float_t         MLPBNN;
   Float_t         MLPCJ;
   Float_t         MLPMSE;
   Float_t         MLPMSEBFGW;

   // List of branches
   TBranch        *b_classID;   //!
   TBranch        *b_className;   //!
   TBranch        *b_TMath_Exp__M_1000_T_LifeTime_;   //!
   TBranch        *b_IPSig;   //!
   TBranch        *b_VertexChi2;   //!
   TBranch        *b_acos_dira_;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_min_p0_IPSig_min_p1_IPSig_p2_IPSig__;   //!
   TBranch        *b_DOCAone;   //!
   TBranch        *b_DOCAtwo;   //!
   TBranch        *b_DOCAthree;   //!
   TBranch        *b_CDF3;   //!
   TBranch        *b_p0_track_MatchChi2;   //!
   TBranch        *b_p1_track_MatchChi2;   //!
   TBranch        *b_p2_track_MatchChi2;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_BDT;   //!
   TBranch        *b_MLP;   //!
   TBranch        *b_MLPBFGS;   //!
   TBranch        *b_MLPBNN;   //!
   TBranch        *b_MLPCJ;   //!
   TBranch        *b_MLPMSE;   //!
   TBranch        *b_MLPMSEBFGW;   //!

   TMVAntuple(TTree *tree=0);
   virtual ~TMVAntuple();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TMVAntuple_cxx
TMVAntuple::TMVAntuple(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("145cf018_MC12vsMC12.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("145cf018_MC12vsMC12.root");
      }
      f->GetObject("TestTree",tree);

   }
   Init(tree);
}

TMVAntuple::~TMVAntuple()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TMVAntuple::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TMVAntuple::LoadTree(Long64_t entry)
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

void TMVAntuple::Init(TTree *tree)
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

   fChain->SetBranchAddress("classID", &classID, &b_classID);
   fChain->SetBranchAddress("className", className, &b_className);
   fChain->SetBranchAddress("TMath_Exp__M_1000_T_LifeTime_", &TMath_Exp__M_1000_T_LifeTime_, &b_TMath_Exp__M_1000_T_LifeTime_);
   fChain->SetBranchAddress("IPSig", &IPSig, &b_IPSig);
   fChain->SetBranchAddress("VertexChi2", &VertexChi2, &b_VertexChi2);
   fChain->SetBranchAddress("acos_dira_", &acos_dira_, &b_acos_dira_);
   fChain->SetBranchAddress("pt", &pt, &b_pt);
   fChain->SetBranchAddress("min_p0_IPSig,min_p1_IPSig,p2_IPSig__", &min_p0_IPSig_min_p1_IPSig_p2_IPSig__, &b_min_p0_IPSig_min_p1_IPSig_p2_IPSig__);
   fChain->SetBranchAddress("DOCAone", &DOCAone, &b_DOCAone);
   fChain->SetBranchAddress("DOCAtwo", &DOCAtwo, &b_DOCAtwo);
   fChain->SetBranchAddress("DOCAthree", &DOCAthree, &b_DOCAthree);
   fChain->SetBranchAddress("CDF3", &CDF3, &b_CDF3);
   fChain->SetBranchAddress("p0_track_MatchChi2", &p0_track_MatchChi2, &b_p0_track_MatchChi2);
   fChain->SetBranchAddress("p1_track_MatchChi2", &p1_track_MatchChi2, &b_p1_track_MatchChi2);
   fChain->SetBranchAddress("p2_track_MatchChi2", &p2_track_MatchChi2, &b_p2_track_MatchChi2);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("BDT", &BDT, &b_BDT);
   fChain->SetBranchAddress("MLP", &MLP, &b_MLP);
   fChain->SetBranchAddress("MLPBFGS", &MLPBFGS, &b_MLPBFGS);
   fChain->SetBranchAddress("MLPBNN", &MLPBNN, &b_MLPBNN);
   fChain->SetBranchAddress("MLPCJ", &MLPCJ, &b_MLPCJ);
   fChain->SetBranchAddress("MLPMSE", &MLPMSE, &b_MLPMSE);
   fChain->SetBranchAddress("MLPMSEBFGW", &MLPMSEBFGW, &b_MLPMSEBFGW);
   Notify();
}

Bool_t TMVAntuple::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TMVAntuple::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TMVAntuple::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TMVAntuple_cxx
