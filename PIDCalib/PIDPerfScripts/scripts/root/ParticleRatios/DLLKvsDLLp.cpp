// $Id: $
// Include files

using namespace RooFit;

//-----------------------------------------------------------------------------
// Implementation file for class : DLLKvsDLLp
//
// 2011-10-10 : Andrew Powell (LHCb)04
//-----------------------------------------------------------------------------

void DLLKvsDLLp_Pion()
{
  gStyle->SetOptStat(0);
  
  TFile* f = new TFile("/data/lhcb/users/contu/PIDFits"
                       "/DataKShort_Plus_v3_MagDown_5_2_0.root");
  
  //----------------------------------------------------
  // Get data
  //----------------------------------------------------
  RooWorkspace* Myws = (RooWorkspace*)f->Get("ws_Pion_5_2_0_Plus");
  Myws->Print("v");
  RooRealVar* DLLKPi = Myws->var("Pion_Plus_RICHDLLK");
  RooRealVar* DLLpPi = Myws->var("Pion_Plus_RICHDLLp");
  RooFormulaVar DLLpK("My_DLLpK",
                      "DLL(p - K)", 
                      "@0 - @1",
                      RooArgSet(*DLLpPi,*DLLKPi));
  RooDataSet* data = (RooDataSet*) Myws->data("data_P_WithSWeights");
  data->addColumn(DLLpK);
  RooRealVar* DLLpKVar = (data->get())->find("My_DLLpK");
  
  //----------------------------------------------------
  // Create weighted dataset
  //----------------------------------------------------
  RooDataSet * data_w = new RooDataSet(data->GetName(),
                                       data->GetTitle(),
                                       data,*data->get(),
                                       0,
                                       "peak_yield_sw");
  data_w->Print("v");
  
  RooBinning* DLLpK_Binning = new RooBinning(-100,100,"DLLpK_Binning");
  DLLpK_Binning->addUniform(100,-100,100);
  RooBinning* DLLpPi_Binning = new RooBinning(-100,100,"DLLpPi_Binning");
  DLLpPi_Binning->addUniform(100,-100,100);
  
  TH2* my2D_DLL = data_w->createHistogram("",
                                          *DLLpKVar,
                                          Binning(*DLLpK_Binning),
                                          YVar(*DLLpPi, 
                                               Binning(*DLLpPi_Binning)) );
  
  my2D_DLL->GetZaxis()->SetRangeUser(0.0, my2D_DLL->GetMaximum());
  my2D_DLL->Draw("COLZ");
  my2D_DLL->GetXaxis()->SetTitle("#DeltaLL(p - K)");
  my2D_DLL->GetYaxis()->SetTitle("#DeltaLL(p - #pi)");
  lhcb7TeVPaper_L->Draw();
  PlotBox();
  my2D_DLL->GetYaxis()->SetTitleFont(62);
  c1->SetRightMargin(0.12);
  string FileName = "RatiosPaperPlots/DLLKpiVsDLLPpi_Pions";
  c1->SaveAs((FileName+".eps").c_str());
  //c1->SaveAs((FileName+".png").c_str());
  //c1->SaveAs((FileName+".pdf").c_str());
}


