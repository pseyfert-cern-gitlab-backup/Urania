#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
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

// #################
// ##### INFO ######  
// This code does the splots of the Ds*Pi mass to get the photon efficiency
// ################# 

// use this order for safety on library loading
using namespace RooFit ;
using namespace RooStats ;

// see below for implementation
void AddModel(RooWorkspace*, float);
void AddData(RooWorkspace*);
void DoSPlot(RooWorkspace*, float);
void MakePlots(RooWorkspace*);
float getEntries();

void fitPhotonEffNum(){

  // Create a new workspace to manage the project.
  RooWorkspace* wspace = new RooWorkspace("myWS");

  // add the signal and background models to the workspace.
  // Inside this function you will find a discription our model.
  float nentries = getEntries();
  //float nentries = 100000;
  AddModel(wspace, nentries);

  // add data to the workspace
  AddData(wspace);

  // inspect the workspace if you wish
  wspace->Print();

  // do sPlot.  
  // This wil make a new dataset with sWeights added for every event.
  DoSPlot(wspace, nentries);

  // Make some plots showing the discriminating variable and 
  // the control variable after unfolding.
  MakePlots(wspace);

  // cleanup
  delete wspace;

}

//____________________________________
void AddModel(RooWorkspace* ws, float nentries){

  // Make models for signal and background 

  Double_t lowRange, highRange, massLow, massHigh, massCentral;
  // set range of observable
  massLow     = 5360.;
  massHigh    = 5375.;
  massCentral = 5366.;
  lowRange    = 5250.;
  highRange   = 5500.;

  // make a RooRealVar for the observables
  RooRealVar invMass("resMass", "resMass", lowRange, highRange,"MeV");

  /////////////////////////////////////////////
  // make 1-d model for signal including the invariant mass 
  std::cout << "make signal model" << std::endl;
  // mass model for signal Gaussian
  RooRealVar mean("mean", "signal mass", massCentral, massLow, massHigh);
  RooRealVar sigma("sigma", "Width of signal", 10.0, 5.0, 35.0);
  //RooRealVar alpha1("alpha1", "alpha1", 0.8, 0., 3.0);
  //RooRealVar alpha2("alpha2", "alpha2", -0.8, -1.5, 0.);
  //RooRealVar n1 = RooRealVar("n1", "n1", 10., 0.2, 60.);
  //RooRealVar n2 = RooRealVar("n2", "n2", 10., 1.2, 60.);
  //RooCBShape *sig1 = new RooCBShape("sig1", "signal CB", invMass, mean, sigma, alpha1, n1);
  //RooCBShape *sig2 = new RooCBShape("sig2", "signal CB", invMass, mean, sigma, alpha2, n2);
  //RooRealVar frac = RooRealVar("frac","frac",0.5,0.,1.);
  //RooCBShape *SigModel = new RooCBShape("sig", "signal CB", invMass, mean, sigma, alpha2, n2);
  RooGaussian *SigModel = new RooGaussian("sig", "signal CB", invMass, mean, sigma);

  // make background model

  std::cout << "make background model" << std::endl;
  RooRealVar a1("a1","a1",0.3,-1,1) ;
  RooRealVar a2("a2","a2",-0.1,-1,1) ;
  RooRealVar a3("a3","a3",-0.01,-1,1) ;
  RooChebychev *BkgModel = new RooChebychev("bkg","background", invMass, RooArgSet(a1,a2,a3));

  //////////////////////////////////////////////
  // combined model
  // These variables represent the number of signal or background events
  // They will be fitted.
  RooRealVar SigYield("SigYield","fitted yield for Signal", nentries*0.1, 0., 0.3*nentries) ;
  RooRealVar BkgYield("BkgYield","fitted yield for Background", nentries*0.9, 0., 0.9*nentries) ;
  SigYield.setError(sqrt(nentries));
  BkgYield.setError(sqrt(nentries));

  // now make the combined model
  std::cout << "make full model" << std::endl;
  RooAddPdf model("model","signal+background models", RooArgList(*SigModel,*BkgModel), RooArgList(SigYield,BkgYield));

  // interesting for debugging and visualizing the model
  model.graphVizTree("fullModel.dot");

  std::cout << "import model" << std::endl;
  ws->import(model);

  delete SigModel;
  delete BkgModel;
}

