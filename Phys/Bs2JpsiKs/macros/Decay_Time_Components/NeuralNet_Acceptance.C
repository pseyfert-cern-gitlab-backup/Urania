/////////////////////////////////////////////////////////////
// ***** Monte Carlo Acceptance after Neural Net Cut ***** //
/////////////////////////////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb
// - Study the B decay time acceptance (relative to stripping and/or selection) after applying the optimal neural net cut



/////////////////////////////////////
// ***** Load useful classes ***** //
/////////////////////////////////////

#include "RooAddModel.h"
#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooCategory.h"
#include "RooCBShape.h"
#include "RooDataSet.h"
#include "RooDecay.h"
#include "RooEfficiency.h"
#include "RooEffProd.h"
#include "RooExponential.h"
#include "RooFit.h"
#include "RooFitResult.h"
#include "RooGaussModel.h"
#include "RooPlot.h"
#include "RooRealVar.h"

#include "RooStats/SPlot.h"

#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMath.h"
#include "TNtuple.h"
#include "TPaveText.h"

using namespace RooFit;

//////////////////////////////
// ***** Declarations ***** //
//////////////////////////////

RooRealVar* Blife;
RooRealVar* accX;
RooRealVar* accY;
RooRealVar* accZ;
RooRealVar* accOffset;
RooRealVar* accVelo;

void LifetimeFit(double *Results_LL, double *Results_DD, TString setup, TString lifetype = "True", bool allPVs = false);
void FitPlotEff(TString label, TString tag, RooDataSet *Data, RooFormulaVar *acceptance, RooCategory *Dec, double *Results);
void FitPlotTau(TString label, TString tag, RooDataSet *Data, RooAbsPdf *decay, double *Results);
void PullPlot(TString savestring, RooPlot* frame, Int_t logy=0);

///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void NNefficiency(TString setup, TString efftype = "Abs", TString lifetype = "True", bool allPVs = false){

// ***** Initialize ***** //
////////////////////////////

  // Using Optimisation VIIb
  Double_t NNcut_LL = 0.60;
  Double_t NNcut_DD = 0.75;

  // *** Plot Ranges ***
  Double_t Bmass_min = 5180;
  Double_t Bmass_max = 5520;


// ***** Part I: From NTuple to DataSet ***** //
////////////////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Part I: From NTuple to DataSet ==" << std::endl;
  std::cout << "====================================" << std::endl;

  // ***** Load NTuples ***** //
  //////////////////////////////
	
  TFile* netFile = TFile::Open("B2JpsiKs-Eval-2-random-SigBd.root");
  TTree* neural_net = (TTree*)netFile->Get("NetTree");

  TChain* chain = new TChain("chain");
  chain->Add("B2JpsiKs-Slim-SigBd.root/Slim_B2JpsiKs_Tuple");
	chain->AddFriend(neural_net);
	
  Long64_t nEntries_NTuple = chain->GetEntries();
	//nEntries_NTuple = 10000;	
  std::cout << "Number of entries from DaVinci: " << nEntries_NTuple << std::endl;		


  // ***** Define DataSet Observables ***** //
  ////////////////////////////////////////////

  // *** Define Observables & Selection Variables ***
				
  // Observable
	Float_t B_FullFit_ctau[10];
  // Observables for Common Selection Cuts
  Float_t B_FullFit_M[10];
  Int_t piminus_TRACK_Type = -999;
  // PV Matching
  Double_t B_TRUEORIGINVERTEX_X = -999;
  Double_t B_TRUEORIGINVERTEX_Y = -999;
  Double_t B_TRUEORIGINVERTEX_Z = -999;
  Float_t B_FullFit_PV_X[10];
  Float_t B_FullFit_PV_Y[10];
  Float_t B_FullFit_PV_Z[10];
	// Trigger
  Bool_t PsiHlt1TrackMuonDecision_TOS = -999;
	Bool_t PsiHlt1DiMuonHighMassDecision_TOS = -999; 
	Bool_t PsiHlt1TrackAllL0Decision_TOS = -999;
  Bool_t PsiHlt2DiMuonDetachedJPsiDecision_TOS = -999; 
	Bool_t PsiHlt2DiMuonJPsiHighPTDecision_TOS = -999;
	Bool_t PsiHlt2DiMuonJPsiDecision_TOS = -999;
	Bool_t PsiHlt2TopoMu2BodyBBDTDecision_TOS = -999;	
  // Neural Net
  Float_t netOutput[10];
  Int_t nPV2 = -999;
	// True ID of Decay
  Int_t B_TRUEID = -999;
  Int_t Psi_TRUEID = -999;
  Int_t KS0_TRUEID = -999;
	Int_t B_BKGCAT = -999;
  Double_t B_TRUETAU = -999;


  // *** Initialize Arrays ***
  for(Int_t i=0; i<10; i++){
		B_FullFit_ctau[i] = -999;
    B_FullFit_M[i] = -999;
    B_FullFit_PV_X[i] = -999;
    B_FullFit_PV_Y[i] = -999;
    B_FullFit_PV_Z[i] = -999;
    netOutput[i] = -999;
  }


  // *** Set Branch Addresses ***
  // Observable
  chain->SetBranchAddress("B_FullFit_ctau", &B_FullFit_ctau);
  chain->SetBranchAddress("B_FullFit_M", &B_FullFit_M);
  chain->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type);
  // PV Matching
  chain->SetBranchAddress("B_TRUEORIGINVERTEX_X", &B_TRUEORIGINVERTEX_X);
  chain->SetBranchAddress("B_TRUEORIGINVERTEX_Y", &B_TRUEORIGINVERTEX_Y);
  chain->SetBranchAddress("B_TRUEORIGINVERTEX_Z", &B_TRUEORIGINVERTEX_Z);
  chain->SetBranchAddress("B_FullFit_PV_X", &B_FullFit_PV_X);
  chain->SetBranchAddress("B_FullFit_PV_Y", &B_FullFit_PV_Y);
  chain->SetBranchAddress("B_FullFit_PV_Z", &B_FullFit_PV_Z);
	// Trigger
  chain->SetBranchAddress("PsiHlt1TrackMuonDecision_TOS", &PsiHlt1TrackMuonDecision_TOS);
	chain->SetBranchAddress("PsiHlt1DiMuonHighMassDecision_TOS", &PsiHlt1DiMuonHighMassDecision_TOS);
	chain->SetBranchAddress("PsiHlt1TrackAllL0Decision_TOS", &PsiHlt1TrackAllL0Decision_TOS);	
  chain->SetBranchAddress("PsiHlt2DiMuonDetachedJPsiDecision_TOS", &PsiHlt2DiMuonDetachedJPsiDecision_TOS);
	chain->SetBranchAddress("PsiHlt2DiMuonJPsiHighPTDecision_TOS", &PsiHlt2DiMuonJPsiHighPTDecision_TOS);
	chain->SetBranchAddress("PsiHlt2DiMuonJPsiDecision_TOS", &PsiHlt2DiMuonJPsiDecision_TOS);
	chain->SetBranchAddress("PsiHlt2TopoMu2BodyBBDTDecision_TOS",&PsiHlt2TopoMu2BodyBBDTDecision_TOS);	
  // Neural Net
  chain->SetBranchAddress("netOutput", &netOutput);
  chain->SetBranchAddress("nPV2", &nPV2);
  // True ID of Decay
  chain->SetBranchAddress("B_TRUEID", &B_TRUEID);
  chain->SetBranchAddress("Psi_TRUEID", &Psi_TRUEID);
  chain->SetBranchAddress("KS0_TRUEID", &KS0_TRUEID);
  chain->SetBranchAddress("B_BKGCAT", &B_BKGCAT);
  chain->SetBranchAddress("B_TRUETAU", &B_TRUETAU); 
  
  // ***** Initialize DataSet ***** //
  ////////////////////////////////////

  // *** Observable ***
  //RooRealVar *
	Blife = new RooRealVar("Blife","lifetime",0.,15.,"ps");
	RooCategory *AccRej = new RooCategory("AccRej","Accept/Reject Category");
  AccRej->defineType("Accept",1);
  AccRej->defineType("Reject",0);

  // *** DataSet ***
  RooArgSet *Obs = new RooArgSet(*Blife,*AccRej);
  RooDataSet *data_LL = new RooDataSet("data_LL","Unbinned dataset",*Obs);
  RooDataSet *data_DD = new RooDataSet("data_DD","Unbinned dataset",*Obs);


  // ***** Loop over Entries: Apply Selection Cuts ***** //
  /////////////////////////////////////////////////////////

  // Initialise
  Double_t DOCA = 0;
  Double_t DOCA_min = 999;
  Int_t truePV = 0;
  bool Trigger = false;

  std::cout << " " << std::endl;
  std::cout << "== Loop 1: Selection Cuts ==" << std::endl;
  std::cout << "============================" << std::endl;

  for(Long64_t i=0; i<nEntries_NTuple; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_NTuple << " (" << 100*i/nEntries_NTuple << "%)" << std::endl;

    // Truth Match
    if(TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && KS0_TRUEID==310 && (B_BKGCAT==0 || B_BKGCAT==10)){

      Trigger = ((PsiHlt1TrackMuonDecision_TOS || PsiHlt1DiMuonHighMassDecision_TOS || PsiHlt1TrackAllL0Decision_TOS) &&
				         (PsiHlt2DiMuonDetachedJPsiDecision_TOS || PsiHlt2DiMuonJPsiHighPTDecision_TOS || PsiHlt2DiMuonJPsiDecision_TOS ||
                  PsiHlt2TopoMu2BodyBBDTDecision_TOS));
                  
      // Loop 1: Determine DOCA
      for(Int_t pv = 0; pv < nPV2 ; pv++){ 
        DOCA = TMath::Sqrt(pow(B_TRUEORIGINVERTEX_X-B_FullFit_PV_X[pv],2) + pow(B_TRUEORIGINVERTEX_Y-B_FullFit_PV_Y[pv],2) + pow(B_TRUEORIGINVERTEX_Z-B_FullFit_PV_Z[pv],2));
        if(DOCA<DOCA_min){
          DOCA_min = DOCA;
          truePV = pv;
        }
      }

      // Loop 2: Fill
      for(Int_t pv = 0; pv < nPV2 ; pv++){
        if(B_FullFit_M[pv]>Bmass_min && B_FullFit_M[pv]<Bmass_max && ((lifetype=="Reco" && B_FullFit_ctau[pv]/299.792458>=0.0002) || (lifetype=="True" && B_TRUETAU>=0.0002))){
          if(efftype=="Abs" || (efftype=="Rel" && netOutput[pv]>-1 && Trigger)){ // Selection Cuts

            if(pv==truePV || allPVs){
              // Neural Net
              if(((piminus_TRACK_Type==3 && netOutput[pv]>NNcut_LL) || (piminus_TRACK_Type==5 && netOutput[pv]>NNcut_DD)) && Trigger)AccRej->setLabel("Accept");
              else AccRej->setLabel("Reject");
      
              // Assign Lifetime
              if(lifetype=="Reco") Blife->setVal(B_FullFit_ctau[pv]*pow(10.,12)/(299792458*pow(10.,3)));	// convert from mm/c to ps
              else Blife->setVal(1000*B_TRUETAU);
              if(piminus_TRACK_Type==3) data_LL->add(*Obs);
              else if(piminus_TRACK_Type==5) data_DD->add(*Obs);
            }
          }
        }
      }
		}
    // Reset
    DOCA_min = 999;
  }

  // Free Memory
  delete chain;
  
