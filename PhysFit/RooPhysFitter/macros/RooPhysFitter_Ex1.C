/** Example of how to use RooPhysFitter to fit a (toy) dataset, construct
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
  // combined full PDF of d0 mass and "x" (30% signal fraction)
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
  delete data;
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
  fitter->AddPdfComponent("d0Bkg", kGreen+3, kDotted, 2);
  fitter->SetPlotParameters("mu,sigma,poly_c1");
  fitter->SetParamBoxX1(0.7);
  fitter->SetParamBoxTextSize(0.04);
  
  // set the bins
  cout << "Setting plot bins" << endl;
  fitter->SetPlotBins(100);

  // perform the fit 
  // arguments:
  // 1) fitName ("fitResults");
  // 2) nCores (4);
  // 3) save snapshot? (true),
  // 4) print results? (false);
  // 5) use sum-of-weights^2 errors? (false);
  // 6) perform extended fit (true)
  cout << "Performing fit" << endl;
  fitter->PerformFit("fitRes", 4, kTRUE, kTRUE, kFALSE, kTRUE);
  
  // calculate sWeights
  // arguments: 
  // 1) fitName ("fitResults");
  // 2) name of data set with weights ("").
  cout << "Calculting sWeights" << endl;
  fitter->CalculateSWeights("fitRes", "data_withSWeights");
  
  // create weighted data set for signal sWeight
  // arguments: 
  // 1) name of data set with weights;
  // 2) name of sWeight variable;
  // 3) fit name ("fitResults");
  // 4) save to workspace? (true).
  cout << "Creating signal sWeighted data set" << endl;
  fitter->CreateWeightedDataSet("data_sig", "nsig_sw", "fitRes");
  
  // create weighted data set for bkg sWeight
  // arguments: 
  // 1) name of data set with weights;
  // 2) name of sWeight variable;
  // 3) fit name ("fitResults");
  // 4) save to workspace? (true).
  cout << "Creating bkg. sWeighted data set" << endl;
  fitter->CreateWeightedDataSet("data_bkg", "nbkg_sw", "fitRes");
  
  // plot the fit results
  // arguments: 
  // 1) variable name;
  // 2) fit name ("fitResults");
  // 3) range ("");
  // 4) range title ("");
  // 5) use sum-of-weights^2 errors? (false)
  cout << "Plotting fit results" << endl;
  RooPlot* rp = fitter->PlotFitResults("mass", "fitRes");
  rp->SetTitleOffset(0.8, "Y");
  
  // make the pull plot
  // arguments:
  // 1) variable name;
  // 2) fit name ("fitResults");
  RooPlot* rp_pull = fitter->PlotFitPulls("mass", "fitRes");
  rp_pull->SetTitle(";;");
  rp_pull->SetLabelSize(0.12, "X");
  rp_pull->SetLabelSize(0.12, "Y");

  TCanvas* c1 = new TCanvas("c1", "Fit Results", 800, 600);
  TPad* c1_upper = new TPad("cnv_mass_upper", "", 0.005, 0.30, 0.995, 0.995);
  TPad* c1_lower = new TPad("cnv_mass_lower", "", 0.005, 0.05, 0.995, 0.295);
  c1_upper->Draw();
  c1_lower->Draw();
  c1_upper->cd();
  rp->Draw();
  c1_lower->cd();
  rp_pull->Draw();
  c1->SaveAs("fitResults.eps");
  
  // plot the "x" variable
  // arguments: 
  // arguments: 
  // 1) variable name;
  // 2) cut(s) ("");
  // 3) range ("");
  // 4) use sum-of-weights^2 errors (false);
  // 5) plot frame (NULL), used for plotting on existing frame;
  // 6) plot scale (0 = no scaling);
  // 7) new name for plot ("");
  // 8) minimum of plot (0 = use default);
  // 9) maximum of plot (0 = use default).
  //
  // Returns RooPlot, unless an existing plot frame is specified
  cout << "Plotting variable 'x'" << endl;
  RooPlot* rp_var = fitter->PlotVariable("x");
  rp_var->SetTitleOffset(0.8, "Y");

  fitter->SetDataSetName("data_sig");
  fitter->SetDataSetLineColor(kRed);
  fitter->SetDataSetMarkerColor(kRed);
  fitter->SetDataSetMarkerStyle(kFullTriangleDown);
  fitter->PlotVariable("x", "", "", kTRUE, rp_var);

  fitter->SetDataSetName("data_bkg");
  fitter->SetDataSetLineColor(kGreen+3);
  fitter->SetDataSetMarkerColor(kGreen+3);
  fitter->SetDataSetMarkerStyle(kFullTriangleDown);
  fitter->PlotVariable("x", "", "", kTRUE, rp_var);

  TCanvas* c2 = new TCanvas("c2", "x Variable", 800, 600);
  rp_var->Draw();
  c2->SaveAs("xVar.eps");

  cout << "Saving workspace" << endl;
  fitter->SaveWS();
  cout << "Example completed!" << endl;

  delete rp;
  rp=NULL;
  delete rp_pull;
  rp_pull=NULL;
  delete rp_var;
  rp_var=NULL;
  delete c1;
  c1=NULL;
  delete c2;
  c2=NULL;
  delete fitter;
  fitter=NULL;
}