//____________________________________
void AddData(RooWorkspace* ws){
  // Add data from nutples

  TChain *fChain;
  // use the ntuples that are cleaned in Ds
  fChain = new TChain("DecayTree");
  fChain->Add("/afs/cern.ch/user/r/rvazquez/RDS/DaVinciDev_v41r3/Phys/BsDsMuNuForRDS/PhotonEff/BsMassForPhotonEff_WithSWeighted_Den_Fixed.root");

  Double_t bsm;
  Double_t dsm;
  Double_t dsgpim;
  Double_t dsgm;
  Double_t gP;
  Double_t gPT;
  Double_t gMult;
  Double_t pibachpid;
  Double_t pipid;
  Double_t pibachpt;  
  Double_t sigden;
  Double_t bkgden;

  TBranch   *b_bsm;
  TBranch   *b_dsm;
  TBranch   *b_dsgpim;
  TBranch   *b_dsgm;
  TBranch   *b_gP;   
  TBranch   *b_gPT;
  TBranch   *b_gMult;
  TBranch   *b_pibachpid;
  TBranch   *b_pipid;
  TBranch   *b_pibachpt;   
  TBranch   *b_sigden;
  TBranch   *b_bkgden;

  fChain->SetBranchStatus("*",1);
  fChain->SetBranchAddress("BMass", &bsm, &b_bsm);
  fChain->SetBranchAddress("DsMass", &dsm, &b_dsm);
  fChain->SetBranchAddress("MassDsGPi", &dsgpim, &b_dsgpim);
  fChain->SetBranchAddress("MassDsG", &dsgm, &b_dsgm);
  fChain->SetBranchAddress("Gamma_P", &gP, &b_gP);
  fChain->SetBranchAddress("Gamma_PT", &gPT, &b_gPT);
  fChain->SetBranchAddress("Gamma_mult", &gMult, &b_gMult);
  fChain->SetBranchAddress("piBachPT", &pibachpt, &b_pibachpt);
  fChain->SetBranchAddress("piBachPIDK", &pibachpid, &b_pibachpid);
  fChain->SetBranchAddress("piPIDK", &pipid, &b_pipid);
  fChain->SetBranchAddress("sigden", &sigden, &b_sigden);
  fChain->SetBranchAddress("bkgden", &bkgden, &b_bkgden);

  RooRealVar *fitMass = new RooRealVar("resMass", "resMass", 5250., 5500.);
  RooRealVar *bsmass = new RooRealVar("bsmass", "bsm", 4800., 6000.);
  RooRealVar *dsgpimass = new RooRealVar("dsgpimass", "dsgpim", 4800., 6000.);
  RooRealVar *dsgmass = new RooRealVar("dsgmass", "dsgm", 2000., 2500.);
  RooRealVar *d = new RooRealVar("d", "d", -1., 1.); 
  RooRealVar *gammaPT = new RooRealVar("gammaPT", "gammaPT", 0., 10000.);
  RooRealVar *gammaP = new RooRealVar("gammaP", "gammaP", 0., 100000.);
  RooRealVar *sigDen = new RooRealVar("sigDen", "sigDen", -100., 100.);
  RooRealVar *bkgDen = new RooRealVar("bkgDen", "bkgDen", -100., 100.);

  RooArgSet vars;
  vars.add(RooArgSet(*fitMass,*bsmass,*dsgpimass,*dsgmass));
  vars.add(RooArgSet(*gammaPT,*gammaP,*sigDen,*bkgDen));

  RooDataSet *data = new RooDataSet("dataset", "dataset", vars);
  for(int i = 0; i!=fChain->GetEntries(); ++i){
    if (i%1000000 == 0) std::cout << "--- ... Processing event: " << i << std::endl;
    fChain->GetEntry(i);
    bool cuts;
    //cuts = Bs_MM < 5366 && det < 0 && mDsGPi < 5500 && mDsGPi > 5250 && gamma_mult>0 && sqrt(pow(gamma_PX,2)+pow(gamma_PY,2))>0;
    cuts = bsm < 5600 && bsm > 5000 && (dsgpim-dsgm+2112.1) < 5500 && (dsgpim-dsgm+2112.1) > 5250 && gMult>0 && (dsgm-dsm+1968.28)<2200 && (dsgm-dsm+1968.28)>2050 && pibachpid<0 && pipid<0 && pibachpt>1000;
    //cuts = bsm < 5600 && bsm > 5000 && gMult>0 && (dsgm-dsm+1968.28)<2200 && (dsgm-dsm+1968.28)>2050 && pibachpid<0 && pipid<0 && pibachpt>1000;
    if (cuts) {
      *fitMass = dsgpim-dsgm+2112.1;
      *bsmass = bsm;
      *dsgpimass = dsgpim;
      *dsgmass = dsgm; 
      *gammaPT = gPT;
      *gammaP = gP;
      *sigDen = sigden;
      *bkgDen = bkgden;

      RooArgSet upvars;
      upvars.add(RooArgSet(*fitMass,*bsmass,*dsgmass));
      upvars.add(RooArgSet(*gammaPT,*gammaP,*sigDen,*bkgDen,*dsgpimass));
      data->add(upvars);
    }
  }

  data->Print("v");
  ws->import(*data);

  delete data;
}

