// $Id: $
// Include files 
// C++
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>

// ROOT
#include "TDirectory.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TF1.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TLeaf.h"
#include "TBranch.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TEfficiency.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TPaveText.h"
#include "TFitResult.h"
#include "TLegend.h"
#include "TMath.h"
#include "TObjArray.h"
#include "TEntryList.h"

// RooFit
#include "RooWorkspace.h"

// local
#include "PIDPerfTools/EvtTrackDataSet.h"
#include "PIDPerfTools/DataBinCuts.h"
#include "PIDPerfTools/PerfCalculator.h"
#include "PIDPerfTools/PIDCrossTable.h"

Bool_t validBranch(TTree* tt, TString brName) 
{
  if (!tt) {
    std::cout << "No TTree specified" << std::endl;
    return kFALSE;
  }
  
  if (!tt->GetBranch(brName.Data())) return kFALSE;
  return kTRUE;
}

TString getBranchType(TTree* tt, TString brName) 
{
  if (!tt) {
    std::cout << "No TTree specified" << std::endl;
    return "";
  }
  TBranch* br = tt->GetBranch(brName.Data());
  if (!br) {
    std::cout << "Failed to retrieve branch " << brName
              << " from TTree " << tt->GetName() << std::endl;
    return "";
  }
  TString brType=((TLeaf*)br->GetListOfLeaves()->At(0))->GetTypeName();
  return brType;
}

Bool_t checkEqualAxes(const TAxis* a1, const TAxis* a2) {
  if (!a1||!a2) {
    std::cout << "ERROR: Cannot check consistency of non-existent axes"
              << std::endl;
    return kFALSE;
  }
  
  // Check that the axis are the same 
  if (a1->GetNbins() != a2->GetNbins() ) {
    std::cout << "ERROR: Axes have different number of bins: a1 = "
              << a1->GetNbins() << ", a2 = " << a2->GetNbins() << std::endl;
    return kFALSE;
  }
  // Check the axis limits
  if ( ! TMath::AreEqualRel(a1->GetXmin(), a2->GetXmin(),1.E-12) ||
       ! TMath::AreEqualRel(a1->GetXmax(), a2->GetXmax(),1.E-12) ) {
    std::cout << "ERROR: Axis have different limits" << std::endl;
    return kFALSE;
  }
  // Check the bin limits
  const TArrayD * h1Array = a1->GetXbins(); 
  const TArrayD * h2Array = a2->GetXbins(); 
  Int_t fN = h1Array->fN;
  if ( fN != 0 ) {
    if ( h2Array->fN != fN ) {
      std::cout << "ERROR: Axes bin arrays are different sizes: a1 = "
                << fN << ", a2 = " << h2Array->fN << std::endl;
      return kFALSE;
    }
    else {
      for ( int i = 0; i < fN; ++i ) {
        if ( ! TMath::AreEqualRel( h1Array->GetAt(i), 
                                   h2Array->GetAt(i), 1E-10 ) ) {
          std::cout << "ERROR: Axes have different bin boundaries"
                    << std::endl;
          return kFALSE;
        }
      }
    }
  }
  return kTRUE;
}

Bool_t checkConsistency(const TH1* h1, const TH1* h2) 
{
  if (!h1||!h2) {
    std::cout << "ERROR: Cannot check consistency of non-existent histograms" 
              << std::endl;
    return kFALSE;
  }
  Int_t nDim=h1->GetDimension();
  if (nDim!=h2->GetDimension()) {
    std::cout << "ERROR: Histograms have inconsistent number of dimensions: "
              << "h1 (" << h1->GetName() << ") = " << nDim
              << ", h2 (" << h2->GetName() << ") = " << h2->GetDimension() 
              << std::endl;
    return kFALSE;
  }
  Int_t nbinsx=-1;
  Int_t nbinsy=-1;
  Int_t nbinsz=-1;

  nbinsx = h1->GetNbinsX();
  if (nbinsx!=h2->GetNbinsX()) {
    std::cout << "ERROR: Histograms have inconsistent number of X bins: "
              << "h1 (" << h1->GetName() << ") = " << nbinsx 
              << ", h2 (" << h2->GetName() << ") = " << h2->GetNbinsX() 
              << std::endl;
    return kFALSE;
  }
  
  if (nDim>=2) {
    nbinsy = h1->GetNbinsY();
    if (nbinsy!=h2->GetNbinsY()) {
      std::cout << "ERROR: Histograms have inconsistent number of Y bins: "
                << "h1 (" << h1->GetName() << ") = " << nbinsy
                << ", h2 (" << h2->GetName() << ") = " << h2->GetNbinsY() 
                << std::endl;
      return kFALSE;
    }
  }
  
  if (nDim==3) {
    nbinsz = h1->GetNbinsZ();
    if (nbinsz!=h2->GetNbinsZ()) {
      std::cout << "ERROR: Histograms have inconsistent number of Z bins: "
                << "h1 (" << h1->GetName() << ") = " << nbinsz
                << ", h2 (" << h2->GetName() << ") = " << h2->GetNbinsZ() 
                << std::endl;
      return kFALSE;
    }
  }
  if (!checkEqualAxes(h1->GetXaxis(), h2->GetXaxis())) return kFALSE;
  if (nDim>=2) {
    if (!checkEqualAxes(h1->GetYaxis(), h2->GetYaxis())) return kFALSE;
  }
  if (nDim==3) {
    if (!checkEqualAxes(h1->GetZaxis(), h2->GetZaxis())) return kFALSE;
  }
  return kTRUE;
}


