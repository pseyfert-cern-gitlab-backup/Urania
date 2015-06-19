/** Example of how to use RooDstarD0MassFitter to fit a (toy) nTuple, construct
sWeights, and plot the results.
*/

Float_t d0MassPDG=1864.83;
Float_t delmPDG=145.421;
Float_t piPDG=139.57018;

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

  // signal PDF of D0 mass
  TString sigStr;
  sigStr.Form("Gaussian::d0Sig(mass[%f,%f],d0_mu[%f,%f,%f],d0_sigma[8,4,24])",
              d0MassPDG-70, d0MassPDG+70, d0MassPDG, d0MassPDG-25, d0MassPDG+25);
  
  ws->factory(sigStr.Data());

  // signal PDF of delta mass
  TString sigDelmStr;
  sigDelmStr.Form("Gaussian::delmSig(delm[%f,%f],delm_mu[%f,%f,%f],delm_sigma[0.8, 0.4, 2.4])",
              delmPDG-6.0, delmPDG+7.0, delmPDG, delmPDG-2.0, delmPDG+2.0);
  
  ws->factory(sigDelmStr.Data());
  
  // background PDF of D0 mass
  ws->factory("Chebychev::d0Bkg(mass,{poly_c1[0.,-1.,1.]})");
  
  // background PDF of delta mass
  TString delmBkgStr;
  delmBkgStr.Form("RooTwoBodyPhspApprox::delmBkg(delm, c1[3.7e-02,-10.,10.], c2[-5.5e-03,-10.,10.])");
//  delmBkgStr.Form("RooDstD0BG::delmBkg(delm, piThr[%f, %f, %f], c[5.0], a[2.9, 2.0, 4.0], b[-8])",
 //   piPDG, piPDG-1, piPDG+1);
  ws->factory(delmBkgStr.Data());
  
  // signal PDF of arbitary variable "x"
  ws->factory("Gaussian::xSig(x[250,750],muX[500,450,550],sigmaX[20,10,60])");
  // background PDF of arbitary variable "x"
  ws->factory("Exponential::xBkg(x,cX[-0.003,-0.01,-0.00001])");

  // combined sig PDF of d0 mass, delta mass and "x"
  ws->factory("PROD::sigModel(d0Sig,delmSig,xSig)");
  // combined bkg PDF of d0 mass, delta mass and "x"
  ws->factory("PROD::bkgModel(d0Bkg,delmBkg,xBkg)");
  // combined "random slow pion" PDF of d0 mass, delta mass and "x" (make x a property of the D0)
  ws->factory("PROD::randModel(d0Sig,delmBkg,xSig)");
  
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
  RooRealVar* delm = ws->var("delm");
  RooRealVar* x = ws->var("x");

  // create a category with explicitly numbered states
  RooCategory y("y","Signal/background classification") ;
  y.defineType("Signal",0);
  y.defineType("Background",1);
  y.defineType("RandomPion",2);
  
  // total number of events to generate
  Int_t nevts = 10000;
  
  // get number of signal events to generate (between 30 and 60% of nevts)
  Double_t sigfrac = gRandom->Uniform(0.3, 0.6);
  Int_t nsig =  TMath::FloorNint(sigfrac*nevts);
  
  // get number of random slow pion events to generate (between 10% and 30% of nevts)
  Double_t randfrac = gRandom->Uniform(0.1, 0.3);
  Int_t nrand =  TMath::FloorNint(randfrac*nevts);

  // generate signal dataset
  RooArgSet* params = new RooArgSet("Params");
  params->add(*mass);
  params->add(*delm);
  params->add(*x);
  
  // generate signal toy dataset
  RooProdPdf* sigModel = dynamic_cast<RooProdPdf*>(ws->pdf("sigModel"));
  RooDataSet* sigData = sigModel->generate(*params, nsig);

  // generate random slow pion toy dataset
  RooProdPdf* randModel = dynamic_cast<RooProdPdf*>(ws->pdf("randModel"));
  RooDataSet* randData = randModel->generate(*params, nrand);

  // generate background toy dataset
  RooProdPdf* bkgModel = dynamic_cast<RooProdPdf*>(ws->pdf("bkgModel"));
  RooDataSet* bkgData = bkgModel->generate(*params, nevts-nsig-nrand);

  cout << "Generated " << sigData->numEntries() << " signal events" << endl;
  cout << "Generated " << randData->numEntries() << " random slow pion events" << endl;
  cout << "Generated " << bkgData->numEntries() << " combinatoric background events" << endl;

  // merge the signal and background datasets
  RooDataSet* data = new RooDataSet("toydata", "", *params,
                                    Index(y),
                                    Import("Signal", *sigData),
                                    Import("Background", *bkgData),
                                    Import("RandomPion", *randData));
  data->Print();
  
  // save the toy dataset as a TTree 
  TTree* tt = exportData(*data);
  f->cd();
  tt->Write();
  delete sigData;
  delete bkgData;
  delete randData;
  delete data;
  delete ws;
  delete f;
}

