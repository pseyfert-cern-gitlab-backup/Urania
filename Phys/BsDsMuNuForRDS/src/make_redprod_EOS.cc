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

void reduceProd(TString opt="");
void CreateReducedFile(TString,TString opt="");
void AddIsoBDT(TString inputfile_name,TString weightfile_name,TString outfile_flag,TString var_name,TString cut_option,int trk_type,TString opt,TString opt2);
void AddBDTVars(TString inputfile_name);
void AddBDT(TString inputfile_name,TString sigflatfile_name,TString weightfile_name,TString BDTvar_name);
void Blind(TString inputfile_name);

bool _v;

//
// Uncomment the set of root files you want to process
//
void make_redprod_EOS(){
  
  //reduceProd("stripping24");
  //reduceProd("stripping21");
  //reduceProd("stripping21r1");
  //reduceProd("stripping20");
  //reduceProd("stripping20r1");
  //reduceProd("mcbs2kk");
  //reduceProd("mcbd2kpi");
  //reduceProd("mcbs2kpi");
  reduceProd("mcbd2pipi");
  //reduceProd("mchipt");
  //reduceProd("mclopt");
  //reduceProd("mcsig_bs");
  //reduceProd("mcsig_bd");

  return;
}//end vairedprod

//
// Download the input root files from EOS and call the steps to produce the reduced files with global BDT and additional variables:
//  a) CreateReducedFile: apply loose preselection
//  b) AddIsoBDT: add isolation variables
//  c) AddBDTVars: add additional variables (some of them are taken as input by the global BDT)
//  d) AddBDT: add the global BDT
//
void reduceProd(TString opt){
  _v=true;
  if (_v) cout<<"Entering reduceProd. opt = "<<opt<<endl;
  gROOT->ProcessLine(".L addIso.C+");
  gROOT->ProcessLine("addIso t");
  
  vector<std::string> file_vec;
  
  //Set vars to access EOS
  TString eos_path="/eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction/";
  TString filelist_name="";
  if (opt.Contains("stripping21r1")){ eos_path+="data/stripping21r1/"; filelist_name="stripping21r1"; }
  else if (opt.Contains("stripping24")){ eos_path+="data/stripping24/"; filelist_name="stripping24"; }
  else if (opt.Contains("stripping21")){ eos_path+="data/stripping21/"; filelist_name="stripping21"; }
  else if (opt.Contains("stripping20r1")){ eos_path+="data/stripping20r1/"; filelist_name="stripping20r1"; }
  else if (opt.Contains("stripping20")){ eos_path+="data/stripping20/"; filelist_name="stripping20"; }
  else if (opt.Contains("mcbs2kk")){ eos_path+="mc/"; filelist_name="mcbs2kk"; }
  else if (opt.Contains("mcbd2kpi")){ eos_path+="mc/"; filelist_name="mcbd2kpi"; }
  else if (opt.Contains("mcbs2kpi")){ eos_path+="mc/"; filelist_name="mcbs2kpi"; }
  else if (opt.Contains("mcbd2pipi")){ eos_path+="mc/"; filelist_name="mcbd2pipi"; }
  else if (opt.Contains("mclopt")){ eos_path+="mc/bbbar2MuMuX/"; filelist_name="mclopt"; }
  else if (opt.Contains("mchipt")){ eos_path+="mc/bbbar2MuMuX/"; filelist_name="mchipt"; }
  else if (opt.Contains("mcsig_bs")){ eos_path+="mc/Bs2MuMu/"; filelist_name="mcsig"; }
  else if (opt.Contains("mcsig_bd")){ eos_path+="mc/Bd2MuMu/"; filelist_name="mcsigbd"; }

  TString filename_flag="Dimuon";
  if (opt.Contains("stripping")) filename_flag="Dimuon";
  else if (opt.Contains("lopt")) filename_flag="lowpt";
  else if (opt.Contains("hipt")) filename_flag="highpt";
  else if (opt.Contains("mcsig_bs")) filename_flag="MC12_Bs2MuMu";
  else if (opt.Contains("mcsig_bd")) filename_flag="MC12_Bd2MuMu";
  else if (opt.Contains("bd2kpi")) filename_flag="";
  else if (opt.Contains("bs2kk")) filename_flag="";
  else if (opt.Contains("bs2kpi")) filename_flag="";
  else if (opt.Contains("bd2pipi")) filename_flag="";

  //Take the list of .root files from EOS...
  if (opt.Contains("eos")){
    TString eos_command="/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select";
    TString shell_command=eos_command+" ls "+eos_path;
    TString stdout=gSystem->GetFromPipe(shell_command);
    TObjArray *stdout_arr = stdout.Tokenize("\n");
    for (int i=0;i<stdout_arr->GetEntries();i++) file_vec.push_back(((TObjString*)stdout_arr->At(i))->String().Data());
  }
  //... or otherwise take the list of .root files from the <xxx>_list file given as input (default choice)
  else{
    filelist_name+="_list.txt";
    cout << filelist_name << endl;
    ifstream file(filelist_name);
    std::vector<std::string> line;
    string mystr;
    int ntot(0);
    while(file >> mystr){
      file_vec.push_back(mystr);
      cout << mystr << endl;
      ntot++;

    }
  }

  //Loop over the .root files and process each of them (copy it locally, apply preselection, add isolations,...,add global BDT, delete original file)
  for (int i=0;i<(int)file_vec.size();i++){
    TString filename=file_vec[i];  
 
    if (!filename.Contains(filename_flag)) continue;
    if (_v) cout<<"file "<<i<<" = "<<filename<<endl;
  

    //Copy the file locally
    TString copy_command="xrdcp -f root://eoslhcb.cern.ch/"+eos_path+filename+" .";//uncomment for production
    //TString copy_command="cp /home/rama/shared/temp/"+filename+" .";//uncomment for tests
    if (_v) cout<<copy_command<<endl;

    gSystem->Exec(copy_command);//uncomment for production

    if (filename.Contains('/')) filename = filename(filename.First('/')+1,filename.Length());
  
    cout << filename << endl;


    //Create reduced file (preselection)
    CreateReducedFile(filename,opt);

    //Add the isolations 
    AddIsoBDT(filename,"600_0.5_4_30_0.75_0_8_BDT.weights.xml","","set8_lt","",3,opt,"jpsiveto");
    AddIsoBDT(filename,"600_0.5_4_30_0.75_3_1_BDT.weights.xml","","set1_velnb","noback",1,opt,"");

    //Add other BDT input vars and remove the track and primary vertex blocks (EVB,VEL,US,PV*)
    AddBDTVars(filename);

    //Add the global BDT
    //AddBDT(filename,"1000_1.00_3_30_0.50_BDTtrain_c5.root","1000_1.00_3_30_0.50_c5_BDT.weights.xml","BDT0");
    //AddBDT(filename,"1000_1.00_3_30_0.50_BDTtrain_c22.root","1000_1.00_3_30_0.50_c22_BDT.weights.xml","BDT1");
    AddBDT(filename,"signalMC_forBDTflattening_BDT0.root","1000_1.00_3_30_0.50_c5_BDT.weights.xml","BDT0");
    AddBDT(filename,"signalMC_forBDTflattening_BDT1.root","1000_1.00_3_30_0.50_c22_BDT.weights.xml","BDT1");
    
    //Blind the mass region if data
    if (opt.Contains("stripping")) Blind(filename);

    //Delete the original .root file
    TString delete_command="rm -f "+filename+"_prereduced";;
    if (_v) cout<<delete_command<<endl;
    gSystem->Exec(delete_command);
  }
  cout<<"Loop over input files complete"<<endl;
  return;
  
}//end reduceProd