//Parses what is on the axes of a histogram into names of branches in the reference tree
std::vector<std::string> ParseAxes(TH1* theHist,
                                   std::map<std::string,std::string> VarMap,
                                   std::string trackName)
{
  //Map of internal titles of variables in PIDPerfTools to codes used for this function
  std::map<std::string,std::string> AxisVars;
  AxisVars["Track Momentum [MeV/c]"] = "P";
  AxisVars["Transverse Momentum [MeV/c]"] = "PT";
  AxisVars["Psuedo Rapidity"] = "ETA";
  AxisVars["No. Best Tracks in Event"] = "nTRACKS";

  //arrange this vector such that the x variable is in position 1, y in position 2 etc.
  std::vector<std::string> theTrackVars;
  

  if (AxisVars[theHist->GetXaxis()->GetTitle()]=="") std::cout << "**ERROR** : Got invalid X bin type." << std::endl;
  else if (AxisVars[theHist->GetXaxis()->GetTitle()]=="nTRACKS")
    theTrackVars.push_back(VarMap[AxisVars[theHist->GetXaxis()->GetTitle()]]);
  else theTrackVars.push_back(trackName+"_"+VarMap[AxisVars[theHist->GetXaxis()->GetTitle()]]);

  if (theHist->GetDimension()>1){
    if (AxisVars[theHist->GetYaxis()->GetTitle()]=="") std::cout << "**ERROR** : Got invalid Y bin type." << std::endl;
    else if (AxisVars[theHist->GetYaxis()->GetTitle()]=="nTRACKS")
      theTrackVars.push_back(VarMap[AxisVars[theHist->GetYaxis()->GetTitle()]]);
    else theTrackVars.push_back(trackName+"_"+VarMap[AxisVars[theHist->GetYaxis()->GetTitle()]]);
  }
  if (theHist->GetDimension()>2){
     if (AxisVars[theHist->GetZaxis()->GetTitle()]=="") std::cout << "**ERROR** : Got invalid Z bin type." << std::endl;
     else if (AxisVars[theHist->GetZaxis()->GetTitle()]=="nTRACKS")
      theTrackVars.push_back(VarMap[AxisVars[theHist->GetZaxis()->GetTitle()]]);
    else theTrackVars.push_back(trackName+"_"+VarMap[AxisVars[theHist->GetZaxis()->GetTitle()]]);
  }
       
  return theTrackVars;
  
}

//this function takes a vector of branchnames and the tree.
//it returns a vector of vectors of floats.
//each entry corresponds to one entry in the tree.
//at each entry there is a vector of floats of the same size as
//"theNames" with the value of each variable in "theNames" (arranged in the same order)
//for this entry in the tree cast as a Float_t.
std::vector<std::vector<Float_t> > GetFloatValuesFromTree(std::vector<std::string> theNames,
                                                          TTree * theTree)
{

  std::vector<std::string> trackVarTypes;
  TString trackVarType;

  //check validity of branchnames in trackVars vector
  //and fill trackVarTypes
  for (std::vector<std::string>::iterator iter = theNames.begin();
       iter != theNames.end(); iter++){
    if (!validBranch(theTree,iter->c_str())) {
      std::cout << "**ERROR**: " << *iter << " does not name a valid branch"
                << std::endl;
      exit(EXIT_FAILURE);
    }
    trackVarType = getBranchType(theTree,iter->c_str());
    if (trackVarType.CompareTo("Int_t")!=0 &&
        trackVarType.CompareTo("Float_t")!=0 &&
        trackVarType.CompareTo("Double_t")!=0){
      std::cout << "ERROR: Got invalid branch type "
                << trackVarType << " for branch with name "
                << *iter << std::endl;
      exit(EXIT_FAILURE);
    }
    trackVarTypes.push_back((std::string)trackVarType);
  }


  std::vector<std::vector<Float_t> > theVars;
  std::vector<Float_t> tempvector;
  
  Int_t track_Var_i;
  Float_t track_Var;
  Double_t track_Var_d;

  for (UInt_t n = 0; n<theTree->GetEntries(); n++){
    for (uint i = 0; i < theNames.size(); i++){
      if(trackVarTypes.at(i)=="Int_t") theTree->SetBranchAddress(theNames.at(i).c_str(), &track_Var_i);
      else if(trackVarTypes.at(i)=="Float_t") theTree->SetBranchAddress(theNames.at(i).c_str(), &track_Var);
      else if(trackVarTypes.at(i)=="Double_t") theTree->SetBranchAddress(theNames.at(i).c_str(), &track_Var_d);
      theTree->GetEntry(n);
      if(trackVarTypes.at(i)=="Int_t") tempvector.push_back((Float_t)track_Var_i);
      else if(trackVarTypes.at(i)=="Float_t") tempvector.push_back((Float_t)track_Var);
      else if(trackVarTypes.at(i)=="Double_t") tempvector.push_back((Float_t)track_Var_d);
      theTree->ResetBranchAddresses();
    } 
    theVars.push_back(tempvector);
    tempvector.clear();
  }
  theTree->ResetBranchAddresses();
  return theVars;
}


