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
  gROOT->ProcessLine(".x lhcbstyle.C");

  TFile* fWgt_Scan = new TFile("$PIDPERFTOOLS/../PIDPerfScripts/"
                               "make/exe/EvtData_PerfCurves_Wgt.root");
  TFile* fRaw_Scan = new TFile("$PIDPERFTOOLS/../PIDPerfScripts/"
                               "make/exe/EvtData_PerfCurves_Raw.root");

  fWgt_Scan->ls();
  fRaw_Scan->ls();
  
  TGraphErrors* Kp1_Scan = (TGraphErrors*)fWgt_Scan->Get("KaonSel_DLLScan");
  TGraphErrors* Kp2_Scan = (TGraphErrors*)fRaw_Scan->Get("KaonSel_DLLScan");
  Kp1_Scan->SetLineColor(kRed);
  Kp1_Scan->SetMarkerColor(kRed);
  Kp2_Scan->SetLineColor(kBlue);
  Kp2_Scan->SetMarkerColor(kBlue);

  
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle("title;Kaon ID Efficiency; Pion Mis-ID Efficiency"); 
  mg->SetMinimum(0.01);
  mg->Add(Kp1_Scan);
  mg->Add(Kp2_Scan);

  leg = new TLegend(0.17,0.58,0.44,0.72);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(Kp1_Scan,"Weighted Cal.","lp");
  leg->AddEntry(Kp2_Scan,"Raw Cal.","lp");
  
  mg->Draw("AL*");
  lhcb7TeVPrelimL->Draw();
  leg->Draw();
  
}

//======================================================================
// Simple function to plot Kaon-MisID vs Pion-ID TGraph
//======================================================================
void PlotPerfCurves_KMisIDvsPiID()
{
  gROOT->ProcessLine(".x lhcbstyle.C");

  TFile* fWgt_Scan = new TFile("$PIDPERFTOOLS/../PIDPerfScripts/"
                               "make/exe/EvtData_PerfCurves_Wgt.root");
  TFile* fRaw_Scan = new TFile("$PIDPERFTOOLS/../PIDPerfScripts/"
                               "make/exe/EvtData_PerfCurves_Raw.root");

  fWgt_Scan->ls();
  fRaw_Scan->ls();
  
  TGraphErrors* Kp1_Scan = (TGraphErrors*)fWgt_Scan->Get("PionSel_DLLScan");
  TGraphErrors* Kp2_Scan = (TGraphErrors*)fRaw_Scan->Get("PionSel_DLLScan");
  Kp1_Scan->SetLineColor(kRed);
  Kp1_Scan->SetMarkerColor(kRed);
  Kp2_Scan->SetLineColor(kBlue);
  Kp2_Scan->SetMarkerColor(kBlue);

  
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
  leg->AddEntry(Kp1_Scan,"Weighted Cal.","lp");
  leg->AddEntry(Kp2_Scan,"Raw Cal.","lp");
  
  mg->Draw("AL*");
  lhcb7TeVPrelimL->Draw();
  leg->Draw();
  
}

