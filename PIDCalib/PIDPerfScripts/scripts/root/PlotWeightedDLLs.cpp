// $Id: $
// Include files 
#include <iomanip>
#include "RooMsgService.h"

using namespace RooFit;
using namespace RooStats;

//-----------------------------------------------------------------------------
// Implementation file for class : PlotWeigtDLL
//
// 2010-11-27 : Andrew Powell (LHCb)04
//-----------------------------------------------------------------------------


void PlotWeightedDLLs(string File,        // File path
                      string MesonName,   // Pion or Kaon
                      string IDinCalData, // MC: {Pion,Kaon}, Data:{Pi,K}
                      string IDinSigData, // Signal track name (Distribution to compare to)
                      int YaxisMax,       
                      int NBins,          // Binning definition for Chi^2/NDF
                      double DLLMin,      // Lowest DLL value to consider in Chi^2/NDF
                      double DLLMax)      // Lowest DLL value to consider in Chi^2/NDF
{
  gROOT->ProcessLine(".x lhcbstyle.C");

  TFile* f = new TFile( File.c_str() );

  //======================================================================
  // Get RooWorkspace
  //======================================================================
  RooWorkspace* ws = (RooWorkspace*) f->Get("ws");
  ws->Print("v");

  //======================================================================
  // Get DLLK Var   
  //======================================================================
  RooRealVar* Pion_PIDK = ws->var( (IDinCalData+"_CombDLLK").c_str() );
  
  //======================================================================
  // Get Default Calib Data
  //======================================================================
  RooDataSet* data_cal = (RooDataSet*) ws->data( ("Cal"+MesonName).c_str() );
  
  RooDataSet* data_cal_sw = new RooDataSet(("Cal"+MesonName).c_str(),
                                           "Cal. Track Data",
                                           data_cal,
                                           *data_cal->get(),
                                           0,
                                           "nsig_sw");
  
  //======================================================================
  // Get Weighted Calib Data 
  //======================================================================
  //RooDataSet* data_cal_binw = (RooDataSet*) ws->data( ("Weighted"+MesonName).c_str() );
  RooDataSet* data_cal_binw = new RooDataSet(("Cal"+MesonName).c_str(),
                                             "Cal. Track Data",
                                             data_cal,
                                             *data_cal->get(),
                                             0,
                                             "Wgt");

  //======================================================================
  // Get Signal Data
  //======================================================================
  string Postfix = (IDinCalData=="K") ? "Kaon" : "Pion";
  RooDataSet* data_sig = (RooDataSet*) ws->data( ("AND"+MesonName+"_Sig_"+Postfix).c_str() );
  data_sig->changeObservableName((IDinSigData+"_PIDK").c_str(), Pion_PIDK->GetName());

  cout<<data_cal_sw->isWeighted()<<'\t'
      <<data_cal_binw->isWeighted()<<'\t'
      <<data_sig->isWeighted()<<endl;
  data_cal_sw->printValue(cout);
  cout<<endl;
  data_cal_binw->printValue(cout);
  cout<<endl;
  data_sig->printValue(cout);
  cout<<endl;

  //======================================================================
  // Plot DLLK         
  //======================================================================
  RooPlot* frame1 = Pion_PIDK->frame(-150, 150) ; 
  double scaleA = data_cal_sw->sumEntries()/data_cal_binw->sumEntries();
  double scaleB = data_sig->sumEntries()/data_cal_binw->sumEntries();
  data_cal_sw->plotOn(frame1, Name("cal"), LineColor(kBlack), MarkerColor(kBlack), Rescale(1.00/scaleA), Binning(120)) ; 
  data_cal_binw->plotOn(frame1, Name("cal_w"), LineColor(kRed), MarkerColor(kRed), Rescale(1.00), Binning(120)) ; 
  data_sig->plotOn(frame1, Name("data"), LineColor(kBlue), MarkerColor(kBlue), Rescale(1/scaleB), Binning(120)) ; 
  (frame1->GetYaxis())->SetRangeUser(0,YaxisMax);
  (frame1->GetYaxis())->SetTitleOffset(1.20);
  frame1->Draw();
  lhcb7TeVPrelimL->Draw();
  data_cal_sw->printValue(cout);
  cout<<endl;
  data_cal_binw->printValue(cout);
  cout<<endl;

  frame1->Print("v");
 
  //======================================================================
  // Calculate Chi2/NDF between calibration distributions and signal
  //======================================================================
  
  TH1* Cal_sw = (TH1*)data_cal_sw->createHistogram("sWeighted Calib. Data",
                                                   *Pion_PIDK,
                                                   Binning(NBins,
                                                           DLLMin,
                                                           DLLMax)
                                                   );
  
  TH1* Cal_binw = (TH1*)data_cal_binw->createHistogram("Bin Weighed Calib. Data",
                                                       *Pion_PIDK,
                                                       Binning(NBins,
                                                               DLLMin,
                                                               DLLMax)
                                                       );
  
  TH1* Sig = (TH1*)data_sig->createHistogram("Signal Data",
                                            *Pion_PIDK,
                                             Binning(NBins,
                                                     DLLMin,
                                                     DLLMax)
                                             );
  //===========================================================
  // TError Global Definitions
  //===========================================================
  // const Int_t kUnset    =  -1;
  // const Int_t kPrint    =   0;
  // const Int_t kInfo     =   1000;
  // const Int_t kWarning  =   2000;
  // const Int_t kError    =   3000;
  // const Int_t kBreak    =   4000;
  // const Int_t kSysError =   5000;
  // const Int_t kFatal    =   6000;
  Long_t dummy = gROOT->ProcessLine("gErrorIgnoreLevel = kWarning");
  //===========================================================
  
  cout<<setfill('-')<<std::setw(32)<<"-"<<setfill(' ')<<endl;
  cout<<"         Chi2/NDF w.r.t         "<<endl;
  cout<<setfill('-')<<std::setw(32)<<"-"<<setfill(' ')<<endl;
  cout<<std::setw(15)<<"Raw Calib"<<'\t'
      <<std::setw(15)<<"Weighted Calib"<<endl;
  cout<<std::setw(15)<<"Distribution"<<'\t'
      <<std::setw(15)<<"Distribution"<<endl;
  cout<<setfill('-')<<setw(32)<<"-"<<setfill(' ')<<endl;
  cout<<std::setw(15)<<Sig->Chi2Test(Cal_sw,
                                     "UWCHI2/NDF")
      <<'\t'
      <<std::setw(15)<<Sig->Chi2Test(Cal_binw,
                      "UWCHI2/NDF")
      <<endl;
  cout<<setfill('-')<<setw(32)<<"-"<<setfill(' ')<<endl;
}

