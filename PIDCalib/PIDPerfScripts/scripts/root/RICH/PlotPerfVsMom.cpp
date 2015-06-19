// $Id: $
// Include files

void PlotTwoTGraphAsymmErrors(TGraphAsymmErrors* His1, TGraphAsymmErrors* His2)
{
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(4);
  
  His1->SetLineColor(2);
  His1->SetMarkerColor(2);
  His1->SetMarkerStyle(20);
  His1->SetMarkerSize(0.9);
  
  His2->SetLineColor(1);
  His2->SetMarkerColor(1);
  His2->SetMarkerStyle(20);
  His2->SetMarkerSize(0.9);

  TMultiGraph *mg = new TMultiGraph();
  string XaxisTitle(His1->GetXaxis()->GetTitle());
  string YaxisTitle(His1->GetYaxis()->GetTitle());
  
  string PlotTitle = "title;"+
    XaxisTitle+
    ";"+
    YaxisTitle;
  
  gPad->Modified();
  
  mg->Add(His1);
  mg->Add(His2);
  mg->Draw("AP");  
  mg->SetTitle(PlotTitle.c_str()); 
  mg->SetMaximum(1.4);
  mg->GetXaxis()->SetLimits(0,100000);
  
}

void PlotFourTGraphAsymmErrors(TGraphAsymmErrors* His1, 
                               TGraphAsymmErrors* His2,
                               TGraphAsymmErrors* His3, 
                               TGraphAsymmErrors* His4)
{
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  
  His1->SetLineColor(2);
  His1->SetMarkerColor(2);
  His1->SetMarkerStyle(24);
  His1->SetMarkerSize(0.9);
  
  His2->SetLineColor(1);
  His2->SetMarkerColor(1);
  His2->SetMarkerStyle(25);
  His2->SetMarkerSize(0.9);

  His3->SetLineColor(2);
  His3->SetMarkerColor(2);
  His3->SetMarkerStyle(20);
  His3->SetMarkerSize(0.9);
  
  His4->SetLineColor(1);
  His4->SetMarkerColor(1);
  His4->SetMarkerStyle(21);
  His4->SetMarkerSize(0.9);

  TMultiGraph *mg = new TMultiGraph();
  //string XaxisTitle(His1->GetXaxis()->GetTitle());
  //string YaxisTitle(His1->GetYaxis()->GetTitle());
  string XaxisTitle("Momentum [MeV/c]");
  string YaxisTitle("Efficiency");
  
  string PlotTitle = "title;"+
    XaxisTitle+
    ";"+
    YaxisTitle;
  
  gPad->Modified();
  
  mg->Add(His1);
  mg->Add(His2);
  mg->Add(His3);
  mg->Add(His4);
  mg->Draw("AP");  
  mg->SetTitle(PlotTitle.c_str()); 
  mg->SetMaximum(1.4);
  mg->GetXaxis()->SetLimits(0,100000);
  
}

void PlotFourTH1FwErrors(TH1F* His1, 
                         TH1F* His2,
                         TH1F* His3,
                         TH1F* His4)
{
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(4);
  
  His1->SetLineColor(2);
  His1->SetMarkerColor(2);
  His1->SetMarkerStyle(24);
  His1->SetMarkerSize(0.9);
  His1->GetYaxis()->SetRangeUser(0.0, 1.4);
  His1->SetYTitle("Efficiency");
  His1->SetXTitle("Momentum (MeV/c)");
  //His1->GetYaxis()->SetTitleFont(62);
  His1->Draw("E");
  gPad->Modified();
  His2->SetLineColor(1);
  His2->SetMarkerColor(1);
  His2->SetMarkerStyle(25);
  His2->SetMarkerSize(0.9);
  His2->GetYaxis()->SetRangeUser(0.0, 1.4);
  His2->SetYTitle("Efficiency");
  His2->SetXTitle("Momentum (MeV/c)");
  His2->GetYaxis()->SetTitleFont(62);
  His2->Draw("Esames");
  gPad->Modified();
  His3->SetLineColor(2);
  His3->SetMarkerColor(2);
  His3->SetMarkerStyle(20);
  His3->SetMarkerSize(0.9);
  His3->GetYaxis()->SetRangeUser(0.0, 1.4);
  His3->SetYTitle("Efficiency");
  His3->SetXTitle("Momentum (MeV/c)");
  His3->GetYaxis()->SetTitleFont(62);
  His3->Draw("Esames");
  gPad->Modified();
  His4->SetLineColor(1);
  His4->SetMarkerColor(1);
  His4->SetMarkerStyle(21);
  His4->SetMarkerSize(0.9);
  His4->GetYaxis()->SetRangeUser(0.0, 1.4);
  His4->SetYTitle("Efficiency");
  His4->SetXTitle("Momentum (MeV/c)");
  His4->GetYaxis()->SetTitleFont(62);
  His4->Draw("Esames");
  gPad->Modified();
}

