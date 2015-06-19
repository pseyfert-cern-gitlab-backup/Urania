// $Id: $
// Include files
#include "TFile.h"
#include "TChain.h"
#include "TCanvas.h"
#include "RooRealVar.h"
#include "RooPlot.h"
#include <vector>

// Include files (local)
#include "CalibDataScripts/SetSpectatorVars.h"
#include "CalibDataScripts/K0SFit.h"
#include "CalibDataScripts/GetData.h"

// Namespaces
using namespace RooPhysFit;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
  //---------------------------------------------------//
  // argv parameters:
  // 1: Field Orientation (Up or Down)
  // 2: Stripping version
  // 3: Subset index
  // 4: Output directory
  // 5: File(s) to run over
  //---------------------------------------------------//
  if (!argc>5) 
  {
    cout<<"Invalid number of arguments passed: "<<argc<<endl;
    return EXIT_FAILURE;
  }
  //---------------------------------------------------//
  
  //---------------------------------------------------//
  // Pass input files into vector 
  //---------------------------------------------------//
  std::vector<const char*> inputFiles;
  for (unsigned int i = 6; i < (unsigned int)argc; ++i) 
  {
    inputFiles.push_back(argv[i]);
  }

  //---------------------------------------------------//
  // Get data
  //---------------------------------------------------//
  TTree* t = NULL;
  GetData(t,
          inputFiles,
          "K0S2PiPiTuple/CalibPID");
  
  if(t==NULL)
  {
    cout<<"TTree pointer is NULL"<<endl;
    return EXIT_FAILURE;
  }
  
  //---------------------------------------------------//
  // Specfiy list of variables to be included in dataset 
  //---------------------------------------------------//
  std::vector<fptr> fun_vec;
  fun_vec.push_back(SetSpecVars_EvtVars2012);
  fun_vec.push_back(SetSpecVars_StdDLLs2011);
  fun_vec.push_back(SetSpecVars_NeuroBayesVars);
  fun_vec.push_back(SetSpecVars_KinematicVars);
  fun_vec.push_back(SetSpecVars_MuonVars);
  //fun_vec.push_back(SetSpecVars_RICHCategories);
  //fun_vec.push_back(SetSpecVars_MuonCategories);
  
  K0SFit(t,
         "Negative",
         "Pi0",
         "K0SCalib",
         TString::Format("%s/K0S_PiMinus_Mag%s_Strip%s_%s.root",
                         argv[4],
                         argv[1],
                         argv[2],
                         argv[3]).Data(),
         "data",
         "mass",
         fun_vec,
         argv[3]);
  
  //delete t;
  //t = NULL;
  
  //---------------------------------------------------//
  // Get data (again!)
  //---------------------------------------------------//
  GetData(t,
          inputFiles,
          "K0S2PiPiTuple/CalibPID");
  
  if(t==NULL)
  {
    cout<<"TTree pointer is NULL"<<endl;
    return EXIT_FAILURE;
  }

  K0SFit(t,
         "Positive",
         "Pi1",
         "K0SCalib",
         TString::Format("%s/K0S_PiPlus_Mag%s_Strip%s_%s.root",
                         argv[4],
                         argv[1],
                         argv[2],
                         argv[3]).Data(),
         "data",
         "mass",
         fun_vec,
         argv[3]);

  //delete t;

  return EXIT_SUCCESS;
}
