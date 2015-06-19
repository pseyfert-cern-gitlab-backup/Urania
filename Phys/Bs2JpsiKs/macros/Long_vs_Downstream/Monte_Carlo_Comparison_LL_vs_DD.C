////////////////////////////////////////////////////////
// ***** Compare Long and Downstream KS Samples ***** //
////////////////////////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb
// - Compare the observables for the Long and Downstream KS Samples


/////////////////////////////////////
// ***** Load useful classes ***** //
/////////////////////////////////////

#include "RooArgSet.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooRealVar.h"

#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TLegend.h"
#include "TMath.h"
#include "TNtuple.h"
#include "TPaveText.h"

using namespace RooFit;


/////////////////////////////////
// ***** Helper Function ***** //
/////////////////////////////////
void MCComparison(TString which, TString what = "Loose"){

// ***** Initialize ***** //
////////////////////////////

  TString decay = "SigBd";

  // *** Neural Net ***
  Double_t NNcut_LL = 0.60;
  Double_t NNcut_DD = 0.75;


// ***** Part I: From NTuple to DataSet ***** //
////////////////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Part I: From NTuple to DataSet ==" << std::endl;
  std::cout << "====================================" << std::endl;

  // ***** Load NTuples ***** //
  //////////////////////////////
  
  TFile* netFile = 0;
  if(what=="Loose") netFile = TFile::Open("B2JpsiKs-Eval-1-random-SigBd.root");
  else if(what=="NN") netFile = TFile::Open("B2JpsiKs-Eval-2-random-SigBd.root");
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
  Int_t piminus_TRACK_Type = -999;
  Double_t Obs_P = -999;
  // PV Matching
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
  Double_t B_TRUEORIGINVERTEX_X = -999;
  Double_t B_TRUEORIGINVERTEX_Y = -999;
  Double_t B_TRUEORIGINVERTEX_Z = -999;
  
  // *** Initialize Arrays ***
  for(Int_t i=0; i<10; i++){
    netOutput[i] = -999;
  }
  

  // *** Set Branch Addresses ***
  // Observable
  chain->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type);
  chain->SetBranchAddress(which+"_P", &Obs_P);
  // PV Matching
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
  chain->SetBranchAddress("B_TRUEORIGINVERTEX_X", &B_TRUEORIGINVERTEX_X);
  chain->SetBranchAddress("B_TRUEORIGINVERTEX_Y", &B_TRUEORIGINVERTEX_Y);
  chain->SetBranchAddress("B_TRUEORIGINVERTEX_Z", &B_TRUEORIGINVERTEX_Z);
  

  // ***** Initialize DataSet ***** //
  ////////////////////////////////////

  // *** Observable ***
  RooRealVar *myMom = new RooRealVar("myMom","Momentum",0,"MeV/c");
  RooRealVar *weight = new RooRealVar("weight","Weight for Normalisation", 0.,1.);

  // *** DataSet ***
  RooArgSet *Obs = new RooArgSet(*myMom,*weight);
  RooDataSet *data_LL = new RooDataSet("data_LL","Unbinned dataset",*Obs, WeightVar(*weight));
  RooDataSet *data_DD = new RooDataSet("data_DD","Unbinned dataset",*Obs, WeightVar(*weight));


  // ***** Loop over Entries: Apply Selection Cuts ***** //
  /////////////////////////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Loop 1: Selection Cuts ==" << std::endl;
  std::cout << "============================" << std::endl;

  // Initialise
  Double_t DOCA = 0;
  Double_t DOCA_min = 999;
  Int_t truePV = 0;
  Long64_t selected_LL = 0;
  Long64_t selected_DD = 0;
  
  bool TruthMatch = false;
  bool Trigger = false;
  bool NN = false;
  bool Loose = false;

  // *** Count ***
  std::cout << "Count" << std::endl;
  for(Long64_t i=0; i<nEntries_NTuple; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_NTuple << " (" << 100*i/nEntries_NTuple << "%)" << std::endl;

    if(decay=="SigBd") TruthMatch = (TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && (B_BKGCAT==0 || B_BKGCAT==10));
    else if(decay=="SigBs") TruthMatch = (TMath::Abs(B_TRUEID)==531 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && (B_BKGCAT==20));

    if(TruthMatch){ // Select only True Signal
        
      // Loop 1: Determine DOCA
      for(Int_t pv = 0; pv < nPV2 ; pv++){ 
        DOCA = TMath::Sqrt(pow(B_TRUEORIGINVERTEX_X-B_FullFit_PV_X[pv],2) + pow(B_TRUEORIGINVERTEX_Y-B_FullFit_PV_Y[pv],2) + pow(B_TRUEORIGINVERTEX_Z-B_FullFit_PV_Z[pv],2));
        if(DOCA<DOCA_min){
          DOCA_min = DOCA;
          truePV = pv;
        }
      }
      
      Trigger = (PsiHlt1TrackMuonDecision_TOS || PsiHlt1DiMuonHighMassDecision_TOS || PsiHlt1TrackAllL0Decision_TOS) &&
                (PsiHlt2DiMuonDetachedJPsiDecision_TOS || PsiHlt2DiMuonJPsiHighPTDecision_TOS || PsiHlt2DiMuonJPsiDecision_TOS ||
                 PsiHlt2TopoMu2BodyBBDTDecision_TOS);
      NN = (((piminus_TRACK_Type==3 && netOutput[truePV]>NNcut_LL) || (piminus_TRACK_Type==5 && netOutput[truePV]>NNcut_DD))  && Trigger);
      Loose = (netOutput[truePV]>-1 && Trigger);
                 
      // Loop 2: Fill
      if((what=="Loose" && Loose) || (what=="NN" && NN)){
        if(piminus_TRACK_Type==3) selected_LL++;
        else if(piminus_TRACK_Type==5) selected_DD++;
      }
    }
    // Reset
    DOCA_min = 999;
  }
    
  // *** Fill ***
  std::cout << "Fill" << std::endl;
  for(Long64_t i=0; i<nEntries_NTuple; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_NTuple << " (" << 100*i/nEntries_NTuple << "%)" << std::endl;

    if(decay=="SigBd") TruthMatch = (TMath::Abs(B_TRUEID)==511 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && (B_BKGCAT==0 || B_BKGCAT==10));
    else if(decay=="SigBs") TruthMatch = (TMath::Abs(B_TRUEID)==531 && Psi_TRUEID==443 && TMath::Abs(KS0_TRUEID)==310 && (B_BKGCAT==20));

    if(TruthMatch){ // Select only True Signal
        
      // Loop 1: Determine DOCA
      for(Int_t pv = 0; pv < nPV2 ; pv++){ 
        DOCA = TMath::Sqrt(pow(B_TRUEORIGINVERTEX_X-B_FullFit_PV_X[pv],2) + pow(B_TRUEORIGINVERTEX_Y-B_FullFit_PV_Y[pv],2) + pow(B_TRUEORIGINVERTEX_Z-B_FullFit_PV_Z[pv],2));
        if(DOCA<DOCA_min){
          DOCA_min = DOCA;
          truePV = pv;
        }
      }
      
      Trigger = (PsiHlt1TrackMuonDecision_TOS || PsiHlt1DiMuonHighMassDecision_TOS || PsiHlt1TrackAllL0Decision_TOS) &&
                (PsiHlt2DiMuonDetachedJPsiDecision_TOS || PsiHlt2DiMuonJPsiHighPTDecision_TOS || PsiHlt2DiMuonJPsiDecision_TOS ||
                 PsiHlt2TopoMu2BodyBBDTDecision_TOS);
      NN = (((piminus_TRACK_Type==3 && netOutput[truePV]>NNcut_LL) || (piminus_TRACK_Type==5 && netOutput[truePV]>NNcut_DD))  && Trigger);
      Loose = (netOutput[truePV]>-1 && Trigger);
                 
      // Loop 2: Fill
      if((what=="Loose" && Loose) || (what=="NN" && NN)){
      
        myMom->setVal(Obs_P);
        if(piminus_TRACK_Type==3){
          weight->setVal(1./(selected_LL));
          data_LL->add(*Obs, weight->getVal());
        }
        else if(piminus_TRACK_Type==5){
          weight->setVal(1./(selected_DD));
          data_DD->add(*Obs, weight->getVal());
        }
      }
    }
    // Reset
    DOCA_min = 999;
  }
  
  // Free Memory
  delete chain;
  
  std::cout << std::endl;
  std::cout << "Average Momentum (Long): " << data_LL->mean(*myMom) << " +/- " << data_LL->sigma(*myMom) << std::endl;
  std::cout << "Average Momentum (Down): " << data_DD->mean(*myMom) << " +/- " << data_DD->sigma(*myMom) << std::endl;
  std::cout << std::endl;

