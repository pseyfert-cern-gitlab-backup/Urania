#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>

//ROOT
#include "TAxis.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH2D.h"
#include "TMath.h"
#include "TPad.h"
#include "TROOT.h"

// RooFit
#include "RooHist.h"
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

//Multiplicaton of two numbers with errors
std::pair<double,double> mult(double v1, double eV1, double v2, double eV2)
{
	double rel1 = eV1/v1;
	double rel2 = eV2/v2;
	return std::make_pair(v1*v2,v1*v2*TMath::Sqrt(rel1*rel1+rel2*rel2));
}

//Division two numbers with errors
std::pair<double,double> ratio(double v1, double eV1, double v2, double eV2)
{
	double ratio = v1/v2;
	double rel1 = eV1/v1;
	double rel2 = eV2/v2;
	return std::make_pair(ratio,ratio*TMath::Sqrt(rel1*rel1+rel2*rel2));
}

bool piToK(std::string origin,std::string destination)
{
	if (origin == "pipi")
		return true;
	else if (origin == "KK")
		return false;
	else if (destination == "pipi")
		return false;
	else if (destination == "KK")
		return true;
	return true;
}


void readOneVal(std::string fileName, std::string name, double& val, double& errLo, double& errHi)
{
	std::ifstream f(fileName.c_str());
	double initVal = val;
	double initHi  = errHi;
	double initLo  = errLo;
	std::string line;
	while(getline(f,line)) {
		std::string t_name, t_val, t_errHi, t_errLo;
		std::istringstream stream(line);
		stream >> t_name;
		if (t_name == name)
			{
				stream >> t_val;
				stream >> t_errHi;
				stream >> t_errLo;
				val   = std::atof(t_val.c_str());
				errLo = std::atof(t_errHi.c_str());
				errHi = std::atof(t_errLo.c_str());
				break;
			}
	}
	if (val == initVal || errHi == initHi || errLo == initLo)
		{
			std::cout << "FATAL: Did not find the name " << name << " in " << fileName << "!" << std::endl;
			std::exit(1);
		}
	return;
}

std::pair<double,double> readConstraintVal(std::string sel, std::string mode, std::string rec, std::string year, std::string KS,std::string type)
{
	TString shortMode(mode.c_str());
	shortMode.ReplaceAll("Bd2KS","");
	shortMode.ReplaceAll("Bs2KS","");
	std::string shortName(shortMode.Data());
	std::string cfName  = "eff_"+type+"_"+sel+"_"+mode+"_"+year+"_"+KS+"_"+rec;
	std::string refName = "eff_"+type+"_"+sel+"_"+mode+"_"+year+"_"+KS+"_"+shortName;
	double val_CF(-1.) ,err_CFLo(-1.) ,err_CFHi(-1.);
	double val_Ref(-1.),err_RefLo(-1.),err_RefHi(-1.);
	std::string fileType = (type == "PID")?"PID":"";
	std::string rootDir = getenv("V0HHFITTERROOT");
	readOneVal(rootDir+"/KShh/scripts/ConstraintsCFAll.txt"    ,cfName ,val_CF ,err_CFLo ,err_CFHi );
	readOneVal(rootDir+"/KShh/scripts/ConstraintsREFAll.txt"   ,refName,val_Ref,err_RefLo,err_RefHi);

	double ratio = val_CF/val_Ref;
	double rel_CFHi  = err_CFHi/val_CF;
	//	double rel_CFLo  = err_CFLo/val_CF;
	double rel_RefHi = err_RefHi/val_Ref;
	//	double rel_RefLo = err_RefLo/val_Ref;
	double err_Hi = ratio * sqrt(rel_CFHi*rel_CFHi + rel_RefHi*rel_CFHi);
	//	double err_Lo = ratio * sqrt(rel_CFLo*rel_CFLo + rel_RefLo*rel_CFLo);
	//	std::cout << mode << " " << rec << " " << year << " " << KS << " " << type << std::endl;
	//	std::cout << err_CFHi << " " << err_CFLo << " " << err_RefHi << " " << err_RefLo << std::endl;
	//	std::cout << ratio << " = " << val_CF << "/" << val_Ref << std::endl;
	return std::make_pair(ratio,err_Hi);
}


//Reads a value in the database.
void readVal(double& val, sqlite3* db, TString instruction, unsigned int column, bool noZero)
{
	sqlite3_stmt *stmt = NULL;	
	int retval;
	retval = sqlite3_prepare_v2(db, instruction.Data(), -1, &stmt, 0);
	while(1) {
		retval = sqlite3_step(stmt);
		if (retval == SQLITE_ROW) {
			const unsigned char* link = sqlite3_column_text(stmt, column);
			std::stringstream str_ss;
			str_ss << link;
			std::string ss = (str_ss).str();
			val = atof((ss).c_str()); 
			break;
		} else if(retval == SQLITE_DONE) { 
			std::cout << ":'( " << instruction << " " << column << std::endl;
			break;
		}		
	}
	if (noZero && val == 0)
		{
			std::cout << "Value equals 0!!" << std::endl;
			std::exit(1);
		}
}

void fillBRs(std::map<std::string,std::pair<double,double> > &BRs, std::string cat, std::string invMass, double min, double max)
{
	BRs[cat+"-"+invMass] = std::make_pair(min,max);
}

//Kind of an exception. Kind of.
void fastExit(const char* msg)
{
  std::cout << msg << std::endl;
  assert(0);
}

