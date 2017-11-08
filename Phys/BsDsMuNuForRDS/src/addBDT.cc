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
#include "TH1D.h"
#include "TMVA/Reader.h"
#include "TString.h"

void addBDTtoNtuple(TString,TString,TFile*,TString,TH1D*,TString);
void fillHisto2(TString trainfile_name,TH1D* his);
vector<string> getBDTVars(TString,TString);
double getVal(TString);
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

void addLumiTree2(TString,TFile*);

double __iso_max2_set8_lt;
double __iso_max2_set1_velnb;
double __mu_DeltaR;
double __mu_MINIPS;
double __B_ACOSDIRA_OWNPV;
double __B_IPS_OWNPV;
double __B_ENDVERTEX_CHI2;

double __sum_isolation;
double __B_yetanother_CDF_iso;
double __B_otherB_ang;
double __mu_DeltaEta;
double __mu_AbsPhi;
double __B_TAU_ps;
double __B_IP_OWNPV;
double __B_doca;
double __B_PT;
double __B_cosnk;
double __B_otherB_boo_ang;

double __mu_DeltaPhi;

void InitTree2(TTree* tree);//NB: changed from InitTree to InitTree2 otherwise the InitTree in addBDTvars.cc is read instead

void addBDT(TString inputfile_name,TString sigflatfile_name,TString weightfile_name,TString BDTvar_name){
  cout<<endl<<"Entering addBDT: inputfile_name = "<<inputfile_name<<endl;

  TString path="";
  inputfile_name=path+inputfile_name;

  //Create new output file with same name as the input file, and fill it
  TString outputfile_name=inputfile_name;

  //Move input file file.root to file.root_preaddbdt
  inputfile_name=inputfile_name+"_preaddbdt";
  TString shellcommand="mv "+outputfile_name+" "+inputfile_name;
  cout<<" Execute shell command= "<<shellcommand<<" (";
  int shell_out=gSystem->Exec(shellcommand);
  cout<<shell_out<<")"<<endl;
  cout<<" input file = "<<inputfile_name<<" output file = "<<outputfile_name<<endl;
  
  //Create output file
  TFile *newfile = new TFile(outputfile_name,"recreate");
  
  //Add the global BDT to the B2MuMu and B2HH trees
  int nbin=(int)3e5;
  TH1D* hisBDT = new TH1D("hisBDT","hisBDT",nbin,-1.5,1.5);
  TString sigflatfile_path="./weights/";
  fillHisto2(sigflatfile_path+sigflatfile_name,hisBDT);
  addBDTtoNtuple(inputfile_name,"B2MuMuTuple",newfile,weightfile_name,hisBDT,BDTvar_name);
  addBDTtoNtuple(inputfile_name,"B2HHTuple",newfile,weightfile_name,hisBDT,BDTvar_name);
  addLumiTree2(inputfile_name,newfile);
  newfile->Close();
  delete newfile;
  //delete hisBDT;

  return;

}//end addBDT

void InitTree2(TTree* tree){
  tree->SetBranchAddress("iso_max2_set8_lt",&__iso_max2_set8_lt);
  tree->SetBranchAddress("iso_max2_set1_velnb",&__iso_max2_set1_velnb);
  tree->SetBranchAddress("mu_DeltaR",&__mu_DeltaR);
  tree->SetBranchAddress("mu_MINIPS",&__mu_MINIPS);
  tree->SetBranchAddress("B_ACOSDIRA_OWNPV",&__B_ACOSDIRA_OWNPV);
  tree->SetBranchAddress("B_IPS_OWNPV",&__B_IPS_OWNPV);
  tree->SetBranchAddress("B_ENDVERTEX_CHI2",&__B_ENDVERTEX_CHI2);
  tree->SetBranchAddress("sum_isolation",&__sum_isolation);
  tree->SetBranchAddress("B_yetanother_CDF_iso",&__B_yetanother_CDF_iso);
  tree->SetBranchAddress("mu_DeltaEta",&__mu_DeltaEta);
  tree->SetBranchAddress("mu_AbsPhi",&__mu_AbsPhi);
  tree->SetBranchAddress("B_TAU_ps",&__B_TAU_ps);
  tree->SetBranchAddress("B_IP_OWNPV",&__B_IP_OWNPV);
  tree->SetBranchAddress("B_doca",&__B_doca);
  tree->SetBranchAddress("B_PT",&__B_PT);
  tree->SetBranchAddress("B_cosnk",&__B_cosnk);
  tree->SetBranchAddress("B_otherB_ang",&__B_otherB_ang);
  tree->SetBranchAddress("B_otherB_boo_ang",&__B_otherB_boo_ang);
   //tree->SetBranchAddress("B_",&__B_);
 
  return;
}//end InitTree2

