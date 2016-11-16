/////////////////////////////////////////////////////
//                                                 //
// Creates the BDT for the Ks0 -> mu+ mu- analysis //
//                                                 //
// Author: Miguel Ramos Pernas                     //
// e-mail: miguel.ramos.pernas@cern.ch             //
//                                                 //
/////////////////////////////////////////////////////

//#include "Utils.h"

#include "TROOT.h"
#include "TMVA/Factory.h"
#include "TMVA/Config.h"
#include "TMVA/MethodBase.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

#include "TFile.h"
#include "TLeaf.h"
#include "TObjString.h"
#include "TRandom3.h"
#include "TTree.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// Here the variables to be used are defined
#include "VarSetDefinition.h"

// Path to the directory where the weights will be saved
//const std::string WEIGHT_FOLDER = "/afs/cern.ch/user/m/mramospe/Work/KS0mumu/BDTmaking/weights/";
const std::string WEIGHT_FOLDER = "/afs/cern.ch/user/m/mramospe/eos/lhcb/user/m/mramospe/KS0mumu/BDT/Training/weights";

// This is the fraction of events that will be used for training
const double TRAIN_RATIO = 0.7;

// This is the maximum amount of events to run over
const Long64_t MAXNEVTS = 10000000;

// These are the weights for signal and background
const double BKG_WEIGHT = 1.;
const double SIG_WEIGHT = 1.;

// These are some extra cuts that can be applied before the training process
const std::string BKG_CUTS = "";
const std::string SIG_CUTS = "";
// --------------------------------------------------------------------------------

