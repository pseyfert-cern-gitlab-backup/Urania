//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jul 29 11:32:53 2013 by ROOT version 5.34/04
// from TTree 1/MCTruth
// found on file: GaussMonitor.root
//////////////////////////////////////////////////////////

#ifndef generatorclass_h
#define generatorclass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class generatorclass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           runN;
   Int_t           evtN;
   Int_t           NInter;
   Float_t         procId[5];   //[NInter]
   Float_t         s_hat[5];   //[NInter]
   Float_t         t_hat[5];   //[NInter]
   Float_t         u_hat[5];   //[NInter]
   Float_t         pt_hat[5];   //[NInter]
   Float_t         x1_Bjork[5];   //[NInter]
   Float_t         x2_Bjork[5];   //[NInter]
   Int_t           NPart;
   Float_t         e[2000];   //[NPart]
   Float_t         px[2000];   //[NPart]
   Float_t         py[2000];   //[NPart]
   Float_t         pz[2000];   //[NPart]
   Float_t         vxProd[2000];   //[NPart]
   Float_t         vyProd[2000];   //[NPart]
   Float_t         vzProd[2000];   //[NPart]
   Float_t         vtProd[2000];   //[NPart]
   Float_t         vxDecay[2000];   //[NPart]
   Float_t         vyDecay[2000];   //[NPart]
   Float_t         vzDecay[2000];   //[NPart]
   Float_t         vtDecay[2000];   //[NPart]
   Float_t         pdgId[2000];   //[NPart]
   Float_t         nDau[2000];   //[NPart]
   Float_t         pdgIdMother[2000];   //[NPart]
   Float_t         pdgIdDau1[2000];   //[NPart]
   Float_t         pdgIdDau2[2000];   //[NPart]
   Float_t         pdgIdDau3[2000];   //[NPart]
   Float_t         pdgIdDau4[2000];   //[NPart]
   Float_t         pdgIdDau5[2000];   //[NPart]
   Float_t         pdgIdDau6[2000];   //[NPart]
   Float_t         indexMother[2000];   //[NPart]
   Float_t         indexInter[2000];   //[NPart]

   // List of branches
   TBranch        *b_runN;   //!
   TBranch        *b_evtN;   //!
   TBranch        *b_NInter;   //!
   TBranch        *b_procId;   //!
   TBranch        *b_s_hat;   //!
   TBranch        *b_t_hat;   //!
   TBranch        *b_u_hat;   //!
   TBranch        *b_pt_hat;   //!
   TBranch        *b_x1_Bjork;   //!
   TBranch        *b_x2_Bjork;   //!
   TBranch        *b_NPart;   //!
   TBranch        *b_e;   //!
   TBranch        *b_px;   //!
   TBranch        *b_py;   //!
   TBranch        *b_pz;   //!
   TBranch        *b_vxProd;   //!
   TBranch        *b_vyProd;   //!
   TBranch        *b_vzProd;   //!
   TBranch        *b_vtProd;   //!
   TBranch        *b_vxDecay;   //!
   TBranch        *b_vyDecay;   //!
   TBranch        *b_vzDecay;   //!
   TBranch        *b_vtDecay;   //!
   TBranch        *b_pdgId;   //!
   TBranch        *b_nDau;   //!
   TBranch        *b_pdgIdMother;   //!
   TBranch        *b_pdgIdDau1;   //!
   TBranch        *b_pdgIdDau2;   //!
   TBranch        *b_pdgIdDau3;   //!
   TBranch        *b_pdgIdDau4;   //!
   TBranch        *b_pdgIdDau5;   //!
   TBranch        *b_pdgIdDau6;   //!
   TBranch        *b_indexMother;   //!
   TBranch        *b_indexInter;   //!

   generatorclass(TTree *tree=0);
   virtual ~generatorclass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef generatorclass_cxx
generatorclass::generatorclass(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("GaussMonitor.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("GaussMonitor.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("GaussMonitor.root:/GeneratorFullMonitor");
      dir->GetObject("1",tree);

   }
   Init(tree);
}

generatorclass::~generatorclass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t generatorclass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t generatorclass::LoadTree(Long64_t entry)
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

void generatorclass::Init(TTree *tree)
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

   fChain->SetBranchAddress("runN", &runN, &b_runN);
   fChain->SetBranchAddress("evtN", &evtN, &b_evtN);
   fChain->SetBranchAddress("NInter", &NInter, &b_NInter);
   fChain->SetBranchAddress("procId", procId, &b_procId);
   fChain->SetBranchAddress("s_hat", s_hat, &b_s_hat);
   fChain->SetBranchAddress("t_hat", t_hat, &b_t_hat);
   fChain->SetBranchAddress("u_hat", u_hat, &b_u_hat);
   fChain->SetBranchAddress("pt_hat", pt_hat, &b_pt_hat);
   fChain->SetBranchAddress("x1_Bjork", x1_Bjork, &b_x1_Bjork);
   fChain->SetBranchAddress("x2_Bjork", x2_Bjork, &b_x2_Bjork);
   fChain->SetBranchAddress("NPart", &NPart, &b_NPart);
   fChain->SetBranchAddress("e", e, &b_e);
   fChain->SetBranchAddress("px", px, &b_px);
   fChain->SetBranchAddress("py", py, &b_py);
   fChain->SetBranchAddress("pz", pz, &b_pz);
   fChain->SetBranchAddress("vxProd", vxProd, &b_vxProd);
   fChain->SetBranchAddress("vyProd", vyProd, &b_vyProd);
   fChain->SetBranchAddress("vzProd", vzProd, &b_vzProd);
   fChain->SetBranchAddress("vtProd", vtProd, &b_vtProd);
   fChain->SetBranchAddress("vxDecay", vxDecay, &b_vxDecay);
   fChain->SetBranchAddress("vyDecay", vyDecay, &b_vyDecay);
   fChain->SetBranchAddress("vzDecay", vzDecay, &b_vzDecay);
   fChain->SetBranchAddress("vtDecay", vtDecay, &b_vtDecay);
   fChain->SetBranchAddress("pdgId", pdgId, &b_pdgId);
   fChain->SetBranchAddress("nDau", nDau, &b_nDau);
   fChain->SetBranchAddress("pdgIdMother", pdgIdMother, &b_pdgIdMother);
   fChain->SetBranchAddress("pdgIdDau1", pdgIdDau1, &b_pdgIdDau1);
   fChain->SetBranchAddress("pdgIdDau2", pdgIdDau2, &b_pdgIdDau2);
   fChain->SetBranchAddress("pdgIdDau3", pdgIdDau3, &b_pdgIdDau3);
   fChain->SetBranchAddress("pdgIdDau4", pdgIdDau4, &b_pdgIdDau4);
   fChain->SetBranchAddress("pdgIdDau5", pdgIdDau5, &b_pdgIdDau5);
   fChain->SetBranchAddress("pdgIdDau6", pdgIdDau6, &b_pdgIdDau6);
   fChain->SetBranchAddress("indexMother", indexMother, &b_indexMother);
   fChain->SetBranchAddress("indexInter", indexInter, &b_indexInter);
   Notify();
}

Bool_t generatorclass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void generatorclass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t generatorclass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef generatorclass_cxx
