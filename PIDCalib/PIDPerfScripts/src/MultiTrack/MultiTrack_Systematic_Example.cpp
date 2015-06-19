// $Id: $
// Include files 
#include "PIDPerfTools/TrackDataSet.h"
#include "PIDPerfTools/DataBinCuts.h"
#include "PIDPerfTools/PerfCalculator.h"
#include "PIDPerfTools/WeightDataSetTool.h"
#include "PIDPerfTools/MultiPerfCalculator.h"

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
//#include "MultiTrack_Systematic_Plots.cpp"

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
#include <boost/algorithm/string.hpp>

using namespace RooFit;
using namespace boost;

//A simple example of the usage of the MultiTrack PID calibration methods
//to determine the systematic error on the efficiency found with the
//calibration procedure.
//"**EDIT THIS **" is written where the code needs to be edited to work
//for the user.

//the binomial error on an efficiency for m = events that pass cut, N = total
double BinomialError(double m, double N)
{
  return TMath::Sqrt(m*(1-m/N))/N;  
}

//get the efficiency of a given cut on the given tree
std::pair<double,double> GetEff(std::string PreCut, std::string theCut, TTree * theTree)
{
  
  double ntot = theTree->GetEntries();
  if(PreCut!="") ntot = theTree->GetEntries(PreCut.c_str());

  double npass = theTree->GetEntries(theCut.c_str());
  if(PreCut!="") npass = theTree->GetEntries((PreCut + " && " + theCut).c_str());

  std::pair<double,double> thePair(npass/ntot, BinomialError(npass,ntot));
  return thePair;
  
}

//translate a cut on the calibration sample to an equivalent that that will work on the MC reference sample
//**EDIT THIS** if you have different names of the PID variables in your MC reference sample
std::string TranslateCutToMC(std::string Cut, std::string trackName, std::string CalibID)
{
  std::string tempstring;
  tempstring = Cut;

  boost::replace_all(tempstring,CalibID+"_",trackName+"_");
  boost::replace_all(tempstring,"CombDLLK","PIDK");
  boost::replace_all(tempstring,"My_DLLpK","("+trackName+"_PIDp-"+trackName+"_PIDK)");

  return tempstring;
}

std::vector<std::string> TranslateCutsToMC(std::vector<std::string> Cuts, std::string trackName, std::string CalibID)
{
  std::vector<std::string> MCCuts;
  for (std::vector<std::string>::iterator iter = Cuts.begin(); iter != Cuts.end(); iter++){
    MCCuts.push_back(TranslateCutToMC(*iter,trackName,CalibID));
  }
  return MCCuts;
}



void printUsage(const char* fname)
{
  std::cout << "usage: " << fname
       << "<Track> <inputFile> <treename>" << std::endl;
  std::cout << "Track is the track to loop over." << std::endl;
  std::cout << "treename is the key of the reference TTree inside inputFile." << std::endl;

  exit(0);
}

