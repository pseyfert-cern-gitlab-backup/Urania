// Phys/Bs2JpsiKs Package
// Analyise Arguments, Name Files, Load NTuples
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################

// ####################################################################################################
// *** Load Useful Classes ***
#include "TupleLoader.h"

// ####################################################################################################
// *** Load Data ***
IB2JpsiX* loadTuple(TString module, TString decay, TString dir, TString what, 
                    unsigned int NNtype, TString weightMethod, unsigned int ttype){

  IB2JpsiX* ntuple = 0;
  // Select Supported Decay
  if ( m_B2JpsiKs == decay ){
    ntuple = loadB2JpsiKsTuple(module, decay, dir, what, NNtype, weightMethod, ttype);
  } else if ( m_B2JpsiPhi == decay ){
    ntuple = loadB2JpsiPhiTuple(module, decay, dir, what, NNtype, weightMethod, ttype);
  } else if ( m_Bu2JpsiK == decay){
    ntuple = loadBu2JpsiKTuple(module, decay, dir, what, NNtype, weightMethod, ttype);
  }

  return ntuple ;
}

// ####################################################################################################
B2JpsiKs_2011* loadB2JpsiKsTuple(TString module, TString decay, TString dir, TString what,
                                 unsigned int NNtype, TString weightMethod, unsigned int ttype){

  // *** Error Check ***
  if(decay!=m_B2JpsiKs){
    std::cout << "ERROR: Calling the wrong instance of IB2JpsiX for decay " << decay << std::endl;
    return 0;
  }
  
  // *** Construct Chain ***
  
  // Declare Stripping Line and File
  TString line  = "BetaSBd2JpsiKsDetachedLine_Tuple" ;
  TString file1 = "" ;
  TString file2 = "" ;
  
  // 1. tuple
  if (""==dir) line = "Slim_"+decay+"_Tuple";  
  else if (isSigMC(what) || what==m_IncJpsi) line = line+"MC"; 
  else if (what==m_2011LD || what==m_2012LD ) line =  "BetaSBd2JpsiKsLDDetachedLine_Tuple" ;
  else if( what==m_Prescaled ) line = "BetaSBd2JpsiKsPrescaledLine_Tuple";
  else if( what==m_Test ) line = "Bd2JpsiKsTest_Tuple";

  // 2. file
  if (dir.Contains(".root")) { // case where file name is give 
    file1 = dir ; 
    if ( m_2012_25==what )line = "Bd2JpsiKs_TupleMC";
  } 
  else if ( ""==dir ){
    file1 = dir+"B2JpsiKs-Slim-"+what+".root"; 
  } 
  else {
    if ( m_2011==what || m_2011LD==what || m_Prescaled==what){
      file1 = dir+"B2JpsiKs-R12S17b-726-732.root"; 
    } 
    else if( m_2012==what  || m_2012LD==what ) {
      file1 = dir+"Bu2JpsiK-S20-Up-759.root"; 
      file2 = dir+"Bu2JpsiK-S20-Down-760.root"; 
    }
    else if ( m_SigBd==what ){
      line = "BetaSBd2JpsiKsDetachedLine_TupleMC";
      file1 = dir+"B2JpsiKs-MC11a-Bd2JpsiKs-727.root" ;
    }  
    else if ( m_SigBs==what ){
      line = "BetaSBd2JpsiKsDetachedLine_TupleMC";
      file1 = dir+"B2JpsiKs-MC11a-Bs2JpsiKs-750-751.root" ;
    }
    else if ( m_SigBdPrescaled==what ){
      line = "BetaSBd2JpsiKsPrescaledLine_TupleMC";
      file1 = dir+"B2JpsiKs-MC11a-Bd2JpsiKs-727.root" ;
    }  
    else if ( m_SigBsPrescaled==what ){
      line = "BetaSBd2JpsiKsPrescaledLine_TupleMC";
      file1 = dir+"B2JpsiKs-MC11a-Bs2JpsiKs-750-751.root" ;
    }
    else if ( m_SigKstar==what ){
      line = "BetaSBd2JpsiKsDetachedLine_TupleMC";
      file1 = dir+"B2JpsiKs-Bd2JpsiKstar-MC11a-WM-686.root" ;
    } 
    else if ( m_SigKstarWM==what ){
      line = "Bd2JpsiKs_TupleMC";
      file1 = dir+"B2JpsiKs-Bd2JpsiKstar-MC11a-WM-686.root" ;
    } 
    else if( m_IncJpsi==what ){
      line = "BetaSBd2JpsiKsDetachedLine_TupleMC";
      file1 = dir+"B2JpsiKs-IncPsi-MC11-469.root" ;
    }
  }
  
  // *** Load Chain ***
  TChain* chain = (TChain *) loadChain(file1, file2, line, module, decay, dir, what, 
                                       NNtype, weightMethod, ttype);
  if (0==chain) return 0 ;
  // Error Analysis
  if(chain->GetEntries()==0) return 0;
  
  // *** Construct NTuple ***
  B2JpsiKs_2011* ntuple = new B2JpsiKs_2011(chain, module, dir, what, NNtype);

  return ntuple ;
}

