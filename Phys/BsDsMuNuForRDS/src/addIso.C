//
// Authors: Matteo Rama (INFN Pisa), 29 March 2016
//
#define addIso_cxx
#include "addIso.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "TString.h"
#include <sstream>
#include <fstream>
//#include <iostream>
#include "TMVA/Reader.h"
#include "TSystem.h"
#include "TLorentzVector.h"

void addIso::Loop(TString inputfile_name,TString weightfile_name,TString outfile_flag,TString var_name,TString cut_option,int trk_type,TString opt,TString opt2)
{
  cout<<"Entering addIso::Loop: inputfile_name = "<<inputfile_name<<" weightfile_name = "<<weightfile_name<<" outfile_flag = "<<outfile_flag<<" var_name = "<<var_name<<" cut_option = "<<cut_option<<" trk_type = "<<trk_type<<endl;
  _v=false;

  TString path="";
  inputfile_name=path+inputfile_name;

  //Define output file name
  TString outputfile_name=inputfile_name;

  //Move input file.root into file.root_save
  inputfile_name=inputfile_name+"_preaddiso";
  TString shellcommand="mv "+outputfile_name+" "+inputfile_name;
  cout<<" Execute shell command  = "<<shellcommand<<" (";
  int shell_out=gSystem->Exec(shellcommand);
  cout<<shell_out<<")"<<endl;
  cout<<" input file = "<<inputfile_name<<" output file = "<<outputfile_name<<endl;
  
  //Create output file
  TFile* newfile=TFile::Open(outputfile_name,"RECREATE");

  //
  // Take B2MuMu tree
  //
  TString dir_name_b2mumu="B2MuMuTuple";
  TChain* ch_b2mumu=new TChain(dir_name_b2mumu+"/DecayTree");
  ch_b2mumu->Add(inputfile_name);
  TTree* oldtree_b2mumu=(TTree*) ch_b2mumu;
  int nentries=oldtree_b2mumu->GetEntries();
  
  //Create B2MuMu dir in new file
  newfile->mkdir(dir_name_b2mumu);
  newfile->cd(dir_name_b2mumu);

  cout<<"Calling oldtree_b2mumu->CloneTree"<<endl;
  TTree * clonetree_b2mumu = oldtree_b2mumu->CloneTree();
  cout<<"Called oldtree_b2mumu->CloneTree"<<endl;
  Init(oldtree_b2mumu);
  cout<<"Init(oldtree_b2mumu) done"<<endl;

  //
  // Create new branches to be added to the original ttree
  //
  double iso_max,iso_max2,iso_ave2,iso_ave3;
  double iso_mup_1st,iso_mup_2nd,iso_mum_1st,iso_mum_2nd;
  TBranch *isoBranch_1 = clonetree_b2mumu->Branch("iso_max_"+var_name,&iso_max,"iso_max_"+var_name+"/D");
  TBranch *isoBranch_2 = clonetree_b2mumu->Branch("iso_max2_"+var_name,&iso_max2,"iso_max2_"+var_name+"/D");
  TBranch *isoBranch_3 = clonetree_b2mumu->Branch("iso_ave2_"+var_name,&iso_ave2,"iso_ave2_"+var_name+"/D");
  TBranch *isoBranch_4 = clonetree_b2mumu->Branch("iso_ave3_"+var_name,&iso_ave3,"iso_ave3_"+var_name+"/D");
  TBranch *isoBranch_5 = clonetree_b2mumu->Branch("iso_mup_1st_"+var_name,&iso_mup_1st,"iso_mup_1st_"+var_name+"/D");
  TBranch *isoBranch_6 = clonetree_b2mumu->Branch("iso_mup_2nd_"+var_name,&iso_mup_2nd,"iso_mup_2nd_"+var_name+"/D");
  TBranch *isoBranch_7 = clonetree_b2mumu->Branch("iso_mum_1st_"+var_name,&iso_mum_1st,"iso_mu,_1st_"+var_name+"/D");
  TBranch *isoBranch_8 = clonetree_b2mumu->Branch("iso_mum_2nd_"+var_name,&iso_mum_2nd,"iso_mum_2nd_"+var_name+"/D");

  double muplus_jpsimass,muminus_jpsimass;
  TBranch* jpsivetoBranch_mup=0;
  TBranch* jpsivetoBranch_mum=0;
  bool do_jpsiveto=(opt2.Contains("jpsiveto")?true:false);
  if (do_jpsiveto){
    jpsivetoBranch_mup = clonetree_b2mumu->Branch("muplus_jpsimass",&muplus_jpsimass,"muplus_jpsimass/D");
    jpsivetoBranch_mum = clonetree_b2mumu->Branch("muminus_jpsimass",&muminus_jpsimass,"muminus_jpsimass/D");
  }
  
  //
  // Extract the isoBDDT vars from the weight file
  //
  TString weight_path;
  weight_path="./weights/";

  TString weightfile_totname=weight_path+weightfile_name;
  vector<string> inputvars_vec=getBDTVars(weightfile_totname,"input");
  vector<string> specvars_vec=getBDTVars(weightfile_totname,"spec");

  //
  //Create and setup TMVA reader
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
  reader->BookMVA("BDT method",weightfile_totname);
  
  //
  // Loop over oldtree_b2mumu, compute new isolations, save new TBranches
  //
  fChain=oldtree_b2mumu;
  if (fChain == 0) return;
  //Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  cout<<"nentries = "<<nentries<<endl;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
     if (!(jentry%1000)) cout<<"jentry = "<<jentry<<endl;
     _jentry=jentry;

    // Loop over long tracks and identify the two muons 
    int muid_vec[2]={-1,-1};
    getMuonTrackIndex(muid_vec);
    _mup_id=muid_vec[0];
    _mum_id=muid_vec[1];

    //iso1_vec is the vector containing the isoBDT, w.r.t. muplus, of all track in the event with the right trk_type. 
    //iso2_vec contains the isoBDT w.r.t. muminus
    vector<double> iso1_vec;
    vector<double> iso2_vec;

    int Ntracks=0;
    if (trk_type==1) Ntracks=VEL_num;
    if (trk_type==3) Ntracks=EVB_Nparts;
    if (trk_type==4) Ntracks=US_num;
    for (int i=0;i<Ntracks;i++){
      //In case of long tracks, skip the two muon candidates
      if (trk_type==3 && (i==_mup_id || i==_mum_id)) continue;
      //In case of long and US tracks, skip tracks without a defined NN<xxx> (<xxx>=mu,pi,k)
      if (trk_type==3 && (EVB_par_NNpi[i]<0 || EVB_par_NNk[i]<0 || (EVB_par_isMuon[i]==1 && EVB_par_NNmu[i]<0))) continue;
      if (trk_type==4 && (US_par_NNpi[i]<0 || US_par_NNk[i]<0 || (US_par_isMuon[i]==1 && US_par_NNmu[i]<0))) continue;
      //In case of VEL tracks, if cutoption="noback" skip tracks with VEL_par_back==1
      if (trk_type==1 && cut_option=="noback" && VEL_par_back[i]==1) continue;

      //Compute the value of all vars trk_<xxx>. Some of them are used by getVal(...)
      ComputeIsoBDTVars_new(trk_type,i);

      for (int j=0;j<(int)inputvars_vec.size();j++){
	var[j]=getVal(inputvars_vec[j],_mup_id);
      }
      double myiso1=reader->EvaluateMVA("BDT method");
      iso1_vec.push_back(myiso1);//store in iso1_vec the isoBDT wrt muplus
    
      for (int j=0;j<(int)inputvars_vec.size();j++){
	var[j]=getVal(inputvars_vec[j],_mum_id);
      }
      double myiso2=reader->EvaluateMVA("BDT method");
      iso2_vec.push_back(myiso2);//store in iso2_vec the isoBDT wrt muminus
      
    }//end i<Ntracks
    
    //
    // compute the J/psi veto variables
    //
    muplus_jpsimass=0;
    muminus_jpsimass=0;
    if (do_jpsiveto){
      double m_mu=105.658;
      TLorentzVector p4_mup(muplus_PX,muplus_PY,muplus_PZ,muplus_PE);
      TLorentzVector p4_mum(muminus_PX,muminus_PY,muminus_PZ,muminus_PE);
      for (int i=0;i<EVB_Nparts;i++){
	if (i==_mup_id || i==_mum_id) continue;//skip the signal muons
	if(EVB_par_NNmu[i]<0.3) continue;//skip longtracks non consistent with being muons
	double e_trk=sqrt(EVB_par_p[i]*EVB_par_p[i]+m_mu*m_mu);//si assume che la traccia sia un vero mu
	TLorentzVector p4_trk(EVB_par_px[i],EVB_par_py[i],EVB_par_pz[i],e_trk);
	TLorentzVector p4_comb;
	if (EVB_par_chg[i]==1){
	  p4_comb=p4_trk+p4_mum;
	  double m_comb=p4_comb.Mag();
	  if (fabs(m_comb-3097)<fabs(muminus_jpsimass-3097)) muminus_jpsimass=m_comb;
	}
	if (EVB_par_chg[i]==-1){
	  p4_comb=p4_trk+p4_mup;
	  double m_comb=p4_comb.Mag();
	  if (fabs(m_comb-3097)<fabs(muplus_jpsimass-3097)) muplus_jpsimass=m_comb;
	}
      }//end i<EVB_Nparts
    }//end do_jpsiveto
    
    // Compute the isolations
    iso_max=ComputeIso(iso1_vec,iso2_vec,1);
    iso_max2=ComputeIso(iso1_vec,iso2_vec,2);
    std::vector<double> iso1_vec_ord=Ordina(iso1_vec);//sort from largest to smallest
    std::vector<double> iso2_vec_ord=Ordina(iso2_vec);//sort from largest to smallest
    iso_ave2=ComputeIso(iso1_vec_ord,iso2_vec_ord,3);
    iso_ave3=ComputeIso(iso1_vec_ord,iso2_vec_ord,4);
    iso_mup_1st=iso_mup_2nd=iso_mum_1st=iso_mum_2nd=-1;
    if (iso1_vec_ord.size()>0){
      iso_mup_1st=iso1_vec_ord[0];
      iso_mum_1st=iso2_vec_ord[0];
    }
    if (iso1_vec_ord.size()>1){
      iso_mup_2nd=iso1_vec_ord[1];
      iso_mum_2nd=iso2_vec_ord[1];
    }
    isoBranch_1->Fill();
    isoBranch_2->Fill();
    isoBranch_3->Fill();
    isoBranch_4->Fill();
    isoBranch_5->Fill();
    isoBranch_6->Fill();
    isoBranch_7->Fill();
    isoBranch_8->Fill();
    if (do_jpsiveto){
      jpsivetoBranch_mup->Fill();
      jpsivetoBranch_mum->Fill();
    }
  }//end jentry<nentries loop
  
  newfile->Write();
  delete ch_b2mumu;

  //
  // Take B2HH tree
  //
  TString dir_name_b2hh="B2HHTuple";
  TChain* ch_b2hh=new TChain(dir_name_b2hh+"/DecayTree");
  ch_b2hh->Add(inputfile_name);
  TTree* oldtree_b2hh=(TTree*) ch_b2hh;
  nentries=oldtree_b2hh->GetEntries();
  
  //Create B2HH dir in new file
  newfile->mkdir(dir_name_b2hh);
  newfile->cd(dir_name_b2hh);
  
  cout<<"Calling oldtree_b2hh->CloneTree"<<endl;
  TTree * clonetree_b2hh = oldtree_b2hh->CloneTree();
  cout<<"Chiamato oldtree_b2hh->CloneTree"<<endl;
  Init(oldtree_b2hh);
  cout<<"Init(oldtree_b2hh) done"<<endl;

  //
  // Create new branches to be added to the original ttree
  //
  isoBranch_1 = clonetree_b2hh->Branch("iso_max_"+var_name,&iso_max,"iso_max_"+var_name+"/D");
  isoBranch_2 = clonetree_b2hh->Branch("iso_max2_"+var_name,&iso_max2,"iso_max2_"+var_name+"/D");
  isoBranch_3 = clonetree_b2hh->Branch("iso_ave2_"+var_name,&iso_ave2,"iso_ave2_"+var_name+"/D");
  isoBranch_4 = clonetree_b2hh->Branch("iso_ave3_"+var_name,&iso_ave3,"iso_ave3_"+var_name+"/D");
  isoBranch_5 = clonetree_b2hh->Branch("iso_mup_1st_"+var_name,&iso_mup_1st,"iso_mup_1st_"+var_name+"/D");
  isoBranch_6 = clonetree_b2hh->Branch("iso_mup_2nd_"+var_name,&iso_mup_2nd,"iso_mup_2nd_"+var_name+"/D");
  isoBranch_7 = clonetree_b2hh->Branch("iso_mum_1st_"+var_name,&iso_mum_1st,"iso_mu,_1st_"+var_name+"/D");
  isoBranch_8 = clonetree_b2hh->Branch("iso_mum_2nd_"+var_name,&iso_mum_2nd,"iso_mum_2nd_"+var_name+"/D");
   if (do_jpsiveto){
    jpsivetoBranch_mup = clonetree_b2hh->Branch("muplus_jpsimass",&muplus_jpsimass,"muplus_jpsimass/D");
    jpsivetoBranch_mum = clonetree_b2hh->Branch("muminus_jpsimass",&muminus_jpsimass,"muminus_jpsimass/D");
  }

  //
  // Loop over oldtree_b2hh, compute new isolations, save new TBranches
  //
  fChain=oldtree_b2hh;
  if (fChain == 0) return;
  //Long64_t nentries = fChain->GetEntriesFast();
  nbytes = 0; 
  nb = 0;
  cout<<"nentries = "<<nentries<<endl;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if (!(jentry%1000)) cout<<"jentry = "<<jentry<<endl;
    
    _jentry=jentry;
    
    // Loop over long tracks and identify the two muons 
    int muid_vec[2]={-1,-1};
    getMuonTrackIndex(muid_vec);
    _mup_id=muid_vec[0];
    _mum_id=muid_vec[1];

    //iso1_vec is the vector containing the isoBDT, w.r.t. muplus, of all track in the event with the right trk_type. 
    //iso2_vec contains the isoBDT w.r.t. muminus
    vector<double> iso1_vec;
    vector<double> iso2_vec;

    int Ntracks=0;
    if (trk_type==1) Ntracks=VEL_num;
    if (trk_type==3) Ntracks=EVB_Nparts;
    if (trk_type==4) Ntracks=US_num;
    for (int i=0;i<Ntracks;i++){
      //In case of long tracks, skip the two muon candidates
      if (trk_type==3 && (i==_mup_id || i==_mum_id)) continue;
      //In case of long and US tracks, skip tracks without a defined NN<xxx> (<xxx>=mu,pi,k)
      if (trk_type==3 && (EVB_par_NNpi[i]<0 || EVB_par_NNk[i]<0 || (EVB_par_isMuon[i]==1 && EVB_par_NNmu[i]<0))) continue;
      if (trk_type==4 && (US_par_NNpi[i]<0 || US_par_NNk[i]<0 || (US_par_isMuon[i]==1 && US_par_NNmu[i]<0))) continue;
      //In case of VEL tracks, if cutoption="noback" skip tracks with VEL_par_back==1
      if (trk_type==1 && cut_option=="noback" && VEL_par_back[i]==1) continue;

      //Compute the value of all vars trk_<xxx>. Some of them are used by getVal(...)
      ComputeIsoBDTVars_new(trk_type,i);

      for (int j=0;j<(int)inputvars_vec.size();j++){
	var[j]=getVal(inputvars_vec[j],_mup_id);
      }
      double myiso1=reader->EvaluateMVA("BDT method");
      iso1_vec.push_back(myiso1);//store in iso1_vec the isoBDT wrt muplus
    
      for (int j=0;j<(int)inputvars_vec.size();j++){
	var[j]=getVal(inputvars_vec[j],_mum_id);
      }
      double myiso2=reader->EvaluateMVA("BDT method");
      iso2_vec.push_back(myiso2);//store in iso2_vec the isoBDT wrt muminus
      
    }//end i<Ntracks

    //
    // compute the J/psi veto variables
    //
    muplus_jpsimass=0;
    muminus_jpsimass=0;
    if (do_jpsiveto){
      double m_mu=105.658;
      TLorentzVector p4_mup(muplus_PX,muplus_PY,muplus_PZ,muplus_PE);
      TLorentzVector p4_mum(muminus_PX,muminus_PY,muminus_PZ,muminus_PE);
      for (int i=0;i<EVB_Nparts;i++){
	if (i==_mup_id || i==_mum_id) continue;//skip the signal muons
	if(EVB_par_NNmu[i]<0.3) continue;//skip longtracks non consistent with being muons
	double e_trk=sqrt(EVB_par_p[i]*EVB_par_p[i]+m_mu*m_mu);//si assume che la traccia sia un vero mu
	TLorentzVector p4_trk(EVB_par_px[i],EVB_par_py[i],EVB_par_pz[i],e_trk);
	TLorentzVector p4_comb;
	if (EVB_par_chg[i]==1){
	  p4_comb=p4_trk+p4_mum;
	  double m_comb=p4_comb.Mag();
	  if (fabs(m_comb-3097)<fabs(muminus_jpsimass-3097)) muminus_jpsimass=m_comb;
	}
	if (EVB_par_chg[i]==-1){
	  p4_comb=p4_trk+p4_mup;
	  double m_comb=p4_comb.Mag();
	  if (fabs(m_comb-3097)<fabs(muplus_jpsimass-3097)) muplus_jpsimass=m_comb;
	}
      }//end i<EVB_Nparts
    }//end do_jpsiveto


    // Compute the isolations
    iso_max=ComputeIso(iso1_vec,iso2_vec,1);
    iso_max2=ComputeIso(iso1_vec,iso2_vec,2);
    std::vector<double> iso1_vec_ord=Ordina(iso1_vec);//sort from largest to smallest
    std::vector<double> iso2_vec_ord=Ordina(iso2_vec);//sort from largest to smallest
    iso_ave2=ComputeIso(iso1_vec_ord,iso2_vec_ord,3);
    iso_ave3=ComputeIso(iso1_vec_ord,iso2_vec_ord,4);
    iso_mup_1st=iso_mup_2nd=iso_mum_1st=iso_mum_2nd=-1;
    if (iso1_vec_ord.size()>0){
      iso_mup_1st=iso1_vec_ord[0];
      iso_mum_1st=iso2_vec_ord[0];
    }
    if (iso1_vec_ord.size()>1){
      iso_mup_2nd=iso1_vec_ord[1];
      iso_mum_2nd=iso2_vec_ord[1];
    }
    isoBranch_1->Fill();
    isoBranch_2->Fill();
    isoBranch_3->Fill();
    isoBranch_4->Fill();
    isoBranch_5->Fill();
    isoBranch_6->Fill();
    isoBranch_7->Fill();
    isoBranch_8->Fill();
    if (do_jpsiveto){
      jpsivetoBranch_mup->Fill();
      jpsivetoBranch_mum->Fill();
    }
  }//end jentry<nentries loop
 
  newfile->Write();
  delete ch_b2hh;
  
  //Copy the GetIntegratedLuminosity dir
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
  delete reader;
  delete newfile;
}//end Loop


