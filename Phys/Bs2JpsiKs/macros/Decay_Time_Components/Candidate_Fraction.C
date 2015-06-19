/////////////////////////////////////////////////////////
// ***** Bd2JpsiKs - Fraction of Long Candidates ***** //
/////////////////////////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb
// - Compare the fraction of Long and Downstream Candidates as a function of the decay time


/////////////////////////////////////
// ***** Load useful classes ***** //
/////////////////////////////////////

#include "RooRealVar.h"

#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TMath.h"
#include "TNtuple.h"
#include "TPaveText.h"

using namespace RooFit;

///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void DownFraction(TString what = "SigBd"){

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

  TFile* netFile = TFile::Open("/Users/Aranel/Documents/PhD_research/Bs2JpsiKs_Eff_Lifetime_Oct2012/NTuples/Optimal_Training/B2JpsiKs-Eval-2-random-"+what+".root");
  TTree* neural_net = (TTree*)netFile->Get("NetTree");

  TChain* chain = new TChain("chain");
  chain->Add("/Users/Aranel/Documents/PhD_research/Bs2JpsiKs_Eff_Lifetime_Oct2012/NTuples/B2JpsiKs-Slim-"+what+".root/Slim_B2JpsiKs_Tuple");
  chain->AddFriend(neural_net);
  
  Long64_t nEntries_NTuple = chain->GetEntries();
  //nEntries_NTuple = 25000;  
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

  // ***** Initialize Graph ***** //
  //////////////////////////////////

  

  // ***** Loop over Entries: Apply Selection Cuts ***** //
  /////////////////////////////////////////////////////////

  // Initialise
  Double_t DOCA = 0;
  Double_t DOCA_min = 999;
  Int_t truePV = 0;
  
  bool TruthMatch = false;
  
  const int bins = 15;
  double binSize = 15./bins;
  double binBoundary[bins];
  binBoundary[0] = 0;
  for(int i=0; i<bins; i++) binBoundary[i+1] = (i+1)*binSize;
  Long64_t nLL[bins];
  Long64_t nDD[bins];
  for(int i=0; i<bins; i++){ nLL[i]=0; nDD[i]=0;}
  double decTime = 0;
  
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
          if((B_FullFit_M[pv]>=Bmass_min && B_FullFit_M[pv]<=Bmass_max) && B_FullFit_ctau[pv]/299.792458>=0.0002){
            decTime = 1000*B_FullFit_ctau[pv]/299.792458;
            
            if(piminus_TRACK_Type==3 && netOutput[pv]>=0.60){
              for(int j=0; j<bins; j++){
                if(decTime>binBoundary[j] && decTime<binBoundary[j+1]) nLL[j]++;
              }
            }
            else if(piminus_TRACK_Type==5 && netOutput[pv]>=0.75){
              for(int j=0; j<bins; j++){
                if(decTime>binBoundary[j] && decTime<binBoundary[j+1]) nDD[j]++;
              }
            }
          }
        }
      }
    }
    // Reset
    DOCA_min = 999;
  }
  
  for(int i=0; i<bins; i++) std::cout << "Bin " << i << " with t in [" << binBoundary[i] << "," << binBoundary[i+1] << "] has " << nLL[i] << " Long and " << nDD[i] << " Down" << std::endl;
  
  
  // Free Memory
  delete chain;
  

// ***** Part II: Graph ***** //
////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Part II: Overview ==" << std::endl;
  std::cout << "=======================" << std::endl;
  
  double xpoint[bins];
  double xerr[bins];
  double yLLpoint[bins];
  double yDDpoint[bins];
  double yerr[bins];
  for(int i=0; i<bins; i++){
    xpoint[i] = (binBoundary[i]+binBoundary[i+1])/2;
    xerr[i] = binSize/2;
    yLLpoint[i] =  (nLL[i] + nDD[i])>0 ? (double) nLL[i]/(nLL[i] + nDD[i]) : 1;
    yDDpoint[i] =  (nLL[i] + nDD[i])>0 ? (double) nDD[i]/(nLL[i] + nDD[i]) : 0;
    yerr[i] = TMath::Sqrt(nLL[i] * nDD[i]/pow((double) nLL[i] + nDD[i],3));
  }
  
  TGraphErrors *contourLL = new TGraphErrors(bins,xpoint,yLLpoint,xerr,yerr);
  TGraphErrors *contourDD = new TGraphErrors(bins,xpoint,yDDpoint,xerr,yerr);


  // ***** Plot ***** //
  //////////////////////

  // *** Canvas ***
  TCanvas *doek = new TCanvas("doek","doek",900,800);
  doek->SetLeftMargin(0.2);
  doek->SetBottomMargin(0.15);
  doek->cd(1);
  
	// Add titles
  contourDD->GetXaxis()->SetTitle("Reco B decay time [ps]");
  contourDD->GetYaxis()->SetTitle("Fraction of Candidates");

  // Plot range
  contourDD->SetMaximum(1.2);
  contourDD->SetMinimum(0.);
  contourDD->GetXaxis()->SetRangeUser(0.,15.);
  //contourDD->GetXaxis()->SetNdivisions(-405);

  // Cosmetics
  contourDD->GetXaxis()->SetTitleSize(0.07);
  contourDD->GetXaxis()->SetTitleOffset(1);
  contourDD->GetXaxis()->SetLabelSize(0.05);
  contourDD->GetXaxis()->SetTitleFont(132);
  contourDD->GetXaxis()->SetLabelFont(132);

  contourDD->GetYaxis()->SetTitleSize(0.07);
  contourDD->GetYaxis()->SetTitleOffset(1);
  contourDD->GetYaxis()->SetLabelSize(0.05);
  contourDD->GetYaxis()->SetTitleFont(132);
  contourDD->GetYaxis()->SetLabelFont(132);

	contourDD->SetMarkerStyle(23);
	contourDD->SetMarkerSize(0.8);
  contourDD->SetMarkerColor(4);
  contourDD->SetLineColor(4);
  contourDD->SetLineWidth(2);
  
	contourLL->SetMarkerStyle(21);
	contourLL->SetMarkerSize(0.8);
  contourLL->SetMarkerColor(2);
  contourLL->SetLineColor(2);
  contourLL->SetLineWidth(2);

  // Draw
  contourDD->Draw("AP");
  contourLL->Draw("P");
  
  
  // *** Further Decoration *** //
  ////////////////////////////////
  
  // *** LHCb Tag ***
  TPaveText *lhcbTag = new TPaveText(0.62,0.79,0.89,0.89,"NDC");
  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  lhcbTag->AddText("#splitline{LHCb MC11a}{#scale[0.7]{B_{d}^{0} #rightarrow J/#psi K_{S}^{0}}}");
  
  lhcbTag->Draw("");
  
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

  TLegend *leg = new TLegend(0.62,0.69,0.89,0.77);
  leg->AddEntry(red_contour,"Long K_{S}^{0}","lep");
  leg->AddEntry(blue_contour,"Downstream K_{S}^{0}","lep");
  leg->SetTextAlign(12);
  leg->SetTextSize(0.03);
  leg->SetTextFont(132);
  leg->Draw("");
  
  doek->SaveAs("Candidate_Fraction.pdf");

}
