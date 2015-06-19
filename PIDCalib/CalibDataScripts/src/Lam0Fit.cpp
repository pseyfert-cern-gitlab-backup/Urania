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
#include "CalibDataScripts/Lam0Fit.h"
#include "CalibDataScripts/GetData.h"

// Namespaces
using namespace RooPhysFit;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
  //---------------------------------------------------//
  // argv parameters:
  // 1: Particle Name in nTulpe
  // 2: Field Orientation (Up or Down)
  // 3: Stripping version
  // 4: Subset index
  // 5: Output directory
  // 6: File(s) to run over
  //---------------------------------------------------//
  if (!argc>6)
  {
    cout<<"!Invalid number of arguments passed: "<<argc<<endl;
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
  
  TTree* t_lo = NULL;
  TTree* t_hi = NULL;
  
  //---------------------------------------------------//
  // Get data
  //---------------------------------------------------//
  GetData(t_lo,
          inputFiles,
          "Lam02PPi_LoPTuple/CalibPID");
  if(t_lo==NULL)
  {
    cout<<"TTree t_lo pointer is NULL"<<endl;
    return EXIT_FAILURE;
  }
  
  GetData(t_hi,
          inputFiles,
          "Lam02PPi_HiPTuple/CalibPID");
  if(t_hi==NULL)
  {
    cout<<"TTree t_hi pointer is NULL"<<endl;
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
  
  //---------------------------------------------------//
  // Fit -ve, Low P tracks 
  //---------------------------------------------------//
  Lam0Fit(t_lo,
          "Negative",
          "LoP",
          argv[1],
          "Lam0Calib",
          TString::Format("%s/Lam0_%sMinus_LoP_Mag%s_Strip%s_%s.root",
                          argv[5],
                          argv[1],
                          argv[2],
                          argv[3],
                          argv[4]).Data(),
          "data",
          "mass",
          fun_vec,
          argv[4]);

  //---------------------------------------------------//
  // Fit -ve, High P tracks 
  //---------------------------------------------------//
  Lam0Fit(t_hi,
          "Negative",
          "HiP",
          argv[1],
          "Lam0Calib",
          TString::Format("%s/Lam0_%sMinus_HiP_Mag%s_Strip%s_%s.root",
                          argv[5],
                          argv[1],
                          argv[2],
                          argv[3],
                          argv[4]).Data(),
          "data",
          "mass",
          fun_vec,
          argv[4]);
  
  //delete t_lo;
  //delete t_hi;
  //t_lo = NULL;
  //t_hi = NULL;
  
  //---------------------------------------------------//
  // Get data (again!)
  //---------------------------------------------------//
  GetData(t_lo,
          inputFiles,
          "Lam02PPi_LoPTuple/CalibPID");
  if(t_lo==NULL)
  {
    cout<<"TTree t_lo pointer is NULL"<<endl;
    return EXIT_FAILURE;
  }

  GetData(t_hi,
          inputFiles,
          "Lam02PPi_HiPTuple/CalibPID");
  if(t_hi==NULL)
  {
    cout<<"TTree t_lo pointer is NULL"<<endl;
    return EXIT_FAILURE;
  }

  //---------------------------------------------------//
  // Fit +ve, Low P tracks 
  //---------------------------------------------------//
  Lam0Fit(t_lo,
          "Positive",
          "LoP",
          argv[1],
          "Lam0Calib",
          TString::Format("%s/Lam0_%sPlus_LoP_Mag%s_Strip%s_%s.root",
                          argv[5],
                          argv[1],
                          argv[2],
                          argv[3],
                          argv[4]).Data(),
          "data",
          "mass",
          fun_vec,
          argv[4]);
  

  //---------------------------------------------------//
  // Fit +ve, High P tracks 
  //---------------------------------------------------//
  Lam0Fit(t_hi,
          "Positive",
          "HiP",
          argv[1],
          "Lam0Calib",
          TString::Format("%s/Lam0_%sPlus_HiP_Mag%s_Strip%s_%s.root",
                          argv[5],
                          argv[1],
                          argv[2],
                          argv[3],
                          argv[4]).Data(),
          "data",
          "mass",
          fun_vec,
          argv[4]);

  //delete t_lo;
  //delete t_hi;
  
  return EXIT_SUCCESS;
}




