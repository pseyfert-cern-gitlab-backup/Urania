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
#include "CalibDataScripts/JpsiFit.h"
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
// map of charge to muon name
ssMap muonNames = bass::map_list_of("Negative", "Mu0")("Positive", "Mu1");
// map of charge to other muon name
ssMap otherMuonNames = bass::map_list_of("Negative", "Mu1")("Positive", "Mu0");

const char* wsName="JpsiCalib";
const char* dsName="data";
const char* massName="mass";
const char* tupleName="CalibPID";

int main(int argc, char *argv[])
{
  //---------------------------------------------------//
  // argv parameters:
  // 1: Field Orientation (Up or Down)
  // 2: Stripping version
  // 3: Datatype (e.g. '2011' or '2012')
  // 4: Subset index
  // 5: Output directory
  // 6: print entries (1 = print entries, 0 = don't print)
  // 7: File(s) to run over
  //---------------------------------------------------//
  if (!argc>7)
  {
    cout<<"Invalid number of arguments passed: "<<argc<<endl;
    return EXIT_FAILURE;
  }
  //---------------------------------------------------//

  const char* magPol=argv[1];
  const char* stripVersion=argv[2];
  const char* DataType=argv[3];
  const char* index=argv[4];
  const char* outDir=argv[5];
  Bool_t printEntries = boost::lexical_cast<Bool_t>(argv[6]);

  //---------------------------------------------------//
  // Pass input files into vector 
  //---------------------------------------------------//
  std::vector<const char*> inputFiles;
  for (unsigned int i = 7; i < (unsigned int)argc; ++i) 
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
  // Fit -ve, +ve tracks 
  //---------------------------------------------------//
  BOOST_FOREACH(const ssMap::value_type& charge, charges) {
    tupleFullName.Form("JpsiFromBNoPIDNoMipTuple/%s", 
                       tupleName);
    const TString& muonName = muonNames[charge.first];
    const TString& otherMuonName = otherMuonNames[charge.first];

    //---------------------------------------------------//
    // Get data
    //---------------------------------------------------//
    TTree* t = NULL;
    GetData(t,
            inputFiles,
            tupleFullName.Data());
    if(t==NULL)
    {
      cout<<"TTree pointer is NULL"<<endl;
      return EXIT_FAILURE;  
    }
    fname.Form("%s/Jpsi_Mu%s_Mag%s_Strip%s_%s.root",
	       outDir, (charge.second).Data(),
	       magPol, stripVersion, index);
    try {
        JpsiFit(t, (charge.first).Data(), 
                muonName.Data(), otherMuonName.Data(),
                wsName, fname.Data(), dsName, massName,
               fun_vec, index, printEntries);
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