void PPMPlots_KPi_Data_TH1F(const char* runMin, const char* runMax, const char* recoVersion="14", const char* fieldPol="Down")
{
  TFile* f = new TFile(TString::Format("$PIDPERFSCRIPTSROOT/test/Plots/automated/"
                                       "RICHPerf_Reco%s_Mag%s_%s_%s.root", recoVersion, fieldPol, runMin, runMax).Data());
  
  TH1F* Pion_0 = (TH1F*)f->Get("Pi_P_DLLK>0.0_All");
  TH1F* Kaon_0 = (TH1F*)f->Get("K_P_DLLK>0.0_All");
  TH1F* Pion_5 = (TH1F*)f->Get("Pi_P_DLLK>5.0_All");
  TH1F* Kaon_5 = (TH1F*)f->Get("K_P_DLLK>5.0_All");
 
  TCanvas* c_PIDPerf = new TCanvas("Perf Plots","Perf Plots", 810, 600);
  c_PIDPerf->SetRightMargin(0.080);
  c_PIDPerf->cd();

  PlotFourTH1FwErrors(Kaon_0,
                      Pion_0,
                      Kaon_5,
                      Pion_5);

  leg = new TLegend(0.62,0.75,0.89,0.92);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(Pion_0,"#Delta LL(K - #pi) > 0","");
  leg->AddEntry(Pion_5,"#Delta LL(K - #pi) > 5","pe");
  
  TLegend* leg1 = new TLegend(0.55,0.75,0.89,0.92);
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->SetTextSize(0.04);
  leg1->AddEntry(Kaon_0,"","");
  leg1->AddEntry(Kaon_5,"","pe");

  lhcbLatex->SetTextSize(0.04);
  lhcbLatex->DrawLatex(70000, 1.270, "#Delta LL(K - #pi) > 0");
  lhcbLatex->DrawLatex(70000, 1.120, "#Delta LL(K - #pi) > 5");

  lhcbLatex->SetTextSize(0.05);
  lhcbLatex->DrawLatex(25000, 0.75, "#color[2]{K #rightarrow K}");
  lhcbLatex->DrawLatex(25000, 0.20, "#pi #rightarrow K");

  TMarker* Marker_Pion_0 = new TMarker(66000, 1.275, 25);
  Marker_Pion_0->Draw();
  TMarker* Marker_Kaon_0 = new TMarker(58500, 1.275, 24);
  Marker_Kaon_0->SetMarkerColor(2);
  Marker_Kaon_0->Draw();
  TMarker* Marker_Pion_5 = new TMarker(66000, 1.125, 21);
  Marker_Pion_5->Draw();
  TMarker* Marker_Kaon_5 = new TMarker(58500, 1.125, 20);
  Marker_Kaon_5->SetMarkerColor(2);
  Marker_Kaon_5->Draw();

  gPad->RedrawAxis();
  TPaveText *lhcb7TeVPaper_L = new TPaveText(lhcbStyle->GetPadLeftMargin() + 0.05,
                                             0.76 - lhcbStyle->SetPadTopMargin(0.05),
                                             lhcbStyle->GetPadLeftMargin() + 0.30,
                                             0.91 - lhcbStyle->SetPadTopMargin(0.05),
                                             "BRNDC");
  lhcb7TeVPaper_L->SetFillColor(0);
  lhcb7TeVPaper_L->SetTextAlign(12);
  lhcb7TeVPaper_L->SetBorderSize(0);
  //lhcb7TeVPaper_L->SetTextSize(0.07);
  if(strcmp(fieldPol,"Up")==0)
     lhcb7TeVPaper_L->AddText("#splitline{LHCb}{#scale[0.7]{#sqrt{s} = 8 TeV #uparrow Data}}");
  if(strcmp(fieldPol,"Down")==0)
     lhcb7TeVPaper_L->AddText("#splitline{LHCb}{#scale[0.7]{#sqrt{s} = 8 TeV #downarrow Data}}");
  lhcb7TeVPaper_L->Draw();
  
  string FileName = "$PIDPERFSCRIPTSROOT/test/Plots/KPi_Strip15_MagUp_DLL";
  //c_PIDPerf->SaveAs((FileName+".eps").c_str());
  //c_PIDPerf->SaveAs((FileName+".png").c_str());
  //c_PIDPerf->SaveAs((FileName+".pdf").c_str());
  
  cout<<"Success"<<endl;
  
}