// ***** Part II: Determine Acceptance ***** //
///////////////////////////////////////////////	

  std::cout << std::endl;
  std::cout << "== Part II: Fitting Acceptance ==" << std::endl;
  std::cout << "=================================" << std::endl;

  // ********** Initialise ********** //
  //////////////////////////////////////
  
	// *** Lifetime ***		
	RooRealVar *tau_Bd = new RooRealVar("tau_Bd","Generated Bd lifetime",1.525,"ps");	
  
  // *** Resolution ***	
	RooRealVar *resSigma = new RooRealVar("resSigma","Resolution - Width",0.00001,"ps");
  RooRealVar *resMean = new RooRealVar("resMean","Resolution - Mean",0.,"ps");
	RooRealVar *coreSigma = new RooRealVar("coreSigma","Resolution - Core Width",0.03,"ps");
	RooRealVar *midSigma = new RooRealVar("midSigma","Resolution - Middle Width",0.06,"ps");
	RooRealVar *tailSigma = new RooRealVar("tailSigma","Resolution - Tail Width",0.10,"ps");
  RooRealVar *Corefrac = new RooRealVar("Corefrac","Fraction of Core", 0.45);
  RooRealVar *Midfrac = new RooRealVar("Midfrac","Fraction of Mid", 0.45);
	
	accX = new RooRealVar("accX","For Acceptance Function",0.9,0.,(setup=="Exp" ? 1. : 1.5));
	accY = new RooRealVar("accY","For Acceptance Function",0.95,0.,5.);
	accZ = new RooRealVar("accZ","For Acceptance Function",1., 0. ,10.);	
  accOffset = new RooRealVar("accOffset","For Acceptance Function",0.2, -1.,1.);	
	accVelo = new RooRealVar("accVelo","For Acceptance Function",-0.0007,-0.5,0.5);


  // ********** Time PDFs ********** //
  /////////////////////////////////////

  // *** Acceptance ***
  RooFormulaVar *acceptance = 0;
  if(setup=="Tan") acceptance = new RooFormulaVar("acceptance","an acceptance function","(2/acos(-1))*@0*TMath::ATan(@1*@3)*(1+@2*@3)",RooArgList(*accX,*accY,*accVelo,*Blife));
  else if(setup=="TanOffset") acceptance = new RooFormulaVar("acceptance","an acceptance function","(2/acos(-1))*@0*TMath::ATan(@1*(@4-@2))*(1+@3*@4)",RooArgList(*accX,*accY,*accOffset,*accVelo,*Blife));
  else if(setup=="Exp") acceptance = new RooFormulaVar("acceptance","an acceptance function","@0*(1-TMath::Exp(-(@4-@2)*@1))*(1+@3*@4)",RooArgList(*accX,*accY,*accOffset,*accVelo,*Blife));
  else if(setup=="Frac") acceptance = new RooFormulaVar("acceptance","an acceptance function","@0*(1+@3*@4)/(1+pow(@2*@4,-@1))",RooArgList(*accX,*accY,*accZ,*accVelo,*Blife));
  else if(setup=="FracOffset") acceptance = new RooFormulaVar("acceptance","an acceptance function","@0*(1+@4*@5)/(1+pow(@2*(@5-@3),-@1))",RooArgList(*accX,*accY,*accZ,*accOffset,*accVelo,*Blife));
  	
  // *** Resolution ***
  RooGaussModel *core = new RooGaussModel("core","Core Gaussian",*Blife,*resMean,*coreSigma);
  RooGaussModel *mid = new RooGaussModel("mid","Middle Gaussian",*Blife,*resMean,*midSigma);
  RooGaussModel *tail = new RooGaussModel("tail","Tail Gaussian",*Blife,*resMean,*tailSigma);
  RooResolutionModel *Res_Model = 0;
  if(lifetype=="Reco") Res_Model = new RooAddModel("Res_Model","Resolution Model",RooArgList(*core,*mid,*tail),RooArgList(*Corefrac,*Midfrac));
  else if(lifetype=="True") Res_Model = new RooGaussModel("Res_Model","Gaussian",*Blife,*resMean,*resSigma);
  
  // *** RooDecays ***
	RooDecay *decay_Bd = new RooDecay("decay_Bd","Long Lifetimes",*Blife,*tau_Bd,*Res_Model,RooDecay::SingleSided);  
  RooEffProd *decay_acc = new RooEffProd("decay_acc","Decay with acceptance",*decay_Bd,*acceptance);


  // ********** Efficiency && Lifetime Fits ********** //
  ///////////////////////////////////////////////////////
  
  // *** Efficiency ***
  char buffer[3];
  Int_t NNVal_LL = NNcut_LL*100;
  Int_t NNVal_DD = NNcut_DD*100;
  std::sprintf(buffer,"_NN%d+%d",NNVal_LL,NNVal_DD);
  TString effString("NNefficiency_LL_"+efftype+"_Acc"+setup);
  if(allPVs) effString = "NNefficiency_allPVs_LL_"+efftype+"_Acc"+setup;
  effString.Append(buffer);
  
  double Minuit_effFit_LL[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
  if(lifetype=="True") FitPlotEff(lifetype,effString,data_LL,acceptance,AccRej,Minuit_effFit_LL);
  
  effString = "NNefficiency_DD_"+efftype+"_Acc"+setup;
  if(allPVs) effString = "NNefficiency_allPVs_DD_"+efftype+"_Acc"+setup;
  effString.Append(buffer);
  double Minuit_effFit_DD[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
  if(lifetype=="True") FitPlotEff(lifetype,effString,data_DD,acceptance,AccRej,Minuit_effFit_DD);
  
  // *** Lifetime ***
  TString tauString("NNtauFit_LL_Acc"+setup);
  if(allPVs) tauString = "NNtauFit_allPVs_LL_Acc"+setup;
  tauString.Append(buffer);
  
  RooDataSet* good_data_LL = (RooDataSet *) data_LL->reduce("AccRej==1");
  double Minuit_tauFit_LL[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
  if(lifetype=="Reco"){
    coreSigma->setVal(0.0313289);
    midSigma->setVal(0.0612225);
    tailSigma->setVal(0.37931);
    Corefrac->setVal(0.702295);
    Midfrac->setVal(0.28924);
  }
  else {
    coreSigma->setVal(0.00001);
    midSigma->setVal(0.00001);
    tailSigma->setVal(0.00001);
    Corefrac->setVal(1.);
    Midfrac->setVal(0.);
  }
  if(efftype=="Abs") FitPlotTau(lifetype,tauString,good_data_LL,decay_acc,Minuit_tauFit_LL);
  
  tauString = "NNtauFit_DD_Acc"+setup;
  if(allPVs) tauString = "NNtauFit_allPVs_DD_Acc"+setup;
  tauString.Append(buffer);
  
  RooDataSet* good_data_DD = (RooDataSet *) data_DD->reduce("AccRej==1");
  double Minuit_tauFit_DD[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
  if(lifetype=="Reco"){
    coreSigma->setVal(0.0313592);
    midSigma->setVal(0.0634281);
    tailSigma->setVal(0.210496);
    Corefrac->setVal(0.633399);
    Midfrac->setVal(0.354031);
  }
  else {
    coreSigma->setVal(0.00001);
    midSigma->setVal(0.00001);
    tailSigma->setVal(0.00001);
    Corefrac->setVal(1.);
    Midfrac->setVal(0.);
  }
  if(efftype=="Abs") FitPlotTau(lifetype,tauString,good_data_DD,decay_acc,Minuit_tauFit_DD);
  
  
  // ********** Fit Bs Lifetime ********** //
  ///////////////////////////////////////////
  if(efftype=="Abs") LifetimeFit(Minuit_tauFit_LL,Minuit_tauFit_DD, setup, lifetype, allPVs);


  // ***** Output ***** //
  ////////////////////////

  std::cout << std::endl;	
  std::cout << "==================================================" << std::endl;
  std::cout << "== PDF Results (Bd->JpsiKs MC): " << lifetype << " Decay Time ==" << std::endl;
  std::cout << "==================================================" << std::endl;
  if(setup=="Exp") std::cout << "Acceptance Model: x*(1-Exp[-y*(tau-offset)])*(1+beta*tau)" << std::endl;
  else if(setup=="Tan") std::cout << "Acceptance Model: (2/acos(-1))*x*ArcTan[y*tau]*(1+beta*tau)" << std::endl;
  else if(setup=="TanOffset") std::cout << "Acceptance Model: (2/acos(-1))*x*ArcTan[y*(tau-offset)]*(1+beta*tau)" << std::endl;
  else if(setup=="Frac") std::cout << "Acceptance Model: x*(1+beta*tau)/(1+(z*tau)^-y)" << std::endl;
  else if(setup=="FracOffset") std::cout << "Acceptance Model: x*(1+beta*tau)/(1+(z*[tau-offset])^-y)" << std::endl;
  std::cout << std::endl;
  if(efftype=="Rel") std::cout << "== Efficiency: Optimal Neural Net versus Selection + Trigger ==" << std::endl;
  else if(efftype=="Abs") std::cout << "== Efficiency: Optimal Neural Net versus Stripping ==" << std::endl;
  std::cout << "== Long KS ==" << std::endl;
  if(Minuit_effFit_LL[0]!=-999) std::cout << "x = " << Minuit_effFit_LL[0] << " +/- " << Minuit_effFit_LL[1] << std::endl;
  if(Minuit_effFit_LL[2]!=-999) std::cout << "y = " << Minuit_effFit_LL[2] << " +/- " << Minuit_effFit_LL[3] << std::endl;
  if(Minuit_effFit_LL[4]!=-999) std::cout << "z = " << Minuit_effFit_LL[4] << " +/- " << Minuit_effFit_LL[5] << std::endl;
  if(Minuit_effFit_LL[6]!=-999) std::cout << "offset = " << Minuit_effFit_LL[6] << " +/- " << Minuit_effFit_LL[7] << std::endl;
  if(Minuit_effFit_LL[8]!=-999) std::cout << "beta = " << Minuit_effFit_LL[8] << " +/- " << Minuit_effFit_LL[9] << std::endl;
	std::cout << std::endl;
  std::cout << "== Downstream KS ==" << std::endl;
  if(Minuit_effFit_DD[0]!=-999) std::cout << "x = " << Minuit_effFit_DD[0] << " +/- " << Minuit_effFit_DD[1] << std::endl;
  if(Minuit_effFit_DD[2]!=-999) std::cout << "y = " << Minuit_effFit_DD[2] << " +/- " << Minuit_effFit_DD[3] << std::endl;
  if(Minuit_effFit_DD[4]!=-999) std::cout << "z = " << Minuit_effFit_DD[4] << " +/- " << Minuit_effFit_DD[5] << std::endl;
  if(Minuit_effFit_DD[6]!=-999) std::cout << "offset = " << Minuit_effFit_DD[6] << " +/- " << Minuit_effFit_DD[7] << std::endl;
  if(Minuit_effFit_DD[8]!=-999) std::cout << "beta = " << Minuit_effFit_DD[8] << " +/- " << Minuit_effFit_DD[9] << std::endl;
	std::cout << std::endl;
  std::cout << "== Lifetime Fit: Optimal Neural Net ==" << std::endl;
  std::cout << "== Long KS ==" << std::endl;
  if(Minuit_tauFit_LL[0]!=-999) std::cout << "x = " << Minuit_tauFit_LL[0] << " +/- " << Minuit_tauFit_LL[1] << std::endl;
  if(Minuit_tauFit_LL[2]!=-999) std::cout << "y = " << Minuit_tauFit_LL[2] << " +/- " << Minuit_tauFit_LL[3] << std::endl;
  if(Minuit_tauFit_LL[4]!=-999) std::cout << "z = " << Minuit_tauFit_LL[4] << " +/- " << Minuit_tauFit_LL[5] << std::endl;
  if(Minuit_tauFit_LL[6]!=-999) std::cout << "offset = " << Minuit_tauFit_LL[6] << " +/- " << Minuit_tauFit_LL[7] << std::endl;
  if(Minuit_tauFit_LL[8]!=-999) std::cout << "beta = " << Minuit_tauFit_LL[8] << " +/- " << Minuit_tauFit_LL[9] << std::endl;
	std::cout << std::endl;
  std::cout << "== Downstream KS ==" << std::endl;
  if(Minuit_tauFit_DD[0]!=-999) std::cout << "x = " << Minuit_tauFit_DD[0] << " +/- " << Minuit_tauFit_DD[1] << std::endl;
  if(Minuit_tauFit_DD[2]!=-999) std::cout << "y = " << Minuit_tauFit_DD[2] << " +/- " << Minuit_tauFit_DD[3] << std::endl;
  if(Minuit_tauFit_DD[4]!=-999) std::cout << "z = " << Minuit_tauFit_DD[4] << " +/- " << Minuit_tauFit_DD[5] << std::endl;
  if(Minuit_tauFit_DD[6]!=-999) std::cout << "offset = " << Minuit_tauFit_DD[6] << " +/- " << Minuit_tauFit_DD[7] << std::endl;
  if(Minuit_tauFit_DD[8]!=-999) std::cout << "beta = " << Minuit_tauFit_DD[8] << " +/- " << Minuit_tauFit_DD[9] << std::endl;
	std::cout << std::endl;

}


///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void LifetimeFit(double *Results_LL, double *Results_DD, TString setup, TString lifetype, bool allPVs){

// ***** Initialize ***** //
////////////////////////////

  // Using Optimisation VIIb
  Double_t NNcut_LL = 0.60;
  Double_t NNcut_DD = 0.75;

  // *** Plot Ranges ***
  Double_t Bmass_min = 5180;
  Double_t Bmass_max = 5520;


// ***** Part I: From NTuple to DataSet ***** //
////////////////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Part I: From NTuple to DataSet ==" << std::endl;
  std::cout << "====================================" << std::endl;

  // ***** Load NTuples ***** //
  //////////////////////////////
	
  TFile* netFile = TFile::Open("B2JpsiKs-Eval-2-random-SigBs.root");
  TTree* neural_net = (TTree*)netFile->Get("NetTree");

  TChain* chain = new TChain("chain");
  chain->Add("B2JpsiKs-Slim-SigBs.root/Slim_B2JpsiKs_Tuple");
	chain->AddFriend(neural_net);
	
  Long64_t nEntries_NTuple = chain->GetEntries();
	//nEntries_NTuple = 10000;	
  std::cout << "Number of entries from DaVinci: " << nEntries_NTuple << std::endl;		


  // ***** Define DataSet Observables ***** //
  ////////////////////////////////////////////

  // *** Define Observables & Selection Variables ***
				
  // Observable
	Float_t B_FullFit_ctau[10];
  Float_t B_FullFit_M[10];
  Int_t piminus_TRACK_Type = -999;
  // PV Matching
  Double_t B_TRUEORIGINVERTEX_X = -999;
  Double_t B_TRUEORIGINVERTEX_Y = -999;
  Double_t B_TRUEORIGINVERTEX_Z = -999;
  Float_t B_FullFit_PV_X[10];
  Float_t B_FullFit_PV_Y[10];
  Float_t B_FullFit_PV_Z[10];
	// Trigger
  Bool_t PsiHlt1TrackMuonDecision_TOS = -999;
	Bool_t PsiHlt1DiMuonHighMassDecision_TOS = -999; 
	Bool_t PsiHlt1TrackAllL0Decision_TOS = -999;
  Bool_t PsiHlt2DiMuonDetachedJPsiDecision_TOS = -999; 
	Bool_t PsiHlt2DiMuonJPsiHighPTDecision_TOS = -999;
	Bool_t PsiHlt2DiMuonJPsiDecision_TOS = -999;
	Bool_t PsiHlt2TopoMu2BodyBBDTDecision_TOS = -999;	
  // Neural Net
  Float_t netOutput[10];
  Int_t nPV2 = -999;
	// True ID of Decay
  Int_t B_TRUEID = -999;
  Int_t Psi_TRUEID = -999;
  Int_t KS0_TRUEID = -999;
	Int_t B_BKGCAT = -999;
  Double_t B_TRUETAU = -999;


  // *** Initialize Arrays ***
  for(Int_t i=0; i<10; i++){
		B_FullFit_ctau[i] = -999;
    B_FullFit_M[i] = -999;
    B_FullFit_PV_X[i] = -999;
    B_FullFit_PV_Y[i] = -999;
    B_FullFit_PV_Z[i] = -999;
    netOutput[i] = -999;
  }


  // *** Set Branch Addresses ***
  // Observable
  chain->SetBranchAddress("B_FullFit_ctau", &B_FullFit_ctau);
  chain->SetBranchAddress("B_FullFit_M", &B_FullFit_M);
  chain->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type);
  // PV Matching
  chain->SetBranchAddress("B_TRUEORIGINVERTEX_X", &B_TRUEORIGINVERTEX_X);
  chain->SetBranchAddress("B_TRUEORIGINVERTEX_Y", &B_TRUEORIGINVERTEX_Y);
  chain->SetBranchAddress("B_TRUEORIGINVERTEX_Z", &B_TRUEORIGINVERTEX_Z);
  chain->SetBranchAddress("B_FullFit_PV_X", &B_FullFit_PV_X);
  chain->SetBranchAddress("B_FullFit_PV_Y", &B_FullFit_PV_Y);
  chain->SetBranchAddress("B_FullFit_PV_Z", &B_FullFit_PV_Z);
	// Trigger
  chain->SetBranchAddress("PsiHlt1TrackMuonDecision_TOS", &PsiHlt1TrackMuonDecision_TOS);
	chain->SetBranchAddress("PsiHlt1DiMuonHighMassDecision_TOS", &PsiHlt1DiMuonHighMassDecision_TOS);
	chain->SetBranchAddress("PsiHlt1TrackAllL0Decision_TOS", &PsiHlt1TrackAllL0Decision_TOS);	
  chain->SetBranchAddress("PsiHlt2DiMuonDetachedJPsiDecision_TOS", &PsiHlt2DiMuonDetachedJPsiDecision_TOS);
	chain->SetBranchAddress("PsiHlt2DiMuonJPsiHighPTDecision_TOS", &PsiHlt2DiMuonJPsiHighPTDecision_TOS);
	chain->SetBranchAddress("PsiHlt2DiMuonJPsiDecision_TOS", &PsiHlt2DiMuonJPsiDecision_TOS);
	chain->SetBranchAddress("PsiHlt2TopoMu2BodyBBDTDecision_TOS",&PsiHlt2TopoMu2BodyBBDTDecision_TOS);	
  // Neural Net
  chain->SetBranchAddress("netOutput", &netOutput);
  chain->SetBranchAddress("nPV2", &nPV2);
  // True ID of Decay
  chain->SetBranchAddress("B_TRUEID", &B_TRUEID);
  chain->SetBranchAddress("Psi_TRUEID", &Psi_TRUEID);
  chain->SetBranchAddress("KS0_TRUEID", &KS0_TRUEID);
  chain->SetBranchAddress("B_BKGCAT", &B_BKGCAT);
  chain->SetBranchAddress("B_TRUETAU", &B_TRUETAU); 
  
  // ***** Initialize DataSet ***** //
  ////////////////////////////////////

  // *** Observable ***
  //RooRealVar *
	Blife = new RooRealVar("Blife","lifetime",0.,15.,"ps");

  // *** DataSet ***
  RooArgSet *Obs = new RooArgSet(*Blife);
  RooDataSet *data_LL = new RooDataSet("data_LL","Unbinned dataset",*Obs);
  RooDataSet *data_DD = new RooDataSet("data_DD","Unbinned dataset",*Obs);


  // ***** Loop over Entries: Apply Selection Cuts ***** //
  /////////////////////////////////////////////////////////

  // Initialise
  Double_t DOCA = 0;
  Double_t DOCA_min = 999;
  Int_t truePV = 0;
  bool Trigger = false;

  std::cout << " " << std::endl;
  std::cout << "== Loop 1: Selection Cuts ==" << std::endl;
  std::cout << "============================" << std::endl;

  for(Long64_t i=0; i<nEntries_NTuple; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_NTuple << " (" << 100*i/nEntries_NTuple << "%)" << std::endl;

    // Truth Match
    if(TMath::Abs(B_TRUEID)==531 && Psi_TRUEID==443 && KS0_TRUEID==310 && B_BKGCAT==20){

      Trigger = ((PsiHlt1TrackMuonDecision_TOS || PsiHlt1DiMuonHighMassDecision_TOS || PsiHlt1TrackAllL0Decision_TOS) &&
				         (PsiHlt2DiMuonDetachedJPsiDecision_TOS || PsiHlt2DiMuonJPsiHighPTDecision_TOS || PsiHlt2DiMuonJPsiDecision_TOS ||
                  PsiHlt2TopoMu2BodyBBDTDecision_TOS));

      // Loop 1: Determine DOCA
      for(Int_t pv = 0; pv < nPV2 ; pv++){ 
        DOCA = TMath::Sqrt(pow(B_TRUEORIGINVERTEX_X-B_FullFit_PV_X[pv],2) + pow(B_TRUEORIGINVERTEX_Y-B_FullFit_PV_Y[pv],2) + pow(B_TRUEORIGINVERTEX_Z-B_FullFit_PV_Z[pv],2));
        if(DOCA<DOCA_min){
          DOCA_min = DOCA;
          truePV = pv;
        }
      }

      // Loop 2: Fill
      for(Int_t pv = 0; pv < nPV2 ; pv++){
        if(B_FullFit_M[pv]>Bmass_min && B_FullFit_M[pv]<Bmass_max && ((lifetype=="Reco" && B_FullFit_ctau[pv]/299.792458>=0.0002) || (lifetype=="True" && B_TRUETAU>=0.0002))){

          // Neural Net
          if(((piminus_TRACK_Type==3 && netOutput[pv]>NNcut_LL) || (piminus_TRACK_Type==5 && netOutput[pv]>NNcut_DD)) && Trigger){
            if(pv==truePV || allPVs){
            
              // Assign Lifetime
              if(lifetype=="Reco") Blife->setVal(B_FullFit_ctau[pv]*pow(10.,12)/(299792458*pow(10.,3)));	// convert from mm/c to ps
              else Blife->setVal(1000*B_TRUETAU);
              if(piminus_TRACK_Type==3) data_LL->add(*Obs);
              else if(piminus_TRACK_Type==5) data_DD->add(*Obs);
            }
          }
        }
      }
		}
    // Reset
    DOCA_min = 999;
  }

  // Free Memory
  delete chain;
  
// ***** Part II: Determine Acceptance ***** //
///////////////////////////////////////////////	

  std::cout << std::endl;
  std::cout << "== Part II: Fitting Acceptance ==" << std::endl;
  std::cout << "=================================" << std::endl;

  // ********** Initialise ********** //
  //////////////////////////////////////
  
	// *** Lifetime ***		
	RooRealVar *tau_Bd = new RooRealVar("tau_Bd","Generated Bd lifetime",1.525,0.5,3.,"ps");	

  // *** Resolution ***	
	RooRealVar *resSigma = new RooRealVar("resSigma","Resolution - Width",0.00001,"ps");
  RooRealVar *resMean = new RooRealVar("resMean","Resolution - Mean",0.,"ps");
	RooRealVar *coreSigma = new RooRealVar("coreSigma","Resolution - Core Width",0.03,"ps");
	RooRealVar *midSigma = new RooRealVar("midSigma","Resolution - Middle Width",0.06,"ps");
	RooRealVar *tailSigma = new RooRealVar("tailSigma","Resolution - Tail Width",0.10,"ps");
  RooRealVar *Corefrac = new RooRealVar("Corefrac","Fraction of Core", 0.45);
  RooRealVar *Midfrac = new RooRealVar("Midfrac","Fraction of Mid", 0.45);
	
	accX = new RooRealVar("accX","For Acceptance Function",1.);
	accY = new RooRealVar("accY","For Acceptance Function",0.);
	accZ = new RooRealVar("accZ","For Acceptance Function",0.);	
  accOffset = new RooRealVar("accOffset","For Acceptance Function",0.);	
	accVelo = new RooRealVar("accVelo","For Acceptance Function",0.);


  // ********** Time PDFs ********** //
  /////////////////////////////////////

  // *** Acceptance ***
  RooFormulaVar *acceptance = 0;
  if(setup=="Tan") acceptance = new RooFormulaVar("acceptance","an acceptance function","(2/acos(-1))*@0*TMath::ATan(@1*@3)*(1+@2*@3)",RooArgList(*accX,*accY,*accVelo,*Blife));
  else if(setup=="TanOffset") acceptance = new RooFormulaVar("acceptance","an acceptance function","(2/acos(-1))*@0*TMath::ATan(@1*(@4-@2))*(1+@3*@4)",RooArgList(*accX,*accY,*accOffset,*accVelo,*Blife));
  else if(setup=="Exp") acceptance = new RooFormulaVar("acceptance","an acceptance function","@0*(1-TMath::Exp(-(@4-@2)*@1))*(1+@3*@4)",RooArgList(*accX,*accY,*accOffset,*accVelo,*Blife));
  else if(setup=="Frac") acceptance = new RooFormulaVar("acceptance","an acceptance function","@0*(1+@3*@4)/(1+pow(@2*@4,-@1))",RooArgList(*accX,*accY,*accZ,*accVelo,*Blife));
  else if(setup=="FracOffset") acceptance = new RooFormulaVar("acceptance","an acceptance function","@0*(1+@4*@5)/(1+pow(@2*(@5-@3),-@1))",RooArgList(*accX,*accY,*accZ,*accOffset,*accVelo,*Blife));
  
  // *** Resolution ***
  RooGaussModel *core = new RooGaussModel("core","Core Gaussian",*Blife,*resMean,*coreSigma);
  RooGaussModel *mid = new RooGaussModel("mid","Middle Gaussian",*Blife,*resMean,*midSigma);
  RooGaussModel *tail = new RooGaussModel("tail","Tail Gaussian",*Blife,*resMean,*tailSigma);
  RooResolutionModel *Res_Model = 0;
  if(lifetype=="Reco") Res_Model = new RooAddModel("Res_Model","Resolution Model",RooArgList(*core,*mid,*tail),RooArgList(*Corefrac,*Midfrac));
  else if(lifetype=="True") Res_Model = new RooGaussModel("Res_Model","Gaussian",*Blife,*resMean,*resSigma);
  
  // *** RooDecays ***
	RooDecay *decay_Bd = new RooDecay("decay_Bd","Long Lifetimes",*Blife,*tau_Bd,*Res_Model,RooDecay::SingleSided);  
  RooEffProd *decay_acc = new RooEffProd("decay_acc","Decay with acceptance",*decay_Bd,*acceptance);


  // ********** Lifetime Fit ********** //
  ////////////////////////////////////////
  
  char buffer[3];
  Int_t NNVal_LL = NNcut_LL*100;
  Int_t NNVal_DD = NNcut_DD*100;
  std::sprintf(buffer,"_NN%d+%d",NNVal_LL,NNVal_DD);
  
  // *** Long Ks ***  
  accY->setVal(Results_LL[2]);
  accZ->setVal(Results_LL[4]);
  accOffset->setVal(Results_LL[6]);
  accVelo->setVal(Results_LL[8]);
  if(lifetype=="Reco"){
    coreSigma->setVal(0.0313289);
    midSigma->setVal(0.0612225);
    tailSigma->setVal(0.37931);
    Corefrac->setVal(0.702295);
    Midfrac->setVal(0.28924);
  }
  else {
    coreSigma->setVal(0.00001);
    midSigma->setVal(0.00001);
    tailSigma->setVal(0.00001);
    Corefrac->setVal(1.);
    Midfrac->setVal(0.);
  }
  TString tauString("BsEffTauFit_LL_Acc"+setup);
  if(allPVs) tauString = "BsEffTauFit_allPVs_LL_Acc"+setup;
  tauString.Append(buffer);
  double Minuit_tauFit_LL[] = {-999,-999};
  FitPlotTau(lifetype,tauString,data_LL,decay_acc,Minuit_tauFit_LL);
  
  // *** Downstream Ks *** 
  accY->setVal(Results_DD[2]);
  accZ->setVal(Results_DD[4]);
  accOffset->setVal(Results_DD[6]);
  accVelo->setVal(Results_DD[8]);
  if(lifetype=="Reco"){
    coreSigma->setVal(0.0313592);
    midSigma->setVal(0.0634281);
    tailSigma->setVal(0.210496);
    Corefrac->setVal(0.633399);
    Midfrac->setVal(0.354031);
  }
  else {
    coreSigma->setVal(0.00001);
    midSigma->setVal(0.00001);
    tailSigma->setVal(0.00001);
    Corefrac->setVal(1.);
    Midfrac->setVal(0.);
  }
  tauString = "BsEffTauFit_DD_Acc"+setup;
  if(allPVs) tauString = "BsEffTauFit_allPVs_DD_Acc"+setup;
  tauString.Append(buffer);
  double Minuit_tauFit_DD[] = {-999,-999};
  FitPlotTau(lifetype,tauString,data_DD,decay_acc,Minuit_tauFit_DD);
  

  // ***** Output ***** //
  ////////////////////////

  std::cout << std::endl;	
  std::cout << "==================================================" << std::endl;
  std::cout << "== PDF Results (Bs->JpsiKs MC): " << lifetype << " Decay Time ==" << std::endl;
  std::cout << "==================================================" << std::endl;
  if(setup=="Exp") std::cout << "Acceptance Model: x*(1-Exp[-y*(tau-offset)])*(1+beta*tau)" << std::endl;
  else if(setup=="Tan") std::cout << "Acceptance Model: (2/acos(-1))*x*ArcTan[y*tau]*(1+beta*tau)" << std::endl;
  else if(setup=="TanOffset") std::cout << "Acceptance Model: (2/acos(-1))*x*ArcTan[y*(tau-offset)]*(1+beta*tau)" << std::endl;
  else if(setup=="Frac") std::cout << "Acceptance Model: x*(1+beta*tau)/(1+(z*tau)^-y)" << std::endl;
  else if(setup=="FracOffset") std::cout << "Acceptance Model: x*(1+beta*tau)/(1+(z*[tau-offset])^-y)" << std::endl;
  std::cout << std::endl;
  std::cout << "== Lifetime Fit: Optimal Neural Net ==" << std::endl;
  std::cout << "Generated Lifetime: 1.475 ps" << std::endl;
  std::cout << "== Long KS ==" << std::endl;
  if(Minuit_tauFit_LL[0]!=-999) std::cout << "Eff Tau = " << Minuit_tauFit_LL[0] << " +/- " << Minuit_tauFit_LL[1] << " => Diff = " << Minuit_tauFit_LL[0]-1.475 << " (" << (Minuit_tauFit_LL[0]-1.475)/Minuit_tauFit_LL[1] << " sigma)" << std::endl;
	std::cout << std::endl;
  std::cout << "== Downstream KS ==" << std::endl;
  if(Minuit_tauFit_DD[0]!=-999) std::cout << "Eff Tau = " << Minuit_tauFit_DD[0] << " +/- " << Minuit_tauFit_DD[1] << " => Diff = " << Minuit_tauFit_DD[0]-1.475 << " (" << (Minuit_tauFit_DD[0]-1.475)/Minuit_tauFit_DD[1] << " sigma)" << std::endl;
	std::cout << std::endl;

}


///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void FullModel(TString setup, TString setupW){

// ***** Initialize ***** //
////////////////////////////

  // Using Optimisation VIIb
  Double_t NNcut_LL = 0.60;
  Double_t NNcut_DD = 0.75;

  // *** Plot Ranges ***
  Double_t Bmass_min = 5180;
  Double_t Bmass_max = 5520;


// ***** Part I: From NTuple to DataSet ***** //
////////////////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Part I: From NTuple to DataSet ==" << std::endl;
  std::cout << "====================================" << std::endl;

  // ***** Load NTuples ***** //
  //////////////////////////////
	
  TFile* netFile = TFile::Open("B2JpsiKs-Eval-2-random-SigBd.root");
  TTree* neural_net = (TTree*)netFile->Get("NetTree");

  TChain* chain = new TChain("chain");
  chain->Add("B2JpsiKs-Slim-SigBd.root/Slim_B2JpsiKs_Tuple");
	chain->AddFriend(neural_net);
	
  Long64_t nEntries_NTuple = chain->GetEntries();
	//nEntries_NTuple = 10000;	
  std::cout << "Number of entries from DaVinci: " << nEntries_NTuple << std::endl;		


  // ***** Define DataSet Observables ***** //
  ////////////////////////////////////////////

  // *** Define Observables & Selection Variables ***
				
  // Observable
	Float_t B_FullFit_ctau[10];
  // Observables for Common Selection Cuts
  Float_t B_FullFit_M[10];
  Int_t piminus_TRACK_Type = -999;
	// Trigger
  Bool_t PsiHlt1TrackMuonDecision_TOS = -999;
	Bool_t PsiHlt1DiMuonHighMassDecision_TOS = -999; 
	Bool_t PsiHlt1TrackAllL0Decision_TOS = -999;
  Bool_t PsiHlt2DiMuonDetachedJPsiDecision_TOS = -999; 
	Bool_t PsiHlt2DiMuonJPsiHighPTDecision_TOS = -999;
	Bool_t PsiHlt2DiMuonJPsiDecision_TOS = -999;
	Bool_t PsiHlt2TopoMu2BodyBBDTDecision_TOS = -999;	
  // Neural Net
  Float_t netOutput[10];
  Int_t nPV2 = -999;
	// True ID of Decay
  Int_t B_TRUEID = -999;
  Int_t Psi_TRUEID = -999;
  Int_t KS0_TRUEID = -999;
	Int_t B_BKGCAT = -999;
  Double_t B_TRUETAU = -999;


  // *** Initialize Arrays ***
  for(Int_t i=0; i<10; i++){
		B_FullFit_ctau[i] = -999;
    B_FullFit_M[i] = -999;
    netOutput[i] = -999;
  }


  // *** Set Branch Addresses ***
  // Observable
  chain->SetBranchAddress("B_FullFit_ctau", &B_FullFit_ctau);
  chain->SetBranchAddress("B_FullFit_M", &B_FullFit_M);
  chain->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type);
	// Trigger
  chain->SetBranchAddress("PsiHlt1TrackMuonDecision_TOS", &PsiHlt1TrackMuonDecision_TOS);
	chain->SetBranchAddress("PsiHlt1DiMuonHighMassDecision_TOS", &PsiHlt1DiMuonHighMassDecision_TOS);
	chain->SetBranchAddress("PsiHlt1TrackAllL0Decision_TOS", &PsiHlt1TrackAllL0Decision_TOS);	
  chain->SetBranchAddress("PsiHlt2DiMuonDetachedJPsiDecision_TOS", &PsiHlt2DiMuonDetachedJPsiDecision_TOS);
	chain->SetBranchAddress("PsiHlt2DiMuonJPsiHighPTDecision_TOS", &PsiHlt2DiMuonJPsiHighPTDecision_TOS);
	chain->SetBranchAddress("PsiHlt2DiMuonJPsiDecision_TOS", &PsiHlt2DiMuonJPsiDecision_TOS);
	chain->SetBranchAddress("PsiHlt2TopoMu2BodyBBDTDecision_TOS",&PsiHlt2TopoMu2BodyBBDTDecision_TOS);	
  // Neural Net
  chain->SetBranchAddress("netOutput", &netOutput);
  chain->SetBranchAddress("nPV2", &nPV2);
  // True ID of Decay
  chain->SetBranchAddress("B_TRUEID", &B_TRUEID);
  chain->SetBranchAddress("Psi_TRUEID", &Psi_TRUEID);
  chain->SetBranchAddress("KS0_TRUEID", &KS0_TRUEID);
  chain->SetBranchAddress("B_BKGCAT", &B_BKGCAT);
  chain->SetBranchAddress("B_TRUETAU", &B_TRUETAU); 
  
  // ***** Initialize DataSet ***** //
  ////////////////////////////////////

  // *** Observable ***
	Blife = new RooRealVar("Blife","lifetime",0.,15.,"ps");

  // *** DataSet ***
  RooArgSet *Obs = new RooArgSet(*Blife);
  RooDataSet *data_LL = new RooDataSet("data_LL","Unbinned dataset",*Obs);
  RooDataSet *data_DD = new RooDataSet("data_DD","Unbinned dataset",*Obs);


  // ***** Loop over Entries: Apply Selection Cuts ***** //
  /////////////////////////////////////////////////////////

  // Initialise
  bool Trigger = false;

  std::cout << " " << std::endl;
  std::cout << "== Loop 1: Selection Cuts ==" << std::endl;
  std::cout << "============================" << std::endl;

  for(Long64_t i=0; i<nEntries_NTuple; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_NTuple << " (" << 100*i/nEntries_NTuple << "%)" << std::endl;

    // Truth Match
    if(TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && KS0_TRUEID==310 && (B_BKGCAT==0 || B_BKGCAT==10)){

      Trigger = ((PsiHlt1TrackMuonDecision_TOS || PsiHlt1DiMuonHighMassDecision_TOS || PsiHlt1TrackAllL0Decision_TOS) &&
				         (PsiHlt2DiMuonDetachedJPsiDecision_TOS || PsiHlt2DiMuonJPsiHighPTDecision_TOS || PsiHlt2DiMuonJPsiDecision_TOS ||
                  PsiHlt2TopoMu2BodyBBDTDecision_TOS));
                  
      for(Int_t pv = 0; pv < nPV2 ; pv++){
        if(B_FullFit_M[pv]>Bmass_min && B_FullFit_M[pv]<Bmass_max && B_FullFit_ctau[pv]/299.792458>=0.0002){
          if(((piminus_TRACK_Type==3 && netOutput[pv]>NNcut_LL) || (piminus_TRACK_Type==5 && netOutput[pv]>NNcut_DD)) && Trigger){
      
            // Assign Lifetime
            Blife->setVal(B_FullFit_ctau[pv]*pow(10.,12)/(299792458*pow(10.,3)));	// convert from mm/c to ps
            if(piminus_TRACK_Type==3) data_LL->add(*Obs);
            else if(piminus_TRACK_Type==5) data_DD->add(*Obs);
          }
        }
      }
		}
  }

  // Free Memory
  delete chain;
  
