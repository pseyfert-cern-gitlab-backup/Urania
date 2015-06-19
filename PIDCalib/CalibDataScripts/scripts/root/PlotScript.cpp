// $Id: $
// Include files
//#include "RooNumber.h"

using namespace RooFit;

//===========================================================//
// Function that runs over RooDataSet produced from the 2D 
// DeltaM vs D0M fit and plots the best fit component PDFs in
// these variables, together with a chosen DLL variable 
//==========================================================//
void Plot2DFitResults(const char* PartName = "K",
                      const char* datasetName = "data_wSWeights",
                      const char* JobID = "1077")
{
  lhcbStyle->SetMarkerSize(0.7);

  TFile* f_ws = TFile::Open( (TString::Format("/data/lhcb/users/powell/gangadir/"
                                              "workspace/powell/LocalXML/%s/"
                                              "output/DSt_%sMinus_MagDown_Strip15_0.root",
                                              JobID, PartName)).Data() );
  
  RooWorkspace* ws = (RooWorkspace*)f_ws->Get("RSDStCalib");
  
  RooPlot* frame_D0 = ((RooRealVar*)ws->var("mass"))->frame(1815.0,1915.0);
  RooPlot* frame_DeltaM = ((RooRealVar*)ws->var("delm"))->frame(138.0,153.0);
  RooPlot* frame_PIDK = ((RooRealVar*)ws->var( (TString::Format("%s_CombDLLK",
                                                                PartName) ).Data() ))->frame(-150,150); 
  RooPlot* frame_nTracks = ((RooRealVar*)ws->var("nTracks"))->frame(0,600); 
  RooPlot* frame_ProbNNK = ((RooRealVar*)ws->var( (TString::Format("%s_ProbNNK",
                                                                   PartName) ).Data() ))->frame(0.0,1.0); 
  RooPlot* frame_ProbNNPi = ((RooRealVar*)ws->var( (TString::Format("%s_ProbNNpi",
                                                                    PartName) ).Data() ))->frame(0.0,1.0); 
  
  RooDataSet* data = (RooDataSet*) ws->data(datasetName);
  RooArgSet* row = data->get();
  //row->Print("v");

  RooDataSet* data_w = new RooDataSet(data->GetName(),
                                      data->GetTitle(),
                                      data,
                                      *data->get(),
                                      0,
                                      "nsig_sw");
  RooArgSet* row_w = data_w->get();
  
  RooAbsPdf* model = ws->pdf("model");
  RooAbsPdf* sig = ws->pdf("sig2DModel");
  RooAbsPdf* misID_bkg = ws->pdf("d0Bkg2DModel");
  RooAbsPdf* comb_bkg = ws->pdf("combBkg2DModel");
  RooAbsPdf* rnd_bkg = ws->pdf("piBkg2DModel");
    
  data->plotOn(frame_D0, Name("data"), Binning(80)) ;
  ws->loadSnapshot("fitResults") ;
  
  model->plotOn(frame_D0,Components(*sig), LineColor(kRed));  
  model->plotOn(frame_D0,Components(*misID_bkg), LineColor(kOrange));  
  model->plotOn(frame_D0,Components(*comb_bkg),LineColor(kGreen)); 
  model->plotOn(frame_D0,Components(*rnd_bkg),LineColor(kMagenta+2)); 
  model->plotOn(frame_D0, Name("model"),LineColor(kBlue));
  
  data->plotOn(frame_DeltaM, Name("data"), Binning(80)) ;
  ws->loadSnapshot("fitResults") ;
  model->plotOn(frame_DeltaM,Components(*sig), LineColor(kRed));  
  model->plotOn(frame_DeltaM,Components(*misID_bkg), LineColor(kOrange));  
  model->plotOn(frame_DeltaM,Components(*rnd_bkg),LineColor(kMagenta+2)); 
  model->plotOn(frame_DeltaM,Components(*comb_bkg),LineColor(kGreen)); 
  model->plotOn(frame_DeltaM, Name("model"),LineColor(kBlue));
  
  TCanvas* c = new TCanvas("c1", "", 1200, 600);
  c->Divide(3,2);
  c->cd(1);
  (frame_D0->GetYaxis())->SetTitleOffset(1.20);
  frame_D0->Draw();
  lhcb7TeVPrelimL->Draw();

  c->cd(2);
  (frame_DeltaM->GetYaxis())->SetTitleOffset(1.20);
  frame_DeltaM->Draw();
  lhcb7TeVPrelimR->Draw();

  c->cd(3);
  data_w->plotOn(frame_PIDK, DataError(RooAbsData::SumW2), LineColor(kBlue),  MarkerColor(kBlue), Binning(160)) ;
  frame_PIDK->Draw();
  lhcb7TeVPrelimL->Draw();

  c->cd(4);
  data_w->plotOn(frame_nTracks, DataError(RooAbsData::SumW2), LineColor(kRed),  MarkerColor(kRed), Binning(60)) ;
  frame_nTracks->Draw();
  lhcb7TeVPrelimR->Draw();

  c->cd(5);
  data_w->plotOn(frame_ProbNNK, LineColor(kGreen),  MarkerColor(kGreen), Binning(80)) ;
  frame_ProbNNK->Draw();
  lhcb7TeVPrelimL->Draw();

  c->cd(6);
  data_w->plotOn(frame_ProbNNPi, LineColor(kViolet),  MarkerColor(kViolet), Binning(80)) ;
  frame_ProbNNPi->Draw();
  lhcb7TeVPrelimR->Draw();
}



