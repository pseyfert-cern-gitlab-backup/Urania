//////////////////////////////////////////////////////////////////////////
// ***** Bd2JpsiKs - Correlation between True and Reco Decay Time ***** //
//////////////////////////////////////////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb
// - Study the correlation between the true and reconstructed decay time
// - Situation for Closest PV and Wrong PV association


/////////////////////////////////////
// ***** Load useful classes ***** //
/////////////////////////////////////

#include "RooAddModel.h"
#include "RooArgSet.h"
#include "RooDataSet.h"
#include "RooDecay.h"
#include "RooEffProd.h"
#include "RooFitResult.h"
#include "RooGaussModel.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "RooResolutionModel.h"

#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH2.h"
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

void plotCorr(TH2D* correlation, TString savestring);
void FitPlotWrongPV(TString savestring, RooDataSet *Data_close, RooDataSet *Data_wrong, TString setup, double *Results);
void PullPlot(TString savestring, RooPlot* frame, Int_t logy=0); // Tweaked


///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void TwoDHist_True_vs_Reco(TString what = "SigBd", Bool_t prescaled = false, TString setup = "Frac", Double_t NNCut = 1){

// ***** Initialize ***** //
////////////////////////////

  Double_t NNcut_LL = (NNCut==1 ? 0.60 : NNCut);
  Double_t NNcut_DD = (NNCut==1 ? 0.75 : NNCut);

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

  TFile* netFile = 0;
  if(prescaled) netFile = TFile::Open("B2JpsiKs-Eval-2-random-"+what+"Prescaled.root");
  else netFile = TFile::Open("B2JpsiKs-Eval-2-random-"+what+".root");
  TTree* neural_net = (TTree*)netFile->Get("NetTree");

  TChain* chain = new TChain("chain");
  if(prescaled) chain->Add("B2JpsiKs-Slim-"+what+"Prescaled.root/Slim_B2JpsiKs_Tuple");
  else chain->Add("B2JpsiKs-Slim-"+what+".root/Slim_B2JpsiKs_Tuple");
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

  // *** Histogram ***
  Int_t xBins = 75;
  Int_t yBins = (prescaled ? 90 : 75);
  Double_t Xmin = 0.;
  Double_t Xmax = 15.;
  Double_t Ymin = (prescaled ? -3. : 0);
  Double_t Ymax = 15.;
  TH2D *correlation_close_LL = new TH2D("correlation_close_LL","Profile of X versus Y",xBins,Xmin,Xmax,yBins,Ymin,Ymax);
  TH2D *correlation_wrong_LL = new TH2D("correlation_wrong_LL","Profile of X versus Y",xBins,Xmin,Xmax,yBins,Ymin,Ymax);
  TH2D *correlation_close_DD = new TH2D("correlation_close_DD","Profile of X versus Y",xBins,Xmin,Xmax,yBins,Ymin,Ymax);
  TH2D *correlation_wrong_DD = new TH2D("correlation_wrong_DD","Profile of X versus Y",xBins,Xmin,Xmax,yBins,Ymin,Ymax);

  // *** Observable ***
  Blife = new RooRealVar("Blife","mass",Ymin,Ymax,"ps");
  RooRealVar *weight = new RooRealVar("weight","Weight for Normalisation", 0.,1.);

  // *** DataSet ***
  RooArgSet *Obs = new RooArgSet(*Blife,*weight);
  RooDataSet *data_close_LL = new RooDataSet("data_close_LL","Unbinned dataset",*Obs, WeightVar(*weight));
  RooDataSet *data_wrong_LL = new RooDataSet("data_wrong_LL","Unbinned dataset",*Obs, WeightVar(*weight));
  RooDataSet *data_close_DD = new RooDataSet("data_close_DD","Unbinned dataset",*Obs, WeightVar(*weight));
  RooDataSet *data_wrong_DD = new RooDataSet("data_wrong_DD","Unbinned dataset",*Obs, WeightVar(*weight));
  

  // ***** Loop over Entries: Apply Selection Cuts ***** //
  /////////////////////////////////////////////////////////

  // Initialise
  Double_t DOCA = 0;
  Double_t DOCA_min = 999;
  Int_t truePV = 0;
  Double_t Xvar = -999;
  Double_t Yvar = -999;
  
  bool TruthMatch = false;

  std::cout << " " << std::endl;
  std::cout << "== Loop 1: Selection Cuts ==" << std::endl;
  std::cout << "============================" << std::endl;
 
  for(Long64_t i=0; i<nEntries_NTuple; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_NTuple << " (" << 100*i/nEntries_NTuple << "%)" << std::endl;

    if((what=="SigBd") && TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && (B_BKGCAT==0 || B_BKGCAT==10)) TruthMatch = true;
    else if((what=="SigBs") && TMath::Abs(B_TRUEID)==531 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && B_BKGCAT==20) TruthMatch = true;
    else TruthMatch = false;

    if(TruthMatch){ // Select only True Signal
      if((PsiHlt1TrackMuonDecision_TOS || PsiHlt1DiMuonHighMassDecision_TOS || PsiHlt1TrackAllL0Decision_TOS) &&
         (PsiHlt2DiMuonDetachedJPsiDecision_TOS || PsiHlt2DiMuonJPsiHighPTDecision_TOS || PsiHlt2DiMuonJPsiDecision_TOS ||PsiHlt2TopoMu2BodyBBDTDecision_TOS)){ // Trigger
        
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
          if((B_FullFit_M[pv]>=Bmass_min && B_FullFit_M[pv]<=Bmass_max) && (prescaled || B_FullFit_ctau[pv]/299.792458>=0.0002)){          
            if((piminus_TRACK_Type==3 && netOutput[pv]>NNcut_LL) || (piminus_TRACK_Type==5 && netOutput[pv]>NNcut_DD)){
              Xvar = (Double_t)1000*B_TRUETAU;
              Yvar = (Double_t)B_FullFit_ctau[pv]*pow(10.,12)/(299792458*pow(10.,3));
              Blife->setVal(Yvar);
              weight->setVal(1.);
            
              if(pv==truePV){
                if(Xvar>Xmin && Xvar<Xmax && Yvar>Ymin && Yvar<Ymax){
                  if(piminus_TRACK_Type==3) correlation_close_LL->Fill(Xvar, Yvar);
                  else if(piminus_TRACK_Type==5) correlation_close_DD->Fill(Xvar, Yvar);
                }
                if(piminus_TRACK_Type==3) data_close_LL->add(*Obs, weight->getVal());
                if(piminus_TRACK_Type==5) data_close_DD->add(*Obs, weight->getVal());
              }
              else{
                if(Xvar>Xmin && Xvar<Xmax && Yvar>Ymin && Yvar<Ymax){
                  if(piminus_TRACK_Type==3) correlation_wrong_LL->Fill(Xvar, Yvar);
                  else if(piminus_TRACK_Type==5) correlation_wrong_DD->Fill(Xvar, Yvar);
                }
                if(piminus_TRACK_Type==3) data_wrong_LL->add(*Obs, weight->getVal());
                if(piminus_TRACK_Type==5) data_wrong_DD->add(*Obs, weight->getVal());              
              }
            }
          }
        }
      }
    }
    // Reset
    Xvar = -999;
    Yvar = -999;
    DOCA_min = 999;
  }

  // Free Memory
  delete chain;

