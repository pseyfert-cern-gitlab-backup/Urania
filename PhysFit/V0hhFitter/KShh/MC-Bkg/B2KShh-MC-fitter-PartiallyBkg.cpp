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
    TString saveDir = currentDir+"/../KShh/"; 

    fitter.set1DFitVarName( massvar );
    fitter.make1DFitVar( xmin, xmax, "MeV/c^{2}", "m(#it{K^{0}_{#rm S} h^{+} h^{-}})" );
    fitter.setPlotBins( massvar, 40 );
    //================================================================================
    //
    //================================================================================
    // Definition of the modes 
    //================================================================================

    std::multimap<TString,TString> part_reco;
    std::vector<TString> KS_cat;
   
    KS_cat.push_back("DD");
    KS_cat.push_back("LL");

    // Partially reconstruct bkgs (more modes need to added)
    part_reco.insert(std::make_pair("pipi","Bd2etapKS"));
    part_reco.insert(std::make_pair("pipi","Bd2KSpipig"));
    part_reco.insert(std::make_pair("pipi","Bu2D0pi")); // not enough statistics, so for the time being this is fixed in the fit!
    part_reco.insert(std::make_pair("pipi","Bd2Kst0rho0"));

    part_reco.insert(std::make_pair("Kpi","Bu2D0K"));
    part_reco.insert(std::make_pair("Kpi","Bu2KstPhi"));
    
    part_reco.insert(std::make_pair("KK","Bu2KstPhi"));
    //================================================================================

    //================================================================================
    // Make all PDFs 
    //================================================================================

    // Partially reconstructed bkg (Bu2D0pi fixed for the time being)
    for(std::multimap<TString,TString>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
       for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
	  if ((it_part_reco->second) == "Bu2D0pi"){
             fitter.makeArgusConvGaussFixed("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_pdf", 15, 5150, -22, 0.7); 
          } else {
             fitter.makeArgusConvGauss("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_pdf", 15, 5279, 5000, 5400, -30, -50, 0 , 1.0, 0, 20); 
          }
       }
    }
    //================================================================================

    //================================================================================
    // Import the dataset 
    //================================================================================
    TString dataDir = getenv("V0HHFITTERDATA");
    TString basedir = dataDir+"/KShh_old/Ntuples/MC/";
    TFile *file = 0;
    TTree* tree = 0;

    for(std::multimap<TString,TString>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
       for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
   
          file = TFile::Open( basedir+"KS"+(it_part_reco->first)+"/2011/"+(it_part_reco->second)+"-MC11a-MagAll-Stripping17b-Selection_noBDT_CutSpurios.root", "READ" );
    	  tree = dynamic_cast<TTree*>( file->Get( "tupleB2KS"+(it_part_reco->first)+(*it_KS) ) );
	  fitter.makeMassDataSet( tree, massvar, "Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second), "" ) ; 
	  file->Close();  // close the file
       }
    } 

    fitter.combineDataSets();
    //================================================================================

    //================================================================================
    // Create PDFs and then add by csv the pdfs that should be used for the mass 
    //================================================================================
    fitter.createPDFSets();

    for(std::multimap<TString,TString>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
       for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          fitter.addPDFs("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second), "Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_pdf");
          fitter.addYields("Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)) ;
       }
    }

    fitter.buildAddPdfs();
    fitter.buildModel();
    //================================================================================
  
    //================================================================================
    // Set parameter constraints and and anything that is constant or has Gaussian 
    // constraints. Can also set blinding of variables here too.
    //================================================================================    

    // Set the DD and LL parameters to be the same
    for(std::multimap<TString,TString>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
       fitter.addConstraint("Bkg_"+(it_part_reco->first)+"LL_"+(it_part_reco->second)+"_pdf_threshold","@0","Bkg_"+(it_part_reco->first)+"DD_"+(it_part_reco->second)+"_pdf_threshold");
       fitter.addConstraint("Bkg_"+(it_part_reco->first)+"LL_"+(it_part_reco->second)+"_pdf_slope","@0","Bkg_"+(it_part_reco->first)+"DD_"+(it_part_reco->second)+"_pdf_slope");
       fitter.addConstraint("Bkg_"+(it_part_reco->first)+"LL_"+(it_part_reco->second)+"_pdf_power","@0","Bkg_"+(it_part_reco->first)+"DD_"+(it_part_reco->second)+"_pdf_power");
    }
 
    //================================================================================
    // Finally perform the fit to the data and the plot some results.
    //================================================================================  
    fitter.performFit("fitResults",true);
    RooFitResult res(*fitter.getFitResult( "fitResults" ));
    res.Print("v");
	
    //================================================================================  

    //================================================================================
    // Plot invariant mass spectra and residuals
    //================================================================================  
    TString dir_plots = saveDir+"MC-Bkg/plots/";
    for(std::multimap<TString,TString>::iterator it_part_reco = part_reco.begin(); it_part_reco != part_reco.end(); ++it_part_reco){
       for(std::vector<TString>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
          fitter.plotPrettyMassAndPull(dir_plots+"Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second)+"_MCFit", "m(#it{K}_{S}^{0}#it{#pi^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]", "Bkg_"+(it_part_reco->first)+(*it_KS)+"_"+(it_part_reco->second), "fitResults", "log") ;
       }
    }
    //================================================================================    

    //================================================================================
    // Save everything in the workspace!
    //================================================================================  
    fitter.saveWS( saveDir+"WS/MC-Bkg-WS.root" );

    return 0;
}
