#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>

//ROOT
#include "TChain.h"
#include "TCanvas.h"
#include "TCut.h"
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

//Cuts
#include "KShh/scripts/bdtcut.hh"
#include "KShh/scripts/vetocut.hh"

void fastExit(const char* msg)
{
  std::cout << msg << std::endl;
  assert(0);
}

bool piToK(std::string origin, std::string destination)
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
	std::string option("Standard");
	std::string dataOrigin("Louis");
	std::string protonCut("strong");
	unsigned int nCPU(4);
  boost::program_options::options_description decisions("Option Arguments");
  decisions.add_options()
	  ("help,h" , "produce help message")
	  ("selectionBDT,s", boost::program_options::value<std::string>(&selectionType), "specify which selection has been used in the sample: Loose, Tight, DP1 or DP2")
	  ("blind,b", boost::program_options::value<bool>(&Bs_blind), "specify the Bs2KSKK mass window to be unblind by setting 'false'. Default is set to blind.")
	  ("name,n"    , boost::program_options::value<std::string>(&name), "")
	  ("sigShape"  , boost::program_options::value<std::string>(&sigShape), "")
	  ("combModel" , boost::program_options::value<std::string>(&combModel), "")
	  ("option"    , boost::program_options::value<std::string>(&option),"")
	  ("nCPU"      , boost::program_options::value<unsigned int>(&nCPU),"")
	  ("data"      , boost::program_options::value<std::string>(&dataOrigin),"")
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
    std::string fileName("constraints-DataFit-"+option);  
  KShhConstraints::testFile(fileName);
  
  //Copy the constraints files...
  TString dir         = getenv("V0HHFITTERROOT");
  std::string V0hhDir = dir.Data();
  std::string saveDir = V0hhDir+"/KShh/"; 
  std::string dir_plots = (saveDir+"Data-Fit/plots/"+selectionType+"/").c_str();    
  std::ifstream inFile((V0hhDir+"/KShh/Constraints/"+fileName+".txt").c_str());
  std::ofstream outFile((dir_plots+fileName+".txt").c_str());
  outFile << inFile.rdbuf();
  
  sigModel = KShhConstraints::readString(fileName,"sigModel");
  crossModel = KShhConstraints::readString(fileName,"crossModel");
  partModel = KShhConstraints::readString(fileName,"partModel");

  //================================================================================
  // Create instance of the fitter and observables
  //================================================================================
  bool reflectPRB  = KShhConstraints::readBool(fileName,"reflectPRB" );
  std::cout << "Read all options: " 
			<< (std::time(NULL) - start_time) << " "
			<< (std::time(NULL) - temp_time)
			<< std::endl;
  temp_time = std::time(NULL);
  V0hhFit::SimultaneousFitter fitter( "B2KShhMCFit", "B0(d,s) --> KS h' h Fit" );
  fitter.createWS( "newDesktop", "newDesktop" );
  
  fitter.setGlobalKillBelowError( RooFit::FATAL ); // Monitoring
  fitter.setnCPU( nCPU ); // Sets the number of CPUs to run the minimisation in parallel
  
  TString massvar("B_M"); // Observable name to be used in the fit
  Float_t xmin( 5000.0 ), xmax( 5800.0 ); // Set the range of fit axis
  bool from5100 = KShhConstraints::readBool(fileName,"from5100");
  if (from5100)
	  xmin=5150;
  if (option == "sWeights")
	  {
		  xmin = KShhConstraints::readValue(fileName,"minMass");
		  xmax = KShhConstraints::readValue(fileName,"maxMass");
	  }
  
  // Path to local area to save informations of the fit 
  //  TString dir         = getenv("V0HHFITTERROOT");
  //  std::string V0hhDir = dir.Data();
  //  std::string saveDir = V0hhDir+"/KShh/"; 
  
  fitter.set1DFitVarName( massvar );
  fitter.make1DFitVar( xmin, xmax, "MeV/c^{2}", "m(#it{K^{0}_{#rm S} h^{+} h^{-}})" ); 
  fitter.setPlotBins( massvar, 50 );
  fitter.setBins("B_M", 100, "cache"); // Cache for the ArgusConvGauss

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
  if (dataOrigin != "FusedYears")
	  {
		  years.push_back("2012a");
		  years.push_back("2012b");
	  }    
  
  // Invariant masses 
  invMass.push_back("pipi");
  invMass.push_back("Kpi");
  invMass.push_back("piK");
  invMass.push_back("KK");

  // Possible misIDs
  misID["pipi"].push_back("Kpi");
  misID["pipi"].push_back("piK");
  misID["Kpi" ].push_back("pipi");
  misID["Kpi" ].push_back("KK");
  misID["KK"  ].push_back("Kpi");
  misID["KK"  ].push_back("piK");

  // Crossfeeds 
  bool isIncluded(false);
  for (std::vector<std::string>::iterator itMode1 = modes.begin() ; itMode1 != modes.end() ; ++itMode1)
	  {
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
	  }
  if (protonCut != "strong")
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
  //  categories.push_back("MissGamRes-Bs");
  categories.push_back("Arbitrary-Bd-pi");
  categories.push_back("Arbitrary-Bs-pi");
  categories.push_back("Arbitrary-Bd-gam");
  categories.push_back("Arbitrary-Bs-gam");
  
  for (std::vector<std::string>::iterator itCat = categories.begin() ; itCat != categories.end() ; ++itCat)
	  for (std::vector<std::string>::iterator itMode = invMass.begin() ; itMode != invMass.end() ; ++itMode)
		  {	
			  if (*itMode == std::string("piK"))
				  continue;
			  isIncluded = KShhConstraints::readKey(fileName,*itCat,*itMode) && (!from5100 || (from5100 && itCat->find("Bd") == std::string::npos));
			  if (isIncluded)
				  part_reco.insert(std::make_pair(itMode->c_str(),itCat->c_str()));
			  if (isIncluded && (*itMode) == "Kpi")
				  part_reco.insert(std::make_pair("piK",itCat->c_str()));
		  }
  
  //================================================================================
  
  //================================================================================
  // Define all pdf's (both import MC info and create new pdf's)  
  //================================================================================
  TString file_WS_Sig;
  TString file_WS_Cross;
  std::string pCutSuffix = (protonCut=="strong")?"-StrongPcut":"";
  file_WS_Sig   = (saveDir+"WS/MC-Sig-Fits-WS-"+sigModel+"-"+dataOrigin+"-"+selectionType+"-"+sigShape+".root").c_str(); 
  //  std::cout << "WARNING: Use the locally-produced MC samples of crossfeeds." << std::endl;
  //  file_WS_Cross = (saveDir+"WS/MC-CrossFeed-WS-"+crossModel+"-Louis-PIDCalib-"+selectionType+pCutSuffix+".root").c_str();   
  file_WS_Cross = (saveDir+"WS/MC-CrossFeed-WS-"+crossModel+"-Louis-"+selectionType+pCutSuffix+".root").c_str();   
  
  std::cout << "WARNING: Using FAST MC on partially-reconstructed shapes. Dangerous." << std::endl;
  TString file_WS_Bkg   = (saveDir+"WS/MC-Bkg-WS-"+partModel+"-FastMC.root").c_str(); 

  //Testing files
  TFile *dummy = TFile::Open(file_WS_Sig.Data());
  if (!dummy)
	  fastExit( ("Could not open file "+file_WS_Sig).Data() );
  dummy->Close();
  dummy = TFile::Open(file_WS_Cross.Data());
  if (!dummy)
	  fastExit( ("Could not open file "+file_WS_Cross).Data() );
  dummy->Close();
  dummy = TFile::Open(file_WS_Bkg.Data());
  if (!dummy)
	  fastExit( ("Could not open file "+file_WS_Bkg).Data() );
  dummy->Close();
  dummy = 0;
  // Signal modes
  for(std::vector<std::string>::iterator it_years     = years.begin();   it_years  != years.end();   ++it_years) {
	  for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
		  for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
			  fitter.importPDFFromFile( file_WS_Sig, ((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf").c_str(), ((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf").c_str(), "Desktop");
			  if (sigShape.find("DoubleCB") != std::string::npos)
				  {
					  fitter.setParameterConstant( ((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_n0").c_str() );
					  fitter.setParameterConstant( ((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_n1oN0").c_str() );
					  fitter.setParameterConstant( ((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_alpha0").c_str() );
					  fitter.setParameterConstant( ((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_alpha1oAlpha0").c_str() );
					  fitter.setParameterConstant( ((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_coreFrac").c_str() );
					  if (sigShape.find("DoubleCB2") != std::string::npos)
						  fitter.setParameterConstant( ((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_s1oS0").c_str() );						  
				  }
			  else if (sigShape.find("Cruijff") != std::string::npos)
				  {
					  fitter.setParameterConstant( ((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_alphaL").c_str() );
					  fitter.setParameterConstant( ((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_alphaR").c_str() );	    
				  }
			  else if (sigShape.find("BristolBall") != std::string::npos)
				  {
					  fitter.setParameterConstant( ((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_n0").c_str() );
					  fitter.setParameterConstant( ((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_n1oN0").c_str() );
					  fitter.setParameterConstant( ((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_alpha0").c_str() );
					  fitter.setParameterConstant( ((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_alpha1oAlpha0").c_str() );
				  }
			  else if (sigShape.find("DoubleGauss") != std::string::npos)
				  {
					  fitter.setParameterConstant( ((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_dM").c_str() );
					  fitter.setParameterConstant( ((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_s1oS0").c_str() );
					  fitter.setParameterConstant( ((*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf_coreFrac").c_str() );	    
				  }
		  }
	  }
  } 
  
  // Crossfeed modes
  for(std::vector<std::string>::iterator it_years        = years.begin();   it_years  != years.end();   ++it_years)
	  for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross)
		  for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
			  {
				  if (it_cross->first.find("Bd2KSKpi") == std::string::npos)
					  //The only thing we should be careful against: Lb does not have a 2012 sample... So if not an Lb or not 2012, proceed.
					  if (it_cross->first.find("Lb2") == std::string::npos || *it_years == "2011")
						  //If we use homemade tuples and this is not a Lb2, it does not have a piK anymore. Which is sad, I know. Poor Kpi.						  
						  if (dataOrigin == "Louis" && it_cross->first.find("Lb2") == std::string::npos && it_cross->second == "piK")
							  fitter.importPDFFromFile( file_WS_Cross,
														("CrossFeed_"+(it_cross->first)+"_as_Kpi"+(*it_KS)+"_"+(*it_years)+"_pdf").c_str(),
														("CrossFeed_"+(it_cross->first)+"_as_piK"+(*it_KS)+"_"+(*it_years)+"_pdf").c_str(), "Desktop", true);
						  else
							  fitter.importPDFFromFile( file_WS_Cross,
														("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)+"_pdf").c_str(),
														("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)+"_pdf").c_str(), "Desktop", true);
				  
					  else
						  fitter.importPDFFromFile( file_WS_Cross,
													("CrossFeed_"+(it_cross->first)+"_as_"+it_cross->second+(*it_KS)+"_2011_pdf").c_str(),
													("CrossFeed_"+(it_cross->first)+"_as_"+it_cross->second+(*it_KS)+"_"+(*it_years)+"_pdf").c_str(), "Desktop", true);
				  
				  else
					  fitter.makeDoubleCB(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)+"_pdf").c_str(), 
										  5322, 5200, 5450,
										  8, 0, 30,
										  1, 0, 15,
										  -1, -15, 0,
										  1, 0, 50,
										  1, 0 ,50,
										  0.5);
				  /*
					fitter.setParameterConstant(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)+"_pdf_sigma").c_str(),true);
					fitter.setParameterConstant(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)+"_pdf_alpha0").c_str(),true);
					fitter.setParameterConstant(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)+"_pdf_n0").c_str(),true);
					fitter.setParameterConstant(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)+"_pdf_alpha1oAlpha0").c_str(),true);
					fitter.setParameterConstant(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)+"_pdf_n1oN0").c_str(),true);
					fitter.setParameterConstant(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)+"_pdf_coreFrac").c_str(),true);
				  */
			  }
  //  double massGapKpi = fitter.getParameterValue("CrossFeed_Bs2KSKpi_as_pipiDD_2011_pdf_mu") - fitter.getParameterValue("CrossFeed_Bd2KSKK_as_KpiDD_2011_pdf_mu");
  //  double massGapPiK = fitter.getParameterValue("CrossFeed_Bs2KSKpi_as_KKDD_2011_pdf_mu") - fitter.getParameterValue("CrossFeed_Bd2KSpipi_as_KpiDD_2011_pdf_mu");
  //  std::cout << massGapKpi << " " << massGapPiK << std::endl;
  for(std::vector<std::string>::iterator it_year        = years.begin();   it_year  != years.end();   ++it_year)
      for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross)
          for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
			  if (it_cross->first.find("Bd2KSKpi") != std::string::npos)
				  {
					  std::string refCrossFeed = (it_cross->second.find("KK"))?
						  "CrossFeed_Bd2KSpipi_as_Kpi"+(*it_KS)+"_"+(*it_year)+"_pdf":
						  "CrossFeed_Bd2KSKK_as_Kpi"+(*it_KS)+"_"+(*it_year)+"_pdf";
					  
					  fitter.setParameterValue(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_alpha0").c_str(),
											   fitter.getParameterValue((refCrossFeed+"_alpha0").c_str()),
											   true);
					  fitter.setParameterValue(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_alpha1oAlpha0").c_str(),
											   fitter.getParameterValue((refCrossFeed+"_alpha1oAlpha0").c_str()),
											   true);
					  fitter.setParameterValue(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_n0").c_str(),
											   fitter.getParameterValue((refCrossFeed+"_n0").c_str()),
											   true);
					  fitter.setParameterValue(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_n1oN0").c_str(),
											   fitter.getParameterValue((refCrossFeed+"_n1oN0").c_str()),
											   true);
					  fitter.setParameterValue(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_sigma").c_str(),
											   fitter.getParameterValue((refCrossFeed+"_sigma").c_str()),
											   true);
					  fitter.setParameterValue(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_coreFrac").c_str(),
											   fitter.getParameterValue((refCrossFeed+"_coreFrac").c_str()),
											   true);					  
					  if (it_cross->second.find("KK") != std::string::npos)
						  //						  fitter.setParameterValue(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_mu").c_str(),
						  //												   massGapPiK,
						  //												   true);
						  fitter.setParameterValue(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_mu").c_str(),5320.,true);
					  else
						  //						  fitter.setParameterValue(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_mu").c_str(),
						  //												   Massgapkpi,
						  //												   true);
						  fitter.setParameterValue(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_mu").c_str(),5240.,true);
				  }
  
  // Partially reconstructed bkg
  for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco)
	  if (it_part_reco->second.find("Arbitrary") == std::string::npos)
		  fitter.importPDFFromFile( file_WS_Bkg,
									(it_part_reco->second+"_pdf").c_str(),
									(it_part_reco->second+"_pdf").c_str(),
									"Desktop", true);
  
  for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco)
	  if (it_part_reco->second.find("Arbitrary") != std::string::npos && it_part_reco->first.find("piK") == std::string::npos)
		  {
			  fitter.addParameter((it_part_reco->second+"_"+it_part_reco->first+"_slope").c_str(),-1.,-50.,0.);
			  fitter.addParameter((it_part_reco->second+"_"+it_part_reco->first+"_power").c_str(),0.5,0.,2.);
		  }
  for(std::vector<std::string>::iterator it_years     = years.begin();   it_years  != years.end();   ++it_years)
	  for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco)
		  for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
			  {
				  fitter.makeArgusConvGauss(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf").c_str(),
											20., 5., 50.,
											5200, 5000., 5800.,
											-30, -80, 0 ,
											10., 0, 20);
				  if (it_part_reco->second.find("Arbitrary") == std::string::npos)
					  {
						  double base = (it_part_reco->second.find("Bd") != std::string::npos)?5285:5370;
						  double miss = (it_part_reco->second.find("Gam") != std::string::npos)?0:135;
						  fitter.setParameterValue(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_threshold").c_str(),
												   base-miss, true);
						  fitter.setParameterValue(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_sigma").c_str(),
												   //												   fitter.getParameterValue((it_part_reco->second+"_pdf_sigma").c_str()),
												   20.,
												   false);						 
						  fitter.setParameterValue(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_power").c_str(),
												   fitter.getParameterValue((it_part_reco->second+"_pdf_power").c_str()),
												   true);
						  fitter.setParameterValue(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_slope").c_str(),
												   fitter.getParameterValue((it_part_reco->second+"_pdf_slope").c_str()),
												   true);
						  //						  std::cout << fitter.getParameterValue((it_part_reco->second+"_pdf_power").c_str()) << "\t"
						  //									<< fitter.getParameterValue((it_part_reco->second+"_pdf_slope").c_str()) << "\t"
						  //									<< std::endl;
					  }
				  else
					  {
						  double base = (it_part_reco->second.find("Bd") != std::string::npos)?5285:5370;
						  double miss = (it_part_reco->second.find("pi") != std::string::npos)?135:0;
						  std::cout << "Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_threshold" << " " << base - miss;
						  fitter.setParameterValue(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_threshold").c_str(),
												   base-miss, true);
					  }
			  }  
  if (reflectPRB)
	  for(std::vector<std::string>::iterator it_years     = years.begin();   it_years  != years.end();   ++it_years)
		  for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco)
			  for(std::vector<std::string>::iterator itMisID = misID[it_part_reco->first].begin() ; itMisID != misID[it_part_reco->first].end() ; ++itMisID)
				  for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
					  {
						  fitter.makeArgusConvGauss(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_as_"+(*itMisID)+"_"+(*it_years)+"_pdf").c_str(),
													20., 5., 50.,
													5200, 5000., 5800.,
													-30, -80, 0 ,
													10., 0, 20);
						  double base = (it_part_reco->second.find("Bd") != std::string::npos)?5285:5370;
						  double miss = (it_part_reco->second.find("Gam") != std::string::npos)?0:135;
						  double misIDmass = (piToK(it_part_reco->first,*itMisID))? 40:40;
						  fitter.setParameterValue(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_as_"+(*itMisID)+"_"+(*it_years)+"_pdf_threshold").c_str(),
												   base-miss+misIDmass, true);
						  fitter.setParameterValue(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_as_"+(*itMisID)+"_"+(*it_years)+"_pdf_sigma").c_str(),
												   fitter.getParameterValue((it_part_reco->second+"_pdf_sigma").c_str()),
												   true);						 
						  fitter.setParameterValue(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_as_"+(*itMisID)+"_"+(*it_years)+"_pdf_power").c_str(),
												   fitter.getParameterValue((it_part_reco->second+"_pdf_power").c_str()),
												   true);
						  fitter.setParameterValue(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_as_"+(*itMisID)+"_"+(*it_years)+"_pdf_slope").c_str(),
												   fitter.getParameterValue((it_part_reco->second+"_pdf_slope").c_str()),
												   true);
					  }
  // Combinatorial background
  if (combModel == "PolSlopes")
	  std::cout << "INFO: Using polynomial slopes." << std::endl;
  for(std::vector<std::string>::iterator it_years       = years.begin();    it_years    != years.end();    ++it_years)
	  for(std::vector<std::string>::iterator it_invMass = invMass.begin(); it_invMass != invMass.end(); ++it_invMass)
		  for(std::vector<std::string>::iterator it_KS   = KS_cat.begin();  it_KS      != KS_cat.end();  ++it_KS)
			  if (combModel == "PolSlopes")
				  fitter.makeChebychev( ("combinatoric_KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_pdf").c_str(),
										-0.001, -1.0, 1.0
										);
				  //				  			  fitter.makeChebychev2( ("combinatoric_KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_pdf").c_str(),
				  //													 -0.001, -1.0, 1.0,
				  //													 -0.001, -1.0, 1.0
				  //													 );
			  else
				  fitter.makeExponential( ("combinatoric_KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_pdf").c_str(), -0.001, -1.0, 1.0 );
  
  std::cout << "Took all PDFs: " 
			<< (std::time(NULL) - start_time) << " "
			<< (std::time(NULL) - temp_time)
			<< std::endl;
  temp_time = std::time(NULL);
  
  //================================================================================
  
  //================================================================================
  // Import the data that you need 
  //================================================================================
  TString dataDir = getenv("V0HHFITTERDATA");
  TString baseDir = "";
  std::string data_aux = (dataDir).Data(); 
  std::string dataDirPath = "/afs/cern.ch/work/r/rsilvaco/V0hhFitter/KShh/Data/";
  if (dataOrigin == "Marouen")
	  dataDirPath = "root://eoslhcb.cern.ch//eos/lhcb/user/l/lohenry/KShh/Data/";
  if (dataOrigin == "Louis")
	  //	  dataDirPath = "/afs/cern.ch/work/l/lohenry/Data/KShhFit/Data/";//"root://eoslhcb.cern.ch//eos/lhcb/user/l/lohenry/KShh/Data/";
	  dataDirPath = "root://eoslhcb.cern.ch//eos/lhcb/user/l/lohenry/KShhFit/Data/";
  TFile *file = 0;
  TTree* tree = 0;
  //  if (option.find("sWeights") != std::string::npos)
  //	  {
		  fitter.addSpectator("m12Sq_Bd2pipiKS",0.,5512*5512);
		  fitter.addSpectator("m12Sq_Bs2pipiKS",0.,5512*5512);
		  fitter.addSpectator("m12Sq_Bd2piKKS",0.,5512*5512);
		  fitter.addSpectator("m12Sq_Bs2piKKS",0.,5512*5512);
		  fitter.addSpectator("m12Sq_Bd2KpiKS",0.,5512*5512);
		  fitter.addSpectator("m12Sq_Bs2KpiKS",0.,5512*5512);
		  fitter.addSpectator("m12Sq_Bd2KKKS",0.,5512*5512);
		  fitter.addSpectator("m12Sq_Bs2KKKS",0.,5512*5512);

		  fitter.addSpectator("m13Sq_Bd2pipiKS",0.,5512*5512);
		  fitter.addSpectator("m13Sq_Bs2pipiKS",0.,5512*5512);
		  fitter.addSpectator("m13Sq_Bd2piKKS",0.,5512*5512);
		  fitter.addSpectator("m13Sq_Bs2piKKS",0.,5512*5512);
		  fitter.addSpectator("m13Sq_Bd2KpiKS",0.,5512*5512);
		  fitter.addSpectator("m13Sq_Bs2KpiKS",0.,5512*5512);
		  fitter.addSpectator("m13Sq_Bd2KKKS",0.,5512*5512);
		  fitter.addSpectator("m13Sq_Bs2KKKS",0.,5512*5512);

		  fitter.addSpectator("m23Sq_Bd2pipiKS",0.,5512*5512);
		  fitter.addSpectator("m23Sq_Bs2pipiKS",0.,5512*5512);
		  fitter.addSpectator("m23Sq_Bd2piKKS",0.,5512*5512);
		  fitter.addSpectator("m23Sq_Bs2piKKS",0.,5512*5512);
		  fitter.addSpectator("m23Sq_Bd2KpiKS",0.,5512*5512);
		  fitter.addSpectator("m23Sq_Bs2KpiKS",0.,5512*5512);
		  fitter.addSpectator("m23Sq_Bd2KKKS",0.,5512*5512);
		  fitter.addSpectator("m23Sq_Bs2KKKS",0.,5512*5512);

		  fitter.addSpectator("mPrime_Bd2pipiKS",0.,10000);
		  fitter.addSpectator("mPrime_Bs2pipiKS",0.,10000);
		  fitter.addSpectator("mPrime_Bd2piKKS" ,0.,10000);
		  fitter.addSpectator("mPrime_Bs2piKKS" ,0.,10000);
		  fitter.addSpectator("mPrime_Bd2KpiKS" ,0.,10000);
		  fitter.addSpectator("mPrime_Bs2KpiKS" ,0.,10000);
		  fitter.addSpectator("mPrime_Bd2KKKS"  ,0.,10000);
		  fitter.addSpectator("mPrime_Bs2KKKS"  ,0.,10000);
		  
		  fitter.addSpectator("thPrime_Bd2pipiKS",-10.,10.);
		  fitter.addSpectator("thPrime_Bs2pipiKS",-10.,10.);
		  fitter.addSpectator("thPrime_Bd2piKKS" ,-10.,10.);
		  fitter.addSpectator("thPrime_Bs2piKKS" ,-10.,10.);
		  fitter.addSpectator("thPrime_Bd2KpiKS" ,-10.,10.);
		  fitter.addSpectator("thPrime_Bs2KpiKS" ,-10.,10.);
		  fitter.addSpectator("thPrime_Bd2KKKS"  ,-10.,10.);
		  fitter.addSpectator("thPrime_Bs2KKKS"  ,-10.,10.);
		  //	  }
  // Calculate Selection efficiency
  //   criterion = false;
  std::pair<double,double> criterionEff;
  std::map<std::string,double> criterionThreshPi;
  criterionThreshPi["2011_DD_Loose"] =  0.20;
  criterionThreshPi["2011_DD_Tight"] =  0.25;
  criterionThreshPi["2011_LL_Loose"] =  0.25;
  criterionThreshPi["2011_LL_Tight"] =  0.35;
  criterionThreshPi["2012_DD_Loose"] =  0.20;
  criterionThreshPi["2012_DD_Tight"] =  0.22;
  criterionThreshPi["2012_LL_Loose"] =  0.25;
  criterionThreshPi["2012_LL_Tight"] =  0.36;
  std::map<std::string,double> criterionThreshK ;
  criterionThreshK ["2011_DD_Loose"] =  0.20;
  criterionThreshK ["2011_DD_Tight"] = -0.03;
  criterionThreshK ["2011_LL_Loose"] =  0.25;
  criterionThreshK ["2011_LL_Tight"] =  0.00;
  criterionThreshK ["2012_DD_Loose"] =  0.20;
  criterionThreshK ["2012_DD_Tight"] = -0.02;
  criterionThreshK ["2012_LL_Loose"] =  0.25;
  criterionThreshK ["2012_LL_Tight"] =  0.00;
  TCut pCut;
  if (protonCut != "none")
	  {
		  if (protonCut == "mild")
			  std::cout << "WARNING: Not implemented yet!" << std::endl;
		  else if (protonCut == "strong")
			  pCut += TCut("(h1_PROBNNp<0.5 && h2_PROBNNp < 0.5)");

		  else
			  {
				  std::cout << "ERROR: Unknown proton cut ("<<protonCut<<"). Interrupting the data acquisition." << std::endl;
				  std::exit(1);
			  }
	  }
  std::string KSpim_Lambda = "((TMath::Abs(TMath::Sqrt((KSpip_PE+TMath::Sqrt(938.3**2+KSpim_P**2))**2 - KS_P**2)-1115.7) > 10) || KSpim_PROBNNp < 0.05)";
  std::string KSpip_Lambda = "((TMath::Abs(TMath::Sqrt((KSpim_PE+TMath::Sqrt(938.3**2+KSpip_P**2))**2 - KS_P**2)-1115.7) > 10) || KSpip_PROBNNp < 0.05)";
  TCut LambdaCut = (KSpim_Lambda+" && "+KSpip_Lambda).c_str();
  for(std::vector<std::string>::iterator it_years       = years.begin();     it_years    != years.end();     ++it_years)
	  for(std::vector<std::string>::iterator it_invMass = invMass.begin();  it_invMass != invMass.end();  ++it_invMass)
		  for(std::vector<std::string>::iterator it_KS   = KS_cat.begin();   it_KS      != KS_cat.end();   ++it_KS) {
			  TCut bdtCut(getBDT(selectionType,*it_invMass,*it_KS,*it_years).c_str());
			  TCut vetoCut(veto(*it_invMass));
			  TString PIDcriterion = "(h1_PROBNN(H1) > h1_PROBNN(NH1) + aH1) && (h2_PROBNN(H2) > h2_PROBNN(NH2) + aH2)";
			  TString tempYear = ((*it_years)==("2011"))?"2011":"2012";
			  TString treeName = it_invMass->c_str();
			  std::string h1_Threshold = (TString(treeName).BeginsWith("pi"))?
				  std::to_string(criterionThreshPi[std::string(tempYear.Data())+
												   "_"+
												   (*it_KS)+
												   "_"+
												   (selectionType)
												   ]
								 ):
				  std::to_string(criterionThreshK [std::string(tempYear.Data())+
												   "_"+
												   (*it_KS)+
												   "_"+
												   (selectionType)
												   ]
								 );
			  std::string h2_Threshold = (TString(treeName).EndsWith("pi"))?
				  std::to_string(criterionThreshPi[std::string(tempYear.Data())+"_"+(*it_KS)+"_"+(selectionType)]):
				  std::to_string(criterionThreshK [std::string(tempYear.Data())+"_"+(*it_KS)+"_"+(selectionType)]);			  
			  
			  if (TString(it_invMass->c_str()).BeginsWith("pi"))
				  {
					  PIDcriterion.ReplaceAll("(H1)" ,"pi");
					  PIDcriterion.ReplaceAll("(NH1)","K" );
					  PIDcriterion.ReplaceAll("aH1",h1_Threshold.c_str());
				  }
			  else
				  {
					  PIDcriterion.ReplaceAll("(H1)" ,"K" );
					  PIDcriterion.ReplaceAll("(NH1)","pi");
					  PIDcriterion.ReplaceAll("aH1",h1_Threshold);
				  }
			  if (TString(it_invMass->c_str()).EndsWith("pi"))
				  {
					  PIDcriterion.ReplaceAll("(H2)" ,"pi");
					  PIDcriterion.ReplaceAll("(NH2)","K" );
					  PIDcriterion.ReplaceAll("aH2",h2_Threshold);
				  }
			  else
				  {
					  PIDcriterion.ReplaceAll("(H2)" ,"K" );
					  PIDcriterion.ReplaceAll("(NH2)","pi");
					  PIDcriterion.ReplaceAll("aH2",h2_Threshold);
				  }
			  //			  TCut PIDcut(PIDcriterion.Data());			  
			  if (dataOrigin == "Rafael")
				  baseDir = dataDirPath+(*it_years)+"/KShhFit/"+selectionType+"/B2KShh-"+(*it_years)+"-Trigger-Presel-Vetoes-BDT-PID-SingleCand.root";
			  else if (dataOrigin == "Marouen")
				  baseDir = dataDirPath+(*it_years)+"/KShhFit/"+selectionType+"/B2KS"+(*it_invMass)+"-"+(*it_years)+"-"+(*it_KS)+"-MagAll.root";
			  else if (dataOrigin == "Louis")
				  baseDir = dataDirPath+selectionType+"/B2KS"+(*it_invMass)+"-"+(*it_years)+"-"+(*it_KS)+"-"+selectionType+"-MagAll.root";
			  std::string filename = baseDir.Data();
			  file = TFile::Open( filename.c_str(), "READ" );
			  if (dataOrigin == "Rafael")
				  tree = dynamic_cast<TTree*>( file->Get( ("B2KShh"+(*it_KS)+"/B2"+(*it_invMass)+"KS").c_str() ) );
			  else if (dataOrigin == "Marouen")
				  tree = dynamic_cast<TTree*>( file->Get( ("B2"+(*it_invMass)+"KS").c_str() ) );
			  else if (dataOrigin == "FusedYears")
				  tree = dynamic_cast<TTree*>( file->Get( ("B2KShh"+(*it_KS)+"/B2"+(*it_invMass)+"KS").c_str() ) );
			  else if (dataOrigin == "Louis")
				  tree = dynamic_cast<TTree*>( file->Get( ("B2"+(*it_invMass)+"KS").c_str() ) );

			  //			  TCut PIDcut(PIDcriterion.Data());			  
			  //			  TCut PIDcut(getPID(selectionType,*it_invMass,*it_KS,*it_years).c_str());			  
			  if (dataOrigin == "Rafael")
				  //				  fitter.makeMassDataSet( tree, massvar, ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), "", PIDcriterion.Data() ) ;
				  fitter.makeMassDataSet( tree, massvar, ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), "", vetoCut ) ;
			  else if (dataOrigin == "Marouen")
				  fitter.makeMassDataSet( tree, massvar, ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), "", bdtCut+vetoCut ) ;
			  else if (dataOrigin == "FusedYears")
				  fitter.makeMassDataSet( tree, massvar, ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), "", bdtCut+vetoCut ) ;
			  else if (dataOrigin == "Louis")
				  fitter.makeMassDataSet( tree, massvar, ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), "", pCut+LambdaCut ) ;
			  //				  fitter.makeMassDataSet( tree, massvar, ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), "", PIDcut ) ;
		  }
  file->Close();  // close the file 
  
  fitter.combineDataSets();
  std::cout << "Took all data: " 
			<< (std::time(NULL) - start_time) << " "
			<< (std::time(NULL) - temp_time)
			<< std::endl;
  
  //================================================================================
  
  //================================================================================
  // Create PDFs and then add by csv the pdfs that should be used for the mass 
  //================================================================================
  fitter.createPDFSets();
  
  for(std::vector<std::string>::iterator it_years       = years.begin();     it_years    != years.end();     ++it_years) {
	  for(std::vector<std::string>::iterator it_invMass = invMass.begin();  it_invMass != invMass.end();  ++it_invMass) {
		  for(std::vector<std::string>::iterator it_KS   = KS_cat.begin();   it_KS      != KS_cat.end();   ++it_KS) {
			  std::string pdf_names = "";
			  for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes)
				  if ((*it_modes).find((*it_invMass)) != std::string::npos)
					  pdf_names = (pdf_names+(*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf,").c_str();
			  for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross)
				  if ((*it_invMass) == (it_cross->second))
					  pdf_names =  (pdf_names+"CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)+"_pdf,").c_str();
			  for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco)
				  {
					  if ((*it_invMass) == (it_part_reco->first))
						  pdf_names = (pdf_names+"Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf,").c_str();
					  if (reflectPRB)
						  for (std::vector<std::string>::iterator itMis = misID[it_part_reco->first].begin(); itMis != misID[it_part_reco->first].end(); ++itMis)
							  if ((*it_invMass) == (*itMis))
								  pdf_names += "Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_as_"+*itMis+"_"+(*it_years)+"_pdf,";
				  }
			  
			  pdf_names = (pdf_names+"combinatoric_KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_pdf").c_str();
			  fitter.addPDFs(("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(),pdf_names.c_str());
		  }
	  }
  }
  
  for(std::vector<std::string>::iterator it_years       = years.begin();     it_years    != years.end();     ++it_years)
	  for(std::vector<std::string>::iterator it_invMass = invMass.begin();  it_invMass != invMass.end();  ++it_invMass)
		  for(std::vector<std::string>::iterator it_KS   = KS_cat.begin();   it_KS      != KS_cat.end();   ++it_KS)
			  fitter.addYields( ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str() ) ;
  
  //fitter.getWS()->Print("V");
  
  fitter.buildAddPdfs();
  fitter.buildModel();
  std::cout << "Model is built: " 
			<< (std::time(NULL) - start_time) << " "
			<< (std::time(NULL) - temp_time)
			<< std::endl;
  temp_time = std::time(NULL);
  std::string suffix("");
  if (combModel == "PolSlopes")
	  suffix += "-PolSlopes";
  else
	  suffix += "-Exponential";
  
  if (protonCut == "strong")
	  suffix += "-StrongPcut";
  fitter.saveWS((saveDir+"WS/Data-WS-"+option+"-"+dataOrigin+"-"+selectionType+suffix+"-"+name+".root").c_str());
  return 0;
}