// ***** Part II: Plotting ***** //
///////////////////////////////////	

  std::cout << std::endl;
  std::cout << "== Part II: Plotting ==" << std::endl;
  std::cout << "=======================" << std::endl;

  // *** Save ***  //
  //////////////////

  char buffer[3];
  TString Tail("");
  Int_t NNVal_LL = NNcut_LL*100;
  Int_t NNVal_DD = NNcut_DD*100;
  if(NNcut_DD>-1){
    std::sprintf(buffer,"_NN%d+%d",NNVal_LL,NNVal_DD);
    Tail.Append(buffer);
  }
  else Tail.Append("_Loose");
  if(prescaled) Tail.Append("_Prescaled");
  
  // ***** TwoD Plot ***** //
  ///////////////////////////

  plotCorr(correlation_close_LL, what+"_LL"+Tail+"_ClosestPV");
  plotCorr(correlation_wrong_LL, what+"_LL"+Tail+"_WrongPV");
  plotCorr(correlation_close_DD, what+"_DD"+Tail+"_ClosestPV");
  plotCorr(correlation_wrong_DD, what+"_DD"+Tail+"_WrongPV");

  // ***** Plot Reco Decay Time ***** //
  //////////////////////////////////////
  
  double Minuit_LL[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
  double Minuit_LL_Ignore[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
  if(!prescaled){
    FitPlotWrongPV(what+"_LL"+Tail, data_close_LL, data_wrong_LL, setup, Minuit_LL);
    if(what=="SigBd") FitPlotWrongPV("IgnoreRes_"+what+"_LL"+Tail, data_close_LL, data_wrong_LL, "FracOffset", Minuit_LL_Ignore);
  }
  
  double Minuit_DD[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
  double Minuit_DD_Ignore[] = {-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};
  if(!prescaled){
    FitPlotWrongPV(what+"_DD"+Tail, data_close_DD, data_wrong_DD, setup, Minuit_DD);
    if(what=="SigBd") FitPlotWrongPV("IgnoreRes_"+what+"_DD"+Tail, data_close_DD, data_wrong_DD, "FracOffset", Minuit_DD_Ignore);
  }
  
  // ***** Output ***** //
  ////////////////////////

  Int_t nClose_LL = data_close_LL->numEntries();
  Int_t nWrong_LL = data_wrong_LL->numEntries();
  Int_t nLL = nClose_LL + nWrong_LL;
  Int_t nClose_DD = data_close_DD->numEntries();
  Int_t nWrong_DD = data_wrong_DD->numEntries();
  Int_t nDD = nClose_DD + nWrong_DD;
  

  std::cout << std::endl;	
  std::cout << "============================================================" << std::endl;
  std::cout << "== PDF Results: Decay Time Fit of Wrongly Associated PVs: ==" << std::endl;
  std::cout << "============================================================" << std::endl;
  if(setup=="Exp") std::cout << "Acceptance Model: x*(1-Exp[-y*(tau-offset)])*(1+beta*tau)" << std::endl;
  else if(setup=="Tan") std::cout << "Acceptance Model: (2/acos(-1))*x*ArcTan[y*tau]*(1+beta*tau)" << std::endl;
  else if(setup=="TanOffset") std::cout << "Acceptance Model: (2/acos(-1))*x*ArcTan[y*(tau-offset)]*(1+beta*tau)" << std::endl;
  else if(setup=="Frac") std::cout << "Acceptance Model: x*(1+beta*tau)/(1+(z*tau)^-y)" << std::endl;
  else if(setup=="FracOffset") std::cout << "Acceptance Model: x*(1+beta*tau)/(1+(z*[tau-offset])^-y)" << std::endl;
  std::cout << std::endl;
  std::cout << "== Long KS ==" << std::endl;
  std::cout << "Sample contains " << nWrong_LL << " (Wrong PVs) and " << nClose_LL << " (Closest PV), Fraction of wrongly associated PVs = " << (double) nWrong_LL/nLL << std::endl;
  std::cout << std::endl;
  std::cout << "Wrong PV Resolution Model" << std::endl;
  if(Minuit_LL[0]!=-999) std::cout << "x = " << Minuit_LL[0] << " +/- " << Minuit_LL[1] << std::endl;
  if(Minuit_LL[2]!=-999) std::cout << "y = " << Minuit_LL[2] << " +/- " << Minuit_LL[3] << std::endl;
  if(Minuit_LL[4]!=-999) std::cout << "z = " << Minuit_LL[4] << " +/- " << Minuit_LL[5] << std::endl;
  if(Minuit_LL[6]!=-999) std::cout << "offset = " << Minuit_LL[6] << " +/- " << Minuit_LL[7] << std::endl;
  if(Minuit_LL[8]!=-999) std::cout << "beta = " << Minuit_LL[8] << " +/- " << Minuit_LL[9] << std::endl;
	std::cout << std::endl;
  std::cout << "Correct PV Resolution Model" << std::endl;
  if(Minuit_LL_Ignore[0]!=-999) std::cout << "x = " << Minuit_LL_Ignore[0] << " +/- " << Minuit_LL_Ignore[1] << std::endl;
  if(Minuit_LL_Ignore[2]!=-999) std::cout << "y = " << Minuit_LL_Ignore[2] << " +/- " << Minuit_LL_Ignore[3] << std::endl;
  if(Minuit_LL_Ignore[4]!=-999) std::cout << "z = " << Minuit_LL_Ignore[4] << " +/- " << Minuit_LL_Ignore[5] << std::endl;
  if(Minuit_LL_Ignore[6]!=-999) std::cout << "offset = " << Minuit_LL_Ignore[6] << " +/- " << Minuit_LL_Ignore[7] << std::endl;
  if(Minuit_LL_Ignore[8]!=-999) std::cout << "beta = " << Minuit_LL_Ignore[8] << " +/- " << Minuit_LL_Ignore[9] << std::endl;
	std::cout << std::endl;
  std::cout << "== Downstream KS ==" << std::endl;
  std::cout << "Sample contains " << nWrong_DD << " (Wrong PVs) and " << nClose_DD << " (Closest PV), Fraction of wrongly associated PVs = " << (double) nWrong_DD/nDD << std::endl;
  std::cout << std::endl;
  std::cout << "Wrong PV Resolution Model" << std::endl;
  if(Minuit_DD[0]!=-999) std::cout << "x = " << Minuit_DD[0] << " +/- " << Minuit_DD[1] << std::endl;
  if(Minuit_DD[2]!=-999) std::cout << "y = " << Minuit_DD[2] << " +/- " << Minuit_DD[3] << std::endl;
  if(Minuit_DD[4]!=-999) std::cout << "z = " << Minuit_DD[4] << " +/- " << Minuit_DD[5] << std::endl;
  if(Minuit_DD[6]!=-999) std::cout << "offset = " << Minuit_DD[6] << " +/- " << Minuit_DD[7] << std::endl;
  if(Minuit_DD[8]!=-999) std::cout << "beta = " << Minuit_DD[8] << " +/- " << Minuit_DD[9] << std::endl;
	std::cout << std::endl;
  std::cout << "Correct PV Resolution Model" << std::endl;
  if(Minuit_DD_Ignore[0]!=-999) std::cout << "x = " << Minuit_DD_Ignore[0] << " +/- " << Minuit_DD_Ignore[1] << std::endl;
  if(Minuit_DD_Ignore[2]!=-999) std::cout << "y = " << Minuit_DD_Ignore[2] << " +/- " << Minuit_DD_Ignore[3] << std::endl;
  if(Minuit_DD_Ignore[4]!=-999) std::cout << "z = " << Minuit_DD_Ignore[4] << " +/- " << Minuit_DD_Ignore[5] << std::endl;
  if(Minuit_DD_Ignore[6]!=-999) std::cout << "offset = " << Minuit_DD_Ignore[6] << " +/- " << Minuit_DD_Ignore[7] << std::endl;
  if(Minuit_DD_Ignore[8]!=-999) std::cout << "beta = " << Minuit_DD_Ignore[8] << " +/- " << Minuit_DD_Ignore[9] << std::endl;

}


/////////////////////////////////
// ***** Helper Function ***** //
/////////////////////////////////
void plotCorr(TH2D* correlation, TString savestring){

  // *** Initialise ***
  string convSave (savestring);
  size_t isLL = convSave.find("LL");
  size_t isDD = convSave.find("DD");
  size_t isPrescaled = convSave.find("Prescaled");
  
  
  // *** Cosmetics ***
  correlation->GetXaxis()->SetTitle("True B decay time (ps)");
  correlation->GetXaxis()->SetTitleOffset(0.8);
  correlation->GetXaxis()->SetTitleSize(0.07);
  correlation->GetXaxis()->SetTitleFont(132);
  correlation->GetXaxis()->SetLabelSize(0.05);
  correlation->GetXaxis()->SetLabelFont(132);
  
  correlation->GetYaxis()->SetTitle("Reco B decay time (ps)");
  correlation->GetYaxis()->SetTitleOffset(0.8);
  correlation->GetYaxis()->SetTitleSize(0.07);
  correlation->GetYaxis()->SetTitleFont(132);
  correlation->GetYaxis()->SetLabelSize(0.05);
  correlation->GetYaxis()->SetLabelFont(132);
    
  if(isPrescaled!=string::npos) correlation->GetYaxis()->SetRangeUser(-3.,15.);
  else correlation->GetYaxis()->SetRangeUser(0.,15.);
  correlation->SetMaximum(10000);
  correlation->SetMinimum(1);

  // *** Canvas ***
  TCanvas *doek = new TCanvas("doek","Observable",900,800);
  doek->cd(1);
  doek->SetLeftMargin(0.12);
  doek->SetRightMargin(0.12);
  doek->SetBottomMargin(0.15);
  doek->cd(1);
  gPad->SetLogz(1);
  correlation->Draw("COLZ");
  
  // *** LHCb Tag *** 
  TString track("");
  if(isLL!=string::npos) track = "Long K_{S}^{0}";
  else if(isDD!=string::npos) track = "Downstream K_{S}^{0}";
  
  TPaveText *lhcbTag = new TPaveText(0.59,0.22,0.84,0.37,"NDC");

  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  lhcbTag->AddText("#splitline{LHCb MC11a}{#splitline{#scale[0.7]{B_{d}^{0}#rightarrow J/#psi K_{S}^{0}}}{#scale[0.7]{"+track+"}}}");
  lhcbTag->Draw();
  
  // *** Save ***
  doek->SaveAs("Correlation_True_vs_Reco_"+savestring+".pdf");
}


/////////////////////////////////
// ***** Helper Function ***** //
/////////////////////////////////
void FitPlotWrongPV(TString savestring, RooDataSet *Data_close, RooDataSet *Data_wrong, TString setup, double *Results){

  // ********** Initialise ********** //
  //////////////////////////////////////
  
  string convSave (savestring);
  TString what = "";
  if(convSave.find("SigBd")!=string::npos) what = "SigBd";
  else if(convSave.find("SigBs")!=string::npos) what = "SigBs";
  Int_t ttype = 0;
  if(convSave.find("LL")!=string::npos) ttype = 3;
  else if(convSave.find("DD")!=string::npos) ttype = 5;
  bool ignoreRes = false;
  if(convSave.find("IgnoreRes")!=string::npos) ignoreRes = true;
  
	// *** Lifetime ***		
	RooRealVar *tauB = new RooRealVar("tauB","Generated Bd lifetime",(what=="SigBd" ? 1.525 : 1.475),"ps");	
  
  // *** Resolution ***	
  RooRealVar *resMeanW = new RooRealVar("resMeanW","Resolution - Mean",(ttype==3 ? 0.076 : 0.056),"ps");
  RooRealVar *resMeanW_II = new RooRealVar("resMeanW_II","Resolution - Mean",(ttype==3 ? 0.77 : 0.87),"ps");
	RooRealVar *coreSigmaW = new RooRealVar("coreSigmaW","Resolution - Core Width",(ttype==3 ? 0.678 : 0.498),"ps");
	RooRealVar *tailSigmaW = new RooRealVar("tailSigmaW","Resolution - Tail Width",(ttype==3 ? 2.42 : 1.95),"ps");
  RooRealVar *CorefracW = new RooRealVar("CorefracW","Fraction of Core", (ttype==3 ? 0.615 : 0.664));
  
  RooRealVar *resMeanC = new RooRealVar("resMeanC","Resolution - Mean",0.,"ps");
	RooRealVar *coreSigmaC = new RooRealVar("coreSigmaC","Resolution - Core Width",(ttype==3 ? 0.0313289 : 0.0313592),"ps");
  RooRealVar *midSigmaC = new RooRealVar("midSigmaC","Resolution - Middle Width",(ttype==3 ? 0.0612225 : 0.0634281),"ps");
	RooRealVar *tailSigmaC = new RooRealVar("tailSigmaC","Resolution - Tail Width",(ttype==3 ? 0.37931 : 0.210496),"ps");
  RooRealVar *CorefracC = new RooRealVar("CorefracC","Fraction of Core", (ttype==3 ? 0.702295 : 0.633399));
  RooRealVar *MidfracC = new RooRealVar("MidfracC","Fraction of Mid", (ttype==3 ? 0.28924 : 0.354031));
	
  // *** Acceptance ***
	accX = new RooRealVar("accX","For Acceptance Function",0.9,0.,(setup=="Exp" ? 1. : 1.5));
	accY = new RooRealVar("accY","For Acceptance Function",1.5,0.,5.);
	accZ = new RooRealVar("accZ","For Acceptance Function",2., 0. ,10.);	
  accOffset = new RooRealVar("accOffset","For Acceptance Function",0.1, -0.5,0.5);	
	accVelo = new RooRealVar("accVelo","For Acceptance Function",-0.0007,-0.1,1.);


  // ********** Time PDFs ********** //
  /////////////////////////////////////

  // *** Acceptance ***
  RooFormulaVar *acceptance = 0;
  if(setup=="Tan") acceptance = new RooFormulaVar("acceptance","an acceptance function","(2/acos(-1))*@0*TMath::ATan(@1*@3)*(1+@2*@3)",RooArgList(*accX,*accY,*accVelo,*Blife));
  else if(setup=="TanOffset") acceptance = new RooFormulaVar("acceptance","an acceptance function","(2/acos(-1))*@0*TMath::ATan(@1*(@4-@2))*(1+@3*@4)",RooArgList(*accX,*accY,*accOffset,*accVelo,*Blife));
  else if(setup=="Exp") acceptance = new RooFormulaVar("acceptance","an acceptance function","@0*(1-TMath::Exp(-(@4-@2)*@1))*(1+@3*@4)",RooArgList(*accX,*accY,*accOffset,*accVelo,*Blife));
  else if(setup=="Frac") acceptance = new RooFormulaVar("acceptance","an acceptance function","@0*(1+@3*@4)/(1+pow(@2*@4,-@1))",RooArgList(*accX,*accY,*accZ,*accVelo,*Blife));
  else if(setup=="FracOffset") acceptance = new RooFormulaVar("acceptance","an acceptance function","(@2*(@5-@3)>0 ? @0*(1+@4*@5)/(1+pow(@2*(@5-@3),-@1)) : 0.)",RooArgList(*accX,*accY,*accZ,*accOffset,*accVelo,*Blife));
  	
  // *** Resolution ***	
  RooGaussModel *coreW = new RooGaussModel("coreW","Core Gaussian",*Blife,*resMeanW,*coreSigmaW);
  RooGaussModel *tailW = new RooGaussModel("tailW","Tail Gaussian",*Blife,*resMeanW_II,*tailSigmaW);
  RooAddModel *Res_ModelW = new RooAddModel("Res_ModelW","Resolution Model",RooArgList(*coreW,*tailW),RooArgList(*CorefracW));
  
  RooGaussModel *coreC = new RooGaussModel("coreC","Core Gaussian",*Blife,*resMeanC,*coreSigmaC);
  RooGaussModel *midC = new RooGaussModel("midC","Middle Gaussian",*Blife,*resMeanC,*midSigmaC);
  RooGaussModel *tailC = new RooGaussModel("tailC","Tail Gaussian",*Blife,*resMeanC,*tailSigmaC);
  RooAddModel *Res_ModelC = new RooAddModel("Res_ModelC","Resolution Model",RooArgList(*coreC,*midC,*tailC),RooArgList(*CorefracC,*MidfracC));
  
  // *** RooDecays ***
	RooDecay *decayW_Bd = new RooDecay("decayW_Bd","Long Lifetimes",*Blife,*tauB,*Res_ModelW,RooDecay::SingleSided);  
  RooEffProd *decayW_acc = new RooEffProd("decayW_acc","Decay with acceptance",*decayW_Bd,*acceptance);
  
	RooDecay *decayC_Bd = new RooDecay("decayC_Bd","Long Lifetimes",*Blife,*tauB,*Res_ModelC,RooDecay::SingleSided);  
  RooEffProd *decayC_acc = new RooEffProd("decayC_acc","Decay with acceptance",*decayC_Bd,*acceptance);


  // *** Initialise *** //
  //////////////////////// 

  // *** Initialise Fitting ***
  accX->setVal(1);
  accX->setConstant();
  Blife->setRange("detached",0.2 ,15.);

  // *** Initialise Frame ***
  RooPlot* BFrame = Blife->frame(Range(0.,15),Bins(75));

  // Titles
  BFrame->SetYTitle("Events/(0.2 ps)");
  BFrame->SetXTitle("Reco B Decay Time (ps)");

  // Cosmetics
  BFrame->SetTitleOffset(0.9,"x");
  BFrame->SetTitleOffset(1.2,"y");
  BFrame->SetTitleSize(0.07,"x");
  BFrame->SetTitleSize(0.07,"y");
  BFrame->SetTitleFont(132,"y");
  BFrame->SetTitleFont(132,"x");
  BFrame->SetLabelOffset(0.015,"y");
  BFrame->SetLabelSize(0.05,"y");
  BFrame->SetLabelSize(0.05,"x");
  BFrame->SetLabelFont(132,"x");
  BFrame->SetLabelFont(132,"y");
  
  // *** Fit && Plot *** //
  ///////////////////////// 
  
  // *** Closest PV ***
  //RooFitResult *fitresult_close = 
  if(what=="SigBs"){
    accY->setVal(ttype==3 ? 1.607 : 1.999);
    accZ->setVal(ttype==3 ? 2.800 : 1.525);
    accVelo->setVal(ttype==3 ? -0.0203 : 0.0289);
    
    accY->setConstant();
    accZ->setConstant();
    accVelo->setConstant();
  }
  accOffset->setVal(0.);
  accOffset->setConstant(true);
  decayC_acc->fitTo(*Data_close,Range("detached"),Save());
  Data_close->plotOn(BFrame,MarkerStyle(23),MarkerSize(0.8),MarkerColor(4),LineColor(4));
  decayC_acc->plotOn(BFrame,LineColor(4),LineWidth(2));
  
  // *** Wrong PVs ***
  if(what=="SigBs"){
    accY->setVal(ttype==3 ? 2.79 : 0.873);
    accZ->setVal(ttype==3 ? 2.22 : 0.00091);
    accVelo->setVal(ttype==3 ? 0.28 : 0.073);
    
    accY->setConstant();
    accZ->setConstant();
    accVelo->setConstant();
  }
  accOffset->setConstant(false);
  RooFitResult *fitresult_wrong = 0;
  if(ignoreRes){
    fitresult_wrong = decayC_acc->fitTo(*Data_wrong,Range("detached"),Save());
    Data_wrong->plotOn(BFrame,MarkerStyle(21),MarkerSize(0.8),MarkerColor(2),LineColor(2));
    decayC_acc->plotOn(BFrame,LineColor(2),LineWidth(2));
  }
  else{
    fitresult_wrong = decayW_acc->fitTo(*Data_wrong,Range("detached"),Save());
    Data_wrong->plotOn(BFrame,MarkerStyle(21),MarkerSize(0.8),MarkerColor(2),LineColor(2));
    decayW_acc->plotOn(BFrame,LineColor(2),LineWidth(2));
  }

  
  // More cosmetics
  BFrame->SetMinimum(0.9);
  BFrame->SetMaximum(what=="SigBd" ? 10000 : 1000);

  // PullPlot
  TString saveString = "WrongPV_"+savestring+".pdf";
  if(what=="SigBs") saveString = "WrongPV_"+savestring+"PullOnly.pdf";
  PullPlot(saveString,BFrame,1);
  
  // *** Results *** //
  /////////////////////

	// Obtaining information from fitted PDF
	if(fitresult_wrong->covQual()==3){

    const RooArgList& fitted_par = fitresult_wrong->floatParsFinal();
	
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
	pullgraph->SetFillColor(2);
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
  
  // *** LHCb Tag ***
	TPaveText *lhcbTag = 0;
  if(logy==1) lhcbTag = new TPaveText(0.65,0.70,0.89,0.89,"NDC");
	else if(logy==0) lhcbTag = new TPaveText(0.23,0.70,0.47,0.89,"NDC");

  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  if(isBd!=string::npos) lhcbTag->AddText("#splitline{LHCb MC11a}{#splitline{#scale[0.7]{B_{d}^{0}#rightarrow J/#psi K_{S}^{0}}}{#scale[0.7]{"+track+"}}}");
  else if(isBs!=string::npos) lhcbTag->AddText("#splitline{LHCb MC11a}{#splitline{#scale[0.7]{B_{s}^{0}#rightarrow J/#psi K_{S}^{0}}}{#scale[0.7]{"+track+"}}}");
  lhcbTag->Draw();
  
  // *** Legend *** //
  ////////////////////
  // Very nasty trick to get the dot in he legend in the correct color  
  Float_t red_point[2];
  red_point[0] = 0;
  red_point[1] = 1;
  TGraph *red_contour = new TGraph(2,red_point,red_point);
  red_contour->SetMarkerStyle(21);
  red_contour->SetMarkerSize(1);
  red_contour->SetMarkerColor(2);
  red_contour->SetLineColor(2);
  
  Float_t blue_point[2];
  blue_point[0] = 0;
  blue_point[1] = 1;
  TGraph *blue_contour = new TGraph(2,blue_point,blue_point);
  blue_contour->SetMarkerStyle(23);
  blue_contour->SetMarkerSize(0.8);
  blue_contour->SetMarkerColor(4);
  blue_contour->SetLineColor(4);

  TLegend *leg = new TLegend(0.65,0.60,0.83,0.68);
  leg->AddEntry(blue_contour  ,"Closest PV","lep");
  leg->AddEntry(red_contour,"Wrong PVs","lep");
  leg->SetTextAlign(12);
  leg->SetTextSize(0.03);
  leg->SetTextFont(132);
  leg->Draw("");
  

	
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