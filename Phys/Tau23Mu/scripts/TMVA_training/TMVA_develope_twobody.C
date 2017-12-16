// @(#)root/tmva $Id: TMVAClassification.C 38895 2011-04-18 11:59:54Z evt $
/**********************************************************************************
 * Project   : TMVA - a ROOT-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Root Macro: TMVAClassification                                                 *
 *                                                                                *
 * This macro provides examples for the training and testing of the               *
 * TMVA classifiers.                                                              *
 *                                                                                *
 * As input data is used a toy-MC sample consisting of four Gaussian-distributed  *
 * and linearly correlated input variables.                                       *
 *                                                                                *
 * The methods to be used can be switched on and off by means of booleans, or     *
 * via the prompt command, for example:                                           *
 *                                                                                *
 *    root -l ./TMVAClassification.C\(\"Fisher,Likelihood\"\)                     *
 *                                                                                *
 * (note that the backslashes are mandatory)                                      *
 * If no method given, a default set of classifiers is used.                      *
 *                                                                                *
 * The output file "TMVA.root" can be analysed with the use of dedicated          *
 * macros (simply say: root -l <macro.C>), which can be conveniently              *
 * invoked through a GUI that will appear at the end of the run of this macro.    *
 * Launch the GUI via the command:                                                *
 *                                                                                *
 *    root -l ./TMVAGui.C                                                         *
 *                                                                                *
 **********************************************************************************/

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVAGui.C"
#include "TMVA/MethodBase.h"


#if not defined(__CINT__) || defined(__MAKECINT__)
// needs to be included when makecint runs (ACLIC)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#endif

