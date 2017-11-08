#define NeutralIso_cxx
#include "NeutralIso.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>

void NeutralIso::Loop()
{
// #################
// ##### INFO ######  
// This code makes the distribution of variables as a function of the aperture of the neutral cones
// This wa used to determine the radius of the cone
// ################# 
  
//   In a ROOT session, you can do:
//      root> .L NeutralIso.C
//      root> NeutralIso t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(20);     // Read and show values of entry 20
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
   nentries = 1000000;
   std::cout << "Total number of entries = " << nentries << std::endl;

   TFile *f = new TFile("histosNeutralIso_Data.root","new");

   int nbinsMu = 80;
   int nbinsTau = 40;

   // photon Right Pt P histograms
   TH1F *hDsMuRightPtPt15 = new TH1F("DsMuRightPtPt15", "DsMuNu Right Pt photon pT 1.5", nbinsMu, 0, 10000);
   TH1F *hDsTauRightPtPt15 = new TH1F("DsTauRightPtPt15", "DsTauNu Right Pt photon pT 1.5", nbinsTau, 0, 10000);
   TH1F *hDsstMuRightPtPt15 = new TH1F("DsstMuRightPtPt15", "DsstMuNu Right Pt photon pT 1.5", nbinsMu, 0, 10000);
   TH1F *hDsstTauRightPtPt15 = new TH1F("DsstTauRightPtPt15", "DsstTauNu Right Pt photon pT 1.5", nbinsTau, 0, 10000);
   TH1F *hDsMuRightPtPt12 = new TH1F("DsMuRightPtPt12", "DsMuNu Right Pt photon pT 1.2", nbinsMu, 0, 10000);
   TH1F *hDsTauRightPtPt12 = new TH1F("DsTauRightPtPt12", "DsTauNu Right Pt photon pT 1.2", nbinsTau, 0, 10000);
   TH1F *hDsstMuRightPtPt12 = new TH1F("DsstMuRightPtPt12", "DsstMuNu Right Pt photon pT 1.2", nbinsMu, 0, 10000);
   TH1F *hDsstTauRightPtPt12 = new TH1F("DsstTauRightPtPt12", "DsstTauNu Right Pt photon pT 1.2", nbinsTau, 0, 10000);
   TH1F *hDsMuRightPtPt09 = new TH1F("DsMuRightPtPt09", "DsMuNu Right Pt photon pT 0.9", nbinsMu, 0, 10000);
   TH1F *hDsTauRightPtPt09 = new TH1F("DsTauRightPtPt09", "DsTauNu Right Pt photon pT 0.9", nbinsTau, 0, 10000);
   TH1F *hDsstMuRightPtPt09 = new TH1F("DsstMuRightPtPt09", "DsstMuNu Right Pt photon pT 0.9", nbinsMu, 0, 10000);
   TH1F *hDsstTauRightPtPt09 = new TH1F("DsstTauRightPtPt09", "DsstTauNu Right Pt photon pT 0.9", nbinsTau, 0, 10000);
   TH1F *hDsMuRightPtPt06 = new TH1F("DsMuRightPtPt06", "DsMuNu Right Pt photon pT 0.6", nbinsMu, 0, 2000);
   TH1F *hDsTauRightPtPt06 = new TH1F("DsTauRightPtPt06", "DsTauNu Right Pt photon pT 0.6", nbinsTau, 0, 2000);
   TH1F *hDsstMuRightPtPt06 = new TH1F("DsstMuRightPtPt06", "DsstMuNu Right Pt photon pT 0.6", nbinsMu, 0, 2000);
   TH1F *hDsstTauRightPtPt06 = new TH1F("DsstTauRightPtPt06", "DsstTauNu Right Pt photon pT 0.6", nbinsTau, 0, 2000);
   TH1F *hDsMuRightPtPt03 = new TH1F("DsMuRightPtPt03", "DsMuNu Right Pt photon pT 0.3", nbinsMu, 0, 2000);
   TH1F *hDsTauRightPtPt03 = new TH1F("DsTauRightPtPt03", "DsTauNu Right Pt photon pT 0.3", nbinsTau, 0, 2000);
   TH1F *hDsstMuRightPtPt03 = new TH1F("DsstMuRightPtPt03", "DsstMuNu Right Pt photon pT 0.3", nbinsMu, 0, 2000);
   TH1F *hDsstTauRightPtPt03 = new TH1F("DsstTauRightPtPt03", "DsstTauNu Right Pt photon pT 0.3", nbinsTau, 0, 2000);

   // photon Max Pt P histograms
   TH1F *hDsMuMaxPtPt15 = new TH1F("DsMuMaxPtPt15", "DsMuNu Max Pt photon pT 1.5", nbinsMu, 0, 10000);
   TH1F *hDsTauMaxPtPt15 = new TH1F("DsTauMaxPtPt15", "DsTauNu Max Pt photon pT 1.5", nbinsTau, 0, 10000);
   TH1F *hDsstMuMaxPtPt15 = new TH1F("DsstMuMaxPtPt15", "DsstMuNu Max Pt photon pT 1.5", nbinsMu, 0, 10000);
   TH1F *hDsstTauMaxPtPt15 = new TH1F("DsstTauMaxPtPt15", "DsstTauNu Max Pt photon pT 1.5", nbinsTau, 0, 10000);
   TH1F *hDsMuMaxPtPt12 = new TH1F("DsMuMaxPtPt12", "DsMuNu Max Pt photon pT 1.2", nbinsMu, 0, 10000);
   TH1F *hDsTauMaxPtPt12 = new TH1F("DsTauMaxPtPt12", "DsTauNu Max Pt photon pT 1.2", nbinsTau, 0, 10000);
   TH1F *hDsstMuMaxPtPt12 = new TH1F("DsstMuMaxPtPt12", "DsstMuNu Max Pt photon pT 1.2", nbinsMu, 0, 10000);
   TH1F *hDsstTauMaxPtPt12 = new TH1F("DsstTauMaxPtPt12", "DsstTauNu Max Pt photon pT 1.2", nbinsTau, 0, 10000);
   TH1F *hDsMuMaxPtPt09 = new TH1F("DsMuMaxPtPt09", "DsMuNu Max Pt photon pT 0.9", nbinsMu, 0, 10000);
   TH1F *hDsTauMaxPtPt09 = new TH1F("DsTauMaxPtPt09", "DsTauNu Max Pt photon pT 0.9", nbinsTau, 0, 10000);
   TH1F *hDsstMuMaxPtPt09 = new TH1F("DsstMuMaxPtPt09", "DsstMuNu Max Pt photon pT 0.9", nbinsMu, 0, 10000);
   TH1F *hDsstTauMaxPtPt09 = new TH1F("DsstTauMaxPtPt09", "DsstTauNu Max Pt photon pT 0.9", nbinsTau, 0, 10000);
   TH1F *hDsMuMaxPtPt06 = new TH1F("DsMuMaxPtPt06", "DsMuNu Max Pt photon pT 0.6", nbinsMu, 0, 2000);
   TH1F *hDsTauMaxPtPt06 = new TH1F("DsTauMaxPtPt06", "DsTauNu Max Pt photon pT 0.6", nbinsTau, 0, 2000);
   TH1F *hDsstMuMaxPtPt06 = new TH1F("DsstMuMaxPtPt06", "DsstMuNu Max Pt photon pT 0.6", nbinsMu, 0, 2000);
   TH1F *hDsstTauMaxPtPt06 = new TH1F("DsstTauMaxPtPt06", "DsstTauNu Max Pt photon pT 0.6", nbinsTau, 0, 2000);
   TH1F *hDsMuMaxPtPt03 = new TH1F("DsMuMaxPtPt03", "DsMuNu Max Pt photon pT 0.3", nbinsMu, 0, 2000);
   TH1F *hDsTauMaxPtPt03 = new TH1F("DsTauMaxPtPt03", "DsTauNu Max Pt photon pT 0.3", nbinsTau, 0, 2000);
   TH1F *hDsstMuMaxPtPt03 = new TH1F("DsstMuMaxPtPt03", "DsstMuNu Max Pt photon pT 0.3", nbinsMu, 0, 2000);
   TH1F *hDsstTauMaxPtPt03 = new TH1F("DsstTauMaxPtPt03", "DsstTauNu Max Pt photon pT 0.3", nbinsTau, 0, 2000);

   // photon Right Pt P histograms
   TH1F *hDsMuRightPtP15 = new TH1F("DsMuRightPtP15", "DsMuNu Right Pt photon momentum 1.5", nbinsMu, 0, 15000);
   TH1F *hDsTauRightPtP15 = new TH1F("DsTauRightPtP15", "DsTauNu Right Pt photon momentum 1.5", nbinsTau, 0, 15000);
   TH1F *hDsstMuRightPtP15 = new TH1F("DsstMuRightPtP15", "DsstMuNu Right Pt photon momentum 1.5", nbinsMu, 0, 15000);
   TH1F *hDsstTauRightPtP15 = new TH1F("DsstTauRightPtP15", "DsstTauNu Right Pt photon momentum 1.5", nbinsTau, 0, 15000);
   TH1F *hDsMuRightPtP12 = new TH1F("DsMuRightPtP12", "DsMuNu Right Pt photon momentum 1.2", nbinsMu, 0, 15000);
   TH1F *hDsTauRightPtP12 = new TH1F("DsTauRightPtP12", "DsTauNu Right Pt photon momentum 1.2", nbinsTau, 0, 15000);
   TH1F *hDsstMuRightPtP12 = new TH1F("DsstMuRightPtP12", "DsstMuNu Right Pt photon momentum 1.2", nbinsMu, 0, 15000);
   TH1F *hDsstTauRightPtP12 = new TH1F("DsstTauRightPtP12", "DsstTauNu Right Pt photon momentum 1.2", nbinsTau, 0, 15000);
   TH1F *hDsMuRightPtP09 = new TH1F("DsMuRightPtP09", "DsMuNu Right Pt photon momentum 0.9", nbinsMu, 0, 15000);
   TH1F *hDsTauRightPtP09 = new TH1F("DsTauRightPtP09", "DsTauNu Right Pt photon momentum 0.9", nbinsTau, 0, 15000);
   TH1F *hDsstMuRightPtP09 = new TH1F("DsstMuRightPtP09", "DsstMuNu Right Pt photon momentum 0.9", nbinsMu, 0, 15000);
   TH1F *hDsstTauRightPtP09 = new TH1F("DsstTauRightPtP09", "DsstTauNu Right Pt photon momentum 0.9", nbinsTau, 0, 15000);
   TH1F *hDsMuRightPtP06 = new TH1F("DsMuRightPtP06", "DsMuNu Right Pt photon momentum 0.6", nbinsMu, 0, 15000);
   TH1F *hDsTauRightPtP06 = new TH1F("DsTauRightPtP06", "DsTauNu Right Pt photon momentum 0.6", nbinsTau, 0, 15000);
   TH1F *hDsstMuRightPtP06 = new TH1F("DsstMuRightPtP06", "DsstMuNu Right Pt photon momentum 0.6", nbinsMu, 0, 15000);
   TH1F *hDsstTauRightPtP06 = new TH1F("DsstTauRightPtP06", "DsstTauNu Right Pt photon momentum 0.6", nbinsTau, 0, 15000);
   TH1F *hDsMuRightPtP03 = new TH1F("DsMuRightPtP03", "DsMuNu Right Pt photon momentum 0.3", nbinsMu, 0, 15000);
   TH1F *hDsTauRightPtP03 = new TH1F("DsTauRightPtP03", "DsTauNu Right Pt photon momentum 0.3", nbinsTau, 0, 15000);
   TH1F *hDsstMuRightPtP03 = new TH1F("DsstMuRightPtP03", "DsstMuNu Right Pt photon momentum 0.3", nbinsMu, 0, 15000);
   TH1F *hDsstTauRightPtP03 = new TH1F("DsstTauRightPtP03", "DsstTauNu Right Pt photon momentum 0.3", nbinsTau, 0, 15000); 

   // photon Max Pt P histograms
   TH1F *hDsMuMaxPtP15 = new TH1F("DsMuMaxPtP15", "DsMuNu Max Pt photon momentum 1.5", nbinsMu, 0, 25000);
   TH1F *hDsTauMaxPtP15 = new TH1F("DsTauMaxPtP15", "DsTauNu Max Pt photon momentum 1.5", nbinsTau, 0, 25000);
   TH1F *hDsstMuMaxPtP15 = new TH1F("DsstMuMaxPtP15", "DsstMuNu Max Pt photon momentum 1.5", nbinsMu, 0, 25000);
   TH1F *hDsstTauMaxPtP15 = new TH1F("DsstTauMaxPtP15", "DsstTauNu Max Pt photon momentum 1.5", nbinsTau, 0, 25000);
   TH1F *hDsMuMaxPtP12 = new TH1F("DsMuMaxPtP12", "DsMuNu Max Pt photon momentum 1.2", nbinsMu, 0, 25000);
   TH1F *hDsTauMaxPtP12 = new TH1F("DsTauMaxPtP12", "DsTauNu Max Pt photon momentum 1.2", nbinsTau, 0, 25000);
   TH1F *hDsstMuMaxPtP12 = new TH1F("DsstMuMaxPtP12", "DsstMuNu Max Pt photon momentum 1.2", nbinsMu, 0, 25000);
   TH1F *hDsstTauMaxPtP12 = new TH1F("DsstTauMaxPtP12", "DsstTauNu Max Pt photon momentum 1.2", nbinsTau, 0, 25000);
   TH1F *hDsMuMaxPtP09 = new TH1F("DsMuMaxPtP09", "DsMuNu Max Pt photon momentum 0.9", nbinsMu, 0, 25000);
   TH1F *hDsTauMaxPtP09 = new TH1F("DsTauMaxPtP09", "DsTauNu Max Pt photon momentum 0.9", nbinsTau, 0, 25000);
   TH1F *hDsstMuMaxPtP09 = new TH1F("DsstMuMaxPtP09", "DsstMuNu Max Pt photon momentum 0.9", nbinsMu, 0, 25000);
   TH1F *hDsstTauMaxPtP09 = new TH1F("DsstTauMaxPtP09", "DsstTauNu Max Pt photon momentum 0.9", nbinsTau, 0, 25000);
   TH1F *hDsMuMaxPtP06 = new TH1F("DsMuMaxPtP06", "DsMuNu Max Pt photon momentum 0.6", nbinsMu, 0, 25000);
   TH1F *hDsTauMaxPtP06 = new TH1F("DsTauMaxPtP06", "DsTauNu Max Pt photon momentum 0.6", nbinsTau, 0, 25000);
   TH1F *hDsstMuMaxPtP06 = new TH1F("DsstMuMaxPtP06", "DsstMuNu Max Pt photon momentum 0.6", nbinsMu, 0, 25000);
   TH1F *hDsstTauMaxPtP06 = new TH1F("DsstTauMaxPtP06", "DsstTauNu Max Pt photon momentum 0.6", nbinsTau, 0, 25000);
   TH1F *hDsMuMaxPtP03 = new TH1F("DsMuMaxPtP03", "DsMuNu Max Pt photon momentum 0.3", nbinsMu, 0, 25000);
   TH1F *hDsTauMaxPtP03 = new TH1F("DsTauMaxPtP03", "DsTauNu Max Pt photon momentum 0.3", nbinsTau, 0, 25000);
   TH1F *hDsstMuMaxPtP03 = new TH1F("DsstMuMaxPtP03", "DsstMuNu Max Pt photon momentum 0.3", nbinsMu, 0, 25000);
   TH1F *hDsstTauMaxPtP03 = new TH1F("DsstTauMaxPtP03", "DsstTauNu Max Pt photon momentum 0.3", nbinsTau, 0, 25000); 

   // photon mass histograms
   TH1F *hDsMuMassWithG15 = new TH1F("DsMuMassWithG15", "DsMuNu Ds Mass with photon 1.5", nbinsMu, 1900, 5000);
   TH1F *hDsTauMassWithG15 = new TH1F("DsTauMassWithG15", "DsTauNu Ds Mass with photon 1.5", nbinsTau, 1900, 5000);
   TH1F *hDsstMuMassWithG15 = new TH1F("DsstMuMassWithG15", "DsstMuNu Ds Mass with photon 1.5", nbinsMu, 1900, 5000);
   TH1F *hDsstTauMassWithG15 = new TH1F("DsstTauMassWithG15", "DsstTauNu Ds Mass with photon 1.5", nbinsTau, 1900, 5000); 
   TH1F *hDsMuMassWithG12 = new TH1F("DsMuMassWithG12", "DsMuNu Ds Mass with photon 1.2", nbinsMu, 1900, 5000);
   TH1F *hDsTauMassWithG12 = new TH1F("DsTauMassWithG12", "DsTauNu Ds Mass with photon 1.2", nbinsTau, 1900, 5000);
   TH1F *hDsstMuMassWithG12 = new TH1F("DsstMuMassWithG12", "DsstMuNu Ds Mass with photon 1.2", nbinsMu, 1900, 5000);
   TH1F *hDsstTauMassWithG12 = new TH1F("DsstTauMassWithG12", "DsstTauNu Ds Mass with photon 1.2", nbinsTau, 1900, 5000);
   TH1F *hDsMuMassWithG09 = new TH1F("DsMuMassWithG09", "DsMuNu Ds Mass with photon 0.9", nbinsMu, 1900, 5000);
   TH1F *hDsTauMassWithG09 = new TH1F("DsTauMassWithG09", "DsTauNu Ds Mass with photon 0.9", nbinsTau, 1900, 5000);
   TH1F *hDsstMuMassWithG09 = new TH1F("DsstMuMassWithG09", "DsstMuNu Ds Mass with photon 0.9", nbinsMu, 1900, 5000);
   TH1F *hDsstTauMassWithG09 = new TH1F("DsstTauMassWithG09", "DsstTauNu Ds Mass with photon 0.9", nbinsTau, 1900, 5000);
   TH1F *hDsMuMassWithG06 = new TH1F("DsMuMassWithG06", "DsMuNu Ds Mass with photon 0.6", nbinsMu, 1900, 3000);
   TH1F *hDsTauMassWithG06 = new TH1F("DsTauMassWithG06", "DsTauNu Ds Mass with photon 0.6", nbinsTau, 1900, 3000);
   TH1F *hDsstMuMassWithG06 = new TH1F("DsstMuMassWithG06", "DsstMuNu Ds Mass with photon 0.6", nbinsMu, 1900, 3000);
   TH1F *hDsstTauMassWithG06 = new TH1F("DsstTauMassWithG06", "DsstTauNu Ds Mass with photon 0.6", nbinsTau, 1900, 3000);
   TH1F *hDsMuMassWithG03 = new TH1F("DsMuMassWithG03", "DsMuNu Ds Mass with photon 0.3", nbinsMu, 1900, 2500);
   TH1F *hDsTauMassWithG03 = new TH1F("DsTauMassWithG03", "DsTauNu Ds Mass with photon 0.3", nbinsTau, 1900, 2500);
   TH1F *hDsstMuMassWithG03 = new TH1F("DsstMuMassWithG03", "DsstMuNu Ds Mass with photon 0.3", nbinsMu, 1900, 2500);
   TH1F *hDsstTauMassWithG03 = new TH1F("DsstTauMassWithG03", "DsstTauNu Ds Mass with photon 0.3", nbinsTau, 1900, 2500); 

   TH1F *hDsMuMaxCone = new TH1F("DsMuMaxCone", "DsMuNu MaxCone", nbinsMu, 0, 3.2);
   TH1F *hDsTauMaxCone = new TH1F("DsTauMaxCone", "DsTauNu MaxCone", nbinsTau, 0, 3.2);
   TH1F *hDsstMuMaxCone = new TH1F("DsstMuMaxCone", "DsstMuNu MaxCone", nbinsMu, 0, 3.2);
   TH1F *hDsstTauMaxCone = new TH1F("DsstTauMaxCone", "DsstTauNu MaxCone", nbinsTau, 0, 3.2);
   TH1F *hDs0MuMaxCone = new TH1F("Ds0MuMaxCone", "Ds0MuNu MaxCone", nbinsMu, 0, 3.2);
   TH1F *hDs0TauMaxCone = new TH1F("Ds0TauMaxCone", "Ds0TauNu MaxCone", nbinsTau, 0, 3.2);
   TH1F *hDs1MuMaxCone = new TH1F("Ds1MuMaxCone", "Ds1MuNu MaxCone", nbinsMu, 0, 3.2);
   TH1F *hDs1TauMaxCone = new TH1F("Ds1TauMaxCone", "Ds1TauNu MaxCone", nbinsTau, 0, 3.2);
   TH1F *hDsprMuMaxCone = new TH1F("DsprMuMaxCone", "DsprMuNu MaxCone", nbinsMu, 0, 3.2);
   TH1F *hDsprTauMaxCone = new TH1F("DsprTauMaxCone", "DsprTauNu MaxCone", nbinsTau, 0, 3.2);
  
   TH1F *hDsMuMaxNeutralCone = new TH1F("DsMuMaxNeutralCone", "DsMuNu MaxNeutralCone", nbinsMu, 0, 1.6);
   TH1F *hDsTauMaxNeutralCone = new TH1F("DsTauMaxNeutralCone", "DsTauNu MaxNeutralCone", nbinsTau, 0, 1.6);
   TH1F *hDsstMuMaxNeutralCone = new TH1F("DsstMuMaxNeutralCone", "DsstMuNu MaxNeutralCone", nbinsMu, 0, 1.6);
   TH1F *hDsstTauMaxNeutralCone = new TH1F("DsstTauMaxNeutralCone", "DsstTauNu MaxNeutralCone", nbinsTau, 0, 1.6);
   TH1F *hDs0MuMaxNeutralCone = new TH1F("Ds0MuMaxNeutralCone", "Ds0MuNu MaxNeutralCone", nbinsMu, 0, 1.6);
   TH1F *hDs0TauMaxNeutralCone = new TH1F("Ds0TauMaxNeutralCone", "Ds0TauNu MaxNeutralCone", nbinsTau, 0, 1.6);
   TH1F *hDs1MuMaxNeutralCone = new TH1F("Ds1MuMaxNeutralCone", "Ds1MuNu MaxNeutralCone", nbinsMu, 0, 1.6);
   TH1F *hDs1TauMaxNeutralCone = new TH1F("Ds1TauMaxNeutralCone", "Ds1TauNu MaxNeutralCone", nbinsTau, 0, 1.6);
   TH1F *hDsprMuMaxNeutralCone = new TH1F("DsprMuMaxNeutralCone", "DsprMuNu MaxNeutralCone", nbinsMu, 0, 1.6);
   TH1F *hDsprTauMaxNeutralCone = new TH1F("DsprTauMaxNeutralCone", "DsprTauNu MaxNeutralCone", nbinsTau, 0, 1.6); 

   TH1F *hDsMuAsym15 = new TH1F("DsMuAsym15", "DsMuNu Asymetry 1.5", nbinsMu, -1.0, 1.0);
   TH1F *hDsTauAsym15 = new TH1F("DsTauAsym15", "DsTauNu Asymetry 1.5", nbinsTau, -1.0, 1.0);
   TH1F *hDsstMuAsym15 = new TH1F("DsstMuAsym15", "DsstMuNu Asymetry 1.5", nbinsMu, -1.0, 1.0);
   TH1F *hDsstTauAsym15 = new TH1F("DsstTauAsym15", "DsstTauNu Asymetry 1.5", nbinsTau, -1.0, 1.0);
   TH1F *hDs0MuAsym15 = new TH1F("Ds0MuAsym15", "Ds0MuNu Asymetry 1.5", nbinsMu, -1.0, 1.0);
   TH1F *hDs0TauAsym15 = new TH1F("Ds0TauAsym15", "Ds0TauNu Asymetry 1.5", nbinsTau, -1.0, 1.0);
   TH1F *hDs1MuAsym15 = new TH1F("Ds1MuAsym15", "Ds1MuNu Asymetry 1.5", nbinsMu, -1.0, 1.0);
   TH1F *hDs1TauAsym15 = new TH1F("Ds1TauAsym15", "Ds1TauNu Asymetry 1.5", nbinsTau, -1.0, 1.0);
   TH1F *hDsprMuAsym15 = new TH1F("DsprMuAsym15", "DsprMuNu Asymetry 1.5", nbinsMu, -1.0, 1.0);
   TH1F *hDsprTauAsym15 = new TH1F("DsprTauAsym15", "DsprTauNu Asymetry 1.5", nbinsTau, -1.0, 1.0); 

   TH1F *hDsMuAsym12 = new TH1F("DsMuAsym12", "DsMuNu Asymetry 1.2", nbinsMu, -1.0, 1.0);
   TH1F *hDsTauAsym12 = new TH1F("DsTauAsym12", "DsTauNu Asymetry 1.2", nbinsTau, -1.0, 1.0);
   TH1F *hDsstMuAsym12 = new TH1F("DsstMuAsym12", "DsstMuNu Asymetry 1.2", nbinsMu, -1.0, 1.0);
   TH1F *hDsstTauAsym12 = new TH1F("DsstTauAsym12", "DsstTauNu Asymetry 1.2", nbinsTau, -1.0, 1.0);
   TH1F *hDs0MuAsym12 = new TH1F("Ds0MuAsym12", "Ds0MuNu Asymetry 1.2", nbinsMu, -1.0, 1.0);
   TH1F *hDs0TauAsym12 = new TH1F("Ds0TauAsym12", "Ds0TauNu Asymetry 1.2", nbinsTau, -1.0, 1.0);
   TH1F *hDs1MuAsym12 = new TH1F("Ds1MuAsym12", "Ds1MuNu Asymetry 1.2", nbinsMu, -1.0, 1.0);
   TH1F *hDs1TauAsym12 = new TH1F("Ds1TauAsym12", "Ds1TauNu Asymetry 1.2", nbinsTau, -1.0, 1.0);
   TH1F *hDsprMuAsym12 = new TH1F("DsprMuAsym12", "DsprMuNu Asymetry 1.2", nbinsMu, -1.0, 1.0);
   TH1F *hDsprTauAsym12 = new TH1F("DsprTauAsym12", "DsprTauNu Asymetry 1.2", nbinsTau, -1.0, 1.0);

   TH1F *hDsMuAsym09 = new TH1F("DsMuAsym09", "DsMuNu Asymetry 0.9", nbinsMu, -1.0, 1.0);
   TH1F *hDsTauAsym09 = new TH1F("DsTauAsym09", "DsTauNu Asymetry 0.9", nbinsTau, -1.0, 1.0);
   TH1F *hDsstMuAsym09 = new TH1F("DsstMuAsym09", "DsstMuNu Asymetry 0.9", nbinsMu, -1.0, 1.0);
   TH1F *hDsstTauAsym09 = new TH1F("DsstTauAsym09", "DsstTauNu Asymetry 0.9", nbinsTau, -1.0, 1.0);
   TH1F *hDs0MuAsym09 = new TH1F("Ds0MuAsym09", "Ds0MuNu Asymetry 0.9", nbinsMu, -1.0, 1.0);
   TH1F *hDs0TauAsym09 = new TH1F("Ds0TauAsym09", "Ds0TauNu Asymetry 0.9", nbinsTau, -1.0, 1.0);
   TH1F *hDs1MuAsym09 = new TH1F("Ds1MuAsym09", "Ds1MuNu Asymetry 0.9", nbinsMu, -1.0, 1.0);
   TH1F *hDs1TauAsym09 = new TH1F("Ds1TauAsym09", "Ds1TauNu Asymetry 0.9", nbinsTau, -1.0, 1.0);
   TH1F *hDsprMuAsym09 = new TH1F("DsprMuAsym09", "DsprMuNu Asymetry 0.9", nbinsMu, -1.0, 1.0);
   TH1F *hDsprTauAsym09 = new TH1F("DsprTauAsym09", "DsprTauNu Asymetry 0.9", nbinsTau, -1.0, 1.0);

   TH1F *hDsMuAsym06 = new TH1F("DsMuAsym06", "DsMuNu Asymetry 0.6", nbinsMu, -1.0, 1.0);
   TH1F *hDsTauAsym06 = new TH1F("DsTauAsym06", "DsTauNu Asymetry 0.6", nbinsTau, -1.0, 1.0);
   TH1F *hDsstMuAsym06 = new TH1F("DsstMuAsym06", "DsstMuNu Asymetry 0.6", nbinsMu, -1.0, 1.0);
   TH1F *hDsstTauAsym06 = new TH1F("DsstTauAsym06", "DsstTauNu Asymetry 0.6", nbinsTau, -1.0, 1.0);
   TH1F *hDs0MuAsym06 = new TH1F("Ds0MuAsym06", "Ds0MuNu Asymetry 0.6", nbinsMu, -1.0, 1.0);
   TH1F *hDs0TauAsym06 = new TH1F("Ds0TauAsym06", "Ds0TauNu Asymetry 0.6", nbinsTau, -1.0, 1.0);
   TH1F *hDs1MuAsym06 = new TH1F("Ds1MuAsym06", "Ds1MuNu Asymetry 0.6", nbinsMu, -1.0, 1.0);
   TH1F *hDs1TauAsym06 = new TH1F("Ds1TauAsym06", "Ds1TauNu Asymetry 0.6", nbinsTau, -1.0, 1.0);
   TH1F *hDsprMuAsym06 = new TH1F("DsprMuAsym06", "DsprMuNu Asymetry 0.6", nbinsMu, -1.0, 1.0);
   TH1F *hDsprTauAsym06 = new TH1F("DsprTauAsym06", "DsprTauNu Asymetry 0.6", nbinsTau, -1.0, 1.0);

   TH1F *hDsMuAsym03 = new TH1F("DsMuAsym03", "DsMuNu Asymetry 0.3", nbinsMu, -1.0, 1.0);
   TH1F *hDsTauAsym03 = new TH1F("DsTauAsym03", "DsTauNu Asymetry 0.3", nbinsTau, -1.0, 1.0);
   TH1F *hDsstMuAsym03 = new TH1F("DsstMuAsym03", "DsstMuNu Asymetry 0.3", nbinsMu, -1.0, 1.0);
   TH1F *hDsstTauAsym03 = new TH1F("DsstTauAsym03", "DsstTauNu Asymetry 0.3", nbinsTau, -1.0, 1.0);
   TH1F *hDs0MuAsym03 = new TH1F("Ds0MuAsym03", "Ds0MuNu Asymetry 0.3", nbinsMu, -1.0, 1.0);
   TH1F *hDs0TauAsym03 = new TH1F("Ds0TauAsym03", "Ds0TauNu Asymetry 0.3", nbinsTau, -1.0, 1.0);
   TH1F *hDs1MuAsym03 = new TH1F("Ds1MuAsym03", "Ds1MuNu Asymetry 0.3", nbinsMu, -1.0, 1.0);
   TH1F *hDs1TauAsym03 = new TH1F("Ds1TauAsym03", "Ds1TauNu Asymetry 0.3", nbinsTau, -1.0, 1.0);
   TH1F *hDsprMuAsym03 = new TH1F("DsprMuAsym03", "DsprMuNu Asymetry 0.3", nbinsMu, -1.0, 1.0);
   TH1F *hDsprTauAsym03 = new TH1F("DsprTauAsym03", "DsprTauNu Asymetry 0.3", nbinsTau, -1.0, 1.0); 

   TH1F *hDsMuPCone15 = new TH1F("DsMuPCone15", "DsMuNu P Cone 1.5", nbinsMu, 0.0, 150000.0);
   TH1F *hDsTauPCone15 = new TH1F("DsTauPCone15", "DsTauNu P Cone 1.5", nbinsTau, 0.0, 150000.0);
   TH1F *hDsstMuPCone15 = new TH1F("DsstMuPCone15", "DsstMuNu P Cone 1.5", nbinsMu, 0.0, 150000.0);
   TH1F *hDsstTauPCone15 = new TH1F("DsstTauPCone15", "DsstTauNu P Cone 1.5", nbinsTau, 0.0, 150000.0);
   TH1F *hDs0MuPCone15 = new TH1F("Ds0MuPCone15", "Ds0MuNu P Cone 1.5", nbinsMu, 0.0, 150000.0);
   TH1F *hDs0TauPCone15 = new TH1F("Ds0TauPCone15", "Ds0TauNu P Cone 1.5", nbinsTau, 0.0, 150000.0);
   TH1F *hDs1MuPCone15 = new TH1F("Ds1MuPCone15", "Ds1MuNu P Cone 1.5", nbinsMu, 0.0, 150000.0);
   TH1F *hDs1TauPCone15 = new TH1F("Ds1TauPCone15", "Ds1TauNu P Cone 1.5", nbinsTau, 0.0, 150000.0);
   TH1F *hDsprMuPCone15 = new TH1F("DsprMuPCone15", "DsprMuNu P Cone 1.5", nbinsMu, 0.0, 150000.0);
   TH1F *hDsprTauPCone15 = new TH1F("DsprTauPCone15", "DsprTauNu P Cone 1.5", nbinsTau, 0.0, 150000.0);

   TH1F *hDsMuPCone12 = new TH1F("DsMuPCone12", "DsMuNu P Cone 1.2", nbinsMu, 0.0, 150000.0);
   TH1F *hDsTauPCone12 = new TH1F("DsTauPCone12", "DsTauNu P Cone 1.2", nbinsTau, 0.0, 150000.0);
   TH1F *hDsstMuPCone12 = new TH1F("DsstMuPCone12", "DsstMuNu P Cone 1.2", nbinsMu, 0.0, 150000.0);
   TH1F *hDsstTauPCone12 = new TH1F("DsstTauPCone12", "DsstTauNu P Cone 1.2", nbinsTau, 0.0, 150000.0);
   TH1F *hDs0MuPCone12 = new TH1F("Ds0MuPCone12", "Ds0MuNu P Cone 1.2", nbinsMu, 0.0, 150000.0);
   TH1F *hDs0TauPCone12 = new TH1F("Ds0TauPCone12", "Ds0TauNu P Cone 1.2", nbinsTau, 0.0, 150000.0);
   TH1F *hDs1MuPCone12 = new TH1F("Ds1MuPCone12", "Ds1MuNu P Cone 1.2", nbinsMu, 0.0, 150000.0);
   TH1F *hDs1TauPCone12 = new TH1F("Ds1TauPCone12", "Ds1TauNu P Cone 1.2", nbinsTau, 0.0, 150000.0);
   TH1F *hDsprMuPCone12 = new TH1F("DsprMuPCone12", "DsprMuNu P Cone 1.2", nbinsMu, 0.0, 150000.0);
   TH1F *hDsprTauPCone12 = new TH1F("DsprTauPCone12", "DsprTauNu P Cone 1.2", nbinsTau, 0.0, 150000.0);

   TH1F *hDsMuPCone09 = new TH1F("DsMuPCone09", "DsMuNu P Cone 0.9", nbinsMu, 0.0, 150000.0);
   TH1F *hDsTauPCone09 = new TH1F("DsTauPCone09", "DsTauNu P Cone 0.9", nbinsTau, 0.0, 150000.0);
   TH1F *hDsstMuPCone09 = new TH1F("DsstMuPCone09", "DsstMuNu P Cone 0.9", nbinsMu, 0.0, 150000.0);
   TH1F *hDsstTauPCone09 = new TH1F("DsstTauPCone09", "DsstTauNu P Cone 0.9", nbinsTau, 0.0, 150000.0);
   TH1F *hDs0MuPCone09 = new TH1F("Ds0MuPCone09", "Ds0MuNu P Cone 0.9", nbinsMu, 0.0, 150000.0);
   TH1F *hDs0TauPCone09 = new TH1F("Ds0TauPCone09", "Ds0TauNu P Cone 0.9", nbinsTau, 0.0, 150000.0);
   TH1F *hDs1MuPCone09 = new TH1F("Ds1MuPCone09", "Ds1MuNu P Cone 0.9", nbinsMu, 0.0, 150000.0);
   TH1F *hDs1TauPCone09 = new TH1F("Ds1TauPCone09", "Ds1TauNu P Cone 0.9", nbinsTau, 0.0, 150000.0);
   TH1F *hDsprMuPCone09 = new TH1F("DsprMuPCone09", "DsprMuNu P Cone 0.9", nbinsMu, 0.0, 150000.0);
   TH1F *hDsprTauPCone09 = new TH1F("DsprTauPCone09", "DsprTauNu P Cone 0.9", nbinsTau, 0.0, 150000.0);

   TH1F *hDsMuPCone06 = new TH1F("DsMuPCone06", "DsMuNu P Cone 0.6", nbinsMu, 0.0, 70000.0);
   TH1F *hDsTauPCone06 = new TH1F("DsTauPCone06", "DsTauNu P Cone 0.6", nbinsTau, 0.0, 70000.0);
   TH1F *hDsstMuPCone06 = new TH1F("DsstMuPCone06", "DsstMuNu P Cone 0.6", nbinsMu, 0.0, 70000.0);
   TH1F *hDsstTauPCone06 = new TH1F("DsstTauPCone06", "DsstTauNu P Cone 0.6", nbinsTau, 0.0, 70000.0);
   TH1F *hDs0MuPCone06 = new TH1F("Ds0MuPCone06", "Ds0MuNu P Cone 0.6", nbinsMu, 0.0, 70000.0);
   TH1F *hDs0TauPCone06 = new TH1F("Ds0TauPCone06", "Ds0TauNu P Cone 0.6", nbinsTau, 0.0, 70000.0);
   TH1F *hDs1MuPCone06 = new TH1F("Ds1MuPCone06", "Ds1MuNu P Cone 0.6", nbinsMu, 0.0, 70000.0);
   TH1F *hDs1TauPCone06 = new TH1F("Ds1TauPCone06", "Ds1TauNu P Cone 0.6", nbinsTau, 0.0, 70000.0);
   TH1F *hDsprMuPCone06 = new TH1F("DsprMuPCone06", "DsprMuNu P Cone 0.6", nbinsMu, 0.0, 70000.0);
   TH1F *hDsprTauPCone06 = new TH1F("DsprTauPCone06", "DsprTauNu P Cone 0.6", nbinsTau, 0.0, 70000.0);

   TH1F *hDsMuPCone03 = new TH1F("DsMuPCone03", "DsMuNu P Cone 0.3", nbinsMu, 0.0, 50000.0);
   TH1F *hDsTauPCone03 = new TH1F("DsTauPCone03", "DsTauNu P Cone 0.3", nbinsTau, 0.0, 50000.0);
   TH1F *hDsstMuPCone03 = new TH1F("DsstMuPCone03", "DsstMuNu P Cone 0.3", nbinsMu, 0.0, 50000.0);
   TH1F *hDsstTauPCone03 = new TH1F("DsstTauPCone03", "DsstTauNu P Cone 0.3", nbinsTau, 0.0, 50000.0);
   TH1F *hDs0MuPCone03 = new TH1F("Ds0MuPCone03", "Ds0MuNu P Cone 0.3", nbinsMu, 0.0, 50000.0);
   TH1F *hDs0TauPCone03 = new TH1F("Ds0TauPCone03", "Ds0TauNu P Cone 0.3", nbinsTau, 0.0, 50000.0);
   TH1F *hDs1MuPCone03 = new TH1F("Ds1MuPCone03", "Ds1MuNu P Cone 0.3", nbinsMu, 0.0, 50000.0);
   TH1F *hDs1TauPCone03 = new TH1F("Ds1TauPCone03", "Ds1TauNu P Cone 0.3", nbinsTau, 0.0, 50000.0);
   TH1F *hDsprMuPCone03 = new TH1F("DsprMuPCone03", "DsprMuNu P Cone 0.3", nbinsMu, 0.0, 50000.0);
   TH1F *hDsprTauPCone03 = new TH1F("DsprTauPCone03", "DsprTauNu P Cone 0.3", nbinsTau, 0.0, 50000.0);

   TH1F *hDsMuMult03 = new TH1F("DsMuNeutralMult03", "DsMuNu Neutral multiplicity 0.3", 11, -0.5, 10.5);
   TH1F *hDsTauMult03 = new TH1F("DsTauNeutralMult03", "DsTauNu Neutral multiplicity 0.3", 11, -0.5, 10.5);
   TH1F *hDsstMuMult03 = new TH1F("DsstMuNeutralMult03", "Ds*MuNu Neutral multiplicity 0.3", 11, -0.5, 10.5);
   TH1F *hDsstTauMult03 = new TH1F("DsstTauNeutralMult03", "Ds*TauNu Neutral multiplicity 0.3", 11, -0.5, 10.5);
   TH1F *hDs0MuMult03 = new TH1F("Ds0MuNeutralMult03", "Ds0MuNu Neutral multiplicity 0.3", 11, -0.5, 10.5);
   TH1F *hDs0TauMult03 = new TH1F("Ds0TauNeutralMult03", "Ds0TauNu Neutral multiplicity 0.3", 11, -0.5, 10.5);
   TH1F *hDs1MuMult03 = new TH1F("Ds1MuNeutralMult03", "Ds1MuNu Neutral multiplicity 0.3", 11, -0.5, 10.5);
   TH1F *hDs1TauMult03 = new TH1F("Ds1TauNeutralMult03", "Ds1TauNu Neutral multiplicity 0.3", 11, -0.5, 10.5);
   TH1F *hDsprMuMult03 = new TH1F("DsprMuNeutralMult03", "DsprMuNu Neutral multiplicity 0.3", 11, -0.5, 10.5);
   TH1F *hDsprTauMult03 = new TH1F("DsprTauNeutralMult03", "DsprTauNu Neutral multiplicity 0.3", 11, -0.5, 10.5);

   TH1F *hDsMuMult06 = new TH1F("DsMuNeutralMult06", "DsMuNu Neutral multiplicity 0.6", 11, -0.5, 10.5);
   TH1F *hDsTauMult06 = new TH1F("DsTauNeutralMult06", "DsTauNu Neutral multiplicity 0.6", 11, -0.5, 10.5);
   TH1F *hDsstMuMult06 = new TH1F("DsstMuNeutralMult06", "Ds*MuNu Neutral multiplicity 0.6", 11, -0.5, 10.5);
   TH1F *hDsstTauMult06 = new TH1F("DsstTauNeutralMult06", "Ds*TauNu Neutral multiplicity 0.6", 11, -0.5, 10.5);
   TH1F *hDs0MuMult06 = new TH1F("Ds0MuNeutralMult06", "Ds0MuNu Neutral multiplicity 0.6", 11, -0.5, 10.5);
   TH1F *hDs0TauMult06 = new TH1F("Ds0TauNeutralMult06", "Ds0TauNu Neutral multiplicity 0.6", 11, -0.5, 10.5);
   TH1F *hDs1MuMult06 = new TH1F("Ds1MuNeutralMult06", "Ds1MuNu Neutral multiplicity 0.6", 11, -0.5, 10.5);
   TH1F *hDs1TauMult06 = new TH1F("Ds1TauNeutralMult06", "Ds1TauNu Neutral multiplicity 0.6", 11, -0.5, 10.5);
   TH1F *hDsprMuMult06 = new TH1F("DsprMuNeutralMult06", "DsprMuNu Neutral multiplicity 0.6", 11, -0.5, 10.5);
   TH1F *hDsprTauMult06 = new TH1F("DsprTauNeutralMult06", "DsprTauNu Neutral multiplicity 0.6", 11, -0.5, 10.5);

   TH1F *hDsMuMult09 = new TH1F("DsMuNeutralMult09", "DsMuNu Neutral multiplicity 0.9", 31, -0.5, 30.5);
   TH1F *hDsTauMult09 = new TH1F("DsTauNeutralMult09", "DsTauNu Neutral multiplicity 0.9", 31, -0.5, 30.5);
   TH1F *hDsstMuMult09 = new TH1F("DsstMuNeutralMult09", "Ds*MuNu Neutral multiplicity 0.9", 31, -0.5, 30.5);
   TH1F *hDsstTauMult09 = new TH1F("DsstTauNeutralMult09", "Ds*TauNu Neutral multiplicity 0.9", 31, -0.5, 30.5);
   TH1F *hDs0MuMult09 = new TH1F("Ds0MuNeutralMult09", "Ds0MuNu Neutral multiplicity 0.9", 31, -0.5, 30.5);
   TH1F *hDs0TauMult09 = new TH1F("Ds0TauNeutralMult09", "Ds0TauNu Neutral multiplicity 0.9", 31, -0.5, 30.5);
   TH1F *hDs1MuMult09 = new TH1F("Ds1MuNeutralMult09", "Ds1MuNu Neutral multiplicity 0.9", 31, -0.5, 30.5);
   TH1F *hDs1TauMult09 = new TH1F("Ds1TauNeutralMult09", "Ds1TauNu Neutral multiplicity 0.9", 31, -0.5, 30.5);
   TH1F *hDsprMuMult09 = new TH1F("DsprMuNeutralMult09", "DsprMuNu Neutral multiplicity 0.9", 31, -0.5, 30.5);
   TH1F *hDsprTauMult09 = new TH1F("DsprTauNeutralMult09", "DsprTauNu Neutral multiplicity 0.9", 31, -0.5, 30.5);

   TH1F *hDsMuMult12 = new TH1F("DsMuNeutralMult12", "DsMuNu Neutral multiplicity 1.2", 31, -0.5, 30.5);
   TH1F *hDsTauMult12 = new TH1F("DsTauNeutralMult12", "DsTauNu Neutral multiplicity 1.2", 31, -0.5, 30.5);
   TH1F *hDsstMuMult12 = new TH1F("DsstMuNeutralMult12", "Ds*MuNu Neutral multiplicity 1.2", 31, -0.5, 30.5);
   TH1F *hDsstTauMult12 = new TH1F("DsstTauNeutralMult12", "Ds*TauNu Neutral multiplicity 1.2", 31, -0.5, 30.5);
   TH1F *hDs0MuMult12 = new TH1F("Ds0MuNeutralMult12", "Ds0MuNu Neutral multiplicity 1.2", 31, -0.5, 30.5);
   TH1F *hDs0TauMult12 = new TH1F("Ds0TauNeutralMult12", "Ds0TauNu Neutral multiplicity 1.2", 31, -0.5, 30.5);
   TH1F *hDs1MuMult12 = new TH1F("Ds1MuNeutralMult12", "Ds1MuNu Neutral multiplicity 1.2", 31, -0.5, 30.5);
   TH1F *hDs1TauMult12 = new TH1F("Ds1TauNeutralMult12", "Ds1TauNu Neutral multiplicity 1.2", 31, -0.5, 30.5);
   TH1F *hDsprMuMult12 = new TH1F("DsprMuNeutralMult12", "DsprMuNu Neutral multiplicity 1.2", 31, -0.5, 30.5);
   TH1F *hDsprTauMult12 = new TH1F("DsprTauNeutralMult12", "DsprTauNu Neutral multiplicity 1.2", 31, -0.5, 30.5);

   TH1F *hDsMuMult15 = new TH1F("DsMuNeutralMult15", "DsMuNu Neutral multiplicity 1.5", 31, -0.5, 30.5);
   TH1F *hDsTauMult15 = new TH1F("DsTauNeutralMult15", "DsTauNu Neutral multiplicity 1.5", 31, -0.5, 30.5);
   TH1F *hDsstMuMult15 = new TH1F("DsstMuNeutralMult15", "Ds*MuNu Neutral multiplicity 1.5", 31, -0.5, 30.5);
   TH1F *hDsstTauMult15 = new TH1F("DsstTauNeutralMult15", "Ds*TauNu Neutral multiplicity 1.5", 31, -0.5, 30.5);
   TH1F *hDs0MuMult15 = new TH1F("Ds0MuNeutralMult15", "Ds0MuNu Neutral multiplicity 1.5", 31, -0.5, 30.5);
   TH1F *hDs0TauMult15 = new TH1F("Ds0TauNeutralMult15", "Ds0TauNu Neutral multiplicity 1.5", 31, -0.5, 30.5);
   TH1F *hDs1MuMult15 = new TH1F("Ds1MuNeutralMult15", "Ds1MuNu Neutral multiplicity 1.5", 31, -0.5, 30.5);
   TH1F *hDs1TauMult15 = new TH1F("Ds1TauNeutralMult15", "Ds1TauNu Neutral multiplicity 1.5", 31, -0.5, 30.5);
   TH1F *hDsprMuMult15 = new TH1F("DsprMuNeutralMult15", "DsprMuNu Neutral multiplicity 1.5", 31, -0.5, 30.5);
   TH1F *hDsprTauMult15 = new TH1F("DsprTauNeutralMult15", "DsprTauNu Neutral multiplicity 1.5", 31, -0.5, 30.5); 

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if (jentry%100000 == 0) std::cout << "Processing event " << jentry << std::endl;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      /*
      float deltaPhiKpl = fabs(Ds_phi - Kpl_phi);
      float deltaEtaKpl = Ds_eta - Kpl_eta; 
      float deltaPhiKmi = fabs(Ds_phi - Kmi_phi);
      float deltaEtaKmi = Ds_eta - Kmi_eta;
      float deltaPhiPi = fabs(Ds_phi - pi_phi);
      float deltaEtaPi = Ds_eta - pi_eta;
      float deltaRKpl = sqrt(deltaPhiKpl * deltaPhiKpl + deltaEtaKpl * deltaEtaKpl);
      float deltaRKmi = sqrt(deltaPhiKmi * deltaPhiKmi + deltaEtaKmi * deltaEtaKmi);
      float deltaRPi = sqrt(deltaPhiPi * deltaPhiPi + deltaEtaPi * deltaEtaPi); 

      float PCone15 = sqrt(Ds_1_50_nc_PX*Ds_1_50_nc_PX + Ds_1_50_nc_PY*Ds_1_50_nc_PY + Ds_1_50_nc_PZ*Ds_1_50_nc_PZ);
      float PCone12 = sqrt(Ds_1_20_nc_PX*Ds_1_20_nc_PX + Ds_1_20_nc_PY*Ds_1_20_nc_PY + Ds_1_20_nc_PZ*Ds_1_20_nc_PZ);
      float PCone09 = sqrt(Ds_0_90_nc_PX*Ds_0_90_nc_PX + Ds_0_90_nc_PY*Ds_0_90_nc_PY + Ds_0_90_nc_PZ*Ds_0_90_nc_PZ);
      float PCone06 = sqrt(Ds_0_60_nc_PX*Ds_0_60_nc_PX + Ds_0_60_nc_PY*Ds_0_60_nc_PY + Ds_0_60_nc_PZ*Ds_0_60_nc_PZ);
      float PCone03 = sqrt(Ds_0_30_nc_PX*Ds_0_30_nc_PX + Ds_0_30_nc_PY*Ds_0_30_nc_PY + Ds_0_30_nc_PZ*Ds_0_30_nc_PZ);

      float AsymP15 = (Ds_P - PCone15) / (Ds_P + PCone15);
      float AsymP12 = (Ds_P - PCone12) / (Ds_P + PCone12);
      float AsymP09 = (Ds_P - PCone09) / (Ds_P + PCone09);
      float AsymP06 = (Ds_P - PCone06) / (Ds_P + PCone06);
      float AsymP03 = (Ds_P - PCone03) / (Ds_P + PCone03);
      
      float MassDsG_1_50 = sqrt((pow((sqrt(Ds_1_50_nc_maxPt_PX*Ds_1_50_nc_maxPt_PX+Ds_1_50_nc_maxPt_PY*Ds_1_50_nc_maxPt_PY+Ds_1_50_nc_maxPt_PZ*Ds_1_50_nc_maxPt_PZ)+Ds_PE),2) ) - ( pow(Ds_1_50_nc_maxPt_PX+Ds_PX,2)+pow(Ds_1_50_nc_maxPt_PY+Ds_PY,2)+pow(Ds_1_50_nc_maxPt_PZ+Ds_PZ,2) ) );
      float MassDsG_1_20 = sqrt((pow((sqrt(Ds_1_20_nc_maxPt_PX*Ds_1_20_nc_maxPt_PX+Ds_1_20_nc_maxPt_PY*Ds_1_20_nc_maxPt_PY+Ds_1_20_nc_maxPt_PZ*Ds_1_20_nc_maxPt_PZ)+Ds_PE),2) ) - ( pow(Ds_1_20_nc_maxPt_PX+Ds_PX,2)+pow(Ds_1_20_nc_maxPt_PY+Ds_PY,2)+pow(Ds_1_20_nc_maxPt_PZ+Ds_PZ,2) ) );
      float MassDsG_0_90 = sqrt((pow((sqrt(Ds_0_90_nc_maxPt_PX*Ds_0_90_nc_maxPt_PX+Ds_0_90_nc_maxPt_PY*Ds_0_90_nc_maxPt_PY+Ds_0_90_nc_maxPt_PZ*Ds_0_90_nc_maxPt_PZ)+Ds_PE),2) ) - ( pow(Ds_0_90_nc_maxPt_PX+Ds_PX,2)+pow(Ds_0_90_nc_maxPt_PY+Ds_PY,2)+pow(Ds_0_90_nc_maxPt_PZ+Ds_PZ,2) ) );
      */
      float MassDsG_0_60 = sqrt((pow((sqrt(Ds_0_60_nc_maxPt_PX*Ds_0_60_nc_maxPt_PX+Ds_0_60_nc_maxPt_PY*Ds_0_60_nc_maxPt_PY+Ds_0_60_nc_maxPt_PZ*Ds_0_60_nc_maxPt_PZ)+Ds_PE),2) ) - ( pow(Ds_0_60_nc_maxPt_PX+Ds_PX,2)+pow(Ds_0_60_nc_maxPt_PY+Ds_PY,2)+pow(Ds_0_60_nc_maxPt_PZ+Ds_PZ,2) ) );
      float MassDsG_0_30 = sqrt((pow((sqrt(Ds_0_30_nc_maxPt_PX*Ds_0_30_nc_maxPt_PX+Ds_0_30_nc_maxPt_PY*Ds_0_30_nc_maxPt_PY+Ds_0_30_nc_maxPt_PZ*Ds_0_30_nc_maxPt_PZ)+Ds_PE),2) ) - ( pow(Ds_0_30_nc_maxPt_PX+Ds_PX,2)+pow(Ds_0_30_nc_maxPt_PY+Ds_PY,2)+pow(Ds_0_30_nc_maxPt_PZ+Ds_PZ,2) ) ); 

      /*
      float MaxPtP_1_5 = sqrt( Ds_1_50_nc_maxPt_PX*Ds_1_50_nc_maxPt_PX+Ds_1_50_nc_maxPt_PY*Ds_1_50_nc_maxPt_PY+Ds_1_50_nc_maxPt_PZ*Ds_1_50_nc_maxPt_PZ );
      float MaxPtP_1_2 = sqrt( Ds_1_20_nc_maxPt_PX*Ds_1_20_nc_maxPt_PX+Ds_1_20_nc_maxPt_PY*Ds_1_20_nc_maxPt_PY+Ds_1_20_nc_maxPt_PZ*Ds_1_20_nc_maxPt_PZ );
      float MaxPtP_0_9 = sqrt( Ds_0_90_nc_maxPt_PX*Ds_0_90_nc_maxPt_PX+Ds_0_90_nc_maxPt_PY*Ds_0_90_nc_maxPt_PY+Ds_0_90_nc_maxPt_PZ*Ds_0_90_nc_maxPt_PZ );
      float MaxPtP_0_6 = sqrt( Ds_0_60_nc_maxPt_PX*Ds_0_60_nc_maxPt_PX+Ds_0_60_nc_maxPt_PY*Ds_0_60_nc_maxPt_PY+Ds_0_60_nc_maxPt_PZ*Ds_0_60_nc_maxPt_PZ );      
      float MaxPtP_0_3 = sqrt( Ds_0_30_nc_maxPt_PX*Ds_0_30_nc_maxPt_PX+Ds_0_30_nc_maxPt_PY*Ds_0_30_nc_maxPt_PY+Ds_0_30_nc_maxPt_PZ*Ds_0_30_nc_maxPt_PZ );

      float MaxPtPt_1_5 = sqrt( Ds_1_50_nc_maxPt_PX*Ds_1_50_nc_maxPt_PX+Ds_1_50_nc_maxPt_PY*Ds_1_50_nc_maxPt_PY );
      float MaxPtPt_1_2 = sqrt( Ds_1_20_nc_maxPt_PX*Ds_1_20_nc_maxPt_PX+Ds_1_20_nc_maxPt_PY*Ds_1_20_nc_maxPt_PY );
      float MaxPtPt_0_9 = sqrt( Ds_0_90_nc_maxPt_PX*Ds_0_90_nc_maxPt_PX+Ds_0_90_nc_maxPt_PY*Ds_0_90_nc_maxPt_PY );
      float MaxPtPt_0_6 = sqrt( Ds_0_60_nc_maxPt_PX*Ds_0_60_nc_maxPt_PX+Ds_0_60_nc_maxPt_PY*Ds_0_60_nc_maxPt_PY );
      float MaxPtPt_0_3 = sqrt( Ds_0_30_nc_maxPt_PX*Ds_0_30_nc_maxPt_PX+Ds_0_30_nc_maxPt_PY*Ds_0_30_nc_maxPt_PY );
      */

      // Tau decays
      if(abs(mu_MC_MOTHER_ID) == 15 && abs(mu_TRUEID) == 13){
        // DsTauNu decays
        if(abs(Ds_MC_MOTHER_ID)==531 && abs(Ds_TRUEID) == 431){
          /*
          hDsTauMult15->Fill(Ds_1_50_nc_mult);
          hDsTauMult12->Fill(Ds_1_20_nc_mult);
          hDsTauMult09->Fill(Ds_0_90_nc_mult);
          hDsTauMult06->Fill(Ds_0_60_nc_mult);
          hDsTauMult03->Fill(Ds_0_30_nc_mult);
          hDsTauMassWithG15->Fill(MassDsG_1_50);
          hDsTauMassWithG12->Fill(MassDsG_1_20);
          hDsTauMassWithG09->Fill(MassDsG_0_90);
          */
          hDsTauMassWithG06->Fill(MassDsG_0_60);
          hDsTauMassWithG03->Fill(MassDsG_0_30);
          /*
          hDsTauMaxPtP15->Fill(MaxPtP_1_5);
          hDsTauMaxPtP12->Fill(MaxPtP_1_2);
          hDsTauMaxPtP09->Fill(MaxPtP_0_9);
          hDsTauMaxPtP06->Fill(MaxPtP_0_6);
          hDsTauMaxPtP03->Fill(MaxPtP_0_3); 
          hDsTauMaxPtPt15->Fill(MaxPtPt_1_5);
          hDsTauMaxPtPt12->Fill(MaxPtPt_1_2);
          hDsTauMaxPtPt09->Fill(MaxPtPt_0_9);
          hDsTauMaxPtPt06->Fill(MaxPtPt_0_6);
          hDsTauMaxPtPt03->Fill(MaxPtPt_0_3);
          if(MassDsG_1_50>2000 && (MassDsG_1_50-2112.1)<30){
            hDsTauRightPtP15->Fill(MaxPtP_1_5);
            hDsTauRightPtPt15->Fill(MaxPtPt_1_5);
          }
          if(MassDsG_1_50>2000 && (MassDsG_1_20-2112.1)<30){
            hDsTauRightPtP12->Fill(MaxPtP_1_2);
            hDsTauRightPtPt12->Fill(MaxPtPt_1_2);
          }
          if(MassDsG_1_50>2000 && (MassDsG_0_90-2112.1)<30){
            hDsTauRightPtP09->Fill(MaxPtP_0_9);
            hDsTauRightPtPt09->Fill(MaxPtPt_0_9);
          }
          if(MassDsG_1_50>2000 && (MassDsG_0_60-2112.1)<30){
            hDsTauRightPtP06->Fill(MaxPtP_0_6);
            hDsTauRightPtPt06->Fill(MaxPtPt_0_6);
          }
          if(MassDsG_1_50>2000 && (MassDsG_0_30-2112.1)<30){
            hDsTauRightPtP03->Fill(MaxPtP_0_3);
            hDsTauRightPtPt03->Fill(MaxPtPt_0_3);
          }
          hDsTauMaxCone->Fill(TMath::Max(TMath::Max(deltaRKpl,deltaRKmi),deltaRPi));
          hDsTauAsym15->Fill(AsymP15);
          hDsTauAsym12->Fill(AsymP12);
          hDsTauAsym09->Fill(AsymP09);
          hDsTauAsym06->Fill(AsymP06);
          hDsTauAsym03->Fill(AsymP03); 
          hDsTauPCone15->Fill(PCone15);
          hDsTauPCone12->Fill(PCone12);
          hDsTauPCone09->Fill(PCone09);
          hDsTauPCone06->Fill(PCone06);
          hDsTauPCone03->Fill(PCone03); 
          */
        }
        // Ds*TauNu decays
        if(abs(Ds_MC_MOTHER_ID)==433 && abs(Ds_TRUEID) == 431){
          /*
          hDsstTauMult15->Fill(Ds_1_50_nc_mult);
          hDsstTauMult12->Fill(Ds_1_20_nc_mult);
          hDsstTauMult09->Fill(Ds_0_90_nc_mult);
          hDsstTauMult06->Fill(Ds_0_60_nc_mult);
          hDsstTauMult03->Fill(Ds_0_30_nc_mult);
          hDsstTauMassWithG15->Fill(MassDsG_1_50);
          hDsstTauMassWithG12->Fill(MassDsG_1_20);
          hDsstTauMassWithG09->Fill(MassDsG_0_90);
          */
          hDsstTauMassWithG06->Fill(MassDsG_0_60);
          hDsstTauMassWithG03->Fill(MassDsG_0_30); 
          /*
          hDsstTauMaxPtP15->Fill(MaxPtP_1_5);
          hDsstTauMaxPtP12->Fill(MaxPtP_1_2);
          hDsstTauMaxPtP09->Fill(MaxPtP_0_9);
          hDsstTauMaxPtP06->Fill(MaxPtP_0_6);
          hDsstTauMaxPtP03->Fill(MaxPtP_0_3);
          hDsstTauMaxPtPt15->Fill(MaxPtPt_1_5);
          hDsstTauMaxPtPt12->Fill(MaxPtPt_1_2);
          hDsstTauMaxPtPt09->Fill(MaxPtPt_0_9);
          hDsstTauMaxPtPt06->Fill(MaxPtPt_0_6);
          hDsstTauMaxPtPt03->Fill(MaxPtPt_0_3); 
          if(MassDsG_1_50>2000 && (MassDsG_1_50-2112.1)<30){
            hDsstTauRightPtP15->Fill(MaxPtP_1_5);
            hDsstTauRightPtPt15->Fill(MaxPtPt_1_5);
          }
          if(MassDsG_1_50>2000 && (MassDsG_1_20-2112.1)<30){
            hDsstTauRightPtP12->Fill(MaxPtP_1_2);
            hDsstTauRightPtPt12->Fill(MaxPtPt_1_2);
          }
          if(MassDsG_1_50>2000 && (MassDsG_0_90-2112.1)<30){
            hDsstTauRightPtP09->Fill(MaxPtP_0_9);
            hDsstTauRightPtPt09->Fill(MaxPtPt_0_9);
          }
          if(MassDsG_1_50>2000 && (MassDsG_0_60-2112.1)<30){
            hDsstTauRightPtP06->Fill(MaxPtP_0_6);
            hDsstTauRightPtPt06->Fill(MaxPtPt_0_6);
          }
          if(MassDsG_1_50>2000 && (MassDsG_0_30-2112.1)<30){
            hDsstTauRightPtP03->Fill(MaxPtP_0_3);
            hDsstTauRightPtPt03->Fill(MaxPtPt_0_3);
          }
          hDsstTauMaxCone->Fill(TMath::Max(TMath::Max(deltaRKpl,deltaRKmi),deltaRPi));
          hDsstTauAsym15->Fill(AsymP15);
          hDsstTauAsym12->Fill(AsymP12);
          hDsstTauAsym09->Fill(AsymP09);
          hDsstTauAsym06->Fill(AsymP06);
          hDsstTauAsym03->Fill(AsymP03);
          hDsstTauPCone15->Fill(PCone15);
          hDsstTauPCone12->Fill(PCone12);
          hDsstTauPCone09->Fill(PCone09);
          hDsstTauPCone06->Fill(PCone06);
          hDsstTauPCone03->Fill(PCone03);
          */
        } 
        /*
        // Ds0*TauNu decays
        if(abs(Ds_MC_MOTHER_ID)==10431 && abs(Ds_TRUEID) == 431){
          hDs0TauMult15->Fill(Ds_1_50_nc_mult);
          hDs0TauMult12->Fill(Ds_1_20_nc_mult);
          hDs0TauMult09->Fill(Ds_0_90_nc_mult);
          hDs0TauMult06->Fill(Ds_0_60_nc_mult);
          hDs0TauMult03->Fill(Ds_0_30_nc_mult);
          hDs0TauMaxCone->Fill(TMath::Max(TMath::Max(deltaRKpl,deltaRKmi),deltaRPi));
          hDs0TauAsym15->Fill(AsymP15);
          hDs0TauAsym12->Fill(AsymP12);
          hDs0TauAsym09->Fill(AsymP09);
          hDs0TauAsym06->Fill(AsymP06);
          hDs0TauAsym03->Fill(AsymP03);
          hDs0TauPCone15->Fill(PCone15);
          hDs0TauPCone12->Fill(PCone12);
          hDs0TauPCone09->Fill(PCone09);
          hDs0TauPCone06->Fill(PCone06);
          hDs0TauPCone03->Fill(PCone03);
        }
        // Ds1TauNu decays
        if(abs(Ds_MC_MOTHER_ID)==20433 && abs(Ds_TRUEID) == 431){
          hDs1TauMult15->Fill(Ds_1_50_nc_mult);
          hDs1TauMult12->Fill(Ds_1_20_nc_mult);
          hDs1TauMult09->Fill(Ds_0_90_nc_mult);
          hDs1TauMult06->Fill(Ds_0_60_nc_mult);
          hDs1TauMult03->Fill(Ds_0_30_nc_mult);
          hDs1TauMaxCone->Fill(TMath::Max(TMath::Max(deltaRKpl,deltaRKmi),deltaRPi));
          hDs1TauAsym15->Fill(AsymP15);
          hDs1TauAsym12->Fill(AsymP12);
          hDs1TauAsym09->Fill(AsymP09);
          hDs1TauAsym06->Fill(AsymP06);
          hDs1TauAsym03->Fill(AsymP03);
          hDs1TauPCone15->Fill(PCone15);
          hDs1TauPCone12->Fill(PCone12);
          hDs1TauPCone09->Fill(PCone09);
          hDs1TauPCone06->Fill(PCone06);
          hDs1TauPCone03->Fill(PCone03);
        }
        // Ds'TauNu decays 
        if(abs(Ds_MC_MOTHER_ID)==10433 && abs(Ds_TRUEID) == 431){
          hDsprTauMult15->Fill(Ds_1_50_nc_mult);
          hDsprTauMult12->Fill(Ds_1_20_nc_mult);
          hDsprTauMult09->Fill(Ds_0_90_nc_mult);
          hDsprTauMult06->Fill(Ds_0_60_nc_mult);
          hDsprTauMult03->Fill(Ds_0_30_nc_mult);
          hDsprTauMaxCone->Fill(TMath::Max(TMath::Max(deltaRKpl,deltaRKmi),deltaRPi));
          hDsprTauAsym15->Fill(AsymP15);
          hDsprTauAsym12->Fill(AsymP12);
          hDsprTauAsym09->Fill(AsymP09);
          hDsprTauAsym06->Fill(AsymP06);
          hDsprTauAsym03->Fill(AsymP03);
          hDsprTauPCone15->Fill(PCone15);
          hDsprTauPCone12->Fill(PCone12);
          hDsprTauPCone09->Fill(PCone09);
          hDsprTauPCone06->Fill(PCone06);
          hDsprTauPCone03->Fill(PCone03);
        }
      */
      }
      // Mu decays
      if(abs(mu_MC_MOTHER_ID) == 531 && abs(mu_TRUEID) == 13){
        // DsMuNu decays
        if(abs(Ds_MC_MOTHER_ID) == 531 && abs(Ds_TRUEID) == 431){   
          /*
          hDsMuMult15->Fill(Ds_1_50_nc_mult);
          hDsMuMult12->Fill(Ds_1_20_nc_mult);
          hDsMuMult09->Fill(Ds_0_90_nc_mult);
          hDsMuMult06->Fill(Ds_0_60_nc_mult);
          hDsMuMult03->Fill(Ds_0_30_nc_mult);
          hDsMuMassWithG15->Fill(MassDsG_1_50);
          hDsMuMassWithG12->Fill(MassDsG_1_20);
          hDsMuMassWithG09->Fill(MassDsG_0_90);
          */
          hDsMuMassWithG06->Fill(MassDsG_0_60);
          hDsMuMassWithG03->Fill(MassDsG_0_30); 
          /*
          hDsMuMaxPtP15->Fill(MaxPtP_1_5);
          hDsMuMaxPtP12->Fill(MaxPtP_1_2);
          hDsMuMaxPtP09->Fill(MaxPtP_0_9);
          hDsMuMaxPtP06->Fill(MaxPtP_0_6);
          hDsMuMaxPtP03->Fill(MaxPtP_0_3);
          hDsMuMaxPtPt15->Fill(MaxPtPt_1_5);
          hDsMuMaxPtPt12->Fill(MaxPtPt_1_2);
          hDsMuMaxPtPt09->Fill(MaxPtPt_0_9);
          hDsMuMaxPtPt06->Fill(MaxPtPt_0_6);
          hDsMuMaxPtPt03->Fill(MaxPtPt_0_3);
          if(MassDsG_1_50>2000 && (MassDsG_1_50-2112.1)<30){
            hDsMuRightPtP15->Fill(MaxPtP_1_5);
            hDsMuRightPtPt15->Fill(MaxPtPt_1_5);
          }
          if(MassDsG_1_50>2000 && (MassDsG_1_20-2112.1)<30){
            hDsMuRightPtP12->Fill(MaxPtP_1_2);
            hDsMuRightPtPt12->Fill(MaxPtPt_1_2);
          }
          if(MassDsG_1_50>2000 && (MassDsG_0_90-2112.1)<30){
            hDsMuRightPtP09->Fill(MaxPtP_0_9);
            hDsMuRightPtPt09->Fill(MaxPtPt_0_9);          
          }
          if(MassDsG_1_50>2000 && (MassDsG_0_60-2112.1)<30){
            hDsMuRightPtP06->Fill(MaxPtP_0_6);
            hDsMuRightPtPt06->Fill(MaxPtPt_0_6);
          }
          if(MassDsG_1_50>2000 && (MassDsG_0_30-2112.1)<30){
            hDsMuRightPtP03->Fill(MaxPtP_0_3);
            hDsMuRightPtPt03->Fill(MaxPtPt_0_3);
          }
          hDsMuMaxCone->Fill(TMath::Max(TMath::Max(deltaRKpl,deltaRKmi),deltaRPi));
          hDsMuAsym15->Fill(AsymP15);
          hDsMuAsym12->Fill(AsymP12);
          hDsMuAsym09->Fill(AsymP09);
          hDsMuAsym06->Fill(AsymP06);
          hDsMuAsym03->Fill(AsymP03);
          hDsMuPCone15->Fill(PCone15);
          hDsMuPCone12->Fill(PCone12);
          hDsMuPCone09->Fill(PCone09);
          hDsMuPCone06->Fill(PCone06);
          hDsMuPCone03->Fill(PCone03);
          */
        }
        // Ds*MuNu decays
        if(abs(Ds_MC_MOTHER_ID) == 433 && abs(Ds_TRUEID) == 431){
          /*
          hDsstMuMult15->Fill(Ds_1_50_nc_mult);
          hDsstMuMult12->Fill(Ds_1_20_nc_mult);
          hDsstMuMult09->Fill(Ds_0_90_nc_mult);
          hDsstMuMult06->Fill(Ds_0_60_nc_mult);
          hDsstMuMult03->Fill(Ds_0_30_nc_mult);
          hDsstMuMassWithG15->Fill(MassDsG_1_50);
          hDsstMuMassWithG12->Fill(MassDsG_1_20);
          hDsstMuMassWithG09->Fill(MassDsG_0_90);
          */
          hDsstMuMassWithG06->Fill(MassDsG_0_60);
          hDsstMuMassWithG03->Fill(MassDsG_0_30); 
          /*
          hDsstMuMaxPtP15->Fill(MaxPtP_1_5);
          hDsstMuMaxPtP12->Fill(MaxPtP_1_2);
          hDsstMuMaxPtP09->Fill(MaxPtP_0_9);
          hDsstMuMaxPtP06->Fill(MaxPtP_0_6);
          hDsstMuMaxPtP03->Fill(MaxPtP_0_3);
          hDsstMuMaxPtPt15->Fill(MaxPtPt_1_5);
          hDsstMuMaxPtPt12->Fill(MaxPtPt_1_2);
          hDsstMuMaxPtPt09->Fill(MaxPtPt_0_9);
          hDsstMuMaxPtPt06->Fill(MaxPtPt_0_6);
          hDsstMuMaxPtPt03->Fill(MaxPtPt_0_3); 
          if(MassDsG_1_50>2000 && (MassDsG_1_50-2112.1)<30){
            hDsstMuRightPtP15->Fill(MaxPtP_1_5);
            hDsstMuRightPtPt15->Fill(MaxPtPt_1_5);
          }
          if(MassDsG_1_50>2000 && (MassDsG_1_20-2112.1)<30){
            hDsstMuRightPtP12->Fill(MaxPtP_1_2);
            hDsstMuRightPtPt12->Fill(MaxPtPt_1_2);
          }
          if(MassDsG_1_50>2000 && (MassDsG_0_90-2112.1)<30){
            hDsstMuRightPtP09->Fill(MaxPtP_0_9);
            hDsstMuRightPtPt09->Fill(MaxPtPt_0_9);
          }
          if(MassDsG_1_50>2000 && (MassDsG_0_60-2112.1)<30){
            hDsstMuRightPtP06->Fill(MaxPtP_0_6);
            hDsstMuRightPtPt06->Fill(MaxPtPt_0_6);
          }
          if(MassDsG_1_50>2000 && (MassDsG_0_30-2112.1)<30){
            hDsstMuRightPtP03->Fill(MaxPtP_0_3);
            hDsstMuRightPtPt03->Fill(MaxPtPt_0_3);
          } 
          hDsstMuMaxCone->Fill(TMath::Max(TMath::Max(deltaRKpl,deltaRKmi),deltaRPi));
          hDsstMuAsym15->Fill(AsymP15);
          hDsstMuAsym12->Fill(AsymP12);
          hDsstMuAsym09->Fill(AsymP09);
          hDsstMuAsym06->Fill(AsymP06);
          hDsstMuAsym03->Fill(AsymP03);
          hDsstMuPCone15->Fill(PCone15);
          hDsstMuPCone12->Fill(PCone12);
          hDsstMuPCone09->Fill(PCone09);
          hDsstMuPCone06->Fill(PCone06);
          hDsstMuPCone03->Fill(PCone03);
          */
        }
        /*
        // Ds0MuNu decays
        if(abs(Ds_MC_MOTHER_ID) == 10431 && abs(Ds_TRUEID) == 431){
          hDs0MuMult15->Fill(Ds_1_50_nc_mult);
          hDs0MuMult12->Fill(Ds_1_20_nc_mult);
          hDs0MuMult09->Fill(Ds_0_90_nc_mult);
          hDs0MuMult06->Fill(Ds_0_60_nc_mult);
          hDs0MuMult03->Fill(Ds_0_30_nc_mult);          
          hDs0MuMaxCone->Fill(TMath::Max(TMath::Max(deltaRKpl,deltaRKmi),deltaRPi));
          hDs0MuAsym15->Fill(AsymP15);
          hDs0MuAsym12->Fill(AsymP12);
          hDs0MuAsym09->Fill(AsymP09);
          hDs0MuAsym06->Fill(AsymP06);
          hDs0MuAsym03->Fill(AsymP03);
          hDs0MuPCone15->Fill(PCone15);
          hDs0MuPCone12->Fill(PCone12);
          hDs0MuPCone09->Fill(PCone09);
          hDs0MuPCone06->Fill(PCone06);
          hDs0MuPCone03->Fill(PCone03);
        }
        // Ds1MuNu decays
        if(abs(Ds_MC_MOTHER_ID) == 20433 && abs(Ds_TRUEID) == 431){
          hDs1MuMult15->Fill(Ds_1_50_nc_mult);
          hDs1MuMult12->Fill(Ds_1_20_nc_mult);
          hDs1MuMult09->Fill(Ds_0_90_nc_mult);
          hDs1MuMult06->Fill(Ds_0_60_nc_mult);
          hDs1MuMult03->Fill(Ds_0_30_nc_mult);      
          hDs1MuMaxCone->Fill(TMath::Max(TMath::Max(deltaRKpl,deltaRKmi),deltaRPi));
          hDs1MuAsym15->Fill(AsymP15);
          hDs1MuAsym12->Fill(AsymP12);
          hDs1MuAsym09->Fill(AsymP09);
          hDs1MuAsym06->Fill(AsymP06);
          hDs1MuAsym03->Fill(AsymP03);
          hDs1MuPCone15->Fill(PCone15);
          hDs1MuPCone12->Fill(PCone12);
          hDs1MuPCone09->Fill(PCone09);
          hDs1MuPCone06->Fill(PCone06);
          hDs1MuPCone03->Fill(PCone03);
        }
        // Ds'MuNu decays
        if(abs(Ds_MC_MOTHER_ID) == 10433 && abs(Ds_TRUEID) == 431){
          hDsprMuMult15->Fill(Ds_1_50_nc_mult);
          hDsprMuMult12->Fill(Ds_1_20_nc_mult);
          hDsprMuMult09->Fill(Ds_0_90_nc_mult);
          hDsprMuMult06->Fill(Ds_0_60_nc_mult);
          hDsprMuMult03->Fill(Ds_0_30_nc_mult);
          hDsprMuMaxCone->Fill(TMath::Max(TMath::Max(deltaRKpl,deltaRKmi),deltaRPi));
          hDsprMuAsym15->Fill(AsymP15);
          hDsprMuAsym12->Fill(AsymP12);
          hDsprMuAsym09->Fill(AsymP09);
          hDsprMuAsym06->Fill(AsymP06);
          hDsprMuAsym03->Fill(AsymP03);
          hDsprMuPCone15->Fill(PCone15);
          hDsprMuPCone12->Fill(PCone12);
          hDsprMuPCone09->Fill(PCone09);
          hDsprMuPCone06->Fill(PCone06);
          hDsprMuPCone03->Fill(PCone03);
        }
        */
      }

   // if (Cut(ientry) < 0) continue;

   }
