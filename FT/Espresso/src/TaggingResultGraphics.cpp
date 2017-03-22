#include "TaggingResultGraphics.hh"

#include <cmath>

#include <TGraphAsymmErrors.h>
#include <TAxis.h>
#include <TCanvas.h>

#include "Statistics.hh"

namespace Espresso 
{

  std::shared_ptr<TGraph> graphBinTable(const TaggingResult::BinTable& table, std::string name, std::string title, int sigmaConf) {
    
    double conf = erf(sigmaConf/sqrt(2));

    // Arrays needed
    int numGroups = table.size();
    Double_t* eta = new Double_t[numGroups];
    Double_t* omega = new Double_t[numGroups];
    Double_t* errLo = new Double_t[numGroups];
    Double_t* errHi = new Double_t[numGroups];

    // Compute quantities
    for (int k = 0; k < numGroups; k++) {
      TaggingResult::BinInfo bin = table[k];
      eta[k] = bin.eta;

      // default value when total = 0;
      Double_t eff = 0;
      Double_t low = 0;
      Double_t upper = 0;
      
      // Skip if total number of events is negative
      const Double_t pass = bin.numWrong;
      const Double_t fail = bin.numRight;
      const Double_t total = pass + fail;
      if (total > 0) {
	std::tie(eff,low,upper) = Espresso::EfficiencyConfidenceInterval(pass,fail,conf);
      }

      omega[k] = eff;
      errLo[k] = eff-low;
      errHi[k] = upper-eff;

    }
    
    // Make graph
    std::shared_ptr<TGraph> graph;
    if (sigmaConf == 0)
      graph = std::make_shared<TGraph>(numGroups, eta, omega);
    else
      graph = std::make_shared<TGraphAsymmErrors>(numGroups, eta, omega, nullptr, nullptr, errLo, errHi);
    graph->SetName(name.c_str());
    graph->SetTitle(title.c_str());
    graph->GetXaxis()->SetTitle("#eta");
    graph->GetYaxis()->SetTitle("#omega");
    
    // Clean up
    delete [] eta;
    delete [] omega;
    delete [] errLo;
    delete [] errHi;

    // Retsurn pointer, casting it to std::shared_ptr
    return graph;

  }

  std::shared_ptr<TGraph> graphTauTable(const TaggingResult::TauTable& table, std::string name, std::string title, int sigmaConf) {
    
    // Arrays needed
    int numGroups = table.size();
    Double_t* tau = new Double_t[numGroups];
    Double_t* asymm = new Double_t[numGroups];
    Double_t* errLo = new Double_t[numGroups];
    Double_t* errHi = new Double_t[numGroups];

    // Compute quantities
    for (int k = 0; k < numGroups; k++) {
      TaggingResult::TauInfo bin = table[k];
      tau[k] = bin.tau;
      asymm[k] = bin.asymm;
      errLo[k] = sigmaConf*bin.err;
      errHi[k] = sigmaConf*bin.err;
    }
    
    // Make graph
    std::shared_ptr<TGraph> graph;
    if (sigmaConf == 0)
      graph = std::make_shared<TGraph>(numGroups, tau, asymm);
    else
      graph = std::make_shared<TGraphAsymmErrors>(numGroups, tau, asymm, nullptr, nullptr, errLo, errHi);
    graph->SetName(name.c_str());
    graph->SetTitle(title.c_str());
    graph->GetXaxis()->SetTitle("#tau [ps]");
    graph->GetYaxis()->SetTitle("A");
    
    // Clean up
    delete [] tau;
    delete [] asymm;
    delete [] errLo;
    delete [] errHi;

    // Return pointer, casting it to std::shared_ptr
    return graph;

  }

