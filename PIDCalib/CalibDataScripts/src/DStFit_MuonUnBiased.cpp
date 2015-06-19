// $Id: $
// Include files
#include <map>
#include <cstdlib>
 
#include "TString.h"
#include "TChain.h"
#include "TCanvas.h"
#include "RooRealVar.h"
#include "RooPlot.h"
#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

// Include files (local)
#include "CalibDataScripts/SetSpectatorVars.h"
#include "CalibDataScripts/DStFit_MuonUnBiased.h"
#include "CalibDataScripts/GetData.h"

// Namespaces
namespace bass=boost::assign;
using std::cout;
using std::endl;

// typedefs
typedef std::map<TString,TString> ssMap;

ssMap charges = bass::map_list_of("Negative", "Minus")("Positive", "Plus");
const char* wsName="RSDStCalib";
const char* dsName="data";
const char* d0MassName="mass";
const char* deltaMassName="delm";
const char* tupleName="CalibPID";

int main(int argc, char *argv[])
{
  //---------------------------------------------------//
  // argv parameters:
  // 1: Particle Name in nTulpe
  // 2: Field Orientation (Up or Down)
  // 3: Stripping version
  // 4: Datatype (e.g. '2011' or '2012')
  // 5: Subset index
  // 6: Output directory
  // 7: Print entries flag (1=print entries, 0=don't print entries)
  // 8: File(s) to run over
  if (!argc>8)
  {
    cout<<"Invalid number of arguments passed: "<<argc<<endl;
    return EXIT_FAILURE;
  }
  //---------------------------------------------------//
  
  const char* pName=argv[1];
  const char* magPol=argv[2];
  const char* stripVersion=argv[3];
  const char* DataType=argv[4];
  const char* index=argv[5];
  const char* outDir=argv[6];
  Bool_t printEntries = boost::lexical_cast<Bool_t>(argv[7]);
  
  //---------------------------------------------------//
  // Pass input files into vector 
  //---------------------------------------------------//
  std::vector<const char*> inputFiles;
  for (unsigned int i = 8; i < (unsigned int)argc; ++i) 
  {
    inputFiles.push_back(argv[i]);
  }
  
  //---------------------------------------------------//
  // Specfiy list of variables to be included in dataset 
  //---------------------------------------------------//
  std::vector<fptr> fun_vec;
  if (strcmp(DataType,"2012")==0) fun_vec.push_back(SetSpecVars_EvtVars2012);
  else if (strcmp(DataType,"2011")==0) fun_vec.push_back(SetSpecVars_EvtVars2011);
  else {
    cout << "Invalid DataType " << DataType << endl;
    return EXIT_FAILURE;
  }
  fun_vec.push_back(SetSpecVars_StdDLLs2011);
  fun_vec.push_back(SetSpecVars_NeuroBayesVars);
  fun_vec.push_back(SetSpecVars_KinematicVars);
  fun_vec.push_back(SetSpecVars_MuonVars);
  //fun_vec.push_back(SetSpecVars_RICHCategories);
  //fun_vec.push_back(SetSpecVars_MUONCategories);

  //---------------------------------------------------//
  // Fit -ve and +ve tracks 
  //---------------------------------------------------//
  TString fname;
  TString tupleFullName=TString::Format("DSt2D0Pi_D02RSKPiTuple/%s", tupleName);
  TTree* t = NULL;
  BOOST_FOREACH(const ssMap::value_type& charge, charges) {
    //---------------------------------------------------//
    // Get data
    //---------------------------------------------------//
    // It'd be better if GetData took a enum that specified the calibration sample
    // and worked out the correct tuple name
    GetData(t, inputFiles, tupleFullName.Data());
  
    if(t==NULL)
    {
      cout<<"TTree pointer is NULL"<<endl;
      return EXIT_FAILURE;
    }

    fname.Form("%s/DSt_MuonUnBiased_%s%s_Mag%s_Strip%s_%s.root",
               outDir, pName, (charge.second).Data(), magPol, stripVersion, index);
    try {    
	DStFit_MuonUnBiased(t, (charge.first).Data(), pName, wsName, fname.Data(), dsName, 
            d0MassName, deltaMassName, fun_vec, index, printEntries);
    }
    catch (std::exception &e) {
       std::cout << "Caught exception: " << e.what() << std::endl;
       return EXIT_FAILURE;
    }
    // we should really delete the TChain, but doing so seems to cause
    // occasional segmentation faults
    /*
    delete t;
    t=NULL;
    */
  } 
  
  return EXIT_SUCCESS;
}



