#define NeutralIsoData_cxx
#include "NeutralIsoData.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>

void NeutralIsoData::Loop()
{
//   In a ROOT session, you can do:
//      root> .L NeutralIsoData.C
//      root> NeutralIsoData t
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

   int nbinsMu = 200;
   int nbinsTau = 200;

   // photon mass histograms
   TH1F *hDsTauMassWithG06 = new TH1F("DsTauMassWithG06", "DsTauNu Ds Mass with photon 0.6", nbinsTau, 1900, 3000);
   TH1F *hDsTauMassWithG03 = new TH1F("DsTauMassWithG03", "DsTauNu Ds Mass with photon 0.3", nbinsTau, 1900, 2500);

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if (jentry%100000 == 0) std::cout << "Processing event " << jentry << std::endl;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if (Ds_MM > 1950 && Ds_MM < 1987 && Kpl_ProbNNk>0.15 && Kmi_ProbNNk>0.15){
        float MassDsG_0_60 = sqrt((pow((sqrt(Ds_0_60_nc_maxPt_PX*Ds_0_60_nc_maxPt_PX+Ds_0_60_nc_maxPt_PY*Ds_0_60_nc_maxPt_PY+Ds_0_60_nc_maxPt_PZ*Ds_0_60_nc_maxPt_PZ)+Ds_PE),2) ) - ( pow(Ds_0_60_nc_maxPt_PX+Ds_PX,2)+pow(Ds_0_60_nc_maxPt_PY+Ds_PY,2)+pow(Ds_0_60_nc_maxPt_PZ+Ds_PZ,2) ) );
        float MassDsG_0_30 = sqrt((pow((sqrt(Ds_0_30_nc_maxPt_PX*Ds_0_30_nc_maxPt_PX+Ds_0_30_nc_maxPt_PY*Ds_0_30_nc_maxPt_PY+Ds_0_30_nc_maxPt_PZ*Ds_0_30_nc_maxPt_PZ)+Ds_PE),2) ) - ( pow(Ds_0_30_nc_maxPt_PX+Ds_PX,2)+pow(Ds_0_30_nc_maxPt_PY+Ds_PY,2)+pow(Ds_0_30_nc_maxPt_PZ+Ds_PZ,2) ) ); 

        hDsTauMassWithG06->Fill(MassDsG_0_60);
        hDsTauMassWithG03->Fill(MassDsG_0_30);
      }

   // if (Cut(ientry) < 0) continue;

   }
   hDsTauMassWithG06->Write();
   hDsTauMassWithG03->Write();
}
