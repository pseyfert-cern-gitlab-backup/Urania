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

// Fitter
#include "V0hhFitter/SimultaneousFitter.h"
#include "V0hhFitter/ToyStudy.h"
#include <boost/program_options.hpp>

int main( int argc, char* argv[] ) {

    Double_t nExp(0.);    

    boost::program_options::options_description decisions("Option Arguments");
    decisions.add_options()
  	("help,h" , "produce help message")
	("nExpt,n", boost::program_options::value<Double_t>(&nExp), "specify the number os ToyMC experiments to generate/fit for the fitted model. Note: in the case of blind fit, the scenario of Bs2KSKK with yield==0 is considered");

    boost::program_options::variables_map vm;
    boost::program_options::store( boost::program_options::parse_command_line( argc, argv, decisions ), vm );
    boost::program_options::notify( vm );

    if( vm.count("help") ) {
       std::cout << decisions << std::endl;
       std::exit(0);
    }
    if (vm.count("nExpt")){ 
       std::cout << "INFO: " << nExp << " ToyMC experiments will be generated after the fit to data" << std::endl;
    }
    //================================================================================
    // Create instance of the fitter and observables
    //================================================================================
    V0hhFit::SimultaneousFitter fitter( "B2KShhMCFit", "B0(d,s) --> KS h' h Fit" );
    fitter.createWS( "newDesktop_Syst", "newDesktop_Syst" );

    fitter.setGlobalKillBelowError( RooFit::FATAL ); // Monitoring
    fitter.setnCPU( 2 ); // Sets the number of CPUs to run the minimisation in parallel

    TString massvar("B_M"); // Observable name to be used in the fit
    Float_t xmin( 5000.0 ), xmax( 5800.0 ); // Set the range of fit axis

    // Path to local area to save informations of the fit 
    TString currentDir = getenv("V0HHFITTERROOT");
    TString saveDir = currentDir+"/KShh/"; 

    fitter.set1DFitVarName( massvar );
    fitter.make1DFitVar( xmin, xmax, "MeV/c^{2}", "m(#it{K^{0}_{#rm S} h^{+} h^{-}})" ); 
    fitter.setPlotBins( massvar, 50 );
    fitter.setBins("B_M", 100, "cache"); // Cache for the ArgusConvGauss
    //================================================================================

    //================================================================================
    // Definition of the modes 
    //================================================================================

    // Define possible combinations of signal, crossfeed and partially bkg modes 
    std::vector<TString> type;
    std::vector<TString> modes;
    std::vector<TString> KS_cat;
    std::multimap<TString,TString> cross_feed;
    std::multimap<TString,TString> part_reco;
   
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
    
    TString file_WS_Sig = saveDir+"WS/MC-Sig-WS-SystII.root"; 
    TString file_WS_Bkg = saveDir+"WS/MC-Bkg-WS.root"; 

    // Signal modes
    for(std::vector<TString>::iterator it_type     = type.begin();   it_type  != type.end();   ++it_type) {
       for(std::vector<TString>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
          for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
             fitter.importPDFFromFile( file_WS_Sig, (*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf", (*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf", "Desktop" );
	     fitter.setParameterConstant( (*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf_a" );
	     fitter.setParameterConstant( (*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf_b" );
	     fitter.setParameterConstant( (*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf_n" );
	  }
       }
    }
   // Crossfeed modes
   for(std::multimap<TString,TString>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
       for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
	   fitter.importPDFFromFile( file_WS_Sig, "CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_pdf", "CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_pdf", "Desktop", true );
       }
    }
    // Partially reconstructed bkg
    for(std::multimap<TString,TString>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
       fitter.importPDFFromFile( file_WS_Bkg,"Bkg_"+(it_part_reco->first)+"DD_"+(it_part_reco->second)+"_pdf","Bkg_"+(it_part_reco->first)+"DD_"+(it_part_reco->second)+"_pdf", "Desktop", true);
       fitter.importPDFFromFile( file_WS_Bkg,"Bkg_"+(it_part_reco->first)+"DD_"+(it_part_reco->second)+"_pdf","Bkg_"+(it_part_reco->first)+"LL_"+(it_part_reco->second)+"_pdf", "Desktop", true );
    }

    // Combinatorial background
    for(std::vector<TString>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
       for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) { fitter.makeChebychev( "combinatoricLL", -0.0045, -1.0, 1.0 );
          fitter.makeExponential( "combinatoric_"+(*it_modes)+(*it_KS), -0.0045, -1.0, 1.0 );
       }
    }
    //================================================================================

    //================================================================================
    // Import the data that you need 
    //================================================================================
    TString dataDir = getenv("V0HHFITTERDATA");
    TString basedir = dataDir+"/KShh/Ntuples/Data/2011/KShh_reduced_officialv1_sumMUMD_RndmBDT_bdtOBSOneCand.root";
    TFile *file = TFile::Open( basedir, "READ" );
    TTree* tree = 0;

    for(std::vector<TString>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
       for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          tree = dynamic_cast<TTree*>( file->Get( "tupleB2KS"+(*it_modes)+(*it_KS) ) );
	  fitter.makeMassDataSet( tree, massvar, "KS"+(*it_modes)+(*it_KS), "" ) ; 
       }
    }
    file->Close();  // close the file 

    fitter.combineDataSets();
    //================================================================================

    //================================================================================
    // Create PDFs and then add by csv the pdfs that should be used for the mass 
    //================================================================================
    fitter.createPDFSets();

    for(std::vector<TString>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
       for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          TString pdf_names = "";
          for(std::vector<TString>::iterator it_type     = type.begin();   it_type  != type.end();   ++it_type) { 
	     pdf_names = pdf_names+(*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf,";
	  }

          for(std::multimap<TString,TString>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
 	     if ((*it_modes) == (it_cross->second)){  
	        pdf_names =  pdf_names+"CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_pdf,";
	     }
          } 	

          for(std::multimap<TString,TString>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
 	     if ((*it_modes) == (it_part_reco->first)){  
                pdf_names = pdf_names+"Bkg_"+(*it_modes)+(*it_KS)+"_"+(it_part_reco->second)+"_pdf,";
	     } 
          }
          pdf_names = pdf_names+"combinatoric_"+(*it_modes)+(*it_KS);
          fitter.addPDFs("KS"+(*it_modes)+(*it_KS),pdf_names);
          std::cout << "Creating pdf's : "<< "KS"+(*it_modes)+(*it_KS) << ", " << pdf_names << std::endl;

       }
    }

    for(std::vector<TString>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
       for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          fitter.addYields( "KS"+(*it_modes)+(*it_KS) ) ;
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

    // Set the same mean for the Bd and Bs modes
    for(std::vector<TString>::iterator it_type     = type.begin();   it_type  != type.end();   ++it_type) {
       for(std::vector<TString>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
          for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
 	     fitter.addConstraint((*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf_mu","@0",(*it_type)+"2KSpipiDD_pdf_mu");
	  }
       }
    } 

    // Set witdh of Bs to be the same as Bd
    for(std::vector<TString>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
       for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          fitter.addConstraint("Bs2KS"+(*it_modes)+(*it_KS)+"_pdf_sigma","@0","Bd2KS"+(*it_modes)+(*it_KS)+"_pdf_sigma");
       }
    } 
   
    // Constraints the Kpi and KK widths to pipi
    for(std::vector<TString>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
       if ((*it_modes) != "pipi"){
          fitter.addParameter( "ratio_width_"+(*it_modes)+"_pipi", 0, 5.0);
          for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
             fitter.addConstraint("Bd2KS"+(*it_modes)+(*it_KS)+"_pdf_sigma","@0*@1","Bd2KSpipi"+(*it_KS)+"_pdf_sigma,ratio_width_"+(*it_modes)+"_pipi");
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
    for(std::vector<TString>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
       for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          if ((*it_modes) != "pipi"){
             fitter.addConstraint("combinatoric_"+(*it_modes)+(*it_KS)+"_slope","@0","combinatoric_pipi"+(*it_KS)+"_slope");
          }
       }
    }
    fitter.addParameter( "ratio_combinatoric", -5.0, 5.0 );
    fitter.addConstraint("combinatoric_pipiLL_slope","@0*@1","combinatoric_pipiDD_slope,ratio_combinatoric");

    // ------------------------------------------- //
    //              Crossfeed Yields               // 
    // ------------------------------------------- //

    // Create constraints to the crossfeed yields
    for(std::multimap<TString,TString>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
       for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          fitter.addParameter( "frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS), 0., 1.0);
          if ((it_cross->first)== "Kpi" ){
             fitter.addConstraint("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_pdf_KS"+(it_cross->second)+(*it_KS)+"_Yield","@0*@1","Bs2KS"+(it_cross->first)+(*it_KS)+"_pdf_KS"+(it_cross->first)+(*it_KS)+"_Yield,frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS));
          } else { 
             fitter.addConstraint("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_pdf_KS"+(it_cross->second)+(*it_KS)+"_Yield","@0*@1","Bd2KS"+(it_cross->first)+(*it_KS)+"_pdf_KS"+(it_cross->first)+(*it_KS)+"_Yield,frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS));
          }
       }
    }
 
    // Create the gaussian constraints
    for(std::multimap<TString,TString>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
       for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          if (((it_cross->second) == "Kpi") && ((it_cross->first) == "pipi")) {
             if ((*it_KS)=="DD"){
                fitter.addGaussianConstraint("frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS), 0.0580,  0.0095);
	     } else {
                fitter.addGaussianConstraint("frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS), 0.0562, 0.0059);
             }
          } else if (((it_cross->second) == "Kpi") && ((it_cross->first) == "KK")) {
             if ((*it_KS)=="DD"){
                fitter.addGaussianConstraint("frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS), 0.0761, 0.0046);
	     } else {
                fitter.addGaussianConstraint("frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS), 0.0693, 0.0046);
             }
          } else if ((it_cross->second) == "pipi"){ 
             if ((*it_KS)=="DD"){
                fitter.addGaussianConstraint("frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS), 0.0505, 0.0054);
	     } else {
                fitter.addGaussianConstraint("frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS), 0.0482, 0.0059);
             }
          } else {
             if ((*it_KS)=="DD"){
                fitter.addGaussianConstraint("frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS), 0.0372, 0.0024);
	     } else {
                fitter.addGaussianConstraint("frac_cross_"+(it_cross->first)+"_"+(it_cross->second)+(*it_KS), 0.0368, 0.0029);
             }
          }
       }
    }
    // ------------------------------------------- //
    //  Partially reconstructed yields constraints // 
    // ------------------------------------------- //
   
    // Create yield fractions
    for(std::multimap<TString,TString>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
       fitter.addParameter("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second),   0., 1.);
    }
    // Create the yield constraints    
    for(std::multimap<TString,TString>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
       for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS != KS_cat.end(); ++it_KS) {
          if ( (it_part_reco->first) == "Kpi" ) {
             fitter.addConstraint("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_pdf_KS"+(it_part_reco->first)+(*it_KS)+"_Yield", "@0*@1", "Bs2KS"+(it_part_reco->first)+(*it_KS)+"_pdf_KS"+(it_part_reco->first)+(*it_KS)+"_Yield,frac_"+(it_part_reco->first)+"_"+(it_part_reco->second));
	  } else {
             fitter.addConstraint("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_pdf_KS"+(it_part_reco->first)+(*it_KS)+"_Yield", "@0*@1", "Bd2KS"+(it_part_reco->first)+(*it_KS)+"_pdf_KS"+(it_part_reco->first)+(*it_KS)+"_Yield,frac_"+(it_part_reco->first)+"_"+(it_part_reco->second));
          }
       }
    }
    // Add gaussian constraints
    for(std::multimap<TString,TString>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
       if ( (it_part_reco->first) == "pipi" ) {
	  if ( (it_part_reco->second) == "Bd2KSpipig"){ 
	     fitter.addGaussianConstraint("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second),   0.04, 0.008);
	  } else if ( (it_part_reco->second) == "Bd2etapKS_rhog"){ 
	     fitter.addGaussianConstraint("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second),   0.04, 0.004);
          } else if ( (it_part_reco->second) == "Bu2D0pi"){ 
	     fitter.addGaussianConstraint("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second),   0.40, 0.08);
          } else { 
	     fitter.addGaussianConstraint("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second),   0.04, 0.04);
          }
       } else if ( (it_part_reco->first) == "Kpi" ) {
	  if ( (it_part_reco->second) == "Bu2D0K"){ 
	     fitter.addGaussianConstraint("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second),   0.26, 0.052);
          } else { 
	     fitter.addGaussianConstraint("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second),   0.04, 0.03);
          }
       } else {
	     fitter.addGaussianConstraint("frac_"+(it_part_reco->first)+"_"+(it_part_reco->second),   0.12, 0.12);
       }
    }
  
    //================================================================================    

    //================================================================================
    // Finally perform the fit to the data and the plot some results.
    //================================================================================  
    fitter.performFit();
    RooFitResult res( *fitter.getFitResult( "fitResults" ) );
//    res.Print("V"); 
		//================================================================================
    // Do some nice plotting of the invariant mass spectra, this will do residual and
    //================================================================================  
    TString dir_plots = saveDir+"Syst/plots/";
    fitter.setPlotBins( massvar, 50 ); // Set binning
    for(std::vector<TString>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
       for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          if ((*it_modes) == "pipi"){
             fitter.plotMass( dir_plots+"KS"+(*it_modes)+(*it_KS), "m(#it{K}_{S}^{0}#it{#pi^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]", "KS"+(*it_modes)+(*it_KS),"fitResults" ) ;
	  } else if ((*it_modes) == "Kpi"){
             fitter.plotMass( dir_plots+"KS"+(*it_modes)+(*it_KS), "m(#it{K}_{S}^{0}#it{K^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]", "KS"+(*it_modes)+(*it_KS),"fitResults" ) ;
          } else {
             fitter.plotMass( dir_plots+"KS"+(*it_modes)+(*it_KS), "m(#it{K}_{S}^{0}#it{K^{+}K^{#font[122]{-}}}) [MeV/#it{c}^{2}]", "KS"+(*it_modes)+(*it_KS),"fitResults" ) ;
          }
       }
    }
    //================================================================================  

    //================================================================================
    // Systematic studies Type II
    //================================================================================  

    // Import official PDF from the WS
    V0hhFit::SimultaneousFitter fitter_official( "B2KShhFit", "B0(d,s) --> KS h' h Fit" );
    fitter_official.loadWS( saveDir+"WS/Data-WS.root", "newDesktop", false );

    V0hhFit::ToyStudy syst(&fitter, nExp);

    syst.runSystII("fitResults", &fitter_official);

    // Plot results
    syst.plotSystII(saveDir+"/Syst/plots/");

    return 0;
}
