/*
    
  Author: Francesco Dettori  
          francesco.dettori@cern.ch
         
  Date:   March-April  2013

  Modified: May 2013
  Author:   Maximilian Schlupp
            max.schlupp@cern.ch

  TODO: 
  - scaleFactor directly in inputfile and used in the whole program from beginning
  - asymmetric errors in inputfile
  - pt correction for the lambda hadronisation fraction 


*/

#include <iostream>
#include <fstream>
#include "TROOT.h"
#include <vector>
#include "TRandom3.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TApplication.h"
#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TMath.h"
#include "TFile.h"
#include "TCut.h"
#include "zstyle.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TPRegexp.h"
#include "TPostScript.h"
#include "TGaxis.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TTreeFormula.h"
#include "TLorentzVector.h"
// This lib contains the definition of the cuts 
#include "cutsdefinition.h" 

// Measurement lib for error propagation 
#include "Measurement.h" 

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooArgSet.h" 

using namespace std; 



#define MAXFILES 10
#define NMAXRWPARTS 2 
bool DEBUG = false;


void help(){
  cout << " " << endl;
  cout << "   BackEff " << endl;
  cout << "   Background efficiency calculator for BsMuMu analysis  " << endl;
  cout << endl;
  cout << " -h             \t Shows this help " << endl;
  cout << " -f [fileName]  \t Analyse given input file " << endl;
  cout << " -NoWeight      \t Switches off weighting for channels which have it " << endl;
  cout << " -ana2fb        \t Runs with normalisation of the 2fb analysis    " << endl;
  cout << " -NoMCMatch     \t Switches off the MC Matching " << endl;
  cout << " -NoFillHoles   \t Switches off the patch for empty bins in reweighting " << endl;
  cout << " -b             \t Runs in batch   " << endl;
  cout << " -d             \t Debug mode on   " << endl;
  cout << "............................................................" << endl;
}

bool match(string a, string b){
  return (std::string::npos != a.find(b));
}

///> define functions to calculate and print binned numbers
void printBinned(Measurement NtotExp, TH2D* MvsBdt, int evtType=-1, int norma_year=2012);
///> define functions which can fit the mass distributions binned in BDT calssifier 
///> (could be outsourced to a class easily)
void fitAndPrintBinnedMass(TH2D* MvsBdt, Bool_t useML, int norm_year=2012);

// Returns the correct bin for a TH2D shifting overflows and underflows back in
int getSensibleBin(TH2D *h, double x , double y);
// Recursive function to find non empty bins 
int getNonEmptyBin(TH1 *h, int bin, int iteration = 0) ;

// pt dependent correction to the Lambda_b hadronisation fraction 
// with respect to 5 GeV
double f_lambda_b_corr(double pt);

// LHCb measurement of f_lambda/(f_u+f_d)
Measurement f_lambda_over_fu(double pt);

// pt dependent hadronisation fraction 
Measurement fLambdab(double pt);
double getLambda_q2(double p_px, double p_py,double p_pz,double l_px,double l_py,double l_pz);
Measurement getLambda_q2_weight(double qsquare);
// Trigger simulation 
bool muonTriggerSim(double muplus_PT, double muminus_PT, int year);


float calculatePVweight ( int nPV ){
  float weight = 0.;
  switch (nPV){
    case 0:
      weight = 0.;
      break;
    case 1:
      weight = 0.807267;
      break;
    case 2:
      weight = 0.972547;
      break;
    case 3:
      weight = 1.21488;
      break;
    case 4:
      weight = 1.39522;
      break;  
    case 5:
      weight = 1.64909;
      break;  
    default:
      weight = 1.05432;
      break;
  }
  return weight;
}


double calculatePTweight(TH2D *h, double p, double pt);

TString plot_dir          = "plots/";
TString root_out_dir      = "root/";
TString summary_out_dir   = "summary/";


TLatex *   tex            = new TLatex(0.7,0.83,"LHCb");

Bool_t useML              = kFALSE;
Bool_t prodOutputFile     = kTRUE;
ofstream summaryFile;
TString fName;
TString prefix;


