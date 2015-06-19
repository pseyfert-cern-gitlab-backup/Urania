// ####################################################################################################
// Phys/Bs2JpsiKs Package
// Neural Net Expert
// Authors: Patrick Koppenburg & Kristof De Bruyn
// ####################################################################################################

// ####################################################################################################
// *** Load Useful Classes ***

// General C++ && Root
#include <iostream>
#include "TObject.h"
#include "TFile.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH1F.h"

// Bs2JpsiKs Package
#include "IB2JpsiX.h"
#include "TupleLoader.h"

// NeuroBayes
#include "NeuroBayesExpert.hh"


// ####################################################################################################
// *** Expert ***
int CreateExpertTree(const TString module, const TString decay, const TString plotfilename, unsigned int ttype,
                     TString weightMethod, TString what, TString dir, unsigned int NNtype, TString doWhat){
                       
// ***** PART 0: Initialise ***** //
////////////////////////////////////

  // *** Initialise ***
  TFile* outfile = new TFile( plotfilename, "RECREATE" );
  outfile->cd();

  // *** Load Data ***
  IB2JpsiX* ntuple = 0;
  
  if(doWhat=="Merge") ntuple = loadTuple(module, decay, dir, what, NNtype, weightMethod, m_LL);
  else ntuple = loadTuple(module, decay, dir, what, NNtype, weightMethod, ttype);
  
  // Error Analysis
  if(!ntuple) {
    help("expert.exe");
    return -1;
  }
// ***** PART I: Create Tree ***** //
/////////////////////////////////////
  
  std::cout << "\n PROGRESS: Creating Tree \n" << std::endl; 

  // *** Initialise ***
  Float_t netOutput[10] ;
  Float_t sweight[10] ;
  Double_t FullFitMass[10] ;
  Double_t FullFitMassErr[10] ;
  Double_t tau[10];
  ULong64_t eventNumber = 0 ;
  UInt_t runNumber = 0;
  unsigned int nPV  = 0 ;
  Int_t mytrack = 0;

  // Histograms  
  TH1F* h_net = new TH1F("h_net","Net Output",100,-1.0,1.0);  
  h_net->Sumw2();

  // Tree
  TTree* outtree = new TTree("NetTree","Neural Net Tree");
  outtree->Branch("nPV2",&nPV, "nPV2/I");
  outtree->Branch("EventNumber",&eventNumber, "EventNumber/l");
  outtree->Branch("RunNumber",&runNumber, "RunNumber/i");
  outtree->Branch("netOutput",&netOutput, "netOutput[nPV2]/F");
  outtree->Branch("tracktype",&mytrack, "tracktype/I");
  outtree->Branch("FullFitMass",&FullFitMass, "FullFitMass[nPV2]/D");
  outtree->Branch("FullFitMassErr",&FullFitMassErr, "FullFitMassErr[nPV2]/D");
  outtree->Branch("WeightVal",&sweight, "WeightVal[nPV2]/F");
  outtree->Branch("Tau",&tau, "Tau[nPV2]/D");
  outtree->SetDirectory(outfile); 
  
  // *** NeuroBayes ***
  // Prepare Ntuple
  unsigned int nvar = ntuple->nVar(decay,NNtype,(doWhat=="Merge" ? m_LL : ttype));
  float* InputArray = new float[nvar]; // array to hold input data
  ntuple->firstFill = true;
  
  std::cout << "\n PROGRESS: Preparing NeuroBayes Expert \n" << std::endl; 
  
  // Read File
  char ExpFile_LL[256];
  expertiseFile(ExpFile_LL,decay,(doWhat=="Merge" ? m_LL : ttype),NNtype);
  Expert* NeuroBayesExpert_LL = new Expert(ExpFile_LL);

  char ExpFile_DD[256];
  Expert* NeuroBayesExpert_DD = 0;
  if(doWhat=="Merge"){
    expertiseFile(ExpFile_DD,decay,m_DD,NNtype);
    NeuroBayesExpert_DD = new Expert(ExpFile_DD);
    std::cout << " * Expert will be using file: " << ExpFile_LL << " and " << ExpFile_DD << std::endl ;
  }
  else std::cout << " * Expert will be using file: " << ExpFile_LL << std::endl ;

  // *** Fill Tree ***
  std::cout << "\n PROGRESS: Running NeuroBayes Expert \n" << std::endl; 
  const Long64_t nentries = ntuple->nEntries();
  Long64_t nFailed = 0;
  Long64_t nGood = 0;
  unsigned int ownPV ;
  
  std::cout << " * Will loop over " << nentries << std::endl;

  double frac = printFrac(nentries);  
  for (Long64_t i=0; i<nentries;i++) {
    ntuple->GetChain()->GetEntry(i);
    runNumber = ntuple->getRunNumber();
    eventNumber = ntuple->getEventNumber();
    mytrack = ntuple->TrackType();
    // Progress
    if(0==i%((int)(frac*nentries))) std::cout << " |-> " << i << " / " 
					      << nentries << " (" << 100*i/nentries << "%)" << std::endl; 
    
    nPV = ntuple->primaries() ;
    for ( unsigned int pv = 0 ; pv!= nPV ; ++pv){
      FullFitMass[pv] = ntuple->mass(pv) ;
      FullFitMassErr[pv] = ntuple->massErr(pv) ;
      tau[pv] = ntuple->time(pv);
      sweight[pv] = ntuple->weightVal(pv) ;
      if ( sweight[pv]!=ErrorCodes::FailsCuts ){
        if(doWhat=="Merge"){
          ntuple->prepareArray(nvar, InputArray, pv, m_LL);
          if(mytrack==m_LL) netOutput[pv] = NeuroBayesExpert_LL->nb_expert(InputArray);
          else if(mytrack==m_DD) netOutput[pv] = NeuroBayesExpert_DD->nb_expert(InputArray);
          else netOutput[pv] = ErrorCodes::Error;
        }
        else{
          ntuple->prepareArray(nvar, InputArray, pv, ttype);
          netOutput[pv] = NeuroBayesExpert_LL->nb_expert(InputArray);
        }
        nGood++;
        h_net->Fill(netOutput[pv]);   
      } else {
        netOutput[pv] = sweight[pv];
        nFailed++ ;
      }
    } // pvs
    outtree->Fill() ;
  }
  
  // *** Results ***
  std::cout << "++++++++++++++++++++ results ++++++++++++++++++++" << std::endl ;
  std::cout << "     # events failing selection cuts: " << nFailed << std::endl;
  std::cout << "     # good events                  : " << nGood << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  

  // *** Write to file ***
  std::cout << "\n PROGRESS: Writing File \n" << std::endl; 

  outfile->cd();
  outtree->Write();
  h_net->Write();
  outfile->Close();

// ***** PART II: Return ***** //
/////////////////////////////////
  std::cout << "\n PROGRESS: Finished! \n" << std::endl;
  return 0 ;
} 

