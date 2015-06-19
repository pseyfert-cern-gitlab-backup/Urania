// $Id: $
// Include files

using namespace RooFit;

//-----------------------------------------------------------------------------
// Implementation file for class : DLLKvsDLLp
//
// 2011-10-10 : Andrew Powell (LHCb)04
//-----------------------------------------------------------------------------

void DLLKvsDLLp_Kaon()
{
  gStyle->SetOptStat(0);
  
  TFile* f = new TFile("/data/lhcb/users/powell/gangadir/workspace"
                       "/powell/LocalXML/959/output"
                       "/DSt_KPlus_MagUp_Strip13b.root");
  
  //----------------------------------------------------
  // Get data
  //----------------------------------------------------
  RooWorkspace* Myws = (RooWorkspace*)f->Get("RSDStCalib");
  Myws->Print("v");
  RooRealVar* DLLK = Myws->var("K_RichDLLK");
  RooRealVar* DLLp = Myws->var("K_RichDLLp");
  RooDataSet* data = (RooDataSet*) Myws->data("data_wSWeights");

  //----------------------------------------------------
  // Create weighted dataset
  //----------------------------------------------------
  RooDataSet * data_w = new RooDataSet(data->GetName(),
                                       data->GetTitle(),
                                       data,*data->get(),
                                       0,
                                       "nsig_sw");

  RooBinning* DLLK_Binning = new RooBinning(-150,150,"DLLK_Binning");
  DLLK_Binning->addUniform(100,-150,150);
  RooBinning* DLLp_Binning = new RooBinning(-150,150,"DLLp_Binning");
  DLLp_Binning->addUniform(100,-150,150);
  
  TH2* my2D_DLL = data_w->createHistogram("",
                                          *DLLK,
                                          Binning(*DLLK_Binning),
                                          YVar(*DLLp, 
                                               Binning(*DLLp_Binning)) );
  
  my2D_DLL->GetZaxis()->SetRangeUser(0.0, my2D_DLL->GetMaximum());
  my2D_DLL->Draw("COLZ");
  my2D_DLL->GetXaxis()->SetTitle("#DeltaLL(K - #pi)");
  my2D_DLL->GetYaxis()->SetTitle("#DeltaLL(p - #pi)");
  lhcb7TeVPaper_L->Draw();
}


void DLLKvsDLLp_Pion()
{
  gStyle->SetOptStat(0);
  
  TFile* f = new TFile("/data/lhcb/users/powell/gangadir/workspace"
                       "/powell/LocalXML/963/output"
                       "/DSt_PiPlus_MagUp_Strip13b.root");
  
  //----------------------------------------------------
  // Get data
  //----------------------------------------------------
  RooWorkspace* Myws = (RooWorkspace*)f->Get("RSDStCalib");
  Myws->Print("v");
  RooRealVar* DLLK = Myws->var("Pi_RichDLLK");
  RooRealVar* DLLp = Myws->var("Pi_RichDLLp");
  RooDataSet* data = (RooDataSet*) Myws->data("data_wSWeights");

  //----------------------------------------------------
  // Create weighted dataset
  //----------------------------------------------------
  RooDataSet * data_w = new RooDataSet(data->GetName(),
                                       data->GetTitle(),
                                       data,*data->get(),
                                       0,
                                       "nsig_sw");

  RooBinning* DLLK_Binning = new RooBinning(-150,150,"DLLK_Binning");
  DLLK_Binning->addUniform(100,-150,150);
  RooBinning* DLLp_Binning = new RooBinning(-150,150,"DLLp_Binning");
  DLLp_Binning->addUniform(100,-150,150);
  
  TH2* my2D_DLL = data_w->createHistogram("",
                                          *DLLK,
                                          Binning(*DLLK_Binning),
                                          YVar(*DLLp, 
                                               Binning(*DLLp_Binning)) );
  
  my2D_DLL->GetZaxis()->SetRangeUser(0.0, my2D_DLL->GetMaximum());
  my2D_DLL->Draw("COLZ");
  my2D_DLL->GetXaxis()->SetTitle("#DeltaLL(K - #pi)");
  my2D_DLL->GetYaxis()->SetTitle("#DeltaLL(p - #pi)");
  lhcb7TeVPaper_L->Draw();
}


void DLLKvsDLLp_Proton()
{
  gStyle->SetOptStat(0);
  
  TFile* f = new TFile("/data/lhcb/users/powell/gangadir/workspace"
                       "/powell/LocalXML/973/output"
                       "/Lam0_PPlus_MagUp_Strip13b.root");
  
  //----------------------------------------------------
  // Get data
  //----------------------------------------------------
  RooWorkspace* Myws = (RooWorkspace*)f->Get("Lam0Calib");
  Myws->Print("v");
  RooRealVar* DLLK = Myws->var("P_RichDLLK");
  RooRealVar* DLLp = Myws->var("P_RichDLLp");
  RooDataSet* data = (RooDataSet*) Myws->data("data_wSWeights");

  //----------------------------------------------------
  // Create weighted dataset
  //----------------------------------------------------
  RooDataSet * data_w = new RooDataSet(data->GetName(),
                                       data->GetTitle(),
                                       data,*data->get(),
                                       0,
                                       "nsig_sw");

  RooBinning* DLLK_Binning = new RooBinning(-150,150,"DLLK_Binning");
  DLLK_Binning->addUniform(100,-150,150);
  RooBinning* DLLp_Binning = new RooBinning(-150,150,"DLLp_Binning");
  DLLp_Binning->addUniform(100,-150,150);
  
  TH2* my2D_DLL = data_w->createHistogram("",
                                          *DLLK,
                                          Binning(*DLLK_Binning),
                                          YVar(*DLLp, 
                                               Binning(*DLLp_Binning)) );
  
  my2D_DLL->GetZaxis()->SetRangeUser(0.0, my2D_DLL->GetMaximum());
  my2D_DLL->Draw("COLZ");
  my2D_DLL->GetXaxis()->SetTitle("#DeltaLL(K - #pi)");
  my2D_DLL->GetYaxis()->SetTitle("#DeltaLL(p - #pi)");
  lhcb7TeVPaper_L->Draw();
}
