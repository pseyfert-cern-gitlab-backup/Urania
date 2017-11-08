#define CheckShapes_cxx
#include "CheckShapes.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void CheckShapes::Loop()
{

// #################
// ##### INFO ######  
// This code checks the distribution of the 3 fitting variables (MCORR, EMU, Q2) 
// and compares them with the distribution with and without photon cuts
// #################  

//   In a ROOT session, you can do:
//      Root > .L CheckShapes.C
//      Root > CheckShapes t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();
   std::cout << "total number of entries = " << nentries << std::endl; 

   TFile *f = new TFile("histosCheckShapes_NewMC_MuNu.root","new");
   float MassDsPDG = 1968.30;
   float MassPi0PDG = 134.9766;

   // photon mass histograms
   TH1F *hDsstMuMass_MCORR = new TH1F("DsstMuMass_MCORR", "DsstMuNu MCORR", 30, 3000, 8000);
   TH1F *hDsstTauMass_MCORR = new TH1F("DsstTauMass_MCORR", "DsstTauNu MCORR", 30, 3000, 8000);
   TH1F *hDsstMuMass_Q2 = new TH1F("DsstMuMass_Q2", "DsstMuNu Q2", 10, -5000000, 11500000);
   TH1F *hDsstTauMass_Q2 = new TH1F("DsstTauMass_Q2", "DsstTauNu Q2", 10, -5000000, 11500000);
   TH1F *hDsstMuMass_Emu = new TH1F("DsstMuMass_Emu", "DsstMuNu Emu", 20, 200, 3600);
   TH1F *hDsstTauMass_Emu = new TH1F("DsstTauMass_Emu", "DsstTauNu Emu", 20, 200, 3600);
   TH1F *hDsstMuMass_MCORR_NoPhoton = new TH1F("DsstMuMass_MCORR_NoPhoton", "DsstMuNu MCORR NoPhoton", 30, 3000, 8000);
   TH1F *hDsstTauMass_MCORR_NoPhoton = new TH1F("DsstTauMass_MCORR_NoPhoton", "DsstTauNu MCORR No Photon", 30, 3000, 8000);
   TH1F *hDsstMuMass_Q2_NoPhoton = new TH1F("DsstMuMass_Q2_NoPhoton", "DsstMuNu Q2 No Photon", 10, -5000000, 11500000);
   TH1F *hDsstTauMass_Q2_NoPhoton = new TH1F("DsstTauMass_Q2_NoPhoton", "DsstTauNu Q2 No Photon", 10, -5000000, 11500000);
   TH1F *hDsstMuMass_Emu_NoPhoton = new TH1F("DsstMuMass_Emu_NoPhoton", "DsstMuNu Emu No Photon", 20, 200, 3600);
   TH1F *hDsstTauMass_Emu_NoPhoton = new TH1F("DsstTauMass_Emu_NoPhoton", "DsstTauNu Emu No Photon", 20, 200, 3600);

   TH1F *hDsstMuMass_MCORR_NoPtMu = new TH1F("DsstMuMass_MCORR_NoPtMu", "DsstMuNu MCORR NoPtMu", 30, 3000, 8000);
   TH1F *hDsstTauMass_MCORR_NoPtMu = new TH1F("DsstTauMass_MCORR_NoPtMu", "DsstTauNu MCORR NoPtMu", 30, 3000, 8000);
   TH1F *hDsstMuMass_Q2_NoPtMu = new TH1F("DsstMuMass_Q2_NoPtMu", "DsstMuNu Q2 NoPtMu", 10, -5000000, 11500000);
   TH1F *hDsstTauMass_Q2_NoPtMu = new TH1F("DsstTauMass_Q2_NoPtMu", "DsstTauNu Q2 NoPtMu", 10, -5000000, 11500000);
   TH1F *hDsstMuMass_Emu_NoPtMu = new TH1F("DsstMuMass_Emu_NoPtMu", "DsstMuNu Emu NoPtMu", 20, 200, 3600);
   TH1F *hDsstTauMass_Emu_NoPtMu = new TH1F("DsstTauMass_Emu_NoPtMu", "DsstTauNu Emu NoPtMu", 20, 200, 3600);
   TH1F *hDsstMuMass_MCORR_NoPhoton_NoPtMu = new TH1F("DsstMuMass_MCORR_NoPhoton_NoPtMu", "DsstMuNu MCORR NoPhoton NoPtMu", 30, 3000, 8000);
   TH1F *hDsstTauMass_MCORR_NoPhoton_NoPtMu = new TH1F("DsstTauMass_MCORR_NoPhoton_NoPtMu", "DsstTauNu MCORR No Photon NoPtMu", 30, 3000, 8000);
   TH1F *hDsstMuMass_Q2_NoPhoton_NoPtMu = new TH1F("DsstMuMass_Q2_NoPhoton_NoPtMu", "DsstMuNu Q2 No Photon NoPtMu", 10, -5000000, 11500000);
   TH1F *hDsstTauMass_Q2_NoPhoton_NoPtMu = new TH1F("DsstTauMass_Q2_NoPhoton_NoPtMu", "DsstTauNu Q2 No Photon NoPtMu", 10, -5000000, 11500000);
   TH1F *hDsstMuMass_Emu_NoPhoton_NoPtMu = new TH1F("DsstMuMass_Emu_NoPhoton_NoPtMu", "DsstMuNu Emu No Photon NoPtMu", 20, 200, 3600);
   TH1F *hDsstTauMass_Emu_NoPhoton_NoPtMu = new TH1F("DsstTauMass_Emu_NoPhoton_NoPtMu", "DsstTauNu Emu No Photon NoPtMu", 20, 200, 3600);

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if (ientry%100000==0) std::cout << "Analysing event " << ientry << std::endl; 
      if(Bs_0_L0Global_Dec==1 && Bs_0_Hlt1Phys_Dec==1 && Bs_0_Hlt2Phys_Dec==1){
        if(Bs_0_Hlt2XcMuXForTauB2XcMuDecision_Dec == 1){
        // Emulate the trigger decision
        //if(Kpl_P>5000 && Kmi_P>5000 && pi_P>5000 && (Kpl_PT>800 || Kmi_PT>800 || pi_PT>800) && Ds_PT>2000 && Bs_0_BDTS_DOCA<0.50 && Bs_0_FDCHI2_TOPPV>50 && Ds_MM>1920 && Ds_MM<2010){
          // Full selection 
          if(Bs_0_MCORR<8000 && Bs_0_MCORR>3000 && mu_PT>1000 && mu_ProbNNmu>0.3 && Ds_MM>1940 && Ds_MM<2000) { 
            // Tau decays 
            if(abs(mu_MC_GD_MOTHER_ID) == 531 && abs(mu_TRUEID) == 13 && abs(mu_MC_MOTHER_ID) == 15){
              // Ds*TauNu decays
              if(abs(Ds_MC_MOTHER_ID) == 433 && abs(Ds_TRUEID) == 431 && abs(Ds_MC_GD_MOTHER_ID) == 531){
                hDsstTauMass_MCORR_NoPhoton->Fill(Bs_0_MCORR);
                hDsstTauMass_Q2_NoPhoton->Fill(q2);
                hDsstTauMass_Emu_NoPhoton->Fill(Emu);
                if(Ds_0_40_nc_mult>0 && sqrt(pow(Ds_0_40_nc_maxPt_PX,2)+pow(Ds_0_40_nc_maxPt_PY,2))>0 && Ds_0_40_nc_CL > 0.6){
                  hDsstTauMass_MCORR->Fill(Bs_0_MCORR);    
                  hDsstTauMass_Q2->Fill(q2);
                  hDsstTauMass_Emu->Fill(Emu);
                }   
              }
            }
            // Mu decays
            if(abs(mu_MC_MOTHER_ID) == 531 && abs(mu_TRUEID) == 13){
              // Ds*MuNu decays
              if(abs(Ds_MC_MOTHER_ID) == 433 && abs(Ds_TRUEID) == 431 && abs(Ds_MC_GD_MOTHER_ID) == 531){
                hDsstMuMass_MCORR_NoPhoton->Fill(Bs_0_MCORR);
                hDsstMuMass_Q2_NoPhoton->Fill(q2);
                hDsstMuMass_Emu_NoPhoton->Fill(Emu);
                if(Ds_0_40_nc_mult>0 && sqrt(pow(Ds_0_40_nc_maxPt_PX,2)+pow(Ds_0_40_nc_maxPt_PY,2))>0 && Ds_0_40_nc_CL > 0.6){
                  hDsstMuMass_MCORR->Fill(Bs_0_MCORR);
                  hDsstMuMass_Q2->Fill(q2);  
                  hDsstMuMass_Emu->Fill(Emu);
                }
              }
            }   
          }
          // No ptMu selection
          if(Bs_0_MCORR<8000 && Bs_0_MCORR>3000 && mu_ProbNNmu>0.3 && Ds_MM>1940 && Ds_MM<2000) {
            // Tau decays 
            if(abs(mu_MC_GD_MOTHER_ID) == 531 && abs(mu_TRUEID) == 13 && abs(mu_MC_MOTHER_ID) == 15){
              // Ds*TauNu decays
              if(abs(Ds_MC_MOTHER_ID) == 433 && abs(Ds_TRUEID) == 431 && abs(Ds_MC_GD_MOTHER_ID) == 531){
                hDsstTauMass_MCORR_NoPhoton_NoPtMu->Fill(Bs_0_MCORR); 
                hDsstTauMass_Q2_NoPhoton_NoPtMu->Fill(q2);
                hDsstTauMass_Emu_NoPhoton_NoPtMu->Fill(Emu);
                if(Ds_0_40_nc_mult>0 && sqrt(pow(Ds_0_40_nc_maxPt_PX,2)+pow(Ds_0_40_nc_maxPt_PY,2))>0 && Ds_0_40_nc_CL > 0.6){
                  hDsstTauMass_MCORR_NoPtMu->Fill(Bs_0_MCORR);    
                  hDsstTauMass_Q2_NoPtMu->Fill(q2);
                  hDsstTauMass_Emu_NoPtMu->Fill(Emu);
                }   
              } 
            } 
            // Mu decays
            if(abs(mu_MC_MOTHER_ID) == 531 && abs(mu_TRUEID) == 13){
              // Ds*MuNu decays
              if(abs(Ds_MC_MOTHER_ID) == 433 && abs(Ds_TRUEID) == 431 && abs(Ds_MC_GD_MOTHER_ID) == 531){
                hDsstMuMass_MCORR_NoPhoton_NoPtMu->Fill(Bs_0_MCORR);
                hDsstMuMass_Q2_NoPhoton_NoPtMu->Fill(q2);
                hDsstMuMass_Emu_NoPhoton_NoPtMu->Fill(Emu);
                if(Ds_0_40_nc_mult>0 && sqrt(pow(Ds_0_40_nc_maxPt_PX,2)+pow(Ds_0_40_nc_maxPt_PY,2))>0 && Ds_0_40_nc_CL > 0.6){
                  hDsstMuMass_MCORR_NoPtMu->Fill(Bs_0_MCORR);
                  hDsstMuMass_Q2_NoPtMu->Fill(q2);  
                  hDsstMuMass_Emu_NoPtMu->Fill(Emu);
                } 
              } 
            }  
          }
        }
      }
   }

   hDsstMuMass_MCORR->Write();
   hDsstTauMass_MCORR->Write();
   hDsstMuMass_Q2->Write();
   hDsstTauMass_Q2->Write();
   hDsstMuMass_Emu->Write();
   hDsstTauMass_Emu->Write();

   hDsstMuMass_MCORR_NoPhoton->Write();
   hDsstTauMass_MCORR_NoPhoton->Write();
   hDsstMuMass_Q2_NoPhoton->Write();
   hDsstTauMass_Q2_NoPhoton->Write(); 
   hDsstMuMass_Emu_NoPhoton->Write();
   hDsstTauMass_Emu_NoPhoton->Write();

   hDsstMuMass_MCORR_NoPtMu->Write();
   hDsstTauMass_MCORR_NoPtMu->Write();
   hDsstMuMass_Q2_NoPtMu->Write();
   hDsstTauMass_Q2_NoPtMu->Write();
   hDsstMuMass_Emu_NoPtMu->Write();
   hDsstTauMass_Emu_NoPtMu->Write();

   hDsstMuMass_MCORR_NoPhoton_NoPtMu->Write();
   hDsstTauMass_MCORR_NoPhoton_NoPtMu->Write();
   hDsstMuMass_Q2_NoPhoton_NoPtMu->Write();
   hDsstTauMass_Q2_NoPhoton_NoPtMu->Write();
   hDsstMuMass_Emu_NoPhoton_NoPtMu->Write();
   hDsstTauMass_Emu_NoPhoton_NoPtMu->Write();

   TCanvas *c1 = new TCanvas();
   hDsstMuMass_MCORR->DrawNormalized();
   hDsstMuMass_MCORR->GetXaxis()->SetTitle("MCORR (MeV)");
   hDsstMuMass_MCORR_NoPhoton->SetLineColor(2);
   hDsstMuMass_MCORR_NoPhoton->DrawNormalized("same");
   hDsstMuMass_MCORR_NoPhoton_NoPtMu->SetLineColor(2);
   hDsstMuMass_MCORR_NoPtMu->SetLineStyle(2);
   hDsstMuMass_MCORR_NoPhoton_NoPtMu->SetLineStyle(2);
   hDsstMuMass_MCORR_NoPtMu->DrawNormalized("same");
   hDsstMuMass_MCORR_NoPhoton_NoPtMu->DrawNormalized("same");
   c1->SaveAs("MCORR_Mu.pdf");

   TCanvas *c2 = new TCanvas();
   hDsstTauMass_MCORR->DrawNormalized();
   hDsstTauMass_MCORR->GetXaxis()->SetTitle("MCORR (MeV)");
   hDsstTauMass_MCORR_NoPhoton->SetLineColor(2);
   hDsstTauMass_MCORR_NoPhoton->DrawNormalized("same");
   hDsstTauMass_MCORR_NoPtMu->SetLineStyle(2);
   hDsstTauMass_MCORR_NoPhoton_NoPtMu->SetLineStyle(2);
   hDsstTauMass_MCORR_NoPhoton_NoPtMu->SetLineColor(2);
   hDsstTauMass_MCORR_NoPtMu->DrawNormalized("same");
   hDsstTauMass_MCORR_NoPhoton_NoPtMu->DrawNormalized("same");
   c2->SaveAs("MCORR_Tau.pdf");

   TCanvas *c3 = new TCanvas();
   hDsstMuMass_Q2->DrawNormalized();
   hDsstMuMass_Q2->GetXaxis()->SetTitle("Q2 (MeV^{2})");
   hDsstMuMass_Q2_NoPhoton->SetLineColor(2);
   hDsstMuMass_Q2_NoPhoton->DrawNormalized("same");
   hDsstMuMass_Q2_NoPhoton_NoPtMu->SetLineColor(2);
   hDsstMuMass_Q2_NoPtMu->SetLineStyle(2);
   hDsstMuMass_Q2_NoPhoton_NoPtMu->SetLineStyle(2);
   hDsstMuMass_Q2_NoPtMu->DrawNormalized("same"); 
   hDsstMuMass_Q2_NoPhoton_NoPtMu->DrawNormalized("same");
   c3->SaveAs("Q2_Mu.pdf");

   TCanvas *c4 = new TCanvas();
   hDsstTauMass_Q2->DrawNormalized();
   hDsstTauMass_Q2->GetXaxis()->SetTitle("Q2 (MeV^{2})");
   hDsstTauMass_Q2_NoPhoton->SetLineColor(2);
   hDsstTauMass_Q2_NoPhoton->DrawNormalized("same");
   hDsstTauMass_Q2_NoPtMu->SetLineStyle(2);
   hDsstTauMass_Q2_NoPhoton_NoPtMu->SetLineStyle(2);
   hDsstTauMass_Q2_NoPhoton_NoPtMu->SetLineColor(2);
   hDsstTauMass_Q2_NoPtMu->DrawNormalized("same");
   hDsstTauMass_Q2_NoPhoton_NoPtMu->DrawNormalized("same");
   c4->SaveAs("Q2_Tau.pdf");

   TCanvas *c5 = new TCanvas();
   hDsstMuMass_Emu->DrawNormalized();
   hDsstMuMass_Emu->GetXaxis()->SetTitle("Emu (MeV)");
   hDsstMuMass_Emu_NoPhoton->SetLineColor(2);
   hDsstMuMass_Emu_NoPhoton->DrawNormalized("same");
   hDsstMuMass_Emu_NoPhoton_NoPtMu->SetLineColor(2);
   hDsstMuMass_Emu_NoPhoton_NoPtMu->SetLineStyle(2);
   hDsstMuMass_Emu_NoPtMu->SetLineStyle(2);
   hDsstMuMass_Emu_NoPtMu->DrawNormalized("same");
   hDsstMuMass_Emu_NoPhoton_NoPtMu->DrawNormalized("same");
   c5->SaveAs("Emu_Mu.pdf");

   TCanvas *c6 = new TCanvas();
   hDsstTauMass_Emu->DrawNormalized();
   hDsstTauMass_Emu->GetXaxis()->SetTitle("Emu (MeV)");
   hDsstTauMass_Emu_NoPhoton->SetLineColor(2);
   hDsstTauMass_Emu_NoPhoton->DrawNormalized("same");
   hDsstTauMass_Emu_NoPhoton_NoPtMu->SetLineColor(2);
   hDsstTauMass_Emu_NoPhoton_NoPtMu->SetLineStyle(2);
   hDsstTauMass_Emu_NoPtMu->SetLineStyle(2);
   hDsstTauMass_Emu_NoPtMu->DrawNormalized("same");
   hDsstTauMass_Emu_NoPhoton_NoPtMu->DrawNormalized("same");
   c6->SaveAs("Emu_Tau.pdf");

}
