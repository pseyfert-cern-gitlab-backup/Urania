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


void fastExit(const char* msg)
{
	std::cout << msg << std::endl;
	assert(0);
}

int main(int argc, char* argv[])
{
	RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
	std::time_t start_time = std::time(NULL);
	std::time_t temp_time = std::time(NULL);
	bool Bs_blind(true);
	std::string selectionType("Loose");
	std::string Int_info = "";    
	std::set<std::string> integral_range;
	//	Double_t sigma_input(0.);
	std::string name("");
	std::string sigShape("DoubleCB");
	std::string sigModel("Standard");
	std::string crossModel("Standard");
	std::string partModel("Standard");
	std::string option("Standard");
	std::string mcOrigin("Louis");
	unsigned int nCPU(4);
	boost::program_options::options_description decisions("Option Arguments");
	decisions.add_options()
		("help,h" , "produce help message")
		("selectionBDT,s", boost::program_options::value<std::string>(&selectionType), "specify which selection has been used in the sample: Loose, Tight, DP1 or DP2")
		("blind,b", boost::program_options::value<bool>(&Bs_blind), "specify the Bs2KSKK mass window to be unblind by setting 'false'. Default is set to blind.")
		("name,n"    , boost::program_options::value<std::string>(&name), "")
		("sigShape"  , boost::program_options::value<std::string>(&sigShape), "")
		("option"    , boost::program_options::value<std::string>(&option),"")
		("nCPU"    , boost::program_options::value<unsigned int>(&nCPU),"")
		("mcOrigin"    , boost::program_options::value<std::string>(&mcOrigin),"")
		;
	
	boost::program_options::variables_map vm;
	boost::program_options::store( boost::program_options::parse_command_line( argc, argv, decisions ), vm );
	boost::program_options::notify( vm );
  
	if( vm.count("help") ) {
		std::cout << decisions << std::endl;
		std::exit(0);
	}
	if (vm.count("blind")) {
		if (!Bs_blind){
			std::cout << "WARNING: The Bs2KSKK mass windows will be considered unblind!" << std::endl;
		}
	}
	
	std::string fileName("constraints-SignalOnly-"+option);  
	KShhConstraints::testFile(fileName);
  
	//Copy the constraints files...
	TString dir         = getenv("V0HHFITTERROOT");
	std::string V0hhDir = dir.Data();
	std::ifstream inFile((V0hhDir+"/KShh/Constraints/"+fileName+".txt").c_str());

	//================================================================================
	// Create instance of the fitter and observables
	//================================================================================
	std::cout << "Read all options: " 
			  << (std::time(NULL) - start_time) << " "
			  << (std::time(NULL) - temp_time)
			  << std::endl;
	temp_time = std::time(NULL);

	//================================================================================
	std::vector<std::string> years;
	years.push_back("2011");
	years.push_back("2012a");
	years.push_back("2012b");
	std::vector<std::string> KS_cat; 
	KS_cat.push_back("DD");
	KS_cat.push_back("LL");
 
	// Invariant masses 
	std::vector<std::string> modes;
	modes.push_back("Bd2KSpipi");
	modes.push_back("Bs2KSpipi");
	modes.push_back("Bd2KSKpi");
	modes.push_back("Bs2KSKpi");
	modes.push_back("Bd2KSpiK");
	modes.push_back("Bs2KSpiK");
	modes.push_back("Bd2KSKK");
	modes.push_back("Bs2KSKK");
  
	//================================================================================
	// Create instance of the fitter and observables
	//================================================================================
	V0hhFit::SimultaneousFitter fitter( "B2KShhMCFit", "B0(d,s) --> KS h' h Fit" );
	fitter.createWS( "Desktop", "Desktop" );
  
	fitter.setGlobalKillBelowError( RooFit::FATAL ); // Monitoring
	fitter.setnCPU( 4 ); // Sets the number of CPUs to run the minimisation in parallel
  
	TString massvar("B_M"); // Observable name to be used in the fit
	Float_t xmin( 5000.0 ), xmax( 5800.0 ); // Set the range of fit axis
  
	// Path to local area to save informations of the fit 
	TString currentDir = getenv("V0HHFITTERROOT");
	std::string auxiliar = (currentDir).Data();
	std::string saveDir = auxiliar+"/KShh/"; 
  
	fitter.set1DFitVarName( massvar );
	fitter.make1DFitVar( xmin, xmax, "MeV/c^{2}", "m(#it{K^{0}_{#rm S} h^{+} h^{-}})" );
	fitter.setPlotBins( massvar, 50 );
  
	//================================================================================
  
	//================================================================================
	// Make all PDFs 
	//================================================================================
	for(std::vector<std::string>::iterator it_year     = years.begin();   it_year  != years.end();   ++it_year)
		for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes)
			for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
				if (sigShape == "Cruijff")
					fitter.makeCruijff(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(),
									   5300, 5250, 5375, 5, 0, 20, 1, 0, 5, 1, 0, 5);  
				else if (sigShape == "CruijffSimple")
					fitter.makeCruijff(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(),
									   5300, 5250, 5375, 5, 0, 20, 1, 0, 5, 1, 0, 5);  
				else if (sigShape == "Apollonios")
					fitter.makeApollonios(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(),
										  5300, 5250, 5375, 5, 0, 20, 1, -5, 10, 1, -5, 10, 1, 0, 5);
				else if (sigShape == "Amoroso")
					fitter.makeAmoroso(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(),
									   5300, 5250, 5375, 5, 0, 20, 1.5, 0, 10, 2.3, 0, 5);
				else if (sigShape == "Hypatia")
					fitter.makeHypatia(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(),
									   1, -1, 3, 1, 0, 10, 0, 5, 0, 20, 5300, 5250, 5375, 1, -5, 5, 2, 0, 10);
				else if (sigShape == "Hypatia2")
					fitter.makeHypatia2(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(),
										1, -2, 3, 1, 0, 10, 0, 5, 0, 20, 5300, 5250, 5375, 1, -5, 5, 2, 0, 10, 1, -5, 5, 2, 0, 10);
				else if (sigShape == "DoubleGauss")
					fitter.makeDoubleGauss(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(),
										   5300,5250,5375,0.,-200.,200.,20,8,40,2.,1.,10.,0.5);
				else if (sigShape == "DoubleCB2")
					if ((*it_modes).find("Bd") != std::string::npos)
						fitter.makeDoubleCB(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(),
											5279, 5269, 5389, 8, 0, 20, 2., 1., 5., 1, 0, 5, -1, -5, 0, 1, 0, 5, 1, 0 ,5, 0.5);
					else
						fitter.makeDoubleCB(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(),
											5366, 5356, 5376, 8, 0, 25, 2., 1., 5., 1, 0, 5, -1, -5, 0, 1, 0, 5, 1, 0 ,5, 0.5);
				else
					if ((*it_modes).find("Bd") != std::string::npos)
						fitter.makeDoubleCB(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(),
											5279, 5269, 5389, 8, 0, 20, 1, 0, 15, -1, -15, 0, 1, 0, 15, 1, 0 ,15, 0.5);
					else
						fitter.makeDoubleCB(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(),
											5366, 5356, 5376, 8, 0, 25, 1, 0, 15, -1, -15, 0, 1, 0, 15, 1, 0 ,15, 0.5);
	std::cout << "INFO: PDFs ready" << std::endl;
	//================================================================================
  
	//================================================================================
	// Import the dataset 
	//================================================================================
	TString dataDir = getenv("V0HHFITTERDATA");
	std::string data_aux = (dataDir).Data(); 
	//std::string basedir = data_aux+"/KShh/MonteCarlo/";
	std::string basedir;
	if (mcOrigin == "Rafael")	  
		basedir = "/afs/cern.ch/work/r/rsilvaco/V0hhFitter/KShh/MonteCarlo/";
	else if (mcOrigin == "Louis")
		//	  basedir = "root://eoslhcb.cern.ch//eos/lhcb/user/l/lohenry/MonteCarlo/";
		basedir = "root://eoslhcb.cern.ch//eos/lhcb/user/l/lohenry/KShhFit/MonteCarlo/";
	//		basedir = "/afs/cern.ch/work/l/lohenry/Data/KShhFit/MonteCarlo/";
	TFile *file = 0;
	TTree* tree = 0;
  
	for(std::vector<std::string>::iterator it_year     = years.begin();   it_year  != years.end();   ++it_year) {
		for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
			for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
				std::cout << "INFO: Acquiring " << *it_year << " " << *it_modes << " " << *it_KS << std::endl;
				std::vector<std::string> name_split;
				boost::split(name_split,(*it_modes),boost::is_any_of("2"));
				name_split[1].erase(0,2);
				if (mcOrigin == "Rafael")
					if (name_split[1] == "piK"){
						file = TFile::Open( (basedir+(*it_year)+"/KShhFit/"+selectionType+"/KS"+(name_split[1])+"/"+(name_split[0])+"2KSKpi-MC-"+(*it_year)+"-MagAll.root").c_str(), "READ" );
					} else{
						file = TFile::Open( (basedir+(*it_year)+"/KShhFit/"+selectionType+"/KS"+(name_split[1])+"/"+(name_split[0])+"2KS"+(name_split[1])+"-MC-"+(*it_year)+"-MagAll.root").c_str(), "READ" );
					}
				else
					file = TFile::Open( (basedir+selectionType+"/"+(name_split[0])+"2KS"+name_split[1]+"-MC-"+(*it_year)+"-"+(*it_KS)+"-"+selectionType+"-MagAll.root").c_str(), "READ" );
				if (mcOrigin == "Rafael")
					tree = dynamic_cast<TTree*>( file->Get( ("B2KShh"+(*it_KS)+"/B2"+(name_split[1])+"KS").c_str() ) );
				else if (mcOrigin == "Louis")
					tree = dynamic_cast<TTree*>( file->Get( ("B2"+(name_split[1])+"KS").c_str() ) );
				if (name_split[0].find("Bd") != std::string::npos)
					fitter.makeMassDataSet( tree, massvar, ((name_split[0])+"2KS"+(name_split[1])+(*it_KS)+"_"+(*it_year)).c_str(), "", "" ) ; 
				else
					fitter.makeMassDataSet( tree, massvar, ((name_split[0])+"2KS"+(name_split[1])+(*it_KS)+"_"+(*it_year)).c_str(), "", "") ; 
				file->Close();  // close file 
			}
		}
	}
  
	fitter.combineDataSets();
	//================================================================================
  
	//================================================================================
	// Create PDFs and then add by csv the pdfs that should be used for the mass 
	//================================================================================
	fitter.createPDFSets();
  
	// Signal modes
	for(std::vector<std::string>::iterator it_year = years.begin();   it_year  != years.end();   ++it_year) {
		for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
			for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
				fitter.addPDFs(((*it_modes)+(*it_KS)+"_"+(*it_year)).c_str(), ((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str());
				fitter.addYields(((*it_modes)+(*it_KS)+"_"+(*it_year)).c_str());
			}
		}
	}
  
	fitter.buildAddPdfs();
	fitter.buildModel();
  
	fitter.saveWS((saveDir+"WS/MC-Sig-Samples-WS-"+mcOrigin+"-"+selectionType+"-"+option+".root").c_str());
	std::cout << "INFO: Saved the workspace in " << saveDir+"WS/MC-Sig-Samples-WS-"+mcOrigin+"-"+selectionType+"-"+option+".root" << std::endl;
	return 0;
}
