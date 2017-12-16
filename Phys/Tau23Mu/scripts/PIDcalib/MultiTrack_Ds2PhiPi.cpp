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
#include <iostream>

// Boost
#include <boost/lexical_cast.hpp>

using namespace RooFit;
using namespace boost;
using namespace std;

void printUsage(const char* fname)
{
  cout << "usage: " << fname
       << "<inputFile> <treename> <outputFile>" << endl;  
  cout << " <treename> is the name of the tree of reference events inside inputFile." << endl;
  cout << "outputFile is the name of the output file containing the original "
       << "candidates with the additional PID efficiecy and error leaves"
       << endl << endl;
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
  //TFile * HistFile = new TFile("PerfHist_Muons_DLLmu1muk20_Merged.root");
  //TFile * HistFile = new TFile("PerfHist_Muons_MagUp_index0_DLLmu1muk20.root");
  //TFile * HistFile = new TFile("PerfHist_027_merged.root");
  //TFile * HistFile = new TFile("PerfHist_057_merged.root");
  //TFile * HistFile = new TFile("PerfHist_075_merged.root");
  TFile * HistFile = new TFile("PerfHist_081_merged.root");

  //=============================================================================
  //Getting the signal TTree
  //=============================================================================
  
  TFile* mcCandFile = TFile::Open(inputFilename, "READ");
  if (!mcCandFile || mcCandFile->IsZombie()) {
    cout << "ERROR: Failed to open candidate file " << inputFilename 
         << " for reading" << endl;
    return 1;
  }
  TTree* mcCandTuple = 0;
  mcCandFile->ls();
  mcCandTuple = (TTree*)mcCandFile->Get(tupleName);

  std::cout << "mcCandTuple contains " << mcCandTuple->GetEntries() << std::endl;  
  if (!mcCandTuple) {
    cout << "ERROR: Failed to retrieve candidate nTuple " << tupleName
         << " from file" << inputFilename << endl;
    return 1;
  }
  mcCandTuple->SetBranchStatus("*",1); // select all branches

  //a map defining what the variables are called in the signal ntuple that correspond
  //to the internal codes in the addPIDEffBranchesND function: P, PT, ETA and nTRACKS.
  //only necessary to add entries here for the variables that are used when making
  //the performance histograms
  //** EDIT THIS **
  std::map<std::string,std::string> VariableMap;
  VariableMap["PT"] = "pt";
  VariableMap["P"] = "p";
  VariableMap["ETA"] = "eta";
  VariableMap["nTRACKS"] = "NbestTracks";
  
  //=============================================================================
  // Define which histograms correspond to which signal tracks
  //=============================================================================

  //A Map of the names of signal tracks in mcCandTuple to their corresponding
  //performance histograms
  //** EDIT THIS **
  std::map<std::string,TH1*> Map;
  Map["p0"] = (TH1*)HistFile->Get("ANN > 0.81");
  Map["p1"] = (TH1*)HistFile->Get("ANN > 0.81");
  Map["p2"] = (TH1*)HistFile->Get("ANN > 0.81");
  //Map["D0KMinus"] = (TH1*)HistFile->Get("D0KMinus_K_CombDLLK>0");
  //Map["KstarK"] = (TH1*)HistFile->Get("KstarK_K_CombDLLK>3 && My_DLLpK<10");
  //Map["KstarPi"] = (TH1*)HistFile->Get("KstarPi_Pi_CombDLLK<3");

  //=============================================================================

  cout << "Input filename: " <<inputFilename << endl;
  cout << "NTuple name: " << tupleName << endl;
  cout << "Output filename: " << outputFilename << endl;

  //=============================================================================
  //Open outputfile and create output TTree that will have the PID Eff branches
  //added.
  //=============================================================================
  TFile* outFile = new TFile(outputFilename,"RECREATE");
  if (!outFile || outFile->IsZombie()) {
    cout << "ERROR: Failed to create output file " << outputFilename
         << endl;
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
