////////////////////////////////////////////////////////////////////////////
// ***** Compare Bd->JpsiKs and Bs->JpsiKs Monte Carlo Data Samples ***** //
////////////////////////////////////////////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb
// - Resolution from Monte Carlo


/////////////////////////////////////
// ***** Load useful classes ***** //
/////////////////////////////////////

#include "RooAddModel.h"
#include "RooAddPdf.h"
#include "RooCBShape.h"
#include "RooChebychev.h"
#include "RooDataSet.h"
#include "RooDecay.h"
#include "RooExponential.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooGaussModel.h"
#include "RooPlot.h"
#include "RooRealVar.h"

#include "RooStats/SPlot.h"

#include "TCanvas.h"
#include "TChain.h"
#include "TF1.h"
#include "TFile.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TMath.h"
#include "TPaveText.h"

using namespace RooFit;

//////////////////////////////
// ***** Declarations ***** //
//////////////////////////////
void FitResolution(RooDataSet *data, RooRealVar *time, double *Minuit, TString saveString);
void FitWrongPV(RooDataSet *data, RooRealVar *time, double *Minuit, TString saveString);
void FitPrescaled(RooDataSet *data, RooRealVar *time, double *Minuit, TString saveString);
void PullPlot(TString savestring, RooPlot* frame, Int_t logy=0);

///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void MCResolution(TString what, Double_t NNCut = 1){

// ***** Initialize ***** //
////////////////////////////

  Double_t NNcut_LL = (NNCut>=1 ? 0.60 : NNCut);
  Double_t NNcut_DD = (NNCut>=1 ? 0.75 : NNCut);

  // *** Plot Ranges ***
  Double_t Bmass_min = 5180;
  Double_t Bmass_max = 5520;


// ***** Part I: From NTuple to DataSet ***** //
////////////////////////////////////////////////

// This is done to easily handle the selection cuts and allows semi-automatic looping over these cuts

  std::cout << " " << std::endl;
  std::cout << "== Part I: From NTuple to DataSet ==" << std::endl;
  std::cout << "====================================" << std::endl;

  // ***** Load NTuples ***** //
  //////////////////////////////

  TFile* netFile = TFile::Open("B2JpsiKs-Eval-2-random-"+what+"Prescaled.root");
  TTree* neural_net = (TTree*)netFile->Get("NetTree");

  TChain* chain = new TChain("chain");
  chain->Add("B2JpsiKs-Slim-"+what+"Prescaled.root/Slim_B2JpsiKs_Tuple");;
  chain->AddFriend(neural_net);
  
  Long64_t nEntries_NTuple = chain->GetEntries();
  //nEntries_NTuple = 10000;  
  std::cout << "Number of entries from DaVinci: " << nEntries_NTuple << std::endl;    


  // ***** Define DataSet Observables ***** //
  ////////////////////////////////////////////

  // *** Define Observables & Selection Variables ***
        
  // Observable
  Float_t B_FullFit_ctau[10];
  Double_t B_TRUETAU = -999;
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
  chain->SetBranchAddress("B_TRUETAU", &B_TRUETAU);
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
  

  // ***** Initialize DataSet ***** //
  ////////////////////////////////////

  // *** Observable ***
  RooRealVar *Btrue = new RooRealVar("Btrue","lifetime",0.,"ps");
  RooRealVar *Breco = new RooRealVar("Breco","lifetime",0.,"ps");
  RooRealVar *Bdiff = new RooRealVar("Bdiff","lifetime",0.,"ps");

  // *** DataSet ***
  RooArgSet *Obs = new RooArgSet(*Btrue,*Breco,*Bdiff);
  RooDataSet *data_close_LL = new RooDataSet("data_close_LL","Unbinned dataset",*Obs);
  RooDataSet *data_close_DD = new RooDataSet("data_close_DD","Unbinned dataset",*Obs);
  RooDataSet *data_wrong_LL = new RooDataSet("data_wrong_LL","Unbinned dataset",*Obs);
  RooDataSet *data_wrong_DD = new RooDataSet("data_wrong_DD","Unbinned dataset",*Obs);

  // ***** Loop over Entries: Apply Selection Cuts ***** //
  /////////////////////////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Loop 1: Selection Cuts ==" << std::endl;
  std::cout << "============================" << std::endl;
  
  // Initialise
  Double_t DOCA = 0;
  Double_t DOCA_min = 999;
  Int_t truePV = 0;
  bool TruthMatch = false;
  bool Trigger = false;
  
  for(Long64_t i=0; i<nEntries_NTuple; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_NTuple << " (" << 100*i/nEntries_NTuple << "%)" << std::endl;
    
    if((what=="SigBd") && TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && (B_BKGCAT==0 || B_BKGCAT==10)) TruthMatch = true;
    else if((what=="SigBs") && TMath::Abs(B_TRUEID)==531 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && B_BKGCAT==20) TruthMatch = true;
    else TruthMatch = false;
    
    Trigger = (PsiHlt1TrackMuonDecision_TOS || PsiHlt1DiMuonHighMassDecision_TOS || PsiHlt1TrackAllL0Decision_TOS) &&
             (PsiHlt2DiMuonDetachedJPsiDecision_TOS || PsiHlt2DiMuonJPsiHighPTDecision_TOS || PsiHlt2DiMuonJPsiDecision_TOS ||
              PsiHlt2TopoMu2BodyBBDTDecision_TOS);
    
    if(TruthMatch && Trigger){
      // Loop 1: Determine DOCA
      for(Int_t pv = 0; pv < nPV2 ; pv++){
        DOCA = TMath::Sqrt(pow(B_TRUEORIGINVERTEX_X-B_FullFit_PV_X[pv],2) + pow(B_TRUEORIGINVERTEX_Y-B_FullFit_PV_Y[pv],2) + pow(B_TRUEORIGINVERTEX_Z-B_FullFit_PV_Z[pv],2));
        if(DOCA<DOCA_min){
          DOCA_min = DOCA;
          truePV = pv;
        }
      }
    
      for(Int_t pv = 0; pv < nPV2 ; pv++){
        if(B_FullFit_M[pv]>Bmass_min && B_FullFit_M[pv]<Bmass_max && Trigger && ((piminus_TRACK_Type==3 && netOutput[pv]>NNcut_LL) || (piminus_TRACK_Type==5 && netOutput[pv]>NNcut_DD))){
          Btrue->setVal(1000*B_TRUETAU);
          Breco->setVal(B_FullFit_ctau[pv]*pow(10.,12)/(299792458*pow(10.,3)));
          Bdiff->setVal(B_FullFit_ctau[pv]*pow(10.,12)/(299792458*pow(10.,3)) - 1000*B_TRUETAU);	// convert from mm/c to ps
          if(pv==truePV){
            if(piminus_TRACK_Type==3) data_close_LL->add(*Obs);
            else if(piminus_TRACK_Type==5) data_close_DD->add(*Obs);
          }
          else{
            if(piminus_TRACK_Type==3) data_wrong_LL->add(*Obs);
            else if(piminus_TRACK_Type==5) data_wrong_DD->add(*Obs);
          }
        }
      }
    }
  }
  
  Int_t nClose_LL = data_close_LL->numEntries() ;
  Int_t nClose_DD = data_close_DD->numEntries() ;
  Int_t nWrong_LL = data_wrong_LL->numEntries() ;
  Int_t nWrong_DD = data_wrong_DD->numEntries() ;
  