vector<string> addIso::getBDTVars(TString weightfile_name,TString opt){
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

std::vector<std::string> & addIso::split(const std::string &s, char delim, std::vector<std::string> &elems) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

std::vector<std::string> addIso::split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}

//This version of getVal exploits the fact that trk_<xxx> have been called previously
//from the call of ComputeIsoBDTVars_new
double addIso::getVal(TString var_name,int i_mu){
  float ch_mu=EVB_par_chg[i_mu];
  if (var_name=="log(trk_ips)") return log(trk_ips);
  else if (var_name=="trk_ips") return trk_ips;
  else if (var_name=="trk_ip") return trk_ip;
  else if (var_name=="trk_bips") return trk_bips;
  else if (var_name=="trk_gho") return trk_gho;
  else if (var_name=="trk_chi") return trk_chi;
  else if (var_name=="trk_pt") return trk_pt;
  else if (var_name=="trk_ch") return trk_ch*ch_mu;
  else if (var_name=="trk_phi") return trk_phi;
  else if (var_name=="trk_eta") return trk_eta;
  else if (var_name=="trk_r") return trk_r;
  else if (var_name=="trk_nnmu") return trk_nnmu;
  else if (var_name=="trk_nnpi") return trk_nnpi;
  else if (var_name=="trk_nnk") return trk_nnk;
  else if (var_name=="trk_dllmu") return trk_dllmu;
  else if (var_name=="trk_dllk") return trk_dllk;
  else if (var_name=="trk_ismuon") return trk_ismuon;
  else if (var_name=="trk_pvdis1"){ 
    if (ch_mu==1) return trk_pvdis1; 
    if (ch_mu==-1) return trk_pvdis2; 
  }
  else if (var_name=="trk_svdis1"){
    if (ch_mu==1) return trk_svdis1;
    if (ch_mu==-1) return trk_svdis2;
  }
  else if (var_name=="log(trk_doca1)"){
    if (ch_mu==1) return log(trk_doca1); 
    if (ch_mu==-1) return log(trk_doca2); 
  }
  else if (var_name=="trk_doca1"){
    if (ch_mu==1) return trk_doca1;
    if (ch_mu==-1) return trk_doca2;
  }
  else if (var_name=="trk_angle1"){
    if (ch_mu==1) return trk_angle1;
    if (ch_mu==-1) return trk_angle2;
  }
  else if (var_name=="trk_fc1"){
    if (ch_mu==1) return trk_fc1;
    if (ch_mu==-1) return trk_fc2;
  }
  else if (var_name=="trk_dphi1"){ 
    if (ch_mu==1) return trk_dphi1;
    if (ch_mu==-1) return trk_dphi2;
  }   
  else if (var_name=="trk_deta1"){
    if (ch_mu==1) return trk_deta1;
    if (ch_mu==-1) return trk_deta2;
  }
  else if (var_name=="abs(trk_deta1)"){
    if (ch_mu==1) return fabs(trk_deta1);
    if (ch_mu==-1) return fabs(trk_deta2);
  }
  else if (var_name=="trk_dr1"){
    if (ch_mu==1) return trk_dr1;
    if (ch_mu==-1) return trk_dr2;
  }
  else if (var_name=="trk_pvdis2"){ 
    if (ch_mu==1) return trk_pvdis2; 
    if (ch_mu==-1) return trk_pvdis1; 
  }
  else if (var_name=="trk_svdis2"){
    if (ch_mu==1) return trk_svdis2;
    if (ch_mu==-1) return trk_svdis1;
  }
  else if (var_name=="log(trk_doca2)"){
    if (ch_mu==1) return log(trk_doca2); 
    if (ch_mu==-1) return log(trk_doca1); 
  }
  else if (var_name=="trk_doca2"){
    if (ch_mu==1) return trk_doca2;
    if (ch_mu==-1) return trk_doca1;
  }
  else if (var_name=="trk_angle2"){
    if (ch_mu==1) return trk_angle2;
    if (ch_mu==-1) return trk_angle1;
  }
  else if (var_name=="trk_fc2"){
    if (ch_mu==1) return trk_fc2;
    if (ch_mu==-1) return trk_fc1;
  }
  else if (var_name=="trk_dphi2"){ 
    if (ch_mu==1) return trk_dphi2;
    if (ch_mu==-1) return trk_dphi1;
  }   
  else if (var_name=="trk_deta2"){
    if (ch_mu==1) return trk_deta2;
    if (ch_mu==-1) return trk_deta1;
  }
  else if (var_name=="abs(trk_deta2)"){
    if (ch_mu==1) return fabs(trk_deta2);
    if (ch_mu==-1) return fabs(trk_deta1);
  }
  else if (var_name=="trk_dr2"){
    if (ch_mu==1) return trk_dr2;
    if (ch_mu==-1) return trk_dr1;
  }
  else if (var_name=="trk_back") return trk_back;

  //else if (var_name=="") return;
  cout<<"ERROR. var_name = "<<var_name<<" Return -1"<<endl; return -1;
  
}//end getVal



