#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TH1F.h"
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
  maxMass = 5366.82;
  //  f_fit_range_max = 5860;
  f_drawbins = 50;
  f_infi = inf;
  f_flag = fl;
  f_isMC = kFALSE;
  f_isNewMC = kFALSE;
  f_doMCmatch = kFALSE;
  f_doSS = kFALSE;
  f_doSB = kFALSE;
  f_doTau = kFALSE;
  f_doTrueDs = kFALSE;
  f_doRooKeys = kFALSE;
  f_doFake = kFALSE;
  f_doFF = kFALSE;
  f_applyTauCut = 0;
  f_applyBMCut = 0;
  f_applyIsoCut = 0;
  f_matchPar = 0;
  m_debug = debug;
  IDX_Prior = 0;
  sum.clear();

}

void TemplateTools::doTemplate() {

  std::cout << " Entering Do Template " << std::endl;

  char hn[200];  
  char pdfnm[200];
  
  TRandom3 rnd3; rnd3.SetSeed(0);

  //Here you should include your Fit Code
  gROOT->ProcessLine(".x lhcbstyle.C");
  gSystem->Load("libRooFit.so");
  gROOT->SetStyle("Plain"); 

  //Write File Result
  sprintf(hn,"output/RootOutp_MCAll_bin%d_%s_Weight.root",f_binFF,f_flag.data());   
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
  sprintf(atext,"datasetQ");
  RooDataSet* Adq  = new  RooDataSet(atext,atext,RooArgSet(*mass,*qsquare));
  sprintf(atext,"datasetQP");
  RooDataSet* Adqp = new  RooDataSet(atext,atext,RooArgSet(*mass,*qsquare));
  sprintf(atext,"datasetQM");
  RooDataSet* Adqm = new  RooDataSet(atext,atext,RooArgSet(*mass,*qsquare));  
  sprintf(atext,"datasetE");
  RooDataSet* Ade  = new  RooDataSet(atext,atext,RooArgSet(*mass,*emu));
  sprintf(atext,"datasetM");
  RooDataSet* Adm  = new  RooDataSet(atext,atext,RooArgSet(*mass,*mmsq));
  //sprintf(atext,"datasetQE");
  //RooDataSet* Adqe  = new  RooDataSet(atext,atext,RooArgSet(*mass,*qsquare,*emu));

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
  std::cout << "nentries = " << fl_nentries << std::endl;
  tree->SetBranchStatus("*",1);
  if(m_debug) tree->Print();
  //tree->SetBranchAddress("Bs_0_MCORR",&fl_Bmass);
  //tree->SetBranchAddress("q2",&fl_q2);
  tree->SetBranchAddress("McorrDsst",&fl_Bmass);
  tree->SetBranchAddress("q2Reg",&fl_q2);
  tree->SetBranchAddress("Emu",&fl_Emu);
  tree->SetBranchAddress("MM2",&fl_MM2);
  
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
    Besides MC there's also reco stuff
  */
  // PID cut
  //  TString rec_muCut = "( mc_MC12TuneV2_probNNmu )";
  //  TString rec_muCut = " && ( mu_ProbNNmu > 0.3)";
  TString rec_muCut = " && ( mu_PIDmu > 0)";
  TString rec_trueDs = " && (Ds_MM>1940 && Ds_MM<2000)";
  //  TString rec_isocut = " && ( Bs_0_D1_isobdt3_2nd > 0.09) "; 
  //  TString rec_isocut = " && Ds_SmallestDeltaChi2OneTrack > 5"; 
  TString rec_isocut = " ";
  if(f_applyIsoCut) rec_isocut = " && (mu_iso_MinBDT_Long>-0.5) ";
  //Hard cut
  //  if(f_applyIsoCut) rec_isocut = " && (mu_iso_MinBDT_Long>0.25) ";
  TString trig_unb = " ";
  TString rec_sbcut = " && (Ds_MM<1940 || Ds_MM>2000) ";
  // add sq > 0, to remove unphysical solutions from the q2
  //TString cut = " Bs_0_MCORR > 3000 && Bs_0_MCORR < 8000 && (Ds_MM>1940 && Ds_MM<2000) && sq > 0.";
  TString cut = " McorrDsst > 3000 && McorrDsst < 8000 && (Ds_MM>1940 && Ds_MM<2000) && sq > 0.";

  TString cutPhiPi = " && (sqrt(Kmi_M*Kmi_M+Kpl_M*Kpl_M+2*(Kmi_PE*Kpl_PE-Kmi_PX*Kpl_PX-Kmi_PY*Kpl_PY-Kmi_PZ*Kpl_PZ))>1000&&sqrt(Kmi_M*Kmi_M+Kpl_M*Kpl_M+2*(Kmi_PE*Kpl_PE-Kmi_PX*Kpl_PX-Kmi_PY*Kpl_PY-Kmi_PZ*Kpl_PZ))<1040)";

  TString cutQ2_bin0 = " && q2Reg > -5000000 && q2Reg < 11500000";

  TString cutQ2_bin1 = " && q2Reg > -5000000 && q2Reg < -3500000";

  TString cutQ2_bin2 = " && q2Reg > -3500000 && q2Reg < -2000000";

  TString cutQ2_bin3 = " && q2Reg > -2000000 && q2Reg < -500000";

  TString cutQ2_bin4 = " && q2Reg > -500000 && q2Reg < 1000000";

  TString cutQ2_bin5 = " && q2Reg > 1000000 && q2Reg < 2500000";

  TString cutQ2_bin6 = " && q2Reg > 2500000 && q2Reg < 4000000";

  TString cutQ2_bin7 = " && q2Reg > 4000000 && q2Reg < 5500000";

  TString cutQ2_bin8 = " && q2Reg > 5500000 && q2Reg < 7000000";

  TString cutQ2_bin9 = " && q2Reg > 7000000 && q2Reg < 8500000";

  TString cutQ2_bin10 = " && q2Reg > 8500000 && q2Reg < 10000000";

  TString cutQ2_bin11 = " && q2Reg > 10000000 && q2Reg < 11500000";

  TString cutTOT;
  if(!f_isMC) {
    //data
    trig_unb = " && (Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS == 1) ";
    if(!f_doTrueDs) {
      cutTOT = cut + trig_unb + rec_muCut + rec_isocut;
    } 
    else {
      cutTOT = cut + trig_unb + rec_trueDs + rec_isocut;
    }
    if(f_doSB) cutTOT += rec_sbcut;

    if(f_applyBMCut) cutTOT += " && (sqrt( (Ds_PE+mu_PE)**2 - ((Ds_PX+mu_PX)**2 + (Ds_PY+mu_PY)**2 + (Ds_PZ+mu_PZ)**2) ) > 3000) ";
    
    if(f_applyTauCut) cutTOT += " && (mu_PT>1000)";

    if(f_doPhiPi) cutTOT += cutPhiPi;
  } 
  else {
    //MC
    if(f_isNewMC){
      trig_unb = " && (Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS == 1) ";
    }
    else {
      trig_unb = " && ( Kpl_P>5000 && Kmi_P>5000 && pi_P>5000 && (Kpl_PT>800 || Kmi_PT>800 || pi_PT>800) && Ds_PT>2000 && Bs_0_BDTS_DOCA<0.50 && Bs_0_FDCHI2_TOPPV>50 && 1940<Ds_MM && 2000>Ds_MM  ) ";
    }
    if(!f_doTrueDs) {
      cutTOT = cut + trig_unb + rec_muCut + rec_isocut;
    } 
    else {
      cutTOT = cut + trig_unb + rec_trueDs + rec_isocut;
    }

    if(f_applyBMCut) cutTOT += " && (sqrt( (Ds_PE+mu_PE)**2 - ((Ds_PX+mu_PX)**2 + (Ds_PY+mu_PY)**2 + (Ds_PZ+mu_PZ)**2) ) > 3000) ";
    
    if(f_applyTauCut) cutTOT += " && (mu_PT>1000)";

    if(f_doPhiPi) cutTOT += cutPhiPi;
 
    if(f_doFF) {
      if(f_binFF == 1) cutTOT += cutQ2_bin1; 
      else if(f_binFF == 2) cutTOT += cutQ2_bin2;
      else if(f_binFF == 3) cutTOT += cutQ2_bin3;
      else if(f_binFF == 4) cutTOT += cutQ2_bin4;
      else if(f_binFF == 5) cutTOT += cutQ2_bin5;
      else if(f_binFF == 6) cutTOT += cutQ2_bin6;
      else if(f_binFF == 7) cutTOT += cutQ2_bin7;
      else if(f_binFF == 8) cutTOT += cutQ2_bin8;
      else if(f_binFF == 9) cutTOT += cutQ2_bin9;
      else if(f_binFF == 10) cutTOT += cutQ2_bin10;
      else if(f_binFF == 11) cutTOT += cutQ2_bin11;
    }

    if(f_doMCmatch) {
      if(f_matchPar == 1) {
	      if(f_doTau) {
	        cutTOT += " && " + Dstau;
	      } 
        else {
	        cutTOT += " && " + Dsmu;
	      }
      } 
      else if(f_matchPar == 2) {
	      if(f_doTau) {
	        cutTOT += " && " + DsStartau;
	      } 
        else {
	        cutTOT += " && " + DsStarmu;
	      }
      } 
      else if(f_matchPar == 3) {
	      if(f_doTau) {
	        cutTOT += " && " + Ds2460tau;
	      } 
        else {
	        cutTOT += " && " + Ds2460mu;
	      }
      } 
      else if(f_matchPar == 4) {
	      if(f_doTau) {
	        cutTOT += " && " + Ds2536tau;
	      } 
        else {
	        cutTOT += " && " + Ds2536mu;
	      } 
      } 
      else if(f_matchPar == 5) {
	      if(f_doTau) {
	        cutTOT += " && " + 	Ds0Startau;
	      }
        else {
	        cutTOT += " && " + 	Ds0Starmu;
	      }
      } 
    }
  }

  cutTOT = "("+cutTOT+")*sigw";
  std::cout << "With weight = " << cutTOT << std::endl;

  TTreeFormula *formula = new TTreeFormula("formula",cutTOT,tree);
  f.cd();

  Double_t bins[12] = { 0., 1000000., 2000000., 3000000., 4000000., 5000000., 6000000., 7000000., 8000000., 9000000., 10000000., 11000000. };
  TH1D *histoMass = new TH1D("histoMass","",f_hbins,3000,maxMass);
  TH2D *histoMassQsq = new TH2D("histoMassQsq","",f_hbins,3000,maxMass,f_qbins,bins);
  TH2D *histoMassQsqP = new TH2D("histoMassQsq_P","",f_hbins,3000,maxMass,f_qbins,bins);
  TH2D *histoMassQsqM = new TH2D("histoMassQsq_M","",f_hbins,3000,maxMass,f_qbins,bins);
  TH2D *histoMassMMsq = new TH2D("histoMassMMsq","",f_hbins,3000,maxMass,f_mbins,0,8000);
  TH2D *histoMassEmu = new TH2D("histoMassEmu","",f_hbins,3000,maxMass,f_ebins,200,3600);
//  TH3D *histoMassQsqEmu = new TH3D("histoMassQsqEmu","",f_hbins,3000,maxMass,f_qbins,bins,f_ebins,200,3600);

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
      *qsquare = fl_q2;
      *emu = fl_Emu;
      *mmsq = fl_MM2;
      
      Ad->add(RooArgSet(*mass));
      Adq->add(RooArgSet(*mass,*qsquare));
      Adqp->add(RooArgSet(*mass,*qsquare));
      Adqm->add(RooArgSet(*mass,*qsquare));
      Adm->add(RooArgSet(*mass,*mmsq));
      Ade->add(RooArgSet(*mass,*emu));
      //Adqe->add(RooArgSet(*mass,*qsquare,*emu));
      histoMass->Fill(fl_Bmass);
      histoMassQsq->Fill(fl_Bmass,fl_q2);
      std::cout << "mass " << fl_Bmass << ", q2 " << fl_q2 << std::endl; 
      histoMassQsqP->Fill(fl_Bmass,fl_q2);
      histoMassQsqM->Fill(fl_Bmass,fl_q2);
      histoMassMMsq->Fill(fl_Bmass,fl_MM2);
      histoMassEmu->Fill(fl_Bmass,fl_Emu);
      //histoMassQsqEmu->Fill(fl_Bmass,fl_q2,fl_Emu);
    }
  }
  Ad->Print();
  Adq->Print();
  Ade->Print();
  Adm->Print();
  //Adqe->Print();
  Adqp->Print();
  Adqm->Print();

  std::cout << "All events processed" << std::endl;

  for(int iX=1; iX<histoMassQsq->GetNbinsX()+1; iX++) {
    for(int iY=1; iY<histoMassQsq->GetNbinsX()+1; iY++) {
      // build the plus and minus histogram
      histoMassQsqP->SetBinContent(iX,iY,histoMassQsq->GetBinContent(iX,iY)+sqrt(histoMassQsq->GetBinContent(iX,iY)));
      histoMassQsqM->SetBinContent(iX,iY,histoMassQsq->GetBinContent(iX,iY)-sqrt(histoMassQsq->GetBinContent(iX,iY)));
      //std::cout << histoMassQsq->GetBinContent(iX,iY)-sqrt(histoMassQsq->GetBinContent(iX,iY)) << std::endl;
      if(histoMassQsq->GetBinContent(iX,iY)<pow(10,-12)) histoMassQsq->SetBinContent(iX,iY,pow(10,-12));
    }
  }
  
  for(int iX=1; iX<histoMassMMsq->GetNbinsX()+1; iX++) {
    for(int iY=1; iY<histoMassMMsq->GetNbinsX()+1; iY++) {
      if(histoMassMMsq->GetBinContent(iX,iY)<pow(10,-12)) histoMassMMsq->SetBinContent(iX,iY,pow(10,-12));
    }
  }
  
  for(int iX=1; iX<histoMassEmu->GetNbinsX()+1; iX++) {
    for(int iY=1; iY<histoMassEmu->GetNbinsX()+1; iY++) {
      if(histoMassEmu->GetBinContent(iX,iY)<pow(10,-12)) histoMassEmu->SetBinContent(iX,iY,pow(10,-12));
    }
  }

