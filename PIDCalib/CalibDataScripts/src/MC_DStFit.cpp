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
#include "CalibDataScripts/MC_DStFit.h"
#include "CalibDataScripts/GetData.h"

// Namespaces
using namespace RooPhysFit;
using std::cout;
using std::endl;

//-----------------------------------------
// Example usage:
// $CMTCONFIG/MC_DStFit.exe 1000 K Up MC10
//-----------------------------------------

int main(int argc, char *argv[])
{
  //---------------------------------------------------//
  // argv parameters:
  // 1: Ganga job ID 
  // 2: Particle Name in nTulpe
  // 3: Field Orientation (Up or Down)
  // 4: Stripping version
  // With possible additional parameters:
  // 5: Min subjob ID
  // 6: Max subjob ID
  //---------------------------------------------------//
  if (!(argc==5 || argc==7))
  {
    cout<<"Invalid number of arguments passed: "<<argc<<endl;
    return EXIT_FAILURE;
  }
  //---------------------------------------------------//
  
  TTree* t = NULL;
  TString path = "$DATADISK/gangadir_calib/workspace/powell/LocalXML/";
  
  //---------------------------------------------------//
  // If only 5 arguments are passed, then run over one
  // TTree
  //---------------------------------------------------//
  if(argc == 5)
  {
    GetData(t,
            path, 
            argv[1],
            "RICH_Modes.root",
            "DSt2D0Pi_D02RSKPiTuple/CalibPID");
  }
  //---------------------------------------------------//
  // If 7 arguments passed, then run over set of TTrees
  // specified in the given subjob range 
  //---------------------------------------------------//
  else
  {
    GetData(t,
            path, 
            argv[1],
            atoi(argv[5]),
            atoi(argv[6]),
            "RICH_Modes.root",
            "DSt2D0Pi_D02RSKPiTuple/CalibPID");
  }
  
  if(t==NULL)
  {
    cout<<"TTree pointer is NULL"<<endl;
    return EXIT_FAILURE;
  }

  //---------------------------------------------------//
  // Specfiy list of variables to be included in dataset 
  //---------------------------------------------------//
  std::vector<fptr> fun_vec;
  fun_vec.push_back(SetSpecVars_MCEvtVars2011);
  fun_vec.push_back(SetSpecVars_StdDLLs2011);
  fun_vec.push_back(SetSpecVars_NeuroBayesVars);
  fun_vec.push_back(SetSpecVars_KinematicVars);
  fun_vec.push_back(SetSpecVars_MuonVars);
  //fun_vec.push_back(SetSpecVars_RadRadius);
  //fun_vec.push_back(SetSpecVars_Categories);
  
  //---------------------------------------------------//
  // Fit -ve tracks 
  //---------------------------------------------------//
  DStFit(t,
         "Negative",
         argv[2],
         "RSDStCalib",
         TString::Format("DSt_%sMinus_Mag%s_%s.root",
                         argv[2],
                         argv[3],
                         argv[4]).Data(),
         "data_wSWeights",
         "mass",
         "delm",
         fun_vec);
  
  delete t;
  t = NULL;
  
  //---------------------------------------------------//
  // If only 5 arguments are passed, then run over one
  // TTree
  //---------------------------------------------------//
  if(argc == 5)
  {
    GetData(t,
            path, 
            argv[1],
            "RICH_Modes.root",
            "DSt2D0Pi_D02RSKPiTuple/CalibPID");
  }
  //---------------------------------------------------//
  // If 7 arguments passed, then run over set of TTrees
  // specified in the given subjob range 
  //---------------------------------------------------//
  else
  {
    GetData(t,
            path, 
            argv[1],
            atoi(argv[5]),
            atoi(argv[6]),
            "RICH_Modes.root",
            "DSt2D0Pi_D02RSKPiTuple/CalibPID");
  }
  
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
         argv[2],
         "RSDStCalib",
         TString::Format("DSt_%sPlus_Mag%s_%s.root",
                         argv[2],
                         argv[3],
                         argv[4]).Data(),
         "data_wSWeights",
         "mass",
         "delm",
         fun_vec);

  delete t;

  return EXIT_SUCCESS;
}




