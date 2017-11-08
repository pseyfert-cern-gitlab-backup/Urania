#ifndef __CINT__
#include "TSystem.h"
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
#include "RooGenericPdf.h"
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
#include "RooThresholdDeltaM.h"

// #################
// ##### INFO ######  
// This code does the splots of the Ds*gamma mass 
// ################# 

// use this order for safety on library loading
using namespace RooFit ;
using namespace RooStats ;

// see below for implementation
void AddModel(RooWorkspace*, float);
void AddData(RooWorkspace*, float, TString);
void DoSPlot(RooWorkspace*, float);
void MakePlots(RooWorkspace*, TString);
float getEntries();

void splotPhotonEff(TString type){

  // Create a new workspace to manage the project.
  RooWorkspace* wspace = new RooWorkspace("myWS");

  // add the signal and background models to the workspace.
  // Inside this function you will find a discription our model.
  float nentries = getEntries(); 
  //float nentries = 200000;
  AddModel(wspace, nentries);

  // add data to the workspace
  AddData(wspace, nentries, type);

  // inspect the workspace if you wish
  wspace->Print();

  // do sPlot.  
  // This wil make a new dataset with sWeights added for every event.
  DoSPlot(wspace, nentries);

  // Make some plots showing the discriminating variable and 
  // the control variable after unfolding.
  MakePlots(wspace, type);

  // cleanup
  delete wspace;

}

//____________________________________
void AddModel(RooWorkspace* ws, float nentries){

  // Make models for signal and background 

  Double_t lowRange, highRange, massLow, massHigh, massCentral;
  // set range of observable
  massLow = 2110.1;
  massHigh = 2114.1;
  massCentral = 2112.1;
  lowRange = 2050.;
  highRange = 2250.;
  //massLow = 2455.5;
  //massHigh = 2463.5;
  //massCentral = 2459.5;
  //lowRange = 2350.;
  //highRange = 2600.;

  // make a RooRealVar for the observables
  RooRealVar invMass("resMass", "resMass", lowRange, highRange,"MeV");
 
  /////////////////////////////////////////////
  // make 1-d model for signal including the invariant mass 
  std::cout << "make signal model" << std::endl;
  // mass model for signal Gaussian
  RooRealVar mean("mean", "signal mass", massCentral, massLow, massHigh);
  RooRealVar sigma("sigma", "Width of signal", 10.0, 3.0, 15.0);
  RooRealVar alpha1("alpha1", "alpha1", 0.8, 0., 3.0);
  RooRealVar alpha2("alpha2", "alpha2", -0.8, -2.0, 0.);
  RooRealVar n1 = RooRealVar("n1", "n1", 10., 3., 50.);
  RooRealVar n2 = RooRealVar("n2", "n2", 5., 3., 60.);
  RooCBShape *sig1 = new RooCBShape("sig1", "signal CB", invMass, mean, sigma, alpha1, n1);
  RooCBShape *sig2 = new RooCBShape("sig2", "signal CB", invMass, mean, sigma, alpha2, n2);
  RooRealVar frac = RooRealVar("frac","frac",0.5,0.,1.);
  //RooGaussian *SigModel = new RooGaussian("sig", "signal CB", invMass, mean, sigma);
  RooCBShape *SigModel = new RooCBShape("sig", "signal CB", invMass, mean, sigma, alpha2, n2);

  // make background model 
  // move from Exponential to RooThreshold for photon calibration sample
  std::cout << "make background model" << std::endl;
  
  RooRealVar a1("a1","a1",-0.6,-1,0.5) ;
  RooRealVar a2("a2","a2",0.1,-0.3,0.3) ;
  RooRealVar a3("a3","a3",-0.04,-0.3,0.3) ;
  RooChebychev *BkgModel = new RooChebychev("bkg","background", invMass, RooArgSet(a1,a2,a3));
  
  /*  
  RooRealVar c = RooRealVar("c", "c", -0.0006, -0.01, 0.);
  RooExponential *BkgModel = new RooExponential("bkg", "exponential 1", invMass, c);
  RooRealVar *thMass;
  thMass = new RooRealVar("thMass", "thMass", 2000, 1900, 2150, "MeV/c^{2}");
  RooRealVar thSigma = RooRealVar("thSigma", "thSigma", 80, 10, 120, "MeV/c^{2}");
  RooFormulaVar *thres = new RooFormulaVar("eff","0.5*(TMath::Erf((resMass-thMass)/thSigma)+1)",RooArgList(invMass,*thMass,thSigma)) ;
  //RooEffProd *BkgModel = new RooEffProd("bkg", "background", *expo, *thres);
  */
  
  //////////////////////////////////////////////
  // combined model
  // These variables represent the number of signal or background events
  // They will be fitted.
  RooRealVar SigYield("SigYield","fitted yield for Signal", nentries*0.12, 0., 0.3*nentries) ; 
  RooRealVar BkgYield("BkgYield","fitted yield for Background", nentries*0.88, 0., 0.7*nentries) ; 
  SigYield.setError(sqrt(nentries));
  BkgYield.setError(sqrt(nentries));

  // now make the combined model
  std::cout << "make full model" << std::endl;
  RooAddPdf model("model","signal+background models", RooArgList(*SigModel,*BkgModel), RooArgList(SigYield,BkgYield));
  //RooAddPdf model("model","signal+background models", RooArgList(*BkgModel), RooArgList(BkgYield)); // only bkg

  // interesting for debugging and visualizing the model
  model.graphVizTree("fullModel.dot");

  std::cout << "import model" << std::endl;
  ws->import(model);

  delete SigModel;
  delete BkgModel; 
}

