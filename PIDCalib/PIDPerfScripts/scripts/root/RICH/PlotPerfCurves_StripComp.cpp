// $Id: $
// Include files
using namespace RooFit;
using namespace RooStats;

//-----------------------------------------------------------------------------
// Implementation file for class : PlotPerfCurves
//
// 2011-01-18 : Andrew Powell (LHCb)04
//-----------------------------------------------------------------------------

//======================================================================
// Simple function to plot Pion-MisID vs Kaon-ID TGraph
//======================================================================
void PlotPerfCurves_PiMisIDvsKID()
{
  //gROOT->ProcessLine(".x lhcbstyle.C");

  //TFile* f_Strip13 = new TFile("Perf_DLLK_Reco10_MagDown.root");
  TFile* f_Strip15 = new TFile("Perf_DLLK_Reco12_MagDown.root");
  TFile* f_Strip17 = new TFile("Perf_DLLK_Reco12_MagDown_P10GeV.root");

  f_Strip15->ls();
  
  //TGraphErrors* Kp1_Scan = (TGraphErrors*)f_Strip13->Get("KaonSel_Scan");
  TGraphErrors* Kp2_Scan = (TGraphErrors*)f_Strip15->Get("KaonSel_Scan");
  TGraphErrors* Kp3_Scan = (TGraphErrors*)f_Strip17->Get("KaonSel_Scan");
  //Kp1_Scan->SetLineColor(kBlue);
  //Kp1_Scan->SetMarkerColor(kBlue);
  Kp2_Scan->SetLineColor(kRed);
  Kp2_Scan->SetMarkerColor(kRed);
  Kp3_Scan->SetLineColor(kOrange);
  Kp3_Scan->SetMarkerColor(kOrange);
  
  TCanvas* MyCanvas = new TCanvas("MyCanvas","",800,600);

  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("title;Kaon ID Efficiency; Pion Mis-ID Efficiency"); 
  mg->SetMinimum(0.007);
  //mg->Add(Kp1_Scan);
  mg->Add(Kp2_Scan);
  mg->Add(Kp3_Scan);

  leg = new TLegend(0.17,0.58,0.44,0.72);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->SetTextSize(0.04);
  //leg->AddEntry(Kp1_Scan,"Stripping-13b","lp");
  leg->AddEntry(Kp2_Scan,"Stripping-15","lp");
  leg->AddEntry(Kp3_Scan,"Stripping-17","lp");
  
  mg->Draw("AL*");
  (mg->GetXaxis())->SetRangeUser(0.5,1.1);
  lhcb7TeVPrelimL->Draw();
  leg->Draw();
  MyCanvas->SetLogy(1);
}