// ***** Part II: Plot ***** //
///////////////////////////////  

  std::cout << std::endl;
  std::cout << "== Part II: Plot ==" << std::endl;
  std::cout << "===================" << std::endl;
	
  // *** Signal ***
  Double_t max = (which=="KS0" ? 100000. : 500000.);
  RooPlot* momFrame = myMom->frame(Range(0.,max),Bins(100));

  // Titles
  TString scale = (which=="KS0" ? "1" : "5");
  momFrame->SetYTitle("Events/("+scale+"000 MeV/c)");
  TString nice = (which=="KS0" ? "K_{S}^{0}" : (which=="Psi" ? "J/#psi" : "B_{d}^{0}"));
  momFrame->SetXTitle(nice+" Momentum (MeV/c)");

  // Cosmetics
  momFrame->SetTitleOffset(1.2,"y");
  momFrame->SetTitleSize(0.07,"x");
  momFrame->SetTitleSize(0.07,"y");
  momFrame->SetTitleFont(132,"y");
  momFrame->SetTitleFont(132,"x");
  momFrame->SetLabelSize(0.05,"y");
  momFrame->SetLabelSize(0.05,"x");
  momFrame->SetLabelFont(132,"x");
  momFrame->SetLabelFont(132,"y");

  data_DD->plotOn(momFrame,MarkerStyle(21),MarkerSize(0.8),MarkerColor(2),LineColor(2));
  data_LL->plotOn(momFrame,MarkerStyle(23),MarkerSize(0.8),MarkerColor(4),LineColor(4));

  momFrame->SetMinimum(0.0001);
  momFrame->SetMaximum(0.1);

	  // *** Canvas ***
  TCanvas *doek = new TCanvas("doek","doek",900,800);
  doek->SetLeftMargin(0.2);
  doek->SetBottomMargin(0.15);
  doek->cd(1);
  gPad->SetLogy(1);
  momFrame->Draw("");
  
  // *** LHCb Tag ***
  TPaveText *lhcbTag = new TPaveText(0.60,0.75,0.89,0.89,"NDC");
  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  if(decay=="SigBs") lhcbTag->AddText("#splitline{LHCb MC11a}{#scale[0.7]{B_{s}^{0}#rightarrow J/#psi K_{S}^{0}}}");
  else if(decay=="SigBd") lhcbTag->AddText("#splitline{LHCb MC11a}{#scale[0.7]{B_{d}^{0}#rightarrow J/#psi K_{S}^{0}}}");
  lhcbTag->Draw("");
  
  
  // *** Legend *** 
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

  TLegend *leg = new TLegend(0.60,0.67,0.89,0.75);
  leg->AddEntry(blue_contour,"Long K_{S}^{0}","lep");
  leg->AddEntry(red_contour,"Down K_{S}^{0}","lep");
  leg->SetTextAlign(12);
  leg->SetTextSize(0.03);
  leg->SetTextFont(132);
  leg->Draw("");
  
  // *** Save ***
  if(what=="NN") doek->SaveAs(which+"_Momentum_SigBd_NN60+75.pdf");
  else if(what=="Loose") doek->SaveAs(which+"_Momentum_SigBd_Loose.pdf");

}
