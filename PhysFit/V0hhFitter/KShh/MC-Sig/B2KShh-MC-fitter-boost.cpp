#include <iostream>
#include <sstream>
#include <string>
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

// Fitter
#include "V0hhFitter/ToyStudy.h"
#include "V0hhFitter/SimultaneousFitter.h"
#include "boost/program_options.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/bind.hpp"

#include "KShh/MC-Sig/constraints.cpp"
#include "KShh/Constraints/useConstraints.cpp"

int main( int argc, char* argv[] ) {
  std::vector<std::string> years;
  std::vector<std::string> modes;
  std::vector<std::string> KS_cat;
  std::vector<std::string> cf;
  std::vector<std::string> name;
  std::string sig_shape("");
  std::string selectionType("");
  std::string option_name("Vanilla");
  int nToys;
  int yields;
  std::string constraints("");
  std::string toyModel("");
  int seed;
  namespace po = boost::program_options; 
  po::options_description decisions("Options");     
  decisions.add_options()
    ("help,h", "produce help message")
    ("yearPeriod,y"  , boost::program_options::value< std::vector< std::string > >( &years )->multitoken(), "specify the list of MC year conditions to be considered. Options are: 2011, 2012a, 2012b")
    ("sigModes,s"    , boost::program_options::value< std::vector< std::string > >( &modes )->multitoken(), "specify the signal modes to be fitted. Options are: Bd2KSpipi, Bs2KSpipi, Bd2KSKpi, Bd2KSpiK, Bs2KSKpi, Bs2KSpiK, Bd2KSKK, Bs2KSKK")
    ("KS,k"          , boost::program_options::value< std::vector< std::string > >( &KS_cat )->multitoken(), "specify the KS category : DD, LL")
    ("sigShape"      , boost::program_options::value<std::string>(&sig_shape), "specify the alternative signal mode shape : Cruijff, Apollonios, Amoroso, Hypatia or Hypatia2")
    ("selectionBDT,b", boost::program_options::value<std::string>(&selectionType), "specify which selection has been used in the sample: Loose, Tight, DP1 or DP2")
    ("option,o"      , boost::program_options::value<std::string>(&option_name), "option to save WS for systematics studies with different signal shape: name of to be added to the WS filename, e.g. SystII")
    ("nToys,n"       , boost::program_options::value<int>(&nToys), "option to set the number of generated toys")
    ("toyModel,t"    , boost::program_options::value<std::string>(&toyModel), "option to set the toy instructions.")
    ("yields,Y"      , boost::program_options::value<int>(&yields), "option to set the yields.")
    ("constraints,c" , boost::program_options::value<std::string>(&constraints), "option to set the constraints to a predefined set.")
    ("seed"          , boost::program_options::value<int>(&seed), "option to set the seed.")
    ;
    boost::program_options::variables_map vm;
    boost::program_options::store( boost::program_options::parse_command_line( argc, argv, decisions ), vm );
    boost::program_options::notify( vm );

  if( vm.count("help") ) {
    std::cout << decisions << std::endl;
    std::exit(0);
  }
  std::cout << "-------------------------------------------" << std::endl;
  if (vm.count("sigModes")) {
    if ((modes[0] != "Bd2KSpipi") && (modes[0] != "Bs2KSpipi") && (modes[0] != "Bd2KSKpi") && (modes[0] != "Bd2KSpiK") && (modes[0] != "Bs2KSKpi") && (modes[0] != "Bs2KSpiK") && (modes[0] != "Bd2KSKK") && (modes[0] != "Bs2KSKK")){
      std::cerr << "ERROR: No signal mode has been included" << std::endl; 
      std::exit(0);
    } else {
      for(std::vector<std::string>::iterator it_modes = modes.begin(); it_modes != modes.end(); ++it_modes) {
             std::cout << "INFO: Adding signal mode for " << (*it_modes) << " decays" << std::endl;
          }
       }
    } else {
      std::cout << "INFO: All signal modes are considered" << std::endl;
      modes.push_back("Bd2KSpipi");
      modes.push_back("Bs2KSpipi");
      modes.push_back("Bd2KSKpi");
      modes.push_back("Bs2KSKpi");
      modes.push_back("Bd2KSpiK");
      modes.push_back("Bs2KSpiK");
      modes.push_back("Bd2KSKK");
      modes.push_back("Bs2KSKK");
    }
    if (vm.count("KS")) {
      for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS != KS_cat.end(); ++it_KS) {
	std::cout << "INFO: Adding KS category " << (*it_KS) << std::endl;
      }
    } else {
      std::cout << "INFO: All KS categories are included" << std::endl;
      KS_cat.push_back("DD");
      KS_cat.push_back("LL");
    }
    if (!vm.count("yearPeriod")){
      std::cout << "INFO: Setting the default configuration for all years 2011, 2012a and 2012b conditions" << std::endl;
      years.push_back("2011");
      years.push_back("2012a");
      years.push_back("2012b");
    } else {
      for(std::vector<std::string>::iterator it_years = years.begin(); it_years != years.end(); ++it_years) {
	std::cout << "INFO: Adding samples for " << (*it_years) << " conditions" << std::endl;
      }
    }
    if (vm.count("selectionBDT")) {
      std::cout << "INFO: Setting the sample with the " << selectionType << " selection" << std::endl;
    } else {
      selectionType = "Loose"; 
    }
    if (vm.count("sigShape")) {
      std::cout << "INFO: Modifying nominal signal model to " << sig_shape << std::endl;
    } else {
      sig_shape = "DoubleCB"; 
    }
    if (vm.count("nToys")) {
      std::cout << "INFO: We will generate: " << nToys << " toys." <<std::endl;
    } else {
      nToys = 500;
    }
    if (vm.count("option")){
      std::cout << "INFO: We will proceed with option " << option_name << "." << std::endl;
      ifstream f;
      f.open((std::string(getenv("V0HHFITTERROOT"))+"KShh/Constraints/constraints-SignalOnly-"+option_name+".txt").c_str());
      if (!f.is_open())
	{
	  std::cout << "ERROR: Constraint file setting " << (std::string(getenv("V0HHFITTERROOT"))+"KShh/Constraints/constraints-SignalOnly-"+option_name+".txt") << " does not exist." << std::endl;
	  return 0;
	}
      f.close();
    }
    if (vm.count("toyModel")) {
      std::cout << "INFO: We will toys with model: " << toyModel << "." <<std::endl;
    } else {
      toyModel = "2011";
    }
    if (vm.count("yields")) {
      std::cout << "INFO: We will toys with yields: " << yields << "." <<std::endl;
    } else {
      yields = 500;
    }
    if (vm.count("constraints")) {
      std::cout << "INFO: Modifying constraints set to " << constraints << std::endl;
    } else {
      constraints = "Vanilla";
    }
    if (vm.count("seed"))
      std::cout << "INFO: Setting the seed to " << seed << std::endl;	
    else
      seed = 1;

    //================================================================================

    // Invariant masses 
    std::vector<std::string> invMass;
    invMass.push_back("pipi");
    invMass.push_back("Kpi");
    invMass.push_back("piK");
    invMass.push_back("KK");

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
    std::string fileName("constraints-SignalOnly-"+option_name);
    
    //================================================================================
    
    //================================================================================
    // Make all PDFs 
    //================================================================================
    for(std::vector<std::string>::iterator it_year     = years.begin();   it_year  != years.end();   ++it_year) {
      for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
	 for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
	   if (sig_shape == "Cruijff"){	      
	     fitter.makeCruijff(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 5300, 5250, 5375, 5, 0, 20, 1, 0, 5, 1, 0, 5);  
	   } else if (sig_shape == "CruijffSimple"){
	     fitter.makeCruijff(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 5300, 5250, 5375, 5, 0, 20, 1, 0, 5, 1, 0, 5);  
	   } else if (sig_shape == "Apollonios"){
	     fitter.makeApollonios(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 5300, 5250, 5375, 5, 0, 20, 1, -5, 10, 1, -5, 10, 1, 0, 5);
	   } else if (sig_shape == "Amoroso"){
	     fitter.makeAmoroso(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 5300, 5250, 5375, 5, 0, 20, 1.5, 0, 10, 2.3, 0, 5);
	   } else if (sig_shape == "Hypatia"){
	     fitter.makeHypatia(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(),  1, -1, 3, 1, 0, 10, 0, 5, 0, 20, 5300, 5250, 5375, 1, -5, 5, 2, 0, 10);
	   } else if (sig_shape == "Hypatia2"){
	     fitter.makeHypatia2(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 1, -2, 3, 1, 0, 10, 0, 5, 0, 20, 5300, 5250, 5375, 1, -5, 5, 2, 0, 10, 1, -5, 5, 2, 0, 10);
	   } else if (sig_shape == "DoubleGauss"){
	     fitter.makeDoubleGauss(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 5300,5250,5375,0.,-200.,200.,20,8,40,2.,1.,10.,0.5);
	   } else {
	     if ((*it_modes).find("Bd") != std::string::npos) { 
	       fitter.makeDoubleCB(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 5279, 5269, 5389, 8, 0, 20, 1, 0, 5, -1, -5, 0, 1, 0, 5, 1, 0 ,5, 0.5);
	     } else {
			 fitter.makeDoubleCB(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 5366, 5356, 5376, 8, 0, 25, 1, 0, 5, -1, -5, 0, 1, 0, 5, 1, 0 ,5, 0.5);
	     }
	   }
	 }
      }
    }
    std::cout << "PDFs ready" << std::endl;
    //================================================================================
    
    //================================================================================
    // Import the dataset 
    //================================================================================
    TString dataDir = getenv("V0HHFITTERDATA");
    std::string data_aux = (dataDir).Data(); 
    //std::string basedir = data_aux+"/KShh/MonteCarlo/";
    std::string basedir = "/afs/cern.ch/work/r/rsilvaco/V0hhFitter/KShh/MonteCarlo/";
    TFile *file = 0;
    TTree* tree = 0;
    
    for(std::vector<std::string>::iterator it_year     = years.begin();   it_year  != years.end();   ++it_year) {
      for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
	for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
	  std::vector<std::string> name_split;
	  boost::split(name_split,(*it_modes),boost::is_any_of("2"));
	  name_split[1].erase(0,2);
	  if (name_split[1] == "piK"){
	    file = TFile::Open( (basedir+(*it_year)+"/KShhFit/"+selectionType+"/KS"+(name_split[1])+"/"+(name_split[0])+"2KSKpi-MC-"+(*it_year)+"-MagAll.root").c_str(), "READ" );
	  } else{
	    file = TFile::Open( (basedir+(*it_year)+"/KShhFit/"+selectionType+"/KS"+(name_split[1])+"/"+(name_split[0])+"2KS"+(name_split[1])+"-MC-"+(*it_year)+"-MagAll.root").c_str(), "READ" );
	  }
	  tree = dynamic_cast<TTree*>( file->Get( ("B2KShh"+(*it_KS)+"/B2"+(name_split[1])+"KS").c_str() ) );
	  fitter.makeMassDataSet( tree, massvar, ((name_split[0])+"2KS"+(name_split[1])+(*it_KS)+"_"+(*it_year)).c_str(), "" ) ; 
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
    //================================================================================
   
    //================================================================================
    // Set the constraints between the signal and crossfeeds for the various years  
    //================================================================================    
    std::vector<std::string> vars;
    if (sig_shape == "DoubleCB")
      {
	vars.push_back("mu");
	vars.push_back("sigma");
	vars.push_back("alpha0");
	vars.push_back("alpha1oAlpha0");
	vars.push_back("n0");
	vars.push_back("n1oN0");
	vars.push_back("coreFrac");
      }
    else if (sig_shape == "CruijffSimple")
      {
	vars.push_back("mu");
	vars.push_back("sigma");
	vars.push_back("alphaL");
	vars.push_back("alphaR");
      }
    else if (sig_shape == "Cruijff")
      {
	vars.push_back("mu");
	//	vars.push_back("sigmaL");
	//	vars.push_back("sigmaR");
	vars.push_back("sigma");
	vars.push_back("alphaL");
	vars.push_back("alphaR");
      }
    else if (sig_shape == "DoubleGauss")
      {
		  vars.push_back("mu");
		  vars.push_back("sigma0");
		  vars.push_back("s1oS0");
		  vars.push_back("dM");
		  vars.push_back("coreFrac");
      }

    //Getting rid of piK
	//	KShhConstraints::bindPiK(fitter,years,modes,KS_cat,vars);

    //Setting the means    
    bool isConstrained(true);
	//    isConstrained = false;
    if (isConstrained)
		{
			if (sig_shape == "DoubleCB" || sig_shape == "Cruijff")
				{
					for (std::vector<std::string>::iterator itYears = years.begin() ; itYears != years.end() ; ++itYears)
						{
							fitter.addParameter(("mu(Bd)("+*itYears+")").c_str(),5250.,5310.);
							fitter.addParameter(("mu(Bs)("+*itYears+")").c_str(),5340.,5400.);
							for (std::vector<std::string>::iterator itModes = modes.begin() ; itModes != modes.end() ; ++itModes)
								//	      if (itModes->find("piK") == std::string::npos)
								for (std::vector<std::string>::iterator itKS = KS_cat.begin() ; itKS != KS_cat.end() ; ++itKS)
									{
										if (itModes->find("Bs") != std::string::npos)
											fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_mu").c_str(),"@0",("mu(Bs)("+*itYears+")").c_str());
										else
											fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_mu").c_str(),"@0",("mu(Bd)("+*itYears+")").c_str());
									}
						}
					//Setting the sigmas
					fitter.addParameter("Sigma(Bd)(pipi)(DD)(2011)",         8.,        30.);
					fitter.addParameter("kSig(Kpi)(2011)"       ,         0.,         2.);
					fitter.addParameter("kSig(KK)(2011)"        ,         0.,         2.);
					fitter.addParameter("kSig(LL)(2011)"        ,         0.,         2.);
					if (std::find(years.begin(),years.end(),"2012a") != years.end())
						{
							fitter.addParameter("Sigma(Bd)(pipi)(DD)(2012a)",         8.,        30.);
							fitter.addParameter("kSig(Kpi)(2012a_o_2011)"       ,         0.,         2.); //Gaussian Constrained
							fitter.addParameter("kSig(KK)(2012a_o_2011)"        ,         0.,         2.); //Gaussian Constrained
							fitter.addParameter("kSig(LL)(2012a_o_2011)"        ,         0.,         2.); //Gaussian Constrained
						}
					if (std::find(years.begin(),years.end(),"2012b") != years.end())
						{
							fitter.addParameter("Sigma(Bd)(pipi)(DD)(2012b)",         8.,        30.);
							fitter.addParameter("kSig(Kpi)(2012b_o_2011)"       ,         0.,         2.); //Gaussian Constrained
							fitter.addParameter("kSig(KK)(2012b_o_2011)"        ,         0.,         2.); //Gaussian Constrained
							fitter.addParameter("kSig(LL)(2012b_o_2011)"        ,         0.,         2.); //Gaussian Constrained
						}
					fitter.addParameter("kSig(Bs)(2011)"        ,         0.,         2.);
					if (std::find(years.begin(),years.end(),"2012a") != years.end())
						fitter.addParameter("kSig(Bs)(2012a_o_2011)"        ,         0.,         2.); //Gaussian Constrained
					if (std::find(years.begin(),years.end(),"2012b") != years.end())
						fitter.addParameter("kSig(Bs)(2012b_o_2011)"        ,         0.,         2.); //Gaussian Constrained
					
					for (std::vector<std::string>::iterator itYears = years.begin() ; itYears != years.end() ; ++itYears)
						{
							for (std::vector<std::string>::iterator itModes = modes.begin() ; itModes != modes.end(); ++itModes)
								for (std::vector<std::string>::iterator itKS = KS_cat.begin() ; itKS != KS_cat.end(); ++itKS)	
									{	
										std::string dependents = "Sigma(Bd)(pipi)(DD)("+*itYears+")";
										std::string formula    = "@0";
										int nDeps = 1;
										if (itModes->find("Bs") != std::string::npos){
											dependents += ",kSig(Bs)(2011)";
											formula    += "*@"+KShhConstraints::itoa(nDeps);
											nDeps++;
											if (itYears->find("2012a") != std::string::npos){
												dependents += ",kSig(Bs)(2012a_o_2011)";
												formula    += "*@"+KShhConstraints::itoa(nDeps);
												nDeps++;
											}
											else if (itYears->find("2012b") != std::string::npos){
												dependents += ",kSig(Bs)(2012b_o_2011)";
												formula    += "*@"+KShhConstraints::itoa(nDeps);
												nDeps++;
											}
										}
										if (itKS->find("LL") != std::string::npos){
											dependents += ",kSig(LL)(2011)";
											formula    += "*@"+KShhConstraints::itoa(nDeps);
											nDeps++;
											if (itYears->find("2012a") != std::string::npos){
												dependents += ",kSig(LL)(2012a_o_2011)";
												formula    += "*@"+KShhConstraints::itoa(nDeps);
												nDeps++;
											}
											else if (itYears->find("2012b") != std::string::npos){
												dependents += ",kSig(LL)(2012b_o_2011)";
												formula    += "*@"+KShhConstraints::itoa(nDeps);
												nDeps++;
											}
										}
										if (itModes->find("Kpi") != std::string::npos || itModes->find("piK") != std::string::npos){
											dependents += ",kSig(Kpi)(2011)";
											formula    += "*@"+KShhConstraints::itoa(nDeps);
											nDeps++;
											if (itYears->find("2012a") != std::string::npos){
												dependents += ",kSig(Kpi)(2012a_o_2011)";
												formula    += "*@"+KShhConstraints::itoa(nDeps);
												nDeps++;
											}
											else if (itYears->find("2012b") != std::string::npos){
												dependents += ",kSig(Kpi)(2012b_o_2011)";
												formula    += "*@"+KShhConstraints::itoa(nDeps);
												nDeps++;
											}
										}
										else if (itModes->find("KK") != std::string::npos){
											dependents += ",kSig(KK)(2011)";
											formula    += "*@"+KShhConstraints::itoa(nDeps);
											nDeps++;
											if (itYears->find("2012a") != std::string::npos){
												dependents += ",kSig(KK)(2012a_o_2011)";
												formula    += "*@"+KShhConstraints::itoa(nDeps);
												nDeps++;
											}
											else if (itYears->find("2012b") != std::string::npos){
												dependents += ",kSig(KK)(2012b_o_2011)";
												formula    += "*@"+KShhConstraints::itoa(nDeps);
												nDeps++;
											}
										}
										fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_sigma").c_str(),formula.c_str(),dependents.c_str());
									}
						}
					//Gaussian now!
					double mean(0), width(0);
					//	mean  = 
					width = KShhConstraints::readWidth(fileName,"kSig(LL)");
					if (width != 0)
						{
							if (std::find(years.begin(),years.end(),"2012a") != years.end())
								fitter.addGaussianConstraint("kSig(LL)(2012a_o_2011)",1.,width);
							if (std::find(years.begin(),years.end(),"2012b") != years.end())
								fitter.addGaussianConstraint("kSig(LL)(2012b_o_2011)",1.,width);
						}
					else
						{
							if (std::find(years.begin(),years.end(),"2012a") != years.end())
								fitter.setParameterConstant("kSig(LL)(2012a_o_2011)");
							if (std::find(years.begin(),years.end(),"2012b") != years.end())
								fitter.setParameterConstant("kSig(LL)(2012b_o_2011)");
						}
					width = KShhConstraints::readWidth(fileName,"kSig(Bs)");
					if (width != 0)
						{
							fitter.addGaussianConstraint("kSig(Bs)(2011)",1.,width);
							if (std::find(years.begin(),years.end(),"2012a") != years.end())
								fitter.addGaussianConstraint("kSig(Bs)(2012a_o_2011)",1.,width);
							if (std::find(years.begin(),years.end(),"2012b") != years.end())
								fitter.addGaussianConstraint("kSig(Bs)(2012b_o_2011)",1.,width);
						}
					else
						{
							if (std::find(years.begin(),years.end(),"2012a") != years.end())
								fitter.setParameterConstant("kSig(Bs)(2012a_o_2011)");
							if (std::find(years.begin(),years.end(),"2012b") != years.end())
								fitter.setParameterConstant("kSig(Bs)(2012b_o_2011)");
						}
					width = KShhConstraints::readWidth(fileName,"kSig(Mode)");
					if (width != 0)
						{
							if (std::find(years.begin(),years.end(),"2012a") != years.end())
								fitter.addGaussianConstraint("kSig(Kpi)(2012a_o_2011)",1.,width);
							if (std::find(years.begin(),years.end(),"2012b") != years.end())
								fitter.addGaussianConstraint("kSig(Kpi)(2012b_o_2011)",1.,width);	
							if (std::find(years.begin(),years.end(),"2012a") != years.end())
								fitter.addGaussianConstraint("kSig(KK)(2012a_o_2011)",1.,width);
							if (std::find(years.begin(),years.end(),"2012b") != years.end())
								fitter.addGaussianConstraint("kSig(KK)(2012b_o_2011)",1.,width);
						}
					else
						{
							if (std::find(years.begin(),years.end(),"2012a") != years.end())
								fitter.setParameterConstant("kSig(Kpi)(2012a_o_2011)");
							if (std::find(years.begin(),years.end(),"2012a") != years.end())
								fitter.setParameterConstant("kSig(KK)(2012a_o_2011)");
							if (std::find(years.begin(),years.end(),"2012b") != years.end())
								fitter.setParameterConstant("kSig(Kpi)(2012b_o_2011)");
							if (std::find(years.begin(),years.end(),"2012b") != years.end())
								fitter.setParameterConstant("kSig(KK)(2012b_o_2011)");
						}
				}
			//Alpha0 & N0 & CoreFrac
			if (sig_shape == "DoubleCB")
				{
					/*
					  fitter.addParameter("Alpha0(pipi)",0.,10.);
					  fitter.addParameter("N0(pipi)"    ,0.,10.);
					  fitter.addParameter("CoreFrac(pipi)",0.,1.);
					  fitter.addParameter("Alpha0(Kpi)",0.,10.);
					  fitter.addParameter("N0(Kpi)"    ,0.,10.);
					  fitter.addParameter("CoreFrac(Kpi)",0.,1.);
					  fitter.addParameter("Alpha0(KK)",0.,10.);
					  fitter.addParameter("N0(KK)"    ,0.,10.);
					  fitter.addParameter("CoreFrac(KK)",0.,1.);
					*/
					for (std::vector<std::string>::iterator itYears = years.begin() ; itYears != years.end() ; ++itYears)
						{
							fitter.addParameter(("Alpha0(pipi)("  +(*itYears)+")").c_str(),0.,10.);
							fitter.addParameter(("N0(pipi)("      +(*itYears)+")").c_str()    ,0.,10.);
							fitter.addParameter(("CoreFrac(pipi)("+(*itYears)+")").c_str(),0.,1.);
							fitter.addParameter(("Alpha0(Kpi)("   +(*itYears)+")").c_str(),0.,10.);
							fitter.addParameter(("N0(Kpi)("       +(*itYears)+")").c_str()    ,0.,10.);
							fitter.addParameter(("CoreFrac(Kpi)(" +(*itYears)+")").c_str(),0.,1.);
							fitter.addParameter(("Alpha0(KK)("    +(*itYears)+")").c_str(),0.,10.);
							fitter.addParameter(("N0(KK)("        +(*itYears)+")").c_str()    ,0.,10.);
							fitter.addParameter(("CoreFrac(KK)("  +(*itYears)+")").c_str(),0.,1.);
						}
					for (std::vector<std::string>::iterator itYears = years.begin() ; itYears != years.end() ; ++itYears)
						for (std::vector<std::string>::iterator itModes = modes.begin() ; itModes != modes.end() ; ++itModes)
							for (std::vector<std::string>::iterator itKS = KS_cat.begin() ; itKS != KS_cat.end() ; ++itKS)
								{
									if (itModes->find("pipi") != std::string::npos)
										{
											/*
											  fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha0").c_str()  ,"@0","Alpha0(pipi)");
											  fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n0").c_str()      ,"@0",    "N0(pipi)");
											  fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_coreFrac").c_str(),"@0","CoreFrac(pipi)");
											*/
											fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha0").c_str()  ,"@0",("Alpha0(pipi)("+(*itYears)+")").c_str());
											fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n0").c_str()      ,"@0",(    "N0(pipi)("+(*itYears)+")").c_str());
											fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_coreFrac").c_str(),"@0",("CoreFrac(pipi)("+(*itYears)+")").c_str());
										}
									else if (itModes->find("Kpi") != std::string::npos || itModes->find("piK") != std::string::npos)
										{
											/*
											  fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha0").c_str()  ,"@0","Alpha0(Kpi)");
											  fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n0").c_str()      ,"@0",    "N0(Kpi)");
											  fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_coreFrac").c_str(),"@0","CoreFrac(Kpi)");
											*/
											fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha0").c_str()  ,"@0",("Alpha0(Kpi)("+(*itYears)+")").c_str());
											fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n0").c_str()      ,"@0",(    "N0(Kpi)("+(*itYears)+")").c_str());
											fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_coreFrac").c_str(),"@0",("CoreFrac(Kpi)("+(*itYears)+")").c_str());
										}
									else
										{
											/*
											  fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha0"  ).c_str(),"@0","Alpha0(KK)");
											  fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n0"      ).c_str(),"@0",    "N0(KK)");
											  fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_coreFrac").c_str(),"@0","CoreFrac(KK)");
											*/
											fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha0").c_str()  ,"@0",("Alpha0(KK)("+(*itYears)+")").c_str());
											fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n0").c_str()      ,"@0",(    "N0(KK)("+(*itYears)+")").c_str());
											fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_coreFrac").c_str(),"@0",("CoreFrac(KK)("+(*itYears)+")").c_str());
										}
								}
					//Alpha1 & N1
					
					fitter.addParameter("Alpha1oAlpha0",-10.,0.);
					fitter.addParameter("N1oN0"    ,0.,10.);
					for (std::vector<std::string>::iterator itYears = years.begin() ; itYears != years.end() ; ++itYears)
						for (std::vector<std::string>::iterator itModes = modes.begin() ; itModes != modes.end() ; ++itModes)
							for (std::vector<std::string>::iterator itKS = KS_cat.begin() ; itKS != KS_cat.end() ; ++itKS)
								{
									fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha1oAlpha0").c_str()  ,"@0","Alpha1oAlpha0");
									fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n1oN0").c_str()      ,"@0",    "N1oN0");
								}
				}
		}
	if (sig_shape == "Cruijff")
		{
		}
	if (sig_shape == "DoubleGauss")
		{
			//			KShhConstraints::setDoubleGauss(fitter,years,modes,KS_cat,"Vanilla");
		}
	
    //================================================================================
    
    //================================================================================
    // Finally perform the fit to the data and the plot some results.
    //================================================================================  
    fitter.performFit("fitResults");
    RooFitResult res(*fitter.getFitResult( "fitResults" ));
    res.Print("v");
    //fitter.getWS()->Print("V");
    //Actualize the values...
    for (std::vector<std::string>::iterator it = vars.begin() ; it != vars.end() ; it++) {
		for(std::vector<std::string>::iterator it_year = years.begin();   it_year  != years.end();   ++it_year) {
			for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {	
				for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
					std::string name = (*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf_";
					std::string newName = name;
					size_t start_pos = newName.find("piK");
					if (!(start_pos == std::string::npos))	      
						newName.replace(start_pos, (std::string("piK")).length(), std::string("Kpi"));
					RooWorkspace *w = fitter.getWS();
					//firstly get the newest function.
					RooFormulaVar* testFormula = (RooFormulaVar*) w->function((newName+(*it)+"_function").c_str());
					RooFormulaVar* formula = NULL;
					Double_t val,error;
					while (testFormula != NULL)
						{
							formula = testFormula;
							testFormula = (RooFormulaVar*) w->function((((TString)formula->GetName())+"_new").Data());
							val = formula->getVal();
							//Get the error is a tad more complicated...
							//WARNING: This DOES NOT take into account several parameters formula.
							if (testFormula == NULL)
								{
									if (!(TString(formula->getParameter(0)->IsA()->GetName()) == "RooRealVar"))
										{
											std::cout << "ERROR: " << formula->getParameter(0)->GetName() << " " << formula->getParameter(0)->IsA()->GetName() <<std::endl;
											assert(0);
										}
									//		    if (name.find("piK") != std::string::npos)
									//		      std::cout << "DEBUG " << name << " " << formula->getParameter(0)->GetName() << std::endl;
									error = ((RooRealVar*) formula->getParameter(0))->getError();		
								}
						}
					RooRealVar *var = w->var((name+(*it)).c_str());
					var->setVal(val);	    
					if (var->getVal() != val)
						std::cout << "ERROR: " << name << *it << " " << var->getVal() << " " << val << std::endl;
					var->setError(error);
					w->import(*var,RooFit::RecycleConflictNodes(kTRUE));
					//	    std::cout << name << *it << " " << var->getVal() << " " << var->getError() << std::endl;
				}
			}
		}
    }    
    //================================================================================  



    //================================================================================
    // Plot invariant mass spectra and residuals
    //================================================================================  
    fitter.setPlotSubComponents(true);
    std::string dir_plots   = saveDir+"MC-Sig/plots/"+selectionType+"/";
    std::string prefix_name = "_MCFit";
    if (sig_shape != "DoubleCB"){ prefix_name += "_"+sig_shape;} 
    fitter.setPlotBins( massvar, 40 ); // Set binning
    if (modes[0] != "none"){
       for(std::vector<std::string>::iterator it_year = years.begin();   it_year  != years.end();   ++it_year) {
          for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
             for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
                if ((*it_modes).find("pipi") != std::string::npos) {
                   fitter.plotMassAndPull( (dir_plots+(*it_modes)+(*it_KS)+"_"+(*it_year)+prefix_name).c_str(), "m(#it{K}_{S}^{0}#it{#pi^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]", ((*it_modes)+(*it_KS)+"_"+(*it_year)).c_str(), "fitResults") ;
                } else if ((*it_modes).find("Kpi") != std::string::npos) {
                   fitter.plotMassAndPull( (dir_plots+(*it_modes)+(*it_KS)+"_"+(*it_year)+prefix_name).c_str(), "m(#it{K}_{S}^{0}#it{K^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]", ((*it_modes)+(*it_KS)+"_"+(*it_year)).c_str(), "fitResults", "log") ;
                } else if ((*it_modes).find("piK") != std::string::npos) {
					fitter.plotMassAndPull( (dir_plots+(*it_modes)+(*it_KS)+"_"+(*it_year)+prefix_name).c_str(), "m(#it{K}_{S}^{0}#it{K^{#font[122]{-}}#pi^{+}}) [MeV/#it{c}^{2}]", ((*it_modes)+(*it_KS)+"_"+(*it_year)).c_str(), "fitResults", "log") ;
                } else {
                   fitter.plotMassAndPull( (dir_plots+(*it_modes)+(*it_KS)+"_"+(*it_year)+prefix_name).c_str(), "m(#it{K}_{S}^{0}#it{K^{+}K^{#font[122]{-}}}) [MeV/#it{c}^{2}]",((*it_modes)+(*it_KS)+"_"+(*it_year)).c_str(), "fitResults", "log") ;
                }
             }
          }
       }
    } 
    //================================================================================    

    //================================================================================
    // Save everything in the workspace!
    //================================================================================  
    std::string saveName((saveDir+"WS/MC-Sig-WS-"+selectionType+"-"+sig_shape+"-"+option_name).c_str());
    saveName += ".root";
    fitter.saveWS( saveName.c_str());
    std::cout << saveName << std::endl;
    return 0;

    std::map<std::string,double> yieldsToy;
    bool begin(true);
    yieldsToy["Bd2KSpipiDD"] = 845;
    yieldsToy["Bd2KSpipiLL"] = 360;
    yieldsToy["Bs2KSpipiDD"] =  75;
    yieldsToy["Bs2KSpipiLL"] =  38;
    
    yieldsToy["Bd2KSKpiDD"] =   60;
    yieldsToy["Bd2KSKpiLL"] =   26;
    yieldsToy["Bs2KSKpiDD"] =  141;
    yieldsToy["Bs2KSKpiLL"] =   76;
	
	yieldsToy["Bd2KSpiKDD"] =   60;
	yieldsToy["Bd2KSpiKLL"] =   26;
	yieldsToy["Bs2KSpiKDD"] =  141;
	yieldsToy["Bs2KSpiKLL"] =   76;
	
	yieldsToy["Bd2KSKKDD"] =   256;
	yieldsToy["Bd2KSKKLL"] =   175;
	yieldsToy["Bs2KSKKDD"] =     4;
	yieldsToy["Bs2KSKKLL"] =     1;
	std::string instructions("");
	for (std::vector<std::string>::iterator itYear = years.begin() ; itYear != years.end() ; ++itYear)
	  for (std::vector<std::string>::iterator it = modes.begin() ; it != modes.end() ; it++)
	    for(std::vector<std::string>::iterator itKS = KS_cat.begin() ; itKS != KS_cat.end() ; itKS++)
	      {
		std::vector<std::string> name_split;
		boost::split(name_split,(*it),boost::is_any_of("2"));
		name_split[1].erase(0,2);
		char buffer[20];
		if (!begin)
		  instructions += " , ";
		std::cout << (*it)+(*itKS) << std::endl;
		instructions += (*it)+(*itKS)+"_"+(*itYear)+"_pdf_"+(*it)+(*itKS)+"_"+(*itYear)+"_Yield=";
		sprintf(buffer,"%.2f",yieldsToy[(*it)+(*itKS)]);
		instructions += std::string(buffer);
		begin = false;	  
	    }
    std::cout << "Instructions are: " << instructions << std::endl;
    //Fixing parameters
    std::vector<std::string> toyFixParams;
    std::string fixInstructions("");
    if (constraints != "nominal")
      {
	toyFixParams.push_back("n0");
	toyFixParams.push_back("n1oN0");
	toyFixParams.push_back("alpha0");
	toyFixParams.push_back("alpha1oAlpha0");
	toyFixParams.push_back("coreFrac");
	TString parFix("");
	for(std::vector<std::string>::iterator it_year     = years.begin();   it_year  != years.end();   ++it_year)
	  for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes)
	    for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
	      for(std::vector<std::string>::iterator iPar = toyFixParams.begin(); iPar != toyFixParams.end(); ++iPar)
		parFix += (*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf_"+(*iPar); parFix += ",";
    
      }
    V0hhFit::ToyStudy toy( &fitter, nToys );
    //    toy.runToyStudy( "fitResults",instructions,fixInstructions,"");

    
    return 0;
}
