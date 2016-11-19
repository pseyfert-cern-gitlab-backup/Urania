#define NeutralIso_cxx
#include "NeutralIso.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void NeutralIso::Loop()
{
//   In a ROOT session, you can do:
//      root> .L NeutralIso.C
//      root> NeutralIso t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
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

   TFile *f = new TFile("histosNeutralIso.root","new");

   TH1F *hDsMuCorrMass01 = new TH1F("DsMuNeutralMult0.1", "DsMuNu Neutral multiplicity 0.1", 16, -0.5, 15.5);
   TH1F *hDsTauCorrMass01 = new TH1F("DsTauNeutralMult0.1", "DsTauNu Neutral multiplicity 0.1", 16, -0.5, 15.5);
   TH1F *hDsstMuCorrMass01 = new TH1F("DsstMuNeutralMult0.1", "Ds*MuNu Neutral multiplicity 0.1", 16, -0.5, 15.5);
   TH1F *hDsstTauCorrMass01 = new TH1F("DsstTauNeutralMult0.1", "Ds*TauNu Neutral multiplicity 0.1", 16, -0.5, 15.5);
   TH1F *hDs0MuCorrMass01 = new TH1F("Ds0MuNeutralMult0.1", "Ds0MuNu Neutral multiplicity 0.1", 16, -0.5, 15.5);
   TH1F *hDs0TauCorrMass01 = new TH1F("Ds0TauNeutralMult0.1", "Ds0TauNu Neutral multiplicity 0.1", 16, -0.5, 15.5);
   TH1F *hDs1MuCorrMass01 = new TH1F("Ds1MuNeutralMult0.1", "Ds1MuNu Neutral multiplicity 0.1", 16, -0.5, 15.5);
   TH1F *hDs1TauCorrMass01 = new TH1F("Ds1TauNeutralMult0.1", "Ds1TauNu Neutral multiplicity 0.1", 16, -0.5, 15.5);
   TH1F *hDsprMuCorrMass01 = new TH1F("DsprMuNeutralMult0.1", "DsprMuNu Neutral multiplicity 0.1", 16, -0.5, 15.5);
   TH1F *hDsprTauCorrMass01 = new TH1F("DsprTauNeutralMult0.1", "DsprTauNu Neutral multiplicity 0.1", 16, -0.5, 15.5);
  
   TH1F *hDsMuCorrMass02 = new TH1F("DsMuNeutralMult0.2", "DsMuNu Neutral multiplicity 0.2", 16, -0.5, 15.5);
   TH1F *hDsTauCorrMass02 = new TH1F("DsTauNeutralMult0.2", "DsTauNu Neutral multiplicity 0.2", 16, -0.5, 15.5);
   TH1F *hDsstMuCorrMass02 = new TH1F("DsstMuNeutralMult0.2", "Ds*MuNu Neutral multiplicity 0.2", 16, -0.5, 15.5);
   TH1F *hDsstTauCorrMass02 = new TH1F("DsstTauNeutralMult0.2", "Ds*TauNu Neutral multiplicity 0.2", 16, -0.5, 15.5);
   TH1F *hDs0MuCorrMass02 = new TH1F("Ds0MuNeutralMult0.2", "Ds0MuNu Neutral multiplicity 0.2", 16, -0.5, 15.5);
   TH1F *hDs0TauCorrMass02 = new TH1F("Ds0TauNeutralMult0.2", "Ds0TauNu Neutral multiplicity 0.2", 16, -0.5, 15.5);
   TH1F *hDs1MuCorrMass02 = new TH1F("Ds1MuNeutralMult0.2", "Ds1MuNu Neutral multiplicity 0.2", 16, -0.5, 15.5);
   TH1F *hDs1TauCorrMass02 = new TH1F("Ds1TauNeutralMult0.2", "Ds1TauNu Neutral multiplicity 0.2", 16, -0.5, 15.5);
   TH1F *hDsprMuCorrMass02 = new TH1F("DsprMuNeutralMult0.2", "DsprMuNu Neutral multiplicity 0.2", 16, -0.5, 15.5);
   TH1F *hDsprTauCorrMass02 = new TH1F("DsprTauNeutralMult0.2", "DsprTauNu Neutral multiplicity 0.2", 16, -0.5, 15.5);

   TH1F *hDsMuCorrMass03 = new TH1F("DsMuNeutralMult0.3", "DsMuNu Neutral multiplicity 0.3", 16, -0.5, 15.5);
   TH1F *hDsTauCorrMass03 = new TH1F("DsTauNeutralMult0.3", "DsTauNu Neutral multiplicity 0.3", 16, -0.5, 15.5);
   TH1F *hDsstMuCorrMass03 = new TH1F("DsstMuNeutralMult0.3", "Ds*MuNu Neutral multiplicity 0.3", 16, -0.5, 15.5);
   TH1F *hDsstTauCorrMass03 = new TH1F("DsstTauNeutralMult0.3", "Ds*TauNu Neutral multiplicity 0.3", 16, -0.5, 15.5);
   TH1F *hDs0MuCorrMass03 = new TH1F("Ds0MuNeutralMult0.3", "Ds0MuNu Neutral multiplicity 0.3", 16, -0.5, 15.5);
   TH1F *hDs0TauCorrMass03 = new TH1F("Ds0TauNeutralMult0.3", "Ds0TauNu Neutral multiplicity 0.3", 16, -0.5, 15.5);
   TH1F *hDs1MuCorrMass03 = new TH1F("Ds1MuNeutralMult0.3", "Ds1MuNu Neutral multiplicity 0.3", 16, -0.5, 15.5);
   TH1F *hDs1TauCorrMass03 = new TH1F("Ds1TauNeutralMult0.3", "Ds1TauNu Neutral multiplicity 0.3", 16, -0.5, 15.5);
   TH1F *hDsprMuCorrMass03 = new TH1F("DsprMuNeutralMult0.3", "DsprMuNu Neutral multiplicity 0.3", 16, -0.5, 15.5);
   TH1F *hDsprTauCorrMass03 = new TH1F("DsprTauNeutralMult0.3", "DsprTauNu Neutral multiplicity 0.3", 16, -0.5, 15.5);

   TH1F *hDsMuCorrMass04 = new TH1F("DsMuNeutralMult0.4", "DsMuNu Neutral multiplicity 0.4", 16, -0.5, 15.5);
   TH1F *hDsTauCorrMass04 = new TH1F("DsTauNeutralMult0.4", "DsTauNu Neutral multiplicity 0.4", 16, -0.5, 15.5);
   TH1F *hDsstMuCorrMass04 = new TH1F("DsstMuNeutralMult0.4", "Ds*MuNu Neutral multiplicity 0.4", 16, -0.5, 15.5);
   TH1F *hDsstTauCorrMass04 = new TH1F("DsstTauNeutralMult0.4", "Ds*TauNu Neutral multiplicity 0.4", 16, -0.5, 15.5);
   TH1F *hDs0MuCorrMass04 = new TH1F("Ds0MuNeutralMult0.4", "Ds0MuNu Neutral multiplicity 0.4", 16, -0.5, 15.5);
   TH1F *hDs0TauCorrMass04 = new TH1F("Ds0TauNeutralMult0.4", "Ds0TauNu Neutral multiplicity 0.4", 16, -0.5, 15.5);
   TH1F *hDs1MuCorrMass04 = new TH1F("Ds1MuNeutralMult0.4", "Ds1MuNu Neutral multiplicity 0.4", 16, -0.5, 15.5);
   TH1F *hDs1TauCorrMass04 = new TH1F("Ds1TauNeutralMult0.4", "Ds1TauNu Neutral multiplicity 0.4", 16, -0.5, 15.5);
   TH1F *hDsprMuCorrMass04 = new TH1F("DsprMuNeutralMult0.4", "DsprMuNu Neutral multiplicity 0.4", 16, -0.5, 15.5);
   TH1F *hDsprTauCorrMass04 = new TH1F("DsprTauNeutralMult0.4", "DsprTauNu Neutral multiplicity 0.4", 16, -0.5, 15.5);
  
   TH1F *hDsMuCorrMass05 = new TH1F("DsMuNeutralMult0.5", "DsMuNu Neutral multiplicity 0.5", 16, -0.5, 15.5);
   TH1F *hDsTauCorrMass05 = new TH1F("DsTauNeutralMult0.5", "DsTauNu Neutral multiplicity 0.5", 16, -0.5, 15.5);
   TH1F *hDsstMuCorrMass05 = new TH1F("DsstMuNeutralMult0.5", "Ds*MuNu Neutral multiplicity 0.5", 16, -0.5, 15.5);
   TH1F *hDsstTauCorrMass05 = new TH1F("DsstTauNeutralMult0.5", "Ds*TauNu Neutral multiplicity 0.5", 16, -0.5, 15.5);
   TH1F *hDs0MuCorrMass05 = new TH1F("Ds0MuNeutralMult0.5", "Ds0MuNu Neutral multiplicity 0.5", 16, -0.5, 15.5);
   TH1F *hDs0TauCorrMass05 = new TH1F("Ds0TauNeutralMult0.5", "Ds0TauNu Neutral multiplicity 0.5", 16, -0.5, 15.5);
   TH1F *hDs1MuCorrMass05 = new TH1F("Ds1MuNeutralMult0.5", "Ds1MuNu Neutral multiplicity 0.5", 16, -0.5, 15.5);
   TH1F *hDs1TauCorrMass05 = new TH1F("Ds1TauNeutralMult0.5", "Ds1TauNu Neutral multiplicity 0.5", 16, -0.5, 15.5);
   TH1F *hDsprMuCorrMass05 = new TH1F("DsprMuNeutralMult0.5", "DsprMuNu Neutral multiplicity 0.5", 16, -0.5, 15.5);
   TH1F *hDsprTauCorrMass05 = new TH1F("DsprTauNeutralMult0.5", "DsprTauNu Neutral multiplicity 0.5", 16, -0.5, 15.5); 

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // Tau decays
      if(abs(mu_MC_MOTHER_ID) == 15 && abs(mu_TRUEID) == 13){
        // DsTauNu decays
        if(abs(Ds_MC_MOTHER_ID)==531 && abs(Ds_TRUEID) == 431){
          hDsTauCorrMass01->Fill(Ds_0_10_nc_mult);
          hDsTauCorrMass02->Fill(Ds_0_20_nc_mult);
          hDsTauCorrMass03->Fill(Ds_0_30_nc_mult);
          hDsTauCorrMass04->Fill(Ds_0_40_nc_mult);
          hDsTauCorrMass05->Fill(Ds_0_50_nc_mult);
        }
        // Ds*TauNu decays
        if(abs(Ds_MC_MOTHER_ID)==433 && abs(Ds_TRUEID) == 431){
          hDsstTauCorrMass01->Fill(Ds_0_10_nc_mult);
          hDsstTauCorrMass02->Fill(Ds_0_20_nc_mult);
          hDsstTauCorrMass03->Fill(Ds_0_30_nc_mult);
          hDsstTauCorrMass04->Fill(Ds_0_40_nc_mult);
          hDsstTauCorrMass05->Fill(Ds_0_50_nc_mult);
        }
        // Ds0*TauNu decays
        if(abs(Ds_MC_MOTHER_ID)==10431 && abs(Ds_TRUEID) == 431){
          hDs0TauCorrMass01->Fill(Ds_0_10_nc_mult);
          hDs0TauCorrMass02->Fill(Ds_0_20_nc_mult);
          hDs0TauCorrMass03->Fill(Ds_0_30_nc_mult);
          hDs0TauCorrMass04->Fill(Ds_0_40_nc_mult);
          hDs0TauCorrMass05->Fill(Ds_0_50_nc_mult);
        }
        // Ds1TauNu decays
        if(abs(Ds_MC_MOTHER_ID)==20433 && abs(Ds_TRUEID) == 431){
          hDs1TauCorrMass01->Fill(Ds_0_10_nc_mult);
          hDs1TauCorrMass02->Fill(Ds_0_20_nc_mult);
          hDs1TauCorrMass03->Fill(Ds_0_30_nc_mult);
          hDs1TauCorrMass04->Fill(Ds_0_40_nc_mult);
          hDs1TauCorrMass05->Fill(Ds_0_50_nc_mult);
        }
        // Ds'TauNu decays 
        if(abs(Ds_MC_MOTHER_ID)==10433 && abs(Ds_TRUEID) == 431){
          hDsprTauCorrMass01->Fill(Ds_0_10_nc_mult);
          hDsprTauCorrMass02->Fill(Ds_0_20_nc_mult);
          hDsprTauCorrMass03->Fill(Ds_0_30_nc_mult);
          hDsprTauCorrMass04->Fill(Ds_0_40_nc_mult);
          hDsprTauCorrMass05->Fill(Ds_0_50_nc_mult);
        }
      }
      // Mu decays
      if(abs(mu_MC_MOTHER_ID) == 531 && abs(mu_TRUEID) == 13){
        // DsMuNu decays
        if(abs(Ds_MC_MOTHER_ID) == 531 && abs(Ds_TRUEID) == 431){   
          hDsMuCorrMass01->Fill(Ds_0_10_nc_mult);
          hDsMuCorrMass02->Fill(Ds_0_20_nc_mult);
          hDsMuCorrMass03->Fill(Ds_0_30_nc_mult);
          hDsMuCorrMass04->Fill(Ds_0_40_nc_mult);
          hDsMuCorrMass05->Fill(Ds_0_50_nc_mult);
        }
        // Ds*MuNu decays
        if(abs(Ds_MC_MOTHER_ID) == 433 && abs(Ds_TRUEID) == 431){
          hDsstMuCorrMass01->Fill(Ds_0_10_nc_mult);
          hDsstMuCorrMass02->Fill(Ds_0_20_nc_mult);
          hDsstMuCorrMass03->Fill(Ds_0_30_nc_mult);
          hDsstMuCorrMass04->Fill(Ds_0_40_nc_mult);
          hDsstMuCorrMass05->Fill(Ds_0_50_nc_mult);
        }
        // Ds0MuNu decays
        if(abs(Ds_MC_MOTHER_ID) == 10431 && abs(Ds_TRUEID) == 431){
          hDs0MuCorrMass01->Fill(Ds_0_10_nc_mult);
          hDs0MuCorrMass02->Fill(Ds_0_20_nc_mult);
          hDs0MuCorrMass03->Fill(Ds_0_30_nc_mult);
          hDs0MuCorrMass04->Fill(Ds_0_40_nc_mult);
          hDs0MuCorrMass05->Fill(Ds_0_50_nc_mult);          
        }
        // Ds1MuNu decays
        if(abs(Ds_MC_MOTHER_ID) == 20433 && abs(Ds_TRUEID) == 431){
          hDs1MuCorrMass01->Fill(Ds_0_10_nc_mult);
          hDs1MuCorrMass02->Fill(Ds_0_20_nc_mult);
          hDs1MuCorrMass03->Fill(Ds_0_30_nc_mult);
          hDs1MuCorrMass04->Fill(Ds_0_40_nc_mult);
          hDs1MuCorrMass05->Fill(Ds_0_50_nc_mult);      
        }
        // Ds'MuNu decays
        if(abs(Ds_MC_MOTHER_ID) == 10433 && abs(Ds_TRUEID) == 431){
          hDsprMuCorrMass01->Fill(Ds_0_10_nc_mult);
          hDsprMuCorrMass02->Fill(Ds_0_20_nc_mult);
          hDsprMuCorrMass03->Fill(Ds_0_30_nc_mult);
          hDsprMuCorrMass04->Fill(Ds_0_40_nc_mult);
          hDsprMuCorrMass05->Fill(Ds_0_50_nc_mult);
        }
      }

   // if (Cut(ientry) < 0) continue;

   }
   hDsMuCorrMass01->Write();
   hDsTauCorrMass01->Write();
   hDsstMuCorrMass01->Write();
   hDsstTauCorrMass01->Write();
   hDs0MuCorrMass01->Write();
   hDs0TauCorrMass01->Write();    
   hDs1MuCorrMass01->Write();
   hDs1TauCorrMass01->Write();
   hDsprMuCorrMass01->Write();
   hDsprTauCorrMass01->Write(); 

   hDsMuCorrMass02->Write();
   hDsTauCorrMass02->Write();
   hDsstMuCorrMass02->Write();
   hDsstTauCorrMass02->Write();
   hDs0MuCorrMass02->Write();
   hDs0TauCorrMass02->Write();
   hDs1MuCorrMass02->Write();
   hDs1TauCorrMass02->Write();
   hDsprMuCorrMass02->Write();
   hDsprTauCorrMass02->Write();

   hDsMuCorrMass03->Write();
   hDsTauCorrMass03->Write();
   hDsstMuCorrMass03->Write();
   hDsstTauCorrMass03->Write();
   hDs0MuCorrMass03->Write();
   hDs0TauCorrMass03->Write();
   hDs1MuCorrMass03->Write();
   hDs1TauCorrMass03->Write();
   hDsprMuCorrMass03->Write();
   hDsprTauCorrMass03->Write();

   hDsMuCorrMass04->Write();
   hDsTauCorrMass04->Write();
   hDsstMuCorrMass04->Write();
   hDsstTauCorrMass04->Write();
   hDs0MuCorrMass04->Write();
   hDs0TauCorrMass04->Write();
   hDs1MuCorrMass04->Write();
   hDs1TauCorrMass04->Write();
   hDsprMuCorrMass04->Write();
   hDsprTauCorrMass04->Write();

   hDsMuCorrMass05->Write();
   hDsTauCorrMass05->Write();
   hDsstMuCorrMass05->Write();
   hDsstTauCorrMass05->Write();
   hDs0MuCorrMass05->Write();
   hDs0TauCorrMass05->Write();
   hDs1MuCorrMass05->Write();
   hDs1TauCorrMass05->Write();
   hDsprMuCorrMass05->Write();
   hDsprTauCorrMass05->Write();
}
