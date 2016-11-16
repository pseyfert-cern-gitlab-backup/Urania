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
#include "V0hhFitter/SimultaneousFitter.h"
#include <boost/program_options.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include "KShh/Constraints/useConstraints.cpp"

int main( int argc, char* argv[] ) {
	
	std::vector<std::string> KS_cat;
	std::vector<std::string> pr;
	std::map<std::string,std::multimap<std::string,std::string> > categories;
	std::vector<std::string> years;
	std::string selectionType("FastMC");
	std::string constraints("Standard");
	boost::program_options::options_description decisions("Option Arguments");
	decisions.add_options()
		("help,h", "produce help message")
		("KS", boost::program_options::value< std::vector< std::string > >( &KS_cat )->multitoken(), "specify the KS category : DD, LL")
		("Bkg,b",  boost::program_options::value< std::vector< std::string > >( &pr )->multitoken(), "specify the partially reconstructed background : Bd2etapKS_pipi, Bd2KSpipig_pipi, Bu2D0pi_pipi, Bd2Kst0rho0_pipi, Bu2D0K_Kpi, Bu2KstPhi_Kpi, Bu2KstPhi_KK")
		("selection,s", boost::program_options::value< std::string > (&selectionType), "specify the selection applied.")
		("constraints,c", boost::program_options::value< std::string > (&constraints), "specify the constraints file name.")
		;
	boost::program_options::variables_map vm;
	boost::program_options::store( boost::program_options::parse_command_line( argc, argv, decisions ), vm );
	boost::program_options::notify( vm );
  
	if( vm.count("help") ) {
		std::cout << decisions << std::endl;
		std::exit(0);
	}
	std::cout << "-------------------------------------------" << std::endl; 
	bool FastMC = (selectionType == "FastMC");  
	if (vm.count("Bkg")) {
		for(std::vector<std::string>::iterator it_pr = pr.begin(); it_pr != pr.end(); ++it_pr) {
			std::cout << "WARNING: Option not ready at all." << std::endl;
			std::vector<std::string> bkg_split;
			boost::split(bkg_split,(*it_pr),boost::is_any_of("_"));
			std::cout << "INFO: Adding background of " <<  bkg_split[0] << " in the KS" << bkg_split[1] << " mass hypothesis" << std::endl;
			categories["Dummy"].insert(std::make_pair(bkg_split[1],bkg_split[0]));
		}
	} 
	else {
		std::cout << "INFO: Adding all available partially reconstructed bkg" << std::endl;
		if (!FastMC)
			{
				categories["MissGamRes-Bd"].insert(std::make_pair("pipi","Bd2etapKS02pipigamma"));
				categories["Charmless-Bd" ].insert(std::make_pair("pipi","Bd2Kst0rho02KS0pi0pipi"));
				categories["MissGamNR-Bd" ] .insert(std::make_pair("pipi","Bd2pipiKS0gamma"));
				categories["Charmed-Bd"   ].insert(std::make_pair("pipi","Bu2D0pi2KS0pipi"));
			  
				categories["Charmed-Bd"  ].insert(std::make_pair("Kpi","Bu2D0K2KS0pipi"));
				categories["Charmless-Bs"].insert(std::make_pair("Kpi","Bs2KstKst2KS0piKpi0"));
				//    categories["Charmed-Bd"  ].insert(std::make_pair("piK","Bu2D0K2KS0pipi"));
				//    categories["Charmless-Bs"].insert(std::make_pair("piK","Bs2KstKst2KS0piKpi0"));
			  
				categories["Charmonia-Bd"].insert(std::make_pair("KK","Bd2etacKS2KKpi0"));
				categories["Charmless-Bd"].insert(std::make_pair("KK","Bu2Kstphi2KS0piKK"));
				categories["Charmless-Bd"].insert(std::make_pair("KK","Bd2Kst0phi2KS0pi0KK"));
			}
		else
			{
				categories["Charmless-Bd"].insert(std::make_pair("pipi","Bd2Kst0Rho0_pipi"));
				categories["Charmless-Bs"].insert(std::make_pair("KK","Bs2KstPhi_KK"));
				categories["Charmed-Bd"  ].insert(std::make_pair("pipi","Bu2D0pi_KSpipi"));
				categories["MissGamNR-Bs"].insert(std::make_pair("pipi","Bs2KSpipigamma"));
				categories["MissGamRes-Bd"].insert(std::make_pair("pipi","Bd2etapKS_pipigamma"));
			}
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

	std::string fileName("constraints-PartReco-"+constraints);  
	KShhConstraints::testFile(fileName);  
  
	std::cout << "INFO: Selection type used is " << selectionType << "." << std::endl;
	std::vector<std::string> baseCat;
	baseCat.push_back("Charmed");
	baseCat.push_back("Charmless");
	if (!FastMC)
		baseCat.push_back("Charmonia");
	baseCat.push_back("MissGamRes");
	baseCat.push_back("MissGamNR");
	//================================================================================
  
	//================================================================================
	// Create instance of the fitter and observables
	//================================================================================
	bool trueMass = KShhConstraints::readBool(fileName,"trueMass");
	V0hhFit::SimultaneousFitter fitter( "B2KShhMCFit", "B0(d,s) --> KS h' h Fit" );
	fitter.createWS( "Desktop", "Desktop" );
  
	fitter.setGlobalKillBelowError( RooFit::ERROR ); // Monitoring
	fitter.setnCPU( 4 ); // Sets the number of CPUs to run the minimisation in parallel
  
	TString massvar("B_M"); // Observable name to be used in the fit
	if (FastMC && trueMass)
		massvar = "B_TRUEM";
	Float_t xmin( 5000.0 ), xmax( 5800.0 ); // Set the range of fit axis
	if (FastMC)
		xmin = 4850;
	// Path to local area to save informations of the fit 
	TString currentDir = getcwd(NULL,0);
	std::string auxiliar = (currentDir).Data();
	std::string saveDir = auxiliar+"/KShh/"; 
  
	fitter.set1DFitVarName( massvar );
	fitter.make1DFitVar( xmin, xmax, "MeV/c^{2}", "m(#it{K^{0}_{#rm S} h^{+} h^{-}})" );
	fitter.setPlotBins( massvar, 40 );
	
	years.push_back("2011");
	//  years.push_back("2012a");
	//  years.push_back("2012b");
  
	//================================================================================
  
	//================================================================================
	// Make all PDFs 
	//================================================================================
	// Partially reconstructed bkg (Bu2D0pi fixed for the time being)
	for (std::vector<std::string>::iterator it_years = years.begin(); it_years != years.end() ; ++it_years)
		for(std::map<std::string,std::multimap<std::string,std::string> >::iterator itCat = categories.begin(); itCat != categories.end(); ++itCat)
			for (std::multimap<std::string,std::string>::iterator itPartReco = itCat->second.begin() ; itPartReco != itCat->second.end() ; ++itPartReco)
				for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
					if (trueMass)	    
						fitter.makeArgus(("Bkg_KS"+(itPartReco->first)+(*it_KS)+"_"+(itPartReco->second)+"_"+(*it_years)+"_pdf").c_str(), 
										 20., 5., 50., 
										 5279, 5000., 5800.,
										 -30, -80, 0
										 );
					else
						fitter.makeArgusConvGauss(("Bkg_KS"+(itPartReco->first)+(*it_KS)+"_"+(itPartReco->second)+"_"+(*it_years)+"_pdf").c_str(), 
												  20., 5., 50., 
												  5279, 5000., 5800.,
												  -30, -80, 0 ,
												  10., 0, 20); 
  
	//================================================================================
  
	//================================================================================
	// Import the dataset 
	//================================================================================
	TString dataDir = getenv("V0HHFITTERDATA");
	std::string data_aux = (dataDir).Data(); 
	//  std::string basedir = data_aux+"/KShh/MonteCarlo/";
	//  std::string basedir = "/afs/cern.ch/work/r/rsilvaco/V0hhFitter/KShh/MonteCarlo/";
	//  std::cout << "WARNING: Using locally made files, with a high-mass cut. See with lohenry@cern.ch for questions." << std::endl;
	std::string basedir = "/afs/cern.ch/work/l/lohenry/Data/2014-Analysis/MonteCarlo/";
	//std::string BDTstrategy = "Loose";
	std::string BDTstrategy = "NoBDTCut";
  
	TFile *file = 0;
	TTree* tree = 0;
	bool noBDTapplied(false);
	if (selectionType == "NoBDTCut")
		noBDTapplied = true;
	const char *weightVar = "";
	if (FastMC)
		weightVar = "weight_BPZ";
	if (noBDTapplied && !FastMC)
		std::cout << "WARNING: A mild cut has been applied one these samples to remove outlier events." << std::endl;
	for (std::vector<std::string>::iterator it_years = years.begin(); it_years != years.end() ; ++it_years)
		for(std::map<std::string,std::multimap<std::string,std::string> >::iterator itCat = categories.begin(); itCat != categories.end(); ++itCat){
			for (std::multimap<std::string,std::string>::iterator itPartReco = itCat->second.begin() ; itPartReco != itCat->second.end() ; ++itPartReco){
				for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {	  
					std::cout << "INFO: Acquiring Bkg_KS"+(itPartReco->first)+(*it_KS)+"_"+(itPartReco->second)+"_"+(*it_years) << std::endl;
					if (noBDTapplied && !FastMC)
						file = TFile::Open( (basedir+(*it_years)+"/KShhFit/"+BDTstrategy+"/"+(itPartReco->second)+"/"+(itPartReco->second)+"-MC-"+(*it_years)+"-MagAll-Stripping-MCTruth-Trigger-Presel-Vetoes-PID-SingleCand-CutHenry.root").c_str());
					else if (FastMC)
						//						file = TFile::Open(("/afs/cern.ch/work/l/lohenry/Data/FastMC/"+(itPartReco->second)+".root").c_str());
						file = TFile::Open(("root://eoslhcb.cern.ch//eos/lhcb/user/l/lohenry/KShhFit/FastMC/"+(itPartReco->second)+".root").c_str());
					else
						file = TFile::Open( (basedir+(*it_years)+"/KShhFit/"+selectionType+"/KS"+(itPartReco->first)+"/"+(itPartReco->second)+"-MC-"+(*it_years)+"-MagAll.root").c_str());
					tree = dynamic_cast<TTree*>(file->Get(("B2KShh"+(*it_KS)+"/B2"+(itPartReco->first)+"KS").c_str()));
					fitter.makeMassDataSet( tree, massvar,
											("Bkg_KS"+(itPartReco->first)+(*it_KS)+"_"+(itPartReco->second)+"_"+(*it_years)).c_str(), weightVar ) ; 
					file->Close();  // close the file
				}
			} 
		}  
	fitter.combineDataSets();

	//================================================================================  
	//================================================================================
	// Create PDFs and then add by csv the pdfs that should be used for the mass 
	//================================================================================
	fitter.createPDFSets();
	
	for (std::vector<std::string>::iterator it_years = years.begin(); it_years != years.end() ; ++it_years)
		for(std::map<std::string,std::multimap<std::string,std::string> >::iterator itCat = categories.begin(); itCat != categories.end(); ++itCat){
			for (std::multimap<std::string,std::string>::iterator itPartReco = itCat->second.begin() ; itPartReco != itCat->second.end() ; ++itPartReco){
				for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
					fitter.addPDFs  (("Bkg_KS"+(itPartReco->first)+(*it_KS)+"_"+(itPartReco->second)+"_"+(*it_years)).c_str(),
									 ("Bkg_KS"+(itPartReco->first)+(*it_KS)+"_"+(itPartReco->second)+"_"+(*it_years)+"_pdf").c_str());
					fitter.addYields(("Bkg_KS"+(itPartReco->first)+(*it_KS)+"_"+(itPartReco->second)+"_"+(*it_years)).c_str()) ;
				}
			}
		}
	fitter.buildAddPdfs();
	fitter.buildModel();

	//================================================================================
  
	//================================================================================
	// Set parameter constraints and and anything that is constant or has Gaussian 
	// constraints. Can also set blinding of variables here too.
	//================================================================================
	//The true mass option (nearly deprecated) offers the possibility to fit only the Argus part
	// on the mass at generator level.
	if (!trueMass)
		{
			fitter.addParameter("Sigma(DD)",8.,50.);
			//  fitter.addParameter("Sigma(LL)",8.,100.);
			for(std::map<std::string,std::multimap<std::string,std::string> >::iterator itCat = categories.begin(); itCat != categories.end(); ++itCat)
				for (std::multimap<std::string,std::string>::iterator it = itCat->second.begin() ; it != itCat->second.end() ; it++)
					for (std::vector<std::string>::iterator itYears = years.begin() ; itYears != years.end() ; ++itYears)	
						{
							fitter.addConstraint(("Bkg_KS"+(it->first)+"DD_"+(it->second)+"_"+(*itYears)+"_pdf_sigma").c_str() ,"@0","Sigma(DD)");
							fitter.addConstraint(("Bkg_KS"+(it->first)+"LL_"+(it->second)+"_"+(*itYears)+"_pdf_sigma").c_str() ,"@0","Sigma(DD)");
						}
		}
	//Physical masses.
	double base(5279),miss(0);
  
	for(std::map<std::string,std::multimap<std::string,std::string> >::iterator itCat = categories.begin(); itCat != categories.end(); ++itCat)
		{
			fitter.addParameter(("threshold_"+itCat->first).c_str(),5000,5800);
			base = 5279.;
			miss = 0;
			if (itCat->first.find("Gam") == std::string::npos)
				miss = 135;
			if (itCat->first.find("Bd") == std::string::npos)
				base = 5367.;
			fitter.setParameterValue(("threshold_"+itCat->first).c_str(),base-miss,true);
			//		fitter.setParameterError(("threshold_"+itCat->first).c_str(),1.);
		}
  
	for(std::map<std::string,std::multimap<std::string,std::string> >::iterator itCat = categories.begin(); itCat != categories.end(); ++itCat)
		{
			std::string catName(itCat->first);
			std::cout << "Binding the category: " << catName << "." << std::endl;
			std::string tempCat = catName;
		  
			if (catName.find("Bs") != std::string::npos)
				tempCat.replace(catName.find("Bs")-1,catName.find("Bs")+2,"");
			if (catName.find("Bd") != std::string::npos)
				tempCat.replace(catName.find("Bd")-1,catName.find("Bd")+2,"");
			if ((fitter.getWS()->var(("power_"+tempCat).c_str())) == NULL)
				fitter.addParameter      (("power_"+tempCat).c_str(),0.,10.);
			fitter.setParameterValue (("power_"+tempCat).c_str(),0.5);
			if (catName == "MissGamNR-Bd")
				fitter.setParameterValue(("power_"+tempCat).c_str(),0.01);
			else if (catName == "MissGamRes-Bd")
				fitter.setParameterValue(("power_"+tempCat).c_str(),0.01);
		  
			//Setting the slope
			if ((fitter.getWS()->var(("slope_"+tempCat).c_str())) == NULL)
				fitter.addParameter      (("slope_"+tempCat).c_str(),-50,0.);
			if (catName == "MissGamNR-Bd")
				fitter.setParameterValue(("slope_"+tempCat).c_str(),-0.01);
			else if (catName == "MissGamRes-Bd")
				fitter.setParameterValue(("slope_"+tempCat).c_str(),-0.01);
			//Setting the constraints
			for (std::multimap<std::string,std::string>::iterator it = itCat->second.begin() ; it != itCat->second.end() ; it++)
				for (std::vector<std::string>::iterator it_years = years.begin() ; it_years != years.end() ; it_years++)
					{
						fitter.addConstraint(("Bkg_KS"+(it->first)+"DD_"+(it->second)+"_"+(*it_years)+"_pdf_threshold").c_str() ,"@0",("threshold_"+catName).c_str());
						fitter.addConstraint(("Bkg_KS"+(it->first)+"LL_"+(it->second)+"_"+(*it_years)+"_pdf_threshold").c_str() ,"@0",("threshold_"+catName).c_str());
						fitter.addConstraint(("Bkg_KS"+(it->first)+"DD_"+(it->second)+"_"+(*it_years)+"_pdf_power").c_str() ,"@0",("power_"+tempCat).c_str());
						fitter.addConstraint(("Bkg_KS"+(it->first)+"LL_"+(it->second)+"_"+(*it_years)+"_pdf_power").c_str() ,"@0",("power_"+tempCat).c_str());
						fitter.addConstraint(("Bkg_KS"+(it->first)+"DD_"+(it->second)+"_"+(*it_years)+"_pdf_slope").c_str() ,"@0",("slope_"+tempCat).c_str());
						fitter.addConstraint(("Bkg_KS"+(it->first)+"LL_"+(it->second)+"_"+(*it_years)+"_pdf_slope").c_str() ,"@0",("slope_"+tempCat).c_str());
					}
		}
	//  fitter.setParameterConstant("Sigma(DD)");
	//================================================================================
	// Finally perform the fit to the data and the plot some results.
	//================================================================================  
	fitter.performFit("fitResults",true);
	//  fitter.performFit("fitResults");
	RooFitResult res(*fitter.getFitResult( "fitResults" ));
	res.Print("v");
	//Create the new PDFs.
  
	for (std::vector<std::string>::iterator it = baseCat.begin() ; it != baseCat.end() ; ++it)
		{
			if (trueMass)
				{
					fitter.makeArgus((*it+"-Bd_pdf").c_str(), 
									 20., 5., 50., 
									 5150., 5000., 5800.,
									 -30, -80, 0);
					fitter.makeArgus((*it+"-Bs_pdf").c_str(), 
									 20., 5., 50., 
									 5150., 5000., 5800.,
									 -30, -80, 0);
				  
				}
			else
				{
					fitter.makeArgusConvGauss((*it+"-Bd_pdf").c_str(), 
											  20., 5., 50., 
											  5150., 5000., 5800.,
											  -30, -80, 0 ,
											  10., 0, 20); 
					fitter.makeArgusConvGauss((*it+"-Bs_pdf").c_str(), 
											  20., 5., 50., 
											  5150., 5000., 5800.,
											  -30, -80, 0 ,
											  10., 0, 20); 
				}
			double miss(0);
			if (it->find("Gam") != std::string::npos)
				miss = 0;
			else
				miss = 135.;
			if (!trueMass)
				{
					std::cout <<fitter.getParameterValue("Sigma(DD)") << std::endl;
					fitter.setParameterValue((*it+"-Bd_pdf_sigma").c_str(),fitter.getParameterValue("Sigma(DD)"),true);
					fitter.setParameterValue((*it+"-Bs_pdf_sigma").c_str(),fitter.getParameterValue("Sigma(DD)"),true);
				}
			fitter.setParameterValue((*it+"-Bd_pdf_threshold").c_str(),5279-miss,true);
			fitter.setParameterValue((*it+"-Bs_pdf_threshold").c_str(),5366-miss,true);      
			std::string tempCat(*it);
			fitter.setParameterValue((*it+"-Bd_pdf_power").c_str(),fitter.getParameterValue((("power_"+tempCat)).c_str()),true);
			fitter.setParameterValue((*it+"-Bs_pdf_power").c_str(),fitter.getParameterValue((("power_"+tempCat)).c_str()),true);
			fitter.setParameterValue((*it+"-Bd_pdf_slope").c_str(),fitter.getParameterValue((("slope_"+tempCat)).c_str()),true);
			fitter.setParameterValue((*it+"-Bs_pdf_slope").c_str(),fitter.getParameterValue((("slope_"+tempCat)).c_str()),true);
		}
	//================================================================================  
  
	//================================================================================
	// Plot invariant mass spectra and residuals
	//================================================================================  
	std::string dir_plots = saveDir+"MC-Bkg/plots/"+selectionType+"/";
	std::string suffix("");
	suffix += "-MCFit-";
	suffix += constraints;
	suffix += "-"+selectionType;
	// std::string dir_plots = saveDir+"MC-Bkg/plots/FastMC/";
	std::cout << "Plotting: " << std::endl;
	for (std::vector<std::string>::iterator it_years = years.begin(); it_years != years.end() ; ++it_years)
		for(std::map<std::string,std::multimap<std::string,std::string> >::iterator itCat = categories.begin(); itCat != categories.end(); ++itCat){
			for (std::multimap<std::string,std::string>::iterator itPartReco = itCat->second.begin() ; itPartReco != itCat->second.end() ; ++itPartReco){
				for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
					fitter.plotPrettyMassAndPull(dir_plots+"Bkg_KS"+(itPartReco->first)+(*it_KS)+"_"+(itPartReco->second)+"_"+(*it_years)+suffix
												 , "m(#it{K}_{S}^{0}#it{#h^{+}#h^{#font[122]{-}}}) [MeV/#it{c}^{2}]"
												 , "Bkg_KS"+(itPartReco->first)+(*it_KS)+"_"+(itPartReco->second)+"_"+(*it_years)
												 , "fitResults", "") ;
				}
			}
		}
	//================================================================================    
  
	//================================================================================
	// Save everything in the workspace!
	//================================================================================  
	fitter.saveWS( (saveDir+"WS/MC-Bkg-WS-"+constraints+"-"+selectionType+".root").c_str() );
	
	return 0;
}
