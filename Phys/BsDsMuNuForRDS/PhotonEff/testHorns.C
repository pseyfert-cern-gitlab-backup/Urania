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
void AddModel(RooWorkspace*, float, TString);
void AddData(RooWorkspace*, TString);
void DoSPlot(RooWorkspace*, float);
void MakePlots(RooWorkspace*, TString);
float getEntries(TString);

double lowRange  = 5000.;
double highRange = 5400.;

void testHorns(TString decay){

  // Create a new workspace to manage the project.
  RooWorkspace *wspace = new RooWorkspace("myWS");

  // add the signal and background models to the workspace.
  // Inside this function you will find a discription our model.
  float nentries = getEntries(decay);
  //float nentries = 100000;
  AddModel(wspace, nentries, decay);
  
  // add data to the workspace
  AddData(wspace, decay);

  // inspect the workspace if you wish
  wspace->Print();

  // do sPlot.  
  // This wil make a new dataset with sWeights added for every event.
  DoSPlot(wspace, nentries);

  // Make some plots showing the discriminating variable and 
  // the control variable after unfolding.
  MakePlots(wspace, decay);

  delete wspace;

}

//____________________________________
void AddModel(RooWorkspace *ws, float nentries, TString decay){

  // Make models for signal and background 

  // make a RooRealVar for the observables
  RooRealVar invMass("resMass", "resMass", lowRange, highRange, "MeV");

  /////////////////////////////////////////////
  // make 1-d model for signal including the invariant mass 
  std::cout << "make signal model" << std::endl;
 
  RooRealVar a("a", "a", 5100, 2000, 5200); 
  RooRealVar b("b", "b", 5200, 4900, 5500);
  //RooRealVar a("a", "a", 5001.7); 
  //RooRealVar b("b", "b", 5311.9);
  //RooRealVar a("a", "a", 5100.5);
  //RooRealVar b("b", "b", 5207.6);
  RooRealVar csi("csi", "csi", 1., 0., 5.);
  RooRealVar shift("shift", "shift", 0., 0., 0.);
  RooRealVar sigma("sigma", "sigma", 30., 5., 400.);
  RooRealVar rsigma("rsigma", "ratio sigma", 7., 0., 10.);
  RooRealVar fsigma("fsigma", "fraction sigma", 0.05, 0., 1.);

  RooRealVar a2("a2", "a2", 2200, 2000, 5200);
  RooRealVar b2("b2", "b2", 5300, 4900, 5500);
  RooRealVar csi2("csi2", "csi2", 1.);
  RooRealVar shift2("shift2", "shift2", 0.);
  RooRealVar sigma2("sigma2", "sigma2", 30., 10., 200.);
  RooRealVar rsigma2("rsigma2", "ratio sigma2", 1.);
  RooRealVar fsigma2("fsigma2", "fraction sigma2", 1.); 

  RooHORNSdini Horn1("horn1", "horn1", invMass, a, b, csi, shift, sigma, rsigma, fsigma);
  RooHORNSdini Horn2("horn2", "horn2", invMass, a2, b2, csi, shift, sigma2, rsigma, fsigma);
  RooHILLdini  Hill("hill1", "hill1", invMass, a, b, csi, shift, sigma, rsigma, fsigma);
  RooRealVar frac("frac", "frac", 0.058, 0.0, 1.); 

  //RooAddPdf SigModel = NULL;
  //if (decay=="bsdsrho"){
  //RooAddPdf SigModel("sig", "signal", RooArgList(Horn1, Horn2), RooArgList(frac));
  //}   
  //if (decay=="bsdsstrho"){
  //RooAddPdf SigModel("sig", "signal", RooArgList(Horn2, Hill), RooArgList(frac));
  //}  
   

  RooHILLdini SigModel("sig", "signal", invMass, a, b, csi, shift, sigma, rsigma, fsigma);
  //RooHORNSdini SigModel("sig", "signal", invMass, a, b, csi, shift, sigma, rsigma, fsigma);

  //////////////////////////////////////////////
  // combined model
  // These variables represent the number of signal or background events
  // They will be fitted.
  RooRealVar SigYield("SigYield","fitted yield for Signal", nentries*1.0, 0.5*nentries, 1.0*nentries) ;
  SigYield.setError(sqrt(nentries));

  // now make the combined model
  std::cout << "make full model" << std::endl;
  RooAddPdf model("model","signal+background models", SigModel, SigYield);
  //RooAddPdf model("model","only background models", RooArgList(*BkgModel), RooArgList(BkgYield));

  // interesting for debugging and visualizing the model
  model.graphVizTree("fullModel.dot");
  std::cout << "import model" << std::endl;
  ws->import(model);

}

