//
// Authors: Matteo Rama (INFN Pisa), 29 March 2016
//
#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include "TChain.h"
#include "TSystem.h"
#include "TSystemDirectory.h"
#include <fstream>
#include <TROOT.h>
#include "TKey.h"
void removeBlocksAndAddVars(TString,TString,TFile*);
void addLumiTree(TString,TFile*);

//intermediate vars to compute the new vars in TTree
double _muplus_phi,_muminus_phi,_muplus_MINIPCHI2,_muminus_MINIPCHI2,_muplus_PT,_muminus_PT,_muplus_IP_OWNPV,_muminus_IP_OWNPV,_muplus_IPCHI2_OWNPV,_muminus_IPCHI2_OWNPV,_muplus_eta,_muminus_eta;
double _B_D1_isolation_Giampi,_B_D2_isolation_Giampi,_B_IPCHI2_OWNPV,_B_DIRA_OWNPV,_B_FDCHI2_OWNPV,_B_TAU,_B_phi,_B_eta;

//new variable in TTree
double _mu_MINIPS;
double _sum_isolation;
double _mu_MINPT;
double _B_IPS_OWNPV;
double _B_ACOSDIRA_OWNPV;
double _B_FDS_OWNPV;
double _B_TAU_ps;
double _mu_MINIP;
double _mu_MAXPT;
double _mu_MAXIP;
double _mu_MAXIPS;
double _mu_AbsPhi;
double _mu_DeltaEta;
double _mu_DeltaPhi;
double _mu_DeltaR;
double _Bmup_DeltaPhi;
double _Bmup_DeltaEta;
double _Bmup_DeltaR;
double _Bmum_DeltaPhi;
double _Bmum_DeltaEta;
double _Bmum_DeltaR;
//double _B_JETBPTRATIO,_B_JETBDRMU1,_B_JETBDRMU2,_B_JETMU1DRMU2,_B_JETMU1PTRATIO,_B_JETMU2DRMU1,_B_JETMU2PTRATIO,_B_JETNOMU1DRMU1,_B_JETNOMU1DRMU2;

//branches corresponding to the new vars in TTree
TBranch* _b_mu_MINIPS;
TBranch* _b_sum_isolation;
TBranch* _b_mu_MINPT;
TBranch* _b_B_IPS_OWNPV;
TBranch* _b_B_ACOSDIRA_OWNPV;
TBranch* _b_B_FDS_OWNPV;
TBranch* _b_B_TAU_ps;
TBranch* _b_mu_MINIP;
TBranch* _b_mu_MAXPT;
TBranch* _b_mu_MAXIP;
TBranch* _b_mu_MAXIPS;
TBranch* _b_mu_AbsPhi;
TBranch* _b_mu_DeltaEta;
TBranch* _b_mu_DeltaPhi;
TBranch* _b_mu_DeltaR;
TBranch* _b_Bmup_DeltaPhi;
TBranch* _b_Bmup_DeltaEta;
TBranch* _b_Bmup_DeltaR;
TBranch* _b_Bmum_DeltaPhi;
TBranch* _b_Bmum_DeltaEta;
TBranch* _b_Bmum_DeltaR;
//TBranch* _b_B_JETBPTRATIO,_b_B_JETBDRMU1,_b_B_JETBDRMU2,_b_B_JETMU1DRMU2,_b_B_JETMU1PTRATIO,_b_B_JETMU2DRMU1,_b_B_JETMU2PTRATIO,_b_B_JETNOMU1DRMU1,_b_B_JETNOMU1DRMU2;

//TBranch* _b_mu_AbsPhi;

void InitTree(TTree* tree);
void FillBDT();

