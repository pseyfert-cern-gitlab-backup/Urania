#define MCNeutralAll_cxx
#include "MCNeutralAll.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void MCNeutralAll::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L MCNeutralAll.C
//      Root > MCNeutralAll t
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

   TFile *f = new TFile("histosNeutralReco_MC_All_Veto.root","new");
   int nbinsMu = 80;
   float minGamma = 1950.0;
   float maxGamma = 2400.0;
   float minPi0 = 1950.0;
   float maxPi0 = 2600.0;
   float minPi0G = 2000.0;
   float maxPi0G = 3000.0;
   float MassDsPDG = 1968.30;
   float MassPi0PDG = 134.9766;

   // photon mass histograms
   TH1F *hDsMuMassFirstG04 = new TH1F("DsMuMassFirstG04", "DsMuNu Ds Mass with first photon 0.4", nbinsMu, minGamma, maxGamma);
   TH1F *hDsMuMassSecondG04 = new TH1F("DsMuMassSecondG04", "DsMuNu Ds Mass with second photon 0.4", nbinsMu, minGamma, maxGamma);
   TH1F *hDsMuMassThirdG04 = new TH1F("DsMuMassThirdG04", "DsMuNu Ds Mass with third photon 0.4", nbinsMu, minGamma, maxGamma);

   // pi0 mass histograms
   TH1F *hDsMuMassFirstPi004 = new TH1F("DsMuMassFirstPi004", "DsMuNu Ds Mass with first pi0 0.4", nbinsMu/1.5, minPi0, maxPi0);
   TH1F *hDsMuMassSecondPi004 = new TH1F("DsMuMassSecondPi004", "DsMuNu Ds Mass with second pi0 0.4", nbinsMu/1.5, minPi0, maxPi0);
   TH1F *hDsMuMassThirdPi004 = new TH1F("DsMuMassThirdPi004", "DsMuNu Ds Mass with third pi0 0.4", nbinsMu/1.5, minPi0, maxPi0);  
   TH1F *hCLFirstPi004 = new TH1F("CLFirstPi004", "Pi0 CL", nbinsMu, 0.0, 1.0);
   TH1F *hG1CLFirstPi004 = new TH1F("G1CLFirstPi004", "g1 CL", nbinsMu, 0.0, 1.0);
   TH1F *hG2CLFirstPi004 = new TH1F("G2CLFirstPi004", "g2 CL", nbinsMu, 0.0, 1.0);
   TH1F *hG1EFirstPi004 = new TH1F("G1EFirstPi004", "gamma 1 energy", nbinsMu, 0.0, 50000.0);
   TH1F *hG2EFirstPi004 = new TH1F("G2EFirstPi004", "gamma 2 energy", nbinsMu, 0.0, 50000.0);
   TH1F *hG1ETFirstPi004 = new TH1F("G1ETFirstPi004", "gamma 1 transverse energy", nbinsMu, 0.0, 5000.0);
   TH1F *hG2ETFirstPi004 = new TH1F("G2ETFirstPi004", "gamma 2 transverse energy", nbinsMu, 0.0, 5000.0);
   TH1F *hAsymEFirstPi004 = new TH1F("AsymEFirstPi004", "asymE", nbinsMu, -1.0, 1.0);
   TH1F *hAsymETFirstPi004 = new TH1F("AsymETFirstPi004", "asymET", nbinsMu, -1.0, 1.0);
   TH1F *hPi0MassWithCL = new TH1F("Pi0MassWithCL", "Pi0 mass with CL", nbinsMu, 50., 200.);
   TH1F *hPi0MassNoCL = new TH1F("Pi0MassNoCL", "Pi0 mass no CL", nbinsMu, 50., 200.);
   TH1F *hPi0MassAntiCL = new TH1F("Pi0MassAntiCL", "Pi0 mass anti CL", nbinsMu, 50., 200.);

   // pi0 gamma mass histograms
   TH1F *hDsMuMassFirstPi0G04 = new TH1F("DsMuMassFirstPi0G04", "DsMuNu Ds Mass with first pi0gamma 0.4", nbinsMu/2.0, minPi0G, maxPi0G);
   TH1F *hDsMuMassSecondPi0G04 = new TH1F("DsMuMassSecondPi0G04", "DsMuNu Ds Mass with second pi0gamma 0.4", nbinsMu/2.0, minPi0G, maxPi0G);
   TH1F *hDsMuMassThirdPi0G04 = new TH1F("DsMuMassThirdPi0G04", "DsMuNu Ds Mass with third pi0gamma 0.4", nbinsMu/2.0, minPi0G, maxPi0G);

   int nMCMatchG = 0;
   int nMCMatchPi0 = 0;
   int nMCMatchPi0G = 0;
   int nCuts = 0;
   int nPhysTrigger = 0;
   int nTrigger = 0;
   int nCutsMu = 0;
   int nCutsDsstMu = 0;
   int nCutsDs0Mu = 0;
   int nCutsTau = 0;
   int nCutsDsstTau = 0;
   int nCutsDs0Tau = 0;
   int nPhotonFirst040 = 0;
   int nPhotonSecond040 = 0;
   int nPhotonThird040 = 0;
   int nPi0First040 = 0;
   int nPi0Second040 = 0;
   int nPi0Third040 = 0;
   int nPi0GFirst040 = 0;
   int nPi0GSecond040 = 0;
   int nPi0GThird040 = 0;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if (ientry%100000==0) std::cout << "Analysing event " << ientry << std::endl; 
      if(Bs_0_L0Global_Dec==1 && Bs_0_Hlt1Phys_Dec==1 && Bs_0_Hlt2Phys_Dec==1){
        nPhysTrigger += 1;  
        // Emulate the trigger decision
        if(Kpl_P>5000 && Kmi_P>5000 && pi_P>5000 && (Kpl_PT>800 || Kmi_PT>800 || pi_PT>800) && Ds_PT>2000 && Bs_0_BDTS_DOCA<0.50 && Bs_0_FDCHI2_TOPPV>50 && Ds_MM>1920 && Ds_MM<2010){
          nTrigger += 1;
          // Tau decays 
          if(abs(mu_MC_GD_MOTHER_ID) == 531 && abs(mu_TRUEID) == 13 && abs(mu_MC_MOTHER_ID) == 15){
            if(Bs_0_MCORR<8000 && Bs_0_MCORR>3000 && Ds_MM>1950 && Ds_MM<1990 && mu_PT>1000 && mu_ProbNNmu>0.3 && sqrt( pow((Ds_PE+mu_PE),2) - ( pow(Ds_PX+mu_PX,2) + pow(Ds_PY+mu_PY,2) + pow(Ds_PZ+mu_PZ,2)) )>3000 ) {
              if(abs(Ds_MC_MOTHER_ID) == 531 && abs(Ds_TRUEID) == 431){
                nCutsTau += 1;  
              }
              if(abs(Ds_MC_MOTHER_ID) == 433 && abs(Ds_TRUEID) == 431 && abs(Ds_MC_GD_MOTHER_ID) == 531){
                nCutsDsstTau += 1;
              }
              if(abs(Ds_MC_MOTHER_ID) == 10431 && abs(Ds_TRUEID) == 431 && abs(Ds_MC_GD_MOTHER_ID) == 531){
                nCutsDs0Tau += 1;
              } 
            }
          }
          // Mu decays
          if(abs(mu_MC_MOTHER_ID) == 531 && abs(mu_TRUEID) == 13){
            // Remove the tau component and add trigger selection
            if(Bs_0_MCORR<8000 && Bs_0_MCORR>3000 && Ds_MM>1950 && Ds_MM<1990 && mu_PT>1000 && mu_ProbNNmu>0.3 && sqrt( pow((Ds_PE+mu_PE),2) - ( pow(Ds_PX+mu_PX,2) + pow(Ds_PY+mu_PY,2) + pow(Ds_PZ+mu_PZ,2)) )>3000 ) {
              nCuts += 1;
              // DsMuNu decays
              if(abs(Ds_MC_MOTHER_ID) == 531 && abs(Ds_TRUEID) == 431){
                nCutsMu += 1;
              }
              if(abs(Ds_MC_MOTHER_ID) == 433 && abs(Ds_TRUEID) == 431 && abs(Ds_MC_GD_MOTHER_ID) == 531){
                nCutsDsstMu += 1;
              }
              if(abs(Ds_MC_MOTHER_ID) == 10431 && abs(Ds_TRUEID) == 431 && abs(Ds_MC_GD_MOTHER_ID) == 531){
                nCutsDs0Mu += 1;
              }
              // Ds*MuNu decays
              if(abs(Ds_MC_MOTHER_ID) == 433 && abs(Ds_TRUEID) == 431 && abs(Ds_MC_GD_MOTHER_ID) == 531){
                nMCMatchG += 1;
                if(Ds_0_40_nc_mult>0 and sqrt(pow(Ds_0_40_nc_maxPt_PX,2)+pow(Ds_0_40_nc_maxPt_PY,2))>0 and Ds_0_40_nc_CL > 0.6){
                  nPhotonFirst040 += 1;
                  float MassDsG1_0_40 = sqrt( pow((Ds_0_40_nc_maxPt_PE+Ds_PE),2) - ( pow(Ds_0_40_nc_maxPt_PX+Ds_PX,2)+pow(Ds_0_40_nc_maxPt_PY+Ds_PY,2)+pow(Ds_0_40_nc_maxPt_PZ+Ds_PZ,2) ) );
                  hDsMuMassFirstG04->Fill(MassDsG1_0_40-Ds_MM+MassDsPDG);
                }
                if(Ds_0_40_nc_mult>1 and sqrt(pow(Ds_0_40_nc_secPt_PX,2)+pow(Ds_0_40_nc_secPt_PY,2))>0 and Ds_0_40_nc_CL > 0.6){
                  nPhotonSecond040 += 1; 
                  float MassDsG2_0_40 = sqrt( pow((Ds_0_40_nc_secPt_PE+Ds_PE),2) - ( pow(Ds_0_40_nc_secPt_PX+Ds_PX,2)+pow(Ds_0_40_nc_secPt_PY+Ds_PY,2)+pow(Ds_0_40_nc_secPt_PZ+Ds_PZ,2) ) );
                  hDsMuMassSecondG04->Fill(MassDsG2_0_40-Ds_MM+MassDsPDG);
                }
                if(Ds_0_40_nc_mult>2 and sqrt(pow(Ds_0_40_nc_thiPt_PX,2)+pow(Ds_0_40_nc_thiPt_PY,2))>0 and Ds_0_40_nc_CL > 0.6){
                  nPhotonThird040 += 1;
                  float MassDsG3_0_40 = sqrt( pow((Ds_0_40_nc_thiPt_PE+Ds_PE),2) - ( pow(Ds_0_40_nc_thiPt_PX+Ds_PX,2)+pow(Ds_0_40_nc_thiPt_PY+Ds_PY,2)+pow(Ds_0_40_nc_thiPt_PZ+Ds_PZ,2) ) );
                  hDsMuMassThirdG04->Fill(MassDsG3_0_40-Ds_MM+MassDsPDG);
                }        
              }
              // Ds0(2317)MuNu decays  
              if(abs(Ds_MC_MOTHER_ID) == 10431 && abs(Ds_TRUEID) == 431 && abs(Ds_MC_GD_MOTHER_ID) == 531){
                nMCMatchPi0 += 1;
                if(Ds_0_40_pi0_mult>0 and sqrt(pow(Ds_0_40_pi0_maxPt_PX,2)+pow(Ds_0_40_pi0_maxPt_PY,2))>0 and Ds_0_40_pi0_maxPt_MM>0.){
                  hCLFirstPi004->Fill(Ds_0_40_pi0_CL);
                  hG1CLFirstPi004->Fill(Ds_0_40_g1_CL);
                  hG2CLFirstPi004->Fill(Ds_0_40_g2_CL);  
                  float E1 = sqrt(pow(Ds_0_40_g1maxPt_PX,2)+pow(Ds_0_40_g1maxPt_PY,2)+pow(Ds_0_40_g1maxPt_PZ,2));
                  float E2 = sqrt(pow(Ds_0_40_g2maxPt_PX,2)+pow(Ds_0_40_g2maxPt_PY,2)+pow(Ds_0_40_g2maxPt_PZ,2));
                  float ET1 = sqrt(pow(Ds_0_40_g1maxPt_PX,2)+pow(Ds_0_40_g1maxPt_PY,2));
                  float ET2 = sqrt(pow(Ds_0_40_g2maxPt_PX,2)+pow(Ds_0_40_g2maxPt_PY,2));
                  hG1EFirstPi004->Fill(E1);
                  hG2EFirstPi004->Fill(E2);
                  hG1ETFirstPi004->Fill(ET1);
                  hG2ETFirstPi004->Fill(ET2);
                  hAsymEFirstPi004->Fill((E1-E2)/(E1+E2));
                  hAsymETFirstPi004->Fill((ET1-ET2)/(ET1+ET2));
                  if(Ds_0_40_g1_CL>0.6 && Ds_0_40_g2_CL>0.6){
                    hPi0MassWithCL->Fill(Ds_0_40_pi0_maxPt_MM);
                  }
                  if((Ds_0_40_g1_CL<0.6 || Ds_0_40_g2_CL<0.6)){
                    hPi0MassAntiCL->Fill(Ds_0_40_pi0_maxPt_MM);
                  }
                  hPi0MassNoCL->Fill(Ds_0_40_pi0_maxPt_MM);
                }
                if(Ds_0_40_pi0_mult>0 and sqrt(pow(Ds_0_40_pi0_maxPt_PX,2)+pow(Ds_0_40_pi0_maxPt_PY,2))>0 and abs(Ds_0_40_pi0_maxPt_MM-MassPi0PDG)<20 and Ds_0_40_g1_CL > 0.6 and Ds_0_40_g2_CL > 0.6){
                  nPi0First040 += 1;
                  float MassDsPi01_0_40 = sqrt( pow((Ds_0_40_pi0_maxPt_PE+Ds_PE),2) - ( pow(Ds_0_40_pi0_maxPt_PX+Ds_PX,2)+pow(Ds_0_40_pi0_maxPt_PY+Ds_PY,2)+pow(Ds_0_40_pi0_maxPt_PZ+Ds_PZ,2) ) );
                  hDsMuMassFirstPi004->Fill(MassDsPi01_0_40-Ds_MM+MassDsPDG);
                }
                if(Ds_0_40_pi0_mult>1 and sqrt(pow(Ds_0_40_pi0_secPt_PX,2)+pow(Ds_0_40_pi0_secPt_PY,2))>0 and abs(Ds_0_40_pi0_secPt_MM-MassPi0PDG)<20 and Ds_0_40_g1_CL > 0.6 and Ds_0_40_g2_CL > 0.6){
                  nPi0Second040 += 1;
                  float MassDsPi02_0_40 = sqrt( pow((Ds_0_40_pi0_secPt_PE+Ds_PE),2) - ( pow(Ds_0_40_pi0_secPt_PX+Ds_PX,2)+pow(Ds_0_40_pi0_secPt_PY+Ds_PY,2)+pow(Ds_0_40_pi0_secPt_PZ+Ds_PZ,2) ) );
                  hDsMuMassSecondPi004->Fill(MassDsPi02_0_40-Ds_MM+MassDsPDG);
                }
                if(Ds_0_40_pi0_mult>2 and sqrt(pow(Ds_0_40_pi0_thiPt_PX,2)+pow(Ds_0_40_pi0_thiPt_PY,2))>0 and abs(Ds_0_40_pi0_thiPt_MM-MassPi0PDG)<20 and Ds_0_40_g1_CL > 0.6 and Ds_0_40_g2_CL > 0.6){
                  nPi0Third040 += 1;
                  float MassDsPi03_0_40 = sqrt( pow((Ds_0_40_pi0_thiPt_PE+Ds_PE),2) - ( pow(Ds_0_40_pi0_thiPt_PX+Ds_PX,2)+pow(Ds_0_40_pi0_thiPt_PY+Ds_PY,2)+pow(Ds_0_40_pi0_thiPt_PZ+Ds_PZ,2) ) );
                  hDsMuMassThirdPi004->Fill(MassDsPi03_0_40-Ds_MM+MassDsPDG);
                }
              }
              // Ds1(2536)MuNu decays
              if(abs(Ds_MC_MOTHER_ID) == 10433 && abs(Ds_TRUEID) == 431 && abs(Ds_MC_GD_MOTHER_ID) == 531){
                nMCMatchPi0G += 1;
                if(Ds_0_40_trig_mult>0 and sqrt(pow(Ds_0_40_trig_maxPt_PX,2)+pow(Ds_0_40_trig_maxPt_PY,2))>0 and abs(Ds_0_40_trig_maxPt_MM-MassPi0PDG)<20 and Ds_0_40_sCL > 0.6 and Ds_0_40_sCL > 0.6 and Ds_0_40_tCL > 0.6){
                  nPi0GFirst040 += 1;
                  float MassDsPi0G1_0_40 = sqrt( pow(((sqrt(pow(Ds_0_40_trig_maxPt_MM,2)+pow(Ds_0_40_trig_maxPt_PX,2)+pow(Ds_0_40_trig_maxPt_PY,2)+pow(Ds_0_40_trig_maxPt_PZ,2)))+Ds_PE),2) - ( pow(Ds_0_40_trig_maxPt_PX+Ds_PX,2)+pow(Ds_0_40_trig_maxPt_PY+Ds_PY,2)+pow(Ds_0_40_trig_maxPt_PZ+Ds_PZ,2) ) );
                  hDsMuMassFirstPi0G04->Fill(MassDsPi0G1_0_40-Ds_MM+MassDsPDG);
                }
                if(Ds_0_40_trig_mult>1 and sqrt(pow(Ds_0_40_trig_secPt_PX,2)+pow(Ds_0_40_trig_secPt_PY,2))>0 and abs(Ds_0_40_trig_secPt_MM-MassPi0PDG)<20 and Ds_0_40_sCL > 0.6 and Ds_0_40_sCL > 0.6 and Ds_0_40_tCL > 0.6){
                  nPi0GSecond040 += 1;
                  float MassDsPi0G2_0_40 = sqrt( pow(((sqrt(pow(Ds_0_40_trig_secPt_MM,2)+pow(Ds_0_40_trig_secPt_PX,2)+pow(Ds_0_40_trig_secPt_PY,2)+pow(Ds_0_40_trig_secPt_PZ,2)))+Ds_PE),2) - ( pow(Ds_0_40_trig_secPt_PX+Ds_PX,2)+pow(Ds_0_40_trig_secPt_PY+Ds_PY,2)+pow(Ds_0_40_trig_secPt_PZ+Ds_PZ,2) ) );
                   hDsMuMassSecondPi0G04->Fill(MassDsPi0G2_0_40-Ds_MM+MassDsPDG);
                }
                if(Ds_0_40_trig_mult>2 and sqrt(pow(Ds_0_40_trig_thiPt_PX,2)+pow(Ds_0_40_trig_thiPt_PY,2))>0 and abs(Ds_0_40_trig_thiPt_MM-MassPi0PDG)<20 and Ds_0_40_sCL > 0.6 and Ds_0_40_sCL > 0.6 and Ds_0_40_tCL > 0.6){
                  nPi0GThird040 += 1;
                  float MassDsPi0G3_0_40 = sqrt( pow(((sqrt(pow(Ds_0_40_trig_thiPt_MM,2)+pow(Ds_0_40_trig_thiPt_PX,2)+pow(Ds_0_40_trig_thiPt_PY,2)+pow(Ds_0_40_trig_thiPt_PZ,2)))+Ds_PE),2) - ( pow(Ds_0_40_trig_thiPt_PX+Ds_PX,2)+pow(Ds_0_40_trig_thiPt_PY+Ds_PY,2)+pow(Ds_0_40_trig_thiPt_PZ+Ds_PZ,2) ) );
                  hDsMuMassThirdPi0G04->Fill(MassDsPi0G3_0_40-Ds_MM+MassDsPDG);
                }
              }
            }   
          }
        }
      }
   }

   std::cout << "Number of events after Phys Trigger = " << nPhysTrigger << std::endl;
   std::cout << "Number of events after Trigger = " << nTrigger << std::endl;
   std::cout << "Number of events after Cuts = " << nCuts << std::endl;
   std::cout << "Number of events after MCmatch G = " << nMCMatchG << std::endl;
   std::cout << "Number of events after MCmatch Pi0 = " << nMCMatchPi0 << std::endl;
   std::cout << "Number of events after MCmatch Pi0 G = " << nMCMatchPi0G << std::endl;
   std::cout << "Number of events after first Photon pT and CL = " << nPhotonFirst040 << std::endl;
   std::cout << "Number of events after second Photon pT and CL = " << nPhotonSecond040 << std::endl;
   std::cout << "Number of events after third Photon pT and CL = " << nPhotonThird040 << std::endl;
   std::cout << "Number of events after first Pi0 pT and CL = " << nPi0First040 << std::endl;
   std::cout << "Number of events after second Pi0 pT and CL = " << nPi0Second040 << std::endl;
   std::cout << "Number of events after third Pi0 pT and CL = " << nPi0Third040 << std::endl;
   std::cout << "Number of events after first Pi0G pT and CL = " << nPi0GFirst040 << std::endl;
   std::cout << "Number of events after second Pi0G pT and CL = " << nPi0GSecond040 << std::endl;
   std::cout << "Number of events after third Pi0G pT and CL = " << nPi0GThird040 << std::endl;
   std::cout << "#########################################################" << std::endl;
   std::cout << "N(Bs->DsMuNu) = " << nCutsMu << std::endl;
   std::cout << "N(Bs->Ds*MuNu) = " << nCutsDsstMu << std::endl;
   std::cout << "N(Bs->Ds0MuNu) = " << nCutsDs0Mu << std::endl;
   std::cout << "N(Bs->DsTauNu) = " << nCutsTau << std::endl;
   std::cout << "N(Bs->Ds*TauNu) = " << nCutsDsstTau << std::endl;
   std::cout << "N(Bs->Ds0TauNu) = " << nCutsDs0Tau << std::endl;


   hDsMuMassFirstG04->Write();
   hDsMuMassSecondG04->Write();
   hDsMuMassThirdG04->Write();

   hDsMuMassFirstPi004->Write();
   hDsMuMassSecondPi004->Write();
   hDsMuMassThirdPi004->Write();
   hCLFirstPi004->Write();
   hG1CLFirstPi004->Write();
   hG2CLFirstPi004->Write();
   hG1EFirstPi004->Write();
   hG2EFirstPi004->Write();
   hAsymEFirstPi004->Write();
   hAsymETFirstPi004->Write();
   hPi0MassWithCL->Write();
   hPi0MassAntiCL->Write();
   hPi0MassNoCL->Write();

   hDsMuMassFirstPi0G04->Write();
   hDsMuMassSecondPi0G04->Write();
   hDsMuMassThirdPi0G04->Write();

}
