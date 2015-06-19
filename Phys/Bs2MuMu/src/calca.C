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
int main(int argc, char **argv){

  zstyle();
  TH1::SetDefaultSumw2();
  //  TString dir = "/user/fdettori/feldcus/";  // base dir 
  TString dir = "/afs/cern.ch/user/f/fdettori/cmtuser/Erasmus_v6r1/Phys/Bs2MuMu/src/";
  

  TString prefix = "Lime"; 
  double NBs(0), NBd(0);
  bool fit_bs(true), fit_bd(true); 
  int nbin(10);
  TString fileName = "RootWorksp_FD_outp.root";
  bool useConstraints(false);
  bool justFit(false);
  //size =  1 - Confidence level 
  double test_size = 0.32; // 0.1 = 90% 0.05 = 95%  CL 
  //Help
  if(argc<2){
    help();
    return 0;
  }
  // option parsing
  for(Int_t i=0; i<argc; i++){
    TString opt(argv[i]);
    if(opt.Contains("-bs")){
      TString val(argv[i+1]);
      NBs = val.Atof();
      prefix += "_bs"+val;
    }
    if(opt.Contains("-bd")){
      TString val(argv[i+1]);
      NBd = val.Atof();
      prefix += "_bd"+val;
    }
    if(opt.Contains("-bin")){
      TString val(argv[i+1]);
      nbin = val.Atof();
      prefix += "_bin"+val;
    }
    if(opt.Contains("-var")){
      TString val(argv[i+1]);
      int v = val.Atoi();
      prefix += "_var"+val;
      if(v == 1)      fit_bd = false; 
      else if(v == 2) fit_bs = false; 
      else continue; 
      
    }
    if(opt.Contains("-trial")){
      TString val(argv[i+1]);
      prefix += "_t"+val;
    }
    if(opt.Contains("-f")){
      TString val(argv[i+1]);
      fileName = val;
    }
    if(opt.Contains("-C")){
      // Apply constraints
      useConstraints = true; 
    }
    if(opt.Contains("-justFit")){
      justFit = true;
    }
  }

  // Set variables names 
  TString s_NBd =  useConstraints ? "B_{Bd}": "N_{Bd}";
  TString s_NBs =  useConstraints ? "B_{Bs}": "N_{Bs}";
  
  // to time the macro
  TStopwatch t;
  t.Start();

  // Normalization factors for 370/ pb 

  cout << " Set workspace " << endl;
  // Set workspace 
  //TString fileName = "fit1d/RootWorksp_MCAll_ScanStp04Fit_LR_NewPrio_Data.root";
  //TString fileName = "fit1d/RootWorksp_MCAll_SingleFit_LR_NewPrio_Data1fb.root";

  
  TApplication theApp("App", &argc, argv);
  confinte cf;
  cf.setWorkspace(dir+fileName); 
  cf.m_ws->Print();  
  cout << "calca: set constraints" << endl;
  cf.setConstr(useConstraints);
  // Config
  cf.setVName(s_NBs, s_NBd);
  TString _poi="";
  if(fit_bs)_poi+= s_NBs;
  if(fit_bs && fit_bd) _poi += ",";
  if(fit_bd)_poi+= s_NBd;
  cout << "calca: set POI " << endl;
  cf.setPOI(_poi);
  


  // enable proof parallelization
  cf.setParallel(true);
  

  
  cout<< "Building the model pdf " << endl;
  

  // ------------------------------------------------------------
  // lets create the model with proper categories
  RooCategory *binning = (RooCategory*)cf.m_ws->cat("binning");
  
  // Binning in BDT 
  const Int_t nBinning = 8;
  //RooDataSet* mydata[nBinning];
  //  TFile f(dir+"fit1d/RootWorksp_MCAll_ScanStp04Fit_3feb_NewPrio_RK_Data10bs1fb.root", "READ");

//   //  Import(map<string,RooDataSet*>&) -
//   cout<< "Combining the binned data " << endl;
  RooDataSet *combData = (RooDataSet*)cf.m_ws->data("combData");
  //     new RooDataSet("combData","combined data",RooArgSet(*cf.m_ws->var("m_{#mu#mu}")),Index(binning),
// 		   Import(data_map));
//   combData->Print();
  
  
  // Set observables, must include the binning 
  cf.setObs("m_{#mu#mu},binning", "obs");
  cout<< "Set data " << endl;
  cf.setData(combData);
  

  // set model 
  TString my_pdf = "simPdf";/// (useConstraints ? "pdfWithPriorC" : "simPdf"); 
  RooAbsPdf *model = (RooAbsPdf*) cf.m_ws->pdf(my_pdf);
  cf.setModel(model);
  cf.m_ws->Print();  
 
  
  if(NBs>0){    
    cout << " Adding "<< NBs << " N_bs events " << endl;
    cf.addRandom(NBs, "simBsPdf");
    cout << " Added "<< NBs << " N_bs events " << endl;
  }
  if(NBd>0){
    cout << " Adding "<< NBd << " N_bd events " << endl;
    cf.addRandom(NBd, "simBdPdf");
  }
  // Set what to fit
  if(!fit_bd){
    cout << " Setting N_bd constant " << endl;
    cf.m_ws->var(s_NBd)->setVal(0.);
    cf.m_ws->var(s_NBd)->setConstant(true);
  }
  if(!fit_bs){
    cout << " Setting N_bs constant " << endl;
    cf.m_ws->var(s_NBs)->setVal(0.);
    cf.m_ws->var(s_NBs)->setConstant(true);
  }

  cout << "debugging " << cf.m_ws->var(s_NBs)->getMin() 
       << " " << cf.m_ws->var(s_NBs)->getMax() << endl;


  RooFitResult *fitresult = cf.fitData(); 
  cout << "Fitted " << endl;
  
  
  //  Double_t tis_mean[nBinning+1]  = { 4116, 1877, 1486, 1447, 1729, 1846, 2133, 2245, 16734};
   

  double mean_bs(0.), min_fit_bs(0.), max_fit_bs (0.);
  double mean_bd(0.), min_fit_bd(0.), max_fit_bd (0.);
  double err_bs(0.), err_bd(0.);
  if(fit_bs){
    mean_bs = cf.m_ws->var(s_NBs)->getVal(); 
    err_bs =  cf.m_ws->var(s_NBs)->getError(); 
    cout << " Fitted bs " << mean_bs << " +/- " << err_bs << endl;
    // I want to scan at least till zero 
    min_fit_bs = 0 ; //min_fit_bs > 0 ? 0. : min_fit_bs;
    
    max_fit_bs = fabs(mean_bs) + 10*err_bs ;  // look up to 6 sigmas away
    //if(mean_bs<2&&mean_bs>0.) max_fit_bs = 20; 
    cout << "\n Bs fitted value = " << mean_bs
         << " assumed range to look at: [ " 
         << min_fit_bs << " - " << max_fit_bs  << " ]\n" << endl; 
    
    double fraction[nBinning];
    for(Int_t b =0; b<nBinning; b++){
      TString _bin = "fr"; _bin+= b+1;
      fraction[b] = ((RooFormulaVar*)cf.m_ws->arg(_bin))->getVal();
      cout << "Fraction " << b+1 <<  " " << fraction[b] << endl;
    }

    
  }
  if(fit_bd){
    mean_bd = cf.m_ws->var(s_NBd)->getVal(); 
    err_bd =  cf.m_ws->var(s_NBd)->getError(); 
    cout << " Fitted bd " << mean_bd << " +/- " << err_bd << endl;
    //min_fit_bd = mean_bd> 0 ? fabs(mean_bd)-6*sqrt(fabs(mean_bd)) : mean_bd - 6*sqrt(fabs(mean_bd));     // set to zero now... 
    //min_fit_bd = min_fit_bd > 0 ? 0. : min_fit_bd;
    min_fit_bd = 0;
     
    max_fit_bd = fabs(mean_bd) + 10*err_bd ;  // look up to  5 sigmas away
    cout << "\n Bd fitted value = " << mean_bd
         << " assumed range to look at: [ " 
         << min_fit_bd << " - " << max_fit_bd  << " ]\n" << endl; 
  }
  TH1 * _h_binning;
  if(fit_bs && fit_bd)     _h_binning = new TH2D("_h_binning", "_h_binning", nbin, min_fit_bs, max_fit_bs, nbin, min_fit_bd, max_fit_bd);
  else if(fit_bs)          _h_binning = new TH1D("_h_binning", "_h_binning", nbin, min_fit_bs, max_fit_bs);
  else if(fit_bd)          _h_binning = new TH1D("_h_binning", "_h_binning", nbin, min_fit_bd, max_fit_bd);
  else {   cerr << "error you are going to do nothing: set fit bd or bs to true." << endl; return -1; }
  RooDataHist * parameterScan = new RooDataHist("MyParameterScan", "", *cf.m_ws->set("myPOI"), Import(*_h_binning));

  cf.setPointsToScan(parameterScan);


  cout << "Setting range " << endl;  
  // Set the range to look at (no other solution unfortunately)
  cf.m_ws->var(s_NBs)->setRange(-20, 100);
  cf.m_ws->var(s_NBd)->setRange(-20, 100); //min_fit_bd, max_fit_bd); 
  if(fit_bs) cout << "Range for Bs is " << cf.m_ws->var(s_NBs)->getMin() <<  " ,  " << cf.m_ws->var(s_NBs)->getMax() << endl; 
  if(fit_bd) cout << "Range for Bd is " << cf.m_ws->var(s_NBd)->getMin() <<  " ,  " << cf.m_ws->var(s_NBd)->getMax() << endl; 
  
  cout << "Doing plots " << endl;  
  //cf.plot(dir+"plots/"+prefix); 
  cf.setDirAndPrefix(dir,prefix);

  
  TIterator* iter =cf.m_ws->set("obs")->createIterator();
  RooRealVar* first_obs = (RooRealVar*)iter->Next();
  cout << "make plot of data" << endl;
  TCanvas * canva = new TCanvas("canva","canva");
  canva->Divide(3,3);
  RooPlot* plot[nBinning];
  for(Int_t b = 0; b <nBinning; b++){
    canva->cd(b+1);
    plot[b] = first_obs->frame();
    TString _bin = "bin";_bin+=b+1;
    cout << "make plot of " << _bin <<  " data " <<endl;
    combData->plotOn(plot[b],Cut("binning==binning::"+_bin)) ;
    cout << "make plot of " << _bin <<  " model " <<  endl;
    model->plotOn(plot[b], Slice(*binning, _bin ),ProjWData(*binning,*combData)) ;
    model->plotOn(plot[b], Slice(*binning, _bin ),ProjWData(*binning,*combData), 
                   Components("*bs*"),LineColor(kRed)) ;
    model->plotOn(plot[b], Slice(*binning, _bin ),ProjWData(*binning,*combData), 
                   Components("*bd*"),LineColor(kMagenta)) ;
    model->plotOn(plot[b], Slice(*binning, _bin ),ProjWData(*binning,*combData), 
                   Components("mass_misid*"),LineColor(kGreen)) ;

    cout << "draw" <<_bin <<  endl;
    plot[b]->Draw();
    gPad->SetLogy();
    
  }
  
  canva->SaveAs(dir+"plots/"+prefix+"_massplots.pdf");
  
  //theApp.Run();
  if(justFit)return 1;

  RooRealVar  *vnbs = cf.m_ws->var(s_NBs);
  RooRealVar  *vnbd = cf.m_ws->var(s_NBd);
  if(nbin >0){
    cout << "calca: Getting interval " << endl;
    PointSetInterval * interval =   cf.FC_interval(test_size, nbin); 
    cout << "calca: interval got " << endl;
    if(fit_bs){
      cout << "\n N_Bs fitted value was = " << mean_bs  << endl; 
      std::cout << "N_Bs interval is ["<<  
	interval->LowerLimit(*vnbs)  << ", "  <<
	interval->UpperLimit(*vnbs) << "]" << endl;
    }
    if(fit_bd){
      cout << "\n N_Bd fitted value was = " << mean_bd  << endl; 
      std::cout << "N_Bd interval is ["<<  
	interval->LowerLimit(*vnbd)  << ", "  <<
	interval->UpperLimit(*vnbd) << "]" << endl;
    }
  
    // should I save info? 
    //cf.saveInfo();
  

    RooArgSet* tmpPoint;
    // loop over points to test
    RooAbsData * pointsScan = cf.m_fc->GetPointsToScan();
    for(Int_t i=0; i<pointsScan->numEntries(); ++i){
      // get a parameter point from the list of points to test.
      tmpPoint = (RooArgSet*) pointsScan->get(i)->clone("temp");
      if (interval){
	if(fit_bs){
	  cout << " N_bs = " << tmpPoint->getRealValue(s_NBs) << " "; 
	}
	if(fit_bd){
	  cout << " N_bd = " << tmpPoint->getRealValue(s_NBd) << " "; 
	}
	cout << "  in interval:  " << interval->IsInInterval( *tmpPoint ) << endl; 
	delete tmpPoint;
      }
    }

    if(fit_bd && fit_bs){
      cf.plotFC2D();
    }

  }// if nbin>0

  bool doCLs = false;
  if(doCLs){

    HypoTestInverterResult *r =   cf.CLs_interval();
  }




  /// print timing info
  t.Stop();
  t.Print();
    
  cout << "... this is the end"<< endl;
  //theApp.Run();
  return 0;
}

