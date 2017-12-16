//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Nov  2 22:01:41 2011 by ROOT version 5.30/02
// from TTree StrippingTriMuonsTau23MuLine/StrippingTriMuonsTau23MuLine
// found on file: mctru_xx_mud_noBDT_flat.root
//////////////////////////////////////////////////////////

#ifndef flatclass_h
#define flatclass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class flatclass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   int             loopcount;

   // Declaration of leaf types
   Int_t           runNumber;
   Float_t         eventNumber;
   Int_t           TCK;
   Float_t         Strip15And17;
   Int_t           cleaningcut;
   Int_t           jonpid;
   Int_t           jongeo;
   Float_t         L0Dec;
   Float_t         Hlt1Dec;
   Float_t         Hlt2Dec;
   Float_t         L0Hlt1DecMu;
   Float_t         Hlt2DecMu;
   Float_t         Hlt2DecSingleMu;
   Float_t         Hlt2DecDhhh;
   Int_t           truetau;
   Int_t           particleid;
   Float_t         FlightDistance;
   Float_t         FlightDistanceError;
   Float_t         mass;
   Float_t         LifeTime;
   Float_t         IP;
   Float_t         IPSig;
   Float_t         VertexChi2;
   Float_t         dira;
   Float_t         pt;
   Float_t         p0_IP;
   Float_t         p1_IP;
   Float_t         p2_IP;
   Float_t         p0_IPSig;
   Float_t         p1_IPSig;
   Float_t         p2_IPSig;
   Float_t         DOCAone;
   Float_t         DOCAtwo;
   Float_t         DOCAthree;
   Float_t         mass_p0p2;
   Float_t         mass_p1p2;
   Float_t         mass_p0p1;
   Float_t         IP_p0p2;
   Float_t         IP_p1p2;
   Float_t         p0_pt;
   Float_t         p1_pt;
   Float_t         p2_pt;
   Float_t         p0_track_Chi2Dof;
   Float_t         p1_track_Chi2Dof;
   Float_t         p2_track_Chi2Dof;
   Float_t         p0_cloneDist;
   Float_t         p1_cloneDist;
   Float_t         p2_cloneDist;
   Float_t         ptorderedp0_IPSig;
   Float_t         ptorderedp1_IPSig;
   Float_t         ptorderedp2_IPSig;
   Float_t         ptorderedp0_pt;
   Float_t         ptorderedp1_pt;
   Float_t         ptorderedp2_pt;
   Float_t         ptorderedp0_p0_track_Chi2Dof;
   Float_t         ptorderedp1_p1_track_Chi2Dof;
   Float_t         ptorderedp2_p2_track_Chi2Dof;
   Float_t         p0_PIDmupi;
   Float_t         p1_PIDmupi;
   Float_t         p2_PIDmupi;
   Float_t         p0_PIDmuk;
   Float_t         p1_PIDmuk;
   Float_t         p2_PIDmuk;
   Float_t         p0_NShared;
   Float_t         p1_NShared;
   Float_t         p2_NShared;
   Float_t         p0_MuLL;
   Float_t         p1_MuLL;
   Float_t         p2_MuLL;
   Float_t         p0_MuDLL;
   Float_t         p1_MuDLL;
   Float_t         p2_MuDLL;
   Float_t         ptorderedp0_PIDmupi;
   Float_t         ptorderedp1_PIDmupi;
   Float_t         ptorderedp2_PIDmupi;
   Float_t         ptorderedp0_PIDmuk;
   Float_t         ptorderedp1_PIDmuk;
   Float_t         ptorderedp2_PIDmuk;
   Int_t           isolationa;
   Int_t           isolationb;
   Int_t           isolationc;
   Int_t           isolationd;
   Int_t           isolatione;
   Int_t           isolationf;
   Float_t         CDF1;
   Float_t         CDF2;
   Float_t         CDF3;
   Float_t         PIDMVA;
   Float_t         GeoMVA;
   Int_t           BCK;

   // List of branches
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_TCK;   //!
   TBranch        *b_Strip15And17;   //!
   TBranch        *b_cleaningcut;   //!
   TBranch        *b_jonpid;   //!
   TBranch        *b_jongeo;   //!
   TBranch        *b_L0Dec;   //!
   TBranch        *b_Hlt1Dec;   //!
   TBranch        *b_Hlt2Dec;   //!
   TBranch        *b_L0Hlt1DecMu;   //!
   TBranch        *b_Hlt2DecMu;   //!
   TBranch        *b_Hlt2DecSingleMu;   //!
   TBranch        *b_Hlt2DecDhhh;   //!
   TBranch        *b_truetau;   //!
   TBranch        *b_particleid;   //!
   TBranch        *b_FlightDistance;   //!
   TBranch        *b_FlightDistanceError;   //!
   TBranch        *b_mass;   //!
   TBranch        *b_LifeTime;   //!
   TBranch        *b_IP;   //!
   TBranch        *b_IPSig;   //!
   TBranch        *b_VertexChi2;   //!
   TBranch        *b_dira;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_p0_IP;   //!
   TBranch        *b_p1_IP;   //!
   TBranch        *b_p2_IP;   //!
   TBranch        *b_p0_IPSig;   //!
   TBranch        *b_p1_IPSig;   //!
   TBranch        *b_p2_IPSig;   //!
   TBranch        *b_DOCAone;   //!
   TBranch        *b_DOCAtwo;   //!
   TBranch        *b_DOCAthree;   //!
   TBranch        *b_mass_p0p2;   //!
   TBranch        *b_mass_p1p2;   //!
   TBranch        *b_mass_p0p1;   //!
   TBranch        *b_IP_p0p2;   //!
   TBranch        *b_IP_p1p2;   //!
   TBranch        *b_p0_pt;   //!
   TBranch        *b_p1_pt;   //!
   TBranch        *b_p2_pt;   //!
   TBranch        *b_p0_track_Chi2Dof;   //!
   TBranch        *b_p1_track_Chi2Dof;   //!
   TBranch        *b_p2_track_Chi2Dof;   //!
   TBranch        *b_p0_cloneDist;   //!
   TBranch        *b_p1_cloneDist;   //!
   TBranch        *b_p2_cloneDist;   //!
   TBranch        *b_ptorderedp0_IPSig;   //!
   TBranch        *b_ptorderedp1_IPSig;   //!
   TBranch        *b_ptorderedp2_IPSig;   //!
   TBranch        *b_ptorderedp0_pt;   //!
   TBranch        *b_ptorderedp1_pt;   //!
   TBranch        *b_ptorderedp2_pt;   //!
   TBranch        *b_ptorderedp0_p0_track_Chi2Dof;   //!
   TBranch        *b_ptorderedp1_p1_track_Chi2Dof;   //!
   TBranch        *b_ptorderedp2_p2_track_Chi2Dof;   //!
   TBranch        *b_p0_PIDmupi;   //!
   TBranch        *b_p1_PIDmupi;   //!
   TBranch        *b_p2_PIDmupi;   //!
   TBranch        *b_p0_PIDmuk;   //!
   TBranch        *b_p1_PIDmuk;   //!
   TBranch        *b_p2_PIDmuk;   //!
   TBranch        *b_p0_NShared;   //!
   TBranch        *b_p1_NShared;   //!
   TBranch        *b_p2_NShared;   //!
   TBranch        *b_p0_MuLL;   //!
   TBranch        *b_p1_MuLL;   //!
   TBranch        *b_p2_MuLL;   //!
   TBranch        *b_p0_MuDLL;   //!
   TBranch        *b_p1_MuDLL;   //!
   TBranch        *b_p2_MuDLL;   //!
   TBranch        *b_ptorderedp0_PIDmupi;   //!
   TBranch        *b_ptorderedp1_PIDmupi;   //!
   TBranch        *b_ptorderedp2_PIDmupi;   //!
   TBranch        *b_ptorderedp0_PIDmuk;   //!
   TBranch        *b_ptorderedp1_PIDmuk;   //!
   TBranch        *b_ptorderedp2_PIDmuk;   //!
   TBranch        *b_isolationa;   //!
   TBranch        *b_isolationb;   //!
   TBranch        *b_isolationc;   //!
   TBranch        *b_isolationd;   //!
   TBranch        *b_isolatione;   //!
   TBranch        *b_isolationf;   //!
   TBranch        *b_CDF1;   //!
   TBranch        *b_CDF2;   //!
   TBranch        *b_CDF3;   //!
   TBranch        *b_PIDMVA;   //!
   TBranch        *b_GeoMVA;   //!
   TBranch        *b_BCK;   //!

   flatclass(TTree *tree=0);
   virtual ~flatclass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   TH1*             Loop(const char* selection,TH1* bcks=NULL);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef flatclass_cxx