//======================================================================
// Implementation of PlotWeightDLL for Pion MC Calibration Sample
//======================================================================
  void PlotWeightedDLLs_PionMC()
{
  PlotWeightedDLLs("$PIDPERFSCRIPTSROOT/test/MC/"
                   "EvtMC_18Momx4Etax4nTrk_Up_Kpi_Pi.root",
                   "Pion",
                   "Pi",
                   "Bach",
                   2600,
                   65,
                   -120,
                   10);
}


//======================================================================
// Implementation of PlotWeightDLL for Kaon MC Calibration Sample
//======================================================================
void PlotWeightedDLLs_KaonMC()
{
  PlotWeightedDLLs("$PIDPERFSCRIPTSROOT/test/MC/"
                   "EvtMC_18Momx4Etax4nTrk_Down_Kpi_K.root",
                   "Kaon",
                   "K",
                   "Bach",
                   2600,
                   65,
                   -10,
                   120);
}

//======================================================================
// Implementation of PlotWeightDLL for Pion MC Calibration Sample
//======================================================================
  void PlotWeightedDLLs_PionData()
{
  PlotWeightedDLLs("$DATADISK/gangadir/workspace/powell/LocalXML/1011/output/"
                   "EvtData_18Momx4Etax4nTrk_kpi_Up_0.root",
                   "Pion",
                   "Pi",
                   "Bach",
                   40000,
                   65,
                   -120,
                   10);
}


//======================================================================
// Implementation of PlotWeightDLL for Kaon MC Calibration Sample
//======================================================================
void PlotWeightedDLLs_KaonData()
{
  PlotWeightedDLLs("$PIDPERFSCRIPTSROOT/"
                   "EvtDataPos_32Momx4Etax4nTrk.root",
                   "Kaon",
                   "K",
                   "Bach",
                   40000,
                   65,
                   -10,
                   120);
}

