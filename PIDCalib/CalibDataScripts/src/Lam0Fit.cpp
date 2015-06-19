// $Id: $

// Include files
#include <map>
#include <vector>
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
#include "CalibDataScripts/Lam0Fit.h"
#include "CalibDataScripts/GetData.h"

// Namespaces
namespace bass=boost::assign;
using std::cout;
using std::endl;

// typedefs
typedef std::map<TString,TString> ssMap;
typedef std::vector<TString> sVect;

// first = name given to fit function,
// second = charge indicator in output filename
// The first part of the pair should really be an enum instead
ssMap charges = bass::map_list_of("Negative", "Minus")("Positive", "Plus");
sVect momRanges = bass::list_of("LoP")("HiP");

const char* wsName="Lam0Calib";
const char* dsName="data";
const char* massName="mass";
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
  // 7: print entries (1 = print entries, 0 = don't print)
  // 8: File(s) to run over
  //---------------------------------------------------//
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

  TString fname;
  TString tupleFullName;
  TTree* t = NULL;
  
  //---------------------------------------------------//
  // Fit -ve, +ve, Low P, High P tracks 
  //---------------------------------------------------//
  BOOST_FOREACH(const TString& momRange, momRanges) {
    tupleFullName.Form("Lam02PPi_%sTuple/%s", 
                       momRange.Data(), tupleName);
    BOOST_FOREACH(const ssMap::value_type& charge, charges) {
      //---------------------------------------------------//
      // Get data
      //---------------------------------------------------//
      GetData(t, inputFiles, tupleFullName.Data());
 
      if(t==NULL)
      {
        cout<<"TTree pointer is NULL"<<endl;
        return EXIT_FAILURE;
      }

      fname.Form("%s/Lam0_%s%s_%s_Mag%s_Strip%s_%s.root",
                 outDir, pName, (charge.second).Data(), momRange.Data(),
                 magPol, stripVersion, index);
      
      try{
          Lam0Fit(t, (charge.first).Data(), momRange.Data(),
                  pName, wsName, fname.Data(), dsName,
                  massName, fun_vec, index, printEntries);
      }
      catch (std::exception &e) {
         std::cout << "Caught exception: " << e.what() << std::endl;
         return EXIT_FAILURE;
      }
     
      // we should really delete the TChain, but doing so seems to cause
      // occasional segmentation faults
      /*
	 TChain* ch = (TChain*)t;
      delete ch;
      ch=NULL;
      */
    }
  }  
  return EXIT_SUCCESS;
}