//  for(int iX=1; iX<histoMassQsqEmu->GetNbinsX()+1; iX++) {
//    for(int iY=1; iY<histoMassQsqEmu->GetNbinsX()+1; iY++) {
//      for(int iZ=1; iZ<histoMassQsqEmu->GetNbinsX()+1; iZ++) {
//        if(histoMassQsqEmu->GetBinContent(iX,iY,iZ)<pow(10,-12)) histoMassQsqEmu->SetBinContent(iX,iY,iZ,pow(10,-12));
//      }
//    }
//  }

  if(!f_doRooKeys) {  
    
    RooDataHist *tmp_hist_bin = new RooDataHist("tmp_hist_bin","",*mass,histoMass);
    sprintf(atext,"histData_bin%d_%s",f_binFF,f_flag.data());
    tmp_hist_bin->SetName(atext); 

    RooDataHist *tmp_hist = new RooDataHist("tmp_hist","",*mass,histoMass);
    sprintf(atext,"histData_%s",f_flag.data());
    tmp_hist->SetName(atext);
    
    RooDataHist *tmp_hist_BQ = new RooDataHist("tmp_hist_BQ","",RooArgSet(*mass,*qsquare),histoMassQsq);
    sprintf(atext,"histData_BQ_%s",f_flag.data());
    tmp_hist_BQ->SetName(atext);
   
    RooDataHist *tmp_hist_BQP = new RooDataHist("tmp_hist_BQP","",RooArgSet(*mass,*qsquare),histoMassQsqP);
    sprintf(atext,"histData_BQP_%s",f_flag.data());
    tmp_hist_BQP->SetName(atext);

    RooDataHist *tmp_hist_BQM = new RooDataHist("tmp_hist_BQM","",RooArgSet(*mass,*qsquare),histoMassQsqM);
    sprintf(atext,"histData_BQM_%s",f_flag.data());
    tmp_hist_BQM->SetName(atext);
 
    RooDataHist *tmp_hist_BE = new RooDataHist("tmp_hist_BE","",RooArgSet(*mass,*emu),histoMassEmu);
    sprintf(atext,"histData_BE_%s",f_flag.data());
    tmp_hist_BE->SetName(atext);
    
    RooDataHist *tmp_hist_BM = new RooDataHist("tmp_hist_BM","",RooArgSet(*mass,*mmsq),histoMassMMsq);
    sprintf(atext,"histData_BM_%s",f_flag.data());
    tmp_hist_BM->SetName(atext);

//    RooDataHist *tmp_hist_BQE = new RooDataHist("tmp_hist_BQE","",RooArgSet(*mass,*qsquare,*emu),histoMassQsqEmu);
//    sprintf(atext,"histData_BQE_%s",f_flag.data());
//    tmp_hist_BQE->SetName(atext);
   
    RooHistPdf *pdf_hist_bin = new RooHistPdf("pdf_hist","",*mass,*tmp_hist_bin);
    sprintf(atext,"histPdf_bin%d_%s",f_binFF,f_flag.data());
    pdf_hist_bin->SetName(atext);

    RooHistPdf *pdf_hist = new RooHistPdf("pdf_hist","",*mass,*tmp_hist);
    sprintf(atext,"histPdf_%s",f_flag.data());
    pdf_hist->SetName(atext);
    
    RooHistPdf *pdf_hist_BQ = new RooHistPdf("pdf_hist_BQ","",RooArgSet(*mass,*qsquare),*tmp_hist_BQ);
    sprintf(atext,"histPdf_BQ_%s",f_flag.data());
    pdf_hist_BQ->SetName(atext);
   
    RooHistPdf *pdf_hist_BQP = new RooHistPdf("pdf_hist_BQP","",RooArgSet(*mass,*qsquare),*tmp_hist_BQP);
    sprintf(atext,"histPdf_BQP_%s",f_flag.data());
    pdf_hist_BQP->SetName(atext);

    RooHistPdf *pdf_hist_BQM = new RooHistPdf("pdf_hist_BQM","",RooArgSet(*mass,*qsquare),*tmp_hist_BQM);
    sprintf(atext,"histPdf_BQM_%s",f_flag.data());
    pdf_hist_BQM->SetName(atext);

    RooHistPdf *pdf_hist_BE = new RooHistPdf("pdf_hist_BE","",RooArgSet(*mass,*emu),*tmp_hist_BE);
    sprintf(atext,"histPdf_BE_%s",f_flag.data());
    pdf_hist_BE->SetName(atext);
    
    RooHistPdf *pdf_hist_BM = new RooHistPdf("pdf_hist_BM","",RooArgSet(*mass,*mmsq),*tmp_hist_BM);
    sprintf(atext,"histPdf_BM_%s",f_flag.data());
    pdf_hist_BM->SetName(atext);

//    RooHistPdf *pdf_hist_BQE = new RooHistPdf("pdf_hist_BQE","",RooArgSet(*mass,*qsquare,*emu),*tmp_hist_BQE);
//    sprintf(atext,"histPdf_BQE_%s",f_flag.data());
//    pdf_hist_BQE->SetName(atext);

    w->import(*pdf_hist);
    w->import(*tmp_hist);
    w->import(*pdf_hist_bin);
    w->import(*tmp_hist_bin);
    w->import(*pdf_hist_BQ);
    w->import(*tmp_hist_BQ);
    w->import(*pdf_hist_BQP);
    w->import(*tmp_hist_BQP);
    w->import(*pdf_hist_BQM);
    w->import(*tmp_hist_BQM);
    w->import(*pdf_hist_BE);
    w->import(*tmp_hist_BE);
    w->import(*pdf_hist_BM);
    w->import(*tmp_hist_BM);
    //w->import(*pdf_hist_BQE);
    //w->import(*tmp_hist_BQE);

    //  ExpPlot(Ad, pdf_hist, f_flag);
    
    //  ExpPlot2D_BQ(Adq, pdf_hist_BQ, f_flag+"_BQ");
    
    //  ExpPlot2D(Adm, pdf_hist_BM, f_flag+"_BM");
    
    //  ExpPlot2D(Ade, pdf_hist_BE, f_flag+"_BE");

  } else {

    RooKeysPdf *pdf_rkeys = new RooKeysPdf("pdf_rkeys","",*mass,*Ad) ;
    sprintf(atext,"keysPdf_%s",f_flag.data());
    pdf_rkeys->SetName(atext);
   
    RooKeysPdf *pdf_rkeys_bin = new RooKeysPdf("pdf_rkeys_bin","",*mass,*Ad) ;
    sprintf(atext,"keysPdf_bin%d_%s",f_binFF,f_flag.data());
    pdf_rkeys_bin->SetName(atext); 

    RooNDKeysPdf *pdf_rkeys_BQ = new RooNDKeysPdf("pdf_rkeys_BQ","",RooArgSet(*mass,*qsquare),*Adq,"am") ;
    sprintf(atext,"keysPdf_BQ_%s",f_flag.data());
    pdf_rkeys_BQ->SetName(atext);

    RooNDKeysPdf *pdf_rkeys_BQP = new RooNDKeysPdf("pdf_rkeys_BQP","",RooArgSet(*mass,*qsquare),*Adqp,"am") ;
    sprintf(atext,"keysPdf_BQP_%s",f_flag.data());
    pdf_rkeys_BQP->SetName(atext);

    RooNDKeysPdf *pdf_rkeys_BQM = new RooNDKeysPdf("pdf_rkeys_BQM","",RooArgSet(*mass,*qsquare),*Adqm,"am") ;
    sprintf(atext,"keysPdf_BQM_%s",f_flag.data());
    pdf_rkeys_BQM->SetName(atext);
    
    RooNDKeysPdf *pdf_rkeys_BE = new RooNDKeysPdf("pdf_rkeys_BE","",RooArgSet(*mass,*emu),*Ade,"am") ;
    sprintf(atext,"keysPdf_BE_%s",f_flag.data());
    pdf_rkeys_BE->SetName(atext);
    
    RooNDKeysPdf *pdf_rkeys_BM = new RooNDKeysPdf("pdf_rkeys_BM","",RooArgSet(*mass,*mmsq),*Adm,"am") ;
    sprintf(atext,"keysPdf_BM_%s",f_flag.data());
    pdf_rkeys_BM->SetName(atext);

//    RooNDKeysPdf *pdf_rkeys_BQE = new RooNDKeysPdf("pdf_rkeys_BQE","",RooArgSet(*mass,*qsquare,*emu),*Adqe,"am");
//    sprintf(atext,"keysPdf_BQE_%s",f_flag.data());
//    pdf_rkeys_BQE->SetName(atext);

    w->import(*pdf_rkeys);
    /*
    w->import(*pdf_rkeys_BQ);
    w->import(*pdf_rkeys_BE);
    w->import(*pdf_rkeys_BM);
    */
  }

  sprintf(atext,"dataSet_%s",f_flag.data());
  Ad->SetName(atext);
  sprintf(atext,"dataSetQ_%s",f_flag.data());
  Adq->SetName(atext);
  sprintf(atext,"dataSetQP_%s",f_flag.data());
  Adqp->SetName(atext);
  sprintf(atext,"dataSetQM_%s",f_flag.data());
  Adqm->SetName(atext);
  sprintf(atext,"dataSetE_%s",f_flag.data());
  Ade->SetName(atext);
  sprintf(atext,"dataSetM_%s",f_flag.data());
  Adm->SetName(atext);
