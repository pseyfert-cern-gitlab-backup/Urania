// $Id: $
// Include files 
#include "PIDPerfTools/EvtTrackDataSet.h"
#include "PIDPerfTools/DataBinCuts.h"
#include "PIDPerfTools/PerfCalculator.h"
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"
#include "RooRealVar.h"
#include "RooBinning.h"
#include "TCut.h"
#include "RooWorkspace.h"
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
// Boost
#include <boost/lexical_cast.hpp>

using namespace RooFit;

void usage(const char* fname) 
{
  std::cout << "Usage: " << gSystem->BaseName(fname)
            << " <polarity> <d0_finalstate> <calib_tack> <ref_track> "<<std::endl;
  std::cout << "\t<polarity> is the magnet polarity (Up/Down)"<<std::endl;
  std::cout << "\t<d0_finalstate> is one of (Kpi/K3pi/KK)"<<std::endl;
  std::cout << "\t<calib_track> is the calibration track sample weighted (K/Pi)"<<std::endl;
  std::cout << "\t<ref_track> is the B->DX bachelor track used in the weighting (K/Pi)"<<std::endl;
}

int main(int argc, char* argv[])
{
  //---------------------------------------------------//
  // argv parameters:
  // 1: Field Orientation (Up/Down)
  // 2: D0 Final State (Kpi,K3pi,KK)
  // 3: Calib Track (K/Pi)
  // 4: Weighting Track (K/Pi)
  if (argc != 5)
  {
    usage(argv[0]);
    return EXIT_FAILURE;
  }
  //---------------------------------------------------//

  gSystem->Load("libRooFit.so");

  //=============================================================================
  // Open Data Efficiency File of Interest
  //=============================================================================
  char* prefix = getenv("DATADISKTMP");
  string Mode = argv[2];
  int (*pf)(int)=tolower; 
  transform(Mode.begin(), Mode.end(), Mode.begin(), pf);

  ifstream infile( TString::Format("%s/ADS/PID/Strip13b/D0Cuts/%s_%s_%s.txt",
                                   prefix,
                                   Mode.c_str(),
                                   argv[1],
                                   (boost::lexical_cast<std::string>(ToLower(argv[3]))).c_str() ).Data() );

  //=============================================================================
  // Read in Efficiencies and Errors
  //=============================================================================
  double p_Effs[9], p_Errs[9];
  std::string line;
  int i=0;
  while (infile)
  {
    cout<<"Reading Line"<<endl;
    getline (infile,line);
    std::stringstream ss(line);
    double a, b, c;
    if (ss >> a >> b >> c)
    {
      p_Effs[i] = b;
      p_Errs[i] = c;
      cout<<p_Effs[i]<<'\t'<<p_Errs[i]<<endl;
    }
    ++i;
    
  }

  /*
  double* p_Effs = NULL;
  double* p_Errs = NULL;

  if(strcmp(argv[3],"Pi")==0 && strcmp(argv[1],"Down")==0)
  {
    p_Effs = Pion_Down_Effs;
    p_Errs = Pion_Down_Errs;
  }
  else if(strcmp(argv[3],"Pi")==0 && strcmp(argv[1],"Up")==0)
  {
    p_Effs = Pion_Up_Effs;
    p_Errs = Pion_Up_Errs;
  }
  else if(strcmp(argv[3],"K")==0 && strcmp(argv[1],"Down")==0)
  {
    p_Effs = Kaon_Down_Effs;
    p_Errs = Kaon_Down_Errs;
  }
  else if(strcmp(argv[3],"K")==0 && strcmp(argv[1],"Up")==0)
  {
    p_Effs = Kaon_Up_Effs;
    p_Errs = Kaon_Up_Errs;
  }
  */
  //======================================================================
  // Ouput file from Test_EvtMC.cpp
  //======================================================================
  //MC B->DPi, D->KPi +ve
  TFile* f_MC = new TFile(TString::Format("$PIDPERFSCRIPTSROOT/test/MC/EvtMC_18Momx4Etax4nTrk_%s_%s_%s.root",
                                          argv[1],
                                          argv[2],
                                          argv[4]).Data());

  //======================================================================
  // Get RooWorkspace
  //======================================================================
  RooWorkspace* ws_MC = (RooWorkspace*) f_MC->Get("ws");
  ws_MC->Print("v");
 
  //======================================================================
  // Obtain RooDataSets
  //======================================================================
  string Postfix_CalID = (strcmp(argv[3],"K")==0) ? "Kaon" : "Pion";
  string Postfix_RefID = (strcmp(argv[4],"K")==0) ? "Kaon" : "Pion";
  cout<<"Cal"+Postfix_CalID<<'\t'<<"AND"+Postfix_CalID+"_Sig_"+Postfix_RefID<<endl;
  RooDataSet* Pion_MCCal_DataSet = (RooDataSet*) ws_MC->data(("Cal"+Postfix_CalID).c_str());
  RooDataSet* Pion_MCSig_DataSet = (RooDataSet*) ws_MC->data(("AND"+Postfix_CalID+"_Sig_"+Postfix_RefID).c_str());
  
  //======================================================================
  // Import DataSets into TrackDataSet instances and declare weighting
  // variable:
  // - peak_yield_sw : Raw calibration
  // - Wgt           : Bin weighted calibration 
  //======================================================================
  EvtTrackDataSet* MC_Cal = new EvtTrackDataSet("Calib. "+Postfix_CalID,
                                                "",
                                                Pion_MCCal_DataSet,
                                                *Pion_MCCal_DataSet->get(),
                                                TString::Format("%s_P",argv[3]).Data(),
                                                TString::Format("%s_PT",argv[3]).Data(),
                                                TString::Format("%s_Eta",argv[3]).Data(),
                                                "nTracks",
                                                TString::Format("%s_CombDLLK",argv[3]).Data(),
                                                TString::Format("%s_CombDLLp",argv[3]).Data(),
                                                "",
                                                "Wgt");
  
  EvtTrackDataSet* MC_Sig = new EvtTrackDataSet(("Signal "+Postfix_CalID).c_str(),
                                                "",
                                                Pion_MCSig_DataSet,
                                                *Pion_MCSig_DataSet->get(),
                                                "Bach_P",
                                                "Bach_PT",
                                                "Bach_TRACK_Eta",
                                                "nTracks",
                                                "Bach_PIDK",
                                                "Bach_PIDp");
  
 
  MC_Cal->Print("v");
  MC_Sig->Print("v");
  
  cout<<MC_Cal->isWeighted()<<'\t'
      <<MC_Sig->isWeighted()<<endl;

  //======================================================================
  // Declare instances of PerfCalculator
  //======================================================================
  PerfCalculator<EvtTrackDataSet>* CalcMC_Cal = new PerfCalculator<EvtTrackDataSet>( MC_Cal );
  PerfCalculator<EvtTrackDataSet>* CalcMC_Sig = new PerfCalculator<EvtTrackDataSet>( MC_Sig );
  
  //======================================================================
  // Define lists of PID cuts
  //======================================================================
  list<std::string> PIDCuts_Pion;
  PIDCuts_Pion.push_back("DLLK < 8.0");
  PIDCuts_Pion.push_back("DLLK < 6.0");
  PIDCuts_Pion.push_back("DLLK < 4.0");
  PIDCuts_Pion.push_back("DLLK < 2.0");
  PIDCuts_Pion.push_back("DLLK < 0.0");
  PIDCuts_Pion.push_back("DLLK < -2.0");
  PIDCuts_Pion.push_back("DLLK < -4.0");
  PIDCuts_Pion.push_back("DLLK < -6.0");
  PIDCuts_Pion.push_back("DLLK < -8.0");

  list<std::string> PIDCuts_Kaon;
  PIDCuts_Kaon.push_back("DLLK > 8.0");
  PIDCuts_Kaon.push_back("DLLK > 6.0");
  PIDCuts_Kaon.push_back("DLLK > 4.0");
  PIDCuts_Kaon.push_back("DLLK > 2.0");
  PIDCuts_Kaon.push_back("DLLK > 0.0");
  PIDCuts_Kaon.push_back("DLLK > -2.0");
  PIDCuts_Kaon.push_back("DLLK > -4.0");
  PIDCuts_Kaon.push_back("DLLK > -6.0");
  PIDCuts_Kaon.push_back("DLLK > -8.0");
 
  //======================================================================
  // Generate ID vs DLL cut value curves
  //======================================================================
  TGraphAsymmErrors* MC_Cal_DLLScan = 0;
  if(strcmp(argv[3],"Pi")==0)
    MC_Cal_DLLScan = CalcMC_Cal->Perf_Scan(PIDCuts_Pion,
                                           kFALSE);
  else
    MC_Cal_DLLScan = CalcMC_Cal->Perf_Scan(PIDCuts_Kaon,
                                           kFALSE);
  MC_Cal_DLLScan->SetName("MC_Cal_DLLScan");
  MC_Cal_DLLScan->GetXaxis()->SetTitle("#Delta LL(K - #pi)");
  MC_Cal_DLLScan->GetYaxis()->SetTitle("Pion ID Efficiency");

  TGraphAsymmErrors* MC_Sig_DLLScan = 0;
  if(strcmp(argv[3],"Pi")==0)
    MC_Sig_DLLScan = CalcMC_Sig->Perf_Scan(PIDCuts_Pion,
                                           kFALSE);
  else
    MC_Sig_DLLScan = CalcMC_Sig->Perf_Scan(PIDCuts_Kaon,
                                           kFALSE);
  MC_Sig_DLLScan->SetName("MC_Sig_DLLScan");
  MC_Sig_DLLScan->GetXaxis()->SetTitle("#Delta LL(K - #pi)");
  MC_Sig_DLLScan->GetYaxis()->SetTitle("Pion ID Efficiency");

  //======================================================================
  // Construct TGraphAsymmErrors of the difference between MC_Sig_DLLScan
  // and MC_Cal_DLLScan
  //======================================================================
  const Int_t numpoints = PIDCuts_Pion.size();
  
  double* resDLL = new double[numpoints];
  double* resY = new double[numpoints];
  double* resY_err_lo = new double[numpoints];
  double* resY_err_hi = new double[numpoints];
  double* resDLLl = new double[numpoints];
  double* resDLLh = new double[numpoints];
  
  for (int i = 0; i < numpoints; i++)
  {
    double x_cal = 0, x_sig = 0;
    double y_cal = 0, y_sig = 0;
    MC_Cal_DLLScan->GetPoint(i, x_cal, y_cal);
    MC_Sig_DLLScan->GetPoint(i, x_sig, y_sig);
    resDLL[i] = x_cal;
    resY[i] = y_sig - y_cal;
    resDLLl[i] = 0.5;
    resDLLh[i] = 0.5;
    resY_err_lo[i] = sqrt( pow(MC_Cal_DLLScan->GetErrorYlow(i),2) + 
                           pow(MC_Sig_DLLScan->GetErrorYlow(i),2));
    resY_err_hi[i] = sqrt( pow(MC_Cal_DLLScan->GetErrorYhigh(i),2) + 
                           pow(MC_Sig_DLLScan->GetErrorYhigh(i),2));
  }
  
  TGraphAsymmErrors* resplot = new TGraphAsymmErrors(numpoints,
                                                     resDLL,
                                                     resY,
                                                     resDLLl,
                                                     resDLLh,
                                                     resY_err_lo,
                                                     resY_err_hi);
  
  resplot->SetTitle("title;DLL(K - #pi);#epsilon^{SIGNAL} - #epsilon^{CALIB}");
  resplot->SetName("Residual");

  delete resDLL;
  delete resY;
  delete resY_err_lo;
  delete resY_err_hi;
  delete resDLLl;
  delete resDLLh;

  //======================================================================
  // Construct TGraphAsymmErrors of the sum of MC_Sig_DLLScan and 
  // MC_Cal_DLLScan
  //======================================================================
  double* sumDLL = new double[numpoints];
  double* sumY = new double[numpoints];
  double* sumY_err_lo = new double[numpoints];
  double* sumY_err_hi = new double[numpoints];
  double* sumDLLl = new double[numpoints];
  double* sumDLLh = new double[numpoints];
  
  for (int i = 0; i < numpoints; i++)
  {
    double x_cal = 0, x_sig = 0;
    double y_cal = 0, y_sig = 0;
    MC_Cal_DLLScan->GetPoint(i, x_cal, y_cal);
    MC_Sig_DLLScan->GetPoint(i, x_sig, y_sig);
    sumDLL[i] = x_cal;
    sumY[i] = y_sig + y_cal;
    sumDLLl[i] = 0.5;
    sumDLLh[i] = 0.5;
    sumY_err_lo[i] = sqrt( pow(MC_Cal_DLLScan->GetErrorYlow(i),2) + 
                           pow(MC_Sig_DLLScan->GetErrorYlow(i),2));
    sumY_err_hi[i] = sqrt( pow(MC_Cal_DLLScan->GetErrorYhigh(i),2) + 
                           pow(MC_Sig_DLLScan->GetErrorYhigh(i),2));
  }
  
  TGraphAsymmErrors* sumplot = new TGraphAsymmErrors(numpoints,
                                                     sumDLL,
                                                     sumY,
                                                     sumDLLl,
                                                     sumDLLh,
                                                     sumY_err_lo,
                                                     sumY_err_hi);
  
  sumplot->SetTitle("title;DLL(K - #pi);#epsilon^{SIGNAL} + #epsilon^{CALIB}");
  sumplot->SetName("Sum");

  delete sumDLL;
  delete sumY;
  delete sumY_err_lo;
  delete sumY_err_hi;
  delete sumDLLl;
  delete sumDLLh;

  //======================================================================
  // Construct TGraphAsymmErrors of the ratio of resplot and sumplot
  //======================================================================
  double* ratioDLL = new double[numpoints];
  double* ratioY = new double[numpoints];
  double* ratioY_err_lo = new double[numpoints];
  double* ratioY_err_hi = new double[numpoints];
  double* ratioDLLl = new double[numpoints];
  double* ratioDLLh = new double[numpoints];
  
  for (int i = 0; i < numpoints; i++)
  {
    double x_res = 0, x_sum = 0;
    double y_res = 0, y_sum = 0;
    resplot->GetPoint(i, x_res, y_res);
    sumplot->GetPoint(i, x_sum, y_sum);
    ratioDLL[i] = x_res;
    ratioY[i] = y_res/y_sum;
    ratioDLLl[i] = 0.5;
    ratioDLLh[i] = 0.5;
    ratioY_err_lo[i] = fabs(y_res/y_sum)*sqrt( pow((resplot->GetErrorYlow(i)/y_res), 2) + 
                                               pow((sumplot->GetErrorYlow(i)/y_sum), 2) + 
                                               ((2*resplot->GetErrorYlow(i)*sumplot->GetErrorYlow(i))/(y_res*y_sum))
                                               );
    ratioY_err_hi[i] = fabs(y_res/y_sum)*sqrt( pow((resplot->GetErrorYhigh(i)/y_res), 2) + 
                                               pow((sumplot->GetErrorYhigh(i)/y_sum), 2) + 
                                               ((2*resplot->GetErrorYlow(i)*sumplot->GetErrorYlow(i))/(y_res*y_sum))
                                               );
    cout<<x_res<<'\t'<<ratioY_err_lo[i]<<'\t'<<ratioY_err_hi[i]<<endl;
  }
  
  TGraphAsymmErrors* ratioplot = new TGraphAsymmErrors(numpoints,
                                                       ratioDLL,
                                                       ratioY,
                                                       ratioDLLl,
                                                       ratioDLLh,
                                                       ratioY_err_lo,
                                                       ratioY_err_hi);
  
  ratioplot->SetTitle("title;DLL(K - #pi);residule/sum");
  ratioplot->SetName("Ratio");

  delete ratioDLL;
  delete ratioY;
  delete ratioY_err_lo;
  delete ratioY_err_hi;
  delete ratioDLLl;
  delete ratioDLLh;

  //======================================================================
  // Construct TGraphAsymmErrors of the product of ratioplot and 
  // PionDataCal_DLLScan
  //======================================================================
  double* prodDLL = new double[numpoints];
  double* prodY = new double[numpoints];
  double* prodY_err_lo = new double[numpoints];
  double* prodY_err_hi = new double[numpoints];
  double* prodDLLl = new double[numpoints];
  double* prodDLLh = new double[numpoints];
  
  for (int i = 0; i < numpoints; i++)
  {
    double x_ratio = 0;
    double y_ratio = 0, y_eff = 0;
    ratioplot->GetPoint(i, x_ratio, y_ratio);
    //PionDataCal_DLLScan->GetPoint(i, x_eff, y_eff);
    y_eff = p_Effs[i];
    prodDLL[i] = x_ratio;
    prodY[i] = y_ratio*2*y_eff;
    prodDLLl[i] = 0.5;
    prodDLLh[i] = 0.5;
    prodY_err_lo[i] = fabs(y_ratio*2*y_eff)*sqrt( pow((ratioplot->GetErrorYlow(i)/y_ratio), 2) + 
                                                  pow((p_Errs[i]/y_eff), 2));
    prodY_err_hi[i] = fabs(y_ratio*2*y_eff)*sqrt( pow((ratioplot->GetErrorYhigh(i)/y_ratio), 2) + 
                                                  pow((p_Errs[i]/y_eff), 2));
  }
  
  TGraphAsymmErrors* prodplot = new TGraphAsymmErrors(numpoints,
                                                       prodDLL,
                                                       prodY,
                                                       prodDLLl,
                                                       prodDLLh,
                                                       prodY_err_lo,
                                                       prodY_err_hi);
  
  prodplot->SetTitle("title;DLL(K - #pi);Corrected Residual");
  prodplot->SetMarkerStyle(8);
  prodplot->GetYaxis()->SetTitleOffset(1.2);
  prodplot->GetYaxis()->SetRangeUser(-0.015,0.015);
  prodplot->GetXaxis()->SetRangeUser(-12.0,22.0);
  prodplot->SetName("Prod");

  delete prodDLL;
  delete prodY;
  delete prodY_err_lo;
  delete prodY_err_hi;
  delete prodDLLl;
  delete prodDLLh;

  //======================================================================
  // Save graphs to file
  //======================================================================
  TFile *myfile = new TFile(TString::Format("Syst_18Momx4Etax4nTrk_%s_%s_%s_%s.root",
                                            argv[1],
                                            argv[2],
                                            argv[3],
                                            argv[4]).Data(), "RECREATE");
  MC_Cal_DLLScan->Write();
  MC_Sig_DLLScan->Write();
  resplot->Write();
  sumplot->Write();
  ratioplot->Write();
  prodplot->Write();

  myfile->Close();

  //======================================================================
  // Clean up
  //======================================================================
  delete MC_Cal_DLLScan;
  delete MC_Sig_DLLScan;
  delete resplot;
  delete sumplot;
  delete ratioplot;
  delete prodplot;
  
  delete myfile;
  
  delete CalcMC_Sig;
  delete CalcMC_Cal;
  
  delete MC_Sig;
  delete MC_Cal;
  
  delete Pion_MCSig_DataSet;
  delete Pion_MCCal_DataSet;

  //delete ws_MC;
  //delete f_MC;
  
  return 0;
  
}

