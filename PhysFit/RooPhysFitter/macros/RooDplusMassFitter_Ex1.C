/** Example of how to use RooDplusMassFitter to fit a (toy) nTuple, construct
sWeights, and plot the results.
*/

Float_t dplusMassPDG=1869.62;
Float_t dsMassPDG=1968.50;

/// Export a RooDataSet as a TTree
TTree* exportData(const RooDataSet& data) {
  cout << "Exporting generated dataset to TTree" << endl;
  TTree* tt = new TTree(data.GetName(), data.GetTitle());
  Int_t nentries = data.numEntries();
  
  UInt_t nvars=0;
  UInt_t ncats=0;
  
  const RooArgSet* args = data.get();
  RooAbsArg* arg;
  
  // get number of variables and categories
  RooLinkedListIter iter = args->iterator();
  while ( (arg=(RooAbsArg*)iter.Next()) ) {
    if ( strcmp(arg->IsA()->GetName(),"RooRealVar")==0 ) {
      nvars++;
    }
    else if ( strcmp(arg->IsA()->GetName(),"RooCategory")==0 ) {
      ncats++;
    }
    else {
      cout << "Argument " << arg << " has unknown type" << endl;
      delete tt;
      tt=NULL;
      return NULL;
    }
  }
  
  // make arrays
  TString* varNames = new TString[nvars];
  Double_t* vars = new Double_t[nvars];
  TString* catNames = new TString[ncats];
  Int_t* cats = new Int_t[ncats];
  
  UInt_t ivar=0;
  UInt_t icat=0;
  
  iter = args->iterator();
  while ( (arg=(RooAbsArg*)iter.Next()) ) {
    TString name = arg->GetName();
    if ( ( strcmp(arg->IsA()->GetName(),"RooCategory")==0 ) ) {
      cats[icat] = 0;
      catNames[icat] = name;
      tt->Branch(name, &(cats[icat]));
      icat++;
    }
    else {
      vars[ivar] = 0.0;
      varNames[ivar] = name;
      tt->Branch(name, &(vars[ivar]));
      ivar++;
    }
  }
  // fill the TTree
  for (Int_t ientry=0; ientry<nentries; ++ientry) {
    const RooArgSet* params = data.get(ientry);
    for ( ivar=0; ivar<nvars; ++ivar ) {
      vars[ivar] = params->getRealValue( (varNames[ivar]).Data() );
    }
    for ( icat=0; icat<ncats; ++icat ) {
      cats[icat] = params->getCatIndex( (catNames[icat]).Data() );
    }
    tt->Fill();
  }

  delete[] varNames;
  delete[] vars;
  delete[] catNames;
  /*
  delete[] cats; */
  return tt;
}

/// Make the signal + background models.
void makeModel() 
{
  // create the output file and workspace
  TFile* f = new TFile("toydata.root", "RECREATE");
  
  RooWorkspace* ws = new RooWorkspace("ToyWS", "");

  // signal PDF of D+ mass
  TString dplusSigStr;
  dplusSigStr.Form("Gaussian::dplusSig(mass[%f,%f],dplus_mu[%f,%f,%f],dplus_sigma[5,2.5,15])",
                   dplusMassPDG-70, dsMassPDG+70, dplusMassPDG, dplusMassPDG-12, dplusMassPDG+12);
  
  ws->factory(dplusSigStr.Data());

  // signal PDF of Ds+ mass
  TString dsSigStr;
  dsSigStr.Form("Gaussian::dsSig(mass,ds_mu[%f,%f,%f],ds_sigma[5.5,2.5,15])",
                dsMassPDG, dsMassPDG-12, dsMassPDG+12);
  
  ws->factory(dsSigStr.Data());

  // background PDF of D+/Ds mass
  ws->factory("Chebychev::dplusdsBkg(mass,{poly_c1[-0.05,-1.,1.]})");

  // signal PDF of arbitary variable "x"
  ws->factory("Gaussian::xSig(x[250,750],muX[500,450,550],sigmaX[20,10,60])");
  // background PDF of arbitary variable "x"
  ws->factory("Exponential::xBkg(x,cX[-0.003,-0.01,-0.00001])");

  // combined sig PDF of D+ mass and "x"
  ws->factory("PROD::dplusSigModel(dplusSig,xSig)");
  // combined sig PDF of Ds+ mass and "x"
  ws->factory("PROD::dsSigModel(dsSig,xSig)");
  // combined bkg PDF of D+/Ds+ mass and "x"
  ws->factory("PROD::bkgModel(dplusdsBkg,xBkg)");

  ws->Write();
  delete ws;
  delete f;
}