//======================================================================
// Simple function to plot Pion-MisID vs Kaon-ID TGraph
//======================================================================
void PlotPerfCurves_PiMisIDvsKID_ANNPID()
{
  //gROOT->ProcessLine(".x lhcbstyle.C");

  //TFile* f_ANA_Strip13 = new TFile("Perf_ProbNNK_Reco10_MagDown.root");
  TFile* f_ANA_Strip15 = new TFile("Perf_ProbNNK_Reco11_MagDown.root");
  TFile* f_ANA_Strip17 = new TFile("Perf_ProbNNK_Reco12_MagDown_P10GeV.root");
  //TFile* f_DLL_Strip13 = new TFile("Perf_DLLK_Reco10_MagDown.root");
  TFile* f_DLL_Strip15 = new TFile("Perf_DLLK_Reco11_MagDown.root");
  TFile* f_DLL_Strip17 = new TFile("Perf_DLLK_Reco12_MagDown_P10GeV.root");
 
  f_ANA_Strip15->ls();
  
  //TGraphErrors* Kp_ANA_13_Scan = (TGraphErrors*)f_ANA_Strip13->Get("KaonSel_Scan");
  TGraphErrors* Kp_ANA_15_Scan = (TGraphErrors*)f_ANA_Strip15->Get("KaonSel_Scan");
  TGraphErrors* Kp_ANA_17_Scan = (TGraphErrors*)f_ANA_Strip17->Get("KaonSel_Scan");
  //TGraphErrors* Kp_DLL_13_Scan = (TGraphErrors*)f_DLL_Strip13->Get("KaonSel_Scan");
  TGraphErrors* Kp_DLL_15_Scan = (TGraphErrors*)f_DLL_Strip15->Get("KaonSel_Scan");
  TGraphErrors* Kp_DLL_17_Scan = (TGraphErrors*)f_DLL_Strip17->Get("KaonSel_Scan");
  //Kp_ANA_13_Scan->SetLineColor(kBlue);
  //Kp_ANA_13_Scan->SetMarkerColor(kBlue);
  //Kp_ANA_13_Scan->SetMarkerStyle(21);
  Kp_ANA_15_Scan->SetLineColor(kRed);
  Kp_ANA_15_Scan->SetMarkerColor(kRed);
  Kp_ANA_15_Scan->SetMarkerStyle(21);
  Kp_ANA_17_Scan->SetLineColor(kOrange);
  Kp_ANA_17_Scan->SetMarkerColor(kOrange);
  Kp_ANA_17_Scan->SetMarkerStyle(21);
  //Kp_DLL_13_Scan->SetLineColor(kBlue);
  //Kp_DLL_13_Scan->SetMarkerColor(kBlue);
  //Kp_DLL_13_Scan->SetMarkerStyle(25);
  Kp_DLL_15_Scan->SetLineColor(kRed);
  Kp_DLL_15_Scan->SetMarkerColor(kRed);
  Kp_DLL_15_Scan->SetMarkerStyle(25);
  Kp_DLL_17_Scan->SetLineColor(kOrange);
  Kp_DLL_17_Scan->SetMarkerColor(kOrange);
  Kp_DLL_17_Scan->SetMarkerStyle(25);
  TCanvas* MyCanvas = new TCanvas("MyCanvas","",800,600);

  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("title;Kaon ID Efficiency; Pion Mis-ID Efficiency"); 
  mg->SetMinimum(0.007);
  //mg->Add(Kp_ANA_13_Scan);
  mg->Add(Kp_ANA_15_Scan);
  mg->Add(Kp_ANA_17_Scan);
  //mg->Add(Kp_DLL_13_Scan);
  mg->Add(Kp_DLL_15_Scan);
  mg->Add(Kp_DLL_17_Scan);

  leg = new TLegend(0.17,0.58,0.44,0.72);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->SetTextSize(0.04);
  //leg->AddEntry(Kp_ANA_13_Scan,"Stripping-13b","lp");
  leg->AddEntry(Kp_ANA_15_Scan,"Stripping-15 (NN)","lp");
  leg->AddEntry(Kp_ANA_17_Scan,"Stripping-17 (NN)","lp");
  //leg->AddEntry(Kp_DLL_13_Scan,"Stripping-13b","lp");
  leg->AddEntry(Kp_DLL_15_Scan,"Stripping-15 (DLL)","lp");
  leg->AddEntry(Kp_DLL_17_Scan,"Stripping-17 (DLL)","lp");
  
  mg->Draw("APL");
  (mg->GetXaxis())->SetRangeUser(0.5,1.1);
  lhcb7TeVPrelimL->Draw();
  leg->Draw();
  MyCanvas->SetLogy(1);
}

//======================================================================
// Simple function to plot Kaon-MisID vs Pion-ID TGraph
//======================================================================
void PlotPerfCurves_KMisIDvsPiID()
{
  //gROOT->ProcessLine(".x lhcbstyle.C");

  TFile* f_Strip13 = new TFile("Perf_ProbNNK_MC.root");
  TFile* f_Strip17 = new TFile("Perf_DLLK_MC.root");

  f_Strip13->ls();
  
  TGraphErrors* Kp1_Scan = (TGraphErrors*)f_Strip13->Get("PionSel_Scan");
  TGraphErrors* Kp2_Scan = (TGraphErrors*)f_Strip17->Get("KaonSel_Scan");
  Kp1_Scan->SetLineColor(kRed);
  Kp1_Scan->SetMarkerColor(kRed);
  Kp2_Scan->SetLineColor(kBlue);
  Kp2_Scan->SetMarkerColor(kBlue);

  TCanvas* MyCanvas = new TCanvas("MyCanvas","",800,600);

  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("title;Pion ID Efficiency; Kaon Mis-ID Efficiency"); 
  mg->SetMinimum(0.01);
  mg->Add(Kp1_Scan);
  mg->Add(Kp2_Scan);

  leg = new TLegend(0.17,0.58,0.44,0.72);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(Kp1_Scan,"ProbNNpi","lp");
  leg->AddEntry(Kp2_Scan,"Comb. DLL(K-#pi)","lp");
  
  mg->Draw("AL*");
  (mg->GetXaxis())->SetRangeUser(0.5,1.1);
  lhcb7TeVPrelimL->Draw();
  leg->Draw();
  MyCanvas->SetLogy(1);
}


