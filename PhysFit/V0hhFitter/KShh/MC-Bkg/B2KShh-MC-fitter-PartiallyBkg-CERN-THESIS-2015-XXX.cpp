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

// Fitter
#include "V0hhFitter/SimultaneousFitter.h"
#include <boost/program_options.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>


int main( int argc, char* argv[] ) {

    std::vector<std::string> year;
    std::vector<std::string> KS_cat;
    std::vector<std::string> pr;
    std::multimap<std::string,std::string> part_reco;
    std::string selectionType("");

    boost::program_options::options_description decisions("Option Arguments");
    decisions.add_options()
    ("help,h", "produce help message")
    ("yearPeriod,y", boost::program_options::value< std::vector< std::string > >( &year )->multitoken(), "specify the list of MC year conditions to be considered. Options are: 2011, 2012a, 2012b")
    ("Bkg,m",  boost::program_options::value< std::vector< std::string > >( &pr )->multitoken(), "specify the partially reconstructed background : Bd2pipiKS0gamma_pipi, Bd2etapKS02pipigamma_pipi, Bd2Kst0rho02KS0pi0pipi_pipi, Bu2D0pi2KS0pipi_pipi, Bs2KstKst2KS0piKpi0_Kpi, Bu2D0K2KS0pipi_pipi, Bd2Kst0phi2KS0pi0KK_KK, Bu2Kstphi2KS0piKK_KK, Bd2etacKS2KKpi0_KK")
    ("KS", boost::program_options::value< std::vector< std::string > >( &KS_cat )->multitoken(), "specify the KS category : DD, LL")
    ("selectionBDT,b", boost::program_options::value<std::string>(&selectionType), "specify which selection has been used in the sample: Loose, Tight, DP1 or DP2");

    boost::program_options::variables_map vm;
    boost::program_options::store( boost::program_options::parse_command_line( argc, argv, decisions ), vm );
    boost::program_options::notify( vm );

    if( vm.count("help") ) {
       std::cout << decisions << std::endl;
       std::exit(0);
    }
    std::cout << "-------------------------------------------" << std::endl;

    if (vm.count("Bkg")) {
       for(std::vector<std::string>::iterator it_pr = pr.begin(); it_pr != pr.end(); ++it_pr) {
          std::vector<std::string> bkg_split;
          boost::split(bkg_split,(*it_pr),boost::is_any_of("_"));
          std::cout << "INFO: Adding background of " <<  bkg_split[0] << " in the KS" << bkg_split[1] << " mass hypothesis" << std::endl;
          part_reco.insert(std::make_pair(bkg_split[1],bkg_split[0]));
          if (bkg_split[1] == "Kpi"){
             part_reco.insert(std::make_pair("piK",bkg_split[0]));
          }
       }
    } else {
       std::cerr << "ERROR: No partially reconstructed background has been included" << std::endl; 
       std::exit(0);
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
       year.push_back("2011");
       year.push_back("2012a");
       year.push_back("2012b");
    } else {
       for(std::vector<std::string>::iterator it_year = year.begin(); it_year != year.end(); ++it_year) {
          std::cout << "INFO: Adding samples for " << (*it_year) << " conditions" << std::endl;
       }
    }
    if (vm.count("selectionBDT")) {
       std::cout << "INFO: Setting the sample with the " << selectionType << " selection" << std::endl;
    } else {
       selectionType = "Tight"; 
       std::cout << "INFO: Setting default selection Tight" << std::endl;
    }
    //================================================================================

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
    fitter.setPlotBins( massvar, 40 );
    //================================================================================

    //================================================================================
    // Make all PDFs 
    //================================================================================

    // Partially reconstructed bkg (Bu2D0pi fixed for the time being)
    for(std::vector<std::string>::iterator it_year     = year.begin();   it_year  != year.end();   ++it_year) {
       for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
          for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
             fitter.makeArgusConvGauss(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_year)+"_pdf").c_str(), 15, 0, 30, 5300, 5000, 5400, -30, -50, 10 , 1.0, -10, 20); 
          }
       }
    }
    //================================================================================

    //================================================================================
    // Import the dataset 
    //================================================================================
    TString dataDir = getenv("V0HHFITTERDATA");
    std::string data_aux = (dataDir).Data(); 
    //std::string basedir = data_aux+"/KShh/MonteCarlo/";
    std::string basedir = data_aux+"/KShh/MonteCarlo/";
    //std::string basedir = "/afs/cern.ch/work/r/rsilvaco/V0hhFitter/KShh/MonteCarlo/";
    TFile *file = 0;
    TTree* tree = 0;

    for(std::vector<std::string>::iterator it_year     = year.begin();   it_year  != year.end();   ++it_year) {
       for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
          for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
	          // Statement to account no 2012 Partially reco sample 
             // TODO : correct this later to the specific year
             //file = TFile::Open((basedir+"2011/KShhFit/"+selectionType+"/KS"+(it_part_reco->first)+"/"+(it_part_reco->second)+"-MC-2011-MagAll.root").c_str(), "READ" );
	     //file = TFile::Open((basedir+"2011/SingleCand/"+selectionType+"/"+(it_part_reco->second)+"/"+(it_part_reco->second)+"-MC-2011-MagAll-Stripping-MCTruth-Trigger-Presel-Vetoes-PID-SingleCand.root").c_str(), "READ");
	     file = TFile::Open((basedir+"2011/BDT/"+selectionType+"/"+(it_part_reco->second)+"/"+(it_part_reco->second)+"-MC-2011-MagAll-Stripping-MCTruth-Trigger-Vetoes-BDT.root").c_str(), "READ");
             tree = dynamic_cast<TTree*>( file->Get( ("B2KShh"+(*it_KS)+"/B2"+(it_part_reco->first)+"KS").c_str()));
             //fitter.makeMassDataSet( tree, massvar, ("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_year)).c_str(), "", "BDT>0.00" ) ; //KSKpi KstKst 
             //fitter.makeMassDataSet( tree, massvar, ("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_year)).c_str(), "", "BDT>0.00&&B_M<5250" ) ; 
             fitter.makeMassDataSet( tree, massvar, ("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_year)).c_str(), "", "B_M<5300" ) ; 
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

    for(std::vector<std::string>::iterator it_year = year.begin();   it_year  != year.end();   ++it_year) {
       for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
          for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
             fitter.addPDFs(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_year)).c_str(), ("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_year)+"_pdf").c_str());
             fitter.addYields(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_year)).c_str()) ;
          }
       }
    }

    fitter.buildAddPdfs();
    fitter.buildModel();
    //================================================================================
  
    //================================================================================
    // Set the necessary constraints 
    //================================================================================    
    // Comment: the piK and Kpi shapes are constraint to be the same
    if ((!vm.count("KS")) && (!vm.count("yearPeriod"))) {
       // Set the threshold to be the same between DD/LL and 2011/12a/12b
       for(std::vector<std::string>::iterator it_year = year.begin();   it_year  != year.end();   ++it_year) {
          for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
             for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
                if ((it_part_reco->first) == "piK"){
                   fitter.addConstraint(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_year)+"_pdf_threshold").c_str(),"@0",("Bkg_KpiDD_"+(it_part_reco->second)+"_2011_pdf_threshold").c_str());
                } else if (((*it_KS) == "DD") && ((*it_year) == "2011")){
                   continue;
                } else {
                   fitter.addConstraint(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_year)+"_pdf_threshold").c_str(),"@0",("Bkg_"+(it_part_reco->first)+"DD_"+(it_part_reco->second)+"_2011_pdf_threshold").c_str());
                }
             }
          }
       }

       // Set the slope and power to be the same between DD and LL of a given year
       for(std::vector<std::string>::iterator it_year = year.begin();   it_year  != year.end();   ++it_year) {
          for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
             for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
                if ((it_part_reco->first) == "piK") {
                   fitter.addConstraint(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_year)+"_pdf_slope").c_str(),"@0",("Bkg_KpiDD_"+(it_part_reco->second)+"_"+(*it_year)+"_pdf_slope").c_str());
                   fitter.addConstraint(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_year)+"_pdf_power").c_str(),"@0",("Bkg_KpiDD_"+(it_part_reco->second)+"_"+(*it_year)+"_pdf_power").c_str());
                } else if ((*it_KS) != "DD"){
                   fitter.addConstraint(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_year)+"_pdf_slope").c_str(),"@0",("Bkg_"+(it_part_reco->first)+"DD_"+(it_part_reco->second)+"_"+(*it_year)+"_pdf_slope").c_str());
                   fitter.addConstraint(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_year)+"_pdf_power").c_str(),"@0",("Bkg_"+(it_part_reco->first)+"DD_"+(it_part_reco->second)+"_"+(*it_year)+"_pdf_power").c_str());
                }
             }
          }
       }
    }
    //================================================================================
    // Finally perform the fit to the data and the plot some results.
    //================================================================================  
    fitter.performFit();
    RooFitResult res(*fitter.getFitResult( "fitResults" ));
    res.Print("v");
    //================================================================================  

    //================================================================================
    // Plot invariant mass spectra and residuals
    //================================================================================  
    std::string dir_plots = saveDir+"MC-Bkg/plots/";
    for(std::vector<std::string>::iterator it_year = year.begin();   it_year  != year.end();   ++it_year) {
       for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
          for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
	     std::string bkg_name = it_part_reco->second;
             if ((it_part_reco->first) == "pipi"){
                fitter.plotMassAndPull( (dir_plots+"Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_year)+"_MCFit").c_str(), "m(#it{K}_{S}^{0}#it{#pi^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]", ("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_"+(*it_year)).c_str(), "fitResults", "log") ;
	     } else if ((it_part_reco->first) == "Kpi"){
                fitter.plotMassAndPull( (dir_plots+"Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+bkg_name+"_"+(*it_year)+"_MCFit").c_str(), "m(#it{K}_{S}^{0}#it{K^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]", ("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+bkg_name+"_"+(*it_year)).c_str(), "fitResults", "log") ;
	     } else if ((it_part_reco->first) == "piK"){
                fitter.plotMassAndPull( (dir_plots+"Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+bkg_name+"_"+(*it_year)+"_MCFit").c_str(), "m(#it{K}_{S}^{0}#it{K^{#font[122]{-}}#pi^{+}}) [MeV/#it{c}^{2}]", ("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+bkg_name+"_"+(*it_year)).c_str(), "fitResults", "log") ;
	     } else if ((it_part_reco->first) == "KK"){
                fitter.plotMassAndPull( (dir_plots+"Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+bkg_name+"_"+(*it_year)+"_MCFit").c_str(), "m(#it{K}_{S}^{0}#it{K^{+}K^{#font[122]{-}}}) [MeV/#it{c}^{2}]", ("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+bkg_name+"_"+(*it_year)).c_str(), "fitResults", "log") ;
	     }
          }
       }
    }

    //================================================================================    

    //================================================================================
    // Save everything in the workspace!
    //================================================================================  
    fitter.exportAllPDFsToFile((saveDir+"WS/MC-Bkg-WS-"+selectionType+".root").c_str(), "WS");

    return 0;
}