//
// Prende il file di input e ne crea uno di output con i trees B2MuMu e B2HH del file di input, ma con
// applicata una selezione per ridurre il numero di eventi
//
//
// From the input .root file create a new .root file with only the B2MuMu and B2HH trees. A loose selection
// is applied to these trees to reduce the number of events
//
void CreateReducedFile(TString inputfile_name,TString opt){
  if (_v) cout<<endl<<"Entering CreateReducedFile: inputfile_name = "<<inputfile_name<<" opt = "<<opt<<endl;

  TString path="";
  inputfile_name=path+inputfile_name;

  //The output file name is the same as the input file name
  TString outputfile_name=inputfile_name;
  
  //Move the input <file>.root to <file>.root_prereduced
  inputfile_name=inputfile_name+"_prereduced";
  TString shellcommand="mv "+outputfile_name+" "+inputfile_name;
  if (_v) cout<<" Execute shell commmand: "<<shellcommand<<" (";
  int shell_out=gSystem->Exec(shellcommand);
  if (_v) cout<<shell_out<<")"<<endl;
  if (_v) cout<<" input file = "<<inputfile_name<<" output file = "<<outputfile_name<<endl;
  
  //Create the output file
  TFile *newfile = new TFile(outputfile_name,"recreate");

  //Define some variables (possibly) used to cut on
  double b_MM,b_BDTS,b_PT,b_TAU;
  double mup_P,mum_P,mup_PT,mum_PT,mup_TRACK_GhostProb,mum_TRACK_GhostProb,mup_PIDK,mum_PIDK,mup_PIDmu,mum_PIDmu;
  bool mup_isMuon,mum_isMuon;
  bool b_L0Global_Dec,b_Hlt1Phys_Dec,b_Hlt2Phys_Dec;

  //First, consider the B2MuMu tree (the B2HH tree is considered later on)
  TString dir_name_b2mumu="B2MuMuTuple";
  TChain* ch_b2mumu=new TChain(dir_name_b2mumu+"/DecayTree");
  ch_b2mumu->Add(inputfile_name);
  TTree* oldtree_b2mumu=(TTree*) ch_b2mumu;

  //Create the directory B2MuMu in new file
  newfile->mkdir(dir_name_b2mumu);
  newfile->cd(dir_name_b2mumu);

  //Create the output tree (newtree) with the same structure as the input tree (oldtree)
  oldtree_b2mumu->SetAutoSave(3000000000);//create backup 'header' if N events>300+e6.
  TTree* newtree_b2mumu=oldtree_b2mumu->CloneTree(0);

  //Apply the loose selection to oldtree_b2mumu
  int nentries=oldtree_b2mumu->GetEntries();
  oldtree_b2mumu->SetBranchAddress("B_MM",&b_MM);
  oldtree_b2mumu->SetBranchAddress("B_BDTS",&b_BDTS);
  oldtree_b2mumu->SetBranchAddress("B_PT",&b_PT);
  oldtree_b2mumu->SetBranchAddress("B_TAU",&b_TAU);
  oldtree_b2mumu->SetBranchAddress("B_L0Global_Dec",&b_L0Global_Dec);  
  oldtree_b2mumu->SetBranchAddress("B_Hlt1Phys_Dec",&b_Hlt1Phys_Dec);  
  oldtree_b2mumu->SetBranchAddress("B_Hlt2Phys_Dec",&b_Hlt2Phys_Dec);  
  oldtree_b2mumu->SetBranchAddress("muplus_P",&mup_P);
  oldtree_b2mumu->SetBranchAddress("muplus_PT",&mup_PT);
  oldtree_b2mumu->SetBranchAddress("muplus_TRACK_GhostProb",&mup_TRACK_GhostProb);
  oldtree_b2mumu->SetBranchAddress("muplus_PIDK",&mup_PIDK);
  oldtree_b2mumu->SetBranchAddress("muplus_PIDmu",&mup_PIDmu);
  oldtree_b2mumu->SetBranchAddress("muplus_isMuon",&mup_isMuon);
  oldtree_b2mumu->SetBranchAddress("muminus_P",&mum_P);
  oldtree_b2mumu->SetBranchAddress("muminus_PT",&mum_PT);
  oldtree_b2mumu->SetBranchAddress("muminus_TRACK_GhostProb",&mum_TRACK_GhostProb);
  oldtree_b2mumu->SetBranchAddress("muminus_PIDK",&mum_PIDK);
  oldtree_b2mumu->SetBranchAddress("muminus_PIDmu",&mum_PIDmu);
  oldtree_b2mumu->SetBranchAddress("muminus_isMuon",&mum_isMuon);
  int count(0);
  double bmass_hicut=6500;
  if (opt.Contains("mc")) bmass_hicut=6000;
  if (_v) cout<<" Loop on  B2MuMu/DecayTree. nentries = "<<nentries<<endl;
  for (int i=0;i<nentries;i++){
    if (_v && !(i%10000)) cout<<" i = "<<i<<" selected = "<<count<<endl;
    oldtree_b2mumu->GetEntry(i);
    if (!(
	  b_MM>4900 && b_MM<bmass_hicut &&
	  b_BDTS>0.05 &&
	  b_PT>500 &&
	  b_TAU*1000<13.248 &&
	  mup_P<5e05 && mum_P<5e05 &&
	  mup_PT<4e04 && mum_PT<4e04 &&
	  //mup_isMuon==1 && mum_isMuon==1 &&
	  mup_TRACK_GhostProb<0.3 && mum_TRACK_GhostProb<0.3 &&
	  //mum_PIDK < 10 && mum_PIDmu>-5 && mup_PIDK<10 && mup_PIDmu>-5 &&
	  //b_L0Global_Dec==1 && b_Hlt1Phys_Dec==1 && b_Hlt2Phys_Dec==1 &&
	  1)
	) continue;
    newtree_b2mumu->Fill();//save in newtree_b2mumu only the events passing the selection
    count++;
  }//end i<nentries loop

  //Save the new file
  newfile->Write();
  delete ch_b2mumu;

  //Now repeat the procedure for the B2HH tree
  TString dir_name_b2hh="B2HHTuple";
  TChain* ch_b2hh=new TChain(dir_name_b2hh+"/DecayTree");
  ch_b2hh->Add(inputfile_name);
  TTree* oldtree_b2hh=(TTree*) ch_b2hh;

  //Create the directory B2HH in new file
  newfile->mkdir(dir_name_b2hh);
  newfile->cd(dir_name_b2hh);

  //Create the output tree (newtree) with the same structure as the input tree (oldtree)
  oldtree_b2hh->SetAutoSave(3000000000);//create backup 'header' if N events>300+e6.
  TTree* newtree_b2hh=oldtree_b2hh->CloneTree(0);

  //Apply the loose selection to oldtree_b2hh
  nentries=oldtree_b2hh->GetEntries();
  oldtree_b2hh->SetBranchAddress("B_MM",&b_MM);
  oldtree_b2hh->SetBranchAddress("B_BDTS",&b_BDTS);
  oldtree_b2hh->SetBranchAddress("B_PT",&b_PT);
  oldtree_b2hh->SetBranchAddress("B_TAU",&b_TAU);
  oldtree_b2hh->SetBranchAddress("B_L0Global_Dec",&b_L0Global_Dec);  
  oldtree_b2hh->SetBranchAddress("B_Hlt1Phys_Dec",&b_Hlt1Phys_Dec);  
  oldtree_b2hh->SetBranchAddress("B_Hlt2Phys_Dec",&b_Hlt2Phys_Dec);  
  oldtree_b2hh->SetBranchAddress("muplus_P",&mup_P);
  oldtree_b2hh->SetBranchAddress("muplus_PT",&mup_PT);
  oldtree_b2hh->SetBranchAddress("muplus_TRACK_GhostProb",&mup_TRACK_GhostProb);
  oldtree_b2hh->SetBranchAddress("muplus_PIDK",&mup_PIDK);
  oldtree_b2hh->SetBranchAddress("muplus_PIDmu",&mup_PIDmu);
  oldtree_b2hh->SetBranchAddress("muplus_isMuon",&mup_isMuon);
  oldtree_b2hh->SetBranchAddress("muminus_P",&mum_P);
  oldtree_b2hh->SetBranchAddress("muminus_PT",&mum_PT);
  oldtree_b2hh->SetBranchAddress("muminus_TRACK_GhostProb",&mum_TRACK_GhostProb);
  oldtree_b2hh->SetBranchAddress("muminus_PIDK",&mum_PIDK);
  oldtree_b2hh->SetBranchAddress("muminus_PIDmu",&mum_PIDmu);
  oldtree_b2hh->SetBranchAddress("muminus_isMuon",&mum_isMuon);
  count=0;
  bmass_hicut=6000;//for B->hh always set bmass_hicut=6.0 GeV
  cout<<" Loop su B2HH/DecayTree. nentries = "<<nentries<<endl;
  for (int i=0;i<nentries;i++){
    if (_v && !(i%10000)) cout<<" i = "<<i<<" selected = "<<count<<endl;
    oldtree_b2hh->GetEntry(i);
    if (!(
	  b_MM>4900 && b_MM<bmass_hicut &&
	  b_BDTS>0.05 &&
	  b_PT>500 &&
	  b_TAU*1000<13.248 &&
	  mup_P<5e05 && mum_P<5e05 &&
	  mup_PT<4e04 && mum_PT<4e04 &&
	  //mup_isMuon==1 && mum_isMuon==1 &&
	  mup_TRACK_GhostProb<0.3 && mum_TRACK_GhostProb<0.3 &&
	  //mum_PIDK < 10 && mum_PIDmu>-5 && mup_PIDK<10 && mup_PIDmu>-5 &&
	  //b_L0Global_Dec==1 && b_Hlt1Phys_Dec==1 && b_Hlt2Phys_Dec==1 &&
	  1)
	) continue;
    newtree_b2hh->Fill();
    count++;
  }//end i<nentries loop

  //Save the new file
  newfile->Write();
  delete ch_b2hh;

  //Copy the directory GetIntegratedLuminosity (real data only)
  if (!opt.Contains("mc")){
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
    delete oldtree_lumi;
  }

  newfile->Close();
  delete newfile;

  return;
}//end CreateReducedFile

