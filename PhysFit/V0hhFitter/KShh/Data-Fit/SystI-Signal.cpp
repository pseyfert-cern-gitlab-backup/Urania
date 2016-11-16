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
	std::string v0hhDir = getenv("V0HHFITTERROOT");
	std::string baseDir = getenv("V0HHFITTERROOT");
	std::cout << "WARNING: Changing the output directory to a personal one, due to space issues." << std::endl;
	baseDir = "/afs/cern.ch/work/l/lohenry/KShh/temp/";
    RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
	boost::program_options::options_description decisions("Option Arguments");
	std::string name("Fitter"), combModel("Standard"), selectionType("Loose"), option("Standard");
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
	
	std::string combOption=(combModel=="Standard")?"Exponential":combModel;
	TFile *g = TFile::Open((v0hhDir+"/KShh/WS/MC-Sig-Fits-WS-Standard-Louis-"+selectionType+"-DoubleCB.root").c_str());   
	RooFitResult *res2 = (RooFitResult*) ((RooWorkspace*)g->Get("Desktop"))->genobj("rfres_fitResults");
	g->Close();
	std::cout << "INFO: Res2 loaded." << std::endl;

	V0hhFit::Fitter fitter(name.c_str(),name.c_str());
	
	fitter.set1DFitVarName( "B_M" );
	fitter.setnCPU(4);
	fitter.loadWS((v0hhDir+"/KShh/WS/Fit-WS-"+option+"-Louis-"+selectionType+"-"+combOption+"-Standard.root").c_str(),"newDesktop");
	fitter.attachFile((baseDir+"/KShh/temp/Temp-SystI-Signal-"+option+"-"+selectionType+"-"+combOption+"-"+name+".root").c_str(),"RECREATE");
	//	if (w == NULL)
	//		{
	//			std::cout << "RooWorkspace does not exist anymore" << std::endl;	
	//			std::exit(1);
	//		}
	//	fitter.setWS(w,true);
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
				if (std::string(arg->GetName()).find("Yield") == std::string::npos && std::string(arg->GetName()).find("dummy") == std::string::npos)
					{
						std::cout << "WARNING: Setting " << arg->GetName() << " constant." << std::endl;
						fitter.setParameterConstant(arg->GetName(),true);
						//					fitter.getWS()->var(arg->GetName())->setConstant(kTRUE);
					}
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
		seed *= 100;
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
		std::vector<std::string> mesons;
		mesons.push_back("Bd");
		mesons.push_back("Bs");
		std::vector<std::string> KScat;
		KScat.push_back("DD");
		KScat.push_back("LL");
		std::multimap<std::string,std::string> args;
		
		for (std::vector<std::string>::iterator itYears = years.begin() ; itYears != years.end() ; ++itYears)
			for (std::vector<std::string>::iterator itMesons = mesons.begin() ; itMesons != mesons.end() ; ++itMesons)			
				for (std::vector<std::string>::iterator itKS = KScat.begin() ; itKS != KScat.end() ; ++itKS)			
					for (std::vector<std::string>::iterator itModes = modes.begin() ; itModes != modes.end() ; ++itModes)			
						{
							//							std::multimap<std::string,std::string> args;
							std::string tempMode(*itModes);
							std::string leftTailSuffix;
							//							leftTailLeftTailSuffix = "("+(*itYears)+")";
							if (itModes->find("piK") != std::string::npos) continue;
							args.insert(std::make_pair((*itMesons)+"2KS"+(*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n0","N0("+(tempMode)+")"+leftTailSuffix));
							args.insert(std::make_pair((*itMesons)+"2KS"+(*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha0","Alpha0("+(tempMode)+")"+leftTailSuffix));
							args.insert(std::make_pair((*itMesons)+"2KS"+(*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n1oN0","N1oN0"));
							args.insert(std::make_pair((*itMesons)+"2KS"+(*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha1oAlpha0","Alpha1oAlpha0"));
							args.insert(std::make_pair((*itMesons)+"2KS"+(*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_coreFrac","CoreFrac("+tempMode+")"+leftTailSuffix));
							if (itModes->find("Kpi") != std::string::npos)
								{
									args.insert(std::make_pair((*itMesons)+"2KSpiK"+(*itKS)+"_"+(*itYears)+"_pdf_n0","N0("+(tempMode)+")"+leftTailSuffix));
									args.insert(std::make_pair((*itMesons)+"2KSpiK"+(*itKS)+"_"+(*itYears)+"_pdf_alpha0","Alpha0("+(tempMode)+")"+leftTailSuffix));
									args.insert(std::make_pair((*itMesons)+"2KSpiK"+(*itKS)+"_"+(*itYears)+"_pdf_n1oN0","N1oN0"));
									args.insert(std::make_pair((*itMesons)+"2KSpiK"+(*itKS)+"_"+(*itYears)+"_pdf_alpha1oAlpha0","Alpha1oAlpha0"));
									args.insert(std::make_pair((*itMesons)+"2KSpiK"+(*itKS)+"_"+(*itYears)+"_pdf_coreFrac","CoreFrac("+tempMode+")"+leftTailSuffix));
								}
							vec.push_back(args);
						}
		vec.push_back(args);
		std::vector<std::string> constPars;
		toy.runSystI("fitResults",res2,vec,constPars);//,V0hhFit::Fitter::
		toy.saveResults((baseDir+"/KShh/temp/SystI-Sig-"+option+"-"+selectionType+"-"+combOption+"-"+name+".root").c_str());    
	}
	
}
