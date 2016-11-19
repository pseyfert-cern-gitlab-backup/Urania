#define KinVarsReco_cxx
#include "KinVarsReco.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void KinVarsReco::Loop()
{
//   In a ROOT session, you can do:
//      root> .L KinVarsReco.C
//      root> KinVarsReco t
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

   TFile *f = new TFile("histosKinReco.root","new");
 
   TH1F *hDsMuCorrMass = new TH1F("DsMuCorrMass", "DsMuNu corrected mass", 100, 2000, 5500);
   TH1F *hDsTauCorrMass = new TH1F("DsTauCorrMass", "DsTauNu corrected mass", 100, 2000, 5500);
   TH1F *hDsMuCorrMassErr = new TH1F("DsMuCorrMassErr", "DsMuNu corrected mass error", 100, 0, 500);
   TH1F *hDsTauCorrMassErr = new TH1F("DsTauCorrMassErr", "DsTauNu corrected mass error", 100, 0, 500);
   TH1F *hDsMuBP = new TH1F("DsMuBP", "DsMuNu B momentum", 100, 0, 250000);
   TH1F *hDsTauBP = new TH1F("DsTauBP", "DsTauNu B momentum", 100, 0, 250000);
   TH1F *hDsMuBPT = new TH1F("DsMuBPT", "DsMuNu B pT", 100, 0, 30000);
   TH1F *hDsTauBPT = new TH1F("DsTauBPT", "DsTauNu B pT", 100, 0, 30000);
   TH1F *hDsMuVChi2 = new TH1F("DsMuVChi2", "DsMuNu B vertex chi2", 100, 0, 6);
   TH1F *hDsTauVChi2 = new TH1F("DsTauVChi2", "DsTauNu B vertex chi2", 100, 0, 6);
   TH1F *hDsMuDsVChi2 = new TH1F("DsMuDsVChi2", "DsMuNu Ds vertex chi2", 100, 0, 4);
   TH1F *hDsTauDsVChi2 = new TH1F("DsTauDsVChi2", "DsTauNu Ds vertex chi2", 100, 0, 4);
   TH1F *hDsMuDOCA = new TH1F("DsMuDOCA", "DsMuNu B DOCA", 100, 0, 0.5);
   TH1F *hDsTauDOCA = new TH1F("DsTauDOCA", "DsTauNu B DOCA", 100, 0, 0.5);
   TH1F *hDsMuDIRA = new TH1F("DsMuDIRA", "DsMuNu B DIRA", 100, 0.999, 1.0);
   TH1F *hDsTauDIRA = new TH1F("DsTauDIRA", "DsTauNu B DIRA", 100, 0.999, 1.0);
   TH1F *hDsMuFD = new TH1F("DsMuFD", "DsMuNu B FD", 100, 0, 200);
   TH1F *hDsTauFD = new TH1F("DsTauFD", "DsTauNu B FD", 100, 0, 200);
   TH1F *hDsMuIP = new TH1F("DsMuIP", "DsMuNu B IP chi2", 100, 0, 2);
   TH1F *hDsTauIP = new TH1F("DsTauIP", "DsTauNu B IP chi2", 100, 0, 2);
   TH1F *hDsMuDsMass = new TH1F("DsMuDsMass", "DsMuNu Ds mass", 100, 1900, 2040);
   TH1F *hDsTauDsMass = new TH1F("DsTauDsMass", "DsTauNu Ds mass", 100, 1900, 2040);
   TH1F *hDsTauMuP = new TH1F("DsTauMuP", "DsTauNu mu momentum", 100, 0, 250000);
   TH1F *hDsMuMuP = new TH1F("DsMuMuP", "DsMuNu mu momentum", 100, 0, 250000); 
   TH1F *hDsMuMuPT = new TH1F("DsMuMuPT", "DsMuNu mu pT", 100, 0, 30000);
   TH1F *hDsTauMuPT = new TH1F("DsTauMuPT", "DsTauNu mu pT", 100, 0, 30000); 
   TH1F *hDsTauDsP = new TH1F("DsTauDsP", "DsTauNu Ds momentum", 100, 0, 250000);
   TH1F *hDsMuDsP = new TH1F("DsMuDsP", "DsMuNu Ds momentum", 100, 0, 250000);
   TH1F *hDsMuDsPT = new TH1F("DsMuDsPT", "DsMuNu Ds pT", 100, 0, 30000);
   TH1F *hDsTauDsPT = new TH1F("DsTauDsPT", "DsTauNu Ds pT", 100, 0, 30000);

   TH1F *hDsstMuCorrMass = new TH1F("DsstMuCorrMass", "Ds*MuNu corrected mass", 100, 2000, 5500);
   TH1F *hDsstTauCorrMass = new TH1F("DsstTauCorrMass", "Ds*TauNu corrected mass", 100, 2000, 5500);
   TH1F *hDsstMuCorrMassErr = new TH1F("DsstMuCorrMassErr", "Ds*MuNu corrected mass error", 100, 0, 500);
   TH1F *hDsstTauCorrMassErr = new TH1F("DsstTauCorrMassErr", "Ds*TauNu corrected mass error", 100, 0, 500);
   TH1F *hDsstMuBP = new TH1F("DsstMuBP", "Ds*MuNu B momentum", 100, 0, 250000);
   TH1F *hDsstTauBP = new TH1F("DsstTauBP", "Ds*TauNu B momentum", 100, 0, 250000);
   TH1F *hDsstMuBPT = new TH1F("DsstMuBPT", "Ds*MuNu B pT", 100, 0, 30000);
   TH1F *hDsstTauBPT = new TH1F("DsstTauBPT", "Ds*TauNu B pT", 100, 0, 30000);
   TH1F *hDsstMuVChi2 = new TH1F("DsstMuVChi2", "Ds*MuNu B vertex chi2", 100, 0, 6);
   TH1F *hDsstTauVChi2 = new TH1F("DsstTauVChi2", "Ds*TauNu B vertex chi2", 100, 0, 6);
   TH1F *hDsstMuDsVChi2 = new TH1F("DsstMuDsVChi2", "Ds*MuNu Ds vertex chi2", 100, 0, 4);
   TH1F *hDsstTauDsVChi2 = new TH1F("DsstTauDsVChi2", "Ds*TauNu Ds vertex chi2", 100, 0, 4);
   TH1F *hDsstMuDOCA = new TH1F("DsstMuDOCA", "Ds*MuNu B DOCA", 100, 0, 0.5);
   TH1F *hDsstTauDOCA = new TH1F("DsstTauDOCA", "Ds*TauNu B DOCA", 100, 0, 0.5);
   TH1F *hDsstMuDIRA = new TH1F("DsstMuDIRA", "Ds*MuNu B DIRA", 100, 0.999, 1.0);
   TH1F *hDsstTauDIRA = new TH1F("DsstTauDIRA", "Ds*TauNu B DIRA", 100, 0.999, 1.0);
   TH1F *hDsstMuFD = new TH1F("DsstMuFD", "Ds*MuNu B FD", 100, 0, 200);
   TH1F *hDsstTauFD = new TH1F("DsstTauFD", "Ds*TauNu B FD", 100, 0, 200);
   TH1F *hDsstMuIP = new TH1F("DsstMuIP", "Ds*MuNu B IP chi2", 100, 0, 2);
   TH1F *hDsstTauIP = new TH1F("DsstTauIP", "Ds*TauNu B IP chi2", 100, 0, 2);
   TH1F *hDsstMuDsMass = new TH1F("DsstMuDsMass", "Ds*MuNu Ds mass", 100, 1900, 2040);
   TH1F *hDsstTauDsMass = new TH1F("DsstTauDsMass", "Ds*TauNu Ds mass", 100, 1900, 2040);
   TH1F *hDsstTauMuP = new TH1F("DsstTauMuP", "Ds*TauNu mu momentum", 100, 0, 250000);
   TH1F *hDsstMuMuP = new TH1F("DsstMuMuP", "Ds*MuNu mu momentum", 100, 0, 250000);
   TH1F *hDsstMuMuPT = new TH1F("DsstMuMuPT", "Ds*MuNu mu pT", 100, 0, 30000);
   TH1F *hDsstTauMuPT = new TH1F("DsstTauMuPT", "Ds*TauNu mu pT", 100, 0, 30000);
   TH1F *hDsstTauDsP = new TH1F("DsstTauDsP", "Ds*TauNu Ds momentum", 100, 0, 250000);
   TH1F *hDsstMuDsP = new TH1F("DsstMuDsP", "Ds*MuNu Ds momentum", 100, 0, 250000);
   TH1F *hDsstMuDsPT = new TH1F("DsstMuDsPT", "Ds*MuNu Ds pT", 100, 0, 30000);
   TH1F *hDsstTauDsPT = new TH1F("DsstTauDsPT", "Ds*TauNu Ds pT", 100, 0, 30000);

   TH1F *hDs0MuCorrMass = new TH1F("Ds0MuCorrMass", "Ds0MuNu corrected mass", 100, 2000, 5500);
   TH1F *hDs0TauCorrMass = new TH1F("Ds0TauCorrMass", "Ds0TauNu corrected mass", 100, 2000, 5500);
   TH1F *hDs0MuCorrMassErr = new TH1F("Ds0MuCorrMassErr", "Ds0MuNu corrected mass error", 100, 0, 500);
   TH1F *hDs0TauCorrMassErr = new TH1F("Ds0TauCorrMassErr", "Ds0TauNu corrected mass error", 100, 0, 500);
   TH1F *hDs0MuBP = new TH1F("Ds0MuBP", "Ds0MuNu B momentum", 100, 0, 250000);
   TH1F *hDs0TauBP = new TH1F("Ds0TauBP", "Ds0TauNu B momentum", 100, 0, 250000);
   TH1F *hDs0MuBPT = new TH1F("Ds0MuBPT", "Ds0MuNu B pT", 100, 0, 30000);
   TH1F *hDs0TauBPT = new TH1F("Ds0TauBPT", "Ds0TauNu B pT", 100, 0, 30000);
   TH1F *hDs0MuVChi2 = new TH1F("Ds0MuVChi2", "Ds0MuNu B vertex chi2", 100, 0, 6);
   TH1F *hDs0TauVChi2 = new TH1F("Ds0TauVChi2", "Ds0TauNu B vertex chi2", 100, 0, 6);
   TH1F *hDs0MuDsVChi2 = new TH1F("Ds0MuDsVChi2", "Ds0MuNu Ds vertex chi2", 100, 0, 4);
   TH1F *hDs0TauDsVChi2 = new TH1F("Ds0TauDsVChi2", "Ds0TauNu Ds vertex chi2", 100, 0, 4);
   TH1F *hDs0MuDOCA = new TH1F("Ds0MuDOCA", "Ds0MuNu B DOCA", 100, 0, 0.5);
   TH1F *hDs0TauDOCA = new TH1F("Ds0TauDOCA", "Ds0TauNu B DOCA", 100, 0, 0.5);
   TH1F *hDs0MuDIRA = new TH1F("Ds0MuDIRA", "Ds0MuNu B DIRA", 100, 0.999, 1.0);
   TH1F *hDs0TauDIRA = new TH1F("Ds0TauDIRA", "Ds0TauNu B DIRA", 100, 0.999, 1.0);
   TH1F *hDs0MuFD = new TH1F("Ds0MuFD", "Ds0MuNu B FD", 100, 0, 200);
   TH1F *hDs0TauFD = new TH1F("Ds0TauFD", "Ds0TauNu B FD", 100, 0, 200);
   TH1F *hDs0MuIP = new TH1F("Ds0MuIP", "Ds0MuNu B IP chi2", 100, 0, 2);
   TH1F *hDs0TauIP = new TH1F("Ds0TauIP", "Ds0TauNu B IP chi2", 100, 0, 2);
   TH1F *hDs0MuDsMass = new TH1F("Ds0MuDsMass", "Ds0MuNu Ds mass", 100, 1900, 2040);
   TH1F *hDs0TauDsMass = new TH1F("Ds0TauDsMass", "Ds0TauNu Ds mass", 100, 1900, 2040);
   TH1F *hDs0TauMuP = new TH1F("Ds0TauMuP", "Ds0TauNu mu momentum", 100, 0, 250000);
   TH1F *hDs0MuMuP = new TH1F("Ds0MuMuP", "Ds0MuNu mu momentum", 100, 0, 250000);
   TH1F *hDs0MuMuPT = new TH1F("Ds0MuMuPT", "Ds0MuNu mu pT", 100, 0, 30000);
   TH1F *hDs0TauMuPT = new TH1F("Ds0TauMuPT", "Ds0TauNu mu pT", 100, 0, 30000);
   TH1F *hDs0TauDsP = new TH1F("Ds0TauDsP", "Ds0TauNu Ds momentum", 100, 0, 250000);
   TH1F *hDs0MuDsP = new TH1F("Ds0MuDsP", "Ds0MuNu Ds momentum", 100, 0, 250000);
   TH1F *hDs0MuDsPT = new TH1F("Ds0MuDsPT", "Ds0MuNu Ds pT", 100, 0, 30000);
   TH1F *hDs0TauDsPT = new TH1F("Ds0TauDsPT", "Ds0TauNu Ds pT", 100, 0, 30000);
 
   TH1F *hDs1MuCorrMass = new TH1F("Ds1MuCorrMass", "Ds1MuNu corrected mass", 100, 2000, 5500);
   TH1F *hDs1TauCorrMass = new TH1F("Ds1TauCorrMass", "Ds1TauNu corrected mass", 100, 2000, 5500);
   TH1F *hDs1MuCorrMassErr = new TH1F("Ds1MuCorrMassErr", "Ds1MuNu corrected mass error", 100, 0, 500);
   TH1F *hDs1TauCorrMassErr = new TH1F("Ds1TauCorrMassErr", "Ds1TauNu corrected mass error", 100, 0, 500);
   TH1F *hDs1MuBP = new TH1F("Ds1MuBP", "Ds1MuNu B momentum", 100, 0, 250000);
   TH1F *hDs1TauBP = new TH1F("Ds1TauBP", "Ds1TauNu B momentum", 100, 0, 250000);
   TH1F *hDs1MuBPT = new TH1F("Ds1MuBPT", "Ds1MuNu B pT", 100, 0, 30000);
   TH1F *hDs1TauBPT = new TH1F("Ds1TauBPT", "Ds1TauNu B pT", 100, 0, 30000);
   TH1F *hDs1MuVChi2 = new TH1F("Ds1MuVChi2", "Ds1MuNu B vertex chi2", 100, 0, 6);
   TH1F *hDs1TauVChi2 = new TH1F("Ds1TauVChi2", "Ds1TauNu B vertex chi2", 100, 0, 6);
   TH1F *hDs1MuDsVChi2 = new TH1F("Ds1MuDsVChi2", "Ds1MuNu Ds vertex chi2", 100, 0, 4);
   TH1F *hDs1TauDsVChi2 = new TH1F("Ds1TauDsVChi2", "Ds1TauNu Ds vertex chi2", 100, 0, 4);
   TH1F *hDs1MuDOCA = new TH1F("Ds1MuDOCA", "Ds1MuNu B DOCA", 100, 0, 0.5);
   TH1F *hDs1TauDOCA = new TH1F("Ds1TauDOCA", "Ds1TauNu B DOCA", 100, 0, 0.5);
   TH1F *hDs1MuDIRA = new TH1F("Ds1MuDIRA", "Ds1MuNu B DIRA", 100, 0.999, 1.0);
   TH1F *hDs1TauDIRA = new TH1F("Ds1TauDIRA", "Ds1TauNu B DIRA", 100, 0.999, 1.0);
   TH1F *hDs1MuFD = new TH1F("Ds1MuFD", "Ds1MuNu B FD", 100, 0, 200);
   TH1F *hDs1TauFD = new TH1F("Ds1TauFD", "Ds1TauNu B FD", 100, 0, 200);
   TH1F *hDs1MuIP = new TH1F("Ds1MuIP", "Ds1MuNu B IP chi2", 100, 0, 2);
   TH1F *hDs1TauIP = new TH1F("Ds1TauIP", "Ds1TauNu B IP chi2", 100, 0, 2);
   TH1F *hDs1MuDsMass = new TH1F("Ds1MuDsMass", "Ds1MuNu Ds mass", 100, 1900, 2040);
   TH1F *hDs1TauDsMass = new TH1F("Ds1TauDsMass", "Ds1TauNu Ds mass", 100, 1900, 2040);
   TH1F *hDs1TauMuP = new TH1F("Ds1TauMuP", "Ds1TauNu mu momentum", 100, 0, 250000);
   TH1F *hDs1MuMuP = new TH1F("Ds1MuMuP", "Ds1MuNu mu momentum", 100, 0, 250000);
   TH1F *hDs1MuMuPT = new TH1F("Ds1MuMuPT", "Ds1MuNu mu pT", 100, 0, 30000);
   TH1F *hDs1TauMuPT = new TH1F("Ds1TauMuPT", "Ds1TauNu mu pT", 100, 0, 30000);
   TH1F *hDs1TauDsP = new TH1F("Ds1TauDsP", "Ds1TauNu Ds momentum", 100, 0, 250000);
   TH1F *hDs1MuDsP = new TH1F("Ds1MuDsP", "Ds1MuNu Ds momentum", 100, 0, 250000);
   TH1F *hDs1MuDsPT = new TH1F("Ds1MuDsPT", "Ds1MuNu Ds pT", 100, 0, 30000);
   TH1F *hDs1TauDsPT = new TH1F("Ds1TauDsPT", "Ds1TauNu Ds pT", 100, 0, 30000);

   TH1F *hDsprMuCorrMass = new TH1F("DsprMuCorrMass", "DsprMuNu corrected mass", 100, 2000, 5500);
   TH1F *hDsprTauCorrMass = new TH1F("DsprTauCorrMass", "DsprTauNu corrected mass", 100, 2000, 5500);
   TH1F *hDsprMuCorrMassErr = new TH1F("DsprMuCorrMassErr", "DsprMuNu corrected mass error", 100, 0, 500);
   TH1F *hDsprTauCorrMassErr = new TH1F("DsprTauCorrMassErr", "DsprTauNu corrected mass error", 100, 0, 500);
   TH1F *hDsprMuBP = new TH1F("DsprMuBP", "DsprMuNu B momentum", 100, 0, 250000);
   TH1F *hDsprTauBP = new TH1F("DsprTauBP", "DsprTauNu B momentum", 100, 0, 250000);
   TH1F *hDsprMuBPT = new TH1F("DsprMuBPT", "DsprMuNu B pT", 100, 0, 30000);
   TH1F *hDsprTauBPT = new TH1F("DsprTauBPT", "DsprTauNu B pT", 100, 0, 30000);
   TH1F *hDsprMuVChi2 = new TH1F("DsprMuVChi2", "DsprMuNu B vertex chi2", 100, 0, 6);
   TH1F *hDsprTauVChi2 = new TH1F("DsprTauVChi2", "DsprTauNu B vertex chi2", 100, 0, 6);
   TH1F *hDsprMuDsVChi2 = new TH1F("DsprMuDsVChi2", "DsprMuNu Ds vertex chi2", 100, 0, 4);
   TH1F *hDsprTauDsVChi2 = new TH1F("DsprTauDsVChi2", "DsprTauNu Ds vertex chi2", 100, 0, 4);
   TH1F *hDsprMuDOCA = new TH1F("DsprMuDOCA", "DsprMuNu B DOCA", 100, 0, 0.5);
   TH1F *hDsprTauDOCA = new TH1F("DsprTauDOCA", "DsprTauNu B DOCA", 100, 0, 0.5);
   TH1F *hDsprMuDIRA = new TH1F("DsprMuDIRA", "DsprMuNu B DIRA", 100, 0.999, 1.0);
   TH1F *hDsprTauDIRA = new TH1F("DsprTauDIRA", "DsprTauNu B DIRA", 100, 0.999, 1.0);
   TH1F *hDsprMuFD = new TH1F("DsprMuFD", "DsprMuNu B FD", 100, 0, 200);
   TH1F *hDsprTauFD = new TH1F("DsprTauFD", "DsprTauNu B FD", 100, 0, 200);
   TH1F *hDsprMuIP = new TH1F("DsprMuIP", "DsprMuNu B IP chi2", 100, 0, 2);
   TH1F *hDsprTauIP = new TH1F("DsprTauIP", "DsprTauNu B IP chi2", 100, 0, 2);
   TH1F *hDsprMuDsMass = new TH1F("DsprMuDsMass", "DsprMuNu Ds mass", 100, 1900, 2040);
   TH1F *hDsprTauDsMass = new TH1F("DsprTauDsMass", "DsprTauNu Ds mass", 100, 1900, 2040);
   TH1F *hDsprTauMuP = new TH1F("DsprTauMuP", "DsprTauNu mu momentum", 100, 0, 250000);
   TH1F *hDsprMuMuP = new TH1F("DsprMuMuP", "DsprMuNu mu momentum", 100, 0, 250000);
   TH1F *hDsprMuMuPT = new TH1F("DsprMuMuPT", "DsprMuNu mu pT", 100, 0, 30000);
   TH1F *hDsprTauMuPT = new TH1F("DsprTauMuPT", "DsprTauNu mu pT", 100, 0, 30000);
   TH1F *hDsprTauDsP = new TH1F("DsprTauDsP", "DsprTauNu Ds momentum", 100, 0, 250000);
   TH1F *hDsprMuDsP = new TH1F("DsprMuDsP", "DsprMuNu Ds momentum", 100, 0, 250000);
   TH1F *hDsprMuDsPT = new TH1F("DsprMuDsPT", "DsprMuNu Ds pT", 100, 0, 30000);
   TH1F *hDsprTauDsPT = new TH1F("DsprTauDsPT", "DsprTauNu Ds pT", 100, 0, 30000);

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
