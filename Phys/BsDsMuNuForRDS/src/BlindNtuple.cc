//
// Authors: Matteo Rama (INFN Pisa), 29 March 2016
//
#include <iostream>
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TKey.h"
#include "TSystem.h"

void blindMassRegion(TString inputfile_name,TString dir_name,TFile* newfile);
void addLumiTree3(TString,TFile*);

void BlindNtuple(TString inputfile_name){
  cout<<endl<<"Entering BlindNtuple: inputfile_name = "<<inputfile_name<<endl;
  
  TString path="";
  inputfile_name=path+inputfile_name;

  //Create new output file with same name as the input file, and fill it
  TString outputfile_name=inputfile_name;

  //Move input file file.root to file.root_preaddbdtvars
  inputfile_name=inputfile_name+"_preblind";
  TString shellcommand="mv "+outputfile_name+" "+inputfile_name;
  cout<<" Execute shell command: "<<shellcommand<<" (";
  int shell_out=gSystem->Exec(shellcommand);
  cout<<shell_out<<")"<<endl;
  cout<<" input file = "<<inputfile_name<<" output file = "<<outputfile_name<<endl;

  //Create output file
  TFile *newfile = new TFile(outputfile_name,"recreate");

  //Blind signal region
  blindMassRegion(inputfile_name,"B2MuMuTuple",newfile);
  blindMassRegion(inputfile_name,"B2HHTuple",newfile);
  addLumiTree3(inputfile_name,newfile);
  
  newfile->Close();
  delete newfile;

  return;
  
}//end BlindNtuple

void blindMassRegion(TString inputfile_name,TString dir_name,TFile* newfile){
  cout<<"Entering blindMassRegion: inputfile_name = "<<inputfile_name<<" dir_name = "<<dir_name<<endl;
  bool _v=true;
  TString inputfile_path="";
  
  //Take the tree in the input file
  TChain* ch=new TChain(dir_name+"/DecayTree");
  ch->Add(inputfile_name);
  TTree* oldtree=(TTree*) ch;
  
  //Create dir_name directory in new file
  newfile->mkdir(dir_name);
  newfile->cd(dir_name);
  
  //Create the output tree
  TTree* newtree=oldtree->CloneTree(0);
  double b_MM;
  oldtree->SetBranchAddress("B_MM",&b_MM);
  int nentries=oldtree->GetEntries();
  int count(0);
  for (int i=0;i<nentries;i++){
    if (_v && !(i%10000)) cout<<" i = "<<i<<" selected = "<<count<<endl;
    oldtree->GetEntry(i);
    if (dir_name=="B2MuMuTuple" && b_MM>5200&&b_MM<5447) continue;//do not blind the B2HH signal region
    newtree->Fill();
    count++;
  }//end i<nentries loop

  newtree->Write();
  
  delete oldtree;
  delete newtree;
  
  return;

}//end blindMassRegion

void addLumiTree3(TString inputfile_name,TFile* newfile){
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
}//end addLumiTree3