  std::shared_ptr<TGraph> graphCalibration(const Calibration& cal, std::string name, std::string title, double min, double max,
					   int sigmaConf, int npx) {

    Double_t* eta = new Double_t[npx];
    Double_t* omega = new Double_t[npx];
    Double_t* errLo = new Double_t[npx];
    Double_t* errHi = new Double_t[npx];

    Double_t dx = (max-min)/(npx-1);
    for (Int_t k = 0; k < npx; k++) {
      Double_t x = min + k*dx;
      eta[k] = x;
      if (sigmaConf == 0) {
	Double_t y = cal.Value(x);
	omega[k] = y;
	errLo[k] = 0.0;
	errHi[k] = 0.0;
      } else {
	Double_t y, ylow, yhigh;
	std::tie(y,ylow,yhigh) = cal.ValueRange(x,sigmaConf);
	omega[k] = y;
	errLo[k] = y-ylow;
	errHi[k] = yhigh-y;
      }
    }

    std::shared_ptr<TGraph> graph;
    if (sigmaConf == 0)
      graph = std::make_shared<TGraph>(npx, eta, omega);
    else
      graph = std::make_shared<TGraphAsymmErrors>(npx, eta, omega, nullptr, nullptr, errLo, errHi);

    graph->SetName(name.c_str());
    graph->SetTitle(title.c_str());
    graph->GetXaxis()->SetTitle("#eta");
    graph->GetYaxis()->SetTitle("#omega");

    // Clean up
    delete [] eta;
    delete [] omega;
    delete [] errLo;
    delete [] errHi;

    // Return pointer
    return graph;
  }

  void printGraph(std::shared_ptr<TGraph> graph, bool saveToRoot) {
    TString name = graph->GetName();
    TString title = graph->GetTitle();

    auto c = std::make_shared<TCanvas>(name,title,800,800);
    c->cd(1);

    graph->SetLineColor(kBlack);
    graph->SetMarkerStyle(20);
    graph->Draw("A P");

    TString fname = name + ".png";
    c->SaveAs(fname.Data());
    if (saveToRoot)
      c->Write();
  }

  void printHistogram(std::shared_ptr<TH1F> hist, bool saveToRoot) {
    TString name = hist->GetName();
    TString title = hist->GetTitle();
    
    auto c = std::make_shared<TCanvas>(name,title,800,800);
    c->cd(1);

    hist->SetLineColor(kBlack);
    hist->SetMarkerStyle(20);
    hist->SetLineColor(kBlack);
    hist->SetMarkerStyle(20);
    hist->Draw("E");

    TString fname = name + ".png";
    c->SaveAs(fname.Data());
    if (saveToRoot)
      c->Write();
  }

  void printCurve(std::shared_ptr<TGraph> graph, bool saveToRoot) {
    TString name = graph->GetName();
    TString title = graph->GetTitle();
    
    auto c = std::make_shared<TCanvas>(name,title,800,800);
    c->cd(1);

    graph->SetLineColor(kRed);
    graph->SetLineWidth(4);
    graph->Draw("A L");

    TString fname = name + ".png";
    c->SaveAs(fname.Data());
    if (saveToRoot)
      c->Write();
  }

  void printSmoothedBinTable(const TaggingResult::BinTable& table, std::string name, std::string title, bool saveToRoot) {
    auto c = std::make_shared<TCanvas>(name.c_str(),title.c_str(),800,800);
    c->cd();

    std::string name2 = name + "_d2";
    auto sgraph2 = graphBinTable(table,name2,title,2);
    sgraph2->SetFillColor(7);
    std::string name1 = name + "_d1";
    auto sgraph1 = graphBinTable(table,name1,title,1);
    sgraph1->SetFillColor(kBlue);

    sgraph2->Draw("A P E3");
    sgraph1->Draw("P E3 SAME");

    std::string fname = name + std::string(".png");
    c->SaveAs(fname.c_str());
    if (saveToRoot)
      c->Write();
  }

  void printSmoothedTauTable(const TaggingResult::TauTable& table, std::string name, std::string title, bool saveToRoot) {
    auto c = std::make_shared<TCanvas>(name.c_str(),title.c_str(),800,800);
    c->cd();

    std::string name2 = name + "_d2";
    auto sgraph2 = graphTauTable(table,name2,title,2);
    sgraph2->SetFillColor(7);
    std::string name1 = name + "_d1";
    auto sgraph1 = graphTauTable(table,name1,title,1);
    sgraph1->SetFillColor(kBlue);

    sgraph2->Draw("A P E3");
    sgraph1->Draw("P E3 SAME");

    std::string fname = name + std::string(".png");
    c->SaveAs(fname.c_str());
    if (saveToRoot)
      c->Write();
  }