void PPMPlots_PPi_Data_TH1F(const char* recoVersion="14", const char* fieldPol="MagDown")
{
  TFile* f = new TFile(TString::Format("$PIDPERFSCRIPTSROOT/test/Plots/"
                                       "RICHPerf_Reco%s_Mag%s.root", recoVersion, fieldPol).Data());
  
  TH1F* Pion_0 = (TH1F*)f->Get("Pi_P_DLLp>0.0_All");
  TH1F* Kaon_0 = (TH1F*)f->Get("P_P_DLLp>0.0_All");
  TH1F* Pion_5 = (TH1F*)f->Get("Pi_P_DLLp>5.0_All");
  TH1F* Kaon_5 = (TH1F*)f->Get("P_P_DLLp>5.0_All");
  
  TCanvas* c_PIDPerf = new TCanvas("Perf Plots","Perf Plots", 810, 600);
  c_PIDPerf->SetRightMargin(0.080);
  c_PIDPerf->cd();

  PlotFourTH1FwErrors(Kaon_0,
                      Pion_0,
                      Kaon_5,
                      Pion_5);

  leg = new TLegend(0.62,0.75,0.89,0.92);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(Pion_0,"#Delta LL(p - #pi) > 0","");
  leg->AddEntry(Pion_5,"#Delta LL(p - #pi) > 5","pe");
  
  TLegend* leg1 = new TLegend(0.55,0.75,0.89,0.92);
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->SetTextSize(0.04);
  leg1->AddEntry(Kaon_0,"","");
  leg1->AddEntry(Kaon_5,"","pe");

  lhcbLatex->SetTextSize(0.04);
  lhcbLatex->DrawLatex(70000, 1.270, "#Delta LL(p - #pi) > 0");
  lhcbLatex->DrawLatex(70000, 1.120, "#Delta LL(p - #pi) > 5");

  lhcbLatex->SetTextSize(0.05);
  lhcbLatex->DrawLatex(25000, 0.75, "#color[2]{p #rightarrow p}");
  lhcbLatex->DrawLatex(25000, 0.20, "#pi #rightarrow p");

  TMarker* Marker_Pion_5 = new TMarker(66000, 1.275, 25);
  Marker_Pion_5->Draw();
  TMarker* Marker_Kaon_5 = new TMarker(58500, 1.275, 24);
  Marker_Kaon_5->SetMarkerColor(2);
  Marker_Kaon_5->Draw();
  TMarker* Marker_Pion_5 = new TMarker(66000, 1.125, 21);
  Marker_Pion_5->Draw();
  TMarker* Marker_Kaon_5 = new TMarker(58500, 1.125, 20);
  Marker_Kaon_5->SetMarkerColor(2);
  Marker_Kaon_5->Draw();

  gPad->RedrawAxis();
  TPaveText *lhcb7TeVPaper_L = new TPaveText(lhcbStyle->GetPadLeftMargin() + 0.05,
                                             0.76 - lhcbStyle->SetPadTopMargin(0.05),
                                             lhcbStyle->GetPadLeftMargin() + 0.30,
                                             0.91 - lhcbStyle->SetPadTopMargin(0.05),
                                             "BRNDC");
  lhcb7TeVPaper_L->SetFillColor(0);
  lhcb7TeVPaper_L->SetTextAlign(12);
  lhcb7TeVPaper_L->SetBorderSize(0);
  //lhcb7TeVPaper_L->SetTextSize(0.07);
  if(strcmp(fieldPol,"Up")==0)
     lhcb7TeVPaper_L->AddText("#splitline{LHCb}{#scale[0.7]{#sqrt{s} = 7 TeV #uparrow Data}}");
  if(strcmp(fieldPol,"Down")==0)
     lhcb7TeVPaper_L->AddText("#splitline{LHCb}{#scale[0.7]{#sqrt{s} = 7 TeV #downarrow Data}}");
  lhcb7TeVPaper_L->Draw();
  
  string FileName = "$PIDPERFSCRIPTSROOT/test/Plots/PPi_Strip17_MagDown_DLL";
  //c_PIDPerf->SaveAs((FileName+".eps").c_str());
  //c_PIDPerf->SaveAs((FileName+".png").c_str());
  //c_PIDPerf->SaveAs((FileName+".pdf").c_str());
  
  cout<<"Success"<<endl;
  
}

