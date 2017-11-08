#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooKeysPdf.h"
#include "RooRealVar.h"
#include "RooStats/SPlot.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooCBShape.h"
#include "RooArgusBG.h"
#include "RooGaussian.h"
#include "RooPolynomial.h"
#include "RooExponential.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooAddition.h"
#include "RooProduct.h"
#include "TCanvas.h"
#include "RooAbsPdf.h"
#include "RooFit.h"
#include "RooFitResult.h"
#include "RooWorkspace.h"
#include "RooConstVar.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TCut.h"
#include "SemiDec.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TMath.h"
#include "RooHORNSdini.h"
#include "RooHILLdini.h"

// #################
// ##### INFO ######  
// This code does the splots of the Ds*Pi mass to get the photon efficiency
// ################# 

// use this order for safety on library loading
using namespace RooFit ;
using namespace RooStats ;

// see below for implementation
void AddModel(RooWorkspace*, float);
void AddData(RooWorkspace*, TString);
void DoSPlot(RooWorkspace*, float, TString);
void MakePlots(RooWorkspace*, TString);
float getEntries(TString);
RooDataSet loadPdf(TString);

double lowRange    = 5000.;
double highRange   = 5600.;

void fitPhotonEffDen(TString sample){

  // Create a new workspace to manage the project.
  RooWorkspace *wspace = new RooWorkspace("myWS");

  // add the signal and background models to the workspace.
  // Inside this function you will find a discription our model.
  float nentries = getEntries(sample);
  //float nentries = 100000;
  AddModel(wspace, nentries);
  
  // add data to the workspace
  AddData(wspace, sample);

  // inspect the workspace if you wish
  wspace->Print();

  // do sPlot.  
  // This wil make a new dataset with sWeights added for every event.
  DoSPlot(wspace, nentries, sample);

  // Make some plots showing the discriminating variable and 
  // the control variable after unfolding.
  MakePlots(wspace, sample);

  delete wspace;

}

