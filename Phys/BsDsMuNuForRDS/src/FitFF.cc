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

void FitFF(){

  int NQ2bins = 11;
  
  TFile *f = new TFile("DsMass_WithSWeighted_Dsst_CB.root","READ");
  TTree *t = (TTree*) f->Get("DecayTree");

  int entries = t->GetEntries();
  std::cout << "DEBUG: nEntries = " << entries << std::endl;

  Double_t Bs_0_MCORR, q2, sigw, Ds_PX, Ds_PY, Ds_PZ, Ds_PE, Ds_0_40_nc_maxPt_PX, Ds_0_40_nc_maxPt_PY, Ds_0_40_nc_maxPt_PZ, Ds_0_40_nc_maxPt_PE;
  Double_t Bs_PX, Bs_PY, Bs_PZ, Bs_PE, Bs_MM;
  Double_t Bs_ORIGX, Bs_ORIGY, Bs_ORIGZ, Bs_ENDX, Bs_ENDY, Bs_ENDZ;
  TBranch *b_Bs_0_MCORR, *b_q2, *b_sigw, *b_Ds_PX, *b_Ds_PY, *b_Ds_PZ, *b_Ds_PE, *b_Ds_0_40_nc_maxPt_PX, *b_Ds_0_40_nc_maxPt_PY, *b_Ds_0_40_nc_maxPt_PZ, *b_Ds_0_40_nc_maxPt_PE; 
  TBranch *b_Bs_PX, *b_Bs_PY, *b_Bs_PZ, *b_Bs_PE, *b_Bs_MM;
  TBranch *b_Bs_ORIGX, *b_Bs_ORIGY, *b_Bs_ORIGZ, *b_Bs_ENDX, *b_Bs_ENDY, *b_Bs_ENDZ;

  t->SetBranchAddress("Bs_0_MCORR", &Bs_0_MCORR, &b_Bs_0_MCORR);
  t->SetBranchAddress("sigw", &sigw, &b_sigw);
  t->SetBranchAddress("q2", &q2, &b_q2);

  // transform the qsquare of Ds into q2 of Ds*
  t->SetBranchAddress("Bs_MM", &Bs_MM, &b_Bs_MM);
  t->SetBranchAddress("Bs_PX", &Bs_PX, &b_Bs_PX);
  t->SetBranchAddress("Bs_PY", &Bs_PY, &b_Bs_PY);
  t->SetBranchAddress("Bs_PZ", &Bs_PZ, &b_Bs_PZ);
  t->SetBranchAddress("Bs_PE", &Bs_PE, &b_Bs_PE);
  t->SetBranchAddress("Ds_PX", &Ds_PX, &b_Ds_PX);
  t->SetBranchAddress("Ds_PY", &Ds_PY, &b_Ds_PY);
  t->SetBranchAddress("Ds_PZ", &Ds_PZ, &b_Ds_PZ);
  t->SetBranchAddress("Ds_PE", &Ds_PE, &b_Ds_PE);
  t->SetBranchAddress("Ds_0.40_nc_maxPt_PX", &Ds_0_40_nc_maxPt_PX, &b_Ds_0_40_nc_maxPt_PX);
  t->SetBranchAddress("Ds_0.40_nc_maxPt_PY", &Ds_0_40_nc_maxPt_PY, &b_Ds_0_40_nc_maxPt_PY);
  t->SetBranchAddress("Ds_0.40_nc_maxPt_PZ", &Ds_0_40_nc_maxPt_PZ, &b_Ds_0_40_nc_maxPt_PZ);
  t->SetBranchAddress("Ds_0.40_nc_maxPt_PE", &Ds_0_40_nc_maxPt_PE, &b_Ds_0_40_nc_maxPt_PE);   
  t->SetBranchAddress("Bs_ORIGX", &Bs_ORIGX, &b_Bs_ORIGX);
  t->SetBranchAddress("Bs_ORIGY", &Bs_ORIGY, &b_Bs_ORIGY);
  t->SetBranchAddress("Bs_ORIGZ", &Bs_ORIGZ, &b_Bs_ORIGZ);
  t->SetBranchAddress("Bs_ENDX", &Bs_ENDX, &b_Bs_ENDX);
  t->SetBranchAddress("Bs_ENDY", &Bs_ENDY, &b_Bs_ENDY);
  t->SetBranchAddress("Bs_ENDZ", &Bs_ENDZ, &b_Bs_ENDZ);

  char histoName[50], name[50], file[400], histoMu[200], histoTau[200], histoSS[200], histo[200];

  for(int i=10; i<=NQ2bins; ++i){

    sprintf(histoName,"MCORR_Bin%d",i);
    TH1F *histMCORR = new TH1F(histoName, histoName, 40, 3000, 8000);
  
    double binCutLow = -5000000+(i-1)*1500000;
    double binCutHigh = -5000000+i*1500000;
    double q2Full, q2Original;
    double newBE, newBPZ, newBPX, newBPY, newBPMag;
    double alpha, xFactor, yFactor;
    TLorentzVector Bs, Ds, gamma, Dsst, full, orig;
    std::cout << "Enter loop " << std::endl;
    TVector3 dispVector, zVector;
    for(int j=0; j<=entries; ++j){
      t->GetEntry(j);
      // get the new PZ of the B
      newBPZ = Bs_PZ * (5366.77/Bs_MM);
      // get the displacement vector
      dispVector.SetX(Bs_ORIGX - Bs_ENDX);
      dispVector.SetY(Bs_ORIGY - Bs_ENDY);
      dispVector.SetZ(Bs_ORIGZ - Bs_ENDZ);
      zVector.SetXYZ(0.0, 0.0, 1.0);
      alpha = dispVector.Angle(zVector);
      newBPMag = newBPZ * pow((1 + (pow(tan(alpha),2))),0.5);
      newBE = pow((pow(newBPMag,2) + pow(5366.79,2)),0.5);
      xFactor = dispVector.X() / dispVector.Z();
      yFactor = dispVector.Y() / dispVector.Z();
      newBPX = xFactor * newBPZ;
      newBPY = yFactor * newBPZ;
      Bs.SetPxPyPzE(newBPX, newBPY, newBPZ, newBE);
      Ds.SetPxPyPzE(Ds_PX,Ds_PY,Ds_PZ,Ds_PE);
      gamma.SetPxPyPzE(Ds_0_40_nc_maxPt_PX,Ds_0_40_nc_maxPt_PY,Ds_0_40_nc_maxPt_PZ,Ds_0_40_nc_maxPt_PE);
      Dsst = Ds + gamma;
      full = Bs - Dsst;
      q2Full = full.M2();
      orig = Bs - Ds;
      q2Original = orig.M2();
      if(q2Full > binCutLow && q2Full < binCutHigh){
        histMCORR->Fill(Bs_0_MCORR,sigw);
      }
    }

    std::cout << "Histogram entries = " << histMCORR->GetSumOfWeights() << std::endl;
    RooArgSet *f_mymcorr_pdfs = new RooArgSet("mymcorr_pdfs");
    RooArgSet *f_my_yields = new RooArgSet("my_yields");
    
    // Mu
    sprintf(file,"/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/Templates/output/RootOutp_MCAll_bin%d_NorBIsoPIDCutSignal_Bs0DstaMu.root",i);
    TFile *fMu = new TFile(file,"READ");
    std::cout << "Read Muon workspace" << std::endl;
    RooWorkspace *wMu = (RooWorkspace*) fMu->Get("w");
   
    RooRealVar *dsta_yield = new RooRealVar("bsdsta_yield","Yield of bsdsta events",1000,1,100000);
    f_my_yields->add(*dsta_yield);
    sprintf(histoMu,"histPdf_bin%d_NorBIsoPIDCutSignal_Bs0DstaMu",i); 
    RooAbsPdf *mcorr_DstMu_pdf = wMu->pdf(histoMu);
    f_mymcorr_pdfs->add(*mcorr_DstMu_pdf);
    std::cout << "DEBUG: loaded histograms for Mu" << std::endl;
    
    // Tau
    sprintf(file,"/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/Templates/output/RootOutp_MCAll_bin%d_TauNorBIsoPIDCutSignal_Bs0DstaTau.root",i);
    TFile *fTau = new TFile(file,"READ");
    std::cout << "Read Tau workspace" << std::endl;
    RooWorkspace *wTau = (RooWorkspace*) fTau->Get("w");

    RooRealVar *dstatau_yield = new RooRealVar("bsdstatau_yield","Yield of bsdsta events",100,0,100000);
    RooRealVar *ratio = new RooRealVar("ratio", "ratio", 0.01, 0., 1.);
    RooFormulaVar *yield = new RooFormulaVar("yield", "yield and RDs", "@0*@1", RooArgList(*ratio, *dsta_yield));
    f_my_yields->add(*yield);
    sprintf(histoTau,"histPdf_bin%d_TauNorBIsoPIDCutSignal_Bs0DstaTau",i);
    RooAbsPdf *mcorr_DstTau_pdf = wTau->pdf(histoTau);
    f_mymcorr_pdfs->add(*mcorr_DstTau_pdf);
    std::cout << "DEBUG: loaded histograms for Tau" << std::endl;

    // SameSign
    sprintf(file,"/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/Templates/output/RootOutp_MCAll_bin%d_NorBIsoPIDCut_SameSign.root",i);
    TFile *fSS = new TFile(file,"READ");
    std::cout << "Read SS workspace" << std::endl;
    RooWorkspace *wSS = (RooWorkspace*) fSS->Get("w");

    RooRealVar *SS_yield = new RooRealVar("SS_yield","Same Sign yield",100,0,100000);
    f_my_yields->add(*SS_yield);
    sprintf(histoSS,"histPdf_bin%d_NorBIsoPIDCut_SameSign",i);
    RooAbsPdf *mcorr_SS_pdf = wSS->pdf(histoSS);
    f_mymcorr_pdfs->add(*mcorr_SS_pdf);
    std::cout << "DEBUG: loaded histograms for SameSign" << std::endl;

    // Double Charm
    //Try to build an "ad hoc" PDF, with fixed ratios.
    RooArgSet *f_my_ddmcorrlist = new RooArgSet("my_ddmcorrlist");
    RooArgSet *f_my_ddfrac = new RooArgSet("my_ddfrac");

    // LbLcDs  
    sprintf(file,"/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/Templates/output/RootOutp_MCAll_bin%d_NorBIsoPIDCutLbLcDs.root",i);
    TFile *fLb = new TFile(file,"READ");
    std::cout << "Read LbLcDs workspace" << std::endl;
    RooWorkspace *wLb = (RooWorkspace*) fLb->Get("w");

    RooRealVar *LbLcDs_frac = new RooRealVar("LbLcDs_frac","Frac of LbLcDs events",0.084,0,1);
    LbLcDs_frac->setConstant(kTRUE);
    f_my_ddfrac->add(*LbLcDs_frac);
    sprintf(histo,"histPdf_bin%d_NorBIsoPIDCutLbLcDs",i);
    RooAbsPdf *mcorr_Lb_pdf = wLb->pdf(histo);
    f_my_ddmcorrlist->add(*mcorr_Lb_pdf);
    std::cout << "DEBUG: loaded histograms for LbLcDs" << std::endl;

    // DsDs
    sprintf(file,"/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/Templates/output/RootOutp_MCAll_bin%d_NorBIsoPIDCutBsDsDs.root",i);
    TFile *fDs = new TFile(file,"READ");
    std::cout << "Read BdDsDs workspace" << std::endl;
    RooWorkspace *wDs = (RooWorkspace*) fDs->Get("w");

    RooRealVar *BsDsDs_frac = new RooRealVar("BsDsDs_frac","Frac of BsDsDs events",0.127,0,1);
    BsDsDs_frac->setConstant(kTRUE);
    f_my_ddfrac->add(*BsDsDs_frac);
    sprintf(histo,"histPdf_bin%d_NorBIsoPIDCutBsDsDs",i);
    RooAbsPdf *mcorr_Ds_pdf = wDs->pdf(histo);
    f_my_ddmcorrlist->add(*mcorr_Ds_pdf);
    std::cout << "DEBUG: loaded histograms for BsDsDs" << std::endl;
  
    // DstDs
    sprintf(file,"/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/Templates/output/RootOutp_MCAll_bin%d_NorBIsoPIDCutBdDstDs.root",i);
    TFile *fDst = new TFile(file,"READ");
    std::cout << "Read BdDstDs workspace" << std::endl;
    RooWorkspace *wDst = (RooWorkspace*) fDst->Get("w");
  
    RooRealVar *BdDstDs_frac = new RooRealVar("BdDstDs_frac","Frac of BdDstDs events",0.339,0,1);
    BdDstDs_frac->setConstant(kTRUE);
    f_my_ddfrac->add(*BdDstDs_frac);
    sprintf(histo,"histPdf_bin%d_NorBIsoPIDCutBdDstDs",i);
    RooAbsPdf *mcorr_Dst_pdf = wDst->pdf(histo);
    f_my_ddmcorrlist->add(*mcorr_Dst_pdf);
    std::cout << "DEBUG: loaded histograms for BdDstDs" << std::endl;
 
    // D0Ds
    sprintf(file,"/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/Templates/output/RootOutp_MCAll_bin%d_NorBIsoPIDCutBuD0Ds.root",i);
    TFile *fD0 = new TFile(file,"READ");
    std::cout << "Read BuD0Ds workspace" << std::endl;
    RooWorkspace *wD0 = (RooWorkspace*) fD0->Get("w");
  
    RooRealVar *BuD0Ds_frac = new RooRealVar("BuD0Ds_frac","Frac of BuD0Ds events",0.450,0,1);
    BuD0Ds_frac->setConstant(kTRUE);
    f_my_ddfrac->add(*BuD0Ds_frac);
    sprintf(histo,"histPdf_bin%d_NorBIsoPIDCutBuD0Ds",i);
    RooAbsPdf *mcorr_D0_pdf = wD0->pdf(histo);
    f_my_ddmcorrlist->add(*mcorr_D0_pdf);
    std::cout << "DEBUG: loaded histograms for BuD0Ds" << std::endl;

    // add all the double charm pdfs and yields
    RooAddPdf *f_dcharmmcorr_pdf = new RooAddPdf("AdHocDoubleCharmMCorr","",RooArgSet(*f_my_ddmcorrlist),RooArgSet(*f_my_ddfrac));
    f_mymcorr_pdfs->add(*f_dcharmmcorr_pdf);
    RooRealVar *dcharm_yield = new RooRealVar("dcharm_yield","Yield of double charm events",100,0,100000);
    f_my_yields->add(*dcharm_yield);

    // Add the pdfs
    RooAbsPdf *pdf_fit_mcorr;
    pdf_fit_mcorr = new RooAddPdf("pdf_fit_mcorr","",RooArgSet(*f_mymcorr_pdfs),RooArgSet(*f_my_yields));
    RooRealVar *mass = new RooRealVar("m_{D_{s}#mu}", "B_s corr mass", 3000, 8000);
    RooDataHist *hM = new RooDataHist("hM", "hM", *mass, histMCORR, 1.0);

    // Fit mass 
    RooFitResult *resM;
    resM = pdf_fit_mcorr->fitTo(*hM, Extended(true), SumW2Error(kTRUE), Minos(true), Strategy(2), Timer(kTRUE), NumCPU(4));

    // MCORR
    RooPlot *frameM = mass->frame(3000,8000,40);
    hM->plotOn(frameM,MarkerStyle(8));
    pdf_fit_mcorr->plotOn(frameM,LineColor(kBlue),LineWidth(2));
    // Get pulls. Has to be done here, otherwise it gets the pulls from the DoubleCharm
    RooHist *hpull_M = frameM->pullHist();
    pdf_fit_mcorr->plotOn(frameM,LineColor(kGreen),Components(histoTau),LineWidth(2));
    pdf_fit_mcorr->plotOn(frameM,LineColor(kMagenta),Components(histoMu),LineWidth(2));
    pdf_fit_mcorr->plotOn(frameM,LineColor(kGray),Components(histoSS),LineWidth(2));
    pdf_fit_mcorr->plotOn(frameM,LineColor(kOrange),Components("AdHocDoubleCharmMCorr"),LineWidth(2));
    hpull_M->GetXaxis()->SetRangeUser(3000, 8000);
    hpull_M->GetYaxis()->SetRangeUser(-5, 5);

    TCanvas *c = new TCanvas("c", "c", 0,0,1200,1000);
    TPad *pad1 = new TPad("pad1","pad1",0.01 ,0.295, 0.99, 0.99 ,0);
    TPad *pad2 = new TPad("pad2","pad2",0.01, 0.01, 0.99, 0.295 ,0);
    pad1->Draw(); pad2->Draw(); 
    pad1->cd(); frameM->Draw(); //gPad->Update();
    pad2->cd(); hpull_M->Draw(); //gPad->Update();
    sprintf(name,"Mass_bin%d.pdf",i);
    c->SaveAs(name);
    delete histMCORR;
    std::cout << "DsMu yield = " << dsta_yield->getVal() << " +/- " << dsta_yield->getError() << std::endl;
  }
}