void addLumiTree2(TString inputfile_name,TFile* newfile){
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
}//end addLumiTree2

void addBDTtoNtuple(TString inputfile_name,TString dir_name,TFile* newfile,TString weightfile_name,TH1D* hisBDT,TString BDTvar_name){
  cout<<"Entering addBDTtoNtuple: inputfile_name = "<<inputfile_name<<" dir_name = "<<dir_name<<endl;
  
  TString inputfile_path="";
  TString weightfile_path="./weights/";
  //Take the tree in the input file
  TChain* ch=new TChain(dir_name+"/DecayTree");
  ch->Add(inputfile_name);
  TTree* oldtree=(TTree*) ch;

  //Create dir_name directory in new file
  newfile->mkdir(dir_name);
  newfile->cd(dir_name);

 //Create the output tree
  TTree* newtree=oldtree->CloneTree();
  InitTree2(newtree);

  //
  // Fill vector with the BDT input vars extracted from the weightfile
  //
  vector<string> inputvars_vec=getBDTVars(weightfile_path+weightfile_name,"input");//input vars
  vector<string> specvars_vec=getBDTVars(weightfile_path+weightfile_name,"spec");//spectator vars
  
  //
  // Create and setup TMVA reader. It takes as input the list of input vars and the weight file
  //
  TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
  float var[inputvars_vec.size()];
  float spec[specvars_vec.size()];
  for (int i=0;i<(int)inputvars_vec.size();i++){
    reader->AddVariable(inputvars_vec[i],&var[i]);
    cout<<"added input var "<<inputvars_vec[i]<<endl;
  }//end i<inputvars_vec.size();

  for (int i=0;i<(int)specvars_vec.size();i++){
    reader->AddSpectator(specvars_vec[i],&spec[i]);
    cout<<"added spectator var "<<specvars_vec[i]<<endl;
  }//end i<specvars_vec.size();

  reader->BookMVA("BDT method",weightfile_path+weightfile_name);
  
  //
  // Create the new branches of newtree
  //
  double BDT,BDTflat;
  TBranch *BDTBranch = newtree->Branch(BDTvar_name,&BDT,BDTvar_name+"/D");
  TBranch *BDTflatBranch = newtree->Branch(BDTvar_name+"flat",&BDTflat,BDTvar_name+"flat/D");

  //
  // Fa il loop sulle entries di newtree, calcola BDT tramite il reader 
  // e calcola BDTflat usando l'istogramma di input. 
  // Loop over the entries of newtree, compute the BDT value and compute BDTflat
  // using the signalMC histogram given as input
  // 
  double hisBDT_nentries=hisBDT->GetEntries();
  Long64_t nentries=oldtree->GetEntries();
  Long64_t nb=0;
  cout<<"nentries = "<<nentries<<endl;
  bool v=true;
  for (int i=0;i<nentries;i++){
    if (i>5) v=false;
    nb=newtree->GetEntry(i);
    if (v) cout<<"__iso_max2_set8_lt = "<<__iso_max2_set8_lt<<endl;
    //assign the values to the vars uses by TMVA reader to compute the BDT
    for (int j=0;j<(int)inputvars_vec.size();j++){
      var[j]=getVal(inputvars_vec[j]);
      if (v) cout<<"var["<<j<<"] = "<<var[j]<<endl;
    }
    BDT=reader->EvaluateMVA("BDT method");
    BDTflat=((double)hisBDT->Integral(1,hisBDT->FindBin(BDT)))/hisBDT_nentries;
    if (v) cout<<"i = "<<i<<" BDT = "<<BDT<<" BDTflat = "<<BDTflat<<endl;
    BDTBranch->Fill();
    BDTflatBranch->Fill();
  }
  newtree->Write();
  delete oldtree;
  delete newtree;
  delete reader;

  return;

}//end addBDTtoNtuple