//____________________________________
void AddModel(RooWorkspace *ws, float nentries){

  // Make models for signal and background 

  Double_t massLow, massHigh, massCentral;
  // set range of observable
  massLow     = 5363.;
  massHigh    = 5371.;
  massCentral = 5366.;

  // make a RooRealVar for the observables
  RooRealVar invMass("resMass", "resMass", lowRange, highRange, "MeV");

  /////////////////////////////////////////////
  // make 1-d model for signal including the invariant mass 
  std::cout << "make signal model" << std::endl;
  // mass model for signal Gaussian
  RooRealVar meanBs("meanBs", "signal mass", massCentral, massLow, massHigh);
  RooRealVar sigma("sigma", "Width of signal", 18.0, 14.0, 22.0);
  RooRealVar meanBd("meanBd", "meanBd", 5279.63);

  //RooRealVar m0("m0", "m0", 5250, 5230, 5260);
  //RooRealVar c("c", "c", 10., -60., 30.);
  //RooRealVar alpha1("alpha1", "alpha1", 0.8, 0., 3.0);
  //RooRealVar alpha2("alpha2", "alpha2", -0.8, -1.5, 0.);
  //RooRealVar n1 = RooRealVar("n1", "n1", 10., 0.2, 60.);
  //RooRealVar n2 = RooRealVar("n2", "n2", 10., 1.2, 60.);
  //RooCBShape BsDsPi("bsdspi", "signal CB", invMass, mean, sigma, alpha1, n1);
  //RooCBShape *sig2 = new RooCBShape("sig2", "signal CB", invMass, mean, sigma, alpha2, n2);
  //RooRealVar frac = RooRealVar("frac","frac",0.5,0.,1.);
  //RooCBShape *SigModel = new RooCBShape("sig", "signal CB", invMass, mean, sigma, alpha2, n2);
  
  // BsDsPi peak
  RooGaussian BsDsPi("bsdspi", "bsdspi", invMass, meanBs, sigma);
  // fraction of BdDsPi is 34 time smaller with the same shape. 
  // the factor 34 comes from the BR and the fd/fs
  RooGaussian BdDsPi("bddspi", "bddspi", invMass, meanBd, sigma);
  //RooRealVar fracBd("fracBd", "fracBd", (2.16/300)*4);
  RooRealVar fracBd("fracBd", "fracBd", (2.16/300)*4, 0.000, 0.2);
 
  // get the DsRho function from the RooKeysPdf
  //RooDataSet BsDsRhoDS = loadPdf("bsdsrho");
  //RooKeysPdf BsDsRho("bsdsrho", "bsdsrho", invMass, BsDsRhoDS, RooKeysPdf::MirrorBoth, 2);
  // get the DsRho function from HILL/HORN distributions
  RooRealVar a3("a3", "a3", 3129.14);
  RooRealVar b3("b3", "b3", 5223.64);
  RooRealVar csi3("csi3", "csi3", 1.);
  RooRealVar shift3("shift3", "shift3", 0.);
  RooRealVar sigma3("sigma3", "sigma3", 24.3);
  RooRealVar rsigma3("rsigma3", "ratio sigma 3", 1.);
  RooRealVar fsigma3("fsigma3", "fraction sigma 3", 1.);
  RooHORNSdini BsDsRhoHorn1("bsdsrhohorn1", "bsdsrhohorn1", invMass, a3, b3, csi3, shift3, sigma3, rsigma3, fsigma3);
  RooRealVar a4("a4", "a4", 2064.47);
  RooRealVar b4("b4", "b4", 5337.78);
  RooRealVar csi4("csi4", "csi4", 1.);
  RooRealVar shift4("shift4", "shift4", 1.);
  RooRealVar sigma4("sigma4", "sigma4",  57.18);
  RooRealVar rsigma4("rsigma4", "ratio sigma 4", 1.);
  RooRealVar fsigma4("fsigma4", "fraction sigma 4", 1.);
  RooHORNSdini BsDsRhoHorn2("bsdsrhohorn2", "bsdsrhohorn2", invMass, a4, b4, csi3, shift3, sigma4, rsigma3, fsigma3);
  RooRealVar fracHorn("fracHorn", "fracHorn", 0.95);
  RooAddPdf BsDsRho("bsdsrho", "bsdsrho", RooArgList(BsDsRhoHorn1, BsDsRhoHorn2), RooArgList(fracHorn));

  RooRealVar fracRho("fracRho", "fracRho", 0.15, 0., 0.7); 
  
  // get the BsDsstK function from the RooKeysPdf
  RooDataSet BsDsstKDS = loadPdf("bsdsstk");
  RooKeysPdf BsDsstK("bsdsstk", "bsdsstk", invMass, BsDsstKDS, RooKeysPdf::MirrorBoth, 2);
  RooRealVar fracDsstK("fracDsstK", "fracDsstK", 0.005);
  //RooRealVar fracDsstK("fracDsstK", "fracDsstK", 0.005, 0.0, 0.2);  

  // get the BsDsK function from the RooKeysPdf
  RooDataSet BsDsKDS = loadPdf("bsdsk");
  RooKeysPdf BsDsK("bsdsk", "bsdsk", invMass, BsDsKDS, RooKeysPdf::MirrorBoth, 2);
  RooRealVar fracDsK("fracDsK", "fracDsK", 0.01); 
  //RooRealVar fracDsK("fracDsK", "fracDsK", 0.01, 0., 0.1);
  
  // get the BsDsstRho function from the RooKeysPdf
  RooDataSet BsDsstRhoDS = loadPdf("bsdsstrho");
  RooKeysPdf BsDsstRho("bsdsstrho", "bsdsstrho", invMass, BsDsstRhoDS, RooKeysPdf::MirrorBoth, 2);
  RooRealVar fracDsstRho("fracDsstRho", "fracDsstRho", 0.04, 0.0, 0.3);

  // add all of them together
  RooAddPdf peaks("peaks", "peaks", RooArgList(BdDsPi, BsDsRho, BsDsstK, BsDsK, BsDsstRho, BsDsPi), 
                                    RooArgList(fracBd, fracRho, fracDsstK, fracDsK, fracDsstRho));
//  RooAddPdf peaks("peaks", "peaks", RooArgList(BsDsRho, BsDsstK, BsDsK, BsDsstRho, BsDsPi),
//                                    RooArgList(fracRho, fracDsstK, fracDsK, fracDsstRho)); 

  //RooAddPdf peaks("peaks", "peaks", RooArgList(BdDsPi,BsDsPi), RooArgList(fracBd));

  //RooRealVar c1("c1","c1",-1.0,-1.5,1.5) ;
  //RooRealVar c2("c2","c2",-0.1,-1,1) ;
  //RooRealVar c3("c3","c3",0.3,-1,1) ;
  //RooRealVar c4("c4","c4",-0.1,-1,1) ;
  
  // get the DsGPi function from the RooKeysPdf
  //RooDataSet BsDsstPiDS = loadPdf("bsdsstgpi");
  //RooKeysPdf BsDsstGPi("bsdsstgpi", "bsdsstgpi", invMass, BsDsstPiDS, RooKeysPdf::MirrorBoth, 2);
  // get the DsGPI from the HORN/HILL distribution
  RooRealVar a1("a1", "a1", 4946.46);
  RooRealVar b1("b1", "b1", 5219.33);
  RooRealVar csi1("csi1", "csi1", 0.077);
  RooRealVar shift1("shift1", "shift1", 0.);
  RooRealVar sigma1("sigma1", "sigma1", 8.50);
  RooRealVar rsigma1("rsigma1", "ratio sigma 1", 6.97);
  RooRealVar fsigma1("fsigma1", "fraction sigma 1", 0.05); 
  RooHILLdini BsDsstGPi("bsdsstgpi", "bsdsstgpi", invMass, a1, b1, csi1, shift1, sigma1, rsigma1, fsigma1);
  // get the BsDsstPi with Dsst->DsPi0 from the RooKeysPdf
  //RooDataSet BsDsstPi0PiDS = loadPdf("bsdsstpi0pi");
  //RooKeysPdf BsDsstPi0Pi("bsdsstpi0pi", "bsdsstpi0pi", invMass, BsDsstPi0PiDS, RooKeysPdf::MirrorBoth, 2);
  // get the DsPi0PI from the HORN/HILL distribution
  RooRealVar a2("a2", "a2", 5105.46);
  RooRealVar b2("b2", "b2", 5209.17);
  RooRealVar csi2("csi2", "csi2", 1.85);
  RooRealVar shift2("shift2", "shift2", 0.);
  RooRealVar sigma2("sigma2", "sigma2", 13.97);
  RooRealVar rsigma2("rsigma2", "ratio sigma 2", 4.92);
  RooRealVar fsigma2("fsigma2", "fraction sigma 2", 0.51);
  RooHORNSdini BsDsstPi0Pi("bsdsstpi0pi", "bsdsstpi0pi", invMass, a2, b2, csi2, shift2, sigma2, rsigma2, fsigma2);
  RooRealVar fracDsstPi0Pi("fracDsstPi0Pi", "fracDsstPi0Pi", 0.058); // fix to PDG BR 5.8 +/- 0.7 %  

  RooAddPdf SigModel("sig", "sig bsdsstgpi", RooArgList(BsDsstPi0Pi,BsDsstGPi), fracDsstPi0Pi);
  //RooChebychev *DsGPi = new RooChebychev("bsdsstpi", "bsdsstpi", invMass, RooArgSet(c1,c2,c3,c4));
  //RooArgusBG  *DsGPi = new RooArgusBG("bsdsstpi", "bsdsstpi", invMass, m0, c);
  RooRealVar fracexp("fracexp", "fracexp", 0.85, 0.1, 1.);
  //RooAddPdf *SigModel = new RooAddPdf("sig", "signal", RooArgList(*DsGPi,*BsDsPi),frac); 
  // make background model

  std::cout << "make background model" << std::endl;
  //RooRealVar a1("a1","a1",0.3,-1,1) ;
  //RooRealVar a2("a2","a2",-0.1,-1,1) ;
  RooRealVar slope("slope","slope",-0.003,-0.01,-0.0001) ;
  //RooChebychev *BkgModel = new RooChebychev("bkg","background", invMass, RooArgSet(a1,a2,a3));
  RooExponential exp("exp", "exponential", invMass, slope);
  RooAddPdf BkgModel("bkg", "background", RooArgList(exp, peaks), fracexp);  

  //////////////////////////////////////////////
  // combined model
  // These variables represent the number of signal or background events
  // They will be fitted.
  RooRealVar SigYield("SigYield","fitted yield for Signal", nentries*0.15, 0.05*nentries, 0.4*nentries) ;
  RooRealVar BkgYield("BkgYield","fitted yield for Background", nentries*0.85, 0.6*nentries, 0.95*nentries) ;
  SigYield.setError(sqrt(nentries));
  BkgYield.setError(sqrt(nentries));

  // now make the combined model
  std::cout << "make full model" << std::endl;
  RooAddPdf model("model","signal+background models", RooArgList(SigModel,BkgModel), RooArgList(SigYield,BkgYield));
  //RooAddPdf model("model","only background models", RooArgList(*BkgModel), RooArgList(BkgYield));

  // interesting for debugging and visualizing the model
  model.graphVizTree("fullModel.dot");
  std::cout << "import model" << std::endl;
  ws->import(model);

}