//____________________________________
void AddData(RooWorkspace* ws, float nentries, TString type){
  // Add data from nutples
  
  TChain *fChain; 
  // use the ntuples that are cleaned in Ds
  fChain = new TChain("B2DsMuNuTuple/DecayTree");
  fChain->Add("/afs/cern.ch/user/r/rvazquez/gangadir/workspace/rvazquez/LocalXML/1448/photonControl.root");

  Double_t        Ds_PT;
  Double_t        Ds_MM;
  Double_t        Ds_PE;
  Double_t        Ds_PX;
  Double_t        Ds_PY;
  Double_t        Ds_PZ;
  Double_t        Ds_0_40_nc_maxPt_PT;
  Double_t        Ds_0_40_nc_maxPt_PX;
  Double_t        Ds_0_40_nc_maxPt_PY;
  Double_t        Ds_0_40_nc_maxPt_PZ;
  Double_t        Ds_0_40_nc_maxPt_PE;
  Int_t           Ds_0_40_nc_mult;
  Double_t        Ds_0_40_nc_CL;
  Double_t        Ds_0_40_nc_radius;
  Double_t        Ds_0_40_nc_secPt_PX;
  Double_t        Ds_0_40_nc_secPt_PY;
  Double_t        Ds_0_40_nc_secPt_PZ;
  Double_t        Ds_0_40_nc_secPt_PE;

  TBranch        *b_Ds_PT;   //!
  TBranch        *b_Ds_MM;   //!
  TBranch        *b_q2;    //!
  TBranch        *b_Ds_PE;   //!
  TBranch        *b_Ds_PX;   //!
  TBranch        *b_Ds_PY;   //!
  TBranch        *b_Ds_PZ;   //!
  TBranch        *b_Ds_0_40_nc_maxPt_PT;
  TBranch        *b_Ds_0_40_nc_maxPt_PX;
  TBranch        *b_Ds_0_40_nc_maxPt_PY;
  TBranch        *b_Ds_0_40_nc_maxPt_PZ;
  TBranch        *b_Ds_0_40_nc_maxPt_PE;
  TBranch        *b_Ds_0_40_nc_mult;   //!
  TBranch        *b_Ds_0_40_nc_CL;   //!
  TBranch        *b_Ds_0_40_nc_radius;
  TBranch        *b_Ds_0_40_nc_secPt_PX;
  TBranch        *b_Ds_0_40_nc_secPt_PY;
  TBranch        *b_Ds_0_40_nc_secPt_PZ;
  TBranch        *b_Ds_0_40_nc_secPt_PE;

  fChain->SetBranchStatus("*",1);
  fChain->SetBranchAddress("Ds_PT", &Ds_PT, &b_Ds_PT);
  fChain->SetBranchAddress("Ds_MM", &Ds_MM, &b_Ds_MM);
  fChain->SetBranchAddress("Ds_PE", &Ds_PE, &b_Ds_PE);
  fChain->SetBranchAddress("Ds_PX", &Ds_PX, &b_Ds_PX);
  fChain->SetBranchAddress("Ds_PY", &Ds_PY, &b_Ds_PY);
  fChain->SetBranchAddress("Ds_PZ", &Ds_PZ, &b_Ds_PZ);
  fChain->SetBranchAddress("Ds_0.40_nc_maxPt_PT", &Ds_0_40_nc_maxPt_PT, &b_Ds_0_40_nc_maxPt_PT);
  fChain->SetBranchAddress("Ds_0.40_nc_maxPt_PX", &Ds_0_40_nc_maxPt_PX, &b_Ds_0_40_nc_maxPt_PX);
  fChain->SetBranchAddress("Ds_0.40_nc_maxPt_PY", &Ds_0_40_nc_maxPt_PY, &b_Ds_0_40_nc_maxPt_PY);
  fChain->SetBranchAddress("Ds_0.40_nc_maxPt_PZ", &Ds_0_40_nc_maxPt_PZ, &b_Ds_0_40_nc_maxPt_PZ);
  fChain->SetBranchAddress("Ds_0.40_nc_maxPt_PE", &Ds_0_40_nc_maxPt_PE, &b_Ds_0_40_nc_maxPt_PE);
  fChain->SetBranchAddress("Ds_0.40_nc_CL", &Ds_0_40_nc_CL, &b_Ds_0_40_nc_CL);
  fChain->SetBranchAddress("Ds_0.40_nc_mult", &Ds_0_40_nc_mult, &b_Ds_0_40_nc_mult);
  fChain->SetBranchAddress("Ds_0.40_nc_radius", &Ds_0_40_nc_radius, &b_Ds_0_40_nc_radius);
  fChain->SetBranchAddress("Ds_0.40_nc_secPt_PX", &Ds_0_40_nc_secPt_PX, &b_Ds_0_40_nc_secPt_PX);
  fChain->SetBranchAddress("Ds_0.40_nc_secPt_PY", &Ds_0_40_nc_secPt_PY, &b_Ds_0_40_nc_secPt_PY);
  fChain->SetBranchAddress("Ds_0.40_nc_secPt_PZ", &Ds_0_40_nc_secPt_PZ, &b_Ds_0_40_nc_secPt_PZ);
  fChain->SetBranchAddress("Ds_0.40_nc_secPt_PE", &Ds_0_40_nc_secPt_PE, &b_Ds_0_40_nc_secPt_PE);

  RooRealVar *fitMass;
  fitMass = new RooRealVar("resMass", "resMass", 2050., 2250.);
  RooRealVar *dspt = new RooRealVar("dspt", "dspt", 0.,10000000.);
  RooRealVar *dsmm = new RooRealVar("dsmm", "dsmm", 1940., 2000.);
  RooRealVar *ncmult = new RooRealVar("ncmult", "ncmult", 0., 20.);
  RooRealVar *ncpt = new RooRealVar("ncpt", "ncpt", 0., 10000000.);
  RooRealVar *ncpx = new RooRealVar("ncpx", "ncpx", -10000000., 10000000.);
  RooRealVar *ncpy = new RooRealVar("ncpy", "ncpy", -10000000., 10000000.);
  RooRealVar *ncpz = new RooRealVar("ncpz", "ncpz", -10000000., 10000000.);
  RooRealVar *ncpe = new RooRealVar("ncpe", "ncpe", 0., 10000000.);
  RooRealVar *secpx = new RooRealVar("secpx", "secpx", -10000000., 10000000.);
  RooRealVar *secpy = new RooRealVar("secpy", "secpy", -10000000., 10000000.);
  RooRealVar *secpz = new RooRealVar("secpz", "secpz", -10000000., 10000000.);
  RooRealVar *secpe = new RooRealVar("secpe", "secpe", 0., 10000000.);
  RooRealVar *ncCL = new RooRealVar("ncCL", "ncCL", 0., 1.);
  RooRealVar *ncrad = new RooRealVar("ncrad", "ncrad", 0., 4.);
  RooRealVar *dspe = new RooRealVar("dspe", "dspe", 0., 10000000.);
  RooRealVar *dspx = new RooRealVar("dspx", "dspx", -10000000., 10000000.);
  RooRealVar *dspy = new RooRealVar("dspy", "dspy", -10000000., 10000000.);
  RooRealVar *dspz = new RooRealVar("dspz", "dspz", -10000000., 10000000.);
  RooRealVar *MassDsG = new RooRealVar("MassDsG", "MassDsG", 0., 3000.);
  RooRealVar *helicity = new RooRealVar("helicity", "helicity", -1.1 ,1.1);
 
  RooArgSet vars;
  vars.add(RooArgSet(*fitMass,*dsmm));
  vars.add(RooArgSet(*ncmult,*ncpt,*ncpx,*ncpy,*ncpz,*ncpe,*ncCL,*ncrad));
  vars.add(RooArgSet(*secpx,*secpy,*secpz,*secpe));
  vars.add(RooArgSet(*dspe,*dspx,*dspy,*dspz)); 
  vars.add(RooArgSet(*helicity));
  vars.add(RooArgSet(*MassDsG));
  RooDataSet *data = new RooDataSet("dataset", "dataset", vars);

  Double_t DsMassPDG(1968.27);
  std::cout << "Imported vars" << std::endl;
  // Fill for Dsst
  for(int i = 0; i!=nentries; ++i){
    if (i%1000000 == 0) std::cout << "--- ... Processing event: " << i << std::endl;
    fChain->GetEntry(i);
    // apply the cuts to add only good data
    bool cuts;
    if(type=="max"){
      cuts = Ds_MM>1940 && Ds_MM<2000 && Ds_0_40_nc_mult>0 && sqrt(pow(Ds_0_40_nc_maxPt_PX,2)+pow(Ds_0_40_nc_maxPt_PY,2))>0;
    }
    if(type=="sec"){
      cuts = Ds_MM>1940 && Ds_MM<2000 && Ds_0_40_nc_mult>0 && sqrt(pow(Ds_0_40_nc_secPt_PX,2)+pow(Ds_0_40_nc_secPt_PY,2))>0;
    }
    if (cuts) {
      float mass;
      if(type=="max"){
        mass = sqrt( pow((Ds_0_40_nc_maxPt_PE+Ds_PE),2) - ( pow(Ds_0_40_nc_maxPt_PX+Ds_PX,2)+pow(Ds_0_40_nc_maxPt_PY+Ds_PY,2)+pow(Ds_0_40_nc_maxPt_PZ+Ds_PZ,2) ) )-Ds_MM+DsMassPDG;
      }
      if(type=="sec"){
        mass = sqrt( pow((Ds_0_40_nc_secPt_PE+Ds_PE),2) - ( pow(Ds_0_40_nc_secPt_PX+Ds_PX,2)+pow(Ds_0_40_nc_secPt_PY+Ds_PY,2)+pow(Ds_0_40_nc_secPt_PZ+Ds_PZ,2) ) )-Ds_MM+DsMassPDG;
      } 
      if(mass < 2050. || mass > 2250.) continue; // for Ds*
      //if(mass < 2350. || mass > 2600.) continue; 
      if(type=="max"){
        *fitMass = sqrt( pow((Ds_0_40_nc_maxPt_PE+Ds_PE),2) - ( pow(Ds_0_40_nc_maxPt_PX+Ds_PX,2)+pow(Ds_0_40_nc_maxPt_PY+Ds_PY,2)+pow(Ds_0_40_nc_maxPt_PZ+Ds_PZ,2) ) )-Ds_MM+DsMassPDG;
      }
      if(type=="sec"){
        *fitMass = sqrt( pow((Ds_0_40_nc_secPt_PE+Ds_PE),2) - ( pow(Ds_0_40_nc_secPt_PX+Ds_PX,2)+pow(Ds_0_40_nc_secPt_PY+Ds_PY,2)+pow(Ds_0_40_nc_secPt_PZ+Ds_PZ,2) ) )-Ds_MM+DsMassPDG;
      }
      *dspt = Ds_PT;
      *dsmm = Ds_MM;
      *ncmult = Ds_0_40_nc_mult;
      *ncpt = Ds_0_40_nc_maxPt_PT;
      *ncpx = Ds_0_40_nc_maxPt_PX;
      *ncpy = Ds_0_40_nc_maxPt_PY;
      *ncpz = Ds_0_40_nc_maxPt_PZ; 
      *ncpe = Ds_0_40_nc_maxPt_PE;
      *secpx = Ds_0_40_nc_secPt_PX;
      *secpy = Ds_0_40_nc_secPt_PY;
      *secpz = Ds_0_40_nc_secPt_PZ;
      *secpe = Ds_0_40_nc_secPt_PE;
      *ncCL = Ds_0_40_nc_CL;
      *ncrad = Ds_0_40_nc_radius;
      *dspe = Ds_PE;
      *dspx = Ds_PX;
      *dspy = Ds_PY;
      *dspz = Ds_PZ;
      // compute the helicity angle
      TLorentzVector gamma(Ds_0_40_nc_maxPt_PX,Ds_0_40_nc_maxPt_PY,Ds_0_40_nc_maxPt_PZ,Ds_0_40_nc_maxPt_PE);
      TLorentzVector Dsst(Ds_PX+Ds_0_40_nc_maxPt_PX,Ds_PY+Ds_0_40_nc_maxPt_PY,Ds_PZ+Ds_0_40_nc_maxPt_PZ,Ds_PE+Ds_0_40_nc_maxPt_PE);        
      gamma.Boost(-Dsst.BoostVector());
      Double_t angle = cos(gamma.Vect().Angle(Dsst.BoostVector()));
      *helicity = angle;
      *MassDsG = sqrt(((Ds_PE+Ds_0_40_nc_maxPt_PE)*(Ds_PE+Ds_0_40_nc_maxPt_PE)-
                     (Ds_PX+Ds_0_40_nc_maxPt_PX)*(Ds_PX+Ds_0_40_nc_maxPt_PX)-
                     (Ds_PY+Ds_0_40_nc_maxPt_PY)*(Ds_PY+Ds_0_40_nc_maxPt_PY)-
                     (Ds_PZ+Ds_0_40_nc_maxPt_PZ)*(Ds_PZ+Ds_0_40_nc_maxPt_PZ))/1000000)-
                     Ds_MM/1000+DsMassPDG/1000;
      RooArgSet upvars(*fitMass, *dsmm);
      upvars.add(RooArgSet(*ncmult,*ncpt,*ncpx,*ncpy,*ncpz,*ncpe,*ncCL,*ncrad));
      upvars.add(RooArgSet(*secpx,*secpy,*secpz,*secpe));
      upvars.add(RooArgSet(*dspe,*dspx,*dspy,*dspz));
      upvars.add(RooArgSet(*MassDsG));
      upvars.add(RooArgSet(*helicity));
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
  RooAbsPdf* model = ws->pdf("model");
  RooRealVar* SigYield = ws->var("SigYield");
  RooRealVar* BkgYield = ws->var("BkgYield");
  RooDataSet* data = (RooDataSet*) ws->data("dataset");
 
  Double_t nen = data->sumEntries();
  std::cout << "The dataset has " << nen << " entries" << std::endl; 

  // fit the model to the data.
  model->fitTo(*data, Extended(true), SumW2Error(kTRUE), Minos(true), Strategy(2), Timer(kTRUE), NumCPU(4)); 
   
  std::cout << "The fit is done" << std::endl;
  // The sPlot technique requires that we fix the parameters
  // of the model that are not yields after doing the fit.
  RooRealVar* sig = ws->var("sigma");
  RooRealVar* masa = ws->var("mean");
  //RooRealVar* al1 = ws->var("alpha1");
  //RooRealVar* N1 = ws->var("n1");
  RooRealVar* al2 = ws->var("alpha2");
  RooRealVar* N2 = ws->var("n2");
  sig->setConstant();
  masa->setConstant();
  //al1->setConstant();
  //N1->setConstant();
  al2->setConstant();
  N2->setConstant();
  //RooRealVar* bkgc = ws->var("c");
  RooRealVar* bkga1 = ws->var("a1");
  RooRealVar* bkga2 = ws->var("a2");
  RooRealVar* bkga3 = ws->var("a3"); 
 
  //RooRealVar* thM = ws->var("thMass");
  //RooRealVar* thSig = ws->var("thSigma");
  //bkgc->setConstant();
  bkga1->setConstant();
  bkga2->setConstant();
  bkga3->setConstant();
  //thM->setConstant();
  //thSig->setConstant(); 
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
  TFile *file = new TFile("DsMass_WithSWeighted_PhotonEff_Cheb.root","RECREATE");
  TTree *finalTree = new TTree("DecayTree","tree with weights");
  
  Double_t dspt, dsmm;
  Double_t ncmult, ncpt, ncpx, ncpy, ncpz, ncpe, ncCL, ncrad;
  Double_t secpx, secpy, secpz, secpe;
  Double_t dspe, dspx, dspy, dspz;
  Double_t sigw, bkgw;
  Double_t MassDsG;
  Double_t MassDsPi0;
  Double_t hel;

  finalTree->Branch("sigw",&sigw,"sigw/D");
  finalTree->Branch("bkgw",&bkgw,"bkgw/D");
  finalTree->Branch("MassDsG",&MassDsG,"MassDsG/D");
  finalTree->Branch("Ds_PT", &dspt, "Ds_PT/D");
  finalTree->Branch("Ds_MM", &dsmm, "Ds_MM/D");
  finalTree->Branch("Ds_0.40_nc_mult", &ncmult, "Ds_0.40_nc_mult/I");
  finalTree->Branch("Ds_0.40_nc_maxPt_PX", &ncpx, "Ds_0.40_nc_maxPt_PX/D");
  finalTree->Branch("Ds_0.40_nc_maxPt_PY", &ncpy, "Ds_0.40_nc_maxPt_PY/D");
  finalTree->Branch("Ds_0.40_nc_maxPt_PZ", &ncpz, "Ds_0.40_nc_maxPt_PZ/D");
  finalTree->Branch("Ds_0.40_nc_maxPt_PE", &ncpe, "Ds_0.40_nc_maxPt_PE/D");
  finalTree->Branch("Ds_0.40_nc_secPt_PX", &secpx, "Ds_0.40_nc_secPt_PX/D");
  finalTree->Branch("Ds_0.40_nc_secPt_PY", &secpy, "Ds_0.40_nc_secPt_PY/D");
  finalTree->Branch("Ds_0.40_nc_secPt_PZ", &secpz, "Ds_0.40_nc_secPt_PZ/D");
  finalTree->Branch("Ds_0.40_nc_secPt_PE", &secpe, "Ds_0.40_nc_secPt_PE/D");
  finalTree->Branch("Ds_0.40_nc_CL", &ncCL, "Ds_0.40_nc_CL/D");
  finalTree->Branch("Ds_0.40_nc_radius", &ncrad, "Ds_0.40_nc_radius/D");
  finalTree->Branch("Ds_0.40_nc_maxPt_PT", &ncpt, "Ds_0.40_nc_maxPt_PT/D");
  finalTree->Branch("Ds_PE", &dspe, "Ds_PE/D");
  finalTree->Branch("Ds_PX", &dspx, "Ds_PX/D");
  finalTree->Branch("Ds_PY", &dspy, "Ds_PY/D");
  finalTree->Branch("Ds_PZ", &dspz, "Ds_PZ/D");
  finalTree->Branch("Helicity", &hel, "Helicity/D");
  for (int i = 0; i!=nen; ++i){
    const RooArgSet *Dset = data->get(i);  // get the row
    sigw = Dset->getRealValue("SigYield_sw");
    bkgw = Dset->getRealValue("BkgYield_sw");
    dspt = Dset->getRealValue("dspt");
    dsmm = Dset->getRealValue("dsmm");
    ncmult = Dset->getRealValue("ncmult");
    ncpt = Dset->getRealValue("ncpt");
    ncpx = Dset->getRealValue("ncpx");
    ncpy = Dset->getRealValue("ncpy");
    ncpz = Dset->getRealValue("ncpz");
    ncpe = Dset->getRealValue("ncpe");
    secpx = Dset->getRealValue("secpx");
    secpy = Dset->getRealValue("secpy");
    secpz = Dset->getRealValue("secpz");
    secpe = Dset->getRealValue("secpe");
    ncCL = Dset->getRealValue("ncCL");
    ncrad = Dset->getRealValue("ncrad");
    dspe = Dset->getRealValue("dspe");
    dspx = Dset->getRealValue("dspx");
    dspy = Dset->getRealValue("dspy");
    dspz = Dset->getRealValue("dspz");
    hel = Dset->getRealValue("helicity");
    bkgw = Dset->getRealValue("BkgYield_sw");  
    MassDsG = Dset->getRealValue("MassDsG");
    finalTree->Fill();
  }
  finalTree->Write();
}

void MakePlots(RooWorkspace* ws, TString type){
  // Here we make plots of the discriminating variable (mass) after the fit
  // and of the control variable (isolation) after unfolding with sPlot.
  std::cout << "make plots" << std::endl;

  // get what we need out of the workspace
  RooAbsPdf* model = ws->pdf("model");
  RooAbsPdf* SigModel = ws->pdf("sig");
  RooAbsPdf* BkgModel = ws->pdf("bkg");

  // get the variables
  RooRealVar* invMass = ws->var("resMass");
  //RooRealVar* radius = ws->var("ncpt");
  RooRealVar* helicity = ws->var("helicity");

  // note, we get the dataset with sWeights
  RooDataSet* data = (RooDataSet*) ws->data("dataWithSWeights");

  // this shouldn't be necessary, need to fix something with workspace
  // do this to set parameters back to their fitted values.
  model->fitTo(*data, Extended(true), SumW2Error(kTRUE), Minos(true), Strategy(2), Timer(kTRUE), NumCPU(4));
  
  // make our canvases and plot
  TCanvas* cdata1 = new TCanvas("sPlotMCORR","sPlot MCORR", 600, 600);

  //plot invMass for data with full model and individual componenets overlayed
  RooPlot *frame_1;
  frame_1 = invMass->frame(2050.,2250.,200);
  data->plotOn(frame_1,MarkerStyle(1)) ;
  model->plotOn(frame_1,LineColor(kBlue),LineWidth(1));//,NormRange("FitRange")) ;   
  model->plotOn(frame_1,Components(*SigModel),LineStyle(kDashed),LineColor(kRed)) ;
  model->plotOn(frame_1,Components(*BkgModel),LineStyle(kDashed),LineColor(kGreen)) ;
  frame_1->SetTitle("Fit of model to discriminating variable");
  frame_1->Draw() ;
  cdata1->SaveAs("SPlot_PhotonEff_"+type+".pdf");

}

float getEntries(){
  int nentries;
  TChain *fChain;
  fChain = new TChain("B2DsMuNuTuple/DecayTree");
  fChain->Add("/afs/cern.ch/user/r/rvazquez/gangadir/workspace/rvazquez/LocalXML/1448/photonControl.root");
  nentries = fChain->GetEntries();
  std::cout << "Total number of entries is = " << nentries << std::endl;
  delete fChain;
  return nentries;
}