// ***** Part II: Determine Acceptance ***** //
///////////////////////////////////////////////	

  std::cout << std::endl;
  std::cout << "== Part II: Fitting Acceptance ==" << std::endl;
  std::cout << "=================================" << std::endl;

  // ********** Initialise ********** //
  //////////////////////////////////////
  
	// *** Lifetime ***		
	RooRealVar *tau_Bd = new RooRealVar("tau_Bd","Generated Bd lifetime",1.519,0.,3.,"ps");
  RooRealVar *tauW = new RooRealVar("tauW","Generated Bd lifetime",1.525,"ps");
  
  // *** Resolution ***	
  RooRealVar *resMean = new RooRealVar("resMean","Resolution - Mean",0.,"ps");
	RooRealVar *coreSigma = new RooRealVar("coreSigma","Resolution - Core Width",0.03,"ps");
	RooRealVar *midSigma = new RooRealVar("midSigma","Resolution - Middle Width",0.06,"ps");
	RooRealVar *tailSigma = new RooRealVar("tailSigma","Resolution - Tail Width",0.10,"ps");
  RooRealVar *Corefrac = new RooRealVar("Corefrac","Fraction of Core", 0.45);
  RooRealVar *Midfrac = new RooRealVar("Midfrac","Fraction of Mid", 0.45);
  
  RooRealVar *resMeanW = new RooRealVar("resMeanW","Resolution - Mean",0.06,"ps");
  RooRealVar *resMeanW_II = new RooRealVar("resMeanW_II","Resolution - Mean",0.8,"ps");
	RooRealVar *coreSigmaW = new RooRealVar("coreSigmaW","Resolution - Core Width",0.5,"ps");
	RooRealVar *tailSigmaW = new RooRealVar("tailSigmaW","Resolution - Tail Width",2.0,"ps");
  RooRealVar *CorefracW = new RooRealVar("CorefracW","Fraction of Core", 0.6);
	
  // *** Acceptance ***
	accX = new RooRealVar("accX","For Acceptance Function",1.);
	accY = new RooRealVar("accY","For Acceptance Function",2.);
	accZ = new RooRealVar("accZ","For Acceptance Function",2.);	
  accOffset = new RooRealVar("accOffset","For Acceptance Function",0.2);	
	accVelo = new RooRealVar("accVelo","For Acceptance Function",0.);

  RooRealVar *accXW = new RooRealVar("accXW","For Acceptance Function",1.);
	RooRealVar *accYW = new RooRealVar("accYW","For Acceptance Function",1.5);
	RooRealVar *accZW = new RooRealVar("accZW","For Acceptance Function",2.);	
  RooRealVar *accOffsetW = new RooRealVar("accOffsetW","For Acceptance Function",0.1);	
	RooRealVar *accVeloW = new RooRealVar("accVeloW","For Acceptance Function",-0.0007);
  RooRealVar *fracW = new RooRealVar("fracW","Fraction of wrong PV",0.01);


  // ********** Time PDFs ********** //
  /////////////////////////////////////

  // *** Acceptance ***
  RooFormulaVar *acceptance = 0;
  if(setup=="Tan") acceptance = new RooFormulaVar("acceptance","an acceptance function","(2/acos(-1))*@0*TMath::ATan(@1*@3)*(1+@2*@3)",RooArgList(*accX,*accY,*accVelo,*Blife));
  else if(setup=="TanOffset") acceptance = new RooFormulaVar("acceptance","an acceptance function","(2/acos(-1))*@0*TMath::ATan(@1*(@4-@2))*(1+@3*@4)",RooArgList(*accX,*accY,*accOffset,*accVelo,*Blife));
  else if(setup=="Exp") acceptance = new RooFormulaVar("acceptance","an acceptance function","@0*(1-TMath::Exp(-(@4-@2)*@1))*(1+@3*@4)",RooArgList(*accX,*accY,*accOffset,*accVelo,*Blife));
  else if(setup=="Frac") acceptance = new RooFormulaVar("acceptance","an acceptance function","@0*(1+@3*@4)/(1+pow(@2*@4,-@1))",RooArgList(*accX,*accY,*accZ,*accVelo,*Blife));
  else if(setup=="FracOffset") acceptance = new RooFormulaVar("acceptance","an acceptance function","@0*(1+@4*@5)/(1+pow(@2*(@5-@3),-@1))",RooArgList(*accX,*accY,*accZ,*accOffset,*accVelo,*Blife));
  
  RooFormulaVar *acceptanceW = 0;
  if(setupW=="Tan") acceptanceW = new RooFormulaVar("acceptanceW","an acceptance function","(2/acos(-1))*@0*TMath::ATan(@1*@3)*(1+@2*@3)",RooArgList(*accXW,*accYW,*accVeloW,*Blife));
  else if(setupW=="TanOffset") acceptanceW = new RooFormulaVar("acceptanceW","an acceptance function","(2/acos(-1))*@0*TMath::ATan(@1*(@4-@2))*(1+@3*@4)",RooArgList(*accXW,*accYW,*accOffsetW,*accVeloW,*Blife));
  else if(setupW=="Exp") acceptanceW = new RooFormulaVar("acceptanceW","an acceptance function","@0*(1-TMath::Exp(-(@4-@2)*@1))*(1+@3*@4)",RooArgList(*accXW,*accYW,*accOffsetW,*accVeloW,*Blife));
  else if(setupW=="Frac") acceptanceW = new RooFormulaVar("acceptanceW","an acceptance function","@0*(1+@3*@4)/(1+pow(@2*@4,-@1))",RooArgList(*accXW,*accYW,*accZW,*accVeloW,*Blife));
  else if(setupW=="FracOffset") acceptanceW = new RooFormulaVar("acceptanceW","an acceptance function","@0*(1+@4*@5)/(1+pow(@2*(@5-@3),-@1))",RooArgList(*accXW,*accYW,*accZW,*accOffsetW,*accVeloW,*Blife));
  
  // *** Resolution ***	
  RooGaussModel *core = new RooGaussModel("core","Core Gaussian",*Blife,*resMean,*coreSigma);
  RooGaussModel *mid = new RooGaussModel("mid","Middle Gaussian",*Blife,*resMean,*midSigma);
  RooGaussModel *tail = new RooGaussModel("tail","Tail Gaussian",*Blife,*resMean,*tailSigma);
  RooAddModel *Res_Model = new RooAddModel("Res_Model","Resolution Model",RooArgList(*core,*mid,*tail),RooArgList(*Corefrac,*Midfrac));
  
  RooGaussModel *coreW = new RooGaussModel("coreW","Core Gaussian",*Blife,*resMeanW,*coreSigmaW);
  RooGaussModel *tailW = new RooGaussModel("tailW","Tail Gaussian",*Blife,*resMeanW_II,*tailSigmaW);
  RooAddModel *Res_ModelW = new RooAddModel("Res_ModelW","Resolution Model",RooArgList(*coreW,*tailW),RooArgList(*CorefracW));
  
  // *** RooDecays ***
	RooDecay *decay_Bd = new RooDecay("decay_Bd","Long Lifetimes",*Blife,*tau_Bd,*Res_Model,RooDecay::SingleSided);  
  RooEffProd *decay_acc = new RooEffProd("decay_acc","Decay with acceptance",*decay_Bd,*acceptance);

  RooDecay *decayW_Bd = 0;
  if(setupW!="FracOffset") decayW_Bd = new RooDecay("decayW_Bd","Long Lifetimes",*Blife,*tauW,*Res_ModelW,RooDecay::SingleSided);
	else decayW_Bd = new RooDecay("decayW_Bd","Long Lifetimes",*Blife,*tauW,*Res_Model,RooDecay::SingleSided);  
  RooEffProd *decayW_acc = new RooEffProd("decayW_acc","Decay with acceptance",*decayW_Bd,*acceptanceW);

  // *** Combined Model ***
  RooAddPdf *decay_model = new RooAddPdf("decay_model","Full Decay Model",RooArgList(*decayW_acc,*decay_acc),*fracW);


  // ********** Efficiency && Lifetime Fits ********** //
  ///////////////////////////////////////////////////////
  
  // *** Initialise ***
  char buffer[3];
  Int_t NNVal_LL = NNcut_LL*100;
  Int_t NNVal_DD = NNcut_DD*100;
  std::sprintf(buffer,"_NN%d+%d",NNVal_LL,NNVal_DD);
 
  // *** Long KS Sample *** //
  ////////////////////////////
  TString tauString("FullFit_LL_ResWrongPV");
  if(setupW=="FracOffset") tauString = "FullFit_LL_ResCorrectPV";
  tauString.Append(buffer);
  
  // Resolution: Correct PVs
  coreSigma->setVal(0.0313289);
  midSigma->setVal(0.0612225);
  tailSigma->setVal(0.37931);
  Corefrac->setVal(0.702295);
  Midfrac->setVal(0.28924);
  // Acceptance: Correct PVs
  accY->setVal(1.98721);
  accZ->setVal(2.76136);
  accVelo->setVal(-0.0128816);
  // Resolution: Wrong PVs
  resMeanW->setVal(0.0761565);
  resMeanW_II->setVal(0.766588);
  coreSigmaW->setVal(0.678194);
  tailSigmaW->setVal(2.42);
  CorefracW->setVal(0.614803);
  // Acceptance: Wrong PVs
  if(setupW=="Frac"){
    accYW->setVal(2.78592);
    accZW->setVal(2.21696);
    accVeloW->setVal(0.284447);
  }
  else if(setupW=="FracOffset"){
    accYW->setVal(0.779385);
    accZW->setVal(0.000119075);
    accVeloW->setVal(0.179393);
    accOffsetW->setVal(0.121159);
  }
  // Fraction of Wrong PVs
  fracW->setVal(0.0225);
  
  double Minuit_FullModel_LL[] = {-999,-999};
  FitPlotTau("Reco",tauString,data_LL,decay_model,Minuit_FullModel_LL); 
  
  // *** Down KS Sample *** //
  ////////////////////////////
  tauString = "FullFit_DD_ResWrongPV";
  if(setupW=="FracOffset") tauString = "FullFit_DD_ResCorrectPV";
  tauString.Append(buffer);
  
  // Resolution: Correct PVs
  coreSigma->setVal(0.0313592);
  midSigma->setVal(0.0634281);
  tailSigma->setVal(0.210496);
  Corefrac->setVal(0.633399);
  Midfrac->setVal(0.354031);
  // Acceptance: Correct PVs
  accY->setVal(2.0842);
  accZ->setVal(1.53447);
  accVelo->setVal(0.032717);
  // Resolution: Wrong PVs
  resMeanW->setVal(0.056283);
  resMeanW_II->setVal(0.873669);
  coreSigmaW->setVal(0.497835);
  tailSigmaW->setVal(1.94824);
  CorefracW->setVal(0.66406);
  // Acceptance: Wrong PVs
  if(setupW=="Frac"){
    accYW->setVal(0.873474);
    accZW->setVal(0.000909781);
    accVeloW->setVal(0.0734636);
  }
  else if(setupW=="FracOffset"){
    accYW->setVal(1.13805);
    accZW->setVal(0.0050124);
    accVeloW->setVal(0.129342);
    accOffsetW->setVal(0.158052);
  }
  // Fraction of Wrong PVs
  fracW->setVal(0.0095);
  
  double Minuit_FullModel_DD[] = {-999,-999};
  FitPlotTau("Reco",tauString,data_DD,decay_model,Minuit_FullModel_DD);

  // ***** Output ***** //
  ////////////////////////

  std::cout << std::endl;	
  std::cout << "==================================================" << std::endl;
  std::cout << "== PDF Results (Bd->JpsiKs MC): Reco Decay Time ==" << std::endl;
  std::cout << "==================================================" << std::endl;
  if(setup=="Exp") std::cout << "Acceptance Model: x*(1-Exp[-y*(tau-offset)])*(1+beta*tau)" << std::endl;
  else if(setup=="Tan") std::cout << "Acceptance Model: (2/acos(-1))*x*ArcTan[y*tau]*(1+beta*tau)" << std::endl;
  else if(setup=="TanOffset") std::cout << "Acceptance Model: (2/acos(-1))*x*ArcTan[y*(tau-offset)]*(1+beta*tau)" << std::endl;
  else if(setup=="Frac") std::cout << "Acceptance Model: x*(1+beta*tau)/(1+(z*tau)^-y)" << std::endl;
  else if(setup=="FracOffset") std::cout << "Acceptance Model: x*(1+beta*tau)/(1+(z*[tau-offset])^-y)" << std::endl;
  std::cout << std::endl;
  std::cout << "== Lifetime Fit: Optimal Neural Net ==" << std::endl;
  std::cout << "Generated Lifetime: 1.525 ps" << std::endl;
  std::cout << "== Long KS ==" << std::endl;
  if(Minuit_FullModel_LL[0]!=-999) std::cout << "Eff Tau = " << Minuit_FullModel_LL[0] << " +/- " << Minuit_FullModel_LL[1] << " => Diff = " << Minuit_FullModel_LL[0]-1.525 << " (" << (Minuit_FullModel_LL[0]-1.525)/Minuit_FullModel_LL[1] << " sigma)" << std::endl;
	std::cout << std::endl;
  std::cout << "== Downstream KS ==" << std::endl;
  if(Minuit_FullModel_DD[0]!=-999) std::cout << "Eff Tau = " << Minuit_FullModel_DD[0] << " +/- " << Minuit_FullModel_DD[1] << " => Diff = " << Minuit_FullModel_DD[0]-1.525 << " (" << (Minuit_FullModel_DD[0]-1.525)/Minuit_FullModel_DD[1] << " sigma)" << std::endl;
	std::cout << std::endl;
}

