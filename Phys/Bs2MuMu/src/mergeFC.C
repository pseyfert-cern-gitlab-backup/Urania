/////////////////////////////////////////////////////////////////////////
// Author: Francesco Dettori 
// macro to merge the FC output
/////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <string>
#include <fstream>
#include "root_libs.h"
#include <vector>
#include "Riostream.h"

#include "RooGlobalFunc.h"
#include "RooProfileLL.h"
#include "RooAbsPdf.h"
#include "RooStats/HypoTestResult.h"
#include "RooRealVar.h"
#include "RooPlot.h"
#include "RooDataSet.h"
#include "RooTreeDataStore.h"
#include "RooFitResult.h"
#include "RooCategory.h"
#include "RooSimultaneous.h" 
#include "TTree.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TStopwatch.h"
#include "TDatabasePDG.h"
#include "TMarker.h"
#include "zstyle.h"
#include "confinte.h" 

#include "RooStats/ProfileLikelihoodCalculator.h"
#include "RooStats/MCMCCalculator.h"
#include "RooStats/UniformProposal.h"
#include "RooStats/FeldmanCousins.h"
#include "RooStats/NumberCountingPdfFactory.h"
#include "RooStats/ConfInterval.h"
#include "RooStats/PointSetInterval.h"
#include "RooStats/ConfidenceBelt.h"
#include "RooStats/LikelihoodInterval.h"
#include "RooStats/LikelihoodIntervalPlot.h"
#include "RooStats/RooStatsUtils.h"
#include "RooStats/ModelConfig.h"

using namespace std;
using namespace RooFit ;
using namespace RooStats ;

#define NMAXFILES 100

void checkData(RooAbsData* data){
  if(!data){
    Error("CheckData","Data pointer not valid");
    exit(-1);
  }
}

//============================================================
// MAIN
//============================================================
int main(int argc, char **argv){
  zstyle();


  TString val("");
  TFile *f[NMAXFILES];
  int nfiles =0;
  TString sinfile; 
  bool files_from_dat = false;
  for(Int_t i=0; i<argc; i++){
    TString opt(argv[i]);
    cout << "testing option " << opt <<   endl; 
    if(opt.Contains(".root")){
      f[nfiles] = TFile::Open(opt);
      nfiles++;
    }
    if(opt.Contains(".dat")){ // file with list of input files 
      sinfile = opt; 
      files_from_dat = true;
    }
  }

  if(files_from_dat){
    ifstream inf(sinfile); 
    string sfname; 
    inf >> sfname; 
    while(!inf.eof()){
      f[nfiles] = TFile::Open(sfname.c_str()); 
      nfiles++;      
      inf >> sfname; 
    }    
  }
  
  
  // Make template from first file. 
  Info("Merge", "Reading data from file %s", f[0]->GetName());
  RooDataSet *data = (RooDataSet*)f[0]->Get("pointsInInterval");
  checkData(data);

  // Loop on other files 
  for(int i=1; i<nfiles; i++){
    Info("Merge", "Reading data from file %s", f[i]->GetName());
    RooDataSet *tmpdata = (RooDataSet*)f[i]->Get("pointsInInterval");
    checkData(tmpdata);
    data->append(*tmpdata);
    delete tmpdata; 
  }
  
  data->Print();

  data->SaveAs("myConfInterval_merged.root");
  //TApplication theApp("App", &argc, argv);
  
  cout << "... this is the end"<< endl;
  // theApp.Run();
  return 0;
}

