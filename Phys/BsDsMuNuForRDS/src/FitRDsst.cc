#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
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
#include "RooHist.h"

#include <iomanip>
#include <iostream>
#include <time.h>
#include <string>

using namespace RooFit;

void FitRDsst(){

  TFile *f = new TFile("DsMass_WithSWeighted_Dsst_CB.root","READ");
  TTree *t = (TTree*) f->Get("DecayTree");

  TH1F *histQ2 = new TH1F("Q2", "Q2", 30, -5000000, 11500000);  
  TH1F *histEmu = new TH1F("Emu", "Emu", 30, 200, 3600);
  TH1F *histMCORR = new TH1F("MCORR", "MCORR", 80, 3000, 8000);
  TH2F *histMQ = new TH2F("MQ", "MQ", 80, 3000, 8000, 30, -5000000, 11500000);
  TH2F *histME = new TH2F("ME", "ME", 80, 3000, 8000, 30, 200, 3600);
  TH3F *histMQE = new TH3F("MQE", "MQE", 40, 3000, 8000, 10, -5000000, 11500000, 10, 200, 3600);
  int entries = t->GetEntries();
  std::cout << "DEBUG: nEntries = " << entries << std::endl;

  Double_t q2, Emu, Bs_0_MCORR, sigw;
  TBranch *b_q2, *b_Emu, *b_Bs_0_MCORR, *b_sigw; 

  t->SetBranchAddress("q2", &q2, &b_q2);
  t->SetBranchAddress("Emu", &Emu, &b_Emu);
  t->SetBranchAddress("Bs_0_MCORR", &Bs_0_MCORR, &b_Bs_0_MCORR);
  t->SetBranchAddress("sigw", &sigw, &b_sigw);

  for(int i=0; i<=entries; ++i){
    t->GetEntry(i);
    histQ2->Fill(q2,sigw);
    histEmu->Fill(Emu,sigw);
    histMCORR->Fill(Bs_0_MCORR,sigw);
    histMQ->Fill(Bs_0_MCORR,q2,sigw);
    histME->Fill(Bs_0_MCORR,Emu,sigw);
    histMQE->Fill(Bs_0_MCORR,q2,Emu,sigw);
  }

  RooArgSet *f_mymcorr_pdfs = new RooArgSet("mymcorr_pdfs");
  RooArgSet *f_myq2_pdfs = new RooArgSet("myq2_pdfs");
  RooArgSet *f_myemu_pdfs = new RooArgSet("myemu_pdfs");
  RooArgSet *f_my3D_pdfs = new RooArgSet("my3D_pdfs");
  RooArgSet *f_my_yields = new RooArgSet("my_yields");

  // Mu
  TFile *fMu = new TFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/Templates/output/RootOutp_MCAll_NorBIsoPIDCutSignal_Bs0DstaMu.root","READ");
  std::cout << "Read Muon workspace" << std::endl;
  RooWorkspace *wMu = (RooWorkspace*) fMu->Get("w");
   
  RooRealVar *dsta_yield = new RooRealVar("bsdsta_yield","Yield of bsdsta events",5.0022e+04,1.e+03,1.e+07);
  f_my_yields->add(*dsta_yield);
  RooAbsPdf *mcorr_DstMu_pdf = wMu->pdf("histPdf_NorBIsoPIDCutSignal_Bs0DstaMu");
  f_mymcorr_pdfs->add(*mcorr_DstMu_pdf);
  RooAbsPdf *q2_DstMu_pdf = wMu->pdf("histPdf_BQ_NorBIsoPIDCutSignal_Bs0DstaMu");
  f_myq2_pdfs->add(*q2_DstMu_pdf);
  RooAbsPdf *emu_DstMu_pdf = wMu->pdf("histPdf_BE_NorBIsoPIDCutSignal_Bs0DstaMu");
  f_myemu_pdfs->add(*emu_DstMu_pdf);
  RooAbsPdf *q2emu_DstMu_pdf = wMu->pdf("histPdf_BQE_NorBIsoPIDCutSignal_Bs0DstaMu");
  f_my3D_pdfs->add(*q2emu_DstMu_pdf);
  std::cout << "DEBUG: loaded histograms for Mu" << std::endl;
    
  // Tau
  TFile *fTau = new TFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/Templates/output/RootOutp_MCAll_TauNorBIsoPIDCutSignal_Bs0DstaTau.root","READ");
  std::cout << "Read Tau workspace" << std::endl;
  RooWorkspace *wTau = (RooWorkspace*) fTau->Get("w");

  // This is to fit the yields separately
  RooRealVar *dstatau_yield = new RooRealVar("bsdstatau_yield","Yield of bsdsta events",2000,10,100000000);
  //f_my_yields->add(*dstatau_yield);
  
  // This is to fit R(Ds*) directly
  RooRealVar *ratio = new RooRealVar("ratio", "ratio", 0.08, 0., 1.);
  RooFormulaVar *yield = new RooFormulaVar("yield", "yield and RDs", "@0*@1", RooArgList(*ratio, *dsta_yield));
  f_my_yields->add(*yield);
  RooAbsPdf *mcorr_DstTau_pdf = wTau->pdf("histPdf_TauNorBIsoPIDCutSignal_Bs0DstaTau");
  f_mymcorr_pdfs->add(*mcorr_DstTau_pdf);
  RooAbsPdf *q2_DstTau_pdf = wTau->pdf("histPdf_BQ_TauNorBIsoPIDCutSignal_Bs0DstaTau");
  f_myq2_pdfs->add(*q2_DstTau_pdf);
  RooAbsPdf *emu_DstTau_pdf = wTau->pdf("histPdf_BE_TauNorBIsoPIDCutSignal_Bs0DstaTau");
  f_myemu_pdfs->add(*emu_DstTau_pdf); 
  RooAbsPdf *q2emu_DstTau_pdf = wTau->pdf("histPdf_BQE_TauNorBIsoPIDCutSignal_Bs0DstaTau");
  f_my3D_pdfs->add(*q2emu_DstTau_pdf);
  std::cout << "DEBUG: loaded histograms for Tau" << std::endl;

  // SameSign
  TFile *fSS = new TFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/Templates/output/RootOutp_MCAll_NorBIsoPIDCut_SameSign.root","READ");
  std::cout << "Read SS workspace" << std::endl;
  RooWorkspace *wSS = (RooWorkspace*) fSS->Get("w");

  RooRealVar *SS_yield = new RooRealVar("SS_yield","Same Sign yield",1000,100,1000000);
  f_my_yields->add(*SS_yield);
  RooAbsPdf *mcorr_SS_pdf = wSS->pdf("histPdf_NorBIsoPIDCut_SameSign");
  f_mymcorr_pdfs->add(*mcorr_SS_pdf);
  RooAbsPdf *q2_SS_pdf = wSS->pdf("histPdf_BQ_NorBIsoPIDCut_SameSign");
  f_myq2_pdfs->add(*q2_SS_pdf);
  RooAbsPdf *emu_SS_pdf = wSS->pdf("histPdf_BE_NorBIsoPIDCut_SameSign");
  f_myemu_pdfs->add(*emu_SS_pdf);
  RooAbsPdf *q2emu_SS_pdf = wSS->pdf("histPdf_BQE_NorBIsoPIDCut_SameSign");
  f_my3D_pdfs->add(*q2emu_SS_pdf);
  std::cout << "DEBUG: loaded histograms for SameSign" << std::endl;

  // Double Charm
  //Try to build an "ad hoc" PDF, with fixed ratios.
  RooArgSet *f_my_ddmcorrlist = new RooArgSet("my_ddmcorrlist");
  RooArgSet *f_my_ddq2list = new RooArgSet("my_ddq2list");
  RooArgSet *f_my_ddemulist = new RooArgSet("my_ddemulist");
  RooArgSet *f_my_ddq2emulist = new RooArgSet("my_ddq2emulist");
  RooArgSet *f_my_ddfrac = new RooArgSet("my_ddfrac");

  // LbLcDs  
  TFile *fLb = new TFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/Templates/output/RootOutp_MCAll_NorBIsoPIDCutLbLcDs.root","READ");
  std::cout << "Read LbLcDs workspace" << std::endl;
  RooWorkspace *wLb = (RooWorkspace*) fLb->Get("w");

  RooRealVar *LbLcDs_frac = new RooRealVar("LbLcDs_frac","Frac of LbLcDs events",0.084,0,1);
  LbLcDs_frac->setConstant(kTRUE);
  f_my_ddfrac->add(*LbLcDs_frac);
  RooAbsPdf *mcorr_Lb_pdf = wLb->pdf("histPdf_NorBIsoPIDCutLbLcDs");
  f_my_ddmcorrlist->add(*mcorr_Lb_pdf);
  RooAbsPdf *q2_Lb_pdf = wLb->pdf("histPdf_BQ_NorBIsoPIDCutLbLcDs");
  f_my_ddq2list->add(*q2_Lb_pdf);
  RooAbsPdf *emu_Lb_pdf = wLb->pdf("histPdf_BE_NorBIsoPIDCutLbLcDs");
  f_my_ddemulist->add(*emu_Lb_pdf);
  RooAbsPdf *q2emu_Lb_pdf = wLb->pdf("histPdf_BQE_NorBIsoPIDCutLbLcDs");
  f_my_ddq2emulist->add(*q2emu_Lb_pdf);
  std::cout << "DEBUG: loaded histograms for LbLcDs" << std::endl;

  // DsDs
  TFile *fDs = new TFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/Templates/output/RootOutp_MCAll_NorBIsoPIDCutBsDsDs.root","READ");
  std::cout << "Read BdDsDs workspace" << std::endl;
  RooWorkspace *wDs = (RooWorkspace*) fDs->Get("w");

  RooRealVar *BsDsDs_frac = new RooRealVar("BsDsDs_frac","Frac of BsDsDs events",0.127,0,1);
  BsDsDs_frac->setConstant(kTRUE);
  f_my_ddfrac->add(*BsDsDs_frac);
  RooAbsPdf *mcorr_Ds_pdf = wDs->pdf("histPdf_NorBIsoPIDCutBsDsDs");
  f_my_ddmcorrlist->add(*mcorr_Ds_pdf);
  RooAbsPdf *q2_Ds_pdf = wDs->pdf("histPdf_BQ_NorBIsoPIDCutBsDsDs");
  f_my_ddq2list->add(*q2_Ds_pdf);
  RooAbsPdf *emu_Ds_pdf = wDs->pdf("histPdf_BE_NorBIsoPIDCutBsDsDs");
  f_my_ddemulist->add(*emu_Ds_pdf);
  RooAbsPdf *q2emu_Ds_pdf = wDs->pdf("histPdf_BQE_NorBIsoPIDCutBsDsDs");
  f_my_ddq2emulist->add(*q2emu_Ds_pdf); 
  std::cout << "DEBUG: loaded histograms for BsDsDs" << std::endl;
  
  // DstDs
  TFile *fDst = new TFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/Templates/output/RootOutp_MCAll_NorBIsoPIDCutBdDstDs.root","READ");
  std::cout << "Read BdDstDs workspace" << std::endl;
  RooWorkspace *wDst = (RooWorkspace*) fDst->Get("w");
  
  RooRealVar *BdDstDs_frac = new RooRealVar("BdDstDs_frac","Frac of BdDstDs events",0.339,0,1);
  BdDstDs_frac->setConstant(kTRUE);
  f_my_ddfrac->add(*BdDstDs_frac);
  RooAbsPdf *mcorr_Dst_pdf = wDst->pdf("histPdf_NorBIsoPIDCutBdDstDs");
  f_my_ddmcorrlist->add(*mcorr_Dst_pdf);
  RooAbsPdf *q2_Dst_pdf = wDst->pdf("histPdf_BQ_NorBIsoPIDCutBdDstDs");
  f_my_ddq2list->add(*q2_Dst_pdf);
  RooAbsPdf *emu_Dst_pdf = wDst->pdf("histPdf_BE_NorBIsoPIDCutBdDstDs");
  f_my_ddemulist->add(*emu_Dst_pdf); 
  RooAbsPdf *q2emu_Dst_pdf = wDst->pdf("histPdf_BQE_NorBIsoPIDCutBdDstDs");
  f_my_ddq2emulist->add(*q2emu_Dst_pdf);  
  std::cout << "DEBUG: loaded histograms for BdDstDs" << std::endl;
 
  // D0Ds
  TFile *fD0 = new TFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/Templates/output/RootOutp_MCAll_NorBIsoPIDCutBuD0Ds.root","READ");
  std::cout << "Read BuD0Ds workspace" << std::endl;
  RooWorkspace *wD0 = (RooWorkspace*) fD0->Get("w");
  
  RooRealVar *BuD0Ds_frac = new RooRealVar("BuD0Ds_frac","Frac of BuD0Ds events",0.450,0,1);
  BuD0Ds_frac->setConstant(kTRUE);
  f_my_ddfrac->add(*BuD0Ds_frac);
  RooAbsPdf *mcorr_D0_pdf = wD0->pdf("histPdf_NorBIsoPIDCutBuD0Ds");
  f_my_ddmcorrlist->add(*mcorr_D0_pdf);
  RooAbsPdf *q2_D0_pdf = wD0->pdf("histPdf_BQ_NorBIsoPIDCutBuD0Ds");
  f_my_ddq2list->add(*q2_D0_pdf);
  RooAbsPdf *emu_D0_pdf = wD0->pdf("histPdf_BE_NorBIsoPIDCutBuD0Ds");
  f_my_ddemulist->add(*emu_D0_pdf);
  RooAbsPdf *q2emu_D0_pdf = wD0->pdf("histPdf_BQE_NorBIsoPIDCutBuD0Ds");
  f_my_ddq2emulist->add(*q2emu_D0_pdf);
  std::cout << "DEBUG: loaded histograms for BuD0Ds" << std::endl;

  // add all the double charm pdfs and yields
  RooAddPdf *f_dcharmmcorr_pdf = new RooAddPdf("AdHocDoubleCharmMCorr","",RooArgSet(*f_my_ddmcorrlist),RooArgSet(*f_my_ddfrac));
  RooAddPdf *f_dcharmq2_pdf = new RooAddPdf("AdHocDoubleCharmQ2","",RooArgSet(*f_my_ddq2list),RooArgSet(*f_my_ddfrac));
  RooAddPdf *f_dcharmemu_pdf = new RooAddPdf("AdHocDoubleCharmEmu","",RooArgSet(*f_my_ddemulist),RooArgSet(*f_my_ddfrac));
  RooAddPdf *f_dcharmq2emu_pdf = new RooAddPdf("AdHocDoubleCharmQ2Emu","",RooArgSet(*f_my_ddq2emulist),RooArgSet(*f_my_ddfrac));

  RooRealVar *dcharm_yield = new RooRealVar("dcharm_yield","Yield of double charm events",1000,0,100000000);
  f_my_yields->add(*dcharm_yield);
  f_mymcorr_pdfs->add(*f_dcharmmcorr_pdf);
  f_myq2_pdfs->add(*f_dcharmq2_pdf);
  f_myemu_pdfs->add(*f_dcharmemu_pdf);
  f_my3D_pdfs->add(*f_dcharmq2emu_pdf); 

  // Add the pdfs
  RooAbsPdf *pdf_fit_q2, *pdf_fit_emu, *pdf_fit_mcorr, *pdf_fit_3D;
  pdf_fit_q2 = new RooAddPdf("pdf_fit_q2","",RooArgSet(*f_myq2_pdfs),RooArgSet(*f_my_yields));
  pdf_fit_emu = new RooAddPdf("pdf_fit_emu","",RooArgSet(*f_myemu_pdfs),RooArgSet(*f_my_yields));
  pdf_fit_mcorr = new RooAddPdf("pdf_fit_mcorr","",RooArgSet(*f_mymcorr_pdfs),RooArgSet(*f_my_yields));
  pdf_fit_3D = new RooAddPdf("pdf_fit_3D","",RooArgSet(*f_my3D_pdfs),RooArgSet(*f_my_yields));

  RooRealVar *qsquare = new RooRealVar("q^{2}","q^{2}",-5000000,11500000);
  RooRealVar *emu = new RooRealVar("E_{#mu}", "E_{#mu}", 200, 3600);
  RooRealVar *mass = new RooRealVar("m_{D_{s}#mu}", "B_s corr mass", 3000, 8000);
  RooDataHist *hMQ = new RooDataHist("hMQ", "hMQ", RooArgSet(*mass, *qsquare), histMQ, 1.0);
  RooDataHist *hME = new RooDataHist("hME", "hME", RooArgSet(*mass, *emu), histME, 1.0);
  RooDataHist *hMQE = new RooDataHist("hMQE", "hMQE", RooArgSet(*mass, *qsquare, *emu), histMQE, 1.0);

  // Fit 3D 
  RooFitResult *resMQE;
  resMQE = pdf_fit_3D->fitTo(*hMQE, Extended(true), SumW2Error(kTRUE), Minos(true), Strategy(2), Timer(kTRUE), NumCPU(4));

  // Project over MCORR
  RooPlot *frameM = mass->frame(3000,8000,40);
  hMQE->plotOn(frameM,MarkerStyle(8));
  pdf_fit_3D->plotOn(frameM,LineColor(kBlue),LineWidth(2));
  // Get pulls. Has to be done here, otherwise it gets the pulls from the DoubleCharm
  RooHist *hpull_M = frameM->pullHist();
  pdf_fit_3D->plotOn(frameM,LineColor(kGreen),Components("histPdf_BQE_TauNorBIsoPIDCutSignal_Bs0DstaTau"),LineWidth(2));
  pdf_fit_3D->plotOn(frameM,LineColor(kMagenta),Components("histPdf_BQE_NorBIsoPIDCutSignal_Bs0DstaMu"),LineWidth(2));
  pdf_fit_3D->plotOn(frameM,LineColor(kGray),Components("histPdf_BQE_NorBIsoPIDCut_SameSign"),LineWidth(2));
  pdf_fit_3D->plotOn(frameM,LineColor(kOrange),Components("AdHocDoubleCharmQ2Emu"),LineWidth(2));
  hpull_M->GetXaxis()->SetRangeUser(3000, 8000);
  hpull_M->GetYaxis()->SetRangeUser(-5, 5);

  // Project over Q2
  RooPlot *frameQ = qsquare->frame(-5000000,11500000,10);
  hMQE->plotOn(frameQ,MarkerStyle(8));
  pdf_fit_3D->plotOn(frameQ,LineColor(kBlue),LineWidth(2));
  // Get pulls. Has to be done here, otherwise it gets the pulls from the DoubleCharm
  RooHist *hpull_Q = frameQ->pullHist();
  pdf_fit_3D->plotOn(frameQ,LineColor(kGreen),Components("histPdf_BQE_TauNorBIsoPIDCutSignal_Bs0DstaTau"),LineWidth(2));
  pdf_fit_3D->plotOn(frameQ,LineColor(kMagenta),Components("histPdf_BQE_NorBIsoPIDCutSignal_Bs0DstaMu"),LineWidth(2));
  pdf_fit_3D->plotOn(frameQ,LineColor(kGray),Components("histPdf_BQE_NorBIsoPIDCut_SameSign"),LineWidth(2));
  pdf_fit_3D->plotOn(frameQ,LineColor(kOrange),Components("AdHocDoubleCharmQ2Emu"),LineWidth(2));
  hpull_Q->GetXaxis()->SetRangeUser(-5000000, 11500000);
  hpull_Q->GetYaxis()->SetRangeUser(-5, 5);

  // Project over E
  RooPlot *frameE = emu->frame(200,3600,10);
  hMQE->plotOn(frameE,MarkerStyle(8));
  pdf_fit_3D->plotOn(frameE,LineColor(kBlue),LineWidth(2));
  // Get pulls. Has to be done here, otherwise it gets the pulls from the DoubleCharm
  RooHist *hpull_E = frameE->pullHist();
  pdf_fit_3D->plotOn(frameE,LineColor(kGreen),Components("histPdf_BQE_TauNorBIsoPIDCutSignal_Bs0DstaTau"),LineWidth(2));
  pdf_fit_3D->plotOn(frameE,LineColor(kMagenta),Components("histPdf_BQE_NorBIsoPIDCutSignal_Bs0DstaMu"),LineWidth(2));
  pdf_fit_3D->plotOn(frameE,LineColor(kGray),Components("histPdf_BQE_NorBIsoPIDCut_SameSign"),LineWidth(2));
  pdf_fit_3D->plotOn(frameE,LineColor(kOrange),Components("AdHocDoubleCharmQ2Emu"),LineWidth(2));
  hpull_E->GetXaxis()->SetRangeUser(200, 3600);
  hpull_E->GetYaxis()->SetRangeUser(-5, 5);

  TCanvas *c3 = new TCanvas("c3", "c3", 0,0,1400,1200);
  TPad *pad1_3 = new TPad("pad1_3","pad1_3",0.01 ,0.295, 0.32, 0.99 ,0);
  TPad *pad2_3 = new TPad("pad2_3","pad2_3",0.32, 0.295, 0.65, 0.99 ,0);
  TPad *pad3_3 = new TPad("pad3_3","pad3_3",0.66, 0.295, 0.99, 0.99, 0);
  TPad *pad4_3 = new TPad("pad4_3","pad4_3",0.01, 0.01, 0.32, 0.295, 0);
  TPad *pad5_3 = new TPad("pad5_3","pad5_3",0.32, 0.01, 0.65, 0.295, 0);
  TPad *pad6_3 = new TPad("pad6_3","pad6_3",0.66, 0.01, 0.99, 0.295, 0);
  pad1_3->Draw(); pad2_3->Draw(); pad3_3->Draw(); pad4_3->Draw(); pad5_3->Draw(); pad6_3->Draw();
  pad1_3->cd(); frameM->Draw(); //gPad->Update();
  pad2_3->cd(); frameQ->Draw(); //gPad->Update();
  pad3_3->cd(); frameE->Draw(); //gPad->Update();
  pad4_3->cd(); hpull_M->Draw(); //gPad->Update();
  pad5_3->cd(); hpull_Q->Draw(); //gPad->Update();   
  pad6_3->cd(); hpull_E->Draw(); //gPad->Update();
  c3->SaveAs("Mass_vs_Q2_vs_Emu_CB.pdf");
/*  
  // Fit MCORR vs Q2
  RooFitResult *resMQ;
  //resMQ = pdf_fit_q2->fitTo(*hMQ, Extended(true), SumW2Error(kTRUE), Minos(true), Strategy(2), Timer(kTRUE), NumCPU(4));

  // Project over MCORR
  RooPlot *frameM1 = mass->frame(3000,8000,80);
  hMQ->plotOn(frameM1,MarkerStyle(8));
  pdf_fit_q2->plotOn(frameM1,LineColor(kBlue),LineWidth(2));
  pdf_fit_q2->plotOn(frameM1,LineColor(kGreen),Components("histPdf_BQ_TauNorBIsoPIDCutSignal_Bs0DstaTau"),LineWidth(2));
  pdf_fit_q2->plotOn(frameM1,LineColor(kMagenta),Components("histPdf_BQ_NorBIsoPIDCutSignal_Bs0DstaMu"),LineWidth(2));
  pdf_fit_q2->plotOn(frameM1,LineColor(kGray),Components("histPdf_BQ_NorBIsoPIDCut_SameSign"),LineWidth(2));
  pdf_fit_q2->plotOn(frameM1,LineColor(kOrange),Components("AdHocDoubleCharmQ2"),LineWidth(2));

  // Get pulls
  RooHist *hpull_M1 = frameM1->pullHist();
  hpull_M1->GetXaxis()->SetRangeUser(3000, 8000);
  hpull_M1->GetYaxis()->SetRangeUser(-10, 10);

  // Project over Q2
  RooPlot *frameQ = qsquare->frame(-5000000,11500000,20);
  hMQ->plotOn(frameQ,MarkerStyle(8));
  pdf_fit_q2->plotOn(frameQ,LineColor(kBlue),LineWidth(2));
  pdf_fit_q2->plotOn(frameQ,LineColor(kGreen),Components("histPdf_BQ_TauNorBIsoPIDCutSignal_Bs0DstaTau"),LineWidth(2));
  pdf_fit_q2->plotOn(frameQ,LineColor(kMagenta),Components("histPdf_BQ_NorBIsoPIDCutSignal_Bs0DstaMu"),LineWidth(2));
  pdf_fit_q2->plotOn(frameQ,LineColor(kGray),Components("histPdf_BQ_NorBIsoPIDCut_SameSign"),LineWidth(2));
  pdf_fit_q2->plotOn(frameQ,LineColor(kOrange),Components("AdHocDoubleCharmQ2"),LineWidth(2));

  // Get pulls
  RooHist *hpull_Q = frameQ->pullHist();
  hpull_Q->GetXaxis()->SetRangeUser(-5000000, 11500000);
  hpull_Q->GetYaxis()->SetRangeUser(-10, 10);

  // Draw everything
  TCanvas *c1 = new TCanvas("c1", "c1", 0,0,1400,1200);
  TPad *pad1 = new TPad("pad1","pad1",0.01 ,0.295,0.495,0.99 ,0);
  TPad *pad2 = new TPad("pad2","pad2",0.505,0.295,0.99, 0.99 ,0);
  TPad *pad3 = new TPad("pad3","pad3",0.01, 0.01, 0.495,0.295,0);
  TPad *pad4 = new TPad("pad4","pad4",0.505,0.01, 0.99 ,0.295,0);
  pad1->Draw(); pad2->Draw(); pad3->Draw(); pad4->Draw();
  pad1->cd(); frameM1->Draw("P");  gPad->Update();
  pad2->cd(); frameQ->Draw("P");   gPad->Update();
  pad3->cd(); hpull_M1->Draw("P"); gPad->Update();
  pad4->cd(); hpull_Q->Draw("P");  gPad->Update();   
  c1->SaveAs("Mass_vs_Q2_CB.pdf");

  // Fit MCORR vs EMU
  RooFitResult *resME;
  resME = pdf_fit_emu->fitTo(*hME, Extended(true), SumW2Error(kTRUE), Minos(true), Strategy(2), Timer(kTRUE), NumCPU(4));

  // Project over MCORR
  RooPlot *frameM2 = mass->frame(3000,8000,80);
  hME->plotOn(frameM2,MarkerStyle(8));
  pdf_fit_emu->plotOn(frameM2,LineColor(kBlue),LineWidth(2));
  pdf_fit_emu->plotOn(frameM2,LineColor(kGreen),Components("histPdf_BE_TauNorBIsoPIDCutSignal_Bs0DstaTau"),LineWidth(2));
  pdf_fit_emu->plotOn(frameM2,LineColor(kMagenta),Components("histPdf_BE_NorBIsoPIDCutSignal_Bs0DstaMu"),LineWidth(2));
  pdf_fit_emu->plotOn(frameM2,LineColor(kGray),Components("histPdf_BE_NorBIsoPIDCut_SameSign"),LineWidth(2));
  pdf_fit_emu->plotOn(frameM2,LineColor(kOrange),Components("AdHocDoubleCharmEmu"),LineWidth(2));
   
  // Get pulls
  RooHist *hpull_M2 = frameM2->pullHist();
  hpull_M2->GetXaxis()->SetRangeUser(3000, 8000);
  hpull_M2->GetYaxis()->SetRangeUser(-10, 10);

  // Project over E
  RooPlot *frameE = emu->frame(200,3600,20);
  hME->plotOn(frameE,MarkerStyle(8));
  pdf_fit_emu->plotOn(frameE,LineColor(kBlue),LineWidth(2));
  pdf_fit_emu->plotOn(frameE,LineColor(kGreen),Components("histPdf_BE_TauNorBIsoPIDCutSignal_Bs0DstaTau"),LineWidth(2));
  pdf_fit_emu->plotOn(frameE,LineColor(kMagenta),Components("histPdf_BE_NorBIsoPIDCutSignal_Bs0DstaMu"),LineWidth(2));
  pdf_fit_emu->plotOn(frameE,LineColor(kGray),Components("histPdf_BE_NorBIsoPIDCut_SameSign"),LineWidth(2));
  pdf_fit_emu->plotOn(frameE,LineColor(kOrange),Components("AdHocDoubleCharmEmu"),LineWidth(2));

  // Get pulls
  RooHist *hpull_E = frameE->pullHist();
  hpull_E->GetXaxis()->SetRangeUser(200, 3600);
  hpull_E->GetYaxis()->SetRangeUser(-10, 10);
  
  // Draw everything
  TCanvas *c2 = new TCanvas("c2", "c2", 0,0,1400,1200);
  TPad *pad1_2 = new TPad("pad1_2","pad1_2",0.01 ,0.295,0.495,0.99 ,0);
  TPad *pad2_2 = new TPad("pad2_2","pad2_2",0.505,0.295,0.99, 0.99 ,0);
  TPad *pad3_2 = new TPad("pad3_2","pad3_2",0.01, 0.01, 0.495,0.295,0);
  TPad *pad4_2 = new TPad("pad4_2","pad4_2",0.505,0.01, 0.99 ,0.295,0);
  pad1_2->Draw(); pad2_2->Draw(); pad3_2->Draw(); pad4_2->Draw();
  pad1_2->cd(); frameM2->Draw();  gPad->Update();
  pad2_2->cd(); frameE->Draw();   gPad->Update();
  pad3_2->cd(); hpull_M2->Draw("P"); gPad->Update();
  pad4_2->cd(); hpull_E->Draw("P");  gPad->Update();
  c2->SaveAs("Mass_vs_Emu_CB.pdf");

  // Print the results

  double RDsstMQ = ratio->getVal();
  double errRDsstMQ = ratio->getError();  
  double RDsstME = ratio->getVal();
  double errRDsstME =  ratio->getError();
  // This is for fitting the ratio directly
  std::cout << "val MQ = " << RDsstMQ << " +/- " << errRDsstMQ << std::endl;
  std::cout << "val ME = " << RDsstME << " +/- " << errRDsstME << std::endl;

  double chi2_M = frameM1->chiSquare();
  double chi2_Q = frameQ->chiSquare();
  double chi2_M2 = frameM2->chiSquare();
  double chi2_E = frameE->chiSquare();
  std::cout << "Chi2 of M = " << chi2_M << std::endl;
  std::cout << "Chi2 of Q = " << chi2_Q << std::endl;
  std::cout << "Chi2 of M2 = " << chi2_M2 << std::endl;
  std::cout << "Chi2 of E = " << chi2_E << std::endl;
*/
}



