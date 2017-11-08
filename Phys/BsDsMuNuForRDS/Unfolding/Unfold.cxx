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
#include "TSVDUnfold.h"
#endif

void Unfold()
{
   gROOT->Reset();
   gROOT->SetStyle("Plain");
   gStyle->SetOptStat(0);

   // --- Data/MC toy generation -----------------------------------

   // The MC inputs
   TFile *MCfile = new TFile("/afs/cern.ch/user/r/rvazquez/RDS/DaVinciDev_v41r3/Phys/BsDsMuNuForRDS/src/DsMass_WithSWeighted_Dsst_sigmu_CB.root");
   TTree *tMC = (TTree*)MCfile->Get("DecayTree");
   float entriesMC = tMC->GetEntries();
   Double_t  q2True, sigw, sqMC, sqData, Ds_PT, Emu, elcmTrue, EmuData;
   Float_t q2RegMC, q2RegData;
   Int_t gID, DsMomID, DsGMID, muMomID;
   Int_t gIDData, DsMomIDData, DsGMIDData, muMomIDData;
   TBranch *b_q2RegMC, *b_q2RegData, *b_q2True, *b_sigw, *b_sqMC, *b_sqData, *b_Ds_PT, *b_Emu, *b_elcmTrue, *b_EmuData;
   TBranch *b_gID, *b_DsMomID, *b_DsGMID, *b_muMomID;
   TBranch *b_gIDData, *b_DsMomIDData, *b_DsGMIDData, *b_muMomIDData;
   tMC->SetBranchAddress("q2Reg", &q2RegMC, &b_q2RegMC);
   tMC->SetBranchAddress("q2True", &q2True, &b_q2True);
   tMC->SetBranchAddress("Ds_PT", &Ds_PT, &b_Ds_PT);
   tMC->SetBranchAddress("sigw", &sigw, &b_sigw);
   tMC->SetBranchAddress("sq", &sqMC, &b_sqMC);
   tMC->SetBranchAddress("elcmTrue", &elcmTrue, &b_elcmTrue);
   tMC->SetBranchAddress("Emu", &Emu, &b_Emu);
   tMC->SetBranchAddress("gID", &gID, &b_gID);
   tMC->SetBranchAddress("DsMomID", &DsMomID, &b_DsMomID);
   tMC->SetBranchAddress("DsGMID", &DsGMID, &b_DsGMID);
   tMC->SetBranchAddress("muMomID", &muMomID, &b_muMomID);

   Int_t nbins = 11;
   Double_t max = 11000000.;
   TH1D *xini = new TH1D("xini", "MC truth", nbins, 0.0, max);
   TH1D *bini = new TH1D("bini", "MC reco", nbins, 0.0, max);
   TH2D *Adet = new TH2D("Adet", "detector response", nbins, 0.0, max, nbins, 0.0, max);

   // Data
   TFile *dfile = new TFile("/afs/cern.ch/user/r/rvazquez/RDS/DaVinciDev_v41r3/Phys/BsDsMuNuForRDS/src/DsMass_WithSWeighted_Dsst_sigmu_CB.root");
   TTree *tdata = (TTree*)dfile->Get("DecayTree");
   float entriesData = tdata->GetEntries();
   tdata->SetBranchAddress("q2Reg",&q2RegData,&b_q2RegData);
   tdata->SetBranchAddress("sq",&sqData,&b_sqData);
   tdata->SetBranchAddress("Emu",&EmuData,&b_EmuData);
   tdata->SetBranchAddress("gID", &gIDData, &b_gIDData);
   tdata->SetBranchAddress("DsMomID", &DsMomIDData, &b_DsMomIDData);
   tdata->SetBranchAddress("DsGMID", &DsGMIDData, &b_DsGMIDData);
   tdata->SetBranchAddress("muMomID", &muMomIDData, &b_muMomIDData); 

   TH1D *data = new TH1D("data", "data", nbins, 0.0, max);
   // Statistical covariance matrix
   TH2D *statcov = new TH2D("statcov", "covariance matrix", nbins, 0.0, max, nbins, 0.0, max);

   // Fill the MC 
   for (Int_t i= 0; i<entriesMC; i++) {
     tMC->GetEntry(i);
     if (sqMC>0 && abs(DsMomID)==433 && abs(muMomID)==531 && abs(DsGMID)==531 && abs(gID)==22){
       bini->Fill(q2RegMC);
       xini->Fill(q2True); 
       Adet->Fill(q2RegMC,q2True);
     }
   }
/*
   // Fill the data
   for (Int_t j = 0; j<entriesData; j++) {
     tdata->GetEntry(j); 
     if(sqData>0 && abs(DsMomIDData)==433 && abs(muMomIDData)==531 && abs(DsGMIDData)==531 && abs(gIDData)==22){
       data->Fill(q2RegData);
     }
   }
*/
   
   data->SetBinContent(1,1292.78);
   data->SetBinContent(2,1744.29);
   data->SetBinContent(3,2146.82);
   data->SetBinContent(4,2285.26);
   data->SetBinContent(5,2511.02);
   data->SetBinContent(6,2378.97);
   data->SetBinContent(7,2236.27);
   data->SetBinContent(8,1935.98);
   data->SetBinContent(9,1597.34);
   data->SetBinContent(10,1098.97);
   data->SetBinContent(11,330.117);

   cout << "Created toy distributions and errors for: " << endl;
   cout << "... \"true MC\"   and \"reconstructed (smeared) MC\"" << endl;
   cout << "... \"true data\" and \"reconstructed (smeared) data\"" << endl;
   cout << "... the \"detector response matrix\"" << endl;

   // Fill the data covariance matrix
   for (int k=1; k<=data->GetNbinsX(); k++) {
     statcov->SetBinContent(k,k,9*data->GetBinError(k)*data->GetBinError(k));
   }

   // --- Here starts the actual unfolding -------------------------

   // Create TSVDUnfold object and initialise
   TSVDUnfold *tsvdunf = new TSVDUnfold( data, statcov, bini, xini, Adet );

   // It is possible to normalise unfolded spectrum to unit area
   tsvdunf->SetNormalize( kFALSE ); // no normalisation here

   // Perform the unfolding with regularisation parameter kreg = 2
   // - the larger kreg, the finer grained the unfolding, but the more fluctuations occur
   // - the smaller kreg, the stronger is the regularisation and the bias
   int param = 5;
   TH1D* unfres = tsvdunf->Unfold( param );
   
   // Get the distribution of the d to cross check the regularization
   // - choose kreg to be the point where |d_i| stop being statistically significantly >>1
   TH1D* ddist = tsvdunf->GetD();

   // Get the distribution of the singular values
   TH1D* svdist = tsvdunf->GetSV();

   // Compute the error matrix for the unfolded spectrum using toy MC
   // using the measured covariance matrix as input to generate the toys
   // 100 toys should usually be enough
   // The same method can be used for different covariance matrices separately.
   TH2D* ustatcov = tsvdunf->GetUnfoldCovMatrix( statcov, 100 );

   // Now compute the error matrix on the unfolded distribution originating
   // from the finite detector matrix statistics
   TH2D* uadetcov = tsvdunf->GetAdetCovMatrix( 100 );

   // Sum up the two (they are uncorrelated)
   ustatcov->Add( uadetcov );

   //Get the computed regularized covariance matrix (always corresponding to total uncertainty passed in constructor) and add uncertainties from finite MC statistics.
   TH2D* utaucov = tsvdunf->GetXtau();
   utaucov->Add( uadetcov );

   //Get the computed inverse of the covariance matrix
   TH2D* uinvcov = tsvdunf->GetXinv();


   // --- Only plotting stuff below ------------------------------

   for (int i=1; i<=unfres->GetNbinsX(); i++) {
     cout << unfres->GetBinContent(i) << " +/- "<< TMath::Sqrt(utaucov->GetBinContent(i,i)) << ". " << (xini->GetBinContent(i))*data->Integral()/xini->Integral() << endl;  
     
     unfres->SetBinError(i, TMath::Sqrt(utaucov->GetBinContent(i,i)));
   }

   // Renormalize just to be able to plot on the same scale
   xini->Scale(data->Integral()/xini->Integral());

   TLegend *leg = new TLegend(0.58,0.68,0.99,0.88);
   leg->SetBorderSize(0);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->AddEntry(unfres,"Unfolded Data","p");
   leg->AddEntry(data,"Reconstructed Data","l");
   leg->AddEntry(xini,"True MC","l");

   TCanvas *c1 = new TCanvas( "c1", "Unfolding toy example with TSVDUnfold", 900, 800 );

   // --- Style settings -----------------------------------------
   Int_t c_Canvas    = TColor::GetColor( "#f0f0f0" );
   Int_t c_FrameFill = TColor::GetColor( "#fffffd" );
   Int_t c_TitleBox  = TColor::GetColor( "#6D7B8D" );
   Int_t c_TitleText = TColor::GetColor( "#FFFFFF" );

   c1->SetFrameFillColor( c_FrameFill );
   c1->SetFillColor     ( c_Canvas    );
   c1->Divide(1,2);
   TVirtualPad * c11 = c1->cd(1);
   c11->SetFrameFillColor( c_FrameFill );
   c11->SetFillColor     ( c_Canvas    );

   gStyle->SetTitleFillColor( c_TitleBox  );
   gStyle->SetTitleTextColor( c_TitleText );
   gStyle->SetTitleBorderSize( 1 );
   gStyle->SetTitleH( 0.052 );
   gStyle->SetTitleX( c1->GetLeftMargin() );
   gStyle->SetTitleY( 1 - c1->GetTopMargin() + gStyle->GetTitleH() );
   gStyle->SetTitleW( 1 - c1->GetLeftMargin() - c1->GetRightMargin() );

   TH1D* frame = new TH1D( *unfres );
   frame->SetTitle( "Unfolding toy example with TSVDUnfold" );
   frame->GetXaxis()->SetTitle( "q^{2} [MeV^{2}]" );
   frame->GetYaxis()->SetTitle( "Events" );
   frame->GetXaxis()->SetTitleOffset( 1.25 );
   frame->GetYaxis()->SetTitleOffset( 1.29 );
   frame->Draw();

   data->SetLineStyle(2);
   data->SetLineColor(4);
   data->SetLineWidth(2);
   unfres->SetMarkerStyle(20);
   xini->SetLineStyle(2);
   xini->SetLineColor(8);
   xini->SetLineWidth(2);
   // ------------------------------------------------------------

   // add histograms
   unfres->Draw("same");
   data->Draw("same");
   xini->Draw("same");

   leg->Draw();

   // covariance matrix
   gStyle->SetPalette(1,0);
   TVirtualPad * c12 = c1->cd(2);
   c12->Divide(2,1);
   TVirtualPad * c2 = c12->cd(1);
   c2->SetFrameFillColor( c_FrameFill );
   c2->SetFillColor     ( c_Canvas    );
   c2->SetRightMargin   ( 0.15         );

   TH2D* covframe = new TH2D( *ustatcov );
   covframe->SetTitle( "TSVDUnfold covariance matrix" );
   covframe->GetXaxis()->SetTitle( "q^{2}" );
   covframe->GetYaxis()->SetTitle( "q^{2}" );
   covframe->GetXaxis()->SetTitleOffset( 1.25 );
   covframe->GetYaxis()->SetTitleOffset( 1.29 );
   covframe->Draw();

   ustatcov->SetLineWidth( 2 );
   ustatcov->Draw( "colzsame" );

   // distribution of the d quantity
   TVirtualPad * c3 = c12->cd(2);
   c3->SetFrameFillColor( c_FrameFill );
   c3->SetFillColor     ( c_Canvas    );
   c3->SetLogy();

   TLine *line = new TLine( 0.,1.,40.,1. );
   line->SetLineStyle(2);

   TH1D* dframe = new TH1D( *ddist );
   dframe->SetTitle( "TSVDUnfold |d_{i}|" );
   dframe->GetXaxis()->SetTitle( "i" );
   dframe->GetYaxis()->SetTitle( "|d_{i}|" );
   dframe->GetXaxis()->SetTitleOffset( 1.25 );
   dframe->GetYaxis()->SetTitleOffset( 1.29 );
   dframe->SetMinimum( 0.001 );
   dframe->Draw();

   ddist->SetLineWidth( 2 );
   ddist->Draw( "same" );
   line->Draw();

   c1->SaveAs("unfolding_FF_6.pdf");
}
