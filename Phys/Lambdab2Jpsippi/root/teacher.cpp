// ####################################################################################################
// Neural Net Teacher
// Authors: Patrick Koppenburg
// ####################################################################################################

// ####################################################################################################
// *** Load Useful Classes **

// General C++ && Root
#include "TString.h"
#include <TVector3.h>
#include <TH1F.h>
#include <TFile.h>

// Lambdab2JPsippi Package
#include "Lambdab.h"
#include "Tuples.h"

using namespace std ;

// NeuroBayes
#include "NeuroBayesTeacher.hh"
#include "NeuroBayesExpert.hh"


// ####################################################################################################
// *** Declarations ***
void loop(Lambdab* ntuple, bool signal, NeuroBayesTeacher* nb){
  // Prepare Ntuple
  float* InputArray = new float[nvar]; // array to hold input data

  double target = (signal?1:-1) ;
  
  // *** Load Array ***
  std::cout << "\n PROGRESS: Feeding NeuroBayes Teacher \n" << std::endl;
  const Long64_t nentries = ntuple->fChain->GetEntries();
  Long64_t nFailed = 0;
  Long64_t nGood = 0;
  Long64_t nKilled = 0; 
  Long64_t nNonTeach = 0; 
  
  std::cout << " * Will loop over " << nentries << std::endl;

  double frac = printFrac(nentries);  
  for (Long64_t i=0; i<nentries;i++) {
    ntuple->fChain->GetEntry(i);
    
    // Progress
    if(0==i%((int)(frac*nentries))) std::cout << " |-> " << i << " / " << nentries 
                                              << " (" << 100*i/nentries << "%)" << std::endl;  

    if (!preselection(ntuple)){
      nFailed++;
    } else if (!teaching(ntuple,signal)){
      nNonTeach++;
    } else {
      nGood++ ;
      // Feed Teacher
      prepareArray(nvar, InputArray, ntuple); // Tuple.cpp
      nb->SetTarget( target  ) ; 
      nb->SetNextInput(nvar,InputArray);     
      
    } 
  }

  // *** Results ***
  std::cout << "++++++++++++++++++++ results ++++++++++++++++++++" << std::endl ;
  std::cout << "     # events failing selection cuts: " << nFailed << std::endl;
  std::cout << "     # Multiple Candidates Killed   : " << nKilled << std::endl;
  std::cout << "     # Outside of Teahing Region    : " << nNonTeach << std::endl;
  std::cout << "     # good events                  : " << nGood << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
}

// ####################################################################################################
// *** Declarations ***
void analysis(string FileName = "teacherHistos.root",const char* PSFileName = "analysis.ps", 
               int sort=0, const char* correlSigniFile = "correl_signi.txt");

// ####################################################################################################
// *** Teacher ***
int TrainTeacher(TString fullname1, TString fullname2){

  // ***** PART 0: Initialise ***** //
  ////////////////////////////////////

  // *** Load Data ***
  Lambdab* ntuple1 = new Lambdab(fullname1);
  Lambdab* ntuple2 = new Lambdab(fullname2);
  
  // Error Analysis
  if(!ntuple1) return -1;
  if(!ntuple2) return -2;


// ***** PART I: Initialise NeuroBayes ***** //
///////////////////////////////////////////////
  
  std::cout << "\n PROGRESS: Initialising NeuroBayes Teacher \n" << std::endl; 

  // *** NeuroBayes ***
  // NOTE: Teacher must run on lxplus! (due to Licence)
  NeuroBayesTeacher* nb = NeuroBayesTeacher::Instance();

  // Settings
  nb->NB_DEF_NODE1(nvar+1);        // nodes in input layer
  nb->NB_DEF_NODE2(nvar);          // nodes in hidden layer
  nb->NB_DEF_NODE3(1);             // nodes in output layer
  nb->NB_DEF_TASK("CLA");          // binominal classification
  //  nb->NB_DEF_SHAPE("DIAG");        // force to diagonal     DOES NOT WORK WITH SPLOT
  nb->NB_DEF_REG("ALL");           // 'OFF','REG' (def) ,'ARD','ASR','ALL'
  nb->NB_DEF_LOSS("ENTROPY");      // 'ENTROPY'(def),'QUADRATIC'
  nb->NB_DEF_ITER(1000);           // number of training iteration   TRY 0
  nb->NB_DEF_METHOD("BFGS");       // will stop automatically if there's nothing more to learn
  nb->NB_DEF_LEARNDIAG( 1 );       // BFGS
  nb->NB_DEF_PRE(212);             // flatten and de-correlate input variables, 
                                   // keep only variables with >1 sigma significance
  
  // Individual preprocessing flags
  // 14,34: Continuous Variables: flatten input variable && regularised spline 
  //          fit to mean of target && no delta function
  // 15,35: same as 14, but perform monotonous fit
  // 18,38: Discrete Variables: flatten input variable && no delta function, unordered class 
  // 19,39: same as 18, but ordered class
  // 3X : Deal with delta functions at -999
  
  for ( unsigned int i = 0 ; i!=nvar ; i++){
    nb->SetIndividualPreproFlag(i,individualPreproFlag(i));
  }
  
  // Output
  char ExpertiseFile[256] = "Lambdab.nb";  
 

  cout << "Will put the Expertise in " << ExpertiseFile << endl;
  nb->SetOutputFile(ExpertiseFile);  // expert file
  
  loop(ntuple1,true,nb);
  loop(ntuple2,false,nb);
  
// ***** PART II: Train NeuroBayes ***** //
///////////////////////////////////////////
  
  std::cout << "\n PROGRESS: Training NeuroBayes Teacher \n" << std::endl;
  nb->TrainNet();

// ***** PART II: Return ***** //
/////////////////////////////////
  std::cout << "\n PROGRESS: Teaching Finished! \n" << std::endl;
  return 0 ;
} 


// ####################################################################################################
// *** Main ***
int main(int argc, char** argv) {

  if(argc<3){
    std::cout << "ERROR: Insufficient arguments given" << std::endl;  
    std::cout << "./teacher.exe /castor/cern.ch/user/p/pkoppenb/Lambdab/Lambdab2Jpsippi-MC11a-Psippi-521.root" 
	      << "  /castor/cern.ch/user/p/pkoppenb/Lambdab/Lambdab2Jpsippi-MC11a-IncPsi-501.root" 
              << "  | tee test-teach" << std::endl;  
    return -9;
  }

  // *** Decode Arguments ***
  TString fullname1 = TString(argv[1]);
  TString fullname2 = TString(argv[2]);

  // *** Main Function ***
  int teachout = TrainTeacher(fullname1, fullname2);
  // Error Analysis
  if (teachout!=0) return teachout;
  
  // *** Process Results ***
  std::cout << "\n PROGRESS: Processing Results \n" << std::endl;
  // Make save string
  char pdfString[100] = "Lambdab.pdf";  
  analysis("ahist.txt",pdfString);
  
  std::cout << "\n PROGRESS: Finished! \n" << std::endl;
  return 0;
}
