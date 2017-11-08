#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2.h"
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

#include "TemplateTools.h"

#include <iomanip>
#include <iostream>
#include <time.h>
#include <string>

using namespace RooFit;
using namespace std;


TemplateTools::TemplateTools(string inf, string fl, int debug) {

  f_applyRange = kFALSE;
  f_range = "";
  f_fit_range_min = 3000;
  f_fit_range_max = 8000;
  //  f_fit_range_max = 5860;
  f_drawbins = 50;
  f_infi = inf;
  f_flag = fl;
  f_isMC = kFALSE;
  f_doMCmatch = kFALSE;
  f_doSS = kFALSE;
  f_doSB = kFALSE;
  f_doTau = kFALSE;
  f_doTrueDs = kFALSE;
  f_doFake = kFALSE;
  f_matchPar = 0;
  m_debug = debug;
  IDX_Prior = 0;
  sum.clear();

}

void TemplateTools::doTemplate() {

  cout<<" Entering Do Template "<<endl;

  char hn[200];  
  char pdfnm[200];
  
  TRandom3 rnd3; rnd3.SetSeed(0);

  //Here you should include your Fit Code
  gROOT->ProcessLine(".x lhcbstyle.C");

  gSystem->Load("libRooFit.so");

  gROOT->SetStyle("Plain"); 

  //Write File Result
  sprintf(hn,"output/RootOutp_MCAll_%s.root",f_flag.data());   
  cout<<"Going to write output file :: "<<hn<<endl;
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
  TFile *f_in = TFile::Open(f_infi.data());
  cout<<" "<<f_infi.data()<<endl;
  f_in->ls();  
  TTree *tree = (TTree*)f_in->Get(intrname);
  if (!tree) return;
  
  fl_nentries = tree->GetEntries();
  tree->SetBranchStatus("*",1);
  if(m_debug) tree->Print();
  tree->SetBranchAddress("Bs_0_MCORR",&fl_Bmass);
  
  /*
    # MC matching stuff
    # Will start with some common cuts. There will be redundancies there but I don't care too much.
  */

  // Cut to say it's a valid reconstructed Ds2KKpi decay.
  TString DsCut = "( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)";
  
  //Cut to say it's a valid mu from a Bs->tau->mu
  TString tauCut = "( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )";
  // Cut to say it's a valid mu from Bs->mu
  TString muCut = "( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )";
  
  // Cut to say the head of the chain is a genuine Bs
  TString Bs0Cut = "( TMath::Abs(Bs_0_TRUEID) == 531 )";
    
  // Cut to indicate the Ds was a direct product of the Bs.
  TString DsFromBsCut = "( TMath::Abs(Ds_MC_MOTHER_ID) == 531 )";
  
  // Cut to say the D came from an intermediate Ds* which came directly from a Bs0.
  TString DsStarCut = "( TMath::Abs(Ds_MC_MOTHER_ID) == 433 )";
    
  //  Same but for Ds1* modes.
  TString Ds2460Cut = "( TMath::Abs(Ds_MC_MOTHER_ID) == 20433 )";
  TString Ds2536Cut = "( TMath::Abs(Ds_MC_MOTHER_ID) == 10433 )";
    
  // For the Ds0*
  TString Ds0StarCut = "( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 )";

  /*    
    # Now for the cut independent strings.
    # For the ground state Ds modes...
  */
  // For Bs0->Dsmu:
  TString Dsmu = "( (" + DsCut + ") && (" + muCut + ") && (" + DsFromBsCut + ") && (" + Bs0Cut + ") )";
  TString Dstau = "( (" + DsCut + ") && (" + tauCut + ") && (" + DsFromBsCut + " ) && (" + Bs0Cut + ") )";

  // For the DsStar modes...
  TString DsStarmu  = "( (" + DsCut + ") && (" + muCut + ") && (" + DsStarCut + " ) && (" + Bs0Cut + ") )" ;
  TString DsStartau = "( (" + DsCut + ") && (" + tauCut + ") && (" + DsStarCut + " ) && (" + Bs0Cut + ") )" ;

  // For the Ds2460 modes...
  TString Ds2460mu  = "( (" + DsCut + ") && (" + muCut + ") && (" + Ds2460Cut + " ) && (" + Bs0Cut + ") )";
  TString Ds2460tau = "( (" + DsCut + ") && (" + tauCut + ") && (" + Ds2460Cut + " ) && (" + Bs0Cut + ") )";

  //For the Ds2536 modes...
  TString Ds2536mu  = "( (" + DsCut + ") && (" + muCut + ") && (" + Ds2536Cut + " ) && (" + Bs0Cut + ") )";
  TString Ds2536tau = "( (" + DsCut + ") && (" + tauCut + ") && (" + Ds2536Cut + " ) && (" + Bs0Cut + ") )";

  // For the Ds0Star modes...
  TString Ds0Starmu  = "( (" + DsCut + ") && (" + muCut + ") && (" + Ds0StarCut + " ) && (" + Bs0Cut + ") )";
  TString Ds0Startau = "( (" + DsCut + ") && (" + tauCut + ") && (" + Ds0StarCut + " ) && (" + Bs0Cut + ") )";

  //      TString intrname = "B2MuMuTuple/DecayTree";
  /*
    Beside MC there's also reco stuff
  */
  // PID cut
  //  TString rec_muCut = "( mc_MC12TuneV2_probNNmu )";
  TString rec_muCut = " && ( mu_ProbNNmu > 0.3)";
  TString rec_trueDs = " && (Ds_MM>1940 && Ds_MM<2000)";
  //  TString rec_isocut = " && ( Bs_0_D1_isobdt3_2nd > 0.09) "; 
  TString rec_isocut = " "; 
  TString rec_sbcut = " && (Ds_MM<1940 || Ds_MM>2000) ";
  TString cut = " Bs_0_MCORR > 3000 && Bs_0_MCORR < 8000 && (Ds_MM>1920 && Ds_MM<2010)";

  TString cutPhiPi = " && (sqrt(Kmi_M*Kmi_M+Kpl_M*Kpl_M+2*(Kmi_PE*Kpl_PE-Kmi_PX*Kpl_PX-Kmi_PY*Kpl_PY-Kmi_PZ*Kpl_PZ))>1000&&sqrt(Kmi_M*Kmi_M+Kpl_M*Kpl_M+2*(Kmi_PE*Kpl_PE-Kmi_PX*Kpl_PX-Kmi_PY*Kpl_PY-Kmi_PZ*Kpl_PZ))<1040)";

  TString cutTOT;
  if(!f_isMC) {
    //data
    if(!f_doTrueDs) {
      cutTOT = cut + rec_muCut + rec_isocut;
    } else {
      cutTOT = cut + rec_trueDs + rec_isocut;
    }
    if(f_doSB) cutTOT += rec_sbcut;

    if(f_doPhiPi) cutTOT += cutPhiPi;
  } else {
    //MC
    if(!f_doTrueDs) {
      cutTOT = cut + rec_muCut + rec_isocut;
    } else {
      cutTOT = cut + rec_trueDs + rec_isocut;
    }

    if(f_doPhiPi) cutTOT += cutPhiPi;

    if(f_doMCmatch) {
      if(f_matchPar == 1) {
	if(f_doTau) {
	  cutTOT += " && " + Dstau;
	} else {
	  cutTOT += " && " + Dsmu;
	}
      } else  if(f_matchPar == 2) {
	if(f_doTau) {
	  cutTOT += " && " + DsStartau;
	} else {
	  cutTOT += " && " + DsStarmu;
	    }
      } else  if(f_matchPar == 3) {
	if(f_doTau) {
	  cutTOT += " && " + Ds2460tau;
	} else {
	  cutTOT += " && " + Ds2460mu;
	}
      } else  if(f_matchPar == 4) {
	if(f_doTau) {
	  cutTOT += " && " + Ds2536tau;
	} else {
	  cutTOT += " && " + Ds2536mu;
	}
      } else  if(f_matchPar == 5) {
	if(f_doTau) {
	  cutTOT += " && " + 	Ds0Startau;
	} else {
	  cutTOT += " && " + 	Ds0Starmu;
	}
      } 

    }
  }


  TTreeFormula *formula = new TTreeFormula("formula",cutTOT,tree);
  f.cd();
  TH1D *histoMass = new TH1D("histoMass","",f_hbins,3000,8000);
  cout<<fl_nentries<<endl;
  for (Long64_t i=0;i<fl_nentries; i++) {
    if (i%10000 == 0) std::cout << "--- ... Processing event: " << i << std::endl;
    
    tree->GetEntry(i);
    if(m_debug)    cout<<"Applying the following CUT::  "<<cutTOT.Data()<<endl;
    Int_t ndata = formula->GetNdata();
    if(ndata!=1) cout<<""<<endl;
    if (formula->EvalInstance(0)>0){ 
      //Store datasets
      *mass = fl_Bmass;
      Ad->add(RooArgSet(*mass));
      histoMass->Fill(fl_Bmass);
    }
  }
  Ad->Print();

  RooDataHist *tmp_hist = new RooDataHist("tmp_hist","",*mass,histoMass);
  sprintf(atext,"histData_%s",f_flag.data());
  tmp_hist->SetName(atext);

  RooHistPdf *pdf_hist = new RooHistPdf("pdf_hist","",*mass,*tmp_hist);
  sprintf(atext,"histPdf_%s",f_flag.data());
  pdf_hist->SetName(atext);
    
  sprintf(atext,"dataSet_%s",f_flag.data());
  Ad->SetName(atext);

  w->import(*pdf_hist);
  w->import(*tmp_hist);
  w->import(*Ad);
  
  
  /*********************************************/
  //     Fitting Parameters are defined
  /*********************************************/
  
  //Getting back in the good old place.
  f.cd();
  
  ExpPlot(Ad, pdf_hist, f_flag);
  histoMass->Write();
  RootTree->Write();

  f.Close();

  sprintf(hn,"output/RootOutp_MCAll_%s.root",f_flag.data());   
  w->writeToFile(hn,kFALSE) ;

  return;
}


