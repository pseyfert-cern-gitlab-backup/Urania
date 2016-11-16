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
    std::vector<std::string> modes;
    std::vector<std::string> KS_cat;
    std::string sig_shape("");

    namespace po = boost::program_options; 
    po::options_description decisions("Options");
     
    decisions.add_options()
    ("help,h", "produce help message")
    ("yearPeriod,y", boost::program_options::value< std::vector< std::string > >( &year )->multitoken(), "specify the list of MC year conditions to be considered. Options are: 2011, 2012a, 2012b")
    ("sigModes,s", boost::program_options::value< std::vector< std::string > >( &modes )->multitoken(), "specify the signal modes to be fitted. Options are: Bd2KSpipi, Bs2KSpipi, Bd2KSpp, Bs2KSpp")
    ("KS", boost::program_options::value< std::vector< std::string > >( &KS_cat )->multitoken(), "specify the KS category : DD, LL")
    ("sigShape", boost::program_options::value<std::string>(&sig_shape), "specify the alternative signal mode shape : Cruijff, Apollonios, Amoroso, Hypatia or Hypatia2");

    boost::program_options::variables_map vm;
    boost::program_options::store( boost::program_options::parse_command_line( argc, argv, decisions ), vm );
    boost::program_options::notify( vm );

    if( vm.count("help") ) {
       std::cout << decisions << std::endl;
       std::exit(0);
    }
    std::cout << "-------------------------------------------" << std::endl;
    if (vm.count("sigModes")) {
       if ((modes[0] != "Bd2KSpipi") && (modes[0] != "Bs2KSpipi") && (modes[0] != "Bd2KSpp") && (modes[0] != "Bs2KSpp")){
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
       modes.push_back("Bd2KSpp");
       modes.push_back("Bs2KSpp");
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
    if (vm.count("sigShape")) {
       std::cout << "INFO: Modifying nominal signal model to " << sig_shape << std::endl;
    } else {
       sig_shape = "DoubleCB"; 
    }
    //================================================================================

    // Invariant masses 
    std::vector<std::string> invMass;
    invMass.push_back("pipi");
    invMass.push_back("pp");

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
    std::string saveDir = auxiliar+"/KSppbar/"; 

    fitter.set1DFitVarName( massvar );
    fitter.make1DFitVar( xmin, xmax, "MeV/c^{2}", "m(#it{K^{0}_{#rm S} h^{+} h^{-}})" );
    fitter.setPlotBins( massvar, 50 );
    //================================================================================

    //================================================================================
    // Make all PDFs 
    //================================================================================
    for(std::vector<std::string>::iterator it_year     = year.begin();   it_year  != year.end();   ++it_year) {
       for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
          for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
             if (sig_shape == "Cruijff"){
                fitter.makeCruijff(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 5300, 5250, 5375, 5, 0, 20, 5, 0, 20, 1, 0, 5, 1, 0, 5);  
             } else if (sig_shape == "Apollonios"){
                fitter.makeApollonios(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 5300, 5250, 5375, 5, 0, 20, 1, -5, 10, 1, -5, 10, 1, 0, 5);
             } else if (sig_shape == "Amoroso"){
                fitter.makeAmoroso(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 5300, 5250, 5375, 5, 0, 20, 1.5, 0, 10, 2.3, 0, 5);
             } else if (sig_shape == "Hypatia"){
                fitter.makeHypatia(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(),  1, -1, 3, 1, 0, 10, 0, 5, 0, 20, 5300, 5250, 5375, 1, -5, 5, 2, 0, 10);
             } else if (sig_shape == "Hypatia2"){
                fitter.makeHypatia2(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 1, -2, 3, 1, 0, 10, 0, 5, 0, 20, 5300, 5250, 5375, 1, -5, 5, 2, 0, 10, 1, -5, 5, 2, 0, 10);
             } else {
		if ((*it_modes).find("Bd") != std::string::npos) { 
                   fitter.makeDoubleCB(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 5279, 5269, 5389, 8, 0, 20, 1, 0, 5, -1, -5, 0, 1, 0, 5, 1, 0 ,5, 0.5);
		} else {
                   fitter.makeDoubleCB(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 5366, 5356, 5376, 8, 0, 20, 1, 0, 5, -1, -5, 0, 1, 0, 5, 1, 0 ,5, 0.5);
		}
             }
          }
       }
    }
    //================================================================================

    //================================================================================
    // Import the dataset 
    //================================================================================
    TString dataDir = getenv("V0HHFITTERDATA");
    std::string data_aux = (dataDir).Data(); 
    std::string basedir  = data_aux+"/KShh/MonteCarlo/";
    std::string ppbarDir = "/afs/cern.ch/work/k/kgoetz/public/MC/Final/";
    TFile *file = 0;
    TTree* tree = 0;

    for(std::vector<std::string>::iterator it_year     = year.begin();   it_year  != year.end();   ++it_year) {
       for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
          for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
             std::vector<std::string> name_split;
             boost::split(name_split,(*it_modes),boost::is_any_of("2"));
             name_split[1].erase(0,2);
             if (name_split[1] == "pp"){
                file = TFile::Open( (ppbarDir+"/Final-"+(name_split[0])+"ppKS0-MC-"+(*it_year)+"-MagAll.root").c_str(), "READ" );
             } else{
                file = TFile::Open( (basedir+(*it_year)+"/KShhFit/Tight/KS"+(name_split[1])+"/"+(name_split[0])+"2KS"+(name_split[1])+"-MC-"+(*it_year)+"-MagAll.root").c_str(), "READ" );
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
    for(std::vector<std::string>::iterator it_year = year.begin();   it_year  != year.end();   ++it_year) {
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

/*    // Set the same mean for the Bd and Bs modes
    for(std::vector<std::string>::iterator it_year     = year.begin();   it_year  != year.end();   ++it_year) {
       for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
          for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
             if (((*it_modes).find("Bd") != std::string::npos) && ((*it_modes) != "Bd2KSpipiDD_2011_pdf")) {
                fitter.addConstraint(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf_mu").c_str(),"@0","Bd2KSpipiDD_2011_pdf_mu");
             } else if (((*it_modes).find("Bs") != std::string::npos) && ((*it_modes) != "Bs2KSpipiDD_2011_pdf")){
                fitter.addConstraint(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf_mu").c_str(),"@0","Bs2KSpipiDD_2011_pdf_mu");
             }
          }
       }
    }

    for(std::vector<std::string>::iterator it_year     = year.begin();   it_year  != year.end();   ++it_year) {
       for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
          for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
             if (((*it_year).find("2011") == std::string::npos) && ((*it_modes).find("piK") == std::string::npos)){
                fitter.addConstraint(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf_n1oN0").c_str(),"@0",((*it_modes)+(*it_KS)+"_2011_pdf_n1oN0").c_str());
                fitter.addConstraint(((*it_modes)+(*it_KS)+"_"+(*it_year)+"_pdf_alpha1oAlpha0").c_str(),"@0",((*it_modes)+(*it_KS)+"_2011_pdf_alpha1oAlpha0").c_str());
             }
          }
       }
    }
*/

    //================================================================================

    //================================================================================
    // Finally perform the fit to the data and the plot some results.
    //================================================================================  
    fitter.performFit("fitResults");
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
    if (modes[0] != "none"){
       for(std::vector<std::string>::iterator it_year = year.begin();   it_year  != year.end();   ++it_year) {
          for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
             for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
                if ((*it_modes).find("pipi") != std::string::npos) {
                   fitter.plotMassAndPull( (dir_plots+(*it_modes)+(*it_KS)+"_"+(*it_year)+prefix_name).c_str(), "m(#it{K}_{S}^{0}#it{#pi^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]", ((*it_modes)+(*it_KS)+"_"+(*it_year)).c_str(), "fitResults", "log") ;
                } else {
                   fitter.plotMassAndPull( (dir_plots+(*it_modes)+(*it_KS)+"_"+(*it_year)+prefix_name).c_str(), "m(#it{K}_{S}^{0}#it{p#bar{p}}) [MeV/#it{c}^{2}]",((*it_modes)+(*it_KS)+"_"+(*it_year)).c_str(), "fitResults", "log") ;
                }
             }
          }
       }
    } 
    //================================================================================    

    //================================================================================
    // Save everything in the workspace!
    //================================================================================  
    fitter.saveWS( (saveDir+"WS/MC-Sig-WS.root").c_str() );
    //fitter.getWS()->Print("V");

    return 0;
}
