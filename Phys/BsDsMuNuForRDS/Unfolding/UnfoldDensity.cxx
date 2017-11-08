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

void UnfoldDensity()
{
   
   #define nbinsFine 11
   #define nbinsCoarse 5
  
   gROOT->Reset();
   gROOT->SetStyle("Plain");
   gStyle->SetOptStat(0);

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

   // Define the binning scheme
   Double_t q2BinsFine[nbinsFine+1]= {0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0};
   Double_t q2BinsCoarse[nbinsCoarse+1]= {0.0,2.0,4.0,6.0,8.0,11.0};
   TUnfoldBinning *detectorBinning = new TUnfoldBinning("detector");
   TUnfoldBinning *detectorDistribution = detectorBinning->AddBinning("detectordistribution");
   detectorDistribution->AddAxis("q2",nbinsFine,q2BinsFine,
                                 false, // no underflow bin (not reconstructed)
                                 false // overflow bin
                                );
   
   detectorBinning->PrintStream(cout);
   // generator level binning
   TUnfoldBinning *generatorBinning=new TUnfoldBinning("generator");
   // signal distribution is measured with coarse binning
   // underflow and overflow bins are needed to take care of
   // what happens outside the phase-space
   TUnfoldBinning *signalBinning = generatorBinning->AddBinning("signal");
   signalBinning->AddAxis("q2gen",nbinsCoarse,q2BinsCoarse,
                          false, // underflow bin
                          false // overflow bin
                          );

   // get the distributions
   TH1 *histDataReco=detectorBinning->CreateHistogram("histDataReco");
   TH1 *histDataTruth=generatorBinning->CreateHistogram("histDataTruth");
   TH2 *histMCGenRec = TUnfoldBinning::CreateHistogramOfMigrations(generatorBinning,detectorBinning,"histMCGenRec");

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

   TH1 *data = detectorBinning->CreateHistogram("histData");

   // Fill the MC 
   for (Int_t i= 0; i<entriesMC; i++) {
     tMC->GetEntry(i);
     if (sqMC>0 && abs(DsMomID)==433 && abs(muMomID)==531 && abs(DsGMID)==531 && abs(gID)==22){
       histDataReco->Fill(q2RegMC/1000000.);
       histDataTruth->Fill(q2True/1000000.); 
       histMCGenRec->Fill(q2True/1000000.,q2RegMC/1000000.);
     }
   }

   // Fill the data
   for (Int_t j = 0; j<entriesData; j++) {
     tdata->GetEntry(j); 
     if(sqData>0 && abs(DsMomIDData)==433 && abs(muMomIDData)==531 && abs(DsGMIDData)==531 && abs(gIDData)==22){
       data->Fill(q2RegData/1000000.);
     }
   }

   cout << "Created toy distributions and errors for: " << endl;
   cout << "... \"true MC\"   and \"reconstructed (smeared) MC\"" << endl;
   cout << "... \"true data\" and \"reconstructed (smeared) data\"" << endl;
   cout << "... the \"detector response matrix\"" << endl;

   // --- Here starts the actual unfolding -------------------------
   
   // detailed steering for regularisation
   const char *REGULARISATION_DISTRIBUTION=0;
   const char *REGULARISATION_AXISSTEERING="*[B]";
   TUnfoldDensity unfold(histMCGenRec, TUnfold::kHistMapOutputHoriz,
       TUnfold::kRegModeCurvature, TUnfold::kEConstraintArea,
       TUnfoldDensity::kDensityModeBinWidth, 
       generatorBinning,detectorBinning,
       REGULARISATION_DISTRIBUTION,
       REGULARISATION_AXISSTEERING  
      );

   // define the input vector (the measured data distribution)
   unfold.SetInput(histDataReco /* ,0.0,1.0 */);
   cout << "Set the data to unfold" << endl;

     // print matrix of regularisation conditions
#ifdef PRINT_MATRIX_L
  TH2 *histL= unfold.GetL("L");
  for(Int_t j=1;j<=histL->GetNbinsY();j++) {
     cout<<"L["<<unfold.GetLBinning()->GetBinName(j)<<"]";
     for(Int_t i=1;i<=histL->GetNbinsX();i++) {
        Double_t c=histL->GetBinContent(i,j);
        if(c!=0.0) cout<<" ["<<i<<"]="<<c;
     }
     cout<<"\n";
  }
#endif
  // run the unfolding
  //
  // here, tau is determined by scanning the global correlation coefficients
  Int_t nScan=100;
  TSpline *rhoLogTau=0;
  TGraph *lCurve=0;
  // for determining tau, scan the correlation coefficients
  // correlation coefficients may be probed for all distributions
  // or only for selected distributions
  // underflow/overflow bins may be included/excluded
  //
  const char *SCAN_DISTRIBUTION="signal";
  const char *SCAN_AXISSTEERING=0;
  Int_t iBest=unfold.ScanTau(nScan,0.,0.,&rhoLogTau,
                             TUnfoldDensity::kEScanTauRhoMax,
                             SCAN_DISTRIBUTION,SCAN_AXISSTEERING,
                             &lCurve);
  // create graphs with one point to visualize best choice of tau
  Double_t t[1],rho[1],x[1],y[1];
  rhoLogTau->GetKnot(iBest,t[0],rho[0]);
  lCurve->GetPoint(iBest,x[0],y[0]);
  TGraph *bestRhoLogTau=new TGraph(1,t,rho);
  TGraph *bestLCurve=new TGraph(1,x,y);
  Double_t *tAll=new Double_t[nScan],*rhoAll=new Double_t[nScan];
  for(Int_t i=0;i<nScan;i++) {
     rhoLogTau->GetKnot(i,tAll[i],rhoAll[i]);
  }
  TGraph *knots=new TGraph(nScan,tAll,rhoAll);
  cout<<"chi**2="<<unfold.GetChi2A()<<"+"<<unfold.GetChi2L() <<" / "<<unfold.GetNdf()<<"\n";
  //===========================
  // Step 4: retreive and plot unfolding results
  // get unfolding output
  TH1 *histDataUnfold=unfold.GetOutput("unfolded signal",0,0,0,kFALSE);
  // get MOnte Carlo reconstructed data
  TH1 *histMCReco=histMCGenRec->ProjectionY("histMCReco",0,-1,"e");
  TH1 *histMCTruth=histMCGenRec->ProjectionX("histMCTruth",0,-1,"e");
  Double_t scaleFactor=histDataTruth->GetSumOfWeights()/histMCTruth->GetSumOfWeights();
  histMCReco->Scale(scaleFactor);
  histMCTruth->Scale(scaleFactor);
  // get matrix of probabilities
  //TH2 *histProbability=unfold.GetProbabilityMatrix("histProbability");
  // get global correlation coefficients
  TH1 *histGlobalCorr=unfold.GetRhoItotal("histGlobalCorr",0,0,0,kFALSE);
  TH1 *histGlobalCorrScan=unfold.GetRhoItotal("histGlobalCorrScan",0,SCAN_DISTRIBUTION,SCAN_AXISSTEERING,kFALSE);
  TH2 *histCorrCoeff=unfold.GetRhoIJtotal("histCorrCoeff",0,0,0,kFALSE);
  TCanvas *canvas = new TCanvas();
  canvas->Print("testUnfold5.pdf[");
  //========== page 1 ============
  // unfolding control plots
  // input, matrix, output
  // tau-scan, global correlations, correlation coefficients
  canvas->Clear();
  canvas->Divide(3,2);
  // (1) all bins, compare to original MC distribution
  canvas->cd(1);
  histDataReco->SetMinimum(0.0);
  histDataReco->Draw("E");
  histMCReco->SetLineColor(kBlue);
  histMCReco->Draw("SAME HIST");
  // (2) matrix of probabilities
  canvas->cd(2);
  //histProbability->Draw("BOX");
  // (3) unfolded data, data truth, MC truth
  canvas->cd(3);
  gPad->SetLogy();
  histDataUnfold->Draw("E");
  histDataTruth->SetLineColor(kBlue);
  histDataTruth->Draw("SAME HIST");
  histMCTruth->SetLineColor(kRed);
  histMCTruth->Draw("SAME HIST");
  // (4) scan of correlation vs tau
  canvas->cd(4);
  rhoLogTau->Draw();
  knots->Draw("*");
  bestRhoLogTau->SetMarkerColor(kRed);
  bestRhoLogTau->Draw("*");
  // (5) global correlation coefficients for the distributions
  //     used during the scan
  canvas->cd(5);
  //histCorrCoeff->Draw("BOX");
  histGlobalCorrScan->Draw("HIST");
  // (6) L-curve
  canvas->cd(6);
  lCurve->Draw("AL");
  bestLCurve->SetMarkerColor(kRed);
  bestLCurve->Draw("*");
  canvas->Print("testUnfold5.pdf");
  canvas->Print("testUnfold5.pdf]");






}
