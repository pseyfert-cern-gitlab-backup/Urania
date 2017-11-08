#include <iostream>
#include <stdio.h>

#include "TCanvas.h"
#include "TH2F.h"

void CreateDataHist(){
  TFile *f = new TFile("DsMass_WithSWeighted_Dsst_data_NoCL_CB.root","READ");
  TTree *t = (TTree*) f->Get("DecayTree");
  int entries = t->GetEntries();
  cout << entries << endl;
  Double_t  McorrDsst, sigw, sq;
  Float_t q2Reg;
  TBranch *b_q2Reg, *b_McorrDsst, *b_sigw, *b_sq;
  t->SetBranchAddress("q2Reg", &q2Reg, &b_q2Reg);
  t->SetBranchAddress("McorrDsst", &McorrDsst, &b_McorrDsst);
  t->SetBranchAddress("sigw", &sigw, &b_sigw);
  t->SetBranchAddress("sq", &sq, &b_sq);

  //Double_t bins[6] = { 0., 2000000., 4000000., 6000000., 8000000, 12000000. };
  TH2F *histDataMassQsq = new TH2F("histDataMassQsq","histDataMassQsq",20,3000,5366.82,11,0.,11000000.);
  TString cutTOT = "(sq>0)*sigw";
  TTreeFormula *formula = new TTreeFormula("formula",cutTOT,t);
  for (int i=0; i<=entries;i++){
    t->GetEntry(i);
    if (formula->EvalInstance(0)>0){ 
      histDataMassQsq->Fill(McorrDsst,q2Reg);
    }
  }
  TFile *foutput = new TFile("signal.root","RECREATE");
  histDataMassQsq->Write();
  foutput->Write();
}
