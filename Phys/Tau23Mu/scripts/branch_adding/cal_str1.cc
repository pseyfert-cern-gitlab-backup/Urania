#include <vector>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <Riostream.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TCut.h"
#include "TStopwatch.h"

#include <cmath>


#include "weights/twobody_etap_MLP.class.C"

void cal()
{

  TFile *_file0 = TFile::Open("stp17unblinded_md_flat.root", "update");
  TTree *tree = (TTree*)gDirectory->Get("Tau23Mu");
  TCut mycutb_mine1 = "L0Dec&&Hlt1Dec&&Hlt2Dec&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99&&( (min(p0_singlePID,min(p1_singlePID,    p2_singlePID))>-0.25&&min(p0_singlePID,min(p1_singlePID,p2_singlePID))<-0.125&&GeoMVA>0.75&&GeoMVA<=1)||(min(p0_singlePID,min(p1_singlePID,    p2_singlePID))>-0.125&&min(p0_singlePID,min(p1_singlePID,p2_singlePID))<-0.025&&GeoMVA>0.35&&GeoMVA<=1) || (min(p0_singlePID,min(p1_singlePID,    p2_singlePID))>-0.025&&min(p0_singlePID,min(p1_singlePID,p2_singlePID))<0.05&&GeoMVA>0.05&&GeoMVA<=1)||(min(p0_singlePID,min(p1_singlePID,    p2_singlePID))>0.05&&min(p0_singlePID,min(p1_singlePID,p2_singlePID))<=1.1&&GeoMVA>0.05&&GeoMVA<=1))";
  TCut mycutb_mine2 = "L0Dec&&Hlt1Dec&&Hlt2Dec&&cleaningcut&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20&&mass_p0p1>250&&LifeTime<0.025&&LifeTime>-0.01&&dira>0.99";





  TCut mass_window="(mass>=1778.4-40&&mass<=1778.4-20)||(mass>=1778.4+20&&mass<=1778.4+40)";
  // TTree *tree = tree_tmp->CopyTree(mass_window&&mycutb_mine2);
  //Tree *tree=tree_tmp;
  int entries = tree->GetEntries();
  cout<<"Entries= "<<entries<<endl;

  Float_t mass_p0p2, mass_p1p2;
  Float_t MLPMVA, BDTGMVA, BDT, Cuts;



  std::vector<std::string> wektors;
  wektors.push_back("mass_p0p2*mass_p0p2");
  wektors.push_back("mass_p1p2*mass_p1p2");



  gROOT->LoadMacro("weights/twobody_etap_MLP.class.C");
  IClassifierReader* MLPResponse  = new ReadMLP (wektors);
  /*
     gROOT->LoadMacro("weights/twobody_etap_BDTG.class.C");
     IClassifierReader* BDTGResponse  = new ReadBDTG (wektors);
     gROOT->LoadMacro("/home/mchrzasz/tau23mu_analysis/tau23mu_eta_treatment/MVA/weights/twobody_etap_BDT.class.C");
     IClassifierReader* BDTResponse  = new ReadBDT (wektors);
     gROOT->LoadMacro("/home/mchrzasz/tau23mu_analysis/tau23mu_eta_treatment/MVA/weights/twobody_etap_Cuts.class.C");
     IClassifierReader* CUTSResponse  = new ReadCuts (wektors);
     */


  tree->SetBranchAddress( "mass_p0p2", &mass_p0p2);
  tree->SetBranchAddress( "mass_p1p2", &mass_p1p2);

  TBranch *newBranch = tree->Branch("MLPMVA", &MLPMVA, "MLPMVA/F");
  // TBranch *newBranch = tree->Branch("BDTGMVA", &BDTGMVA, "BDTGMVA/F");
  // TBranch *newBranch = tree->Branch("BDTMVA", &BDTMVA, "BDTMVA/F");
  // TBranch *newBranch = tree->Branch("CutsMVA", &CutsMVA, "CutsMVA/F");



  for (int i =0;i<entries;++i)
  {
    tree->GetEntry(i);
    if(i%1000==0) cout<<i<<endl;
    std::vector<Double_t> wektor(2);
    (wektor) [0] = mass_p0p2*mass_p0p2;
    (wektor) [1] = mass_p1p2*mass_p1p2;
    MLPMVA = MLPResponse->GetMvaValue( wektor );
    //  BDTGMVA = BDTGResponse->GetMvaValue( wektor );
    // BDTMVA = BDTResponse->GetMvaValue( wektor );
    // CutsMVA =CutsResponse->GetMvaValue( wektor );
    newBranch->Fill();



  }

  tree->Write("", TObject::kOverwrite);
  cout<<"ALL DONE"<<endl;

}

int main() {cal();}
