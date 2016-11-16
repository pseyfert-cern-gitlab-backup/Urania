#ifndef __CINT__
#include "RooGlobalFunc.h"
//------------------------------------------------
#endif
#include "RooMCStudy.h"
#include "RooFitResult.h"
#include "RooStats/SPlot.h"
#include <vector>
#include <string>
#include <iostream>
#include "RooRandom.h"
#include "RooMinuit.h"
#include "RooBreitWigner.h"
#include "RooGenericPdf.h"
#include "TRandom3.h"
#include <time.h>
#include <TROOT.h>
#include <TH2.h>
#include <TF1.h>
#include <TTree.h>
#include <TBranch.h>
#include <TCanvas.h>
#include <TString.h>
#include <TTimeStamp.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <TMath.h> 
#include "TH1D.h"
#include "TH2.h"
#include "RooFormulaVar.h"
#include "RooSimultaneous.h"
#include "RooCategory.h"
#include "RooArgusBG.h"
#include "TString.h"
#include "RooFormulaVar.h"
#include "RooAddPdf.h"
#include "RooLandau.h"
#include "RooGaussian.h"
#include "RooPolynomial.h"
#include "RooProdPdf.h"
#include "RooFFTConvPdf.h"
#include "RooCurve.h"
#include "RooAbsReal.h"
#include "RooCBShape.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooMappedCategory.h"
#include "BifurcatedCB.h"
#include "RooCmdArg.h"
#include "RooChebychev.h"
#include "RooUnblindUniform.h"
#include "RooUnblindPrecision.h"
#include "RooExponential.h"
#include "RooRealVar.h"
#include "RooAbsPdf.h"
#include "RooSimWSTool.h"
#include "RooWorkspace.h"
#include <TLatex.h>
#include "RooFit.h"
#include "RooConstVar.h"
#include "RooSimPdfBuilder.h"
#include "RooStringVar.h"
#include "TText.h"
#include "TPaveText.h"
#include "RooHist.h"
#include <algorithm>

using namespace std;
using namespace RooFit;
using namespace RooStats; 

void plot_with_residuals(TCanvas& _c,RooPlot& _frame,RooRealVar& var,int _nbins,double r_min,double r_max){
  
  _c.SetName("_c");
  _c.Divide(1,2);

   TVirtualPad* _c_1 = _c.cd(1);
  _c_1->SetPad(0.01,0.28,0.99,0.99);
  _frame.Draw();

  TVirtualPad* _c_2 = _c.cd(2);
  _c_2->SetPad(0.01,0.01,0.99,0.23);
  RooHist* hpull = _frame.pullHist();
  
  RooPlot* frame_pull = var.frame(Title(" "),Range(r_min,r_max),Bins(_nbins));


  frame_pull->addPlotable(hpull,"P");
  
  frame_pull->SetMinimum(-5);
  frame_pull->SetMaximum(+5);
  frame_pull->SetNdivisions(0,"x");   // 510 for having x values also
  frame_pull->SetNdivisions(504,"y");   // axis divisions was 510
  frame_pull->SetXTitle(" ");
  frame_pull->SetYTitle(" ");
 frame_pull->SetTitle(" ");
  frame_pull->SetLabelSize(0.15,"Y");
  
  frame_pull->Draw();
  
  TLine *line = new TLine(r_min,-3.,r_max,-3);
  line->SetLineStyle(1);
  line->SetLineColor(2);
  line->SetLineWidth(1);
  line->Draw();
  TLine *line2 = new TLine(r_min,+3.,r_max,+3);
  line2->SetLineStyle(1);
  line2->SetLineColor(2);
  line2->SetLineWidth(1);
  line2->Draw();
  
}