//======================================================================
// Simple function to plot Pion-MisID vs Kaon-ID TGraph
//======================================================================
void PlotPerfCurves_PiMisIDvsKID_S20_Up(const char* fieldPol="Up")
{
  
  TFile* f_MagUp_0 = new TFile("RICHPerfCurves_Reco14_MagUp_114205_114287.root");
  TFile* f_MagUp_1 = new TFile("RICHPerfCurves_Reco14_MagUp_115518_117103.root");
  TFile* f_MagUp_2 = new TFile("RICHPerfCurves_Reco14_MagUp_118326_123803.root");
  /*
  TFile* f_MagDown_0 = new TFile("RICHPerfCurves_Reco14_MagUp_111761_113146.root");
  TFile* f_MagDown_1 = new TFile("RICHPerfCurves_Reco14_MagUp_114316_115464.root");
  TFile* f_MagDown_2 = new TFile("RICHPerfCurves_Reco14_MagUp_117192_118286.root");
  TFile* f_MagDown_3 = new TFile("RICHPerfCurves_Reco14_MagUp_123910_125115.root");
  */

  TGraphErrors* Kpi_Up_0 = (TGraphErrors*)f_MagUp_0->Get("Graph");
  TGraphErrors* Kpi_Up_1 = (TGraphErrors*)f_MagUp_1->Get("Graph");
  TGraphErrors* Kpi_Up_2 = (TGraphErrors*)f_MagUp_2->Get("Graph");
  Kpi_Up_0->SetLineColor(kBlue);
  Kpi_Up_0->SetMarkerColor(kBlue);
  Kpi_Up_1->SetLineColor(kRed);
  Kpi_Up_1->SetMarkerColor(kRed);
  Kpi_Up_2->SetLineColor(kOrange);
  Kpi_Up_2->SetMarkerColor(kOrange);
  
  TCanvas* MyCanvas = new TCanvas("MyCanvas","",800,600);

  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("title;Kaon ID Efficiency; Pion Mis-ID Efficiency"); 
  mg->SetMinimum(0.007);
  mg->Add(Kpi_Up_0);
  mg->Add(Kpi_Up_1);
  mg->Add(Kpi_Up_2);

  leg = new TLegend(0.17,0.58,0.44,0.72);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->SetTextSize(0.04);
  leg->SetTextFont(132);
  leg->AddEntry(Kpi_Up_0,"Runs : [114205 - 114287]","lp");
  leg->AddEntry(Kpi_Up_1,"Runs : [115518 - 117103]","lp");
  leg->AddEntry(Kpi_Up_2,"Runs : [118326 - 123803]","lp");
  //leg->AddEntry(Kpi_Up_0,"(01-May - 02-May)","lp");
  //leg->AddEntry(Kpi_Up_1,"(16-May - 31-May)","lp");
  //leg->AddEntry(Kpi_Up_2,"(11-Jun - 25-Jun)","lp");
  
  mg->Draw("AL*");
  (mg->GetXaxis())->SetRangeUser(0.5,1.1);
  
  TPaveText *lhcb8TeVPaper_L = new TPaveText(lhcbStyle->GetPadLeftMargin() + 0.05,
                                             0.76 - lhcbStyle->SetPadTopMargin(0.05),
                                             lhcbStyle->GetPadLeftMargin() + 0.30,
                                             0.91 - lhcbStyle->SetPadTopMargin(0.05),
                                             "BRNDC");
  lhcb8TeVPaper_L->SetFillColor(0);
  lhcb8TeVPaper_L->SetTextAlign(12);
  lhcb8TeVPaper_L->SetBorderSize(0);
  if(strcmp(fieldPol,"Up")==0)
     lhcb8TeVPaper_L->AddText("#splitline{LHCb}{#scale[0.7]{#sqrt{s} = 8 TeV #uparrow Data}}");
  else if(strcmp(fieldPol,"Down")==0)
     lhcb8TeVPaper_L->AddText("#splitline{LHCb}{#scale[0.7]{#sqrt{s} = 8 TeV #downarrow Data}}");
  lhcb8TeVPaper_L->Draw();
  
  leg->Draw();
  MyCanvas->SetLogy(1);
}

