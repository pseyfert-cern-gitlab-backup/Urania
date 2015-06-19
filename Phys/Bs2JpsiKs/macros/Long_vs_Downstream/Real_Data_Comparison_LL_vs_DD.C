////////////////////////////////////////////////////////
// ***** Compare Long and Downstream KS Samples ***** //
////////////////////////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb
// - Compare the observables for the Long and Downstream KS Samples


/////////////////////////////////////
// ***** Load useful classes ***** //
/////////////////////////////////////

#include "RooAddPdf.h"
#include "RooArgSet.h"
#include "RooCategory.h"
#include "RooCBShape.h"
#include "RooDataSet.h"
#include "RooEfficiency.h"
#include "RooExponential.h"
#include "RooFit.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooRealVar.h"

#include "RooStats/SPlot.h"

#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TLegend.h"
#include "TMath.h"
#include "TNtuple.h"
#include "TPaveText.h"

using namespace RooFit;


///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void Momentum(TString what = "KS0"){

// ***** Initialize ***** //
////////////////////////////

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
  
  TFile* netFile = TFile::Open("B2JpsiKs-Eval-2-random-LHCb2011.root");
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
  Double_t Obs_P = -999;
  Int_t piminus_TRACK_Type = -999;
  // Neural Net
  Float_t netOutput[10];
  Int_t nPV2 = -999;
  
  // *** Initialize Arrays ***
  for(Int_t i=0; i<10; i++){
    netOutput[i] = -999;
  }
  

  // *** Set Branch Addresses ***
  // Observable
  chain->SetBranchAddress(what+"_P", &Obs_P);
  chain->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type);
  // Neural Net
  chain->SetBranchAddress("netOutput", &netOutput);
  chain->SetBranchAddress("nPV2", &nPV2);
  

  // ***** Initialize DataSet ***** //
  ////////////////////////////////////

  // *** Observable ***
  RooRealVar *myMom = new RooRealVar("myMom","mass",0,"MeV/c");
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
  
  bool pick = false;
  Long64_t selected_LL = 0;
  Long64_t selected_DD = 0;
  
  // *** Count ***
  std::cout << "Count" << std::endl;
  for(Long64_t i=0; i<nEntries_NTuple; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_NTuple << " (" << 100*i/nEntries_NTuple << "%)" << std::endl;

    for(Int_t pv=0; pv<nPV2 && !pick; pv++){
      if((piminus_TRACK_Type==3 && netOutput[pv]>NNcut_LL) || (piminus_TRACK_Type==5 && netOutput[pv]>NNcut_DD)){
        pick = true;

        if(piminus_TRACK_Type==3) selected_LL++;
        else if(piminus_TRACK_Type==5) selected_DD++;
      }
    }
    pick = false;
  }

  // *** Fill ***
  std::cout << "Fill" << std::endl;
  for(Long64_t i=0; i<nEntries_NTuple; i++){
    chain->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_NTuple << " (" << 100*i/nEntries_NTuple << "%)" << std::endl;

    for(Int_t pv=0; pv<nPV2 && !pick; pv++){
      if((piminus_TRACK_Type==3 && netOutput[pv]>NNcut_LL) || (piminus_TRACK_Type==5 && netOutput[pv]>NNcut_DD)){
        pick = true;
      
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
    pick = false;
  }
  
  std::cout << "Mean Momentum = " << data_LL->mean(*myMom) << " (LL) and " << data_DD->mean(*myMom) << " (DD)" << std::endl;
  
  // Free Memory
  delete chain;

  // ***** Plot: Mass ***** //
  ////////////////////////////
	
  // *** Signal ***
  Double_t max = (what=="KS0" ? 100000. : 500000.);
  RooPlot* momFrame = myMom->frame(Range(0.,max),Bins(100));

  // Titles
  TString scale = (what=="KS0" ? "1" : "5");
  momFrame->SetYTitle("Events/("+scale+"000 MeV/c)");
  TString nice = (what=="KS0" ? "K_{S}^{0}" : (what=="Psi" ? "J/#psi" : "B_{d}^{0}"));
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
  lhcbTag->AddText("#splitline{LHCb 2011}{#scale[0.7]{Reco 12 - Stripping 17b}}");
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
  doek->SaveAs(what+"_Momentum_NN60+75.pdf");

}
