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
#include "RooMCStudy.h"
#include "RooChi2Var.h"

#include "FitTools.h"

#include <iomanip>
#include <iostream>
#include <time.h>
#include <string>

using namespace RooFit;
using namespace std;


FitTools::FitTools(string inf, string fl, int dbg, bool sigO, bool addCon) {

  f_applyRange = kFALSE;
  f_range = "";
  f_fit_range_min = 3000;
  f_fit_range_max = 8000;
  //  f_fit_range_max = 5860;
  f_drawbins = 125;
  f_infi = inf;
  f_flag = fl;
  f_flag = fl;
  f_hbins = 125;
  f_doPhiPi = 0;
  f_addDs1p = 0;
  f_addCon = addCon;
  f_applyTauCut = 0;
  f_applyIsoCut = 0;
  f_applyBMCut = 0;
  f_useTauPdfs = 0;
  f_doMCmat = kFALSE;
  f_doTau = kFALSE;
  f_doTwoD = kFALSE;
  f_doSameSign = kFALSE;
  f_debug = dbg;
  f_sigOnly = sigO;
  f_useQsquare   =  1;
  f_useEmu   =  0;

}

void FitTools::doFit() {

  cout<<" Entering Do FIt "<<endl;

  char hn[200];  
  char pdfnm[200];
  
  TRandom3 rnd3; rnd3.SetSeed(0);

  //Here you should include your Fit Code
  gROOT->ProcessLine(".x lhcbstyle.C");

  gSystem->Load("libRooFit.so");

  gROOT->SetStyle("Plain"); 

  //Write File Result
  sprintf(hn,"output/RootOutp_FitResult_%s.root",f_flag.data());   
  cout<<"Going to write output file :: "<<hn<<endl;
  TFile f(hn,"RECREATE"); f.cd();

  RooWorkspace *w;
  RooMinuit *m1;

  RooAbsPdf* pdf_fit;

  
  sprintf(pdfnm,"w");
  w = new RooWorkspace(pdfnm,"workspace");
  //  w->import(*pdf_fit,RenameConflictNodes("1"));
  sprintf(pdfnm,"pdf_fit");
  cout<<f_my_pdfs->getSize()<<" "<<f_my_yields->getSize()<<endl;;
  pdf_fit = new RooAddPdf(pdfnm,"",RooArgSet(*f_my_pdfs),RooArgSet(*f_my_yields));

  /*
    Create Dataset
  */

  char atext[200];
  Double_t fl_Bmass;
  sprintf(atext,"dataset");
  RooDataSet* Ad;
  if(f_doTwoD) {
    if(f_useQsquare)
      Ad  = new  RooDataSet(atext,atext,RooArgSet(*mass,*qsquare));
    if(f_useEmu) 
      Ad  = new  RooDataSet(atext,atext,RooArgSet(*mass,*emu));
  }
  else Ad  = new  RooDataSet(atext,atext,RooArgSet(*mass));

  RooDataHist* AdH;
  if(f_doTwoD) {
    if(f_useQsquare)
      AdH  = new  RooDataHist(atext,atext,RooArgSet(*mass,*qsquare),"fewb");
    if(f_useEmu)
      AdH  = new  RooDataHist(atext,atext,RooArgSet(*mass,*emu),"fewb");
  }
  else AdH  = new  RooDataHist(atext,atext,RooArgSet(*mass),"fewb");

  //TREE name
  //  TString intrname = "DecayTree";
  TString intrname = "B2DsMuNuTuple/DecayTree";

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


  //  TString rec_muCut = " && ( mu_ProbNNmu > 0.3)";
  TString rec_muCut = " && ( mu_PIDmu > 0)";
  //  TString rec_isocut = " && ( Bs_0_D1_isobdt3_2nd > 0.09) "; 
  //  TString rec_isocut = " && Ds_SmallestDeltaChi2OneTrack > 5"; 
  TString rec_isocut = " "; 
  if(f_applyIsoCut) rec_isocut = " && (mu_iso_MinBDT_Long>-0.5) ";
  //  if(f_applyIsoCut) rec_isocut = " && (mu_iso_MinBDT_Long>0.25) ";
  TString cut = " Bs_0_MCORR > 3000 && Bs_0_MCORR < 8000 && (Ds_MM>1920 && Ds_MM<2010) && (resFlag != 2) ";

  TString trig_unb = " && ( Kpl_P>5000 && Kmi_P>5000 && pi_P>5000 && (Kpl_PT>800 || Kmi_PT>800 || pi_PT>800) && Ds_PT>2000 && Bs_0_BDTS_DOCA<0.50 && Bs_0_FDCHI2_TOPPV>50 && 1920<Ds_MM && 2010>Ds_MM  ) ";
  if(!f_doMCmat) trig_unb = " && (Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS == 1)";

  TString cutPhiPi = " && (sqrt(Kmi_M*Kmi_M+Kpl_M*Kpl_M+2*(Kmi_PE*Kpl_PE-Kmi_PX*Kpl_PX-Kmi_PY*Kpl_PY-Kmi_PZ*Kpl_PZ))>1000&&sqrt(Kmi_M*Kmi_M+Kpl_M*Kpl_M+2*(Kmi_PE*Kpl_PE-Kmi_PX*Kpl_PX-Kmi_PY*Kpl_PY-Kmi_PZ*Kpl_PZ))<1040)";

  TString cutTOT;

  TFile *f_in = TFile::Open(f_infi.data());
  cout<<" "<<f_infi.data()<<endl;
  f_in->ls();  
  TTree *tree = (TTree*)f_in->Get(intrname);
  if (!tree) return;
  
  fl_nentries = tree->GetEntries();
  tree->SetBranchStatus("*",1);
  tree->SetBranchAddress("Bs_0_MCORR",&fl_Bmass);
  tree->SetBranchAddress("q2",&fl_q2);
  tree->SetBranchAddress("Emu",&fl_Emu);
  tree->SetBranchAddress("MM2",&fl_MM2);

  cutTOT = cut + rec_muCut + rec_isocut;

  if(f_applyBMCut) cutTOT += " && (sqrt( (Ds_PE+mu_PE)**2 - ((Ds_PX+mu_PX)**2 + (Ds_PY+mu_PY)**2 + (Ds_PZ+mu_PZ)**2) ) > 3000) ";

  if(f_applyTauCut) cutTOT += " && (mu_PT>1000)";

  //  if(!f_doTau) cutTOT += " && (sqrt( (Ds_PE+mu_PE)**2 - ((Ds_PX+mu_PX)**2 + (Ds_PY+mu_PY)**2 + (Ds_PZ+mu_PZ)**2) ) > 3000)  && (mu_PT>1000)";

  if(f_useQsquare) cutTOT += " && (q2>-5000000) ";

  if(f_doPhiPi) cutTOT += cutPhiPi;

  //Only 3 principal modes

  //3comp  
  //  if(f_doMCmat) cutTOT += " && ( " + Dsmu + " || " + Dstau + " || " + DsStarmu + " || " + DsStartau + " || " + Ds0Starmu + " ) ";

  //3comp  
  if(f_doMCmat) cutTOT += " && ( " + Dsmu + " || " + Dstau + " || " + DsStarmu + " || " + DsStartau + " || " + Ds0Starmu + " || " + Ds0Startau + " ) ";

  //Adding Ds1p
  //  if(f_doMCmat) cutTOT += " && ( " + Dsmu + " || " + Dstau + " || " + DsStarmu + " || " + DsStartau + " || " + Ds0Starmu + " || " + Ds0Startau + " || " + Ds2536tau + " || " + Ds2536mu + " ) ";

  //  cutTOT += " && ( " + Ds0Startau + " ) ";

  cutTOT += trig_unb;

  cout<<cutTOT<<endl;

  TTreeFormula *formula = new TTreeFormula("formula",cutTOT,tree);
  f.cd();  
  
  for (Long64_t i=0;i<fl_nentries; i++) {
    if (i%10000 == 0) std::cout << "--- ... Processing event: " << i << std::endl;
    
    tree->GetEntry(i);
    
    Int_t ndata = formula->GetNdata();
    if(ndata!=1) cout<<""<<endl;
    if (formula->EvalInstance(0)>0){ 
      //Store datasets
      *mass = fl_Bmass;
      *qsquare = fl_q2;
      *emu = fl_Emu;
      *mmsq = fl_MM2;
      //      cout<<"Q2?? "<<fl_q2<<endl;
      if(f_doTwoD) {
	if(f_useQsquare)
	  Ad->add(RooArgSet(*mass,*qsquare));
	if(f_useEmu)
	  Ad->add(RooArgSet(*mass,*emu));
      }
      else Ad->add(RooArgSet(*mass));

      if(f_doTwoD) {
	if(f_useQsquare) 
	  AdH->add(RooArgSet(*mass,*qsquare));
	if(f_useEmu) 
	  AdH->add(RooArgSet(*mass,*emu));
      }
      else AdH->add(RooArgSet(*mass));
      //      Ad->add(RooArgSet(*mass,*qsquare,*emu,*mmsq));
    }
  }
  Ad->Print();
  AdH->Print("v");
  
  sprintf(pdfnm,"mydata");
  Ad->SetName(pdfnm);
  w->import(*Ad);
  
  sprintf(pdfnm,"mydataH");
  AdH->SetName(pdfnm);
  w->import(*AdH);
  
  // Construct binned clone of unbinned weighted dataset
  RooDataHist* binnedData = AdH;
  /*
  binnedData->SetName("binnedData") ;
  binnedData->Print("v") ;
  w->import(*binnedData);
  */

  /*********************************************/
  //     Fitting Parameters are defined
  /*********************************************/
  
  //Getting back in the good old place.
  f.cd();
  
  //    gRandom->SetSeed(3123);
  
  /*
    FIT
  */

  /*
  RooChi2Var *chi2;
  chi2 =  new RooChi2Var("chi2","chi2",*pdf_fit,*binnedData,Extended(kTRUE),DataError(RooAbsData::SumW2)) ;
  */


  pdf_fit->printCompactTree("v");

  RooArgList  terms;
  char name[200];
  RooRealVar* brMean  = new RooRealVar("brMean","mean ",0.942);
  RooRealVar* brSigma = new RooRealVar("brSigma","sigma ",0.007);
  // Prior paramter definition 
  sprintf(name,"brPrior");
  RooFormulaVar * brPrior = new RooFormulaVar(name,"prior",
					      "0.5*(@0-@1)**2/@2**2",
					      RooArgList(*BR_dsgam,*brMean,*brSigma));
  
  if(f_addCon)  terms.add(*brPrior);

  //Ds0: (Ds0mu+Ds0tau)*0.9=12285
  RooRealVar* ds0Mean  = new RooRealVar("ds0Mean","mean ",1.2285e+04);//2.46470e+04);
  //30%  
  RooRealVar* ds0Sigma = new RooRealVar("ds0Sigma","sigma ",3.6855e+03);//2.441970e+03);
  //10%  
  //  RooRealVar* ds0Sigma = new RooRealVar("ds0Sigma","sigma ",1.2285e+03);//2.441970e+03);
  //1%
  //  RooRealVar* ds0Sigma = new RooRealVar("ds0Sigma","sigma ",0.24647e+03);

  // Prior paramter definition 
  sprintf(name,"ds0Prior");
  RooFormulaVar * ds0Prior = new RooFormulaVar(name,"prior",
					      "0.5*(@0-@1)**2/@2**2",
					      RooArgList(*Ds0StaConstr,*ds0Mean,*ds0Sigma));
  
  if(f_addCon)  terms.add(*ds0Prior);


  //Ds*: (Ds*mu+Ds*tau)*0.942=80277
  RooRealVar* dssMean  = new RooRealVar("dssMean","mean ",8.0277e+04);//1.60233e+05);
  //10%
  RooRealVar* dssSigma = new RooRealVar("dssSigma","sigma ",8.0277e+03);//1.60233e+04);
  //5%
  //  RooRealVar* dssSigma = new RooRealVar("dssSigma","sigma ",4.01e+03);//1.60233e+04);
  //1 %
  //  RooRealVar* dssSigma = new RooRealVar("dssSigma","sigma ",0.160233e+04);
  // Prior paramter definition 
  sprintf(name,"dssPrior");
  RooFormulaVar * dssPrior = new RooFormulaVar(name,"prior",
					      "0.5*(@0-@1)**2/@2**2",
					      RooArgList(*DsStaConstr,*dssMean,*dssSigma));
  
  if(f_addCon)  terms.add(*dssPrior);

  //RooRealVar* RdsCMean  = new RooRealVar("RdsCMean","mean ",34.3);
  //10%
  //RooRealVar* RdsCSigma = new RooRealVar("RdsCSigma","sigma ",3.43);
  //  RooRealVar* RdsCSigma = new RooRealVar("RdsCSigma","sigma ",1.7);
  //0.1 %
  //  RooRealVar* RdsCSigma = new RooRealVar("RdsCSigma","sigma ",0.0343);
  // Prior paramter definition 
  //sprintf(name,"RdsCPrior");
  //RooFormulaVar * RdsCPrior = new RooFormulaVar(name,"prior",
	//				      "0.5*(@0-@1)**2/@2**2",
	//				      RooArgList(*RDsConstr,*RdsCMean,*RdsCSigma));
  
  //  terms.add(*RdsCPrior);


  RooGaussian *br_con = new RooGaussian("br_con","BR constraint",*BR_dsgam,RooConst(0.942),RooConst(0.007));

  RooGaussian *ds0_con = new RooGaussian("ds0_con","Ds*0 constraint",*Ds0StaConstr,RooConst(1.2285e+04),RooConst(1.2285e+03));

  RooGaussian *dss_con = new RooGaussian("dss_con","Ds* constraint",*DsStaConstr,RooConst(8.0277e+04),RooConst(8.0277e+03));

  RooArgSet fit_constr(*br_con,*ds0_con,*dss_con); // external Gaussian constraints

  RooNLLVar *chi2;
  chi2 =  new RooNLLVar("chi2","chi2",*pdf_fit,*binnedData,Extended(kTRUE),DataError(RooAbsData::SumW2)) ;
  terms.add(*chi2);


  string mysum = "@0";
  if(f_addCon) mysum = "@0 + @1 + @2 + @3";
  //  if(f_addCon) mysum = "@0 + @1 + @2 + @3 + @4";
  RooFormulaVar * L = new RooFormulaVar("L",mysum.data(),terms);

  RooFitResult * res;
  m1 = new RooMinuit(*L);
  m1->setErrorLevel(0.5);
  m1->setVerbose(kTRUE) ;    
  m1->setLogFile("output/FitLog.txt");  
  m1->setProfile(1);
  m1->setPrintLevel(3);    m1->setStrategy(2);
  res = m1->save();
  res->Print("v") ; 
  m1->migrad() ;
  m1->minos() ;

  res = m1->save();


  /*
  if(f_addCon) 
    res = pdf_fit->fitTo(*binnedData,ExternalConstraints(RooArgSet(*br_con,*ds0_con,*dss_con)),Extended(kTRUE),Minos(kTRUE),Strategy(2),DataError(RooAbsData::SumW2),Save(),Verbose(kTRUE));
  else 
    res = pdf_fit->fitTo(*binnedData,Extended(kTRUE),Minos(kTRUE),Strategy(2),DataError(RooAbsData::SumW2),Save(),Verbose(kTRUE));
  */
  
  RooArgList myVals  = res->floatParsFinal(); 
  
  res->Print("v") ; 
  res->Print() ; 
  
  
  // Extract covariance and correlation matrix as TMatrixDSym
  const TMatrixDSym& cor = res->correlationMatrix() ;
  const TMatrixDSym& cov = res->covarianceMatrix() ;
  
  // Print correlation, covariance matrix
  cout << "correlation matrix" << endl ;
  cor.Print() ;
  cout << "covariance matrix" << endl ;
  cov.Print() ;

  w->import(*pdf_fit);
  
  
  if(res) res->Write();

  MyPlot(mass, binnedData, pdf_fit,0);
  
  if(f_doTwoD) {
    if(f_useQsquare)
      MyPlot(qsquare, binnedData, pdf_fit,1);
    if(f_useEmu)
      MyPlot(emu, binnedData, pdf_fit,2);
  }

  f.Close();

  sprintf(hn,"output/RootOutp_FitResult_%s.root",f_flag.data());   
  w->writeToFile(hn,kFALSE) ;

  return;
}