//  sprintf(atext,"dataSetQE_%s",f_flag.data());
//  Adqe->SetName(atext);

  w->import(*Ad);
  w->import(*Adq);
  w->import(*Adqp);
  w->import(*Adqm);
  w->import(*Ade);
  w->import(*Adm);
//  w->import(*Adqe);
  
  /*********************************************/
  //     Fitting Parameters are defined
  /*********************************************/
  
  //Getting back in the good old place.
  f.cd();

  histoMass->Write();
  histoMassQsq->Write();
  histoMassQsqP->Write();
  histoMassQsqM->Write();
  histoMassEmu->Write();
  histoMassMMsq->Write();
  //histoMassQsqEmu->Write(); 
  //  RootTree->Write();

  f.Close();

  sprintf(hn,"output/RootOutp_MCAll_bin%d_%s_Weight.root",f_binFF,f_flag.data());   
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

void TemplateTools::ExpPlot2D_BQ(RooDataSet *adt, RooAbsPdf *apdf, string flg) {

  RooPlot *rpb; char hn[200];
  TLatex *lhcbLatex;
  lhcbLatex = new TLatex(0.18, 0.83,"#splitline{LHCb}{Preliminary}");
  TCanvas *c_4 = new TCanvas("c_4","");
  //Expert plot

  c_4->Clear(); c_4->cd(); 
  //  gPad->SetLogy();

  //  rpb = abdt->frame(5100,5600,25);
  rpb = mass->frame(f_fit_range_min,f_fit_range_max,20);
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
  
  sprintf(hn,"output/PlotPdf_Mass_2D_%s.pdf",flg.data());   
  
  c_4->Print(hn);

  c_4->Clear(); c_4->cd(); 
  //  gPad->SetLogy();

  //  rpb = abdt->frame(5100,5600,25);
  rpb = qsquare->frame(0.,12000000.,5);
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
  
  sprintf(hn,"output/PlotPdf_Qsq_2D_%s.pdf",flg.data());   
  
  c_4->Print(hn);

}

