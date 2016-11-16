#include <iostream>
#include <string>        
#include <fstream>       
#include "root_libs.h"   
#include <vector>        
#include "Riostream.h"  

#include "TMVA/Reader.h"

void help()
{
  cout << endl << "      addbdt       " << endl
       << " -h             : print this help " << endl
       << " -f [file name]    " << endl
       << " -d [dir name]  :  directory inside root file " << endl
       << " -t [tree name] :  tree inside directory   " << endl
       << " -c [category]  : 0 = B_s0 muplus muminus " << endl
       << "                : 1 = B0 muplus muminus   " << endl
       << "                : -1 = B_s0 muplus muplus0   " << endl
       << endl;
  
}

void addBDT(TString fname, TString dname, TString tname, int flaggo)
{
  
  Info("addBDT", "Going to add BDT for file  %s \n and tree %s/%s ", 
       fname.Data(), dname.Data(), tname.Data());
  
  //Load the histogram for flattening
  TString flat_file = "weights/Hflat_BDT9_BDTS05_withsm.root";
  
  Info("addBDT","Using flattening file %s", flat_file.Data());
  
  TFile fFlatter2(flat_file,"READ");
  TH1F* h_flat05 = ((TH1F*)fFlatter2.Get("h_flat"));
  //Load the file with the ntuple to update
  TString met = "";
  if(fname.Contains("castor")) met = "rfio:";
  TFile *f = TFile::Open(met+fname,"update");
  f->cd(dname);

  TTree *t = (TTree*)f->Get(dname+"/"+tname);
  //Declare variables and set branches
  //Frascati
  //Old BDT (9 variables)
  Double_t B_s0_CTAU_ps;   
  Double_t B_s0_TAU;   
  Double_t muplus_MINIPCHI2;  
  Double_t muminus_MINIPCHI2;  
  Double_t B_s0_D1_isolation_Giampi;
  Double_t B_s0_D2_isolation_Giampi;
  Double_t B_s0_PT;
  Double_t B_s0_CDFiso;
  Double_t B_s0_yetanother_CDF_iso;
  Double_t muplus_PT;  
  Double_t muminus_PT;  
  Double_t B_s0_cosnk;
  Double_t B_s0_doca;  
  Double_t B_s0_IP_OWNPV;

  Double_t B_s0_ENDVERTEX_CHI2;
  Double_t B_s0_DIRA_OWNPV;
  Double_t B_s0_FDCHI2_OWNPV;
  Double_t muplus_MINIP;
  Double_t muminus_MINIP;
  Double_t B_s0_FD_OWNPV;


  TBranch        *b_B_s0_PT;   //!
  TBranch        *b_B_s0_D1_isolation_Giampi;   //!
  TBranch        *b_B_s0_D2_isolation_Giampi;   //!
  TBranch        *b_B_s0_CDFiso;   //!
  TBranch        *b_B_s0_yetanother_CDF_iso;
  TBranch        *b_B_s0_cosnk;   //!
  TBranch        *b_B_s0_CTAU_ps;   //!
  TBranch        *b_B_s0_TAU;   //!
  TBranch        *b_B_s0_doca;   //!
  TBranch        *b_B_s0_IP_OWNPV;   //!
  TBranch        *b_B_s0_FD_OWNPV;   //!
  TBranch        *b_B_s0_FDCHI2_OWNPV;   //!
  TBranch        *b_B_s0_DIRA_OWNPV;   //!
  TBranch        *b_B_s0_ENDVERTEX_CHI2;   //!
  TBranch        *b_muminus_MINIP;   //!
  TBranch        *b_muminus_MINIPCHI2;   //!
  TBranch        *b_muminus_PT;   //!
  TBranch        *b_muplus_MINIP;   //!
  TBranch        *b_muplus_MINIPCHI2;   //!
  TBranch        *b_muplus_PT;   //!

  TString Bname = "";
  TString nameplus = "";
  TString nameminus = "";
  if (flaggo == 0){
    Bname = "B_s0";
    nameplus = "muplus";
    nameminus = "muminus";
  }else if (flaggo == 1){
    Bname = "B0";
    nameplus = "muplus";
    nameminus = "muminus";
  }else if (flaggo == -1){ // Opposite sign
    Bname = "B_s0";
    nameplus = "muplus";
    nameminus = "muplus0";
  }else{
    Error("addBDT", "Flag not known %i ", flaggo);
    return ;
  }

  t->SetBranchAddress(Bname+"_IP_OWNPV", &B_s0_IP_OWNPV, &b_B_s0_IP_OWNPV);
  t->SetBranchAddress(Bname+"_FD_OWNPV", &B_s0_FD_OWNPV, &b_B_s0_FD_OWNPV);
  t->SetBranchAddress(Bname+"_FDCHI2_OWNPV", &B_s0_FDCHI2_OWNPV, &b_B_s0_FDCHI2_OWNPV);
  t->SetBranchAddress(Bname+"_DIRA_OWNPV", &B_s0_DIRA_OWNPV, &b_B_s0_DIRA_OWNPV);
  t->SetBranchAddress(Bname+"_ENDVERTEX_CHI2", &B_s0_ENDVERTEX_CHI2, &b_B_s0_ENDVERTEX_CHI2);
  t->SetBranchAddress(Bname+"_PT", &B_s0_PT, &b_B_s0_PT);
  t->SetBranchAddress(Bname+"_doca", &B_s0_doca, &b_B_s0_doca);
  t->SetBranchAddress(Bname+"_D1_isolation_Giampi", &B_s0_D1_isolation_Giampi, &b_B_s0_D1_isolation_Giampi);
  t->SetBranchAddress(Bname+"_D2_isolation_Giampi", &B_s0_D2_isolation_Giampi, &b_B_s0_D2_isolation_Giampi);
  t->SetBranchAddress(Bname+"_CDFiso", &B_s0_CDFiso, &b_B_s0_CDFiso);
  t->SetBranchAddress(Bname+"_yetanother_CDF_iso", &B_s0_yetanother_CDF_iso, &b_B_s0_yetanother_CDF_iso);
  t->SetBranchAddress(Bname+"_cosnk", &B_s0_cosnk, &b_B_s0_cosnk);
  t->SetBranchAddress(Bname+"_CTAU_ps", &B_s0_CTAU_ps, &b_B_s0_CTAU_ps);
  t->SetBranchAddress(Bname+"_TAU", &B_s0_TAU, &b_B_s0_TAU);
  TString ipname = "_MINIP";
  TString ipchi2name = "_MINIPCHI2";
  //TString ipname = "_IP_OWNPV";
  //TString ipchi2name = "_IPCHI2_OWNPV";
  
  
  t->SetBranchAddress(nameplus+ipname,     &muplus_MINIP,  &b_muplus_MINIP);
  t->SetBranchAddress(nameminus+ipname,    &muminus_MINIP, &b_muminus_MINIP);
  t->SetBranchAddress(nameplus+ipchi2name, &muplus_MINIPCHI2, &b_muplus_MINIPCHI2);
  t->SetBranchAddress(nameminus+ipchi2name,&muminus_MINIPCHI2,&b_muminus_MINIPCHI2);
  t->SetBranchAddress(nameplus+"_PT", &muplus_PT, &b_muplus_PT);
  t->SetBranchAddress(nameminus+"_PT", &muminus_PT, &b_muminus_PT);

  //New variables
  Float_t bBDT05;     //BDTS classifier output
  Float_t bBDT05flat; //flat BDTS output
  Float_t var0,var1,var2,var3,var4,var5,var6,var7,var8;

  TString method = "BDTD";
  std::cout << "----------------------------------------------------" << std::endl;
  std::cout << "\nMethod used: " << method << std::endl;
  std::cout << "----------------------------------------------------" << std::endl;



  TBranch * bBDT05Branch = t->Branch("bBDT05",&bBDT05,"bBDT05/F");
  TBranch * bBDT05flatBranch = t->Branch("bBDT05flat",&bBDT05flat,"bBDT05flat/F");

  TMVA::Reader *readerb = new TMVA::Reader( "!Color:!Silent" );
  readerb->AddVariable("B_tau"        ,&var0);
  readerb->AddVariable("minIPSalldaug",&var1);
  readerb->AddVariable("iso5"         ,&var2);
  readerb->AddVariable("B_PT"         ,&var3);
  readerb->AddVariable("mu_CDFiso"    ,&var4);
  readerb->AddVariable("mu_minPT"     ,&var5);
  readerb->AddVariable("mu_polar"     ,&var6);
  readerb->AddVariable("mu_DOCA"      ,&var7);
  readerb->AddVariable("B_IP"         ,&var8);


  TString dir    = "weights/";
  TString prefix = "TMVAClassification";
  TString methodName = method;
  methodName += TString(" method"); 

  TString weightFile2 = dir + prefix + TString("_BDT9_BDTS05_root30") + TString(".weights.xml");   
  readerb->BookMVA( methodName, weightFile2 );

  Int_t nentries = (Int_t) t->GetEntries();
  for (Int_t i = 0; i<nentries; i++){
    if (i%5000 == 0) std::cout << "--- ... Processing event: " << i << std::endl;

    t->GetEntry(i);
  
    //    var0 = B_s0_CTAU_ps;     
    var0 = B_s0_TAU*1000;     
    var1 = sqrt(TMath::Min(muplus_MINIPCHI2,muminus_MINIPCHI2));    
    var2 = B_s0_D1_isolation_Giampi+B_s0_D2_isolation_Giampi;// the isos are already defined as float
    var3 = B_s0_PT;      
    var4 = B_s0_yetanother_CDF_iso;  
    var5 = TMath::Min(muplus_PT,muminus_PT);
    var6 = B_s0_cosnk;   
    var7 = B_s0_doca;    
    var8 = B_s0_IP_OWNPV;  
    

    bBDT05 = readerb->EvaluateMVA(methodName);
    bBDT05flat = 
      ((Float_t)h_flat05->Integral(1,h_flat05->FindBin(bBDT05)))/
      (Float_t)h_flat05->Integral(1,h_flat05->GetNbinsX());
    bBDT05Branch->Fill();
    bBDT05flatBranch->Fill();

  }
  t->Write("",TObject::kOverwrite);

  f->Close();
  fFlatter2.Close();
  
  cout << endl << "-----------------------------------" << endl;
  
}