//____________________________________
void AddData(RooWorkspace *ws, TString sample){
  // Add data from nutples

  TChain *fChain;
  // use the ntuples that are cleaned in Ds
  if (sample == "RS"){
    fChain = new TChain("B2DsMuNuTuple/DecayTree");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_1_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_2_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_3_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_4_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_5_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_1_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_2_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_3_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_4_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_5_cut.root");
  } else if (sample == "SS"){
    fChain = new TChain("B2DsMuNuSSTuple/DecayTree");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_1_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_2_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_3_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_4_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_5_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_1_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_2_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_3_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_4_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_5_cut.root");
  }

  Double_t Bs_MM;
  Double_t Bs_DIRA;
  Double_t pi_PT;
  Double_t piFromBPIDK;
  Double_t piFromBMINIPCHI2;
  Double_t piPIDK;
  Double_t Ds_MM;
  Double_t det;
  Double_t mDsGPi;
  Double_t massDsG;
  Double_t gamma_PX;
  Double_t gamma_PY;
  Double_t gamma_PZ;
  Int_t gamma_mult;

  TBranch   *b_Bs_MM;
  TBranch   *b_Bs_DIRA;
  TBranch   *b_pi_PT;
  TBranch   *b_piFromBPIDK;
  TBranch   *b_piFromBMINIPCHI2;
  TBranch   *b_piPIDK;
  TBranch   *b_Ds_MM;
  TBranch   *b_det;
  TBranch   *b_mDsGPi;
  TBranch   *b_massDsG;
  TBranch   *b_gamma_PX;   
  TBranch   *b_gamma_PY;
  TBranch   *b_gamma_PZ;   
  TBranch   *b_gamma_mult;

  fChain->SetBranchStatus("*",1);
  fChain->SetBranchAddress("Bs_MM", &Bs_MM, &b_Bs_MM);
  fChain->SetBranchAddress("Bs_DIRA", &Bs_DIRA, &b_Bs_DIRA);
  fChain->SetBranchAddress("pi_PT", &pi_PT, &b_pi_PT);
  fChain->SetBranchAddress("piFromBPIDK", &piFromBPIDK, &b_piFromBPIDK);
  fChain->SetBranchAddress("piFromBMINIPCHI2", &piFromBMINIPCHI2, &b_piFromBMINIPCHI2);
  fChain->SetBranchAddress("piPIDK", &piPIDK, &b_piPIDK);
  fChain->SetBranchAddress("Ds_MM", &Ds_MM, &b_Ds_MM);
  fChain->SetBranchAddress("det", &det, &b_det);
  fChain->SetBranchAddress("mDsGPi", &mDsGPi, &b_mDsGPi);
  fChain->SetBranchAddress("massDsG", &massDsG, &b_massDsG);
  fChain->SetBranchAddress("gamma_PX", &gamma_PX, &b_gamma_PX);
  fChain->SetBranchAddress("gamma_PY", &gamma_PY, &b_gamma_PY);
  fChain->SetBranchAddress("gamma_PZ", &gamma_PZ, &b_gamma_PZ);
  fChain->SetBranchAddress("gamma_mult", &gamma_mult, &b_gamma_mult);

  RooRealVar *fitMass = new RooRealVar("resMass", "resMass", lowRange, highRange);
  RooRealVar *dsgpim = new RooRealVar("dsgpim", "dsgpim", 4800., 6000.);
  RooRealVar *dsgm = new RooRealVar("dsgm", "dsgm", 1900., 2500.);
  RooRealVar *bsm = new RooRealVar("bsm", "bsm", 4800., 6000.);
  RooRealVar *dsm = new RooRealVar("dsm", "dsm", 1940., 2000.);
  RooRealVar *d = new RooRealVar("d", "d", -1., 1.); 
  RooRealVar *gPT = new RooRealVar("gPT", "gPT", 0., 10000.);
  RooRealVar *gP = new RooRealVar("gP", "gP", 0., 100000.);
  RooRealVar *gMult = new RooRealVar("gMult", "gMult", 0, 100);
  RooRealVar *pibachpid = new RooRealVar("pibachpid", "pibachpid", -150., 150.);
  RooRealVar *pipid = new RooRealVar("pipid", "pipid", -150., 150.);
  RooRealVar *pibachpt = new RooRealVar("pibachpt", "pibachpt", 0., 150000.);

  RooArgSet vars;
  vars.add(RooArgSet(*fitMass, *d, *dsgpim, *dsgm, *bsm, *dsm));
  vars.add(RooArgSet(*gPT,*gP,*gMult,*pibachpid,*pipid,*pibachpt));

  RooDataSet *data = new RooDataSet("dataset", "dataset", vars);
  for(int i = 0; i!=fChain->GetEntries(); ++i){
    if (i%20000 == 0) std::cout << "--- ... Processing event: " << i << std::endl;
    fChain->GetEntry(i);
    bool cuts;
    //cuts = Bs_MM < 5366 && det < 0 && mDsGPi < 5500 && mDsGPi > 5250 && gamma_mult>0 && sqrt(pow(gamma_PX,2)+pow(gamma_PY,2))>0;
    //cuts = Bs_MM < 5600 && Bs_MM > 5100 && (mDsGPi-massDsG+2112.1) < 5500 && (mDsGPi-massDsG+2112.1) > 5250 && gamma_mult>0 && (massDsG-Ds_MM+1968.28)<2200 && (massDsG-Ds_MM+1968.28)>2050;
    cuts = Bs_MM < 5600 && Bs_MM > 5000 && piFromBPIDK<0 && pi_PT>1000 && piFromBMINIPCHI2>25 && TMath::ACos(Bs_DIRA)<0.02; //piPIDK<0;
    if (cuts) {
      *fitMass = Bs_MM;
      if(det>0) *d=1.;
      if(det<0) *d=-1.;
      *dsgpim = mDsGPi;
      *gPT = sqrt(gamma_PX*gamma_PX+gamma_PY*gamma_PY);
      *gP = sqrt(gamma_PX*gamma_PX+gamma_PY*gamma_PY+gamma_PZ*gamma_PZ);
      *gMult = gamma_mult;
      *dsgm = massDsG;
      *bsm = Bs_MM;
      *dsm = Ds_MM;
      *pibachpid = piFromBPIDK;
      *pipid = piPIDK;
      *pibachpt = pi_PT;
      RooArgSet upvars;
      upvars.add(RooArgSet(*fitMass, *d, *dsgpim, *dsgm, *bsm, *dsm));
      upvars.add(RooArgSet(*gPT,*gP,*gMult,*pibachpid,*pipid,*pibachpt));
      data->add(upvars);
    }
  }

  data->Print("v");
  ws->import(*data);

}

