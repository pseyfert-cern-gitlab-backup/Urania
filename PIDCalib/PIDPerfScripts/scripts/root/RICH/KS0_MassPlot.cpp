// $Id: $
// Include files 
using namespace RooFit;

void KS0_MassPlot()
{
  TFile* f = new TFile("/data/lhcb/users/powell/gangadir/workspace"
                       "/powell/LocalXML/891/output"
                       "/K0S_PionPlus_MagUp_Strip13b.root");
  
  RooWorkspace* Myws = (RooWorkspace*)f->Get("K0SCalib");
  RooRealVar* Lambda_M = Myws->var("mass");
  RooAbsPdf* model = Myws->pdf("model");
  RooPlot* frame = Lambda_M->frame();
  RooDataSet* data = (RooDataSet*) Myws->data("data");
  data->plotOn(frame, Binning(100)) ;
  model->plotOn(frame,LineColor(kBlue));
  frame->Draw();
  lhcb7TeVPaper_L->Draw();
  frame->GetYaxis()->SetTitleOffset(1.23);

  TPaveText *Title = new TPaveText(0.70 - lhcbStyle->GetPadRightMargin(),
                                   0.755 - lhcbStyle->SetPadTopMargin(0.05),
                                   0.95 - lhcbStyle->GetPadRightMargin(),
                                   0.855 - lhcbStyle->SetPadTopMargin(0.05),
                                   "BRNDC");
  Title->SetFillColor(0);
  Title->SetTextAlign(12);
  Title->SetBorderSize(0);
  Title->SetTextSize(0.07);
  Title->AddText("K^{0}_{S} #rightarrow #pi^{+}#pi^{-}");
  Title->Draw();

  string FileName = "FinalRICHPaperPlots/K0S_Mass";
  c1->SaveAs((FileName+".eps").c_str());
  c1->SaveAs((FileName+".png").c_str());
  c1->SaveAs((FileName+".pdf").c_str());
  
  cout<<"Success"<<endl;
  
}
