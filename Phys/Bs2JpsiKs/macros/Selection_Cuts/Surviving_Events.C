////////////////////////////////////////////////////////////////////////
// ***** Study the Effect of Selection Cuts on the Data Samples ***** //
////////////////////////////////////////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb
// - Study the effect of applying the different selection cuts on the data sample
// - Fit the mass distributions


/////////////////////////////////////
// ***** Load useful classes ***** //
/////////////////////////////////////

#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooCBShape.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooFit.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooRealVar.h"

#include "TAxis.h"
#include "TBox.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TLegend.h"
#include "TMath.h"
#include "TNtuple.h"
#include "TPaveText.h"

#include "RooExpAndGauss.h"

using namespace RooFit;

///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void SelectionCuts(TString what, TString which, Int_t tracktype = 0){

// ***** Initialize ***** //
////////////////////////////

  // *** Settings ***
  bool doPullPlot = true;
  Double_t clight = 299.792458;
  Double_t m_Kplus = 493.677;
  Double_t m_BdPDG = 5279.58;

  // Using Optimisation VIIb
  Double_t NNcut = 0.60;
  Double_t NNcut_DD = 0.75;
  
  // *** Plot Settings ***
  Double_t Bmass_min = 5180;
  Double_t Bmass_max = 5520;
  Int_t nBins = (Bmass_max-Bmass_min)/5;
  TString scale = "/(5 MeV/c^{2})";
  TString track("");
  if(tracktype==3) track = "Long K_{S}^{0}";
  else if(tracktype==5) track = "Downstream K_{S}^{0}";
  TString nice = "#splitline{LHCb MC11a}{#scale[0.7]{B_{d}^{0} #rightarrow J/#psi K^{*0}}}";
  Double_t plotMax = 10000;
  Double_t labelsize = 0.05;
  Double_t boxStart = 0.65;
  Double_t boxOffset = 0;
  Double_t legOffset = 0;
  Int_t col = 2;
  if(which=="NN" || which=="NNPullOnly") col = 1;
  
  if(what=="SigKstarWM"){
    Bmass_min = 4520;
    nBins = (Bmass_max-Bmass_min)/25;
    scale = "/(25 MeV/c^{2})";
    plotMax = 100000;
    labelsize = 0.03;
    boxStart = 0.25;
    legOffset = 0.04;
  }
  else if(what=="SigBd"){
    plotMax = (tracktype==0 ? 500000 : 100000);
    //nice = "#splitline{LHCb MC11a}{#scale[0.7]{B_{d}^{0} #rightarrow J/#psi K_{S}^{0}}}";
    nice = "#splitline{LHCb MC11a}{#splitline{#scale[0.7]{B_{d}^{0}#rightarrow J/#psi K_{S}^{0}}}{#scale[0.7]{"+track+"}}}";
  }
  else if(what=="SigBs"){
    plotMax = 100000;
    boxStart = 0.25;
    //nice = "#splitline{LHCb MC11a}{#scale[0.7]{B_{s}^{0} #rightarrow J/#psi K_{S}^{0}}}";
    nice = "#splitline{LHCb MC11a}{#splitline{#scale[0.7]{B_{s}^{0}#rightarrow J/#psi K_{S}^{0}}}{#scale[0.7]{"+track+"}}}";
  }
  else if(what=="LHCb2011"){
    plotMax = 100000;
    boxOffset = 0.05;
    //nice = "#splitline{LHCb 2011}{#scale[0.7]{Reco 12 - Stripping 17b}}";
    nice = "#splitline{LHCb 2011}{#splitline{#scale[0.7]{Reco 12 - Stripping 17b}}{#scale[0.7]{"+track+"}}}";
  }  

// ***** Part I: From NTuple to DataSet ***** //
////////////////////////////////////////////////

