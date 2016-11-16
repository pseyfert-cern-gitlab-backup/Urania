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
#include "boost/program_options.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string.hpp"
#include "boost/bind.hpp"
#include "KShh/Constraints/useConstraints.cpp"
//#include "scripts/relaxCFthresholds.cc"
//#include "scripts/bdtcut.hh"

bool piToK(std::pair<std::string,std::string> cf)
{
  if (cf.first.find("KK") != std::string::npos || cf.second.find("pipi") != std::string::npos)
    return false;
  return true;
}

std::string nameType(std::pair<std::string,std::string> cf)
{
	if (cf.first.find("KK") != std::string::npos || cf.second.find("pipi") != std::string::npos)
		return "KToPi";
	return "PiToK";
}

void addThreshold(std::map<std::string,std::pair<double,double> >& thresholds, std::string key, double val1, double val2)
{
	thresholds[key] = std::make_pair(val1,val2);
}

std::string relaxCFthresholds(std::string invMass, std::string year, std::string ks, std::string selection, double shift)
{
	if (year == "2012a" || year == "2012b")
		year = "2012";
	std::string  pidcut = "";
	std::map<std::string,std::pair<double,double> > thresholds;
	addThreshold(thresholds,"Loose-pipi-2011-DD",0.20,0.20);
	addThreshold(thresholds,"Loose-pipi-2011-LL",0.25,0.25);
	addThreshold(thresholds,"Loose-pipi-2012-DD",0.20,0.20);
	addThreshold(thresholds,"Loose-pipi-2012-LL",0.25,0.25);
	addThreshold(thresholds,"Tight-pipi-2011-DD",0.25,0.25);
	addThreshold(thresholds,"Tight-pipi-2011-LL",0.35,0.35);
	addThreshold(thresholds,"Tight-pipi-2012-DD",0.22,0.22);
	addThreshold(thresholds,"Tight-pipi-2012-LL",0.35,0.35);
	
	addThreshold(thresholds,"Loose-KK-2011-DD",-0.20,-0.20);
	addThreshold(thresholds,"Loose-KK-2011-LL",-0.25,-0.25);
	addThreshold(thresholds,"Loose-KK-2012-DD",-0.20,-0.20);
	addThreshold(thresholds,"Loose-KK-2012-LL",-0.25,-0.25);
	addThreshold(thresholds,"Tight-KK-2011-DD",0.03,0.03);
	addThreshold(thresholds,"Tight-KK-2011-LL",0.00,0.00);
	addThreshold(thresholds,"Tight-KK-2012-DD",0.02,0.02);
	addThreshold(thresholds,"Tight-KK-2012-LL",0.00,0.00);
	
	addThreshold(thresholds,"Loose-Kpi-2011-DD",-0.20,0.20);
	addThreshold(thresholds,"Loose-Kpi-2011-LL",-0.25,0.25);
	addThreshold(thresholds,"Loose-Kpi-2012-DD",-0.20,0.20);
	addThreshold(thresholds,"Loose-Kpi-2012-LL",-0.25,0.25);
	addThreshold(thresholds,"Tight-Kpi-2011-DD",0.03,0.25);
	addThreshold(thresholds,"Tight-Kpi-2011-LL",0.00 ,0.35);
	addThreshold(thresholds,"Tight-Kpi-2012-DD",0.02,0.22);
	addThreshold(thresholds,"Tight-Kpi-2012-LL",0.00 ,0.35);
	
	addThreshold(thresholds,"Loose-piK-2011-DD",0.20,-0.20);
	addThreshold(thresholds,"Loose-piK-2011-LL",0.25,-0.25);
	addThreshold(thresholds,"Loose-piK-2012-DD",0.20,-0.20);
	addThreshold(thresholds,"Loose-piK-2012-LL",0.25,-0.25);
	addThreshold(thresholds,"Tight-piK-2011-DD",0.25,0.03);
	addThreshold(thresholds,"Tight-piK-2011-LL",0.35,0.00);
	addThreshold(thresholds,"Tight-piK-2012-DD",0.22,0.02);
	addThreshold(thresholds,"Tight-piK-2012-LL",0.35,0.00);
	  
	  std::pair<double,double> vals = thresholds[selection+"-"+invMass+"-"+year+"-"+ks];
	  std::stringstream ss;
	  ss << vals.first - shift;
	  std::string val1 = ss.str();
	  ss.str("");
	  ss << vals.second - shift;
	  std::string val2 = ss.str();
	  TString easyInvMass(invMass.c_str());
	  std::string h1  = (easyInvMass.BeginsWith("pi"))?"pi":"K";
	  std::string nh1 = (easyInvMass.BeginsWith("pi"))?"K":"pi";
	  std::string h2  = (easyInvMass.  EndsWith("pi"))?"pi":"K";
	  std::string nh2 = (easyInvMass.  EndsWith("pi"))?"K":"pi";
	  std::string cut1 = "h1_PROBNN"+h1+" - h1_PROBNN"+nh1+" > "+val1;
	  std::string cut2 = "h2_PROBNN"+h2+" - h2_PROBNN"+nh2+" > "+val2;
	  return cut1 + " && " + cut2;
}