void PPMPlots_KPi_MC10_TH1F()
{
  TFile* f = new TFile("../test/MC10_MagUp_Final_Perf_A.root");
  
  TH1F* Pion_0 = (TH1F*)f->Get("Pion_P_0");
  TH1F* Kaon_0 = (TH1F*)f->Get("Kaon_P_0");
  TH1F* Pion_5 = (TH1F*)f->Get("Pion_P_5");
  TH1F* Kaon_5 = (TH1F*)f->Get("Kaon_P_5");
  
  TCanvas* c_PIDPerf = new TCanvas("Perf Plots","Perf Plots", 810, 600);
  c_PIDPerf->SetRightMargin(0.075);
  c_PIDPerf->cd();

  PlotFourTH1FwErrors(Kaon_0,
                      Pion_0,
                      Kaon_5,
                      Pion_5);
  
  TLegend* leg = new TLegend(0.62,0.75,0.89,0.92);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(Pion_0,"#Delta LL(K - #pi) > 0","");
  leg->AddEntry(Pion_5,"#Delta LL(K - #pi) > 5","pe");
  
  TLegend* leg1 = new TLegend(0.55,0.75,0.89,0.92);
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->SetTextSize(0.04);
  leg1->AddEntry(Kaon_0,"","");
  leg1->AddEntry(Kaon_5,"","pe");

  leg1->Draw();
  leg->Draw();

  lhcbLatex->SetTextSize(0.05);
  lhcbLatex->DrawLatex(25000, 0.75, "#color[2]{K #rightarrow K}");
  lhcbLatex->DrawLatex(25000, 0.20, "#pi #rightarrow K");

  TMarker* Marker_Pion_5 = new TMarker(66000, 1.275, 25);
  Marker_Pion_5->Draw();
  TMarker* Marker_Kaon_5 = new TMarker(58500, 1.275, 24);
  Marker_Kaon_5->SetMarkerColor(2);
  Marker_Kaon_5->Draw();
  TMarker* Marker_Pion_5 = new TMarker(66000, 1.125, 21);
  Marker_Pion_5->Draw();
  TMarker* Marker_Kaon_5 = new TMarker(58500, 1.125, 20);
  Marker_Kaon_5->SetMarkerColor(2);
  Marker_Kaon_5->Draw();

  gPad->RedrawAxis();
  lhcb7TeVMCPaper_L->Draw();
  
  string FileName = "FinalRICHPaperPlots/MC10_KPi_Separation_MagUp_Final";
  c_PIDPerf->SaveAs((FileName+".eps").c_str());
  c_PIDPerf->SaveAs((FileName+".png").c_str());
  c_PIDPerf->SaveAs((FileName+".pdf").c_str());
  
  cout<<"Success"<<endl;
  
}

