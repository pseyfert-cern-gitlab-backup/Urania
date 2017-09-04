{

  	gROOT->ProcessLine(".x lhcbstyle.C");  	
  	gROOT->ProcessLine(".L PlotDrawingFunctions.C");
  
  	TFile MuasMu("PubPlots_Mu_as_Mu_Mu_minus_K_Mu_minus_P.root");
  	
  	TFile KasMu("PubPlots_K_as_Mu_minus_K.root");
  	
  	TH1F* Kaon_IsMuon = (TH1F*)KasMu.Get("K_IsMuon_All");
  	TH1F* Kaon_0 = (TH1F*)KasMu.Get("K_IsMuon && (DLLmu-DLLK) > 0.0_All");
  	
  	TH1F* Muon_IsMuon = (TH1F*)MuasMu.Get("Mu_IsMuon_All");
  	TH1F* Muon_0 = (TH1F*)MuasMu.Get("Mu_IsMuon && (DLLmu-DLLK) > 0.0_All");
  	
  	
 	TCanvas *c1 = new TCanvas("c1", "c1",14,35,700,500);
 	c1->SetLeftMargin(0.1393678);
    c1->SetRightMargin(0.07614943);
    c1->SetTopMargin(0.04872881);
    c1->SetBottomMargin(0.161017);

 	PlotFourTH1FwErrors(Muon_IsMuon,Kaon_IsMuon,Muon_0, Kaon_0);

 	leg = new TLegend(0.62,1.4,0.89,1.6);
 	leg->SetFillColor(0);
  	leg->SetLineColor(0);
  	leg->SetShadowColor(0);
  	leg->SetTextSize(0.04);
   	leg->AddEntry(Kaon_IsMuon,"IsMuon","");
    leg->AddEntry(Kaon_0,"IsMuon + #Delta LL(#mu - K) > 0","pe");
  
  	TLegend* leg1 = new TLegend(0.55,1.4,0.89,1.6);
  	leg1->SetFillColor(0);
  	leg1->SetLineColor(0);
  	leg1->SetShadowColor(0);
  	leg1->SetTextSize(0.04);
  	leg1->AddEntry(Muon_IsMuon,"","");
    leg1->AddEntry(Muon_0,"","pe");

  	lhcbLatex->SetTextSize(0.04);
  	lhcbLatex->DrawLatex(70000-15000, 1.270, "IsMuon");
  	lhcbLatex->DrawLatex(70000-15000, 1.120, "IsMuon + #Delta LL(#mu - K) > 0");

  	lhcbLatex->SetTextSize(0.05);
  	lhcbLatex->DrawLatex(25000, 0.8, "#color[2]{#mu #rightarrow #mu}");
  	lhcbLatex->DrawLatex(25000, 0.30, "K #rightarrow #mu");

  	TMarker* Marker_Kaon_IsMuon = new TMarker(66000-15000, 1.275, 25);
  	Marker_Kaon_IsMuon->Draw();
  	TMarker* Marker_Muon_IsMuon = new TMarker(58500-15000, 1.275, 24);
  	Marker_Muon_IsMuon->SetMarkerColor(2);
  	Marker_Muon_IsMuon->Draw();
	TMarker* Marker_Kaon_0 = new TMarker(66000-15000, 1.125, 21);
  	Marker_Kaon_0->Draw();
  	TMarker* Marker_Muon_0 = new TMarker(58500-15000, 1.125, 20);
  	Marker_Muon_0->SetMarkerColor(2);
  	Marker_Muon_0->Draw();

  	gPad->RedrawAxis();
  	
  	double get_left = lhcbStyle->GetPadLeftMargin();
  	
  	TPaveText *lhcb7TeVPaper_L = new TPaveText(get_left + 0.05,
                                             0.76,// - lhcbStyle->SetPadTopMargin(0.05),
                                             get_left + 0.30,
                                             0.91,// - lhcbStyle->SetPadTopMargin(0.05),
                                             "BRNDC");
  	lhcb7TeVPaper_L->SetFillColor(0);
  	lhcb7TeVPaper_L->SetTextAlign(12);
  	lhcb7TeVPaper_L->SetBorderSize(0);
  	lhcb7TeVPaper_L->SetTextSize(0.035);
  	lhcb7TeVPaper_L->AddText("#splitline{LHCb}{#scale[0.9]{#sqrt{s} = 13 TeV 2017 validation}}");  
  	lhcb7TeVPaper_L->Draw();
  
  	c1->Print("Plot_2017Validation_MuK_P.eps");
  	c1->Print("Plot_2017Validation_MuK_P.pdf");

}