void addBDTvars(TString inputfile_name){
  cout<<endl<<"Entering addBDTvars: inputfile_name = "<<inputfile_name<<endl;
  
  TString path="";
  inputfile_name=path+inputfile_name;

  //Create new output file with same name as the input file, and fill it
  TString outputfile_name=inputfile_name;

  //Move input file file.root to file.root_preaddbdtvars
  inputfile_name=inputfile_name+"_preaddbdtvars";
  TString shellcommand="mv "+outputfile_name+" "+inputfile_name;
  cout<<" Execute shell command: "<<shellcommand<<" (";
  int shell_out=gSystem->Exec(shellcommand);
  cout<<shell_out<<")"<<endl;
  cout<<" input file = "<<inputfile_name<<" output file = "<<outputfile_name<<endl;

  //Create output file
  TFile *newfile = new TFile(outputfile_name,"recreate");

  //Remove track blocks and add some variables
  removeBlocksAndAddVars(inputfile_name,"B2MuMuTuple",newfile);
  removeBlocksAndAddVars(inputfile_name,"B2HHTuple",newfile);
  addLumiTree(inputfile_name,newfile);
  newfile->Close();
  delete newfile;
  
  return;

}//end addBDTvars


void removeBlocksAndAddVars(TString inputfile_name,TString dir_name,TFile* newfile){
  cout<<"Entering removeBlocksAndAddVars: inputfile_name = "<<inputfile_name<<" dir_name = "<<dir_name<<endl;
  TString inputfile_path="";
  
  //Take the tree in the input file
  TChain* ch=new TChain(dir_name+"/DecayTree");
  ch->Add(inputfile_name);
  TTree* oldtree=(TTree*) ch;
  
  //Create dir_name directory in new file
  newfile->mkdir(dir_name);
  newfile->cd(dir_name);

  //Disable the blocks in the old tree
  oldtree->SetBranchStatus("EVB_*",0);
  oldtree->SetBranchStatus("IsoST*",0);
  oldtree->SetBranchStatus("VEL_*",0);
  oldtree->SetBranchStatus("US_*",0);
  oldtree->SetBranchStatus("PV*",0);

  //Create the output tree
  TTree* newtree=oldtree->CloneTree();
  InitTree(newtree);

  Long64_t nentries=oldtree->GetEntries();
  Long64_t nb=0;
  cout<<"nentries = "<<nentries<<endl;
  for (int i=0;i<nentries;i++){
    nb=newtree->GetEntry(i);
    FillBDT();
  }

  newtree->Write();
  delete oldtree;
  delete newtree;
  //newfile->Close();//the new file is closed outside this method

  return;
}//end removeBlocksAndAddVars

