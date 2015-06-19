//#include "RooWorkspace.h"
//#include "RooRealVar.h"
//#include "RooGaussian.h"
//#include "RooChebychev.h"
//#include "RooAddPdf.h"
//#include "RooDataSet.h"
//#include "RooPlot.h"

//#include "TFile.h"
//#include "TCanvas.h"
//#include "TROOT.h"

//#include "RooPhysFitter/RooPhysFitter.h"

/* example of how to use RooPhysFitter to fit a (toy) dataset, construct
sWeights, and plot the results
*/
void makeModel() 
{
  // create the output file and workspace
  TFile* f = new TFile("output.root", "RECREATE");
  RooWorkspace* ws = new RooWorkspace("WS", "");

  // signal PDF of D0 mass
  ws->factory("Gaussian::d0Sig(mass[1789.83,1939.85],mu[1864.83,1839.83,1889.83],sigma[8,4,24])");

  // background PDF of D0 mass
  ws->factory("Chebychev::d0Bkg(mass,{poly_c1[0.,-10.,10.]})");

  // combined PDF of D0 mass
  ws->factory("SUM::model(nsig[3000,0,10000]*d0Sig,nbkg[7000,0,10000]*d0Bkg)");

  // signal PDF of arbitary variable "x"
  ws->factory("Gaussian::xSig(x[250,750],muX[500,450,550],sigmaX[20,10,60])");
  // background PDF of arbitary variable "x"
  ws->factory("Exponential::xBkg(x,cX[-0.001,-0.01,-0.00001])");

  // combined PDF of arbitary variable "x"
  ws->factory("SUM::modelX(nsigX[2000,0,10000]*xSig,nbkgX[7500,0,10000]*xBkg)");
  // combined sig PDF of d0 mass and "x"
  ws->factory("PROD::sigModel(d0Sig,xSig)");
  // combined bkg PDF of d0 mass and "x"
  ws->factory("PROD::bkgModel(d0Bkg,xBkg)");
  // combined full PDF of d0 mass and "x"
  ws->factory("SUM::fullModel(nsigFull[3000,0,10000]*sigModel,nbkgFull[7000,0,10000]*bkgModel)");
  ws->Write();
  delete ws;
  delete f;
}
void makeData() 
{
  TFile* f = new TFile("output.root", "UPDATE");
  RooWorkspace* ws = (RooWorkspace*)f->Get("WS");

  RooRealVar* mass = ws->var("mass");
  RooRealVar* x = ws->var("x");
  RooAddPdf* model = dynamic_cast<RooAddPdf*>(ws->pdf("fullModel"));
  RooDataSet* data = model->generate(RooArgSet(*mass,*x), 10000);
  if (ws->import(*data, RooFit::Rename("data"))) exit(1);
  f->cd();
  ws->Write();
  delete ws;
  delete f;
}

