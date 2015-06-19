// #############################################################################
// Phys/Bs2JpsiKs Package
// Neural Net Expert
// Authors: Patrick Koppenburg & Kristof De Bruyn
// #############################################################################

// #############################################################################
// *** Load Useful Classes ***
// General C++
#include <iostream>

// Root
#include <TBranch.h>
#include <TFile.h>
#include <TString.h>
#include <TTree.h>

// Bs2JpsiKs Package
#include "IB2JpsiX.h"
#include "TupleLoader.h"

// NeuroBayes
#include <NeuroBayesExpert.hh>


// #############################################################################
// *** Expert ***
int runExpert(const TString module, const TString data, const TString step,
              const TString dir, const TString decay,
              const TString weightMethod) {
                       
// ***** PART 0: Initialise ***** //
////////////////////////////////////

  std::cout << "\n PROGRESS: Loading Data \n" << std::endl;

  // *** Load NTuple ***
  IB2JpsiX* ntuple = loadTuple(module, data, step, dir, decay, weightMethod);
  if (!ntuple) {
    std::cout << "ERROR: Ntuple could not be loaded" << std::endl;
    return -1;
  }

  // *** Set Output ***
  TString outFileName = makeFileName(module, data, step, dir, decay,
                                     weightMethod);
  // Error Handling
  if (outFileName=="") {
    std::cout << "ERROR: Failed to generate output file." << std::endl;
    return -1;
  }
  TFile *outfile = new TFile(outFileName, "RECREATE");
  outfile->cd();

// ***** PART I: Create Tree ***** //
/////////////////////////////////////
  
  std::cout << "\n PROGRESS: Creating Tree \n" << std::endl; 

  // *** Initialise ***
  // Variables
  const int nleafs = 25;
  ULong64_t eventNumber = 0;
  UInt_t runNumber = 0;
  unsigned int nPVs  = 0;
  Int_t tracktype = 0;
  Float_t sweight[nleafs];
  Float_t netOutput[nleafs];
  Double_t mass[nleafs];
  Double_t time[nleafs];
  unsigned int unbiased = 0;

  // Tree
  TTree* outtree = new TTree("NetTree", "Neural Net Tree");
  outtree->Branch("eventNumberNet", &eventNumber, "eventNumberNet/l");
  outtree->Branch("runNumberNet",   &runNumber,   "runNumberNet/i");
  outtree->Branch("nPVsNet",        &nPVs,        "nPVsNet/I");
  outtree->Branch("tracktypeNet",   &tracktype,   "tracktypeNet/I");
  outtree->Branch("sweightNet",     &sweight,     "sweightNet[nPVsNet]/F");
  outtree->Branch("netOutput",      &netOutput,   "netOutput[nPVsNet]/F");
  outtree->Branch("massNet",        &mass,        "massNet[nPVsNet]/D");
  outtree->Branch("timeNet",        &time,        "timeNet[nPVsNet]/D");
  if (step==m_NNUnbiased) {
    outtree->Branch("unbiased", &unbiased, "unbiased/I");
  }
  outtree->SetDirectory(outfile); 
  
  // *** NeuroBayes ***
  std::cout << "\n PROGRESS: Preparing NeuroBayes Expert \n" << std::endl;

  // Prepare Ntuple
  const unsigned int nvar_LL = ntuple->nVar(step, m_LL);
  float* InputArray_LL = new float[nvar_LL];
  const unsigned int nvar_DD = ntuple->nVar(step, m_DD);
  float* InputArray_DD = new float[nvar_DD];
  
  // Read File
  TString ExpFile_LL = mvaFileName(decay, step, m_LL, "nb");
  Expert* NeuroBayesExpert_LL = new Expert(ExpFile_LL);
  Expert* NeuroBayesExpert_DD = 0;
  if (step!=m_NNKstar) {
    TString ExpFile_DD = mvaFileName(decay, step, m_DD, "nb");
    NeuroBayesExpert_DD = new Expert(ExpFile_DD);
    std::cout << "EXPERT: Will be using file: " << ExpFile_LL
              << " and " << ExpFile_DD << std::endl;
  } else {
    std::cout << "EXPERT: Will be using file: " << ExpFile_LL << std::endl;
  }

  // *** Fill Tree ***
  std::cout << "\n PROGRESS: Running NeuroBayes Expert \n" << std::endl; 
  const Long64_t nentries = ntuple->nEntries();
  const Long64_t printMod = printFrac(nentries); 
  Long64_t nFailed = 0;
  Long64_t nReject = 0;
  Long64_t nGood = 0;

  bool filled_LL = false;
  bool filled_DD = false;

  bool inset = false;
  Long64_t fitLimit = 159000; // Max for 2011: 159186

  std::cout << "EXPERT: Will loop over " << nentries << " entries." << std::endl;
  for (Long64_t i=0; i<nentries;i++) {
    ntuple->GetChain()->GetEntry(i);

    // Progress
    if (i%printMod==0) {
      std::cout << " |-> " << i << " / " << nentries
                << " (" << 100*i/nentries << "%)" << std::endl;
    }

    inset = (trainset=="Full" || (nGood<fitLimit && (
            (trainset=="All" && ntuple->getGpsSecond()>numberofseconds*2./3.) ||
            (trainset=="2011" && ntuple->getInputFile()==0) ||
            (trainset=="2012" && ntuple->getInputFile()==1))));

    // Fill Variables
    runNumber   = ntuple->getRunNumber();
    eventNumber = ntuple->getEventNumber();
    nPVs        = ntuple->primaries();
    tracktype   = ntuple->TrackType();
    unbiased    = ntuple->isUnbiased();

    for (unsigned int pv = 0; pv!= nPVs; pv++) {
      // Fill Arrays
      sweight[pv] = ntuple->weightVal(pv);
      mass[pv]    = ntuple->mass(pv);
      time[pv]    = ntuple->time(pv);

      // Get Neural Net Output
      if (!inset) {
        netOutput[pv] = -7.;
        nReject++;
      } else if (sweight[pv]>-6.5) {
        if (tracktype==m_LL) {
          if (!filled_LL) ntuple->firstFill = true;
          ntuple->prepareNBArray(InputArray_LL, pv, step, m_LL);
          netOutput[pv] = NeuroBayesExpert_LL->nb_expert(InputArray_LL);
          filled_LL = true;
        } else if (tracktype==m_DD && step==m_NNKstar) {
          netOutput[pv] = 1.;
        } else if (tracktype==m_DD) {
          if (!filled_DD) ntuple->firstFill = true;
          ntuple->prepareNBArray(InputArray_DD, pv, step, m_DD);
          netOutput[pv] = NeuroBayesExpert_DD->nb_expert(InputArray_DD);
          filled_DD = true;
        } else {
          netOutput[pv] = ErrorCodes::Error;
        }
        nGood++;  
      } else {
        netOutput[pv] = sweight[pv];
        nFailed++;
      }
    } // pvs
    outtree->Fill();
  }
  
  // *** Results ***
  std::cout << "########################################" << std::endl;
  std::cout << "  RESULTS" << std::endl;
  std::cout << "  # Events with netOutput assigned: " << nGood   << std::endl;
  std::cout << "  # Events rejected to have netOut: " << nReject << std::endl;
  std::cout << "  # Events failing previous cuts  : " << nFailed << std::endl; 
  std::cout << "########################################" << std::endl;

  // *** Write to file ***
  std::cout << "\n PROGRESS: Writing File \n" << std::endl; 
  outfile->cd();
  outtree->Write();
  outfile->Close();
  std::cout << "\n PROGRESS: Finished! \n" << std::endl;
  return 0;
} 

// #############################################################################
// *** Main ***
int main(int argc, char** argv) {

  // *** Decode Arguments ***
  TString module, data, step, dir, decay, weightMethod;
  bool hasOpt;
  int out = decodeArgs(argc, argv,
                       module, data, step, dir, decay, weightMethod, hasOpt);
  if (out!=0) return out;
   
  // *** Main Function ***
  return runExpert(module, data, step, dir, decay, weightMethod);
}

// #############################################################################
