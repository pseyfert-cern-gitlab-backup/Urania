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

#include "createTable.h"

#if not defined(__CINT__) || defined(__MAKECINT__)
// needs to be included when makecint runs (ACLIC)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#endif

int gstep ;
//////////
// switches
//
// a)
//float lumi_C_error = -1.;
//float lumi_B_error = 1.;
// b)
//float lumi_C_error = 1.;
//float lumi_B_error = -1.;
//
float lumi_C_error = 0.;
float lumi_B_error = 0.;
bool restricttods = false;//true;
//
//////////

std::vector<std::pair<int,float> > Frank01eff;
std::vector<std::pair<int,float> > Frank01efferr;

std::vector<std::pair<int,float> > Lrank01eff;
std::vector<std::pair<int,float> > Lrank01efferr;

std::vector<std::pair<int,float> > Brank01eff;
std::vector<std::pair<int,float> > Brank01efferr;
std::vector<std::pair<int,float> > rankroc;
std::vector<std::pair<int,float> > ranksig;     

void TMVACC( TString myMethodList = "" , int varset = 0xFFFFFF)
{

  //---------------------------------------------------------------
  // This loads the library
  TMVA::Tools::Instance();

  // Default MVA methods to be trained + tested
  std::map<std::string,int> Use;

  // --- Cut optimisation
  Use["Cuts"]            = 0;
  Use["CutsD"]           = 0;
  Use["CutsPCA"]         = 0;
  Use["CutsGA"]          = 0;
  Use["CutsSA"]          = 0;
  // 
  // --- 1-dimensional likelihood ("naive Bayes estimator")
  Use["Likelihood"]      = 0;
  Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
  Use["LikelihoodPCA"]   = 0; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
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
  Use["Fisher"]          = 0;
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
  Use["MLPCJ"]           = 1; // Recommended ANN
  Use["MLPMSE"]          = 0; // Recommended ANN
  Use["MLPMSEBFGW"]      = 0; // Recommended ANN
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
  Use["BDTold"]             = 1; // uses Adaptive Boost
  Use["BDTG"]            = 0; // uses Gradient Boost
  Use["BDTB"]            = 0; // uses Bagging
  Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
  Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting 
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
  TString outfileName( Form("%x_MC12vsMC12.root",varset) );
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
  TMVA::Factory *factory = new TMVA::Factory( Form("GeoMVA2013_v3_%x",varset), outputFile,
      "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

  // If you wish to modify default settings
  // (please check "src/Config.h" to see all available global options)
  //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
  //    (TMVA::gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory";

  // Define the input variables that shall be used for the MVA training
  // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
  // [all types of expressions that can also be parsed by TTree::Draw( "expression" )]

  if (varset & 1 << 0)
    factory->AddVariable("FlightDistance");
  //factory->AddVariable("FlightDistanceError");
  if (varset & 1 << 1)
    factory->AddVariable("FlightDistance/FlightDistanceError");
  if (varset & 1 << 20)
    factory->AddVariable("TMath::Exp(-1000*LifeTime)","transformed decay time","1",'F');
  if (varset & 1 << 2)
    factory->AddVariable("IP");
  if (varset & 1 << 3)
    factory->AddVariable("IPSig","IP significance","1",'F');
  if (varset & 1 << 4)
    factory->AddVariable("VertexChi2","vertex #chi^{2}","1",'F');
  if (varset & 1 << 18)
    factory->AddVariable("acos(dira)","pointing angle","1",'F');
  if (varset & 1 << 19)
    factory->AddVariable("pt","p_{T}","[MeV/c]",'F');
  if (varset & 1 << 5)
    factory->AddVariable("p0_IP");
  if (varset & 1 << 6)
    factory->AddVariable("p1_IP");
  if (varset & 1 << 7)
    factory->AddVariable("p2_IP");
  if (varset & 1 << 8)
    factory->AddVariable("p0_IPSig");
  if (varset & 1 << 9)
    factory->AddVariable("p1_IPSig");
  if (varset & 1 << 10)
    factory->AddVariable("p2_IPSig");


  if (varset & 1 << 11)
    factory->AddVariable("Laura_SumBDT");
    
  if (varset & 1 << 12)
    factory->AddVariable("min(p0_IPSig,min(p1_IPSig,p2_IPSig))","min. #mu IP significance","1",'F');


  if (varset & 1 << 13)
    factory->AddVariable("DOCAone","DOCA (#mu 1 and 2)","mm",'F');
  if (varset & 1 << 14)
    factory->AddVariable("DOCAtwo","DOCA (#mu 2 and 3)","mm",'F');
  if (varset & 1 << 15)
    factory->AddVariable("DOCAthree","DOCA (#mu 1 and 3)","mm",'F');

  if (varset & 1 << 16)
    factory->AddVariable("max(max(DOCAone,DOCAtwo),DOCAthree)","max. DOCA","mm",'F');



  if (varset & 1 << 21)
    factory->AddVariable("isolationa");
  if (varset & 1 << 21)
    factory->AddVariable("isolationb");
  if (varset & 1 << 21)
    factory->AddVariable("isolationc");
  if (varset & 1 << 22)
    factory->AddVariable("isolationd");
  if (varset & 1 << 22)
    factory->AddVariable("isolatione");
  if (varset & 1 << 22)
    factory->AddVariable("isolationf");
  if (varset & 1 << 23)
    factory->AddVariable("iso","track isolation","1",'F');
  if (varset & 1 << 24)
    factory->AddVariable("CDF1");
  if (varset & 1 << 25)
    factory->AddVariable("CDF2");
  if (varset & 1 << 26)
    factory->AddVariable("CDF3","cone isolation","1",'F');

  //   factory->AddVariable("IP_p0p2");
  //   factory->AddVariable("IP_p1p2");


  //   factory->AddVariable("p0_pt");
  //   factory->AddVariable("p1_pt");
  //   factory->AddVariable("p2_pt");
  //   factory->AddVariable("p0_eta");
  //   factory->AddVariable("p1_eta");
  //   factory->AddVariable("p2_eta");
  if (varset & 1 << 27)
    factory->AddVariable("p0_track_Chi2Dof");
  if (varset & 1 << 27)
    factory->AddVariable("p1_track_Chi2Dof");
  if (varset & 1 << 27)
    factory->AddVariable("p2_track_Chi2Dof");

  if (varset & 1 << 28)
    factory->AddVariable("p0_track_MatchChi2","track match #chi^{2} (#mu 1)","1",'F');
  if (varset & 1 << 28)
    factory->AddVariable("p1_track_MatchChi2","track match #chi^{2} (#mu 2)","1",'F');
  if (varset & 1 << 28)
    factory->AddVariable("p2_track_MatchChi2","track match #chi^{2} (#mu 3)","1",'F');

  if (varset & 1 << 29)
    factory->AddVariable("max(p0_track_MatchChi2,max(p1_track_MatchChi2,p2_track_MatchChi2))","max. #mu track match #chi^{2}","1",'F');

  if (varset & 1 << 30)
    factory->AddVariable("polarisationangle","polarisation angle","1",'F');
  if (varset & 1 << 31) {
    factory->AddVariable("mass_p0p2");
    factory->AddVariable("mass_p1p2");
  }

  //factory->AddSpectator("truetau");
  //factory->AddSpectator("NeuroBayes_0x109cf818");
  //factory->AddSpectator("NeuroBayes_0x119cf818");
  //factory->AddSpectator("NeuroBayes_0x129cf818");
  //factory->AddSpectator("NeuroBayes_0x141cf818");
  //factory->AddSpectator("NeuroBayes_0x143cf818");
  //factory->AddSpectator("NeuroBayes_0x145cf818");
  //factory->AddSpectator("NeuroBayes_0x149c1818");
  //factory->AddSpectator("NeuroBayes_0x149ce018");
  //factory->AddSpectator("NeuroBayes_0x149ce718");
  //factory->AddSpectator("NeuroBayes_0x149cf818");
  //factory->AddSpectator("NeuroBayes_0x149d1818");
  //factory->AddSpectator("NeuroBayes_0x1c9cf818");
  //   factory->AddVariable("ptorderedp0_pt");
  //   factory->AddVariable("ptorderedp1_pt");
  //   factory->AddVariable("ptorderedp2_pt");
  //   factory->AddVariable("ptorderedp0_p0_track_Chi2Dof");
  //   factory->AddVariable("ptorderedp1_p1_track_Chi2Dof");
  //   factory->AddVariable("ptorderedp2_p2_track_Chi2Dof");
  //   factory->AddVariable("p0_PIDmupi");
  //   factory->AddVariable("p1_PIDmupi");
  //   factory->AddVariable("p2_PIDmupi");
  //   factory->AddVariable("p0_PIDmuk");
  //   factory->AddVariable("p1_PIDmuk");
  //   factory->AddVariable("p2_PIDmuk");
  //   factory->AddVariable("p0_NShared");
  //   factory->AddVariable("p1_NShared");
  //   factory->AddVariable("p2_NShared");
  //   factory->AddVariable("p0_MuLL");
  //   factory->AddVariable("p1_MuLL");
  //   factory->AddVariable("p2_MuLL");
  //   factory->AddVariable("p0_MuDLL");
  //   factory->AddVariable("p1_MuDLL");
  //   factory->AddVariable("p2_MuDLL");
  //   factory->AddVariable("p0_MuBkg");
  //   factory->AddVariable("p0_richMU");
  //   factory->AddVariable("p0_richK");
  //   factory->AddVariable("p0_richPI");
  //   factory->AddVariable("p0_ecalMU");
  //   factory->AddVariable("p0_hcalMU");
  //   factory->AddVariable("p1_MuBkg");
  //   factory->AddVariable("p1_richMU");
  //   factory->AddVariable("p1_richK");
  //   factory->AddVariable("p1_richPI");
  //   factory->AddVariable("p1_ecalMU");
  //   factory->AddVariable("p1_hcalMU");
  //   factory->AddVariable("p2_MuBkg");
  //   factory->AddVariable("p2_richMU");
  //   factory->AddVariable("p2_richK");
  //   factory->AddVariable("p2_richPI");
  //   factory->AddVariable("p2_ecalMU");
  //   factory->AddVariable("p2_hcalMU");
  //   factory->AddVariable("ptorderedp0_PIDmupi");
  //   factory->AddVariable("ptorderedp1_PIDmupi");
  //   factory->AddVariable("ptorderedp2_PIDmupi");
  //   factory->AddVariable("ptorderedp0_PIDmuk");
  //   factory->AddVariable("ptorderedp1_PIDmuk");
  //   factory->AddVariable("ptorderedp2_PIDmuk");

  /*

     factory->AddVariable("FlightDistance");
     factory->AddVariable("FlightDistance/FlightDistanceError","FlightDistanceSignificance","1",'F');
     factory->AddVariable("IP");
     factory->AddVariable("IPSig");

     factory->AddVariable("VertexChi");
     factory->AddVariable("firstIP");
     factory->AddVariable("secondIP");
     factory->AddVariable("thirdIP");

     factory->AddVariable("firstIPSig");
     factory->AddVariable("secondIPSig");
     factory->AddVariable("thirdIPSig");
     if (varset & 1 << 11)
     factory->AddVariable("max(thirdIPSig,max(secondIPSig,firstIPSig))","max Muon IPSig","1",'F');

     factory->AddVariable("min(thirdIPSig,min(secondIPSig,firstIPSig))","min Muon IPSig","1",'F');
     factory->AddVariable("DOCAone");
     factory->AddVariable("DOCAtwo");
     factory->AddVariable("DOCAthree");

     factory->AddVariable("max(max(DOCAone,DOCAtwo),DOCAthree)");
     if (varset & 1 << 17)
     factory->AddVariable("min(min(DOCAone,DOCAtwo),DOCAthree)");
     factory->AddVariable("dira");
     factory->AddVariable("pt");

     factory->AddVariable("LifeTime");
     */

  // You can add so-called "Spectator variables", which are not used in the MVA training,
  // but will appear in the final "TestTree" produced by TMVA. This TestTree will contain the
  // input variables, the response values of all trained MVAs, and the spectator variables

  // Read training and test data
  // (it is also possible to use ASCII format as input -> see TMVA Users Guide)
  //TString sname = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_tau23mu.root"; /// deprecated

  ///@todo: add Krakow ntuples
  //TString Bbname = "/tmp/d0bar/2013/MC/v7/MC12_inclB.root";
  //TString Cbname = "/tmp/d0bar/2013/MC/v7/MC12_inclC.root";
  TString Bbname = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_inclB.root";
  TString Cbname = "/auto/data/pseyfert/Tau_MC/v9_copy/MC12_inclC.root";

  TFile *inputBb = TFile::Open( Bbname );
  TFile *inputCb = TFile::Open( Cbname );
  //TFile *inputs = TFile::Open( sname ); /// deprecated

  // --- Register the training and test trees

  float sig_train_frac = 0.5;
  float bkg_train_frac = 0.8;
  float sig_test_frac = 0.5;
  float bkg_test_frac = 0.2;
  ///TTree *signal     = (TTree*)inputs->Get("Tau23Mu"); /// deprecated
  TTree *Cbackground = (TTree*)inputCb->Get("Tau23Mu");
  TTree *Bbackground = (TTree*)inputBb->Get("Tau23Mu");

  TFile* sigtrainfile = TFile::Open("/auto/data/pseyfert/Tau_MC/tau23mu_mix_train.root");
  TFile* sigtestfile = TFile::Open("/auto/data/pseyfert/Tau_MC/tau23mu_mix_test.root");
  TTree* signal_train = (TTree*)sigtrainfile->Get("Tau23Mu");
  TTree* signal_test = (TTree*)sigtestfile->Get("Tau23Mu");
  sig_train_frac = 1.-sig_train_frac;
  bkg_train_frac = 1.-bkg_train_frac;
// no inversion here: sig_test_frac = 1.-sig_test_frac;
// no inversion here: bkg_test_frac = 1.-bkg_test_frac;



  TString mycuts;
  if (restricttods) {
    mycuts = "L0Dec&&Hlt1Dec&&(TriggerTOSHlt2TriMuonTauDecision||TriggerTOSHlt2CharmSemilep3bodyD2KMuMuDecision)&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99&&truetau==15&&(!(tauproduction&0x2220))";
  } else {
    mycuts = "L0Dec&&Hlt1Dec&&(TriggerTOSHlt2TriMuonTauDecision||TriggerTOSHlt2CharmSemilep3bodyD2KMuMuDecision)&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99&&truetau==15";
  }
  TString mycutb = "L0Dec&&Hlt1Dec&&(TriggerTOSHlt2TriMuonTauDecision||TriggerTOSHlt2CharmSemilep3bodyD2KMuMuDecision)&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99&&peakingbkg<0.5";
  //TCut mycutb = "(abs(EventHash%2)==1)&&L0Dec&&Hlt1Dec&&Hlt2Dec&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99";



  TFile* ff = new TFile(Form("/tmp/pseyfert/buffer%d.root",gstep),"recreate");
  TDirectory* buffer = gDirectory;
  ff->cd();
  //TTree *sig_train =       signal->CopyTree(Form("%s&&(abs(EventHash)\%100)>=%d",mycuts.Data(),(int)(sig_train_frac*100)));
  //TTree *sig_test =        signal->CopyTree(Form("%s&&(abs(EventHash)\%100)<%d", mycuts.Data(),(int)(sig_test_frac*100)));
  TTree* sig_train = signal_train->CopyTree(mycuts.Data());
  TTree* sig_test = signal_test->CopyTree(mycuts.Data());
  TTree *Cbkg_train = Cbackground->CopyTree(Form("%s&&(abs(EventHash)\%100)>=%d",mycutb.Data(),(int)(bkg_train_frac*100)));
  TTree *Cbkg_test =  Cbackground->CopyTree(Form("%s&&(abs(EventHash)\%100)<%d", mycutb.Data(),(int)(bkg_test_frac*100)));
  TTree *Bbkg_train = Bbackground->CopyTree(Form("%s&&(abs(EventHash)\%100)>=%d",mycutb.Data(),(int)(bkg_train_frac*100)));
  TTree *Bbkg_test =  Bbackground->CopyTree(Form("%s&&(abs(EventHash)\%100)<%d", mycutb.Data(),(int)(bkg_test_frac*100)));
  buffer->cd();

  float sigevts = sig_train->GetEntriesFast();
  float bkgevts = Bbkg_train->GetEntriesFast()
              + Cbkg_train->GetEntriesFast();


  // global event weights per tree (see below for setting event-wise weights)
  //
  //  MC12_inclCP6_UP_TCKEMU_sm0
  //    Nb of events read    =    1282497
  //--
  //  MC12_inclCP8_UP_TCKEMU_sm0
  //    Nb of events read    =    1277749
  //--
  //  MC12_inclCP6_DOWN_TCKEMU_sm0
  //    Nb of events read    =    1274993
  //--
  //  MC12_inclCP6_DOWN_TCKEMU_sm0
  //    Nb of events read    =    1274993
  //  = 5110232
  //--
  //  MC12_inclBP8_DOWN_TCKEMU_sm0
  //    Nb of events read    =    1275747
  //--
  //  MC12_inclBP6_DOWN_TCKEMU_sm0
  //    Nb of events read    =    1291247
  //--
  //  MC12_inclBP8_UP_TCKEMU_sm0
  //    Nb of events read    =    1268746
  //--
  //  MC12_inclBP6_UP_TCKEMU_sm0
  //    Nb of events read    =    1295743
  //  = 5131483
  //
  //
  //
  Double_t signalWeight     = 3.193;
  float lumi_C_sample = 1.3 + lumi_C_error * 0.2;
  float lumi_B_sample = 6.2 + lumi_B_error * 1.0;
  /// transform numbers close to one: A'*B' = 1, A/B = A'/B'
  ///                             =>  A/B*B'^2 = 1
  ///                             =>  B'= sqrt(B/A)
  lumi_C_sample = sqrt(lumi_C_sample/lumi_B_sample);
  lumi_B_sample = 1./lumi_C_sample;
  /// relative weights are inverse luminosities;
  Double_t CbackgroundWeight = 1./lumi_C_sample;
  Double_t BbackgroundWeight = 1./lumi_B_sample;
  Double_t totalBweight = BbackgroundWeight * Bbkg_train->GetEntriesFast();
  Double_t totalCweight = CbackgroundWeight * Cbkg_train->GetEntriesFast();
  signalWeight = (totalBweight+totalCweight)/sigevts;


  Double_t signalTrainWeight = signalWeight / sig_train_frac;
  Double_t signalTestWeight = signalWeight / (sig_test_frac);
  Double_t CbackgroundTrainWeight = CbackgroundWeight / sig_train_frac;
  Double_t BbackgroundTrainWeight = BbackgroundWeight / sig_train_frac;
  Double_t CbackgroundTestWeight = CbackgroundWeight / (sig_test_frac);
  Double_t BbackgroundTestWeight = BbackgroundWeight / (sig_test_frac);

  // You can add an arbitrary number of signal or background trees
  //factory->AddSignalTree    ( signal,     signalWeight     );
  //factory->AddBackgroundTree( Cbackground, CbackgroundWeight );
  //factory->AddBackgroundTree( Bbackground, BbackgroundWeight );

  // To give different trees for training and testing, do as follows:
  factory->AddSignalTree( sig_train, signalTrainWeight, "Training" );
  factory->AddSignalTree( sig_test,     signalTestWeight,  "Test" );

  factory->AddBackgroundTree( Cbkg_train, CbackgroundTrainWeight, "Training" );
  factory->AddBackgroundTree( Cbkg_test,     CbackgroundTestWeight,  "Test" );
  factory->AddBackgroundTree( Bbkg_train, BbackgroundTrainWeight, "Training" );
  factory->AddBackgroundTree( Bbkg_test,     BbackgroundTestWeight,  "Test" );

  /// signal events = 51369
  /// background C: 471+501
  /// background B: 1062+1162
  /// background =  3196
  factory->SetBackgroundWeightExpression( Form("%f",sigevts/sqrt(sigevts+bkgevts)) );
  factory->SetSignalWeightExpression(Form("%f",bkgevts/sqrt(sigevts+bkgevts)));


  factory->PrepareTrainingAndTestTree( "1", "1",
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

  if (Use["MLPCJ"])
    mypointer.push_back(factory->BookMethod( TMVA::Types::kMLP, "MLPCJ", "!H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:EstimatorType=CE:!UseRegulator" ));

  if (Use["MLPBFGS"])
    factory->BookMethod( TMVA::Types::kMLP, "MLPBFGS", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:EstimatorType=CE:!UseRegulator" );

  if (Use["MLPMSE"])
    mypointer.push_back(factory->BookMethod( TMVA::Types::kMLP, "MLPMSE", "!H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:EstimatorType=MSE:!UseRegulator" ));

  if (Use["MLPMSEBFGW"])
    mypointer.push_back(factory->BookMethod( TMVA::Types::kMLP, "MLPMSEBFGW", "!H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TRainingMethod=BFGS:TestRate=5:EstimatorType=MSE:!UseRegulator" ));

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
        "!H:!V:NTrees=50:BoostType=Grad:Shrinkage=0.5:UseBaggedGrad:GradBaggingFraction=0.5:nEventsMin=1880:MaxDepth=4:NNodesMax=8" );
  /*--- OptimizeConfigParamete...: For BDTG the optimized Parameters are: 
    --- OptimizeConfigParamete...: MaxDepth = 8
    --- OptimizeConfigParamete...: NTrees = 50
    --- OptimizeConfigParamete...: NodeMinEvents = 65
    --- OptimizeConfigParamete...: Shrinkage = 0.5
    --- Factory                  : Optimization of tuning paremters finished for Method:BDTG
    */

  if (Use["BDTold"])  // Adaptive Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTold",
        "!H:!V:NTrees=50:nEventsMin=200:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
  if (Use["BDT"])  // Adaptive Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDT",
        "!H:!V:NTrees=50:nEventsMin=1880:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
  /*--- OptimizeConfigParamete...: For BDT the optimized Parameters are: 
    --- OptimizeConfigParamete...: AdaBoostBeta = 0.5
    --- OptimizeConfigParamete...: MaxDepth = 3
    --- OptimizeConfigParamete...: NTrees = 50
    --- OptimizeConfigParamete...: NodeMinEvents = 200
    --- Factory                  : Optimization of tuning paremters finished for Method:BDT
    --

*/
  if (Use["BDTB"]) // Bagging
    factory->BookMethod( TMVA::Types::kBDT, "BDTB",
        "!H:!V:NTrees=50:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20:MaxDepth=5:nEventsMin=20:PruneMethod=NoPruning" );
  /*--- OptimizeConfigParamete...: For BDTB the optimized Parameters are: 
    --- OptimizeConfigParamete...: MaxDepth = 10
    --- OptimizeConfigParamete...: NTrees = 1000
    --- OptimizeConfigParamete...: NodeMinEvents = 20
    --- Factory                  : Optimization of tuning paremters finished for Method:BDTB
    */

  if (Use["BDTD"]) // Decorrelation + Adaptive Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTD",
        "!H:!V:NTrees=50:nEventsMin=20:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning:VarTransform=Decorrelate" );
  /*--
    --- OptimizeConfigParamete...: For BDTD the optimized Parameters are: 
    --- OptimizeConfigParamete...: AdaBoostBeta = 0.5
    --- OptimizeConfigParamete...: MaxDepth = 3
    --- OptimizeConfigParamete...: NTrees = 50
    --- OptimizeConfigParamete...: NodeMinEvents = 20
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

  // Frank01eff.push_back(std::pair<int,float>(varset, (dynamic_cast<TMVA::MethodBase*>(factory->GetMethod("Fisher")))->GetEfficiency("Efficiency:0.01",TMVA::Types::kTesting,err)));
  // Frank01efferr.push_back(std::pair<int,float>(varset,err));
  // rankroc.push_back(std::pair<int,float>(varset, (dynamic_cast<TMVA::MethodBase*>(factory->GetMethod("BDT")))->GetROCIntegral()));
  // ranksig.push_back(std::pair<int,float>(varset, (dynamic_cast<TMVA::MethodBase*>(factory->GetMethod("BDT")))->GetSignificance()));
  // //Lrank01eff.push_back(std::pair<int,float>(varset, (dynamic_cast<TMVA::MethodBase*>(factory->GetMethod("LikelihoodPCA")))->GetEfficiency("Efficiency:0.01",TMVA::Types::kTesting,err)));
  // //Lrank01efferr.push_back(std::pair<int,float>(varset,err));
  // Brank01eff.push_back(std::pair<int,float>(varset, (dynamic_cast<TMVA::MethodBase*>(factory->GetMethod("BDT")))->GetEfficiency("Efficiency:0.01",TMVA::Types::kTesting,err)));
  // Brank01efferr.push_back(std::pair<int,float>(varset,err));

  std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
  std::cout << "==> TMVAClassification is done!" << std::endl;

  MakeFlatteningFunction(Form("%x_MC12vsMC12.root",varset),"TestTree","BDT",-1.,1.0001,false,300,varset,"classID==0");

  delete factory;

  buffer->Close();
  delete buffer;

  // Launch the GUI for the root macros
  //   if (!gROOT->IsBatch()) TMVAGui( outfileName );
}

int ip, flight,taukin,docas,dira,Tiso,Ciso;
int trchi;
int matchchi;
int varset = 0;
int conditions = 0;
int withpolangle = 0;
int dalitz = 0;
int make_varset() {
  varset = 0 ;
  varset |= 0x8;
  varset |= 0x10;
  if (0 == ip)
    varset |= 0x700;
  if (1 == ip) 
    varset |= 0x1800;
  if (0 == flight)
    varset |= 0x3;
  if (1 == flight)
    varset |= 0x100000;
  if (2 == flight)
    varset |= 0x100003;
  if (1 == taukin) 
    varset |= 0x080000;
  if (1 == docas)
    varset |= 0xE000;
  if (2 == docas)
    varset |= 0x10000;
  if (1 == dira)
    varset |= 0x40000;
  if (1 == Tiso)
    varset |= 1 << 21;
  if (2 == Tiso)
    varset |= 1 << 22;
  if (3 == Tiso)
    varset |= 1 << 23;
  if (1 == Ciso)
    varset |= 1 << 24;
  if (2 == Ciso)
    varset |= 1 << 25;
  if (3 == Ciso)
    varset |= 1 << 26;
  if (1 == trchi)
    varset |= 1 << 27;
  if (1 == matchchi)
    varset |= 1 << 28;
  if (2 == matchchi)
    varset |= 1 << 29;
  if (1 == withpolangle)
    varset |= 1 << 30;
  if (1 == dalitz)
    varset |= 1 << 31;
  ++conditions;
  TMVACC("",varset);

  return varset;
}

void initvar() {

  ip = 1;
  flight = 1;
  taukin = 1;
  docas = 1;
  dira = 1;
  Tiso = 3;
  Ciso = 3;
  trchi = 0;
  matchchi = 1;
  withpolangle = 0;
}

void TMVA_develope_GeoMVA2013(int step) {
  gstep = step;
  varset = 0;
  conditions = 0;
  if (false) {
    for ( ip = 0 ; ip < 3 ; ++ip) { // 3
      for ( flight = 0 ; flight < 4 ; ++flight) { //4
        for ( taukin = 0 ; taukin < 2 ; ++taukin) { //2
          for ( docas = 0 ; docas < 2 ; ++docas) { //2
            for ( dira = 0 ; dira <2 ; ++dira) { //2
              for ( Tiso = 0 ; Tiso < 2 ; ++Tiso) {
                for ( Ciso = 0 ; Ciso < 2 ; ++Ciso) {
                  varset = 0 ;
                  varset |= 0x8;
                  varset |= 0x10;
                  if (0 == ip)
                    varset |= 0x700;
                  if (1 == ip) 
                    varset |= 0x1800;
                  if (0 == flight)
                    varset |= 0x3;
                  if (1 == flight)
                    varset |= 0x100000;
                  if (2 == flight)
                    varset |= 0x100003;
                  if (1 == taukin) 
                    varset |= 0x080000;
                  if (1 == docas)
                    varset |= 0xE000;
                  if (1 == dira)
                    varset |= 0x40000;
                  if (1 == Tiso)
                    varset |= 1 << 21;
                  if (2 == Tiso)
                    varset |= 1 << 22;
                  if (3 == Tiso)
                    varset |= 1 << 23;
                  if (1 == Ciso)
                    varset |= 1 << 24;
                  if (2 == Ciso)
                    varset |= 1 << 25;
                  if (3 == Ciso)
                    varset |= 1 << 26;
                  ++conditions;
                  TMVACC("",varset);
                }
              }
            }
          }
        }
      } 
    }
  }
  if (false) {
    //initvar();
    //printf("%x",make_varset());

    initvar();
    //dalitz = 1;
    withpolangle = 1;
    printf("%x",make_varset());


    //  initvar();
    //  docas = 2;
    //  make_varset();

    //  initvar();
    //  matchchi = 2;
    //  make_varset();

  }


  ++conditions;

  /// force no iso
  varset = ((0x145cf818) | (1 << 11) | (1 << 22) | (1 << 23)) ^ ((1 << 22) | (1 << 11) | (1 << 23));
  int basevars = varset;
  printf("varset nothing 0x%x\n",varset);
if (step==1)
  TMVACC("",varset);
  /// force all iso
  varset = basevars | (1 << 22);
  printf("varset all G isos 0x%x\n",varset);
if (step==2)
  TMVACC("",varset);
  /// lauras iso
  varset = basevars | (1 << 11);
  printf("varset laura 0x%x\n",varset);
if (step==3)
  TMVACC("",varset);
  /// lauras iso and old iso
  varset = basevars | (1 << 11);
  varset |=  (1 << 23);
  printf("varset laura and old 0x%x\n",varset);
if (step==4)
  TMVACC("",varset);
  /// force summ iso
  varset = basevars | (1 << 23);
  printf("varset sum G iso 0x%x\n",varset);
if (step==5)
  TMVACC("",varset);

  if (false) {

    initvar();
    trchi = 1;
    make_varset();

    initvar();
    matchchi = 1;
    make_varset();

    initvar();
    trchi = 1;
    matchchi = 1;
    make_varset();

    initvar();
    Ciso = 0;
    make_varset();

    initvar();
    Ciso = 1;
    make_varset();

    initvar();
    Ciso = 2;
    make_varset();

    initvar();
    Tiso = 0;
    make_varset();

    initvar();
    Tiso = 1;
    make_varset();

    initvar();
    Tiso = 2;
    make_varset();

    initvar();
    docas = 0;
    make_varset();

    initvar();
    docas = 2;
    make_varset();

    initvar();
    ip = 0;
    make_varset();

    initvar();
    ip = 2;
    make_varset();

  }
  TH1* Fhist = new TH1F("hist","efficiency at 0.01 bkg Fisher",conditions,0,conditions);
  TH1* Lhist = new TH1F("hist","efficiency at 0.01 bkg LikelihoodPCA",conditions,0,conditions);
  TH1* Bhist = new TH1F("hist","efficiency at 0.01 bkg BDT",conditions,0,conditions);
  TH1* roc = new TH1F("roc","roc integral",conditions,0,conditions);
  TH1* sig = new TH1F("sig","significance",conditions,0,conditions);
  for (unsigned i = 0 ; i < Frank01eff.size() ; ++i) {
    int bin = Fhist->Fill(Form("%x",Frank01eff[i].first),Frank01eff[i].second);
    if (Fhist->GetBinContent(bin) != Frank01eff[i].second) break;
    Fhist->SetBinError(bin,Frank01efferr[i].second);
    //bin = Lhist->Fill(Form("%x",Lrank01eff[i].first),Lrank01eff[i].second);
    //if (Lhist->GetBinContent(bin) != Lrank01eff[i].second) break;
    //Lhist->SetBinError(bin,Lrank01efferr[i].second);
    bin = Bhist->Fill(Form("%x",Brank01eff[i].first),Brank01eff[i].second);
    if (Bhist->GetBinContent(bin) != Brank01eff[i].second) break;
    Bhist->SetBinError(bin,Brank01efferr[i].second);   
    roc->Fill(Form("0x%x",rankroc[i].first),rankroc[i].second);
    sig->Fill(Form("0x%x",ranksig[i].first),ranksig[i].second);
  } 
  TCanvas* c = new TCanvas();
  c->Divide(2,1);
  c->cd(1);
  Fhist->Draw();
  c->cd(2);
  Bhist->Draw();
  TCanvas* c2 = new TCanvas();
  roc->Draw();
  TCanvas* c1 = new TCanvas();
  sig->Draw();

  //return;
  initvar();
  //TMVAGui(Form("%x_MC12vsMC12.root",varset));
}
