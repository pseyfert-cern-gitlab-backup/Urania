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
#endif

void CheckPhotonIDForUnfolding()
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
   Double_t Bs_0_MCORR;
   TBranch *b_q2RegMC, *b_q2RegData, *b_q2True, *b_sigw, *b_sqMC, *b_sqData, *b_Ds_PT, *b_Emu, *b_elcmTrue, *b_EmuData;
   TBranch *b_gID, *b_DsMomID, *b_DsGMID, *b_muMomID;
   TBranch *b_gIDData, *b_DsMomIDData, *b_DsGMIDData, *b_muMomIDData;
   TBranch *b_Bs_0_MCORR;
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
   tMC->SetBranchAddress("Bs_0_MCORR", &Bs_0_MCORR, &b_Bs_0_MCORR);

   Int_t nbins = 20;
   Double_t max = 5400.;
   Double_t min = 3000.;
   TH1D *histoMassFullID_bin1 = new TH1D("histoMassFullID_bin1", "MC truth full ID bin1", nbins, min, max);
   TH1D *histoMassFullID_bin2 = new TH1D("histoMassFullID_bin2", "MC truth full ID bin2", nbins, min, max);
   TH1D *histoMassFullID_bin3 = new TH1D("histoMassFullID_bin3", "MC truth full ID bin3", nbins, min, max);
   TH1D *histoMassFullID_bin4 = new TH1D("histoMassFullID_bin4", "MC truth full ID bin4", nbins, min, max);
   TH1D *histoMassFullID_bin5 = new TH1D("histoMassFullID_bin5", "MC truth full ID bin5", nbins, min, max);
   TH1D *histoMassFullID_bin6 = new TH1D("histoMassFullID_bin6", "MC truth full ID bin6", nbins, min, max); 
   TH1D *histoMassID_bin1 = new TH1D("histoMassID_bin1", "MC truth ID bin1", nbins, min, max);
   TH1D *histoMassID_bin2 = new TH1D("histoMassID_bin2", "MC truth ID bin2", nbins, min, max);
   TH1D *histoMassID_bin3 = new TH1D("histoMassID_bin3", "MC truth ID bin3", nbins, min, max);
   TH1D *histoMassID_bin4 = new TH1D("histoMassID_bin4", "MC truth ID bin4", nbins, min, max);
   TH1D *histoMassID_bin5 = new TH1D("histoMassID_bin5", "MC truth ID bin5", nbins, min, max);
   TH1D *histoMassID_bin6 = new TH1D("histoMassID_bin6", "MC truth ID bin6", nbins, min, max);
   TH1D *histoMass_bin1 = new TH1D("histoMass_bin1", "MC truth bin1", nbins, min, max);
   TH1D *histoMass_bin2 = new TH1D("histoMass_bin2", "MC truth bin2", nbins, min, max);
   TH1D *histoMass_bin3 = new TH1D("histoMass_bin3", "MC truth bin3", nbins, min, max);
   TH1D *histoMass_bin4 = new TH1D("histoMass_bin4", "MC truth bin4", nbins, min, max);
   TH1D *histoMass_bin5 = new TH1D("histoMass_bin5", "MC truth bin5", nbins, min, max);
   TH1D *histoMass_bin6 = new TH1D("histoMass_bin6", "MC truth bin6", nbins, min, max); 

   // Fill the MC 
   for (Int_t i= 0; i<entriesMC; i++) {
     tMC->GetEntry(i);
     if (sqMC>0){
       if (q2RegMC/1000000.<2.) histoMass_bin1->Fill(Bs_0_MCORR);
       if (q2RegMC/1000000.<4. && q2RegMC/1000000.>2.0) histoMass_bin2->Fill(Bs_0_MCORR);
       if (q2RegMC/1000000.<6. && q2RegMC/1000000.>4.0) histoMass_bin3->Fill(Bs_0_MCORR);
       if (q2RegMC/1000000.<8. && q2RegMC/1000000.>6.0) histoMass_bin4->Fill(Bs_0_MCORR);
       if (q2RegMC/1000000.<10. && q2RegMC/1000000.>8.0) histoMass_bin5->Fill(Bs_0_MCORR);
       if (q2RegMC/1000000.<12. && q2RegMC/1000000.>10.0) histoMass_bin6->Fill(Bs_0_MCORR);      
     }
     if (sqMC>0 && abs(DsMomID)==433 && abs(muMomID)==531 && abs(DsGMID)==531 && abs(gID)==22){
       if (q2RegMC/1000000.<2.) histoMassFullID_bin1->Fill(Bs_0_MCORR);
       if (q2RegMC/1000000.<4. && q2RegMC/1000000.>2.0) histoMassFullID_bin2->Fill(Bs_0_MCORR);
       if (q2RegMC/1000000.<6. && q2RegMC/1000000.>4.0) histoMassFullID_bin3->Fill(Bs_0_MCORR);
       if (q2RegMC/1000000.<8. && q2RegMC/1000000.>6.0) histoMassFullID_bin4->Fill(Bs_0_MCORR);
       if (q2RegMC/1000000.<10. && q2RegMC/1000000.>8.0) histoMassFullID_bin5->Fill(Bs_0_MCORR);
       if (q2RegMC/1000000.<12. && q2RegMC/1000000.>10.0) histoMassFullID_bin6->Fill(Bs_0_MCORR);
     }
     if (sqMC>0 && abs(DsMomID)==433 && abs(muMomID)==531 && abs(DsGMID)==531){
       if (q2RegMC/1000000.<2.) histoMassID_bin1->Fill(Bs_0_MCORR);
       if (q2RegMC/1000000.<4. && q2RegMC/1000000.>2.0) histoMassID_bin2->Fill(Bs_0_MCORR);
       if (q2RegMC/1000000.<6. && q2RegMC/1000000.>4.0) histoMassID_bin3->Fill(Bs_0_MCORR);
       if (q2RegMC/1000000.<8. && q2RegMC/1000000.>6.0) histoMassID_bin4->Fill(Bs_0_MCORR);
       if (q2RegMC/1000000.<10. && q2RegMC/1000000.>8.0) histoMassID_bin5->Fill(Bs_0_MCORR);
       if (q2RegMC/1000000.<12. && q2RegMC/1000000.>10.0) histoMassID_bin6->Fill(Bs_0_MCORR);
     }
   }

   TCanvas *c1 = new TCanvas();
   TLegend *l1 = new TLegend(0.1,0.7,0.3,0.9);
   histoMassID_bin1->DrawNormalized();
   histoMass_bin1->SetLineColor(2);  
   histoMassFullID_bin1->SetLineColor(3);
   histoMass_bin1->DrawNormalized("same"); 
   histoMassFullID_bin1->DrawNormalized("same");
   l1->AddEntry(histoMass_bin1,"no ID","l");
   l1->AddEntry(histoMassID_bin1,"Ds + mu ID","l");
   l1->AddEntry(histoMassFullID_bin1,"Ds + g + mu ID","l");
   l1->Draw();
   c1->SaveAs("q2_bin1.pdf");

   TCanvas *c2 = new TCanvas();
   TLegend *l2 = new TLegend(0.1,0.7,0.3,0.9);
   histoMassID_bin2->DrawNormalized();
   histoMass_bin2->SetLineColor(2);
   histoMassFullID_bin2->SetLineColor(3);
   histoMass_bin2->DrawNormalized("same");
   histoMassFullID_bin2->DrawNormalized("same");
   l2->AddEntry(histoMass_bin1,"no ID","l");
   l2->AddEntry(histoMassID_bin1,"Ds + mu ID","l");
   l2->AddEntry(histoMassFullID_bin1,"Ds + g + mu ID","l");
   l2->Draw();
   c2->SaveAs("q2_bin2.pdf");

   TCanvas *c3 = new TCanvas();
   TLegend *l3 = new TLegend(0.1,0.7,0.3,0.9);
   histoMassID_bin3->DrawNormalized();
   histoMass_bin3->SetLineColor(2);
   histoMassFullID_bin3->SetLineColor(3);
   histoMass_bin3->DrawNormalized("same");
   histoMassFullID_bin3->DrawNormalized("same");
   l3->AddEntry(histoMass_bin1,"no ID","l");
   l3->AddEntry(histoMassID_bin1,"Ds + mu ID","l");
   l3->AddEntry(histoMassFullID_bin1,"Ds + g + mu ID","l");
   l3->Draw();
   c3->SaveAs("q2_bin3.pdf");

   TCanvas *c4 = new TCanvas();
   TLegend *l4 = new TLegend(0.1,0.7,0.3,0.9);
   histoMassID_bin4->DrawNormalized();
   histoMass_bin4->SetLineColor(2);
   histoMassFullID_bin4->SetLineColor(3);
   histoMass_bin4->DrawNormalized("same");
   histoMassFullID_bin4->DrawNormalized("same");
   l4->AddEntry(histoMass_bin1,"no ID","l");
   l4->AddEntry(histoMassID_bin1,"Ds + mu ID","l");
   l4->AddEntry(histoMassFullID_bin1,"Ds + g + mu ID","l");
   l4->Draw();
   c4->SaveAs("q2_bin4.pdf");

   TCanvas *c5 = new TCanvas();
   TLegend *l5 = new TLegend(0.1,0.7,0.3,0.9);
   histoMassID_bin5->DrawNormalized();
   histoMass_bin5->SetLineColor(2);
   histoMassFullID_bin5->SetLineColor(3);
   histoMass_bin5->DrawNormalized("same");
   histoMassFullID_bin5->DrawNormalized("same");
   l5->AddEntry(histoMass_bin1,"no ID","l");
   l5->AddEntry(histoMassID_bin1,"Ds + mu ID","l");
   l5->AddEntry(histoMassFullID_bin1,"Ds + g + mu ID","l");
   l5->Draw();
   c5->SaveAs("q2_bin5.pdf");

   TCanvas *c6 = new TCanvas();
   TLegend *l6 = new TLegend(0.1,0.7,0.3,0.9);
   histoMassID_bin6->DrawNormalized();
   histoMass_bin6->SetLineColor(2);
   histoMassFullID_bin6->SetLineColor(3);
   histoMass_bin6->DrawNormalized("same");
   histoMassFullID_bin6->DrawNormalized("same"); 
   l6->AddEntry(histoMass_bin1,"no ID","l");
   l6->AddEntry(histoMassID_bin1,"Ds + mu ID","l");
   l6->AddEntry(histoMassFullID_bin1,"Ds + g + mu ID","l");
   l6->Draw();
   c6->SaveAs("q2_bin6.pdf");   

}
