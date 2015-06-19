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

std::vector<std::string> TranslateCutsToMC(std::vector<std::string> Cuts, std::string trackName, std::string CalibID)
{
  std::vector<std::string> MCCuts;
  std::string tempstring;
  for (std::vector<std::string>::iterator iter = Cuts.begin(); iter != Cuts.end(); iter++){
    tempstring = *iter;
    //only need to use the boost replace_first algorithm
    boost::replace_all(tempstring,CalibID+"_",trackName+"_");
    boost::replace_all(tempstring,"CombDLLK","PIDK");
    boost::replace_all(tempstring,"My_DLLpK","("+trackName+"_PIDp-"+trackName+"_PIDK)");
    MCCuts.push_back(tempstring);
  }
  return MCCuts;
}

std::string TranslateCutToMC(std::string Cut, std::string trackName, std::string CalibID)
{
  std::string tempstring;
  tempstring = Cut;

  boost::replace_all(tempstring,CalibID+"_",trackName+"_");
  boost::replace_all(tempstring,"CombDLLK","PIDK");
  boost::replace_all(tempstring,"My_DLLpK","("+trackName+"_PIDp-"+trackName+"_PIDK)");

  return tempstring;
}

void printUsage(const char* fname)
{
  std::cout << "usage: " << fname
       << " <Mode> <Track> <inputFile> <treename> [<B0/B0bar>]" << std::endl;  

  std::cout << "Track is the track to loop over." << std::endl;
  std::cout << "write 'B0' or 'B0bar' as the third option to dictate whether "
            << "the PID eff is calculated for B0 or B0bar." << std::endl;
  exit(0);
}