//____________________________________
void DoSPlot(RooWorkspace *ws, float nentries, TString sample){
  std::cout << "Calculate sWeights" << std::endl;

  // get what we need out of the workspace to do the fit
  RooAbsPdf* model = ws->pdf("model");
  RooRealVar *SigYield = ws->var("SigYield");
  RooRealVar *BkgYield = ws->var("BkgYield");
  RooDataSet *data = (RooDataSet*) ws->data("dataset");
  data->Print("v");
  Double_t nen = data->sumEntries();
  std::cout << "The dataset has " << nen << " entries" << std::endl;

  // fit the model to the data.
  model->fitTo(*data, Extended(true), SumW2Error(kTRUE), Minos(true), Strategy(2), Timer(kTRUE), NumCPU(4));

  std::cout << "The fit is done" << std::endl;
  // The sPlot technique requires that we fix the parameters
  // of the model that are not yields after doing the fit.
  RooRealVar* sigma = ws->var("sigma");
  RooRealVar* meanBs = ws->var("meanBs");
  //RooRealVar* alpha1 = ws->var("alpha1");
  //RooRealVar* n1 = ws->var("n1");
  //RooRealVar* mean2 = ws->var("mean2");
  //RooRealVar* m0 = ws->var("m0");
  //RooRealVar* c = ws->var("c");
  //RooRealVar *c1 = ws->var("c1");
  //RooRealVar *c2 = ws->var("c2");
  //RooRealVar *c3 = ws->var("c3");
  //RooRealVar *c4 = ws->var("c4");
  RooRealVar* slope = ws->var("slope");
  //RooRealVar* fracsig = ws->var("sigFrac");
//  RooRealVar* fracBd = ws->var("fracBd"); 
  RooRealVar* fracRho = ws->var("fracRho");
  RooRealVar* fracBd = ws->var("fracBd");
  //RooRealVar* fracDsstK = ws->var("fracDsstK");
  //RooRealVar* fracDsK = ws->var("fracDsK");
  RooRealVar* fracDsstRho = ws->var("fracDsstRho");
  //RooRealVar* fracDsstPi0Pi = ws->var("fracDsstPi0Pi");
  RooRealVar* fracexp = ws->var("fracexp");
  sigma->setConstant();
  meanBs->setConstant();
  //alpha1->setConstant();
  //n1->setConstant();
  //mean2->setConstant();
  //m0->setConstant();
  //c->setConstant();
  //c1->setConstant();
  //c2->setConstant();
  //c3->setConstant();
  //c4->setConstant();
  slope->setConstant();
  //fracsig->setConstant();
  fracBd->setConstant();
  fracRho->setConstant();
  fracDsstRho->setConstant();
  fracexp->setConstant();  
  //fracBd->setConstant();
  //fracDsstPi0Pi->setConstant();
  //fracDsstK->setConstant();
  //fracDsK->setConstant(); 

  RooMsgService::instance().setSilentMode(false);

  // Now we use the SPlot class to add SWeights to our data set
  // based on our model and our yield variables
  std::cout << "Start the splot" << std::endl;
  RooStats::SPlot* sData = new RooStats::SPlot("sData","An SPlot", *data, model, RooArgList(*SigYield,*BkgYield));
  //RooStats::SPlot* sData = new RooStats::SPlot("sData","An SPlot", *data, model, RooArgList(*BkgYield));

  // Check that our weights have the desired properties

  std::cout << "Check SWeights:" << std::endl;

  std::cout << "Yield of signal is "
      << SigYield->getVal() << ". From sWeights it is "
      << sData->GetYieldFromSWeight("SigYield") << std::endl;

  std::cout << "Yield of background is "
      << BkgYield->getVal() << ". From sWeights it is "
      << sData->GetYieldFromSWeight("BkgYield") << std::endl;

  for(Int_t i=0; i != 10; ++i)
    {
      std::cout << "sig Weight " << sData->GetSWeight(i,"SigYield")
    << ", bkg Weight " << sData->GetSWeight(i,"BkgYield")
    << ", Total Weight " << sData->GetSumOfEventSWeight(i)
    << std::endl;
    }

  std::cout << std::endl;

  // import this new dataset with sWeights
  std::cout << "import new dataset with sWeights" << std::endl;
  ws->import(*data, Rename("dataWithSWeights"));
  data->Print("v");

  // here will unraved the WS to write an ntuple with weights
  TFile *file = new TFile("BsMassForPhotonEff_WithSWeighted_Den_Fixed.root","RECREATE");
  TTree *finalTree = new TTree("DecayTree","tree with weights");

  Double_t sigw, bkgw, MassDsGPi, MassDsG, BMass, DsMass, piPIDK, piBachPIDK, piBachPT, Gamma_P, Gamma_PT;
  Int_t Gamma_mult;

  finalTree->Branch("sigden",&sigw,"sigden/D");
  finalTree->Branch("bkgden",&bkgw,"bkgden/D");
  finalTree->Branch("MassDsGPi",&MassDsGPi,"MassDsGPi/D");
  finalTree->Branch("Gamma_P",&Gamma_P,"Gamma_P/D");
  finalTree->Branch("Gamma_PT",&Gamma_PT,"Gamma_PT/D");
  finalTree->Branch("Gamma_mult",&Gamma_mult,"Gamma_mult/I");
  finalTree->Branch("MassDsG",&MassDsG,"MassDsG/D");
  finalTree->Branch("BMass",&BMass,"BMass/D");
  finalTree->Branch("DsMass",&DsMass,"DsMass/D");
  finalTree->Branch("piPIDK",&piPIDK,"piPIDK/D");
  finalTree->Branch("piBachPIDK",&piBachPIDK,"piBachPIDK/D");
  finalTree->Branch("piBachPT",&piBachPT,"piBachPT/D");

  for (int i = 0; i!=nen; ++i){
    const RooArgSet *Dset = data->get(i);  // get the row
    MassDsGPi = Dset->getRealValue("dsgpim");
    MassDsG = Dset->getRealValue("dsgm");
    BMass = Dset->getRealValue("bsm");
    DsMass = Dset->getRealValue("dsm");
    piPIDK = Dset->getRealValue("pipid");
    piBachPIDK = Dset->getRealValue("pibachpid");
    piBachPT = Dset->getRealValue("pibachpt");
    Gamma_mult = Dset->getRealValue("gMult");
    Gamma_P = Dset->getRealValue("gP");
    Gamma_PT = Dset->getRealValue("gPT");
    sigw = Dset->getRealValue("SigYield_sw");
    bkgw = Dset->getRealValue("BkgYield_sw");
    finalTree->Fill();
  }
  finalTree->Write();
}