//===========================================================//
// This function confirms that the separate datasets (i.e. 
// -ve & +ve) can be successfully extracted from the merged
// dataset. The combined DLL(K-pi) distributions are plotted
// for the original un-merged datasets and then the 
// suppossedly equivalent samples from the merged dataset.
//==========================================================//
void PlotMergedKaons()
{
  //TString path_base = "/data/lhcb/users/powell/gangadir/workspace/powell/LocalXML/867/output";
  //TString path_base = "/data/lhcb/users/malde/gangadir/workspace/malde/LocalXML/25/output";
  TString path_base = "/data/lhcbtemp/users/powell/CalibData/tmp";

  TFile* f_Neg = TFile::Open((path_base+"/DSt_KMinus_MagDown_Strip13b_0.root").Data());
  TFile* f_Pos = TFile::Open((path_base+"/DSt_KPlus_MagDown_Strip13b_0.root").Data());
  TFile* f_All = TFile::Open((path_base+"/DSt_K_MagDown_Strip13b_0.root").Data());
  
  RooWorkspace* ws_Neg = (RooWorkspace*)f_Neg->Get("RSDStCalib");
  RooWorkspace* ws_Pos = (RooWorkspace*)f_Pos->Get("RSDStCalib");
  RooWorkspace* ws_All = (RooWorkspace*)f_All->Get("RSDStCalib");
  
  RooPlot* frame_Neg_PIDK = ((RooRealVar*)ws_Neg->var("K_CombDLLK"))->frame(-150,150); 
  RooPlot* frame_Pos_PIDK = frame_Neg_PIDK->Clone();
  RooPlot* frame_Neg_All_PIDK = frame_Neg_PIDK->Clone();
  RooPlot* frame_Pos_All_PIDK = frame_Neg_PIDK->Clone();
 
  RooDataSet* data_Neg = (RooDataSet*) ws_Neg->data("data_wSWeights");
  RooDataSet* data_Pos = (RooDataSet*) ws_Pos->data("data_wSWeights");
  RooDataSet* data_All = (RooDataSet*) ws_All->data("data");
  
  RooDataSet* data_wNeg = new RooDataSet(data_Neg->GetName(),
                                         data_Neg->GetTitle(),
                                         data_Neg,
                                         *data_Neg->get(),
                                         0,
                                         "nsig_sw");

  delete data_Neg;
  
  RooDataSet* data_wPos = new RooDataSet(data_Pos->GetName(),
                                         data_Pos->GetTitle(),
                                         data_Pos,
                                         *data_Pos->get(),
                                         0,
                                         "nsig_sw");
  
  delete data_Pos;

  RooDataSet* data_wPos_All = new RooDataSet(data_All->GetName(),
                                             data_All->GetTitle(),
                                             data_All,
                                             *data_All->get(),
                                             "Charge==Charge::Positive",
                                             "nsig_sw");
  
  RooDataSet* data_wNeg_All = new RooDataSet(data_All->GetName(),
                                             data_All->GetTitle(),
                                             data_All,
                                             *data_All->get(),
                                             "Charge==Charge::Negative",
                                             "nsig_sw");
  delete data_All;

  RooArgSet* row_wNeg = data_wNeg->get();
  row_wNeg->Print("v");
  RooArgSet* row_wNeg_All = data_wNeg_All->get();
  row_wNeg_All->Print("v");

  RooArgSet* row_wPos = data_wPos->get();
  row_wPos->Print("v");
  RooArgSet* row_wPos_All = data_wPos_All->get();
  row_wPos_All->Print("v");

  TCanvas* c = new TCanvas("c", "", 800, 600);
  c->Divide(2,2);
  c->cd(1);
  data_wNeg->plotOn(frame_Neg_PIDK, DataError(RooAbsData::SumW2), LineColor(kBlue),  MarkerColor(kBlue), Binning(160)) ;
  data_wNeg->statOn(frame_Neg_PIDK, What("N"));
  frame_Neg_PIDK->Draw();
  lhcb7TeVPrelimL->Draw();
  c->cd(2);
  data_wPos->plotOn(frame_Pos_PIDK, DataError(RooAbsData::SumW2), LineColor(kBlue),  MarkerColor(kBlue), Binning(160)) ;
  data_wPos->statOn(frame_Pos_PIDK, What("N"));
  frame_Pos_PIDK->Draw();
  lhcb7TeVPrelimL->Draw();
  c->cd(3);
  data_wNeg_All->plotOn(frame_Neg_All_PIDK, DataError(RooAbsData::SumW2), LineColor(kBlue),  MarkerColor(kBlue), Binning(160)) ;
  data_wNeg_All->statOn(frame_Neg_All_PIDK, What("N"));
  frame_Neg_All_PIDK->Draw();
  lhcb7TeVPrelimL->Draw();
  c->cd(4);
  data_wPos_All->plotOn(frame_Pos_All_PIDK, DataError(RooAbsData::SumW2), LineColor(kBlue),  MarkerColor(kBlue), Binning(160)) ;
  data_wPos_All->statOn(frame_Pos_All_PIDK, What("N"));
  frame_Pos_All_PIDK->Draw();
  lhcb7TeVPrelimL->Draw();
  
}