//function that takes a histogram and a TTree and activates the PID eff and err
//branches, fills them and returns the tree
//ND version
TTree* addPIDEffBranchesND(TTree* inTree,
                           TDirectory* outFile,
                           TH1* theHist,
                           TString trackName,
                           TString PIDBranchName,//the prefix for PIDEff branches (in case there are 2 or more cuts on one track)
                           std::map<std::string,std::string> VarMap)
{
  if (!inTree) {
    std::cout << "ERROR: No signal TTree specified" << std::endl;
    return NULL;
  }
  if (!outFile) {
    std::cout << "ERROR: No output directory specified" << std::endl;
    return NULL;
  }
  if (!theHist) {
    std::cout << "ERROR: No track histogram found!" << std::endl;
    return NULL;
  }


  Int_t nDim = theHist->GetDimension();

  //Debugging    
//  std::cout << "X  " << theHist->GetXaxis()->GetTitle() << std::endl;
//  std::cout << "Y  " << theHist->GetYaxis()->GetTitle() << std::endl;
//  std::cout << "Z  " << theHist->GetZaxis()->GetTitle() << std::endl;

  //convert the axis titles of calibration histogram to branch names in the reference tree
  std::vector<std::string> branchNames = ParseAxes(theHist,VarMap,(std::string)trackName);

  std::vector<std::vector<Float_t> > branchValues = GetFloatValuesFromTree(branchNames,inTree);
  
  //Copy the header of inTree to new outTree
  outFile->cd();
  TTree *outTree = inTree->CloneTree(0);
  
  if (!outTree) {
    std::cout << "ERROR: Failed to clone input tree header" << std::endl;
    exit(EXIT_FAILURE);
  }
  
  outTree->SetName(inTree->GetName());

  //Initialising variables
  //track efficiency
  Float_t track_pidEff = -9999.9;

  // track efficiency error
  Float_t track_pidErr = -9999.9;

  //bin number in the calibration histogram
  Int_t track_binNumber = -1;
  

  /********* Activate PID Eff and Error Branches *********/
  TBranch * track_pidEffBranch = 0;
  track_pidEffBranch = outTree->Branch((PIDBranchName+"_PIDCalibEff").Data(),
                                       &track_pidEff, 
                                       (PIDBranchName+"_PIDCalibEff/F").Data());
  if (!track_pidEffBranch) {
    std::cout << "ERROR: Failed to create PID efficiency track branch"
              << std::endl;
    delete outTree;
    exit(EXIT_FAILURE);
  }

  TBranch * track_pidErrBranch = 0;
  track_pidErrBranch = outTree->Branch((PIDBranchName+"_PIDCalibEffError").Data(),
                                       &track_pidErr,
                                       (PIDBranchName+"_PIDCalibEffError/F").Data());                                       

  if (!track_pidErrBranch) {
    std::cout << "ERROR: Failed to create PID efficiency error track branch"
              << std::endl;
    delete outTree;
    exit(EXIT_FAILURE);
  }
  /*********************Activate Bin Number Branch**************/
  TBranch * track_binNumberBranch = 0;
  track_binNumberBranch = outTree->Branch((PIDBranchName+"_PIDCalibBinNumber").Data(),
                                          &track_binNumber,
                                          (PIDBranchName+"_PIDCalibBinNumber/I").Data());

  if (!track_binNumberBranch) {
    std::cout << "ERROR: Failed to create bin number track branch"
              << std::endl;
    delete outTree;
    exit(EXIT_FAILURE);
  }  
  

  //Loop over entries
  UInt_t nEntries = inTree->GetEntries();
  for(UInt_t i = 0; i<nEntries; i++)
  {

    inTree->GetEntry(i);
    
    //Get the global bin number of the historgram that this event lies in
    Int_t track_bin = -100;
    if (nDim==3) track_bin = theHist->FindBin(branchValues.at(i).at(0),
                                              branchValues.at(i).at(1),
                                              branchValues.at(i).at(2));
    else if (nDim==2) track_bin = theHist->FindBin(branchValues.at(i).at(0),
                                                   branchValues.at(i).at(1));
    else if (nDim==1) track_bin = theHist->FindBin(branchValues.at(i).at(0));
    //set the efficiency and error from this global bin number
    track_pidEff = theHist->GetBinContent(track_bin);
    track_pidErr = theHist->GetBinError(track_bin);
    track_binNumber = track_bin;
    
    //finding whether this is in an over or underflow bin
    Int_t nx = theHist->GetNbinsX(), ny = -100, nz = -100;
    if (nDim==2) ny = theHist->GetNbinsY();
    if (nDim==3) nz = theHist->GetNbinsZ();

    Int_t binx=-100,biny=-100,binz=-100;
    theHist->GetBinXYZ(track_bin,binx,biny,binz);

    //printing some warnings and setting efficiencies and errors to zero 
    //if anything weird happens
    //complex condition here because biny and binz are set to zero by GetBinXYZ if it is not a 3d histogram
    if ((nDim==3&&(binx==0||biny==0||binz==0))||
        (nDim==2&&(binx==0||biny==0))|| 
        (nDim==1&&(binx==0))) {
      std::cout << "WARNING: Track in underflow bin. "
                << "Please check the calibration histograms have been created properly."
                << std::endl;
      for (uint j = 0;j<branchNames.size(); j++){
        std::cout << branchNames.at(j)+" = " << branchValues.at(i).at(j) << std::endl;
      }
      track_pidEff = 0;
      track_pidErr = 0;      
      track_binNumber = -1;
    }
    else if (binx==(nx+1)||biny==(ny+1)||binz==(nz+1)) {
      std::cout << "WARNING: Track in overflow bin. "
                << "Please check the calibration histograms have been created properly"
                << std::endl;
      for (uint j = 0;j<branchNames.size(); j++){
        std::cout << branchNames.at(j)+" = " << branchValues.at(i).at(j) << std::endl;
      }     
      track_pidEff = 0;
      track_pidErr = 0;
      track_binNumber = -1;
    }
    else if (track_pidEff<0||track_pidEff>1) {
      std::cout << "Track efficiency (" 
                << std::setprecision(4) << 100.*track_pidEff << "%)" 
                << " in bin " << "(" 
                << binx-1 << "," << biny-1 << "," << binz-1 << ")"
                << " out of range here: " << std::endl;
      for (uint j = 0;j<branchNames.size(); j++){
        std::cout << branchNames.at(j)+" = " << branchValues.at(i).at(j) << std::endl;
      } 
      track_pidEff=0;
      track_pidErr=0;
      track_binNumber = -1;
    }
//    else if (track_pidErr==0) {
//      std::cout << "Track efficiency error "
//                << " in bin " << "(" << binx-1 << "," 
//                << biny-1 << "," << binz-1 << ") is zero here: " << std::endl;
//      for (uint j = 0;j<branchNames.size(); j++){
//        std::cout << branchNames.at(j)+" = " << branchValues.at(i).at(j) << std::endl;
//      }
//      std::cout << "Efficiency in this bin = " << track_pidEff << std::endl;
//      track_pidEff=0;
//      track_pidErr=0;
//      track_binNumber = -1;
//    }
    else if (track_pidEff==0) {
      std::cout << "Track efficiency "
                << " in bin " << "(" << binx-1 << "," 
                << biny-1 << "," << binz-1 << ") is zero here: " << std::endl;
      for (uint j = 0;j<branchNames.size(); j++){
        std::cout << branchNames.at(j)+" = " << branchValues.at(i).at(j) << std::endl;
      }
      track_pidEff=0;
      track_pidErr=0;
      track_binNumber = -1;
    }
    outTree->Fill();
  }
  
  // Reset branch addresses of new branches, since they will go
  // out of scope at the end of the function call
  outTree->ResetBranchAddresses();
  
  return outTree;  
}