void InitTree(TTree* tree){
  tree->SetBranchAddress("muplus_IPCHI2_OWNPV",&_muplus_IPCHI2_OWNPV);
  tree->SetBranchAddress("muminus_IPCHI2_OWNPV",&_muminus_IPCHI2_OWNPV);
  tree->SetBranchAddress("B_D1_isolation_Giampi",&_B_D1_isolation_Giampi);
  tree->SetBranchAddress("B_D2_isolation_Giampi",&_B_D2_isolation_Giampi);
  tree->SetBranchAddress("muplus_PT",&_muplus_PT);
  tree->SetBranchAddress("muminus_PT",&_muminus_PT);
  tree->SetBranchAddress("B_IPCHI2_OWNPV",&_B_IPCHI2_OWNPV);
  tree->SetBranchAddress("B_DIRA_OWNPV",&_B_DIRA_OWNPV);
  tree->SetBranchAddress("B_FDCHI2_OWNPV",&_B_FDCHI2_OWNPV);
  tree->SetBranchAddress("B_TAU",&_B_TAU);
  tree->SetBranchAddress("muplus_IP_OWNPV",&_muplus_IP_OWNPV);
  tree->SetBranchAddress("muminus_IP_OWNPV",&_muminus_IP_OWNPV);
  tree->SetBranchAddress("muplus_phi",&_muplus_phi);
  tree->SetBranchAddress("muminus_phi",&_muminus_phi);
  tree->SetBranchAddress("muplus_eta",&_muplus_eta);
  tree->SetBranchAddress("muminus_eta",&_muminus_eta);
  tree->SetBranchAddress("B_phi",&_B_phi);
  tree->SetBranchAddress("B_eta",&_B_eta);
  //tree->SetBranchAddress("B_",&_B_);


  _b_mu_MINIPS=tree->Branch("mu_MINIPS",&_mu_MINIPS,"mu_MINIPS/D");
  _b_sum_isolation=tree->Branch("sum_isolation",&_sum_isolation,"sum_isolation/D");
  _b_mu_MINPT=tree->Branch("mu_MINPT",&_mu_MINPT,"mu_MINPT/D");
  _b_B_IPS_OWNPV=tree->Branch("B_IPS_OWNPV",&_B_IPS_OWNPV,"B_IPS_OWNPV/D");
  _b_B_ACOSDIRA_OWNPV=tree->Branch("B_ACOSDIRA_OWNPV",&_B_ACOSDIRA_OWNPV,"B_ACOSDIRA_OWNPV/D");
  _b_B_FDS_OWNPV=tree->Branch("B_FDS_OWNPV",&_B_FDS_OWNPV,"B_FDS_OWNPV/D");
  _b_B_TAU_ps=tree->Branch("B_TAU_ps",&_B_TAU_ps,"B_TAU_ps/D");
  _b_mu_MINIP=tree->Branch("mu_MINIP",&_mu_MINIP,"mu_MINIP/D");
  _b_mu_MAXPT=tree->Branch("mu_MAXPT",&_mu_MAXPT,"mu_MAXPT/D");
  _b_mu_MAXIP=tree->Branch("mu_MAXIP",&_mu_MAXIP,"mu_MAXIP/D");
  _b_mu_MAXIPS=tree->Branch("mu_MAXIPS",&_mu_MAXIPS,"mu_MAXIPS/D");
  _b_mu_AbsPhi=tree->Branch("mu_AbsPhi",&_mu_AbsPhi,"mu_AbsPhi/D");
  _b_mu_DeltaEta=tree->Branch("mu_DeltaEta",&_mu_DeltaEta,"mu_DeltaEta/D");
  _b_mu_DeltaPhi=tree->Branch("mu_DeltaPhi",&_mu_DeltaPhi,"mu_DeltaPhi/D");
  _b_mu_DeltaR=tree->Branch("mu_DeltaR",&_mu_DeltaR,"mu_DeltaR/D");
  _b_Bmup_DeltaPhi=tree->Branch("Bmup_DeltaPhi",&_Bmup_DeltaPhi,"Bmup_DeltaPhi/D");
  _b_Bmup_DeltaEta=tree->Branch("Bmup_DeltaEta",&_Bmup_DeltaEta,"Bmup_DeltaEta/D");
  _b_Bmup_DeltaR=tree->Branch("Bmup_DeltaR",&_Bmup_DeltaR,"Bmup_DeltaR/D");
  _b_Bmum_DeltaPhi=tree->Branch("Bmum_DeltaPhi",&_Bmum_DeltaPhi,"Bmum_DeltaPhi/D");
  _b_Bmum_DeltaEta=tree->Branch("Bmum_DeltaEta",&_Bmum_DeltaEta,"Bmum_DeltaEta/D");
  _b_Bmum_DeltaR=tree->Branch("Bmum_DeltaR",&_Bmum_DeltaR,"Bmum_DeltaR/D");
  //_b_mu_AbsPhi=tree->Branch("mu_",&_mu_,"mu_/D");

  return;
}//end InitTree