//===========================================================//
// This function confirms that the separate datasets (i.e. 
// -ve & +ve) can be successfully extracted from the merged
// dataset. The combined DLL(K-pi) distributions are plotted
// for the original un-merged datasets and then the 
// suppossedly equivalent samples from the merged dataset.
//==========================================================//
void PlotMergedPions()
{
  //TString path_base = "/data/lhcb/users/powell/gangadir/workspace/powell/LocalXML/867/output";
  //TString path_base = "/data/lhcb/users/malde/gangadir/workspace/malde/LocalXML/25/output";
  TString path_base = "/data/lhcbtemp/users/powell/CalibData/tmp";

  TFile* f_Neg = TFile::Open((path_base+"/DSt_PiMinus_MagDown_Strip13b_0.root").Data());
  TFile* f_Pos = TFile::Open((path_base+"/DSt_PiPlus_MagDown_Strip13b_0.root").Data());
  TFile* f_All = TFile::Open((path_base+"/DSt_Pi_MagDown_Strip13b_0.root").Data());
  
  RooWorkspace* ws_Neg = (RooWorkspace*)f_Neg->Get("RSDStCalib");
  RooWorkspace* ws_Pos = (RooWorkspace*)f_Pos->Get("RSDStCalib");
  RooWorkspace* ws_All = (RooWorkspace*)f_All->Get("RSDStCalib");
  
  RooPlot* frame_Neg_PIDK = ((RooRealVar*)ws_Neg->var("Pi_CombDLLK"))->frame(-150,150); 
  RooPlot* frame_Pos_PIDK = frame_Neg_PIDK->Clone();
  RooPlot* frame_Neg_All_PIDK = frame_Neg_PIDK->Clone();
  RooPlot* frame_Pos_All_PIDK = frame_Neg_PIDK->Clone();
 
  RooDataSet* data_Neg = (RooDataSet*) ws_Neg->data("data_wSWeights");
  RooDataSet* data_Pos = (RooDataSet*) ws_Pos->data("data_wSWeights");
  RooDataSet* data_All = (RooDataSet*) ws_All->data("data");
  
  RooDataSet* data_wNeg = new RooDataSet(data_Neg->GetName(),
                                         data_Neg->GetTitle(),
                                         data_Neg,
                                         *data_Neg->get(),
                                         0,
                                         "nsig_sw");

  delete data_Neg;
  
  RooDataSet* data_wPos = new RooDataSet(data_Pos->GetName(),
                                         data_Pos->GetTitle(),
                                         data_Pos,
                                         *data_Pos->get(),
                                         0,
                                         "nsig_sw");
  
  delete data_Pos;

  RooDataSet* data_wPos_All = new RooDataSet(data_All->GetName(),
                                             data_All->GetTitle(),
                                             data_All,
                                             *data_All->get(),
                                             "Charge==Charge::Positive",
                                             "nsig_sw");
  
  RooDataSet* data_wNeg_All = new RooDataSet(data_All->GetName(),
                                             data_All->GetTitle(),
                                             data_All,
                                             *data_All->get(),
                                             "Charge==Charge::Negative",
                                             "nsig_sw");
  delete data_All;

  RooArgSet* row_wNeg = data_wNeg->get();
  row_wNeg->Print("v");
  RooArgSet* row_wNeg_All = data_wNeg_All->get();
  row_wNeg_All->Print("v");

  RooArgSet* row_wPos = data_wPos->get();
  row_wPos->Print("v");
  RooArgSet* row_wPos_All = data_wPos_All->get();
  row_wPos_All->Print("v");

  TCanvas* c = new TCanvas("c", "", 800, 600);
  c->Divide(2,2);
  c->cd(1);
  data_wNeg->plotOn(frame_Neg_PIDK, DataError(RooAbsData::SumW2), LineColor(kBlue),  MarkerColor(kBlue), Binning(160)) ;
  data_wNeg->statOn(frame_Neg_PIDK, What("N"));
  frame_Neg_PIDK->Draw();
  lhcb7TeVPrelimL->Draw();
  c->cd(2);
  data_wPos->plotOn(frame_Pos_PIDK, DataError(RooAbsData::SumW2), LineColor(kBlue),  MarkerColor(kBlue), Binning(160)) ;
  data_wPos->statOn(frame_Pos_PIDK, What("N"));
  frame_Pos_PIDK->Draw();
  lhcb7TeVPrelimL->Draw();
  c->cd(3);
  data_wNeg_All->plotOn(frame_Neg_All_PIDK, DataError(RooAbsData::SumW2), LineColor(kBlue),  MarkerColor(kBlue), Binning(160)) ;
  data_wNeg_All->statOn(frame_Neg_All_PIDK, What("N"));
  frame_Neg_All_PIDK->Draw();
  lhcb7TeVPrelimL->Draw();
  c->cd(4);
  data_wPos_All->plotOn(frame_Pos_All_PIDK, DataError(RooAbsData::SumW2), LineColor(kBlue),  MarkerColor(kBlue), Binning(160)) ;
  data_wPos_All->statOn(frame_Pos_All_PIDK, What("N"));
  frame_Pos_All_PIDK->Draw();
  lhcb7TeVPrelimL->Draw();
  
}