  void overlayDataAndCalibration(const Calibration& cal, const TaggingResult::BinTable& table,
                                 std::string name, std::string title,
                                 double min, double max, bool saveToRoot) 
  {
    auto c = std::make_shared<TCanvas>(name.c_str(),title.c_str(),800,800);
    c->cd(1);

    std::string name2 = name + std::string("_c2");
    auto graph2 = graphCalibration(cal,name2.c_str(),title.c_str(),min,max,2);
    graph2->SetFillColor(kYellow+1);
    std::string name1 = name + std::string("_c1");
    auto graph1 = graphCalibration(cal,name1.c_str(),title.c_str(),min,max,1);
    graph1->SetFillColor(kGreen+2);
    std::string nameb = name + std::string("_d1");
    auto graph = graphBinTable(table,nameb.c_str(),title.c_str(),1);
    graph->SetLineColor(kBlack);
    graph->SetMarkerStyle(20);

    graph2->Draw("A P E3");
    graph1->Draw("P E3 SAME");
    graph->Draw("PSAME");

    std::string fname = name + std::string(".png");
    c->SaveAs(fname.c_str());
    if (saveToRoot)
      c->Write();
  }
  
  void overlaySmoothedDataAndCalibration(const Calibration& cal, const TaggingResult::BinTable& table,
                                         std::string name, std::string title,
                                         double min, double max, bool saveToRoot) 
  {
    auto c = std::make_shared<TCanvas>(name.c_str(),title.c_str(),800,800);
    c->cd(1);

    std::string sname2 = name + std::string("_d2");
    auto sgraph2 = graphBinTable(table,sname2,title,2);
    sgraph2->SetFillColorAlpha(7,0.40);
    std::string sname1 = name + std::string("_d1");
    auto sgraph1 = graphBinTable(table,sname1,title,1);
    sgraph1->SetFillColorAlpha(kBlue,0.40);
    std::string name2 = name + std::string("_c2");
    auto graph2 = graphCalibration(cal,name2,title,min,max,2);
    graph2->SetFillColorAlpha(kYellow+1,0.40);
    std::string name1 = name + std::string("_c1");
    auto graph1 = graphCalibration(cal,name1,title,min,max,1);
    graph1->SetFillColorAlpha(kGreen+2,0.40);

    sgraph2->Draw("A P E3");
    sgraph1->Draw("P E3 SAME");
    graph2->Draw("P E3 SAME");
    graph1->Draw("P E3 SAME");

    std::string fname = name + std::string(".png");
    c->SaveAs(fname.c_str());
    if (saveToRoot)
      c->Write();
  }
  

  std::shared_ptr<TGraph> graphIntegratedTaggingPower(const TaggingResult& tag, std::string name, std::string title, int npx) {
    std::shared_ptr<TGraph> graph = std::make_shared<TGraph>(npx);
    graph->SetName(name.c_str());
    graph->SetTitle(title.c_str());
    
    tag.sortByEta();
    const TaggingResult::TagTable& table = tag.GetTagTable();
    graph->GetXaxis()->SetTitle("#eta");
    graph->GetYaxis()->SetTitle("tagging power for mistag < #eta");

    if (table.size() == 0)
      return graph;
    
    double min = table[0].omega;
    double max = table[table.size()-1].omega;
    Double_t dx = (max-min)/(npx-1);
    
    double dil2 = 0.0;
    double count = tag.GetNumEvents();
    auto it = table.begin();
    for (int k = 0; k < npx; k++) {
      double x = min + k*dx;
        while (it != table.end() and (*it).omega <= x) {
          double dil = 1-2*(*it).omega;
          dil2 += (*it).W*dil*dil;
          ++it;
        }
        double thispow = dil2 / count;
        graph->SetPoint(k,x,thispow);
    }
      
    return graph;
  }

