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
#include "TROOT.h"
#include "TH2D.h"
#include "TFile.h"

// RooFit
#include "RooPlot.h"
#include "RooRealVar.h"
#include "RooSimultaneous.h"

// Fitter
#include "V0hhFitter/SimultaneousFitter.h"
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
	std::string name("Fitter"), signalWS("Standard"), selectionType("Loose"),option("Standard"),combModel("Exponential");
	unsigned int nToys(0), nCPU(4), seed(1);
	decisions.add_options()
		("help,h" , "produce help message")
		("name,n"    , boost::program_options::value<std::string>(&name), "")
		("toying,t"    , boost::program_options::value<unsigned int>(&nToys), "")
		("nCPU"    , boost::program_options::value<unsigned int>(&nCPU),"")
		("seed"    , boost::program_options::value<unsigned int>(&seed),"")
		("signalModel", boost::program_options::value<std::string>(&signalWS), "") 
		("combModel", boost::program_options::value<std::string>(&combModel), "") 
		("selectionBDT,s", boost::program_options::value<std::string>(&selectionType), "specify which selection has been used in the sample: Loose, Tight, DP1 or DP2")
		("option", boost::program_options::value<std::string>(&option))
		;
	boost::program_options::variables_map vm;
	boost::program_options::store( boost::program_options::parse_command_line( argc, argv, decisions ), vm );
	boost::program_options::notify( vm );

	if (option=="Standard")
		{
			std::cout << "FATAL: Cannot test the Standard with respect to itself." << std::endl;
			std::exit(1);
		}

	TString dir         = getenv("V0HHFITTERROOT");
	std::string V0hhDir = dir.Data();
	std::string saveDir = V0hhDir+"/KShh/"; 
	std::string otherComb = "Standard";
	//fitter is the instance of the normal fit.
	V0hhFit::Fitter fitter(name.c_str(),name.c_str());	
	fitter.set1DFitVarName( "B_M" );
	fitter.setnCPU(4);
	fitter.loadWS(("/afs/cern.ch/user/l/lohenry/cmtuser/Urania_v2r4/PhysFit/V0hhFitter/KShh/WS/Fit-WS-Standard-Louis-"+selectionType+"-"+combModel+"-Standard.root").c_str(),"newDesktop");
	fitter.attachFile(("/afs/cern.ch/user/l/lohenry/cmtuser/Urania_v2r4/PhysFit/V0hhFitter/KShh/temp/Temp-SystII-CombModel-"+option+"-"+selectionType+"-"+combModel+"-"+name+".root").c_str(),"RECREATE");
	std::string newModelName = fitter.findModel("model");
	fitter.setModelName(newModelName.c_str());
	fitter.setConstraintString("Constraints");
	fitter.setDataSetName("data");

	// Import official PDF from the WS
	V0hhFit::SimultaneousFitter fitter_official( "B2KShhFit", "B0(d,s) --> KS h' h Fit" );
	TString massvar("B_M"); // Observable name to be used in the fit
	fitter_official.loadWS((saveDir+"WS/Fit-WS-"+option+"-Louis-"+selectionType+"-"+combModel+"-Standard.root").c_str(), "newDesktop", false );
	fitter_official.set1DFitVarName( massvar );
	fitter_official.setPlotBins( massvar, 50 );
	fitter_official.setBins("B_M", 100, "cache"); // Cache for the ArgusConvGauss
	std::string officialModelName = fitter_official.findModel("model");
	fitter_official.setModelName(officialModelName.c_str());
	fitter_official.setDataSetName("data");
	fitter_official.setConstraintString("Constraints");

	V0hhFit::ToyStudy toy( &fitter, nToys );
	//  fitter.saveWS("temp.root");
	std::vector<std::string> years;
	years.push_back("2011");
	years.push_back("2012a");
	years.push_back("2012b");
	// Set Bs2KSKK initial yield to zero if is blind  
	std::string instructions("");
	//First we check if the original fit is good.
	RooFitResult* res = (RooFitResult*) fitter.getWS()->genobj("rfres_fitResults");
	//	res->Print();
	bool goodFit = res->covQual()==3 && res->edm()<1e-2 && res->status()==0;
	if (!goodFit)
		{
			std::cout << "FATAL: Concurrent fit is not good enough!" << std::endl;
			return 1;
		}
	seed *= 1000;
	toy.setSeed(seed);	
	toy.runSystII("fitResults",&fitter_official,true);
	toy.saveResults(("/afs/cern.ch/user/l/lohenry/cmtuser/Urania_v2r4/PhysFit/V0hhFitter/KShh/temp/SystII-CombModel-"+option+"-"+selectionType+"-"+combModel+"-"+name+".root").c_str());
	return 0;
}