//===========================================================//
// This function confirms that the separate datasets (i.e. 
// -ve & +ve) can be successfully extracted from the merged
// dataset. The combined DLL(K-pi) distributions are plotted
// for the original un-merged datasets and then the 
// suppossedly equivalent samples from the merged dataset.
//==========================================================//
void PlotMergedProtons()
{
  //TString path_base = "/data/lhcb/users/powell/gangadir/workspace/powell/LocalXML/867/output";
  //TString path_base = "/data/lhcb/users/malde/gangadir/workspace/malde/LocalXML/25/output";
  TString path_base = "/data/lhcbtemp/users/powell/CalibData/tmp";

  TFile* f_Neg = TFile::Open((path_base+"/Lam0_PMinus_MagDown_Strip13b_0.root").Data());
  TFile* f_Pos = TFile::Open((path_base+"/Lam0_PPlus_MagDown_Strip13b_0.root").Data());
  TFile* f_All = TFile::Open((path_base+"/Lam0_P_MagDown_Strip13b_0.root").Data());
  
  RooWorkspace* ws_Neg = (RooWorkspace*)f_Neg->Get("Lam0Calib");
  RooWorkspace* ws_Pos = (RooWorkspace*)f_Pos->Get("Lam0Calib");
  RooWorkspace* ws_All = (RooWorkspace*)f_All->Get("Lam0Calib");
  
  RooPlot* frame_Neg_PIDK = ((RooRealVar*)ws_Neg->var("P_CombDLLp"))->frame(-150,150); 
  RooPlot* frame_Pos_PIDK = frame_Neg_PIDK->Clone();
  RooPlot* frame_Neg_All_PIDK = frame_Neg_PIDK->Clone();
  RooPlot* frame_Pos_All_PIDK = frame_Neg_PIDK->Clone();
 
  RooDataSet* data_Neg = (RooDataSet*) ws_Neg->data("data_wSWeights");
  RooDataSet* data_Pos = (RooDataSet*) ws_Pos->data("data_wSWeights");
  RooDataSet* data_All = (RooDataSet*) ws_All->data("data");
  
  RooDataSet* data_wNeg = new RooDataSet(data_Neg->GetName(),
                                         data_Neg->GetTitle(),
                                         data_Neg,
                                         *data_Neg->get(),
                                         0,
                                         "nsig_sw");

  delete data_Neg;
  
  RooDataSet* data_wPos = new RooDataSet(data_Pos->GetName(),
                                         data_Pos->GetTitle(),
                                         data_Pos,
                                         *data_Pos->get(),
                                         0,
                                         "nsig_sw");
  
  delete data_Pos;

  RooDataSet* data_wPos_All = new RooDataSet(data_All->GetName(),
                                             data_All->GetTitle(),
                                             data_All,
                                             *data_All->get(),
                                             "Charge==Charge::Positive",
                                             "nsig_sw");
  
  RooDataSet* data_wNeg_All = new RooDataSet(data_All->GetName(),
                                             data_All->GetTitle(),
                                             data_All,
                                             *data_All->get(),
                                             "Charge==Charge::Negative",
                                             "nsig_sw");
  delete data_All;

  RooArgSet* row_wNeg = data_wNeg->get();
  row_wNeg->Print("v");
  RooArgSet* row_wNeg_All = data_wNeg_All->get();
  row_wNeg_All->Print("v");

  RooArgSet* row_wPos = data_wPos->get();
  row_wPos->Print("v");
  RooArgSet* row_wPos_All = data_wPos_All->get();
  row_wPos_All->Print("v");

  TCanvas* c = new TCanvas("c", "", 800, 600);
  c->Divide(2,2);
  c->cd(1);
  data_wNeg->plotOn(frame_Neg_PIDK, DataError(RooAbsData::SumW2), LineColor(kBlue),  MarkerColor(kBlue), Binning(160)) ;
  data_wNeg->statOn(frame_Neg_PIDK, What("N"));
  frame_Neg_PIDK->Draw();
  lhcb7TeVPrelimL->Draw();
  c->cd(2);
  data_wPos->plotOn(frame_Pos_PIDK, DataError(RooAbsData::SumW2), LineColor(kBlue),  MarkerColor(kBlue), Binning(160)) ;
  data_wPos->statOn(frame_Pos_PIDK, What("N"));
  frame_Pos_PIDK->Draw();
  lhcb7TeVPrelimL->Draw();
  c->cd(3);
  data_wNeg_All->plotOn(frame_Neg_All_PIDK, DataError(RooAbsData::SumW2), LineColor(kBlue),  MarkerColor(kBlue), Binning(160)) ;
  data_wNeg_All->statOn(frame_Neg_All_PIDK, What("N"));
  frame_Neg_All_PIDK->Draw();
  lhcb7TeVPrelimL->Draw();
  c->cd(4);
  data_wPos_All->plotOn(frame_Pos_All_PIDK, DataError(RooAbsData::SumW2), LineColor(kBlue),  MarkerColor(kBlue), Binning(160)) ;
  data_wPos_All->statOn(frame_Pos_All_PIDK, What("N"));
  frame_Pos_All_PIDK->Draw();
  lhcb7TeVPrelimL->Draw();
  
}