  std::shared_ptr<TGraph> graphROC(const TaggingResult& tag, std::string name, std::string title, int npx) {

    // get quantiles
    std::vector<double> qs = tag.EtaQuantiles(npx);
    
    // Get four entries of prediction/response table
    std::vector<double> numRightAbove(qs.size(),0.0);
    std::vector<double> numWrongAbove(qs.size(),0.0);
    std::vector<double> numRightBelow(qs.size(),0.0);
    std::vector<double> numWrongBelow(qs.size(),0.0);
    const TaggingResult::TagTable& table = tag.GetTagTable();
    for (const auto& it : table) {
      for (std::size_t k = 0; k < qs.size(); k++) {
	if (it.eta >= qs[k]) {
	  if (it.correct) numRightAbove[k] += it.W;
	  else numWrongAbove[k] += it.W;
	} else {
	  if (it.correct) numRightBelow[k] += it.W;
	  else numWrongBelow[k] += it.W;
	}
      }
    }

    // Create false positive and true positive vectors
    std::vector<double> fpr(qs.size(),0.0);
    std::vector<double> tpr(qs.size(),0.0);
    for (std::size_t k = 0; k < qs.size(); k++) {
      fpr[k] = numWrongBelow[k]/(numWrongBelow[k]+numWrongAbove[k]);
      tpr[k] = numRightBelow[k]/(numRightBelow[k]+numRightAbove[k]);
    }

    // sort?

    std::shared_ptr<TGraph> graph = std::make_shared<TGraph>(npx,&fpr[0],&tpr[0]);
    graph->SetName(name.c_str());
    graph->SetTitle(title.c_str());
    graph->GetXaxis()->SetTitle("FPR (1-specificity)");
    graph->GetYaxis()->SetTitle("TPR (sensitivity)");

    // return
    return graph;
  }

  std::shared_ptr<TH1F> graphEtaDist(const TaggingResult& tag, std::string name, std::string title, int bins, double min, double max) {
    std::shared_ptr<TH1F> eta = std::make_shared<TH1F>(name.c_str(), title.c_str(), bins, min, max);
    for (const auto& it : tag.GetTagTable()) {
      eta->Fill(it.omega,it.W);
    }

    double integral = eta->Integral("width");
    if (integral != 0.0)
      eta->Scale(1.0/integral);
    eta->GetXaxis()->SetTitle("#eta");
    eta->GetYaxis()->SetTitle("pdf(#eta)");

    return eta;
  }

  std::shared_ptr<TH1F> graphEtaDistRight(const TaggingResult& tag, std::string name, std::string title, int bins, double min, double max) {
    std::shared_ptr<TH1F> etaR = std::make_shared<TH1F>(name.c_str(), title.c_str(), bins, min, max);
    for (const auto& it : tag.GetTagTable()) {
      if (it.correct)
        etaR->Fill(it.omega,it.W);
    }
    
    double integral = etaR->Integral("width");
    if (integral != 0.0)
      etaR->Scale(1.0/integral);
    etaR->GetXaxis()->SetTitle("#eta");
    etaR->GetYaxis()->SetTitle("pdf(#eta)");

    return etaR;
  }

  std::shared_ptr<TH1F> graphEtaDistWrong(const TaggingResult& tag, std::string name, std::string title, int bins, double min, double max) {
    std::shared_ptr<TH1F> etaW = std::make_shared<TH1F>(name.c_str(), title.c_str(), bins, min, max);
    for (const auto& it : tag.GetTagTable()) {
      if (not it.correct)
        etaW->Fill(it.omega,it.W);
    }

    double integral = etaW->Integral("width");
    if (integral != 0.0)
      etaW->Scale(1.0/integral);
    etaW->GetXaxis()->SetTitle("#eta");
    etaW->GetYaxis()->SetTitle("pdf(#eta)");

    return etaW;
  }

}
