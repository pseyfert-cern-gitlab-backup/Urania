#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include "TLorentzVector.h"

void fullFix(){
  TFile *_file0 = TFile::Open("bsmumukk_f0_phi_0.5pi.root");
  TTree* tree = (TTree*)_file0->Get("bsmumukk");
  TFile* tuple = new TFile("bsmumukk_f0_phi_0.5pi_FF.root","RECREATE");
  TTree*  newtree = tree->CloneTree(-1);

  //RooArgSet:: = (mass,mdau2,time,sigmat,helcosthetaK,helcosthetaL,helphi,tagomega_os_cb,tagomega_ss_nn,hlt1_excl_biased,hlt2_biased,hlt2_unbiased,KKMassCat,iTagOS,iTagSS,tagCatP2VVOS,tagCatP2VVSS,tagCatP2VV,runPeriod)

  int iTag; TBranch* Br_iTag = newtree->Branch("iTagOS",&iTag, "iTagOS/I");
  int RP; TBranch* Br_RP = newtree->Branch("runPeriod",&RP, "runPeriod/I");
  double tagOmega; TBranch* Br_tagOmega = newtree->Branch("tagomega_os_cb",&tagOmega, "tagomega_os_cb/D");
  int tagCat; TBranch* Br_tagCat = newtree->Branch("tagCatP2VVOS",&tagCat, "tagCatP2VVOS/I");
  int iTagSS; TBranch* Br_iTagSS = newtree->Branch("iTagSS",&iTagSS, "iTagSS/I");
  double tagOmegaSS; TBranch* Br_tagOmegaSS = newtree->Branch("tagomega_ss_cb",&tagOmegaSS, "tagomega_ss_cb/D");
  int tagCatSS; TBranch* Br_tagCatSS = newtree->Branch("tagCatP2VVSS",&tagCatSS, "tagCatP2VVSS/I");
  //
  double helcosthetaK; TBranch* Br_helcosthetaK = newtree->Branch("helcosthetaK",&helcosthetaK, "helcosthetaK/D");
  double helcosthetaL; TBranch* Br_helcosthetaL = newtree->Branch("helcosthetaL",&helcosthetaL, "helcosthetaL/D");
  double helphi; TBranch* Br_helphi = newtree->Branch("helphi",&helphi, "helphi/D");
  double sig; TBranch* Br_sig = newtree->Branch("sigmat",&sig, "sigmat/D");
  double mass; TBranch* Br_mass = newtree->Branch("mass",&mass, "mass/D");
  double mKK; TBranch* Br_mKK = newtree->Branch("mKK",&mKK, "mKK/D");
  //
  int tag; newtree->SetBranchAddress("q",&tag);
  double theta_K; newtree->SetBranchAddress("theta_K",&theta_K);
  double MKK; newtree->SetBranchAddress("MKK",&MKK);
  double theta_Mu; newtree->SetBranchAddress("theta_mu",&theta_Mu);
  double phi; newtree->SetBranchAddress("phi",&phi);
  //

  for ( int i = 0;  i < newtree->GetEntries(); ++i){
    newtree->GetEntry(i);

    RP=2011;
    mKK=MKK*1000.0;
    iTag=-tag;
    iTagSS=1;
    tagOmegaSS=0.49;
    tagOmega=0.01;
    tagCat=1;
    tagCatSS=0;
    sig=0.01;
    mass=5366.67;
    helcosthetaK = (theta_K);
    helcosthetaL = (theta_Mu);
    helphi=phi;
    
    Br_RP->Fill();
    Br_iTag->Fill();
    Br_tagOmega->Fill();
    Br_tagCat->Fill();
    Br_mKK->Fill();
    Br_iTagSS->Fill();
    Br_tagOmegaSS->Fill();
    Br_tagCatSS->Fill();
    Br_sig->Fill();
    Br_mass->Fill();
    Br_helcosthetaK->Fill();
    Br_helcosthetaL->Fill();
    Br_helphi->Fill();
  }

  newtree->Write();
  tuple->Close();
}