//calculate cross terms of binomially propagated errors assuming that tracks of the same type
//are 100% correlated e.g. K+ and K- are 100% as are K+ and K+. charge doesn't matter
Float_t CrossTerms(std::vector<std::pair<Int_t,Float_t> > theErrors)
{

  Float_t xTerms = 0;

  //iterator used to make sure all possible pairs are checked with no double counting
  std::vector<std::pair<Int_t,Float_t> >::iterator marker = theErrors.begin()+1;

  for (std::vector<std::pair<Int_t,Float_t> >::iterator iter = theErrors.begin();
       iter != theErrors.end() && marker != theErrors.end(); iter++, marker++){
    //std::cout << "Correlation coefficients for particle " << distance(theErrors.begin(),iter) << ":" << std::endl;
    for (std::vector<std::pair<Int_t,Float_t> >::iterator iter2 = marker;
         iter2 != theErrors.end(); iter2++){
      //same type? if so times by 1, if not 0.
      xTerms += 2*(abs(iter->first)==abs(iter2->first))*iter->second*iter2->second;
      //std::cout << " particle " << distance(theErrors.begin(),iter2) << ": ";
      //std::cout << (iter->first==iter2->first) << std::endl;
    }
  }
  //std::cout << "xTerms = "<< xTerms << std::endl;
  return xTerms;

}