//____________________________________
void DoSPlot(RooWorkspace* ws, float nentries){
  std::cout << "Calculate sWeights" << std::endl;

  // get what we need out of the workspace to do the fit
  RooAbsPdf *model = ws->pdf("model");
  RooRealVar *SigYield = ws->var("SigYield");
  RooRealVar *BkgYield = ws->var("BkgYield");
  RooDataSet *data = (RooDataSet*) ws->data("dataset");
  //RooRealVar *weight = (RooRealVar*) data->addColumn(ws->var("sigden"));


  Double_t nen = data->sumEntries();
  std::cout << "The dataset has " << nen << " entries" << std::endl;

  // fit the model to the data.
  model->fitTo(*data, Extended(true), SumW2Error(kTRUE), Minos(true), Strategy(2), Timer(kTRUE), NumCPU(4));

  std::cout << "The fit is done" << std::endl;
  // The sPlot technique requires that we fix the parameters
  // of the model that are not yields after doing the fit.
  RooRealVar* sig = ws->var("sigma");
  RooRealVar* masa = ws->var("mean");
  sig->setConstant();
  masa->setConstant();
  RooRealVar* bkga1 = ws->var("a1");
  RooRealVar* bkga2 = ws->var("a2");
  RooRealVar* bkga3 = ws->var("a3");
  bkga1->setConstant();
  bkga2->setConstant();
  bkga3->setConstant();
  RooMsgService::instance().setSilentMode(false);

  // Now we use the SPlot class to add SWeights to our data set
  // based on our model and our yield variables
  std::cout << "Start the splot" << std::endl;
  RooStats::SPlot* sData = new RooStats::SPlot("sData","An SPlot", *data, model, RooArgList(*SigYield,*BkgYield));

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
  TFile *file = new TFile("BsMassForPhotonEff_WithSWeighted_Num_Fixed.root","RECREATE");
  TTree *finalTree = new TTree("DecayTree","tree with weights");

  Double_t sigw, bkgw, sigwden, bkgwden;
  Double_t MassDsGPi, MassBs, MassDsG, Gamma_P, Gamma_PT;

  finalTree->Branch("signum",&sigw,"signum/D");
  finalTree->Branch("bkgnum",&bkgw,"bkgnum/D");
  finalTree->Branch("MassDsGPi",&MassDsGPi,"MassDsGPi/D");
  finalTree->Branch("MassBs",&MassBs,"MassBs/D");
  finalTree->Branch("MassDsG",&MassDsG,"MassDsG/D");
  finalTree->Branch("Gamma_P",&Gamma_P,"Gamma_P/D");
  finalTree->Branch("Gamma_PT",&Gamma_PT,"Gamma_PT/D");
  finalTree->Branch("sigden",&sigwden,"sigden/D");
  finalTree->Branch("bkgden",&bkgwden,"bkgden/D");

  for (int i = 0; i!=nen; ++i){
    const RooArgSet *Dset = data->get(i);  // get the row
    MassDsGPi = Dset->getRealValue("dsgpimass");
    MassDsG = Dset->getRealValue("dsgmass");
    MassBs = Dset->getRealValue("bsmass");
    Gamma_P = Dset->getRealValue("gammaP");
    Gamma_PT = Dset->getRealValue("gammaPT");
    sigw = Dset->getRealValue("SigYield_sw");
    bkgw = Dset->getRealValue("BkgYield_sw");
    sigwden = Dset->getRealValue("sigDen");
    bkgwden = Dset->getRealValue("bkgDen");
    finalTree->Fill();
  }
  finalTree->Write();
}

