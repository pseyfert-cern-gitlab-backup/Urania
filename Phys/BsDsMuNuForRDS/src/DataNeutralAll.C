#define DataNeutralAll_cxx
#include "DataNeutralAll.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void DataNeutralAll::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L DataNeutralAll.C
//      Root > DataNeutralAll t
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

   TFile *f = new TFile("histosNeutralReco_Data_All_Veto.root","new");
   int nbinsMu = 80;
   float minGamma = 1950.0;
   float maxGamma = 2400.0;
   float minPi0 = 2050.0;
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
 
   // pi0 gamma mass histograms
   TH1F *hDsMuMassFirstPi0G04 = new TH1F("DsMuMassFirstPi0G04", "DsMuNu Ds Mass with first pi0gamma 0.4", nbinsMu/2.0, minPi0G, maxPi0G);
   TH1F *hDsMuMassSecondPi0G04 = new TH1F("DsMuMassSecondPi0G04", "DsMuNu Ds Mass with second pi0gamma 0.4", nbinsMu/2.0, minPi0G, maxPi0G);
   TH1F *hDsMuMassThirdPi0G04 = new TH1F("DsMuMassThirdPi0G04", "DsMuNu Ds Mass with third pi0gamma 0.4", nbinsMu/2.0, minPi0G, maxPi0G);

   int nTrigger = 0;
   int nTriggerXc = 0;
   int nCuts = 0;
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
      if(Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS==1){
        nTriggerXc += 1;
      }
      // Emulate the trigger decision
      if(Kpl_P>5000 && Kmi_P>5000 && pi_P>5000 && (Kpl_PT>800 || Kmi_PT>800 || pi_PT>800) && Ds_PT>2000 && Bs_0_BDTS_DOCA<0.50 && Bs_0_FDCHI2_TOPPV>50 && Ds_MM>1920 && Ds_MM<2010){
        nTrigger += 1;
        // Remove the tau component
        if(Bs_0_MCORR<8000 && Bs_0_MCORR>3000 && Ds_MM>1950 && Ds_MM<1990 && mu_PT>1000 && mu_ProbNNmu>0.3 && sqrt( pow((Ds_PE+mu_PE),2) - ( pow(Ds_PX+mu_PX,2) + pow(Ds_PY+mu_PY,2) + pow(Ds_PZ+mu_PZ,2)) )>3000) {
          nCuts += 1;
          // Ds*MuNu decays
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
          // Ds0(2317)MuNu decays  
          if(Ds_0_40_pi0_mult>0 and sqrt(pow(Ds_0_40_pi0_maxPt_PX,2)+pow(Ds_0_40_pi0_maxPt_PY,2))>0 and abs(Ds_0_40_pi0_maxPt_MM-MassPi0PDG)<20 and Ds_0_40_g1_CL>0.6 and Ds_0_40_g2_CL>0.6){
            nPi0First040 += 1;
            float MassDsPi01_0_40 = sqrt( pow((Ds_0_40_pi0_maxPt_PE+Ds_PE),2) - ( pow(Ds_0_40_pi0_maxPt_PX+Ds_PX,2)+pow(Ds_0_40_pi0_maxPt_PY+Ds_PY,2)+pow(Ds_0_40_pi0_maxPt_PZ+Ds_PZ,2) ) );
            hDsMuMassFirstPi004->Fill(MassDsPi01_0_40-Ds_MM+MassDsPDG);
          }
          if(Ds_0_40_pi0_mult>1 and sqrt(pow(Ds_0_40_pi0_secPt_PX,2)+pow(Ds_0_40_pi0_secPt_PY,2))>0 and abs(Ds_0_40_pi0_secPt_MM-MassPi0PDG)<20 and Ds_0_40_g1_CL>0.6 and Ds_0_40_g2_CL>0.6){
            nPi0Second040 += 1;
            float MassDsPi02_0_40 = sqrt( pow((Ds_0_40_pi0_secPt_PE+Ds_PE),2) - ( pow(Ds_0_40_pi0_secPt_PX+Ds_PX,2)+pow(Ds_0_40_pi0_secPt_PY+Ds_PY,2)+pow(Ds_0_40_pi0_secPt_PZ+Ds_PZ,2) ) );
            hDsMuMassSecondPi004->Fill(MassDsPi02_0_40-Ds_MM+MassDsPDG);
          }
          if(Ds_0_40_pi0_mult>2 and sqrt(pow(Ds_0_40_pi0_thiPt_PX,2)+pow(Ds_0_40_pi0_thiPt_PY,2))>0 and abs(Ds_0_40_pi0_thiPt_MM-MassPi0PDG)<20 and Ds_0_40_g1_CL>0.6 and Ds_0_40_g2_CL>0.6){
            nPi0Third040 += 1;
            float MassDsPi03_0_40 = sqrt( pow((Ds_0_40_pi0_thiPt_PE+Ds_PE),2) - ( pow(Ds_0_40_pi0_thiPt_PX+Ds_PX,2)+pow(Ds_0_40_pi0_thiPt_PY+Ds_PY,2)+pow(Ds_0_40_pi0_thiPt_PZ+Ds_PZ,2) ) );
            hDsMuMassThirdPi004->Fill(MassDsPi03_0_40-Ds_MM+MassDsPDG);
          }
          // Ds1(2536)MuNu decays
          if(Ds_0_40_trig_mult>0 and sqrt(pow(Ds_0_40_trig_maxPt_PX,2)+pow(Ds_0_40_trig_maxPt_PY,2))>0 and abs(Ds_0_40_trig_maxPt_MM-MassPi0PDG)<20 and Ds_0_40_fCL > 0.6 and Ds_0_40_sCL > 0.6){
            nPi0GFirst040 += 1;
            float MassDsPi0G1_0_40 = sqrt( pow(((sqrt(pow(Ds_0_40_trig_maxPt_MM,2)+pow(Ds_0_40_trig_maxPt_PX,2)+pow(Ds_0_40_trig_maxPt_PY,2)+pow(Ds_0_40_trig_maxPt_PZ,2)))+Ds_PE),2) - ( pow(Ds_0_40_trig_maxPt_PX+Ds_PX,2)+pow(Ds_0_40_trig_maxPt_PY+Ds_PY,2)+pow(Ds_0_40_trig_maxPt_PZ+Ds_PZ,2) ) );
            hDsMuMassFirstPi0G04->Fill(MassDsPi0G1_0_40-Ds_MM+MassDsPDG);
          }
          if(Ds_0_40_trig_mult>1 and sqrt(pow(Ds_0_40_trig_secPt_PX,2)+pow(Ds_0_40_trig_secPt_PY,2))>0 and abs(Ds_0_40_trig_secPt_MM-MassPi0PDG)<20 and Ds_0_40_fCL > 0.6 and Ds_0_40_sCL > 0.6){
            nPi0GSecond040 += 1;
            float MassDsPi0G2_0_40 = sqrt( pow(((sqrt(pow(Ds_0_40_trig_secPt_MM,2)+pow(Ds_0_40_trig_secPt_PX,2)+pow(Ds_0_40_trig_secPt_PY,2)+pow(Ds_0_40_trig_secPt_PZ,2)))+Ds_PE),2) - ( pow(Ds_0_40_trig_secPt_PX+Ds_PX,2)+pow(Ds_0_40_trig_secPt_PY+Ds_PY,2)+pow(Ds_0_40_trig_secPt_PZ+Ds_PZ,2) ) );
            hDsMuMassSecondPi0G04->Fill(MassDsPi0G2_0_40-Ds_MM+MassDsPDG);
          }
          if(Ds_0_40_trig_mult>2 and sqrt(pow(Ds_0_40_trig_thiPt_PX,2)+pow(Ds_0_40_trig_thiPt_PY,2))>0 and abs(Ds_0_40_trig_thiPt_MM-MassPi0PDG)<20 and Ds_0_40_fCL > 0.6 and Ds_0_40_sCL > 0.6){
            nPi0GThird040 += 1;
            float MassDsPi0G3_0_40 = sqrt( pow(((sqrt(pow(Ds_0_40_trig_thiPt_MM,2)+pow(Ds_0_40_trig_thiPt_PX,2)+pow(Ds_0_40_trig_thiPt_PY,2)+pow(Ds_0_40_trig_thiPt_PZ,2)))+Ds_PE),2) - ( pow(Ds_0_40_trig_thiPt_PX+Ds_PX,2)+pow(Ds_0_40_trig_thiPt_PY+Ds_PY,2)+pow(Ds_0_40_trig_thiPt_PZ+Ds_PZ,2) ) );
            hDsMuMassThirdPi0G04->Fill(MassDsPi0G3_0_40-Ds_MM+MassDsPDG);
          }
        }
     }
   }

   std::cout << "Number of events after emulated trigger = " << nTrigger << std::endl;
   std::cout << "Number of events after trigger Xc = " << nTriggerXc << std::endl;
   std::cout << "Number of events after Cuts = " << nCuts << std::endl;
   std::cout << "Number of events after first Photon pT and CL = " << nPhotonFirst040 << std::endl;
   std::cout << "Number of events after second Photon pT and CL = " << nPhotonSecond040 << std::endl;
   std::cout << "Number of events after third Photon pT and CL = " << nPhotonThird040 << std::endl;
   std::cout << "Number of events after first Pi0 pT and CL = " << nPi0First040 << std::endl;
   std::cout << "Number of events after second Pi0 pT and CL = " << nPi0Second040 << std::endl;
   std::cout << "Number of events after third Pi0 pT and CL = " << nPi0Third040 << std::endl;
   std::cout << "Number of events after first Pi0G pT and CL = " << nPi0GFirst040 << std::endl;
   std::cout << "Number of events after second Pi0G pT and CL = " << nPi0GSecond040 << std::endl;
   std::cout << "Number of events after third Pi0G pT and CL = " << nPi0GThird040 << std::endl;


   hDsMuMassFirstG04->Write();
   hDsMuMassSecondG04->Write();
   hDsMuMassThirdG04->Write();

   hDsMuMassFirstPi004->Write();
   hDsMuMassSecondPi004->Write();
   hDsMuMassThirdPi004->Write();
   
   hDsMuMassFirstPi0G04->Write();
   hDsMuMassSecondPi0G04->Write();
   hDsMuMassThirdPi0G04->Write();

}
