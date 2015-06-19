// ####################################################################################################
// Phys/Lambdab Package
// Neural Net Expert
// Authors: Patrick Koppenburg
// ####################################################################################################

// ####################################################################################################
// *** Load Useful Classes ***

// General C++ && Root
#include <iostream>
#include "TObject.h"
#include "TFile.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH1F.h"
#include "TString.h"

// Bs2JpsiKs Package
#include "Lambdab.h"
#include "Tuples.h"

// NeuroBayes
#include "NeuroBayesExpert.hh"

// Namespace
namespace ErrorCodes{
  enum EC{ Error = -33 ,
           FailsCuts = -9 ,
           KilledMuCa = -8 };
}


// ####################################################################################################
// *** Expert ***
int CreateExpertTree(const TString fullname){
                       
  // ***** PART 0: Initialise ***** //
  ////////////////////////////////////
  // *** Load Data ***
  Lambdab* ntuple = new Lambdab(fullname);
  if(!ntuple) return -1;
  
  unsigned int lastslash = fullname.Last('/');
  TString plotfilename = fullname(lastslash+1,fullname.Length()-lastslash-1);
  plotfilename = plotfilename.ReplaceAll(".root","-NN.root") ;
  std::cout << plotfilename << std::endl ;
  TFile* outfile = new TFile( plotfilename, "RECREATE" );
  outfile->cd();

// ***** PART I: Create Tree ***** //
/////////////////////////////////////
  
  std::cout << "\n PROGRESS: Creating Tree \n" << std::endl; 

  // Histograms  
  TH1F* h_net = new TH1F("h_net","Net Output",100,-1.0,1.0);  
  h_net->Sumw2();

  // *** Initialise ***
  Float_t netOutput = -999;
  Float_t FullFitMass = -999;
  Float_t FullFitMassErr = -999;
  Float_t DiLeptonMass = -999;

  // Tree
  TTree outtree("NetTree","Neural Net Tree");
  outtree.Branch("netOutput",&netOutput, "b_netOutput/F");
  outtree.Branch("FullFitMass",&FullFitMass, "b_FullFitMass/F");
  outtree.Branch("FullFitMassErr",&FullFitMassErr, "b_FullFitMassErr/F");
  // pi p mass calculate here and add to ntuple
  outtree.SetDirectory(outfile); 
  
  // *** NeuroBayes ***
  // Prepare Ntuple
  float* InputArray = new float[nvar]; // array to hold input data
  
  std::cout << "\n PROGRESS: Preparing NeuroBayes Expert \n" << std::endl; 
  
  // Read File
  char ExpFile[256] = "Lambdab.nb";			// N-Alex: AHA! So this is where data from the teacher comes in :D
  Expert* NeuroBayesExpert  = new Expert(ExpFile);
  std::cout << " * Expert will be using file: " << ExpFile  << std::endl ;
  
  // *** Fill Tree ***
  std::cout << "\n PROGRESS: Running NeuroBayes Expert \n" << std::endl; 
  const Long64_t nentries = ntuple->fChain->GetEntries();
  Long64_t nFailed = 0;
  Long64_t nKilled = 0;
  Long64_t nGood = 0;
  
  std::cout << " * Will loop over " << nentries << "entries" << std::endl;

  double frac = printFrac(nentries);  
  for (Long64_t i=0; i<nentries;i++) {
    ntuple->fChain->GetEntry(i);
    
    // Progress
    if(0==i%((int)(frac*nentries))) std::cout << " |-> " << i << " / " 
                                              << nentries << " (" << 100*i/nentries << "%)" << std::endl; 
  
    // Get Data
    FullFitMass = ntuple->B_FullFit_M[0] ;
    FullFitMassErr = ntuple->B_FullFit_MERR[0] ;

    if (!preselection(ntuple)){
      nFailed++;
      netOutput = ErrorCodes::FailsCuts; 
    } else {
      nGood++ ;
      // Feed Teacher
      prepareArray(nvar, InputArray, ntuple);
      netOutput = NeuroBayesExpert->nb_expert(InputArray);
    } 
    // Store Result
    h_net->Fill(netOutput);
    outtree.Fill() ;
  }
  
  // *** Results ***
  std::cout << "++++++++++++++++++++ results ++++++++++++++++++++" << std::endl ;
  std::cout << "     # events failing selection cuts: " << nFailed << std::endl;
  std::cout << "     # Multiple Candidates Killed   : " << nKilled << std::endl;
  std::cout << "     # good events                  : " << nGood << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  

  // *** Write to file ***
  std::cout << "\n PROGRESS: Writing File \n" << std::endl; 

  outfile->cd();
  outtree.Write();
  h_net->Write();
  outfile->Close();

// ***** PART II: Return ***** //
/////////////////////////////////
  std::cout << "\n PROGRESS: Finished! \n" << std::endl;
  return 0 ;
} 

// ####################################################################################################
// *** Main ***
int main(int argc, char** argv) {

   if(argc<2){
    std::cout << "ERROR: Insufficient arguments given" << std::endl;  
    std::cout << "./expert.exe /castor/cern.ch/user/p/pkoppenb/Lambdab/Lambdab2Jpsippi-MC11a-Psippi-521.root" 
              << " | tee test-expert" << std::endl;  
    return -9;
  }

  // *** Decode Arguments ***
  TString fullname = TString(argv[1]);  
  // *** Main Function ***
  return CreateExpertTree(fullname);
}
// ####################################################################################################