//____________________________________
void AddData(RooWorkspace *ws, TString decay){
  // Add data from nutples

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
  if(decay=="bsdsstpifull"){
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

  Double_t B_MM;
  Double_t B_DIRA_OWNPV;
  Double_t pi_PT;
  Double_t piFromB_PIDK;
  Double_t piFromB_MINIPCHI2;
  Double_t pi_PIDK;
  Double_t Ds_MM;
  Int_t Ds_0_40_nc_MCmax_MOTHER_ID, Ds_0_40_nc_MCmax_ID, Ds_0_40_nc_MCmax_GD_ID, Ds_TRUEID, piFromB_MC_MOTHER_ID;

  TBranch   *b_B_MM;
  TBranch   *b_B_DIRA_OWNPV;
  TBranch   *b_pi_PT;
  TBranch   *b_piFromB_PIDK;
  TBranch   *b_piFromB_MINIPCHI2;
  TBranch   *b_pi_PIDK;
  TBranch   *b_Ds_MM;
  TBranch   *b_Ds_0_40_nc_MCmax_MOTHER_ID, *b_Ds_0_40_nc_MCmax_ID, *b_Ds_0_40_nc_MCmax_GD_ID, *b_Ds_TRUEID, *b_piFromB_MC_MOTHER_ID;

  chain->SetBranchStatus("*",1);
  chain->SetBranchAddress("B_MM", &B_MM, &b_B_MM);
  chain->SetBranchAddress("B_DIRA_OWNPV", &B_DIRA_OWNPV, &b_B_DIRA_OWNPV);
  chain->SetBranchAddress("pi_PT", &pi_PT, &b_pi_PT);
  chain->SetBranchAddress("piFromB_PIDK", &piFromB_PIDK, &b_piFromB_PIDK);
  chain->SetBranchAddress("piFromB_MINIPCHI2", &piFromB_MINIPCHI2, &b_piFromB_MINIPCHI2);
  chain->SetBranchAddress("pi_PIDK", &pi_PIDK, &b_pi_PIDK);
  chain->SetBranchAddress("Ds_MM", &Ds_MM, &b_Ds_MM);
  chain->SetBranchAddress("Ds_0.40_nc_MCmax_MOTHER_ID", &Ds_0_40_nc_MCmax_MOTHER_ID, &b_Ds_0_40_nc_MCmax_MOTHER_ID);
  chain->SetBranchAddress("Ds_0.40_nc_MCmax_ID", &Ds_0_40_nc_MCmax_ID, &b_Ds_0_40_nc_MCmax_ID);
  chain->SetBranchAddress("Ds_0.40_nc_MCmax_GD_ID", &Ds_0_40_nc_MCmax_GD_ID, &b_Ds_0_40_nc_MCmax_GD_ID);
  chain->SetBranchAddress("Ds_TRUEID", &Ds_TRUEID, &b_Ds_TRUEID);
  chain->SetBranchAddress("piFromB_MC_MOTHER_ID", &piFromB_MC_MOTHER_ID, &b_piFromB_MC_MOTHER_ID);

  RooRealVar *fitMass = new RooRealVar("resMass", "resMass", lowRange, highRange);
  RooRealVar *bsm = new RooRealVar("bsm", "bsm", 4800., 6000.);
  RooRealVar *dsm = new RooRealVar("dsm", "dsm", 1940., 2000.);
  RooRealVar *pibachpid = new RooRealVar("pibachpid", "pibachpid", -150., 150.);
  RooRealVar *pipid = new RooRealVar("pipid", "pipid", -150., 150.);
  RooRealVar *pibachpt = new RooRealVar("pibachpt", "pibachpt", 0., 150000.);

  RooArgSet vars;
  vars.add(RooArgSet(*fitMass, *bsm, *dsm));
  vars.add(RooArgSet(*pibachpid,*pipid,*pibachpt));

  RooDataSet *data = new RooDataSet("dataset", "dataset", vars);
  for(int i = 0; i!=chain->GetEntries(); ++i){
    if (i%20000 == 0) std::cout << "--- ... Processing event: " << i << std::endl;
    chain->GetEntry(i);
    bool cuts;
    //cuts = Bs_MM < 5366 && det < 0 && mDsGPi < 5500 && mDsGPi > 5250 && gamma_mult>0 && sqrt(pow(gamma_PX,2)+pow(gamma_PY,2))>0;
    //cuts = Bs_MM < 5600 && Bs_MM > 5100 && (mDsGPi-massDsG+2112.1) < 5500 && (mDsGPi-massDsG+2112.1) > 5250 && gamma_mult>0 && (massDsG-Ds_MM+1968.28)<2200 && (massDsG-Ds_MM+1968.28)>2050;
    cuts = B_MM < 5400 && B_MM > 5000 && piFromB_PIDK<0 && pi_PT>1000 && piFromB_MINIPCHI2>25 && TMath::ACos(B_DIRA_OWNPV)<0.02 && abs(Ds_TRUEID)==431 && abs(piFromB_MC_MOTHER_ID)==531; //piPIDK<0;
    if(decay=="bsdsstgpi") {
      cuts = B_MM < 5400 && B_MM > 5000 && piFromB_PIDK<0 && pi_PT>1000 && piFromB_MINIPCHI2>25 && TMath::ACos(B_DIRA_OWNPV)<0.02 && abs(Ds_0_40_nc_MCmax_ID)==22 && abs(Ds_0_40_nc_MCmax_MOTHER_ID)==433 && abs(Ds_TRUEID)==431 && abs(piFromB_MC_MOTHER_ID)==531; 
    }
    else if(decay=="bsdsstpi0pi"){
      cuts = B_MM < 5400 && B_MM > 5000 && piFromB_PIDK<0 && pi_PT>1000 && piFromB_MINIPCHI2>25 && TMath::ACos(B_DIRA_OWNPV)<0.02 && abs(Ds_0_40_nc_MCmax_ID)==22 && abs(Ds_0_40_nc_MCmax_MOTHER_ID)==111 && abs(Ds_0_40_nc_MCmax_GD_ID)==433 && abs(Ds_TRUEID)==431 && abs(piFromB_MC_MOTHER_ID)==531;
    }
    if (cuts) {
      *fitMass = B_MM;
      *bsm = B_MM;
      *dsm = Ds_MM;
      *pibachpid = piFromB_PIDK;
      *pipid = pi_PIDK;
      *pibachpt = pi_PT;
      RooArgSet upvars;
      upvars.add(RooArgSet(*fitMass, *bsm, *dsm));
      upvars.add(RooArgSet(*pibachpid,*pipid,*pibachpt));
      data->add(upvars);
    }
  }

  data->Print("v");
  ws->import(*data);

}

//____________________________________
void DoSPlot(RooWorkspace *ws, float nentries){
  std::cout << "Calculate sWeights" << std::endl;

  // get what we need out of the workspace to do the fit
  RooAbsPdf* model = ws->pdf("model");
  RooRealVar *SigYield = ws->var("SigYield");
  RooDataSet *data = (RooDataSet*) ws->data("dataset");
  data->Print("v");
  Double_t nen = data->sumEntries();
  std::cout << "The dataset has " << nen << " entries" << std::endl;

  // fit the model to the data.
  model->fitTo(*data, Extended(true), SumW2Error(kTRUE), Minos(false), Strategy(2), Timer(kTRUE), NumCPU(4));

  std::cout << "The fit is done" << std::endl;
  // The sPlot technique requires that we fix the parameters
  // of the model that are not yields after doing the fit.
  RooRealVar* a = ws->var("a");
  RooRealVar* b = ws->var("b");
  RooRealVar* csi = ws->var("csi");
//  RooRealVar* shift = ws->var("shift");
  RooRealVar* sigma = ws->var("sigma");
  RooRealVar* rsigma = ws->var("rsigma");
  RooRealVar* fsigma = ws->var("fsigma");
  a->setConstant();
  b->setConstant();
  csi->setConstant();
//  shift->setConstant();
  sigma->setConstant();
  rsigma->setConstant();
  fsigma->setConstant();

  std::cout << "Value of a = " << a->getVal() << " +/- " << a->getError() << std::endl;
  std::cout << "Value of b = " << b->getVal() << " +/- " << b->getError() << std::endl;
  std::cout << "Value of csi = " << csi->getVal() << " +/- " << csi->getError() << std::endl;
//  std::cout << "Value of shift = " << shift->getVal() << " +/- " << shift->getError() << std::endl;
  std::cout << "Value of sigma = " << sigma->getVal() << " +/- " << sigma->getError() << std::endl;
  std::cout << "Value of rsigma = " << rsigma->getVal() << " +/- " << rsigma->getError() << std::endl;
  std::cout << "Value of fsigma = " << fsigma->getVal() << " +/- " << fsigma->getError() << std::endl;

/*
  RooRealVar* a2 = ws->var("a2");
  RooRealVar* b2 = ws->var("b2");
//  RooRealVar* csi2 = ws->var("csi2");
//  RooRealVar* shift2 = ws->var("shift2");
  RooRealVar* sigma2 = ws->var("sigma2");
//  RooRealVar* rsigma2 = ws->var("rsigma2");
//  RooRealVar* fsigma2 = ws->var("fsigma2");
  a2->setConstant();
  b2->setConstant();
//  csi2->setConstant();
//  shift2->setConstant();
  sigma2->setConstant();
//  rsigma2->setConstant();
//  fsigma2->setConstant();

  std::cout << "Value of a2 = " << a2->getVal() << " +/- " << a2->getError() << std::endl;
  std::cout << "Value of b2 = " << b2->getVal() << " +/- " << b2->getError() << std::endl;
//  std::cout << "Value of csi2 = " << csi2->getVal() << " +/- " << csi2->getError() << std::endl;
//  std::cout << "Value of shift2 = " << shift2->getVal() << " +/- " << shift2->getError() << std::endl;
  std::cout << "Value of sigma2 = " << sigma2->getVal() << " +/- " << sigma2->getError() << std::endl;
//  std::cout << "Value of rsigma2 = " << rsigma2->getVal() << " +/- " << rsigma2->getError() << std::endl;
//  std::cout << "Value of fsigma2 = " << fsigma2->getVal() << " +/- " << fsigma2->getError() << std::endl;

  RooRealVar* frac = ws->var("frac");  
  frac->setConstant();
  std::cout << "Value of frac = " << frac->getVal() << " +/- " << frac->getError() << std::endl; 
*/
  RooMsgService::instance().setSilentMode(false);

  // Now we use the SPlot class to add SWeights to our data set
  // based on our model and our yield variables
  std::cout << "Start the splot" << std::endl;
  RooStats::SPlot* sData = new RooStats::SPlot("sData","An SPlot", *data, model, RooArgList(*SigYield));

  // Check that our weights have the desired properties

  std::cout << "Check SWeights:" << std::endl;

  std::cout << "Yield of signal is "
      << SigYield->getVal() << ". From sWeights it is "
      << sData->GetYieldFromSWeight("SigYield") << std::endl;

  for(Int_t i=0; i != 10; ++i)
    {
      std::cout << "sig Weight " << sData->GetSWeight(i,"SigYield")
    << ", Total Weight " << sData->GetSumOfEventSWeight(i)
    << std::endl;
    }

  std::cout << std::endl;

  // import this new dataset with sWeights
  std::cout << "import new dataset with sWeights" << std::endl;
  ws->import(*data, Rename("dataWithSWeights"));
  data->Print("v");

}

void MakePlots(RooWorkspace *ws, TString decay){

  // Here we make plots of the discriminating variable (mass) after the fit
  // and of the control variable (isolation) after unfolding with sPlot.
  std::cout << "make plots" << std::endl;

  // get what we need out of the workspace
  RooAbsPdf *model = ws->pdf("model");
  RooAbsPdf *sig = ws->pdf("sig");
//  RooAbsPdf *hill = ws->pdf("hill1");
//  RooAbsPdf *horn = ws->pdf("horn2");

  // get the variables
  RooRealVar *invMass = ws->var("resMass");
  //RooRealVar gP = ws->var("gP");

  // note, we get the dataset with sWeights
  RooDataSet* data = (RooDataSet*) ws->data("dataWithSWeights");

  // this shouldn't be necessary, need to fix something with workspace
  // do this to set parameters back to their fitted values.
  model->fitTo(*data, Extended(true), SumW2Error(kTRUE), Minos(false), Strategy(2), Timer(kTRUE), NumCPU(4));
  // make our canvases and plot
  TCanvas* cdata1 = new TCanvas("sPlotMCORR","sPlot MCORR", 400, 400);

  //plot invMass for data with full model and individual componenets overlayed
  RooPlot *frame1_1;
  frame1_1 = invMass->frame(lowRange, highRange, 80);
  data->plotOn(frame1_1,MarkerStyle(7)) ;
  model->plotOn(frame1_1,LineColor(kBlue),LineWidth(3));//,NormRange("FitRange")) ;   
  model->plotOn(frame1_1,Components(*sig),LineStyle(kDashed),LineColor(kMagenta-1),LineWidth(3));
//  model->plotOn(frame1_1,Components(*hill),LineStyle(kDashed),LineColor(kMagenta-2),LineWidth(3));
//  model->plotOn(frame1_1,Components(*horn),LineStyle(kDashed),LineColor(kMagenta-3),LineWidth(3));
  frame1_1->SetTitle("Fit of model to discriminating variable");
  frame1_1->Draw() ;
  std::cout << "drawn" << std::endl;

  cdata1->SaveAs("SPlot_BsDsPi_"+decay+".pdf");

  delete cdata1;
}

float getEntries(TString decay){
  int nentries;
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
  if(decay=="bsdsstpifull"){
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
  Double_t B_MM, pi_PT, piFromB_PIDK, pi_PIDK, piFromB_MINIPCHI2, B_DIRA_OWNPV;
  Int_t Ds_0_40_nc_MCmax_MOTHER_ID, Ds_0_40_nc_MCmax_ID, Ds_0_40_nc_MCmax_GD_ID, Ds_TRUEID, piFromB_MC_MOTHER_ID;
  TBranch *b_B_MM, *b_pi_PT, *b_piFromB_PIDK, *b_pi_PIDK, *b_B_DIRA_OWNPV, *b_piFromB_MINIPCHI2;
  TBranch *b_Ds_0_40_nc_MCmax_MOTHER_ID, *b_Ds_0_40_nc_MCmax_ID, *b_Ds_0_40_nc_MCmax_GD_ID, *b_Ds_TRUEID, *b_piFromB_MC_MOTHER_ID;

  chain->SetBranchStatus("*",1);
  chain->SetBranchAddress("B_MM", &B_MM, &b_B_MM);
  chain->SetBranchAddress("pi_PT", &pi_PT, &b_pi_PT);
  chain->SetBranchAddress("piFromB_PIDK", &piFromB_PIDK, &b_piFromB_PIDK);
  chain->SetBranchAddress("pi_PIDK", &pi_PIDK, &b_pi_PIDK); 
  chain->SetBranchAddress("B_DIRA_OWNPV", &B_DIRA_OWNPV, &b_B_DIRA_OWNPV);
  chain->SetBranchAddress("piFromB_MINIPCHI2", &piFromB_MINIPCHI2, &b_piFromB_MINIPCHI2);
  chain->SetBranchAddress("Ds_0.40_nc_MCmax_MOTHER_ID", &Ds_0_40_nc_MCmax_MOTHER_ID, &b_Ds_0_40_nc_MCmax_MOTHER_ID);
  chain->SetBranchAddress("Ds_0.40_nc_MCmax_ID", &Ds_0_40_nc_MCmax_ID, &b_Ds_0_40_nc_MCmax_ID);
  chain->SetBranchAddress("Ds_0.40_nc_MCmax_GD_ID", &Ds_0_40_nc_MCmax_GD_ID, &b_Ds_0_40_nc_MCmax_GD_ID);
  chain->SetBranchAddress("Ds_TRUEID", &Ds_TRUEID, &b_Ds_TRUEID); 
  chain->SetBranchAddress("piFromB_MC_MOTHER_ID", &piFromB_MC_MOTHER_ID, &b_piFromB_MC_MOTHER_ID);
  
  nentries = chain->GetEntries("B_MM < 5400 && B_MM > 5000 && piFromB_PIDK<0 && pi_PT>1000 && piFromB_MINIPCHI2>25 && acos(B_DIRA_OWNPV)<0.02 && abs(Ds_TRUEID)==431 && abs(piFromB_MC_MOTHER_ID)==531"); //piPIDK<0");
  if(decay=="bsdsstgpi") {
    nentries = chain->GetEntries("B_MM < 5400 && B_MM > 5000 && piFromB_PIDK<0 && pi_PT>1000 && piFromB_MINIPCHI2>25 && acos(B_DIRA_OWNPV)<0.02 && abs(Ds_0.40_nc_MCmax_ID)==22 && abs(Ds_0.40_nc_MCmax_MOTHER_ID)==433 && abs(Ds_TRUEID)==431 && abs(piFromB_MC_MOTHER_ID)==531");
  } 
  else if(decay=="bsdsstpi0pi"){
    nentries = chain->GetEntries("B_MM < 5400 && B_MM > 5000 && piFromB_PIDK<0 && pi_PT>1000 && piFromB_MINIPCHI2>25 && acos(B_DIRA_OWNPV)<0.02 && abs(Ds_0.40_nc_MCmax_ID)==22 && abs(Ds_0.40_nc_MCmax_MOTHER_ID)==111 && abs(Ds_0.40_nc_MCmax_GD_ID)==433 && abs(Ds_TRUEID)==431 && abs(piFromB_MC_MOTHER_ID)==531");
  }
  std::cout << "Total number of data entries is = " << nentries << std::endl;
  delete chain;
  return nentries;
}