int main(int argc, char* argv[])
{    
	//	RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
	std::time_t start_time = std::time(NULL);
	std::time_t temp_time = std::time(NULL);
	bool Bs_blind(true);
	std::string selectionType("Loose");
	std::string Int_info = "";    
	std::set<std::string> integral_range;
	//	Double_t sigma_input(0.);
	std::string name("Standard");
	std::string sigShape("DoubleCB");
	std::string sigModel("Standard");
	std::string combModel("Standard");
	std::string crossModel("Standard");
	std::string partModel("Standard");
	std::string option("Standard");
	std::string dataOrigin("Louis");
	std::string protonCut("strong");
	unsigned int nCPU(4);
	boost::program_options::options_description decisions("Option Arguments");
	decisions.add_options()
		("help,h" , "produce help message")
		("selectionType,s", boost::program_options::value<std::string>(&selectionType), "specify which selection has been used in the sample: Loose, Tight, DP1 or DP2")
		("blind,b", boost::program_options::value<bool>(&Bs_blind), "specify the Bs2KSKK mass window to be unblind by setting 'false'. Default is set to blind.")
		("integral,i", boost::program_options::value<std::string>(&Int_info), "provide information about the mass window integration to produce final sample for Dalitz plot analysis. Please provide in the format 'All' or 'Bs2KSpipi-2', where 2 stands for 2sigma of the measured value. Notice that in the case of the KSKpi spectra the corresponding charge hypothesis needs to be specified, e.g. Bs2KSKpi_DP1")
		//		("toyMC,t", boost::program_options::value<Double_t>(&nExp), "optional (kFalse = default): specify the number os ToyMC experiments to generate/fit for the fitted model. Note: in the case of blind fit, the scenario of Bs2KSKK with yield==0 is considered")
		("name,n"    , boost::program_options::value<std::string>(&name), "")
		("sigShape"  , boost::program_options::value<std::string>(&sigShape), "")
		("sigModel"  , boost::program_options::value<std::string>(&sigModel), "")
		("combModel"  , boost::program_options::value<std::string>(&combModel), "")
		("crossModel", boost::program_options::value<std::string>(&crossModel), "")
		("partModel" , boost::program_options::value<std::string>(&partModel), "")
		("option"    , boost::program_options::value<std::string>(&option),"")
		("nCPU"    , boost::program_options::value<unsigned int>(&nCPU),"precises the suffix of the used constraints file")
		("data"      , boost::program_options::value<std::string>(&dataOrigin),"allows to change the origin of the data samples")
		("protonCut,c"      , boost::program_options::value<std::string>(&protonCut),"")
		;
	
	boost::program_options::variables_map vm;
	boost::program_options::store( boost::program_options::parse_command_line( argc, argv, decisions ), vm );
	boost::program_options::notify( vm );
	
	if( vm.count("help") ) {
		std::cout << decisions << std::endl;
		std::exit(0);
	}
	if (vm.count("blind"))
		if (!Bs_blind)
			std::cout << "WARNING: The Bs2KSKK mass windows will be considered unblind!" << std::endl;

	//	if (vm.count("toyMC")){ 
		//		ToyMC = true;
	//		std::cout << "INFO: " << nExp << " ToyMC experiments will be generated after the fit to data" << std::endl;
	//	}

	if (vm.count("integral")){
		std::vector<std::string> split_name;
		boost::split(split_name,Int_info,boost::is_any_of("-"));
		std::string range_name = split_name[0];
		TString sigmaRange = split_name[1];
		if (Int_info.find("All") == std::string::npos) { 
			std::cout << "INFO: Integrating fit results of mode " <<  split_name[0] << " within " << split_name[1] << " sigma" << std::endl;
			integral_range.insert(range_name);
			//			sigma_input =  atof(sigmaRange);
		} else if (Int_info.find("All") != std::string::npos) {
			std::cout << "INFO: Integrating fit results for all modes within " << split_name[1] << " sigma" << std::endl;
			integral_range.insert("Bd2KSpipi");
			integral_range.insert("Bs2KSpipi");
			integral_range.insert("Bd2KSKpi_DP1");
			integral_range.insert("Bs2KSKpi_DP1");
			integral_range.insert("Bd2KSKpi_DP2");
			integral_range.insert("Bs2KSKpi_DP2");
			integral_range.insert("Bd2KSKK");
			integral_range.insert("Bs2KSKK");
			//			sigma_input =  atof(sigmaRange);
		} else {
			std::cout << "ERROR: Please provide an apropriate name e.g.: Bs2KSKpi_2" << std::endl;
		}
	}

	//	if (vm.count("protonCut"))
	if (protonCut == "strong")
		{
			std::cout << "INFO: Proton cut option enabled." << std::endl;
			if (protonCut == "strong")
				protonCut = "-StrongPcut";
			else
				std::cout << "ERROR: No real proton cut applied: unknown proton cut (" << protonCut << ")" << std::endl;
		}
	std::string fileName("constraints-DataFit-"+option);  
	KShhConstraints::testFile(fileName);
	if (!vm.count("crossModel"))
		crossModel = KShhConstraints::readString(fileName,"crossModel");
	if (!vm.count("partModel"))
		partModel = KShhConstraints::readString(fileName,"partModel");
	
	//Copy the constraints files...
	TString dir         = getenv("V0HHFITTERROOT");
	std::string V0hhDir = dir.Data();
	std::string saveDir = V0hhDir+"/KShh/"; 
	std::string dir_plots = (saveDir+"Data-Fit/plots/").c_str();
	bool likelihoodScan = KShhConstraints::readBool(fileName,"likelihoodScan");
	if (!likelihoodScan)
		dir_plots += selectionType+"/";
	else
		dir_plots += "LikelihoodScan/";
	std::ifstream inFile((V0hhDir+"/KShh/Constraints/"+fileName+".txt").c_str());
	std::ofstream outFile((dir_plots+fileName+".txt").c_str());
	outFile << inFile.rdbuf();
	
	//================================================================================
	// Create instance of the fitter and observables
	//================================================================================
	std::cout << "Read all options: " 
			  << (std::time(NULL) - start_time) << " "
			  << (std::time(NULL) - temp_time)
			  << std::endl;
	temp_time = std::time(NULL);
	V0hhFit::SimultaneousFitter fitter( "B2KShhMCFit", "B0(d,s) --> KS h' h Fit" );
	
	fitter.setGlobalKillBelowError( RooFit::FATAL ); // Monitoring
	fitter.setnCPU( nCPU ); // Sets the number of CPUs to run the minimisation in parallel
	
	TString massvar("B_M"); // Observable name to be used in the fit
	
	// Path to local area to save informations of the fit 
	//  TString dir         = getenv("V0HHFITTERROOT");
	//  std::string V0hhDir = dir.Data();
	//  std::string saveDir = V0hhDir+"/KShh/"; 
	std::string combOption = (combModel.find("PolSlopes") != std::string::npos)? "PolSlopes":"Exponential";
	bool changeData = KShhConstraints::readBool(fileName,"changeData");
	if (changeData)
		fitter.loadWS((saveDir+"WS/Data-WS-"+option+"-"+dataOrigin+"-"+selectionType+"-"+combOption+protonCut+"-"+name+".root").c_str(),"newDesktop",false);  
	else
		fitter.loadWS((saveDir+"WS/Data-WS-Standard-"+dataOrigin+"-"+selectionType+"-"+combOption+protonCut+"-"+name+".root").c_str(),"newDesktop",false);  
	fitter.set1DFitVarName( massvar );
	fitter.setNegativeYields(true);
	//  fitter.make1DFitVar( xmin, xmax, "MeV/c^{2}", "m(#it{K^{0}_{#rm S} h^{+} h^{-}})" ); 
	fitter.setBins("B_M", 100, "cache"); // Cache for the ArgusConvGauss
	fitter.setModelName("model");
	fitter.setDataSetName("data");
	//================================================================================
	
	//================================================================================
	// Definition of the modes 
	//================================================================================
	
	// Define possible combinations of signal, crossfeed and partially bkg modes 
	std::vector<std::string> years;
	std::vector<std::string> modes;
	std::vector<std::string> KS_cat;
	std::vector<std::string> invMass;
	std::multimap<std::string,std::string> cross_feed;
	std::multimap<std::string,std::string> part_reco;
	std::map<std::string,std::vector<std::string> > misID;
	
	// MC signal modes 
	modes.push_back("Bd2KSpipi");
	modes.push_back("Bs2KSpipi");
	modes.push_back("Bd2KSKpi");
	modes.push_back("Bs2KSKpi");
	modes.push_back("Bd2KSpiK");
	modes.push_back("Bs2KSpiK");
	modes.push_back("Bd2KSKK");
	modes.push_back("Bs2KSKK");
	
	// KS categories
	KS_cat.push_back("DD");
	KS_cat.push_back("LL");
	
	// Various years
	years.push_back("2011");
	years.push_back("2012a");
	years.push_back("2012b");
	
	// Invariant masses 
	invMass.push_back("pipi");
	invMass.push_back("Kpi");
	invMass.push_back("piK");
	invMass.push_back("KK");
	
	//Possible misIDs
	misID["pipi"].push_back("Kpi");
	misID["pipi"].push_back("piK");
	misID["Kpi" ].push_back("pipi");
	misID["Kpi" ].push_back("KK");
	misID["KK"  ].push_back("Kpi");
	misID["KK"  ].push_back("piK");	
	
	// Crossfeeds 
	bool isIncluded(false);
	for (std::vector<std::string>::iterator itMode1 = modes.begin() ; itMode1 != modes.end() ; ++itMode1)
		for (std::vector<std::string>::iterator itMode2 = invMass.begin() ; itMode2 != invMass.end() ; ++itMode2)
			{
				if (itMode1->find(itMode2->c_str()) != std::string::npos)
					continue;
				if (*itMode2 == std::string("piK") || itMode1->find("piK") != std::string::npos)
					continue;
				isIncluded = KShhConstraints::readKey(fileName,*itMode1,*itMode2);
				if (isIncluded)
					cross_feed.insert(std::make_pair(itMode1->c_str(),itMode2->c_str()));
				if (isIncluded && *itMode2 == std::string("Kpi"))
					cross_feed.insert(std::make_pair(itMode1->c_str(),"piK"));
			}
	if (protonCut.find("-Strong") == std::string::npos)
		{
			if (KShhConstraints::readKey(fileName,"Lb2KS0ppi","pipi"))
				cross_feed.insert(std::make_pair("Lb2KS0ppi","pipi"));
			
			if (KShhConstraints::readKey(fileName,"Lb2KS0ppi","Kpi"))
				{
					cross_feed.insert(std::make_pair("Lb2KS0ppi","Kpi"));
					cross_feed.insert(std::make_pair("Lb2KS0ppi","piK"));
				}
			if (KShhConstraints::readKey(fileName,"Lb2KS0ppi","KK"))
				cross_feed.insert(std::make_pair("Lb2KS0ppi","KK"));
			
			if (KShhConstraints::readKey(fileName,"Lb2KS0pK","pipi"))
				cross_feed.insert(std::make_pair("Lb2KS0pK","pipi"));
			
			if (KShhConstraints::readKey(fileName,"Lb2KS0pK","Kpi"))
				{
					cross_feed.insert(std::make_pair("Lb2KS0pK","Kpi"));
					cross_feed.insert(std::make_pair("Lb2KS0pK","piK"));
				}
			if (KShhConstraints::readKey(fileName,"Lb2KS0pK","KK"))
				cross_feed.insert(std::make_pair("Lb2KS0pK","KK"));
		}
	// Partially reconstruct bkg
	std::vector<std::string> categories;
	categories.push_back("Charmless-Bd");
	categories.push_back("Charmless-Bs");
	categories.push_back("Charmed-Bd");
	categories.push_back("Charmed-Bs");
	categories.push_back("Charmonia-Bd");
	categories.push_back("Charmonia-Bs");
	categories.push_back("MissGamNR-Bd");
	categories.push_back("MissGamNR-Bs");
	categories.push_back("MissGamRes-Bd");
	categories.push_back("MissGamRes-Bs");
	categories.push_back("Arbitrary-Bd-pi");
	categories.push_back("Arbitrary-Bs-pi");
	categories.push_back("Arbitrary-Bd-gam");
	categories.push_back("Arbitrary-Bs-gam");
	
	//  std::multimap<std::string,std::multimap<std::string,std::pair<double,double> > > BRs;
	bool branchingRatios       = KShhConstraints::readBool(fileName,"branchingRatios" );
	std::map<std::string,std::pair<double,double> > BRs;
	//	bool alterKK_BRs = KShhConstaints::readBool(fileName,"alterKK_BRs");
	fillBRs(BRs,"Charmless-Bd","pipi",2.00, 500.);
	fillBRs(BRs,"Charmless-Bd","Kpi" ,0.02,  50.);
	fillBRs(BRs,"Charmless-Bd","KK"  ,2.00, 500.);
	fillBRs(BRs,"Charmless-Bs","pipi",0.00,  50.);
	fillBRs(BRs,"Charmless-Bs","Kpi" ,0.45, 500.);
	fillBRs(BRs,"Charmless-Bs","KK"  ,0.00,  10.);
	
	fillBRs(BRs,"Charmed-Bd","pipi",28.00, 100.00);
	fillBRs(BRs,"Charmed-Bd","Kpi" , 1.60,  50.00);
	fillBRs(BRs,"Charmed-Bd","KK"  , 0.04,  10.00);
	//  fillBRs(BRs,"Charmed-Bd","KK"  , 0.00, 0.00);
	//	fillBRs(BRs,"Charmed-Bs","pipi", 1.00,  50.00);
	fillBRs(BRs,"Charmed-Bs","pipi", 0.10,  50.00);
	fillBRs(BRs,"Charmed-Bs","Kpi" , 1.00, 100.00);
	fillBRs(BRs,"Charmed-Bs","KK"  , 0.10,  50.00);
	
	fillBRs(BRs,"Charmonia-Bd","pipi",0.80,5.00);
	fillBRs(BRs,"Charmonia-Bd","Kpi" ,0.00,5.00);
	fillBRs(BRs,"Charmonia-Bd","KK"  ,1.10,5.00);
	fillBRs(BRs,"Charmonia-Bs","pipi",0.02,5.00);
	fillBRs(BRs,"Charmonia-Bs","Kpi" ,0.00,5.00);
	fillBRs(BRs,"Charmonia-Bs","KK"  ,0.00,5.00);
	
	fillBRs(BRs,"MissGamNR-Bd","pipi",1.95,0.22);
	fillBRs(BRs,"MissGamNR-Bd","Kpi" ,0.00,1.00);
	fillBRs(BRs,"MissGamNR-Bd","KK"  ,0.00,1.00);
	fillBRs(BRs,"MissGamNR-Bs","pipi",0.00,1.00);
	fillBRs(BRs,"MissGamNR-Bs","Kpi" ,0.00,1.00);
	fillBRs(BRs,"MissGamNR-Bs","KK"  ,0.00,1.00);
	
	fillBRs(BRs,"MissGamRes-Bd","pipi",3.30,0.2);
	fillBRs(BRs,"MissGamRes-Bd","Kpi" ,0.00,0.1);
	fillBRs(BRs,"MissGamRes-Bd","KK"  ,0.00,0.1);
	fillBRs(BRs,"MissGamRes-Bs","pipi",0.00,0.1);
	fillBRs(BRs,"MissGamRes-Bs","Kpi" ,0.00,0.1);
	fillBRs(BRs,"MissGamRes-Bs","KK"  ,0.00,0.1);
	bool from5100 = KShhConstraints::readBool(fileName,"from5100");
	for (std::vector<std::string>::iterator itCat = categories.begin() ; itCat != categories.end() ; ++itCat)
		for (std::vector<std::string>::iterator itMode = invMass.begin() ; itMode != invMass.end() ; ++itMode)
			{	
				if (*itMode == std::string("piK"))
					continue;
				//				isIncluded = KShhConstraints::readKey(fileName,*itCat,*itMode);
				isIncluded = KShhConstraints::readKey(fileName,*itCat,*itMode) && (!from5100 || (from5100 && itCat->find("Bd") == std::string::npos));
				if (isIncluded)
					part_reco.insert(std::make_pair(itMode->c_str(),itCat->c_str()));
				if (isIncluded && (*itMode) == "Kpi")
					part_reco.insert(std::make_pair("piK",itCat->c_str()));
			}
	if (branchingRatios)
		{
			for (std::multimap<std::string,std::string>::iterator it = part_reco.begin() ; it != part_reco.end() ; ++it)
				{
					if (it->first.find("piK") == std::string::npos)
						if (it->second.find("Gam") == std::string::npos)
							fitter.addParameter(("BR-"+it->second+"-"+it->first).c_str(),BRs[it->second+"-"+it->first].first*0.00001,BRs[it->second+"-"+it->first].second*0.00001);
					std::cout << "INFO: Branching fractions enabled. Added the parameter " << "BR-"+it->second+"-"+it->first << " to the fitter." << std::endl; 
				}
	  }
	
	//================================================================================
	
	//================================================================================
	// Set parameter constraints and and anything that is constant or has Gaussian 
	// constraints. Can also set blinding of variables here too.
	//================================================================================    
	
	//=============================================//
	// ------------------------------------------- //
	//            Signal parametrisation           // 
	// ------------------------------------------- //
	//=============================================//
	//fitter.getWS()->Print("V");
	//Sets yield starting values to something sensible.
	for(std::vector<std::string>::iterator it_years = years.begin(); it_years != years.end(); ++it_years)
		for (std::vector<std::string>::iterator it_invmass = invMass.begin(); it_invmass != invMass.end(); ++it_invmass)
			for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
				{ 
					std::string temp = "KS"+(*it_invmass)+(*it_KS)+"_"+(*it_years)+"_pdf_KS"+(*it_invmass)+(*it_KS)+"_"+(*it_years)+"_Yield";
					std::string modeName;
					if (it_invmass->find("Kpi") != std::string::npos || it_invmass->find("piK") != std::string::npos)
						modeName = "Bd2";
					else					  
						modeName = "Bs2";
					modeName += temp;
					if (selectionType=="Tight")
						{
							fitter.setParameterValue(modeName.c_str(),0.5*fitter.getParameterValue(modeName.c_str()),false);
							//							if (it_invmass->find("KK") != std::string::npos && it_KS->find("LL") != std::string::npos)
							//								fitter.setParameterValue(modeName.c_str(),0.*fitter.getParameterValue(modeName.c_str()),false);
							if (it_invmass->find("KK") != std::string::npos)
								fitter.setParameterValue(("combinatoric_KS"+(*it_invmass)+(*it_KS)+"_"+(*it_years)+"_pdf_KS"+(*it_invmass)+(*it_KS)+"_"+(*it_years)+"_Yield").c_str(),0.1*fitter.getParameterValue(modeName.c_str()),false);
						}
					if (selectionType=="Loose")
						{
							fitter.setParameterValue(modeName.c_str(),0.2*fitter.getParameterValue(modeName.c_str()),false);
							if (it_invmass->find("KK") != std::string::npos && it_KS->find("LL") != std::string::npos)
								fitter.setParameterValue(modeName.c_str(),0.1*fitter.getParameterValue(modeName.c_str()),false);
							if (it_invmass->find("KK") != std::string::npos)
								fitter.setParameterValue(("combinatoric_KS"+(*it_invmass)+(*it_KS)+"_"+(*it_years)+"_pdf_KS"+(*it_invmass)+(*it_KS)+"_"+(*it_years)+"_Yield").c_str(),0.8*fitter.getParameterValue(modeName.c_str()),false);
						}
				}
	
	
	// Set Bs2KSKK blind in case of true 
	if (Bs_blind)
		for(std::vector<std::string>::iterator it_years     = years.begin();   it_years  != years.end();   ++it_years)
			for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
				fitter.blindParameter(("Bs2KSKK"+(*it_KS)+"_"+(*it_years)+"_pdf_KSKK"+(*it_KS)+"_"+(*it_years)+"_Yield").c_str(), 200);
	
	KShhConstraints::setSignalModel(fitter,
									//				  sigModel,
									sigShape,
									years,
									modes,
									KS_cat,
									option
									);
	
	std::cout << "Signal model is done: " 
			  << (std::time(NULL) - start_time) << " "
			  << (std::time(NULL) - temp_time)
			  << std::endl;
	
	//Constraint the masses
	bool massIndex(false);
	//  massIndex = true;
	if (massIndex)
		{
			fitter.addParameter("DM_missPi",135.,135.);
			fitter.setParameterConstant("DM_missPi");
			fitter.addParameter("DM_missGam",0.,0.);
			fitter.setParameterConstant("DM_missGam");
		}
	for(std::vector<std::string>::iterator it_years     = years.begin();   it_years  != years.end();   ++it_years)
		for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
			for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco)
				{
					std::string miss = (it_part_reco->second.find("Gam") != std::string::npos)? "DM_missGam" : "DM_missPi";
					std::string meson = (it_part_reco->second.find("Bs") != std::string::npos)? "Bs":"Bd";
					double mass = (meson=="Bd")?5285:5370;
					double missMass = (miss=="DM_missGam")?0:135;
					if (massIndex)
						{
							fitter.addConstraint(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_sigma").c_str()
												 ,"@0"
												 ,"Sigma(pipi)(DD)(2011)"
												 );	  
							
							fitter.addConstraint(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_threshold").c_str()
												 ,"@0-@1"
												 ,("mu("+meson+")(2011),"+miss).c_str()
												 );	  
						}
					else
						{
							fitter.setParameterValue(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_threshold").c_str(),mass - missMass, true);
							fitter.setParameterValue(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_sigma").c_str(), 20., true);  
						}
				}  
	for(std::vector<std::string>::iterator it_years     = years.begin();   it_years  != years.end();   ++it_years)
		for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco)
			for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
				{
					if (it_part_reco->second.find("Arbitrary") == std::string::npos)
						continue;
					//				  if (it_part_reco->first.find("piK") == std::string::npos)
					//					  {
					fitter.addConstraint(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_slope").c_str(),
										 "@0",
										 //											   (it_part_reco->second+"_"+it_part_reco->first+"_slope").c_str());
										 (it_part_reco->second+"_pipi_slope").c_str());
					fitter.addConstraint(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_power").c_str()
										 ,"@0"
										 //											   ,(it_part_reco->second+"_"+it_part_reco->first+"_power").c_str());
										 ,(it_part_reco->second+"_pipi_power").c_str());
					//					  }
					//				  else
					//					  {
					//						  fitter.addConstraint(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_slope").c_str(),
					//											   "@0",
					//											   (it_part_reco->second+"_Kpi_slope").c_str());
					//						  fitter.addConstraint(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_power").c_str()
					//											   ,"@0"
					//											   ,(it_part_reco->second+"_Kpi_power").c_str());
					//					  }
					std::cout << "Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_power" 
							  << " " 
							  << it_part_reco->second+"_"+it_part_reco->first << std::endl;
				}
	
	temp_time = std::time(NULL);
	
	// ------------------------------------------- //
	// ------------------------------------------- //
	//              Crossfeed Yields               // 
	// ------------------------------------------- //
	// ******************************************* //
	//Constraint the masses
	/*
	  for(std::vector<std::string>::iterator it_years = years.begin(); it_years != years.end(); ++it_years)
      for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)	
	  for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross)
	  {
	  if (it_cross->second.find("piK") != std::string::npos)
	  fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)+"_pdf_mu").c_str(),
										   "@0",
										   ("CrossFeed_"+(it_cross->first)+"_as_KpiDD_2011_pdf_mu").c_str());
				  else
					  fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)+"_pdf_mu").c_str(),
										   "@0",
										   ("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+"DD_2011_pdf_mu").c_str());
				  
			  }
  */
 	// Create constraints to the crossfeed yields
	std::cout << "INFO: Reading the crossfeeds constraints from " << fileName << std::endl;
	bool crossFeedCriterion       = KShhConstraints::readBool(fileName,"crossFeedCriterion" );
	bool crossFeedSameForYears    = KShhConstraints::readBool(fileName,"crossFeedSameForYears"); 
	bool crossFeedSameForDDLL     = KShhConstraints::readBool(fileName,"crossFeedSameForDDLL");  
	bool crossFeedFacForYears     = KShhConstraints::readBool(fileName,"crossFeedFacForYears");  
	bool crossFeedSameFacForYears = KShhConstraints::readBool(fileName,"crossFeedSameFacForYears");  
	bool crossFeedFacForDDLL      = KShhConstraints::readBool(fileName,"crossFeedFacForDDLL");  
	bool crossFeedFacForCF        = KShhConstraints::readBool(fileName,"crossFeedFacForCF");  
	bool crossFeedSameForPiK      = KShhConstraints::readBool(fileName,"crossFeedSameForPiK");  
	bool crossFeedConstant        = KShhConstraints::readBool(fileName,"crossFeedConstant");  
	Double_t globalCFerr_factor   = KShhConstraints::readValue(fileName,"crossFeedFactor");	
	//Checking for inconsistencies
	if (crossFeedConstant)
		{
			crossFeedSameForYears = false;
			crossFeedSameForDDLL  = false;
			crossFeedFacForYears  = false;
			crossFeedFacForDDLL   = false;
			crossFeedFacForCF     = false;
			crossFeedSameForPiK   = true;
		}
	if (crossFeedSameForYears && (crossFeedFacForYears || crossFeedFacForYears))
		{
			std::cout << "WARNING: Crossfeeds are both SAME and FAC wrt years. SAME overrides this." << std::endl;
			crossFeedFacForYears = false;
			crossFeedSameFacForYears = false;
		}
	if (!crossFeedFacForYears && crossFeedSameFacForYears)
		{
			std::cout << "WARNING: Crossfeeds are not factorized wrt years, yet the factor should be the same? Setting crossFeedSameFacForYears to false." << std::endl;
			crossFeedSameFacForYears = false;
		}
	if (crossFeedSameForDDLL && crossFeedFacForDDLL)
		{
			std::cout << "WARNING: Crossfeeds are both SAME and FAC wrt DD-LL. SAME overrides this." << std::endl;
			crossFeedFacForDDLL = false;
		}
	if (crossFeedFacForCF)
		{
			std::cout << "Factorization between crossfeeds is NOT IMPLEMENTED YET. Setting to false." << std::endl;      
			crossFeedFacForCF = false;
		}
	for(std::vector<std::string>::iterator it_years = years.begin(); it_years != years.end(); ++it_years) {
		for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
			for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {	
				std::string baseYear = (crossFeedSameForYears|| crossFeedFacForYears)? "2011":*it_years;
				std::string baseMode = (crossFeedSameForDDLL || crossFeedFacForDDLL )? "DD"  :*it_KS;	
				std::string baseFrac = (crossFeedFacForCF)? 
					"frac_cross_Bs2KSKpi_as_KK"+baseMode+"_"+baseYear:
					"frac_cross_"+(it_cross->first)+"_as_"+(it_cross->second)+baseMode+"_"+baseYear;
				if (!crossFeedFacForCF && crossFeedSameForPiK && it_cross->second.find("piK") != std::string::npos)
					baseFrac = "frac_cross_"+(it_cross->first)+"_as_Kpi"+baseMode+"_"+baseYear;
				if (fitter.getWS()->var(baseFrac.c_str()) == NULL)
					fitter.addParameter(baseFrac.c_str(), 0., 1.0);       
				
				std::string cf_constName = "CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)+"_pdf_KS"+(it_cross->second)+(*it_KS)+"_"+(*it_years)+"_Yield";
				
				// Creating the formula
				//Base yields
				std::string formula("@0*"),dependents(baseFrac);
				unsigned int nDependents(1);
				if ((it_cross->first).find("Bs") != std::string::npos) {
					dependents += 
						",Bs2KSKpi"+(*it_KS)+"_"+(*it_years)+"_pdf_KSKpi"+(*it_KS)+"_"+(*it_years)+"_Yield"+
						",Bs2KSpiK"+(*it_KS)+"_"+(*it_years)+"_pdf_KSpiK"+(*it_KS)+"_"+(*it_years)+"_Yield";
					formula += "(@1+@2)";
					nDependents = 3;
				} else if ( it_cross->first == "Bd2KSKpi"){
					dependents +=
						",Bd2KSKpi"+(*it_KS)+"_"+(*it_years)+"_pdf_KSKpi"+(*it_KS)+"_"+(*it_years)+"_Yield"+
						",Bd2KSpiK"+(*it_KS)+"_"+(*it_years)+"_pdf_KSpiK"+(*it_KS)+"_"+(*it_years)+"_Yield";
					formula += "(@1+@2)";
					nDependents = 3;
				} else if ( it_cross->first == "Bd2KSpipi"){
					dependents += ","+(it_cross->first)+(*it_KS)+"_"+(*it_years)+"_pdf_KSpipi"+(*it_KS)+"_"+(*it_years)+"_Yield";
					formula += "@1";
					nDependents = 2;
				} else if ( it_cross->first == "Bd2KSKK"){
					dependents += ","+(it_cross->first)+(*it_KS)+"_"+(*it_years)+"_pdf_KSKK"+(*it_KS)+"_"+(*it_years)+"_Yield";
					formula += "@1";
					nDependents = 2;
				} else if ( it_cross->first.find("Lb2") != std::string::npos){
					dependents += ",Bd2KSpipi"+(*it_KS)+"_"+(*it_years)+"_pdf_KSpipi"+(*it_KS)+"_"+(*it_years)+"_Yield";
					formula += "@1";
					nDependents = 2;
				} else {
					std::cout << "ERROR: There is something wrong with the configuration" << std::endl;
				}
				//Factorization
				if (crossFeedFacForDDLL && it_KS->find("LL") !=std::string::npos)
					{
						if (fitter.getWS()->var("kFrac_CF_KS") == NULL)
					  fitter.addParameter("kFrac_CF_KS",0.,5.);
						std::stringstream ss_dependents;
						ss_dependents << nDependents;
						formula += "*@"+ss_dependents.str();
						dependents += ",kFrac_CF_KS";
						nDependents++;
					}
				if (crossFeedFacForYears && it_years->find("2012") != std::string::npos)
					{
						if (!crossFeedSameFacForYears)
							{
								if (fitter.getWS()->var("kFrac_CF_2012a") == NULL)
									fitter.addParameter("kFrac_CF_2012a",0.,5.);
								if (fitter.getWS()->var("kFrac_CF_2012b") == NULL)
									fitter.addParameter("kFrac_CF_2012b",0.,5.);
							}
						else
							if (fitter.getWS()->var("kFrac_CF_2012") == NULL)
								fitter.addParameter("kFrac_CF_2012",0.,5.);
						
						std::stringstream ss_dependents;
						ss_dependents << nDependents;
						formula += "*@"+ss_dependents.str();
						if (!crossFeedSameFacForYears)
							if (it_years->find("2012a") != std::string::npos)
								dependents += ",kFrac_CF_2012a";
							else if (it_years->find("2012b") != std::string::npos)
								dependents += ",kFrac_CF_2012b";
							else{}
						else
							dependents += ",kFrac_CF_2012";
						nDependents++;
					}
				fitter.addConstraint(cf_constName.c_str(),formula.c_str(),dependents.c_str());
			}
		}
	}
	//	fitter.addGaussianConstraint("kSig(LL)(2011)",1.,0.01);  
	// Create the gaussian constraints (import from DB)  
	
	std::string dbTable = ((crossFeedCriterion))? V0hhDir+"/KShh/dB/efficiencyTable-PIDcrit.db":V0hhDir+"/KShh/dB/efficiencyTable.db"; 
	sqlite3 *db;
	int rc = sqlite3_open(dbTable.c_str(), &db);
	if (rc) {
		std::fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	} else {
		fprintf(stderr, "Opened database successfully\n");
	}
	
	// Variables initialisation
	std::string sig_eff_str(""), sig_err_str("");
	std::string cross_eff_str(""), cross_err_str("");
	std::string misID_eff_str(""), misID_err_str("");
	std::string total_eff_str(""), total_err_str("");
	Double_t factor_cross(0.), factor_cross_err(0.);
	//	const char* sqlSig;
	if (globalCFerr_factor == 0.)
		globalCFerr_factor = 1.;
	if (globalCFerr_factor != 1.)
		std::cout << "WARNING: Modified CF error by a factor " << globalCFerr_factor << std::endl;
	std::map<std::string,std::pair<double,double> > crossConstraints;
	for(std::vector<std::string>::iterator it_years = years.begin(); it_years != years.end(); ++it_years) {
		for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
			for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
				if ((crossFeedSameForYears || crossFeedFacForYears) && it_years->find("2012") != std::string::npos)
					continue;
				if ((crossFeedSameForDDLL || crossFeedFacForDDLL)  && it_KS->find("LL") != std::string::npos)
					continue;
				if ((crossFeedSameForPiK) && it_cross->second.find("piK") != std::string::npos)
					continue;
				if (dataOrigin == "Rafael")
					{
						Double_t Eff_Sel_sig(0.), Err_Sel_sig(0.);
						Double_t Eff_Sel_cross(0.), Err_Sel_cross(0.);
						Double_t Eff_MisID(0.), Err_MisID(0.);
						Double_t Eff_PIDcrit(0.), Err_PIDcrit(0.);
						Double_t Eff_Total(0.), Err_Total(0.);
						TString dbLinkSig   = "";
						TString dbLinkCross = "";
						if (((it_cross->second) == "Kpi") || ((it_cross->second) == "piK"))
							dbLinkSig = "SELECTION LIKE '"+selectionType+
								"' AND MODE LIKE 'Bs2KS"+(it_cross->second)+
								"' AND KSTYPE LIKE '"+(*it_KS)+
								"' AND YEAR LIKE '"+(*it_years)+
								"' AND TREENAME LIKE '"+(it_cross->second)+"'";
						else
							dbLinkSig = "SELECTION LIKE '"+selectionType+
								"' AND MODE LIKE 'Bd2KS"+(it_cross->second)+
								"' AND KSTYPE LIKE '"+(*it_KS)+
								"' AND YEAR LIKE '"+(*it_years)+
								"' AND TREENAME LIKE '"+(it_cross->second)+"'";
						
						dbLinkCross  = "SELECTION LIKE '"+selectionType+
							"' AND MODE LIKE '"+(it_cross->first)+
							"' AND KSTYPE LIKE '"+(*it_KS)+
							"' AND YEAR LIKE '"+(*it_years)+
							"' AND TREENAME LIKE '"+(it_cross->second)+"'";
						// Retrieve signal efficiency information 
						TString aux = "SELECT * from EFFICIENCY WHERE "+dbLinkSig;
						//						sqlSig = aux.Data();
						if (crossFeedCriterion)
							{
								readVal(Eff_Sel_sig,db,aux,15,true);
								readVal(Err_Sel_sig,db,aux,16,true);
							}
						else
							{
								readVal(Eff_Sel_sig,db,aux,13,true);
								readVal(Err_Sel_sig,db,aux,14,true);
							}
						// Retrive crossfeed efficiency information
						TString aux_cross = "SELECT * from EFFICIENCY WHERE "+dbLinkCross;
						readVal(Eff_Sel_cross,db,aux_cross,9 ,true);
						readVal(Err_Sel_cross,db,aux_cross,10,true);
						readVal(Eff_MisID    ,db,aux_cross,11,true);
						readVal(Err_MisID    ,db,aux_cross,12,true);
						if (crossFeedCriterion)
							{
								readVal(Eff_PIDcrit,db,aux_cross,13,false);
								readVal(Err_PIDcrit,db,aux_cross,14,false);
								readVal(Eff_Total  ,db,aux_cross,15,false);
								readVal(Err_Total  ,db,aux_cross,16,false);
							}
						else
							{
								readVal(Eff_Total  ,db,aux_cross,13,true);
								readVal(Err_Total  ,db,aux_cross,14,true);
							}
						// Factor and associated error
						//						std::pair<double,double> ratio_Sel = ratio(Eff_Sel_cross,Err_Sel_cross,Eff_Sel_sig,Err_Sel_sig);
						//						std::pair<double,double> misID_Sel = mult(ratio_Sel.first,ratio_Sel.second,Eff_MisID,Err_MisID);
						// Creating the Gaussian constraints
						std::pair<double,double> ratioTotal = ratio(Eff_Total,Err_Total,Eff_Sel_sig,Err_Sel_sig);
						
						factor_cross     = ratioTotal.first;
						factor_cross_err = ratioTotal.second;
					}
				else if (dataOrigin == "Louis")
					{
						if (it_cross->first.find("Lb2") == std::string::npos)
							{
								std::pair<double,double> facCrossSel = readConstraintVal(selectionType,it_cross->first,it_cross->second,*it_years,*it_KS,"SelTISTOS");
								std::pair<double,double> facCrossPID = readConstraintVal(selectionType,it_cross->first,it_cross->second,*it_years,*it_KS,"PID");
								std::pair<double,double> facCross = mult(facCrossSel.first,facCrossSel.second,facCrossPID.first,facCrossPID.second);
								crossConstraints[(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)] = std::make_pair(facCross.first,facCross.second);
								factor_cross     = facCross.first;
								factor_cross_err = facCross.second * globalCFerr_factor;								
							}
						else
							{
								factor_cross     = 0.3;
								factor_cross_err = 0.3;
							}
					}
				if (it_cross->first == "Bd2KSKK")
					{
						std::cout << "WARNING: Modified Bd2KSKK -> Kpi error." << std::endl;
						factor_cross_err *= 20./globalCFerr_factor;
					}
				if (((it_cross->second) == "Kpi") || ((it_cross->second) == "piK")){
					if (!crossFeedConstant)
						fitter.addGaussianConstraint(("frac_cross_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)).c_str(), 0.5*factor_cross, 0.5*factor_cross_err);
					else
						fitter.setParameterValue(("frac_cross_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)).c_str(), 0.5*factor_cross, true);
				} 
				else {
					if (!crossFeedConstant)
						fitter.addGaussianConstraint(("frac_cross_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)).c_str(), factor_cross, factor_cross_err);
					else
						fitter.setParameterValue(("frac_cross_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)).c_str(), factor_cross, true);
				}
			}
		}
	}

	if (crossFeedFacForDDLL || crossFeedFacForYears)
		std::cout << "WARNING: The following values are hardcoded, be wary." << std::endl;
	if (crossFeedFacForDDLL)
		fitter.addGaussianConstraint("kFrac_CF_KS",1.06,0.05);
	if (crossFeedFacForYears && !crossFeedSameFacForYears)
		{
			fitter.addGaussianConstraint("kFrac_CF_2012a",0.882,0.041);
			fitter.addGaussianConstraint("kFrac_CF_2012b",0.945,0.037);
		}
	if (crossFeedFacForYears && crossFeedSameFacForYears)
		fitter.addGaussianConstraint("kFrac_CF_2012",0.916,0.036);
	
	// ------------------------------------------- //
	//            Combinatorial slope              // 
	// ------------------------------------------- //
	KShhConstraints::setCombinatorialModel(fitter,
										   years,
										   invMass,
										   KS_cat,
										   option,
										   combOption
										   );  
	
	// ------------------------------------------- //
	//  Partially reconstructed yields constraints // 
	// ------------------------------------------- //
	std::cout << "INFO: Reading the part. reco. constraints from " << fileName << std::endl;
	bool     partRecoSameModes     = KShhConstraints::readBool(fileName,"partRecoSameModes" );
	bool     partRecoSameDDLL      = KShhConstraints::readBool(fileName,"partRecoSameDDLL" );
	bool     partRecoSameYears     = KShhConstraints::readBool(fileName,"partRecoSameYears");
	bool     partRecoFacDDLL       = KShhConstraints::readBool(fileName,"partRecoFacDDLL" );
	bool     partRecoFacMode       = KShhConstraints::readBool(fileName,"partRecoFacMode" );
	bool     partRecoFacYears      = KShhConstraints::readBool(fileName,"partRecoFacYears");
	bool     partRecoSameFacYears  = KShhConstraints::readBool(fileName,"partRecoSameFacYears");
	bool     partRecoSamePiK       = KShhConstraints::readBool(fileName,"partRecoSamePiK");
	bool     partRecoConstant      = KShhConstraints::readBool(fileName,"partRecoConstant");
	Double_t partRecoFactor        = KShhConstraints::readValue(fileName,"partRecoFactor");
	//Checking for inconsistencies
	if (partRecoConstant)
		{
			partRecoSameDDLL = false;
			partRecoSameYears = false;
			partRecoFacDDLL = false;
			partRecoFacYears = false;
			partRecoSamePiK = false;
		}
	if (partRecoSameYears && (partRecoFacYears || partRecoSameFacYears))
		{
			std::cout << "WARNING: PartReco are both SAME and FAC wrt years. SAME overrides this." << std::endl;
			partRecoFacYears = false;
			partRecoSameFacYears = false;
		}
	if (!partRecoFacYears && partRecoSameFacYears)
		{
			std::cout << "WARNING: PartReco are not factorized wrt years, yet the factor should be the same? Setting partRecoSameFacYears to false." << std::endl;
			partRecoSameFacYears = false;
		}
	if (partRecoSameDDLL && partRecoFacDDLL)
		{
			std::cout << "WARNING: PartReco are both SAME and FAC wrt DD-LL. SAME overrides this." << std::endl;
			partRecoFacDDLL = false;
		}
	
	// Create the yield constraints parameters.
	for(std::vector<std::string>::iterator it_years       = years.begin();    it_years    != years.end();    ++it_years)
		for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco)
			for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS != KS_cat.end(); ++it_KS) {
				if (it_part_reco->second.find("Arbitrary") != std::string::npos)
					continue;
				std::string baseYear = (*it_years);
				std::string baseKS = (*it_KS);
				std::string baseSpectrum = (it_part_reco->first);
				std::string baseMode = it_part_reco->second;
				if (partRecoFacMode)
					baseMode = "Charmed-Bd";
				if (partRecoSameYears || partRecoFacYears)
					baseYear = "2011";
				if (partRecoSameDDLL || partRecoFacDDLL)
					baseKS = "DD";
				if (partRecoSamePiK && it_part_reco->second == "piK")
					baseSpectrum = "Kpi";
				std::string fracName = ("frac_"+baseSpectrum+"_"+it_part_reco->second+"_"+baseKS+"_"+baseYear);
				if (fitter.getWS()->var(fracName.c_str()) == NULL)
					{
						if ((it_part_reco->second.find("MissGam") == std::string::npos)) //&& (!partRecoSameModes || it_part_reco->second.find("Charmed-Bd") != std::string::npos))
							fitter.addParameter((fracName).c_str(),1.,0.,1000000.);	
						else if (it_part_reco->second.find("MissGam") != std::string::npos)
							fitter.addParameter((fracName).c_str(),0.,1.);	
					}
			}  
	
	// ------------------------------------------- //  
	// Create the yield constraints    
	// ------------------------------------------- //  

  std::map<std::string,std::pair<double,double> > partRecoConstraints;
  for(std::vector<std::string>::iterator it_years       = years.begin();    it_years    != years.end();    ++it_years)
	  for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco)
		  for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS != KS_cat.end(); ++it_KS) {
			  if (it_part_reco->second.find("Arbitrary") != std::string::npos)
				  continue;
			  std::string baseYear = (*it_years);
			  std::string baseKS = (*it_KS);
			  std::string baseSpectrum = it_part_reco->first;
			  std::string baseMode =  it_part_reco->second;
			  if (partRecoSameYears || partRecoFacYears)
				  baseYear = "2011";
			  if (partRecoSameDDLL || partRecoFacDDLL)
				  baseKS = "DD";
			  if (partRecoSamePiK && baseSpectrum == "piK")
				  baseSpectrum = "Kpi";
			  if (partRecoSameModes && it_part_reco->second.find("MissGam") == std::string::npos)
				  baseMode = "Charmed-Bd";
				
			  std::string fracName = ("frac_"+baseSpectrum+"_"+baseMode+"_"+baseKS+"_"+baseYear);
			  std::string bkg_yieldName    = "Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_KS"+(it_part_reco->first)+(*it_KS)+"_"+(*it_years)+"_Yield";
			  std::string sig_yieldRefName = "";
			  // Creating the formula
			  //Base yields
			  if ((it_part_reco->first == "Kpi") || (it_part_reco->first == "piK"))
					sig_yieldRefName = "Bs2KSKpi"+(*it_KS)+"_"+(*it_years)+"_pdf_KSKpi"+(*it_KS)+"_"+(*it_years)+"_Yield";
				else
					sig_yieldRefName = "Bd2KS"+(it_part_reco->first)+(*it_KS)+"_"+(*it_years)+"_pdf_KS"+(it_part_reco->first)+(*it_KS)+"_"+(*it_years)+"_Yield";	
				std::string formula("@0*@1"),dependents(fracName+","+sig_yieldRefName);
				unsigned int nDependents(2);
				//BRs?
				if (branchingRatios)
					if (it_part_reco->second.find("Gam") == std::string::npos)							
						{
							std::stringstream ss_dependents;
							ss_dependents << nDependents;
							formula += "*@"+ss_dependents.str();
							if (it_part_reco->first.find("piK") == std::string::npos)
								dependents += ",BR-"+it_part_reco->second+"-"+it_part_reco->first;
							else
								dependents += ",BR-"+it_part_reco->second+"-Kpi";
							nDependents++;
						}
				
				//Factorization
				if (partRecoFacDDLL && it_KS->find("LL") !=std::string::npos)
					{
						if (fitter.getWS()->var("kFrac_PR_DDLL") == NULL)
							fitter.addParameter("kFrac_PR_DDLL",0.,5.);
						std::stringstream ss_dependents;
						ss_dependents << nDependents;
						formula += "*@"+ss_dependents.str();
						dependents += ",kFrac_PR_DDLL";
						nDependents++;
					}
				if (partRecoFacYears && it_years->find("2012") != std::string::npos)
					{
						if (!partRecoSameFacYears)
							{
								if (fitter.getWS()->var("kFrac_PR_2012a") == NULL)
									fitter.addParameter("kFrac_PR_2012a",0.,5.);
								if (fitter.getWS()->var("kFrac_PR_2012b") == NULL)
									fitter.addParameter("kFrac_PR_2012b",0.,5.);
							}
						else
							if (fitter.getWS()->var("kFrac_PR_2012") == NULL)
								fitter.addParameter("kFrac_PR_2012",0.,5.);
						
						std::stringstream ss_dependents;
						ss_dependents << nDependents;
						formula += "*@"+ss_dependents.str();
						if (!partRecoSameFacYears)
							if (it_years->find("2012a") != std::string::npos)
								dependents += ",kFrac_PR_2012a";
							else if (it_years->find("2012b") != std::string::npos)
								dependents += ",kFrac_PR_2012b";
							else{}
						else
							dependents += ",kFrac_PR_2012";
						nDependents++;
					}
				fitter.addConstraint(bkg_yieldName.c_str(), formula.c_str(), dependents.c_str());				
		  }
  // Create the gaussian constraints (import from DB)
  std::string dbTable_pr = V0hhDir+"/KShh/dB/";
  if (branchingRatios)
	  dbTable_pr += "partiallyRecoYielTable-BF.db"; 
  else
	  dbTable_pr += "partiallyRecoYielTable.db"; 
  
  sqlite3 *db_pr;
  int rc_pr = sqlite3_open(dbTable_pr.c_str(), &db_pr);
  if (rc_pr) {
	  std::fprintf(stderr, "Can't open partially reco database: %s\n", sqlite3_errmsg(db_pr));
	  exit(0);
	} else {
	  fprintf(stderr, "Opened partially reconstructed bkg database successfully\n");
  }
  
	// Variables initialisation

	const char *sqlRatio_pr;
	std::string frac_bkg_str(""), frac_bkg_err_str("");
	Double_t Fraction_bkg_val(0.), Fraction_err_bkg_val(0.);
	for(std::vector<std::string>::iterator it_years                       = years.begin();        it_years    != years.end();      ++it_years) {
		for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
			for(std::vector<std::string>::iterator it_KS                   = KS_cat.begin();      it_KS      != KS_cat.end();    ++it_KS) {
				if (it_part_reco->second.find("Arbitrary") != std::string::npos)
					continue;		  
				if ((partRecoSameYears || partRecoFacYears) && it_years->find("2012") != std::string::npos)
					continue;
				if ((partRecoSameDDLL || partRecoFacDDLL)  && it_KS->find("LL") != std::string::npos)
					continue;
				if ((partRecoSamePiK) && it_part_reco->first.find("piK") != std::string::npos)
					continue;
				if(partRecoSameModes && it_part_reco->second.find("Charmed-Bd") == std::string::npos)
					if (it_part_reco->second.find("MissGam") == std::string::npos)
						continue;
				sqlite3_stmt* stmt_pr   = NULL;
				int retval_pr;
				TString dbLinkPR = "SELECTION LIKE '"+selectionType+"' AND PARTRECO LIKE '"+it_part_reco->second+"' AND TREENAME LIKE '"+(it_part_reco->first)+"' AND KSTYPE LIKE '"+(*it_KS)+"' AND YEAR LIKE '"+(*it_years)+"'";
				std::cout << dbLinkPR << std::endl;
				
				// Retrieve the estimation of the fraction information 
				TString info_pr = "SELECT * from BKGYIELD WHERE "+dbLinkPR;
				sqlRatio_pr     = info_pr.Data();
				retval_pr       = sqlite3_prepare_v2(db_pr, sqlRatio_pr, -1, &stmt_pr, 0);
				if (retval_pr){
					printf("Selecting data from DB Failed (err_code=%d)\n", retval_pr);
					return 0;
				}
				while(1) {
					retval_pr = sqlite3_step(stmt_pr);
					if (retval_pr == SQLITE_ROW) {
						// Fraction mean value for each bkg 
						const unsigned char* frac_bkgLink    = sqlite3_column_text(stmt_pr, 14);
						std::stringstream frac_bkg_tmp_str;
						frac_bkg_tmp_str << frac_bkgLink;
						frac_bkg_str = (frac_bkg_tmp_str).str();
						Fraction_bkg_val = atof((frac_bkg_str).c_str()); 
						// Fraction mean error value for each bkg 
						const unsigned char* frac_bkgErrLink = sqlite3_column_text(stmt_pr, 15);
						std::stringstream frac_bkg_err_tmp_str;
						frac_bkg_err_tmp_str << frac_bkgErrLink;
						frac_bkg_err_str = (frac_bkg_err_tmp_str).str();
						Fraction_err_bkg_val = atof((frac_bkg_err_str).c_str()); 
						break;
					} 
					else if(retval_pr == SQLITE_DONE) { 
						std::cout << "WARNING: REQUEST NOT FOUND:" << std::endl << dbLinkPR << std::endl;
						break;
					}
				}	
				if (it_part_reco->second.find("Gam") != std::string::npos && it_part_reco->second.find("Arbitrary") == std::string::npos)
					{
						double BRval = BRs[(it_part_reco->second)+"-"+(it_part_reco->first)].first  * 1e-5;
						double BRerr = BRs[(it_part_reco->second)+"-"+(it_part_reco->first)].second * 1e-5;
						std::cout << BRval << " " << BRerr << std::endl;
						partRecoConstraints["frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)+"_"+(*it_KS)+"_"+(*it_years)] 
							= std::make_pair(Fraction_bkg_val*BRval,TMath::Sqrt(Fraction_err_bkg_val*Fraction_err_bkg_val*BRval*BRval+
																				Fraction_bkg_val    *Fraction_bkg_val    *BRerr*BRerr));
					}
				else
					partRecoConstraints["frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)+"_"+(*it_KS)+"_"+(*it_years)] 
						= std::make_pair(Fraction_bkg_val,partRecoFactor*Fraction_err_bkg_val);
				Fraction_bkg_val = 0;
				Fraction_err_bkg_val = 0;	
			}
		}
	}
	for (std::map<std::string,std::pair<double,double> >::iterator it = partRecoConstraints.begin() ; it != partRecoConstraints.end() ; ++it)
		if (partRecoConstant)
			fitter.setParameterConstant(it->first.c_str(),it->second.first);
		else
			fitter.addGaussianConstraint(it->first.c_str(),it->second.first,it->second.second);        
	
	if (fitter.getWS()->var("kFrac_PR_2012") != NULL)
		fitter.addGaussianConstraint("kFrac_PR_2012",0.811,0.078);
	if (fitter.getWS()->var("kFrac_PR_2012a") != NULL)
		fitter.addGaussianConstraint("kFrac_PR_2012a",0.75,0.10);
	if (fitter.getWS()->var("kFrac_PR_2012b") != NULL)
		fitter.addGaussianConstraint("kFrac_PR_2012b",0.90,0.12);
	if (fitter.getWS()->var("kFrac_PR_DDLL") != NULL)
		fitter.addGaussianConstraint("kFrac_PR_DDLL",1.,0.1);  
	/*
	if (branchingRatios)
		for (std::multimap<std::string,std::string>::iterator it = part_reco.begin() ; it != part_reco.end() ; ++it)
			if (it->second.find("Gam") != std::string::npos)
				fitter.addGaussianConstraint(("BR-"+it->second+"-"+it->first).c_str(),
											 BRs[it->second+"-"+it->first].first*0.00001,
											 BRs[it->second+"-"+it->first].second*0.00001);
	*/	
	//================================================================================    
	
	//================================================================================
	// Finally perform the fit to the data and the plot some results.
	//================================================================================  
	
	std::cout << "Ready for the fit: "
			  << (std::time(NULL) - start_time) << " "
			  << (std::time(NULL) - temp_time)
			  << std::endl;
	temp_time = std::time(NULL);
	//  fitter.buildNewWorkspace("SimplifiedWS");
	if (likelihoodScan)
		{
			//This is not very interesting to people just wanting to use the fitter.
			gROOT->SetBatch(true);
			fitter.performFit("fitResults",false);
			RooFitResult *fitRes = fitter.getFitResult( "fitResults" ) ;
			RooArgList listOfParams_temp = fitRes->floatParsFinal();
			TIterator *itParams_temp = listOfParams_temp.createIterator();
			TNamed *obj_temp;	
			
			while ((obj_temp = (TNamed*) itParams_temp->Next()) != NULL)
				if (std::string(obj_temp->GetName()).find("BR") != std::string::npos)
					fitter.setParameterConstant(obj_temp->GetName());
			
			std::string varToScan("BR-Charmless-Bd-pipi");
			double centerVal = ((RooRealVar*) &(fitRes->floatParsFinal()[fitRes->floatParsFinal().index(varToScan.c_str())]))->getVal();
			int nPoints = 30;
			double step = centerVal*0.05;
			TGraph *graph = NULL;
			graph = new TGraph(nPoints);
			for (int i = 0 ; i < nPoints ; i++)
				{
					for(std::vector<std::string>::iterator it_years       = years.begin();     it_years    != years.end();     ++it_years)
						//fitter.setParameterValue(("c1(Comb)(KK)("+*it_years+")").c_str(),centerVal - (nPoints/2 - i)*step,true);
						fitter.setParameterValue("BR-Charmless-Bd-pipi",centerVal - (nPoints/2 - i)*step,true);
					std::stringstream ss;
					ss << i;
					std::string fitName = "likelihoodScan_"+ss.str();
					fitter.performFit((fitName).c_str(),false);
					RooFitResult dataResults( *fitter.getFitResult( fitName.c_str() ));
					graph->SetPoint(i,centerVal - (nPoints/2 - i)*step,dataResults.minNll());
					std::ofstream scanFile;
					scanFile.open((dir_plots+"ScanValues.txt").c_str(),std::ofstream::app);
					scanFile << centerVal - (nPoints/2 - i)*step << " " << dataResults.minNll() << std::endl;
					scanFile.close();
					//Plotting
					for(std::vector<std::string>::iterator it_years       = years.begin();     it_years    != years.end();     ++it_years)
						for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
							{
								std::stringstream ss;
								ss << centerVal - (nPoints/2 - i)*step;
								std::string strVal = ss.str();
								fitter.plotMassAndPull( (dir_plots+selectionType+"-KSpipi"+(*it_KS)+"_"+(*it_years)+"_Fit_"+strVal).c_str(),
														"m(#it{K}_{S}^{0}#it{K^{+}K^{#font[122]{-}}}) [MeV/#it{c}^{2}]",
														("KSKK"+(*it_KS)+"_"+(*it_years)).c_str(),fitName.c_str(),"log" ) ;
								fitter.plotMassAndPull( (dir_plots+selectionType+"-KSpipi"+(*it_KS)+"_"+(*it_years)+"_Fit_"+strVal).c_str(),
														"m(#it{K}_{S}^{0}#it{K^{+}K^{#font[122]{-}}}) [MeV/#it{c}^{2}]",
														("KSKK"+(*it_KS)+"_"+(*it_years)).c_str(),fitName.c_str() ) ;
							}
						}
				}
			TCanvas *C = new TCanvas("C","C",1000,1000);
			graph->Draw("A*");
			C->SaveAs((dir_plots+"LikelihoodScan.png").c_str());
			delete C;
			delete graph;

		}

	//Performs the fit once to extract the BRs
	for (std::map<std::string,std::pair<double,double> >::iterator it = partRecoConstraints.begin() ; it != partRecoConstraints.end() ; ++it)
		fitter.setParameterConstant(it->first.c_str()); // We set the fractions to a constant value
	fitter.performFit("firstResults",false);
	
	for (std::map<std::string,std::pair<double,double> >::iterator it = partRecoConstraints.begin() ; it != partRecoConstraints.end() ; ++it)
		fitter.setParameterConstant(it->first.c_str(),false); // We release the fractions.
	//Setting the BRs constant
	fitter.getFitResult("firstResults")->Print();
	RooFitResult *fitResults = fitter.getFitResult( "firstResults" ) ;
	RooArgList listOfParams_temp = fitResults->floatParsFinal();
	
	TIterator *itParams_temp = listOfParams_temp.createIterator();
	TNamed *obj_temp;	
	
	while ((obj_temp = (TNamed*) itParams_temp->Next()) != NULL)
		if (std::string(obj_temp->GetName()).find("BR") != std::string::npos)
			fitter.setParameterConstant(obj_temp->GetName());

	//FINAL RESULT
	fitter.performFit("fitResults",false);
	fitResults = fitter.getFitResult( "fitResults" ) ;
	fitResults->Print("");
	
	//LAST FIT, sWEIGHTS-style
	
    RooArgList myList = fitResults->floatParsFinal();
	
    TIterator *myIt = myList.createIterator();
    while ((obj_temp = (TNamed*) myIt->Next()) != NULL)
		{
			std::cout << obj_temp->GetName() << std::endl;
			if (std::string(obj_temp->GetName()).find("Yield") == std::string::npos)
				fitter.setParameterConstant(obj_temp->GetName());
			//We have to save the Gaussian constraints...
			if (fitter.getWS()->var((std::string(obj_temp->GetName())+"_gaussconstraint_mean").c_str())  != NULL)
				fitter.setParameterValue((std::string(obj_temp->GetName())+"_gaussconstraint_mean").c_str(),fitter.getParameterValue(obj_temp->GetName()),true);
		}	
	fitter.performFit("sWeights",false);
	(fitter.getFitResult("sWeights"))->Print();
	
	std::cout << "Fit done: "
			  << (std::time(NULL) - start_time) << " "
			  << (std::time(NULL) - temp_time)
			  << std::endl;
	temp_time = std::time(NULL);

	//================================================================================  
	
	//================================================================================
	// Do some nice plotting of the invariant mass spectra, this will do residual and
	//================================================================================  
	//  std::string dir_plots = (saveDir+"Data-Fit/plots/"+selectionType+"/").c_str();  

	fitter.setPlotBins( massvar, 100 ); // Set binning
	std::string prefixPlots = (combOption == "PolSlopes")?"Polynomial-":"Exponential-";
	if (from5100)
		prefixPlots += "from5100-";
	dir_plots += option + "-";
	dir_plots += dataOrigin + "-";
	dir_plots += prefixPlots;
	const char* fitResultsName = "fitResults";
	if (protonCut.find("Strong") != std::string::npos)
		dir_plots += "StrongPcut-";
	for(std::vector<std::string>::iterator it_years       = years.begin();     it_years    != years.end();     ++it_years) {
		for(std::vector<std::string>::iterator it_invMass = invMass.begin();  it_invMass != invMass.end();  ++it_invMass) {
			for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
				if ((*it_invMass) == "pipi"){
					fitter.plotMassAndPull((dir_plots+selectionType+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"-"+name).c_str(),
										   "m(#it{K}_{S}^{0}#it{#pi^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]",
										   ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), fitResultsName) ;
					fitter.plotMassAndPull((dir_plots+selectionType+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"-"+name).c_str(),
										   "m(#it{K}_{S}^{0}#it{#pi^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]",
										 ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), fitResultsName, "log") ;
				} else if ((*it_invMass) == "Kpi"){
					fitter.plotMassAndPull((dir_plots+selectionType+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"-"+name).c_str(),
										   "m(#it{K}_{S}^{0}#it{K^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]",
										   ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), fitResultsName, "log") ;
					fitter.plotMassAndPull((dir_plots+selectionType+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"-"+name).c_str(),
										   "m(#it{K}_{S}^{0}#it{K^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]",
										   ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), fitResultsName) ;
				} else if ((*it_invMass) == "piK"){
					fitter.plotMassAndPull((dir_plots+selectionType+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"-"+name).c_str(),
										   "m(#it{K}_{S}^{0}#it{K^{#font[122]{-}}#pi^{+}}) [MeV/#it{c}^{2}]", 
										   ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), fitResultsName, "log") ;
					fitter.plotMassAndPull((dir_plots+selectionType+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"-"+name).c_str(),
										   "m(#it{K}_{S}^{0}#it{K^{#font[122]{-}}#pi^{+}}) [MeV/#it{c}^{2}]",
										   ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), fitResultsName) ;
				} else {
					fitter.plotMassAndPull( (dir_plots+selectionType+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"-"+name).c_str(),
											"m(#it{K}_{S}^{0}#it{K^{+}K^{#font[122]{-}}}) [MeV/#it{c}^{2}]",
											("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(),fitResultsName,"log" ) ;
					fitter.plotMassAndPull( (dir_plots+selectionType+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"-"+name).c_str(),
											"m(#it{K}_{S}^{0}#it{K^{+}K^{#font[122]{-}}}) [MeV/#it{c}^{2}]",
											("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(),fitResultsName ) ;
				}
			}
		}
	}
	std::cout << "Plots done: "
			  << (std::time(NULL) - start_time) << " "
			  << (std::time(NULL) - temp_time)
			  << std::endl;
	temp_time = std::time(NULL);
	
	//================================================================================
	// Save everything in the workspace!
	//================================================================================  
	fitter.saveWS( (saveDir+"WS/Fit-WS-"+option+"-"+dataOrigin+"-"+selectionType+"-"+combOption+"-"+name+".root").c_str() );
	std::cout << "INFO: Saved the workspace in " 
			  << saveDir+"WS/Fit-WS-"+option+"-"+dataOrigin+"-"+selectionType+"-"+combOption+"-"+name+".root"
			  << std::endl;
	//================================================================================
	
	return 0;	
}
