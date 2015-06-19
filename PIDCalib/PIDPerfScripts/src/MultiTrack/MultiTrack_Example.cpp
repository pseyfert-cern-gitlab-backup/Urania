// $Id: $
// Include files 
#include "PIDPerfTools/TrackDataSet.h"
#include "PIDPerfTools/DataBinCuts.h"
#include "PIDPerfTools/PerfCalculator.h"
#include "PIDPerfTools/WeightDataSetTool.h"
#include "TFile.h"
#include "TTree.h"
#include "TH3F.h"
#include "TChain.h"
#include "TSystem.h"
#include "RooRealVar.h"
#include "RooBinning.h"
#include "TCut.h"
#include "RooWorkspace.h"
#include <list>
#include <sstream>
#include <map>
#include "TCanvas.h"

#include "MultiTrackTools.cpp"

// $Id: $
// Include files
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"
#include "TCut.h"
#include "RooRealVar.h"
#include "RooBinning.h"
#include "RooWorkspace.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TMath.h"

// std libraries
#include <list>
#include <boost/lexical_cast.hpp>
#include <cstdlib>
#include <cassert>
#include <iomanip>

// Boost
#include <boost/lexical_cast.hpp>

using namespace RooFit;
using namespace boost;

void printUsage(const char* fname)
{
  std::cout << "usage: " << fname
            << "<inputFile> <treename> <outputFile>" << std::endl;  
  std::cout << " <treename> is the name of the tree of reference events inside inputFile." << std::endl;
  std::cout << "outputFile is the name of the output file containing the original "
       << "candidates with the additional PID efficiecy and error leaves"
       << std::endl << std::endl;
  exit(0);
}

int main(int argc, char *argv[]) 
{
  //A simple example of the usage of the MultiTrack PID calibration methods
  //"**EDIT THIS **" is written where the code needs to be edited to work
  //for the user.

  int nargs=argc-1;
  std::cout << nargs << std::endl;
  
  if (nargs!=3)
  {
    printUsage(argv[0]);
  }
  
  gSystem->Load("libRooStats.so");
  gROOT->SetBatch(kTRUE);
  
  const char* inputFilename = argv[1];
  const char* tupleName = argv[2];
  const char* outputFilename = argv[3];

  //==================================================================
  // Get the calibration histograms (output of Test_PerfHist)
  //==================================================================

  // The TH1Fs,2Fs or 3Fs containing the efficiency of cuts on calibration sample
  // are in HistFile
  //** EDIT THIS **
  TFile * HistFile = new TFile("/data/lhcb/users/smithe/PIDCalib_2012/Test_PerfHists_B02D0Kstar_D02KK_Data_merged.root");

  //=============================================================================
  //Getting the signal TTree
  //=============================================================================
  
  TFile* mcCandFile = TFile::Open(inputFilename, "READ");
  if (!mcCandFile || mcCandFile->IsZombie()) {
    std::cout << "ERROR: Failed to open candidate file " << inputFilename 
         << " for reading" << std::endl;
    return 1;
  }
  TTree* mcCandTuple = 0;
  mcCandFile->ls();
  mcCandTuple = (TTree*)mcCandFile->Get(tupleName);

  std::cout << "mcCandTuple contains " << mcCandTuple->GetEntries() << std::endl;  
  if (!mcCandTuple) {
    std::cout << "ERROR: Failed to retrieve candidate nTuple " << tupleName
         << " from file" << inputFilename << std::endl;
    return 1;
  }
  mcCandTuple->SetBranchStatus("*",1); // select all branches

  //a map defining what the variables are called in the signal ntuple that correspond
  //to the internal codes in the addPIDEffBranchesND function: P, PT, ETA and nTRACKS.
  //only necessary to add entries here for the variables that are used when making
  //the performance histograms
  //** EDIT THIS **
  std::map<std::string,std::string> VariableMap;
  VariableMap["PT"] = "PT";
  VariableMap["P"] = "P";
  VariableMap["ETA"] = "LOKI_ETA";
  VariableMap["nTRACKS"] = "BestTracks";
  
  //=============================================================================
  // Define which histograms correspond to which signal tracks
  //=============================================================================

  //A Map of the names of signal tracks in mcCandTuple to their corresponding
  //performance histograms
  //** EDIT THIS **
  std::map<std::string,TH1*> Map;
  Map["D0KPlus"] = (TH1*)HistFile->Get("D0KPlus_K_CombDLLK>0");
  Map["D0KMinus"] = (TH1*)HistFile->Get("D0KMinus_K_CombDLLK>0");
  Map["KstarK"] = (TH1*)HistFile->Get("KstarK_K_CombDLLK>3 && My_DLLpK<10");
  Map["KstarPi"] = (TH1*)HistFile->Get("KstarPi_Pi_CombDLLK<3");

  //check that all the histograms were retrieved properly
  for (std::map<std::string,TH1*>::iterator iter = Map.begin(); iter != Map.end(); iter++){
    if (!(iter->second)){
      std::cout << "Histogram for " << iter->first << " not retrieved properly, check names." << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  //=============================================================================

  std::cout << "Input filename: " <<inputFilename << std::endl;
  std::cout << "NTuple name: " << tupleName << std::endl;
  std::cout << "Output filename: " << outputFilename << std::endl;

  //=============================================================================
  //Open outputfile and create output TTree that will have the PID Eff branches
  //added.
  //=============================================================================
  TFile* outFile = new TFile(outputFilename,"RECREATE");
  if (!outFile || outFile->IsZombie()) {
    std::cout << "ERROR: Failed to create output file " << outputFilename
         << std::endl;
    return 1;
  }

  outFile->cd();
  
  TTree * outTree = new TTree();
  outTree = mcCandTuple->CopyTree("");
  //=============================================================================
  
  std::vector<std::string> trackvector;
  //loop over the signal tracks in the map and add PID efficiency and error branches for each one
  //from its corresponding histogram made from the calibration sample
  for (std::map<std::string,TH1*>::iterator iter = Map.begin();
       iter != Map.end(); iter++){

    outTree = addPIDEffBranchesND(outTree, 
                                  outFile,
                                  iter->second,
                                  iter->first,
                                  iter->first,
                                  VariableMap);
    
    trackvector.push_back(iter->first);
    
  }  

  //calculate and fill Event weights (Event PID efficiencies) for the signal
  outTree = addEventWeightsToTree(outTree,
                                  outFile,
                                  "ID",
                                  trackvector,
                                  trackvector);
  
  //take the mean of all Event weights
  std::pair<double,double> EffAndError = AveragePIDEfficiency(outTree);
  
  if (!outTree) return 1;
  outFile->cd();
  outTree->Write();
  outFile->Close();
  delete outFile;
  
  return 1;
}