//
// Store in input 2-dim array the EVB indices of muplus and muminus from B->muplus muminus
//
void addIso::getMuonTrackIndex(int* ind_vec){
  double diff_mup_min=1e2;
  double diff_mum_min=1e2;

  double diff_mup,diff_mum;

  for (int i=0;i<EVB_Nparts;i++){
    diff_mup=fabs(muplus_PT-EVB_par_pt[i]);
    diff_mum=fabs(muminus_PT-EVB_par_pt[i]);
    if (diff_mup<diff_mup_min && muplus_TRACK_GhostProb==EVB_par_gho[i]){ diff_mup_min=diff_mup; ind_vec[0]=i;}
    if (diff_mum<diff_mum_min && muminus_TRACK_GhostProb==EVB_par_gho[i]){ diff_mum_min=diff_mum; ind_vec[1]=i;}
  }//end i<EVB_Nparts
  if (EVB_par_gho[ind_vec[0]]!=muplus_TRACK_GhostProb || EVB_par_gho[ind_vec[1]]!=muminus_TRACK_GhostProb){ cout<<"ATTENTION: getMuonTrackIndex: matching not found, ind_vec[0] = "<<ind_vec[0]<<" ind_vec[1] = "<<ind_vec[1]<<" jentry = "<<_jentry<<endl; 
    cout<<"EVB_par_gho[ind_vec[0]] = "<<EVB_par_gho[ind_vec[0]]<<" muplus_TRACK_GhostProb = "<<muplus_TRACK_GhostProb<<endl;
    cout<<"EVB_par_gho[ind_vec[1]] = "<<EVB_par_gho[ind_vec[1]]<<" muminus_TRACK_GhostProb = "<<muminus_TRACK_GhostProb<<endl;
  }

  return;

}//end getMuonTrackIndex


double addIso::ratio( double p1, double p2){
  return fabs(p1 -p2)*(1./fabs(p1+p2));
}

double addIso::GetTrackPhi(int i_trk){
  double px=EVB_par_px[i_trk];
  double py=EVB_par_py[i_trk];
  if (px==0 && py==0) return 0;
  double phi=atan(py/px);
  if (px>=0 && py>=0) return phi;
  else if(px<0 && py>=0) return phi+acos(-1);
  else if(px<0 && py<0) return phi-acos(-1);
  else return phi;

}//end GetTrackPhi

double addIso::GetTrackEta(int i_trk){
  double p=EVB_par_p[i_trk];
  double pz=EVB_par_pz[i_trk];

  return 0.5*log((p+pz)/(p-pz));
  
}//end GetTrackEta

double addIso::ComputeIso(std::vector<double> iso1_vec,std::vector<double> iso2_vec,int flag){
  //flag:
  //1: max of iso1+iso2 (computed on same track)
  //2: max of iso1 + max of iso2 (the 2 max usually correspond to different tracks)
  //3: mean[2 highest iso1] + meen[2 highest iso2]
  //4: mean[3 highest iso1] + meen[3 highest iso2]
  //5: mean[4 highest iso1] + meen[4 highest iso2]
  //6: fraction of iso1 and iso2 > -0.2
  //7: fraction of iso1 and iso2 > -0.4
  //8: fraction of iso1 and iso2 > -0.6
  if (iso1_vec.size()!=iso2_vec.size()) cout<<"ComputeIso: ATTENTION! iso1_vec.size() = "<<iso1_vec.size()<<" iso2_vec.size() = "<<iso2_vec.size()<<endl;
  if (flag==1){
    double iso_max=-2;
    for (int i=0;i<(int)iso1_vec.size();i++){
      double iso_temp=iso1_vec[i]+iso2_vec[i];
      if (iso_temp>=iso_max) iso_max=iso_temp;
    }//end i<iso1_vec.size()
    return iso_max;
  }//end flag==1
  if (flag==2){
    double iso_max1=-1;
    double iso_max2=-1;
    for (int i=0;i<(int)iso1_vec.size();i++){
      double iso_temp1=iso1_vec[i];
      double iso_temp2=iso2_vec[i];
      if (iso_temp1>=iso_max1) iso_max1=iso_temp1;
      if (iso_temp2>=iso_max2) iso_max2=iso_temp2;
    }//end i<iso1_vec.size()
    return iso_max1+iso_max2;
  }//end flag==2
  if (flag==3){
    double len=TMath::Min(2,(int)iso1_vec.size());
    if (len==0) return -2;
    double iso1=0;
    double iso2=0;
    for (int i=0;i<len;i++){
      iso1+=iso1_vec[i];
      iso2+=iso2_vec[i];
    }
    iso1/=len;
    iso2/=len;
    return iso1+iso2;
  }//end flag==3
  if (flag==4){
    double len=TMath::Min(3,(int)iso1_vec.size());
    if (len==0) return -2;
    double iso1=0;
    double iso2=0;
    for (int i=0;i<len;i++){
      iso1+=iso1_vec[i];
      iso2+=iso2_vec[i];
    }
    iso1/=len;
    iso2/=len;
    return iso1+iso2;
  }//end flag==4
  if (flag==5){
    double len=TMath::Min(4,(int)iso1_vec.size());
    if (len==0) return -2;
    double iso1=0;
    double iso2=0;
    for (int i=0;i<len;i++){
      iso1+=iso1_vec[i];
      iso2+=iso2_vec[i];
    }
    iso1/=len;
    iso2/=len;
    return iso1+iso2;
  }//end flag==5
  if (flag==6){
    double n=0;
    for (int i=0;i<(int)iso1_vec.size();i++){
      if (iso1_vec[i]>0.1) n++;
      if (iso2_vec[i]>0.1) n++;
    }
    if ((int)iso1_vec.size()>0) return n/(2*(int)iso1_vec.size());
    else return 0;
  }//end flag==6
  if (flag==7){
    double n=0;
    for (int i=0;i<(int)iso1_vec.size();i++){
      if (iso1_vec[i]>0.0) n++;
      if (iso2_vec[i]>0.0) n++;
    }
    if ((int)iso1_vec.size()>0) return n/(2*(int)iso1_vec.size());
    else return 0;
  }//end flag==7
  if (flag==8){
    double n=0;
    for (int i=0;i<(int)iso1_vec.size();i++){
      if (iso1_vec[i]>-0.1) n++;
      if (iso2_vec[i]>-0.1) n++;
    }
    if ((int)iso1_vec.size()>0) return n/(2*(int)iso1_vec.size());
    else return 0;
  }//end flag==8
  
  return 0;

}//end ComputeIso

//Sort
std::vector<double> addIso::Ordina(std::vector<double> iso_vec){
  int size=(int)iso_vec.size();
  int j;
  do{
    j = 0;
    for (int i=0;i<(size-1);i++){
      if (iso_vec[i+1]>iso_vec[i]){
        j = 1;
	double temp=iso_vec[i];
	iso_vec[i]=iso_vec[i+1];
	iso_vec[i+1]=temp;
      }
    }//end i<mat_dim
  } while (j == 1);
  
  return iso_vec;

}//end Ordina