void TemplateTools::configure(string range, bool arange, string confF) {

  cout << "Configuring" << endl;

  f_range = range;
  f_applyRange = arange;

  if(!strcmp(range.data(),"right")) {
    //    f_fit_range_max = 6250;
    f_drawbins = 10;
    std::cout<<" Disabling the Misid and Excl, fitting right only up to: "<<f_fit_range_max<<std::endl;
  }

  //Read configuration file
  f_applyTauCut = ReadValFromFile(confF,"applyTauCut");
  f_applyBMCut  = ReadValFromFile(confF,"applyBMCut");
  f_applyIsoCut = ReadValFromFile(confF,"applyIsoCut");
  f_hbins   = ReadValFromFile(confF,"nBinsMass");
  f_qbins   = ReadValFromFile(confF,"nBinsQsq");
  f_ebins   = ReadValFromFile(confF,"nBinsEmu");
  f_mbins   = ReadValFromFile(confF,"nBinsMMsq");
  f_doPhiPi = ReadValFromFile(confF,"doPhiPi");

  mass = new RooRealVar("m_{D_{s}#mu}","B_s corr mass",f_fit_range_min,f_fit_range_max,"MeV/c^{2}");
  mass->setBins(f_hbins,"cache");
  qsquare = new RooRealVar("q^{2}","q^{2}",0.,11000000.,"MeV/c^{2}");
  qsquare->setBins(f_qbins,"cache");
  mmsq = new RooRealVar("mm^2","m_{miss}^{2}",0,8000,"MeV/c^{2}");
  mmsq->setBins(f_mbins,"cache");
  emu = new RooRealVar("E_{#mu}","E_{#mu}^{*}",200,3600,"MeV/c^{2}");
  emu->setBins(f_ebins,"cache");

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

void TemplateTools::doRooKeys() {
  f_doRooKeys = kTRUE;
  return;
}

void TemplateTools::doSideBands() {
  f_doSB = kTRUE;
  return;
}

void TemplateTools::doSameSign() {
  f_doSS = kTRUE;
  return;
}

void TemplateTools::doMC() {
  f_isMC = kTRUE;
  return;
}

void TemplateTools::doNewMC(){
  f_isNewMC = kTRUE;
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

void TemplateTools::doFF(int bin) {
  f_doFF = kTRUE;
  f_binFF = bin;
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
