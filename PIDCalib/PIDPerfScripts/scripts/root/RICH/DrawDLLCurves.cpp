// $Id: $
// Include files 

void DrawDLLCurves_nTracks()
{
  TFile* f_Scan = new TFile("../make/exe/RichPerf_NTracks.root");
 
  string GraphTitle;
  string PlotTitle;

  GraphTitle = "Kaon_vs_Pion";
  PlotTitle = "title;Kaon ID Efficiency; Pion Mis-ID Efficiency";
  
  TGraph* Kp1_Scan = (TGraph*)f_Scan->Get("KaonSel_DLLScan_0");
  TGraph* Kp2_Scan = (TGraph*)f_Scan->Get("KaonSel_DLLScan_1");
  TGraph* Kp3_Scan = (TGraph*)f_Scan->Get("KaonSel_DLLScan_2");
  TGraph* Kp4_Scan = (TGraph*)f_Scan->Get("KaonSel_DLLScan_3");

  Kp1_Scan->SetLineColor(kOrange+1);
  Kp1_Scan->SetMarkerColor(kOrange+1);
  Kp1_Scan->SetMarkerSize(1.1);
  Kp1_Scan->SetMarkerStyle(20);
  Kp2_Scan->SetLineColor(kRed);
  Kp2_Scan->SetMarkerColor(kRed);
  Kp2_Scan->SetMarkerSize(1.1);
  Kp2_Scan->SetMarkerStyle(21);
  Kp3_Scan->SetLineColor(kBlue);
  Kp3_Scan->SetMarkerColor(kBlue);
  Kp3_Scan->SetMarkerSize(1.1);
  Kp3_Scan->SetMarkerStyle(22);
  Kp4_Scan->SetLineColor(kGreen+1);
  Kp4_Scan->SetMarkerColor(kGreen+1);
  Kp4_Scan->SetMarkerSize(1.1);
  Kp4_Scan->SetMarkerStyle(23);
  
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle(PlotTitle.c_str()); 
  mg->Add(Kp1_Scan);
  mg->Add(Kp2_Scan);
  mg->Add(Kp3_Scan);
  mg->Add(Kp4_Scan);

  leg = new TLegend(0.17,0.52,0.44,0.92);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->SetTextSize(0.04);
  leg->SetHeader("No. Tracks in Event");
  leg->AddEntry(Kp1_Scan,"[0,100]","lp");
  leg->AddEntry(Kp2_Scan,"[100,200]","lp");
  leg->AddEntry(Kp3_Scan,"[200,300]","lp");
  leg->AddEntry(Kp4_Scan,"[300,400]","lp");
  
  TCanvas* myCanvas = new TCanvas("myCanvas", "", 800. 600.);
  gPad->Modified();
  
  mg->Draw("APL");
  lhcb7TeVPaper_BR->Draw();
  leg->Draw();
  
  mg->SetMinimum(0.004);
  mg->SetMaximum(0.6);
  myCanvas->SetLogy(1);

}

void DrawDLLCurves_nPV()
{
  TFile* f_Scan = new TFile("../make/exe/RichPerf_NPV.root");
  
  string GraphTitle;
  string PlotTitle;
  
  GraphTitle = "Kaon_vs_Pion";
  PlotTitle = "title;Kaon ID Efficiency; Pion Mis-ID Efficiency";
  
  TGraph* Kp1_Scan = (TGraph*)f_Scan->Get("KaonSel_DLLScan_0");
  TGraph* Kp2_Scan = (TGraph*)f_Scan->Get("KaonSel_DLLScan_1");
  TGraph* Kp3_Scan = (TGraph*)f_Scan->Get("KaonSel_DLLScan_2");
  TGraph* Kp4_Scan = (TGraph*)f_Scan->Get("KaonSel_DLLScan_3");
  TGraph* Kp5_Scan = (TGraph*)f_Scan->Get("KaonSel_DLLScan_4");

  Kp1_Scan->SetLineColor(kOrange+1);
  Kp1_Scan->SetMarkerColor(kOrange+1);
  Kp1_Scan->SetMarkerSize(1.1);
  Kp1_Scan->SetMarkerStyle(20);
  Kp2_Scan->SetLineColor(kRed);
  Kp2_Scan->SetMarkerColor(kRed);
  Kp2_Scan->SetMarkerSize(1.1);
  Kp2_Scan->SetMarkerStyle(21);
  Kp3_Scan->SetLineColor(kBlue);
  Kp3_Scan->SetMarkerColor(kBlue);
  Kp3_Scan->SetMarkerSize(1.1);
  Kp3_Scan->SetMarkerStyle(22);
  Kp4_Scan->SetLineColor(kGreen+1);
  Kp4_Scan->SetMarkerColor(kGreen+1);
  Kp4_Scan->SetMarkerSize(1.1);
  Kp4_Scan->SetMarkerStyle(23);
  Kp5_Scan->SetLineColor(kViolet+1);
  Kp5_Scan->SetMarkerColor(kViolet+1);
  Kp5_Scan->SetMarkerSize(1.1);
  Kp5_Scan->SetMarkerStyle(29);
  
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle(PlotTitle.c_str()); 
  mg->Add(Kp1_Scan);
  mg->Add(Kp2_Scan);
  mg->Add(Kp3_Scan);
  mg->Add(Kp4_Scan);
  //mg->Add(Kp5_Scan);

  leg = new TLegend(0.17,0.52,0.44,0.92);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->SetTextSize(0.04);
  leg->SetHeader("No. Reco. PVs in Event");
  leg->AddEntry(Kp1_Scan,"1","lp");
  leg->AddEntry(Kp2_Scan,"2","lp");
  leg->AddEntry(Kp3_Scan,"3","lp");
  leg->AddEntry(Kp4_Scan,"4","lp");
  //leg->AddEntry(Kp5_Scan,"5","lp");
  
  TCanvas* myCanvas = new TCanvas("myCanvas", "", 800. 600.);
  gPad->Modified();
  
  mg->Draw("APL");
  lhcb7TeVPaper_BR->Draw();
  leg->Draw();

  mg->SetMinimum(0.005);
  mg->SetMaximum(0.6);
  myCanvas->SetLogy(1);
  
}