//======================================================================
// Simple function to plot Pion-MisID vs Kaon-ID TGraph
//======================================================================
void PlotPerfCurves_PiMisIDvsKID_S20_Down(const char* fieldPol="Down")
{
  TFile* f_MagDown_0 = new TFile("RICHPerfCurves_Reco14_MagDown_111761_113146.root");
  TFile* f_MagDown_1 = new TFile("RICHPerfCurves_Reco14_MagDown_114316_115464.root");
  TFile* f_MagDown_2 = new TFile("RICHPerfCurves_Reco14_MagDown_117192_118286.root");
  TFile* f_MagDown_3 = new TFile("RICHPerfCurves_Reco14_MagDown_123910_125115.root");

  TGraphErrors* Kpi_Down_0 = (TGraphErrors*)f_MagDown_0->Get("Graph");
  TGraphErrors* Kpi_Down_1 = (TGraphErrors*)f_MagDown_1->Get("Graph");
  TGraphErrors* Kpi_Down_2 = (TGraphErrors*)f_MagDown_2->Get("Graph");
  TGraphErrors* Kpi_Down_3 = (TGraphErrors*)f_MagDown_3->Get("Graph");
  Kpi_Down_0->SetLineColor(kBlue);
  Kpi_Down_0->SetMarkerColor(kBlue);
  Kpi_Down_1->SetLineColor(kRed);
  Kpi_Down_1->SetMarkerColor(kRed);
  Kpi_Down_2->SetLineColor(kOrange);
  Kpi_Down_2->SetMarkerColor(kOrange);
  Kpi_Down_3->SetLineColor(kViolet);
  Kpi_Down_3->SetMarkerColor(kViolet);
  
  TCanvas* MyCanvas = new TCanvas("MyCanvas","",800,600);

  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("title;Kaon ID Efficiency; Pion Mis-ID Efficiency"); 
  mg->SetMinimum(0.007);
  mg->Add(Kpi_Down_0);
  mg->Add(Kpi_Down_1);
  mg->Add(Kpi_Down_2);
  mg->Add(Kpi_Down_3);

  leg = new TLegend(0.17,0.55,0.44,0.72);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->SetTextSize(0.04);
  leg->SetTextFont(132);
  leg->AddEntry(Kpi_Down_0,"Runs : [111761 - 113146]","lp");
  leg->AddEntry(Kpi_Down_1,"Runs : [114316 - 115464]","lp");
  leg->AddEntry(Kpi_Down_2,"Runs : [117192 - 118286]","lp");
  leg->AddEntry(Kpi_Down_3,"Runs : [123910 - 125115]","lp");
  //leg->AddEntry(Kpi_Down_0,"(08-Apr - 20-Apr)","lp");
  //leg->AddEntry(Kpi_Down_1,"(02-May - 16-May)","lp");
  //leg->AddEntry(Kpi_Down_2,"(01-Jun - 11-Jun)","lp");
  //leg->AddEntry(Kpi_Down_3,"(26-Jul - 10-Aug)","lp");
  
  mg->Draw("AL*");
  (mg->GetXaxis())->SetRangeUser(0.5,1.1);
  
  TPaveText *lhcb8TeVPaper_L = new TPaveText(lhcbStyle->GetPadLeftMargin() + 0.05,
                                             0.76 - lhcbStyle->SetPadTopMargin(0.05),
                                             lhcbStyle->GetPadLeftMargin() + 0.30,
                                             0.91 - lhcbStyle->SetPadTopMargin(0.05),
                                             "BRNDC");
  lhcb8TeVPaper_L->SetFillColor(0);
  lhcb8TeVPaper_L->SetTextAlign(12);
  lhcb8TeVPaper_L->SetBorderSize(0);
  if(strcmp(fieldPol,"Up")==0)
     lhcb8TeVPaper_L->AddText("#splitline{LHCb}{#scale[0.7]{#sqrt{s} = 8 TeV #uparrow Data}}");
  else if(strcmp(fieldPol,"Down")==0)
     lhcb8TeVPaper_L->AddText("#splitline{LHCb}{#scale[0.7]{#sqrt{s} = 8 TeV #downarrow Data}}");
  lhcb8TeVPaper_L->Draw();
  
  leg->Draw();
  MyCanvas->SetLogy(1);
}