//
// Call addIso.C/h to add the isolations
//
void AddIsoBDT(TString inputfile_name,TString weightfile_name,TString outfile_flag,TString var_name,TString cut_option,int trk_type,TString opt,TString opt2){
  if (_v) cout<<endl<<"Entering AddIsoBDT: inputfile_name = "<<inputfile_name<<" weightfile_name = "<<weightfile_name<<" outfile_flag = "<<outfile_flag<<" var_name = "<<var_name<<" cut_option = "<<cut_option<<" trk_type = "<<trk_type<<" opt = "<<opt<<" opt2 = "<<opt2<<endl;
  
  char* command=new char[200];
  sprintf(command,"t.Loop(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%i,\"%s\",\"%s\")",inputfile_name.Data(),weightfile_name.Data(),outfile_flag.Data(),var_name.Data(),cut_option.Data(),trk_type,opt.Data(),opt2.Data());
  if (_v) cout<<"command = "<<command<<endl;
  gROOT->ProcessLine(command);
  delete command;

  return;
  
}//end AddIsoBDT

//
// Call the macro to add some variables (some of them are used as input by the global BDT)
//
void AddBDTVars(TString inputfile_name){
  if (_v) cout<<endl<<"Entering AddBDTVars: inpufile_name = "<<inputfile_name<<endl;
  gROOT->ProcessLine(".L addBDTvars.cc+");
  TString command="addBDTvars(\""+inputfile_name+"\")";
  //TString command=".x addBDTvars.cc(\""+inputfile_name+"\")";
  if (_v) cout<<"command = "<<command<<endl;
  gROOT->ProcessLine(command);

  return;

}//end AddBDTvars

//
// Call the macro to add the global BDT
//
void AddBDT(TString inputfile_name,TString sigflatfile_name,TString weightfile_name,TString BDTvar_name){
  if (_v) cout<<endl<<"Entering AddBDT: inpufile_name = "<<inputfile_name<<endl;
  gROOT->ProcessLine(".L addBDT.cc+");
  TString command="addBDT(\""+inputfile_name+"\",";
  //TString command=".x addBDT.cc(\""+inputfile_name+"\",";
  command+="\""+sigflatfile_name+"\",";
  command+="\""+weightfile_name+"\",";
  command+="\""+BDTvar_name+"\")";
  if (_v) cout<<"command = "<<command<<endl;
  gROOT->ProcessLine(command);

  return;

}//end AddBDT


//
// Blind the B mass region
//
void Blind(TString inputfile_name){
  if (_v) cout<<endl<<"Entering Blind: inputfile_name = "<<inputfile_name<<endl;
  gROOT->ProcessLine(".L BlindNtuple.cc+");
  TString command="BlindNtuple(\""+inputfile_name+"\")";
  if (_v) cout<<"command = "<<command<<endl;
  gROOT->ProcessLine(command);
  
  return;
  
}//end Blind