void Fit_KsPiPi_MC(){

  gROOT->ProcessLine(".x lhcbStyle.C");
  
  Int_t m1=400;
  Int_t m2=490;
  Int_t m3=510;
  Int_t m4=600;

  string bkg = "expo";
  string eopt = "cristalBall";

  TFile * f = new TFile("/afs/cern.ch/work/j/jpriscia/KSMUMU/MC/MC_KspipiSMALL_TosTos1Tos.root");
  TTree * nt = (TTree*)f->Get("DecayTree");


  Bool_t muP_isM;
  Bool_t muM_isM;
  Double_t k_mass = 0;
  Int_t Bin = 0;

  nt->SetBranchAddress("muplus_isMuon",&muP_isM);
  nt->SetBranchAddress("muminus_isMuon",&muM_isM);
  nt->SetBranchAddress("KS0_massMM",&k_mass);
  nt->SetBranchAddress("Bin",&Bin);

  RooRealVar kMass ("kMass", "M_{#pi^{+}#pi^{-}}", 400, 600, "MeV/c^{2}");  //observable  ---> To check the range!!!!!!
  RooArgSet param (kMass);
  RooDataSet data ("data","data",param);

 
  kMass.setRange("left", m1,m2);
  kMass.setRange("signal", m2,m3);
  kMass.setRange("right", m3,m4);

  
  int sigEvts = 0;

  for (int i = 0; i <  nt->GetEntries() ; i ++)
    {
      //      i < nt->GetEntries()
      nt->GetEntry(i);
      //cout<< "sn nel for"<<endl;
      if (k_mass>400 && k_mass<600 && Bin==5 && muM_isM && muP_isM ){
	
	kMass = k_mass;
	data.add(param);

	if(k_mass>490 && k_mass<510){
	  sigEvts++;

	}
      }
    }

  /*
  //BifurcatedCB 
  RooRealVar mK ("mK","mK",460,380,480);
  RooRealVar sigmaK ("sigmaK","sigmaK",5,2,10);
  RooRealVar alphaLK ("alphaLK","alphaLK",1.81,0.5,3);
  RooRealVar nLK ("nLK","nLK",2,0.1,10);
  RooRealVar alphaRK ("alphaRK","alphaRK",1.49,0.5,5);
  RooRealVar nRK ("nRK","nRK",2,0.1,10);
  
  BifurcatedCB signalK("signalK","signalK",kMass,mK,sigmaK,alphaLK,nLK,alphaRK,nRK);
  
  
  //RooPolynomial 
  RooRealVar indx0 ("k0", "indx0", 8.5,-10.,10.);
  RooRealVar indx1 ("k1", "indx1", 1.,-10.,10.);
  RooRealVar indx2 ("k2", "indx2", 7.5,-10.,10.);
  RooRealVar indx3 ("k3", "indx3", 0.5,-10.,10.);
  RooRealVar indx4 ("k4", "indx4", 0.5,-10.,10.);
  RooRealVar indx5 ("k5", "indx5", 0.5,-10.,10.);
  
  RooPolynomial signalK("model", " poly pdf", kMass, RooArgList(indx0,indx1,indx2,indx3,indx4,indx5));
  */

  /*  
  //landau
  RooRealVar mean ("mean", "mean", 460., 450., 500.);
  RooRealVar sigma ("sigma", "sigma", 2.5, 0., 15.);
  RooLandau signalK("model","landau", kMass, mean,sigma);
  */
  
  //breit
  RooRealVar  meanB ("meanB", "meanB", 460., 450., 470.);
  RooRealVar sigmaB ("sigmaB", "sigmaB", 10., 5., 30.);
  RooBreitWigner signalK ("signalK","signalK", kMass, meanB,sigmaB);
  
  /*
  //PowerLaw
  RooRealVar  mean3 ("mean3", "mean3", 400., -1., 600.);
  RooRealVar indx ("indx","indx",4.,0.,10.);
  RooGenericPdf signalK ("model","1.0/pow((kMass-mean3),indx)",RooArgList(kMass,mean3,indx)) ;
    

  //npoly
  RooRealVar indN ("indN","indN",10.0,1.,50.);
  RooGenericPdf signalK("model","1/(kMass^indN)",RooArgList(kMass,indN));
  
  //lorentz
  RooRealVar  ind1 ("ind1","ind1",0.1,-5.,5.);
  RooRealVar  ind2 ("ind2","ind2",250.0,1.,2000.);
  RooRealVar ind3 ("ind3","ind3",465.0,1.,1000.);
  RooRealVar ind4 ("ind4","ind4",0.1,-5.,5.);
  RooGenericPdf signalK("model","ind1+ind2/(1+((kMass-ind3)/ind4)^2)",RooArgList(kMass,ind1,ind2,ind3,ind4)) ;
  */

  //************************combinatorial********************

  //expo
  /*
  RooRealVar slopeK("slopeK", "slopeK",   -0.000002,-0.005,-0.0000001);
  RooExponential ChebK("ChebK", "ChebK", kMass,slopeK);
  */
  
  //cheb1
  RooRealVar slopeK("slopeK", "slopeK", 0.5,-0.1, 0.8);
  RooChebychev ChebK("ChebK", "ChebK", kMass, RooArgList(slopeK)); 
  

  

  //***********************number of events***********************
  cout<<"qui anche"<<endl;
  RooRealVar NSig("NSig","NSig",700,0,10000);
  RooRealVar NCombBkg("NCombBkg","NCombBkg",0.00000000001,0.000000000000000000001,10);

  RooAddPdf model("model","model",RooArgList(signalK,ChebK),RooArgList(NSig,NCombBkg));

  cout<<"prima del fit"<<endl;
  RooFitResult * rf=  model.fitTo(data,Range("left,right"),Extended(),Save());
  //  model.fitTo(data,Extended());
  cout<<"ha fittato"<<endl;

  //***********************Plot**************************

  RooPlot* kFrame = kMass.frame(); 
  data.plotOn(kFrame, Binning(50));
  model.plotOn(kFrame,Components(signalK),LineStyle(9),LineWidth(2), LineColor(kRed), Range("left,right"),NormRange("left,right"));
  model.plotOn(kFrame,Components(ChebK),LineStyle(9),LineWidth(2), LineColor(kBlue), Range("left,right"),NormRange("left,right"));
  model.plotOn(kFrame,Range("left,right"),NormRange("left,right"));
  model.plotOn(kFrame,Name("sigReg"),Range("signal"),NormRange("left,right"), LineColor(kGreen));
  
  

 TLatex *myLatex = new TLatex(0.5,0.5,"");
  myLatex->SetTextFont(132);
  myLatex->SetTextColor(1);
  myLatex->SetTextAlign(11);
  myLatex->SetNDC(kTRUE);
  myLatex->SetTextSize(0.06); 


  TCanvas * kCanvas = new TCanvas("kCanvas", "kCanvas", 800,600); 
  plot_with_residuals(*kCanvas,*kFrame,kMass,50,350,550);
  kCanvas->cd(1);
  myLatex->DrawLatex(0.65, 0.85,"LHCb simulation");


  cout<<"events in the signal region: " << sigEvts<<endl;
  //  cout<<"mymethod = " <<  kFrame->findObject("sigReg").average(490,510)*20<<endl;


  RooArgList pars = rf->floatParsFinal();
  float n = ((RooRealVar*) pars.find("NSig"))->getVal();
  float dn = ((RooRealVar*) pars.find("NSig"))->getError();

  RooAbsReal* xtra_int = model.createIntegral(kMass,NormSet(kMass), Range("signal")) ;
  RooAbsReal* full_int = model.createIntegral(kMass,NormSet(kMass), Range("signal,left,right")) ;

  cout << " xtra_int  = " << xtra_int->getVal()* n/full_int->getVal() << endl;
  cout << " full_int  = " << full_int->getVal()  << endl;
  cout<<"n: "<<n<<endl;

  cout<< xtra_int->getVal() * n/full_int->getVal() << " +- " << xtra_int->getVal() * dn/full_int->getVal() << endl;
  // bCanvas->cd();
  //  bFrame->Draw();
  
  // etaCanvas->cd();
  // etaFrame->Draw();
 
  // TFile outputFile ("FIT_ETAPKMC_newStrip_2012_tailsFixed.root","RECREATE");
  // bCanvas->Write();
  //etaCanvas->Write();
 
  //     outputFile.Close();
  


}
