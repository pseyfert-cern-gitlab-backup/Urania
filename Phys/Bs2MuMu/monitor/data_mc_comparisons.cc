// author: Matteo Rama, first version 27 July 2016
//
// Macro to compare the variable distributions from different data/MC samples
//
// Instructions:
// The macro works in 2 phases: 
// a) produce the .root file with the collection of monitoring histograms for the data or MC samples to be compared
// b) produce the PDF file with the histogram comparison
//
// a) produce the .root file with the collection of monitoring histograms for the data or MC samples to be compared
//
// In if (flag==1){ ... }:
// Create a file with the list of variables, each with its selection range. The format is:
// "B_MM","4900:6500",
// "B_P","0:500000",
// ...etc...
// where the second filed gives the low and high range.
//
// Set filelist_name with the name of the file containing the var list. For example:
//   TString filelist_name="vars_rawntuples_list.txt";
//
// Set tree_name with the name of the TTree containing the vars. For example:
//    TString tree_name="B2MuMuTuple/DecayTree";
//
// Define the vectors with the name of the ROOT files, the EOS path where the ROOT files are and
// the name of the output ROOT file containing the histograms for the give sample. For example:
//   vector<TString> inputlist_S20glob;
//   inputlist_S20glob.push_back("Dimuon*.root");
//   TString path_S20glob="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction/data/stripping20/";
//   TString outputfile_S20glob="histo_S20glob.root";
//
// Call the SavePlots(...) method to access the ROOT files and collect the histograms. For example:
//   SavePlots(vars_vec,bkgcut_data,path_S20glob,inputlist_S20glob,tree_name,outputfile_S20glob);
//
// Examples are given in the macro (under the (flag==1) condition).
//
// To run it: 
// root>.L data_mc_comparison.cc
// root>data_mc_comparison(1)
//
// b) produce the PDF file with the histogram comparison
// 
// In if (flag==2){ ... }:
//
// Fill the vector inputfile_list with the names of the histo collections (ROOT files) you want to overlap. Example:
// inputfile_list.push_back("histo_S20glob.root:col=4:norm:leg=S20");//blue
// inputfile_list.push_back("histo_S21glob.root:col=2:norm:leg=S21");//red
//
// In each entry you should define the input ROOT file name, the color and the legend label, as in the example.
//
// Launch the method ComparePlots(...) which produces the PDF file with the histos overlapped
// ComparePlots(inputfile_list);

#include <iostream>
#include "TString.h"
#include "TCut.h"
#include "TChain.h"
#include "TRegexp.h"
#include "TFile.h"
#include "TH1F.h"
#include "TROOT.h"
#include "TKey.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"
#include <fstream>

void SavePlots(vector<TString> vars_vec,TCut cut,TString path,vector<TString> inputfile_vec,TString tree_name,TString outputfile_name);
void ComparePlots(vector<TString>);
void DrawPlots(vector<TH1*> his_vec,vector<int> hiscolor_vec,vector<TString> option_vec,vector<TString> leg_vec);
void GetVars(TString filename,vector<TString>& vars_vec);

