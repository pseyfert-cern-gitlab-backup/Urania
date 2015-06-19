Float_t d0MassPDG=1864.83;


void MakeFit(const char* sigType) 
{
  TFile* f = TFile::Open("/data/lhcb/users/hunt/data/offline/MC10/D02K3PiForXS/noPID/offline/untagged/D02K3PiForXSec.root", 
                         "READ");
  TTree* tt = (TTree*)gDirectory->Get("UntaggedD02K3Pi");
  
  RooDMassFitter* fitter = new RooDMassFitter(TString::Format("Fitter_%s",sigType).Data(),
                                              "An example fitter");

  cout << "Creating workspace instance" << endl;
  fitter->CreateWS("RWS","");
  
  cout << "Attach output file" << endl;
  fitter->AttachFile(TString::Format("output_%s.root",sigType).Data(), "RECREATE");

  // create the fitter object
  cout << "*******************************************************************************" << endl;
  cout << "Performing fits for signal type " << sigType << endl;

  
  cout << "Setting parameter names" << endl;
  fitter->SetDMassPartName("D^{0}");
  fitter->SetDMassName("mass");
  fitter->SetDMassSigModelName("sigModel");
  fitter->SetDMassBkgModelName("bkgModel");
  fitter->SetModelName("model");
  fitter->SetSWeightSetName("SWeights");
  fitter->SetPlotParameterSetName("PlotParams");
  fitter->SetSpectatorSetName("Spectators");
  fitter->SetCategorySetName("Categories");

  cout << "Create D0 mass variable" << endl;
  fitter->MakeDMassVar(d0MassPDG-70,d0MassPDG+70,"MeV/c^{2}", 
                       "m_{K#pi#pi#pi}");
  
  cout << "Add spectators" << endl;
  fitter->AddSpectator("logIPChi2", -8,10,std::log,"D0_IPCHI2_BPV", ""
                       "log(D^{0} IP #chi^{2}");
  fitter->AddSpectator("pt", 0,10000,"D0_PT", "MeV/c^{2}", "D^{0} p_{T}");

  cout << "Add categories" << endl;
  vector<std::string> types;
  types.push_back("undefined");
  types.push_back("secondary");
  types.push_back("prompt");
  vector<Int_t> indices;
  indices.push_back(-1);
  indices.push_back(0);
  indices.push_back(1);
  fitter->AddCategory("promptCat", types, indices, "D0_MC_ISPROMPT");
  types.clear();
  indices.clear();
  types.push_back("sig");
  types.push_back("quasisig");
  types.push_back("fullreco");
  types.push_back("reflection");
  types.push_back("partreco");
  types.push_back("lowmass");
  types.push_back("ghost");
  types.push_back("clone");
  types.push_back("hierarchy");
  types.push_back("fromPV");
  types.push_back("samePV");
  types.push_back("diffPV");
  types.push_back("bbar");
  types.push_back("ccbar");
  types.push_back("uds");
  vector<Int_t> indices;
  indices.push_back(0);
  indices.push_back(10);
  indices.push_back(20);
  indices.push_back(30);
  indices.push_back(40);
  indices.push_back(50);
  indices.push_back(60);
  indices.push_back(63);
  indices.push_back(66);
  indices.push_back(70);
  indices.push_back(80);
  indices.push_back(100);
  indices.push_back(110);
  indices.push_back(120);
  indices.push_back(130);
  fitter->AddCategory("bkgCat", types, indices, "D0_BKGCAT");

  cout << "Making data set" << endl;
  fitter->MakeDMassDataSet(tt, "D0_M", "data");

  // quadratic combinatoric D0 background
  fitter->MakeDMassBkgQuadratic(0,-1,1, 0, -1, 1);

  cout << "Making model" << endl;
  if (strcmp(sigType,"gauss")==0) {
    // single Gaussian signal, quadratic background
    fitter->MakeDMassSigGauss(d0MassPDG,d0MassPDG-25,d0MassPDG+25,8,4,24);
    fitter->SetPlotParameters("dmass_sig_mu,dmass_sig_sigma,dmass_bkg_poly_c1,dmass_bkg_poly_c2");
  }
  else if (strcmp(sigType,"cb")==0) {
    // single CB, quadratic background
    fitter->MakeDMassSigCB(d0MassPDG,d0MassPDG-25,d0MassPDG+25,8,4,24,0.2,0,10,3,1,20);
    TString plotParams="dmass_sig_mu,dmass_sig_sigma,dmass_sig_alpha";
    plotParams+=",dmass_sig_n,dmass_bkg_poly_c1,dmass_bkg_poly_c2";
    fitter->SetPlotParameters(plotParams.Data());
  }
  else if (strcmp(sigType,"dblGauss")==0) {
    // double Gaussian signal, quadratic background
    fitter->MakeDMassSigBiGauss(d0MassPDG,d0MassPDG-25,d0MassPDG+25,
                                d0MassPDG,d0MassPDG-25,d0MassPDG+25,
                                8,4,24, 1.5,1,3,0.85);
    TString plotParams="dmass_sig_mu0,dmass_sig_sigma0,dmass_sig_mu1,dmass_sig_sigma1";
    plotParams+=",dmass_bkg_poly_c1,dmass_bkg_poly_c2";
    fitter->SetPlotParameters(plotParams.Data());
  }
  else if (strcmp(sigType,"dblGaussSimple")==0) {
    // double Gaussian signal (common mean), quadratic background
    fitter->MakeDMassSigBiGauss(d0MassPDG,d0MassPDG-25,d0MassPDG+25,
                                8,4,24, 1.5,1,3,0.85);
    TString plotParams="dmass_sig_mu,dmass_sig_sigma0,dmass_sig_sigma1";
    plotParams+=",dmass_bkg_poly_c1,dmass_bkg_poly_c2";
    fitter->SetPlotParameters(plotParams.Data());
  }
  else if (strcmp(sigType,"cruijff")==0) {
    // single Cruijff, quadratic background
    fitter->MakeDMassSigCruijff(d0MassPDG,d0MassPDG-25,d0MassPDG+25,
                                8,4,24, 8,4,24, 0.2, 0, 10, 0.2, 0, 10);
    TString plotParams="dmass_sig_mu,dmass_sig_sigmaL,dmass_sig_sigmaR,dmass_sig_alphaL,dmass_sig_alphaR";
    plotParams+=",dmass_bkg_poly_c1,dmass_bkg_poly_c2";
    fitter->SetPlotParameters(plotParams.Data());
  }
  else if (strcmp(sigType,"cruijffSimple")==0) {
    // single Cruijff (common mean), quadratic background
    fitter->MakeDMassSigCruijff(d0MassPDG,d0MassPDG-25,d0MassPDG+25,
                                8,4,24, 0.2, 0, 10, 0.2, 0, 10);
    TString plotParams="dmass_sig_mu,dmass_sig_sigma,dmass_sig_alphaL,dmass_sig_alphaR";
    plotParams+=",dmass_bkg_poly_c1,dmass_bkg_poly_c2";
    fitter->SetPlotParameters(plotParams.Data());
  } 
  else {
    cout << "Unexpected signal type " << sigType << endl;
    exit(1);
  }

  fitter->MakeDMassModel(0.3,0.7);
 
  // set the plot attributes
  cout << "Setting plot attributes" << endl;
  fitter->AddPdfComponent("sigModel", kRed, kDashed, 3);
  fitter->AddPdfComponent("bkgModel", kMagenta, kDotted, 3);

  // set the chi^2 test statistic
  cout << "Setting test statistic" << endl;
  fitter->SetChi2TestStat(RooPhysFitter::LLRatio);
  
  // set the bins
  cout << "Setting plot parameters" << endl;
  fitter->SetPlotBins(100);
  fitter->SetChi2Bins(300);
  fitter->SetParamBoxY1(0.55);
  fitter->SetParamBoxTextSize(0.026);

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
  fitter->CreateWeightedDataSet("data_sig", "nsig_sw", "fitRes");
  
  // create weighted data set for bkg sWeight
  // arguments: name of data set with weights,
  // name of sWeight variable, save to workspace (true)
  cout << "Creating bkg. sWeighted data set" << endl;
  fitter->CreateWeightedDataSet("data_bkg", "nbkg_sw", "fitRes");

  cout << "Created signal (MC associated) data set" << endl;
  fitter->CreateReducedDataSet("data_sig_mc", "bkgCat==bkgCat::sig||bkgCat==bkgCat::quasisig");

  RooRealVar* mass=fitter->GetVar("mass");
  mass->setRange("sigRange",d0MassPDG-40,d0MassPDG+30);
  
  cout << "Plotting fit results" << endl;
  TString rangeTitle="sigRegion";
  RooPlot* rp = fitter->PlotFitResults("mass", "fitRes", "sigRange",
                                        rangeTitle.Data());
  TCanvas* c1 = new TCanvas("c1", "Fit Results",1280, 1024);
  rp->Draw();
  c1->SaveAs(TString::Format("fitResults_%s.eps", sigType).Data());

 
  RooPlot* rp_var = fitter->PlotVariable("pt");

  fitter->SetDataSetName("data_sig");
  fitter->SetDataSetLineColor(kRed);
  fitter->SetDataSetMarkerColor(kRed);
  fitter->PlotVariable("pt", "", "", kTRUE, rp_var);

  fitter->SetDataSetName("data");
  fitter->SetDataSetLineColor(kMagenta);
  fitter->SetDataSetMarkerColor(kMagenta);
  fitter->PlotVariable("pt",
                       "bkgCat==bkgCat::sig||bkgCat==bkgCat::quasisig",
                       "", kFALSE, rp_var);

  TCanvas* c2 = new TCanvas("c2", "pt Variable",1280, 1024);
  rp_var->Draw();
  c2->SaveAs(TString::Format("pt_%s.eps", sigType).Data());

  cout << "Saving workspace" << endl;
  fitter->SaveWS();
  cout << "Example completed!" << endl;

  delete f;
  delete fitter;
  delete c1;
  delete c2;
}

void RooDMassFitter_Ex1()
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

 //  MakeFit("gauss");
//   MakeFit("dblGauss");
//   MakeFit("dblGaussSimple");
//   MakeFit("cb");
//   MakeFit("cruijff");
  MakeFit("cruijffSimple");
}