void TMVACC( TString myMethodList = "" , int varset = 0xFFFFFF)
{
   // The explicit loading of the shared libTMVA is done in TMVAlogon.C, defined in .rootrc
   // if you use your private .rootrc, or run from a different directory, please copy the
   // corresponding lines from .rootrc

   // methods to be processed can be given as an argument; use format:
   //
   // mylinux~> root -l TMVAClassification.C\(\"myMethod1,myMethod2,myMethod3\"\)
   //
   // if you like to use a method via the plugin mechanism, we recommend using
   //
   // mylinux~> root -l TMVAClassification.C\(\"P_myMethod\"\)
   // (an example is given for using the BDT as plugin (see below),
   // but of course the real application is when you write your own
   // method based)

   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();

   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   // --- Cut optimisation
   Use["Cuts"]            = 1;
   Use["CutsD"]           = 0;
   Use["CutsPCA"]         = 0;
   Use["CutsGA"]          = 0;
   Use["CutsSA"]          = 0;
   // 
   // --- 1-dimensional likelihood ("naive Bayes estimator")
   Use["Likelihood"]      = 0;
   Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
   Use["LikelihoodPCA"]   = 1; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
   Use["LikelihoodKDE"]   = 0;
   Use["LikelihoodMIX"]   = 0;
   //
   // --- Mutidimensional likelihood and Nearest-Neighbour methods
   Use["PDERS"]           = 0;
   Use["PDERSD"]          = 0;
   Use["PDERSPCA"]        = 0;
   Use["PDEFoam"]         = 0;
   Use["PDEFoamBoost"]    = 0; // uses generalised MVA method boosting
   Use["KNN"]             = 0; // k-nearest neighbour method
   //
   // --- Linear Discriminant Analysis
   Use["LD"]              = 0; // Linear Discriminant identical to Fisher
   Use["Fisher"]          = 1;
   Use["FisherG"]         = 0;
   Use["BoostedFisher"]   = 0; // uses generalised MVA method boosting
   Use["HMatrix"]         = 0;
   //
   // --- Function Discriminant analysis
   Use["FDA_GA"]          = 0; // minimisation of user-defined function using Genetics Algorithm
   Use["FDA_SA"]          = 0;
   Use["FDA_MC"]          = 0;
   Use["FDA_MT"]          = 0;
   Use["FDA_GAMT"]        = 0;
   Use["FDA_MCMT"]        = 0;
   //
   // --- Neural Networks (all are feed-forward Multilayer Perceptrons)
   Use["MLP"]             = 1; // Recommended ANN
   Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
   Use["MLPBNN"]          = 0; // Recommended ANN with BFGS training method and bayesian regulator
   Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
   Use["TMlpANN"]         = 0; // ROOT's own ANN
   //
   // --- Support Vector Machine 
   Use["SVM"]             = 0;
   // 
   // --- Boosted Decision Trees
   Use["BDT"]             = 1; // uses Adaptive Boost
   Use["BDTG"]            = 1; // uses Gradient Boost
   Use["BDTB"]            = 1; // uses Bagging
   Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
   Use["BDTF"]            = 1; // allow usage of fisher discriminant for node splitting 
   // 
   // --- Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
   Use["RuleFit"]         = 0;
   // ---------------------------------------------------------------

   std::cout << std::endl;
   std::cout << "==> Start TMVAClassification" << std::endl;

   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
      }
   }

   // --------------------------------------------------------------------------------------------------

   // --- Here the preparation phase begins

   // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
   TString outfileName( Form("twobody.root",varset) );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   // Create the factory object. Later you can choose the methods
   // whose performance you'd like to investigate. The factory is 
   // the only TMVA object you have to interact with
   //
   // The first argument is the base of the name of all the
   // weightfiles in the directory weight/
   //
   // The second argument is the output file for the training results
   // All TMVA output can be suppressed by removing the "!" (not) in
   // front of the "Silent" argument in the option string
   TMVA::Factory *factory = new TMVA::Factory( Form("twobody",varset), outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

   // If you wish to modify default settings
   // (please check "src/Config.h" to see all available global options)
   //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
   //    (TMVA::gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory";

   // Define the input variables that shall be used for the MVA training
   // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
   // [all types of expressions that can also be parsed by TTree::Draw( "expression" )]


//factory->AddVariable("RUNNING_EVENT_NUMBER");
//factory->AddVariable("runNumber");
//factory->AddVariable("eventNumber");
//factory->AddVariable("TCK");
//factory->AddVariable("Strip15And17");
//factory->AddVariable("cleaningcut");
//factory->AddVariable("jonpid");
//factory->AddVariable("jongeo");
//factory->AddVariable("NumberPV");
//factory->AddVariable("Ncandidates");
//factory->AddVariable("NbestTracks");

//factory->AddVariable("truetau");
//factory->AddVariable("particleid");
//factory->AddVariable("FlightDistance");
//factory->AddVariable("FlightDistanceError");
//factory->AddVariable("mass");
//factory->AddVariable("LifeTime");
//factory->AddVariable("IP");
//factory->AddVariable("IPSig");
//factory->AddVariable("VertexChi2");
//factory->AddVariable("dira");
//factory->AddVariable("pt");
//factory->AddVariable("BPVIPCHI2");
//factory->AddVariable("BPVLTIME225");
//factory->AddVariable("p0_IP");
//factory->AddVariable("p1_IP");
//factory->AddVariable("p2_IP");
//factory->AddVariable("p0_IPSig");
//factory->AddVariable("p1_IPSig");
//factory->AddVariable("p2_IPSig");
//factory->AddVariable("DOCAone");
//factory->AddVariable("DOCAtwo");
//factory->AddVariable("DOCAthree");
//factory->AddVariable("mass_p0p2");
//factory->AddVariable("mass_p1p2");
factory->AddVariable("Dalitz_m12");
factory->AddVariable("Dalitz_m23");
//factory->AddVariable("mass_p0p1");
//factory->AddVariable("IP_p0p2");
//factory->AddVariable("IP_p1p2");
//factory->AddVariable("mass_phihypo");
//factory->AddVariable("mass_k0k2");
//factory->AddVariable("mass_k1k2");
//factory->AddVariable("p0_BPVIPCHI2");
//factory->AddVariable("p1_BPVIPCHI2");
//factory->AddVariable("p2_BPVIPCHI2");
//factory->AddVariable("p0_pt");
//factory->AddVariable("p1_pt");
//factory->AddVariable("p2_pt");
//factory->AddVariable("p0_p");
//factory->AddVariable("p1_p");
//factory->AddVariable("p2_p");
//factory->AddVariable("p0_eta");
//factory->AddVariable("p1_eta");
//factory->AddVariable("p2_eta");
//factory->AddVariable("p0_phi");
//factory->AddVariable("p1_phi");
//factory->AddVariable("p2_phi");
//factory->AddVariable("p0_track_Chi2Dof");
//factory->AddVariable("p1_track_Chi2Dof");
//factory->AddVariable("p2_track_Chi2Dof");
//factory->AddVariable("p0_track_MatchChi2");
//factory->AddVariable("p1_track_MatchChi2");
//factory->AddVariable("p2_track_MatchChi2");
//factory->AddVariable("p0_cloneDist");
//factory->AddVariable("p1_cloneDist");
//factory->AddVariable("p2_cloneDist");
//factory->AddVariable("ptorderedp0_IPSig");
//factory->AddVariable("ptorderedp1_IPSig");
//factory->AddVariable("ptorderedp2_IPSig");
//factory->AddVariable("ptorderedp0_pt");
//factory->AddVariable("ptorderedp1_pt");
//factory->AddVariable("ptorderedp2_pt");
//factory->AddVariable("ptorderedp0_p0_track_Chi2Dof");
//factory->AddVariable("ptorderedp1_p1_track_Chi2Dof");
//factory->AddVariable("ptorderedp2_p2_track_Chi2Dof");
//factory->AddVariable("p0_isMuon");
//factory->AddVariable("p1_isMuon");
//factory->AddVariable("p2_isMuon");
//factory->AddVariable("p0_PIDmupi");
//factory->AddVariable("p1_PIDmupi");
//factory->AddVariable("p2_PIDmupi");
//factory->AddVariable("p0_PIDmuk");
//factory->AddVariable("p1_PIDmuk");
//factory->AddVariable("p2_PIDmuk");
//factory->AddVariable("p0_NShared");
//factory->AddVariable("p1_NShared");
//factory->AddVariable("p2_NShared");
//factory->AddVariable("p0_MuLL");
//factory->AddVariable("p1_MuLL");
//factory->AddVariable("p2_MuLL");
//factory->AddVariable("p0_MuDLL");
//factory->AddVariable("p1_MuDLL");
//factory->AddVariable("p2_MuDLL");
//factory->AddVariable("p0_MuBkg");
//factory->AddVariable("p0_richMU");
//factory->AddVariable("p0_richK");
//factory->AddVariable("p0_richPI");
//factory->AddVariable("p0_ecalMU");
//factory->AddVariable("p0_hcalMU");
//factory->AddVariable("p1_MuBkg");
//factory->AddVariable("p1_richMU");
//factory->AddVariable("p1_richK");
//factory->AddVariable("p1_richPI");
//factory->AddVariable("p1_ecalMU");
//factory->AddVariable("p1_hcalMU");
//factory->AddVariable("p2_MuBkg");
//factory->AddVariable("p2_richMU");
//factory->AddVariable("p2_richK");
//factory->AddVariable("p2_richPI");
//factory->AddVariable("p2_ecalMU");
//factory->AddVariable("p2_hcalMU");
//factory->AddVariable("ptorderedp0_PIDmupi");
//factory->AddVariable("ptorderedp1_PIDmupi");
//factory->AddVariable("ptorderedp2_PIDmupi");
//factory->AddVariable("ptorderedp0_PIDmuk");
//factory->AddVariable("ptorderedp1_PIDmuk");
//factory->AddVariable("ptorderedp2_PIDmuk");
//factory->AddVariable("isolationa");
//factory->AddVariable("isolationb");
//factory->AddVariable("isolationc");
//factory->AddVariable("isolationd");
//factory->AddVariable("isolatione");
//factory->AddVariable("isolationf");
//factory->AddVariable("iso");
//factory->AddVariable("CDF1");
//factory->AddVariable("CDF2");
//factory->AddVariable("CDF3");
//factory->AddVariable("PIDMVA");
//factory->AddVariable("noptPIDMVA");
//factory->AddVariable("GeoMVA");
//factory->AddVariable("p0_singlePID");
//factory->AddVariable("p1_singlePID");
//factory->AddVariable("p2_singlePID");
//factory->AddVariable("BCK");
//factory->AddVariable("tauproduction");
//factory->AddVariable("productionweight");
//factory->AddVariable("productionweighterror");
//factory->AddVariable("production");
//factory->AddVariable("EventHash");
//factory->AddVariable("p0_ANNghost");
//factory->AddVariable("p0_ANNpion");
//factory->AddVariable("p0_ANNmuon");
//factory->AddVariable("p0_ANNkaon");
//factory->AddVariable("p0_ANNproton");
//factory->AddVariable("p0_ANNelectron");
//factory->AddVariable("p0_Tchi");
//factory->AddVariable("p0_Vchi");
//factory->AddVariable("p0_Tdof");
//factory->AddVariable("p0_Vdof");
//factory->AddVariable("p0_observedV");
//factory->AddVariable("p0_observedT");
//factory->AddVariable("p0_observedTT");
//factory->AddVariable("p0_expectedV");
//factory->AddVariable("p0_expectedT");
//factory->AddVariable("p0_expectedTT");
//factory->AddVariable("p1_ANNghost");
//factory->AddVariable("p1_ANNpion");
//factory->AddVariable("p1_ANNmuon");
//factory->AddVariable("p1_ANNkaon");
//factory->AddVariable("p1_ANNproton");
//factory->AddVariable("p1_ANNelectron");
//factory->AddVariable("p1_Tchi");
//factory->AddVariable("p1_Vchi");
//factory->AddVariable("p1_Tdof");
//factory->AddVariable("p1_Vdof");
//factory->AddVariable("p1_observedV");
//factory->AddVariable("p1_observedT");
//factory->AddVariable("p1_observedTT");
//factory->AddVariable("p1_expectedV");
//factory->AddVariable("p1_expectedT");
//factory->AddVariable("p1_expectedTT");
//factory->AddVariable("p2_ANNghost");
//factory->AddVariable("p2_ANNpion");
//factory->AddVariable("p2_ANNmuon");
//factory->AddVariable("p2_ANNkaon");
//factory->AddVariable("p2_ANNproton");
//factory->AddVariable("p2_ANNelectron");
//factory->AddVariable("p2_Tchi");
//factory->AddVariable("p2_Vchi");
//factory->AddVariable("p2_Tdof");
//factory->AddVariable("p2_Vdof");
//factory->AddVariable("p2_observedV");
//factory->AddVariable("p2_observedT");
//factory->AddVariable("p2_observedTT");
//factory->AddVariable("p2_expectedV");
//factory->AddVariable("p2_expectedT");
//factory->AddVariable("p2_expectedTT");

   // You can add so-called "Spectator variables", which are not used in the MVA training,
   // but will appear in the final "TestTree" produced by TMVA. This TestTree will contain the
   // input variables, the response values of all trained MVAs, and the spectator variables

   // Read training and test data
   // (it is also possible to use ASCII format as input -> see TMVA Users Guide)
   TString fname = "/tmp/sig.root";
   TString bname = "/tmp/bkg.root";
   TString Bbname = "/tmp/Bbkg.root";
   TString Cbname = "/tmp/Cbkg.root";
   
   TFile *inputs = TFile::Open( fname );
   TFile *inputb = TFile::Open( bname );
   TFile *inputbB = TFile::Open( Bbname );
   TFile *inputbC = TFile::Open( Cbname );
   
   std::cout << "--- TMVAClassification       : Using input file: " << inputs->GetName() << std::endl;
   
   // --- Register the training and test trees

   TTree *signal     = (TTree*)inputs->Get("Tau23Mu");
   TTree *background = (TTree*)inputb->Get("Tau23Mu");
   TTree *Cbackground     = (TTree*)inputbC->Get("Tau23Mu");
   TTree *Bbackground     = (TTree*)inputbB->Get("Tau23Mu");
   
   // global event weights per tree (see below for setting event-wise weights)
   Double_t signalWeight     = 1.0;
   Double_t BbackgroundWeight = 10./9.1;
   Double_t CbackgroundWeight = 10./4.4;
   Double_t backgroundWeight = 10./2000.;
   
   // You can add an arbitrary number of signal or background trees
   factory->AddSignalTree    ( signal,     signalWeight     );
   factory->AddBackgroundTree( Bbackground, BbackgroundWeight );
   factory->AddBackgroundTree( Cbackground, CbackgroundWeight );
   factory->AddBackgroundTree( background, backgroundWeight );
   
   // To give different trees for training and testing, do as follows:
   //    factory->AddSignalTree( signalTrainingTree, signalTrainWeight, "Training" );
   //    factory->AddSignalTree( signalTestTree,     signalTestWeight,  "Test" );
   
   // Use the following code instead of the above two or four lines to add signal and background
   // training and test events "by hand"
   // NOTE that in this case one should not give expressions (such as "var1+var2") in the input
   //      variable definition, but simply compute the expression before adding the event
   //
   //     // --- begin ----------------------------------------------------------
   //     std::vector<Double_t> vars( 4 ); // vector has size of number of input variables
   //     Float_t  treevars[4], weight;
   //     
   //     // Signal
   //     for (UInt_t ivar=0; ivar<4; ivar++) signal->SetBranchAddress( Form( "var%i", ivar+1 ), &(treevars[ivar]) );
   //     for (UInt_t i=0; i<signal->GetEntries(); i++) {
   //        signal->GetEntry(i);
   //        for (UInt_t ivar=0; ivar<4; ivar++) vars[ivar] = treevars[ivar];
   //        // add training and test events; here: first half is training, second is testing
   //        // note that the weight can also be event-wise
   //        if (i < signal->GetEntries()/2.0) factory->AddSignalTrainingEvent( vars, signalWeight );
   //        else                              factory->AddSignalTestEvent    ( vars, signalWeight );
   //     }
   //   
   //     // Background (has event weights)
   //     background->SetBranchAddress( "weight", &weight );
   //     for (UInt_t ivar=0; ivar<4; ivar++) background->SetBranchAddress( Form( "var%i", ivar+1 ), &(treevars[ivar]) );
   //     for (UInt_t i=0; i<background->GetEntries(); i++) {
   //        background->GetEntry(i);
   //        for (UInt_t ivar=0; ivar<4; ivar++) vars[ivar] = treevars[ivar];
   //        // add training and test events; here: first half is training, second is testing
   //        // note that the weight can also be event-wise
   //        if (i < background->GetEntries()/2) factory->AddBackgroundTrainingEvent( vars, backgroundWeight*weight );
   //        else                                factory->AddBackgroundTestEvent    ( vars, backgroundWeight*weight );
   //     }
         // --- end ------------------------------------------------------------
   //
   // --- end of tree registration 

   // Set individual event weights (the variables must exist in the original TTree)
   //    for signal    : factory->SetSignalWeightExpression    ("weight1*weight2");
   //    for background: factory->SetBackgroundWeightExpression("weight1*weight2");
   factory->SetBackgroundWeightExpression( "1" );
   factory->SetSignalWeightExpression("productionweightMC11v2");

   // Apply additional cuts on the signal and background samples (can be different)
//   TCut mycuts = "cleaningcut&&L0Dec&&Hlt1Dec&&Hlt2Dec&&truetau==15"; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
//   TCut mycutb = "cleaningcut&&L0Dec&&Hlt1Dec&&Hlt2Dec"; // for example: TCut mycutb = "abs(var1)<0.5";
   
     TCut mycuts;
     mycuts = "L0Dec&&Hlt1Dec&&Hlt2Dec&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99&&truetau==15";
     TCut mycutb = "L0Dec&&Hlt1Dec&&Hlt2Dec&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99";
     //TCut mycutb = "(abs(EventHash%2)==1)&&L0Dec&&Hlt1Dec&&Hlt2Dec&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99";
   


   // Tell the factory how to use the training and testing events
   //
   // If no numbers of events are given, half of the events in the tree are used 
   // for training, and the other half for testing:
   //    factory->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );
   // To also specify the number of testing events, use:
   //    factory->PrepareTrainingAndTestTree( mycut,
   //                                         "NSigTrain=3000:NBkgTrain=3000:NSigTest=3000:NBkgTest=3000:SplitMode=Random:!V" );
   factory->PrepareTrainingAndTestTree( mycuts, mycutb,
                                        "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:SplitSeed=500:!V" );

   // ---- Book MVA methods
   //
   // Please lookup the various method configuration options in the corresponding cxx files, eg:
   // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
   // it is possible to preset ranges in the option string in which the cut optimisation should be done:
   // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable

   std::vector<TMVA::MethodBase*> mypointer;
   // Cut optimisation
   if (Use["Cuts"])
      factory->BookMethod( TMVA::Types::kCuts, "Cuts",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );

   if (Use["CutsD"])
      factory->BookMethod( TMVA::Types::kCuts, "CutsD",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=Decorrelate" );

   if (Use["CutsPCA"])
      factory->BookMethod( TMVA::Types::kCuts, "CutsPCA",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=PCA" );

   if (Use["CutsGA"])
      factory->BookMethod( TMVA::Types::kCuts, "CutsGA",
                           "H:!V:FitMethod=GA:CutRangeMin[0]=-10:CutRangeMax[0]=10:VarProp[1]=FMax:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95" );

   if (Use["CutsSA"])
      factory->BookMethod( TMVA::Types::kCuts, "CutsSA",
                           "!H:!V:FitMethod=SA:EffSel:MaxCalls=150000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );

   // Likelihood ("naive Bayes estimator")
   if (Use["Likelihood"])
      factory->BookMethod( TMVA::Types::kLikelihood, "Likelihood",
                           "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );

   // Decorrelated likelihood
   if (Use["LikelihoodD"])
      factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodD",
                           "!H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=Decorrelate" );

   // PCA-transformed likelihood
   if (Use["LikelihoodPCA"])
      factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodPCA",
                           "!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=PCA" ); 

   // Use a kernel density estimator to approximate the PDFs
   if (Use["LikelihoodKDE"])
      factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodKDE",
                           "!H:!V:!TransformOutput:PDFInterpol=KDE:KDEtype=Gauss:KDEiter=Adaptive:KDEFineFactor=0.3:KDEborder=None:NAvEvtPerBin=50" ); 

   // Use a variable-dependent mix of splines and kernel density estimator
   if (Use["LikelihoodMIX"])
      factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodMIX",
                           "!H:!V:!TransformOutput:PDFInterpolSig[0]=KDE:PDFInterpolBkg[0]=KDE:PDFInterpolSig[1]=KDE:PDFInterpolBkg[1]=KDE:PDFInterpolSig[2]=Spline2:PDFInterpolBkg[2]=Spline2:PDFInterpolSig[3]=Spline2:PDFInterpolBkg[3]=Spline2:KDEtype=Gauss:KDEiter=Nonadaptive:KDEborder=None:NAvEvtPerBin=50" ); 

   // Test the multi-dimensional probability density estimator
   // here are the options strings for the MinMax and RMS methods, respectively:
   //      "!H:!V:VolumeRangeMode=MinMax:DeltaFrac=0.2:KernelEstimator=Gauss:GaussSigma=0.3" );
   //      "!H:!V:VolumeRangeMode=RMS:DeltaFrac=3:KernelEstimator=Gauss:GaussSigma=0.3" );
   if (Use["PDERS"])
      factory->BookMethod( TMVA::Types::kPDERS, "PDERS",
                           "!H:!V:NormTree=T:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600" );

   if (Use["PDERSD"])
      factory->BookMethod( TMVA::Types::kPDERS, "PDERSD",
                           "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=Decorrelate" );

   if (Use["PDERSPCA"])
      factory->BookMethod( TMVA::Types::kPDERS, "PDERSPCA",
                           "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=PCA" );

   // Multi-dimensional likelihood estimator using self-adapting phase-space binning
   if (Use["PDEFoam"])
      factory->BookMethod( TMVA::Types::kPDEFoam, "PDEFoam",
                           "!H:!V:SigBgSeparate=F:TailCut=0.001:VolFrac=0.0666:nActiveCells=500:nSampl=2000:nBin=5:Nmin=100:Kernel=None:Compress=T" );

   if (Use["PDEFoamBoost"])
      factory->BookMethod( TMVA::Types::kPDEFoam, "PDEFoamBoost",
                           "!H:!V:Boost_Num=30:Boost_Transform=linear:SigBgSeparate=F:MaxDepth=4:UseYesNoCell=T:DTLogic=MisClassificationError:FillFoamWithOrigWeights=F:TailCut=0:nActiveCells=500:nBin=20:Nmin=400:Kernel=None:Compress=T" );

   // K-Nearest Neighbour classifier (KNN)
   if (Use["KNN"])
      factory->BookMethod( TMVA::Types::kKNN, "KNN",
                           "H:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim" );

   // H-Matrix (chi2-squared) method
   if (Use["HMatrix"])
      factory->BookMethod( TMVA::Types::kHMatrix, "HMatrix", "!H:!V:VarTransform=None" );

   // Linear discriminant (same as Fisher discriminant)
   if (Use["LD"])
      factory->BookMethod( TMVA::Types::kLD, "LD", "H:!V:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );

   // Fisher discriminant (same as LD)
   if (Use["Fisher"])
      mypointer.push_back(factory->BookMethod( TMVA::Types::kFisher, "Fisher", "!H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" ));

   // Fisher with Gauss-transformed input variables
   if (Use["FisherG"])
      factory->BookMethod( TMVA::Types::kFisher, "FisherG", "H:!V:VarTransform=Gauss" );

   // Composite classifier: ensemble (tree) of boosted Fisher classifiers
   if (Use["BoostedFisher"])
      factory->BookMethod( TMVA::Types::kFisher, "BoostedFisher", 
                           "H:!V:Boost_Num=20:Boost_Transform=log:Boost_Type=AdaBoost:Boost_AdaBoostBeta=0.2:!Boost_DetailedMonitoring" );

   // Function discrimination analysis (FDA) -- test of various fitters - the recommended one is Minuit (or GA or SA)
   if (Use["FDA_MC"])
      factory->BookMethod( TMVA::Types::kFDA, "FDA_MC",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:SampleSize=100000:Sigma=0.1" );

   if (Use["FDA_GA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
      factory->BookMethod( TMVA::Types::kFDA, "FDA_GA",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:PopSize=300:Cycles=3:Steps=20:Trim=True:SaveBestGen=1" );

   if (Use["FDA_SA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
      factory->BookMethod( TMVA::Types::kFDA, "FDA_SA",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=SA:MaxCalls=15000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );

   if (Use["FDA_MT"])
      factory->BookMethod( TMVA::Types::kFDA, "FDA_MT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=2:UseImprove:UseMinos:SetBatch" );

   if (Use["FDA_GAMT"])
      factory->BookMethod( TMVA::Types::kFDA, "FDA_GAMT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:Cycles=1:PopSize=5:Steps=5:Trim" );

   if (Use["FDA_MCMT"])
      factory->BookMethod( TMVA::Types::kFDA, "FDA_MCMT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:SampleSize=20" );

   // TMVA ANN: MLP (recommended ANN) -- all ANNs in TMVA are Multilayer Perceptrons
   if (Use["MLP"])
      mypointer.push_back(factory->BookMethod( TMVA::Types::kMLP, "MLP", "!H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator" ));

   if (Use["MLPBFGS"])
      factory->BookMethod( TMVA::Types::kMLP, "MLPBFGS", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:!UseRegulator" );

   if (Use["MLPBNN"])
      factory->BookMethod( TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator" ); // BFGS training with bayesian regulators

   // CF(Clermont-Ferrand)ANN
   if (Use["CFMlpANN"])
      factory->BookMethod( TMVA::Types::kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=2000:HiddenLayers=N+1,N"  ); // n_cycles:#nodes:#nodes:...  

   // Tmlp(Root)ANN
   if (Use["TMlpANN"])
      factory->BookMethod( TMVA::Types::kTMlpANN, "TMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N:LearningMethod=BFGS:ValidationFraction=0.3"  ); // n_cycles:#nodes:#nodes:...

   // Support Vector Machine
   if (Use["SVM"])
      factory->BookMethod( TMVA::Types::kSVM, "SVM", "Gamma=0.25:Tol=0.001:VarTransform=Norm" );

   // Boosted Decision Trees
   if (Use["BDTG"]) // Gradient Boost
      factory->BookMethod( TMVA::Types::kBDT, "BDTG",
                           "!H:!V:NTrees=525:BoostType=Grad:Shrinkage=0.1625:UseBaggedGrad:GradBaggingFraction=0.5:nEventsMin=20:MaxDepth=8:NNodesMax=8" );
/*--- OptimizeConfigParamete...: For BDTG the optimized Parameters are:
 * --- OptimizeConfigParamete...: MaxDepth = 8
 *  --- OptimizeConfigParamete...: NTrees = 525
 *  --- OptimizeConfigParamete...: NodeMinEvents = 20
 *  --- OptimizeConfigParamete...: Shrinkage = 0.1625
 
*/

   if (Use["BDT"])  // Adaptive Boost
      factory->BookMethod( TMVA::Types::kBDT, "BDT",
                           "!H:!V:NTrees=288:nEventsMin=20:MaxDepth=7:BoostType=AdaBoost:AdaBoostBeta=1.5:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
/*--- OptimizeConfigParamete...: For BDT the optimized Parameters are:
 * --- OptimizeConfigParamete...: AdaBoostBeta = 1.5
 *  --- OptimizeConfigParamete...: MaxDepth = 7
 *  --- OptimizeConfigParamete...: NTrees = 287.5
 *  --- OptimizeConfigParamete...: NodeMinEvents = 20
 *  */
   if (Use["BDTB"]) // Bagging
      factory->BookMethod( TMVA::Types::kBDT, "BDTB",
                           "!H:!V:NTrees=50:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20:MaxDepth=3:nEventsMin=1280:PruneMethod=NoPruning" );
/*--- OptimizeConfigParamete...: For BDTB the optimized Parameters are:
 * --- OptimizeConfigParamete...: MaxDepth = 3
 *  --- OptimizeConfigParamete...: NTrees = 50
 *  --- OptimizeConfigParamete...: NodeMinEvents = 1280
 *  */

   if (Use["BDTD"]) // Decorrelation + Adaptive Boost
      factory->BookMethod( TMVA::Types::kBDT, "BDTD",
                           "!H:!V:NTrees=50:nEventsMin=20:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning:VarTransform=Decorrelate" );
/*--
-
*/

   if (Use["BDTF"])  // Allow Using Fisher discriminant in node splitting for (strong) linearly correlated variables
      factory->BookMethod( TMVA::Types::kBDT, "BDTMitFisher",
                           "!H:!V:NTrees=50:nEventsMin=150:UseFisherCuts:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );

   // RuleFit -- TMVA implementation of Friedman's method
   if (Use["RuleFit"])
      factory->BookMethod( TMVA::Types::kRuleFit, "RuleFit",
                           "H:!V:RuleFitModule=RFTMVA:Model=ModRuleLinear:MinImp=0.001:RuleMinDist=0.001:NTrees=20:fEventsMin=0.01:fEventsMax=0.5:GDTau=-1.0:GDTauPrec=0.01:GDStep=0.01:GDNSteps=10000:GDErrScale=1.02" );

   // For an example of the category classifier usage, see: TMVAClassificationCategory

   // --------------------------------------------------------------------------------------------------

   // ---- Now you can optimize the setting (configuration) of the MVAs using the set of training events

    //factory->OptimizeAllMethods("SigEffAtBkgEff001","FitGA");
   // factory->OptimizeAllMethods("ROCIntegral","GA");

   // --------------------------------------------------------------------------------------------------

   // ---- Now you can tell the factory to train, test, and evaluate the MVAs

   // Train MVAs using the set of training events
   factory->TrainAllMethods();

   // ---- Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // ----- Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();

   // --------------------------------------------------------------
         Double_t err;

   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;


   delete factory;

   // Launch the GUI for the root macros
//   if (!gROOT->IsBatch()) TMVAGui( outfileName );
}


void TMVA_develope_twobody() {
  TMVACC();
  int varset = 0000;
  TMVAGui(Form("twobody.root",varset));
}
