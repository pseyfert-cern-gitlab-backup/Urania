// ####################################################################################################
// Phys/Lambdab Package
// Neural Net Expert
// Authors: Patrick Koppenburg
// ####################################################################################################

/*
foreach a ( `nsls $CASTOR_HOME/Lambdab | grep root`)
  set root = `echo $a | awk -F. '{print $1}'`
  echo $root
  ./expert.exe $CASTOR_HOME/Lambdab/$a | tee expert-${root} &
end
*/

// ####################################################################################################
// *** Load Useful Classes ***

// General C++ && Root
#include <iostream>
#include "TObject.h"
#include "TFile.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH2D.h"
#include "TString.h"

// local Package
#include "Lambdab.h"
#include "Tuples.h"
#include "MultipleCandidates.h"

// NeuroBayes
#include "NeuroBayesExpert.hh"
static const unsigned int c_PiBins = 144; // (10+2)*(10+2)
static const unsigned int c_KBins = 144;  // (10+2)*(10+2)
double c_PiMCWeight[c_PiBins]= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1.19259, -0.466767, 0.320144, 1.82297, 0, 0, 0, 0, 0, 0, 0, 0.246238, 1.03979, 0.469918, -0.213585, -0.15482, -0.338207, 0.136204, 0, 0, 0, 0, 0, 1.03759, 1.01909, 0.614937, 0.0068019, -0.0940086, -0.0870351, 0.0397639, 0.29541, 0.268071, 0, 0, 0, 1.49275, 1.92398, 2.96543, 0.575071, 0.0406724, 0.0300444, 0.325253, -0.00803388, 0.0240618, 0.427225, 0, 0, 4.37688, 2.8471, 2.38607, 0.848485, 0.509259, -0.0730889, 0.214139, -0.0264016, -0.0290784, 0.151433, 0, 0, 6.11969, 3.51174, 2.32215, 0.534393, -0.0516525, -0.0392459, 0.135846, 0.386999, 0.21985, 0.5273, 0, 0, 2.1955, 5.22527, 3.36751, 0.581198, 0.123069, 0.173208, 0.590739, 0.275603, 0.488924, 0.445175, 0, 0, 0, 4.32117, 3.20405, 1.99854, 0.638345, 0.383617, 0.70093, 0.284849, 0.371644, 0, 0, 0, 0, 1.33778, 5.36237, 4.04646, 1.46851, 1.22627, 0.432889, 0.936338, 0, 0, 0, 0, 0, 0, 4.36533, 6.23568, 0.956228, 1.18641, 9.63815, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
double c_KMCWeight[c_KBins]= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.478467, 0.287423, -0.0365866, 0, 0, 0, 0, 0, 0, 0, 0, 0.511514, 0.708485, 0.20674, 0.143397, 0.0819982, 0.0499014, 0.130307, 0, 0, 0, 0, 6.56573, 0.78266, 0.645979, 0.226656, 0.222081, 0.119158, 0.151718, 0.164706, 0.105085, -0.188567, 0, 0, 4.73918, 1.25297, 0.88257, 0.257419, 0.21203, 0.14678, 0.143073, 0.167968, 0.0612371, 0.139937, 0, 0, 5.03227, 1.74277, 1.08383, 0.436258, 0.193153, 0.11691, 0.20453, 0.277236, 0.350747, 0.309682, 0, 0, 4.72616, 2.68089, 1.28528, 0.611691, 0.207369, 0.289043, 0.449887, 0.383583, 0.377391, 0.365822, -12.2298, 0, 4.7508, 3.71951, 2.14641, 1.47928, 0.542804, 0.507505, 0.37131, 0.321805, 0.240034, 0.0396781, 0, 0, 11.7402, 5.42117, 3.60734, 1.84096, 0.688941, 0.409903, 0.386273, 0.349808, 0.144216, -4.90162, 0, 0, 0, 5.34774, 4.18737, 2.52022, 1.53863, 1.09506, 0.68846, 0.55299, 0, 0, 0, 0, 0, 0, 4.07631, 3.19, 1.40136, 1.11104, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
TH2D c_hK("c_hK","c_hK",   10,1.9e6,6.5e6,10,12.0e6,22.5e6);
TH2D c_hPi("c_hPi","c_hPi",10,1.0e6,6.5e6,10,10.0e6,22.5e6);
// ####################################################################################################
// *** MC weight ***
double mcWeight(double massX, double massY, bool pion){
  double w = 0 ;
  int bin = 0 ;
  if (pion){
    bin = c_hPi.FindBin(massX,massY);
    w = c_PiMCWeight[bin];
  } else {
    bin = c_hK.FindBin(massX,massY);
    w = c_KMCWeight[bin];
  }
  //  if (w==0) std::cout << pion << " " << massX << " " << massY << " bin " << bin << " has weight " << w << std::endl ;
  return w>0?w:0. ;
}
// ####################################################################################################
// *** Expert ***
int CreateExpertTree(const TString fullname, const TString type){
  
  // ***** PART 0: Initialise ***** //
  ////////////////////////////////////
  // *** Load Data ***
  Lambdab* ntuple = new Lambdab(fullname,"",type);
  if(!ntuple) return -1;
  
  unsigned int lastslash = fullname.Last('/');
  TString plotfilename = fullname(lastslash+1,fullname.Length()-lastslash-1);
  plotfilename = plotfilename.ReplaceAll(".root","-NN.root") ;
  if ("ppi"!=type) plotfilename = plotfilename.ReplaceAll(".root","-"+type+".root") ;
  std::cout << plotfilename << std::endl ;
  TFile* outfile = new TFile( plotfilename, "RECREATE" );
  outfile->cd();


  // ***** PART I: Create Tree ***** //
/////////////////////////////////////
  
  std::cout << " PROGRESS: Creating Tree " << std::endl; 

  // Histograms  
  TH1F* h_net = new TH1F("h_net","Net Output",100,-1.0,1.0);  
  h_net->Sumw2();

  // *** Initialise ***
  Double_t netOutput[100];
  Double_t PsippiMass[100];
  //  Float_t PsippiMassErr[10];
  Double_t pMMass2[100];
  Double_t psiMMass2[100];
  Double_t psipMass2[100];
  Double_t PsipKMass[100];
  Double_t PsiKpiMass[100];
  Double_t MCWeight[100];
  Int_t category[100] ;
  Int_t ErrorCode[100] ;
  Int_t baryon = true ;
  float* InputArray = new float[nvar]; // array to hold input data
  unsigned int nVar = 0 ;/// I can't pass a static const as variable
  int bkgCat = 0 ;
  bool teaching = false ;
  unsigned int nPV  = 0 ;
  ULong64_t eventNumber = 0 ;
  UInt_t runNumber = 0;

   // Tree
  TTree outtree("NetTree","Neural Net Tree");
  outtree.Branch("PVs",&nPV, "PVs/I");
  outtree.Branch("EventNumber",&eventNumber, "EventNumber/l");
  outtree.Branch("RunNumber",&runNumber, "RunNumber/i");
  outtree.Branch( c_NetOutput,&netOutput, c_NetOutput+"[PVs]/D");
  outtree.Branch( c_PsippiMass,&PsippiMass, c_PsippiMass+"[PVs]/D");
  outtree.Branch( c_PsipKMass ,&PsipKMass, c_PsipKMass+"[PVs]/D");
  outtree.Branch( c_PsiKpiMass ,&PsiKpiMass, c_PsiKpiMass+"[PVs]/D");
  outtree.Branch("pMMass2",&pMMass2, "pMMass2[PVs]/D");
  outtree.Branch("psiMMass2",&psiMMass2, "psiMMass2[PVs]/D");
  outtree.Branch("psipMass2",&psipMass2, "psipMass2[PVs]/D");
  outtree.Branch(c_Category ,&category, c_Category+"[PVs]/I");
  outtree.Branch(c_ErrorCode ,&ErrorCode, c_ErrorCode+"[PVs]/I");
  outtree.Branch(c_Baryon,&baryon, c_Baryon+"/I");
  if (ntuple->MC()) outtree.Branch("BKGCAT",&bkgCat, "BKGCAT/I");
  if (ntuple->MC()) outtree.Branch("MCWeight",&MCWeight, "MCWeight[PVs]/D");
  outtree.Branch("Teaching", &teaching , "Teaching/B");  

  //  outtree.Branch("PsippiMassErr",&PsippiMassErr, "PsippiMassErr/F");
  // pi p mass calculate here and add to ntuple
  outtree.SetDirectory(outfile); 
  
  // *** NeuroBayes ***
  // Prepare Ntuple
  
  std::cout << " PROGRESS: Preparing NeuroBayes Expert" << std::endl; 
  
  // Read File
  char ExpFile[256] = "Lambdab.nb";// N-Alex: AHA! So this is where data from the teacher comes in :D
  Expert* NeuroBayesExpert  = new Expert(ExpFile);
  std::cout << " * Expert will be using file: " << ExpFile  << std::endl ;
  
  // *** Fill Tree ***
  std::cout << " PROGRESS: Running NeuroBayes Expert" << std::endl; 
  const Long64_t nentries = ntuple->fChain->GetEntries();
  Long64_t nTotal = 0;
  Long64_t nFailed = 0;
  Long64_t nFailTrigger = 0;
  Long64_t nKilled = 0;
  Long64_t nGood = 0;
  Long64_t npK = 0;
  Long64_t nSignal = 0;
  Long64_t nVeto = 0;
  Long64_t nMultiPV = 0;
  Long64_t nNonBestPV = 0;
 
  std::cout << " * Will loop over " << nentries << " entries" << std::endl;

  double frac = printFrac(nentries);  
  bool tSample = (!ntuple->MC() || fullname.Contains("Inc")) ;
  if (tSample) std::cout << "This is a teaching sample " << fullname << std::endl ;
  
  for (Long64_t i=0; i<nentries;i++) {
    ntuple->fChain->GetEntry(i);
    nVar = nvar ; /// I can't pass a statis const as variable
    runNumber = ntuple->runNumber;
    eventNumber = ntuple->eventNumber;
   
    // Progress
    if(0==i%((int)(frac*nentries))) std::cout << " |-> " << i << " / " 
                                              << nentries << " (" << 100*i/nentries << "%)" << std::endl; 
  
    baryon = (ntuple->pplus_ID>0)?1:-1;
    if (ntuple->MC()) {
      bkgCat = ntuple->B_BKGCAT ;
      if (30==bkgCat && abs(ntuple->pplus_TRUEID)==2212 && abs(ntuple->piminus_TRUEID)==321 
          && abs(ntuple->muplus_TRUEID)==13 && abs(ntuple->muminus_TRUEID)==13) bkgCat = c_psipK_BKGCAT ; // psipK
      // std::cout << "Background Category " << ntuple->B_BKGCAT << " becomes " <<  bkgCat << std::endl ;
    }
    teaching = ntuple->teaching(!tSample);
    nPV = ntuple->nPV ;
    unsigned int passC = 0 ;
    for ( unsigned int pv = 0 ; pv!= nPV ; ++pv){    
      nTotal++ ;
      PsippiMass[pv] = (ntuple->B_FullFit_M[pv]>0)?ntuple->B_FullFit_M[pv]:0.  ;
      if (PsippiMass[pv]>10000) PsippiMass[pv] = 10000 ;
      PsipKMass[pv] = ntuple->B_SubpK_M[pv] ;
      PsiKpiMass[pv] = ntuple->B_SubKpi_M[pv] ;
      pMMass2[pv] = ntuple->pMMass2(pv);
      psiMMass2[pv] = ntuple->psiMMass2(pv);
      if (ntuple->MC()) MCWeight[pv]=mcWeight(pMMass2[pv],psiMMass2[pv],ntuple->isPion());
      psipMass2[pv] = ntuple->psipMass2(pv);
      ntuple->prepareArray(nvar, InputArray,pv);
    // std::cout << InputArray[0] << " " << InputArray[1] << " " << InputArray[2] << std::endl ;
      bool isGood = false ;
      category[pv] =  ErrorCodes::FailsCuts ; // make sure nothing bad happens
      netOutput[pv] =  ErrorCodes::FailsCuts ; // make sure nothing bad happens
      ErrorCode[pv] =  ErrorCodes::FailsCuts ; // make sure nothing bad happens
      if (!ntuple->preselection(pv)){
        nFailed++;
      } else { // 
        netOutput[pv] = NeuroBayesExpert->nb_expert(InputArray);
        if (!ntuple->trigger()){
          nFailTrigger++;
          ErrorCode[pv] = ErrorCodes::FailsTrigger; 
        } else {
          nGood++ ;
          passC++ ;
          if (0!=pv) nNonBestPV++ ;
          ErrorCode[pv] = ErrorCodes::OK ; 
          h_net->Fill(netOutput[pv]); // only for triggered events
          isGood = true ; // good guy
        }
        if ( ntuple->AtLambdaMass()){
          category[pv] =  CatCodes::Lambda ;
          if (isGood) nVeto++ ;
        } else if ( !(ntuple->PassesMassVetoes(pv)) ) { // Vetoes
          category[pv] =  CatCodes::Reflection ;
          if (isGood) nVeto++ ;
        } else if ( ntuple->isKaon() ) { // normalisation channel
          category[pv] = CatCodes::pKCand ;
          if (isGood) npK++ ;
        } else { // pion
          category[pv] = CatCodes::SignalCand ;
          if (isGood) nSignal++ ;
        } 
      }
    }
    if (passC>1) nMultiPV++ ;
    // Store Result
    outtree.Fill() ;
  }
  
  // *** Results ***
  std::cout << "++++++++++++++++++++ results ++++++++++++++++++++" << std::endl ;
  std::cout << "     # events                          : " << nentries << std::endl;
  std::cout << "     #   (Lb,PV) pairs                 : " << nTotal << std::endl;
  std::cout << "     #   pairs failing selection cuts  : " << nFailed << std::endl;
  std::cout << "     #   pairs failing trigger         : " << nFailTrigger << std::endl;
  std::cout << "     #   good candidate pairs          : " << nGood << std::endl;
  std::cout << "     #     Vetoed candidates           : " << nVeto << std::endl;
  std::cout << "     #     Signal candidates           : " << nSignal << std::endl;
  std::cout << "     #     PsipK candidates            : " << npK << std::endl;
  std::cout << "     #     Good pairs with non-best PV : " << nNonBestPV << std::endl;
  std::cout << "     #  Multiple good pairs            : " << nMultiPV << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl ;
  

  // *** Write to file ***
  std::cout << " PROGRESS: Writing File " << std::endl; 

  outfile->cd();
  outtree.Write();
  h_net->Write();
  outfile->Close();

// ***** PART II: Return ***** //
/////////////////////////////////
  std::cout << " PROGRESS: Finished! " << std::endl;
  return 0 ;
} 

// ####################################################################################################
// *** Main ***
int main(int argc, char** argv) {

   if(argc<2){
    std::cout << "ERROR: Insufficient arguments given" << std::endl;  
    std::cout << "./expert.exe /castor/cern.ch/user/p/pkoppenb/Lambdab/Lambdab-R12S17b-721.root" 
              << " [ Lambda ] | tee test-expert" << std::endl;  
    return -9;
  }

  // *** Decode Arguments ***
  TString fullname = TString(argv[1]);  
  TString type = (argc==3)?TString(argv[2]):"ppi";
  // *** Main Function ***
  return CreateExpertTree(fullname,type);
}
// ####################################################################################################

