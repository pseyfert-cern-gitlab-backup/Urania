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
#include "MultipleCandidates.h"

using namespace std ;

// NeuroBayes
#include "NeuroBayesTeacher.hh"
#include "NeuroBayesExpert.hh"

// ####################################################################################################
// *** Declarations ***
int loop(Lambdab* ntuple, int signal, NeuroBayesTeacher* nb){
  
  bool debug = false ;

  // Prepare Ntuple
  float* InputArray = new float[nvar]; // array to hold input data

  double target = signal ;
  
  // *** Load Array ***
  std::cout << "\n PROGRESS: Feeding NeuroBayes Teacher \n" << std::endl;
  const Long64_t nentries = (debug?1000:ntuple->fChain->GetEntries());
  Long64_t nFailed = 0;
  Long64_t nGood = 0;
  Long64_t nKilled = 0; 
  Long64_t nNonTeach = 0; 
  Long64_t nMuCa = 0; 

  std::cout << " * Will loop over " << nentries << " entries" << std::endl;

  double frac = printFrac(nentries);  
  for (Long64_t i=0; i<nentries;i++) {
    ntuple->fChain->GetEntry(i);
    target = (TrainingType::Weighted==signal? ntuple->tweightLb[0] : signal) ;
    
    // Progress
    if(debug || 0==i%((int)(frac*nentries))){
      std::cout << " |-> " << i << " / " << nentries << " (" << 100*i/nentries 
                << "%) Good : " << nGood 
                << " (" << (nGood>0?int(10000.*nGood/i+0.5)/100.:0) << "%) sweight: " << target << std::endl;  
    }
    
    if (!ntuple->preselection(0,debug)){ // only pv 0 considered
      nFailed++;
    } else if (!ntuple->teaching(signal,debug)){
      nNonTeach++;
    } else if (target==ErrorCodes::KilledMuCa){
      nMuCa++;
    } else if (target<ErrorCodes::KilledMuCa){
      cout << "ERROR: Candidate " << i << " has sweight " << target << endl ;
      return -12 ;
    } else {
      nGood++ ;
      if (debug) cout << "New candidate " << nGood << " with target " << target << std::endl ;
      // Feed Teacher
      ntuple->prepareArray(nvar, InputArray,0,debug); // Tuple.icpp pv =0
      nb->SetTarget( target  ) ; 
      nb->SetNextInput(nvar,InputArray);     
      /*
      if (nGood>= NB_MAXPATTERN - 3*(nvar+1)){ // 1499985
        std::cout << "ERROR: Used " << nGood << "/" << NB_MAXPATTERN - 3*(nvar+1) << " events." 
                  << " Exiting before NeuroBayes kills the job" << std::endl;
        break ;
      }
      */
    } 
  }

  // *** Results ***
  std::cout << "++++++++++++++++++++ results ++++++++++++++++++++" << std::endl ;
  std::cout << "     # events failing selection cuts: " << nFailed << std::endl;
  std::cout << "     # Multiple Candidates Killed   : " << nKilled << std::endl;
  std::cout << "     # Outside of Teaching Region   : " << nNonTeach << std::endl;
  std::cout << "     # Killed Multiple Candidates   : " << nMuCa << std::endl;
  std::cout << "     # good events                  : " << nGood << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  if (0==nGood) return -1;
  return 0;
}

// ####################################################################################################
// *** Declarations ***
void analysis(string FileName = "teacherHistos.root",const char* PSFileName = "analysis.ps", 
               int sort=0, const char* correlSigniFile = "correl_signi.txt");

// ####################################################################################################
// *** Teacher ***
int TrainTeacher(TString fullname1, TString fullname2, TString opt){

  // ***** PART 0: Initialise ***** //
  ////////////////////////////////////

  // *** Load Data ***
  Lambdab* ntuple1 = 0 ;
  Lambdab* ntuple2 = 0 ;
  bool useMC = false ;
  if ( "MC"==opt ){
    ntuple1 = new Lambdab(fullname1,"","","ppi");
    ntuple2 = new Lambdab(fullname2,"","","ppi");
    // Error Analysis
    if(!ntuple1) return -1;
    if(!ntuple2) return -2;
    useMC = true ;
  } else {
    ntuple1 = new Lambdab(fullname1,"",opt,"ppi"); /// can add another full name. 3rd arg is friend.
    if (""!=fullname2) ntuple2 = new Lambdab(fullname2,"",opt,"ppi"); /// can add another full name. 3rd arg is friend.
    if(!ntuple1) return -1;
  }

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
  nb->NB_DEF_PRE(612);             // flatten and de-correlate input variables, 
                                   // keep only variables with >3 sigma significance
  
  // Individual preprocessing flags
  // 14,34: Continuous Variables: flatten input variable && regularised spline 
  //          fit to mean of target && no delta function
  // 15,35: same as 14, but perform monotonous fit
  // 18,38: Discrete Variables: flatten input variable && no delta function, unordered class 
  // 19,39: same as 18, but ordered class
  // 3X : Deal with delta functions at -999
  
  for ( unsigned int i = 0 ; i!=nvar ; i++){
    nb->SetIndividualPreproFlag(i,ntuple1->individualPreproFlag(i));
  }
  
  // Output
  char ExpertiseFile[256] = "Lambdab.nb";  
 

  cout << "Will put the Expertise in " << ExpertiseFile << endl;
  nb->SetOutputFile(ExpertiseFile);  // expert file
  
  int ok = 0;
  if (useMC){
    ok = loop(ntuple1,TrainingType::Signal,nb);
    if (0!=ok) return ok;
    ok = loop(ntuple2,TrainingType::Background,nb);
    if (0!=ok) return ok;
  } else {
    loop(ntuple1,TrainingType::Weighted,nb);
    if (0!=ok) return ok;
    if (ntuple2) loop(ntuple2,TrainingType::Weighted,nb);
    if (0!=ok) return ok;
  }
  
  
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
    std::cout << "./teacher.exe [ /castor/cern.ch/user/p/pkoppenb/Lambdab/LambdabMC-MC11-Lb2Jpsippi-716.root" 
              << " /castor/cern.ch/user/p/pkoppenb/Lambdab/LambdabMC-MC11-IncPsi-717.root ] | [ "
              << " /castor/cern.ch/user/p/pkoppenb/Lambdab/Lambdab-S20-982.root " 
              << " /castor/cern.ch/user/p/pkoppenb/Lambdab/Lambdab-S20r1-980.root All-SW ] " 
              << "  | tee test-teach" << std::endl;  
    return -9;
  }

  // *** Decode Arguments ***
  TString fullname1 = TString(argv[1]);
  TString fullname2 = TString(argv[2]);
  TString opt = (argc>3)?TString(argv[3]):"";
  if ( !fullname2.Contains(".root") ){
    opt = fullname2 ;
    fullname2 = "";
  }
  if (""==opt) opt = "MC" ;
  
  std::cout << "Configured teacher with file1: ``" << fullname1 << "'', file2 ``" 
            << fullname2 << "'', opt ``" << opt << "''" << std::endl ;

  // *** Main Function ***
  int teachout = TrainTeacher(fullname1, fullname2, opt);
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
