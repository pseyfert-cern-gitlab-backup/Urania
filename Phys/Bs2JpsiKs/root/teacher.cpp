// ####################################################################################################
// Phys/Bs2JpsiKs Package
// Neural Net Teacher
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################

// ####################################################################################################
// *** Load Useful Classes ***

// General C++ && Root
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <string>
#include "TString.h"
#include <TVector3.h>
#include <TH1F.h>
#include <TFile.h>

// Bs2JpsiKs Package
#include "IB2JpsiX.h"
#include "TupleLoader.h"

// NeuroBayes
#include "NeuroBayesTeacher.hh"
#include "NeuroBayesExpert.hh"


// ####################################################################################################
// *** Declarations ***
void analysis(string FileName = "teacherHistos.root",const char* PSFileName = "analysis.ps", 
               int sort=0, const char* correlSigniFile = "correl_signi.txt");

// ####################################################################################################
// *** Teacher ***
int TrainTeacher(const TString module, const TString decay, unsigned int ttype,
                 TString weightMethod, TString what, TString dir, unsigned int NNtype){

// ***** PART 0: Initialise ***** //
////////////////////////////////////

  // *** Load Data ***
  IB2JpsiX* ntuple = loadTuple(module, decay, dir, what, NNtype, weightMethod, ttype);
  
  // Error Analysis
  if(!ntuple) return -1;


// ***** PART I: Initialise NeuroBayes ***** //
///////////////////////////////////////////////
  
  std::cout << "\n PROGRESS: Initialising NeuroBayes Teacher \n" << std::endl; 

  // Prepare Ntuple
  unsigned int nvar = ntuple->nVar(decay,NNtype,ttype);
  float* InputArray = new float[nvar]; // array to hold input data
  ntuple->firstFill = true;

  // *** NeuroBayes ***
  // NOTE: Teacher must run on lxplus! (due to Licence)
  std::cout << " * Create Instance" << std::endl;
  NeuroBayesTeacher* nb = NeuroBayesTeacher::Instance();

  std::cout << " * Settings" << std::endl;
  // Settings
  nb->NB_DEF_NODE1(nvar+1);        // nodes in input layer
  nb->NB_DEF_NODE2(nvar);          // nodes in hidden layer
  nb->NB_DEF_NODE3(1);             // nodes in output layer
  nb->NB_DEF_TASK("CLA");          // binominal classification
  //nb->NB_DEF_SHAPE("DIAG");        // force to diagonal     DOES NOT WORK WITH SPLOT
  nb->NB_DEF_REG("ALL");           // 'OFF','REG' (def) ,'ARD','ASR','ALL'
  nb->NB_DEF_LOSS("ENTROPY");      // 'ENTROPY'(def),'QUADRATIC'
  nb->NB_DEF_ITER(1000);           // number of training iteration   TRY 0
  nb->NB_DEF_METHOD("BFGS");       // will stop automatically if there's nothing more to learn
  nb->NB_DEF_LEARNDIAG( 1 );       // BFGS
  //nb->NB_DEF_PRE(212);             // flatten and de-correlate input variables, keep only variables with >1 sigma significance
  //nb->NB_DEF_PRE(612);             // flatten and de-correlate input variables, keep only variables with >3 sigma significance
  nb->NB_DEF_PRE(1012);            // flatten and de-correlate input variables, keep only variables with >5 sigma significance
  
  // Individual preprocessing flags
  // 14,34: Continuous Variables: flatten input variable && regularised spline fit to mean of target && no delta function
  // 15,35: same as 14, but perform monotonous fit
  // 18,38: Discrete Variables: flatten input variable && no delta function, unordered class 
  // 19,39: same as 18, but ordered class
  // 3X : Deal with delta functions at -999

  for ( unsigned int i = 0 ; i!=nvar ; i++){
    nb->SetIndividualPreproFlag(i,ntuple->individualPreproFlag(i));
  }
  
  // Output
  char ExpertiseFile[256] ;
  expertiseFile(ExpertiseFile,decay,ttype,NNtype);
  cout << "Will put the Expertise in " << ExpertiseFile << endl;
  nb->SetOutputFile(ExpertiseFile);  // expert file


  // *** Load Array ***
  std::cout << "\n PROGRESS: Feeding NeuroBayes Teacher \n" << std::endl;
  const Long64_t nentries = ntuple->nEntries();
  Long64_t nFailed = 0;
  Long64_t nKillMuCa = 0;
  Long64_t nKillMuPV = 0;
  Long64_t nGood = 0; 
  Long64_t nNonTeach = 0; 
  Long64_t nTeach = 0 ;
  
  Double_t sweight = -999;

  std::cout << " * Will loop over " << nentries << std::endl;

  double frac = printFrac(nentries);  
  for (Long64_t i=0; i<nentries;i++) {
    ntuple->GetChain()->GetEntry(i);
    
    // Progress
    if(0==i%((int)(frac*nentries))) std::cout << " |-> " << i << " / " << nentries 
					      << " (" << 100*i/nentries << "%)" << std::endl; 
    
    // Get Data
    unsigned int npv = ntuple->primaries();
    for (unsigned int pv=0 ; pv!=npv ; ++pv){
      sweight = ntuple->weightVal(pv) ;
      // Select Teaching Sample
      if(sweight==ErrorCodes::FailsCuts || (ttype!=0 && ntuple->TrackType()!=ttype)){ 
        nFailed++;
        continue;
      } else if(sweight==ErrorCodes::KilledMuCa){
        nKillMuCa++;
        continue;
      } else if(sweight==ErrorCodes::KilledMuPV){
        nKillMuPV++;
        continue;
      } else if(sweight>=-1){
        nGood++;
        if(!ntuple->teacherSample()){ // Exclude Part of sample for final fit
          nNonTeach++;
          continue;    
        } else if(!ntuple->teachingRegion(pv)){ // Exclude Signal region
          nNonTeach++;
          continue;    
        } else{ // Events for Teacher
          nTeach++;

          // Feed Teacher
          ntuple->prepareArray(nvar, InputArray, pv, ttype);
          nb->SetTarget(sweight) ; 
          nb->SetNextInput(nvar,InputArray);     
        
          // Error Analysis
          if (nTeach>= NB_MAXPATTERN - 3*(nvar+1)){ // 1499985
            std::cout << "ERROR: Used " << nTeach << "/" << NB_MAXPATTERN - 3*(nvar+1) << " events." 
		                  << " Exiting before NeuroBayes kills the job" << std::endl;
            break ;
          }
        }
      } else {
        // Error Analysis
        std::cout << "WARNING: read sweight " << sweight << " Will treat it as Failed Cuts." << std::endl; 
        nFailed++;
      }
    } // pv
  }

  // *** Results ***
  std::cout << "++++++++++++++++++++ results ++++++++++++++++++++" << std::endl ;
  std::cout << "     # events failing selection cuts: " << nFailed << std::endl;
  std::cout << "     # Multiple Candidates Killed   : " << nKillMuCa << std::endl;
  std::cout << "     # Multiple (B,PV) pairs Killed : " << nKillMuPV << std::endl;
  std::cout << "     # good events                  : " << nGood << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  std::cout << "     # events used for Teaching     : " << nTeach << std::endl; 
  std::cout << "     # events excluded from Teaching: " << nNonTeach << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;

  
// ***** PART II: Train NeuroBayes ***** //
///////////////////////////////////////////
  
  std::cout << "\n PROGRESS: Training NeuroBayes Teacher \n" << std::endl;
  nb->TrainNet();

// ***** PART II: Return ***** //
/////////////////////////////////
  std::cout << "\n PROGRESS: Teaching Finished! \n" << std::endl;
  //delete nb;
  return 0 ;
} 