RooDataSet loadPdf(TString decay){
  // get the RooKeysPdf from the ntuples
  // first load it's ntuple
  TChain *chain = new TChain("B2DsMuNuTuple/DecayTree");
  if(decay=="bsdsk"){
    chain->Add("/afs/cern.ch/user/r/rvazquez/work/gangadir/workspace/rvazquez/LocalXML/1534/BsDsK.root");
  }
  if(decay=="bsdsstgpi"){ 
    chain->Add("/afs/cern.ch/user/r/rvazquez/work/gangadir/workspace/rvazquez/LocalXML/1536/BsDsstPi.root");
  }
  if(decay=="bsdsstpi0pi"){
    chain->Add("/afs/cern.ch/user/r/rvazquez/work/gangadir/workspace/rvazquez/LocalXML/1536/BsDsstPi.root");
  }
  if(decay=="bsdsrho"){
    chain->Add("/afs/cern.ch/user/r/rvazquez/work/gangadir/workspace/rvazquez/LocalXML/1538/BsDsRho.root");
  }
  if(decay=="bsdsstrho"){
    chain->Add("/afs/cern.ch/user/r/rvazquez/work/gangadir/workspace/rvazquez/LocalXML/1540/BsDsstRho.root");
  }
  if(decay=="bsdsstk"){
    chain->Add("/afs/cern.ch/user/r/rvazquez/work/gangadir/workspace/rvazquez/LocalXML/1545/BsDsstK.root");
  }
  std::cout << "For decay " << decay << ", there are " << chain->GetEntries() << " entries" << std::endl;
  Double_t B_MM, Ds_MM, Kpl_PIDK, Kmi_PIDK, Kpl_PIDp, Kmi_PIDp, piFromB_PIDK, piFromB_MINIPCHI2, B_ENDVERTEX_CHI2, pi_PIDK, B_DIRA_OWNPV;
  Double_t Kpl_PX, Kpl_PY, Kpl_PZ, Kpl_PE, Kmi_PX, Kmi_PY, Kmi_PZ, Kmi_PE, piFromB_PT;
  Int_t Ds_0_40_nc_MCmax_MOTHER_ID, Ds_0_40_nc_MCmax_ID, Ds_0_40_nc_MCmax_GD_ID;
  TBranch *b_B_MM, *b_Ds_MM, *b_Kpl_PIDK, *b_Kmi_PIDK, *b_Kpl_PIDp, *b_Kmi_PIDp, *b_piFromB_PIDK, *b_piFromB_MINIPCHI2, *b_B_ENDVERTEX_CHI2, *b_pi_PIDK, *b_B_DIRA_OWNPV;
  TBranch *b_Kpl_PX, *b_Kpl_PY, *b_Kpl_PZ, *b_Kpl_PE, *b_Kmi_PX, *b_Kmi_PY, *b_Kmi_PZ, *b_Kmi_PE, *b_piFromB_PT; 
  TBranch *b_Ds_0_40_nc_MCmax_MOTHER_ID, *b_Ds_0_40_nc_MCmax_ID, *b_Ds_0_40_nc_MCmax_GD_ID;
  chain->SetBranchStatus("*",1);
  chain->SetBranchAddress("B_MM", &B_MM, &b_B_MM);
  chain->SetBranchAddress("B_DIRA_OWNPV", &B_DIRA_OWNPV, &b_B_DIRA_OWNPV);
  chain->SetBranchAddress("Ds_MM", &Ds_MM, &b_Ds_MM);
  chain->SetBranchAddress("Kpl_PIDK", &Kpl_PIDK, &b_Kpl_PIDK);
  chain->SetBranchAddress("Kmi_PIDK", &Kmi_PIDK, &b_Kmi_PIDK);
  chain->SetBranchAddress("Kpl_PIDp", &Kpl_PIDp, &b_Kpl_PIDp);
  chain->SetBranchAddress("Kmi_PIDp", &Kmi_PIDp, &b_Kmi_PIDp);
  chain->SetBranchAddress("pi_PIDK", &pi_PIDK, &b_pi_PIDK);
  chain->SetBranchAddress("piFromB_PIDK", &piFromB_PIDK, &b_piFromB_PIDK);
  chain->SetBranchAddress("piFromB_PT", &piFromB_PT, &b_piFromB_PT);
  chain->SetBranchAddress("piFromB_MINIPCHI2", &piFromB_MINIPCHI2, &b_piFromB_MINIPCHI2);
  chain->SetBranchAddress("B_ENDVERTEX_CHI2", &B_ENDVERTEX_CHI2, &b_B_ENDVERTEX_CHI2);
  chain->SetBranchAddress("Kpl_PX", &Kpl_PX, &b_Kpl_PX);
  chain->SetBranchAddress("Kpl_PY", &Kpl_PY, &b_Kpl_PY);
  chain->SetBranchAddress("Kpl_PZ", &Kpl_PZ, &b_Kpl_PZ);
  chain->SetBranchAddress("Kpl_PE", &Kpl_PE, &b_Kpl_PE);
  chain->SetBranchAddress("Kmi_PX", &Kmi_PX, &b_Kmi_PX);
  chain->SetBranchAddress("Kmi_PY", &Kmi_PY, &b_Kmi_PY);
  chain->SetBranchAddress("Kmi_PZ", &Kmi_PZ, &b_Kmi_PZ);
  chain->SetBranchAddress("Kmi_PE", &Kmi_PE, &b_Kmi_PE); 
  chain->SetBranchAddress("Ds_0.40_nc_MCmax_MOTHER_ID", &Ds_0_40_nc_MCmax_MOTHER_ID, &b_Ds_0_40_nc_MCmax_MOTHER_ID);
  chain->SetBranchAddress("Ds_0.40_nc_MCmax_ID", &Ds_0_40_nc_MCmax_ID, &b_Ds_0_40_nc_MCmax_ID);
  chain->SetBranchAddress("Ds_0.40_nc_MCmax_GD_ID", &Ds_0_40_nc_MCmax_GD_ID, &b_Ds_0_40_nc_MCmax_GD_ID); 

  // create the ws variables
  RooRealVar BMass("resMass", "resMass", 5000., 5600.);
  RooArgSet vars;
  vars.add(RooArgSet(BMass));
  // create the dataset
  RooDataSet *ds = new RooDataSet(decay+"DS", decay+"DS", vars);
  for(int i = 0; i != chain->GetEntries(); ++i){
    if (i%10000 == 0) std::cout << "--- ... Processing event: " << i << std::endl;
    chain->GetEntry(i);
    bool cuts;
    cuts = Ds_MM>1940 && Ds_MM<2000 && Kpl_PIDK-Kpl_PIDp>-10 && Kmi_PIDK-Kmi_PIDp>-10 && B_MM<5600 && B_MM>5000 && B_ENDVERTEX_CHI2<6 && piFromB_PIDK<0 && abs(sqrt((Kpl_PE+Kmi_PE)*(Kpl_PE+Kmi_PE)-(Kpl_PX+Kmi_PX)*(Kpl_PX+Kmi_PX)-(Kpl_PY+Kmi_PY)*(Kpl_PY+Kmi_PY)-(Kpl_PZ+Kmi_PZ)*(Kpl_PZ+Kmi_PZ))-1019.46)<7 && piFromB_PT>1000 && piFromB_MINIPCHI2>25 && TMath::ACos(B_DIRA_OWNPV)<0.02; // pi_PIDK<0;
    //cuts = Ds_MM>1940 && Ds_MM<2000 && B_MM<5600 && B_MM>5000 && piFromB_PT>1000 && Kpl_PIDK-Kpl_PIDp>-10 && Kmi_PIDK-Kmi_PIDp>-10 && B_ENDVERTEX_CHI2<6 && piFromB_PIDK<0;
    if (cuts) {
      bool extraCut;
      if(decay=="bsdsstgpi"){
        extraCut = abs(Ds_0_40_nc_MCmax_ID)==22 && abs(Ds_0_40_nc_MCmax_MOTHER_ID)==433;
      }
      else if(decay=="bsdsstpi0pi"){
        extraCut = abs(Ds_0_40_nc_MCmax_ID)==22 && abs(Ds_0_40_nc_MCmax_MOTHER_ID)==111 && abs(Ds_0_40_nc_MCmax_GD_ID)==433;
      }
      else {
        extraCut = B_MM>4500;
      }
      if (extraCut){
        BMass = B_MM;
        RooArgSet upvars;
        upvars.add(RooArgSet(BMass));
        ds->add(upvars);
      }
    }
  }
  ds->Print("v");
  return *ds;
}