// ####################################################################################################
B2JpsiPhi_2011* loadB2JpsiPhiTuple(TString module, TString decay, TString dir, TString what, 
                                   unsigned int NNtype, TString weightMethod, unsigned int ttype){

  // *** Error Check ***
  if(decay!=m_B2JpsiPhi){
    std::cout << "ERROR: Calling the wrong instance of IB2JpsiX for decay " << decay << std::endl;
    return 0;
  }

  // *** Construct Chain ***
  
  // Declare Stripping Line and File
  TString line  = "" ;
  TString file1 = "" ;
  TString file2 = "" ;
  
  if(what==m_2011){
    line = "BetaSBd2JpsiPhiDetachedLine_Tuple";
    file1 = dir+"B2JpsiPhi-S17-284.root";  // Out-dated?
  }
  else if(what=="LD"){
    line = "BetaSBd2JpsiPhiLDDetachedLine_Tuple" ;
    //file1 = dir+"B2JpsiKs-S17b-357.root" ;
  }
  else if(what==m_SigBs){
    line = "BetaSBd2JpsiPhiDetachedLine_TupleMC";
    //file1 = dir+"B2JpsiKs-338-SigMC11.root" ;
  }
  else if(what==m_IncJpsi){
    line = "BetaSBd2JpsiPhiDetachedLine_TupleMC";
    //file1 = dir+"B2JpsiKs-338-SigMC11.root" ;
  }
  
  // *** Load Chain ***
  TChain* chain = (TChain *) loadChain(file1, file2, line, module, decay, dir, what, NNtype, weightMethod, ttype);
  if (0==chain) return 0 ;
  // Error Analysis
  if(chain->GetEntries()==0) return 0;
  
  // *** Construct NTuple ***
  B2JpsiPhi_2011* ntuple = new B2JpsiPhi_2011(chain, module, dir, what, NNtype);

  return ntuple ;
}

// ####################################################################################################
Bu2JpsiK_2011* loadBu2JpsiKTuple(TString module, TString decay, TString dir, TString what,
                                 unsigned int NNtype, TString weightMethod, unsigned int ttype){

  // *** Error Check ***
  if(decay!=m_Bu2JpsiK){
    std::cout << "ERROR: Calling the wrong instance of IB2JpsiX for decay " << decay << std::endl;
    return 0;
  }
  
  // *** Construct Chain ***
  
  // Declare Stripping Line and File
  TString line  = "BetaSBu2JpsiKDetachedLine_Tuple" ;
  TString file1 = "" ;
  TString file2 = "" ;
  
  if (dir.Contains(".root")) { // case where file name is give 
    file1 = dir ; 
    if (what==m_SigBu || what==m_IncJpsi) line = line+"MC"; 
    if ( m_2012_25==what ) line = "Bu2JpsiK_Tuple";
  } else if(what==m_2011 && dir!=""){
    line = "BetaSBu2JpsiKDetachedLine_Tuple";
    file1 = dir+"Bu2JpsiK-R12S17b-Down-432-443.root";
    file2 = dir+"Bu2JpsiK-R12S17b-Up-434-444-462.root";
  }
  else if(what==m_2011 && dir=="") {
    line = "Slim_"+decay+"_Tuple";
    file1 = dir+"Bu2JpsiK-Slim-1-"+weightMethod+".root"; 
  }  
  else if(what==m_SigBu){
    line = "BetaSBu2JpsiKDetachedLine_TupleMC";
    //file1 = dir+"B2JpsiKs-338-SigMC11.root" ;
  }
  else if(what==m_IncJpsi){
    line = "BetaSBu2JpsiKDetachedLine_TupleMC";
    //file1 = dir+"B2JpsiKs-338-SigMC11.root" ;
  }
  else if(what==m_2012 && dir!="") {
    line = "BetaSBu2JpsiKDetachedLine_Tuple";
    file1 = dir+"Bu2JpsiK-S20-Up-759.root"; 
    file2 = dir+"Bu2JpsiK-S20-Down-760.root"; 
  }
  
  // *** Load Chain ***
  TChain* chain = (TChain *) loadChain(file1, file2, line, module, decay, dir, what, NNtype, weightMethod, ttype);
  if (0==chain) {
    std::cout << "loadChain failed" << endl ;
    return 0 ;
  }
  // Error Analysis
  if(chain->GetEntries()==0) return 0;
  
  // *** Construct NTuple ***
  Bu2JpsiK_2011* ntuple = new Bu2JpsiK_2011(chain, module, dir, what, NNtype);

  return ntuple ;
}

