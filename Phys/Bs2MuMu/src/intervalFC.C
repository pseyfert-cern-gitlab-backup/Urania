/////////////////////////////////////////////////////////////////////////
// Author: Francesco Dettori 
// macro to get the the FC interval from the merged output
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
  TString filename;
  double confLevel = 0.9;
  TString poiname = "B_{Bs}";
  for(Int_t i=0; i<argc; i++){
    TString opt(argv[i]);
    cout << "testing option " << opt <<   endl; 
    if(opt.Contains(".root")){
      filename = opt; 
    }
    if(opt.Contains("-cl")){
      val = TString(argv[++i]);
      confLevel = val.Atof();
    }
    if(opt.Contains("-poi")){
      val = TString(argv[++i]);
      poiname = val;
    }
    
  }
  
  TFile f(filename);
  RooDataSet *data = (RooDataSet*)f.Get("pointsInInterval");

  RooRealVar * var1 =  (RooRealVar*)(data->get())->find(poiname);
  RooRealVar * var2 =  (RooRealVar*)(data->get())->find("cl");
  if(!var1 || !var2){
    Error("interval", "variables not found ");
    exit(-1);
  }
  
  checkData(data);
  data->Print();
  
  double min_interval = 1e30; 
  double max_interval = -1e30;
    
  Int_t entries = data->numEntries();
  TGraph * gr = new TGraph(entries);
  for(Int_t i =0; i<entries; i++){
    const RooArgSet * evt = data->get(i);
    double x = evt->getRealValue(poiname);
    double cl  = evt->getRealValue("cl");
    gr->SetPoint(i, x, cl ); 
    if(cl >= (1-confLevel)){
      if(min_interval > x )min_interval = x;
      if(max_interval < x )max_interval = x; 
    }
  }
  TApplication theApp("App", &argc, argv);
  TCanvas * canva = new TCanvas("canva","canva", 700,500);
  gr->Draw("AP*");
  double xmin, xmax, ymin, ymax;
   
  
  data->getRange(*var1, xmin, xmax);
  //  data->getRange(*var2, ymin, ymax);
  ymin = 1-confLevel;
  ymax = 1-confLevel;
  
  TLine * line = new TLine(xmin, ymin, xmax, ymax);
  line->SetLineWidth(2);
  line->SetLineColor(kRed);
  line->Draw("SAME");
  
  cout << "... this is the end"<< endl;
  gr->SaveAs("interval.root");
  

  cout << "Interval is " << min_interval << " - " << max_interval << endl;
   theApp.Run();
  return 0;
}

