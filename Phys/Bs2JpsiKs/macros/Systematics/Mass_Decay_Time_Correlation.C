/////////////////////////////////////////////////////////
// ***** Correlation Between Mass and Decay Time ***** //
/////////////////////////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb
// - Search for a correlation between the reconstructed mass and the decay time difference


/////////////////////////////////////
// ***** Load useful classes ***** //
/////////////////////////////////////

#include "RooRealVar.h"

#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH2.h"
#include "TMath.h"
#include "TNtuple.h"
#include "TPaveText.h"
#include "TProfile.h"

using namespace RooFit;

//////////////////////////////
// ***** Declarations ***** //
//////////////////////////////
void FitPlotProfile(TH2D* correlation, TString savestring);


///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void TwoDHist_Mass_vs_Time(TString what = "SigBd", Bool_t prescaled = true, Double_t NNCut = -1.5){

// ***** Initialize ***** //
////////////////////////////

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

  // *** DataSet ***
  Int_t Xbins = 68;
  Double_t Xmin = Bmass_min;
  Double_t Xmax = Bmass_max;
  Int_t Ybins = 100;
  Double_t Ymin = -1;
  Double_t Ymax = 1;
  
  TH2D *correlation_LL = new TH2D("correlation_LL","Profile of X versus Y",Xbins,Xmin,Xmax,Ybins,Ymin,Ymax);
  TH2D *correlation_DD = new TH2D("correlation_DD","Profile of X versus Y",Xbins,Xmin,Xmax,Ybins,Ymin,Ymax);


  // ***** Loop over Entries: Apply Selection Cuts ***** //
  /////////////////////////////////////////////////////////
  
  // Initialise
  Double_t DOCA = 0;
  Double_t DOCA_min = 999;
  Int_t truePV = 0;
  Double_t Xvar = -999;
  Double_t Yvar = -999;
  
  bool TruthMatch = false;
  bool Trigger = false;
  Int_t count = 0;

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
    
    Trigger = ((PsiHlt1TrackMuonDecision_TOS || PsiHlt1DiMuonHighMassDecision_TOS || PsiHlt1TrackAllL0Decision_TOS) &&
         (PsiHlt2DiMuonDetachedJPsiDecision_TOS || PsiHlt2DiMuonJPsiHighPTDecision_TOS || PsiHlt2DiMuonJPsiDecision_TOS ||PsiHlt2TopoMu2BodyBBDTDecision_TOS));

    if(TruthMatch){ // Select only True Signal
        
      // Loop 1: Determine DOCA
      for(Int_t pv = 0; pv < nPV2 ; pv++){ 
        DOCA = TMath::Sqrt(pow(B_TRUEORIGINVERTEX_X-B_FullFit_PV_X[pv],2) + pow(B_TRUEORIGINVERTEX_Y-B_FullFit_PV_Y[pv],2) + pow(B_TRUEORIGINVERTEX_Z-B_FullFit_PV_Z[pv],2));
        if(DOCA<DOCA_min){
          DOCA_min = DOCA;
          truePV = pv;
        }
      }

      // Loop 2: Fill
      if(NNCut<-1. || (Trigger && ((piminus_TRACK_Type==3 && netOutput[truePV]>NNcut_LL) || (piminus_TRACK_Type==5 && netOutput[truePV]>NNcut_DD)))){

        Xvar = (Double_t)B_FullFit_M[truePV];
        Yvar = (Double_t)B_FullFit_ctau[truePV]*pow(10.,12)/(299792458*pow(10.,3)) - 1000*B_TRUETAU;
      
        if(Xvar>Xmin && Xvar<Xmax && Yvar>Ymin && Yvar<Ymax){
          if(piminus_TRACK_Type==3) correlation_LL->Fill(Xvar, Yvar);
          else if(piminus_TRACK_Type==5) correlation_DD->Fill(Xvar, Yvar);
          count++;
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
  std::cout << "Selected " << count << " events" << std::endl;

// ***** Part II: Histograms and Profiles ***** //
//////////////////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Part II: Histograms and Profiles ==" << std::endl;
  std::cout << "======================================" << std::endl;

  char buffer[3];
  TString Tail("");
  Int_t NNVal_LL = NNcut_LL*100;
  Int_t NNVal_DD = NNcut_DD*100;
  if(NNCut>-1){
    std::sprintf(buffer,"_NN%d+%d",NNVal_LL,NNVal_DD);
    Tail.Append(buffer);
  }
  else Tail.Append("_Loose");
  if(prescaled) Tail.Append("_Prescaled");

  FitPlotProfile(correlation_LL,what+"_LL"+Tail);
  FitPlotProfile(correlation_DD,what+"_DD"+Tail);
  
}


/////////////////////////////////
// ***** Helper Function ***** //
/////////////////////////////////
void FitPlotProfile(TH2D* correlation, TString savestring){

  TString Xaxis = "m_{J/#psi K_{S}^{0}} #scale[0.8]{(MeV/c^{2})}";
  TString Yaxis = "t_{reco} - t_{true} (ps)";
  Double_t Xmin = 5180;
  Double_t Xmax = 5520;
  Double_t Ymin = -1;
  Double_t Ymax = 1;
  Double_t Xmin_inner = 5255;
  Double_t Xmax_inner = 5305;
  Double_t Ymin_inner = -0.2;
  Double_t Ymax_inner = 0.2;
  
  
  // ***** Marginalise ***** //
  /////////////////////////////
  
  TCanvas *doek = new TCanvas("doek","Observable",900,800);
  doek->cd(1);
  
  TProfile *xfitProfile = (TProfile *)correlation->ProfileX("xfitProfile");
  TProfile *yfitProfile = (TProfile *)correlation->ProfileY("yfitProfile");

  TProfile *xProfile = (TProfile *)correlation->ProfileX("xProfile");
  TProfile *yProfile = (TProfile *)correlation->ProfileY("yProfile");
 
  // ***** Fit Profile ***** //
  /////////////////////////////
  
  TF1 *xFit = new TF1("xFit","[0]+[1]*(x-5180)",Xmin_inner,Xmax_inner);
  xFit->SetParName(0,"constant");
  xFit->SetParLimits(0,-0.5,0.5);  
  xFit->SetParName(1,"linear");
  xFit->SetParLimits(1,-0.01,0.01);
  std::cout << std::endl;
  std::cout << "Fit Results Profile Mass versus Time" << std::endl;
  xfitProfile->Fit("xFit","R"); 
/*  
  TF1 *xFullFit = new TF1("xFullFit","[0]+[1]*(x-5180)",Xmin,Xmax);
  xFullFit->SetParName(0,"constant");
  xFullFit->SetParLimits(0,-0.5,0.5);  
  xFullFit->SetParName(1,"linear");
  xFullFit->SetParLimits(1,-0.01,0.01);
  std::cout << std::endl;
  std::cout << "Full Fit Results Profile Mass versus Time" << std::endl;
  xfitProfile->Fit("xFullFit");
*/
  // Transform to TGraph
  Float_t xFit_xpoint[2];
  xFit_xpoint[0] = Xmin_inner;
  xFit_xpoint[1] = Xmax_inner;
  Float_t xFit_ypoint[2];
  xFit_ypoint[0] = xFit->GetParameter(0) + (xFit->GetParameter(1)) * (xFit_xpoint[0] - Xmin);
  xFit_ypoint[1] = xFit->GetParameter(0) + (xFit->GetParameter(1)) * (xFit_xpoint[1] - Xmin);
  
  TGraph *xGraph = new TGraph(2,xFit_xpoint,xFit_ypoint);
  xGraph->SetLineColor(4);
  xGraph->SetLineWidth(2);
/*  
  Float_t xFullFit_xpoint[2];
  xFullFit_xpoint[0] = Xmin;
  xFullFit_xpoint[1] = Xmax;
  Float_t xFullFit_ypoint[2];
  xFullFit_ypoint[0] = xFullFit->GetParameter(0) + (xFullFit->GetParameter(1)) * (xFullFit_xpoint[0] - Xmin);
  xFullFit_ypoint[1] = xFullFit->GetParameter(0) + (xFullFit->GetParameter(1)) * (xFullFit_xpoint[1] - Xmin);
  
  TGraph *xFullGraph = new TGraph(2,xFullFit_xpoint,xFullFit_ypoint);
  xFullGraph->SetLineColor(2);
  xFullGraph->SetLineWidth(2);
*/
  
  // *** Y Profile ***
  TF1 *yFit = new TF1("yFit","([0]+5279.58)+[1]*x",Ymin_inner,Ymax_inner);
  yFit->SetParName(0,"constant");
  yFit->SetParLimits(0,-10.,10.);  
  yFit->SetParName(1,"linear");
  yFit->SetParLimits(1,-100.,100.);
  std::cout << std::endl;
  std::cout << "Fit Results Profile Time versus Mass" << std::endl;
  yfitProfile->Fit("yFit","R");
/*  
  TF1 *yFullFit = new TF1("yFullFit","[0]*(x-[1])*(x-[2])*(x-[3])+5279.58",Ymin,Ymax);
  yFullFit->SetParName(0,"amplitude");
  yFullFit->SetParLimits(0,-100,100);  
  yFullFit->SetParName(1,"zero1");
  yFullFit->SetParLimits(1,-10.,-0.2);
  yFullFit->SetParName(2,"zero2");
  yFullFit->SetParLimits(2,-0.1,0.1);
  yFullFit->SetParName(3,"zero3");
  yFullFit->SetParLimits(3,0.2,10.);
  yFullFit->SetParameters(-5,-0.6,0,0.6);
  std::cout << std::endl;
  std::cout << "Full Fit Results Profile Time versus Mass" << std::endl;
  yfitProfile->Fit("yFullFit");
*/
  // Transform to TGraph
  Float_t yFit_xpoint[2];
  yFit_xpoint[0] = Ymin_inner;
  yFit_xpoint[1] = Ymax_inner;
  Float_t yFit_ypoint[2];
  yFit_ypoint[0] = (yFit->GetParameter(0) + 5279.58) + (yFit->GetParameter(1)) * yFit_xpoint[0];
  yFit_ypoint[1] = (yFit->GetParameter(0) + 5279.58) + (yFit->GetParameter(1)) * yFit_xpoint[1];
  
  TGraph *yGraph = new TGraph(2,yFit_xpoint,yFit_ypoint);
  yGraph->SetLineColor(4);
  yGraph->SetLineWidth(2);
/*  
  Float_t yFullFit_xpoint[100];
  Float_t yFullFit_ypoint[100];
  for(Int_t i=0; i<100; i++){
    yFullFit_xpoint[i] = Ymin + (Ymax-Ymin)*i/100;
    yFullFit_ypoint[i] = (yFullFit->GetParameter(0))*(yFullFit_xpoint[i]-yFullFit->GetParameter(1))*(yFullFit_xpoint[i]-yFullFit->GetParameter(2))*(yFullFit_xpoint[i]-yFullFit->GetParameter(3)) + 5279.58;
    if(i<5) std::cout << yFullFit_xpoint[i] << " " << yFullFit_ypoint[i] << std::endl;
  }
    
  TGraph *yFullGraph = new TGraph(100,yFullFit_xpoint,yFullFit_ypoint);
  yFullGraph->SetLineColor(2);
  yFullGraph->SetLineWidth(2);
*/

  // ***** TwoD Plot ***** //
  ///////////////////////////
  
  // Cosmetics
  correlation->GetXaxis()->SetTitle(Xaxis);
  correlation->GetXaxis()->SetTitleOffset(0.9);
  correlation->GetXaxis()->SetTitleSize(0.07);
  correlation->GetXaxis()->SetTitleFont(132);
  correlation->GetXaxis()->SetLabelSize(0.05);
  correlation->GetXaxis()->SetLabelFont(132);
  
  correlation->GetYaxis()->SetTitle(Yaxis);
  correlation->GetYaxis()->SetTitleOffset(0.8);
  correlation->GetYaxis()->SetTitleSize(0.07);
  correlation->GetYaxis()->SetTitleFont(132);
  correlation->GetYaxis()->SetLabelSize(0.05);
  correlation->GetYaxis()->SetLabelFont(132);
    
  correlation->GetYaxis()->SetRangeUser(Ymin,Ymax);
  correlation->SetMaximum(10000);
  correlation->SetMinimum(1);

  // *** Canvas ***
  //TCanvas *doek = new TCanvas("doek","Observable",900,800);
  doek->SetLeftMargin(0.12);
  doek->SetRightMargin(0.12);
  doek->SetBottomMargin(0.15);
  doek->cd(1);
  gPad->SetLogz(1);
  correlation->Draw("COLZ");
  
  // *** LHCb Tag *** 
  string convSave (savestring);
  size_t isBd=convSave.find("SigBd");
  size_t isBs=convSave.find("SigBs");
  size_t isLL=convSave.find("LL");
  size_t isDD=convSave.find("DD");
  
  TString track("");
  if(isLL!=string::npos) track = "Long K_{S}^{0}";
  else if(isDD!=string::npos) track = "Downstream K_{S}^{0}";
   
  TPaveText *lhcbTag = new TPaveText(0.60,0.72,0.89,0.89,"NDC");

  lhcbTag->SetFillColor(0);
  lhcbTag->SetTextAlign(32);
  lhcbTag->SetBorderSize(0);
  lhcbTag->SetTextSize(0.05);
  lhcbTag->SetTextFont(132);
  if(isBd!=string::npos) lhcbTag->AddText("#splitline{LHCb MC11a}{#splitline{#scale[0.7]{B_{d}^{0}#rightarrow J/#psi K_{S}^{0}}}{#scale[0.7]{"+track+"}}}");
  else if(isBs!=string::npos) lhcbTag->AddText("#splitline{LHCb MC11a}{#splitline{#scale[0.7]{B_{s}^{0}#rightarrow J/#psi K_{S}^{0}}}{#scale[0.7]{"+track+"}}}");

  lhcbTag -> Draw("");
  
  
  // ***** Plot X Profile ***** //
  ////////////////////////////////

  // Cosmetics  
  xProfile->GetXaxis()->SetTitle(Xaxis);
  xProfile->GetXaxis()->SetTitleOffset(0.9);
  xProfile->GetXaxis()->SetTitleSize(0.07);
  xProfile->GetXaxis()->SetTitleFont(132);
  xProfile->GetXaxis()->SetLabelSize(0.05);
  xProfile->GetXaxis()->SetLabelFont(132);
  
  xProfile->GetYaxis()->SetTitle(Yaxis);
  xProfile->GetYaxis()->SetTitleOffset(1.3);
  xProfile->GetYaxis()->SetTitleSize(0.07);
  xProfile->GetYaxis()->SetTitleFont(132);
  xProfile->GetYaxis()->SetLabelSize(0.05);
  xProfile->GetYaxis()->SetLabelFont(132);
    
  xProfile->GetYaxis()->SetRangeUser(-0.1,0.1);
  
  xProfile->SetMarkerStyle(22);
  xProfile->SetMarkerSize(1);
  
  // *** Canvas ***
  TCanvas *doek_X = new TCanvas("doek_X","Observable",900,800);
  doek_X->SetLeftMargin(0.20);
  doek_X->SetBottomMargin(0.15);
  doek_X->cd(1);
  gPad->SetTicks(1,1);
  xProfile->Draw("");
  //xFullGraph->Draw("same");
  xGraph->Draw("same");
  lhcbTag->Draw("");  
  
  // ***** Plot Y Profile ***** //
  ////////////////////////////////
  
  // Cosmetics  
  yProfile->GetXaxis()->SetTitle(Yaxis);
  yProfile->GetXaxis()->SetTitleOffset(0.9);
  yProfile->GetXaxis()->SetTitleSize(0.07);
  yProfile->GetXaxis()->SetTitleFont(132);
  yProfile->GetXaxis()->SetLabelSize(0.05);
  yProfile->GetXaxis()->SetLabelFont(132);
  
  yProfile->GetYaxis()->SetTitle(Xaxis);
  yProfile->GetYaxis()->SetTitleOffset(1.3);
  yProfile->GetYaxis()->SetTitleSize(0.07);
  yProfile->GetYaxis()->SetTitleFont(132);
  yProfile->GetYaxis()->SetLabelSize(0.05);
  yProfile->GetYaxis()->SetLabelFont(132);

  yProfile->GetYaxis()->SetRangeUser(5270,5290);
  
  yProfile->SetMarkerStyle(22);
  yProfile->SetMarkerSize(1);
  
  // *** Canvas ***
  TCanvas *doek_Y = new TCanvas("doek_Y","Observable",900,800);
  doek_Y->SetLeftMargin(0.20);
  doek_Y->SetBottomMargin(0.15);
  doek_Y->cd(1);
  gPad->SetTicks(1,1);
  yProfile->Draw("");
  //yFullGraph->Draw("same");
  yGraph->Draw("same");
  lhcbTag -> Draw("");
  
  // *** Save *** //
  //////////////////
  
  doek->SaveAs("Correlation_Mass_vs_Time_"+savestring+".pdf");
  doek_X->SaveAs("Profile_Mass_vs_Time_"+savestring+".pdf");
  doek_Y->SaveAs("Profile_Time_vs_Mass_"+savestring+".pdf");
  
  // *** Results *** //
  /////////////////////
  std::cout << std::endl;
  std::cout << "Mass versus Time --- Fit Model: c_0 + c_1 * (x - xmin)" << std::endl;
/*
  std::cout << "Range = [" << Xmin << "," << Xmax << "]" << std::endl;
  std::cout << "c_0 = " << xFullFit->GetParameter(0) << " +/- " << xFullFit->GetParError(0) << " ps (Sig: " << xFullFit->GetParameter(0)/xFullFit->GetParError(0) << " sigma)" << std::endl;
  std::cout << "c_1 = " << xFullFit->GetParameter(1) << " +/- " << xFullFit->GetParError(1) << " ps (Sig: " << xFullFit->GetParameter(1)/xFullFit->GetParError(1) << " sigma)" << std::endl;
  std::cout << "Spread in Time = c_1 * (xmax - xmin) = " << xFullFit->GetParameter(1)*(Xmax-Xmin) << " +/- " << xFullFit->GetParError(1)*(Xmax-Xmin) << " ps" << std::endl;
  std::cout << std::endl;
*/
  std::cout << "Range = [" << Xmin_inner << "," << Xmax_inner << "]" << std::endl;
  std::cout << "c_0 = " << xFit->GetParameter(0) << " +/- " << xFit->GetParError(0) << " ps (Sig: " << xFit->GetParameter(0)/xFit->GetParError(0) << " sigma)" << std::endl;
  std::cout << "c_1 = " << xFit->GetParameter(1) << " +/- " << xFit->GetParError(1) << " ps (Sig: " << xFit->GetParameter(1)/xFit->GetParError(1) << " sigma)" << std::endl;
  std::cout << "Spread in Time = c_1 * (xmax - xmin) = " << xFit->GetParameter(1)*(Xmax_inner-Xmin_inner) << " +/- " << xFit->GetParError(1)*(Xmax_inner-Xmin_inner) << " ps (Sig: " << xFit->GetParameter(1)/xFit->GetParError(1) << " sigma)" << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Time versus Mass --- Fit Model: (c_0 + 5279.58) + c_1 * x" << std::endl;
/*
  std::cout << "Range = [" << Ymin << "," << Ymax << "]" << std::endl;
  std::cout << "c_0 = " << yFullFit->GetParameter(0) << " +/- " << yFullFit->GetParError(0) << " MeV/c^{2}" << std::endl;
  std::cout << "c_1 = " << yFullFit->GetParameter(1) << " +/- " << yFullFit->GetParError(1) << " MeV/c^{2} (Sig: " << yFullFit->GetParameter(1)/yFullFit->GetParError(1) << " sigma)" << std::endl;
  std::cout << "Spread in Mass = c_1 * (xmax - xmin) = " << yFullFit->GetParameter(1)*(Ymax-Ymin) << " +/- " << yFullFit->GetParError(1)*(Ymax-Ymin) << " MeV/c^{2}" << std::endl;
  std::cout << std::endl;
*/
  std::cout << "Range = [" << Ymin_inner << "," << Ymax_inner << "]" << std::endl;
  std::cout << "c_0 = " << yFit->GetParameter(0) << " +/- " << yFit->GetParError(0) << " MeV/c^{2} (Sig: " << yFit->GetParameter(0)/yFit->GetParError(0) << " sigma)" << std::endl;
  std::cout << "c_1 = " << yFit->GetParameter(1) << " +/- " << yFit->GetParError(1) << " MeV/c^{2} (Sig: " << yFit->GetParameter(1)/yFit->GetParError(1) << " sigma)" << std::endl;
  std::cout << "Spread in Mass = c_1 * (xmax - xmin) = " << yFit->GetParameter(1)*(Ymax_inner-Ymin_inner) << " +/- " << yFit->GetParError(1)*(Ymax_inner-Ymin_inner) << " MeV/c^{2} (Sig: " << yFit->GetParameter(1)/yFit->GetParError(1) << " sigma)" << std::endl;
  std::cout << std::endl;
  
}

