#define MCTuple_cxx
#include "MCTuple.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void MCTuple::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L MCTuple.C
//      Root > MCTuple t
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

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}
// ####################################################################################################
Double_t MCTuple::psiMMass2(){
  return 
    (J_psi_1S_TRUEP_E + piminus_TRUEP_E)*
    (J_psi_1S_TRUEP_E + piminus_TRUEP_E) -
    (J_psi_1S_TRUEP_X + piminus_TRUEP_X)*
    (J_psi_1S_TRUEP_X + piminus_TRUEP_X)-
    (J_psi_1S_TRUEP_Y + piminus_TRUEP_Y)*
    (J_psi_1S_TRUEP_Y + piminus_TRUEP_Y) -
    (J_psi_1S_TRUEP_Z + piminus_TRUEP_Z)*
    (J_psi_1S_TRUEP_Z + piminus_TRUEP_Z) ;
  
}
// ####################################################################################################
Double_t MCTuple::pMMass2(){
  return 
    (pplus_TRUEP_E + piminus_TRUEP_E)*(pplus_TRUEP_E + piminus_TRUEP_E) -
    (pplus_TRUEP_X + piminus_TRUEP_X)*(pplus_TRUEP_X + piminus_TRUEP_X) -
    (pplus_TRUEP_Y + piminus_TRUEP_Y)*(pplus_TRUEP_Y + piminus_TRUEP_Y) -
    (pplus_TRUEP_Z + piminus_TRUEP_Z)*(pplus_TRUEP_Z + piminus_TRUEP_Z);
  
}
// ####################################################################################################
Double_t MCTuple::psipMass2(){
  return 
    (J_psi_1S_TRUEP_E + pplus_TRUEP_E)*
    (J_psi_1S_TRUEP_E + pplus_TRUEP_E) -
    (J_psi_1S_TRUEP_X + pplus_TRUEP_X)*
    (J_psi_1S_TRUEP_X + pplus_TRUEP_X) -
    (J_psi_1S_TRUEP_Y + pplus_TRUEP_Y)*
    (J_psi_1S_TRUEP_Y + pplus_TRUEP_Y) -
    (J_psi_1S_TRUEP_Z + pplus_TRUEP_Z)*
    (J_psi_1S_TRUEP_Z + pplus_TRUEP_Z) ;
}
// ####################################################################################################
Double_t MCTuple::mprime(){
  Double_t m = (sqrt(psipMass2())-m_psi-m_p)/(m_Lb-m_psi-m_p-(m_isPi?m_pi:m_K));
  Double_t mp = (1./TMath::Pi())*acos(2*m-1) ;
  if (!(mp>=0.)){
    // std::cout << "Error with mprime : psipM " <<  psipMass2() << " m: " << m << std::endl ;
    return -1. ;
  }  
  return mp ;
}
// ####################################################################################################
Double_t MCTuple::thetaprime(){
  Double_t mjp2 = psipMass2();
  Double_t mph2 = pMMass2();
  Double_t mjh2 = psiMMass2();
  Double_t mh2 = (m_isPi?m_pi*m_pi:m_K*m_K);
  Double_t t1 = mjp2*(mph2-mjh2)-(m_p*m_p-m_psi*m_psi)*(m_Lb*m_Lb-mh2);
  Double_t t2a = mjp2+m_psi*m_psi-m_p*m_p;
  Double_t t2 = t2a*t2a - 4*mjp2*m_psi*m_psi;
  Double_t t3a = m_Lb*m_Lb-mh2-mjp2 ;
  Double_t t3 = t3a*t3a - 4*mjp2*mh2;
  Double_t th = (1./TMath::Pi())*acos(t1/(sqrt(t2)*sqrt(t3))) ;
  if (!(th>=0.)){
    /*
      std::cout << "Error with thetaprime : mjp2 " << mjp2  << " mph2 " << mph2 << " mjh2 " << mjh2 
      << " Stream " << (m_isPi?"pi":"K") << std::endl ; 
      std::cout << "     -> t1 " << t1 << " t2a " << t2a << " t2 " << t2 << " t3a " 
      << t3a << " t3 " << t3 << " fraction " << t1/(sqrt(t2)*sqrt(t3)) << " - th " << th << std::endl ; 
    */
    return -1. ;
  }
  return th ;
}