void data_mc_comparisons(int flag){

 //
 // produce gli istogrammi e li salva in files .root
 //
 if (flag==1){

   //TString filelist_name="vars_rawntuples_list.txt";
   TString filelist_name="vars_reducedntuples_list.txt";
   
   //Get the vars and corresponding cuts from the input file
   vector<TString> vars_vec;
   GetVars(filelist_name,vars_vec);
   cout<<"vars_vec.size() = "<<vars_vec.size()<<endl;
   for (int i=0;i<(int)vars_vec.size();i++) cout<<"vars_vec["<<i<<"] = "<<vars_vec[i]<<endl;

   TCut s20_cut="B_FDCHI2_OWNPV>225&&muplus_IPCHI2_OWNPV>25&&muminus_IPCHI2_OWNPV>25";
   TCut trig_cut="B_L0Global_Dec==1&&B_Hlt1Phys_Dec==1&&B_Hlt2Phys_Dec==1";
   
   TCut bkgcut_mc="B_MM>4900&&B_MM<6000";
   TCut bkgcut_mc_rsb="B_MM>5447&&B_MM<6000";
   TCut sigcut="B_MM>4900&&B_MM<6000";
   bkgcut_mc+=trig_cut+s20_cut;
   
   TCut bkgcut_data="B_MM>4900&&B_MM<6000&&!(B_MM>5200&&B_MM<5447)";//blinded sig region
   TCut bkgcut_data_rsb="B_MM>5447&&B_MM<6000";//right mass sideband
   TCut bkgcut_data_ursb="B_MM>6000&&B_MM<6500";//ultra-right mass sideband
   
   bkgcut_data+=trig_cut+s20_cut;
   bkgcut_data_rsb+=trig_cut+s20_cut;
   bkgcut_data_ursb+=trig_cut+s20_cut;
   
   TString tree_name="B2MuMuTuple/DecayTree";

   //
   // stripping 20 (2012) - reduced ntuples
   //
   vector<TString> inputlist_S20;
   inputlist_S20.push_back("Dimuon*.root");
   TString path_S20="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction_bdt/data/stripping20/";
   TString outputfile_S20="histo_S20.root";

   //
   // stripping 20 (2012) - full ntuples
   //
   vector<TString> inputlist_S20glob;
   inputlist_S20glob.push_back("Dimuon*.root");
   TString path_S20glob="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction/data/stripping20/";
   TString outputfile_S20glob="histo_S20glob.root";
   TString outputfile_S20glob_rsb="histo_S20glob_rsb.root";
   
   //
   // stripping 20r1 (2011) - reduced ntuples
   //
   vector<TString> inputlist_S20r1;
   inputlist_S20r1.push_back("Dimuon*.root");
   TString path_S20r1="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction_bdt/data/stripping20r1/";
   TString outputfile_S20r1="histo_S20r1.root";

   //
   // stripping 20r1 (2011) - full ntuples
   //
   vector<TString> inputlist_S20r1glob;
   inputlist_S20r1glob.push_back("Dimuon*.root");
   TString path_S20r1glob="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction/data/stripping20r1/";
   TString outputfile_S20r1glob="histo_S20r1glob.root";
   TString outputfile_S20r1glob_rsb="histo_S20r1glob_rsb.root";
   						
   //
   // stripping 21 (2012) - reduced ntuples
   //
   vector<TString> inputlist_S21;
   inputlist_S21.push_back("Dimuon*.root");
   TString path_S21="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction_bdt/data/stripping21/";
   TString outputfile_S21="histo_S21.root";
   
   //
   // stripping 21 (2012) - full ntuples
   //
   vector<TString> inputlist_S21glob_old;
   inputlist_S21glob_old.push_back("Dimuon*.root");
   TString path_S21glob_old="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction/data/stripping21/TrackBlock/";
   TString outputfile_S21glob_old="histo_S21glob_old.root";
   TString outputfile_S21glob_old_rsb="histo_S21glob_old_rsb.root";
   
   //
   // stripping 21 (2012) - full ntuples NEW 27/7/2016
   //
   vector<TString> inputlist_S21glob;
   inputlist_S21glob.push_back("BsMuMu_data_S21_*.root");
   TString path_S21glob="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction_July2016/data/";
   TString outputfile_S21glob="histo_S21glob.root";
   TString outputfile_S21glob_rsb="histo_S21glob_rsb.root";
   
   //
   // stripping 21r1 (2011) - reduced ntuples
   //
   vector<TString> inputlist_S21r1;
   inputlist_S21r1.push_back("Dimuon*.root");
   TString path_S21r1="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction_bdt/data/stripping21r1/";
   TString outputfile_S21r1="histo_S21r1.root";

   //
   // stripping 21r1 (2011) - full ntuples
   //
   vector<TString> inputlist_S21r1glob;
   inputlist_S21r1glob.push_back("Dimuon*.root");
   TString path_S21r1glob="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction/data/stripping21r1/TrackBlock/";
   TString outputfile_S21r1glob="histo_S21r1glob.root";
   TString outputfile_S21r1glob_rsb="histo_S21r1glob_rsb.root";
   
   //
   // stripping 24 (2015) - reduced ntuples
   //
   vector<TString> inputlist_S24;
   inputlist_S24.push_back("Dimuon*.root");
   TString path_S24="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction_bdt/data/stripping24/";
   TString outputfile_S24="histo_S24.root";

   //
   // stripping 24 (2015) - full ntuples
   //
   vector<TString> inputlist_S24glob;
   inputlist_S24glob.push_back("Dimuon*.root");
   TString path_S24glob="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction/data/stripping24/";
   TString outputfile_S24glob="histo_S24glob.root";
   TString outputfile_S24glob_rsb="histo_S24glob_rsb.root";
   
   //
   // bbbar->mumu X MC (Sim06) - reduced ntuples
   //
   vector<TString> inputlist_mumuX_mc;
   inputlist_mumuX_mc.push_back("bbbar*.root");
   TString path_mumuX_mc="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction_bdt/mc/bbbar2MuMuX/";
   TString outputfile_mumuX_mc="histo_mumuX_mc.root";

   //
   // bbbar->mumu X MC (Sim06) - full ntuples
   //
   vector<TString> inputlist_mumuX_mcglob;
   inputlist_mumuX_mcglob.push_back("bbbar*.root");
   TString path_mumuX_mcglob="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction/mc/bbbar2MuMuX/";
   TString outputfile_mumuX_mcglob="histo_mumuX_mcglob.root";
   
   //
   // Bs->mumu 2015 (Sim09) - reduced ntuples
   //
   vector<TString> inputlist_BsMuMu_mc15;
   inputlist_BsMuMu_mc15.push_back("MC15_Bs2MuMu_*.root");
   TString path_BsMuMu_mc15="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction_bdt/mc/Bs2MuMu/";
   TString outputfile_BsMuMu_mc15="histo_BsMuMu_mc15.root";
   
   //
   // Bs->mumu 2015 (Sim09) - full ntuples
   //
   vector<TString> inputlist_BsMuMu_mc15glob;
   inputlist_BsMuMu_mc15glob.push_back("BsMuMu_*_MC09.root");
   TString path_BsMuMu_mc15glob="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction_July2016/MC/";
   TString outputfile_BsMuMu_mc15glob="histo_BsMuMu_mc15glob.root";
   
   //
   // Bs->mumu 2012 (Sim06b) - reduced ntuples
   //
   vector<TString> inputlist_BsMuMu_mc12;
   inputlist_BsMuMu_mc12.push_back("MC12_*.root");
   TString path_BsMuMu_mc12="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction_bdt/mc/Bs2MuMu/";
   TString outputfile_BsMuMu_mc12="histo_BsMuMu_mc12.root";

   //
   // Bs->mumu 2012 (Sim06b) - full ntuples
   //
   vector<TString> inputlist_BsMuMu_mc12glob;
   inputlist_BsMuMu_mc12glob.push_back("MC12*.root");
   TString path_BsMuMu_mc12glob="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction/mc/Bs2MuMu/";
   TString outputfile_BsMuMu_mc12glob="histo_BsMuMu_mc12glob.root";

   //
   // Bs->mumu 2011 (Sim08) - reduced ntuples
   //
   vector<TString> inputlist_BsMuMu_mc11;
   inputlist_BsMuMu_mc11.push_back("MC11_*.root");
   TString path_BsMuMu_mc11="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction_bdt/mc/Bs2MuMu/";
   TString outputfile_BsMuMu_mc11="histo_BsMuMu_mc11.root";
   
   //
   // Bs->mumu 2011 (Sim08) - full ntuples
   //
   vector<TString> inputlist_BsMuMu_mc11glob;
   inputlist_BsMuMu_mc11glob.push_back("MC11*.root");
   TString path_BsMuMu_mc11glob="root://eoslhcb.cern.ch//eos/lhcb/wg/RD/BsMuMu/ntuple_reproduction/mc/Bs2MuMu/";
   TString outputfile_BsMuMu_mc11glob="histo_BsMuMu_mc11glob.root";

   //
   // Tests
   //
   vector<TString> inputlist_s24test;
   inputlist_s24test.push_back("s24.root");
   TString path_s24test="/afs/cern.ch/user/m/masantim/public/ForMatteo/";
   TString outputfile_s24test="histo_s24test.root";

   //data
   //SavePlots(vars_vec,bkgcut_data,path_S20,inputlist_S20,tree_name,outputfile_S20);
   //SavePlots(vars_vec,bkgcut_data,path_S20r1,inputlist_S20r1,tree_name,outputfile_S20r1);
   //SavePlots(vars_vec,bkgcut_data,path_S21,inputlist_S21,tree_name,outputfile_S21);
   //SavePlots(vars_vec,bkgcut_data,path_S21r1,inputlist_S21r1,tree_name,outputfile_S21r1);
   //SavePlots(vars_vec,bkgcut_data,path_S24,inputlist_S24,tree_name,outputfile_S24);

   //data full
   //SavePlots(vars_vec,bkgcut_data,path_S20glob,inputlist_S20glob,tree_name,outputfile_S20glob);
   //SavePlots(vars_vec,bkgcut_data,path_S20r1glob,inputlist_S20r1glob,tree_name,outputfile_S20r1glob);
   //SavePlots(vars_vec,bkgcut_data,path_S21glob_old,inputlist_S21glob_old,tree_name,outputfile_S21glob_old);
   //SavePlots(vars_vec,bkgcut_data,path_S21glob,inputlist_S21glob,tree_name,outputfile_S21glob);
   //SavePlots(vars_vec,bkgcut_data,path_S21r1glob,inputlist_S21r1glob,tree_name,outputfile_S21r1glob);
   //SavePlots(vars_vec,bkgcut_data,path_S24glob,inputlist_S24glob,tree_name,outputfile_S24glob);

   //data full right sb
   //SavePlots(vars_vec,bkgcut_data_rsb,path_S20glob,inputlist_S20glob,tree_name,outputfile_S20glob_rsb);
   //SavePlots(vars_vec,bkgcut_data_rsb,path_S20r1glob,inputlist_S20r1glob,tree_name,outputfile_S20r1glob_rsb);
   //SavePlots(vars_vec,bkgcut_data_rsb,path_S21glob,inputlist_S21glob,tree_name,outputfile_S21glob_rsb);
   //SavePlots(vars_vec,bkgcut_data_rsb,path_S21r1glob,inputlist_S21r1glob,tree_name,outputfile_S21r1glob_rsb);
   //SavePlots(vars_vec,bkgcut_data_rsb,path_S24glob,inputlist_S24glob,tree_name,outputfile_S24glob_rsb);
   
   //MC full
   //SavePlots(vars_vec,bkgcut_mc,path_mumuX_mcglob,inputlist_mumuX_mcglob,tree_name,outputfile_mumuX_mcglob);
   //SavePlots(vars_vec,bkgcut_mc,path_BsMuMu_mc11glob,inputlist_BsMuMu_mc11glob,tree_name,outputfile_BsMuMu_mc11glob);
   //SavePlots(vars_vec,bkgcut_mc,path_BsMuMu_mc12glob,inputlist_BsMuMu_mc12glob,tree_name,outputfile_BsMuMu_mc12glob);
   //SavePlots(vars_vec,bkgcut_mc,path_BsMuMu_mc15glob,inputlist_BsMuMu_mc15glob,tree_name,outputfile_BsMuMu_mc15glob);
   
   //MC reduced
   SavePlots(vars_vec,bkgcut_mc,path_BsMuMu_mc15,inputlist_BsMuMu_mc15,tree_name,outputfile_BsMuMu_mc15);
   SavePlots(vars_vec,bkgcut_mc,path_BsMuMu_mc12,inputlist_BsMuMu_mc12,tree_name,outputfile_BsMuMu_mc12);
   SavePlots(vars_vec,bkgcut_mc,path_BsMuMu_mc11,inputlist_BsMuMu_mc11,tree_name,outputfile_BsMuMu_mc11);
   
   //Tests
   //SavePlots(vars_vec,bkgcut_data,path_s24test,inputlist_s24test,tree_name,outputfile_s24test);

 }//end flag==1


 //
 // Produce confronto degli istogrammi prodotti in flag==1
 //
 if (flag==2){
   vector<TString> inputfile_list;
   /*
   //inputfile_list.push_back("histo_S20.root:col=4:norm:leg=S20");//blu
   inputfile_list.push_back("histo_S20_rsb.root:col=4:norm:leg=S20 rsb");//blu
   inputfile_list.push_back("histo_S20_ursb.root:col=2:norm:leg=S20 ursb");//rosso
   //inputfile_list.push_back("histo_S21.root:col=2:norm:leg=S21");//rosso
   //inputfile_list.push_back("histo_mc.root:col=1:norm:leg=b#bar{b}#rightarrow#mu^{+}#mu^{-}X MC");//nero
   inputfile_list.push_back("histo_mc_rsb.root:col=1:norm:leg=b#bar{b}#rightarrow#mu^{+}#mu^{-}X MC");//nero
   //inputfile_list.push_back("histo_sigmc.root:col=4:norm:leg=sig MC");//blu
   */
   //inputfile_list.push_back("histo_S20.root:col=4:norm:leg=S20");//blue
   //inputfile_list.push_back("histo_S20r1.root:col=63:norm:leg=S20r1");//light blue
   //inputfile_list.push_back("histo_S21.root:col=2:norm:leg=S21");//red
   //inputfile_list.push_back("histo_S21r1.root:col=94:norm:leg=S21r1");//orange
   //inputfile_list.push_back("histo_S24.root:col=8:norm:leg=S24");//green
   //inputfile_list.push_back("histo_mumuX_mc.root:col=8:norm:leg=b#bar{b}#rightarrow#mu^{+}#mu^{-}X MC");//green
   /*
   inputfile_list.push_back("histo_S20glob.root:col=4:norm:leg=S20");//blue
   inputfile_list.push_back("histo_S21glob.root:col=2:norm:leg=S21");//red
   inputfile_list.push_back("histo_S24glob.root:col=8:norm:leg=S24");//green
   inputfile_list.push_back("histo_mumuX_mcglob.root:col=94:norm:leg=b#bar{b}#rightarrow#mu^{+}#mu^{-}X MC");//orange
   */
   
   inputfile_list.push_back("histo_BsMuMu_mc12glob.root:col=4:norm:leg=B_{s}#rightarrow#mu^{+}#mu^{-} MC12");//blu
   inputfile_list.push_back("histo_BsMuMu_mc15glob.root:col=2:norm:leg=B_{s}#rightarrow#mu^{+}#mu^{-} MC(2015)");//red
   

   ComparePlots(inputfile_list);
   
 }//end flag==2

  return;
}//end data_mc_comparisons

