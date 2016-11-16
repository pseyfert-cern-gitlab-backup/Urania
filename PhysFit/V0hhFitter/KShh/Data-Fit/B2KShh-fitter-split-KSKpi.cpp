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

int main( int argc, char* argv[] ) {
  
  RooMsgService::instance().setGlobalKillBelow(RooFit::ERROR);
  std::time_t start_time = std::time(NULL);
  std::time_t temp_time = std::time(NULL);
  bool Bs_blind(true);
  bool ToyMC(false);
  bool facBs(true);
  bool gausBs(true), gausLL(true), gausMode(true);
  Double_t nExp(0.);    
  std::string selectionType("Loose");
  std::string Int_info = "";    
  std::set<std::string> integral_range;
  Double_t sigma_input(0.);
  std::string name("");
  std::string sigShape("DoubleCB");
  std::string sigModel("Vanilla");
  std::string crossModel("Vanilla");
  std::string partModel("Vanilla");
  std::string option("Vanilla");
  unsigned int nCPU(4);
  boost::program_options::options_description decisions("Option Arguments");
  decisions.add_options()
    ("help,h" , "produce help message")
	  ("selectionBDT,s", boost::program_options::value<std::string>(&selectionType), "specify which selection has been used in the sample: Loose, Tight, DP1 or DP2")
	  ("blind,b", boost::program_options::value<bool>(&Bs_blind), "specify the Bs2KSKK mass window to be unblind by setting 'false'. Default is set to blind.")
	  ("integral,i", boost::program_options::value<std::string>(&Int_info), "provide information about the mass window integration to produce final sample for Dalitz plot analysis. Please provide in the format 'All' or 'Bs2KSpipi-2', where 2 stands for 2sigma of the measured value. Notice that in the case of the KSKpi spectra the corresponding charge hypothesis needs to be specified, e.g. Bs2KSKpi_DP1")
	  ("toyMC,t", boost::program_options::value<Double_t>(&nExp), "optional (kFalse = default): specify the number os ToyMC experiments to generate/fit for the fitted model. Note: in the case of blind fit, the scenario of Bs2KSKK with yield==0 is considered")
	  ("name,n"    , boost::program_options::value<std::string>(&name), "")
	  ("sigShape"  , boost::program_options::value<std::string>(&sigShape), "")
	  ("sigModel"  , boost::program_options::value<std::string>(&sigModel), "")
	  ("crossModel", boost::program_options::value<std::string>(&crossModel), "")
	  ("partModel" , boost::program_options::value<std::string>(&partModel), "")
	  ("option"    , boost::program_options::value<std::string>(&option),"")
	  ("nCPU"    , boost::program_options::value<unsigned int>(&nCPU),"")
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
  if (vm.count("toyMC")){ 
    ToyMC = true;
    std::cout << "INFO: " << nExp << " ToyMC experiments will be generated after the fit to data" << std::endl;
  }
  if (vm.count("integral")){
    std::vector<std::string> split_name;
    boost::split(split_name,Int_info,boost::is_any_of("-"));
    std::string range_name = split_name[0];
    TString sigmaRange = split_name[1];
    if (Int_info.find("All") == std::string::npos) { 
      std::cout << "INFO: Integrating fit results of mode " <<  split_name[0] << " within " << split_name[1] << " sigma" << std::endl;
      integral_range.insert(range_name);
      sigma_input =  atof(sigmaRange);
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
      sigma_input =  atof(sigmaRange);
    } else {
      std::cout << "ERROR: Please provide an apropriate name e.g.: Bs2KSKpi_2" << std::endl;
    }
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
  std::string dir_plots = (saveDir+"Data-Fit/plots/"+selectionType+"/").c_str();    
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
  fitter.createWS( "newDesktop", "newDesktop" );
  
  fitter.setGlobalKillBelowError( RooFit::FATAL ); // Monitoring
  fitter.setnCPU( nCPU ); // Sets the number of CPUs to run the minimisation in parallel
  
  TString massvar("B_M"); // Observable name to be used in the fit
  Float_t xmin( 5000.0 ), xmax( 5800.0 ); // Set the range of fit axis
  
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
  // Define all pdf's (both import MC info and create new pdf's)  
  //================================================================================
  //  std::string sigShape("DoubleCB");
  //To be re-written soon
  //  if (sigModel.find("Cruijff") != std::string::npos)
  //    sigShape = "Cruijff";
  //  if (sigModel.find("BristolBall") != std::string::npos)
  //    sigShape = "BristolBall";
  //  crossModel = "SameMissID";
  TString file_WS_Sig   = (saveDir+"WS/MC-Sig-WS-"+selectionType+"-"+sigShape+"-"+sigModel+".root").c_str(); 
  TString file_WS_Cross = (saveDir+"WS/MC-CrossFeed-WS-"+selectionType+"-"+crossModel+".root").c_str(); 
  TString file_WS_Bkg   = (saveDir+"WS/MC-Bkg-WS-"+selectionType+"-"+partModel+".root").c_str(); 
  
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
	fitter.importPDFFromFile( file_WS_Cross,
				  ("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)+"_pdf").c_str(),
				  ("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)+"_pdf").c_str(), "Desktop", true);
  
  // Partially reconstructed bkg
  for(std::vector<std::string>::iterator it_years     = years.begin();   it_years  != years.end();   ++it_years)
    for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco)
      for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
	fitter.importPDFFromFile( file_WS_Bkg,
				  //				  ("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf").c_str(),
				  (it_part_reco->second+"_pdf").c_str(),
				  ("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf").c_str(), "Desktop", true);
  
  // Combinatorial background
  for(std::vector<std::string>::iterator it_years       = years.begin();    it_years    != years.end();    ++it_years)
    for(std::vector<std::string>::iterator it_invMass = invMass.begin(); it_invMass != invMass.end(); ++it_invMass)
      for(std::vector<std::string>::iterator it_KS   = KS_cat.begin();  it_KS      != KS_cat.end();  ++it_KS)
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
  TFile *file = 0;
  TTree* tree = 0;
  
  for(std::vector<std::string>::iterator it_years       = years.begin();     it_years    != years.end();     ++it_years)
    for(std::vector<std::string>::iterator it_invMass = invMass.begin();  it_invMass != invMass.end();  ++it_invMass)
      for(std::vector<std::string>::iterator it_KS   = KS_cat.begin();   it_KS      != KS_cat.end();   ++it_KS) {
	//baseDir = dataDir+"/KShh/Data/"+(*it_years)+"/KShhFit/"+selectionType+"/B2KShh-"+(*it_years)+"-Trigger-Presel-Vetoes-BDT-PID-SingleCand.root";
	std::cerr << *it_years << " " << *it_invMass << " " << *it_KS << std::endl;
	std::cout << *it_years << " " << *it_invMass << " " << *it_KS << std::endl;
	baseDir = dataDirPath+(*it_years)+"/KShhFit/"+selectionType+"/B2KShh-"+(*it_years)+"-Trigger-Presel-Vetoes-BDT-PID-SingleCand.root";
	std::string filename = baseDir.Data();
	file = TFile::Open( filename.c_str(), "READ" );
	tree = dynamic_cast<TTree*>( file->Get( ("B2KShh"+(*it_KS)+"/B2"+(*it_invMass)+"KS").c_str() ) );
	fitter.makeMassDataSet( tree, massvar, ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), "" ) ; 
      }
  file->Close();  // close the file 
  
  fitter.combineDataSets();
  std::cout << "Took all data: " 
	    << (std::time(NULL) - start_time) << " "
	    << (std::time(NULL) - temp_time)
	    << std::endl;
  temp_time = std::time(NULL);

  //================================================================================
  
  //================================================================================
  // Create PDFs and then add by csv the pdfs that should be used for the mass 
  //================================================================================
  fitter.createPDFSets();
  
  for(std::vector<std::string>::iterator it_years       = years.begin();     it_years    != years.end();     ++it_years) {
    for(std::vector<std::string>::iterator it_invMass = invMass.begin();  it_invMass != invMass.end();  ++it_invMass) {
      for(std::vector<std::string>::iterator it_KS   = KS_cat.begin();   it_KS      != KS_cat.end();   ++it_KS) {
	std::string pdf_names = "";
	for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
	  if ((*it_modes).find((*it_invMass)) != std::string::npos) {
	    pdf_names = (pdf_names+(*it_modes)+(*it_KS)+"_"+(*it_years)+"_pdf,").c_str();
	  }
	}
	for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
	  if ((*it_invMass) == (it_cross->second)){  
	    pdf_names =  (pdf_names+"CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)+"_pdf,").c_str();
	  }
	}
	for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
	  if ((*it_invMass) == (it_part_reco->first)){  
	    pdf_names = (pdf_names+"Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf,").c_str();
	  }
	}
	pdf_names = (pdf_names+"combinatoric_KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_pdf").c_str();
	fitter.addPDFs(("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(),pdf_names.c_str());
      }
    }
  }
  
  for(std::vector<std::string>::iterator it_years       = years.begin();     it_years    != years.end();     ++it_years) {
    for(std::vector<std::string>::iterator it_invMass = invMass.begin();  it_invMass != invMass.end();  ++it_invMass) {
      for(std::vector<std::string>::iterator it_KS   = KS_cat.begin();   it_KS      != KS_cat.end();   ++it_KS) {
	fitter.addYields( ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str() ) ;
      }
    }
  }
  //fitter.getWS()->Print("V");
  
  fitter.buildAddPdfs();
  fitter.buildModel();
  std::cout << "Model is built: " 
	    << (std::time(NULL) - start_time) << " "
	    << (std::time(NULL) - temp_time)
	    << std::endl;
  temp_time = std::time(NULL);

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
  if (Bs_blind){ 
    for(std::vector<std::string>::iterator it_years     = years.begin();   it_years  != years.end();   ++it_years) {
      for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
	fitter.blindParameter(("Bs2KSKK"+(*it_KS)+"_"+(*it_years)+"_pdf_KSKK"+(*it_KS)+"_"+(*it_years)+"_Yield").c_str(), 100);
      }
    }
  }
  
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
  temp_time = std::time(NULL);

   
  //  fitter.getWS()->Print("");
  // ------------------------------------------- //
  // ------------------------------------------- //
  //              Crossfeed Yields               // 
  // ------------------------------------------- //
  // ******************************************* //
  // Create constraints to the crossfeed yields
  for(std::vector<std::string>::iterator it_years = years.begin(); it_years != years.end(); ++it_years) {
    for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
      for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
	std::string fracName = "frac_cross_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years);
	//	if (it_cross->second.find("piK") == std::string::npos)
	fitter.addParameter(fracName.c_str(), 0., 1.0);
	//	else
	//	  fracName = "frac_cross_"+(it_cross->first)+"_as_Kpi"+(*it_KS)+"_"+(*it_years);
	std::string cf_constName = "CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)+"_pdf_KS"+(it_cross->second)+(*it_KS)+"_"+(*it_years)+"_Yield";
	
	// Crossfeeds from pipi or KK
	if ((it_cross->first).find("Bs") != std::string::npos) {
	  std::string cf_refName   = "Bs2KSKpi"+(*it_KS)+"_"+(*it_years)+"_pdf_KSKpi"+(*it_KS)+"_"+(*it_years)+"_Yield,Bs2KSpiK"+(*it_KS)+"_"+(*it_years)+"_pdf_KSpiK"+(*it_KS)+"_"+(*it_years)+"_Yield";
	  fitter.addConstraint(cf_constName.c_str(),"(@0+@1)*@2",(cf_refName+","+fracName).c_str());
	} else if ( it_cross->first == "Bd2KSpipi"){
	  std::string cf_refName = (it_cross->first)+(*it_KS)+"_"+(*it_years)+"_pdf_KSpipi"+(*it_KS)+"_"+(*it_years)+"_Yield";
	  fitter.addConstraint(cf_constName.c_str(),"@0*@1*0.5",(cf_refName+","+fracName).c_str());
	} else if ( it_cross->first == "Bd2KSKK"){
	  std::string cf_refName = (it_cross->first)+(*it_KS)+"_"+(*it_years)+"_pdf_KSKK"+(*it_KS)+"_"+(*it_years)+"_Yield";
	  fitter.addConstraint(cf_constName.c_str(),"@0*@1*0.5",(cf_refName+","+fracName).c_str());
	} else {
	  std::cout << "ERROR: There is something wrong with the configuration" << std::endl;
	}
      }
    }
  }
  
  // Create the gaussian constraints (import from DB)

  std::string dbTable = V0hhDir+"/KShh/dB/efficiencyTable.db"; 
  sqlite3 *db;
  int rc = sqlite3_open(dbTable.c_str(), &db);
  if (rc) {
    std::fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
       exit(0);
  } else {
    fprintf(stderr, "Opened database successfully\n");
  }
  
  // Variables initialisation
  const char *sqlSig;
  const char *sqlCross;
  Double_t Eff_Sel_sig(0.), Err_Sel_sig(0.);
  Double_t Eff_Sel_cross(0.), Err_Sel_cross(0.);
  Double_t Eff_MisID(0.), Err_MisID(0.);
  std::string sig_eff_str(""), sig_err_str("");
  std::string cross_eff_str(""), cross_err_str("");
  std::string misID_eff_str(""), misID_err_str("");
  Double_t factor_cross(0.), factor_cross_err(0.), Err_Sel_fac(0.);
  
  for(std::vector<std::string>::iterator it_years = years.begin(); it_years != years.end(); ++it_years) {
    for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
      for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
	sqlite3_stmt* stmt_sig   = NULL;
	sqlite3_stmt* stmt_cross = NULL;
	int retval, retval_cross;
	TString dbLinkSig   = "";
	TString dbLinkCross = "";
	if (((it_cross->second) == "Kpi") || ((it_cross->second) == "piK")){
	  dbLinkSig = "SELECTION LIKE '"+selectionType+"' AND MODE LIKE 'Bs2KS"+(it_cross->second)+"' AND KSTYPE LIKE '"+(*it_KS)+"' AND YEAR LIKE '"+(*it_years)+"' AND TREENAME LIKE '"+(it_cross->second)+"'";
	} else {
	  dbLinkSig = "SELECTION LIKE '"+selectionType+"' AND MODE LIKE 'Bd2KS"+(it_cross->second)+"' AND KSTYPE LIKE '"+(*it_KS)+"' AND YEAR LIKE '"+(*it_years)+"' AND TREENAME LIKE '"+(it_cross->second)+"'";
	}
	dbLinkCross  = "SELECTION LIKE '"+selectionType+"' AND MODE LIKE '"+(it_cross->first)+"' AND KSTYPE LIKE '"+(*it_KS)+"' AND YEAR LIKE '"+(*it_years)+"' AND TREENAME LIKE '"+(it_cross->second)+"'";
	// Retrive signal efficiency information 
	TString aux = "SELECT * from EFFICIENCY WHERE "+dbLinkSig;
	sqlSig = aux.Data();
	retval = sqlite3_prepare_v2(db, sqlSig, -1, &stmt_sig, 0);
	if (retval){
	  printf("Selecting data from DB Failed (err_code=%d)\n", retval);
	  return 0;
	}
	while(1) {
	  retval = sqlite3_step(stmt_sig);
	  if (retval == SQLITE_ROW) {
	    // Selection and Generation efficiency
	    const unsigned char* sig_effLink = sqlite3_column_text(stmt_sig, 8);
	    std::stringstream sig_eff_tmp_str;
	    sig_eff_tmp_str << sig_effLink;
	    sig_eff_str = (sig_eff_tmp_str).str();
	    Eff_Sel_sig = atof((sig_eff_str).c_str()); 
	    // Selection and Generation efficiency error
	    const unsigned char* sig_errLink = sqlite3_column_text(stmt_sig, 9);
	    std::stringstream sig_err_tmp_str;
	    sig_err_tmp_str << sig_errLink;
	    sig_err_str = (sig_err_tmp_str).str();
	    Err_Sel_sig = atof((sig_err_str).c_str()); 
	    break;
	  } else if(retval == SQLITE_DONE) { 
	    break;
	  }
	}
	
	// Retrive crossfeed efficiency information
	TString aux_cross = "SELECT * from EFFICIENCY WHERE "+dbLinkCross;
	sqlCross = aux_cross.Data();
	retval_cross = sqlite3_prepare_v2(db, sqlCross, -1, &stmt_cross, 0);
	if (retval_cross){
	  printf("Selecting data from DB Failed (err_code=%d)\n", retval_cross);
	  return 0;
	}
	while(1) {
	  retval_cross = sqlite3_step(stmt_cross);
	  if (retval_cross == SQLITE_ROW) {
	    // Sel and Gen efficiency cross
	    const unsigned char* cross_effLink = sqlite3_column_text(stmt_cross, 8);
	    std::stringstream cross_eff_tmp_str;
	    cross_eff_tmp_str << cross_effLink;
	    cross_eff_str = (cross_eff_tmp_str).str();
	    Eff_Sel_cross = atof((cross_eff_str).c_str()); 
	    // Sel and Gen efficiency error cross
	    const unsigned char* cross_errLink = sqlite3_column_text(stmt_cross, 9);
	    std::stringstream cross_err_tmp_str;
	    cross_err_tmp_str << cross_errLink;
	    cross_err_str = (cross_err_tmp_str).str();
	    Err_Sel_cross = atof((cross_err_str).c_str()); 
	    // misID efficiency
	    const unsigned char* misID_effLink = sqlite3_column_text(stmt_cross, 10);
	    std::stringstream misID_eff_tmp_str;
	    misID_eff_tmp_str << misID_effLink;
	    misID_eff_str = (misID_eff_tmp_str).str();
	    Eff_MisID     = atof((misID_eff_str).c_str()); 
	    // misID efficiency error
	    const unsigned char* misID_errLink = sqlite3_column_text(stmt_cross, 11);
	    std::stringstream misID_err_tmp_str;
	    misID_err_tmp_str << misID_errLink;
	    misID_err_str = (misID_err_tmp_str).str();
	    Err_MisID     = atof((misID_err_str).c_str()); 
	    break;
	  } else if(retval_cross == SQLITE_DONE) { 
	    break;
	  }
	}
	//std::cout << "Mode: " << (it_cross->first) << " in the KS" << (it_cross->second) << " invariant Mass" << std::endl;
	//std::cout << "Signal selection*gen efficiency :" << Eff_Sel_sig << " +/- " << Err_Sel_sig << std::endl;
	//std::cout << "Cross  selection*gen efficiency :" << Eff_Sel_cross << " +/- " << Err_Sel_cross << std::endl;
	//std::cout << "MisID  efficiency :" << Eff_MisID << " +/- " << Err_MisID << std::endl;
        
	// Factor and associated error
	factor_cross = Eff_MisID * (Eff_Sel_sig/Eff_Sel_cross);
	Double_t sel_sig_1_sq = (Err_Sel_sig/Eff_Sel_sig)*(Err_Sel_sig/Eff_Sel_sig);
	Double_t sel_sig_2_sq = (Err_Sel_cross/Eff_Sel_cross)*(Err_Sel_cross/Eff_Sel_cross);
	Double_t sel_factor   = (Eff_Sel_sig/Eff_Sel_cross);
	Err_Sel_fac = sel_factor*(sqrt(sel_sig_1_sq + sel_sig_2_sq));
	Double_t tot_sig_1_sq = (Err_Sel_fac/sel_factor)*(Err_Sel_fac/sel_factor);
	Double_t tot_sig_2_sq = (Err_MisID/Eff_MisID)*(Err_MisID/Eff_MisID); 
	factor_cross_err = factor_cross*(sqrt(tot_sig_1_sq + tot_sig_2_sq));
	// Creating the Gaussian constraints
	if (((it_cross->second) == "Kpi") || ((it_cross->second) == "piK")){
	  fitter.addGaussianConstraint(("frac_cross_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)).c_str(), 0.5*factor_cross, 0.5*factor_cross_err);
	} else {
	  fitter.addGaussianConstraint(("frac_cross_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_years)).c_str(), factor_cross, factor_cross_err);
	}
      }
    }
  }

  // ------------------------------------------- //
  //            Combinatorial slope              // 
  // ------------------------------------------- //
  KShhConstraints::setCombinatorialModel(fitter,
					 years,
					 invMass,
					 KS_cat,
					 option
					 );
  
  // ------------------------------------------- //
  //  Partially reconstructed yields constraints // 
  // ------------------------------------------- //
  bool sameForDDLL  = KShhConstraints::readBool(fileName,"sameForDDLL" );
  bool sameForYears = KShhConstraints::readBool(fileName,"sameForYears");
  // Create the yield constraints parameters.
  for(std::vector<std::string>::iterator it_years       = years.begin();    it_years    != years.end();    ++it_years)
    for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco)
      for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS != KS_cat.end(); ++it_KS) {
	std::string fracName = ("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)+"_"+(*it_KS)+"_"+(*it_years));
	if ((!sameForDDLL || it_KS->find("LL") == std::string::npos) && (!sameForYears && (*it_years) != "2012a" && (*it_years) != "2012b"))
	  fitter.addParameter((fracName).c_str(),0.,1.);
      }
  for(std::vector<std::string>::iterator it_years       = years.begin();    it_years    != years.end();    ++it_years)
    for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco)
      for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS != KS_cat.end(); ++it_KS) {
	std::string tempYear = (*it_years);
	if (sameForYears)
	  tempYear = "2011";
	std::string tempKS = (*it_KS);
	if (sameForDDLL)
	  tempYear = "DD";
	std::string fracName = ("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)+"_"+tempKS+"_"+tempYear);
	std::string bkg_yieldName    = "Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_years)+"_pdf_KS"+(it_part_reco->first)+(*it_KS)+"_"+(*it_years)+"_Yield";
	std::string sig_yieldRefName = "";
	if ((it_part_reco->first == "Kpi") || (it_part_reco->first == "piK"))
	  //	  sig_yieldRefName = "Bs2KS"+(it_part_reco->first)+(*it_KS)+"_"+(*it_years)+"_pdf_KS"+(it_part_reco->first)+(*it_KS)+"_"+(*it_years)+"_Yield";
	  sig_yieldRefName = "Bs2KSKpi"+(*it_KS)+"_"+(*it_years)+"_pdf_KSKpi"+(*it_KS)+"_"+(*it_years)+"_Yield";
	else
	  sig_yieldRefName = "Bd2KS"+(it_part_reco->first)+(*it_KS)+"_"+(*it_years)+"_pdf_KS"+(it_part_reco->first)+(*it_KS)+"_"+(*it_years)+"_Yield";
	
	//	fitter.addConstraint(bkg_yieldName.c_str(), "@0*@1", (sig_yieldRefName+",frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)+"_"+(*it_KS)+"_"+(*it_years)).c_str());
	fitter.addConstraint(bkg_yieldName.c_str(), "@0*@1", (sig_yieldRefName+","+fracName).c_str());
      }
  
  // Create the gaussian constraints (import from DB)
  std::string dbTable_pr = V0hhDir+"/KShh/dB/partiallyRecoYielTable.db"; 
  sqlite3 *db_pr;
  int rc_pr = sqlite3_open(dbTable_pr.c_str(), &db_pr);
  if (rc_pr) {
    std::fprintf(stderr, "Can't open partially reco database: %s\n", sqlite3_errmsg(db_pr));
    exit(0);
  } else {
    fprintf(stderr, "Opened partially reconstructed bkg database successfully\n");
  }
  
  // Variables initialisation
  std::map<std::string,std::string> canonicalModes;
  canonicalModes["Charmed-Bd"]    = "Bu2D0pi2KS0pipi";
  canonicalModes["Charmed-Bs"]    = "Bu2D0pi2KS0pipi";
  canonicalModes["Charmless-Bd"]  = "Bd2Kst0rho02KS0pi0pipi";
  canonicalModes["Charmless-Bs"]  = "Bs2KstKst2KS0piKpi0";
  canonicalModes["MissGamNR-Bd"]  = "Bd2pipiKS0gamma";
  canonicalModes["MissGamNR-Bs"]  = "Bd2pipiKS0gamma";
  canonicalModes["Charmonia-Bd"]  = "Bd2etacKS2KKpi0";
  canonicalModes["Charmonia-Bs"]  = "Bd2etacKS2KKpi0";
  canonicalModes["MissGamRes-Bd"] = "Bd2etapKS02pipigamma";
  canonicalModes["MissGamRes-Bs"] = "Bd2etapKS02pipigamma";

  const char *sqlRatio_pr;
  std::string frac_bkg_str(""), frac_bkg_err_str("");
  Double_t Fraction_bkg_val(0.), Fraction_err_bkg_val(0.);
  for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){      
    for(std::vector<std::string>::iterator it_years                       = years.begin();        it_years    != years.end();      ++it_years) {
      for(std::vector<std::string>::iterator it_KS                   = KS_cat.begin();      it_KS      != KS_cat.end();    ++it_KS) {
	if (sameForYears && (it_years->find("2012") != std::string::npos))
	  continue;
	if (sameForDDLL && (it_KS->find("LL") != std::string::npos))
	  continue;
	sqlite3_stmt* stmt_pr   = NULL;
	int retval_pr;
	//	TString dbLinkPR = "SELECTION LIKE '"+selectionType+"' AND PARTRECO LIKE '"+canonicalModes[it_part_reco->second]+"' AND TREENAME LIKE '"+(it_part_reco->first)+"' AND KSTYPE LIKE '"+(*it_KS)+"' AND YEAR LIKE '"+(*it_years)+"'";
	TString dbLinkPR = "SELECTION LIKE '"+selectionType+"' AND PARTRECO LIKE '"+it_part_reco->second+"' AND TREENAME LIKE '"+(it_part_reco->first)+"' AND KSTYPE LIKE '"+(*it_KS)+"' AND YEAR LIKE '"+(*it_years)+"'";
	
	// Retrive the estimation of the fraction information 
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
	    const unsigned char* frac_bkgLink    = sqlite3_column_text(stmt_pr, 12);
	    std::stringstream frac_bkg_tmp_str;
	    frac_bkg_tmp_str << frac_bkgLink;
	    frac_bkg_str = (frac_bkg_tmp_str).str();
	    Fraction_bkg_val = atof((frac_bkg_str).c_str()); 
	    // Fraction mean error value for each bkg 
	    const unsigned char* frac_bkgErrLink = sqlite3_column_text(stmt_pr, 13);
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
	
	// Add the Gaussian constraints
	//	fitter.addGaussianConstraint(("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)+"_"+(*it_KS)+"_"+(*it_years)).c_str(), Fraction_bkg_val, 10*Fraction_err_bkg_val);
	fitter.addGaussianConstraint(("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)+"_"+(*it_KS)+"_"+(*it_years)).c_str(), Fraction_bkg_val, Fraction_err_bkg_val);
	//	fitter.setParameterValue(("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)+"_"+(*it_KS)+"_"+(*it_years)).c_str(), Fraction_bkg_val, true);
	Fraction_bkg_val = 0;
	Fraction_err_bkg_val = 0;	
      }
    }
  }
  

  // Add gaussian constraints
  /*
	for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
	if ( (it_part_reco->first) == "pipi" ) {
	  if ( (it_part_reco->second) == "Bd2KSpipig"){ 
	  fitter.addGaussianConstraint(("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)).c_str(),   0.04, 0.008);
	  } else if ( (it_part_reco->second) == "Bd2etapKS_rhog"){ 
	  fitter.addGaussianConstraint(("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)).c_str(),   0.04, 0.004);
          } else if ( (it_part_reco->second) == "Bu2D0pi"){ 
	     fitter.addGaussianConstraint(("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)).c_str(),   0.40, 0.08);
          } else { 
	     fitter.addGaussianConstraint(("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)).c_str(),   0.04, 0.04);
          }
       } else if ( (it_part_reco->first) == "Kpi" ) {
	  for(std::vector<std::string>::iterator it_DP = DP_cat.begin(); it_DP    != DP_cat.end(); ++it_DP) {
	     if ( (it_part_reco->second) == "Bu2D0K"){ 
		fitter.addGaussianConstraint(("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)+"_"+(*it_DP)).c_str(),   0.26, 0.052);
             } else { 
		fitter.addGaussianConstraint(("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)+"_"+(*it_DP)).c_str(),   0.04, 0.03);
             }
	  }
       } else {
	  fitter.addGaussianConstraint(("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)).c_str(),   0.12, 0.12);
       }
    }
    */

  //================================================================================    
  
  //================================================================================
  // Finally perform the fit to the data and the plot some results.
  //================================================================================  
  //  return 0;
  //  fitter.getWS()->Print("v");
  std::cout << "Ready for the fit: "
	    << (std::time(NULL) - start_time) << " "
	    << (std::time(NULL) - temp_time)
	    << std::endl;
  temp_time = std::time(NULL);
  //  fitter.buildNewWorkspace("SimplifiedWS");
  std::time_t start_fit = std::time(NULL);
  fitter.performFit("fitResults",false);
  RooFitResult dataResults( *fitter.getFitResult( "fitResults" ) );
  dataResults.Print("v");
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
  fitter.setPlotBins( massvar, 50 ); // Set binning
  for(std::vector<std::string>::iterator it_years       = years.begin();     it_years    != years.end();     ++it_years) {
    for(std::vector<std::string>::iterator it_invMass = invMass.begin();  it_invMass != invMass.end();  ++it_invMass) {
      for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
	    if ((*it_invMass) == "pipi"){
	      fitter.plotMassAndPull((dir_plots+"KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Fit"+name).c_str(),
				     "m(#it{K}_{S}^{0}#it{#pi^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]",
				     ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), "fitResults", "log") ;
	    } else if ((*it_invMass) == "Kpi"){
	      fitter.plotMassAndPull((dir_plots+"KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Fit"+name).c_str(),
				     "m(#it{K}_{S}^{0}#it{K^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]",
				     ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), "fitResults", "log") ;
	      fitter.plotMassAndPull((dir_plots+"KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Fit"+name).c_str(),
				     "m(#it{K}_{S}^{0}#it{K^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]",
				     ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), "fitResults") ;
	    } else if ((*it_invMass) == "piK"){
	      fitter.plotMassAndPull((dir_plots+"KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Fit"+name).c_str(),
				     "m(#it{K}_{S}^{0}#it{K^{#font[122]{-}}#pi^{+}}) [MeV/#it{c}^{2}]", 
				     ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), "fitResults", "log") ;
	      fitter.plotMassAndPull((dir_plots+"KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Fit"+name).c_str(),
				     "m(#it{K}_{S}^{0}#it{K^{#font[122]{-}}#pi^{+}}) [MeV/#it{c}^{2}]",
				     ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(), "fitResults") ;
	    } else {
	      fitter.plotMassAndPull( (dir_plots+"KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Fit"+name).c_str(),
				      "m(#it{K}_{S}^{0}#it{K^{+}K^{#font[122]{-}}}) [MeV/#it{c}^{2}]",
				      ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(),"fitResults","log" ) ;
	      fitter.plotMassAndPull( (dir_plots+"KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)+"_Fit"+name).c_str(),
				      "m(#it{K}_{S}^{0}#it{K^{+}K^{#font[122]{-}}}) [MeV/#it{c}^{2}]",
				      ("KS"+(*it_invMass)+(*it_KS)+"_"+(*it_years)).c_str(),"fitResults" ) ;
	    }
      }
    }
  }
  std::cout << "Plots done: "
	    << (std::time(NULL) - start_time) << " "
	    << (std::time(NULL) - temp_time)
	    << std::endl;
  temp_time = std::time(NULL);

  //Copy the constraints files...
  //  std::ifstream inFile((V0hhDir+"KShh/Constraints/"+fileName+".txt").c_str());
  //  std::ofstream outFile((dir_plots+fileName+".txt").c_str());
  //  outFile << inFile.rdbuf();
  
  //================================================================================
  // Save everything in the workspace!
  //================================================================================  
  fitter.saveWS( (saveDir+"WS/Data-WS"+name+".root").c_str() );
  //================================================================================
  /*
  //================================================================================
  // Perform the integration for a given sigma of the mean
  //================================================================================  
  if (vm.count("integral"))
  {
  const RooArgList fitParams = dataResults.floatParsFinal();
  RooArgSet fittedParams( fitParams );
  TIterator* iter = fittedParams.createIterator();
  RooRealVar *arg = 0;
  std::string varName;
  Double_t mean_Bd(0), mean_Bs(0), sigmaDD(0), sigmaLL_r(0), sigma_Kpi_r(0), sigma_KK_r(0);
       std::map<std::string,Double_t> var_map_sig, var_map_bkg;
       while ( (arg = dynamic_cast<RooRealVar*>( iter->Next() ) ) ) {
	  varName = arg->GetName();
          if (varName == "Bd2KSpipiDD_pdf_mu"){ mean_Bd  = arg->getVal(); 
	  } else if  (varName == "Bs2KSpipiDD_pdf_mu"){ mean_Bs  = arg->getVal();
	  } else if (varName == "Bd2KSpipiDD_pdf_sigma"){ sigmaDD = arg->getVal();
	  } else if (varName == "ratio_width"){ sigmaLL_r = arg->getVal();
	  } else if (varName == "ratio_width_Kpi_pipi"){ sigma_Kpi_r = arg->getVal();
	  } else if (varName == "ratio_width_KK_pipi"){ sigma_KK_r = arg->getVal(); 
          } else {
	     for(std::vector<std::string>::iterator it_type     = type.begin();   it_type  != type.end();   ++it_type) {
                for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
                   for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
		      if ((*it_modes) == "Kpi"){
			 for(std::vector<std::string>::iterator it_DP = DP_cat.begin(); it_DP    != DP_cat.end(); ++it_DP) {
			    if ( integral_range.find(((*it_type)+"2KS"+(*it_modes)+"_"+(*it_DP)).c_str()) != integral_range.end() ) {
			       if (varName == (*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_"+(*it_DP)+"_pdf_KS"+(*it_modes)+(*it_KS)+"_"+(*it_DP)+"_Yield") {
				  var_map_sig.insert(std::make_pair((*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_"+(*it_DP)+"_pdf",arg->getVal()));
			       } else if ( varName == "combinatoric_"+(*it_modes)+(*it_KS)+"_"+(*it_DP)+"_KS"+(*it_modes)+(*it_KS)+"_"+(*it_DP)+"_Yield") {
				  var_map_bkg.insert(std::make_pair("combinatoric_"+(*it_modes)+(*it_KS)+"_"+(*it_DP),arg->getVal()));
			       }
			    }
			 }
		      } else {
			 if ( integral_range.find(((*it_type)+"2KS"+(*it_modes)).c_str()) != integral_range.end() ) {
			    if (varName == (*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf_KS"+(*it_modes)+(*it_KS)+"_Yield") {
			       var_map_sig.insert(std::make_pair((*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf",arg->getVal()));
			    } else if ( varName == "combinatoric_"+(*it_modes)+(*it_KS)+"_KS"+(*it_modes)+(*it_KS)+"_Yield") {
			       var_map_bkg.insert(std::make_pair("combinatoric_"+(*it_modes)+(*it_KS),arg->getVal()));
			    }
			 }
		      }
		   }
		}
	     }
	  }	
       }
       Double_t minRange(0.), maxRange(0.);
       RooRealVar *B_M_int = fitter.getWS()->var("B_M");
       RooAbsReal* norm_sig_aux = 0;
       RooAbsReal* norm_bkg_aux = 0;
       Double_t norm_sig, norm_bkg;
       std::multimap<Double_t,Double_t> input_Yields;
       Double_t mean(0), sigma(0);
       string_tools m_stringHelper;
       std::string mode;
       for(std::map<std::string,Double_t>::iterator it_bkg = var_map_bkg.begin(); it_bkg != var_map_bkg.end(); ++it_bkg){
	  for(std::map<std::string,Double_t>::iterator it_sig = var_map_sig.begin(); it_sig != var_map_sig.end(); ++it_sig){
	     std::cout << "Names : " << it_sig->first << " and bkg : " << it_bkg->first<< std::endl;
	     if ((it_sig->first).find("Bd") != std::string::npos) { mean = mean_Bd; } 
	     else { mean = mean_Bs; }

             if (((it_sig->first).find("pipi") != std::string::npos) && ((it_sig->first).find("DD") != std::string::npos) && ((it_bkg->first).find("pipi") != std::string::npos) && ((it_bkg->first).find("DD") != std::string::npos)) {
		sigma =  sigma_input*sigmaDD;
	     } else if (((it_sig->first).find("pipi") != std::string::npos) && ((it_sig->first).find("LL") != std::string::npos) && ((it_bkg->first).find("pipi") != std::string::npos) && ((it_bkg->first).find("LL") != std::string::npos)) {
		sigma =  sigma_input*sigmaLL_r*sigmaDD;
	     } else if (((it_sig->first).find("Kpi") != std::string::npos) && ((it_sig->first).find("DD") != std::string::npos) && ((it_sig->first).find("DP1") != std::string::npos) && ((it_bkg->first).find("Kpi") != std::string::npos) && ((it_bkg->first).find("DD") != std::string::npos) && ((it_bkg->first).find("DP1") != std::string::npos)) {
		sigma =  sigma_input*sigma_Kpi_r*sigmaDD;
	     } else if (((it_sig->first).find("Kpi") != std::string::npos) && ((it_sig->first).find("LL") != std::string::npos) && ((it_sig->first).find("DP1") != std::string::npos) && ((it_bkg->first).find("Kpi") != std::string::npos) && ((it_bkg->first).find("LL") != std::string::npos) && ((it_bkg->first).find("DP1") != std::string::npos)) {
		sigma =  sigma_input*sigma_Kpi_r*sigmaLL_r*sigmaDD;
	     } else if (((it_sig->first).find("Kpi") != std::string::npos) && ((it_sig->first).find("DD") != std::string::npos) && ((it_sig->first).find("DP2") != std::string::npos) && ((it_bkg->first).find("Kpi") != std::string::npos) && ((it_bkg->first).find("DD") != std::string::npos) && ((it_bkg->first).find("DP2") != std::string::npos)) {
		sigma =  sigma_input*sigma_Kpi_r*sigmaDD;
	     } else if (((it_sig->first).find("Kpi") != std::string::npos) && ((it_sig->first).find("LL") != std::string::npos) && ((it_sig->first).find("DP2") != std::string::npos) && ((it_bkg->first).find("Kpi") != std::string::npos) && ((it_bkg->first).find("LL") != std::string::npos) && ((it_bkg->first).find("DP2") != std::string::npos)) {
		sigma =  sigma_input*sigma_Kpi_r*sigmaLL_r*sigmaDD;
	     } else if (((it_sig->first).find("KK") != std::string::npos) && ((it_sig->first).find("DD") != std::string::npos) && ((it_bkg->first).find("KK") != std::string::npos) && ((it_bkg->first).find("DD") != std::string::npos)) {
		sigma =  sigma_input*sigma_KK_r*sigmaDD;
	     } else if (((it_sig->first).find("KK") != std::string::npos) && ((it_sig->first).find("LL") != std::string::npos) && ((it_bkg->first).find("KK") != std::string::npos) && ((it_bkg->first).find("LL") != std::string::npos)) {
		sigma =  sigma_input*sigma_KK_r*sigmaLL_r*sigmaDD;
	     } else {
		continue;
	     }
					
             minRange = mean - sigma;
             maxRange = mean + sigma;

	     B_M_int->setRange("sigma", minRange, maxRange);
	     norm_sig_aux = fitter.getWS()->pdf((it_sig->first).c_str())->createIntegral( *B_M_int, RooFit::NormSet(*B_M_int), RooFit::Range("sigma")) ; 
	     norm_bkg_aux = fitter.getWS()->pdf((it_bkg->first).c_str())->createIntegral( *B_M_int, RooFit::NormSet(*B_M_int), RooFit::Range("sigma")) ; 
	     norm_sig = norm_sig_aux->getVal() * (it_sig->second);
	     norm_bkg = norm_bkg_aux->getVal() * (it_bkg->second);

             mode = it_sig->first;
	     std::cout << "Modes : " << mode << std::endl;
             m_stringHelper.replaceAll( mode, "_pdf", "" ); 
	     fitter.saveDPInfo( norm_sig, norm_bkg, filename.c_str(), mode.c_str(), minRange, maxRange); 
	  }   
       }   
    }
    //================================================================================
    // ToyMC studies
    //================================================================================  
    */
    if (ToyMC){
      if (dataResults.covQual() != 3 || dataResults.status() != 0 || dataResults.edm() > 1.)
	{
	  std::cout << "Original fit did not even converge properly..." << std::endl;
	}
       V0hhFit::ToyStudy toy( &fitter, nExp );
       
       // Set Bs2KSKK initial yield to zero if is blind  
       if (Bs_blind){
	 std::string instructions("");
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
	 //	 toy.runToyStudy( "fitResults" , instructions.c_str(),"","Bd2KSKpiDD_2011_pdf_KSKpiDD_2011_Yield,Bd2KSpipiDD_2011_pdf_KSpipiDD_2011_Yield");
	 toy.runToyStudy( "fitResults" , instructions.c_str(),"","",true);
       } else {
	 toy.runToyStudy( "fitResults" );
       }
       
       // Plot Toy MC results
       toy.plotErrorVsResiduals ((name+"ErrVsRes").c_str());
       toy.plotNlls             ((name+"Nlls").c_str());
       toy.plotValues           ((name+"Values").c_str());
       toy.plotResiduals        ((name+"Residuals").c_str());
       toy.plotPulls            ((name+"Pulls").c_str());
    }
    
    return 0;
}