//making total event weights
std::vector<std::pair<Float_t,Float_t> > MakeEventWeights(TTree * inTree,
                                                          std::string PDG_ID,
                                                          std::vector<std::string> Tracks,
                                                          std::vector<std::string> PIDNames)
{
  std::vector<std::pair<Float_t,Float_t> > outVector;
  if (!inTree) {
    std::cout << "ERROR: No signal TTree specified" << std::endl;
    return outVector;
  }
  
  //Initialising variables
  //Event efficiency
  Float_t event_pidEff;

  //Event efficiency error
  Float_t event_pidErr;

  //track parameters used in the calculation of total event weights and their errors  
  Float_t track_pidEff;
  Float_t track_pidErr;

  //track pdg id
  Int_t track_pdg_id;

  //Loop over entries
  UInt_t nEntries = inTree->GetEntries();
  std::vector<std::pair<Float_t,Float_t> > EventEfficiencies;
  std::vector<std::pair<Int_t,Float_t> > IDs_And_Errors;
  Float_t ErrorOverEff;
  //fill vectors with all the relevant numbers
  
  typedef std::vector<std::string>::iterator striter;
  
  for(UInt_t i = 0; i<nEntries; i++)
  {
    event_pidEff = 1;
    event_pidErr = 0;
    for (std::pair<striter,striter> iterpair(Tracks.begin(), PIDNames.begin());
         iterpair.first != Tracks.end() && iterpair.second != PIDNames.end(); ++iterpair.first, ++iterpair.second){

      inTree->SetBranchAddress(((*iterpair.first)+"_"+PDG_ID).c_str(), &track_pdg_id);
      inTree->SetBranchAddress(((*iterpair.second)+"_PIDCalibEff").c_str(), &track_pidEff);
      inTree->SetBranchAddress(((*iterpair.second)+"_PIDCalibEffError").c_str(), &track_pidErr);
      inTree->GetEntry(i);
      event_pidEff *= track_pidEff;

      //prevent NaN being recorded as fractional error on an efficiency
      if(track_pidErr==0||track_pidEff==0) ErrorOverEff = 0;
      else ErrorOverEff = track_pidErr/track_pidEff;

      event_pidErr += pow(ErrorOverEff,2);
      IDs_And_Errors.push_back(std::pair<Int_t,Float_t> (track_pdg_id,ErrorOverEff));
      inTree->ResetBranchAddresses();
    }
    
    //just propagating the errors binomially at the moment    
    event_pidErr = event_pidEff*sqrt(event_pidErr + CrossTerms(IDs_And_Errors));
    IDs_And_Errors.clear();
    

    if (event_pidEff<0||event_pidEff>1) {
      std::cout << "WARNING : Event efficiency (" 
                << std::setprecision(4) << 100.*event_pidEff << "%)" 
                << std::endl;
      event_pidEff=0;
      event_pidErr=0;
    }
//    else if (event_pidErr==0) {
//      std::cout << "WARNING : Event efficiency error is zero."
//                << std::endl; 
//      event_pidEff=0;
//      event_pidErr=0;
//    }
    else if (event_pidEff==0) {
      std::cout << "WARNING : Event efficiency is zero."
                << std::endl; 
      event_pidEff=0;
      event_pidErr=0;
    }
    EventEfficiencies.push_back(std::pair <Float_t,Float_t> (event_pidEff,event_pidErr));
  }
  inTree->ResetBranchAddresses();
  
  return EventEfficiencies;  
 
}