void SavePlots(vector<TString> vars_vec,TCut global_cut,TString inputfile_path,vector<TString> inputfile_vec,TString tree_name,TString outputfile_name){
  cout<<"*\n* Entering SavePlots(...) vars_vec size = "<<vars_vec.size()<<"\n*"<<endl;
  cout<<" path = "<<inputfile_path<<endl;
  cout<<" TTree = "<<tree_name<<endl<<endl;
  
  TChain* ch=new TChain(tree_name);
  for (int i=0;i<(int)inputfile_vec.size();i++) ch->Add(TString(inputfile_path+inputfile_vec[i]));
  
  //create the output file
  TFile* file=new TFile(outputfile_name,"recreate");
  
  int count(0);
  //loop on vars list
  for (int i=0;i<(int)vars_vec.size();i=i+2){
    count=i/2;
    cout<<" vars_vec["<<i<<"] = "<<vars_vec[i]<<" cut = "<<vars_vec[i+1]<<endl;

    //define the cut 
    TString mystr=vars_vec[i+1];
    TObjArray* split_vec=mystr.Tokenize(":");
    TString locut_str=((TObjString*)split_vec->At(0))->String();
    TString hicut_str=((TObjString*)split_vec->At(1))->String();
    double locut=atof(locut_str.Data());
    double hicut=atof(hicut_str.Data());
    TString cut_string=vars_vec[i]+">"+locut_str+"&&"+vars_vec[i]+"<"+hicut_str;
    TCut cut(cut_string);
    cout<<" locut = "<<locut<<" hicut = "<<hicut<<endl;
    cout<<" cut_string = "<<cut_string<<endl;
    cout<<endl;

    //plot var with corresponding cut
    TString his_name="his";his_name+=count;
    TH1F* his=new TH1F(his_name,TString(vars_vec[i]),100,locut,hicut);
    ch->Draw(TString(vars_vec[i])+">>"+his_name,cut+global_cut,"goff");

    //save in histo the option string (if given)
    TString opt_str="";
    if (split_vec->GetEntries()>=3) opt_str=((TObjString*)split_vec->At(2))->String();
    his->SetOption(opt_str);
    
    //save plot in output file
    his->Write();
    //delete his;
  }//end i<(int)vars_vec.size();
  file->Close();
  return;
}//end SavePlots