///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void RDDecayTime(TString setup){

// ***** Initialize ***** //
////////////////////////////

  bool debug = false;
  
  // Using Optimisation VIIb
  Double_t NNcut_LL = 0.60;
  Double_t NNcut_DD = 0.75;

  // *** Plot Ranges ***
  Double_t Bmass_min = 5180;
  Double_t Bmass_max = 5520;


// ***** Part I: From NTuple to DataSet ***** //
////////////////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Part I: From NTuple to DataSet ==" << std::endl;
  std::cout << "====================================" << std::endl;

  // ***** Load NTuples ***** //
  //////////////////////////////
	
  TFile* netFile = TFile::Open("B2JpsiKs-Eval-2-random-LHCb2011.root");// Double Net
  TTree* neural_net = (TTree*)netFile->Get("NetTree");

  TChain* chain = new TChain("chain");
  chain->Add("B2JpsiKs-Slim-LHCb2011.root/Slim_B2JpsiKs_Tuple");
	chain->AddFriend(neural_net);
	
  Long64_t nEntries_NTuple = chain->GetEntries();
	//nEntries_NTuple = 10000;	
  std::cout << "Number of entries from DaVinci: " << nEntries_NTuple << std::endl;		


  // ***** Define DataSet Observables ***** //
  ////////////////////////////////////////////

  // *** Define Observables & Selection Variables ***
				
  // Observable
	Float_t B_FullFit_ctau[10];
  Float_t B_FullFit_M[10];
  // Neural Net
  Float_t netOutput[10];
  Int_t nPV2 = -999;
  Int_t piminus_TRACK_Type = -999;

  // *** Initialize Arrays ***
  for(Int_t i=0; i<10; i++){
		B_FullFit_ctau[i] = -999;
    B_FullFit_M[i] = -999;
    netOutput[i] = -999;
  }


  // *** Set Branch Addresses ***
  // Observable
  chain->SetBranchAddress("B_FullFit_ctau", &B_FullFit_ctau);
  chain->SetBranchAddress("B_FullFit_M", &B_FullFit_M);	
  // Neural Net
  chain->SetBranchAddress("netOutput", &netOutput);
  chain->SetBranchAddress("nPV2", &nPV2);
  chain->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type);
  
  // ***** Initialize DataSet ***** //
  ////////////////////////////////////

  // *** Observable ***
  RooRealVar *Bmass = new RooRealVar("Bmass","mass",Bmass_min,Bmass_max,"MeV/c^{2}");
  Blife = new RooRealVar("Blife","lifetime",0.,15.,"ps");

  // *** DataSet ***
  RooArgSet *Obs = new RooArgSet(*Blife,*Bmass);
  RooDataSet *data_LL = new RooDataSet("data_LL","Unbinned dataset",*Obs);
  RooDataSet *data_DD = new RooDataSet("data_DD","Unbinned dataset",*Obs);


  // ***** Loop over Entries: Apply Selection Cuts ***** //
  /////////////////////////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Loop 1: Selection Cuts ==" << std::endl;
  std::cout << "============================" << std::endl;

  for(Long64_t i=0; i<nEntries_NTuple; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_NTuple << " (" << 100*i/nEntries_NTuple << "%)" << std::endl;

    for(Int_t pv = 0; pv < nPV2 ; pv++){
      if((piminus_TRACK_Type==3 && netOutput[pv]>NNcut_LL) || (piminus_TRACK_Type==5 && netOutput[pv]>NNcut_DD)){// Selection Cuts

        // Fill DataSet
        Bmass->setVal(B_FullFit_M[pv]);
        Blife->setVal(B_FullFit_ctau[pv]*pow(10.,12)/(299792458*pow(10.,3)));	// convert from mm/c to ps
        if(piminus_TRACK_Type==3) data_LL->add(*Obs);
        else if(piminus_TRACK_Type==5) data_DD->add(*Obs);
      } 
		}
  }

  Int_t nEvents_LL = data_LL->numEntries();
  Int_t nEvents_DD = data_DD->numEntries();

  // Free Memory
  delete chain;
  
  
