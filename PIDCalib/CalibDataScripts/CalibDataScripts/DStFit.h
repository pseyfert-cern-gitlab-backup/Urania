// $Id: $
#ifndef CALIBDATASCRIPTS_DSTFIT_H 
#define CALIBDATASCRIPTS_DSTFIT_H 1

/*
 *  @author Andrew Powell (LHCb)04
 *  @date   2011-06-14
 */

// Include files
#include "RooPhysFitter/RooDstarD0MassFitter.h"
#include "CalibDataScripts/LHCbStyle.h"

//Boost
#include <boost/assign.hpp>

// Type Definitions
typedef void (*fptr)(RooDMassFitter*, 
                     const char*,
                     const char*);

namespace bass=boost::assign;

void DStFit(TTree* tt, 
            const char* charge,
            const char* pName,
            const char* wsName,
            const char* fName,
            const char* dsName,
            const char* d0Name,
            const char* delmName,
            std::vector<fptr>& fun_vec,
            const char* index="0")
{
  
  //==================================================//
  // Constants
  //==================================================//
  Float_t d0MassPDG=1864.83;
  Float_t delmPDG=145.421;
  Float_t piPDG=139.57018;

  //==================================================//
  // Declare and configure fitter 
  //==================================================//
  RooDstarD0MassFitter* massFitter = new RooDstarD0MassFitter("MassFitter","");
  massFitter->CreateWS(wsName, "");
  massFitter->AttachFile(fName, "RECREATE");
  massFitter->SetDMassName(d0Name);
  massFitter->SetDelmName(delmName);
  massFitter->MakeDMassVar(d0MassPDG-70,
                           d0MassPDG+70,
                           "MeV/c^{2}",
                           "m_{K#pi}");

  massFitter->MakeDelmVar(delmPDG-6.0,
                          delmPDG+7.0,
                          "MeV/c^{2}",
                          "m_{K#pi#pi_{s}}-m_{K#pi}");

  //==================================================//
  // If pName is sPi, set DataSet name to Pi
  //==================================================//
  const char* DSpName = NULL;
  if(strcmp(pName,"Pi")==0 || strcmp(pName,"K")==0)
    DSpName = pName;
  else if(strcmp(pName,"sPi")==0)
    DSpName = "Pi";
  else
  {
    std::cout<<"Unexpected particle name "<<pName<<std::endl;
    exit(1);
  }
    
  //==================================================//
  // Add Spectator variables
  //==================================================//
  std::vector<fptr>::iterator itr;
  for(itr=fun_vec.begin(); itr!=fun_vec.end(); ++itr)
  {
    std::cout<<"Adding Spectator Vars"<<std::endl;
    (*itr)(massFitter, DSpName, pName);
  }
  
  //==================================================//
  // Select tracks with specific charge
  //==================================================//
  TString chrg="";
  if(strcmp(charge, "Positive")==0)
    chrg = "1.0";
  else if(strcmp(charge,"Negative")==0)
    chrg = "-1.0";
  else{
    std::cout<<"Unexpected charge type "<<charge<<std::endl;
    exit(1);
  }

  massFitter->MakeDelmDataSet(tt, 
                              "D0_M", 
                              "DSt_M", 
                              dsName, 
                              "", 
                              TString::Format("%s_hasRich == 1.0 && %s_Q == "+chrg, pName, pName).Data(),
                              kFALSE);


  //==================================================//
  // Configure D0 Line Shape
  //==================================================//
  massFitter->MakeDMassSigBiGauss(d0MassPDG, d0MassPDG-5, d0MassPDG+5,
                                  8.0,7.0,9.0,
                                  2.0,1.5,2.5, 
                                  0.75);
  
  //==================================================//
  // Configure D0 Background Shape
  //==================================================//
  massFitter->MakeDMassBkgFlat(-0.4, -0.8, -0.3);
  
  //==================================================//
  // Configure DeltaM Line Shape
  //==================================================//
  massFitter->MakeDelmSigBiGauss(delmPDG, delmPDG-1.0, delmPDG+1.0,
                                 delmPDG, delmPDG-2.0, delmPDG+2.0,
                                 0.55, 0.45, 0.65,
                                 2.0, 1.5, 2.5,
                                 0.55); 
  


  //==================================================//
  // Configure DeltaM Background Shape
  //==================================================//
  /*massFitter->MakeDelmBkgDstD0BG(piPDG, piPDG-1, piPDG+1,//dm0 (threshold)
                                 15.0, 1.0, 17.0,          //c   (exponent)
                                 2.9,   2.0,  4.0,         //a   (power)
                                 -7.4, -15.0, -6.0);       //b   (linear)
  */
  //Fix b and c parameters for better fit
  massFitter->MakeDelmBkgDstD0BG(piPDG,piPDG-1, piPDG+1,//dm0 (threshold)
                                 5.0,                   //c   (exponent)
                                 2.9,   2.0,  4.0,      //a   (power)
                                 -8);                   //b   (linear)
  


  //==================================================//
  // Make composite model with following estimate of 
  // yield breakdown
  //==================================================//
  massFitter->MakeDelmModel(0.67, 0.12, 0.15, 0.01);


  
  //==================================================// 
  // Perform Fit
  //==================================================//
  std::cout << "Performing fit" << std::endl;
  std::vector<Int_t> FitStrategies = bass::list_of(0)(1);
  massFitter->PerformDelmIterativeBinnedFit(200,
                                            200,
                                            FitStrategies,
                                            "fitResults", 
                                            6, 
                                            kTRUE, 
                                            kTRUE, 
                                            kFALSE, 
                                            kTRUE, 
                                            kFALSE);

  //==================================================// 
  // Calculate sWeights
  //==================================================//
  massFitter->CalculateSWeights("fitResults", 
                                TString::Format("%s_wSWeights",dsName).Data());
  massFitter->SaveWS();
  
  //==================================================// 
  // Configure plot attributes
  //==================================================//
  std::cout << "Setting plot attributes" << std::endl;
  massFitter->AddPdfComponent("sig2DModel",     kRed,      kDashed, 3);
  massFitter->AddPdfComponent("combBkg2DModel", kGreen,    kDotted, 3);
  massFitter->AddPdfComponent("piBkg2DModel",   kMagenta,  kDashed, 3);
  massFitter->AddPdfComponent("d0Bkg2DModel",   kOrange+2, 7,       3);

  TString plotParams_d0="";
  TString plotParams_delm="";
  plotParams_d0="dmass_sig_mu,dmass_sig_sigma0,dmass_sig_sigma1";
  plotParams_delm="delm_sig_mu0,delm_sig_sigma0,delm_sig_mu1,delm_sig_sigma1";
  massFitter->SetParamBoxAttributes("paramBox",0.68,0.65,0.95,0.93,0.026,12);

  int nbins = 100;
  massFitter->SetPlotBins(nbins);
  massFitter->SetChi2Bins(nbins);
  massFitter->SetChi2Bins(d0Name,nbins);
  massFitter->SetChi2Bins("delm",nbins);
  massFitter->SetChi2Bins(d0Name,nbins/2);
  massFitter->SetChi2Bins("delm",nbins/2);
  massFitter->SetParamBoxY1(0.5);
  massFitter->SetParamBoxX1(0.62);
  massFitter->SetParamBoxTextSize(0.022);

  
  //==================================================// 
  // Make plots
  //==================================================//
  RooRealVar* mass=massFitter->GetVar(d0Name);
  mass->setRange("sigRange",d0MassPDG-40,d0MassPDG+30);
  RooRealVar* delm=massFitter->GetVar("delm");
  delm->setRange("sigRange",delmPDG-2.3,delmPDG+2.3);

  TString rangeTitle="sigRegion";
  LHCbStyle();
  
  //==================================================// 
  // Plot D0 Mass Fit
  //==================================================//
  massFitter->SetPlotParameters(plotParams_d0.Data());
  
  RooPlot* rp_mass = massFitter->PlotFitResults(d0Name, 
                                                "fitResults",
                                                "sigRange",
                                                rangeTitle.Data());

  TCanvas* c1 = new TCanvas("cnv_mass", "", 1024, 768);
  rp_mass->Draw();
  c1->SaveAs(TString::Format("FitRes_%s_%s_%s_%s.eps",d0Name,pName,charge,index).Data());
  
  //==================================================// 
  // Plot DeltaM Fit
  //==================================================//
  massFitter->SetPlotParameters(plotParams_delm.Data());
  RooPlot* rp_delm = massFitter->PlotFitResults(delmName, 
                                                "fitResults",
                                                "sigRange",
                                                rangeTitle.Data());

  TCanvas* c2 = new TCanvas("cnv_delm", "", 1024, 768);
  rp_delm->Draw();
  c2->SaveAs(TString::Format("FitRes_%s_%s_%s_%s.eps",delmName,pName,charge,index).Data());

  //==================================================// 
  // Plot weighted DLL(K-pi) distribution
  //==================================================//
  massFitter->CreateWeightedDataSet("data_sigw",
                                    "nsig_sw");
  massFitter->SetDataSetName("data_sigw");
  RooPlot* rp_kpidk = massFitter->PlotVariable(TString::Format("%s_CombDLLK",DSpName).Data(),"", "", kTRUE);
  TCanvas* c3 = new TCanvas("cnv_kpidk", "", 1024, 768);
  rp_kpidk->Draw();
  c3->SaveAs(TString::Format("DLLK_%s_%s_%s.eps",pName,charge,index).Data());
  
  //==================================================// 
  // Clean up
  //==================================================//
  delete rp_kpidk;
  delete rp_mass;
  delete rp_delm;
  delete c1;
  delete c2;
  delete c3;
  delete massFitter;
  
}
#endif // CALIBDATASCRIPTS_DSTFIT_H