void FitTools::MyPlot(RooRealVar *myma, RooDataHist *adt, RooAbsPdf *apdf, int idx) {

  RooPlot *rpb; char hn[200];

  TLatex *lhcbLatex;
  lhcbLatex = new TLatex(0.18, 0.83,"#splitline{LHCb}{Preliminary}");
  TCanvas *c_4 = new TCanvas("c_4","");

  cout<<" IDX:: "<<idx<<endl;

  c_4->Clear(); c_4->cd(); 
  //  gPad->SetLogy();
  rpb = mass->frame(f_fit_range_min,f_fit_range_max,20);
  if(f_doTwoD && idx == 1) rpb = myma->frame(-5000000,11500000,20);
  if(f_doTwoD && idx == 2) rpb = myma->frame(200,3600,20);

  gPad->SetLeftMargin(0.14);
  gPad->SetBottomMargin(0.14);
  gPad->SetRightMargin(0.05);
  gPad->SetTopMargin(0.05);
  rpb->SetTitle("");
  rpb->SetTitleSize(0.06,"x");
  rpb->SetTitleSize(0.06,"y");
  adt->plotOn(rpb,Name("binnedData"));

  if(f_applyRange) {
    apdf->plotOn(rpb,Name("fitPdf"),Range(f_range.data()));
    apdf->plotOn(rpb,"",Components("*Bs0DsMu*"), "", LineColor(2),LineStyle(kDashed),Range(f_range.data()));
    apdf->plotOn(rpb,"",Components("*Bs0DstaMu*"), "", LineColor(6),LineStyle(2),Range(f_range.data()));
    apdf->plotOn(rpb,"",Components("*Bs0Ds0staMu*"), "", LineColor(kGreen+1),LineStyle(4),Range(f_range.data()));
    if(!f_sigOnly)  apdf->plotOn(rpb,"",Components("*DoubleCharm*"), "", LineColor(kOrange+1),LineStyle(4),Range(f_range.data()));

  } else {
    apdf->plotOn(rpb,Name("fitPdf"));
    apdf->plotOn(rpb,"",Components("*Bs0DsMu*"), "", LineColor(2),LineStyle(kDashed));
    apdf->plotOn(rpb,"",Components("*Bs0DstaMu*"), "", LineColor(6),LineStyle(2));
    apdf->plotOn(rpb,"",Components("*Bs0Ds0staMu*"), "", LineColor(kGreen+1),LineStyle(4));
    if(!f_sigOnly)    apdf->plotOn(rpb,"",Components("*DoubleCharm*"), "", LineColor(kOrange+1),LineStyle(4));
  }


  lhcbLatex->SetNDC(kTRUE);
  //  lhcbLatex->SetTextFont(lhcbFont);
  lhcbLatex->SetTextColor(1);
  lhcbLatex->SetTextSize(0.06);
  lhcbLatex->DrawLatex(0.18, 0.83,"#splitline{LHCb}{Preliminary}");
  //  rpb->addObject(lhcbLatex);
  rpb->SetMinimum(0.00001);
  sprintf(hn,"FitResult_%s",f_flag.data());   
  rpb->SetName(hn);
  rpb->Draw();
  rpb->Write();
  
  sprintf(hn,"output/FitResultMass_%s.pdf",f_flag.data());   
  if(idx == 1)   sprintf(hn,"output/FitResultQ2_%s.pdf",f_flag.data());   
  if(idx == 2)   sprintf(hn,"output/FitResultEmu_%s.pdf",f_flag.data());   
  cout<<"Going to create::  "<<hn<<endl;
  c_4->Print(hn);

}