//======================================================================
// Simple function to plot Pion-MisID vs Kaon-ID TGraph
//======================================================================
void PlotPerfCurves_PiMisIDvsKID_S17_Up(const char* fieldPol="Up")
{
  
  TFile* f_MagUp_0 = new TFile("RICHPerfCurves_Reco12_MagUp_89933_90207.root");
  TFile* f_MagUp_1 = new TFile("RICHPerfCurves_Reco12_MagUp_93398_97028.root");
  TFile* f_MagUp_2 = new TFile("RICHPerfCurves_Reco12_MagUp_98900_101862.root");
  TFile* f_MagUp_3 = new TFile("RICHPerfCurves_Reco12_MagUp_102499_102907.root");
  TFile* f_MagUp_4 = new TFile("RICHPerfCurves_Reco12_MagUp_103954_104414.root");
  
  TGraphErrors* Kpi_Up_0 = (TGraphErrors*)f_MagUp_0->Get("Graph");
  TGraphErrors* Kpi_Up_1 = (TGraphErrors*)f_MagUp_1->Get("Graph");
  TGraphErrors* Kpi_Up_2 = (TGraphErrors*)f_MagUp_2->Get("Graph");
  TGraphErrors* Kpi_Up_3 = (TGraphErrors*)f_MagUp_3->Get("Graph");
  TGraphErrors* Kpi_Up_4 = (TGraphErrors*)f_MagUp_4->Get("Graph");
  Kpi_Up_0->SetLineColor(kBlue);
  Kpi_Up_0->SetMarkerColor(kBlue);
  Kpi_Up_1->SetLineColor(kRed);
  Kpi_Up_1->SetMarkerColor(kRed);
  Kpi_Up_2->SetLineColor(kOrange);
  Kpi_Up_2->SetMarkerColor(kOrange);
  Kpi_Up_3->SetLineColor(kViolet);
  Kpi_Up_3->SetMarkerColor(kViolet);
  Kpi_Up_4->SetLineColor(kGreen+2);
  Kpi_Up_4->SetMarkerColor(kGreen+2);
  
  TCanvas* MyCanvas = new TCanvas("MyCanvas","",800,600);

  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("title;Kaon ID Efficiency; Pion Mis-ID Efficiency"); 
  mg->SetMinimum(0.007);
  mg->Add(Kpi_Up_0);
  mg->Add(Kpi_Up_1);
  mg->Add(Kpi_Up_2);
  mg->Add(Kpi_Up_3);
  mg->Add(Kpi_Up_4);

  leg = new TLegend(0.17,0.50,0.44,0.72);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->SetTextSize(0.04);
  leg->SetTextFont(132);
  leg->AddEntry(Kpi_Up_0,"Runs : [89333 - 90207] ","lp");
  leg->AddEntry(Kpi_Up_1,"Runs : [93398 - 97028] ","lp");
  leg->AddEntry(Kpi_Up_2,"Runs : [98900 - 101862] ","lp");
  leg->AddEntry(Kpi_Up_3,"Runs : [102499 - 102907] ","lp");
  leg->AddEntry(Kpi_Up_4,"Runs : [103954 - 104414] ","lp");
  //leg->AddEntry(Kpi_Up_0,"(01-May - 02-May)","lp");
  //leg->AddEntry(Kpi_Up_1,"(16-May - 31-May)","lp");
  //leg->AddEntry(Kpi_Up_2,"(11-Jun - 25-Jun)","lp");
  
  mg->Draw("AL*");
  (mg->GetXaxis())->SetRangeUser(0.5,1.1);

  TPaveText *lhcb7TeVPaper_L = new TPaveText(lhcbStyle->GetPadLeftMargin() + 0.05,
                                             0.76 - lhcbStyle->SetPadTopMargin(0.05),
                                             lhcbStyle->GetPadLeftMargin() + 0.30,
                                             0.91 - lhcbStyle->SetPadTopMargin(0.05),
                                             "BRNDC");
  lhcb7TeVPaper_L->SetFillColor(0);
  lhcb7TeVPaper_L->SetTextAlign(12);
  lhcb7TeVPaper_L->SetBorderSize(0);
  if(strcmp(fieldPol,"Up")==0)
     lhcb7TeVPaper_L->AddText("#splitline{LHCb}{#scale[0.7]{#sqrt{s} = 7 TeV #uparrow Data}}");
  if(strcmp(fieldPol,"Down")==0)
     lhcb7TeVPaper_L->AddText("#splitline{LHCb}{#scale[0.7]{#sqrt{s} = 7 TeV #downarrow Data}}");
  lhcb7TeVPaper_L->Draw();
  
  leg->Draw();
  MyCanvas->SetLogy(1);
}