void FillBDT(){
  _mu_MINIPS = sqrt(TMath::Min(_muplus_IPCHI2_OWNPV,_muminus_IPCHI2_OWNPV));
  _sum_isolation = _B_D1_isolation_Giampi+_B_D2_isolation_Giampi;
  _mu_MINPT = TMath::Min(_muplus_PT,_muminus_PT);
  _B_IPS_OWNPV = sqrt(_B_IPCHI2_OWNPV);
  _B_ACOSDIRA_OWNPV = acos(_B_DIRA_OWNPV);
  _B_FDS_OWNPV = sqrt(_B_FDCHI2_OWNPV);
  _B_TAU_ps = _B_TAU*1000;
  
  _mu_MINIP = TMath::Min(_muplus_IP_OWNPV,_muminus_IP_OWNPV);
  _mu_MAXPT = TMath::Max(_muplus_PT,_muminus_PT);
  _mu_MAXIP = sqrt(TMath::Max(_muplus_IP_OWNPV,_muminus_IP_OWNPV));
  _mu_MAXIPS= sqrt(TMath::Max(_muplus_IPCHI2_OWNPV,_muminus_IPCHI2_OWNPV));
  _mu_AbsPhi =  fabs(_muplus_phi-_muminus_phi);

  _mu_DeltaEta =  fabs(_muplus_eta-_muminus_eta);
  _mu_DeltaPhi=abs(abs(abs(_mu_AbsPhi)-acos(-1))-acos(-1));
  _mu_DeltaR=sqrt(pow(_mu_DeltaPhi,2)+pow(_mu_DeltaEta,2));

  double _Bmup_AbsPhi=abs(_B_phi-_muplus_phi);
  _Bmup_DeltaPhi=abs(abs(abs(_Bmup_AbsPhi)-acos(-1))-acos(-1));
  _Bmup_DeltaEta= fabs(_B_eta-_muplus_eta);
  _Bmup_DeltaR=sqrt(pow(_Bmup_DeltaPhi,2)+pow(_Bmup_DeltaEta,2));

  double _Bmum_AbsPhi=abs(_B_phi-_muminus_phi);
  _Bmum_DeltaPhi=abs(abs(abs(_Bmum_AbsPhi)-acos(-1))-acos(-1));
  _Bmum_DeltaEta= fabs(_B_eta-_muminus_eta);
  _Bmum_DeltaR=sqrt(pow(_Bmum_DeltaPhi,2)+pow(_Bmum_DeltaEta,2));


  _b_mu_MINIPS->Fill();
  _b_sum_isolation->Fill();
  _b_mu_MINPT->Fill();
  _b_B_IPS_OWNPV->Fill();
  _b_B_ACOSDIRA_OWNPV->Fill();
  _b_B_FDS_OWNPV->Fill();
  _b_B_TAU_ps->Fill();
  _b_mu_MINIP->Fill();
  _b_mu_MAXPT->Fill();
  _b_mu_MAXIP->Fill();
  _b_mu_MAXIPS->Fill();
  _b_mu_AbsPhi->Fill();
  _b_mu_DeltaEta->Fill();
  _b_mu_DeltaPhi->Fill();
  _b_mu_DeltaR->Fill();
  _b_Bmup_DeltaPhi->Fill();
  _b_Bmup_DeltaEta->Fill();
  _b_Bmup_DeltaR->Fill();
  _b_Bmum_DeltaPhi->Fill();
  _b_Bmum_DeltaEta->Fill();
  _b_Bmum_DeltaR->Fill();

  return;
}//end FillBDT


void addLumiTree(TString inputfile_name,TFile* newfile){
  bool addlumi=0;
  TFile* inputfile=TFile::Open(inputfile_name);
  TIter next(inputfile->GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)next())) {
    cout<<key->GetName()<<endl;
    TString key_name=key->GetName();
    if (key_name.Contains("GetIntegratedLuminosity")) addlumi=1;
  }
  if (addlumi==0){
    cout<<"GetIntegratedLuminosity not found. Exiting..."<<endl;
    inputfile->Close();
    return;
  }
  TString dir_name_lumi="GetIntegratedLuminosity";
  TChain* ch_lumi=new TChain(dir_name_lumi+"/LumiTuple");
  ch_lumi->Add(inputfile_name);
  TTree* oldtree_lumi=(TTree*) ch_lumi;
  
  newfile->mkdir(dir_name_lumi);
  newfile->cd(dir_name_lumi);
    
  oldtree_lumi->SetAutoSave(3000000000);
  TTree* newtree_lumi=oldtree_lumi->CloneTree();
  newtree_lumi->Draw("IntegratedLuminosity");
  newfile->Write();
  inputfile->Close();
  delete oldtree_lumi;
  delete newtree_lumi;

  return;
}//end addLumiTree