// ####################################################################################################
// *** Make Chain ***
TChain* loadChain(TString file1, TString file2, TString line,
                  TString module, TString decay, TString dir, TString what, 
                  unsigned int NNtype, TString weightMethod, unsigned int ttype){

  // *** Error Analysis ***
  if ( ""==file1 ) {
    std::cout << "ERROR: Did not find file-specification for " << decay << " with setting ``" << what << "''"<< std::endl ;
    return 0 ;
  }
  else {
    std::cout << "Found file: " << file1 << " for line " << line << std::endl ;
    if (""!=file2) std::cout << "Found file: " << file2 << " for line " << line << std::endl ;
  }
  
  // *** Define chain ***
  TChain* chain = new TChain((dir==""? line: line+"/DecayTree"),"");
  chain->Add(file1);
  if (""!=file2) chain->Add(file2);
  std::cout << "Total number of " << chain->GetEntries() << " entries" << std::endl ;
  
  // Error Analysis
  if(chain->GetEntries()==0){
    std::cout << "ERROR: File is not loaded properly" << std::endl;
    return 0; // Catch the error later
  }

  std::cout << NNtype << " " << module << std::endl ;
  // *** Add Friends ***
  // Load First neural net output: only needed by weighting
  if((NNtype==m_NNtype_two && module==m_weighting) || (NNtype==m_NNtype_one && module==m_branching)){
    TString coarseFile = makeFileName(m_expert, decay, m_NNtype_one,weightMethod,what,ttype,dir);
    TFile* netFile = TFile::Open(coarseFile);
    if (!netFile) return 0;
    TTree* neural_net = (TTree*)netFile->Get("NetTree");    
    if (!neural_net) return 0;
    TFriendElement* t = chain->AddFriend(neural_net);
    std::cout << "Opened " << coarseFile << " and got " << neural_net << " added as " << t << std::endl ;
    
  } 
  // Load Final neural net output: needed by analysis tools = branching and lifetime
  else if(NNtype==m_NNtype_ANA && (module==m_branching || module==m_branchingSim || module==m_lifetime)){
    TString coarseFile = makeFileName(m_expert, decay, (twoNets ? m_NNtype_two : m_NNtype_one), weightMethod,what,ttype,dir);
    TFile* netFile = TFile::Open(coarseFile);
    if (!netFile){
      // Surely this can be done better?
      std::cout << "Trying to add the random version instead" << std::endl;
      coarseFile = makeFileName(m_expert, decay, (twoNets ? m_NNtype_two : m_NNtype_one), m_random,what,ttype,dir);
      netFile = TFile::Open(coarseFile);
      if (!netFile) return 0;
    }
    TTree* neural_net = (TTree*)netFile->Get("NetTree");    
    if (!neural_net) return 0;
    TFriendElement* t = chain->AddFriend(neural_net);
    std::cout << "Opened " << coarseFile << " and got " << neural_net << " added as " << t << std::endl ;
    
  }
  // Load sWeights: needed by teacher and expert
  else if ((module==m_teacher || module==m_expert)){
    TString coarseFile = makeFileName(m_weighting, decay, NNtype,weightMethod,what,m_ANY,dir);
    TFile* weightFile = TFile::Open(coarseFile);
    if (!weightFile) return 0;
    TTree* weights = 0;
    if(ttype==m_ANY || isSigMC(what)) weights = (TTree*)weightFile->Get("WeightTree_Combi");
    else weights = (TTree*)weightFile->Get("WeightTree_Merged");    
    if (!weights) return 0;
    TFriendElement* t = chain->AddFriend(weights);
    std::cout << "Opened " << coarseFile << " and got " << weights << " added as " << t << std::endl ;
    
  }
  else std::cout << "No need to add friends" << std::endl ;
  
  // *** Return ***
  return chain;
} 