void FitTools::configure(string range, bool arange, string confF) {

  RooNumIntConfig &conf=RooNumIntConfig::defaultConfig();
  conf.method1D().setLabel("RooAdaptiveGaussKronrodIntegrator1D");
  RooAbsReal::defaultIntegratorConfig()->setEpsAbs(1e-8) ;
  RooAbsReal::defaultIntegratorConfig()->setEpsRel(1e-8) ;
  RooAbsReal::defaultIntegratorConfig()->Print("v");

  f_range = range;
  f_applyRange = arange;

  if(!strcmp(range.data(),"right")) {

    //    f_fit_range_max = 6250;
    f_drawbins = 10;
    cout<<" Disabling the Misid and Excl, fitting right only up to: "<<f_fit_range_max<<endl;
  }


  //Read configuration file
  f_applyTauCut   =  ReadValFromFile(confF,"applyTauCut");
  f_applyIsoCut   =  ReadValFromFile(confF,"applyIsoCut");
  f_applyBMCut   =  ReadValFromFile(confF,"applyBMCut");
  f_useTauPdfs   =  ReadValFromFile(confF,"useTauPdfs");
  f_useQsquare   =  ReadValFromFile(confF,"useQsquare");
  f_useEmu   =  ReadValFromFile(confF,"useEmu");
  f_addDs1p =  ReadValFromFile(confF,"includeDs1p");
  f_hbins   =  ReadValFromFile(confF,"nBinsMass");
  f_qbins   =  ReadValFromFile(confF,"nBinsQsq");
  f_ebins   =  ReadValFromFile(confF,"nBinsEmu");
  f_mbins   =  ReadValFromFile(confF,"nBinsMMsq");
  f_doPhiPi =  ReadValFromFile(confF,"doPhiPi");

  mass = new RooRealVar("m_{D_{s}#mu}","B_s corr mass",f_fit_range_min,f_fit_range_max,"MeV/c^{2}");
  mass->setBins(f_hbins,"fewb");
  qsquare = new RooRealVar("q^{2}","q^{2}",-5000000,11500000,"MeV^{2}/c^{4}");
  qsquare->setBins(f_qbins,"fewb");
  mmsq = new RooRealVar("mm^2","m_{miss}^{2}",-20000000,20000000,"MeV/c^{2}");
  mmsq->setBins(f_mbins,"fewb");
  emu = new RooRealVar("E_{#mu}","E_{#mu}^{*}",200,3600,"MeV/c^{2}");
  emu->setBins(f_ebins,"fewb");

  return;
}

