void basem() {
  TH2D* ex;
  TH2D* ep;
  TH2D* em;
  TFile* ff = new TFile("./v3_basem_with450Veto.root","read");
  ff->GetObject("expected",ex);
  ff->GetObject("expected_plus_3sigma",ep);
  ff->GetObject("expected_minus_3sigma",em);
  for (unsigned x = 1 ; x <= ex->GetNbinsX() ; ++x) {
    TFile* fff = new TFile(Form("v3_basem_with450Veto_sys%d.root",x),"recreate");
    TH2D* epc = ex->Clone("expected_plus");
    TH2D* emc = ex->Clone("expected_minus");
    for (unsigned m = 1 ; m <= ex->GetNbinsY() ; ++m) {
      epc->SetBinContent(ep->GetBin(x,m),ep->GetBinContent(ep->GetBin(x,m)));
      emc->SetBinContent(em->GetBin(x,m),em->GetBinContent(em->GetBin(x,m)));
    }
    fff->WriteTObject(epc);
    fff->WriteTObject(emc);
    fff->Close();
    
  }
}
