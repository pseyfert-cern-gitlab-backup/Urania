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
#include "TH2D.h"
#include "TMath.h"
#include "TPad.h"
#include "TROOT.h"

// RooFit
#include "RooAddPdf.h"
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

double calcIntRatio(RooWorkspace *w, std::string name, double minMass, double maxMass)
{
    RooAbsPdf *myPDF = NULL;
	std::cout << name << std::endl;
	name.erase(name.find("_pdf")+4,std::string::npos);
	std::cout << name << std::endl;
    while (w->pdf(name.c_str()) != NULL)
        {
            myPDF = w->pdf(name.c_str());
            name +="_new";
        }	
	RooRealVar* mass = w->var("B_M");
    mass->setRange("normalRange",5000,5800);
	//    mass->setRange("reducedRange",mass->getMin(),mass->getMax());
    mass->setRange("reducedRange",minMass,maxMass);
    RooRealVar* globalInt = (RooRealVar*) myPDF->getNormObj(new RooArgSet(),new RooArgSet(*mass),new TNamed("normalRange",""));
    RooRealVar* windowInt = (RooRealVar*) myPDF->getNormObj(new RooArgSet(),new RooArgSet(*mass),new TNamed("reducedRange",""));
	std::cout << "INFO: Setting the integral ratio for "+name+" to: " << (windowInt->getVal()/globalInt->getVal()) << " (" << minMass << "," << maxMass << ")" << std::endl;
    return (windowInt->getVal()/globalInt->getVal());
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
	RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
	std::time_t start_time = std::time(NULL);
	std::time_t temp_time = std::time(NULL);
	bool Bs_blind(true);
	std::string selectionType("Loose");
	std::string Int_info = "";    
	std::set<std::string> integral_range;
	std::string name("Standard");
	std::string sigShape("DoubleCB");
	std::string sigModel("Standard");
	std::string crossModel("Standard");
	std::string partModel("Standard");
	std::string combModel("Exponential");
	std::string option("sWeights");
	std::string dataOrigin("Louis");
	std::string dataFitModel("Standard");
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
		("crossModel", boost::program_options::value<std::string>(&crossModel), "")
		("combModel", boost::program_options::value<std::string>(&combModel), "")
		("partModel" , boost::program_options::value<std::string>(&partModel), "")
		("option"    , boost::program_options::value<std::string>(&option),"")
		("dataFitModel"    , boost::program_options::value<std::string>(&dataFitModel),"")
		("nCPU"    , boost::program_options::value<unsigned int>(&nCPU),"")
		("protonCut,c"      , boost::program_options::value<std::string>(&protonCut),"")
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
	if (protonCut == "strong")
		protonCut = "-StrongPcut";
  
	std::string fileName("constraints-DataFit-"+option);  
	std::string fileDataFitModel("constraints-DataFit-"+dataFitModel);  
	KShhConstraints::testFile(fileName);
	KShhConstraints::testFile(fileDataFitModel);
	if (!vm.count("crossModel"))
		crossModel = KShhConstraints::readString(fileDataFitModel,"crossModel");
	if (!vm.count("partModel"))
		partModel = KShhConstraints::readString(fileDataFitModel,"partModel");
  
	//Copy the constraints files...
	TString dir         = getenv("V0HHFITTERROOT");
	std::string V0hhDir = dir.Data();
	std::string saveDir = V0hhDir+"/KShh/"; 
	std::string dir_plots = (saveDir+"Data-Fit/plots/").c_str();
	dir_plots += "sWeights/";
	dir_plots += selectionType+"/";
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

	//	std::string WSname = (KShhConstraints::readBool(fileName,"changeDataSet"))?
	//		"Data-WS-"+option+"-"+dataFitModel+"-"+dataOrigin+"-"+selectionType+"-"+combModel+"-StrongPcut-"+name+".root":
	//		"Data-WS-"+dataFitModel+"-"+dataOrigin+"-"+selectionType+"-"+combModel+"-StrongPcut-"+name+".root";
	std::string WSname = "Data-WS-"+option+"-"+dataOrigin+"-"+selectionType+"-"+combModel+"-StrongPcut-"+name+".root";
	fitter.loadWS((saveDir+"WS/"+WSname).c_str(),"newDesktop",false);  
	fitter.set1DFitVarName( massvar );
	//  fitter.make1DFitVar( xmin, xmax, "MeV/c^{2}", "m(#it{K^{0}_{#rm S} h^{+} h^{-}})" ); 
	fitter.setPlotBins( massvar,40 );
	fitter.setBins("B_M", 100, "cache"); // Cache for the ArgusConvGauss
	fitter.setModelName("model");
	fitter.setDataSetName("data");
	//	fitter.getWS()->var("B_M")->Print("v");
	//	std::cout << fitter.getWS()->var("B_M")->getMin() << std::endl;
	//	return 0;
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
  
	// Partially-reconstructed bkg
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
  
	for (std::vector<std::string>::iterator itCat = categories.begin() ; itCat != categories.end() ; ++itCat)
		for (std::vector<std::string>::iterator itMode = invMass.begin() ; itMode != invMass.end() ; ++itMode)
			{	
				if (*itMode == std::string("piK"))
					continue;
				isIncluded = KShhConstraints::readKey(fileName,*itCat,*itMode);
				if (isIncluded)
					part_reco.insert(std::make_pair(itMode->c_str(),itCat->c_str()));
				if (isIncluded && (*itMode) == "Kpi")
					part_reco.insert(std::make_pair("piK",itCat->c_str()));
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
									dataFitModel
									);
  
	std::cout << "Signal model is done: " 
			  << (std::time(NULL) - start_time) << " "
			  << (std::time(NULL) - temp_time)
			  << std::endl;
	
	//Constraint the masses
	for(std::vector<std::string>::iterator it_years     = years.begin();   it_years  != years.end();   ++it_years)
		for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
			for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco)
				{
					std::string miss = (it_part_reco->second.find("Gam") != std::string::npos)? "DM_missGam" : "DM_missPi";
					std::string meson = (it_part_reco->first.find("Bs") != std::string::npos)? "Bs":"Bd";	  
					//					double mass = (meson=="Bd")?5285:5370;
					//					double missMass = (miss=="DM_missGam")?0:139;
					fitter.setParameterConstant(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_threshold").c_str(), true);
					fitter.setParameterConstant(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_sigma").c_str(), true);
					fitter.setParameterConstant(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_KS"
												 +(it_part_reco->first)+(*it_KS)+"_"+(*it_years)+"_Yield").c_str(), true);
				}
	temp_time = std::time(NULL);
	
	// ------------------------------------------- //
	//            Combinatorial slope              // 
	// ------------------------------------------- //
	KShhConstraints::setCombinatorialModel(fitter,
										   years,
										   invMass,
										   KS_cat,
										   dataFitModel,
										   combModel
										   );

  
	//================================================================================
	// Finally perform the fit to the data and the plot some results.
	//================================================================================  

	std::cout << "Ready for the fit: "
			  << (std::time(NULL) - start_time) << " "
			  << (std::time(NULL) - temp_time)
			  << std::endl;
	temp_time = std::time(NULL);
	//  fitter.buildNewWorkspace("SimplifiedWS");
	fitter.performFit("dummy",false);
	RooFitResult dataResults( *fitter.getFitResult( "dummy" ) );
	//	dataResults.Print("v");
	std::cout << "Fit done: "
			  << (std::time(NULL) - start_time) << " "
			  << (std::time(NULL) - temp_time)
			  << std::endl;
	temp_time = std::time(NULL);
	//The previous fit was completely dummy. The goal was to easily get the variables names...
	std::cout << "WARNING: Extracting sWeights uniquely from Standard workspaces." << std::endl;
	TFile *f = TFile::Open((saveDir+"WS/Fit-WS-"+dataFitModel+"-"+dataOrigin+"-"+selectionType+"-"+combModel+"-"+name+".root").c_str(),"READ");
	RooWorkspace *w_ref = (RooWorkspace*) f->Get("newDesktop");
	RooArgList params = dataResults.floatParsFinal();
	
	TIterator *it = params.createIterator();
	RooRealVar* var(0);
	double minMass = fitter.getWS()->var("B_M")->getMin();
	double maxMass = fitter.getWS()->var("B_M")->getMax();
	while ((var = (RooRealVar*) it->Next()) != NULL)
		{		
			std::cout << var->GetName() << std::endl;
			Double_t     val = var->getVal();
			Double_t initVal = var->getVal();
			std::string name = var->GetName();
			std::string newName = name;
			//Changing the piK stuff into Kpi
			size_t start_pos = newName.find("piK");			
			if (
				(std::string(var->GetName()).find("Yield") == std::string::npos ||
				 std::string(var->GetName()).find("Cross") != std::string::npos)
				)
				;
			
			RooFormulaVar* testFormula = (RooFormulaVar*) w_ref->function((newName+"_function").c_str());
			RooFormulaVar* formula = NULL;
			if (testFormula == NULL)
				val = w_ref->var(newName.c_str())->getVal();
			std::string testName = newName+"_function";
			while ((testFormula = (RooFormulaVar*) w_ref->function((testName).c_str())) != NULL)
				{
					testName += "_new";
					formula = testFormula;
					val = formula->getVal();
				}
			if (formula != NULL)
				std::cout << "Found the formula @ " << formula->GetName() << std::endl;
			//Chebychev coefficients!!
			if (std::string(var->GetName()).find("c1") != std::string::npos)
				val *= (maxMass-minMass)/800.;
			var->setVal(val);
			double intFactor = 1.;
			std::string varName = var->GetName();
			
			if (varName.find("CrossFeed") != std::string::npos || varName.find("Bkg") != std::string::npos)
				intFactor = calcIntRatio(w_ref,varName,minMass,maxMass);
			if (var->getVal() != val)
				std::cout << "ERROR: " << name << " " << var->getVal() << " " << val << std::endl;
			std::cout << "Setting " << var->GetName() << " to " << var->getVal() << " (" << initVal << ")" << std::endl;
			if (std::string(var->GetName()).find("Yield") != std::string::npos )
				
				if(std::string(var->GetName()).find("Cross") == std::string::npos)
					fitter.setParameterValue(var->GetName(),var->getVal(),false);
				else
					fitter.setParameterValue(var->GetName(),var->getVal(),true);
			else if (std::string(var->GetName()).find("frac") != std::string::npos)
				fitter.setParameterValue(var->GetName(),var->getVal()*intFactor,true);
			else
				fitter.setParameterValue(var->GetName(),var->getVal(),true);
			std::cout << varName+": " << var->getVal()*intFactor << std::endl;
		}

	//Partially-reconstructed background
	RooArgList fixedParams = dataResults.constPars();	
	it = fixedParams.createIterator();		
	while ((var = (RooRealVar*) it->Next()) != NULL)	
		{
			std::string name = var->GetName();
			std::string newName = name;
			double val = 0.;
			if (std::string(var->GetName()).find("Bkg") != std::string::npos &&
				std::string(var->GetName()).find("Yield") != std::string::npos
				)
				{
					RooFormulaVar* testFormula = (RooFormulaVar*) w_ref->function((newName+"_function").c_str());
					RooFormulaVar* formula = NULL;
					if (testFormula == NULL)
						val = w_ref->var(newName.c_str())->getVal();
					std::string testName = newName+"_function";
					while ((testFormula = (RooFormulaVar*) w_ref->function((testName).c_str())) != NULL)
						{
							testName += "_new";
							formula = testFormula;
							val = formula->getVal();
						}
					var->setVal(val);
					double intFactor = calcIntRatio(w_ref,name,minMass,maxMass);
					std::cout << "Setting " << var->GetName() << " to " << var->getVal() << std::endl;
					fitter.setParameterValue(var->GetName(),var->getVal()*intFactor,true);
				}
		}

	fitter.performFit("sWeights",false);
	fitter.getFitResult("sWeights")->Print("");

	fitter.saveWS( (saveDir+"WS/Fit-WS-"+option+"-"+dataFitModel+"-"+dataOrigin+"-"+selectionType+"-"+combOption+"-"+name+".root").c_str() );

	//Calculating the sWeights
	for(std::vector<std::string>::iterator it_years       = years.begin();     it_years    != years.end();     ++it_years)
		for(std::vector<std::string>::iterator it_invMass = invMass.begin();  it_invMass != invMass.end();  ++it_invMass)
			for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
				if (it_invMass->find("KK") == std::string::npos)
					//					fitter.calculateSWeights("sWeights",("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str());
					;
	
	//================================================================================  
	
	//================================================================================
	// Do some nice plotting of the invariant mass spectra, this will do residual and
	//================================================================================  
	//  std::string dir_plots = (saveDir+"Data-Fit/plots/"+selectionType+"/").c_str();  
	fitter.setPlotBins( massvar, 40 ); // Set binning
	for(std::vector<std::string>::iterator it_years       = years.begin();     it_years    != years.end();     ++it_years) {
		for(std::vector<std::string>::iterator it_invMass = invMass.begin();  it_invMass != invMass.end();  ++it_invMass) {
			for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
				std::string plotName = option+"-"+dataFitModel+"-"+dataOrigin+"-"+combOption+protonCut+"-"+selectionType+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Fit"+name;
				std::string axisName;
				if ((*it_invMass) == "pipi")
					axisName = "m(#it{K}_{S}^{0}#it{#pi^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]";
				else if ((*it_invMass) == "Kpi")
					axisName = "m(#it{K}_{S}^{0}#it{K^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]";
				else if ((*it_invMass) == "piK")
					axisName = "m(#it{K}_{S}^{0}#it{K^{#font[122]{-}}#pi^{+}}) [MeV/#it{c}^{2}]";
				else
					axisName = "m(#it{K}_{S}^{0}#it{K^{+}K^{#font[122]{-}}}) [MeV/#it{c}^{2}]";
				fitter.plotMassAndPull((dir_plots+plotName).c_str(),
									   axisName.c_str(),
									   ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), "sWeights", "log") ;
				fitter.plotMassAndPull((dir_plots+plotName).c_str(),
									   axisName.c_str(),
									   ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), "sWeights") ;
			}
		}
	}
	std::cout << "Plots done: "
			  << (std::time(NULL) - start_time) << " "
			  << (std::time(NULL) - temp_time)
			  << std::endl;
	temp_time = std::time(NULL);
	/*	
  
	TCanvas *C = NULL;
	std::vector<std::string> projections; 
	projections.push_back("12");
	projections.push_back("13");
	projections.push_back("23");
	TH1F* projection = NULL;
	TH2F* Dalitz = NULL;
	const RooDataSet* data;
	RooPlot* plot(0);
	std::string plotPrefix = option+"-"+dataFitModel+"-"+dataOrigin+"-"+combOption+protonCut+"-"+selectionType;
	for(std::vector<std::string>::iterator it_years       = years.begin();     it_years    != years.end();     ++it_years)
		for(std::vector<std::string>::iterator it_invMass = invMass.begin();  it_invMass != invMass.end();  ++it_invMass)
			for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
				if (it_invMass->find("KK") == std::string::npos)
					{
						data = (RooDataSet*) (fitter.getDataSet(("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_withSWeights").c_str()))->reduce(("Categories==Categories::KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str());
						std::cout << *it_invMass << " " << data->sumEntries() << std::endl;
						//Plot masses
						fitter.setPlotBins(massvar, 50);
						C = new TCanvas("C","C",1000,1000);
						plot = fitter.makePlot("B_M",("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_withSWeights").c_str(),
											   ("Bd2KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_pdf_KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Yield_sw").c_str());
						
						double *vals = plot->getHist(0)->GetY();
						double max(0),min(100000);
						for (int i = 0 ; i < plot->getHist(0)->GetN() ; i++)
							{
								max = (max > vals[i])? max:(vals[i]+2*TMath::Sqrt(vals[i]));
								min = (min < vals[i])? min:(vals[i]-2*TMath::Sqrt(TMath::Abs(vals[i])));
							}
						plot->GetYaxis()->SetRangeUser(min,max);
						plot->Draw();
						C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/"+plotPrefix+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Bd_sw.pdf").c_str());
						C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/"+plotPrefix+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Bd_sw.png").c_str());						  
						C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/"+plotPrefix+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Bd_sw.eps").c_str());						  
						delete plot; plot = 0;
						delete C; C=0;
						max = 0; min = 1000000;
						C = new TCanvas("C","C",1000,1000);
						plot = fitter.makePlot("B_M",("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_withSWeights").c_str(),
											   ("Bs2KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_pdf_KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Yield_sw").c_str());
						vals = plot->getHist(0)->GetY();
						for (int i = 0 ; i < plot->getHist(0)->GetN() ; i++)
							{
								max = (max > vals[i])? max:(vals[i]+2*TMath::Sqrt(vals[i]));
								min = (min < vals[i])? min:(vals[i]-2*TMath::Sqrt(TMath::Abs(vals[i])));
							}
						plot->GetYaxis()->SetRangeUser(min,max);
						plot->Draw();
						C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/"+plotPrefix+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Bs_sw.pdf").c_str());
						C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/"+plotPrefix+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Bs_sw.png").c_str());						  
						C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/"+plotPrefix+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Bs_sw.eps").c_str());						  
						delete plot; plot = 0;
						delete C; C=0;
						//Plot 1D projections
						for (std::vector<std::string>::iterator itProj = projections.begin() ; itProj != projections.end() ; ++itProj)
							{
								projection = new TH1F("hist","hist",30,0.,5450*5450);
								unsigned int i = 0;
								const RooArgSet* temp = NULL;
								while ((temp = data->get(i)) != NULL)
									{
										double m(0),weight(0);
										m = temp->getRealValue(("m"+(*itProj)+"Sq_Bd2"+(*it_invMass)+"KS").c_str());
										weight = temp->getRealValue(("Bd2KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_pdf_KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Yield_sw").c_str());
										projection->Fill(m,weight);
										i++;
									}
								C = new TCanvas("C","C",1000,1000);						  
								projection->Draw("E");
								C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/"+plotPrefix+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_m"+(*itProj)+"_Bd2"+(*it_invMass)+"KS.pdf").c_str());
								C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/"+plotPrefix+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_m"+(*itProj)+"_Bd2"+(*it_invMass)+"KS.eps").c_str());
								C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/"+plotPrefix+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_m"+(*itProj)+"_Bd2"+(*it_invMass)+"KS.png").c_str());
								delete C; C=0;
								delete projection; projection = 0;
								i = 0;
								projection = new TH1F("hist","hist",30,0.,5450*5450);
								while ((temp = data->get(i)) != NULL)
									{
										double m(0),weight(0);
										m = temp->getRealValue(("m"+(*itProj)+"Sq_Bs2"+(*it_invMass)+"KS").c_str());
										weight = temp->getRealValue(("Bs2KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_pdf_KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Yield_sw").c_str());
										projection->Fill(m,weight);
										i++;
									}
								C = new TCanvas("C","C",1000,1000);						  
								projection->Draw("E");
								C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/"+plotPrefix+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_m"+(*itProj)+"_Bs2"+(*it_invMass)+"KS.pdf").c_str());
								C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/"+plotPrefix+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_m"+(*itProj)+"_Bs2"+(*it_invMass)+"KS.eps").c_str());
								C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/"+plotPrefix+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_m"+(*itProj)+"_Bs2"+(*it_invMass)+"KS.png").c_str());
								delete C; C=0;
								delete projection; projection = 0;
							}
					}
	//Plot 2D projections
	//						  Dalitz = (TH2F*) fitter.getDataSet((selectionType+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_withSWeights").c_str())->createHistogram(("m13Sq_Bd2"+(*it_invMass)+"KS:m23Sq_Bd2"+(*it_invMass)+"KS").c_str(),30,30);
	for(std::vector<std::string>::iterator it_invMass = invMass.begin();  it_invMass != invMass.end();  ++it_invMass)
		for(std::vector<std::string>::iterator it_years       = years.begin();     it_years    != years.end();     ++it_years)
			for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
				if (it_invMass->find("KK") == std::string::npos)
					{
						unsigned int i = 0;
						Dalitz = new TH2F("Dalitz","Dalitz",30,0.,5512*5512,30,0.,5512*5512);						  
						const RooArgSet* temp = NULL;
						data = (RooDataSet*) (fitter.getDataSet(("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_withSWeights").c_str()))->reduce(("Categories==Categories::KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str());
						i = 0;
						while ((temp = data->get(i)) != NULL)
							{
								double m13(0),m23(0),weight(0);
								m13 = temp->getRealValue(("m13Sq_Bd2"+(*it_invMass)+"KS").c_str());
								m23 = temp->getRealValue(("m23Sq_Bd2"+(*it_invMass)+"KS").c_str());
								weight = temp->getRealValue(("Bd2KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_pdf_KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Yield_sw").c_str());
								Dalitz->Fill(m13,m23,weight);
								//								  Dalitz->Fill(m13,m23);
								i++;
							}
						std::cout << Dalitz->GetEntries() << std::endl;
						C = new TCanvas("C","C",1000,1000);						  
						Dalitz->SetFillColor(0);
						Dalitz->Draw("BOX");
						//			  C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Bd_Dalitz.pdf").c_str());
						//			  C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Bd_Dalitz.png").c_str());
						C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/"+plotPrefix+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Bd_Dalitz.pdf").c_str());
						C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/"+plotPrefix+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Bd_Dalitz.eps").c_str());
						C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/"+plotPrefix+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Bd_Dalitz.png").c_str());
						delete Dalitz; Dalitz = 0;
						delete C; C = 0;
						Dalitz = new TH2F("Dalitz","Dalitz",30,0.,5512*5512,30,5512,5512);						  
						data = (RooDataSet*) (fitter.getDataSet(("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_withSWeights").c_str()))->reduce(("Categories==Categories::KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str());
						i =0;			  
						while ((temp = data->get(i)) != NULL)
							{
								double m13(0),m23(0),weight(0);
								m13 = temp->getRealValue(("m13Sq_Bs2"+(*it_invMass)+"KS").c_str());
								m23 = temp->getRealValue(("m23Sq_Bs2"+(*it_invMass)+"KS").c_str());
								weight = temp->getRealValue(("Bs2KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_pdf_KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Yield_sw").c_str());
								Dalitz->Fill(m13,m23,weight);
								i++;
							}
						C = new TCanvas("C","C",1000,1000);						  
						Dalitz->SetFillColor(0);
						Dalitz->Draw("BOX");
						//			  C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Bs_Dalitz.pdf").c_str());
						//			  C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Bs_Dalitz.png").c_str());
						C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/"+plotPrefix+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Bs_Dalitz.pdf").c_str());
						C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/"+plotPrefix+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Bs_Dalitz.eps").c_str());
						C->SaveAs((saveDir+"Data-Fit/plots/sWeights/"+selectionType+"/"+plotPrefix+"-KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Bs_Dalitz.png").c_str());
						delete Dalitz; Dalitz = 0;
						delete C; C = 0;						
					}	
	*/
	//================================================================================
	// Save everything in the workspace!
	//================================================================================  
	fitter.saveWS( (saveDir+"WS/Fit-WS-"+option+"-"+dataFitModel+"-"+dataOrigin+"-"+selectionType+"-"+combOption+"-"+name+".root").c_str() );
	std::cout << "INFO: Saved the workspace in " << saveDir+"WS/Fit-WS-"+option+"-"+dataFitModel+"-"+dataOrigin+"-"+selectionType+"-"+combOption+"-"+name+".root" << std::endl;
	//================================================================================
	
	return 0;
	
	}