void FitTools::loadPDFs(string conf="") {

  char name[200];

  TFile *f;
  RooWorkspace *w;
  f_confFl = conf;

  f_flag += f_confFl;

  f_my_pdfs = new RooArgSet("my_pdfs");
  f_my_yields = new RooArgSet("my_yields");

  sprintf(name,"input/RootOutp_MCAll_%s%s.root",conf.data(),"Signal_Bs0DsMu");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");
  if(f_debug) w->Print();
  sprintf(name,"histPdf_%s%s",conf.data(),"Signal_Bs0DsMu");
  if(f_doTwoD) {
    if(f_useQsquare)
      sprintf(name,"histPdf_BQ_%s%s",conf.data(),"Signal_Bs0DsMu");
    if(f_useEmu)
      sprintf(name,"histPdf_BE_%s%s",conf.data(),"Signal_Bs0DsMu");
  }
  f_sig_pdf = w->pdf(name);

  

  f_my_pdfs->add(*f_sig_pdf);

  RooRealVar *dsmu_yield = new RooRealVar("dsmu_yield","Yield of signal events",1.0056e+04,1.e+04,1.e+06);
  f_my_yields->add(*dsmu_yield);

  sprintf(name,"input/RootOutp_MCAll_%s%s.root",conf.data(),"Signal_Bs0DstaMu");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");

  sprintf(name,"histPdf_%s%s",conf.data(),"Signal_Bs0DstaMu");
  if(f_doTwoD) {
    if(f_useQsquare)
      sprintf(name,"histPdf_BQ_%s%s",conf.data(),"Signal_Bs0DstaMu");
    if(f_useEmu)
      sprintf(name,"histPdf_BE_%s%s",conf.data(),"Signal_Bs0DstaMu");
  }
  f_dsta_pdf = w->pdf(name);
  f_my_pdfs->add(*f_dsta_pdf);

  RooRealVar *dsta_yield = new RooRealVar("bsdsta_yield","Yield of bsdsta events",5.0022e+04,1.e+03,1.e+07);
  f_my_yields->add(*dsta_yield);


  sprintf(name,"input/RootOutp_MCAll_%s%s.root",conf.data(),"Signal_Bs0Ds0staMu");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");

  sprintf(name,"histPdf_%s%s",conf.data(),"Signal_Bs0Ds0staMu");
  if(f_doTwoD) {
    if(f_useQsquare) 
      sprintf(name,"histPdf_BQ_%s%s",conf.data(),"Signal_Bs0Ds0staMu");
    if(f_useEmu) 
      sprintf(name,"histPdf_BE_%s%s",conf.data(),"Signal_Bs0Ds0staMu");
  }
  f_ds0sta_pdf = w->pdf(name);
  f_my_pdfs->add(*f_ds0sta_pdf);

  RooRealVar *ds0sta_yield = new RooRealVar("bsds0sta_yield","Yield of bsds0sta events",13000.0,1.,1.e+06);
  f_my_yields->add(*ds0sta_yield);


  if(f_addDs1p) {

    sprintf(name,"input/RootOutp_MCAll_%s%s.root",conf.data(),"Signal_Bs0D1pMu");
    f = new TFile(name,"READ");
    w = (RooWorkspace*) f->Get("w");
    
    sprintf(name,"histPdf_%s%s",conf.data(),"Signal_Bs0D1pMu");
    if(f_doTwoD) {
      if(f_useQsquare)
	sprintf(name,"histPdf_BQ_%s%s",conf.data(),"Signal_Bs0D1pMu");
      if(f_useEmu)
	sprintf(name,"histPdf_BE_%s%s",conf.data(),"Signal_Bs0D1pMu");
    }
    f_ds1pmu_pdf = w->pdf(name);
    f_my_pdfs->add(*f_ds1pmu_pdf);
    
    RooRealVar *ds1pmu_yield = new RooRealVar("bsds1pmu_yield","Yield of bsds1pmu events",1.0023e+03,1.e+01,1.e+04);
    f_my_yields->add(*ds1pmu_yield);
    
  }

  /*
    Tau signal
  */
  sprintf(name,"input/RootOutp_MCAll_Tau%s%s.root",conf.data(),"Signal_Bs0DsTau");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");
  if(f_debug) w->Print();
  sprintf(name,"histPdf_Tau%s%s",conf.data(),"Signal_Bs0DsTau");
  if(f_doTwoD) {
    if(f_useQsquare)
      sprintf(name,"histPdf_BQ_Tau%s%s",conf.data(),"Signal_Bs0DsTau");
    if(f_useEmu)
      sprintf(name,"histPdf_BE_Tau%s%s",conf.data(),"Signal_Bs0DsTau");
  }
  f_dstau_pdf = w->pdf(name);
  if(f_useTauPdfs)  f_my_pdfs->add(*f_dstau_pdf);

  RooRealVar *dstau_yield = new RooRealVar("dstau_yield","Yield of signal events",1000,0,100000000);
  if(f_useTauPdfs)  f_my_yields->add(*dstau_yield);

  sprintf(name,"input/RootOutp_MCAll_Tau%s%s.root",conf.data(),"Signal_Bs0DstaTau");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");

  sprintf(name,"histPdf_Tau%s%s",conf.data(),"Signal_Bs0DstaTau");
  if(f_doTwoD) {
    if(f_useQsquare) 
      sprintf(name,"histPdf_BQ_Tau%s%s",conf.data(),"Signal_Bs0DstaTau");
    if(f_useEmu) 
      sprintf(name,"histPdf_BE_Tau%s%s",conf.data(),"Signal_Bs0DstaTau");
  }
  f_dstatau_pdf = w->pdf(name);
  if(f_useTauPdfs)  f_my_pdfs->add(*f_dstatau_pdf);

  RooRealVar *dstatau_yield = new RooRealVar("bsdstatau_yield","Yield of bsdsta events",2000,10,100000000);
  if(f_useTauPdfs)  f_my_yields->add(*dstatau_yield);


  sprintf(name,"input/RootOutp_MCAll_Tau%s%s.root",conf.data(),"Signal_Bs0Ds0staTau");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");

  sprintf(name,"histPdf_Tau%s%s",conf.data(),"Signal_Bs0Ds0staTau");
  if(f_doTwoD) {
    if(f_useQsquare) 
      sprintf(name,"histPdf_BQ_Tau%s%s",conf.data(),"Signal_Bs0Ds0staTau");
    if(f_useEmu) 
      sprintf(name,"histPdf_BE_Tau%s%s",conf.data(),"Signal_Bs0Ds0staTau");
  }
  f_ds0statau_pdf = w->pdf(name);
  if(f_useTauPdfs)  f_my_pdfs->add(*f_ds0statau_pdf);

  RooRealVar *ds0statau_yield = new RooRealVar("bsds0statau_yield","Yield of bsds0sta events",400,0,100000000);
  if(f_useTauPdfs)  f_my_yields->add(*ds0statau_yield);
  

  if(f_addDs1p) {
    sprintf(name,"input/RootOutp_MCAll_Tau%s%s.root",conf.data(),"Signal_Bs0Ds1pTau");
    f = new TFile(name,"READ");
    w = (RooWorkspace*) f->Get("w");
    w->Print();
    
    sprintf(name,"histPdf_Tau%s%s",conf.data(),"Signal_Bs0Ds1pTau");
    if(f_doTwoD) {
      if(f_useQsquare) 
	sprintf(name,"histPdf_BQ_Tau%s%s",conf.data(),"Signal_Bs0Ds1pTau");
      if(f_useEmu) 
	sprintf(name,"histPdf_BE_Tau%s%s",conf.data(),"Signal_Bs0Ds1pTau");
    }
    f_ds1ptau_pdf = w->pdf(name);
    if(f_useTauPdfs)      f_my_pdfs->add(*f_ds1ptau_pdf);
    
    RooRealVar *ds1ptau_yield = new RooRealVar("bsds1ptau_yield","Yield of bsds1ptau events",1.0023e+03,1.e-01,1.e+04);
    if(f_useTauPdfs)      f_my_yields->add(*ds1ptau_yield);
    
  }


  BR_dspi = new RooRealVar("BR_dspi","BR of Dspi decay",0.9,0,1);
  //  BR_dspi->setConstant(kTRUE);
  BR_dsgam = new RooRealVar("BR_dsgam","BR of Dspi decay",0.942,0,1); //0.007

  Ds0StaConstr = new RooFormulaVar("Ds0StaConstr","Constraint on fitted Ds0Sta rad","(@0+@1)*@2",RooArgList(*ds0sta_yield,*ds0statau_yield,*BR_dspi));

  DsStaConstr = new RooFormulaVar("DsStaConstr","Constraint on fitted DsSta rad","(@0+@1)*@2",RooArgList(*dsta_yield,*dstatau_yield,*BR_dsgam));

  RDsConstr = new RooFormulaVar("RDsConstr","Constraint on fitted BR rat","(@0/@1)",RooArgList(*dsta_yield,*dstatau_yield));

  /*
    Double Charm
  */

  sprintf(name,"input/RootOutp_MCAll_%s%s.root",conf.data(),"DoubleCharm");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");

  RooRealVar *dcharm_yield = new RooRealVar("dcharm_yield","Yield of bsds0sta events",1000,0,100000000);

  /*
    Lambda_b    0.47    0.084
    Bs_DsDs      0.71    0.127
    Bd_DstDS     1.89   0.339
    BuD0Ds        2.52    0.450
  */

  //Try to build an "ad hoc" PDF, with fixed ratios.
  RooArgSet *f_my_ddclist = new RooArgSet("my_ddclist");
  RooArgSet *f_my_ddfrac = new RooArgSet("my_ddfrac");

  sprintf(name,"input/RootOutp_MCAll_%s%s.root",conf.data(),"LbLcDs");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");
  sprintf(name,"histPdf_%s%s",conf.data(),"LbLcDs");
  if(f_doTwoD) {
    if(f_useQsquare) 
      sprintf(name,"histPdf_BQ_%s%s",conf.data(),"LbLcDs");
    if(f_useEmu) 
      sprintf(name,"histPdf_BE_%s%s",conf.data(),"LbLcDs");
  }
  f_LbLcDs_pdf = w->pdf(name);
  RooRealVar *LbLcDs_frac = new RooRealVar("LbLcDs_frac","Frac of LbLcDs events",0.084,0,1);
  LbLcDs_frac->setConstant(kTRUE);
  f_my_ddclist->add(*f_LbLcDs_pdf);
  f_my_ddfrac->add(*LbLcDs_frac);

  sprintf(name,"input/RootOutp_MCAll_%s%s.root",conf.data(),"BsDsDs");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");
  sprintf(name,"histPdf_%s%s",conf.data(),"BsDsDs");
  if(f_doTwoD) {
    if(f_useQsquare) 
      sprintf(name,"histPdf_BQ_%s%s",conf.data(),"BsDsDs");
    if(f_useEmu) 
      sprintf(name,"histPdf_BE_%s%s",conf.data(),"BsDsDs");
  }
  f_BsDsDs_pdf = w->pdf(name);
  RooRealVar *BsDsDs_frac = new RooRealVar("BsDsDs_frac","Frac of BsDsDs events",0.127,0,1);
  BsDsDs_frac->setConstant(kTRUE);
  f_my_ddclist->add(*f_BsDsDs_pdf);
  f_my_ddfrac->add(*BsDsDs_frac);

  sprintf(name,"input/RootOutp_MCAll_%s%s.root",conf.data(),"BdDstDs");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");
  sprintf(name,"histPdf_%s%s",conf.data(),"BdDstDs");
  if(f_doTwoD) {
    if(f_useQsquare) 
      sprintf(name,"histPdf_BQ_%s%s",conf.data(),"BdDstDs");
    if(f_useEmu) 
      sprintf(name,"histPdf_BE_%s%s",conf.data(),"BdDstDs");
  }
  f_BdDstDs_pdf = w->pdf(name);
  RooRealVar *BdDstDs_frac = new RooRealVar("BdDstDs_frac","Frac of BdDstDs events",0.339,0,1);
  BdDstDs_frac->setConstant(kTRUE);
  f_my_ddclist->add(*f_BdDstDs_pdf);
  f_my_ddfrac->add(*BdDstDs_frac);

  sprintf(name,"input/RootOutp_MCAll_%s%s.root",conf.data(),"BuD0Ds");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");
  sprintf(name,"histPdf_%s%s",conf.data(),"BuD0Ds");
  if(f_doTwoD) {
    if(f_useQsquare) 
      sprintf(name,"histPdf_BQ_%s%s",conf.data(),"BuD0Ds");
    if(f_useEmu) 
      sprintf(name,"histPdf_BE_%s%s",conf.data(),"BuD0Ds");
  }
  f_BuD0Ds_pdf = w->pdf(name);
  RooRealVar *BuD0Ds_frac = new RooRealVar("BuD0Ds_frac","Frac of BuD0Ds events",0.450,0,1);
  BuD0Ds_frac->setConstant(kTRUE);
  f_my_ddclist->add(*f_BuD0Ds_pdf);
  f_my_ddfrac->add(*BuD0Ds_frac);

  f_dcharm_pdf = new RooAddPdf("AdHocDoubleCharm","",RooArgSet(*f_my_ddclist),RooArgSet(*f_my_ddfrac));
  if(!f_sigOnly)  f_my_pdfs->add(*f_dcharm_pdf);

  if(!f_sigOnly)  f_my_yields->add(*dcharm_yield);
  
  /*
    An additional tau bkg component can be foreseen
    But we fix the contribution to some fract of the DD
  */

  sprintf(name,"input/RootOutp_MCAll_Tau%s%s.root",conf.data(),"Signal_Bs0DsTau");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");
  gDirectory->ls();  
  w->Print();
  sprintf(name,"histPdf_Tau%s%s",conf.data(),"Signal_Bs0DsTau");
  if(f_doTwoD)  {
    if(f_useQsquare) 
      sprintf(name,"histPdf_BQ_Tau%s%s",conf.data(),"Signal_Bs0DsTau");
    if(f_useEmu) 
      sprintf(name,"histPdf_BE_Tau%s%s",conf.data(),"Signal_Bs0DsTau");
  }
  f_taubkg_pdf = w->pdf(name);
  //  sprintf(name,"histPdf_Tau%s%s",conf.data(),"Signal_Bs0DsTau");
  f_taubkg_pdf->SetName(name);
  if(!f_sigOnly)  f_my_pdfs->add(*f_taubkg_pdf);
  
  RooRealVar *taubkg_yield = new RooRealVar("dstaubkg_yield","Yield of bsds0sta events",1000.,0.,100000.);
  //  taubkg_frac->setConstant(kTRUE);
  //  RooFormulaVar * taubkg_yield = new RooFormulaVar("taubkg_yield","taubkg fr","@0*@1",RooArgList(*dcharm_yield,*taubkg_frac));
  
  if(!f_sigOnly)  f_my_yields->add(*taubkg_yield);

  /*
    Combinatorial Background
  */

  sprintf(name,"input/RootOutp_MCAll_%s%s.root",conf.data(),"SideBands");
  if(f_doSameSign)
    sprintf(name,"input/RootOutp_MCAll_%s%s.root",conf.data(),"SameSide");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");
  w->Print();
  if(f_doTwoD)  {
    if(f_useQsquare)  {
      sprintf(name,"histPdf_BQ_%s%s",conf.data(),"SideBands");
      if(f_doSameSign)
	sprintf(name,"histPdf_BQ_%s%s",conf.data(),"SameSide");
    }
    if(f_useEmu)  {
      sprintf(name,"histPdf_BE_%s%s",conf.data(),"SideBands");
      if(f_doSameSign)
	sprintf(name,"histPdf_BE_%s%s",conf.data(),"SameSide");
    }
  }

  f_sideb_pdf = w->pdf(name);
  if(!f_sigOnly)  f_my_pdfs->add(*f_sideb_pdf);
  
  RooRealVar *sideb_yield = new RooRealVar("sideb_yield","Yield of bsds0sta events",100,0,100000000);
  if(!f_sigOnly)  f_my_yields->add(*sideb_yield);

  /*
  sprintf(name,"input/RootOutp_MCAll_%s%s.root",conf.data(),"DsTrueComb");
  f = new TFile(name,"READ");
  w = (RooWorkspace*) f->Get("w");
  w->Print();
  sprintf(name,"histPdf_%s%s",conf.data(),"DsTrueComb");
  f_dstrcom_pdf = w->pdf(name);
  //  f_my_pdfs->add(*f_dstrcom_pdf);

  RooRealVar *dstrcom_yield = new RooRealVar("dstrcom_yield","Yield of bsds0sta events",100,0,100000000);
  //  f_my_yields->add(*dstrcom_yield);

  */
  return;

}

void FitTools::doMCmat() {
  f_doMCmat = kTRUE;
  return;
}

void FitTools::doTau() {
  f_doTau = kTRUE;
  return;
}


void FitTools::doTwoD() {
  f_doTwoD = kTRUE;
  return;
}

void FitTools::doSameSign() {
  f_doSameSign = kTRUE;
  return;
}


vector<double> FitTools::ReadVecFromFile(string filen, vector<string> parnames) {

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

double FitTools::ReadValFromFile(string filen, string parname) {

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

