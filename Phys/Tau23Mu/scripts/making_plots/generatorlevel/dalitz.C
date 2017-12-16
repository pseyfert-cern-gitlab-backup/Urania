#define dalitz_cxx
#include "dalitz.h"
#include <TH2.h>
#include <TNtuple.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "gamma.h"
#include "model.h"

float Number = 1.;
float norm = 1./0.00328524;
float normR = 1./0.000410582;
float normRAD = 1./201.947;
float normRAD_L = 1./2555.49;
float normRAD_R = 1./2555.41;




void dalitz::Loop()
{
  //   In a ROOT session, you can do:
  //      Root > .L dalitz.C
  //      Root > dalitz t
  //      Root > t.GetEntry(12); // Fill t data members with entry number 12
  //      Root > t.Show();       // Show values of entry 12
  //      Root > t.Show(16);     // Read and show values of entry 16
  //      Root > t.Loop();       // Loop on all entries
  //

  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
  TFile* fout = new TFile("output.root","recreate");

  TNtuple* dalitzplot = new TNtuple("dd","Dalitz_Plot","m02:m12:m01:LL:LR");


  Long64_t nbytes = 0, nb = 0;
  model m;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    m.fill(m01,m02,m12);
    dalitzplot->Fill(m02,m12,m01,gammaVLLLL(m01*m01,m02*m02,m12*m12),gammaVLLRR(m01*m01,m02*m02,m12*m12));
  }
  m.print();
  fout->WriteTObject(dalitzplot);
  fout->Close();

}