// This is done to easily handle the selection cuts and allows semi-automatic looping over these cuts

  std::cout << " " << std::endl;
  std::cout << "== Part I: From NTuple to DataSet ==" << std::endl;
  std::cout << "====================================" << std::endl;

  // ***** Load NTuples ***** //
  //////////////////////////////
  
  TFile* netFile = TFile::Open("B2JpsiKs-Eval-2-random-"+what+".root");
  TTree* neural_net = (TTree*)netFile->Get("NetTree");

  TChain* chain = new TChain("chain");
  chain->Add("B2JpsiKs-Slim-"+what+".root/Slim_B2JpsiKs_Tuple");
  chain->AddFriend(neural_net);
  
  Long64_t nEntries_NTuple = chain->GetEntries();
  //nEntries_NTuple = 10000;  
  std::cout << "Number of entries from DaVinci: " << nEntries_NTuple << std::endl;    


  // ***** Define DataSet Observables ***** //
  ////////////////////////////////////////////

  // *** Define Observables & Selection Variables ***

  // Observable
  Float_t B_FullFit_M[10];
  Int_t piminus_TRACK_Type = -999;
  // Observables for Common Selection Cuts
  Float_t B_FullFit_ctau[10];
	Float_t B_FullFit_status[10];
	Float_t B_FullFit_chi2[10];
  Float_t B_FullFit_MERR[10];
	Float_t B_FullFit_PV_Z[10];
  // Observables for Decay Specific Cuts
  Double_t Psi_PE = -999;
  Double_t piplus_PE = -999;
  Double_t piminus_PE = -999;
  Double_t Psi_PX = -999;
  Double_t piplus_PX = -999;
  Double_t piminus_PX = -999;
  Double_t Psi_PY = -999;
  Double_t piplus_PY = -999;
  Double_t piminus_PY = -999;
  Double_t Psi_PZ = -999;
  Double_t piplus_PZ = -999;
  Double_t piminus_PZ = -999;
	Double_t KS0_M_with_pplus_piplus = -999;
	Double_t KS0_M_with_piplus_pplus = -999;
	Float_t B_FullFit_KS0_ctau[10];
  Float_t B_FullFit_KS0_ctauErr[10];
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
    B_FullFit_status[i] = -999;
    B_FullFit_chi2[i] = -999;
    B_FullFit_MERR[i] = -999;
    B_FullFit_PV_Z[i] = -999;
    B_FullFit_KS0_ctau[i] = -999;
    B_FullFit_KS0_ctauErr[i] = -999;
    netOutput[i] = -999;
  }
  

  // *** Set Branch Addresses ***
  // Observable
  chain->SetBranchAddress("B_FullFit_M", &B_FullFit_M);
  chain->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type);
  // Observables for Common Selection Cuts
  chain->SetBranchAddress("B_FullFit_ctau", &B_FullFit_ctau);
  chain->SetBranchAddress("B_FullFit_status", &B_FullFit_status);
  chain->SetBranchAddress("B_FullFit_chi2", &B_FullFit_chi2);
  chain->SetBranchAddress("B_FullFit_MERR", &B_FullFit_MERR);
  chain->SetBranchAddress("B_FullFit_PV_Z", &B_FullFit_PV_Z);
  // Observables for Decay Specific Cuts
  chain->SetBranchAddress("Psi_PE", &Psi_PE);
  chain->SetBranchAddress("piplus_PE", &piplus_PE);
  chain->SetBranchAddress("piminus_PE", &piminus_PE);
  chain->SetBranchAddress("Psi_PX", &Psi_PX);
  chain->SetBranchAddress("piplus_PX", &piplus_PX);
  chain->SetBranchAddress("piminus_PX", &piminus_PX);
  chain->SetBranchAddress("Psi_PY", &Psi_PY);
  chain->SetBranchAddress("piplus_PY", &piplus_PY);
  chain->SetBranchAddress("piminus_PY", &piminus_PY);
  chain->SetBranchAddress("Psi_PZ", &Psi_PZ);
  chain->SetBranchAddress("piplus_PZ", &piplus_PZ);
  chain->SetBranchAddress("piminus_PZ", &piminus_PZ);
  chain->SetBranchAddress("KS0_M_with_pplus_piplus", &KS0_M_with_pplus_piplus);
  chain->SetBranchAddress("KS0_M_with_piplus_pplus", &KS0_M_with_piplus_pplus);
  chain->SetBranchAddress("B_FullFit_KS0_ctau", &B_FullFit_KS0_ctau);
  chain->SetBranchAddress("B_FullFit_KS0_ctauErr", &B_FullFit_KS0_ctauErr);
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
  RooRealVar *Bmass = new RooRealVar("Bmass","mass",Bmass_min,Bmass_max,"MeV/c^{2}");

  // *** DataSet ***
  RooArgSet *Obs = new RooArgSet(*Bmass);
  RooDataSet *data_All = new RooDataSet("data_All","Unbinned dataset",*Obs);
  RooDataSet *data_Sel = new RooDataSet("data_Sel","Unbinned dataset",*Obs);
  RooDataSet *data_Veto = new RooDataSet("data_Veto","Unbinned dataset",*Obs);
  RooDataSet *data_Trig = new RooDataSet("data_Trig","Unbinned dataset",*Obs);
  RooDataSet *data_NN = new RooDataSet("data_NN","Unbinned dataset",*Obs);


  // ***** Loop over Entries: Apply Selection Cuts ***** //
  /////////////////////////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Loop 1: Selection Cuts ==" << std::endl;
  std::cout << "============================" << std::endl;

  Int_t Long_All = 0;
  Int_t Long_Sel = 0;
  Int_t Long_Veto = 0;
  Int_t Long_Trig = 0;
  Int_t Long_NN = 0;
  
  bool TruthMatch = false;
  bool SelCuts = false;
  bool Trigger = false;
  bool KstarVeto = false;
  Double_t Kstar_minMass = 0;
  Double_t Kstar_plusMass = 0;

  for(Long64_t i=0; i<nEntries_NTuple; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_NTuple << " (" << 100*i/nEntries_NTuple << "%)" << std::endl;

    // Truth Match
    if((what=="SigKstar" || what=="SigKstarWM" ) && TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==313 && B_BKGCAT==30) TruthMatch = true;
    else if((what=="SigBd") && TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && (B_BKGCAT==0 || B_BKGCAT==10)) TruthMatch = true;
    else if((what=="SigBs") && TMath::Abs(B_TRUEID)==531 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && B_BKGCAT==20) TruthMatch = true;
    else if(what=="LHCb2011") TruthMatch = true;
    else TruthMatch = false;
    
    if(TruthMatch && (piminus_TRACK_Type==tracktype || tracktype==0)){
      for(Int_t pv = 0; pv < nPV2 ; pv++){
        if(B_FullFit_M[pv]>Bmass_min && B_FullFit_M[pv]<Bmass_max){
          Bmass->setVal(B_FullFit_M[pv]);
        
          // All Events
          data_All->add(*Obs);
          if(piminus_TRACK_Type==3) Long_All++;
        
          // Selection Cuts
          SelCuts = (B_FullFit_status[pv]==0 && B_FullFit_chi2[pv]<72 && B_FullFit_MERR[pv]<30 &&
            B_FullFit_ctau[pv]/clight>0.0002 && TMath::Abs(B_FullFit_PV_Z[pv])<250 &&
            TMath::Abs(KS0_M_with_pplus_piplus-1116)>2*piminus_TRACK_Type &&
            TMath::Abs(KS0_M_with_piplus_pplus-1116)>2*piminus_TRACK_Type &&
            B_FullFit_KS0_ctau[pv]/B_FullFit_KS0_ctauErr[pv]>5
            );
        
          // Kstar Veto
          Kstar_minMass = TMath::Sqrt(pow(Psi_PE + piplus_PE
            + TMath::Sqrt(pow(m_Kplus,2) + pow(piminus_PX,2) + pow(piminus_PY,2) + pow(piminus_PZ,2)),2)
            - pow(Psi_PX+piplus_PX+piminus_PX,2) - pow(Psi_PY+piplus_PY+piminus_PY,2) - pow(Psi_PZ+piplus_PZ+piminus_PZ,2));
          Kstar_plusMass = TMath::Sqrt(pow(Psi_PE + piminus_PE
            + TMath::Sqrt(pow(m_Kplus,2) + pow(piplus_PX,2) + pow(piplus_PY,2) + pow(piplus_PZ,2)),2)
            - pow(Psi_PX+piplus_PX+piminus_PX,2) - pow(Psi_PY+piplus_PY+piminus_PY,2) - pow(Psi_PZ+piplus_PZ+piminus_PZ,2));
        
          KstarVeto = (piminus_TRACK_Type==5 || (piminus_TRACK_Type==3 && 
                TMath::Abs(Kstar_minMass-m_BdPDG)>20 && TMath::Abs(Kstar_plusMass-m_BdPDG)>20));
        
          // Trigger
          Trigger = (PsiHlt1TrackMuonDecision_TOS || PsiHlt1DiMuonHighMassDecision_TOS || PsiHlt1TrackAllL0Decision_TOS) &&
             (PsiHlt2DiMuonDetachedJPsiDecision_TOS || PsiHlt2DiMuonJPsiHighPTDecision_TOS || PsiHlt2DiMuonJPsiDecision_TOS ||
              PsiHlt2TopoMu2BodyBBDTDecision_TOS);
          
          // Continue with the datasets
          if(SelCuts){
            if(what=="SigKstarWM"){
              data_Veto->add(*Obs);
              if(piminus_TRACK_Type==3) Long_Veto++;
            }
              
            if(KstarVeto){
              data_Sel->add(*Obs);
              if(piminus_TRACK_Type==3) Long_Sel++;
              
              // Trigger
              if(KstarVeto && Trigger){
                data_Trig->add(*Obs);
                if(piminus_TRACK_Type==3) Long_Trig++;
            
                // Neural Net Cut
                if((piminus_TRACK_Type==3 && netOutput[pv]>NNcut) || (piminus_TRACK_Type==5 && netOutput[pv]>NNcut_DD)){
                  data_NN->add(*Obs);
                  if(piminus_TRACK_Type==3) Long_NN++;
                }// Neural Net
              }// Trigger
            }// SelCuts + Veto
          }// SelCuts
        }// mass in range
      }// pv loop
    }// Bd2JpsiKstar
  }

  // Free Memory
  delete chain;