//============================================================
// MAIN
//============================================================
int main(int argc, char **argv){
  TString fname;
  TString dname;
  TString tname = "DecayTree";
  int flaggo = 0;

  if(argc<2){
    help() ;
    return 1;
  }

  for(Int_t i=1; i<argc; i++){
    TString opt(argv[i]);
    cout << " Parsing option: " << opt << endl;
    if(opt.Contains("-h")){
      help();
      return 0;
    }else if(opt.Contains("-f")){
      i++;
      TString val(argv[i]);
      fname = val; 
    }else if(opt.Contains("-d")){
      i++;
      TString val(argv[i]);
      dname = val;
    }else if(opt.Contains("-t")){
      i++;
      TString val(argv[i]);
      tname = val;
    }else if(opt.Contains("-c")){
      i++;
      TString val(argv[i]);
      flaggo = val.Atoi();
    }else{
      Error("Option parsing...","unknown option %s",opt.Data());
      return -1;
    }
  }

  if(fname ==""){
    Error("","You must specify the file name");
    cout << endl;
    help();
    return -1;
  }
  

  if(dname != ""){
    addBDT(fname, dname, tname,flaggo);
    return 0;
  }
  Info("" ," No directory specified: will try B2MuMuTuple and B2HHTuple" );
  
  
  // If no dir is specified do both
  addBDT(fname, "B2MuMuTuple", tname,  flaggo);
  
  cout << endl;
  
  
  addBDT(fname, "B2HHTuple",   tname,  flaggo);


  cout << " This is the end..." << endl;
  
  return 0;
}