void addIso::get_TrkIPSwrtBVtx(int trk_id,TVector3& vtx_pos,TMatrixD& vtx_Cov,double& chi2,int trk_type){
  if (_v) cout<<"Entro in get_TrkIPSwrtBVtx. trk_id = "<<trk_id<<" trk_type = "<<trk_type<<endl;
  TVector3 x0_trk;
  if (trk_type==3) x0_trk.SetXYZ(EVB_par_pos_x[trk_id],EVB_par_pos_y[trk_id],EVB_par_pos_z[trk_id]); 
  if (trk_type==4) x0_trk.SetXYZ(US_par_pos_x[trk_id],US_par_pos_y[trk_id],US_par_pos_z[trk_id]);
  if (trk_type==1) x0_trk.SetXYZ(VEL_par_pos_x[trk_id],VEL_par_pos_y[trk_id],VEL_par_pos_z[trk_id]);

  double x_bv_arr[3]={B_ENDVERTEX_X,B_ENDVERTEX_Y,B_ENDVERTEX_Z};
  TVectorD x_bv(3,x_bv_arr);
  TMatrixDSym covM_bv(3);
  covM_bv[0][0]=B_cov00;
  covM_bv[0][1]=B_cov01;
  covM_bv[0][2]=B_cov02;
  covM_bv[1][0]=covM_bv[0][1];
  covM_bv[1][1]=B_cov11;
  covM_bv[1][2]=B_cov12;
  covM_bv[2][0]=covM_bv[0][2];
  covM_bv[2][1]=covM_bv[1][2];
  covM_bv[2][2]=B_cov22;

  TMatrixDSym covMinv_bv(covM_bv);
  covMinv_bv.Invert();

  if (_v) cout<<"Ho invertito covMinv_bv"<<endl;
  //Nota: da ora in poi chiamiamo con p_i={px_i/pz_i,py_i/pz_i} i vettori 2dim con le slopes della traccia. Infatti sono questi i parametri
  //      che entrano nei conti seguenti

  //definisco i p_i contenenti le slopes e i parametri misurati qm_i={xm_i,ym_i,pxm_i/pzm_i,pym_i/pzm_i} 
  TVectorD p_trk(2);
  TVectorD qm_trk(4);
  if (trk_type==3){
    p_trk[0]=EVB_par_px[trk_id]/EVB_par_pz[trk_id];
    p_trk[1]=EVB_par_py[trk_id]/EVB_par_pz[trk_id];
    qm_trk[0]=EVB_par_pos_x[trk_id];
    qm_trk[1]=EVB_par_pos_y[trk_id];
    qm_trk[2]=p_trk[0];
    qm_trk[3]=p_trk[1];
  }
  if (trk_type==4){
    p_trk[0]=US_par_px[trk_id]/US_par_pz[trk_id];
    p_trk[1]=US_par_py[trk_id]/US_par_pz[trk_id];
    qm_trk[0]=US_par_pos_x[trk_id];
    qm_trk[1]=US_par_pos_y[trk_id];
    qm_trk[2]=p_trk[0];
    qm_trk[3]=p_trk[1];
  }
  if (trk_type==1){
    p_trk[0]=VEL_par_px[trk_id]/VEL_par_pz[trk_id];
    p_trk[1]=VEL_par_py[trk_id]/VEL_par_pz[trk_id];
    qm_trk[0]=VEL_par_pos_x[trk_id];
    qm_trk[1]=VEL_par_pos_y[trk_id];
    qm_trk[2]=p_trk[0];
    qm_trk[3]=p_trk[1];
  }
  for (int ii=0;ii<4;ii++) if (_v) cout<<"qm_trk["<<ii<<"] = "<<qm_trk[ii]<<endl;
  //definisco v0 come coincidente con il PV
  TVector3 v0(x_bv[0],x_bv[1],x_bv[2]);
  TVectorD x_v0(x_bv);//da cambiare nel caso non si definisca V0=posizione del PV; usato solo in calcolo chi2 sotto

  //definisco F(v0,p0_i) come F(v,p_i) calcolato in v=v0, p_i=pm_i (cioe' le slopes misurate nel primo 'stato')
  double F_v0p0_trk_arr[4]={v0[0]+p_trk[0]*(x0_trk[2]-v0[2]),v0[1]+p_trk[1]*(x0_trk[2]-v0[2]),p_trk[0],p_trk[1]};
  TVectorD F_v0p0_trk(4,F_v0p0_trk_arr);
  //definisce le variazioni dqm
  TVectorD dqm_trk=qm_trk-F_v0p0_trk;
  //definisco le matrici dF/dv=D per ogni traccia. dF/dv e' definita in (v0,p0_i)
  TMatrixD D_trk=get_dFdv(p_trk);
  //definisco le matrici dF/dp=E per ogni traccia. dF/dp e' definita in (v0,p0_i)
  TMatrixD E_trk=get_dFdp(v0,x0_trk);
  //calcolo la matrice di covarianza del vettore dei parametri qm
  //NB: nella ntupla c'e' la mat. cov. di x-p o di slopes, ma non di x-slopes.
  TMatrixDSym W_trk=get_trkCov(trk_id,trk_type);
  if (_v) cout<<"Sto per invertire W_trk"<<endl;
  W_trk.Invert();
  if (_v) cout<<"invertito W_trk"<<endl;

  //
  // Now we have all the ingredients to apply Billoir
  //
  TMatrixD D_trk_t(D_trk); D_trk_t.T();

  TMatrixD A=D_trk_t*W_trk*D_trk+covMinv_bv;

  TMatrixD B_trk=D_trk_t*W_trk*E_trk;
  TMatrixD B_trk_t(B_trk); B_trk_t.T();
  TMatrixD E_trk_t(E_trk); E_trk_t.T();
  TMatrixD C_trk=E_trk_t*W_trk*E_trk;

  TVectorD T=D_trk_t*W_trk*dqm_trk+covMinv_bv*(x_bv-x_v0);
  TVectorD U_trk=E_trk_t*W_trk*dqm_trk;

  TMatrixD Cinv_trk(C_trk); Cinv_trk.Invert();

  TMatrixD Cov_V=A-B_trk*Cinv_trk*B_trk_t;//cov mat dell'intersezione tra la traccia e il vertice di input
  if (_v) cout<<"Sto per invertire Cov_V"<<endl;
  Cov_V.Invert();
  if (_v) cout<<"invertito Cov_V"<<endl;

  TVectorD vec=T-B_trk*Cinv_trk*U_trk;
  TVectorD dV=Cov_V*vec;
  vtx_pos.SetXYZ(v0[0]+dV[0],v0[1]+dV[1],v0[2]+dV[2]);
  vtx_Cov=Cov_V;

  TVectorD dp_trk=Cinv_trk*U_trk-Cinv_trk*B_trk_t*dV;

  TVectorD deltaq_trk=qm_trk-(F_v0p0_trk+D_trk*dV+E_trk*dp_trk);
  chi2=deltaq_trk*(W_trk*deltaq_trk)+dV*(covMinv_bv*dV);
  if (_v) cout<<"deltaq_trk*(W_trk*deltaq_trk) = "<<deltaq_trk*(W_trk*deltaq_trk)<<" dV*(covMinv_bv*dV) = "<<dV*(covMinv_bv*dV)<<endl;
  if (_v){
    for (int n=0;n<4;n++) cout<<"deltaq_trk["<<n<<"] = "<<deltaq_trk[n]<<endl;
    for (int m=0;m<4;m++) 
      for (int n=0;n<4;n++) cout<<"W_trk["<<m<<"]["<<n<<"] = "<<W_trk[m][n]<<endl;
  }
  return;
}//end get_TrkIPSwrtBVtx

TMatrixD addIso::get_dFdv(TVectorD p){
  TMatrixD out(4,3);
  for (int i=0;i<4;i++)
    for (int j=0;j<3;j++) out[i][j]=0;
  out[0][0]=1;
  out[1][1]=1;
  out[0][2]=-p[0];
  out[1][2]=-p[1];
  return out;
}//end get_dFdv

//return dF/dp (matrix 4x2)
TMatrixD addIso::get_dFdp(TVector3 v0,TVector3 x0){
  //x0 is the vector with the position of the first measurement layer
  TMatrixD out(4,2);
  out[0][0]=out[1][1]=x0[2]-v0[2];
  out[2][0]=out[3][1]=1;
  out[0][1]=out[1][0]=out[2][1]=out[3][0]=0;
  return out;
}//end get_dFdp