// ***** Part II: Mass Fit ***** //
///////////////////////////////////  

  std::cout << std::endl;
  std::cout << "== Part II: Mass Fit ==" << std::endl;
  std::cout << "=======================" << std::endl;
  
  // ***** Mass Model ***** //
  ////////////////////////////

  // *** Define Parameters ***
  Double_t apar_I_Val = (tracktype==3 ? 1.3124 : (tracktype==5 ? 2.3394 : 2.3045));
  Double_t apar_II_Val = (tracktype==3 ? -1.4314 : (tracktype==5 ? -2.2482 : -2.2074));
  Double_t fracB_Val = (tracktype==3 ? 0.47458 : (tracktype==5 ? 0.64630 : 0.65254));
  Double_t npar_I_Val = (tracktype==3 ? 4.0188 : (tracktype==5 ? 1.7084 : 1.7497));
  Double_t npar_II_Val = (tracktype==3 ? 124.48 : (tracktype==5 ? 6.6748 : 7.4342));
  Double_t sigmaB_I_Val = (tracktype==3 ? 5.1423 : (tracktype==5 ? 6.2735 : 5.9641));
  Double_t sigmaB_II_Val = (tracktype==3 ? 6.8683 : (tracktype==5 ? 10.884 : 10.525));
  
  if(which=="NN"){
    apar_I_Val = (tracktype==3 ? 1.2128 : (tracktype==5 ? 2.4783 : 2.3869));
    apar_II_Val = (tracktype==3 ? -1.5172 : (tracktype==5 ? -2.5354 : -2.4101));
    fracB_Val = (tracktype==3 ? 0.41314 : (tracktype==5 ? 0.67070 : 0.67072));
    npar_I_Val = (tracktype==3 ? 5.1266 : (tracktype==5 ? 1.8101 : 1.9366));
    npar_II_Val = (tracktype==3 ? 145.50 : (tracktype==5 ? 7.4710 : 8.8797));
    sigmaB_I_Val = (tracktype==3 ? 4.9750 : (tracktype==5 ? 6.1474 : 5.8081));
    sigmaB_II_Val = (tracktype==3 ? 6.5592 : (tracktype==5 ? 10.326 : 9.9057));
  }

  // Signal
  RooRealVar *meanBd = new RooRealVar("meanBd","Position of Bd mass peak",5279.,Bmass_min,Bmass_max);
  RooRealVar *meanBs = new RooRealVar("meanBs","Position of Bs mass peak",5366.,Bmass_min,Bmass_max);
  RooRealVar *sigmaB_I = new RooRealVar("sigmaB_I","Width of Bd mass peak",sigmaB_I_Val,1.0,25.0);
  RooRealVar *sigmaB_II = new RooRealVar("sigmaB_II","Width of Bd mass peak",sigmaB_II_Val,1.0,25.0);
  RooRealVar *fracB = new RooRealVar("fracB","Fraction of model I",fracB_Val,0.,1.);
  RooRealVar *apar_I = new RooRealVar("apar_I","A parameter of Crystal Ball I",apar_I_Val,0.,5.);
  RooRealVar *apar_II = new RooRealVar("apar_II","A parameter of Crystal Ball II",apar_II_Val,-5.,0.);
  RooRealVar *npar_I = new RooRealVar("npar_I","N parameter of Crystal Ball I",npar_I_Val,0.,25.);
  RooRealVar *npar_II = new RooRealVar("npar_II","N parameter of Crystal Ball II",npar_II_Val,0.,250.);
  
  // Kstar
  RooRealVar *meanKstar = new RooRealVar("meanKstar","Mean of Gaussian",5180.,5100.,5300.);
  RooRealVar *sigmaKstar = new RooRealVar("sigmaKstar","Width of Gaussian",25.,0.,100.);
  //RooRealVar *trans = new RooRealVar("trans","Transition to Exp",5180.,5100.,5300.);
  RooRealVar *shift = new RooRealVar("shift","Transition to Exp",4.,0.,25.);
  RooFormulaVar *trans = new RooFormulaVar("trans","Transition to Exp","@0-@1",RooArgSet(*meanKstar,*shift));
  
  // Background
  RooRealVar *lambda = new RooRealVar("lambda","decay constant",-0.005,-0.1,0.);
  Double_t nEvents = data_NN->numEntries();
  RooRealVar *nBkg = new RooRealVar("nBkg","fraction",0.05*nEvents,0.,nEvents);
  RooRealVar *nBd = new RooRealVar("nBd","fraction",0.90*nEvents,0.,nEvents);
  RooRealVar *nBs = new RooRealVar("nBs","fraction",0.01*nEvents,0.,nEvents);


  // *** PDF ***
  // Bd Signal
  RooCBShape *CBall_Bd_I = new RooCBShape("CBall_Bd_I","Crystal Ball model",*Bmass,*meanBd,*sigmaB_I,*apar_I,*npar_I);
  RooCBShape *CBall_Bd_II = new RooCBShape("CBall_Bd_II","Reflected Crystal Ball model",*Bmass,*meanBd,*sigmaB_II,*apar_II,*npar_II);
  RooAddPdf *double_CBall_Bd = new RooAddPdf("double_CBall_Bd","Double Crystal Ball",RooArgList(*CBall_Bd_I,*CBall_Bd_II),*fracB);
    
  // Bs Signal
  RooCBShape *CBall_Bs_I = new RooCBShape("CBall_Bs_I","Crystal Ball model",*Bmass,*meanBs,*sigmaB_I,*apar_I,*npar_I);
  RooCBShape *CBall_Bs_II = new RooCBShape("CBall_Bs_II","Reflected Crystal Ball model",*Bmass,*meanBs,*sigmaB_II,*apar_II,*npar_II);
  RooAddPdf *double_CBall_Bs = new RooAddPdf("double_CBall_Bs","Double Crystal Ball",RooArgList(*CBall_Bs_I,*CBall_Bs_II),*fracB);
  
  // Kstar
  RooExpAndGauss *background = new RooExpAndGauss("background","Background model",*Bmass,*meanKstar,*sigmaKstar,*trans);
  
  // Background
  RooExponential *exponential = new RooExponential("exponential","Exponential for background",*Bmass,*lambda);

  // Signal + Background
  RooAddPdf *massPDF = new RooAddPdf("massPDF","PDF for Sig + Bkg",RooArgList(*exponential,*double_CBall_Bd,*double_CBall_Bs),RooArgList(*nBkg,*nBd,*nBs));


  // *** Fit ***
  RooFitResult *fitresult = 0;
  if(what=="SigBd"){
    if(which=="Loose") fitresult = (RooFitResult *)double_CBall_Bd->fitTo(*data_Trig,Save(),NumCPU(2));
    else if(which=="NN") fitresult = (RooFitResult *)double_CBall_Bd->fitTo(*data_NN,Save(),NumCPU(2));
  }
  else if(what=="SigBs"){
    if(which=="Loose") fitresult = (RooFitResult *)double_CBall_Bs->fitTo(*data_Trig,Save(),NumCPU(2));
    else if(which=="NN") fitresult = (RooFitResult *)double_CBall_Bs->fitTo(*data_NN,Save(),NumCPU(2));
    else{
      apar_I->setConstant();
      apar_II->setConstant();
      npar_I->setConstant();
      npar_II->setConstant();
      sigmaB_I->setConstant();
      sigmaB_II->setConstant();
      fracB->setConstant();
      fitresult = (RooFitResult *)double_CBall_Bs->fitTo(*data_Trig,Save(),NumCPU(2));
    }
  }
  else if(what=="SigKstarWM") fitresult = (RooFitResult *)background->fitTo(*data_Veto,Save(),NumCPU(2));
  else if(what=="LHCb2011"){
    apar_I->setConstant();
    apar_II->setConstant();
    npar_I->setConstant();
    npar_II->setConstant();
    if(which=="Loose") fitresult = (RooFitResult *)massPDF->fitTo(*data_Trig,Save(),NumCPU(2));
    if(which=="NN") fitresult = (RooFitResult *)massPDF->fitTo(*data_NN,Save(),NumCPU(2));
  }
  

