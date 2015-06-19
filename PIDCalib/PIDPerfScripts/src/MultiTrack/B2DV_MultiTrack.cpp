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
       << " <Mode> <inputFile> <treename> <outputFile> [<B0/B0Bar>]" << std::endl;  
  std::cout << " <treename> is the name of the tree of reference events inside inputFile." << std::endl;
  std::cout << "outputFile is the name of the output file containing the original "
       << "candidates with the additional PID efficiecy and error leaves"
       << std::endl << std::endl;
  std::cout << "write 'B0' or 'B0bar' as the third option to dictate whether the PID eff is calculated "
       << "for B0 or B0bar (optional)." << std::endl;
  exit(0);
}

int main(int argc, char *argv[]) 
{

  int nargs=argc-1;
  std::cout << nargs << std::endl;
  
  bool B0opt = false;
  std::string B;
  if (nargs<4)
  {
    printUsage(argv[0]);
  }
  else if (nargs==5){
    B0opt = true;
    B = argv[5];
    if (!(B=="B0"||B=="B0bar")) printUsage(argv[0]);
  }
  else if (nargs>5) printUsage(argv[0]);
  
  gSystem->Load("libRooStats.so");
  gROOT->SetBatch(kTRUE);

  std::string inMode = argv[1];
  std::string Mode = inMode;
  
  const char* inputFilename = argv[2];
  const char* outputFilename = argv[4];
  std::string tupleName = argv[3];
  
  bool B0_ID = true;
  if (B0opt){  
    if (B=="B0") B0_ID = true;
    else if (B=="B0bar") B0_ID = false;
    else printUsage(argv[0]);
  }

  //==================================================================
  // Get the calibration histograms (output of Test_PerfHist)
  //==================================================================
  if (inMode=="Bs02D0Kstar_D02KPi"){
    Mode = "B02D0Kstar_D02KPi";
  }
  else if (inMode=="B02D0Kstar_D02KPi_PhiAna"||
           inMode=="Bs02D0Kstar_D02KPi_PhiAna"||
           inMode=="B02D0Phi_D02KPi") Mode = "B02D0Kstar_D02KPi";
  
  std::string histfilename = "/data/lhcb/users/smithe/PIDCalib_2012/B2DV_PerfHists_";
  histfilename+=Mode+"_Data_Sumw2_merged.root";

  const char * HistFilename = histfilename.c_str();
  
  // The TH1Fs,2Fs or 3Fs containing the efficiency of cuts on calibration sample
  // are in HistFile
  TFile * HistFile = new TFile(HistFilename);
  //HistFile->ls();

  if (inMode=="B02D0Kstar_D02KPi_PhiAna"||
      inMode=="Bs02D0Kstar_D02KPi_PhiAna"||
      inMode=="B02D0Phi_D02KPi") Mode = inMode;
  
  //=============================================================================
  // Define which histograms correspond to which signal tracks
  //=============================================================================
  //A Map of signal tracks to their calibration performance histos

  std::map<std::string,TH1*> Map;
  if (Mode=="B02D0Kstar_D02KK"){
    Map["D0KPlus"] = (TH1*)HistFile->Get("D0KPlus_K_CombDLLK>0");
    Map["D0KMinus"] = (TH1*)HistFile->Get("D0KMinus_K_CombDLLK>0");
    Map["KstarK"] = (TH1*)HistFile->Get("KstarK_K_CombDLLK>3 && My_DLLpK<10");
    Map["KstarPi"] = (TH1*)HistFile->Get("KstarPi_Pi_CombDLLK<3");
  }
  else if (Mode=="B02D0Kstar_D02PiPi"){
    Map["D0PiPlus"] = (TH1*)HistFile->Get("D0PiPlus_Pi_CombDLLK<4");
    Map["D0PiMinus"] = (TH1*)HistFile->Get("D0PiMinus_Pi_CombDLLK<4");
    Map["KstarK"] = (TH1*)HistFile->Get("KstarK_K_CombDLLK>3 && My_DLLpK<10");
    Map["KstarPi"] = (TH1*)HistFile->Get("KstarPi_Pi_CombDLLK<3");
  }
  else if (Mode=="B02D0Kstar_D02KPi"){
    Map["D0K"] = (TH1*)HistFile->Get("D0K_K_CombDLLK>0");
    Map["D0Pi"] = (TH1*)HistFile->Get("D0Pi_Pi_CombDLLK<4");
    Map["KstarK"] = (TH1*)HistFile->Get("KstarK_K_CombDLLK>3 && My_DLLpK<10");
    Map["KstarPi"] = (TH1*)HistFile->Get("KstarPi_Pi_CombDLLK<3");
  }
  else if (Mode=="B2D0Pi_D02KPi"){
    Map["Bach"] = (TH1*)HistFile->Get("Bach_Pi_CombDLLK<4");
  }
  else if (Mode=="Lb2D0pPi_D02KPi"){
    Map["D0K"] = (TH1*)HistFile->Get("D0K_K_CombDLLK>0");
    Map["D0Pi"] = (TH1*)HistFile->Get("D0Pi_Pi_CombDLLK<4");
    //exactly the same but KstarK_K --> KstarK_P because the calib hist was made from protons
    Map["KstarK"] = (TH1*)HistFile->Get("KstarK_P_CombDLLK>3 && My_DLLpK<10");
    Map["KstarPi"] = (TH1*)HistFile->Get("KstarPi_Pi_CombDLLK<3");
  }
  else if (Mode=="B02D0Kstar_D02KPi_PhiAna"){
    Map["D0K"] = (TH1*)HistFile->Get("D0K_K_CombDLLK>0");
    Map["D0Pi"] = (TH1*)HistFile->Get("D0Pi_Pi_CombDLLK<4");
    Map["KstarK"] = (TH1*)HistFile->Get("D0K_K_CombDLLK>3");
    Map["KstarPi"] = (TH1*)HistFile->Get("KstarPi_Pi_CombDLLK<3");
  }
  else if (Mode=="Bs02D0Kstar_D02KPi_PhiAna"){
    Map["D0K"] = (TH1*)HistFile->Get("D0K_K_CombDLLK>0");
    Map["D0Pi"] = (TH1*)HistFile->Get("D0Pi_Pi_CombDLLK<4");
    Map["KstarK"] = (TH1*)HistFile->Get("D0K_K_CombDLLK>3");
    Map["KstarPi"] = (TH1*)HistFile->Get("KstarPi_Pi_CombDLLK<3");
  }
  else if (Mode=="B02D0Phi_D02KPi"){
    Map["D0K"] = (TH1*)HistFile->Get("D0K_K_CombDLLK>0");
    Map["D0Pi"] = (TH1*)HistFile->Get("D0Pi_Pi_CombDLLK<4");
    Map["PhiKPlus"] = (TH1*)HistFile->Get("D0K_K_CombDLLK>3");
    Map["PhiKMinus"] = (TH1*)HistFile->Get("D0K_K_CombDLLK>3");    
  }
  else {
    std::cout << "Unrecognised mode, could not retrieve histograms..." << std::endl;
    return 1;
  }

  //check that all the histograms were retrieved properly
  for (std::map<std::string,TH1*>::iterator iter = Map.begin(); iter != Map.end(); iter++){
    if (!(iter->second)){
      std::cout << "Histogram for " << iter->first << " not retrieved properly, check names." << std::endl;
      exit(EXIT_FAILURE);
    }
  }  
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
  mcCandTuple = (TTree*)mcCandFile->Get(tupleName.c_str());
  
  //mcCandFile->GetObject(tupleName.c_str(), mcCandTuple);
  std::cout << "mcCandTuple contains " << mcCandTuple->GetEntries() << std::endl;  
  if (!mcCandTuple) {
    std::cout << "ERROR: Failed to retrieve candidate nTuple " << tupleName
         << " from file" << inputFilename << std::endl;
    return 1;
  }
  mcCandTuple->SetBranchStatus("*",1); // select all branches


  //=============================================================================

  std::cout << "Hist filename: " << HistFilename << std::endl;
  std::cout << "Input filename: " <<inputFilename << std::endl;
  std::cout << "NTuple name: " << tupleName << std::endl;
  std::cout << "Output filename: " << outputFilename << std::endl;

  //=============================================================================

  TFile* outFile = new TFile(outputFilename,"RECREATE");
  if (!outFile || outFile->IsZombie()) {
    std::cout << "ERROR: Failed to create output file " << outputFilename
         << std::endl;
    return 1;
  }

  outFile->cd();

  //a map defining what the variables are called in the signal ntuple that correspond
  //to the internal codes in the addPIDEffBranches function: P, PT, ETA and nTRACKS.
  std::map<std::string,std::string> VariableMap;
  VariableMap["PT"] = "PT";
  VariableMap["P"] = "P";
  VariableMap["ETA"] = "LOKI_ETA";
  VariableMap["nTRACKS"] = "BestTracks";
  if (Mode=="B2D0Pi_D02KPi"){
    VariableMap["ETA"] = "TRACK_Eta";
    VariableMap["nTRACKS"] = "nTracks";
  }
  
  TTree * outTree = new TTree();
  
  //outTree = mcCandTuple->CloneTree();

  if (B0opt) outTree = mcCandTuple->CopyTree((B0_ID?"Bd_TRUEID>0":"Bd_TRUEID<0"));
  else outTree = mcCandTuple->CopyTree("");
  
  std::cout << "outTree contains " << outTree->GetEntries() << " entries." << std::endl;
  
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

  outTree = addEventWeightsToTree(outTree,
                                  outFile,
                                  "ID",
                                  trackvector,
                                  trackvector);
  
  std::pair<double,double> EffAndError =   AveragePIDEfficiency(outTree);
  //std::cout << EffAndError.first << " +- " << EffAndError.second << std::endl;
  
  if (!outTree) return 1;
  outFile->cd();
  outTree->Write();
  outFile->Close();
  delete outFile;
  return 1;
}