// ####################################################################################################
// *** Teach && Process ***
int trainOnce(const TString module, const TString decay, unsigned int ttype,
              TString weightMethod, TString what, TString dir, unsigned int NNtype){

  int teachout = TrainTeacher(module, decay, ttype, weightMethod, what, dir, NNtype);
  // Error Analysis
  if (teachout!=0) return teachout;
    
  // *** Process Results ***
  std::cout << "\n PROGRESS: Processing Results \n" << std::endl;
  // Make save string
  char pdfString[100] = "";  
  strcpy(pdfString,decay.Data());  
  char pdfTail[100] = "";  
  sprintf(pdfTail,"-analysis-%i-%i.pdf", ttype, NNtype);
  strcat(pdfString,pdfTail);
  // Process
  analysis("ahist.txt",pdfString);
  
  std::cout << "\n PROGRESS: Finished! \n" << std::endl;
  return 0;
}

// ####################################################################################################
// *** Main ***
int main(int argc, char** argv) {

  // *** Decode Arguments ***
  TString module, decay, dir, weightMethod, what;
  unsigned int NNtype, ttype;
  int out = decodeArgs(module, decay, NNtype, dir, weightMethod, ttype, what, argc, argv);
  // Error Analysis
  if (out != 0) return out ;

  // *** Main Function ***
  if(ttype==m_ANY) return trainOnce(module, decay, m_ANY, weightMethod, what, dir, NNtype);
  else{
    // Somehow this runs into an error with NeuroBayes while preprocessing DD sample.
    // We do not get two instances, the first one is re-used
    //out += trainOnce(module, decay, m_LL, weightMethod, what, dir, NNtype);
    //out += trainOnce(module, decay, m_DD, weightMethod, what, dir, NNtype);
    
    out += trainOnce(module, decay, ttype, weightMethod, what, dir, NNtype);
    return out;
  }
}