vector<string> getBDTVars(TString weightfile_name,TString opt){
  ifstream file(weightfile_name);
  std::vector<std::string> line;
  string mystr;
  int ntot(0);
  while(file >> mystr){
    line.push_back(mystr);
    ntot++;
  }
  //Loop over string vec and look for strings containing the BDT var names.
  //Use splitting to identify the var names and store the names in vars_vec.
  int nvars(0);
  vector<std::string> vars_vec;
  //vector<std::string> vars_vec;
  if (opt=="input"){
    for (int i=0;i<ntot-1;i++){
      //if (line[i]=="<Input" && line[i+1]=="Type=\"Variable\""){//tmva root v.5.34 
      if (line[i]=="<Variable"){//tmva root v.5.27 o v.5.34
	std::vector<std::string> x = split(line[i+2],'"');
	vars_vec.push_back(x[1]);
	nvars++;
      }
    }//end i<ntot-1 cond
  }//end opt=="input" cond
  if (opt=="spec"){
    for (int i=0;i<ntot-1;i++){
      if (line[i]=="<Spectator"){
	std::vector<std::string> x = split(line[i+2],'"');
	vars_vec.push_back(x[1]);
	nvars++;
      }
    }//end i<ntot-1 cond
  }//end opt=="spec" cond

  
  return vars_vec;

}//end getBDTVars

double getVal(TString var_name){
  if (var_name=="iso_max2_set8_lt") return __iso_max2_set8_lt;
  else if (var_name=="iso_max2_set1_velnb") return __iso_max2_set1_velnb;
  else if (var_name=="mu_DeltaR") return __mu_DeltaR;
  else if (var_name=="mu_MINIPS") return __mu_MINIPS;
  else if (var_name=="B_ACOSDIRA_OWNPV") return __B_ACOSDIRA_OWNPV;
  else if (var_name=="B_IPS_OWNPV") return __B_IPS_OWNPV;
  else if (var_name=="B_ENDVERTEX_CHI2") return __B_ENDVERTEX_CHI2;
  else if (var_name=="sum_isolation") return __sum_isolation;
  else if (var_name=="B_yetanother_CDF_iso") return __B_yetanother_CDF_iso;
  else if (var_name=="B_otherB_ang") return __B_otherB_ang;
  else if (var_name=="mu_DeltaEta") return __mu_DeltaEta;
  else if (var_name=="mu_AbsPhi") return __mu_AbsPhi;
  else if (var_name=="B_TAU_ps") return __B_TAU_ps;
  else if (var_name=="B_IP_OWNPV") return __B_IP_OWNPV;
  else if (var_name=="B_doca") return __B_doca;
  else if (var_name=="B_PT") return __B_PT;
  else if (var_name=="B_cosnk") return __B_cosnk;
  else if (var_name=="B_otherB_boo_ang") return __B_otherB_boo_ang;
   //else if (var_name=="") return ;
  else {cout<<"ERROR. var_name = "<<var_name<<" Return -1"<<endl; return -1;}
}

std::vector<std::string> & split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

//
// Fill the input histogram with the BDT distribution of signal events contained in TestTree of the input file
//
void fillHisto2(TString trainfile_name,TH1D* his){
  TFile* inputfile = new TFile(trainfile_name);
  TTree* t = (TTree*) inputfile->Get("TestTree");
  TBranch* bBDT=t->GetBranch("BDT");
  TBranch* bclassID=t->GetBranch("classID");
  float BDT_var;
  int classID_var;
  bBDT->SetAddress(&BDT_var);
  bclassID->SetAddress(&classID_var);
  int n=t->GetEntries();
  for (int i=0;i<n;i++){
    t->GetEvent(i);
    if (classID_var==0) his->Fill(BDT_var);
  }//end i<n loop

  return;
  
}//end fillHisto2
