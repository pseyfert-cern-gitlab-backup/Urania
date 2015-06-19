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




void SystematicPlots(std::vector<std::pair<double,double> > MCSig_Effs,
                     std::vector<std::pair<double,double> > MCCal_Effs,
                     std::vector<std::pair<double,double> > DataCal_Effs,
                     std::vector<double> DLLs,
                     std::string outputFileName)
{
 
  uint vecsize = MCSig_Effs.size();
  if (MCCal_Effs.size()!=vecsize||
      DataCal_Effs.size()!=vecsize||
      DLLs.size()!=vecsize){
    std::cout << "Number of points for systematic graphs not equal!" << std::endl;
    return;
  }

  //======================================================================
  // Construct TGraphAsymmErrors of the difference between MCSig_Effs
  // and MCCal_Effs
  //======================================================================
  const Int_t numpoints = (Int_t)vecsize;
  
  double* resDLL = new double[numpoints];
  double* resY = new double[numpoints];
  double* resY_err_lo = new double[numpoints];
  double* resY_err_hi = new double[numpoints];
  double* resDLLl = new double[numpoints];
  double* resDLLh = new double[numpoints];
  
  for (int i = 0; i < numpoints; i++)
  {
    double y_cal = 0, y_sig = 0;
    y_cal = MCCal_Effs.at(i).first;
    y_sig = MCSig_Effs.at(i).first;
    
    resDLL[i] = DLLs.at(i);
    resY[i] = y_sig - y_cal;
    resDLLl[i] = 0.5;
    resDLLh[i] = 0.5;
    resY_err_lo[i] = sqrt( pow(MCCal_Effs.at(i).second,2) + 
                           pow(MCSig_Effs.at(i).second,2));
    resY_err_hi[i] = sqrt(  pow(MCCal_Effs.at(i).second,2) + 
                            pow(MCSig_Effs.at(i).second,2));
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
  // Construct TGraphAsymmErrors of the sum of MCSig_Effs and 
  // MCCal_Effs
  //======================================================================
  double* sumDLL = new double[numpoints];
  double* sumY = new double[numpoints];
  double* sumY_err_lo = new double[numpoints];
  double* sumY_err_hi = new double[numpoints];
  double* sumDLLl = new double[numpoints];
  double* sumDLLh = new double[numpoints];
  
  for (int i = 0; i < numpoints; i++)
  {
    double y_cal = 0, y_sig = 0;
    y_cal = MCCal_Effs.at(i).first;
    y_sig = MCSig_Effs.at(i).first;
    
    sumDLL[i] = DLLs.at(i);
    sumY[i] = y_sig + y_cal;
    sumDLLl[i] = 0.5;
    sumDLLh[i] = 0.5;
    sumY_err_lo[i] = sqrt( pow(MCCal_Effs.at(i).second,2) + 
                           pow(MCSig_Effs.at(i).second,2));
    sumY_err_hi[i] = sqrt(  pow(MCCal_Effs.at(i).second,2) + 
                            pow(MCSig_Effs.at(i).second,2));

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
  // DataCal_Effs
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
    y_eff = DataCal_Effs.at(i).first;

    prodDLL[i] = x_ratio;
    prodY[i] = y_ratio*y_eff;
    prodDLLl[i] = 0.5;
    prodDLLh[i] = 0.5;
    prodY_err_lo[i] = fabs(y_ratio*y_eff)*sqrt( pow((ratioplot->GetErrorYlow(i)/y_ratio), 2) + 
                                                  pow((DataCal_Effs.at(i).second/y_eff), 2));
    prodY_err_hi[i] = fabs(y_ratio*y_eff)*sqrt( pow((ratioplot->GetErrorYhigh(i)/y_ratio), 2) + 
                                                  pow((DataCal_Effs.at(i).second/y_eff), 2));
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

  //======================================================================
  // Find the Maximum in the prodplot (largest excursion from zero) and 
  // print this. Also print the value of prodplot at the cut in question.
  //======================================================================
  double maxSyst = fabs(prodY[0]);
  double maxSystPosition = prodDLL[0];
  
  for (int i = 0; i < numpoints; i++)
  {
    if (fabs(prodY[i])>=maxSyst){
      maxSyst = fabs(prodY[i]);
      maxSystPosition = prodDLL[i];
    }
  }
  std::cout << "The Maximum systematic over the whole range is " << maxSyst << " and this occurs "
            << "at a cut of " << maxSystPosition << "." << std::endl;
  //======================================================================

  delete prodDLL;
  delete prodY;
  delete prodY_err_lo;
  delete prodY_err_hi;
  delete prodDLLl;
  delete prodDLLh;
  
  //======================================================================
  // Save graphs to file
  //======================================================================
  TFile *myfile = new TFile(outputFileName.c_str(),"recreate");
  resplot->Write();
  sumplot->Write();
  ratioplot->Write();
  prodplot->Write();

  myfile->Close();

  //======================================================================
  // Clean up
  //======================================================================
  delete resplot;
  delete sumplot;
  delete ratioplot;
  delete prodplot;
  
  delete myfile;
  
}

