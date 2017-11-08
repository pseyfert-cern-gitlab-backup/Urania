#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TFile.h"
#include "TLatex.h"
#include "TPaveText.h"
#include "TTree.h"
#include "TRandom.h"

#include "RooWorkspace.h"
#include "RooPlot.h"
#include "RooBinning.h"
#include "RooRandom.h"
#include "RooGenericPdf.h"
#include "RooPolynomial.h"
#include "RooThresholdCategory.h"
#include "RooGlobalFunc.h"
#include "RooKeysPdf.h"
#include "RooNDKeysPdf.h"
#include "RooBDecay.h"
#include "RooRealSumPdf.h"
#include "RooAddPdf.h"
#include "RooCategory.h"
#include "RooMinuit.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooFormulaVar.h"
#include "RooEffProd.h"
#include "RooRealConstant.h"
#include "RooGaussModel.h"
#include "RooGaussian.h"
#include "RooProdPdf.h"
#include "RooAddModel.h"
#include "RooDataHist.h"
#include "RooExponential.h"
#include "RooGenericPdf.h"
#include "RooNumConvPdf.h"
#include "RooFFTConvPdf.h"
#include "RooExtendPdf.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooMCStudy.h"

//#include "doTemplates.h"

#include <iomanip>
#include <iostream>
#include <time.h>
#include <string>

using namespace RooFit;
using namespace std;

void doTemplate() {

  std::cout << " Entering Do Template " << std::endl;

  f_fit_range_min = 5100;
  f_fit_range_max = 5600;
  f_drawbins = 100;
  f_infi = inf;
  f_doRooKeys = kTRUE;

  char hn[200];  
  char pdfnm[200];
  
  //Here you should include your Fit Code
  //gROOT->ProcessLine(".x lhcbstyle.C");
  gSystem->Load("libRooFit.so");
  gROOT->SetStyle("Plain"); 

  //Write File Result
  sprintf(hn,"output/RootOutp_MCAll_BsDsstPi_Weight.root");   
  std::cout<<"Going to write output file :: "<<hn<<std::endl;
  TFile f(hn,"RECREATE"); f.cd();

  RooWorkspace *w;
  
  sprintf(pdfnm,"w");
  w = new RooWorkspace(pdfnm,"workspace");

  /*
    Create Dataset
  */

  char atext[200];
  Double_t fl_Bmass;
  sprintf(atext,"dataset");
  RooDataSet* Ad  = new  RooDataSet(atext,atext,RooArgSet(*mass));

  TString intrname;
  /*
  intrname = "B2DsMuNuTuple/DecayTree";
  if(!f_isMC) {
    intrname = "B2DsMuNuTuple/DecayTree";
    if(f_doFake) {
      intrname = "B2DsMuNuTupleFake/DecayTree";
    }
    if(f_doSS) {
      intrname = "B2DsMuNuSSTuple/DecayTree";
    }
  }
  */
  intrname = "DecayTree";
  TFile *f_in = TFile::Open(f_infi.data());
  std::cout << " " << f_infi.data() << std::endl;
  f_in->ls();  
  TTree *tree = (TTree*)f_in->Get(intrname);
  if (!tree) return;
  
  fl_nentries = tree->GetEntries();
  std::cout << "Number of entries = " << fl_nentries << std::endl;
  tree->SetBranchStatus("*",1);
  tree->Print();
  tree->SetBranchAddress("B_MM",&fl_Bmass);
  
  /*
    Reco cuts
  */

  TString cutTOT = "Ds_MM>1940 && Ds_MM<2000 && Kpl_PIDK>0 && Kmi_PIDK>0 && B_MM<5600 && B_MM>5100 && piFromB_PIDK<0 && Ds_ENDVERTEX_CHI2<15 && B_ENDVERTEX_CHI2<6 && Kpl_ProbNNp<0.7 && Kmi_ProbNNp<0.7 && pi_PIDK<0";
  std::cout << "With weight = " << cutTOT << std::endl;

  TTreeFormula *formula = new TTreeFormula("formula",cutTOT,tree);
  f.cd();

  TH1D *histoMass = new TH1D("histoMass","",100,5100,5600);

  mass = new RooRealVar("m_{D_{s}#pi}","B_s mass",f_fit_range_min,f_fit_range_max,"MeV/c^{2}");
  mass->setBins(100);

  std::cout<<fl_nentries<<std::endl;
  for (Long64_t i=0;i<fl_nentries; i++) {
    if (i%10000 == 0) std::cout << "--- ... Processing event: " << i << std::endl;
    
    tree->GetEntry(i);
    if(m_debug) std::cout<<"Applying the following CUT::  "<<cutTOT.Data()<<std::endl;
    Int_t ndata = formula->GetNdata();
    if(ndata!=1) std::cout<<""<<std::endl;
    if (formula->EvalInstance(0)>0){ 
      //Store datasets
      *mass = fl_Bmass;
      
      Ad->add(RooArgSet(*mass));
      histoMass->Fill(fl_Bmass);
    }
  }
  Ad->Print();

  std::cout << "All events processed" << std::endl;

  if(!f_doRooKeys) {  
    
    RooDataHist *tmp_hist = new RooDataHist("tmp_hist","",*mass,histoMass);
    sprintf(atext,"histData_BsDsstPi");
    tmp_hist->SetName(atext);
    
    RooHistPdf *pdf_hist = new RooHistPdf("pdf_hist","",*mass,*tmp_hist);
    sprintf(atext,"histPdf_BsDsstPi");
    pdf_hist->SetName(atext);
    
    w->import(*pdf_hist);
    w->import(*tmp_hist);
    
  } else {

    RooKeysPdf *pdf_rkeys = new RooKeysPdf("pdf_rkeys","",*mass,*Ad) ;
    sprintf(atext,"keysPdf_BsDsstPi");
    pdf_rkeys->SetName(atext);
   
    w->import(*pdf_rkeys);
  }

  sprintf(atext,"dataSet_BsDsstPi");
  Ad->SetName(atext);

  w->import(*Ad);
  
  /*********************************************/
  //     Fitting Parameters are defined
  /*********************************************/
  
  //Getting back in the good old place.
  f.cd();

  histoMass->Write();

  f.Close();

  sprintf(hn,"output/RootOutp_MCAll_BsDsstPi_Weight.root");   
  w->writeToFile(hn,kFALSE) ;

  return;
}

