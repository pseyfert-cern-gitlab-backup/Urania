// $Id: $
#ifndef CALIBDATASCRIPTS_LAM0FIT_H 
#define CALIBDATASCRIPTS_LAM0FIT_H 1

/*
 * @author Andrew Powell (LHCb)04
 *  @date   2011-06-14
 */

// Include files
#include "RooPhysFitter/RooDMassFitter.h"
#include "CalibDataScripts/LHCbStyle.h"

//Boost
#include <boost/assign.hpp>

// Type Definitions
typedef void (*fptr)(RooDMassFitter*, 
                     const char*,
                     const char*);

namespace bass=boost::assign;

void Lam0Fit(TTree* tt, 
             const char* charge,
             const char* MomRange,
             const char* pName,
             const char* wsName,
             const char* fName,
             const char* dsName,
             const char* lam0Name,
             std::vector<fptr>& fun_vec,
             const char* index="0",
             Bool_t isVerbose=kFALSE)
{
  
  //==================================================//
  // Constants
  //==================================================//
  Float_t lam0MassPDG=1115.683;

  //==================================================//
  // Declare and configure fitter 
  //==================================================//
  RooDMassFitter* massFitter = new RooDMassFitter("MassFitter","");
  massFitter->CreateWS(wsName, "");
  massFitter->AttachFile(fName, "RECREATE");
  massFitter->SetDMassName(lam0Name);
  massFitter->SetDMassSigModelName("sigModel");
  massFitter->SetDMassBkgModelName("bkgModel");
  massFitter->MakeDMassVar(lam0MassPDG-15,
                           lam0MassPDG+15,
                           "MeV/c^{2}",
                           "m_{p#pi}");

  if (isVerbose) massFitter->SetPrintEntriesFlag(kTRUE);

  //==================================================//
  // Add Spectator variables
  //==================================================//
  std::vector<fptr>::iterator itr;
  for(itr=fun_vec.begin(); itr!=fun_vec.end(); ++itr)
  {
    std::cout<<"Adding Spectator Vars"<<std::endl;
    (*itr)(massFitter, pName, pName);
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

  //==================================================//
  // Apply max momentum cut on events in LoP line
  //==================================================//
  TString Cuts;
  Cuts.Form("%s_hasRich == 1.0 && %s_Q == "+chrg, pName, pName);
  if(strcmp(MomRange, "LoP")==0)
    Cuts.Append(" && P_P <= 40000.0");
  else if (strcmp(MomRange, "HiP")==0)
    Cuts.Append(" && P_P > 40000.0");
  else{
    std::cout<<"Unexpected momentum type "<<MomRange<<std::endl;
    exit(1);
  }
  massFitter->MakeDMassDataSet(tt, 
                               "Lam0_M", 
                               dsName, 
                               "", 
                               Cuts.Data());
  
  //==================================================//
  // Configure Lambda Line Shape
  //==================================================//
  /*
  massFitter->MakeDMassSigBiGauss(lam0MassPDG, lam0MassPDG-5, lam0MassPDG+5,
                                   0.7,0.1,1.5,
                                   2.4,1.0,4.0, 
                                   0.5);
  */
  massFitter->MakeDMassSigTriGauss(lam0MassPDG, lam0MassPDG-5, lam0MassPDG+5,
                                   0.8,0.1,1.5,
                                   2.0,1.0,4.0, 
                                   5.0,1.0,7.0, 
                                   0.3,
                                   0.1);
  
  //==================================================//
  // Configure Lambda Background Shape
  //==================================================//
  massFitter->MakeDMassBkgQuadratic(-0.2, -1, 1,
                                    -0.2, -1, 1);

  //==================================================//
  // Make composite model with following estimate of 
  // yield breakdown
  //==================================================//
  massFitter->MakeDMassModel(0.9, 0.1);
  
  //==================================================// 
  // Perform Fit
  //==================================================//
  std::cout << "Performing fit" << std::endl;
  std::vector<Int_t> FitStrategies = bass::list_of(0)(2);
  massFitter->PerformDMassIterativeBinnedFit(500,
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
  massFitter->AddPdfComponent("sigModel",     kRed,      kDashed, 3);
  massFitter->AddPdfComponent("bkgModel",   kOrange+2, 7,       3);

  TString plotParams="dmass_sig_mu,dmass_sig_sigma0,dmass_sig_sigma1";
  plotParams+=",dmass_bkg_poly_c1,dmass_bkg_poly_c2";
  massFitter->SetPlotParameters(plotParams.Data());
  massFitter->SetParamBoxAttributes("paramBox",0.68,0.65,0.95,0.93,0.026,12);

  int nbins = 100;
  massFitter->SetPlotBins(nbins);
  massFitter->SetChi2Bins(nbins);
  massFitter->SetChi2Bins(lam0Name,nbins);
  massFitter->SetChi2Bins(lam0Name,nbins/2);
  massFitter->SetParamBoxY1(0.5);
  massFitter->SetParamBoxX1(0.62);
  massFitter->SetParamBoxTextSize(0.022);
  
  //==================================================// 
  // Make plots
  //==================================================//
  RooRealVar* mass=massFitter->GetVar(lam0Name);
  mass->setRange("sigRange",lam0MassPDG-15,lam0MassPDG+15);

  TString rangeTitle="sigRegion";
  LHCbStyle();
  
  //==================================================// 
  // Plot D0 Mass Fit
  //==================================================//
  RooPlot* rp_mass = massFitter->PlotFitResults(lam0Name, 
                                                "fitResults",
                                                "sigRange",
                                                rangeTitle.Data());

  TCanvas* c1 = new TCanvas("cnv_mass", "", 1024, 768);
  rp_mass->Draw();
  c1->SaveAs(TString::Format("FitRes_%s_%s_%s_%s_%s.eps",lam0Name,pName,charge,MomRange,index).Data());
  
  //==================================================// 
  // Plot weighted DLL(K-pi) distribution
  //==================================================//
  massFitter->CreateWeightedDataSet("data_sigw",
                                    "nsig_sw");
  massFitter->SetDataSetName("data_sigw");
  RooPlot* rp_kpidk = massFitter->PlotVariable(TString::Format("%s_CombDLLp",pName).Data(),"", "", kTRUE);
  TCanvas* c2 = new TCanvas("cnv_kpidk", "", 1024, 768);
  rp_kpidk->Draw();
  c2->SaveAs(TString::Format("DLLp_%s_%s_%s_%s.eps",pName,charge,MomRange,index).Data());
  
  //==================================================// 
  // Clean up
  //==================================================//
  delete rp_mass;
  delete rp_kpidk;
  delete c1;
  delete c2;
  delete massFitter;
}
#endif // CALIBDATASCRIPTS_LAM0FIT_H