void ComparePlots(vector<TString> inputfile_list){
  cout<<"Entering ComparePlots"<<endl;

  //produce the list of: input .root file, histo colors, options
  vector<TString> filename_vec;
  vector<int> hiscolor_vec;
  vector<TString> option_vec;
  vector<TString> leg_vec;
  //Fill the vectors above
  for (int i=0;i<(int)inputfile_list.size();i++){
    TString mystr=inputfile_list[i];
    TObjArray* split_vec=mystr.Tokenize(":");
    filename_vec.push_back(((TObjString*)split_vec->At(0))->String());
    TString col_str=((TObjString*)split_vec->At(1))->String();
    col_str.ReplaceAll("col=","");
    hiscolor_vec.push_back(atoi(col_str));
    //get the (possible) visualization option (norm, log,...)
    option_vec.push_back(((TObjString*)split_vec->At(2))->String());
    //get the name for the legend
    TString leg_str=((TObjString*)split_vec->At(3))->String();
    leg_str.ReplaceAll("leg=","");
    leg_vec.push_back(leg_str);
  }

  //open the .root input files
  const int nfiles=(int)filename_vec.size();
  TFile* file_vec[nfiles];
  for (int i=0;i<(int)filename_vec.size();i++) file_vec[i]=new TFile(filename_vec[i]);
  
  //Loop over the histograms of the first file. For each histo, gets the same
  //histo in the other files and draw them superimposed
  TIter next(file_vec[0]->GetListOfKeys());
  TKey* key;
  TCanvas* canvas=new TCanvas("canvas","titolo canvas",700,500);
  int count(0);
  TString output_file="./canvas.pdf";
  while ((key=(TKey*)next())){
    //print the canvas created in prev iteration
    if (count==1) canvas->Print(output_file+"(");
    if (count>1) canvas->Print(output_file);
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if (!cl->InheritsFrom("TH1")) continue;
    TString his_name=key->GetName();
    cout<<"his_name = "<<his_name<<endl;
    TH1 *h = (TH1*)key->ReadObj();
    vector<TH1*> his_vec;
    his_vec.push_back(h);
    //loop over the other files and take the same histo, to superimpose it
    for (int j=1;j<nfiles;j++){
      TH1* h=(TH1*)file_vec[j]->Get(his_name);
      his_vec.push_back(h);
    }
    DrawPlots(his_vec,hiscolor_vec,option_vec,leg_vec);
    count++;
  }
  canvas->Print(output_file+")");
}//end ComparePlots


