/**
* @file BinningPlots.C
* @brief make plots of the signal and background distributions of our multivariates with the current binning superimposed
*
* @author Paul Seyfert
* @date 2012-04-19
*/



/**
* @brief make a plot of the signal and background distribution of the pid MVA (which one it is is specified in the limit interface class)
*
* @param sig a TTree containing the signal
* @param Bbkg a TTree containing the bb background
* @param Cbkg a TTree containing the cc background
*/
void PID_plot(TTree* sig, TTree* Bbkg, TTree* Cbkg) {
  TCanvas* c = new TCanvas();
  sig->SetLineColor(kBlue);
  gSystem->Load("../params/libLimitROOT.so");
  gROOT->ProcessLine(".L fillmassbins.C++O");
  getGeoRefString();
  limit_interface* li = new limit_interface();
  TH1F* sigh = new TH1F("sigh","sigh",100,-1.,1.00000001);
  TH1F* bbkgh = new TH1F("bbkgh","bbkgh",100,-1.,1.00000001);
  TH1F* cbkgh = new TH1F("cbkgh","cbkgh",100,-1.,1.00000001);
  TH1F* bkgh = new TH1F("bkgh","bkgh",100,-1.,1.00000001);

  sigh->SetLineColor(kBlue);
  bkgh->SetLineColor(kRed);
  sig->Draw(li->the_pid()+">>sigh",TString("(")+getGeoRefString(false)+TString(")*productionweight"));
  sigh->Scale(1./sigh->GetSum());
  Bbkg->Draw(li->the_pid()+">>bbkgh",getGeoRefString(false)+"&&BCK!=4&&"+li->the_pid()+">-0.999");
  Cbkg->Draw(li->the_pid()+">>cbkgh",getGeoRefString(false)+"&&BCK!=4&&"+li->the_pid()+">-0.999");
  bkgh->Add(bbkgh,1./9.1);
  bkgh->Add(cbkgh,1./4.4);
  bkgh->Scale(1./bkgh->GetSum());
  sigh->Draw();
  bkgh->Draw("same");
  for (int i = 0 ; i < li->the_pidbins() ; ++i ) {
    TLine* line = new TLine(li->the_pidbinning()[i],0,li->the_pidbinning()[i],0.11);
    line->Draw("same");
  }
  sigh->GetYaxis()->SetRangeUser(0,0.11);
  sigh->GetXaxis()->SetTitle("PidMVA");

}

void GEO_plot(TTree* sig, TTree* Bbkg, TTree* Cbkg) {
  gSystem->Load("../params/libLimitROOT.so");
  sig->SetLineColor(kBlue);
  gROOT->ProcessLine(".L fillmassbins.C+O");
  getGeoRefString();
  limit_interface* li = new limit_interface();
  getGeoRefString();
  TH1F* sigh = new TH1F("sigh","sigh",100,-1.,1.00000001);
  TH1F* bbkgh = new TH1F("bbkgh","bbkgh",100,-1.,1.00000001);
  TH1F* cbkgh = new TH1F("cbkgh","cbkgh",100,-1.,1.00000001);
  TH1F* bkgh = new TH1F("bkgh","bkgh",100,-1.,1.00000001);
  sigh->SetLineColor(kBlue);
  bkgh->SetLineColor(kRed);
  sig->Draw("GeoMVA>>sigh",TString("(")+getGeoRefString(true)+TString(")*productionweight"));
  std::cout << "======= sigh is drawn ====== " << std::endl;
  std::cout << "GeoMVA>>sigh" << "," << TString("(")+getGeoRefString(true)+TString(")*productionweight") << std::endl;
  sigh->Scale(1./sigh->GetSum());
  Bbkg->Draw("GeoMVA>>bbkgh",getGeoRefString(true));
  Cbkg->Draw("GeoMVA>>cbkgh",getGeoRefString(true));
  bkgh->Add(bbkgh,1./9.1);
  bkgh->Add(cbkgh,1./4.4);
  bkgh->Scale(1./bkgh->GetSum());
  sigh->Draw();
  bkgh->Draw("same");
  for (int i = 1 ; i < li->the_geobins() ; ++i ) {
    TLine* line = new TLine(li->the_geobinning()[i],0,li->the_geobinning()[i],0.035);
    line->Draw("same");
  }
  sigh->GetYaxis()->SetRangeUser(0,0.035);
  sigh->GetXaxis()->SetTitle("GeoMVA");
}

