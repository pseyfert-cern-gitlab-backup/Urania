#include <string>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include "TError.h"
#include "Riostream.h"

#include "TemplateTools.h"

using namespace std;
using namespace RooFit;

int main(int argc, char **argv) {

  string f_flag = "outp";
  string infi = "Strip20_20r1_data_dimuon_all_newDLL.root";
  string f_confFl = "config/config_file.txt";
  int f_debug(0), parm;
  gErrorIgnoreLevel = kFatal;

  for (int i = 0; i < argc; i++){
    cout<<" "<<argc<<" "<<argv[i]<<endl;
    if(strcmp(argv[i],"-in") == 0)    { infi = string(argv[++i]);    }                 // Decide among different MC input
    if(strcmp(argv[i],"-flag") == 0)  { f_flag = string(argv[++i]);    }                 // Flagging output eps files
    if(strcmp(argv[i],"-deb") == 0)   { f_debug = atoi(argv[++i]);  }                    // Enable debug
    if(strcmp(argv[i],"-conf") == 0) { f_confFl = string(argv[++i]);  }                    // configuration file
  }
  RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL) ;

  char name[200];

  TFile *f;
  RooWorkspace *w;
  f_flag += f_confFl;

  sprintf(name,"input/RootOutp_MCAll_%s%s.root",f_confFl.data(),"Signal_Bs0DsMu");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");
  if(f_debug) w->Print();
  sprintf(name,"histPdf_%s%s",f_confFl.data(),"Signal_Bs0DsMu");
  RooAbsPdf* f_sig_pdf = w->pdf(name);

  sprintf(name,"histPdf_BQ_%s%s",f_confFl.data(),"Signal_Bs0DsMu");
  RooAbsPdf* f_sig_pdf_bq = w->pdf(name);

  sprintf(name,"histPdf_BE_%s%s",f_confFl.data(),"Signal_Bs0DsMu");
  RooAbsPdf* f_sig_pdf_be = w->pdf(name);

    sprintf(name,"input/RootOutp_MCAll_%s%s.root",f_confFl.data(),"Signal_Bs0DstaMu");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");

  sprintf(name,"histPdf_%s%s",f_confFl.data(),"Signal_Bs0DstaMu");
  RooAbsPdf* f_dsta_pdf = w->pdf(name);

  sprintf(name,"histPdf_BQ_%s%s",f_confFl.data(),"Signal_Bs0DstaMu");
  RooAbsPdf* f_dsta_pdf_bq = w->pdf(name);

  sprintf(name,"histPdf_BE_%s%s",f_confFl.data(),"Signal_Bs0DstaMu");
  RooAbsPdf* f_dsta_pdf_be = w->pdf(name);


  sprintf(name,"input/RootOutp_MCAll_%s%s.root",f_confFl.data(),"Signal_Bs0Ds0staMu");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");

  sprintf(name,"histPdf_%s%s",f_confFl.data(),"Signal_Bs0Ds0staMu");
  RooAbsPdf* f_ds0sta_pdf = w->pdf(name);

  sprintf(name,"histPdf_BQ_%s%s",f_confFl.data(),"Signal_Bs0Ds0staMu");
  RooAbsPdf* f_ds0sta_pdf = w->pdf(name);

  sprintf(name,"histPdf_BE_%s%s",f_confFl.data(),"Signal_Bs0Ds0staMu");
  RooAbsPdf* f_ds0sta_pdf = w->pdf(name);


  sprintf(name,"input/RootOutp_MCAll_%s%s.root",f_confFl.data(),"Signal_Bs0D1pMu");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");
  
  sprintf(name,"histPdf_%s%s",f_confFl.data(),"Signal_Bs0D1pMu");
  RooAbsPdf* f_ds1pmu_pdf = w->pdf(name);

  sprintf(name,"histPdf_BQ_%s%s",f_confFl.data(),"Signal_Bs0D1pMu");
  RooAbsPdf* f_ds1pmu_pdf = w->pdf(name);

  sprintf(name,"histPdf_BE_%s%s",f_confFl.data(),"Signal_Bs0D1pMu");
  RooAbsPdf* f_ds1pmu_pdf = w->pdf(name);
  
  /*
    Tau signal
  */
  sprintf(name,"input/RootOutp_MCAll_Tau%s%s.root",f_confFl.data(),"Signal_Bs0DsTau");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");
  if(f_debug) w->Print();

  sprintf(name,"histPdf_Tau%s%s",f_confFl.data(),"Signal_Bs0DsTau");
  RooAbsPdf* f_dstau_pdf = w->pdf(name);

  sprintf(name,"histPdf_BQ_Tau%s%s",f_confFl.data(),"Signal_Bs0DsTau");
  RooAbsPdf* f_dstau_pdf = w->pdf(name);

  sprintf(name,"histPdf_BE_Tau%s%s",f_confFl.data(),"Signal_Bs0DsTau");
  RooAbsPdf* f_dstau_pdf = w->pdf(name);


  sprintf(name,"input/RootOutp_MCAll_Tau%s%s.root",f_confFl.data(),"Signal_Bs0DstaTau");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");

  sprintf(name,"histPdf_Tau%s%s",f_confFl.data(),"Signal_Bs0DstaTau");
  RooAbsPdf* f_dstatau_pdf = w->pdf(name);

  sprintf(name,"histPdf_BQ_Tau%s%s",f_confFl.data(),"Signal_Bs0DstaTau");
  RooAbsPdf* f_dstatau_pdf = w->pdf(name);

  sprintf(name,"histPdf_BE_Tau%s%s",f_confFl.data(),"Signal_Bs0DstaTau");
  RooAbsPdf* f_dstatau_pdf = w->pdf(name);

  sprintf(name,"input/RootOutp_MCAll_Tau%s%s.root",f_confFl.data(),"Signal_Bs0Ds0staTau");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");

  sprintf(name,"histPdf_Tau%s%s",f_confFl.data(),"Signal_Bs0Ds0staTau");
  RooAbsPdf* f_ds0statau_pdf = w->pdf(name);

  sprintf(name,"histPdf_BQ_Tau%s%s",f_confFl.data(),"Signal_Bs0Ds0staTau");
  RooAbsPdf* f_ds0statau_pdf = w->pdf(name);

  sprintf(name,"histPdf_BE_Tau%s%s",f_confFl.data(),"Signal_Bs0Ds0staTau");
  RooAbsPdf* f_ds0statau_pdf = w->pdf(name);

  sprintf(name,"input/RootOutp_MCAll_Tau%s%s.root",f_confFl.data(),"Signal_Bs0Ds1pTau");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");
  w->Print();
    
  sprintf(name,"histPdf_Tau%s%s",f_confFl.data(),"Signal_Bs0Ds1pTau");
  RooAbsPdf* f_ds1ptau_pdf = w->pdf(name);

  sprintf(name,"histPdf_BQ_Tau%s%s",f_confFl.data(),"Signal_Bs0Ds1pTau");
  f_ds1ptau_pdf = w->pdf(name);

  sprintf(name,"histPdf_BE_Tau%s%s",f_confFl.data(),"Signal_Bs0Ds1pTau");
  f_ds1ptau_pdf = w->pdf(name);

  /*
    Double Charm
  */

  sprintf(name,"input/RootOutp_MCAll_%s%s.root",f_confFl.data(),"LbLcDs");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");
  sprintf(name,"histPdf_%s%s",f_confFl.data(),"LbLcDs");
  f_LbLcDs_pdf = w->pdf(name);

  sprintf(name,"histPdf_BQ_%s%s",f_confFl.data(),"LbLcDs");
  f_LbLcDs_pdf = w->pdf(name);

  sprintf(name,"histPdf_BE_%s%s",f_confFl.data(),"LbLcDs");
  f_LbLcDs_pdf = w->pdf(name);


  sprintf(name,"input/RootOutp_MCAll_%s%s.root",f_confFl.data(),"BsDsDs");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");
  sprintf(name,"histPdf_%s%s",f_confFl.data(),"BsDsDs");
  f_BsDsDs_pdf = w->pdf(name);

  sprintf(name,"histPdf_BQ_%s%s",f_confFl.data(),"BsDsDs");
  f_BsDsDs_pdf = w->pdf(name);

  sprintf(name,"histPdf_BE_%s%s",f_confFl.data(),"BsDsDs");
  f_BsDsDs_pdf = w->pdf(name);

  sprintf(name,"input/RootOutp_MCAll_%s%s.root",f_confFl.data(),"BdDstDs");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");
  sprintf(name,"histPdf_%s%s",f_confFl.data(),"BdDstDs");
  f_BdDstDs_pdf = w->pdf(name);

  sprintf(name,"histPdf_BQ_%s%s",f_confFl.data(),"BdDstDs");
  f_BdDstDs_pdf = w->pdf(name);

  sprintf(name,"histPdf_BE_%s%s",f_confFl.data(),"BdDstDs");
  f_BdDstDs_pdf = w->pdf(name);

  sprintf(name,"input/RootOutp_MCAll_%s%s.root",f_confFl.data(),"BuD0Ds");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");
  sprintf(name,"histPdf_%s%s",f_confFl.data(),"BuD0Ds");
  f_BuD0Ds_pdf = w->pdf(name);

  sprintf(name,"histPdf_BQ_%s%s",f_confFl.data(),"BuD0Ds");
  f_BuD0Ds_pdf = w->pdf(name);

  sprintf(name,"histPdf_BE_%s%s",f_confFl.data(),"BuD0Ds");
  f_BuD0Ds_pdf = w->pdf(name);

  /*
    An additional tau bkg component can be foreseen
    But we fix the contribution to some fract of the DD
  */

  sprintf(name,"input/RootOutp_MCAll_Tau%s%s.root",f_confFl.data(),"Signal_Bs0DsTau");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");
  gDirectory->ls();  
  w->Print();

  sprintf(name,"histPdf_Tau%s%s",f_confFl.data(),"Signal_Bs0DsTau");
  f_taubkg_pdf = w->pdf(name);

  sprintf(name,"histPdf_BQ_Tau%s%s",f_confFl.data(),"Signal_Bs0DsTau");
  f_taubkg_pdf = w->pdf(name);

  sprintf(name,"histPdf_BE_Tau%s%s",f_confFl.data(),"Signal_Bs0DsTau");
  f_taubkg_pdf = w->pdf(name);

  /*
    Combinatorial Background
  */

  sprintf(name,"input/RootOutp_MCAll_%s%s.root",f_confFl.data(),"SideBands");
  if(f_doSameSign)
    sprintf(name,"input/RootOutp_MCAll_%s%s.root",f_confFl.data(),"SameSide");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");
  w->Print();
  if(f_doTwoD)  {
    if(f_useQsquare)  {
      sprintf(name,"histPdf_BQ_%s%s",f_confFl.data(),"SideBands");
      if(f_doSameSign)
	sprintf(name,"histPdf_BQ_%s%s",f_confFl.data(),"SameSide");
    }
    if(f_useEmu)  {
      sprintf(name,"histPdf_BE_%s%s",f_confFl.data(),"SideBands");
      if(f_doSameSign)
	sprintf(name,"histPdf_BE_%s%s",f_confFl.data(),"SameSide");
    }
  }

  f_sideb_pdf = w->pdf(name);


  return 0;
}