int main(int argc, char *argv[]) 
{
  int nargs=argc-1;
  std::cout << nargs << std::endl;
  
  bool B0opt = false;
  std::string B = "";
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
  std::string Track = argv[2];
  
  const char* inputFilename = argv[3];
  std::string tupleName = argv[4];
  
  bool B0_ID = true;
  if (B0opt){  
    if (B=="B0") B0_ID = true;
    else if (B=="B0bar") B0_ID = false;
    else printUsage(argv[0]);
  }
  
  //==================================================================
  // Get the MC and Data calibration histograms
  //==================================================================
  if (inMode=="Bs02D0Kstar_D02KPi"||
      inMode=="B02D0Kstar_D02KPi_PhiAna"||
      inMode=="Bs02D0Kstar_D02KPi_PhiAna") Mode = "B02D0Kstar_D02KPi";

  std::string MChistfilename = "/data/lhcb/users/smithe/PIDCalib_2012/B2DV_PerfHists_";
  MChistfilename+=Mode+"_MC_Sumw2_merged.root";
  
  const char * MCHistFilename = MChistfilename.c_str();
  
  // The TH1Fs,2Fs or 3Fs containing the efficiency of cuts on calibration sample
  // are in HistFile
  TFile * MCHistFile = new TFile(MCHistFilename);
  
  std::string Datahistfilename = "/data/lhcb/users/smithe/PIDCalib_2012/B2DV_PerfHists_";
  Datahistfilename+=Mode+"_Data_Sumw2_merged.root";
  
  const char * DataHistFilename = Datahistfilename.c_str();
  
  // The TH1Fs,2Fs or 3Fs containing the efficiency of cuts on calibration sample
  // are in HistFile
  TFile * DataHistFile = new TFile(DataHistFilename);

  //==================================================================

  //map of signal tracks to their cuts.
  //use these to construct the histogram names
  std::map<std::string,std::string> SignalTracks;
  
  if (Mode=="B02D0Kstar_D02KK"){
    SignalTracks["D0KPlus"] = "K_CombDLLK>0";
    SignalTracks["D0KMinus"] = "K_CombDLLK>0";
    SignalTracks["KstarK"] = "K_CombDLLK>3";
    SignalTracks["KstarKpV"] = "My_DLLpK<10";
    SignalTracks["KstarPi"] = "Pi_CombDLLK<3";
  }
  else if (Mode=="B02D0Kstar_D02PiPi"){
    SignalTracks["D0PiPlus"] = "Pi_CombDLLK<4";
    SignalTracks["D0PiMinus"] = "Pi_CombDLLK<4";
    SignalTracks["KstarK"] = "K_CombDLLK>3";
    SignalTracks["KstarKpV"] = "My_DLLpK<10";   
    SignalTracks["KstarPi"] = "Pi_CombDLLK<3";
  }
  else if (Mode=="B02D0Kstar_D02KPi"){
    SignalTracks["D0K"] = "K_CombDLLK>0";
    SignalTracks["D0Pi"] = "Pi_CombDLLK<4";
    SignalTracks["KstarK"] = "K_CombDLLK>3";
    SignalTracks["KstarKpV"] = "My_DLLpK<10";   
    SignalTracks["KstarPi"] = "Pi_CombDLLK<3";
  }
  else if (Mode=="B02D0Phi_D02KPi"){
    SignalTracks["D0K"] = "K_CombDLLK>0";
    SignalTracks["D0Pi"] = "Pi_CombDLLK<4";
    SignalTracks["PhiKPlus"] = "K_CombDLLK>3";
    SignalTracks["PhiKMinus"] = "K_CombDLLK>3";
  }
  else 
    return EXIT_FAILURE;

  //map with CalibIDs of signal tracks
  std::map<std::string,std::string> CalibIDs;
  if (Mode=="B02D0Kstar_D02KK"){
    CalibIDs["D0KPlus"] = "K";
    CalibIDs["D0KMinus"] = "K";
    CalibIDs["KstarK"] = "K";
    CalibIDs["KstarKpV"] = "K";
    CalibIDs["KstarPi"] = "Pi";
  }
  else if (Mode=="B02D0Kstar_D02PiPi"){
    CalibIDs["D0PiPlus"] = "Pi";
    CalibIDs["D0PiMinus"] = "Pi";
    CalibIDs["KstarK"] = "K";
    CalibIDs["KstarKpV"] = "K";   
    CalibIDs["KstarPi"] = "Pi";
  }
  else if (Mode=="B02D0Kstar_D02KPi"){
    CalibIDs["D0K"] = "K";
    CalibIDs["D0Pi"] = "Pi";
    CalibIDs["KstarK"] = "K";
    CalibIDs["KstarKpV"] = "K";
    CalibIDs["KstarPi"] = "Pi";
  }
  else if (Mode=="B02D0Phi_D02KPi"){
    CalibIDs["D0K"] = "K";
    CalibIDs["D0Pi"] = "Pi";
    CalibIDs["PhiKPlus"] = "K";
    CalibIDs["PhiKMinus"] = "K";
  }
  else 
    return EXIT_FAILURE;

  
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

  std::cout << "MC Hist filename: " << MCHistFilename << std::endl;
  std::cout << "Data Hist filename: " << DataHistFilename << std::endl;
  std::cout << "Input filename: " <<inputFilename << std::endl;
  std::cout << "NTuple name: " << tupleName << std::endl;

  //=============================================================================
  //outFile is a transient file for creating lots of copies of the reference TTree
  //inside, then deleting..
  TFile* outFile = new TFile(("/data/lhcb/users/smithe/PIDCalib_2012/MultiTrack_Systematic_"+Mode+
                              "_"+Track+"_"+tupleName+"_"+B+"_temp.root").c_str(),"recreate");
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

  std::vector<std::string> MCCuts = TranslateCutsToMC(Cuts,(Track=="KstarKpV")?"KstarK":Track,CalibIDs[Track]);
  
  for (std::vector<std::string>::iterator iter = Cuts.begin();
       iter != Cuts.end(); iter++){
    std::cout << *iter << std::endl;
  }
  for (std::vector<std::string>::iterator iter = MCCuts.begin();
       iter != MCCuts.end(); iter++){
    std::cout << *iter << std::endl;
  }
  for (std::vector<double>::iterator iter = theDLLs.begin();
       iter != theDLLs.end(); iter++){
    std::cout << *iter << std::endl;
  }
  
  std::string MCCutstring;
  uint counter = 0;
  for (std::vector<std::string>::iterator iter = Cuts.begin();
       iter != Cuts.end(); iter++){

    //loop over these cuts
    //make fresh outTree every time
    if(B0opt){  
      outTree_MC = mcCandTuple->CopyTree((B0_ID?"Bd_TRUEID>0":"Bd_TRUEID<0"));
      outTree_Data = mcCandTuple->CopyTree((B0_ID?"Bd_TRUEID>0":"Bd_TRUEID<0"));
    }
    else{
      outTree_MC = mcCandTuple->CopyTree("");
      outTree_Data = mcCandTuple->CopyTree("");
    }
    
    MCCutstring = "";
    counter = 0;
    for(std::map<std::string,std::string>::iterator iter2 = SignalTracks.begin();
        iter2 != SignalTracks.end(); iter2++){
      //loop over the signal tracks if the signal track is the same as the one currently being studied
      //set the histogram to the one at the Cut being done at the moment, else set it to the
      //one with the default cut.
      if (iter2->first==Track){
        theHist_MC = (TH1*)MCHistFile->Get((((iter2->first=="KstarKpV")?"KstarK":iter2->first)
                                            +"_"+(*iter)).c_str());
        theHist_Data =  (TH1*)DataHistFile->Get((((iter2->first=="KstarKpV")?"KstarK":iter2->first)
                                                 +"_"+(*iter)).c_str());
      }
      else {
        theHist_MC = (TH1*)MCHistFile->Get((((iter2->first=="KstarKpV")?"KstarK":iter2->first)+"_"+iter2->second).c_str());
        theHist_Data = (TH1*)DataHistFile->Get((((iter2->first=="KstarKpV")?"KstarK":iter2->first)+"_"+iter2->second).c_str());
      }
      
      std::cout << theHist_MC->GetName() << std::endl;
      std::cout << theHist_Data->GetName() << std::endl;

      outTree_MC = addPIDEffBranchesND(outTree_MC,
                                       outFile,
                                       theHist_MC,
                                       (iter2->first=="KstarKpV")?"KstarK":iter2->first,
                                       iter2->first,
                                       VariableMap);

      outTree_Data = addPIDEffBranchesND(outTree_Data,
                                         outFile,
                                         theHist_Data,
                                         (iter2->first=="KstarKpV")?"KstarK":iter2->first,
                                         iter2->first,
                                         VariableMap);

      if (iter2->first==Track){  
        MCCutstring += TranslateCutToMC(iter->c_str(),(iter2->first=="KstarKpV")?"KstarK":iter2->first,CalibIDs[iter2->first]);
      }
      else {
        MCCutstring += TranslateCutToMC(iter2->second,(iter2->first=="KstarKpV")?"KstarK":iter2->first,CalibIDs[iter2->first]);
      }

      
      counter +=1;
      if (counter!=SignalTracks.size()) MCCutstring+="&&";
      
      //2 efficiencies for one track so need to make 2 vectors of names 
      trackvector.push_back((iter2->first=="KstarKpV")?"KstarK":iter2->first);
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
    
    theEffs_MCCal.push_back(AveragePIDEfficiency(outTree_MC));
    theEffs_DataCal.push_back(AveragePIDEfficiency(outTree_Data));

    std::cout << MCCutstring << std::endl;
    
    if(B0opt) theEffs_MCSig.push_back(GetEff((std::string)(B0_ID?"Bd_TRUEID>0":"Bd_TRUEID<0"),MCCutstring,mcCandTuple));
    else theEffs_MCSig.push_back(GetEff("",MCCutstring,mcCandTuple));
    
    gDirectory->DeleteAll();    
    outFile->Flush();
  }

  for (uint i = 0; i < theEffs_DataCal.size(); i++){
    std::cout << "Residual at " << theDLLs.at(i) << "is " 
              << ((theEffs_MCCal.at(i).first-theEffs_MCSig.at(i).first)/
                  (theEffs_MCCal.at(i).first+theEffs_MCSig.at(i).first))*theEffs_DataCal.at(i).first
              << std::endl;
  }
  
  if (!outTree_MC) return 1;
  if (!outTree_Data) return 1;
  //outFile->cd();
  //outTree_MC->Write();
  //outTree_Data->Write();
  //outFile->Close();
  
  //make plots
  SystematicPlots(theEffs_MCSig,
                  theEffs_MCCal,
                  theEffs_DataCal,
                  theDLLs,
                  "/data/lhcb/users/smithe/PIDCalib_2012/MultiTrackSyst_"+inMode+"_"+Track+"_"+B+".root");

//  delete outTree_MC;
//  delete outTree_Data;
  delete mcCandTuple;
  delete outFile;
  delete dummy_data;
  delete dummy_calc;
  
  return 1;
}
