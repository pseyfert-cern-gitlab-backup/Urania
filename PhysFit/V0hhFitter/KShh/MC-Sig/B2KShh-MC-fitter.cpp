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
//#include "DataLocationConfig.h"


int main() {
    
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
    TString saveDir = currentDir+"/KShh/"; 

    fitter.set1DFitVarName( massvar );
    fitter.make1DFitVar( xmin, xmax, "MeV/c^{2}", "m(#it{K^{0}_{#rm S} h^{+} h^{-}})" );
    fitter.setPlotBins( massvar, 50 );
    //================================================================================

    //================================================================================
    // Definition of the modes 
    //================================================================================

    // Define possible combinations of signal and crossfeed modes
    // For the time being one needs to manually comment out some contribution 
    std::vector<TString> type;
    std::vector<TString> modes;
    std::vector<TString> KS_cat;
    std::multimap<TString,TString> cross_feed;
   
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
    //================================================================================

    //================================================================================
    // Make all PDFs 
    //================================================================================

    // Signal modes (e.g. makeDoubleCB, makeCruijff, makeApolonios, makeIpatia, ...)
    for(std::vector<TString>::iterator it_type     = type.begin();   it_type  != type.end();   ++it_type) {
       for(std::vector<TString>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
          for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
	     if ((*it_type) == "Bs"){  
			 fitter.makeDoubleCB((*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf", 5366, 5250, 5375, 8, 0, 20,
								 1, 0, 5,
								 -1, -5, 0,
								 1, -5, 5,
								 1, -5 ,5,
								 0.5);
	     } else {
		fitter.makeDoubleCB((*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf", 5280, 5250, 5300, 8, 0, 20, 1, 0, 5, -1, -5, 0, 1, -5, 5, 1, -5 ,5, 0.5);
	     }
	  }
       }
    }

    // Crossfeeds (Many alternatives for the Double CB, e.g. same mean with different widths)
    for(std::multimap<TString,TString>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
       for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {

          fitter.makeDoubleCB("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_pdf", 5322, 5200, 5450, 8, 0, 20, 1, 0, 5, -1, -5, 0, 1, -5, 5, 1, -5 ,5, 0.5);
       }
    }
    //================================================================================

    //================================================================================
    // Import the dataset 
    //================================================================================
    TString dataDir = getenv("V0HHFITTERDATA");
    TString basedir = dataDir+ "/KShh_old/Ntuples/MC/";
    TFile *file = 0;
    TTree* tree = 0;

    for(std::vector<TString>::iterator it_type     = type.begin();   it_type  != type.end();   ++it_type) {
       for(std::vector<TString>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
          for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
	     			 file = TFile::Open( basedir+"KS"+(*it_modes)+"/2011/"+(*it_type)+"2"+(*it_modes)+"KS-MC11a-MagAll-Stripping17b-withMCtruth-Selection.root", "READ" );
	     			 tree = dynamic_cast<TTree*>( file->Get( "tupleB2KS"+(*it_modes)+(*it_KS) ) );
	     			 fitter.makeMassDataSet( tree, massvar, (*it_type)+"2KS"+(*it_modes)+(*it_KS), "" ) ; 
             file->Close();  // close file 
	  			}
       }
    }

    for(std::multimap<TString,TString>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
       for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
   

	  if ((it_cross->first) == "Kpi"){
             file = TFile::Open( basedir+"KS"+(it_cross->second)+"/2011/Bs2"+(it_cross->first)+"KS-as-"+(it_cross->second)+"-MC11a-MagAll-Stripping17b-withMCtruth-Selection.root", "READ" );
	  } else {
             file = TFile::Open( basedir+"KS"+(it_cross->second)+"/2011/Bd2"+(it_cross->first)+"KS-as-"+(it_cross->second)+"-MC11a-MagAll-Stripping17b-withMCtruth-Selection.root", "READ" );
	  }
    	  tree = dynamic_cast<TTree*>( file->Get( "tupleB2KS"+(it_cross->second)+(*it_KS) ) );
	    
	  if ((it_cross->first) == "Kpi"){
	     fitter.makeMassDataSet( tree, massvar, "Bs2KS"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS), "" ) ; 
	  } else {
	     fitter.makeMassDataSet( tree, massvar, "Bd2KS"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS), "" ) ; 
	  }
	  file->Close();  // close the file 
       }
    } 
 
    fitter.combineDataSets();
    //================================================================================

    //================================================================================
    // Create PDFs and then add by csv the pdfs that should be used for the mass 
    //================================================================================
    fitter.createPDFSets();

    // Signal modes
    for(std::vector<TString>::iterator it_type     = type.begin();   it_type  != type.end();   ++it_type) {
       for(std::vector<TString>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
          for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {

    	     fitter.addPDFs((*it_type)+"2KS"+(*it_modes)+(*it_KS), (*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_pdf");
	     fitter.addYields((*it_type)+"2KS"+(*it_modes)+(*it_KS)) ;
	  }
       }
    }

    // Crossfeeds
    for(std::multimap<TString,TString>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
       for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          if ((it_cross->first) == "Kpi"){
	     fitter.addPDFs( "Bs2KS"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS), "CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_pdf");
             fitter.addYields("Bs2KS"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)) ;
          } else {
	     fitter.addPDFs( "Bd2KS"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS), "CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_pdf");
             fitter.addYields("Bd2KS"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)) ;
	  }
       }
    }

    fitter.buildAddPdfs();
    fitter.buildModel();
    //================================================================================
   
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
    TString dir_plots = saveDir+"MC-Sig/plots/";
    fitter.setPlotBins( massvar, 40 ); // Set binning
    for(std::vector<TString>::iterator it_type     = type.begin();   it_type  != type.end();   ++it_type) {
       for(std::vector<TString>::iterator it_modes = modes.begin();  it_modes != modes.end();  ++it_modes) {
          for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
	     if ((*it_modes) = "pipi"){
	        fitter.plotMassAndPull( dir_plots+(*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_MCFit", "m(#it{K}_{S}^{0}#it{#pi^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]", (*it_type)+"2KS"+(*it_modes)+(*it_KS), "fitResults", "log") ;
	     } else if ((*it_modes) = "Kpi"){
	        fitter.plotMassAndPull( dir_plots+(*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_MCFit", "m(#it{K}_{S}^{0}#it{K^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]", (*it_type)+"2KS"+(*it_modes)+(*it_KS), "fitResults", "log") ;
	     } else {
	        fitter.plotMassAndPull( dir_plots+(*it_type)+"2KS"+(*it_modes)+(*it_KS)+"_MCFit", "m(#it{K}_{S}^{0}#it{K^{+}K^{#font[122]{-}}}) [MeV/#it{c}^{2}]", (*it_type)+"2KS"+(*it_modes)+(*it_KS), "fitResults", "log") ;
	     }
          }
       }
    }

    // Crossfeeds
    for(std::multimap<TString,TString>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
       for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          if ((it_cross->first) == "Kpi"){
	     if ((it_cross->second) == "pipi") {
	        fitter.plotMassAndPull(dir_plots+"Bs2KS"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_MCFit", "m(#it{K}_{S}^{0}#it{#pi^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]", "Bs2KS"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS), "fitResults", "log") ;
	     } else {
	        fitter.plotMassAndPull(dir_plots+"Bs2KS"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_MCFit", "m(#it{K}_{S}^{0}#it{K^{+}K^{#font[122]{-}}}) [MeV/#it{c}^{2}]", "Bs2KS"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS), "fitResults", "log") ;
	     }

          } else {
	     fitter.plotMassAndPull(dir_plots+"Bd2KS"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_MCFit", "m(#it{K}_{S}^{0}#it{K^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]", "Bd2KS"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS), "fitResults", "log") ;
          }
       }
    }
    //================================================================================    

    //================================================================================
    // Save everything in the workspace!
    //================================================================================  
    fitter.saveWS( saveDir+"WS/MC-Sig-WS.root" );

    return 0;
}