void MakePlots(RooWorkspace *ws, TString sample){

  // Here we make plots of the discriminating variable (mass) after the fit
  // and of the control variable (isolation) after unfolding with sPlot.
  std::cout << "make plots" << std::endl;

  // get what we need out of the workspace
  RooAbsPdf *model = ws->pdf("model");
  RooAbsPdf *bsdspi = ws->pdf("bsdspi");
  RooAbsPdf *bddspi = ws->pdf("bddspi");
  RooAbsPdf *bsdsrho = ws->pdf("bsdsrho");
  RooAbsPdf *exp = ws->pdf("exp");
  RooAbsPdf *bsdsstpi = ws->pdf("sig");
  RooAbsPdf *sig = ws->pdf("bsdsstgpi");
  RooAbsPdf *bsdsstpi0pi = ws->pdf("bsdsstpi0pi");
  RooAbsPdf *bsdsstk = ws->pdf("bsdsstk");
  RooAbsPdf *bsdsk = ws->pdf("bsdsk");
  RooAbsPdf *bsdsstrho = ws->pdf("bsdsstrho");
  RooAbsPdf *bkg = ws->pdf("bkg");

  // get the variables
  RooRealVar *invMass = ws->var("resMass");
  //RooRealVar gP = ws->var("gP");

  // note, we get the dataset with sWeights
  RooDataSet* data = (RooDataSet*) ws->data("dataWithSWeights");

  // this shouldn't be necessary, need to fix something with workspace
  // do this to set parameters back to their fitted values.
  model->fitTo(*data, Extended(true), SumW2Error(kTRUE), Minos(true), Strategy(2), Timer(kTRUE), NumCPU(4));
  // make our canvases and plot
  TCanvas* cdata1 = new TCanvas("sPlotMCORR","sPlot MCORR", 400, 400);
  //cdata1->Divide(1,3);

  //plot invMass for data with full model and individual componenets overlayed
  //cdata1->cd(1);
  RooPlot *frame1_1;
  frame1_1 = invMass->frame(lowRange, highRange, 100);
  data->plotOn(frame1_1,MarkerStyle(7)) ;
  model->plotOn(frame1_1,LineColor(kBlue),LineWidth(3));//,NormRange("FitRange")) ;   
  model->plotOn(frame1_1,Components(*bsdspi),LineColor(kRed),LineWidth(3));
  model->plotOn(frame1_1,Components(*bddspi),LineStyle(kDashed),LineColor(kRed),LineWidth(3));
  model->plotOn(frame1_1,Components(*exp),LineStyle(kDashed),LineColor(kCyan),LineWidth(3));
  model->plotOn(frame1_1,Components(*bsdsstpi),LineStyle(kDashed),LineColor(kMagenta),LineWidth(3));
  model->plotOn(frame1_1,Components(*sig),LineStyle(kDashed),LineColor(kMagenta-1),LineWidth(3));
  model->plotOn(frame1_1,Components(*bsdsstpi0pi),LineStyle(kDashed),LineColor(kMagenta+1),LineWidth(3));
  model->plotOn(frame1_1,Components(*bsdsrho),LineStyle(kDashed),LineColor(kBlue),LineWidth(3));
  model->plotOn(frame1_1,Components(*bsdsstk),LineStyle(kDashed),LineColor(kGreen),LineWidth(3));
  model->plotOn(frame1_1,Components(*bsdsk),LineStyle(kDashed),LineColor(kGreen+1),LineWidth(3));
  model->plotOn(frame1_1,Components(*bsdsstrho),LineStyle(kDashed),LineColor(kGreen+2),LineWidth(3));
  frame1_1->SetTitle("Fit of model to discriminating variable");
  frame1_1->Draw() ;
  std::cout << "drawn" << std::endl;

  // Plot Ds_MM for signal component.  
  // Do this by plotting all events weighted by the sWeight for the signal component.
  // The SPlot class adds a new variable that has the name of the corresponding
  // yield + "_sw".
/*
  cdata1->cd(2);
  RooDataSet *dataw_sig_1 = new RooDataSet(data->GetName(),data->GetTitle(),data,*data->get(),0,"SigYield_sw") ;
  RooPlot* frame2_1;
  frame2_1 = gP->frame(0.,30000.,100);
  dataw_sig_1->plotOn(frame2_1, DataError(RooAbsData::SumW2), MarkerStyle(1) ) ;
  frame2_1->SetTitle("Corrected mass distribution for signal");
  frame2_1->Draw() ;

  // Plot Ds_MM for backgournd component.  
  // Eg. plot all events weighted by the sWeight for the background component.
  // The SPlot class adds a new variable that has the name of the corresponding
  // yield + "_sw".
  cdata1->cd(3);
  RooDataSet *dataw_bkg_1 = new RooDataSet(data->GetName(),data->GetTitle(),data,*data->get(),0,"BkgYield_sw") ;
  RooPlot* frame3_1;
  frame3_1 = gP->frame(0.,30000.,100);
  dataw_bkg_1->plotOn(frame3_1,DataError(RooAbsData::SumW2), MarkerStyle(1) ) ;
  frame3_1->SetTitle("Corrected mass distribution for background");
  frame3_1->Draw() ;
*/  
  cdata1->SaveAs("SPlot_BsDsPi_"+sample+"_fixed.pdf");

  delete cdata1;
}