/** Generates a combined signal + background toy MC dataset
 */
void makeData() 
{
  TFile* f = new TFile("toydata.root", "UPDATE");
  RooWorkspace* ws = (RooWorkspace*)f->Get("ToyWS");

  RooRealVar* mass = ws->var("mass");
  RooRealVar* x = ws->var("x");

  // create a category with explicitly numbered states
  RooCategory y("y","Signal/background classification") ;
  y.defineType("Dplus",0);
  y.defineType("Ds",1);
  y.defineType("Background",2);

  // total number of events to generate
  Int_t nevts = 10000;
  
  // get total number of signal events to generate (between 30 and 70% of nevts)
  Double_t sigfrac = gRandom->Uniform(0.3, 0.7);
  Int_t nsig =  TMath::FloorNint(sigfrac*nevts);

  // get the number of Ds+ events to generate (between 50 and 70% of nsig)
  Double_t dsSigfrac = gRandom->Uniform(0.5, 0.7);
  Int_t nds =  TMath::FloorNint(dsSigfrac*nsig);

  // generate signal datasets
  RooArgSet* params = new RooArgSet("Params");
  params->add(*mass);
  params->add(*x);
 
  RooProdPdf* dsSigModel = dynamic_cast<RooProdPdf*>(ws->pdf("dsSigModel"));
  RooDataSet* dsSigData = dsSigModel->generate(*params, nds);
 
  RooProdPdf* dplusSigModel = dynamic_cast<RooProdPdf*>(ws->pdf("dplusSigModel"));
  RooDataSet* dplusSigData = dplusSigModel->generate(*params, nsig-nds);

  // generate background toy dataset
  RooProdPdf* bkgModel = dynamic_cast<RooProdPdf*>(ws->pdf("bkgModel"));
  RooDataSet* bkgData = bkgModel->generate(*params, nevts-nsig);

  cout << "Generated " << dsSigData->numEntries() << " Ds+ signal events" << endl;
  cout << "Generated " << dplusSigData->numEntries() << " Ds+ signal events" << endl;
  cout << "Generated " << bkgData->numEntries() << " background events" << endl;

  // merge the signal and background datasets
  RooDataSet* data = new RooDataSet("toydata", "", *params,
                                    Index(y),
                                    Import("Dplus", *dplusSigData),
                                    Import("Ds", *dsSigData),
                                    Import("Background", *bkgData));
  data->Print();
  
  // save the toy dataset as a TTree 
  TTree* tt = exportData(*data);
  f->cd();
  tt->Write();
  delete dsSigData;
  delete dplusSigData;
  delete bkgData;
  delete data;
  delete ws;
  delete f;
}

/** Read the toy data and perform the fit.
    @param sigType The signal PDF to use (same PDF used to fit D+ and Ds
    signal peaks). Accepted values are:
    gauss          - Gaussian;
    cb             - Crystal Ball;
    dblGauss       - Sum of two Gaussians with a common mean;
    cruijff        - Cruijff;
    cruijffSimple  - Cruijff with same sigma for left and right tails.
 */