void TemplateTools::ExpPlot(RooDataSet *adt, RooAbsPdf *apdf, string flg) {

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
  
  sprintf(hn,"output/PlotPdf_%s.pdf",flg.data());   
  
  c_4->Print(hn);

}

void TemplateTools::configure(string range, bool arange, string confF) {

  f_range = range;
  f_applyRange = arange;

  if(!strcmp(range.data(),"right")) {

    //    f_fit_range_max = 6250;
    f_drawbins = 10;
    cout<<" Disabling the Misid and Excl, fitting right only up to: "<<f_fit_range_max<<endl;
  }


  mass = new RooRealVar("m_{#mu#mu}","m_{#mu#mu}",f_fit_range_min,f_fit_range_max,"MeV/c^{2}");
  mass->setBins(10000,"cache");

  mass->setRange("all_pa",f_fit_range_min,f_fit_range_max);

  mass->setRange("bli_l",f_fit_range_min,5225);
  mass->setRange("bli_u",5432,f_fit_range_max);

  //Read configuration file
  f_hbins   =  ReadValFromFile(confF,"nBinsMass");
  f_doPhiPi =  ReadValFromFile(confF,"doPhiPi");

  return;
}


vector<double> TemplateTools::ReadVecFromFile(string filen, vector<string> parnames) {

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

double TemplateTools::ReadValFromFile(string filen, string parname) {

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

void TemplateTools::doSideBands() {
  f_doSB = kTRUE;
  return;
}

void TemplateTools::doSameSide() {
  f_doSS = kTRUE;
  return;
}

void TemplateTools::doMC() {
  f_isMC = kTRUE;
  return;
}

void TemplateTools::doFake() {
  f_doFake = kTRUE;
  return;
}

void TemplateTools::doTau() {
  f_doTau = kTRUE;
  return;
}

void TemplateTools::doTrueDs() {
  f_doTrueDs = kTRUE;
  return;
}

void TemplateTools::doMCmatch(int par) {
  f_doMCmatch = kTRUE;
  f_matchPar = par;
  return;
}

void TemplateTools::SetupOutput() {

  RootTree = new TTree("ProfileTree","Profile 2D results");
  RootTree->Branch("nbs",&t_nbs,"nbs/D");
  RootTree->Branch("nbd",&t_nbd,"nbd/D");

  return;
}

