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
#include "boost/program_options.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/bind.hpp"

int main( int argc, char* argv[] ) {

    std::vector<std::string> year;
    std::vector<std::string> KS_cat;
    std::vector<std::string> cf;
    std::multimap<std::string,std::string> cross_feed;
    std::string sig_shape("");
    std::string selectionType("");
    std::string option_name("");

    namespace po = boost::program_options; 
    po::options_description decisions("Options");
     
    decisions.add_options()
    ("help,h", "produce help message")
    ("yearPeriod,y", boost::program_options::value< std::vector< std::string > >( &year )->multitoken(), "specify the list of MC year conditions to be considered. Options are: 2011, 2012a, 2012b")
    ("KS", boost::program_options::value< std::vector< std::string > >( &KS_cat )->multitoken(), "specify the KS category : DD, LL")
    ("crossFeeds,c", boost::program_options::value< std::vector< std::string > >( &cf )->multitoken(), "specify the signal crossfeeds : Bd2KSpipiAsKpi, Bd2KSpipiAspiK, Bs2KSKpiAspipi, Bs2KSKpiAsKK, Bd2KSKKAsKpi, Bd2KSKKAspiK")
    ("sigShape", boost::program_options::value<std::string>(&sig_shape), "specify the alternative signal mode shape : Cruijff, Apollonios, Amoroso, Hypatia or Hypatia2")
    ("selectionBDT,b", boost::program_options::value<std::string>(&selectionType), "specify which selection has been used in the sample: Loose, Tight, DP1 or DP2")
    ("option,o", boost::program_options::value<std::string>(&option_name), "option to save WS for systematics studies with different signal shape: name of to be added to the WS filename, e.g. SystII");

    boost::program_options::variables_map vm;
    boost::program_options::store( boost::program_options::parse_command_line( argc, argv, decisions ), vm );
    boost::program_options::notify( vm );

    if( vm.count("help") ) {
       std::cout << decisions << std::endl;
       std::exit(0);
    }
    std::cout << "-------------------------------------------" << std::endl;
    if (vm.count("KS")) {
       for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS != KS_cat.end(); ++it_KS) {
          std::cout << "INFO: Adding KS category " << (*it_KS) << std::endl;
       }
    } else {
       std::cout << "INFO: All KS categories are included" << std::endl;
       KS_cat.push_back("DD");
       KS_cat.push_back("LL");
    }
    if (vm.count("crossFeeds")) {
       if ((cf[0] != "Bd2KSpipiAsKpi") && (cf[0] != "Bd2KSpipiAspiK") && (cf[0] != "Bs2KSKpiAspipi") && (cf[0] != "Bs2KSKpiAsKK") && (cf[0] != "Bd2KSKKAsKpi") && (cf[0] != "Bd2KSKKAspiK")){
          std::cerr << "ERROR: No crossfeed has been included" << std::endl; 
	       std::exit(0);
       } else {
          for(std::vector<std::string>::iterator it_cross = cf.begin(); it_cross != cf.end(); ++it_cross) {
             std::vector<std::string> cross_split;
             boost::split(cross_split,(*it_cross),boost::is_any_of("As"));
             std::cout << "INFO: Adding crossfeed of " <<  cross_split[0] << "As" << cross_split[2] << std::endl;
             cross_feed.insert(std::make_pair(cross_split[0],cross_split[2]));
          }
       }
    } else {
       std::cout << "INFO: Adding all significant crossfeeds" << std::endl;
       cross_feed.insert(std::make_pair("Bd2KSpipi","Kpi"));
       cross_feed.insert(std::make_pair("Bd2KSpipi","piK"));
       cross_feed.insert(std::make_pair("Bs2KSKpi","pipi"));
       cross_feed.insert(std::make_pair("Bs2KSKpi","KK"));
       cross_feed.insert(std::make_pair("Bd2KSKK","Kpi"));
       cross_feed.insert(std::make_pair("Bd2KSKK","piK"));
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
    }
    if (vm.count("sigShape")) {
       std::cout << "INFO: Modifying nominal signal model to " << sig_shape << std::endl;
    } else {
       sig_shape = "DoubleCB"; 
    }
    //================================================================================

    //================================================================================
    // Create instance of the fitter and observables
    //================================================================================
    V0hhFit::SimultaneousFitter fitter( "B2KShhMCFit", "B0(d,s) --> KS h' h Fit" );
    fitter.createWS( "Desktop", "Desktop" );

    fitter.setGlobalKillBelowError( RooFit::FATAL ); // Monitoring
    fitter.setnCPU( 2 ); // Sets the number of CPUs to run the minimisation in parallel

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
    // Crossfeeds 
    for(std::vector<std::string>::iterator it_year        = year.begin();   it_year  != year.end();   ++it_year) {
       for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
          for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
             fitter.makeDoubleCB(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 5322, 5200, 5450, 20, 0, 30, 1, 0, 10, -1, -10, 0, 1, 0, 10, 1, 0 ,10, 0.5);
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
    std::string basedir = "/afs/cern.ch/work/r/rsilvaco/V0hhFitter/KShh/MonteCarloNewOpt/";
    TFile *file = 0;
    TTree* tree = 0;

    for(std::vector<std::string>::iterator it_year = year.begin();   it_year  != year.end();   ++it_year) {
       for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
          for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
             file = TFile::Open( (basedir+(*it_year)+"/KShhFit/"+selectionType+"/KS"+(it_cross->second)+"/"+(it_cross->first)+"-MC-"+(*it_year)+"-MagAll-RecoMCMatch-PIDCalib-DPInfo.root").c_str(), "READ" );
			 tree = dynamic_cast<TTree*>( file->Get( ("B2KShh"+(*it_KS)+"/B2"+(it_cross->second)+"KS").c_str() ) );
			 fitter.makeMassDataSet( tree, massvar, ((it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)).c_str(), "", "", "PIDnDPweightScaled" ) ; 
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

    // Crossfeeds
    for(std::vector<std::string>::iterator it_year = year.begin();   it_year  != year.end();   ++it_year) {
       for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
          for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
             fitter.addPDFs(((it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)).c_str(),("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str());
             fitter.addYields(((it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)).c_str()) ;
          }
       }
    }

    fitter.buildAddPdfs();
    fitter.buildModel();
    //================================================================================
   
    //================================================================================
    // Set the constraints between the signal and crossfeeds for the various years  
    //================================================================================    

    // Crossfeed mean
    for(std::vector<std::string>::iterator it_year = year.begin();   it_year  != year.end();   ++it_year) {
       for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
          for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
             if (((it_cross->first) == "Bd2KSpipi") && (((it_cross->second) == "Kpi") || ((it_cross->second) == "piK"))){ 
	        if ((it_cross->second) == "piK"){
                   fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_mu").c_str(),"@0","CrossFeed_Bd2KSpipi_as_KpiDD_2011_pdf_mu");
		} else if (((*it_KS) == "DD") && ((*it_year) != "2011")){
                   fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_mu").c_str(),"@0","CrossFeed_Bd2KSpipi_as_KpiDD_2011_pdf_mu");
                } else if ((*it_KS) == "LL"){
                   fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_mu").c_str(),"@0","CrossFeed_Bd2KSpipi_as_KpiDD_2011_pdf_mu");
                }
             } else if (((it_cross->first) == "Bd2KSKK") && (((it_cross->second) == "Kpi") || ((it_cross->second) == "piK"))){
	        if ((it_cross->second) == "piK"){
                   fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_mu").c_str(),"@0","CrossFeed_Bd2KSKK_as_KpiDD_2011_pdf_mu");
		} else if (((*it_KS) == "DD") && ((*it_year) != "2011")){
                   fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_mu").c_str(),"@0","CrossFeed_Bd2KSKK_as_KpiDD_2011_pdf_mu");
                } else if ((*it_KS) == "LL"){
                   fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_mu").c_str(),"@0","CrossFeed_Bd2KSKK_as_KpiDD_2011_pdf_mu");
                }		
             } else if (((it_cross->first) == "Bs2KSKpi") && ((it_cross->second) == "pipi")){
                if (((*it_KS) == "DD") && ((*it_year) != "2011")){
                   fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_mu").c_str(),"@0","CrossFeed_Bs2KSKpi_as_pipiDD_2011_pdf_mu");
                } else if ((*it_KS) == "LL"){
                   fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_mu").c_str(),"@0","CrossFeed_Bs2KSKpi_as_pipiDD_2011_pdf_mu");
                }
             } else if (((it_cross->first) == "Bs2KSKpi") && ((it_cross->second) == "KK")){
                if (((*it_KS) == "DD") && ((*it_year) != "2011")){
                   fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_mu").c_str(),"@0","CrossFeed_Bs2KSKpi_as_KKDD_2011_pdf_mu");
                } else if ((*it_KS) == "LL"){
                   fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_mu").c_str(),"@0","CrossFeed_Bs2KSKpi_as_KKDD_2011_pdf_mu");
                }
             }
          }
       }
    }
    
    
    // Additional constraint for the mean between K+pi- and K-pi+
    //fitter.addConstraint("CrossFeed_Bd2KSpipi_as_piKDD_2011_pdf_mu","@0","CrossFeed_Bd2KSpipi_as_KpiDD_2011_pdf_mu");
    //fitter.addConstraint("CrossFeed_Bd2KSKK_as_piKDD_2011_pdf_mu","@0","CrossFeed_Bd2KSKK_as_KpiDD_2011_pdf_mu");
    
    // Crossfeed shape for the K+pi- and K-pi+
    for(std::vector<std::string>::iterator it_year = year.begin();   it_year  != year.end();   ++it_year) {
       for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          // Bd2KSpipi crossfeed
          fitter.addConstraint(("CrossFeed_Bd2KSpipi_as_piK"+(*it_KS)+"_"+(*it_year)+"_pdf_n0").c_str(),"@0",("CrossFeed_Bd2KSpipi_as_Kpi"+(*it_KS)+"_"+(*it_year)+"_pdf_n0").c_str());
          fitter.addConstraint(("CrossFeed_Bd2KSpipi_as_piK"+(*it_KS)+"_"+(*it_year)+"_pdf_n1oN0").c_str(),"@0",("CrossFeed_Bd2KSpipi_as_Kpi"+(*it_KS)+"_"+(*it_year)+"_pdf_n1oN0").c_str());
          fitter.addConstraint(("CrossFeed_Bd2KSpipi_as_piK"+(*it_KS)+"_"+(*it_year)+"_pdf_alpha0").c_str(),"@0",("CrossFeed_Bd2KSpipi_as_Kpi"+(*it_KS)+"_"+(*it_year)+"_pdf_alpha0").c_str());
          fitter.addConstraint(("CrossFeed_Bd2KSpipi_as_piK"+(*it_KS)+"_"+(*it_year)+"_pdf_alpha1oAlpha0").c_str(),"@0",("CrossFeed_Bd2KSpipi_as_Kpi"+(*it_KS)+"_"+(*it_year)+"_pdf_alpha1oAlpha0").c_str());
          fitter.addConstraint(("CrossFeed_Bd2KSpipi_as_piK"+(*it_KS)+"_"+(*it_year)+"_pdf_coreFrac").c_str(),"@0",("CrossFeed_Bd2KSpipi_as_Kpi"+(*it_KS)+"_"+(*it_year)+"_pdf_coreFrac").c_str());
          fitter.addConstraint(("CrossFeed_Bd2KSpipi_as_piK"+(*it_KS)+"_"+(*it_year)+"_pdf_sigma").c_str(),"@0",("CrossFeed_Bd2KSpipi_as_Kpi"+(*it_KS)+"_"+(*it_year)+"_pdf_sigma").c_str());
          // Bd2KSKK crossfeed
          fitter.addConstraint(("CrossFeed_Bd2KSKK_as_piK"+(*it_KS)+"_"+(*it_year)+"_pdf_n0").c_str(),"@0",("CrossFeed_Bd2KSKK_as_Kpi"+(*it_KS)+"_"+(*it_year)+"_pdf_n0").c_str());
          fitter.addConstraint(("CrossFeed_Bd2KSKK_as_piK"+(*it_KS)+"_"+(*it_year)+"_pdf_n1oN0").c_str(),"@0",("CrossFeed_Bd2KSKK_as_Kpi"+(*it_KS)+"_"+(*it_year)+"_pdf_n1oN0").c_str());
          fitter.addConstraint(("CrossFeed_Bd2KSKK_as_piK"+(*it_KS)+"_"+(*it_year)+"_pdf_alpha0").c_str(),"@0",("CrossFeed_Bd2KSKK_as_Kpi"+(*it_KS)+"_"+(*it_year)+"_pdf_alpha0").c_str());
          fitter.addConstraint(("CrossFeed_Bd2KSKK_as_piK"+(*it_KS)+"_"+(*it_year)+"_pdf_alpha1oAlpha0").c_str(),"@0",("CrossFeed_Bd2KSKK_as_Kpi"+(*it_KS)+"_"+(*it_year)+"_pdf_alpha1oAlpha0").c_str());
          fitter.addConstraint(("CrossFeed_Bd2KSKK_as_piK"+(*it_KS)+"_"+(*it_year)+"_pdf_coreFrac").c_str(),"@0",("CrossFeed_Bd2KSKK_as_Kpi"+(*it_KS)+"_"+(*it_year)+"_pdf_coreFrac").c_str());
          fitter.addConstraint(("CrossFeed_Bd2KSKK_as_piK"+(*it_KS)+"_"+(*it_year)+"_pdf_sigma").c_str(),"@0",("CrossFeed_Bd2KSKK_as_Kpi"+(*it_KS)+"_"+(*it_year)+"_pdf_sigma").c_str());
       }
    }

    fitter.addConstraint("CrossFeed_Bd2KSpipi_as_KpiDD_2012a_pdf_coreFrac","@0","CrossFeed_Bd2KSpipi_as_KpiDD_2011_pdf_coreFrac");
    fitter.addConstraint("CrossFeed_Bd2KSpipi_as_KpiDD_2012b_pdf_coreFrac","@0","CrossFeed_Bd2KSpipi_as_KpiDD_2011_pdf_coreFrac");
    fitter.addConstraint("CrossFeed_Bd2KSpipi_as_KpiLL_2012a_pdf_coreFrac","@0","CrossFeed_Bd2KSpipi_as_KpiLL_2011_pdf_coreFrac");
    fitter.addConstraint("CrossFeed_Bd2KSpipi_as_KpiLL_2012b_pdf_coreFrac","@0","CrossFeed_Bd2KSpipi_as_KpiLL_2011_pdf_coreFrac");

    fitter.addConstraint("CrossFeed_Bd2KSKK_as_KpiDD_2012a_pdf_coreFrac","@0","CrossFeed_Bd2KSKK_as_KpiDD_2011_pdf_coreFrac");
    fitter.addConstraint("CrossFeed_Bd2KSKK_as_KpiDD_2012b_pdf_coreFrac","@0","CrossFeed_Bd2KSKK_as_KpiDD_2011_pdf_coreFrac");
    fitter.addConstraint("CrossFeed_Bd2KSKK_as_KpiLL_2012a_pdf_coreFrac","@0","CrossFeed_Bd2KSKK_as_KpiLL_2011_pdf_coreFrac");
    fitter.addConstraint("CrossFeed_Bd2KSKK_as_KpiLL_2012b_pdf_coreFrac","@0","CrossFeed_Bd2KSKK_as_KpiLL_2011_pdf_coreFrac");

    fitter.addConstraint("CrossFeed_Bs2KSKpi_as_pipiDD_2012a_pdf_coreFrac","@0","CrossFeed_Bs2KSKpi_as_pipiDD_2011_pdf_coreFrac");
    fitter.addConstraint("CrossFeed_Bs2KSKpi_as_pipiDD_2012b_pdf_coreFrac","@0","CrossFeed_Bs2KSKpi_as_pipiDD_2011_pdf_coreFrac");
    fitter.addConstraint("CrossFeed_Bs2KSKpi_as_pipiLL_2012a_pdf_coreFrac","@0","CrossFeed_Bs2KSKpi_as_pipiLL_2011_pdf_coreFrac");
    fitter.addConstraint("CrossFeed_Bs2KSKpi_as_pipiLL_2012b_pdf_coreFrac","@0","CrossFeed_Bs2KSKpi_as_pipiLL_2011_pdf_coreFrac");

    fitter.addConstraint("CrossFeed_Bs2KSKpi_as_KKDD_2012a_pdf_coreFrac","@0","CrossFeed_Bs2KSKpi_as_KKDD_2011_pdf_coreFrac");
    fitter.addConstraint("CrossFeed_Bs2KSKpi_as_KKDD_2012b_pdf_coreFrac","@0","CrossFeed_Bs2KSKpi_as_KKDD_2011_pdf_coreFrac");
    fitter.addConstraint("CrossFeed_Bs2KSKpi_as_KKLL_2012a_pdf_coreFrac","@0","CrossFeed_Bs2KSKpi_as_KKLL_2011_pdf_coreFrac");
    fitter.addConstraint("CrossFeed_Bs2KSKpi_as_KKLL_2012b_pdf_coreFrac","@0","CrossFeed_Bs2KSKpi_as_KKLL_2011_pdf_coreFrac");

    //================================================================================
    // Finally perform the fit to the data and the plot some results.
    //================================================================================  
    fitter.performFit();
    RooFitResult res(*fitter.getFitResult( "fitResults" ));
    res.Print("v");
    //fitter.getWS()->Print("V");
    //================================================================================  

    //================================================================================
    // Plot invariant mass spectra and residuals
    //================================================================================  
    fitter.setPlotSubComponents(true);
    std::string dir_plots   = saveDir+"MC-Sig/plots/";
    std::string prefix_name = "_MCFit";
    if (sig_shape != "DoubleCB"){ prefix_name += "_"+sig_shape;} 
    fitter.setPlotBins( massvar, 40 ); // Set binning

    // Crossfeeds
    for(std::vector<std::string>::iterator it_year = year.begin();   it_year  != year.end();   ++it_year) {
       for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
          for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
             if ((it_cross->second) == "pipi") {
                fitter.plotMassAndPull((dir_plots+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+prefix_name).c_str(), "m(#it{K}_{S}^{0}#it{#pi^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]", ((it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)).c_str(), "fitResults", "log") ;
             } else if ((it_cross->second) == "KK") {
                fitter.plotMassAndPull((dir_plots+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+prefix_name).c_str(), "m(#it{K}_{S}^{0}#it{K^{+}K^{#font[122]{-}}}) [MeV/#it{c}^{2}]", ((it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)).c_str(), "fitResults", "log") ;
             } else if ((it_cross->second) == "Kpi") {
                fitter.plotMassAndPull((dir_plots+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+prefix_name).c_str(), "m(#it{K}_{S}^{0}#it{K^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]", ((it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)).c_str(), "fitResults", "log") ;
             } else {
                fitter.plotMassAndPull((dir_plots+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+prefix_name).c_str(), "m(#it{K}_{S}^{0}#it{K^{#font[122]{-}}#pi^{+}}) [MeV/#it{c}^{2}]", ((it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)).c_str(), "fitResults", "log") ;
             }
          }
       }
    }
    //================================================================================    

    //================================================================================
    // Save everything in the workspace!
    //================================================================================  
    if (vm.count("option")) {
       fitter.saveWS( (saveDir+"WS/MC-CrossFeed-WS-"+option_name+"-"+selectionType+".root").c_str() );
    } else {
       fitter.saveWS( (saveDir+"WS/MC-CrossFeed-WS-"+selectionType+".root").c_str() );
    }

    return 0;
}
