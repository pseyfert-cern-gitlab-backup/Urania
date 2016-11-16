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
	std::string name("Fitter"), signalWS(""), selectionType(""), combModel("Exponential"),option("Standard");
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
		("option"    , boost::program_options::value<std::string>(&option),"")
		;
	boost::program_options::variables_map vm;
	boost::program_options::store( boost::program_options::parse_command_line( argc, argv, decisions ), vm );
	boost::program_options::notify( vm );
	
	//	TFile *f = TFile::Open(("/afs/cern.ch/user/l/lohenry/cmtuser/Urania_v2r4/PhysFit/V0hhFitter/KShh/WS/Data-WS-"+selectionType+signalWS+".root").c_str(),"READ");
	//	RooWorkspace *w = (RooWorkspace*) f->Get("newDesktop");
	//	f->Close();
	V0hhFit::Fitter fitter(name.c_str(),name.c_str());
	
	fitter.set1DFitVarName( "B_M" );
	fitter.setnCPU(4);
	//  fitter.loadWS(("/afs/cern.ch/user/l/lohenry/cmtuser/Urania_v2r4/PhysFit/V0hhFitter/KShh/WS/Data-WS"+signalWS+".root").c_str(),"SimplifiedWS");
	std::string baseDir = getenv("V0HHFITTERROOT");	
	std::cout << "WARNING: Changing the output directory to a personal one, due to space issues." << std::endl;
	//	baseDir = "/afs/cern.ch/work/l/lohenry/Fitter";
	fitter.loadWS((baseDir+"/KShh/WS/Fit-WS-"+option+"-Louis-"+selectionType+"-"+combModel+"-Standard.root").c_str(),"newDesktop");
	fitter.attachFile((baseDir+"/KShh/temp/Temp-Toy-"+option+"-"+selectionType+"-"+combModel+"-"+name+".root").c_str(),"RECREATE");
	std::string newModelName = fitter.findModel("model");
	std::cout << newModelName << std::endl;
	fitter.setModelName(newModelName.c_str());
	fitter.setConstraintString("Constraints");
	fitter.setDataSetName("data");
	
	V0hhFit::ToyStudy toy( &fitter, nToys );
	//  fitter.saveWS("temp.root");
	std::vector<std::string> years;
	years.push_back("2011");
	years.push_back("2012a");
	years.push_back("2012b");
	bool Bs_blind(true);
	// Set Bs2KSKK initial yield to zero if is blind  
	std::string instructions("");
	//First we check if the original fit is good.
	RooFitResult* res = (RooFitResult*) fitter.getWS()->genobj("rfres_fitResults");
	bool goodfit = res->covQual()==3 && res->edm()<1e-2 && res->status()==0;
	if (!goodfit)
		{
			std::cout << "FATAL: The original fit is not good enough! EDM = " << res->edm() << ", COVQUAL = " << res->covQual() << ", and STATUS = " << res->status() << "." << std::endl;
			std::exit(1);
		}
	if (Bs_blind){
		bool begin(true);
		for (std::vector<std::string>::iterator it_years       = years.begin();     it_years    != years.end();     ++it_years)
			{
				if (begin)
					{
						instructions += "Bs2KSKKDD_"+(*it_years)+"_pdf_KSKKDD_"+(*it_years)+"_Yield=0";
						instructions += ",";
						instructions += "Bs2KSKKLL_"+(*it_years)+"_pdf_KSKKLL_"+(*it_years)+"_Yield=0";
						begin = false;
					}
				else
					{
						instructions += ",";
						instructions += "Bs2KSKKDD_"+(*it_years)+"_pdf_KSKKDD_"+(*it_years)+"_Yield=0";
						instructions += ",";
						instructions += "Bs2KSKKLL_"+(*it_years)+"_pdf_KSKKLL_"+(*it_years)+"_Yield=0";
					}
			}
		seed *= 100;
		toy.setSeed(seed);
		toy.runToyStudy( "fitResults" , instructions.c_str(),"","",true);		
		toy.saveResults((baseDir+"/KShh/temp/Toy-"+option+"-"+selectionType+"-"+combModel+"-"+name+".root").c_str());
	}
	
}
