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

bool piToK(std::pair<std::string,std::string> cross)
{
	if (cross.first == "Bd2KSpipi")
		return true;
	if (cross.first == "Bd2KSKK")
		return false;
	if (cross.second == "pipi")
		return false;
	if (cross.second == "KK")
		return true;
	std::cout << "FATAL: Did not find the proper CF category... : " << cross.first << " " << cross.second << "." <<std::endl;
	std::exit(1);
	return true;
}

int main(int argc, char* argv[])
{ 
    RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
	boost::program_options::options_description decisions("Option Arguments");
	std::string name("Fitter"), combModel("Exponential"), selectionType("Loose"),option("Standard");
	unsigned int nToys(0), nCPU(4), seed(1);
	decisions.add_options()
		("help,h" , "produce help message")
		("name,n"    , boost::program_options::value<std::string>(&name), "")
		("toying,t"    , boost::program_options::value<unsigned int>(&nToys), "")
		("nCPU"    , boost::program_options::value<unsigned int>(&nCPU),"")
		("seed"    , boost::program_options::value<unsigned int>(&seed),"")
		("combModel", boost::program_options::value<std::string>(&combModel), "") 
		("selectionBDT,s", boost::program_options::value<std::string>(&selectionType), "specify which selection has been used in the sample: Loose, Tight, DP1 or DP2")
		("option"    , boost::program_options::value<std::string>(&option),"")
		;
	boost::program_options::variables_map vm;
	boost::program_options::store( boost::program_options::parse_command_line( argc, argv, decisions ), vm );
	boost::program_options::notify( vm );
	//TODO
	std::string WSdir = getenv("V0HHFITTERROOT");
	WSdir += "/KShh/WS/";
	std::cout << "WARNING: Only the standard SameMissID & Strong p cut samples are implemented." << std::endl;
	TFile *g = TFile::Open((WSdir+"MC-CrossFeed-WS-SameMissID-Louis-"+selectionType+"-StrongPcut.root").c_str());
	RooFitResult *res2 = (RooFitResult*) ((RooWorkspace*)g->Get("Desktop"))->genobj("rfres_fitResults");
	g->Close();
	if (res2 == NULL)
		{
			std::cout << "Did not find the RooFitResult in the file" << std::endl;
			return 0;
		}

	
	V0hhFit::Fitter fitter(name.c_str(),name.c_str());
	
	fitter.set1DFitVarName( "B_M" );
	fitter.setnCPU(4);
	std::cout << "WARNING: Only standard fit taken into account." << std::endl;
	std::string combOption = (combModel == "PolSlopes")? "PolSlopes":"Exponential";
	fitter.loadWS((WSdir+"Fit-WS-"+option+"-Louis-"+selectionType+"-"+combModel+"-Standard.root").c_str(),"newDesktop");
	std::string baseDir = getenv("V0HHFITTERROOT");	
	std::cout << "WARNING: Changing the output directory to a personal one, due to space issues." << std::endl;
	baseDir = "/afs/cern.ch/work/l/lohenry/KShh/temp/";
	fitter.attachFile((baseDir+"/KShh/temp/Temp-SystI-CrossFeed-"+option+"-"+selectionType+"-"+name+".root").c_str(),"RECREATE");
	std::string newModelName = fitter.findModel("model");
	std::cout << newModelName << std::endl;
	fitter.setModelName(newModelName.c_str());
	fitter.setConstraintString("Constraints");
	fitter.setDataSetName("data");

	V0hhFit::ToyStudy toy( &fitter, nToys );
	std::vector<std::string> years;
	years.push_back("2011");
	years.push_back("2012a");
	years.push_back("2012b");
	bool Bs_blind(true);
	// Set Bs2KSKK initial yield to zero if is blind  
	std::string instructions("");
	//First we check if the original fit is good.
	RooFitResult* res = (RooFitResult*) fitter.getWS()->genobj("rfres_fitResults");
	bool goodfit = res->covQual()==3 && res->edm()<1 && res->status()==0;
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
	}
	seed *= 1000;
	toy.setSeed(seed);
	std::vector<std::multimap<std::string,std::string> > vec;
	std::vector<std::string> KScat;
	KScat.push_back("DD");
	KScat.push_back("LL");
	//	std::multimap<std::string,std::string> args;
	std::vector<std::pair<std::string,std::string > > vars;
	std::vector<std::pair<std::string,std::string> > cross;
	cross.push_back(std::make_pair("Bd2KSpipi","piK"));
	cross.push_back(std::make_pair("Bd2KSpipi","Kpi"));
	cross.push_back(std::make_pair("Bs2KSKpi","pipi"));
	cross.push_back(std::make_pair("Bs2KSKpi","KK"));
	cross.push_back(std::make_pair("Bd2KSKK","piK"));
	cross.push_back(std::make_pair("Bd2KSKK","Kpi"));

	std::multimap<std::string,std::string> args;
	for (std::vector<std::string>::iterator itYears = years.begin() ; itYears != years.end() ; ++itYears)
		for (std::vector<std::string>::iterator itKS = KScat.begin() ; itKS != KScat.end() ; ++itKS)			
			for (std::vector<std::pair<std::string,std::string> >::iterator itCross = cross.begin() ; itCross != cross.end() ; ++itCross)
				{
					
					if (itCross->second.find("piK") != std::string::npos) continue;
					std::string tempCross = (piToK(*itCross))?"PiToK":"KToPi";
					args.insert(std::make_pair("CrossFeed_"+itCross->first+"_as_"+itCross->second+(*itKS)+"_"+(*itYears)+"_pdf_mu",itCross->first+"_as_"+itCross->second+"_mu"));
					args.insert(std::make_pair("CrossFeed_"+itCross->first+"_as_"+itCross->second+(*itKS)+"_"+(*itYears)+"_pdf_sigma"        ,"sigma_"        +tempCross));
					args.insert(std::make_pair("CrossFeed_"+itCross->first+"_as_"+itCross->second+(*itKS)+"_"+(*itYears)+"_pdf_alpha0"       ,"alpha0_"       +tempCross));
					args.insert(std::make_pair("CrossFeed_"+itCross->first+"_as_"+itCross->second+(*itKS)+"_"+(*itYears)+"_pdf_n0"           ,"n0_"           +tempCross));
					args.insert(std::make_pair("CrossFeed_"+itCross->first+"_as_"+itCross->second+(*itKS)+"_"+(*itYears)+"_pdf_n1oN0"        ,"n1oN0_"        +tempCross));
					args.insert(std::make_pair("CrossFeed_"+itCross->first+"_as_"+itCross->second+(*itKS)+"_"+(*itYears)+"_pdf_alpha1oAlpha0","alpha1oAlpha0_"+tempCross));
					args.insert(std::make_pair("CrossFeed_"+itCross->first+"_as_"+itCross->second+(*itKS)+"_"+(*itYears)+"_pdf_coreFrac"     ,"coreFrac_"     +tempCross));
					if (itCross->second.find("Kpi") != std::string::npos)
						{
							args.insert(std::make_pair("CrossFeed_"+itCross->first+"_as_piK"+(*itKS)+"_"+(*itYears)+"_pdf_mu",itCross->first+"_as_"+itCross->second+"_mu"));
							args.insert(std::make_pair("CrossFeed_"+itCross->first+"_as_piK"+(*itKS)+"_"+(*itYears)+"_pdf_sigma"        ,"sigma_"        +tempCross));
							args.insert(std::make_pair("CrossFeed_"+itCross->first+"_as_piK"+(*itKS)+"_"+(*itYears)+"_pdf_alpha0"       ,"alpha0_"       +tempCross));
							args.insert(std::make_pair("CrossFeed_"+itCross->first+"_as_piK"+(*itKS)+"_"+(*itYears)+"_pdf_n0"           ,"n0_"           +tempCross));
							args.insert(std::make_pair("CrossFeed_"+itCross->first+"_as_piK"+(*itKS)+"_"+(*itYears)+"_pdf_n1oN0"        ,"n1oN0_"        +tempCross));
							args.insert(std::make_pair("CrossFeed_"+itCross->first+"_as_piK"+(*itKS)+"_"+(*itYears)+"_pdf_alpha1oAlpha0","alpha1oAlpha0_"+tempCross));
							args.insert(std::make_pair("CrossFeed_"+itCross->first+"_as_piK"+(*itKS)+"_"+(*itYears)+"_pdf_coreFrac"     ,"coreFrac_"     +tempCross));
						}
				}
	vec.push_back(args);
	std::vector<std::string> constPars;
	toy.runSystI("fitResults",res2,vec,constPars);//,V0hhFit::Fitter::
	toy.saveResults((baseDir+"/KShh/temp/SystI-CrossFeed-"+option+"-"+combOption+"-"+selectionType+"-Standard-"+name+".root").c_str());
}