void MakePlots(RooWorkspace* ws){

  // Here we make plots of the discriminating variable (mass) after the fit
  // and of the control variable (isolation) after unfolding with sPlot.
  std::cout << "make plots" << std::endl;

  // get what we need out of the workspace
  RooAbsPdf* model = ws->pdf("model");
  RooAbsPdf* SigModel = ws->pdf("sig");
  RooAbsPdf* BkgModel = ws->pdf("bkg");

  // get the variables
  RooRealVar* invMass = ws->var("resMass");
  RooRealVar* gP = ws->var("gammaP");

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
  frame1_1 = invMass->frame(5250.,5500.,50);
  data->plotOn(frame1_1,MarkerStyle(1)) ;
  model->plotOn(frame1_1,LineColor(kBlue),LineWidth(1));//,NormRange("FitRange")) ;   
  model->plotOn(frame1_1,Components(*SigModel),LineStyle(kDashed),LineColor(kRed)) ;
  model->plotOn(frame1_1,Components(*BkgModel),LineStyle(kDashed),LineColor(kGreen)) ;
  frame1_1->SetTitle("Fit of model to discriminating variable");
  frame1_1->Draw() ;
  std::cout << "drawn" << std::endl;
/*
  // Plot Ds_MM for signal component.  
  // Do this by plotting all events weighted by the sWeight for the signal component.
  // The SPlot class adds a new variable that has the name of the corresponding
  // yield + "_sw".
  cdata1->cd(2);
  RooDataSet *dataw_sig_1 = new RooDataSet(data->GetName(),data->GetTitle(),data,*data->get(),0,"SigYield_sw") ;
  RooPlot* frame2_1;
  frame2_1 = gP->frame(0.,15000.,50);
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
  frame3_1 = gP->frame(0.,15000.,50);
  dataw_bkg_1->plotOn(frame3_1,DataError(RooAbsData::SumW2), MarkerStyle(1) ) ;
  frame3_1->SetTitle("Corrected mass distribution for background");
  frame3_1->Draw() ;
*/
  cdata1->SaveAs("SPlot_MDsGPi_Num.pdf");

  delete cdata1;
}

float getEntries(){
  int nentries;
  TChain *fChain;
  fChain = new TChain("DecayTree");
  fChain->Add("/afs/cern.ch/user/r/rvazquez/RDS/DaVinciDev_v41r3/Phys/BsDsMuNuForRDS/PhotonEff/BsMassForPhotonEff_WithSWeighted_Den_Fixed.root");
  nentries = fChain->GetEntries();
  std::cout << "Total number of entries is = " << nentries << std::endl;
  delete fChain;
  return nentries;
}

