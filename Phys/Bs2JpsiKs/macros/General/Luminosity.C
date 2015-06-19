////////////////////////////////////////
// ***** Bs2JpsiKs - Luminosity ***** //
////////////////////////////////////////

// This is the ROOT Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb
// - Get integrated luminosity of the data sample

/////////////////////////////////////
// ***** Load useful classes ***** //
/////////////////////////////////////

#include "RooRealVar.h"

#include "TChain.h"
#include "TFile.h"

using namespace RooFit;

///////////////////////////////
// ***** Main Function ***** //
///////////////////////////////
void Luminosity(){

  std::cout << " " << std::endl;
  std::cout << "== Calculating Integrated Luminosity ==" << std::endl;
  std::cout << "=======================================" << std::endl;

  // ***** Load NTuples ***** //
  //////////////////////////////

  TChain* chain = new TChain("chain");
  // LHCb2011
  chain->Add("/castor/cern.ch/user/p/pkoppenb/B2JpsiKs/B2JpsiKs-R12S17b-726-732.root/GetIntegratedLuminosity/LumiTuple");
	
  Int_t nEntries_DaVinci = chain->GetEntries();
  std::cout << "Number of entries from DaVinci: " << nEntries_DaVinci << std::endl;	

  // ***** Define DataSet Observables ***** //
  ////////////////////////////////////////////

  // *** Define Observables & Selection Variables ***
  Double_t IntegratedLuminosity = -999;
	Double_t IntegratedLuminosityErr = -999;

  // *** Set Branch Addresses ***
  chain->SetBranchAddress("IntegratedLuminosity", &IntegratedLuminosity);
  chain->SetBranchAddress("IntegratedLuminosityErr", &IntegratedLuminosityErr);


  // *** Observable ***
	Double_t TotIntegratedLuminosity = 0;
	Double_t TotIntegratedLuminosityErr = 0;


  // ***** Loop over Entries: ***** //
  ////////////////////////////////////

  std::cout << " " << std::endl;
  std::cout << "== Loop ==" << std::endl;
  std::cout << "==========" << std::endl;


  for(Int_t i=0; i<nEntries_DaVinci; i++){
    chain->GetEntry(i);
		
    // Debug
    //if(i<3) std::cout << "Entry " << i << " has luminosity: " << IntegratedLuminosity << " +/- " << IntegratedLuminosityErr << std::endl;
    
		TotIntegratedLuminosity += IntegratedLuminosity;
		TotIntegratedLuminosityErr += IntegratedLuminosityErr;
	
  }
		
  std::cout << "Total Integrated Luminosity: " << TotIntegratedLuminosity << " +/- " << TotIntegratedLuminosityErr << std::endl;

  // RESULTS
  // Total Integrated Luminosity: 1017.79 +/- 35.6228
}