// ***** Part II: Determine Resolution ***** //
///////////////////////////////////////////////	

  std::cout << std::endl;
  std::cout << "== Part II: Determine Resolution ==" << std::endl;
  std::cout << "===================================" << std::endl;
  
  char buffer[3];
  Int_t NNVal_LL = NNcut_LL*100;
  Int_t NNVal_DD = NNcut_DD*100;
  std::sprintf(buffer,"_NN%d+%d",NNVal_LL,NNVal_DD);
  
  
  TString saveString("Resolution_LL_"+what);
  if(NNCut>-1) saveString.Append(buffer);
  else saveString.Append("_LooseCuts");
  if(NNCut>1.5 || NNCut<-1.5)saveString.Append("PullOnly");
  saveString.Append("_ClosestPV.pdf");
  
  double Minuit_ResLL[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
  FitResolution(data_close_LL,Bdiff,Minuit_ResLL,saveString);


  saveString = "Resolution_DD_"+what;
  if(NNCut>-1) saveString.Append(buffer);
  else saveString.Append("_LooseCuts");
  if(NNCut>1.5 || NNCut<-1.5)saveString.Append("PullOnly");
  saveString.Append("_ClosestPV.pdf");
  
  double Minuit_ResDD[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
  FitResolution(data_close_DD,Bdiff,Minuit_ResDD,saveString);
  
  
  saveString = "Resolution_LL_"+what;
  if(NNCut>-1) saveString.Append(buffer);
  else saveString.Append("_LooseCuts");
  if(NNCut>1.5 || NNCut<-1.5 || what=="SigBs")saveString.Append("PullOnly");
  saveString.Append("_WrongPV.pdf");
  
  double Minuit_ResLL_Wrong[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
  FitWrongPV(data_wrong_LL,Bdiff,Minuit_ResLL_Wrong,saveString);


  saveString = "Resolution_DD_"+what;
  if(NNCut>-1) saveString.Append(buffer);
  else saveString.Append("_LooseCuts");
  if(NNCut>1.5 || NNCut<-1.5 || what=="SigBs")saveString.Append("PullOnly");
  saveString.Append("_WrongPV.pdf");
  
  double Minuit_ResDD_Wrong[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
  FitWrongPV(data_wrong_DD,Bdiff,Minuit_ResDD_Wrong,saveString);
  
  
  // ***** Output ***** //
  ////////////////////////

  std::cout << std::endl;	
  std::cout << "Long KS: Selected " << nClose_LL << " (Closest PV) and " << nWrong_LL << " (Wrong PVs) events, giving a fraction " << (double) nWrong_LL/(nClose_LL + nWrong_LL) << std::endl;
  std::cout << "Down KS: Selected " << nClose_DD << " (Closest PV) and " << nWrong_DD << " (Wrong PVs) events, giving a fraction " << (double) nWrong_DD/(nClose_DD + nWrong_DD) << std::endl;
  std::cout << std::endl;
  std::cout << "==================================================" << std::endl;
  std::cout << "== PDF Results: Resolution from MC11a for "+what+" ==" << std::endl;
  std::cout << "==================================================" << std::endl;
  std::cout << "Model: Triple Gaussian" << std::endl;
  std::cout << std::endl;
  std::cout << "== Long Long ==" << std::endl;
  std::cout << "mean = " << Minuit_ResLL[0] << " +/- " << Minuit_ResLL[1] << std::endl;
  std::cout << "Core Sigma = " << Minuit_ResLL[2] << " +/- " << Minuit_ResLL[3] << std::endl;
  std::cout << "Mid  Sigma = " << Minuit_ResLL[4] << " +/- " << Minuit_ResLL[5] << std::endl;
  std::cout << "Tail Sigma = " << Minuit_ResLL[6] << " +/- " << Minuit_ResLL[7] << std::endl;
  std::cout << "Core Fraction = " << Minuit_ResLL[8] << " +/- " << Minuit_ResLL[9] << std::endl;
  std::cout << "Mid  Fraction = " << Minuit_ResLL[10] << " +/- " << Minuit_ResLL[11] << std::endl;
  std::cout << std::endl;
  std::cout << "Core Mean = " << Minuit_ResLL_Wrong[0] << " +/- " << Minuit_ResLL_Wrong[1] << std::endl;
  std::cout << "Tail Mean = " << Minuit_ResLL_Wrong[2] << " +/- " << Minuit_ResLL_Wrong[3] << std::endl;
  std::cout << "Core Sigma = " << Minuit_ResLL_Wrong[4] << " +/- " << Minuit_ResLL_Wrong[5] << std::endl;
  std::cout << "Tail Sigma = " << Minuit_ResLL_Wrong[6] << " +/- " << Minuit_ResLL_Wrong[7] << std::endl;
  std::cout << "Core Fraction = " << Minuit_ResLL_Wrong[8] << " +/- " << Minuit_ResLL_Wrong[9] << std::endl;
  std::cout << std::endl;
  std::cout << "== Down Down ==" << std::endl;
  std::cout << "mean = " << Minuit_ResDD[0] << " +/- " << Minuit_ResDD[1] << std::endl;
  std::cout << "Core Sigma = " << Minuit_ResDD[2] << " +/- " << Minuit_ResDD[3] << std::endl;
  std::cout << "Mid  Sigma = " << Minuit_ResDD[4] << " +/- " << Minuit_ResDD[5] << std::endl;
  std::cout << "Tail Sigma = " << Minuit_ResDD[6] << " +/- " << Minuit_ResDD[7] << std::endl;
  std::cout << "Core Fraction = " << Minuit_ResDD[8] << " +/- " << Minuit_ResDD[9] << std::endl;
  std::cout << "Mid  Fraction = " << Minuit_ResDD[10] << " +/- " << Minuit_ResDD[11] << std::endl;
  std::cout << std::endl;
  std::cout << "Core Mean = " << Minuit_ResDD_Wrong[0] << " +/- " << Minuit_ResDD_Wrong[1] << std::endl;
  std::cout << "Tail Mean = " << Minuit_ResDD_Wrong[2] << " +/- " << Minuit_ResDD_Wrong[3] << std::endl;
  std::cout << "Core Sigma = " << Minuit_ResDD_Wrong[4] << " +/- " << Minuit_ResDD_Wrong[5] << std::endl;
  std::cout << "Tail Sigma = " << Minuit_ResDD_Wrong[6] << " +/- " << Minuit_ResDD_Wrong[7] << std::endl;
  std::cout << "Core Fraction = " << Minuit_ResDD_Wrong[8] << " +/- " << Minuit_ResDD_Wrong[9] << std::endl;
}

///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void RDResolution(TString what = "Bkg", TString model = "",Double_t NNCut = 0.5){

// ***** Initialize ***** //
////////////////////////////

  bool debug = false;
  
  Double_t NNcut_LL = (NNCut==1 ? 0.60 : NNCut);
  Double_t NNcut_DD = (NNCut==1 ? 0.75 : NNCut);

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
	
  TFile* netFile = TFile::Open("B2JpsiKs-Eval-2-random-Prescaled.root");// Double Net
  TTree* neural_net = (TTree*)netFile->Get("NetTree");

  TChain* chain = new TChain("chain");
  chain->Add("B2JpsiKs-Slim-Prescaled.root/Slim_B2JpsiKs_Tuple");
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
  RooRealVar *Blife = new RooRealVar("Blife","lifetime",-10.,20.,"ps");

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
  std::cout << "== Part II: sWeights/High Mass Sideband ==" << std::endl;
  std::cout << "==========================================" << std::endl;
  
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
  RooRealVar *apar_I_LL = new RooRealVar("apar_I_LL","A parameter of Crystal Ball I",1.3474);
  RooRealVar *apar_I_DD = new RooRealVar("apar_I_DD","A parameter of Crystal Ball I",2.1848);
  RooRealVar *apar_II_LL = new RooRealVar("apar_II_LL","A parameter of Crystal Ball II",-1.4741);
  RooRealVar *apar_II_DD = new RooRealVar("apar_II_DD","A parameter of Crystal Ball II",-2.2193);
  RooRealVar *npar_I_LL = new RooRealVar("npar_I_LL","N parameter of Crystal Ball I",3.8154);
  RooRealVar *npar_I_DD = new RooRealVar("npar_I_DD","N parameter of Crystal Ball I",1.9771);
  RooRealVar *npar_II_LL = new RooRealVar("npar_II_LL","N parameter of Crystal Ball II",7.0071);
  RooRealVar *npar_II_DD = new RooRealVar("npar_II_DD","N parameter of Crystal Ball II",7.2691);
  
  //RooRealVar *lambda_LL = new RooRealVar("lambda_LL","decay constant",-0.0027,-0.1,0.);
  RooRealVar *poly_I = new RooRealVar("poly_I","combi bkg",-0.11 , -0.3, 0.3);
  RooRealVar *poly_II = new RooRealVar("poly_II","combi bkg",-0.03 , -1., 0.);
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
  //RooExponential *exponential_LL = new RooExponential("exponential_LL","Exponential for background",*Bmass,*lambda_LL);
  RooChebychev* exponential_LL = new RooChebychev("exponential_LL","Combi background", *Bmass, RooArgList(*poly_I, *poly_II));
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
  if(what!="MassSidebands"){
    massPDF_LL->fitTo(*data_LL,Save(),NumCPU(2));
    //massPDF_DD->fitTo(*data_DD,Save(),NumCPU(2)); 
  }
  
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
	
  // *** Mass Sidebands ***
  RooDataSet *Data_sWeight_LL = 0;
  if(what=="MassSidebands") Data_sWeight_LL = (RooDataSet *) data_LL->reduce("Bmass>5400");
  
  // *** sWeighted Dataset ***
  else{
    // Initialise
    RooArgSet *sWeightVar = (RooArgSet *)data_LL->get();
	  RooRealVar *sWeight_Blife = (RooRealVar *)sWeightVar->find(Blife->GetName());
    //Double_t tot_LL = sData_LL->GetYieldFromSWeight("n"+what+"_LL");
    Data_sWeight_LL = new RooDataSet("Data_sWeight_LL","sWeighted Dataset",RooArgSet(*Blife,*sWeight),WeightVar(*sWeight));
		
    // Get Weights
    RooStats::SPlot *sData_LL = new RooStats::SPlot("sData_LL","sData", *data_LL, massPDF_LL, RooArgSet(*nBkg_LL,*nBd_LL,*nBs_LL));
	  for(Int_t i=0; i<nEvents_LL; i++){	
	    data_LL->get(i);
	    Blife->setVal(sWeight_Blife->getVal());
      sWeight->setVal(sData_LL->GetSWeight(i,"n"+what+"_LL"));
      Data_sWeight_LL->add(RooArgSet(*Blife,*sWeight),sWeight->getVal());	
	  }
  }
  
  // ***** sWeighted Datasets - DD ***** //
  /////////////////////////////////////////
  // *** Mass Sidebands ***
  RooDataSet *Data_sWeight_DD = 0;
  if(what=="MassSidebands") Data_sWeight_DD = (RooDataSet *) data_DD->reduce("Bmass>5400");

  // *** sWeighted Dataset ***
  else{
    // Initialise
    RooArgSet *sWeightVar = (RooArgSet *)data_DD->get();
	  RooRealVar *sWeight_Blife = (RooRealVar *)sWeightVar->find(Blife->GetName());
    Data_sWeight_DD = new RooDataSet("Data_sWeight_DD","sWeighted Dataset",RooArgSet(*Blife,*sWeight),WeightVar(*sWeight));
		
    // Get Weights
    RooStats::SPlot *sData_DD = new RooStats::SPlot("sData_DD","sData", *data_DD, massPDF_DD, RooArgSet(*nBkg_DD,*nBd_DD,*nBs_DD));
	  for(Int_t i=0; i<nEvents_DD; i++){	
	    data_DD->get(i);
	    Blife->setVal(sWeight_Blife->getVal());
      sWeight->setVal(sData_DD->GetSWeight(i,"n"+what+"_DD"));
      Data_sWeight_DD->add(RooArgSet(*Blife,*sWeight),sWeight->getVal());	
	  }
  }

// ***** Part III: Determine Resolution ***** //
////////////////////////////////////////////////	

  std::cout << std::endl;
  std::cout << "== Part III: Determine Resolution ==" << std::endl;
  std::cout << "====================================" << std::endl;

  char buffer[3];
  Int_t NNVal_LL = NNcut_LL*100;
  Int_t NNVal_DD = NNcut_DD*100;
  std::sprintf(buffer,"_NN%d+%d",NNVal_LL,NNVal_DD);
  TString saveString("Resolution_LL_"+what);
  saveString.Append(buffer);
  saveString.Append(model+".pdf");
  // Model Option: "", _MC, PullOnly, PullOnly_MC, _Gauss, _GaussWide
  
  double Minuit_ResLL[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
  FitPrescaled(Data_sWeight_LL,Blife,Minuit_ResLL,saveString);


  saveString = "Resolution_DD_"+what;
  saveString.Append(buffer);
  saveString.Append(model+".pdf");
  
  double Minuit_ResDD[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
  FitPrescaled(Data_sWeight_DD,Blife,Minuit_ResDD,saveString);

  // ***** Output ***** //
  ////////////////////////

  std::cout << std::endl;	
  std::cout << "==================================================" << std::endl;
  std::cout << "== PDF Results: Resolution for "+what+" ==" << std::endl;
  std::cout << "==================================================" << std::endl;
  std::cout << "Model: Triple Gaussian" << std::endl;
  std::cout << std::endl;
  std::cout << "== Long Long ==" << std::endl;
  std::cout << "mean = " << Minuit_ResLL[0] << " +/- " << Minuit_ResLL[1] << std::endl;
  std::cout << "Core Sigma = " << Minuit_ResLL[2] << " +/- " << Minuit_ResLL[3] << std::endl;
  std::cout << "Mid  Sigma = " << Minuit_ResLL[4] << " +/- " << Minuit_ResLL[5] << std::endl;
  std::cout << "Tail Sigma = " << Minuit_ResLL[6] << " +/- " << Minuit_ResLL[7] << std::endl;
  std::cout << "Core Fraction = " << Minuit_ResLL[8] << " +/- " << Minuit_ResLL[9] << std::endl;
  std::cout << "Mid  Fraction = " << Minuit_ResLL[10] << " +/- " << Minuit_ResLL[11] << std::endl;
  std::cout << std::endl;
  std::cout << "Fraction = " << Minuit_ResLL[12] << " +/- " << Minuit_ResLL[13] << std::endl;
  std::cout << "Tau Long = " << Minuit_ResLL[14] << " +/- " << Minuit_ResLL[15] << std::endl;
  std::cout << std::endl;
  std::cout << "== Down Down ==" << std::endl;
  std::cout << "mean = " << Minuit_ResDD[0] << " +/- " << Minuit_ResDD[1] << std::endl;
  std::cout << "Core Sigma = " << Minuit_ResDD[2] << " +/- " << Minuit_ResDD[3] << std::endl;
  std::cout << "Mid  Sigma = " << Minuit_ResDD[4] << " +/- " << Minuit_ResDD[5] << std::endl;
  std::cout << "Tail Sigma = " << Minuit_ResDD[6] << " +/- " << Minuit_ResDD[7] << std::endl;
  std::cout << "Core Fraction = " << Minuit_ResDD[8] << " +/- " << Minuit_ResDD[9] << std::endl;
  std::cout << "Mid  Fraction = " << Minuit_ResDD[10] << " +/- " << Minuit_ResDD[11] << std::endl;
  std::cout << std::endl;
  std::cout << "Fraction = " << Minuit_ResDD[12] << " +/- " << Minuit_ResDD[13] << std::endl;
  std::cout << "Tau Long = " << Minuit_ResDD[14] << " +/- " << Minuit_ResDD[15] << std::endl;
 
}


/////////////////////////////////
// ***** Helper Function ***** //
/////////////////////////////////
void FitResolution(RooDataSet *data, RooRealVar *time, double *Minuit, TString saveString){
  
  // ********** Initialise ********** //
  //////////////////////////////////////	
  
  string convSave (saveString);
  
  TString what = "";
  if(convSave.find("SigBd")!=string::npos) what = "SigBd";
  else if(convSave.find("SigBs")!=string::npos) what = "SigBs";
  else if(convSave.find("Bkg")!=string::npos) what = "Bkg";
  else if(convSave.find("MassSidebands")!=string::npos) what = "MassSidebands";
  Int_t ttype = 0;
  if(convSave.find("LL")!=string::npos) ttype = 3;
  else if(convSave.find("DD")!=string::npos) ttype = 5;
  bool pullOnly = false;
  if(convSave.find("PullOnly")!=string::npos) pullOnly = true;
  
  // *** Settings ***
  Int_t plotMax = 20000;
  TString xTitle = "";
  Double_t xMax = 1.;
  Double_t xMin = -1.;
  Int_t nBins = 100;
  if(what=="SigBd" || what=="SigBs")xTitle = "t_{reco} - t_{true} (ps)";
  else{
    xTitle = "Reco B decay time (ps)";
    xMax = 1;
    nBins = 100;
  }

  // *** Resolution ***	
  RooRealVar *resMean = new RooRealVar("resMean","Resolution - Mean",-0.005,-0.01,0.01,"ps");
	RooRealVar *coreSigma = new RooRealVar("coreSigma","Resolution - Core Width",0.03,0.,0.05,"ps");
  RooRealVar *midSigma = new RooRealVar("midSigma","Resolution - Middle Width",0.06,0.025,0.08,"ps");
	RooRealVar *tailSigma = new RooRealVar("tailSigma","Resolution - Tail Width",0.21,0.07,1.,"ps");
  RooRealVar *Corefrac = new RooRealVar("Corefrac","Fraction of Core", 0.60,0.,1.);
  RooRealVar *Midfrac = new RooRealVar("Midfrac","Fraction of Mid", 0.30,0.,1.);


  // ********** Time PDFs ********** //
  /////////////////////////////////////

  // *** Resolution ***	
  RooGaussian *core = new RooGaussian("core","Core Gaussian",*time,*resMean,*coreSigma);
  RooGaussian *mid = new RooGaussian("mid","Middle Gaussian",*time,*resMean,*midSigma);
  RooGaussian *tail = new RooGaussian("tail","Tail Gaussian",*time,*resMean,*tailSigma);
  RooAddPdf *Res_Model = new RooAddPdf("Res_Model","Resolution Model",RooArgList(*core,*mid,*tail),RooArgList(*Corefrac,*Midfrac));
  
  // ***** Fit ***** //
  /////////////////////

  RooRealVar* temp = 0;
  
  std::cout << std::endl;
  std::cout << "== Fit ==" << std::endl;
  bool weighted = false;
  if(what=="Bkg") weighted = true;
  // Set Values
  if(ttype==3){
    coreSigma->setVal(0.0313289);
    midSigma->setVal(0.0612225);
    tailSigma->setVal(0.37931);
    Corefrac->setVal(0.702295);
    Midfrac->setVal(0.28924);
  }
  else if(ttype==5){
    coreSigma->setVal(0.0313592);
    midSigma->setVal(0.0634281);
    tailSigma->setVal(0.210496);
    Corefrac->setVal(0.633399);
    Midfrac->setVal(0.354031);
  }
  // Set constant
  if(pullOnly){
    coreSigma->setConstant();
    midSigma->setConstant();
    tailSigma->setConstant();
    Corefrac->setConstant();
    Midfrac->setConstant();
  }
  // Set Range
  if(what=="SigBd" && ttype==5) time->setRange("FitRange",xMin,0.3);
  else if((what=="SigBd" && ttype==3) || what=="SigBs") time->setRange("FitRange",xMin,xMax);
  else if(what=="Bkg" || what=="MassSidebands"){
    time->setRange("FitRange",xMin,xMax);
    resMean->setVal(0.);
    resMean->setConstant();
  }
  
  // Fit
  RooFitResult* fitresult = 0;
  if(what=="SigBd" || what=="SigBs") fitresult = (RooFitResult *)Res_Model->fitTo(*data,Range("FitRange"),SumW2Error(weighted),Save(),NumCPU(2));
  //if(fitresult->covQual()==3 || fitresult->covQual()<0){
  if(fitresult && fitresult->covQual()!=0){
    fitresult->Print();
    std::cout << "Cov Quality " << fitresult->covQual() << std::endl;

    const RooArgList& fitted_par = fitresult->floatParsFinal();
	
		temp = (RooRealVar*)fitted_par.find("resMean");
    if(temp){
      Minuit[0] = temp->getVal();
      Minuit[1] = temp->getError();
      delete temp;
    }
		temp = (RooRealVar*)fitted_par.find("coreSigma");
    if(temp){
      Minuit[2] = temp->getVal();
      Minuit[3] = temp->getError();
      delete temp;
    }
		temp = (RooRealVar*)fitted_par.find("midSigma");
    if(temp){
      Minuit[4] = temp->getVal();
      Minuit[5] = temp->getError();
      delete temp;
    }
		temp = (RooRealVar*)fitted_par.find("tailSigma");
    if(temp){
      Minuit[6] = temp->getVal();
      Minuit[7] = temp->getError();
      delete temp;
    }
		temp = (RooRealVar*)fitted_par.find("Corefrac");
    if(temp){
      Minuit[8] = temp->getVal();
      Minuit[9] = temp->getError();
      delete temp;
    }
		temp = (RooRealVar*)fitted_par.find("Midfrac");
    if(temp){
      Minuit[10] = temp->getVal();
      Minuit[11] = temp->getError();
      delete temp;
    }
  }

	// ***** Plot ***** //
  //////////////////////
  
  std::cout << std::endl;
  std::cout << "== Plot ==" << std::endl;
	
	// *** Frame ***
  RooPlot* BFrame = time->frame(Range(xMin,xMax),Bins(nBins));

	// Titles
	BFrame->SetYTitle("Events/(0.02 ps)");
	BFrame->SetXTitle(xTitle);

	// Cosmetics
	BFrame->SetTitleOffset(1.2,"y");
	BFrame->SetTitleSize(0.07,"x");
	BFrame->SetTitleSize(0.07,"y");
	BFrame->SetTitleFont(132,"y");
	BFrame->SetTitleFont(132,"x");
	BFrame->SetLabelSize(0.05,"y");
	BFrame->SetLabelSize(0.05,"x");
	BFrame->SetLabelFont(132,"x");
	BFrame->SetLabelFont(132,"y");

  data->plotOn(BFrame,MarkerStyle(8),MarkerSize(0.8)); 
  Res_Model->plotOn(BFrame,Components("core"),Range(-3.,3.),LineColor(2),LineWidth(2));
  Res_Model->plotOn(BFrame,Components("mid"),Range(-3.,3.),LineColor(3),LineWidth(2));
  Res_Model->plotOn(BFrame,Components("tail"),Range(-3.,3.),LineColor(1),LineWidth(2));
  Res_Model->plotOn(BFrame,Range(-3.,3.),LineColor(4),LineWidth(2));
    
  BFrame->SetMinimum(0.9);
  BFrame->SetMaximum(plotMax);	

  PullPlot(saveString,BFrame,1);
}

/////////////////////////////////
// ***** Helper Function ***** //
/////////////////////////////////
void FitWrongPV(RooDataSet *data, RooRealVar *time, double *Minuit, TString saveString){
  
  // ********** Initialise ********** //
  //////////////////////////////////////	
  
  string convSave (saveString);
  
  TString what = "";
  if(convSave.find("SigBd")!=string::npos) what = "SigBd";
  else if(convSave.find("SigBs")!=string::npos) what = "SigBs";
  Int_t ttype = 0;
  if(convSave.find("LL")!=string::npos) ttype = 3;
  else if(convSave.find("DD")!=string::npos) ttype = 5;
  bool pullOnly = false;
  if(convSave.find("PullOnly")!=string::npos) pullOnly = true;
  
  // *** Settings ***
  Int_t plotMax = 20000;
  TString xTitle = "";
  Double_t xMax = 5.;
  Double_t xMin = -5.;
  Int_t nBins = 100;
  xTitle = "t_{reco} - t_{true} (ps)";

  // *** Resolution ***	
  RooRealVar *resMean = new RooRealVar("resMean","Resolution - Mean",0.0,-0.1,0.1,"ps");
  RooRealVar *resMean_II = new RooRealVar("resMean_II","Resolution - Mean",0.7,0.,1.,"ps");
	RooRealVar *coreSigma = new RooRealVar("coreSigma","Resolution - Core Width",0.6,0.,1.,"ps");
	RooRealVar *tailSigma = new RooRealVar("tailSigma","Resolution - Tail Width",2.5,1.,5.,"ps");
  RooRealVar *Corefrac = new RooRealVar("Corefrac","Fraction of Core", 0.60,0.,1.);

  // ********** Time PDFs ********** //
  /////////////////////////////////////

  // *** Resolution ***	
  RooGaussian *core = new RooGaussian("core","Core Gaussian",*time,*resMean,*coreSigma);
  RooGaussian *tail = new RooGaussian("tail","Tail Gaussian",*time,*resMean_II,*tailSigma);
  RooAddPdf *Res_Model = new RooAddPdf("Res_Model","Resolution Model",RooArgList(*core,*tail),RooArgList(*Corefrac));
  
  // ***** Fit ***** //
  /////////////////////

  RooRealVar* temp = 0;
  
  std::cout << std::endl;
  std::cout << "== Fit ==" << std::endl;
  // Set Values
  if(ttype==3){
    resMean->setVal(0.0761565);
    resMean_II->setVal(0.766588);
    coreSigma->setVal(0.678194);
    tailSigma->setVal(2.42);
    Corefrac->setVal(0.614803);
  }
  else if(ttype==5){
    resMean->setVal(0.056283);
    resMean_II->setVal(0.873669);
    coreSigma->setVal(0.497835);
    tailSigma->setVal(1.94824);
    Corefrac->setVal(0.66406);
  }
  // Set constant
  if(pullOnly){
    resMean->setConstant();
    resMean_II->setConstant();
    coreSigma->setConstant();
    tailSigma->setConstant();
    Corefrac->setConstant();
  }
  // Set Range
  time->setRange("FitRange",xMin,xMax);
  
  // Fit
  RooFitResult* fitresult = (RooFitResult *)Res_Model->fitTo(*data,Range("FitRange"),Save(),NumCPU(2));
  fitresult->Print();
  if(fitresult->covQual()==3 || fitresult->covQual()<0){

    const RooArgList& fitted_par = fitresult->floatParsFinal();
	
		temp = (RooRealVar*)fitted_par.find("resMean");
    if(temp){
      Minuit[0] = temp->getVal();
      Minuit[1] = temp->getError();
      delete temp;
    }
		temp = (RooRealVar*)fitted_par.find("resMean_II");
    if(temp){
      Minuit[2] = temp->getVal();
      Minuit[3] = temp->getError();
      delete temp;
    }
		temp = (RooRealVar*)fitted_par.find("coreSigma");
    if(temp){
      Minuit[4] = temp->getVal();
      Minuit[5] = temp->getError();
      delete temp;
    }
		temp = (RooRealVar*)fitted_par.find("tailSigma");
    if(temp){
      Minuit[6] = temp->getVal();
      Minuit[7] = temp->getError();
      delete temp;
    }
    temp = (RooRealVar*)fitted_par.find("Corefrac");
    if(temp){
      Minuit[8] = temp->getVal();
      Minuit[9] = temp->getError();
      delete temp;
    }
  }

	// ***** Plot ***** //
  //////////////////////
  
  std::cout << std::endl;
  std::cout << "== Plot ==" << std::endl;
	
	// *** Frame ***
  RooPlot* BFrame = time->frame(Range(xMin,xMax),Bins(nBins));

	// Titles
	BFrame->SetYTitle("Events/(0.1 ps)");
	BFrame->SetXTitle(xTitle);

	// Cosmetics
	BFrame->SetTitleOffset(1.2,"y");
	BFrame->SetTitleSize(0.07,"x");
	BFrame->SetTitleSize(0.07,"y");
	BFrame->SetTitleFont(132,"y");
	BFrame->SetTitleFont(132,"x");
	BFrame->SetLabelSize(0.05,"y");
	BFrame->SetLabelSize(0.05,"x");
	BFrame->SetLabelFont(132,"x");
	BFrame->SetLabelFont(132,"y");

  data->plotOn(BFrame,MarkerStyle(8),MarkerSize(0.8)); 
  Res_Model->plotOn(BFrame,Components("core"),Range(xMin,xMax),LineColor(2),LineWidth(2));
  Res_Model->plotOn(BFrame,Components("tail"),Range(xMin,xMax),LineColor(1),LineWidth(2));
  Res_Model->plotOn(BFrame,Range(xMin,xMax),LineColor(4),LineWidth(2));
    
  BFrame->SetMinimum(0.9);
  BFrame->SetMaximum(plotMax);	

  PullPlot(saveString,BFrame,1);
}

/////////////////////////////////
// ***** Helper Function ***** //
/////////////////////////////////
void FitPrescaled(RooDataSet *data, RooRealVar *time, double *Minuit, TString saveString){
  
  // ********** Initialise ********** //
  //////////////////////////////////////	
  
  string convSave (saveString);
  
  TString what = "";
  if(convSave.find("Bkg")!=string::npos) what = "Bkg";
  else if(convSave.find("MassSidebands")!=string::npos) what = "MassSidebands";
  Int_t ttype = 0;
  if(convSave.find("LL")!=string::npos) ttype = 3;
  else if(convSave.find("DD")!=string::npos) ttype = 5;
  bool pullOnly = false;
  if(convSave.find("PullOnly")!=string::npos) pullOnly = true;
  if(convSave.find("MC")!=string::npos) ttype = -ttype;
  
  // *** Settings ***
  Int_t plotMax = 2000;
  TString xTitle = "Reco B decay time (ps)";
  Double_t xMax = 1.;
  Double_t xMin = -1.;
  Int_t nBins = 100;

  // *** Resolution ***	
  RooRealVar *resMean = new RooRealVar("resMean","Resolution - Mean",0.,-0.01,0.01,"ps");
	RooRealVar *coreSigma = new RooRealVar("coreSigma","Resolution - Core Width",0.03,0.,0.05,"ps");
  RooRealVar *midSigma = new RooRealVar("midSigma","Resolution - Middle Width",0.06,0.025,0.1,"ps");
	RooRealVar *tailSigma = new RooRealVar("tailSigma","Resolution - Tail Width",0.21,0.,1.,"ps");
  RooRealVar *Corefrac = new RooRealVar("Corefrac","Fraction of Core", 0.60,0.,1.);
  RooRealVar *Midfrac = new RooRealVar("Midfrac","Fraction of Mid", 0.30,0.,1.);

  // *** Lifetime ***	
	RooRealVar *tau_long = new RooRealVar("tau_long","Long Lifetime for Bkg",1.525,0.,25.,"ps");	
	//RooRealVar *tau_short = new RooRealVar("tau_short","Short lifetime for Bkg",0.3,0.,1.5,"ps");	
  RooRealVar *frac = new RooRealVar("frac","Fraction of Short",0.5,0.,1.);

  // ********** Time PDFs ********** //
  /////////////////////////////////////

  // *** Resolution ***	
  RooGaussian *corePrompt = new RooGaussian("corePrompt","Core Gaussian",*time,*resMean,*coreSigma);
  RooGaussian *midPrompt = new RooGaussian("midPrompt","Middle Gaussian",*time,*resMean,*midSigma);
  RooGaussian *tailPrompt = new RooGaussian("tailPrompt","Tail Gaussian",*time,*resMean,*tailSigma);
  RooAddPdf *Prompt = new RooAddPdf("Prompt","Resolution Model",RooArgList(*corePrompt,*midPrompt,*tailPrompt),RooArgList(*Corefrac,*Midfrac));
  
  RooGaussModel *core = new RooGaussModel("core","Core Gaussian",*time,*resMean,*coreSigma);
  RooGaussModel *mid = new RooGaussModel("mid","Middle Gaussian",*time,*resMean,*midSigma);
  RooGaussModel *tail = new RooGaussModel("tail","Tail Gaussian",*time,*resMean,*tailSigma);
  RooAddModel *Res_Model = new RooAddModel("Res_Model","Resolution Model",RooArgList(*core,*mid,*tail),RooArgList(*Corefrac,*Midfrac));
  
  // *** RooDecays && Composite ***
  RooDecay *decay_long = 0;
  RooAddPdf *background = 0;
  if(convSave.find("Gauss")!=string::npos){
    decay_long = new RooDecay("decay_long","Long Lifetimes",*time,*tau_long,*tail,RooDecay::SingleSided);
    background = new RooAddPdf("background","Background Model",RooArgList(*tailPrompt,*decay_long),*frac);
  }
  else{
    decay_long = new RooDecay("decay_long","Long Lifetimes",*time,*tau_long,*Res_Model,RooDecay::SingleSided);
    background = new RooAddPdf("background","Background Model",RooArgList(*Prompt,*decay_long),*frac);
  }
  
  //RooDecay *decay_short = new RooDecay("decay_short","Short Lifetimes",*time,*tau_short,*Res_Model,RooDecay::SingleSided);
  
  // ***** Fit ***** //
  /////////////////////

  RooRealVar* temp = 0;
  
  std::cout << std::endl;
  std::cout << "== Fit ==" << std::endl;
  bool weighted = false;
  if(what=="Bkg") weighted = true;
  // Set Values
  if(ttype==-3){
    coreSigma->setVal(0.0313289);
    midSigma->setVal(0.0612225);
    tailSigma->setVal(0.37931);
    Corefrac->setVal(0.702295);
    Midfrac->setVal(0.28924);
  }
  else if(ttype==3){
    coreSigma->setVal(0.0339915);
    midSigma->setVal(0.0648249);
    tailSigma->setVal(0.37931);
    Corefrac->setVal(0.625239);
    Midfrac->setVal(0.362524);
  }
  else if(ttype==-5){
    coreSigma->setVal(0.0313592);
    midSigma->setVal(0.0634281);
    tailSigma->setVal(0.210496);
    Corefrac->setVal(0.633399);
    Midfrac->setVal(0.354031);
  }
  else if(ttype==5){
    coreSigma->setVal(0.0397601);
    midSigma->setVal(0.0720899);
    tailSigma->setVal(0.210496);
    Corefrac->setVal(0.491009);
    Midfrac->setVal(0.43744);
  }  
  // Set constant
  if(pullOnly){
    coreSigma->setConstant();
    midSigma->setConstant();
    tailSigma->setConstant();
    Corefrac->setConstant();
    Midfrac->setConstant();
  }
  else if(convSave.find("Gauss")==string::npos){
    if(ttype<0){
      coreSigma->setConstant();
      midSigma->setConstant();
    }
    tailSigma->setConstant();
  }
  else if(convSave.find("Wide")!=string::npos){
    tailSigma->setVal(0.5);
    tailSigma->setConstant();
    frac->setVal(ttype==3 ? 0.949934 : 0.627694);
    frac->setConstant();
    tau_long->setVal(ttype==3 ? 0.374303 : 1.5149);
    tau_long->setConstant();
  }
  // Set Range
  time->setRange("FitRange",xMin,xMax);

  // Fit
  RooFitResult* fitresult = (RooFitResult *)background->fitTo(*data,Range("FitRange"),SumW2Error(weighted),Save(),NumCPU(2));
  //if(fitresult->covQual()==3 || fitresult->covQual()<0){
  if(fitresult && fitresult->covQual()!=0){
    fitresult->Print();
    std::cout << "Cov Quality " << fitresult->covQual() << std::endl;

    const RooArgList& fitted_par = fitresult->floatParsFinal();
	
		temp = (RooRealVar*)fitted_par.find("resMean");
    if(temp){
      Minuit[0] = temp->getVal();
      Minuit[1] = temp->getError();
      delete temp;
    }
		temp = (RooRealVar*)fitted_par.find("coreSigma");
    if(temp){
      Minuit[2] = temp->getVal();
      Minuit[3] = temp->getError();
      delete temp;
    }
		temp = (RooRealVar*)fitted_par.find("midSigma");
    if(temp){
      Minuit[4] = temp->getVal();
      Minuit[5] = temp->getError();
      delete temp;
    }
		temp = (RooRealVar*)fitted_par.find("tailSigma");
    if(temp){
      Minuit[6] = temp->getVal();
      Minuit[7] = temp->getError();
      delete temp;
    }
		temp = (RooRealVar*)fitted_par.find("Corefrac");
    if(temp){
      Minuit[8] = temp->getVal();
      Minuit[9] = temp->getError();
      delete temp;
    }
		temp = (RooRealVar*)fitted_par.find("Midfrac");
    if(temp){
      Minuit[10] = temp->getVal();
      Minuit[11] = temp->getError();
      delete temp;
    }
		temp = (RooRealVar*)fitted_par.find("frac");
    if(temp){
      Minuit[12] = temp->getVal();
      Minuit[13] = temp->getError();
      delete temp;
    }
		temp = (RooRealVar*)fitted_par.find("tau_long");
    if(temp){
      Minuit[14] = temp->getVal();
      Minuit[15] = temp->getError();
      delete temp;
    }
  }

	// ***** Plot ***** //
  //////////////////////
  
  std::cout << std::endl;
  std::cout << "== Plot ==" << std::endl;
	
	// *** Frame ***
  RooPlot* BFrame = time->frame(Range(xMin,xMax),Bins(nBins));

	// Titles
	BFrame->SetYTitle("Events/(0.02 ps)");
	BFrame->SetXTitle(xTitle);

	// Cosmetics
	BFrame->SetTitleOffset(1.2,"y");
	BFrame->SetTitleSize(0.07,"x");
	BFrame->SetTitleSize(0.07,"y");
	BFrame->SetTitleFont(132,"y");
	BFrame->SetTitleFont(132,"x");
	BFrame->SetLabelSize(0.05,"y");
	BFrame->SetLabelSize(0.05,"x");
	BFrame->SetLabelFont(132,"x");
	BFrame->SetLabelFont(132,"y");

  data->plotOn(BFrame,MarkerStyle(8),MarkerSize(0.8));

  background->plotOn(BFrame,Components("corePrompt"),Range(xMin,xMax),LineColor(2),LineWidth(2));
  background->plotOn(BFrame,Components("midPrompt"),Range(xMin,xMax),LineColor(3),LineWidth(2));
  background->plotOn(BFrame,Components("tailPrompt"),Range(xMin,xMax),LineColor(1),LineWidth(2));
  background->plotOn(BFrame,Range(xMin,xMax),LineColor(4),LineWidth(2));
    
  BFrame->SetMinimum(0.9);
  BFrame->SetMaximum(plotMax);	

  PullPlot(saveString,BFrame,1);
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
  size_t isBd=convSave.find("SigBd");
  size_t isBs=convSave.find("SigBs");
  size_t isLL=convSave.find("LL");
  size_t isDD=convSave.find("DD");
  
  TString track("");
  if(isLL!=string::npos) track = "Long K_{S}^{0}";
  else if(isDD!=string::npos) track = "Downstream K_{S}^{0}";
  
	TPaveText *lhcbTag = 0;
  double offset = 0.;
  if(isBd==string::npos && isBs==string::npos) offset = 0.04;
	if(logy==1){lhcbTag = new TPaveText(0.23,0.70,0.47+offset,0.89,"NDC");}
	//if(logy==1){lhcbTag = new TPaveText(0.65,0.70,0.89,0.89,"NDC");}
	if(logy==0){lhcbTag = new TPaveText(0.65,0.35,0.89,0.47,"NDC");}

  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  if(isBd!=string::npos) lhcbTag->AddText("#splitline{LHCb MC11a}{#splitline{#scale[0.7]{B_{d}^{0}#rightarrow J/#psi K_{S}^{0}}}{#scale[0.7]{"+track+"}}}");
  else if(isBs!=string::npos) lhcbTag->AddText("#splitline{LHCb MC11a}{#splitline{#scale[0.7]{B_{s}^{0}#rightarrow J/#psi K_{S}^{0}}}{#scale[0.7]{"+track+"}}}");
  else lhcbTag->AddText("#splitline{LHCb 2011}{#splitline{#scale[0.7]{Reco 12 - Stripping 17b}}{#scale[0.7]{"+track+"}}}");
  lhcbTag -> Draw("");
		
	
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
