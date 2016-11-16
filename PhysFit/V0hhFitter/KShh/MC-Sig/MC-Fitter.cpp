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
	//  std::vector<std::string> name;
	std::string sig_shape("");
	std::string selectionType("");
	std::string option("Standard");
	int nToys;
	int yields;
	std::string toyModel("");
	std::string mcOrigin("Louis");
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
		("option,o"      , boost::program_options::value<std::string>(&option), "option to save WS for systematics studies with different signal shape: name of to be added to the WS filename, e.g. SystII")
		("nToys,n"       , boost::program_options::value<int>(&nToys), "option to set the number of generated toys")
		("toyModel,t"    , boost::program_options::value<std::string>(&toyModel), "option to set the toy instructions.")
		("yields,Y"      , boost::program_options::value<int>(&yields), "option to set the yields.")
		("seed"          , boost::program_options::value<int>(&seed), "option to set the seed.")
		("mcOrigin"    , boost::program_options::value<std::string>(&mcOrigin),"")
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
		std::cout << "INFO: We will proceed with option " << option << "." << std::endl;
		ifstream f;
		f.open((std::string(getenv("V0HHFITTERROOT"))+"KShh/Constraints/constraints-SignalOnly-"+option+".txt").c_str());
		if (!f.is_open())
			{
				std::cout << "ERROR: Constraint file setting " << (std::string(getenv("V0HHFITTERROOT"))+"KShh/Constraints/constraints-SignalOnly-"+option+".txt") << " does not exist." << std::endl;
				return 0;
			}
		f.close();
    }
	else
		std::cout << "INFO: We will proceed with option " << option << "." << std::endl;

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
    fitter.setGlobalKillBelowError( RooFit::FATAL ); // Monitoring
    unsigned int nCPU(4);
    fitter.setnCPU( nCPU ); // Sets the number of CPUs to run the minimisation in parallel
    
    TString massvar("B_M"); // Observable name to be used in the fit
	// Path to local area to save informations of the fit 
	TString currentDir = getenv("V0HHFITTERROOT");
	std::string auxiliar = (currentDir).Data();
	std::string saveDir = auxiliar+"/KShh/";     
	std::string fileName("constraints-SignalOnly-"+option);
	bool changeWS = KShhConstraints::readBool(fileName,"changeWS");
	if (changeWS)
		fitter.loadWS((saveDir+"WS/MC-Sig-Samples-WS-"+mcOrigin+"-"+selectionType+"-"+option+".root").c_str(),"Desktop",false);  
	else
		fitter.loadWS((saveDir+"WS/MC-Sig-Samples-WS-"+mcOrigin+"-"+selectionType+"-Standard.root").c_str(),"Desktop",false);  
    fitter.set1DFitVarName( massvar );
    //  fitter.make1DFitVar( xmin, xmax, "MeV/c^{2}", "m(#it{K^{0}_{#rm S} h^{+} h^{-}})" ); 
    fitter.setPlotBins( massvar, 50 );
    fitter.setBins("B_M", 100, "cache"); // Cache for the ArgusConvGauss
    fitter.setModelName("model");  
    
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
	else if (sig_shape == "DoubleCB2")
		{
			vars.push_back("mu");
			vars.push_back("sigma0");
			vars.push_back("s1oS0");
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
			vars.push_back("coreFrac");
		}

    //Getting rid of piK
	//  KShhConstraints::bindPiK(fitter,years,modes,KS_cat,vars);
    
    //Setting the means    

    if (sig_shape == "DoubleCB" || sig_shape == "Cruijff" || sig_shape == "DoubleCB2")
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
								if (sig_shape == "DoubleCB2")
									fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_sigma0").c_str(),formula.c_str(),dependents.c_str());
								else
									fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_sigma").c_str(),formula.c_str(),dependents.c_str());
							}
				}
			//Gaussian now!
			double width(0);
			width = KShhConstraints::readValue(fileName,"kSig(LL)");
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
			width = KShhConstraints::readValue(fileName,"kSig(Bs)");
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
			width = KShhConstraints::readValue(fileName,"kSig(Mode)");
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
	bool sameLeftTailForYears = KShhConstraints::readBool(fileName,"sameLeftTailForYears");
	bool sameLeftTailForModes = KShhConstraints::readBool(fileName,"sameLeftTailForModes");
	bool sameRightTailForYears = KShhConstraints::readBool(fileName,"sameRightTailForYears");
	bool sameRightTailForModes = KShhConstraints::readBool(fileName,"sameRightTailForModes");
	
	if (!sameRightTailForYears || !sameRightTailForModes || sameLeftTailForModes)
		{
			std::cout << "FATAL: Constraint not implemented yet!" << std::endl;
			std::exit(1);
		}

    if (sig_shape.find("DoubleCB") != std::string::npos)
		{
			if (!sameLeftTailForYears)
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
			else
				{
					fitter.addParameter("Alpha0(pipi)",0.,10.);
					fitter.addParameter("Alpha0(Kpi)" ,0.,10.);
					fitter.addParameter("Alpha0(KK)"  ,0.,10.);
					fitter.addParameter("N0(pipi)",0.,10.);
					fitter.addParameter("N0(Kpi)" ,0.,10.);
					fitter.addParameter("N0(KK)"  ,0.,10.);
					fitter.addParameter("CoreFrac(pipi)",0.,1.);
					fitter.addParameter("CoreFrac(Kpi)" ,0.,1.);
					fitter.addParameter("CoreFrac(KK)"  ,0.,1.);
				}
			for (std::vector<std::string>::iterator itYears = years.begin() ; itYears != years.end() ; ++itYears)
				for (std::vector<std::string>::iterator itModes = modes.begin() ; itModes != modes.end() ; ++itModes)
					for (std::vector<std::string>::iterator itKS = KS_cat.begin() ; itKS != KS_cat.end() ; ++itKS)
						{
							std::string suffix = (sameLeftTailForYears)?"":"("+(*itYears)+")";
							if (itModes->find("pipi") != std::string::npos)
								{
									fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha0").c_str()  ,
														 "@0",
														 ("Alpha0(pipi)"+suffix).c_str());
									fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n0").c_str()      ,
														 "@0",
														 (    "N0(pipi)"+suffix).c_str());
									fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_coreFrac").c_str(),
														 "@0",
														 ("CoreFrac(pipi)"+suffix).c_str());
								}
							else if (itModes->find("Kpi") != std::string::npos || itModes->find("piK") != std::string::npos)
								{
									fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha0").c_str()  ,
														 "@0",
														 ("Alpha0(Kpi)"+suffix).c_str());
									fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n0").c_str()      ,
														 "@0",
														 (    "N0(Kpi)"+suffix).c_str());
									fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_coreFrac").c_str(),
														 "@0",
														 ("CoreFrac(Kpi)"+suffix).c_str());
								}
							else
								{
									fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha0").c_str()  ,
														 "@0",
														 ("Alpha0(KK)"+suffix).c_str());
									fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n0").c_str()      ,
														 "@0",
														 (    "N0(KK)"+suffix).c_str());
									fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_coreFrac").c_str(),
														 "@0",
														 ("CoreFrac(KK)"+suffix).c_str());
								}
						}
			//Alpha1 & N1
			if (sig_shape.find("DoubleCB2") != std::string::npos)
				fitter.addParameter("Sig1oSig0",2.,1.,10.);
			fitter.addParameter("Alpha1oAlpha0",-10.,0.);
			fitter.addParameter("N1oN0"    ,0.,10.);
			for (std::vector<std::string>::iterator itYears = years.begin() ; itYears != years.end() ; ++itYears)
				for (std::vector<std::string>::iterator itModes = modes.begin() ; itModes != modes.end() ; ++itModes)
					for (std::vector<std::string>::iterator itKS = KS_cat.begin() ; itKS != KS_cat.end() ; ++itKS)
						{
							fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_alpha1oAlpha0").c_str()  ,"@0","Alpha1oAlpha0");
							fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_n1oN0").c_str()      ,"@0",    "N1oN0");
							if (sig_shape.find("DoubleCB2") != std::string::npos)
								fitter.addConstraint(((*itModes)+(*itKS)+"_"+(*itYears)+"_pdf_s1oS0").c_str(),"@0","Sig1oSig0");
						}
		}
    if (sig_shape == "Cruijff")
		{
		}

    //================================================================================
    
    //================================================================================
    // Finally perform the fit to the data and the plot some results.
    //================================================================================  
	fitter.performFit("fitResults");
	RooFitResult res(*fitter.getFitResult( "fitResults" ));
	res.Print("v");
    //fitter.getWS()->Print("V");
	
	//WARNING: THIS IS IMPORTANT: For the moment the fitter does not propagate the values & errors
	// properly due to constraints. This bit of code does the trick.
    //Actualize the values...
	std::cout << "INFO: Moving through the formulae to correctly propagate the values." << std::endl;
	std::cout << "WARNING: Formulae with several parameters will not be properly handled" << std::endl;

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
							//WARNING: This DOES NOT take into account several parameters formulae.
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
    std::string suffix = "-MCFit-"+mcOrigin;
    suffix += "-"+sig_shape;
	suffix += "-"+option;
    fitter.setPlotBins( massvar, 40 ); // Set binning
    if (modes[0] != "none"){
		for(std::vector<std::string>::iterator it_year = years.begin();   it_year  != years.end();   ++it_year) {
			for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
				for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
					if ((*it_modes).find("pipi") != std::string::npos) {
						fitter.plotMassAndPull( (dir_plots+(*it_modes)+(*it_KS)+"_"+(*it_year)+suffix).c_str(),
												"m(#it{K}_{S}^{0}#it{#pi^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]",
												((*it_modes)+(*it_KS)+"_"+(*it_year)).c_str(), "fitResults", "log") ;
					} else if ((*it_modes).find("Kpi") != std::string::npos) {
						fitter.plotMassAndPull( (dir_plots+(*it_modes)+(*it_KS)+"_"+(*it_year)+suffix).c_str(),
												"m(#it{K}_{S}^{0}#it{K^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]",
												((*it_modes)+(*it_KS)+"_"+(*it_year)).c_str(), "fitResults", "log") ;
					} else if ((*it_modes).find("piK") != std::string::npos) {
						fitter.plotMassAndPull( (dir_plots+(*it_modes)+(*it_KS)+"_"+(*it_year)+suffix).c_str(),
												"m(#it{K}_{S}^{0}#it{K^{#font[122]{-}}#pi^{+}}) [MeV/#it{c}^{2}]",
												((*it_modes)+(*it_KS)+"_"+(*it_year)).c_str(), "fitResults", "log") ;
					} else {
						fitter.plotMassAndPull( (dir_plots+(*it_modes)+(*it_KS)+"_"+(*it_year)+suffix).c_str(),
												"m(#it{K}_{S}^{0}#it{K^{+}K^{#font[122]{-}}}) [MeV/#it{c}^{2}]",
												((*it_modes)+(*it_KS)+"_"+(*it_year)).c_str(), "fitResults", "log") ;
					}
				}
			}
		}
    } 
    //================================================================================    

    //================================================================================
    // Save everything in the workspace!
    //================================================================================  
    std::string saveName((saveDir+"WS/MC-Sig-Fits-WS-"+option+"-"+mcOrigin+"-"+selectionType+"-"+sig_shape).c_str());
    saveName += ".root";
	std::cout << saveName << std::endl;
    fitter.saveWS( saveName.c_str());
    return 0;
}
