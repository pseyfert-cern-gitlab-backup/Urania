#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>

//ROOT
#include "TChain.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TAxis.h"
#include "TKey.h"
#include "TROOT.h"
#include "TH2D.h"
#include "TFile.h"

// RooFit
#include "RooPlot.h"
#include "RooRealVar.h"
#include "RooSimultaneous.h"

// Fitter
#include "V0hhFitter/SimultaneousFitter.h"
#include "V0hhFitter/FitterPulls.h"
#include "V0hhFitter/ToyStudy.h"
#include "V0hhFitter/string_tools.h"
#include <boost/program_options.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

// SQLite
#include <sqlite3.h> 

//Constraints
#include "KShh/Constraints/useConstraints.cpp"


int main(int argc, char* argv[])
{
  RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
  boost::program_options::options_description decisions("Option Arguments");
  std::string name("Fitter"), signalWS("Standard");
  std::string selectionType("Loose"),combModel("Exponential"), option("Standard");
  unsigned int nToys(0), nCPU(4);
  decisions.add_options()
    ("help,h" , "produce help message")
	  ("name,n"    , boost::program_options::value<std::string>(&name), "")
	  ("selectionBDT,s"    , boost::program_options::value<std::string>(&selectionType), "")
	  ("toying,t"    , boost::program_options::value<unsigned int>(&nToys), "")
	  ("nCPU"    , boost::program_options::value<unsigned int>(&nCPU),"")
	  ("signalModel", boost::program_options::value<std::string>(&signalWS), "")
	  ("combModel", boost::program_options::value<std::string>(&combModel), "")
	  ("option", boost::program_options::value<std::string>(&option), "")
	  ;
  boost::program_options::variables_map vm;
  boost::program_options::store( boost::program_options::parse_command_line( argc, argv, decisions ), vm );
  boost::program_options::notify( vm );
  
  std::vector<std::string> files;
  TFile *temp = NULL;
  for (unsigned int i = 1 ; i < 50; i++) //Cap
    {
      std::stringstream ss;
      ss << i;
      temp = TFile::Open(("/afs/cern.ch/user/l/lohenry/cmtuser/Urania_v2r4/PhysFit/V0hhFitter/KShh/temp/Toy-"+option+"-"+selectionType+"-"+combModel+"-"+ss.str()+".root").c_str());
      if (!temp)
		  //		  break;
		  continue;
      temp->Close();
      files.push_back(temp->GetName());
      std::cout << "INFO: Adding " << temp->GetName() << " file in the FitterPulls." << std::endl;
    }
  V0hhFit::FitterPulls fPulls(files);
  //  fPulls.plotPulls(("KShh/temp/"+selectionType+"-pulls").c_str());
  //  fPulls.plotResiduals(("KShh/temp/"+selectionType+"-residuals").c_str());
  //  fPulls.plotPulls((selectionType+"-pulls").c_str());
  //  fPulls.plotValues(("KShh/temp/plots/"+selectionType+"/"+combModel+"/").c_str(),("Toys-"+option+"-Values-"+signalWS).c_str(),2);
  fPulls.plotErrorVsResiduals(("KShh/temp/plots/"+selectionType+"/"+combModel+"/").c_str(),("Toys-"+option+"-ErrVsRes-"+signalWS+"-").c_str());
  fPulls.plotResiduals(("KShh/temp/plots/"+selectionType+"/"+combModel+"/").c_str(),("Toys-"+option+"-Res-"+signalWS).c_str(),2);
	  
  
  //  fPulls.writeVectors("temp.txt");
}