//Trasform the x-p cov matrix into x-slopes cov matrix
//NB: in case of  US and VEl tracks (trk_type=4,1) since only the x,y cov matrix is available, and not that of p, 
//    a dummy sigma(p_i)=0.1MeV (i.e. about zero) is assumed, and all correlations are set to zero
TMatrixDSym addIso::get_trkCov(int trk_id,int trk_type){
  TVectorD x(5);
  if (trk_type==3){
    x[0]=EVB_par_pos_x[trk_id];
    x[1]=EVB_par_pos_y[trk_id];
    x[2]=EVB_par_px[trk_id];
    x[3]=EVB_par_py[trk_id];
    x[4]=EVB_par_pz[trk_id];
  }
  if (trk_type==4){
    x[0]=US_par_pos_x[trk_id];
    x[1]=US_par_pos_y[trk_id];
    x[2]=US_par_px[trk_id];
    x[3]=US_par_py[trk_id];
    x[4]=US_par_pz[trk_id];
  }
  if (trk_type==1){
    x[0]=VEL_par_pos_x[trk_id];
    x[1]=VEL_par_pos_y[trk_id];
    x[2]=VEL_par_px[trk_id];
    x[3]=VEL_par_py[trk_id];
    x[4]=VEL_par_pz[trk_id];
  }
  
  TMatrixDSym covM(5);
  if (trk_type==3){
    covM[0][0]=EVB_par_xp_cov00[trk_id];
    covM[0][1]=EVB_par_xp_cov01[trk_id];
    covM[0][2]=EVB_par_xp_cov03[trk_id];
    covM[0][3]=EVB_par_xp_cov04[trk_id];
    covM[0][4]=EVB_par_xp_cov05[trk_id];
    covM[1][1]=EVB_par_xp_cov11[trk_id];
    covM[1][2]=EVB_par_xp_cov13[trk_id];
    covM[1][3]=EVB_par_xp_cov14[trk_id];
    covM[1][4]=EVB_par_xp_cov15[trk_id];
    covM[2][2]=EVB_par_xp_cov33[trk_id];
    covM[2][3]=EVB_par_xp_cov34[trk_id];
    covM[2][4]=EVB_par_xp_cov35[trk_id];
    covM[3][3]=EVB_par_xp_cov44[trk_id];
    covM[3][4]=EVB_par_xp_cov45[trk_id];
    covM[4][4]=EVB_par_xp_cov55[trk_id];
  }
  if (trk_type==4){
    covM[0][0]=US_par_xp_cov00[trk_id];
    covM[0][1]=US_par_xp_cov01[trk_id];
    covM[0][2]=US_par_xp_cov03[trk_id];
    covM[0][3]=US_par_xp_cov04[trk_id];
    covM[0][4]=US_par_xp_cov05[trk_id];
    covM[1][1]=US_par_xp_cov11[trk_id];
    covM[1][2]=US_par_xp_cov13[trk_id];
    covM[1][3]=US_par_xp_cov14[trk_id];
    covM[1][4]=US_par_xp_cov15[trk_id];
    covM[2][2]=US_par_xp_cov33[trk_id];
    covM[2][3]=US_par_xp_cov34[trk_id];
    covM[2][4]=US_par_xp_cov35[trk_id];
    covM[3][3]=US_par_xp_cov44[trk_id];
    covM[3][4]=US_par_xp_cov45[trk_id];
    covM[4][4]=US_par_xp_cov55[trk_id];

    /*
    for (int l=0;l<5;l++)
      for (int m=0;m<5;m++) covM[l][m]=0;
    covM[0][0]=US_par_xp_cov00[trk_id];
    covM[0][1]=US_par_xp_cov01[trk_id];
    covM[1][1]=US_par_xp_cov11[trk_id];
    double dummyval=1e-2;//(0.1MeV)^2; valore dummy per l'errore su px,py,pz, che non ho nell'ntupla per US e VEl tracks
    covM[2][2]=dummyval;
    covM[3][3]=dummyval;
    covM[4][4]=dummyval;
    */
  }
  if (trk_type==1){
    //      [18/1/2015]
    //      Note: I've verified that for VEL tracks the determinant of the cov matrix below is negative,
    //      indicating that there's a problem probably related to the fact that for VEL tracks the
    //      p direction is measured, but not the magnitude. Consequently, vtx_chi2 computed to evaluate trk_bips
    //      by get_TrkIPSwrtBVtx is sometimes negative and therfore trk_bips=NAN.
    //      For this reason covM_new is computed, using VEL_par_slope_cov<><>. See below just before the end of get_trkCov(...)
    covM[0][0]=VEL_par_xp_cov00[trk_id];
    covM[0][1]=VEL_par_xp_cov01[trk_id];
    covM[0][2]=VEL_par_xp_cov03[trk_id];
    covM[0][3]=VEL_par_xp_cov04[trk_id];
    covM[0][4]=VEL_par_xp_cov05[trk_id];
    covM[1][1]=VEL_par_xp_cov11[trk_id];
    covM[1][2]=VEL_par_xp_cov13[trk_id];
    covM[1][3]=VEL_par_xp_cov14[trk_id];
    covM[1][4]=VEL_par_xp_cov15[trk_id];
    covM[2][2]=VEL_par_xp_cov33[trk_id];
    covM[2][3]=VEL_par_xp_cov34[trk_id];
    covM[2][4]=VEL_par_xp_cov35[trk_id];
    covM[3][3]=VEL_par_xp_cov44[trk_id];
    covM[3][4]=VEL_par_xp_cov45[trk_id];
    covM[4][4]=VEL_par_xp_cov55[trk_id];
    /*
    for (int l=0;l<5;l++)
      for (int m=0;m<5;m++) covM[l][m]=0;
    covM[0][0]=VEL_par_xp_cov00[trk_id];
    covM[0][1]=VEL_par_xp_cov01[trk_id];
    covM[1][1]=VEL_par_xp_cov11[trk_id];
    double dummyval=1e-2;//(0.1MeV)^2; valore dummy per l'errore su px,py,pz, che non ho nell'ntupla per US e VEl tracks
    covM[2][2]=dummyval;
    covM[3][3]=dummyval;
    */
  }


  //Symmetrize the matrix
  for (int i=0;i<5;i++)
    for (int j=0;j<i;j++) covM[i][j]=covM[j][i];

  //Define the Jacobian of the {x,y,px,py,pz} -> {x,y,px/pz,py/pz} transformation:
  //{x,y,px/pz,py/pz}={f_i} {x,y,px,py,pz}={x_j}
  TMatrixD J(4,5);//J_ij = df_i/d x_j
  for (int i=0;i<4;i++)
    for (int j=0;j<5;j++) J[i][j]=0;
  J[0][0]=J[1][1]=1;
  J[2][2]=1/x[4];
  J[2][4]=-x[2]/(x[4]*x[4]);
  J[3][3]=1/x[4];
  J[3][4]=-x[3]/(x[4]*x[4]);

  //cov(x,y,slx,sly) = J*covM*J^T
  //TMatrixD covM_temp=(J*covM)*J.T();
  TMatrixD covM_temp=J*covM;
  TMatrixD covM_temp2=covM_temp*J.T();
  TMatrixDSym covM_new(4);
  for (int i=0;i<4;i++)
    for (int j=0;j<4;j++) covM_new[i][j]=covM_temp2[i][j];
  
  //[18/1/2015]: Nel caso di VEL tracks costruisci la matrice 4x4 usando VEL_par_slope_cov<><>
  //perche' la matrice VEL_par_xp_cov<><> NON ha determinante positivo
  //(probabilmente perche' solo la direzione e non il modulo di p e' misurata)
  //NB: si _assume_ zero correlazione tra x,y e px/pz,py/pz, perche' i corrispondenti
  //elementi di matrice non sono disponibili

  //[18/1/2015]: In case of VEL tracks build the 4x4 matrix using VEL_par_slope_cov<><>
  //because the VEL_par_xp_cov<><> matrix has NOT positive determinant
  //(probably because only the direction of p, and not the magnitude, is measured)
  //NB: 0 correlation between x,y and px/pz,py/pz is assumed, because those matrix elements are not available
  /*
  for (int i=0;i<4;i++)
    for (int j=0;j<4;j++) cout<<"covM_new["<<i<<"]["<<j<<"] = "<<covM_new[i][j]<<endl;
  */
  if (trk_type==1){
    for (int l=0;l<4;l++)
      for (int m=0;m<4;m++) covM_new[l][m]=0;
    covM_new[0][0]=VEL_par_xp_cov00[trk_id];
    covM_new[0][1]=VEL_par_xp_cov01[trk_id];
    covM_new[1][1]=VEL_par_xp_cov11[trk_id];
    covM_new[1][0]=covM_new[0][1];
    covM_new[2][2]=VEL_par_slope_covxx[trk_id];
    covM_new[2][3]=VEL_par_slope_covxy[trk_id];
    covM_new[3][3]=VEL_par_slope_covyy[trk_id];
    covM_new[3][2]=covM_new[2][3];
  }
  /*
  if (trk_type==3){
    for (int l=0;l<4;l++)
      for (int m=0;m<4;m++) covM_new[l][m]=0;
    covM_new[0][0]=EVB_par_xp_cov00[trk_id];
    covM_new[0][1]=EVB_par_xp_cov01[trk_id];
    covM_new[1][1]=EVB_par_xp_cov11[trk_id];
    covM_new[1][0]=covM_new[0][1];
    covM_new[2][2]=EVB_par_slope_covxx[trk_id];
    covM_new[2][3]=EVB_par_slope_covxy[trk_id];
    covM_new[3][3]=EVB_par_slope_covyy[trk_id];
    covM_new[3][2]=covM_new[2][3];
  }
  */

  return covM_new;
}//end get_trkCov

void addIso::get_TRKminIP(int trk_id, int& pv_ip_id, int& pv_ips_id, double& mytrk_ip, double& mytrk_ips,int trk_type){
  if (_v) cout<<"Entro in get_TRKminIP. trk_id = "<<trk_id<<" trk_type = "<<trk_type<<endl;
  mytrk_ips=1e6;
  mytrk_ip=1e6;
  //x,y and slopes track parameters
  TVector3 x_trk;
  TVector3 p_trk;
  if (trk_type==3){
    p_trk.SetXYZ(EVB_par_px[trk_id],EVB_par_py[trk_id],EVB_par_pz[trk_id]);
    x_trk.SetXYZ(EVB_par_pos_x[trk_id],EVB_par_pos_y[trk_id],EVB_par_pos_z[trk_id]);
  } 
  if (trk_type==4){
    p_trk.SetXYZ(US_par_px[trk_id],US_par_py[trk_id],US_par_pz[trk_id]);
    x_trk.SetXYZ(US_par_pos_x[trk_id],US_par_pos_y[trk_id],US_par_pos_z[trk_id]);
  }
  if (trk_type==1){
    p_trk.SetXYZ(VEL_par_px[trk_id],VEL_par_py[trk_id],VEL_par_pz[trk_id]);
    x_trk.SetXYZ(VEL_par_pos_x[trk_id],VEL_par_pos_y[trk_id],VEL_par_pos_z[trk_id]);
  }

  //loop over the PVs of the event
  for (int i_pv=0;i_pv<PV_num;i_pv++){
    TVector3 x_pv(PV_x[i_pv],PV_y[i_pv],PV_z[i_pv]);
    TVector3 v=p_trk.Unit();
    TVector3 doca_vec=v.Cross(x_pv-x_trk);
    double ip=doca_vec.Mag();

    //compute IPCHI2 wrt PV
    TVector3 vtx_pos;
    TMatrixD vtx_Cov(3,3);
    double vtx_chi2=-1;
    if (_v) cout<<"Entering get_TrkIPSwrtPV"<<endl;
    get_TrkIPSwrtPV(trk_id,i_pv,vtx_pos,vtx_Cov,vtx_chi2,trk_type);
    if (_v) cout<<"Out of get_TrkIPSwrtPV"<<endl;
    double ips=sqrt(vtx_chi2);

    if (ip<mytrk_ip){
      pv_ip_id=i_pv;
      mytrk_ip=ip;
    }
    if (ips<mytrk_ips){
      pv_ips_id=i_pv;
      mytrk_ips=ips;
    }

  }//end i<PV_num


  return;
}//end get_TRKminIP