/*
   hDsMuRightPtPt15->Write();
   hDsMuRightPtPt12->Write();
   hDsMuRightPtPt09->Write();
   hDsMuRightPtPt06->Write();
   hDsMuRightPtPt03->Write();
   hDsTauRightPtPt15->Write();
   hDsTauRightPtPt12->Write();
   hDsTauRightPtPt09->Write();
   hDsTauRightPtPt06->Write();
   hDsTauRightPtPt03->Write();

   hDsstMuRightPtPt15->Write();
   hDsstMuRightPtPt12->Write();
   hDsstMuRightPtPt09->Write();
   hDsstMuRightPtPt06->Write();
   hDsstMuRightPtPt03->Write();
   hDsstTauRightPtPt15->Write();
   hDsstTauRightPtPt12->Write();
   hDsstTauRightPtPt09->Write();
   hDsstTauRightPtPt06->Write();
   hDsstTauRightPtPt03->Write();

   hDsMuMaxPtPt15->Write();
   hDsMuMaxPtPt12->Write();
   hDsMuMaxPtPt09->Write();
   hDsMuMaxPtPt06->Write();
   hDsMuMaxPtPt03->Write();
   hDsTauMaxPtPt15->Write();
   hDsTauMaxPtPt12->Write();
   hDsTauMaxPtPt09->Write();
   hDsTauMaxPtPt06->Write();
   hDsTauMaxPtPt03->Write();

   hDsstMuMaxPtPt15->Write();
   hDsstMuMaxPtPt12->Write();
   hDsstMuMaxPtPt09->Write();
   hDsstMuMaxPtPt06->Write();
   hDsstMuMaxPtPt03->Write();
   hDsstTauMaxPtPt15->Write();
   hDsstTauMaxPtPt12->Write();
   hDsstTauMaxPtPt09->Write();
   hDsstTauMaxPtPt06->Write();
   hDsstTauMaxPtPt03->Write();

   hDsMuRightPtP15->Write();
   hDsMuRightPtP12->Write();
   hDsMuRightPtP09->Write();
   hDsMuRightPtP06->Write();
   hDsMuRightPtP03->Write();
   hDsTauRightPtP15->Write();
   hDsTauRightPtP12->Write();
   hDsTauRightPtP09->Write();
   hDsTauRightPtP06->Write();
   hDsTauRightPtP03->Write();

   hDsstMuRightPtP15->Write();
   hDsstMuRightPtP12->Write();
   hDsstMuRightPtP09->Write();
   hDsstMuRightPtP06->Write();
   hDsstMuRightPtP03->Write();
   hDsstTauRightPtP15->Write();
   hDsstTauRightPtP12->Write();
   hDsstTauRightPtP09->Write();
   hDsstTauRightPtP06->Write();
   hDsstTauRightPtP03->Write();

   hDsMuMaxPtP15->Write();
   hDsMuMaxPtP12->Write();
   hDsMuMaxPtP09->Write();
   hDsMuMaxPtP06->Write();
   hDsMuMaxPtP03->Write();
   hDsTauMaxPtP15->Write();
   hDsTauMaxPtP12->Write();
   hDsTauMaxPtP09->Write();
   hDsTauMaxPtP06->Write();
   hDsTauMaxPtP03->Write();

   hDsstMuMaxPtP15->Write();
   hDsstMuMaxPtP12->Write();
   hDsstMuMaxPtP09->Write();
   hDsstMuMaxPtP06->Write();
   hDsstMuMaxPtP03->Write();
   hDsstTauMaxPtP15->Write();
   hDsstTauMaxPtP12->Write();
   hDsstTauMaxPtP09->Write();
   hDsstTauMaxPtP06->Write();
   hDsstTauMaxPtP03->Write();
*/
/*  
   hDsMuMassWithG15->Write();
   hDsMuMassWithG12->Write();
   hDsMuMassWithG09->Write();
*/
   hDsMuMassWithG06->Write();
   hDsMuMassWithG03->Write();
