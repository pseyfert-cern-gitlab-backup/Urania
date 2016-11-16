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
	TFile *g = TFile::Open("/afs/cern.ch/user/l/lohenry/cmtuser/Urania_v2r4/PhysFit/V0hhFitter/KShh/WS/MC-Bkg-WS-Standard-FastMC.root");   
	RooFitResult *res2 = (RooFitResult*) ((RooWorkspace*)g->Get("Desktop"))->genobj("rfres_fitResults");
	g->Close();
	if (res2 == NULL)
		{
			std::cout << "Did not find the RooFitResult in the file" << std::endl;
			return 0;
		}
    RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
	boost::program_options::options_description decisions("Option Arguments");
	std::string name("Fitter"), signalWS("Standard"), selectionType("Loose"), combModel("Exponential"), option("Standard");
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
	
	V0hhFit::Fitter fitter(name.c_str(),name.c_str());
	std::string baseDir = getenv("V0HHFITTERROOT");	
	std::cout << "WARNING: Changing the output directory to a personal one, due to space issues." << std::endl;
	baseDir = "/afs/cern.ch/work/l/lohenry/KShh/temp/";

	fitter.set1DFitVarName( "B_M" );
	fitter.setnCPU(4);
	fitter.loadWS(("/afs/cern.ch/user/l/lohenry/cmtuser/Urania_v2r4/PhysFit/V0hhFitter/KShh/WS/Fit-WS-"+option+"-Louis-"+selectionType+"-"+combModel+"-Standard.root").c_str(),"newDesktop");
	fitter.attachFile((baseDir+"KShh/temp/Temp-SystI-PartReco-"+option+"-"+selectionType+"-"+combModel+"-"+name+".root").c_str(),"RECREATE");
	std::string newModelName = fitter.findModel("model");
	std::cout << newModelName << std::endl;
	fitter.setModelName(newModelName.c_str());
	fitter.setConstraintString("Constraints");
	fitter.setDataSetName("data");	
	bool setConstant(true);
	setConstant = false;
	if (setConstant)
		{
			RooAbsPdf *model = fitter.getModel();
			const RooDataSet *data = fitter.getDataSet();
			RooArgSet *obs = model->getParameters(*data);
			TIterator *it = obs->createIterator();
			RooAbsArg *arg = NULL;
			while ((arg = (RooAbsArg*) it->Next()) != NULL)
				if (std::string(arg->GetName()).find("threshold") != std::string::npos)
					fitter.setParameterError(arg->GetName(),1.);
		}
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
		seed *= 1000;
		toy.setSeed(seed);
		//    toy.runToyStudy( "fitResults" , instructions.c_str(),"","",true);
		//    res->Print("V");
		//    res2->Print();    
		//	std::vector<std::string> args;
		//	args.push_back("Bd2KSpipiDD_2011_pdf_alpha0,Bd2KSpipiLL_2011_pdf_alpha0");
		std::vector<std::multimap<std::string,std::string> > vec;
		std::vector<std::string> modes;
		modes.push_back("pipi");
		modes.push_back("piK");
		modes.push_back("Kpi");
		modes.push_back("KK");
		std::vector<std::string> KScat;
		KScat.push_back("DD");
		KScat.push_back("LL");
		
		std::multimap<std::string,std::string> args;
		for (std::vector<std::string>::iterator itYears = years.begin() ; itYears != years.end() ; ++itYears)
			for (std::vector<std::string>::iterator itKS = KScat.begin() ; itKS != KScat.end() ; ++itKS)			
				for (std::vector<std::string>::iterator itModes = modes.begin() ; itModes != modes.end() ; ++itModes)			
					{
						std::string tempMode(*itModes);
						if (itModes->find("piK") != std::string::npos) continue;
												
						args.insert(std::make_pair(("Bkg_pipi"+(*itKS)+"_Charmed-Bd_"+(*itYears)+"_pdf_power"),"power_Charmed"));
						args.insert(std::make_pair(("Bkg_pipi"+(*itKS)+"_Charmed-Bd_"+(*itYears)+"_pdf_slope"),"slope_Charmed"));
						//						args.insert(std::make_pair(("Bkg_piK"+(*itKS)+"_Charmed-Bd_"+(*itYears)+"_pdf_power") ,"power_Charmed"));
						//						args.insert(std::make_pair(("Bkg_piK"+(*itKS)+"_Charmed-Bd_"+(*itYears)+"_pdf_slope") ,"slope_Charmed"));
						//						args.insert(std::make_pair(("Bkg_Kpi"+(*itKS)+"_Charmed-Bd_"+(*itYears)+"_pdf_power") ,"power_Charmed"));
						//						args.insert(std::make_pair(("Bkg_Kpi"+(*itKS)+"_Charmed-Bd_"+(*itYears)+"_pdf_slope") ,"slope_Charmed"));
						args.insert(std::make_pair(("Bkg_KK"+(*itKS)+"_Charmed-Bd_"+(*itYears)+"_pdf_power")  ,"power_Charmed"));
						args.insert(std::make_pair(("Bkg_KK"+(*itKS)+"_Charmed-Bd_"+(*itYears)+"_pdf_slope")  ,"slope_Charmed"));
						
						args.insert(std::make_pair(("Bkg_pipi"+(*itKS)+"_Charmed-Bs_"+(*itYears)+"_pdf_power"),"power_Charmed"));
						args.insert(std::make_pair(("Bkg_pipi"+(*itKS)+"_Charmed-Bs_"+(*itYears)+"_pdf_slope"),"slope_Charmed"));
						args.insert(std::make_pair(("Bkg_piK"+(*itKS)+"_Charmed-Bs_"+(*itYears)+"_pdf_power") ,"power_Charmed"));
						args.insert(std::make_pair(("Bkg_piK"+(*itKS)+"_Charmed-Bs_"+(*itYears)+"_pdf_slope") ,"slope_Charmed"));
						args.insert(std::make_pair(("Bkg_Kpi"+(*itKS)+"_Charmed-Bs_"+(*itYears)+"_pdf_power") ,"power_Charmed"));
						args.insert(std::make_pair(("Bkg_Kpi"+(*itKS)+"_Charmed-Bs_"+(*itYears)+"_pdf_slope") ,"slope_Charmed"));						

						args.insert(std::make_pair(("Bkg_pipi"+(*itKS)+"_Charmless-Bd_"+(*itYears)+"_pdf_power"),"power_Charmless"));
						args.insert(std::make_pair(("Bkg_pipi"+(*itKS)+"_Charmless-Bd_"+(*itYears)+"_pdf_slope"),"slope_Charmless"));
						//						args.insert(std::make_pair(("Bkg_piK"+(*itKS)+"_Charmless-Bd_"+(*itYears)+"_pdf_power") ,"power_Charmless"));
						//						args.insert(std::make_pair(("Bkg_piK"+(*itKS)+"_Charmless-Bd_"+(*itYears)+"_pdf_slope") ,"slope_Charmless"));
						//						args.insert(std::make_pair(("Bkg_Kpi"+(*itKS)+"_Charmless-Bd_"+(*itYears)+"_pdf_power") ,"power_Charmless"));
						//						args.insert(std::make_pair(("Bkg_Kpi"+(*itKS)+"_Charmless-Bd_"+(*itYears)+"_pdf_slope") ,"slope_Charmless"));
						args.insert(std::make_pair(("Bkg_KK"+(*itKS)+"_Charmless-Bd_"+(*itYears)+"_pdf_power")  ,"power_Charmless"));
						args.insert(std::make_pair(("Bkg_KK"+(*itKS)+"_Charmless-Bd_"+(*itYears)+"_pdf_slope")  ,"slope_Charmless"));

						args.insert(std::make_pair(("Bkg_pipi"+(*itKS)+"_Charmless-Bs_"+(*itYears)+"_pdf_power"),"power_Charmless"));
						args.insert(std::make_pair(("Bkg_pipi"+(*itKS)+"_Charmless-Bs_"+(*itYears)+"_pdf_slope"),"slope_Charmless"));
						args.insert(std::make_pair(("Bkg_piK"+(*itKS)+"_Charmless-Bs_"+(*itYears)+"_pdf_power"),"power_Charmless"));
						args.insert(std::make_pair(("Bkg_piK"+(*itKS)+"_Charmless-Bs_"+(*itYears)+"_pdf_slope"),"slope_Charmless"));
						args.insert(std::make_pair(("Bkg_Kpi"+(*itKS)+"_Charmless-Bs_"+(*itYears)+"_pdf_power"),"power_Charmless"));
						args.insert(std::make_pair(("Bkg_Kpi"+(*itKS)+"_Charmless-Bs_"+(*itYears)+"_pdf_slope"),"slope_Charmless"));

						args.insert(std::make_pair(("Bkg_pipi"+(*itKS)+"_MissGamNR-Bd_"+(*itYears)+"_pdf_power"),"power_MissGamNR"));
						args.insert(std::make_pair(("Bkg_pipi"+(*itKS)+"_MissGamNR-Bd_"+(*itYears)+"_pdf_slope"),"slope_MissGamNR"));

						args.insert(std::make_pair(("Bkg_pipi"+(*itKS)+"_MissGamRes-Bd_"+(*itYears)+"_pdf_power"),"power_MissGamRes"));
						args.insert(std::make_pair(("Bkg_pipi"+(*itKS)+"_MissGamRes-Bd_"+(*itYears)+"_pdf_slope"),"slope_MissGamRes"));
						
						//						args.insert(std::make_pair(("Bkg_pipi"+(*itKS)+"_Charmless-Bs_"+(*itYears)+"_pdf_power"),"power_Charmless"));
						//						args.insert(std::make_pair(("Bkg_pipi"+(*itKS)+"_Charmless-Bs_"+(*itYears)+"_pdf_slope"),"slope_Charmless"));
						//						args.insert(std::make_pair("Bkg_pipi"+(*itKS)+"_MissGamNR-Bd_"+(*itYears)+"_pdf_threshold","threshold_MissGamNR-Bd"));
						//						args.insert(std::make_pair("Bkg_pipi"+(*itKS)+"_MissGamRes-Bd_"+(*itYears)+"_pdf_threshold","threshold_MissGamRes-Bd"));
						
					}
		vec.push_back(args);
		std::vector<std::string> constPars;
		for (std::vector<std::string>::iterator itYears = years.begin() ; itYears != years.end() ; ++itYears)
			for (std::vector<std::string>::iterator itKS = KScat.begin() ; itKS != KScat.end() ; ++itKS)			
				{		
					std::multimap<std::string,std::string> args;
					args.insert(std::make_pair("Bkg_pipi"+(*itKS)+"_Charmless-Bs_"+(*itYears)+"_pdf_threshold","threshold_Charmless-Bs"));
					args.insert(std::make_pair("Bkg_pipi"+(*itKS)+"_Charmed-Bd_"+(*itYears)+"_pdf_threshold","threshold_Charmed-Bd"));
					args.insert(std::make_pair("Bkg_Kpi" +(*itKS)+"_Charmed-Bd_"+(*itYears)+"_pdf_threshold","threshold_Charmed-Bd"));
					//						args.insert(std::make_pair("Bkg_KK" +(*itKS)+"_Charmed-Bs_"+(*itYears)+"_pdf_threshold","threshold_Charmless-Bd"));
					args.insert(std::make_pair("Bkg_KK" +(*itKS)+"_Charmed-Bd_"+(*itYears)+"_pdf_threshold","threshold_Charmed-Bd"));
					args.insert(std::make_pair("Bkg_pipi"+(*itKS)+"_Charmless-Bd_"+(*itYears)+"_pdf_threshold","threshold_Charmless-Bd"));
					args.insert(std::make_pair("Bkg_Kpi"+(*itKS)+"_Charmless-Bd_"+(*itYears)+"_pdf_threshold","threshold_Charmless-Bd"));
					args.insert(std::make_pair("Bkg_KK"+(*itKS)+"_Charmless-Bd_"+(*itYears)+"_pdf_threshold","threshold_Charmless-Bd"));
					constPars.push_back("threshold_Charmed-Bd");
					constPars.push_back("threshold_Charmless-Bd");
					constPars.push_back("threshold_Charmed-Bs");
					constPars.push_back("threshold_Charmless-Bs");
				}
		
		toy.runSystI("fitResults",res2,vec,constPars);//,V0hhFit::Fitter::
		//		toy.runSystI("fitResults","threshold_Charmless-Bd",V0hhFit::Fitter::GAUSSIAN);
		toy.saveResults((baseDir+"KShh/temp/SystI-PartReco-"+option+"-"+selectionType+"-"+combModel+"-"+name+".root").c_str());    
	}
	
}
