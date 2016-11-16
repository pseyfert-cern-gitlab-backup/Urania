#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

// Fitter
#include "V0hhFitter/SimultaneousFitter.h"
#include "V0hhFitter/ToyStudy.h"
#include <boost/program_options.hpp>

int main( int argc, char* argv[] ) {

    Double_t nExp(0.);    
    std::string paramName = "";

    boost::program_options::options_description decisions("Option Arguments");
    decisions.add_options()
  	("help,h" , "produce help message")
   	("nExp,n" , boost::program_options::value<Double_t>(&nExp), "specify the number os ToyMC experiments to generate/fit for given systematic parameter study")
   	("par,p"  , boost::program_options::value<std::string>(&paramName), "specify the name of the parameter to be floated : e.g. 'Bd2KSpipiDD_pdf_n0'. Name scheme follows : 'Mode'_pdf_'parameter'. Full list: [2CB]-> n0, n1oN0, alpha0, alpha1oAlpha0, coreFrac; [ArgusConvGauss]-> mu, power, sigma, slope, threshold.");

    boost::program_options::variables_map vm;
    boost::program_options::store( boost::program_options::parse_command_line( argc, argv, decisions ), vm );
    boost::program_options::notify( vm );

    if( vm.count("help") ) {
       std::cout << decisions << std::endl;
       std::exit(0);
    }
    if ((vm.count("nExp")) && (vm.count("par"))){
       std::cout << "INFO: " << nExp << " ToyMC experiments will be generated " << std::endl;
       std::cout << "INFO: Systematic studies for parameter : " << paramName << std::endl;
    } else if (vm.count("nExp")){ 
       std::cout << "ERROR: Please specify as well the parameter to be floated " << std::endl;
       std::exit(0);
    } else {
       std::cout << "INFO: Setting number of experiments to default = 10 " << std::endl;
       nExp = 10;
       std::cout << "INFO: Systematic studies for parameter : " << paramName << std::endl;
    }

    //================================================================================
    // Import relevant WS's from data and MC 
    //================================================================================  
    // Path to local area 
    TString currentDir = getenv("V0HHFITTERROOT");
    std::string auxiliar = (currentDir).Data();
    TString dir = auxiliar;

    // Data fit results WS
    V0hhFit::SimultaneousFitter fitter( "B2KShhFit", "B0(d,s) --> KS h' h Fit" );
    fitter.loadWS( dir+"/KShh/WS/Data-WS.root", "newDesktop", false );

    // MC fit results WS
    V0hhFit::SimultaneousFitter fitterMC( "B2KShhMCFit", "B0(d,s) --> KS h' h Fit" );
    fitterMC.loadWS( dir+"/KShh/WS/MC-Sig-WS.root", "Desktop", false );

    //================================================================================
    // Systematic studies
    //================================================================================  
    V0hhFit::ToyStudy syst( &fitter, nExp );

    // Pass the MC fitted values and the fixed parameter to be investigated
    syst.runSystI( "fitResults" , &fitterMC, paramName);

    // Plot results
    syst.plotSystI(dir+"/KShh/Syst/plots/", paramName);

    return 0;
}