/*
   hDsTauMassWithG15->Write();
   hDsTauMassWithG12->Write();
   hDsTauMassWithG09->Write();
*/
   hDsTauMassWithG06->Write();
   hDsTauMassWithG03->Write();
/*
   hDsstMuMassWithG15->Write();
   hDsstMuMassWithG12->Write();
   hDsstMuMassWithG09->Write();
*/
   hDsstMuMassWithG06->Write();
   hDsstMuMassWithG03->Write();
/*
   hDsstTauMassWithG15->Write();
   hDsstTauMassWithG12->Write();
   hDsstTauMassWithG09->Write();
*/
   hDsstTauMassWithG06->Write();
   hDsstTauMassWithG03->Write();
/*
   hDsMuAsym15->Write();
   hDsMuAsym12->Write();
   hDsMuAsym09->Write();
   hDsMuAsym06->Write();
   hDsMuAsym03->Write();
   hDsTauAsym15->Write();
   hDsTauAsym12->Write();
   hDsTauAsym09->Write();
   hDsTauAsym06->Write();
   hDsTauAsym03->Write();

   hDsMuPCone15->Write();
   hDsMuPCone12->Write();
   hDsMuPCone09->Write();
   hDsMuPCone06->Write();
   hDsMuPCone03->Write();
   hDsTauPCone15->Write();
   hDsTauPCone12->Write();
   hDsTauPCone09->Write();
   hDsTauPCone06->Write();
   hDsTauPCone03->Write();
 
   hDsstMuAsym15->Write();
   hDsstMuAsym12->Write();
   hDsstMuAsym09->Write();
   hDsstMuAsym06->Write();
   hDsstMuAsym03->Write();
   hDsstTauAsym15->Write();
   hDsstTauAsym12->Write();
   hDsstTauAsym09->Write();
   hDsstTauAsym06->Write();
   hDsstTauAsym03->Write();

   hDsstMuPCone15->Write();
   hDsstMuPCone12->Write();
   hDsstMuPCone09->Write();
   hDsstMuPCone06->Write();
   hDsstMuPCone03->Write();
   hDsstTauPCone15->Write();
   hDsstTauPCone12->Write();
   hDsstTauPCone09->Write();
   hDsstTauPCone06->Write();
   hDsstTauPCone03->Write();

   hDs0MuAsym15->Write();
   hDs0MuAsym12->Write();
   hDs0MuAsym09->Write();
   hDs0MuAsym06->Write();
   hDs0MuAsym03->Write();
   hDs0TauAsym15->Write();
   hDs0TauAsym12->Write();
   hDs0TauAsym09->Write();
   hDs0TauAsym06->Write();
   hDs0TauAsym03->Write();

   hDs0MuPCone15->Write();
   hDs0MuPCone12->Write();
   hDs0MuPCone09->Write();
   hDs0MuPCone06->Write();
   hDs0MuPCone03->Write();
   hDs0TauPCone15->Write();
   hDs0TauPCone12->Write();
   hDs0TauPCone09->Write();
   hDs0TauPCone06->Write();
   hDs0TauPCone03->Write();

   hDs1MuAsym15->Write();
   hDs1MuAsym12->Write();
   hDs1MuAsym09->Write();
   hDs1MuAsym06->Write();
   hDs1MuAsym03->Write();
   hDs1TauAsym15->Write();
   hDs1TauAsym12->Write();
   hDs1TauAsym09->Write();
   hDs1TauAsym06->Write();
   hDs1TauAsym03->Write();

   hDs1MuPCone15->Write();
   hDs1MuPCone12->Write();
   hDs1MuPCone09->Write();
   hDs1MuPCone06->Write();
   hDs1MuPCone03->Write();
   hDs1TauPCone15->Write();
   hDs1TauPCone12->Write();
   hDs1TauPCone09->Write();
   hDs1TauPCone06->Write();
   hDs1TauPCone03->Write();

   hDsprMuAsym15->Write();
   hDsprMuAsym12->Write();
   hDsprMuAsym09->Write();
   hDsprMuAsym06->Write();
   hDsprMuAsym03->Write();
   hDsprTauAsym15->Write();
   hDsprTauAsym12->Write();
   hDsprTauAsym09->Write();
   hDsprTauAsym06->Write();
   hDsprTauAsym03->Write();

   hDsprMuPCone15->Write();
   hDsprMuPCone12->Write();
   hDsprMuPCone09->Write();
   hDsprMuPCone06->Write();
   hDsprMuPCone03->Write();
   hDsprTauPCone15->Write();
   hDsprTauPCone12->Write();
   hDsprTauPCone09->Write();
   hDsprTauPCone06->Write();
   hDsprTauPCone03->Write();

   hDsMuMaxCone->Write();
   hDsstMuMaxCone->Write();
   hDs0MuMaxCone->Write();
   hDs1MuMaxCone->Write();
   hDsprMuMaxCone->Write();
   hDsTauMaxCone->Write();
   hDsstTauMaxCone->Write();
   hDs0TauMaxCone->Write();
   hDs1TauMaxCone->Write();
   hDsprTauMaxCone->Write();
 
   hDsMuMult15->Write();
   hDsTauMult15->Write();
   hDsstMuMult15->Write();
   hDsstTauMult15->Write();
   hDs0MuMult15->Write();
   hDs0TauMult15->Write();    
   hDs1MuMult15->Write();
   hDs1TauMult15->Write();
   hDsprMuMult15->Write();
   hDsprTauMult15->Write(); 

   hDsMuMult12->Write();
   hDsTauMult12->Write();
   hDsstMuMult12->Write();
   hDsstTauMult12->Write();
   hDs0MuMult12->Write();
   hDs0TauMult12->Write();
   hDs1MuMult12->Write();
   hDs1TauMult12->Write();
   hDsprMuMult12->Write();
   hDsprTauMult12->Write();

   hDsMuMult09->Write();
   hDsTauMult09->Write();
   hDsstMuMult09->Write();
   hDsstTauMult09->Write();
   hDs0MuMult09->Write();
   hDs0TauMult09->Write();
   hDs1MuMult09->Write();
   hDs1TauMult09->Write();
   hDsprMuMult09->Write();
   hDsprTauMult09->Write();

   hDsMuMult06->Write();
   hDsTauMult06->Write();
   hDsstMuMult06->Write();
   hDsstTauMult06->Write();
   hDs0MuMult06->Write();
   hDs0TauMult06->Write();
   hDs1MuMult06->Write();
   hDs1TauMult06->Write();
   hDsprMuMult06->Write();
   hDsprTauMult06->Write();

   hDsMuMult03->Write();
   hDsTauMult03->Write();
   hDsstMuMult03->Write();
   hDsstTauMult03->Write();
   hDs0MuMult03->Write();
   hDs0TauMult03->Write();
   hDs1MuMult03->Write();
   hDs1TauMult03->Write();
   hDsprMuMult03->Write();
   hDsprTauMult03->Write();
*/
}
