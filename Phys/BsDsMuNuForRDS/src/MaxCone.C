#define MaxCone_cxx
#include "MaxCone.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void MaxCone::Loop()
{
//   In a ROOT session, you can do:
//      root> .L MaxCone.C
//      root> MaxCone t
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

   Long64_t nentries = fChain->GetEntriesFast();

   TFile *f = new TFile("histosMaxCone.root","new");
 
   TH1F *hDsMuMaxCone = new TH1F("DsMuMaxCone", "DsMuNu MaxCone ", 100, 0, 3.2);
   TH1F *hDsTauMaxCone = new TH1F("DsTauMaxCone", "DsTauNu MaxCone", 100, 0, 3.2);

   TH1F *hDsstMuCorrMass = new TH1F("DsstMuCorrMass", "Ds*MuNu corrected mass", 100, 2000, 5500);
   TH1F *hDsstTauCorrMass = new TH1F("DsstTauCorrMass", "Ds*TauNu corrected mass", 100, 2000, 5500);

   TH1F *hDs0MuCorrMass = new TH1F("Ds0MuCorrMass", "Ds0MuNu corrected mass", 100, 2000, 5500);
   TH1F *hDs0TauCorrMass = new TH1F("Ds0TauCorrMass", "Ds0TauNu corrected mass", 100, 2000, 5500);
 
   TH1F *hDs1MuCorrMass = new TH1F("Ds1MuCorrMass", "Ds1MuNu corrected mass", 100, 2000, 5500);
   TH1F *hDs1TauCorrMass = new TH1F("Ds1TauCorrMass", "Ds1TauNu corrected mass", 100, 2000, 5500);

   TH1F *hDsprMuCorrMass = new TH1F("DsprMuCorrMass", "DsprMuNu corrected mass", 100, 2000, 5500);
   TH1F *hDsprTauCorrMass = new TH1F("DsprTauCorrMass", "DsprTauNu corrected mass", 100, 2000, 5500);

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // Tau decays
      if(abs(mu_MC_MOTHER_ID) == 15 && abs(mu_TRUEID) == 13){
        // DsTauNu decays
        if(abs(Ds_MC_MOTHER_ID)==531 && abs(Ds_TRUEID) == 431){
          hDsTauCorrMass->Fill(Bs_0_MCORR);
          hDsTauCorrMassErr->Fill(Bs_0_MCORRERR);
          hDsTauBP->Fill(Bs_0_P);
          hDsTauBPT->Fill(Bs_0_PT);
          hDsTauVChi2->Fill(Bs_0_ENDVERTEX_CHI2);
          hDsTauDsVChi2->Fill(Ds_ENDVERTEX_CHI2);
          hDsTauDOCA->Fill(Bs_0_BDTS_DOCA);
          hDsTauDsMass->Fill(Ds_MM);
          hDsTauDIRA->Fill(Bs_0_DIRA_OWNPV);
          hDsTauFD->Fill(Bs_0_FD_OWNPV);
          hDsTauIP->Fill(Bs_0_IP_OWNPV);
          hDsTauDsP->Fill(Ds_P);
          hDsTauDsPT->Fill(Ds_PT);
          hDsTauMuP->Fill(mu_P);
          hDsTauMuPT->Fill(mu_PT);
        }
        // Ds*TauNu decays
        if(abs(Ds_MC_MOTHER_ID)==433 && abs(Ds_TRUEID) == 431){
          hDsstTauCorrMass->Fill(Bs_0_MCORR);
          hDsstTauCorrMassErr->Fill(Bs_0_MCORRERR);
          hDsstTauBP->Fill(Bs_0_P);
          hDsstTauBPT->Fill(Bs_0_PT);
          hDsstTauVChi2->Fill(Bs_0_ENDVERTEX_CHI2);
          hDsstTauDsVChi2->Fill(Ds_ENDVERTEX_CHI2);
          hDsstTauDOCA->Fill(Bs_0_BDTS_DOCA);
          hDsstTauDsMass->Fill(Ds_MM);
          hDsstTauDIRA->Fill(Bs_0_DIRA_OWNPV);
          hDsstTauFD->Fill(Bs_0_FD_OWNPV);
          hDsstTauIP->Fill(Bs_0_IP_OWNPV);
          hDsstTauDsP->Fill(Ds_P);
          hDsstTauDsPT->Fill(Ds_PT);
          hDsstTauMuP->Fill(mu_P);
          hDsstTauMuPT->Fill(mu_PT);
        }
        // Ds0*TauNu decays
        if(abs(Ds_MC_MOTHER_ID)==10431 && abs(Ds_TRUEID) == 431){
          hDs0TauCorrMass->Fill(Bs_0_MCORR);
          hDs0TauCorrMassErr->Fill(Bs_0_MCORRERR);
          hDs0TauBP->Fill(Bs_0_P);
          hDs0TauBPT->Fill(Bs_0_PT);
          hDs0TauVChi2->Fill(Bs_0_ENDVERTEX_CHI2);
          hDs0TauDsVChi2->Fill(Ds_ENDVERTEX_CHI2);
          hDs0TauDOCA->Fill(Bs_0_BDTS_DOCA);
          hDs0TauDsMass->Fill(Ds_MM);
          hDs0TauDIRA->Fill(Bs_0_DIRA_OWNPV);
          hDs0TauFD->Fill(Bs_0_FD_OWNPV);
          hDs0TauIP->Fill(Bs_0_IP_OWNPV);
          hDs0TauDsP->Fill(Ds_P);
          hDs0TauDsPT->Fill(Ds_PT);
          hDs0TauMuP->Fill(mu_P);
          hDs0TauMuPT->Fill(mu_PT);
        }
        // Ds1TauNu decays
        if(abs(Ds_MC_MOTHER_ID)==20433 && abs(Ds_TRUEID) == 431){
          hDs1TauCorrMass->Fill(Bs_0_MCORR);
          hDs1TauCorrMassErr->Fill(Bs_0_MCORRERR);
          hDs1TauBP->Fill(Bs_0_P);
          hDs1TauBPT->Fill(Bs_0_PT);
          hDs1TauVChi2->Fill(Bs_0_ENDVERTEX_CHI2);
          hDs1TauDsVChi2->Fill(Ds_ENDVERTEX_CHI2);
          hDs1TauDOCA->Fill(Bs_0_BDTS_DOCA);
          hDs1TauDsMass->Fill(Ds_MM);
          hDs1TauDIRA->Fill(Bs_0_DIRA_OWNPV);
          hDs1TauFD->Fill(Bs_0_FD_OWNPV);
          hDs1TauIP->Fill(Bs_0_IP_OWNPV);
          hDs1TauDsP->Fill(Ds_P);
          hDs1TauDsPT->Fill(Ds_PT);
          hDs1TauMuP->Fill(mu_P);
          hDs1TauMuPT->Fill(mu_PT);
        }
        // Ds'TauNu decays 
        if(abs(Ds_MC_MOTHER_ID)==10433 && abs(Ds_TRUEID) == 431){
          hDsprTauCorrMass->Fill(Bs_0_MCORR);
          hDsprTauCorrMassErr->Fill(Bs_0_MCORRERR);
          hDsprTauBP->Fill(Bs_0_P);
          hDsprTauBPT->Fill(Bs_0_PT);
          hDsprTauVChi2->Fill(Bs_0_ENDVERTEX_CHI2);
          hDsprTauDsVChi2->Fill(Ds_ENDVERTEX_CHI2);
          hDsprTauDOCA->Fill(Bs_0_BDTS_DOCA);
          hDsprTauDsMass->Fill(Ds_MM);
          hDsprTauDIRA->Fill(Bs_0_DIRA_OWNPV);
          hDsprTauFD->Fill(Bs_0_FD_OWNPV);
          hDsprTauIP->Fill(Bs_0_IP_OWNPV);
          hDsprTauDsP->Fill(Ds_P);
          hDsprTauDsPT->Fill(Ds_PT);
          hDsprTauMuP->Fill(mu_P);
          hDsprTauMuPT->Fill(mu_PT); 
        }
      }
      // Mu decays
      if(abs(mu_MC_MOTHER_ID) == 531 && abs(mu_TRUEID) == 13){
        // DsMuNu decays
        if(abs(Ds_MC_MOTHER_ID) == 531 && abs(Ds_TRUEID) == 431){
          hDsMuCorrMass->Fill(Bs_0_MCORR);
          hDsMuCorrMassErr->Fill(Bs_0_MCORRERR);
          hDsMuBP->Fill(Bs_0_P);
          hDsMuBPT->Fill(Bs_0_PT);
          hDsMuVChi2->Fill(Bs_0_ENDVERTEX_CHI2);
          hDsMuDsVChi2->Fill(Ds_ENDVERTEX_CHI2);
          hDsMuDOCA->Fill(Bs_0_BDTS_DOCA);
          hDsMuDsMass->Fill(Ds_MM);
          hDsMuDIRA->Fill(Bs_0_DIRA_OWNPV);
          hDsMuFD->Fill(Bs_0_FD_OWNPV);
          hDsMuIP->Fill(Bs_0_IP_OWNPV);
          hDsMuDsP->Fill(Ds_P);
          hDsMuDsPT->Fill(Ds_PT);
          hDsMuMuP->Fill(mu_P);
          hDsMuMuPT->Fill(mu_PT);
        }
        // Ds*MuNu decays
        if(abs(Ds_MC_MOTHER_ID) == 433 && abs(Ds_TRUEID) == 431){
          hDsstMuCorrMass->Fill(Bs_0_MCORR);
          hDsstMuCorrMassErr->Fill(Bs_0_MCORRERR);
          hDsstMuBP->Fill(Bs_0_P);
          hDsstMuBPT->Fill(Bs_0_PT);
          hDsstMuVChi2->Fill(Bs_0_ENDVERTEX_CHI2);
          hDsstMuDsVChi2->Fill(Ds_ENDVERTEX_CHI2);
          hDsstMuDOCA->Fill(Bs_0_BDTS_DOCA);
          hDsstMuDsMass->Fill(Ds_MM);
          hDsstMuDIRA->Fill(Bs_0_DIRA_OWNPV);
          hDsstMuFD->Fill(Bs_0_FD_OWNPV);
          hDsstMuIP->Fill(Bs_0_IP_OWNPV);
          hDsstMuDsP->Fill(Ds_P);
          hDsstMuDsPT->Fill(Ds_PT);
          hDsstMuMuP->Fill(mu_P);
          hDsstMuMuPT->Fill(mu_PT);
        }
        // Ds0MuNu decays
        if(abs(Ds_MC_MOTHER_ID) == 10431 && abs(Ds_TRUEID) == 431){
          hDs0MuCorrMass->Fill(Bs_0_MCORR);
          hDs0MuCorrMassErr->Fill(Bs_0_MCORRERR);
          hDs0MuBP->Fill(Bs_0_P);
          hDs0MuBPT->Fill(Bs_0_PT);
          hDs0MuVChi2->Fill(Bs_0_ENDVERTEX_CHI2);
          hDs0MuDsVChi2->Fill(Ds_ENDVERTEX_CHI2);
          hDs0MuDOCA->Fill(Bs_0_BDTS_DOCA);
          hDs0MuDsMass->Fill(Ds_MM);
          hDs0MuDIRA->Fill(Bs_0_DIRA_OWNPV);
          hDs0MuFD->Fill(Bs_0_FD_OWNPV);
          hDs0MuIP->Fill(Bs_0_IP_OWNPV);
          hDs0MuDsP->Fill(Ds_P);
          hDs0MuDsPT->Fill(Ds_PT);
          hDs0MuMuP->Fill(mu_P);
          hDs0MuMuPT->Fill(mu_PT);
        }
        // Ds1MuNu decays
        if(abs(Ds_MC_MOTHER_ID) == 20433 && abs(Ds_TRUEID) == 431){
          hDs1MuCorrMass->Fill(Bs_0_MCORR);
          hDs1MuCorrMassErr->Fill(Bs_0_MCORRERR);
          hDs1MuBP->Fill(Bs_0_P);
          hDs1MuBPT->Fill(Bs_0_PT);
          hDs1MuVChi2->Fill(Bs_0_ENDVERTEX_CHI2);
          hDs1MuDsVChi2->Fill(Ds_ENDVERTEX_CHI2);
          hDs1MuDOCA->Fill(Bs_0_BDTS_DOCA);
          hDs1MuDsMass->Fill(Ds_MM);
          hDs1MuDIRA->Fill(Bs_0_DIRA_OWNPV);
          hDs1MuFD->Fill(Bs_0_FD_OWNPV);
          hDs1MuIP->Fill(Bs_0_IP_OWNPV);
          hDs1MuDsP->Fill(Ds_P);
          hDs1MuDsPT->Fill(Ds_PT);
          hDs1MuMuP->Fill(mu_P);
          hDs1MuMuPT->Fill(mu_PT);
        }
        // Ds'MuNu decays
        if(abs(Ds_MC_MOTHER_ID) == 10433 && abs(Ds_TRUEID) == 431){
          hDsprMuCorrMass->Fill(Bs_0_MCORR);
          hDsprMuCorrMassErr->Fill(Bs_0_MCORRERR);
          hDsprMuBP->Fill(Bs_0_P);
          hDsprMuBPT->Fill(Bs_0_PT);
          hDsprMuVChi2->Fill(Bs_0_ENDVERTEX_CHI2);
          hDsprMuDsVChi2->Fill(Ds_ENDVERTEX_CHI2);
          hDsprMuDOCA->Fill(Bs_0_BDTS_DOCA);
          hDsprMuDsMass->Fill(Ds_MM);
          hDsprMuDIRA->Fill(Bs_0_DIRA_OWNPV);
          hDsprMuFD->Fill(Bs_0_FD_OWNPV);
          hDsprMuIP->Fill(Bs_0_IP_OWNPV);
          hDsprMuDsP->Fill(Ds_P);
          hDsprMuDsPT->Fill(Ds_PT);
          hDsprMuMuP->Fill(mu_P);
          hDsprMuMuPT->Fill(mu_PT);
        }
      } 
    
      // if (Cut(ientry) < 0) continue;
   }
 
   hDsTauCorrMass->Write();
   hDsMuCorrMass->Write();
   hDsTauCorrMassErr->Write();
   hDsMuCorrMassErr->Write();
   hDsTauBP->Write();
   hDsMuBP->Write();
   hDsTauBPT->Write();
   hDsMuBPT->Write();
   hDsTauVChi2->Write();
   hDsMuVChi2->Write();
   hDsTauDsVChi2->Write();
   hDsMuDsVChi2->Write();
   hDsTauDOCA->Write();
   hDsMuDOCA->Write(); 
   hDsTauDsMass->Write();
   hDsMuDsMass->Write();
   hDsTauDIRA->Write();
   hDsMuDIRA->Write();
   hDsTauFD->Write();
   hDsMuFD->Write();
   hDsTauIP->Write();
   hDsMuIP->Write();
   hDsTauMuP->Write();
   hDsTauMuPT->Write();
   hDsMuMuP->Write();
   hDsMuMuPT->Write();
   hDsTauDsP->Write();
   hDsMuDsP->Write();
   hDsTauDsPT->Write();
   hDsMuDsPT->Write();

   hDsstTauCorrMass->Write();
   hDsstMuCorrMass->Write();
   hDsstTauCorrMassErr->Write();
   hDsstMuCorrMassErr->Write();
   hDsstTauBP->Write();
   hDsstMuBP->Write();
   hDsstTauBPT->Write();
   hDsstMuBPT->Write();
   hDsstTauVChi2->Write();
   hDsstMuVChi2->Write();
   hDsstTauDsVChi2->Write();
   hDsstMuDsVChi2->Write();
   hDsstTauDOCA->Write();
   hDsstMuDOCA->Write();
   hDsstTauDsMass->Write();
   hDsstMuDsMass->Write();
   hDsstTauDIRA->Write();
   hDsstMuDIRA->Write();
   hDsstTauFD->Write();
   hDsstMuFD->Write();
   hDsstTauIP->Write();
   hDsstMuIP->Write();
   hDsstTauMuP->Write();
   hDsstTauMuPT->Write();
   hDsstMuMuP->Write();
   hDsstMuMuPT->Write();
   hDsstTauDsP->Write();
   hDsstMuDsP->Write();
   hDsstTauDsPT->Write();
   hDsstMuDsPT->Write();
 
   hDs0TauCorrMass->Write();
   hDs0MuCorrMass->Write();
   hDs0TauCorrMassErr->Write();
   hDs0MuCorrMassErr->Write();
   hDs0TauBP->Write();
   hDs0MuBP->Write();
   hDs0TauBPT->Write();
   hDs0MuBPT->Write();
   hDs0TauVChi2->Write();
   hDs0MuVChi2->Write();
   hDs0TauDsVChi2->Write();
   hDs0MuDsVChi2->Write();
   hDs0TauDOCA->Write();
   hDs0MuDOCA->Write();
   hDs0TauDsMass->Write();
   hDs0MuDsMass->Write();
   hDs0TauDIRA->Write();
   hDs0MuDIRA->Write();
   hDs0TauFD->Write();
   hDs0MuFD->Write();
   hDs0TauIP->Write();
   hDs0MuIP->Write();
   hDs0TauMuP->Write();
   hDs0MuMuP->Write();
   hDs0TauDsPT->Write();
   hDs0MuDsPT->Write();
   hDs0TauMuP->Write();
   hDs0TauMuPT->Write();
   hDs0MuMuP->Write();
   hDs0MuMuPT->Write();
   hDs0TauDsP->Write();
   hDs0MuDsP->Write();
   hDs0TauDsPT->Write();
   hDs0MuDsPT->Write();

   hDs1TauCorrMass->Write();
   hDs1MuCorrMass->Write();
   hDs1TauCorrMassErr->Write();
   hDs1MuCorrMassErr->Write();
   hDs1TauBP->Write();
   hDs1MuBP->Write();
   hDs1TauBPT->Write();
   hDs1MuBPT->Write();
   hDs1TauVChi2->Write();
   hDs1MuVChi2->Write();
   hDs1TauDsVChi2->Write();
   hDs1MuDsVChi2->Write();
   hDs1TauDOCA->Write();
   hDs1MuDOCA->Write();
   hDs1TauDsMass->Write();
   hDs1MuDsMass->Write();
   hDs1TauDIRA->Write();
   hDs1MuDIRA->Write();
   hDs1TauFD->Write();
   hDs1MuFD->Write();
   hDs1TauIP->Write();
   hDs1MuIP->Write();
   hDs1TauMuP->Write();
   hDs1MuMuP->Write();
   hDs1TauDsPT->Write();
   hDs1MuDsPT->Write();
   hDs1TauMuP->Write();
   hDs1TauMuPT->Write();
   hDs1MuMuP->Write();
   hDs1MuMuPT->Write();
   hDs1TauDsP->Write();
   hDs1MuDsP->Write();
   hDs1TauDsPT->Write();
   hDs1MuDsPT->Write();

   hDsprTauCorrMass->Write();
   hDsprMuCorrMass->Write();
   hDsprTauCorrMassErr->Write();
   hDsprMuCorrMassErr->Write();
   hDsprTauBP->Write();
   hDsprMuBP->Write();
   hDsprTauBPT->Write();
   hDsprMuBPT->Write();
   hDsprTauVChi2->Write();
   hDsprMuVChi2->Write();
   hDsprTauDsVChi2->Write();
   hDsprMuDsVChi2->Write();
   hDsprTauDOCA->Write();
   hDsprMuDOCA->Write();
   hDsprTauDsMass->Write();
   hDsprMuDsMass->Write();
   hDsprTauDIRA->Write();
   hDsprMuDIRA->Write();
   hDsprTauFD->Write();
   hDsprMuFD->Write();
   hDsprTauIP->Write();
   hDsprMuIP->Write();
   hDsprTauMuP->Write();
   hDsprMuMuP->Write();
   hDsprTauDsPT->Write();
   hDsprMuDsPT->Write();
   hDsprTauMuP->Write();
   hDsprTauMuPT->Write();
   hDsprMuMuP->Write();
   hDsprMuMuPT->Write();
   hDsprTauDsP->Write();
   hDsprMuDsP->Write();
   hDsprTauDsPT->Write();
   hDsprMuDsPT->Write();

}