void RooPhysFitter_Ex1()
{
  // load the libraries
  ROOT::Cintex::Cintex cintex;
  ROOT::Cintex::Cintex::Enable();
  gSystem->Load("libRooPhysFitterLib.so");
  gSystem->Load("libRooPhysFitterDict.so");
  gROOT->ProcessLine(".x $ROOPHYSFITTERROOT/macros/lhcbstyle.C");
  using namespace RooFit;
  using namespace RooPhysFit;
  using namespace std;
  
  // create the data+model
  cout << "Making model" << endl;
  makeModel();
  cout << "Making data set" << endl;
  makeData(); 
  
  // create the fitter object
  cout << "Creating fitter instance" << endl;
  RooPhysFitter* fitter = new RooPhysFitter("ExampleFitter",
                                            "An example fitter");
  
  // load the workspace containing a model and generated dataset,
  // and attach the file for editing
  cout << "Loading workspace" << endl;
  fitter->LoadWS("output.root", "WS", kTRUE);
  
  // set the input parameter names
  cout << "Setting input parameter names" << endl;
  fitter->SetDataSetName("data");
  fitter->SetModelName("model");
  fitter->SetSWeightSetName("SWeights");
  fitter->SetPlotParameterSetName("PlotParams");
  
  // set the plot attributes
  cout << "Setting plot attributes" << endl;
  fitter->AddPdfComponent("d0Sig", kRed, kDashed, 2);
  fitter->AddPdfComponent("d0Bkg", kMagenta, kDotted, 2);
  fitter->SetPlotParameters("mu,sigma,poly_c1");
  
  // set the chi^2 test statistic
  cout << "Setting test statistic" << endl;
  fitter->SetChi2TestStat(RooPhysFitter::LLRatio);
  
  // set the bins
  cout << "Setting plot bins" << endl;
  fitter->SetPlotBins(100);
  fitter->SetChi2Bins(200);

  // peform the fit 
  // arguments: fitName ("fitResults"), nCores (4), save snapshot (true),
  // print results (false), use sum-of-weights^2 errors (false),
  // perform extended fit (true)
  cout << "Performing fit" << endl;
  fitter->PerformFit("fitRes", 4, kTRUE, kTRUE, kFALSE, kTRUE);
  
  // calculate sWeights
  // arguments: fitName ("fitResults"), name of data set with weights ("")
  cout << "Calculting sWeights" << endl;
  fitter->CalculateSWeights("fitRes", "data_withSWeights");
  
  // create weighted data set for signal sWeight
  // arguments: name of data set with weights,
  // name of sWeight variable, save to workspace (true)
  cout << "Creating signal sWeighted data set" << endl;
//   fitter->SetDataSetName("data_withSWeights");
  fitter->CreateWeightedDataSet("data_sig", "nsig_sw", "fitRes");
  
  // create weighted data set for bkg sWeight
  // arguments: name of data set with weights,
  // name of sWeight variable, save to workspace (true)
  cout << "Creating bkg. sWeighted data set" << endl;
//   fitter->SetDataSetName("data_withSWeights");
  fitter->CreateWeightedDataSet("data_bkg", "nbkg_sw", "fitRes");
  
  // plot the fit results
  // arguments: variable name, fit name ("fitResults"),
  // range (""), range title (""), use sum-of-weights^2 errors (false),
  // print chi^2 (true), perform extended chi^2 fit (true)
  // number of cores for chi^2 fit (4)
  cout << "Plotting fit results" << endl;
  RooPlot* rp = fitter->PlotFitResults("mass", "fitRes");
  TCanvas* c1 = new TCanvas("c1", "Fit Results", 800, 600);
  rp->Draw();
  c1->SaveAs("fitResults.eps");
  
  // plot the "x" variable
  // arguments: variable name, range (""),  
  // use sum-of-weights^2 errors (false),
  // plot frame (NULL), plot scale (0), new name for plot (""),
  // minimum of plot (0), maximum of plot (0)
  cout << "Plotting variable 'x'" << endl;
  RooPlot* rp_var = fitter->PlotVariable("x");

  fitter->SetDataSetName("data_sig");
  fitter->SetDataSetLineColor(kRed);
  fitter->SetDataSetMarkerColor(kRed);
  fitter->PlotVariable("x", "", kTRUE, rp_var);

  fitter->SetDataSetName("data_bkg");
  fitter->SetDataSetLineColor(kBlue);
  fitter->SetDataSetMarkerColor(kBlue);
  fitter->PlotVariable("x", "", kTRUE, rp_var);

  TCanvas* c2 = new TCanvas("c2", "x Variable", 800, 600);
  rp_var->Draw();
  c2->SaveAs("xVar.eps");

 //  // create likelihood scan plots for the model parameters
  //  fitter->SetDataSetName("data");
//   cout << "Plot likelihood scan for mu" << endl;
//   RooPlot* rp_mu = fitter->PlotLikelihoodScan("mu", "fitRes");
//   TCanvas* c4 = new TCanvas("c4", "LL for mu", 1024, 768);
//   rp_mu->Draw();
//   c4->SaveAs("LL_mu.eps");

//   cout << "Plot likelihood scan for sigma" << endl;
//   RooPlot* rp_sigma = fitter->PlotLikelihoodScan("sigma", "fitRes");
//   TCanvas* c5 = new TCanvas("c5", "LL for sigma", 1024, 768);
//   rp_sigma->Draw();
//   c5->SaveAs("LL_sigma.eps");

//   cout << "Plot likelihood scan for poly_c1" << endl;
//   RooPlot* rp_poly_c1 = fitter->PlotLikelihoodScan("poly_c1", "fitRes");
//   TCanvas* c6 = new TCanvas("c6", "LL for poly_c1", 1024, 768);
//   rp_poly_c1->Draw();
//   c6->SaveAs("LL_poly_c1.eps");
  
  cout << "Saving workspace" << endl;
  fitter->SaveWS();
  cout << "Example completed!" << endl;
  //delete fitter;
  //fitter=0;
}