void MakeFit(const char* sigType) 
{
  TFile* f = TFile::Open("toydata.root", "READ");
  f->ls();
  TTree* tt = gDirectory->Get("toydata");
  tt->Print();
  
  RooPhysFit::RooDplusMassFitter* fitter 
    = new RooPhysFit::RooDplusMassFitter(TString::Format("Fitter_%s",
                                         sigType).Data(),
                                         "An example fitter");

  cout << "Creating workspace instance" << endl;
  fitter->CreateWS("FitWS","");
  
  cout << "Attach output file" << endl;
  fitter->AttachFile(TString::Format("output_%s.root",sigType).Data(),
                     "RECREATE");

  // create the fitter object
  cout << "************************************************************" << endl;
  cout << "Performing fits for signal type " << sigType << endl;
  
  cout << "Setting parameter names" << endl;
  const RooPhysFit::RooDplusMassFitter::PartType DsPart
    = RooPhysFit::RooDplusMassFitter::Ds;
  RooPhysFit::RooDplusMassFitter::PartType DplusPart
    = RooPhysFit::RooDplusMassFitter::Dplus;

  fitter->SetDplusMassSigPartName(DsPart, "D_{s}^{+}");
  fitter->SetDplusMassSigPartName(DplusPart, "D^{+}");
  fitter->SetDplusMassName("mass");
  fitter->SetDplusMassSigModelName(DsPart, "dsSigModel");
  fitter->SetDplusMassSigModelName(DplusPart, "dplusSigModel");
  fitter->SetDplusMassBkgModelName("bkgModel");
  fitter->SetModelName("model");
  fitter->SetSWeightSetName("SWeights");
  fitter->SetPlotParameterSetName("PlotParams");
  fitter->SetSpectatorSetName("Spectators");
  fitter->SetCategorySetName("Categories");
  
  cout << "Create D+ mass variable" << endl;
  // arguments are: xmin, xmax, unit, title
  fitter->MakeDplusMassVar(dplusMassPDG-70, dsMassPDG+70, "MeV/c^{2}", 
                           "Toy MC D_{(s)}^{+} mass");
  
  cout << "Add spectators" << endl;
  // arguments are: name, xmin, xmax, branch name
  fitter->AddSpectator("exampleVar", 250, 750, "x");

  cout << "Add categories" << endl;
  TString types[3] = {"Dplus", "Ds", "Background"};
  Int_t indices[3] = {0, 1, 2};
  
  // arguments are: name, array of state names, array of indices,
  // number of indices, branch name
  fitter->AddCategory("bkgCat", types, indices, 3, "y");

  cout << "Making data set" << endl;
  fitter->MakeDplusMassDataSet(tt, "mass", "data");

  // flat combinatoric D0 background
  fitter->MakeDplusMassBkgFlat(0., -1., 1.);

  cout << "Making model" << endl;
  if (strcmp(sigType,"gauss")==0) {
    // single Gaussian signal
    fitter->MakeDplusMassSigGauss(DplusPart,
                                  dplusMassPDG, dplusMassPDG-25., dplusMassPDG+25.,
                                  5., 2.5, 15. /* sigma start, min, max */ );
    fitter->MakeDplusMassSigGauss(DsPart,
                                  dsMassPDG, dsMassPDG-25., dsMassPDG+25.,
                                  5., 2.5, 15. /* sigma start, min, max */ );
    TString plotParams="dplusmass_dplus_mu,dplusmass_dplus_sigma";
    plotParams+=",dplusmass_ds_mu,dplusmass_ds_sigma,dplusmass_bkg_poly_c1";
    fitter->SetPlotParameters(plotParams.Data());
  }
  else if (strcmp(sigType,"cb")==0) {
    // single CB
    fitter->MakeDplusMassSigCB(DplusPart,
                               dplusMassPDG, dplusMassPDG-25., dplusMassPDG+25.,
                               5., 2.5, 15., /* sigma start, min, max */
                               0.2, 0., 10., /* alpha start, min, max */
                               3., 1., 20. /* n start, min, max */);
    fitter->MakeDplusMassSigCB(DsPart,
                               dsMassPDG, dsMassPDG-25., dsMassPDG+25.,
                               5., 2.5, 15., /* sigma start, min, max */
                               0.2, 0., 10., /* alpha start, min, max */
                               3., 1., 20. /* n start, min, max */);
    TString plotParams="dplusmass_dplus_mu,dplusmass_dplus_sigma";
    plotParams+=",dplusmass_dplus_alpha,dplusmass_dplus_n";
    plotParams+=",dplusmass_ds_mu,dplusmass_ds_sigma";
    plotParams+=",dplusmass_ds_alpha,dplusmass_ds_n";
    plotParams+=",dplusmass_bkg_poly_c1";
    fitter->SetPlotParameters(plotParams.Data());
  }
  else if (strcmp(sigType,"dblGauss")==0) {
    // double Gaussian signal (common mean)
    fitter->MakeDplusMassSigBiGauss(DplusPart,
                                    dplusMassPDG, dplusMassPDG-25., 
                                    dplusMassPDG+25.,
                                    5, 2.5, 15., /* sigma0 start, min, max */
                                    1.5, 1., 3., /* sigma1/sigma0 start, min, max */
                                    0.85 /* core fraction start */ );
    fitter->MakeDplusMassSigBiGauss(DsPart,
                                    dsMassPDG, dsMassPDG-25., dsMassPDG+25.,
                                    5, 2.5, 15., /* sigma0 start, min, max */
                                    1.5, 1., 3., /* sigma1/sigma0 start, min, max */
                                    0.85 /* core fraction start */ );
    TString plotParams="dplusmass_dplus_mu,dplusmass_dplus_sigma0";
    plotParams+=",dplusmass_dplus_sigma1";
    plotParams+=",dplusmass_ds_mu,dplusmass_ds_sigma0";
    plotParams+=",dplusmass_ds_sigma1";
    plotParams+=",dplusmass_bkg_poly_c1";
    fitter->SetPlotParameters(plotParams.Data());
  }
  else if (strcmp(sigType,"cruijff")==0) {
    // single Cruijff
    fitter->MakeDplusMassSigCruijff(DplusPart,
                                    dplusMassPDG,dplusMassPDG-25,dplusMassPDG+25,
                                    5, 2.5, 15., /* left sigma start, min, max */
                                    5, 2.5, 15., /* right sigma start, min, max */
                                    0.2, 0, 10, /* left alpha start, min, max */
                                    0.2, 0, 10 /* right alpha start, min, max */ );
    fitter->MakeDplusMassSigCruijff(DsPart,
                                    dsMassPDG,dsMassPDG-25,dsMassPDG+25,
                                    5, 2.5, 15., /* left sigma start, min, max */
                                    5, 2.5, 15., /* right sigma start, min, max */
                                    0.2, 0, 10, /* left alpha start, min, max */
                                    0.2, 0, 10 /* right alpha start, min, max */ );
    TString plotParams="dplusmass_dplus_mu,dplusmass_dplus_sigmaL";
    plotParams+=",dplusmass_dplus_sigmaR,dplusmass_dplus_alphaL";
    plotParams+=",dplusmass_dplus_alphaR";
    plotParams+=",dplusmass_ds_mu,dplusmass_ds_sigmaL";
    plotParams+=",dplusmass_ds_sigmaR,dplusmass_ds_alphaL";
    plotParams+=",dplusmass_ds_alphaR";
    plotParams+=",dplusmass_bkg_poly_c1";
    fitter->SetPlotParameters(plotParams.Data());
  }
  else if (strcmp(sigType,"cruijffSimple")==0) {
    // single Cruijff (common sigma)
    fitter->MakeDplusMassSigCruijff(DplusPart,
                                    dplusMassPDG,dplusMassPDG-25,dplusMassPDG+25,
                                    5, 2.5, 15., /* sigma start, min, max */
                                    0.2, 0, 10, /* left alpha start, min, max */
                                    0.2, 0, 10 /* right alpha start, min, max */);
    fitter->MakeDplusMassSigCruijff(DsPart,
                                    dsMassPDG,dsMassPDG-25,dsMassPDG+25,
                                    5, 2.5, 15., /* sigma start, min, max */
                                    0.2, 0, 10, /* left alpha start, min, max */
                                    0.2, 0, 10 /* right alpha start, min, max */);
    TString plotParams="dplusmass_dplus_mu,dplusmass_dplus_sigma";
    plotParams+=",dplusmass_dplus_alphaL,dplusmass_dplus_alphaR";
    plotParams+=",dplusmass_ds_mu,dplusmass_ds_sigma";
    plotParams+=",dplusmass_ds_alphaL,dplusmass_ds_alphaR";
    plotParams+=",dplusmass_bkg_poly_c1";
    fitter->SetPlotParameters(plotParams.Data());
  } 
  else {
    cout << "Unexpected signal type " << sigType << endl;
    exit(1);
  }

  // arguments: Dplus fraction start, Ds fraction start,
  // background fraction start
  fitter->MakeDplusMassModel(0.25, 0.35, 0.4);
 
  // set the plot attributes
  cout << "Setting plot attributes" << endl;
  fitter->AddPdfComponent("dplusSigModel", kRed, kDashed, 3);
  fitter->AddPdfComponent("dsSigModel", kMagenta, kDashed, 3);
  fitter->AddPdfComponent("bkgModel", kGreen+3, kDotted, 3);
  
  // set the bins
  cout << "Setting plot parameters" << endl;
  fitter->SetPlotBins(100);
  fitter->SetParamBoxX1(0.4);
  fitter->SetParamBoxY1(0.5);
  fitter->SetParamBoxY2(0.9);
  fitter->SetParamBoxX2(0.65);
  fitter->SetParamBoxTextSize(0.038);
  
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
  
  // create weighted data set for D+ signal sWeight
  // arguments: 
  // 1) name of data set with weights;
  // 2) name of sWeight variable;
  // 3) fit name ("fitResults");
  // 4) save to workspace? (true).
  cout << "Creating D+ signal sWeighted data set" << endl;
  fitter->CreateWeightedDataSet("data_dplus", "ndplus_sw", "fitRes");
  
  // create weighted data set for D+ signal sWeight
  // arguments: 
  // 1) name of data set with weights;
  // 2) name of sWeight variable;
  // 3) fit name ("fitResults");
  // 4) save to workspace? (true).
  cout << "Creating Ds+ signal sWeighted data set" << endl;
  fitter->CreateWeightedDataSet("data_ds", "nds_sw", "fitRes");
  
  // create weighted data set for bkg sWeight
  // arguments: 
  // 1) name of data set with weights;
  // 2) name of sWeight variable;
  // 3) fit name ("fitResults");
  // 4) save to workspace? (true).
  cout << "Creating bkg. sWeighted data set" << endl;
  fitter->CreateWeightedDataSet("data_bkg", "nbkg_sw", "fitRes");

  RooRealVar* mass=fitter->GetVar("mass");
  mass->setRange("sigRange_dplus",dplusMassPDG-25,dplusMassPDG+25);
  mass->setRange("sigRange_ds",dsMassPDG-25,dsMassPDG+25);

  // plot the fit results
  // arguments: 
  // 1) variable name;
  // 2) fit name ("fitResults");
  // 3) range ("");
  // 4) range title ("");
  // 5) use sum-of-weights^2 errors? (false)
  cout << "Plotting fit results" << endl;
  TString rangeTitle="SigRange";
  RooPlot* rp = fitter->PlotFitResults("mass", "fitRes",
                                        "sigRange_dplus;sigRange_ds",
                                        rangeTitle.Data());
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
  c1->SaveAs(TString::Format("fitResults_%s.eps", sigType).Data());

  // plot the "exampleVar" (a.k.a. "x") variable
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
  cout << "Plotting variable 'exampleVar'" << endl;

  RooPlot* rp_var = fitter->PlotVariable("exampleVar");
  rp_var->SetTitleOffset(0.8, "Y");

  // plot the dplus sWeighted dataset
  fitter->SetDataSetName("data_dplus");
  fitter->SetDataSetLineColor(kRed);
  fitter->SetDataSetMarkerColor(kRed);
  fitter->SetDataSetMarkerStyle(kFullTriangleDown);
  fitter->PlotVariable("exampleVar", "", "", kTRUE, rp_var);

  // plot the background sWeighted dataset
  fitter->SetDataSetName("data_bkg");
  fitter->SetDataSetLineColor(kGreen+3);
  fitter->SetDataSetMarkerColor(kGreen+3);  
  fitter->SetDataSetMarkerStyle(kFullTriangleDown);
  fitter->PlotVariable("exampleVar", "", "", kTRUE, rp_var);

  // plot the associated D+ events
  fitter->SetDataSetName("data");
  fitter->SetDataSetLineColor(kMagenta);
  fitter->SetDataSetMarkerColor(kMagenta);
  fitter->SetDataSetMarkerStyle(kOpenCircle);
  fitter->PlotVariable("exampleVar",
                       "bkgCat==bkgCat::Dplus",
                       "", kFALSE, rp_var);   
  
  // plot the associated background events
  fitter->SetDataSetName("data");
  fitter->SetDataSetLineColor(kGreen);
  fitter->SetDataSetMarkerColor(kGreen);
  fitter->SetDataSetMarkerStyle(kOpenCircle);
  fitter->PlotVariable("exampleVar",
                       "bkgCat==bkgCat::Background",
                       "", kFALSE, rp_var);

  TCanvas* c2 = new TCanvas("c2", "example variable", 800, 600);
  rp_var->Draw();
  c2->SaveAs(TString::Format("exampleVar_dplus_%s.eps", sigType).Data());
  
  ///////////////////////////////////////////////////////////////////////
  delete rp_var;
  rp_Var=NULL;
  rp_var = fitter->PlotVariable("exampleVar");
  rp_var->SetTitleOffset(0.8, "Y");
  
  // plot the Ds sWeighted dataset
  fitter->SetDataSetName("data_ds");
  fitter->SetDataSetLineColor(kRed);
  fitter->SetDataSetMarkerColor(kRed);
  fitter->SetDataSetMarkerStyle(kFullTriangleDown);
  fitter->PlotVariable("exampleVar", "", "", kTRUE, rp_var);

  // plot the background sWeighted dataset
  fitter->SetDataSetName("data_bkg");
  fitter->SetDataSetLineColor(kGreen+3);
  fitter->SetDataSetMarkerColor(kGreen+3);  
  fitter->SetDataSetMarkerStyle(kFullTriangleDown);
  fitter->PlotVariable("exampleVar", "", "", kTRUE, rp_var);

  // plot the associated Ds events
  fitter->SetDataSetName("data");
  fitter->SetDataSetLineColor(kMagenta);
  fitter->SetDataSetMarkerColor(kMagenta);
  fitter->SetDataSetMarkerStyle(kOpenCircle);
  fitter->PlotVariable("exampleVar",
                       "bkgCat==bkgCat::Ds",
                       "", kFALSE, rp_var);   
  
  // plot the associated background events
  fitter->SetDataSetName("data");
  fitter->SetDataSetLineColor(kGreen);
  fitter->SetDataSetMarkerColor(kGreen);
  fitter->SetDataSetMarkerStyle(kOpenCircle);
  fitter->PlotVariable("exampleVar",
                       "bkgCat==bkgCat::Background",
                       "", kFALSE, rp_var);

  TCanvas* c3 = new TCanvas("c3", "example variable", 800, 600);
  rp_var->Draw();
  c3->SaveAs(TString::Format("exampleVar_ds_%s.eps", sigType).Data());
  
 /*  TCanvas* c3 = new TCanvas("c3", "example variable", 800, 600);
  rp_var_bkg->Draw();
  c3->SaveAs(TString::Format("exampleVar_bkg_%s.eps", sigType).Data());
 */
  cout << "Saving workspace" << endl;
  fitter->SaveWS();
  cout << "Example completed!" << endl;

  delete f;
  delete fitter;
  delete c1;
  delete c2;
  delete c3;
  delete rp;
  delete rp_var;
}

void RooDplusMassFitter_Ex1()
{
  // load the libraries
  gSystem->Load("libMinuit.so");
  gSystem->Load("libRooFit.so");
  gSystem->Load("libRooFitCore.so");
  gSystem->Load("libRooStats.so");
  gSystem->Load("libCintex.so");
  ROOT::Cintex::Cintex cintex;
  ROOT::Cintex::Cintex::Enable();
  gSystem->Load("libRooPhysFitterLib.so");
  gSystem->Load("libRooPhysFitterDict.so");
  gROOT->ProcessLine(".x $ROOPHYSFITTERROOT/macros/lhcbstyle.C");

  // create the data+model
  makeModel();
  makeData();
  MakeFit("gauss");
  MakeFit("cruijffSimple");
  MakeFit("cruijff");
  MakeFit("dblGauss");
  MakeFit("cb");
}
