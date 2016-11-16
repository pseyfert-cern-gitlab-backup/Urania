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
  TFile fFlatter2("weights/flatter_BDT12.root","READ");
  TH1D* h_flat12 = ((TH1D*)fFlatter2.Get("h_BDTout"));
  //Load the file with the ntuple to update
  //Load the file with the ntuple to update
  TString met = "";
  if(fname.Contains("castor")) met = "rfio:";
  TFile *f = TFile::Open(met+fname,"update");
  f->cd(dname);

  TTree *t = (TTree*)f->Get(dname+"/"+tname);


  //Declare variables and set branches
  //Frascati


  Double_t B_s0_TAU;   
  Double_t B_s0_MM;   
  Double_t muplus_MINIPCHI2;  
  Double_t muminus_MINIPCHI2;  
  Double_t B_s0_D1_isolation_Giampi;
  Double_t B_s0_D2_isolation_Giampi;
  Double_t B_s0_CDFiso;
  Double_t B_s0_yetanother_CDF_iso;
  Double_t muplus_PT;  
  Double_t muminus_PT;  
  Double_t B_s0_doca;  
  Double_t B_s0_IP_OWNPV;
  Double_t B_s0_ENDVERTEX_CHI2;
  Double_t B_s0_DIRA_OWNPV;
  Double_t muplus_MINIP;
  Double_t muminus_MINIP;
  Double_t B_s0_cosnk;
  Double_t B_s0_PT;
  Double_t B_s0_otherB_ang;
  Double_t B_s0_otherB_boo_ang;
  Double_t muplus_phi; 
  Double_t muminus_phi;
  Double_t muplus_eta; 
  Double_t muminus_eta;

  TBranch        *b_B_s0_PT;   //!
  TBranch        *b_B_s0_D1_isolation_Giampi;   //!
  TBranch        *b_B_s0_D2_isolation_Giampi;   //!
  TBranch        *b_B_s0_CDFiso;   //!
  TBranch        *b_B_s0_yetanother_CDF_iso;
  TBranch        *b_B_s0_cosnk;   //!
  TBranch        *b_B_s0_TAU;   //!
  TBranch        *b_B_s0_MM;   //!
  TBranch        *b_B_s0_doca;   //!
  TBranch        *b_B_s0_IP_OWNPV;   //!
  TBranch        *b_B_s0_DIRA_OWNPV;   //!
  TBranch        *b_B_s0_ENDVERTEX_CHI2;   //!
  TBranch        *b_muminus_MINIP;   //!
  TBranch        *b_muminus_MINIPCHI2;   //!
  TBranch        *b_muminus_PT;   //!
  TBranch        *b_muplus_MINIP;   //!
  TBranch        *b_muplus_MINIPCHI2;   //!
  TBranch        *b_muplus_PT;   //!
  TBranch        *b_B_s0_otherB_ang;   //!
  TBranch        *b_B_s0_otherB_boo_ang;   //!
  TBranch        *b_muminus_eta;   //!
  TBranch        *b_muminus_phi;   //!
  TBranch        *b_muplus_eta;   //!
  TBranch        *b_muplus_phi;   //!

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
  }else if (flaggo == 2){
    Bname = "Bplus";
    nameplus = "muplus";
    nameminus = "muminus";
  }else if (flaggo == 3){
    Bname = "B_s0";
    nameplus = "eplus";
    nameminus = "muminus";
  }else if (flaggo == 4){
    Bname = "B_s0";
    nameplus = "eplus";
    nameminus = "eminus";
  }else{
    std::cout << "wrong flag" << std::endl;
    return ;
  }

  t->SetBranchAddress(Bname+"_IP_OWNPV", &B_s0_IP_OWNPV, &b_B_s0_IP_OWNPV);
  t->SetBranchAddress(Bname+"_DIRA_OWNPV", &B_s0_DIRA_OWNPV, &b_B_s0_DIRA_OWNPV);
  t->SetBranchAddress(Bname+"_ENDVERTEX_CHI2", &B_s0_ENDVERTEX_CHI2, &b_B_s0_ENDVERTEX_CHI2);
  t->SetBranchAddress(Bname+"_PT", &B_s0_PT, &b_B_s0_PT);
  t->SetBranchAddress(Bname+"_doca", &B_s0_doca, &b_B_s0_doca);
  t->SetBranchAddress(Bname+"_D1_isolation_Giampi", &B_s0_D1_isolation_Giampi, &b_B_s0_D1_isolation_Giampi);
  t->SetBranchAddress(Bname+"_D2_isolation_Giampi", &B_s0_D2_isolation_Giampi, &b_B_s0_D2_isolation_Giampi);
  t->SetBranchAddress(Bname+"_CDFiso", &B_s0_CDFiso, &b_B_s0_CDFiso);
  t->SetBranchAddress(Bname+"_yetanother_CDF_iso", &B_s0_yetanother_CDF_iso, &b_B_s0_yetanother_CDF_iso);
  t->SetBranchAddress(Bname+"_cosnk", &B_s0_cosnk, &b_B_s0_cosnk);
  t->SetBranchAddress(Bname+"_TAU", &B_s0_TAU, &b_B_s0_TAU);
  t->SetBranchAddress(Bname+"_MM", &B_s0_MM, &b_B_s0_MM);
  
  t->SetBranchAddress(nameplus+"_MINIP",     &muplus_MINIP,  &b_muplus_MINIP);
  t->SetBranchAddress(nameminus+"_MINIP",    &muminus_MINIP, &b_muminus_MINIP);
  t->SetBranchAddress(nameplus+"_MINIPCHI2", &muplus_MINIPCHI2, &b_muplus_MINIPCHI2);
  t->SetBranchAddress(nameminus+"_MINIPCHI2",&muminus_MINIPCHI2,&b_muminus_MINIPCHI2);
  t->SetBranchAddress(nameplus+"_PT", &muplus_PT, &b_muplus_PT);
  t->SetBranchAddress(nameminus+"_PT", &muminus_PT, &b_muminus_PT);

  t->SetBranchAddress(nameminus+"_eta", &muminus_eta, &b_muminus_eta);
  t->SetBranchAddress(nameminus+"_phi", &muminus_phi, &b_muminus_phi);
  t->SetBranchAddress(nameplus+"_eta", &muplus_eta, &b_muplus_eta);
  t->SetBranchAddress(nameplus+"_phi", &muplus_phi, &b_muplus_phi);
  t->SetBranchAddress(Bname+"_otherB_ang", &B_s0_otherB_ang, &b_B_s0_otherB_ang);
  t->SetBranchAddress(Bname+"_otherB_boo_ang", &B_s0_otherB_boo_ang, &b_B_s0_otherB_boo_ang);

  Float_t BDT12;     //BDTS classifier output
  Float_t BDT12flat; //flat BDTS output
  Float_t var0,var1,var2,var3,var4,var5,var6,var7,var8,var9,var10,var11,spect0;

  TString method = "BDTD";
  std::cout << "----------------------------------------------------" << std::endl;
  std::cout << "\nMethod used: " << method << std::endl;
  std::cout << "----------------------------------------------------" << std::endl;

  TBranch * BDT12Branch = t->Branch("BDT12",&BDT12,"BDT12/F");
  TBranch * BDT12flatBranch = t->Branch("BDT12flat",&BDT12flat,"BDT12flat/F");

  TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
  reader->AddVariable("B_s0_TAU_ps",         &var0);
  reader->AddVariable("mu_MINIPS",           &var1);
  reader->AddVariable("sum_isolation",       &var2);
  reader->AddVariable("B_s0_PT",             &var3);
  reader->AddVariable("B_s0_yetanother_CDF_iso", &var4);
  reader->AddVariable("B_s0_cosnk",          &var5);
  reader->AddVariable("B_s0_doca",           &var6);
  reader->AddVariable("B_s0_IP_OWNPV",       &var7);
  reader->AddVariable("mu_AbsPhi",          &var8);
  reader->AddVariable("mu_DeltaEta",        &var9);
  reader->AddVariable("B_s0_otherB_ang",    &var10);
  reader->AddVariable("B_s0_otherB_boo_ang",&var11);
  reader->AddSpectator("B_s0_MM",&spect0);

  TString dir    = "weights/";
  TString prefix = "TMVAClassification";
  TString methodName = method;
  methodName += TString(" method"); 
  //TMVAClassification_BDTD7_BDTScut0.05_mva_1000_4500_6_30_0.50_518.weights.xml
  TString weightFile2 = dir + prefix + TString("_BDTD7_BDTScut0.05_mva_1000_4500_6_30_0.50_518") + TString(".weights.xml");   

  reader->BookMVA( methodName, weightFile2 );

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
    var5 = B_s0_cosnk;   
    var6 = B_s0_doca;    
    var7 = B_s0_IP_OWNPV;  
    var8 = fabs(muplus_phi-muminus_phi);           
    var9 = fabs(muplus_eta-muminus_eta);           
    var10= B_s0_otherB_ang;           
    var11= B_s0_otherB_boo_ang;           
    spect0 = B_s0_MM;

    BDT12 = reader->EvaluateMVA(methodName);
    BDT12flat = 
      ((Float_t) h_flat12->Integral(1,h_flat12->FindBin(BDT12)))/
      (Float_t) h_flat12->Integral(1,h_flat12->GetNbinsX());
    BDT12Branch->Fill();
    BDT12flatBranch->Fill();

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