// ####################################################################################################
// *** File Naming ***
TString makeFileName(TString module, TString decay,unsigned int NNtype, TString weightMethod, 
                     TString what, int ttype, TString dir ){
  
  // Name Components
  TString level = "";
  if(module==m_weighting) level = "Weights";
  else if(module==m_expert) level = "Eval";
  else if(module==m_slimtuple) level = "Slim";
  else if(module==m_branching || module==m_branchingSim) level = "BR";
  else if(module==m_lifetime) level = "TAU";
  else if(module==m_systematics) level = "SYST";
  else if(module==m_punzi) level = "PUNZI";
  else if(module==m_mod) level = "MOD";
  else if(module==m_systematicsTau) level = "SYSTTAU";
  else level = "";
  TString TNT = (NNtype==m_NNtype_one)? TString("-1-"): ((NNtype==m_NNtype_two)? TString("-2-"): TString("-")) ;
  TString pType = "";
  if ( m_ANY != ttype ) pType = (ttype==m_DD) ? "DD-" : "LL-" ;
  TString wType = TString("-")+what;
  
  // Error Analysis
  if(level==""){
    std::cout << "ERROR: Module " << module << " is not associated with a ROOT file." << std::endl;
    return "";
  }
  
  // Return String
  TString theFile = "";
  if (dir.Contains(".root")) {
    unsigned int c = dir.Last('/');
    theFile = (dir(c+1,dir.Length()-c))  ;
    theFile = decay+"-"+theFile.ReplaceAll(".root",TString("-"+level+".root")) ;
  }
  else theFile = decay+"-"+level+TNT+pType+weightMethod+wType+TString(".root");
  if(module==m_slimtuple) theFile = decay+"-"+level+wType+TString(".root");
  std::cout << "Made File(name): " << theFile << std::endl ;  
  return theFile ;
}
// ####################################################################################################
// *** File Naming ***

void expertiseFile(char* ExpertiseFile, TString decay, unsigned int ttype, unsigned int NNtype){
  char ExpertiseFile2[256] ;
  strcpy(ExpertiseFile,decay.Data());
  sprintf(ExpertiseFile2,"-%i-%i.nb", ttype, NNtype);
  strcat(ExpertiseFile,ExpertiseFile2);
  std::cout << "Made File(name): " << ExpertiseFile << std::endl;
}