flatclass::flatclass(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   loopcount = 0;
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("mctru_xx_mud_noBDT_flat.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("mctru_xx_mud_noBDT_flat.root");
      }
      f->GetObject("StrippingTriMuonsTau23MuLine",tree);

   }
   Init(tree);
}

flatclass::~flatclass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t flatclass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t flatclass::LoadTree(Long64_t entry)
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

void flatclass::Init(TTree *tree)
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

   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("TCK", &TCK, &b_TCK);
   fChain->SetBranchAddress("Strip15And17", &Strip15And17, &b_Strip15And17);
   fChain->SetBranchAddress("cleaningcut", &cleaningcut, &b_cleaningcut);
   fChain->SetBranchAddress("jonpid", &jonpid, &b_jonpid);
   fChain->SetBranchAddress("jongeo", &jongeo, &b_jongeo);
   fChain->SetBranchAddress("L0Dec", &L0Dec, &b_L0Dec);
   fChain->SetBranchAddress("Hlt1Dec", &Hlt1Dec, &b_Hlt1Dec);
   fChain->SetBranchAddress("Hlt2Dec", &Hlt2Dec, &b_Hlt2Dec);
   fChain->SetBranchAddress("L0Hlt1DecMu", &L0Hlt1DecMu, &b_L0Hlt1DecMu);
   fChain->SetBranchAddress("Hlt2DecMu", &Hlt2DecMu, &b_Hlt2DecMu);
   fChain->SetBranchAddress("Hlt2DecSingleMu", &Hlt2DecSingleMu, &b_Hlt2DecSingleMu);
   fChain->SetBranchAddress("Hlt2DecDhhh", &Hlt2DecDhhh, &b_Hlt2DecDhhh);
   fChain->SetBranchAddress("truetau", &truetau, &b_truetau);
   fChain->SetBranchAddress("particleid", &particleid, &b_particleid);
   fChain->SetBranchAddress("FlightDistance", &FlightDistance, &b_FlightDistance);
   fChain->SetBranchAddress("FlightDistanceError", &FlightDistanceError, &b_FlightDistanceError);
   fChain->SetBranchAddress("mass", &mass, &b_mass);
   fChain->SetBranchAddress("LifeTime", &LifeTime, &b_LifeTime);
   fChain->SetBranchAddress("IP", &IP, &b_IP);
   fChain->SetBranchAddress("IPSig", &IPSig, &b_IPSig);
   fChain->SetBranchAddress("VertexChi2", &VertexChi2, &b_VertexChi2);
   fChain->SetBranchAddress("dira", &dira, &b_dira);
   fChain->SetBranchAddress("pt", &pt, &b_pt);
   fChain->SetBranchAddress("p0_IP", &p0_IP, &b_p0_IP);
   fChain->SetBranchAddress("p1_IP", &p1_IP, &b_p1_IP);
   fChain->SetBranchAddress("p2_IP", &p2_IP, &b_p2_IP);
   fChain->SetBranchAddress("p0_IPSig", &p0_IPSig, &b_p0_IPSig);
   fChain->SetBranchAddress("p1_IPSig", &p1_IPSig, &b_p1_IPSig);
   fChain->SetBranchAddress("p2_IPSig", &p2_IPSig, &b_p2_IPSig);
   fChain->SetBranchAddress("DOCAone", &DOCAone, &b_DOCAone);
   fChain->SetBranchAddress("DOCAtwo", &DOCAtwo, &b_DOCAtwo);
   fChain->SetBranchAddress("DOCAthree", &DOCAthree, &b_DOCAthree);
   fChain->SetBranchAddress("mass_p0p2", &mass_p0p2, &b_mass_p0p2);
   fChain->SetBranchAddress("mass_p1p2", &mass_p1p2, &b_mass_p1p2);
   fChain->SetBranchAddress("mass_p0p1", &mass_p0p1, &b_mass_p0p1);
   fChain->SetBranchAddress("IP_p0p2", &IP_p0p2, &b_IP_p0p2);
   fChain->SetBranchAddress("IP_p1p2", &IP_p1p2, &b_IP_p1p2);
   fChain->SetBranchAddress("p0_pt", &p0_pt, &b_p0_pt);
   fChain->SetBranchAddress("p1_pt", &p1_pt, &b_p1_pt);
   fChain->SetBranchAddress("p2_pt", &p2_pt, &b_p2_pt);
   fChain->SetBranchAddress("p0_track_Chi2Dof", &p0_track_Chi2Dof, &b_p0_track_Chi2Dof);
   fChain->SetBranchAddress("p1_track_Chi2Dof", &p1_track_Chi2Dof, &b_p1_track_Chi2Dof);
   fChain->SetBranchAddress("p2_track_Chi2Dof", &p2_track_Chi2Dof, &b_p2_track_Chi2Dof);
   fChain->SetBranchAddress("p0_cloneDist", &p0_cloneDist, &b_p0_cloneDist);
   fChain->SetBranchAddress("p1_cloneDist", &p1_cloneDist, &b_p1_cloneDist);
   fChain->SetBranchAddress("p2_cloneDist", &p2_cloneDist, &b_p2_cloneDist);
   fChain->SetBranchAddress("ptorderedp0_IPSig", &ptorderedp0_IPSig, &b_ptorderedp0_IPSig);
   fChain->SetBranchAddress("ptorderedp1_IPSig", &ptorderedp1_IPSig, &b_ptorderedp1_IPSig);
   fChain->SetBranchAddress("ptorderedp2_IPSig", &ptorderedp2_IPSig, &b_ptorderedp2_IPSig);
   fChain->SetBranchAddress("ptorderedp0_pt", &ptorderedp0_pt, &b_ptorderedp0_pt);
   fChain->SetBranchAddress("ptorderedp1_pt", &ptorderedp1_pt, &b_ptorderedp1_pt);
   fChain->SetBranchAddress("ptorderedp2_pt", &ptorderedp2_pt, &b_ptorderedp2_pt);
   fChain->SetBranchAddress("ptorderedp0_p0_track_Chi2Dof", &ptorderedp0_p0_track_Chi2Dof, &b_ptorderedp0_p0_track_Chi2Dof);
   fChain->SetBranchAddress("ptorderedp1_p1_track_Chi2Dof", &ptorderedp1_p1_track_Chi2Dof, &b_ptorderedp1_p1_track_Chi2Dof);
   fChain->SetBranchAddress("ptorderedp2_p2_track_Chi2Dof", &ptorderedp2_p2_track_Chi2Dof, &b_ptorderedp2_p2_track_Chi2Dof);
   fChain->SetBranchAddress("p0_PIDmupi", &p0_PIDmupi, &b_p0_PIDmupi);
   fChain->SetBranchAddress("p1_PIDmupi", &p1_PIDmupi, &b_p1_PIDmupi);
   fChain->SetBranchAddress("p2_PIDmupi", &p2_PIDmupi, &b_p2_PIDmupi);
   fChain->SetBranchAddress("p0_PIDmuk", &p0_PIDmuk, &b_p0_PIDmuk);
   fChain->SetBranchAddress("p1_PIDmuk", &p1_PIDmuk, &b_p1_PIDmuk);
   fChain->SetBranchAddress("p2_PIDmuk", &p2_PIDmuk, &b_p2_PIDmuk);
   fChain->SetBranchAddress("p0_NShared", &p0_NShared, &b_p0_NShared);
   fChain->SetBranchAddress("p1_NShared", &p1_NShared, &b_p1_NShared);
   fChain->SetBranchAddress("p2_NShared", &p2_NShared, &b_p2_NShared);
   fChain->SetBranchAddress("p0_MuLL", &p0_MuLL, &b_p0_MuLL);
   fChain->SetBranchAddress("p1_MuLL", &p1_MuLL, &b_p1_MuLL);
   fChain->SetBranchAddress("p2_MuLL", &p2_MuLL, &b_p2_MuLL);
   fChain->SetBranchAddress("p0_MuDLL", &p0_MuDLL, &b_p0_MuDLL);
   fChain->SetBranchAddress("p1_MuDLL", &p1_MuDLL, &b_p1_MuDLL);
   fChain->SetBranchAddress("p2_MuDLL", &p2_MuDLL, &b_p2_MuDLL);
   fChain->SetBranchAddress("ptorderedp0_PIDmupi", &ptorderedp0_PIDmupi, &b_ptorderedp0_PIDmupi);
   fChain->SetBranchAddress("ptorderedp1_PIDmupi", &ptorderedp1_PIDmupi, &b_ptorderedp1_PIDmupi);
   fChain->SetBranchAddress("ptorderedp2_PIDmupi", &ptorderedp2_PIDmupi, &b_ptorderedp2_PIDmupi);
   fChain->SetBranchAddress("ptorderedp0_PIDmuk", &ptorderedp0_PIDmuk, &b_ptorderedp0_PIDmuk);
   fChain->SetBranchAddress("ptorderedp1_PIDmuk", &ptorderedp1_PIDmuk, &b_ptorderedp1_PIDmuk);
   fChain->SetBranchAddress("ptorderedp2_PIDmuk", &ptorderedp2_PIDmuk, &b_ptorderedp2_PIDmuk);
   fChain->SetBranchAddress("isolationa", &isolationa, &b_isolationa);
   fChain->SetBranchAddress("isolationb", &isolationb, &b_isolationb);
   fChain->SetBranchAddress("isolationc", &isolationc, &b_isolationc);
   fChain->SetBranchAddress("isolationd", &isolationd, &b_isolationd);
   fChain->SetBranchAddress("isolatione", &isolatione, &b_isolatione);
   fChain->SetBranchAddress("isolationf", &isolationf, &b_isolationf);
   fChain->SetBranchAddress("CDF1", &CDF1, &b_CDF1);
   fChain->SetBranchAddress("CDF2", &CDF2, &b_CDF2);
   fChain->SetBranchAddress("CDF3", &CDF3, &b_CDF3);
   fChain->SetBranchAddress("PIDMVA", &PIDMVA, &b_PIDMVA);
   fChain->SetBranchAddress("GeoMVA", &GeoMVA, &b_GeoMVA);
   fChain->SetBranchAddress("BCK", &BCK, &b_BCK);
   Notify();
}

Bool_t flatclass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void flatclass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t flatclass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef flatclass_cxx