void addIso::get_TrkIPSwrtPV(int trk_id,int pv_id,TVector3& vtx_pos,TMatrixD& vtx_Cov,double& chi2,int trk_type){
  if (_v) cout<<"Entering get_TrkIPSwrtPV. trk_id = "<<trk_id<<" pv_id = "<<pv_id<<endl;
  TVector3 x0_trk;
  if (trk_type==3) x0_trk.SetXYZ(EVB_par_pos_x[trk_id],EVB_par_pos_y[trk_id],EVB_par_pos_z[trk_id]); 
  if (trk_type==4) x0_trk.SetXYZ(US_par_pos_x[trk_id],US_par_pos_y[trk_id],US_par_pos_z[trk_id]);
  if (trk_type==1) x0_trk.SetXYZ(VEL_par_pos_x[trk_id],VEL_par_pos_y[trk_id],VEL_par_pos_z[trk_id]);

  double x_pv_arr[3]={PV_x[pv_id],PV_y[pv_id],PV_z[pv_id]};
  TVectorD x_pv(3,x_pv_arr);
  TMatrixDSym covM_pv=get_PVCov(pv_id);
  TMatrixDSym covMinv_pv(covM_pv);
  covMinv_pv.Invert();
  if (_v) cout<<"Ho invertito covMinv_pv"<<endl;

  TVectorD p_trk(2);
  TVectorD qm_trk(4);
  if (trk_type==3){
    p_trk[0]=EVB_par_px[trk_id]/EVB_par_pz[trk_id];
    p_trk[1]=EVB_par_py[trk_id]/EVB_par_pz[trk_id];
    qm_trk[0]=EVB_par_pos_x[trk_id];
    qm_trk[1]=EVB_par_pos_y[trk_id];
    qm_trk[2]=p_trk[0];
    qm_trk[3]=p_trk[1];
  }
  if (trk_type==4){
    p_trk[0]=US_par_px[trk_id]/US_par_pz[trk_id];
    p_trk[1]=US_par_py[trk_id]/US_par_pz[trk_id];
    qm_trk[0]=US_par_pos_x[trk_id];
    qm_trk[1]=US_par_pos_y[trk_id];
    qm_trk[2]=p_trk[0];
    qm_trk[3]=p_trk[1];
  }
  if (trk_type==1){
    p_trk[0]=VEL_par_px[trk_id]/VEL_par_pz[trk_id];
    p_trk[1]=VEL_par_py[trk_id]/VEL_par_pz[trk_id];
    qm_trk[0]=VEL_par_pos_x[trk_id];
    qm_trk[1]=VEL_par_pos_y[trk_id];
    qm_trk[2]=p_trk[0];
    qm_trk[3]=p_trk[1];
  }
  for (int ii=0;ii<4;ii++) if (_v) cout<<"qm_trk["<<ii<<"] = "<<qm_trk[ii]<<endl;
  TVector3 v0(x_pv[0],x_pv[1],x_pv[2]);
  TVectorD x_v0(x_pv);//da cambiare nel caso non si definisca V0=posizione del PV; usato solo in calcolo chi2 sotto

  //definisco F(v0,p0_i) come F(v,p_i) calcolato in v=v0, p_i=pm_i (cioe' le slopes misurate nel primo 'stato')
  double F_v0p0_trk_arr[4]={v0[0]+p_trk[0]*(x0_trk[2]-v0[2]),v0[1]+p_trk[1]*(x0_trk[2]-v0[2]),p_trk[0],p_trk[1]};
  TVectorD F_v0p0_trk(4,F_v0p0_trk_arr);
  //definisce le variazioni dqm
  TVectorD dqm_trk=qm_trk-F_v0p0_trk;
  //definisco le matrici dF/dv=D per ogni traccia. dF/dv e' definita in (v0,p0_i)
  TMatrixD D_trk=get_dFdv(p_trk);
  //definisco le matrici dF/dp=E per ogni traccia. dF/dp e' definita in (v0,p0_i)
  TMatrixD E_trk=get_dFdp(v0,x0_trk);
  //calcolo la matrice di covarianza del vettore dei parametri qm
  //NB: nella ntupla c'e' la mat. cov. di x-p o di slopes, ma non di x-slopes.
  //TMatrixDSym W_trk=get_trkCov(trk_id,2);
  TMatrixDSym W_trk=get_trkCov(trk_id,trk_type);
  if (_v) cout<<"I'm going to invert W_trk"<<endl;
  W_trk.Invert();
  if (_v) cout<<"W_trk was inverted"<<endl;

  //
  // Now we have all ingredients to apply Billoir
  //

  TMatrixD D_trk_t(D_trk); D_trk_t.T();

  TMatrixD A=D_trk_t*W_trk*D_trk+covMinv_pv;

  TMatrixD B_trk=D_trk_t*W_trk*E_trk;
  TMatrixD B_trk_t(B_trk); B_trk_t.T();
  TMatrixD E_trk_t(E_trk); E_trk_t.T();
  TMatrixD C_trk=E_trk_t*W_trk*E_trk;

  TVectorD T=D_trk_t*W_trk*dqm_trk+covMinv_pv*(x_pv-x_v0);
  TVectorD U_trk=E_trk_t*W_trk*dqm_trk;

  TMatrixD Cinv_trk(C_trk); Cinv_trk.Invert();

  TMatrixD Cov_V=A-B_trk*Cinv_trk*B_trk_t;
  if (_v) cout<<"I'm going to invert Cov_V"<<endl;
  Cov_V.Invert();
  if (_v) cout<<"Cov_V was inverted"<<endl;

  TVectorD vec=T-B_trk*Cinv_trk*U_trk;
  TVectorD dV=Cov_V*vec;
  vtx_pos.SetXYZ(v0[0]+dV[0],v0[1]+dV[1],v0[2]+dV[2]);
  vtx_Cov=Cov_V;

  TVectorD dp_trk=Cinv_trk*U_trk-Cinv_trk*B_trk_t*dV;

  TVectorD deltaq_trk=qm_trk-(F_v0p0_trk+D_trk*dV+E_trk*dp_trk);
 chi2=deltaq_trk*(W_trk*deltaq_trk)+dV*(covMinv_pv*dV);

  return;
}//end get_TrkIPSwrtPV

TMatrixDSym addIso::get_PVCov(int pv_id){
  TMatrixDSym covM(3);
  covM[0][0]=PV_covxx[pv_id];
  covM[0][1]=PV_covxy[pv_id];
  covM[0][2]=PV_covxz[pv_id];
  covM[1][1]=PV_covyy[pv_id];
  covM[1][2]=PV_covyz[pv_id];
  covM[2][2]=PV_covzz[pv_id];
  covM[1][0]=covM[0][1];
  covM[2][0]=covM[0][2];
  covM[2][1]=covM[1][2];

  return covM;
}//end get_PVCov


// The vars trk_<xxx> with index 1 refer to muplus, those with index 2 refer to muminus.
// It is getVal(...) which decides, depending on whether the index i_mu corresponds to muplus or muminus, if the returned output 
// are the variables with index 1 or 2.
// Example: getVal(...) is called with var_name="trk_pvdis1" and i_mu=_i_mup, then getVal(...) returns 
// trk_pvdis1. If instead i_mu=_i_mum then getVal(...) returns trk_pvdis2 (because trk_pvdis2 is defined,
// in ComputeIsoBDTVars_new(...), as the trk_pvdis wrt muminus)
void addIso::ComputeIsoBDTVars_new(int trk_type,int i_trk){
  int mu1_id=_mup_id;
  int mu2_id=_mum_id;
  TVector3 p_mu1(EVB_par_px[_mup_id],EVB_par_py[_mup_id],EVB_par_pz[_mup_id]);
  TVector3 p_mu2(EVB_par_px[_mum_id],EVB_par_py[_mum_id],EVB_par_pz[_mum_id]);
  TVector3 p_trk;
  if (trk_type==3){
    trk_gho=EVB_par_gho[i_trk];
    trk_chi=EVB_par_chi[i_trk];
    trk_pt=EVB_par_pt[i_trk];
    trk_ch=EVB_par_chg[i_trk];
    trk_typ=(int)EVB_par_typ[i_trk];
    trk_clo=EVB_par_clo[i_trk];
    trk_pvind=EVB_par_PVind[i_trk];
    trk_nnmu=(EVB_par_NNmu[i_trk]>0?EVB_par_NNmu[i_trk]:-0.1);//when it is <0 (-10) set -0.1
    trk_nnpi=EVB_par_NNpi[i_trk];
    trk_nnk=EVB_par_NNk[i_trk];
    trk_ismuon=EVB_par_isMuon[i_trk];
    trk_dllmu=EVB_par_DLLmu[i_trk];
    trk_dllk=EVB_par_DLLk[i_trk];
    p_trk.SetXYZ(EVB_par_px[i_trk],EVB_par_py[i_trk],EVB_par_pz[i_trk]);
  }//end trk_type==3
  if (trk_type==4){
    trk_gho=US_par_gho[i_trk];
    trk_chi=US_par_chi[i_trk];
    trk_pt=US_par_pt[i_trk];
    trk_ch=US_par_chg[i_trk];
    trk_typ=(int)US_par_typ[i_trk];
    trk_clo=US_par_clo[i_trk];
    trk_pvind=US_par_PVind[i_trk];
    trk_nnmu=(US_par_NNmu[i_trk]>0?US_par_NNmu[i_trk]:-0.1);//when it is <0 (-10) set -0.1
    trk_nnpi=US_par_NNpi[i_trk];
    trk_nnk=US_par_NNk[i_trk];
    trk_ismuon=US_par_isMuon[i_trk];
    trk_dllmu=US_par_DLLmu[i_trk];
    trk_dllk=US_par_DLLk[i_trk];
    p_trk.SetXYZ(US_par_px[i_trk],US_par_py[i_trk],US_par_pz[i_trk]);
  }//end trk_type==4
  if (trk_type==1){
    trk_gho=VEL_par_gho[i_trk];
    trk_chi=VEL_par_chi[i_trk];
    trk_pt=VEL_par_pt[i_trk];
    trk_ch=VEL_par_chg[i_trk];
    trk_typ=(int)VEL_par_typ[i_trk];
    trk_clo=VEL_par_clo[i_trk];
    trk_pvind=VEL_par_PVind[i_trk];
    trk_nnmu=-1;
    trk_nnpi=-1;
    trk_nnk=-1;
    trk_ismuon=-1;
    trk_dllmu=-1;
    trk_dllk=-1;
    p_trk.SetXYZ(VEL_par_px[i_trk],VEL_par_py[i_trk],VEL_par_pz[i_trk]);
  }//end trk_type==1
  //get phi and eta
  trk_phi=p_trk.Phi();
  trk_eta=p_trk.Eta();
  trk_r=sqrt(trk_phi*trk_phi+trk_eta*trk_eta);
  //get angle between track and mu1/mu2
  trk_angle1=p_trk.Angle(p_mu1);
  trk_angle2=p_trk.Angle(p_mu2);
  //get doca between track and mu1/mu2
  trk_doca1=get_Doca(i_trk,mu1_id,trk_typ);
  trk_doca2=get_Doca(i_trk,mu2_id,trk_typ);
  //get fc, pvdis and svdis between track and mu1/mu2
  get_fc_pvdis_svdis(i_trk,mu1_id,trk_typ,trk_fc1,trk_pvdis1,trk_svdis1);
  get_fc_pvdis_svdis(i_trk,mu2_id,trk_typ,trk_fc2,trk_pvdis2,trk_svdis2);

  //get dphi between track and mu1/mu2
  trk_dphi1=fabs(trk_phi-p_mu1.Phi());
  trk_dphi2=fabs(trk_phi-p_mu2.Phi());
  //get deta between track and mu1/mu2
  trk_deta1=trk_eta-p_mu1.Eta();
  trk_deta2=trk_eta-p_mu2.Eta();
  //get deltaR between track and mu1/mu2
  trk_dr1=p_trk.DeltaR(p_mu1);
  trk_dr2=p_trk.DeltaR(p_mu2);
 
  //get track ips wrt B vtx
  TVector3 vtx_pos; TMatrixD vtx_Cov(3,3); double vtx_chi2;
  get_TrkIPSwrtBVtx(i_trk,vtx_pos,vtx_Cov,vtx_chi2,trk_typ);
  if (vtx_chi2<0) cout<<"vtx_chi2 = "<<vtx_chi2<<" trk_typ = "<<trk_typ<<endl;
  trk_bips=sqrt(vtx_chi2);
  //get track ip and ips wrt PV
  int trk_minip_pvid,trk_minips_pvid; 
  get_TRKminIP(i_trk,trk_minip_pvid,trk_minips_pvid,trk_ip,trk_ips,trk_typ);
  //get track back info
  if (trk_typ==1) trk_back=(double)VEL_par_back[i_trk];
  else trk_back=0;
  //get muons info
  mu1_gho=EVB_par_gho[mu1_id];
  mu2_gho=EVB_par_gho[mu2_id];
  mu1_phi=p_mu1.Phi();
  mu2_phi=p_mu2.Phi();
  mu1_ch=(int)EVB_par_chg[mu1_id];
  mu2_ch=(int)EVB_par_chg[mu2_id];

  //if the track is long, for some quantities take the values computed by DaVinci (to be consistent with the past)
  if (trk_typ==3){
    trk_ips=IsoST_trk_ips[i_trk];
    if (mu1_id==_mup_id){
      trk_fc1=IsoST_fim_fc[i_trk];
      trk_svdis1=IsoST_fim_svdis[i_trk];
      trk_pvdis1=IsoST_fim_pvdis[i_trk];
      trk_fc2=IsoST_sem_fc[i_trk];
      trk_svdis2=IsoST_sem_svdis[i_trk];
      trk_pvdis2=IsoST_sem_pvdis[i_trk];
    }
    else{
      trk_fc1=IsoST_sem_fc[i_trk];
      trk_svdis1=IsoST_sem_svdis[i_trk];
      trk_pvdis1=IsoST_sem_pvdis[i_trk];
      trk_fc2=IsoST_fim_fc[i_trk];
      trk_svdis2=IsoST_fim_svdis[i_trk];
      trk_pvdis2=IsoST_fim_pvdis[i_trk];
    }
  }//end trk_typ==3

  return; 
}//end ComputeIsoBDTVars_new

