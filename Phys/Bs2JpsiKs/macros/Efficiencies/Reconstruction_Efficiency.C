/////////////////////////////////////////////////////////////////////////////////
// ***** MCTruth Reconstruction Efficiency for Bd->JpsiKs and Bs->JpsiKs ***** //
/////////////////////////////////////////////////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb
// - Determine the reconstruction efficiency for Bd->JpsiKs and Bs->JpsiKs using the MCTruth Samples


/////////////////////////////////////
// ***** Load useful classes ***** //
/////////////////////////////////////
#include "RooRealVar.h"

#include "TChain.h"
#include "TMath.h"

using namespace RooFit;

///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void recoEfficiency(TString Reco = "Reconstructed", bool SelCuts = false){

  /*
  // *** Overview of _Reconstructed ***
  Not Reconstructed = 0
  Charged Long = 1
  Charged Downstream = 2
  Neutral = 50
  // *** Overview of _Reconstructible ***
  Outside Acceptance = 0
  Not Reconstructed = 1
  Charged Long = 2
  Charged Downstream = 3
  Neutral = 50
  
  Only consider the charged final state particles. Thus if we can find two good muons in one event we have found a Jpsi.
  */
  Int_t isLong = (Reco=="Reconstructed" ? 1 : 2);
  Int_t isDown = (Reco=="Reconstructed" ? 2 : 3);

  // ***** Load NTuples ***** //
  //////////////////////////////

  TChain* chain_Bd = new TChain("chain_Bd");
  chain_Bd->Add("/castor/cern.ch/user/p/pkoppenb/B2JpsiKs/B2JpsiKs-MC11a-Bd2JpsiKs-727.root/MCTupleBd/MCDecayTree");
  
  TChain* chain_Bs = new TChain("chain_Bs");
  chain_Bs->Add("/castor/cern.ch/user/p/pkoppenb/B2JpsiKs/B2JpsiKs-MC11a-Bs2JpsiKs-750-751.root/MCTupleBs/MCDecayTree");
  
  Long64_t nEntries_Bd = chain_Bd->GetEntries();
  Long64_t nEntries_Bs = chain_Bs->GetEntries();
  //nEntries_Bd = 50000;
  //nEntries_Bs = 50000;
  
  // ***** Define DataSet Observables ***** //
  ////////////////////////////////////////////

  // *** Define Observables ***
  Int_t muplus_Reco = -999;
  Int_t muminus_Reco = -999;
  Int_t piplus_Reco = -999;
  Int_t piminus_Reco = -999;
  
  // Search for origin of difference
  Double_t TRUEP_Z = -999;
  
  // *** Set Branch Addresses: Bd->JpsiKs ***
  if(Reco=="Reconstructed"){
    chain_Bd->SetBranchAddress("muplus_Reconstructed", &muplus_Reco);
    chain_Bd->SetBranchAddress("muminus_Reconstructed", &muminus_Reco);
    chain_Bd->SetBranchAddress("piplus_Reconstructed", &piplus_Reco);
    chain_Bd->SetBranchAddress("piminus_Reconstructed", &piminus_Reco);
  }
  else if(Reco=="Reconstructible"){
    chain_Bd->SetBranchAddress("muplus_Reconstructible", &muplus_Reco);
    chain_Bd->SetBranchAddress("muminus_Reconstructible", &muminus_Reco);
    chain_Bd->SetBranchAddress("piplus_Reconstructible", &piplus_Reco);
    chain_Bd->SetBranchAddress("piminus_Reconstructible", &piminus_Reco);
  }
  chain_Bd->SetBranchAddress("B0_TRUEP_Z", &TRUEP_Z);

  // *** Set Branch Addresses: Bs->JpsiKs ***
  if(Reco=="Reconstructed"){
    chain_Bs->SetBranchAddress("muplus_Reconstructed", &muplus_Reco);
    chain_Bs->SetBranchAddress("muminus_Reconstructed", &muminus_Reco);
    chain_Bs->SetBranchAddress("piplus_Reconstructed", &piplus_Reco);
    chain_Bs->SetBranchAddress("piminus_Reconstructed", &piminus_Reco);
  }
  else if(Reco=="Reconstructible"){
    chain_Bs->SetBranchAddress("muplus_Reconstructible", &muplus_Reco);
    chain_Bs->SetBranchAddress("muminus_Reconstructible", &muminus_Reco);
    chain_Bs->SetBranchAddress("piplus_Reconstructible", &piplus_Reco);
    chain_Bs->SetBranchAddress("piminus_Reconstructible", &piminus_Reco);
  }
  chain_Bs->SetBranchAddress("B_s0_TRUEP_Z", &TRUEP_Z);
  
  // ***** Loop over Entries ***** //
  ///////////////////////////////////
  
  // *** Booleans ***
  bool Pass = true;
  
  // *** Counters ***
  Long64_t total_Bd = 0;
  Long64_t muplus_Bd = 0;
  Long64_t muminus_Bd = 0;
  Long64_t piplus_LL_Bd = 0;
  Long64_t piminus_LL_Bd = 0;
  Long64_t piplus_DD_Bd = 0;
  Long64_t piminus_DD_Bd = 0;
  Long64_t Jpsi_Bd = 0;
  Long64_t KS0_LL_Bd = 0;
  Long64_t KS0_LD_Bd = 0;
  Long64_t KS0_DD_Bd = 0;
  Long64_t B_LL_Bd = 0;
  Long64_t B_DD_Bd = 0;
  
  Long64_t total_Bs = 0;
  Long64_t muplus_Bs = 0;
  Long64_t muminus_Bs = 0;
  Long64_t piplus_LL_Bs = 0;
  Long64_t piminus_LL_Bs = 0;
  Long64_t piplus_DD_Bs = 0;
  Long64_t piminus_DD_Bs = 0;
  Long64_t Jpsi_Bs = 0;
  Long64_t KS0_LL_Bs = 0;
  Long64_t KS0_LD_Bs = 0;
  Long64_t KS0_DD_Bs = 0;
  Long64_t B_LL_Bs = 0;
  Long64_t B_DD_Bs = 0;
  
  std::cout << std::endl;
  std::cout << "== Loop over Entries: Bd->JpsiKs ==" << std::endl;
  std::cout << "===================================" << std::endl;
  
  for(Long64_t i=0; i<nEntries_Bd; i++){
    chain_Bd->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_Bd << " (" << 100*i/nEntries_Bd << "%)" << std::endl;
    
    if(SelCuts){
      if(TRUEP_Z>15000) Pass = true;
      else Pass = false;
    }
    else Pass = true;
    
    if(Pass){
      total_Bd++;
      
      // Individual Particles
      if(muplus_Reco==isLong) muplus_Bd++;
      if(muminus_Reco==isLong) muminus_Bd++;
      if(piplus_Reco==isLong) piplus_LL_Bd++;
      if(piminus_Reco==isLong) piminus_LL_Bd++;
      if(piplus_Reco==isDown) piplus_DD_Bd++;
      if(piminus_Reco==isDown) piminus_DD_Bd++;
    
      // Daughters
      if(muplus_Reco==isLong && muminus_Reco==isLong) Jpsi_Bd++;
      if(piplus_Reco==isLong && piminus_Reco==isLong) KS0_LL_Bd++;
      if((piplus_Reco==isLong && piminus_Reco==isDown) || (piplus_Reco==isDown && piminus_Reco==isLong)) KS0_LD_Bd++;
      if(piplus_Reco==isDown && piminus_Reco==isDown) KS0_DD_Bd++;
    
      // B Decay
      if(muplus_Reco==isLong && muminus_Reco==isLong && piplus_Reco==isLong && piminus_Reco==isLong) B_LL_Bd++;
      if(muplus_Reco==isLong && muminus_Reco==isLong && piplus_Reco==isDown && piminus_Reco==isDown) B_DD_Bd++;
    }
  }
  
  std::cout << std::endl;
  std::cout << "== Loop over Entries: Bs->JpsiKs ==" << std::endl;
  std::cout << "===================================" << std::endl;
  
  for(Long64_t i=0; i<nEntries_Bs; i++){
    chain_Bs->GetEntry(i);
    
    // Progress
    if(0==i%25000) std::cout << " |-> " << i << "/" << nEntries_Bs << " (" << 100*i/nEntries_Bs << "%)" << std::endl;
    
    //if(TRUEP_Z>15000) Pass = true;
    //else Pass = false;
    
    if(Pass){
      total_Bs++;
      
      // Individual Particles
      if(muplus_Reco==isLong) muplus_Bs++;
      if(muminus_Reco==isLong) muminus_Bs++;
      if(piplus_Reco==isLong) piplus_LL_Bs++;
      if(piminus_Reco==isLong) piminus_LL_Bs++;
      if(piplus_Reco==isDown) piplus_DD_Bs++;
      if(piminus_Reco==isDown) piminus_DD_Bs++;
    
      // Daughters
      if(muplus_Reco==isLong && muminus_Reco==isLong) Jpsi_Bs++;
      if(piplus_Reco==isLong && piminus_Reco==isLong) KS0_LL_Bs++;
      if((piplus_Reco==isLong && piminus_Reco==isDown) || (piplus_Reco==isDown && piminus_Reco==isLong)) KS0_LD_Bs++;
      if(piplus_Reco==isDown && piminus_Reco==isDown) KS0_DD_Bs++;
    
      // B Decay
      if(muplus_Reco==isLong && muminus_Reco==isLong && piplus_Reco==isLong && piminus_Reco==isLong) B_LL_Bs++;
      if(muplus_Reco==isLong && muminus_Reco==isLong && piplus_Reco==isDown && piminus_Reco==isDown) B_DD_Bs++;
    }
  }
  
  // ***** Results ***** //
  /////////////////////////
  
  double muplus_Eff_Val_Bd = (double) muplus_Bd/total_Bd;
  double muplus_Eff_Err_Bd = (double) TMath::Sqrt((pow(muplus_Bd,2.) + muplus_Bd * total_Bd)/pow(total_Bd,3.));
  double muminus_Eff_Val_Bd = (double) muminus_Bd/total_Bd;
  double muminus_Eff_Err_Bd = (double) TMath::Sqrt((pow(muminus_Bd,2.) + muminus_Bd * total_Bd)/pow(total_Bd,3.));
  double piplus_LL_Eff_Val_Bd = (double) piplus_LL_Bd/total_Bd;
  double piplus_LL_Eff_Err_Bd = (double) TMath::Sqrt((pow(piplus_LL_Bd,2.) + piplus_LL_Bd * total_Bd)/pow(total_Bd,3.));
  double piminus_LL_Eff_Val_Bd = (double) piminus_LL_Bd/total_Bd;
  double piminus_LL_Eff_Err_Bd = (double) TMath::Sqrt((pow(piminus_LL_Bd,2.) + piminus_LL_Bd * total_Bd)/pow(total_Bd,3.));
  double piplus_DD_Eff_Val_Bd = (double) piplus_DD_Bd/total_Bd;
  double piplus_DD_Eff_Err_Bd = (double) TMath::Sqrt((pow(piplus_DD_Bd,2.) + piplus_DD_Bd * total_Bd)/pow(total_Bd,3.));
  double piminus_DD_Eff_Val_Bd = (double) piminus_DD_Bd/total_Bd;
  double piminus_DD_Eff_Err_Bd = (double) TMath::Sqrt((pow(piminus_DD_Bd,2.) + piminus_DD_Bd * total_Bd)/pow(total_Bd,3.));
  double Jpsi_Eff_Val_Bd = (double) Jpsi_Bd/total_Bd;
  double Jpsi_Eff_Err_Bd = (double) TMath::Sqrt((pow(Jpsi_Bd,2.) + Jpsi_Bd * total_Bd)/pow(total_Bd,3.));
  double KS0_LL_Eff_Val_Bd = (double) KS0_LL_Bd/total_Bd;
  double KS0_LL_Eff_Err_Bd = (double) TMath::Sqrt((pow(KS0_LL_Bd,2.) + KS0_LL_Bd * total_Bd)/pow(total_Bd,3.));
  double KS0_LD_Eff_Val_Bd = (double) KS0_LD_Bd/total_Bd;
  double KS0_LD_Eff_Err_Bd = (double) TMath::Sqrt((pow(KS0_LD_Bd,2.) + KS0_LD_Bd * total_Bd)/pow(total_Bd,3.));
  double KS0_DD_Eff_Val_Bd = (double) KS0_DD_Bd/total_Bd;
  double KS0_DD_Eff_Err_Bd = (double) TMath::Sqrt((pow(KS0_DD_Bd,2.) + KS0_DD_Bd * total_Bd)/pow(total_Bd,3.));
  double B_LL_Eff_Val_Bd = (double) B_LL_Bd/total_Bd;
  double B_LL_Eff_Err_Bd = (double) TMath::Sqrt((pow(B_LL_Bd,2.) + B_LL_Bd * total_Bd)/pow(total_Bd,3.));
  double B_DD_Eff_Val_Bd = (double) B_DD_Bd/total_Bd;
  double B_DD_Eff_Err_Bd = (double) TMath::Sqrt((pow(B_DD_Bd,2.) + B_DD_Bd * total_Bd)/pow(total_Bd,3.));
  
  double muplus_Eff_Val_Bs = (double) muplus_Bs/total_Bs;
  double muplus_Eff_Err_Bs = (double) TMath::Sqrt((pow(muplus_Bs,2.) + muplus_Bs * total_Bs)/pow(total_Bs,3.));
  double muminus_Eff_Val_Bs = (double) muminus_Bs/total_Bs;
  double muminus_Eff_Err_Bs = (double) TMath::Sqrt((pow(muminus_Bs,2.) + muminus_Bs * total_Bs)/pow(total_Bs,3.));
  double piplus_LL_Eff_Val_Bs = (double) piplus_LL_Bs/total_Bs;
  double piplus_LL_Eff_Err_Bs = (double) TMath::Sqrt((pow(piplus_LL_Bs,2.) + piplus_LL_Bs * total_Bs)/pow(total_Bs,3.));
  double piminus_LL_Eff_Val_Bs = (double) piminus_LL_Bs/total_Bs;
  double piminus_LL_Eff_Err_Bs = (double) TMath::Sqrt((pow(piminus_LL_Bs,2.) + piminus_LL_Bs * total_Bs)/pow(total_Bs,3.));
  double piplus_DD_Eff_Val_Bs = (double) piplus_DD_Bs/total_Bs;
  double piplus_DD_Eff_Err_Bs = (double) TMath::Sqrt((pow(piplus_DD_Bs,2.) + piplus_DD_Bs * total_Bs)/pow(total_Bs,3.));
  double piminus_DD_Eff_Val_Bs = (double) piminus_DD_Bs/total_Bs;
  double piminus_DD_Eff_Err_Bs = (double) TMath::Sqrt((pow(piminus_DD_Bs,2.) + piminus_DD_Bs * total_Bs)/pow(total_Bs,3.));
  double Jpsi_Eff_Val_Bs = (double) Jpsi_Bs/total_Bs;
  double Jpsi_Eff_Err_Bs = (double) TMath::Sqrt((pow(Jpsi_Bs,2.) + Jpsi_Bs * total_Bs)/pow(total_Bs,3.));
  double KS0_LL_Eff_Val_Bs = (double) KS0_LL_Bs/total_Bs;
  double KS0_LL_Eff_Err_Bs = (double) TMath::Sqrt((pow(KS0_LL_Bs,2.) + KS0_LL_Bs * total_Bs)/pow(total_Bs,3.));
  double KS0_LD_Eff_Val_Bs = (double) KS0_LD_Bs/total_Bs;
  double KS0_LD_Eff_Err_Bs = (double) TMath::Sqrt((pow(KS0_LD_Bs,2.) + KS0_LD_Bs * total_Bs)/pow(total_Bs,3.));
  double KS0_DD_Eff_Val_Bs = (double) KS0_DD_Bs/total_Bs;
  double KS0_DD_Eff_Err_Bs = (double) TMath::Sqrt((pow(KS0_DD_Bs,2.) + KS0_DD_Bs * total_Bs)/pow(total_Bs,3.));
  double B_LL_Eff_Val_Bs = (double) B_LL_Bs/total_Bs;
  double B_LL_Eff_Err_Bs = (double) TMath::Sqrt((pow(B_LL_Bs,2.) + B_LL_Bs * total_Bs)/pow(total_Bs,3.));
  double B_DD_Eff_Val_Bs = (double) B_DD_Bs/total_Bs;
  double B_DD_Eff_Err_Bs = (double) TMath::Sqrt((pow(B_DD_Bs,2.) + B_DD_Bs * total_Bs)/pow(total_Bs,3.));
  
  double muplus_Eff_Diff_Val = muplus_Eff_Val_Bd - muplus_Eff_Val_Bs;
  double muplus_Eff_Diff_Err = TMath::Sqrt(pow(muplus_Eff_Err_Bd,2) + pow(muplus_Eff_Err_Bs,2));
  double muminus_Eff_Diff_Val = muminus_Eff_Val_Bd - muminus_Eff_Val_Bs;
  double muminus_Eff_Diff_Err = TMath::Sqrt(pow(muminus_Eff_Err_Bd,2) + pow(muminus_Eff_Err_Bs,2));
  double piplus_LL_Eff_Diff_Val = piplus_LL_Eff_Val_Bd - piplus_LL_Eff_Val_Bs;
  double piplus_LL_Eff_Diff_Err = TMath::Sqrt(pow(piplus_LL_Eff_Err_Bd,2) + pow(piplus_LL_Eff_Err_Bs,2));
  double piminus_LL_Eff_Diff_Val = piminus_LL_Eff_Val_Bd - piminus_LL_Eff_Val_Bs;
  double piminus_LL_Eff_Diff_Err = TMath::Sqrt(pow(piminus_LL_Eff_Err_Bd,2) + pow(piminus_LL_Eff_Err_Bs,2));
  double piplus_DD_Eff_Diff_Val = piplus_DD_Eff_Val_Bd - piplus_DD_Eff_Val_Bs;
  double piplus_DD_Eff_Diff_Err = TMath::Sqrt(pow(piplus_DD_Eff_Err_Bd,2) + pow(piplus_DD_Eff_Err_Bs,2));
  double piminus_DD_Eff_Diff_Val = piminus_DD_Eff_Val_Bd - piminus_DD_Eff_Val_Bs;
  double piminus_DD_Eff_Diff_Err = TMath::Sqrt(pow(piminus_DD_Eff_Err_Bd,2) + pow(piminus_DD_Eff_Err_Bs,2));
  double Jpsi_Eff_Diff_Val = Jpsi_Eff_Val_Bd - Jpsi_Eff_Val_Bs;
  double Jpsi_Eff_Diff_Err = TMath::Sqrt(pow(Jpsi_Eff_Err_Bd,2) + pow(Jpsi_Eff_Err_Bs,2));
  double KS0_LL_Eff_Diff_Val = KS0_LL_Eff_Val_Bd - KS0_LL_Eff_Val_Bs;
  double KS0_LL_Eff_Diff_Err = TMath::Sqrt(pow(KS0_LL_Eff_Err_Bd,2) + pow(KS0_LL_Eff_Err_Bs,2));
  double KS0_LD_Eff_Diff_Val = KS0_LD_Eff_Val_Bd - KS0_LD_Eff_Val_Bs;
  double KS0_LD_Eff_Diff_Err = TMath::Sqrt(pow(KS0_LD_Eff_Err_Bd,2) + pow(KS0_LD_Eff_Err_Bs,2));
  double KS0_DD_Eff_Diff_Val = KS0_DD_Eff_Val_Bd - KS0_DD_Eff_Val_Bs;
  double KS0_DD_Eff_Diff_Err = TMath::Sqrt(pow(KS0_DD_Eff_Err_Bd,2) + pow(KS0_DD_Eff_Err_Bs,2));
  double B_LL_Eff_Diff_Val = B_LL_Eff_Val_Bd - B_LL_Eff_Val_Bs;
  double B_LL_Eff_Diff_Err = TMath::Sqrt(pow(B_LL_Eff_Err_Bd,2) + pow(B_LL_Eff_Err_Bs,2));
  double B_DD_Eff_Diff_Val = B_DD_Eff_Val_Bd - B_DD_Eff_Val_Bs;
  double B_DD_Eff_Diff_Err = TMath::Sqrt(pow(B_DD_Eff_Err_Bd,2) + pow(B_DD_Eff_Err_Bs,2));

  
  std::cout << std::endl;
  std::cout << "== SigBd Reconstruction Efficiencies ==" << std::endl;
  std::cout << "=======================================" << std::endl;
  std::cout << Reco << " Mu plus : " << muplus_Bd << "/" << total_Bd << " = " << muplus_Eff_Val_Bd << " +/- " << muplus_Eff_Err_Bd << std::endl;
  std::cout << Reco << " Mu minus: " << muminus_Bd << "/" << total_Bd << " = " << muminus_Eff_Val_Bd << " +/- " << muminus_Eff_Err_Bd << std::endl;
  std::cout << Reco << " Pi plus  (LL): " << piplus_LL_Bd << "/" << total_Bd << " = " << piplus_LL_Eff_Val_Bd << " +/- " << piplus_LL_Eff_Err_Bd << std::endl;
  std::cout << Reco << " Pi minus (LL): " << piminus_LL_Bd << "/" << total_Bd << " = " << piminus_LL_Eff_Val_Bd << " +/- " << piminus_LL_Eff_Err_Bd << std::endl;
  std::cout << Reco << " Pi plus  (DD): " << piplus_DD_Bd << "/" << total_Bd << " = " << piplus_DD_Eff_Val_Bd << " +/- " << piplus_DD_Eff_Err_Bd << std::endl;
  std::cout << Reco << " Pi minus (DD): " << piminus_DD_Bd << "/" << total_Bd << " = " << piminus_DD_Eff_Val_Bd << " +/- " << piminus_DD_Eff_Err_Bd << std::endl;
  std::cout << std::endl;
  std::cout << Reco << " Jpsi: " << Jpsi_Bd << "/" << total_Bd << " = " << Jpsi_Eff_Val_Bd << " +/- " << Jpsi_Eff_Err_Bd << std::endl;
  std::cout << Reco << " KS0 (LL): " << KS0_LL_Bd << "/" << total_Bd << " = " << KS0_LL_Eff_Val_Bd << " +/- " << KS0_LL_Eff_Err_Bd << std::endl;
  std::cout << Reco << " KS0 (LD): " << KS0_LD_Bd << "/" << total_Bd << " = " << KS0_LD_Eff_Val_Bd << " +/- " << KS0_LD_Eff_Err_Bd << std::endl;
  std::cout << Reco << " KS0 (DD): " << KS0_DD_Bd << "/" << total_Bd << " = " << KS0_DD_Eff_Val_Bd << " +/- " << KS0_DD_Eff_Err_Bd << std::endl;
  std::cout << std::endl;
  std::cout << Reco << " B (LL): " << B_LL_Bd << "/" << total_Bd << " = " << B_LL_Eff_Val_Bd << " +/- " << B_LL_Eff_Err_Bd << std::endl;
  std::cout << Reco << " B (DD): " << B_DD_Bd << "/" << total_Bd << " = " << B_DD_Eff_Val_Bd << " +/- " << B_DD_Eff_Err_Bd << std::endl;
  
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "== SigBs Reconstruction Efficiencies ==" << std::endl;
  std::cout << "=======================================" << std::endl;
  std::cout << Reco << " Mu plus : " << muplus_Bs << "/" << total_Bs << " = " << muplus_Eff_Val_Bs << " +/- " << muplus_Eff_Err_Bs << std::endl;
  std::cout << Reco << " Mu minus: " << muminus_Bs << "/" << total_Bs << " = " << muminus_Eff_Val_Bs << " +/- " << muminus_Eff_Err_Bs << std::endl;
  std::cout << Reco << " Pi plus  (LL): " << piplus_LL_Bs << "/" << total_Bs << " = " << piplus_LL_Eff_Val_Bs << " +/- " << piplus_LL_Eff_Err_Bs << std::endl;
  std::cout << Reco << " Pi minus (LL): " << piminus_LL_Bs << "/" << total_Bs << " = " << piminus_LL_Eff_Val_Bs << " +/- " << piminus_LL_Eff_Err_Bs << std::endl;
  std::cout << Reco << " Pi plus  (DD): " << piplus_DD_Bs << "/" << total_Bs << " = " << piplus_DD_Eff_Val_Bs << " +/- " << piplus_DD_Eff_Err_Bs << std::endl;
  std::cout << Reco << " Pi minus (DD): " << piminus_DD_Bs << "/" << total_Bs << " = " << piminus_DD_Eff_Val_Bs << " +/- " << piminus_DD_Eff_Err_Bs << std::endl;
  std::cout << std::endl;
  std::cout << Reco << " Jpsi: " << Jpsi_Bs << "/" << total_Bs << " = " << Jpsi_Eff_Val_Bs << " +/- " << Jpsi_Eff_Err_Bs << std::endl;
  std::cout << Reco << " KS0 (LL): " << KS0_LL_Bs << "/" << total_Bs << " = " << KS0_LL_Eff_Val_Bs << " +/- " << KS0_LL_Eff_Err_Bs << std::endl;
  std::cout << Reco << " KS0 (LD): " << KS0_LD_Bs << "/" << total_Bs << " = " << KS0_LD_Eff_Val_Bs << " +/- " << KS0_LD_Eff_Err_Bs << std::endl;
  std::cout << Reco << " KS0 (DD): " << KS0_DD_Bs << "/" << total_Bs << " = " << KS0_DD_Eff_Val_Bs << " +/- " << KS0_DD_Eff_Err_Bs << std::endl;
  std::cout << std::endl;
  std::cout << Reco << " B (LL): " << B_LL_Bs << "/" << total_Bs << " = " << B_LL_Eff_Val_Bs << " +/- " << B_LL_Eff_Err_Bs << std::endl;
  std::cout << Reco << " B (DD): " << B_DD_Bs << "/" << total_Bs << " = " << B_DD_Eff_Val_Bs << " +/- " << B_DD_Eff_Err_Bs << std::endl;
  
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "== Difference ==" << std::endl;
  std::cout << "================" << std::endl;
  std::cout << Reco << " Mu plus : " << muplus_Eff_Diff_Val << " +/- " << muplus_Eff_Diff_Err << " => Sig: " << muplus_Eff_Diff_Val/muplus_Eff_Diff_Err << std::endl;
  std::cout << Reco << " Mu minus: " << muminus_Eff_Diff_Val << " +/- " << muminus_Eff_Diff_Err << " => Sig: " << muminus_Eff_Diff_Val/muminus_Eff_Diff_Err << std::endl;
  std::cout << Reco << " Pi plus  (LL): " << piplus_LL_Eff_Diff_Val << " +/- " << piplus_LL_Eff_Diff_Err << " => Sig: " << piplus_LL_Eff_Diff_Val/piplus_LL_Eff_Diff_Err << std::endl;
  std::cout << Reco << " Pi minus (LL): " << piminus_LL_Eff_Diff_Val << " +/- " << piminus_LL_Eff_Diff_Err << " => Sig: " << piminus_LL_Eff_Diff_Val/piminus_LL_Eff_Diff_Err << std::endl;
  std::cout << Reco << " Pi plus  (DD): " << piplus_DD_Eff_Diff_Val << " +/- " << piplus_DD_Eff_Diff_Err << " => Sig: " << piplus_DD_Eff_Diff_Val/piplus_DD_Eff_Diff_Err << std::endl;
  std::cout << Reco << " Pi minus (DD): " << piminus_DD_Eff_Diff_Val << " +/- " << piminus_DD_Eff_Diff_Err << " => Sig: " << piminus_DD_Eff_Diff_Val/piminus_DD_Eff_Diff_Err << std::endl;
  std::cout << std::endl;
  std::cout << Reco << " Jpsi: " << Jpsi_Eff_Diff_Val << " +/- " << Jpsi_Eff_Diff_Err << " => Sig: " << Jpsi_Eff_Diff_Val/Jpsi_Eff_Diff_Err << std::endl;
  std::cout << Reco << " KS0 (LL): " << KS0_LL_Eff_Diff_Val << " +/- " << KS0_LL_Eff_Diff_Err << " => Sig: " << KS0_LL_Eff_Diff_Val/KS0_LL_Eff_Diff_Err << std::endl;
  std::cout << Reco << " KS0 (LD): " << KS0_LD_Eff_Diff_Val << " +/- " << KS0_LD_Eff_Diff_Err << " => Sig: " << KS0_LD_Eff_Diff_Val/KS0_LD_Eff_Diff_Err << std::endl;
  std::cout << Reco << " KS0 (DD): " << KS0_DD_Eff_Diff_Val << " +/- " << KS0_DD_Eff_Diff_Err << " => Sig: " << KS0_DD_Eff_Diff_Val/KS0_DD_Eff_Diff_Err << std::endl;
  std::cout << std::endl;
  std::cout << Reco << " B (LL): " << B_LL_Eff_Diff_Val << " +/- " << B_LL_Eff_Diff_Err << " => Sig: " << B_LL_Eff_Diff_Val/B_LL_Eff_Diff_Err << std::endl;
  std::cout << Reco << " B (DD): " << B_DD_Eff_Diff_Val << " +/- " << B_DD_Eff_Diff_Err << " => Sig: " << B_DD_Eff_Diff_Val/B_DD_Eff_Diff_Err << std::endl;
  
  
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "== Table ==" << std::endl;
  std::cout << "===========" << std::endl;
  std::cout << "Particle & Bd sample & Bs sample & Difference & Significance" << std::endl;
  printf("mup & %.5f ! %.5f & %.5f ! %.5f & %.5f ! %.5f & $%.1fsigma$ \n",muplus_Eff_Val_Bd,muplus_Eff_Err_Bd,muplus_Eff_Val_Bs,muplus_Eff_Err_Bs,muplus_Eff_Diff_Val,muplus_Eff_Diff_Err,muplus_Eff_Diff_Val/muplus_Eff_Diff_Err);
  printf("mun & %.5f ! %.5f & %.5f ! %.5f & %.5f ! %.5f & $%.1fsigma$ \n",muminus_Eff_Val_Bd,muminus_Eff_Err_Bd,muminus_Eff_Val_Bs,muminus_Eff_Err_Bs,muminus_Eff_Diff_Val,muminus_Eff_Diff_Err,muminus_Eff_Diff_Val/muminus_Eff_Diff_Err);
  printf("pip (L) & %.5f ! %.5f & %.5f ! %.5f & %.5f ! %.5f & $%.1fsigma$ \n",piplus_LL_Eff_Val_Bd,piplus_LL_Eff_Err_Bd,piplus_LL_Eff_Val_Bs,piplus_LL_Eff_Err_Bs,piplus_LL_Eff_Diff_Val,piplus_LL_Eff_Diff_Err,piplus_LL_Eff_Diff_Val/piplus_LL_Eff_Diff_Err);
  printf("pim (L) & %.5f ! %.5f & %.5f ! %.5f & %.5f ! %.5f & $%.1fsigma$ \n",piminus_LL_Eff_Val_Bd,piminus_LL_Eff_Err_Bd,piminus_LL_Eff_Val_Bs,piminus_LL_Eff_Err_Bs,piminus_LL_Eff_Diff_Val,piminus_LL_Eff_Diff_Err,piminus_LL_Eff_Diff_Val/piminus_LL_Eff_Diff_Err);
  printf("pip (D) & %.5f ! %.5f & %.5f ! %.5f & %.5f ! %.5f & $%.1fsigma$ \n",piplus_DD_Eff_Val_Bd,piplus_DD_Eff_Err_Bd,piplus_DD_Eff_Val_Bs,piplus_DD_Eff_Err_Bs,piplus_DD_Eff_Diff_Val,piplus_DD_Eff_Diff_Err,piplus_DD_Eff_Diff_Val/piplus_DD_Eff_Diff_Err);
  printf("pim (D) & %.5f ! %.5f & %.5f ! %.5f & %.5f ! %.5f & $%.1fsigma$ \n",piminus_DD_Eff_Val_Bd,piminus_DD_Eff_Err_Bd,piminus_DD_Eff_Val_Bs,piminus_DD_Eff_Err_Bs,piminus_DD_Eff_Diff_Val,piminus_DD_Eff_Diff_Err,piminus_DD_Eff_Diff_Val/piminus_DD_Eff_Diff_Err);
  printf("jpsi & %.5f ! %.5f & %.5f ! %.5f & %.5f ! %.5f & $%.1fsigma$ \n",Jpsi_Eff_Val_Bd,Jpsi_Eff_Err_Bd,Jpsi_Eff_Val_Bs,Jpsi_Eff_Err_Bs,Jpsi_Eff_Diff_Val,Jpsi_Eff_Diff_Err,Jpsi_Eff_Diff_Val/Jpsi_Eff_Diff_Err);
  printf("KS (LL) & %.5f ! %.5f & %.5f ! %.5f & %.5f ! %.5f & $%.1fsigma$ \n",KS0_LL_Eff_Val_Bd,KS0_LL_Eff_Err_Bd,KS0_LL_Eff_Val_Bs,KS0_LL_Eff_Err_Bs,KS0_LL_Eff_Diff_Val,KS0_LL_Eff_Diff_Err,KS0_LL_Eff_Diff_Val/KS0_LL_Eff_Diff_Err);
  printf("KS (LD) & %.5f ! %.5f & %.5f ! %.5f & %.5f ! %.5f & $%.1fsigma$ \n",KS0_LD_Eff_Val_Bd,KS0_LD_Eff_Err_Bd,KS0_LD_Eff_Val_Bs,KS0_LD_Eff_Err_Bs,KS0_LD_Eff_Diff_Val,KS0_LD_Eff_Diff_Err,KS0_LD_Eff_Diff_Val/KS0_LD_Eff_Diff_Err);
  printf("KS (DD) & %.5f ! %.5f & %.5f ! %.5f & %.5f ! %.5f & $%.1fsigma$ \n",KS0_DD_Eff_Val_Bd,KS0_DD_Eff_Err_Bd,KS0_DD_Eff_Val_Bs,KS0_DD_Eff_Err_Bs,KS0_DD_Eff_Diff_Val,KS0_DD_Eff_Diff_Err,KS0_DD_Eff_Diff_Val/KS0_DD_Eff_Diff_Err);
  printf("Bd (LL) & %.5f ! %.5f & %.5f ! %.5f & %.5f ! %.5f & $%.1fsigma$ \n",B_LL_Eff_Val_Bd,B_LL_Eff_Err_Bd,B_LL_Eff_Val_Bs,B_LL_Eff_Err_Bs,B_LL_Eff_Diff_Val,B_LL_Eff_Diff_Err,B_LL_Eff_Diff_Val/B_LL_Eff_Diff_Err);
  printf("Bd (DD) & %.5f ! %.5f & %.5f ! %.5f & %.5f ! %.5f & $%.1fsigma$ \n",B_DD_Eff_Val_Bd,B_DD_Eff_Err_Bd,B_DD_Eff_Val_Bs,B_DD_Eff_Err_Bs,B_DD_Eff_Diff_Val,B_DD_Eff_Diff_Err,B_DD_Eff_Diff_Val/B_DD_Eff_Diff_Err);
  
  std::cout << std::endl;
  std::cout << Reco << " B (LL+DD) " << B_LL_Eff_Val_Bd + B_DD_Eff_Val_Bd << " +/- " << TMath::Sqrt(pow(B_LL_Eff_Err_Bd,2)+pow(B_DD_Eff_Err_Bd,2)) << " versus " << B_LL_Eff_Val_Bs + B_DD_Eff_Val_Bs << " +/- " << TMath::Sqrt(pow(B_LL_Eff_Err_Bs,2)+pow(B_DD_Eff_Err_Bs,2)) << " giving relative difference of " << ((B_LL_Eff_Val_Bd + B_DD_Eff_Val_Bd) - (B_LL_Eff_Val_Bs + B_DD_Eff_Val_Bs))/TMath::Min(B_LL_Eff_Val_Bd + B_DD_Eff_Val_Bd,B_LL_Eff_Val_Bs + B_DD_Eff_Val_Bs) << " +/ - " << TMath::Sqrt(pow(TMath::Sqrt(pow(B_LL_Eff_Err_Bd,2)+pow(B_DD_Eff_Err_Bd,2))/(B_LL_Eff_Val_Bs + B_DD_Eff_Val_Bs),2) + pow(TMath::Sqrt(pow(B_LL_Eff_Err_Bs,2)+pow(B_DD_Eff_Err_Bs,2)) * (B_LL_Eff_Val_Bd + B_DD_Eff_Val_Bd)/pow(B_LL_Eff_Val_Bs + B_DD_Eff_Val_Bs,2),2)) << std::endl;
  
}
