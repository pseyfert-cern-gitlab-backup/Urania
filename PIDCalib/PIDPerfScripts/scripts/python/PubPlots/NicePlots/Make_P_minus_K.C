{

  	gROOT->ProcessLine(".x lhcbstyle.C");  	
  	gROOT->ProcessLine(".L PlotDrawingFunctions.C");
  
  	TFile PasP("PubPlots_P_as_P_minus_K.root");
  	
  	TFile KasP("PubPlots_K_as_P_minus_K.root");
  	
  	TH1F* Kaon_0 = (TH1F*)KasP.Get("K_(DLLp-DLLK) > 0.0_All");
  	TH1F* Kaon_5 = (TH1F*)KasP.Get("K_(DLLp-DLLK) > 5.0_All");
  	
  	TH1F* Proton_0 = (TH1F*)PasP.Get("P_(DLLp-DLLK) > 0.0_All");
  	TH1F* Proton_5 = (TH1F*)PasP.Get("P_(DLLp-DLLK) > 5.0_All");
  	
  	
 	TCanvas *c1 = new TCanvas("c1", "c1",14,35,700,500);
 	c1->SetLeftMargin(0.1393678);
    c1->SetRightMargin(0.07614943);
    c1->SetTopMargin(0.04872881);
    c1->SetBottomMargin(0.161017);

 	PlotFourTH1FwErrors(Proton_0,Kaon_0,Proton_5, Kaon_5);

 	leg = new TLegend(0.62,1.4,0.89,1.6);
 	leg->SetFillColor(0);
  	leg->SetLineColor(0);
  	leg->SetShadowColor(0);
  	leg->SetTextSize(0.04);
   	leg->AddEntry(Kaon_0,"#Delta LL(p - K) > 0","");
    leg->AddEntry(Kaon_5,"#Delta LL(p - K) > 5","pe");
  
  	TLegend* leg1 = new TLegend(0.55,1.4,0.89,1.6);
  	leg1->SetFillColor(0);
  	leg1->SetLineColor(0);
  	leg1->SetShadowColor(0);
  	leg1->SetTextSize(0.04);
  	leg1->AddEntry(Proton_0,"","");
    leg1->AddEntry(Proton_5,"","pe");

  	lhcbLatex->SetTextSize(0.04);
  	lhcbLatex->DrawLatex(70000, 1.270, "#Delta LL(p - K) > 0");
  	lhcbLatex->DrawLatex(70000, 1.120, "#Delta LL(p - K) > 5");

  	lhcbLatex->SetTextSize(0.05);
  	lhcbLatex->DrawLatex(25000, 0.8, "#color[2]{p #rightarrow p}");
  	lhcbLatex->DrawLatex(25000, 0.30, "K #rightarrow p");

  	TMarker* Marker_Kaon_0 = new TMarker(66000, 1.275, 25);
  	Marker_Kaon_0->Draw();
  	TMarker* Marker_Proton_0 = new TMarker(58500, 1.275, 24);
  	Marker_Proton_0->SetMarkerColor(2);
  	Marker_Proton_0->Draw();
	TMarker* Marker_Kaon_5 = new TMarker(66000, 1.125, 21);
  	Marker_Kaon_5->Draw();
  	TMarker* Marker_Proton_5 = new TMarker(58500, 1.125, 20);
  	Marker_Proton_5->SetMarkerColor(2);
  	Marker_Proton_5->Draw();

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
  
  	c1->Print("Plot_2017Validation_PK_P.eps");
  	c1->Print("Plot_2017Validation_PK_P.pdf");

}
