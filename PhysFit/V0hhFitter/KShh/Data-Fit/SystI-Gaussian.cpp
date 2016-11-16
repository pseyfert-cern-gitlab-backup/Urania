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
	TFile *g = TFile::Open("/afs/cern.ch/user/l/lohenry/cmtuser/Urania_v2r4/PhysFit/V0hhFitter/KShh/WS/MC-Sig-WS-Loose-DoubleCB-Vanilla.root");
	RooFitResult *res2 = (RooFitResult*) ((RooWorkspace*)g->Get("Desktop"))->genobj("rfres_fitResults");
	g->Close();
    RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
	boost::program_options::options_description decisions("Option Arguments");
	std::string name("Fitter"), signalWS("Vanilla"), selectionType("Loose");
	unsigned int nToys(0), nCPU(4), seed(1);
	decisions.add_options()
		("help,h" , "produce help message")
		("name,n"    , boost::program_options::value<std::string>(&name), "")
		("toying,t"    , boost::program_options::value<unsigned int>(&nToys), "")
		("nCPU"    , boost::program_options::value<unsigned int>(&nCPU),"")
		("seed"    , boost::program_options::value<unsigned int>(&seed),"")
		("signalModel", boost::program_options::value<std::string>(&signalWS), "") 
		("selectionBDT,s", boost::program_options::value<std::string>(&selectionType), "specify which selection has been used in the sample: Loose, Tight, DP1 or DP2")
		;
	boost::program_options::variables_map vm;
	boost::program_options::store( boost::program_options::parse_command_line( argc, argv, decisions ), vm );
	boost::program_options::notify( vm );
	
	V0hhFit::Fitter fitter(name.c_str(),name.c_str());	
	fitter.set1DFitVarName( "B_M" );
	fitter.setnCPU(4);
	fitter.loadWS(("/afs/cern.ch/user/l/lohenry/cmtuser/Urania_v2r4/PhysFit/V0hhFitter/KShh/WS/Data-WS-"+selectionType+"-"+signalWS+".root").c_str(),"newDesktop");
	fitter.attachFile(("/afs/cern.ch/user/l/lohenry/cmtuser/Urania_v2r4/PhysFit/V0hhFitter/KShh/temp/Temp-SystI-Gaussian-"+selectionType+"-"+name+".root").c_str(),"RECREATE");
	std::string newModelName = fitter.findModel("model");
	std::cout << newModelName << std::endl;
	fitter.setModelName(newModelName.c_str());
	fitter.setConstraintString("Constraints");
	fitter.setDataSetName("data");
	bool setConstant(true);
	setConstant = false;
	V0hhFit::ToyStudy toy( &fitter, nToys );
	//  fitter.saveWS("temp.root");
	std::vector<std::string> years;
	years.push_back("2011");
	years.push_back("2012a");
	years.push_back("2012b");
	std::vector<std::string> KS_cat;
	KS_cat.push_back("DD");
	KS_cat.push_back("LL");
	std::vector<std::string> invMass;
	invMass.push_back("pipi");
	invMass.push_back("Kpi");
	invMass.push_back("piK");
	invMass.push_back("KK");
	for(std::vector<std::string>::iterator it_years = years.begin(); it_years != years.end(); ++it_years)
		for (std::vector<std::string>::iterator it_invmass = invMass.begin(); it_invmass != invMass.end(); ++it_invmass)
			for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
				{ 
					std::string temp = "KS"+(*it_invmass)+(*it_KS)+"_"+(*it_years)+"_pdf_KS"+(*it_invmass)+(*it_KS)+"_"+(*it_years)+"_Yield";
					std::string name;
					if (it_invmass->find("Kpi") != std::string::npos || it_invmass->find("piK") != std::string::npos)
						name = "Bd2";
					else					  
						name = "Bs2";
					name += temp;
				  fitter.setParameterValue(name.c_str(),0.5*fitter.getParameterValue(name.c_str()),false);
				  if (it_invmass->find("KK") != std::string::npos && it_KS->find("LL") != std::string::npos)
					  fitter.setParameterValue(name.c_str(),0.5*fitter.getParameterValue(name.c_str()),false);
				  
				  std::cout << fitter.getParameterValue(name.c_str());
				}

	bool Bs_blind(true);
	// Set Bs2KSKK initial yield to zero if is blind  
	std::string instructions("");
	//First we check if the original fit is good.
	RooFitResult* res = (RooFitResult*) fitter.getWS()->genobj("fitResults");
	bool goodfit = res->covQual()==3 && res->edm()<1 && res->status()==0;
	seed *= 100;
	toy.setSeed(seed);
	std::vector<std::string> args;
	//	toy.runSystI("fitResults",args,1.);//,V0hhFit::Fitter::
	toy.saveResults(("/afs/cern.ch/user/l/lohenry/cmtuser/Urania_v2r4/PhysFit/V0hhFitter/KShh/temp/SystI-Gaussian-"+selectionType+"-"+name+".root").c_str());
}
