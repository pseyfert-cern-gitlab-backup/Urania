// $Id: $
// Include files
#include "TChain.h"
#include "TCanvas.h"
#include "RooRealVar.h"
#include "RooPlot.h"
#include <vector>
#include <stdlib.h>

// Include files (local)
#include "CalibDataScripts/SetSpectatorVars.h"
#include "CalibDataScripts/JpsiFit.h"
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
  if (!argc>5)
  {
    cout<<"!Invalid number of arguments passed: "<<argc<<endl;
    return EXIT_FAILURE;
  }
  //---------------------------------------------------//
  
  //---------------------------------------------------//
  // Pass input files into vector 
  //---------------------------------------------------//
  std::vector<const char*> inputFiles;
  for (unsigned int i = 5; i < (unsigned int)argc; ++i) 
  {
    inputFiles.push_back(argv[i]);
  }
  
  //---------------------------------------------------//
  // Get data
  //---------------------------------------------------//
  TTree* t = NULL;
  GetData(t,
          inputFiles,
          "JpsiFromBNoPIDNoMipTuple/CalibPID");
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
  //fun_vec.push_back(SetSpecVars_MOUNCategories);
  
  //---------------------------------------------------//
  // Fit -ve tracks 
  //---------------------------------------------------//
  JpsiFit(t,
         "Negative",
         "Mu0",
         "Mu1",
         "JpsiCalib",
         TString::Format("%s/Jpsi_MuMinus_Mag%s_Strip%s_%s.root",
                         argv[4],
                         argv[1],
                         argv[2],
                         argv[3]).Data(),
         "data",
         "mass",
         fun_vec,
         argv[3]);
  
  //---------------------------------------------------//
  // Get data (again!)
  //---------------------------------------------------//
  //delete t;
  t = NULL;
  GetData(t,
          inputFiles,
          "JpsiFromBNoPIDNoMipTuple/CalibPID");

  if(t==NULL)
  {
    cout<<"TTree pointer is NULL"<<endl;
    return EXIT_FAILURE;  
  }

  //---------------------------------------------------//
  // Fit +ve tracks 
  //---------------------------------------------------//
  JpsiFit(t,
         "Positive",
         "Mu1",
         "Mu0",
         "JpsiCalib",
         TString::Format("%s/Jpsi_MuPlus_Mag%s_Strip%s_%s.root",
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