void PPMPlots_KPi_Data()
{
  TFile* f = new TFile("$PIDPERFSCRIPTSROOT/test/KPi_Neg_Separation_MagUp_Bayes_Strip15.root");
  
  TGraphAsymmErrors* Pion_0 = (TGraphAsymmErrors*)f->Get("Pion_P_0");
  TGraphAsymmErrors* Kaon_0 = (TGraphAsymmErrors*)f->Get("Kaon_P_0");
  TGraphAsymmErrors* Pion_5 = (TGraphAsymmErrors*)f->Get("Pion_P_5");
  TGraphAsymmErrors* Kaon_5 = (TGraphAsymmErrors*)f->Get("Kaon_P_5");
  
  TCanvas* c_PIDPerf = new TCanvas("Perf Plots","Perf Plots", 810, 600);
  c_PIDPerf->SetRightMargin(0.075);
  c_PIDPerf->cd();

  PlotFourTGraphAsymmErrors(Kaon_0,
                            Pion_0,
                            Kaon_5,
                            Pion_5);

  lhcb7TeVPrelimL->Draw();
  
  leg = new TLegend(0.62,0.75,0.89,0.92);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(Pion_0,"#Delta LL(K - #pi) > 0","");
  leg->AddEntry(Pion_5,"#Delta LL(K - #pi) > 5","pe");
  
  TLegend* leg1 = new TLegend(0.55,0.75,0.89,0.92);
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->SetTextSize(0.04);
  leg1->AddEntry(Kaon_0,"","");
  leg1->AddEntry(Kaon_5,"","pe");

  leg1->Draw();
  leg->Draw();

  lhcbLatex->SetTextSize(0.05);
  lhcbLatex->DrawLatex(25000, 0.75, "#color[2]{K #rightarrow K}");
  lhcbLatex->DrawLatex(25000, 0.20, "#pi #rightarrow K");

  TMarker* Marker_Pion_5 = new TMarker(65000, 1.275, 25);
  Marker_Pion_5->Draw();
  TMarker* Marker_Kaon_5 = new TMarker(57500, 1.275, 24);
  Marker_Kaon_5->SetMarkerColor(2);
  Marker_Kaon_5->Draw();
  TMarker* Marker_Pion_5 = new TMarker(65000, 1.125, 21);
  Marker_Pion_5->Draw();
  TMarker* Marker_Kaon_5 = new TMarker(57500, 1.125, 20);
  Marker_Kaon_5->SetMarkerColor(2);
  Marker_Kaon_5->Draw();
  
  string FileName = "$PIDPERFSCRIPTSROOT/test/KPi_Separation_MagUp_Neg";
  c_PIDPerf->SaveAs((FileName+".eps").c_str());
  c_PIDPerf->SaveAs((FileName+".png").c_str());
  //c_PIDPerf->SaveAs((FileName+".pdf").c_str());
  
  cout<<"Success"<<endl;
  
}

void PPMPlots_KPi_MC()
{
  TFile* f = new TFile("../MC10_MagUp_Final_Perf.root");
  
  TGraphAsymmErrors* Pion_0 = (TGraphAsymmErrors*)f->Get("Pion_P_0");
  TGraphAsymmErrors* Kaon_0 = (TGraphAsymmErrors*)f->Get("Kaon_P_0");
  TGraphAsymmErrors* Pion_5 = (TGraphAsymmErrors*)f->Get("Pion_P_5");
  TGraphAsymmErrors* Kaon_5 = (TGraphAsymmErrors*)f->Get("Kaon_P_5");
  
  TCanvas* c_PIDPerf = new TCanvas("Perf Plots","Perf Plots", 810, 600);
  c_PIDPerf->SetRightMargin(0.075);
  c_PIDPerf->cd();

  PlotFourTGraphAsymmErrors(Kaon_0,
                            Pion_0,
                            Kaon_5,
                            Pion_5);

  lhcb7TeVMCL->Draw();

  leg = new TLegend(0.62,0.75,0.89,0.92);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(Pion_0,"#Delta LL(K - #pi) > 0","");
  leg->AddEntry(Pion_5,"#Delta LL(K - #pi) > 5","pe");
  
  TLegend* leg1 = new TLegend(0.55,0.75,0.89,0.92);
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->SetTextSize(0.04);
  leg1->AddEntry(Kaon_0,"","");
  leg1->AddEntry(Kaon_5,"","pe");

  leg1->Draw();
  leg->Draw();

  lhcbLatex->SetTextSize(0.05);
  lhcbLatex->DrawLatex(25000, 0.75, "#color[2]{K #rightarrow K}");
  lhcbLatex->DrawLatex(25000, 0.20, "#pi #rightarrow K");

  TMarker* Marker_Pion_5 = new TMarker(65000, 1.275, 25);
  Marker_Pion_5->Draw();
  TMarker* Marker_Kaon_5 = new TMarker(57500, 1.275, 24);
  Marker_Kaon_5->SetMarkerColor(2);
  Marker_Kaon_5->Draw();
  TMarker* Marker_Pion_5 = new TMarker(65000, 1.125, 21);
  Marker_Pion_5->Draw();
  TMarker* Marker_Kaon_5 = new TMarker(57500, 1.125, 20);
  Marker_Kaon_5->SetMarkerColor(2);
  Marker_Kaon_5->Draw();
  
  string FileName = "MC10_KPi_Separation_MagUp";
  c_PIDPerf->SaveAs((FileName+".eps").c_str());
  c_PIDPerf->SaveAs((FileName+".png").c_str());
  c_PIDPerf->SaveAs((FileName+".pdf").c_str());
  
  cout<<"Success"<<endl;
  
}
