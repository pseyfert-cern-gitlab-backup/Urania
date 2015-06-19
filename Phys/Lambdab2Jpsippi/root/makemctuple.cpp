// ####################################################################################################
// Add variables to MC tuple that are hard to calculate in root
// Authors: Patrick Koppenburg
// ####################################################################################################

// ####################################################################################################
// *** Load Useful Classes **

// General C++ && Root
#include "TString.h"
#include <TVector3.h>
#include <iostream>
#include "MultipleCandidates.h"

// Lambdab2JPsippi Package
#include "MCTuple.h"

using namespace std ;


// ####################################################################################################
// *** Declarations ***
int loop(MCTuple* ntuple){

  if (!ntuple) return -1 ;
  if (!(ntuple->fChain)) {
    std::cout << "fchain is NULL" << std::endl ;
    return -2 ;
  }
  const Long64_t nentries = ntuple->fChain->GetEntries();
  double frac = printFrac(nentries);  
  TFile* outfile = new TFile( (ntuple->m_isPi?"MCLb2Psippi.root":"MCLb2PsipK.root"), "RECREATE" );
 
  unsigned long int runNumber, eventNumber ;
  Double_t mprime, thetaprime, pMMass2, psipMass2, psiMMass2 ;
  TTree outtree("MCTree","MC Truth Helper Tree");
  outtree.Branch("EventNumber",&eventNumber, "EventNumber/l");
  outtree.Branch("RunNumber",&runNumber, "RunNumber/i");
  outtree.Branch("mprime",&mprime,"mprime/D");
  outtree.Branch("thetaprime",&thetaprime,"thetaprime/D");
  outtree.Branch("pMMass2",&pMMass2,"pMMass2/D");
  outtree.Branch("psipMass2",&psipMass2,"psipMass2/D");
  outtree.Branch("psiMMass2",&psiMMass2,"psiMMass2/D");
  outtree.SetDirectory(outfile); 
  for (Long64_t i=0; i<nentries;i++) {
    ntuple->fChain->GetEntry(i);
    runNumber = ntuple->runNumber;
    eventNumber = ntuple->eventNumber;
    mprime = ntuple->mprime() ;
    thetaprime = ntuple->thetaprime() ;
    pMMass2 = ntuple->pMMass2() ;
    psipMass2 = ntuple->psipMass2() ;
    psiMMass2 = ntuple->psiMMass2() ;
    outtree.Fill() ;
    if(0==i%((int)(frac*nentries))) std::cout << " |-> " << i << " / " 
                                              << nentries << " (" << 100*i/nentries << "%)" 
					      << " Dalitz: " << mprime << ":" << thetaprime << std::endl; 
  }
  std::cout << "Done" << std::endl  ;
  outfile->cd();
  outtree.Write();
  outfile->Close();
 
  
  return 0;
}



// ####################################################################################################
// *** Main ***
int main(int argc, char** argv) {

  if(argc<2){
    std::cout << "ERROR: Insufficient arguments given" << std::endl;  
    std::cout << "./makemctuple.exe $CASTOR_HOME/Lambdab/LambdabMC-Lbpi-Sim08a-1122-1123-1124-1125.root" 
              << "  | tee test-makemctuple" << std::endl;  
    return -9;
  }

  // *** Decode Arguments ***
  TString fullname = TString(argv[1]);
  
  std::cout << "Configured makemctuple with file: ``" << fullname << "''" << std::endl ;
  
  MCTuple* tuple = new MCTuple(fullname);
  if (!tuple) {
    std::cout << "Tuple is " << tuple << std::endl ;
    return -1 ;
  }
  return loop(tuple);
}