void addIso::ComputeIsoBDTVars(int i_trk,int trk_type){
  if (trk_type==1){
    //get track ips wrt B vtx
    TVector3 vtx_pos; TMatrixD vtx_Cov(3,3); double vtx_chi2;
    get_TrkIPSwrtBVtx(i_trk,vtx_pos,vtx_Cov,vtx_chi2,trk_type);
    trkus_bips=sqrt(vtx_chi2);
    //get min track ip and ips wrt PV
    int trk_minip_pvid,trk_minips_pvid;
    get_TRKminIP(i_trk,trk_minip_pvid,trk_minips_pvid,trkus_ip,trkus_ips,trk_type);
    //get track ghostprob and chi2
    trkus_gho=US_par_gho[i_trk];
    trkus_chi=US_par_chi[i_trk];
    //get angle between track and mup/mum
    TVector3 p_us(US_par_px[i_trk],US_par_py[i_trk],US_par_pz[i_trk]);
    TVector3 p_mup(EVB_par_px[_mup_id],EVB_par_py[_mup_id],EVB_par_pz[_mup_id]);
    TVector3 p_mum(EVB_par_px[_mum_id],EVB_par_py[_mum_id],EVB_par_pz[_mum_id]);
    trkus_angle1=p_us.Angle(p_mup);
    trkus_angle2=p_us.Angle(p_mum);
    //get doca between track and mup/mum
    trkus_doca1=get_Doca(i_trk,_mup_id,trk_type);
    trkus_doca2=get_Doca(i_trk,_mum_id,trk_type);
    //get fc, pvdis and svdis between track and mup/mum
    get_fc_pvdis_svdis(i_trk,_mup_id,trk_type,trkus_fc1,trkus_pvdis1,trkus_svdis1);
    get_fc_pvdis_svdis(i_trk,_mum_id,trk_type,trkus_fc2,trkus_pvdis2,trkus_svdis2);
    //get dphi between track and mup/mum
    double trkus_phi=p_us.Phi();
    trkus_dphi1=fabs(trkus_phi-muplus_phi);
    trkus_dphi2=fabs(trkus_phi-muminus_phi);
    //get deta between track and mup/mum
    double trkus_eta=p_us.Eta();
    trkus_deta1=trkus_eta-muplus_eta;
    trkus_deta2=trkus_eta-muminus_eta;
    //get pt,ch,PID of track
    trkus_pt=US_par_pt[i_trk];
    trkus_ch=US_par_chg[i_trk];
    trkus_nnmu=(US_par_NNmu[i_trk]>0?US_par_NNmu[i_trk]:-0.1);//quando e' <0 (-10) metti -0.1
    trkus_nnpi=US_par_NNpi[i_trk];
    trkus_nnk=US_par_NNk[i_trk];
    trkus_ismuon=US_par_isMuon[i_trk];
    //trkus_pvind=US_par_PVind[i_trk];
  }//end trk_type==1

  if (trk_type==2){
    //get track ips wrt B vtx
    TVector3 vtx_pos; TMatrixD vtx_Cov(3,3); double vtx_chi2;
    get_TrkIPSwrtBVtx(i_trk,vtx_pos,vtx_Cov,vtx_chi2,trk_type);
    trkvel_bips=sqrt(vtx_chi2);
    //get min track ip and ips wrt PV
    int trk_minip_pvid,trk_minips_pvid;
    get_TRKminIP(i_trk,trk_minip_pvid,trk_minips_pvid,trkvel_ip,trkvel_ips,trk_type);
    //get track ghostprob and chi2
    trkvel_gho=VEL_par_gho[i_trk];
    trkvel_chi=VEL_par_chi[i_trk];
    //get angle between track and mup/mum
    TVector3 p_us(VEL_par_px[i_trk],VEL_par_py[i_trk],VEL_par_pz[i_trk]);
    TVector3 p_mup(EVB_par_px[_mup_id],EVB_par_py[_mup_id],EVB_par_pz[_mup_id]);
    TVector3 p_mum(EVB_par_px[_mum_id],EVB_par_py[_mum_id],EVB_par_pz[_mum_id]);
    trkvel_angle1=p_us.Angle(p_mup);
    trkvel_angle2=p_us.Angle(p_mum);
    //get doca between track and mup/mum
    trkvel_doca1=get_Doca(i_trk,_mup_id,trk_type);
    trkvel_doca2=get_Doca(i_trk,_mum_id,trk_type);
    //get fc, pvdis and svdis between track and mup/mum
    get_fc_pvdis_svdis(i_trk,_mup_id,trk_type,trkvel_fc1,trkvel_pvdis1,trkvel_svdis1);
    get_fc_pvdis_svdis(i_trk,_mum_id,trk_type,trkvel_fc2,trkvel_pvdis2,trkvel_svdis2);
    //get dphi between track and mup/mum
    double trkvel_phi=p_us.Phi();
    trkvel_dphi1=fabs(trkvel_phi-muplus_phi);
    trkvel_dphi2=fabs(trkvel_phi-muminus_phi);
    //get deta between track and mup/mum
    double trkvel_eta=p_us.Eta();
    trkvel_deta1=trkvel_eta-muplus_eta;
    trkvel_deta2=trkvel_eta-muminus_eta;
    //trkvel_pvind=VEL_par_PVind[i_trk];
  }//end trk_type==2

  return;
}//end ComputeIsoBDTVars

double addIso::get_Doca(int trk_id, int mu_id,int trk_type){//trk_type: 3=EVB,4=US,1=VEL
  TVector3 p_mu(EVB_par_px[mu_id],EVB_par_py[mu_id],EVB_par_pz[mu_id]);
  TVector3 x_mu(EVB_par_pos_x[mu_id],EVB_par_pos_y[mu_id],EVB_par_pos_z[mu_id]);
  TVector3 p_trk;
  TVector3 x_trk;
  if (trk_type==3){
    p_trk.SetXYZ(EVB_par_px[trk_id],EVB_par_py[trk_id],EVB_par_pz[trk_id]);
    x_trk.SetXYZ(EVB_par_pos_x[trk_id],EVB_par_pos_y[trk_id],EVB_par_pos_z[trk_id]);
  } 
  if (trk_type==4){
    p_trk.SetXYZ(US_par_px[trk_id],US_par_py[trk_id],US_par_pz[trk_id]);
    x_trk.SetXYZ(US_par_pos_x[trk_id],US_par_pos_y[trk_id],US_par_pos_z[trk_id]);
  }
  if (trk_type==1){
    p_trk.SetXYZ(VEL_par_px[trk_id],VEL_par_py[trk_id],VEL_par_pz[trk_id]);
    x_trk.SetXYZ(VEL_par_pos_x[trk_id],VEL_par_pos_y[trk_id],VEL_par_pos_z[trk_id]);
  }
  
  TVector3 u1=p_mu.Unit();
  TVector3 u2=p_trk.Unit();
  double a = u1.Dot(u2);
  if (a==1){ cout<<"ATTENTION!! get_Doca(...): parallel track. Return -1"<<endl; return -1; }
  TVector3 r0 = x_mu-x_trk;
  double b = r0.Dot(u1);
  double c = r0.Dot(u2);
  double t1=(a*c-b)/(1-a*a);
  double t2=(-a*b+c)/(1-a*a);

  TVector3 d1=x_mu+u1*t1;//POCA 1
  TVector3 d2=x_trk+u2*t2;//POCA 2

  return (d2-d1).Mag();

}//end get_Doca