// ***** Part II: sWeights ***** //
///////////////////////////////////	

  std::cout << std::endl;
  std::cout << "== Part II: sWeights ==" << std::endl;
  std::cout << "=======================" << std::endl;
  
  // ***** Mass Model ***** //
  ////////////////////////////

  // *** Define Parameters ***  
  RooRealVar *meanBd = new RooRealVar("meanBd","Position of Bd mass peak",5279.5,Bmass_min,Bmass_max);
  RooFormulaVar *meanBs = new RooFormulaVar("meanBs","Position of Bs mass peak","@0+87.52",RooArgList(*meanBd));
  RooRealVar *frac_LL = new RooRealVar("frac_LL","Fraction of model I",0.47134,0.,1.);
  RooRealVar *frac_DD = new RooRealVar("frac_DD","Fraction of model I",0.64519,0.,1.);
  RooRealVar *sigma_I_LL = new RooRealVar("sigma_I_LL","Width of Bd mass peak",5.0722,1.0,25.0);
  RooRealVar *sigma_I_DD = new RooRealVar("sigma_I_DD","Width of Bd mass peak",6.2499,1.0,25.0);
  RooRealVar *sigma_II_LL = new RooRealVar("sigma_II_LL","Width of Bd mass peak",6.9036,1.0,25.0);
  RooRealVar *sigma_II_DD = new RooRealVar("sigma_II_DD","Width of Bd mass peak",10.677,1.0,25.0);
  RooRealVar *apar_I_LL = new RooRealVar("apar_I_LL","A parameter of Crystal Ball I",1.312);
  RooRealVar *apar_I_DD = new RooRealVar("apar_I_DD","A parameter of Crystal Ball I",2.339);
  RooRealVar *apar_II_LL = new RooRealVar("apar_II_LL","A parameter of Crystal Ball II",-1.434);
  RooRealVar *apar_II_DD = new RooRealVar("apar_II_DD","A parameter of Crystal Ball II",-2.248);
  RooRealVar *npar_I_LL = new RooRealVar("npar_I_LL","N parameter of Crystal Ball I",4.02);
  RooRealVar *npar_I_DD = new RooRealVar("npar_I_DD","N parameter of Crystal Ball I",1.71);
  RooRealVar *npar_II_LL = new RooRealVar("npar_II_LL","N parameter of Crystal Ball II",124.48);
  RooRealVar *npar_II_DD = new RooRealVar("npar_II_DD","N parameter of Crystal Ball II",4.7);
  
  RooRealVar *lambda_LL = new RooRealVar("lambda_LL","decay constant",-0.0027,-0.1,0.);
  RooRealVar *lambda_DD = new RooRealVar("lambda_DD","decay constant",-0.0027,-0.1,0.);
    
  // *** Crystal Ball ***
  RooCBShape *CBall_LL_Bd_I = new RooCBShape("CBall_LL_Bd_I","Crystal Ball",*Bmass,*meanBd,*sigma_I_LL,*apar_I_LL,*npar_I_LL);
  RooCBShape *CBall_LL_Bd_II = new RooCBShape("CBall_LL_Bd_II","Reflected Crystal Ball",*Bmass,*meanBd,*sigma_II_LL,*apar_II_LL,*npar_II_LL);
  RooAddPdf *double_CBall_LL_Bd = new RooAddPdf("double_CBall_LL_Bd","Double Crystal Ball",RooArgList(*CBall_LL_Bd_I,*CBall_LL_Bd_II),*frac_LL);
  RooCBShape *CBall_DD_Bd_I = new RooCBShape("CBall_DD_Bd_I","Crystal Ball",*Bmass,*meanBd,*sigma_I_DD,*apar_I_DD,*npar_I_DD);
  RooCBShape *CBall_DD_Bd_II = new RooCBShape("CBall_DD_Bd_II","Reflected Crystal Ball",*Bmass,*meanBd,*sigma_II_DD,*apar_II_DD,*npar_II_DD);
  RooAddPdf *double_CBall_DD_Bd = new RooAddPdf("double_CBall_DD_Bd","Double Crystal Ball",RooArgList(*CBall_DD_Bd_I,*CBall_DD_Bd_II),*frac_DD);

  RooCBShape *CBall_LL_Bs_I = new RooCBShape("CBall_LL_Bs_I","Crystal Ball",*Bmass,*meanBs,*sigma_I_LL,*apar_I_LL,*npar_I_LL);
  RooCBShape *CBall_LL_Bs_II = new RooCBShape("CBall_LL_Bs_II","Reflected Crystal Ball",*Bmass,*meanBs,*sigma_II_LL,*apar_II_LL,*npar_II_LL);
  RooAddPdf *double_CBall_LL_Bs = new RooAddPdf("double_CBall_LL_Bs","Double Crystal Ball",RooArgList(*CBall_LL_Bs_I,*CBall_LL_Bs_II),*frac_LL);
  RooCBShape *CBall_DD_Bs_I = new RooCBShape("CBall_DD_Bs_I","Crystal Ball",*Bmass,*meanBs,*sigma_I_DD,*apar_I_DD,*npar_I_DD);
  RooCBShape *CBall_DD_Bs_II = new RooCBShape("CBall_DD_Bs_II","Reflected Crystal Ball",*Bmass,*meanBs,*sigma_II_DD,*apar_II_DD,*npar_II_DD);
  RooAddPdf *double_CBall_DD_Bs = new RooAddPdf("double_CBall_DD_Bs","Double Crystal Ball",RooArgList(*CBall_DD_Bs_I,*CBall_DD_Bs_II),*frac_DD);
  
  // *** exponential (Background) ***
  RooExponential *exponential_LL = new RooExponential("exponential_LL","Exponential for background",*Bmass,*lambda_LL);
  RooExponential *exponential_DD = new RooExponential("exponential_DD","Exponential for background",*Bmass,*lambda_DD);

  // *** Combined signal and background ***
  RooRealVar *nBkg_LL = new RooRealVar("nBkg_LL","fraction",0.042311*nEvents_LL,0,nEvents_LL);
  RooRealVar *nBd_LL = new RooRealVar("nBd_LL","fraction",0.947600*nEvents_LL,0,nEvents_LL);
  RooRealVar *nBs_LL = new RooRealVar("nBs_LL","fraction",0.010089*nEvents_LL,0,nEvents_LL);

  RooAddPdf *massPDF_LL= new RooAddPdf("massPDF_LL","PDF for Sig + Bkg",RooArgList(*exponential_LL,*double_CBall_LL_Bd,*double_CBall_LL_Bs),RooArgList(*nBkg_LL,*nBd_LL,*nBs_LL));
  
  RooRealVar *nBkg_DD = new RooRealVar("nBkg_DD","fraction",0.042311*nEvents_DD,0,nEvents_DD);
  RooRealVar *nBd_DD = new RooRealVar("nBd_DD","fraction",0.947600*nEvents_DD,0,nEvents_DD);
  RooRealVar *nBs_DD = new RooRealVar("nBs_DD","fraction",0.010089*nEvents_DD,0,nEvents_DD);

  RooAddPdf *massPDF_DD= new RooAddPdf("massPDF_DD","PDF for Sig + Bkg",RooArgList(*exponential_DD,*double_CBall_DD_Bd,*double_CBall_DD_Bs),RooArgList(*nBkg_DD,*nBd_DD,*nBs_DD));


  // *** Fit ***
  massPDF_LL->fitTo(*data_LL,Save(),NumCPU(2));
  massPDF_DD->fitTo(*data_DD,Save(),NumCPU(2)); 
  
  if(debug){
    // ***** Plot: Mass ***** //
    ////////////////////////////
	
    // *** Signal ***
    RooPlot* mBframe = Bmass->frame(Bins(60));

    // Titles
    mBframe->SetYTitle("# Events/(5 MeV/c^{2})");
    mBframe->SetXTitle("B mass (MeV/c^{2})");

    // Cosmetics
    mBframe->SetTitleOffset(1.2,"y");
    mBframe->SetTitleSize(0.07,"x");
    mBframe->SetTitleSize(0.07,"y");
    mBframe->SetTitleFont(132,"y");
    mBframe->SetTitleFont(132,"x");
    mBframe->SetLabelSize(0.05,"y");
    mBframe->SetLabelSize(0.05,"x");
    mBframe->SetLabelFont(132,"x");
    mBframe->SetLabelFont(132,"y");

    data_LL->plotOn(mBframe,MarkerStyle(20),MarkerSize(1),MarkerColor(2));
    massPDF_LL->plotOn(mBframe,Components("exponential_LL"),LineColor(1),LineWidth(2));
    massPDF_LL->plotOn(mBframe,LineColor(2),LineWidth(2));
  
    data_DD->plotOn(mBframe,MarkerStyle(20),MarkerSize(1),MarkerColor(4));
    massPDF_DD->plotOn(mBframe,Components("exponential_DD"),LineColor(3),LineWidth(2));
    massPDF_DD->plotOn(mBframe,LineColor(4),LineWidth(2));

    mBframe->SetMinimum(0.9);
    mBframe->SetMaximum(10000);

	  // *** Canvas ***
    TCanvas *doek_mass = new TCanvas("doek_mass","B Mass Spectrum",900,800);
    doek_mass->SetLeftMargin(0.2);
    doek_mass->SetBottomMargin(0.15);
    doek_mass->cd(1);
    gPad->SetLogy(1);
    mBframe->Draw("");
  }
  
  // ***** sPlot ***** //
  ///////////////////////
  
  std::cout << " " << std::endl;
  std::cout << "==============" << std::endl;
  std::cout << "== sWeights ==" << std::endl;
  std::cout << "==============" << std::endl;
  
  RooRealVar *sWeight = new RooRealVar("sWeight","sWeight for component",0);

	// ***** sWeighted Datasets - LL ***** //
  /////////////////////////////////////////
  
  // *** sWeighted Dataset ***
  // Initialise
  RooArgSet *sWeightVar = (RooArgSet *)data_LL->get();
  RooRealVar *sWeight_Blife = (RooRealVar *)sWeightVar->find(Blife->GetName());
  //Double_t tot_LL = sData_LL->GetYieldFromSWeight("n"+what+"_LL");
  RooDataSet *Data_sWeight_LL = new RooDataSet("Data_sWeight_LL","sWeighted Dataset",RooArgSet(*Blife,*sWeight),WeightVar(*sWeight));
		
  // Get Weights
  RooStats::SPlot *sData_LL = new RooStats::SPlot("sData_LL","sData", *data_LL, massPDF_LL, RooArgSet(*nBkg_LL,*nBd_LL,*nBs_LL));
  for(Int_t i=0; i<nEvents_LL; i++){	
    data_LL->get(i);
    Blife->setVal(sWeight_Blife->getVal());
    sWeight->setVal(sData_LL->GetSWeight(i,"nBd_LL"));
    Data_sWeight_LL->add(RooArgSet(*Blife,*sWeight),sWeight->getVal());	
  }
  
  // ***** sWeighted Datasets - DD ***** //
  /////////////////////////////////////////

  // *** sWeighted Dataset ***
  // Initialise
  sWeightVar = (RooArgSet *)data_DD->get();
  sWeight_Blife = (RooRealVar *)sWeightVar->find(Blife->GetName());
  RooDataSet *Data_sWeight_DD = new RooDataSet("Data_sWeight_DD","sWeighted Dataset",RooArgSet(*Blife,*sWeight),WeightVar(*sWeight));
		
  // Get Weights
  RooStats::SPlot *sData_DD = new RooStats::SPlot("sData_DD","sData", *data_DD, massPDF_DD, RooArgSet(*nBkg_DD,*nBd_DD,*nBs_DD));
  for(Int_t i=0; i<nEvents_DD; i++){	
    data_DD->get(i);
    Blife->setVal(sWeight_Blife->getVal());
    sWeight->setVal(sData_DD->GetSWeight(i,"nBd_DD"));
    Data_sWeight_DD->add(RooArgSet(*Blife,*sWeight),sWeight->getVal());	
  }