// ***** Part III: Plot ***** //
////////////////////////////////

  std::cout << std::endl;
  std::cout << "== Part III: Plot ==" << std::endl;
  std::cout << "====================" << std::endl;

  // *** Frame ***
  RooPlot* BmassFrame = Bmass->frame(Bins(nBins));

  // Titles
  BmassFrame->SetYTitle("Events"+scale);
  BmassFrame->SetXTitle("m_{J/#psi K_{S}^{0}} #scale[0.8]{(MeV/c^{2})}");

  // Cosmetics
  BmassFrame->SetTitleOffset(0.9,"x");
  BmassFrame->SetTitleOffset(1.2,"y");
  BmassFrame->SetTitleSize(0.07,"x");
  BmassFrame->SetTitleSize(0.07,"y");
  BmassFrame->SetTitleFont(132,"y");
  BmassFrame->SetTitleFont(132,"x");
  BmassFrame->SetLabelOffset(0.015,"y");
  BmassFrame->SetLabelSize(0.05,"y");
  BmassFrame->SetLabelSize(labelsize,"x");
  BmassFrame->SetLabelFont(132,"x");
  BmassFrame->SetLabelFont(132,"y");

  // The order is important for the pull plot
  data_All ->plotOn(BmassFrame,MarkerStyle(23),MarkerSize(0.8),MarkerColor(4),LineColor(4));
  data_Sel ->plotOn(BmassFrame,MarkerStyle(22),MarkerSize(0.8),MarkerColor(3),LineColor(3));
  if(which=="Loose" || which=="LoosePullOnly"){
    data_NN  ->plotOn(BmassFrame,MarkerStyle(29),MarkerSize(1  ),MarkerColor(1),LineColor(1));
    data_Trig->plotOn(BmassFrame,MarkerStyle(21),MarkerSize(0.8),MarkerColor(2),LineColor(2));
  }
  else if(which=="NN" || which=="NNPullOnly"){
    data_Trig->plotOn(BmassFrame,MarkerStyle(21),MarkerSize(0.8),MarkerColor(2),LineColor(2));
    data_NN  ->plotOn(BmassFrame,MarkerStyle(29),MarkerSize(1  ),MarkerColor(1),LineColor(1));
  }
  if(what=="SigBd") double_CBall_Bd->plotOn(BmassFrame,Range(Bmass_min,Bmass_max),LineColor(col),LineWidth(2));
  else if(what=="SigBs") double_CBall_Bs->plotOn(BmassFrame,Range(Bmass_min,Bmass_max),LineColor(col),LineWidth(2));
  else if(what=="LHCb2011"){
    massPDF->plotOn(BmassFrame,Components("double_CBall_Bd"),Range(Bmass_min,Bmass_max),LineColor(3),LineWidth(2));
    massPDF->plotOn(BmassFrame,Components("double_CBall_Bs"),Range(Bmass_min,Bmass_max),LineColor(4),LineWidth(2));
    massPDF->plotOn(BmassFrame,Components("exponential"),Range(Bmass_min,Bmass_max),LineColor((2*col)%3),LineWidth(2));
    massPDF->plotOn(BmassFrame,Range(Bmass_min,Bmass_max),LineColor(col),LineWidth(2));
  }
  if(what=="SigKstarWM"){
    data_Veto->plotOn(BmassFrame,MarkerStyle(20),MarkerSize(0.8),MarkerColor(kOrange+1),LineColor(kOrange+1));
    background->plotOn(BmassFrame,Range(Bmass_min,Bmass_max),LineColor(kOrange+1),LineWidth(2));
  }
  
  BmassFrame->SetMinimum(0.9);
  BmassFrame->SetMaximum(plotMax);
  
  // *** Canvas ***
  TCanvas *doek = new TCanvas("doek","Observable",900,800);
  Float_t ratio = 0.30; // Percentage of the plot for Pull distributions
  if(!doPullPlot){
    doek->SetLeftMargin(0.2);
    doek->SetBottomMargin(0.15);
    gPad->SetLogy(1);
    BmassFrame->Draw("");
  }
  else{
    doek->cd(1);
    // *** Place the first frame ***
    // To keep the correct scale of the labels, use the Margins instead of Pad coordinates
    TPad* xPad = new TPad("xPad", "Pad for Observable Plot", 0., 0, 1., 1.);
    xPad->SetLeftMargin(0.2);
    xPad->SetBottomMargin(ratio);
    // Draw Pad
    xPad->Draw();
    xPad->cd();
    xPad->SetLogy(1);
    // Suppress X-axis decoration
    BmassFrame->SetLabelSize(0,"x");
    BmassFrame->SetTitleSize(0,"x");
    // Fill Pad
  }
  BmassFrame->Draw("");
    
  if(what=="SigKstarWM"){
    // *** Exclusion Box ***
    TBox* box = new TBox(Bmass_min,0,5180,plotMax-2000);
    box->SetFillColor(18);
    box->Draw();
    BmassFrame->Draw("same");
    
    Float_t black_pointx[2];
    black_pointx[0] = 5180;
    black_pointx[1] = black_pointx[0];
    Float_t black_pointy[4];
    black_pointy[0] = 0;
    black_pointy[1] = plotMax;
    TGraph *black_contour = new TGraph(2,black_pointx,black_pointy);
    black_contour->SetLineColor(1);
    black_contour->SetLineWidth(2);
    black_contour->Draw("");
  }
  
  if(doPullPlot){
    // go back to the Bottom layer
    doek->cd();
    
    // ***** Pull Plot ***** //
    ///////////////////////////
    RooPlot* pullframe = (RooPlot *)BmassFrame->emptyClone("pullframe");
    
    // Titles
    pullframe->SetYTitle("Pull");
    pullframe->SetXTitle(BmassFrame->GetXaxis()->GetTitle());

    // Cosmetics
    pullframe->SetTitleOffset(0.9,"x");
    pullframe->SetTitleSize(0.07,"x");
    pullframe->SetTitleFont(132,"x");
    pullframe->SetLabelSize(labelsize,"x");
    pullframe->SetLabelFont(132,"x");
    pullframe->SetTitleSize(0,"y");// No title here
    pullframe->SetLabelSize(0.03,"y");
    pullframe->SetLabelFont(132,"y");
    
    // Fill - And specify plot option: Bar-chart
    pullframe->addObject((TObject*)BmassFrame->pullHist(),"B");
    // Extract the histogram in orde to apply plot options
    TGraph* pullgraph = (TGraph*) pullframe->getObject(0);
    //pullgraph->SetLineWidth(2);
    pullgraph->SetFillColor((what=="SigKstarWM" ? kOrange+1 : col));
    pullgraph->SetFillStyle(1001);
    
    // General Settings
    pullframe->SetMinimum(-5);
    pullframe->SetMaximum(5);
    pullframe->GetYaxis()->SetNdivisions(503,kTRUE);
  
    // *** Place the second frame ***
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
    pullframe->Draw("");
  }
  
  // *** Further Decoration *** //
  ////////////////////////////////
  
  // *** LHCb Tag ***
  TPaveText *lhcbTag = new TPaveText(boxStart-boxOffset,0.72,boxStart+0.24,0.89,"NDC");
  lhcbTag->SetFillColor(what=="SigKstarWM" ? 18 : 0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  lhcbTag->AddText(nice);
  lhcbTag->Draw("");
  
  // *** Legend *** //
  ////////////////////
  // Very nasty trick to get the dot in he legend in the correct color
  Float_t black_point[2];
  black_point[0] = 0;
  black_point[1] = 1;
  TGraph *black_contour = new TGraph(2,black_point,black_point);
  black_contour->SetMarkerStyle(29);
  black_contour->SetMarkerSize(1);
  black_contour->SetMarkerColor(1);
  black_contour->SetLineColor(1);
  
  Float_t red_point[2];
  red_point[0] = 0;
  red_point[1] = 1;
  TGraph *red_contour = new TGraph(2,red_point,red_point);
  red_contour->SetMarkerStyle(21);
  red_contour->SetMarkerSize(1);
  red_contour->SetMarkerColor(2);
  red_contour->SetLineColor(2);
  
  Float_t green_point[2];
  green_point[0] = 0;
  green_point[1] = 1;
  TGraph *green_contour = new TGraph(2,green_point,green_point);
  green_contour->SetMarkerStyle(22);
  green_contour->SetMarkerSize(0.8);
  green_contour->SetMarkerColor(3);
  green_contour->SetLineColor(3);
  
  Float_t blue_point[2];
  blue_point[0] = 0;
  blue_point[1] = 1;
  TGraph *blue_contour = new TGraph(2,blue_point,blue_point);
  blue_contour->SetMarkerStyle(23);
  blue_contour->SetMarkerSize(0.8);
  blue_contour->SetMarkerColor(4);
  blue_contour->SetLineColor(4);
  
  Float_t orange_point[2];
  orange_point[0] = 0;
  orange_point[1] = 1;
  TGraph *orange_contour = new TGraph(2,orange_point,orange_point);
  orange_contour->SetMarkerStyle(20);
  orange_contour->SetMarkerSize(0.8);
  orange_contour->SetMarkerColor(kOrange+1);
  orange_contour->SetLineColor(kOrange+1);

  TLegend *leg = new TLegend(boxStart-0.03,0.54-legOffset,boxStart+0.24,0.70);
  leg->AddEntry(blue_contour  ,"All from Stripping","lep");
  if(what=="SigKstarWM"){
    leg->AddEntry(orange_contour ,"+ Sel Cuts Applied","lep");
    leg->AddEntry(green_contour,"+ K^{*0} Veto Applied","lep");
  }
  else leg->AddEntry(green_contour,"+ Sel Cuts Applied","lep");
  leg->AddEntry(red_contour,"+ Trigger Applied","lep");
  leg->AddEntry(black_contour ,"+ NN Cut Applied","lep");
  leg->SetTextAlign(12);
  leg->SetTextSize(0.03);
  leg->SetTextFont(132);
  leg->Draw("");
  
  // *** Save ***
  if(tracktype==3) track = "_LL_";
  else if(tracktype==5) track = "_DD_";
  else track= "_";
  doek->SaveAs("Surviving_Events_"+what+track+which+".pdf");

    
  // ***** Output ***** //
  ////////////////////////

  std::cout << std::endl;  
  std::cout << "===========================" << std::endl;
  std::cout << "== Results: "+what+" ==" << std::endl;
  std::cout << "===========================" << std::endl;
  std::cout << "Mass Range = [" << Bmass_min << "," << Bmass_max << "]" << std::endl;
  std::cout << "Number of events from Stripping: " << data_All->numEntries() << "/" << data_All->numEntries() << " = " << (double) data_All->numEntries()/data_All->numEntries() << " of which " << Long_All << " (LL)" << std::endl;
  if(what=="SigKstarWM") std::cout << "Number of events passing Selection without KstarVeto: " << data_Veto->numEntries() << "/" << data_All->numEntries() << " = " << (double) data_Veto->numEntries()/data_All->numEntries() << " of which " << Long_Veto << " (LL)" << std::endl;
  std::cout << "Number of events passing Selection: " << data_Sel->numEntries() << "/" << data_All->numEntries() << " = " << (double) data_Sel->numEntries()/data_All->numEntries() << " of which " << Long_Sel << " (LL)" << std::endl;
  std::cout << "Number of events passing Trigger: " << data_Trig->numEntries() << "/" << data_All->numEntries() << " = " << (double) data_Trig->numEntries()/data_All->numEntries() << " of which " << Long_Trig << " (LL)" << std::endl;
  std::cout << "Number of events passing Neural Net: " << data_NN->numEntries() << "/" << data_All->numEntries() << " = " << (double) data_NN->numEntries()/data_All->numEntries() << " of which " << Long_NN << " (LL)" << std::endl;
  std::cout << std::endl;
  std::cout << "== " << (tracktype==3 ? "Long KS - " : (tracktype==5 ? "Down KS - " : "All KS - ")) << which << " ==" << std::endl;
  std::cout << "=====================" << std::endl;
  fitresult->Print();
  
}