float getEntries(TString sample){
  int nentries;
  TChain *fChain;
  if (sample == "RS"){
    fChain = new TChain("B2DsMuNuTuple/DecayTree");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_1_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_2_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_3_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_4_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_5_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_1_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_2_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_3_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_4_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_5_cut.root");
  } else if (sample == "SS"){
    fChain = new TChain("B2DsMuNuSSTuple/DecayTree");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_1_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_2_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_3_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_4_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Up_5_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_1_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_2_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_3_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_4_cut.root");
    fChain->Add("/afs/cern.ch/user/r/rvazquez/work/photonControl_Down_5_cut.root");
  }
  Double_t Bs_MM, pi_PT, piFromBPIDK, piPIDK;
  TBranch *b_Bs_MM, *b_pi_PT, *b_piFromBPIDK, *b_piPIDK;
  fChain->SetBranchStatus("*",1);
  fChain->SetBranchAddress("Bs_MM", &Bs_MM, &b_Bs_MM);
  fChain->SetBranchAddress("pi_PT", &pi_PT, &b_pi_PT);
  fChain->SetBranchAddress("piFromBPIDK", &piFromBPIDK, &b_piFromBPIDK);
  fChain->SetBranchAddress("piPIDK", &piPIDK, &b_piPIDK); 

  nentries = fChain->GetEntries("Bs_MM < 5600 && Bs_MM > 5000 && piFromBPIDK<0 && pi_PT>1000"); //piPIDK<0");
  std::cout << "Total number of data entries is = " << nentries << std::endl;
  delete fChain;
  return nentries;
}

