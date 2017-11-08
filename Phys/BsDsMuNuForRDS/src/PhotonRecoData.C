#define PhotonRecoData_cxx
#include "PhotonRecoData.h"
#include <TH2.h>
#include <TEventList.h>
#include <TStyle.h>
#include <TCanvas.h>

void PhotonRecoData::Loop()
{
// #################
// ##### INFO ######  
// This code makes the distribution of ithe invariant mass of Ds+gamma for different cone sizes and different photons 
// using data
// ################# 
  
//   In a ROOT session, you can do:
//      root> .L PhotonRecoData.C
//      root> PhotonRecoData t
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

   //TFile *f2 = TFile::Open("root://eoslhcb.cern.ch///eos/lhcb/user/s/sogilvy/RDs/FriendTrees/DataMagUp_S24_RDS_FromTauMu.root");
   //TTree *t2 = (TTree*)f2->Get("B2DsMuNuTuple/DecayTree");

   // The cutstring.
   //TCut c = "(resFlag == 0 && (((TMath::Abs(3096.916000 - WM_Jpsi_piasmu) > 50.0 || pi_isMuon==0)) && ((WM_Dst_FullReco > 190)) && ((WM_Dst_SSKaspi_fromDz > 190)) && ((TMath::Abs(2286.460000 - WM_Lc_SSKasproton) > 33 || (SSK_PIDK - SSK_PIDp) > 7)) && (1) && ((WM_Dst_SSKaspi_fromDst > 190)) && ((TMath::Abs(3096.916000 - WM_Jpsi_SSKasmu) > 50.0  || SSK_isMuon==0)) ) && ((1)) ) || (resFlag == 1 && (((TMath::Abs(3096.916000 - WM_Jpsi_piasmu) > 50.0 || pi_isMuon==0)) && ((WM_Dst_FullReco > 190)) && ((WM_Dst_SSKaspi_fromDz > 190)) && ((TMath::Abs(2286.460000 - WM_Lc_SSKasproton) > 33 || (SSK_PIDK - SSK_PIDp) > 10)) && (((TMath::Abs(1869.570000 - WM_Dp_SSKaspi) > 30 && TMath::Abs(1968.300000 - WM_Dp_SSKaspi) > 30 ) || SSK_PIDK > 8) ) && ((WM_Dst_SSKaspi_fromDst > 190)) && ((TMath::Abs(3096.916000 - WM_Jpsi_SSKasmu) > 50.0  || SSK_isMuon==0)) ) && ((SSK_ProbNNk > 0.25 && OSK_ProbNNk > 0.25)) ) || (resFlag == 2 && (((TMath::Abs(3096.916000 - WM_Jpsi_piasmu) > 50.0 || pi_isMuon==0)) && ((WM_Dst_FullReco > 190)) && ((WM_Dst_SSKaspi_fromDz > 190)) && ((TMath::Abs(2286.460000 - WM_Lc_SSKasproton) > 33 || (SSK_PIDK - SSK_PIDp) > 12)) && (((TMath::Abs(1869.570000 - WM_Dp_SSKaspi) > 30 && TMath::Abs(1968.300000 - WM_Dp_SSKaspi) > 30 ) || SSK_PIDK > 8) ) && ((WM_Dst_SSKaspi_fromDst > 190)) && ((TMath::Abs(3096.916000 - WM_Jpsi_SSKasmu) > 50.0  || SSK_isMuon==0)) ) && ((SSK_ProbNNk > 0.3 && OSK_ProbNNk > 0.3 && pi_PIDK < 8)) )";

   // Use Steve's trees to make a TEventList object.
   //t2->Draw(">>myEventList", c);
   //TEventList *myEventList = (TEventList*)gDirectory->Get("myEventList");
     
   Long64_t nentries = fChain->GetEntries();
   std::cout << "total number of entries = " << nentries << std::endl;
   //TFile *f = new TFile("histosPhotonReco_Data_DsVeto_Up_DeltaM.root","new");
   TFile *f = new TFile("histosPhotonReco_Data_ResolvedPi0_Veto.root","new");

   int nbinsMu = 80;
   float MassDsPDG = 1968.30; 
   float MassPi0PDG = 134.9766;
   float MassPhotonPDG = 0.0;
   float mass;

   bool whichNeutral=1;
   if(whichNeutral==0) mass = MassPhotonPDG;
   if(whichNeutral==1) mass = MassPi0PDG;

   // DsMu histograms for combinatorial background
   TH1F *hDsMuComb08 = new TH1F("DsMuComb08", "DsMuNu combinatorial 0.8", nbinsMu, 1950, 2800);
   TH1F *hDsMuComb06 = new TH1F("DsMuComb06", "DsMuNu combinatorial 0.6", nbinsMu, 1950, 2600);
   TH1F *hDsMuComb04 = new TH1F("DsMuComb04", "DsMuNu combinatorial 0.4", nbinsMu, 1950, 2600);
   TH1F *hDsMuComb02 = new TH1F("DsMuComb02", "DsMuNu combinatorial 0.2", nbinsMu, 1950, 2600);

   // photon mass histograms
   TH1F *hDsMuMassWithFirstG08 = new TH1F("DsMuMassWithFirstG08", "DsMuNu Ds Mass with first photon 0.8", nbinsMu, 1950, 2800);
   TH1F *hDsMuMassWithFirstG06 = new TH1F("DsMuMassWithFirstG06", "DsMuNu Ds Mass with first photon 0.6", nbinsMu, 1950, 2600);
   TH1F *hDsMuMassWithFirstG04 = new TH1F("DsMuMassWithFirstG04", "DsMuNu Ds Mass with first photon 0.4", nbinsMu, 1950, 2600);
   TH1F *hPi0MassWithFirstG04 = new TH1F("Pi0MassWithFirstG04", "DsMuNu Pi0 Mass with first photon 0.4", nbinsMu, 100, 160);
   TH1F *hDsMuMassWithFirstG02 = new TH1F("DsMuMassWithFirstG02", "DsMuNu Ds Mass with first photon 0.2", nbinsMu, 1950, 2600);
   TH1F *hDsMuMassWithSecondG08 = new TH1F("DsMuMassWithSecondG08", "DsMuNu Ds Mass with second photon 0.8", nbinsMu, 1950, 2800);
   TH1F *hDsMuMassWithSecondG06 = new TH1F("DsMuMassWithSecondG06", "DsMuNu Ds Mass with second photon 0.6", nbinsMu, 1950, 2600);
   TH1F *hDsMuMassWithSecondG04 = new TH1F("DsMuMassWithSecondG04", "DsMuNu Ds Mass with second photon 0.4", nbinsMu, 1950, 2600);
   TH1F *hDsMuMassWithSecondG02 = new TH1F("DsMuMassWithSecondG02", "DsMuNu Ds Mass with second photon 0.2", nbinsMu, 1950, 2600);
   TH1F *hDsMuMassWithThirdG08 = new TH1F("DsMuMassWithThirdG08", "DsMuNu Ds Mass with third photon 0.8", nbinsMu, 1950, 2800);
   TH1F *hDsMuMassWithThirdG06 = new TH1F("DsMuMassWithThirdG06", "DsMuNu Ds Mass with third photon 0.6", nbinsMu, 1950, 2600);
   TH1F *hDsMuMassWithThirdG04 = new TH1F("DsMuMassWithThirdG04", "DsMuNu Ds Mass with third photon 0.4", nbinsMu, 1950, 2600);
   TH1F *hDsMuMassWithThirdG02 = new TH1F("DsMuMassWithThirdG02", "DsMuNu Ds Mass with third photon 0.2", nbinsMu, 1950, 2600);

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if (ientry%50000==0) std::cout << "Analysing event " << ientry << std::endl;
      // DsVeto
      //if (myEventList->Contains(ientry)) {
          
        if(Bs_0_MCORR<8000 && Bs_0_MCORR>3000 && Ds_MM>1950 && Ds_MM<1990 && mu_PT>1000 && mu_ProbNNmu>0.3 && sqrt( pow( (Ds_PE+mu_PE) ,2) - ( pow(Ds_PX+mu_PX,2) + pow(Ds_PY+mu_PY,2) + pow(Ds_PZ+mu_PZ,2)) )>3000 ) {
          // for combinatorial background
          if(Ds_0_80_nc_mult>0 and sqrt(pow(Ds_0_80_nc_maxPt_PX,2)+pow(Ds_0_80_nc_maxPt_PY,2))>0 and abs(Ds_0_80_nc_maxPt_MM-MassPi0PDG)>20 and abs(Ds_0_80_nc_maxPt_MM-MassPi0PDG)<40){
            float MassDsG1_0_80 = sqrt((pow((sqrt(Ds_0_80_nc_maxPt_PX*Ds_0_80_nc_maxPt_PX+Ds_0_80_nc_maxPt_PY*Ds_0_80_nc_maxPt_PY+Ds_0_80_nc_maxPt_PZ*Ds_0_80_nc_maxPt_PZ+mass*mass)+Ds_PE),2) ) - ( pow(Ds_0_80_nc_maxPt_PX+Ds_PX,2)+pow(Ds_0_80_nc_maxPt_PY+Ds_PY,2)+pow(Ds_0_80_nc_maxPt_PZ+Ds_PZ,2) ) );
            hDsMuComb08->Fill(MassDsG1_0_80-Ds_MM+MassDsPDG);
          } 
          if(Ds_0_60_nc_mult>0 and sqrt(pow(Ds_0_60_nc_maxPt_PX,2)+pow(Ds_0_60_nc_maxPt_PY,2))>0 and abs(Ds_0_60_nc_maxPt_MM-MassPi0PDG)>20 and abs(Ds_0_60_nc_maxPt_MM-MassPi0PDG)<40){
            float MassDsG1_0_60 = sqrt((pow((sqrt(Ds_0_60_nc_maxPt_PX*Ds_0_60_nc_maxPt_PX+Ds_0_60_nc_maxPt_PY*Ds_0_60_nc_maxPt_PY+Ds_0_60_nc_maxPt_PZ*Ds_0_60_nc_maxPt_PZ+mass*mass)+Ds_PE),2) ) - ( pow(Ds_0_60_nc_maxPt_PX+Ds_PX,2)+pow(Ds_0_60_nc_maxPt_PY+Ds_PY,2)+pow(Ds_0_60_nc_maxPt_PZ+Ds_PZ,2) ) );
            hDsMuComb06->Fill(MassDsG1_0_60-Ds_MM+MassDsPDG);
          }
          if(Ds_0_40_nc_mult>0 and sqrt(pow(Ds_0_40_nc_maxPt_PX,2)+pow(Ds_0_40_nc_maxPt_PY,2))>0 and abs(Ds_0_40_nc_maxPt_MM-MassPi0PDG)>20 and abs(Ds_0_40_nc_maxPt_MM-MassPi0PDG)<40){
            float MassDsG1_0_40 = sqrt((pow((sqrt(Ds_0_40_nc_maxPt_PX*Ds_0_40_nc_maxPt_PX+Ds_0_40_nc_maxPt_PY*Ds_0_40_nc_maxPt_PY+Ds_0_40_nc_maxPt_PZ*Ds_0_40_nc_maxPt_PZ+mass*mass)+Ds_PE),2) ) - ( pow(Ds_0_40_nc_maxPt_PX+Ds_PX,2)+pow(Ds_0_40_nc_maxPt_PY+Ds_PY,2)+pow(Ds_0_40_nc_maxPt_PZ+Ds_PZ,2) ) );
            hDsMuComb04->Fill(MassDsG1_0_40-Ds_MM+MassDsPDG);
          }
          if(Ds_0_20_nc_mult>0 and sqrt(pow(Ds_0_20_nc_maxPt_PX,2)+pow(Ds_0_20_nc_maxPt_PY,2))>0 and abs(Ds_0_20_nc_maxPt_MM-MassPi0PDG)>20 and abs(Ds_0_20_nc_maxPt_MM-MassPi0PDG)<40){
            float MassDsG1_0_20 = sqrt((pow((sqrt(Ds_0_20_nc_maxPt_PX*Ds_0_20_nc_maxPt_PX+Ds_0_20_nc_maxPt_PY*Ds_0_20_nc_maxPt_PY+Ds_0_20_nc_maxPt_PZ*Ds_0_20_nc_maxPt_PZ+mass*mass)+Ds_PE),2) ) - ( pow(Ds_0_20_nc_maxPt_PX+Ds_PX,2)+pow(Ds_0_20_nc_maxPt_PY+Ds_PY,2)+pow(Ds_0_20_nc_maxPt_PZ+Ds_PZ,2) ) );
            hDsMuComb02->Fill(MassDsG1_0_20-Ds_MM+MassDsPDG);
          }

          // for DsNeutral
          if(Ds_0_80_nc_mult>0 and sqrt(pow(Ds_0_80_nc_maxPt_PX,2)+pow(Ds_0_80_nc_maxPt_PY,2))>0 and abs(Ds_0_80_nc_maxPt_MM-MassPi0PDG)<20){
            float MassDsG1_0_80 = sqrt((pow((sqrt(Ds_0_80_nc_maxPt_PX*Ds_0_80_nc_maxPt_PX+Ds_0_80_nc_maxPt_PY*Ds_0_80_nc_maxPt_PY+Ds_0_80_nc_maxPt_PZ*Ds_0_80_nc_maxPt_PZ+mass*mass)+Ds_PE),2) ) - ( pow(Ds_0_80_nc_maxPt_PX+Ds_PX,2)+pow(Ds_0_80_nc_maxPt_PY+Ds_PY,2)+pow(Ds_0_80_nc_maxPt_PZ+Ds_PZ,2) ) );
            hDsMuMassWithFirstG08->Fill(MassDsG1_0_80-Ds_MM+MassDsPDG);
          }
          if(Ds_0_80_nc_mult>1 and sqrt(pow(Ds_0_80_nc_secPt_PX,2)+pow(Ds_0_80_nc_secPt_PY,2))>0 and abs(Ds_0_80_nc_secPt_MM-MassPi0PDG)<20){
            float MassDsG2_0_80 = sqrt((pow((sqrt(Ds_0_80_nc_secPt_PX*Ds_0_80_nc_secPt_PX+Ds_0_80_nc_secPt_PY*Ds_0_80_nc_secPt_PY+Ds_0_80_nc_secPt_PZ*Ds_0_80_nc_secPt_PZ+mass*mass)+Ds_PE),2) ) - ( pow(Ds_0_80_nc_secPt_PX+Ds_PX,2)+pow(Ds_0_80_nc_secPt_PY+Ds_PY,2)+pow(Ds_0_80_nc_secPt_PZ+Ds_PZ,2) ) );
            hDsMuMassWithSecondG08->Fill(MassDsG2_0_80-Ds_MM+MassDsPDG);
          }
          if(Ds_0_80_nc_mult>2 and sqrt(pow(Ds_0_80_nc_thiPt_PX,2)+pow(Ds_0_80_nc_thiPt_PY,2))>0 and abs(Ds_0_80_nc_thiPt_MM-MassPi0PDG)<20){
            float MassDsG3_0_80 = sqrt((pow((sqrt(Ds_0_80_nc_thiPt_PX*Ds_0_80_nc_thiPt_PX+Ds_0_80_nc_thiPt_PY*Ds_0_80_nc_thiPt_PY+Ds_0_80_nc_thiPt_PZ*Ds_0_80_nc_thiPt_PZ+mass*mass)+Ds_PE),2) ) - ( pow(Ds_0_80_nc_thiPt_PX+Ds_PX,2)+pow(Ds_0_80_nc_thiPt_PY+Ds_PY,2)+pow(Ds_0_80_nc_thiPt_PZ+Ds_PZ,2) ) );
            hDsMuMassWithThirdG08->Fill(MassDsG3_0_80-Ds_MM+MassDsPDG);
          }
      
          if(Ds_0_60_nc_mult>0 and sqrt(pow(Ds_0_60_nc_maxPt_PX,2)+pow(Ds_0_60_nc_maxPt_PY,2))>0 and abs(Ds_0_60_nc_maxPt_MM-MassPi0PDG)<20){
            float MassDsG1_0_60 = sqrt((pow((sqrt(Ds_0_60_nc_maxPt_PX*Ds_0_60_nc_maxPt_PX+Ds_0_60_nc_maxPt_PY*Ds_0_60_nc_maxPt_PY+Ds_0_60_nc_maxPt_PZ*Ds_0_60_nc_maxPt_PZ+mass*mass)+Ds_PE),2) ) - ( pow(Ds_0_60_nc_maxPt_PX+Ds_PX,2)+pow(Ds_0_60_nc_maxPt_PY+Ds_PY,2)+pow(Ds_0_60_nc_maxPt_PZ+Ds_PZ,2) ) );
            hDsMuMassWithFirstG06->Fill(MassDsG1_0_60-Ds_MM+MassDsPDG); 
          }
          if(Ds_0_60_nc_mult>1 and sqrt(pow(Ds_0_60_nc_secPt_PX,2)+pow(Ds_0_60_nc_secPt_PY,2))>0 and abs(Ds_0_60_nc_secPt_MM-MassPi0PDG)<20){
            float MassDsG2_0_60 = sqrt((pow((sqrt(Ds_0_60_nc_secPt_PX*Ds_0_60_nc_secPt_PX+Ds_0_60_nc_secPt_PY*Ds_0_60_nc_secPt_PY+Ds_0_60_nc_secPt_PZ*Ds_0_60_nc_secPt_PZ+mass*mass)+Ds_PE),2) ) - ( pow(Ds_0_60_nc_secPt_PX+Ds_PX,2)+pow(Ds_0_60_nc_secPt_PY+Ds_PY,2)+pow(Ds_0_60_nc_secPt_PZ+Ds_PZ,2) ) );
            hDsMuMassWithSecondG06->Fill(MassDsG2_0_60-Ds_MM+MassDsPDG);
          }
          if(Ds_0_60_nc_mult>2 and sqrt(pow(Ds_0_60_nc_thiPt_PX,2)+pow(Ds_0_60_nc_thiPt_PY,2))>0 and abs(Ds_0_60_nc_thiPt_MM-MassPi0PDG)<20){
            float MassDsG3_0_60 = sqrt((pow((sqrt(Ds_0_60_nc_thiPt_PX*Ds_0_60_nc_thiPt_PX+Ds_0_60_nc_thiPt_PY*Ds_0_60_nc_thiPt_PY+Ds_0_60_nc_thiPt_PZ*Ds_0_60_nc_thiPt_PZ+mass*mass)+Ds_PE),2) ) - ( pow(Ds_0_60_nc_thiPt_PX+Ds_PX,2)+pow(Ds_0_60_nc_thiPt_PY+Ds_PY,2)+pow(Ds_0_60_nc_thiPt_PZ+Ds_PZ,2) ) );
            hDsMuMassWithThirdG06->Fill(MassDsG3_0_60-Ds_MM+MassDsPDG);
          }

          if(Ds_0_40_nc_mult>0 and sqrt(pow(Ds_0_40_nc_maxPt_PX,2)+pow(Ds_0_40_nc_maxPt_PY,2))>0 and abs(Ds_0_40_nc_maxPt_MM-MassPi0PDG)<20){
            //float MassDsG1_0_40 = sqrt((pow((sqrt(Ds_0_40_nc_maxPt_PX*Ds_0_40_nc_maxPt_PX+Ds_0_40_nc_maxPt_PY*Ds_0_40_nc_maxPt_PY+Ds_0_40_nc_maxPt_PZ*Ds_0_40_nc_maxPt_PZ+mass*mass)+Ds_PE),2) ) - ( pow(Ds_0_40_nc_maxPt_PX+Ds_PX,2)+pow(Ds_0_40_nc_maxPt_PY+Ds_PY,2)+pow(Ds_0_40_nc_maxPt_PZ+Ds_PZ,2) ) );
            float MassDsG1_0_40 = sqrt((pow((sqrt(Ds_0_40_nc_maxPt_PX*Ds_0_40_nc_maxPt_PX+Ds_0_40_nc_maxPt_PY*Ds_0_40_nc_maxPt_PY+Ds_0_40_nc_maxPt_PZ*Ds_0_40_nc_maxPt_PZ+Ds_0_40_nc_maxPt_MM*Ds_0_40_nc_maxPt_MM)+Ds_PE),2) ) - ( pow(Ds_0_40_nc_maxPt_PX+Ds_PX,2)+pow(Ds_0_40_nc_maxPt_PY+Ds_PY,2)+pow(Ds_0_40_nc_maxPt_PZ+Ds_PZ,2) ) );

            hDsMuMassWithFirstG04->Fill(MassDsG1_0_40-Ds_MM+MassDsPDG);
            hPi0MassWithFirstG04->Fill(Ds_0_40_nc_maxPt_MM);
          }
          if(Ds_0_40_nc_mult>1 and sqrt(pow(Ds_0_40_nc_secPt_PX,2)+pow(Ds_0_40_nc_secPt_PY,2))>0 and abs(Ds_0_40_nc_secPt_MM-MassPi0PDG)<20){
            float MassDsG2_0_40 = sqrt((pow((sqrt(Ds_0_40_nc_secPt_PX*Ds_0_40_nc_secPt_PX+Ds_0_40_nc_secPt_PY*Ds_0_40_nc_secPt_PY+Ds_0_40_nc_secPt_PZ*Ds_0_40_nc_secPt_PZ+mass*mass)+Ds_PE),2) ) - ( pow(Ds_0_40_nc_secPt_PX+Ds_PX,2)+pow(Ds_0_40_nc_secPt_PY+Ds_PY,2)+pow(Ds_0_40_nc_secPt_PZ+Ds_PZ,2) ) );
            hDsMuMassWithSecondG04->Fill(MassDsG2_0_40-Ds_MM+MassDsPDG);
          }
          if(Ds_0_40_nc_mult>2 and sqrt(pow(Ds_0_40_nc_thiPt_PX,2)+pow(Ds_0_40_nc_thiPt_PY,2))>0 and abs(Ds_0_40_nc_thiPt_MM-MassPi0PDG)<20){
            float MassDsG3_0_40 = sqrt((pow((sqrt(Ds_0_40_nc_thiPt_PX*Ds_0_40_nc_thiPt_PX+Ds_0_40_nc_thiPt_PY*Ds_0_40_nc_thiPt_PY+Ds_0_40_nc_thiPt_PZ*Ds_0_40_nc_thiPt_PZ+mass*mass)+Ds_PE),2) ) - ( pow(Ds_0_40_nc_thiPt_PX+Ds_PX,2)+pow(Ds_0_40_nc_thiPt_PY+Ds_PY,2)+pow(Ds_0_40_nc_thiPt_PZ+Ds_PZ,2) ) );
            hDsMuMassWithThirdG04->Fill(MassDsG3_0_40-Ds_MM+MassDsPDG);
          }

          if(Ds_0_20_nc_mult>0 and sqrt(pow(Ds_0_20_nc_maxPt_PX,2)+pow(Ds_0_20_nc_maxPt_PY,2))>0 and abs(Ds_0_20_nc_maxPt_MM-MassPi0PDG)<20){
            float MassDsG1_0_20 = sqrt((pow((sqrt(Ds_0_20_nc_maxPt_PX*Ds_0_20_nc_maxPt_PX+Ds_0_20_nc_maxPt_PY*Ds_0_20_nc_maxPt_PY+Ds_0_20_nc_maxPt_PZ*Ds_0_20_nc_maxPt_PZ+mass*mass)+Ds_PE),2) ) - ( pow(Ds_0_20_nc_maxPt_PX+Ds_PX,2)+pow(Ds_0_20_nc_maxPt_PY+Ds_PY,2)+pow(Ds_0_20_nc_maxPt_PZ+Ds_PZ,2) ) );
            hDsMuMassWithFirstG02->Fill(MassDsG1_0_20-Ds_MM+MassDsPDG);
          }
          if(Ds_0_20_nc_mult>1 and sqrt(pow(Ds_0_20_nc_secPt_PX,2)+pow(Ds_0_20_nc_secPt_PY,2))>0 and abs(Ds_0_20_nc_secPt_MM-MassPi0PDG)<20){
            float MassDsG2_0_20 = sqrt((pow((sqrt(Ds_0_20_nc_secPt_PX*Ds_0_20_nc_secPt_PX+Ds_0_20_nc_secPt_PY*Ds_0_20_nc_secPt_PY+Ds_0_20_nc_secPt_PZ*Ds_0_20_nc_secPt_PZ+mass*mass)+Ds_PE),2) ) - ( pow(Ds_0_20_nc_secPt_PX+Ds_PX,2)+pow(Ds_0_20_nc_secPt_PY+Ds_PY,2)+pow(Ds_0_20_nc_secPt_PZ+Ds_PZ,2) ) );
            hDsMuMassWithSecondG02->Fill(MassDsG2_0_20-Ds_MM+MassDsPDG);
          }
          if(Ds_0_20_nc_mult>2 and sqrt(pow(Ds_0_20_nc_thiPt_PX,2)+pow(Ds_0_20_nc_thiPt_PY,2))>0 and abs(Ds_0_20_nc_thiPt_MM-MassPi0PDG)<20){
            float MassDsG3_0_20 = sqrt((pow((sqrt(Ds_0_20_nc_thiPt_PX*Ds_0_20_nc_thiPt_PX+Ds_0_20_nc_thiPt_PY*Ds_0_20_nc_thiPt_PY+Ds_0_20_nc_thiPt_PZ*Ds_0_20_nc_thiPt_PZ+mass*mass)+Ds_PE),2) ) - ( pow(Ds_0_20_nc_thiPt_PX+Ds_PX,2)+pow(Ds_0_20_nc_thiPt_PY+Ds_PY,2)+pow(Ds_0_20_nc_thiPt_PZ+Ds_PZ,2) ) );
            hDsMuMassWithThirdG02->Fill(MassDsG3_0_20-Ds_MM+MassDsPDG);
          }
        }
      //}
   }
   hDsMuMassWithFirstG08->Write();
   hDsMuMassWithFirstG06->Write();
   hDsMuMassWithFirstG04->Write();
   hDsMuMassWithFirstG02->Write();
   hDsMuMassWithSecondG08->Write();
   hDsMuMassWithSecondG06->Write();
   hDsMuMassWithSecondG04->Write();
   hDsMuMassWithSecondG02->Write();
   hDsMuMassWithThirdG08->Write();
   hDsMuMassWithThirdG06->Write();
   hDsMuMassWithThirdG04->Write();
   hDsMuMassWithThirdG02->Write();
  
   hPi0MassWithFirstG04->Write(); 

   hDsMuComb08->Write();
   hDsMuComb06->Write();
   hDsMuComb04->Write();
   hDsMuComb02->Write();

}
