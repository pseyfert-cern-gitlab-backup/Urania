// ####################################################################################################
// Phys/Lambdab Package
// Neural Net Expert
// Authors: Patrick Koppenburg
// ####################################################################################################

// ####################################################################################################
// *** Load Useful Classes ***

// General C++ && Root
#include <iostream>
#include "TObject.h"
#include "TFile.h"
#include "TBranch.h"
#include "TTree.h"
#include "TString.h"

// local Package
#include "Lambdab.h"
#include "Tuples.h"
#include "MultipleCandidates.h"
#include "TRandom2.h"

// NeuroBayes
#include "NeuroBayesExpert.hh"
#include "weights.h"
// ####################################################################################################
// *** Expert ***
int CreateExpertTree(const TString fullname, const TString type){
  
  bool debug = false ;
  // ***** PART 0: Initialise ***** //
  ////////////////////////////////////
  // *** Load Data ***
  Lambdab* ntuple = new Lambdab(fullname,"","",type);
  if(!ntuple) return -1;
  
  TRandom2* m_rndm = new TRandom2(m_theSeed); // 0 : use time
  m_rndm->SetSeed(m_theSeed);
  fillFluctuateBins(m_rndm);

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

  static const unsigned int PVS = (ntuple->MC()?1:100);
  TString pvs = (ntuple->MC()?"":"[PVs]");
  std::cout << "PVs ``" << pvs << "''" << std::endl ;

  // *** Initialise ***
  Double_t netOutput[PVS];
  Double_t PsippiMass[PVS];      // The pion stream mass
  Double_t PsipKMass[PVS];       // The kaon stream mass
  Double_t PsiKpiMass[PVS];      // p->K gets Bd->J/psiKpi in pion stream
  Double_t PsipiKMass[PVS];      // p->pi gets Bd->J/psipiK in kaon stream
  Double_t PsiKKMass[PVS];       // p->K gets Bs->J/psiKK in kaon stream
  Double_t PsiKpMass[PVS];       // p->K and K->p gets Lb->J/psiKp in kaon stream  
  //  Float_t PsippiMassErr[10];
  Double_t pMMass2[PVS];         
  Double_t psiMMass2[PVS];
  Double_t psipMass2[PVS];
  Double_t KKMass[PVS];
  Double_t DalitzWeight[PVS];
  Double_t DalitzWeight2[PVS];
  Double_t DalitzWeightWE[PVS];
  Double_t NNEffWeight[PVS];
  Double_t SPDWeight;
  Double_t PTWeight ;
  Double_t PTWeight2 ;
  Double_t PTWeight2WE ;
  Double_t CPWeight ;
  Double_t mprime[PVS];
  Double_t thetaprime[PVS];
  Double_t CosTheta[PVS];
  Int_t category[PVS] ;
  Int_t ErrorCode[PVS] ;
  Int_t baryon = true ;
  float* InputArray = new float[nvar]; // array to hold input data
  unsigned int nVar = 0 ;/// I can't pass a static const as variable
  int bkgCat = 0 ;
  int pptid = 0 ;
  bool teaching = false ;
  unsigned int nPV  = 0 ;
  ULong64_t eventNumber = 0 ;
  UInt_t runNumber = 0;

   // Tree
  TTree outtree("NetTree","Neural Net Tree");
  outtree.Branch("PVs",&nPV, "PVs/I");
  outtree.Branch("EventNumber",&eventNumber, "EventNumber/l");
  outtree.Branch("RunNumber",&runNumber, "RunNumber/i");
  outtree.Branch( c_NetOutput,&netOutput, c_NetOutput+pvs+"/D");
  outtree.Branch( c_PsippiMass,&PsippiMass, c_PsippiMass+pvs+"/D");
  outtree.Branch( c_PsipKMass ,&PsipKMass, c_PsipKMass+pvs+"/D");
  outtree.Branch( c_PsiKpiMass ,&PsiKpiMass, c_PsiKpiMass+pvs+"/D");
  outtree.Branch( c_PsipiKMass ,&PsipiKMass, c_PsipiKMass+pvs+"/D");
  outtree.Branch( c_PsiKKMass ,&PsiKKMass, c_PsiKKMass+pvs+"/D");
  outtree.Branch( c_PsiKpMass ,&PsiKpMass, c_PsiKpMass+pvs+"/D");
  outtree.Branch("pMMass2",&pMMass2, "pMMass2"+pvs+"/D");
  outtree.Branch("psiMMass2",&psiMMass2, "psiMMass2"+pvs+"/D");
  outtree.Branch("psipMass2",&psipMass2, "psipMass2"+pvs+"/D");
  outtree.Branch("KKMass",&KKMass, "KKMass"+pvs+"/D");
  outtree.Branch("mprime",&mprime, "mprime"+pvs+"/D");
  outtree.Branch("thetaprime",&thetaprime, "thetaprime"+pvs+"/D");
  outtree.Branch(c_Category ,&category, c_Category+pvs+"/I");
  outtree.Branch(c_ErrorCode ,&ErrorCode, c_ErrorCode+pvs+"/I");
  outtree.Branch(c_Baryon,&baryon, c_Baryon+"/I");
  if (ntuple->MC()) {
    outtree.Branch(c_BKGCAT,&bkgCat, c_BKGCAT+"/I");
    outtree.Branch(c_pTrueID,&pptid, c_pTrueID+"/I");
    outtree.Branch(c_DalitzWeight,&DalitzWeight, "DalitzWeight"+pvs+"/D");
    outtree.Branch(c_DalitzWeight+"2",&DalitzWeight2, "DalitzWeight2"+pvs+"/D");
    outtree.Branch(c_DalitzWeight+"WE",&DalitzWeightWE, "DalitzWeightWE"+pvs+"/D");
    outtree.Branch("SPDWeight",&SPDWeight, "SPDWeight/D");
    outtree.Branch("PTWeight",&PTWeight, "PTWeight/D");
    outtree.Branch("PTWeight2",&PTWeight2, "PTWeight2/D");
    outtree.Branch("PTWeight2WE",&PTWeight2WE, "PTWeight2WE/D");
  } 
  outtree.Branch(c_NNEffWeight,&NNEffWeight, "NNEffWeight"+pvs+"/D");
  outtree.Branch("CPWeight",&CPWeight, "CPWeight/D");
  outtree.Branch("Teaching", &teaching , "Teaching/B");  
  outtree.Branch("CosTheta", &CosTheta , "CosTheta"+pvs+"/D");  

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
      bkgCat = ntuple->backgroundCategory() ;
      pptid = ntuple->pplus_TRUEID ;
      // std::cout << "Background Category " << ntuple->B_BKGCAT << " becomes " <<  bkgCat << std::endl ;
    }
    teaching = ntuple->teaching(!tSample,debug);
    nPV = (ntuple->MC()?1:ntuple->nPV) ;
    unsigned int passC = 0 ;
    for ( unsigned int pv = 0 ; pv!= nPV ; ++pv){    
      nTotal++ ;
      PsippiMass[pv] = (ntuple->B_FullFit_M[pv]>0)?ntuple->B_FullFit_M[pv]:0.  ;
      if (PsippiMass[pv]>10000) PsippiMass[pv] = 10000 ;
      PsipKMass[pv] = ntuple->B_SubpK_M[pv] ;
      PsiKpiMass[pv] = ntuple->B_SubKpi_M[pv] ;
      PsipiKMass[pv] = ntuple->JpsipiKMass() ;
      PsiKKMass[pv] = ntuple->JpsiKKMass() ;
      PsiKpMass[pv] = ntuple->JpsiKpMass() ;
      pMMass2[pv] = ntuple->pMMass2(pv);
      psiMMass2[pv] = ntuple->psiMMass2(pv);
      KKMass[pv] = ntuple->KKMass();
      mprime[pv] = ntuple->mprime(pv);
      thetaprime[pv] = ntuple->thetaprime(pv);
      CosTheta[pv] = ntuple->cosTheta(pv);
      if (ntuple->MC()) {
        DalitzWeight[pv] = (fullname.Contains("-Lb")?mcWeight(mprime[pv],thetaprime[pv],ntuple->isPion()):1.);
        DalitzWeight2[pv] = (fullname.Contains("-Lb")?mcWeight(mprime[pv],thetaprime[pv],ntuple->isPion(),2):1.);
        DalitzWeightWE[pv] = (fullname.Contains("-Lb")?mcWeight(mprime[pv],thetaprime[pv],ntuple->isPion(),1,m_rndm):1.);
        SPDWeight = ntuple->spdWeight();
        PTWeight = (fullname.Contains("-Lb")?ptWeight(ntuple->B_PT):1.);
        PTWeight2 = (fullname.Contains("-Lb")?ptWeight(ntuple->B_PT,2):1.);
        PTWeight2WE = (fullname.Contains("-Lb")?ptWeight(ntuple->B_PT,2,m_rndm):1.);
      }
      NNEffWeight[pv] = (ntuple->MC()?nnEffWeight(mprime[pv]):dataNnEffWeight(mprime[pv]));
      CPWeight = cpWeight(ntuple->isPion(),ntuple->piminus_P);
      psipMass2[pv] = ntuple->psipMass2(pv);
      ntuple->prepareArray(nvar, InputArray,pv,debug);
    // std::cout << InputArray[0] << " " << InputArray[1] << " " << InputArray[2] << std::endl ;
      bool isGood = false ;
      category[pv]  = ntuple->getCategory();
      netOutput[pv] = NeuroBayesExpert->nb_expert(InputArray);
      ErrorCode[pv] = ErrorCodes::Error ; // make sure nothing bad happens
      if (!ntuple->preselection(pv)){
        ErrorCode[pv] = ErrorCodes::FailsCuts ; // make sure nothing bad happens
        nFailed++;
      } else { // 
        if (!ntuple->trigger()){
          nFailTrigger++;
          ErrorCode[pv] = ErrorCodes::FailsTrigger; 
        } else {
          ErrorCode[pv] = ntuple->getReflectionCode(pv);
          if (ErrorCodes::OK!=ErrorCode[pv]){
            nVeto++ ;
          } else {
            nGood++ ;
            passC++ ;
            if (0!=pv) nNonBestPV++ ;
            h_net->Fill(netOutput[pv]); // only for triggered events
            if ( CatCodes::pKCand == category[pv] ) npK++ ;
            else if ( CatCodes::SignalCand== category[pv] ) nSignal++ ;
            else std::cout << "what's that " << category[pv] << "?" << std::endl ;
          } // Good
        } // trigger 
      } // preselection
      if ( ErrorCodes::Error == ErrorCode[pv] ) std::cout << "ErrorCode is still " << ErrorCode[pv] << std::endl ;
    } // pv
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
  std::cout << "     #   vetoed candidates             : " << nVeto << std::endl;
  std::cout << "     #   good candidate pairs          : " << nGood << std::endl;
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
    std::cout << "./expert.exe /castor/cern.ch/user/p/pkoppenb/Lambdab/Lambdab-S20r1-980.root "
	      << " [ /castor/cern.ch/user/p/pkoppenb/Lambdab/Lambdab-S20-982.root ] "
              << " [ Lambda ] | tee test-expert" << std::endl;  
    return -9;
  }

  // *** Decode Arguments ***
  TString fullname = TString(argv[1]);  
  TString fullname2 = "";
  TString type = "ppi";
  if (3==argc ){
    fullname2 = TString(argv[2]);  
    if (fullname2.Length()<10) {
      type = fullname2 ;
      fullname2 = "";
    }
  } else if ( 4==argc ){ // easy
    fullname2 = TString(argv[2]);  
    type = TString(argv[3]); 
  }
  if (fullname2==fullname) return -5;
  // *** Main Function ***
  std::cout << "++++++++++++++++++++ INIT ++++++++++++++++++++" << std::endl ;
  std::cout << "     File name    : " << fullname << std::endl;
  std::cout << "     File name 2  : " << fullname2 << std::endl;
  std::cout << "     type         : " << type << std::endl;
  std::cout << "     Arguments    : " << argc << std::endl;
  int ok = CreateExpertTree(fullname,type);
  if (0!=ok) return ok ;
  if (""!=fullname2) ok = CreateExpertTree(fullname2,type);
  return ok ;
  
}
// ####################################################################################################