int main( int argc, char* argv[] ) {

	std::vector<std::string> year;
	std::vector<std::string> KS_cat;
	std::vector<std::string> cf;
	std::multimap<std::string,std::string> cross_feed;
	std::string sig_shape("");
	std::string selectionType("");
	std::string constraints("Standard");
	std::string mcOrigin("Louis");
	std::string protonCut("");	
	double relaxShift(0);
	namespace po = boost::program_options; 
	po::options_description decisions("Options");
	
	decisions.add_options()
		("help,h", "produce help message")
		("yearPeriod,y", boost::program_options::value< std::vector< std::string > >( &year )->multitoken(), "specify the list of MC year conditions to be considered. Options are: 2011, 2012a, 2012b")
		("KS", boost::program_options::value< std::vector< std::string > >( &KS_cat )->multitoken(), "specify the KS category : DD, LL")
		("crossFeeds,c", boost::program_options::value< std::vector< std::string > >( &cf )->multitoken(), "specify the signal crossfeeds : Bd2KSpipiAsKpi, Bd2KSpipiAspiK, Bs2KSKpiAspipi, Bs2KSKpiAsKK, Bd2KSKKAsKpi, Bd2KSKKAspiK")
		("sigShape", boost::program_options::value<std::string>(&sig_shape), "specify the alternative signal mode shape : Cruijff, Apollonios, Amoroso, Hypatia or Hypatia2")
		("selectionBDT,b", boost::program_options::value<std::string>(&selectionType), "specify which selection has been used in the sample: Loose, Tight, DP1 or DP2")
		("constraints", boost::program_options::value<std::string>(&constraints))
		("mcOrigin"    , boost::program_options::value<std::string>(&mcOrigin),"")    
		("relax"    , boost::program_options::value<double>(&relaxShift),"Relaxes the thresholds of the PID cuts.")    
		("protonCut"  , boost::program_options::value<std::string>(&protonCut),"")
		;
	
	boost::program_options::variables_map vm;
	boost::program_options::store( boost::program_options::parse_command_line( argc, argv, decisions ), vm );
	boost::program_options::notify( vm );

	if (vm.count("protonCut"))
		{
			if (protonCut == "strong")
				std::cout << "INFO: Using a strong proton PID cut." << std::endl;			
		}
	std::string protonPar = (protonCut == "strong")? "-StrongPcut":"";
    std::string optionFile("constraints-CrossOnly-");
    optionFile += constraints;
    
    std::ifstream f((std::string(getenv("V0HHFITTERROOT"))+"/KShh/Constraints/"+optionFile+".txt").c_str());
    if (!f.is_open())
		{
		  std::cout << "ERROR: Could not open constraints file " << (std::string(getenv("V0HHFITTERROOT"))+"/KShh/Constraints/")+optionFile+".txt" << "." << std::endl;
	return 0;
      }
	bool lambdaB      =KShhConstraints::readBool(optionFile,"lambdaB");
	bool onlyLambdaB  = KShhConstraints::readBool(optionFile,"onlyLambdaB");
	bool lambdaBArgus = KShhConstraints::readBool(optionFile,"lambdaBArgus");
	
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
	  if (!onlyLambdaB)
		  {
			  cross_feed.insert(std::make_pair("Bd2KSpipi","Kpi"));
			  cross_feed.insert(std::make_pair("Bs2KSKpi","pipi"));
			  cross_feed.insert(std::make_pair("Bs2KSKpi","KK"));
			  cross_feed.insert(std::make_pair("Bd2KSKK","Kpi"));
		  }
	  if (mcOrigin != "Louis" && mcOrigin != "Louis-PIDCalib" && !onlyLambdaB)
		  {
			  cross_feed.insert(std::make_pair("Bd2KSpipi","piK"));
			  cross_feed.insert(std::make_pair("Bd2KSKK","piK"));
		  }
	  if ((mcOrigin == "Louis" || onlyLambdaB) && lambdaB)
		  {
			  cross_feed.insert(std::make_pair("Lb2KS0ppi","pipi")) ;
			  cross_feed.insert(std::make_pair("Lb2KS0ppi","piK")) ;
			  cross_feed.insert(std::make_pair("Lb2KS0ppi","Kpi")) ;
			  //			  cross_feed.insert(std::make_pair("Lb2KS0ppi","KK")) ;
			  //			  cross_feed.insert(std::make_pair("Lb2KS0pK","pipi")) ;
			  cross_feed.insert(std::make_pair("Lb2KS0pK","piK")) ;
			  cross_feed.insert(std::make_pair("Lb2KS0pK","Kpi")) ;
			  cross_feed.insert(std::make_pair("Lb2KS0pK","KK")) ;
		  }
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
      selectionType = "Loose"; 
    }
    if (vm.count("sigShape")) {
		std::cout << "INFO: Modifying nominal signal model to " << sig_shape << std::endl;
    } else {
		sig_shape = "DoubleCB"; 
    }
    
    if (KShhConstraints::readBool(optionFile,"Bd2KSKpi"))
      {
		  cross_feed.insert(std::make_pair("Bd2KSKpi","pipi"));
		  cross_feed.insert(std::make_pair("Bd2KSKpi","KK"));
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
    fitter.setPlotBins( massvar, 50 );
    //================================================================================

    //================================================================================
    // Make all PDFs 
    //================================================================================
    // Crossfeeds 
	bool singleCB   = KShhConstraints::readBool(optionFile,"SingleCB");
	bool twoWidths  = KShhConstraints::readBool(optionFile,"twoWidths");
	bool shiftMeans = KShhConstraints::readBool(optionFile,"shiftMeans");
	bool mixed      = KShhConstraints::readBool(optionFile,"mixed");

    for(std::vector<std::string>::iterator it_year        = year.begin();   it_year  != year.end();   ++it_year) {
		for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
			for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
				if (it_year->find("2012") != std::string::npos && it_cross->first.find("Lb") != std::string::npos)
					continue;
				if (it_cross->first.find("Lb") == std::string::npos)
					{
						if (singleCB)
							fitter.makeSingleCB(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 
												5322, 5200, 5450,
												8, 0, 100,
												1, 0, 15,
												1, 0 ,50);
						else if (!twoWidths && !shiftMeans)
							if (!mixed || !piToK(*it_cross))
								fitter.makeDoubleCB(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 
													5322, 5200, 5600,
													8, 0, 100,
													1, 0, 20,
													-1, -20, 0.,
													1, 0, 50,
													1, 0 ,50,
													0.5);
							else
								fitter.makeSingleCB(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 
													5322, 5200, 5600,
													8, 0, 100,
													1, 0, 20,
													1, 0 ,50
													);
						
						else if (!twoWidths && shiftMeans)
							fitter.makeDoubleCBDiffMeans(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 
														 5322., 5200., 5600.,
														 0.,-20.,20.,
														 8, 0, 100,
														 1, 15, 0,
														 -1, -15, 0,
														 1, 0, 50,
														 1, 0 ,50,
														 0.5);
						
						else					
							fitter.makeDoubleCB(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 
												5322, 5200, 5600, //mu
												8, 0, 100,        //sigma
												1.,0.,15.,        //alpha0
												//										1.,0.,15.,        //alpha0
												-1., -50., 0.,    //alpha1Oalpha0
												1, 0, 50,         //n0
												1, 0 ,50,         //n1oN0
												0.5);             //coreFrac
					}
				else
					if (lambdaBArgus)
						fitter.makeArgusConvGauss(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(),
												  50., 5., 100., 
												  5500., 5000., 5800.,
												  -30, -80, 0,
												  0.5,0.,20.
												  );
					else
						fitter.makeDoubleCB(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(),
											5550, 5200, 5600,
											8, 0, 100,
											1.,0.,15.,
											-1., -50., 0.,
											1, 0, 50,
											1, 0 ,50,
											0.5);

				//	    else
				//	      fitter.makeSingleCB(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str(), 5322, 5200, 5450, 8, 0, 30, 1, 0, 5, 1, 0, 5);	    
			}
		}
    }
    //================================================================================

    //================================================================================
    // Import the dataset 
    //================================================================================
    TString dataDir = getenv("V0HHFITTERDATA");
    std::string data_aux = (dataDir).Data(); 
    std::string basedir = "/afs/cern.ch/work/l/lohenry/Data/2014-Analysis/";
	if (mcOrigin == "Louis")
		basedir = "root://eoslhcb.cern.ch//eos/lhcb/user/l/lohenry/KShhFit/MonteCarlo/";
	if (mcOrigin == "Louis-PIDCalib")
		basedir = "/afs/cern.ch/work/l/lohenry/Data/newPID/";
    TFile *file = 0;
    TTree* tree = 0;

	bool relax = vm.count("relax");
	std::stringstream ss;
	ss << relaxShift;
	TString temp = ss.str().c_str();
	temp.ReplaceAll(".",",");
	std::string relaxShift_str = temp.Data();
	if (relax)
		std::cout << "WARNING: Relaxing the PID thresholds by " << relaxShift << "." << std::endl;

    for(std::vector<std::string>::iterator it_year = year.begin();   it_year  != year.end();   ++it_year) {
		for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
		  for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
			  if (it_year->find("2012") != std::string::npos && it_cross->first.find("Lb") != std::string::npos)
				  continue;
			  if (it_cross->second == "piK" && mcOrigin == "Louis" && it_cross->first.find("Lb") == std::string::npos)
				  continue;
			  //             file = TFile::Open( (basedir+(*it_year)+"/KShhFit/"+selectionType+"/KS"+(it_cross->second)+"/"+(it_cross->first)+"-MC-"+(*it_year)+"-MagAll.root").c_str(), "READ" );
			  //	    file = TFile::Open( (basedir+(*it_year)+"/SingleCand/"+selectionType+"/"+(it_cross->first)+"/"+(it_cross->first)+"-MC-"+(*it_year)+"-MagAll-Stripping-MCTruth-Trigger-Presel-Vetoes-BDT-PID-SingleCand.root").c_str(), "READ" );
			  std::cout << *it_year << " "<< it_cross->first+" as "+it_cross->second << " " << *it_KS << std::endl;
			  if (mcOrigin == "Rafael")
				  file = TFile::Open( (basedir+(it_cross->first)+"-MC-"+(*it_year)+"-MagAll-Stripping-MCTruth-Trigger-Presel-Vetoes-BDT-PID-SingleCand.root").c_str(), "READ" );
			  else if (mcOrigin == "Louis" && !relax)
				  file = TFile::Open( (basedir+selectionType+"/"+it_cross->first+"-as-"+it_cross->second+"-MC-"+(*it_year)+"-"+(*it_KS)+"-"+selectionType+"-MagAll.root").c_str());
			  else if (mcOrigin == "Louis" && relax)
				  file = TFile::Open( (basedir+selectionType+"/"+it_cross->first+"-as-"+it_cross->second+"-MC-"+(*it_year)+"-"+(*it_KS)+"-"+selectionType+"-MagAll-noPID.root").c_str());
			  else if (mcOrigin == "Louis-PIDCalib")
				  //tmp-Loose-2011-Bs2KSKpi-as-KK-LL.root
				  file = TFile::Open( (basedir+"tmp-"+selectionType+"-"+*it_year+"-"+it_cross->first+"-as-"+it_cross->second+"-"+*it_KS+".root").c_str());
			  if (mcOrigin == "Rafael")
				  tree = dynamic_cast<TTree*>( file->Get( ("B2KShh"+(*it_KS)+"/B2"+(it_cross->second)+"KS").c_str() ) );
			  else if (mcOrigin == "Louis")
				  tree = dynamic_cast<TTree*>( file->Get( ("B2"+it_cross->second+"KS").c_str() ) );
			  //			  std::string cut = "B_BKGCAT == 30 ";
			  else if (mcOrigin == "Louis-PIDCalib")
				  tree = dynamic_cast<TTree*>( file->Get( ("B2"+it_cross->second+"KS").c_str() ) );
			  std::string cut = "(1)";
			  if (mcOrigin != "Louis" || !relax)
				  if (protonCut == "strong" && it_cross->first.find("Lb2") != std::string::npos)
					  cut += " && h1_PROBNNp < 0.2 && h2_PROBNNp < 0.2";
				  else{}
			  else
				  cut += " && (" + relaxCFthresholds(it_cross->second,*it_year,*it_KS,selectionType,relaxShift)+")";
			  if (mcOrigin != "Louis-PIDCalib")
				  fitter.makeMassDataSet( tree, massvar, ((it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)).c_str(), "", cut.c_str() ) ; 
			  else
				  fitter.makeMassDataSet( tree, massvar, ((it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)).c_str(), "", "", "PIDweight" ) ; 
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
				if (it_year->find("2012") != std::string::npos && it_cross->first.find("Lb") != std::string::npos)
					continue;
				if (it_cross->second == "piK" && mcOrigin == "Louis" && it_cross->first.find("Lb") == std::string::npos)
					continue;
				fitter.addPDFs(((it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)).c_str(),
							   ("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf").c_str());
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
    
    std::map<std::string,std::vector<std::string> > vars;
	if (singleCB)
		{
            vars["PiToK"].push_back("mu");
            vars["PiToK"].push_back("sigma0");
            vars["PiToK"].push_back("alpha0");
            vars["PiToK"].push_back("n0");

            vars["KToPi"].push_back("mu");
            vars["KToPi"].push_back("sigma0");
            vars["KToPi"].push_back("alpha0");
            vars["KToPi"].push_back("n0");
		}
	else
		{
			if (!lambdaBArgus)
				{			
					vars["PiToK"].push_back("mu");
					vars["PiToK"].push_back("alpha0");
					vars["PiToK"].push_back("n0");
					if (!mixed)
						{
							vars["PiToK"].push_back("alpha1oAlpha0");
							vars["PiToK"].push_back("n1oN0");
							vars["PiToK"].push_back("coreFrac");
						}
					
					vars["KToPi"].push_back("mu");
					vars["KToPi"].push_back("alpha0");
					vars["KToPi"].push_back("n0");
					vars["KToPi"].push_back("alpha1oAlpha0");
					vars["KToPi"].push_back("n1oN0");
					vars["KToPi"].push_back("coreFrac");
					
					if (!twoWidths)
						{
							vars["KToPi"].push_back("sigma");
							if (!mixed)
								vars["PiToK"].push_back("sigma");
							else
								vars["PiToK"].push_back("sigma0");
						}
					else
						{
							vars["PiToK"].push_back("sigma0");
							vars["KToPi"].push_back("sigma0");
							vars["PiToK"].push_back("s1oS0");
							vars["KToPi"].push_back("s1oS0");
						}
					if (shiftMeans)
						{
							vars["PiToK"].push_back("dM");
							vars["KToPi"].push_back("dM");
						}
					else{}
				}
			else
				{
					vars["PiToK"].push_back("threshold");
					vars["KToPi"].push_back("threshold");
					vars["PiToK"].push_back("sigma");
					vars["KToPi"].push_back("sigma");
					vars["PiToK"].push_back("power");
					vars["KToPi"].push_back("power");
					vars["PiToK"].push_back("slope");
					vars["KToPi"].push_back("slope");
				}
		}
    // Crossfeed shape for the K+pi- and K-pi+
    for(std::vector<std::string>::iterator it_year = year.begin();   it_year  != year.end();   ++it_year)
		for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
			for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross)
				{
					if (it_cross->first.find("Lb") != std::string::npos)
						continue;
					if (it_cross->second.find("piK") != std::string::npos)
						{
							std::string newName(it_cross->second);
							newName.replace(newName.begin(),newName.end(),"Kpi");
							std::string typeName = nameType(*it_cross);
							//						std::cout << typeName << std::endl;
							for (std::vector<std::string>::iterator itVar = vars[typeName].begin() ; itVar != vars[typeName].end() ; ++itVar)		
								{
									
									fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_piK"+(*it_KS)+"_"+(*it_year)+"_pdf_"+(*itVar)).c_str(),
														 "@0",
														 ("CrossFeed_"+(it_cross->first)+"_as_Kpi"+(*it_KS)+"_"+(*it_year)+"_pdf_"+(*itVar)).c_str());
								}
						}
				}
    for(std::vector<std::string>::iterator it_year = year.begin();   it_year  != year.end();   ++it_year)
		for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
			for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross)
				{
					if (it_cross->first.find("Lb") == std::string::npos || it_year->find("2012") != std::string::npos)
						continue;
					if (it_cross->second.find("piK") != std::string::npos)
						{
							std::string newName(it_cross->second);
							newName.replace(newName.begin(),newName.end(),"Kpi");
							std::string typeName = nameType(*it_cross);
							//						std::cout << typeName << std::endl;
							for (std::vector<std::string>::iterator itVar = vars[typeName].begin() ; itVar != vars[typeName].end() ; ++itVar)		
								fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_piK"+(*it_KS)+"_"+(*it_year)+"_pdf_"+(*itVar)).c_str(),
													 "@0",
													 ("CrossFeed_"+(it_cross->first)+"_as_Kpi"+(*it_KS)+"_"+(*it_year)+"_pdf_"+(*itVar)).c_str());
						}
				}
	// Crossfeed mean
    for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
		if (it_cross->second.find("piK") != std::string::npos || it_cross->first.find("Lb2") != std::string::npos)
			continue;
		fitter.addParameter((it_cross->first+"_as_"+it_cross->second+"_mu").c_str(),5100,5500);
		for(std::vector<std::string>::iterator it_year = year.begin();   it_year  != year.end();   ++it_year)
			for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)			  
				{
					if (it_year->find("2012") != std::string::npos && it_cross->first.find("Lb") != std::string::npos)
						continue;
					fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_mu").c_str(),
										 "@0",
										 ((it_cross->first+"_as_"+(it_cross->second)+"_mu").c_str()));
				}
    }
    // Same vars for each year
    std::map<std::string,std::pair<double,double> > varLimits;
    varLimits["sigma"] = std::make_pair(8.,100.);
	varLimits["sigma0"] = std::make_pair(8.,100.);
	varLimits["s1oS0"]  = std::make_pair(0.5,5.);
	varLimits["dM"]     = std::make_pair(-20.,20.);
    varLimits["alpha0"] = std::make_pair(0.,15.);
    varLimits["alpha1oAlpha0"] = std::make_pair(-50.,0.);
    varLimits["n0"] = std::make_pair(0.,50.);
    varLimits["n1oN0"] = std::make_pair(0.,50.);
    varLimits["coreFrac"] = std::make_pair(0.,1.);

	std::map<std::string,double> varVals;
	varVals["mu"] = 5320.;
	varVals["sigma" ] = 19.;
	varVals["sigma0"] = 19.;
	varVals["s1oS0"] = 1.5;
	varVals["dM"] = 0.;
	varVals["alpha0"] = 5.;
	varVals["alpha1oAlpha0"] = -5.;
	varVals["n0"] = 5.;
	varVals["n1oN0"] = 5.;
	varVals["coreFrac"] = 0.;

	//Lb variables ain't no "sameMissID"
	for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross)
		if (it_cross->second.find("piK") == std::string::npos && it_cross->first.find("Lb2") != std::string::npos)
			for (std::vector<std::string>::iterator itVar = vars[nameType(*it_cross)].begin() ; itVar != vars[nameType(*it_cross)].end() ; itVar++)
				fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+"LL_2011_pdf_"+(*itVar)).c_str(),
									 "@0",
									 ("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+"DD_2011_pdf_"+(*itVar)).c_str());
	
    if (KShhConstraints::readBool(optionFile,"sameMissID"))
		{
			for (std::vector<std::string>::iterator itVar = vars["PiToK"].begin() ; itVar != vars["PiToK"].end() ; itVar++)
				if (itVar->find("mu") == std::string::npos)
					fitter.addParameter((*itVar+"_PiToK").c_str(),varVals[*itVar],varLimits[*itVar].first,varLimits[*itVar].second);
			for (std::vector<std::string>::iterator itVar = vars["KToPi"].begin() ; itVar != vars["KToPi"].end() ; itVar++)
				if (itVar->find("mu") == std::string::npos)
					fitter.addParameter((*itVar+"_KToPi").c_str(),varVals[*itVar],varLimits[*itVar].first,varLimits[*itVar].second);
			
			for(std::vector<std::string>::iterator it_year = year.begin();   it_year  != year.end();   ++it_year)
				for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
					for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross)
						{			
							if (it_cross->first.find("Lb") != std::string::npos)
								continue;
							std::string typeName = nameType(*it_cross);
							if (it_cross->second.find("piK") != std::string::npos)
								continue;
							for (std::vector<std::string>::iterator itVar = vars[typeName].begin() ; itVar != vars[typeName].end() ; itVar++)
								if (itVar->find("mu") == std::string::npos)
									{
										if (piToK(*it_cross))
											fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_"+(*itVar)).c_str(),
																 "@0",                                             
																 (*itVar+"_PiToK").c_str());
										else
											fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_"+(*itVar)).c_str(),
																 "@0",                                             
																 (*itVar+"_KToPi").c_str());
									}
						}
		}
    else
		for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross)
			if (it_cross->second.find("piK") == std::string::npos)
				for (std::vector<std::string>::iterator itVar = vars[nameType(*it_cross)].begin() ; itVar != vars[nameType(*it_cross)].end() ; itVar++)
					if (itVar->find("mu") == std::string::npos)
						for(std::vector<std::string>::iterator it_year = year.begin();   it_year  != year.end();   ++it_year)
							if (it_cross->first.find("Lb") == std::string::npos)
								for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS)
									if (it_year->find("2011") == std::string::npos || it_KS->find("DD") == std::string::npos)
										fitter.addConstraint(("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_"+(*itVar)).c_str(),
															 "@0",
															 ("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+"DD_2011_pdf_"+(*itVar)).c_str());
    //================================================================================
    // Finally perform the fit to the data and the plot some results.
    //================================================================================  
	if (!onlyLambdaB)
		fitter.performFit("fitResults",true);
	else
		fitter.performFit("fitResults",false);
    RooFitResult res(*fitter.getFitResult( "fitResults" ));
    res.Print("v");
    //    fitter.getWS()->Print("V");
    //================================================================================  

    //================================================================================
    // Plot invariant mass spectra and residuals
    //================================================================================  
    fitter.setPlotSubComponents(true);
    std::string dir_plots   = saveDir+"MC-Sig/plots/"+selectionType+"/";
    std::string suffix = "-MCFit";
	suffix += "-"+constraints;
	suffix += "-"+mcOrigin;
    suffix += "-"+sig_shape;
	//	if (relax)
	//		suffix += "-Relax-"+relaxShift_str;	
	suffix += protonPar;
    fitter.setPlotBins( massvar, 40 ); // Set binning
    
    // Crossfeeds
    for(std::vector<std::string>::iterator it_year = year.begin();   it_year  != year.end();   ++it_year) {
		for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
			for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
				if (it_year->find("2012") != std::string::npos && it_cross->first.find("Lb") != std::string::npos)
					continue;
				if (it_cross->second == "piK" && mcOrigin == "Louis")
					continue;
				if ((it_cross->second) == "pipi"){
					fitter.plotMassAndPull((dir_plots+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+suffix).c_str(),
										   "m(#it{K}_{S}^{0}#it{#pi^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]",
										   ((it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)).c_str(), "fitResults", "log") ;
				} else if ((it_cross->second) == "KK") {
					fitter.plotMassAndPull((dir_plots+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+suffix).c_str(),
										   "m(#it{K}_{S}^{0}#it{K^{+}K^{#font[122]{-}}}) [MeV/#it{c}^{2}]",
										   ((it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)).c_str(), "fitResults", "log") ;
				} else if ((it_cross->second) == "Kpi") {
					fitter.plotMassAndPull((dir_plots+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+suffix).c_str(),
										   "m(#it{K}_{S}^{0}#it{K^{+}#pi^{#font[122]{-}}}) [MeV/#it{c}^{2}]",
										   ((it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)).c_str(), "fitResults", "log") ;
				} else {
					fitter.plotMassAndPull((dir_plots+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+suffix).c_str(),
										   "m(#it{K}_{S}^{0}#it{K^{#font[122]{-}}#pi^{+}}) [MeV/#it{c}^{2}]",
										   ((it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)).c_str(), "fitResults", "log") ;
				}
			}
		}
    }

    //================================================================================    
    
    //================================================================================
    // Save everything in the workspace!
    //================================================================================  
    //Set each variable to its true value...
    for(std::vector<std::string>::iterator it_year = year.begin();   it_year  != year.end();   ++it_year) {
		for(std::multimap<std::string,std::string>::iterator it_cross = cross_feed.begin(); it_cross != cross_feed.end(); ++it_cross){
			for(std::vector<std::string>::iterator it_KS = KS_cat.begin(); it_KS    != KS_cat.end(); ++it_KS) {
				for (std::vector<std::string>::iterator itVar = vars[nameType(*it_cross)].begin() ; itVar != vars[nameType(*it_cross)].end() ; ++itVar)
					{
						if (it_year->find("2012") != std::string::npos && it_cross->first.find("Lb") != std::string::npos)
							continue;
						std::string varName1 = ("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_"+(*itVar));
						std::string varName2 = varName1;
						if (varName1.find("piK") != std::string::npos)
							varName2 = ("CrossFeed_"+(it_cross->first)+"_as_Kpi"+(*it_KS)+"_"+(*it_year)+"_pdf_"+(*itVar));
						std::string funcName;
						if (it_cross->second.find("piK") != std::string::npos)
							funcName = ("CrossFeed_"+(it_cross->first)+"_as_Kpi"+(*it_KS)+"_"+(*it_year)+"_pdf_"+(*itVar)+"_function");
						else
							funcName = ("CrossFeed_"+(it_cross->first)+"_as_"+(it_cross->second)+(*it_KS)+"_"+(*it_year)+"_pdf_"+(*itVar)+"_function");
						double varVal = fitter.getParameterValue(varName2.c_str());
						double funcVal = varVal;
						if (fitter.getWS()->function(funcName.c_str()) != NULL)
							funcVal = fitter.getWS()->function(funcName.c_str())->getVal();
						fitter.setParameterValue(varName1.c_str()				       
												 ,funcVal
												 );
						std::cout 
							<< varName1 << " "
							<< varVal << " "
							<< funcVal
							<< std::endl;
					}
			}
		}
    }
	//	if (!relax)
		fitter.saveWS( (saveDir+"WS/MC-CrossFeed-WS-"+constraints+"-"+mcOrigin+"-"+selectionType+protonPar+".root").c_str() );
		//	else
		//		fitter.saveWS( (saveDir+"WS/MC-CrossFeed-WS-"+constraints+"-"+mcOrigin+"-"+selectionType+"-Relax-"+relaxShift_str+protonPar+".root").c_str() );
	
    return 0;
}