//===========================================================//
// Function that runs over RooDataSet produced from the 2D 
// DeltaM vs D0M fit and plots the best fit component PDFs in
// these variables, together with a chosen DLL variable 
//==========================================================//
void Plot1DFitResults(const char* DLLName1 = "P_CombDLLK",
                      const char* DLLName2 = "P_CombDLLp",
                      const char* datasetName = "data_wSWeights",
                      const char* file = "../ProtonPlus_Strip13bMagDown.root")
{
  TFile* f_ws = TFile::Open(file);
  
  RooWorkspace* ws = (RooWorkspace*)f_ws->Get("Lam0Calib");
  ws->Print("v");
  
  RooPlot* frame_D0 = ((RooRealVar*)ws->var("mass"))->frame(1101,1130);
  RooPlot* frame_PID1 = ((RooRealVar*)ws->var(DLLName1))->frame(-150,150); 
  RooPlot* frame_PID2 = ((RooRealVar*)ws->var(DLLName2))->frame(-150,150); 
  RooPlot* frame_nTracks = ((RooRealVar*)ws->var("nTracks"))->frame(0,600); 
  
  RooDataSet* data = (RooDataSet*) ws->data(datasetName);
  RooArgSet* row = data->get();
  //row->Print("v");

  RooDataSet* data_w = new RooDataSet(data->GetName(),
                                      data->GetTitle(),
                                      data,
                                      *data->get(),
                                      0,
                                      "nsig_sw");
  
  RooArgSet* row_w = data_w->get();
  
  RooAbsPdf* model = ws->pdf("model");
  RooAbsPdf* sig = ws->pdf("sigModel");
  RooAbsPdf* comb_bkg = ws->pdf("bkgModel");
    
  data->plotOn(frame_D0, Name("data"), Binning(80)) ;
  ws->loadSnapshot("fitResults") ;
  
  model->plotOn(frame_D0,Components(*sig), LineColor(kRed));  
  model->plotOn(frame_D0,Components(*comb_bkg),LineColor(kGreen)); 
  model->plotOn(frame_D0, Name("model"),LineColor(kBlue));
  
  TCanvas* c = new TCanvas("c1", "", 800, 600);
  c->Divide(2,2);
  c->cd(1);
  (frame_D0->GetYaxis())->SetTitleOffset(1.20);
  frame_D0->Draw();
  lhcb7TeVPrelimL->Draw();

  c->cd(2);
  data_w->plotOn(frame_PID1, DataError(RooAbsData::SumW2), LineColor(kGreen),  MarkerColor(kGreen), Binning(160)) ;
  frame_PID1->Draw();
  lhcb7TeVPrelimL->Draw();

  c->cd(3);
  data_w->plotOn(frame_PID2, DataError(RooAbsData::SumW2), LineColor(kBlue),  MarkerColor(kBlue), Binning(160)) ;
  frame_PID2->Draw();
  lhcb7TeVPrelimL->Draw();

  c->cd(4);
  data_w->plotOn(frame_nTracks, DataError(RooAbsData::SumW2), LineColor(kRed),  MarkerColor(kRed), Binning(60)) ;
  frame_nTracks->Draw();
  lhcb7TeVPrelimR->Draw();
}
