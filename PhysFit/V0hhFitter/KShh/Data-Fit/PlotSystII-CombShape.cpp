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

	TString dir         = getenv("V0HHFITTERROOT");
	std::string V0hhDir = dir.Data();
	std::string saveDir = V0hhDir+"/KShh/"; 
	std::string otherComb = (combModel=="Exponential")?"PolSlopes":"Exponential";
	
	std::vector<std::string> files;
	unsigned int i = 1;
	TFile *temp = NULL;
	while (i <= 25) //Cap
		{
			std::stringstream ss;
			ss << i;
			temp = TFile::Open(("/afs/cern.ch/user/l/lohenry/cmtuser/Urania_v2r4/PhysFit/V0hhFitter/KShh/temp/SystII-CombShape-"+combModel+"-"+option+"-"+selectionType+"-"+otherComb+"-"+ss.str()+".root").c_str());
			if (!temp)
				{
					//				  break;
					i++;
					continue;
				}
			temp->Close();
			files.push_back(temp->GetName());
			std::cout << "INFO: Adding " << temp->GetName() << " file in the FitterPulls." << std::endl;
			++i;
		}
	V0hhFit::FitterPulls fPulls(files,"SystII-TypeII","dataFit","SystII-CombShape-"+selectionType+"-"+combModel+"-"+option+".txt");
	//	fPulls.fillVectors_SystII(files);
	fPulls.plotSystII(("KShh/temp/plots/SystII-CombShape/"+selectionType+"/").c_str(),"SystII-CombShape-"+combModel+"-"+option,2);//("PolSlopes-"+signalWS).c_str(),2);  
}