void addIso::get_fc_pvdis_svdis(int trk_id, int mu_id,int trk_type,double& fc,double& pvdis,double& svdis){
  TVector3 p_mu(EVB_par_px[mu_id],EVB_par_py[mu_id],EVB_par_pz[mu_id]);
  TVector3 x_mu(EVB_par_pos_x[mu_id],EVB_par_pos_y[mu_id],EVB_par_pos_z[mu_id]);
  TVector3 p_trk;
  TVector3 x_trk;
  if (trk_type==3){
    p_trk.SetXYZ(EVB_par_px[trk_id],EVB_par_py[trk_id],EVB_par_pz[trk_id]);
    x_trk.SetXYZ(EVB_par_pos_x[trk_id],EVB_par_pos_y[trk_id],EVB_par_pos_z[trk_id]);
  } 
  if (trk_type==4){
    p_trk.SetXYZ(US_par_px[trk_id],US_par_py[trk_id],US_par_pz[trk_id]);
    x_trk.SetXYZ(US_par_pos_x[trk_id],US_par_pos_y[trk_id],US_par_pos_z[trk_id]);
  }
  if (trk_type==1){
    p_trk.SetXYZ(VEL_par_px[trk_id],VEL_par_py[trk_id],VEL_par_pz[trk_id]);
    x_trk.SetXYZ(VEL_par_pos_x[trk_id],VEL_par_pos_y[trk_id],VEL_par_pos_z[trk_id]);
  }

  TVector3 u1=p_mu.Unit();
  TVector3 u2=p_trk.Unit();
  double a = u1.Dot(u2);
  if (a==1){ cout<<"ATTENTION!! get_fc_pvdis_svdis(...): parallel tracks."<<endl; return; }
  TVector3 r0 = x_mu-x_trk;
  double b = r0.Dot(u1);
  double c = r0.Dot(u2);
  double t1=(a*c-b)/(1-a*a);
  double t2=(-a*b+c)/(1-a*a);

  TVector3 d1=x_mu+u1*t1;//POCA 1
  TVector3 d2=x_trk+u2*t2;//POCA 2
  TVector3 vtx=0.5*(d1+d2);//NB: this approximate estimate of the vertex is used to be consistent with the def of the 'classic' track iso (used in 2013)

  int minip_pv_id,minips_pv_id;
  double ip,ips;
  get_BminIP(minip_pv_id,minips_pv_id,ip,ips);
  
  //int pv_id=getBPV();
  int pv_id=minips_pv_id;
  TVector3 pv_pos(PV_x[pv_id],PV_y[pv_id],PV_z[pv_id]);

  //compute fc
  TVector3 rv = vtx-pv_pos;
  double pt=p_mu.Pt()+p_trk.Pt();
  TVector3 ptot=p_mu+p_trk;
  double temp=rv.Angle(ptot);
  double  num=ptot.Mag()*sin(temp);
  double  den=(num+pt);
  fc=num/den;
  //compute psvid
  int sign_pv=vtx.z()-pv_pos.z()>=0?1:-1;
  pvdis = sign_pv*(vtx-pv_pos).Mag();
  //compute svdis
  TVector3 b_pos(B_ENDVERTEX_X,B_ENDVERTEX_Y,B_ENDVERTEX_Z);
  int sign_sv=vtx.z()-b_pos.z()>=0?1:-1;
  svdis = sign_sv*(vtx-b_pos).Mag();

  return;

}//end get_fc_pvdis_svdis


//
// Loop over the list of PV and return min IP and IPS 
//

void addIso::get_BminIP(int& minip_pv_id, int& minips_pv_id, double& b_ip, double& b_ips){
  b_ip=1e6;
  b_ips=1e6;
  double ip,ips,fl,fl0,ctau;
  for (int i=0;i<PV_num;i++){
    get_BIPwrtPV(i,ip,ips,fl,fl0,ctau);
    if (ip<b_ip){
      minip_pv_id=i;
      b_ip=ip;
    }
    if (ips<b_ips){
      minips_pv_id=i;
      b_ips=ips;
    }
  }//end i<PV_num

  return;
}//end get_BminIP


// Make fit of intersersection between the B direction and PV, minimizing the chi2. Extract the new vtx(B) position, slope(B) and the B f.l.
// Compute the IP between the B direction and the PV (before refit).Compute IPS as the chi2 value. Compute ctau from the f.l. (see notes below)
//
// Note: B_FD_OWNPV is defined as |x_b-x_pv|, i.e. the equivalent of q0[5] in the code below. It would be more correct to define it as 
//       (q0+dq)[5], which corresponds to the fl extracted from the 'fit'. However, to be consistent with what DaVinci does,  
//       get_BIPwrtPV returns also fl0=|x_b-x_pv|.
//       In the standard ntuples B_CTAU_ps is defined exaclty as B_FD_OWNPV/(c*B_P/B_M)*1e+12. On the other hand, B_TAU is similar to
//       fl/(c*B_P/B_M)*1e+12, even though it is not exactly so (it differs by about 0.1%).
void addIso::get_BIPwrtPV(int pv_id,double& ip, double& ips, double& fl, double& fl0, double& ctau){
  //The vector q of the params to fit is given by x,y,z,slx,sly and f.l.of B
  TVector3 xb_m=get_Bpos();
  TVector3 pb_m=get_Bmom();

  TVector3 xpv_m(PV_x[pv_id],PV_y[pv_id],PV_z[pv_id]);
  fl0=(xb_m-xpv_m).Mag();
  double q0_arr[6]={xb_m[0],xb_m[1],xb_m[2],pb_m[0]/pb_m[2],pb_m[1]/pb_m[2],fl0};
  TVectorD q0(6,q0_arr);
  //take the cov mat of PV and its inverse
  TMatrixDSym covM_pv=get_PVCov(pv_id);
  TMatrixDSym W_pv(covM_pv);
  W_pv.Invert();
  //introduce qm_pv, q0_pv and dq_pv=qm_pv-q0_pv
  double qm_pv_arr[3]={PV_x[pv_id],PV_y[pv_id],PV_z[pv_id]};
  TVectorD qm_pv(3,qm_pv_arr);
  double root=sqrt(1+q0[3]*q0[3]+q0[4]*q0[4]);
  double q0_pv_arr[3]={q0[0]-q0[3]/root*q0[5],q0[1]-q0[4]/root*q0[5],q0[2]-1/root*q0[5]};
  TVectorD q0_pv(3,q0_pv_arr);
  TVectorD dq_pv=qm_pv-q0_pv;
  //take the matrix D such that q_pv = q0_pv+D*dq
  TMatrixD D=get_dFdq(q0);
  TMatrixD D_t(D); D_t.T();

  //take the cov mat x,y,z,slx,sly of the B
  TMatrixDSym W_B=get_BCov();
  W_B.Invert();
  //define W_B_prime as W_B with the addition of one row and one col (used later)
  TMatrixDSym W_B_prime(6);
  for (int i=0;i<6;i++)
    for (int j=0;j<6;j++){
      if (i<5 && j<5) W_B_prime[i][j]=W_B[i][j];
      else W_B_prime[i][j]=0;
    }

  TMatrixD Cov_dq=D_t*W_pv*D+W_B_prime;
  Cov_dq.Invert();
  TVectorD dq=Cov_dq*(D_t*W_pv*dq_pv);

  //compute chi2 relative to PV
  TVectorD deltaq_pv=qm_pv-q0_pv-D*dq;
  double chi2_pv=deltaq_pv*(W_pv*deltaq_pv);

  //compute chi2 relative to B (it exploits the fact that q0_b was chosen so that qm_b-q0_b=0)
  double chi2_b=dq*(W_B_prime*dq);
  double chi2=chi2_b+chi2_pv;
  ips=sqrt(chi2);

  //compute the IP. NB: Do NOT use the _refitted_ vertex and slopes of B to be consistent with DaVinci
  TVector3 v=pb_m.Unit();
  TVector3 doca_vec=v.Cross(xpv_m-xb_m);
  ip=doca_vec.Mag();

  //compute the flight length
  fl=q0[5]+dq[5];
  double B_P=sqrt(B_PT*B_PT+B_PZ*B_PZ);
  double cbg=2.99792458e+11*B_P/B_MM;
  ctau=fl/cbg*1e+12;

  return;
}//end get_BIPwrtPV

TVector3 addIso::get_Bpos(){
  TVector3 out(B_ENDVERTEX_X,B_ENDVERTEX_Y,B_ENDVERTEX_Z);
  return out;
}//end get_Bpos()

TVector3 addIso::get_Bmom(){
  TVector3 out(B_PX,B_PY,B_PZ);
  return out;
}//end get_Bpos()

//As get_trkCov but applied to the B cand as opposed to the track
//Trasform the x-p cov mat into x-slopes cov mat
TMatrixDSym addIso::get_BCov(){
  double x_arr[6]={B_ENDVERTEX_X,B_ENDVERTEX_Y,B_ENDVERTEX_Z,B_PX,B_PY,B_PZ};
  TVectorD x(6,x_arr);
  TMatrixDSym covM(6);
  covM[0][0]=B_cov00;
  covM[0][1]=B_cov01;
  covM[0][2]=B_cov02;
  covM[0][3]=B_cov03;
  covM[0][4]=B_cov04;
  covM[0][5]=B_cov05;
  covM[1][1]=B_cov11;
  covM[1][2]=B_cov12;
  covM[1][3]=B_cov13;
  covM[1][4]=B_cov14;
  covM[1][5]=B_cov15;
  covM[2][2]=B_cov22;
  covM[2][3]=B_cov23;
  covM[2][4]=B_cov24;
  covM[2][5]=B_cov25;
  covM[3][3]=B_cov33;
  covM[3][4]=B_cov34;
  covM[3][5]=B_cov35;
  covM[4][4]=B_cov44;
  covM[4][5]=B_cov45;
  covM[5][5]=B_cov55;
  for (int i=0;i<6;i++)
    for (int j=0;j<i;j++) covM[i][j]=covM[j][i];

  TMatrixD J(5,6);//J_ij = df_i/d x_j
  for (int i=0;i<5;i++)
    for (int j=0;j<6;j++) J[i][j]=0;
  J[0][0]=J[1][1]=J[2][2]=1;

  J[3][3]=1/x[5];
  J[3][5]=-x[3]/(x[5]*x[5]);
  J[4][4]=1/x[5];
    J[4][5]=-x[4]/(x[5]*x[5]);

  //cov(x,y,slx,sly) = J*covM*J^T
  //TMatrixD covM_temp=(J*covM)*J.T();
  TMatrixD covM_temp=J*covM;
  TMatrixD covM_temp2=covM_temp*J.T();
  TMatrixDSym covM_new(5);
  for (int i=0;i<5;i++)
    for (int j=0;j<5;j++) covM_new[i][j]=covM_temp2[i][j];

  return covM_new;
}//end get_BCov

//return dF/dq (3x6 matrix used in get_BIPwrtPV)
TMatrixD addIso::get_dFdq(TVectorD q){
  //q={xb,yb,zb,slx_b,sly_b,fl_b}, where xb,yb,zb, slx_b and sly_b are the measured values. fl_b=|xvec_b-xvec_pv|
  double slx=q[3];
  double sly=q[4];
  double fl=q[5];
  TMatrixD out(3,6);
  out[0][0]=out[1][1]=out[2][2]=1;
  out[0][1]=out[0][2]=out[1][0]=out[1][2]=out[2][0]=out[2][1]=0;
  double root1=sqrt(1+q[3]*q[3]+q[4]*q[4]);
  double root2=pow(root1,3);
  out[0][3]=-(1+sly*sly)/root2*fl;
  out[0][4]=slx*sly/root2*fl;
  out[0][5]=-slx/root1;
  out[1][3]=slx*sly/root2*fl;
  out[1][4]=-(1+slx*slx)/root2*fl;
  out[1][5]=-sly/root1;
  out[2][3]=slx/root2;
  out[2][4]=sly/root2;
  out[2][5]=-1/root1;

  return out;
}//end get_dFdq