// ***** Part III: Determine Acceptance ***** //
////////////////////////////////////////////////	

  std::cout << std::endl;
  std::cout << "== Part III: Determine Acceptance ==" << std::endl;
  std::cout << "====================================" << std::endl;


  // ********** Initialise ********** //
  //////////////////////////////////////
  
	// *** Lifetime ***		
	RooRealVar *tau_Bd = new RooRealVar("tau_Bd","Generated Bd lifetime",1.519,"ps");	// HFAG Fall 2012
  
  // *** Resolution ***	
  RooRealVar *resMean = new RooRealVar("resMean","Resolution - Mean",0.,"ps");
	RooRealVar *coreSigma = new RooRealVar("coreSigma","Resolution - Core Width",0.03,"ps");
	RooRealVar *midSigma = new RooRealVar("midSigma","Resolution - Middle Width",0.06,"ps");
	RooRealVar *tailSigma = new RooRealVar("tailSigma","Resolution - Tail Width",0.10,"ps");
  RooRealVar *Corefrac = new RooRealVar("Corefrac","Fraction of Core", 0.45);
  RooRealVar *Midfrac = new RooRealVar("Midfrac","Fraction of Mid", 0.45);
	
  // *** Acceptance ***
	accX = new RooRealVar("accX","For Acceptance Function",0.9,0.,(setup=="Exp" ? 1. : 1.5));
	accY = new RooRealVar("accY","For Acceptance Function",1.53,0.,5.);
	accZ = new RooRealVar("accZ","For Acceptance Function",2.29, 0. ,10.);	
  accOffset = new RooRealVar("accOffset","For Acceptance Function",0.2, -1.,1.);	
	accVelo = new RooRealVar("accVelo","For Acceptance Function",-0.022,-0.5,0.5);
  

  // ********** Time PDFs ********** //
  /////////////////////////////////////

  // *** Acceptance ***
  RooFormulaVar *acceptance = 0;
  if(setup=="Tan") acceptance = new RooFormulaVar("acceptance","an acceptance function","(2/acos(-1))*@0*TMath::ATan(@1*@3)*(1+@2*@3)",RooArgList(*accX,*accY,*accVelo,*Blife));
  else if(setup=="TanOffset") acceptance = new RooFormulaVar("acceptance","an acceptance function","(2/acos(-1))*@0*TMath::ATan(@1*(@4-@2))*(1+@3*@4)",RooArgList(*accX,*accY,*accOffset,*accVelo,*Blife));
  else if(setup=="Exp") acceptance = new RooFormulaVar("acceptance","an acceptance function","@0*(1-TMath::Exp(-(@4-@2)*@1))*(1+@3*@4)",RooArgList(*accX,*accY,*accOffset,*accVelo,*Blife));
  else if(setup=="Frac") acceptance = new RooFormulaVar("acceptance","an acceptance function","@0*(1+@3*@4)/(1+pow(@2*@4,-@1))",RooArgList(*accX,*accY,*accZ,*accVelo,*Blife));
  else if(setup=="FracOffset") acceptance = new RooFormulaVar("acceptance","an acceptance function","@0*(1+@4*@5)/(1+pow(@2*(@5-@3),-@1))",RooArgList(*accX,*accY,*accZ,*accOffset,*accVelo,*Blife));
 
  // *** Resolution ***	
  RooGaussModel *core = new RooGaussModel("core","Core Gaussian",*Blife,*resMean,*coreSigma);
  RooGaussModel *mid = new RooGaussModel("mid","Middle Gaussian",*Blife,*resMean,*midSigma);
  RooGaussModel *tail = new RooGaussModel("tail","Tail Gaussian",*Blife,*resMean,*tailSigma);
  RooAddModel *Res_Model = new RooAddModel("Res_Model","Resolution Model",RooArgList(*core,*mid,*tail),RooArgList(*Corefrac,*Midfrac));
 
  // *** RooDecays ***
	RooDecay *decay_Bd = new RooDecay("decay_Bd","Long Lifetimes",*Blife,*tau_Bd,*Res_Model,RooDecay::SingleSided);  
  RooEffProd *decay_acc = new RooEffProd("decay_acc","Decay with acceptance",*decay_Bd,*acceptance);

  // ********** Lifetime Fits ********** //
  /////////////////////////////////////////
  
  char buffer[3];
  Int_t NNVal_LL = NNcut_LL*100;
  Int_t NNVal_DD = NNcut_DD*100;
  std::sprintf(buffer,"_NN%d+%d",NNVal_LL,NNVal_DD);
  
  // *** Long Ks ***
  TString tauString("sWeightedBdAccFit_LL_Acc"+setup);
  tauString.Append(buffer);
  
  double Minuit_tauFit_LL[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
  // Resolution: Correct PVs
  coreSigma->setVal(0.0340);
  midSigma->setVal(0.0648);
  tailSigma->setVal(0.379);
  Corefrac->setVal(0.63);
  Midfrac->setVal(0.36);

  FitPlotTau("Reco",tauString,Data_sWeight_LL,decay_acc,Minuit_tauFit_LL);
  
  
  // *** Down Ks ***
  tauString = "sWeightedBdAccFit_DD_Acc"+setup;
  tauString.Append(buffer);
  
  double Minuit_tauFit_DD[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
  // Resolution: Correct PVs
  coreSigma->setVal(0.0398);
  midSigma->setVal(0.0721);
  tailSigma->setVal(0.210);
  Corefrac->setVal(0.491);
  Midfrac->setVal(0.437);

  FitPlotTau("Reco",tauString,Data_sWeight_DD,decay_acc,Minuit_tauFit_DD);


  // ***** Output ***** //
  ////////////////////////

  std::cout << std::endl;	
  std::cout << "==============================================================" << std::endl;
  std::cout << "== PDF Results (sWeighted Bd->JpsiKs Data): Reco Decay Time ==" << std::endl;
  std::cout << "==============================================================" << std::endl;
  if(setup=="Exp") std::cout << "Acceptance Model: x*(1-Exp[-y*(tau-offset)])*(1+beta*tau)" << std::endl;
  else if(setup=="Tan") std::cout << "Acceptance Model: (2/acos(-1))*x*ArcTan[y*tau]*(1+beta*tau)" << std::endl;
  else if(setup=="TanOffset") std::cout << "Acceptance Model: (2/acos(-1))*x*ArcTan[y*(tau-offset)]*(1+beta*tau)" << std::endl;
  else if(setup=="Frac") std::cout << "Acceptance Model: x*(1+beta*tau)/(1+(z*tau)^-y)" << std::endl;
  else if(setup=="FracOffset") std::cout << "Acceptance Model: x*(1+beta*tau)/(1+(z*[tau-offset])^-y)" << std::endl;
  std::cout << std::endl;
  std::cout << "== Lifetime Fit: Optimal Neural Net ==" << std::endl;
  std::cout << "== Long KS ==" << std::endl;
  if(Minuit_tauFit_LL[0]!=-999) std::cout << "x = " << Minuit_tauFit_LL[0] << " +/- " << Minuit_tauFit_LL[1] << std::endl;
  if(Minuit_tauFit_LL[2]!=-999) std::cout << "y = " << Minuit_tauFit_LL[2] << " +/- " << Minuit_tauFit_LL[3] << std::endl;
  if(Minuit_tauFit_LL[4]!=-999) std::cout << "z = " << Minuit_tauFit_LL[4] << " +/- " << Minuit_tauFit_LL[5] << std::endl;
  if(Minuit_tauFit_LL[6]!=-999) std::cout << "offset = " << Minuit_tauFit_LL[6] << " +/- " << Minuit_tauFit_LL[7] << std::endl;
  if(Minuit_tauFit_LL[8]!=-999) std::cout << "beta = " << Minuit_tauFit_LL[8] << " +/- " << Minuit_tauFit_LL[9] << std::endl;
	std::cout << std::endl;
  std::cout << "== Downstream KS ==" << std::endl;
  if(Minuit_tauFit_DD[0]!=-999) std::cout << "x = " << Minuit_tauFit_DD[0] << " +/- " << Minuit_tauFit_DD[1] << std::endl;
  if(Minuit_tauFit_DD[2]!=-999) std::cout << "y = " << Minuit_tauFit_DD[2] << " +/- " << Minuit_tauFit_DD[3] << std::endl;
  if(Minuit_tauFit_DD[4]!=-999) std::cout << "z = " << Minuit_tauFit_DD[4] << " +/- " << Minuit_tauFit_DD[5] << std::endl;
  if(Minuit_tauFit_DD[6]!=-999) std::cout << "offset = " << Minuit_tauFit_DD[6] << " +/- " << Minuit_tauFit_DD[7] << std::endl;
  if(Minuit_tauFit_DD[8]!=-999) std::cout << "beta = " << Minuit_tauFit_DD[8] << " +/- " << Minuit_tauFit_DD[9] << std::endl;
	std::cout << std::endl;

}


/////////////////////////////////
// ***** Helper Function ***** //
/////////////////////////////////
void FitPlotEff(TString label, TString tag, RooDataSet *Data, RooFormulaVar *acceptance, RooCategory *Dec, double *Results){
  
  // ********** Efficiency Fit ********** //
  //////////////////////////////////////////
	
	// Model
	RooEfficiency *effPdf = new RooEfficiency("effPdf","Efficiency Function",*acceptance,*Dec,"Accept");

  // Fit
	Blife->setRange("detached", 0.2, 10.);
  RooFitResult *fitresult = effPdf->fitTo(*Data,Range("detached"),ConditionalObservables(*Blife),Save(),PrintEvalErrors(0),NumCPU(2));
	
	// Obtaining information from fitted PDF
	if(fitresult->covQual()==3){

    const RooArgList& fitted_par = fitresult->floatParsFinal();
	
		RooRealVar *temp_accX = (RooRealVar*)fitted_par.find("accX");
    if(temp_accX){
      Results[0] = temp_accX->getVal();
      Results[1] = temp_accX->getError();
      delete temp_accX;
    }
    RooRealVar *temp_accY = (RooRealVar*)fitted_par.find("accY");
    if(temp_accY){
      Results[2] = temp_accY->getVal();
      Results[3] = temp_accY->getError();
      delete temp_accY;
		}
    RooRealVar *temp_accZ = (RooRealVar*)fitted_par.find("accZ");
    if(temp_accZ){
      Results[4] = temp_accZ->getVal();
      Results[5] = temp_accZ->getError();
      delete temp_accZ;
    }
    RooRealVar *temp_accOffset = (RooRealVar*)fitted_par.find("accOffset");
    if(temp_accOffset){
      Results[6] = temp_accOffset->getVal();
      Results[7] = temp_accOffset->getError();
      delete temp_accOffset;
    }
    RooRealVar *temp_accVelo = (RooRealVar*)fitted_par.find("accVelo");
    if(temp_accVelo){
      Results[8] = temp_accVelo->getVal();
      Results[9] = temp_accVelo->getError();
      delete temp_accVelo;
    }
  }

	// ***** Plot Model: Efficiency ***** //
	////////////////////////////////////////
	
	// *** Signal ***
	RooPlot* effBframe = Blife->frame(Range(0.,15.),Bins(75));

	// Titles
	effBframe->SetYTitle("Efficiency/(0.20 ps)");
  effBframe->SetXTitle(label+" B decay time (ps)");

	// Cosmetics
	effBframe->SetTitleOffset(1.2,"y");
	effBframe->SetTitleSize(0.07,"x");
	effBframe->SetTitleSize(0.07,"y");
	effBframe->SetTitleFont(132,"y");
	effBframe->SetTitleFont(132,"x");
	effBframe->SetLabelSize(0.05,"y");
	effBframe->SetLabelSize(0.05,"x");
	effBframe->SetLabelFont(132,"x");
	effBframe->SetLabelFont(132,"y");

	Data->plotOn(effBframe,Efficiency(*Dec),MarkerStyle(8),MarkerSize(0.8));
	
	effBframe->SetMinimum(0.);
	effBframe->SetMaximum(1.05);
		
	if(fitresult->covQual()==3){
	  acceptance->plotOn(effBframe,LineColor(2),LineWidth(2));	
    
    effBframe->SetMinimum(0.);
	  effBframe->SetMaximum(1.05);	

	  // Canvas
    PullPlot(tag+"_"+label+"Lifetime.pdf",effBframe,0);
  }
	else{
	  // *** Canvas ***
    TCanvas *doek = new TCanvas("doek","Observable",900,800);
    doek->SetLeftMargin(0.2);
    doek->SetBottomMargin(0.15);
    doek->cd(1);
    effBframe->Draw("");
		
		// *** LHCb Tag *** 
	  TPaveText *lhcbTag = 0;
	  lhcbTag = new TPaveText(0.65,0.27,0.89,0.39,"NDC");

    lhcbTag->SetFillColor(0);
    lhcbTag->SetTextAlign(32);
    lhcbTag->SetBorderSize(0);
    lhcbTag->SetTextSize(0.05);
    lhcbTag->SetTextFont(132);
		lhcbTag->AddText("#splitline{LHCb MC11}{#scale[0.7]{Bd2JpsiKs}}");

    lhcbTag -> Draw("");
		
		doek->SaveAs(tag+"_"+label+"Lifetime.pdf");
		
	}

	// Clean up
	delete effBframe;

	return;
}

void FitPlotTau(TString label, TString tag, RooDataSet *Data, RooAbsPdf *decay, double *Results){


  // ********** Selection Cuts ********** //
  //////////////////////////////////////////
  string convSave (tag);
  
  accX->setVal(1);
  accX->setConstant();
  Blife->setRange("detached",0.2 ,15.);
  RooFitResult *fitresult = 0;
 
  if(convSave.find("sWeighted")!=string::npos) fitresult = (RooFitResult *) decay->fitTo(*Data,Range("detached"),SumW2Error(true),Save());
  else fitresult = (RooFitResult *) decay->fitTo(*Data,Range("detached"),Save());
 
	if(fitresult && fitresult->covQual()!=0){

    const RooArgList& fitted_par = fitresult->floatParsFinal();
	
		RooRealVar *temp_accX = (RooRealVar*)fitted_par.find("accX");
    if(temp_accX){
      Results[0] = temp_accX->getVal();
      Results[1] = temp_accX->getError();
      delete temp_accX;
    }
    RooRealVar *temp_accY = (RooRealVar*)fitted_par.find("accY");
    if(temp_accY){
      Results[2] = temp_accY->getVal();
      Results[3] = temp_accY->getError();
      delete temp_accY;
		}
    RooRealVar *temp_accZ = (RooRealVar*)fitted_par.find("accZ");
    if(temp_accZ){
      Results[4] = temp_accZ->getVal();
      Results[5] = temp_accZ->getError();
      delete temp_accZ;
    }
    RooRealVar *temp_accOffset = (RooRealVar*)fitted_par.find("accOffset");
    if(temp_accOffset){
      Results[6] = temp_accOffset->getVal();
      Results[7] = temp_accOffset->getError();
      delete temp_accOffset;
    }
    RooRealVar *temp_accVelo = (RooRealVar*)fitted_par.find("accVelo");
    if(temp_accVelo){
      Results[8] = temp_accVelo->getVal();
      Results[9] = temp_accVelo->getError();
      delete temp_accVelo;
    }
    RooRealVar *temp_tau_Bd = (RooRealVar*)fitted_par.find("tau_Bd");
    if(temp_tau_Bd){
      Results[0] = temp_tau_Bd->getVal();
      Results[1] = temp_tau_Bd->getError();
      delete temp_tau_Bd;
    }
  }
  
	// ***** Plot ***** //
  //////////////////////
	
	// *** Frame ***
	RooPlot* BlifeFrame = Blife->frame(Range(0.,15.),Bins(75));

	// Titles
	BlifeFrame->SetYTitle("Events/(0.20 ps)");
	BlifeFrame->SetXTitle(label+" B decay time (ps)");

	// Cosmetics
	BlifeFrame->SetTitleOffset(1.2,"y");
	BlifeFrame->SetTitleSize(0.07,"x");
	BlifeFrame->SetTitleSize(0.07,"y");
	BlifeFrame->SetTitleFont(132,"y");
	BlifeFrame->SetTitleFont(132,"x");
	BlifeFrame->SetLabelSize(0.05,"y");
	BlifeFrame->SetLabelSize(0.05,"x");
	BlifeFrame->SetLabelFont(132,"x");
	BlifeFrame->SetLabelFont(132,"y");

  Data->plotOn(BlifeFrame,MarkerStyle(8),MarkerSize(0.8));
  decay->plotOn(BlifeFrame,Components("decay_acc"), LineWidth(2),LineColor(2));
  decay->plotOn(BlifeFrame,Components("decayW_acc"), LineWidth(2),LineColor(3));
  decay->plotOn(BlifeFrame,LineWidth(2),LineColor(4));
  
  BlifeFrame->SetMinimum(1.);
  BlifeFrame->SetMaximum(10000);

  if(convSave.find("sWeighted")!=string::npos) BlifeFrame->SetMaximum(2000);
  
  PullPlot(tag+"_"+label+"Lifetime.pdf",BlifeFrame,1);
}


/////////////////////////////////
// ***** Helper Function ***** //
/////////////////////////////////
void PullPlot(TString savestring, RooPlot* frame, Int_t logy){
  // *** Canvas ***
  TCanvas *doek = new TCanvas("doek","Observable",900,800);
	doek->cd(1);
	Float_t ratio = 0.30; // Percentage of the plot for Pull distributions
	
	// *** Pull Plot ***
  RooPlot* pullframe = (RooPlot *)frame->emptyClone("pullframe");
	
	// Titles
  pullframe->SetYTitle("Pull");
  pullframe->SetXTitle(frame->GetXaxis()->GetTitle());

  // Cosmetics
  pullframe->SetTitleOffset(0.9,"x");
  pullframe->SetTitleSize(0.07,"x");
  pullframe->SetTitleFont(132,"x");
  pullframe->SetLabelSize(0.05,"x");
  pullframe->SetLabelFont(132,"x");
  pullframe->SetTitleSize(0,"y");// No title here	
	pullframe->SetLabelSize(0.03,"y");// and no labels
  pullframe->SetLabelFont(132,"y");	
	
	// Fill - And specify plot option: Bar-chart
	pullframe->addObject((TObject*)frame->pullHist(),"B");
	// Extract the histogram in orde to apply plot options
	TGraph* pullgraph = (TGraph*) pullframe->getObject(0);
	//pullgraph->SetLineWidth(2);
	pullgraph->SetFillColor(4);
	pullgraph->SetFillStyle(1001);
	
	// General Settings
  pullframe->SetMinimum(-5);
	pullframe->SetMaximum(5);
	pullframe->GetYaxis()->SetNdivisions(503,kTRUE);
	
	// *** Place the first frame ***
	// To keep the correct scale of the labels, use the Margins instead of Pad coordinates
	TPad* xPad = new TPad("xPad", "Pad for Observable Plot", 0., 0, 1., 1.);
	xPad->SetLeftMargin(0.2);
	xPad->SetBottomMargin(ratio);	
	// Draw Pad	
	xPad->Draw();
	xPad->cd();
	xPad->SetLogy(logy);
	// Suppress X-axis decoration
	frame->SetLabelSize(0,"x");
	frame->SetTitleSize(0,"x");
  frame->SetLabelOffset(0.015,"y");
	// Fill Pad	
	frame->Draw("");
	
	
  // *** LHCb Tag *** 
  string convSave (savestring);
  size_t isBs=convSave.find("Bs");
  size_t isData=convSave.find("sWeighted");
  size_t isLL=convSave.find("LL");
  size_t isDD=convSave.find("DD");
  
  TString track("");
  if(isLL!=string::npos) track = "Long K_{S}^{0}";
  else if(isDD!=string::npos) track = "Downstream K_{S}^{0}";
  
  // *** LHCb Tag ***
  size_t found=convSave.find("Abs");
	TPaveText *lhcbTag = 0;
	//if(logy==1){lhcbTag = new TPaveText(0.22,0.75,0.46,0.89,"NDC");}
  if(logy==1) lhcbTag = new TPaveText(0.65,0.70,0.89,0.89,"NDC");
	//else if(logy==0 && found!=string::npos) lhcbTag = new TPaveText(0.23,0.70,0.47,0.89,"NDC");
  else if(logy==0 && found!=string::npos) lhcbTag = new TPaveText(0.65,0.35,0.89,0.54,"NDC");
  else if(logy==0 && found==string::npos) lhcbTag = new TPaveText(0.65,0.35,0.89,0.54,"NDC");

  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  if(isBs!=string::npos) lhcbTag->AddText("#splitline{LHCb MC11a}{#splitline{#scale[0.7]{B_{s}^{0}#rightarrow J/#psi K_{S}^{0}}}{#scale[0.7]{"+track+"}}}");
  else if(isData!=string::npos) lhcbTag->AddText("#splitline{LHCb 2011}{#splitline{#scale[0.7]{Reco 12 - Stripping 17b}}{#scale[0.7]{"+track+"}}}");
  else lhcbTag->AddText("#splitline{LHCb MC11a}{#splitline{#scale[0.7]{B_{d}^{0}#rightarrow J/#psi K_{S}^{0}}}{#scale[0.7]{"+track+"}}}");
  lhcbTag->Draw();
	
	// *** Place the second frame ***
	// go back to the Bottom layer
	doek->cd();
	// To keep the correct scale of the labels, use the Margins instead of Pad coordinates
	TPad* pullPad = new TPad("pullPad", "Pad for Pull Plot", 0., 0., 1., 1);
	pullPad->SetLeftMargin(0.2);
	pullPad->SetBottomMargin(0.15);	
	pullPad->SetTopMargin(1-ratio+0.01);
	// Make the pad transparent
	pullPad->SetFillColor(0);
	pullPad->SetFillStyle(0);
	// Draw Pad	
	pullPad->Draw();
	pullPad->cd();
	// Fill Pad - Draw Y axis on the right side such that it doesn't overlap
	pullframe->Draw("");

	// *** Save ***
	doek->SaveAs(savestring);
	
	// *** Clean Up ***
	delete lhcbTag;
	delete xPad;
	delete pullPad;
	delete pullframe;
	delete doek;
	return;
}
