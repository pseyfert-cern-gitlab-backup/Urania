// $Id: $
// Include files 
using namespace RooFit;

void DSt_MassPlot()
{
  TFile* f = new TFile("/data/lhcb/users/powell/gangadir/workspace"
                       "/powell/LocalXML/959/output"
                       "/DSt_KPlus_MagUp_Strip13b.root");
  
  RooWorkspace* Myws = (RooWorkspace*)f->Get("RSDStCalib");
  RooRealVar* D0_M = Myws->var("mass");
  RooRealVar* Delta_M = Myws->var("delm");
  RooAbsPdf* model = Myws->pdf("model");
  RooPlot* frame_D0 = D0_M->frame();
  RooPlot* frame_Delm = Delta_M->frame();
  RooDataSet* data = (RooDataSet*) Myws->data("data");
  
  data->plotOn(frame_D0, Binning(100)) ;
  model->plotOn(frame_D0,LineColor(kBlue));
  frame_D0->Draw();
  lhcb7TeVPaper_L->Draw();
  frame_D0->GetYaxis()->SetTitleOffset(1.23);

  TPaveText *Title_D0 = new TPaveText(0.70 - lhcbStyle->GetPadRightMargin(),
                                      0.755 - lhcbStyle->SetPadTopMargin(0.05),
                                      0.95 - lhcbStyle->GetPadRightMargin(),
                                      0.855 - lhcbStyle->SetPadTopMargin(0.05),
                                      "BRNDC");
  Title_D0->SetFillColor(0);
  Title_D0->SetTextAlign(12);
  Title_D0->SetBorderSize(0);
  Title_D0->SetTextSize(0.07);
  Title_D0->AddText("D^{0} #rightarrow K^{-}#pi^{+}");
  Title_D0->Draw();

  string FileName_D0 = "FinalRICHPaperPlots/D0_Mass";
  c1->SaveAs((FileName_D0+".eps").c_str());
  c1->SaveAs((FileName_D0+".png").c_str());
  c1->SaveAs((FileName_D0+".pdf").c_str());

  TCanvas* c2 = new TCanvas("c2", "", 700, 500);
  c2->cd();
  c2->SetLeftMargin(0.15);
  data->plotOn(frame_Delm, Binning(100)) ;
  model->plotOn(frame_Delm,LineColor(kBlue));
  frame_Delm->Draw();
  lhcb7TeVPaper_L->Draw();
  frame_Delm->GetYaxis()->SetTitleOffset(1.32);
  frame_Delm->GetXaxis()->SetTitle("m_{K#pi#pi_{s}}- m_{K#pi} (MeV/c^{2})");
  
  TPaveText *Title_DSt = new TPaveText(0.70 - lhcbStyle->GetPadRightMargin(),
                                       0.755 - lhcbStyle->SetPadTopMargin(0.05),
                                       0.95 - lhcbStyle->GetPadRightMargin(),
                                       0.855 - lhcbStyle->SetPadTopMargin(0.05),
                                       "BRNDC");
  Title_DSt->SetFillColor(0);
  Title_DSt->SetTextAlign(12);
  Title_DSt->SetBorderSize(0);
  Title_DSt->SetTextSize(0.07);
  Title_DSt->AddText("D^{*+} #rightarrow D^{0}#pi^{+}_{s}");
  Title_DSt->Draw();

  string FileName_Delm = "FinalRICHPaperPlots/DeltaM_Mass";
  c2->SaveAs((FileName_Delm+".eps").c_str());
  c2->SaveAs((FileName_Delm+".png").c_str());
  c2->SaveAs((FileName_Delm+".pdf").c_str());

  cout<<"Success"<<endl;
  
}
