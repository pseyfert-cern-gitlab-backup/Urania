// ####################################################################################################
// Add variables to MC tuple that are hard to calculate in root
// Authors: Patrick Koppenburg
// ####################################################################################################

// ####################################################################################################
// *** Load Useful Classes **

// General C++ && Root
#include "TString.h"
#include <TVector3.h>
#include <iostream>
#include "MultipleCandidates.h"
#include "weights.h"
#include "TRandom2.h"

// Lambdab2JPsippi Package
#include "Lambdab.h"

static const TString c_pos = "pos";
static const TString c_neg = "neg";
using namespace std ;


// ####################################################################################################
// *** Declarations ***
int loop(Lambdab* ntuple, bool isPi, TString charge){

  if (!ntuple) return -1 ;
  if (!(ntuple->fChain)) {
    std::cout << "fchain is NULL" << std::endl ;
    return -2 ;
  }

  int theCharge = 0 ;
  if (""!=charge){
    if (c_pos==charge) theCharge = 1;
    else if (c_neg==charge) theCharge = -1;
    else {
      cout << "Unknown charge " << charge << endl ;
      return -55 ;
    }
  }
  std::cout << "Will only keep candidates with mesons of charge " << theCharge << " (0: all)" << endl ;

  const Long64_t nentries = ntuple->fChain->GetEntries();
  double frac = printFrac(nentries);  
  TFile* outfile = new TFile( (isPi?"PIDLb2Psippi"+charge+".root":"PIDLb2PsipK"+charge+".root"), "RECREATE" );
  TRandom2* m_rndm = new TRandom2(m_theSeed); // 0 : use time
  m_rndm->SetSeed(m_theSeed);
  fillFluctuateBins(m_rndm);
 
  unsigned long int runNumber, eventNumber ;
  Double_t mprime, thetaprime, pMMass2, psipMass2, psiMMass2, DalitzWeight,  DalitzWeightWE, PTWeight2,  PTWeight2WE ;
  // PIDCalib vars
  Double_t nTracks, nPVs, meson_P, meson_PT, meson_ETA, meson_PIDK, meson_PIDp, meson_ProbNNK, meson_ProbNNpi, nsig_sw, meson_c  ;
  TString meson = (isPi?"Pi_":"K_");
  Int_t Polarity ;
  
  TTree outtree("MCTree","MC PID Helper Tree");
  outtree.Branch("EventNumber",&eventNumber, "EventNumber/l");
  outtree.Branch("RunNumber",&runNumber, "RunNumber/i");
  outtree.Branch("mprime",&mprime,"mprime/D");
  outtree.Branch("thetaprime",&thetaprime,"thetaprime/D");
  outtree.Branch("pMMass2",&pMMass2,"pMMass2/D");
  outtree.Branch("psipMass2",&psipMass2,"psipMass2/D");
  outtree.Branch("psiMMass2",&psiMMass2,"psiMMass2/D");
  outtree.Branch("DalitzWeight",&DalitzWeight,"DalitzWeight/D");
  outtree.Branch("DalitzWeightWE",&DalitzWeightWE,"DalitzWeightWE/D");
  outtree.Branch("PTWeight2",&PTWeight2,"PTWeight2/D");
  outtree.Branch("PTWeight2WE",&PTWeight2WE,"PTWeight2WE/D");
  outtree.Branch("nTracks",&nTracks);
  outtree.Branch("nPVs",&nPVs);
  outtree.Branch(meson+"Charge",&meson_c);
  outtree.Branch(meson+"P",&meson_P);
  outtree.Branch(meson+"PT",&meson_PT);
  outtree.Branch(meson+"TRACK_Eta",&meson_ETA);
  outtree.Branch(meson+"PIDK",&meson_PIDK);
  outtree.Branch(meson+"PIDp",&meson_PIDp);
  outtree.Branch(meson+"ProbNNK",&meson_ProbNNK);
  outtree.Branch(meson+"ProbNNpi",&meson_ProbNNpi);
  outtree.Branch("Meson_Charge",&meson_c);  
  outtree.Branch("Meson_P",&meson_P);  // just to overcome a stupid PIDCalib feature
  outtree.Branch("Meson_PT",&meson_PT);
  outtree.Branch("Meson_TRACK_Eta",&meson_ETA);
  outtree.Branch("Meson_PIDK",&meson_PIDK);
  outtree.Branch("Meson_PIDp",&meson_PIDp);
  outtree.Branch("Meson_ProbNNK",&meson_ProbNNK);
  outtree.Branch("Meson_ProbNNpi",&meson_ProbNNpi);
  outtree.Branch("nsig_sw",&nsig_sw);
  outtree.Branch("isPion",&isPi);
  outtree.Branch("Polarity",&Polarity);

  outtree.SetDirectory(outfile); 

  unsigned int BadBK = 0 ;
  unsigned int BadP = 0 ;
  unsigned int BadEta = 0 ;
  unsigned int BadTk = 0 ;  
  unsigned int BadTrig = 0 ;  
  unsigned int BadPresel = 0 ;  
  unsigned int BadCharge = 0 ;  
  unsigned int Good = 0 ;  

  for (Long64_t i=0; i<nentries;i++) {
    ntuple->fChain->GetEntry(i);
    if ((isPi && 0!=ntuple->backgroundCategory()) ||
        (!isPi && c_psipK_BKGCAT!=ntuple->backgroundCategory())){
      BadBK++;
      continue ;
    }
    if ( ntuple->piminus_P< 3000 || ntuple->piminus_P > 100000){
      BadP++;
      continue;
    }
    double eta = -log(tan(atan2(abs(ntuple->piminus_PT),ntuple->piminus_PZ)/2.)) ;
    if ( eta < 1.5 || eta>5. ){
      BadEta++;
      continue;
    }
    if ( ntuple->nTracks>=500 ){
      BadTk++;
      continue;
    }
    if ( !ntuple->trigger() ){
      BadTrig++;
      continue;
    }
    if ( !ntuple->preselection(0,false,true) ){
      BadPresel++;
      continue;
    }
    meson_c = (ntuple->piminus_ID>0?1.:-1.) ;
   // 3000 <= K_P && 100000 > K_P && 1.5 <= K_TRACK_Eta && 5 > K_TRACK_Eta && 0 <= nTracks && 500 > nTracks
    if (0!=theCharge && theCharge!=meson_c ){
      BadCharge++;
      continue ;
    }
    Good++;
    runNumber = ntuple->runNumber;
    eventNumber = ntuple->eventNumber;
    mprime = ntuple->mprime(0) ;
    thetaprime = ntuple->thetaprime(0) ;
    pMMass2 = ntuple->pMMass2(0) ;
    psipMass2 = ntuple->psipMass2(0) ;
    psiMMass2 = ntuple->psiMMass2(0) ;
    DalitzWeight = mcWeight(mprime,thetaprime,isPi);
    DalitzWeightWE = mcWeight(mprime,thetaprime,isPi,1,m_rndm);
    PTWeight2 = ptWeight(ntuple->B_PT,2);
    PTWeight2WE = ptWeight(ntuple->B_PT,2,m_rndm);
    nTracks = ntuple->nTracks ;
    nPVs = ntuple->nPV ;
    meson_P = ntuple->piminus_P ;
    meson_PT = ntuple->piminus_PT ;
    meson_ETA = eta ;
    meson_PIDK = ntuple->piminus_PIDK ;
    meson_PIDp = ntuple->piminus_PIDp ;
    meson_ProbNNK = ntuple->piminus_ProbNNk ;
    meson_ProbNNpi = ntuple->piminus_ProbNNpi ;
    nsig_sw = DalitzWeight*PTWeight2 ;
    Polarity = ntuple->Polarity ;

    outtree.Fill() ;
    if(0==i%((int)(frac*nentries))) std::cout << " |-> " << i << " / " 
                                              << nentries << " (" << 100*i/nentries << "%)" 
					      << " Dalitz: " << mprime << ":" << thetaprime << std::endl; 
  }
  std::cout << "Bad BKGCAT : " << BadBK << std::endl ;
  std::cout << "Bad P      : " << BadP << std::endl ;
  std::cout << "Bad Eta    : " << BadEta << std::endl ;
  std::cout << "Bad Tracks : " << BadTk << std::endl ;
  std::cout << "Bad Trigger: " << BadTrig << std::endl ;
  std::cout << "Bad Presel : " << BadPresel << std::endl ;
  std::cout << "Bad Charge : " << BadCharge << std::endl ;
  std::cout << "Good       : " << Good << std::endl ;

  std::cout << "Done" << std::endl  ;
  outfile->cd();
  outtree.Write();
  outfile->Close();
 
  
  return 0;
}



// ####################################################################################################
// *** Main ***
int main(int argc, char** argv) {

  if(argc<2){
    std::cout << "ERROR: Insufficient arguments given" << std::endl;  
    std::cout << "./makePIDtuple.exe $CASTOR_HOME/Lambdab/LambdabMC-Lbpi-Sim08a-1122-1123-1124-1125.root [ charge ]" 
              << "  | tee test-makePIDtuple" << std::endl;  
    return -9;
  }

  // *** Decode Arguments ***
  TString fullname = TString(argv[1]);
  TString charge   = (argc>2)?TString(argv[2]):"";
  
  std::cout << "Configured makePIDtuple with file: ``" << fullname << "'' charge: " << charge << std::endl ;
  
  bool isPi =  fullname.Contains("Lbpi");
  Lambdab* tuple = new Lambdab(fullname,"","","");
  if (!tuple) {
    std::cout << "Tuple is " << tuple << std::endl ;
    return -1 ;
  }
  return loop(tuple, isPi, charge);
}