// ####################################################################################################
// *** Analyse Arguments ***
int decodeArgs(TString& module, TString& decay, unsigned int& NNtype, TString& dir, TString& weightMethod,
               unsigned int& ttype,TString& what,int argc, char** argv){
  
  // *** Error Analysis ***
  int error = 0;
  if (( argc <2 ) || (TString(argv[1])=="--help") || (TString(argv[1])=="--h")){
    error = 1 ;
  } else {
  
    module       = TString(argv[0]);
    decay        = TString(argv[1])  ;
    what         = argc > 2 ? TString(argv[2]) : m_2011 ;
    dir          = argc > 3 ? TString(argv[3]) : m_castor ;
    unsigned int defNN = (m_branching==module || module==m_branchingSim || m_lifetime==module )? m_NNtype_ANA : m_NNtype_one;
    NNtype       = argc > 4 ? atoi(argv[4])    : defNN ;  
    weightMethod = argc > 5 ? TString(argv[5]) : m_random ;
    ttype        = argc > 6 ? atoi(argv[6])    : m_ANY ;
    
    // Cross-Checks: Valid Input
    if(!( m_B2JpsiKs==decay || m_B2JpsiPhi==decay || m_Bu2JpsiK==decay)){
      std::cout << "ERROR: Unsupported decay channel = " << decay << std::endl;
      error = -1;
    }
    if(!( m_NNtype_one==NNtype || m_NNtype_two==NNtype || m_NNtype_ANA==NNtype)){
      std::cout << "ERROR: Unknown NN type = " << NNtype << std::endl;
      error = -2;
    }    
    if(!( m_castor==dir || m_local==dir)){
      std::cout << "WARNING: Unknown data directory = " << dir << std::endl;
    }
    if(!(m_downscaled==weightMethod || m_random==weightMethod || m_weighted==weightMethod || m_noweight==weightMethod)){
      std::cout << "ERROR: Unknown weighting method " << weightMethod << std::endl;
      error = -4;
    }
    if(!( m_ANY==ttype || m_LL==ttype || m_DD==ttype)){
      std::cout << "ERROR: Unknown track type " << ttype << std::endl;
      error = -5;
    }
    if(!( m_2011==what || isSigMC(what) || m_SigBu
    || m_IncJpsi==what || m_2012==what || m_Prescaled==what || m_2011LD==what || m_2012LD==what || m_Test==what )){
      std::cout << "ERROR: Unknown data type " << what << std::endl;
      error = -6;
    }
    // Cross-Checks: Match NNtype with module
    if(m_NNtype_two==NNtype && !twoNets){
      std::cout << "ERROR: This NN type " << NNtype << " does not match the predefined settings: Use Two NN? " << 
	(twoNets==0 ? "false" : "true") << std::endl;
      error = -10;
    }
    if(m_NNtype_ANA==NNtype && (module!=m_branching && module!=m_branchingSim && module!=m_lifetime)){
      std::cout << "ERROR: This NN type " << NNtype << " is only for analysis modules and not supported by the current Module "
                << module << std::endl;
      error = -10;
    }
    if((NNtype!=m_NNtype_ANA && (module==m_branchingSim || m_lifetime==module)) || (NNtype==m_NNtype_two && m_branching==module)){
      std::cout << "ERROR: The analysis modules should use NN type " << m_NNtype_ANA << " in order to load all files correctly."
		            << std::endl;
      error = -10;
    }
    
    // Set Directory
    if (dir==m_castor){ // data can be read from castor
      dir = "/castor/cern.ch/user/p/pkoppenb/B2JpsiKs/";
    } else if (dir==m_local){ // data can be read locally
      dir = "";
    }
    // *** Result of Decoding ***
    std::cout << "###################################################" << std::endl ;
    if(error==0){std::cout << "Successfully decoded arguments " << std::endl ;}
    else{std::cout << "FAILED to decode arguments " << std::endl ;}
    std::cout << "  module is           ``" << module << "''" << std::endl;
    std::cout << "  decay is            ``" << decay << "''" << std::endl ; 
    std::cout << "  EventType is        ``" << what << "''" << std::endl ; 
    std::cout << "  directory is        ``" << dir << "''" << std::endl ; 
    std::cout << "  NNtype is           ``" << NNtype << "''" << std::endl ; 
    std::cout << "  weighting method is ``" << weightMethod << "''" << std::endl ; 
    std::cout << "  track type is       ``" << ttype << "''" << std::endl ; 
    std::cout << "###################################################" << std::endl ;
  }

  // *** Error Messages ***
  if(error!=0 && error>-10) help(argv[0]);
  
  return error;
}

// ####################################################################################################
void help(std::string module){
    std::cout << std::endl;
    std::cout << "HELP: Function should be called as" << std::endl;
    std::cout << module << " [decay] [EventType] [dir] [NN] [weight] [TT]" << std::endl ;
    std::cout << "Where:" <<
      "\n ``decay'' specifies which decay channel to run. Supported: " << 
      m_B2JpsiKs << ", " << m_B2JpsiPhi << ", " << m_Bu2JpsiK <<
      "\n ``EventType'' specifies the settings. Supported: " << m_2011 << " (d), " << m_2012 << ", " << m_SigBd
        << " (and Bs, Bu and Prescaled), " << m_IncJpsi <<
      "\n ``dir'' is the data directory. Supported: " << m_castor << " (d), " << m_local << ", or any directory " <<  
      "\n ``NN'' is the Neural Net iteration. Supported: " << m_NNtype_one << " (d), " << m_NNtype_two << ", " << m_NNtype_ANA <<
      "\n ``weight'' is the weighting method. Supported: " 
        << m_random << " (d), " << m_weighted << ", " << m_downscaled << ", " << m_noweight <<
      "\n ``TT'' is the track type. Supported: " << m_ANY << " (d), " << m_LL << ", " << m_DD <<
      ", " << m_Prescaled <<  ", " << m_Test << std::endl ;
    std::cout << std::endl;

}

// ####################################################################################################
double printFrac(Long64_t n){ return n>0 ? 1./int(sqrt(sqrt(1.0*n))):1 ;} ;

// ####################################################################################################
