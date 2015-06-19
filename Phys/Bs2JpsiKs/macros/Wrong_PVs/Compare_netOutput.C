///////////////////////////////////////////////
// ***** Bd2JpsiKs - Compare NN Output ***** //
///////////////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb
// - Compare the NN output for wrongly and correctly associated PVs


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

///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void CompareNN(TString what = "SigBd"){

// ***** Initialize ***** //
////////////////////////////

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

  TFile* netFile = TFile::Open("B2JpsiKs-Eval-2-random-"+what+".root");
  TTree* neural_net = (TTree*)netFile->Get("NetTree");

  TChain* chain = new TChain("chain");
  chain->Add("B2JpsiKs-Slim-"+what+".root/Slim_B2JpsiKs_Tuple");
  chain->AddFriend(neural_net);
  
  Long64_t nEntries_NTuple = chain->GetEntries();
  //nEntries_NTuple = 1000;  
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

  RooRealVar *NNpar = new RooRealVar("NNpar","netOutput", -1.,1.);
  RooRealVar *weight = new RooRealVar("weight","Weight for Normalisation", 0.,1.);

  // *** DataSet ***
  RooArgSet *Obs = new RooArgSet(*NNpar,*weight);
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
  
  bool TruthMatch = false;
  
  Long64_t Closest_LL = 0;
  Long64_t Closest_DD = 0;
  Long64_t Wrong_LL = 0;
  Long64_t Wrong_DD = 0;
  
  std::cout << " " << std::endl;
  std::cout << "== Loop 1: Count ==" << std::endl;
  std::cout << "===================" << std::endl;
 
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
          if((B_FullFit_M[pv]>=Bmass_min && B_FullFit_M[pv]<=Bmass_max) && B_FullFit_ctau[pv]/299.792458>=0.0002 && netOutput[pv]>=-1.){

            if(pv==truePV && piminus_TRACK_Type==3) Closest_LL++;
            else if(pv==truePV && piminus_TRACK_Type==5) Closest_DD++;
            else if(pv!=truePV && piminus_TRACK_Type==3) Wrong_LL++;
            else if(pv!=truePV && piminus_TRACK_Type==5) Wrong_DD++;
          
          }
        }
      }
    }
    // Reset
    DOCA_min = 999;
  }
  
  
  std::cout << " " << std::endl;
  std::cout << "== Loop 2: Fill ==" << std::endl;
  std::cout << "==================" << std::endl;
    
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
          if((B_FullFit_M[pv]>=Bmass_min && B_FullFit_M[pv]<=Bmass_max) && B_FullFit_ctau[pv]/299.792458>=0.0002 && netOutput[pv]>=-1.){
          
            NNpar->setVal(netOutput[pv]);
            if(pv==truePV && piminus_TRACK_Type==3){
              weight->setVal(1./Closest_LL);
              data_close_LL->add(*Obs, weight->getVal());
            }
            else if(pv==truePV && piminus_TRACK_Type==5){
              weight->setVal(1./Closest_DD);
              data_close_DD->add(*Obs, weight->getVal());
            }
            else if(pv!=truePV && piminus_TRACK_Type==3){
              weight->setVal(1./Wrong_LL);
              data_wrong_LL->add(*Obs, weight->getVal());
            }
            else if(pv!=truePV && piminus_TRACK_Type==5){
              weight->setVal(1./Wrong_DD);
              data_wrong_DD->add(*Obs, weight->getVal());
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
  

// ***** Part II: Results ***** //
//////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Part II: Results ==" << std::endl;
  std::cout << "======================" << std::endl;

  // ***** Numerical Results ***** //
  ///////////////////////////////////
  
  Int_t nClose_LL = data_close_LL->numEntries();
  Int_t nWrong_LL = data_wrong_LL->numEntries();
  Int_t nLL = nClose_LL + nWrong_LL;
  Int_t nClose_DD = data_close_DD->numEntries();
  Int_t nWrong_DD = data_wrong_DD->numEntries();
  Int_t nDD = nClose_DD + nWrong_DD;
  
  std::cout << std::endl;	
  std::cout << "LL Sample contains " << nWrong_LL << " (Wrong PVs) and " << nClose_LL << " (Closest PV), Fraction of wrongly associated PVs = " << (double) nWrong_LL/nLL << std::endl;
  std::cout << std::endl;
  std::cout << "DD Sample contains " << nWrong_DD << " (Wrong PVs) and " << nClose_DD << " (Closest PV), Fraction of wrongly associated PVs = " << (double) nWrong_DD/nDD << std::endl;


  // ***** Plot ***** //
  //////////////////////

  // *** Frame ***
  RooPlot* NNFrame = NNpar->frame(Bins(100));

  // Titles
  NNFrame->SetYTitle("Events/(0.02)");
  NNFrame->SetXTitle("NN Output");

  // Cosmetics
  NNFrame->SetTitleOffset(0.9,"x");
  NNFrame->SetTitleOffset(1.2,"y");
  NNFrame->SetTitleSize(0.07,"x");
  NNFrame->SetTitleSize(0.07,"y");
  NNFrame->SetTitleFont(132,"y");
  NNFrame->SetTitleFont(132,"x");
  NNFrame->SetLabelOffset(0.015,"y");
  NNFrame->SetLabelSize(0.05,"y");
  NNFrame->SetLabelSize(0.05,"x");
  NNFrame->SetLabelFont(132,"x");
  NNFrame->SetLabelFont(132,"y");
  
  // Content
  data_close_LL->plotOn(NNFrame,MarkerStyle(23),MarkerSize(0.8),MarkerColor(4),LineColor(4));
  data_close_DD->plotOn(NNFrame,MarkerStyle(22),MarkerSize(0.8),MarkerColor(3),LineColor(3));
  data_wrong_LL->plotOn(NNFrame,MarkerStyle(21),MarkerSize(0.8),MarkerColor(2),LineColor(2));
  data_wrong_DD->plotOn(NNFrame,MarkerStyle(29),MarkerSize(1.0),MarkerColor(1),LineColor(1));
  
  NNFrame->SetMinimum(0.);
  NNFrame->SetMaximum(0.09);
  
  
  // *** Further Decoration *** //
  ////////////////////////////////
  
  // *** LHCb Tag ***
  TPaveText *lhcbTag = new TPaveText(0.22,0.79,0.49,0.89,"NDC");
  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  lhcbTag->AddText("#splitline{LHCb MC11a}{#scale[0.7]{B_{d}^{0} #rightarrow J/#psi K_{S}^{0}}}");
  
  // *** Legend *** 
  
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
  

  TLegend *leg = new TLegend(0.23,0.58,0.55,0.78);
  leg->AddEntry(blue_contour,"Correct PVs - Long K_{S}^{0}","lep");
  leg->AddEntry(green_contour,"Correct PVs - Down K_{S}^{0}","lep");
  leg->AddEntry(red_contour,"Wrong PVs - Long K_{S}^{0}","lep");
  leg->AddEntry(black_contour,"Wrong PVs - Down K_{S}^{0}","lep");
  leg->SetTextAlign(12);
  leg->SetTextSize(0.03);
  leg->SetTextFont(132);
  
  // *** Line ***
  Float_t NN_pointx[4];
  NN_pointx[0] = 0.60;
  NN_pointx[1] = NN_pointx[0];
  NN_pointx[2] = 0.75;
  NN_pointx[3] = NN_pointx[2];
  Float_t NN_pointy[4];
  NN_pointy[0] = 0;
  NN_pointy[1] = 0.095;
  NN_pointy[2] = 0.095;
  NN_pointy[3] = 0.;
  TGraph *NN_line = new TGraph(4,NN_pointx,NN_pointy);
  NN_line->SetLineColor(kOrange+1);
  NN_line->SetLineWidth(2);


  // *** Canvas ***
  TCanvas *doek = new TCanvas("doek","Observable",900,800);
  doek->SetLeftMargin(0.2);
  doek->SetBottomMargin(0.15);
  NNFrame->Draw();
  lhcbTag->Draw("");
  leg->Draw("");
  NN_line->Draw("");
  
  doek->SaveAs("NNoutput_Closest_vs_WrongPV.pdf");

}