int main(int argc, char *argv[]) 
{

  int nargs=argc-1;  

  if (nargs!=3)
  {
    printUsage(argv[0]);
  }
  
  gSystem->Load("libRooStats.so");
  gROOT->SetBatch(kTRUE);

  std::string Track = argv[1];
  
  const char* inputFilename = argv[2];
  std::string tupleName = argv[3];
  
  //==================================================================
  // Get the MC and Data calibration histograms
  //==================================================================

  // The TH1Fs,2Fs or 3Fs containing the efficiency of cuts on the MC version of the calibration sample
  // are in MCHistFile
  //**EDIT THIS**
  TFile * MCHistFile = new TFile("/data/lhcb/users/smithe/PIDCalib_2012/Test_PerfHists_B02D0Kstar_D02KK_MC_merged.root");  
  
  
  // The TH1Fs,2Fs or 3Fs containing the efficiency of cuts on calibration sample
  // are in DataHistFile
  //**EDIT THIS**
  TFile * DataHistFile = new TFile("/data/lhcb/users/smithe/PIDCalib_2012/Test_PerfHists_B02D0Kstar_D02KK_Data_merged.root");

  //==================================================================

  //map of signal tracks to their cuts.
  //use these to construct the histogram names
  //**EDIT THIS**
  std::map<std::string,std::string> SignalTracks;
  SignalTracks["D0KPlus"] = "K_CombDLLK>0";
  SignalTracks["D0KMinus"] = "K_CombDLLK>0";
  SignalTracks["KstarK"] = "K_CombDLLK>3";
  SignalTracks["KstarPi"] = "Pi_CombDLLK<3";

  //map with CalibIDs of signal tracks
  std::map<std::string,std::string> CalibIDs;
  CalibIDs["D0KPlus"] = "K";
  CalibIDs["D0KMinus"] = "K";
  CalibIDs["KstarK"] = "K";
  CalibIDs["KstarPi"] = "Pi";

  
  //==================================================================
  //Getting the signal TTree
  //==================================================================

  TFile* mcCandFile = TFile::Open(inputFilename, "READ");
  if (!mcCandFile || mcCandFile->IsZombie()) {
    std::cout << "ERROR: Failed to open candidate file " << inputFilename 
         << " for reading" << std::endl;
    return 1;
  }
  TTree* mcCandTuple = 0;
  mcCandFile->GetObject(tupleName.c_str(), mcCandTuple);
  if (!mcCandTuple) {
    std::cout << "ERROR: Failed to retrieve candidate nTuple " << tupleName
         << " from file" << inputFilename << std::endl;
    return 1;
  }
  mcCandTuple->SetBranchStatus("*",1); // select all branches

  //=============================================================================

  std::cout << "Input filename: " <<inputFilename << std::endl;
  std::cout << "NTuple name: " << tupleName << std::endl;

  //=============================================================================
  //outFile is a transient file for creating lots of copies of the reference TTree
  //inside, then deleting..
  TFile* outFile = new TFile(("MultiTrack_Systematic_"+Track+"_"+tupleName+"_temp.root").c_str(),"recreate");
  if (!outFile || outFile->IsZombie()) {
    std::cout << "ERROR: Failed to create output file." << std::endl;
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
  
  TTree * outTree_MC = new TTree();
  TTree * outTree_Data = new TTree();
  
  std::vector<std::string> trackvector;
  std::vector<std::string> PIDNamevector;
  
  //while keeping all tracks at their default cuts scan over one of them.
  //apply the set of cuts to the MC signal and look at the efficiency
  //look at what you get from weighting the MC calib with MC
  //store this residual

  TrackDataSet * dummy_data = new TrackDataSet();
  MultiPerfCalculator<TrackDataSet>* dummy_calc = new MultiPerfCalculator<TrackDataSet>( dummy_data );
  std::vector<std::string> Cuts;

  TH1* theHist_MC = 0;
  TH1* theHist_Data = 0;

  //the efficiencies and errors from the MC calibration sample
  std::vector<std::pair<double,double> > theEffs_MCCal;

  //the efficiencies and errors from the data calibration sample
  std::vector<std::pair<double,double> > theEffs_DataCal;

  //the efficiencies and errors from MC Signal
  std::vector<std::pair<double,double> > theEffs_MCSig;

  //the DLL cut values
  //make sure the range parameters match in DLLsForRangeOfCuts and RangeOfCuts!
  std::vector<double> theDLLs;
  theDLLs = dummy_calc->DLLsForRangeOfCuts(SignalTracks[Track],5);
  
  //set the range of cuts to iterate over
  Cuts = dummy_calc->RangeOfCuts(SignalTracks[Track],5);

  //translate them to cuts on the MC tree
  std::vector<std::string> MCCuts = TranslateCutsToMC(Cuts,Track,CalibIDs[Track]);
  

  std::string MCCutstring;
  uint counter = 0;
  for (std::vector<std::string>::iterator iter = Cuts.begin();
       iter != Cuts.end(); iter++){

    //loop over these cuts
    //make fresh outTrees every time

    outTree_MC = mcCandTuple->CopyTree("");
    outTree_Data = mcCandTuple->CopyTree("");

    
    MCCutstring = "";
    counter = 0;
    for(std::map<std::string,std::string>::iterator iter2 = SignalTracks.begin();
        iter2 != SignalTracks.end(); iter2++){
      //loop over the signal tracks if the signal track is the same as the one currently being studied
      //set the histogram to the one at the Cut being done at the moment, else set it to the
      //one with the default cut.
      if (iter2->first==Track){
        theHist_MC = (TH1*)MCHistFile->Get((iter2->first+"_"+(*iter)).c_str());
        theHist_Data =  (TH1*)DataHistFile->Get((iter2->first+"_"+(*iter)).c_str());
      }
      else {
        theHist_MC = (TH1*)MCHistFile->Get((iter2->first+"_"+iter2->second).c_str());
        theHist_Data = (TH1*)DataHistFile->Get((iter2->first+"_"+iter2->second).c_str());
      }
      
      std::cout << theHist_MC->GetName() << std::endl;
      std::cout << theHist_Data->GetName() << std::endl;

      outTree_MC = addPIDEffBranchesND(outTree_MC,
                                       outFile,
                                       theHist_MC,
                                       iter2->first,
                                       iter2->first,
                                       VariableMap);

      outTree_Data = addPIDEffBranchesND(outTree_Data,
                                         outFile,
                                         theHist_Data,
                                         iter2->first,
                                         iter2->first,
                                         VariableMap);
      
      if (iter2->first==Track){  
        MCCutstring += TranslateCutToMC(iter->c_str(),iter2->first,CalibIDs[iter2->first]);
      }
      else {
        MCCutstring += TranslateCutToMC(iter2->second,iter2->first,CalibIDs[iter2->first]);
      }

      counter +=1;
      if (counter!=SignalTracks.size()) MCCutstring+="&&";
      
      //sometimes there could be 2 efficiencies for one track (see B2DV code) so need to make 2 vectors of names
      //could probably be done another way
      trackvector.push_back(iter2->first);
      PIDNamevector.push_back(iter2->first);
      
    }

    outTree_MC = addEventWeightsToTree(outTree_MC,
                                       outFile,
                                       "ID",
                                       trackvector,
                                       PIDNamevector);

    outTree_Data = addEventWeightsToTree(outTree_Data,
                                         outFile,
                                         "ID",
                                         trackvector,
                                         PIDNamevector);
    
    trackvector.clear();
    PIDNamevector.clear();
    
    //the efficiency calculated from performing the calibration process in MC
    theEffs_MCCal.push_back(AveragePIDEfficiency(outTree_MC));
    
    //the efficiency in data
    theEffs_DataCal.push_back(AveragePIDEfficiency(outTree_Data));
    
    //the efficiency of the cut on signal MC
    theEffs_MCSig.push_back(GetEff("",MCCutstring,mcCandTuple));
    
    //remove all the TTrees from memory
    gDirectory->DeleteAll();    

  }

  
  if (!outTree_MC) return 1;
  if (!outTree_Data) return 1;
 
  //outFile->Close();

  //make plots of the residuals as a function of the cut that has been varied
  //this is the interesting output of this code
  SystematicPlots(theEffs_MCSig,
                  theEffs_MCCal,
                  theEffs_DataCal,
                  theDLLs,
                  "ExampleSystPlots.root");
  
  delete mcCandTuple;
  delete outFile;
  delete dummy_data;
  delete dummy_calc;
  
  return 1;
}