/** Read the toy data and perform the fit.
    @param d0SigType The signal PDF to use for the D0 mass component. 
    @param d0BkgType The background PDF to use for the D0 mass component.
    @param delmSigType The signal PDF to use for the delta mass component.
    @param delmBkgType The background PDF to use for the delta mass component.
    
    Accepted signal PDF values are:
    gauss          - Gaussian;
    cb             - Crystal Ball;
    dblGauss       - Sum of two Gaussians with a common mean;
    cruijff        - Cruijff;
    cruijffSimple  - Cruijff with same sigma for left and right tails.
    
    Accepted D0 mass background PDF values are:
    linear     - first-order Chebychev polynomial;
    quadratic  - second-order Chebychev polynomial.
    
    Accepted delta mass background PDF values are:
    DstD0BG               - "RooDstD0BG" PDF;
    DstD0BGFixedThreshold - "RooDstD0BG" PDF with the pion threshold 
    fixed to the PDG pion mass;
    Granet                - Granet PDF;
    GranetFixedThreshold  - Granet PDF with the pion threshold fixed
    to the PDG pion mass.
 */
void MakeFit(const char* d0SigType, const char* d0BkgType, const char* delmSigType, const char* delmBkgType) 
{
  TFile* f = TFile::Open("toydata.root", "READ");
  f->ls();
  TTree* tt = gDirectory->Get("toydata");
  tt->Print();
  
  RooPhysFit::RooDstarD0MassFitter* fitter 
    = new RooPhysFit::RooDstarD0MassFitter(TString::Format("Fitter_%s_%s_%s_%s",
                                           d0SigType,d0BkgType,delmSigType,delmBkgType).Data(),
                                           "An example fitter");

  cout << "Creating workspace instance" << endl;
  fitter->CreateWS("FitWS","");
  
  cout << "Attach output file" << endl;
  fitter->AttachFile(TString::Format("output_%s_%s_%s_%s.root",
                     d0SigType,d0BkgType,delmSigType,delmBkgType).Data(),
                     "RECREATE");
                     
 
  // create the fitter object
  cout << "************************************************************" << endl;
  cout << "Performing fits for D0 signal type = " << d0SigType 
       << ", D0 bkg. type = " << d0BkgType
       << ", Delta mass signal type = " << delmSigType
       << ", Delta mass bkg. type = " << delmBkgType << endl;
  
  cout << "Setting parameter names" << endl;
  fitter->SetDMassPartName("D^{0}");
  fitter->SetDMassName("mass");
  fitter->SetDelmPartName("#Delta m");
  fitter->SetDelmName("delm");
  fitter->SetSWeightSetName("SWeights");
  fitter->SetPlotParameterSetName("PlotParams");
  fitter->SetSpectatorSetName("Spectators");
  fitter->SetCategorySetName("Categories");
  
  cout << "Create D0 mass variable" << endl;
  fitter->MakeDMassVar(d0MassPDG-70,d0MassPDG+70,"MeV/c^{2}", 
                       "Toy MC D^{0} mass");
  cout << "Create Delta mass variable" << endl;
  fitter->MakeDelmVar(delmPDG-6.0,delmPDG+7.0,"MeV/c^{2}", 
                      "Toy MC delta mass");

  cout << "Add spectators" << endl;
  // arguments are: name, xmin, xmax, branch name
  fitter->AddSpectator("exampleVar", 250, 750, "x");

  cout << "Add categories" << endl;
  TString types[3] = {"Signal", "Background", "RandomPion"};
  Int_t indices[3] = {0, 1, 2};

  // arguments are: name, list of state names, list of indices, branch name
  fitter->AddCategory("bkgCat", types, indices, 3, "y");
  
  cout << "Making data set" << endl;
  fitter->MakeDelmDataSet(tt, "mass", "delm", "data");

  TString plotParams_d0="";
  TString plotParams_delm="";

  cout << "Making D0 signal model" << endl;
  if (strcmp(d0SigType,"gauss")==0) {
    // single Gaussian signal
    fitter->MakeDMassSigGauss(d0MassPDG, d0MassPDG-25, d0MassPDG+25, 
                              8, 4, 24);
    plotParams_d0="dmass_sig_mu,dmass_sig_sigma";
  }
  else if (strcmp(d0SigType,"cb")==0) {
    // single CB
    fitter->MakeDMassSigCB(d0MassPDG, d0MassPDG-25, d0MassPDG+25,
                           8, 4, 24,
                           0.2, 0, 10,
                           3, 1, 20);
    plotParams_d0="dmass_sig_mu,dmass_sig_sigma,dmass_sig_alpha,dmass_sig_n";
  }
  else if (strcmp(d0SigType,"dblGauss")==0) {
    // double Gaussian signal (common mean)
    fitter->MakeDMassSigBiGauss(d0MassPDG, d0MassPDG-25, d0MassPDG+25,
                                8, 4, 24,
                                1.5, 1, 3,
                                0.85);
    plotParams_d0="dmass_sig_mu,dmass_sig_sigma0,dmass_sig_sigma1";
  }
  else if (strcmp(d0SigType,"cruijff")==0) {
    // single Cruijff
    fitter->MakeDMassSigCruijff(d0MassPDG, d0MassPDG-25, d0MassPDG+25,
                                8, 4, 24,
                                8, 4, 24,
                                0.2, 0, 10, 
                                0.2, 0, 10);
    plotParams_d0="dmass_sig_mu,dmass_sig_sigmaL,dmass_sig_sigmaR,dmass_sig_alphaL,dmass_sig_alphaR";
  }
  else if (strcmp(d0SigType,"cruijffSimple")==0) {
    // single Cruijff (common mean)
    fitter->MakeDMassSigCruijff(d0MassPDG, d0MassPDG-25, d0MassPDG+25,
                                8, 4, 24,
                                0.2, 0, 10,
                                0.2, 0, 10);
    plotParams_d0="dmass_sig_mu,dmass_sig_sigma,dmass_sig_alphaL,dmass_sig_alphaR";
  }
  else {
    cout << "Unexpected D0 signal type " << d0SigType << endl;
    exit(1);
  }

  
  cout << "Making D0 background model" << endl;
  if (strcmp(d0BkgType,"linear")==0) {
    fitter->MakeDMassBkgFlat(0,-1,1);
  }
  else if (strcmp(d0BkgType,"quadratic")==0) {
    fitter->MakeDMassBkgQuadratic(0,-1,1, 0,-1,1);
    plotParams_d0+=",dmass_bkg_poly_c1,dmass_bkg_poly_c2";
  }
  else {
    cout << "Unexpected D0 bkg. type " << d0BkgType << endl;
    exit(1);
  }

  
  cout << "Making Delta mass signal model" << endl;
  if (strcmp(delmSigType,"gauss")==0) {
    // single Gaussian signal
    fitter->MakeDelmSigGauss(delmPDG, delmPDG-2.5, delmPDG+2.5,
                             0.8, 0.4, 2.4);
    plotParams_delm="delm_sig_mu,delm_sig_sigma";
  }
  else if (strcmp(delmSigType,"cb")==0) {
    // single CB
    fitter->MakeDelmSigCB(delmPDG, delmPDG-2.5, delmPDG+2.5,
                          0.8, 0.4, 2.4,
                          0.2, 0, 10,
                          3, 1, 20);
    plotParams_delm="delm_sig_mu,delm_sig_sigma,delm_sig_alpha,delm_sig_n";
  }
  else if (strcmp(delmSigType,"dblGauss")==0) {
    // double Gaussian signal (common mean)
    fitter->MakeDelmSigBiGauss(delmPDG, delmPDG-2.5, delmPDG+2.5,
                               0.8, 0.4, 2.4,
                               1.5, 1, 3,
                               0.85);
    plotParams_delm="delm_sig_mu,delm_sig_sigma0,delm_sig_sigma1";
  }
  else if (strcmp(delmSigType,"cruijff")==0) {
    // single Cruijff
    fitter->MakeDelmSigCruijff(delmPDG, delmPDG-2.5, delmPDG+2.5,
                               0.8, 0.4, 2.4,
                               0.8, 0.4, 2.4,
                               0.2, 0, 10,
                               0.2, 0, 10);
    plotParams_delm="delm_sig_mu,delm_sig_sigmaL,delm_sig_sigmaR,delm_sig_alphaL,delm_sig_alphaR";
  }
  else if (strcmp(delmSigType,"cruijffSimple")==0) {
    // single Cruijff (common mean)
    fitter->MakeDelmSigCruijff(delmPDG, delmPDG-2.5, delmPDG+2.5,
                               0.8, 0.4, 2.4,
                               0.2, 0, 10,
                               0.2, 0, 10);
    plotParams_delm="delm_sig_mu,delm_sig_sigma,delm_sig_alphaL,delm_sig_alphaR";
  }
  else {
    cout << "Unexpected Delta mass signal type " << delmSigType << endl;
    exit(1);
  }


  if (strcmp(delmBkgType,"DstD0BG")==0) {
    fitter->MakeDelmBkgDstD0BG(piPDG, piPDG-3, piPDG+3,//dm0 (threshold)
                               1.0, 0.0, 10.0, //c (exponent)
                               2.0, 0.0, 10.0, //a (power)
                               5.0, -10.0, 10.0 //b (linear)
                               );
    plotParams_delm+=",delm_bkg_dm0,delm_bkg_c,delm_bkg_a,delm_bkg_b";
  }
  else if (strcmp(delmBkgType,"DstD0BGFixedThreshold")==0) {
    fitter->MakeDelmBkgDstD0BG(piPDG,//dm0
                               1.0, 0.0, 10.0, //c (exponent)
                               2.0, 0.0, 10.0, //a (power)
                               5.0, -10.0, 10.0 //b (linear)
                               );
    plotParams_delm+=",delm_bkg_dm0,delm_bkg_c,delm_bkg_a,delm_bkg_b";
  }
  else if (strcmp(delmBkgType,"Granet")==0) {
    fitter->MakeDelmBkgGranet(piPDG, piPDG-3, piPDG+3,//dm0 (threshold)
                              0.1, 0.0, 1.0, //a (exponent)
                              2.0, 0.0, 10.0 //b (power)
                              );
    plotParams_delm+=",delm_bkg_dm0,delm_bkg_a,delm_bkg_b";
  }
  else if (strcmp(delmBkgType,"GranetFixedThreshold")==0) {
    fitter->MakeDelmBkgGranet(piPDG,//dm0 (threshold)
                              0.1, 0.0, 1.0, //a (exponent)
                              2.0, 0.0, 10.0 //b (power)
                              );
    plotParams_delm+=",delm_bkg_dm0,delm_bkg_a,delm_bkg_b";
  }
  else if (strcmp(delmBkgType, "TwoBodyPhsp")==0) {
    fitter->MakeDelmBkgTwoBodyPhsp(-0.1,-10.0,10.0, // 1st-order coefficient
		                   -0.1,-10.0,10.0 // 2nd-order coefficient
                                  );
    plotParams_delm+=",delm_bkg_c1,delm_bkg_c2";
  }
  else {
    cout << "Unexpected Delta mass bkg. type " << delmBkgType << endl;
    exit(1);
  }

  // arguments:
  // 1) signal fraction
  // 2) combinatoric background fraction
  // 3) random pion background fraction
  // 4) "fake D0" background (unphysical)
  fitter->MakeDelmModel(0.4, 0.6, 0.2, -1.0);
 
  // set the plot attributes
  cout << "Setting plot attributes" << endl;
  fitter->AddPdfComponent("sig2DModel", kRed, kDashed, 3);
  fitter->AddPdfComponent("combBkg2DModel", kGreen+3, kDotted, 3);
  fitter->AddPdfComponent("piBkg2DModel", kOrange+3, kDashed, 3);

  // set the parameters
  cout << "Setting plot parameters" << endl;
  fitter->SetPlotBins(100);
  fitter->SetPlotBins("mass",100);
  fitter->SetPlotBins("delm",100);
  fitter->SetParamBoxX1(0.6);
  fitter->SetParamBoxY1(0.45);
  fitter->SetParamBoxY2(0.9);
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
  
  // create weighted data set for signal sWeight
  // arguments: 
  // 1) name of data set with weights;
  // 2) name of sWeight variable;
  // 3) fit name ("fitResults");
  // 4) save to workspace? (true).
  cout << "Creating signal sWeighted data set" << endl;
  fitter->CreateWeightedDataSet("data_sig", "nsig_sw", "fitRes");
  
  // create weighted data set for random slow pion bkg sWeight
  // arguments: 
  // 1) name of data set with weights;
  // 2) name of sWeight variable;
  // 3) fit name ("fitResults");
  // 4) save to workspace? (true).
  cout << "Creating random piob bkg. sWeighted data set" << endl;
  fitter->CreateWeightedDataSet("data_rand", "nbkg_randPi_sw", "fitRes");
  
  // create weighted data set for combinatoric bkg sWeight
  // arguments: 
  // 1) name of data set with weights;
  // 2) name of sWeight variable;
  // 3) fit name ("fitResults");
  // 4) save to workspace? (true).
  cout << "Creating combinatoric bkg. sWeighted data set" << endl;
  fitter->CreateWeightedDataSet("data_bkg", "nbkg_comb_sw", "fitRes");

  RooRealVar* mass=fitter->GetVar("mass");
  mass->setRange("sigRange",d0MassPDG-40,d0MassPDG+30);
  RooRealVar* delm=fitter->GetVar("delm");
  delm->setRange("sigRange",delmPDG-2.3,delmPDG+2.3);

  // plot the fit results
  // arguments: 
  // 1) variable name;
  // 2) fit name ("fitResults");
  // 3) range ("");
  // 4) range title ("");
  // 5) use sum-of-weights^2 errors? (false)
  cout << "Plotting fit results" << endl;
  TString rangeTitle="sigRegion";
  fitter->SetPlotParameters(plotParams_d0.Data());
  RooPlot* rp_mass = fitter->PlotFitResults("mass", "fitRes", "sigRange",
                                            rangeTitle.Data());
  rp_mass->SetTitleOffset(0.8, "Y");
  rp_mass->Print();
  
  // make the pull plot
  // arguments:
  // 1) variable name;
  // 2) fit name ("fitResults");
  RooPlot* rp_mass_pull = fitter->PlotFitPulls("mass", "fitRes");
  rp_mass_pull->SetTitle(";;");
  rp_mass_pull->SetLabelSize(0.12, "X");
  rp_mass_pull->SetLabelSize(0.12, "Y");
  
  TCanvas* c1 = new TCanvas("c1", "Fit Results (m_{D^{0}})", 800, 600);
  TPad* c1_upper = new TPad("cnv_mass_upper", "", 0.005, 0.30, 0.995, 0.995);
  TPad* c1_lower = new TPad("cnv_mass_lower", "", 0.005, 0.05, 0.995, 0.295);
  c1_upper->Draw();
  c1_lower->Draw();
  c1_upper->cd();
  rp_mass->Draw();
  c1_lower->cd();
  rp_mass_pull->Draw();
  
  c1->SaveAs(TString::Format("fitResults_d0Mass_%s_%s_%s_%s.eps",
                             d0SigType, d0BkgType, delmSigType, delmBkgType).Data());


  fitter->SetPlotParameters(plotParams_delm.Data());
  RooPlot* rp_delm = fitter->PlotFitResults("delm", "fitRes", "sigRange",
                                            rangeTitle.Data());
  rp_delm->SetTitleOffset(0.8, "Y");
 
  // make the pull plot
  // arguments:
  // 1) variable name;
  // 2) fit name ("fitResults");
  RooPlot* rp_delm_pull = fitter->PlotFitPulls("delm", "fitRes");
  rp_delm_pull->SetTitle(";;");
  rp_delm_pull->SetLabelSize(0.12, "X");
  rp_delm_pull->SetLabelSize(0.12, "Y");
  
  TCanvas* c2 = new TCanvas("c2", "Fit Results (#Delta_{m})", 800, 600);
  TPad* c2_upper = new TPad("cnv_mass_upper", "", 0.005, 0.30, 0.995, 0.995);
  TPad* c2_lower = new TPad("cnv_mass_lower", "", 0.005, 0.05, 0.995, 0.295);
  c2_upper->Draw();
  c2_lower->Draw();
  c2_upper->cd();
  rp_delm->Draw();
  c2_lower->cd();
  rp_delm_pull->Draw();
  
  c2->SaveAs(TString::Format("fitResults_delm_%s_%s_%s_%s.eps",
                             d0SigType, d0BkgType, delmSigType, delmBkgType).Data());

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

  // plot the signal sWeighted dataset
  fitter->SetDataSetName("data_sig");
  fitter->SetDataSetLineColor(kRed);
  fitter->SetDataSetMarkerColor(kRed);
  fitter->SetDataSetMarkerStyle(kFullTriangleDown);
  fitter->PlotVariable("exampleVar", "", "", kTRUE, rp_var);

  // plot the random pion sWeighted dataset
  fitter->SetDataSetName("data_rand");
  fitter->SetDataSetLineColor(kOrange+3);
  fitter->SetDataSetMarkerColor(kOrange+3);
  fitter->SetDataSetMarkerStyle(kFullTriangleDown);
  fitter->PlotVariable("exampleVar", "", "", kTRUE, rp_var);
  
  // plot the background sWeighted dataset
  fitter->SetDataSetName("data_bkg");
  fitter->SetDataSetLineColor(kGreen+3);
  fitter->SetDataSetMarkerColor(kGreen+3);
  fitter->SetDataSetMarkerStyle(kFullTriangleDown);
  fitter->PlotVariable("exampleVar", "", "", kTRUE, rp_var);

  // plot the associated signal events
  fitter->SetDataSetName("data");
  fitter->SetDataSetLineColor(kMagenta);
  fitter->SetDataSetMarkerColor(kMagenta);
  fitter->SetDataSetMarkerStyle(kOpenCircle);
  fitter->PlotVariable("exampleVar",
                       "bkgCat==bkgCat::Signal",
                       "", kFALSE, rp_var);
  
  // plot the associated random slow pion events
  fitter->SetDataSetName("data");
  fitter->SetDataSetLineColor(kOrange);
  fitter->SetDataSetMarkerColor(kOrange);
  fitter->SetDataSetMarkerStyle(kOpenCircle);
  fitter->PlotVariable("exampleVar",
                       "bkgCat==bkgCat::RandomPion",
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
  c3->SaveAs(TString::Format("exampleVar_%s_%s_%s_%s.eps",
                             d0SigType, d0BkgType, delmSigType, delmBkgType).Data());
  
  cout << "Saving workspace" << endl;
  fitter->SaveWS();
  cout << "Example completed!" << endl;

  delete f;
  delete fitter;
  delete c1;
  delete c2;
  delete c3;
  delete rp_mass;
  delete rp_delm;
  delete rp_var;
}

void RooDstarD0MassFitter_Ex1()
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
 
  vector<TString> d0SigTypes;
//   d0SigTypes.push_back("gauss");
//   d0SigTypes.push_back("dblGauss");
//   d0SigTypes.push_back("cb");
//   d0SigTypes.push_back("cruijff");
  d0SigTypes.push_back("cruijffSimple");

  vector<TString> d0BkgTypes;
  d0BkgTypes.push_back("linear");
  //d0BkgTypes.push_back("quadratic");

  vector<TString> delmSigTypes;
  //   delmSigTypes.push_back("gauss");
  //   delmSigTypes.push_back("dblGauss");
  //   delmSigTypes.push_back("cb");
  //   delmSigTypes.push_back("cruijff");
  delmSigTypes.push_back("cruijffSimple");

  vector<TString> delmBkgTypes;
  //delmBkgTypes.push_back("DstD0BG");
  //   delmBkgTypes.push_back("DstD0BGFixedThreshold");
  delmBkgTypes.push_back("Granet");
  delmBkgTypes.push_back("TwoBodyPhsp");
  //   delmBkgTypes.push_back("GranetFixedThreshold");

  for (vector<TString>::iterator d0SigType=d0SigTypes.begin();
       d0SigType!=d0SigTypes.end(); ++d0SigType) {
    for (vector<TString>::iterator d0BkgType=d0BkgTypes.begin();
         d0BkgType!=d0BkgTypes.end(); ++d0BkgType) {
      for (vector<TString>::iterator delmSigType=delmSigTypes.begin();
           delmSigType!=delmSigTypes.end(); ++delmSigType) {
        for (vector<TString>::iterator delmBkgType=delmBkgTypes.begin();
             delmBkgType!=delmBkgTypes.end(); ++delmBkgType) {
    
          MakeFit(d0SigType->Data(),d0BkgType->Data(),
                  delmSigType->Data(),delmBkgType->Data());
        }
      }
    }
  }
  exit(0);
} 