//======================================================================
// Simple function to plot Pion-MisID vs Kaon-ID TGraph
//======================================================================
void PlotPerfCurves_PiMisIDvsKID_S17_Down(const char* fieldPol="Down")
{
  TFile* f_MagDown_0 = new TFile("RICHPerfCurves_Reco12_MagDown_87665_87977.root");
  TFile* f_MagDown_1 = new TFile("RICHPerfCurves_Reco12_MagDown_90256_93282.root");
  TFile* f_MagDown_2 = new TFile("RICHPerfCurves_Reco12_MagDown_97114_98882.root");
  TFile* f_MagDown_3 = new TFile("RICHPerfCurves_Reco12_MagDown_101891_102452.root");
  //TFile* f_MagDown_4 = new TFile("RICHPerfCurves_Reco12_MagDown_103049_103686.root");

  TGraphErrors* Kpi_Down_0 = (TGraphErrors*)f_MagDown_0->Get("Graph");
  TGraphErrors* Kpi_Down_1 = (TGraphErrors*)f_MagDown_1->Get("Graph");
  TGraphErrors* Kpi_Down_2 = (TGraphErrors*)f_MagDown_2->Get("Graph");
  TGraphErrors* Kpi_Down_3 = (TGraphErrors*)f_MagDown_3->Get("Graph");
  //TGraphErrors* Kpi_Down_4 = (TGraphErrors*)f_MagDown_4->Get("Graph");
  Kpi_Down_0->SetLineColor(kBlue);
  Kpi_Down_0->SetMarkerColor(kBlue);
  Kpi_Down_1->SetLineColor(kRed);
  Kpi_Down_1->SetMarkerColor(kRed);
  Kpi_Down_2->SetLineColor(kOrange);
  Kpi_Down_2->SetMarkerColor(kOrange);
  Kpi_Down_3->SetLineColor(kViolet);
  Kpi_Down_3->SetMarkerColor(kViolet);
  //Kpi_Down_4->SetLineColor(kGreen+2);
  //Kpi_Down_4->SetMarkerColor(kGreen+2);
  
  TCanvas* MyCanvas = new TCanvas("MyCanvas","",800,600);

  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("title;Kaon ID Efficiency; Pion Mis-ID Efficiency"); 
  mg->SetMinimum(0.007);
  mg->Add(Kpi_Down_0);
  mg->Add(Kpi_Down_1);
  mg->Add(Kpi_Down_2);
  mg->Add(Kpi_Down_3);
  //mg->Add(Kpi_Down_4);
 
  leg = new TLegend(0.17,0.50,0.44,0.72);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->SetTextSize(0.04);
  leg->SetTextFont(132);
  leg->AddEntry(Kpi_Down_0,"Runs : [87665 - 87977]","lp");
  leg->AddEntry(Kpi_Down_1,"Runs : [90256 - 93282]","lp");
  leg->AddEntry(Kpi_Down_2,"Runs : [97114 - 98882]","lp");
  leg->AddEntry(Kpi_Down_3,"Runs : [101891 - 102452]","lp");
  // leg->AddEntry(Kpi_Down_4,"Runs : [103049 - 103686]","lp");
  //leg->AddEntry(Kpi_Down_0,"(08-Apr - 20-Apr)","lp");
  //leg->AddEntry(Kpi_Down_1,"(02-May - 16-May)","lp");
  //leg->AddEntry(Kpi_Down_2,"(01-Jun - 11-Jun)","lp");
  //leg->AddEntry(Kpi_Down_3,"(26-Jul - 10-Aug)","lp");
  
  mg->Draw("AL*");
  (mg->GetXaxis())->SetRangeUser(0.5,1.1);
  
  TPaveText *lhcb7TeVPaper_L = new TPaveText(lhcbStyle->GetPadLeftMargin() + 0.05,
                                             0.76 - lhcbStyle->SetPadTopMargin(0.05),
                                             lhcbStyle->GetPadLeftMargin() + 0.30,
                                             0.91 - lhcbStyle->SetPadTopMargin(0.05),
                                             "BRNDC");
  lhcb7TeVPaper_L->SetFillColor(0);
  lhcb7TeVPaper_L->SetTextAlign(12);
  lhcb7TeVPaper_L->SetBorderSize(0);
  if(strcmp(fieldPol,"Up")==0)
     lhcb7TeVPaper_L->AddText("#splitline{LHCb}{#scale[0.7]{#sqrt{s} = 7 TeV #uparrow Data}}");
  if(strcmp(fieldPol,"Down")==0)
     lhcb7TeVPaper_L->AddText("#splitline{LHCb}{#scale[0.7]{#sqrt{s} = 7 TeV #downarrow Data}}");
  lhcb7TeVPaper_L->Draw();

  leg->Draw();
  MyCanvas->SetLogy(1);
}
