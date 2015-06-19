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

/* example of how to use RooDMassFitter to fit a (toy) dataset, construct
sWeights, and plot the results
*/
// #include <boost/assign/list_of.hpp>
// using namespace std;

Float_t d0MassPDG=1864.83;
Float_t delmPDG=145.421;
Float_t piPDG=139.57018;

void MakeFit(const char* d0SigType, const char* d0BkgType, const char* delmSigType, const char* delmBkgType) 
{
  TFile* f = TFile::Open("/data/lhcb/users/hunt/data/offline/MC10/D02K3PiForXS/noPID/offline/tagged/D02K3PiForXSec.root", 
                         "READ");
  TTree* tt = (TTree*)gDirectory->Get("TaggedD02K3Pi");
  
  RooDstarD0MassFitter* fitter = new RooDstarD0MassFitter(TString::Format("Fitter_%s_%s_%s_%s",
                                                                          d0SigType,d0BkgType,delmSigType,delmBkgType).Data(),
                                                          "An example fitter");

  cout << "Creating workspace instance" << endl;
  fitter->CreateWS("RWS","");
  
  cout << "Attach output file" << endl;
  fitter->AttachFile(TString::Format("output_%s_%s_%s_%s.root",d0SigType,d0BkgType,delmSigType,delmBkgType).Data(), "RECREATE");

  // create the fitter object
  cout << "*******************************************************************************" << endl;
  cout << "Performing fits for D0 signal type = " << d0SigType 
       << ", D0 bkg. type = " << d0BkgType
       << ", Delta mass signal type = " << delmSigType
       << ", Delta mass bkg. type = " << delmBkgType << endl;

  
  cout << "Setting parameter names" << endl;

 //  fitter->SetDMassPartName("D^{0}");
//   fitter->SetDMassName("mass");
//   fitter->SetDelmPartName("#Delta_{m}");
//   fitter->SetDelmName("delm");

//   fitter->SetDMassSigModelName("d0SigModel");
//   fitter->SetDMassBkgModelName("d0BkgModel");
//   fitter->SetDelmSigModelName("delmSigModel");
//   fitter->SetDelmBkgModelName("delmBkgModel");

//   fitter->Set2DMassSigModelName("sigModel");
//   fitter->Set2DMassCombBkgModelName("combBkgModel");
//   fitter->Set2DMassRandPiBkgModelName("randPiBkgModel");
//   fitter->Set2DMassFakeD0BkgModelName("fakeD0BkgModel");

//   fitter->SetModelName("model");
//   fitter->SetSWeightSetName("SWeights");
//   fitter->SetPlotParameterSetName("PlotParams");
//   fitter->SetSpectatorSetName("Spectators");
//   fitter->SetCategorySetName("Categories");

  cout << "Create D0 mass variable" << endl;
  fitter->MakeDMassVar(d0MassPDG-70,d0MassPDG+70,"MeV/c^{2}", 
                       "m_{K#pi#pi#pi}");
  cout << "Create Delta mass variable" << endl;
  fitter->MakeDelmVar(delmPDG-5.5,delmPDG+10,"MeV/c^{2}", 
                      "m_{K#pi#pi#pi#pi_{s}}-m_{K#pi#pi#pi}");

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
  fitter->AddCategory("promptCat", types, indices, "Dstar_MC_ISPROMPT");
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
  fitter->AddCategory("bkgCat", types, indices, "Dstar_BKGCAT");

  cout << "Making data set" << endl;
  fitter->MakeDelmDataSet(tt, "D0_M", "Dstar_M", "data");

  TString plotParams_d0="";
  TString plotParams_delm="";

  cout << "Making D0 signal model" << endl;
  if (strcmp(d0SigType,"gauss")==0) {
    // single Gaussian signal, quadratic background
    fitter->MakeDMassSigGauss(d0MassPDG, d0MassPDG-25, d0MassPDG+25, 
                              8, 4, 24);
    plotParams_d0="dmass_sig_mu,dmass_sig_sigma";
  }
  else if (strcmp(d0SigType,"cb")==0) {
    // single CB, quadratic background
    fitter->MakeDMassSigCB(d0MassPDG, d0MassPDG-25, d0MassPDG+25,
                           8, 4, 24,
                           0.2, 0, 10,
                           3, 1, 20);
    plotParams_d0="dmass_sig_mu,dmass_sig_sigma,dmass_sig_alpha,dmass_sig_n";
  }
  else if (strcmp(d0SigType,"dblGauss")==0) {
    // double Gaussian signal, quadratic background
    fitter->MakeDMassSigBiGauss(d0MassPDG, d0MassPDG-25, d0MassPDG+25,
                                d0MassPDG, d0MassPDG-25, d0MassPDG+25,
                                8, 4, 24,
                                1.5, 1, 3,
                                0.85);    
    plotParams_d0="dmass_sig_mu0,dmass_sig_sigma0,dmass_sig_mu1,dmass_sig_sigma1";
  }
  else if (strcmp(d0SigType,"dblGaussSimple")==0) {
    // double Gaussian signal (common mean), quadratic background
    fitter->MakeDMassSigBiGauss(d0MassPDG, d0MassPDG-25, d0MassPDG+25,
                                8, 4, 24,
                                1.5, 1, 3,
                                0.85);
    plotParams_d0="dmass_sig_mu,dmass_sig_sigma0,dmass_sig_sigma1";
  }
  else if (strcmp(d0SigType,"cruijff")==0) {
    // single Cruijff, quadratic background
    fitter->MakeDMassSigCruijff(d0MassPDG, d0MassPDG-25, d0MassPDG+25,
                                8, 4, 24,
                                8, 4, 24,
                                0.2, 0, 10, 
                                0.2, 0, 10);
    plotParams_d0="dmass_sig_mu,dmass_sig_sigmaL,dmass_sig_sigmaR,dmass_sig_alphaL,dmass_sig_alphaR";
  }
  else if (strcmp(d0SigType,"cruijffSimple")==0) {
    // single Cruijff (common mean), quadratic background
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
    // single Gaussian signal, quadratic background
    fitter->MakeDelmSigGauss(delmPDG, delmPDG-2.5, delmPDG+2.5,
                             0.8, 0.4, 2.4);
    plotParams_delm="delm_sig_mu,delm_sig_sigma";
  }
  else if (strcmp(delmSigType,"cb")==0) {
    // single CB, quadratic background
    fitter->MakeDelmSigCB(delmPDG, delmPDG-2.5, delmPDG+2.5,
                          0.8, 0.4, 2.4,
                          0.2, 0, 10,
                          3, 1, 20);
    plotParams_delm="delm_sig_mu,delm_sig_sigma,delm_sig_alpha,delm_sig_n";
  }
  else if (strcmp(delmSigType,"dblGauss")==0) {
    // double Gaussian signal, quadratic background
    fitter->MakeDelmSigBiGauss(delmPDG, delmPDG-2.5, delmPDG+2.5,
                               delmPDG, delmPDG-2.5, delmPDG+2.5,
                               0.8, 0.4, 2.4,
                               1.5, 1,3,
                               0.85);  
    plotParams_delm="delm_sig_mu0,delm_sig_sigma0,delm_sig_mu1,delm_sig_sigma1";
  }
  else if (strcmp(delmSigType,"dblGaussSimple")==0) {
    // double Gaussian signal (common mean), quadratic background
    fitter->MakeDelmSigBiGauss(delmPDG, delmPDG-2.5, delmPDG+2.5,
                               0.8, 0.4, 2.4,
                               1.5, 1, 3,
                               0.85);
    plotParams_delm="delm_sig_mu,delm_sig_sigma0,delm_sig_sigma1";
  }
  else if (strcmp(delmSigType,"cruijff")==0) {
    // single Cruijff, quadratic background
    fitter->MakeDelmSigCruijff(delmPDG, delmPDG-2.5, delmPDG+2.5,
                               0.8, 0.4, 2.4,
                               0.8, 0.4, 2.4,
                               0.2, 0, 10,
                               0.2, 0, 10);
    plotParams_delm="delm_sig_mu,delm_sig_sigmaL,delm_sig_sigmaR,delm_sig_alphaL,delm_sig_alphaR";
  }
  else if (strcmp(delmSigType,"cruijffSimple")==0) {
    // single Cruijff (common mean), quadratic background
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
  else {
    cout << "Unexpected Delta mass bkg. type " << delmBkgType << endl;
    exit(1);
  }

  
  fitter->MakeDelmModel(0.2,0.6,0.15,0.05);
 
  // set the plot attributes
  cout << "Setting plot attributes" << endl;
  fitter->AddPdfComponent("sig2DModel", kRed, kDashed, 3);
  fitter->AddPdfComponent("combBkg2DModel", kGreen, kDotted, 3);
  fitter->AddPdfComponent("randPiBkg2DModel", kMagenta, kDashed, 3);
  fitter->AddPdfComponent("d0Bkg2DModel", kOrange+2, 7, 3);

  // set the chi^2 test statistic
  cout << "Setting test statistic" << endl;
  fitter->SetChi2TestStat(RooPhysFitter::LLRatio);
  
  // set the bins
  cout << "Setting plot parameters" << endl;
  fitter->SetPlotBins(100);
  fitter->SetChi2Bins(100);
  fitter->SetPlotBins("mass",100);
  fitter->SetPlotBins("delm",100);
  fitter->SetChi2Bins("mass",50);
  fitter->SetChi2Bins("delm",50);
  fitter->SetParamBoxY1(0.5);
  fitter->SetParamBoxX1(0.62);
  fitter->SetParamBoxTextSize(0.022);

  cout << "Performing fit" << endl;
  fitter->PerformFit("fitRes", 6, kTRUE, kTRUE, kFALSE, kTRUE);
  
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
 //  // name of sWeight variable, save to workspace (true)
//   cout << "Creating bkg. sWeighted data set" << endl;
//   fitter->CreateWeightedDataSet("data_bkg", "nbkg_sw", "fitRes");

//   cout << "Created signal (MC associated) data set" << endl;
//   fitter->CreateReducedDataSet("data_sig_mc", "bkgCat==bkgCat::sig||bkgCat==bkgCat::quasisig");

  RooRealVar* mass=fitter->GetVar("mass");
  mass->setRange("sigRange",d0MassPDG-40,d0MassPDG+30);
  RooRealVar* delm=fitter->GetVar("delm");
  delm->setRange("sigRange",delmPDG-2.3,delmPDG+2.3);

  cout << "Plotting fit results" << endl;
  TString rangeTitle="sigRegion";//"[-30,40],[-2.3,2.3]";

  fitter->SetPlotParameters(plotParams_d0.Data());
  RooPlot* rp_mass = fitter->PlotFitResults("mass", "fitRes", "sigRange",
                                            rangeTitle.Data());
  TCanvas* c1 = new TCanvas("c1", "Fit Results (m_{D^{0}})",1280, 1024);
  rp_mass->Draw();
  c1->SaveAs(TString::Format("fitResults_d0Mass_%s_%s_%s_%s.eps",
                             d0SigType, d0BkgType, delmSigType, delmBkgType).Data());


  fitter->SetPlotParameters(plotParams_delm.Data());
  RooPlot* rp_delm = fitter->PlotFitResults("delm", "fitRes", "sigRange",
                                            rangeTitle.Data());

  TCanvas* c2 = new TCanvas("c2", "Fit Results (#Delta_{m})",1280, 1024);
  rp_delm->Draw();
  c2->SaveAs(TString::Format("fitResults_delm_%s_%s_%s_%s.eps",
                             d0SigType, d0BkgType, delmSigType, delmBkgType).Data());


//   cout << "Performing fit to MC signal" << endl;
// //   fitter->SetDataSetName("data_sig_mc");
// //   fitter->SetModelName("sigOnlyModel");
//   fitter->PerformFit("fitRes", 4, kTRUE, kTRUE, kFALSE, kTRUE);
  
//   cout << "Plotting fit results for MC signal" << endl;
//   TString rangeTitle="[-30,40 MeV/c^{2}]";
//   RooPlot* rp_mc = fitter->PlotFitResults("mass", "fitRes", "sigRange",
//                                           rangeTitle.Data());
//   TCanvas* c2 = new TCanvas("c2", "Fit Results (MC signal)",1280, 1024);
//   rp_mc->Draw();
//   c2->SaveAs(TString::Format("fitResults_MCSignal_%s.eps", sigType).Data());

  fitter->SetModelName("model");

  cout << "Plotting variable 'pt'" << endl;
  RooPlot* rp_var = fitter->PlotVariable("pt");

  fitter->SetDataSetName("data_sig");
  fitter->SetDataSetLineColor(kRed);
  fitter->SetDataSetMarkerColor(kRed);
  fitter->PlotVariable("pt", "", "", kTRUE, rp_var);

 //  fitter->SetDataSetName("data_bkg");
//   fitter->SetDataSetLineColor(kBlue);
//   fitter->SetDataSetMarkerColor(kBlue);
//   fitter->PlotVariable("pt", "", "", kTRUE, rp_var);

  fitter->SetDataSetName("data");
  fitter->SetDataSetLineColor(kMagenta);
  fitter->SetDataSetMarkerColor(kMagenta);
  fitter->PlotVariable("pt",
                       "bkgCat==bkgCat::sig||bkgCat==bkgCat::quasisig",
                       "", kFALSE, rp_var);

 //  fitter->SetDataSetLineColor(kCyan+2);
//   fitter->SetDataSetMarkerColor(kCyan+2);
//   fitter->PlotVariable("pt",
//                        "bkgCat!=bkgCat::sig&&bkgCat!=bkgCat::quasisig",
//                        "", kFALSE, rp_var);
  TCanvas* c3 = new TCanvas("c3", "pt Variable",1280, 1024);
  rp_var->Draw();
  c3->SaveAs(TString::Format("pt_%s_%s_%s_%s.eps", 
                             d0SigType, d0BkgType, delmSigType, delmBkgType).Data());

  cout << "Saving workspace" << endl;
  fitter->SaveWS();
  cout << "Example completed!" << endl;

  delete f;
  delete fitter;
  delete c1;
  delete c2;
  delete c3;
}

void RooDstarD0MassFitter_Ex1()
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

  vector<TString> d0SigTypes;
//   d0SigTypes.push_back("gauss");
//   d0SigTypes.push_back("dblGauss");
//   d0SigTypes.push_back("dblGaussSimple");
//   d0SigTypes.push_back("cb");
//   d0SigTypes.push_back("cruijff");
  d0SigTypes.push_back("cruijffSimple");

  vector<TString> d0BkgTypes;
//   d0BkgTypes.push_back("linear");
  d0BkgTypes.push_back("quadratic");

  vector<TString> delmSigTypes;
//   delmSigTypes.push_back("gauss");
//   delmSigTypes.push_back("dblGauss");
//   delmSigTypes.push_back("dblGaussSimple");
//   delmSigTypes.push_back("cb");
//   delmSigTypes.push_back("cruijff");
  delmSigTypes.push_back("cruijffSimple");

  vector<TString> delmBkgTypes;
  delmBkgTypes.push_back("DstD0BG");
//   delmBkgTypes.push_back("DstD0BGFixedThreshold");
  delmBkgTypes.push_back("Granet");
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