// The different methods are defined here, with the options to be used on each case
void BookMethods( TMVA::Factory &factory, const std::map<std::string, bool> &mp ) {
  // Boosted Decision trees, BEFORE THEY HAD "nCuts=-1" instead of "nCuts=20" and no "IgnoreNegWeightsInTraining" PRESENT
  if ( mp.at( "BDT" ) )
    factory.BookMethod( TMVA::Types::kBDT, "BDT", "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );
  if ( mp.at( "BDTB" ) )
    factory.BookMethod( TMVA::Types::kBDT, "BDTB", "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20" );
  if ( mp.at( "BDTD" ) )
    factory.BookMethod( TMVA::Types::kBDT, "BDTD", "!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate" );
  if ( mp.at( "BDTF") )
    factory.BookMethod( TMVA::Types::kBDT, "BDTF", "!H:!V:NTrees=50:MinNodeSize=2.5%:UseFisherCuts:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=200" );
   if ( mp.at( "BDTGDs01de3nt1000M15B08" ) )
     factory.BookMethod( TMVA::Types::kBDT, "BDTGDs01de3nt1000M15B08", "!H:!V:NTrees=1000:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost=True:BaggedSampleFraction=0.8:nCuts=200:MaxDepth=3:VarTransform=Decorrelate:NegWeightTreatment=IgnoreNegWeightsInTraining " );
   if ( mp.at( "BDTGDs01de4nt700M15B05" ) )
     factory.BookMethod( TMVA::Types::kBDT, "BDTGDs01de4nt700M15B05", "!H:!V:NTrees=700:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost=True:BaggedSampleFraction=0.5:nCuts=200:MaxDepth=4:VarTransform=Decorrelate:NegWeightTreatment=IgnoreNegWeightsInTraining " );
   if ( mp.at( "BDTb025de4nt850M1" ) )
     factory.BookMethod( TMVA::Types::kBDT, "BDTb025de4nt850M1", "!H:!V:NTrees=850:MinNodeSize=1%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.25:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=200" );
   if ( mp.at( "BDTb05de4nt850M1" ) )
     factory.BookMethod( TMVA::Types::kBDT, "BDTb05de4nt850M1", "!H:!V:NTrees=850:MinNodeSize=1%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=200" );
   if ( mp.at( "BDTb025de4nt1000M1" ) )
     factory.BookMethod( TMVA::Types::kBDT, "BDTb025de4nt1000M1", "!H:!V:NTrees=1000:MinNodeSize=1%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.25:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=200" );
   if ( mp.at( "BDTb05de4nt1000M1" ) )
     factory.BookMethod( TMVA::Types::kBDT, "BDTb05de4nt1000M1", "!H:!V:NTrees=1000:MinNodeSize=1%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=200" );

  // K-Nearest Neighbour classifier (KNN) 
  if ( mp.at( "KNN20T" ))
    factory.BookMethod( TMVA::Types::kKNN, "KNN20T", "!H:!V:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:Trim" );
  if ( mp.at( "KNN30T" ))
    factory.BookMethod( TMVA::Types::kKNN, "KNN30T", "!H:!V:nkNN=30:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:Trim" );
  
  // BFGS training with bayesian regulators
  if ( mp.at( "MLPBNN" ))
    factory.BookMethod( TMVA::Types::kMLP, "MLPBNN", "!H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator" );
}

// In this function the variables to be used are defined. By default the variables set index is set to -1 to prevent errors.
void DefineVariables( std::map<std::string, TLeaf*> &vec, std::vector<std::string> &order, const int &glstatus,  const int &varset = -1 ) {

  if ( varset < 0 ) {
    std::cerr << "ERROR: The index of the variable set must be smaller than 4" << std::endl;
    return;
  }
  
  if ( glstatus ) {
    size_t nvars = MAIN_VARIABLES.size() + ( varset == 0 ? 2 : varset == 1 ? 3 : 4 );
    for ( unsigned short int i = 0; i < nvars; ++i ) {
      order.push_back( "GLmvas" + std::to_string( i ) + '.' );
      if ( glstatus == 2 )
	order.push_back( "GLmvan" + std::to_string( i ) + '.' );
    }
    if ( varset < 2 )
      order.push_back( "KS0_isInMatter" );
  }
  else {

    if ( varset == 0 )
      order = VARSET_0;
    else if ( varset == 1 )
      order = VARSET_1;
    else if ( varset == 2 )
      order = VARSET_2;
    else if ( varset == 3 )
      order = VARSET_3;
    
    order.insert( order.end(), MAIN_VARIABLES.begin(), MAIN_VARIABLES.end() );
  }
  order.insert( order.end(), SPECTATORVARS.begin(), SPECTATORVARS.end() );

  for ( auto it = order.begin(); it != order.end(); ++it )
    vec[ *it ] = 0;
}

// In this function the methods to be used are defined
void DefineMethods( std::map<std::string, bool> &mp, const int &glstatus ) {
  mp[ "BDT" ]                     = false;
  mp[ "BDTB" ]                    = false;
  mp[ "BDTD" ]                    = false;
  mp[ "BDTF" ]                    = false;//
  mp[ "BDTGDs01de3nt1000M15B08" ] = false;//
  mp[ "BDTGDs01de4nt700M15B05" ]  = false;
  mp[ "BDTb025de4nt850M1" ]       = false;//
  mp[ "BDTb05de4nt850M1" ]        = false;//
  mp[ "BDTb025de4nt1000M1" ]      = true;
  mp[ "BDTb05de4nt1000M1" ]       = false;//
  mp[ "KNN20T" ]                  = false;
  mp[ "KNN30T" ]                  = false;
  mp[ "MLPBNN" ]                  = false;//

  // The GL makes the variables to have variance = 0, so this method
  // become useless
  if ( glstatus )
    mp[ "BDTF" ] = false;//
}

// Function to set the path to the leaves of the trees
void SetLeafPaths( TTree *tree, std::map<std::string, TLeaf*> &mp ) {
  for ( auto it = mp.begin(); it != mp.end(); ++it )
    it -> second = tree -> GetLeaf( it -> first.c_str() );
}

// Main function to study one configuration
void RunOneConfigProc( const std::string &triggercat, const int &glstatus, const int &varset ) {
  
  // Here the different trigger categories are defined. One can specify the category
  // here or specifying it when executing this code.
  std::vector<std::string> allowedCats = { "TisTisTos", "TosTos1Tos", "TosTos2Tos" };
  while ( std::find( allowedCats.begin(), allowedCats.end(), triggercat ) == allowedCats.end() ) {
    std::cout << "WARNING: Trigger category < " << triggercat << " > not known; skiping";
    return;
  }
  std::cout << "*** Using trigger category < " << triggercat << " > ***" << std::endl;
  if ( glstatus > 0 ) {
    std::cout << "*** GL VARIABLES < ENABLED > ***" << std::endl;
    if ( glstatus == 2 )
      std::cout << "*** USING ALL GL VARIABLES ***" << std::endl;
    else
      std::cout << "*** USING ONLY SIG GL VARIABLES ***" << std::endl;
  }
  else
    std::cout << "*** GL VARIABLES < DISABLED > ***" << std::endl;
  std::cout << "*** USING VARIABLE SET < " << varset << " >" << std::endl;

  // ----------------------------------------------------------------------------
  // Defines the input files

  std::string
    //proxypath = "/afs/cern.ch/work/m/mramospe/public/RootFiles/KS0mumu/Proxies/",
    //path      = "/afs/cern.ch/work/m/mramospe/public/RootFiles/KS0mumu/BDT/";
    proxypath = "/afs/cern.ch/user/m/mramospe/eos/lhcb/user/m/mramospe/KS0mumu/BDT/Proxies/",
    path      = "/afs/cern.ch/user/m/mramospe/eos/lhcb/user/m/mramospe/KS0mumu/BDT/Training/";
  
  TTree *sigTree, *bkgTree;
  if ( glstatus > 0 ) {
    TFile *sigfile, *bkgfile; 
    std::string flag = triggercat + "_VarSet" + std::to_string( varset );
    sigfile = TFile::Open( ( path + "GLdata/Ks0mumu_GL_SigTest_" + flag + ".root" ).c_str() );
    bkgfile = TFile::Open( ( path + "GLdata/Ks0mumu_GL_BkgTest_" + flag + ".root" ).c_str() );
    sigTree = (TTree*) sigfile -> Get( "T" );
    bkgTree = (TTree*) bkgfile -> Get( "T" );
  }
  else {
    TFile *inputFile = TFile::Open( ( proxypath + "Ks0mumu_Data2012_MuPtCutOff2500_Proxy_" + triggercat + ".root" ).c_str() );
    sigTree = (TTree*) inputFile -> Get( "KS0pipi" );
    bkgTree = (TTree*) inputFile -> Get( "Background" );
  }
  // ----------------------------------------------------------------------------
  
  // Calls the functions to define the variables and the methods
  std::map<std::string, TLeaf*> Variables;
  std::vector<std::string> VarOrder;
  DefineVariables( Variables, VarOrder, glstatus, varset );
  std::map<std::string, bool> Methods;
  DefineMethods( Methods, glstatus );

  // Enables only the variables to work with and sets the name of the factory
  std::string
    //ofilename   = path + "BDTfiles/MULTI/BDTClassification_" + triggercat,
    ofilename   = path + "BDTClassification_" + triggercat,
    factoryname = "Factory_" + triggercat,
    factoryopts = "!V:!Silent:Color:!DrawProgressBar:Transformations=I:AnalysisType=Classification";
  sigTree -> SetBranchStatus( "*", false );
  bkgTree -> SetBranchStatus( "*", false );
  for ( auto it = VarOrder.begin(); it != VarOrder.end(); ++it ) {
    sigTree -> SetBranchStatus( it -> c_str(), true );
    bkgTree -> SetBranchStatus( it -> c_str(), true );
  }

  // Adds the corresponding flags given the GL status and the set of variables
  AddGLandVarSetFlags( factoryname, glstatus, varset );
  AddGLandVarSetFlags( ofilename  , glstatus, varset );

  // Defines the weights folder path
  std::cout << "*** Weights saved in directory: " << WEIGHT_FOLDER << " ***" << std::endl;
  TMVA::gConfig().GetIONames().fWeightFileDir = WEIGHT_FOLDER.c_str();

  // Creates the output file and the factory. If the variable is KS0_isInMatter is added as
  // and integer. The spectator variables are added at the end.
  ofilename += ".root";
  TFile *outputFile = TFile::Open( ofilename.c_str(), "RECREATE" );
  std::cout << "Created output file: " << ofilename << std::endl;
  TMVA::Factory Factory( factoryname.c_str(), outputFile, factoryopts.c_str() ); 
  size_t ilim = VarOrder.size() - SPECTATORVARS.size();
  for ( size_t i = 0; i < VarOrder.size(); ++i ) {
    std::string var = VarOrder[ i ];
    if ( i < ilim ) {
      std::cout << "--- Adding variable: " << var << std::endl;
      if ( var == "KS0_isInMatter" )
	Factory.AddVariable( var.c_str(), VARTITLES.at(var).c_str(), "",  'I' );
      else
	Factory.AddVariable( var.c_str(), VARTITLES.at(var).c_str(), "", 'F' );
    }
    else {
      std::cout << "--- Adding spectator: " << var << std::endl;
      Factory.AddSpectator( var.c_str(), VARTITLES.at(var).c_str(), "", 'F' );
    }
  }

  // Defines the training and testing samples
  std::vector<double> VarValues( VarOrder.size() );
  std::vector<double>::iterator itv;
  std::vector<std::string>::iterator itl;
  Long64_t counter;
  TRandom3 rndm;
  Long64_t nevtslim, maxentries;

  SetLeafPaths( sigTree, Variables );
  counter    = 0;
  maxentries = sigTree -> GetEntries() > MAXNEVTS ? MAXNEVTS : sigTree -> GetEntries();
  nevtslim   = TRAIN_RATIO*maxentries;
  std::cout << "--- Adding " << maxentries <<
    " signal events (" << sigTree -> GetEntries() << ")" << std::endl;
  for ( Long64_t ievt = 0; ievt < maxentries; ievt++ ) {
    sigTree -> GetEntry( ievt );
    itv = VarValues.begin();
    itl = VarOrder.begin();
    while ( itl != VarOrder.end() )
      *itv++ = Variables[ *itl++ ] -> GetValue();
    if ( counter < nevtslim ) {
      Factory.AddSignalTrainingEvent( VarValues, SIG_WEIGHT );
      ++counter;
    }
    else
      Factory.AddSignalTestEvent( VarValues, SIG_WEIGHT );
  }
  
  SetLeafPaths( bkgTree, Variables );
  counter    = 0;
  maxentries = bkgTree -> GetEntries() > MAXNEVTS ? MAXNEVTS : bkgTree -> GetEntries();
  nevtslim   = TRAIN_RATIO*bkgTree -> GetEntries();
  std::cout << "--- Adding " << maxentries <<
    " background events (" << bkgTree -> GetEntries() << ")" << std::endl;
  for ( Long64_t ievt = 0; ievt < maxentries; ievt++ ) {
    bkgTree -> GetEntry( ievt );
    itv = VarValues.begin();
    itl = VarOrder.begin();
    while ( itl != VarOrder.end() )
      *itv++ = Variables[ *itl++ ] -> GetValue();
    if ( counter < nevtslim ) {
      Factory.AddBackgroundTrainingEvent( VarValues, BKG_WEIGHT );
      ++counter;
    }
    else
      Factory.AddBackgroundTestEvent( VarValues, BKG_WEIGHT );
  }
  
  // Prepares the trees for training and testing
  Factory.PrepareTrainingAndTestTree( SIG_CUTS.c_str(), BKG_CUTS.c_str(), "" );

  // Defines the methods. Also sets the path to the weights file.
  BookMethods( Factory, Methods );
  
  // Train MVAs using the set of training events
  Factory.TrainAllMethods();
  // Evaluate all MVAs using the set of test events
  Factory.TestAllMethods();
  // Evaluate and compare performance of all configured MVAs
  Factory.EvaluateAllMethods();

  
  std::cout << "==> Wrote root file: " << outputFile -> GetName() << std::endl;
  std::cout << "==> TMVAClassification is done!" << std::endl;

  outputFile -> Close();
}

/* ================================ MAIN FUNCTION ================================ */
int main( int argc, const char *argv[] ) {

  if ( argc == 1 ) {
    std::cout << "*** No input parameters provided. Running over all different configurations. ***" << std::endl;
    std::vector<std::string> categories = { "TisTisTos", "TosTos1Tos", "TosTos2Tos" };
    for ( auto itc = categories.begin(); itc != categories.end(); ++itc )
      for ( size_t gl = 0; gl < 1; ++gl )
	for ( size_t iv = 0; iv < 4; ++iv )
	  RunOneConfigProc( *itc, gl, iv );
  }
  else {

    std::string tc = argv[ 1 ];
    /*
    std::string config( argv[ 1 ] );
    // Checks that the options are correctly given
    General::CheckParseOpts( config, { "TriggerCategory", "GLstatus", "VarSet" } );
   
    // Gets the trigger category
    std::string tc;
    General::ParseOpt( config, "TriggerCategory", tc );

    // Gets the status of the gl
    int glstatus;
    General::ParseOpt( config, "GLstatus", glstatus );

    // Gets the variable set to be used
    int varset;
    General::ParseOpt( config, "VarSet", varset );
    */
    
    RunOneConfigProc( tc, 0, 2 );
  }

  return 0;
}