TTree * addEventWeightsToTree(TTree * inTree,
                              TDirectory* outFile,
                              std::string PDG_ID,
                              std::vector<std::string> Tracks,
                              std::vector<std::string> PIDNames)
{

  if (!inTree) {
    std::cout << "ERROR: No signal TTree specified" << std::endl;
    return NULL;
  }
  if (!outFile) {
    std::cout << "ERROR: No output directory specified" << std::endl;
    return NULL;
  }

  //get the vector of event weights and errors
  std::vector<std::pair<Float_t,Float_t> > efficiencies = MakeEventWeights(inTree,PDG_ID,Tracks,PIDNames);
  std::cout << "Made Weights" << std::endl;
  
  //Copy the header of inTree to new outTree
  outFile->cd();
  TTree *outTree = inTree->CloneTree(0);
  
  if (!outTree) {
    std::cout << "ERROR: Failed to clone input tree header" << std::endl;
    return NULL;
  }
  outTree->SetName(inTree->GetName());
  
  //Initialising variables
  //event efficiency
  Float_t event_pidEff = -9999.9;

  //event efficiency error
  Float_t event_pidErr = -9999.9;
  
  /********* Activate PID Eff and Error Branches *********/
  TBranch * event_pidEffBranch = 0;
  event_pidEffBranch = outTree->Branch("Event_PIDCalibEff",
                                       &event_pidEff,
                                       "Event_PIDCalibEff/F");
  if (!event_pidEffBranch) {
    std::cout << "ERROR: Failed to create PID efficiency event branch"
              << std::endl;
    delete outTree;
    return NULL;
  }

  TBranch * event_pidErrBranch = 0;
  event_pidErrBranch = outTree->Branch("Event_PIDCalibEffError",
                                       &event_pidErr,
                                       "Event_PIDCalibEffError/F");                                       

  if (!event_pidErrBranch) {
    std::cout << "ERROR: Failed to create PID efficiency error event branch"
              << std::endl;
    delete outTree;
    return NULL;
  }
  
  //Loop over entries
  UInt_t nEntries = inTree->GetEntries();  
  
  for(UInt_t i = 0; i<nEntries; i++)
  {
    inTree->GetEntry(i);
    event_pidEff = efficiencies.at(i).first;
    event_pidErr = efficiencies.at(i).second;
    
    outTree->Fill();
  }
  
  // Reset branch addresses of new branches, since they will go
  // out of scope at the end of the function call
  outTree->ResetBranchAddresses();
  
  return outTree;  

}

//Calculating the average Event PID Efficiency
std::pair<double,double> AveragePIDEfficiency(TTree * theTree)
{

  UInt_t nEntries = theTree->GetEntries();

  Int_t goodEvents = 0;
  Float_t event_pidEff;
  Float_t event_pidErr;
  Float_t EfficiencySum = 0;
  Float_t EfficiencyErrorSum = 0;
  theTree->SetBranchAddress("Event_PIDCalibEff",&event_pidEff);
  theTree->SetBranchAddress("Event_PIDCalibEffError",&event_pidErr);

  for (uint i = 0; i<nEntries; i++){
    theTree->GetEntry(i);
    //is the efficiency and error between 0 and 1?
    if (event_pidEff>0&&event_pidEff<=1&&event_pidErr>=0){
      goodEvents++;
      EfficiencySum += event_pidEff;
      EfficiencyErrorSum += pow(event_pidErr,2);
    }
    
  }
  Float_t MeanEff = ((double)EfficiencySum)/((double)goodEvents);
  Float_t MeanEffError = sqrt((double)EfficiencyErrorSum)/((double)goodEvents);
  
  std::cout << "------Mean Event PID Efficiency------" << std::endl;
  std::cout << MeanEff << " +- " << MeanEffError << std::endl;
  std::cout << "-------------------------------------" << std::endl;
  
  theTree->ResetBranchAddresses();
  return std::pair<double,double> (MeanEff,MeanEffError);
}


