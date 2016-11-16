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
#include "RooSimultaneous.h"

// Fitter
#include "V0hhFitter/SimultaneousFitter.h"
#include "V0hhFitter/ToyStudy.h"
#include "V0hhFitter/string_tools.h"
#include <boost/program_options.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

int main( int argc, char* argv[] ) {

    bool Bs_blind(true);
    bool ToyMC(false);
    Double_t nExp(0.);    
    std::string Int_info = "";    
    std::set<std::string> integral_range;
    Double_t sigma_input(0.);

    boost::program_options::options_description decisions("Option Arguments");
    decisions.add_options()
  	("help,h" , "produce help message")
  	("blind,b", boost::program_options::value<bool>(&Bs_blind), "specify the Bs2KSKK mass window to be unblind by setting 'false'. Default is set to blind.")
  	("integral,i", boost::program_options::value<std::string>(&Int_info), "provide information about the mass window integration to produce final sample for Dalitz plot analysis. Please provide in the format 'All' or 'Bs2KSKpi-2', where 2 stands for 2sigma of the measured value. ")
	("toyMC,t", boost::program_options::value<Double_t>(&nExp), "optional (kFalse = default): specify the number os ToyMC experiments to generate/fit for the fitted model. Note: in the case of blind fit, the scenario of Bs2KSKK with yield==0 is considered");

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
			 boost::split(split_name,Int_info,boost::is_any_of("_"));
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
             integral_range.insert("Bd2KSKpi");
             integral_range.insert("Bs2KSKpi");
             integral_range.insert("Bd2KSKK");
             integral_range.insert("Bs2KSKK");
						 sigma_input =  atof(sigmaRange);
			 } else {
             std::cout << "ERROR: Please provide an apropriate name e.g.: Bs2KSKpi_2" << std::endl;
			 }
	  }

    //================================================================================
    // Create instance of the fitter and observables
    //================================================================================
    V0hhFit::SimultaneousFitter fitter( "B2KShhMCFit", "B0(d,s) --> KS h' h Fit" );
    fitter.createWS( "newDesktop", "newDesktop" );

    fitter.setGlobalKillBelowError( RooFit::FATAL ); // Monitoring
    fitter.setnCPU( 2 ); // Sets the number of CPUs to run the minimisation in parallel

    TString massvar("B_M"); // Observable name to be used in the fit
    Float_t xmin( 5000.0 ), xmax( 5800.0 ); // Set the range of fit axis

    // Path to local area to save informations of the fit 
    TString currentDir = getenv("V0HHFITTERROOT");
    std::string auxiliar = (currentDir).Data();
    std::string saveDir = auxiliar+"/../KShh/"; 

    fitter.set1DFitVarName( massvar );
    fitter.make1DFitVar( xmin, xmax, "MeV/c^{2}", "m(#it{K^{0}_{#rm S} h^{+} h^{-}})" ); 
    fitter.setPlotBins( massvar, 50 );
    fitter.setBins("B_M", 100, "cache"); // Cache for the ArgusConvGauss
    //================================================================================

    //================================================================================
    // Definition of the modes 
    //================================================================================

    // Define possible combinations of signal, crossfeed and partially bkg modes 
    std::vector<std::string> type;
    std::vector<std::string> modes;
    std::vector<std::string> KS_cat;
    std::multimap<std::string,std::string> cross_feed;
    std::multimap<std::string,std::string> part_reco;
   
    // MC signal modes 
    type.push_back("Bd");
    type.push_back("Bs");
    modes.push_back("pipi");
    modes.push_back("Kpi");
    modes.push_back("KK");

    KS_cat.push_back("DD");
    KS_cat.push_back("LL");

    // Crossfeeds 
    cross_feed.insert(std::make_pair("pipi","Kpi"));
    cross_feed.insert(std::make_pair("Kpi","pipi"));
    cross_feed.insert(std::make_pair("Kpi","KK"));
    cross_feed.insert(std::make_pair("KK","Kpi"));

    // Partially reconstruct bkg
    part_reco.insert(std::make_pair("pipi","Bd2etapKS"));
    part_reco.insert(std::make_pair("pipi","Bd2KSpipig"));
    part_reco.insert(std::make_pair("pipi","Bu2D0pi"));
    part_reco.insert(std::make_pair("pipi","Bd2Kst0rho0"));
    part_reco.insert(std::make_pair("Kpi","Bu2D0K"));
    part_reco.insert(std::make_pair("Kpi","Bu2KstPhi"));
    part_reco.insert(std::make_pair("KK","Bu2KstPhi"));
    //================================================================================
 
    //================================================================================
    // Define all pdf's (both import MC info and create new pdf's)  
    //================================================================================
    
    TString file_WS_Sig = (saveDir+"WS/MC-Sig-WS.root").c_str(); 
    TString file_WS_Bkg = (saveDir+"WS/MC-Bkg-WS.root").c_str(); 

    // Signal modes
    for(std::vector<std::string>::iterator it_type     = type.begin();   it_type  != type.end();   ++it_type) {
       for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
          for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
             fitter.importPDFFromFile( file_WS_Sig, ((*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf").c_str(), ((*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf").c_str(), "Desktop" );
    	     fitter.setParameterConstant( ((*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf_n0").c_str() );
    	     fitter.setParameterConstant( ((*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf_n1oN0").c_str() );
    	     fitter.setParameterConstant( ((*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf_alpha0").c_str() );
    	     fitter.setParameterConstant( ((*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf_alpha1oAlpha0").c_str() );
    	     fitter.setParameterConstant( ((*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf_coreFrac").c_str() );
	  }
       }
    }
   // Crossfeed modes
   for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
       for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
	   fitter.importPDFFromFile( file_WS_Sig, ("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_pdf").c_str(), ("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_pdf").c_str(), "Desktop", true );
       }
    }
    // Partially reconstructed bkg
    for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
          fitter.importPDFFromFile( file_WS_Bkg,("Bkg_"+(it_part_reco->first)+"DD_"+(it_part_reco->second)+"_pdf").c_str(),("Bkg_"+(it_part_reco->first)+"DD_"+(it_part_reco->second)+"_pdf").c_str(), "Desktop", true);
          fitter.importPDFFromFile( file_WS_Bkg,("Bkg_"+(it_part_reco->first)+"DD_"+(it_part_reco->second)+"_pdf").c_str(),("Bkg_"+(it_part_reco->first)+"LL_"+(it_part_reco->second)+"_pdf").c_str(), "Desktop", true );
    }

    // Combinatorial background
    for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
       for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) { fitter.makeChebychev( "combinatoricLL", -0.0045, -1.0, 1.0 );
          fitter.makeExponential( ("combinatoric_"+(*it_modes)+(*it_KS)).c_str(), -0.0045, -1.0, 1.0 );
       }
    }
    //================================================================================

    //================================================================================
    // Import the data that you need 
    //================================================================================
    TString dataDir = getenv("V0HHFITTERDATA");
    std::string data_aux = (dataDir).Data(); 
    std::string filename = data_aux+"/KShh/Ntuples/Data/2011/KShh_reduced_officialv1_sumMUMD_RndmBDT_bdtOBSOneCand.root";
    TFile *file = TFile::Open( filename.c_str(), "READ" );
    TTree* tree = 0;

    for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
       for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          tree = dynamic_cast<TTree*>( file->Get( ("tupleB2KS"+(*it_modes)+(*it_KS)).c_str() ) );
	        fitter.makeMassDataSet( tree, massvar, ("KS"+(*it_modes)+(*it_KS)).c_str(), "" ) ; 
       }
    }
    file->Close();  // close the file 

    fitter.combineDataSets();
    //================================================================================

    //================================================================================
    // Create PDFs and then add by csv the pdfs that should be used for the mass 
    //================================================================================
    fitter.createPDFSets();

    for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
       for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          std::string pdf_names = "";
          for(std::vector<std::string>::iterator it_type     = type.begin();   it_type  != type.end();   ++it_type) { 
 	           pdf_names = (pdf_names+(*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf,").c_str();
	        }

          for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
 	           if ((*it_modes) == (it_cross->second)){  
	              pdf_names =  (pdf_names+"CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_pdf,").c_str();
	           }
          } 	

          for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
 	           if ((*it_modes) == (it_part_reco->first)){  
                pdf_names = (pdf_names+"Bkg_"+(*it_modes)+(*it_KS)+"_"+(it_part_reco->second)+"_pdf,").c_str();
	          } 
          }
          pdf_names = (pdf_names+"combinatoric_"+(*it_modes)+(*it_KS)).c_str();
          fitter.addPDFs(("KS"+(*it_modes)+(*it_KS)).c_str(),pdf_names.c_str());
       }
    }

    for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
       for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          fitter.addYields( ("KS"+(*it_modes)+(*it_KS)).c_str() ) ;
       }
    }

    fitter.buildAddPdfs();
    fitter.buildModel();
    //================================================================================

    //================================================================================
    // Set parameter constraints and and anything that is constant or has Gaussian 
    // constraints. Can also set blinding of variables here too.
    //================================================================================    

    // ------------------------------------------- //
    //            Signal parametrisation           // 
    // ------------------------------------------- //

    // Set Bs2KSKK blind in case of true 
    if (Bs_blind){ 
       fitter.blindParameter("Bs2KSKKDD_pdf_KSKKDD_Yield", 100);
       fitter.blindParameter("Bs2KSKKLL_pdf_KSKKLL_Yield", 100);
    }

    // Set the same mean for the Bd and Bs modes
    for(std::vector<std::string>::iterator it_type     = type.begin();   it_type  != type.end();   ++it_type) {
       for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
          for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
 	           fitter.addConstraint(((*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf_mu").c_str(),"@0",((*it_type)+"2KSpipiDD_pdf_mu").c_str());
	        }
       }
    } 

    // Set witdh of Bs to be the same as Bd
    for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
       for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          fitter.addConstraint(("Bs2KS"+(*it_modes)+(*it_KS)+"_pdf_sigma").c_str(),"@0",("Bd2KS"+(*it_modes)+(*it_KS)+"_pdf_sigma").c_str());
       }
    } 
   
    // Constraints the Kpi and KK widths to pipi
    for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
       if ((*it_modes) != "pipi"){
          fitter.addParameter( ("ratio_width_"+(*it_modes)+"_pipi").c_str(), 0, 5.0);
          for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
             fitter.addConstraint(("Bd2KS"+(*it_modes)+(*it_KS)+"_pdf_sigma").c_str(),"@0*@1",("Bd2KSpipi"+(*it_KS)+"_pdf_sigma,ratio_width_"+(*it_modes)+"_pipi").c_str());
          }
       }
    }
    // Constraints the LL and DD width ratio
    fitter.addParameter( "ratio_width", 0, 5.0);
    fitter.addConstraint("Bd2KSpipiLL_pdf_sigma","@0*@1","Bd2KSpipiDD_pdf_sigma,ratio_width");


    // ------------------------------------------- //
    //            Combinatorial slope              // 
    // ------------------------------------------- //

    // Set the same slope for the modes, but split into DD/LL
    for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
       for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          if ((*it_modes) != "pipi"){
             fitter.addConstraint(("combinatoric_"+(*it_modes)+(*it_KS)+"_slope").c_str(),"@0",("combinatoric_pipi"+(*it_KS)+"_slope").c_str());
          }
       }
    }
    fitter.addParameter( "ratio_combinatoric", -5.0, 5.0 );
    fitter.addConstraint("combinatoric_pipiLL_slope","@0*@1","combinatoric_pipiDD_slope,ratio_combinatoric");

    // ------------------------------------------- //
    //              Crossfeed Yields               // 
    // ------------------------------------------- //

    // Create constraints to the crossfeed yields
    for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
       for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          fitter.addParameter( ("frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS)).c_str(), 0., 1.0);
          if ((it_cross->first)== "Kpi" ){
             fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_pdf_KS"+(it_cross->second)+(*it_KS)+"_Yield").c_str(),"@0*@1",("Bs2KS"+(it_cross->first)+(*it_KS)+"_pdf_KS"+(it_cross->first)+(*it_KS)+"_Yield,frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS)).c_str());
          } else { 
             fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_pdf_KS"+(it_cross->second)+(*it_KS)+"_Yield").c_str(),"@0*@1",("Bd2KS"+(it_cross->first)+(*it_KS)+"_pdf_KS"+(it_cross->first)+(*it_KS)+"_Yield,frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS)).c_str());
          }
       }
    }
 
    // Create the gaussian constraints
    for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
       for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          if (((it_cross->second) == "Kpi") && ((it_cross->first) == "pipi")) {
             if ((*it_KS)=="DD"){
                fitter.addGaussianConstraint(("frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS)).c_str(), 0.0580,  0.0095);
	     } else {
                fitter.addGaussianConstraint(("frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS)).c_str(), 0.0562, 0.0059);
             }
          } else if (((it_cross->second) == "Kpi") && ((it_cross->first) == "KK")) {
             if ((*it_KS)=="DD"){
                fitter.addGaussianConstraint(("frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS)).c_str(), 0.0761, 0.0046);
	     } else {
                fitter.addGaussianConstraint(("frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS)).c_str(), 0.0693, 0.0046);
             }
          } else if ((it_cross->second) == "pipi"){ 
             if ((*it_KS)=="DD"){
                fitter.addGaussianConstraint(("frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS)).c_str(), 0.0505, 0.0054);
	     } else {
                fitter.addGaussianConstraint(("frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS)).c_str(), 0.0482, 0.0059);
             }
          } else {
             if ((*it_KS)=="DD"){
                fitter.addGaussianConstraint(("frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS)).c_str(), 0.0372, 0.0024);
	     } else {
                fitter.addGaussianConstraint(("frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS)).c_str(), 0.0368, 0.0029);
             }
          }
       }
    }
    // ------------------------------------------- //
    //  Partially reconstructed yields constraints // 
    // ------------------------------------------- //
   
    // Create yield fractions
    for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
       fitter.addParameter(("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)).c_str(),   0., 1.);
    }
    // Create the yield constraints    
    for(std::multimap<std::string,std::string>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
       for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS != KS_cat.end(); ++it_KS) {
          if ( (it_part_reco->first) == "Kpi" ) {
             fitter.addConstraint(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_pdf_KS"+(it_part_reco->first)+(*it_KS)+"_Yield").c_str(), "@0*@1", ("Bs2KS"+(it_part_reco->first)+(*it_KS)+"_pdf_KS"+(it_part_reco->first)+(*it_KS)+"_Yield,frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)).c_str());
	  } else {
             fitter.addConstraint(("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_pdf_KS"+(it_part_reco->first)+(*it_KS)+"_Yield").c_str(), "@0*@1", ("Bd2KS"+(it_part_reco->first)+(*it_KS)+"_pdf_KS"+(it_part_reco->first)+(*it_KS)+"_Yield,frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)).c_str());
          }
       }
    }
    // Add gaussian constraints
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
	  if ( (it_part_reco->second) == "Bu2D0K"){ 
	     fitter.addGaussianConstraint(("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)).c_str(),   0.26, 0.052);
          } else { 
	     fitter.addGaussianConstraint(("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)).c_str(),   0.04, 0.03);
          }
       } else {
	     fitter.addGaussianConstraint(("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second)).c_str(),   0.12, 0.12);
       }
    }
  
    //================================================================================    

    //================================================================================
    // Finally perform the fit to the data and the plot some results.
    //================================================================================  
    fitter.performFit();
    RooFitResult dataResults( *fitter.getFitResult( "fitResults" ) );
    dataResults.Print("v");
    //================================================================================  

    //================================================================================
    // Do some nice plotting of the invariant mass spectra, this will do residual and
    //================================================================================  
    std::string dir_plots = (saveDir+"Data-Fit/plots/").c_str();
    fitter.setPlotBins( massvar, 50 ); // Set binning
    for(std::vector<std::string>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
       for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          if ((*it_modes) == "pipi"){
             fitter.plotMass( (dir_plots+"KS"+(*it_modes)+(*it_KS)).c_str(), "m(#it{K}_{S}^{0}#it{#pi^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]", ("KS"+(*it_modes)+(*it_KS)).c_str(),"fitResults" ) ;
	  } else if ((*it_modes) == "Kpi"){
             fitter.plotMass( (dir_plots+"KS"+(*it_modes)+(*it_KS)).c_str(), "m(#it{K}_{S}^{0}#it{K^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]", ("KS"+(*it_modes)+(*it_KS)).c_str(),"fitResults" ) ;
          } else {
             fitter.plotMass( (dir_plots+"KS"+(*it_modes)+(*it_KS)).c_str(), "m(#it{K}_{S}^{0}#it{K^{+}K^{#font[122]{-}}}) [MeV/#it{c}^{2}]", ("KS"+(*it_modes)+(*it_KS)).c_str(),"fitResults" ) ;
          }
       }
    }

    //================================================================================
    // Save everything in the workspace!
    //================================================================================  
    fitter.saveWS( (saveDir+"WS/Data-WS.root").c_str() );
    //================================================================================

    //================================================================================
    // Perform the integration for a given sigma of the mean
    //================================================================================  
    if (vm.count("integral")){
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
             if ((it_sig->first).find("Bd") != std::string::npos) { mean = mean_Bd; } 
	     else { mean = mean_Bs; }

             if (((it_sig->first).find("pipi") != std::string::npos) && ((it_sig->first).find("DD") != std::string::npos) && ((it_bkg->first).find("pipi") != std::string::npos) && ((it_bkg->first).find("DD") != std::string::npos)) {
	        sigma =  sigma_input*sigmaDD;
	     } else if (((it_sig->first).find("pipi") != std::string::npos) && ((it_sig->first).find("LL") != std::string::npos) && ((it_bkg->first).find("pipi") != std::string::npos) && ((it_bkg->first).find("LL") != std::string::npos)) {
                sigma =  sigma_input*sigmaLL_r*sigmaDD;
	     } else if (((it_sig->first).find("Kpi") != std::string::npos) && ((it_sig->first).find("DD") != std::string::npos) && ((it_bkg->first).find("Kpi") != std::string::npos) && ((it_bkg->first).find("DD") != std::string::npos)) {
		sigma =  sigma_input*sigma_Kpi_r*sigmaDD;
	     } else if (((it_sig->first).find("Kpi") != std::string::npos) && ((it_sig->first).find("LL") != std::string::npos) && ((it_bkg->first).find("Kpi") != std::string::npos) && ((it_bkg->first).find("LL") != std::string::npos)) {
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
             m_stringHelper.replaceAll( mode, "_pdf", "" ); 
	     fitter.saveDPInfo( norm_sig, norm_bkg, filename.c_str(), mode.c_str(), minRange, maxRange); 
	  }   
       }   
    }
    //================================================================================
    // ToyMC studies
    //================================================================================  
    if (ToyMC){
       V0hhFit::ToyStudy toy( &fitter, nExp );

       // Set Bs2KSKK initial yield to zero if is blind  
       if (Bs_blind){
          toy.runToyStudy( "fitResults" , "Bs2KSKKDD_pdf_KSKKDD_Yield=0,Bs2KSKKLL_pdf_KSKKLL_Yield=0");
       } else {
          toy.runToyStudy( "fitResults" );
       }

       // Plot Toy MC results
       toy.plotNlls("toystudy_nlls");
       toy.plotValues("toystudy_values");
       toy.plotPulls("toystudy_pulls");
    }

    return 0;
}
