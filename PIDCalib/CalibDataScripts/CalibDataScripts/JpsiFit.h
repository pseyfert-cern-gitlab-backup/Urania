// $Id: $
#ifndef CALIBDATASCRIPTS_JPSIFIT_H 
#define CALIBDATASCRIPTS_JPSIFIT_H 1

/*
 *  @author Juan Martin Otalora Goicochea
 *  @date   2012-09-26
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

void JpsiFit(TTree* tt, 
            const char* charge,
            const char* pName,
            const char* otherPName,
            const char* wsName,
            const char* fName,
            const char* dsName,
            const char* jpsiName,
            std::vector<fptr>& fun_vec,
            const char* index="0")
{
  
  //==================================================//
  // Constants
  //==================================================//
  Float_t jpsiMassPDG=3096;

  //==================================================//
  // Declare and configure fitter 
  //==================================================//
  RooDMassFitter* massFitter = new RooDMassFitter("MassFitter","");
  massFitter->CreateWS(wsName, "");
  massFitter->AttachFile(fName, "RECREATE");
  massFitter->SetDMassName(jpsiName);
  massFitter->SetDMassSigModelName("sigModel");
  massFitter->SetDMassBkgModelName("bkgModel");
  massFitter->MakeDMassVar(jpsiMassPDG-110,
                           jpsiMassPDG+110,
                           "MeV/c^{2}",
                           "m_{#mu#mu}");

  //==================================================//
  // Add Spectator variables
  //==================================================//
  std::vector<fptr>::iterator itr;
  for(itr=fun_vec.begin(); itr!=fun_vec.end(); ++itr)
  {
    std::cout<<"Adding Spectator Vars"<<std::endl;
    (*itr)(massFitter, "Mu", pName);
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

  TString cutString = TString("(")+pName+TString("_L0MuonDecision_TIS||")+
                                   pName+TString("_L0DiMuonDecision_TIS||")+
                                   pName+TString("_L0PhotonDecision_TIS||")+
                                   pName+TString("_L0ElectronDecision_TIS||")+
                                   pName+TString("_L0HadronDecision_TIS)&&(")+
                                   pName+TString("_Hlt1TrackAllL0Decision_TIS||")+
                                   pName+TString("_Hlt1TrackMuonDecision_TIS)&&")+
                                   pName+TString("_Hlt2Global_TIS&&")+
                                   pName+TString("_Prob&&")+otherPName+TString("_Tag&&")+pName+TString("_Q==")+chrg;

  massFitter->MakeDMassDataSet(tt, 
                               "Jpsi_MM", 
                               dsName, 
                               "", 
                               cutString.Data());
  
  //==================================================//
  // Configure Jpsi Line Shape
  //==================================================//
  massFitter->MakeDMassSigBiGauss(jpsiMassPDG, jpsiMassPDG-10, jpsiMassPDG+10,
                                  12.0,10,13,
                                  2.0,1.5,2.5, 
                                  0.5);
  //massFitter->MakeDMassSigCB(jpsiMassPDG, jpsiMassPDG-10, jpsiMassPDG+10, 
  //                                  12.0, 9.0, 30.0,
  //                                  10, 0, 30, 
  //                                  1, 0, 10);
  
  //==================================================//
  // Configure D0 Background Shape
  //==================================================//
  massFitter->MakeDMassBkgFlat(-0.2, -1, 1);

  //==================================================//
  // Make composite model with following estimate of 
  // yield breakdown
  //==================================================//
  massFitter->MakeDMassModel(0.5, 0.5);
  
  //==================================================// 
  // Perform Fit
  //==================================================//
  std::cout << "Performing fit" << std::endl;
  massFitter->PerformDMassBinnedFit(500,
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
//  TString plotParams="dmass_sig_mu,dmass_sig_sigma,dmass_sig_alpha,dmass_sig_n";
//  plotParams+=",dmass_bkg_poly_c1,dmass_bkg_poly_c2";
  plotParams+=",dmass_bkg_poly_c1";

  massFitter->SetPlotParameters(plotParams.Data());
  massFitter->SetParamBoxAttributes("paramBox",0.68,0.65,0.95,0.93,0.026,12);

  int nbins = 100;
  massFitter->SetPlotBins(nbins);
  massFitter->SetChi2Bins(nbins);
  massFitter->SetChi2Bins(jpsiName,nbins);
  massFitter->SetChi2Bins(jpsiName,nbins/2);
  massFitter->SetParamBoxY1(0.5);
  massFitter->SetParamBoxX1(0.62);
  massFitter->SetParamBoxTextSize(0.022);
  
  //==================================================// 
  // Make plots
  //==================================================//
  RooRealVar* mass=massFitter->GetVar(jpsiName);
  mass->setRange("sigRange",jpsiMassPDG-55,jpsiMassPDG+55);

  TString rangeTitle="sigRegion";
  LHCbStyle();
  
  //==================================================// 
  // Plot D0 Mass Fit
  //==================================================//
  RooPlot* rp_mass = massFitter->PlotFitResults(jpsiName, 
                                                "fitResults",
                                                "sigRange",
                                                rangeTitle.Data());

  TCanvas* c1 = new TCanvas("cnv_mass", "", 1024, 768);
  rp_mass->Draw();
  c1->SaveAs(TString::Format("FitRes_%s_%s_%s_%s.pdf",jpsiName,pName,charge,index).Data());

  //==================================================// 
  // Plot weighted DLL(K-mu) distribution
  //==================================================//
  massFitter->CreateWeightedDataSet("data_sigw",
                                    "nsig_sw");
  massFitter->SetDataSetName("data_sigw");
  RooPlot* rp_mupidmu = massFitter->PlotVariable("Mu_CombDLLmu","", "", kTRUE);
  TCanvas* c2 = new TCanvas("cnv_mupidmu", "", 1024, 768);
  rp_mupidmu->SetAxisRange(-20, 20);
  rp_mupidmu->Draw();
  c2->SaveAs(TString::Format("DLLmu_%s_%s_%s.pdf",pName,charge,index).Data());

  //==================================================// 
  // Clean up
  //==================================================//
  delete rp_mass;
  delete rp_mupidmu;
  delete c1;
  delete c2;
  delete massFitter; 
  
}
#endif // CALIBDATASCRIPTS_JPSIFIT_H