// ####################################################################################################
// *** Main ***
int main(int argc, char** argv) {

  // *** Decode Arguments ***
  TString module, decay, dir, weightMethod, what;
  unsigned int NNtype, ttype;
  int out = decodeArgs(module, decay, NNtype, dir, weightMethod, ttype, what, argc, argv);
  // Extra argument
  TString doWhat = (argc > 7 ? TString(argv[7]) : "Combi");
  std::cout << "Extra Arguments" << std::endl;
  std::cout << "  run option is: " << doWhat << std::endl;
  std::cout << "###################################################" << std::endl;
  // Error Analysis
  if (out != 0) return out ;
  if(!(doWhat=="Combi" || doWhat=="Merge")){
    std::cout << "ERROR: Unknown run option: " << doWhat << std::endl;
    return -255;
  }
  if(doWhat=="Merge" && ttype!=m_ANY){
    std::cout << "ERROR: Need both LL and DD to merge! Use tracktype 0 instead" << std::endl;
    return -255;
  }
  
  TString eFile = makeFileName(module,decay,NNtype,weightMethod,what,ttype,dir);
  // Error Analysis
  if (""==eFile) {
    std::cout << "ERROR: Failed to generate file." << std::endl;
    return -255 ;
  }
   
  // *** Main Function ***
  return CreateExpertTree(module, decay, eFile, ttype, weightMethod, what, dir, NNtype, doWhat);
}
// ####################################################################################################
