/**
* @file IsoPlot.C
* @brief make plots of variables (originally intended for isolations) showing differences between production channels)
* @author Paul Seyfert
* @date 2012-04-19
*/


TH1F* histvec[8];
TCanvas* c1 = new TCanvas();
TCanvas* c2 = new TCanvas();



/**
* @brief makes a plot for a variable for the main interesting production modes
*
* @param varname the name of the variable after steamrolling
* @param varlow the lower edge of the variable range
* @param varhigh the upper edge of the variable range
*/
void IsoPlot(TString varname = "CDF3",float varlow = 0., float varhigh = 1.00001) {
  gStyle->SetOptStat(0);
  int n_bins = 30;
  TString presel = "L0Dec&&Hlt1Dec&&Hlt2Dec&&cleaningcut&&mass_p0p1>250&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&truetau==15";
  TH2F* twod = new TH2F("twod","twod",n_bins,varlow,varhigh,8,0,8);
  for (int i = 0 ; i < 8 ; ++i) {
    TH1F* iso = new TH1F(Form("CDF3_for_production%d",i),Form("CDF3_for_production%d",i),twod->GetNbinsX(),varlow,varhigh);
    std::cout << presel+Form("&&(production&7)==%d",i) << std::endl;
    Tau23Mu->Draw(varname + Form(">>CDF3_for_production%d",i),presel+Form("&&(production&7)==%d",i));
    if (iso->GetSum() > 0) {
      iso->Scale(1./iso->GetSum());
    } else {
      std::cout << "rubish in production code " << i << std::endl;
    }
    std::cout << "Normalization is " << iso->GetSum() << std::endl;
    for (int j = 1 ; j <= twod->GetNbinsX() ; ++j) {
      twod->SetBinContent(twod->GetBin(j,i+1),iso->GetBinContent(j));
    }
    histvec[i] = iso;
  }
  c1->cd();
  for (int i = 0 ; i < 8 ; ++i) {
    histvec[i]->SetLineColor(i);
    if (0==i) {
      histvec[i]->Draw();
    } else {
      histvec[i]->Draw("same");
    }
  }
  c1->cd();
    histvec[1]->SetLineColor(kBlack);
    histvec[1]->SetTitle("#tau from D_{s}");
    histvec[1]->Draw();
    histvec[4]->SetLineColor(kBlue);
    histvec[4]->SetTitle("#tau directly from B");
    histvec[4]->Draw("same");
    histvec[5]->SetLineColor(kRed);
    histvec[5]->SetTitle("#tau from B#rightarrow D_{s}");
    histvec[5]->Draw("same");
  c1->BuildLegend()->SetFillColor(kWhite);
  c2->cd();
  twod->Draw("colz");
}