void ExpPlot(RooDataSet *adt, RooAbsPdf *apdf) {

  RooPlot *rpb; char hn[200];
  TLatex *lhcbLatex;
  lhcbLatex = new TLatex(0.18, 0.83,"#splitline{LHCb}{Preliminary}");
  TCanvas *c_4 = new TCanvas("c_4","");
  //Expert plot

  c_4->Clear(); c_4->cd(); 
  //  gPad->SetLogy();

  //  rpb = abdt->frame(5100,5600,25);
  rpb = mass->frame(f_fit_range_min,f_fit_range_max,f_drawbins);
  //  rpb = abdt->frame(5000,5500,20);
  gPad->SetLeftMargin(0.14);
  gPad->SetBottomMargin(0.14);
  gPad->SetRightMargin(0.05);
  gPad->SetTopMargin(0.05);
  rpb->SetTitle("");
  rpb->SetTitleSize(0.06,"x");
  rpb->SetTitleSize(0.06,"y");
  adt->plotOn(rpb);
  apdf->plotOn(rpb);

  lhcbLatex->SetNDC(kTRUE);
  //  lhcbLatex->SetTextFont(lhcbFont);
  lhcbLatex->SetTextColor(1);
  lhcbLatex->SetTextSize(0.06);
  lhcbLatex->DrawLatex(0.18, 0.83,"#splitline{LHCb}{Preliminary}");
  rpb->SetName("plot");
  rpb->Draw();
  rpb->Write();
  
  sprintf(hn,"output/PlotPdf_BsDsstPi.pdf");   
  
  c_4->Print(hn);

}
/*
vector<double> ReadVecFromFile(string filen, vector<string> parnames) {

  char bufConf[200]; 
  char parn[120];
  double val;
  ifstream incF; 

  incF.open(filen.data());

  std::cout<<" ::: Setting Fit Parameters from "<<filen.data()<<" file ::: "<<std::endl;

  vector<double> resvec;
  while (incF.getline(bufConf, 200, '\n')) {
    sscanf(bufConf, "%s = %lf",parn,&val);
    for(int ipn=0; ipn<(int)parnames.size(); ipn++) {
      if(!strcmp(parn,parnames.at(ipn).data())) {
	      resvec.push_back(val);
	      std::cout<<"Read value :: "<<val<< " :: for param :: "<<parn<<std::endl;
      }
    }
  }
		
  incF.close();
  return resvec;

}

double ReadValFromFile(string filen, string parname) {

  char bufConf[200]; 
  char parn[120];
  double val;
  ifstream incF; 

  incF.open(filen.data());

  std::cout<<" ::: Setting Fit Parameters from "<<filen.data()<<" file ::: "<<std::endl;

  double resvec;
  while (incF.getline(bufConf, 200, '\n')) {
    sscanf(bufConf, "%s = %lf",parn,&val);
    if(!strcmp(parn,parname.data())) {
      resvec = val;
      std::cout<<"Read value :: "<<val<< " :: for param :: "<<parn<<std::endl;
    }
  }

  incF.close();
					
  return resvec;

}

void SetupOutput() {

  RootTree = new TTree("ProfileTree","Profile 2D results");
  RootTree->Branch("nbs",&t_nbs,"nbs/D");
  RootTree->Branch("nbd",&t_nbd,"nbd/D");

  return;
}
*/
