// $Id: $
// Include files 
using namespace RooFit;

void Phi_MassPlot()
{
  TFile* f = new TFile("/data/lhcb/users/contu/PIDFits"
                       "/DataPhi_Plus_v3_MagDown_2_2_0.root");
  
  RooWorkspace* Myws = (RooWorkspace*)f->Get("ws_Kaon_2_2_0_Plus");
  RooRealVar* Lambda_M = Myws->var("Phi_M");
  RooAbsPdf* model = Myws->pdf("model");
  RooPlot* frame = Lambda_M->frame();
  RooDataSet* data = (RooDataSet*) Myws->data("data_P_WithSWeights");
  data->plotOn(frame, Binning(100)) ;
  model->plotOn(frame,LineColor(kBlue));
  double binWidth = Lambda_M->getBinWidth(1);
  frame->GetYaxis()->SetTitle((TString::Format("Candidates / ( %3.1f %s )", 
                                               binWidth,
                                               Lambda_M->getUnit()) ).Data()
                              );
  frame->Draw();
  //lhcb7TeVPaper_L->Draw();
  //frame->GetYaxis()->SetTitleOffset(1.23);
  //frame->GetYaxis()->SetTitleFont(62);
  lhcbName->Draw();

  TPaveText *Title = new TPaveText(0.70 - lhcbStyle->GetPadRightMargin(),
                                   0.71 - lhcbStyle->SetPadTopMargin(0.05),
                                   0.95 - lhcbStyle->GetPadRightMargin(),
                                   0.91 - lhcbStyle->SetPadTopMargin(0.05),
                                   "BRNDC");
  Title->SetFillColor(0);
  Title->SetTextAlign(12);
  Title->SetBorderSize(0);
  Title->SetTextSize(0.07);
  //Title->AddText("#splitline{(c)}{#scale[1.0]{#phi #rightarrow K^{+}K^{-}}}");
  Title->AddText("(c)");
  Title->AddText("#phi #rightarrow K^{+}K^{-}");
  Title->Draw();

  string FileName = "RatiosPaperPlots/Phi_Mass";
  c1->SaveAs((FileName+".eps").c_str());
  //c1->SaveAs((FileName+".png").c_str());
  //c1->SaveAs((FileName+".pdf").c_str());
  
  cout<<"Success"<<endl;
  
}
