#include <iostream>
#include "TFile.h"
#include "TH2D.h"

TH2D* offbyone(TH2D* e) {
  TH2D* n = (TH2D*)e->Clone("exp");
  n->Reset();
    for (int x = 0 ; x < e->GetNbinsX() ; ++x) {
    for (int y = 0 ; y < e->GetNbinsY() ; ++y) {
      n->SetBinContent(n->GetBin(x+1,y+1),e->GetBinContent(e->GetBin(x,y)));
    }
  }
  n->Draw("box");
  n->SetName(e->GetName());
  return n;
}


TFile* off(TFile* ff) {
  TFile* of = new TFile((TString(ff->GetName())+"fixed.root").Data(),"recreate");
  for (int i = 0 ; i <= ff->GetListOfKeys()->LastIndex() ; ++i) {
    std::cout << "accessing " << i << " which is " << ff->GetListOfKeys()->At(i)->GetName() << std::endl;
    TH2D* out = offbyone((TH2D*)ff->Get(ff->GetListOfKeys()->At(i)->GetName()));
    of->WriteTObject(out);
  }
  of->Close();
  return of;
}
