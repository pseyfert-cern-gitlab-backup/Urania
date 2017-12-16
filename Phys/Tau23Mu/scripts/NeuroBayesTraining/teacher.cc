// access to data in nutple
#include "readNtuple.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <TMath.h>

// ROOT 
#include <TVector3.h>
#include <TH1F.h>
#include <TFile.h>

// NeuroBayes
#include "NeuroBayesTeacher.hh"
#include "NeuroBayesExpert.hh"

//////////
// switches
//
//
float lumi_C_error = 0.;
float lumi_B_error = 0.;
//
//////////



// declare functions
void teacher(int);

int ip, flight,taukin,docas,dira,Tiso,Ciso;
int trchi;
int matchchi;
int m_varset = 0;
int conditions = 0;
int withpolangle = 0;
int dalitz = 0;
int make_varset(int varset=0) {
  if (0==varset) {
  m_varset = 0 ;
  m_varset |= 0x8;
  m_varset |= 0x10;
  if (0 == ip)
    m_varset |= 0x700;
  if (1 == ip) 
    m_varset |= 0x1800;
  if (0 == flight)
    m_varset |= 0x3;
  if (1 == flight)
    m_varset |= 0x100000;
  if (2 == flight)
    m_varset |= 0x100003;
  if (1 == taukin) 
    m_varset |= 0x080000;
  if (1 == docas)
    m_varset |= 0xE000;
  if (2 == docas)
    m_varset |= 0x10000;
  if (1 == dira)
    m_varset |= 0x40000;
  if (1 == Tiso)
    m_varset |= 1 << 21;
  if (2 == Tiso)
    m_varset |= 1 << 22;
  if (3 == Tiso)
    m_varset |= 1 << 23;
  if (1 == Ciso)
    m_varset |= 1 << 24;
  if (2 == Ciso)
    m_varset |= 1 << 25;
  if (3 == Ciso)
    m_varset |= 1 << 26;
  if (1 == trchi)
    m_varset |= 1 << 27;
  if (1 == matchchi)
    m_varset |= 1 << 28;
  if (2 == matchchi)
    m_varset |= 1 << 29;
  if (1 == withpolangle)
    m_varset |= 1 << 30;
  if (1 == dalitz)
    m_varset |= 1 << 31;
  } else {
    m_varset = varset;
  }

  std::cout << "DO A TRAINING" << std::endl;
  teacher(m_varset);
  std::cout << "DID A TRAINING" << std::endl;
  return m_varset;
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




// ---------------------------------------------------------------
void teacher(int varset = 0x149cf818) 
{
  std::cout << "Start NeuroBayes Setup" << std::endl
    << "======================" << std::endl
    << std::endl;

  //stripping net

  //
  // plot input variables 
  //
  TFile output("inputvars.root","recreate");
  //  TH1F* hKPlusPt     = new TH1F("hKPlusPt"     , "K+ pt"                   , 120,    0.0,  30.0);
  //  TH1F* hKPlusMinPt  = new TH1F("hKPlusMinPt"  , "K+ pt"                   , 120,    0.0,  30.0);
  //  TH1F* hKPlusMaxPt  = new TH1F("hKPlusMaxPt"  , "K+ pt"                   , 120,    0.0,  30.0);
  //  TH1F* hKPlusP      = new TH1F("hKPlusP"      , "K+ p"                    , 120,    0.0, 300.0);
  //  TH1F* hKPlusD0     = new TH1F("hKPlusD0"     , "K+ impact parameter"     , 120,   -8.0,  10.0);
  //  TH1F* hKPlusD0SV   = new TH1F("hKPlusD0SV"   , "K+ impact parameter (SV)", 120,   -0.5,   8.0);
  //  TH1F* hKPlusDllK   = new TH1F("hKPlusDllK"   , "K+ DllK"                 , 5000, -1000, 200.0);
  //  TH1F* hKPlusDllE   = new TH1F("hKPusDllE"    , "K+ DllE"                 , 5000, -1000,  25.0);
  //  TH1F* hKPlusDllP   = new TH1F("hKPlusDllP"   , "K+ DllP"                 , 5000, -1000, 120.0);
  //  TH1F* hKPlusDllMu  = new TH1F("hKPlusDllMu"  , "K+ DllMu"                , 5000, -1000,  25.0);
  //  TH1F* hKPlusE      = new TH1F("hKPlusE"      , "K+ calo E"               , 5000, -1000.0,8000.0);
  //  TH1F* hBsChi2      = new TH1F("hBsChi2"      , "Bs chi2"                 , 120,    0.0,  25.0);
  //  TH1F* hBsP         = new TH1F("hBsP "        , "Bs P "                   , 120,    0.0, 300.0);
  //  TH1F* hBsMassErr   = new TH1F("hBsMassErr"   , "Bs massErr"              , 120,    0.0,   0.1);
  //  TH1F* hBsCTauErr   = new TH1F("hBsCTauErr"   , "Bs cTauErr"              , 120,    0.0,   0.1);
  //  TH1F* hThetaStar   = new TH1F("hThetaStar"   , "|cos(theta*)|"           , 120,    0.0,   1.0);
  //  TH1F* hNCand       = new TH1F("hNCand"       , "n BsCand"                ,  40,    0.0,  40.0);
  //
  //  TH1F* hWT          = new TH1F("hWT"          , "event weight"            , 120,    0.0, 10.0); 
  //
  // setup NeuroBayes
  //
  //create NeuroBayes instance
  NeuroBayesTeacher* teacher = NeuroBayesTeacher::Instance();

  teacher->NB_DEF_NODE2(15);          	// nodes in hidden layer
  teacher->NB_DEF_NODE3(1);          	  // nodes in output layer


  teacher->NB_DEF_TASK("CLA");          // binominal classification
  teacher->NB_DEF_SHAPE("DIAG");        // force to diagonal  
  teacher->NB_DEF_REG("ALL");           // 'OFF','REG' (def) ,'ARD','ASR','ALL'
  teacher->NB_DEF_LOSS("ENTROPY");      // 'ENTROPY'(def),'QUADRATIC'

  teacher->NB_DEF_ITER(500);            // number of training iteration
  teacher->NB_DEF_METHOD("BFGS");	     // will stop automatically if there's nothing more to learn
  teacher->NB_DEF_LEARNDIAG( 1 );	     // BFGS
  teacher->NB_DEF_PRE(12);		         // flatten and de-correlate input variables, keep only variables with >n*0.5 sigma significance

  teacher->NB_DEF_SPEED(0.1);
  teacher->NB_DEF_MAXLEARN(0.01);
  teacher->NB_DEF_EPOCH(100);
  /////teacher->NB_DEF_MOM(0.9);

  //int i= 49801;
  //int j= 21; 
  //teacher->NB_RANVIN(i,j,2);      //different random seed

  char ExpertiseFile[256];
  sprintf(ExpertiseFile,Form("tau23mu_v2_%x.nb",varset));

  std::cout << "Will put the Expertise in " << ExpertiseFile << std::endl;
  teacher->SetOutputFile(ExpertiseFile);  // expert file

  //
  // individual prepro-flags
  //
  // 14: flatten input variable, regularised spline fit to mean of target, no delta function
  // 15: same as 14 but monotonous fit
  // 18: flatten input variable,no delta func, unordered class 
  // 19: same, but ordered class
  //
  Long64_t nbytes = 0, nb = 0;
  TChain* ffffChain = new TChain("Tau23Mu");
  ffffChain->Add("/afs/cern.ch/work/p/pseyfert/public/triggeremulation/weightsv3/mcselected_MC11tau23mu_md_TCKEMU_flat_593995evts.root");

  readNtuple fffntuple(ffffChain);
  TTree* trainingtree = new TTree("trainingtree","trainingtree");
  std::vector<double> inputvector;
  int varcount(0);
  if (varset & 1 << 0) {
    inputvector.push_back(fffntuple.FlightDistance);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.FlightDistance",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.FlightDistance);" << std::endl;
  }
  //inputvector.push_back(fffntuple.FlightDistanceError);
  if (varset & 1 << 1) {
    inputvector.push_back(fffntuple.FlightDistance/fffntuple.FlightDistanceError);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.FlightDistance/fffntuple.FlightDistanceError",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.FlightDistance/fffntuple.FlightDistanceError);" << std::endl;
  }
  if (varset & 1 << 20) {
    inputvector.push_back(TMath::Exp(-1000*fffntuple.LifeTime));
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("LifeTime",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(TMath::Exp(-1000*fffntuple.LifeTime));" << std::endl;
  }
  if (varset & 1 << 2) {
    inputvector.push_back(fffntuple.IP);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.IP",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.IP);" << std::endl;
  }
  if (varset & 1 << 3) {
    inputvector.push_back(fffntuple.IPSig);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.IPSig",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.IPSig);" << std::endl;
  }
  if (varset & 1 << 4) {
    inputvector.push_back(fffntuple.VertexChi2);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.VertexChi2",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.VertexChi2);" << std::endl;
  }
  if (varset & 1 << 18) {
    inputvector.push_back(acos(fffntuple.dira));
    teacher->SetIndividualPreproFlag( varcount++,15);
    trainingtree->Branch("acos(fffntuple.dira)",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(acos(fffntuple.dira));" << std::endl;
  }
  if (varset & 1 << 19) {
    inputvector.push_back(fffntuple.pt);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.pt",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.pt);" << std::endl;
  }
  if (varset & 1 << 5) {
    inputvector.push_back(fffntuple.p0_IP);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.p0_IP",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.p0_IP);" << std::endl;
  }
  if (varset & 1 << 6) {
    inputvector.push_back(fffntuple.p1_IP);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.p1_IP",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.p1_IP);" << std::endl;
  }
  if (varset & 1 << 7) {
    inputvector.push_back(fffntuple.p2_IP);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.p2_IP",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.p2_IP);" << std::endl;
  }
  if (varset & 1 << 8) {
    inputvector.push_back(fffntuple.p0_IPSig);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.p0_IPSig",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.p0_IPSig);" << std::endl;
  }
  if (varset & 1 << 9) {
    inputvector.push_back(fffntuple.p1_IPSig);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.p1_IPSig",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.p1_IPSig);" << std::endl;
  }
  if (varset & 1 << 10) {
    inputvector.push_back(fffntuple.p2_IPSig);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.p2_IPSig",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.p2_IPSig);" << std::endl;
  }
  if (varset & 1 << 11) {
    inputvector.push_back(fffntuple.Laura_SumBDT);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.Laura_SumBDT",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.Laura_SumBDT);" << std::endl;
  }


  if (varset & 1 << 12) {
    inputvector.push_back(std::min(fffntuple.p0_IPSig,std::min(fffntuple.p1_IPSig,fffntuple.p2_IPSig)));
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("min(fffntuple.p0_IPSig,min(fffntuple.p1_IPSig,fffntuple.p2_IPSig))",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(std::min(fffntuple.p0_IPSig,std::min(fffntuple.p1_IPSig,fffntuple.p2_IPSig)));" << std::endl;
  }


  if (varset & 1 << 13) {
    inputvector.push_back(fffntuple.DOCAone);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.DOCAone",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.DOCAone);" << std::endl;
  }
  if (varset & 1 << 14) {
    inputvector.push_back(fffntuple.DOCAtwo);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.DOCAtwo",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.DOCAtwo);" << std::endl;
  }
  if (varset & 1 << 15) {
    inputvector.push_back(fffntuple.DOCAthree);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.DOCAthree",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.DOCAthree);" << std::endl;
  }

  if (varset & 1 << 16) {
    inputvector.push_back(std::max(std::max(fffntuple.DOCAone,fffntuple.DOCAtwo),fffntuple.DOCAthree));
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("max(max(fffntuple.DOCAone,fffntuple.DOCAtwo),fffntuple.DOCAthree)",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(std::max(std::max(fffntuple.DOCAone,fffntuple.DOCAtwo),fffntuple.DOCAthree));" << std::endl;
  }



  if (varset & 1 << 21) {
    inputvector.push_back(fffntuple.isolationa);
    teacher->SetIndividualPreproFlag( varcount++,19);
    trainingtree->Branch("fffntuple.isolationa",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.isolationa);" << std::endl;
  }
  if (varset & 1 << 21) {
    inputvector.push_back(fffntuple.isolationb);
    teacher->SetIndividualPreproFlag( varcount++,19);
    trainingtree->Branch("fffntuple.isolationb",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.isolationb);" << std::endl;
  }
  if (varset & 1 << 21) {
    inputvector.push_back(fffntuple.isolationc);
    teacher->SetIndividualPreproFlag( varcount++,19);
    trainingtree->Branch("fffntuple.isolationc",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.isolationc);" << std::endl;
  }
  if (varset & 1 << 22) {
    inputvector.push_back(fffntuple.isolationd);
    teacher->SetIndividualPreproFlag( varcount++,19);
    trainingtree->Branch("fffntuple.isolationd",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.isolationd);" << std::endl;
  }
  if (varset & 1 << 22) {
    inputvector.push_back(fffntuple.isolatione);
    teacher->SetIndividualPreproFlag( varcount++,19);
    trainingtree->Branch("fffntuple.isolatione",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.isolatione);" << std::endl;
  }
  if (varset & 1 << 22) {
    inputvector.push_back(fffntuple.isolationf);
    teacher->SetIndividualPreproFlag( varcount++,19);
    trainingtree->Branch("fffntuple.isolationf",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.isolationf);" << std::endl;
  }
  if (varset & 1 << 23) {
    inputvector.push_back(fffntuple.iso);
    teacher->SetIndividualPreproFlag( varcount++,19);
    trainingtree->Branch("fffntuple.iso",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.iso);" << std::endl;
  }
  if (varset & 1 << 24) {
    inputvector.push_back(fffntuple.CDF1);
    teacher->SetIndividualPreproFlag( varcount++,34);
    trainingtree->Branch("fffntuple.CDF1",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.CDF1);" << std::endl;
  }
  if (varset & 1 << 25) {
    inputvector.push_back(fffntuple.CDF2);
    teacher->SetIndividualPreproFlag( varcount++,34);
    trainingtree->Branch("fffntuple.CDF2",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.CDF2);" << std::endl;
  }
  if (varset & 1 << 26) {
    inputvector.push_back(fffntuple.CDF3);
    teacher->SetIndividualPreproFlag( varcount++,34);
    trainingtree->Branch("fffntuple.CDF3",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.CDF3);" << std::endl;
  }

  //   inputvector.push_back(fffntuple.IP_p0p2);
  //   factory->AddVariable("IP_p1p2");


  //   factory->AddVariable("p0_pt");
  //   factory->AddVariable("p1_pt");
  //   factory->AddVariable("p2_pt");
  //   factory->AddVariable("p0_eta");
  //   factory->AddVariable("p1_eta");
  //   factory->AddVariable("p2_eta");
  if (varset & 1 << 27) {
    inputvector.push_back(fffntuple.p0_track_Chi2Dof);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.p0_track_Chi2Dof",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.p0_track_Chi2Dof);" << std::endl;
  }
  if (varset & 1 << 27) {
    inputvector.push_back(fffntuple.p1_track_Chi2Dof);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.p1_track_Chi2Dof",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.p1_track_Chi2Dof);" << std::endl;
  }
  if (varset & 1 << 27) {
    inputvector.push_back(fffntuple.p2_track_Chi2Dof);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.p2_track_Chi2Dof",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.p2_track_Chi2Dof);" << std::endl;
  }

  if (varset & 1 << 28) {
    inputvector.push_back(fffntuple.p0_track_MatchChi2);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.p0_track_MatchChi2",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.p0_track_MatchChi2);" << std::endl;
  }
  if (varset & 1 << 28) {
    inputvector.push_back(fffntuple.p1_track_MatchChi2);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.p1_track_MatchChi2",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.p1_track_MatchChi2);" << std::endl;
  }
  if (varset & 1 << 28) {
    inputvector.push_back(fffntuple.p2_track_MatchChi2);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.p2_track_MatchChi2",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.p2_track_MatchChi2);" << std::endl;
  }

  if (varset & 1 << 29) {
    inputvector.push_back(std::max(fffntuple.p0_track_MatchChi2,std::max(fffntuple.p1_track_MatchChi2,fffntuple.p2_track_MatchChi2)));
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("std::max(fffntuple.p0_track_MatchChi2,std::max(fffntuple.p1_track_MatchChi2,fffntuple.p2_track_MatchChi2))",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(std::max(fffntuple.p0_track_MatchChi2,std::max(fffntuple.p1_track_MatchChi2,fffntuple.p2_track_MatchChi2)));" << std::endl;
  }

  if (varset & 1 << 30) {
    inputvector.push_back(fffntuple.polarisationangle);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.polarisationangle",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.polarisationangle);" << std::endl;
  }
  if (varset & 1 << 31) {
    inputvector.push_back(fffntuple.mass_p0p2);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.mass_p0p2",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.mass_p0p2);" << std::endl;
    inputvector.push_back(fffntuple.mass_p1p2);
    teacher->SetIndividualPreproFlag( varcount++,14);
    trainingtree->Branch("fffntuple.mass_p1p2",&(inputvector.back()));
    std::cout << "pushing back inputvector.push_back(fffntuple.mass_p1p2);" << std::endl;
  }


  teacher->NB_DEF_NODE1(varcount+1);        // nodes in input layer
  std::cout << " ---------------> varcount " << varcount << std::endl;
  //
  // acceess to training sample
  //

  float* InputArray  = new float[varcount]; // array to hold input data

  // import from TMVA training script
  // Read training and test data
  // (it is also possible to use ASCII format as input -> see TMVA Users Guide)
  TString sname = "/afs/cern.ch/work/p/pseyfert/public/Tau_MC/v9_original/MC12_tau23mu.root";
  ///@todo: add Krakow ntuples
  //TString Bbname = "/tmp/d0bar/2013/MC/v7/MC12_inclB.root";
  //TString Cbname = "/tmp/d0bar/2013/MC/v7/MC12_inclC.root";
  TString Bbname = "/afs/cern.ch/work/p/pseyfert/public/Tau_MC/v9_original/new_MC12_inclB.root";
  TString Cbname = "/afs/cern.ch/work/p/pseyfert/public/Tau_MC/v9_original/new_MC12_inclC.root";
  TFile *inputBb = TFile::Open( Bbname );
  TFile *inputCb = TFile::Open( Cbname );
  TFile *inputs = TFile::Open( sname );

  // --- Register the training and test trees

  float sig_train_frac = 0.5;
  float bkg_train_frac = 0.8;
  float sig_test_frac = 0.5;
  float bkg_test_frac = 0.2;
  TTree *signal     = (TTree*)inputs->Get("Tau23Mu");
  TTree *Cbackground = (TTree*)inputCb->Get("Tau23Mu");
  TTree *Bbackground = (TTree*)inputBb->Get("Tau23Mu");


  TFile* sigtrainfile = TFile::Open("/afs/cern.ch/work/p/pseyfert/public/Tau_MC/tau23mu_mix_train.root");
  //TFile* sigtestfile = TFile::Open("/afs/cern.ch/work/p/pseyfert/public/Tau_MC/tau23mu_mix_test.root");
  TTree* signal_train = (TTree*)sigtrainfile->Get("Tau23Mu");
  //TTree* signal_test = (TTree*)sigtestfile->Get("Tau23Mu");
  sig_train_frac = 1.-sig_train_frac;
  bkg_train_frac = 1.-bkg_train_frac;
// no inversion here: sig_test_frac = 1.-sig_test_frac;
// no inversion here: bkg_test_frac = 1.-bkg_test_frac;


  TFile* ff = new TFile("/tmp/pseyfert/buffer.root","recreate");
  TDirectory* buffer = gDirectory;
  ff->cd();

  TString mycuts;
  if (false/*restricttods*/) {
    mycuts = "L0Dec&&Hlt1Dec&&(TriggerDecHlt2TriMuonTauDecision||TriggerDecHlt2CharmSemilepD2HMuMuDecision||TriggerDecHlt2DiMuonDetachedDecision)&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99&&truetau==15&&(!(tauproduction&0x2220))";
  } else {
    mycuts = "L0Dec&&Hlt1Dec&&mass>1000&&(TriggerDecHlt2TriMuonTauDecision||TriggerDecHlt2CharmSemilepD2HMuMuDecision||TriggerDecHlt2DiMuonDetachedDecision)&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99&&truetau==15";
  }
  //TString mycutb = "(!peakingbkg)&&L0Dec&&Hlt1Dec&&(TriggerDecHlt2TriMuonTauDecision||TriggerDecHlt2CharmSemilepD2HMuMuDecision||TriggerDecHlt2DiMuonDetachedDecision)&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99";
  TString mycutb = "L0Dec&&Hlt1Dec&&(TriggerDecHlt2TriMuonTauDecision||TriggerDecHlt2CharmSemilepD2HMuMuDecision||TriggerDecHlt2DiMuonDetachedDecision)&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99";
  //TCut mycutb = "(abs(EventHash%2)==1)&&L0Dec&&Hlt1Dec&&Hlt2Dec&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99";


  //TTree *sig_train = signal->CopyTree(mycuts+Form("&&((abs(EventHash)\%100)>=%d)",(int)(sig_train_frac*100)));
  //TTree *sig_test = signal->CopyTree(Form("(abs(EventHash)\%100)<%d",(int)(sig_test_frac*100)));
  TTree* sig_train = signal_train->CopyTree(mycuts.Data());
  //TTree* sig_test = signal_test->CopyTree(mycuts.Data());
  TTree *Cbkg_train = Cbackground->CopyTree(mycutb+Form("&&((abs(EventHash)\%100)>=%d)",(int)(bkg_train_frac*100)));
  //TTree *Cbkg_test = Cbackground->CopyTree(Form("(abs(EventHash)\%100)<%d",(int)(bkg_test_frac*100)));
  TTree *Bbkg_train = Bbackground->CopyTree(mycutb+Form("&&((abs(EventHash)\%100)>=%d)",(int)(bkg_train_frac*100)));
  //TTree *Bbkg_test = Bbackground->CopyTree(Form("(abs(EventHash)\%100)<%d",(int)(bkg_test_frac*100)));
  buffer->cd();
  //

  float sigevts = sig_train->GetEntriesFast();
  float bkgevts = Bbkg_train->GetEntriesFast()
              + Cbkg_train->GetEntriesFast();
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

  // To give different trees for training and testing, do as follows:
//  factory->AddSignalTree( sig_train, signalTrainWeight, "Training" );
//  factory->AddSignalTree( sig_test,     signalTestWeight,  "Test" );

//  factory->AddBackgroundTree( Cbkg_train, CbackgroundTrainWeight, "Training" );
 // factory->AddBackgroundTree( Cbkg_test,     CbackgroundTestWeight,  "Test" );
  //factory->AddBackgroundTree( Bbkg_train, BbackgroundTrainWeight, "Training" );
  //factory->AddBackgroundTree( Bbkg_test,     BbackgroundTestWeight,  "Test" );
  for (unsigned sample = 1 ; sample <= 3 ; ++sample) {

    TTree* fChain;
    if (1==sample) fChain = sig_train;
    if (2==sample) fChain = Bbkg_train;
    if (3==sample) fChain = Cbkg_train;

/////////    if (NULL==signal) {
/////////      std::cout << "wat" << std::endl;
/////////    } else {
/////////  //    std::cout << signal->GetEntries() << std::endl;
/////////  //    signal->GetEntry(2);
/////////      readNtuple ntuple(sig_train);
/////////    }
/////////  }
/////////  if (false) {
/////////    unsigned sample = 1;
    readNtuple ntuple(fChain);
    Long64_t nentries = ntuple.fChain->GetEntries();
    std::cout << "read #entries " << nentries << std::endl;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if (jentry % (int)((double)nentries/10.0) == 0) {
        std::cout << "now read entry " << jentry << " of " << nentries <<  std::endl;
      }
      Long64_t ientry = ntuple.LoadTree(jentry);
      if (ientry < 0) break;
      nb = ntuple.fChain->GetEntry(jentry);
      nbytes += nb;

      inputvector.clear();
      if (varset & 1 << 0) {
        inputvector.push_back(ntuple.FlightDistance);
      }
      //inputvector.push_back(ntuple.FlightDistanceError);
      if (varset & 1 << 1) {
        inputvector.push_back(ntuple.FlightDistance/ntuple.FlightDistanceError);
      }
      if (varset & 1 << 20) {
        inputvector.push_back(TMath::Exp(-1000*ntuple.LifeTime));
      }
      if (varset & 1 << 2) {
        inputvector.push_back(ntuple.IP);
      }
      if (varset & 1 << 3) {
        if (!(ntuple.IPSig==ntuple.IPSig)) {
          inputvector.push_back(-999);
        } else {
          inputvector.push_back(ntuple.IPSig);
        }
      }
      if (varset & 1 << 4) {
        inputvector.push_back(ntuple.VertexChi2);
      }
      if (varset & 1 << 18) {
        inputvector.push_back(acos(ntuple.dira));
      }
      if (varset & 1 << 19) {
        inputvector.push_back(ntuple.pt);
      }
      if (varset & 1 << 5) {
        inputvector.push_back(ntuple.p0_IP);
      }
      if (varset & 1 << 6) {
        inputvector.push_back(ntuple.p1_IP);
      }
      if (varset & 1 << 7) {
        inputvector.push_back(ntuple.p2_IP);
      }
      if (varset & 1 << 8) {
        inputvector.push_back(ntuple.p0_IPSig);
      }
      if (varset & 1 << 9) {
        inputvector.push_back(ntuple.p1_IPSig);
      }
      if (varset & 1 << 10) {
        inputvector.push_back(ntuple.p2_IPSig);
      }
      if (varset & 1 << 11) {
        inputvector.push_back(ntuple.Laura_SumBDT);
      }


      if (varset & 1 << 12) {
        inputvector.push_back(std::min(ntuple.p0_IPSig,std::min(ntuple.p1_IPSig,ntuple.p2_IPSig)));
      }


      if (varset & 1 << 13) {
        inputvector.push_back(ntuple.DOCAone);
      }
      if (varset & 1 << 14) {
        inputvector.push_back(ntuple.DOCAtwo);
      }
      if (varset & 1 << 15) {
        inputvector.push_back(ntuple.DOCAthree);
      }

      if (varset & 1 << 16) {
        inputvector.push_back(std::max(std::max(ntuple.DOCAone,ntuple.DOCAtwo),ntuple.DOCAthree));
      }



      if (varset & 1 << 21) {
        inputvector.push_back(ntuple.isolationa);
      }
      if (varset & 1 << 21) {
        inputvector.push_back(ntuple.isolationb);
      }
      if (varset & 1 << 21) {
        inputvector.push_back(ntuple.isolationc);
      }
      if (varset & 1 << 22) {
        inputvector.push_back(ntuple.isolationd);
      }
      if (varset & 1 << 22) {
        inputvector.push_back(ntuple.isolatione);
      }
      if (varset & 1 << 22) {
        inputvector.push_back(ntuple.isolationf);
      }
      if (varset & 1 << 23) {
        inputvector.push_back(ntuple.iso);
      }
      if (varset & 1 << 24) {
        inputvector.push_back((1==ntuple.CDF1)?(-999):(ntuple.CDF1));
      }
      if (varset & 1 << 25) {
        inputvector.push_back((1==ntuple.CDF2)?(-999):(ntuple.CDF2));
      }
      if (varset & 1 << 26) {
        inputvector.push_back((1==ntuple.CDF3)?(-999):(ntuple.CDF3));
      }

      //   inputvector.push_back(ntuple.IP_p0p2);
      //   factory->AddVariable("IP_p1p2");


      //   factory->AddVariable("p0_pt");
      //   factory->AddVariable("p1_pt");
      //   factory->AddVariable("p2_pt");
      //   factory->AddVariable("p0_eta");
      //   factory->AddVariable("p1_eta");
      //   factory->AddVariable("p2_eta");
      if (varset & 1 << 27) {
        inputvector.push_back(ntuple.p0_track_Chi2Dof);
      }
      if (varset & 1 << 27) {
        inputvector.push_back(ntuple.p1_track_Chi2Dof);
      }
      if (varset & 1 << 27) {
        inputvector.push_back(ntuple.p2_track_Chi2Dof);
      }

      if (varset & 1 << 28) {
        inputvector.push_back(ntuple.p0_track_MatchChi2);
      }
      if (varset & 1 << 28) {
        inputvector.push_back(ntuple.p1_track_MatchChi2);
      }
      if (varset & 1 << 28) {
        inputvector.push_back(ntuple.p2_track_MatchChi2);
      }

      if (varset & 1 << 29) {
        inputvector.push_back(std::max(ntuple.p0_track_MatchChi2,std::max(ntuple.p1_track_MatchChi2,ntuple.p2_track_MatchChi2)));
      }

      if (varset & 1 << 30) {
        inputvector.push_back(ntuple.polarisationangle);
      }
      if (varset & 1 << 31) {
        inputvector.push_back(ntuple.mass_p0p2);
        inputvector.push_back(ntuple.mass_p1p2);
      }


      //

      // pre-cuts based on loose strippingline 
      //if (mB               < mMin     ||
      //    mB               > mMax     ||
      //    hPlusTrackChi2   >  5       ||
      //    hMinusTrackChi2  >  5       ||
      //    minP             < 10.0     ||
      //    minPt            <  1.5     ||
      //    (hPlusDllK   > -0.1 && hPlusDllK  < 0.1) ||
      //    (hMinusDllK  > -0.1 && hMinusDllK < 0.1) ||
      //    docaB            > 0.10     ||
      //    chi2B            > 25.0     ||
      //    maxPt            <  2.0     ||
      //    maxDllK          <  0.1)
      //  continue;


      // softer precuts
      if (ntuple.cleaningcut == 0) continue;

      trainingtree->Fill();


      //    }else {
      //      if (fileName.Contains("BsKK") || (fileName.Contains("BdPiK")))
      //        continue;
      //    }

      //    // upper sideband only
      //    if (fileName.Contains("Reco8Strip12") && mB < signal_max)
      //      continue;


      //with pre-cuts -- MC10
      //    //const double nBGCut =  15720.0;   // MC10: BG incl B
      //    //const double nBGCut = 18640.0; // MC10: BG inclB + signal tapes
      //    //const double nBGCut = 904770.0; // MC10: BG inclB + inclJPsi + signal tapes
      //    //const double nBGCut = 570252.0; // data - loose - full mass spectrum 
      //    //const double nBGCut = 137138; // data - loose - uppper sideband
      //    if (fileName.Contains("BsKK")  && nTrueBs > nBGCut/2.0)
      //      continue;
      //    if (fileName.Contains("BdPiK") && nTrueBd > nBGCut/2.0)
      //      continue;

      // #remaining Bd, Bs signal events after pre-cuts
      //const double nSigCut = 411089;
      //if (!isSignal && nBg > nSigCut)
      //  continue;


      //
      // move delta functions to -999
      //


      // fill input variables
      for (unsigned k = 0 ; k < varcount ; ++k) {
        InputArray[k] = inputvector[k];
      }
    if (varcount != inputvector.size()) {std::cerr <<"varcount = " << varcount << "\tinputvec = " << inputvector.size() <<std::endl;}

      if (ntuple.truetau==15)  {
        teacher->SetTarget(1) ;
        teacher->SetWeight(1.);
      } else {
        teacher->SetTarget(-1);
        // 3: cc, 2: bb

        teacher->SetWeight(1.);
        if (3==sample) {
          teacher->SetWeight(CbackgroundTrainWeight);
        }
        if (2==sample) {
          teacher->SetWeight(BbackgroundTrainWeight);
        }
      }

      teacher->SetNextInput(varcount,InputArray);


    } // for
  }

  output.Write();
  output.WriteTObject(trainingtree);
  output.Close();
  
  //
  // perform training
  //
  
  std::cout << "To see NeuroBayes output have a look at \"nb_teacher.log\"" << std::endl;
  //stdout is redirected to the file "nb_teacher.log"
  int original = dup(fileno(stdout));
  fflush(stdout);
  freopen("nb_teacher.log", "w", stdout);
  
  teacher->TrainNet();
  
  fflush(stdout);
  dup2(original, fileno(stdout));
  close(original);

} // void teacher


//----------------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  char* buffer;
  int varset = strtol(argv[1],&buffer,0);
  printf("setting %x\n",varset);
  make_varset(varset);
  return 0;
  int bl = 0;

  if (bl++ == atoi(argv[1])) {
    initvar();
    trchi = 1;
    make_varset();
  }
  if (bl++ == atoi(argv[1])) {
    initvar();
    matchchi = 1;
    make_varset();
  }

  if (bl++ == atoi(argv[1])) {
    initvar();
    trchi = 1;
    matchchi = 1;
    make_varset();
  }

  if (bl++ == atoi(argv[1])) {
    initvar();
    Ciso = 1;
    make_varset();
  }

  if (bl++ == atoi(argv[1])) {
    initvar();
    Ciso = 0;
    make_varset();
  }

  if (bl++ == atoi(argv[1])) {
    initvar();
    Ciso = 2;
    make_varset();
  }
          
  if (bl++ == atoi(argv[1])) {
    initvar();
    Tiso = 0;
    make_varset();
  }
    
  if (bl++ == atoi(argv[1])) {
    initvar();
    Tiso = 1;
    make_varset();
  }
    
  if (bl++ == atoi(argv[1])) {
    initvar();
    Tiso = 2;
    make_varset();
  }
   
  if (bl++ == atoi(argv[1])) {
    initvar();
    docas = 0;
    make_varset();
  }
    
  if (bl++ == atoi(argv[1])) {
    initvar();
    docas = 2;
    make_varset();
  }
      
  if (bl++ == atoi(argv[1])) {
    initvar();
    ip = 0;
    make_varset();
  }
       
  if (bl++ == atoi(argv[1])) {
    initvar();
    ip = 2;
    make_varset();
  }
        
  if (bl++ == atoi(argv[1])) {
    teacher(0x149cf818);
  }  
}
