void TemplatesForPrese() {

  TFile *f = new TFile("input/RootOutp_MCAll_IsoNoBMSignal_Bs0DsMu.root","READ");
  f->ls();
  TH2D *dsmu_mqs = (TH2D*)((TH2D*)gDirectory->Get("histoMassQsq"))->Clone("dsmu_mqs");
  TH1D *dsmu_ma = dsmu_mqs->ProjectionX(); 
  TH1D *dsmu_qs = dsmu_mqs->ProjectionY(); 


  TFile *f2 = new TFile("input/RootOutp_MCAll_IsoNoBMSignal_Bs0DstaMu.root","READ");
  f2->ls();
  TH2D *dsstamu_mqs = (TH2D*)((TH2D*)gDirectory->Get("histoMassQsq"))->Clone("dsstamu_mqs");
  TH1D *dsstamu_ma = dsstamu_mqs->ProjectionX(); 
  TH1D *dsstamu_qs = dsstamu_mqs->ProjectionY(); 

  TFile *f3 = new TFile("input/RootOutp_MCAll_IsoNoBMSignal_Bs0Ds0staMu.root","READ");
  f3->ls();
  TH2D *ds0stamu_mqs = (TH2D*)((TH2D*)gDirectory->Get("histoMassQsq"))->Clone("ds0stamu_mqs");
  TH1D *ds0stamu_ma = ds0stamu_mqs->ProjectionX(); 
  TH1D *ds0stamu_qs = ds0stamu_mqs->ProjectionY(); 


  TFile *tf = new TFile("input/RootOutp_MCAll_TauMCLowBinTemDSignal_Bs0DsTau.root","READ");
  tf->ls();
  TH2D *dstau_mqs = (TH2D*)((TH2D*)gDirectory->Get("histoMassQsq"))->Clone("dstau_mqs");
  TH1D *dstau_ma = dstau_mqs->ProjectionX(); 
  TH1D *dstau_qs = dstau_mqs->ProjectionY(); 


  TFile *tf2 = new TFile("input/RootOutp_MCAll_TauMCLowBinTemDSignal_Bs0DstaTau.root","READ");
  tf2->ls();
  TH2D *dsstatau_mqs = (TH2D*)((TH2D*)gDirectory->Get("histoMassQsq"))->Clone("dsstatau_mqs");
  TH1D *dsstatau_ma = dsstatau_mqs->ProjectionX(); 
  TH1D *dsstatau_qs = dsstatau_mqs->ProjectionY(); 

  TFile *tf3 = new TFile("input/RootOutp_MCAll_TauMCLowBinTemDSignal_Bs0Ds0staTau.root","READ");
  tf3->ls();
  TH2D *ds0statau_mqs = (TH2D*)((TH2D*)gDirectory->Get("histoMassQsq"))->Clone("ds0statau_mqs");
  TH1D *ds0statau_ma = ds0statau_mqs->ProjectionX(); 
  TH1D *ds0statau_qs = ds0statau_mqs->ProjectionY(); 


  TGaxis::SetMaxDigits(3);

  TCanvas *c1 = new TCanvas("c1","",900,900);
  c1->cd();
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.12);
  gStyle->SetOptStat(0);
  dsmu_ma->Scale(1./dsmu_ma->GetSumOfWeights());
  dsstamu_ma->Scale(1./dsstamu_ma->GetSumOfWeights());
  ds0stamu_ma->Scale(1./ds0stamu_ma->GetSumOfWeights());
  //  myprobL->Scale(1./myprobL->GetSumOfWeights());
  dsmu_ma->SetTitle("");
  dsmu_ma->SetLineWidth(3);
  dsstamu_ma->SetLineWidth(3);
  ds0stamu_ma->SetLineWidth(3);
  dsmu_ma->SetLineColor(2);
  dsstamu_ma->SetLineColor(6);
  ds0stamu_ma->SetLineColor(kGreen+1);
  dsmu_ma->GetYaxis()->SetTitle("Entries / 167 [MeV]");
  dsmu_ma->GetXaxis()->SetTitle("M(B) corr [MeV]");
  dsmu_ma->GetYaxis()->SetTitleOffset(2);
  dsmu_ma->GetXaxis()->SetTitleOffset(1.2);
  dsmu_ma->Draw();
  dsstamu_ma->Draw("same");
  ds0stamu_ma->Draw("same");


  TLegend* l1 = new TLegend(0.6,0.6,0.82,0.80);
  l1->AddEntry(dsmu_ma,"D_{s} #mu","l");
  l1->AddEntry(dsstamu_ma,"D_{s}* #mu","l");
  l1->AddEntry(ds0stamu_ma,"D_{s0}* #mu","l");

  l1->Draw();

  c1->Print("TemplatesBmass.pdf");


  c1->cd();
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.12);
  gStyle->SetOptStat(0);
  dsmu_qs->Scale(1./dsmu_qs->GetSumOfWeights());
  dsstamu_qs->Scale(1./dsstamu_qs->GetSumOfWeights());
  ds0stamu_qs->Scale(1./ds0stamu_qs->GetSumOfWeights());
  //  myprobL->Scale(1./myprobL->GetSumOfWeights());
  dsmu_qs->SetTitle("");
  dsmu_qs->SetLineWidth(3);
  dsstamu_qs->SetLineWidth(3);
  ds0stamu_qs->SetLineWidth(3);
  dsmu_qs->SetLineColor(2);
  dsstamu_qs->SetLineColor(6);
  ds0stamu_qs->SetLineColor(kGreen+1);
  dsmu_qs->GetYaxis()->SetTitle("Entries / 1.65 10^{6} [MeV]");
  dsmu_qs->GetXaxis()->SetTitle("q^{2} [MeV^{2}/c^{4}]");
  dsmu_qs->GetYaxis()->SetTitleOffset(2);
  dsmu_qs->GetXaxis()->SetTitleOffset(1.2);
  dsmu_qs->SetMaximum(0.2);
  dsmu_qs->Draw();
  dsstamu_qs->Draw("same");
  ds0stamu_qs->Draw("same");


  TLegend* lq1 = new TLegend(0.2,0.6,0.42,0.80);
  lq1->AddEntry(dsmu_qs,"D_{s} #mu","l");
  lq1->AddEntry(dsstamu_qs,"D_{s}* #mu","l");
  lq1->AddEntry(ds0stamu_qs,"D_{s0}* #mu","l");

  lq1->Draw();

  c1->Print("TemplatesQsq.pdf");


  c1->cd();
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.12);
  gStyle->SetOptStat(0);
  dstau_ma->Scale(1./dstau_ma->GetSumOfWeights());
  dsstatau_ma->Scale(1./dsstatau_ma->GetSumOfWeights());
  ds0statau_ma->Scale(1./ds0statau_ma->GetSumOfWeights());
  //  myprobL->Scale(1./myprobL->GetSumOfWeights());
  dstau_ma->SetLineWidth(3);
  dsstatau_ma->SetLineWidth(3);
  ds0statau_ma->SetLineWidth(3);
  dstau_ma->SetMaximum(0.2);
  dstau_ma->SetTitle("");
  dstau_ma->SetLineColor(kBlue+8);
  dsstatau_ma->SetLineColor(kOrange);
  ds0statau_ma->SetLineColor(kGreen+4);
  dstau_ma->GetYaxis()->SetTitle("Entries / 167 [MeV]");
  dstau_ma->GetXaxis()->SetTitle("M(B) corr [MeV]");
  dstau_ma->GetYaxis()->SetTitleOffset(2);
  dstau_ma->GetXaxis()->SetTitleOffset(1.2);
  dstau_ma->Draw();
  dsstatau_ma->Draw("same");
  ds0statau_ma->Draw("same");


  TLegend* lt1 = new TLegend(0.6,0.6,0.82,0.80);
  lt1->AddEntry(dstau_ma,"D_{s} #tau","l");
  lt1->AddEntry(dsstatau_ma,"D_{s}* #tau","l");
  lt1->AddEntry(ds0statau_ma,"D_{s0}* #tau","l");

  lt1->Draw();

  c1->Print("TemplatesBmass_Tau.pdf");

  c1->cd();
  gPad->SetLeftMargin(0.16);
  gPad->SetBottomMargin(0.12);
  gStyle->SetOptStat(0);
  dstau_qs->Scale(1./dstau_qs->GetSumOfWeights());
  dsstatau_qs->Scale(1./dsstatau_qs->GetSumOfWeights());
  ds0statau_qs->Scale(1./ds0statau_qs->GetSumOfWeights());
  //  myprobL->Scale(1./myprobL->GetSumOfWeights());
  dstau_qs->SetLineWidth(3);
  dsstatau_qs->SetLineWidth(3);
  ds0statau_qs->SetLineWidth(3);
  dstau_qs->SetMaximum(0.4);
  dstau_qs->SetTitle("");
  dstau_qs->SetLineColor(kBlue+8);
  dsstatau_qs->SetLineColor(kOrange);
  ds0statau_qs->SetLineColor(kGreen+4);
  dstau_qs->GetYaxis()->SetTitle("Entries / 1.65 10^{6} [MeV]");
  dstau_qs->GetXaxis()->SetTitle("q^{2} [MeV^{2}/c^{4}]");
  dstau_qs->GetYaxis()->SetTitleOffset(2);
  dstau_qs->GetXaxis()->SetTitleOffset(1.2);
  dstau_qs->Draw();
  dsstatau_qs->Draw("same");
  ds0statau_qs->Draw("same");


  TLegend* lt2 = new TLegend(0.2,0.6,0.42,0.80);
  lt2->AddEntry(dstau_qs,"D_{s} #tau","l");
  lt2->AddEntry(dsstatau_qs,"D_{s}* #tau","l");
  lt2->AddEntry(ds0statau_qs,"D_{s0}* #tau","l");

  lt2->Draw();

  c1->Print("TemplatesQsq_Tau.pdf");
  return;

}