void DrawPlots(vector<TH1*> his_vec,vector<int> hiscolor_vec,vector<TString> option_vec,vector<TString> leg_vec){
  cout<<"Entering DrawPlots"<<endl;
  for (int i=0;i<(int)leg_vec.size();i++) cout<<"leg_vec["<<i<<"] = "<<leg_vec[i]<<endl;
  float max=0;
  for (int i=0;i<(int)his_vec.size();i++){
    //his_vec[i]->SetDefaultSumw2(1);
    his_vec[i]->Sumw2();
    if (option_vec[i].Contains("norm") && his_vec[i]->GetEntries()>0) his_vec[i]->Scale(1./his_vec[i]->GetEntries());    
    if (his_vec[i]->GetMaximum()>max) max=his_vec[i]->GetMaximum();
    cout<<"i = "<<i<<" his_vec[i]->GetMaximum() = "<<his_vec[i]->GetMaximum()<<endl;
    his_vec[i]->SetLineColor(hiscolor_vec[i]);
  }

  bool log_scale=false;
  TString hisopt_str=his_vec[0]->GetOption();
  if (hisopt_str.Contains("log")) log_scale=true;
  //reset (possible) option of the histos
  for (int i=0;i<(int)his_vec.size();i++) his_vec[i]->SetOption("");
  //Set histo line width to 2
  for (int i=0;i<(int)his_vec.size();i++) his_vec[i]->SetLineWidth(2);
  
  if (log_scale){
    his_vec[0]->SetMaximum(10*max);
    his_vec[0]->SetMinimum(his_vec[0]->GetMaximum()*1e-6);
  }
  else {
    his_vec[0]->SetMaximum(1.2*max);
    his_vec[0]->SetMinimum(0);
  }
  
  //draw the first histo and set the log scale of GPad (if required)
  his_vec[0]->Draw("e");
  if (log_scale) gPad->SetLogy();
  else gPad->SetLogy(0);
  for (int i=1;i<(int)his_vec.size();i++){
    his_vec[i]->Draw("esame");
  }
  
  //draw the legend
  TLegend* leg=new TLegend(0.45,0.78,0.55,0.88);
  leg->SetFillColor(10);
  leg->SetLineColor(10);
  leg->SetLineStyle(0);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.03);
  for (int i=0;i<(int)his_vec.size();i++) leg->AddEntry(his_vec[i],leg_vec[i]);
  leg->Draw();
  gStyle->SetOptStat(0);
  return;
}//end DrawPlots

void GetVars(TString filename,vector<TString>& vars_vec){
  
  ifstream file(filename);
  std::vector<std::string> line;
  string mystr;
  while (!file.eof()){
    getline(file,mystr);
    TString line(mystr);
    if (!line.Contains("\"")) continue;
    cout<<"line = "<<line<<endl;
    TObjArray* split_vec=line.Tokenize(",");
    TString var=((TObjString*)split_vec->At(0))->String();
    TString cut=((TObjString*)split_vec->At(1))->String();
    var.ReplaceAll("\"","");
    cut.ReplaceAll("\"","");
    vars_vec.push_back(var);
    vars_vec.push_back(cut);
    cout<<"var = "<<var<<" cut = "<<cut<<endl;
  }
  cout<<"Esco"<<endl;
  return;
}//end GetVars