//======================================================================
// Make the plots of the residual between MCSig_Effs and MCCal_Effs,
// the sum of these, the ratio of residual over sum and the corrected 
// residual (the ratio of residual to sum multiplied by DataCal_Effs).
//======================================================================
void SystematicPlots(std::vector<std::pair<double,double> > MCSig_Effs,
                     std::vector<std::pair<double,double> > MCCal_Effs,
                     std::vector<std::pair<double,double> > DataCal_Effs,
                     std::vector<double> DLLs,
                     std::string outputFileName)
{
 
  uint vecsize = MCSig_Effs.size();
  if (MCCal_Effs.size()!=vecsize||
      DataCal_Effs.size()!=vecsize||
      DLLs.size()!=vecsize){
    std::cout << "Number of points for systematic graphs not equal!" << std::endl;
    return;
  }

  //======================================================================
  // Construct TGraphAsymmErrors of the difference between MCSig_Effs
  // and MCCal_Effs
  //======================================================================
  const Int_t numpoints = (Int_t)vecsize;
  
  double* resDLL = new double[numpoints];
  double* resY = new double[numpoints];
  double* resY_err_lo = new double[numpoints];
  double* resY_err_hi = new double[numpoints];
  double* resDLLl = new double[numpoints];
  double* resDLLh = new double[numpoints];
  
  for (int i = 0; i < numpoints; i++)
  {
    double y_cal = 0, y_sig = 0;
    y_cal = MCCal_Effs.at(i).first;
    y_sig = MCSig_Effs.at(i).first;
    
    resDLL[i] = DLLs.at(i);
    resY[i] = y_sig - y_cal;
    resDLLl[i] = 0.5;
    resDLLh[i] = 0.5;
    resY_err_lo[i] = sqrt( pow(MCCal_Effs.at(i).second,2) + 
                           pow(MCSig_Effs.at(i).second,2));
    resY_err_hi[i] = sqrt(  pow(MCCal_Effs.at(i).second,2) + 
                            pow(MCSig_Effs.at(i).second,2));
  }
  
  TGraphAsymmErrors* resplot = new TGraphAsymmErrors(numpoints,
                                                     resDLL,
                                                     resY,
                                                     resDLLl,
                                                     resDLLh,
                                                     resY_err_lo,
                                                     resY_err_hi);
  
  resplot->SetTitle("title;DLL(K - #pi);#epsilon^{SIGNAL} - #epsilon^{CALIB}");
  resplot->SetName("Residual");

  delete resDLL;
  delete resY;
  delete resY_err_lo;
  delete resY_err_hi;
  delete resDLLl;
  delete resDLLh;

  //======================================================================
  // Construct TGraphAsymmErrors of the sum of MCSig_Effs and 
  // MCCal_Effs
  //======================================================================
  double* sumDLL = new double[numpoints];
  double* sumY = new double[numpoints];
  double* sumY_err_lo = new double[numpoints];
  double* sumY_err_hi = new double[numpoints];
  double* sumDLLl = new double[numpoints];
  double* sumDLLh = new double[numpoints];
  
  for (int i = 0; i < numpoints; i++)
  {
    double y_cal = 0, y_sig = 0;
    y_cal = MCCal_Effs.at(i).first;
    y_sig = MCSig_Effs.at(i).first;
    
    sumDLL[i] = DLLs.at(i);
    sumY[i] = y_sig + y_cal;
    sumDLLl[i] = 0.5;
    sumDLLh[i] = 0.5;
    sumY_err_lo[i] = sqrt( pow(MCCal_Effs.at(i).second,2) + 
                           pow(MCSig_Effs.at(i).second,2));
    sumY_err_hi[i] = sqrt(  pow(MCCal_Effs.at(i).second,2) + 
                            pow(MCSig_Effs.at(i).second,2));

  }
  
  TGraphAsymmErrors* sumplot = new TGraphAsymmErrors(numpoints,
                                                     sumDLL,
                                                     sumY,
                                                     sumDLLl,
                                                     sumDLLh,
                                                     sumY_err_lo,
                                                     sumY_err_hi);
  
  sumplot->SetTitle("title;DLL(K - #pi);#epsilon^{SIGNAL} + #epsilon^{CALIB}");
  sumplot->SetName("Sum");

  delete sumDLL;
  delete sumY;
  delete sumY_err_lo;
  delete sumY_err_hi;
  delete sumDLLl;
  delete sumDLLh;

  //======================================================================
  // Construct TGraphAsymmErrors of the ratio of resplot and sumplot
  //======================================================================
  double* ratioDLL = new double[numpoints];
  double* ratioY = new double[numpoints];
  double* ratioY_err_lo = new double[numpoints];
  double* ratioY_err_hi = new double[numpoints];
  double* ratioDLLl = new double[numpoints];
  double* ratioDLLh = new double[numpoints];
  
  for (int i = 0; i < numpoints; i++)
  {
    double x_res = 0, x_sum = 0;
    double y_res = 0, y_sum = 0;
    resplot->GetPoint(i, x_res, y_res);
    sumplot->GetPoint(i, x_sum, y_sum);
    ratioDLL[i] = x_res;
    ratioY[i] = y_res/y_sum;
    ratioDLLl[i] = 0.5;
    ratioDLLh[i] = 0.5;
    ratioY_err_lo[i] = fabs(y_res/y_sum)*sqrt( pow((resplot->GetErrorYlow(i)/y_res), 2) + 
                                               pow((sumplot->GetErrorYlow(i)/y_sum), 2) + 
                                               ((2*resplot->GetErrorYlow(i)*sumplot->GetErrorYlow(i))/(y_res*y_sum))
                                               );
    ratioY_err_hi[i] = fabs(y_res/y_sum)*sqrt( pow((resplot->GetErrorYhigh(i)/y_res), 2) + 
                                               pow((sumplot->GetErrorYhigh(i)/y_sum), 2) + 
                                               ((2*resplot->GetErrorYlow(i)*sumplot->GetErrorYlow(i))/(y_res*y_sum))
                                               );
    std::cout<<x_res<<'\t'<<ratioY_err_lo[i]<<'\t'<<ratioY_err_hi[i]<<std::endl;
  }
  
  TGraphAsymmErrors* ratioplot = new TGraphAsymmErrors(numpoints,
                                                       ratioDLL,
                                                       ratioY,
                                                       ratioDLLl,
                                                       ratioDLLh,
                                                       ratioY_err_lo,
                                                       ratioY_err_hi);
  
  ratioplot->SetTitle("title;DLL(K - #pi);residule/sum");
  ratioplot->SetName("Ratio");

  delete ratioDLL;
  delete ratioY;
  delete ratioY_err_lo;
  delete ratioY_err_hi;
  delete ratioDLLl;
  delete ratioDLLh;

  //======================================================================
  // Construct TGraphAsymmErrors of the product of ratioplot and 
  // DataCal_Effs
  //======================================================================
  double* prodDLL = new double[numpoints];
  double* prodY = new double[numpoints];
  double* prodY_err_lo = new double[numpoints];
  double* prodY_err_hi = new double[numpoints];
  double* prodDLLl = new double[numpoints];
  double* prodDLLh = new double[numpoints];
  
  for (int i = 0; i < numpoints; i++)
  {
    double x_ratio = 0;
    double y_ratio = 0, y_eff = 0;
    ratioplot->GetPoint(i, x_ratio, y_ratio);
    y_eff = DataCal_Effs.at(i).first;

    prodDLL[i] = x_ratio;
    prodY[i] = y_ratio*y_eff;
    prodDLLl[i] = 0.5;
    prodDLLh[i] = 0.5;
    prodY_err_lo[i] = fabs(y_ratio*y_eff)*sqrt( pow((ratioplot->GetErrorYlow(i)/y_ratio), 2) + 
                                                  pow((DataCal_Effs.at(i).second/y_eff), 2));
    prodY_err_hi[i] = fabs(y_ratio*y_eff)*sqrt( pow((ratioplot->GetErrorYhigh(i)/y_ratio), 2) + 
                                                  pow((DataCal_Effs.at(i).second/y_eff), 2));
  }
  
  TGraphAsymmErrors* prodplot = new TGraphAsymmErrors(numpoints,
                                                       prodDLL,
                                                       prodY,
                                                       prodDLLl,
                                                       prodDLLh,
                                                       prodY_err_lo,
                                                       prodY_err_hi);
  
  prodplot->SetTitle("title;DLL(K - #pi);Corrected Residual");
  prodplot->SetMarkerStyle(8);
  prodplot->GetYaxis()->SetTitleOffset(1.2);
  prodplot->GetYaxis()->SetRangeUser(-0.015,0.015);
  prodplot->GetXaxis()->SetRangeUser(-12.0,22.0);
  prodplot->SetName("Prod");

  //======================================================================
  // Find the Maximum in the prodplot (largest excursion from zero) and 
  // print this. Also print the value of prodplot at the cut in question.
  //======================================================================
  double maxSyst = fabs(prodY[0]);
  double maxSystPosition = prodDLL[0];
  
  for (int i = 0; i < numpoints; i++)
  {
    if (fabs(prodY[i])>=maxSyst){
      maxSyst = fabs(prodY[i]);
      maxSystPosition = prodDLL[i];
    }
  }
  std::cout << "The Maximum systematic over the whole range is " << maxSyst << " and this occurs "
            << "at a cut of " << maxSystPosition << "." << std::endl;
  //======================================================================

  delete prodDLL;
  delete prodY;
  delete prodY_err_lo;
  delete prodY_err_hi;
  delete prodDLLl;
  delete prodDLLh;
  
  //======================================================================
  // Save graphs to file
  //======================================================================
  TFile *myfile = new TFile(outputFileName.c_str(),"recreate");
  resplot->Write();
  sumplot->Write();
  ratioplot->Write();
  prodplot->Write();

  myfile->Close();

  //======================================================================
  // Clean up
  //======================================================================
  delete resplot;
  delete sumplot;
  delete ratioplot;
  delete prodplot;
  
  delete myfile;
  
}

