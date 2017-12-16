TH2D* removetrash(TH2D* pdf) {
  limit_interface* li = new limit_interface();
  int newx = (li->GetNPIDbins()-1)*(li->GetNGeobins()-1);
  float mlow = li->GetMasslow(0);
  float mhigh = li->GetMasshigh(li->GetNMassbins()-1);
  TH2D* ret = new TH2D("skimmed","skimmed",newx,0,newx,li->GetNMassbins(),mlow,mhigh);
  int n_geobins_notrash = li->GetNGeobins() - 1;
  for (int g = 1; g < li->GetNGeobins() ; ++g) {
    for (int p = 1; p < li->GetNPIDbins() ; ++p) {
      for (int y = 1 ; y <= pdf->GetNbinsY() ; ++y) {
        float bincont = pdf->GetBinContent(pdf->GetBin(1+li->GetGlobalMVAbin(g,p),y));
        int targetbin = 1 + (g-1) + (p-1)*n_geobins_notrash;
        ret->SetBinContent(ret->GetBin(targetbin,y),bincont);
      }
    }
  }
  ret->SetName(pdf->GetName());
  return ret;
}

void remove(TFile* ff) {
  TFile* of = new TFile((TString(ff->GetName())+"_trash.root").Data(),"recreate");
  for (int i = 0 ; i <= ff->GetListOfKeys()->LastIndex() ; ++i) {
    std::cout << "working on " << ff->GetListOfKeys()->At(i)->GetName() << std::endl;
    TH2D* out = removetrash((TH2D*)ff->Get(ff->GetListOfKeys()->At(i)->GetName()));
    of->WriteTObject(out);
  }
  of->Close();
}

TH2D* removetrash_scaled(TH2D* pdf) {
  limit_interface* li = new limit_interface();
  int newx = (li->GetNPIDbins()-1)*(li->GetNGeobins()-1);
  float mlow = li->GetMasslow(0);
  float mhigh = li->GetMasshigh(li->GetNMassbins()-1);
  TH2D* ret = new TH2D("skimmed","skimmed",newx,0,newx,li->GetNMassbins(),mlow,mhigh);
  int n_geobins_notrash = li->GetNGeobins() - 1;
  //pdf->Scale(1./pdf->GetSum());
  std::cout << "input comes normalised to " << pdf->GetSum() << std::endl;
  double mysum = 0.;
  for (int g = 0; g < li->GetNGeobins() ; ++g) {
    for (int p = 0; p < li->GetNPIDbins() ; ++p) {
      for (int y = 1 ; y <= pdf->GetNbinsY() ; ++y) {
        mysum += (pdf->GetBinContent(pdf->GetBin(1+li->GetGlobalMVAbin(g,p),y)));
      }
    }
  }
  std::cout << "handy check says " << mysum << std::endl;
  for (int g = 1; g < li->GetNGeobins() ; ++g) {
    for (int p = 1; p < li->GetNPIDbins() ; ++p) {
      for (int y = 1 ; y <= pdf->GetNbinsY() ; ++y) {
        double bincont = (pdf->GetBinContent(pdf->GetBin(1+li->GetGlobalMVAbin(g,p),y)));
        bincont = bincont/mysum;
        int targetbin = 1 + (g-1) + (p-1)*n_geobins_notrash;
        ret->SetBinContent(ret->GetBin(targetbin,y),bincont);
      }
    }
  }
  ret->SetName(pdf->GetName());
  std::cout << "normalised to " << ret->GetSum() << std::endl;
  return ret;
}

TFile* remove_scaled(TFile* ff) {
  TFile* of = new TFile((TString(ff->GetName())+"_trash.root").Data(),"recreate");
  for (int i = 0 ; i <= ff->GetListOfKeys()->LastIndex() ; ++i) {
    std::cout << "working on " << ff->GetListOfKeys()->At(i)->GetName() << std::endl;
    TH2D* out = removetrash_scaled((TH2D*)ff->Get(ff->GetListOfKeys()->At(i)->GetName()));
    out->Draw("textbox");
    of->WriteTObject(out);
  }
  return of;
}

