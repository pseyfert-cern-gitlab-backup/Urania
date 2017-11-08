#include <iostream>

#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TRandom3.h"
#include "TString.h"
#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TLine.h"
#include "TChain.h"
#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TUnfoldDensity.h"
#endif

void UnfoldDensityNew()
{

  // switch on histogram errors
  TH1::SetDefaultSumw2();
  // show fit result
  gStyle->SetOptFit(1111);
  //========================
  // Step 1: define binning, book histograms
  // reconstructed pt (fine binning)
  Int_t const nDet=24;
  Double_t const xminDet=0.0;
  Double_t const xmaxDet=11.0;
  // generated pt (coarse binning)
  Int_t const nGen=10;
  Double_t const xminGen= 0.0;
  Double_t const xmaxGen=11.0; 

  // (1) create histograms required for unfolding
  TH1D *histUnfoldInput = new TH1D("unfolding input rec",";q2Reg",nDet,xminDet,xmaxDet);
  TH2D *histUnfoldMatrix = new TH2D("unfolding matrix",";q2True;q2Reg",nGen,xminGen,xmaxGen,nDet,xminDet,xmaxDet);

  // (3) control histograms
  TH1D *histDataTruth = new TH1D("DATA truth gen",";q2True",nGen,xminGen,xmaxGen);
  TH1D *histDetMC = new TH1D("MC prediction rec",";q2Reg",nDet,xminDet,xmaxDet);


   gROOT->Reset();
   gROOT->SetStyle("Plain");

   // --- Data/MC toy generation -----------------------------------

   // The MC inputs
   TFile *MCfile = new TFile("/afs/cern.ch/user/r/rvazquez/RDS/DaVinciDev_v41r3/Phys/BsDsMuNuForRDS/src/DsMass_WithSWeighted_Dsst_sigmu_CB.root");
   TTree *tMC = (TTree*)MCfile->Get("DecayTree");
   float entriesMC = tMC->GetEntries();
   Double_t  q2True, sigw, sqMC, sqData;
   Float_t q2RegMC, q2RegData;
   Int_t gID, DsMomID, DsGMID, muMomID;
   Int_t gIDData, DsMomIDData, DsGMIDData, muMomIDData;
   TBranch *b_q2RegMC, *b_q2RegData, *b_q2True, *b_sigw, *b_sqMC, *b_sqData;
   TBranch *b_gID, *b_DsMomID, *b_DsGMID, *b_muMomID;
   TBranch *b_gIDData, *b_DsMomIDData, *b_DsGMIDData, *b_muMomIDData;
   tMC->SetBranchAddress("q2Reg", &q2RegMC, &b_q2RegMC);
   tMC->SetBranchAddress("q2True", &q2True, &b_q2True);
   tMC->SetBranchAddress("sigw", &sigw, &b_sigw);
   tMC->SetBranchAddress("sq", &sqMC, &b_sqMC);
   tMC->SetBranchAddress("gID", &gID, &b_gID);
   tMC->SetBranchAddress("DsMomID", &DsMomID, &b_DsMomID);
   tMC->SetBranchAddress("DsGMID", &DsGMID, &b_DsGMID);
   tMC->SetBranchAddress("muMomID", &muMomID, &b_muMomID);   


   // Data
   TFile *dfile = new TFile("/afs/cern.ch/user/r/rvazquez/RDS/DaVinciDev_v41r3/Phys/BsDsMuNuForRDS/src/DsMass_WithSWeighted_Dsst_sigmu_CB.root");
   TTree *tdata = (TTree*)dfile->Get("DecayTree");
   float entriesData = tdata->GetEntries();
   tdata->SetBranchAddress("q2Reg",&q2RegData,&b_q2RegData);
   tdata->SetBranchAddress("sq",&sqData,&b_sqData);
   tdata->SetBranchAddress("gID", &gIDData, &b_gIDData);
   tdata->SetBranchAddress("DsMomID", &DsMomIDData, &b_DsMomIDData);
   tdata->SetBranchAddress("DsGMID", &DsGMIDData, &b_DsGMIDData);
   tdata->SetBranchAddress("muMomID", &muMomIDData, &b_muMomIDData);

   // Fill the MC 
   for (Int_t i= 0; i<entriesMC; i++) {
     tMC->GetEntry(i);
     if (sqMC>0 && abs(DsMomID)==433 && abs(muMomID)==531 && abs(DsGMID)==531 && abs(gID)==22){
       histDataTruth->Fill(q2True/1000000.);     
       histUnfoldMatrix->Fill(q2True/1000000.,q2RegMC/1000000.);
       histDetMC ->Fill(q2RegMC/1000000.);
     }
   }

   // Fill the data
   for (Int_t j = 0; j<entriesData; j++) {
     tdata->GetEntry(j); 
     if(sqData>0 && abs(DsMomIDData)==433 && abs(muMomIDData)==531 && abs(DsGMIDData)==531 && abs(gIDData)==22){
       histUnfoldInput->Fill(q2RegData/1000000.);
     }
   }
   TCanvas *c= new TCanvas();
   histUnfoldInput->Draw();
   c->SaveAs("test.pdf");

  // this method is new in version 16 of TUnfold
  cout<<"TUnfold version is "<<TUnfold::GetTUnfoldVersion()<<"\n";

  //========================
  // Step 5: unfolding
  //
  // here one has to decide about the regularisation scheme
  // regularize curvature
  TUnfold::ERegMode regMode = TUnfold::kRegModeCurvature;
 // preserve the area
  TUnfold::EConstraint constraintMode = TUnfold::kEConstraintArea;
  // bin content is divided by the bin width
  TUnfoldDensity::EDensityMode densityFlags = TUnfoldDensity::kDensityModeBinWidth;
  // set up matrix of migrations
  TUnfoldDensity unfold(histUnfoldMatrix,TUnfold::kHistMapOutputHoriz,
                        regMode,constraintMode,densityFlags);
  // define the input vector (the measured data distribution)
  unfold.SetInput(histUnfoldInput);
  // run the unfolding
  Int_t nScan=30;
  TSpline *logTauX,*logTauY;
  TGraph *lCurve;
  // this method scans the parameter tau and finds the kink in the L curve
  // finally, the unfolding is done for the best choice of tau
  Int_t iBest=unfold.ScanLcurve(nScan,0.,0.,&lCurve,&logTauX,&logTauY);
  cout<<"chi**2="<<unfold.GetChi2A()<<"+"<<unfold.GetChi2L()<<" / "<<unfold.GetNdf()<<"\n";
  // save graphs with one point to visualize best choice of tau
  Double_t t[1],x[1],y[1];
  logTauX->GetKnot(iBest,t[0],x[0]);
  logTauY->GetKnot(iBest,t[0],y[0]);
  TGraph *bestLcurve=new TGraph(1,x,y);
  TGraph *bestLogTauLogChi2=new TGraph(1,t,x);
  //===========================
  // Step 6: retreive unfolding results
  // get unfolding output
  // includes the statistical and background errors
  // but not the other systematic uncertainties
  TH1 *histUnfoldOutput=unfold.GetOutput("PT(unfold,stat+bgrerr)");
  // retreive error matrix of statistical errors
  TH2 *histEmatStat=unfold.GetEmatrixInput("unfolding stat error matrix");
  // retreive full error matrix
  // This includes all systematic errors
  TH2 *histEmatTotal=unfold.GetEmatrixTotal("unfolding total error matrix");
  // create two copies of the unfolded data, one with statistical errors
  // the other with total errors
  TH1 *histUnfoldStat=new TH1D("PT(unfold,staterr)",";q2True",nGen,xminGen,xmaxGen);
  TH1 *histUnfoldTotal=new TH1D("PT(unfold,totalerr)",";q2True",nGen,xminGen,xmaxGen);
  for(Int_t i=0;i<nGen+2;i++) {
     Double_t c=histUnfoldOutput->GetBinContent(i);
     // histogram with unfolded data and stat errors
     histUnfoldStat->SetBinContent(i,c);
     histUnfoldStat->SetBinError(i,TMath::Sqrt(histEmatStat->GetBinContent(i,i)));
     // histogram with unfolded data and total errors
     histUnfoldTotal->SetBinContent(i,c);
     histUnfoldTotal->SetBinError(i,TMath::Sqrt(histEmatTotal->GetBinContent(i,i)));
  }
  // create histogram with correlation matrix
  TH2D *histCorr=new TH2D("Corr(total)",";q2True;q2Reg",nGen,xminGen,xmaxGen,nGen,xminGen,xmaxGen);
  for(Int_t i=0;i<nGen+2;i++) {
     Double_t ei,ej;
     ei=TMath::Sqrt(histEmatTotal->GetBinContent(i,i));
     if(ei<=0.0) continue;
     for(Int_t j=0;j<nGen+2;j++) {
        ej=TMath::Sqrt(histEmatTotal->GetBinContent(j,j));
        if(ej<=0.0) continue;
        histCorr->SetBinContent(i,j,histEmatTotal->GetBinContent(i,j)/ei/ej);
     }
  }
  // retreive bgr source 1
  //========================
  // Step 7: plots
  TCanvas *output = new TCanvas();
  output->Divide(3,2);
  output->cd(1);
  // data, MC prediction, background
  histUnfoldInput->SetMinimum(0.0);
  histUnfoldInput->Draw("E");
  histDetMC->SetMinimum(0.0);
  histDetMC->SetLineColor(kBlue);
  histDetMC->Draw("SAME HIST");
  output->cd(2);
  // unfolded data, data truth, MC truth
  histUnfoldTotal->SetMinimum(0.0);
  histUnfoldTotal->SetMaximum(histUnfoldTotal->GetMaximum()*1.5);
  // outer error: total error
  histUnfoldTotal->Draw("E");
  // middle error: stat+bgr
  histUnfoldOutput->Draw("SAME E1");
  // inner error: stat only
  histUnfoldStat->Draw("SAME E1");
  histDataTruth->Draw("SAME HIST");
  output->cd(3);
  // unfolding matrix
  histUnfoldMatrix->SetLineColor(kBlue);
  histUnfoldMatrix->Draw("BOX");
  // show tau as a function of chi**2
  output->cd(4);
  logTauX->Draw();
  bestLogTauLogChi2->SetMarkerColor(kRed);
  bestLogTauLogChi2->Draw("*");
  // show the L curve
  output->cd(5);
  lCurve->Draw("AL");
  bestLcurve->SetMarkerColor(kRed);
  bestLcurve->Draw("*");
  // show correlation matrix
  output->cd(6);
  histCorr->Draw("BOX");
}  
