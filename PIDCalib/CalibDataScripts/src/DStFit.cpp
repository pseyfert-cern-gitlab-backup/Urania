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
#include "CalibDataScripts/DStFit.h"
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
  
  //---------------------------------------------------//
  // Get data
  //---------------------------------------------------//
  TTree* t = NULL;
  GetData(t,
          inputFiles,
          "DSt2D0Pi_D02RSKPiTuple/CalibPID");
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
  //fun_vec.push_back(SetSpecVars_MUONCategories);
  
  //---------------------------------------------------//
  // Fit -ve tracks 
  //---------------------------------------------------//
  DStFit(t,
         "Negative",
         argv[1],
         "RSDStCalib",
         TString::Format("%s/DSt_%sMinus_Mag%s_Strip%s_%s.root",
                         argv[5],
                         argv[1],
                         argv[2],
                         argv[3],
                         argv[4]).Data(),
         "data",
         "mass",
         "delm",
         fun_vec,
         argv[4]);
  
  //---------------------------------------------------//
  // Get data (again!)
  //---------------------------------------------------//
  //delete t;
  t = NULL;
  GetData(t,
          inputFiles,
          "DSt2D0Pi_D02RSKPiTuple/CalibPID");
  
  if(t==NULL)
  {
    cout<<"TTree pointer is NULL"<<endl;
    return EXIT_FAILURE;
  }
  
  //---------------------------------------------------//
  // Fit +ve tracks 
  //---------------------------------------------------//
  DStFit(t,
         "Positive",
         argv[1],
         "RSDStCalib",
         TString::Format("%s/DSt_%sPlus_Mag%s_Strip%s_%s.root",
                         argv[5],
                         argv[1],
                         argv[2],
                         argv[3],
                         argv[4]).Data(),
         "data",
         "mass",
         "delm",
         fun_vec,
         argv[4]);

  //delete t;

  return EXIT_SUCCESS;
}