void DLLKvsDLLp_Kaon()
{
  gStyle->SetOptStat(0);
  
  TFile* f = new TFile("/data/lhcb/users/contu/PIDFits"
                       "/DataPhi_Plus_v3_MagDown_5_2_0.root");
  
  //----------------------------------------------------
  // Get data
  //----------------------------------------------------
  RooWorkspace* Myws = (RooWorkspace*)f->Get("ws_Kaon_5_2_0_Plus");
  Myws->Print("v");
  RooRealVar* DLLKPi = Myws->var("Kaon_Plus_RICHDLLK");
  RooRealVar* DLLpPi = Myws->var("Kaon_Plus_RICHDLLp");
  RooFormulaVar DLLpK("My_DLLpK",
                      "DLL(p - K)", 
                      "@0 - @1",
                      RooArgSet(*DLLpPi,*DLLKPi));
  RooDataSet* data = (RooDataSet*) Myws->data("data_P_WithSWeights");
  data->addColumn(DLLpK);
  RooRealVar* DLLpKVar = (data->get())->find("My_DLLpK");
  
  //----------------------------------------------------
  // Create weighted dataset
  //----------------------------------------------------
  RooDataSet * data_w = new RooDataSet(data->GetName(),
                                       data->GetTitle(),
                                       data,*data->get(),
                                       0,
                                       "peak_yield_sw");

  RooBinning* DLLpK_Binning = new RooBinning(-100,100,"DLLpK_Binning");
  DLLpK_Binning->addUniform(100,-100,100);
  RooBinning* DLLpPi_Binning = new RooBinning(-100,100,"DLLpPi_Binning");
  DLLpPi_Binning->addUniform(100,-100,100);
  
  TH2* my2D_DLL = data_w->createHistogram("",
                                          *DLLpKVar,
                                          Binning(*DLLpK_Binning),
                                          YVar(*DLLpPi, 
                                               Binning(*DLLpPi_Binning)) );
  
  my2D_DLL->GetZaxis()->SetRangeUser(0.0, my2D_DLL->GetMaximum());
  my2D_DLL->Draw("COLZ");
  my2D_DLL->GetXaxis()->SetTitle("#DeltaLL(p - K)");
  my2D_DLL->GetYaxis()->SetTitle("#DeltaLL(p - #pi)");
  lhcb7TeVPaper_L->Draw();
  PlotBox();
  my2D_DLL->GetYaxis()->SetTitleFont(62);
  c1->SetRightMargin(0.12);
  string FileName = "RatiosPaperPlots/DLLKpiVsDLLPpi_Kaons";
  c1->SaveAs((FileName+".eps").c_str());
  //c1->SaveAs((FileName+".png").c_str());
  //c1->SaveAs((FileName+".pdf").c_str());
}


void DLLKvsDLLp_Proton()
{
  gStyle->SetOptStat(0);
  
  TFile* f = new TFile("/data/lhcb/users/contu/PIDFits"
                       "/DataLambda_Plus_v3_MagDown_5_2_0.root");
  
  //----------------------------------------------------
  // Get data
  //----------------------------------------------------
  RooWorkspace* Myws = (RooWorkspace*)f->Get("ws_Proton_5_2_0_Plus");
  Myws->Print("v");
  RooRealVar* DLLKPi = Myws->var("Proton_RICHDLLK");
  RooRealVar* DLLpPi = Myws->var("Proton_RICHDLLp");
  RooFormulaVar DLLpK("My_DLLpK",
                      "DLL(p - K)", 
                      "@0 - @1",
                      RooArgSet(*DLLpPi,*DLLKPi));
  RooDataSet* data = (RooDataSet*) Myws->data("data_P_WithSWeights");
  data->addColumn(DLLpK);
  RooRealVar* DLLpKVar = (data->get())->find("My_DLLpK");
  
  //----------------------------------------------------
  // Create weighted dataset
  //----------------------------------------------------
  RooDataSet * data_w = new RooDataSet(data->GetName(),
                                       data->GetTitle(),
                                       data,*data->get(),
                                       0,
                                       "peak_yield_sw");

  RooBinning* DLLpK_Binning = new RooBinning(-100,100,"DLLpK_Binning");
  DLLpK_Binning->addUniform(100,-100,100);
  RooBinning* DLLpPi_Binning = new RooBinning(-100,100,"DLLpPi_Binning");
  DLLpPi_Binning->addUniform(100,-100,100);
  
  TH2* my2D_DLL = data_w->createHistogram("",
                                          *DLLpKVar,
                                          Binning(*DLLpK_Binning),
                                          YVar(*DLLpPi, 
                                               Binning(*DLLpPi_Binning)) );
  
  my2D_DLL->GetZaxis()->SetRangeUser(0.0, my2D_DLL->GetMaximum());
  my2D_DLL->Draw("COLZ");
  my2D_DLL->GetXaxis()->SetTitle("#DeltaLL(p - K)");
  my2D_DLL->GetYaxis()->SetTitle("#DeltaLL(p - #pi)");
  lhcb7TeVPaper_L->Draw();
  PlotBox();
  my2D_DLL->GetYaxis()->SetTitleFont(62);
  c1->SetRightMargin(0.12);
  string FileName = "RatiosPaperPlots/DLLKpiVsDLLPpi_Protons";
  c1->SaveAs((FileName+".eps").c_str());
  //c1->SaveAs((FileName+".png").c_str());
  //c1->SaveAs((FileName+".pdf").c_str());

}


void PlotBox()
{
  TLine* myLine = new TLine(1.86,1.86,1.87,1.87);
  myLine->SetLineColor(1);
  myLine->SetLineWidth(4);
  myLine->SetLineStyle(7);
  myLine->DrawLine(10,14,10,100);
  myLine->DrawLine(10,14,100,14);
  gPad->Modified();
}