//============================================================
// MAIN 
int main(int argc, char **argv)
{
  zstyle();
  gROOT->SetBatch(kFALSE);
  gStyle->SetOptStat(0000);

  TGaxis::SetMaxDigits(3);
  TH1::SetDefaultSumw2();
  // ============================================================
  // Pars command line arguments
  if(argc<2){
    help();
    return 0;
  }
  TString conf_file_name;
  int eventType;
  
  bool batchrunning = false;
  bool weighting_off = false;
  bool fillholes_off = false;
  bool mcmatch_off = false;
  bool ana2fb = false;
  bool lambda_ptw_off = false;
  bool oldBDT =false;
  
  
  
  for(Int_t i=1; i<argc; i++){
    TString opt(argv[i]);
    cout << " Parsing option: " << opt << endl;
    if(opt.Contains("-h")){
      help();
      return 0;
    }else if(opt.Contains("-b")){
      Info("...","Running in batch" );
      batchrunning =true;
      // Note: option will be parsed by TApplication later 
    }else if(opt.Contains("-d")){
      Info("...","DEBUG mode on" );
      DEBUG =true;
      // Note: option will be parsed by TApplication later 
    }else if(opt.Contains("-f")){
      i++;
      TString val(argv[i]);
      conf_file_name = val; 
    }else if(opt.Contains("-NoWeight")){
      Warning("Configuration","Switching off weighting!!!" );
      
      weighting_off = true;
    }else if(opt.Contains("-NoMCMatch")){
      Warning("Configuration","Switching off mcmatch!!!" );
      
      mcmatch_off = true;
    }else if(opt.Contains("-NoFillHoles")){
      Warning("Configuration","Switching off the fill holes patch for muID reweighting!!!" );
      fillholes_off = true;
    }else if(opt.Contains("-ana2fb")){
      Warning("Configuration", "Using the normalisation for 2 fb analysis version");
      ana2fb = true;
    }else if(opt.Contains("-oldBDT")){
      Warning("Configuration", "Using the old BDT: BDT paper");
      oldBDT = true;
    }else if(opt.Contains("-NoLambdaPtW")){
      Warning("Configuration", "Switching off f_lambda pt weighting");
      lambda_ptw_off = true;
    }else{
      Error("Option parsing...","unknown option %s",opt.Data());
      help();
      
      return -1;
    }
  }
  cout << " End of argument parsing  " << endl;

  // End of command line argument parsing 
  // ============================================================
  // Start configuration
  //  TString input_dir = "";
  TString input_files[MAXFILES];
  int nfiles(0.);
  

  // Numbers;
  Measurement eff_gen;  // Generation efficiency 
  Measurement branch_fract; // Branching fraction 


  int analysed_events(0.);
  int norm_year = 2011; 
  int NRwParticles = 0.;
  int NRwFiles = 0.;
  // more than one file name... 
  int rew_particleid[NMAXRWPARTS];
  TString weightfilenames[NMAXRWPARTS];
  
  cout << " Start configuration" << endl;
  ifstream conf_file(conf_file_name);
  if (conf_file.is_open()){
    while (conf_file.good()){
      TString buffer;
      //    getline(conf_file, buffer); 
      conf_file >> buffer ;
      //      cout << " buffering " << buffer << endl;
      if(buffer.Contains("EventType")){
        conf_file >> eventType;
        Info("", "EventType to be analysed is: %i", eventType);
        continue;
      }else if(buffer.Contains("GenerationEfficiency")){
        double _eff, _eff_err;
        conf_file >> _eff;
        conf_file >> _eff_err;
        eff_gen = Measurement(_eff, _eff_err);
        Info("", "Generation Efficiency is %s",(char*)eff_gen);
        continue;
      }else if(buffer.Contains("BranchingFraction")){ 
        double br, br_err;
        conf_file >> br;
        conf_file >> br_err;
        branch_fract = Measurement(br, br_err);
        Info("", "Branching Fraction is %s", (char*)branch_fract);
        continue;
      }else if(buffer.Contains("AsymBF")){ ///> adds asymmetric errors (q&d!) 
        double br, br_err_up, br_err_low;
        conf_file >> br;
        conf_file >> br_err_up;
        conf_file >> br_err_low;
        branch_fract = Measurement(br, br_err_up, br_err_low, 1);
        Info("", "Branching Fraction is: %s", (char*)branch_fract); //(char*)branch_fract);
        continue;
      }else if(buffer.Contains("ReweightParticle") && !weighting_off){
        int tmp_part;
        conf_file >> tmp_part;
        rew_particleid[NRwParticles] = tmp_part;
        Info("", "Going to reweight particles with ID %i", rew_particleid[NRwParticles]);
        NRwParticles++;
        continue;
      }else if(buffer.Contains("WeightFile") && !weighting_off){
        TString tmp_file;
        conf_file >> tmp_file;
        weightfilenames[NRwFiles] = tmp_file;
        Info("", "Going to use weight file %s " , weightfilenames[NRwFiles].Data());
        NRwFiles++;
        continue;
      }else if(buffer.Contains("AnalysedEvents")){
        conf_file >> analysed_events;
        Info("", "Total number of analysed events is %i", analysed_events);
        
        continue;
      }else if(buffer.Contains("NormalisationYear")){
        conf_file >> norm_year;
        Info("", "Will be normalising for year %i", norm_year);
        continue;
        
      }else if(buffer.Contains("InputFile")){
        TString tmp_file;
        conf_file >> tmp_file;
        input_files[nfiles] = tmp_file;
        
        Info("", "Will use input file %s", input_files[nfiles].Data());
        nfiles++;
        
        continue;
      }
    }
  }else{
    Error("", "Configuration file %s not found", conf_file_name.Data());
    return -1;
    
  }

  if(eff_gen.value() ==0 || branch_fract.value()==0 || analysed_events ==0) {
    Error("","Missing parameters in configuration" );
    return -1;
    
  }
  
  if(NRwParticles != NRwFiles){
    Error("Reweighting ","Should have the same numbers of reweight particles and files ");
    return -1;
  }
  
  
  //===========================================================
  // End of configuration 

  
  TApplication theApp("App", &argc, argv);
 
  // Stuff for writing on plots 
  tex->SetNDC();
  tex->SetTextAlign(12);
  tex->SetTextFont(132);
  tex->SetTextSize(0.08);
  tex->SetLineWidth(2);

  //============================================================
  // Get file for the betas 
  TString beta_file_name = "beta/BetaParameters13_2011.txt";
  if (norm_year == 2012){
    beta_file_name = "beta/BetaParameters13_2012.txt";
  }
  if (norm_year == 2013)
  {
    beta_file_name = "beta/BetaParameters13_Comb.txt";
  }
  
  if(ana2fb){
    beta_file_name = "beta/BetaParameters2011.txt";
    if (norm_year == 2012){
      beta_file_name = "beta/BetaParameters2012.txt";
    }
  }
  
  
  Measurement beta, betas, beta_baryon, beta_bb;
  Info("","Going to get beta parameters" );
  ifstream beta_file(beta_file_name);
  if (beta_file.is_open()){
    string sbuffer;
    while (getline(beta_file,sbuffer)){
      stringstream ss(sbuffer);
      double _val, _valerr;
      if(match(sbuffer,"beta ")){
        ss >> sbuffer;
        ss >> _val;
        ss >> _valerr;
        beta = Measurement(_val, _valerr);
        Info("", "Beta is: %s", (char*)beta);
        continue;
      }else if(match(sbuffer,"betas ")){
        ss >> sbuffer;
        ss >> _val;
        ss >> _valerr;
        betas = Measurement(_val, _valerr);
        Info("", "Betas is: %s", (char*)betas);
         continue;
      }else if(match(sbuffer,"betabaryon ")){
        ss >> sbuffer;
        ss >> _val;
        ss >> _valerr;
        beta_baryon = Measurement(_val, _valerr);
        Info("", "Beta baryon is: %s", (char*)beta_baryon);
        continue;
      }else if(match(sbuffer,"betabb ")){
        ss >> sbuffer;
        ss >> _val;
        ss >> _valerr;
        beta_bb = Measurement(_val, _valerr);
        Info("", "Beta bb is: %s", (char*)beta_bb);
        continue;
      }
      
    }
    beta_file.close();
  }else{
    Error("", "Unable to open file %s", beta_file_name.Data());
    return -1;
  }
  
  Measurement beta_to_use;
  int motherID;
  switch ( eventType/1000000 ){
  case 11: // Bd
    beta_to_use = beta;
    motherID = 511;
    break;
  case 12: // B+
    beta_to_use = beta;
    motherID = 521;
    break;
  case 13: // Bs
    beta_to_use = betas;
    motherID = 531;
    break;
  case 14: // Bc
    beta_to_use = beta; //betabb has no hadronization fractions.
    branch_fract = branch_fract*Measurement(0.0593,0.0006)*
      Measurement(0.001014,0.000034)*Measurement(0.5,0.); // multiplies BR(J/Psi->mumu) & Bu->J/PsiK+ // PDG
    motherID = 541;
    break;
  case 15: //Lambda_b
    beta_to_use = beta; // And then correct for hadronisation while normalising 
    // changed to beta and use ratio 
    if(lambda_ptw_off)  beta_to_use = beta_baryon;
    
    Info("", "Going to use beta_bb for baryons and then correcting for hadronisation in normalising");
    motherID = 5122;
    break;
  default:
    Error(" ", "Not recognised beta to use for eventType %i", eventType);
    return -1;
  }
  Info("", "Beta to use is %s", (char*)beta_to_use );
  bool reweight = (NRwParticles>0);

  //============================================================
  // Define MC matching cut 
  int imup_id = 13;
  int imum_id = 13;
  
  TString smotherID(motherID);
  if(reweight){
    imup_id = rew_particleid[0];
    if(NRwParticles>1){
      imum_id += rew_particleid[1];
    }
    // The possibility of more than 2 particles is actually not supported
  }
  TString mup_id = "";
  mup_id += imup_id;
  TString mum_id = "";
  mum_id += imum_id;

  Info("","Particle IDs are %s and %s", mup_id.Data(), mum_id.Data());
  
  // Standard match 
  TString stdmcmatch = Form("(abs(muplus_TRUEID*muminus_TRUEID) == "+mum_id+"*"+mup_id+
    " && ((muplus_MC_MOTHER_ID==muminus_MC_MOTHER_ID && abs(muplus_MC_MOTHER_ID)==%i)||\
(muplus_MC_GD_MOTHER_ID==muminus_MC_MOTHER_ID && abs(muplus_MC_GD_MOTHER_ID)==%i)||\
(muplus_MC_MOTHER_ID==muminus_MC_GD_MOTHER_ID && abs(muminus_MC_GD_MOTHER_ID)==%i)))",motherID,motherID,motherID);
  // Match to take into account decays in flight
  // - One non muon particle (NRwParticles = 1)
  TString difmcmatch = "(muplus_TRUEID*muminus_TRUEID == -13*13 &&\
     ((muplus_MC_MOTHER_ID=="+mup_id+"&& muplus_MC_GD_MOTHER_ID==muminus_MC_MOTHER_ID)|| \
(muminus_MC_MOTHER_ID=="+mup_id+"&& muplus_MC_MOTHER_ID==muminus_MC_GD_MOTHER_ID)))";
  // - Two non muon particles
  //   - mup decayed
  TString difmcmatch_p = "(abs(muplus_TRUEID*muminus_TRUEID) == "+mup_id+"*13"+
    "&& ((abs(muplus_MC_MOTHER_ID)=="+mum_id+"&& muplus_MC_GD_MOTHER_ID==muminus_MC_MOTHER_ID)|| \
 (abs(muminus_MC_MOTHER_ID)=="+mum_id+" && muplus_MC_MOTHER_ID==muminus_MC_GD_MOTHER_ID)))";
  //   - mum decayed
  TString difmcmatch_m = "(abs(muplus_TRUEID*muminus_TRUEID) == "+mum_id+"*13"+
    "&& ((abs(muplus_MC_MOTHER_ID)=="+mup_id+"&& muplus_MC_GD_MOTHER_ID==muminus_MC_MOTHER_ID)|| \
 (abs(muminus_MC_MOTHER_ID)=="+mup_id+" && muplus_MC_MOTHER_ID==muminus_MC_GD_MOTHER_ID)))";

  //   - both decayed
  TString difmcmatch_b = "(muplus_TRUEID*muminus_TRUEID == -13*13 && \
  ((abs(muplus_MC_MOTHER_ID)=="+mup_id+"&& abs(muminus_MC_MOTHER_ID)=="+mum_id+") ||"+
    "(abs(muplus_MC_MOTHER_ID)=="+mum_id+"&& abs(muminus_MC_MOTHER_ID)=="+mup_id+")) && \
muplus_MC_GD_MOTHER_ID == muminus_MC_GD_MOTHER_ID)";
  
  TString mcmatch = stdmcmatch;
  if(NRwParticles ==1)      mcmatch = "("+stdmcmatch+"||"+difmcmatch+")";
  else if(NRwParticles ==2) mcmatch = "("+stdmcmatch+"||"+difmcmatch_p+
                              "||"+difmcmatch_m+"||"+difmcmatch_b+")";
  
  if(mcmatch_off)mcmatch = "1";
  
  
  Info("","MC match cut is: %s",mcmatch.Data());
  

  //============================================================
  //           Start running 
  //============================================================
  
  // ------------------------------------------------------------
  // This part is only used to estimate the equivalent luminosity of the sample
  // 
  Measurement beta_equivalent = analysed_events/(branch_fract*eff_gen);
  Measurement lumi(2.0282, 0);  // In femtobarns
  if(norm_year == 2011) lumi = Measurement(0.9707,0);// In femtobarns
  if(norm_year == 2013) lumi = Measurement(2.0282+0.9707,0);
  
  Measurement beta_here = beta_to_use;
  if(motherID==5122)beta_here *= 2*f_lambda_over_fu(5);
  Measurement lumi_equivalent =  lumi * beta_equivalent/ beta_here;
  cout << endl <<" This channel has " << analysed_events << " produced events" 
       << " with " << eff_gen << " generation efficiency " << endl;
  cout << " Equivalent beta for this channel " << beta_equivalent.tex() << endl;
  cout << " Beta in use " << beta_here.tex() << endl;
  cout << " Luminosity in use for "<< norm_year << " normalisation year " << lumi.tex() << " /fb" <<endl;
  cout << " Equivalent luminosity is " << lumi_equivalent.tex() << "/ fb "<< endl<< endl;
  // ------------------------------------------------------------
  
  ///> Define BDT bins
  const int nbdtbins = 8;
  Double_t bdtbins[nbdtbins+1] = {0, 0.25, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
  
  TH2D *h_mbdt        = new TH2D("MvsBdt", "MvsBdt", 22, 4900., 6000., nbdtbins, bdtbins);
  TH2D *h_massFit     = new TH2D("MassFit", "MassFit", 200, 4870., 6000., nbdtbins, bdtbins);
  RooRealVar * v_mass   = new RooRealVar("B_s0_M","mass", 4000,6000);
  RooRealVar * v_bdt    = new RooRealVar("BDT","bdt", 0,1);
  RooRealVar * v_w      = new RooRealVar("w","w", 0,100);
  
  RooDataSet *ds      = new RooDataSet("ds","ds", RooArgSet(*v_mass,*v_bdt));//,*v_w),"w");
  
  prefix              = Form("%i_",eventType);
  if(ana2fb) prefix += "_ana2fb_";
  fName               = Form(prefix+"Summary_%i",norm_year);

  TChain *hh  = new TChain("B2HHTuple/DecayTree");
  TChain *mm  = new TChain("B2MuMuTuple/DecayTree");
  cout << "Opening input files " << endl;
  for(int i=0; i<nfiles; i++){
    TString tmp_file = input_files[i];
    hh->Add(tmp_file);
    mm->Add(tmp_file);
    Info("","Adding input file %s",tmp_file.Data());   
  }
  
  double mm_total_entries = mm->GetEntries();
  //  double hh_total_entries = hh->GetEntries();
  cout << endl <<"   - - -     " << endl
       << "Total entries B2MuMu:            \t " << mm->GetEntries() << endl
       << "Total entries B2HH:              \t " << hh->GetEntries() << endl
       << "check total entris B2HH w isMuon \t " << 
    hh->GetEntries("muplus_isMuon==1 && muminus_isMuon==1")<< endl;
  ///> Quick fix for MC11: Choose Stripping
  TString bsmumu_strip  = (ana2fb) ? bsmumu_stripping_10 : bsmumu_stripping_12;
  if(input_files[0].Contains("MC11")) bsmumu_strip =bsmumu_stripping_12_mod;
  TString bdt = "BDT12flat";
  if(oldBDT) bdt           = (ana2fb) ? "aBDT05flat" : "bBDT05flat";

  cout << endl << "       Print cuts       " << endl;
  cout << "MC match is " << mcmatch << endl;
  cout << "Stripping is " << bsmumu_strip << endl << endl;  
  cout << "Fiducial cuts are " << bsmumu_cuts << endl<< endl;    
  cout << "Mass cut is " << bsmumu_masscut << endl<< endl;  
  cout << "Mass win is " << bsmumu_masswin << endl<< endl;  
  // Define observables: 
  double mm_raw       = mm->GetEntries();
  double mm_matched   = mm->GetEntries(mcmatch);
  double mm_mc        = mm->GetEntries(bsmumu_masscut+"&&"+mcmatch); 
  double mm_stripped  = mm->GetEntries(bsmumu_strip+"&&"+mcmatch);
  double mm_triggered = mm->GetEntries(bsmumu_trigger+"&&"+mcmatch);
  double mm_fidcuts   = mm->GetEntries(bsmumu_trigger+"&&"+bsmumu_cuts+"&&"+bsmumu_ghost+"&&"+mcmatch);
  double mm_masscut   =  
    mm->GetEntries(bsmumu_trigger+"&&"+bsmumu_cuts+"&&"+bsmumu_ghost+"&&"+bsmumu_masscut+"&&"+mcmatch);
  double mm_masscut_nt   =  
    mm->GetEntries(bsmumu_cuts+"&&"+bsmumu_ghost+"&&"+bsmumu_masscut+"&&"+mcmatch);

  TString trig_sim = "((muplus_PT > 1670) || (muminus_PT > 1670) || (muplus_PT * muminus_PT >  1600*1600))";
  double hh_masscut   = 
    hh->GetEntries(bsmumu_trigger+"&&"+bsmumu_cuts+"&&"+bsmumu_ghost+"&&"
                   +bsmumu_masscut+"&&"+mcmatch+"&& muplus_isMuon==1 && muminus_isMuon==1");
  double hh_biased   = 
    hh->GetEntries(trig_sim+"&&"+bsmumu_cuts+"&&"+bsmumu_ghost+"&&"
                   +bsmumu_masscut+"&&"+mcmatch+"&& muplus_isMuon==1 && muminus_isMuon==1");

  
  
  double hh_nofid   = 
    hh->GetEntries(trig_sim+"&&"+bsmumu_ghost+"&&"+bsmumu_masscut+"&&"+mcmatch+"&& muplus_isMuon==1 && muminus_isMuon==1");
  double hh_nofid_t   = 
    hh->GetEntries(bsmumu_trigger+"&&"+bsmumu_ghost+"&&"+bsmumu_masscut+"&&"+mcmatch+"&& muplus_isMuon==1 && muminus_isMuon==1");

 
  double mm_bsmasswin   =  mm->GetEntries(bsmumu_trigger+"&&"+bsmumu_cuts+"&&"+bsmumu_ghost+"&&"+bsmumu_masswin);
  double mm_bdmasswin   =  mm->GetEntries(bsmumu_trigger+"&&"+bsmumu_cuts+"&&"+bsmumu_ghost+"&&"+bdmumu_masswin);

  Measurement eff_bsmasswin = Measurement::GetEfficiency(mm_bsmasswin, analysed_events);
  Measurement eff_bdmasswin = Measurement::GetEfficiency(mm_bdmasswin, analysed_events);

  // total efficiencies 
  Measurement eff_trigger = Measurement::GetEfficiency(mm_masscut , mm_masscut_nt);  // Used also later.
  if(eventType==15512012) eff_trigger = Measurement::GetEfficiency(mm_triggered , mm_matched);  // Used also later.
  Measurement eff_strip   = Measurement::GetEfficiency(mm_total_entries , analysed_events);
  Measurement eff_fidcuts = Measurement::GetEfficiency(mm_fidcuts , analysed_events);
  Measurement eff_masscut = Measurement::GetEfficiency(mm_masscut , analysed_events);

  // printout 
  cout << endl  << "  Print  Bsmumu analysis    " << endl  
       << "   - - -     " << endl;
  cout << "                                 \t   Selected Events \t   Efficiency "          << endl;
  cout << "Raw entries                      \t " << mm_raw << endl;
  cout << "MC matched entries               \t " << mm_matched << endl;
  cout << "Raw entries (with masscut)       \t " << mm_mc << endl;
  cout << "After (re)stripping cross-check  \t " << mm_stripped   << " \t " << eff_strip    << endl;
  cout << "Triggered                        \t " << mm_triggered  << " \t "  << endl;
  cout << "After strip + fiducial cuts      \t " << mm_fidcuts    << " \t " << eff_fidcuts  << endl;
  cout << "After trg strip + fid + mass cut \t " << mm_masscut    << " \t " << eff_masscut  << endl;
  cout << "After strip + fidcuts + mass cut \t " << mm_masscut_nt    << " \t "  << eff_trigger << endl;
  cout << "Crosscheck: full selection in hh \t " << hh_masscut    << endl;
  cout << "Crosscheck: fullsel notrig in hh \t " << hh_biased    << endl;
  cout << "hh no fid " << hh_nofid << endl;
  cout << "hh no fid t" << hh_nofid_t << endl;
  
  
  cout << "   - - -     " << endl;

  ///> Define total efficencies
  Measurement toteff_strip      = eff_gen*eff_strip;
  Measurement toteff_fidcuts    = eff_gen*eff_fidcuts;
  Measurement toteff_masscut    = eff_gen*eff_masscut;
  Measurement toteff_bsmasswin  = eff_gen*eff_bsmasswin;
  Measurement toteff_bdmasswin  = eff_gen*eff_bdmasswin;
  ///> calc yields after each cut
  Measurement total_evt = beta_to_use * branch_fract;
  Measurement bsmasswin_evt = total_evt * toteff_bsmasswin;
  Measurement bdmasswin_evt = total_evt * toteff_bdmasswin;
  Measurement strip_evt = total_evt * toteff_strip;
  Measurement fidcut_evt = total_evt * toteff_fidcuts;
  Measurement masscut_evt = total_evt * toteff_masscut;

  cout << " ------------------------------------------------------------" << endl;
  
  cout << "Normalised total decays (beta*BR) \t\t" << total_evt << endl;
  cout << "                    \t Total Efficiency    \t Events"<< endl;
  cout << "After stripping     \t " << eff_strip*eff_gen    << " \t " << strip_evt << endl
       << "After fid cuts      \t " << eff_fidcuts*eff_gen  << " \t " << fidcut_evt <<endl
       << "After masscut       \t " << eff_masscut*eff_gen  << " \t " << masscut_evt << endl;
  
 

    
  // options to stay here 
  bool fillHoles = (!fillholes_off);

  double n_unweighted(0.), 
    n_fidcuts(0.), n_masscut(0.),
    n_bdmasswin(0), n_bsmasswin(0);


  

  Measurement w_entries(0.,0);
  Measurement w_fidcuts(0.,0);
  Measurement w_masscut(0.,0);
  Measurement w_bdmasswin(0,0);
  Measurement w_bsmasswin(0,0);
  
  TString name ="";  
  
  if(reweight){
    for(int k=0; k<NRwParticles; k++){
      Info("Reweight", "Going to reweight particle: %i", rew_particleid[k]);
    }
    
    int nentries  = hh->GetEntries();
    
    // Needed variables for the reweight: 
    double muplus_PX, muplus_PY, muplus_PZ,  muplus_PT;
    double muminus_PX,muminus_PY,muminus_PZ, muminus_PT;
    bool muplus_isMuon;
    bool muminus_isMuon;
    int muplus_TRUEID, muminus_TRUEID, muplus_MC_MOTHER_ID, muminus_MC_MOTHER_ID;
    int muplus_MC_GD_MOTHER_ID, muminus_MC_GD_MOTHER_ID;
    double B_s0_PT, B_s0_M, B_s0_TAU, muminus_P, muplus_P,
      muplus_PIDmu, muplus_PIDK, muminus_PIDmu, muminus_PIDK, B_s0_BDTS;
    double B_s0_TRUEP_X,B_s0_TRUEP_Y, B_s0_TRUEP_Z;
    
    float BDT; // Always check: float or double. 
      
    int nPVs;
    

    hh->SetBranchAddress("muplus_PX", &muplus_PX);
    hh->SetBranchAddress("muplus_PY", &muplus_PY);
    hh->SetBranchAddress("muplus_PZ", &muplus_PZ);
    hh->SetBranchAddress("muplus_PT", &muplus_PT);
    hh->SetBranchAddress("muplus_isMuon", &muplus_isMuon);

    hh->SetBranchAddress("muminus_PX", &muminus_PX);
    hh->SetBranchAddress("muminus_PY", &muminus_PY);
    hh->SetBranchAddress("muminus_PZ", &muminus_PZ);
    hh->SetBranchAddress("muminus_PT", &muminus_PT);
    hh->SetBranchAddress("muminus_isMuon", &muminus_isMuon);

    hh->SetBranchAddress("muplus_TRUEID", &muplus_TRUEID);
    hh->SetBranchAddress("muminus_TRUEID", &muminus_TRUEID);
    hh->SetBranchAddress("muplus_MC_MOTHER_ID", &muplus_MC_MOTHER_ID);
    hh->SetBranchAddress("muminus_MC_MOTHER_ID", &muminus_MC_MOTHER_ID);
    hh->SetBranchAddress("muplus_MC_GD_MOTHER_ID", &muplus_MC_GD_MOTHER_ID);
    hh->SetBranchAddress("muminus_MC_GD_MOTHER_ID", &muminus_MC_GD_MOTHER_ID);
    
    hh->SetBranchAddress("B_s0_PT", &B_s0_PT);
    hh->SetBranchAddress("B_s0_TRUEP_X",&B_s0_TRUEP_X);
    hh->SetBranchAddress("B_s0_TRUEP_Y",&B_s0_TRUEP_Y);
    hh->SetBranchAddress("B_s0_TRUEP_Z",&B_s0_TRUEP_Z);
    hh->SetBranchAddress("B_s0_TAU",&B_s0_TAU);
    hh->SetBranchAddress("B_s0_M",&B_s0_M);
    hh->SetBranchAddress("muminus_P", &muminus_P);
    hh->SetBranchAddress("muplus_P", &muplus_P);
    hh->SetBranchAddress("muplus_PIDmu", &muplus_PIDmu);   
    hh->SetBranchAddress("muplus_PIDK",&muplus_PIDK);  
    hh->SetBranchAddress("muminus_PIDmu",&muminus_PIDmu); 
    hh->SetBranchAddress("muminus_PIDK",&muminus_PIDK); 
    hh->SetBranchAddress("B_s0_BDTS", &B_s0_BDTS);
    hh->SetBranchAddress("nPVs", &nPVs);
    hh->SetBranchAddress(bdt, &BDT); // for all the possibilities 
    
    // This works also for 2011
    if(oldBDT){
      int check = hh->SetBranchAddress("bBDT05flat", &BDT);
      if(check !=0 ){
        Warning("","No branch found for bBDT05flat will try aBDT05flat");
        hh->SetBranchAddress("aBDT05flat", &BDT);
        bdt           = "aBDT05flat" ;
      }
    }
    
      


    //    int imcmatch;
    // hh->SetAlias("mcmatch",mcmatch);
    // hh->SetBranchAddress("mcmatch",&imcmatch);
    
    TTreeFormula *mytmc = new TTreeFormula("mcmatch", mcmatch.Data(), hh);
    
    Info("","Looping on events ");
    
    
    // Case with only one particle to reweight... 
    // Therefore B->hh is not included: we can think to include it for the future
    TFile *grw[NRwParticles];
    TH2D *hrw[NRwParticles];
    for(int i=0; i<NRwParticles; i++){
      grw[i] = TFile::Open(weightfilenames[i]);
      if(!grw[i]->IsOpen()){
        Error("Reweighting", "File %s not opend properly",weightfilenames[i].Data());
        return -1;
      }
      hrw[i] = (TH2D*)grw[i]->Get("w");
      if(!hrw[i]){
        Error("Reweighting", "Histogram  not found " );
        return -1;
      }
      
    }
    
    // Particle loop
    for(Int_t i = 0; i < nentries; i++){
      hh->GetEntry(i);
      // Mass cut 
      if(i%10000==0) cout <<  "... "<< i << endl;
      
      // Apply mc matching 
      if(!mcmatch_off){
        mytmc->UpdateFormulaLeaves();
        int mymcmatch = mytmc->EvalInstance();
        if(DEBUG)cout<< i <<  " | " << muplus_TRUEID << " | " << muminus_TRUEID 
                     << " | " << muplus_MC_MOTHER_ID << " | " 
                     << muminus_MC_MOTHER_ID << " \t |  mc = "<< mymcmatch  << endl;
        if(! mymcmatch)continue;
      }
      
      if(!muonTriggerSim( muplus_PT/1000 , muminus_PT/1000, norm_year))continue;
      
      double muplus_P = sqrt(muplus_PX * muplus_PX + 
                             muplus_PY * muplus_PY + 
                             muplus_PZ * muplus_PZ);
      double muminus_P = sqrt(muminus_PX * muminus_PX + 
                              muminus_PY * muminus_PY + 
                              muminus_PZ * muminus_PZ);

      
      // Weight 
      Measurement tot_weight(1.,0.);
      double average_weight = 1;
      bool passed_entry = true;
      for(int k=0; k<NRwParticles; k++){
        Measurement weight(0,0.);
        // Calculate weight for the particles to be reweighted 
        // If a particle is not to be reweighted (or badly linked), then standard PID cuts have to be applied 
        if((abs(muplus_TRUEID) == rew_particleid[k] && abs(muplus_MC_MOTHER_ID)==motherID) || 
           (abs(muplus_TRUEID)==13 && abs(muplus_MC_MOTHER_ID)== rew_particleid[k]
            && abs(muplus_MC_GD_MOTHER_ID)==motherID)){ // DIF 
          int bin = hrw[k]->FindBin( muplus_PT/1000, muplus_P/1000);
          if(fillHoles){
            bin = getSensibleBin(hrw[k], muplus_PT/1000, muplus_P/1000);
            bin =  getNonEmptyBin(hrw[k],bin);
          }
          if(bin==-1){
            Error("","Bin should not be -1");
          }
          average_weight *= 0.01* (hrw[k]->GetSumOfWeights()/ hrw[k]->GetEntries());
          

          weight = Measurement(0.01* hrw[k]->GetBinContent(bin),
                               0.01* hrw[k]->GetBinError(bin));
          
          //          cout << " (p,pt) = "<< muplus_PT << "," << muplus_P << "   w="<< weight<< endl;
          
        }else{ // Apply standard PID cuts 
          if( !(abs(muplus_TRUEID)==13 && abs(muplus_MC_MOTHER_ID)==motherID 
                    && muplus_isMuon==1 && muplus_PIDmu>-5 && muplus_PIDK<10 ) )passed_entry =false;
        }
        
        if((abs(muminus_TRUEID) == rew_particleid[k] && abs(muplus_MC_MOTHER_ID)==motherID) || 
           (abs(muminus_TRUEID)==13 && abs(muminus_MC_MOTHER_ID)== rew_particleid[k]
            && abs(muminus_MC_GD_MOTHER_ID)==motherID)){ // DIF 
          int bin = hrw[k]->FindBin( muminus_PT/1000, muminus_P/1000); 
          if(fillHoles){
            bin = getSensibleBin(hrw[k], muminus_PT/1000, muminus_P/1000);
            bin =  getNonEmptyBin(hrw[k],bin);
          }
          weight = Measurement(0.01* hrw[k]->GetBinContent(bin),
                               0.01* hrw[k]->GetBinError(bin));
          
          average_weight *= 0.01* (hrw[k]->GetSumOfWeights()/ hrw[k]->GetEntries());
        }else{ // Apply standard PID cuts 
          if( ! (abs(muminus_TRUEID)==13 && abs(muminus_MC_MOTHER_ID)==motherID 
                 && muminus_isMuon ==1 && muminus_PIDmu>-5 && muminus_PIDK<10) )passed_entry=false;
        }
         
          
        if(fillHoles){
          // This has to be changed... the average is way too much 
          if(weight==0){
            cout << "Filling holes  was " << weight ;
            weight = Measurement(0.01* (hrw[k]->GetSumOfWeights()/ hrw[k]->GetEntries()),
                                 0.01* (hrw[k]->GetSumOfWeights()/ hrw[k]->GetEntries()));
            cout << " is " << weight << endl;
            
          }
          
        }
        
        tot_weight  *= weight;
      }

      // Check that if we applied cuts to the particles they are satisfied 
      if(!passed_entry)continue;
      
      if(tot_weight  ==1 ){
        Warning("Reweighting" , "Weight is still 1, check this is OK. Particle IDs (mothers) \
are %i (%i)  %i (%i)",
                muplus_TRUEID, muplus_MC_MOTHER_ID, 
                muminus_TRUEID, muminus_MC_MOTHER_ID );
        //        cout << "IDs " << muplus_TRUEID << " " << muminus_TRUEID << endl; 
      }
      if(tot_weight.value() > 0.1){
        cout << "w " << tot_weight << endl;
        
      }
      
      // Add correction for lambda b hadronisation fraction vs. pt 
      if(motherID==5122 && !lambda_ptw_off){ // Not checking true id, just which channel we are running
        //Measurement flambda = fLambdab(B_s0_PT/1000); // this is an approximation of Lambda_b pt 
        Measurement r = f_lambda_over_fu(B_s0_PT/1000);
        
        //if(DEBUG) cout << "Flambda is " << flambda << " for pt(GeV) = " << B_s0_PT/1000 << endl;
        
        tot_weight *= 2*r; // The factor 2 comes from the measurement being flambda/(fu+fd)
        average_weight *= 2*r.value();
      }
      if(motherID==5122) { // Weighting for different q2 factors 
        double p_px = (muplus_TRUEID==2212 ? muplus_PX/1000 : muminus_PX/1000);
        double p_py = (muplus_TRUEID==2212 ? muplus_PY/1000 : muminus_PY/1000);
        double p_pz = (muplus_TRUEID==2212 ? muplus_PZ/1000 : muminus_PZ/1000);
        
        double qsquare = getLambda_q2(p_px, p_py, p_pz, 
                                      B_s0_TRUEP_X/1000,
                                      B_s0_TRUEP_Y/1000,
                                      B_s0_TRUEP_Z/1000);
        //cout << "qsquare " << qsquare << endl;
        
        Measurement q2w = getLambda_q2_weight(qsquare);
        tot_weight /= q2w;
        average_weight /= q2w.value();
        
        
      }
      if(tot_weight.value() != tot_weight.value())cout << "NAN in tot_weight " << tot_weight <<  endl;
      
      
      
      tot_weight *= calculatePVweight ( nPVs );
      


      n_unweighted++;  
      w_entries += tot_weight;
      
      if(DEBUG)cout << " tot weight is " << tot_weight << " tot entries are " << w_entries << endl;
      
      // Start with the cuts 
      
      // Fiducial cuts apart from MuID 

      // It would be nice here if we can get this cut done
      // without branch variables
      if(!(B_s0_PT>500 &&B_s0_TAU*1000.<13.248
           && muminus_P<500e03 && muplus_P<500e03 && muminus_PT<40e03
           && muplus_PT<40e03 && muplus_PT > 250 &&
           muminus_PT > 250  && B_s0_BDTS>0.05))
        continue;
      
      n_fidcuts++;  
      w_fidcuts  += tot_weight;
  
      h_massFit->Fill(B_s0_M, BDT,tot_weight.value());   // fill it before the final mass cut 
      v_mass->setVal(B_s0_M);
      //cout << tot_weight << " " << average_weight  << " " << tot_weight.value()/average_weight << endl;
      
      v_w->setVal(tot_weight.value()/average_weight);
      v_bdt->setVal(BDT);
      ds->add(RooArgSet(*v_mass,*v_bdt), tot_weight.value()/average_weight, tot_weight.error()/average_weight);
      
      if(!(B_s0_M>4900 && B_s0_M<6000))continue;
      
      n_masscut++;
      w_masscut += tot_weight;
      
      //      cout << " Adding " << tot_weight << " " << w_masscut << endl;

      if((abs(B_s0_M - 5366.3) < 60)){
        n_bsmasswin++;
        w_bsmasswin += tot_weight;
      }
      
      if((abs(B_s0_M - 5279.53) < 60)){
        n_bdmasswin++;
        w_bdmasswin += tot_weight;
      }
      
      
      
      // Fill the MvsBDT Histogram!
      // here we are not considering the weight error properly, 
      // but it is ok since the error is considered in the total yield,
      //  here we are interested in the shapes
      h_mbdt->Fill(B_s0_M, BDT,tot_weight.value());      
  
    }

    // eff_strip     = Measurement::GetEfficiency(w_entries , Measurement(analysed_events,0));
    // eff_fidcuts   = Measurement::GetEfficiency(w_fidcuts , Measurement( analysed_events,0));
    // eff_masscut   = Measurement::GetEfficiency(w_masscut , Measurement( analysed_events,0));
    // eff_bsmasswin = Measurement::GetEfficiency(w_bsmasswin , Measurement( analysed_events,0));
    // eff_bdmasswin = Measurement::GetEfficiency(w_bdmasswin , Measurement( analysed_events,0));

    eff_strip = Measurement::GetEfficiency(n_unweighted, analysed_events);
    eff_strip *= (w_entries / n_unweighted);
    cout << "Average weight is " << w_entries / n_unweighted << endl;
    
    eff_fidcuts   = Measurement::GetEfficiency(n_fidcuts , analysed_events);
    eff_fidcuts *= (w_fidcuts / n_fidcuts );

    eff_masscut   = Measurement::GetEfficiency(n_masscut , analysed_events);
    eff_masscut *= (w_masscut / n_masscut );

    eff_bsmasswin   = Measurement::GetEfficiency(n_bsmasswin , analysed_events);
    eff_bsmasswin *= (w_bsmasswin / n_bsmasswin );

    eff_bdmasswin   = Measurement::GetEfficiency(n_bdmasswin , analysed_events);
    eff_bdmasswin *= (w_bdmasswin / n_bdmasswin );
    


    cout << endl << "   - - -     " << endl;    
    cout << "                     \t  Weighted events \t Sel&Rec Efficiency " << endl;
    cout << "Total parsed entries \t " << n_unweighted<< " \t " << endl;
    cout << "Total weighted       \t" << w_entries    << " \t " << eff_strip << endl
         << "After fid cuts       \t " << w_fidcuts   << " \t " << eff_fidcuts <<  endl 
         << "After mass cut       \t" << w_masscut    << " \t " << eff_masscut <<  endl  
         << "In Bs mass win       \t" << w_bsmasswin <<   " \t " << eff_bsmasswin <<  endl  
         << "In Bd mass win       \t" << w_bdmasswin <<   " \t " << eff_bdmasswin <<  endl  ;
    
    
    cout << "Note parsed entries masscut are " << n_masscut << endl;
    cout << "   - - -     " << endl;
    
    ///> reset total efficencies

    toteff_strip      = eff_gen*eff_strip*eff_trigger;
    toteff_fidcuts    = eff_gen*eff_fidcuts*eff_trigger;
    toteff_masscut    = eff_gen*eff_masscut*eff_trigger;
    toteff_bsmasswin  = eff_gen*eff_bsmasswin*eff_trigger;
    toteff_bdmasswin  = eff_gen*eff_bdmasswin*eff_trigger;
    
    // In this case we take the trigger from before and apply the rest of the cuts only  
    strip_evt = total_evt * toteff_strip;
    fidcut_evt = total_evt * toteff_fidcuts;
    masscut_evt = total_evt * toteff_masscut;

    bsmasswin_evt = total_evt * toteff_bsmasswin;
    bdmasswin_evt = total_evt * toteff_bdmasswin;
/* ///> copy to the end of 

    cout << " ------------------------------------------------------------" << endl;
    cout << "\\toprule" << endl;
    cout << " $\\beta$               \t& " << beta_to_use.tex() << "\\\\" << endl;
    cout << " Branching fraction ($\\mathcal{B}$)\t& " << branch_fract.tex() <<  "\\\\" <<  endl;
    cout << " Normalised total decays ($\\beta\\cdot\\mathcal{B}$) \t&" << total_evt <<  "\\\\" << endl;
    cout << " $\\epsilon_{gen}$      \t& " << eff_gen.tex() <<  "\\\\" << endl;
    cout << " $\\epsilon_{trig}$  \t& " << eff_trigger.tex() <<  "\\\\" << endl;
    cout << " $\\epsilon_{sel}$ (up to a masscut)  \t& " << eff_masscut.tex() <<  "\\\\" << endl;
    cout << "\\midrule" << endl;
    cout << "                    \t&  Efficiency    \t& Events \\\\"<< endl;
    cout << "\\midrule" << endl;
    cout << "After stripping     \t& " << (eff_strip*eff_gen*eff_trigger).tex() 
         <<  " \t &" << strip_evt.tex() <<  "\\\\" << endl
         << "After fid. cuts      \t & " << (eff_fidcuts*eff_gen*eff_trigger).tex() 
         << "\t & " << fidcut_evt.tex() << "\\\\" <<  endl
         << "Mass in [4900,6000]\\mevcc  \t &" << (eff_masscut*eff_gen*eff_trigger).tex() 
         << "\t & " << masscut_evt.tex() <<  "\\\\" << endl
         << "In \\Bs masswin         \t & " << (eff_bsmasswin*eff_gen*eff_trigger).tex() 
         << "\t & " << bsmasswin_evt.tex() <<  "\\\\" << endl
         << "In \\Bd masswin         \t & " << (eff_bdmasswin*eff_gen*eff_trigger).tex() << "\t & " 
         << bdmasswin_evt.tex() <<  "\\\\" << endl;
    cout << "\\bottomrule" << endl;

    ofstream texFile("texfiles/"+fName+"_summary.tex");
    texFile << "\\begin{tabular}{llll} " << endl;
    texFile << "\\toprule" << endl;
    texFile << " $\\beta$               \t& " << beta_to_use.tex() << "\\\\" << endl;
    texFile << " Branching fraction ($\\mathcal{B}$)\t& " << branch_fract.tex() <<  "\\\\" <<  endl;
    texFile << " Normalised total decays ($\\beta\\cdot\\mathcal{B}$) \t&" << total_evt <<  "\\\\" << endl;
    texFile << " $\\epsilon_{gen}$      \t& " << eff_gen.tex() <<  "\\\\" << endl;
    texFile << " $\\epsilon_{trig}$  \t& " << eff_trigger.tex() <<  "\\\\" << endl;
    texFile << " $\\epsilon_{sel}$ (up to a masscut)  \t& " << eff_masscut.tex() <<  "\\\\" << endl;
    texFile << "\\midrule" << endl;
    texFile << "                    \t&  Efficiency    \t& Events \\\\"<< endl;
    texFile << "\\midrule" << endl;
    texFile << "After stripping     \t& " << (eff_strip*eff_gen*eff_trigger).tex() 
         <<  " \t &" << strip_evt.tex() <<  "\\\\" << endl
         << "After fid. cuts      \t & " << (eff_fidcuts*eff_gen*eff_trigger).tex() 
         << "\t & " << fidcut_evt.tex() << "\\\\" <<  endl
         << "Mass in [4900,6000]\\mevcc  \t &" << (eff_masscut*eff_gen*eff_trigger).tex() 
         << "\t & " << masscut_evt.tex() <<  "\\\\" << endl
         << "In \\Bs masswin         \t & " << (eff_bsmasswin*eff_gen*eff_trigger).tex() 
         << "\t & " << bsmasswin_evt.tex() <<  "\\\\" << endl
         << "In \\Bd masswin         \t & " << (eff_bdmasswin*eff_gen*eff_trigger).tex() << "\t & " 
         << bdmasswin_evt.tex() <<  "\\\\" << endl;
    texFile << "\\bottomrule" << endl;
    texFile << "\\end{tabular}" << endl;
*/



    ///> edit name for weighted Case
    name += Form("weighted_MvsBDT_%i.root",norm_year);  
  }
  else{
    ///> Make 2D Histogramme Mass vs BDT AND set unused histogramme to NULL pointer
    mm->Draw(bdt+":B_s0_M>>MvsBdt", bsmumu_trigger+"&&"+
             bsmumu_cuts+"&&"+bsmumu_ghost+"&&"+bsmumu_masscut , "colzN");
    mm->Draw(bdt+":B_s0_M>>MassFit", bsmumu_trigger+"&&"+
             bsmumu_cuts+"&&"+bsmumu_ghost+"&&"+bsmumu_masscut , "colzN");
    name += Form("unweighted_MvsBDT_%i.root",norm_year);  
  }

  ///> Start: calculating binned numbers
  cout  << "\n\t ==================== \t\n\t === BDT Binned numbers: === \n\t ====================== \t\n" 
        << endl;
  printBinned(masscut_evt, h_mbdt, eventType, norm_year);
  cout << "total Efficiency: ";
  if(reweight){
    cout << eff_masscut*eff_gen*eff_trigger << endl; ;
  }
  else{
    cout << eff_masscut*eff_gen << endl;
  }
  cout << "the end" << endl;
  h_massFit->SaveAs(root_out_dir+prefix+name);
  ds->SaveAs(root_out_dir+prefix+"_ds_"+name);

  fitAndPrintBinnedMass(h_massFit, useML, norm_year);
    ///> quick Bu/Bd->pimumu. (could be done smarter I guess), external input or if splitted DELETE IT!!
  Measurement bdpimumuScale(1,0);
  if(eventType == 12113023){  
    ///> This is the case for Bu/Bd --> pi mu mu 
    Measurement add(0.47, 0.22, -0.18, 1);
    bdpimumuScale+=add;
    strip_evt*=bdpimumuScale;   
    fidcut_evt*=bdpimumuScale;
    masscut_evt*=bdpimumuScale;
    bsmasswin_evt*=bdpimumuScale;
    bdmasswin_evt*=bdpimumuScale;
  }

  ///> copied from reweighing part
  cout << " ------------------------------------------------------------" << endl;
  cout << "\\toprule" << endl;
  cout << " $\\beta$               \t& " << beta_to_use.tex() << "\\\\" << endl;
  cout << " Branching fraction ($\\mathcal{B}$)\t& " << branch_fract.tex() <<  "\\\\" <<  endl;
  cout << " Normalised total decays ($\\beta\\cdot\\mathcal{B}$) \t&" << total_evt <<  "\\\\" << endl;
  cout << " $\\epsilon_{gen}$      \t& " << eff_gen.tex() <<  "\\\\" << endl;
  cout << " $\\epsilon_{trig}$  \t& " << eff_trigger.tex() <<  "\\\\" << endl;
  cout << " $\\epsilon_{sel}$ (up to mass cut)  \t& " << eff_masscut.tex() <<  "\\\\" << endl;
  cout << "\\midrule" << endl;
  cout << "                    \t&  Efficiency    \t& Events \\\\"<< endl;
  cout << "\\midrule" << endl;
  cout << "After stripping     \t& " << (toteff_strip).tex() 
       <<  " \t &" << strip_evt.tex() <<  "\\\\" << endl
       << "After fid. cuts      \t & " << (toteff_fidcuts).tex() 
       << "\t & " << fidcut_evt.tex() << "\\\\" <<  endl
       << "Mass in [4900,6000]\\mevcc  \t &" << (toteff_masscut).tex() 
       << "\t & " << masscut_evt.tex() <<  "\\\\" << endl
       << "In \\Bs masswin         \t & " << (toteff_bsmasswin).tex() 
       << "\t & " << bsmasswin_evt.tex() <<  "\\\\" << endl
       << "In \\Bd masswin         \t & " << (toteff_bdmasswin).tex() << "\t & " 
       << bdmasswin_evt.tex() <<  "\\\\" << endl;
  cout << "\\bottomrule" << endl;

  ofstream texFile("texfiles/"+fName+"_summary.tex");
  texFile << "\\begin{tabular}{llll} " << endl;
  texFile << "\\toprule" << endl;
  texFile << " $\\beta$               \t& " << beta_to_use.tex() << "\\\\" << endl;
  texFile << " Branching fraction ($\\mathcal{B}$)\t& " << branch_fract.tex() <<  "\\\\" <<  endl;
  texFile << " Normalised total decays ($\\beta\\cdot\\mathcal{B}$) \t&" << total_evt <<  "\\\\" << endl;
  texFile << " $\\epsilon_{gen}$      \t& " << eff_gen.tex() <<  "\\\\" << endl;
  texFile << " $\\epsilon_{trig}$  \t& " << eff_trigger.tex() <<  "\\\\" << endl;
  texFile << " $\\epsilon_{sel}$ (up to mass cut)  \t& " << eff_masscut.tex() <<  "\\\\" << endl;
  texFile << "\\midrule" << endl;
  texFile << "                    \t&  Efficiency    \t& Events \\\\"<< endl;
  texFile << "\\midrule" << endl;
  texFile << "After stripping     \t& " << (toteff_strip).tex() 
       <<  " \t &" << strip_evt.tex() <<  "\\\\" << endl
       << "After fid. cuts      \t & " << (toteff_fidcuts).tex() 
       << "\t & " << fidcut_evt.tex() << "\\\\" <<  endl
       << "Mass in [4900,6000]\\mevcc  \t &" << (toteff_masscut).tex() 
       << "\t & " << masscut_evt.tex() <<  "\\\\" << endl
       << "In \\Bs masswin         \t & " << (toteff_bsmasswin).tex() 
       << "\t & " << bsmasswin_evt.tex() <<  "\\\\" << endl
       << "In \\Bd masswin         \t & " << (toteff_bdmasswin).tex() << "\t & " 
       << bdmasswin_evt.tex() <<  "\\\\" << endl;
  texFile << "\\bottomrule" << endl;
  texFile << "\\end{tabular}" << endl;
  //theApp.Run();
}


///> ======================================
///> implentation of printBinned funtion...
void printBinned(Measurement NtotExp, TH2D* MvsBdt, int evtType, int norm_year){
  if(!MvsBdt){
    Error("printBinned", "Histogram MvsBdt not found");
    return;
  }
  ///> open output file if neccessary
  if(prodOutputFile){
      summaryFile.open(summary_out_dir+fName+".txt", ios::out); // at end of the file
      if(!summaryFile.is_open()){
        Error("printBinned", "Output File cannot be opened!");
        return;
      }
  }
  ///> Project on BDT -> Y projection
  TH1D* BDTprojection         = MvsBdt->ProjectionY("BDTproj",1,MvsBdt->GetNbinsX());
  Measurement selectedEvents(MvsBdt->GetSum(),0);
  
  ///> add optional factor for scaling, like Bu(d)->pi mu mu
  ///> default value is 1\pm 0... obviously ;)
  ///> has to be modified for eventual splitting of Bu, Bd --> pi mu mu
  Measurement scaleFactor(1,0);
  
  ///> define values being caculated
  Measurement NexpBin, totFrac, Nbin, NbinPrevLast;
  if(evtType!=-1 && evtType == 12113023){  
    ///> This is the case for Bu/Bd --> pi mu mu
    Measurement additional(0.47, 0.22, -0.18, 1);
    scaleFactor+=additional;
  }
  NtotExp *= scaleFactor;
  
  ///> caculate factor which scales MC events to the data expectation
  ///> idea: exp. evts. per bin = (evts per mc bin / nTotHisto)*NTotExp
  ///> this results: \sum exp evts per bin = NtotExp*(\sum (evts per mc bin / nTotHisto)) = NtotExp...check
  Measurement scaleToData     = NtotExp/selectedEvents;


  Measurement totScale      = scaleFactor;
  if(prodOutputFile && !summaryFile.is_open()){
    Error("printBinned", "ofstream closed magically?!");
    return;
  }
  
  summaryFile << NtotExp.value() << "\t\t+" << 
    NtotExp.errors()[0] << "\t\t-" << NtotExp.errors()[1] 
              << "\t # Total Yield of the component " << evtType << endl;    
  
  ///> loop over the BDT bins
  ofstream texFile("texfiles/"+fName+"_BDT_bin_yields.tex");
  printf(" BDT bin \t&\t $N_{\\text{exp}}$ \t\t&\t fraction \\\\ \\hline \n");
  texFile << "\\begin{tabular}{lll} " << endl;
  texFile << " BDT bin \t&\t $N_{\\text{exp}}$ \t\t&\t fraction \\\\ \\midrule" << endl;
  const int nbins = BDTprojection->GetNbinsX();
  for(int ii=1;ii<=nbins;ii++){
    ///> Get number of events per BDT bin from the histogramme projection
    Nbin              = Measurement(BDTprojection->GetBinContent(ii), BDTprojection->GetBinError(ii) );
    ///> calculate binned expected events
    NexpBin           = Nbin*scaleToData;
    ///> calculate fraction in bin
    totFrac           = Nbin/selectedEvents;
    ///> print result
    printf("%4i \t\t&\t %s \t&\t %s \\\\\n", ii, NexpBin.tex().c_str(), totFrac.tex().c_str());
    texFile << ii << " \t& " << NexpBin.tex() << " \t& " << totFrac.tex() <<  "\\\\"<< endl;
    ///> print stuff to file
    if(prodOutputFile && !summaryFile.is_open()){
      Error("printBinned", "ofstream closed magically?!");
      return;
    }
    
    summaryFile << totFrac.value() << "\t+" << totFrac.errors()[0] << "\t-" << totFrac.errors()[1]
                << "\t # fraction of bin " << ii << endl;
    
    if(ii==nbins){
      ///> combine 7&8 Bin
      Nbin              = Measurement(BDTprojection->GetBinContent(ii), BDTprojection->GetBinError(ii));
      NbinPrevLast      = Measurement(BDTprojection->GetBinContent(ii-1), BDTprojection->GetBinError(ii-1));
      NexpBin           = (Nbin+NbinPrevLast)*scaleToData;
      totFrac           = (Nbin+NbinPrevLast)/selectedEvents;
      printf(" 7 & 8  \t&\t %s \t&\t %s \\\\\n", NexpBin.tex().c_str(), totFrac.tex().c_str());
      texFile << " 7 \\& 8   \t& " << NexpBin.tex() << " \t& " << totFrac.tex() <<  "\\\\"<<endl;
      summaryFile << totFrac.value() << "\t+" << totFrac.errors()[0] << "\t-" << totFrac.errors()[1]
                  << "\t # fraction of bin 7+8" << endl;
      
    }
    
  
  }
  
  texFile << "\\end{tabular}" << endl;

  ///> ============================
  ///> work around for Bu->pi mu mu
  ///> check for additional scaling:
  ///> ============================
  // if(scaleFactor.value() != 1.0 ){
  //   cout << "\n======================================================" << endl;
  //   cout << "=== Scaled additional contribution (Bd-->pi mu mu) ===" << endl;
  //   cout << "======================================================" << endl;
  //   printf(" BDT bin \t&\t $N_{\\text{exp}}$ \t\t&\t fraction \\\\ \\hline \n");
  //   for(int ii=1;ii<=nbins;ii++){
  //     ///> Get number of events per BDT bin from the histogramme projection
  //     Nbin              = Measurement(BDTprojection->GetBinContent(ii), BDTprojection->GetBinError(ii) );
  //     ///> calculate binned expected events
  //     NexpBin           = Nbin*scaleToData*scaleFactor;
  //     ///> calculate fraction in bin
  //     totFrac           = NexpBin/NtotExpScale;
  //     ///> print result
  //     //cout << NexpBin.getLaTeX() << " tex string" << endl;
  //     printf("%4i \t\t&\t %s \t&\t %s \\\\\n", ii, NexpBin.tex().c_str(), totFrac.tex().c_str()); 
  //     //NexpBinTeX, totFracTeX);
  //     if(ii==nbins && norm_year == 2012){
  //       ///> combine 7&8 Bin
  //       Nbin              = Measurement(BDTprojection->GetBinContent(ii), BDTprojection->GetBinError(ii));
  //       NbinPrevLast      = Measurement(BDTprojection->GetBinContent(ii-1), BDTprojection->GetBinError(ii-1));
  //       NexpBin           = (Nbin+NbinPrevLast)*scaleToData*scaleFactor;
  //       totFrac           = NexpBin/(NtotExp*scaleFactor);
  //       printf(" 7 & 8  \t&\t %s \t&\t %s \\\\\n", NexpBin.tex().c_str(), totFrac.tex().c_str());
  //     }
  //   }
//     cout << "\n========================================================" << endl;
//     cout << "=== Total Contribution after scaling (1+scaleFactor) ===" << endl;
//     cout << "========================================================" << endl;
//     printf(" BDT bin \t&\t $N_{\\text{exp}}$ \t\t&\t fraction \\\\ \\hline \n");
//     for(int ii=1;ii<=nbins;ii++){
//       ///> Get number of events per BDT bin from the histogramme projection
//       Nbin              = Measurement(BDTprojection->GetBinContent(ii), BDTprojection->GetBinError(ii) );
//       ///> calculate binned expected events
//       NexpBin           = Nbin*scaleToData*totScale;
//       ///> calculate fraction in bin
//       totFrac           = NexpBin/NtotExpScale;
//       ///> print result
//       printf("%4i \t\t&\t %s \t&\t %s \\\\\n", ii, NexpBin.tex().c_str(), totFrac.tex().c_str());
    
//       ///> print stuff to file
//       if(prodOutputFile && !summaryFile.is_open()){
//         Error("printBinned", "ofstream closed magically?!");
//         return;
//       }
//       else{
//         summaryFile << totFrac.value() << "\t+" << totFrac.errors()[0] << "\t-" << totFrac.errors()[1]
//                     << "\t # fraction of bin " << ii << endl;
//       }
//       if(ii==nbins && norm_year == 2012){
//         ///> combine 7&8 Bin
//         Nbin              = Measurement(BDTprojection->GetBinContent(ii), BDTprojection->GetBinError(ii));
//         NbinPrevLast      = Measurement(BDTprojection->GetBinContent(ii-1), BDTprojection->GetBinError(ii-1));
//         NexpBin           = (Nbin+NbinPrevLast)*scaleToData*totScale;
//         totFrac           = NexpBin/(NtotExp*totScale);
//         printf(" 7 & 8  \t&\t %s \t&\t %s \\\\\n", NexpBin.tex().c_str(), totFrac.tex().c_str());
//         summaryFile << totFrac.value() << "\t+" << totFrac.errors()[0] << "\t-" << totFrac.errors()[1]
//                     << "\t # fraction of bin 7 + 8" << endl;
//       }
//     }
//     Measurement NtotExp2nd   = NtotExp*scaleFactor;
//     cout << "\n\t\t ----------- \n" 
//          << "\t\t ----------- \n"
//          << "\n============================================================" << endl;
//     printf( "=== Summary for Channel with Event Type: %i (%i) ===\n", evtType, norm_year); 
//     cout << "============================================================\n"
//          << endl;
//     printf("Number of expected events from inputs: %s\n", NtotExp.getLaTeX());
//     printf("Number of expected scaled events:      %s\n", NtotExp2nd.getLaTeX());
//     printf("Total Number of expected events:       %s\n", NtotExpScale.getLaTeX());
// }
  

  cout << "\n\t\t ----------- \n" 
       << "\t\t ----------- \n"
       << "\n============================================================" << endl;
  printf( "=== Summary for Channel with Event Type: %i (%i) ===\n", evtType, norm_year); 
  cout << "============================================================\n"
       << endl;
  printf("Total Number of expected events: %s\n", NtotExp.getLaTeX());
 
  BDTprojection->SaveAs(root_out_dir+Form("bdtproj_%i.root",norm_year));
  if(prodOutputFile && summaryFile.is_open()) summaryFile.close();
};

///> Function to bin mass distribution and fit these
///> takes a TChain, and an array for the binning.
///> prints out the fit result in a LaTeX formatted table
void fitAndPrintBinnedMass(TH2D* MvsBdt, Bool_t useML, int norm_year){
  if(!MvsBdt){
    Error("fitAndPrintBinnedMass", "Histogram MvsBdt not found");
    return;
  };
  if(prodOutputFile){
      summaryFile.open(summary_out_dir+fName+".txt", ios::out | ios::app); // at end of the file
      if(!summaryFile.is_open()){
        Error("fitAndPrintBinnedMass", "Output File cannot be opened!");
        return;
      }
  }

  ///> Set fit options
  TString fitOpts = useML ? "WLBIMEQS" : "BIMEQS" ; 
  if(DEBUG) fitOpts.ReplaceAll("Q","");
  
///>WLBIMEQS Sets Maximum Likelihood + Minuit, use Integral, Bound, Improved, use MINOS, Quiet, Save flags
  zstyle();
  gStyle->SetErrorX(0);
  TCanvas* c;
  cout << endl <<"=================================" << endl
         << "=== Summary for the Mass Fits ===" << endl; 
  if(useML){
    cout << "=== -Maximum Likelihood used- ===" << endl;
  }
  else{
    cout << "=== --- Chi2 Method used! --- ===" << endl;
  }
  cout  << Form("============= %i ==============", norm_year) << endl;
  cout  << "=================================\n" << endl;
  ofstream texFile("texfiles/"+fName+"_BDT_mass_par.tex");
  printf(" BDT bin \t&\t Mean \t\t&\t\t $\\sigma$ \\\\ \\hline \n");
  texFile << "\\begin{tabular}{lll} " << endl;
  texFile << " BDT bin \t&\t Mean \t\t&\t\t $\\sigma$ \\\\ \\midrule " << endl;
  
  ///> Histo-Loop
  for(int ii=1;ii<=MvsBdt->GetNbinsY(); ii++){
    ///> Define canvases and Fitfunction
    c           = new TCanvas("c","c", 800,450); ///> 16:9  canvas ratio
    ////////
    TF1* fit    = new TF1("fitFunction","gaus(0)",4000, 6000); 

    fit->SetParName(0, "Gauss Const");
    fit->SetParName(1, "Gauss Mean");
    fit->SetParName(2, "Gauss Sigma");
    //fit->SetParName(3, "Const");
    ///> just some initial values
    fit->SetParameter("Gauss Const", 30.);
    fit->SetParameter("Gauss Mean", 4900.);
    fit->SetParLimits(1, 3500., 6000); // Limits on the mean
    fit->SetParameter("Gauss Sigma", 85.);
    fit->SetParLimits(2, 40, 1000); // Limits on the sigma
    fit->SetParameter("Const", 0.1e-4);
    fit->SetParLimits(0, 0., 1000);
    
    TH1D* h;
    ///> project a single bin
    h           = MvsBdt->ProjectionX(Form("proj_bin_%i",ii),ii,ii);

    ///> edit some style stuff
    //========================
    h->SetMarkerStyle(20);
    h->SetMarkerSize(1.0);
    h->GetXaxis()->SetTitle("m( #mu^{+} #mu^{-} ) [MeV]");
    h->GetXaxis()->SetTitleSize(0.07);
    h->GetXaxis()->SetTitleOffset(1.05);
    h->GetXaxis()->SetLabelSize(0.07);
    h->GetXaxis()->SetNoExponent();
    h->GetYaxis()->SetTitle("# candidates / 25 MeV");
    h->GetYaxis()->SetTitleSize(0.07);
    h->GetYaxis()->SetTitleOffset(1.05);
    h->GetYaxis()->SetLabelSize(0.07);
    fit->SetLineWidth(2);
    fit->SetLineColor(kRed);
    //========================
    ///>

    c->cd(ii);
    h->Draw("E1");
    if(ii>1){
      //fit->FixParameter(3, 0.0);
    }
    if(h->GetEntries()==0)continue;
    
    TFitResultPtr r   = h->Fit(fit, fitOpts);
    Int_t stat = r;
    if(stat!=0 && stat != 4000){
      Warning("fitAndPrintBinnedMass", "I might something be wrong with the fit status. Please check!");
    }
    TString drawString;
    tex->SetNDC();
    tex->SetTextAlign(13);
    tex->SetTextFont(1);
    tex->SetTextSize(0.08);
    tex->SetLineWidth(2);
    
    tex->DrawLatex(0.4,0.9,TString::Format("LHCb Simulations %i    Bin %i",norm_year, ii));
    tex->SetTextSize(0.06);
    drawString = Form("Chi2 / ndf: %4.4f / %i", r->Chi2(), r->Ndf());
    tex->DrawLatex(0.4, 0.8, drawString);
    drawString = Form("Mean:        %4.4f  +-  %3.4f", r->Parameter(1), r->ParError(1));
    tex->DrawLatex(0.4, 0.7, drawString);
    drawString = Form("Sigma:       %4.4f  +-  %3.4f", r->Parameter(2), r->ParError(2));
    tex->DrawLatex(0.4, 0.6, drawString);
    drawString = Form("Constant:   %4.4f  +-  %3.4f", r->Parameter(0),r->ParError(0));
    tex->DrawLatex(0.4, 0.5, drawString);
    tex->SetTextSize(0.04);
    drawString = useML ? "Method: Maximum Likelihood" : "Method: Chi2";
    tex->DrawLatex(0.4, 0.4, drawString); 
    
    printf("    %i \t\t&\t$%F \\pm %F$ \t&\t$%F \\pm %F$\n",ii, 
           r->Parameter(1), r->ParError(1), r->Parameter(2), r->ParError(2));
    texFile << ii << " \t& " << Measurement(r->Parameter(1),  r->ParError(1)).tex() 
            << " \t& " << Measurement(r->Parameter(2),  r->ParError(2)).tex()  << "\\\\"<<endl;
    

    if(prodOutputFile && !summaryFile.is_open()){
      Error("fitAndPrintBinnedMass", "ofstream closed magically?!");
      return;
    }
    else{
      summaryFile << r->Parameter(1) << "\t\t" << r->ParError(1) << "\t\t # Mean of bin " << ii << endl;
      summaryFile << r->Parameter(2) << "\t\t" << r->ParError(2) << "\t\t # Sigma of bin " << ii << endl;
    }
    gErrorIgnoreLevel = kWarning;
    TString n = prefix;
    n += useML ? Form("ML_MassFit_bin%i_%i",ii, norm_year) : Form("Chi2_MassFit_bin%i_%i",ii, norm_year);
    c->SaveAs(plot_dir+n+".pdf");
    c->SaveAs(root_out_dir+n+".root");
    gErrorIgnoreLevel = kInfo;
    delete c;
    delete fit;
    if(ii==MvsBdt->GetNbinsY()){
          c           = new TCanvas("c","c", 800,450); ///> 16:9  canvas ratio
          TF1* fit    = new TF1("fitFunction","gaus(0)",4000, 6000); 
          fit->SetParName(0, "Gauss Const");
          fit->SetParName(1, "Gauss Mean");
          fit->SetParName(2, "Gauss Sigma");
          fit->SetParameter("Gauss Const", 30.);
          fit->SetParameter("Gauss Mean", 4900.);
          fit->SetParLimits(1, 3500., 6000); // Limits on the mean
          fit->SetParameter("Gauss Sigma", 85.);
          fit->SetParLimits(2, 40, 1000); // Limits on the sigma
          fit->SetParameter("Const", 0.1e-4);
          fit->SetParLimits(0, 0, 1000);
          
          TH1D* h;
          h           = MvsBdt->ProjectionX(Form("proj_bin_%i",ii),ii-1,ii);
          h->SetMarkerStyle(20);
          h->SetMarkerSize(1.0);
          h->GetXaxis()->SetTitle("m( #mu^{+} #mu^{-} ) [MeV]");
          h->GetXaxis()->SetTitleSize(0.07);
          h->GetXaxis()->SetTitleOffset(1.05);
          h->GetXaxis()->SetLabelSize(0.07);
          h->GetXaxis()->SetNoExponent();
          h->GetYaxis()->SetTitle("# candidates / 25 MeV");
          h->GetYaxis()->SetTitleSize(0.07);
          h->GetYaxis()->SetTitleOffset(1.05);
          h->GetYaxis()->SetLabelSize(0.07);
          fit->SetLineWidth(2);
          fit->SetLineColor(kRed);
          c->cd(ii);
          h->Draw("E1");
          TFitResultPtr r   = h->Fit(fit, fitOpts);
          Int_t stat = r;
          if(stat!=0 && stat != 4000){
            Warning("fitAndPrintBinnedMass", "I might something be wrong with the fit status. Please check!");
          }
          TString drawString;
          tex->SetNDC();
          tex->SetTextAlign(13);
          tex->SetTextFont(1);
          tex->SetTextSize(0.08);
          tex->SetLineWidth(2);
          tex->DrawLatex(0.4,0.9,TString::Format("LHCb Simulations %i  Bin 7+8",norm_year));
          tex->SetTextSize(0.06);
          drawString = Form("Chi2 / ndf: %4.4f / %i", r->Chi2(), r->Ndf());
          tex->DrawLatex(0.4, 0.8, drawString);
          drawString = Form("Mean:        %4.4f  +-  %3.4f", r->Parameter(1), r->ParError(1));
          tex->DrawLatex(0.4, 0.7, drawString);
          drawString = Form("Sigma:       %4.4f  +-  %3.4f", r->Parameter(2), r->ParError(2));
          tex->DrawLatex(0.4, 0.6, drawString);
          drawString = Form("Constant:   %4.4f  +-  %3.4f", r->Parameter(0),r->ParError(0));
          tex->DrawLatex(0.4, 0.5, drawString);
          tex->SetTextSize(0.04);
          drawString = useML ? "Method: Maximum Likelihood" : "Method: Chi2";
          tex->DrawLatex(0.4, 0.4, drawString); 
          printf(" 7 & 8  \t&\t$%F \\pm %F$ \t&\t$%F \\pm %F$\n", 
                 r->Parameter(1), r->ParError(1), r->Parameter(2), r->ParError(2));
          texFile << "7 \\& 8" << " \t& " << Measurement(r->Parameter(1),  r->ParError(1)).tex() 
                  << " \t& " << Measurement(r->Parameter(2),  r->ParError(2)).tex()  << "\\\\"<<endl;

          if(prodOutputFile && !summaryFile.is_open()){
            Error("fitAndPrintBinnedMass", "ofstream closed magically?!");
            return;
          }
          else{
            summaryFile << r->Parameter(1) << "\t\t" << r->ParError(1) << "\t\t # Mean of bin 7+8" << endl;
            summaryFile << r->Parameter(2) << "\t\t" << r->ParError(2) << "\t\t # Sigma of bin 7+8" << endl;
          }
          gErrorIgnoreLevel = kWarning;
          TString n =prefix;
          n += useML ? Form("ML_MassFit_bin78_%i", norm_year) : Form("Chi2_MassFit_bin78_%i", norm_year);
          c->SaveAs(plot_dir+n+".pdf");
          c->SaveAs(root_out_dir+n+".root");
          gErrorIgnoreLevel = kInfo;
          delete c;
          delete fit;
    }
  }
  
    texFile<< "\\end{tabular}"<< endl;
  

  Info("fitAndPrintBinnedMass", "Mass fit plots saved as *.pdf and *.root");
  if(prodOutputFile){
    summaryFile.close();
    cout <<"=====================================================" << endl 
         <<"=== Summary File created: (eventType)_Summary.txt ===" << endl
         <<"=====================================================" << endl;
  }
};


int getSensibleBin(TH2D *h, double x , double y){
  int binx = h->GetXaxis()->FindFixBin(x);
  int biny = h->GetYaxis()->FindFixBin(y);
  if(binx == 0)binx = 1;
  if(binx == h->GetNbinsX() +1) binx = h->GetNbinsX();
  if(biny == 0)biny = 1;
  if(biny == h->GetNbinsY() +1) biny = h->GetNbinsY();
  int bin =  binx +(h->GetNbinsX()+2)*biny;
  //  cout << " getsbin " << bin << " " << h->FindBin(x,y) << endl;
  return bin;
}

// Recursive function to find non empty bins 
int getNonEmptyBin(TH1 *h, int bin, int iteration)
{
  if(h->IsBinOverflow(bin) || h->IsBinUnderflow(bin) || iteration>3) return bin;
  iteration++;
  if(h->GetBinContent(bin) !=0 ) return bin;
  else{
    if(!h->IsBinOverflow(bin+1)) return getNonEmptyBin(h, bin+1, iteration);
    else if(!h->IsBinUnderflow(bin-1)) return getNonEmptyBin(h, bin-1, iteration);
    else return -1; // A one bin histogram shouldn't call this function     
  }
}

// LHCb measurement of f_lambda/(f_u+f_d)
Measurement f_lambda_over_fu(double pt){
  Measurement ptdepa(0.404, sqrt(pow(0.017,2) + pow(0.027,2)+ pow(0.105,2) ));
  Measurement ptdepb(0.031, sqrt(pow(0.004,2)+ pow(0.003,2)));
  Measurement flbr =  (ptdepa *(1 - ptdepb* pt));
  return flbr;
}



// pt dependent hadronisation fraction 
Measurement fLambdab(double pt){
  Measurement fsfd(0.256,0.020); // LHCb October 2012          
  Measurement flbr = f_lambda_over_fu(pt);
  Measurement flambdab = 1/(flbr.inverse()*(1+fsfd/2) +1);
  return flambdab;
}

double f_lambda_b_corr(double pt){
  Measurement ratio = fLambdab(pt)/fLambdab(5);
  return ratio.value();
  
} 

// Measurement calculatePTweightCorr(TH2D *hweight, TH2D *hcentroids, double p, double pt){
//   int bin = getSensibleBin(hrw[k], muplus_PT/1000, muplus_P/1000);
//   bin =  getNonEmptyBin(hrw[k],bin);
//   weight = Measurement(0.01* hweight->GetBinContent(bin),
//                        0.01* hweight->GetBinError(bin));
  

  
// }


double getLambda_q2(double p_px, double p_py,double p_pz,double l_px,double l_py,double l_pz){
  TLorentzVector proton, lambda, pair;
  proton.SetXYZM(p_px,p_py,p_pz, 0.93827);
  lambda.SetXYZM(l_px,l_py,l_pz,5.6194);
  pair = lambda - proton;
  return pair.M2();
  
  

}



Measurement  getLambda_q2_weight(double qsquare){
  Measurement weights[9];
  weights[0] =           Measurement(9.4838, 2.37174);
  weights[1] =           Measurement(4.15054,0.602319);
  weights[2] =           Measurement(2.35136, 0.190996);
  weights[3] =           Measurement(1.36817,  0.0797272);
  weights[4] =           Measurement(0.828522,  0.027045);
  weights[5] =           Measurement(0.527594,  0.0180509);
  weights[6] =           Measurement(0.33264, 0.0115299);
  weights[7] =           Measurement(0.227188,  0.00782955);
  weights[8] =           Measurement(0.175852, 0.0266922);
  
  int bin = (qsquare/2.5);
  if(bin<0)bin=0;
  if(bin>8)bin=8;
  
   // if(qsquare< 5) return Measurement(5.29699, 1.34551);
   // else if(qsquare<10) return Measurement(1.75218, 0.289815);
   // else if(qsquare<15) return Measurement(0.652362, 0.0762127);
   // else if(qsquare<20) return Measurement(0.278729, 0.0178385);
   // else return Measurement(0.207335, 0.0314708);
  //  cout << qsquare << " " << bin << endl;
  
  return weights[bin];
}


// Trigger simulation 
bool muonTriggerSim(double muplus_PT, double muminus_PT, int year=2012)
{
  double single_ptcut = (year == 2012 ? 1.67 : 1.48);
  double dimuon_ptcut = (year == 2012 ? 1.6*1.6 : 1.3*1.3);
  
  return ((muplus_PT > single_ptcut) || (muminus_PT > single_ptcut) ||
          (muplus_PT * muminus_PT > dimuon_ptcut));
  
  
}

