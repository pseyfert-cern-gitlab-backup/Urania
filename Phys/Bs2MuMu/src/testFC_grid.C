/////////////////////////////////////////////////////////////////////////
// Author: Francesco Dettori 
// macro to test the FC estimation
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

void help()
{
  cout << " Usage : ./calca -bs 20 -bd 30 -bin 10 -var 0 -trial a "<< endl
       << "-bs is the number of fake Bs to add \n" 
       << "-bd is the number of fake Bd to add \n " 
       << "-bin is the binning in each variable (N_Bs and N_Bd)\n"
       << "-var is the variable to keep fixed (0=none 1 = bd 2 = bs)"
       << "-trial is a just an additional label "<<endl;
  
}




//============================================================
// MAIN
//============================================================
int a_main(int argc, char **argv){

  zstyle();
  TH1::SetDefaultSumw2();
  //  TString dir = "/user/fdettori/feldcus/";  // base dir 
  TString dir = "";///afs/cern.ch/user/f/fdettori/cmtuser/Erasmus_v6r1/Phys/Bs2MuMu/src/";
  

  TString prefix = "Lime"; 
  double NBs(0), NBd(0);
  bool fit_bs(true), fit_bd(true); 
  int nbin(10);
  TString fileName = "DoubleGaussModel_x3.000000_y3.000000.root";

  bool useConstraints(false);
  bool justFit(false);
  //size =  1 - Confidence level 
  double test_size = 0.1; // 0.1 = 90% 0.05 = 95%  CL 
  int nth_test_point = -1;
  int n_points = 1;
  bool fcr = false;
  //Help
//   if(argc<2){
//     help();
//     return 0;
//   }
  // option parsing
  TString val("");
  TString outFileName;
  for(Int_t i=0; i<argc; i++){
    TString opt(argv[i]);
    cout << "testing option " << opt <<   endl;
    
    if(opt.Contains("-bs")){
      val = TString(argv[++i]);
      NBs = val.Atof();
      prefix += "_bs"+val;
    }
    if(opt.Contains("-bd")){
      val = TString(argv[++i]);
      NBd = val.Atof();
      prefix += "_bd"+val;
    }
    if(opt.Contains("-bin")){
      val = TString(argv[++i]);
      nbin = val.Atof();
      prefix += "_bin"+val;
    }
    if(opt.Contains("-var")){
      val = TString(argv[++i]);
      int v = val.Atoi();
      prefix += "_var"+val;
      if(v == 1)      fit_bd = false; 
      else if(v == 2) fit_bs = false; 
      else continue; 
      
    }
    if(opt.Contains("-trial")){
      val = TString(argv[++i]);
      prefix += "_t"+val;
    }
    if(opt.Contains("-P")){
      val = TString(argv[++i]);
      nth_test_point = val.Atoi() ; 
    }
    if(opt.Contains("-points")){
      val = TString(argv[++i]);
      n_points = val.Atoi() ; 
    }
    if(opt.Contains("-f")){
      fileName = TString(argv[++i]);
      //cout << " filename "<< fileName << " " << val << " " << argv[i+1] << endl;
      
    }
    if(opt.Contains("-C")){
      // Apply constraints
      useConstraints = true; 
    }
    if(opt.Contains("-o")){
      // Apply constraints
      outFileName = TString(argv[++i]);
    }
    if(opt.Contains("-justFit")){
      justFit = true;
    }
    if(opt.Contains("-FCR")){
      // Do RooStat Feldman-Cousins implementation
      fcr = true;
      
    }
  }


  cout << " debug options " << justFit << " " << useConstraints << " " 
       << fileName << " " << prefix << " " << endl;
  
  // Set variables names 

  
  // to time the macro
  TStopwatch t;
  t.Start();

  
  TApplication theApp("App", &argc, argv);
  confinte cf;
  cf.setWorkspace(dir+fileName,"w;1"); 
  cf.m_ws->Print();  
  cout << "calca: set constraints" << endl;
  //  cf.setConstr(useConstraints);
  // Config
  //  cf.setVName(s_NBs, s_NBd);
  cf.setOutFile(outFileName);
  
  //  cf.setPOI("s");
  // cf.setPOI("meanx,meany");
  TString poiname  = "B_{Bs}";
  cf.setPOI(poiname);
  cf.m_ws->var("B_{Bd}")->setConstant(kTRUE);
  cf.m_ws->var("alpha_{Bd}")->setConstant(kTRUE);

  // Set range of the variable NOT of the POI
  //  cf.m_ws->var("N_{Bs}")->setRange(-5,100);
  
  //  cf.setObs("x,y", "obs");
  cf.setObs("m_{#mu#mu},binning", "obs");

  // enable proof parallelization
  //  cf.setParallel(true);
  

  

  cout<< "Set data" << endl;
  RooDataSet *data = (RooDataSet*)cf.m_ws->data("combData");
  if(!data){
    cerr << " NO DATA " << endl;
    exit(-1);
  }
  cf.setData(data);
  
  
  cf.setNBin(nbin);
  // set model 
  TString my_pdf = "simPdf";/// (useConstraints ? "pdfWithPriorC" : "simPdf"); 
  cout  << " Setting model " << my_pdf << endl;
  RooAbsPdf *model = (RooAbsPdf*) cf.m_ws->pdf(my_pdf);
  
  cf.setModel(model);
  //cf.m_ws->Print();  
  cout << "#####################" << endl;
  cf.setModelConfig("myProblem");
  cout << "#####################" << endl;
  
  
  
  TH1 * _h_binning;
  //if(fit_bs && fit_bd)     _h_binning = new TH2D("_h_binning", "_h_binning", 
  //nbin, min_fit_bs, max_fit_bs, nbin, min_fit_bd, max_fit_bd);
  //  else if(fit_bs)
  double poimin = 0.;
  double poimax = 1e-8;
  double poi_step = (poimax - poimin)/(double)nbin;
  double test_min = poi_step * nth_test_point + poimin;
  double test_max = poi_step * (nth_test_point+n_points+1)+poimin ;
  _h_binning = new TH1D("_h_binning", "_h_binning", n_points, test_min, test_max);
  
  
  //else if(fit_bd)          _h_binning = new TH1D("_h_binning", "_h_binning", nbin, min_fit_bd, max_fit_bd);
  //  else {   cerr << "error you are going to do nothing: set fit bd or bs to true." << endl; return -1; }

  RooArgSet * poi_snapshot = (RooArgSet*)cf.m_ws->set("myPOI")->snapshot();
  RooDataHist * parameterScan = new RooDataHist("MyParameterScan", "", *cf.m_ws->set("myPOI"), Import(*_h_binning));
  TIter it_snap = poi_snapshot->createIterator();
  TIter it = cf.m_ws->set("myPOI")->createIterator();
  RooRealVar *myarg, *mysnap; 
  Info("Main","Restoring previous border values to avoid RooDataHist bug ");
  while ((myarg = dynamic_cast<RooRealVar*>(it.Next()))) { 
    mysnap = dynamic_cast<RooRealVar*>(it_snap.Next());
    myarg->setRange(mysnap->getMin(),mysnap->getMax());
    //cout << " Setting range " << mysnap->GetName() << " " << mysnap->getMin()<< " " <<mysnap->getMax()<< endl;
  
  }

  
  ////#  cf.m_ws->var("B_{Bs}")->setRange(-1e-7, 1e-6);
  
  cf.setPointsToScan(parameterScan);
  
 
  if(fcr){
    cf.setDirAndPrefix(dir,prefix);

  
    // TIterator* iter =cf.m_ws->set("obs")->createIterator();
    // RooRealVar* first_obs = (RooRealVar*)iter->Next();
    // cout << "make plot of data" << endl;
    // TCanvas * canva = new TCanvas("canva","canva");
    // canva->Divide(3,3);
    TIterator* iter =cf.m_ws->set("myPOI")->createIterator();
    const Int_t npoi = cf.m_ws->set("myPOI")->getSize();
    
    if(nbin >0){
      cout << "calca: Getting interval " << endl;
      PointSetInterval * interval =   cf.FC_interval(test_size); 
      cout << "calca: interval got " << endl;
    
      RooRealVar* first_poi = (RooRealVar*)iter->Next();
      RooRealVar* second_poi;
      if(npoi>1) second_poi = (RooRealVar*)iter->Next();
      RooArgSet* tmpPoint;
      // loop over points to test
      RooAbsData * pointsScan = cf.m_fc->GetPointsToScan();
      for(Int_t i=0; i<pointsScan->numEntries(); ++i){
        /// get a parameter point from the list of points to test.
        tmpPoint = (RooArgSet*) pointsScan->get(i)->clone("temp");
        if (interval){
          cout << first_poi->GetName() << " = " << tmpPoint->getRealValue(first_poi->GetName()) << " "; 
          if(npoi>1) cout << second_poi->GetName() << "  = " << tmpPoint->getRealValue(second_poi->GetName()) << " "; 
        }
        cout << "  in interval:  " << interval->IsInInterval( *tmpPoint ) << endl; 
        delete tmpPoint;
      }
      
      cout << " Interval for " << first_poi->GetName() << "  is  [" 
           << interval->LowerLimit(*first_poi)  << ", "  
           << interval->UpperLimit(*first_poi) << "]" << endl;
      if(npoi>1) cout << " Interval for " << second_poi->GetName() << "  is  [" 
                      << interval->LowerLimit(*second_poi)  << ", "  
                      << interval->UpperLimit(*second_poi) << "]" << endl;
    
      //if(npoi==1)     cf.plotFC();
      if(npoi==2) cf.plotFC2D();
    
    

    }// if nbin>0
  }
  bool doCLs = false;
  if(doCLs){

    HypoTestInverterResult *r =   cf.CLs_interval();
  }


  // Run Felman Cousins interval by hand... 
  Info("Main", "Now let's start FC");
  
  cf.FeldmanCousinsInt(  nth_test_point, n_points );
    
  /// print timing info
  t.Stop();
  t.Print();
    
  cout << "... this is the end"<< endl;

  return 0;
}

